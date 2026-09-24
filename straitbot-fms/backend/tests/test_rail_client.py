"""通用连接 Client 测试：本地 TCP 假控制板模拟真机/仿真桥。

覆盖：连接与回显收发、接收超时自动断开重连、对端关闭自动重连、
close 停止重连、未连接发送报错、状态序列。
"""
import asyncio
import unittest

from app.rail.client import ConnStatus, ConnectionError2, RailClient


class TcpHarness:
    """本地 TCP server：按连接序号执行不同脚本，模拟控制板行为。"""

    def __init__(self):
        self.server = None
        self.port = 0
        self.clients = []   # [(reader, writer)]
        self.handlers = []  # handler tasks
        self._cb = None     # async def (reader, writer, conn_index)

    def on_connection(self, cb):
        self._cb = cb

    async def start(self):
        self.server = await asyncio.start_server(self._handle, "127.0.0.1", 0)
        self.port = self.server.sockets[0].getsockname()[1]

    async def _handle(self, r, w):
        idx = len(self.clients)
        self.clients.append((r, w))
        if self._cb is None:
            return
        try:
            await self._cb(r, w, idx)
        except asyncio.CancelledError:
            pass
        except Exception:
            pass

    async def close(self):
        for r, w in self.clients:
            try:
                w.close()
            except Exception:
                pass
        if self.server is not None:
            self.server.close()
            await self.server.wait_closed()


async def echo_loop(r, w, idx):
    """回显：收到什么回什么（模拟正常控制板，持续响应）。"""
    try:
        while True:
            data = await r.read(4096)
            if not data:
                break
            w.write(data)
            await w.drain()
    except Exception:
        pass
    finally:
        try:
            w.close()
        except Exception:
            pass


async def wait_status(client: RailClient, want: ConnStatus, timeout: float = 4.0):
    async def _wait():
        while client.status is not want:
            await asyncio.sleep(0.01)
    await asyncio.wait_for(_wait(), timeout)


class RailClientTest(unittest.TestCase):

    def test_connect_and_echo(self):
        async def run():
            h = TcpHarness()
            h.on_connection(echo_loop)
            await h.start()

            statuses, messages = [], []
            c = RailClient("127.0.0.1", h.port, read_timeout=2.0)
            c.on_status_change(lambda s: statuses.append(s))
            c.on_message(lambda b: messages.append(b))
            try:
                await c.open()
                await wait_status(c, ConnStatus.CONNECTED)
                c.send(b"hello")
                await asyncio.wait_for(self._wait_for(lambda: messages), 2.0)
                self.assertEqual(messages, [b"hello"])
                self.assertEqual(statuses[0], ConnStatus.CONNECTING)
                self.assertEqual(statuses[-1], ConnStatus.CONNECTED)
                self.assertNotIn(ConnStatus.RECONNECTING, statuses, "不应发生重连")
            finally:
                await c.close()
                await h.close()
        asyncio.run(run())

    def test_read_timeout_reconnects(self):
        """对端收下消息后不再发数据 → 客户端接收超时 → 主动断开并自动重连成功。"""
        async def run():
            h = TcpHarness()

            async def on_conn(r, w, idx):
                if idx == 0:
                    # 收一条消息后静默（模拟控制板失联）
                    try:
                        await r.read(4096)
                    except Exception:
                        pass
                    try:
                        await asyncio.sleep(30)
                    except asyncio.CancelledError:
                        pass
                else:
                    await echo_loop(r, w, idx)

            h.on_connection(on_conn)
            await h.start()

            reconnects, messages = [], []
            c = RailClient("127.0.0.1", h.port, read_timeout=0.3,
                           reconnect_min=0.2, reconnect_max=0.5)
            c.on_reconnect(lambda n: reconnects.append(n))
            c.on_message(lambda b: messages.append(b))
            try:
                await c.open()
                await wait_status(c, ConnStatus.CONNECTED)
                c.send(b"ping")                       # idx0 收到后静默
                await asyncio.wait_for(self._wait_for(lambda: reconnects), 3.0)
                self.assertEqual(c.status, ConnStatus.CONNECTED, "重连后应回到 connected")
                self.assertTrue(len(reconnects) >= 1, "应至少重连一次")
                c.send(b"pong")                       # idx1 正常回显
                await asyncio.wait_for(self._wait_for(lambda: messages), 2.0)
                self.assertIn(b"pong", messages)
            finally:
                await c.close()
                await h.close()
        asyncio.run(run())

    def test_peer_close_reconnects(self):
        """对端主动断开 → 客户端自动重连。"""
        async def run():
            h = TcpHarness()

            async def on_conn(r, w, idx):
                if idx == 0:
                    w.close()                          # 立即断开
                    return
                await echo_loop(r, w, idx)

            h.on_connection(on_conn)
            await h.start()

            reconnects = []
            c = RailClient("127.0.0.1", h.port, read_timeout=5.0,
                           reconnect_min=0.2, reconnect_max=0.5)
            c.on_reconnect(lambda n: reconnects.append(n))
            try:
                await c.open()
                await wait_status(c, ConnStatus.CONNECTED)
                await asyncio.wait_for(self._wait_for(lambda: reconnects), 3.0)
                self.assertEqual(c.status, ConnStatus.CONNECTED)
                self.assertEqual(len(h.clients), 2, "断开后应重连出第 2 个连接")
            finally:
                await c.close()
                await h.close()
        asyncio.run(run())

    def test_close_stops_reconnect(self):
        """reconnecting 期间 close() → 停止重连，进入 close 终态。"""
        async def run():
            h = TcpHarness()

            async def on_conn(r, w, idx):
                w.close()

            h.on_connection(on_conn)
            await h.start()

            closed = []
            c = RailClient("127.0.0.1", h.port, read_timeout=5.0,
                           reconnect_min=0.2, reconnect_max=0.5)
            c.on_close(lambda: closed.append(True))
            try:
                await c.open()
                await wait_status(c, ConnStatus.CONNECTED)
                await asyncio.wait_for(
                    self._wait_for(lambda: c.status is ConnStatus.RECONNECTING), 3.0)
                await c.close()
                self.assertEqual(c.status, ConnStatus.CLOSE)
                self.assertTrue(closed)
                before = len(h.clients)
                await asyncio.sleep(0.8)               # 超过退避窗口
                self.assertEqual(len(h.clients), before, "close 后不应再重连")
            finally:
                await c.close()
                await h.close()
        asyncio.run(run())

    def test_send_when_not_connected_raises(self):
        async def run():
            h = TcpHarness()
            await h.start()
            c = RailClient("127.0.0.1", h.port)
            try:
                with self.assertRaises(ConnectionError2):
                    c.send(b"x")
            finally:
                await c.close()
                await h.close()
        asyncio.run(run())

    def test_status_sequence_first_open(self):
        async def run():
            h = TcpHarness()
            h.on_connection(echo_loop)
            await h.start()
            statuses = []
            c = RailClient("127.0.0.1", h.port, read_timeout=5.0)
            c.on_status_change(lambda s: statuses.append(s))
            try:
                await c.open()
                await wait_status(c, ConnStatus.CONNECTED)
                self.assertEqual(statuses, [ConnStatus.CONNECTING, ConnStatus.CONNECTED])
            finally:
                await c.close()
                await h.close()
        asyncio.run(run())

    # ---------- helpers ----------
    async def _wait_for(self, check, timeout=3.0):
        async def _wait():
            while not check():
                await asyncio.sleep(0.01)
        await asyncio.wait_for(_wait(), timeout)


if __name__ == "__main__":
    unittest.main()
