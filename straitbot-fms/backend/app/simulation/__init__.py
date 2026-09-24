"""仿真: 协议帧编解码 + TCP/WS 双向桥。"""
from .protocol import (
    FRAME_HEAD, FRAME_TAIL, HEADER_LEN, CRC_LEN, MAX_PAYLOAD,
    crc16_kermit, crc16_ccitt, crc_mismatch_count, ACCEPT_CRC_MISMATCH,
    encode_frame, decode_frame, FrameParser,
    CMD_HEARTBEAT, CMD_INIT, CMD_GET_CONFIG, CMD_REBOOT, CMD_GET_VERSION,
    CMD_TIME_SYNC, CMD_MOTOR_POWER, CMD_CHASSIS_MOVE, CMD_GET_CHASSIS,
    CMD_UPLOAD_CHASSIS, CMD_MOTOR_CTRL, CMD_GET_MOTOR, CMD_UPLOAD_MOTOR,
    CMD_UNSUPPORTED,
)
from .bridge import SimulationBridge, bridge

__all__ = [
    "FRAME_HEAD", "FRAME_TAIL", "HEADER_LEN", "CRC_LEN", "MAX_PAYLOAD",
    "crc16_kermit", "crc16_ccitt", "crc_mismatch_count", "ACCEPT_CRC_MISMATCH",
    "encode_frame", "decode_frame", "FrameParser",
    "CMD_HEARTBEAT", "CMD_INIT", "CMD_GET_CONFIG", "CMD_REBOOT", "CMD_GET_VERSION",
    "CMD_TIME_SYNC", "CMD_MOTOR_POWER", "CMD_CHASSIS_MOVE", "CMD_GET_CHASSIS",
    "CMD_UPLOAD_CHASSIS", "CMD_MOTOR_CTRL", "CMD_GET_MOTOR", "CMD_UPLOAD_MOTOR",
    "CMD_UNSUPPORTED", "SimulationBridge", "bridge",
]
