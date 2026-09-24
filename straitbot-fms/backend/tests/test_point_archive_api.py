"""HTTP contracts against temporary JSON + SQLite, never production storage."""
import copy
from types import SimpleNamespace

import pytest
from fastapi import FastAPI
from fastapi.testclient import TestClient
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from app.auth import get_current_user
from app.database import Base, get_db
from app.models import PointBinding, Robot, RobotMap, Waypoint
from app.point_archive.runtime import get_archive_store
from app.point_archive.store import ArchiveStore
from app.routers.point_archive import router, install_error_handlers
from tests.point_archive_fixtures import archive_fixture

PREFIX = "/api/point-archive"


@pytest.fixture
def context(tmp_path):
    store = ArchiveStore(tmp_path / "archive.json")
    store.initialize(archive_fixture(3))
    engine = create_engine("sqlite:///" + str(tmp_path / "test.db"), connect_args={"check_same_thread": False})
    Base.metadata.create_all(engine)
    sessions = sessionmaker(bind=engine)
    app = FastAPI()
    install_error_handlers(app)
    app.include_router(router)
    def db_dependency():
        with sessions() as db:
            yield db
    app.dependency_overrides[get_db] = db_dependency
    app.dependency_overrides[get_archive_store] = lambda: store
    app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role="engineer", enabled=True)
    with TestClient(app) as client:
        yield client, store, sessions, app
    engine.dispose()


def test_auth_required_and_operator_rejected(context):
    client, _, _, app = context
    app.dependency_overrides.pop(get_current_user)
    assert client.get(PREFIX + "/meta").status_code == 401
    app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role="operator")
    assert client.get(PREFIX + "/meta").status_code == 403
    assert client.put(PREFIX + "/snapshot", json={}).status_code == 403


def test_meta_detail_search_and_page(context):
    client, _, _, _ = context
    assert client.get(PREFIX + "/meta").json()["counts"]["points"] == 3
    result = client.get(PREFIX + "/points", params={"page_size": 2}).json()
    assert result["total"] == 3 and len(result["items"]) == 2
    assert client.get(PREFIX + "/entities/points", params={"code": "P00002"}).json()["items"][0]["id"] == "p2"
    assert client.get(PREFIX + "/entities/points", params={"name": "does-not-exist"}).json()["total"] == 0
    assert client.get(PREFIX + "/points/p1").json()["item"]["id"] == "p1"
    assert client.get(PREFIX + "/points/missing").status_code == 404


@pytest.mark.parametrize("query", [{"page": 0}, {"page_size": 201}, {"page_size": -1}, {"revision": 999}])
def test_invalid_pagination_or_revision(context, query):
    client, _, _, _ = context
    assert client.get(PREFIX + "/entities/points", params=query).status_code == (409 if "revision" in query else 422)


def test_tree_hierarchy(context):
    client, _, _, _ = context
    root = client.get(PREFIX + "/tree").json()["items"]
    assert root[0]["id"] == "s1"
    levels = client.get(PREFIX + "/tree", params={"parent_type": "station", "parent_id": "s1"}).json()["items"]
    assert levels[0]["type"] == "voltage"
    assert client.get(PREFIX + "/tree", params={"parent_type": "equipment", "parent_id": "e1"}).json()["total"] == 3
    assert client.get(PREFIX + "/tree", params={"parent_type": "equipment"}).status_code == 422


def test_entity_crud_is_persistent_and_id_immutable(context):
    client, store, _, _ = context
    revision = 1
    for kind, row in [
        ("stations", {"id": "s2", "name": "第二站", "code": "002"}),
        ("bays", {"id": "b2", "name": "间隔", "station_id": "s2", "voltage_level": "10kV"}),
        ("equipment", {"id": "e2", "name": "设备", "bay_id": "b2"}),
        ("points", {"id": "0001", "code": "00001", "name": "新测点", "equipment_id": "e2", "times": 2}),
    ]:
        response = client.post(PREFIX + f"/entities/{kind}", json=row, headers={"If-Match": str(revision)})
        assert response.status_code == 200, response.text
        revision = response.json()["revision"]
    response = client.put(PREFIX + "/entities/points/0001", json={"name": "已更新", "active": False}, headers={"If-Match": str(revision)})
    assert response.status_code == 200, response.text
    revision = response.json()["revision"]
    reloaded = ArchiveStore(store.path)
    reloaded.load()
    assert reloaded.get("0001")["name"] == "已更新"
    assert reloaded.get("0001")["code"] == "00001"
    assert client.put(PREFIX + "/entities/points/0001", json={"id": "changed"}, headers={"If-Match": str(revision)}).status_code == 422
    assert client.delete(PREFIX + "/entities/equipment/e2", headers={"If-Match": str(revision)}).status_code == 422
    assert client.delete(PREFIX + "/entities/points/0001", headers={"If-Match": str(revision)}).status_code == 200


def test_concurrent_update_conflict_missing_header_and_duplicate(context):
    client, store, _, _ = context
    assert client.put(PREFIX + "/entities/points/p1", json={"name": "A"}).status_code == 428
    assert client.put(PREFIX + "/entities/points/p1", json={"name": "A"}, headers={"If-Match": "1"}).status_code == 200
    assert client.put(PREFIX + "/entities/points/p1", json={"name": "B"}, headers={"If-Match": "1"}).status_code == 409
    assert store.get("p1")["name"] == "A"
    assert client.post(PREFIX + "/entities/points", json={"id": "p1"}, headers={"If-Match": "2"}).status_code == 409


def test_preview_export_and_publish_roundtrip(context):
    client, store, _, _ = context
    before = store.path.read_bytes()
    candidate = client.get(PREFIX + "/export").json()
    candidate["points"][0]["name"] = "导入更新"
    response = client.post(PREFIX + "/import/preview", json=candidate)
    assert response.status_code == 200, response.text
    assert response.json()["changes"]["updated"] == 1
    assert store.path.read_bytes() == before
    result = client.put(PREFIX + "/snapshot", json=candidate, headers={"If-Match": "1"})
    assert result.status_code == 200, result.text
    exported = client.get(PREFIX + "/export")
    assert "attachment" in exported.headers["content-disposition"]
    assert exported.json()["points"][0]["name"] == "导入更新"
    assert list((store.path.parent / "revisions").glob("*.json"))


@pytest.mark.parametrize("payload", ['{"name":"a","name":"b"}', '{"times":NaN}', '[]', '{', '{"name":"ok","times":0}'])
def test_invalid_json_or_entity_is_rejected_without_writes(context, payload):
    client, store, _, _ = context
    result = client.put(PREFIX + "/entities/points/p1", content=payload, headers={"If-Match": "1", "Content-Type": "application/json"})
    assert result.status_code == 422, result.text
    assert store.revision == 1


def test_bindings_protect_point_and_filter_results(context):
    client, store, sessions, _ = context
    with sessions() as db:
        robot = Robot(name="test", ip="127.0.0.1")
        db.add(robot); db.flush()
        m = RobotMap(robot_pk=robot.id, name="map")
        db.add(m); db.flush()
        waypoint = Waypoint(robot_pk=robot.id, map_pk=m.id, name="test-waypoint")
        db.add(waypoint); db.commit()
        wid = waypoint.id
    binding = client.post(PREFIX + "/bindings", json={"point_id": "p1", "waypoint_pk": wid})
    assert binding.status_code == 200, binding.text
    assert client.get(PREFIX + "/entities/points", params={"bound": True}).json()["total"] == 1
    assert client.get(PREFIX + "/entities/points", params={"bound": False}).json()["total"] == 2
    assert client.delete(PREFIX + "/entities/points/p1", headers={"If-Match": "1"}).status_code == 409
    candidate = store.snapshot()
    candidate["points"] = [p for p in candidate["points"] if p["id"] != "p1"]
    assert client.post(PREFIX + "/import/preview", json=candidate).status_code == 409
    assert client.delete(PREFIX + f'/bindings/{binding.json()["id"]}').status_code == 200
    assert client.delete(PREFIX + "/entities/points/p1", headers={"If-Match": "1"}).status_code == 200


def test_service_unavailable_never_returns_fake_empty_archive(context):
    client, store, _, _ = context
    store._state = None
    assert client.get(PREFIX + "/meta").status_code == 503

def test_binding_batch_http_is_atomic_and_scoped(context):
    client, store, sessions, _ = context
    with sessions() as db:
        first = Robot(name='first', ip='127.0.0.1'); second = Robot(name='second', ip='127.0.0.2')
        db.add_all([first, second]); db.flush()
        m = RobotMap(robot_pk=first.id, name='map'); db.add(m); db.flush()
        w = Waypoint(robot_pk=first.id, map_pk=m.id, name='target'); db.add(w); db.commit()
        rid, other, wid = first.id, second.id, w.id
    assert client.get(PREFIX+'/binding-options', params={'robot_pk': other}).json()['total'] == 0
    assert client.get(PREFIX+'/binding-options', params={'robot_pk': rid}).json()['total'] == 1
    payload = {'robot_pk': rid, 'waypoint_pk': wid, 'point_ids': ['p1', 'missing']}
    assert client.post(PREFIX+'/bindings/batch', json=payload).status_code == 404
    assert client.get(PREFIX+'/bindings', params={'robot_pk': rid}).json()['items'] == []
    payload['point_ids'] = ['p1', 'p2']
    wrong = dict(payload, robot_pk=other)
    assert client.post(PREFIX+'/bindings/batch', json=wrong).status_code == 422
    result = client.post(PREFIX+'/bindings/batch', json=payload)
    assert result.status_code == 200, result.text
    assert len(result.json()['items']) == 2
    assert client.get(PREFIX+'/bindings', params={'robot_pk': other}).json()['items'] == []
    assert client.get(PREFIX+'/bindings', params={'robot_pk': rid, 'waypoint_pk': wid}).json()['items'][0]['point_name']
