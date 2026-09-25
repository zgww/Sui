"""0x01 初始化控制板。

字段与《机器人控制板通信协议 V2.0》指令 0x01 的字段表严格一一对应（12 字段 / 26 字节）::

    ID(1) | 方向(1) | 环形轨道(1) | 光电避障(1) | 超声波避障(1) | 低电量阈值(1)
    | XMin(4,i32) | XMax(4,i32) | YMin(4,i32) | YMax(4,i32) | ZMin(2,i16) | ZMax(2,i16)

⚠️ 历史坑：本消息此前把「环形轨道」与「光电避障」**合并成一个字节**（共 11 字段 / 25 字节），
且方向字段被误命名为 ``ring``。真机上按 25 字节下发会让控制板整体错位一字节。
这里已按文档拆开，字段名与前端下位机配置项对齐（见 frontend/src/config/configSchema.ts）：
``director``=轨道方向 · ``is_ring``=环形轨道 · ``track_photo_avoid``=光电避障 ·
``ultrasonic_avoid``=超声波避障 · ``low_battery_threshold``=低电量阈值。

响应：``ErrorResponse``（2 字节错误码）。
"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg, _i32, _i16
from .constants import CMD_INIT

#: payload 固定长度（12 字段 = 1*6 + 4*4 + 2*2 = 26）
INIT_PAYLOAD_LEN = 26

_STRUCT = ">BBBBBBiiiihh"

# 「不设置」哨兵值（与文档取值范围一致：整型最小/最大值表示不限制）
I32_MIN, I32_MAX = -2_147_483_648, 2_147_483_647
I16_MIN, I16_MAX = -32_768, 32_767


@dataclass(frozen=True)
class InitRequest(IBoardMsg):
    """0x01 初始化控制板（26B payload）。"""

    cmd = CMD_INIT
    id: int = 0                     # 控制板 ID
    director: int = 0               # 方向: 0-正向 1-反向
    is_ring: int = 0                # 环形轨道: 0-非 1-是
    track_photo_avoid: int = 0      # 光电避障: 0-关 1-开
    ultrasonic_avoid: int = 0       # 超声波避障: 0-关 1-开
    low_battery_threshold: int = 0  # 低电量阈值 0-100
    x_min: int = I32_MIN
    x_max: int = I32_MAX
    y_min: int = I32_MIN
    y_max: int = I32_MAX
    z_min: int = I16_MIN
    z_max: int = I16_MAX

    def to_bytes(self) -> bytes:
        return struct.pack(
            _STRUCT,
            self.id & 0xFF, self.director & 0xFF, self.is_ring & 0xFF,
            self.track_photo_avoid & 0xFF, self.ultrasonic_avoid & 0xFF,
            self.low_battery_threshold & 0xFF,
            self.x_min, self.x_max, self.y_min, self.y_max,
            self.z_min, self.z_max,
        )

    @classmethod
    def from_bytes(cls, payload: bytes) -> "InitRequest":
        if len(payload) != INIT_PAYLOAD_LEN:
            raise ValueError(f"0x01 请求应为 {INIT_PAYLOAD_LEN}B，实际 {len(payload)}B")
        return cls(
            id=payload[0],
            director=payload[1],
            is_ring=payload[2],
            track_photo_avoid=payload[3],
            ultrasonic_avoid=payload[4],
            low_battery_threshold=payload[5],
            x_min=_i32(payload, 6),
            x_max=_i32(payload, 10),
            y_min=_i32(payload, 14),
            y_max=_i32(payload, 18),
            z_min=_i16(payload, 22),
            z_max=_i16(payload, 24),
        )
