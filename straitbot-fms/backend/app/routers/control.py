"""控制模块: 运动/云台/升降杆/拍照测温/音频/急停。

统一前缀 /api/control/{rid}/..., 按 thing_model services 定义调用 robot_api。
"""
from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel
from typing import Optional
from sqlalchemy.orm import Session

from ..database import get_db
from ..models import Robot
from ..schemas import Ok
from ..auth import engineer_only, get_current_user
from ..services import robot_api, ssh_client
import logging

router = APIRouter(prefix="/api/control", tags=["control"])

logger = logging.getLogger("rail.robot")


def _robot(rid: int, db: Session) -> Robot:
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    return r


# ========== 运动 ==========
class MotionMoveIn(BaseModel):
    command: int = 0    # 0停 1前 2后 3左转 4右转 5左转(轮距) 6右转(轮距)
    instant_speed: float = 0


class PoseIn(BaseModel):
    x: float
    y: float
    theta: float = 0
    ptz_pan: float = 0
    ptz_tilt: float = 0
    ptz_zoom: float = 0


class HomeIn(BaseModel):
    go_home: bool = True


@router.post("/{rid}/motion/move")
def motion_move(rid: int, body: MotionMoveIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 32,
                                      {"command": body.command, "instant_speed": body.instant_speed,
                                       "safety_check": False})
    return {"ok": code == 0, "msg": msg}


@router.post("/{rid}/motion/pose")
def motion_set_pose(rid: int, body: PoseIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    r = _robot(rid, db)
    payload = {
        "point": {"x": body.x, "y": body.y},
        "theta": body.theta,
        "ptz": {"pan": body.ptz_pan, "tilt": body.ptz_tilt, "zoom": body.ptz_zoom},
        "safety_check": False,
    }
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 31, payload)
    return {"ok": code == 0, "msg": msg}


@router.get("/{rid}/motion/pose")
def motion_get_pose(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 30)
    return {"ok": code == 0, "data": data, "msg": msg}


@router.post("/{rid}/motion/home")
def motion_home(rid: int, body: HomeIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 33, {"go_home": body.go_home})
    return {"ok": code == 0, "msg": msg}


@router.post("/{rid}/motion/estop")
def motion_estop(rid: int, action: bool = True, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """急停(挂轨专用 cmd=51)。"""
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 51, {"emergency_stop": action})
    return {"ok": code == 0, "msg": msg}


# ========== 云台 ==========
class PtzPoseIn(BaseModel):
    pan: float = 0
    tilt: float = 0
    zoom: float = 0


class PtzActionIn(BaseModel):
    command: int = 0   # 0复位 1上仰 2下俯 3左转 4右转 ...
    stop: bool = False
    channel: int = 1


@router.get("/{rid}/ptz/pose")
def ptz_get_pose(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 35)
    return {"ok": code == 0, "data": data, "msg": msg}


@router.post("/{rid}/ptz/pose")
def ptz_set_pose(rid: int, body: PtzPoseIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 36,
                                      {"pan": body.pan, "tilt": body.tilt, "zoom": body.zoom})
    return {"ok": code == 0, "msg": msg}


@router.post("/{rid}/ptz/action")
def ptz_action(rid: int, body: PtzActionIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 37,
                                      {"command": body.command, "stop": body.stop, "channel": body.channel})
    return {"ok": code == 0, "msg": msg}


# ========== 拍照/录像/测温 ==========
class CaptureIn(BaseModel):
    command: int = 1   # 1可见光拍照 2红外拍照 3录像 4红外测温 5停止录像
    duration: int = 0  # 录像时长(s)


@router.post("/{rid}/camera/capture")
def camera_capture(rid: int, body: CaptureIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 38,
                                      {"command": body.command, "duration": body.duration})
    return {"ok": code == 0, "data": data, "msg": msg}


# ========== 升降杆 ==========
class LiftIn(BaseModel):
    command: int = 0   # 0停 1展开 2收缩 3指定高度 4复位
    height: float = 0  # command=3 时有效


@router.get("/{rid}/lift/status")
def lift_status(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 40)
    return {"ok": code == 0, "data": data, "msg": msg}


@router.post("/{rid}/lift/control")
def lift_control(rid: int, body: LiftIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 41,
                                      {"command": body.command, "height": body.height})
    return {"ok": code == 0, "msg": msg}


# ========== 音频 ==========
class AudioIn(BaseModel):
    command: int = 0   # 0停 1播放
    file: str = ""


@router.post("/{rid}/audio/play")
def audio_play(rid: int, body: AudioIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 47,
                                      {"command": body.command, "file": body.file})
    return {"ok": code == 0, "msg": msg}


# ========== 局放 ==========
@router.post("/{rid}/pdd/detect")
def pdd_detect(rid: int, command: int = 1, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """局放检测 cmd=48。command: 0停 1开放式超声 2地波 3特高频 4接触式超声。"""
    r = _robot(rid, db)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 48, {"command": command})
    return {"ok": code == 0, "data": data, "msg": msg}



@router.post("/{rid}/inspection/cancel")
def cancel_inspection(rid: int, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """取消当前正在进行的巡检。

    向机器人状态机发送"取消巡检"信号，主机退出"巡检中"状态。
    """
    from ..rail.runtime import get_robot
    logger.info('取消当前正在进行的巡检')
    r = _robot(rid, db)

    robot = get_robot()
    if robot is None:
        raise HTTPException(503, "机器人运行时未就绪")

    # 向状态机发送"取消巡检"信号
    logger.info('发送取消巡检的信号')
    robot.sm.send("取消巡检", "main")
    robot.sm.send("取消巡检", "insp")

    return {"code": 0, "msg": "取消巡检信号已发送"}
