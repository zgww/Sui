"""Sm：if/else 式（轮询表驱动）状态机引擎。

范式（行为写在宿主的 ``beh_xxx`` 里，直观、平铺）::

    sm = Sm("charge", initSt="start")
    def beh_charge():
        st, sig = sm.st, sm.signal
        if st == "start" and sig == "enter":
            移动到最近的充电桩(); sm.setState("移动中")
        if st == "移动中" and sig == "到达目标位置":
            sm.setState("就位优化")
        ...

    # 每个节拍：先 beh（读 st/signal 决策），再 sm.tick()（消费动作、产生周期/超时信号）
    beh_charge(); sm.tick()

核心概念
--------
- ``st``：当前状态（字符串）；``None`` 表示未激活（用于子机按需启动 / 结束后可重入）。
- ``acts``：动作队列（FIFO），每个节拍 :meth:`tick` 只消费队首一个动作并把其信号放到
  ``self.signal``，供下一节拍的 ``beh`` 读取。
- ``setState(s)``：依次入队 ``exit`` / ``enter`` 两个动作，因此一次迁移占两个节拍
  （exit 拍、enter 拍各一），``beh`` 里 ``if sig == "enter"`` 即"进入该状态的那一拍"。
- ``emit(sig)``：入队一个普通信号（不改状态），用于外部事件。
- 周期信号 ``intervalSignals``（tick10/30/60/300）：进入状态自动归零。
- 一次性超时 ``setTimeout(sec, sig)``：到点且仍处于武装状态时发一次信号并移除；进入其它
  状态会自动作废指向旧状态的超时（避免泄漏）。
- 子机：``parent.signalMove("enter", childSm)`` 激活（未启动则 start）；子机结束自行
  ``stop()`` 并向主机 emit 完成信号。

与旧草稿的差异：旧 sm.py 不可编译且混入了其它语言语法；本文件保留同名类与队列语义，修正
语法错误、``sm.sig`` 笔误、子机激活不发 enter、定时器不清理等问题，并支持注入时钟（测试用）。
"""
from __future__ import annotations

import time
from dataclasses import dataclass
from typing import Callable, Optional

# 默认周期信号（秒）
DEFAULT_INTERVALS: tuple[tuple[int, str], ...] = (
    (10, "tick10"),
    (30, "tick30"),
    (60, "tick60"),
    (300, "tick300"),
)


# --------------------------------------------------------------------------- #
# 动作（acts 队列元素）
# --------------------------------------------------------------------------- #
class SmAct:
    """队列动作基类。"""

    signal: str = ""

    def apply(self, sm: "Sm", now: float) -> None:
        pass


@dataclass
class SmSignal(SmAct):
    """一个信号动作：enter/exit 携带状态迁移，其它为纯信号。"""

    signal: str = ""
    fromState: Optional[str] = None
    toState: Optional[str] = None

    def apply(self, sm: "Sm", now: float) -> None:
        if self.signal == "enter":
            sm._on_enter(self.toState, now)
        elif self.signal == "exit":
            sm.st = self.toState
        # 普通信号：applyAct 已把 sm.signal 置位，不改状态


class SmSetState(SmAct):
    """直接设置状态（一般用 setState 走 exit/enter，本类保留用于特殊场景）。"""

    def __init__(self, state: str) -> None:
        self.state = state

    def apply(self, sm: "Sm", now: float) -> None:
        sm.st = self.state


# --------------------------------------------------------------------------- #
# 周期 / 超时信号
# --------------------------------------------------------------------------- #
class SmIntervalSignal:
    def __init__(self, interval_sec: float, signal: str, clock: Callable[[], float]) -> None:
        self.interval_sec = interval_sec
        self.signal = signal
        self._clock = clock
        self.start_time = clock()

    def reset(self, now: Optional[float] = None) -> None:
        self.start_time = self._clock() if now is None else now

    def tick(self, sm: "Sm", now: float) -> None:
        if now - self.start_time >= self.interval_sec:
            sm.emit(self.signal)
            self.start_time = now


class SmTimeoutSignal:
    """一次性超时：到点且当前状态匹配 matchState（'*' 为任意）时发信号。"""

    def __init__(self, interval_sec: float, signal: str, match_state: str,
                 now: float) -> None:
        self.interval_sec = interval_sec
        self.signal = signal
        self.match_state = match_state
        self.start_time = now

    def tick(self, sm: "Sm", now: float) -> bool:
        if now - self.start_time >= self.interval_sec and (
            self.match_state == "*" or sm.st == self.match_state
        ):
            sm.emit(self.signal)
            return True
        return False


# --------------------------------------------------------------------------- #
# Sm
# --------------------------------------------------------------------------- #
class Sm:
    def __init__(
        self,
        name: str = "sm",
        initSt: str = "start",
        intervals: tuple[tuple[float, str], ...] = DEFAULT_INTERVALS,
        clock: Callable[[], float] = time.monotonic,
    ) -> None:
        self.name = name
        self.initSt = initSt
        self._clock = clock
        self.st: Optional[str] = None
        self.signal: Optional[str] = None
        self.acts: list[SmAct] = []
        self.intervalSignals = [
            SmIntervalSignal(sec, sig, clock) for sec, sig in intervals
        ]
        self.timeoutSignals: list[SmTimeoutSignal] = []
        self.enterTimestamp: float = 0.0
        # running 表示本机已 start（enter 可能尚在队列待消费）；stop 后置 False。
        # 不能用 st is not None 判定激活——start 后到首个 tick 消费 enter 前 st 仍为 None。
        self.running: bool = False

    # ------------------------------------------------------------ 状态
    @property
    def active(self) -> bool:
        """是否处于运行态（子机据此判断是否已激活）。"""
        return self.running

    def setTimeout(self, sec: float, signal: str, matchState: Optional[str] = None) -> None:
        self.timeoutSignals.append(
            SmTimeoutSignal(sec, signal, matchState or (self.st or "*"), self._clock())
        )

    def resetIntervalSignals(self, now: Optional[float] = None) -> None:
        now = self._clock() if now is None else now
        for isig in self.intervalSignals:
            isig.reset(now)

    def exitState(self, state: Optional[str]) -> None:
        self.acts.append(SmSignal("exit", self.st, state))

    def enterState(self, state: str) -> None:
        self.acts.append(SmSignal("enter", self.st, state))

    def setState(self, state: str) -> bool:
        if self.signal == "exit":
            raise RuntimeError(f"{self.name}: exit 信号拍不允许切换状态 -> {state}")
        self.exitState(state)
        self.enterState(state)
        return True

    def emit(self, signal: str) -> None:
        self.acts.append(SmSignal(signal))

    # ------------------------------------------------------------ 引擎
    def _on_enter(self, state: Optional[str], now: float) -> None:
        self.st = state
        self.resetIntervalSignals(now)
        self.enterTimestamp = now
        # 进入新状态：作废仍指向旧状态的一次性超时（修旧草稿的定时器泄漏）
        self.timeoutSignals = [
            t for t in self.timeoutSignals
            if t.match_state == "*" or t.match_state == state
        ]

    def applyAct(self, now: float) -> None:
        self.signal = None
        if self.acts:
            act = self.acts.pop(0)
            self.signal = act.signal
            act.apply(self, now)

    def tick(self, now: Optional[float] = None) -> None:
        now = self._clock() if now is None else now
        self.applyAct(now)
        for isig in self.intervalSignals:
            isig.tick(self, now)
        done = [t for t in self.timeoutSignals if t.tick(self, now)]
        for t in done:
            self.timeoutSignals.remove(t)

    # ------------------------------------------------------------ 生命周期
    def start(self, now: Optional[float] = None) -> None:
        """（重新）激活：清空队列/超时，从初始状态进入。"""
        now = self._clock() if now is None else now
        self.acts.clear()
        self.timeoutSignals.clear()
        self.st = None
        self.signal = None
        self.running = True
        self.resetIntervalSignals(now)
        self.enterState(self.initSt)

    def stop(self, now: Optional[float] = None) -> None:
        """结束并回到未激活态，可被再次 start。"""
        self.acts.clear()
        self.timeoutSignals.clear()
        self.st = None
        self.signal = None
        self.running = False

    # ------------------------------------------------------------ 子机/迁移糖
    def signalMove(self, signal: str, toState) -> None:
        """``toState`` 为 Sm：激活子机（未启动才 start）；为状态名：信号匹配则迁移。"""
        if isinstance(toState, Sm):
            child = toState
            if not child.active:
                child.start(self._clock())
            return
        if self.signal == signal:
            self.setState(toState)

    def broadcast(self, sms: list["Sm"], signal: str) -> None:
        for sm in sms:
            sm.emit(signal)

    @classmethod
    def tickAll(cls, sms: list["Sm"], now: Optional[float] = None) -> None:
        for sm in sms:
            sm.tick(now)
