"""定时轮询: 周期性采集机器人状态/版本/告警/电源/配置。

改造后走物模型 accessor, 不直接操作 DB 和 robot_api。
APScheduler 后台调度。每个作业失败不影响其它作业。
"""
import json
from datetime import datetime
from apscheduler.schedulers.background import BackgroundScheduler

from ..database import SessionLocal
from ..models import Robot, RobotConfigSnapshot
from ..thing_model import accessor
from . import robot_api


_scheduler = None
_last_cfg_sig = {}   # robot_pk -> config 签名, 变化才存


def _tick_status():
    """状态轮询(10s): 走 accessor.fetch_runtime。"""
    db = SessionLocal()
    try:
        for r in db.query(Robot).filter(Robot.enabled.is_(True), Robot.poll_status.is_(True)).all():
            try:
                accessor.fetch_runtime(r, db)
            except Exception:
                pass
    finally:
        db.close()


def _tick_meta():
    """元数据轮询(60s): 版本 + 告警 + 电源 + 配置。"""
    db = SessionLocal()
    try:
        for r in db.query(Robot).filter(Robot.enabled.is_(True), Robot.poll_meta.is_(True)).all():
            # 版本
            try:
                accessor.fetch_version(r, db)
            except Exception:
                pass
            # 告警
            try:
                accessor.fetch_alerts(r, db)
            except Exception:
                pass
            # 电源
            try:
                accessor.fetch_power(r, db)
            except Exception:
                pass
            # 配置快照(变化时存)
            try:
                _store_config_if_changed(r, db)
            except Exception:
                pass
    finally:
        db.close()


def _store_config_if_changed(r: Robot, db):
    """配置变化时存快照。"""
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 4)
    if code != 0 or not data:
        return
    sig = json.dumps(data, sort_keys=True, ensure_ascii=False)
    if _last_cfg_sig.get(r.id) != sig:
        _last_cfg_sig[r.id] = sig
        db.add(RobotConfigSnapshot(robot_pk=r.id, source="poll", operator="system", config_json=data))
        db.commit()


def start_scheduler():
    global _scheduler
    if _scheduler is not None:
        return _scheduler
    from ..config import settings
    _scheduler = BackgroundScheduler(timezone="UTC")
    from .inspection_dispatch import tick_plans, tick_execution_status
    _scheduler.add_job(tick_plans, "interval", seconds=15, id="inspection-plans",
                       max_instances=1, coalesce=True)
    _scheduler.add_job(tick_execution_status, "interval", seconds=30, id="inspection-plan-status",
                       max_instances=1, coalesce=True)
    _scheduler.add_job(_tick_status, "interval",
                       seconds=settings.poll_status_interval_sec, id="status",
                       max_instances=1, coalesce=True)
    _scheduler.add_job(_tick_meta, "interval",
                       seconds=settings.poll_meta_interval_sec, id="meta",
                       max_instances=1, coalesce=True)
    # 日志保留清理
    from .log_retention import cleanup_once
    _scheduler.add_job(cleanup_once, "interval", hours=6, id="retention",
                       max_instances=1, coalesce=True)
    _scheduler.start()
    print("[scheduler] started (thing_model accessor)")
    return _scheduler


def shutdown_scheduler():
    global _scheduler
    if _scheduler:
        _scheduler.shutdown(wait=False)
        _scheduler = None
