"""0x06 心跳。"""
from __future__ import annotations

from dataclasses import dataclass

from .base import EmptyRequest
from .constants import CMD_HEARTBEAT


@dataclass(frozen=True)
class HeartbeatMsg(EmptyRequest):
    """0x06 心跳（payload 空，响应亦为空）。"""

    cmd = CMD_HEARTBEAT
