"""Pydantic 入参/出参模型。"""
from datetime import datetime
from typing import Any, Optional, List
from pydantic import BaseModel, Field


# ---------- 通用 ----------
class Ok(BaseModel):
    ok: bool = True
    msg: str = "ok"


# ---------- 鉴权 ----------
class LoginIn(BaseModel):
    username: str
    password: str


class TokenOut(BaseModel):
    access_token: str
    token_type: str = "bearer"
    role: str
    username: str


class UserOut(BaseModel):
    id: int
    username: str
    role: str
    enabled: bool


# ---------- 机器人 ----------
class RobotIn(BaseModel):
    name: str
    robot_id: int = 1
    ip: str
    api_port: int = 6002
    product_type: str = ""
    ssh_user: str = "nav"
    ssh_pass: str = "nav2022"
    ssh_port: int = 22
    log_dir: str = "/home/nav/robot/robot/filelog"
    install_dir: str = "/home/nav/robot"
    version_file: str = "/home/nav/robot/robot/version"
    poll_status: bool = True
    poll_meta: bool = True
    log_retention_days: int = 30
    enabled: bool = True
    note: str = ""
    # 视频流配置(ZLMediaKit)
    video_server: str = ""
    video_secret: str = ""
    video_visible_stream: str = ""
    video_thermal_stream: str = ""
    video_protocol: str = "webrtc"
    video_use_robot_ip: bool = False


class RobotOut(RobotIn):
    id: int
    created_at: Optional[datetime] = None
    updated_at: Optional[datetime] = None
    # 最新快照(列表接口回填)
    last_status: Optional[Any] = None
    last_battery: Optional[int] = None
    last_version: Optional[str] = None
    last_seen: Optional[datetime] = None
    online: Optional[bool] = None

    class Config:
        from_attributes = True


# ---------- 监控 ----------
class StatusPoint(BaseModel):
    ts: datetime
    battery: Optional[int] = None
    cpu: Optional[float] = None
    temperature: Optional[float] = None
    speed: Optional[float] = None
    status: Optional[int] = None
    doing: Optional[str] = None


class AlertOut(BaseModel):
    id: int
    ts: datetime
    alert_id: Optional[int]
    content: Optional[str]
    level: Optional[str]


# ---------- OTA ----------
class OtaPackageOut(BaseModel):
    id: int
    filename: str
    version: str
    product_type: str
    channel: str
    size: int
    md5: str
    notes: str
    force_flag: bool
    created_at: datetime
    created_by: str

    class Config:
        from_attributes = True


class OtaTaskCreate(BaseModel):
    robot_ids: List[int]
    package_id: int
    force: bool = False


class OtaTaskOut(BaseModel):
    id: int
    robot_pk: int
    package_id: Optional[int]
    package_filename: str
    from_version: str
    to_version: str
    force: bool
    status: str
    log: str
    started_at: Optional[datetime]
    finished_at: Optional[datetime]
    created_at: datetime
    created_by: str

    class Config:
        from_attributes = True


# ---------- 日志 ----------
class LogEntry(BaseModel):
    name: str
    size: int
    modify_time: str
    is_dir: bool = False


class FetchLogIn(BaseModel):
    files: List[str]   # 远端文件名/相对路径


class UploadLogMeta(BaseModel):
    robot_id: int
    source: str = "manual"


# ---------- 指令 / 参数配置 ----------
class CmdIn(BaseModel):
    cmd: int
    data: dict = Field(default_factory=dict)


class CmdOut(BaseModel):
    ok: bool
    raw: Any = None
    msg: str = ""
