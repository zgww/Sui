"""机器人 CRUD + 连通性测试。"""
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session
from typing import List
from ..point_archive.relations import guard_archive_bindings
from ..database import get_db
from ..models import Robot, RobotStatusLog, RobotVersion
from ..schemas import RobotIn, RobotOut, Ok
from ..auth import get_current_user, engineer_only
from ..services import ssh_client, robot_api

router = APIRouter(prefix="/api/robots", tags=["robots"])


def _enrich(r: Robot, db: Session) -> dict:
    """回填最新状态/版本用于列表展示。"""
    last_st = (db.query(RobotStatusLog)
               .filter(RobotStatusLog.robot_pk == r.id)
               .order_by(RobotStatusLog.ts.desc()).first())
    last_ver = (db.query(RobotVersion)
                .filter(RobotVersion.robot_pk == r.id)
                .order_by(RobotVersion.ts.desc()).first())
    d = {
        "id": r.id, "name": r.name, "robot_id": r.robot_id, "ip": r.ip,
        "api_port": r.api_port, "product_type": r.product_type,
        "ssh_user": r.ssh_user, "ssh_pass": r.ssh_pass, "ssh_port": r.ssh_port,
        "log_dir": r.log_dir, "install_dir": r.install_dir, "version_file": r.version_file,
        "poll_status": r.poll_status, "poll_meta": r.poll_meta,
        "log_retention_days": r.log_retention_days, "enabled": r.enabled, "note": r.note,
        "video_server": r.video_server, "video_secret": r.video_secret,
        "video_visible_stream": r.video_visible_stream, "video_thermal_stream": r.video_thermal_stream,
        "video_protocol": r.video_protocol, "video_use_robot_ip": r.video_use_robot_ip,
        "created_at": r.created_at, "updated_at": r.updated_at,
        "last_battery": last_st.battery if last_st else None,
        "last_version": last_ver.application if last_ver else None,
        "last_seen": last_st.ts if last_st else None,
        "online": (last_st is not None and last_st.conn_server in (True,)),
    }
    return d


@router.get("", response_model=List[RobotOut])
def list_robots(db: Session = Depends(get_db), _=Depends(get_current_user)):
    rs = db.query(Robot).order_by(Robot.id).all()
    return [_enrich(r, db) for r in rs]


@router.post("", response_model=RobotOut)
def create_robot(body: RobotIn, db: Session = Depends(get_db), user=Depends(engineer_only)):
    r = Robot(**body.model_dump())
    db.add(r)
    db.commit()
    db.refresh(r)
    return _enrich(r, db)


@router.put("/{rid}", response_model=RobotOut)
def update_robot(rid: int, body: RobotIn, db: Session = Depends(get_db), user=Depends(engineer_only)):
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    for k, v in body.model_dump().items():
        setattr(r, k, v)
    db.commit()
    db.refresh(r)
    return _enrich(r, db)


@router.delete("/{rid}", response_model=Ok)
@guard_archive_bindings("robot", "rid")
def delete_robot(rid: int, db: Session = Depends(get_db), user=Depends(engineer_only)):
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    db.delete(r)
    db.commit()
    return Ok(msg="已删除")


@router.get("/{rid}/ping", response_model=Ok)
def ping_robot(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """综合连通性: SSH + API。"""
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    ok_ssh, msg_ssh = ssh_client.check(r.ip, r.ssh_port, r.ssh_user, r.ssh_pass)
    api_ok = False
    api_msg = ""
    try:
        code, m, _ = robot_api.call(r.ip, r.api_port, r.robot_id, 21)
        api_ok = (code == 0)
        api_msg = f"cmd=21 code={code} msg={m}"
    except Exception as e:  # noqa: BLE001
        api_msg = f"API 不可达: {e}"
    return Ok(ok=(ok_ssh and api_ok),
              msg=f"SSH: {'OK' if ok_ssh else 'FAIL'} ({msg_ssh}) | API: {'OK' if api_ok else 'FAIL'} ({api_msg})")
