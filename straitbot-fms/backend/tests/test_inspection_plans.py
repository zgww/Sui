"""Plan persistence, schedule and dispatch against isolated SQLite; no device access."""
import json
from datetime import datetime
import pytest
from fastapi import HTTPException
from pydantic import ValidationError
from app.models import InspectionPlan, InspectionRobotLease, PlanExecution, InspectionTask
from app.point_archive.relations import add_binding, referenced_point_ids
from app.services.inspection_schedule import PlanSchedule, next_occurrence
from app.services.inspection_plans import PlanInput, save_plan, delete_plan
from app.services.inspection_dispatch import dispatch, apply_report, reconcile
from app.services import robot_api
from tests.test_point_archive_relations import context
from app.point_archive.runtime import get_archive_store
from app.routers.inspection_plans import router as plan_router


def body_for(context, **changes):
    db, store, robot, robot_map, waypoint, action = context
    if not db.query(InspectionPlan).first():
        from app.models import PointBinding
        if not db.query(PointBinding).first():
            add_binding(db, store, '0001', waypoint.id, action.id)
    return PlanInput(**dict(robot_pk=robot.id, map_pk=robot_map.id, name='巡检', point_ids=['0001'], enabled=True, **changes))


def test_schedule_timezone_weekly_and_once():
    s = dict(mode='daily', timezone='Asia/Shanghai', start_date='2026-09-18', time='09:00')
    assert next_occurrence(s, datetime(2026, 9, 18, 0)) == datetime(2026, 9, 18, 1)
    assert next_occurrence(s, datetime(2026, 9, 18, 1)) == datetime(2026, 9, 19, 1)
    assert next_occurrence(dict(s, mode='once'), datetime(2026, 9, 18, 1)) is None
    assert next_occurrence(dict(s, mode='weekly', weekdays=[0]), datetime(2026, 9, 18)) == datetime(2026, 9, 21, 1)
    assert next_occurrence(dict(s, end_date='2026-09-18'), datetime(2026, 9, 18, 1)) is None
    assert next_occurrence({'mode': 'manual'}, datetime(2026, 9, 18)) is None


@pytest.mark.parametrize('changes', [{'time': '9:00'}, {'timezone': 'invalid'}, {'mode': 'weekly', 'weekdays': []}, {'weekdays': [7]}, {'end_date': '2020-01-01'}])
def test_invalid_schedules(changes):
    with pytest.raises(ValidationError):
        PlanSchedule.model_validate(dict(mode='daily', start_date='2026-09-18', **changes) if 'mode' not in changes else dict(start_date='2026-09-18', **changes))


def test_crud_version_reference_and_no_dispatch(context, monkeypatch):
    monkeypatch.setattr(robot_api, 'call', lambda *a, **kw: pytest.fail('configuration must not call robot'))
    db, store, robot, _, _, _ = context
    body = body_for(context)
    saved = save_plan(db, store, body)
    assert saved['version'] == 1 and saved['next_run_at'] is None
    assert '0001' in referenced_point_ids(db)
    with pytest.raises(HTTPException) as error:
        save_plan(db, store, body)
    assert error.value.status_code == 409
    with pytest.raises(HTTPException):
        save_plan(db, store, body.model_copy(update={'version': 7}), saved['id'])
    updated = save_plan(db, store, body.model_copy(update={'version': 1, 'enabled': False}), saved['id'])
    assert not updated['enabled'] and updated['version'] == 2
    with pytest.raises(HTTPException):
        delete_plan(db, store, saved['id'], robot.id + 999, 2)
    delete_plan(db, store, saved['id'], robot.id, 2)
    assert db.get(InspectionPlan, saved['id']).deleted


def test_dispatch_idempotent_snapshot_and_report(context, monkeypatch):
    db, store, robot, _, _, _ = context
    saved = save_plan(db, store, body_for(context))
    calls = []
    def call(*args):
        calls.append(args)
        return (0, 'ok', {})
    monkeypatch.setattr(robot_api, 'call', call)
    result = dispatch(db, store, saved['id'], robot.id, 'manual:testkey', expected_version=1)
    assert result['status'] == 'accepted'
    assert [c[3] for c in calls] == [102, 100]
    assert json.loads(calls[1][4]['content'])['id'] == result['id']
    assert isinstance(calls[1][4]['content'], str)
    assert json.loads(calls[1][4]['content'])['waypoint'][0]['action'][0]['id']
    same = dispatch(db, store, saved['id'], robot.id, 'manual:testkey', expected_version=1)
    assert same['id'] == result['id'] and len(calls) == 2
    with pytest.raises(HTTPException) as error:
        dispatch(db, store, saved['id'], robot.id, 'manual:another', expected_version=1)
    assert error.value.status_code == 409
    task = db.get(InspectionTask, result['task_id'])
    assert task.archive_snapshot['points'][0]['id'] == '0001'
    assert task.archive_snapshot['bindings'][0]['point_id'] == '0001'
    with pytest.raises(HTTPException):
        apply_report(db, result['id'], robot.id + 1, 1)
    apply_report(db, result['id'], robot.id, 1); db.commit()
    assert db.get(InspectionRobotLease, robot.id) is None
    assert db.get(PlanExecution, result['id']).status == 'done'
    apply_report(db, result['id'], robot.id, 0); db.commit()
    assert db.get(PlanExecution, result['id']).status == 'done'


@pytest.mark.parametrize('failure_cmd,expected', [(102, 'failed'), (100, 'unknown')])
def test_network_failure_is_not_retried(context, monkeypatch, failure_cmd, expected):
    db, store, robot, _, _, _ = context
    saved = save_plan(db, store, body_for(context))
    calls = []
    def call(*args):
        calls.append(args[3])
        if args[3] == failure_cmd:
            raise TimeoutError('timeout')
        return 0, 'ok', {}
    monkeypatch.setattr(robot_api, 'call', call)
    result = dispatch(db, store, saved['id'], robot.id, 'manual:testkey')
    assert result['status'] == expected
    count = len(calls)
    assert dispatch(db, store, saved['id'], robot.id, 'manual:testkey')['id'] == result['id']
    assert len(calls) == count
    assert bool(db.get(InspectionRobotLease, robot.id)) == (expected == 'unknown')
    if expected == 'unknown':
        monkeypatch.setattr(robot_api, 'call', lambda *a: (0, 'ok', {}))
        assert reconcile(db, store, result['id'], robot.id, True)['status'] == 'closed'
        assert db.get(InspectionRobotLease, robot.id) is None


def test_unbound_or_disabled_points_rejected(context):
    db, store, robot, robot_map, waypoint, action = context
    with pytest.raises(HTTPException):
        save_plan(db, store, PlanInput(robot_pk=robot.id, map_pk=robot_map.id, name='new', point_ids=['0001']))
    body = body_for(context)
    snap = store.snapshot(); snap['points'][0]['active'] = False; store.publish(snap, store.revision)
    with pytest.raises(HTTPException):
        save_plan(db, store, body)

def test_dst_nonexistent_time_skipped_and_repeated_time_once():
    spring = dict(mode='daily', timezone='America/New_York', start_date='2026-03-08', time='02:30')
    assert next_occurrence(spring, datetime(2026, 3, 8)) == datetime(2026, 3, 9, 6, 30)
    fall = dict(mode='daily', timezone='America/New_York', start_date='2026-11-01', time='01:30')
    first = next_occurrence(fall, datetime(2026, 11, 1))
    assert first == datetime(2026, 11, 1, 5, 30)
    assert next_occurrence(fall, first) == datetime(2026, 11, 2, 6, 30)


def test_scheduler_claim_restart_and_missed_window(context, monkeypatch):
    from datetime import timedelta
    from sqlalchemy.orm import sessionmaker
    from app import database
    from app.services.inspection_dispatch import tick_plans
    db, store, robot, _, _, _ = context
    saved = save_plan(db, store, body_for(context, schedule=PlanSchedule(mode='daily', start_date='2026-01-01', time='09:00')))
    p = db.get(InspectionPlan, saved['id'])
    p.next_run_at = datetime.utcnow() - timedelta(seconds=1)
    db.commit()
    monkeypatch.setattr(database, 'SessionLocal', sessionmaker(bind=db.get_bind()))
    calls = []
    monkeypatch.setattr(robot_api, 'call', lambda *a: (calls.append(a[3]) or (0, 'ok', {})))
    tick_plans(); tick_plans()
    db.expire_all()
    assert calls == [102, 100]
    assert db.query(PlanExecution).count() == 1
    assert db.get(InspectionPlan, p.id).next_run_at > datetime.utcnow()
    # Recover the same due instant after a crash between claim and cursor update.
    run = db.query(PlanExecution).first()
    p.next_run_at = run.scheduled_at; db.commit()
    tick_plans()
    assert calls == [102, 100]
    db.expire_all(); p = db.get(InspectionPlan, p.id)
    p.next_run_at = datetime.utcnow() - timedelta(hours=1); db.commit()
    tick_plans(); db.expire_all()
    assert db.query(PlanExecution).filter_by(status='skipped').count() == 1
    assert calls == [102, 100]


def test_report_during_dispatch_not_overwritten(context, monkeypatch):
    db, store, robot, _, _, _ = context
    saved = save_plan(db, store, body_for(context))
    def call(*args):
        if args[3] == 100:
            execution_id = json.loads(args[4]['content'])['id']
            apply_report(db, execution_id, robot.id, 1); db.commit()
        return 0, 'ok', {}
    monkeypatch.setattr(robot_api, 'call', call)
    result = dispatch(db, store, saved['id'], robot.id, 'manual:race')
    assert result['status'] == 'done'
    assert db.get(InspectionRobotLease, robot.id) is None


def test_plan_http_scope_and_auth(context):
    from fastapi import FastAPI
    from fastapi.testclient import TestClient
    from types import SimpleNamespace
    from app.auth import get_current_user
    from app.database import get_db
    db, store, robot, _, _, _ = context
    body = body_for(context)
    app = FastAPI(); app.include_router(plan_router)
    app.dependency_overrides[get_db] = lambda: db
    app.dependency_overrides[get_archive_store] = lambda: store
    app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role='engineer')
    with TestClient(app) as client:
        saved = client.post('/api/inspection-plans', json=body.model_dump(mode='json'))
        assert saved.status_code == 200, saved.text
        pid = saved.json()['id']
        assert client.get('/api/inspection-plans', params={'robot_pk': robot.id+1}).json()['total'] == 0
        assert client.get(f'/api/inspection-plans/{pid}/history', params={'robot_pk': robot.id+1}).status_code == 404
        assert client.get('/api/inspection-plans/calendar/occurrences', params={'robot_pk': robot.id, 'start': '2026-01-01T00:00:00Z', 'end': '2027-01-01T00:00:00Z'}).status_code == 422
        app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role='operator')
        assert client.post('/api/inspection-plans', json=body.model_dump(mode='json')).status_code == 403
        app.dependency_overrides.pop(get_current_user)
        assert client.get('/api/inspection-plans', params={'robot_pk': robot.id}).status_code == 401

def test_http_reports_correlate_robot_and_do_not_regress_terminal_state(context, monkeypatch):
    from fastapi import FastAPI
    from fastapi.testclient import TestClient
    from app.database import get_db
    from app.routers.inspection import router
    from app.models import InspectionRun
    db, store, robot, _, _, _ = context
    saved = save_plan(db, store, body_for(context))
    monkeypatch.setattr(robot_api, 'call', lambda *a: (0, 'ok', {}))
    execution = dispatch(db, store, saved['id'], robot.id, 'manual:report-test')
    app = FastAPI(); app.include_router(router)
    app.dependency_overrides[get_db] = lambda: db
    with TestClient(app) as client:
        payload = {'inspection_id': execution['id'], 'status': 1}
        for path in ('status', 'result', 'finish', 'progress'):
            response = client.post('/api/inspection/report/'+path, json=payload, headers={'X-Real-IP': '192.0.2.123'})
            assert response.status_code == 403, (path, response.text)
        assert client.post('/api/inspection/report/status', json=payload, headers={'X-Real-IP': robot.ip}).status_code == 200
        payload['status'] = 0
        assert client.post('/api/inspection/report/status', json=payload, headers={'X-Real-IP': robot.ip}).status_code == 200
    assert db.get(PlanExecution, execution['id']).status == 'done'
    assert db.query(InspectionRun).filter_by(inspection_id=execution['id']).one().status == 'done'
    assert db.get(InspectionRobotLease, robot.id) is None

def test_crashed_claim_becomes_uncertain_without_resend(context, monkeypatch):
    from datetime import timedelta
    db, store, robot, _, _, _ = context
    saved = save_plan(db, store, body_for(context))
    monkeypatch.setattr(robot_api, 'call', lambda *a: (0, 'ok', {}))
    result = dispatch(db, store, saved['id'], robot.id, 'manual:crash')
    e = db.get(PlanExecution, result['id'])
    e.status = 'dispatching'; e.created_at = datetime.utcnow() - timedelta(minutes=2); db.commit()
    calls = []
    monkeypatch.setattr(robot_api, 'call', lambda *a: (calls.append(a[3]) or (0, 'ok', {})))
    assert reconcile(db, store, e.id, robot.id)['status'] == 'unknown'
    assert calls == [102]
    assert db.get(InspectionRobotLease, robot.id) is not None
