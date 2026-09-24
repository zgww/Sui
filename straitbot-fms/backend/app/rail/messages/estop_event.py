"""0x26 急停事件上传。"""
from __future__ import annotations

from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_ESTOP_EVENT_UPLOAD


@dataclass(frozen=True)
class EstopEventUpload(IBoardMsg):
    """0x26 急停事件上传（文档未定义明细字段，保留原始 payload 供上层解析）。"""

    cmd = CMD_ESTOP_EVENT_UPLOAD
    raw: bytes = b""

    def to_bytes(self) -> bytes:
        return bytes(self.raw)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "EstopEventUpload":
        return cls(raw=payload)
