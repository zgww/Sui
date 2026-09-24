"""巡检结果的落库器：把 rail 状态机跑出来的动作数据写进 SQLite。

## 为什么要先占位

巡检**开始时**（状态机 "start" 那一拍）就按任务结构把整批行插好
（``status='pending'``），动作执行完再回填。这样：

- 下游（检测识别 / 上报平台）只要轮询 ``status='pending'`` 的行，不用去猜执行器
  现在跑到哪、也不用等巡检整次跑完才拿得到数据；
- 执行器崩了、机器人断电，占位行留在那里没回填，一眼看出卡在第几个动作；
- 巡检任务结构（有多少动作）在开始那一刻就固定了，不受后续执行成败影响。

## 为什么全部吞异常

落库是给**下游**用的，不是巡检的前置条件。库不可用、表没建、字段冲突——
都只告警不抛出：巡检该跑完还得跑完，图已经落到盘上了，数据不会真丢。
真要查问题看日志，不要让状态机在"执行动作"里炸掉。

## 线程

由 Robot 的状态机线程直接调用（同步 SQLAlchemy）。SQLite 连接建库时已带
``check_same_thread=False``；每个方法自己开 session、用完必关，不跨调用持有。
"""
from __future__ import annotations

import logging
from datetime import datetime
from typing import Any, Optional

from ..database import SessionLocal
from ..models import (
    InspectionActionResult,
    InspectionPointResult,
    InspectionRun,
    Robot,
)

logger = logging.getLogger("rail.recorder")

STATUS_PENDING = "pending"
STATUS_OK = "ok"
STATUS_FAILED = "failed"
STATUS_SKIPPED = "skipped"

DEFAULT_DETECT_TYPE = "platform"
DEFAULT_EXECUTOR = "fms"


def _now() -> datetime:
    return datetime.utcnow()


def _robot_pk(db, robot_id: Optional[str], robot_ip: Optional[str]) -> Optional[int]:
    """业务 robot_id / ip -> ``robots.id``。

    prefab 里配的 ``robot_id`` 是字符串（如 ``R001``），库里 ``robots.robot_id``
    是整数，两边对不上的情况很常见；再按 ip 兜一次。都查不到返回 ``None``——
    ``robot_pk`` 允许为空，不该因为"这台机器没在库里登记"就不记巡检结果。
    """
    try:
        if robot_id:
            try:
                rid = int(str(robot_id))
            except (TypeError, ValueError):
                rid = None
            if rid is not None:
                row = db.query(Robot).filter(Robot.robot_id == rid).first()
                if row:
                    return row.id
        if robot_ip:
            row = db.query(Robot).filter(Robot.ip == str(robot_ip)).first()
            if row:
                return row.id
    except Exception:
        logger.exception("[recorder] 查询机器人主键失败，按未登记处理")
    return None


class InspectionRecorder:
    """巡检结果落库。方法全部幂等、全部吞异常。

    ``session_factory`` 可注入（默认全局 ``SessionLocal``）——测试用它指向临时库，
    生产不用传。
    """

    def __init__(self, session_factory=None) -> None:
        self._session_factory = session_factory or SessionLocal

    # ---------------------------------------------------------------- 占位
    def ensure_placeholders(self, task, *, robot_id: Optional[str] = None,
                            robot_ip: Optional[str] = None,
                            detect_type: str = DEFAULT_DETECT_TYPE) -> Optional[int]:
        """巡检开始时调用：确保 run + 每个动作/测温点各有一条占位。

        **已生成过就跳过**（续跑、重复下发同一 id 都会走到这里）。返回 ``run_id``，
        失败返回 ``None``——调用方不要拿返回值做流程判断，落库失败不影响巡检。
        """
        try:
            db = self._session_factory()
        except Exception:
            logger.exception("[recorder] 无法建立数据库会话，跳过占位")
            return None
        try:
            run = self._ensure_run(db, task, robot_id, robot_ip)
            self._ensure_actions(db, task, run, detect_type)
            db.commit()
            logger.info("[recorder] 巡检 %s 占位就绪（run=%s，动作%d，测点%d）",
                        task.inspection_id, run.id, task.action_count,
                        self._point_count(db, run.id))
            return run.id
        except Exception:
            db.rollback()
            logger.exception("[recorder] 巡检 %s 占位失败（不影响巡检继续）",
                             getattr(task, "inspection_id", "?"))
            return None
        finally:
            db.close()

    def _ensure_run(self, db, task, robot_id, robot_ip) -> InspectionRun:
        run = db.query(InspectionRun).filter(
            InspectionRun.inspection_id == task.inspection_id).first()
        if run is not None:
            # 续跑：状态回到 started（上次可能是中止），robot_pk 缺了补上
            if run.status != "started":
                run.status = "started"
            if run.robot_pk is None:
                run.robot_pk = _robot_pk(db, robot_id, robot_ip)
            return run
        run = InspectionRun(
            inspection_id=task.inspection_id,
            robot_pk=_robot_pk(db, robot_id, robot_ip),
            status="started",
            start_time=_now(),
            remark=f"{task.name} · {len(task.floors)}层",
        )
        db.add(run)
        db.flush()   # 要 id 给动作行用
        return run

    def _ensure_actions(self, db, task, run, detect_type) -> None:
        """按任务结构插动作占位与测点占位；已存在的 (floor, 航点, 动作) 跳过。"""
        existing = {
            (r.floor, r.waypoint_id, r.action_id)
            for r in db.query(
                InspectionActionResult.floor,
                InspectionActionResult.waypoint_id,
                InspectionActionResult.action_id,
            ).filter(InspectionActionResult.run_id == run.id).all()
        }
        added_actions = 0
        added_points = 0
        for floor, wp in task.waypoints:
            for seq, act in enumerate(wp.action):
                key = (floor, wp.id, act.id)
                if key in existing:
                    continue
                row = InspectionActionResult(
                    run_id=run.id, robot_pk=run.robot_pk,
                    inspection_id=task.inspection_id,
                    floor=floor, waypoint_id=wp.id,
                    waypoint_index=int(wp.index or 0),
                    action_id=act.id, action_seq=seq,
                    action_type=int(act.type or 0),
                    attempt=1,
                    executor=DEFAULT_EXECUTOR,
                    detect_type=detect_type,
                    reference_image=getattr(act, "reference_image", "") or "",
                    status=STATUS_PENDING,
                    start_time=_now(),
                )
                db.add(row)
                db.flush()
                added_actions += 1
                added_points += self._add_points(db, run, row, task, floor, wp, act)
        logger.debug("[recorder] 新增动作占位 %d、测点占位 %d", added_actions, added_points)

    def _add_points(self, db, run, action_row, task, floor, wp, act) -> int:
        """测温点 + 检测框逐个插测点占位。

        - ``thermometry_points``：测温点（kind='thermometry'）
        - ``detect_boxes``：检测框（kind='detect'），巡检开始时就把占位插好
        """
        n = 0
        seq = 0

        # 测温点
        pts = getattr(act, "thermometry_points", None) or []
        for pt in pts:
            if not isinstance(pt, dict):
                continue
            db.add(InspectionPointResult(
                action_result_id=action_row.id,
                run_id=run.id, robot_pk=run.robot_pk,
                inspection_id=task.inspection_id,
                floor=floor, waypoint_id=wp.id, action_id=act.id,
                point_id=str(pt.get("id") or ""),
                seq=seq, kind="thermometry",
                status=STATUS_PENDING,
                raw_json=pt,          # 测点配置（rect/发射率/距离…）先留一份
            ))
            n += 1
            seq += 1

        # 检测框
        boxes = getattr(act, "detect_boxes", None) or []
        for box in boxes:
            if not isinstance(box, dict):
                continue
            # box_id 是检测框自己的身份（编排处生成），point_id 是顺手绑的测点档案 id。
            # 两者都留着：老任务里可能只有 point_id（那时 to_inspection_json 拿它顶 id），
            # 所以这里再退一步用 `id` 兜底，保证占位行一定有东西可对。
            box_id = str(box.get("box_id") or box.get("id") or "")
            box_pid = str(box.get("point_id") or "")
            db.add(InspectionPointResult(
                action_result_id=action_row.id,
                run_id=run.id, robot_pk=run.robot_pk,
                inspection_id=task.inspection_id,
                floor=floor, waypoint_id=wp.id, action_id=act.id,
                point_id=box_pid,
                box_id=box_id,
                box_name=str(box.get("box_name") or box.get("point_name") or ""),
                seq=seq, kind="detect",
                status=STATUS_PENDING,
                detect_flow=str(box.get("detect_flow") or ""),
                label=str(box.get("point_name") or ""),
                raw_json=box,         # 检测框配置（rect/流程引用…）先留一份
            ))
            n += 1
            seq += 1

        return n

    def _point_count(self, db, run_id: int) -> int:
        return db.query(InspectionPointResult).filter(
            InspectionPointResult.run_id == run_id).count()

    # ---------------------------------------------------------------- 回填
    def finish_action(self, *, inspection_id: str, floor: Optional[int],
                      waypoint_id: str, action_id: str,
                      status: str, picture: str = "", infrared: str = "",
                      media: str = "", local_path: str = "",
                      thermometry: Any = None, env: Any = None, pdd: Any = None,
                      raw: Any = None, duration_ms: int = 0,
                      inplace_ts: str = "", code: int = 0,
                      point_values: Optional[dict] = None) -> bool:
        """动作执行完回填一行；只填非空字段，不把已有的好数据抹成空。

        找不到对应占位行（老任务、占位被清）返回 False 并告警——不新建行：
        没有占位说明这次巡检的账本对不上，宁可留个告警让人查，也别凭空造数据。
        """
        try:
            db = self._session_factory()
        except Exception:
            logger.exception("[recorder] 无法建立数据库会话，跳过回填")
            return False
        try:
            q = db.query(InspectionActionResult).filter(
                InspectionActionResult.inspection_id == inspection_id,
                InspectionActionResult.waypoint_id == waypoint_id,
                InspectionActionResult.action_id == action_id,
            )
            if floor is not None:
                q = q.filter(InspectionActionResult.floor == floor)
            row = q.order_by(InspectionActionResult.id.desc()).first()
            if row is None:
                logger.warning("[recorder] 动作结果无占位可回填：%s/%s/%s",
                               inspection_id, waypoint_id, action_id)
                return False
            row.status = status
            row.code = code
            row.finish_time = _now()
            row.duration_ms = int(duration_ms or 0)
            if picture:
                row.picture = picture
            if infrared:
                row.infrared = infrared
            if media:
                row.media = media
            if local_path:
                row.local_path = local_path
            if inplace_ts:
                row.inplace_ts = inplace_ts
            if thermometry is not None:
                row.thermometry_json = thermometry
            if env is not None:
                row.env_json = env
            if pdd is not None:
                row.pdd_json = pdd
            if raw is not None:
                row.raw_json = raw
            if point_values:
                self._fill_points(db, row.id, point_values)
            db.commit()
            return True
        except Exception:
            db.rollback()
            logger.exception("[recorder] 动作结果回填失败：%s/%s/%s",
                             inspection_id, waypoint_id, action_id)
            return False
        finally:
            db.close()

    def _fill_points(self, db, action_result_id: int, values: dict) -> None:
        """按 point_id 回填测温值。温度能力接入后由调用方传进来。"""
        for row in db.query(InspectionPointResult).filter(
                InspectionPointResult.action_result_id == action_result_id).all():
            v = values.get(row.point_id)
            if v is None:
                continue
            try:
                row.value = float(v)
                row.status = STATUS_OK
            except (TypeError, ValueError):
                logger.warning("[recorder] 测点 %s 温度值非法：%r", row.point_id, v)
