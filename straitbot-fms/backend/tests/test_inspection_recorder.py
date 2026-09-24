"""巡检结果落库：巡检开始先占位、动作跑完回填。

用**临时 SQLite**（不碰 data/fms.db）+ 假视觉/假云台跑完一次巡检，然后直接查表。
假的对象与驱动函数复用 `test_inspection_runtime`（与 `test_inspection_protocol`
引用 `test_inspection_plans` 同一路子，避免把 fake 再抄一份）。
"""
import pytest
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from app.database import Base
from app.models import (
    InspectionActionResult,
    InspectionPointResult,
    InspectionRun,
)
from app.rail.recorder import InspectionRecorder, STATUS_OK, STATUS_PENDING
from tests.test_inspection_runtime import (
    drive_inspection,
    make_robot,
    until,
)

TASK_ID = "d" * 32


def make_session(tmp_path):
    """临时库 + 建表，返回 sessionmaker（每次调用一个独立会话）。"""
    engine = create_engine(f"sqlite:///{tmp_path / 'rec.db'}",
                           connect_args={"check_same_thread": False})
    Base.metadata.create_all(engine)
    return sessionmaker(bind=engine)


def payload(detect_type=None):
    """一次巡检：1 个航点 / 2 个动作（可见光拍照 + 带 2 个测温点的测温）。"""
    seg = {
        "floor": 1, "id": TASK_ID, "name": "落库测试", "plan": "p",
        "waypoint": [{
            "id": "w1", "index": 1,
            "pose": {"point": {"x": 1.0, "y": 0.0, "z": 0.0}, "theta": 0.0},
            "action": [
                {"id": "a1", "type": 1},
                {"id": "a2", "type": 2, "thermometry_points": [
                    {"id": "p1", "thermometry_param": {"emissivity": 0.96}},
                    {"id": "p2", "thermometry_param": {"emissivity": 0.95}},
                ]},
            ],
        }],
    }
    if detect_type:
        seg["detectType"] = detect_type
    return [seg]


def test_placeholders_generated_for_every_action_and_point(tmp_path):
    """巡检开始即为每个动作/测温点生成 pending 占位，run 也一并建好。"""
    Session = make_session(tmp_path)
    r, clk = make_robot(tmp_path, recorder=InspectionRecorder(Session))
    r.sm.start()
    until(r, clk, "空闲")

    r.接收巡检任务(payload())
    # 占位发生在巡检子机 "start" 那一拍（接收后由状态机推进触发），不是接收的瞬间
    until(r, clk, "移动到航点")

    db = Session()
    runs = db.query(InspectionRun).all()
    assert len(runs) == 1 and runs[0].inspection_id == TASK_ID
    assert runs[0].status == "started"

    acts = db.query(InspectionActionResult).order_by(InspectionActionResult.id).all()
    assert len(acts) == 2
    assert [a.action_id for a in acts] == ["a1", "a2"]
    assert [a.action_seq for a in acts] == [0, 1]
    assert [a.action_type for a in acts] == [1, 2]
    # 关键：全是 pending —— 下游就轮询这个
    assert all(a.status == STATUS_PENDING for a in acts)
    assert all(a.run_id == runs[0].id for a in acts)
    assert all(a.floor == 1 and a.waypoint_id == "w1" for a in acts)

    pts = db.query(InspectionPointResult).order_by(InspectionPointResult.id).all()
    assert [(p.point_id, p.seq) for p in pts] == [("p1", 0), ("p2", 1)]
    assert all(p.status == STATUS_PENDING for p in pts)
    assert all(p.action_result_id == acts[1].id for p in pts)   # 都挂在测温动作下
    db.close()


def test_placeholders_are_idempotent(tmp_path):
    """重复下发 / 续跑再次调用：不能把占位翻一倍。"""
    Session = make_session(tmp_path)
    r, clk = make_robot(tmp_path, recorder=InspectionRecorder(Session))
    r.sm.start()
    until(r, clk, "空闲")

    r.接收巡检任务(payload())
    until(r, clk, "移动到航点")
    r.准备巡检结果占位()      # 模拟续跑时又走了一遍
    r.准备巡检结果占位()

    db = Session()
    assert db.query(InspectionRun).count() == 1
    assert db.query(InspectionActionResult).count() == 2
    assert db.query(InspectionPointResult).count() == 2
    db.close()


def test_action_result_filled_after_execution(tmp_path):
    """动作跑完：占位行翻转成 ok，图路径跟着落进去。"""
    Session = make_session(tmp_path)
    r, clk = make_robot(tmp_path, recorder=InspectionRecorder(Session))
    r.sm.start()
    until(r, clk, "空闲")
    r.接收巡检任务(payload())

    drive_inspection(r, clk)
    assert r.巡检进行中 is False

    db = Session()
    row = db.query(InspectionActionResult).filter(
        InspectionActionResult.action_id == "a1").first()
    assert row.status == STATUS_OK
    assert row.local_path.endswith("a01_a1_visible.jpg")
    assert row.picture == row.local_path          # 可见光图进 picture
    assert row.finish_time is not None
    thermal = db.query(InspectionActionResult).filter(
        InspectionActionResult.action_id == "a2").first()
    assert thermal.status == STATUS_OK
    assert thermal.infrared.endswith("a02_a2_thermometry.jpg")
    db.close()


def test_detect_type_written_into_placeholders(tmp_path):
    """detectType 落进占位行：下游靠它决定这条数据是本地消化还是上报平台。"""
    Session = make_session(tmp_path)
    r, clk = make_robot(tmp_path, recorder=InspectionRecorder(Session))
    r.sm.start()
    until(r, clk, "空闲")
    r.接收巡检任务(payload(detect_type="fms"))
    until(r, clk, "移动到航点")

    db = Session()
    assert {a.detect_type for a in db.query(InspectionActionResult).all()} == {"fms"}
    db.close()


def test_recorder_failure_does_not_stop_inspection(tmp_path):
    """库不可用（会话都建不出来）：巡检照样跑完，图照样落盘。"""
    def broken():
        raise RuntimeError("db down")

    r, clk = make_robot(tmp_path, recorder=InspectionRecorder(broken))
    r.sm.start()
    until(r, clk, "空闲")
    assert r.接收巡检任务(payload())["accepted"] is True

    drive_inspection(r, clk)
    assert r.巡检进行中 is False
    # 落盘的图还在——库没了，数据没丢
    assert list((tmp_path / TASK_ID).glob("*_visible.jpg"))
