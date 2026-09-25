"""全局 Robot 运行时单例。

后端启动时从 ``data/prefabs/robot.prefab.json`` 实例化唯一一台挂轨机器人并运行；
控制板（真机或仿真）不在线时，BoardSrv/RailClient 内部自动重连，不阻塞后端启动。

路由通过 :func:`get_robot` 拿到实例；不要在别处自行 ``Robot.from_prefab``，
保证整进程只有一个 Robot、一条到控制板的连接。
"""
from __future__ import annotations

import logging
from typing import Optional

from ..config import PREFAB_DIR
from .recorder import InspectionRecorder
from .robot import Robot

logger = logging.getLogger("rail.runtime")

# 机器人配置树（单点数据源）
ROBOT_PREFAB_PATH = PREFAB_DIR / "robot.prefab.json"

# 进程内唯一 Robot 实例；未就绪（缺配置/启动失败）时为 None
robot: Optional[Robot] = None


async def start_robot() -> None:
    """实例化并启动 Robot。幂等；失败只告警、不抛出，避免拖垮后端启动。"""
    global robot
    if robot is not None:
        return
    if not ROBOT_PREFAB_PATH.exists():
        logger.warning("[rail] 未找到机器人配置 %s，跳过 Robot 启动", ROBOT_PREFAB_PATH)
        return
    try:
        # 落库器显式注入：Robot 默认不碰数据库（测试不传就没有 DB 依赖），
        # 生产这一份负责把巡检动作数据写进 SQLite 供下游轮询
        r = Robot.from_prefab(ROBOT_PREFAB_PATH, recorder=InspectionRecorder())
        # board.start() 在控制板不在线时会后台自动重连，立即返回
        await r.start()
        robot = r
        logger.info("[rail] Robot %s(%s) 已启动，目标控制板 %s:%s",
                    r.name, r.robot_id, r.ip, r.port)
    except Exception:
        logger.exception("[rail] Robot 启动失败（不影响后端其它功能）")
        robot = None


async def shutdown_robot() -> None:
    """停止并释放 Robot。幂等。"""
    global robot
    if robot is None:
        return
    try:
        await robot.stop()
    except Exception:
        logger.exception("[rail] Robot 停止异常")
    robot = None


def get_robot() -> Optional[Robot]:
    """获取当前 Robot 实例（未就绪返回 None）。"""
    return robot
