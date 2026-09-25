"""SQLite archive reference and task snapshot regression tests; no device access."""
import sys
from types import SimpleNamespace

import pytest
from fastapi import HTTPException
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from app.database import Base
from app.models import ArchiveTaskPoint, InspectionTask, PointBinding, Robot, RobotMap, Waypoint, WaypointAction
from app.point_archive.schema import empty_snapshot
from app.point_archive.store import ArchiveStore, RevisionConflict
from app.point_archive.relations import add_binding, list_bindings, referenced_point_ids, remove_binding


@pytest.fixture
def context(tmp_path, monkeypatch):
    engine = create_engine('sqlite:///' + str(tmp_path / 'test.sqlite'))
    Base.metadata.create_all(engine)
    session = sessionmaker(bind=engine)()
    robot = Robot(name='测试机器人', ip='127.0.0.1')
    session.add(robot); session.flush()
    robot_map = RobotMap(robot_pk=robot.id, name='地图')
    session.add(robot_map); session.flush()
    waypoint = Waypoint(map_pk=robot_map.id, robot_pk=robot.id, name='航点')
    session.add(waypoint); session.flush()
    action = WaypointAction(waypoint_pk=waypoint.id, name='动作')
    session.add(action); session.commit()
    store = ArchiveStore(tmp_path / 'archive.json')
    snapshot = empty_snapshot()
    snapshot.update(revision=3, stations=[{'id': 's', 'name': '站'}],
                    bays=[{'id': 'b', 'name': '间隔', 'station_id': 's'}],
                    equipment=[{'id': 'e', 'name': '设备', 'bay_id': 'b'}],
                    points=[{'id': '0001', 'code': 'PT01', 'name': '原名称', 'equipment_id': 'e', 'active': True}])
    store.initialize(snapshot)
    monkeypatch.setitem(sys.modules, 'app.point_archive.runtime', SimpleNamespace(archive_store=store))
    yield session, store, robot, robot_map, waypoint, action
    session.close(); engine.dispose()


def test_binding_create_duplicate_remove_and_reference(context):
    db, store, robot, robot_map, waypoint, action = context
    result = add_binding(db, store, '0001', waypoint.id, action.id)
    assert result['robot_pk'] == robot.id
    assert list_bindings(db, '0001')[0]['action_name'] == '动作'
    assert referenced_point_ids(db) == {'0001'}
    with pytest.raises(HTTPException) as error:
        add_binding(db, store, '0001', waypoint.id, action.id)
    assert error.value.status_code == 409
    remove_binding(db, store, result['id'])
    assert referenced_point_ids(db) == set()
    with pytest.raises(HTTPException):
        remove_binding(db, store, result['id'])


def test_binding_validates_target_and_active_point(context):
    db, store, _, _, waypoint, action = context
    for point_id, waypoint_id, action_id, status in [('missing', waypoint.id, None, 404), ('0001', 999, None, 404), ('0001', waypoint.id, 999, 422)]:
        with pytest.raises(HTTPException) as error:
            add_binding(db, store, point_id, waypoint_id, action_id)
        assert error.value.status_code == status
    updated = store.snapshot()
    updated['points'][0]['active'] = False
    store.publish(updated, store.revision)
    with pytest.raises(HTTPException) as error:
        add_binding(db, store, '0001', waypoint.id)
    assert error.value.status_code == 422


@pytest.mark.parametrize('target', ['map', 'waypoint', 'action', 'robot', 'import'])
def test_delete_and_replace_reject_bound_target(context, target):
    from app.routers import waypoint as api
    from app.routers.robots import delete_robot
    db, store, robot, robot_map, waypoint, action = context
    binding = add_binding(db, store, '0001', waypoint.id, action.id)
    calls = {
        'map': lambda: api.delete_map(robot_map.id, db=db),
        'waypoint': lambda: api.delete_waypoint(waypoint.id, db=db),
        'action': lambda: api.delete_action(action.id, db=db),
        'robot': lambda: delete_robot(robot.id, db=db),
        'import': lambda: api.import_robot(robot.id, api.ImportIn(data={'version': '1.0', 'maps': []}, replace=True), db=db),
    }
    with pytest.raises(HTTPException) as error:
        calls[target]()
    assert error.value.status_code == 409
    assert db.get(Waypoint, waypoint.id) is not None
    remove_binding(db, store, binding['id'])
    calls[target]()


def test_task_snapshot_is_immutable_and_protocol_unchanged(context, monkeypatch):
    from app.routers import inspection
    db, store, robot, _, _, _ = context
    seen = []
    def call(*args):
        # References must already be durable before device interaction.
        assert referenced_point_ids(db) == {'0001'}
        seen.append(args)
        return 0, 'ok', {}
    monkeypatch.setattr(inspection.robot_api, 'call', call)
    result = inspection.create_task(inspection.TaskCreateIn(robot_pk=robot.id, point_ids=['0001'], archive_revision=3, content='legacy-content'), db=db)
    updated = store.snapshot()
    updated['points'][0]['name'] = '新名称'
    store.publish(updated, store.revision)
    task = db.get(InspectionTask, result['task_id'])
    assert task.archive_snapshot['points'][0]['name'] == '原名称'
    assert task.archive_snapshot['revision'] == 3
    assert seen[0][3:] == (100, {'content': 'legacy-content'})
    assert inspection.task_archive_snapshot(task.id, db=db)['archive_snapshot'] == task.archive_snapshot


def test_invalid_snapshot_never_calls_device(context, monkeypatch):
    from app.routers import inspection
    db, _, robot, _, _, _ = context
    monkeypatch.setattr(inspection.robot_api, 'call', lambda *args: pytest.fail('unexpected device call'))
    with pytest.raises(RevisionConflict):
        inspection.create_task(inspection.TaskCreateIn(robot_pk=robot.id, point_ids=['0001'], archive_revision=1), db=db)
    assert db.query(InspectionTask).count() == 0


def test_legacy_task_has_no_archive_requirement(context, monkeypatch):
    from app.routers import inspection
    db, _, robot, _, _, _ = context
    monkeypatch.setattr(inspection.robot_api, 'call', lambda *args: (0, 'ok', {}))
    result = inspection.create_task(inspection.TaskCreateIn(robot_pk=robot.id), db=db)
    assert db.get(InspectionTask, result['task_id']).archive_snapshot is None
    assert db.query(ArchiveTaskPoint).count() == 0


def test_waypoint_only_binding_duplicate_is_rejected(context):
    db, store, _, _, waypoint, _ = context
    add_binding(db, store, '0001', waypoint.id)
    with pytest.raises(HTTPException) as error:
        add_binding(db, store, '0001', waypoint.id)
    assert error.value.status_code == 409


def test_action_must_belong_to_selected_waypoint(context):
    db, store, robot, robot_map, waypoint, action = context
    other = Waypoint(map_pk=robot_map.id, robot_pk=robot.id)
    db.add(other); db.commit()
    with pytest.raises(HTTPException) as error:
        add_binding(db, store, '0001', other.id, action.id)
    assert error.value.status_code == 422
    assert db.query(PointBinding).count() == 0


def test_failed_device_call_keeps_reference_and_snapshot(context, monkeypatch):
    from app.routers import inspection
    db, _, robot, _, _, _ = context
    def fail(*args):
        raise RuntimeError('offline mock')
    monkeypatch.setattr(inspection.robot_api, 'call', fail)
    with pytest.raises(RuntimeError):
        inspection.create_task(inspection.TaskCreateIn(robot_pk=robot.id, point_ids=['0001']), db=db)
    task = db.query(InspectionTask).one()
    assert task.status == 'failed'
    assert task.archive_snapshot['points'][0]['id'] == '0001'
    assert referenced_point_ids(db) == {'0001'}

def test_batch_binding_atomic_and_robot_scoped(context):
    from app.point_archive.relations import add_bindings
    db, store, robot, robot_map, waypoint, action = context
    second = Robot(name='other', ip='127.0.0.2')
    db.add(second); db.commit()
    with pytest.raises(HTTPException) as error:
        add_bindings(db, store, second.id, waypoint.id, ['0001'])
    assert error.value.status_code == 422
    with pytest.raises(HTTPException):
        add_bindings(db, store, robot.id, waypoint.id, ['0001', 'missing'])
    assert db.query(PointBinding).count() == 0
    with pytest.raises(HTTPException):
        add_bindings(db, store, robot.id, waypoint.id, ['0001', '0001'])
    assert db.query(PointBinding).count() == 0
    result = add_bindings(db, store, robot.id, waypoint.id, ['0001'], action.id)
    assert result['items'][0]['point_id'] == '0001'
    assert len(list_bindings(db, robot_pk=robot.id, waypoint_pk=waypoint.id)) == 1
    assert list_bindings(db, robot_pk=second.id) == []
    with pytest.raises(HTTPException) as error:
        add_bindings(db, store, robot.id, waypoint.id, ['0001'], action.id)
    assert error.value.status_code == 409
    assert db.query(PointBinding).count() == 1
