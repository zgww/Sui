"""0x10 显示屏控制。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_DISPLAY_CTRL


@dataclass(frozen=True)
class DisplayControlRequest(IBoardMsg):
    """0x10 显示屏控制（23B）。"""

    cmd = CMD_DISPLAY_CTRL
    y: int = 0
    x: int = 0
    content: bytes = b""   # 20B
    state: int = 0         # 0 显示电源信息 1 显示下发数据

    def to_bytes(self) -> bytes:
        content = (self.content + b"\x00" * 20)[:20]
        return struct.pack(">BB20sB", self.y & 0xFF, self.x & 0xFF, content,
                           self.state & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "DisplayControlRequest":
        if len(payload) != 23:
            raise ValueError(f"0x10 请求应为 23B，实际 {len(payload)}B")
        y, x, content, st = struct.unpack(">BB20sB", payload)
        return cls(y=y, x=x, content=content, state=st)
