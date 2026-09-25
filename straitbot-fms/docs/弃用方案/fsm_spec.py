"""FsmSpec —— 状态动作图（*.fsm.json）的声明式解释执行运行时。
@deprecated

与前端 FsmEditor 产出的 spec 一一对应，业务层只描述"有哪些状态机/状态/迁移动作/
激活动作"，运行时负责解释执行，不再像旧 sm.py 那样在 behXxx() 里手写 if/else。

四类对象（与前端 OBJ_META 完全对齐），左入(in)右出(out)：

    state_machine      pin: activator(in)  end(out)
                       字段: initial_state(入口状态名) end_signal(默认 sm_close)
    state              pin: in(in)  actions(out)
    signal_action      pin: in(in)  out(out)        字段: signal(监听的信号)
    sm_activate_action pin: in(in)  target_sm(out)  complete(out)

合法连线（编译期白名单校验）：

    state.actions            -> signal_action.in          状态监听某信号迁移动作
    signal_action.out        -> state.in                  迁移目标状态
    state.actions            -> sm_activate_action.in     状态挂一个子状态机激活动作
    sm_activate_action.target_sm -> state_machine.activator  激活哪台子状态机
    sm_activate_action.complete  -> state.in              子机结束后迁移到的状态(可空)
    state_machine.end       -> state_machine.activator    机器结束后平级链式激活(可空)

执行语义（见 docs/机器人状态机.md）：
  * signal_action（信号迁移）：当前激活状态收到 signal 时，**退出源状态、激活目标状态**，
    一个事件只做一次迁移，不级联。
  * sm_activate_action（状态机激活）：进入源状态时**自动激活目标状态机**（目标机从
    initial_state 开始），**不退出源状态**，从而父子并行；目标机收到自己的 end_signal
    （默认 sm_close）后出栈，若激活动作连了 complete，则退出源状态、迁移到 complete 目标。
    若该动作填了可选字段 signal，则进入状态后改为"收到该信号才激活"。
  * 事件按激活栈 LIFO（最内层子机优先）分发，被消费即止，避免一事件多机乱动。

针对旧 sm.py 的修正：纯同步确定性内核（时间由 tick(now) 注入，不碰 wall clock/asyncio）、
一事件一迁移、定时器随状态进入建立/退出取消（不泄漏）、子机结束即出栈（可重入）、
无模块级全局单例（可多机器人实例化）、业务 IO 只经 FsmHandler 回调外抛。
"""
from __future__ import annotations

import json
import logging
import time
from collections import deque
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Callable, Literal, Optional

from pydantic import BaseModel, ConfigDict, Field

logger = logging.getLogger("rail.fsm")

# ---------------------------------------------------------------------------
# 一、IO 模型：与前端 *.fsm.json 字段严格对齐（pydantic，负责读文件/校验基本形状）
# ---------------------------------------------------------------------------

FsmObjType = Literal[
    "state_machine", "state", "signal_action", "sm_activate_action"
]

# 每类对象的 pin：name -> side（与前端 FsmEditor.OBJ_META 保持一致）
PIN_SIDES: dict[str, dict[str, str]] = {
    "state_machine": {"activator": "in", "end": "out"},
    "state": {"in": "in", "actions": "out"},
    "signal_action": {"in": "in", "out": "out"},
    "sm_activate_action": {"in": "in", "target_sm": "out", "complete": "out"},
}

# 合法连线白名单：(源类型, 源 pin) -> (目标类型, 目标 pin)
LEGAL_EDGES: set[tuple[str, str, str, str]] = {
    ("state", "actions", "signal_action", "in"),
    ("signal_action", "out", "state", "in"),
    ("state", "actions", "sm_activate_action", "in"),
    ("sm_activate_action", "target_sm", "state_machine", "activator"),
    ("sm_activate_action", "complete", "state", "in"),
    ("state_machine", "end", "state_machine", "activator"),
}

DEFAULT_END_SIGNAL = "sm_close"


class FsmObject(BaseModel):
    model_config = ConfigDict(extra="ignore", populate_by_name=True)

    id: str
    type: FsmObjType
    name: str = ""
    x: float = 0.0
    y: float = 0.0
    description: str = ""

    # signal_action：监听的信号名
    signal: Optional[str] = None
    # state_machine：入口状态名 / 结束信号
    initial_state: Optional[str] = None
    end_signal: Optional[str] = None
    # state：显式归属的状态机（id 或 name）；缺省由迁移连线连通性自动推断
    sm: Optional[str] = None
    # state：进入/退出时调用的业务动作 key（交给 FsmHandler.call_action）
    on_enter: Optional[str] = None
    on_exit: Optional[str] = None
    # state：进入后 timeout_sec 未离开，则投递 timeout_event（定时器随状态生命周期）
    timeout_sec: Optional[float] = None
    timeout_event: Optional[str] = None
    # sm_activate_action：填了则进入状态后等该信号再激活子机；不填则进入即激活
    # （复用 signal 字段）


class FsmConnection(BaseModel):
    model_config = ConfigDict(extra="ignore", populate_by_name=True)

    id: str
    # `from` 是 Python 关键字，JSON 字段名仍为 from
    from_: str = Field(alias="from")
    fromPin: str
    to: str
    toPin: str


class FsmSpecDoc(BaseModel):
    model_config = ConfigDict(extra="ignore", populate_by_name=True)

    version: int = 1
    name: str = ""
    description: str = ""
    # 可选：显式指定根状态机（id 或 name）；缺省按"activator 无入边"推断
    root: Optional[str] = None
    objects: list[FsmObject] = []
    connections: list[FsmConnection] = []

    @classmethod
    def from_file(cls, path: str | Path, encoding: str = "utf-8") -> "FsmSpecDoc":
        with open(path, "r", encoding=encoding) as f:
            return cls.model_validate(json.load(f))

    def compile(self) -> "CompiledFsm":
        return compile_spec(self)


# ---------------------------------------------------------------------------
# 二、编译产物：不可变的机器/状态/迁移/激活表
# ---------------------------------------------------------------------------

@dataclass(frozen=True)
class CTransition:
    """信号迁移动作编译结果：sources 收到 event -> 退 sources 进 targets。"""
    id: str
    name: str
    event: str
    sources: tuple[str, ...]
    targets: tuple[str, ...]
    machine_id: str


@dataclass(frozen=True)
class CActivation:
    """状态机激活动作编译结果。"""
    id: str
    name: str
    sources: tuple[str, ...]
    target_machine_id: str
    complete_targets: tuple[str, ...]   # 子机结束后迁移目标；空 = 子机结束后源状态继续
    machine_id: str                     # 源状态所属（调用方）状态机
    signal: Optional[str]               # 缺省 None = 进入源状态即激活


@dataclass(frozen=True)
class CState:
    id: str
    name: str
    machine_id: str
    transitions: tuple[CTransition, ...] = ()
    activations: tuple[CActivation, ...] = ()
    on_enter: Optional[str] = None
    on_exit: Optional[str] = None
    timeout_sec: Optional[float] = None
    timeout_event: Optional[str] = None


@dataclass(frozen=True)
class CMachine:
    id: str
    name: str
    initial_state_id: str
    end_signal: str
    states: tuple[str, ...]


@dataclass
class CompiledFsm:
    name: str
    machines: dict[str, CMachine]
    states: dict[str, CState]
    root_machine_id: str
    # 机器 end pin -> 下游机器 activator（平级链式激活）
    end_links: dict[str, list[str]] = field(default_factory=dict)
    warnings: list[str] = field(default_factory=list)

    def runtime(self, handler: Optional["FsmHandler"] = None,
                clock: Callable[[], float] = time.monotonic) -> "FsmRuntime":
        return FsmRuntime(self, handler=handler, clock=clock)

    @classmethod
    def from_file(cls, path: str | Path, handler: Optional["FsmHandler"] = None,
                  clock: Callable[[], float] = time.monotonic) -> "FsmRuntime":
        return FsmSpecDoc.from_file(path).compile().runtime(handler, clock)


class FsmCompileError(Exception):
    """编译期错误聚合：一次性给出图中所有问题，便于在编辑器里定位。"""

    def __init__(self, name: str, errors: list[str], warnings: list[str] | None = None):
        self.name = name
        self.errors = errors
        self.warnings = warnings or []
        body = "\n  - ".join(errors)
        super().__init__(f"状态机图 [{name}] 编译失败，{len(errors)} 个错误:\n  - {body}")


# ---------------------------------------------------------------------------
# 三、编译器
# ---------------------------------------------------------------------------

def compile_spec(doc: FsmSpecDoc) -> CompiledFsm:
    name = doc.name or "<unnamed>"
    errors: list[str] = []
    warnings: list[str] = []

    def err(msg: str) -> None:
        errors.append(msg)

    # ---- 3.1 索引对象，校验 id 唯一 / 类型合法 ----
    objs: dict[str, FsmObject] = {}
    for o in doc.objects:
        if o.id in objs:
            err(f"对象 id 重复: {o.id}")
            continue
        objs[o.id] = o

    def label(oid: str) -> str:
        o = objs.get(oid)
        return f"{o.type}「{o.name or oid}」({oid})" if o else oid

    machines_o = [o for o in doc.objects if o.type == "state_machine"]
    states_o = [o for o in doc.objects if o.type == "state"]
    sig_acts_o = [o for o in doc.objects if o.type == "signal_action"]
    act_acts_o = [o for o in doc.objects if o.type == "sm_activate_action"]

    if not machines_o:
        err("图中没有任何状态机(state_machine)对象")
    if not states_o:
        err("图中没有任何状态(state)对象")

    # ---- 3.2 校验连线：端点 / pin / 方向 / 白名单 ----
    # 每类 pin 的入边、出边收集
    incoming: dict[str, list[FsmConnection]] = {}   # key=目标对象 id
    outgoing: dict[str, list[FsmConnection]] = {}   # key=源对象 id
    for c in doc.connections:
        if c.from_ not in objs:
            err(f"连线 {c.id} 的源对象不存在: {c.from_}")
            continue
        if c.to not in objs:
            err(f"连线 {c.id} 的目标对象不存在: {c.to}")
            continue
        src, dst = objs[c.from_], objs[c.to]
        src_pins = PIN_SIDES.get(src.type, {})
        dst_pins = PIN_SIDES.get(dst.type, {})
        if c.fromPin not in src_pins:
            err(f"连线 {c.id}：{label(src.id)} 不存在输出 pin「{c.fromPin}」")
            continue
        if c.toPin not in dst_pins:
            err(f"连线 {c.id}：{label(dst.id)} 不存在输入 pin「{c.toPin}」")
            continue
        if src_pins[c.fromPin] != "out":
            err(f"连线 {c.id}：{label(src.id)} 的 pin「{c.fromPin}」是输入 pin，不能作为连线起点")
            continue
        if dst_pins[c.toPin] != "in":
            err(f"连线 {c.id}：{label(dst.id)} 的 pin「{c.toPin}」是输出 pin，不能作为连线终点")
            continue
        if (src.type, c.fromPin, dst.type, c.toPin) not in LEGAL_EDGES:
            err(
                f"连线 {c.id}「{src.type}.{c.fromPin} -> {dst.type}.{c.toPin}」不是可执行的连线，"
                f"支持：状态.actions→迁移动作.in、迁移动作.out→状态.in、"
                f"状态.actions→激活动作.in、激活动作.target_sm→状态机.activator、"
                f"激活动作.complete→状态.in、状态机.end→状态机.activator"
            )
            continue
        outgoing.setdefault(c.from_, []).append(c)
        incoming.setdefault(c.to, []).append(c)

    # 硬错误（缺对象/缺 pin）会让后续构建无意义，直接抛出
    if errors:
        raise FsmCompileError(name, errors, warnings)

    # ---- 3.3 构建信号迁移动作 ----
    # transition_by_id / 每个 state 的源迁移
    raw_transitions: dict[str, CTransition] = {}
    for a in sig_acts_o:
        ins = [c for c in incoming.get(a.id, []) if c.toPin == "in"]
        outs = [c for c in outgoing.get(a.id, []) if c.fromPin == "out"]
        sources = tuple(c.from_ for c in ins
                        if objs[c.from_].type == "state" and c.fromPin == "actions")
        targets = tuple(c.to for c in outs
                        if objs[c.to].type == "state" and c.toPin == "in")
        event = (a.signal or "").strip()
        if not event:
            err(f"信号迁移动作「{a.name or a.id}」未填写 signal（监听信号）")
        if not sources:
            err(f"信号迁移动作「{a.name or a.id}」没有输入：需要从某状态的 actions pin 连到它的 in")
        if not targets:
            err(f"信号迁移动作「{a.name or a.id}」没有输出目标：需要从它的 out 连到某状态的 in")
        if sources and targets:
            raw_transitions[a.id] = CTransition(
                id=a.id, name=a.name or a.id, event=event,
                sources=sources, targets=targets, machine_id="",
            )

    # ---- 3.4 构建状态机激活动作 ----
    raw_activations: dict[str, CActivation] = {}
    for a in act_acts_o:
        ins = [c for c in incoming.get(a.id, []) if c.toPin == "in"]
        sources = tuple(c.from_ for c in ins
                        if objs[c.from_].type == "state" and c.fromPin == "actions")
        tgt_conns = [c for c in outgoing.get(a.id, []) if c.fromPin == "target_sm"]
        comp_conns = [c for c in outgoing.get(a.id, []) if c.fromPin == "complete"]
        target_machines = tuple(c.to for c in tgt_conns
                                if objs[c.to].type == "state_machine" and c.toPin == "activator")
        complete_targets = tuple(c.to for c in comp_conns
                                 if objs[c.to].type == "state" and c.toPin == "in")
        if not sources:
            err(f"状态机激活动作「{a.name or a.id}」没有输入：需要从某状态的 actions 连到它的 in")
        if len(target_machines) == 0:
            err(f"状态机激活动作「{a.name or a.id}」未连 target_sm：需要连到目标状态机的 activator")
        elif len(target_machines) > 1:
            err(f"状态机激活动作「{a.name or a.id}」的 target_sm 连了 {len(target_machines)} 台状态机，只能激活 1 台")
        if sources and len(target_machines) == 1:
            raw_activations[a.id] = CActivation(
                id=a.id, name=a.name or a.id, sources=sources,
                target_machine_id=target_machines[0],
                complete_targets=complete_targets,
                machine_id="", signal=(a.signal or None),
            )

    # ---- 3.5 状态归属：initial_state 种子 + 迁移连线连通性切分 ----
    # 3.5.1 解析每台机器的 initial_state（按状态名）
    states_by_name: dict[str, list[str]] = {}
    for s in states_o:
        states_by_name.setdefault(s.name or s.id, []).append(s.id)

    machine_initial: dict[str, str] = {}   # machine id -> initial state id
    for m in machines_o:
        ini = (m.initial_state or "").strip()
        if not ini:
            err(f"状态机「{m.name or m.id}」未填写 initial_state（入口状态名）")
            continue
        cand = states_by_name.get(ini, [])
        # 显式 sm 消歧
        cand = [sid for sid in cand
                if not (objs[sid].sm and _resolve_ref(objs[sid].sm, machines_o) != m.id)]
        if len(cand) == 1:
            machine_initial[m.id] = cand[0]
        elif len(cand) == 0:
            err(f"状态机「{m.name or m.id}」的 initial_state「{ini}」找不到同名状态")
        else:
            err(f"状态机「{m.name or m.id}」的 initial_state「{ini}」匹配到多个状态，请重名状态设置 sm 字段消歧")

    # 3.5.2 以 signal 迁移为边，建状态无向图
    adj: dict[str, set[str]] = {s.id: set() for s in states_o}
    for tr in raw_transitions.values():
        for s in tr.sources:
            for t in tr.targets:
                adj.setdefault(s, set()).add(t)
                adj.setdefault(t, set()).add(s)

    # 3.5.3 连通分量
    seen: set[str] = set()
    components: list[set[str]] = []
    for sid in adj:
        if sid in seen:
            continue
        stack, comp = [sid], set()
        seen.add(sid)
        while stack:
            cur = stack.pop()
            comp.add(cur)
            for nb in adj[cur]:
                if nb not in seen:
                    seen.add(nb)
                    stack.append(nb)
        components.append(comp)

    initial_owner = {sid: mid for mid, sid in machine_initial.items()}
    state_machine: dict[str, str] = {}   # state id -> machine id
    unresolved: set[str] = set()         # 已报过归属错误的状态，避免后续级联误报

    def assign_explicit(sid: str) -> Optional[str]:
        ref = (objs[sid].sm or "").strip()
        return _resolve_ref(ref, machines_o) if ref else None

    for comp in components:
        seed_mids = {initial_owner[s] for s in comp if s in initial_owner}
        explicit_mids = {assign_explicit(s) for s in comp}
        explicit_mids.discard(None)
        if len(seed_mids) > 1:
            names = "、".join(label(mid) for mid in seed_mids)
            err(f"信号迁移动作把不同状态机（{names}）的状态连成了同一网络；信号迁移不能跨状态机，"
                f"跨状态机请改用状态机激活动作（sm_activate_action，target_sm 连到目标状态机）。"
                f"涉及状态：{'、'.join(label(s) for s in comp)}")
            unresolved.update(comp)
            continue
        if len(seed_mids) == 1:
            mid = next(iter(seed_mids))
            for s in comp:
                ex = assign_explicit(s)
                if ex and ex != mid:
                    err(f"状态 {label(s)} 显式 sm 指向 {label(ex)}，但它通过迁移线属于 {label(mid)}，二者冲突")
                state_machine[s] = mid
        else:
            # 分量里没有任何机器入口：只能靠显式 sm，且必须一致
            if len(explicit_mids) == 1:
                mid = next(iter(explicit_mids))
                for s in comp:
                    state_machine[s] = mid
            else:
                err("以下状态无法确定属于哪台状态机（既不在任何状态机 initial_state 的迁移网络内，"
                    f"也未设置一致的 sm 字段）：{'、'.join(label(s) for s in comp)}")
                unresolved.update(comp)

    # 3.5.4 校验每台机器都拿到了 initial，且没有状态漏网
    for mid, sid in machine_initial.items():
        if state_machine.get(sid) not in (None, mid):
            err(f"状态机 {label(mid)} 的初始状态 {label(sid)} 归属异常")
    for s in states_o:
        if s.id in state_machine or s.id in unresolved:
            continue
        # 孤立状态（没有任何迁移线）且无显式 sm
        ex = assign_explicit(s.id)
        if ex:
            state_machine[s.id] = ex
        else:
            err(f"状态 {label(s.id)} 是孤立状态：请用信号迁移线把它连入某状态机，或在该状态上设置 sm 字段")

    # ---- 3.6 归并迁移/激活到状态，并做跨机/重复校验 ----
    # machine -> states
    machine_states: dict[str, list[str]] = {m.id: [] for m in machines_o}
    for sid, mid in state_machine.items():
        machine_states.setdefault(mid, []).append(sid)

    transitions_by_state: dict[str, list[CTransition]] = {}
    for tr in raw_transitions.values():
        mid = state_machine.get(tr.sources[0])
        target_mids = {state_machine.get(t) for t in tr.targets}
        missing = [t for t in tr.targets if t not in state_machine and t not in unresolved]
        if missing:
            err(f"信号迁移动作「{tr.name}」的目标状态缺少状态机归属：{'、'.join(label(t) for t in missing)}")
            continue
        if any(tm is None for tm in target_mids):
            continue  # 归属冲突已在分量分析阶段报错，此处不级联
        if target_mids != {mid}:
            err(f"信号迁移动作「{tr.name}」跨状态机迁移（源属 {label(mid)}，目标属 "
                f"{'、'.join(label(t) for t in target_mids if t)}）；跨机请改用状态机激活动作")
            continue
        if len(tr.targets) != 1:
            err(f"信号迁移动作「{tr.name}」连了 {len(tr.targets)} 个目标状态，同一状态机内一次迁移只能有 1 个目标")
            continue
        fixed = CTransition(
            id=tr.id, name=tr.name, event=tr.event, sources=tr.sources,
            targets=tr.targets, machine_id=mid,
        )
        raw_transitions[tr.id] = fixed
        for s in tr.sources:
            transitions_by_state.setdefault(s, []).append(fixed)

    activations_by_state: dict[str, list[CActivation]] = {}
    for ac in raw_activations.values():
        mid = state_machine.get(ac.sources[0])
        missing = [t for t in ac.complete_targets if t not in state_machine and t not in unresolved]
        if missing:
            err(f"状态机激活动作「{ac.name}」的 complete 目标状态缺少状态机归属："
                f"{'、'.join(label(t) for t in missing)}")
            continue
        comp_mids = {state_machine.get(t) for t in ac.complete_targets}
        if any(cm is None for cm in comp_mids):
            continue  # 归属冲突已报，不级联
        if comp_mids and comp_mids != {mid}:
            err(f"状态机激活动作「{ac.name}」的 complete 目标不在源状态机 {label(mid)} 内")
            continue
        if ac.target_machine_id == mid:
            err(f"状态机激活动作「{ac.name}」的目标状态机就是它自己（{label(mid)}），自激活无意义")
            continue
        fixed = CActivation(
            id=ac.id, name=ac.name, sources=ac.sources,
            target_machine_id=ac.target_machine_id,
            complete_targets=ac.complete_targets, machine_id=mid, signal=ac.signal,
        )
        raw_activations[ac.id] = fixed
        for s in ac.sources:
            activations_by_state.setdefault(s, []).append(fixed)

    # 同一状态同一信号多条迁移 -> 歧义
    for sid, trs in transitions_by_state.items():
        seen_events: dict[str, str] = {}
        for tr in trs:
            if tr.event in seen_events:
                err(f"状态 {label(sid)} 上信号「{tr.event}」对应了多个迁移动作"
                    f"（{seen_events[tr.event]} / {tr.name}），触发时无法抉择")
            seen_events[tr.event] = tr.name

    # ---- 3.7 状态超时字段校验，组装 CState ----
    cstates: dict[str, CState] = {}
    for s in states_o:
        mid = state_machine.get(s.id)
        if mid is None:
            continue  # 归属错误已记录
        if (s.timeout_sec is None) != (s.timeout_event is None):
            err(f"状态 {label(s.id)} 的 timeout_sec 与 timeout_event 必须同时填写")
        cstates[s.id] = CState(
            id=s.id, name=s.name or s.id, machine_id=mid,
            transitions=tuple(transitions_by_state.get(s.id, [])),
            activations=tuple(activations_by_state.get(s.id, [])),
            on_enter=s.on_enter, on_exit=s.on_exit,
            timeout_sec=s.timeout_sec, timeout_event=s.timeout_event,
        )

    # ---- 3.8 组装 CMachine ----
    cmachines: dict[str, CMachine] = {}
    for m in machines_o:
        sid = machine_initial.get(m.id)
        if sid is None or sid not in cstates:
            continue
        cmachines[m.id] = CMachine(
            id=m.id, name=m.name or m.id, initial_state_id=sid,
            end_signal=(m.end_signal or DEFAULT_END_SIGNAL).strip() or DEFAULT_END_SIGNAL,
            states=tuple(machine_states.get(m.id, [])),
        )

    # ---- 3.9 根状态机推断 ----
    activated_targets = {ac.target_machine_id for ac in raw_activations.values()}
    end_link_targets: set[str] = set()
    end_links: dict[str, list[str]] = {}
    for c in doc.connections:
        src, dst = objs.get(c.from_), objs.get(c.to)
        if (src and dst and src.type == "state_machine" and c.fromPin == "end"
                and dst.type == "state_machine" and c.toPin == "activator"):
            end_links.setdefault(src.id, []).append(dst.id)
            end_link_targets.add(dst.id)
    non_roots = activated_targets | end_link_targets
    root_candidates = [m.id for m in machines_o if m.id not in non_roots]

    root_id: Optional[str] = None
    if doc.root:
        root_id = _resolve_ref(doc.root, machines_o)
        if root_id is None:
            err(f"spec.root「{doc.root}」找不到对应状态机")
    else:
        if len(root_candidates) == 1:
            root_id = root_candidates[0]
        elif len(root_candidates) == 0:
            err("无法确定根状态机：所有状态机的 activator 都被连线占用（可能存在激活环），"
                "请在 spec 顶层用 root 字段指定")
        else:
            err("存在多个无 activator 入边的状态机（"
                f"{'、'.join(label(m) for m in root_candidates)}），无法确定根，"
                "请在 spec 顶层用 root 字段指定，或用激活动作把它们串起来")

    # 未被任何迁移/激活使用的状态机（除根外）给 warning
    for m in machines_o:
        if m.id in cmachines and m.id != root_id and m.id not in activated_targets and m.id not in end_link_targets:
            warnings.append(f"状态机 {label(m.id)} 既不是根，也没有被任何激活动作/end 链引用，永远不会运行")

    if errors:
        raise FsmCompileError(name, errors, warnings)

    return CompiledFsm(
        name=name, machines=cmachines, states=cstates,
        root_machine_id=root_id, end_links=end_links, warnings=warnings,
    )


def _resolve_ref(ref: str, machines: list[FsmObject]) -> Optional[str]:
    """按 id 或 name 解析状态机引用。"""
    ref = ref.strip()
    for m in machines:
        if m.id == ref or (m.name or m.id) == ref:
            return m.id
    return None


# ---------------------------------------------------------------------------
# 四、运行时
# ---------------------------------------------------------------------------

@dataclass
class FsmTrace:
    seq: int
    ts: float
    kind: str                 # enter/exit/transition/activate/close/complete/timeout/unhandled
    machine: str
    state: Optional[str] = None
    detail: dict[str, Any] = field(default_factory=dict)


@dataclass
class FsmContext:
    """传给业务回调的上下文：只读信息 + 受控的运行时操作。"""
    runtime: "FsmRuntime"
    machine: CMachine
    state: Optional[CState]
    event: Optional[str]

    def send(self, event: str) -> bool:
        return self.runtime.send(event)

    def close_machine(self) -> None:
        """业务在状态动作里显式结束当前状态机（等价于投递它的 end_signal）。"""
        self.runtime.close_machine(self.machine.id)

    @property
    def state_age(self) -> float:
        return self.runtime.state_age(self.machine.id)


class FsmHandler:
    """业务动作接缝：默认实现仅记录日志。RobotCtrl 继承本类，把动作转成下发命令。

    内核不 import 任何 IO/BoardSrv；所有真实副作用（移动、拍照、充电）都在这里发生，
    且保持同步语义；若需异步，请在实现里用 loop.call_soon_threadsafe 投递，不要阻塞内核。
    """

    def on_enter(self, ctx: FsmContext, state: CState) -> None:
        logger.info("[fsm] enter %s/%s", ctx.machine.name, state.name)

    def on_exit(self, ctx: FsmContext, state: CState) -> None:
        logger.info("[fsm] exit  %s/%s", ctx.machine.name, state.name)

    def call_action(self, ctx: FsmContext, key: str, phase: str) -> None:
        """state.on_enter / on_exit 填写动作 key 时回调（phase='enter'|'exit'）。"""
        logger.info("[fsm] action %s/%s key=%s", ctx.machine.name, phase, key)

    def on_unhandled(self, ctx: FsmContext, event: str) -> None:
        logger.debug("[fsm] unhandled event=%s in %s", event, ctx.machine.name)

    def on_error(self, ctx: Optional[FsmContext], exc: Exception) -> bool:
        """回调内抛异常时触发。返回 True 表示已处理（继续运行）；False 则继续向上抛。"""
        logger.exception("[fsm] handler error: %s", exc)
        return False


@dataclass
class _Activation:
    machine_id: str
    action_id: Optional[str]          # 由哪个激活动作激活；根/end 链为 None
    caller_machine_id: Optional[str]
    source_state_id: Optional[str]
    current: str
    entered_at: float
    timed_out: bool = False


class FsmRuntimeError(RuntimeError):
    pass


class FsmRuntime:
    """声明式状态机运行时（同步、确定性、可多实例）。

    用法：
        rt = FsmSpecDoc.from_file(path).compile().runtime(MyHandler())
        rt.start()
        rt.send("收到巡检")
        rt.tick(time.monotonic())
    """

    def __init__(self, compiled: CompiledFsm, handler: Optional[FsmHandler] = None,
                 clock: Callable[[], float] = time.monotonic, trace_size: int = 500):
        self.fsm = compiled
        self.handler = handler or FsmHandler()
        self.clock = clock
        self.running = False
        self._machines: dict[str, _Activation] = {}
        self._stack: list[str] = []          # machine_id，栈顶在最后（LIFO 分发）
        self._seq = 0
        self.history: deque[FsmTrace] = deque(maxlen=trace_size)

    # ---------- 生命周期 ----------

    def start(self, now: Optional[float] = None) -> None:
        if self.running:
            raise FsmRuntimeError("状态机已在运行")
        now = self.clock() if now is None else now
        self.running = True
        self._activate_machine(self.fsm.root_machine_id, None, None, None, now)

    def stop(self, now: Optional[float] = None) -> None:
        """整体停止：退出所有激活状态机（子机先于父机）。"""
        now = self.clock() if now is None else now
        for mid in reversed(list(self._stack)):
            self._deactivate_machine(mid, now, fire_completion=False)
        self._stack.clear()
        self._machines.clear()
        self.running = False

    # ---------- 事件 ----------

    def send(self, event: str, now: Optional[float] = None) -> bool:
        """向激活栈投递事件，栈顶（最内层子机）优先，消费即止。返回是否被处理。"""
        if not self.running:
            raise FsmRuntimeError("状态机尚未 start")
        now = self.clock() if now is None else now
        event = (event or "").strip()
        if not event:
            return False
        for mid in reversed(list(self._stack)):
            act = self._machines.get(mid)
            if act is None:
                continue
            machine = self.fsm.machines[mid]
            state = self.fsm.states[act.current]

            # 1) 信号迁移
            tr = next((t for t in state.transitions if t.event == event), None)
            if tr is not None:
                self._do_transition(mid, tr, now)
                return True

            # 2) 进入后等待信号的子机激活动作
            guarded = next((a for a in state.activations
                            if a.signal and a.signal == event), None)
            if guarded is not None:
                self._do_activate(mid, act.current, guarded, now)
                return True

            # 3) 本机结束信号
            if event == machine.end_signal:
                self._deactivate_machine(mid, now, fire_completion=True)
                return True

        # 无人消费
        top = self._stack[-1] if self._stack else None
        ctx = (self._ctx(self.fsm.machines[top], self.fsm.states[self._machines[top].current], event)
               if top else None)
        self._trace(now, "unhandled", top or "", None, {"event": event})
        if ctx:
            self._safe(self.handler.on_unhandled, ctx, event)
        return False

    def tick(self, now: Optional[float] = None) -> int:
        """推进时间：触发各激活状态的一次性超时。返回本次触发的超时数。时间外部注入。"""
        if not self.running:
            return 0
        now = self.clock() if now is None else now
        fired = 0
        for mid in list(self._stack):
            act = self._machines.get(mid)
            if act is None:
                continue
            state = self.fsm.states[act.current]
            if (state.timeout_sec is not None and state.timeout_event
                    and not act.timed_out and now - act.entered_at >= state.timeout_sec):
                act.timed_out = True
                self._trace(now, "timeout", mid, state.id,
                            {"after": state.timeout_sec, "event": state.timeout_event})
                if self.send(state.timeout_event, now):
                    fired += 1
        return fired

    # ---------- 内部：状态进入/退出 ----------

    def _enter_state(self, mid: str, sid: str, now: float) -> None:
        act = self._machines[mid]
        act.current = sid
        act.entered_at = now
        act.timed_out = False
        machine = self.fsm.machines[mid]
        state = self.fsm.states[sid]
        ctx = self._ctx(machine, state, None)
        self._safe(self.handler.on_enter, ctx, state)
        if state.on_enter:
            self._safe(self.handler.call_action, ctx, state.on_enter, "enter")
        self._trace(now, "enter", mid, sid)

        # 进入即激活的子状态机（无 signal 的激活动作）
        for ac in state.activations:
            if not ac.signal:
                self._do_activate(mid, sid, ac, now)

    def _exit_state(self, mid: str, now: float) -> None:
        act = self._machines.get(mid)
        if act is None:
            return
        sid = act.current
        machine = self.fsm.machines[mid]
        state = self.fsm.states[sid]
        ctx = self._ctx(machine, state, None)

        # 退出父状态：连带关闭由该状态激活、仍在运行的后代状态机（不触发 complete）
        for child_mid in [m for m, a in self._machines.items()
                          if a.caller_machine_id == mid and a.source_state_id == sid]:
            self._deactivate_machine(child_mid, now, fire_completion=False)

        if state.on_exit:
            self._safe(self.handler.call_action, ctx, state.on_exit, "exit")
        self._safe(self.handler.on_exit, ctx, state)
        self._trace(now, "exit", mid, sid)

    # ---------- 内部：迁移 / 激活 / 结束 ----------

    def _do_transition(self, mid: str, tr: CTransition, now: float) -> None:
        act = self._machines[mid]
        if act.current not in tr.sources:
            return  # 防御：当前状态不是该迁移的源
        self._trace(now, "transition", mid, act.current,
                    {"event": tr.event, "action": tr.name, "to": tr.targets[0]})
        self._exit_state(mid, now)
        self._enter_state(mid, tr.targets[0], now)   # 一事件一迁移，不递归 send

    def _do_activate(self, caller_mid: str, source_sid: str, ac: CActivation,
                     now: float) -> None:
        tgt = ac.target_machine_id
        if tgt in self._machines:
            raise FsmRuntimeError(
                f"状态机「{self.fsm.machines[tgt].name}」已处于激活态，不能重复激活"
                f"（动作「{ac.name}」）；请检查图中是否存在激活环")
        self._activate_machine(tgt, ac.id, caller_mid, source_sid, now)
        self._trace(now, "activate", caller_mid, source_sid,
                    {"action": ac.name, "target": self.fsm.machines[tgt].name})

    def _activate_machine(self, mid: str, action_id: Optional[str],
                          caller_mid: Optional[str], source_sid: Optional[str],
                          now: float) -> None:
        machine = self.fsm.machines[mid]
        act = _Activation(
            machine_id=mid, action_id=action_id, caller_machine_id=caller_mid,
            source_state_id=source_sid, current=machine.initial_state_id,
            entered_at=now,
        )
        self._machines[mid] = act
        self._stack.append(mid)
        self._enter_state(mid, machine.initial_state_id, now)

    def close_machine(self, mid: str, now: Optional[float] = None) -> None:
        """显式关闭某台激活中的状态机。"""
        if mid not in self._machines:
            raise FsmRuntimeError(f"状态机 {mid} 当前未激活")
        now = self.clock() if now is None else now
        self._deactivate_machine(mid, now, fire_completion=True)

    def _deactivate_machine(self, mid: str, now: float, *, fire_completion: bool) -> None:
        act = self._machines.get(mid)
        if act is None:
            return
        machine = self.fsm.machines[mid]

        # 先退出后代（栈中在它之上、由它链路激活的），再退自己
        for child_mid in [m for m, a in self._machines.items()
                          if _is_descendant(self._machines, m, mid)]:
            self._deactivate_machine(child_mid, now, fire_completion=False)

        self._exit_state(mid, now)
        self._stack.remove(mid)
        del self._machines[mid]
        self._trace(now, "close", mid, None, {"fire_completion": fire_completion})

        action_id = act.action_id
        caller_mid = act.caller_machine_id
        source_sid = act.source_state_id

        if fire_completion and action_id is not None:
            # 子例程式激活：子机结束 -> 找激活动作 -> 走 complete
            ac = self._find_activation(action_id)
            if ac is not None and ac.complete_targets:
                caller_act = self._machines.get(caller_mid) if caller_mid else None
                if caller_act is not None and caller_act.current == source_sid:
                    self._trace(now, "complete", caller_mid, source_sid,
                                {"action": ac.name, "to": ac.complete_targets[0]})
                    self._exit_state(caller_mid, now)
                    self._enter_state(caller_mid, ac.complete_targets[0], now)
                else:
                    logger.warning("子机 %s 结束，但调用方状态已迁移，忽略 complete", machine.name)
            # 无 complete 目标：源状态继续（fire-and-forget），什么都不做
            return

        if action_id is None:
            # 根 或 end 链机器结束：处理 end pin 平级链；根无下游则整体停止
            downs = [d for d in self.fsm.end_links.get(mid, []) if d not in self._machines]
            if downs:
                for d in downs:
                    self._activate_machine(d, None, caller_mid, source_sid, now)
            elif mid == self.fsm.root_machine_id and not self._machines:
                self.running = False

    def _find_activation(self, action_id: str) -> Optional[CActivation]:
        for st in self.fsm.states.values():
            for ac in st.activations:
                if ac.id == action_id:
                    return ac
        return None

    # ---------- 观测 ----------

    def state_age(self, mid: str) -> float:
        act = self._machines.get(mid)
        return self.clock() - act.entered_at if act else 0.0

    def current_state(self, machine_id: Optional[str] = None) -> Optional[str]:
        mid = machine_id or self.fsm.root_machine_id
        act = self._machines.get(mid)
        return self.fsm.states[act.current].name if act else None

    def snapshot(self) -> dict[str, Any]:
        return {
            "running": self.running,
            "root": self.fsm.machines[self.fsm.root_machine_id].name,
            "stack": [self.fsm.machines[m].name for m in self._stack],
            "machines": {
                self.fsm.machines[m].name: {
                    "state": self.fsm.states[a.current].name,
                    "state_id": a.current,
                    "activated_by": (self._find_activation(a.action_id).name
                                     if a.action_id and self._find_activation(a.action_id) else None),
                }
                for m, a in self._machines.items()
            },
        }

    # ---------- 小工具 ----------

    def _ctx(self, machine: CMachine, state: Optional[CState], event: Optional[str]) -> FsmContext:
        return FsmContext(runtime=self, machine=machine, state=state, event=event)

    def _safe(self, fn: Callable[..., Any], *args: Any) -> None:
        """执行业务回调，异常交给 handler.on_error 决策；未处理则向上抛。"""
        try:
            fn(*args)
        except Exception as exc:  # noqa: BLE001
            ctx = args[0] if args and isinstance(args[0], FsmContext) else None
            if not self.handler.on_error(ctx, exc):
                raise

    def _trace(self, ts: float, kind: str, machine: str, state: Optional[str],
               detail: Optional[dict] = None) -> None:
        self._seq += 1
        self.history.append(FsmTrace(self._seq, ts, kind, machine, state, dict(detail or {})))


def _is_descendant(machines: dict[str, _Activation], mid: str, ancestor: str) -> bool:
    """mid 是否为 ancestor 的后代（沿 caller 链向上能走到 ancestor），且不是 ancestor 本身。"""
    cur = machines.get(mid)
    if cur is None or cur.machine_id == ancestor:
        return False
    seen: set[str] = set()
    node = cur.caller_machine_id
    while node is not None and node not in seen:
        if node == ancestor:
            return True
        seen.add(node)
        nxt = machines.get(node)
        node = nxt.caller_machine_id if nxt else None
    return False
