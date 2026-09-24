"""Single-writer JSON archive. Reads use one immutable-by-convention snapshot."""
from __future__ import annotations

import json
import os
import tempfile
import threading
from collections import defaultdict
from datetime import datetime, timezone
from pathlib import Path

from .schema import ArchiveValidationError, decode_snapshot, validate_snapshot, copy_json

KINDS = ("stations", "bays", "equipment", "points")


class RevisionConflict(ValueError):
    pass


class ReferencedPointError(ValueError):
    pass


class ArchiveUnavailable(RuntimeError):
    pass


class ArchiveStore:
    def __init__(self, path: Path):
        self.path = Path(path)
        self.lock = threading.RLock()
        self._state = None
        self._lease = None
        self.last_error = None

    def acquire_writer(self):
        """Process-lifetime lease: fail closed if another worker owns the file."""
        if self._lease is not None:
            return
        self.path.parent.mkdir(parents=True, exist_ok=True)
        lease = (self.path.parent / ".writer.lock").open("a+b")
        try:
            if os.name == "nt":
                import msvcrt
                lease.seek(0)
                if lease.read(1) == b"":
                    lease.write(b"0")
                    lease.flush()
                lease.seek(0)
                msvcrt.locking(lease.fileno(), msvcrt.LK_NBLCK, 1)
            else:
                import fcntl
                fcntl.flock(lease.fileno(), fcntl.LOCK_EX | fcntl.LOCK_NB)
        except OSError as exc:
            lease.close()
            raise ArchiveUnavailable("测点档案仅支持一个后端写入进程，请检查 worker/副本数量") from exc
        self._lease = lease

    def close(self):
        if self._lease is not None:
            self._lease.close()
            self._lease = None

    def _ready(self):
        state = self._state
        if state is None:
            raise ArchiveUnavailable(self.last_error or "测点档案尚未加载")
        return state

    @property
    def revision(self):
        return self._ready()[0]["revision"]

    @staticmethod
    def _build(document):
        ids = {kind: {row["id"]: row for row in document[kind]} for kind in KINDS}
        order = {kind: sorted(document[kind], key=lambda r: (r.get("code", ""), r["id"])) for kind in KINDS}
        groups = {key: defaultdict(set) for key in ("equipment_id", "bay_id", "station_id", "voltage_level", "assay_type", "code")}
        folded_names = {kind: {row["id"]: row["name"].casefold() for row in document[kind]} for kind in KINDS}
        named_order = {kind: [(folded_names[kind][row["id"]], row) for row in order[kind]] for kind in KINDS}
        ancestry = {}
        if document["schema_version"] == 2:
            from .catalog import catalog_index
            catalog = catalog_index(document)
            ids["directories"] = catalog[1]
            return document, {"ids": ids, "order": order, "groups": groups, "ancestry": ancestry, "catalog": catalog, "folded_names": folded_names, "named_order": named_order}
        for p in order["points"]:
            e = ids["equipment"][p["equipment_id"]]
            b = ids["bays"][e["bay_id"]]
            attrs = {"equipment_id": e["id"], "bay_id": b["id"], "station_id": b["station_id"],
                     "voltage_level": b.get("voltage_level", ""), "assay_type": p.get("assay_type"), "code": p.get("code", "")}
            ancestry[p["id"]] = attrs
            for key, value in attrs.items():
                groups[key][value].add(p["id"])
        return document, {"ids": ids, "order": order, "groups": groups, "ancestry": ancestry, "folded_names": folded_names, "named_order": named_order}

    def _activate(self, state):
        self._state = state
        self.last_error = None

    def initialize(self, raw):
        with self.lock:
            if self.path.exists():
                raise RevisionConflict("档案已存在，不能重新初始化")
            doc = validate_snapshot(raw)
            state = self._build(doc)
            self._write_atomic(self.path, doc)
            self._activate(state)

    def load(self):
        with self.lock:
            # On a failed manual reload retain the previously valid in-memory data.
            doc = decode_snapshot(self.path.read_bytes())
            state = self._build(doc)
            self._activate(state)

    def snapshot(self):
        return copy_json(self._ready()[0])

    def meta(self):
        doc, _ = self._ready()
        return {"revision": doc["revision"], "schema_version": doc["schema_version"],
                "updated_at": doc.get("updated_at"), "source": copy_json(doc.get("source", {})),
                "counts": {k: len(doc[k]) for k in KINDS}, "status": "ready"}

    def get(self, point_id):
        return self.get_entity("points", point_id)

    def get_entity(self, kind, item_id):
        if kind not in (*KINDS, "directories"):
            raise ArchiveValidationError("未知档案类型")
        return copy_json(self._ready()[1]["ids"][kind].get(item_id))

    def capture(self, point_ids, expected_revision=None):
        with self.lock:
            doc, idx = self._ready()
            self._check_revision(doc, expected_revision)
            rows = []
            for pid in dict.fromkeys(point_ids):
                point = idx["ids"]["points"].get(pid)
                if not point or not point.get("active", True):
                    raise ArchiveValidationError(f"测点不存在或已停用：{pid}")
                rows.append(copy_json(point))
            return {"revision": doc["revision"], "points": rows}

    @staticmethod
    def _check_revision(doc, expected):
        if expected is not None and expected != doc["revision"]:
            raise RevisionConflict("档案已被其他操作更新，请刷新后重试")

    def list_points(self, **kwargs):
        return self.list_entities("points", **kwargs)

    def list_entities(self, kind, *, name=None, code=None, station_id=None, bay_id=None,
                      equipment_id=None, voltage_level=None, assay_type=None, active=None,
                      bound=None, bound_ids=None, page=1, page_size=50, revision=None):
        if kind not in KINDS:
            raise ArchiveValidationError("未知档案类型")
        if page < 1 or not 1 <= page_size <= 200:
            raise ArchiveValidationError("页码必须大于0，页长须为1到200")
        doc, idx = self._ready()
        self._check_revision(doc, revision)
        if doc["schema_version"] == 2 and kind == "points":
            return self.catalog_points(name=name, code=code, active=active, bound=bound, bound_ids=bound_ids, page=page, page_size=page_size, revision=revision)
        rows = idx["order"][kind]
        filters = {"code": code, "equipment_id": equipment_id, "bay_id": bay_id,
                   "station_id": station_id, "voltage_level": voltage_level, "assay_type": assay_type}
        selected = None
        if kind == "points":
            for key, value in filters.items():
                if value is not None and (value != "" or key == "voltage_level"):
                    matches = idx["groups"][key].get(value, set())
                    selected = set(matches) if selected is None else selected & matches
            if bound is True:
                matches = set(bound_ids or ())
                selected = matches if selected is None else selected & matches
            elif bound is False and bound_ids:
                if selected is None:
                    rows = [row for row in rows if row["id"] not in bound_ids]
                else:
                    selected = selected - set(bound_ids)
            if selected is not None:
                if len(selected) > len(rows) // 2:
                    rows = [row for row in rows if row["id"] in selected]
                else:
                    rows = sorted((idx["ids"][kind][pid] for pid in selected if pid in idx["ids"][kind]),
                                  key=lambda r: (r.get("code", ""), r["id"]))
        else:
            def match(row):
                if code and row.get("code") != code:
                    return False
                if kind == "stations":
                    return not station_id or row["id"] == station_id
                bay = row if kind == "bays" else idx["ids"]["bays"][row["bay_id"]]
                return ((not station_id or bay["station_id"] == station_id)
                        and (not bay_id or bay["id"] == bay_id)
                        and (voltage_level is None or bay.get("voltage_level", "") == voltage_level)
                        and (kind != "equipment" or not equipment_id or row["id"] == equipment_id))
            rows = [row for row in rows if match(row)]
        if name:
            needle = name.casefold()
            if rows is idx["order"][kind]:
                rows = [row for folded, row in idx["named_order"][kind] if needle in folded]
            else:
                names = idx["folded_names"][kind]
                rows = [row for row in rows if needle in names[row["id"]]]
        if active is not None:
            rows = [row for row in rows if row.get("active", True) == active]
        total = len(rows)
        items = copy_json(rows[(page-1)*page_size:page*page_size])
        for row in items:
            if kind == "points":
                row["parent_name"] = idx["ids"]["equipment"][row["equipment_id"]]["name"]
                row["bound"] = row["id"] in (bound_ids or set())
            elif kind == "equipment":
                row["parent_name"] = idx["ids"]["bays"][row["bay_id"]]["name"]
            elif kind == "bays":
                row["parent_name"] = idx["ids"]["stations"][row["station_id"]]["name"]
        return {"revision": doc["revision"], "total": total, "page": page, "page_size": page_size, "items": items}

    def tree(self, parent_type="root", parent_id=None, voltage_level=None, page=1, page_size=50):
        # Hold a single revision while deriving levels and their child counts.
        if page < 1 or not 1 <= page_size <= 200:
            raise ArchiveValidationError("页码必须大于0，页长须为1到200")
        with self.lock:
            doc, _ = self._ready()
            if parent_type == "station":
                values = sorted({b.get("voltage_level", "") for b in doc["bays"] if b["station_id"] == parent_id})
                nodes = [{"id": parent_id, "station_id": parent_id, "voltage_level": v,
                          "name": v or "未设置电压等级", "type": "voltage", "has_children": True} for v in values]
            else:
                table = {"root": ("stations", "station", {}),
                         "voltage": ("bays", "bay", {"station_id": parent_id, "voltage_level": voltage_level}),
                         "bay": ("equipment", "equipment", {"bay_id": parent_id}),
                         "equipment": ("points", "point", {"equipment_id": parent_id})}
                if parent_type not in table:
                    raise ArchiveValidationError("未知树节点类型")
                kind, node_type, filters = table[parent_type]
                result = self.list_entities(kind, page=page, page_size=page_size, **filters)
                for r in result["items"]:
                    r["type"] = node_type
                    r["has_children"] = node_type != "point"
                return result
            return {"revision": doc["revision"], "total": len(nodes), "page": page, "page_size": page_size,
                    "items": nodes[(page-1)*page_size:page*page_size]}

    def preview(self, raw):
        candidate = validate_snapshot(raw)
        with self.lock:
            current = self._ready()[0]
            kinds = KINDS
            if candidate["schema_version"] == 2 or current["schema_version"] == 2:
                from .catalog import as_catalog
                candidate, current = as_catalog(candidate), as_catalog(current)
                kinds = ("directories", "points")
            changes = {"added": 0, "updated": 0, "removed": 0}
            for kind in kinds:
                old = {x["id"]: x for x in current[kind]}
                new = {x["id"]: x for x in candidate[kind]}
                changes["added"] += len(new.keys()-old.keys())
                changes["removed"] += len(old.keys()-new.keys())
                changes["updated"] += sum(old[k] != new[k] for k in old.keys() & new.keys())
            return {"revision": current["revision"], "counts": {k: len(candidate[k]) for k in kinds},
                    "changes": changes, "warnings": []}

    @staticmethod
    def _write_atomic(path, document):
        path.parent.mkdir(parents=True, exist_ok=True)
        fd, tmp = tempfile.mkstemp(prefix=".archive-", suffix=".tmp", dir=path.parent)
        try:
            with os.fdopen(fd, "w", encoding="utf-8") as f:
                json.dump(document, f, ensure_ascii=False, allow_nan=False, separators=(",", ":"))
                f.flush()
                os.fsync(f.fileno())
            os.replace(tmp, path)
            if hasattr(os, "O_DIRECTORY"):
                directory_fd = os.open(path.parent, os.O_RDONLY | os.O_DIRECTORY)
                try:
                    os.fsync(directory_fd)
                finally:
                    os.close(directory_fd)
        finally:
            if os.path.exists(tmp):
                os.unlink(tmp)

    def publish(self, raw, expected_revision, referenced_ids=()):
        candidate = validate_snapshot(raw)
        with self.lock:
            old, _ = self._ready()
            self._check_revision(old, expected_revision)
            missing = set(referenced_ids) - {p["id"] for p in candidate["points"]}
            if missing:
                raise ReferencedPointError("测点仍被航点或任务引用，不能删除：" + ", ".join(sorted(missing)[:10]))
            candidate["revision"] = old["revision"] + 1
            candidate["updated_at"] = datetime.now(timezone.utc).isoformat()
            state = self._build(candidate)
            backup = self.path.parent / "revisions" / f"archive-{old['revision']:010d}.json"
            self._write_atomic(backup, old)
            try:
                self._write_atomic(self.path, candidate)
                self._activate(state)
            except Exception:
                # Failure may occur after rename (directory fsync or activation).
                # Recover authoritative disk state; if corrupt, fail closed.
                try:
                    disk = decode_snapshot(self.path.read_bytes())
                    self._state = self._build(disk)
                except Exception:
                    self._state = None
                    self.last_error = "档案保存后恢复失败，请检查磁盘文件与备份"
                raise
            return candidate["revision"]

    def catalog_data(self):
        from .catalog import catalog_index
        doc, idx = self._ready()
        if "catalog" not in idx:
            # Derived once per immutable snapshot; never modifies the persisted v1 file.
            with self.lock:
                if "catalog" not in idx:
                    idx["catalog"] = catalog_index(doc)
        if "catalog_order" not in idx:
            with self.lock:
                if "catalog_order" not in idx:
                    ordered = sorted(idx["catalog"][0]["points"], key=lambda p: (p.get("code", ""), p["id"]))
                    idx["catalog_named"] = [(p["name"].casefold(), p) for p in ordered]
                    by_directory = defaultdict(list)
                    for p in ordered:
                        by_directory[p.get("directory_id")].append(p)
                    idx["catalog_by_directory"] = by_directory
                    idx["catalog_order"] = ordered
        return idx["catalog"]

    def catalog_directories(self):
        with self.lock:
            doc, ids, children, direct = self.catalog_data()
            return {"revision": doc["revision"], "point_count": len(doc["points"]),
                    "items": [{**copy_json(d), "child_count": len(children[d["id"]]),
                               "point_count": direct[d["id"]]} for d in ids.values()]}

    def catalog_points(self, *, directory_id=None, recursive=True, name=None, code=None, q=None,
                       active=None, bound=None, bound_ids=None, page=1, page_size=50, revision=None):
        with self.lock:
            if page < 1 or not 1 <= page_size <= 200:
                raise ArchiveValidationError("页码或页长不合法")
            doc, ids, children, _ = self.catalog_data()
            self._check_revision(doc, revision)
            selected = None
            if directory_id is not None:
                if directory_id not in ids:
                    raise ArchiveValidationError("所选目录不存在，请刷新")
                selected = {directory_id}
                if recursive:
                    pending = [directory_id]
                    while pending:
                        node = pending.pop()
                        selected.update(children[node])
                        pending.extend(children[node])
            idx = self._ready()[1]
            rows = idx["catalog_order"]
            if selected is not None:
                rows = sorted((p for d in selected for p in idx["catalog_by_directory"].get(d, ())),
                              key=lambda p: (p.get("code", ""), p["id"]))
            if name:
                needle = name.casefold()
                rows = ([p for folded, p in idx["catalog_named"] if needle in folded] if rows is idx["catalog_order"]
                        else [p for p in rows if needle in p["name"].casefold()])
            if q and q.strip():
                needle = q.strip().casefold()
                rows = [p for p in rows if needle in ' '.join((p['name'], p['id'], p.get('code', ''))).casefold()]
            if code:
                rows = [p for p in rows if p.get("code", "") == code]
            if active is not None:
                rows = [p for p in rows if p.get("active", True) == active]
            bound_ids = bound_ids or set()
            if bound is True or (bound is False and bound_ids):
                rows = [p for p in rows if (p["id"] in bound_ids) == bound]
            items = copy_json(rows[(page-1)*page_size:page*page_size])
            for p in items:
                p["parent_name"] = ids.get(p.get("directory_id"), {}).get("name", "根目录")
                p["bound"] = p["id"] in bound_ids
            return {"revision": doc["revision"], "total": len(rows), "page": page, "page_size": page_size, "items": items}
