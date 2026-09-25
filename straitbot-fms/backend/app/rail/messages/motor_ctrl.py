"""0x0C 伸缩杆电机控制。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_MOTOR_CTRL, MOTOR_STOP


@dataclass(frozen=True)
class MotorCtrl(IBoardMsg):
    """0x0C 伸缩杆控制（8B）。电机 ID 语义随机型定义（挂轨约定 1=伸缩杆）。"""

    cmd = CMD_MOTOR_CTRL
    motor_id: int = 1
    mode: int = MOTOR_STOP   # 0停 1正转 2反转 3指定坐标 4复位 6设速度
    speed: int = 0           # mm/s
    coord: int = 0           # mm

    def to_bytes(self) -> bytes:
        return struct.pack(">BBhi", self.motor_id & 0xFF, self.mode & 0xFF,
                           self.speed, self.coord)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "MotorCtrl":
        if len(payload) != 8:
            raise ValueError(f"0x0C 请求应为 8B，实际 {len(payload)}B")
        mid, mode, spd, coord = struct.unpack(">BBhi", payload)
        return cls(motor_id=mid, mode=mode, speed=spd, coord=coord)
