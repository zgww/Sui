"""At-most-once dispatch with durable robot leases and auditable uncertain outcomes."""
import logging
import uuid
from datetime import datetime, timedelta
from fastapi import HTTPException
from sqlalchemy.exc import IntegrityError
from ..models import (InspectionPlan, PlanExecution, InspectionRobotLease, InspectionTask,
                      InspectionRun, ArchiveTaskPoint, Robot)
from .inspection_compile import compile_route
from .inspection_protocol import immediate_payload
from .inspection_plans import get_plan
from .inspection_schedule import next_occurrence
from . import robot_api

logger = logging.getLogger(__name__)
TERMINAL = {'done', 'canceled', 'failed', 'skipped', 'closed'}
STATUS = {-1: 'canceled', 0: 'running', 1: 'done', 2: 'paused', 3: 'running', 4: 'suspended'}


def execution_out(e):
    result = {k: getattr(e, k) for k in ('id', 'plan_id', 'robot_pk', 'task_id', 'trigger', 'scheduled_at', 'status', 'message', 'created_at', 'finished_at')}
    result['stage_index'] = e.stage_index or 0
    result['stages'] = [{k: stage.get(k) for k in ('map_pk', 'map_name', 'floor', 'point_ids')} for stage in (e.route or [])]
    return result


def report_execution(db, inspection_id):
    e = db.get(PlanExecution, inspection_id)
    if e:
        return e
    root, separator, number = inspection_id.rpartition('-s')
    if separator and number.isdigit():
        e = db.get(PlanExecution, root)
        if e and any(stage['content']['id'] == inspection_id for stage in (e.route or [])):
            return e
    return None


def active_id(e):
    return e.content['id'] if e.content else e.id


def release(db, e):
    db.query(InspectionRobotLease).filter_by(execution_id=e.id).delete()


def dispatch(db, store, plan_id, robot_pk, request_key, trigger='manual', scheduled_at=None, expected_version=None):
    with store.lock:
        existing = db.query(PlanExecution).filter_by(plan_id=plan_id, request_key=request_key).first()
        if existing:
            if existing.robot_pk != robot_pk:
                raise HTTPException(404, '执行记录不存在')
            return execution_out(existing)
        p = get_plan(db, plan_id, robot_pk)
        if not p.enabled:
            raise HTTPException(409, '计划已停用')
        if expected_version is not None and p.version != expected_version:
            raise HTTPException(409, '计划已修改，请重新预览')
        now = datetime.utcnow()
        e = PlanExecution(id='fms-' + uuid.uuid4().hex, plan_id=p.id, robot_pk=robot_pk,
                          request_key=request_key, trigger=trigger, scheduled_at=scheduled_at, status='dispatching')
        robot = db.get(Robot, robot_pk)
        try:
            if not robot or not robot.enabled:
                raise HTTPException(422, '机器人不存在或已停用')
            if db.get(InspectionRobotLease, robot_pk):
                raise HTTPException(409, '机器人有运行中或结果待确认的巡检，请先查看执行历史')
            route, bindings = compile_route(db, store, robot_pk, p.stages or [{'map_pk': p.map_pk, 'point_ids': p.point_ids}], e.id, p.name)
            content = route[0]['content']
            e.route, e.stage_index = route, 0
            snapshot = store.capture(p.point_ids)
            snapshot['bindings'] = bindings
            task = InspectionTask(robot_pk=robot_pk, name=p.name, plan_json=content,
                                  archive_snapshot=snapshot, status='dispatching')
            db.add(task); db.flush()
            e.task_id, e.content = task.id, content
            db.add_all([ArchiveTaskPoint(task_id=task.id, point_id=pid) for pid in p.point_ids])
            db.add(e); db.flush()
            db.add(InspectionRobotLease(robot_pk=robot_pk, execution_id=e.id))
            db.add(InspectionRun(task_id=task.id, robot_pk=robot_pk, inspection_id=e.id, status='dispatching'))
            db.commit()
        except HTTPException as exc:
            db.rollback()
            if trigger == 'manual':
                raise
            e.status, e.message, e.finished_at = 'skipped', str(exc.detail), now
            db.add(e); db.commit()
            return execution_out(e)
        except IntegrityError:
            db.rollback()
            existing = db.query(PlanExecution).filter_by(plan_id=plan_id, request_key=request_key).first()
            if existing:
                return execution_out(existing)
            raise HTTPException(409, '机器人正在接收其他巡检，请刷新')
        return_id = e.id
    return send_stage(db, store, return_id)


def send_stage(db, store, execution_id):
    e = db.get(PlanExecution, execution_id)
    robot = db.get(Robot, e.robot_pk)
    robot_pk, stage_index = e.robot_pk, e.stage_index or 0
    endpoint = (robot.ip, robot.api_port, robot.robot_id)
    content = e.content
    # Read current robot state first; a stale/offline device is never treated as idle.
    sent = False
    try:
        payload = immediate_payload(content)
        code, msg, info = robot_api.call(*endpoint, 102, {})
        if code != 0 or not isinstance(info, dict):
            raise RuntimeError('无法确认机器人巡检状态：' + str(msg))
        if info.get('inspection_id') and info.get('status') not in (-1, 1):
            raise RuntimeError('机器人已有未结束的巡检任务')
        sent = True
        code, msg, _ = robot_api.call(*endpoint, 100, payload)
        result_status = 'accepted' if code == 0 else 'failed'
        result_message = (str(msg) or '机器人已接受任务') if code == 0 else f'机器人拒绝任务（code={code}）：{msg}'
    except Exception as exc:
        result_status = 'unknown' if sent else 'failed'
        result_message = ('下发结果未知，不自动重发：' if sent else '未下发：') + str(exc)
    with store.lock:
        db.expire_all()
        e = db.get(PlanExecution, e.id)
        # A report can arrive before the HTTP response; never regress its state.
        if e.status == 'dispatching' and (e.stage_index or 0) == stage_index:
            e.status, e.message = result_status, result_message
            task = db.get(InspectionTask, e.task_id)
            task.status = result_status
            run = db.query(InspectionRun).filter_by(inspection_id=content['id'], robot_pk=robot_pk).first()
            if run:
                run.status = result_status
            if result_status == 'failed':
                e.finished_at = datetime.utcnow(); release(db, e)
            db.commit()
        return execution_out(e)


def apply_report(db, execution_id, robot_pk, status, remark=''):
    e = report_execution(db, execution_id)
    if not e:
        return
    if robot_pk != e.robot_pk:
        raise HTTPException(403, '上报机器人与巡检记录不一致')
    state = STATUS.get(status)
    if state is None or e.status in TERMINAL or execution_id != active_id(e) or e.status == 'waiting_transition':
        return
    run = db.query(InspectionRun).filter_by(inspection_id=execution_id, robot_pk=robot_pk).first()
    if run:
        run.status = state
    if state == 'done' and (e.stage_index or 0) + 1 < len(e.route or []):
        state = 'waiting_transition'
        remark = '本段已完成，请确认到达下一段地图/楼层后继续'
    e.status, e.message = state, remark or '机器人状态上报'
    task = db.get(InspectionTask, e.task_id)
    if task:
        task.status = state
    if state in TERMINAL:
        e.finished_at = datetime.utcnow(); release(db, e)


def reconcile(db, store, execution_id, robot_pk, close_idle=False):
    e = db.get(PlanExecution, execution_id)
    if not e or e.robot_pk != robot_pk:
        raise HTTPException(404, '执行记录不存在')
    if e.status in TERMINAL:
        return execution_out(e)
    robot = db.get(Robot, robot_pk)
    if not robot:
        raise HTTPException(404, '机器人不存在')
    queried_stage = active_id(e)
    try:
        code, msg, info = robot_api.call(robot.ip, robot.api_port, robot.robot_id, 102, {})
    except Exception as exc:
        raise HTTPException(502, '机器人状态查询失败：' + str(exc))
    if code != 0 or not isinstance(info, dict):
        raise HTTPException(502, '机器人状态查询失败：' + str(msg))
    with store.lock:
        db.expire_all(); e = db.get(PlanExecution, execution_id)
        if e.status in TERMINAL or active_id(e) != queried_stage:
            return execution_out(e)
        if close_idle and e.status == 'waiting_transition' and (not info.get('inspection_id') or info.get('status') in (-1, 1)):
            e.status, e.message, e.finished_at = 'closed', '人工结束剩余巡检分段', datetime.utcnow()
            release(db, e)
            db.get(InspectionTask, e.task_id).status = 'closed'
        elif info.get('inspection_id') == active_id(e):
            apply_report(db, active_id(e), robot_pk, info.get('status'), info.get('remark', ''))
        elif close_idle and (not info.get('inspection_id') or info.get('status') in (-1, 1)):
            e.status, e.message, e.finished_at = 'closed', '人工确认机器人空闲，关闭本地占用；不代表巡检完成', datetime.utcnow()
            release(db, e)
            task = db.get(InspectionTask, e.task_id)
            if task:
                task.status = 'closed'
        else:
            if e.status == 'dispatching' and e.created_at < datetime.utcnow() - timedelta(seconds=30):
                e.status = 'unknown'
            e.message = '机器人当前记录与本次执行不一致；未重发，请核对现场状态'
        db.commit()
        return execution_out(e)


def tick_plans():
    from ..database import SessionLocal
    from ..point_archive.runtime import archive_store
    with SessionLocal() as db:
        now = datetime.utcnow()
        due_ids = [p.id for p in db.query(InspectionPlan).filter(InspectionPlan.enabled.is_(True), InspectionPlan.deleted.is_(False),
                   InspectionPlan.next_run_at <= now).order_by(InspectionPlan.next_run_at).limit(100)]
        for pid in due_ids:
            try:
                with archive_store.lock:
                    db.expire_all(); p = db.get(InspectionPlan, pid)
                    due = p.next_run_at
                    if not p.enabled or p.deleted or due is None or due > now:
                        continue
                    version, rid = p.version, p.robot_pk
                    key = f'schedule:{version}:{due.isoformat()}'
                    # Dispatch commits the claim before advancing the cursor. A restart
                    # sees the same unique request key, so it cannot send twice.
                    if now - due > timedelta(minutes=5):
                        exists = db.query(PlanExecution).filter_by(plan_id=pid, request_key=key).first()
                        if not exists:
                            db.add(PlanExecution(id='fms-' + uuid.uuid4().hex, plan_id=pid, robot_pk=rid,
                                request_key=key, trigger='schedule', scheduled_at=due, status='skipped',
                                message='超过 5 分钟容错窗口，跳过停机期间的排期', finished_at=now))
                            db.commit()
                        skipped = True
                    else:
                        skipped = False
                if not skipped:
                    dispatch(db, archive_store, pid, rid, key, 'schedule', due, version)
                with archive_store.lock:
                    db.expire_all(); p = db.get(InspectionPlan, pid)
                    if p.version == version and p.next_run_at == due:
                        p.next_run_at = next_occurrence(p.schedule, now)
                        db.commit()
            except Exception:
                db.rollback(); logger.exception('inspection plan tick failed: %s', pid)


def tick_execution_status():
    """Recover status after missed callbacks; a mismatched ID is never resent."""
    from ..database import SessionLocal
    from ..point_archive.runtime import archive_store
    with SessionLocal() as db:
        rows = db.query(PlanExecution).join(InspectionRobotLease, InspectionRobotLease.execution_id == PlanExecution.id).filter(
            PlanExecution.created_at < datetime.utcnow() - timedelta(seconds=30)).limit(100).all()
        for e in rows:
            try:
                if e.status == 'waiting_transition':
                    continue
                reconcile(db, archive_store, e.id, e.robot_pk)
            except Exception:
                db.rollback()
                logger.warning('Could not reconcile inspection execution %s', e.id)


def continue_execution(db, store, execution_id, robot_pk, stage_index, confirmed=False):
    if not confirmed:
        raise HTTPException(422, '请先确认机器人已到达目标地图/楼层并完成定位')
    with store.lock:
        db.expire_all()
        e = db.get(PlanExecution, execution_id)
        if not e or e.robot_pk != robot_pk:
            raise HTTPException(404, '执行记录不存在')
        if (e.stage_index or 0) > stage_index:
            return execution_out(e)  # Duplicate confirmation never sends again.
        if e.status != 'waiting_transition' or (e.stage_index or 0) != stage_index:
            raise HTTPException(409, '执行阶段已变化，请刷新历史')
        next_index = stage_index + 1
        if next_index >= len(e.route or []):
            raise HTTPException(409, '没有后续分段')
        changed = db.query(PlanExecution).filter_by(id=e.id, status='waiting_transition', stage_index=stage_index).update(
            {'stage_index': next_index, 'status': 'dispatching', 'message': '已确认到达，正在下发下一段', 'content': e.route[next_index]['content']}, synchronize_session=False)
        if not changed:
            db.rollback()
            raise HTTPException(409, '执行阶段已变化，请刷新历史')
        db.expire_all(); e = db.get(PlanExecution, execution_id)
        task = db.get(InspectionTask, e.task_id)
        task.plan_json, task.status = e.content, 'dispatching'
        db.add(InspectionRun(task_id=e.task_id, robot_pk=robot_pk, inspection_id=active_id(e), status='dispatching'))
        db.commit()  # Durable stage claim before external I/O; crash never re-sends.
    return send_stage(db, store, execution_id)
