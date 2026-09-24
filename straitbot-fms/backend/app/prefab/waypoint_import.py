"""巡检任务 JSON → 航点树 prefab spec 的转换。

巡检任务结构（见 backend/tests/test_inspection.json）：
    [楼层, ...]（同一 id 的多个成员 = 一次巡检的多个楼层）
    楼层: {floor, id, name, plan, substationMapsId, waypoint:[...]}
    航点: {id, index, pose:{point:{x,y,z}, theta}, action:[...]}
    动作: {id, type(1拍照/2测温/3录像), lift_height, duration?, steer_point_name,
           ptz_param:{pan,tilt,zoom,focal_len,focus}, thermometry_points:[...]}
    测温点: {id, thermometry_param:{distance, emissivity, enable_reflective,
             reflective_temperature, rect:{x,y,w,h}}}

映射为航点树：
    GroupNode(任务)
      └ GroupNode(楼层)
          └ WaypointNode(航点)
              └ ActionPointNode(动作点)
                  └ MeasurePointNode(测温点)

位姿单位沿用巡检任务：x/y/z 为米、theta 为度（与上位机标准单位一致，不换算）。
"""
from __future__ import annotations

from typing import Any

_ACTION_TYPE_NAME = {1: "拍照", 2: "全屏测温", 3: "录像"}


def _f(v: Any, d: float = 0.0) -> float:
    try:
        return float(v)
    except (TypeError, ValueError):
        return d


def _i(v: Any, d: int = 0) -> int:
    try:
        return int(v)
    except (TypeError, ValueError):
        return d


def _node(type_name: str, props: dict[str, Any] | None = None,
          children: list[dict[str, Any]] | None = None) -> dict[str, Any]:
    return {"type": type_name, "properties": props or {}, "children": children or []}


def _measure_point(tp: dict[str, Any]) -> dict[str, Any]:
    prm = tp.get("thermometry_param") or {}
    rect = prm.get("rect") or {}
    pid = str(tp.get("id") or "")
    return _node("MeasurePointNode", {
        "name": f"测点{pid[-6:]}" if pid else "测温点",
        "point_id": pid,
        "rect_x": _f(rect.get("x")), "rect_y": _f(rect.get("y")),
        "rect_w": _f(rect.get("w")), "rect_h": _f(rect.get("h")),
        "distance": _i(prm.get("distance")),
        "emissivity": _f(prm.get("emissivity"), 0.96),
        "enable_reflective": _i(prm.get("enable_reflective")),
        "reflective_temperature": _f(prm.get("reflective_temperature")),
    })


def _action_point(a: dict[str, Any]) -> dict[str, Any]:
    ptz = a.get("ptz_param") or {}
    atype = _i(a.get("type"), 1)
    name = a.get("steer_point_name") or f"{_ACTION_TYPE_NAME.get(atype, '动作')}"
    children = [_measure_point(tp) for tp in (a.get("thermometry_points") or [])
                if isinstance(tp, dict)]
    return _node("ActionPointNode", {
        "name": name,
        "action_id": str(a.get("id") or ""),
        "action_type": atype,
        "steer_point_name": str(a.get("steer_point_name") or ""),
        "lift_height": _f(a.get("lift_height")),
        "duration_ms": _i(a.get("duration")),
        "pan": _f(ptz.get("pan")), "tilt": _f(ptz.get("tilt")),
        "zoom": _f(ptz.get("zoom"), 1.0),
        "focal_len": _i(ptz.get("focal_len")), "focus": _i(ptz.get("focus")),
    }, children)


def _waypoint(w: dict[str, Any], floor: int = 1) -> dict[str, Any]:
    """单个航点 -> WaypointNode。

    `floor` 由**楼层段**传下来（`floor` 是巡检任务楼层段的字段），写进航点自己的
    `floor`——只写在分组名 `楼层N` 里是有损的：用户把分组改个名（或再套一层
    "区域A"）就解不出来了，反向组装巡检任务时整段航点的楼层都会错。
    """
    pose = w.get("pose") or {}
    pt = pose.get("point") or {}
    children = [_action_point(a) for a in (w.get("action") or []) if isinstance(a, dict)]
    return _node("WaypointNode", {
        "name": f"航点{w.get('index')}",
        "wp_id": str(w.get("id") or ""),
        "index": _i(w.get("index")),
        "floor": _i(floor, 1),
        "x": _f(pt.get("x")), "y": _f(pt.get("y")), "z": _f(pt.get("z")),
        "theta": _f(pose.get("theta")),
    }, children)


def _floor(fl: dict[str, Any]) -> dict[str, Any]:
    floor = _i(fl.get("floor"), 1)
    children = [_waypoint(w, floor) for w in (fl.get("waypoint") or []) if isinstance(w, dict)]
    return _node("GroupNode", {
        "name": f"楼层{fl.get('floor')}",
        "description": str(fl.get("name") or ""),
    }, children)


def inspection_to_spec(payload: Any) -> dict[str, Any]:
    """巡检任务（楼层对象或其数组）→ 航点树 prefab spec。

    输出可直接作为 POST /api/waypoint-prefab/tree 的 spec 保存。
    """
    if isinstance(payload, dict):
        floors = [payload]
    elif isinstance(payload, list):
        floors = [f for f in payload if isinstance(f, dict)]
    else:
        raise ValueError("巡检任务必须是楼层对象或其数组")
    if not floors:
        raise ValueError("巡检任务为空（没有任何楼层）")

    task_name = ""
    for f in floors:
        if f.get("name"):
            task_name = str(f["name"])
            break
    root_children = [_floor(f) for f in floors]
    wp_count = sum(len(f.get("waypoint") or []) for f in floors)
    root = _node("GroupNode", {
        "name": task_name or "巡检任务",
        "description": f"由巡检任务导入：{len(floors)} 楼层 / {wp_count} 航点",
    }, root_children)
    return {"name": task_name or "巡检任务", "description": "", "root": root}
