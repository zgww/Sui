"""Publication failure and concurrency regressions for durable archive revisions."""
from concurrent.futures import ThreadPoolExecutor
import json
from pathlib import Path
import subprocess
import sys
import threading

import pytest

from app.point_archive.store import ArchiveStore, ArchiveUnavailable, ReferencedPointError, RevisionConflict
from tests.point_archive_fixtures import archive_fixture


@pytest.fixture
def archive(tmp_path):
    store = ArchiveStore(tmp_path / "archive.json")
    store.acquire_writer()
    store.initialize(archive_fixture(2))
    yield store
    store.close()


def test_publication_preserves_prior_revision_and_input(archive):
    before = archive.snapshot()
    candidate = archive.snapshot()
    candidate["points"][0]["name"] = "new name"
    assert archive.publish(candidate, expected_revision=1) == 2
    assert candidate["revision"] == 1
    assert archive.revision == 2
    assert archive.get("p1")["name"] == "new name"
    backup = archive.path.parent / "revisions" / "archive-0000000001.json"
    assert json.loads(backup.read_text(encoding="utf-8")) == before
    restarted = ArchiveStore(archive.path)
    restarted.load()
    assert restarted.snapshot() == archive.snapshot()


@pytest.mark.parametrize("failure_target", ["backup", "main"])
def test_replace_failure_preserves_old_disk_and_cache(archive, monkeypatch, failure_target):
    import app.point_archive.store as module
    before = archive.snapshot()
    disk = archive.path.read_bytes()
    original = module.os.replace
    def failed_replace(source, destination):
        is_main = Path(destination) == archive.path
        if is_main == (failure_target == "main"):
            raise OSError(f"injected {failure_target} rename failure")
        return original(source, destination)
    monkeypatch.setattr(module.os, "replace", failed_replace)
    candidate = archive.snapshot()
    candidate["points"][0]["name"] = "unpublished"
    with pytest.raises(OSError):
        archive.publish(candidate, expected_revision=1)
    assert archive.snapshot() == before
    assert archive.path.read_bytes() == disk
    assert not list(archive.path.parent.rglob(".archive-*.tmp"))


def test_post_rename_activation_failure_recovers_authoritative_disk(archive, monkeypatch):
    def fail(state):
        raise RuntimeError("activation failed after rename")
    monkeypatch.setattr(archive, "_activate", fail)
    candidate = archive.snapshot()
    candidate["points"][0]["name"] = "committed on disk"
    with pytest.raises(RuntimeError):
        archive.publish(candidate, expected_revision=1)
    assert archive.revision == 2
    assert archive.get("p1")["name"] == "committed on disk"
    assert json.loads(archive.path.read_text(encoding="utf-8")) == archive.snapshot()
    with pytest.raises(RevisionConflict):
        archive.publish(candidate, expected_revision=1)


def test_failed_recovery_after_commit_fails_closed(archive, monkeypatch):
    def fail(state):
        archive.path.write_text("corrupted", encoding="utf-8")
        raise OSError("simulated storage fault")
    monkeypatch.setattr(archive, "_activate", fail)
    with pytest.raises(OSError):
        archive.publish(archive.snapshot(), expected_revision=1)
    with pytest.raises(ArchiveUnavailable):
        archive.snapshot()
    with pytest.raises(ArchiveUnavailable):
        archive.publish(archive_fixture(), expected_revision=1)


def test_concurrent_same_revision_has_one_winner(archive):
    barrier = threading.Barrier(2)
    def publish(name):
        candidate = archive.snapshot()
        candidate["points"][0]["name"] = name
        barrier.wait(timeout=5)
        try:
            return archive.publish(candidate, expected_revision=1)
        except RevisionConflict:
            return "conflict"
    with ThreadPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(publish, name) for name in ("writer A", "writer B")]
        results = [future.result(timeout=10) for future in futures]
    assert sorted(map(str, results)) == ["2", "conflict"]
    assert archive.revision == 2
    assert archive.get("p1")["name"] in {"writer A", "writer B"}


def test_referenced_deletion_denied_but_deactivation_preserves_history(archive):
    candidate = archive.snapshot()
    candidate["points"].pop(0)
    with pytest.raises(ReferencedPointError):
        archive.publish(candidate, expected_revision=1, referenced_ids={"p1"})
    assert archive.revision == 1
    candidate = archive.snapshot()
    candidate["points"][0]["active"] = False
    assert archive.publish(candidate, expected_revision=1, referenced_ids={"p1"}) == 2
    assert archive.get("p1")["active"] is False


def test_writer_lease_excludes_second_store_and_releases(archive):
    other = ArchiveStore(archive.path)
    try:
        with pytest.raises(ArchiveUnavailable):
            other.acquire_writer()
        archive.close()
        other.acquire_writer()
    finally:
        other.close()


def test_writer_lease_excludes_another_process(archive):
    script = """
import sys
from pathlib import Path
from app.point_archive.store import ArchiveStore, ArchiveUnavailable
store = ArchiveStore(Path(sys.argv[1]))
try:
    store.acquire_writer()
except ArchiveUnavailable:
    print('writer-blocked')
else:
    store.close()
    sys.exit(2)
"""
    result = subprocess.run([sys.executable, "-c", script, str(archive.path)],
                            cwd=Path(__file__).resolve().parents[1], capture_output=True, text=True, timeout=15)
    assert result.returncode == 0, result.stderr
    assert "writer-blocked" in result.stdout


def test_republication_preserves_legacy_source_and_extensions(archive):
    candidate = archive.snapshot()
    candidate["source"] = {"system": "legacy-platform", "export_revision": "0007"}
    candidate["points"][0].update(source_id="0000123", extensions={"sensorType": "temperature", "vendor": {"code": "0004"}})
    candidate["points"][0]["created_at"] = "2026-09-17 12:00:00"
    archive.publish(candidate, expected_revision=1)
    first = archive.snapshot()
    assert archive.preview(first)["changes"] == {"added": 0, "removed": 0, "updated": 0}
    archive.publish(first, expected_revision=2)
    second = archive.snapshot()
    assert second["source"] == first["source"]
    assert second["points"] == first["points"]
    assert second["points"][0]["source_id"] == "0000123"
    reloaded = ArchiveStore(archive.path)
    reloaded.load()
    assert reloaded.snapshot() == second
