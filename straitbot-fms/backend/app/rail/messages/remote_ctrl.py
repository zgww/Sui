"""0x15 遥控器（手柄）状态变化上传。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_REMOTE_CTRL_UPLOAD


@dataclass(frozen=True)
class RemoteCtrlUpload(IBoardMsg):
    """0x15 遥控器状态变化上传（3B）。"""

    cmd = CMD_REMOTE_CTRL_UPLOAD
    connected: int = 0  # 0未连接 1已连接
    keys: int = 0       # 16bit 按键位图

    def to_bytes(self) -> bytes:
        return struct.pack(">BH", self.connected & 0xFF, self.keys & 0xFFFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "RemoteCtrlUpload":
        if len(payload) != 3:
            raise ValueError(f"0x15 上传应为 3B，实际 {len(payload)}B")
        conn, keys = struct.unpack(">BH", payload)
        return cls(connected=conn, keys=keys)
