"""0x02 获取配置：请求 / 响应。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import EmptyRequest, IBoardMsg
from .constants import CMD_GET_CONFIG


@dataclass(frozen=True)
class GetConfigRequest(EmptyRequest):
    """0x02 获取配置（payload 空）。"""

    cmd = CMD_GET_CONFIG


@dataclass(frozen=True)
class ConfigResponse(IBoardMsg):
    """0x02 响应：错误码 + 移动限速 + 伸缩限速 + 伸缩杆限高最小/最大（10B）。"""

    cmd = CMD_GET_CONFIG
    error_code: int = 0
    move_limit: int = 0       # mm/s, UInt16Min 表示未设置
    lift_limit: int = 0       # mm/s
    lift_min: int = 0         # mm
    lift_max: int = 0         # mm

    def to_bytes(self) -> bytes:
        return struct.pack(">HHHHH",
                           self.error_code & 0xFFFF, self.move_limit & 0xFFFF,
                           self.lift_limit & 0xFFFF, self.lift_min & 0xFFFF,
                           self.lift_max & 0xFFFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "ConfigResponse":
        if len(payload) != 10:
            raise ValueError(f"0x02 响应应为 10B，实际 {len(payload)}B")
        ec, mv, lf, mn, mx = struct.unpack(">HHHHH", payload)
        return cls(error_code=ec, move_limit=mv, lift_limit=lf, lift_min=mn, lift_max=mx)
