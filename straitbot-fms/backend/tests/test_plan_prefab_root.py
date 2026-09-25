"""巡检计划文件**新建时的根**：必须是分组 `PlanGroupNode`。

一个文件只有一个根。根是 `InspectionPlanNode`（单条计划）就等于"一个文件只能
配一条计划"——同一台机器人要排"白天每小时一遍、夜里两小时一遍"得开两个文件，
航点树 `source` 之类的配置还得抄两遍。根是分组，下面挂 N 条计划。

老文件的根可能是单条计划：那由前端在**内存里**包一层分组（`ensureGroupRoot`），
不写盘，用户点保存才落盘——所以这里只锁"新建出来的根"。
"""
from app.prefab import registry
from app.routers.plan_prefab import _plan_root


def test_root_is_group():
    root = _plan_root("日常巡检")["root"]
    assert root["type"] == "PlanGroupNode"
    assert root["properties"]["name"] == "日常巡检"
    assert root["properties"]["enabled"] is True
    assert root["children"] == []


def test_root_builds():
    """能 build 成功才说明字段与节点模型对得上（保存接口就是这么校验的）。"""
    node = registry.build(_plan_root("x")["root"])
    assert node.type == "PlanGroupNode"
    assert node.child_nodes == []


def test_one_file_can_hold_many_plans():
    """根是分组 -> 一个文件里能挂多条计划，每条各自带元信息与启停。"""
    spec = _plan_root("multi")
    spec["root"]["children"] = [
        {"type": "InspectionPlanNode",
         "properties": {"name": "白天", "plan_id": "P-1", "enabled": True}},
        {"type": "InspectionPlanNode",
         "properties": {"name": "夜间", "plan_id": "P-2", "enabled": False, "priority": 2}},
    ]
    node = registry.build(spec["root"])
    assert [c.type for c in node.child_nodes] == ["InspectionPlanNode"] * 2
    # 启停是**每条计划自己**的属性（停用的那条连同它的子树不参与运行）
    assert node.child_nodes[0].enabled is True
    assert node.child_nodes[1].enabled is False


def test_plan_root_has_no_plan_fields():
    """分组根不该带上计划专属字段（那些属于 InspectionPlanNode）。"""
    props = _plan_root("x")["root"]["properties"]
    assert "plan_id" not in props
    assert "robot_name" not in props
    assert "priority" not in props
