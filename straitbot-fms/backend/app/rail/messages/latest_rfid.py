"""0x29 最近 RFID 信息。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import EmptyRequest, IBoardMsg
from .constants import CMD_GET_LATEST_RFID


@dataclass(frozen=True)
class GetLatestRfidRequest(EmptyRequest):
    """0x29 获取最近一次触发的 RFID 信息（payload 空）。"""

    cmd = CMD_GET_LATEST_RFID


@dataclass(frozen=True)
class LatestRfidResponse(IBoardMsg):
    """0x29 响应：最近触发的一次 RFID 信息（10B，无错误码，按文档）。"""

    cmd = CMD_GET_LATEST_RFID
    rfid: int = 0
    x: int = 0
    range: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">Hii", self.rfid & 0xFFFF, self.x, self.range)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "LatestRfidResponse":
        if len(payload) != 10:
            raise ValueError(f"0x29 响应应为 10B，实际 {len(payload)}B")
        rfid, x, rng = struct.unpack(">Hii", payload)
        return cls(rfid=rfid, x=x, range=rng)
