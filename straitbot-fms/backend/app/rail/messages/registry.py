"""消息注册表：cmd → 消息类 + decode 路由。"""
from __future__ import annotations

from typing import Dict, Type

from .base import ErrorResponse, IBoardMsg, UnknownUpload
from .chassis_move import ChassisMove
from .chassis_state import ChassisState
from .charge_ctrl import ChargeControlRequest
from .clear_alert import ClearDriveAlertRequest
from .config import ConfigResponse
from .display import DisplayControlRequest
from .estop_event import EstopEventUpload
from .heartbeat import HeartbeatMsg
from .init import InitRequest
from .key_state import KeyStateResponse
from .latest_rfid import LatestRfidResponse
from .light import SingleColorLightRequest
from .log import BoardLogUpload
from .map_tag import LoadMapRequest, MapTagResponse
from .mapping import MappingControlRequest, MappingProgressResponse
from .mark_event import HardwareMarkEvent
from .motor_ctrl import MotorCtrl
from .motor_power import MotorPowerRequest
from .motor_state import MotorState
from .obstacle_event import ObstacleEventUpload
from .obstacle_param import SetObstacleParamRequest
from .obstacle_state import ObstacleStateResponse
from .power import ChargeStateUpload, PowerResponse
from .reboot import RebootRequest
from .remote_ctrl import RemoteCtrlUpload
from .remote_pair import RemotePairRequest
from .rfid_range import RfidRangeEventUpload
from .time_sync import TimeSyncRequest
from .version import VersionResponse
from .constants import (CMD_BOARD_LOG, CMD_CHARGE_CTRL, CMD_CHARGE_STATE_UPLOAD,
                        CMD_CHASSIS_MOVE, CMD_CLEAR_DRIVE_ALERT, CMD_DISPLAY_CTRL,
                        CMD_ESTOP_EVENT_UPLOAD, CMD_GET_CHASSIS, CMD_GET_CONFIG,
                        CMD_GET_KEY_STATE, CMD_GET_LATEST_RFID, CMD_GET_MAPPING_PROGRESS,
                        CMD_GET_MOTOR, CMD_GET_OBSTACLE_STATE, CMD_GET_POWER,
                        CMD_GET_VERSION, CMD_HARDWARE_MARK_EVENT, CMD_HEARTBEAT,
                        CMD_INIT, CMD_LOAD_MAP, CMD_MAPPING_CTRL, CMD_MAP_TAG_QUERY,
                        CMD_MOTOR_CTRL, CMD_MOTOR_POWER, CMD_OBSTACLE_EVENT_UPLOAD,
                        CMD_REBOOT, CMD_REMOTE_CTRL_UPLOAD, CMD_REMOTE_PAIR,
                        CMD_RFID_RANGE_EVENT, CMD_SET_OBSTACLE_PARAM,
                        CMD_SINGLE_COLOR_LIGHT, CMD_TIME_SYNC, CMD_UPLOAD_CHASSIS,
                        CMD_UPLOAD_MOTOR)

# ============================================================ 注册表：cmd → 消息类
MESSAGE_REGISTRY: Dict[int, Type[IBoardMsg]] = {
    CMD_INIT: InitRequest,
    CMD_GET_CONFIG: ConfigResponse,          # 0x02 响应；请求 GetConfigRequest 同 cmd
    CMD_REBOOT: RebootRequest,
    CMD_GET_VERSION: VersionResponse,        # 0x04 响应
    CMD_TIME_SYNC: TimeSyncRequest,
    CMD_HEARTBEAT: HeartbeatMsg,
    CMD_MOTOR_POWER: MotorPowerRequest,
    CMD_CHASSIS_MOVE: ChassisMove,
    CMD_GET_CHASSIS: ChassisState,           # 0x0A 响应（与 0x0B 同布局）
    CMD_UPLOAD_CHASSIS: ChassisState,
    CMD_MOTOR_CTRL: MotorCtrl,
    CMD_GET_MOTOR: MotorState,               # 0x0D 响应（与 0x0E 同布局）
    CMD_UPLOAD_MOTOR: MotorState,
    CMD_SINGLE_COLOR_LIGHT: SingleColorLightRequest,
    CMD_DISPLAY_CTRL: DisplayControlRequest,
    CMD_GET_KEY_STATE: KeyStateResponse,
    CMD_GET_OBSTACLE_STATE: ObstacleStateResponse,
    CMD_SET_OBSTACLE_PARAM: SetObstacleParamRequest,
    CMD_REMOTE_CTRL_UPLOAD: RemoteCtrlUpload,
    CMD_GET_POWER: PowerResponse,
    CMD_CHARGE_STATE_UPLOAD: ChargeStateUpload,
    CMD_CHARGE_CTRL: ChargeControlRequest,
    CMD_OBSTACLE_EVENT_UPLOAD: ObstacleEventUpload,
    CMD_HARDWARE_MARK_EVENT: HardwareMarkEvent,
    CMD_REMOTE_PAIR: RemotePairRequest,
    CMD_BOARD_LOG: BoardLogUpload,
    CMD_MAP_TAG_QUERY: MapTagResponse,
    CMD_LOAD_MAP: LoadMapRequest,
    CMD_MAPPING_CTRL: MappingControlRequest,
    CMD_GET_MAPPING_PROGRESS: MappingProgressResponse,
    CMD_CLEAR_DRIVE_ALERT: ClearDriveAlertRequest,
    CMD_ESTOP_EVENT_UPLOAD: EstopEventUpload,
    CMD_GET_LATEST_RFID: LatestRfidResponse,
    CMD_RFID_RANGE_EVENT: RfidRangeEventUpload,
}

# 这些指令的响应帧仅含 2B 错误码；上位机收到的都是响应，统一按 ErrorResponse 解析
ERROR_ONLY_RESPONSE_CMDS = {
    CMD_INIT, CMD_REBOOT, CMD_TIME_SYNC, CMD_MOTOR_POWER, CMD_CHASSIS_MOVE,
    CMD_MOTOR_CTRL, CMD_SET_OBSTACLE_PARAM, CMD_CHARGE_CTRL, CMD_REMOTE_PAIR,
    CMD_LOAD_MAP, CMD_MAPPING_CTRL, CMD_CLEAR_DRIVE_ALERT,
}

# 协议文档里**没有定义**、但真机固件会上发的指令码 → 保留原始 payload，不报错。
# 0x35：连接建立后立刻上发一帧，payload 5B（实测 08 00 02 00 00），含义待固件方确认。
OPAQUE_UPLOAD_CMDS = frozenset({0x35})


def decode(cmd: int, payload: bytes) -> IBoardMsg:
    """按指令码反序列化为消息对象（面向"收到的帧"：响应/上发）。未注册指令抛 ValueError。"""
    if cmd in ERROR_ONLY_RESPONSE_CMDS:
        return ErrorResponse.from_bytes(payload)
    if cmd in OPAQUE_UPLOAD_CMDS:
        return UnknownUpload(cmd=cmd, payload=bytes(payload))
    cls = MESSAGE_REGISTRY.get(cmd)
    if cls is None:
        raise ValueError(f"未注册的指令码 0x{cmd:02X}")
    return cls.from_bytes(payload)
