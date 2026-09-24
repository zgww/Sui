"""巡检计划调度**节点**与「启动树」的冒烟测试。

纯逻辑（时刻展开、去重）在 `test_plan_scheduler.py`；这里只测三件"接错了就整个
功能等于没有"的事：

1. 节点注册了（否则 启动.prefab.json 里配上去是未知节点类型）；
2. `on_active` 真的起了线程、到点真的触发（emit `inspection_due`）、
   `on_deactive` 真的把线程停掉；
3. 启动时**启动树先激活**，且 `plan/` 目录不会被当成规则树加载
   （计划树是数据，由调度节点按文件消费）。
"""
import json
import threading
import time
from datetime import datetime, timedelta
from pathlib import Path
from zoneinfo import ZoneInfo

import pytest

from app.config import DATA_DIR
from app.prefab import registry
from app.prefab.base import Context
from app.prefab.loader import PrefabLoader
from app.prefab.runtime import PrefabRuntime


def _now_slot_str():
    """当前（Asia/Shanghai）这一分钟，用来造一条"此刻正好到期"的调度。"""
    return datetime.now(ZoneInfo("Asia/Shanghai")).strftime("%H:%M")


def _plan_spec(start, end, interval=1):
    return {
        "name": "计划",
        "description": "",
        "root": {
            "type": "PlanGroupNode",
            "properties": {"name": "根", "enabled": True},
            "children": [{
                "type": "InspectionPlanNode",
                "properties": {"name": "冒烟", "plan_id": "SMOKE-1", "enabled": True},
                "children": [{
                    "type": "DailyScheduleNode",
                    "properties": {"name": "调度", "enabled": True,
                                   "start_time": start, "end_time": end,
                                   "interval_minutes": interval},
                }],
            }],
        },
    }


def test_node_registered():
    types = registry.registered_types()
    assert "InspectionPlanSchedulerNode" in types
    schema = registry.node_schema("InspectionPlanSchedulerNode")
    # dry_run 必须默认开：真下发映射还没接通，配上去先观察
    assert schema["properties"]["dry_run"]["default"] is True
    assert schema["properties"]["poll_interval"]["default"] == 30


def test_thread_starts_fires_and_stops(tmp_path, monkeypatch):
    monkeypatch.setattr("app.config.DATA_DIR", tmp_path)   # 账本写到临时目录
    plans = tmp_path / "plans"
    plans.mkdir()
    now = _now_slot_str()
    (plans / "smoke.prefab.json").write_text(
        json.dumps(_plan_spec(now, now), ensure_ascii=False), encoding="utf-8")

    node = registry.build({
        "type": "InspectionPlanSchedulerNode",
        "properties": {"name": "调度", "plan_dir": str(plans), "poll_interval": 1,
                       "misfire_grace": 600},
    })
    ctx = Context()
    got = threading.Event()
    seen = []
    ctx.on("inspection_due", lambda p: (seen.append(p), got.set()))

    node.activate(ctx)
    try:
        assert node.status()["running"] is True
        assert got.wait(timeout=10), "10 秒内没有触发（调度线程没跑起来？）"
        payload = seen[0]
        assert payload["plan_id"] == "SMOKE-1"
        assert payload["dry_run"] is True          # 默认不下发
        # 同一槽位不该被重复触发
        time.sleep(2)
        assert len(seen) == 1, f"同一时刻被触发了 {len(seen)} 次"
    finally:
        node.deactivate(ctx)
    assert node.status()["running"] is False


def test_boot_tree_activated_first(tmp_path):
    """启动树优先激活：常驻任务要先起来，别的规则链才靠得住。"""
    (tmp_path / "启动.prefab.json").write_text(json.dumps({
        "name": "启动", "description": "",
        "root": {"type": "Sequence", "properties": {"name": "启动", "enabled": True},
                 "children": []},
    }, ensure_ascii=False), encoding="utf-8")
    (tmp_path / "rules").mkdir()
    (tmp_path / "rules" / "其它.prefab.json").write_text(json.dumps({
        "name": "其它", "description": "",
        "root": {"type": "Sequence", "properties": {"name": "其它", "enabled": True},
                 "children": []},
    }, ensure_ascii=False), encoding="utf-8")
    # plan/ 是**数据**目录，不该被当成规则树加载
    (tmp_path / "plan").mkdir()
    (tmp_path / "plan" / "计划.prefab.json").write_text(json.dumps(
        _plan_spec("08:00", "18:00", 60), ensure_ascii=False), encoding="utf-8")

    loader = PrefabLoader(tmp_path, exclude=("waypoint", "plan"))
    assert loader.load_all() == []
    assert set(loader.trees) == {"启动", "其它"}

    rt = PrefabRuntime(loader)
    order = []
    rt._activate_tree = lambda name, tree: order.append(name)   # 只记顺序，不真激活
    rt.activate_all()
    assert order[0] == "启动"
    assert rt.boot_tree() is not None and rt.boot_tree().name == "启动"


def test_ensure_boot_prefab_creates_file(tmp_path):
    from app.routers.prefab import _ensure_boot_prefab

    target = tmp_path / "启动.prefab.json"
    assert _ensure_boot_prefab(target) is True
    spec = json.loads(target.read_text(encoding="utf-8"))
    assert spec["root"]["type"] == "Sequence"
    assert spec["root"]["children"] == []
    # 已存在时不覆盖（运维配好的内容不能被启动流程冲掉）
    target.write_text(json.dumps({"name": "自定义", "root": {"type": "Parallel"}},
                                 ensure_ascii=False), encoding="utf-8")
    assert _ensure_boot_prefab(target) is False
    assert json.loads(target.read_text(encoding="utf-8"))["name"] == "自定义"
