"""检测流程的执行逻辑（**纯函数**：吃一棵流程树 + 一个命中事件，吐出要做什么）。

编排（`prefab/nodes/detect.py`）与执行在这里分开，理由与 `plan_scheduler.py`
完全一样：**算的东西必须能单测**。流程树是"配了什么"，本模块回答"这一次命中
到底该不该报、要报给谁"。

## 语义

按 **children 顺序**走一遍（顺序就是执行顺序，模型层不强制但执行侧认它）：

- `enabled=false` 的节点**整棵子树跳过**（与前端变灰的范围一致）；
- **前处理 / 判定类**节点（取帧 / 节流 / 抽帧 / 区域过滤 / 生效时段 / 结果过滤 /
  连续确认）是**闸门**：不满足就把这次命中拦下，后面的节点**一个都不跑**
  （`passed=False` + `stopped_by`）。拦下不是错误——它就是"这次不报"；
- 图像预处理只记录要做什么，**不拦**；
- `DetectorNode` 也是闸门：算法对不上、置信度低于阈值、类别不在白名单里，拦下；
- **后处理**节点（留存 / 告警 / 转发 / 短信 / 邮件）**发动作**：往 `actions` 里
  追加一条，不拦、也不继续往下影响别的节点；
- 短信 / 邮件带 `min_level` 闸门：事件级别（取 `AlarmNode.level`，没配告警时
  按 `预警`）达不到就不发。

⚠️ **本模块不发短信、不发邮件、不推 HTTP**——它只算出"要做什么"（`actions`
是一堆 dict）。真正外发由调用方拿着 actions 去做：编排数据不该有副作用，
否则点一下"试跑"就真把短信发出去了。

## 状态

节流 / 连续确认需要**跨事件记忆**，状态放在调用方传入的 `DetectState` 里
（按 `key` 分桶，通常是"流程 + 测点"）。本模块不落盘、不建线程：
要不要持久化由调用方决定（`plan_scheduler` 那套账本是落盘的，这里先不落，
因为流程的执行侧还没接真机）。

## 事件

`DetectEvent` 是一次"算法说命中了"的证据：算法 id、类别、置信度、取帧来源、
帧号、归一化位置。位置只用于「区域过滤」——没给位置就**不过滤**（宁可放行，
也不能因为缺字段把真告警拦掉）。
"""
from __future__ import annotations

import time
from dataclasses import dataclass, field
from datetime import datetime
from typing import Any, Iterable

#: 告警级别从低到高。**顺序即语义**：`level_at_least` 靠下标比较，
#: 加一档要插到对应位置，别追加在末尾。
#: 与 `nodes/detect.py::LEVEL_OPTIONS` **必须一致**（靠下标比大小）
LEVELS: tuple[str, ...] = ("预警", "一般告警", "严重告警", "危急告警")

#: 星期几：`datetime.weekday()` 是 0=周一，节点里存的是 1=周一（跟人写的一致）
WEEKDAY_OFFSET = 1


# ---------------------------------------------------------------- 事件与状态

@dataclass
class DetectEvent:
    """一次检测结果（算法说"命中了"）。"""

    algorithm: str = ""            # 命中的算法 id（对应 DetectorNode.algorithm）
    label: str = ""                # 类别，如 "person"
    confidence: float = 0.0        # 0~1
    source: str = "抓拍图"          # 取帧来源（对应 FrameSourceNode.source）
    frame_index: int = 0           # 帧序号（抽帧用；0 基，每次调用自己维护）
    point_id: str = ""             # 测点 id（可选，只进动作的文本）
    point_name: str = ""           # 测点名（可选）
    value: float | None = None     # 监测数值（数值告警 / 数值范围告警的判据；None = 没有数值）
    x: float | None = None         # 命中位置（归一化 0~1，区域过滤用）
    y: float | None = None
    ts: float | None = None        # 事件时间戳；None = 用调用时刻


@dataclass
class DetectState:
    """跨事件的运行态（节流窗口 / 连续确认计数）。用完可以丢，不落盘。"""

    #: key -> [窗口内的放行时间戳]
    throttle: dict[str, list[float]] = field(default_factory=dict)
    #: key -> {"count": 连续命中次数, "first": 首次命中时刻}
    confirm: dict[str, dict[str, Any]] = field(default_factory=dict)


@dataclass
class FlowRun:
    """一次流程跑完的结果。"""

    passed: bool                   # 有没有走完（False = 被某个闸门拦下）
    stopped_by: str | None         # 拦下的那个节点的名字/类型（passed=True 时是 None）
    actions: list[dict[str, Any]]  # 要做的动作（调用方决定真不真发）
    notes: list[str]               # 给人看的说明（为什么拦下 / 做了什么）


# ---------------------------------------------------------------- 小工具

def level_at_least(level: str, minimum: str) -> bool:
    """`level` 是否达到 `minimum`（都按 `LEVELS` 的下标比）。

    不在 `LEVELS` 里的值（手改 json 写错）**按最低档算**：宁可多报也不静默丢告警，
    但会由调用方记一条 note——静默丢弃是这类系统最难查的故障。
    """
    return _level_rank(level) >= _level_rank(minimum)


def _level_rank(level: str) -> int:
    try:
        return LEVELS.index(str(level))
    except ValueError:
        return 0


def parse_hm(v: Any) -> int | None:
    """"HH:MM" -> 当天分钟数；解析不出来返回 `None`（调用方按"不限制"处理）。"""
    s = str(v or "").strip()
    if not s or ":" not in s:
        return None
    h, _, m = s.partition(":")
    try:
        hh, mm = int(h), int(m)
    except ValueError:
        return None
    if not (0 <= hh <= 23 and 0 <= mm <= 59):
        return None
    return hh * 60 + mm


def point_in_polygon(x: float, y: float, pts: Iterable[dict[str, Any]]) -> bool:
    """射线法判点在多边形内（顶点归一化 0~1，按给的顺序连成闭合区域）。

    少于 3 个点围不出区域 -> `False`（调用方据此**不放行**，见 `_gate_roi`：
    区域没画出来时按"不过滤"处理，避免手滑画了两点就把告警全拦了）。
    """
    poly: list[tuple[float, float]] = []
    for p in pts or []:
        if not isinstance(p, dict):
            continue
        try:
            poly.append((float(p.get("x")), float(p.get("y"))))
        except (TypeError, ValueError):
            continue
    if len(poly) < 3:
        return False
    inside = False
    n = len(poly)
    for i in range(n):
        x1, y1 = poly[i]
        x2, y2 = poly[(i + 1) % n]
        # 点落在边上：算在区域内（边界情况宁可放行）
        if (x1 == x2 == x and min(y1, y2) <= y <= max(y1, y2)) or \
           (y1 == y2 == y and min(x1, x2) <= x <= max(x1, x2)):
            return True
        if (y1 > y) != (y2 > y):
            xt = x1 + (y - y1) * (x2 - x1) / (y2 - y1)
            if x < xt:
                inside = not inside
    return inside


def render(template: str, event: DetectEvent, extra: dict[str, Any] | None = None) -> str:
    """把 `{var}` 占位换成事件里的值。

    认得的变量：`algorithm` / `label` / `confidence` / `point_id` /
    `point_name` / `source` / `frame`。**不认得的占位原样留着**（不替换成空串）：
    告警正文里出现一个空的"{置信度}"比"{confidence}"更难看出是没配还是没取到。
    """
    values: dict[str, Any] = {
        "algorithm": event.algorithm,
        "label": event.label,
        "confidence": f"{event.confidence:.2f}",
        "point_id": event.point_id,
        "point_name": event.point_name or event.point_id,
        "source": event.source,
        "frame": event.frame_index,
    }
    values.update(extra or {})
    out = str(template or "")
    for k, v in values.items():
        out = out.replace("{" + k + "}", str(v))
    return out


# ---------------------------------------------------------------- 闸门

def _node_props(node: Any) -> dict[str, Any]:
    """取节点的字段值。

    ⚠️ 实例上**没有** `properties` 这个子字典——spec 里的 `properties` 在 build
    时被拆开当成模型字段了（`cls(**props)`），所以字段就在对象自己身上。
    早先按 `node.properties` 取，拿到的一律是 `{}`，于是所有闸门都读不到阈值、
    全部退化成"不限制"（测试里表现为"该拦的没拦"）。
    """
    dump = getattr(node, "model_dump", None)
    if callable(dump):
        try:
            return dict(dump(exclude={"children"}))
        except Exception:  # noqa: BLE001 - 兜住非 pydantic 的假节点（测试里可能手搓）
            pass
    return dict(getattr(node, "properties", None) or {})


def _node_name(node: Any) -> str:
    p = _node_props(node)
    return str(p.get("name") or getattr(node, "type", "") or "未命名节点")


def _enabled(node: Any) -> bool:
    return _node_props(node).get("enabled", True) is not False


def _gate_source(p: dict[str, Any], ev: DetectEvent) -> tuple[bool, str]:
    want = str(p.get("source") or "").strip()
    if not want:
        return True, ""
    return (ev.source == want), f"图像来源 {ev.source} != 要求 {want}"


def _gate_frame_skip(p: dict[str, Any], ev: DetectEvent) -> tuple[bool, str]:
    try:
        n = int(p.get("every_n_frames") or 1)
    except (TypeError, ValueError):
        n = 1
    if n <= 1:
        return True, ""
    # 第 0 帧一定处理：否则"刚开始"的那一帧永远被跳掉
    return (ev.frame_index == 0 or ev.frame_index % n == 0), f"第 {ev.frame_index} 帧被抽掉（每 {n} 帧处理 1 帧）"


def _gate_roi(p: dict[str, Any], ev: DetectEvent) -> tuple[bool, str]:
    roi = p.get("roi") or []
    if not isinstance(roi, list) or len(roi) < 3:
        return True, ""      # 区域没画出来 = 不过滤（见 point_in_polygon 的说明）
    if ev.x is None or ev.y is None:
        return True, ""      # 事件没带位置 = 不过滤
    inside = point_in_polygon(float(ev.x), float(ev.y), roi)
    mode = str(p.get("mode") or "只处理框内")
    if mode == "排除框内":
        return (not inside), "命中位置落在排除区域内"
    return inside, "命中位置不在 ROI 内"


def _gate_time_window(p: dict[str, Any], now: datetime) -> tuple[bool, str]:
    start = parse_hm(p.get("start_time"))
    end = parse_hm(p.get("end_time"))
    if start is None or end is None:
        return True, ""      # 时间没填对 = 不限制（填错不该等于"永远不报"）
    if end <= start:
        return True, ""      # 跨零点不支持（与编排侧同一取舍）：按不限制处理
    cur = now.hour * 60 + now.minute
    if not (start <= cur <= end):
        return False, f"当前 {now:%H:%M} 不在 {p.get('start_time')}–{p.get('end_time')}"
    if p.get("every_day") is True:
        return True, ""
    days = p.get("days")
    if isinstance(days, list) and days:
        # 节点里 1=周一，datetime.weekday() 0=周一
        wd = now.weekday() + WEEKDAY_OFFSET
        if wd not in days:
            return False, f"星期{wd} 不在生效的 {days}"
    return True, ""


def numeric_alarm_hit(p: dict[str, Any], value: float) -> tuple[bool, str]:
    """数值告警判据：`value op threshold`。

    事件**没带数值**由调用方处理（记一条 note 跳过）——没有数就判不了，
    不能默认成 0（把"没采到"当成"0℃"会报一堆假低温告警）。
    """
    try:
        th = float(p.get("threshold") or 0)
    except (TypeError, ValueError):
        th = 0.0
    op = str(p.get("op") or ">")
    if op == ">":
        ok = value > th
    elif op == ">=":
        ok = value >= th
    elif op == "<":
        ok = value < th
    elif op == "<=":
        ok = value <= th
    elif op == "==":
        ok = value == th
    elif op == "!=":
        ok = value != th
    else:
        return True, f"未知比较符 {op}（按成立处理）"
    return ok, ("" if ok else f"{value:g} {op} {th:g} 不成立")


def range_alarm_hit(p: dict[str, Any], value: float) -> tuple[bool, str]:
    """数值范围告警判据：按 `mode` 判断落在区间内还是外。

    `max < min` 是配错的空区间 -> **不报**（记一条 note）：宁可漏报也不让一个
    手滑填反的区间把所有数值都判成越界。
    """
    try:
        lo = float(p.get("min_value") or 0)
    except (TypeError, ValueError):
        lo = 0.0
    try:
        hi = float(p.get("max_value") or 0)
    except (TypeError, ValueError):
        hi = 0.0
    if hi < lo:
        return False, f"区间配反了（下限 {lo:g} > 上限 {hi:g}）"
    incl = p.get("inclusive", True) is not False
    inside = (lo <= value <= hi) if incl else (lo < value < hi)
    mode = str(p.get("mode") or "区间外告警")
    if mode == "区间内告警":
        return inside, ("" if inside else f"{value:g} 不在 [{lo:g}, {hi:g}] 内")
    return (not inside), ("" if not inside else f"{value:g} 在 [{lo:g}, {hi:g}] 内")


def _gate_detector(p: dict[str, Any], ev: DetectEvent, ntype: str = "") -> tuple[bool, str]:
    """算法检测节点这一关：算法身份 + 置信度 + 类别白名单。

    ⚠️ 置信度比较**只对还带阈值的算法节点做**（`ntype` 不在
    `_NO_THRESHOLD_GATE_TYPES` 里）。`MeterAlgorithmNode` 对接的推理服务不认
    置信度阈值、字段已从检视器下线，所以它这一关不比置信度——但老 prefab 里
    残留的旧阈值**同样不能再生效**，否则界面上看不见的值会继续拦结果。
    """
    algo = str(p.get("algorithm") or "").strip()
    if algo and ev.algorithm and algo != ev.algorithm:
        return False, f"算法 {ev.algorithm} != 本节点 {algo}"
    if ntype not in _NO_THRESHOLD_GATE_TYPES:
        try:
            th = float(p.get("threshold") or 0)
        except (TypeError, ValueError):
            th = 0.0
        if th > 0 and ev.confidence < th:
            return False, f"置信度 {ev.confidence:.2f} < 阈值 {th:.2f}"
    labels = p.get("labels")
    if isinstance(labels, list) and labels and ev.label and ev.label not in labels:
        return False, f"类别 {ev.label} 不在白名单 {labels}"
    return True, ""


def _gate_result_filter(p: dict[str, Any], ev: DetectEvent) -> tuple[bool, str]:
    try:
        mc = float(p.get("min_confidence") or 0)
    except (TypeError, ValueError):
        mc = 0.0
    if mc > 0 and ev.confidence < mc:
        return False, f"置信度 {ev.confidence:.2f} < 过滤线 {mc:.2f}"
    labels = p.get("labels")
    if isinstance(labels, list) and labels and ev.label and ev.label not in labels:
        return False, f"类别 {ev.label} 不在保留列表 {labels}"
    return True, ""


# ---------------------------------------------------------------- 节流 / 连续确认

def throttle_allows(state: DetectState, key: str, now: float,
                    window_seconds: float, max_events: int,
                    strategy: str = "丢弃") -> tuple[bool, str]:
    """节流：窗口内最多放行 `max_events` 条。

    返回 `(放行?, 说明)`，并**就地更新** `state.throttle[key]`（丢掉窗口外的记录）。

    `window_seconds <= 0` = 不节流；`max_events == 0` = 窗口内一条都不放行
    （等于临时关掉这条流程的后续——与节点字段的说明一致）。
    """
    if window_seconds <= 0:
        return True, ""
    bucket = state.throttle.setdefault(key, [])
    bucket[:] = [t for t in bucket if now - t < window_seconds]
    if len(bucket) >= max_events:
        if strategy == "延后到窗末":
            # 延后 = 记一条说明，但**这次仍然拦下**（真延后要有个队列，执行侧
            # 还没接，先如实拦下并记 note，别假装"稍后会发"）
            return False, f"窗口内已放行 {len(bucket)} 条（延后策略待执行侧实现）"
        return False, f"窗口内已放行 {len(bucket)} 条（上限 {max_events}）"
    bucket.append(now)
    return True, ""


def confirm_hit(state: DetectState, key: str, now: float, require_count: int,
                within_seconds: float, reset_on_miss: bool = True) -> tuple[bool, str]:
    """连续确认：连续 `require_count` 次命中才放行。

    ⚠️ 只认"命中"这一种输入：**没有"未命中"事件**可喂进来（算法不命中就不产生
    事件），所以计数**不会自己清零**——`reset_on_miss=True` 的实际含义是
    "计满之后从头再来"（`within_seconds` 之外也从头再来）。想靠"中间断一次就
    清零"必须能收到未命中信号，那是执行侧接真机之后的事。
    """
    try:
        need = int(require_count or 1)
    except (TypeError, ValueError):
        need = 1
    if need <= 1:
        return True, ""
    slot = state.confirm.setdefault(key, {"count": 0, "first": now})
    try:
        within = float(within_seconds or 0)
    except (TypeError, ValueError):
        within = 0.0
    if within > 0 and now - float(slot.get("first") or now) > within:
        slot["count"] = 0
        slot["first"] = now
    slot["count"] = int(slot.get("count") or 0) + 1
    if slot["count"] >= need:
        slot["count"] = 0 if reset_on_miss else slot["count"]
        slot["first"] = now if reset_on_miss else slot["first"]
        return True, ""
    return False, f"连续命中 {slot['count']}/{need}"


# ---------------------------------------------------------------- 主流程

_ACTION_KIND = {
    "EvidenceNode": "evidence",
    "AlarmNode": "alarm",                    # 事件告警：命中即报
    "NumericAlarmNode": "numeric_alarm",     # 数值告警：数值越过阈值
    "RangeAlarmNode": "range_alarm",         # 数值范围告警：跑出（或落进）区间
    "ForwardNode": "forward",
    "SmsNotifyNode": "sms",
    "EmailNotifyNode": "email",
}

_GATE_KIND = {
    "FrameSourceNode": "source",
    "FrameSkipNode": "skip",
    "RoiFilterNode": "roi",
    "TimeWindowNode": "time",
    "ResultFilterNode": "filter",
}


def _collect_detector_types() -> frozenset[str]:
    """所有已注册的算法检测节点类型名（`DetectorNode` 子类）。

    算法身份从"一个通用节点 + 算法下拉"改成了"每种算法一个子类"
    （见 nodes/algorithms.py），执行侧按继承关系收集类型名，
    以后新增算法不用改本模块。
    """
    try:
        from . import registry
        from .nodes.detect import DetectorNode
        return frozenset(
            name for name, cls in registry.registered_types().items()
            if isinstance(cls, type) and issubclass(cls, DetectorNode)
        )
    except Exception:  # noqa: BLE001 - 收集失败不该让执行模块整体不可 import
        return frozenset()


#: 算法检测节点类型名集合（模块导入时 nodes 已由 app.prefab 包完成注册）
_DETECTOR_TYPES = _collect_detector_types()


def _collect_no_threshold_gate_types() -> frozenset[str]:
    """**不比置信度**的算法节点类型名（`DetectorNode.__threshold_gate__ = False`）。

    `MeterAlgorithmNode` 就是这一类：它对接的现有推理服务不认置信度阈值，
    阈值字段已从检视器下线（`__hidden_fields__`）。既然界面上没有这个属性，
    老 prefab 里残留的旧值就不能再参与闸门 —— 否则用户看不到、也改不掉，
    却还在拦结果，是最难查的那种问题。
    """
    try:
        from . import registry
        from .nodes.detect import DetectorNode
        return frozenset(
            name for name, cls in registry.registered_types().items()
            if isinstance(cls, type) and issubclass(cls, DetectorNode)
            and getattr(cls, "__threshold_gate__", True) is False
        )
    except Exception:  # noqa: BLE001 - 收集失败不该让执行模块整体不可 import
        return frozenset()


_NO_THRESHOLD_GATE_TYPES = _collect_no_threshold_gate_types()


def run_flow(root: Any, event: DetectEvent, *, now: float | None = None,
             now_dt: datetime | None = None, state: DetectState | None = None,
             key: str = "default") -> FlowRun:
    """跑一遍流程树，返回"这次命中要不要报、要做什么"。

    :param root: 流程树根节点（**已 build 的节点实例**，`registry.build` 的产物）
    :param event: 这次的检测结果
    :param now: 时间戳（`time.time()` 语义）；None = 取当前
    :param now_dt: 用于「生效时段」的本地时间；None = `datetime.now()`
    :param state: 跨事件状态（节流/确认）；None = 本次临时建一个（等于无记忆）
    :param key: 状态分桶键，通常传"流程 + 测点"
    """
    ts = float(now if now is not None else time.time())
    dt = now_dt or datetime.now()
    st = state if state is not None else DetectState()
    out = FlowRun(passed=True, stopped_by=None, actions=[], notes=[])

    # 事件级别：初始最低档；每产生一个告警动作（事件/数值/范围）就把当前级别
    # 抬到这次动作配的级别（取较高者）。短信/邮件的 min_level 闸门按这个
    # "已报出的最高级别"判。之所以不靠开头预扫某个告警节点：纯数值流程里根本
    # 没有事件告警节点，预扫只会让数值节点自己配的级别被当成"预警"。
    level = "预警"

    def stop(node: Any, why: str) -> None:
        out.passed = False
        out.stopped_by = f"{_node_name(node)}（{why}）" if why else _node_name(node)

    def walk(node: Any) -> None:
        nonlocal level
        if not _enabled(node):
            return
        ntype = getattr(node, "type", "")
        p = _node_props(node)
        name = _node_name(node)

        gate = _GATE_KIND.get(ntype)
        if ntype in _DETECTOR_TYPES:
            gate = "detector"
        if gate == "source":
            ok, why = _gate_source(p, event)
            if not ok:
                stop(node, why); return
        elif gate == "skip":
            ok, why = _gate_frame_skip(p, event)
            if not ok:
                stop(node, why); return
        elif gate == "roi":
            ok, why = _gate_roi(p, event)
            if not ok:
                stop(node, why); return
        elif gate == "time":
            ok, why = _gate_time_window(p, dt)
            if not ok:
                stop(node, why); return
        elif gate == "detector":
            ok, why = _gate_detector(p, event, ntype)
            if not ok:
                stop(node, why); return
        elif gate == "filter":
            ok, why = _gate_result_filter(p, event)
            if not ok:
                stop(node, why); return
        elif ntype == "ThrottleNode":
            try:
                window = float(p.get("window_seconds") or 0)
            except (TypeError, ValueError):
                window = 0.0
            try:
                mx = int(p.get("max_events") if p.get("max_events") is not None else 1)
            except (TypeError, ValueError):
                mx = 1
            ok, why = throttle_allows(st, key, ts, window, mx,
                                      str(p.get("strategy") or "丢弃"))
            if not ok:
                stop(node, why); return
        elif ntype == "ConfirmNode":
            try:
                need = int(p.get("require_count") or 1)
            except (TypeError, ValueError):
                need = 1
            try:
                within = float(p.get("within_seconds") or 0)
            except (TypeError, ValueError):
                within = 0.0
            ok, why = confirm_hit(st, key, ts, need, within,
                                  p.get("reset_on_miss", True) is not False)
            if not ok:
                stop(node, why); return
        elif ntype == "ImagePreprocessNode":
            out.notes.append(f"{name}：预处理（执行侧未接，仅记录）")
        elif ntype in _ACTION_KIND:
            kind = _ACTION_KIND[ntype]
            min_level = str(p.get("min_level") or "")
            if min_level and not level_at_least(level, min_level):
                out.notes.append(f"{name}：级别 {level} 未达 {min_level}，跳过")
                return
            # 数值类告警还要过自己的判据：不满足就**不产生动作**（它不是闸门，
            # 后面的节点照跑——同一条流程里可以既有温度告警又有事件告警）
            if kind in ("numeric_alarm", "range_alarm"):
                if event.value is None:
                    out.notes.append(f"{name}：事件没带数值，跳过")
                    return
                hit = (numeric_alarm_hit(p, float(event.value)) if kind == "numeric_alarm"
                       else range_alarm_hit(p, float(event.value)))
                if not hit[0]:
                    out.notes.append(f"{name}：{hit[1]}，不报")
                    return
            act = _make_action(kind, ntype, p, event, level)
            # 告警动作产生后，把"当前事件级别"抬到这次动作的级别（取较高者），
            # 供后面的短信/邮件 min_level 闸门用。判据不满足 / 事件没带数值的
            # 告警节点这次没产生动作，不抬级——它没报就不该影响这次分流。
            if kind in ("alarm", "numeric_alarm", "range_alarm"):
                act_level = str(act.get("level") or "预警")
                if level_at_least(act_level, level):
                    level = act_level
            out.actions.append(act)
            out.notes.append(f"{name}：产生 {kind} 动作")
        # DetectPipelineNode / DetectGroupNode / 未知类型：只是容器，继续往下走

        for c in _children(node):
            walk(c)
            if not out.passed:
                return

    walk(root)
    return out


def _walk(node: Any):
    yield node
    for c in _children(node):
        yield from _walk(c)


def _children(node: Any) -> list[Any]:
    kids = getattr(node, "child_nodes", None)
    if kids is None:
        return list(getattr(node, "children", None) or [])
    return list(kids)


def _make_action(kind: str, ntype: str, p: dict[str, Any],
                 event: DetectEvent, level: str) -> dict[str, Any]:
    """把一个后处理节点转成一条动作 dict（**不执行**：外发由调用方做）。"""
    base: dict[str, Any] = {
        "kind": kind,
        "node": ntype,
        "name": str(p.get("name") or ntype),
        "level": level,
        "point_id": event.point_id,
        "point_name": event.point_name,
    }
    if kind == "evidence":
        base.update({
            "dir": str(p.get("dir") or ""),
            "keep_days": int(p.get("keep_days") or 0),
            "with_box": bool(p.get("with_box", True)),
        })
    elif kind == "alarm":
        base.update({
            "level": str(p.get("level") or level),
            "template": str(p.get("template") or ""),
            "title": render(p.get("title"), event),
            "content": render(p.get("content"), event),
            "dedup_seconds": float(p.get("dedup_seconds") or 0),
        })
    elif kind in ("numeric_alarm", "range_alarm"):
        value = event.value
        extra = {"value": "" if value is None else f"{value:g}",
                 "metric": str(p.get("metric") or ""),
                 "unit": str(p.get("unit") or "")}
        if kind == "numeric_alarm":
            extra["threshold"] = p.get("threshold")
            extra["op"] = str(p.get("op") or ">")
        else:
            extra["min"] = p.get("min_value")
            extra["max"] = p.get("max_value")
        base.update({
            "level": str(p.get("level") or level),
            "metric": str(p.get("metric") or ""),
            "unit": str(p.get("unit") or ""),
            "value": value,
            "duration_seconds": float(p.get("duration_seconds") or 0),
            "template": str(p.get("template") or ""),
            "title": render(p.get("title"), event, extra),
            "content": render(p.get("content"), event, extra),
            "dedup_seconds": float(p.get("dedup_seconds") or 0),
        })
        if kind == "numeric_alarm":
            base.update({"op": str(p.get("op") or ">"), "threshold": p.get("threshold"),
                         "hysteresis": float(p.get("hysteresis") or 0)})
        else:
            base.update({"min_value": p.get("min_value"), "max_value": p.get("max_value"),
                         "inclusive": bool(p.get("inclusive", True)),
                         "mode": str(p.get("mode") or "区间外告警")})
    elif kind == "forward":
        base.update({
            "url": str(p.get("url") or ""),
            "method": str(p.get("method") or "POST"),
            "headers": p.get("headers") or {},
            "body": render(p.get("body"), event, {"level": level}),
            "timeout": float(p.get("timeout") or 5),
            "retry": int(p.get("retry") or 0),
        })
    elif kind == "sms":
        base.update({
            "receivers": list(p.get("receivers") or []),
            "template_id": str(p.get("template_id") or ""),
            "content": render(p.get("content"), event, {"level": level}),
        })
    elif kind == "email":
        base.update({
            "to": list(p.get("to") or []),
            "subject": render(p.get("subject"), event, {"level": level}),
            "body": render(p.get("body"), event, {"level": level}),
            "attach_snapshot": bool(p.get("attach_snapshot", True)),
        })
    return base
