"""检测流程执行逻辑（`app/prefab/detect_pipeline.py`）的回归。

锁的是**语义**，不是实现细节：哪个节点是闸门、拦下之后后面还跑不跑、
阈值/窗口/连续次数这些边界。这些错了不会报错，只会"该报的没报"或"刷爆告警"，
而编排侧（节点定义）与执行侧（本模块）一旦理解不一致，现场最难查。

树一律用 `registry.build` 从 spec 造（跟真实文件走同一条路），不手搓对象——
否则节点字段名改了这里还在测旧的。
"""
from __future__ import annotations

from datetime import datetime

from app.prefab import registry
from app.prefab.detect_pipeline import (
    DetectEvent, DetectState, FlowRun, confirm_hit, level_at_least, parse_hm,
    point_in_polygon, render, run_flow, throttle_allows,
)


def tree(*children, **props):
    """造一棵流程树：根 DetectPipelineNode + 若干子节点。"""
    return registry.build({
        "type": "DetectPipelineNode",
        "properties": {"name": "流程", **props},
        "children": list(children),
    })


def node(ntype, **props):
    return {"type": ntype, "properties": {"name": ntype, **props}}


def group(*children, **props):
    return {"type": "DetectGroupNode", "properties": {"name": "分组", **props},
            "children": list(children)}


def ev(**kw):
    base = dict(algorithm="person", label="person", confidence=0.9,
                source="抓拍图", frame_index=0)
    base.update(kw)
    return DetectEvent(**base)


def run(root, event=None, **kw):
    return run_flow(root, event or ev(), **kw)


# ---------------------------------------------------------------- 1. 闸门：拦下就不往下走

def test_empty_flow_passes():
    r = run(tree())
    assert r.passed and r.actions == []


def test_gate_source_mismatch():
    r = run(tree(node("FrameSourceNode", source="热像仪")), ev(source="抓拍图"))
    assert not r.passed
    assert "热像仪" in r.stopped_by


def test_gate_stops_later_actions():
    """闸门在后处理之前：被拦下时**一个动作都不产生**。"""
    root = tree(node("FrameSourceNode", source="热像仪"),
                node("AlarmNode", level="严重告警", title="x"))
    r = run(root, ev(source="抓拍图"))
    assert not r.passed and r.actions == []


def test_actions_before_gate_still_emitted():
    """顺序就是执行顺序：后处理排在闸门**之前**，动作照样产生。"""
    root = tree(node("AlarmNode", level="严重告警", title="x"),
                node("FrameSourceNode", source="热像仪"))
    r = run(root, ev(source="抓拍图"))
    assert not r.passed and len(r.actions) == 1


def test_disabled_subtree_skipped():
    """enabled=false 的**整棵子树**都不跑（与前端变灰的范围一致）。"""
    root = tree(group(node("AlarmNode", title="不该报"), enabled=False))
    assert run(root).actions == []


def test_disabled_gate_does_not_stop():
    root = tree(node("FrameSourceNode", source="热像仪", enabled=False),
                node("AlarmNode", title="要报"))
    r = run(root, ev(source="抓拍图"))
    assert r.passed and len(r.actions) == 1


# ---------------------------------------------------------------- 2. 抽帧 / 区域 / 时段

def test_frame_skip():
    root = tree(node("FrameSkipNode", every_n_frames=5), node("AlarmNode"))
    assert not run(root, ev(frame_index=3)).passed   # 3 % 5 != 0
    assert run(root, ev(frame_index=0)).passed       # 第 0 帧一定处理
    assert run(root, ev(frame_index=5)).passed


def test_frame_skip_one_means_all():
    root = tree(node("FrameSkipNode", every_n_frames=1), node("AlarmNode"))
    assert run(root, ev(frame_index=7)).passed


def test_roi_inside_only():
    roi = [{"x": 0.0, "y": 0.0}, {"x": 1.0, "y": 0.0},
           {"x": 1.0, "y": 1.0}, {"x": 0.0, "y": 1.0}]
    root = tree(node("RoiFilterNode", roi=roi, mode="只处理框内"), node("AlarmNode"))
    assert run(root, ev(x=0.5, y=0.5)).passed
    assert not run(root, ev(x=1.5, y=0.5)).passed


def test_roi_exclude_mode():
    roi = [{"x": 0.0, "y": 0.0}, {"x": 0.5, "y": 0.0}, {"x": 0.5, "y": 0.5}, {"x": 0.0, "y": 0.5}]
    root = tree(node("RoiFilterNode", roi=roi, mode="排除框内"), node("AlarmNode"))
    assert not run(root, ev(x=0.2, y=0.2)).passed   # 落在排除区内 -> 拦
    assert run(root, ev(x=0.8, y=0.8)).passed


def test_roi_missing_means_no_filter():
    """区域没画出来 / 事件没位置 -> **不过滤**（宁可放行也不能静默拦掉告警）。"""
    root = tree(node("RoiFilterNode", roi=[], mode="只处理框内"), node("AlarmNode"))
    assert run(root, ev(x=0.9, y=0.9)).passed
    root2 = tree(node("RoiFilterNode", roi=[{"x": 0, "y": 0}, {"x": 1, "y": 0}, {"x": 1, "y": 1}]),
                 node("AlarmNode"))
    assert run(root2, ev()).passed   # 事件没带 x/y


def test_time_window_inside_and_outside():
    root = tree(node("TimeWindowNode", start_time="08:00", end_time="18:00"),
                node("AlarmNode"))
    assert run(root, now_dt=datetime(2026, 9, 22, 10, 0)).passed
    assert not run(root, now_dt=datetime(2026, 9, 22, 20, 0)).passed


def test_time_window_cross_midnight_not_supported():
    """跨零点按**不限制**处理（与编排侧同一取舍：含糊处理不如放行）。"""
    root = tree(node("TimeWindowNode", start_time="22:00", end_time="06:00"),
                node("AlarmNode"))
    assert run(root, now_dt=datetime(2026, 9, 22, 2, 0)).passed


def test_time_window_weekday():
    root = tree(node("TimeWindowNode", start_time="00:00", end_time="23:59",
                     every_day=False, days=[1, 2, 3, 4, 5]), node("AlarmNode"))
    # 2026-09-22 是周二
    assert run(root, now_dt=datetime(2026, 9, 22, 10, 0)).passed
    assert not run(root, now_dt=datetime(2026, 9, 26, 10, 0)).passed  # 周六


# ---------------------------------------------------------------- 3. 节流 / 连续确认

def test_throttle_window():
    root = tree(node("ThrottleNode", window_seconds=10, max_events=1),
                node("AlarmNode"))
    st = DetectState()
    assert run(root, state=st, key="k", now=100.0).passed
    assert not run(root, state=st, key="k", now=101.0).passed   # 窗口内第二条
    assert run(root, state=st, key="k", now=120.0).passed       # 过了窗口


def test_throttle_zero_means_block_all():
    root = tree(node("ThrottleNode", window_seconds=10, max_events=0), node("AlarmNode"))
    assert not run(root, state=DetectState(), now=1.0).passed


def test_throttle_no_window_means_off():
    root = tree(node("ThrottleNode", window_seconds=0, max_events=1), node("AlarmNode"))
    st = DetectState()
    assert run(root, state=st, now=1.0).passed and run(root, state=st, now=1.1).passed


def test_confirm_requires_n_hits():
    root = tree(node("ConfirmNode", require_count=3, within_seconds=30),
                node("AlarmNode"))
    st = DetectState()
    assert not run(root, state=st, now=1.0).passed
    assert not run(root, state=st, now=2.0).passed
    assert run(root, state=st, now=3.0).passed


def test_confirm_resets_after_window():
    root = tree(node("ConfirmNode", require_count=2, within_seconds=10),
                node("AlarmNode"))
    st = DetectState()
    assert not run(root, state=st, now=1.0).passed
    assert not run(root, state=st, now=100.0).passed   # 超窗 -> 计数清零，重新数
    assert run(root, state=st, now=101.0).passed       # 窗内第二次 -> 放行


def test_confirm_one_means_immediate():
    root = tree(node("ConfirmNode", require_count=1), node("AlarmNode"))
    assert run(root).passed


def test_confirm_hit_direct():
    st = DetectState()
    assert confirm_hit(st, "k", 1.0, 2, 0)[0] is False
    assert confirm_hit(st, "k", 2.0, 2, 0)[0] is True


def test_throttle_allows_direct():
    st = DetectState()
    assert throttle_allows(st, "k", 1.0, 5.0, 2)[0] is True
    assert throttle_allows(st, "k", 2.0, 5.0, 2)[0] is True
    assert throttle_allows(st, "k", 3.0, 5.0, 2)[0] is False


# ---------------------------------------------------------------- 4. 算法 / 结果过滤

def test_detector_algorithm_mismatch():
    # 人员入侵节点只认 person_intrusion 事件；事件算法对不上则拦下
    root = tree(node("PersonIntrusionNode"), node("AlarmNode"))
    assert not run(root, ev(algorithm="person")).passed


def test_detector_threshold():
    root = tree(node("PersonIntrusionNode", threshold=0.8), node("AlarmNode"))
    assert not run(root, ev(algorithm="person_intrusion", confidence=0.5)).passed
    assert run(root, ev(algorithm="person_intrusion", confidence=0.95)).passed


def test_detector_labels_whitelist():
    root = tree(node("PersonIntrusionNode", labels=["person"]),
                node("AlarmNode"))
    assert not run(root, ev(algorithm="person_intrusion", label="cat")).passed
    assert run(root, ev(algorithm="person_intrusion", label="person")).passed


# ---------------------------------------------------------------- 4b. 算法节点子类化

def test_algorithm_nodes_match_algorithms_json():
    """algorithms.json 里每个算法 id 都有一个注册的 DetectorNode 子类，反之亦然。"""
    import json
    from pathlib import Path
    from app.prefab import registry
    from app.prefab.nodes.detect import DetectorNode

    algo_json = json.loads(
        (Path(__file__).resolve().parents[1] / "data" / "algorithms.json")
        .read_text(encoding="utf-8"))
    expect = {a["id"] for a in algo_json["algorithms"]}

    got = {getattr(cls, "algorithm_id", ""): name
           for name, cls in registry.registered_types().items()
           if isinstance(cls, type) and issubclass(cls, DetectorNode)}
    assert set(got) == expect
    assert got["person_intrusion"] == "PersonIntrusionNode"


def test_algorithm_node_pins_algorithm_field():
    """节点类型即算法身份：只读 algorithm 字段默认值被固定成该算法 id。"""
    from app.prefab import registry
    cls = registry.registered_types()["PersonIntrusionNode"]
    assert cls().algorithm == "person_intrusion"


def test_algorithm_node_types_filtered_by_tree():
    """node-types 按继承过滤：算法节点进检测树、不串门到航点树；抽象基类不进。"""
    from app.prefab import registry
    detect_types = registry.schema_for_base("DetectNodeBase")
    assert "PersonIntrusionNode" in detect_types
    assert "MeterDigitalNode" in detect_types and "SwitchStateNode" in detect_types
    assert "DetectorNode" not in detect_types            # 抽象基类不注册
    assert "PersonIntrusionNode" not in registry.schema_for_base("WaypointNodeBase")


def test_meter_node_has_category_fields():
    """表计读数节点带类别专属字段（单位/量程/小数位）；安全告警节点没有表计字段。"""
    from app.prefab import registry
    types = registry.registered_types()
    meter = types["MeterDigitalNode"](unit="A", range_max=100, decimals=2)
    assert (meter.unit, meter.range_max, meter.decimals) == ("A", 100.0, 2)
    assert "unit" not in types["PersonIntrusionNode"].model_fields


def test_result_filter_min_confidence():
    root = tree(node("ResultFilterNode", min_confidence=0.95), node("AlarmNode"))
    assert not run(root, ev(confidence=0.9)).passed


# ---------------------------------------------------------------- 5. 后处理动作

def test_alarm_action_fields():
    root = tree(node("AlarmNode", level="严重告警", template="t.prefab.json",
                     title="{point_name} 告警", content="置信度 {confidence}",
                     dedup_seconds=300))
    r = run(root, ev(confidence=0.91, point_name="3号柜"))
    a = r.actions[0]
    assert a["kind"] == "alarm" and a["level"] == "严重告警"
    assert a["title"] == "3号柜 告警" and a["content"] == "置信度 0.91"
    assert a["dedup_seconds"] == 300


def test_sms_gated_by_min_level():
    root = tree(node("AlarmNode", level="预警"),
                node("SmsNotifyNode", min_level="严重告警", receivers=["138"]))
    r = run(root)
    assert r.actions and all(a["kind"] != "sms" for a in r.actions)
    assert any("未达" in n for n in r.notes)


def test_email_gated_by_min_level():
    root = tree(node("AlarmNode", level="严重告警"),
                node("EmailNotifyNode", min_level="一般告警", to=["a@b.c"]))
    assert any(a["kind"] == "email" for a in run(root).actions)


def test_all_action_kinds():
    root = tree(node("EvidenceNode", dir="data/evidence"),
                node("AlarmNode", level="一般告警"),
                node("ForwardNode", url="http://x", body="lvl={level}"),
                node("SmsNotifyNode", min_level="一般告警", receivers=["138"]),
                node("EmailNotifyNode", min_level="一般告警", to=["a@b.c"]))
    kinds = [a["kind"] for a in run(root).actions]
    assert kinds == ["evidence", "alarm", "forward", "sms", "email"]


def test_forward_body_rendered():
    root = tree(node("AlarmNode", level="严重告警"),
                node("ForwardNode", url="http://x", body="{point_name}/{level}"))
    fwd = [a for a in run(root, ev(point_name="3号柜")).actions if a["kind"] == "forward"][0]
    assert fwd["body"] == "3号柜/严重告警"


def test_preprocess_only_notes():
    root = tree(node("ImagePreprocessNode", grayscale=True), node("AlarmNode"))
    r = run(root)
    assert any("预处理" in n for n in r.notes) and len(r.actions) == 1


# ---------------------------------------------------------------- 6. 纯函数

def test_level_at_least():
    assert level_at_least("严重告警", "预警") and level_at_least("一般告警", "一般告警")
    assert not level_at_least("预警", "严重告警")
    assert level_at_least("不存在", "危急告警") is False   # 未知级别按最低档


def test_parse_hm():
    assert parse_hm("08:30") == 8 * 60 + 30
    assert parse_hm("") is None and parse_hm("abc") is None
    assert parse_hm("25:00") is None


def test_point_in_polygon():
    sq = [{"x": 0, "y": 0}, {"x": 1, "y": 0}, {"x": 1, "y": 1}, {"x": 0, "y": 1}]
    assert point_in_polygon(0.5, 0.5, sq) is True
    assert point_in_polygon(2.0, 0.5, sq) is False
    assert point_in_polygon(0.5, 0.5, [{"x": 0, "y": 0}]) is False  # 围不出区域


def test_render_keeps_unknown_placeholder():
    """不认得的占位**原样留着**，不替换成空串（否则看不出是没配还是没取到）。"""
    e = ev(point_name="3号柜", confidence=0.5)
    assert render("{point_name}-{confidence}-{nope}", e) == "3号柜-0.50-{nope}"


def test_run_returns_flowrun():
    assert isinstance(run(tree()), FlowRun)


# ---------------------------------------------------------------- 7. 数值告警 / 数值范围告警

def test_numeric_alarm_hit():
    root = tree(node("NumericAlarmNode", metric="温度", op=">", threshold=80),
                node("EvidenceNode"))
    assert any(a["kind"] == "numeric_alarm" for a in run(root, ev(value=85)).actions)
    assert not any(a["kind"] == "numeric_alarm" for a in run(root, ev(value=70)).actions)


def test_numeric_alarm_operators():
    for op, val, want in [(">", 81, True), (">", 80, False), (">=", 80, True),
                          ("<", 79, True), ("<=", 80, True), ("<", 80, False),
                          ("==", 80, True), ("==", 81, False), ("!=", 81, True)]:
        root = tree(node("NumericAlarmNode", op=op, threshold=80))
        got = any(a["kind"] == "numeric_alarm" for a in run(root, ev(value=val)).actions)
        assert got is want, (op, val)


def test_numeric_alarm_without_value():
    """事件没带数值 -> 跳过（不能默认成 0，否则"没采到"会变成一堆假低温告警）。"""
    root = tree(node("NumericAlarmNode", op=">", threshold=80))
    r = run(root, ev())        # value=None
    assert r.actions == [] and any("没带数值" in n for n in r.notes)


def test_numeric_alarm_title_rendered():
    root = tree(node("NumericAlarmNode", metric="温度", unit="℃", op=">", threshold=80,
                     title="{point_name} {metric}{value}{unit}"))
    a = [x for x in run(root, ev(value=85.5, point_name="3号柜")).actions
         if x["kind"] == "numeric_alarm"][0]
    assert a["title"] == "3号柜 温度85.5℃" and a["unit"] == "℃"


def test_range_alarm_outside():
    root = tree(node("RangeAlarmNode", min_value=60, max_value=80, mode="区间外告警"))
    assert any(a["kind"] == "range_alarm" for a in run(root, ev(value=95)).actions)
    assert not any(a["kind"] == "range_alarm" for a in run(root, ev(value=70)).actions)


def test_range_alarm_inside_mode():
    root = tree(node("RangeAlarmNode", min_value=60, max_value=80, mode="区间内告警"))
    assert not any(a["kind"] == "range_alarm" for a in run(root, ev(value=95)).actions)
    assert any(a["kind"] == "range_alarm" for a in run(root, ev(value=70)).actions)


def test_range_alarm_inclusive_boundary():
    root = tree(node("RangeAlarmNode", min_value=60, max_value=80, inclusive=True))
    assert not any(a["kind"] == "range_alarm" for a in run(root, ev(value=80)).actions)
    root2 = tree(node("RangeAlarmNode", min_value=60, max_value=80, inclusive=False))
    assert any(a["kind"] == "range_alarm" for a in run(root2, ev(value=80)).actions)


def test_range_alarm_reversed_never_fires():
    """上下限填反 = 空区间 -> **不报**（宁可漏报，也不能把所有值都判成越界）。"""
    root = tree(node("RangeAlarmNode", min_value=80, max_value=60))
    r = run(root, ev(value=70))
    assert r.actions == [] and any("配反" in n for n in r.notes)


def test_numeric_alarm_does_not_stop_flow():
    """数值告警是**动作**不是闸门：判据不满足也只跳过自己，后面照跑。"""
    root = tree(node("NumericAlarmNode", op=">", threshold=80),
                node("AlarmNode", level="一般告警"))
    r = run(root, ev(value=10))
    assert r.passed and [a["kind"] for a in r.actions] == ["alarm"]


def test_levels_four_tiers():
    """四级告警：预警 < 一般告警 < 严重告警 < 危急告警。"""
    assert level_at_least("危急告警", "严重告警")
    assert level_at_least("严重告警", "一般告警")
    assert level_at_least("一般告警", "预警")
    assert not level_at_least("预警", "危急告警")


def test_levels_match_node_options():
    """执行侧的 LEVELS 必须与节点定义的 LEVEL_OPTIONS **一致**（否则级别比大小会错）。"""
    from app.prefab.nodes.detect import LEVEL_OPTIONS
    from app.prefab.detect_pipeline import LEVELS
    assert tuple(LEVEL_OPTIONS) == LEVELS


# ---------------------------------------------------------------- 8. 告警级别：三种告警节点的 level 都要生效

def test_numeric_alarm_level_written_to_action():
    """纯数值流程（没有事件告警节点）：动作的 level 必须是节点自己配的级别，
    不能退化成 run_flow 的默认"预警"。"""
    root = tree(node("NumericAlarmNode", metric="温度", op=">", threshold=80,
                     level="严重告警"))
    a = [x for x in run(root, ev(value=85)).actions if x["kind"] == "numeric_alarm"][0]
    assert a["level"] == "严重告警"


def test_numeric_alarm_level_feeds_sms_gate():
    """数值节点配的级别要参与短信/邮件的 min_level 闸门——
    纯数值流程里没有 AlarmNode，不能靠预扫事件告警节点定级。"""
    root = tree(node("NumericAlarmNode", op=">", threshold=80, level="严重告警"),
                node("SmsNotifyNode", min_level="一般告警", receivers=["138"]))
    r = run(root, ev(value=85))
    # 严重告警 >= 一般告警，应该发短信
    assert any(a["kind"] == "sms" for a in r.actions)


def test_range_alarm_level_written_to_action():
    root = tree(node("RangeAlarmNode", min_value=60, max_value=80,
                     level="危急告警"))
    a = [x for x in run(root, ev(value=95)).actions if x["kind"] == "range_alarm"][0]
    assert a["level"] == "危急告警"


def test_multiple_alarms_take_highest_level():
    """一条流程里多个告警节点都命中时，短信闸门按**报出的最高级别**判，
    而不是只认第一个告警节点。"""
    root = tree(
        node("NumericAlarmNode", op=">", threshold=80, level="预警"),
        node("RangeAlarmNode", min_value=90, max_value=100, mode="区间内告警",
             level="危急告警"),
        node("SmsNotifyNode", min_level="严重告警", receivers=["138"]),
    )
    # value=95：两个判据都命中，报出的最高级别=危急告警 >= 严重告警
    r = run(root, ev(value=95))
    assert any(a["kind"] == "sms" for a in r.actions)


def test_unfired_alarm_does_not_raise_level():
    """判据不满足的告警节点（这次没报）不抬高级别——它这次没报就不该影响分流。"""
    root = tree(
        node("NumericAlarmNode", op=">", threshold=80, level="严重告警"),  # value=10 不命中
        node("AlarmNode", level="预警"),
        node("SmsNotifyNode", min_level="严重告警", receivers=["138"]),
    )
    r = run(root, ev(value=10))
    assert not any(a["kind"] == "sms" for a in r.actions)
