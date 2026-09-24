"""OTA 模型: 安装包 + 升级任务。"""
from datetime import datetime
from sqlalchemy import Column, Integer, String, Boolean, Text, DateTime, ForeignKey

from ..database import Base


def now():
    return datetime.utcnow()


class OtaPackage(Base):
    __tablename__ = "ota_packages"
    id = Column(Integer, primary_key=True)
    filename = Column(String(255), nullable=False)
    version = Column(String(64), default="", index=True)
    product_type = Column(String(32), default="", index=True)
    channel = Column(String(32), default="upper")
    size = Column(Integer, default=0)
    md5 = Column(String(64), default="")
    notes = Column(Text, default="")
    force_flag = Column(Boolean, default=False)
    created_at = Column(DateTime, default=now, index=True)
    created_by = Column(String(64), default="")


class OtaTask(Base):
    __tablename__ = "ota_tasks"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    package_id = Column(Integer, ForeignKey("ota_packages.id"))
    package_filename = Column(String(255))
    from_version = Column(String(64), default="")
    to_version = Column(String(64), default="")
    force = Column(Boolean, default=False)
    status = Column(String(32), default="pending", index=True)
    log = Column(Text, default="")
    started_at = Column(DateTime)
    finished_at = Column(DateTime)
    created_at = Column(DateTime, default=now, index=True)
    created_by = Column(String(64), default="")
