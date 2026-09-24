"""Portable, arbitrary-depth archive directories. No project runtime bindings."""
from collections import defaultdict
from hashlib import sha256

from .schema import ArchiveValidationError, copy_json, _text, _integer, MAX_POINTS

FORMAT = "straitbot.point-archive"
ROLES = ("custom", "station", "voltage", "bay", "equipment")


def validate_catalog(raw):
    # Envelope, JSON safety and limits have already been checked by schema.
    result = copy_json(raw)
    from .legacy import _normalize_copied_point
    directories = result.get("directories")
    points = result.get("points")
    if not isinstance(directories, list) or len(directories) > MAX_POINTS:
        raise ArchiveValidationError("directories: 最多10000个目录")
    if not isinstance(points, list) or len(points) > MAX_POINTS:
        raise ArchiveValidationError("points: 最多10000个测点")
    for kind in ("stations", "bays", "equipment"):
        if result.get(kind):
            raise ArchiveValidationError("新版档案请使用 directories，不能混合旧版层级")
        result[kind] = []
    ids = {}
    for i, row in enumerate(directories):
        path = f"directories[{i}]"
        if not isinstance(row, dict):
            raise ArchiveValidationError(f"{path}: 必须为对象")
        for key in ("id", "name"):
            _text(row, key, path, required=True, limit=256)
        _text(row, "code", path, limit=256)
        if row["id"] in ids:
            raise ArchiveValidationError(f"重复目录ID：{row['id']}")
        if not isinstance(row.get("role", "custom"), str) or row.get("role", "custom") not in ROLES:
            raise ArchiveValidationError(f"{path}.role: 未知平台层级类型")
        row.setdefault("role", "custom")
        row.setdefault("parent_id", None)
        if row["parent_id"] is not None:
            _text(row, "parent_id", path, required=True, limit=256)
        ids[row["id"]] = row
    # Iterative tri-color walk, O(n); graph depth is not JSON nesting depth.
    done = set()
    for start in ids:
        cursor, chain = start, set()
        while cursor is not None and cursor not in done:
            if cursor not in ids:
                raise ArchiveValidationError(f"目录父节点不存在：{cursor}")
            if cursor in chain:
                raise ArchiveValidationError(f"目录不能循环引用：{cursor}")
            chain.add(cursor)
            cursor = ids[cursor]["parent_id"]
        done.update(chain)
    seen = set()
    for i, original in enumerate(points):
        if not isinstance(original, dict):
            raise ArchiveValidationError(f"points[{i}]: 必须为对象")
        row = _normalize_copied_point(original)
        points[i] = row
        path = f"points[{i}]"
        for key in ("id", "name"):
            _text(row, key, path, required=True, limit=256)
        if row["id"] in seen:
            raise ArchiveValidationError(f"重复测点ID：{row['id']}")
        seen.add(row["id"])
        row.setdefault("directory_id", None)
        if row["directory_id"] is not None:
            _text(row, "directory_id", path, required=True, limit=256)
            if row["directory_id"] not in ids:
                raise ArchiveValidationError(f"{path}: 所属目录不存在")
        row.setdefault("active", True)
        if type(row["active"]) is not bool:
            raise ArchiveValidationError(f"{path}.active: 必须为布尔值")
        row.setdefault("code", "")
        row.setdefault("assay_type", 1)
        row.setdefault("times", 1)
        _integer(row["assay_type"], path + ".assay_type", 1, 5)
        _integer(row["times"], path + ".times", 1, 1000)
        if row.get("meter_type") is not None:
            _integer(row["meter_type"], path + ".meter_type", 0, 2**31 - 1)
        for key in ("code", "scope", "unit", "warn_setting", "source_id", "created_at", "updated_at"):
            _text(row, key, path, limit=4096)
        if row.get("position") is not None and not isinstance(row["position"], (str, dict, list)):
            raise ArchiveValidationError(f"{path}.position: 必须为位置对象、数组、字符串或null")
    return result


def as_catalog(document):
    """Non-writing v1 projection; point IDs and unknown fields survive migration."""
    if document["schema_version"] == 2:
        return copy_json(document)
    result = {"schema_version": 2, "revision": document["revision"], "directories": [],
              "points": copy_json(document["points"]), "stations": [], "bays": [], "equipment": []}
    directories = result["directories"]
    # Prefix legacy kind since legacy IDs may overlap between entity tables.
    def key(kind, value):
        return kind + ":" + sha256(value.encode("utf-8")).hexdigest()
    for s in document["stations"]:
        directories.append({**copy_json(s), "id": key("station", s["id"]), "parent_id": None,
                            "role": "station", "legacy_id": s["id"]})
    voltages = set()
    for b in document["bays"]:
        voltage = b.get("voltage_level", "")
        token = b["station_id"] + "\0" + voltage
        voltage_id = key("voltage", token)
        if voltage_id not in voltages:
            directories.append({"id": voltage_id, "parent_id": key("station", b["station_id"]),
                                "name": voltage or "未设置电压等级", "role": "voltage", "code": voltage})
            voltages.add(voltage_id)
        directories.append({**copy_json(b), "id": key("bay", b["id"]), "parent_id": voltage_id,
                            "role": "bay", "legacy_id": b["id"]})
    for e in document["equipment"]:
        directories.append({**copy_json(e), "id": key("equipment", e["id"]),
                            "parent_id": key("bay", e["bay_id"]), "role": "equipment", "legacy_id": e["id"]})
    for p in result["points"]:
        p["directory_id"] = key("equipment", p.pop("equipment_id"))
    for field in ("source", "updated_at"):
        if field in document:
            result[field] = copy_json(document[field])
    return result


def portable(document):
    doc = as_catalog(document)
    return {"format": FORMAT, "schema_version": 2,
            "directories": doc["directories"], "points": doc["points"]}


def from_portable(raw):
    if not isinstance(raw, dict):
        raise ArchiveValidationError("档案必须为JSON对象")
    if "format" in raw:
        if raw["format"] != FORMAT or raw.get("schema_version") != 2:
            raise ArchiveValidationError("不支持的静态档案格式或版本")
        if set(raw) - {"format", "schema_version", "directories", "points"}:
            raise ArchiveValidationError("静态档案仅允许format、schema_version、directories、points")
        raw = {**raw, "revision": 1}
        raw.pop("format")
    from .schema import validate_snapshot
    return as_catalog(validate_snapshot(raw))


def platform_check(document):
    doc = as_catalog(document)
    ids = {d["id"]: d for d in doc["directories"]}
    expected = {"station": None, "voltage": "station", "bay": "voltage", "equipment": "bay"}
    issues = []
    labels = {"station": "变电站", "voltage": "电压等级", "bay": "间隔", "equipment": "设备"}
    for d in ids.values():
        parent = ids.get(d["parent_id"])
        role = d["role"]
        if role not in expected:
            message = "普通目录未指定平台层级，请选择变电站、电压等级、间隔或设备"
        elif (parent["role"] if parent else None) != expected[role]:
            message = f"{labels[role]}应位于{labels.get(expected[role], '根目录')}下"
        else:
            continue
        issues.append({"id": d["id"], "name": d["name"], "kind": "directory", "message": message})
    for p in doc["points"]:
        parent = ids.get(p["directory_id"])
        if parent is None or parent["role"] != "equipment":
            issues.append({"id": p["id"], "name": p["name"], "kind": "point", "message": "测点必须直属设备目录"})
    return {"valid": not issues, "revision": doc["revision"], "issues": issues,
            "message": "层级校验通过；未向平台发送数据" if not issues else "请调整以下层级后再同步，日常维护不受影响"}


def catalog_index(document):
    doc = document if document["schema_version"] == 2 else as_catalog(document)
    ids = {d["id"]: d for d in doc["directories"]}
    children = defaultdict(list)
    for d in ids.values():
        children[d["parent_id"]].append(d["id"])
    direct = defaultdict(int)
    for p in doc["points"]:
        direct[p["directory_id"]] += 1
    return doc, ids, children, direct
