"""0x03 重启控制板。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_REBOOT


@dataclass(frozen=True)
class RebootRequest(IBoardMsg):
    """0x03 重启控制板：0-重启 1-休眠（1B payload）。"""

    cmd = CMD_REBOOT
    command: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">B", self.command & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "RebootRequest":
        if len(payload) != 1:
            raise ValueError(f"0x03 请求应为 1B，实际 {len(payload)}B")
        return cls(command=payload[0])
