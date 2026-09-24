"""公共依赖: 取机器人对象、校验归属。"""
from fastapi import Depends, HTTPException
from sqlalchemy.orm import Session
from .database import get_db
from .models import Robot


def get_robot(robot_id: int, db: Session = Depends(get_db)) -> Robot:
    r = db.query(Robot).filter(Robot.id == robot_id).first()
    if not r:
        raise HTTPException(status_code=404, detail="机器人不存在")
    return r
