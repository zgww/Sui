"""用 ``docs/inspection.json`` 造巡检日志：口径映射与三表产出。

这个脚本是**给演示/联调用的数据源**，产出要能直接喂给巡检日志页，所以关键在
"源数据的私有口径有没有被正确翻译成 FMS 的口径"。这里拿**临时库**跑一遍完整
灌数，再直接查三张表断言，不碰 ``data/fms.db``。
"""
import json
from pathlib import Path

import pytest
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from app.database import Base
from app.models import (
    InspectionActionResult,
    InspectionPointResult,
    InspectionRun,
    Robot,
)

# 脚本在 backend/scripts 下，import 需要 backend 在 sys.path（pytest 的 rootdir 已保证）
from scripts.seed_inspection_log import (      # noqa: E402
    SOURCE,
    _ACTION_TYPE_MAP,
    _rect_to_boxes,
    build_task,
    index_source,
    seed,
)

pytestmark = pytest.mark.skipif(not SOURCE.exists(),
                                reason="docs/inspection.json 不存在")


def make_session(tmp_path):
    engine = create_engine(f"sqlite:///{tmp_path / 'seed.db'}",
                           connect_args={"check_same_thread": False})
    Base.metadata.create_all(engine)
    return sessionmaker(bind=engine)


@pytest.fixture
def seeded(tmp_path, monkeypatch):
    """在临时库上灌一次数据，返回 (sessionmaker, 结果 dict)。"""
    Session = make_session(tmp_path)
    # seed() 用的是模块级 SessionLocal，这里换掉指向临时库
    monkeypatch.setattr("scripts.seed_inspection_log.SessionLocal", Session)
    # robots 表要有行，robot_pk 才落得上
    with Session() as db:
        db.add(Robot(name="测试机器人", ip="10.0.0.1", robot_id=1))
        db.commit()
    result = seed(seed_value=42)
    return Session, result


# ---------------------------------------------------------------- 源数据口径
def test_source_is_single_floor_private_types():
    """源数据是单楼层对象，动作 type 用的是机器人侧私有口径（1000/7/3）。"""
    raw = json.loads(Path(SOURCE).read_text(encoding="utf-8"))
    assert "floor" not in raw                      # 单楼层，没有 floor 字段
    assert raw["id"] and raw["plan"]
    types = {a["type"] for wp in raw["waypoint"] for a in wp.get("action") or []}
    assert types <= set(_ACTION_TYPE_MAP), f"出现未映射的 type: {types}"


def test_build_task_wraps_single_floor():
    """单楼层对象被包成含 ``floor`` 的分段，InspectionTask 能解析。"""
    raw = json.loads(Path(SOURCE).read_text(encoding="utf-8"))
    task = build_task(raw)
    assert task.floor_count == 1
    assert task.floors[0].floor == 1
    assert task.waypoint_count == 106
    assert task.action_count == 107
    # 源数据没写 detectType -> 回落 platform（旧版行为）
    assert task.detect_type == "platform"


def test_index_source_maps_action_id_to_raw_dict():
    """``snap_shot_url`` / ``pdd_channel`` 没进模型，得靠这份索引取。"""
    raw = json.loads(Path(SOURCE).read_text(encoding="utf-8"))
    src = index_source(raw)
    assert len(src) == 107
    with_url = [v for v in src.values() if v.get("snap_shot_url")]
    assert with_url, "源数据里应该有 snap_shot_url"
    # 局放动作带 pdd_channel
    assert any(v.get("pdd_channel") is not None for v in src.values())


def test_rect_to_boxes_keeps_normalized_coords():
    """rect 已是归一化 0~1，直接当检出框；认不出的返回空表。"""
    boxes = _rect_to_boxes({"thermometry_param": {"rect": {
        "x": 0.1, "y": 0.2, "w": 0.3, "h": 0.4}}})
    assert boxes == [{"x": 0.1, "y": 0.2, "w": 0.3, "h": 0.4}]
    assert _rect_to_boxes({}) == []
    assert _rect_to_boxes({"thermometry_param": {"rect": {"x": "坏"}}}) == []


# ---------------------------------------------------------------- 三表产出
def test_seed_creates_one_run(seeded):
    Session, result = seeded
    with Session() as db:
        runs = db.query(InspectionRun).all()
        assert len(runs) == 1
        run = runs[0]
        assert run.inspection_id == result["inspection_id"]
        assert run.status in ("started", "done")
        assert run.robot_pk is not None
        assert run.start_time is not None
        assert run.remark


def test_seed_creates_action_row_per_source_action(seeded):
    """107 个源动作 -> 107 条动作行，且 type 被翻成协议口径 1/2/3。"""
    Session, result = seeded
    with Session() as db:
        rows = db.query(InspectionActionResult).all()
        assert len(rows) == 107
        types = {r.action_type for r in rows}
        # 私有口径 1000/7 都该落到 1，3 -> 3
        assert types <= {1, 2, 3}, f"动作类型未被翻译：{types}"
        assert 3 in types, "录像动作没保留"
        # 源 type 记进 raw_json 兜底，不丢。**未执行（pending）的那条没回填过**，
        # raw_json 天然为空 —— 占位行只记任务结构，不记结果。
        filled = [r for r in rows if r.status != "pending"]
        assert all((r.raw_json or {}).get("source_type") is not None for r in filled)
        pending = [r for r in rows if r.status == "pending"]
        assert all(r.raw_json is None for r in pending), "未执行的行不该有结果"


def test_seed_action_status_and_dispatch_are_not_all_green(seeded):
    """结果不该全绿：要有失败/跳过/未执行，分发也要有失败项，页面才验得动。"""
    Session, result = seeded
    with Session() as db:
        rows = db.query(InspectionActionResult).all()
        statuses = {r.status for r in rows}
        assert "ok" in statuses
        assert statuses & {"failed", "skipped", "pending"}, "没有异常/未完成状态"
        dispatches = {r.dispatch_status for r in rows}
        assert "done" in dispatches
        assert dispatches & {"failed", "pending"}, "分发状态没有失败/待处理"
        # 分发失败的要有原因
        bad = [r for r in rows if r.dispatch_status == "failed"]
        assert bad and all(r.dispatch_error for r in bad)


def test_seed_video_action_has_no_picture_but_media(seeded):
    """录像动作没有图片（没有可看的一帧），走 media 而不是 picture。"""
    Session, result = seeded
    with Session() as db:
        videos = db.query(InspectionActionResult).filter(
            InspectionActionResult.action_type == 3).all()
        assert len(videos) == 1
        assert not videos[0].picture
        assert videos[0].media.endswith(".mp4")


def test_seed_pdd_channel_preserved(seeded):
    """局放动作的原始通道号存进 pdd_json。"""
    Session, result = seeded
    with Session() as db:
        rows = db.query(InspectionActionResult).filter(
            InspectionActionResult.pdd_json.isnot(None)).all()
        assert rows
        assert all(r.pdd_json.get("channel") is not None for r in rows)


def test_seed_points_are_detect_kind_with_boxes(seeded):
    """``thermometry_points`` 语义是归一化检测区域 -> kind=detect + 检出框。"""
    Session, result = seeded
    with Session() as db:
        points = db.query(InspectionPointResult).all()
        assert len(points) == 19
        # 一个都不能留成 thermometry（那是占位默认值，源数据里没有测温点）
        assert {p.kind for p in points} == {"detect"}
        assert all(p.boxes_json for p in points), "检测点应该带检出框"
        assert all(p.unit == "" for p in points), "检测点不该有温度单位"
        # 结论三态都要出现（通过 / 未通过 / 动作失败未判定）
        passed_vals = {p.passed for p in points if p.status == "ok"}
        assert True in passed_vals and False in passed_vals
        assert any(p.status == "failed" for p in points)


def test_seed_is_idempotent(seeded, monkeypatch, tmp_path):
    """重复灌不产生重复行（占位去重 + 回填 UPDATE）。"""
    Session, first = seeded
    monkeypatch.setattr("scripts.seed_inspection_log.SessionLocal", Session)
    seed(seed_value=42)
    with Session() as db:
        assert db.query(InspectionRun).count() == 1
        assert db.query(InspectionActionResult).count() == 107
        assert db.query(InspectionPointResult).count() == 19
