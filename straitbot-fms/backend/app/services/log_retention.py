"""日志保留策略: 按机器人配置的 retention_days 清理 data/logs/<pk>/ 下过期文件,
并删除对应的 uploaded_logs/fetched_logs 记录。
"""
import os
import time
from datetime import datetime, timedelta
from pathlib import Path
from sqlalchemy.orm import Session

from ..database import SessionLocal
from ..models import Robot, UploadedLog, FetchedLog
from ..config import LOGS_DIR


def cleanup_once():
    db = SessionLocal()
    try:
        now = time.time()
        cleaned = 0
        for r in db.query(Robot).all():
            days = r.log_retention_days or 0
            if days <= 0:
                continue
            cutoff = now - days * 86400
            rdir = LOGS_DIR / str(r.id)
            if not rdir.exists():
                continue
            # 清理 uploaded_logs
            for rec in db.query(UploadedLog).filter(UploadedLog.robot_pk == r.id).all():
                p = rec.stored_path or ""
                try:
                    if p and os.path.exists(p) and os.path.getmtime(p) < cutoff:
                        os.remove(p)
                        db.delete(rec)
                        cleaned += 1
                except Exception:
                    pass
            # 清理 fetched_logs
            for rec in db.query(FetchedLog).filter(FetchedLog.robot_pk == r.id).all():
                p = rec.stored_path or ""
                try:
                    if p and os.path.exists(p) and os.path.getmtime(p) < cutoff:
                        os.remove(p)
                        db.delete(rec)
                        cleaned += 1
                except Exception:
                    pass
            # 兜底: 清理孤儿文件(目录里存在但 DB 没记录且过期)
            for f in rdir.glob("*"):
                try:
                    if f.is_file() and f.stat().st_mtime < cutoff:
                        f.unlink()
                        cleaned += 1
                except Exception:
                    pass
        db.commit()
        if cleaned:
            print(f"[retention] cleaned {cleaned} files")
    finally:
        db.close()
