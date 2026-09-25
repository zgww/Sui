"""挂轨机器人直接动作控制 + 实时状态。

动作是"调用即下发"的手动/调试直通指令（不经 Robot 状态机决策）：
- POST /jog/forward、/jog/backward：点动走行（底盘持续走，直到 /stop）
- POST /stop：立即停车
- POST /goto：绝对位置移动到目标弧长 x（m）
- POST /inspection：下发一次巡检任务（body 为楼层分段对象或其数组，多楼层合并）；
  有未完成巡检时返回 409 忽略新任务
- GET  /state：机器人配置、连接、位姿、电源、RFID 与状态机当前状态（标准单位）
"""
import json
from dataclasses import asdict
from pathlib import Path

from fastapi import APIRouter, Depends, HTTPException, Request
from pydantic import BaseModel, Field

from ..auth import engineer_only, get_current_user
from ..rail import messages
from ..rail.runtime import get_robot

router = APIRouter(prefix="/api/rail/robot", tags=["rail-robot"])


class JogBody(BaseModel):
    # 点动速率 m/s；不传则用机器人内置默认点动速度
    speed: float | None = Field(default=None, ge=0)


class GotoBody(BaseModel):
    x: float                  # 目标弧长，m


def _robot():
    r = get_robot()
    if r is None:
        raise HTTPException(status_code=503,
                            detail="Robot 未就绪：缺少 robot.prefab.json 或启动失败")
    return r


def _require_connected(r):
    """走行类指令要求控制板在线；未连接（自动重连窗口）时明确报错，避免静默丢帧无反馈。"""
    if not r.state.online:
        raise HTTPException(
            status_code=503,
            detail=f"控制板未连接（{r.state.board_status}），指令未下发；正在自动重连，请稍后重试")


@router.get("/state", dependencies=[Depends(get_current_user)])
def get_state():
    r = _robot()
    s = r.state
    return {
        # 配置（实时取自 prefab 树中的 RobotConfig 节点）
        "robot_id": r.robot_id,
        "name": r.name,
        "version": r.version,
        "robot_type": r.robot_type,
        "ip": r.ip,
        "port": r.port,
        # 连接 / 机台
        "online": s.online,
        "board_status": s.board_status,
        "firmware_version": s.firmware_version,
        # 0x01 初始化控制板结果（连接建立/重连后自动下发；ok=false 时看 error）
        "board_init": {
            "ok": s.board_init_ok,
            "error": s.board_init_error,
            "at": s.board_init_at,
        },
        "chassis_state": s.chassis_state,
        "chassis_mode": s.chassis_mode,
        "state_path": r.sm.state_path(),
        # 标准单位：pose(m/度/m·s⁻¹)、battery(V/A/Ah/℃/%)、rfid(m)
        "pose": asdict(s.pose),
        "battery": {
            **asdict(s.battery),
            "contacted": s.battery.contacted,
            "charging": s.battery.charging,
        },
        "rfid": asdict(s.rfid),
        # 当前巡检（无任务时 inspection_id 为 None）
        "inspection": {
            "busy": r.巡检进行中,
            "inspection_id": s.insp.current_inspection_id,
            "current_floor": s.insp.current_floor,
            "current_waypoint_id": s.insp.current_waypoint_id,
            "waypoint_cursor": s.insp.waypoint_cursor,
            "current_action_index": s.insp.current_action_index,
            "current_action_id": s.insp.current_action_id,
            "current_action_type": s.insp.current_action_type,
            "target_x_m": s.insp.target_x_m,
            "target_lift_m": s.insp.target_lift_m,
            # 设备无进展看门狗：>0 说明走行/升降一度无进展，现场可据此排查
            "move_retry": s.insp.move_watch.retry,
            "lift_retry": s.insp.lift_watch.retry,
            # 最近一次巡检中止原因（看门狗触发；接收新任务/续跑后清空）
            "last_abort": r.last_abort,
            # —— 云台动作（后台线程定位）与视觉动作（拍照/测温）闩锁 ——
            "target_ptz": s.insp.target_ptz,
            "ptz_busy": s.insp.ptz_busy,
            "ptz_done": s.insp.ptz_done,
            "ptz_error": s.insp.ptz_error,
            "vision_kind": s.insp.vision_kind,
            "vision_busy": s.insp.vision_busy,
            "vision_done": s.insp.vision_done,
            "vision_error": s.insp.vision_error,
            "vision_result": s.insp.vision_result,
            "abort_reason": s.insp.abort_reason,
        },
        # 伸缩杆（升降）状态（0x0E 电机状态上发，ID 见 prefab lift_motor_id）
        "lift": {
            **asdict(s.lift),
            "arrived": s.lift.state == messages.MOTOR_ST_ARRIVED,
        },
        # 状态机各子机当前状态（main/charge/floor/insp，用于树视图展开）
        "sm": _sm_states(r),
        # 断点（存在即"有未完成巡检"，开机据此续跑）
        "progress": _progress(r),
        # robot.state 原始结构（RobotState 各 dataclass 字段递归展开）
        # 上层那几个业务字段是给业务页用的便捷视图；这里给的是**状态对象本身**，
        # 字段与 RobotState 一一对应，新增字段会自动出现，供调试/巡检树视图逐项核对。
        "raw_state": _raw_state(r),
    }


def _raw_state(r) -> dict:
    """把 ``robot.state``（RobotState）递归序列化为纯 JSON。

    只用 ``asdict`` 的字段集合，**不引入任何业务重构**——树视图应当忠实反映
    状态对象的真实结构，而不是重排成"看起来更好读"的视图。
    派生属性（如 battery.contacted / lift.arrived）单独附加，便于直接观察。
    """
    s = r.state
    raw = asdict(s)
    # 补充 dataclass @property 派生量（asdict 不含 property）
    raw["battery"]["contacted"] = s.battery.contacted
    raw["battery"]["charging"] = s.battery.charging
    raw["lift"]["arrived"] = s.lift.state == messages.MOTOR_ST_ARRIVED
    return raw


def _sm_states(r) -> dict:
    """4 个状态子机的当前状态（main/charge/floor/insp），按名称做 key。

    返回 ``{"main": {...}, "charge": {...}, ...}`` 而不是列表——前端按名字
    取状态机（``sm.insp.state``）比按下标遍历列表直观得多。
    """
    out = {}
    for sm in r.sm.sms:
        out[sm.name] = {
            "state": sm.st,
            "active": bool(sm.active),
            "signal": sm.signal,
        }
    return out


def _progress(r) -> dict | None:
    """读当前断点（只读，不修改文件）。无断点返回 None。"""
    try:
        p = r._progress_path(r.state.insp.current_inspection_id) \
            if r.state.insp.current_inspection_id else None
        if p is None or not p.exists():
            return None
        return json.loads(p.read_text(encoding="utf-8"))
    except Exception:  # noqa: BLE001  状态接口不应因断点读取失败而报错
        return None


@router.post("/jog/forward", dependencies=[Depends(engineer_only)])
def jog_forward(body: JogBody):
    r = _robot()
    _require_connected(r)
    r.向前() if body.speed is None else r.向前(body.speed)
    return {"ok": True, "action": "forward", "speed_mps": body.speed}


@router.post("/jog/backward", dependencies=[Depends(engineer_only)])
def jog_backward(body: JogBody):
    r = _robot()
    _require_connected(r)
    r.向后() if body.speed is None else r.向后(body.speed)
    return {"ok": True, "action": "backward", "speed_mps": body.speed}


@router.post("/stop", dependencies=[Depends(engineer_only)])
def stop():
    r = _robot()
    r.停止()
    return {"ok": True, "action": "stop"}


@router.post("/goto", dependencies=[Depends(engineer_only)])
def goto(body: GotoBody):
    r = _robot()
    _require_connected(r)
    r.移动到指定位置(body.x)
    return {"ok": True, "action": "goto", "target_x_m": body.x}


@router.post("/inspection", dependencies=[Depends(engineer_only)])
async def dispatch_inspection(request: Request):
    """下发一次巡检任务。

    body 为单个楼层分段对象或其数组（同 id 的多个成员视为同一次巡检的多楼层，
    合并落盘到 data/inspection/{id}.json 并启动巡检）。不要求控制板在线：任务先
    落盘记录、状态机进入巡检，待连接后执行走行。已有未完成巡检时返回 409 忽略。
    """
    r = _robot()
    try:
        payload = await request.json()
    except Exception:
        raise HTTPException(status_code=400, detail="请求体必须是巡检任务 JSON（对象或数组）")
    result = r.接收巡检任务(payload)
    if not result.get("accepted"):
        if result.get("reason") == "busy":
            raise HTTPException(status_code=409, detail=result)
        raise HTTPException(status_code=400, detail=result)
    return result


# 测试巡检任务夹具（机器人控制页"测试巡检"按钮下发，走与正式任务完全相同的接收逻辑）
_TEST_INSPECTION_FILE = (
    Path(__file__).resolve().parents[2] / "tests" / "test_inspection.json"
)


@router.post("/inspection/test", dependencies=[Depends(engineer_only)])
def dispatch_test_inspection():
    """下发内置测试巡检任务（tests/test_inspection.json，多楼层）。

    用于在机器人控制页一键验证完整巡检流程；任务解析、忙时忽略(409)、落盘与
    启动均复用 POST /inspection 的同一套逻辑。
    """
    r = _robot()
    if not _TEST_INSPECTION_FILE.exists():
        raise HTTPException(
            status_code=404,
            detail=f"测试巡检任务文件不存在: {_TEST_INSPECTION_FILE}")
    try:
        payload = json.loads(_TEST_INSPECTION_FILE.read_text(encoding="utf-8"))
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"测试巡检任务文件读取失败: {e}")
    result = r.接收巡检任务(payload)
    if not result.get("accepted"):
        if result.get("reason") == "busy":
            raise HTTPException(status_code=409, detail=result)
        raise HTTPException(status_code=400, detail=result)
    result["source"] = "tests/test_inspection.json"
    return result



@router.post("/inspection/cancel", dependencies=[Depends(engineer_only)])
def cancel_inspection():
    """取消当前正在进行的巡检。

    向机器人状态机发送"取消巡检"信号，主机退出"巡检中"状态。
    """
    r = _robot()
    r.sm.send("取消巡检", "insp")
    return {"code": 0, "msg": "取消巡检信号已发送"}


@router.post("/inspection/progress/clear", dependencies=[Depends(engineer_only)])
def clear_inspection_progress():
    """删除 data/inspection 下全部巡检断点文件（*.progress.json）。

    取消巡检只让状态机退出，磁盘上的断点仍在；此按钮用于人工清理"巡检中"残留状态，
    避免下次开机续跑被当成未完成任务。
    """
    r = _robot()
    removed = r.clear_progress_files()
    return {"code": 0, "removed": removed, "count": len(removed),
            "msg": f"已删除 {len(removed)} 个巡检断点文件"}


@router.post("/charge/go", dependencies=[Depends(engineer_only)])
def go_charge():
    """手动回去充电：主机进"去充电"，走到充电桩坐标（巡检中会先中止巡检再回桩）。"""
    r = _robot()
    r.回去充电()
    return {"code": 0, "msg": "回充信号已发送"}


@router.post("/state/reset", dependencies=[Depends(engineer_only)])
def reset_state_machine():
    """重置状态机：停车、停全部子机、主机回到启动态。"""
    r = _robot()
    r.重置状态机()
    return {"code": 0, "msg": "状态机已重置"}
