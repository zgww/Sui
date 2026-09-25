"""0x20 下位机日志上发。"""
from __future__ import annotations

import struct
from dataclasses import dataclass

from .base import IBoardMsg
from .constants import CMD_BOARD_LOG


@dataclass(frozen=True)
class BoardLogUpload(IBoardMsg):
    """0x20 下位机日志上发（1B 等级 + 变长内容）。

    等级>2 且内容为 [$code]:$content 格式时产生告警（协议约定）。
    """

    cmd = CMD_BOARD_LOG
    level: int = 0   # 0Debug 1Info 2Warning 3Error 4Fatal
    content: bytes = b""

    def to_bytes(self) -> bytes:
        return struct.pack(">B", self.level & 0xFF) + bytes(self.content)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "BoardLogUpload":
        if not payload:
            raise ValueError("0x20 上传至少 1B")
        return cls(level=payload[0], content=payload[1:])

    @property
    def text(self) -> str:
        try:
            return self.content.decode("utf-8", "replace")
        except Exception:
            return ""
