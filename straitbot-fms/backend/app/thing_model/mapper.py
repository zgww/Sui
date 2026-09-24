"""物模型映射器: 机器人 API 响应 → 结构化的物模型属性对象。

输入: robot_api 调用返回的原始 JSON
输出: RuntimeProperties / VersionInfo / PowerInfo / ConfigInfo

这样上层(poller / router)不需要知道 API 字段长什么样,
只需要和物模型对象打交道。换机型时只改这里。
"""
from __future__ import annotations
from dataclasses import dataclass, field
from typing import Optional


@dataclass
class RuntimeProperties:
    """运行时属性快照(cmd=20/21 返回映射)。"""
    status: Optional[int] = None
    doing: Optional[str] = None
    cpu: Optional[float] = None
    temperature: Optional[float] = None
    speed: Optional[float] = None
    angular_speed: Optional[float] = None
    battery: Optional[int] = None
    pose_x: Optional[float] = None
    pose_y: Optional[float] = None
    theta: Optional[float] = None
    floor: Optional[int] = None
    conn_chassis: Optional[bool] = None
    conn_server: Optional[bool] = None
    conn_elevator: Optional[bool] = None
    ptz_pan: Optional[float] = None
    ptz_tilt: Optional[float] = None
    ptz_zoom: Optional[float] = None
    raw: dict = field(default_factory=dict)


@dataclass
class PowerInfo:
    mode: Optional[int] = None
    voltage: Optional[float] = None
    current: Optional[float] = None
    capacity: Optional[int] = None
    remaining: Optional[int] = None
    charging: Optional[int] = None


@dataclass
class VersionInfo:
    application: str = ""
    firmware: str = ""
    hardware: str = ""
    hardware_sn: str = ""
    motion: str = ""
    sdk: str = ""


@dataclass
class AlertItem:
    alert_id: int
    content: str
    level: str = "warning"
    params: dict = field(default_factory=dict)


# ---------- 映射函数 ----------

def map_runtime(raw: dict) -> RuntimeProperties:
    """cmd=20/21 响应 → RuntimeProperties。"""
    if not raw:
        return RuntimeProperties()
    pose = raw.get("pose", {}) or {}
    pt = pose.get("point", {}) or {}
    ptz = pose.get("ptz", {}) or {}
    conns = raw.get("connects", {}) or {}
    return RuntimeProperties(
        status=_i(raw.get("status")),
        doing=raw.get("doing"),
        cpu=_f(raw.get("cpu")),
        temperature=_f(raw.get("temperature")),
        speed=_f(raw.get("speed")),
        angular_speed=_f(raw.get("angular_speed")),
        battery=_i(raw.get("battery")),
        pose_x=_f(pt.get("x")),
        pose_y=_f(pt.get("y")),
        theta=_f(pose.get("theta")),
        floor=_i(raw.get("floor")),
        conn_chassis=conns.get("chassis"),
        conn_server=conns.get("server"),
        conn_elevator=conns.get("elevator"),
        ptz_pan=_f(ptz.get("pan")),
        ptz_tilt=_f(ptz.get("tilt")),
        ptz_zoom=_f(ptz.get("zoom")),
        raw=raw,
    )


def map_power(raw: dict) -> PowerInfo:
    """cmd=22 响应 → PowerInfo。"""
    if not raw:
        return PowerInfo()
    return PowerInfo(
        mode=_i(raw.get("mode")),
        voltage=_f(raw.get("voltage")),
        current=_f(raw.get("current")),
        capacity=_i(raw.get("capacity")),
        remaining=_i(raw.get("remaining")),
        charging=_i(raw.get("charging")),
    )


def map_version(raw: dict) -> VersionInfo:
    """cmd=6 或 cmd=4.version 响应 → VersionInfo。"""
    if not raw:
        return VersionInfo()
    return VersionInfo(
        application=raw.get("application", "") or "",
        firmware=raw.get("firmware", "") or "",
        hardware=raw.get("hardware", "") or "",
        hardware_sn=raw.get("hardware_sn", "") or "",
        motion=raw.get("motion", "") or "",
        sdk=raw.get("sdk", "") or "",
    )


def map_alerts(raw_list: list) -> list[AlertItem]:
    """cmd=10/11 告警列表 → [AlertItem]。"""
    result = []
    for a in (raw_list or []):
        result.append(AlertItem(
            alert_id=_i(a.get("id")) or 0,
            content=a.get("content", ""),
            level=a.get("level", "warning"),
            params=a.get("params", {}) or {},
        ))
    return result


# ---------- 工具 ----------

def _f(v):
    try:
        return float(v)
    except (TypeError, ValueError):
        return None


def _i(v):
    try:
        return int(v)
    except (TypeError, ValueError):
        return None
