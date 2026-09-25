"""Explicit legacy Point aliases; never derive parent IDs from ID prefixes."""
from copy import deepcopy
from .schema import ArchiveValidationError, reject_relations

ALIASES = {"equipmentId": "equipment_id", "assayType": "assay_type", "meterType": "meter_type",
           "warnSetting": "warn_setting", "createTime": "created_at", "updateTime": "updated_at"}
FIELDS = {"directory_id", "id", "name", "code", "equipment_id", "assay_type", "meter_type", "warn_setting", "created_at",
          "updated_at", "active", "position", "times", "scope", "unit", "source_id", "extensions"}


def normalize_legacy_point(raw):
    if not isinstance(raw, dict):
        raise ArchiveValidationError("point must be an object")
    reject_relations(raw)
    return _normalize_copied_point(deepcopy(raw))


def _normalize_copied_point(result):
    """Internal: the full archive has already been validated and copied once."""
    for old, new in ALIASES.items():
        if old in result:
            value = result.pop(old)
            if new in result and (result[new] != value or type(result[new]) is not type(value)):
                raise ArchiveValidationError(f"conflicting point fields: {old} and {new}")
            result[new] = value
    if "isDelete" in result:
        value = result.pop("isDelete")
        if type(value) is not int or value not in (0, 1):
            raise ArchiveValidationError("isDelete must be integer 0 or 1 (1 means active)")
        active = value == 1
        if "active" in result and (type(result["active"]) is not bool or result["active"] != active):
            raise ArchiveValidationError("conflicting isDelete and active")
        result["active"] = active
    extensions = result.setdefault("extensions", {})
    if not isinstance(extensions, dict):
        raise ArchiveValidationError("point.extensions must be an object")
    for key in list(result):
        if key not in FIELDS:
            if key in extensions and (extensions[key] != result[key] or type(extensions[key]) is not type(result[key])):
                raise ArchiveValidationError(f"conflicting extension field: {key}")
            extensions[key] = result.pop(key)
    if "id" in result:
        result.setdefault("source_id", result["id"])
    return result
