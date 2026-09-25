"""Read-side behavior: hierarchy, immutable snapshots and cached indexed queries."""
import json
from pathlib import Path

import pytest

from app.point_archive.schema import ArchiveValidationError
from app.point_archive.store import ArchiveStore, RevisionConflict
from tests.point_archive_fixtures import archive_fixture


@pytest.fixture
def archive(tmp_path):
    raw = archive_fixture(4)
    raw["stations"].append({"id": "s2", "name": "第二站"})
    raw["bays"][0]["voltage_level"] = "110kV"
    raw["bays"].append({"id": "b2", "name": "第二间隔", "station_id": "s2", "voltage_level": "220kV"})
    raw["equipment"].append({"id": "e2", "name": "第二设备", "bay_id": "b2"})
    raw["points"][1].update(equipment_id="e2", assay_type=2, name="Temperature B")
    raw["points"][2].update(code="P00001", active=False)
    raw["points"][3].update(name="temperature A")
    store = ArchiveStore(tmp_path / "archive.json")
    store.initialize(raw)
    yield store
    store.close()


def ids(result):
    return [row["id"] for row in result["items"]]


def test_cached_reads_do_not_read_or_parse_file(archive, monkeypatch):
    def forbidden(*args, **kwargs):
        raise AssertionError("query reread/reparsed disk")
    monkeypatch.setattr(Path, "read_bytes", forbidden)
    monkeypatch.setattr(json, "loads", forbidden)
    assert archive.get("p1")["id"] == "p1"
    assert archive.meta()["counts"]["points"] == 4
    assert archive.list_points()["total"] == 4
    assert archive.tree()["total"] == 2
    assert archive.capture(["p1"])["revision"] == 1


def test_exact_code_duplicates_stable_order_and_name_casefold(archive):
    assert ids(archive.list_points(code="P00001")) == ["p1", "p3"]
    assert archive.list_points(code="P0000")["total"] == 0
    assert ids(archive.list_points(name="TEMPERATURE")) == ["p2", "p4"]


def test_hierarchy_and_intersected_filters(archive):
    for query in ({"station_id": "s2"}, {"bay_id": "b2"}, {"equipment_id": "e2"},
                  {"voltage_level": "220kV"}, {"assay_type": 2}):
        assert ids(archive.list_points(**query)) == ["p2"]
    assert archive.list_points(station_id="s1", equipment_id="e2")["total"] == 0
    assert archive.list_points(station_id="unknown")["total"] == 0
    assert ids(archive.list_entities("equipment", station_id="s2")) == ["e2"]
    assert ids(archive.list_entities("bays", station_id="s1")) == ["b1"]
    assert ids(archive.list_points(active=False)) == ["p3"]
    assert ids(archive.list_points(bound=True, bound_ids={"p1", "unknown"})) == ["p1"]
    assert ids(archive.list_points(bound=False, bound_ids={"p1", "p2", "p3"})) == ["p4"]


def test_pagination_revision_and_tree_levels(archive):
    assert ids(archive.list_points(page=1, page_size=2)) == ["p1", "p3"]
    assert ids(archive.list_points(page=2, page_size=2)) == ["p2", "p4"]
    assert archive.list_points(page=3, page_size=2)["items"] == []
    assert archive.list_points(page_size=1)["total"] == 4
    with pytest.raises(RevisionConflict):
        archive.list_points(revision=2)
    assert archive.tree(parent_type="station", parent_id="s1")["items"][0]["voltage_level"] == "110kV"
    assert ids(archive.tree(parent_type="voltage", parent_id="s2", voltage_level="220kV")) == ["b2"]
    assert ids(archive.tree(parent_type="bay", parent_id="b2")) == ["e2"]
    assert ids(archive.tree(parent_type="equipment", parent_id="e2")) == ["p2"]
    for options in ({"page": 0}, {"page_size": 0}, {"page_size": 201}):
        with pytest.raises(ArchiveValidationError):
            archive.list_points(**options)


def test_return_values_are_isolated_copies(archive):
    archive.snapshot()["points"][0]["name"] = "changed"
    archive.get("p1")["extensions"]["injected"] = True
    archive.list_points()["items"][0]["name"] = "changed"
    archive.capture(["p1"])["points"][0]["name"] = "changed"
    assert archive.get("p1")["name"] == "测点1"
    assert archive.get("p1")["extensions"] == {}
    assert archive.get("missing") is None


def test_capture_deduplicates_and_rejects_inactive_or_missing(archive):
    assert len(archive.capture(["p1", "p1"])["points"]) == 1
    for point_id in ("p3", "missing"):
        with pytest.raises(ArchiveValidationError):
            archive.capture([point_id])
    with pytest.raises(RevisionConflict):
        archive.capture(["p1"], expected_revision=2)


def test_corrupt_reload_retains_last_good_snapshot(archive):
    before = archive.snapshot()
    archive.path.write_text('{"broken":', encoding="utf-8")
    with pytest.raises(ArchiveValidationError):
        archive.load()
    assert archive.snapshot() == before
    assert archive.list_points()["total"] == 4


def test_preview_does_not_publish_or_mutate(archive):
    before = archive.snapshot()
    disk = archive.path.read_bytes()
    candidate = archive.snapshot()
    candidate["points"][0]["name"] = "renamed"
    candidate["points"].pop()
    preview = archive.preview(candidate)
    assert preview["changes"] == {"added": 0, "updated": 1, "removed": 1}
    assert archive.snapshot() == before
    assert archive.path.read_bytes() == disk

@pytest.mark.parametrize("options", [{"page": 0}, {"page_size": 0}, {"page_size": 201}])
def test_voltage_tree_rejects_invalid_pagination(archive, options):
    with pytest.raises(ArchiveValidationError):
        archive.tree(parent_type="station", parent_id="s1", **options)


def test_unspecified_voltage_node_does_not_include_other_voltages(archive):
    candidate = archive.snapshot()
    candidate["bays"].append({"id": "b3", "name": "无电压间隔", "station_id": "s1"})
    archive.publish(candidate, expected_revision=1)
    result = archive.tree(parent_type="voltage", parent_id="s1", voltage_level="")
    assert ids(result) == ["b3"]


def test_nested_json_copies_do_not_alias_inputs_or_cached_rows(archive):
    shared = {"values": [{"number": 1}], "labels": ["001", None, True, 2.5]}
    candidate = archive.snapshot()
    candidate["points"][0]["extensions"] = {"left": shared, "right": shared}
    archive.publish(candidate, expected_revision=1)
    shared["values"][0]["number"] = 99
    for output in (archive.snapshot()["points"][0], archive.get("p1"),
                   archive.list_points(code="P00001")["items"][0], archive.capture(["p1"])["points"][0]):
        assert output["extensions"]["left"]["values"][0]["number"] == 1
        output["extensions"]["left"]["values"][0]["number"] = 7
        assert output["extensions"]["right"]["values"][0]["number"] == 1
    assert archive.get("p1")["extensions"]["left"]["values"][0]["number"] == 1


def test_bound_exclusion_matches_full_and_narrowed_candidates(archive):
    assert ids(archive.list_points(bound=False, bound_ids=set())) == ["p1", "p3", "p2", "p4"]
    assert ids(archive.list_points(bound=False, bound_ids={"p1", "unknown"})) == ["p3", "p2", "p4"]
    assert ids(archive.list_points(bound=False, bound_ids={"p1"}, code="P00001")) == ["p3"]
    assert archive.list_points(bound=False, bound_ids={"p2"}, equipment_id="e2")["total"] == 0


def test_casefold_index_rebuilt_after_publication(archive):
    candidate = archive.snapshot()
    candidate["points"][0]["name"] = "Straße 温度"
    archive.publish(candidate, expected_revision=1)
    assert ids(archive.list_points(name="STRASSE")) == ["p1"]
    candidate = archive.snapshot()
    candidate["points"][0]["name"] = "New Name"
    archive.publish(candidate, expected_revision=2)
    assert archive.list_points(name="STRASSE")["total"] == 0
    assert ids(archive.list_points(name="NEW NAME")) == ["p1"]
