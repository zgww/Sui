"""0x21 地图标签查询 / 0x22 加载地图。"""
from __future__ import annotations

import struct
from dataclasses import dataclass, field

from .base import IBoardMsg
from .constants import CMD_LOAD_MAP, CMD_MAP_TAG_QUERY, MARK_MAGNET, MARK_RFID


@dataclass(frozen=True)
class MapTag:
    """地图标签（磁钉/RFID）。"""

    tag_type: int = 0      # 1磁钉 2RFID（修订后支持位运算组合）
    index: int = 0
    x: int = 0             # 标签坐标 mm
    range: int = 0         # 感应范围
    extra: bytes = b""     # 磁钉 0B / RFID 8B

    def to_bytes(self) -> bytes:
        return struct.pack(">BHih", self.tag_type & 0xFF, self.index & 0xFFFF,
                           self.x, self.range) + bytes(self.extra)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "MapTag":
        if len(payload) < 9:
            raise ValueError(f"标签至少 9B，实际 {len(payload)}B")
        t, idx, x, rng = struct.unpack(">BHih", payload[:9])
        # 附加长度：磁钉 0B / RFID 8B（0x21 修订后类型可为位运算组合）
        extra_len = 8 if (t & MARK_RFID) else (0 if (t & MARK_MAGNET) else len(payload) - 9)
        extra = payload[9:9 + extra_len]
        return cls(tag_type=t, index=idx, x=x, range=rng, extra=extra)


@dataclass(frozen=True)
class MapTagQueryRequest(IBoardMsg):
    """0x21 分页查询地图标签（2B）。"""

    cmd = CMD_MAP_TAG_QUERY
    page: int = 0          # 分页序号，从 0 开始
    tag_type: int = 0      # 0全部 1磁钉 2RFID（可位运算）

    def to_bytes(self) -> bytes:
        return struct.pack(">BB", self.page & 0xFF, self.tag_type & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "MapTagQueryRequest":
        if len(payload) != 2:
            raise ValueError(f"0x21 请求应为 2B，实际 {len(payload)}B")
        return cls(page=payload[0], tag_type=payload[1])


@dataclass(frozen=True)
class MapTagResponse(IBoardMsg):
    """0x21 响应：分页标签列表。count < 10 且 error=0 表示取完。"""

    cmd = CMD_MAP_TAG_QUERY
    error_code: int = 0
    total: int = 0
    count: int = 0
    tags: list = field(default_factory=list)

    def to_bytes(self) -> bytes:
        head = struct.pack(">HHB", self.error_code & 0xFFFF, self.total & 0xFFFF,
                           len(self.tags) & 0xFF)
        return head + b"".join(t.to_bytes() for t in self.tags)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "MapTagResponse":
        if len(payload) < 5:
            raise ValueError(f"0x21 响应至少 5B，实际 {len(payload)}B")
        ec, total, count = struct.unpack(">HHB", payload[:5])
        tags, off = [], 5
        for _ in range(count):
            if off >= len(payload):
                raise ValueError("0x21 标签数据不足")
            tag = MapTag.from_bytes(payload[off:])
            tags.append(tag)
            off += 9 + len(tag.extra)
        return cls(error_code=ec, total=total, count=count, tags=tags)


@dataclass(frozen=True)
class LoadMapRequest(IBoardMsg):
    """0x22 分批下载地图标签。标签固定 15B。"""

    cmd = CMD_LOAD_MAP
    page: int = 0
    total: int = 0
    count: int = 0
    tags: list = field(default_factory=list)  # MapTag 列表

    def to_bytes(self) -> bytes:
        return struct.pack(">BHB", self.page & 0xFF, self.total & 0xFFFF,
                           len(self.tags) & 0xFF) + b"".join(
            self._pad15(t) for t in self.tags)

    @staticmethod
    def _pad15(t: MapTag) -> bytes:
        raw = t.to_bytes()
        return (raw + b"\x00" * 15)[:15]

    @classmethod
    def from_bytes(cls, payload: bytes) -> "LoadMapRequest":
        if len(payload) < 4:
            raise ValueError(f"0x22 请求至少 4B，实际 {len(payload)}B")
        page, total, count = struct.unpack(">BHB", payload[:4])
        tags = []
        off = 4
        for _ in range(count):
            if off + 15 > len(payload):
                raise ValueError("0x22 标签数据不足")
            tags.append(MapTag.from_bytes(payload[off:off + 15]))
            off += 15
        return cls(page=page, total=total, count=count, tags=tags)
