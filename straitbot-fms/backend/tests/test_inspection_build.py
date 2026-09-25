"""航点树 -> 巡检任务载荷的组装，以及"到点 -> 真下发"这一段。

这里锁的是**字段映射**和**谁被排除了**——组装错了不会报错，只会让机器人去错的
地方拍错的东西，所以每一条映射都得钉住：

- 航点/动作/测温各自 `to_inspection_json` 的字段（尤其 `index` 是**楼层内**序号）；
- 楼层分段：`floor` 取航点自己的字段，段内保持树中顺序；
- 测点指定 = 过滤测温点；测温动作被过滤得一个点不剩 -> 整个动作丢掉；
- 停用的航点不下发；
- `dispatch_inspection`：没机器人 / 机器人不对 / 忙 -> `accepted=False` 且不抛；
  正常 -> 载荷原样交给 `接收巡检任务`。
"""
import json
from pathlib import Path

import pytest

from app.prefab import inspection_build as ib
from app.prefab.inspection_build import (
    DEFAULT_FLOOR, build_from_plan, build_inspection_payload, collect_waypoints,
    floor_from_name, hex_id, load_waypoint_spec, waypoint_floor, waypoint_key,
)
from app.prefab.plan_scheduler import clear_inspection_trigger, dispatch_inspection, \
    get_inspection_trigger, install_default_trigger, set_inspection_trigger


# ---------------------------------------------------------------- 造 spec

def mpt(pid="P1", rect=(0.1, 0.2, 0.3, 0.4)):
    x, y, w, h = rect
    return {"type": "MeasurePointNode",
            "properties": {"name": pid, "point_id": pid, "rect_x": x, "rect_y": y,
                           "rect_w": w, "rect_h": h, "distance": 200,
                           "emissivity": 0.95, "enable_reflective": 0,
                           "reflective_temperature": 23.0},
            "children": []}


def action(aid="A1", atype=1, pts=(), **kw):
    props = {"name": aid, "action_id": aid, "action_type": atype,
             "steer_point_name": "AO-RC-057", "lift_height": 1.2,
             "duration_ms": 3000, "pan": 10.0, "tilt": 20.0, "zoom": 2.0,
             "focal_len": 520, "focus": 100}
    props.update(kw)
    return {"type": "ActionPointNode", "properties": props, "children": list(pts)}


def wp(name="wp", wp_id="W1", floor=1, x=0.0, children=(), enabled=True):
    return {"type": "WaypointNode",
            "properties": {"name": name, "wp_id": wp_id, "floor": floor,
                           "index": 0, "x": x, "y": 0.0, "z": 1.5, "theta": 90.0,
                           "enabled": enabled},
            "children": list(children)}


def group(name="g", children=(), enabled=True):
    return {"type": "GroupNode",
            "properties": {"name": name, "enabled": enabled},
            "children": list(children)}


def spec(root):
    return {"name": "测试航点树", "description": "", "root": root}


def write_spec(tmp_path: Path, name: str, root) -> str:
    """写一份航点树文件，返回它的文件名（`build_from_plan` 的 `source`）。"""
    p = tmp_path / name
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(json.dumps(spec(root), ensure_ascii=False), encoding="utf-8")
    return name


# ---------------------------------------------------------------- hex / key

def test_hex_id_len():
    assert len(hex_id()) == 32
    assert hex_id() != hex_id()


def test_waypoint_key_prefers_wp_id():
    from app.prefab.registry import build
    n = build(wp(wp_id="  W-9  "))
    assert waypoint_key(n, "root/children/0") == "W-9"

    n2 = build(wp(wp_id=""))
    assert waypoint_key(n2, "root/children/0") == "root/children/0"


# ---------------------------------------------------------------- 节点自我序列化

def test_waypoint_json_fields():
    from app.prefab.registry import build
    n = build(wp(wp_id="W-1", floor=2, x=12.5))
    w = n.to_inspection_json(index=3)
    assert w["id"] == "W-1"
    assert w["index"] == 3
    assert w["pose"] == {"point": {"x": 12.5, "y": 0.0, "z": 1.5}, "theta": 90.0}
    assert w["action"] == []


def test_waypoint_json_fresh_id():
    from app.prefab.registry import build
    n = build(wp(wp_id="W-1"))
    assert n.to_inspection_json(fresh_id=True)["id"] != "W-1"


def test_action_json_duration_only_for_video():
    from app.prefab.registry import build
    shot = build(action("A1", 1))
    video = build(action("A2", 3))
    therm = build(action("A3", 2))
    assert shot.to_inspection_json()["duration"] == 0      # 拍照不带时长
    assert video.to_inspection_json()["duration"] == 3000
    assert therm.to_inspection_json()["type"] == 2


def test_action_json_ptz_and_points():
    from app.prefab.registry import build
    a = build(action("A1", 2, [mpt("P1"), mpt("P2")]))
    j = a.to_inspection_json()
    assert j["ptz_param"] == {"focal_len": 520, "focus": 100, "pan": 10.0,
                              "tilt": 20.0, "zoom": 2.0}
    assert j["steer_point_name"] == "AO-RC-057"
    assert [p["id"] for p in j["thermometry_points"]] == ["P1", "P2"]


def test_action_json_filter_points():
    from app.prefab.registry import build
    a = build(action("A1", 2, [mpt("P1"), mpt("P2")]))
    assert [p["id"] for p in a.to_inspection_json(point_ids={"P2"})["thermometry_points"]] \
        == ["P2"]
    # 空集合 = 一个都不要（调用方不会这么传，但语义要明确：是过滤不是"不过滤"）
    assert a.to_inspection_json(point_ids=set())["thermometry_points"] == []


def test_unknown_node_returns_none():
    from app.prefab.registry import build
    assert build(group()).to_inspection_json() is None


# ---------------------------------------------------------------- 收集

def test_collect_skips_disabled_subtree():
    from app.prefab.registry import build
    root = build(group("root", [
        wp("a", "W1"),
        group("停用组", [wp("b", "W2")], enabled=False),
        wp("c", "W3", enabled=False),
        wp("d", "W4"),
    ]))
    keys = [waypoint_key(pk.node, pk.path) for pk in collect_waypoints(root)]
    assert keys == ["W1", "W4"]


def test_collect_keeps_tree_order():
    from app.prefab.registry import build
    root = build(group("root", [wp("a", "W9", x=30), wp("b", "W1", x=1)]))
    assert [waypoint_key(pk.node, pk.path) for pk in collect_waypoints(root)] \
        == ["W9", "W1"]


# ---------------------------------------------------------------- 楼层判定

def test_floor_from_name():
    assert floor_from_name("楼层2") == 2
    assert floor_from_name("楼层-1") == -1          # 地下室
    assert floor_from_name("楼层 3") == 3
    assert floor_from_name("区域A") == DEFAULT_FLOOR
    assert floor_from_name(None) == DEFAULT_FLOOR


def test_floor_own_field_wins():
    """航点自己写了 floor 就用它（含 0 和负数），不去解分组名。"""
    from app.prefab.registry import build
    n = build(wp("a", floor=0))
    assert waypoint_floor(n, ("楼层5",)) == 0
    n2 = build(wp("a", floor=-1))
    assert waypoint_floor(n2, ("楼层5",)) == -1


def test_floor_fallback_to_group_name():
    """老数据：`floor` 这个字段出现之前导入的树，航点上没有 floor。"""
    from app.prefab.registry import build
    n = build({"type": "WaypointNode",         # 故意不给 floor
               "properties": {"name": "a", "wp_id": "W1"}, "children": []})
    assert "floor" not in n.model_fields_set
    assert waypoint_floor(n, ("全程TT", "楼层2")) == 2


def test_floor_fallback_innermost_group():
    """由内向外找：`楼层1 > 区域A > 航点` 时楼层在更外面一层。"""
    from app.prefab.registry import build
    n = build({"type": "WaypointNode",
               "properties": {"name": "a", "wp_id": "W1"}, "children": []})
    assert waypoint_floor(n, ("楼层1", "区域A", "新分组")) == 1
    assert waypoint_floor(n, ("区域A", "楼层-2")) == -2


def test_floor_default():
    from app.prefab.registry import build
    n = build({"type": "WaypointNode",
               "properties": {"name": "a", "wp_id": "W1"}, "children": []})
    assert waypoint_floor(n, ("区域A",)) == DEFAULT_FLOOR


def old_wp(name, wp_id):
    """老格式的航点：`properties` 里**没有 `floor`**（`floor` 字段出现之前导入的）。"""
    return {"type": "WaypointNode",
            "properties": {"name": name, "wp_id": wp_id, "index": 0,
                           "x": 0.0, "y": 0.0, "z": 0.0, "theta": 0.0},
            "children": []}


def test_collect_reports_floor_from_group():
    """整条链路：老树没有 floor，靠分组名照样分出两个楼层段。"""
    out = build_inspection_payload(spec(group("任务", [
        group("楼层2", [old_wp("a", "W1")]),
        group("楼层1", [old_wp("b", "W2")]),
    ])))
    assert out["floors"] == [1, 2]
    assert [w["id"] for w in out["payload"][0]["waypoint"]] == ["W2"]
    assert [w["id"] for w in out["payload"][1]["waypoint"]] == ["W1"]


# ---------------------------------------------------------------- 组装

def test_build_payload_floor_sections():
    root = group("root", [
        wp("a", "W1", floor=2, x=1),
        wp("b", "W2", floor=1, x=2),
        wp("c", "W3", floor=2, x=3),
    ])
    out = build_inspection_payload(spec(root), name="任务A", plan="PLAN1",
                                   substation_maps_id="MAP1",
                                   inspection_id="TASK1")
    payload = out["payload"]
    assert [s["floor"] for s in payload] == [1, 2]
    assert out["floors"] == [1, 2]
    assert out["inspection_id"] == "TASK1"
    assert out["plan"] == "PLAN1"
    # 段内 index 从 1 重新编号
    assert [w["index"] for w in payload[0]["waypoint"]] == [1]
    assert [w["index"] for w in payload[1]["waypoint"]] == [1, 2]
    assert [w["id"] for w in payload[1]["waypoint"]] == ["W1", "W3"]
    for s in payload:
        assert s["id"] == "TASK1" and s["name"] == "任务A"
        assert s["substationMapsId"] == "MAP1"


def test_build_payload_selects_by_key():
    root = group("root", [wp("a", "W1"), wp("b", "W2"), wp("c", "W3")])
    out = build_inspection_payload(spec(root), ["W1", "W3"])
    assert out["waypoint_count"] == 2
    assert [w["id"] for w in out["payload"][0]["waypoint"]] == ["W1", "W3"]


def test_build_payload_drops_empty_thermometry_action():
    """测温动作被测点指定过滤得一个点不剩 -> 这个动作没有意义，丢掉。"""
    root = group("root", [
        wp("a", "W1", children=[
            action("A1", 2, [mpt("P1")]),      # 测温，不要 P1 -> 丢
            action("A2", 1),                   # 拍照，不受影响 -> 留
            action("A3", 3, [mpt("P1")]),      # 录像带测温点 -> 留（不是 type=2）
        ]),
    ])
    out = build_inspection_payload(spec(root), None, point_ids=["P9"])
    acts = out["payload"][0]["waypoint"][0]["action"]
    assert [a["id"] for a in acts] == ["A2", "A3"]
    assert out["action_count"] == 2


def test_build_payload_counts():
    root = group("root", [
        wp("a", "W1", floor=1, children=[action("A1", 1)]),
        wp("b", "W2", floor=2, children=[action("A2", 1), action("A3", 1)]),
    ])
    out = build_inspection_payload(spec(root))
    assert out["waypoint_count"] == 2 and out["action_count"] == 3


# ---------------------------------------------------------------- 从计划组装

def _job(waypoints, points=(), plan_name="夜巡", robot_name="", plan_id="",
         file="a.prefab.json", detect_type="fms"):
    return {"plan_key": f"{file}#{plan_id or plan_name}", "plan_id": plan_id,
            "plan_name": plan_name, "robot_name": robot_name, "priority": 0,
            "detect_type": detect_type,
            "file": file, "scheduled_at": "2026-09-21T02:00:00+08:00",
            "schedule": {"start": "02:00", "end": "02:00", "interval_minutes": 60,
                         "label": ""},
            "waypoints": list(waypoints), "points": list(points)}


# ---------------------------------------------------------------- detectType

def test_build_from_plan_writes_detect_type_per_floor(tmp_path):
    """`detectType` 必须写进**每一个**楼层段，不能只写第一段。

    `FloorTask.detect_type` 是**按段**解析的，`InspectionTask.detect_type` 取
    **首个分段**的值并检查各段是否一致。只写第一段的话其余段各自回落到缺省
    `platform`，于是同一次巡检内部不一致：那边告警、按首段为准，看着"能跑"，
    实际是在混着来（部分楼层按 platform 上传、部分按 fms 本机）。多楼层才露。
    """
    write_spec(tmp_path, "t1.json", group("root", [
        wp("a", "W1", floor=1), wp("b", "W2", floor=2), wp("c", "W3", floor=3)]))
    job = _job([{"source": "t1.json", "include_all": True, "waypoint_ids": []}],
               detect_type="platform")
    out = build_from_plan(job, root_dir=tmp_path)
    assert [s["floor"] for s in out["payload"]] == [1, 2, 3]
    assert [s["detectType"] for s in out["payload"]] == ["platform"] * 3
    assert out["detect_type"] == "platform"


def test_build_from_plan_detect_type_defaults_to_fms(tmp_path):
    """计划里没写 / 写了不认识的 -> `fms`（与编排侧 InspectionPlanNode 默认一致）。"""
    write_spec(tmp_path, "t1.json", group("root", [wp("a", "W1")]))
    for raw in ("fms", "", None, "xxx"):
        job = _job([{"source": "t1.json", "include_all": True, "waypoint_ids": []}],
                   detect_type=raw)
        out = build_from_plan(job, root_dir=tmp_path)
        assert out["payload"][0]["detectType"] == "fms", f"raw={raw!r}"


def test_build_from_plan_detect_type_is_legal_for_floor_task(tmp_path):
    """写出来的值必须是 `FloorTask` 认的 —— 不认识会被静默回落成 platform。

    这条是"组装侧与解析侧对齐"的胶水测试：两边各有一套 normalize，方向还相反
    （编排侧回落 fms，解析侧回落 platform）。组装写出去的值必须落在白名单里，
    否则用户明明选了 fms，落盘记录里却是 platform。
    """
    from app.rail.inspection import DETECT_TYPES, InspectionTask

    write_spec(tmp_path, "t1.json", group("root", [wp("a", "W1", floor=1)]))
    for want in ("fms", "platform"):
        job = _job([{"source": "t1.json", "include_all": True, "waypoint_ids": []}],
                   detect_type=want)
        out = build_from_plan(job, root_dir=tmp_path)
        assert out["payload"][0]["detectType"] in DETECT_TYPES
        task = InspectionTask.from_payload(out["payload"])
        # 解析回来还是它本人（没有被 validator 回落成别的）
        assert task.detect_type == want
        assert task.to_record()["detect_type"] == want


def test_build_from_plan_merges_trees(tmp_path):
    """多个「航点指定」= 多棵树，合成**一次**巡检：同一个 id/plan，按楼层分段。"""
    write_spec(tmp_path, "t1.json",
               group("root", [wp("a", "W1", floor=1)]))
    write_spec(tmp_path, "t2.json",
               group("root", [wp("b", "W2", floor=2), wp("c", "W3", floor=1)]))
    job = _job([{"source": "t1.json", "include_all": True, "waypoint_ids": []},
                {"source": "t2.json", "include_all": True, "waypoint_ids": []}])
    out = build_from_plan(job, root_dir=tmp_path)
    ids = {s["id"] for s in out["payload"]}
    assert len(ids) == 1                       # 一次巡检
    assert [s["floor"] for s in out["payload"]] == [1, 2]
    assert [w["id"] for w in out["payload"][0]["waypoint"]] == ["W1", "W3"]
    assert out["waypoint_count"] == 3


def test_build_from_plan_pick_ids(tmp_path):
    write_spec(tmp_path, "t1.json",
               group("root", [wp("a", "W1"), wp("b", "W2"), wp("c", "W3")]))
    job = _job([{"source": "t1.json", "include_all": False,
                 "waypoint_ids": ["W2"]}])
    out = build_from_plan(job, root_dir=tmp_path)
    assert [w["id"] for w in out["payload"][0]["waypoint"]] == ["W2"]


def test_build_from_plan_point_filter(tmp_path):
    write_spec(tmp_path, "t1.json", group("root", [
        wp("a", "W1", children=[action("A1", 2, [mpt("P1"), mpt("P2")])])]))
    job = _job([{"source": "t1.json", "include_all": True, "waypoint_ids": []}],
               points=[{"include_all": False, "point_ids": ["P2"]}])
    out = build_from_plan(job, root_dir=tmp_path)
    pts = out["payload"][0]["waypoint"][0]["action"][0]["thermometry_points"]
    assert [p["id"] for p in pts] == ["P2"]


def test_build_from_plan_include_all_points_no_filter(tmp_path):
    write_spec(tmp_path, "t1.json", group("root", [
        wp("a", "W1", children=[action("A1", 2, [mpt("P1"), mpt("P2")])])]))
    job = _job([{"source": "t1.json", "include_all": True, "waypoint_ids": []}],
               points=[{"include_all": True, "point_ids": []}])
    out = build_from_plan(job, root_dir=tmp_path)
    pts = out["payload"][0]["waypoint"][0]["action"][0]["thermometry_points"]
    assert [p["id"] for p in pts] == ["P1", "P2"]


def test_build_from_plan_no_waypoint_select():
    with pytest.raises(ValueError):
        build_from_plan(_job([]))


def test_build_from_plan_nothing_matched(tmp_path):
    write_spec(tmp_path, "t1.json", group("root", [wp("a", "W1")]))
    job = _job([{"source": "t1.json", "include_all": False, "waypoint_ids": ["NOPE"]}])
    with pytest.raises(ValueError):
        build_from_plan(job, root_dir=tmp_path)


def test_load_waypoint_spec_absolute(tmp_path):
    name = write_spec(tmp_path, "sub/t1.json", group("root", [wp("a", "W1")]))
    d = load_waypoint_spec(str(tmp_path / name))
    assert d["root"]["type"] == "GroupNode"


# ---------------------------------------------------------------- 真下发

class FakeRobot:
    def __init__(self, name="机器人1", robot_id="R-1", busy=False):
        self.name = name
        self.robot_id = robot_id
        self.巡检进行中 = busy
        self.received = []

    def 接收巡检任务(self, payload):
        self.received.append(payload)
        return {"accepted": True, "inspection_id": payload[0]["id"],
                "waypoint_count": sum(len(s["waypoint"]) for s in payload)}


class BoomRobot(FakeRobot):
    def 接收巡检任务(self, payload):
        raise RuntimeError("设备炸了")


def _dispatch_job(tmp_path, **kw):
    write_spec(tmp_path, "t1.json", group("root", [
        wp("a", "W1", floor=1, children=[action("A1", 1)]),
        wp("b", "W2", floor=2, children=[action("A2", 1)]),
    ]))
    return _job([{"source": "t1.json", "include_all": True, "waypoint_ids": []}], **kw)


def test_dispatch_ok(tmp_path):
    job = _dispatch_job(tmp_path, plan_name="夜巡")
    r = FakeRobot()
    out = dispatch_inspection(job, robot=r, root_dir=tmp_path)
    assert out["accepted"] is True
    assert len(r.received) == 1
    payload = r.received[0]
    assert [s["floor"] for s in payload] == [1, 2]
    assert out["waypoint_count"] == 2 and out["action_count"] == 2
    assert out["plan_name"] == "夜巡"
    assert out["inspection_id"] == payload[0]["id"]


def test_dispatch_no_robot(tmp_path):
    out = dispatch_inspection(_dispatch_job(tmp_path), robot=None, root_dir=tmp_path)
    # robot=None 会去取全局实例；测试环境没有机器人，必须是"拒了"而不是抛异常
    assert out["accepted"] is False
    assert "机器人" in out["reason"]


def test_dispatch_robot_mismatch(tmp_path):
    job = _dispatch_job(tmp_path, robot_name="别的机器人")
    out = dispatch_inspection(job, robot=FakeRobot(), root_dir=tmp_path)
    assert out["accepted"] is False
    assert "别的机器人" in out["reason"]


def test_dispatch_robot_match_by_id(tmp_path):
    job = _dispatch_job(tmp_path, robot_name="R-1")
    r = FakeRobot(name="机器人1", robot_id="R-1")
    assert dispatch_inspection(job, robot=r, root_dir=tmp_path)["accepted"] is True


def test_dispatch_busy_does_not_build(tmp_path):
    job = _dispatch_job(tmp_path)
    r = FakeRobot(busy=True)
    out = dispatch_inspection(job, robot=r, root_dir=tmp_path)
    assert out["accepted"] is False and out["reason"] == "busy"
    assert r.received == []          # 忙就别读盘建树了


def test_dispatch_robot_raises(tmp_path):
    job = _dispatch_job(tmp_path)
    out = dispatch_inspection(job, robot=BoomRobot(), root_dir=tmp_path)
    assert out["accepted"] is False
    assert "设备炸了" in out["reason"]


def test_dispatch_bad_plan(tmp_path):
    out = dispatch_inspection(_job([]), robot=FakeRobot(), root_dir=tmp_path)
    assert out["accepted"] is False
    assert "航点" in out["reason"]


def test_install_default_trigger_is_idempotent():
    clear_inspection_trigger()
    try:
        assert install_default_trigger() is dispatch_inspection
        sentinel = lambda p: None      # noqa: E731
        set_inspection_trigger(sentinel)
        assert install_default_trigger() is sentinel      # 已注册的不被顶掉
    finally:
        clear_inspection_trigger()


def test_get_trigger_roundtrip():
    clear_inspection_trigger()
    try:
        assert get_inspection_trigger() is None
        install_default_trigger()
        assert get_inspection_trigger() is dispatch_inspection
    finally:
        clear_inspection_trigger()
