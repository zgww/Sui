"""机器人本体 HTTP API 客户端。

约定(来自 API 文档):
  - 统一 POST http://<ip>:<port>/  (注意末尾 /)
  - Header X-ROBOT_ID
  - body 含 cmd 字段
  - 返回 {code, msg, cmd, ts, data}
"""
from __future__ import annotations
from typing import Any, Optional, Tuple
import threading
import httpx
from ..config import settings


class RobotAPIError(Exception):
    def __init__(self, code: int, msg: str, data: Any = None):
        self.code = code
        self.msg = msg
        self.data = data
        super().__init__(f"robot api error code={code} msg={msg}")


def _url(ip: str, port: int) -> str:
    return f"http://{ip}:{port}/"


# 模块级共享客户端: 轮询频率高(status 每10s/台、前端监控每2-3s),
# 每次调用重建 Client 会反复分配连接池/SSL 上下文, 造成内存碎片化与高 churn。
# httpx.Client 线程安全, 可被 FastAPI 线程池与调度器线程并发使用。
_shared_client: Optional[httpx.Client] = None
_client_lock = threading.Lock()


def _get_client() -> httpx.Client:
    """返回进程级共享的 httpx.Client(懒初始化, 连接复用)。"""
    global _shared_client
    if _shared_client is None:
        with _client_lock:
            if _shared_client is None:
                _shared_client = httpx.Client(
                    timeout=settings.robot_api_timeout,
                    limits=httpx.Limits(max_connections=50, max_keepalive_connections=20),
                )
    return _shared_client


def call(ip: str, port: int, robot_id: int, cmd: int, data: Optional[dict] = None,
         timeout: Optional[float] = None) -> Tuple[int, str, Any]:
    """调用机器人 API。返回 (code, msg, data)。失败抛 RobotAPIError / 网络异常。"""
    body = {"cmd": cmd}
    if data:
        body.update(data)
    headers = {"X-ROBOT_ID": str(robot_id), "Content-Type": "application/json"}
    t = timeout or settings.robot_api_timeout
    cli = _get_client()
    resp = cli.post(_url(ip, port), json=body, headers=headers, timeout=t)
    resp.raise_for_status()
    obj = resp.json()
    code = int(obj.get("code", -1))
    msg = obj.get("msg", "")
    d = obj.get("data", {})
    return code, msg, d


# ---- 高层封装 ----
def get_version(ip: str, port: int, robot_id: int) -> dict:
    """cmd=6 版本信息。"""
    code, msg, d = call(ip, port, robot_id, 6)
    return d


def get_config(ip: str, port: int, robot_id: int) -> dict:
    """cmd=4 机器人参数配置。"""
    code, msg, d = call(ip, port, robot_id, 4)
    if code != 0:
        raise RobotAPIError(code, msg, d)
    return d


def set_config(ip: str, port: int, robot_id: int, payload: dict) -> dict:
    """cmd=5 配置系统参数(部分更新)。"""
    code, msg, d = call(ip, port, robot_id, 5, payload)
    if code != 0:
        raise RobotAPIError(code, msg, d)
    return d


def get_status(ip: str, port: int, robot_id: int) -> dict:
    """cmd=21 机器人状态。"""
    code, msg, d = call(ip, port, robot_id, 21)
    return d


def get_power(ip: str, port: int, robot_id: int) -> dict:
    """cmd=22 电源信息。"""
    code, msg, d = call(ip, port, robot_id, 22)
    return d


def get_alerts(ip: str, port: int, robot_id: int) -> list:
    """cmd=10 当前告警列表。"""
    code, msg, d = call(ip, port, robot_id, 10)
    return d.get("alerts", []) if isinstance(d, dict) else []


def charge(ip: str, port: int, robot_id: int, action: int = 1, pile_index: int = 0) -> dict:
    """cmd=23 充电控制 action:1充电 0停止。"""
    code, msg, d = call(ip, port, robot_id, 23, {"action": action, "pile_index": pile_index})
    return d


def reset_and_home(ip: str, port: int, robot_id: int, go_home: bool = False) -> dict:
    """cmd=33 复位/返航。"""
    code, msg, d = call(ip, port, robot_id, 33, {"go_home": go_home})
    return d


def self_check(ip: str, port: int, robot_id: int) -> dict:
    """cmd=7 触发自检。"""
    code, msg, d = call(ip, port, robot_id, 7)
    return d


def clear_nav_alert(ip: str, port: int, robot_id: int) -> dict:
    """cmd=12 清除轮式导航告警。"""
    code, msg, d = call(ip, port, robot_id, 12)
    return d


def raw_call(ip: str, port: int, robot_id: int, cmd: int, data: dict) -> Tuple[int, str, Any]:
    """指令调试: 任意 cmd 透传。"""
    return call(ip, port, robot_id, cmd, data if data else None)
