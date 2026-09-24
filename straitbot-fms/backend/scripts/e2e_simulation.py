# -*- coding: utf-8 -*-
"""端到端验证: 模拟上位机 → TCP 50000 → 后端 → WS → 前端仿真 → 状态回流。

流程:
  1. 发 0x09 模式5(移动到弧长 12000mm) → 收响应 → 持续收 0x0B, 断言 X 逼近目标且出现状态2
  2. 发 0x09 模式0(停止)
  3. 发 0x0C 伸缩杆模式3(高度 400mm) → 收响应 → 收 0x0E 断言高度上升
"""
import argparse
import socket
import struct
import sys
import time

HEAD, TAIL = 0xA0AB, 0xCD


def crc16(data: bytes, init: int = 0x0000) -> int:
    """下位机实际算法 CRC-16/KERMIT（反射 poly 0x8408 / init 0），见 app/simulation/protocol.py。"""
    crc = init & 0xFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ 0x8408 if crc & 1 else crc >> 1
    return crc & 0xFFFF


def frame(seq: int, cmd: int, payload: bytes = b"") -> bytes:
    body = struct.pack(">HHHBB", HEAD, seq & 0xFFFF, len(payload), 0, cmd) + payload
    return body + struct.pack(">H", crc16(body)) + bytes([TAIL])


def i16(b): return struct.unpack(">h", b)[0]
def i32(b): return struct.unpack(">i", b)[0]


class Upper:
    def __init__(self, port):
        self.sock = socket.create_connection(("127.0.0.1", port), timeout=3)
        self.sock.settimeout(0.4)
        self.seq = 0
        self.buf = b""

    def send(self, cmd, payload=b""):
        self.sock.sendall(frame(self.seq, cmd, payload))
        s = self.seq
        self.seq = (self.seq + 1) & 0xFFFF
        return s

    def recv_frames(self, timeout=1.0, max_frames=40):
        """收齐一批帧, 返回 [(seq, marker, cmd, payload)]"""
        out = []
        end = time.time() + timeout
        while len(out) < max_frames and time.time() < end:
            try:
                data = self.sock.recv(4096)
            except socket.timeout:
                break
            if not data:
                break
            self.buf += data
            while True:
                i = self.buf.find(b"\xA0\xAB")
                if i < 0:
                    self.buf = b""
                    break
                self.buf = self.buf[i:]
                if len(self.buf) < 8:
                    break
                _, mlen, _, cmd = struct.unpack_from(">HHBB", self.buf, 2)
                total = 8 + mlen + 3
                if len(self.buf) < total:
                    break
                f = self.buf[:total]
                self.buf = self.buf[total:]
                seq, marker, c, pl = struct.unpack_from(">H", f, 2)[0], f[6], f[7], f[8:8 + mlen]
                out.append((seq, marker, c, pl))
        return out

    def close(self):
        self.sock.close()


def chassis_state(payload):
    if len(payload) < 18:
        return None
    return {
        "state": payload[0], "mode": payload[1],
        "x": i32(payload[2:6]), "v": i16(payload[12:14]),
    }


def motor_state(payload):
    if len(payload) < 28:
        return None
    return {"state": payload[1], "v": i16(payload[2:4]), "h": i32(payload[4:8])}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=50000)
    ap.add_argument("--target", type=int, default=12000)
    ap.add_argument("--ext", type=int, default=400)
    args = ap.parse_args()

    u = Upper(args.port)
    print(f"[upper] 已连接 :{args.port}")

    # 1) 移动: 模式5 目标 {target}mm
    pl = struct.pack(">B", 5) + struct.pack(">H", 0) + b"\x00\x00\x00\x00" + struct.pack(">i", args.target) + struct.pack(">i", 0) + struct.pack(">h", 0)
    u.send(0x09, pl)
    frames = u.recv_frames(timeout=1.0)
    assert any(c == 0x09 for _, _, c, _ in frames), "未收到 0x09 响应"
    print(f"[ok] 0x09 响应已收到(目标 {args.target}mm)")

    # 2) 监听 0x0B: 应看到 X 接近目标且出现状态2
    print("[..] 监听 0x0B 状态上传(等到位或 15s) …")
    states, arrived = [], False
    end = time.time() + 15
    while time.time() < end:
        for _, _, c, pl in u.recv_frames(timeout=0.5):
            if c == 0x0B:
                st = chassis_state(pl)
                if st:
                    states.append(st)
                    if st["state"] == 2:
                        arrived = True
                    if len(states) <= 8 or st["state"] != 0:
                        print(f"     0x0B 状态={st['state']} X={st['x']} v={st['v']}")
        if arrived and states[-1]["state"] == 0:
            break
    assert states, "15s 内未收到任何 0x0B"
    final = states[-1]
    print(f"[ok] 收到 {len(states)} 帧 0x0B, 最终 X={final['x']} 状态={final['state']}")
    assert abs(final["x"] - args.target) < 50, f"未到位: X={final['x']}"
    assert arrived, "未观察到状态2(已到达)"
    print("[ok] 移动到位且出现 已到达(状态2)")

    # 3) 停止
    u.send(0x09, struct.pack(">B", 0) + b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00")
    time.sleep(0.3)

    # 4) 伸缩杆: 模式3 高度 {ext}mm
    pl = struct.pack(">BB", 1, 3) + struct.pack(">h", 100) + struct.pack(">i", args.ext)
    u.send(0x0C, pl)
    frames = u.recv_frames(timeout=1.0)
    assert any(c == 0x0C for _, _, c, _ in frames), "未收到 0x0C 响应"
    print(f"[ok] 0x0C 响应已收到(目标高度 {args.ext}mm)")

    # 5) 监听 0x0E: 高度应接近目标
    print("[..] 监听 0x0E 电机状态(等到位或 8s) …")
    exts = []
    end = time.time() + 8
    while time.time() < end:
        for _, _, c, pl in u.recv_frames(timeout=0.5):
            if c == 0x0E:
                m = motor_state(pl)
                if m:
                    exts.append(m)
                    if len(exts) <= 4:
                        print(f"     0x0E 状态={m['state']} 高度={m['h']} 速度={m['v']}")
        if exts and exts[-1]["state"] == 0 and len(exts) > 5:
            break
    assert exts, "8s 内未收到 0x0E"
    print(f"[ok] 收到 {len(exts)} 帧 0x0E, 最终高度={exts[-1]['h']}")
    assert abs(exts[-1]["h"] - args.ext) < 30, f"伸缩未到位: {exts[-1]['h']}"
    print("[ok] 伸缩杆到位")

    # 6) 心跳
    u.send(0x06)
    frames = u.recv_frames(timeout=1.0)
    assert any(c == 0x06 for _, _, c, _ in frames), "未收到 0x06 响应"
    print("[ok] 0x06 心跳响应正常")

    u.close()
    print("\n[PASS] 端到端全部通过")


if __name__ == "__main__":
    main()
