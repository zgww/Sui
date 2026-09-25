"""0x1A 硬件标记事件上传（磁钉 / RFID / 末端限位）。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_HARDWARE_MARK_EVENT, MARK_MAGNET


@dataclass(frozen=True)
class HardwareMarkEvent(IBoardMsg):
    """0x1A 硬件标记触发事件上传（9B 固定头 + 附加）。

    extra：磁钉 0 字节；RFID 8 字节（附加）。
    """

    cmd = CMD_HARDWARE_MARK_EVENT
    mark_type: int = MARK_MAGNET   # 1磁钉 2RFID 0xFF末端限位
    index: int = 0                 # 同类型标记中的序号
    x: int = 0                     # 当前坐标 mm
    speed: int = 0                 # 当前速度 mm/s
    extra: bytes = b""

    def to_bytes(self) -> bytes:
        return struct.pack(">BHih", self.mark_type & 0xFF, self.index & 0xFFFF,
                           self.x, self.speed) + bytes(self.extra)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "HardwareMarkEvent":
        if len(payload) < 9:
            raise ValueError(f"0x1A 上传至少 9B，实际 {len(payload)}B")
        mt, idx, x, spd = struct.unpack(">BHih", payload[:9])
        return cls(mark_type=mt, index=idx, x=x, speed=spd, extra=payload[9:])
