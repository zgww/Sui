"""`POST /api/plan-prefab/execute` —— 编排页的「立即执行」接口。

这条链路末端是 `Robot.接收巡检任务`，**机器人会真的出发**，所以这里锁的重点不是
"能不能跑"，而是几件"跑错了也不会报错、只会让机器人去错地方"的事：

- 执行的是**磁盘上的文件**：前端内存态一律不吃（前端可能没保存）；
- 路径不能出计划目录（`../../` 之类一律 400），且必须落在 `*.prefab.json` 上；
- 只认 `InspectionPlanNode`：对着分组 / 航点指定 / 根点「立即执行」要 422 说清楚；
- **不写账本**：手动执行不该占掉定时触发的槽位（否则"刚手动跑过，到点反而
  不跑了"）；
- **不做"忙不忙"的前置检查**：机器人忙就是 `accepted=false, reason=busy` 的
  业务结果（HTTP 200），不是 4xx —— 用 4xx 的话前端拦截器会先弹一个通用提示，
  把后端给的具体原因盖掉。

接口层用最小 app + `dependency_overrides` 绕过鉴权（见 `test_inspection_log.py`
的同一套路）；下发回调用假的（不碰真机器人、不碰状态机）。
"""
import json
from pathlib import Path

import pytest


# ---------------------------------------------------------------- 造数据

def plan(name="日常", plan_id="P-1", children=(), enabled=True, **extra):
    props = {"name": name, "plan_id": plan_id, "enabled": enabled, **extra}
    return {"type": "InspectionPlanNode", "properties": props,
            "children": list(children)}


def sched(start="08:00", end="18:00", interval=60):
    return {"type": "DailyScheduleNode",
            "properties": {"name": "调度", "enabled": True, "start_time": start,
                           "end_time": end, "interval_minutes": interval}}


def wp_source(source="wp.prefab.json", wp_ids=("W-1",)):
    return {"type": "WaypointSelectNode",
            "properties": {"name": "航点指定", "enabled": True, "source": source,
                           "include_all": False, "waypoint_ids": list(wp_ids)}}


def group(children, name="分组"):
    return {"type": "PlanGroupNode",
            "properties": {"name": name, "enabled": True},
            "children": list(children)}


def write_json(path: Path, root: dict, name="t") -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps({"name": name, "description": "", "root": root},
                               ensure_ascii=False), encoding="utf-8")
    return path


# ---------------------------------------------------------------- 夹具

@pytest.fixture
def plan_dir(tmp_path, monkeypatch):
    """把 `PLAN_PREFAB_DIR` 指到 tmp_path 下的目录（别碰真实 data/prefabs/plan）。"""
    from app import config as cfg
    from app.routers import plan_prefab
    d = tmp_path / "plan"
    d.mkdir()
    monkeypatch.setattr(cfg, "PLAN_PREFAB_DIR", d)
    monkeypatch.setattr(plan_prefab, "PLAN_PREFAB_DIR", d)
    return d


@pytest.fixture
def wp_dir(tmp_path, monkeypatch):
    """航点树目录（`build_from_plan` 的 `source` 从这里读）。"""
    d = tmp_path / "waypoint"
    d.mkdir()
    return d


class FakeRobot:
    """只实现 `dispatch_inspection` 用到的那几个属性。"""

    def __init__(self, name="机器人1", robot_id="R-1", busy=False):
        self.name = name
        self.robot_id = robot_id
        self.巡检进行中 = busy
        self.received = []

    def 接收巡检任务(self, payload):
        self.received.append(payload)
        return {"accepted": True, "inspection_id": payload[0]["id"]}


@pytest.fixture
def fake_dispatch(monkeypatch, wp_dir):
    """把 `dispatch_inspection` 换成假的：记下收到的载荷并回"接受"。

    ⚠️ 为什么不用真 `dispatch_inspection`：它会去 `get_robot()` 拿全局实例，
    在测试环境没有机器人 -> `accepted=False`，于是"接口把载荷组装对了吗"这件事
    根本测不到。这里要验的是**接口把 job 抽对、把路径校验做对、把结果透传对**，
    真下发的内部逻辑由 `test_inspection_build.py` 那一节负责。

    ⚠️ 包装时**先把原函数存下来**：`monkeypatch.setattr` 改的是模块属性，
    在替身里再调 `ps.dispatch_inspection(...)` 会调到自己 -> 无限递归
    （表现为 `RecursionError: maximum recursion depth exceeded`）。
    """
    from app.prefab import plan_scheduler as ps
    monkeypatch.setattr(ps, "WAYPOINT_PREFAB_DIR", wp_dir, raising=False)
    calls = []
    robot = FakeRobot()
    real_dispatch = ps.dispatch_inspection      # ← 必须在 setattr 之前抓

    def fake(payload, **kw):
        calls.append(payload)
        return real_dispatch(payload, robot=robot, root_dir=wp_dir)

    monkeypatch.setattr(ps, "dispatch_inspection", fake)
    return {"calls": calls, "robot": robot, "waypoint_dir": wp_dir,
            "real": real_dispatch}


@pytest.fixture
def client(plan_dir, fake_dispatch):
    """最小 app + 绕过鉴权。

    ⚠️ `execute_plan_now` 是**在函数体里**延迟 import `dispatch_inspection` 的
    （避免启动期循环导入）。`monkeypatch.setattr(ps, "dispatch_inspection", ...)`
    改的是模块属性，延迟 import 拿到的就是改过的那个，所以替换能生效。

    ⚠️ 鉴权覆盖要返回**真的 `User`**，不能图省事丢个 dict：`engineer_only` 是
    `require_role("engineer")` 包出来的，它读的是 `user.role` 属性，dict 会
    `AttributeError: 'dict' object has no attribute 'role'`（所有用例一起 500）。
    """
    from fastapi import FastAPI
    from fastapi.testclient import TestClient
    from app.auth import get_current_user
    from app.models import User
    from app.routers import plan_prefab

    app = FastAPI()
    app.include_router(plan_prefab.router)
    # 未入库的 User 实例：只用来过角色判定，不落库
    app.dependency_overrides[get_current_user] = lambda: User(
        id=1, username="tester", role="engineer", enabled=True)
    return TestClient(app)


def waypoint_tree(fake_dispatch, name="wp.prefab.json", wp_ids=("W-1",)):
    """写一棵最小航点树（1 个航点 1 个动作）。"""
    d = fake_dispatch["waypoint_dir"]
    root = {"type": "GroupNode", "properties": {"name": "g", "enabled": True},
            "children": [
                {"type": "WaypointNode",
                 "properties": {"name": "w", "wp_id": wid, "floor": 1, "index": 0,
                                "x": 1.0, "y": 0.0, "z": 1.5, "theta": 90.0,
                                "enabled": True},
                 "children": [
                     {"type": "ActionPointNode",
                      "properties": {"name": "a", "action_id": "A-1",
                                     "action_type": 1, "steer_point_name": "AO-RC-057",
                                     "lift_height": 1.2, "duration_ms": 3000,
                                     "pan": 10.0, "tilt": 20.0, "zoom": 2.0,
                                     "focal_len": 520, "focus": 100},
                      "children": []}]}
                for wid in wp_ids]}
    return write_json(d / name, root, name=name)


# ---------------------------------------------------------------- 正常路径

def test_execute_writes_disk_spec_and_dispatches(client, plan_dir, fake_dispatch):
    """happy path：抽计划 -> 组装 -> 交给机器人；载荷按楼层分段、带 detectType。"""
    waypoint_tree(fake_dispatch)
    write_json(plan_dir / "a.prefab.json",
               group([plan("日常", "P-1", [wp_source(), sched()])]))

    r = client.post("/api/plan-prefab/execute",
                    json={"rel_path": "a.prefab.json", "node_path": "root/children/0"})
    assert r.status_code == 200, r.text
    body = r.json()
    assert body["accepted"] is True
    assert body["rel_path"] == "a.prefab.json"
    assert body["node_path"] == "root/children/0"
    assert body["inspection_id"]
    assert body["floors"] == [1]
    assert body["waypoint_count"] == 1 and body["action_count"] == 1

    assert len(fake_dispatch["calls"]) == 1
    # `calls` 记的是 **job payload**（接口这一层的入参）……
    job_payload = fake_dispatch["calls"][0]
    assert job_payload["plan_id"] == "P-1"
    assert job_payload["waypoints"][0]["source"] == "wp.prefab.json"
    # ……而交给机器人的是**组装好的巡检载荷**（楼层分段数组，
    # 同 tests/test_inspection.json 的形状）
    assert len(fake_dispatch["robot"].received) == 1
    payload = fake_dispatch["robot"].received[0]
    assert isinstance(payload, list) and len(payload) == 1
    seg = payload[0]
    assert seg["floor"] == 1
    assert seg["detectType"] == "fms"           # 计划没写 -> 默认 fms
    assert [w["id"] for w in seg["waypoint"]] == ["W-1"]


def test_execute_payload_carries_trigger_manual(client, plan_dir, fake_dispatch,
                                                monkeypatch):
    """`trigger=manual` 与 `schedule=None` 标在 **job payload** 上。

    ⚠️ 两种载荷别搞混：
    - **job payload**（`PlanJob.payload()`）—— 一条计划的元信息 + 航点/测点指定，
      接口在这里补 `trigger=manual`，好让日志/记录分得清"手动点的"和"到点自动的"；
    - **巡检载荷**（`build_from_plan` 产出的楼层分段数组）—— 交给机器人那份，
      它是从 job payload 里**抽出来的**，`trigger` 这类额外键不会传过去。

    所以这里换一个"只看 job payload、不做组装"的替身，专测这一层。
    """
    from app.prefab import plan_scheduler as ps
    from app.routers.plan_prefab import ExecuteIn, execute_plan_now

    waypoint_tree(fake_dispatch)
    write_json(plan_dir / "a.prefab.json", group([plan("日常", "P-1", [wp_source()])]))

    seen = {}

    def spy(job_payload, **kw):
        seen.update(job_payload)
        return {"accepted": True, "inspection_id": "INSP-SPY"}

    monkeypatch.setattr(ps, "dispatch_inspection", spy)
    out = execute_plan_now(ExecuteIn(rel_path="a.prefab.json",
                                     node_path="root/children/0"))
    assert out["accepted"] is True
    assert seen["trigger"] == "manual"
    assert seen["plan_id"] == "P-1"
    assert seen["detect_type"] == "fms"
    assert seen["schedule"] is None            # 这条计划没配「每日调度」
    assert seen["waypoints"][0]["source"] == "wp.prefab.json"


def test_payload_schedule_none_when_draft():
    """没有调度时 `schedule` 出 **None**，不是空壳 `{"start": ""...}`。"""
    from app.prefab.plan_scheduler import PlanJob
    from datetime import datetime
    job = PlanJob(key="k", file="f", plan_name="草稿", plan_id="P-1",
                  robot_name="", priority=0)
    p = job.payload(datetime(2026, 9, 23, 10, 0), None)
    assert p["schedule"] is None
    assert json.loads(json.dumps(p))["schedule"] is None     # 可 JSON 化


def test_execute_reads_disk_not_memory(client, plan_dir, fake_dispatch):
    """**只读磁盘**：请求里没有、也不该有树内容 —— 前端没保存的改动不生效。"""
    waypoint_tree(fake_dispatch)
    write_json(plan_dir / "a.prefab.json",
               group([plan("磁盘上的名字", "P-1", [wp_source()])]))

    # 就算前端把自己那份"改了名的"树塞进 body，也不该被采信（模型里没这个字段）
    r = client.post("/api/plan-prefab/execute", json={
        "rel_path": "a.prefab.json", "node_path": "root/children/0",
        "spec": {"root": group([plan("内存态的名字", "P-9", [wp_source()])])},
    })
    assert r.status_code == 200, r.text
    assert r.json()["plan_name"] == "磁盘上的名字"
    assert r.json()["plan_key"].endswith("#P-1")


def test_execute_does_not_require_schedule(client, plan_dir, fake_dispatch):
    """草稿（只配了航点、没配时段）也能立即执行 —— 这是手动与定时的唯一差别。"""
    waypoint_tree(fake_dispatch)
    write_json(plan_dir / "draft.prefab.json",
               group([plan("草稿", "P-1", [wp_source()])]))
    r = client.post("/api/plan-prefab/execute",
                    json={"rel_path": "draft.prefab.json", "node_path": "root/children/0"})
    assert r.status_code == 200, r.text
    assert r.json()["accepted"] is True


def test_execute_nested_plan(client, plan_dir, fake_dispatch):
    """计划可以套在分组里，路径要能一层层走下去。"""
    waypoint_tree(fake_dispatch)
    write_json(plan_dir / "n.prefab.json",
               group([group([plan("深", "P-9", [wp_source()])], name="内层")]))
    r = client.post("/api/plan-prefab/execute", json={
        "rel_path": "n.prefab.json", "node_path": "root/children/0/children/0"})
    assert r.status_code == 200, r.text
    assert r.json()["plan_key"].endswith("#P-9")


def test_execute_subdir(client, plan_dir, fake_dispatch):
    """计划文件在子目录里（新建文件允许 `daily/日常`）。"""
    waypoint_tree(fake_dispatch)
    write_json(plan_dir / "daily" / "a.prefab.json",
               group([plan("日常", "P-1", [wp_source()])]))
    r = client.post("/api/plan-prefab/execute", json={
        "rel_path": "daily/a.prefab.json", "node_path": "root/children/0"})
    assert r.status_code == 200, r.text
    assert r.json()["rel_path"] == "daily/a.prefab.json"


# ---------------------------------------------------------------- 拒绝

def test_execute_rejects_non_plan_node(client, plan_dir, fake_dispatch):
    """对着分组 / 根 / 计划下面的子节点点执行 -> 422 且说明"只能执行巡检计划"。"""
    waypoint_tree(fake_dispatch)
    write_json(plan_dir / "a.prefab.json",
               group([group([plan("里", "P-1", [wp_source()])])]))
    for node_path in ("root", "root/children/0", "root/children/0/children/0/children/0"):
        r = client.post("/api/plan-prefab/execute",
                        json={"rel_path": "a.prefab.json", "node_path": node_path})
        assert r.status_code == 422, f"{node_path} -> {r.status_code}"
        assert "只能立即执行" in r.json()["detail"]


def test_execute_rejects_bad_node_path(client, plan_dir, fake_dispatch):
    waypoint_tree(fake_dispatch)
    write_json(plan_dir / "a.prefab.json", group([plan("日常", "P-1", [wp_source()])]))
    for node_path in ("root/children/9", "root/children/x", "root/0", "children/0"):
        r = client.post("/api/plan-prefab/execute",
                        json={"rel_path": "a.prefab.json", "node_path": node_path})
        assert r.status_code == 422
        assert "路径不存在" in r.json()["detail"]


def test_execute_rejects_disabled_plan(client, plan_dir, fake_dispatch):
    """停用 = 不参与运行，手动执行也不例外（否则"停用了手点还能跑"会被当成正常）。"""
    waypoint_tree(fake_dispatch)
    write_json(plan_dir / "a.prefab.json",
               group([plan("停用", "P-1", [wp_source()], enabled=False)]))
    r = client.post("/api/plan-prefab/execute",
                    json={"rel_path": "a.prefab.json", "node_path": "root/children/0"})
    assert r.status_code == 422
    assert "停用" in r.json()["detail"]


def test_execute_rejects_disabled_child(client, plan_dir, fake_dispatch):
    """计划本身启用，但「航点指定」被停用 -> 挑不到航点，如实说"没挑到航点"。"""
    waypoint_tree(fake_dispatch)
    sel = wp_source()
    sel["properties"]["enabled"] = False
    write_json(plan_dir / "a.prefab.json", group([plan("日常", "P-1", [sel])]))
    r = client.post("/api/plan-prefab/execute",
                    json={"rel_path": "a.prefab.json", "node_path": "root/children/0"})
    assert r.status_code == 200
    assert r.json()["accepted"] is False
    assert "航点" in r.json()["reason"]


def test_execute_missing_file(client, plan_dir, fake_dispatch):
    r = client.post("/api/plan-prefab/execute",
                    json={"rel_path": "nope.prefab.json", "node_path": "root/children/0"})
    assert r.status_code == 404


def test_execute_requires_prefab_json_suffix(client, plan_dir, fake_dispatch):
    (plan_dir / "a.json").write_text("{}", encoding="utf-8")
    r = client.post("/api/plan-prefab/execute",
                    json={"rel_path": "a.json", "node_path": "root/children/0"})
    assert r.status_code == 422
    assert ".prefab.json" in r.json()["detail"]


def test_execute_rejects_path_traversal(client, plan_dir, fake_dispatch):
    """目录穿越一律挡掉 —— 这个接口会读盘，不能让它读到计划目录以外。"""
    secret = plan_dir.parent / "secret.prefab.json"
    write_json(secret, group([plan("偷来的", "P-X", [wp_source()])]))
    for rel in ("../secret.prefab.json", "..\\secret.prefab.json",
                "a/../../secret.prefab.json", "/etc/passwd.prefab.json"):
        r = client.post("/api/plan-prefab/execute",
                        json={"rel_path": rel, "node_path": "root/children/0"})
        # 关键是**别被执行**：要么 400/422 直接拒，要么 404 说文件不在这里
        assert r.status_code in (400, 404, 422), f"{rel} -> {r.status_code} {r.text}"
    # 穿越进来的那份文件从头到尾没被碰过
    assert fake_dispatch["robot"].received == []


def test_execute_broken_json(client, plan_dir, fake_dispatch):
    (plan_dir / "bad.prefab.json").write_text("{不是 json", encoding="utf-8")
    r = client.post("/api/plan-prefab/execute",
                    json={"rel_path": "bad.prefab.json", "node_path": "root/children/0"})
    assert r.status_code == 422
    assert "读取计划文件失败" in r.json()["detail"]


def test_execute_empty_body(client, plan_dir, fake_dispatch):
    """`rel_path` / `node_path` 都必填且非空（pydantic 层拦）。"""
    for body in ({}, {"rel_path": "a.prefab.json"}, {"node_path": "root"},
                 {"rel_path": "", "node_path": "root"}):
        r = client.post("/api/plan-prefab/execute", json=body)
        assert r.status_code == 422, f"{body} -> {r.status_code}"


# ---------------------------------------------------------------- 业务拒绝透传

def test_execute_busy_is_200_not_4xx(client, plan_dir, fake_dispatch):
    """机器人忙 = 业务结果（200 + accepted=false + reason=busy），不是 HTTP 错误。

    用 4xx 的话前端拦截器会先弹一个通用 Toast，把"机器人正在巡检"这个**有用的**
    原因盖掉；而且忙不是"你请求发错了"，重试就能成。
    """
    waypoint_tree(fake_dispatch)
    fake_dispatch["robot"].巡检进行中 = True
    write_json(plan_dir / "a.prefab.json", group([plan("日常", "P-1", [wp_source()])]))

    r = client.post("/api/plan-prefab/execute",
                    json={"rel_path": "a.prefab.json", "node_path": "root/children/0"})
    assert r.status_code == 200, r.text
    body = r.json()
    assert body["accepted"] is False and body["reason"] == "busy"
    # 忙的时候连组装都不该做（读盘建树白干）—— 载荷没交给机器人
    assert fake_dispatch["robot"].received == []


def test_execute_no_waypoint_tree(client, plan_dir, fake_dispatch):
    """计划指向的航点树不在盘上 -> accepted=false 且原因说得出来（不 500）。"""
    write_json(plan_dir / "a.prefab.json",
               group([plan("日常", "P-1", [wp_source(source="不存在.prefab.json")])]))
    r = client.post("/api/plan-prefab/execute",
                    json={"rel_path": "a.prefab.json", "node_path": "root/children/0"})
    assert r.status_code == 200, r.text
    body = r.json()
    assert body["accepted"] is False
    assert "组装巡检任务失败" in body["reason"]


def test_execute_leaves_no_ledger(client, plan_dir, fake_dispatch):
    """**不写账本**：手动执行不该占掉定时触发的槽位。

    账本（`plan_scheduler_state.json`）是给定时触发去重用的。如果手动执行也
    mark 一下，就会出现"我刚手动跑过，到点反而不跑了"。

    这条只看一件事：跑完接口后计划目录里**没有多出账本文件**（也不该动已有的）。
    """
    waypoint_tree(fake_dispatch)
    write_json(plan_dir / "a.prefab.json", group([plan("日常", "P-1", [wp_source()])]))
    before = sorted(p.name for p in plan_dir.rglob("*"))
    r = client.post("/api/plan-prefab/execute",
                    json={"rel_path": "a.prefab.json", "node_path": "root/children/0"})
    assert r.status_code == 200, r.text
    after = sorted(p.name for p in plan_dir.rglob("*"))
    assert before == after, f"计划目录被动了: {set(after) - set(before)}"
    assert not (plan_dir / "plan_scheduler_state.json").exists()


# ---------------------------------------------------------------- 路由注册

def test_route_is_registered():
    """路由真的挂上去了（prefix / 方法 / 鉴权依赖）。"""
    from app.auth import engineer_only
    from app.routers.plan_prefab import router

    hit = [r for r in router.routes if getattr(r, "path", "") == "/api/plan-prefab/execute"]
    assert len(hit) == 1, [getattr(r, "path", None) for r in router.routes]
    route = hit[0]
    assert "POST" in route.methods
    # engineer_only 是"会动真格设备"的接口该有的门槛
    deps = [d.call for d in route.dependant.dependencies]
    assert getattr(engineer_only, "__name__", "") in [getattr(d, "__name__", "") for d in deps] \
        or any(d is engineer_only for d in deps), deps
