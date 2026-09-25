"""BoardSrv：控制板消息服务（协议 V2.0 帧/消息层）。

定位：asyncio 单事件循环内的消息服务对象（非 Actor/mailbox 模式）——
外部直接 await 其方法、读取只读属性、注册事件回调；连接层（RailClient）
由内部管理，外部只需传入 ip/port。

职责：
- 唯一负责"帧 ↔ 消息对象"转换：订阅客户端字节流 → FrameParser 解帧 → messages.decode
- 请求-响应：seq 分配（1..65535 循环）、pending future 匹配、超时控制（BoardTimeout）
- 心跳保活：周期单向下发 0x06（连接后立刻发第一个），按"静默窗口内有没有收到
  数据"跟踪链路健康，连续丢失触发 on_link_loss 通知
- 上发事件：0x0B/0x0E/0x15/0x17/0x19/0x1A/0x20/0x26/0x30 等主动上发帧分发给订阅者
- 断线联动：连接状态离开 connected 时 fail 所有 pending（重连由内部 RailClient 负责）

对外接口（业务层 / Navigator 使用）：
  await srv.start() / await srv.stop()                     start=连接+订阅+心跳；stop=停止+断开
  await srv.request(msg, *, timeout=3.0) -> IBoardMsg     请求-响应（响应复用请求 seq）
  srv.send(msg)                                           单向下发，不等待响应
  srv.on(cmd, handler) / srv.on(handler)                  订阅上发/事件消息，返回注销函数
  srv.on_link_loss(handler)                               心跳连续丢失通知，返回注销函数
  srv.status / srv.connected / srv.seq / srv.last_rx_at

错误模型：
  - 未连接请求 → ConnectionError2（连接中/重连中均如此）
  - 请求超时 → BoardTimeout（带 cmd/seq/timeout）
  - 断线/停止 → pending 全部以 ConnectionError2 / RuntimeError fail
"""
from __future__ import annotations

import asyncio
import logging
import time
from typing import Callable, Dict, Optional

from ..client import ConnStatus, ConnectionError2, RailClient
from .. import messages
from ..messages import IBoardMsg, HeartbeatMsg
from ...simulation.protocol import FrameParser, decode_frame, encode_frame

logger = logging.getLogger("rail.boardsrv")

# 控制板主动上发的指令（不参与请求-响应匹配，直接分发给订阅者）
UPLOAD_CMDS = frozenset({
    messages.CMD_UPLOAD_CHASSIS,       # 0x0B
    messages.CMD_UPLOAD_MOTOR,         # 0x0E
    messages.CMD_REMOTE_CTRL_UPLOAD,   # 0x15
    messages.CMD_CHARGE_STATE_UPLOAD,  # 0x17
    messages.CMD_OBSTACLE_EVENT_UPLOAD,  # 0x19
    messages.CMD_HARDWARE_MARK_EVENT,  # 0x1A
    messages.CMD_BOARD_LOG,            # 0x20
    messages.CMD_ESTOP_EVENT_UPLOAD,   # 0x26
    messages.CMD_RFID_RANGE_EVENT,     # 0x30
    # 文档外但确实是"上发"的指令码（见 messages.OPAQUE_UPLOAD_CMDS）。
    # ⚠️ 必须列进来：下位机的上发帧用**它自己的**帧序号，而响应帧复用请求序号，
    # 两个 16 位序号空间会撞车 —— 不在这里拦掉，0x35 就可能被当成某个 pending 请求的响应。
} | frozenset(messages.OPAQUE_UPLOAD_CMDS))


class BoardTimeout(TimeoutError):
    """请求超时。"""

    def __init__(self, cmd: int, seq: int, timeout: float) -> None:
        self.cmd = cmd
        self.seq = seq
        self.timeout = timeout
        super().__init__(f"请求超时 cmd=0x{cmd:02X} seq={seq} timeout={timeout}s")


class BoardSrv:
    """控制板消息服务：连接层（RailClient）由内部管理，外部只传 ip/port。"""

    def __init__(
        self,
        host: str,
        port: int,
        *,
        read_timeout: float = 10.0,
        reconnect_min: float = 1.0,
        reconnect_max: float = 30.0,
        reconnect_factor: float = 2.0,
        request_timeout: float = 3.0,
        heartbeat_interval: float = 2.0,
        heartbeat_timeout: float = 2.0,
        heartbeat_miss_limit: int = 3,
    ) -> None:
        self._client = RailClient(
            host, port,
            read_timeout=read_timeout,
            reconnect_min=reconnect_min,
            reconnect_max=reconnect_max,
            reconnect_factor=reconnect_factor,
        )
        self._host = host
        self._port = port
        self._request_timeout = max(0.1, request_timeout)
        self._hb_interval = max(0.1, heartbeat_interval)
        self._hb_timeout = max(0.1, heartbeat_timeout)
        self._hb_miss_limit = max(1, heartbeat_miss_limit)

        self._loop: Optional[asyncio.AbstractEventLoop] = None
        self._parser = FrameParser()
        self._pending: Dict[int, asyncio.Future] = {}
        self._seq = 0
        self._running = False
        self._heartbeat_task: Optional[asyncio.Task] = None
        self._unregs: list = []
        self._hb_miss = 0
        self._last_rx_at = 0.0
        self._bad_frame_count = 0   # 切帧成功但 decode_frame 不认的帧数（诊断用）
        self._empty_payload_count = 0   # 空载荷帧数（设备连接初期的固定行为，见 _on_client_message）

        self._handlers: Dict[Optional[int], list] = {}
        self._link_loss_handlers: list = []

    # ------------------------------------------------------------ 只读状态
    @property
    def status(self) -> ConnStatus:
        return self._client.status

    @property
    def connected(self) -> bool:
        return self._client.connected

    @property
    def seq(self) -> int:
        return self._seq

    @property
    def last_rx_at(self) -> float:
        """最近一次收到控制板数据的时间（time.monotonic），0=从未收到。"""
        return self._last_rx_at

    @property
    def bad_frame_count(self) -> int:
        """切帧成功但被 `decode_frame` 拒绝的帧数（>0 说明收发两侧校验策略不一致）。"""
        return self._bad_frame_count

    @property
    def empty_payload_count(self) -> int:
        """空载荷帧数（无内容可解，非异常；设备每次连接初期会发 2 帧 0x17）。"""
        return self._empty_payload_count

    # ------------------------------------------------------------ 生命周期
    async def start(self) -> None:
        """连接（内部 open）→ 订阅字节流/状态 → 启动心跳。幂等。

        连接失败由内部 RailClient 自动重连，start 立即返回；
        连接状态通过 srv.status / srv.connected 观察。
        """
        if self._running:
            return
        loop = asyncio.get_running_loop()
        unregs = [
            self._client.on_message(self._on_client_message),
            self._client.on_status_change(self._on_status),
        ]
        # ⚠️ 先置位再 open()：CONNECTED 是在 open() 内部**同步**触发的，注册在
        # on_status_change 上的业务回调（如"连接后下发 0x01 初始化"）会在那一刻
        # 就创建任务；若此时 _running 还是 False，任务一跑就撞 "BoardSrv 未启动"。
        # 期间状态为 connecting，request() 会以 ConnectionError2 拒绝，语义正确。
        self._running = True
        self._loop = loop
        try:
            await self._client.open()
        except Exception:
            self._running = False
            self._loop = None
            for u in unregs:
                try:
                    u()
                except Exception:
                    pass
            raise
        self._unregs = unregs
        self._heartbeat_task = loop.create_task(self._heartbeat_loop())
        logger.info("[boardsrv] BoardSrv 已启动 (%s:%s)", self._host, self._port)

    async def stop(self) -> None:
        """停止心跳、注销订阅、fail 全部 pending、断开连接。幂等。"""
        if not self._running:
            return
        self._running = False
        for un in self._unregs:
            try:
                un()
            except Exception:
                pass
        self._unregs.clear()
        if self._heartbeat_task is not None:
            self._heartbeat_task.cancel()
            try:
                await self._heartbeat_task
            except (asyncio.CancelledError, Exception):
                pass
            self._heartbeat_task = None
        self._fail_pending(RuntimeError("BoardSrv 已停止"))
        await self._client.close()
        logger.info("[boardsrv] BoardSrv 已停止 (%s:%s)", self._host, self._port)

    # ------------------------------------------------------------ 请求-响应
    def _next_seq(self) -> int:
        self._seq = (self._seq % 0xFFFF) + 1  # 1..65535 循环，跳过 0
        return self._seq

    async def request(self, msg: IBoardMsg, *, timeout: Optional[float] = None) -> IBoardMsg:
        """下发请求并等待响应（响应复用请求 seq）。超时抛 BoardTimeout。"""
        if not self._running:
            raise RuntimeError("BoardSrv 未启动")
        if not self._client.connected:
            raise ConnectionError2(f"未连接，无法请求（status={self._client.status.value}）")
        seq = self._next_seq()
        fut: asyncio.Future = self._loop.create_future()
        self._pending[seq] = fut
        try:
            self._client.send(encode_frame(seq, msg.cmd, msg.to_bytes()))
        except ConnectionError2:
            self._pending.pop(seq, None)
            raise
        to = timeout if timeout is not None else self._request_timeout
        try:
            return await asyncio.wait_for(fut, to)
        except asyncio.TimeoutError:
            self._pending.pop(seq, None)
            raise BoardTimeout(cmd=msg.cmd, seq=seq, timeout=to) from None
        except asyncio.CancelledError:
            self._pending.pop(seq, None)
            raise

    def send(self, msg: IBoardMsg) -> None:
        """单向下发（不等待响应）。未连接抛 ConnectionError2。"""
        if not self._running:
            raise RuntimeError("BoardSrv 未启动")
        seq = self._next_seq()
        logger.debug("[boardsrv] 下发 seq=%d cmd=0x%02X", seq, msg.cmd)
        self._client.send(encode_frame(seq, msg.cmd, msg.to_bytes()))

    # ------------------------------------------------------------ 订阅
    def on(self, cmd: Optional[int], handler: Optional[Callable[[IBoardMsg], Any]] = None) -> Callable[[], None]:
        """订阅消息事件。

        - on(0x0B, fn)：仅订阅指定指令（上发/未匹配响应）
        - on(fn)：cmd=None 通配，订阅全部消息
        返回注销函数。
        """
        if handler is None:
            handler = cmd
            cmd = None
        if not callable(handler):
            raise TypeError("handler 必须是可调用对象")
        self._handlers.setdefault(cmd, []).append(handler)

        def _unreg() -> None:
            try:
                self._handlers[cmd].remove(handler)
            except ValueError:
                pass
        return _unreg

    def on_link_loss(self, handler: Callable[[int], Any]) -> Callable[[], None]:
        """心跳连续丢失通知（参数=本次连续丢失次数）。返回注销函数。"""
        self._link_loss_handlers.append(handler)

        def _unreg() -> None:
            try:
                self._link_loss_handlers.remove(handler)
            except ValueError:
                pass
        return _unreg

    def on_status_change(self, handler: Callable[[ConnStatus], Any]) -> Callable[[], None]:
        """订阅连接状态变化（透传 RailClient）。返回注销函数。

        ⚠️ 时序：首次 CONNECTED 是在 `start()` **内部**（`_client.open()`）产生的，
        所以想捕获"第一次连上"必须在 `await start()` **之前**注册；在 start() 之后
        注册只能收到后续的重连。已连接状态下补做的场景，自行判断 `connected`。
        """
        return self._client.on_status_change(handler)

    def _dispatch(self, cmd: int, msg: IBoardMsg) -> None:
        for fn in list(self._handlers.get(cmd, ())) + list(self._handlers.get(None, ())):
            try:
                fn(msg)
            except Exception:
                logger.exception("[boardsrv] 消息处理器异常 cmd=0x%02X", cmd)

    def _notify_link_loss(self) -> None:
        for fn in list(self._link_loss_handlers):
            try:
                fn(self._hb_miss_limit)
            except Exception:
                logger.exception("[boardsrv] 链路丢失处理器异常")

    # ------------------------------------------------------------ 客户端回调
    def _on_client_message(self, data: bytes) -> None:
        if not self._running:
            return
        logger.debug("[boardsrv] 收到 %d 字节", len(data))
        self._last_rx_at = time.monotonic()
        for frame in self._parser.feed(data):
            r = decode_frame(frame)
            if r is None:
                # 切帧层已放行、解码层却不认 → 两边策略不一致（真机上曾整片丢帧）。
                # 计数并节流告警，别每帧都刷（真机 ~4 帧/秒）。
                self._bad_frame_count += 1
                if self._bad_frame_count == 1 or self._bad_frame_count % 500 == 0:
                    logger.warning("[boardsrv] 帧解析失败第 %d 次，丢弃 %d 字节帧: %s",
                                   self._bad_frame_count, len(frame), frame.hex())
                continue
            seq, _marker, cmd, payload = r
            try:
                msg = messages.decode(cmd, payload)
            except ValueError as e:
                if not payload:
                    # 空载荷帧没有内容可解，**不是异常**：下位机在连接建立初期固定会发
                    # 2 帧长度为 0 的 0x17（CRC 合法，实测样本 a0ab0002000000179cb8cd /
                    # a0ab000500000017ac64cd），之后恢复正常。首次 INFO，之后 debug，
                    # 免得每次重连都往日志里刷 WARNING。
                    self._empty_payload_count += 1
                    if self._empty_payload_count == 1 or self._empty_payload_count % 200 == 0:
                        logger.info("[boardsrv] 收到空载荷帧 cmd=0x%02X，跳过（第 %d 次）",
                                    cmd, self._empty_payload_count)
                    else:
                        logger.debug("[boardsrv] 空载荷帧 cmd=0x%02X，跳过", cmd)
                else:
                    logger.warning("[boardsrv] 消息解析失败 cmd=0x%02X: %s", cmd, e)
                continue
            logger.debug("[boardsrv] 收到 cmd=0x%02X seq=%d %s", cmd, seq, msg)
            if cmd in UPLOAD_CMDS:
                self._dispatch(cmd, msg)
                continue
            fut = self._pending.pop(seq, None)
            if fut is not None and not fut.done():
                fut.set_result(msg)
            else:
                # 未匹配的响应（乱序/重复/无请求的应答）→ 按事件分发
                self._dispatch(cmd, msg)

    def _on_status(self, s: ConnStatus) -> None:
        if s is ConnStatus.CONNECTED:
            self._hb_miss = 0
        else:
            self._fail_pending(
                ConnectionError2(f"连接状态 {s.value}，请求已失效（重连后请重试）"))

    def _fail_pending(self, exc: Exception) -> None:
        pend, self._pending = self._pending, {}
        for fut in pend.values():
            if not fut.done():
                fut.set_exception(exc)

    # ------------------------------------------------------------ 心跳
    async def _heartbeat_loop(self) -> None:
        """周期下发 0x06 心跳保活；链路健康按"最近有没有收到数据"判定。

        ⚠️ 三个关键点（2026-09-24 真机 192.168.8.91:16122 实测）：

        1. **连接后必须立刻发第一个心跳**，不能先 sleep 一个周期。下位机约 **3s**
           收不到任何数据就主动断开（被动观察 3.02s 断；每 2s 发一次则 12s 不断）。
           旧实现 `while: sleep(interval)` 打头 + interval=5s → 第一个心跳在 5s 才发，
           设备早在第 3 秒就把连接关了 → 表现就是"一连上就掉、日志里几百次重连"。

        2. 心跳**只发不等**（`send` 而非 `request`）。下位机可能几秒后才回（实测 0x01
           与 0x06 的应答会在 6s 后成批回来），若串行 await 响应，实际发包间隔会被拉长
           到 interval+timeout，照样超过设备的静默超时。发包节奏必须由本地时钟决定。

        3. 链路健康改看 `last_rx_at`：下位机常态每 0.5s 就上发 0x0B/0x0E/0x17，
           "一个静默窗口内一帧都没收到"才是真正的链路异常；只看 0x06 的应答会误判
           （下位机在忙的时候应答会延迟甚至丢）。

        参数：`heartbeat_interval` = 发包周期；`heartbeat_timeout` = 判定静默的窗口
        （`heartbeat_miss_limit` 次连续静默 → `on_link_loss`）。
        """
        tick = max(0.05, min(0.2, self._hb_interval))
        last_sent = 0.0
        try:
            while self._running:
                await asyncio.sleep(tick)
                if not self._running:
                    return
                if not self._client.connected:
                    last_sent = 0.0        # 断开：重连后立刻补一个心跳
                    continue
                now = time.monotonic()
                if last_sent and now - last_sent < self._hb_interval:
                    continue
                try:
                    self.send(HeartbeatMsg())
                except ConnectionError2:
                    continue
                last_sent = now
                # 链路健康：静默窗口内没收到任何数据 → 计一次丢失
                if self._last_rx_at == 0.0:
                    silent, why = True, "从未收到任何数据"
                else:
                    gap = now - self._last_rx_at
                    silent, why = gap > self._hb_timeout, f"已 {gap:.1f}s 无数据"
                if silent:
                    self._hb_miss += 1
                    logger.warning("[boardsrv] 心跳周期内%s，第 %d 次丢失", why, self._hb_miss)
                    if self._hb_miss >= self._hb_miss_limit:
                        self._hb_miss = 0
                        logger.warning("[boardsrv] 连续 %d 次判定链路异常",
                                       self._hb_miss_limit)
                        self._notify_link_loss()
                else:
                    self._hb_miss = 0
        except asyncio.CancelledError:
            pass
