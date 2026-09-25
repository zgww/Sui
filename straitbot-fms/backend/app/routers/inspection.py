"""巡检框架: 任务创建/控制/结果查询 + 机器人上报接收(cmd=103~106)。

基于 cmd=100~106。
"""
import json
import logging
from datetime import datetime
from typing import Optional, Any, List, Dict
from pathlib import Path

from fastapi import APIRouter, Depends, HTTPException, Query, Request
from fastapi.responses import FileResponse
from pydantic import BaseModel, Field, AliasChoices
from sqlalchemy.orm import Session

from ..database import get_db
from ..models import (
    Robot, InspectionTask, InspectionRun, InspectionResult,
    InspectionActionResult, InspectionPointResult, ArchiveTaskPoint,
)
from ..auth import engineer_only, get_current_user
from ..services import robot_api
from ..config import DATA_DIR

logger = logging.getLogger(__name__)
router = APIRouter(prefix="/api/inspection", tags=["inspection"])


def _robot(rid, db):
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    return r


def _resolve_robot(body, request, db):
    """上报请求识别机器人。优先按 body.robot_id (robots.robot_id, 如56) 匹配,
    回退 X-Real-IP (robots.ip) 匹配。返回 Robot 记录, 落库时用 robot.id (robot_pk, 如2)。"""
    rid = body.get("robot_id")
    if rid:
        try:
            robot = db.query(Robot).filter(Robot.robot_id == int(rid)).first()
            if robot:
                return robot
        except (TypeError, ValueError):
            pass
    robot_ip = (request.headers.get("X-Real-IP")
                or request.headers.get("X-Forwarded-For", "").split(",")[0].strip()
                or (request.client.host if request.client else ""))
    if robot_ip:
        return db.query(Robot).filter(Robot.ip == robot_ip).first()
    return None


def _plan_report(body, request, db):
    """New plan execution reports must match their robot; retain legacy handling."""
    from ..models import PlanExecution
    from ..services.inspection_dispatch import report_execution
    execution = report_execution(db, body.get("inspection_id", ""))
    if execution:
        robot = _resolve_robot(body, request, db)
        if robot is None or robot.id != execution.robot_pk:
            raise HTTPException(403, "上报机器人与巡检记录不一致")
    return execution


# ========== 任务管理 ==========

@router.get("/tasks")
def list_tasks(robot_pk: Optional[int] = None, limit: int = 100,
               db: Session = Depends(get_db), _=Depends(get_current_user)):
    q = db.query(InspectionTask)
    if robot_pk:
        q = q.filter(InspectionTask.robot_pk == robot_pk)
    tasks = q.order_by(InspectionTask.created_at.desc()).limit(limit).all()
    return [{
        "id": t.id, "robot_pk": t.robot_pk, "name": t.name,
        "status": t.status, "created_at": t.created_at.isoformat() if t.created_at else None,
    } for t in tasks]


class TaskCreateIn(BaseModel):
    robot_pk: int
    name: str = ""
    content: Optional[Any] = None
    schedule: Optional[Any] = None
    point_ids: List[str] = Field(default_factory=list, max_length=10000)
    archive_revision: Optional[int] = Field(default=None, ge=0)


@router.post("/tasks")
def create_task(body: TaskCreateIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """创建巡检任务。同时下发到机器人(cmd=100)。"""
    r = _robot(body.robot_pk, db)
    payload = {}
    if body.content:
        try:
            payload["content"] = body.content if isinstance(body.content, str) else json.dumps(body.content, ensure_ascii=False, allow_nan=False)
        except (ValueError, TypeError):
            raise HTTPException(422, "巡检内容包含无效数值或无法序列化的参数")
    if body.schedule:
        payload["schedule"] = body.schedule
    task = InspectionTask(
        robot_pk=body.robot_pk, name=body.name or "巡检任务",
        plan_json=body.content, schedule_json=body.schedule, status="idle",
    )
    if body.point_ids or body.archive_revision is not None:
        from ..point_archive.runtime import archive_store
        with archive_store.lock:
            task.archive_snapshot = archive_store.capture(body.point_ids, body.archive_revision)
            db.add(task)
            db.flush()
            for point_id in dict.fromkeys(body.point_ids):
                db.add(ArchiveTaskPoint(task_id=task.id, point_id=point_id))
            db.commit()
    try:
        code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 100, payload)
    except Exception:
        if task.id is not None:
            task.status = "failed"
            db.commit()
        raise
    task.status = "running" if code == 0 else "failed"
    db.add(task)
    db.commit()
    db.refresh(task)
    return {"ok": code == 0, "msg": msg, "task_id": task.id}


@router.get("/tasks/{task_id}/archive-snapshot")
def task_archive_snapshot(task_id: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    task = db.get(InspectionTask, task_id)
    if task is None:
        raise HTTPException(404, "任务不存在")
    return {"task_id": task.id, "archive_snapshot": task.archive_snapshot}



@router.post("/tasks/{task_id}/control")
def control_task(task_id: int, action: int = 0, target_waypoint: int = 0,
                 db: Session = Depends(get_db), _=Depends(engineer_only)):
    """控制巡检 cmd=101。action: 0取消 1暂停 2恢复 3跳航点。"""
    task = db.query(InspectionTask).filter(InspectionTask.id == task_id).first()
    if not task:
        raise HTTPException(404, "任务不存在")
    r = _robot(task.robot_pk, db)
    if action not in (0, 1, 2, 3):
        raise HTTPException(422, "未知控制动作")
    inspection_id = task.plan_json.get("id", str(task.id)) if isinstance(task.plan_json, dict) else str(task.id)
    payload = {"control": action, "inspection_id": inspection_id}
    if action == 3 and target_waypoint:
        payload["target_waypoint"] = target_waypoint
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 101, payload)
    if code == 0:
        task.status = {0: "canceled", 1: "paused", 2: "running", 3: "running"}.get(action, task.status)
        from ..services.inspection_dispatch import apply_report
        apply_report(db, inspection_id, task.robot_pk, {0: -1, 1: 2, 2: 3, 3: 3}[action])
    db.commit()
    return {"ok": code == 0, "msg": msg}


@router.get("/tasks/{task_id}/info")
def task_info(task_id: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """查询机器人侧巡检状态 cmd=102。"""
    task = db.query(InspectionTask).filter(InspectionTask.id == task_id).first()
    if not task:
        raise HTTPException(404, "任务不存在")
    r = _robot(task.robot_pk, db)
    inspection_id = task.plan_json.get("id", str(task.id)) if isinstance(task.plan_json, dict) else str(task.id)
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 102, {"inspection_id": inspection_id})
    return {"ok": code == 0, "data": data, "msg": msg}


# ========== 机器人上报接收 (cmd=103~106) ==========

class ReportStatusIn(BaseModel):
    """cmd=103 巡检状态上报"""
    inspection_id: str
    plan: str = ""
    status: int = 0   # -1取消 0开始 1完成 2暂停 3恢复 4挂起
    start_time: str = ""
    stop_time: str = ""
    finish_time: str = ""
    remark: str = ""
    substation_maps_id: str = Field(default="", validation_alias=AliasChoices("substation_maps_id", "substationMapsId"))
    floor: int = 0


class ActionResultItem(BaseModel):
    """cmd=104 单条动作结果"""
    code: int = 0
    waypoint_id: str = ""
    action_id: str = ""
    picture: str = ""
    infrared: str = ""
    media: str = ""
    inplace_timestamp: str = ""
    thermometry_points: Optional[Any] = None
    env: Optional[Any] = None
    pdd_data: Optional[Any] = None


class ReportResultIn(BaseModel):
    """cmd=104 巡检结果上报"""
    inspection_id: str
    start_time: str = ""
    finish_time: str = ""
    substation_maps_id: str = ""
    floor: int = 0
    results: List[ActionResultItem] = []


class ReportFinishIn(BaseModel):
    """cmd=105 巡检结果上传结束"""
    inspection_id: str
    total: int = 0
    uploaded: int = 0
    last_upload_time: str = ""
    substation_maps_id: str = Field(default="", validation_alias=AliasChoices("substation_maps_id", "substationMapsId"))
    floor: int = 0


class ReportProgressIn(BaseModel):
    """cmd=106 巡检进度上报"""
    inspection_id: str
    waypoint_id: str = ""
    action_id: str = ""
    progress: int = 0
    total_waypoint: int = 0
    current_waypoint: int = 0


def _parse_time(s: str):
    """解析时间字符串, 失败返回 None。"""
    if not s:
        return None
    for fmt in ["%Y-%m-%d %H:%M:%S", "%Y-%m-%dT%H:%M:%S", "%Y-%m-%dT%H:%M:%SZ"]:
        try:
            return datetime.strptime(s, fmt)
        except ValueError:
            continue
    return None


@router.post("/report/status")
async def report_status(request: Request, db: Session = Depends(get_db)):
    """机器人上报巡检状态 (cmd=103)。无需认证(机器人内部调用)。"""
    try:
        raw = await request.body()
        if not raw:
            return {"ok": False, "msg": "empty body"}
        try:
            body = json.loads(raw)
        except json.JSONDecodeError as je:
            # 尝试看 raw 是什么
            preview = raw[:500].decode("utf-8", errors="replace")
            logger.warning("[report/status] json fail: %s raw_preview=%s", je, preview)
            return {"ok": False, "msg": f"json error: {je}"}
        # 兼容驼峰 substationMapsId
        sid = body.get("substationMapsId") or body.get("substation_maps_id", "")
        body["substation_maps_id"] = sid
    except Exception as e:
        logger.warning("[report/status] body read fail: %s", e)
        return {"ok": False, "msg": str(e)}

    from ..services.inspection_dispatch import apply_report
    execution = _plan_report(body, request, db)
    if execution:
        apply_report(db, body.get("inspection_id", ""), execution.robot_pk, body.get("status", 0), body.get("remark", ""))

    run = db.query(InspectionRun).filter(
        InspectionRun.inspection_id == body.get("inspection_id", "")
    ).first()

    status_map = {-1: "canceled", 0: "started", 1: "done", 2: "paused", 3: "running", 4: "suspended"}
    status_str = status_map.get(body.get("status", 0), "started")
    if execution:
        from ..services.inspection_dispatch import active_id
        if body.get('inspection_id') != active_id(execution):
            db.commit()
            return {'ok': True, 'msg': '历史分段状态已忽略'}
        status_str = 'done' if execution.status == 'waiting_transition' else execution.status

    if run is None:
        # 优先 body.robot_id, 回退请求 IP 识别机器人 (robot_id→robots.robot_id→robot.id 即 robot_pk)
        robot = _resolve_robot(body, request, db)
        print(f"[report/status] robot_id={body.get('robot_id','(missing)')} X-Real-IP={request.headers.get('X-Real-IP','(missing)')} → matched robot_pk={robot.id if robot else None}", flush=True)
        run = InspectionRun(
            inspection_id=body.get("inspection_id", ""),
            robot_pk=robot.id if robot else None,
            status=status_str,
            start_time=_parse_time(body.get("start_time", "")) or datetime.utcnow(),
        )
        db.add(run)
    else:
        run.status = status_str
        # 旧记录可能 robot_pk 为空(104 兜底创建), 有 robot_id 时补上
        if run.robot_pk is None:
            robot = _resolve_robot(body, request, db)
            if robot:
                run.robot_pk = robot.id
        if body.get("stop_time"):
            run.remark = body.get("remark", "")
        if body.get("finish_time"):
            run.finish_time = _parse_time(body.get("finish_time", "")) or datetime.utcnow()

    db.commit()
    logger.info("[report/status] inspection_id=%s status=%s", body.get("inspection_id"), status_str)
    return {"ok": True}


@router.post("/report/result")
async def report_result(request: Request, db: Session = Depends(get_db)):
    """机器人上报巡检结果 (cmd=104)。无需认证。"""
    try:
        raw = await request.body()
        body = json.loads(raw) if raw else {}
        sid = body.get("substationMapsId") or body.get("substation_maps_id", "")
        body["substation_maps_id"] = sid
    except Exception:
        return {"ok": False, "msg": "invalid json"}

    inspection_id = body.get("inspection_id", "")
    _plan_report(body, request, db)
    run = db.query(InspectionRun).filter(InspectionRun.inspection_id == inspection_id).first()
    if run is None:
        robot = _resolve_robot(body, request, db)
        print(f"[report/result] robot_id={body.get('robot_id','(missing)')} X-Real-IP={request.headers.get('X-Real-IP','(missing)')} → matched robot_pk={robot.id if robot else None}", flush=True)
        run = InspectionRun(
            inspection_id=inspection_id,
            robot_pk=robot.id if robot else None,
            status="started",
            start_time=_parse_time(body.get("start_time", "")) or datetime.utcnow(),
        )
        db.add(run)
        db.flush()
    elif run.robot_pk is None:
        # 旧记录 robot_pk 为空, 有 robot_id 时补上
        robot = _resolve_robot(body, request, db)
        if robot:
            run.robot_pk = robot.id

    inserted = 0
    results = body.get("results", [])
    for item in results:
        existing = db.query(InspectionResult).filter(
            InspectionResult.run_id == run.id,
            InspectionResult.waypoint_id == item.get("waypoint_id", ""),
            InspectionResult.action_id == item.get("action_id", ""),
        ).first()
        if existing:
            existing.code = item.get("code", 0)
            existing.picture = item.get("picture") or existing.picture
            existing.infrared = item.get("infrared") or existing.infrared
            existing.media = item.get("media") or existing.media
            existing.inplace_ts = str(item.get("inplace_timestamp", "")) or existing.inplace_ts
            if item.get("thermometry_points"):
                existing.thermometry_json = item["thermometry_points"]
            if item.get("env"):
                existing.env_json = item["env"]
            if item.get("pdd_data"):
                existing.pdd_json = item["pdd_data"]
        else:
            result = InspectionResult(
                run_id=run.id, robot_pk=run.robot_pk,
                waypoint_id=item.get("waypoint_id", ""),
                action_id=item.get("action_id", ""),
                code=item.get("code", 0),
                picture=item.get("picture", ""),
                infrared=item.get("infrared", ""),
                media=item.get("media", ""),
                inplace_ts=str(item.get("inplace_timestamp", "")),
                thermometry_json=item.get("thermometry_points"),
                env_json=item.get("env"),
                pdd_json=item.get("pdd_data"),
            )
            db.add(result)
            inserted += 1

    db.commit()
    logger.info("[report/result] inspection_id=%s results=%d inserted=%d", inspection_id, len(results), inserted)
    return {"ok": True, "inserted": inserted, "updated": len(results) - inserted}


@router.post("/report/finish")
async def report_finish(request: Request, db: Session = Depends(get_db)):
    """机器人上报巡检结果上传结束 (cmd=105)。无需认证。"""
    try:
        raw = await request.body()
        body = json.loads(raw) if raw else {}
        sid = body.get("substationMapsId") or body.get("substation_maps_id", "")
        body["substation_maps_id"] = sid
    except Exception:
        return {"ok": False, "msg": "invalid json"}

    inspection_id = body.get("inspection_id", "")
    execution = _plan_report(body, request, db)
    if execution:
        from ..services.inspection_dispatch import active_id
        if inspection_id == active_id(execution) and execution.status not in ("waiting_transition", "done", "canceled", "closed", "failed"):
            execution.message = "巡检结果上传结束；执行状态以上报或状态查询为准"
    run = db.query(InspectionRun).filter(InspectionRun.inspection_id == inspection_id).first()
    if run:
        run.status = "done"
        run.finish_time = _parse_time(body.get("last_upload_time", "")) or datetime.utcnow()
        total_results = db.query(InspectionResult).filter(InspectionResult.run_id == run.id).count()
        run.remark = f"total_actions={body.get('total',0)} uploaded={body.get('uploaded',0)} results_in_db={total_results}"
        db.commit()
        logger.info("[report/finish] inspection_id=%s total=%s uploaded=%s",
                    inspection_id, body.get("total"), body.get("uploaded"))
    else:
        logger.warning("[report/finish] 未找到 inspection_id=%s", inspection_id)
    return {"ok": True}


# 进度缓存(内存, 简单实现)
_progress_cache: dict = {}


@router.post("/report/progress")
async def report_progress(request: Request, db: Session = Depends(get_db)):
    """机器人上报巡检进度 (cmd=106)。无需认证。"""
    try:
        raw = await request.body()
        body = json.loads(raw) if raw else {}
    except Exception:
        return {"ok": False}
    _plan_report(body, request, db)
    _progress_cache[body.get("inspection_id", "")] = {
        "waypoint_id": body.get("waypoint_id", ""),
        "action_id": body.get("action_id", ""),
        "progress": body.get("progress", 0),
        "total_waypoint": body.get("total_waypoint", 0),
        "current_waypoint": body.get("current_waypoint", 0),
        "updated_at": datetime.utcnow().isoformat(),
    }
    return {"ok": True}


# ========== 前端查询 API ==========

def _log_service():
    """巡检日志的查询/序列化逻辑全在 ``services/inspection_log.py``（可单测）。

    路由只做鉴权 + 参数校验 + 拼响应。这里用函数内 import 是为了避免模块级
    循环（service 引 models，router 引 service，两者都引 database）。
    """
    from ..services import inspection_log
    return inspection_log


def _serialize_action(row):
    return _log_service().serialize_action(row)


def _serialize_point(row, *, action=None, flows=None, archive=None):
    return _log_service().serialize_point(row, action=action, flows=flows, archive=archive)


def _action_log_summary(rows):
    return _log_service().action_status_summary(rows)


@router.get("/runs")
def list_runs(robot_pk: Optional[int] = None, limit: int = 50,
              page: Optional[int] = None, page_size: int = Query(20, ge=1, le=200),
              status: str = "", keyword: str = "",
              start: str = "", end: str = "",
              db: Session = Depends(get_db), _=Depends(get_current_user)):
    """巡检执行记录列表 —— **数据库里的全部 InspectionRun**，不限于某一台机器人。

    两种调用形态：

    - **分页**（巡检日志页用）：传 ``page``，返回 ``{"total": n, "items": [...]}``，
      支持 ``robot_pk`` / ``status`` / ``keyword`` / ``start`` / ``end`` 筛选。
    - **旧形态**（其它页面已在用）：不传 ``page``，返回**裸数组**、``limit`` 截断，
      字段是旧集合的超集 —— 老调用方不受影响，不用跟着改。

    ``robot_pk`` 不传即"全部机器人"；``robot_name`` 会一并带出，否则前端拿着
    外键没法显示是哪台机器。
    """
    from ..services import inspection_log as log_svc

    filters = {"robot_pk": robot_pk, "status": status, "keyword": keyword,
               "start": start, "end": end}

    if page is None:
        runs = (log_svc.query_runs(db, **filters)
                .order_by(InspectionRun.start_time.desc().nullslast(),
                          InspectionRun.id.desc())
                .limit(max(1, int(limit or 50))).all())
    else:
        page = max(1, int(page))
        runs = log_svc.page_runs(db, page=page, page_size=page_size, **filters)

    run_ids = [r.id for r in runs]
    names = log_svc.robot_names(db, [r.robot_pk for r in runs])
    counts = log_svc.action_counts(db, run_ids)
    legacy = log_svc.legacy_counts(db, run_ids)
    points = log_svc.detect_counts(db, run_ids)

    items = [log_svc.summarize_run(
        r,
        counts=counts.get(r.id),
        legacy=legacy.get(r.id),
        points=points.get(r.id),
        names=names,
        progress=_progress_cache.get(r.inspection_id, {}),
    ) for r in runs]

    if page is None:
        return items
    return {"total": log_svc.count_runs(db, filters), "page": page,
            "page_size": page_size, "items": items}


@router.get("/runs/{run_id}/actions")
def run_actions(run_id: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """一次巡检的动作结果明细（新表 ``inspection_action_results``）。

    跟 ``/runs/{id}`` 的区别：那个接口看的是机器人上报的**旧表**（按航点分组、
    带校准数据），这里看的是 FMS 自己记的账本 —— 有分发状态、有执行耗时、
    有占位行（卡住不动的动作也在里面）。
    """
    run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
    if not run:
        raise HTTPException(404, "巡检记录不存在")

    rows = (db.query(InspectionActionResult)
            .filter(InspectionActionResult.run_id == run_id)
            .order_by(InspectionActionResult.floor, InspectionActionResult.waypoint_index,
                      InspectionActionResult.action_seq, InspectionActionResult.id).all())
    return {
        "run_id": run_id,
        "inspection_id": run.inspection_id,
        "summary": _action_log_summary(rows),
        "items": [_serialize_action(row) for row in rows],
    }


@router.get("/runs/{run_id}/points")
def run_points(run_id: int, kind: str = "", db: Session = Depends(get_db),
               _=Depends(get_current_user)):
    """一次巡检的测点结果（测温点 / 检测点）。

    ``kind`` 可传 ``thermometry`` 或 ``detect`` 只取一类；不传就是全部。
    同时把动作结果一次查出来做 map，避免逐测点回查（一个动作下挂了多个测点）。
    """
    run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
    if not run:
        raise HTTPException(404, "巡检记录不存在")

    q = db.query(InspectionPointResult).filter(InspectionPointResult.run_id == run_id)
    if kind:
        q = q.filter(InspectionPointResult.kind == kind)
    rows = q.order_by(InspectionPointResult.action_result_id,
                      InspectionPointResult.seq, InspectionPointResult.id).all()

    action_rows = (db.query(InspectionActionResult)
                   .filter(InspectionActionResult.run_id == run_id).all())
    by_id = {row.id: row for row in action_rows}

    # 旁路数据：账本里只有流程引用 id 与测点 id，检视器要显示的是名字。
    # 一次查好传下去（别在 serialize_point 里逐条查：一个动作下可能挂多个测点）。
    # 两处都做了容错 —— 流程目录 / 档案文件坏了只是少两栏，不该让详情接口 500。
    flows = _log_service().detect_flow_names()
    archive = _log_service().point_archive_map({row.point_id for row in rows if row.point_id})

    summary = {"total": len(rows), "kind": {}, "status": {}, "passed": 0, "failed": 0}
    for row in rows:
        kk = row.kind or "thermometry"
        summary["kind"][kk] = summary["kind"].get(kk, 0) + 1
        ss = row.status or "pending"
        summary["status"][ss] = summary["status"].get(ss, 0) + 1
        if row.passed is True:
            summary["passed"] += 1
        elif row.passed is False:
            summary["failed"] += 1
    return {
        "run_id": run_id,
        "inspection_id": run.inspection_id,
        "summary": summary,
        "items": [_serialize_point(row, action=by_id.get(row.action_result_id),
                                   flows=flows, archive=archive) for row in rows],
    }


@router.get("/runs/{run_id}/summary")
def run_summary(run_id: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """**单条**巡检记录的列表行（与 ``/runs`` 的 items 同形状）。

    给独立详情页 ``/inspection/log/:id`` 用：那个页面手里只有一个 id（用户直接输 URL
    或从别处点进来），标题栏要的 ``robot_name`` / ``status`` / ``remark`` 得单独取。

    ⚠️ 别让前端退化成"拉一页 200 条再本地 find"——记录一多就漏，而且每次打开详情
    都要多传 200 条。这里复用列表页同一套聚合口径（``summarize_run``），保证
    "同一个 id，从列表进来的和直接输 URL 进来的，看到的数字完全一样"。
    """
    from ..services import inspection_log as log_svc

    run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
    if not run:
        raise HTTPException(404, "巡检记录不存在")

    names = log_svc.robot_names(db, [run.robot_pk])
    counts = log_svc.action_counts(db, [run_id]).get(run_id)
    legacy = log_svc.legacy_counts(db, [run_id]).get(run_id)
    points = log_svc.detect_counts(db, [run_id]).get(run_id)

    return log_svc.summarize_run(
        run, counts=counts, legacy=legacy, points=points, names=names,
        progress=_progress_cache.get(run.inspection_id, {}),
    )


@router.post("/runs/{run_id}/report/generate")
def generate_report_async(run_id: int, regenerate: bool = False, _=Depends(get_current_user)):
    """异步触发生成巡检报表。

    报表生成是耗时操作（几十上百个检测框），不能同步等。
    提交后台任务后立即返回，前端轮询 ``/report/status`` 查状态。

    Args:
        regenerate: 是否重新生成（覆盖旧报表）。默认 False，已生成过就直接返回。
    """
    from ..services.report_task import submit_report_task
    return submit_report_task(run_id, regenerate=regenerate)


@router.get("/runs/{run_id}/report/status")
def get_report_status(run_id: int, _=Depends(get_current_user)):
    """查询报表生成状态："" / pending / running / done / failed。"""
    from ..services.report_task import get_report_status
    return get_report_status(run_id)


@router.get("/runs/{run_id}/report/download")
def download_report(run_id: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """下载已生成的巡检报表 Excel。"""
    run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
    if not run:
        raise HTTPException(404, "巡检记录不存在")
    if run.report_status != "done" or not run.report_path:
        raise HTTPException(400, "报表尚未生成完成，请先生成")
    path = Path(run.report_path)
    if not path.exists():
        raise HTTPException(404, "报表文件已丢失，请重新生成")
    return FileResponse(
        str(path),
        filename=path.name,
        media_type='application/vnd.openxmlformats-officedocument.spreadsheetml.sheet',
    )


@router.get("/runs/{run_id}")
def run_detail(run_id: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """单次巡检详情(含所有动作结果)。"""
    run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
    if not run:
        raise HTTPException(404, "巡检记录不存在")

    results = db.query(InspectionResult).filter(
        InspectionResult.run_id == run_id
    ).order_by(InspectionResult.id).all()

    # 按 waypoint_id 分组
    waypoints_map: dict = {}
    for r in results:
        wp_id = r.waypoint_id or "unknown"
        if wp_id not in waypoints_map:
            waypoints_map[wp_id] = []
        waypoints_map[wp_id].append({
            "id": r.id,
            "action_id": r.action_id,
            "code": r.code,
            "picture": r.picture,
            "infrared": r.infrared,
            "media": r.media,
            "inplace_ts": r.inplace_ts,
            "thermometry": r.thermometry_json,
            "env": r.env_json,
            "pdd": r.pdd_json,
        })

    waypoints = [{"waypoint_id": k, "actions": v} for k, v in waypoints_map.items()]

    # 扫描校准数据目录, 关联到航点/动作
    calib_data = {}
    if run.robot_pk and run.inspection_id:
        calib_base = DATA_DIR / "robot" / str(run.robot_pk) / "inspection" / run.inspection_id / "multiple"
        if calib_base.exists():
            for wps_dir in calib_base.iterdir():
                if not wps_dir.is_dir() or not wps_dir.name.startswith("wps_"):
                    continue
                wp_id = wps_dir.name[4:]  # 去掉 wps_ 前缀
                for sess_dir in wps_dir.iterdir():
                    if not sess_dir.is_dir():
                        continue
                    calib_type = "xaxis" if "_xaxis" in sess_dir.name else ("ptz" if "_ptz" in sess_dir.name else None)
                    if not calib_type:
                        continue
                    node_id = sess_dir.name.replace("_xaxis", "").replace("_ptz", "")
                    # 读 metrics.json
                    mf = sess_dir / "metrics.json"
                    metrics = {}
                    if mf.exists():
                        try:
                            metrics = json.loads(mf.read_text(encoding="utf-8"))
                        except Exception:
                            pass
                    # 收集根目录过程图
                    images = []
                    for f in sorted(sess_dir.iterdir()):
                        if f.is_file() and f.suffix in ('.jpg', '.png'):
                            images.append(f.name)
                    # 按轮收集迭代子目录的图片
                    iter_images: list[dict] = []
                    for sub in sorted(sess_dir.iterdir()):
                        if sub.is_dir() and sub.name.isdigit():
                            iter_imgs = sorted(f.name for f in sub.iterdir() if f.suffix in ('.jpg', '.png'))
                            if iter_imgs:
                                iter_images.append({"iter": int(sub.name), "images": iter_imgs})
                    key = f"{wp_id}/{node_id}_{calib_type}"
                    calib_data[key] = {
                        "type": calib_type,
                        "node_id": node_id,
                        "wp_id": wp_id,
                        "metrics": metrics,
                        "images": images,
                        "iterations": iter_images,
                    }

    # 查 WaypointsTree 获取名称映射 + 预期航点/动作列表
    wp_names: dict = {}
    expected_waypoints: list[dict] = []  # [{id, name, actions: [{id, name}]}]
    if run.robot_pk:
        tree_path = DATA_DIR / "robot" / str(run.robot_pk) / "WaypointsTree.json"
        if tree_path.exists():
            try:
                tree = json.loads(tree_path.read_text(encoding="utf-8"))
                def _walk_names(node: dict):
                    if not node:
                        return
                    nid = node.get("id", "")
                    nm = node.get("name", "") or node.get("steer_point_name", "")
                    if nid and nm:
                        wp_names[nid] = nm
                    # 收集航点+动作
                    if node.get("nodeType") == "WaypointNode":
                        actions = []
                        for child in node.get("children", []):
                            if child.get("nodeType") == "ActionNode":
                                actions.append({"id": child.get("id", ""), "name": child.get("name", "") or child.get("steer_point_name", "")})
                        expected_waypoints.append({"id": nid, "name": nm, "actions": actions})
                    for child in node.get("children", []):
                        _walk_names(child)
                _walk_names(tree)
            except Exception:
                pass

    # 已上报的 action_id 集合
    reported_action_ids = {r.action_id for r in results if r.action_id}
    # 已上报的 waypoint_id 集合
    reported_wp_ids = {r.waypoint_id for r in results if r.waypoint_id}

    # 找缺失的动作
    missing_actions: list[dict] = []
    for wp in expected_waypoints:
        for act in wp.get("actions", []):
            if act["id"] not in reported_action_ids:
                missing_actions.append({"waypoint": wp["name"], "action": act["name"] or act["id"][:12]})

    # 失败的动作 (code != 0)
    failed_actions: list[dict] = []
    for r in results:
        if r.code != 0:
            wp_name = wp_names.get(r.waypoint_id, r.waypoint_id[:12] if r.waypoint_id else "")
            act_name = wp_names.get(r.action_id, r.action_id[:12] if r.action_id else "")
            failed_actions.append({"waypoint": wp_name, "action": act_name, "code": r.code})

    # 给 waypoints 加名称
    for wp in waypoints:
        wp["waypoint_name"] = wp_names.get(wp["waypoint_id"], "")
        for action in wp["actions"]:
            action["action_name"] = wp_names.get(action.get("action_id", ""), "")

    # 给 calib_data 加名称
    for key, val in calib_data.items():
        val["wp_name"] = wp_names.get(val.get("wp_id", ""), "")
        val["node_name"] = wp_names.get(val.get("node_id", ""), "")

    # action_id → waypoint_id 反查 (PTZ 校准的 wp_id 实际存的是 action_id, 需还原所属航点)
    action_wp: dict = {}
    for r in results:
        if r.action_id and r.waypoint_id:
            action_wp[r.action_id] = r.waypoint_id

    # PTZ 校准的 wp_id 修正为真实航点 ID, 前端按 waypoint_id 匹配才能找到
    for key, val in calib_data.items():
        if val.get("type") == "ptz" and val.get("wp_id") in action_wp:
            val["wp_id"] = action_wp[val["wp_id"]]
            val["wp_name"] = wp_names.get(val["wp_id"], "")

    # 结论摘要
    total_actions = sum(len(wp.get("actions", [])) for wp in waypoints)
    reported_actions = len(results)
    success_actions = sum(1 for r in results if r.code == 0)
    fail_actions = reported_actions - success_actions
    # 校准统计
    xaxis_calibs = [v for v in calib_data.values() if v.get("type") == "xaxis"]
    ptz_calibs = [v for v in calib_data.values() if v.get("type") == "ptz"]
    xaxis_converged = sum(1 for v in xaxis_calibs if v.get("metrics", {}).get("converged"))
    ptz_converged = sum(1 for v in ptz_calibs if v.get("metrics", {}).get("converged"))

    def _fmt_unconverged(calibs: list) -> list:
        """未收敛列表: 【航点名】:【动作名】。PTZ 的 wp_id 是 action_id, 先还原到航点。"""
        out = []
        for v in calibs:
            if v.get("metrics", {}).get("converged"):
                continue
            wp_id = v.get("wp_id", "")
            node_id = v.get("node_id", "")
            real_wp_id = action_wp.get(wp_id) or action_wp.get(node_id) or wp_id
            wp_name = wp_names.get(real_wp_id) or (real_wp_id[:8] if real_wp_id else "")
            node_name = v.get("node_name") or wp_names.get(node_id) or (node_id[:8] if node_id else "")
            out.append(f"{wp_name}: {node_name}")
        return out

    xaxis_unconverged = _fmt_unconverged(xaxis_calibs)
    ptz_unconverged = _fmt_unconverged(ptz_calibs)
    summary = {
        "total_waypoints": len(waypoints),
        "total_actions": total_actions,
        "expected_waypoints": len(expected_waypoints),
        "expected_actions": sum(len(wp.get("actions", [])) for wp in expected_waypoints),
        "reported_actions": reported_actions,
        "success_actions": success_actions,
        "fail_actions": fail_actions,
        "missing_count": len(missing_actions),
        "missing_actions": missing_actions[:50],  # 最多返回50条
        "failed_actions": failed_actions[:50],
        "xaxis_total": len(xaxis_calibs),
        "xaxis_converged": xaxis_converged,
        "xaxis_unconverged_names": xaxis_unconverged,
        "ptz_total": len(ptz_calibs),
        "ptz_converged": ptz_converged,
        "ptz_unconverged_names": ptz_unconverged,
    }

    return {
        "id": run.id,
        "inspection_id": run.inspection_id,
        "robot_pk": run.robot_pk,
        "status": run.status,
        "start_time": run.start_time.isoformat() if run.start_time else None,
        "finish_time": run.finish_time.isoformat() if run.finish_time else None,
        "remark": run.remark,
        "waypoints": waypoints,
        "calib_data": calib_data,
        "summary": summary,
        "progress": _progress_cache.get(run.inspection_id, {}),
    }


@router.get("/calib-images/{rid}/{inspection_id}/{path:path}")
def get_calib_image(rid: int, inspection_id: str, path: str):
    """获取校准过程图(ORB debug images)。"""
    file_path = DATA_DIR / "robot" / str(rid) / "inspection" / inspection_id / path
    if not file_path.exists():
        raise HTTPException(404, "图片不存在")
    return FileResponse(str(file_path))



# ============================================================ 算法推理回调
#
# 算法服务（ai_server.py）识别完成后，POST 到这个接口传递结果。
# 调用时我们会带上 taskResultId（= action_result_id），算法服务原样回调回来。

@router.post("/report/detect_callback")
async def detect_callback(request: Request, db: Session = Depends(get_db)):
    """算法服务识别结果回调接口。

    算法服务识别完成后，POST 到这个接口传递结果。
    请求体是 JSON，格式由算法服务决定。
    """
    try:
        body = await request.json()
    except Exception:
        logger.warning("算法回调无法解析为 JSON")
        raise HTTPException(400, "请求体必须是 JSON")

    # 回调 body 里的 algorithmTempId 就是我们提交时传的动作结果 id
    arid_raw = body.get("algorithmTempId")
    logger.info("收到算法回调: algorithmTempId=%s body=%s",
                arid_raw, str(body)[:500])

    # 记录算法推理服务的最终处理结果到对应动作行
    if arid_raw not in (None, ""):
        try:
            arid = int(arid_raw)
            action = db.query(InspectionActionResult).filter(
                InspectionActionResult.id == arid).first()
            if action is not None:
                action.infer_result_json = body
                db.commit()
                logger.info("算法处理结果已记录 action_result_id=%d code=%s",
                            arid, body.get("code"))
                # 继续跑该动作各检测框绑定的检测流程，按条件产生告警、回写测点
                try:
                    from ..services.alarm_processor import process_callback
                    stats = process_callback(db, action, body)
                    db.commit()
                    logger.info("检测流程处理完成 action_result_id=%d %s",
                                arid, stats)
                except Exception:  # noqa: BLE001 - 流程判定失败不影响回调应答
                    db.rollback()
                    logger.exception("检测流程处理失败 action_result_id=%d", arid)
            else:
                logger.warning("算法回调找不到动作结果行 id=%s", arid_raw)
        except (TypeError, ValueError):
            logger.warning("算法回调 algorithmTempId 非整数: %s", arid_raw)

    return {"code": 0, "msg": "ok"}



@router.post("/runs/{run_id}/actions/{action_result_id}/trigger_detect")
def trigger_detect(run_id: int, action_result_id: int, db: Session = Depends(get_db),
                   _=Depends(get_current_user)):
    """手动触发指定动作的检测。

    把动作的 dispatch_status 改成 pending，让 task_executor 下一轮轮询时捡起来处理。
    """
    action = db.query(InspectionActionResult).filter(
        InspectionActionResult.id == action_result_id,
        InspectionActionResult.run_id == run_id,
    ).first()
    if not action:
        raise HTTPException(404, "动作结果不存在")

    # 重置分发状态，让执行器重新处理
    action.dispatch_status = "pending"
    action.dispatch_error = ""
    action.dispatched_at = None
    action.dispatch_attempts = 0
    db.commit()

    logger.info("手动触发检测: run_id=%d action_result_id=%d action_id=%s",
                run_id, action_result_id, action.action_id)

    return {"code": 0, "msg": "已提交检测任务", "action_result_id": action_result_id}



@router.post("/runs/{run_id}/cancel")
def cancel_run(run_id: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """取消一次巡检执行。

    把巡检记录状态改成 canceled，未完成的动作也标记为 canceled。
    """
    run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
    if not run:
        raise HTTPException(404, "巡检记录不存在")

    if run.status in ("done", "failed", "canceled"):
        raise HTTPException(400, f"巡检已经是 {run.status} 状态，无法取消")

    # 标记巡检为 canceled
    run.status = "canceled"
    if not run.finish_time:
        run.finish_time = datetime.utcnow()

    # 未完成的动作也标记为 canceled
    actions = db.query(InspectionActionResult).filter(
        InspectionActionResult.run_id == run_id,
        InspectionActionResult.status.in_(("pending",)),
    ).all()
    for a in actions:
        a.status = "canceled"

    db.commit()

    logger.info("巡检已取消: run_id=%d inspection_id=%s 取消了 %d 个未完成动作",
                run_id, run.inspection_id, len(actions))

    return {"code": 0, "msg": "巡检已取消", "canceled_actions": len(actions)}
