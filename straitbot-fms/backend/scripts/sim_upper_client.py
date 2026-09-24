# -*- coding: utf-8 -*-
"""模拟上位机 TCP 客户端 — 联调机器人仿真(经后端 50000 端口)。

用法:
    python scripts/sim_upper_client.py                 # 连接 127.0.0.1:50000 进入交互模式
    python scripts/sim_upper_client.py --port 50000    # 指定端口

交互命令:
    heartbeat                    发 0x06 心跳
    move stop|fwd|back|goto|setv 发 0x09 底盘运动控制
        move goto 3000           移动到弧长 3000mm
        move fwd 300             前进 300mm/s
        move setv 500            设定速度 500mm/s
    ext stop|up|down|goto|reset  发 0x0C 伸缩杆控制(电机ID=1)
        ext goto 500             伸缩到高度 500mm
    get                          发 0x0A 查询底盘状态
    monitor                      进入状态监听模式(Ctrl+C 退出, 打印 0x0B/0x0E)
    quit                         退出
"""
import argparse
import socket
import struct
import sys

HEAD, TAIL = 0xA0AB, 0xCD


def crc16(data: bytes, init: int = 0x0000) -> int:
    """下位机实际算法 CRC-16/KERMIT（反射 poly 0x8408 / init 0），见 app/simulation/protocol.py。"""
    crc = init & 0xFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ 0x8408 if crc & 1 else crc >> 1
    return crc & 0xFFFF


def make_frame(seq: int, cmd: int, payload: bytes = b"") -> bytes:
    body = struct.pack(">HHHBB", HEAD, seq & 0xFFFF, len(payload), 0, cmd) + payload
    return body + struct.pack(">H", crc16(body)) + bytes([TAIL])


def parse_frame(frame: bytes):
    seq, mlen, marker, cmd = struct.unpack_from(">HHBB", frame, 2)
    return seq, marker, cmd, frame[8:8 + mlen]


def i16(b: bytes) -> int:
    return struct.unpack(">h", b)[0]


def u16(b: bytes) -> int:
    return struct.unpack(">H", b)[0]


def i32(b: bytes) -> int:
    return struct.unpack(">i", b)[0]


def fmt_cmd(cmd: int, payload: bytes) -> str:
    try:
        if cmd == 0x06:
            return "心跳响应(空)"
        if cmd == 0x09:
            return f"0x09 响应 错误码={u16(payload[:2])}"
        if cmd == 0x0A:
            err, st, mode = u16(payload[:2]), payload[2], payload[3]
            x, y, yaw = i32(payload[4:8]), i32(payload[8:12]), i16(payload[12:14])
            lx, ly, ang = i16(payload[14:16]), i16(payload[16:18]), i16(payload[18:20])
            return (f"0x0A 响应 错误码={err} 状态={st} 模式={mode} "
                    f"X={x} Y={y} YAW={yaw / 10:.1f}° LinearX={lx} LinearY={ly} Angular={ang}")
        if cmd == 0x0B:
            st, mode = payload[0], payload[1]
            x, y, yaw = i32(payload[2:6]), i32(payload[6:10]), i16(payload[10:12])
            lx, ly, ang = i16(payload[12:14]), i16(payload[14:16]), i16(payload[16:18])
            return (f"0x0B 上传 状态={st} 模式={mode} X={x} Y={y} YAW={yaw / 10:.1f}° "
                    f"LinearX={lx} LinearY={ly} Angular={ang}")
        if cmd == 0x0C:
            return f"0x0C 响应 错误码={u16(payload[:2])}"
        if cmd == 0x0E:
            mid, st = payload[0], payload[1]
            v, h = i16(payload[2:4]), i32(payload[4:8])
            sw, err = u16(payload[8:10]), u16(payload[10:12])
            i1, i2, tmp = i32(payload[12:16]), i32(payload[16:20]), i32(payload[20:24])
            return (f"0x0E 上传 电机={mid} 状态={st} 速度={v} 高度={h} 状态字={sw} "
                    f"错误码={err} 电流1={i1} 电流2={i2} 温度={tmp}")
        if cmd in (0x01, 0x02, 0x04, 0x05):
            return f"0x{cmd:02X} 响应 payload={payload.hex()}"
        return f"0x{cmd:02X} payload={payload.hex()}"
    except Exception:
        return f"0x{cmd:02X} payload={payload.hex()}(解析失败)"


def interactive(port: int):
    sock = socket.create_connection(("127.0.0.1", port), timeout=5)
    sock.settimeout(1.0)
    seq = 0
    print(f"[upper] 已连接 127.0.0.1:{port}，输入 help 查看命令")
    while True:
        try:
            line = input("upper> ").strip()
        except (EOFError, KeyboardInterrupt):
            break
        if not line:
            continue
        parts = line.split()
        cmd_name = parts[0].lower()
        try:
            if cmd_name == "quit":
                break
            elif cmd_name == "help":
                print(__doc__.split("交互命令:")[1].split("退出")[0] + "quit")
                continue
            elif cmd_name == "heartbeat":
                frame = make_frame(seq, 0x06)
                seq = (seq + 1) & 0xFFFF
            elif cmd_name == "move":
                mode_map = {"stop": 0, "fwd": 1, "back": 2, "goto": 5, "setv": 6}
                sub, val = parts[1], int(parts[2]) if len(parts) > 2 else 0
                payload = struct.pack(">B", mode_map[sub]) + struct.pack(">H", val) + b"\x00\x00\x00\x00" \
                    + struct.pack(">i", val if sub == "goto" else 0) + struct.pack(">i", 0) + struct.pack(">h", 0)
                frame = make_frame(seq, 0x09, payload)
                seq = (seq + 1) & 0xFFFF
            elif cmd_name == "ext":
                mode_map = {"stop": 0, "up": 1, "down": 2, "goto": 3, "reset": 4}
                sub, val = parts[1], int(parts[2]) if len(parts) > 2 else 0
                payload = struct.pack(">BB", 1, mode_map[sub]) + struct.pack(">h", 100) + struct.pack(">i", val if sub == "goto" else 0)
                frame = make_frame(seq, 0x0C, payload)
                seq = (seq + 1) & 0xFFFF
            elif cmd_name == "get":
                frame = make_frame(seq, 0x0A)
                seq = (seq + 1) & 0xFFFF
            elif cmd_name == "monitor":
                print("[upper] 监听状态上传中… Ctrl+C 返回")
                sock.settimeout(None)
                try:
                    while True:
                        data = sock.recv(4096)
                        if not data:
                            print("[upper] 连接断开")
                            break
                        for f in _split(data):
                            print(fmt_cmd(f[2], f[3]))
                except KeyboardInterrupt:
                    sock.settimeout(1.0)
                    continue
            else:
                print("未知命令, 输入 help")
                continue
            sock.sendall(frame)
            try:
                while True:
                    data = sock.recv(4096)
                    if not data:
                        print("[upper] 连接断开")
                        return
                    for f in _split(data):
                        print(fmt_cmd(f[2], f[3]))
                    break
            except socket.timeout:
                pass
        except (KeyError, IndexError, ValueError):
            print("参数错误, 输入 help")
        except (ConnectionResetError, OSError) as e:
            print(f"[upper] 连接异常: {e}")
            break
    sock.close()
    print("[upper] 已退出")


def _split(data: bytes):
    """简单按帧拆包(联调用, 完整拆包逻辑在后端)。"""
    frames, buf = [], data
    while True:
        idx = buf.find(b"\xA0\xAB")
        if idx < 0:
            break
        buf = buf[idx:]
        if len(buf) < 8:
            break
        _, mlen, _, cmd = struct.unpack_from(">HHBB", buf, 2)
        total = 8 + mlen + 3
        if len(buf) < total:
            break
        frames.append(struct.unpack_from(">H", buf, 0) and parse_frame(buf[:total]))
        buf = buf[total:]
    return frames


def main():
    ap = argparse.ArgumentParser(description="模拟上位机(协议 V2.0)")
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--port", type=int, default=50000)
    args = ap.parse_args()
    interactive(args.port)


if __name__ == "__main__":
    main()
