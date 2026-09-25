"""航点管理: 地图/航点/动作 CRUD + 定标图上传 + 导入/导出 JSON。

floor: 地图层有 floor, 航点层也有 floor(可空, 空则继承地图 floor)。
定标图: 上传存 data/calibration/, DB 存相对路径(/data/calibration/xxx.jpg)。
"""
import json
import uuid
from datetime import datetime
from io import BytesIO
from fastapi import APIRouter, Depends, HTTPException, UploadFile, File, Query
from fastapi.responses import StreamingResponse
from pydantic import BaseModel
from typing import Optional, List
from sqlalchemy.orm import Session

from ..point_archive.relations import guard_archive_bindings
from ..database import get_db
from ..models import Robot, RobotMap, Waypoint, WaypointAction
from ..auth import engineer_only, get_current_user
from ..config import CALIB_DIR
from ..services import robot_api

router = APIRouter(prefix="/api/waypoints", tags=["waypoints"])


def _robot(rid: int, db: Session) -> Robot:
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    return r


# ========== 地图 ==========
class MapIn(BaseModel):
    name: str = ""
    floor: Optional[int] = None
    image_path: str = ""
    scale: float = 1.0
    origin_x: float = 0.0
    origin_y: float = 0.0
    note: str = ""


def _map_out(m: RobotMap) -> dict:
    return {
        "id": m.id, "robot_pk": m.robot_pk, "name": m.name, "floor": m.floor,
        "image_path": m.image_path, "scale": m.scale,
        "origin_x": m.origin_x, "origin_y": m.origin_y, "note": m.note,
        "created_at": m.created_at, "updated_at": m.updated_at,
        "waypoint_count": len(m.waypoints) if m.waypoints else 0,
    }


@router.get("/robots/{rid}/maps")
def list_maps(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    _robot(rid, db)
    ms = db.query(RobotMap).filter(RobotMap.robot_pk == rid).order_by(RobotMap.floor, RobotMap.id).all()
    return [_map_out(m) for m in ms]


@router.post("/robots/{rid}/maps")
def create_map(rid: int, body: MapIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    _robot(rid, db)
    m = RobotMap(robot_pk=rid, **body.model_dump())
    db.add(m)
    db.commit()
    db.refresh(m)
    return _map_out(m)


@router.put("/maps/{mid}")
def update_map(mid: int, body: MapIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    m = db.query(RobotMap).filter(RobotMap.id == mid).first()
    if not m:
        raise HTTPException(404, "地图不存在")
    for k, v in body.model_dump().items():
        setattr(m, k, v)
    db.commit()
    db.refresh(m)
    return _map_out(m)


@router.delete("/maps/{mid}")
@guard_archive_bindings("map", "mid")
def delete_map(mid: int, db: Session = Depends(get_db), _=Depends(engineer_only)):
    m = db.query(RobotMap).filter(RobotMap.id == mid).first()
    if not m:
        raise HTTPException(404, "地图不存在")
    db.delete(m)
    db.commit()
    return {"ok": True, "msg": "已删除"}


# ========== 航点 ==========
class WaypointIn(BaseModel):
    index: int = 0
    name: str = ""
    type: int = 0
    floor: Optional[int] = None
    pose_x: float = 0.0
    pose_y: float = 0.0
    pose_theta: float = 0.0
    lift_height: float = 0.0
    ptz_pan: float = 0.0
    ptz_tilt: float = 0.0
    ptz_zoom: float = 0.0
    calib_visible: str = ""
    calib_thermal: str = ""
    note: str = ""


def _action_out(a: WaypointAction) -> dict:
    return {
        "id": a.id, "waypoint_pk": a.waypoint_pk, "seq": a.seq,
        "action_type": a.action_type, "name": a.name,
        "ptz_pan": a.ptz_pan, "ptz_tilt": a.ptz_tilt, "ptz_zoom": a.ptz_zoom,
        "lift_height": a.lift_height, "duration_ms": a.duration_ms, "note": a.note,
    }


def _wp_out(w: Waypoint) -> dict:
    return {
        "id": w.id, "map_pk": w.map_pk, "robot_pk": w.robot_pk,
        "index": w.index, "wp_id": w.wp_id, "name": w.name, "type": w.type,
        "floor": w.floor,
        "pose": {"x": w.pose_x, "y": w.pose_y, "theta": w.pose_theta},
        "lift_height": w.lift_height,
        "ptz": {"pan": w.ptz_pan, "tilt": w.ptz_tilt, "zoom": w.ptz_zoom},
        "calib_visible": w.calib_visible, "calib_thermal": w.calib_thermal,
        "note": w.note, "created_at": w.created_at, "updated_at": w.updated_at,
        "actions": [_action_out(a) for a in w.actions],
    }


@router.get("/maps/{mid}/list")
def list_waypoints(mid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    ws = db.query(Waypoint).filter(Waypoint.map_pk == mid).order_by(Waypoint.index).all()
    return [_wp_out(w) for w in ws]


@router.post("/maps/{mid}")
def create_waypoint(mid: int, body: WaypointIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    m = db.query(RobotMap).filter(RobotMap.id == mid).first()
    if not m:
        raise HTTPException(404, "地图不存在")
    # 自动序号: 取当前最大+1
    max_idx = db.query(Waypoint.index).filter(Waypoint.map_pk == mid).order_by(Waypoint.index.desc()).first()
    idx = (max_idx[0] + 1) if max_idx else 0
    wp_id = f"wp_{uuid.uuid4().hex[:8]}"
    w = Waypoint(
        map_pk=mid, robot_pk=m.robot_pk, index=body.index or idx, wp_id=wp_id,
        name=body.name, type=body.type, floor=body.floor,
        pose_x=body.pose_x, pose_y=body.pose_y, pose_theta=body.pose_theta,
        lift_height=body.lift_height,
        ptz_pan=body.ptz_pan, ptz_tilt=body.ptz_tilt, ptz_zoom=body.ptz_zoom,
        calib_visible=body.calib_visible, calib_thermal=body.calib_thermal,
        note=body.note,
    )
    db.add(w)
    db.commit()
    db.refresh(w)
    return _wp_out(w)


@router.put("/{wid}")
def update_waypoint(wid: int, body: WaypointIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    w = db.query(Waypoint).filter(Waypoint.id == wid).first()
    if not w:
        raise HTTPException(404, "航点不存在")
    w.index = body.index
    w.name = body.name
    w.type = body.type
    w.floor = body.floor
    w.pose_x, w.pose_y, w.pose_theta = body.pose_x, body.pose_y, body.pose_theta
    w.lift_height = body.lift_height
    w.ptz_pan, w.ptz_tilt, w.ptz_zoom = body.ptz_pan, body.ptz_tilt, body.ptz_zoom
    w.calib_visible = body.calib_visible
    w.calib_thermal = body.calib_thermal
    w.note = body.note
    db.commit()
    db.refresh(w)
    return _wp_out(w)


@router.delete("/{wid}")
@guard_archive_bindings("waypoint", "wid")
def delete_waypoint(wid: int, db: Session = Depends(get_db), _=Depends(engineer_only)):
    w = db.query(Waypoint).filter(Waypoint.id == wid).first()
    if not w:
        raise HTTPException(404, "航点不存在")
    db.delete(w)
    db.commit()
    return {"ok": True, "msg": "已删除"}


# ========== 动作 ==========
class ActionIn(BaseModel):
    seq: int = 0
    action_type: int = 1
    name: str = ""
    ptz_pan: Optional[float] = None
    ptz_tilt: Optional[float] = None
    ptz_zoom: Optional[float] = None
    lift_height: Optional[float] = None
    duration_ms: int = 0
    note: str = ""


@router.post("/{wid}/actions")
def add_action(wid: int, body: ActionIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    w = db.query(Waypoint).filter(Waypoint.id == wid).first()
    if not w:
        raise HTTPException(404, "航点不存在")
    max_seq = db.query(WaypointAction.seq).filter(WaypointAction.waypoint_pk == wid) \
        .order_by(WaypointAction.seq.desc()).first()
    seq = body.seq or ((max_seq[0] + 1) if max_seq else 0)
    a = WaypointAction(
        waypoint_pk=wid, seq=seq, action_type=body.action_type, name=body.name,
        ptz_pan=body.ptz_pan, ptz_tilt=body.ptz_tilt, ptz_zoom=body.ptz_zoom,
        lift_height=body.lift_height, duration_ms=body.duration_ms, note=body.note,
    )
    db.add(a)
    db.commit()
    db.refresh(a)
    return _action_out(a)


@router.put("/actions/{aid}")
def update_action(aid: int, body: ActionIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    a = db.query(WaypointAction).filter(WaypointAction.id == aid).first()
    if not a:
        raise HTTPException(404, "动作不存在")
    a.seq = body.seq
    a.action_type = body.action_type
    a.name = body.name
    a.ptz_pan = body.ptz_pan
    a.ptz_tilt = body.ptz_tilt
    a.ptz_zoom = body.ptz_zoom
    a.lift_height = body.lift_height
    a.duration_ms = body.duration_ms
    a.note = body.note
    db.commit()
    db.refresh(a)
    return _action_out(a)


@router.delete("/actions/{aid}")
@guard_archive_bindings("action", "aid")
def delete_action(aid: int, db: Session = Depends(get_db), _=Depends(engineer_only)):
    a = db.query(WaypointAction).filter(WaypointAction.id == aid).first()
    if not a:
        raise HTTPException(404, "动作不存在")
    db.delete(a)
    db.commit()
    return {"ok": True, "msg": "已删除"}


# ========== 定标图上传 ==========
@router.post("/{wid}/calibration")
async def upload_calibration(
    wid: int,
    channel: str = "visible",   # visible | thermal
    file: UploadFile = File(...),
    db: Session = Depends(get_db),
    _=Depends(engineer_only),
):
    """上传航点定标图。存 data/calibration/, DB 存 /data/calibration/相对路径。"""
    w = db.query(Waypoint).filter(Waypoint.id == wid).first()
    if not w:
        raise HTTPException(404, "航点不存在")
    ext = (file.filename or ".jpg").rsplit(".", 1)[-1].lower()
    if ext not in ("jpg", "jpeg", "png", "bmp"):
        ext = "jpg"
    fname = f"wp{wid}_{channel}_{uuid.uuid4().hex[:6]}.{ext}"
    save_path = CALIB_DIR / fname
    content = await file.read()
    save_path.write_bytes(content)
    rel = f"/data/calibration/{fname}"
    if channel == "thermal":
        w.calib_thermal = rel
    else:
        w.calib_visible = rel
    db.commit()
    return {"ok": True, "path": rel}


@router.post("/{wid}/calibration/base64")
def upload_calibration_base64(
    wid: int,
    body: dict,
    db: Session = Depends(get_db),
    _=Depends(engineer_only),
):
    """前端截屏(base64 dataurl)直接存为定标图。body: {channel, dataurl}。"""
    w = db.query(Waypoint).filter(Waypoint.id == wid).first()
    if not w:
        raise HTTPException(404, "航点不存在")
    import base64
    dataurl = body.get("dataurl", "")
    channel = body.get("channel", "visible")
    if "," in dataurl:
        header, _, b64 = dataurl.partition(",")
        ext = "png" if "png" in header else "jpg"
    else:
        b64, ext = dataurl, "jpg"
    try:
        raw = base64.b64decode(b64)
    except Exception:
        raise HTTPException(400, "无效的 base64 图片")
    fname = f"wp{wid}_{channel}_{uuid.uuid4().hex[:6]}.{ext}"
    (CALIB_DIR / fname).write_bytes(raw)
    rel = f"/data/calibration/{fname}"
    if channel == "thermal":
        w.calib_thermal = rel
    else:
        w.calib_visible = rel
    db.commit()
    return {"ok": True, "path": rel}


# ========== 读取当前位姿(用于录点时填充) ==========
@router.get("/robots/{rid}/current_pose")
def current_pose(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """读取机器人当前位姿(cmd=30) + 云台(cmd=35) + 升降(cmd=40)。"""
    r = _robot(rid, db)
    result = {"ok": True, "pose": None, "ptz": None, "lift": None}
    # 位姿 cmd=30
    try:
        code, msg, d = robot_api.call(r.ip, r.api_port, r.robot_id, 30)
        if code == 0 and d:
            result["pose"] = {"x": d.get("x") or d.get("point", {}).get("x"),
                              "y": d.get("y") or d.get("point", {}).get("y"),
                              "theta": d.get("theta", 0)}
            if "floor" in d:
                result["floor"] = d.get("floor")
    except Exception as e:  # noqa: BLE001
        result["pose_err"] = str(e)
    # 云台 cmd=35
    try:
        code, msg, d = robot_api.call(r.ip, r.api_port, r.robot_id, 35)
        if code == 0 and d:
            result["ptz"] = {"pan": d.get("pan", 0), "tilt": d.get("tilt", 0), "zoom": d.get("zoom", 0)}
    except Exception:  # noqa: BLE001
        pass
    # 升降 cmd=40
    try:
        code, msg, d = robot_api.call(r.ip, r.api_port, r.robot_id, 40)
        if code == 0 and d:
            result["lift"] = {"height": d.get("height", 0)}
    except Exception:  # noqa: BLE001
        pass
    return result


# ========== 导入 / 导出 JSON ==========
@router.get("/robots/{rid}/export")
def export_robot(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """导出机器人所有地图+航点+动作为 JSON(v1.1)。"""
    r = _robot(rid, db)
    maps = db.query(RobotMap).filter(RobotMap.robot_pk == rid).order_by(RobotMap.floor, RobotMap.id).all()
    payload = {
        "version": "1.1",
        "exported_at": datetime.utcnow().isoformat(),
        "source": "straitbot-fms",
        "robot": {"id": r.id, "name": r.name, "ip": r.ip, "product_type": r.product_type},
        "maps": [_serialize_map(m) for m in maps],
    }
    return payload


def _serialize_map(m: RobotMap) -> dict:
    return {
        "name": m.name, "floor": m.floor, "image_path": m.image_path,
        "scale": m.scale, "origin_x": m.origin_x, "origin_y": m.origin_y, "note": m.note,
        "waypoints": [_serialize_wp(w) for w in m.waypoints],
    }


def _serialize_wp(w: Waypoint) -> dict:
    return {
        "index": w.index, "id": w.wp_id, "name": w.name, "type": w.type,
        "floor": w.floor,
        "pose": {"x": w.pose_x, "y": w.pose_y, "theta": w.pose_theta},
        "lift_height": w.lift_height,
        "ptz": {"pan": w.ptz_pan, "tilt": w.ptz_tilt, "zoom": w.ptz_zoom},
        "calibration_images": {"visible": w.calib_visible, "thermal": w.calib_thermal},
        "actions": [_serialize_action(a) for a in w.actions],
        "note": w.note,
    }


def _serialize_action(a: WaypointAction) -> dict:
    return {
        "seq": a.seq, "type": a.action_type, "name": a.name,
        "ptz_param": {"pan": a.ptz_pan, "tilt": a.ptz_tilt, "zoom": a.ptz_zoom},
        "lift_height": a.lift_height, "duration_ms": a.duration_ms, "note": a.note,
    }


class ImportIn(BaseModel):
    data: dict
    replace: bool = False   # True=先清空该机器人旧地图再导入


@router.post("/robots/{rid}/import")
@guard_archive_bindings("robot", "rid", replacing=True)
def import_robot(rid: int, body: ImportIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """导入 JSON 到机器人。replace=True 时先清空旧数据。"""
    r = _robot(rid, db)
    data = body.data
    if data.get("version", "").startswith("1."):
        maps_data = data.get("maps", [])
    else:
        raise HTTPException(400, "不支持的版本/格式")
    if body.replace:
        for old_map in db.query(RobotMap).filter(RobotMap.robot_pk == rid).all():
            db.delete(old_map)
        db.flush()
    cnt_m = cnt_w = cnt_a = 0
    for md in maps_data:
        m = RobotMap(
            robot_pk=rid, name=md.get("name", ""), floor=md.get("floor"),
            image_path=md.get("image_path", ""), scale=md.get("scale", 1.0),
            origin_x=md.get("origin_x", 0), origin_y=md.get("origin_y", 0),
            note=md.get("note", ""),
        )
        db.add(m)
        db.flush()
        cnt_m += 1
        for wd in md.get("waypoints", []):
            pose = wd.get("pose", {})
            ptz = wd.get("ptz", {})
            calib = wd.get("calibration_images", {})
            w = Waypoint(
                map_pk=m.id, robot_pk=rid, index=wd.get("index", 0),
                wp_id=wd.get("id") or f"wp_{uuid.uuid4().hex[:8]}",
                name=wd.get("name", ""), type=wd.get("type", 0), floor=wd.get("floor"),
                pose_x=pose.get("x", 0), pose_y=pose.get("y", 0), pose_theta=pose.get("theta", 0),
                lift_height=wd.get("lift_height", 0),
                ptz_pan=ptz.get("pan", 0), ptz_tilt=ptz.get("tilt", 0), ptz_zoom=ptz.get("zoom", 0),
                calib_visible=calib.get("visible", ""), calib_thermal=calib.get("thermal", ""),
                note=wd.get("note", ""),
            )
            db.add(w)
            db.flush()
            cnt_w += 1
            for ad in wd.get("actions", []):
                pp = ad.get("ptz_param", {})
                a = WaypointAction(
                    waypoint_pk=w.id, seq=ad.get("seq", 0),
                    action_type=ad.get("type", 1), name=ad.get("name", ""),
                    ptz_pan=pp.get("pan"), ptz_tilt=pp.get("tilt"), ptz_zoom=pp.get("zoom"),
                    lift_height=ad.get("lift_height"), duration_ms=ad.get("duration_ms", 0),
                    note=ad.get("note", ""),
                )
                db.add(a)
                cnt_a += 1
    db.commit()
    return {"ok": True, "msg": f"导入完成: {cnt_m} 地图 / {cnt_w} 航点 / {cnt_a} 动作"}


# ========== 导出为可下载文件 ==========
@router.get("/robots/{rid}/export/file")
def export_file(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """导出为可下载的 JSON 文件。"""
    payload = export_robot(rid, db, _=get_current_user)
    content = json.dumps(payload, ensure_ascii=False, indent=2).encode("utf-8")
    r = _robot(rid, db)
    fname = f"waypoints_{r.name}_{datetime.utcnow().strftime('%Y%m%d_%H%M%S')}.json"
    return StreamingResponse(
        BytesIO(content),
        media_type="application/json",
        headers={"Content-Disposition": f'attachment; filename="{fname}"'},
    )
