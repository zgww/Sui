"""日志模型: 上传日志 + 拉取日志。"""
from datetime import datetime
from sqlalchemy import Column, Integer, String, DateTime, ForeignKey

from ..database import Base


def now():
    return datetime.utcnow()


class UploadedLog(Base):
    __tablename__ = "uploaded_logs"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    robot_id_label = Column(String(64), default="")
    filename = Column(String(255))
    stored_path = Column(String(512))
    size = Column(Integer, default=0)
    source = Column(String(32), default="manual")
    created_at = Column(DateTime, default=now, index=True)


class FetchedLog(Base):
    __tablename__ = "fetched_logs"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    remote_path = Column(String(512))
    stored_path = Column(String(512))
    filename = Column(String(255))
    size = Column(Integer, default=0)
    fetched_at = Column(DateTime, default=now, index=True)
    fetched_by = Column(String(64), default="")
