"""用 ``docs/inspection.json`` 的真实数据灌一份完整的巡检日志。

## 为什么需要它

巡检日志页面（``/inspection/log``）读的是 ``inspection_runs`` /
``inspection_action_results`` / ``inspection_point_results`` 三张表，而这三张表是
**巡检开始时先占位、执行中再回填**才有的。没连机器人、没跑过巡检，页面就是空的，
前端做不出来也验不了。本脚本把现场备份下来的那份真实任务数据按同一条链路
（``InspectionTask`` -> ``InspectionRecorder``）落进库，得到一份"像真跑过一次"的
账本：run + 107 条动作 + 19 条测点，状态有成功/失败/跳过，分发也有已完成/待处理/失败。

## 数据来源与口径映射

``docs/inspection.json`` 是**机器人侧**的任务备份，动作 ``type`` 用的是私有口径
（``1000`` 可见光检测 / ``7`` 局部放电 / ``3`` 录像），而 FMS 的
``inspection_action_results.action_type`` 是**设备协议口径**（1 拍照 / 2 测温 / 3 录像）。
两边对不上，所以这里显式过一张映射表（``_ACTION_TYPE_MAP``），并保留原始 type：

- ``1000``（97 条）-> ``1`` 拍照：一图一检测，图片 URL 就是 ``snap_shot_url``；
- ``7``（9 条）-> ``1`` 拍照：局部放电，原始 ``pdd_channel`` 存进 ``pdd_json``；
- ``3``（1 条）-> ``3`` 录像：带 ``duration``，没有图，也没有测点。

``thermometry_points``（19 个航点各 1 个）**不是温度值**，是归一化的**检测区域**
（``rect {x,y,w,h}`` 都在 0~1），语义上属于检测点 —— 所以落 ``kind='detect'``，
把 rect 转成 ``boxes_json``，``unit`` 留空（检测点没有温度单位）。

## 顶层结构

源文件是**单楼层对象**（没有 ``floor``），而 ``InspectionTask`` 期望楼层分段列表。
这里包一层补 ``floor: 1``（该站是单层配电室，航点 ``pose.point.z`` 恒 0）。

## 幂等

``InspectionRecorder.ensure_placeholders`` 按 ``(floor, waypoint_id, action_id)``
去重，重复跑不会插重复行；回填也是 UPDATE。所以本脚本可以反复执行。

用法（必须在 ``backend`` 目录下、用项目解释器）::

    python scripts/seed_inspection_log.py
    python scripts/seed_inspection_log.py --reset   # 先清掉旧 run 再灌
"""
from __future__ import annotations

import argparse
import json
import random
import sys
from datetime import UTC, datetime, timedelta
from pathlib import Path
from typing import Any, Optional

BACKEND_DIR = Path(__file__).resolve().parent.parent
if str(BACKEND_DIR) not in sys.path:
    sys.path.insert(0, str(BACKEND_DIR))

from app.database import SessionLocal, init_db            # noqa: E402
from app.models import (                                   # noqa: E402
    InspectionActionResult,
    InspectionPointResult,
    InspectionRun,
    Robot,
)
from app.rail.inspection import InspectionTask             # noqa: E402
from app.rail.recorder import InspectionRecorder           # noqa: E402

#: 源数据（相对仓库根）。
SOURCE = BACKEND_DIR.parent / "docs" / "inspection.json"

#: 机器人侧的私有动作 type -> 设备协议口径。认不出的回落 1（可见光拍照）。
#: 1000 是"可见光拍照 + 后续检测"的复合语义，落到协议里就是拍照。
_ACTION_TYPE_MAP = {
    1000: 1,   # 可见光检测（人员入侵 / 设备外观 / 测温区域）
    7: 1,      # 局部放电（图仍是可见光图，原始 pdd_channel 另存）
    3: 3,      # 录像
}

#: 无图可看的动作类型 —— 分发时不上传图片，直接标 done。
_NO_IMAGE_TYPES = {3}

DEFAULT_FLOOR = 1          # 源数据没有 floor，该站是单层配电室
DEFAULT_DETECT_TYPE = "platform"


def _name_pool(task: InspectionTask) -> list[str]:
    """所有动作的 ``steer_point_name`` 去重 —— 用来给检测点起个像样的标签。

    源数据里 ``thermometry_points`` 只有 id，没有名字；而同一个动作的
    ``steer_point_name`` 就是它对准的那台柜子（如"1D7柜"），拿它当测点名最自然。
    """
    seen: dict[str, None] = {}
    for _, wp in task.waypoints:
        for act in wp.action:
            nm = (act.steer_point_name or "").strip()
            if nm:
                seen.setdefault(nm, None)
    return list(seen)


def _rect_to_boxes(pt: dict) -> list[dict]:
    """``thermometry_param.rect`` -> 检出框列表。

    rect 已经是**归一化**的 ``{x, y, w, h}``（0~1，左上角 + 宽高），正好是
    ``boxes_json`` 约定的形状。reflective / emissivity 这类参数不是框的一部分，
    留在 ``raw_json`` 里即可。

    没有 rect、或 rect 退化成 0 宽/0 高时返回空表 —— 一个"零面积的框"没有意义，
    画到图上是个点，不如不要。
    """
    param = pt.get("thermometry_param") or {}
    rect = param.get("rect") or {}
    try:
        box = {"x": float(rect.get("x") or 0.0), "y": float(rect.get("y") or 0.0),
               "w": float(rect.get("w") or 0.0), "h": float(rect.get("h") or 0.0)}
    except (TypeError, ValueError):
        return []
    if box["w"] <= 0 or box["h"] <= 0:
        return []
    label = pt.get("name") or pt.get("label") or ""
    if label:
        box["label"] = str(label)
    return [box]


def build_task(raw: dict) -> InspectionTask:
    """把单楼层对象包成 ``InspectionTask`` 认的楼层分段。"""
    payload = dict(raw)
    payload.setdefault("floor", DEFAULT_FLOOR)
    payload.setdefault("detectType", DEFAULT_DETECT_TYPE)
    return InspectionTask.from_payload(payload)


def index_source(raw: dict) -> dict[str, dict]:
    """``action_id -> 源动作 dict``。

    ``InspectionAction`` 只建模了 FMS 真正要用的字段（id/type/ptz/测温点…），
    ``snap_shot_url`` / ``pdd_channel`` 这些**机器人侧私有字段没被建模**，
    读不到。所以这里另建一份按 action id 的索引，要什么从原始 dict 取，
    避免为了灌数据去改任务模型（那是协议层的事，不该被脚本牵着走）。
    """
    out: dict[str, dict] = {}
    for wp in raw.get("waypoint") or []:
        for act in (wp.get("action") or []):
            aid = act.get("id")
            if aid:
                out[str(aid)] = act
    return out


def _outcome(i: int, total: int, rng: random.Random) -> tuple[str, int]:
    """给第 ``i`` 个动作定个结果（确定性，靠固定种子）。

    分布刻意做得不像"全绿"：绝大多数成功，少量失败，个别跳过（现场刚好没到那个
    柜位），最后一个动作留 pending 表示"这次巡检还没跑完"——日志页要能同时展示
    这几种状态才有验证价值。
    """
    if i == total - 1:
        return "pending", 0
    if i in (7, 33, 61):
        return "failed", 4          # 设备侧错误码
    if i in (19, 88):
        return "skipped", 0
    if rng.random() < 0.03:
        return "failed", 2
    return "ok", 0


def seed(reset: bool = False, seed_value: int = 20260922) -> dict:
    if not SOURCE.exists():
        raise SystemExit(f"源数据不存在：{SOURCE}")

    raw = json.loads(SOURCE.read_text(encoding="utf-8"))
    task = build_task(raw)
    rng = random.Random(seed_value)

    init_db()
    recorder = InspectionRecorder(SessionLocal)

    # —— 机器人主键：库里只有一台，直接取；没有就留空（robot_pk 允许为空）——
    with SessionLocal() as db:
        robot = db.query(Robot).order_by(Robot.id).first()
        robot_id = str(robot.robot_id) if robot and robot.robot_id is not None else None
        robot_ip = robot.ip if robot else None
        robot_pk = robot.id if robot else None
        robot_name = robot.name if robot else "(未登记机器人)"

        if reset:
            old = db.query(InspectionRun).filter(
                InspectionRun.inspection_id == task.inspection_id).all()
            ids = [r.id for r in old]
            if ids:
                db.query(InspectionPointResult).filter(
                    InspectionPointResult.run_id.in_(ids)).delete(synchronize_session=False)
                db.query(InspectionActionResult).filter(
                    InspectionActionResult.run_id.in_(ids)).delete(synchronize_session=False)
                db.query(InspectionRun).filter(InspectionRun.id.in_(ids)).delete(
                    synchronize_session=False)
                db.commit()
                print(f"[seed] 已清掉旧 run {ids}")

    # —— 1) 占位：run + 动作 + 测点 ——
    run_id = recorder.ensure_placeholders(task, robot_id=robot_id, robot_ip=robot_ip,
                                          detect_type=task.detect_type)
    if run_id is None:
        raise SystemExit("占位失败，请看日志")

    start = datetime.now(UTC).replace(tzinfo=None) - timedelta(days=3, hours=4)
    with SessionLocal() as db:
        run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
        run.start_time = start
        db.commit()

    # —— 2) 回填：逐动作造结果 ——
    src = index_source(raw)
    names = _name_pool(task)
    actions: list[tuple[int, Any, Any, Any]] = []      # (序号, floor, wp, act)
    seq = 0
    for floor, wp in task.waypoints:
        for act in wp.action:
            actions.append((seq, floor, wp, act))
            seq += 1
    total = len(actions)

    stat = {"ok": 0, "failed": 0, "skipped": 0, "pending": 0, "points": 0}
    cursor = start
    for i, (idx, floor, wp, act) in enumerate(actions):
        status, code = _outcome(i, total, rng)
        cursor += timedelta(milliseconds=rng.randint(900, 4200))

        src_type = int(act.type or 0)
        proto_type = _ACTION_TYPE_MAP.get(src_type, 1)
        # ⚠️ 占位行写的是**源口径**的 type（``ensure_placeholders`` 直接搬 act.type），
        # 而 FMS 的字段语义是设备协议口径，所以必须在这里改回来 —— 否则页面上的
        # "类型1000"没人认识，`action_type_name` 也永远空。
        _fix_action_type(run_id, floor, wp.id, act.id, proto_type)

        if status == "pending":
            stat["pending"] += 1
            continue

        raw_act = src.get(str(act.id), {})
        # 录像没有图片，下载的是视频 —— 塞进 media 而不是 picture
        is_video = proto_type in _NO_IMAGE_TYPES
        shot = str(raw_act.get("snap_shot_url") or "")
        picture = "" if is_video else shot
        media = "" if is_video else ""
        if is_video:
            media = (f"data/captures/{task.inspection_id[:8]}/"
                     f"{act.id[:12]}.mp4")

        raw_json = {
            "source_type": src_type,
            "lift_height": act.lift_height,
            "ptz_param": act.ptz_param.model_dump() if act.ptz_param else None,
            "steer_point_name": act.steer_point_name,
            "source": "docs/inspection.json",
        }
        if act.duration:
            raw_json["duration"] = act.duration

        kwargs: dict[str, Any] = {
            "inspection_id": task.inspection_id,
            "floor": floor,
            "waypoint_id": wp.id,
            "action_id": act.id,
            "status": status,
            "code": code,
            "picture": picture,
            "media": media,
            "local_path": (f"data/captures/{task.inspection_id[:8]}/"
                           f"{act.id[:12]}.{'mp4' if is_video else 'jpg'}"),
            "inplace_ts": cursor.isoformat(timespec="seconds"),
            "duration_ms": (int(act.duration) if is_video and act.duration
                            else rng.randint(800, 3800)) if status == "ok" else 0,
            "raw": raw_json,
        }
        # 局部放电：原始通道号存进 pdd_json
        if src_type == 7 and raw_act.get("pdd_channel") is not None:
            kwargs["pdd"] = {"channel": raw_act.get("pdd_channel")}
        # 测温动作的原始测温配置留一份（本轮没有温度值，只有区域配置）
        if act.thermometry_points and status == "ok":
            kwargs["thermometry"] = act.thermometry_points

        recorder.finish_action(**kwargs)
        stat[status] = stat.get(status, 0) + 1

        # 分发状态 —— 动作跑完之后数据要送出去，这一步与动作结果是两件事
        _set_dispatch(run_id, floor, wp.id, act.id, status, proto_type, is_video, rng)

        # 测点回填 —— 一条动作下每个测点一条。**不论动作成败都要回填**：
        # 失败的动作留一条 kind 还是 thermometry 的占位，页面上会显示成
        # "测温点/未执行"，那是错的（源数据里根本没有测温点）。
        if act.thermometry_points:
            _fill_points(task, wp, act, run_id, floor, status, names, rng, picture)
            stat["points"] += len(act.thermometry_points)

    # —— 3) run 收尾 ——
    with SessionLocal() as db:
        run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
        total_rows = (db.query(InspectionActionResult)
                      .filter(InspectionActionResult.run_id == run_id).count())
        done = (db.query(InspectionActionResult)
                .filter(InspectionActionResult.run_id == run_id,
                        InspectionActionResult.status.in_(("ok", "failed", "skipped")))
                .count())
        # 刻意留最后一个动作 pending —— 让日志页能同时展示"进行中"与"已完成"
        run.finish_time = cursor if done >= total_rows else None
        run.status = "done" if done >= total_rows else "started"
        db.commit()

    return {
        "run_id": run_id, "robot": robot_name, "robot_pk": robot_pk,
        "inspection_id": task.inspection_id, "name": task.name,
        "action_count": task.action_count, "point_count": stat["points"],
        "stat": stat, "start": start.isoformat(timespec="seconds"),
        "finish": cursor.isoformat(timespec="seconds"),
    }


def _find_action(db, run_id: int, floor: int, waypoint_id: str, action_id: str):
    return (db.query(InspectionActionResult)
            .filter(InspectionActionResult.run_id == run_id,
                    InspectionActionResult.floor == floor,
                    InspectionActionResult.waypoint_id == waypoint_id,
                    InspectionActionResult.action_id == action_id)
            .order_by(InspectionActionResult.id.desc()).first())


def _fix_action_type(run_id: int, floor: int, waypoint_id: str, action_id: str,
                     proto_type: int) -> None:
    """把占位行里的**源口径** type 改成设备协议口径（1 拍照 / 2 测温 / 3 录像）。

    ``ensure_placeholders`` 是照搬任务里的 ``act.type`` 写的，源数据的 1000/7/3
    在 FMS 的语义里不成立；协议口径是展示与下游判断的依据，必须纠正。
    """
    with SessionLocal() as db:
        row = _find_action(db, run_id, floor, waypoint_id, action_id)
        if row is not None and row.action_type != proto_type:
            row.action_type = proto_type
            db.commit()


def _set_dispatch(run_id: int, floor: int, waypoint_id: str, action_id: str,
                  status: str, proto_type: int, is_video: bool,
                  rng: random.Random) -> None:
    """模拟任务执行器的分发结果。

    真跑起来这一步由 ``nodes/task_executor.py`` 干：``pendings`` 里捞未分发的行，
    按 ``detect_type`` 决定上传平台还是本地检测，成/败写 ``dispatch_status``。
    造假数据时把三种结局都造出来，页面上的"分发"一栏才有东西验：

    - 动作没跑完（pending）：没东西可发，留 ``pending``；
    - 动作失败：没图，标 ``failed`` 并把原因写进 ``dispatch_error``；
    - 动作成功：98% 送出去（``done``），少数标 ``failed`` 模拟平台侧 5xx。
    """
    with SessionLocal() as db:
        row = _find_action(db, run_id, floor, waypoint_id, action_id)
        if row is None:
            return
        row.dispatch_mode = "upload"          # 本次是 platform 口径，统一走上传
        if status == "pending":
            return                            # 留 pending，不写 attempts
        if status in ("failed", "skipped"):
            row.dispatch_status = "failed"
            row.dispatch_attempts = 1
            row.dispatch_error = "动作无有效数据，未分发"
            db.commit()
            return
        row.dispatch_attempts = 1
        if rng.random() < 0.98:
            row.dispatch_status = "done"
            row.dispatched_at = datetime.now(UTC).replace(tzinfo=None)
        else:
            row.dispatch_status = "failed"
            row.dispatch_attempts = 2
            row.dispatch_error = "平台接口 503 Service Unavailable"
        db.commit()


def _fill_points(task, wp, act, run_id, floor, action_status, names, rng,
                 picture: str = "") -> None:
    """按 ``thermometry_points`` 回填测点行（kind=detect，带检出框）。

    **不论动作成败都要调用**：占位行建的时候 ``kind`` 用的是默认值 ``thermometry``，
    不纠正就会在页面上显示成"测温点 / 未执行"——但源数据里这些压根不是测温点，
    而是归一化的检测区域。动作失败时把测点也标 failed，别留个假的"待测温"。
    """
    with SessionLocal() as db:
        arow = _find_action(db, run_id, floor, wp.id, act.id)
        if arow is None:
            return
        for seq, pt in enumerate(act.thermometry_points):
            if not isinstance(pt, dict):
                continue
            row = (db.query(InspectionPointResult)
                   .filter(InspectionPointResult.action_result_id == arow.id,
                           InspectionPointResult.point_id == str(pt.get("id") or ""))
                   .first())
            if row is None:
                continue
            # 有区域配置、但没有独立算法流程 —— 这条动作本身走的是"上传平台"口径，
            # 检测由平台侧做，本地只留区域配置与一个占位结论。
            # 标签优先用动作自己的 ``steer_point_name``（它对准的那台柜子）；
            # 源数据里每个动作基本只有 1 个测点，用序号取全局名字池只会全落第一个。
            label = (act.steer_point_name or "").strip()
            if not label and names:
                label = names[seq % len(names)]
            row.kind = "detect"
            row.unit = ""
            row.image = picture
            row.algorithm = "上传平台检测"
            row.label = label
            row.boxes_json = _rect_to_boxes(pt)
            row.raw_json = pt
            if action_status == "ok":
                ok = rng.random() < 0.88
                row.status = "ok"
                row.passed = ok
                row.confidence = round(rng.uniform(0.62, 0.98), 4)
                row.detect_json = {"source": "docs/inspection.json",
                                   "conclusion": "正常" if ok else "异常"}
            else:
                row.status = "failed"
                row.detect_json = {"source": "docs/inspection.json",
                                   "error": "动作执行失败，未取到图"}
            db.commit()


def main() -> None:
    ap = argparse.ArgumentParser(description="用 docs/inspection.json 灌巡检日志样例数据")
    ap.add_argument("--reset", action="store_true", help="先删掉同 inspection_id 的旧记录")
    args = ap.parse_args()

    result = seed(reset=args.reset)
    print(json.dumps(result, ensure_ascii=False, indent=2))
    print("\n[seed] 完成。验证：")
    print("  curl --noproxy '*' http://127.0.0.1:8000/api/inspection/runs?page=1")
    print(f"  curl --noproxy '*' http://127.0.0.1:8000/api/inspection/runs/{result['run_id']}/actions")
    print(f"  curl --noproxy '*' http://127.0.0.1:8000/api/inspection/runs/{result['run_id']}/points")


if __name__ == "__main__":
    main()
