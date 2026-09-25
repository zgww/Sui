# -*- coding: utf-8 -*-
"""后端冒烟: WS(模拟前端) <-> TCP(模拟上位机) 全链路转发验证。"""
import asyncio
import struct
import sys

sys.path.insert(0, r"D:\git_ai\straitbot-fms\backend")
from app.simulation.protocol import encode_frame, decode_frame, CMD_HEARTBEAT, CMD_CHASSIS_MOVE

try:
    import websockets
except ImportError:
    print("websockets 库不可用, 跳过 WS 冒烟")
    sys.exit(0)


async def main():
    # 1. WS 连前端端点
    async with websockets.connect("ws://127.0.0.1:8000/ws/simulation") as ws:
        # 2. TCP 连 50000(模拟上位机)
        reader, writer = await asyncio.open_connection("127.0.0.1", 50000)
        print("[ok] TCP 50000 已连接")

        # 3. TCP -> WS: 发心跳帧
        hb = encode_frame(1, CMD_HEARTBEAT)
        writer.write(hb)
        await writer.drain()
        got = await asyncio.wait_for(ws.recv(), timeout=3)
        d = decode_frame(got)
        assert d is not None and d[2] == CMD_HEARTBEAT, f"WS 收到异常: {got.hex()}"
        print("[ok] TCP->WS 转发: 心跳帧(seq=1) 送达前端")

        # 4. WS -> TCP: 前端回响应帧
        resp = encode_frame(1, CMD_CHASSIS_MOVE, b"\x00\x00")
        await ws.send(resp)
        back = await asyncio.wait_for(reader.read(4096), timeout=3)
        d2 = decode_frame(back)
        assert d2 is not None and d2[2] == CMD_CHASSIS_MOVE, f"TCP 收到异常: {back.hex()}"
        print("[ok] WS->TCP 转发: 0x09 响应帧 送达上位机")

        # 5. status 端点
        import httpx
        async with httpx.AsyncClient() as c:
            r = await c.get("http://127.0.0.1:8000/api/simulation/status")
            st = r.json()
            print(f"[ok] /api/simulation/status -> {st}")
            assert st["tcp_connected"] and st["ws_connected"]

        writer.close()
    print("[PASS] 后端桥全链路冒烟通过")


asyncio.run(main())
