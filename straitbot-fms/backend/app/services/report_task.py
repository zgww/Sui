"""巡检报表异步生成任务。

报表生成是耗时操作（几十上百个检测框，每个要读图片、写 Excel），
不能占着 HTTP 请求同步等。用后台线程异步生成，生成完更新数据库状态，
前端轮询状态后下载。

状态机：
  "" (未生成) -> pending (已提交) -> running (生成中) -> done (完成) / failed (失败)
"""
import logging
import threading
from datetime import datetime
from pathlib import Path

from sqlalchemy.orm import Session

from ..config import DATA_DIR
from ..database import SessionLocal
from ..models import InspectionRun
from .inspection_report import generate_report

logger = logging.getLogger(__name__)

# 报表输出目录
REPORT_DIR = DATA_DIR / "reports"
REPORT_DIR.mkdir(parents=True, exist_ok=True)

# 正在生成的 run_id 集合（防止重复提交）
_running: set[int] = set()
_lock = threading.Lock()


def is_running(run_id: int) -> bool:
    with _lock:
        return run_id in _running


def submit_report_task(run_id: int, regenerate: bool = False) -> dict:
    """提交报表生成任务（异步）。

    Args:
        run_id: 巡检记录 ID
        regenerate: 是否重新生成（覆盖旧报表）。默认 False，已生成过就直接返回。

    返回当前状态：
    - {"status": "pending"}  已提交，正在排队
    - {"status": "running"}  正在生成中（重复提交）
    - {"status": "done"}     已生成过，直接可用
    """
    db = SessionLocal()
    try:
        run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
        if not run:
            return {"status": "error", "message": "巡检记录不存在"}

        # 正在生成中，不重复提交
        if run.report_status in ("pending", "running"):
            return {"status": run.report_status}

        # 已生成过，且不要求重新生成，直接返回
        if run.report_status == "done" and run.report_path and not regenerate:
            return {"status": "done", "path": run.report_path}

        # 标记为 pending，启动后台线程
        run.report_status = "pending"
        run.report_error = ""
        run.report_generated_at = None
        db.commit()

        thread = threading.Thread(
            target=_generate_worker,
            args=(run_id,),
            daemon=True,
            name=f"report-{run_id}",
        )
        thread.start()
        logger.info("报表生成任务已提交: run_id=%d (regenerate=%s)", run_id, regenerate)
        return {"status": "pending"}
    finally:
        db.close()


def _generate_worker(run_id: int) -> None:
    """后台线程：生成报表并更新状态。"""
    with _lock:
        if run_id in _running:
            return
        _running.add(run_id)

    db = SessionLocal()
    try:
        # 标记为 running
        run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
        if not run:
            return
        run.report_status = "running"
        db.commit()

        # 生成报表（耗时操作）
        path = generate_report(db, run_id)

        # 标记为 done
        run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
        run.report_status = "done"
        run.report_path = str(path)
        run.report_error = ""
        run.report_generated_at = datetime.utcnow()
        db.commit()
        logger.info("报表生成完成: run_id=%d -> %s", run_id, path)

    except Exception as e:
        logger.exception("报表生成失败: run_id=%d", run_id)
        try:
            run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
            if run:
                run.report_status = "failed"
                run.report_error = str(e)
                db.commit()
        except Exception:
            pass
    finally:
        with _lock:
            _running.discard(run_id)
        db.close()


def get_report_status(run_id: int) -> dict:
    """查询报表生成状态。"""
    db = SessionLocal()
    try:
        run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
        if not run:
            return {"status": "error", "message": "巡检记录不存在"}
        return {
            "status": run.report_status or "",
            "path": run.report_path or "",
            "error": run.report_error or "",
            "generated_at": run.report_generated_at.isoformat() if run.report_generated_at else None,
        }
    finally:
        db.close()
