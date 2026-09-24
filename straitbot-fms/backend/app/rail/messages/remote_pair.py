"""0x1B 遥控器配对。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_REMOTE_PAIR


@dataclass(frozen=True)
class RemotePairRequest(IBoardMsg):
    """0x1B 遥控器配对（1B）。"""

    cmd = CMD_REMOTE_PAIR
    address: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">B", self.address & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "RemotePairRequest":
        if len(payload) != 1:
            raise ValueError(f"0x1B 请求应为 1B，实际 {len(payload)}B")
        return cls(address=payload[0])
