"""TCP(50000) <-> WebSocket 双向桥。

角色: 仿真整体为 TCP 服务端(外部上位机主动连接); 前端经 WebSocket 连入。
- TCP 收到完整帧 → 推给 WS(前端)
- WS 收到前端组好的帧 → 写回 TCP(上位机)
- 连接状态暴露给 /api/simulation/status 与 WS 侧回调

策略(第一版): 单 TCP 客户端, 新连接替换旧连接; WS 单前端, 断开自动清。
"""
import asyncio
import logging

from .protocol import FrameParser

logger = logging.getLogger("simulation.bridge")


class SimulationBridge:
    def __init__(self, host: str = "0.0.0.0", port: int = 50000):
        self.host = host
        self.port = port
        self._tcp_server: asyncio.base_events.Server | None = None
        self._writer_task: asyncio.Task | None = None
        self._ws_to_tcp: asyncio.Queue = asyncio.Queue()

        # 当前连接
        self._tcp_writer: asyncio.StreamWriter | None = None
        self._tcp_connected = False
        self._ws = None
        self._ws_connected = False
        self._lock = asyncio.Lock()
        self._state_cb = None   # 可选: async def cb() -> None, 状态变化时调用
        self.started = False
        self.uptime = 0.0

    # ---------- 生命周期 ----------
    async def start(self):
        self._tcp_server = await asyncio.start_server(self._handle_tcp, self.host, self.port)
        self._writer_task = asyncio.create_task(self._tcp_writer_loop())
        self.started = True
        logger.info("[sim] TCP 监听 %s:%s", self.host, self.port)

    async def close(self):
        if self._writer_task:
            self._writer_task.cancel()
        if self._tcp_server:
            self._tcp_server.close()
            await self._tcp_server.wait_closed()
        self.started = False
        logger.info("[sim] TCP 服务已关闭")

    def set_state_callback(self, cb):
        self._state_cb = cb

    # ---------- TCP 侧 ----------
    async def _handle_tcp(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
        addr = writer.get_extra_info("peername")
        # 下位机(前端仿真 WS)不在线时，不维持与上位机(Robot)的连接：
        # 否则 TCP 虽通却无人应答，会让上位机一直显示"已连接"（假在线）。
        if not self._ws_connected:
            logger.info("[sim] 下位机(WS)不在线，拒绝上位机接入 %s", addr)
            try:
                writer.close()
                await writer.wait_closed()
            except Exception:
                pass
            return
        async with self._lock:
            old = self._tcp_writer
            self._tcp_writer = writer
            self._tcp_connected = True
        if old is not None:
            try:
                old.close()
                await old.wait_closed()
            except Exception:
                pass
            logger.info("[sim] TCP 旧连接已替换")
        logger.info("[sim] TCP 客户端接入: %s", addr)
        self._notify_state()

        parser = FrameParser()
        try:
            while True:
                data = await reader.read(4096)
                if not data:
                    break
                frames = parser.feed(data)
                if parser.discarded:
                    logger.warning("[sim] TCP 丢弃 %d 字节(非帧/坏帧)", parser.discarded)
                    parser.discarded = 0
                for frame in frames:
                    await self._push_to_ws(frame)
        except (ConnectionResetError, asyncio.IncompleteReadError):
            pass
        except Exception as e:
            logger.warning("[sim] TCP 读循环异常: %r", e)
        finally:
            async with self._lock:
                if self._tcp_writer is writer:
                    self._tcp_writer = None
                    self._tcp_connected = False
            try:
                writer.close()
            except Exception:
                pass
            logger.info("[sim] TCP 客户端断开: %s", addr)
            self._notify_state()

    async def _tcp_writer_loop(self):
        """WS → TCP 帧回写循环。"""
        while True:
            frame = await self._ws_to_tcp.get()
            async with self._lock:
                w = self._tcp_writer
            if w is None:
                continue  # 无 TCP 客户端, 丢弃(前端仍本地生效)
            try:
                w.write(frame)
                await w.drain()
            except Exception:
                pass

    # ---------- WS 侧 ----------
    async def attach_ws(self, ws):
        """新下位机(前端仿真)接入。单下位机语义：替换并踢掉旧连接。"""
        async with self._lock:
            old = self._ws
            self._ws = ws
            self._ws_connected = True
        if old is not None and old is not ws:
            try:
                await old.close()
            except Exception:
                pass
            logger.info("[sim] 旧 WS 被新连接替换")
        self._notify_state()
        logger.info("[sim] 前端 WS 已接入")

    async def detach_ws(self, ws=None):
        """下位机断开。

        - 传入具体连接：仅当它仍是"当前连接"时才清空，避免旧连接乱序断开误伤新连接；
        - 不传(ws=None)：强制清空当前连接（测试 / 显式关闭语义）。
        """
        async with self._lock:
            if ws is not None and self._ws is not ws:
                return
            self._ws = None
            self._ws_connected = False
        # 下位机掉线：同步断开上位机(Robot)的 TCP，使其立即进入重连，避免假在线
        await self._drop_tcp()
        self._notify_state()
        logger.info("[sim] 前端 WS 已断开")

    async def _drop_tcp(self):
        """关闭并清空当前上位机(TCP)连接。"""
        async with self._lock:
            w = self._tcp_writer
            self._tcp_writer = None
            self._tcp_connected = False
        if w is not None:
            try:
                w.close()
                await w.wait_closed()
            except Exception:
                pass

    async def _push_to_ws(self, frame: bytes):
        ws = self._ws
        if ws is None:
            return
        try:
            await ws.send_bytes(frame)
        except Exception as e:
            logger.warning("[sim] 推送 WS 失败: %r", e)

    def enqueue_to_tcp(self, frame: bytes):
        """前端 WS 收到帧 → 队列 → TCP 回写。"""
        self._ws_to_tcp.put_nowait(frame)

    # ---------- 状态 ----------
    def status(self) -> dict:
        return {
            "tcp_connected": self._tcp_connected,
            "ws_connected": self._ws_connected,
            "tcp_host": self.host,
            "tcp_port": self.port,
            "started": self.started,
        }

    def _notify_state(self):
        if self._state_cb is not None:
            try:
                asyncio.get_running_loop().create_task(self._state_cb())
            except RuntimeError:
                pass


# 模块级单例(由 main.py lifespan 启动)
bridge = SimulationBridge()
