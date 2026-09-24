"""0x14 设置避障参数。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_SET_OBSTACLE_PARAM


@dataclass(frozen=True)
class SetObstacleParamRequest(IBoardMsg):
    """0x14 设置避障参数（6B）。"""

    cmd = CMD_SET_OBSTACLE_PARAM
    set_type: int = 0      # 0关 1开 2设置距离
    sensor_type: int = 0   # 0距离检测 1防撞条 2防跌落 3急停
    sensor_index: int = 0
    level: int = 0         # 0无 1远 2近 3已碰撞
    distance: int = 0      # mm

    def to_bytes(self) -> bytes:
        return struct.pack(">BBBBH", self.set_type & 0xFF, self.sensor_type & 0xFF,
                           self.sensor_index & 0xFF, self.level & 0xFF,
                           self.distance & 0xFFFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "SetObstacleParamRequest":
        if len(payload) != 6:
            raise ValueError(f"0x14 请求应为 6B，实际 {len(payload)}B")
        st, snt, si, lv, d = struct.unpack(">BBBBH", payload)
        return cls(set_type=st, sensor_type=snt, sensor_index=si, level=lv, distance=d)
