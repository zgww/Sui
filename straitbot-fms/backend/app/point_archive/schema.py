"""Strict JSON validation for the basic (non-relational) point archive."""
from datetime import datetime, timezone
import json
import math

MAX_BYTES = 32 * 1024 * 1024
MAX_POINTS = 10000
MAX_DEPTH = 32
COLLECTIONS = ("stations", "bays", "equipment", "points")


RELATION_KEYS = {"assaytypeid", "assaytypecloneid", "templateid", "templatebinding", "templatebindings",
                     "alarmtemplateid", "alarmtemplates", "templates", "clones", "cloneid",
                     "bindings", "binding", "waypointid", "waypointids", "steerpointid", "tracpointid",
                     "robotid", "actionid", "bound", "assaytypepoints", "metadataclone", "alarmsetclone"}

def copy_json(value):
    """Copy already validated JSON containers; immutable scalars may be shared.

    Only call after validation: cycles and arbitrary Python objects are not JSON.
    Each container occurrence is copied independently, including shared inputs.
    """
    if isinstance(value, dict):
        return {key: copy_json(item) for key, item in value.items()}
    if isinstance(value, list):
        return [copy_json(item) for item in value]
    return value


class ArchiveValidationError(ValueError):
    """A candidate archive cannot safely be published."""


def empty_snapshot():
    return {"schema_version": 1, "revision": 1,
            "updated_at": datetime.now(timezone.utc).isoformat(),
            "stations": [], "bays": [], "equipment": [], "points": []}


def _walk(value, path="$", depth=0):
    if depth > MAX_DEPTH:
        raise ArchiveValidationError(f"{path}: nesting exceeds {MAX_DEPTH}")
    if isinstance(value, dict):
        for key, item in value.items():
            if not isinstance(key, str):
                raise ArchiveValidationError(f"{path}: object keys must be strings")
            _walk(key, path, depth + 1)
            _walk(item, f"{path}.{key}", depth + 1)
    elif isinstance(value, list):
        for index, item in enumerate(value):
            _walk(item, f"{path}[{index}]", depth + 1)
    elif isinstance(value, float):
        if not math.isfinite(value):
            raise ArchiveValidationError(f"{path}: non-finite number")
    elif isinstance(value, str):
        try:
            value.encode("utf-8")
        except UnicodeEncodeError as exc:
            raise ArchiveValidationError(f"{path}: invalid Unicode") from exc
    elif value is not None and type(value) not in (int, bool):
        raise ArchiveValidationError(f"{path}: unsupported JSON value")


def reject_relations(value, path="$"):
    """Relations belong to separate services; do not silently flatten an export."""
    if isinstance(value, dict):
        for key, item in value.items():
            if key.replace("_", "").lower() in RELATION_KEYS and item not in (None, "", False, [], {}):
                raise ArchiveValidationError(f"{path}.{key}: relationship export is not supported; import basic archive data only")
            reject_relations(item, f"{path}.{key}")
    elif isinstance(value, list):
        for index, item in enumerate(value):
            reject_relations(item, f"{path}[{index}]")


def _text(item, key, path, required=False, limit=1024):
    if key not in item:
        if required:
            raise ArchiveValidationError(f"{path}.{key}: required")
        return
    value = item[key]
    if not isinstance(value, str) or len(value) > limit or (required and not value.strip()):
        raise ArchiveValidationError(f"{path}.{key}: expected {'nonempty ' if required else ''}string, max {limit} characters")


def _integer(value, path, low, high):
    if type(value) is not int or not low <= value <= high:
        raise ArchiveValidationError(f"{path}: expected integer in {low}..{high}")


def validate_snapshot(raw):
    if not isinstance(raw, dict):
        raise ArchiveValidationError("archive must be an object")
    _walk(raw)
    try:
        size = len(json.dumps(raw, ensure_ascii=False, allow_nan=False).encode("utf-8"))
    except (ValueError, TypeError, OverflowError) as exc:
        raise ArchiveValidationError("invalid JSON data") from exc
    if size > MAX_BYTES:
        raise ArchiveValidationError("archive exceeds 32 MiB")
    _integer(raw.get("schema_version"), "schema_version", 1, 2)
    _integer(raw.get("revision"), "revision", 1, 2**63 - 1)
    reject_relations(raw)
    if raw["schema_version"] == 2:
        from .catalog import validate_catalog
        return validate_catalog(raw)
    result = copy_json(raw)
    if "source" in result and not isinstance(result["source"], dict):
        raise ArchiveValidationError("source must be an object")
    _text(result, "updated_at", "$", limit=128)
    ids = {}
    from .legacy import _normalize_copied_point
    for kind in COLLECTIONS:
        values = result.get(kind)
        if not isinstance(values, list) or len(values) > MAX_POINTS:
            raise ArchiveValidationError(f"{kind}: expected array of at most {MAX_POINTS} items")
        seen = set()
        for index, original in enumerate(values):
            path = f"{kind}[{index}]"
            if not isinstance(original, dict):
                raise ArchiveValidationError(f"{path}: expected object")
            item = _normalize_copied_point(original) if kind == "points" else original
            values[index] = item
            _text(item, "id", path, required=True, limit=256)
            _text(item, "name", path, required=True, limit=256)
            _text(item, "code", path, limit=256)
            if item["id"] in seen:
                raise ArchiveValidationError(f"{path}.id: duplicate {item['id']}")
            seen.add(item["id"])
            if "active" in item and type(item["active"]) is not bool:
                raise ArchiveValidationError(f"{path}.active: expected boolean")
            if "extensions" in item and not isinstance(item["extensions"], dict):
                raise ArchiveValidationError(f"{path}.extensions: expected object")
            if kind == "bays":
                _text(item, "voltage_level", path, limit=128)
            if kind == "points":
                item.setdefault("active", True)
                item.setdefault("assay_type", 1)
                item.setdefault("times", 1)
                item.setdefault("code", "")
                _integer(item["assay_type"], f"{path}.assay_type", 1, 5)
                _integer(item["times"], f"{path}.times", 1, 1000)
                if item.get("meter_type") is not None:
                    _integer(item["meter_type"], f"{path}.meter_type", 0, 2**31 - 1)
                for key in ("scope", "warn_setting", "unit", "source_id", "created_at", "updated_at"):
                    _text(item, key, path, limit=4096)
                if "position" in item and item["position"] is not None and not isinstance(item["position"], (str, dict, list)):
                    raise ArchiveValidationError(f"{path}.position: expected string, coordinates or null")
        ids[kind] = seen
    # Fixed entity-kind edges are acyclic even where IDs match across kinds.
    for kind, parent, key in (("bays", "stations", "station_id"), ("equipment", "bays", "bay_id"), ("points", "equipment", "equipment_id")):
        for index, item in enumerate(result[kind]):
            path = f"{kind}[{index}]"
            _text(item, key, path, required=True, limit=256)
            if item[key] not in ids[parent]:
                raise ArchiveValidationError(f"{path}.{key}: unknown {parent} ID {item[key]}")
    return result


def decode_snapshot(raw, *, validate=True):
    if not isinstance(raw, (bytes, str)):
        raise ArchiveValidationError("archive must be UTF-8 JSON bytes or text")
    try:
        encoded = raw if isinstance(raw, bytes) else raw.encode("utf-8")
        if len(encoded) > MAX_BYTES:
            raise ArchiveValidationError("archive exceeds 32 MiB")
        text = encoded.decode("utf-8")
        def pairs(items):
            result = {}
            for key, value in items:
                if key in result:
                    raise ArchiveValidationError(f"duplicate JSON key: {key}")
                result[key] = value
            return result
        def constant(value):
            raise ArchiveValidationError(f"invalid JSON number: {value}")
        parsed = json.loads(text, object_pairs_hook=pairs, parse_constant=constant)
        if validate:
            return validate_snapshot(parsed)
        _walk(parsed)
        return parsed
    except ArchiveValidationError:
        raise
    except (UnicodeError, RecursionError, ValueError, OverflowError) as exc:
        raise ArchiveValidationError(f"invalid archive JSON: {exc}") from exc
