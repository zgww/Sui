"""Verify real HTTP request envelopes against the supplied cmd=100 contract."""
import copy
import json
from types import SimpleNamespace

import httpx
import pytest
from fastapi import FastAPI, HTTPException
from fastapi.testclient import TestClient

from app.auth import get_current_user
from app.database import get_db
from app.models import InspectionRobotLease, InspectionTask
from app.services import robot_api
from app.services.inspection_dispatch import dispatch
from app.services.inspection_plans import save_plan
from app.services.inspection_protocol import immediate_payload
from tests.test_inspection_plans import context, body_for, plan_router, get_archive_store


def test_immediate_button_reaches_documented_http_endpoint(context, monkeypatch):
    db, store, robot, _, waypoint, action = context
    robot.ip, robot.api_port, robot.robot_id = '192.0.2.10', 6002, 56
    waypoint.pose_x, waypoint.pose_y, waypoint.pose_theta = 1.25, 2.5, 90
    waypoint.lift_height = 1.5
    action.action_type, action.duration_ms = 201, 1250
    db.commit()
    p = save_plan(db, store, body_for(context))
    sent = []

    def robot_http(request):
        assert str(request.url) == 'http://192.0.2.10:6002/'
        assert request.method == 'POST' and request.headers['X-ROBOT_ID'] == '56'
        assert request.headers['content-type'] == 'application/json'
        payload = json.loads(request.content)
        sent.append(payload)
        if payload['cmd'] == 102:
            return httpx.Response(200, json={'code': 0, 'msg': 'ok', 'data': {}})
        assert set(payload) == {'cmd', 'content'}  # No schedule and no file.
        assert isinstance(payload['content'], str)
        content = json.loads(payload['content'])
        assert set(content) == {'id', 'name', 'plan', 'waypoint'}
        assert content['name'] == '巡检'
        wp = content['waypoint'][0]
        assert wp['pose']['point']['x'] == 1.25 and wp['pose']['theta'] == 90
        assert wp['action'][0]['lift_height'] == 1.5
        assert wp['action'][0]['action_delay_msec'] == 1250
        assert 'duration' not in wp['action'][0]
        return httpx.Response(200, json={'code': 0, 'msg': '已接收'})  # Common response has no data.

    with httpx.Client(transport=httpx.MockTransport(robot_http)) as transport:
        monkeypatch.setattr(robot_api, '_shared_client', transport)
        app = FastAPI(); app.include_router(plan_router)
        app.dependency_overrides[get_db] = lambda: db
        app.dependency_overrides[get_archive_store] = lambda: store
        app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role='engineer')
        with TestClient(app) as client:
            request = {'robot_pk': robot.id, 'version': p['version'], 'request_key': 'document-wire-test'}
            url = f"/api/inspection-plans/{p['id']}/execute"
            response = client.post(url, json=request)
            assert response.status_code == 200, response.text
            assert response.json()['status'] == 'accepted'
            assert response.json()['message'] == '已接收'
            assert json.loads(sent[1]['content'])['id'] == response.json()['id']
            repeated = client.post(url, json=request)
            assert repeated.json()['id'] == response.json()['id']
    assert [payload['cmd'] for payload in sent] == [102, 100]
    assert isinstance(db.get(InspectionTask, response.json()['task_id']).plan_json, dict)


@pytest.mark.parametrize('failure,expected', [('busy', 'failed'), ('reject', 'failed'), ('timeout', 'unknown'), ('bad_response', 'unknown')])
def test_http_failure_semantics(context, monkeypatch, failure, expected):
    db, store, robot, _, _, _ = context
    p = save_plan(db, store, body_for(context))
    sent = []

    def robot_http(request):
        payload = json.loads(request.content); sent.append(payload['cmd'])
        if payload['cmd'] == 102:
            state = {'inspection_id': 'other', 'status': 0} if failure == 'busy' else {}
            return httpx.Response(200, json={'code': 0, 'msg': 'ok', 'data': state})
        if failure == 'timeout':
            raise httpx.ReadTimeout('response lost', request=request)
        if failure == 'bad_response':
            return httpx.Response(200, text='not JSON')
        return httpx.Response(200, json={'code': 42, 'msg': '定位未就绪'})

    with httpx.Client(transport=httpx.MockTransport(robot_http)) as transport:
        monkeypatch.setattr(robot_api, '_shared_client', transport)
        result = dispatch(db, store, p['id'], robot.id, 'manual:wire-failure')
        again = dispatch(db, store, p['id'], robot.id, 'manual:wire-failure')
    assert again['id'] == result['id'] and result['status'] == expected
    assert sent == ([102] if failure == 'busy' else [102, 100])
    assert bool(db.get(InspectionRobotLease, robot.id)) == (expected == 'unknown')
    if failure == 'reject':
        assert '42' in result['message'] and '定位未就绪' in result['message']


def test_old_snapshot_adapted_without_mutation():
    content = {'id': 'old', 'name': '旧任务', 'plan': '旧计划', 'substationMapsId': '17',
               'waypoint': [{'id': 'w', 'action': [{'id': 'a', 'type': 201, 'duration': 500}]}]}
    before = copy.deepcopy(content)
    payload = immediate_payload(content)
    wire = json.loads(payload['content'])
    assert 'substationMapsId' not in wire and 'schedule' not in payload
    assert wire['waypoint'][0]['action'][0]['action_delay_msec'] == 500
    assert content == before


@pytest.mark.parametrize('content', [None, {}, {'waypoint': []}, {'waypoint': [{'pose': {'x': float('nan')}}]}])
def test_invalid_inline_content_is_rejected(content):
    with pytest.raises(HTTPException) as error:
        immediate_payload(content)
    assert error.value.status_code == 422


def test_legacy_task_dictionary_uses_json_not_python_repr(context, monkeypatch):
    from app.routers.inspection import create_task, TaskCreateIn
    db, _, robot, _, _, _ = context
    content = {'id': 'legacy', 'name': '中文名称', 'waypoint': []}
    sent = []
    monkeypatch.setattr(robot_api, 'call', lambda *args: (sent.append(args[4]) or (0, 'ok', {})))
    create_task(TaskCreateIn(robot_pk=robot.id, content=content), db=db)
    assert json.loads(sent[0]['content']) == content


def test_immediate_payload_strips_fms_only_keys():
    """detectType 是 FMS 侧的路由提示，不是设备协议字段——下发前必须裁掉。

    老机器人不认识这个键，带上它等于把"要不要炸"交给对方的实现决定。这与
    substationMapsId 是同一类键，处理方式也一致。
    """
    content = {
        'id': 'i', 'name': 'n', 'plan': 'p',
        'substationMapsId': 'm',
        'detectType': 'fms',
        'waypoint': [{'id': 'w1', 'index': 1,
                      'pose': {'point': {'x': 1.0, 'y': 0.0, 'z': 0.0}},
                      'action': [{'id': 'a1', 'type': 1}]}],
    }
    wire = json.loads(immediate_payload(content)['content'])
    assert set(wire) == {'id', 'name', 'plan', 'waypoint'}
    assert 'detectType' not in wire and 'substationMapsId' not in wire

    # 蛇形写法也要裁：落盘记录里两种都可能出现
    content['detect_type'] = 'fms'
    wire = json.loads(immediate_payload(content)['content'])
    assert 'detect_type' not in wire

    # 裁剪不能改坏调用方手里的原件
    assert content['detectType'] == 'fms' and content['substationMapsId'] == 'm'
