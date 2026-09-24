# -*- coding: utf-8 -*-
"""从真机帧样本反推下位机的校验算法。

背景：文档写「校验码 CRC16-CCITT 标准」，但真机帧里的 2 字节校验值与 CCITT-FALSE
（poly 0x1021 / init 0xFFFF）**全部不匹配**，此前手工试过的 29 种标准变体也都不匹配。
所以这里做穷举：**65536 个多项式 × 2 个方向（MSB-first / LSB-first）× 若干初值 ×
若干参与校验的字节区间 × 2 种字节序**，用 numpy 向量化跑完。

用法:
    python scripts/probe_board_link.py --hb-interval 2 --seconds 14 --dump frames.txt
    python scripts/solve_board_crc.py frames.txt
"""
import argparse
import struct
import sys

import numpy as np

ALL_POLYS = np.arange(1, 0x10000, dtype=np.uint16)
N = len(ALL_POLYS)
AR = np.arange(N)


def build_tables_msb(polys: np.ndarray) -> np.ndarray:
    """MSB-first（非反射）查表：table[p][b] = 用多项式 p 处理单字节 b 的结果。"""
    base = np.arange(256, dtype=np.uint32)
    c = np.broadcast_to((base << 8) & 0xFFFF, (len(polys), 256)).copy()
    P = polys.astype(np.uint32)[:, None]
    for _ in range(8):
        top = (c & 0x8000) != 0
        c = (c << 1) & 0xFFFF
        c = np.where(top, c ^ P, c)
    return c.astype(np.uint16)


def build_tables_lsb(polys: np.ndarray) -> np.ndarray:
    """LSB-first（反射）查表。"""
    base = np.arange(256, dtype=np.uint32)
    c = np.broadcast_to(base, (len(polys), 256)).copy()
    P = polys.astype(np.uint32)[:, None]
    for _ in range(8):
        low = (c & 1) != 0
        c = c >> 1
        c = np.where(low, c ^ P, c)
    return c.astype(np.uint16)


def crc_msb(tables, data: bytes, init: int) -> np.ndarray:
    crc = np.full(N, init, dtype=np.uint16)
    for b in data:
        i = ((crc >> 8) ^ b).astype(np.int32)
        crc = (((crc.astype(np.uint32) << 8) & 0xFFFF) ^ tables[AR, i]).astype(np.uint16)
    return crc


def crc_lsb(tables, data: bytes, init: int) -> np.ndarray:
    crc = np.full(N, init, dtype=np.uint16)
    for b in data:
        i = ((crc ^ b) & 0xFF).astype(np.int32)
        crc = ((crc.astype(np.uint32) >> 8) ^ tables[AR, i]).astype(np.uint16)
    return crc


def parse_samples(path: str):
    """读 hex 行 → [(frame_bytes, mlen, stored_crc_be, stored_crc_le)]。"""
    out = []
    with open(path, encoding="ascii") as fp:
        for line in fp:
            line = line.strip()
            if not line:
                continue
            f = bytes.fromhex(line)
            if len(f) < 11 or f[0] != 0xA0 or f[1] != 0xAB or f[-1] != 0xCD:
                continue
            mlen = struct.unpack_from(">H", f, 4)[0]
            if len(f) != 8 + mlen + 3:
                continue
            out.append((f, mlen,
                        struct.unpack_from(">H", f, 8 + mlen)[0],
                        struct.unpack_from("<H", f, 8 + mlen)[0]))
    return out


def ranges_of(f: bytes, mlen: int):
    """候选的「参与校验的字节区间」。"""
    return {
        "帧头..消息内容 (文档口径)": f[:8 + mlen],
        "帧序号..消息内容": f[2:8 + mlen],
        "仅消息内容": f[8:8 + mlen],
        "帧头..消息内容+帧尾": f[:8 + mlen] + f[-1:],
        "帧头..消息内容+校验位(置0)": f[:8 + mlen] + b"\x00\x00",
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("frames", help="hex 逐行的帧样本文件")
    ap.add_argument("--limit", type=int, default=0, help="只用前 N 帧做首轮筛选（0=全用）")
    args = ap.parse_args()

    samples = parse_samples(args.frames)
    if not samples:
        print("✗ 没有可用样本")
        return 2
    print(f"样本 {len(samples)} 帧；命令码分布：", end="")
    dist = {}
    for f, mlen, *_ in samples:
        dist[f[7]] = dist.get(f[7], 0) + 1
    print(", ".join(f"0x{k:02X}×{v}" for k, v in sorted(dist.items())))

    probe = samples[: args.limit] if args.limit else samples
    print(f"首轮筛选用 {len(probe)} 帧\n")

    tab_msb = build_tables_msb(ALL_POLYS)
    tab_lsb = build_tables_lsb(ALL_POLYS)

    hits = []
    for label, get in (("MSB-first", "msb"), ("LSB-first", "lsb")):
        tables = tab_msb if get == "msb" else tab_lsb
        fn = crc_msb if get == "msb" else crc_lsb
        for init in (0x0000, 0xFFFF, 0x1D0F, 0x800D, 0xB2AA):
            for rname in ("帧头..消息内容 (文档口径)", "帧序号..消息内容",
                          "仅消息内容", "帧头..消息内容+帧尾"):
                for endian in ("BE", "LE"):
                    cand = None
                    use = 0
                    for use in range(1, len(probe) + 1):
                        f, mlen, be, le = probe[use - 1]
                        data = ranges_of(f, mlen)[rname]
                        want = be if endian == "BE" else le
                        got = fn(tables, data, init)
                        keep = np.nonzero(got == want)[0]
                        if keep.size == 0:
                            cand = keep
                            break
                        cand = keep if use == 1 else np.intersect1d(cand, keep, assume_unique=True)
                        if cand.size == 0:
                            break
                    if cand is not None and cand.size and use == len(probe):
                        for p in cand[:20]:
                            hits.append((label, init, rname, endian, int(ALL_POLYS[p])))

    if not hits:
        print("✗ 未命中：65536 多项式 × 2 方向 × 5 初值 × 4 区间 × 2 字节序 全部不匹配")
        print("  → 下位机很可能不是标准 CRC16（私有查表 / 或者那 2 字节根本不是校验位）")
        return 1

    print(f"✓ 命中 {len(hits)} 组（最多列 20）：")
    for label, init, rname, endian, poly in hits:
        # 用全部样本复核
        ok = 0
        tables = tab_msb if label == "MSB-first" else tab_lsb
        fn = crc_msb if label == "MSB-first" else crc_lsb
        for f, mlen, be, le in samples:
            data = ranges_of(f, mlen)[rname]
            want = be if endian == "BE" else le
            if int(fn(tables, data, init)[ALL_POLYS == poly][0]) == want:
                ok += 1
        print(f"  {label} poly=0x{poly:04X} init=0x{init:04X} 区间={rname} "
              f"字节序={endian} → 全样本复核 {ok}/{len(samples)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
