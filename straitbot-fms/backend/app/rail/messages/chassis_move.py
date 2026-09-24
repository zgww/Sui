"""0x09 底盘运动控制（挂轨只用 mode/LinearX/TargetX）。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_CHASSIS_MOVE, MOVE_STOP


@dataclass(frozen=True)
class ChassisMove(IBoardMsg):
    """0x09 底盘运动控制（17B）。挂轨机器人：X 即弧长 mm。"""

    cmd = CMD_CHASSIS_MOVE
    mode: int = MOVE_STOP
    linear_x: int = 0    # mm/s
    linear_y: int = 0    # mm/s（轮式）
    angular: int = 0     # 角速度*10（轮式）
    target_x: int = 0    # 目标位置 X，mm
    target_y: int = 0    # mm（轮式）
    target_yaw: int = 0  # 偏航角*10（轮式）

    def to_bytes(self) -> bytes:
        return struct.pack(">BHHHiih",
                           self.mode & 0xFF,
                           max(0, self.linear_x) & 0xFFFF,
                           max(0, self.linear_y) & 0xFFFF,
                           max(0, self.angular) & 0xFFFF,
                           self.target_x, self.target_y, self.target_yaw)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "ChassisMove":
        if len(payload) != 17:
            raise ValueError(f"0x09 请求应为 17B，实际 {len(payload)}B")
        mode, lx, ly, ang, tx, ty, tyaw = struct.unpack(">BHHHiih", payload)
        return cls(mode=mode, linear_x=lx, linear_y=ly, angular=ang,
                   target_x=tx, target_y=ty, target_yaw=tyaw)
