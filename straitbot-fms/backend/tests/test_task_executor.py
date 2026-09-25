"""任务执行器背后的纯逻辑：分流决策 / 上报载荷 / 推理响应归一化 / 检测流程引用。

这里锁的是"数据分发"这件事最容易悄悄错的地方：

- **detect_type 回落**：只有明确写了 `fms` 才本地检测，空/None/未知值/大小写
  混写一律回落 platform（与 `rail/inspection.py` 同一约定，旧数据不能突然开始
  产生检测结论）；
- **录像不分发**：动作类型 3 没有图像，必须 skip —— 否则每轮都以"没有图片"
  失败一次，把 `dispatch_attempts` 刷到上限；
- **上报载荷形状**：必须与旧平台 cmd=104 的 `/report/result` 同形状，且
  **FMS 内部字段（detect_type / local_path）不能混进去**；
- **推理响应归一化**：外部推理服务的字段名/嵌套深度不受本系统控制，认不出的
  形状要退回"没检出"而不是抛异常（一次格式对不上不该让数据永久失败）；
- **流程引用 id 的取值规则**：必须与前端下料的规则一致，否则现场会出现
  "下拉选中了、执行时却找不到流程"。

节点类本身（线程起停、HTTP、回写）不在这里测——它需要真线程和数据库，见
`test_task_executor_node.py`。
"""
from app.prefab.task_executor import (
    DETECT_FMS,
    DETECT_PLATFORM,
    DISPATCH_PENDING,
    PendingAction,
    action_image,
    apply_flow_result,
    flow_ref,
    group_plans,
    index_flows,
    infer_payload,
    infer_result,
    is_dispatchable,
    normalize_detect_type,
    plan_dispatch,
    should_retry,
    to_pending,
    upload_header,
    upload_payload,
)


# ---------------------------------------------------------------- 小工厂

def pa(**kw) -> PendingAction:
    base = dict(action_result_id=1, inspection_id="I" * 32, floor=1,
                waypoint_id="w1", action_id="a1", action_type=1,
                detect_type=DETECT_PLATFORM, picture="p.jpg", infrared="",
                local_path="", inplace_ts="2026-09-22T10:00:00")
    base.update(kw)
    return PendingAction(**base)


class FakeRow:
    """轻量假行（模拟 ORM 行，只带用到的那几个属性）。"""

    def __init__(self, **kw):
        self.__dict__.update(kw)


# ---------------------------------------------------------------- detect_type 回落

def test_detect_type_falls_back_to_platform():
    """只有明确写 fms 才本地检测；其余（含未知值）一律 platform。"""
    assert normalize_detect_type("fms") == DETECT_FMS
    assert normalize_detect_type("FMS") == DETECT_FMS
    assert normalize_detect_type(" fms ") == DETECT_FMS
    for v in (None, "", "  ", "platform", "PLATFORM", "robot", "fms2", 0, [], {}):
        assert normalize_detect_type(v) == DETECT_PLATFORM, v


def test_to_pending_normalizes_detect_type():
    """ORM 行 -> PendingAction 时就归一化：坏值不该流到后面的判定里。"""
    assert to_pending(FakeRow(id=7, detect_type="ROBOT")).detect_type == DETECT_PLATFORM
    assert to_pending(FakeRow(id=7, detect_type="fms")).detect_type == DETECT_FMS
    assert to_pending(FakeRow(id=7)).detect_type == DETECT_PLATFORM


def test_to_pending_tolerates_missing_columns():
    """缺列（老库 / 轻量假行）不能抛：getattr 一律给兜底。"""
    p = to_pending(FakeRow(id=3))
    assert p.action_result_id == 3
    assert p.floor == 0 and p.dispatch_attempts == 0 and p.robot_pk is None


# ---------------------------------------------------------------- 可分发判定

def test_video_action_is_not_dispatchable():
    """录像（3）没有图像：不分发，否则会一直以"没有图片"失败刷 attempts。"""
    assert is_dispatchable(1) is True
    assert is_dispatchable(2) is True
    assert is_dispatchable(3) is False
    assert is_dispatchable(None) is False
    assert is_dispatchable("abc") is False


def test_action_image_picks_infrared_for_thermometry():
    """测温优先红外（测点框画在热像画面上），拍照优先可见光，都回落到 local_path。

    `prefer_infrared` 留空时**由行的 action_type 自己决定**：默认值比调用方可靠，
    漏传的后果是"测温流程拿可见光图去测点区域找框"，跑得出结论但全是错的。
    """
    assert action_image(pa(action_type=2, picture="v.jpg", infrared="i.jpg")) == "i.jpg"
    assert action_image(pa(action_type=1, picture="v.jpg", infrared="i.jpg")) == "v.jpg"
    assert action_image(pa(action_type=1, picture="", local_path="l.jpg")) == "l.jpg"
    # 测温没红外时退回可见光，而不是直接空
    assert action_image(pa(action_type=2, picture="v.jpg")) == "v.jpg"
    assert action_image(pa(action_type=1, picture="", infrared="")) == ""
    # 显式传参优先于行上的类型
    assert action_image(pa(action_type=1, infrared="i.jpg"), prefer_infrared=True) == "i.jpg"
    # 轻量假行（没有 action_type 属性）不能抛
    assert action_image(FakeRow(picture="v.jpg")) == "v.jpg"


def test_pending_image_uses_action_type():
    assert pa(action_type=2, picture="v.jpg", infrared="i.jpg").image == "i.jpg"
    assert pa(action_type=1, picture="v.jpg", infrared="i.jpg").image == "v.jpg"


def test_should_retry_respects_limit():
    assert should_retry(pa(dispatch_attempts=0), 3) is True
    assert should_retry(pa(dispatch_attempts=2), 3) is True
    assert should_retry(pa(dispatch_attempts=3), 3) is False
    assert should_retry(pa(dispatch_attempts=99), 0) is True   # 0 = 不限次


# ---------------------------------------------------------------- 分流决策

def test_plan_dispatch_platform_uploads_without_image():
    """platform 分支不做图校验：图路径可能就是平台自己用的。"""
    plan = plan_dispatch(pa(detect_type="platform", picture="", local_path=""))
    assert plan.mode == "upload" and plan.reason == ""


def test_plan_dispatch_fms_needs_image_and_flows():
    ok = plan_dispatch(pa(detect_type="fms", picture="p.jpg"), flows=["F1"])
    assert ok.mode == "detect" and ok.flows == ["F1"] and ok.image == "p.jpg"

    no_img = plan_dispatch(pa(detect_type="fms", picture="", local_path=""), flows=["F1"])
    assert no_img.mode == "skip" and "图片" in no_img.reason

    no_flow = plan_dispatch(pa(detect_type="fms", picture="p.jpg"), flows=[])
    assert no_flow.mode == "skip" and "检测框" in no_flow.reason

    # 空字符串的流程引用 = 没配，不能当成一条有效流程
    blank = plan_dispatch(pa(detect_type="fms", picture="p.jpg"), flows=["", "  "])
    assert blank.mode == "skip"


def test_plan_dispatch_skips_video_and_exceeded_retry():
    assert plan_dispatch(pa(action_type=3)).mode == "skip"
    assert plan_dispatch(pa(dispatch_attempts=5), max_attempts=5).mode == "skip"
    assert plan_dispatch(pa(dispatch_attempts=4), max_attempts=5).mode == "upload"


def test_group_plans_buckets_by_mode():
    plans = [
        plan_dispatch(pa(detect_type="platform")),
        plan_dispatch(pa(detect_type="fms", picture="p.jpg"), flows=["F"]),
        plan_dispatch(pa(action_type=3)),
    ]
    g = group_plans(plans)
    assert len(g["upload"]) == 1 and len(g["detect"]) == 1 and len(g["skip"]) == 1


# ---------------------------------------------------------------- 上报载荷

def test_upload_payload_matches_cmd104_shape():
    """形状必须与旧平台 cmd=104 的 /report/result 对得上，老平台才解析得了。"""
    body = upload_payload(pa(picture="p.jpg", infrared="i.jpg"))
    assert body["inspection_id"] == "I" * 32
    assert body["floor"] == 1
    item = body["results"][0]
    assert item["waypoint_id"] == "w1" and item["action_id"] == "a1"
    assert item["picture"] == "p.jpg" and item["infrared"] == "i.jpg"
    assert item["inplace_timestamp"] == "2026-09-22T10:00:00"
    assert item["code"] == 0 and item["media"] == ""


def test_upload_payload_excludes_internal_fields():
    """detect_type / local_path 是本系统账本，平台不认（与下发真机前裁 detectType 同理）。"""
    item = upload_payload(pa(detect_type="fms", local_path="/tmp/x.jpg",
                             dispatch_attempts=3))["results"][0]
    assert "detect_type" not in item and "detectType" not in item
    assert "local_path" not in item and "dispatch_attempts" not in item


def test_upload_payload_only_passes_known_extra_fields():
    """extra 里只挑平台认得的业务字段，不整体合并（防内部字段从 extra 漏出去）。"""
    body = upload_payload(pa(), extra={"thermometry_points": [{"id": "p1"}],
                                       "local_path": "/tmp/x.jpg",
                                       "internal_secret": 1})
    item = body["results"][0]
    assert item["thermometry_points"] == [{"id": "p1"}]
    assert "local_path" not in item and "internal_secret" not in item


def test_upload_header_parses_and_warns():
    assert upload_header("Authorization: Bearer x") == {"Authorization": "Bearer x"}
    assert upload_header("A: 1; B: 2") == {"A": "1", "B": "2"}
    # 缺冒号 / 空值的整段忽略：发一个坏头出去只会换来 401，不如不带
    assert upload_header("bogus;  : v; K:") == {}
    assert upload_header("") == {}
    assert upload_header(None) == {}


# ---------------------------------------------------------------- 推理请求

def test_infer_payload_carries_image_algorithm_region():
    body = infer_payload(pa(), flow="F1", algorithm="person_intrusion",
                         image="p.jpg",
                         region={"shape": "rect",
                                 "points": [{"x": 0.1, "y": 0.2}]},
                         extra={"threshold": 0.5, "labels": ["person"],
                                "note": "不该传", "params": {}})
    assert body["image"] == "p.jpg"
    assert body["algorithm"] == "person_intrusion"
    assert body["flow"] == "F1"
    assert body["region"]["shape"] == "rect"
    assert body["threshold"] == 0.5 and body["labels"] == ["person"]
    # 空值/内部字段不传
    assert "note" not in body and "params" not in body
    assert body["waypoint_id"] == "w1" and body["action_id"] == "a1"


def test_infer_payload_omits_empty_region():
    assert "region" not in infer_payload(pa(), image="p.jpg", region={})


# ---------------------------------------------------------------- 响应归一化

def test_infer_result_reads_detections_list():
    out = infer_result({"detections": [
        {"label": "person", "score": 0.31, "x": 0.1, "y": 0.2, "w": 0.3, "h": 0.4},
        {"label": "person", "score": 0.87, "x": 0.5, "y": 0.5, "w": 0.2, "h": 0.2},
    ]})
    assert out["label"] == "person" and abs(out["confidence"] - 0.87) < 1e-6
    assert len(out["boxes"]) == 2 and out["boxes"][1]["x"] == 0.5
    # 检出即命中
    assert out["passed"] is True


def test_infer_result_reads_nested_bbox_and_alt_keys():
    """不同服务的框表示法差这点：`bbox` 数组 / `left,top,width,height` / `conf`。"""
    out = infer_result({"results": [
        {"class": "rust", "conf": 0.6, "bbox": [0.1, 0.1, 0.2, 0.2]},
        {"category": "rust", "confidence": 0.4,
         "box": {"left": 0.3, "top": 0.3, "width": 0.1, "height": 0.1}},
    ]})
    assert len(out["boxes"]) == 2
    assert out["boxes"][0]["label"] == "rust"
    assert out["boxes"][1]["x"] == 0.3 and out["boxes"][1]["y"] == 0.3
    assert abs(out["confidence"] - 0.6) < 1e-6


def test_infer_result_handles_single_result_and_top_level_list():
    one = infer_result({"label": "smoke", "confidence": 0.9,
                        "box": {"x": 0.0, "y": 0.0, "w": 1.0, "h": 1.0}})
    assert one["label"] == "smoke" and one["passed"] is True

    listed = infer_result([{"label": "a", "score": 0.2}])
    assert listed["label"] == "a"


def test_infer_result_reads_meter_value():
    """表计读数类算法给的是数值，不是框。"""
    out = infer_result({"detections": [{"label": "meter", "score": 0.9,
                                        "value": 12.5}]})
    assert out["value"] == 12.5
    assert out["passed"] is True


def test_infer_result_no_conclusion_is_not_ok():
    """解析不出结论时 `ok=False` + `passed=None`（**不是**"没检出"）。

    这两件事必须分开：把"服务没接上"记成"没检出/通过"，日志里会全是"检测通过"，
    现场几乎不可能发现推理服务根本没在工作。
    """
    for raw in (None, "ok", 42, True, {"detections": "x"}, {"foo": "bar"}):
        out = infer_result(raw)
        assert out["ok"] is False, raw
        assert out["passed"] is None and out["boxes"] == [], raw
    # 既无类别也无分数的条目不算一条结果 -> 分析了但没检出，ok 仍为 True
    empty = infer_result({"detections": [{"x": 1, "y": 2}]})
    assert empty["ok"] is True
    assert empty["passed"] is False and empty["boxes"] == []


def test_infer_result_empty_detections_is_analysed_but_not_hit():
    """`detections: []` = 确实分析了、结论是没有目标 -> ok=True, passed=False。"""
    out = infer_result({"detections": []})
    assert out["ok"] is True and out["passed"] is False and out["boxes"] == []
    assert out["label"] == "" and out["confidence"] == 0.0


def test_infer_result_respects_explicit_passed_false():
    """服务明确说 passed=false 时不能被"有框"覆盖成 True。"""
    out = infer_result({"passed": False, "detections": [{"label": "x", "score": 0.9}]})
    assert out["passed"] is False


def test_infer_result_clamps_score():
    out = infer_result({"detections": [{"label": "x", "score": 1.7}]})
    assert out["boxes"][0]["score"] == 1.0


# ---------------------------------------------------------------- 检测流程引用

def test_flow_ref_prefers_detect_id():
    """引用 id 优先取流程根的检测编号，留空才用文件名——与前端下料规则一致。"""
    class Root:
        detect_id = "FLOW-1"

    assert flow_ref(Root(), "人员入侵.prefab.json") == "FLOW-1"


def test_flow_ref_falls_back_to_file_stem():
    class Root:
        detect_id = ""

    assert flow_ref(Root(), "人员入侵.prefab.json") == "人员入侵"
    assert flow_ref(Root(), "人员入侵") == "人员入侵"
    assert flow_ref(None, "人员入侵.prefab.json") == "人员入侵"


def test_index_flows_builds_and_skips_broken():
    """坏流程跳过但不影响好流程：一条写坏的流程不该让整个执行器起不来。"""
    good = {"name": "G", "description": "", "root": {
        "type": "DetectPipelineNode",
        "properties": {"name": "G", "detect_id": "F-GOOD", "enabled": True},
        "children": []}}
    no_root = {"name": "N", "description": ""}
    bad_type = {"name": "B", "description": "", "root": {
        "type": "不存在的节点类型", "properties": {}}}

    flows = index_flows([("G.prefab.json", good), ("N.prefab.json", no_root),
                         ("B.prefab.json", bad_type)])
    assert set(flows) == {"F-GOOD"}
    assert flows["F-GOOD"].type == "DetectPipelineNode"


def test_index_flows_keeps_first_on_duplicate_ref():
    def spec(detect_id, name):
        return {"name": name, "description": "", "root": {
            "type": "DetectPipelineNode",
            "properties": {"name": name, "detect_id": detect_id, "enabled": True},
            "children": []}}

    flows = index_flows([("A.prefab.json", spec("DUP", "先到")),
                         ("B.prefab.json", spec("DUP", "后到"))])
    assert list(flows) == ["DUP"] and flows["DUP"].name == "先到"


# ---------------------------------------------------------------- 流程结果并进测点

def test_apply_flow_result_passed_false_is_still_ok():
    """流程拦下（这次不报）是**正常结论**，不是失败：状态照样 ok，passed 带上去。"""
    from app.prefab.task_executor import PointResult

    class Run:
        passed = False
        stopped_by = "结果过滤（置信度 0.30 < 过滤线 0.50）"
        actions = []
        notes = ["结果过滤：置信度 0.30 < 过滤线 0.50"]

    res = PointResult(point_id="p1")
    apply_flow_result(res, Run(), algorithm="person_intrusion")
    assert res.status == "ok"          # 没被改成 failed
    assert res.passed is False
    assert res.algorithm == "person_intrusion"
    assert res.detect["stopped_by"].startswith("结果过滤")
    assert res.detect["notes"]


def test_apply_flow_result_keeps_actions_for_audit():
    from app.prefab.task_executor import PointResult

    class Run:
        passed = True
        stopped_by = None
        actions = [{"kind": "alarm", "level": "一般告警"}]
        notes = []

    res = PointResult(point_id="p1")
    apply_flow_result(res, Run())
    assert res.passed is True
    assert res.detect["actions"][0]["kind"] == "alarm"
