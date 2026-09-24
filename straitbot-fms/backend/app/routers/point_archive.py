"""Authenticated point archive maintenance; no request reads the archive file."""
import json
from typing import Literal, Optional

from fastapi import APIRouter, Depends, Header, HTTPException, Query, Request, Response
from fastapi.responses import JSONResponse
from sqlalchemy.orm import Session
from pydantic import BaseModel, Field, StrictInt, StrictStr

from ..auth import engineer_only
from ..database import get_db
from ..models import PointBinding, Waypoint, Robot, RobotMap, WaypointAction
from ..point_archive.runtime import get_archive_store
from ..point_archive.store import ArchiveStore, ArchiveUnavailable, RevisionConflict, ReferencedPointError, KINDS
from ..point_archive.schema import ArchiveValidationError, decode_snapshot, validate_snapshot, MAX_BYTES
from ..point_archive.relations import referenced_point_ids, list_bindings, add_binding, add_bindings, remove_binding

router = APIRouter(prefix="/api/point-archive", tags=["point-archive"], dependencies=[Depends(engineer_only)])
Kind = Literal["stations", "bays", "equipment", "points"]


def install_error_handlers(app):
    async def validation(request, exc):
        return JSONResponse(status_code=422, content={"detail": str(exc)})
    async def conflict(request, exc):
        return JSONResponse(status_code=409, content={"detail": str(exc)})
    async def unavailable(request, exc):
        return JSONResponse(status_code=503, content={"detail": str(exc)})
    app.add_exception_handler(ArchiveValidationError, validation)
    app.add_exception_handler(RevisionConflict, conflict)
    app.add_exception_handler(ReferencedPointError, conflict)
    app.add_exception_handler(ArchiveUnavailable, unavailable)


def expected_revision(if_match: Optional[str] = Header(None, alias="If-Match")):
    if if_match is None:
        raise HTTPException(428, "缺少档案版本 If-Match，请刷新后重试")
    try:
        value = int(if_match.strip('"'))
        if value < 1:
            raise ValueError()
        return value
    except ValueError:
        raise HTTPException(422, "If-Match 必须是有效版本号")


async def json_body(request: Request):
    data = bytearray()
    async for chunk in request.stream():
        data.extend(chunk)
        if len(data) > MAX_BYTES:
            raise HTTPException(413, "JSON 超过32 MiB限制")
    # Decoder handles duplicate keys and invalid constants before validation.
    return decode_snapshot(bytes(data), validate=False)


@router.get("/meta")
def meta(store: ArchiveStore = Depends(get_archive_store)):
    return store.meta()


@router.get("/snapshot")
def snapshot(store: ArchiveStore = Depends(get_archive_store)):
    return store.snapshot()


@router.get("/export")
def export(store: ArchiveStore = Depends(get_archive_store)):
    doc = store.snapshot()
    return Response(json.dumps(doc, ensure_ascii=False, allow_nan=False), media_type="application/json",
                    headers={"Content-Disposition": f'attachment; filename="point-archive-r{doc["revision"]}.json"'})


@router.post("/import/preview")
def preview(body=Depends(json_body), store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    with store.lock:
        result = store.preview(body)
        candidate = validate_snapshot(body)
        removed = referenced_point_ids(db) - {p["id"] for p in candidate["points"]}
        if removed:
            raise ReferencedPointError("导入会删除被引用测点：" + ", ".join(sorted(removed)[:10]))
        return result


@router.put("/snapshot")
def publish(body=Depends(json_body), revision=Depends(expected_revision),
            store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    with store.lock:
        return {"revision": store.publish(body, revision, referenced_point_ids(db))}


@router.get("/tree")
def tree(parent_type: Literal["root", "station", "voltage", "bay", "equipment"] = "root",
         parent_id: Optional[str] = None, voltage_level: Optional[str] = None,
         page: int = Query(1, ge=1), page_size: int = Query(50, ge=1, le=200),
         store: ArchiveStore = Depends(get_archive_store)):
    if parent_type != "root" and not parent_id:
        raise HTTPException(422, "缺少父节点ID")
    return store.tree(parent_type, parent_id, voltage_level, page, page_size)


@router.get("/entities/{kind}")
def entities(kind: Kind, name: Optional[str] = Query(None, max_length=256), code: Optional[str] = Query(None, max_length=128),
             station_id: Optional[str] = None, bay_id: Optional[str] = None, equipment_id: Optional[str] = None,
             voltage_level: Optional[str] = None, assay_type: Optional[int] = None,
             active: Optional[bool] = None, bound: Optional[bool] = None,
             page: int = Query(1, ge=1), page_size: int = Query(50, ge=1, le=200), revision: Optional[int] = None,
             store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    with store.lock:
        bound_ids = {r[0] for r in db.query(PointBinding.point_id).distinct()} if kind == "points" else set()
        result = store.list_entities(kind, name=name, code=code, station_id=station_id, bay_id=bay_id,
                                   equipment_id=equipment_id, voltage_level=voltage_level, assay_type=assay_type,
                                   active=active, bound=bound, bound_ids=bound_ids, page=page, page_size=page_size, revision=revision)
    # Already validated JSON primitives; avoid FastAPI recursively re-encoding every field.
    return JSONResponse(content=result)


@router.get("/points")
def points(name: Optional[str] = None, code: Optional[str] = None, equipment_id: Optional[str] = None,
           station_id: Optional[str] = None, bay_id: Optional[str] = None, bound: Optional[bool] = None,
           page: int = Query(1, ge=1), page_size: int = Query(50, ge=1, le=200), revision: Optional[int] = None,
           store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    return entities("points", name, code, station_id, bay_id, equipment_id, None, None, None, bound,
                    page, page_size, revision, store, db)


@router.get("/entities/{kind}/{item_id}")
def detail(kind: Kind, item_id: str, store: ArchiveStore = Depends(get_archive_store)):
    with store.lock:
        item = store.get_entity(kind, item_id)
        if item is None:
            raise HTTPException(404, "档案记录不存在")
        return {"revision": store.revision, "item": item}


@router.get("/points/{point_id}")
def point_detail(point_id: str, store: ArchiveStore = Depends(get_archive_store)):
    return detail("points", point_id, store)


def mutate(kind, item_id, body, mode, revision, store, db):
    if not isinstance(body, dict):
        raise ArchiveValidationError("档案记录必须为JSON对象")
    with store.lock:
        doc = store.snapshot()
        if doc["schema_version"] == 2:
            raise HTTPException(409, "档案已升级自由目录，请使用新版测点档案接口")
        store._check_revision(doc, revision)
        if mode == "create":
            if any(r["id"] == body.get("id") for r in doc[kind]):
                raise HTTPException(409, "ID已存在")
            item = dict(body)
            doc[kind].append(item)
        else:
            item = next((row for row in doc[kind] if row["id"] == item_id), None)
            if item is None:
                raise HTTPException(404, "档案记录不存在")
            if mode == "delete":
                doc[kind].remove(item)
            else:
                if "id" in body and body["id"] != item_id:
                    raise HTTPException(422, "不能修改稳定ID，请修改编码或名称")
                item.update(body)
        if mode != "delete":
            item.pop("parent_name", None)
            item.pop("bound", None)
        new_revision = store.publish(doc, revision, referenced_point_ids(db))
        return {"revision": new_revision, "item": store.get_entity(kind, item["id"]) if mode != "delete" else None}


@router.post("/entities/{kind}")
def create(kind: Kind, body=Depends(json_body), revision=Depends(expected_revision),
           store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    return mutate(kind, None, body, "create", revision, store, db)


@router.put("/entities/{kind}/{item_id}")
def update(kind: Kind, item_id: str, body=Depends(json_body), revision=Depends(expected_revision),
           store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    return mutate(kind, item_id, body, "update", revision, store, db)


@router.delete("/entities/{kind}/{item_id}")
def delete(kind: Kind, item_id: str, revision=Depends(expected_revision),
           store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    return mutate(kind, item_id, {}, "delete", revision, store, db)


@router.get("/bindings")
def bindings(point_id: Optional[str] = None, robot_pk: Optional[int] = None,
             waypoint_pk: Optional[int] = None, store: ArchiveStore = Depends(get_archive_store),
             db: Session = Depends(get_db)):
    items = list_bindings(db, point_id, robot_pk, waypoint_pk)
    from ..models import Robot, RobotMap, InspectionPlan
    robots = {r.id: r for r in db.query(Robot).all()}
    maps = {m.id: m for m in db.query(RobotMap).all()}
    plans = db.query(InspectionPlan).filter(InspectionPlan.deleted.is_(False)).all()
    for item in items:
        robot = robots.get(item['robot_pk']); robot_map = maps.get(item['map_pk'])
        item['robot_name'] = robot.name if robot else ''
        item['map_name'] = robot_map.name if robot_map else ''
        item['plan_names'] = [p.name for p in plans if p.robot_pk == item['robot_pk'] and item['point_id'] in p.point_ids
                              and any(stage['map_pk'] == item['map_pk'] for stage in (p.stages or [{'map_pk': p.map_pk}]))]
        point = store.get(item["point_id"])
        item["point_name"] = point["name"] if point else item["point_id"]
        item["point_active"] = point.get("active", True) if point else False
    return {"items": items}


@router.get("/binding-options")
def binding_options(name: str = "", page: int = Query(1, ge=1), page_size: int = Query(50, ge=1, le=200),
                    robot_pk: Optional[int] = None, map_pk: Optional[int] = None,
                    floor: Optional[int] = None, waypoint_pk: Optional[int] = None,
                    db: Session = Depends(get_db)):
    query = db.query(Waypoint, Robot, RobotMap).join(Robot, Robot.id == Waypoint.robot_pk).join(RobotMap, RobotMap.id == Waypoint.map_pk)
    if robot_pk is not None:
        query = query.filter(Waypoint.robot_pk == robot_pk)
    from sqlalchemy import func, or_
    from ..models import PointBinding
    if map_pk is not None:
        query = query.filter(Waypoint.map_pk == map_pk)
    if floor is not None:
        query = query.filter(func.coalesce(Waypoint.floor, RobotMap.floor, 0) == floor)
    if waypoint_pk is not None:
        query = query.filter(Waypoint.id == waypoint_pk)
    if name.strip():
        query = query.filter(or_(Waypoint.name.contains(name.strip(), autoescape=True), Waypoint.wp_id.contains(name.strip(), autoescape=True)))
    total = query.count()
    rows = query.order_by(Waypoint.id).offset((page-1)*page_size).limit(page_size).all()
    ids = [w.id for w, _, _ in rows]
    actions = db.query(WaypointAction).filter(WaypointAction.waypoint_pk.in_(ids)).order_by(WaypointAction.seq, WaypointAction.id).all() if ids else []
    counts = dict(db.query(PointBinding.waypoint_pk, func.count(func.distinct(PointBinding.point_id))).filter(
        PointBinding.waypoint_pk.in_(ids)).group_by(PointBinding.waypoint_pk).all()) if ids else {}
    by_waypoint = {}
    for a in actions:
        by_waypoint.setdefault(a.waypoint_pk, []).append({"id": a.id, "name": a.name, "action_type": a.action_type})
    return {"page": page, "page_size": page_size, "total": total,
            "items": [{"id": w.id, "name": w.name, "robot_pk": r.id, "map_pk": m.id,
                       "robot_name": r.name, "map_name": m.name, "floor": w.floor if w.floor is not None else (m.floor or 0), "binding_count": counts.get(w.id, 0),
                       "wp_id": w.wp_id, "actions": by_waypoint.get(w.id, [])} for w, r, m in rows]}


class BatchBindingIn(BaseModel):
    robot_pk: StrictInt
    waypoint_pk: StrictInt
    action_pk: Optional[StrictInt] = None
    point_ids: list[StrictStr] = Field(min_length=1, max_length=10000)


@router.post("/bindings/batch")
def bind_batch(body: BatchBindingIn, store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    return add_bindings(db, store, body.robot_pk, body.waypoint_pk, body.point_ids, body.action_pk)


@router.post("/bindings")
def bind(body=Depends(json_body), store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    if not isinstance(body, dict) or not isinstance(body.get("point_id"), str) or type(body.get("waypoint_pk")) is not int:
        raise HTTPException(422, "绑定需要point_id字符串和waypoint_pk整数")
    if body.get("action_pk") is not None and type(body["action_pk"]) is not int:
        raise HTTPException(422, "action_pk必须是整数")
    return add_binding(db, store, body["point_id"], body["waypoint_pk"], body.get("action_pk"))


@router.delete("/bindings/{binding_id}")
def unbind(binding_id: int, store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    return remove_binding(db, store, binding_id)

# Free hierarchy APIs share the same store, publication lock and reference protection.
from ..point_archive.catalog import from_portable, portable, platform_check
from ..point_archive.schema import copy_json


@router.get("/catalog/directories")
def catalog_directories(store: ArchiveStore = Depends(get_archive_store)):
    with store.lock:
        return JSONResponse(content=store.catalog_directories())


@router.get("/catalog/points")
def catalog_points(directory_id: Optional[str] = None, recursive: bool = True,
                   q: Optional[str] = Query(None, max_length=256),
                   name: Optional[str] = Query(None, max_length=256), code: Optional[str] = Query(None, max_length=256),
                   active: Optional[bool] = None, bound: Optional[bool] = None,
                   page: int = Query(1, ge=1), page_size: int = Query(50, ge=1, le=200), revision: Optional[int] = None,
                   store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    with store.lock:
        bound_ids = {r[0] for r in db.query(PointBinding.point_id).distinct()}
        return JSONResponse(content=store.catalog_points(directory_id=directory_id, recursive=recursive, name=name, q=q,
                            code=code, active=active, bound=bound, bound_ids=bound_ids,
                            page=page, page_size=page_size, revision=revision))


@router.get("/catalog/platform-check")
def platform_validation(store: ArchiveStore = Depends(get_archive_store)):
    with store.lock:
        return platform_check(store.catalog_data()[0])


@router.get("/catalog/export")
def portable_export(platform: bool = False, store: ArchiveStore = Depends(get_archive_store)):
    with store.lock:
        doc = store.catalog_data()[0]
        if platform:
            check = platform_check(doc)
            if not check["valid"]:
                raise HTTPException(422, check)
        return Response(json.dumps(portable(doc), ensure_ascii=False, allow_nan=False, indent=2),
                        media_type="application/json", headers={"Content-Disposition": 'attachment; filename="point-archive.json"'})


@router.post("/catalog/import/preview")
def portable_preview(body=Depends(json_body), store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    candidate = from_portable(body)
    with store.lock:
        result = store.preview(candidate)
        missing = referenced_point_ids(db) - {p["id"] for p in candidate["points"]}
        if missing:
            raise ReferencedPointError("导入会删除被引用测点：" + ", ".join(sorted(missing)[:10]))
        result["warnings"] = ["替换全部目录与测点，同ID测点覆盖配置。本地航点绑定和历史任务不迁移、不删除。"]
        return result


@router.put("/catalog/import")
def portable_import(body=Depends(json_body), revision=Depends(expected_revision),
                    store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    candidate = from_portable(body)
    with store.lock:
        return {"revision": store.publish(candidate, revision, referenced_point_ids(db))}


def mutate_catalog(kind, item_id, body, mode, revision, store, db):
    if not isinstance(body, dict):
        raise ArchiveValidationError("记录必须为JSON对象")
    with store.lock:
        doc = copy_json(store.catalog_data()[0])
        store._check_revision(doc, revision)
        rows = doc[kind]
        if mode == "create":
            if any(r["id"] == body.get("id") for r in rows):
                raise HTTPException(409, "ID已存在")
            item = dict(body)
            rows.append(item)
        else:
            item = next((r for r in rows if r["id"] == item_id), None)
            if item is None:
                raise HTTPException(404, "记录不存在")
            if mode == "delete":
                if kind == "directories" and (any(d.get("parent_id") == item_id for d in rows)
                        or any(p.get("directory_id") == item_id for p in doc["points"])):
                    raise HTTPException(409, "目录内仍有子目录或测点，请先移动或删除内容")
                rows.remove(item)
            else:
                if body.get("id", item_id) != item_id:
                    raise HTTPException(422, "不能修改稳定ID")
                item.update(body)
        for field in ("parent_name", "bound", "child_count", "point_count"):
            item.pop(field, None)
        return {"revision": store.publish(doc, revision, referenced_point_ids(db))}


@router.post("/catalog/{kind}")
def catalog_create(kind: Literal["directories", "points"], body=Depends(json_body), revision=Depends(expected_revision),
                   store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    return mutate_catalog(kind, None, body, "create", revision, store, db)


@router.put("/catalog/{kind}/{item_id:path}")
def catalog_update(kind: Literal["directories", "points"], item_id: str, body=Depends(json_body), revision=Depends(expected_revision),
                   store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    return mutate_catalog(kind, item_id, body, "update", revision, store, db)


@router.delete("/catalog/{kind}/{item_id:path}")
def catalog_delete(kind: Literal["directories", "points"], item_id: str, revision=Depends(expected_revision),
                   store: ArchiveStore = Depends(get_archive_store), db: Session = Depends(get_db)):
    return mutate_catalog(kind, item_id, {}, "delete", revision, store, db)
