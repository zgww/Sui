"""Round 9: upgrades and recovery use temporary files and SQLite only."""
import ast
import asyncio
from contextlib import asynccontextmanager
from pathlib import Path
import sys
from types import SimpleNamespace

from fastapi import FastAPI
import pytest
from sqlalchemy import create_engine, inspect, text
from sqlalchemy.orm import sessionmaker

from app import database
from app.models import InspectionTask
from app.point_archive import runtime
from app.point_archive.schema import empty_snapshot
from app.point_archive.store import ArchiveStore, ArchiveUnavailable


def test_upgrade_existing_task_table_preserves_legacy_row(tmp_path, monkeypatch):
    engine = create_engine('sqlite:///' + str(tmp_path / 'legacy.db'))
    sessions = sessionmaker(bind=engine)
    with engine.begin() as conn:
        conn.execute(text('''CREATE TABLE inspection_tasks (
            id INTEGER PRIMARY KEY, robot_pk INTEGER, name VARCHAR(128),
            plan_json JSON, schedule_json JSON, status VARCHAR(32),
            created_at DATETIME, updated_at DATETIME)'''))
        conn.execute(text('''INSERT INTO inspection_tasks (id, name, plan_json, status)
                             VALUES (7, '既有任务', '{"legacy": true}', 'done')'''))
    monkeypatch.setattr(database, 'engine', engine)
    monkeypatch.setattr(database, 'SessionLocal', sessions)
    try:
        database.init_db()
        database.init_db()
        assert 'archive_snapshot' in {c['name'] for c in inspect(engine).get_columns('inspection_tasks')}
        assert {'point_bindings', 'archive_task_points'} <= set(inspect(engine).get_table_names())
        with sessions() as db:
            task = db.get(InspectionTask, 7)
            assert task.name == '既有任务' and task.status == 'done'
            assert task.plan_json == {'legacy': True} and task.archive_snapshot is None
            task.archive_snapshot = {'revision': 1, 'points': [{'id': '0001'}]}
            db.commit()
        with sessions() as db:
            assert db.get(InspectionTask, 7).archive_snapshot['points'][0]['id'] == '0001'
    finally:
        engine.dispose()


@pytest.fixture
def isolated_archive(tmp_path, monkeypatch):
    store = ArchiveStore(tmp_path / 'archive.json')
    monkeypatch.setattr(runtime, 'archive_store', store)
    yield store
    store.close()


def test_startup_initializes_missing_archive_once(isolated_archive):
    store = isolated_archive
    runtime.startup_archive()
    before = store.path.read_bytes()
    assert store.meta()['counts']['points'] == 0 and store.revision == 1
    runtime.startup_archive()
    assert store.path.read_bytes() == before
    assert store._lease is not None
    store.close()
    replacement = ArchiveStore(store.path)
    try:
        replacement.acquire_writer()
        replacement.load()
        assert replacement.revision == 1
    finally:
        replacement.close()


@pytest.mark.parametrize('raw', [b'{broken', b'{}', b'{"schema_version": 9000}'])
def test_corrupt_startup_never_resets_file(isolated_archive, raw):
    store = isolated_archive
    store.path.write_bytes(raw)
    runtime.startup_archive()
    assert store.path.read_bytes() == raw
    assert store.last_error
    with pytest.raises(ArchiveUnavailable):
        store.meta()
    with pytest.raises(ArchiveUnavailable):
        store.publish(empty_snapshot(), 1)
    assert store.path.read_bytes() == raw


def test_second_writer_is_rejected_and_can_recover_after_close(isolated_archive):
    store = isolated_archive
    runtime.startup_archive()
    competitor = ArchiveStore(store.path)
    try:
        with pytest.raises(ArchiveUnavailable):
            competitor.acquire_writer()
        assert competitor._lease is None
        store.close()
        competitor.acquire_writer()
        competitor.load()
        assert competitor.revision == 1
    finally:
        competitor.close()


def _isolated_lifespan(monkeypatch, *, fail_start=False, fail_shutdown=False):
    # Execute the actual lifespan definition with unrelated startup services
    # isolated; avoid import-time AI/vision dependencies and production paths.
    source = Path(__file__).resolve().parents[1] / 'app' / 'main.py'
    module = ast.parse(source.read_text(encoding='utf-8'))
    definition = next(n for n in module.body if isinstance(n, ast.AsyncFunctionDef) and n.name == 'lifespan')
    async def no_async():
        return None
    def no_op():
        return None
    def startup_prefab():
        if fail_start:
            raise RuntimeError('simulated startup failure')
    def shutdown_scheduler():
        if fail_shutdown:
            raise RuntimeError('simulated shutdown failure')
    monkeypatch.setitem(sys.modules, 'app.routers.prefab', SimpleNamespace(startup_prefab=startup_prefab, shutdown_prefab=no_op))
    monkeypatch.setitem(sys.modules, 'app.simulation.bridge', SimpleNamespace(bridge=SimpleNamespace(start=no_async, close=no_async)))
    monkeypatch.setitem(sys.modules, 'app.services.poller', SimpleNamespace(start_scheduler=no_op, shutdown_scheduler=shutdown_scheduler))
    namespace = {'__package__': 'app', 'asynccontextmanager': asynccontextmanager, 'FastAPI': FastAPI,
                 'init_db': no_op, '_ensure_default_prefabs': no_op, '_ensure_default_data': no_op,
                 '_ensure_default_users': no_op}
    exec(compile(ast.Module(body=[definition], type_ignores=[]), str(source), 'exec'), namespace)
    return namespace['lifespan']


@pytest.mark.parametrize('fail_start,fail_shutdown', [(False, False), (True, False), (False, True)])
def test_lifespan_always_releases_writer(isolated_archive, monkeypatch, fail_start, fail_shutdown):
    store = isolated_archive
    lifespan = _isolated_lifespan(monkeypatch, fail_start=fail_start, fail_shutdown=fail_shutdown)
    async def run():
        async with lifespan(FastAPI()):
            assert store._lease is not None
            assert store.meta()['counts']['points'] == 0
    if fail_start or fail_shutdown:
        with pytest.raises(RuntimeError):
            asyncio.run(run())
    else:
        asyncio.run(run())
    assert store._lease is None
    competitor = ArchiveStore(store.path)
    try:
        competitor.acquire_writer()
    finally:
        competitor.close()


def test_lifespan_keeps_corrupt_archive_unavailable_without_reset(isolated_archive, monkeypatch):
    store = isolated_archive
    original = b'{"broken":'
    store.path.write_bytes(original)
    lifespan = _isolated_lifespan(monkeypatch)
    async def run():
        async with lifespan(FastAPI()):
            assert store.path.read_bytes() == original
            with pytest.raises(ArchiveUnavailable):
                store.snapshot()
    asyncio.run(run())
    assert store.path.read_bytes() == original
    assert store._lease is None
