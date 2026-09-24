"""0x13 避障状态：请求 / 响应。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import EmptyRequest, IBoardMsg
from .constants import CMD_GET_OBSTACLE_STATE


@dataclass(frozen=True)
class GetObstacleStateRequest(EmptyRequest):
    """0x13 获取避障状态（payload 空）。"""

    cmd = CMD_GET_OBSTACLE_STATE


@dataclass(frozen=True)
class ObstacleStateResponse(IBoardMsg):
    """0x13 响应：防碰撞(每4bit一传感器) 防撞条 防跌落 急停状态（11B）。"""

    cmd = CMD_GET_OBSTACLE_STATE
    error_code: int = 0
    ultrasonic: int = 0   # 4B：每 4bit 一个传感器 0无 1远 2近 3碰撞
    bumper: int = 0       # 2B：每 4bit 一个 0未碰 1已碰
    drop: int = 0         # 2B
    estop: int = 0        # 1B：Bit0-3 硬急停 Bit4-7 软急停

    def to_bytes(self) -> bytes:
        return struct.pack(">HiHHB", self.error_code & 0xFFFF,
                           self.ultrasonic, self.bumper & 0xFFFF,
                           self.drop & 0xFFFF, self.estop & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "ObstacleStateResponse":
        if len(payload) != 11:
            raise ValueError(f"0x13 响应应为 11B，实际 {len(payload)}B")
        ec, us, bm, dr, es = struct.unpack(">HiHHB", payload)
        return cls(error_code=ec, ultrasonic=us, bumper=bm, drop=dr, estop=es)
