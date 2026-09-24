"""系统设置模型。"""
from sqlalchemy import Column, String, Text

from ..database import Base


class Setting(Base):
    __tablename__ = "settings"
    key = Column(String(64), primary_key=True)
    value = Column(Text, default="")
