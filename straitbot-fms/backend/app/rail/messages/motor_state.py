"""0x0D 获取电机状态 / 0x0E 电机状态主动上发。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_GET_MOTOR, CMD_UPLOAD_MOTOR, MOTOR_ST_IDLE


@dataclass(frozen=True)
class GetMotorRequest(IBoardMsg):
    """0x0D 获取电机状态（1B）。"""

    cmd = CMD_GET_MOTOR
    motor_id: int = 1

    def to_bytes(self) -> bytes:
        return struct.pack(">B", self.motor_id & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "GetMotorRequest":
        if len(payload) != 1:
            raise ValueError(f"0x0D 请求应为 1B，实际 {len(payload)}B")
        return cls(motor_id=payload[0])


@dataclass(frozen=True)
class MotorState(IBoardMsg):
    """0x0D 响应 / 0x0E 主动上发：电机状态（0x0E 无错误码前缀，按文档）。

    文档布局 30B：错误码(2) 电机ID(1) 状态(1) 速度(2) 坐标(4) 状态字(4)
    错误码(4) 电流1(4) 电流2(4) 温度(4)。
    兼容旧仿真器 28B：[状态(1) 电机ID(1) 速度(2) 坐标(4) 状态字 错误码 电流1 电流2 温度]。
    """

    cmd = CMD_UPLOAD_MOTOR
    error_code: int = 0
    motor_id: int = 1
    state: int = MOTOR_ST_IDLE   # 0空闲 1运行 2已到位 3初始化
    speed: int = 0               # 当前速度 mm/s
    coord: int = 0               # 当前坐标(高度) mm
    status_word: int = 0         # 驱动器状态字
    driver_error: int = 0        # 驱动器错误码
    current_1: int = 0           # 电流1 mA
    current_2: int = 0           # 电流2 mA
    temperature: int = 0         # °C

    def to_bytes(self) -> bytes:
        return struct.pack(">HBBhiiiiii",
                           self.error_code & 0xFFFF, self.motor_id & 0xFF,
                           self.state & 0xFF, self.speed, self.coord,
                           self.status_word, self.driver_error,
                           self.current_1, self.current_2, self.temperature)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "MotorState":
        if len(payload) == 30:
            ec, mid, st, spd, coord, sw, de, c1, c2, tmp = \
                struct.unpack(">HBBhiiiiii", payload)
        elif len(payload) == 28:
            # 旧仿真器：[state(1) mode/motor_id(1) speed(2) coord(4) 状态字 错误码 电流1 电流2 温度]
            ec = 0
            st, mid, spd, coord, sw, de, c1, c2, tmp = \
                struct.unpack(">BBhiiiiii", payload)
        else:
            raise ValueError(f"0x0D/0x0E 状态应为 28/30B，实际 {len(payload)}B")
        return cls(error_code=ec, motor_id=mid, state=st, speed=spd, coord=coord,
                   status_word=sw, driver_error=de, current_1=c1, current_2=c2,
                   temperature=tmp)
