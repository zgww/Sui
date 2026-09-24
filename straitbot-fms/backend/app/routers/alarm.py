"""检测告警 API：列表（筛选 / 分页）、未确认数量、确认（单条 / 确认所有筛选）。"""
from datetime import datetime, timedelta
from typing import Any, Optional

from fastapi import APIRouter, Body, Depends, HTTPException, Query
from sqlalchemy import or_
from sqlalchemy.orm import Session

from ..auth import get_current_user
from ..database import get_db
from ..models import Alarm
from ..prefab.detect_pipeline import LEVELS

router = APIRouter(prefix="/api/alarms", tags=["alarms"])


# ============================================================ 筛选 / 序列化

def _apply_filters(q, *, alarm_type: str = "", level: str = "",
                   keyword: str = "", start: str = "", end: str = "",
                   status: str = ""):
    if status:
        q = q.filter(Alarm.status == status)
    if alarm_type:
        q = q.filter(Alarm.alarm_type == alarm_type)
    if level:
        q = q.filter(Alarm.level == level)
    if keyword:
        like = f"%{keyword.strip()}%"
        q = q.filter(or_(Alarm.title.ilike(like), Alarm.content.ilike(like),
                         Alarm.point_name.ilike(like)))
    if start:
        try:
            q = q.filter(Alarm.triggered_at >= datetime.strptime(start, "%Y-%m-%d"))
        except ValueError:
            pass
    if end:
        try:
            d = datetime.strptime(end, "%Y-%m-%d") + timedelta(days=1)
            q = q.filter(Alarm.triggered_at < d)
        except ValueError:
            pass
    return q


def serialize(a: Alarm) -> dict:
    return {
        "id": a.id,
        "run_id": a.run_id,
        "action_result_id": a.action_result_id,
        "inspection_id": a.inspection_id,
        "floor": a.floor,
        "waypoint_id": a.waypoint_id,
        "action_id": a.action_id,
        "point_id": a.point_id,
        "point_name": a.point_name,
        "alarm_type": a.alarm_type,
        "algorithm": a.algorithm,
        "level": a.level,
        "title": a.title,
        "content": a.content,
        "picture": a.picture,
        "extra": a.extra_json,
        "status": a.status,
        "triggered_at": a.triggered_at.isoformat() if a.triggered_at else None,
        "acknowledged_at": a.acknowledged_at.isoformat() if a.acknowledged_at else None,
        "acknowledged_by": a.acknowledged_by,
        "created_at": a.created_at.isoformat() if a.created_at else None,
    }


# ============================================================ 列表 / 元数据

@router.get("")
def list_alarms(
    page: int = Query(1, ge=1),
    page_size: int = Query(20, ge=1, le=200),
    status: str = "", alarm_type: str = "", level: str = "",
    keyword: str = "", start: str = "", end: str = "",
    db: Session = Depends(get_db), _=Depends(get_current_user),
):
    """告警分页列表，支持 status / alarm_type / level / keyword / 日期筛选。"""
    base = _apply_filters(db.query(Alarm), status=status, alarm_type=alarm_type,
                          level=level, keyword=keyword, start=start, end=end)
    total = base.count()
    rows = (base.order_by(Alarm.triggered_at.desc().nullslast(), Alarm.id.desc())
            .offset((page - 1) * page_size).limit(page_size).all())
    return {"total": total, "page": page, "page_size": page_size,
            "items": [serialize(a) for a in rows]}


@router.get("/unack-count")
def unack_count(db: Session = Depends(get_db), _=Depends(get_current_user)):
    """未确认告警数量（右上角角标用）。"""
    n = db.query(Alarm).filter(Alarm.status == "unack").count()
    return {"count": n}


@router.get("/meta")
def alarm_meta(db: Session = Depends(get_db), _=Depends(get_current_user)):
    """筛选用的类型清单（库里实际出现过的类型）与固定级别清单。"""
    types = sorted({r[0] for r in db.query(Alarm.alarm_type).distinct().all() if r[0]})
    return {"types": types, "levels": list(LEVELS)}


# ============================================================ 确认

@router.post("/{alarm_id}/ack")
def ack_one(alarm_id: int, db: Session = Depends(get_db),
            user=Depends(get_current_user)):
    """确认单条告警。"""
    a = db.query(Alarm).filter(Alarm.id == alarm_id).first()
    if a is None:
        raise HTTPException(404, "告警不存在")
    if a.status != "ack":
        a.status = "ack"
        a.acknowledged_at = datetime.utcnow()
        a.acknowledged_by = user.username
        db.commit()
    return {"id": a.id, "status": a.status}


@router.post("/ack-all")
def ack_all(body: dict = Body(default={}), db: Session = Depends(get_db),
            user=Depends(get_current_user)):
    """确认所有**符合筛选条件**的未确认告警。

    body 字段与列表筛选一致（alarm_type / level / keyword / start / end）；
    不传任何条件 = 确认全部未确认告警。只动未确认行，已确认的不变。
    """
    q = _apply_filters(db.query(Alarm), status="unack",
                       alarm_type=str(body.get("alarm_type") or ""),
                       level=str(body.get("level") or ""),
                       keyword=str(body.get("keyword") or ""),
                       start=str(body.get("start") or ""),
                       end=str(body.get("end") or ""))
    rows = q.all()
    nowdt = datetime.utcnow()
    for a in rows:
        a.status = "ack"
        a.acknowledged_at = nowdt
        a.acknowledged_by = user.username
    db.commit()
    return {"acknowledged": len(rows)}
