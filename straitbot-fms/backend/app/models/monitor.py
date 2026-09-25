"""监控时序模型: 状态/电源/告警/版本/配置快照。"""
from datetime import datetime
from sqlalchemy import Column, Integer, String, Float, Boolean, DateTime, ForeignKey, JSON

from ..database import Base


def now():
    return datetime.utcnow()


class StatusLog(Base):
    __tablename__ = "robot_status_logs"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    ts = Column(DateTime, default=now, index=True)
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
    conn_chassis = Column(Boolean)
    conn_server = Column(Boolean)
    conn_elevator = Column(Boolean)
    raw = Column(JSON)


class PowerLog(Base):
    __tablename__ = "robot_power_logs"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    ts = Column(DateTime, default=now, index=True)
    mode = Column(Integer)
    capacity = Column(Integer)
    voltage = Column(Float)
    current = Column(Float)
    charging = Column(Integer)
    remaining = Column(Integer)


class RobotAlert(Base):
    __tablename__ = "robot_alerts"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    ts = Column(DateTime, default=now, index=True)
    alert_id = Column(Integer, index=True)
    content = Column(String(256))
    level = Column(String(32), index=True)
    params = Column(JSON)


class RobotVersion(Base):
    __tablename__ = "robot_versions"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    ts = Column(DateTime, default=now, index=True)
    application = Column(String(64), index=True)
    firmware = Column(String(64))
    hardware = Column(String(64))
    hardware_sn = Column(String(128))
    motion = Column(String(64))
    sdk = Column(String(64))
    raw = Column(JSON)


class RobotConfigSnapshot(Base):
    __tablename__ = "robot_config_snapshots"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    ts = Column(DateTime, default=now, index=True)
    source = Column(String(16), default="poll")
    operator = Column(String(64), default="")
    config_json = Column(JSON)
