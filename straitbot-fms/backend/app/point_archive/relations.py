"""Serialize SQLite reference changes with archive publication."""
from functools import wraps
from inspect import signature

from fastapi import HTTPException

from ..models import ArchiveTaskPoint, InspectionPlanPoint, InspectionPlan, PointBinding, Robot, RobotMap, Waypoint, WaypointAction


def referenced_point_ids(db):
    return {row[0] for row in db.query(PointBinding.point_id).all()} | {
        row[0] for row in db.query(ArchiveTaskPoint.point_id).all()
    } | {row[0] for row in db.query(InspectionPlanPoint.point_id).all()}


def _binding_out(binding, waypoint, action):
    return {
        "id": binding.id, "point_id": binding.point_id,
        "waypoint_pk": binding.waypoint_pk, "action_pk": binding.action_pk,
        "robot_pk": waypoint.robot_pk, "map_pk": waypoint.map_pk,
        "waypoint_name": waypoint.name, "action_name": action.name if action else None,
    }


def list_bindings(db, point_id=None, robot_pk=None, waypoint_pk=None):
    query = db.query(PointBinding, Waypoint, WaypointAction).join(
        Waypoint, PointBinding.waypoint_pk == Waypoint.id
    ).outerjoin(WaypointAction, PointBinding.action_pk == WaypointAction.id)
    if point_id is not None:
        query = query.filter(PointBinding.point_id == point_id)
    if robot_pk is not None:
        query = query.filter(Waypoint.robot_pk == robot_pk)
    if waypoint_pk is not None:
        query = query.filter(PointBinding.waypoint_pk == waypoint_pk)
    return [_binding_out(*row) for row in query.order_by(PointBinding.id).all()]


def add_binding(db, store, point_id, waypoint_pk, action_pk=None, *, commit=True):
    with store.lock:
        point = store.get(point_id)
        if point is None:
            raise HTTPException(404, "测点不存在")
        if not point.get("active", True):
            raise HTTPException(422, "停用测点不能新增绑定")
        waypoint = db.get(Waypoint, waypoint_pk)
        if waypoint is None:
            raise HTTPException(404, "航点不存在")
        robot_map = db.get(RobotMap, waypoint.map_pk)
        if not robot_map or robot_map.robot_pk != waypoint.robot_pk or not db.get(Robot, waypoint.robot_pk):
            raise HTTPException(422, "航点所属地图或机器人无效")
        action = db.get(WaypointAction, action_pk) if action_pk is not None else None
        if action_pk is not None and (action is None or action.waypoint_pk != waypoint_pk):
            raise HTTPException(422, "动作不属于所选航点")
        exists = db.query(PointBinding).filter_by(
            point_id=point_id, waypoint_pk=waypoint_pk, action_pk=action_pk
        ).first()
        if exists:
            raise HTTPException(409, "该测点绑定已存在")
        binding = PointBinding(point_id=point_id, waypoint_pk=waypoint_pk, action_pk=action_pk)
        db.add(binding)
        if commit:
            db.commit()
        else:
            db.flush()
        db.refresh(binding)
        return _binding_out(binding, waypoint, action)


def add_bindings(db, store, robot_pk, waypoint_pk, point_ids, action_pk=None):
    """One transaction for the whole selection, using the same archive lock."""
    with store.lock:
        waypoint = db.get(Waypoint, waypoint_pk)
        if waypoint is None or waypoint.robot_pk != robot_pk:
            raise HTTPException(422, "航点不属于所选机器人")
        if not point_ids or len(point_ids) != len(set(point_ids)):
            raise HTTPException(422, "请选择测点且不能重复")
        try:
            items = [add_binding(db, store, point_id, waypoint_pk, action_pk, commit=False)
                     for point_id in point_ids]
            db.commit()
            return {"items": items}
        except Exception:
            db.rollback()
            raise


def remove_binding(db, store, binding_id):
    with store.lock:
        binding = db.get(PointBinding, binding_id)
        if binding is None:
            raise HTTPException(404, "绑定不存在")
        db.delete(binding)
        db.commit()
        return {"ok": True}


def guard_archive_bindings(kind, parameter, replacing=False):
    """Keep validation and target mutation within the archive mutation lock."""
    def decorate(function):
        call_signature = signature(function)

        @wraps(function)
        def guarded(*args, **kwargs):
            from .runtime import archive_store
            arguments = call_signature.bind(*args, **kwargs).arguments
            db, target = arguments["db"], arguments[parameter]
            with archive_store.lock:
                if not replacing or arguments["body"].replace:
                    if kind in ("robot", "map"):
                        column = InspectionPlan.robot_pk if kind == "robot" else InspectionPlan.map_pk
                        plans = db.query(InspectionPlan).filter(InspectionPlan.deleted.is_(False))
                        referenced = plans.filter(column == target).first()
                        if kind == 'map' and not referenced:
                            referenced = any(any(stage['map_pk'] == target for stage in (p.stages or [])) for p in plans)
                        if referenced:
                            raise HTTPException(409, "存在巡检计划，请先删除计划再删除或覆盖机器人/地图")
                    query = db.query(PointBinding).join(Waypoint, PointBinding.waypoint_pk == Waypoint.id)
                    columns = {"robot": Waypoint.robot_pk, "map": Waypoint.map_pk,
                               "waypoint": PointBinding.waypoint_pk, "action": PointBinding.action_pk}
                    if query.filter(columns[kind] == target).first():
                        raise HTTPException(409, "存在测点档案绑定，请先显式解除绑定再删除或覆盖")
                return function(*args, **kwargs)
        return guarded
    return decorate
