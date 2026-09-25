"""0x05 时间校准。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_TIME_SYNC


@dataclass(frozen=True)
class TimeSyncRequest(IBoardMsg):
    """0x05 时间校准（6B）。年份为后两位（21 代表 2021）。"""

    cmd = CMD_TIME_SYNC
    year: int = 0
    month: int = 1
    day: int = 1
    hour: int = 0
    minute: int = 0
    second: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">BBBBBB", self.year & 0xFF, self.month & 0xFF,
                           self.day & 0xFF, self.hour & 0xFF,
                           self.minute & 0xFF, self.second & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "TimeSyncRequest":
        if len(payload) != 6:
            raise ValueError(f"0x05 请求应为 6B，实际 {len(payload)}B")
        y, mo, d, h, mi, s = struct.unpack(">BBBBBB", payload)
        return cls(year=y, month=mo, day=d, hour=h, minute=mi, second=s)
