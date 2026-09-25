"""0x11 按键状态：请求 / 响应。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import EmptyRequest, IBoardMsg
from .constants import CMD_GET_KEY_STATE


@dataclass(frozen=True)
class GetKeyStateRequest(EmptyRequest):
    """0x11 获取按键状态（payload 空）。"""

    cmd = CMD_GET_KEY_STATE


@dataclass(frozen=True)
class KeyStateResponse(IBoardMsg):
    """0x11 响应：启动/停止按钮。-1 位置错误 0 释放 1 按下（4B）。"""

    cmd = CMD_GET_KEY_STATE
    error_code: int = 0
    start_button: int = 0
    stop_button: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">Hbb", self.error_code & 0xFFFF,
                           self.start_button, self.stop_button)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "KeyStateResponse":
        if len(payload) != 4:
            raise ValueError(f"0x11 响应应为 4B，实际 {len(payload)}B")
        ec, st, sp = struct.unpack(">Hbb", payload)
        return cls(error_code=ec, start_button=st, stop_button=sp)
