"""0x0F 单色灯控制。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_SINGLE_COLOR_LIGHT


@dataclass(frozen=True)
class SingleColorLightRequest(IBoardMsg):
    """0x0F 单色灯控制（7B）。"""

    cmd = CMD_SINGLE_COLOR_LIGHT
    id: int = 0          # 0-RGB灯带 1-状态灯 2-照明灯
    mode: int = 0        # 0熄灭 1常亮 2闪烁
    interval_ms: int = 0
    rgb: bytes = b"\x00\x00\x00"

    def to_bytes(self) -> bytes:
        rgb = (self.rgb + b"\x00\x00\x00")[:3]
        return struct.pack(">BBH3s", self.id & 0xFF, self.mode & 0xFF,
                           self.interval_ms & 0xFFFF, rgb)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "SingleColorLightRequest":
        if len(payload) != 7:
            raise ValueError(f"0x0F 请求应为 7B，实际 {len(payload)}B")
        i, mode, iv, rgb = struct.unpack(">BBH3s", payload)
        return cls(id=i, mode=mode, interval_ms=iv, rgb=rgb)
