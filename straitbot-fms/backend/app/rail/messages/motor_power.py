"""0x07 电机驱动器电源开关。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_MOTOR_POWER


@dataclass(frozen=True)
class MotorPowerRequest(IBoardMsg):
    """0x07 电机驱动器电源开关：power 0-关 1-开（2B）。"""

    cmd = CMD_MOTOR_POWER
    motor_id: int = 0
    power: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">BB", self.motor_id & 0xFF, self.power & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "MotorPowerRequest":
        if len(payload) != 2:
            raise ValueError(f"0x07 请求应为 2B，实际 {len(payload)}B")
        return cls(motor_id=payload[0], power=payload[1])
