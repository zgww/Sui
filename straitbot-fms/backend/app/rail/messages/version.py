"""0x04 获取版本/SN：请求 / 响应。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import EmptyRequest, IBoardMsg
from .constants import CMD_GET_VERSION


@dataclass(frozen=True)
class GetVersionRequest(EmptyRequest):
    """0x04 获取软件版本号与 SN（payload 空）。"""

    cmd = CMD_GET_VERSION


@dataclass(frozen=True)
class VersionResponse(IBoardMsg):
    """0x04 响应：错误码 + 软件版本号(3B, 如 V1.10.0→0x010A00) + SN(12B)（17B）。"""

    cmd = CMD_GET_VERSION
    error_code: int = 0
    version: bytes = b"\x00\x00\x00"   # 3B 大端主版本号
    sn: bytes = b""                    # 12B

    def to_bytes(self) -> bytes:
        ver = (self.version + b"\x00\x00\x00")[:3]
        sn = (self.sn + b"\x00" * 12)[:12]
        return struct.pack(">H3s12s", self.error_code & 0xFFFF, ver, sn)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "VersionResponse":
        if len(payload) != 17:
            raise ValueError(f"0x04 响应应为 17B，实际 {len(payload)}B")
        ec, ver, sn = struct.unpack(">H3s12s", payload)
        return cls(error_code=ec, version=ver, sn=sn)
