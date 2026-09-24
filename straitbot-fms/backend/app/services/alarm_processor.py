"""检测告警处理：算法回调结果 -> 继续跑检测流程 -> 产生告警 / 回写测点。

算法服务（ai_server.py）识别完成后把结果回调到 ``/report/detect_callback``。
回调 body 的 ``info.boxs`` 是**每个提交框的识别结论**（display 正常/异常、
parameter 读数、extra.detections 目标框）。本模块对每个结果框：

1. 从提交留痕（``infer_request_json.box_flow``）查出它对应哪个**检测流程** /
   测点 / 区域（提交时跳过了无算法框，结果框 id 对不上检测框顺序，必须靠快照）。
   先按提交序号 ``id`` 对，对不上再按 ``box_id`` 对 —— **``point_id`` 可以是空的**
   （本站场景里检测框常常不绑测点），这时 ``box_id`` 是唯一能把结果认回框的键；
2. 把结论构建成 :class:`DetectEvent`，喂给该流程树跑 :func:`run_flow`——
   流程里的阈值 / 连续确认是闸门，``AlarmNode`` / ``NumericAlarmNode`` /
   ``RangeAlarmNode`` 命中条件就产出 alarm 动作；
3. 把 alarm 动作落成 :class:`Alarm`（含 dedup 合并），同时回写
   ``inspection_point_results``。**没有测点也要回写**（按 box_id 定位），
   否则"算法识别出来了、详情里却什么都没有"。

纯编排判定，无外发（短信 / 邮件 / HTTP 转发的动作本期只记录、不真发）。
"""
from __future__ import annotations

import json
import logging
import re
from datetime import datetime
from pathlib import Path
from typing import Any, Optional

from ..config import DETECT_PREFAB_DIR
from ..models import Alarm, InspectionActionResult, InspectionPointResult
from ..prefab.detect_pipeline import DetectEvent, run_flow
from ..prefab.task_executor import index_flows

logger = logging.getLogger("app.alarm_processor")


# ============================================================ 主入口

def process_callback(db: Any, action: InspectionActionResult, body: dict) -> dict:
    """处理一次算法回调：跑流程、产告警、回写测点。

    :return: 统计 ``{boxes, alarms, points, failed}``
    """
    result_boxs = (body.get("info") or {}).get("boxs") or []
    flow_map = _load_flow_map()
    box_flow = _get_box_flow(action)
    picture = str(action.picture or action.local_path or "")

    stats = {"boxes": len(result_boxs), "alarms": 0, "points": 0, "failed": 0}

    for rb in result_boxs:
        # ⚠️ 结果框一般会把入参原样带回，所以 box_id 可能来自结果框自己
        # （`rb["box_id"]`）或提交留痕（box_flow）。两条都试，取得到的那个。
        rb_box_id = str(rb.get("box_id") or "").strip()
        bf = _lookup_bf(box_flow, rb.get("id"), rb_box_id)
        flow_ref = (bf or {}).get("flow_ref", "") or ""
        point_id = (bf or {}).get("point_id", "") or str(rb.get("pointId") or "")
        point_name = (bf or {}).get("point_name", "") or ""
        box_id = (bf or {}).get("box_id", "") or rb_box_id
        box_name = (bf or {}).get("box_name", "") or str(rb.get("box_name") or "")
        region = (bf or {}).get("region", "") or {}

        # 算法处理失败（配准失败等，code 非 0）：测点记 failed，不跑流程、不告警
        if _is_failed(rb):
            _upsert_point(db, action, point_id, point_name, flow_ref, rb,
                          status="failed", box_id=box_id, box_name=box_name)
            stats["failed"] += 1
            continue

        event, einfo = _build_event(rb, point_id, point_name, region)
        root = flow_map.get(flow_ref) if flow_ref else None
        flow_run = run_flow(root, event) if root is not None else None

        _upsert_point(db, action, point_id, point_name, flow_ref, rb,
                      status="ok", event=event, einfo=einfo, flow_run=flow_run,
                      box_id=box_id, box_name=box_name)
        stats["points"] += 1

        if flow_run is not None:
            for act in flow_run.actions:
                if act.get("kind") in ("alarm", "numeric_alarm", "range_alarm"):
                    # 没绑测点的框没有 point_name，告警列表就会显示一条没有名字的记录 ——
                    # 用框名兜底（列表读的是 point_name，别为了一个新字段去改一堆页面）
                    _create_alarm(db, action, act, rb, picture,
                                  point_id, point_name or box_name, flow_ref,
                                  box_id=box_id, box_name=box_name)
                    stats["alarms"] += 1

    logger.info("回调处理完成 action_result_id=%s %s", action.id, stats)
    return stats


# ============================================================ 流程树加载

def _load_flow_map() -> dict:
    """加载检测算法目录 -> `{flow_ref: 流程根实例}`（每次现读，不缓存）。"""
    specs: list[tuple[str, dict]] = []
    root_dir = Path(DETECT_PREFAB_DIR)
    if root_dir.exists():
        for p in sorted(root_dir.rglob("*.prefab.json")):
            if not p.is_file():
                continue
            try:
                specs.append((p.name, json.loads(p.read_text(encoding="utf-8"))))
            except Exception as exc:  # noqa: BLE001 - 单坏文件不影响其它
                logger.warning("检测流程 %s 解析失败: %s", p, exc)
    return index_flows(specs)


def _get_box_flow(action: InspectionActionResult) -> Optional[list]:
    """从提交留痕取 box_flow 快照（老数据没有，返回 None 走降级）。"""
    req = action.infer_request_json
    if isinstance(req, dict):
        bf = req.get("box_flow")
        if isinstance(bf, list):
            return bf
    return None


def _lookup_bf(box_flow: Optional[list], bid: Any, box_id: str = "") -> Optional[dict]:
    """结果框 -> 提交留痕。先按提交时的序号 `id` 对，对不上再按 `box_id` 对。

    ⚠️ 为什么要退到 box_id：`id` 是**提交时的序号**，算法服务丢框 / 合并框 /
    只回一部分时序号会错位；而 `box_id` 是框自己的身份，不会变。
    """
    if not box_flow:
        return None
    for bf in box_flow:
        if bf.get("id") == bid:
            return bf
    if box_id:
        for bf in box_flow:
            if bf.get("box_id") and bf.get("box_id") == box_id:
                return bf
    return None


def _is_failed(rb: dict) -> bool:
    """结果框是否为算法处理失败（code 非 "0"）。成功含命中与未命中。"""
    return str(rb.get("code") or "0") != "0"


# ============================================================ 事件构建

def _build_event(rb: dict, point_id: str, point_name: str, region: dict):
    """结果框 -> (DetectEvent, 解析信息)。"""
    extra = rb.get("extra") or {}
    dets = []
    for d in (extra.get("detections") or []):
        try:
            dets.append({
                "label": str(d.get("name") or ""),
                "conf": float(d.get("conf") or 0.0),
                "box": d.get("box") or [],
            })
        except (TypeError, ValueError):
            continue
    dets.sort(key=lambda d: d["conf"], reverse=True)

    display = str(rb.get("display") or "")
    is_hit = display != "正常"
    best = dets[0] if dets else None
    if best:
        label, conf = best["label"], best["conf"]
    else:
        label = display if is_hit else ""
        try:
            conf = float(rb.get("confidence") or (1.0 if is_hit else 0.0))
        except (TypeError, ValueError):
            conf = 1.0 if is_hit else 0.0

    cx, cy = _region_center(region)
    event = DetectEvent(
        # 留空：当前对接的 MeterAlgorithmNode.algorithm 为空，闸门会跳过算法比对，
        # 只让阈值/类别白名单生效
        algorithm="",
        label=label,
        confidence=conf,
        source="抓拍图",
        point_id=point_id,
        point_name=point_name,
        value=_read_value(rb),
        x=cx,
        y=cy,
    )
    return event, {"detections": dets, "display": display, "is_hit": is_hit}


def _read_value(rb: dict) -> Optional[float]:
    """结果框的**读数** —— 一律从 `parameter` 取。

    `parameter` 是推理服务对这块区域给出的读数（表计读数 / 状态码 / 二值结论），
    `NumericAlarmNode` / `RangeAlarmNode` 都拿它当判据（见
    `detect_pipeline.numeric_alarm_hit`）。取不出数字就返回 None ——
    调用方会记一条"事件没带数值"跳过，**绝不拿 0 顶替**
    （把"没采到"当成"0℃"会报一堆假低温告警）。

    ⚠️ 这里曾经有一条「`name` 以 `0_` 开头就当安全/二值类、不产生数值」的判断，
    那是错的：`name` 是提交推理时带过去的 **panel_list 算法编码**
    （如 `0_0_0_4010_0_0`），63 个算法里有 37 个以 `0_` 开头，其中就包括
    「电流表_中_1.5KA」「电压表_中_12KV」这些**本来就要读数**的表计 ——
    那条判断会把它们的读数整片掐掉，数值告警**永远不触发**
    （现象：流程配好了、算法也命中了，告警就是不报）。
    要不要按数值判，看 `parameter` 里有没有数字就够了，别再去猜 `name` 的编码含义。
    """
    param = str(rb.get("parameter") or "")
    m = re.search(r"[-+]?\d+(?:\.\d+)?", param)
    if not m:
        return None
    try:
        return float(m.group())
    except ValueError:
        return None


def _region_center(region: dict) -> tuple[Optional[float], Optional[float]]:
    """检测区域中心（归一化），供流程的区域过滤用。"""
    pts = (region or {}).get("points") or []
    xs, ys = [], []
    for p in pts:
        if isinstance(p, dict):
            try:
                xs.append(float(p.get("x")))
                ys.append(float(p.get("y")))
            except (TypeError, ValueError):
                pass
    if xs and ys:
        return sum(xs) / len(xs), sum(ys) / len(ys)
    return None, None


# ============================================================ 告警落表

def _create_alarm(db: Any, action: InspectionActionResult, act: dict, rb: dict,
                  picture: str, point_id: str, point_name: str,
                  flow_ref: str, *, box_id: str = "", box_name: str = "") -> Alarm:
    """把一条 alarm 动作落成 Alarm（dedup 窗口内合并）。

    ⚠️ 去重要**带上 box_id**：同一个动作下可能有好几个都没绑测点的框
    （`point_id` 全是 ""），只按 `(run_id, alarm_type, point_id)` 去重的话，
    它们的告警会在窗口内被合并成一条，等于悄悄丢告警。
    """
    dedup = _safe_float(act.get("dedup_seconds"))
    if dedup > 0:
        existing = db.query(Alarm).filter(
            Alarm.run_id == action.run_id,
            Alarm.alarm_type == flow_ref,
            Alarm.point_id == point_id,
            Alarm.box_id == box_id,
        ).order_by(Alarm.id.desc()).first()
        if existing is not None and existing.triggered_at is not None:
            age = (datetime.utcnow() - existing.triggered_at).total_seconds()
            if age <= dedup:
                existing.triggered_at = datetime.utcnow()
                existing.title = act.get("title") or existing.title
                existing.content = act.get("content") or existing.content
                if picture:
                    existing.picture = picture
                existing.extra_json = {"action": act, "result_box": rb}
                db.flush()
                return existing

    alarm = Alarm(
        run_id=action.run_id,
        action_result_id=action.id,
        inspection_id=action.inspection_id,
        floor=action.floor,
        waypoint_id=action.waypoint_id,
        action_id=action.action_id,
        point_id=point_id,
        point_name=point_name,
        box_id=box_id,
        box_name=box_name,
        alarm_type=flow_ref,
        algorithm=str(rb.get("name") or ""),
        level=str(act.get("level") or "一般告警"),
        title=str(act.get("title") or flow_ref or "检测告警"),
        content=str(act.get("content") or ""),
        picture=picture,
        extra_json={"action": act, "result_box": rb},
        status="unack",
        triggered_at=datetime.utcnow(),
    )
    db.add(alarm)
    db.flush()
    return alarm


# ============================================================ 测点回写

def _upsert_point(db: Any, action: InspectionActionResult, point_id: str,
                  point_name: str, flow_ref: str, rb: dict, *,
                  status: str, event: Optional[DetectEvent] = None,
                  einfo: Optional[dict] = None,
                  flow_run: Any = None,
                  box_id: str = "", box_name: str = "") -> Optional[InspectionPointResult]:
    """更新（或补插）本次回调对应的测点行。

    ## 定位键：优先 box_id，退回 point_id

    ⚠️ **不能因为 `point_id` 为空就整条丢掉**（老写法 `if not point_id: return None`）。
    本站场景里检测框常常**不绑测点**，此时唯一能定位的键就是 `box_id`（框自己的 id，
    一定有）。丢掉的话表现是"算法明明识别出来了、巡检详情里却什么都没有" ——
    比多插一行难查得多。

    老数据（改造前提交的任务）没有 box_id，退回按 `(action_result_id, point_id)`
    匹配；再退一步，旧占位行当时是拿 `point_id` 列装框 id 的，所以也试一下
    `point_id == box_id`，免得升级瞬间正在跑的那次巡检多出一行重复。
    """
    if not box_id and not point_id:
        return None

    target = None
    if box_id:
        target = db.query(InspectionPointResult).filter(
            InspectionPointResult.action_result_id == action.id,
            InspectionPointResult.box_id == box_id,
        ).first()
    if target is None and point_id:
        target = db.query(InspectionPointResult).filter(
            InspectionPointResult.action_result_id == action.id,
            InspectionPointResult.point_id == point_id,
        ).first()
    if target is None and box_id:
        # 兼容改造前的占位行（那时 point_id 列里装的是框 id）
        target = db.query(InspectionPointResult).filter(
            InspectionPointResult.action_result_id == action.id,
            InspectionPointResult.point_id == box_id,
        ).first()

    if target is None:
        target = InspectionPointResult(
            action_result_id=action.id, run_id=action.run_id,
            robot_pk=action.robot_pk, inspection_id=action.inspection_id,
            floor=action.floor, waypoint_id=action.waypoint_id,
            action_id=action.action_id, point_id=point_id,
        )
        db.add(target)

    target.kind = "detect"
    target.status = status
    target.point_id = point_id or target.point_id or ""
    target.box_id = box_id or target.box_id or ""
    if box_name:
        target.box_name = box_name
    target.detect_flow = flow_ref or ""
    target.algorithm = str(rb.get("name") or "")
    target.raw_json = rb

    if event is not None:
        target.label = event.label
        target.confidence = event.confidence
        target.value = event.value
        target.boxes_json = _norm_boxes(rb, einfo)

    if status == "failed":
        target.passed = None
    else:
        alarmed = bool(flow_run and [
            a for a in flow_run.actions
            if a.get("kind") in ("alarm", "numeric_alarm", "range_alarm")
        ])
        target.passed = not alarmed

    if flow_run is not None:
        target.detect_json = {
            "passed": flow_run.passed,
            "stopped_by": flow_run.stopped_by,
            "actions": flow_run.actions,
            "notes": flow_run.notes,
        }
    db.flush()
    return target


def _norm_boxes(rb: dict, einfo: Optional[dict]) -> Optional[list]:
    """把检测目标的像素框转归一化（orig_shape 给高宽）。"""
    ri = (rb.get("extra") or {}).get("result_info") or {}
    shape = ri.get("orig_shape")
    h = w = None
    if isinstance(shape, list) and len(shape) == 2:
        h, w = shape[0], shape[1]
    out = []
    for d in (einfo or {}).get("detections") or []:
        box = d.get("box") or []
        item = {"label": d.get("label"), "score": d.get("conf")}
        if len(box) == 4 and w and h:
            x1, y1, x2, y2 = box
            item.update({"x": x1 / w, "y": y1 / h,
                         "w": (x2 - x1) / w, "h": (y2 - y1) / h})
        out.append(item)
    return out or None


def _safe_float(v: Any) -> float:
    try:
        return float(v or 0.0)
    except (TypeError, ValueError):
        return 0.0
