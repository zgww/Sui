# -*- coding: utf-8 -*-
"""仿真模块单测: CRC / 帧编解码 / 拆包器 / TCP<->WS 桥转发回环。

运行:  cd backend && python -m unittest tests.test_simulation -v
"""
import asyncio
import unittest

from app.simulation.protocol import (
    FRAME_HEAD, FRAME_TAIL, HEADER_LEN, CRC_LEN,
    crc16_kermit, crc16_ccitt, encode_frame, decode_frame, FrameParser,
    CMD_HEARTBEAT, CMD_CHASSIS_MOVE, CMD_UPLOAD_CHASSIS,
)
from app.simulation.bridge import SimulationBridge


class TestCRC(unittest.TestCase):
    def test_board_algorithm_known_vector(self):
        """下位机实际用的是 CRC-16/KERMIT（反射 CCITT / init 0）。"""
        self.assertEqual(crc16_kermit(b"123456789"), 0x2189)

    def test_board_algorithm_matches_real_frames(self):
        """真机报文样本（2026-09-24 采集）必须全部通过校验 —— 这是算法的唯一硬证据。"""
        samples = [
            # 0x35 / 0x17 / 0x0B / 0x0E 各取一帧（帧头..消息内容 的 KERMIT 值 = 帧内值）
            "a0ab0000000500350800020000d0decd",
            "a0ab0002000000179cb8cd",
        ]
        for h in samples:
            f = bytes.fromhex(h)
            mlen = int.from_bytes(f[4:6], "big")
            self.assertEqual(crc16_kermit(f[:8 + mlen]),
                             int.from_bytes(f[8 + mlen:10 + mlen], "big"), h)

    def test_ccitt_reference_only(self):
        # 文档口径的 CCITT-FALSE，仅作对照（下位机不用它）
        self.assertEqual(crc16_ccitt(b"123456789"), 0x29B1)

    def test_empty(self):
        self.assertEqual(crc16_ccitt(b""), 0xFFFF)
        self.assertEqual(crc16_kermit(b""), 0x0000)


class TestFrameCodec(unittest.TestCase):
    def test_encode_structure(self):
        payload = bytes([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])  # 0x09 停止
        frame = encode_frame(1, CMD_CHASSIS_MOVE, payload)
        self.assertEqual(frame[:2], b"\xA0\xAB")
        self.assertEqual(frame[2:4], b"\x00\x01")           # seq=1
        self.assertEqual(frame[4:6], b"\x00\x07")           # 长度=7
        self.assertEqual(frame[6], 0x00)                     # 标记
        self.assertEqual(frame[7], 0x09)                     # 指令
        self.assertEqual(frame[-1], 0xCD)                    # 帧尾
        self.assertEqual(len(frame), HEADER_LEN + 7 + CRC_LEN + 1)

    def test_roundtrip(self):
        for payload in (b"", bytes([0x06]), bytes(range(16))):
            frame = encode_frame(0xABCD, 0x0C, payload, marker=0x80)
            got = decode_frame(frame)
            self.assertIsNotNone(got)
            seq, marker, cmd, pl = got
            self.assertEqual(seq, 0xABCD)
            self.assertEqual(marker, 0x80)
            self.assertEqual(cmd, 0x0C)
            self.assertEqual(pl, payload)

    def test_decode_reject(self):
        frame = encode_frame(0, CMD_HEARTBEAT)
        self.assertIsNone(decode_frame(frame[:-1]))            # 截断
        self.assertIsNone(decode_frame(frame + b"\x00"))       # 多余
        bad2 = bytearray(frame)
        bad2[0] = 0x00                                         # 破坏帧头
        self.assertIsNone(decode_frame(bytes(bad2)))
        bad3 = bytearray(frame)
        bad3[-1] = 0x00                                        # 破坏帧尾
        self.assertIsNone(decode_frame(bytes(bad3)))

    def test_decode_crc_mismatch_policy(self):
        """CRC 不匹配的处置由 ACCEPT_CRC_MISMATCH 决定。

        默认**严格**（算法已确认为 KERMIT，真机 53/53 帧复核通过）；置 True 可放行
        （现场应急），放行时仍计数。
        """
        frame = bytearray(encode_frame(0, CMD_HEARTBEAT))
        frame[-2] ^= 0xFF                                      # 破坏 CRC
        frame = bytes(frame)

        import app.simulation.protocol as P
        before = P.crc_mismatch_count()
        self.assertIsNone(decode_frame(frame))                 # 默认严格丢弃
        self.assertEqual(P.crc_mismatch_count(), before + 1)   # 但被计数

        old = P.ACCEPT_CRC_MISMATCH
        P.ACCEPT_CRC_MISMATCH = True
        try:
            self.assertIsNotNone(decode_frame(frame))          # 放行模式接受
        finally:
            P.ACCEPT_CRC_MISMATCH = old


class TestFrameParser(unittest.TestCase):
    def test_two_frames_in_one_feed(self):
        a = encode_frame(1, CMD_HEARTBEAT)
        b = encode_frame(2, CMD_CHASSIS_MOVE, bytes(7))
        frames = FrameParser().feed(a + b)
        self.assertEqual(len(frames), 2)
        self.assertEqual(decode_frame(frames[0])[0], 1)
        self.assertEqual(decode_frame(frames[1])[0], 2)

    def test_split_feed(self):
        a = encode_frame(5, CMD_HEARTBEAT)
        p = FrameParser()
        self.assertEqual(p.feed(a[:3]), [])
        self.assertEqual(p.feed(a[3:9]), [])
        frames = p.feed(a[9:])
        self.assertEqual(len(frames), 1)
        self.assertEqual(decode_frame(frames[0])[0], 5)

    def test_garbage_resync(self):
        a = encode_frame(7, CMD_HEARTBEAT)
        stream = b"\x01\x02\x03" + a
        frames = FrameParser().feed(stream)
        self.assertEqual(len(frames), 1)
        self.assertEqual(decode_frame(frames[0])[0], 7)

    def test_bad_crc_frame_kept_by_parser_dropped_by_decoder(self):
        """职责划分：切帧层只看 帧头/长度/帧尾（不判 CRC），CRC 由 decode_frame 判。

        两层**算法必须一致**——历史上解析层把校验注释掉、解码层按错的算法校验，
        导致真机每一帧都被丢掉（连接通、数据全 0）。
        """
        good = encode_frame(8, CMD_HEARTBEAT)
        bad = bytearray(good)
        bad[-2] ^= 0x01                                        # 只改 CRC 字节
        p = FrameParser()
        frames = p.feed(bytes(bad) + good)
        self.assertEqual(len(frames), 2)                       # 两帧都被切出来
        self.assertIsNone(decode_frame(frames[0]))             # 坏 CRC 被解码层丢弃
        self.assertEqual(decode_frame(frames[1])[0], 8)        # 好帧照常通过


class TestBridgeLoopback(unittest.TestCase):
    def test_tcp_to_ws_and_back(self):
        async def run():
            bridge = SimulationBridge("127.0.0.1", 0)
            await bridge.start()
            real_port = bridge._tcp_server.sockets[0].getsockname()[1]

            # 模拟前端 WS: 记录收到的帧
            received = []

            class FakeWS:
                async def send_bytes(self, data):
                    received.append(data)

            await bridge.attach_ws(FakeWS())

            # TCP 客户端发两帧(一包发), 验证 WS 收到
            reader, writer = await asyncio.open_connection("127.0.0.1", real_port)
            a = encode_frame(10, CMD_HEARTBEAT)
            b = encode_frame(11, CMD_UPLOAD_CHASSIS, bytes(13))
            writer.write(a + b)
            await writer.drain()
            for _ in range(50):
                if len(received) >= 2:
                    break
                await asyncio.sleep(0.02)

            # WS -> TCP: 前端组响应帧, 验证 TCP 收到
            resp = encode_frame(10, CMD_CHASSIS_MOVE, b"\x00\x00")
            bridge.enqueue_to_tcp(resp)
            tcp_back = await asyncio.wait_for(reader.read(4096), timeout=2)

            bridge.detach_ws_task = None
            await bridge.detach_ws()
            writer.close()
            await bridge.close()

            self.assertEqual(len(received), 2)
            self.assertEqual(decode_frame(received[0])[0], 10)
            self.assertEqual(decode_frame(received[1])[0], 11)
            self.assertEqual(decode_frame(tcp_back)[0], 10)
            self.assertEqual(decode_frame(tcp_back)[2], CMD_CHASSIS_MOVE)

        asyncio.run(run())


if __name__ == "__main__":
    unittest.main()
