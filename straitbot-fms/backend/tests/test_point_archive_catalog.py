"""Free hierarchy, portability, project isolation and optional platform validation."""
import copy
import pytest
from app.point_archive.catalog import as_catalog, portable, from_portable, platform_check
from app.point_archive.schema import validate_snapshot, ArchiveValidationError
from app.point_archive.store import ArchiveStore
from tests.test_point_archive_api import context, PREFIX
from tests.point_archive_fixtures import archive_fixture


def catalog(depth=7):
    return {"schema_version": 2, "revision": 1,
            "directories": [{"id": str(i), "name": f"目录{i}", "parent_id": str(i-1) if i else None, "role": "custom"} for i in range(depth)],
            "points": [{"id": "000001", "name": "测点", "directory_id": str(depth-1) if depth else None,
                        "extensions": {"vendor": {"value": [1, 2]}}}]}


def test_arbitrary_depth_iterative_and_roundtrip(tmp_path):
    doc = validate_snapshot(catalog(2000))
    store = ArchiveStore(tmp_path / 'archive.json'); store.initialize(doc)
    assert store.catalog_points(directory_id='0')['total'] == 1
    assert store.catalog_points(directory_id='0', recursive=False)['total'] == 0
    assert len(store.catalog_directories()['items']) == 2000
    exported = portable(store.snapshot())
    assert set(exported) == {'format', 'schema_version', 'directories', 'points'}
    imported = from_portable(exported)
    assert imported['points'][0]['id'] == '000001'
    assert portable(imported) == exported
    reloaded = ArchiveStore(store.path); reloaded.load()
    assert reloaded.catalog_points()['items'][0]['parent_name'] == '目录1999'


@pytest.mark.parametrize('change', ['cycle', 'self', 'missing', 'pointmissing', 'role', 'duplicate'])
def test_invalid_catalog(change):
    doc = catalog()
    if change == 'cycle': doc['directories'][0]['parent_id'] = '6'
    if change == 'self': doc['directories'][2]['parent_id'] = '2'
    if change == 'missing': doc['directories'][2]['parent_id'] = 'unknown'
    if change == 'pointmissing': doc['points'][0]['directory_id'] = 'missing'
    if change == 'role': doc['directories'][2]['role'] = []
    if change == 'duplicate': doc['directories'].append(copy.deepcopy(doc['directories'][0]))
    with pytest.raises(ArchiveValidationError): validate_snapshot(doc)


def test_legacy_migration_retains_point_id_and_fields():
    old = validate_snapshot(archive_fixture(2))
    old['points'][0]['extensions'] = {'custom': ['原值']}
    new = from_portable(old)
    assert [p['id'] for p in new['points']] == [p['id'] for p in old['points']]
    assert new['points'][0]['extensions'] == {'custom': ['原值']}
    assert platform_check(new)['valid']
    new['points'][0]['extensions']['custom'].append('new')
    assert old['points'][0]['extensions']['custom'] == ['原值']


def test_free_hierarchy_valid_locally_invalid_for_platform():
    doc = validate_snapshot(catalog())
    assert not platform_check(doc)['valid']
    assert portable(doc)['directories']
    assert validate_snapshot(catalog(0))['points'][0]['directory_id'] is None
    assert not platform_check(catalog(0))['valid']


def test_v1_read_projection_does_not_write_or_change_revision(context):
    client, store, _, _ = context
    before = store.path.read_bytes()
    r = client.get(PREFIX + '/catalog/directories')
    assert r.status_code == 200 and len(r.json()['items']) == 4
    assert store.path.read_bytes() == before
    assert store.snapshot()['schema_version'] == 1
    assert client.get(PREFIX + '/catalog/platform-check').json()['valid']


def test_catalog_crud_and_move_protections(context):
    client, store, _, _ = context
    def create(row):
        return client.post(PREFIX + '/catalog/directories', json=row, headers={'If-Match':str(store.revision)})
    assert create({'id':'free','name':'自由目录','parent_id':None}).status_code == 200
    assert store.snapshot()['schema_version'] == 2
    assert create({'id':'child','name':'任意下级','parent_id':'free'}).status_code == 200
    h={'If-Match':str(store.revision)}
    r=client.put(PREFIX+'/catalog/directories/free',json={'parent_id':'child'},headers=h)
    assert r.status_code == 422
    assert client.delete(PREFIX+'/catalog/directories/free',headers=h).status_code == 409
    assert client.put(PREFIX+'/catalog/directories/child',json={'parent_id':None},headers=h).status_code == 200
    assert client.delete(PREFIX+'/catalog/directories/free',headers={'If-Match':str(store.revision)}).status_code == 200
    assert client.post(PREFIX+'/entities/stations',json={'id':'old','name':'old'},headers={'If-Match':str(store.revision)}).status_code == 409


def test_portable_preview_publish_export_and_optional_validation(context):
    client, store, _, _ = context
    raw = portable(validate_snapshot(catalog()))
    before = store.path.read_bytes()
    r=client.post(PREFIX+'/catalog/import/preview',json=raw)
    assert r.status_code == 200 and r.json()['counts']['directories'] == 7
    assert store.path.read_bytes() == before
    assert client.put(PREFIX+'/catalog/import',json=raw).status_code == 428
    h={'If-Match':str(store.revision)}
    assert client.put(PREFIX+'/catalog/import',json=raw,headers=h).status_code == 200
    assert client.put(PREFIX+'/catalog/import',json=raw,headers=h).status_code == 409
    response=client.get(PREFIX+'/catalog/export')
    assert response.status_code == 200 and 'attachment' in response.headers['content-disposition']
    assert response.json() == raw
    assert client.get(PREFIX+'/catalog/export?platform=true').status_code == 422
    assert not client.get(PREFIX+'/catalog/platform-check').json()['valid']
    assert client.get(PREFIX+'/catalog/points?directory_id=0').json()['total'] == 1
    assert client.get(PREFIX+'/catalog/points?directory_id=0&recursive=false').json()['total'] == 0
    assert client.get(PREFIX+'/points').json()['total'] == 1


def test_projects_have_independent_revisions_and_no_bindings_in_portable(context, tmp_path):
    client, source, _, _ = context
    payload = client.get(PREFIX+'/catalog/export').json()
    assert 'revision' not in payload and 'bindings' not in payload and 'source' not in payload
    target = ArchiveStore(tmp_path/'project-b.json'); target.initialize(validate_snapshot(catalog(0)))
    target.publish(from_portable(payload), 1)
    assert target.revision == 2
    assert source.revision == 1
    target_doc=target.snapshot(); target_doc['points'][0]['name']='项目B本地修改'; target.publish(target_doc,2)
    assert source.get(source.snapshot()['points'][0]['id'])['name'] != '项目B本地修改'


def test_new_api_auth_and_duplicate_keys(context):
    from app.auth import get_current_user
    from types import SimpleNamespace
    client, store, _, app = context
    assert client.post(PREFIX+'/catalog/import/preview',content='{"schema_version":2,"schema_version":2}').status_code == 422
    app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role='operator',enabled=True)
    for suffix in ['/catalog/directories','/catalog/points','/catalog/export','/catalog/platform-check']:
        assert client.get(PREFIX+suffix).status_code == 403


def test_import_rejects_project_runtime_fields():
    raw=portable(validate_snapshot(catalog()))
    raw['bindings']=[{'point_id':'000001','waypoint_pk':99}]
    with pytest.raises(ArchiveValidationError): from_portable(raw)
    raw.pop('bindings');raw['points'][0]['extensions']['robot_id']='device-a'
    with pytest.raises(ArchiveValidationError): from_portable(raw)


def test_migration_preserves_bindings_and_historical_snapshots(context):
    from app.models import Robot, RobotMap, Waypoint, PointBinding
    from app.point_archive.relations import add_binding
    client, store, sessions, _ = context
    original = store.capture(['p1'], store.revision)
    with sessions() as db:
        robot=Robot(name='test',ip='127.0.0.1');db.add(robot);db.flush()
        m=RobotMap(robot_pk=robot.id,name='test');db.add(m);db.flush()
        w=Waypoint(map_pk=m.id,robot_pk=robot.id,name='test');db.add(w);db.commit()
        binding=add_binding(db,store,'p1',w.id)
    payload=client.get(PREFIX+'/catalog/export').json()
    h={'If-Match':str(store.revision)}
    assert client.put(PREFIX+'/catalog/import',json=payload,headers=h).status_code == 200
    assert client.get(PREFIX+'/catalog/points?bound=true').json()['total'] == 1
    point=next(p for p in payload['points'] if p['id']=='p1');point['name']='新版修改'
    assert client.put(PREFIX+'/catalog/points/p1',json=point,headers={'If-Match':str(store.revision)}).status_code == 200
    assert original['points'][0]['name'] != '新版修改'
    assert store.capture(['p1'],store.revision)['points'][0]['name'] == '新版修改'
    assert client.delete(PREFIX+'/catalog/points/p1',headers={'If-Match':str(store.revision)}).status_code == 409
    payload['points']=[p for p in payload['points'] if p['id']!='p1']
    assert client.post(PREFIX+'/catalog/import/preview',json=payload).status_code == 409
    assert client.put(PREFIX+'/catalog/import',json=payload,headers={'If-Match':str(store.revision)}).status_code == 409
    with sessions() as db:
        assert db.query(PointBinding).count() == 1


def test_directory_id_with_slash_can_be_edited_and_removed(context):
    client, store, _, _ = context
    row={'id':'area/001','name':'斜杠ID目录','parent_id':None}
    assert client.post(PREFIX+'/catalog/directories',json=row,headers={'If-Match':str(store.revision)}).status_code == 200
    row['name']='改名目录'
    assert client.put(PREFIX+'/catalog/directories/area%2F001',json=row,headers={'If-Match':str(store.revision)}).status_code == 200
    assert client.delete(PREFIX+'/catalog/directories/area%2F001',headers={'If-Match':str(store.revision)}).status_code == 200
