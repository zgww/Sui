"""通用 TCP 连接客户端：内置连接状态机、自动重连、接收超时。

设计（供 Actor 层复用）：
- 单事件循环内使用（Actor 模式），不跨线程。
- 连接生命周期：open() -> connecting -> connected；
  任何断开（对端关闭 / 异常 / 接收超时）都走内部自动重连：reconnecting -> connecting -> connected。
  只有显式 close() 才进入终态 close，重连循环随之停止。
- 接收消息超时（默认 10s）：读循环对每次 read 施加超时，超时视为"对端失联"，
  主动断开并进入重连——防止半死连接长期悬挂。
- 回调全部在事件循环内同步调用，异常被隔离（仅记日志），不打断读循环。

对外接口：
  open() / close() / send(data)
  on_message / on_error / on_close / on_reconnect / on_status_change（可注册多个）
  status -> ConnStatus 只读
"""
from __future__ import annotations

import asyncio
import logging
from enum import Enum
from typing import Any, Callable, Optional

logger = logging.getLogger("rail.client")


class ConnStatus(str, Enum):
    IDLE = "idle"              # 初始：未 open
    CONNECTING = "connecting"  # 正在建立连接（首次 open 或重连）
    CONNECTED = "connected"    # 已连接，读循环运行中
    RECONNECTING = "reconnecting"  # 断开后等待退避，准备重连
    ERROR = "error"            # 不可自动恢复的错误（预留，当前不进入）
    CLOSE = "close"            # 用户显式 close 后的终态


class ConnectionError2(Exception):
    """连接未建立 / 已关闭时的操作错误。"""


class RailClient:
    def __init__(
        self,
        host: str,
        port: int,
        *,
        read_timeout: float = 10.0,
        reconnect_min: float = 1.0,
        reconnect_max: float = 30.0,
        reconnect_factor: float = 2.0,
        loop: Optional[asyncio.AbstractEventLoop] = None,
    ) -> None:
        self.host = host
        self.port = port
        self.read_timeout = read_timeout
        self.reconnect_min = max(0.1, reconnect_min)
        self.reconnect_max = max(self.reconnect_min, reconnect_max)
        self.reconnect_factor = max(1.0, reconnect_factor)

        self._loop = loop or asyncio.get_event_loop()
        self._status = ConnStatus.IDLE
        self._reader: Optional[asyncio.StreamReader] = None
        self._writer: Optional[asyncio.StreamWriter] = None
        self._read_task: Optional[asyncio.Task] = None
        self._reconnect_task: Optional[asyncio.Task] = None
        self._retry = 0
        self._closed = False          # 用户显式关闭
        self._breaking = False        # 断开处理进行中（防并发重复断开/重连）
        self._lock = asyncio.Lock()

        self._listeners: dict[str, list[Callable[..., Any]]] = {
            "message": [], "error": [], "close": [], "reconnect": [], "status": [],
        }

    # ------------------------------------------------------------ 只读状态
    @property
    def status(self) -> ConnStatus:
        return self._status

    @property
    def connected(self) -> bool:
        return self._status is ConnStatus.CONNECTED

    def _set_status(self, s: ConnStatus) -> None:
        if self._status is s:
            return
        self._status = s
        logger.info("[rail] 连接状态 -> %s (%s:%s)", s.value, self.host, self.port)
        self._notify("status", s)

    # ------------------------------------------------------------ 回调注册
    def _add_listener(self, kind: str, fn: Callable[..., Any]) -> Callable[[], None]:
        """注册监听并返回注销函数（幂等）。"""
        self._listeners[kind].append(fn)

        def _unreg() -> None:
            try:
                self._listeners[kind].remove(fn)
            except ValueError:
                pass
        return _unreg

    def on_message(self, fn: Callable[[bytes], Any]) -> Callable[[], None]:
        """收到对端数据（读循环一次 read 的原始字节段）。返回注销函数。"""
        return self._add_listener("message", fn)

    def on_error(self, fn: Callable[[Exception], Any]) -> Callable[[], None]:
        """发生错误（读/写异常、连接失败等），错误已被内部处理。返回注销函数。"""
        return self._add_listener("error", fn)

    def on_close(self, fn: Callable[[], Any]) -> Callable[[], None]:
        """显式 close() 完成后通知。返回注销函数。"""
        return self._add_listener("close", fn)

    def on_reconnect(self, fn: Callable[[int], Any]) -> Callable[[], None]:
        """每次重连成功通知（参数=本次是第几次重连；首次连接成功不触发）。返回注销函数。"""
        return self._add_listener("reconnect", fn)

    def on_status_change(self, fn: Callable[[ConnStatus], Any]) -> Callable[[], None]:
        return self._add_listener("status", fn)

    def _notify(self, kind: str, *args: Any) -> None:
        for fn in list(self._listeners.get(kind, ())):
            try:
                fn(*args)
            except Exception:
                logger.exception("[rail] 回调 %s 异常", kind)

    # ------------------------------------------------------------ 生命周期
    async def open(self) -> None:
        """主动打开连接。已连接/连接中/重连中忽略；close 后允许重新 open。"""
        async with self._lock:
            if self._status in (ConnStatus.CONNECTED, ConnStatus.CONNECTING, ConnStatus.RECONNECTING):
                logger.info("[rail] open 忽略：当前状态 %s", self._status.value)
                return
            if self._status is ConnStatus.ERROR:
                raise ConnectionError2(f"客户端处于错误状态，无法 open：{self.host}:{self.port}")
            self._closed = False
            self._breaking = False
            self._retry = 0
            logger.info("[rail] open %s:%s", self.host, self.port)
        await self._connect()

    async def close(self) -> None:
        """显式关闭：停止重连、断开 socket、进入终态 close。幂等。"""
        async with self._lock:
            if self._closed:
                return
            self._closed = True
        rt = self._reconnect_task
        if rt is not None and not rt.done():
            rt.cancel()
            try:
                await rt
            except (asyncio.CancelledError, Exception):
                pass
        await self._teardown_connection()
        self._set_status(ConnStatus.CLOSE)
        self._notify("close")

    # ------------------------------------------------------------ 发送
    def send(self, data: bytes) -> None:
        """发送原始字节。未连接抛 ConnectionError2。drain 异步执行防背压阻塞。"""
        if not isinstance(data, (bytes, bytearray)):
            raise TypeError("data 必须是 bytes")
        if self._status is not ConnStatus.CONNECTED or self._writer is None:
            raise ConnectionError2(f"未连接，无法发送（status={self._status.value}）")
        try:
            self._writer.write(bytes(data))
        except Exception as e:
            self._emit_error(e)
            self._loop.create_task(self._on_break(f"写入失败: {e}"))
            raise ConnectionError2(f"写入失败: {e}") from e
        self._loop.create_task(self._drain())

    async def _drain(self) -> None:
        w = self._writer
        if w is None:
            return
        try:
            await w.drain()
        except Exception as e:
            self._emit_error(e)
            await self._on_break(f"写 drain 失败: {e}")

    # ------------------------------------------------------------ 内部：连接
    async def _connect(self) -> None:
        self._set_status(ConnStatus.CONNECTING)
        try:
            reader, writer = await asyncio.open_connection(self.host, self.port)
        except asyncio.CancelledError:
            raise
        except Exception as e:
            self._emit_error(e)
            await self._schedule_reconnect()
            return
        # 与 close() 竞态：连接成功但用户已关闭 → 立即关掉新 socket
        async with self._lock:
            if self._closed:
                self._set_status(ConnStatus.CLOSE)
                try:
                    writer.close()
                    await writer.wait_closed()
                except Exception:
                    pass
                return
        self._reader = reader
        self._writer = writer
        self._set_status(ConnStatus.CONNECTED)
        if self._retry > 0:
            self._notify("reconnect", self._retry)
        self._retry = 0
        self._read_task = self._loop.create_task(self._read_loop())

    async def _read_loop(self) -> None:
        """协程接收消息：每次 read 受 read_timeout 约束；超时 = 对端失联，断开重连。"""
        reader = self._reader
        assert reader is not None
        try:
            while True:
                try:
                    data = await asyncio.wait_for(reader.read(4096), timeout=self.read_timeout)
                except asyncio.TimeoutError:
                    logger.warning("[rail] 接收消息超时 %.1fs，主动断开重连", self.read_timeout)
                    await self._on_break("接收超时")
                    return
                if not data:
                    await self._on_break("对端关闭连接")
                    return
                self._notify("message", data)
        except asyncio.CancelledError:
            pass
        except Exception as e:
            self._emit_error(e)
            await self._on_break(f"读循环异常: {e}")

    # ------------------------------------------------------------ 内部：断开与重连
    async def _on_break(self, reason: str) -> None:
        """连接中断（非用户关闭）：清理 socket 并进入自动重连。并发安全：同一时刻仅一个执行体。"""
        logger.warning("[rail] 连接断开：%s", reason)
        async with self._lock:
            if self._closed or self._breaking:
                return
            self._breaking = True
        try:
            await self._teardown_connection()
        finally:
            async with self._lock:
                self._breaking = False
                if self._closed:
                    return
        await self._schedule_reconnect()

    async def _teardown_connection(self) -> None:
        """关闭当前 socket 与读任务（不改状态机）。幂等。"""
        rt = self._read_task
        if rt is not None:
            rt.cancel()
            try:
                await rt
            except (asyncio.CancelledError, Exception):
                pass
            self._read_task = None
        w = self._writer
        self._reader = None
        self._writer = None
        if w is not None:
            try:
                w.close()
                await w.wait_closed()
            except Exception:
                pass

    async def _schedule_reconnect(self) -> None:
        """进入 reconnecting：指数退避后再次 _connect。close() 会取消本任务。"""
        async with self._lock:
            if self._closed:
                self._set_status(ConnStatus.CLOSE)
                return
            self._set_status(ConnStatus.RECONNECTING)
            self._retry += 1
            wait = min(self.reconnect_max, self.reconnect_min * (self.reconnect_factor ** (self._retry - 1)))
            logger.info("[rail] 第 %d 次重连，%.1fs 后尝试（%s:%s）", self._retry, wait, self.host, self.port)
            self._reconnect_task = self._loop.create_task(self._reconnect_after(wait))

    async def _reconnect_after(self, wait: float) -> None:
        try:
            await asyncio.sleep(wait)
        except asyncio.CancelledError:
            return
        await self._connect()

    def _emit_error(self, e: Exception) -> None:
        logger.warning("[rail] 错误: %r", e)
        self._notify("error", e)
