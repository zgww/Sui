"""机器人状态机（RobotSm）——用 State/StateMachine 对旧 sm.py 的忠实迁移。

@deprecated

四台机器（与 sm.py 一一对应）：

* :class:`MainMachine`        主机：启动 / 空闲 / 手控模式 / 巡检中 / 去充电
* :class:`ChargeMachine`      充电子机：start→移动中→就位优化→充电微挪→充电中
* :class:`FloorMachine`       切楼层子机：到轿厢前→安全检测→进轿厢→切楼层→（出轿厢）→完成
* :class:`InspectionMachine`  巡检子机：航点开始→移动到航点→动作点→云台→执行动作→…→完成

与旧 sm.py 的对应关系
---------------------
* 旧的 ``behXxx()`` 每 tick 轮询 + ``if st==…`` 分支，改为各 :class:`RobotState` 子类的
  ``enter`` / ``handle``；状态名用中文 ``name`` 保持与原草稿、FsmEditor 文档一致（类名用英文
  便于跳转重构）。
* 旧 ``SmIntervalSignal``（tick10/30/60/300）改为机器的 ``intervals``，进入状态自动归零。
* 旧 ``setTimeout`` 改为 :meth:`State.arm_timeout`，退出状态自动作废（修掉定时器泄漏）。
* 旧主机 ``signalMove('enter', otherSm)`` 激活子机，改为父状态 ``enter`` 里
  ``self.activate(child, on_complete=…)``；旧子机结束 ``broadcastSignal`` + 主机分支回状态，
  改为子机 ``self.complete()`` + 父状态 ``on_complete`` 回调（不再靠全局广播）。
* 跨状态业务数据（旧 RobotState 及若干 XxxState）集中到 :class:`RobotCtx`；动作/检查函数成为
  ctx 上的方法（当前是与旧草稿一致的桩，真实实现里替换为 BoardSrv 命令与传感器缓存）。

旧草稿中被修正的缺陷（代码内以 ``[迁移补全]`` 标注）
----------------------------------------------------
* 切楼层 start 里 ``setState('')`` 空状态名：按所在位置补成跳到对应安全检测/进轿厢状态。
* 出轿厢阶段调用了未定义的 ``检查机器人在1号卡()``：在 ctx 补桩。
* floorSm 在旧草稿里没有任何激活入口：本文件完整实现 FloorMachine，但 MainMachine 暂不挂载
  （与旧草稿一致），待业务确认切楼层由哪个任务触发后，在对应父状态 activate 即可。

异步 IO
-------
内核同步，状态里**不要 await**。ctx 的动作方法当前是同步桩；生产环境应"投递命令→结果回来后
由宿主 machine.send(事件)"。例如 :meth:`InspectionMachine.ExecAction.enter` 真实实现应停在
ExecAction 等动作完成事件，再迁移动作完成，而不是假定动作立即完成。
"""
from __future__ import annotations

import logging
import time
from dataclasses import dataclass, field
from typing import Callable, Optional

from app.rail.state import State, StateMachine

logger = logging.getLogger(__name__)

# 旧 Sm 默认内置的周期信号（秒）
TICK_INTERVALS = [(10, "tick10"), (30, "tick30"), (60, "tick60"), (300, "tick300")]

# 手控模式超时：20 分钟无手控指令回空闲（旧 手控超时）
MANUAL_IDLE_SECONDS = 20 * 60
# 充电微挪：单步耗时、扫完一遍后的重试间隔、行程范围（旧充电微挪）
NUDGE_STEP_SECONDS = 2
NUDGE_RESWEEP_SECONDS = 60
NUDGE_RANGE = 10


# =========================================================================== #
# 业务上下文：跨状态数据 + 动作/检查桩（替换旧 RobotState 与散落的全局函数）
# =========================================================================== #
@dataclass
class CommandData:
    last_manual_ts: Optional[float] = None


@dataclass
class InspectionData:
    current_inspection_id: Optional[str] = None
    current_waypoint_id: Optional[str] = None
    current_action_index: int = 0


@dataclass
class SwitchFloorData:
    flag_go_out: bool = False


@dataclass
class ChargeData:
    flag_go_out: bool = False


@dataclass
class BatteryData:
    charging: bool = False


@dataclass
class NudgeData:
    offset: int = 0
    move_dir: int = 1


class RobotSmContext:
    """状态机与外部世界之间的门面（状态类只依赖它，不 import Robot/BoardSrv）。

    * **数据块**（command/inspection/switch_floor/charge/battery/nudge）：状态机跨状态运行时
      数据。生产环境传入 ``state``（:class:`app.rail.robot.RobotState`）复用同一份对象，使硬件
      上报写入与状态机读取指向同一处；不传则自建（测试/离线推演用）。
    * **动作/检查方法**：委托给 ``executor``（生产环境即 :class:`app.rail.robot.Robot`，动作是
      Robot 的成员函数）。executor 未提供或未实现某方法时，回退到与旧 sm.py 一致的安全默认桩，
      保证状态机在未接真机时也能独立推演。

    状态类保持 ``self.ctx.动作()`` / ``self.ctx.battery.charging`` 的直观写法，不感知 IO。
    """

    def __init__(
        self,
        clock: Callable[[], float] = time.monotonic,
        executor: Optional[object] = None,
        state: Optional[object] = None,
    ) -> None:
        self._clock = clock
        self._executor = executor
        if state is not None:
            # 复用 RobotState 上的同一份流程数据块（硬件上报 ↔ 状态机共享）
            self.command = state.command
            self.inspection = state.inspection
            self.switch_floor = state.switch_floor
            self.charge = state.charge
            self.battery = state.battery
            self.nudge = state.nudge
        else:
            self.command = CommandData()
            self.inspection = InspectionData()
            self.switch_floor = SwitchFloorData()
            self.charge = ChargeData()
            self.battery = BatteryData()
            self.nudge = NudgeData()
        self.calls: list[str] = []  # 未接 executor 时记录动作调用，便于调试/测试

    # ---- 委托机制 ----
    def _do(self, name: str, *args) -> None:
        """动作类方法：executor 有实现则调用，否则仅记录（不阻塞状态机）。"""
        fn = getattr(self._executor, name, None)
        if callable(fn):
            fn(*args)
            return
        self.calls.append(name)
        logger.debug("[robot-ctx] (stub 动作) %s %s", name, args)

    def _ask(self, name: str, default: bool, *args) -> bool:
        """检查类方法：executor 有实现则返回其布尔结果，否则回退默认桩。"""
        fn = getattr(self._executor, name, None)
        if callable(fn):
            try:
                return bool(fn(*args))
            except Exception:
                logger.exception("[robot-ctx] 检查 %s 异常，回退默认 %s", name, default)
        return default

    # ---- 主机相关 ----
    def 检查未完成的任务(self) -> bool:
        return self._ask("检查未完成的任务", False)

    def 手控超时(self) -> bool:
        # 纯流程判定（时钟 + 最后手控时间戳），保留在上下文，不依赖 executor
        ts = self.command.last_manual_ts
        if ts is None:
            return False
        return self._clock() - ts >= MANUAL_IDLE_SECONDS

    # ---- 充电：动作 ----
    def 移动到最近的充电桩(self) -> None:
        self._do("移动到最近的充电桩")

    def 继续前进(self, distance) -> None:
        self._do("继续前进", distance)

    def 设置速度(self, x, y) -> None:
        self._do("设置速度", x, y)

    def stopRobot(self) -> None:
        self._do("stopRobot")

    # ---- 充电：检查 ----
    def 是否在充电桩里(self) -> bool:
        return self._ask("是否在充电桩里", False)

    def 是否最近触发了充电桩rfid(self) -> bool:
        return self._ask("是否最近触发了充电桩rfid", False)

    def 视觉检测轨道对接(self) -> bool:
        return self._ask("视觉检测轨道对接", True)

    # ---- 切楼层 ----
    def 切楼层(self) -> None:
        self._do("切楼层")

    def 移动机器人到0点(self) -> bool:
        return self._ask("移动机器人到0点", True)

    def 移动机器人到1号卡(self) -> None:
        self._do("移动机器人到1号卡")

    def 检查机器人到位(self, x=None) -> bool:
        return self._ask("检查机器人到位", True, x)

    def 检查机器人到达1号卡(self, x=None) -> bool:
        return self._ask("检查机器人到达1号卡", True, x)

    def 检查机器人到轿厢(self, x=None) -> bool:
        return self._ask("检查机器人到轿厢", True, x)

    def 检查在1号卡前(self) -> bool:
        return self._ask("检查在1号卡前", False)

    def 检查在轿厢里(self) -> bool:
        return self._ask("检查在轿厢里", False)

    def 检查机器人在1号卡(self) -> bool:
        """[迁移补全] 旧 sm.py 出轿厢阶段调用了此函数但从未定义，默认桩为未到。"""
        return self._ask("检查机器人在1号卡", False)

    # ---- 巡检 ----
    def 检查下一个航点(self) -> bool:
        return self._ask("检查下一个航点", False)

    def 检查下一个动作(self) -> bool:
        return self._ask("检查下一个动作", False)

    def 移动机器人到当前航点(self) -> None:
        self._do("移动机器人到当前航点")

    def 调整云台位姿(self) -> None:
        self._do("调整云台位姿")

    def 检查云台位姿到位(self) -> bool:
        return self._ask("检查云台位姿到位", True)

    def 执行动作(self) -> None:
        """执行当前动作点动作。

        旧 sm.py 此处为 ``await 执行动作()``。同步内核下：桩实现立即返回；真机实现应投递异步
        任务，任务完成后由宿主 ``machine.send('动作完成')``，状态停在 ExecAction 等待该事件。
        """
        self._do("执行动作")

    def 拍照(self) -> bool:
        return self._ask("拍照", False)

    def 全屏测温(self) -> bool:
        return self._ask("全屏测温", False)


# 向后兼容别名（测试/离线推演可直接用 RobotCtx）
RobotCtx = RobotSmContext


# =========================================================================== #
# 状态基类：周期事件（tick*）默认由本机消化，不跨机冒泡到主机
# =========================================================================== #
class RobotStateBase(State):
    def handle(self, event: str, *args) -> bool:
        if event.startswith("tick"):
            return self.on_tick(event)
        return False

    def on_tick(self, event: str) -> bool:
        """重写以响应周期事件；默认消费、不迁移。"""
        return True


# =========================================================================== #
# 充电子机
# =========================================================================== #
class ChargeMachine(StateMachine):
    class Start(RobotStateBase):
        name = "start"

        def enter(self):
            self.ctx.移动到最近的充电桩()
            self.goto(ChargeMachine.Moving)

    class Moving(RobotStateBase):
        name = "移动中"

        def handle(self, event, *a):
            if event == "到达目标位置":
                self.goto(ChargeMachine.Align)
                return True
            return super().handle(event, *a)

    class Align(RobotStateBase):
        name = "就位优化"

        def enter(self):
            if self.ctx.是否在充电桩里():
                self.goto(ChargeMachine.Nudging)
            else:
                self.ctx.继续前进(300)

        def handle(self, event, *a):
            if event == "到了目标点":
                self.goto(ChargeMachine.Nudging)
                return True
            if event == "tick10" and self.ctx.是否最近触发了充电桩rfid():
                self.goto(ChargeMachine.Nudging)
                return True
            return super().handle(event, *a)

    class Nudging(RobotStateBase):
        name = "充电微挪"

        def enter(self):
            self.ctx.nudge.offset = 0
            self.ctx.nudge.move_dir = 1
            self._step()

        def _check_charging(self) -> bool:
            if self.ctx.battery.charging:
                self.goto(ChargeMachine.Charging)
                return True
            return False

        def _step(self) -> None:
            n = self.ctx.nudge
            n.offset += n.move_dir
            if n.offset >= NUDGE_RANGE:
                n.move_dir = -1
            if n.offset < -NUDGE_RANGE:
                # 扫完整个行程仍未充上：停一会再重新扫
                self.clear_timeout("nudge_tick")
                self.arm_timeout("nudge_restart", NUDGE_RESWEEP_SECONDS)
                return
            self.ctx.设置速度(n.move_dir * 1, 2)
            self.arm_timeout("nudge_tick", NUDGE_STEP_SECONDS)

        def handle(self, event, *a):
            if event == "nudge_tick":       # 旧"微挪时间到"：停一下，稍后挪下一步
                self.ctx.stopRobot()
                self.arm_timeout("nudge_step", NUDGE_STEP_SECONDS)
                return self._check_charging() or True
            if event == "nudge_step":       # 旧"微挪开始"：挪一步
                self._step()
                return self._check_charging() or True
            if event == "nudge_restart":    # 60s 后重新扫描
                self.enter()
                return True
            if event == "tick10":
                return self._check_charging() or True
            return super().handle(event, *a)

    class Charging(RobotStateBase):
        name = "充电中"

        def handle(self, event, *a):
            if event == "充电一直丢失":
                self.goto(ChargeMachine.Nudging)
                return True
            if event == "充电到阈值":
                self.complete()
                return True
            return super().handle(event, *a)

    initial_state = Start


# =========================================================================== #
# 切楼层子机（旧草稿无主机激活入口，完整保留待挂载）
# =========================================================================== #
class FloorMachine(StateMachine):
    class Start(RobotStateBase):
        name = "start"

        def enter(self):
            # [迁移补全] 旧草稿此处目标为空状态名；按当前所在位置快捷进入对应阶段
            if self.ctx.检查在1号卡前():
                self.goto(FloorMachine.SafetyCheckEnter)
            elif self.ctx.检查在轿厢里():
                self.goto(FloorMachine.InCage)
            else:
                self.goto(FloorMachine.ToCage)

    class ToCage(RobotStateBase):
        name = "到轿厢前"

        def enter(self):
            self.ctx.移动机器人到1号卡()

        def handle(self, event, *a):
            if event == "机器人到位":
                self.goto(FloorMachine.SafetyCheckEnter)
                return True
            return super().handle(event, *a)

    class SafetyCheckEnter(RobotStateBase):
        name = "进轿厢的安全检测"

        def handle(self, event, *a):
            if event == "tick60" and self.ctx.视觉检测轨道对接():
                self.goto(FloorMachine.InCage)
                return True
            return super().handle(event, *a)

    class InCage(RobotStateBase):
        name = "进轿厢"

        def enter(self):
            self.ctx.移动机器人到0点()

        def handle(self, event, *a):
            if event == "tick30" and self.ctx.检查机器人到轿厢():
                self.goto(FloorMachine.Switching)
                return True
            return super().handle(event, *a)

    class Switching(RobotStateBase):
        name = "切楼层"

        def enter(self):
            self.ctx.切楼层()

        def handle(self, event, *a):
            if event == "楼层到位":
                if self.ctx.switch_floor.flag_go_out:
                    self.goto(FloorMachine.SafetyCheckExit)
                else:
                    self.goto(FloorMachine.FloorDone)
                return True
            return super().handle(event, *a)

    class SafetyCheckExit(RobotStateBase):
        name = "出轿厢的安全检测"

        def handle(self, event, *a):
            if event == "tick60" and self.ctx.视觉检测轨道对接():
                self.goto(FloorMachine.ExitCage)
                return True
            return super().handle(event, *a)

    class ExitCage(RobotStateBase):
        name = "出轿厢"

        def enter(self):
            self.ctx.移动机器人到1号卡()

        def handle(self, event, *a):
            if event == "tick10" and self.ctx.检查机器人在1号卡():
                self.goto(FloorMachine.ExitDone)
                return True
            return super().handle(event, *a)

    class ExitDone(RobotStateBase):
        name = "出轿厢完成"

        def enter(self):
            self.goto(FloorMachine.FloorDone)

    class FloorDone(RobotStateBase):
        name = "切换楼层完成"

        def enter(self):
            self.complete()

    initial_state = Start


# =========================================================================== #
# 巡检子机
# =========================================================================== #
class InspectionMachine(StateMachine):
    class WaypointStart(RobotStateBase):
        name = "航点开始"

        def enter(self):
            if self.ctx.检查下一个航点():
                self.goto(InspectionMachine.MovingToWaypoint)
            else:
                self.goto(InspectionMachine.InspDone)

    class MovingToWaypoint(RobotStateBase):
        name = "移动到航点"

        def enter(self):
            self.ctx.移动机器人到当前航点()

        def handle(self, event, *a):
            if event == "已到达当前航点":
                self.goto(InspectionMachine.ActionPointStart)
                return True
            return super().handle(event, *a)

    class ActionPointStart(RobotStateBase):
        name = "动作点开始"

        def enter(self):
            if self.ctx.检查下一个动作():
                self.goto(InspectionMachine.AdjustPtz)
            else:
                self.goto(InspectionMachine.WaypointStart)

    class AdjustPtz(RobotStateBase):
        name = "调整云台位姿"

        def enter(self):
            self.ctx.调整云台位姿()

        def handle(self, event, *a):
            if event == "tick10" and self.ctx.检查云台位姿到位():
                self.goto(InspectionMachine.ExecAction)
                return True
            return super().handle(event, *a)

    class ExecAction(RobotStateBase):
        name = "执行动作"

        def enter(self):
            self.ctx.执行动作()
            # 桩默认动作立即完成；真机若动作异步，应改为停在此状态等 '动作完成' 事件
            self.goto(InspectionMachine.ActionDone)

    class ActionDone(RobotStateBase):
        name = "动作完成"

        def enter(self):
            self.goto(InspectionMachine.ActionPointStart)

    class InspDone(RobotStateBase):
        name = "巡检完成"

        def enter(self):
            self.complete()

    initial_state = WaypointStart


# =========================================================================== #
# 主机
# =========================================================================== #
class MainMachine(StateMachine):
    class Boot(RobotStateBase):
        name = "启动"

        def enter(self):
            if self.ctx.检查未完成的任务():
                self.goto(MainMachine.Inspecting)
            else:
                self.goto(MainMachine.Idle)

    class Idle(RobotStateBase):
        name = "空闲"

        def handle(self, event, *a):
            if event in ("电量不足", "长期不动"):
                self.goto(MainMachine.GotoCharge)
                return True
            if event == "进入手控模式":
                self.goto(MainMachine.Manual)
                return True
            if event == "收到巡检":
                self.goto(MainMachine.Inspecting)
                return True
            return super().handle(event, *a)

    class Manual(RobotStateBase):
        name = "手控模式"

        def handle(self, event, *a):
            if event == "tick10" and self.ctx.手控超时():
                self.goto(MainMachine.Idle)
                return True
            return super().handle(event, *a)

    class Inspecting(RobotStateBase):
        name = "巡检中"

        def enter(self):
            child = InspectionMachine(
                ctx=self.ctx, clock=self.machine.clock, intervals=TICK_INTERVALS
            )
            self.activate(child, on_complete=lambda r: self.goto(MainMachine.Idle))

    class GotoCharge(RobotStateBase):
        name = "去充电"

        def enter(self):
            child = ChargeMachine(
                ctx=self.ctx, clock=self.machine.clock, intervals=TICK_INTERVALS
            )
            self.activate(child, on_complete=lambda r: self.goto(MainMachine.Idle))

    initial_state = Boot


# =========================================================================== #
# 组装
# =========================================================================== #
def build_robot_sm(
    ctx: Optional[RobotSmContext] = None,
    clock: Callable[[], float] = time.monotonic,
) -> MainMachine:
    """构建机器人根状态机（主机）。子机在进入对应父状态时按需创建。"""
    if ctx is None:
        ctx = RobotSmContext(clock=clock)
    return MainMachine(ctx=ctx, clock=clock, intervals=TICK_INTERVALS, name="main")
