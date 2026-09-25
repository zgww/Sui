"""Archive / binding / plan linkage, with isolated DB and simulated device."""
import json
from types import SimpleNamespace
import pytest
from fastapi import FastAPI
from fastapi.testclient import TestClient
from app.auth import get_current_user
from app.database import get_db
from app.point_archive.runtime import get_archive_store
from app.routers.point_archive import router as archive_router
from app.routers.inspection_plans import router as plan_router
from app.models import Robot, RobotMap, Waypoint, InspectionTask
from app.services import robot_api
from tests.test_point_archive_relations import context

@pytest.fixture
def client(context):
    db, store, *_ = context
    app = FastAPI(); app.include_router(archive_router); app.include_router(plan_router)
    app.dependency_overrides[get_db] = lambda: db
    app.dependency_overrides[get_archive_store] = lambda: store
    app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role='engineer')
    with TestClient(app) as c:
        yield c


def test_archive_binding_plan_execution_chain(client, context, monkeypatch):
    db, store, robot, robot_map, waypoint, action = context
    monkeypatch.setattr(robot_api, 'call', lambda *a: pytest.fail('configuration cannot contact robot'))
    base = '/api/point-archive'
    point = {'id': 'workflow-created', 'name': '工作流新测点', 'code': 'FLOW-1', 'active': True, 'directory_id': None}
    r = client.post(base+'/catalog/points', json=point, headers={'If-Match': str(store.revision)})
    assert r.status_code == 200, r.text
    params = {'robot_pk': robot.id, 'map_pk': robot_map.id, 'floor': 0}
    assert not client.get('/api/inspection-plans/options/points', params=params).json()['items']
    r = client.post(base+'/bindings/batch', json={'robot_pk': robot.id, 'waypoint_pk': waypoint.id, 'action_pk': action.id, 'point_ids': [point['id']]})
    assert r.status_code == 200, r.text
    binding_id = r.json()['items'][0]['id']
    assert client.get('/api/inspection-plans/options/points', params=params).json()['items'][0]['id'] == point['id']
    body = dict(robot_pk=robot.id, map_pk=robot_map.id, name='三链路联动测试', point_ids=[point['id']], stages=[dict(map_pk=robot_map.id, floor=0, point_ids=[point['id']])], enabled=True)
    r = client.post('/api/inspection-plans', json=body); assert r.status_code == 200, r.text
    plan = r.json(); url = f"/api/inspection-plans/{plan['id']}"
    preview = client.get(url+'/preview', params={'robot_pk': robot.id})
    assert preview.status_code == 200, preview.text
    stage = preview.json()['stages'][0]
    assert (stage['point_count'], stage['waypoint_count'], stage['action_count']) == (1, 1, 1)
    assert stage['waypoints'][0]['point_ids'] == [point['id']]
    assert stage['waypoints'][0]['actions'][0]['id'] == str(action.id)
    bindings = client.get(base+'/bindings', params={'point_id': point['id'], 'robot_pk': robot.id}).json()['items']
    assert bindings[0]['plan_names'] == [plan['name']] and bindings[0]['map_name'] == robot_map.name
    sent = []
    monkeypatch.setattr(robot_api, 'call', lambda *a: (sent.append(a) or (0, 'simulated', {})))
    result = client.post(url+'/execute', json={'robot_pk': robot.id, 'version': plan['version'], 'request_key': 'workflow-one-shot'})
    assert result.status_code == 200 and result.json()['status'] == 'accepted', result.text
    assert json.loads(sent[1][4]['content'])['waypoint'][0]['action'][0]['id'] == str(action.id)
    snapshot = db.get(InspectionTask, result.json()['task_id']).archive_snapshot
    assert snapshot['points'][0]['id'] == point['id']
    assert client.delete(base+f'/bindings/{binding_id}').status_code == 200
    assert not client.get('/api/inspection-plans/options/points', params=params).json()['items']
    assert client.get(url+'/preview', params={'robot_pk': robot.id}).status_code == 422
    assert db.get(InspectionTask, result.json()['task_id']).archive_snapshot == snapshot


def test_binding_filters_counts_and_robot_isolation(client, context):
    db, store, robot, robot_map, waypoint, action = context
    robot_map.floor = -1; waypoint.wp_id = 'WP-search-code'
    other = Robot(name='other', ip='127.0.0.1'); db.add(other); db.flush()
    othermap = RobotMap(name='other', robot_pk=other.id); db.add(othermap); db.flush()
    db.add(Waypoint(name=waypoint.name, robot_pk=other.id, map_pk=othermap.id)); db.commit()
    base = '/api/point-archive'
    r = client.post(base+'/bindings/batch', json={'robot_pk': robot.id, 'waypoint_pk': waypoint.id, 'point_ids': ['0001']}); assert r.status_code == 200
    filters = {'robot_pk': robot.id, 'map_pk': robot_map.id, 'floor': -1, 'name': 'search-code'}
    row = client.get(base+'/binding-options', params=filters).json()['items'][0]
    assert row['id'] == waypoint.id and row['binding_count'] == 1 and row['floor'] == -1
    assert client.get(base+'/binding-options', params={**filters, 'floor': 2}).json()['total'] == 0
    assert client.get(base+'/binding-options', params={'robot_pk': other.id, 'waypoint_pk': waypoint.id}).json()['total'] == 0
    assert client.get(base+'/bindings', params={'robot_pk': other.id, 'point_id': '0001'}).json()['items'] == []
    for query in ['PT01', '0001', '原名称']:
        assert client.get(base+'/catalog/points', params={'q': ' '+query+' '}).json()['total'] == 1
    assert client.get(base+'/catalog/points', params={'name': 'PT01'}).json()['total'] == 0


def test_workflow_permissions(client, context):
    client.app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role='operator')
    assert client.get('/api/point-archive/binding-options').status_code == 403
    assert client.get('/api/inspection-plans/1/preview', params={'robot_pk': 1}).status_code == 403


def test_plan_directory_filter_includes_legacy_descendants(client, context):
    db, store, robot, robot_map, waypoint, action = context
    result = client.post('/api/point-archive/bindings', json={'point_id': '0001', 'waypoint_pk': waypoint.id})
    assert result.status_code == 200
    doc = store.catalog_data()[0]
    station = next(d for d in doc['directories'] if d['role'] == 'station')
    params = {'robot_pk': robot.id, 'map_pk': robot_map.id, 'floor': 0, 'directory_id': station['id']}
    result = client.get('/api/inspection-plans/options/points', params=params)
    assert [p['id'] for p in result.json()['items']] == ['0001']
    result = client.get('/api/inspection-plans/options/points', params={**params, 'directory_id': 'missing'})
    assert result.status_code == 422
