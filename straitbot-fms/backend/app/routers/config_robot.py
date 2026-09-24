"""机器人参数配置: cmd=4 读 / cmd=5 写。写时存快照。engineer 专用。"""
import json
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session
from typing import Any
from ..database import get_db
from ..models import Robot, RobotConfigSnapshot
from ..schemas import Ok
from ..auth import engineer_only
from ..services import robot_api

router = APIRouter(prefix="/api/robot_config", tags=["robot_config"])


@router.get("/{rid}")
def read_config(rid: int, db: Session = Depends(get_db), _=Depends(engineer_only)):
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    try:
        cfg = robot_api.get_config(r.ip, r.api_port, r.robot_id)
        return {"ok": True, "config": cfg}
    except robot_api.RobotAPIError as e:
        return {"ok": False, "msg": f"读取失败 code={e.code} {e.msg}", "config": e.data}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "msg": str(e), "config": None}


@router.post("/{rid}")
def write_config(rid: int, payload: dict, db: Session = Depends(get_db), user=Depends(engineer_only)):
    """部分更新。仅允许写: move_speed/angular_speed/is_ring/battery/home_pose/
    inplace_tolerance/limit_position。"""
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    allowed = {
        "limit_position", "is_ring", "move_speed", "angular_speed",
        "inplace_tolerance", "battery", "home_pose", "realtime_thermal",
        "director", "ptz", "with_lift", "lift_limit", "lift_speed",
        "elevator", "enable_obstacle_light", "enable_obstacle_sound",
        "obstacle_cancel_inspection_sec", "server", "oss", "board_addr",
        "log", "bt_trace", "groot", "reboot_config",
    }
    filtered = {k: v for k, v in payload.items() if k in allowed}
    if not filtered:
        return Ok(ok=False, msg="没有可写入的字段")
    try:
        robot_api.set_config(r.ip, r.api_port, r.robot_id, filtered)
    except robot_api.RobotAPIError as e:
        return Ok(ok=False, msg=f"下发失败 code={e.code} {e.msg}")
    except Exception as e:  # noqa: BLE001
        return Ok(ok=False, msg=str(e))
    # 存快照
    snap = RobotConfigSnapshot(robot_pk=r.id, source="user_write", operator=user.username,
                               config_json=filtered)
    db.add(snap)
    db.commit()
    return Ok(msg="已下发并记录")
