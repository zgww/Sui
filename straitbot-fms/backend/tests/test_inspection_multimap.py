"""Map/floor route isolation and durable, explicitly confirmed transitions."""
import json
import pytest
from fastapi import HTTPException
from pydantic import ValidationError
from app.models import RobotMap, Waypoint, WaypointAction, InspectionTask, PlanExecution, InspectionRobotLease
from app.point_archive.relations import add_binding, remove_binding, guard_archive_bindings
from app.services.inspection_plans import PlanInput, save_plan
from app.services.inspection_compile import compile_route
from app.services.inspection_dispatch import dispatch, apply_report, continue_execution, reconcile, report_execution
from app.services import robot_api
from tests.test_inspection_plans import context, body_for
from app.routers.inspection_plans import available_floors, eligible_points


def route_fixture(context):
    db, store, robot, first, wp, _ = context
    body_for(context)
    first.floor = 1
    second = RobotMap(robot_pk=robot.id, name='配电楼', floor=2)
    db.add(second); db.flush()
    for floor in (None, 3):
        w = Waypoint(robot_pk=robot.id, map_pk=second.id, floor=floor, wp_id='same-external-id', name=f'楼层 {floor}', pose_x=20 if floor is None else 30)
        db.add(w); db.flush()
        db.add(WaypointAction(waypoint_pk=w.id, name='拍照', action_type=1)); db.flush()
        add_binding(db, store, '0001', w.id)
    stages = [{'map_pk': first.id, 'floor': 1, 'point_ids': ['0001']},
              {'map_pk': second.id, 'floor': 2, 'point_ids': ['0001']},
              {'map_pk': second.id, 'floor': 3, 'point_ids': ['0001']}]
    db.commit()
    return PlanInput(robot_pk=robot.id, name='跨楼层计划', stages=stages, enabled=True)


def test_map_floor_scope_and_order(context):
    db, store, robot, first, _, _ = context
    body = route_fixture(context)
    saved = save_plan(db, store, body)
    assert saved['point_ids'] == ['0001']
    route, bindings = compile_route(db, store, robot.id, saved['stages'], 'test', 'route')
    assert [s['floor'] for s in route] == [1, 2, 3]
    assert [s['content']['id'] for s in route] == ['test', 'test-s2', 'test-s3']
    assert [s['content']['waypoint'][0]['pose']['point']['x'] for s in route][1:] == [20, 30]
    assert len(bindings) == 3
    assert len(available_floors(robot.id, db)['items']) == 3
    assert eligible_points(robot.id, first.id, floor=2, page=1, db=db, store=store)['total'] == 0
    assert eligible_points(robot.id, first.id, floor=1, page=1, db=db, store=store)['total'] == 1
    bad = dict(saved['stages'][0], floor=99)
    with pytest.raises(HTTPException):
        compile_route(db, store, robot.id, [bad], 'test', 'route')
    with pytest.raises(HTTPException):
        compile_route(db, store, robot.id + 1, saved['stages'], 'test', 'route')


def test_explicit_transition_snapshot_deduplication_and_late_reports(context, monkeypatch):
    db, store, robot, _, _, _ = context
    p = save_plan(db, store, route_fixture(context))
    sent = []
    monkeypatch.setattr(robot_api, 'call', lambda *args: (sent.append(json.loads(args[4]['content'])) or (0, 'ok', {})) if args[3] == 100 else (0, 'ok', {}))
    e = dispatch(db, store, p['id'], robot.id, 'manual:route-test')
    apply_report(db, e['id'], robot.id, 1); db.commit()
    assert db.get(PlanExecution, e['id']).status == 'waiting_transition'
    assert db.get(InspectionRobotLease, robot.id)
    with pytest.raises(HTTPException):
        continue_execution(db, store, e['id'], robot.id, 0, False)
    db.query(Waypoint).filter(Waypoint.pose_x == 20).update({'pose_x': 99}); db.commit()
    second = continue_execution(db, store, e['id'], robot.id, 0, True)
    assert second['stage_index'] == 1 and second['status'] == 'accepted'
    assert sent[1]['waypoint'][0]['pose']['point']['x'] == 20  # immutable snapshot
    assert db.get(InspectionTask, e['task_id']).plan_json['id'] == e['id'] + '-s2'
    assert continue_execution(db, store, e['id'], robot.id, 0, True)['stage_index'] == 1
    assert len(sent) == 2
    apply_report(db, e['id'], robot.id, 1); db.commit()  # stale stage one completion
    assert db.get(PlanExecution, e['id']).status == 'accepted'
    assert report_execution(db, e['id'] + '-s2').id == e['id']
    assert report_execution(db, e['id'] + '-s99') is None
    with pytest.raises(HTTPException):
        apply_report(db, e['id'] + '-s2', robot.id + 1, 1)
    apply_report(db, e['id'] + '-s2', robot.id, 1); db.commit()
    continue_execution(db, store, e['id'], robot.id, 1, True)
    apply_report(db, e['id'] + '-s3', robot.id, 1); db.commit()
    assert db.get(PlanExecution, e['id']).status == 'done'
    assert db.get(InspectionRobotLease, robot.id) is None
    assert len(sent) == 3


def test_second_segment_timeout_holds_lease_and_is_not_retried(context, monkeypatch):
    db, store, robot, _, _, _ = context
    p = save_plan(db, store, route_fixture(context))
    monkeypatch.setattr(robot_api, 'call', lambda *args: (0, 'ok', {}))
    e = dispatch(db, store, p['id'], robot.id, 'manual:timeout')
    apply_report(db, e['id'], robot.id, 1); db.commit()
    calls = []
    def timed_out(*args):
        calls.append(args[3])
        if args[3] == 100:
            raise TimeoutError('lost response')
        return 0, 'ok', {}
    monkeypatch.setattr(robot_api, 'call', timed_out)
    result = continue_execution(db, store, e['id'], robot.id, 0, True)
    assert result['status'] == 'unknown' and db.get(InspectionRobotLease, robot.id)
    continue_execution(db, store, e['id'], robot.id, 0, True)
    assert calls == [102, 100]
    monkeypatch.setattr(robot_api, 'call', lambda *a: (0, 'ok', {'inspection_id': e['id'] + '-s2', 'status': -1}))
    assert reconcile(db, store, e['id'], robot.id)['status'] == 'canceled'
    assert db.get(InspectionRobotLease, robot.id) is None


def test_secondary_map_protected_after_unbinding(context):
    from app.models import PointBinding
    db, store, robot, _, _, _ = context
    p = save_plan(db, store, route_fixture(context))
    for b in db.query(PointBinding).all():
        remove_binding(db, store, b.id)
    @guard_archive_bindings('map', 'map_pk')
    def remove(map_pk, db):
        pytest.fail('referenced map must be protected')
    with pytest.raises(HTTPException) as error:
        remove(p['stages'][1]['map_pk'], db)
    assert error.value.status_code == 409


def test_null_floor_disallowed_for_new_routes():
    with pytest.raises(ValidationError):
        PlanInput(robot_pk=1, name='invalid', stages=[{'map_pk': 1, 'point_ids': ['a']}])


def test_http_second_stage_reports_and_authorized_continuation(context, monkeypatch):
    from types import SimpleNamespace
    from fastapi import FastAPI
    from fastapi.testclient import TestClient
    from app.database import get_db
    from app.auth import get_current_user
    from app.routers.inspection import router
    from tests.test_inspection_plans import plan_router, get_archive_store
    db, store, robot, _, _, _ = context
    p = save_plan(db, store, route_fixture(context))
    monkeypatch.setattr(robot_api, 'call', lambda *args: (0, 'ok', {}))
    execution = dispatch(db, store, p['id'], robot.id, 'manual:http-stages')
    app = FastAPI(); app.include_router(router); app.include_router(plan_router)
    app.dependency_overrides[get_db] = lambda: db
    app.dependency_overrides[get_archive_store] = lambda: store
    app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role='engineer')
    with TestClient(app) as client:
        for index in range(3):
            eid = execution['id'] if index == 0 else execution['id'] + f'-s{index+1}'
            response = client.post('/api/inspection/report/status', json={'inspection_id': eid, 'status': 1}, headers={'X-Real-IP': robot.ip})
            assert response.status_code == 200
            assert db.get(PlanExecution, execution['id']).status == ('done' if index == 2 else 'waiting_transition')
            if index < 2:
                url = '/api/inspection-plans/executions/' + execution['id'] + '/continue'
                body = {'robot_pk': robot.id, 'stage_index': index, 'confirmed': True}
                app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role='operator')
                assert client.post(url, json=body).status_code == 403
                app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role='engineer')
                assert client.post(url, json=dict(body, robot_pk=robot.id+1)).status_code == 404
                assert client.post(url, json=body).json()['stage_index'] == index + 1
    assert db.get(InspectionRobotLease, robot.id) is None


def test_legacy_null_stage_round_trip(context):
    db, store, _, _, _, _ = context
    p = save_plan(db, store, body_for(context))
    assert p['stages'] is None
    updated = save_plan(db, store, PlanInput(**dict(p, enabled=False)), p['id'])
    assert not updated['enabled']
