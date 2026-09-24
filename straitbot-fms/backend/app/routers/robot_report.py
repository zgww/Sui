"""机器人主动上报接收 (通用入口)。

接收 C++ 推送的各种事件, 暂时只打印日志, 后续按需接入业务。
C++ HttpClient 可能不设 Content-Type, 用 Request.body() 手动解析。
对应 cmd: 9/11/20/29/39/46/107/138
"""

import json
import logging

from fastapi import APIRouter, Request

logger = logging.getLogger("robot-report")
logging.basicConfig(level=logging.INFO, force=True)
router = APIRouter(prefix="/api/robot/report", tags=["robot-report"])


@router.post("/{kind}")
async def robot_report(kind: str, request: Request):
    """通用上报入口。kind: alert|selftest|status|inplace|ptz|env|devicestate|event"""
    try:
        raw = await request.body()
        body = json.loads(raw) if raw else {}
    except Exception:
        body = {"_raw": raw.decode("utf-8", errors="replace") if raw else "(empty)"}

    payload = json.dumps(body, ensure_ascii=False)
    if len(payload) > 300:
        payload = payload[:300] + "..."
    # print 确保输出到 uvicorn 日志流
    print(f"[robot-report/{kind}] {payload}", flush=True)
    return {"ok": True, "kind": kind}
