"""海康云台相机（PTZ）控制 + 抓图。

云台走原生 HCNetSDK（:mod:`app.rail.hkptz_runtime` 的单例会话），端点全部为**同步
``def``**——SDK 调用是阻塞式的，交给 FastAPI 线程池执行，不阻塞事件循环。

- GET  /state：相机配置 + 连接状态 + 设备信息（不触发连接）
- POST /connect、/disconnect：显式登录/注销（move/snapshot 也会按需自动登录）
- POST /move：云台方向/变焦（command + stop + speed），按住式控制用 stop 收尾
- POST /stop：停止全部云台运动
- POST /preset：预置点 goto/set/clean
- GET  /snapshot：抓一张 JPEG（image/jpeg）
"""
from fastapi import APIRouter, Depends, HTTPException
from fastapi.responses import Response
from pydantic import BaseModel, Field

from ..auth import engineer_only, get_current_user
from ..rail import HkPtz as hk
from ..rail.hkptz_runtime import (config_info, disconnect_hkptz, get_hkptz,
                                  peek_hkptz)
from ..rail.HkPtz import HkPtzError

router = APIRouter(prefix="/api/rail/ptz", tags=["rail-ptz"])

# 命令名 -> HCNetSDK 云台命令常量（前端传语义名，避免暴露原始数值）
_MOVE_CMDS = {
    "left": hk.PAN_LEFT,
    "right": hk.PAN_RIGHT,
    "up": hk.TILT_UP,
    "down": hk.TILT_DOWN,
    "zoomin": hk.ZOOM_IN,
    "zoomout": hk.ZOOM_OUT,
}


class MoveBody(BaseModel):
    command: str = Field(description="left/right/up/down/zoomin/zoomout")
    stop: bool = False
    speed: int = Field(default=hk.DEFAULT_PTZ_SPEED, ge=1, le=7)


class PresetBody(BaseModel):
    action: str = Field(description="goto/set/clean")
    index: int = Field(ge=1, le=255)


def _connected_ptz():
    """取已登录的相机；未配置 -> 503，SDK/登录错误 -> 503（带可读原因）。"""
    try:
        return get_hkptz()
    except ValueError as e:
        raise HTTPException(status_code=503, detail=f"云台相机未配置：{e}")
    except HkPtzError as e:
        raise HTTPException(status_code=503, detail=f"云台相机连接失败：{e}")


def _safe_device_info(p) -> dict | None:
    try:
        return p.device_info()
    except Exception:
        return None


@router.get("/state", dependencies=[Depends(get_current_user)])
def state():
    """相机配置与连接状态。不主动连接——面板据此显示"未连接"并提供连接按钮。"""
    try:
        cfg = config_info()
    except ValueError as e:
        return {"configured": False, "connected": False, "reason": str(e)}
    p = peek_hkptz()
    connected = bool(p and p.connected)
    return {
        "configured": True,
        "connected": connected,
        **cfg,
        "device_info": _safe_device_info(p) if connected else None,
    }


@router.post("/connect", dependencies=[Depends(engineer_only)])
def connect():
    p = _connected_ptz()
    return {"ok": True, "connected": True, "device_info": _safe_device_info(p)}


@router.post("/disconnect", dependencies=[Depends(engineer_only)])
def disconnect():
    disconnect_hkptz()
    return {"ok": True, "connected": False}


@router.post("/move", dependencies=[Depends(engineer_only)])
def move(body: MoveBody):
    cmd = _MOVE_CMDS.get(body.command)
    if cmd is None:
        raise HTTPException(status_code=400,
                            detail=f"未知云台命令: {body.command}（可用: {list(_MOVE_CMDS)}）")
    p = _connected_ptz()
    try:
        p.ptz(cmd, stop=body.stop, speed=body.speed)
    except HkPtzError as e:
        raise HTTPException(status_code=503, detail=str(e))
    return {"ok": True, "command": body.command, "stop": body.stop, "speed": body.speed}


@router.post("/stop", dependencies=[Depends(engineer_only)])
def stop():
    p = _connected_ptz()
    try:
        p.stop()
    except HkPtzError as e:
        raise HTTPException(status_code=503, detail=str(e))
    return {"ok": True}


@router.post("/preset", dependencies=[Depends(engineer_only)])
def preset(body: PresetBody):
    p = _connected_ptz()
    fn = {"goto": p.goto_preset, "set": p.set_preset, "clean": p.clean_preset}.get(body.action)
    if fn is None:
        raise HTTPException(status_code=400,
                            detail=f"未知预置点操作: {body.action}（可用: goto/set/clean）")
    try:
        fn(body.index)
    except HkPtzError as e:
        raise HTTPException(status_code=503, detail=str(e))
    return {"ok": True, "action": body.action, "index": body.index}


@router.get("/snapshot", dependencies=[Depends(get_current_user)])
def snapshot():
    """抓一张 JPEG（按需自动登录）。返回 image/jpeg 字节流。"""
    p = _connected_ptz()
    try:
        data = p.snapshot()
    except HkPtzError as e:
        raise HTTPException(status_code=503, detail=str(e))
    return Response(content=data, media_type="image/jpeg",
                    headers={"Cache-Control": "no-store"})
