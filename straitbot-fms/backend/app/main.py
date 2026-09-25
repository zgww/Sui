"""FastAPI 入口。

启动顺序:
  1. init_db() 建表
  2. 确保默认账号存在
  3. 注册路由
  4. 启动调度器

直接调试启动（无需 uvicorn CLI，IDE 可直接右键 Run/Debug 本文件）:
  python app/main.py        # 以脚本方式运行
  python -m app.main        # 以模块方式运行
生产仍可用:
  uvicorn app.main:app --host 0.0.0.0 --port 8000
host/port 取 settings（环境变量 HOST / PORT 可覆盖）。
"""

# 以脚本方式直接运行（python app/main.py）时本文件没有父包，下方的相对导入会失败；
# 因此在任何相对导入之前，把 backend 根加入 sys.path，并以包模块 app.main 重新执行一次。
# 以 `python -m app.main` 或 uvicorn 导入时 __package__ == "app"，不会进入此分支。
if __name__ == "__main__" and (__package__ in (None, "")):
    import os as _os
    import runpy as _runpy
    import sys as _sys

    _backend_root = _os.path.abspath(_os.path.join(_os.path.dirname(__file__), ".."))
    if _backend_root not in _sys.path:
        _sys.path.insert(0, _backend_root)
    _runpy.run_module("app.main", run_name="__main__", alter_sys=True)
    raise SystemExit(0)

from contextlib import asynccontextmanager
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from fastapi.staticfiles import StaticFiles

from .config import settings, APP_VERSION, FMS_MODE, CALIB_DIR, DEFAULTS_DIR, DATA_DIR, PREFAB_DIR, DEFAULT_PREFAB_DIR, WAYPOINT_PREFAB_DIR
from .database import init_db, SessionLocal
from .models import User
from .auth import hash_pwd
from .routers import (auth, robots, monitor, robot_cmd, config_robot, logs, ota,
                      settings as r_settings, ai, scan, hotspot, thing_model, control, inspection,
                      video, waypoint, waypoint_tree, orb_calibration, calibration, terminal,
                      robot_report, prefab, simulation, fsm, rail_robot, rail_ptz, point_archive, inspection_plans, waypoint_prefab,
                      plan_prefab, detect_prefab, enum_prefab, alarm)


def _ensure_default_data():
    """data 卷缺失的默认 JSON 从镜像内置 defaults/ 补全(物模型/prompts)。"""
    import shutil
    for fn in ("thing_model.json", "prompts.json"):
        dst = DATA_DIR / fn
        src = DEFAULTS_DIR / fn
        if not dst.exists() and src.exists():
            shutil.copy2(src, dst)
            print(f"[init] 已从默认模板恢复 {fn}")

def _ensure_default_prefabs():
    """data/prefabs 为空时从内置模板复制默认 prefab(可嵌套目录)。"""
    import shutil
    if not any(PREFAB_DIR.rglob("*.prefab.json")) and DEFAULT_PREFAB_DIR.exists():
        shutil.copytree(DEFAULT_PREFAB_DIR, PREFAB_DIR, dirs_exist_ok=True)
        print("[init] 已从内置模板恢复默认 prefab")


def _ensure_default_users():
    db = SessionLocal()
    try:
        if not db.query(User).first():
            db.add(User(username=settings.default_engineer_user,
                        pwd_hash=hash_pwd(settings.default_engineer_pass), role="engineer"))
            db.add(User(username=settings.default_operator_user,
                        pwd_hash=hash_pwd(settings.default_operator_pass), role="operator"))
            db.commit()
            print(f"[init] 已创建默认账号: {settings.default_engineer_user}/{settings.default_operator_user}")
    finally:
        db.close()


@asynccontextmanager
async def lifespan(app: FastAPI):
    init_db()

    # 点位档案库
    from .point_archive.runtime import startup_archive, archive_store
    startup_archive()
    try:
        _ensure_default_prefabs()
        from .routers.prefab import startup_prefab, shutdown_prefab
        startup_prefab()

        # 仿真 TCP<->WebSocket 桥（监听 50000，只启动一次）
        from .config import settings as _s
        from .simulation.bridge import bridge as sim_bridge
        sim_bridge.host = _s.sim_tcp_host
        sim_bridge.port = _s.sim_tcp_port
        await sim_bridge.start()
        try:
            # 机器人单例（BoardSrv 连接下位机/仿真）
            from .rail.runtime import start_robot, shutdown_robot
            await start_robot()
            try:
                _ensure_default_data()
                _ensure_default_users()
                from .services.poller import start_scheduler, shutdown_scheduler
                start_scheduler()
                try:
                    yield
                finally:
                    shutdown_scheduler()
            finally:
                await shutdown_robot()
        finally:
            await sim_bridge.close()
    finally:
        try:
            from .routers.prefab import shutdown_prefab
            shutdown_prefab()
        finally:
            archive_store.close()
        from .rail.hkptz_runtime import shutdown_hkptz
        shutdown_hkptz()


app = FastAPI(title=settings.app_name, lifespan=lifespan,
              docs_url="/api/docs", redoc_url=None, openapi_url="/api/openapi.json")
point_archive.install_error_handlers(app)

app.add_middleware(
    CORSMiddleware, allow_origins=["*"], allow_credentials=True,
    allow_methods=["*"], allow_headers=["*"],
)

for r in (auth.router, robots.router, monitor.router, robot_cmd.router,
          config_robot.router, logs.router, ota.router, r_settings.router,
          ai.router, scan.router, hotspot.router, thing_model.router,
          control.router, inspection.router, video.router, waypoint.router,
          waypoint_tree.router, orb_calibration.router, calibration.router,
          terminal.router, robot_report.router, prefab.router, simulation.router,
          fsm.router, point_archive.router, inspection_plans.router, rail_robot.router, rail_ptz.router,
          waypoint_prefab.router, plan_prefab.router, detect_prefab.router,
          enum_prefab.router, alarm.router):
    app.include_router(r)

# 定标图静态访问(/data/calibration/xxx.jpg)
app.mount("/data/calibration", StaticFiles(directory=str(CALIB_DIR)), name="calibration")

# 航点树抓拍图静态访问(/data/prefabs/waypoint/<子树>/images/xxx.jpg)
# `<img src>` 带不了 Authorization 头，ActionPointNode.imageUrl 存的又是相对
# prefab 文件的路径，所以整棵航点树目录要挂出来——挂出来的都是编排数据，
# 与定标图同一套暴露策略。
app.mount("/data/prefabs/waypoint", StaticFiles(directory=str(WAYPOINT_PREFAB_DIR)),
          name="waypoint-prefab")

# 巡检图片静态访问(/data/inspection/<inspection_id>/xxx.jpg)
# FMS 本地检测落盘的图存在 data/inspection/ 下，数据库里存的是相对于该目录的
# 相对路径，前端直接拼 `/data/inspection/` 前缀就能加载。
app.mount("/data/inspection", StaticFiles(directory=str(DATA_DIR / "inspection")),
          name="inspection-files")


@app.get("/api/health")
def health():
    return {"ok": True, "app": settings.app_name, "version": APP_VERSION, "mode": FMS_MODE}


if __name__ == "__main__":
    # 内建启动入口：直接运行本文件即可调试，不必敲 uvicorn 命令。
    # reload=False 不 fork 重载子进程，保证 IDE 断点与单进程日志正常；
    # 需要热重载做前端联调时仍可改用 uvicorn CLI --reload。
    import uvicorn

    uvicorn.run(
        "app.main:app",
        host=settings.host,
        port=settings.port,
        reload=True,
        log_level="info",
    )
