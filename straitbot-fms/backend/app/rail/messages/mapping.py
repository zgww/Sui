"""0x23 建图控制 / 0x24 建图进度。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import EmptyRequest, IBoardMsg
from .constants import CMD_GET_MAPPING_PROGRESS, CMD_MAPPING_CTRL


@dataclass(frozen=True)
class MappingControlRequest(IBoardMsg):
    """0x23 建图控制：0中断 1全程 2部分（9B）。"""

    cmd = CMD_MAPPING_CTRL
    control_type: int = 0
    x_start: int = 0
    x_end: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">Bii", self.control_type & 0xFF, self.x_start, self.x_end)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "MappingControlRequest":
        if len(payload) != 9:
            raise ValueError(f"0x23 请求应为 9B，实际 {len(payload)}B")
        ct, xs, xe = struct.unpack(">Bii", payload)
        return cls(control_type=ct, x_start=xs, x_end=xe)


@dataclass(frozen=True)
class GetMappingProgressRequest(EmptyRequest):
    """0x24 获取建图进度（payload 空）。"""

    cmd = CMD_GET_MAPPING_PROGRESS


@dataclass(frozen=True)
class MappingProgressResponse(IBoardMsg):
    """0x24 响应：建图进度（3B）。"""

    cmd = CMD_GET_MAPPING_PROGRESS
    error_code: int = 0
    progress: int = 0  # 0未开始 1建图中

    def to_bytes(self) -> bytes:
        return struct.pack(">HB", self.error_code & 0xFFFF, self.progress & 0xFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "MappingProgressResponse":
        if len(payload) != 3:
            raise ValueError(f"0x24 响应应为 3B，实际 {len(payload)}B")
        ec, pr = struct.unpack(">HB", payload)
        return cls(error_code=ec, progress=pr)
