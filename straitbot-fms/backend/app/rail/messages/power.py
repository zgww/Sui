"""0x16 获取电源信息 / 0x17 充电状态主动上发。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import EmptyRequest, IBoardMsg
from .constants import CMD_CHARGE_STATE_UPLOAD, CMD_GET_POWER


@dataclass(frozen=True)
class GetPowerRequest(EmptyRequest):
    """0x16 获取电源信息（payload 空）。"""

    cmd = CMD_GET_POWER


@dataclass(frozen=True)
class PowerResponse(IBoardMsg):
    """0x16 响应：电源信息（13B）。电压 10mV、电流 10mA(正充负放)、容量 10mAh、温度 0.1℃。"""

    cmd = CMD_GET_POWER
    error_code: int = 0
    battery_percent: int = 0
    voltage: int = 0
    current: int = 0
    capacity: int = 0
    temperature: int = 0
    contact: int = 0      # 0未对接 1已对接
    charge_state: int = 0 # 0未启动 1前往中 2未找到信号 3已收到信号 4异常 5充电中 6完成

    def to_bytes(self) -> bytes:
        return struct.pack(">HBHhHHBB",
                           self.error_code & 0xFFFF, self.battery_percent & 0xFF,
                           self.voltage, self.current, self.capacity,
                           self.temperature, self.contact & 0xFF,
                           self.charge_state & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "PowerResponse":
        if len(payload) != 13:
            raise ValueError(f"0x16 响应应为 13B，实际 {len(payload)}B")
        ec, bp, v, c, cap, tmp, ct, cs = struct.unpack(">HBHhHHBB", payload)
        return cls(error_code=ec, battery_percent=bp, voltage=v, current=c,
                   capacity=cap, temperature=tmp, contact=ct, charge_state=cs)


@dataclass(frozen=True)
class ChargeStateUpload(IBoardMsg):
    """0x17 充电状态主动上发（11B，无错误码）。

    ⚠️ 单位：文档那行写 mV/mA/mAh/℃，但**真机实测与 0x16 一致**
    （电压 10mV、电流 10mA、容量 10mAh、温度 0.1℃），换算见
    `app/rail/robot.py` 的 P17_*_SCALE。本类只装原始值，不做换算。
    """

    cmd = CMD_CHARGE_STATE_UPLOAD
    battery_percent: int = 0
    voltage: int = 0
    current: int = 0
    capacity: int = 0
    temperature: int = 0
    contact: int = 0
    charge_state: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">BHhHHBB", self.battery_percent & 0xFF,
                           self.voltage, self.current, self.capacity,
                           self.temperature, self.contact & 0xFF,
                           self.charge_state & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "ChargeStateUpload":
        if len(payload) != 11:
            raise ValueError(f"0x17 上传应为 11B，实际 {len(payload)}B")
        bp, v, c, cap, tmp, ct, cs = struct.unpack(">BHhHHBB", payload)
        return cls(battery_percent=bp, voltage=v, current=c, capacity=cap,
                   temperature=tmp, contact=ct, charge_state=cs)
