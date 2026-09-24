"""消息定义层包：每个下位机消息一个文件。

约定：
- base.py        IBoardMsg 接口 + 通用消息（EmptyRequest/ErrorResponse）+ 编解码助手
- constants.py   指令码 / 错误码 / 语义常量
- registry.py    MESSAGE_REGISTRY 注册表 + decode 路由
- 其余文件       按指令码组织的具体消息（请求/响应/上发类）

业务层统一 `from app.rail import messages as m`，通过本包导出访问全部消息类与常量。
"""
from .constants import *  # noqa: F401,F403
from .base import *  # noqa: F401,F403

from .init import InitRequest
from .config import GetConfigRequest, ConfigResponse
from .reboot import RebootRequest
from .version import GetVersionRequest, VersionResponse
from .time_sync import TimeSyncRequest
from .heartbeat import HeartbeatMsg
from .motor_power import MotorPowerRequest
from .chassis_move import ChassisMove
from .chassis_state import GetChassisRequest, ChassisState
from .motor_ctrl import MotorCtrl
from .motor_state import GetMotorRequest, MotorState
from .light import SingleColorLightRequest
from .display import DisplayControlRequest
from .key_state import GetKeyStateRequest, KeyStateResponse
from .obstacle_state import GetObstacleStateRequest, ObstacleStateResponse
from .obstacle_param import SetObstacleParamRequest
from .remote_ctrl import RemoteCtrlUpload
from .power import GetPowerRequest, PowerResponse, ChargeStateUpload
from .charge_ctrl import ChargeControlRequest
from .obstacle_event import ObstacleEventUpload
from .mark_event import HardwareMarkEvent
from .remote_pair import RemotePairRequest
from .log import BoardLogUpload
from .map_tag import MapTag, MapTagQueryRequest, MapTagResponse, LoadMapRequest
from .mapping import (MappingControlRequest, GetMappingProgressRequest,
                      MappingProgressResponse)
from .clear_alert import ClearDriveAlertRequest
from .estop_event import EstopEventUpload
from .latest_rfid import GetLatestRfidRequest, LatestRfidResponse
from .rfid_range import RfidRangeEventUpload

from .registry import (MESSAGE_REGISTRY, ERROR_ONLY_RESPONSE_CMDS,  # noqa: E402,F401
                       OPAQUE_UPLOAD_CMDS, decode)
