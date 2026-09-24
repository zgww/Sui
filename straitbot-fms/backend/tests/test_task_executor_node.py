"""任务执行器**节点**的冒烟测试：起线程 -> 分流 -> 回写库 -> 停线程。

纯逻辑（分流决策、载荷形状、响应归一化）在 `test_task_executor.py`；这里只测三件
"接错了就整个功能等于没有"的事：

1. 节点注册了（否则 启动.prefab.json 里配上去是未知节点类型）；
2. `on_active` 真的起了线程、真的按 `detect_type` 分流（platform 发 HTTP、
   fms 走推理+流程），`on_deactive` 真的把线程停掉；
3. 回写幂等：成功置 done 后下一轮扫不到；失败留 failed 并能重试；
   跳过不是失败（置 done + 记原因）。

HTTP 用假传输（monkeypatch `httpx.post`），库用**临时 SQLite**（不碰 data/fms.db）；
检测流程目录与航点树目录都指向 tmp_path，测试不依赖现场数据。
"""
import json
import threading
import time
from pathlib import Path

import pytest
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from app.database import Base
from app.models import InspectionActionResult, InspectionPointResult
from app.prefab import registry
from app.prefab.base import Context
from app.prefab.task_executor import DISPATCH_DONE, DISPATCH_PENDING

TASK_ID = "e" * 32


# ---------------------------------------------------------------- 环境搭建

def make_session_factory(tmp_path):
    engine = create_engine(f"sqlite:///{tmp_path / 'exec.db'}",
                           connect_args={"check_same_thread": False})
    Base.metadata.create_all(engine)
    return sessionmaker(bind=engine)


def make_action_row(Session, **kw):
    """插一条 `status='ok'` 且待分发的动作行，返回 id。"""
    db = Session()
    row = InspectionActionResult(
        inspection_id=TASK_ID, floor=1, waypoint_id="w1", action_id="a1",
        action_seq=0, action_type=kw.pop("action_type", 1),
        detect_type=kw.pop("detect_type", "platform"),
        status="ok", picture=kw.pop("picture", "p.jpg"),
        infrared=kw.pop("infrared", ""), local_path="",
        inplace_ts="2026-09-22T10:00:00",
        dispatch_status=kw.pop("dispatch_status", "pending"),
        dispatch_attempts=kw.pop("dispatch_attempts", 0),
        **kw,
    )
    db.add(row)
    db.commit()
    rid = row.id
    db.close()
    return rid


def point_row(Session, action_result_id):
    db = Session()
    row = InspectionPointResult(
        action_result_id=action_result_id, inspection_id=TASK_ID,
        floor=1, waypoint_id="w1", action_id="a1", point_id="PT-1", seq=0,
        status="pending",
    )
    db.add(row)
    db.commit()
    pid = row.id
    db.close()
    return pid


def write_waypoint_tree(tmp_path, *, detect_flow="FLOW-1", action_id="a1",
                        wp_id="w1", with_box=True, point_id="PT-1"):
    """写一棵最小航点树：航点 -> 动作点 -> 检测框。"""
    p = tmp_path / "waypoint" / "floor1"
    p.mkdir(parents=True, exist_ok=True)
    box = {
        "type": "DetectBoxNode",
        "properties": {"name": "框1", "enabled": True, "shape": "rect",
                       "points": [{"x": 0.1, "y": 0.2}, {"x": 0.4, "y": 0.2},
                                  {"x": 0.4, "y": 0.5}, {"x": 0.1, "y": 0.5}],
                       "detect_flow": detect_flow, "point_id": point_id,
                       "point_name": "测点1"},
        "children": [],
    }
    action = {
        "type": "ActionPointNode",
        "properties": {"name": "动作", "enabled": True, "action_id": action_id,
                       "action_type": 1},
        "children": [box] if with_box else [],
    }
    spec = {
        "name": "测试航线", "description": "",
        "root": {"type": "GroupNode",
                 "properties": {"name": "任务", "enabled": True},
                 "children": [{"type": "WaypointNode",
                               "properties": {"name": "航点1", "enabled": True,
                                              "wp_id": wp_id, "floor": 1, "x": 1.0},
                               "children": [action]}]},
    }
    (p / "测试航线.prefab.json").write_text(
        json.dumps(spec, ensure_ascii=False), encoding="utf-8")


def write_detect_flow(tmp_path, *, detect_id="FLOW-1", with_detector=True,
                      alarm=True):
    """写一条最小检测流程：算法节点（人员入侵） + 可选告警节点。"""
    children = []
    if with_detector:
        children.append({
            "type": "PersonIntrusionNode",
            "properties": {"name": "人员入侵", "enabled": True,
                           "algorithm": "person_intrusion",
                           "threshold": 0.5, "labels": [], "max_results": 0,
                           "params": {}, "note": "", "min_box_ratio": 0},
            "children": [],
        })
    if alarm:
        children.append({
            "type": "AlarmNode",
            "properties": {"name": "告警", "enabled": True, "level": "一般告警",
                           "template": "", "title": "有人", "content": "",
                           "dedup_seconds": 0, "note": ""},
            "children": [],
        })
    d = tmp_path / "检测算法"
    d.mkdir(parents=True, exist_ok=True)
    spec = {
        "name": "人员入侵", "description": "",
        "root": {"type": "DetectPipelineNode",
                 "properties": {"name": "流程", "enabled": True,
                                "detect_id": detect_id, "scene": ""},
                 "children": children},
    }
    (d / "人员入侵.prefab.json").write_text(
        json.dumps(spec, ensure_ascii=False), encoding="utf-8")


class FakeHttp:
    """假 httpx：记录全部 POST，按脚本返回。"""

    def __init__(self, *, infer_body=None, upload_status=200, infer_status=200,
                 fail_times=0):
        self.calls = []
        self.infer_body = infer_body if infer_body is not None else {
            "detections": [{"label": "person", "score": 0.9, "x": 0.2, "y": 0.3,
                            "w": 0.1, "h": 0.1}]}
        self.upload_status = upload_status
        self.infer_status = infer_status
        self.fail_times = fail_times      # 前 N 次 POST 直接抛（模拟网络故障）

    def __call__(self, url, *, json=None, headers=None, timeout=None, verify=None):
        self.calls.append({"url": url, "json": json, "headers": headers,
                           "timeout": timeout})
        if self.fail_times > 0:
            self.fail_times -= 1
            raise RuntimeError("connection refused")

        class Resp:
            def __init__(self, status, body):
                self.status_code = status
                self._body = body

            @property
            def text(self):
                # ⚠️ 这里**不能**写 `json.dumps`：假 resp 的 `json()` 方法在类作用域里
                # 把模块级 `json` 遮蔽成了方法对象，`json.dumps` 会变成
                # "dict has no attribute dumps"——一个只在这里才暴露的坑。
                import json as _json
                return _json.dumps(self._body, ensure_ascii=False)

            def json(self):
                return self._body

        if "infer" in url:
            return Resp(self.infer_status, self.infer_body)
        return Resp(self.upload_status, {"ok": True})


def make_node(**kw):
    props = {"name": "执行器", "poll_interval": 0.5, "batch_size": 50}
    props.update(kw)
    return registry.build({"type": "TaskExecutorNode", "properties": props})


def wait_until(pred, timeout=8.0, interval=0.05):
    end = time.time() + timeout
    while time.time() < end:
        if pred():
            return True
        time.sleep(interval)
    return False


@pytest.fixture
def env(tmp_path, monkeypatch):
    """把库、航点树目录、检测流程目录、平台配置都搬到 tmp_path。"""
    import app.database as database
    import app.config as config

    Session = make_session_factory(tmp_path)
    monkeypatch.setattr(database, "SessionLocal", Session)
    monkeypatch.setattr(config, "WAYPOINT_PREFAB_DIR", tmp_path / "waypoint")
    monkeypatch.setattr(config, "DETECT_PREFAB_DIR", tmp_path / "检测算法")
    monkeypatch.setattr(config, "PREFAB_DIR", tmp_path / "prefabs")
    write_waypoint_tree(tmp_path)
    write_detect_flow(tmp_path)
    return {"Session": Session, "tmp": tmp_path}


def platform_ctx(**kw):
    """造一个带平台配置的 Context（等价于 PlatformConfig 节点已 on_active）。"""
    ctx = Context()
    ctx.kv["platform.upload_url"] = kw.get("upload_url", "http://plat/api/inspection/report/result")
    ctx.kv["platform.infer_url"] = kw.get("infer_url", "http://infer/infer")
    ctx.kv["platform.auth_header"] = kw.get("auth_header", "")
    ctx.kv["platform.timeout"] = str(kw.get("timeout", 2.0))
    ctx.kv["platform.retry"] = str(kw.get("retry", 0))
    ctx.kv["platform.verify_tls"] = "True"
    return ctx


# ---------------------------------------------------------------- 注册

def test_node_registered_and_defaults():
    assert "TaskExecutorNode" in registry.registered_types()
    schema = registry.node_schema("TaskExecutorNode")
    # dry_run 默认**关**（与计划调度节点相反）：这节点是数据出口，
    # 默认开着等于"配上去什么都不干"，现场会以为功能坏了
    assert schema["properties"]["dry_run"]["default"] is False
    assert schema["properties"]["poll_interval"]["default"] == 5
    assert schema["properties"]["max_attempts"]["default"] == 5


def test_platform_config_registered():
    assert "PlatformConfig" in registry.registered_types()
    schema = registry.node_schema("PlatformConfig")
    assert "infer_url" in schema["properties"]


def test_platform_node_writes_context():
    node = registry.build({"type": "PlatformConfig",
                           "properties": {"upload_url": "http://p/x",
                                          "infer_url": "http://i/y",
                                          "auth_header": "A: 1"}})
    ctx = Context()
    node.activate(ctx)
    assert ctx.kv["platform.upload_url"] == "http://p/x"
    assert ctx.kv["platform.infer_url"] == "http://i/y"
    assert ctx.kv["platform.auth_header"] == "A: 1"
    assert node.configured is True and node.infer_configured is True


def test_robot_prefab_has_platform_node():
    """平台配置节点必须预置在 robot.prefab.json 里：没有它现场不知道去哪填地址。"""
    path = Path(__file__).resolve().parents[1] / "data" / "prefabs" / "robot.prefab.json"
    spec = json.loads(path.read_text(encoding="utf-8"))
    types = [c.get("type") for c in spec["root"].get("children") or []]
    assert "PlatformConfig" in types


# ---------------------------------------------------------------- 起停

def test_thread_starts_and_stops(env, monkeypatch):
    monkeypatch.setattr("httpx.post", FakeHttp())
    node = make_node()
    ctx = platform_ctx()
    node.activate(ctx)
    assert node.status()["running"] is True
    node.deactivate(ctx)
    assert node.status()["running"] is False
    # 线程确实退出了（不是只把引用清了）
    assert wait_until(lambda: not (node._thread and node._thread.is_alive()), 3)


# ---------------------------------------------------------------- platform 分支

def test_platform_branch_posts_to_upload_url(env, monkeypatch):
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, detect_type="platform")

    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: len(fake.calls) >= 1), "没有发出上报请求"
    finally:
        node.deactivate(platform_ctx())

    call = fake.calls[0]
    assert call["url"] == "http://plat/api/inspection/report/result"
    assert call["json"]["inspection_id"] == TASK_ID
    item = call["json"]["results"][0]
    assert item["waypoint_id"] == "w1" and item["picture"] == "p.jpg"
    # 内部字段不能混进上报体
    assert "detect_type" not in item and "local_path" not in item

    db = Session()
    row = db.query(InspectionActionResult).filter_by(id=rid).first()
    assert row.dispatch_status == "done"
    assert row.dispatch_mode == "upload"
    assert row.dispatched_at is not None
    db.close()


def test_done_row_is_not_reprocessed(env, monkeypatch):
    """幂等：置 done 后下一轮扫不到（同一批数据不会上报两次）。"""
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    make_action_row(Session, detect_type="platform")

    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: len(fake.calls) >= 1)
        time.sleep(1.0)          # 至少再扫两轮
    finally:
        node.deactivate(platform_ctx())
    assert len(fake.calls) == 1, f"同一行被上报了 {len(fake.calls)} 次"


def test_upload_failure_marks_failed_and_retries(env, monkeypatch):
    """上报失败 -> failed + attempts+1，**下一轮还会重试**（不能就这么丢了）。"""
    fake = FakeHttp(upload_status=500)
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, detect_type="platform")

    node = make_node(poll_interval=0.2, max_attempts=5)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: len(fake.calls) >= 2), "失败后没有重试"
    finally:
        node.deactivate(platform_ctx())

    db = Session()
    row = db.query(InspectionActionResult).filter_by(id=rid).first()
    assert row.dispatch_status == "failed"
    assert row.dispatch_attempts >= 2
    assert "500" in row.dispatch_error
    db.close()


def test_failed_row_is_picked_up_again(env, monkeypatch):
    """⚠️ 候选条件是 `dispatch_status != 'done'`，不是 `== 'pending'`。

    曾经写成只查 pending：一条上传失败的数据被标 failed 之后**永远不再被选中**，
    等于永久搁浅——现场再也看不到它去哪了。这条测试专门锁住这个坑。
    """
    fake = FakeHttp(upload_status=500)
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, detect_type="platform")

    node = make_node(poll_interval=0.2, max_attempts=3)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: len(fake.calls) >= 3, 5), \
            f"failed 的行没有被重新捞起来（只发了 {len(fake.calls)} 次）"
        # 到上限后**下一轮**才会被跳过（attempts 记到 3 那一刻还没走到超限判定），
        # 所以这里要等状态自己转过去，不能在"发出第 3 次"的瞬间就断言。
        assert wait_until(lambda: _dispatch_status(Session, rid) == "done", 5), \
            "达到重试上限后没有置 done"
    finally:
        node.deactivate(platform_ctx())
    # 置 done 之后不能再刷请求
    n = len(fake.calls)
    time.sleep(0.6)
    assert len(fake.calls) == n, "已达重试上限还在发请求"


def test_retry_limit_stops_hammering(env, monkeypatch):
    """到重试上限就跳过：置 done + 记原因，不再每轮都发一次。"""
    fake = FakeHttp(upload_status=500)
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, detect_type="platform", dispatch_attempts=5)

    node = make_node(poll_interval=0.2, max_attempts=5)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: _dispatch_status(Session, rid) == "done", 3)
        time.sleep(0.6)
    finally:
        node.deactivate(platform_ctx())
    assert fake.calls == [], "已达重试上限还在发请求"


def test_missing_upload_url_skips_without_failing(env, monkeypatch):
    """没配地址 = 跳过（不是失败）：置 done 并记原因，免得每 5 秒刷一次日志。"""
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, detect_type="platform")

    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx(upload_url=""))
    try:
        assert wait_until(lambda: _dispatch_status(Session, rid) == "done", 3)
    finally:
        node.deactivate(platform_ctx())
    assert fake.calls == []
    db = Session()
    row = db.query(InspectionActionResult).filter_by(id=rid).first()
    assert "平台上报地址" in row.dispatch_error
    db.close()


def test_video_action_is_skipped(env, monkeypatch):
    """录像动作没有图像：跳过，不要以"没有图片"失败刷 attempts。"""
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, action_type=3, detect_type="platform")

    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: _dispatch_status(Session, rid) == "done", 3)
    finally:
        node.deactivate(platform_ctx())
    assert fake.calls == []


# ---------------------------------------------------------------- fms 分支

def test_fms_branch_infers_and_writes_point_result(env, monkeypatch):
    """fms 分支：调推理服务 -> 跑流程 -> 结果写回测点（不调平台上报口）。"""
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, detect_type="fms")
    pid = point_row(Session, rid)

    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: _dispatch_status(Session, rid) == "done", 6), \
            f"fms 分支没跑完；calls={[c['url'] for c in fake.calls]}"
    finally:
        node.deactivate(platform_ctx())

    infer_calls = [c for c in fake.calls if "infer" in c["url"]]
    assert len(infer_calls) == 1, "没有调推理服务"
    body = infer_calls[0]["json"]
    assert body["algorithm"] == "person_intrusion"     # 算法取自流程树
    assert body["flow"] == "FLOW-1"
    assert body["image"] == "p.jpg"
    assert body["region"]["shape"] == "rect"
    assert len(body["region"]["points"]) == 4
    # **不能**去调平台上报口
    assert not [c for c in fake.calls if "report/result" in c["url"]]

    db = Session()
    row = db.query(InspectionActionResult).filter_by(id=rid).first()
    assert row.dispatch_status == "done" and row.dispatch_mode == "detect"

    pt = db.query(InspectionPointResult).filter_by(id=pid).first()
    assert pt.kind == "detect"
    assert pt.point_id == "PT-1"                 # 更新已有行，不是新插
    assert pt.detect_flow == "FLOW-1"
    assert pt.algorithm == "person_intrusion"
    assert pt.label == "person"
    assert pt.confidence is not None and abs(pt.confidence - 0.9) < 1e-6
    assert pt.passed is True
    assert pt.boxes_json and pt.boxes_json[0]["x"] == 0.2
    assert pt.detect_json["actions"], "告警动作应记进 detect_json 备查"
    assert db.query(InspectionPointResult).count() == 1
    db.close()


def test_fms_missing_flow_skips(env, monkeypatch):
    """检测框没引用流程 = 没活干，跳过（不是失败）。"""
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    write_waypoint_tree(env["tmp"], detect_flow="")     # 覆盖成"没配流程"
    rid = make_action_row(Session, detect_type="fms")

    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: _dispatch_status(Session, rid) == "done", 3)
    finally:
        node.deactivate(platform_ctx())
    assert fake.calls == []
    db = Session()
    assert "检测框" in db.query(InspectionActionResult).filter_by(id=rid).first().dispatch_error
    db.close()


def test_fms_flow_not_found_fails(env, monkeypatch):
    """引用了一条不存在的流程 -> failed（配置错了要让人看见，不能静默通过）。"""
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    write_waypoint_tree(env["tmp"], detect_flow="不存在的流程")
    rid = make_action_row(Session, detect_type="fms")
    point_row(Session, rid)

    node = make_node(poll_interval=0.2, max_attempts=999)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: _dispatch_status(Session, rid) == "failed", 4)
    finally:
        node.deactivate(platform_ctx())
    db = Session()
    row = db.query(InspectionActionResult).filter_by(id=rid).first()
    assert "不存在" in row.dispatch_error
    db.close()


def test_fms_missing_infer_url_skips(env, monkeypatch):
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, detect_type="fms")

    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx(infer_url=""))
    try:
        assert wait_until(lambda: _dispatch_status(Session, rid) == "done", 3)
    finally:
        node.deactivate(platform_ctx())
    assert fake.calls == []
    db = Session()
    assert "推理服务" in db.query(InspectionActionResult).filter_by(id=rid).first().dispatch_error
    db.close()


def test_fms_creates_point_row_when_placeholder_missing(env, monkeypatch):
    """没有测点占位行（老任务）时补插一行：结果算出来了，丢了比多一行更糟。"""
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, detect_type="fms")   # 不预插测点

    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: _dispatch_status(Session, rid) == "done", 6)
    finally:
        node.deactivate(platform_ctx())
    db = Session()
    pt = db.query(InspectionPointResult).filter_by(action_result_id=rid).first()
    assert pt is not None and pt.point_id == "PT-1" and pt.kind == "detect"
    db.close()


def test_detect_type_unknown_falls_back_to_platform(env, monkeypatch):
    """库里 detect_type 是个坏值 -> 走 platform（与 rail 侧同一约定）。"""
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, detect_type="robot")

    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: len(fake.calls) >= 1, 4)
    finally:
        node.deactivate(platform_ctx())
    assert "report/result" in fake.calls[0]["url"]
    db = Session()
    assert db.query(InspectionActionResult).filter_by(id=rid).first().dispatch_mode == "upload"
    db.close()


# ---------------------------------------------------------------- dry_run

def test_dry_run_does_not_send_or_write(env, monkeypatch):
    """演练：只记日志，不发 HTTP、不回写库（行保持 pending）。"""
    fake = FakeHttp()
    monkeypatch.setattr("httpx.post", fake)
    Session = env["Session"]
    rid = make_action_row(Session, detect_type="platform")

    node = make_node(poll_interval=0.2, dry_run=True)
    node.activate(platform_ctx())
    try:
        time.sleep(0.8)
    finally:
        node.deactivate(platform_ctx())
    assert fake.calls == []
    db = Session()
    row = db.query(InspectionActionResult).filter_by(id=rid).first()
    assert row.dispatch_status == "pending" and row.dispatch_attempts == 0
    db.close()


# ---------------------------------------------------------------- 健壮性

def test_scan_error_does_not_kill_thread(env, monkeypatch):
    """一次扫描抛异常不能让线程死掉（否则"上报悄无声息停了"）。"""
    node = make_node(poll_interval=0.2)
    ctx = platform_ctx()
    node.activate(ctx)
    try:
        calls = {"n": 0}
        real = node._scan_once

        def boom():
            calls["n"] += 1
            if calls["n"] == 1:
                raise RuntimeError("boom")
            real()

        node._scan_once = boom
        assert wait_until(lambda: calls["n"] >= 3, 4), "线程被异常打死了"
        assert node.status()["running"] is True
    finally:
        node.deactivate(ctx)


def test_broken_db_does_not_kill_thread(env, monkeypatch):
    """库不可用：只告警，线程继续跑（不能因为一次查询失败就停掉上报）。"""
    import app.database as database

    def broken():
        raise RuntimeError("db down")

    monkeypatch.setattr(database, "SessionLocal", broken)
    node = make_node(poll_interval=0.2)
    ctx = platform_ctx()
    node.activate(ctx)
    try:
        time.sleep(0.8)
        assert node.status()["running"] is True
    finally:
        node.deactivate(ctx)


def test_status_reports_flows_and_stats(env, monkeypatch):
    monkeypatch.setattr("httpx.post", FakeHttp())
    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx())
    try:
        assert wait_until(lambda: "FLOW-1" in node._flow_map(), 3)
        st = node.status()
        assert st["running"] is True
        assert "FLOW-1" in st["flows"]
        assert set(st["stats"]) >= {"uploaded", "detected", "skipped", "failed"}
    finally:
        node.deactivate(platform_ctx())


def test_detect_flow_cache_invalidated_on_change(env, monkeypatch):
    """流程目录变了要重新加载：改了流程却要重启才生效是最容易当成 bug 的行为。"""
    monkeypatch.setattr("httpx.post", FakeHttp())
    node = make_node(poll_interval=0.2)
    node.activate(platform_ctx())
    try:
        assert "FLOW-1" in node._flow_map()
        write_detect_flow(env["tmp"], detect_id="FLOW-2")
        import os
        p = env["tmp"] / "检测算法" / "人员入侵.prefab.json"
        os.utime(p, (time.time() + 5, time.time() + 5))
        assert "FLOW-2" in node._flow_map()
    finally:
        node.deactivate(platform_ctx())


def _dispatch_status(Session, rid):
    db = Session()
    try:
        row = db.query(InspectionActionResult).filter_by(id=rid).first()
        return row.dispatch_status if row else None
    finally:
        db.close()
