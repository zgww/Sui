"""用户模型。"""
from datetime import datetime
from sqlalchemy import Column, Integer, String, Boolean, DateTime

from ..database import Base


class User(Base):
    __tablename__ = "users"
    id = Column(Integer, primary_key=True)
    username = Column(String(64), unique=True, index=True, nullable=False)
    pwd_hash = Column(String(255), nullable=False)
    role = Column(String(32), nullable=False, default="operator")
    enabled = Column(Boolean, default=True)
    created_at = Column(DateTime, default=datetime.utcnow)
