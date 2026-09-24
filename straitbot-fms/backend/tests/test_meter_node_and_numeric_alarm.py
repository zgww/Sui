"""`MeterAlgorithmNode` 字段下线 + 数值告警取 `parameter` 的回归。

两个需求（2026-09-24）：

1. `MeterAlgorithmNode` 是"一个节点 + 算法下拉"对接**现有算法推理服务**的，
   推理服务不认置信度阈值等参数，所以 `threshold` / `params` / 只读 `algorithm`
   从检视器下线，只留 `labels` / `max_results` 两个**结果口径**字段。
   ⚠️ 下线 ≠ 删字段：`extra="forbid"` 是故意开着的，真删字段会让存量 prefab
   当场打不开。所以模型上留着、schema 里摘掉、执行侧停止读取。

2. 数值告警从**测点识别结果的 `parameter`** 取值来比。这里锁的是那条曾经
   把读数整片掐掉的 `name.startswith("0_")` 判断 —— `name` 是 panel_list 的
   算法编码，63 个算法里 37 个以 `0_` 开头（含「电流表_中_*」「电压表_中_*」
   这些**本来就要读数**的表计），判断一错，数值告警永远不触发。
"""
from __future__ import annotations

from app.prefab import registry
from app.prefab.detect_pipeline import (
    DetectEvent, _NO_THRESHOLD_GATE_TYPES, run_flow,
)
from app.services.alarm_processor import _build_event, _read_value

#: 检视器上不该再出现的字段
RETIRED = ("algorithm", "threshold", "params")
#: 保留的两个结果口径字段（外加算法选择本身）
KEPT = ("panel_algorithm", "labels", "max_results")


def visible_props(node_type: str) -> set[str]:
    return set(registry.node_schema(node_type).get("properties", {}))


def pipeline(*children, **props):
    return registry.build({
        "type": "DetectPipelineNode",
        "properties": {"name": "流程", **props},
        "children": list(children),
    })


def node(ntype, **props):
    return {"type": ntype, "properties": {"name": ntype, **props}}


def event(value=None, **kw):
    base = dict(algorithm="", label="", confidence=0.9, source="抓拍图")
    base.update(kw)
    base["value"] = value
    return DetectEvent(**base)


# ============================================================ 1. 字段下线

def test_meter_node_hides_retired_fields_from_inspector():
    props = visible_props("MeterAlgorithmNode")
    for f in RETIRED:
        assert f not in props, f"{f} 应该已从检视器下线"
    for f in KEPT:
        assert f in props, f"{f} 应该保留"


def test_meter_node_fields_reachable_through_node_types_api():
    """`node-types` 走的是 `schema_for_base`，两条路都得摘干净。"""
    types = registry.schema_for_base("DetectNodeBase")
    props = set(types["MeterAlgorithmNode"]["schema"].get("properties", {}))
    for f in RETIRED:
        assert f not in props


def test_other_algorithm_nodes_untouched():
    """只动 MeterAlgorithmNode：其他算法子类的阈值/参数一个都不能少。"""
    for ntype in ("PersonIntrusionNode", "MeterDigitalNode"):
        props = visible_props(ntype)
        assert "threshold" in props and "params" in props, ntype


def test_legacy_tree_with_retired_fields_still_builds():
    """存量 prefab 里带着 threshold/params/algorithm 的照常打开（不撞 extra=forbid）。"""
    root = registry.build({
        "type": "DetectPipelineNode",
        "properties": {"name": "人员入侵"},
        "children": [{
            "type": "MeterAlgorithmNode",
            "properties": {"name": "人员入侵", "enabled": True, "algorithm": "",
                           "threshold": 0, "labels": [], "max_results": 0,
                           "params": {}, "note": "",
                           "panel_algorithm": "0_0_0_4010_0_0"},
        }],
    })
    box = root.child_nodes[0]
    assert box.panel_algorithm == "0_0_0_4010_0_0"
    assert box.threshold == 0            # 字段还在模型上（只是不渲染）


def test_meter_node_ignores_legacy_threshold_in_gate():
    """阈值已下线 -> 老数据里残留的旧值也不能再拦结果。"""
    assert "MeterAlgorithmNode" in _NO_THRESHOLD_GATE_TYPES
    root = pipeline(
        node("MeterAlgorithmNode", panel_algorithm="0_0_0_4010_0_0", threshold=0.99),
        node("AlarmNode", title="x"),
    )
    r = run_flow(root, event(confidence=0.10))
    assert r.passed, f"不该被已下线的阈值拦下：{r.stopped_by}"


def test_other_detectors_still_gated_by_threshold():
    """对照组：别的算法节点阈值闸门还在（别把闸门一起删了）。"""
    root = pipeline(
        node("PersonIntrusionNode", threshold=0.8),
        node("AlarmNode", title="x"),
    )
    assert not run_flow(root, event(algorithm="person_intrusion", confidence=0.5)).passed


def test_meter_node_labels_gate_still_works():
    """保留的字段要真的有用：类别白名单仍然拦。"""
    root = pipeline(
        node("MeterAlgorithmNode", labels=["吸烟"]),
        node("AlarmNode", title="x"),
    )
    assert not run_flow(root, event(label="人员越界")).passed
    assert run_flow(root, event(label="吸烟")).passed


# ============================================================ 2. 数值取 parameter

def test_read_value_uses_parameter():
    assert _read_value({"name": "1_0_0_1_53_0", "parameter": "210"}) == 210.0
    assert _read_value({"name": "x", "parameter": "-3.75"}) == -3.75


def test_read_value_not_blocked_by_zero_underscore_panel_name():
    """🔴 回归点：`name` 是 panel_list 的算法编码，不是"安全/二值类"的标记。

    下面两个都是**要读数**的表计，名字却以 `0_` 开头 —— 旧实现在这里 return None，
    数值告警永远不触发。
    """
    assert _read_value({"name": "0_0_0_1_17_0", "parameter": "82.5"}) == 82.5   # 电流表_中_1.5KA
    assert _read_value({"name": "0_0_0_1_23_0", "parameter": "11.8"}) == 11.8   # 电压表_中_12KV


def test_read_value_returns_none_without_number():
    assert _read_value({"name": "0_0_0_3001_0_0", "parameter": ""}) is None
    assert _read_value({"name": "0_0_0_3005_0_0", "parameter": "正常"}) is None
    assert _read_value({}) is None


def test_numeric_alarm_fires_on_parameter_from_result_box():
    """端到端：结果框 -> DetectEvent -> 流程 -> 告警动作（用户当前那条流程）。"""
    rb = {"name": "0_0_0_4010_0_0", "parameter": "1", "display": "吸烟",
          "code": "0", "confidence": "1"}
    ev, _ = _build_event(rb, "", "", {})
    root = pipeline(
        node("MeterAlgorithmNode", panel_algorithm="0_0_0_4010_0_0"),
        node("NumericAlarmNode", op="==", threshold=1, metric="吸烟", title="有人吸烟"),
    )
    r = run_flow(root, ev)
    assert [a["kind"] for a in r.actions] == ["numeric_alarm"]


def test_numeric_alarm_skips_when_parameter_is_zero():
    rb = {"name": "0_0_0_4010_0_0", "parameter": "0", "display": "正常",
          "code": "0", "confidence": "1"}
    ev, _ = _build_event(rb, "", "", {})
    root = pipeline(
        node("MeterAlgorithmNode", panel_algorithm="0_0_0_4010_0_0"),
        node("NumericAlarmNode", op="==", threshold=1),
    )
    assert run_flow(root, ev).actions == []


def test_meter_reading_alarm_fires_on_zero_underscore_algorithm():
    """修复前必失败的场景：0_ 前缀的表计读数超限。"""
    rb = {"name": "0_0_0_1_17_0", "parameter": "82.5", "display": "82.5",
          "code": "0", "confidence": "1"}
    ev, _ = _build_event(rb, "", "", {})
    root = pipeline(
        node("MeterAlgorithmNode", panel_algorithm="0_0_0_1_17_0"),
        node("NumericAlarmNode", op=">", threshold=80, metric="电流", unit="A"),
    )
    acts = [a for a in run_flow(root, ev).actions if a["kind"] == "numeric_alarm"]
    assert acts and acts[0]["value"] == 82.5
