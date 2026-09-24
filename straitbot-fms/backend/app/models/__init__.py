"""ORM 模型统一导出。

按领域拆分: user / robot / monitor / ota / log / setting / inspection。
所有模型在此统一导出, 外部 `from .models import Robot, User` 不变。
"""
from .user import User
from .robot import Robot, RobotProperty
from .monitor import StatusLog, PowerLog, RobotAlert, RobotVersion, RobotConfigSnapshot
from .ota import OtaPackage, OtaTask
from .log import UploadedLog, FetchedLog
from .setting import Setting
from .inspection import (
    InspectionTask, InspectionRun, InspectionResult,
    InspectionActionResult, InspectionPointResult,
)
from .waypoint import RobotMap, Waypoint, WaypointAction
from .point_binding import PointBinding, ArchiveTaskPoint
from .inspection_plan import InspectionPlan, InspectionPlanPoint, PlanExecution, InspectionRobotLease
from .alarm import Alarm

# 兼容别名(旧代码用 RobotStatusLog/RobotPowerLog)
RobotStatusLog = StatusLog
RobotPowerLog = PowerLog

__all__ = [
    "User", "Robot", "RobotProperty",
    "StatusLog", "RobotStatusLog", "PowerLog", "RobotPowerLog",
    "RobotAlert", "RobotVersion", "RobotConfigSnapshot",
    "OtaPackage", "OtaTask",
    "UploadedLog", "FetchedLog",
    "Setting",
    "InspectionTask", "InspectionRun", "InspectionResult",
    "InspectionActionResult", "InspectionPointResult",
    "RobotMap", "Waypoint", "WaypointAction",
    "PointBinding", "ArchiveTaskPoint",
    "Alarm",
]
