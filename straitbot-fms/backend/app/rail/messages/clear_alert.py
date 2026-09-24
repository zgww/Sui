"""0x25 清除驱动器告警。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_CLEAR_DRIVE_ALERT


@dataclass(frozen=True)
class ClearDriveAlertRequest(IBoardMsg):
    """0x25 清除驱动器告警（1B）。"""

    cmd = CMD_CLEAR_DRIVE_ALERT
    drive_id: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">B", self.drive_id & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "ClearDriveAlertRequest":
        if len(payload) != 1:
            raise ValueError(f"0x25 请求应为 1B，实际 {len(payload)}B")
        return cls(drive_id=payload[0])
