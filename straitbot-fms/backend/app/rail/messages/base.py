"""消息基类与通用消息。

- IBoardMsg：所有下位机消息的统一接口，业务层只操作消息对象。
- EmptyRequest：payload 为空的请求帧（心跳等）。
- ErrorResponse：仅含 2 字节错误码的响应帧。
"""
from __future__ import annotations

import struct
from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import ClassVar

from .constants import CMD_HEARTBEAT, CMD_INIT


# ============================================================ 编解码助手
def _u16(b: bytes, o: int = 0) -> int:
    return struct.unpack_from(">H", b, o)[0]


def _i16(b: bytes, o: int = 0) -> int:
    return struct.unpack_from(">h", b, o)[0]


def _i32(b: bytes, o: int = 0) -> int:
    return struct.unpack_from(">i", b, o)[0]


# ============================================================ 消息基类
class IBoardMsg(ABC):
    """下位机消息接口：业务层只操作消息对象，不直接接触字节。

    帧封装（帧头/序号/长度/标记/校验/帧尾）由 protocol.encode_frame/decode_frame
    负责，本接口只处理消息内容（payload）。
    """

    cmd: ClassVar[int]

    @abstractmethod
    def to_bytes(self) -> bytes:
        """序列化为消息内容（payload）字节数组（大端）。"""

    @classmethod
    @abstractmethod
    def from_bytes(cls, payload: bytes) -> "IBoardMsg":
        """从 payload 字节数组反序列化。长度不符抛 ValueError。"""

    def __repr__(self) -> str:  # pragma: no cover - 调试友好
        fields = ", ".join(f"{k}={v}" for k, v in self.__dict__.items())
        return f"{type(self).__name__}({fields})"


# ============================================================ 通用空请求
@dataclass(frozen=True)
class EmptyRequest(IBoardMsg):
    """payload 为空的请求帧。"""

    cmd: ClassVar[int] = CMD_HEARTBEAT

    def to_bytes(self) -> bytes:
        return b""

    @classmethod
    def from_bytes(cls, payload: bytes) -> "EmptyRequest":
        if payload:
            raise ValueError(f"{cls.__name__} 期望空 payload，实际 {len(payload)}B")
        return cls()


# ============================================================ 通用错误响应
@dataclass(frozen=True)
class ErrorResponse(IBoardMsg):
    """仅含 2 字节错误码的响应帧（0x01/0x03/0x05/0x07/0x09/0x0C/0x14/0x18/0x1B/0x22/0x23/0x25 等）。"""

    cmd: ClassVar[int] = CMD_INIT
    error_code: int = 0

    def to_bytes(self) -> bytes:
        return struct.pack(">H", self.error_code & 0xFFFF)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "ErrorResponse":
        if len(payload) != 2:
            raise ValueError(f"错误响应应为 2B，实际 {len(payload)}B")
        return cls(error_code=_u16(payload))


# ============================================================ 文档外的上发帧
@dataclass(frozen=True)
class UnknownUpload(IBoardMsg):
    """协议文档里**没有定义**、但真机固件确实会上发的帧：只保留原始 payload。

    存在的意义是"别让未知上发帧把日志刷爆"：以前 `decode()` 对未注册指令码直接抛
    ValueError，真机连接后立刻上发的 0x35 每连一次就报一条 WARNING。
    拿到含义后应补成正式消息类，并从 `OPAQUE_UPLOAD_CMDS` 里摘掉。
    """

    cmd: int = 0
    payload: bytes = b""

    def to_bytes(self) -> bytes:
        return bytes(self.payload)

    @classmethod
    def from_bytes(cls, payload: bytes) -> "UnknownUpload":
        return cls(payload=bytes(payload))
