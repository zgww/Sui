"""物模型访问器: 对接 robot_api + DB, 提供统一的数据读写接口。

上层(poller / router)调用 accessor, 不直接碰 robot_api 和 DB:

    props = accessor.fetch_runtime(robot, db)   # 取 + 存, 一步到位
    ver   = accessor.fetch_version(robot, db)
    alerts = accessor.fetch_alerts(robot, db)
"""
from __future__ import annotations
from datetime import datetime
from typing import List, Optional
from sqlalchemy.orm import Session

from ..models.robot import Robot, RobotProperty
from ..models.monitor import StatusLog, PowerLog, RobotAlert, RobotVersion
from ..services import robot_api
from . import mapper
from .definition import get_alert_text


def fetch_runtime(robot: Robot, db: Session) -> Optional[mapper.RuntimeProperties]:
    """获取运行时状态 → 存快照 + 写时序。"""
    try:
        code, msg, data = robot_api.call(robot.ip, robot.api_port, robot.robot_id, 21)
    except Exception:
        return None
    if code != 0 or not data:
        return None

    props = mapper.map_runtime(data)

    # 1. 更新最新快照
    snap = db.query(RobotProperty).filter(RobotProperty.robot_pk == robot.id).first()
    if not snap:
        snap = RobotProperty(robot_pk=robot.id)
        db.add(snap)
    _update_snapshot(snap, props)
    snap.last_seen = datetime.utcnow()
    snap.updated_at = datetime.utcnow()

    # 2. 写时序
    log = StatusLog(
        robot_pk=robot.id, status=props.status, doing=props.doing,
        cpu=props.cpu, temperature=props.temperature, speed=props.speed,
        angular_speed=props.angular_speed, battery=props.battery,
        pose_x=props.pose_x, pose_y=props.pose_y, theta=props.theta,
        floor=props.floor, conn_chassis=props.conn_chassis,
        conn_server=props.conn_server, conn_elevator=props.conn_elevator,
    )
    db.add(log)
    db.commit()
    return props


def fetch_power(robot: Robot, db: Session) -> Optional[mapper.PowerInfo]:
    """获取电源信息 → 存快照 + 写时序。"""
    try:
        code, msg, data = robot_api.call(robot.ip, robot.api_port, robot.robot_id, 22)
    except Exception:
        return None
    if code != 0 or not data:
        return None

    info = mapper.map_power(data)

    # 更新快照
    snap = db.query(RobotProperty).filter(RobotProperty.robot_pk == robot.id).first()
    if snap:
        snap.power_mode = info.mode
        snap.voltage = info.voltage
        snap.current = info.current
        snap.capacity = info.capacity
        snap.remaining = info.remaining
        snap.charging = info.charging
        snap.updated_at = datetime.utcnow()

    db.add(PowerLog(
        robot_pk=robot.id, mode=info.mode, voltage=info.voltage,
        current=info.current, capacity=info.capacity,
        remaining=info.remaining, charging=info.charging,
    ))
    db.commit()
    return info


def fetch_version(robot: Robot, db: Session) -> Optional[mapper.VersionInfo]:
    """获取版本 → 存快照(变更时写历史)。"""
    raw = None
    try:
        code, msg, data = robot_api.call(robot.ip, robot.api_port, robot.robot_id, 6)
        if code == 0 and data:
            raw = data
    except Exception:
        pass
    # 回退到 cmd=4.version
    if not raw:
        try:
            code, msg, data = robot_api.call(robot.ip, robot.api_port, robot.robot_id, 4)
            if code == 0 and data:
                raw = data.get("version", {})
        except Exception:
            pass
    if not raw:
        return None

    ver = mapper.map_version(raw)

    # 更新快照
    snap = db.query(RobotProperty).filter(RobotProperty.robot_pk == robot.id).first()
    if not snap:
        snap = RobotProperty(robot_pk=robot.id)
        db.add(snap)
    snap.app_version = ver.application
    snap.fw_version = ver.firmware
    snap.hw_version = ver.hardware
    snap.motion_version = ver.motion
    snap.sdk_version = ver.sdk
    snap.updated_at = datetime.utcnow()

    # 变更时写历史
    last = (db.query(RobotVersion).filter(RobotVersion.robot_pk == robot.id)
            .order_by(RobotVersion.ts.desc()).first())
    if (not last or last.application != ver.application
            or last.firmware != ver.firmware or last.motion != ver.motion):
        db.add(RobotVersion(
            robot_pk=robot.id, application=ver.application, firmware=ver.firmware,
            hardware=ver.hardware, hardware_sn=ver.hardware_sn,
            motion=ver.motion, sdk=ver.sdk, raw=raw))
    db.commit()
    return ver


def fetch_alerts(robot: Robot, db: Session) -> List[mapper.AlertItem]:
    """获取告警列表 → 存历史。"""
    try:
        code, msg, data = robot_api.call(robot.ip, robot.api_port, robot.robot_id, 10)
    except Exception:
        return []
    alerts_raw = data.get("alerts", []) if code == 0 and isinstance(data, dict) else []
    items = mapper.map_alerts(alerts_raw)
    for a in items:
        db.add(RobotAlert(
            robot_pk=robot.id, alert_id=a.alert_id,
            content=a.content or get_alert_text(a.alert_id),
            level=a.level, params=a.params))
    if items:
        db.commit()
    return items


def _update_snapshot(snap: RobotProperty, props: mapper.RuntimeProperties):
    """更新快照字段。"""
    snap.status = props.status
    snap.doing = props.doing
    snap.cpu = props.cpu
    snap.temperature = props.temperature
    snap.speed = props.speed
    snap.angular_speed = props.angular_speed
    snap.battery = props.battery
    snap.pose_x = props.pose_x
    snap.pose_y = props.pose_y
    snap.theta = props.theta
    snap.floor = props.floor
    snap.conn_chassis = props.conn_chassis
    snap.conn_server = props.conn_server
    snap.conn_elevator = props.conn_elevator
    snap.ptz_pan = props.ptz_pan
    snap.ptz_tilt = props.ptz_tilt
    snap.ptz_zoom = props.ptz_zoom
