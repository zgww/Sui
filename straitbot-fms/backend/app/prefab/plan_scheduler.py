"""巡检计划调度的**纯逻辑**：扫文件 -> 抽计划 -> 算到期时刻 -> 去重。

这部分刻意与"节点类 + 线程"分开：节点只负责起停线程，判断"这一刻该不该触发"
全在这里，可以直接单测（不启线程、不碰运行时、不碰数据库）。

## 扫的是什么

`data/prefabs/plan/**/*.prefab.json` —— 巡检计划编排页维护的那批文件。它们是
**纯数据**（根是 `PlanGroupNode`，下面挂 N 条 `InspectionPlanNode`），不进规则
runtime：本模块按文件读取，不通过 `PrefabLoader`，也不 `registry.build`成对象树
（构建成对象没有意义，也拿不到树外信息；spec 就是它的存储格式）。

## 到期怎么算

计划里的「每日调度」是 `start_time` / `end_time` / `interval_minutes`（`HH:MM`，
24 小时制，本地时区）。与前端 `utils/planSelect.ts::scheduleSlots` 同一套规则：

- 时刻 = `start + n*interval`，**末次不晚于 end**；
- `end < start`（跨零点）**不排**（真机上"跨天那段算今天还是明天"必须跟调度器
  对齐语义，含糊处理只会让现场对不上账，夜间巡检请拆成两条计划）；
- `start == end` 算"整天只有一个时刻"；
- 时间串或间隔不合法 -> 该条调度不排（由调用方记错误）。

## 去重 / 停机容错

线程每 `poll_interval` 秒扫一次，同一个时刻很容易被扫到两次（尤其间隔小于扫描
间隔时），所以"触发过"要**按槽位时刻**记账，且**落盘**：进程重启后内存里的账本
没了，不落盘就会把重启前刚触发过的那条再发一次（真机上就是机器人被叫出去两趟）。

反过来，停机很久后重启，账面会攒下一堆过期槽位——那些**不补**（`misfire_grace`
之外的过期时刻直接丢弃），只补最后一个还没超过容错窗口的。这与
`services/inspection_dispatch.tick_plans` 里"超过 5 分钟容错窗口就跳过"是同一条
规矩：宁可漏一次，也不要让机器人在凌晨把一天的量补回来。

## 触发之后：怎么变成一次真巡检

"到点了"到"机器人动起来"之间还差一步——把计划里挑的航点/测点变成机器人认得的
巡检任务 JSON。这一步在 `dispatch_inspection`（本模块底部）：

    build_from_plan(...)        # 航点树 -> 楼层分段载荷（各节点自己组织字段）
    robot.接收巡检任务(payload)  # 机器人自己决定要不要接（忙就拒）

它也是 `set_inspection_trigger` 注册的**默认回调**，由
`routers/prefab.startup_prefab` 调 `install_default_trigger()` 装上。节点
`dry_run=True`（默认）时压根不会走到这里，所以配上去先观察、确认无误再去掉演练。
"""
from __future__ import annotations

import json
import logging
import re
import threading
from dataclasses import dataclass, field
from datetime import datetime, timedelta
from pathlib import Path
from typing import Any, Iterable, Optional

logger = logging.getLogger(__name__)

#: 计划文件后缀（与 `prefab_store` / `plan_prefab` 的约定一致）
PLAN_SUFFIX = ".prefab.json"

#: 记账本保留多久（天）。更老的键会被丢掉，免得文件无限膨胀
STATE_KEEP_DAYS = 7

#: 编排侧的检测方式默认值（`InspectionPlanNode.detect_type` 的 default 也是它）
DETECT_FMS = "fms"
DETECT_PLATFORM = "platform"

_HM_RE = re.compile(r"^(\d{1,2}):(\d{2})$")


def normalize_detect_type(v: Any) -> str:
    """计划的 `detect_type` 归一化：**只有明确写了 `platform` 才是上传平台，其余一律 `fms`**。

    ⚠️ 与 `task_executor.normalize_detect_type` 的**回退方向相反**，这是有意的：
    - `task_executor` 那边判的是"**动作数据**该怎么处理"，缺省必须回落到
      `platform`（旧版行为）—— 一条历史数据没写这个字段时，绝不能自作主张
      在本机跑检测；
    - 这里是"**计划编排**里的显式配置"，用户在检视器里看到并选择的就是它，
      默认值是 `fms`。所以缺省/空值回落 `fms`。

    两边各自回落到自己的默认值，只有值**真的写出来**时才需要一致（写入
    `detectType` 之后，`rail/inspection.py` 的 validator 会原样接受）。
    """
    s = str(v or "").strip().lower()
    if s == DETECT_PLATFORM:
        return DETECT_PLATFORM
    if s and s != DETECT_FMS:
        logger.warning("[prefab] 计划的 detect_type=%r 不认识，按 %s 处理", v, DETECT_FMS)
    return DETECT_FMS


# ---------------------------------------------------------------- 数据结构

@dataclass(frozen=True)
class ScheduleSpec:
    """一条「每日调度」：`start`/`end` 是 `HH:MM`，`interval` 单位分钟。"""

    start: str
    end: str
    interval: int
    label: str = ""


@dataclass
class PlanJob:
    """一条**可触发**的巡检计划（已把航点/测点/调度从计划节点下收集齐）。

    `key` 是去重主键：优先用计划编号 `plan_id`（它存在的意义就是对外标识这条
    计划），没填才退回"文件 + 计划名"。⚠️ 因此改计划名会让账本对不上（视为一条
    新计划，可能重复触发一次）——真上场前把 `plan_id` 填上。
    """

    key: str
    file: str
    plan_name: str
    plan_id: str
    robot_name: str
    priority: int
    #: 动作数据怎么作用到检测（`fms` 本机检测 / `platform` 上传平台）。
    #: 缺省 `fms` —— 与编排侧 `InspectionPlanNode.detect_type` 的默认一致。
    #: ⚠️ 与 `rail/inspection.py::FloorTask` 的缺省(`platform`)不同是有意的：
    #: 那边是"老 JSON 没这个字段"的兼容缺省，这里是编排侧的显式配置。
    detect_type: str = "fms"
    schedules: list[ScheduleSpec] = field(default_factory=list)
    #: 每条航点指定：`{source, include_all, waypoint_ids}`
    waypoints: list[dict] = field(default_factory=list)
    #: 每条测点指定：`{include_all, point_ids}`
    points: list[dict] = field(default_factory=list)

    def payload(self, slot: datetime, schedule: Optional[ScheduleSpec]) -> dict:
        """触发事件 / 下发回调拿到的载荷（JSON 友好的普通 dict）。

        `schedule` 允许 **None**：手动「立即执行」的草稿计划可能一条「每日调度」
        都没配（`plan_job_at` 刻意不要求有调度），那就没有"这次是哪个时段"可言。
        这时候 `schedule` 出 `None`，**不能**塞一个空壳 `ScheduleSpec` 进去 ——
        下游看到 `{"start": "", "end": "", "interval_minutes": 0}` 会当成"配了个
        空时段"，比明确的 None 更容易误判。
        """
        return {
            "plan_key": self.key,
            "plan_id": self.plan_id,
            "plan_name": self.plan_name,
            "robot_name": self.robot_name,
            "priority": self.priority,
            "detect_type": self.detect_type,
            "file": self.file,
            "scheduled_at": slot.isoformat(),
            "schedule": None if schedule is None else {
                "start": schedule.start,
                "end": schedule.end,
                "interval_minutes": schedule.interval,
                "label": schedule.label,
            },
            "waypoints": self.waypoints,
            "points": self.points,
        }


# ---------------------------------------------------------------- 文件扫描

def iter_plan_files(root: Path | str) -> list[Path]:
    """计划目录下所有 `*.prefab.json`，**按路径排序**（顺序稳定 = 日志可读）。"""
    p = Path(root)
    if not p.exists():
        return []
    return sorted(q for q in p.rglob(f"*{PLAN_SUFFIX}") if q.is_file())


def read_plan_spec(path: Path) -> dict:
    return json.loads(Path(path).read_text(encoding="utf-8"))


# ---------------------------------------------------------------- 计划抽取

def _props(node: Any) -> dict:
    return node.get("properties") or {} if isinstance(node, dict) else {}


def _enabled(node: Any) -> bool:
    """`enabled` 缺省视为 True，只有显式 `false` 才算停用（与前端一致）。"""
    return _props(node).get("enabled") is not False


def _schedule_of(node: dict) -> Optional[ScheduleSpec]:
    if node.get("type") != "DailyScheduleNode":
        return None
    p = _props(node)
    return ScheduleSpec(
        start=str(p.get("start_time") or ""),
        end=str(p.get("end_time") or ""),
        interval=int(p.get("interval_minutes") or 0),
        label=str(p.get("name") or ""),
    )


def _collect_under(node: dict, out: dict) -> None:
    """把计划节点下的"航点指定 / 测点指定 / 每日调度"收进 `out`（只看启用的）。"""
    t = node.get("type")
    p = _props(node)
    if t == "WaypointSelectNode":
        out["waypoints"].append({
            "source": str(p.get("source") or ""),
            "include_all": p.get("include_all") is not False,
            "waypoint_ids": [str(x) for x in (p.get("waypoint_ids") or [])],
        })
    elif t == "PointSelectNode":
        out["points"].append({
            "include_all": p.get("include_all") is not False,
            "point_ids": [str(x) for x in (p.get("point_ids") or [])],
        })
    elif t == "DailyScheduleNode":
        s = _schedule_of(node)
        if s is not None:
            out["schedules"].append(s)
    for c in node.get("children") or []:
        if isinstance(c, dict) and _enabled(c):
            _collect_under(c, out)


def _plan_job(file_rel: str, node: dict, path: str, *,
              require_schedule: bool = True) -> Optional[PlanJob]:
    """一个 `InspectionPlanNode` -> 一条可触发计划。

    `require_schedule=True`（定时触发用）时，没有「每日调度」就返回 None
    （没有周期就谈不上触发，连日志都不该刷）。
    手动「立即执行」传 `False`：只配了航点还没配时间的草稿计划也应该能试跑。
    """
    p = _props(node)
    out: dict = {"waypoints": [], "points": [], "schedules": []}
    for c in node.get("children") or []:
        if isinstance(c, dict) and _enabled(c):
            _collect_under(c, out)
    if require_schedule and not out["schedules"]:
        return None
    plan_id = str(p.get("plan_id") or "").strip()
    name = str(p.get("name") or "").strip() or plan_id or path
    return PlanJob(
        key=f"{file_rel}#{plan_id}" if plan_id else f"{file_rel}#{name}",
        file=file_rel,
        plan_name=name,
        plan_id=plan_id,
        robot_name=str(p.get("robot_name") or "").strip(),
        priority=int(p.get("priority") or 0),
        detect_type=normalize_detect_type(p.get("detect_type")),
        schedules=out["schedules"],
        waypoints=out["waypoints"],
        points=out["points"],
    )


def plan_job_at(spec: dict, node_path: str, *, file_rel: str = "") -> Optional[PlanJob]:
    """按**节点路径**从一棵计划树 spec 里取出**那一条**计划（"立即执行"用）。

    与 `collect_jobs` 走的是同一套抽取（`_plan_job`），所以"立即执行"和"到点触发"
    拿到的 plan 内容必然一致，不会两边漂移。

    ⚠️ 与 `collect_jobs` 有一处**刻意的差别**：这里**不要求有「每日调度」**。
    手动点「立即执行」的意思是"就现在，跑这一次"——一条只配了航点、还没配
    时间范围的草稿计划，照样应该能立刻试跑（定时触发那边才必须有调度，
    没有周期就谈不上"到点"）。

    停用的节点照样拒绝：`enabled is False` 的语义是"不参与运行"，手动执行
    也不例外（否则用户会以为"停用了但手点还能跑"是正常的）。

    :param node_path: `root`、`root/children/0`、`root/children/0/children/2` 这种
        以斜杠分隔的路径（与前端树节点的 `value` 同一套编码）。
    :raises ValueError: 路径不存在 / 指向的不是 `InspectionPlanNode` / 节点已停用。
    """
    node = _node_at(spec, node_path)
    if node is None:
        raise ValueError(f"节点路径不存在: {node_path}")
    if not _enabled(node):
        raise ValueError("这条计划已停用（enabled=false），先启用再执行")
    if node.get("type") != "InspectionPlanNode":
        raise ValueError(
            f"只能立即执行「巡检计划」节点，当前是 {node.get('type') or '未知类型'}")
    job = _plan_job(file_rel, node, node_path, require_schedule=False)
    if job is None:                       # require_schedule=False 时不会走到，防御性兜底
        raise ValueError("这条计划没有可执行的内容")
    return job


def _node_at(spec: Any, node_path: str) -> Optional[dict]:
    """按 `root/children/0/children/2` 路径取节点。任何一段对不上就返回 None。

    路径编码与前端树节点一致（`root` 后面跟成对的 `children` / 下标）。
    逐段解析、不跳段：`root/children/0/children/1` 就是"根的第 0 个孩子的
    第 1 个孩子"。写成 `root/0` 这种缺 `children` 的路径直接判不合法。
    """
    if not isinstance(spec, dict):
        return None
    parts = [s for s in str(node_path or "").strip().strip("/").split("/") if s]
    if not parts or parts[0] != "root":
        return None
    cur: Any = spec.get("root")
    i = 1
    while i < len(parts):
        # 每前进一层都要 `children` + 下标两个片段，缺一不可
        if parts[i] != "children" or i + 1 >= len(parts):
            return None
        try:
            idx = int(parts[i + 1])
        except (TypeError, ValueError):
            return None
        if not isinstance(cur, dict):
            return None
        kids = cur.get("children") or []
        if idx < 0 or idx >= len(kids):
            return None
        cur = kids[idx]
        i += 2
    return cur if isinstance(cur, dict) else None


def collect_jobs(
    root: Path | str,
    *,
    robot_name: str = "",
) -> tuple[list[PlanJob], list[str]]:
    """扫目录 -> 全部可触发计划 + 错误列表。

    跳过：停用节点（含停用计划的整棵子树）、没有"每日调度"的计划、
    `robot_name` 参数非空时不匹配该机器人的计划（空 = 不限）。
    """
    root_p = Path(root)
    jobs: list[PlanJob] = []
    errors: list[str] = []

    def walk(node: Any, path: str, file_rel: str) -> None:
        if not isinstance(node, dict):
            return
        if not _enabled(node):
            return
        if node.get("type") == "InspectionPlanNode":
            job = _plan_job(file_rel, node, path)
            if job is not None and (not robot_name or not job.robot_name
                                    or job.robot_name == robot_name):
                jobs.append(job)
            # 计划里再套计划（嵌套）也照样往下找：不重复触发同一层，但支持"计划组"
            for i, c in enumerate(node.get("children") or []):
                walk(c, f"{path}/children/{i}", file_rel)
            return
        for i, c in enumerate(node.get("children") or []):
            walk(c, f"{path}/children/{i}", file_rel)

    for f in iter_plan_files(root_p):
        try:
            spec = read_plan_spec(f)
        except Exception as exc:
            errors.append(f"{f}: {exc}")
            continue
        if not isinstance(spec, dict) or not isinstance(spec.get("root"), dict):
            errors.append(f"{f}: 顶层缺少 root 节点")
            continue
        try:
            rel = str(f.relative_to(root_p)).replace("\\", "/")
        except ValueError:
            rel = f.name
        walk(spec["root"], "root", rel)

    return jobs, errors


# ---------------------------------------------------------------- 到期时刻

def parse_hm(v: Any) -> Optional[int]:
    """`"HH:MM"` -> 当日分钟数；不合法返回 None（**不接受 `"8:5"` 半截写法**）。"""
    if not isinstance(v, str):
        return None
    m = _HM_RE.match(v.strip())
    if not m:
        return None
    h, mi = int(m.group(1)), int(m.group(2))
    if h > 23 or mi > 59:
        return None
    return h * 60 + mi


def due_slots(
    sched: ScheduleSpec,
    now: datetime,
    since: Optional[datetime] = None,
    grace_seconds: int = 300,
) -> list[datetime]:
    """`now` 这一天里、在 `(since, now]` 内**应当触发**的时刻（升序）。

    - 只补**最后**一个过期但未超容错窗口的槽位由调用方决定（这里全量返回，
      调用方取 `[-1]`），因为"补几次"是策略，不是计算；
    - `grace_seconds`：超过这个迟到量的槽位直接丢弃（停机期间不补触发）。
    """
    a = parse_hm(sched.start)
    b = parse_hm(sched.end)
    if a is None or b is None:
        return []
    step = int(sched.interval or 0)
    if step <= 0:
        return []
    if b < a:          # 跨零点：刻意不支持
        return []

    base = now.replace(hour=0, minute=0, second=0, microsecond=0)
    if b == a:
        minutes = [a]
    else:
        minutes = list(range(a, b + 1, step))
        if minutes and minutes[-1] > b:
            minutes = [m for m in minutes if m <= b]

    grace = timedelta(seconds=max(0, int(grace_seconds)))
    out: list[datetime] = []
    for m in minutes:
        slot = base + timedelta(minutes=m)
        if slot > now:
            continue
        if since is not None and slot <= since:
            continue
        if now - slot > grace:
            continue
        out.append(slot)
    return out


# ---------------------------------------------------------------- 触发账本

class PlanSchedulerState:
    """"哪个槽位已经触发过"的账本（**落盘**，重启后不至于重复触发）。

    只记 `key -> 槽位时刻(iso)`。文件损坏/读不出来时**从头开始**（宁可重复一次
    也不要因为一个坏文件整个调度器不工作）——重复触发的代价由 `dry_run` 兜着。
    """

    def __init__(self, path: Path | str) -> None:
        self.path = Path(path)
        self._lock = threading.Lock()
        self._data: dict[str, str] = {}
        self.load()

    def load(self) -> None:
        try:
            raw = json.loads(self.path.read_text(encoding="utf-8"))
            if isinstance(raw, dict):
                self._data = {str(k): str(v) for k, v in raw.items()}
        except FileNotFoundError:
            self._data = {}
        except Exception as exc:
            logger.warning("[prefab] 巡检计划调度账本读取失败，从空账本开始: %s", exc)
            self._data = {}

    def _save(self) -> None:
        try:
            self.path.parent.mkdir(parents=True, exist_ok=True)
            tmp = self.path.with_suffix(self.path.suffix + ".tmp")
            tmp.write_text(json.dumps(self._data, ensure_ascii=False, indent=0),
                           encoding="utf-8")
            tmp.replace(self.path)
        except Exception as exc:
            logger.warning("[prefab] 巡检计划调度账本写入失败: %s", exc)

    def last(self, key: str) -> Optional[datetime]:
        with self._lock:
            raw = self._data.get(key)
        if not raw:
            return None
        try:
            return datetime.fromisoformat(raw)
        except ValueError:
            return None

    def mark(self, key: str, slot: datetime) -> bool:
        """记账。**返回 True 表示这条是新的**（调用方据此触发），已记过返回 False。"""
        iso = slot.isoformat()
        with self._lock:
            if self._data.get(key) == iso:
                return False
            self._data[key] = iso
            self._prune(slot)
            self._save()
        return True

    def _prune(self, now: datetime, keep_days: int = STATE_KEEP_DAYS) -> None:
        """丢掉 `keep_days` 天以前的键（必须在锁内调用）。"""
        limit = now - timedelta(days=keep_days)
        for k in [k for k in self._data]:
            try:
                if datetime.fromisoformat(self._data[k]) < limit:
                    del self._data[k]
            except ValueError:
                del self._data[k]


# ---------------------------------------------------------------- 触发回调

_default_trigger: Any = None


def set_inspection_trigger(fn: Any) -> None:
    """注册"真的下发巡检任务"的回调（`payload -> None`）。

    这是**唯一的真下发入口**：节点自己不知道怎么把一条计划变成设备动作
    （那需要机器人、地图、测点档案库合成巡检内容，见
    `services/inspection_dispatch.dispatch`）。没注册或节点 `dry_run=True` 时，
    节点只记日志 + emit `inspection_due` 事件。
    """
    global _default_trigger
    _default_trigger = fn


def get_inspection_trigger() -> Any:
    return _default_trigger


def clear_inspection_trigger() -> None:
    global _default_trigger
    _default_trigger = None


def slot_keys(jobs: Iterable[PlanJob]) -> list[str]:
    """（调试/测试用）列出账本里会用到的键。"""
    return [j.key for j in jobs]


# ---------------------------------------------------------------- 真下发

def dispatch_inspection(
    job_payload: dict,
    *,
    robot: Any = None,
    root_dir: Optional[Path] = None,
    fresh_ids: bool = False,
) -> dict:
    """一条到期计划 -> **真的下发**给机器人（默认触发回调）。

    两步：
    1. `inspection_build.build_from_plan`：读计划的「航点指定」指向的航点树，
       **问每个节点要**它自己的航点/动作/测温字段（`to_inspection_json`），
       按楼层汇总成 `tests/test_inspection.json` 那个形状的载荷；
    2. `robot.接收巡检任务(payload)`：机器人自己判断能不能接（巡检中就是
       `busy`），接了才落盘记录并启动状态机。

    **全程不抛**：任何一步失败都返回 `{"accepted": False, "reason": ...}`。
    调用方是调度线程——抛出去除了刷一屏堆栈没有别的后果，而"这次为什么没发出去"
    得在返回值里说清楚（日志里也记一遍）。

    - `robot`：注入的机器人实例，测试用；`None` = 取全局 `get_robot()`；
    - `root_dir`：航点树根目录，测试用；`None` = `data/prefabs/waypoint`。
    """
    plan_name = str(job_payload.get("plan_name") or "").strip() or "未命名计划"
    plan_key = str(job_payload.get("plan_key") or "")

    def reject(reason: str, **extra: Any) -> dict:
        out = {"accepted": False, "reason": reason, "plan_key": plan_key,
               "plan_name": plan_name}
        out.update(extra)
        logger.warning("[prefab] 巡检计划「%s」下发失败: %s", plan_name, reason)
        return out

    # 1) 找机器人
    if robot is None:
        try:
            from ..rail.runtime import get_robot
            robot = get_robot()
        except Exception as exc:      # 导入失败也算"没有机器人"，不能让线程挂掉
            return reject(f"取机器人实例失败: {exc}")
    if robot is None:
        return reject("没有可用的机器人实例（robot.prefab.json 没配或启动失败）")

    # 2) 这台机器人是不是这条计划要的那台
    want = str(job_payload.get("robot_name") or "").strip()
    if want:
        mine = {str(x) for x in (getattr(robot, "name", ""),
                                 getattr(robot, "robot_id", "")) if x}
        if want not in mine:
            return reject(f"计划指定的机器人是 {want}，当前是 {sorted(mine)}")

    # 3) 忙就别组装了（组装要读盘建树，白干）
    if getattr(robot, "巡检进行中", False):
        return reject("busy", current_inspection_id=getattr(
            robot.state.insp, "current_inspection_id", None)
            if getattr(robot, "state", None) is not None else None)

    # 4) 汇总成巡检任务载荷
    try:
        from .inspection_build import build_from_plan
        built = build_from_plan(job_payload, root_dir=root_dir, fresh_ids=fresh_ids)
    except Exception as exc:
        return reject(f"组装巡检任务失败: {exc}")

    if built["waypoint_count"] <= 0:
        return reject("这条计划没有挑到任何航点")

    # 5) 交给机器人
    try:
        result = robot.接收巡检任务(built["payload"])
    except Exception as exc:
        return reject(f"机器人接收巡检任务失败: {exc}")

    if not isinstance(result, dict):
        result = {"accepted": True, "result": result}
    result.setdefault("accepted", True)
    result.update({
        "plan_key": plan_key,
        "plan_name": plan_name,
        "inspection_id": result.get("inspection_id") or built["inspection_id"],
        "floors": built["floors"],
        "waypoint_count": built["waypoint_count"],
        "action_count": built["action_count"],
    })
    logger.info("[prefab] 巡检计划「%s」已下发：航点%d 动作%d 楼层%s -> %s",
                plan_name, built["waypoint_count"], built["action_count"],
                built["floors"], result.get("inspection_id"))
    return result


def install_default_trigger() -> Any:
    """把 `dispatch_inspection` 装成默认下发回调（启动时调一次，幂等）。

    已经注册过（别人先装了自己的）就**不覆盖**——注册是显式的，不该被启动流程
    悄悄顶掉。返回当前生效的回调。
    """
    if get_inspection_trigger() is None:
        set_inspection_trigger(dispatch_inspection)
    return get_inspection_trigger()
