"""0x0A 获取底盘状态 / 0x0B 底盘状态主动上发。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import EmptyRequest, IBoardMsg
from .constants import (CHASSIS_IDLE, CMD_GET_CHASSIS, CMD_UPLOAD_CHASSIS,
                        MODE_EMBEDDED)


@dataclass(frozen=True)
class GetChassisRequest(EmptyRequest):
    """0x0A 获取底盘运动状态（payload 空）。"""

    cmd = CMD_GET_CHASSIS


@dataclass(frozen=True)
class ChassisState(IBoardMsg):
    """0x0A 响应 / 0x0B 主动上发：底盘运动状态（X 即挂轨弧长 mm）。

    文档布局（20B）含 2B 错误码前缀；兼容旧仿真器 18B（无错误码，error_code 记为 0）。
    """

    cmd = CMD_UPLOAD_CHASSIS
    error_code: int = 0
    state: int = CHASSIS_IDLE   # 0空闲 1运行 2已到达 3初始化
    mode: int = MODE_EMBEDDED   # 0边界校正 1工程 2嵌入式 3遥控 4导航 5空闲
    x: int = 0                  # 当前 X 坐标（弧长）mm
    y: int = 0                  # mm（轮式）
    yaw: int = 0                # 偏航角*10（轮式）
    linear_x: int = 0           # mm/s
    linear_y: int = 0           # mm/s
    angular: int = 0            # 角速度*10

    def to_bytes(self) -> bytes:
        return struct.pack(">HBBiihhhh",
                           self.error_code & 0xFFFF, self.state & 0xFF,
                           self.mode & 0xFF, self.x, self.y, self.yaw,
                           self.linear_x, self.linear_y, self.angular)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "ChassisState":
        if len(payload) == 20:
            ec, st, md, x, y, yaw, lx, ly, ang = struct.unpack(">HBBiihhhh", payload)
        elif len(payload) == 18:
            # 旧仿真器无错误码前缀
            ec = 0
            st, md, x, y, yaw, lx, ly, ang = struct.unpack(">BBiihhhh", payload)
        else:
            raise ValueError(f"0x0A/0x0B 状态应为 18/20B，实际 {len(payload)}B")
        return cls(error_code=ec, state=st, mode=md, x=x, y=y, yaw=yaw,
                   linear_x=lx, linear_y=ly, angular=ang)
