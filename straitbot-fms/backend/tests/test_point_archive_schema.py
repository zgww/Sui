"""Validation regressions for untrusted archive imports."""
import json
import unittest

from app.point_archive.schema import ArchiveValidationError, decode_snapshot, validate_snapshot
from app.point_archive.legacy import normalize_legacy_point
from tests.point_archive_fixtures import archive_fixture


class SchemaTests(unittest.TestCase):
    def test_valid_is_deep_copied_and_defaults(self):
        raw = archive_fixture()
        del raw["points"][0]["active"]
        result = validate_snapshot(raw)
        self.assertTrue(result["points"][0]["active"])
        self.assertNotIn("active", raw["points"][0])

    def test_zero_ids_duplicate_codes_and_cross_kind_ids(self):
        raw = archive_fixture(2)
        raw["stations"][0]["id"] = "0001"
        raw["bays"][0]["station_id"] = "0001"
        raw["points"][1]["code"] = raw["points"][0]["code"]
        raw["points"][0]["id"] = "0001"
        self.assertEqual(validate_snapshot(raw)["points"][0]["id"], "0001")

    def test_invalid_fields(self):
        for key, value in [("id", 1), ("name", " "), ("active", 1), ("assay_type", True),
                           ("assay_type", 6), ("times", 0), ("times", 1001), ("code", 42),
                           ("equipment_id", "missing"), ("meter_type", "1")]:
            with self.subTest(key=key, value=value):
                raw = archive_fixture()
                raw["points"][0][key] = value
                with self.assertRaises(ArchiveValidationError):
                    validate_snapshot(raw)

    def test_duplicate_id_or_invalid_revision(self):
        raw = archive_fixture(2)
        raw["points"][1]["id"] = "p1"
        with self.assertRaises(ArchiveValidationError):
            validate_snapshot(raw)
        for key, value in [("schema_version", True), ("schema_version", 2), ("revision", 0), ("revision", True)]:
            raw = archive_fixture()
            raw[key] = value
            with self.assertRaises(ArchiveValidationError):
                validate_snapshot(raw)

    def test_decode_rejects_malformed_json_and_duplicates(self):
        for value in [b"\xff", '{"points":[],"points":[]}', '{"x":NaN}', '{"x":Infinity}', '[]', '{', '[' * 80 + '0' + ']' * 80]:
            with self.subTest(value=str(value)[:80]), self.assertRaises(ArchiveValidationError):
                decode_snapshot(value)

    def test_limits_and_nested_finite(self):
        raw = archive_fixture(10001)
        with self.assertRaises(ArchiveValidationError):
            validate_snapshot(raw)
        raw = archive_fixture()
        raw["points"][0]["extensions"] = {"nested": [float("inf")]}
        with self.assertRaises(ArchiveValidationError):
            validate_snapshot(raw)
        with self.assertRaises(ArchiveValidationError):
            decode_snapshot(b" " * (32 * 1024 * 1024 + 1))

    def test_legacy_aliases_and_extensions(self):
        result = normalize_legacy_point({"id": "0001", "name": "表计", "equipmentId": "e1", "assayType": 2,
                                         "isDelete": 0, "sensorType": "temperature", "position": "1,2"})
        self.assertEqual(result["equipment_id"], "e1")
        self.assertEqual(result["source_id"], "0001")
        self.assertFalse(result["active"])
        self.assertEqual(result["extensions"]["sensorType"], "temperature")
        for value in [True, 2, "1", None]:
            with self.assertRaises(ArchiveValidationError):
                normalize_legacy_point({"id": "x", "isDelete": value})

    def test_relation_exports_and_conflicting_aliases_rejected(self):
        for key in ["assayTypeId", "assayTypeCloneId", "template_id", "waypoint_id", "binding"]:
            raw = archive_fixture()
            raw["points"][0][key] = "relation"
            with self.assertRaises(ArchiveValidationError):
                validate_snapshot(raw)
        with self.assertRaises(ArchiveValidationError):
            normalize_legacy_point({"equipmentId": "e1", "equipment_id": "e2"})

    def test_all_hierarchy_edges_reject_orphans(self):
        for kind, key in [("bays", "station_id"), ("equipment", "bay_id"), ("points", "equipment_id")]:
            raw = archive_fixture()
            raw[kind][0][key] = "missing"
            with self.assertRaises(ArchiveValidationError):
                validate_snapshot(raw)

    def test_maximum_population_valid(self):
        self.assertEqual(len(validate_snapshot(archive_fixture(10000))["points"]), 10000)

    def test_cycle_invalid_unicode_and_non_json_objects(self):
        for value in [set(), b"bytes", "\ud800"]:
            raw = archive_fixture()
            raw["vendor"] = value
            with self.assertRaises(ArchiveValidationError):
                validate_snapshot(raw)
        raw = archive_fixture()
        raw["cycle"] = raw
        with self.assertRaises(ArchiveValidationError):
            validate_snapshot(raw)

    def test_legacy_extension_collision_rejected(self):
        with self.assertRaises(ArchiveValidationError):
            normalize_legacy_point({"vendor": "new", "extensions": {"vendor": "old"}})
        with self.assertRaises(ArchiveValidationError):
            normalize_legacy_point({"isDelete": 1, "active": False})

    def test_json_roundtrip_preserves_unknown_data(self):
        raw = archive_fixture()
        raw["vendor"] = {"zero": "000"}
        raw["points"][0]["extra"] = {"flag": True}
        result = decode_snapshot(json.dumps(raw))
        self.assertEqual(result["vendor"], raw["vendor"])
        self.assertEqual(result["points"][0]["extensions"]["extra"], {"flag": True})


if __name__ == "__main__":
    unittest.main()
