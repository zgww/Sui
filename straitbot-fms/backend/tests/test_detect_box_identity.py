"""检测框身份（`box_id`）与"没绑测点也能回写"的回归。

## 为什么单独一个文件

`point_id` 在本站场景里**不是必须的**（检测框常常不绑测点）。一旦它为空：

- 下发给算法服务的报文里只剩一个空的 `pointId`，结果回来**认不回是哪个框**；
- 回调回写时（老代码 `if not point_id: return None`）整条结果被静默丢掉 ——
  表现是"算法明明识别出来了，巡检详情里什么都没有"，比多插一行难查得多。

所以 `box_id` / `box_name` 必须**一路带到底**：
    编排（`DetectBoxNode.box_id`）-> 巡检任务（`to_inspection_json`）
    -> 提交报文（`_infer_async` 的 `box_id`/`box_name`）
    -> 回调留痕（`box_flow`）-> 回写测点（`_upsert_point` 按 box_id 定位）

本文件把这条链上的每一跳都锁住。用临时 SQLite + tmp_path 下的航点树/流程目录，
不碰现场数据。
"""
import json

import pytest
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from app.database import Base
from app.models import Alarm, InspectionActionResult, InspectionPointResult
from app.prefab import registry
from app.prefab.task_executor import PendingAction

TASK_ID = "f" * 32


# ---------------------------------------------------------------- 环境

def make_session_factory(tmp_path):
    engine = create_engine(f"sqlite:///{tmp_path / 'box.db'}",
                           connect_args={"check_same_thread": False})
    Base.metadata.create_all(engine)
    return sessionmaker(bind=engine)


def write_waypoint_tree(tmp_path, boxes):
    """写一棵最小航点树：航点 -> 动作点 -> 若干检测框（`boxes` 是 properties 列表）。"""
    p = tmp_path / "waypoint" / "floor1"
    p.mkdir(parents=True, exist_ok=True)
    spec = {
        "name": "测试航线", "description": "",
        "root": {"type": "GroupNode",
                 "properties": {"name": "任务", "enabled": True},
                 "children": [{"type": "WaypointNode",
                               "properties": {"name": "航点1", "enabled": True,
                                              "wp_id": "w1", "floor": 1, "x": 1.0},
                               "children": [{
                                   "type": "ActionPointNode",
                                   "properties": {"name": "动作", "enabled": True,
                                                  "action_id": "a1", "action_type": 1},
                                   "children": [{"type": "DetectBoxNode",
                                                 "properties": b, "children": []}
                                                for b in boxes],
                               }]}]},
    }
    (p / "测试航线.prefab.json").write_text(
        json.dumps(spec, ensure_ascii=False), encoding="utf-8")


def write_detect_flow(tmp_path, *, detect_id="FLOW-1", dedup_seconds=0):
    """写一条最小检测流程：人员入侵算法 + 告警节点。"""
    d = tmp_path / "检测算法"
    d.mkdir(parents=True, exist_ok=True)
    spec = {
        "name": "人员入侵", "description": "",
        "root": {"type": "DetectPipelineNode",
                 "properties": {"name": "流程", "enabled": True,
                                "detect_id": detect_id, "scene": ""},
                 "children": [{
                     "type": "PersonIntrusionNode",
                     "properties": {"name": "人员入侵", "enabled": True,
                                    "algorithm": "person_intrusion", "threshold": 0.5,
                                    "labels": [], "max_results": 0, "params": {},
                                    "note": "", "min_box_ratio": 0},
                     "children": [],
                 }, {
                     "type": "AlarmNode",
                     "properties": {"name": "告警", "enabled": True, "level": "一般告警",
                                    "template": "", "title": "有人", "content": "",
                                    "dedup_seconds": dedup_seconds, "note": ""},
                     "children": [],
                 }]},
    }
    (d / "人员入侵.prefab.json").write_text(
        json.dumps(spec, ensure_ascii=False), encoding="utf-8")


@pytest.fixture
def env(tmp_path, monkeypatch):
    """航点树目录、流程目录搬到 tmp_path；返回 Session 工厂与 tmp 根。"""
    import app.config as config

    Session = make_session_factory(tmp_path)
    monkeypatch.setattr(config, "WAYPOINT_PREFAB_DIR", tmp_path / "waypoint")
    monkeypatch.setattr(config, "DETECT_PREFAB_DIR", tmp_path / "检测算法")
    return {"Session": Session, "tmp": tmp_path}


def make_node():
    return registry.build({"type": "TaskExecutorNode",
                           "properties": {"name": "执行器"}})


def rect_box(**props):
    base = {"name": "框", "enabled": True, "shape": "rect",
            "points": [{"x": 0.1, "y": 0.2}, {"x": 0.4, "y": 0.2},
                       {"x": 0.4, "y": 0.5}, {"x": 0.1, "y": 0.5}],
            "detect_flow": "FLOW-1"}
    base.update(props)
    return base


def pending_action(**kw):
    kw.setdefault("action_result_id", 1)
    kw.setdefault("inspection_id", TASK_ID)
    kw.setdefault("floor", 1)
    kw.setdefault("waypoint_id", "w1")
    kw.setdefault("action_id", "a1")
    kw.setdefault("action_type", 1)
    kw.setdefault("detect_type", "fms")
    return PendingAction(**kw)


# ---------------------------------------------------------------- 1. 节点身份

def test_detect_box_node_uses_its_own_id():
    """`id` 是**框自己的** box_id，不再拿 point_id 顶替。"""
    from app.prefab.nodes.waypoint import DetectBoxNode

    n = DetectBoxNode(name="3号柜电流表", box_id="B1", point_id="PT-1",
                      detect_flow="FLOW-1",
                      points=[{"x": 0.1, "y": 0.2}, {"x": 0.4, "y": 0.5}])
    j = n.to_inspection_json()
    assert j["id"] == "B1" and j["box_id"] == "B1"
    assert j["box_name"] == "3号柜电流表"
    assert j["point_id"] == "PT-1"
    # fresh_id（复制粘贴）要换一个，否则两个框抢同一份结果
    assert n.to_inspection_json(fresh_id=True)["id"] != "B1"


def test_detect_box_node_without_point_id_still_has_id():
    """没绑测点的框也必须有身份 —— 老写法 `point_id or 现摇 hex` 每次 build 都变。"""
    from app.prefab.nodes.waypoint import DetectBoxNode

    n = DetectBoxNode(name="框2")
    j = n.to_inspection_json()
    assert j["point_id"] == ""
    assert j["box_id"] == j["id"] and len(j["id"]) == 32


# ---------------------------------------------------------------- 2. 目标清单

def test_detect_targets_carry_box_identity(env):
    """`_detect_targets` 要把 box_id 带出来，并按 框名→测点名→检测框N 定 box_name。"""
    write_waypoint_tree(env["tmp"], [
        rect_box(name="3号柜电流表", box_id="B1", point_id="PT-1", point_name="测点1"),
        # 没名字、没测点：只能落到"检测框N"（N 是动作内第几个框，不是全局序号）
        rect_box(name="", box_id="B2", point_id="", point_name=""),
        # 没框名但有测点名：用测点名，比"检测框3"有信息量
        rect_box(name="", box_id="B3", point_id="PT-3", point_name="测点3"),
    ])
    targets = make_node()._detect_targets(pending_action(), ["FLOW-1"])

    assert [t.box_id for t in targets] == ["B1", "B2", "B3"]
    assert [t.point_id for t in targets] == ["PT-1", "", "PT-3"]
    assert [t.box_name for t in targets] == ["3号柜电流表", "检测框2", "测点3"]
    # 流程引用与区域照常带出（别为了新字段把老字段弄丢）
    assert all(t.flow_ref == "FLOW-1" for t in targets)
    assert targets[0].region["shape"] == "rect"
    assert len(targets[0].region["points"]) == 4


def test_detect_targets_still_dedupes_bound_point(env):
    """一个测点只能绑一处：两个框绑同一个测点时只取先到的（老规则不能丢）。"""
    write_waypoint_tree(env["tmp"], [
        rect_box(name="A", box_id="B1", point_id="PT-1"),
        rect_box(name="B", box_id="B2", point_id="PT-1"),
    ])
    targets = make_node()._detect_targets(pending_action(), ["FLOW-1"])
    assert [t.box_id for t in targets] == ["B1"]


def test_detect_targets_keeps_unbound_boxes(env):
    """⚠️ 去重只针对**绑了测点**的框：没绑测点的框不能被当成"重复"丢掉。"""
    write_waypoint_tree(env["tmp"], [
        rect_box(name="A", box_id="B1"),
        rect_box(name="B", box_id="B2"),
        rect_box(name="C", box_id="B3"),
    ])
    targets = make_node()._detect_targets(pending_action(), ["FLOW-1"])
    assert [t.box_id for t in targets] == ["B1", "B2", "B3"]


def test_detect_targets_falls_back_for_legacy_tree(env):
    """老树（没有 box_id）：退回 point_id，至少让绑了测点的框还能对上。"""
    write_waypoint_tree(env["tmp"], [
        rect_box(name="A", point_id="PT-1"),
        rect_box(name="B", point_id=""),
    ])
    targets = make_node()._detect_targets(pending_action(), ["FLOW-1"])
    assert [t.box_id for t in targets] == ["PT-1", ""]
    # 框名仍然要有（树上看不出"这个框没身份"）
    assert [t.box_name for t in targets] == ["A", "B"]


# ---------------------------------------------------------------- 3. 回调回写

def _action_row(Session, *, box_flow):
    db = Session()
    row = InspectionActionResult(
        inspection_id=TASK_ID, floor=1, waypoint_id="w1", action_id="a1",
        action_seq=0, action_type=1, detect_type="fms", status="ok",
        picture="p.jpg", dispatch_status="done",
        infer_request_json={"box_flow": box_flow},
    )
    db.add(row)
    db.commit()
    rid = row.id
    db.close()
    return rid


def _callback_body(box_id, box_name="", *, point_id="", display="异常"):
    """算法服务回调：一般会把入参原样带回，所以 box_id / box_name 也在里面。"""
    return {
        "info": {"boxs": [{
            "id": 1,
            "pointId": point_id,
            "box_id": box_id,
            "box_name": box_name,
            "name": "person_intrusion",
            "display_name": "人员入侵",
            "display": display,
            "parameter": "0",
            "code": "0",
            "msg": "",
            "error": "",
            "extra": {
                "detections": [{"name": "person", "conf": 0.9, "box": [10, 20, 30, 40]}],
                "result_info": {"orig_shape": [100, 200]},
            },
        }]},
    }


def test_callback_writes_point_without_point_id(env, monkeypatch):
    """★ 没绑测点的框：结果**必须**回写（老代码在这里整条丢掉）。"""
    import app.services.alarm_processor as ap

    monkeypatch.setattr(ap, "DETECT_PREFAB_DIR", env["tmp"] / "检测算法")
    write_detect_flow(env["tmp"])
    Session = env["Session"]
    rid = _action_row(Session, box_flow=[{
        "id": 1, "flow_ref": "FLOW-1", "point_id": "", "point_name": "",
        "box_id": "B2", "box_name": "检测框2",
        "region": {"shape": "rect", "points": []},
    }])

    db = Session()
    action = db.query(InspectionActionResult).filter_by(id=rid).first()
    stats = ap.process_callback(db, action, _callback_body("B2", "检测框2"))
    db.commit()

    assert stats["points"] == 1, stats
    pt = db.query(InspectionPointResult).filter_by(action_result_id=rid).first()
    assert pt is not None, "没绑测点的结果被丢掉了"
    assert pt.box_id == "B2" and pt.box_name == "检测框2"
    assert pt.point_id == ""            # 确实没绑测点
    assert pt.kind == "detect" and pt.status == "ok"
    assert pt.detect_flow == "FLOW-1"
    assert pt.label == "person" and pt.confidence is not None
    # 检出框要归一化（10/200=0.05）
    assert pt.boxes_json and abs(pt.boxes_json[0]["x"] - 0.05) < 1e-6
    db.close()


def test_callback_is_idempotent_by_box_id(env, monkeypatch):
    """同一框回调两次只更新一行（不能续跑一次多一条）。"""
    import app.services.alarm_processor as ap

    monkeypatch.setattr(ap, "DETECT_PREFAB_DIR", env["tmp"] / "检测算法")
    write_detect_flow(env["tmp"])
    Session = env["Session"]
    rid = _action_row(Session, box_flow=[{
        "id": 1, "flow_ref": "FLOW-1", "point_id": "", "point_name": "",
        "box_id": "B2", "box_name": "检测框2",
        "region": {"shape": "rect", "points": []},
    }])

    db = Session()
    action = db.query(InspectionActionResult).filter_by(id=rid).first()
    ap.process_callback(db, action, _callback_body("B2", "检测框2"))
    ap.process_callback(db, action, _callback_body("B2", "检测框2"))
    db.commit()
    assert db.query(InspectionPointResult).filter_by(action_result_id=rid).count() == 1
    db.close()


def test_callback_updates_placeholder_row_by_box_id(env, monkeypatch):
    """巡检开始时的占位行（point_id 为空、box_id 已写）要能被更新，而不是新插一行。"""
    import app.services.alarm_processor as ap

    monkeypatch.setattr(ap, "DETECT_PREFAB_DIR", env["tmp"] / "检测算法")
    write_detect_flow(env["tmp"])
    Session = env["Session"]
    rid = _action_row(Session, box_flow=[{
        "id": 1, "flow_ref": "FLOW-1", "point_id": "", "point_name": "",
        "box_id": "B2", "box_name": "检测框2",
        "region": {"shape": "rect", "points": []},
    }])
    db = Session()
    db.add(InspectionPointResult(
        action_result_id=rid, inspection_id=TASK_ID, floor=1,
        waypoint_id="w1", action_id="a1", point_id="", box_id="B2",
        box_name="检测框2", seq=0, kind="detect", status="pending",
    ))
    db.commit()

    action = db.query(InspectionActionResult).filter_by(id=rid).first()
    ap.process_callback(db, action, _callback_body("B2", "检测框2"))
    db.commit()

    rows = db.query(InspectionPointResult).filter_by(action_result_id=rid).all()
    assert len(rows) == 1, "占位行没被更新，反而新插了一行"
    assert rows[0].status == "ok" and rows[0].kind == "detect"
    db.close()


def test_unbound_boxes_do_not_merge_alarms(env, monkeypatch):
    """★ 同一个动作下两个都没绑测点的框，告警**不能**被去重窗口合成一条。

    只按 `(run_id, alarm_type, point_id)` 去重时，两个框的 point_id 都是 ""，
    第二条告警会被当成"同一条的重复"合并掉 —— 等于悄悄丢告警。
    """
    import app.services.alarm_processor as ap

    monkeypatch.setattr(ap, "DETECT_PREFAB_DIR", env["tmp"] / "检测算法")
    write_detect_flow(env["tmp"], dedup_seconds=60)
    Session = env["Session"]
    rid = _action_row(Session, box_flow=[
        {"id": 1, "flow_ref": "FLOW-1", "point_id": "", "point_name": "",
         "box_id": "B1", "box_name": "框1", "region": {"shape": "rect", "points": []}},
        {"id": 2, "flow_ref": "FLOW-1", "point_id": "", "point_name": "",
         "box_id": "B2", "box_name": "框2", "region": {"shape": "rect", "points": []}},
    ])

    body = {"info": {"boxs": [
        _callback_body("B1", "框1")["info"]["boxs"][0] | {"id": 1},
        _callback_body("B2", "框2")["info"]["boxs"][0] | {"id": 2},
    ]}}
    db = Session()
    action = db.query(InspectionActionResult).filter_by(id=rid).first()
    stats = ap.process_callback(db, action, body)
    db.commit()

    assert stats["alarms"] == 2, f"两个框的告警被合并了: {stats}"
    alarms = db.query(Alarm).filter_by(action_result_id=rid).all()
    assert sorted(a.box_id for a in alarms) == ["B1", "B2"]
    # 没绑测点时用框名兜底，告警列表里不能是一条没名字的记录
    assert sorted(a.point_name for a in alarms) == ["框1", "框2"]
    db.close()


# ---------------------------------------------------------------- 4. 提交报文

def write_meter_flow(tmp_path, *, detect_id="FLOW-1"):
    """写一条能被 `_infer_async` 提交的流程（必须含 MeterAlgorithmNode）。

    当前算法推理服务只认 `MeterAlgorithmNode` 选的算法（`box.name` 是 panel_list
    的 name 编码），流程里没有它时 `_infer_async` 会整框跳过。
    """
    d = tmp_path / "检测算法"
    d.mkdir(parents=True, exist_ok=True)
    spec = {
        "name": "电流表", "description": "",
        "root": {"type": "DetectPipelineNode",
                 "properties": {"name": "流程", "enabled": True,
                                "detect_id": detect_id, "scene": ""},
                 "children": [{
                     "type": "MeterAlgorithmNode",
                     "properties": {"name": "算法", "enabled": True,
                                    "panel_algorithm": "1_0_0_1_53_0",
                                    "threshold": 0.5, "labels": [], "max_results": 0,
                                    "params": {}, "note": ""},
                     "children": [],
                 }]},
    }
    (d / "电流表.prefab.json").write_text(
        json.dumps(spec, ensure_ascii=False), encoding="utf-8")


def test_infer_payload_carries_box_id_and_name(env, monkeypatch):
    """★ 提交给算法服务的报文里必须有 `box_id` / `box_name`。

    这就是本改动要解决的问题：`pointId` 可能是空的（没绑测点），只靠它的话结果
    回来认不回是哪个框。算法服务一般会把入参原样带回结果框，所以这两个字段同时也是
    **回调时的定位键**（见 `alarm_processor._lookup_bf`）。
    """
    import httpx

    write_meter_flow(env["tmp"])
    img = env["tmp"] / "fig.jpg"
    img.write_bytes(b"\xff\xd8\xff\xd9")     # 内容不重要：尺寸被替身掉了

    sent = {}

    class Resp:
        status_code = 200
        text = '{"code": 0}'

        def json(self):
            return {"code": 0}

    def fake_post(url, *, data=None, files=None, headers=None, timeout=None,
                  verify=None, **kw):
        sent["url"] = url
        sent["data"] = dict(data or {})
        for f in (files or {}).values():     # 真 open 的文件句柄要关掉
            f[1].close()
        return Resp()

    monkeypatch.setattr(httpx, "post", fake_post)

    node = make_node()
    monkeypatch.setattr(node, "_image_size", lambda p: (200, 100))
    monkeypatch.setattr(node, "_save_infer_trace", lambda *a, **k: None)
    monkeypatch.setattr(node, "_fms_host", lambda: "127.0.0.1:8000")

    from app.prefab.nodes.task_executor import DetectTarget

    def target(box_id, box_name, point_id, point_name, flow_ref="FLOW-1"):
        return DetectTarget(
            flow_ref=flow_ref, algorithm="1_0_0_1_53_0",
            point_id=point_id, point_name=point_name,
            region={"shape": "rect",
                    "points": [{"x": 0.1, "y": 0.2}, {"x": 0.5, "y": 0.6}]},
            params={}, box_id=box_id, box_name=box_name,
        )

    node._infer_async(
        "http://infer/infer", pending_action(),
        {"auth_header": "", "timeout": 2.0, "verify_tls": True},
        image=str(img),
        targets=[target("B1", "3号柜电流表", "PT-1", "测点1"),
                 target("B2", "检测框2", "", "")],
        callback_url="http://127.0.0.1:8000/api/inspection/report/detect_callback",
    )

    info = json.loads(sent["data"]["info"])
    boxes = info["boxs"]
    assert [b["box_id"] for b in boxes] == ["B1", "B2"]
    assert [b["box_name"] for b in boxes] == ["3号柜电流表", "检测框2"]
    # 没绑测点的那个框 pointId 为空，但身份仍在
    assert boxes[1]["pointId"] == "" and boxes[1]["box_id"] == "B2"
    assert boxes[0]["pointId"] == "PT-1"
    # 序号仍是提交顺序（回调靠它做第一层匹配）
    assert [b["id"] for b in boxes] == [1, 2]
    # 区域要转成像素框（归一化 0.1~0.5 × 宽 200）
    assert boxes[0]["box"] == [20, 20, 100, 60]
    # 回调地址照常带上
    assert sent["data"]["callbackUrl"].endswith("/report/detect_callback")
