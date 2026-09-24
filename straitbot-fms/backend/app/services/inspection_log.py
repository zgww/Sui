"""巡检日志查询：把 ``inspection_runs`` / ``inspection_action_results`` /
``inspection_point_results`` 三张表读成前端能直接渲染的 dict。

## 为什么单独一个模块

路由里塞筛选 + 聚合 + 序列化会变成几百行的"读接口巨兽"，而这个页面的口径
（哪些状态算异常、进度怎么算、超时多久算卡住）是需要单独测的**业务规则**。
所以这里只做纯函数式的查询与转换，**不持有 session、不开事务、不 flush**；
路由负责鉴权与参数校验，前端负责怎么摆。

## 与旧表 ``inspection_results`` 的关系

旧表是机器人 cmd=104 直接上报的原始记录（一航点一动作一条），新表是
FMS 自己按任务结构先占位再回填的账本。**两张表并存**：

- ``list_runs`` 同时取新旧两套计数，新表有数据就用新表（带分发与检测信息），
  没有就回落旧表 —— 老巡检记录不会因为这次改造而变空。
- ``run_actions`` / ``run_points`` 只看新表：旧表没有分发状态、也没有测点维度，
  硬凑出来的字段是假的，不如不显示。

## 状态口径

``InspectionRun.status``：started / done / failed / canceled。
``InspectionActionResult.status``：pending / ok / failed / skipped —— 这是
**动作执行结果**；数据有没送出去看 ``dispatch_status``（pending/done/failed），
两者是两件事，别混。
"""
from __future__ import annotations

import logging
from datetime import datetime, timedelta
from typing import Any, Optional

from sqlalchemy import case, func, or_
from sqlalchemy.orm import Session

from ..models import (
    InspectionActionResult,
    InspectionPointResult,
    InspectionResult,
    InspectionRun,
    Robot,
)

logger = logging.getLogger(__name__)

# —— run 状态 ——
RUN_STARTED = "started"
RUN_DONE = "done"
RUN_FAILED = "failed"
RUN_CANCELED = "canceled"
RUN_STATUSES = (RUN_STARTED, RUN_DONE, RUN_FAILED, RUN_CANCELED)

# —— 动作结果状态 ——
STATUS_PENDING = "pending"
STATUS_OK = "ok"
STATUS_FAILED = "failed"
STATUS_SKIPPED = "skipped"

# —— 分发状态 ——
DISPATCH_PENDING = "pending"
DISPATCH_DONE = "done"
DISPATCH_FAILED = "failed"
DISPATCH_STATUSES = (DISPATCH_PENDING, DISPATCH_DONE, DISPATCH_FAILED)

# —— 测点来源 ——
KIND_THERMOMETRY = "thermometry"
KIND_DETECT = "detect"

# 动作类型（设备协议口径）
ACTION_TYPE_PICTURE = 1
ACTION_TYPE_THERMOMETRY = 2
ACTION_TYPE_VIDEO = 3

#: 一个 ``started`` 的 run 多久没动静就提醒"可能卡住了"。机器人跑一整层楼
#: 可能十几分钟，所以给得比较宽 —— 这个数只是给前端提示，不做任何状态改写。
STALL_HOURS = 2

#: 关键字筛选时会 ``contains`` 的字符串列，只这些（数字列不参与）。
_KEYWORD_FIELDS = ("inspection_id", "remark")

#: 动作**状态值** -> 计数**桶名**。
#:
#: 这两个词看着像同一件事，其实不是：状态叫 ``ok``（动作执行成功），而页面上要
#: 说的是"完成了几条"（``done``）。直接拿状态值当键会得到一个 ``done=0`` 但
#: ``total`` 正常的字典 —— 进度条 0% 却查不出错。
_ACTION_BUCKET = {
    STATUS_OK: "done",
    STATUS_FAILED: "failed",
    STATUS_SKIPPED: "skipped",
    STATUS_PENDING: "pending",
}


# ------------------------------------------------------------------ 小工具
def _iso(value: Optional[datetime]) -> Optional[str]:
    """datetime -> ISO 字符串。**不带时区**，与原接口一致（前端 ``new Date()`` 按本地解析）。"""
    return value.isoformat() if value else None


def _parse_dt(value: Any) -> Optional[datetime]:
    """把查询参数里的时间字符串宽容地解析成 datetime；认不出返回 None。

    认得出 ``2026-09-22`` 与 ``2026-09-22 14:30`` / ``2026-09-22T14:30:00``——
    前端 input 直接传原始字符串，不该因为它多带了个空格就 500。
    """
    if value is None or isinstance(value, datetime):
        return value
    text = str(value).strip()
    if not text:
        return None
    text = text.replace("T", " ")
    for fmt in ("%Y-%m-%d %H:%M:%S", "%Y-%m-%d %H:%M", "%Y-%m-%d"):
        try:
            return datetime.strptime(text, fmt)
        except ValueError:
            continue
    return None


def _pct(done: int, total: int) -> int:
    """完成百分比，0~100 取整。``total`` 为 0 时返回 0（不是 100，也不是除零）。"""
    if total <= 0:
        return 0
    return max(0, min(100, int(round(done * 100.0 / total))))


def _count(value: Any) -> int:
    """把聚合结果收成 int。

    SQLite 在某些布尔聚合下会回 ``True``/``None`` 而不是数字（见
    ``legacy_counts`` 的说明），这里统一收口，免得 ``int(True)`` 悄悄变成 1
    混进计数里。
    """
    if isinstance(value, bool):
        # 布尔是 int 的子类，int(True)==1 —— SQLite 布尔聚合的坑，别让它混进计数
        return 1 if value else 0
    if value is None:
        return 0
    try:
        return int(value)
    except (TypeError, ValueError):
        return 0


def _text(value: Any, limit: int = 0) -> str:
    """兜底成字符串。``None`` -> ``""``；截断是为了别把整段 traceback 塞进列表响应。"""
    if value is None:
        return ""
    text = str(value)
    return text[:limit] if limit > 0 else text


def _action_type_name(value: Any) -> str:
    try:
        code = int(value)
    except (TypeError, ValueError):
        return ""
    return {ACTION_TYPE_PICTURE: "拍照",
            ACTION_TYPE_THERMOMETRY: "测温",
            ACTION_TYPE_VIDEO: "录像"}.get(code, "")


def _effective_status(run_status: str, total: int, done: int, start: Optional[datetime],
                      *, now: Optional[datetime] = None) -> str:
    """列表里显示的"有效状态"。

    库里 ``status`` 只在巡检**开始**与**结束**（cmd=105）时改。机器人断电、
    上报丢了，行就永远停在 ``started``。这里不改库，只在**展示口径**上把
    "开跑很久、一个动作都没回填"的标成 ``stalled``，让人一眼看出哪次没跑完 ——
    否则日志页会挂着一条半年前的"进行中"。
    """
    if run_status != RUN_STARTED:
        return run_status
    if done > 0:
        return RUN_STARTED
    if start is None:
        return RUN_STARTED
    ref = now or datetime.utcnow()
    if ref - start > timedelta(hours=STALL_HOURS):
        return "stalled"
    return RUN_STARTED


# ------------------------------------------------------------------ 查询
def query_runs(db: Session, *, robot_pk: Optional[int] = None, status: str = "",
               keyword: str = "", start: Any = None, end: Any = None):
    """按筛选条件造 ``InspectionRun`` 查询。

    只加 ``where``，不排序不分页——调用方拿它既能 ``count()`` 又能取页，
    两次查询条件完全一致，不会因为复制一遍筛选逻辑而走偏。
    """
    q = db.query(InspectionRun)
    if robot_pk is not None:
        q = q.filter(InspectionRun.robot_pk == robot_pk)
    if status:
        q = q.filter(InspectionRun.status == status)
    if keyword.strip():
        pattern = keyword.strip()
        q = q.filter(or_(*[getattr(InspectionRun, f).contains(pattern, autoescape=True)
                           for f in _KEYWORD_FIELDS]))
    begin = _parse_dt(start)
    if begin is not None:
        q = q.filter(InspectionRun.start_time >= begin)
    finish = _parse_dt(end)
    if finish is not None:
        # 只给了日期（没给时分秒）就按"当天结束"算，否则 2026-09-22 会把
        # 9-22 当天的记录全滤掉 —— 用户填那天是想看那天。
        if isinstance(end, str) and len(str(end).strip()) <= 10:
            finish = finish + timedelta(days=1) - timedelta(seconds=1)
        q = q.filter(InspectionRun.start_time <= finish)
    return q


def count_runs(db: Session, filters: dict) -> int:
    return query_runs(db, **filters).count()


def page_runs(db: Session, *, page: int = 1, page_size: int = 20, **filters
              ) -> list[InspectionRun]:
    """取一页 run。排序：``start_time desc nullslast`` 再 ``id desc``。

    加 id 兜底是因为 ``start_time`` 可能为 NULL（老数据）或有并列（同一秒开跑），
    只按时间排的话翻页会跳行/重复。
    """
    page = max(1, int(page or 1))
    page_size = max(1, int(page_size or 20))
    return (query_runs(db, **filters)
            .order_by(InspectionRun.start_time.desc().nullslast(), InspectionRun.id.desc())
            .offset((page - 1) * page_size).limit(page_size).all())


def robot_names(db: Session, robot_pks: list[Optional[int]]) -> dict:
    """``robots.id`` -> 名称。列表页要显示"哪台机器人跑的"，而库里只有外键。"""
    ids = sorted({int(p) for p in robot_pks if p is not None})
    if not ids:
        return {}
    rows = db.query(Robot.id, Robot.name).filter(Robot.id.in_(ids)).all()
    return {int(rid): _text(name) for rid, name in rows}


def action_counts(db: Session, run_ids: list[int]) -> dict:
    """新表计数：``run_id -> {total, done, failed, pending, skipped, other, statuses}``。

    用一条 group_by 查出来，不在循环里按 run 逐条 count —— 列表 20 行就是
    80 次查询，看着能用，数据一多就拖垮页面。

    ⚠️ **状态值不能直接当桶的键**：``status`` 存的是 ``ok``，而桶要的是
    ``done``（"完成了几条"）。第一版把 ``ok`` 直接塞进字典，于是
    ``{"total":3, "done":0, ..., "ok":3}`` —— 进度条永远 0%，``total`` 又是对的，
    最容易被当成"前端算错"而查半天。所以这里显式过一张映射表，
    认不出的状态进 ``other``，同时在 ``statuses`` 里留原样，不用为了新状态改代码。
    """
    out: dict[int, dict] = {}
    if not run_ids:
        return out
    rows = (db.query(
        InspectionActionResult.run_id,
        InspectionActionResult.status,
        func.count(InspectionActionResult.id),
    ).filter(InspectionActionResult.run_id.in_(run_ids))
        .group_by(InspectionActionResult.run_id, InspectionActionResult.status).all())
    for run_id, status, count in rows:
        bucket = out.setdefault(int(run_id), {"total": 0, "done": 0, "failed": 0,
                                              "pending": 0, "skipped": 0, "other": 0,
                                              "statuses": {}})
        n = _count(count)
        key = _text(status) or STATUS_PENDING
        bucket["total"] += n
        bucket["statuses"][key] = bucket["statuses"].get(key, 0) + n
        target = _ACTION_BUCKET.get(key)
        if target:
            bucket[target] += n
        else:
            bucket[key] = bucket.get(key, 0) + n
            bucket["other"] += n
    return out


def legacy_counts(db: Session, run_ids: list[int]) -> dict:
    """旧表计数：``run_id -> {total, done}``。

    ``inspection_results.code == 0`` 表示上报成功，算"完成"。

    ⚠️ 这里必须用 ``case(...).sum()`` 而不是 ``func.sum(布尔表达式)``：
    SQLAlchemy 把 ``sum(col == 0)`` 推断成 Boolean，到了 SQLite 上被聚合器
    直接按"有没有真值"压成 ``True``/``None`` —— 于是 3 条成功也只数出 1 条，
    进度条永远卡在个位数。``case`` 给的是显式 1/0，才是真的求和。
    """
    out: dict[int, dict] = {}
    if not run_ids:
        return out
    ok_flag = case((func.coalesce(InspectionResult.code, 0) == 0, 1), else_=0)
    rows = (db.query(
        InspectionResult.run_id,
        func.count(InspectionResult.id),
        func.sum(ok_flag),
    ).filter(InspectionResult.run_id.in_(run_ids))
        .group_by(InspectionResult.run_id).all())
    for run_id, total, done in rows:
        out[int(run_id)] = {"total": _count(total), "done": _count(done)}
    return out


def detect_counts(db: Session, run_ids: list[int]) -> dict:
    """测点计数（按 ``kind``）：``run_id -> {points, thermometry, detect}``。"""
    out: dict[int, dict] = {}
    if not run_ids:
        return out
    rows = (db.query(
        InspectionPointResult.run_id,
        InspectionPointResult.kind,
        func.count(InspectionPointResult.id),
    ).filter(InspectionPointResult.run_id.in_(run_ids))
        .group_by(InspectionPointResult.run_id, InspectionPointResult.kind).all())
    for run_id, kind, count in rows:
        bucket = out.setdefault(int(run_id), {"points": 0, KIND_THERMOMETRY: 0, KIND_DETECT: 0})
        n = _count(count)
        bucket["points"] += n
        key = _text(kind) or KIND_THERMOMETRY
        bucket[key] = bucket.get(key, 0) + n
    return out


# ------------------------------------------------------------------ 序列化
def summarize_run(run: InspectionRun, *, counts: Optional[dict] = None,
                  legacy: Optional[dict] = None, points: Optional[dict] = None,
                  names: Optional[dict] = None,
                  progress: Optional[dict] = None,
                  now: Optional[datetime] = None) -> dict:
    """一条 run -> 列表行。

    **进度口径**：优先新表动作数（FMS 自己记的账本最准），新表没有数据时回落
    旧表；再没有就用内存里的上报进度兜。``total=0`` 时 ``progress_pct`` 给
    ``None``——前端渲染成"—"，别显示成 0%（看着像"一个都没跑"）。
    """
    counts = counts or {}
    legacy = legacy or {}
    points = points or {}
    names = names or {}
    progress = progress or {}

    total = int(counts.get("total") or 0)
    done = int(counts.get("done") or 0)
    failed = int(counts.get("failed") or 0)
    pending = int(counts.get("pending") or 0)
    source = "action_results" if total else ""
    if not total and legacy:
        total = int(legacy.get("total") or 0)
        done = int(legacy.get("done") or 0)
        source = "inspection_results" if total else ""
    if not total and progress:
        total = int(progress.get("total_waypoint") or 0)
        done = max(0, int(progress.get("current_waypoint") or 0) - 1)
        source = "progress_cache" if total else ""

    robot_pk = run.robot_pk
    return {
        "id": run.id,
        "inspection_id": _text(run.inspection_id),
        "task_id": run.task_id,
        "robot_pk": robot_pk,
        "robot_name": names.get(int(robot_pk)) if robot_pk is not None else None,
        "status": _text(run.status) or RUN_STARTED,
        "display_status": _effective_status(_text(run.status) or RUN_STARTED,
                                            total, done, run.start_time, now=now),
        "total_actions": total,
        "done_actions": done,
        "failed_actions": failed,
        "pending_actions": pending,
        "progress_pct": _pct(done, total) if total else None,
        "point_count": int(points.get("points") or 0),
        "detect_count": int(points.get(KIND_DETECT) or 0),
        "thermometry_count": int(points.get(KIND_THERMOMETRY) or 0),
        "counts_source": source,
        "start_time": _iso(run.start_time),
        "finish_time": _iso(run.finish_time),
        "created_at": _iso(run.created_at),
        "remark": _text(run.remark),
        "progress": progress,
        # —— 报表生成状态（异步任务）——
        "report_status": _text(getattr(run, 'report_status', '')),
        "report_path": _text(getattr(run, 'report_path', '')),
        "report_error": _text(getattr(run, 'report_error', '')),
        "report_generated_at": _iso(getattr(run, 'report_generated_at', None)),
    }


def _waypoint_name(row: InspectionActionResult) -> str:
    """从 ``raw_json`` 里取巡检当次记下的航点/设备名（如 ``G10联络柜``）。

    ⚠️ 这不是 ``robots``/``waypoints`` 表里的名字，而是**那一次巡检跑的时候**下发数据
    里带的 ``steer_point_name``。之所以不反查库：巡检记录要能独立成立 —— 事后改了
    航点名字、甚至删了航点，历史日志还得显示当时的名字，否则"这条测的是哪个柜子"
    就查不清了。老记录没这个字段就返回空串，前端显示 id 前缀。
    """
    raw = row.raw_json
    if not isinstance(raw, dict):
        return ""
    return _text(raw.get("steer_point_name"), 128)


def serialize_action(row: InspectionActionResult) -> dict:
    """一条动作结果。图片 / 录像路径原样带出——前端自己决定能不能加载。"""
    return {
        "id": row.id,
        "run_id": row.run_id,
        "robot_pk": row.robot_pk,
        "inspection_id": _text(row.inspection_id),
        "floor": row.floor,
        "waypoint_id": _text(row.waypoint_id),
        "waypoint_index": row.waypoint_index,
        # 航点/设备名（历史快照，见 `_waypoint_name`）
        "waypoint_name": _waypoint_name(row),
        "action_id": _text(row.action_id),
        "action_seq": row.action_seq,
        "action_type": row.action_type,
        "action_type_name": _action_type_name(row.action_type),
        "attempt": row.attempt,
        "executor": _text(row.executor),
        "detect_type": _text(row.detect_type),
        "status": _text(row.status) or STATUS_PENDING,
        "code": row.code,
        "picture": _text(row.picture, 512),
        "infrared": _text(row.infrared, 512),
        "media": _text(row.media, 512),
        "local_path": _text(row.local_path, 512),
        "thermometry": row.thermometry_json,
        "env": row.env_json,
        "pdd": row.pdd_json,
        "inplace_ts": _text(row.inplace_ts),
        "start_time": _iso(row.start_time),
        "finish_time": _iso(row.finish_time),
        "duration_ms": row.duration_ms or 0,
        # —— 分发（任务执行器）——
        "dispatch_status": _text(row.dispatch_status) or DISPATCH_PENDING,
        "dispatch_mode": _text(row.dispatch_mode),
        "dispatch_attempts": row.dispatch_attempts or 0,
        "dispatched_at": _iso(row.dispatched_at),
        "dispatch_error": _text(row.dispatch_error, 512),
        "reference_image": _text(row.reference_image, 512),
        # —— 推理留痕：请求参数 / 同步响应(含 http status) / 算法回调结果 ——
        "infer_request": row.infer_request_json,
        "infer_response": row.infer_response_json,
        "infer_result": row.infer_result_json,
    }


def serialize_point(row: InspectionPointResult, *, action: Optional[InspectionActionResult] = None,
                    flows: Optional[dict] = None,
                    archive: Optional[dict] = None) -> dict:
    """一条测点结果。``action`` 可选——传进来能给测点补上动作类型与图片。

    测温点与检测点共用本结构（见 ``models/inspection.py`` 的说明）：``kind``
    区分来源，``value``/``unit`` 是判定值，检测细节在 ``detect`` 里。

    ``flows`` / ``archive`` 是**可选的旁路数据**（调用方一次查好传进来，别在这里查）：
    ``flows`` 是 `{流程引用 id: 流程名}`、``archive`` 是 `{测点 id: 测点档案}`。
    巡检详情的检视器要显示"用的哪条流程、绑的哪个测点"，但**这些数据不在账本里** ——
    账本只有引用 id。传空表就只是少这两栏，不影响其余字段（档案文件坏了也不该让
    整个详情接口 500）。
    """
    out = {
        "id": row.id,
        "action_result_id": row.action_result_id,
        "run_id": row.run_id,
        "robot_pk": row.robot_pk,
        "inspection_id": _text(row.inspection_id),
        "floor": row.floor,
        "waypoint_id": _text(row.waypoint_id),
        "action_id": _text(row.action_id),
        "point_id": _text(row.point_id),
        # 检测框身份：point_id 可能为空（没绑测点），box_id 一定有
        "box_id": _text(row.box_id),
        "box_name": _text(row.box_name),
        "seq": row.seq,
        "kind": _text(row.kind) or KIND_THERMOMETRY,
        "status": _text(row.status) or STATUS_PENDING,
        "value": row.value,
        "unit": _text(row.unit),
        "image": _text(row.image, 512),
        "detect_flow": _text(row.detect_flow),
        "detect_flow_name": (flows or {}).get(_text(row.detect_flow), "") if row.detect_flow else "",
        "algorithm": _text(row.algorithm),
        "label": _text(row.label),
        "confidence": row.confidence,
        "passed": row.passed,
        "boxes": row.boxes_json or [],
        "detect": row.detect_json,
        # 算法**原始识别结果**（回调结果框原样留痕）：display / parameter / code /
        # extra.detections… 检视器要"看算法到底识别出了什么"就得靠它
        "raw": row.raw_json,
        # 测点档案（按 point_id 查；没绑测点 / 档案里没有该 id 时为 None）
        "point": (archive or {}).get(_text(row.point_id)) if row.point_id else None,
        "created_at": _iso(row.created_at),
        "updated_at": _iso(row.updated_at),
    }
    if action is not None:
        out["action_type"] = action.action_type
        out["action_type_name"] = _action_type_name(action.action_type)
        out["picture"] = _text(action.picture, 512)
        if not out["image"] and action.infrared:
            out["image"] = _text(action.infrared, 512)
    return out


# ============================================================ 旁路数据（流程名 / 测点档案）

def detect_flow_names() -> dict[str, str]:
    """检测流程引用 id -> 流程名（根节点 `name`）。

    账本里只存流程的**引用 id**（`detect_id` 或文件名），巡检详情要显示的是人看的
    名字。引用规则**不在这里重写** —— 直接复用回调那条链上的 `_load_flow_map`，
    否则两边算法漂移会出现"详情说用的是流程 A、实际跑的是流程 B"。
    流程目录缺失 / 单条写坏都只是少一个名字，返回空表即可。
    """
    try:
        from .alarm_processor import _load_flow_map

        return {str(ref): (str(getattr(root, "name", "") or "") or str(ref))
                for ref, root in _load_flow_map().items()}
    except Exception:  # noqa: BLE001 - 详情页少一栏，不该 500
        logger.warning("检测流程目录读取失败，巡检详情不显示流程名", exc_info=True)
        return {}


def point_archive_map(point_ids: Any) -> dict[str, dict]:
    """测点档案：`point_id` -> `{id, name, code, active, parent_name, path}`。

    只取**被引用到的**那几个测点（一次遍历，不按 id 逐个查）。档案未加载 / 文件坏了
    返回空表 —— 巡检详情少一栏，比整个接口 500 好。
    """
    want = {str(x).strip() for x in (point_ids or []) if str(x or "").strip()}
    if not want:
        return {}
    try:
        from ..point_archive.runtime import get_archive_store

        doc, dirs, _children, _direct = get_archive_store().catalog_data()
    except Exception:  # noqa: BLE001 - 同上
        logger.warning("测点档案读取失败，巡检详情不显示测点信息", exc_info=True)
        return {}

    out: dict[str, dict] = {}
    for p in doc.get("points") or []:
        pid = str(p.get("id") or "")
        if pid not in want:
            continue
        parent = dirs.get(p.get("directory_id")) or {}
        out[pid] = {
            "id": pid,
            "name": str(p.get("name") or ""),
            "code": str(p.get("code") or ""),
            "active": bool(p.get("active", True)),
            "parent_name": str(parent.get("name") or ""),
            "path": _dir_path(dirs, p.get("directory_id")),
        }
    return out


def _dir_path(dirs: dict, directory_id: Any, limit: int = 8) -> list[str]:
    """目录 id -> `['站', '电压等级', '间隔', '设备']`（**从外到内**）。

    `limit` 是防环的兜底：档案是外部导入的 JSON，`parent_id` 万一指成环，
    没有上限就会在这里转到天荒地老（详情接口直接挂住）。
    """
    chain: list[str] = []
    cur = directory_id
    while cur and len(chain) < limit:
        node = dirs.get(cur)
        if not isinstance(node, dict):
            break
        chain.append(str(node.get("name") or ""))
        cur = node.get("parent_id")
    chain.reverse()
    return [x for x in chain if x]


def action_status_summary(rows: list[InspectionActionResult]) -> dict:
    """动作结果的分状态计数 + 分发状态计数，给详情页顶部的摘要条用。"""
    summary = {"total": len(rows), "status": {}, "dispatch": {}}
    for row in rows:
        key = _text(row.status) or STATUS_PENDING
        summary["status"][key] = summary["status"].get(key, 0) + 1
        dkey = _text(row.dispatch_status) or DISPATCH_PENDING
        summary["dispatch"][dkey] = summary["dispatch"].get(dkey, 0) + 1
    return summary
