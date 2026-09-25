"""Robot-scoped plan configuration, occurrence preview and audited execution."""
from datetime import datetime, timedelta
from fastapi import APIRouter, Depends, HTTPException, Query
from pydantic import BaseModel, Field
from sqlalchemy.orm import Session
from ..auth import engineer_only
from ..database import get_db
from ..models import InspectionPlan, PlanExecution
from ..models import PointBinding, Waypoint, RobotMap
from sqlalchemy import func
from ..point_archive.runtime import get_archive_store
from ..services.inspection_plans import PlanInput, save_plan, delete_plan, plan_out, get_plan
from ..services.inspection_schedule import next_occurrence
from ..services.inspection_dispatch import dispatch, execution_out, reconcile

router = APIRouter(prefix='/api/inspection-plans', tags=['inspection-plans'], dependencies=[Depends(engineer_only)])


@router.get('/options/points')
def eligible_points(robot_pk: int, map_pk: int, floor: int | None = None, name: str = '', page: int = Query(1, ge=1),
                    directory_id: str | None = None, db: Session = Depends(get_db), store=Depends(get_archive_store)):
    query = db.query(PointBinding.point_id).join(Waypoint, PointBinding.waypoint_pk == Waypoint.id).join(RobotMap, Waypoint.map_pk == RobotMap.id).filter(
        Waypoint.robot_pk == robot_pk, Waypoint.map_pk == map_pk, RobotMap.robot_pk == robot_pk)
    if floor is not None:
        query = query.filter(func.coalesce(Waypoint.floor, RobotMap.floor, 0) == floor)
    ids = query.distinct().all()
    points = [store.get(pid) for pid, in ids]
    points = [p for p in points if p and p.get('active', True) and (not name or name.lower() in (p['name'] + p['id'] + p.get('code', '')).lower())]
    if directory_id:
        doc, directories, children, _ = store.catalog_data()
        if directory_id not in directories:
            raise HTTPException(422, '目录不存在，请刷新')
        descendants, pending = {directory_id}, [directory_id]
        while pending:
            child_ids = children[pending.pop()]
            descendants.update(child_ids); pending.extend(child_ids)
        directory_points = {p['id'] for p in doc['points'] if p.get('directory_id') in descendants}
        points = [p for p in points if p['id'] in directory_points]
    points.sort(key=lambda p: p['id'])
    return {'total': len(points), 'items': points[(page-1)*20:page*20]}


@router.get('/options/floors')
def available_floors(robot_pk: int, db: Session = Depends(get_db)):
    rows = db.query(RobotMap.id, RobotMap.name, func.coalesce(Waypoint.floor, RobotMap.floor, 0)).outerjoin(
        Waypoint, (Waypoint.map_pk == RobotMap.id) & (Waypoint.robot_pk == robot_pk)).filter(RobotMap.robot_pk == robot_pk).distinct().all()
    return {'items': [{'map_pk': mid, 'map_name': name, 'floor': floor} for mid, name, floor in sorted(rows, key=lambda r: (r[0], r[2]))]}


@router.get('')
def plans(robot_pk: int, name: str = '', page: int = Query(1, ge=1), page_size: int = Query(20, ge=1, le=100), db: Session = Depends(get_db)):
    q = db.query(InspectionPlan).filter(InspectionPlan.robot_pk == robot_pk, InspectionPlan.deleted.is_(False))
    if name:
        q = q.filter(InspectionPlan.name.contains(name, autoescape=True))
    return {'total': q.count(), 'items': [plan_out(p) for p in q.order_by(InspectionPlan.id.desc()).offset((page-1)*page_size).limit(page_size)]}


@router.post('')
def create(body: PlanInput, db: Session = Depends(get_db), store=Depends(get_archive_store)):
    return save_plan(db, store, body)


@router.put('/{plan_id}')
def update(plan_id: int, body: PlanInput, db: Session = Depends(get_db), store=Depends(get_archive_store)):
    return save_plan(db, store, body, plan_id)


@router.delete('/{plan_id}')
def remove(plan_id: int, robot_pk: int, version: int, db: Session = Depends(get_db), store=Depends(get_archive_store)):
    return delete_plan(db, store, plan_id, robot_pk, version)


class ExecuteInput(BaseModel):
    robot_pk: int
    version: int
    request_key: str = Field(min_length=8, max_length=100, pattern=r'^[a-zA-Z0-9_-]+$')


@router.get('/{plan_id}/preview')
def preview_plan(plan_id: int, robot_pk: int, db: Session = Depends(get_db), store=Depends(get_archive_store)):
    from ..services.inspection_compile import compile_route
    with store.lock:
        p = get_plan(db, plan_id, robot_pk)
        route, bindings = compile_route(db, store, robot_pk, p.stages or [{'map_pk': p.map_pk, 'point_ids': p.point_ids}], 'preview', p.name)
        waypoint_ids = {b['waypoint_pk'] for b in bindings}
        external_ids = {w.id: w.wp_id or str(w.id) for w in db.query(Waypoint).filter(Waypoint.id.in_(waypoint_ids)).all()}
        bound = {}
        for binding in bindings:
            bound.setdefault((binding['stage_index'], external_ids[binding['waypoint_pk']]), set()).add(binding['point_id'])
        return {'version': p.version, 'point_count': len(p.point_ids), 'stages': [
            {'map_pk': stage['map_pk'], 'map_name': stage['map_name'], 'floor': stage['floor'],
             'point_count': len(stage['point_ids']), 'waypoint_count': len(stage['content']['waypoint']),
             'action_count': sum(len(w['action']) for w in stage['content']['waypoint']),
             'waypoints': [{'id': w['id'], 'actions': w['action'],
                            'point_ids': sorted(bound.get((index, w['id']), set()))}
                           for w in stage['content']['waypoint']]}
            for index, stage in enumerate(route)]}


@router.post('/{plan_id}/execute')
def execute(plan_id: int, body: ExecuteInput, db: Session = Depends(get_db), store=Depends(get_archive_store)):
    return dispatch(db, store, plan_id, body.robot_pk, 'manual:' + body.request_key, expected_version=body.version)


@router.get('/{plan_id}/history')
def history(plan_id: int, robot_pk: int, page: int = Query(1, ge=1), db: Session = Depends(get_db)):
    get_plan(db, plan_id, robot_pk)
    q = db.query(PlanExecution).filter_by(plan_id=plan_id, robot_pk=robot_pk)
    return {'total': q.count(), 'items': [execution_out(e) for e in q.order_by(PlanExecution.created_at.desc()).offset((page-1)*20).limit(20)]}


@router.get('/calendar/occurrences')
def calendar(robot_pk: int, start: datetime, end: datetime, db: Session = Depends(get_db)):
    from datetime import timezone
    start = start.astimezone(timezone.utc).replace(tzinfo=None) if start.tzinfo else start
    end = end.astimezone(timezone.utc).replace(tzinfo=None) if end.tzinfo else end
    if end <= start or end-start > timedelta(days=62):
        raise HTTPException(422, '日历范围须在 1–62 天内')
    plans = db.query(InspectionPlan).filter_by(robot_pk=robot_pk, enabled=True, deleted=False).all()
    items = []
    for p in plans:
        occurrence = next_occurrence(p.schedule, start-timedelta(microseconds=1))
        while occurrence and occurrence < end:
            items.append({'plan_id': p.id, 'name': p.name, 'at': occurrence})
            if len(items) > 10000:
                raise HTTPException(422, '日历结果过多，请缩小日期范围')
            occurrence = next_occurrence(p.schedule, occurrence)
    return {'items': sorted(items, key=lambda row: row['at'])}


class ReconcileInput(BaseModel):
    robot_pk: int
    close_idle: bool = False


@router.post('/executions/{execution_id}/reconcile')
def check_execution(execution_id: str, body: ReconcileInput, db: Session = Depends(get_db), store=Depends(get_archive_store)):
    return reconcile(db, store, execution_id, body.robot_pk, body.close_idle)


class ContinueInput(BaseModel):
    robot_pk: int
    stage_index: int = Field(ge=0)
    confirmed: bool = False


@router.post('/executions/{execution_id}/continue')
def continue_route(execution_id: str, body: ContinueInput, db: Session = Depends(get_db), store=Depends(get_archive_store)):
    from ..services.inspection_dispatch import continue_execution
    return continue_execution(db, store, execution_id, body.robot_pk, body.stage_index, body.confirmed)
