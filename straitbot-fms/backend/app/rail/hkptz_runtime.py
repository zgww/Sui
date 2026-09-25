"""全局海康云台相机（HkPtz）运行时单例。

从与 Robot 同一份 ``data/prefabs/robot.prefab.json`` 里找 ``HkPtzConfig`` 节点，
懒创建 :class:`app.rail.HkPtz.HkPtz` 并在首次使用时登录设备；之后整个进程复用同一
SDK 会话（HCNetSDK 登录句柄）。

路由通过 :func:`get_hkptz` 拿到"已连接"的实例；:func:`peek_hkptz` 只窥视当前实例
（不触发连接），供状态查询用。所有 HCNetSDK 调用都是同步阻塞的，路由端点应声明为
普通 ``def``（FastAPI 会放到线程池执行），不要放进事件循环。
"""
from __future__ import annotations

import logging
import threading
from typing import Optional

from ..config import PREFAB_DIR
from .HkPtz import HkPtz, HkPtzError  # noqa: F401  (HkPtzError 供路由捕获)

logger = logging.getLogger("rail.hkptz_runtime")

# 云台相机配置与机器人同源（HkPtzConfig 挂在 robot.prefab.json 的节点树下）
PTZ_PREFAB_PATH = PREFAB_DIR / "robot.prefab.json"

_lock = threading.Lock()
_ptz: Optional[HkPtz] = None


def _create() -> HkPtz:
    """从 prefab 构建 HkPtz（不登录）。未找到 HkPtzConfig 抛 ValueError。"""
    return HkPtz.from_prefab(PTZ_PREFAB_PATH)


def get_hkptz() -> HkPtz:
    """返回"已登录"的 HkPtz 单例：懒创建 + 懒登录。

    - 未配置相机（缺 HkPtzConfig）抛 ``ValueError``；
    - SDK 缺失 / 登录失败抛 ``HkPtzError``。
    路由据此转成 4xx/5xx。
    """
    global _ptz
    with _lock:
        if _ptz is None:
            _ptz = _create()
        ptz = _ptz
        if not ptz.connected:
            ptz.connect()   # 失败抛 HkPtzError，_ptz 保留以便下次重试
        return ptz


def peek_hkptz() -> Optional[HkPtz]:
    """只返回当前实例（可能未连接/未创建），不触发任何网络调用。"""
    return _ptz


def config_info() -> dict:
    """读取云台配置（懒创建实例但不登录），供状态展示。未配置抛 ValueError。"""
    global _ptz
    with _lock:
        if _ptz is None:
            _ptz = _create()
        p = _ptz
    return {"ip": p.ip, "port": p.port, "channel": p.channel, "username": p.username}


def disconnect_hkptz() -> None:
    """注销当前 SDK 会话（幂等）。实例保留，下次 get_hkptz 会重新登录。"""
    with _lock:
        if _ptz is not None:
            try:
                _ptz.close()
            except Exception:
                logger.exception("[hkptz] 注销相机会话异常")


def shutdown_hkptz() -> None:
    """应用关闭时释放相机会话。SDK 全局初始化为进程级单例，不在此 Cleanup。"""
    disconnect_hkptz()
