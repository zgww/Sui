# -*- coding: utf-8 -*-
"""下位机链路探针：观察 TCP 链路行为 + 受控地试发单条指令。

⚠️ 安全默认：**只**建立 TCP 连接并被动接收，不发任何数据。
   试发必须显式开开关：
     --heartbeat / --hb-interval   发 0x06 心跳（保活请求，无副作用）
     --init                        发 0x01 初始化控制板（会改控制板的方向/避障开关/限位，
                                   **不驱动机构**；发之前请确认现场安全）
     --send-hex A0AB...            发任意原始帧（自担风险）
   **绝不会**主动发 0x09 运动 / 0x0C 伸缩杆等驱动机构的消息。

用法:
    python scripts/probe_board_link.py                          # 只连不发言，观察 12s
    python scripts/probe_board_link.py --seconds 20             # 观察 20s
    python scripts/probe_board_link.py --hb-interval 2          # 连接后立即发心跳，之后每 2s 一次
    python scripts/probe_board_link.py --init --seconds 15      # 连接后立即发 0x01，再观察 15s
"""
import argparse
import socket
import struct
import sys
import time

HEAD, TAIL = 0xA0AB, 0xCD
sys.path.insert(0, ".")
try:
    from app.simulation.protocol import crc16_kermit, crc16_ccitt
except Exception:  # 允许脱离 backend 目录单独跑
    def crc16_kermit(data: bytes, init: int = 0x0000) -> int:
        crc = init & 0xFFFF
        for b in data:
            crc ^= b
            for _ in range(8):
                crc = (crc >> 1) ^ 0x8408 if crc & 1 else crc >> 1
        return crc & 0xFFFF

    def crc16_ccitt(data: bytes, init: int = 0xFFFF) -> int:
        crc = init
        for b in data:
            crc ^= b << 8
            for _ in range(8):
                crc = ((crc << 1) ^ 0x1021) & 0xFFFF if crc & 0x8000 else (crc << 1) & 0xFFFF
        return crc

CMD_NAME = {
    0x01: "初始化控制板", 0x02: "获取控制板配置", 0x03: "重启控制板", 0x04: "获取版本号及SN",
    0x05: "时间校准", 0x06: "心跳", 0x07: "电机电源开关", 0x09: "底盘运动控制",
    0x0A: "获取底盘状态", 0x0B: "上传底盘状态", 0x0C: "伸缩杆控制", 0x0D: "获取伸缩杆状态",
    0x0E: "上传伸缩杆状态", 0x17: "充电状态上传", 0x19: "避障事件上传", 0x26: "急停事件上传",
}


def make_frame(seq: int, cmd: int, payload: bytes = b"", marker: int = 0) -> bytes:
    body = struct.pack(">HHHBB", HEAD, seq & 0xFFFF, len(payload), marker & 0xFF, cmd & 0xFF) + payload
    return body + struct.pack(">H", crc16_kermit(body)) + bytes([TAIL])


def split_frames(buf: bytearray):
    """从缓冲区里切出完整帧（按 8+len+3 切），返回 (frames, 剩余)。"""
    out = []
    while True:
        i = buf.find(b"\xA0\xAB")
        if i < 0:
            buf.clear()
            break
        if i > 0:
            del buf[:i]
        if len(buf) < 8:
            break
        mlen = struct.unpack_from(">H", buf, 4)[0]
        total = 8 + mlen + 3
        if len(buf) < total:
            break
        out.append(bytes(buf[:total]))
        del buf[:total]
    return out


def describe(f: bytes) -> str:
    _, seq, mlen, marker, cmd = struct.unpack_from(">HHHBB", f, 0)
    got = struct.unpack_from(">H", f, 8 + mlen)[0]
    calc = crc16_kermit(f[:8 + mlen])
    return (f"seq={seq:<6} cmd=0x{cmd:02X}({CMD_NAME.get(cmd, '?'):<12}) len={mlen:<3} "
            f"marker=0x{marker:02X} CRC帧内=0x{got:04X} KERMIT=0x{calc:04X} "
            f"{'匹配' if calc == got else '不匹配'}")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", default="192.168.8.91")
    ap.add_argument("--port", type=int, default=16122)
    ap.add_argument("--seconds", type=float, default=12.0, help="连接后观察时长")
    ap.add_argument("--heartbeat", action="store_true", help="观察结束后发一次 0x06 心跳")
    ap.add_argument("--hb-interval", type=float, default=0.0,
                    help="连接后**立即**发 0x06 心跳，之后每 N 秒一次（0=不发）")
    ap.add_argument("--init", action="store_true",
                    help="连接后**立即**发 0x01 初始化控制板（用后端同款编码器）")
    ap.add_argument("--init-payload-len", type=int, default=26,
                    help="--init 时 payload 截断/补零到该长度（默认 26=文档口径；老代码是 25）")
    ap.add_argument("--send-hex", default="", help="连接后立即发送的原始帧（hex）")
    ap.add_argument("--send-at", type=float, default=0.5, help="首次试发的时刻（秒，默认 0.5）")
    ap.add_argument("--dump", default="", help="把收到的完整帧按 hex 逐行写入该文件（供 CRC 反推）")
    args = ap.parse_args()

    print(f"== 连接 {args.host}:{args.port}（观察 {args.seconds}s）==")
    t0 = time.monotonic()
    try:
        s = socket.create_connection((args.host, args.port), timeout=5)
    except Exception as e:
        print(f"  ✗ 连接失败: {e!r}")
        return 2
    print(f"  ✓ TCP 已连接（{time.monotonic() - t0:.2f}s）")

    # 计划要发的帧：(时刻, 标签, bytes)
    plan = []
    if args.send_hex:
        raw = bytes.fromhex(args.send_hex.replace(" ", ""))
        plan.append((args.send_at, f"原始帧 {raw.hex()}", raw))
    if args.init:
        from app.rail.messages import InitRequest
        req = InitRequest()
        pl = req.to_bytes()
        if args.init_payload_len != len(pl):
            pl = (pl + bytes(args.init_payload_len))[:args.init_payload_len]
        f = make_frame(1, 0x01, pl)
        plan.append((args.send_at, f"0x01 初始化控制板 payload={len(pl)}B", f))
    if args.hb_interval > 0:
        plan.append((args.send_at, f"0x06 心跳(每 {args.hb_interval}s)", None))
    plan.sort(key=lambda x: x[0])

    buf = bytearray()
    frames = []          # [(到达时刻, bytes)]
    closed_at = None
    close_reason = ""
    sent = []            # [(时刻, 标签)]
    next_hb = None
    hb_seq = 1
    s.settimeout(0.05)
    idx = 0
    while True:
        now = time.monotonic()
        rel = now - t0
        if rel >= args.seconds:
            break
        while idx < len(plan) and rel >= plan[idx][0]:
            at, label, raw = plan[idx]
            idx += 1
            if raw is None:                      # 心跳（周期）
                hb_seq = (hb_seq % 0xFFFF) + 1
                raw = make_frame(hb_seq, 0x06)
                next_hb = now + args.hb_interval
            try:
                s.sendall(raw)
                sent.append((rel, label))
                print(f"  → [{rel:6.2f}s] 发出 {label}：{raw.hex()}")
            except Exception as e:
                print(f"  ✗ [{rel:6.2f}s] 发送失败: {e!r}")
                closed_at, close_reason = rel, f"发送失败 {e!r}"
                break
        if next_hb is not None and now >= next_hb:
            hb_seq = (hb_seq % 0xFFFF) + 1
            raw = make_frame(hb_seq, 0x06)
            next_hb = now + args.hb_interval
            try:
                s.sendall(raw)
                sent.append((rel, "0x06 心跳"))
                print(f"  → [{rel:6.2f}s] 发出 0x06 心跳 seq={hb_seq}")
            except Exception as e:
                closed_at, close_reason = rel, f"发送失败 {e!r}"
                break
        if closed_at is not None:
            break
        try:
            d = s.recv(4096)
        except socket.timeout:
            continue
        except Exception as e:
            closed_at, close_reason = time.monotonic() - t0, f"接收异常 {e!r}"
            print(f"  ✗ 接收异常 @ {closed_at:.2f}s: {e!r}")
            break
        if not d:
            closed_at, close_reason = time.monotonic() - t0, "对端关闭连接"
            print(f"  ✗ 对端关闭连接 @ {closed_at:.2f}s")
            break
        at = time.monotonic() - t0
        buf.extend(d)
        for f in split_frames(buf):
            frames.append((at, f))

    if closed_at is None:
        print(f"  ✓ 观察期内未断开，共收 {len(buf)} 字节 / {len(frames)} 帧")
    else:
        print(f"  ✗ 断开 @ {closed_at:.2f}s（{close_reason}），共收 {len(frames)} 帧")

    print(f"\n== 收到 {len(frames)} 帧 ==")
    if args.dump:
        try:
            with open(args.dump, "w", encoding="ascii") as fp:
                for _, f in frames:
                    fp.write(f.hex() + "\n")
            print(f"  → 已把 {len(frames)} 帧原始字节写入 {args.dump}")
        except Exception as e:
            print(f"  ✗ 写 dump 失败: {e!r}")
    for at, f in frames[:12]:
        print(f"  [{at:6.2f}s] {describe(f)}")
    if len(frames) > 12:
        print(f"  … 其余 {len(frames) - 12} 帧略")
    if frames:
        ok = sum(1 for _, f in frames[:20]
                 if crc16_kermit(f[:8 + struct.unpack_from(">H", f, 4)[0]])
                 == struct.unpack_from(">H", f, 8 + struct.unpack_from(">H", f, 4)[0])[0])
        print(f"  >>> CRC(KERMIT) 匹配 {ok}/{min(len(frames), 20)}（首 20 帧）")

    if sent:
        print(f"\n== 试发汇总 ==")
        for rel, label in sent:
            print(f"  [{rel:6.2f}s] {label}")
        # 关键判定：发出之后设备是否还继续上发、是否被关闭
        first_send = sent[0][0]
        after = [f for at, f in frames if at > first_send]
        print(f"  首次试发后：再收 {len(after)} 帧，"
              f"{'连接被对端关闭 @ %.2fs' % closed_at if closed_at else '连接保持到观察结束'}")
        if closed_at is None and not after:
            print("  ⚠️ 发出后设备不再上发也不断开 —— 可能被静默忽略（校验不过）")

    try:
        s.close()
    except Exception:
        pass
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
