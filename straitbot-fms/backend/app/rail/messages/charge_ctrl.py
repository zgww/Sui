"""0x18 充电控制。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_CHARGE_CTRL


@dataclass(frozen=True)
class ChargeControlRequest(IBoardMsg):
    """0x18 充电控制（6B）。控制类型 0停 1启；退出距离 0xFF 表示自动。"""

    cmd = CMD_CHARGE_CTRL
    control_type: int = 1
    pile_index: int = 0
    exit_distance: int = 0  # 0xFF 表示自动
    speed: int = 0          # mm/s

    def to_bytes(self) -> bytes:
        return struct.pack(">BBHH", self.control_type & 0xFF, self.pile_index & 0xFF,
                           self.exit_distance & 0xFFFF, self.speed & 0xFFFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "ChargeControlRequest":
        if len(payload) != 6:
            raise ValueError(f"0x18 请求应为 6B，实际 {len(payload)}B")
        ct, pi, ed, spd = struct.unpack(">BBHH", payload)
        return cls(control_type=ct, pile_index=pi, exit_distance=ed, speed=spd)
