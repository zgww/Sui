"""仿真页: WebSocket 桥接端点 + 连接状态查询 + 场景配置(障碍物/RFID/轨道)持久化。"""
import json
import re
from datetime import datetime, timezone
from pathlib import Path

from fastapi import APIRouter, HTTPException, WebSocket, WebSocketDisconnect
from pydantic import BaseModel

from ..simulation.bridge import bridge

router = APIRouter(tags=["simulation"])

# 场景配置存储目录: backend/data/sim_scenarios/*.json
SCENARIOS_DIR = Path(__file__).resolve().parents[2] / "data" / "sim_scenarios"


class ScenarioPayload(BaseModel):
    """保存场景配置: 轨道 + 障碍物 + RFID 卡片。"""
    track: dict
    obstacles: list = []
    rfids: list = []


def _safe_name(name: str) -> str:
    """场景名 → 安全文件名(保留中文/字母/数字/下划线/连字符)。"""
    cleaned = re.sub(r"[^\w\u4e00-\u9fff-]", "_", name.strip())
    cleaned = cleaned.strip("_")
    return cleaned or "scenario"


def _scenario_path(name: str) -> Path:
    safe = _safe_name(name)
    if safe != name:
        raise HTTPException(status_code=400, detail=f"场景名含非法字符, 建议: {safe}")
    return SCENARIOS_DIR / f"{safe}.json"


@router.get("/api/simulation/scenarios")
async def list_scenarios():
    """列出全部已保存场景(元信息, 不含正文)。"""
    SCENARIOS_DIR.mkdir(parents=True, exist_ok=True)
    metas = []
    for f in sorted(SCENARIOS_DIR.glob("*.json")):
        try:
            data = json.loads(f.read_text(encoding="utf-8"))
        except (json.JSONDecodeError, OSError):
            continue
        metas.append({
            "name": f.stem,
            "savedAt": data.get("savedAt", ""),
            "obstacleCount": len(data.get("obstacles", [])),
            "rfidCount": len(data.get("rfids", [])),
            "trackKind": (data.get("track") or {}).get("kind", "rect"),
        })
    return {"scenarios": metas}


@router.get("/api/simulation/scenarios/{name}")
async def get_scenario(name: str):
    """读取单个场景配置全文。"""
    p = _scenario_path(name)
    if not p.exists():
        raise HTTPException(status_code=404, detail="场景不存在")
    try:
        data = json.loads(p.read_text(encoding="utf-8"))
    except (json.JSONDecodeError, OSError) as e:
        raise HTTPException(status_code=500, detail=f"场景文件损坏: {e}")
    return {"name": p.stem, **data}


@router.put("/api/simulation/scenarios/{name}")
async def save_scenario(name: str, payload: ScenarioPayload):
    """保存(覆盖)一套场景配置。"""
    SCENARIOS_DIR.mkdir(parents=True, exist_ok=True)
    p = _scenario_path(name)
    doc = {
        "name": p.stem,
        "savedAt": datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds"),
        "track": payload.track,
        "obstacles": payload.obstacles,
        "rfids": payload.rfids,
    }
    p.write_text(json.dumps(doc, ensure_ascii=False, indent=2), encoding="utf-8")
    return {"ok": True, "name": p.stem}


@router.delete("/api/simulation/scenarios/{name}")
async def delete_scenario(name: str):
    """删除一套场景配置。"""
    p = _scenario_path(name)
    if not p.exists():
        raise HTTPException(status_code=404, detail="场景不存在")
    p.unlink()
    return {"ok": True, "name": p.stem}


@router.websocket("/ws/simulation")
async def ws_simulation(ws: WebSocket):
    """前端仿真页 WebSocket。

    - 二进制帧：协议帧，透传给 TCP 上位机；
    - 文本 ``ping``：应用层保活探测，服务端直接回 ``pong``（不经 TCP），
      供前端判断 WS 是否半开（后端重启 / 代理静默断链时，浏览器可能收不到 close）。
    """
    await ws.accept()
    await bridge.attach_ws(ws)
    try:
        while True:
            msg = await ws.receive()
            mtype = msg.get("type")
            if mtype == "websocket.disconnect":
                break
            text = msg.get("text")
            if text is not None:
                if text == "ping":
                    await ws.send_text("pong")
                continue
            data = msg.get("bytes")
            if data is not None:
                bridge.enqueue_to_tcp(data)
    except WebSocketDisconnect:
        pass
    finally:
        await bridge.detach_ws(ws)


@router.get("/api/simulation/status")
async def simulation_status():
    return bridge.status()
