"""薄手写状态机基类（State / StateMachine）。
@deprecated

定位
----
介于 sm.py（状态逻辑与业务全揉在一起、跑不起来的草稿）和 fsm_spec.py（数据驱动的
声明式解释器）之间：**业务流程直接写在 Python 状态类里**（守卫、参数、运动学计算想怎么写
怎么写），而把多状态机最容易出错的几件事交给基类一次性兜住：

* 事件驱动、**一个事件最多触发一次迁移，不级联**；
* 超时/周期事件**绑定状态生命周期，退出状态立即作废**（修掉 sm.py 定时器泄漏）；
* 状态实例**每次进入都新建、退出即丢弃**，天然无残留、子状态机可重复激活；
* 子状态机 **LIFO 激活栈**：事件最内层子机优先消费、不处理才向父状态冒泡；
* 父状态退出时**连带关闭其激活的子机**；子机 ``complete`` 后回调父状态（可回连迁移）；
* 内核**纯同步、时间由外部注入**（``clock`` / ``tick(now)``），不 import asyncio、不碰 IO，
  可确定性单测；业务动作通过 ``ctx`` 外抛。

最小示例
--------
>>> class Idle(State):
...     def handle(self, event):
...         if event == "go":
...             self.goto(Running); return True
...         return False
>>> class Running(State):
...     def enter(self):
...         self.arm_timeout("stuck", 30)      # 30s 没进展则回到 Idle
...     def handle(self, event):
...         if event in ("done", "stuck"):
...             self.goto(Idle); return True
...         return False
>>> m = StateMachine(Idle, ctx=my_robot, name="main")
>>> m.start()
>>> m.send("go")          # 外部事件（上位机指令 / 下位机上报）
>>> m.tick(now)           # 外部心跳周期调用，驱动超时与周期事件

层次（子状态机）
----------------
父状态在 ``enter`` 里 ``self.activate(child, on_complete=self._child_done)``；激活子机
**不会退出父状态**（父子并行）。子机跑完调用 ``self.complete(result)``，基类把它弹出激活栈
并回调父状态的 ``on_complete``，由父状态决定迁到哪里。要重复跑同一个子流程，重新 new 一个
子机实例再 activate 即可（可重入）。

周期事件（替代 sm.py 的 tick10/30/60/300）
----------------------------------------
``StateMachine(..., intervals=[(10, "tick10"), (60, "tick60")])``；``tick(now)`` 到点会把该
事件派发给当前状态的 ``handle``，且**每次进入新状态后周期计时归零**（复刻 sm.py 的
resetIntervalSignals 语义，避免刚进入就被周期事件打断）。

一次性超时（替代 sm.py 的 setTimeout）
------------------------------------
``self.arm_timeout("就位超时", 60)``；到点基类派发同名事件给当前状态 ``handle``，状态退出
即作废、每次进入只武装一次。

与异步 IO / BoardSrv 的桥接（重要）
----------------------------------
内核是同步的，**不要在 State 里 await**。需要 IO 时：在 ``handle``/``enter`` 里通过 ``ctx``
*投递一条命令*（fire-and-forget，例如 ``self.ctx.board.request(...)`` 或往 RobotCtrl 的命令
队列塞任务），异步结果回来后，由宿主（RobotCtrl / BoardSrv 回调）再调用 ``machine.send(事件)``
驱动下一步。状态机只做"何时做、做到什么状态转下一步"的同步决策，IO 在命令对象里异步执行。
"""
from __future__ import annotations

import logging
import time
from collections import deque
from typing import Any, Callable, Deque, Optional, Sequence, Tuple

logger = logging.getLogger(__name__)

# (周期秒数, 事件名)
Interval = Tuple[float, str]
# 子机结束回调：complete(result)
CompleteCb = Callable[[Any], None]


class State:
    """一个状态。业务继承本类，按需重写 enter/exit/handle。

    状态实例由 StateMachine 在每次进入时新建，因此：

    * 本次驻留的局部变量直接在 ``enter`` 里赋值即可，退出即回收，无需手动清理；
    * 跨状态共享的业务数据（位置、电量、当前任务……）放到 ``ctx`` 上，不要放状态实例；
    * ``self.machine`` / ``self.ctx`` 在 enter/handle/exit 期间已由机器绑定，可直接使用。
    """

    #: 状态名，缺省取类名；可设中文 label 仅用于展示
    name: Optional[str] = None
    label: Optional[str] = None

    # 由机器绑定
    _machine: "Optional[StateMachine]" = None

    # ---- 生命周期钩子（业务重写）----
    def enter(self, **params: Any) -> None:
        """进入状态时调用一次；params 来自 goto(State, **params)。"""

    def exit(self) -> None:
        """离开状态时调用一次。"""

    def handle(self, event: str, *args: Any) -> bool:
        """处理一个事件。

        返回 True 表示本状态消费了该事件（无论是否调用了 goto）；返回 False/None 表示不处理，
        事件将向父状态机冒泡。**一次 handle 调用最多做一次 goto**，迁移后新状态不会在同一事件
        里被再次触发（不级联）。
        """
        return False

    # ---- 给业务用的便捷方法（转发给所属机器）----
    def goto(self, state: "type[State] | str", **params: Any) -> None:
        """迁移到另一个状态（传 State 子类，或机器内注册的状态名字符串）。"""
        assert self._machine is not None, "State 尚未绑定 StateMachine"
        self._machine.goto(state, **params)

    def activate(self, child: "StateMachine", on_complete: Optional[CompleteCb] = None) -> None:
        """激活一个子状态机（不退出本状态，父子并行）。"""
        assert self._machine is not None, "State 尚未绑定 StateMachine"
        self._machine.activate(child, on_complete=on_complete)

    def complete(self, result: Any = None) -> None:
        """结束本状态所属的（子）状态机，回到激活它的父状态机并触发 on_complete。"""
        assert self._machine is not None, "State 尚未绑定 StateMachine"
        self._machine.complete(result)

    def arm_timeout(self, name: str, delay: float) -> None:
        """武装一次性超时：delay 秒后若仍在本状态，派发同名事件；退出本状态即作废。"""
        assert self._machine is not None, "State 尚未绑定 StateMachine"
        self._machine.arm_timeout(name, delay)

    def clear_timeout(self, name: str) -> None:
        assert self._machine is not None, "State 尚未绑定 StateMachine"
        self._machine.clear_timeout(name)

    def send(self, event: str, *args: Any) -> bool:
        """向所属机器发送事件（沿 LIFO 栈正常路由）。"""
        assert self._machine is not None, "State 尚未绑定 StateMachine"
        return self._machine.send(event, *args)

    @property
    def machine(self) -> "StateMachine":
        assert self._machine is not None, "State 尚未绑定 StateMachine"
        return self._machine

    @property
    def ctx(self) -> Any:
        return self.machine.ctx

    @classmethod
    def state_name(cls) -> str:
        return cls.name or cls.__name__


class StateMachine:
    """一台状态机。可独立作为根机，也可被另一台机器 activate 成为子机。

    参数
    ----
    initial: 初始状态的 State 子类（也可在子类里用嵌套 State + __init_subclass__ 注册后传名字符串）。
    ctx:     业务上下文（持有 BoardSrv 句柄、RobotState、命令投递方法等），子机默认共享。
    intervals: 周期事件列表 ``[(秒, 事件名), ...]``，如 [(10,"tick10"),(60,"tick60")]。
    clock:   返回当前单调时间（秒）的可调用对象，默认 time.monotonic；测试可传虚拟时钟。
    history: 历史轨迹容量，0 表示不记录。
    name:    机器名，缺省取类名。
    """

    #: 子类通过嵌套 State 自动注册的 状态名 -> 状态类（__init_subclass__ 填充，机器间隔离）
    _named_states: dict[str, type[State]] = {}

    #: 子类可在此指定默认初始状态（构造未传 initial 时使用）
    initial_state: "Optional[type[State] | str]" = None

    def __init_subclass__(cls, **kwargs: Any) -> None:
        """收集定义在本机器类体内的嵌套 State 子类，使其可按名字 goto。

        也会合并父机器类注册过的状态。状态类直接 goto 时无需注册；这只是给
        "嵌套定义 + 按名引用"提供便利，不引入全局注册表（避免跨机器重名污染）。
        """
        super().__init_subclass__(**kwargs)
        named: dict[str, type[State]] = {}
        for base in cls.__mro__[1:]:
            named.update(getattr(base, "_named_states", {}))
        for value in list(vars(cls).values()):
            if isinstance(value, type) and issubclass(value, State) and value is not State:
                named[value.state_name()] = value
        cls._named_states = named

    def __init__(
        self,
        initial: "Optional[type[State] | str]" = None,
        ctx: Any = None,
        intervals: Sequence[Interval] = (),
        clock: Callable[[], float] = time.monotonic,
        history: int = 200,
        name: Optional[str] = None,
    ) -> None:
        self._initial = initial if initial is not None else self.initial_state
        self.ctx = ctx
        self._intervals: list[Interval] = list(intervals)
        self._clock = clock
        self.name = name or type(self).__name__

        self.running = False
        self._state: Optional[State] = None
        self._generation = 0  # 每次 goto 自增；用于作废上一代状态武装的超时/周期派发
        self._cur = 0.0       # 最近一次 start/send/tick/goto 的时间锚，内部迁移/超时沿用它
        # name -> (到期时刻, 武装时的 generation)
        self._timeouts: dict[str, Tuple[float, int]] = {}
        # event -> 下一次到期时刻
        self._interval_next: dict[str, float] = {}
        # 子机激活栈（栈顶 = 最内层）
        self._children: list[StateMachine] = []
        self._parent: Optional[StateMachine] = None
        self._on_complete: Optional[CompleteCb] = None

        self._history: Optional[Deque[tuple]] = (
            deque(maxlen=history) if history > 0 else None
        )

    # ------------------------------------------------------------------ #
    # 生命周期
    # ------------------------------------------------------------------ #
    def start(self, now: Optional[float] = None) -> None:
        """启动机器并进入初始状态。"""
        if self.running:
            raise RuntimeError(f"状态机 {self.name} 已在运行")
        now = self._now(now)
        self._cur = now
        self.running = True
        self._trace("start")
        if self._initial is not None:
            self.goto(self._initial, now=now)
        else:
            self._reset_intervals(now)

    def stop(self, now: Optional[float] = None) -> None:
        """停止根机：连带关闭子机、退出当前状态。子机正常结束请用 complete。"""
        if not self.running and self._state is None:
            return
        now = self._now(now)
        self._cur = now
        self._close_children(now=now)
        self._exit_current(now=now)
        self.running = False
        self._timeouts.clear()
        self._interval_next.clear()
        self._trace("stop")

    # ------------------------------------------------------------------ #
    # 事件
    # ------------------------------------------------------------------ #
    def send(self, event: str, *args: Any, now: Optional[float] = None) -> bool:
        """发送事件。LIFO：最内层子机优先，其次本机当前状态，都不处理则 on_unhandled。"""
        if not self.running:
            return False
        self._cur = self._now(now)
        return self._dispatch(event, *args)

    def _dispatch(self, event: str, *args: Any) -> bool:
        # 栈顶子机优先
        if self._children:
            top = self._children[-1]
            if top._dispatch(event, *args):
                return True
        if self._state is not None:
            if bool(self._state.handle(event, *args)):
                return True
        if self.on_unhandled(event, *args):
            return True
        self._trace("unhandled", event=event)
        return False

    def on_unhandled(self, event: str, *args: Any) -> bool:
        """重写以兜底未处理事件（默认仅 debug 日志、不消费）。"""
        logger.debug("[%s] 未处理事件: %s", self.name, event)
        return False

    # ------------------------------------------------------------------ #
    # 状态迁移
    # ------------------------------------------------------------------ #
    def goto(self, target: "type[State] | str", now: Optional[float] = None, **params: Any) -> None:
        """迁移到目标状态：关闭子机 -> exit 旧状态 -> 新建并 enter 新状态。"""
        now = now if now is not None else self._cur
        self._cur = now
        state_cls = self._resolve(target)
        # 父状态离开：连带关闭它激活的所有子机（不触发 on_complete）
        self._close_children(now=now)
        self._exit_current(now=now)

        self._generation += 1
        gen = self._generation
        self._timeouts.clear()  # 上一代状态武装的超时一律作废
        self._reset_intervals(now)

        new_state = state_cls()
        new_state._machine = self
        self._state = new_state
        self._trace("enter", state=state_cls.state_name(), gen=gen)
        self._call(lambda: new_state.enter(**params), where="enter", state=state_cls)

    def current_state_name(self) -> Optional[str]:
        return self._state.state_name() if self._state is not None else None

    def leaf_state_name(self) -> Optional[str]:
        """最内层活跃子机当前状态名（用于上报/前端高亮）。"""
        if self._children:
            leaf = self._children[-1].leaf_state_name()
            return leaf if leaf is not None else self.current_state_name()
        return self.current_state_name()

    def state_path(self) -> list[str]:
        """从本机沿活跃子机栈顶到叶子的 "机器:状态" 路径。"""
        path = [f"{self.name}:{self.current_state_name()}"]
        if self._children:
            path.extend(self._children[-1].state_path())
        return path

    # ------------------------------------------------------------------ #
    # 子状态机
    # ------------------------------------------------------------------ #
    def activate(self, child: "StateMachine", on_complete: Optional[CompleteCb] = None) -> None:
        """激活子机并压入栈顶；不退出当前状态（父子并行）。子机共享 ctx 与时钟。"""
        if not self.running:
            raise RuntimeError(f"状态机 {self.name} 未运行，无法激活子机 {child.name}")
        if child.running or child._state is not None:
            raise RuntimeError(f"子状态机 {child.name} 已在运行；需要重入请 new 一个新实例")
        if child is self or child in self._ancestors():
            raise RuntimeError(f"不能激活自身或祖先状态机 {child.name}（会形成环）")
        child._parent = self
        child._on_complete = on_complete
        child.ctx = child.ctx if child.ctx is not None else self.ctx
        child._clock = self._clock
        self._children.append(child)
        self._trace("activate", child=child.name)
        child.start(self._cur)

    def complete(self, result: Any = None) -> None:
        """子机正常结束：弹出激活栈、停止子机、回调父状态的 on_complete。"""
        parent = self._parent
        if parent is None:
            # 根机调 complete 等价于停止
            self.stop()
            return
        if self in parent._children:
            parent._children.remove(self)
        self._teardown()
        self._trace("complete")
        cb = self._on_complete
        self._parent = None
        self._on_complete = None
        if cb is not None:
            parent._call(lambda: cb(result), where="on_complete", machine=self)

    def _close_children(self, now: Optional[float] = None) -> None:
        """父状态退出时连带关闭所有子机，且不触发 on_complete。"""
        for child in list(self._children):
            child._parent = None
            child._on_complete = None
            child._teardown()
        self._children.clear()

    def _teardown(self) -> None:
        self._close_children()
        self._exit_current()
        self.running = False
        self._timeouts.clear()
        self._interval_next.clear()

    def _ancestors(self) -> list["StateMachine"]:
        out, p = [], self._parent
        while p is not None:
            out.append(p)
            p = p._parent
        return out

    # ------------------------------------------------------------------ #
    # 超时 / 周期 / 时钟
    # ------------------------------------------------------------------ #
    def arm_timeout(self, name: str, delay: float) -> None:
        if self._state is None:
            raise RuntimeError("当前没有活动状态，无法 arm_timeout")
        self._timeouts[name] = (self._cur + delay, self._generation)

    def clear_timeout(self, name: str) -> None:
        self._timeouts.pop(name, None)

    def tick(self, now: Optional[float] = None) -> int:
        """推进时间：先 tick 活跃子机，再处理本机一次性超时与周期事件。返回触发的事件数。

        一旦本 tick 内发生状态迁移（generation 变化），后续超时/周期事件本轮不再派发，
        等下一 tick——保证一个 tick 内不级联。
        """
        if not self.running:
            return 0
        now = self._now(now)
        self._cur = now
        fired = 0
        gen = self._generation

        for child in list(self._children):
            fired += child.tick(now)
        if self._generation != gen:
            return fired  # 子机 tick 中已导致本机迁移（如 complete 回调）
        if self._state is None:
            return fired

        # 一次性超时：到点派发同名事件
        due = [name for name, (dl, g) in self._timeouts.items() if g == gen and dl <= now]
        for name in due:
            self._timeouts.pop(name, None)
            self._trace("timeout", name=name)
            self._dispatch(name)
            fired += 1
            if self._generation != gen:
                return fired

        # 周期事件
        for _period, event in self._intervals:
            deadline = self._interval_next.get(event)
            if deadline is not None and deadline <= now:
                self._interval_next[event] = now + _period
                self._trace("interval", event=event)
                self._dispatch(event)
                fired += 1
                if self._generation != gen:
                    return fired
        return fired

    def _reset_intervals(self, now: float) -> None:
        # 进入新状态后周期计时归零（复刻 sm.py resetIntervalSignals）
        self._interval_next = {event: now + period for period, event in self._intervals}

    def _now(self, now: Optional[float]) -> float:
        return now if now is not None else self._clock()

    # ------------------------------------------------------------------ #
    # 内部工具
    # ------------------------------------------------------------------ #
    def _resolve(self, target: "type[State] | str") -> type[State]:
        if isinstance(target, str):
            cls = self._named_states.get(target)
            if cls is None:
                raise KeyError(
                    f"状态机 {self.name} 找不到名为 {target!r} 的状态；"
                    f"可用：{sorted(self._named_states)}，或直接传 State 子类"
                )
            return cls
        if not (isinstance(target, type) and issubclass(target, State)):
            raise TypeError(f"goto 目标必须是 State 子类或其注册名，得到 {target!r}")
        return target

    def _exit_current(self, now: Optional[float] = None) -> None:
        if self._state is not None:
            old = self._state
            self._state = None
            self._generation += 1
            self._timeouts.clear()
            self._trace("exit", state=old.state_name())
            self._call(old.exit, where="exit", state=type(old))

    def _call(self, fn: Callable[[], Any], where: str, **ctx_info: Any) -> Any:
        try:
            return fn()
        except Exception as exc:  # noqa: BLE001 - 统一交给 handle_error 决策
            if self.handle_error(exc, where, **ctx_info) is True:
                return None
            raise

    def handle_error(self, exc: Exception, where: str, **ctx_info: Any) -> bool:
        """状态回调抛异常时的兜底。默认记录并上抛；重写返回 True 可吞掉异常继续运行。"""
        logger.exception("[%s] 状态机在 %s 阶段异常（%s）: %r", self.name, where, ctx_info, exc)
        return False

    def _trace(self, kind: str, **info: Any) -> None:
        if self._history is not None:
            self._history.append((kind, info))

    @property
    def clock(self) -> Callable[[], float]:
        """本机使用的时钟（子机激活时与父机一致），供状态构造同钟子机。"""
        return self._clock

    @property
    def history(self) -> Deque[tuple]:
        assert self._history is not None, "该机器未开启 history（history=0）"
        return self._history
