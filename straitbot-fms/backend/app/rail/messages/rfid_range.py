"""0x30 RFID 进入/离开感应范围事件上传。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_RFID_RANGE_EVENT, RFID_EVENT_ENTER


@dataclass(frozen=True)
class RfidRangeEventUpload(IBoardMsg):
    """0x30 刚进入/离开 RFID 感应范围事件上传（13B）。type: 0-enter 1-leave。"""

    cmd = CMD_RFID_RANGE_EVENT
    type: int = RFID_EVENT_ENTER
    rfid: int = 0
    x: int = 0
    speed: int = 0
    x_before_calibrated: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">BHihi", self.type & 0xFF, self.rfid & 0xFFFF,
                           self.x, self.speed, self.x_before_calibrated)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "RfidRangeEventUpload":
        if len(payload) != 13:
            raise ValueError(f"0x30 上传应为 13B，实际 {len(payload)}B")
        t, rfid, x, spd, xb = struct.unpack(">BHihi", payload)
        return cls(type=t, rfid=rfid, x=x, speed=spd, x_before_calibrated=xb)
