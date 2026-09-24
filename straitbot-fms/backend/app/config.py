"""配置: 读取 .env / 环境变量。所有运行期参数集中在此。"""
import os
from pathlib import Path
from pydantic_settings import BaseSettings, SettingsConfigDict


BASE_DIR = Path(__file__).resolve().parent.parent          # backend/
# 项目根(含 VERSION 文件) = backend 的上一级
PROJECT_ROOT = BASE_DIR.parent
DATA_DIR = BASE_DIR / "data"
LOGS_DIR = DATA_DIR / "logs"
PKG_DIR = DATA_DIR / "packages"
CALIB_DIR = DATA_DIR / "calibration"   # 航点定标图存储
ORB_DIR = CALIB_DIR / "orb"           # ORB 配准调试过程图存储
DEFAULTS_DIR = BASE_DIR / "defaults"   # 镜像内置默认(物模型/prompts)
PREFAB_DIR = DATA_DIR / "prefabs"      # prefab 节点树目录(可嵌套)
DEFAULT_PREFAB_DIR = BASE_DIR / "app" / "prefab" / "prefabs"  # 内置默认 prefab
FSM_DIR = DATA_DIR / "fsm"             # 机器人状态机(状态动作图)文件目录(可嵌套)
WAYPOINT_PREFAB_DIR = PREFAB_DIR / "waypoint"  # 航点树编排(prefab 机制承载，纯数据，不进规则 runtime)
PLAN_PREFAB_DIR = PREFAB_DIR / "plan"          # 巡检计划编排(同上，另一棵独立的树)
# 检测算法编排：一个 *.prefab.json = 一条检测逻辑（取帧/前处理 -> 算法 -> 后处理：
# 告警 / 转发 / 短信 / 邮件），同上，第三棵独立的树
DETECT_PREFAB_DIR = PREFAB_DIR / "检测算法"
# 枚举编排：一个 *.prefab.json = 一份枚举配置（EnumNode 根 + 若干 EnumItemNode），
# 同上，第四棵独立的树。告警中心的「类型」下拉等筛选项从这里取选项，
# 见 prefab/enum_catalog.py。
ENUM_PREFAB_DIR = PREFAB_DIR / "枚举"
#: **启动时只遍历这一个目录**：`data/prefabs/启动/`。
#:
#: 为什么不是"扫整个 prefabs/ 再排除几个目录"：prefab 根下现在混着好几种东西——
#: 编排数据（waypoint / plan / 检测算法）、告警模板、随手建的示例，它们都**不该
#: 在启动时被激活**。靠"排除名单"维护，每加一种目录就要记得来加一次，漏一个就是
#: 一棵被悄悄激活的树（告警模板就曾经这样被当规则跑起来过）。改成"只认启动目录"
#: 之后，默认不加载，谁要跑谁搬进 `启动/`——**默认安全**。
#:
#: ⚠️ 规则页（`/api/prefab/*` 与前端「Prefab 编排」）的根**也是它**：文件 CRUD、
#: 目录列表、runtime loader 三处必须同一个根，否则会出现"页面看得到这棵树、
#: runtime 里却没有"或者反过来。
BOOT_PREFAB_DIR = PREFAB_DIR / "启动"
# 启动树：程序启动时加载并**激活**，是常驻内存的对象树（常驻任务/调度节点挂在这里，
# 如「巡检计划调度节点」）。它本身也是 *.prefab.json，走同一套 loader/schema，
# 只是被 runtime 单独认出来，保证**先于**其它 prefab 激活。
BOOT_PREFAB_FILE = PREFAB_DIR / "启动.prefab.json"
DB_PATH = DATA_DIR / "fms.db"
ARCHIVE_DIR = DATA_DIR / "point_archive"


def _read_version() -> str:
    for p in (PROJECT_ROOT / "VERSION", BASE_DIR / "VERSION"):
        try:
            if p.exists():
                return p.read_text(encoding="utf-8").strip() or "unknown"
        except Exception:
            pass
    return os.environ.get("FMS_VERSION", "unknown")


APP_VERSION = _read_version()
FMS_MODE = os.environ.get("FMS_MODE", "server")  # server | robot

for _d in (DATA_DIR, LOGS_DIR, PKG_DIR, CALIB_DIR, ORB_DIR, PREFAB_DIR, FSM_DIR,
           WAYPOINT_PREFAB_DIR, PLAN_PREFAB_DIR, DETECT_PREFAB_DIR, ENUM_PREFAB_DIR,
           BOOT_PREFAB_DIR):
    _d.mkdir(parents=True, exist_ok=True)


class Settings(BaseSettings):
    model_config = SettingsConfigDict(env_file=".env", env_file_encoding="utf-8", extra="ignore")

    app_name: str = "Straitbot FMS"
    # 服务
    host: str = "0.0.0.0"
    port: int = 8000
    # 鉴权
    jwt_secret: str = "change-me-in-production-please"
    jwt_algo: str = "HS256"
    token_expire_minutes: int = 60 * 24 * 7          # 7天
    # 默认账号(.env 可覆盖)
    default_engineer_user: str = "admin"
    default_engineer_pass: str = "admin"
    default_operator_user: str = "operator"
    default_operator_pass: str = "operator"
    # 轮询
    poll_status_interval_sec: int = 10        # 状态轮询间隔
    poll_meta_interval_sec: int = 60          # 版本/告警轮询间隔
    # SSH
    ssh_connect_timeout: int = 8
    ssh_cmd_timeout: int = 40
    # 机器人 HTTP API
    robot_api_timeout: float = 5.0
    # 日志保留(天), 0 表示不清理
    default_log_retention_days: int = 30
    # 机器人仿真: TCP 监听(外部上位机连接) + 前端经 WS 桥接
    sim_tcp_host: str = "0.0.0.0"
    sim_tcp_port: int = 50000


settings = Settings()


def DB_URL() -> str:
    return f"sqlite:///{DB_PATH.as_posix()}"


print(f"[config] data_dir={DATA_DIR} db={DB_PATH}")
