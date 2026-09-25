"""BoardSrv 测试：请求-响应、超时、上发分发、心跳丢失、断线 fail pending、seq 分配。

BoardSrv 内部管理连接：外部只传 ip/port。复用 TcpHarness 扮演控制板。
"""
import asyncio
import unittest

from app.rail.services.board import BoardSrv, BoardTimeout
from app.rail.client import ConnStatus, ConnectionError2
from app.rail import messages as m
from app.simulation.protocol import FrameParser, decode_frame, encode_frame


class TcpHarness:
    """本地 TCP server：按连接序号执行脚本，模拟控制板。"""

    def __init__(self):
        self.server = None
        self.port = 0
        self.clients = []
        self._cb = None

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


def default_respond(seq, cmd, payload):
    """标准控制板应答：心跳回空、错误码-only 指令回 0、0x0A/0x0D 回状态。未知静默。"""
    if cmd == m.CMD_HEARTBEAT:
        return encode_frame(seq, cmd, b"")
    if cmd in m.ERROR_ONLY_RESPONSE_CMDS:
        return encode_frame(seq, cmd, (0).to_bytes(2, "big"))
    if cmd == m.CMD_GET_CHASSIS:
        st = m.ChassisState(state=m.CHASSIS_RUNNING, mode=m.MODE_EMBEDDED, x=8000)
        return encode_frame(seq, cmd, st.to_bytes())
    if cmd == m.CMD_GET_MOTOR:
        st = m.MotorState(state=m.MOTOR_ST_ARRIVED, coord=350)
        return encode_frame(seq, cmd, st.to_bytes())
    return None


async def board_responder(r, w, idx, *, respond_fn=default_respond, push_frames=(),
                          push_delay=0.15):
    """控制板：读帧 → respond_fn 决定应答；连接后延迟推送 push_frames（主动上发）。"""
    parser = FrameParser()

    async def _push():
        await asyncio.sleep(push_delay)
        for fb in push_frames:
            try:
                w.write(fb)
                await w.drain()
            except Exception:
                return

    if push_frames:
        asyncio.get_running_loop().create_task(_push())
    try:
        while True:
            data = await r.read(4096)
            if not data:
                break
            for frame in parser.feed(data):
                fr = decode_frame(frame)
                if fr is None:
                    continue
                seq, _mk, cmd, payload = fr
                if respond_fn is None:
                    continue
                resp = respond_fn(seq, cmd, payload)
                if resp is not None:
                    w.write(resp)
                    await w.drain()
    except Exception:
        pass
    finally:
        try:
            w.close()
        except Exception:
            pass


async def wait_status(actor: BoardSrv, want: ConnStatus, timeout: float = 4.0):
    async def _wait():
        while actor.status is not want:
            await asyncio.sleep(0.01)
    await asyncio.wait_for(_wait(), timeout)


class BoardSrvTest(unittest.TestCase):

    async def _wait_for(self, check, timeout=3.0):
        async def _wait():
            while not check():
                await asyncio.sleep(0.01)
        await asyncio.wait_for(_wait(), timeout)

    def _mk_actor(self, h, **kw):
        return BoardSrv("127.0.0.1", h.port, **kw)

    def test_request_gets_response(self):
        """request(0x09) → 假板回 ErrorResponse(0)；校验收到的帧内容与 seq。"""
        async def run():
            h = TcpHarness()
            seen = []

            def respond(seq, cmd, payload):
                seen.append((seq, cmd, payload))
                return default_respond(seq, cmd, payload)

            h.on_connection(lambda r, w, i: board_responder(r, w, i, respond_fn=respond))
            await h.start()
            actor = self._mk_actor(h)
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)

                resp = await actor.request(
                    m.ChassisMove(mode=m.MOVE_GOTO, linear_x=1000, target_x=12345))
                self.assertIsInstance(resp, m.ErrorResponse)
                self.assertEqual(resp.error_code, 0)
                self.assertEqual(len(seen), 1)
                seq, cmd, payload = seen[0]
                self.assertEqual(seq, 1)
                self.assertEqual(cmd, m.CMD_CHASSIS_MOVE)
                self.assertEqual(len(payload), 17)
                self.assertEqual(int.from_bytes(payload[7:11], "big", signed=True), 12345)
            finally:
                await actor.stop()
                await h.close()
        asyncio.run(run())

    def test_request_timeout(self):
        """假板对 0x09 静默 → BoardTimeout。"""
        async def run():
            h = TcpHarness()

            def respond(seq, cmd, payload):
                if cmd == m.CMD_CHASSIS_MOVE:
                    return None
                return default_respond(seq, cmd, payload)

            h.on_connection(lambda r, w, i: board_responder(r, w, i, respond_fn=respond))
            await h.start()
            actor = self._mk_actor(h)
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                with self.assertRaises(BoardTimeout) as cm:
                    await actor.request(m.ChassisMove(), timeout=0.2)
                self.assertEqual(cm.exception.cmd, m.CMD_CHASSIS_MOVE)
            finally:
                await actor.stop()
                await h.close()
        asyncio.run(run())

    def test_upload_dispatch(self):
        """假板主动上发 0x0B（18B 仿真格式）→ 精确订阅与通配订阅都收到。"""
        async def run():
            h = TcpHarness()
            upload_payload = bytes([m.CHASSIS_RUNNING, m.MODE_EMBEDDED]) + \
                (8000).to_bytes(4, "big", signed=True) + (0).to_bytes(4, "big", signed=True) + \
                b"\x00\x00" * 4
            push = [encode_frame(100, m.CMD_UPLOAD_CHASSIS, upload_payload)]
            h.on_connection(lambda r, w, i: board_responder(r, w, i, push_frames=push))
            await h.start()
            actor = self._mk_actor(h)
            exact, wild = [], []
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                actor.on(m.CMD_UPLOAD_CHASSIS, exact.append)
                actor.on(wild.append)
                await self._wait_for(lambda: exact and wild)
                self.assertEqual(len(exact), 1)
                self.assertIsInstance(exact[0], m.ChassisState)
                self.assertEqual(exact[0].x, 8000)
                self.assertEqual(exact[0].state, m.CHASSIS_RUNNING)
                self.assertTrue(any(isinstance(x, m.ChassisState) for x in wild))
            finally:
                await actor.stop()
                await h.close()
        asyncio.run(run())

    def test_heartbeat_link_loss(self):
        """假板对 0x06 静默 → 连续丢失触发 on_link_loss。"""
        async def run():
            h = TcpHarness()

            def respond(seq, cmd, payload):
                if cmd == m.CMD_HEARTBEAT:
                    return None  # 心跳不回
                return default_respond(seq, cmd, payload)

            h.on_connection(lambda r, w, i: board_responder(r, w, i, respond_fn=respond))
            await h.start()
            actor = self._mk_actor(
                h, heartbeat_interval=0.1, heartbeat_timeout=0.1, heartbeat_miss_limit=2)
            losses = []
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                actor.on_link_loss(lambda n: losses.append(n))
                await self._wait_for(lambda: losses, timeout=3.0)
                self.assertTrue(losses)
            finally:
                await actor.stop()
                await h.close()
        asyncio.run(run())

    def test_disconnect_fails_pending(self):
        """请求挂起时假板断开 → pending 以 ConnectionError2 fail。"""
        async def run():
            h = TcpHarness()

            async def on_conn(r, w, idx):
                if idx == 0:
                    try:
                        await r.read(4096)  # 收下 0x09 后静默
                        await asyncio.sleep(30)
                    except asyncio.CancelledError:
                        pass
                else:
                    await board_responder(r, w, idx)

            h.on_connection(on_conn)
            await h.start()
            actor = self._mk_actor(h)
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                task = asyncio.create_task(actor.request(m.ChassisMove(), timeout=5.0))
                await asyncio.sleep(0.2)
                await h.close()          # 假板断开 → status 离开 connected → fail pending
                with self.assertRaises(ConnectionError2):
                    await asyncio.wait_for(task, 3.0)
            finally:
                await actor.stop()
                await h.close()
        asyncio.run(run())

    def test_seq_increments(self):
        """连续请求 seq 递增。"""
        async def run():
            h = TcpHarness()
            seqs = []

            def respond(seq, cmd, payload):
                seqs.append(seq)
                return default_respond(seq, cmd, payload)

            h.on_connection(lambda r, w, i: board_responder(r, w, i, respond_fn=respond))
            await h.start()
            actor = self._mk_actor(h)
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                await actor.request(m.HeartbeatMsg())
                await actor.request(m.HeartbeatMsg())
                self.assertEqual(seqs, [1, 2])
            finally:
                await actor.stop()
                await h.close()
        asyncio.run(run())

    def test_unknown_cmd_frame_ignored(self):
        """收到未注册指令的帧 → 忽略不崩，不向订阅者分发。

        ⚠️ 唯一会出现在通配订阅里的是**心跳应答**：连上瞬间就会下发一次 0x06
        （保活需要，见 BoardSrv._heartbeat_loop），它没有等待者，于是作为
        "无主响应"走 `_dispatch` 广播出来。断言时按类型滤掉。
        """
        async def run():
            h = TcpHarness()
            push = [encode_frame(200, 0xFE, b"\x00\x01")]
            h.on_connection(lambda r, w, i: board_responder(r, w, i, push_frames=push))
            await h.start()
            actor = self._mk_actor(h)
            got = []
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                actor.on(got.append)
                await asyncio.sleep(0.4)
                # 0xFE 未注册 → decode 抛 ValueError，被丢弃且不分发；剩下只可能是心跳应答
                self.assertEqual([x for x in got if not isinstance(x, m.HeartbeatMsg)], [])
                # actor 仍可用
                resp = await actor.request(m.HeartbeatMsg())
                self.assertIsInstance(resp, m.HeartbeatMsg)
            finally:
                await actor.stop()
                await h.close()
        asyncio.run(run())

    def test_empty_payload_frame_skipped_quietly(self):
        """空载荷帧 → 跳过，且**不刷 WARNING**、不计入坏帧。

        实测样本 `a0ab0002000000179cb8cd`：CRC 合法、消息长度=0。下位机在连接
        建立初期固定会发 2 帧这种 0x17，之后恢复正常。它没有内容可解，既不是
        校验失败（bad_frame_count 不动），也不该按"解析失败"告警。
        """
        async def run():
            h = TcpHarness()
            push = [bytes.fromhex("a0ab0002000000179cb8cd")]
            h.on_connection(lambda r, w, i: board_responder(r, w, i, push_frames=push))
            await h.start()
            # 放宽心跳窗口，避免测试期内的静默告警干扰日志断言
            actor = self._mk_actor(h, heartbeat_interval=5.0, heartbeat_timeout=5.0)
            got = []
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                actor.on(got.append)
                await asyncio.sleep(0.4)
                # 未作为事件分发（剩下只可能是心跳应答）
                self.assertEqual([x for x in got if not isinstance(x, m.HeartbeatMsg)], [])
                self.assertEqual(actor.bad_frame_count, 0)      # 不是坏帧
                self.assertEqual(actor.empty_payload_count, 1)  # 计入了空载荷
                # 连接仍可用
                resp = await actor.request(m.HeartbeatMsg())
                self.assertIsInstance(resp, m.HeartbeatMsg)
            finally:
                await actor.stop()
                await h.close()

        with self.assertNoLogs("rail.boardsrv", level="WARNING"):
            asyncio.run(run())

    def test_send_fire_and_forget(self):
        """send() 单向下发，不等待响应；假板收到帧即可。"""
        async def run():
            h = TcpHarness()
            seen = []

            def respond(seq, cmd, payload):
                seen.append((seq, cmd))
                return None  # 不回，验证 send 不等待

            h.on_connection(lambda r, w, i: board_responder(r, w, i, respond_fn=respond))
            await h.start()
            actor = self._mk_actor(h)
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                actor.send(m.ChassisMove(mode=m.MOVE_STOP))
                await self._wait_for(lambda: seen)
                self.assertEqual(seen, [(1, m.CMD_CHASSIS_MOVE)])
            finally:
                await actor.stop()
                await h.close()
        asyncio.run(run())

    def test_request_when_disconnected(self):
        """连不上（端口拒绝，重连中）时 request → ConnectionError2。"""
        async def run():
            h = TcpHarness()
            await h.start()
            port = h.port
            await h.close()          # 关闭监听 → 连接被拒 → 内部进入重连中
            actor = BoardSrv("127.0.0.1", port,
                               reconnect_min=0.2, reconnect_max=0.5)
            try:
                await actor.start()
                self.assertEqual(actor.status, ConnStatus.RECONNECTING)
                with self.assertRaises(ConnectionError2):
                    await actor.request(m.HeartbeatMsg())
            finally:
                await actor.stop()
        asyncio.run(run())

    def test_stop_fails_pending(self):
        """请求挂起时 stop() → RuntimeError，且连接被关闭。"""
        async def run():
            h = TcpHarness()
            h.on_connection(lambda r, w, i: board_responder(r, w, i, respond_fn=None))
            await h.start()
            actor = self._mk_actor(h)
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                task = asyncio.create_task(actor.request(m.ChassisMove(), timeout=5.0))
                await asyncio.sleep(0.15)
                await actor.stop()
                with self.assertRaises(RuntimeError):
                    await asyncio.wait_for(task, 2.0)
                self.assertEqual(actor.status, ConnStatus.CLOSE)
            finally:
                await h.close()
        asyncio.run(run())

    def test_restart_after_stop(self):
        """stop 后重新 start 可再次连接并工作。"""
        async def run():
            h = TcpHarness()
            h.on_connection(lambda r, w, i: board_responder(r, w, i))
            await h.start()
            actor = self._mk_actor(h)
            try:
                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                resp = await actor.request(m.HeartbeatMsg())
                self.assertIsInstance(resp, m.HeartbeatMsg)
                await actor.stop()
                self.assertEqual(actor.status, ConnStatus.CLOSE)

                await actor.start()
                await wait_status(actor, ConnStatus.CONNECTED)
                resp = await actor.request(m.HeartbeatMsg())
                self.assertIsInstance(resp, m.HeartbeatMsg)
                self.assertEqual(len(h.clients), 2, "重启应建立第 2 个连接")
            finally:
                await actor.stop()
                await h.close()
        asyncio.run(run())


if __name__ == "__main__":
    unittest.main()
