"""0x19 避障事件上传。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_OBSTACLE_EVENT_UPLOAD


@dataclass(frozen=True)
class ObstacleEventUpload(IBoardMsg):
    """0x19 避障状态上传：四个方向 0未触发 1已触发（4B）。"""

    cmd = CMD_OBSTACLE_EVENT_UPLOAD
    forward: int = 0
    backward: int = 0
    extend: int = 0
    retract: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">BBBB", self.forward & 0xFF, self.backward & 0xFF,
                           self.extend & 0xFF, self.retract & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "ObstacleEventUpload":
        if len(payload) != 4:
            raise ValueError(f"0x19 上传应为 4B，实际 {len(payload)}B")
        f, b, e, r = struct.unpack(">BBBB", payload)
        return cls(forward=f, backward=b, extend=e, retract=r)
