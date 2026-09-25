"""机器人模型: Robot(连接信息) + RobotProperty(物模型快照)。"""
from datetime import datetime
from sqlalchemy import Column, Integer, String, Float, Boolean, DateTime, ForeignKey, JSON, Text
from sqlalchemy.orm import relationship

from ..database import Base


class Robot(Base):
    """机器人连接信息 + 配置。"""
    __tablename__ = "robots"
    id = Column(Integer, primary_key=True)
    name = Column(String(128), nullable=False)
    robot_id = Column(Integer, default=1, comment="机器人本体 ID(X-ROBOT_ID)")
    ip = Column(String(64), nullable=False)
    api_port = Column(Integer, default=6002)
    product_type = Column(String(32), default="")
    ssh_user = Column(String(64), default="nav")
    ssh_pass = Column(String(128), default="nav2022")
    ssh_port = Column(Integer, default=22)
    log_dir = Column(String(256), default="/home/nav/robot/robot/filelog")
    install_dir = Column(String(256), default="/home/nav/robot")
    version_file = Column(String(256), default="/home/nav/robot/robot/version")
    poll_status = Column(Boolean, default=True)
    poll_meta = Column(Boolean, default=True)
    log_retention_days = Column(Integer, default=30)
    enabled = Column(Boolean, default=True)
    note = Column(String(256), default="")
    # 视频流(ZLMediaKit): FMS 只配置 + 代理信令, 不自建流媒体
    video_server = Column(String(256), default="", comment="ZLMediaKit 地址, 如 http://192.168.6.54")
    video_secret = Column(String(256), default="", comment="ZLMediaKit secret, 用于 API 鉴权")
    video_visible_stream = Column(String(256), default="", comment="可见光流标识 app/stream, 如 live/robot-109")
    video_thermal_stream = Column(String(256), default="", comment="红外/热成像流标识")
    video_protocol = Column(String(16), default="webrtc", comment="播放协议 webrtc|flv|hls")
    video_use_robot_ip = Column(Boolean, default=False, comment="是否用机器人 IP 末段拼接流名")
    created_at = Column(DateTime, default=datetime.utcnow)
    updated_at = Column(DateTime, default=datetime.utcnow, onupdate=datetime.utcnow)

    # 关联
    property = relationship("RobotProperty", uselist=False, back_populates="robot",
                            cascade="all, delete-orphan")


class RobotProperty(Base):
    """物模型最新快照 — 每机器人一行。由 accessor 维护。"""
    __tablename__ = "robot_properties"
    robot_pk = Column(Integer, ForeignKey("robots.id"), primary_key=True)
    # identity
    sn = Column(String(128))
    product_type = Column(Integer)
    # version
    app_version = Column(String(64))
    fw_version = Column(String(64))
    hw_version = Column(String(64))
    motion_version = Column(String(64))
    sdk_version = Column(String(64))
    # runtime
    status = Column(Integer)
    doing = Column(String(128))
    cpu = Column(Float)
    temperature = Column(Float)
    speed = Column(Float)
    angular_speed = Column(Float)
    battery = Column(Integer)
    pose_x = Column(Float)
    pose_y = Column(Float)
    theta = Column(Float)
    floor = Column(Integer)
    # power
    power_mode = Column(Integer)
    voltage = Column(Float)
    current = Column(Float)
    capacity = Column(Integer)
    remaining = Column(Integer)
    charging = Column(Integer)
    # connections
    conn_chassis = Column(Boolean)
    conn_server = Column(Boolean)
    conn_elevator = Column(Boolean)
    # ptz
    ptz_pan = Column(Float)
    ptz_tilt = Column(Float)
    ptz_zoom = Column(Float)
    # meta
    last_seen = Column(DateTime)
    updated_at = Column(DateTime)

    robot = relationship("Robot", back_populates="property")
