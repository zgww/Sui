"""监控: 实时状态、历史曲线、告警、版本历史。"""
from datetime import datetime, timedelta
from fastapi import APIRouter, Depends, HTTPException, Query
from sqlalchemy.orm import Session
from typing import List
from ..database import get_db
from ..models import Robot, RobotStatusLog, RobotPowerLog, RobotAlert, RobotVersion, RobotConfigSnapshot
from ..schemas import AlertOut, Ok
from ..auth import get_current_user
from ..services import robot_api

router = APIRouter(prefix="/api/monitor", tags=["monitor"])


@router.get("/{rid}/status")
def live_status(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    try:
        code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 21)
        if code == 0 and data:
            # cmd=21 不返回云台位姿, 额外调用 cmd=35 获取并合并到 pose.ptz
            try:
                p_code, p_msg, p_data = robot_api.call(
                    r.ip, r.api_port, r.robot_id, 35, timeout=4.0)
                if p_code == 0 and p_data:
                    pose = data.get("pose")
                    if not isinstance(pose, dict):
                        pose = {}
                        data["pose"] = pose
                    pose["ptz"] = {
                        "pan": float(p_data.get("pan", 0)),
                        "tilt": float(p_data.get("tilt", 0)),
                        "zoom": float(p_data.get("zoom", 0)),
                    }
            except Exception:
                pass  # 云台查询失败不影响整体状态返回
        return {"ok": code == 0, "code": code, "msg": msg, "data": data}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "code": -1, "msg": str(e), "data": None}


@router.get("/{rid}/history")
def status_history(
    rid: int,
    hours: int = Query(24, ge=1, le=720),
    db: Session = Depends(get_db),
    _=Depends(get_current_user),
):
    """最近 N 小时的状态/电源时序, 用于画曲线。"""
    since = datetime.utcnow() - timedelta(hours=hours)
    sts = (db.query(RobotStatusLog)
           .filter(RobotStatusLog.robot_pk == rid, RobotStatusLog.ts >= since)
           .order_by(RobotStatusLog.ts.asc()).all())
    pws = (db.query(RobotPowerLog)
           .filter(RobotPowerLog.robot_pk == rid, RobotPowerLog.ts >= since)
           .order_by(RobotPowerLog.ts.asc()).all())
    return {
        "status": [{
            "ts": s.ts.isoformat(), "battery": s.battery, "cpu": s.cpu,
            "temperature": s.temperature, "speed": s.speed,
            "angular_speed": s.angular_speed, "status": s.status, "doing": s.doing,
        } for s in sts],
        "power": [{
            "ts": p.ts.isoformat(), "voltage": p.voltage, "current": p.current,
            "remaining": p.remaining, "charging": p.charging, "mode": p.mode,
        } for p in pws],
    }


@router.get("/{rid}/alerts", response_model=List[AlertOut])
def alerts(
    rid: int,
    limit: int = Query(100, ge=1, le=1000),
    level: str = Query("", description="warning|error|fatal|空=全部"),
    db: Session = Depends(get_db),
    _=Depends(get_current_user),
):
    q = db.query(RobotAlert).filter(RobotAlert.robot_pk == rid)
    if level:
        q = q.filter(RobotAlert.level == level)
    return q.order_by(RobotAlert.ts.desc()).limit(limit).all()


@router.get("/{rid}/versions")
def version_history(rid: int, limit: int = Query(50, ge=1, le=500),
                    db: Session = Depends(get_db), _=Depends(get_current_user)):
    vs = (db.query(RobotVersion).filter(RobotVersion.robot_pk == rid)
          .order_by(RobotVersion.ts.desc()).limit(limit).all())
    return [{
        "ts": v.ts.isoformat(), "application": v.application, "firmware": v.firmware,
        "hardware": v.hardware, "motion": v.motion, "sdk": v.sdk,
    } for v in vs]


@router.get("/{rid}/configs")
def config_history(rid: int, limit: int = Query(50, ge=1, le=500),
                   db: Session = Depends(get_db), _=Depends(get_current_user)):
    """参数配置快照历史(cmd=4)。"""
    cs = (db.query(RobotConfigSnapshot).filter(RobotConfigSnapshot.robot_pk == rid)
          .order_by(RobotConfigSnapshot.ts.desc()).limit(limit).all())
    return [{
        "ts": c.ts.isoformat(), "source": c.source, "operator": c.operator,
        "config": c.config_json,
    } for c in cs]
