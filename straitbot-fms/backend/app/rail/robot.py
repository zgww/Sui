"""Robot：一台挂轨机器人的运行时编排根对象。

行为调度采用 sm.py 的 **if/else 式状态机**（字符串状态 + 每节拍 beh 轮询），不是状态类层次。
组合关系::

    Robot
    ├── config      RobotConfig prefab 节点（id/name/version/ip/port/type，来自 robot.prefab.json）
    ├── prefab_root 该机器人的 prefab 配置节点树（未来在其下挂规则链/定时任务）
    ├── board       BoardSrv（控制板消息服务，连接层内部管理，外部只传 ip/port）
    ├── state       RobotState —— 运行时状态（硬件上报缓存 + 状态块），实例化属性
    └── sm          RobotSm —— 4 个 Sm（main/charge/floor/insp）+ beh_* if/else 行为

节拍（Robot._tick_loop 每秒驱动）：先跑各机 ``beh_*``（读 st/signal 决策、调 Robot 成员动作），
再 ``Sm.tick()``（消费动作队列、产生周期/超时信号）。

数据流：
    控制板上报 → BoardSrv 订阅回调 → 更新 RobotState / 向对应 Sm emit 事件
    状态机动作 → Robot 的中文成员函数 → BoardSrv 下发

已接真机 / 仍是桩
------------------
- 已接：底盘上报与到位事件、电源/充电上报（contact、charge_state、充电完成）、RFID 进入、
  速度/停止/前进/回零指令、**巡检航点走行**（复用 goto + 0x0B 到位事件驱动
  "移动到航点 → 动作点开始 → 下一航点" 闭环）、**巡检伸缩杆升降**（0x0C 指定坐标 +
  0x0E 到位事件，按动作 ``lift_height`` 摆位后再执行动作）、**巡检断点续跑**（进度落盘，
  开机从断点航点恢复）、**设备无进展看门狗**（走行/升降无进展则重发指令，重试耗尽中止巡检
  并保留断点，不再无限占用 busy）。
- 桩（与旧 sm.py 默认值一致，标 ``[TODO-…]``）：依赖导航层（去桩/卡/切楼层目标坐标）、
  任务层（跨楼层切换）、视觉/云台层（对接检测、云台、拍照、测温）的函数。

注意：拍照/测温走机器人本体 HTTP API（``app/services/robot_api.py`` 的 cmd 编号，与
``app/routers/control.py``、``calibration.py`` 同源），是**阻塞式同步调用**。这里就让它
**占住状态机那一拍**——"执行动作"本来就是个等结果的状态，起后台线程反而要额外准备代际
校验、超时兜底、结果回投三套机制（见 :meth:`Robot._run_vision`）。云台定位同理是同步
调用，但仍放在线程里（见 :meth:`Robot.调整云台位姿`）：它要等电机走到位，期间状态机还得
继续收 0x0B 底盘上报。
"""
from __future__ import annotations

import asyncio
import json
import logging
import threading
import time
from dataclasses import dataclass, field
from datetime import datetime, timezone
from pathlib import Path
from typing import Callable, Optional

from . import messages
from .client import ConnStatus, ConnectionError2
from .inspection import (
    DETECT_TYPE_PLATFORM,
    InspectionTask,
)
from .recorder import STATUS_FAILED, STATUS_OK, STATUS_SKIPPED
from .services.board import BoardSrv
from .sm import Sm
from .vision import HkPtzVision, VisionResult
from ..config import DATA_DIR

logger = logging.getLogger("rail.robot")

# 状态机节拍（秒）。Sm 内部另有 tick10/30/60/300 周期。
SM_TICK_SECONDS = 0.1
# 手控模式超时：20 分钟无手控指令回空闲
MANUAL_IDLE_SECONDS = 20 * 60
# RFID 进入事件在多少秒内视为"最近触发"（充电就位判定）
RFID_FRESH_SECONDS = 5.0
# 0x01 初始化控制板的等待响应超时（秒）。连接刚建立，下位机在忙的时候应答会明显延迟
# （实测 0x01 与 0x06 的应答会延后到 6s 左右成批回来），给足窗口，别误报失败。
INIT_REQUEST_TIMEOUT = 5.0
# 电源 charge_state 枚举（messages/power.py）
CHARGE_STATE_CHARGING = 5
CHARGE_STATE_DONE = 6

# 巡检断点文件名后缀（与 {inspection_id}.json 任务记录同目录）。断点存在即"巡检未完成"，
# 开机由 检查未完成的任务() 恢复；巡检完成时删除。
INSPECTION_PROGRESS_SUFFIX = ".progress.json"

# =========================================================================== #
# 单位换算：下位机协议为 int、工程怪单位；上位机状态/接口统一用标准单位（float）。
# 消息类（messages/*）仍代表线上字节、保持协议原值与原单位，换算只在 Robot 边界做。
# =========================================================================== #
# 长度 / 速度 / 角度（底盘、RFID、目标位置）
MM_TO_M = 0.001                  # mm -> m
M_TO_MM = 1000.0                 # m -> mm
MMPS_TO_MPS = 0.001             # mm/s -> m/s
MPS_TO_MMPS = 1000.0            # m/s -> mm/s
DEG10_TO_DEG = 0.1              # 偏航角 raw*10（0.1°）-> 度
DEG_TO_DEG10 = 10.0             # 度 -> raw*10
DPS10_TO_DPS = 0.1              # 角速度 raw*10（0.1°/s）-> 度/s
DPS_TO_DPS10 = 10.0            # 度/s -> raw*10

# 电源 0x16 PowerResponse：电压10mV、电流10mA(正充负放)、容量10mAh、温度0.1℃
P16_VOLTAGE_SCALE = 0.01        # -> V
P16_CURRENT_SCALE = 0.01        # -> A
P16_CAPACITY_SCALE = 0.01       # -> Ah
P16_TEMP_SCALE = 0.1            # -> ℃
# 电源 0x17 ChargeStateUpload。
# ⚠️ 文档里 0x17 那行单位写的是 mV/mA/mAh/℃，比 0x16 小 10 倍；但**真机不是这样**：
# 2026-09-24 实测 0x17 payload `5f 0b22 ff77 070a 0145 00 00`
#   → 电压 2850、电流 -137、容量 1802、温度 325、电量 95%
# 按文档口径会得到 2.85V / 1.8Ah / 325℃（明显荒谬），按 0x16 口径才是
# 28.5V / 18.02Ah / 32.5℃ —— 四个量同时合理。所以 0x17 与 0x16 单位一致。
# （文档自身也写「0x17 充电状态…参照 0x16 协议」，且变更记录里有"修改 0x17 协议"。）
P17_VOLTAGE_SCALE = P16_VOLTAGE_SCALE      # -> V（原始 10mV）
P17_CURRENT_SCALE = P16_CURRENT_SCALE      # -> A（原始 10mA）
P17_CAPACITY_SCALE = P16_CAPACITY_SCALE    # -> Ah（原始 10mAh）
P17_TEMP_SCALE = P16_TEMP_SCALE            # -> ℃（原始 0.1℃）

# 充电微挪点动速度（m/s）。等价旧草稿 raw 1 mm/s，现场可调。[TODO-调参]
NUDGE_SPEED_MPS = 0.001
# 手动点动（向前/向后）默认速度，m/s。现场可调。[TODO-调参]
DEFAULT_JOG_SPEED_MPS = 0.3
# 巡检航点到位判定容差（m）。正常到位由 0x0B ARRIVED 上升沿驱动；此容差用于
# "目标与当前位置重合"（相邻航点同一 X，控制板不再产生上升沿）的兜底判定。
INSP_ARRIVE_TOL_M = 0.02

# 设备无进展看门狗：到位不能无限等。控制板失联/机构卡住时"移动到航点"或"调整升降杆"
# 永远等不到到位事件，busy 会一直成立、后续任务持续被 409 拒绝，只能重启。
# 以"无进展"（窗口内位置几乎不动）而非绝对超时判定——长距离慢速走行不会被误判。
# 注意窗口必须明显大于设备状态上发周期（0x0B/0x0E，真机通常 ≤1s，仿真 0.1s），
# 否则位置本来就"还没更新"会被当成无进展。现场按实际上发周期调大。
DEVICE_STALL_SEC = 60.0             # 无进展判定窗口，s
DEVICE_PROGRESS_EPS_M = 0.005       # 视为"有进展"的最小位移，m
DEVICE_MAX_RETRY = 2                # 重发指令次数上限，耗尽则中止本次巡检

# 伸缩杆（升降）电机 ID **默认值**：挂轨约定 1=伸缩杆（见 messages/motor_ctrl.py）。
# 真机若用别的 ID，改 prefab 的 `RobotConfig.lift_motor_id`，别改这里。
LIFT_MOTOR_ID = 1
# 升降到位容差（m）
LIFT_ARRIVE_TOL_M = 0.01

# 云台绝对定位（HTTP ISAPI，见 HkPtz.absolute_move）：定位在后台线程里跑，用的是
# **真实墙钟**（time.monotonic / time.sleep），与注入的状态机时钟无关——真机走完一次
# 绝对定位约 2s，节拍线程不能阻塞等它。到位判定按各轴容差比对 ptz_status 回读。
PTZ_POLL_INTERVAL_SEC = 0.3         # 到位轮询间隔，s
PTZ_SETTLE_TIMEOUT_SEC = 15.0       # 单次定位最长等待，s（超时也放行，不阻断巡检）
PTZ_PAN_TOL_DEG = 1.0               # 水平角到位容差，°
PTZ_TILT_TOL_DEG = 1.0              # 俯仰角到位容差，°
PTZ_ZOOM_TOL = 0.3                  # 变倍到位容差（倍率；设备回读有取整误差）

# 巡检动作类型（与下发任务 action[].type 一致；见 app/rail/inspection.py）
ACTION_TYPE_PHOTO = 1        # 可见光拍照
ACTION_TYPE_THERMOMETRY = 2  # 全屏测温（红外热像）
ACTION_TYPE_VIDEO = 3        # 录像（带 duration）


# =========================================================================== #
# 状态块（对应旧 sm.py 的 CommandState/InspState/...）
# =========================================================================== #
@dataclass
class StallWatch:
    """无进展看门狗（底盘走行 / 伸缩杆升降共用）。

    以"位置在窗口内几乎不动"判定卡住，而不是"动作超过 N 秒"——慢速但持续的运动不会误判，
    而设备失联（状态停更、位置冻住）或机构卡死都能抓到。

    生命周期：``arm()`` 开始一次动作 → 每次判定调 ``stalled()`` → ``clear()`` 收尾。
    ``retry`` 属于"本次动作"，由调用方在开始新动作时归零（``clear()`` 已含）。
    """

    last_value: Optional[float] = None
    last_progress_at: Optional[float] = None
    retry: int = 0

    def arm(self, value: float, now: float) -> None:
        """武装/重新武装：记录基线值并开始计时（重发指令后也调它）。"""
        self.last_value = float(value)
        self.last_progress_at = now

    def clear(self) -> None:
        """清空（未武装）：任务装载/恢复/结束/中止时调用。"""
        self.last_value = None
        self.last_progress_at = None
        self.retry = 0

    def stalled(self, value: float, now: float, window: float, eps: float) -> bool:
        """窗口内位移小于 ``eps`` 即认为卡住。未武装时恒为 False。"""
        if self.last_progress_at is None:
            return False
        v = float(value)
        if self.last_value is None or abs(v - self.last_value) >= eps:
            # 有进展：刷新基线，窗口重新计时
            self.last_value = v
            self.last_progress_at = now
            return False
        return now - self.last_progress_at >= window


@dataclass
class LiftState:
    """伸缩杆（升降）状态，来自 0x0E 电机状态上发（ID 见 prefab `lift_motor_id`）。

    仅建模巡检需要的部分：到位状态与当前高度；驱动电流/温度等原样缓存备查。
    """

    motor_id: int = LIFT_MOTOR_ID
    state: int = messages.MOTOR_ST_IDLE      # 0空闲 1运行 2已到位 3初始化
    coord_m: float = 0.0                     # 当前高度，m
    speed: int = 0                           # 当前速度，mm/s
    status_word: int = 0
    driver_error: int = 0
    temperature: int = 0
    updated_at: float = 0.0                  # 最近一次收到上发的时刻
    target_m: Optional[float] = None         # 最近一次下发的目标高度（None=未下发）


@dataclass
class CommandState:
    last_manual_ts: Optional[float] = None      # 最后手控指令时间


@dataclass
class InspState:
    current_inspection_id: Optional[str] = None
    current_waypoint_id: Optional[str] = None
    current_action_index: int = 0
    # —— 本次巡检的动作数据怎么作用到检测（"fms" 本地消化 / "platform" 上传平台）——
    #  缺省 platform = 旧版行为；动作执行侧据此决定动作数据往哪送
    detect_type: str = DETECT_TYPE_PLATFORM
    # —— 巡检任务游标（任务装载后由"检查下一个航点/动作"推进）——
    current_floor: Optional[int] = None       # 当前航点所属楼层
    waypoint_cursor: int = 0                  # 扁平航点序列中"下一个待取"下标
    action_cursor: int = 0                    # 当前航点内"下一个待取"动作下标
    current_action_id: Optional[str] = None
    current_action_type: Optional[int] = None
    target_x_m: Optional[float] = None        # 当前航点目标弧长，m（下一轮导航用）
    arrive_handled: bool = False              # 本次走行到位是否已处理（防重复迁移）
    # —— 当前动作要求的升降高度与到位闩锁 ——
    target_lift_m: Optional[float] = None     # 当前动作要求高度，m（0=不升降）
    lift_handled: bool = False                # 升降到位是否已处理（防重复迁移）
    # —— 当前动作要求的云台绝对位姿与到位闩锁（后台线程定位，见 调整云台位姿）——
    target_ptz: Optional[dict] = None         # {"pan","tilt","zoom"}；None=本动作无云台要求
    ptz_busy: bool = False                    # 云台定位线程进行中
    ptz_done: bool = False                    # 云台已到位/无需/失败放行（检查云台位姿到位 据此迁移）
    ptz_error: Optional[str] = None           # 最近一次云台定位异常信息（失败也放行，仅记录）
    # —— 中止原因（看门狗判定失败时写入，"巡检中止"状态据此记录）——
    abort_reason: Optional[str] = None        # "move_stalled" / "lift_stalled"
    # —— 设备无进展看门狗 ——
    move_watch: StallWatch = field(default_factory=StallWatch)   # 底盘走行
    lift_watch: StallWatch = field(default_factory=StallWatch)   # 伸缩杆升降
    # —— 当前视觉动作（拍照/全屏测温）—— 同步跑在状态机线程里，见 _run_vision
    vision_kind: Optional[str] = None        # "visible" / "thermometry" / "video"
    # 同步执行后恒 False：视觉在"执行动作"那一拍里跑完，不存在进行中的中间态。
    # 字段留着是为了状态接口（routers/rail_robot.py）的键不变化
    vision_busy: bool = False
    vision_done: bool = False                # 动作完成（成功或失败放行；检查动作完成 据此迁移）
    vision_error: Optional[str] = None       # 最近一次视觉异常（失败也放行，仅记录）
    vision_result: Optional[dict] = None     # 最近一次结果（图片路径/测温数据）
    vision_handled: bool = False             # 完成迁移闩锁：保证"执行动作→动作完成"只迁移一次


@dataclass
class SwitchFloorState:
    flag_go_out: bool = False                   # 切楼层后是否需要出轿厢


@dataclass
class ChargeState:
    flag_go_out: bool = False


@dataclass
class Pose:
    """底盘位姿与速度（0x0A/0x0B），上位机标准单位、浮点。

    协议为 int：x/y 与 target 用 mm，linear_* 用 mm/s，yaw/angular 为 ×10（0.1°、0.1°/s），
    在 Robot 上报/下发边界换算。
    """
    x: float = 0.0          # 位置 X（挂轨为弧长），m
    y: float = 0.0          # 位置 Y（轮式），m
    yaw: float = 0.0        # 偏航角，度（°）
    linear_x: float = 0.0   # 线速度 X，m/s
    linear_y: float = 0.0   # 线速度 Y（轮式），m/s
    angular: float = 0.0    # 角速度，度/s（°/s）


@dataclass
class BatteryState:
    """电源/电池与充电对接状态（0x16/0x17 上报），充电判定由字段派生。

    物理量统一用浮点（协议层为整数，写入时按工程量转换）；contact/charge_state
    是状态枚举，保持整数。
    """
    battery_percent: float = 0.0  # 电量百分比，%（0-100）
    voltage: float = 0.0          # 电压，V
    current: float = 0.0          # 电流，A（正充负放）
    capacity: float = 0.0         # 额定容量，Ah
    temperature: float = 0.0      # 电池温度，℃
    contact: int = 0        # 0 未对接 1 已对接
    charge_state: int = 0   # 0未启动 1前往中 2未找到信号 3已收到信号 4异常 5充电中 6完成

    @property
    def contacted(self) -> bool:
        return self.contact == 1

    @property
    def charging(self) -> bool:
        return self.charge_state == CHARGE_STATE_CHARGING


@dataclass
class RfidState:
    """最近一次 RFID 进入事件（0x30 进入 / 0x29 查询）。

    rfid 为卡号（协议 uint16，整数；0 表示尚未触发）；
    x 为沿轨位置（弧长），m（协议 int32 mm，写入时换算）。
    """
    rfid: int = 0
    x: float = 0.0         # 标签位置（弧长），m（协议为 mm）
    ts: float = 0.0        # 进入时刻（clock 秒）


@dataclass
class ChargeSlightMoveState:
    offset: int = 0                             # 充电微挪行程
    move_dir: int = 1


@dataclass
class RobotState:
    """机器人运行时状态：状态机状态块 + 硬件上报缓存。"""

    # ---- 状态机状态块 ----
    command: CommandState = field(default_factory=CommandState)
    insp: InspState = field(default_factory=InspState)
    switch_floor: SwitchFloorState = field(default_factory=SwitchFloorState)
    charge: ChargeState = field(default_factory=ChargeState)
    battery: BatteryState = field(default_factory=BatteryState)
    nudge: ChargeSlightMoveState = field(default_factory=ChargeSlightMoveState)

    # ---- 连接 / 版本 ----
    online: bool = False
    board_status: str = "idle"
    firmware_version: str = ""

    # ---- 控制板初始化（0x01，连接建立/重连后自动下发）----
    board_init_ok: bool = False     # 最近一次 0x01 是否成功（错误码 0）
    board_init_error: str = ""      # 最近一次失败原因（超时/未连接/错误码）
    board_init_at: float = 0.0      # 最近一次 0x01 成功时间（time.monotonic）

    # ---- 底盘运行状态（机台状态；位姿/速度见 pose）----
    chassis_state: int = messages.CHASSIS_IDLE
    chassis_mode: int = messages.MODE_EMBEDDED
    pose: Pose = field(default_factory=Pose)

    # ---- RFID（最近一次进入事件；电源/充电状态见 battery）----
    rfid: RfidState = field(default_factory=RfidState)

    # ---- 伸缩杆（升降）状态（0x0E 电机状态上发）----
    lift: LiftState = field(default_factory=LiftState)


# =========================================================================== #
# RobotSm：4 个 Sm + if/else 行为（忠实迁移旧 sm.py 的 behMain/Charge/Floor/Insp）
# =========================================================================== #
class RobotSm:
    def __init__(self, robot: "Robot", clock: Callable[[], float] = time.monotonic) -> None:
        self.robot = robot
        self.state = robot.state
        self._clock = clock

        self.main = Sm("main", initSt="启动", clock=clock)
        self.charge = Sm("charge", initSt="start", clock=clock)
        self.floor = Sm("floor", initSt="start", clock=clock)
        self.insp = Sm("insp", initSt="start", clock=clock)
        self.sms = [self.main, self.charge, self.floor, self.insp]

    # ------------------------------------------------------------ 生命周期
    def start(self, now: Optional[float] = None) -> None:
        self.charge.stop()
        self.floor.stop()
        self.insp.stop()
        self.main.start(now)

    def stop(self) -> None:
        for sm in self.sms:
            sm.stop()

    def tick(self, now: Optional[float] = None) -> None:
        """一个节拍：先 beh 决策，再各活动机 tick。"""
        if not self.main.active:
            return
        self._beh_main()
        self._beh_charge()
        self._beh_floor()
        self._beh_insp()
        for sm in self.sms:
            if sm.active:
                sm.tick(now)

    # ------------------------------------------------------------ 事件入口
    def send(self, event: str, target: str = "main") -> None:
        """向指定机投递一个事件信号；目标机未激活则丢弃（避免堆积）。"""
        sm = {"main": self.main, "charge": self.charge,
              "floor": self.floor, "insp": self.insp}.get(target, self.main)
        if not sm.active:
            logger.debug("[sm] 丢弃事件 %r -> %s（未激活）", event, sm.name)
            return
        sm.emit(event)

    def active_child(self) -> Optional[str]:
        for name in ("insp", "charge", "floor"):
            if getattr(self, name).active:
                return name
        return None

    # ------------------------------------------------------------ 观测
    def current_state(self) -> Optional[str]:
        return self.main.st

    def leaf_state(self) -> Optional[str]:
        child = self.active_child()
        return getattr(self, child).st if child else self.main.st

    def state_path(self) -> list[str]:
        path = [f"main:{self.main.st}"] if self.main.active else ["main:None"]
        for name in ("charge", "floor", "insp"):
            sm = getattr(self, name)
            if sm.active:
                path.append(f"{sm.name}:{sm.st}")
        return path

    @property
    def running(self) -> bool:
        return self.main.active

    # ============================================================== #
    # 主机（旧 behMain）
    # ============================================================== #
    def _beh_main(self) -> None:
        sm = self.main
        r = self.robot
        st, sig = sm.st, sm.signal

        if st == "启动":
            if r.检查未完成的任务():
                sm.setState("巡检中")
            else:
                sm.setState("空闲")

        if st == "空闲":
            sm.signalMove("电量不足", "去充电")
            sm.signalMove("长期不动", "去充电")
            sm.signalMove("手动回充", "去充电")
            sm.signalMove("进入手控模式", "手控模式")
            sm.signalMove("收到巡检", "巡检中")

        if st == "巡检中":
            # [修正] 只在进入"巡检中"的 enter 拍激活一次巡检子机；旧草稿每拍 signalMove
            # 会在子机 stop 后、主机尚未离开的窗口里把它重新激活
            if sig == "enter":
                self.insp.start()
            # 手动回充：先中止巡检（停车、保留断点、释放 busy）再回桩
            if sig == "手动回充":
                self.中止当前巡检()
                self.insp.stop()
            sm.signalMove("巡检完成", "去充电")
            # 走行看门狗中止（子机停车并保留断点）：主机同样要退出"巡检中"释放 busy，
            # 否则后续任务会一直被 409 拒绝
            sm.signalMove("巡检中止", "空闲")
            # 手动取消巡检：用户从页面点"取消巡检"，主机退出巡检中
            sm.signalMove("取消巡检", "空闲")
            sm.signalMove("手动回充", "去充电")

        if st == "手控模式":
            sm.signalMove("手动回充", "去充电")
            if r.手控超时():
                sm.setState("空闲")

        if st == "去充电":
            if sig == "enter":
                self.charge.start()
            sm.signalMove("充电到阈值", "空闲")

    # ============================================================== #
    # 充电子机（旧 behCharge）
    # ============================================================== #
    def _beh_charge(self) -> None:
        sm = self.charge
        if not sm.active:
            return
        r = self.robot
        st, sig = sm.st, sm.signal

        if st == "start":
            if sig == "enter":
                r.移动到最近的充电桩()
                sm.setState("移动中")

        if st == "移动中":
            if sig == "到达目标位置":
                sm.setState("到位检查是否充电中")

        if st == "到位检查是否充电中":
            if sig == "tick30": # 等待30秒，检查是否在充电中了
                if self.state.battery.charging:
                    sm.setState("充电中")
                else:
                    sm.setState("就位优化")

        if st == "就位优化":
            if sig == "enter":
                if r.是否在充电桩里():
                    sm.setState("充电微挪")
                else:
                    r.继续前进(0.3)   # 300 mm = 0.3 m
            # [修正] 旧草稿仅 sig is None 才查 rfid，会漏掉 tick10 拍；两者都查
            if (sig is None or sig == "tick10") and r.是否最近触发了充电桩rfid():
                sm.setState("充电微挪")
            if sig == "到了目标点":
                sm.setState("充电微挪")

        if st == "充电微挪":
            if sig == "enter":
                # [修正] 旧草稿 setState('微挪开始') 会进入一个不存在的状态导致卡死；
                # 微挪开始/微挪时间到应是定时信号，状态始终停留在"充电微挪"
                self.state.nudge = ChargeSlightMoveState()
                sm.emit("微挪开始")
            if sig == "微挪开始":
                if self._nudge_step(sm) == "end":
                    # 扫完整个行程仍未充上：重置行程，60s 后重新扫
                    self.state.nudge = ChargeSlightMoveState()
                    sm.setTimeout(60, "微挪开始")
            if sig == "微挪时间到":
                r.stopRobot()
                sm.setTimeout(2, "微挪开始")
            if sig != "exit" and self.state.battery.charging:
                sm.setState("充电中")

        if st == "充电中":
            sm.signalMove("充电一直丢失", "充电微挪")
            if sig == "充电到阈值":
                sm.stop()
                self.main.emit("充电到阈值")   # [补全] 回连主机（旧草稿只 stop 子机）

    def _nudge_step(self, sm: Sm) -> Optional[str]:
        """充电微挪挪一步（旧 充电微挪(sm) 函数）。到行程尽头返回 'end'。"""
        n = self.state.nudge
        n.offset += n.move_dir
        if n.offset >= 10:
            n.move_dir = -1
        if n.offset < -10:
            return "end"
        self.robot.设置速度(n.move_dir * NUDGE_SPEED_MPS)
        sm.setTimeout(2, "微挪时间到")
        return None

    # ============================================================== #
    # 切楼层子机（旧 behFloor）。主机当前无激活入口，完整保留待挂载。
    # ============================================================== #
    def _beh_floor(self) -> None:
        sm = self.floor
        if not sm.active:
            return
        r = self.robot
        st, sig = sm.st, sm.signal

        if st == "start":
            if sig == "enter":
                # [迁移补全] 旧草稿此处 setState('') 为空状态名，按所在位置快捷进入
                if r.检查在1号卡前():
                    sm.setState("进轿厢的安全检测")
                elif r.检查在轿厢里():
                    sm.setState("进轿厢")
                else:
                    sm.setState("到轿厢前")

        if st == "到轿厢前":
            if sig == "enter":
                r.移动机器人到1号卡()
            if sig == "机器人到位":
                sm.setState("进轿厢的安全检测")

        if st == "进轿厢的安全检测":
            if sig == "tick60" and r.视觉检测轨道对接():
                sm.setState("进轿厢")

        if st == "进轿厢":
            if sig == "enter":
                r.移动机器人到0点()
            if sig == "tick30" and r.检查机器人到轿厢():
                sm.setState("切楼层")

        if st == "切楼层":
            if sig == "enter":
                r.切楼层()
            if sig == "楼层到位":
                if self.state.switch_floor.flag_go_out:
                    sm.setState("出轿厢的安全检测")
                else:
                    sm.setState("切换楼层完成")

        if st == "出轿厢的安全检测":
            if sig == "tick60" and r.视觉检测轨道对接():
                sm.setState("出轿厢")

        if st == "出轿厢":
            if sig == "enter":
                r.移动机器人到1号卡()
            if sig is None and r.检查机器人在1号卡():
                sm.setState("出轿厢完成")

        if st == "出轿厢完成":
            if sig == "enter":
                sm.setState("切换楼层完成")

        if st == "切换楼层完成":
            if sig == "enter":
                sm.stop()
                self.main.emit("切换楼层完成")

    # ============================================================== #
    # 巡检子机（旧 behInsp）
    # ============================================================== #
    def _beh_insp(self) -> None:
        sm = self.insp
        if not sm.active:
            return
        r = self.robot
        st, sig = sm.st, sm.signal

        if sig == '取消巡检':
            logger.info(f'收到信号 {sig}')
            r.停止()
            insp = self.state.insp
            insp.abort_reason = "巡检中止"
            sm.setState("巡检中止")
            return

        if st == "start" and sig == "enter":
            # 巡检开始：先把这次巡检的动作/测点结果占位写进 SQLite（幂等），
            # 下游才能边跑边取；占位早于执行，崩了也看得出卡在第几个动作
            r.准备巡检结果占位()
            sm.signalMove("enter", "航点开始")

        if st == "航点开始":
            if sig == "enter":
                if r.检查下一个航点():
                    sm.setState("移动到航点")
                else:
                    sm.setState("巡检完成")

        if st == "移动到航点":
            insp = self.state.insp
            if sig == "enter":
                r.移动机器人到当前航点()
                insp.arrive_handled = False   # 新一次走行，重置到位闩锁
                insp.move_watch.clear()       # 新一次走行，重试计数归零
                r.重置走行看门狗()             # 并武装无进展看门狗

                
            # 到位有两条来源：控制板 0x0B 上升沿事件、以及目标与当前位置重合时的容差兜底。
            # 两者可能在同一两拍过渡窗口内先后命中，闩锁保证只迁移一次——否则会重复入队
            # exit/enter，使每个状态被进入两次、动作游标错位。
            if not insp.arrive_handled and (
                sig == "已到达当前航点"
                or (sig not in ("enter", "exit") and r.检查已到达当前航点())
            ):
                insp.arrive_handled = True
                sm.setState("动作点开始")
            # 到位 watchdog：控制板失联/走行卡住时不能无限等。先重发 goto（可能是指令
            # 丢失或 0x0B 流中断），重试耗尽仍无进展则中止本次巡检、释放 busy。
            elif not insp.arrive_handled and sig not in ("enter", "exit") and r.检查走行卡住():
                if not r.重试走行():
                    insp.abort_reason = "move_stalled"
                    sm.setState("巡检中止")

        if st == "动作点开始":
            if sig == "enter":
                if r.检查下一个动作():
                    sm.setState("调整云台位姿")
                else:
                    sm.setState("航点开始")

        if st == "调整云台位姿":
            if sig == "enter":
                r.调整云台位姿()
            # [修正] exit 拍（迁移过渡拍）不允许 setState，旧写法会在云台就绪时抛
            # RuntimeError；此分支此前因"移动到航点"是桩而从未被执行到
            if sig != "exit" and r.检查云台位姿到位():
                sm.setState("调整升降杆")

        if st == "调整升降杆":
            # 按当前动作的 lift_height 摆好伸缩杆再执行动作：高度不对拍出来的图/温度没意义。
            insp = self.state.insp
            if sig == "enter":
                if not r.has_lift:
                    # 无升降杆机型：跳过升降摆位，直接执行动作（不下发 0x0C、不等 0x0E）
                    sm.setState("执行动作")
                else:
                    r.调整升降杆()
                    insp.lift_handled = False     # 新一次升降，重置到位闩锁
                    insp.lift_watch.clear()       # 新一次升降，重试计数归零
                    r.重置升降看门狗()
            # 与"移动到航点"同构：到位有 0x0E 上升沿事件与容差兜底两条来源，必须闩锁合流
            if not insp.lift_handled and (
                sig == "升降到位"
                or (sig not in ("enter", "exit") and r.检查升降杆到位())
            ):
                insp.lift_handled = True
                sm.setState("执行动作")
            elif not insp.lift_handled and sig not in ("enter", "exit") and r.检查升降卡住():
                if not r.重试调整升降杆():
                    insp.abort_reason = "lift_stalled"
                    sm.setState("巡检中止")

        if st == "执行动作":
            if sig == "enter":
                r.执行动作()   # enter 拍启动后台视觉动作（拍照/测温），置 vision_done=False
            # 视觉是后台线程阻塞调用，停在本状态等闩锁；完成（含失败放行）后再迁移
            # 闩锁：setState 到真正离开本状态有 exit/enter 两拍，这期间 st 仍是"执行动作"，
            # 不闩住会重复 setState、使"动作点开始"被进入两次而多推进一个动作（跳过动作）。
            _insp = self.state.insp
            if (not _insp.vision_handled and sig != "exit"
                    and r.检查动作完成()):
                _insp.vision_handled = True
                sm.setState("动作完成")

        if st == "动作完成":
            if sig == "enter":
                sm.signalMove("enter", "动作点开始")

        if st == "巡检完成":
            if sig == "enter":
                sm.stop()
                r.巡检结束()
                self.main.emit("巡检完成")

        if st == "巡检中止":
            # 走行看门狗判定卡死且重试耗尽：停车 + 释放 busy，**保留断点**（重启可续跑）
            if sig == "enter":
                # todo 需要收升降杆，复位云台
                r.中止当前巡检()
                sm.stop()
                self.main.emit("巡检中止")


# =========================================================================== #
# Robot
# =========================================================================== #
class Robot:
    """一台挂轨机器人。配置来自 prefab，BoardSrv 与状态机由内部持有。"""

    def __init__(
        self,
        *,
        prefab_root,
        clock: Callable[[], float] = time.monotonic,
        board: Optional[BoardSrv] = None,
        tick_interval: float = SM_TICK_SECONDS,
        inspection_dir: Optional[Path] = None,
        device_stall_sec: float = DEVICE_STALL_SEC,
        device_max_retry: int = DEVICE_MAX_RETRY,
        ptz_provider: Optional[Callable[[], object]] = None,
        vision_provider: Optional[Callable[[], object]] = None,
        recorder: Optional[object] = None,
    ) -> None:
        # 配置单点数据源：整棵 prefab 树。机器人基础信息（id/名称/版本/机型/ip/port）
        # 不另存副本，统一通过下方 property 实时从 RobotConfig 节点读取——inspector 对
        # 配置树的修改会即时反映，避免多处拷贝不一致。
        self.prefab_root = prefab_root
        if self._config_node is None:
            raise ValueError("prefab_root 中未找到 RobotConfig 配置节点")

        self._clock = clock
        self.state = RobotState()
        # 心跳周期取自 prefab（现场可调）：下位机约 3s 收不到数据就断开，必须小于它。
        self.board = board if board is not None else BoardSrv(
            self.ip, self.port,
            heartbeat_interval=float(self._config_node.heartbeat_interval))
        self.sm = RobotSm(self, clock=clock)

        self._tick_interval = max(0.02, tick_interval)
        self._tick_task: Optional[asyncio.Task] = None
        self._unregs: list[Callable[[], None]] = []
        self._running = False
        # 连接状态订阅（**必须**在 board.start() 之前注册，否则漏掉首次 CONNECTED）
        self._status_unreg: Optional[Callable[[], None]] = None
        # 在途的 0x01 初始化任务（同一时刻只保留一个）
        self._init_task: Optional[asyncio.Task] = None
        # 见过的 0x0E 电机 ID（只在首次出现时记一条日志，帮现场定位 ID 配错）
        self._seen_motor_ids: set[int] = set()

        # 巡检：任务记录落盘目录 + 当前正在执行的一次巡检（None=空闲）
        self.inspection_dir: Path = Path(inspection_dir) if inspection_dir else DATA_DIR / "inspection"
        self.current_inspection: Optional[InspectionTask] = None
        # 设备无进展看门狗参数（现场可调；测试/故障注入用短窗口）
        self._device_stall_sec = float(device_stall_sec)
        self._device_max_retry = int(device_max_retry)
        # 最近一次巡检中止的原因快照（走行看门狗触发时写入，接收新任务时清空）。
        # 只写日志的话现场很容易漏掉"巡检为什么不跑了"，这里留一份可查。
        self.last_abort: Optional[dict] = None
        # 云台访问工厂（可注入，测试用假对象）。None 时在调用处回退 hkptz_runtime.get_hkptz。
        self._ptz_provider = ptz_provider
        # 视觉访问工厂（可注入，测试/仿真用假对象）。None 时默认海康双光相机 HkPtzVision。
        self._vision_provider = vision_provider
        # 巡检结果落库器（可注入，测试用假对象）。None = 不落库，只落盘。
        self._recorder = recorder

    # ------------------------------------------------------------ 配置（prefab 单点）
    @property
    def _config_node(self):
        """prefab 树中的 RobotConfig 节点（懒查找，始终读取最新配置）。"""
        from app.prefab.nodes.robot import RobotConfig
        return _find_node(self.prefab_root, RobotConfig)

    @property
    def robot_id(self) -> str:
        return self._config_node.robot_id

    @property
    def name(self) -> str:
        return self._config_node.name

    @property
    def version(self) -> str:
        return self._config_node.version

    @property
    def robot_type(self) -> str:
        return self._config_node.robot_type

    @property
    def ip(self) -> str:
        return self._config_node.ip

    @property
    def port(self) -> int:
        return int(self._config_node.port)

    @property
    def task_min_battery(self) -> float:
        """允许任务的最低电量（%）；0=不限制。"""
        return float(self._config_node.task_min_battery)

    @property
    def lift_motor_id(self) -> int:
        """伸缩杆（升降）电机 ID（prefab 可配）。

        ⚠️ 不写死：2026-09-24 真机实测 0x0E 上发里 ID 字段是 **0**，而代码原本按 1 过滤，
        结果升降状态一直不更新（一直显示默认值）。不同机型约定不同，所以放配置里。
        """
        return int(self._config_node.lift_motor_id)

    @property
    def _lift_config_node(self):
        """prefab 树中的 LiftConfig 节点（懒查找；无则 None）。"""
        from app.prefab.nodes.lift import LiftConfigNode
        return _find_node(self.prefab_root, LiftConfigNode)

    @property
    def has_lift(self) -> bool:
        """这台机是否配备升降杆（无 LiftConfig 节点一律视为没有）。"""
        n = self._lift_config_node
        return bool(n.has_lift) if n is not None else False

    @property
    def lift_min_distance(self) -> float:
        """升降杆最低位置（m）。"""
        n = self._lift_config_node
        return float(n.min_distance) if n is not None else 0.0

    @property
    def lift_max_distance(self) -> float:
        """升降杆最高位置（m）。"""
        n = self._lift_config_node
        return float(n.max_distance) if n is not None else 0.0

    @property
    def _charge_pile_node(self):
        """prefab 树中的充电桩配置节点（懒查找；无则 None）。"""
        from app.prefab.nodes.charge_pile import ChargePileConfigNode
        return _find_node(self.prefab_root, ChargePileConfigNode)

    @property
    def charge_pile_x(self) -> float:
        """充电桩弧长坐标（m）；未配置节点则为 0。"""
        n = self._charge_pile_node
        return float(n.x) if n is not None else 0.0

    @property
    def charge_pile_floor(self) -> int:
        """充电桩所在楼层；未配置节点则为 0。"""
        n = self._charge_pile_node
        return int(n.floor) if n is not None else 0

    # ------------------------------------------------------------ 构建
    @classmethod
    def from_prefab(cls, path: str | Path, **kwargs) -> "Robot":
        """从 data/prefabs/xx.prefab.json 加载机器人配置树并构造 Robot。"""
        import app.prefab  # noqa: F401  触发节点类型注册（含 nodes.robot.RobotConfig）
        from app.prefab.nodes.robot import RobotConfig
        from app.prefab.registry import build

        spec = json.loads(Path(path).read_text(encoding="utf-8"))
        root = build(spec.get("root") or {})
        if _find_node(root, RobotConfig) is None:
            raise ValueError(f"{path} 中未找到 RobotConfig 配置节点")
        return cls(prefab_root=root, **kwargs)

    # ------------------------------------------------------------ 生命周期
    async def start(self) -> None:
        if self._running:
            return
        # ⚠️ 顺序：连接状态订阅必须在 board.start() **之前**注册 —— 首次 CONNECTED 是在
        # board.start() 内部（client.open()）同步产生的，start() 之后再注册只能收到重连。
        self._status_unreg = self.board.on_status_change(self._on_board_status)
        try:
            await self.board.start()
        except Exception:
            un = self._status_unreg
            self._status_unreg = None
            if un is not None:
                try:
                    un()
                except Exception:
                    pass
            raise
        self._unregs = [
            self.board.on(messages.CMD_UPLOAD_CHASSIS, self._on_chassis),
            self.board.on(messages.CMD_UPLOAD_MOTOR, self._on_motor),
            self.board.on(messages.CMD_CHARGE_STATE_UPLOAD, self._on_power_upload),
            self.board.on(messages.CMD_GET_POWER, self._on_power_response),
            self.board.on(messages.CMD_RFID_RANGE_EVENT, self._on_rfid),
        ]
        self._running = True
        self.sm.start()
        self._tick_task = asyncio.get_running_loop().create_task(self._tick_loop())
        # board.start() 内可能已经连上（首次 CONNECTED 回调发生在 _running 置位之前，
        # 那时 _send_init 会被"未启动"挡掉），这里补一次。
        if self.board.connected:
            self._on_board_status(ConnStatus.CONNECTED)
        logger.info("[robot] %s(%s) 已启动，目标控制板 %s:%s",
                    self.name, self.robot_id, self.ip, self.port)

    async def stop(self) -> None:
        if not self._running:
            return
        self._running = False
        if self._tick_task is not None:
            self._tick_task.cancel()
            try:
                await self._tick_task
            except (asyncio.CancelledError, Exception):
                pass
            self._tick_task = None
        if self._init_task is not None:
            self._init_task.cancel()
            try:
                await self._init_task
            except (asyncio.CancelledError, Exception):
                pass
            self._init_task = None
        if self._status_unreg is not None:
            try:
                self._status_unreg()
            except Exception:
                pass
            self._status_unreg = None
        for un in self._unregs:
            try:
                un()
            except Exception:
                pass
        self._unregs.clear()
        self.sm.stop()
        await self.board.stop()
        self.state.online = False
        self.state.board_status = self.board.status.value
        logger.info("[robot] %s(%s) 已停止", self.name, self.robot_id)

    # ------------------------------------------------------------ 控制板初始化（0x01）
    def _on_board_status(self, s: ConnStatus) -> None:
        """连接状态变化：每次 CONNECTED（首次 + 每次重连）都下发 0x01 初始化控制板。

        控制板把 0x01 当作"进入工作模式"的开关（方向/环形轨道/避障开关/限位都在里面），
        不初始化时设备行为不可预期（实测未初始化时约 5s 就主动断开）。
        """
        if s is not ConnStatus.CONNECTED:
            return
        if not self._config_node.init_on_connect:
            logger.info("[robot] %s 已按配置跳过 0x01 初始化控制板", self.robot_id)
            return
        self._schedule_init()

    def _schedule_init(self) -> None:
        """异步下发初始化（不在状态回调里阻塞），同一时刻只保留一个在途任务。"""
        task = self._init_task
        if task is not None and not task.done():
            return
        try:
            self._init_task = asyncio.get_running_loop().create_task(self._send_init())
        except RuntimeError:   # 无运行中的事件循环（同步调用场景）
            logger.debug("[robot] 无事件循环，跳过 0x01 初始化")

    async def _send_init(self) -> None:
        """下发 0x01 初始化控制板，并把结果写入 state（供 /api/rail/robot/state 观察）。"""
        node = self._config_node
        try:
            req = node.init_request()
        except Exception as e:
            self.state.board_init_ok = False
            self.state.board_init_error = f"构造 0x01 报文失败: {e}"
            logger.exception("[robot] %s 构造 0x01 初始化报文失败", self.robot_id)
            return
        params = node.init_params()
        logger.info("[robot] %s 下发 0x01 初始化控制板 %s", self.robot_id, params)
        try:
            resp = await self.board.request(req, timeout=INIT_REQUEST_TIMEOUT)
        except Exception as e:
            self.state.board_init_ok = False
            self.state.board_init_error = f"{type(e).__name__}: {e}"
            logger.warning("[robot] %s 0x01 初始化控制板失败：%r（参数 %s）",
                           self.robot_id, e, params)
            return
        code = int(getattr(resp, "error_code", 0) or 0)
        if code == 0:
            self.state.board_init_ok = True
            self.state.board_init_error = ""
            self.state.board_init_at = self._clock()
            logger.info("[robot] %s 0x01 初始化控制板成功", self.robot_id)
        else:
            self.state.board_init_ok = False
            self.state.board_init_error = f"控制板返回错误码 {code}"
            logger.warning("[robot] %s 0x01 初始化控制板被拒：错误码 %d（参数 %s）",
                           self.robot_id, code, params)

    async def _tick_loop(self) -> None:
        try:
            while self._running:
                self.state.online = self.board.connected
                self.state.board_status = self.board.status.value
                try:
                    self.sm.tick()
                except Exception:
                    logger.exception("[robot] %s 状态机 tick 异常", self.robot_id)
                await asyncio.sleep(self._tick_interval)
        except asyncio.CancelledError:
            pass

    # ------------------------------------------------------------ 外部命令入口
    def command(self, event: str, *args) -> None:
        """通用事件入口：业务层只"下发事件"，是否/何时执行由状态机决策。"""
        self.sm.send(event, "main")

    def note_manual(self) -> None:
        self.state.command.last_manual_ts = self._clock()

    def enter_manual(self) -> None:
        self.note_manual()
        self.sm.send("进入手控模式", "main")

    def start_inspection(self, inspection_id: Optional[str] = None) -> None:
        if inspection_id is not None:
            self.state.insp.current_inspection_id = inspection_id
        self.sm.send("收到巡检", "main")

    # ------------------------------------------------------------ 巡检任务入口
    def 接收巡检任务(self, payload) -> dict:
        """巡检命令入口：解析(多楼层合并) → 有未完成任务则忽略 → 落盘记录 → 装载 → 发信号启动。

        payload 为一次巡检的楼层分段（单个 dict 或其列表，同 id 视为同一次巡检的
        不同楼层）。返回结果字典，accepted=False 时不会落盘、不会启动。
        """
        try:
            task = InspectionTask.from_payload(payload)
        except Exception as e:  # 数据格式错误
            logger.warning("[robot] %s 巡检任务解析失败: %r", self.robot_id, e)
            return {"accepted": False, "reason": f"任务解析失败: {e}"}

        if self.巡检进行中:
            logger.info("[robot] %s 已有未完成巡检 %s，忽略新任务 %s",
                        self.robot_id, self.state.insp.current_inspection_id,
                        task.inspection_id)
            return {
                "accepted": False,
                "reason": "busy",
                "current_inspection_id": self.state.insp.current_inspection_id,
            }

        # 电量门槛：低于阈值且未在充电时拒绝接任务（阈值 0=不限制）
        threshold = self.task_min_battery
        if threshold > 0 and not self.state.battery.charging \
                and self.state.battery.battery_percent < threshold:
            logger.info("[robot] %s 电量 %.1f%% 低于允许阈值 %.0f%%（未充电），拒绝任务 %s",
                        self.robot_id, self.state.battery.battery_percent,
                        threshold, task.inspection_id)
            return {
                "accepted": False,
                "reason": "low_battery",
                "battery_percent": self.state.battery.battery_percent,
                "threshold": threshold,
            }

        record_path = task.save(self.inspection_dir)
        self.current_inspection = task
        insp = self.state.insp
        insp.current_inspection_id = task.inspection_id
        insp.current_waypoint_id = None
        insp.current_floor = None
        insp.detect_type = task.detect_type
        insp.waypoint_cursor = 0
        insp.action_cursor = 0
        insp.current_action_index = 0
        insp.current_action_id = None
        insp.current_action_type = None
        insp.target_x_m = None
        insp.arrive_handled = False
        insp.target_lift_m = None
        insp.lift_handled = False
        self._clear_watches()
        # 断点是"单槽"的（同时只可能有一次未完成巡检）：先清掉上一次中止/异常残留的
        # 其它 id 断点，否则本巡检完成删掉自己的断点后，残留会被开机续跑误当成未完成任务。
        self._clear_other_progress(task.inspection_id)
        # 落断点（航点 0）：断点存在即"有未完成巡检"，开机据此续跑
        self._write_progress(0)
        self.last_abort = None   # 新任务开始，清掉上一次的中止记录

        # 发 sm 信号要求启动巡检：main 收到"收到巡检"进入"巡检中"并激活 insp 子机
        self.sm.send("收到巡检", "main")
        logger.info(
            "[robot] %s 已接收巡检 %s（楼层%s，航点%d，动作%d），记录 %s",
            self.robot_id, task.inspection_id, task.floors_desc(),
            task.waypoint_count, task.action_count, record_path,
        )
        return {
            "accepted": True,
            "inspection_id": task.inspection_id,
            "name": task.name,
            "floors": task.floors_desc(),
            "waypoint_count": task.waypoint_count,
            "action_count": task.action_count,
            "detect_type": task.detect_type,
            "record_path": str(record_path),
        }

    @property
    def 巡检进行中(self) -> bool:
        """是否存在尚未完成（或未取消）的巡检；完成时由 :meth:`巡检结束` 清空。"""
        return self.current_inspection is not None

    def 巡检结束(self) -> None:
        """巡检子机走到"巡检完成"时调用：清空当前任务与游标，回到可接收新任务状态。"""
        if self.current_inspection is None and self.state.insp.current_inspection_id is None:
            return
        logger.info("[robot] %s 巡检 %s 结束",
                    self.robot_id, self.state.insp.current_inspection_id)
        # 完成即删断点：开机不会再续跑这一次巡检
        self._clear_progress()
        self.current_inspection = None
        insp = self.state.insp
        insp.current_inspection_id = None
        insp.current_waypoint_id = None
        insp.current_floor = None
        insp.detect_type = DETECT_TYPE_PLATFORM
        insp.waypoint_cursor = 0
        insp.action_cursor = 0
        insp.current_action_index = 0
        insp.current_action_id = None
        insp.current_action_type = None
        insp.target_x_m = None
        insp.arrive_handled = False
        insp.target_lift_m = None
        insp.lift_handled = False
        self._clear_watches()

    def 中止当前巡检(self) -> None:
        """设备无进展看门狗判定卡死且重试耗尽时调用：停车/停杆并中止本次巡检。

        与 :meth:`巡检结束` 的关键差别是**保留断点**——中止是"这次先不跑了"，不是
        "跑完了"。断点留在盘上，下次开机由 :meth:`检查未完成的任务` 从当前航点续跑。
        同时清空当前任务以释放 busy，否则后续任务会一直被 409 拒绝（这正是要看门狗的原因）。

        中止原因由 ``InspState.abort_reason`` 传入（看门狗失败的分支负责设置）。
        """
        insp = self.state.insp
        reason = insp.abort_reason or "move_stalled"
        iid, wp_id, act_id = (insp.current_inspection_id, insp.current_waypoint_id,
                              insp.current_action_id)
        retry = (insp.lift_watch.retry if reason == "lift_stalled"
                 else insp.move_watch.retry)
        self.stopRobot()   # 安全优先：先停车（升降机构另有自身限位，此处不主动回零）
        logger.error("[robot] %s 巡检 %s 中止（%s）：航点 %s 动作 %s 无进展"
                     "（已重发指令 %d 次仍无到位），已停车并保留断点，重启可续跑",
                     self.robot_id, iid, reason, wp_id, act_id, retry)
        self.last_abort = {
            "reason": reason,
            "inspection_id": iid,
            "waypoint_id": wp_id,
            "waypoint_index": max(0, insp.waypoint_cursor - 1),
            "action_id": act_id,
            "retry": retry,
            "stall_sec": self._device_stall_sec,
            "at": datetime.now(timezone.utc).isoformat(),
        }
        self.current_inspection = None
        insp.current_inspection_id = None
        insp.current_waypoint_id = None
        insp.current_floor = None
        insp.waypoint_cursor = 0
        insp.action_cursor = 0
        insp.current_action_index = 0
        insp.current_action_id = None
        insp.current_action_type = None
        insp.target_x_m = None
        insp.arrive_handled = False
        insp.target_lift_m = None
        insp.lift_handled = False
        insp.detect_type = DETECT_TYPE_PLATFORM
        insp.abort_reason = None
        self._clear_watches()

    # ------------------------------------------------------------ 巡检断点（续跑）
    def _progress_path(self, inspection_id: str) -> Path:
        return self.inspection_dir / f"{inspection_id}{INSPECTION_PROGRESS_SUFFIX}"

    def _write_progress(self, waypoint_index: int) -> None:
        """落盘断点航点下标。

        只记"当前正在做的航点下标"，不记航点内动作下标——恢复时该航点整点重做
        （走行 + 全部动作）。宁可重做一次拍照/测温，也不漏做。
        """
        iid = self.state.insp.current_inspection_id
        if not iid:
            return
        try:
            self.inspection_dir.mkdir(parents=True, exist_ok=True)
            self._progress_path(iid).write_text(
                json.dumps({
                    "inspection_id": iid,
                    "waypoint_index": int(waypoint_index),
                    "updated_at": datetime.now(timezone.utc).isoformat(),
                }, ensure_ascii=False, indent=2),
                encoding="utf-8",
            )
        except OSError:
            logger.exception("[robot] %s 巡检断点落盘失败（不影响巡检继续）", self.robot_id)

    def _clear_progress(self, inspection_id: Optional[str] = None) -> None:
        iid = inspection_id or self.state.insp.current_inspection_id
        if not iid:
            return
        try:
            self._progress_path(iid).unlink(missing_ok=True)
        except OSError:
            logger.exception("[robot] %s 巡检断点清理失败", self.robot_id)

    def _clear_other_progress(self, keep_id: Optional[str] = None) -> None:
        """清掉除 ``keep_id`` 以外的所有断点。

        断点是"单槽"的：同时只可能有一次未完成巡检。残留断点（上一次中止留下的）若不清，
        会被开机续跑当成未完成任务。
        """
        try:
            if not self.inspection_dir.is_dir():
                return
            keep = f"{keep_id}{INSPECTION_PROGRESS_SUFFIX}" if keep_id else None
            for path in self.inspection_dir.glob(f"*{INSPECTION_PROGRESS_SUFFIX}"):
                if path.name != keep:
                    self._unlink_quiet(path)
        except OSError:
            logger.exception("[robot] %s 巡检断点清理失败", self.robot_id)

    def _load_progress(self) -> Optional[dict]:
        """取最新的一条巡检断点（按文件修改时间倒序，跳过损坏文件）。无则 None。"""
        try:
            if not self.inspection_dir.is_dir():
                return None
            files = sorted(
                self.inspection_dir.glob(f"*{INSPECTION_PROGRESS_SUFFIX}"),
                key=lambda p: p.stat().st_mtime, reverse=True)
        except OSError:
            logger.exception("[robot] %s 巡检断点目录读取失败", self.robot_id)
            return None
        for path in files:
            try:
                data = json.loads(path.read_text(encoding="utf-8"))
                if isinstance(data, dict) and data.get("inspection_id"):
                    return data
                reason = "内容无效"
            except (OSError, ValueError):
                reason = "文件损坏"
            # 坏断点顺手清掉，避免每次开机都撞上；清理失败不影响开机（下面会返回 None）
            logger.warning("[robot] %s 巡检断点%s，已忽略: %s", self.robot_id, reason, path)
            self._unlink_quiet(path)
        return None

    def _unlink_quiet(self, path: Path) -> None:
        """尽力删除文件：失败只告警。开机路径上不能因清理失败把状态机卡在"启动"。"""
        try:
            path.unlink(missing_ok=True)
        except OSError:
            logger.warning("[robot] %s 清理文件失败: %s", self.robot_id, path)

    def clear_progress_files(self) -> list:
        """删除 data/inspection 下全部巡检断点文件（*.progress.json），返回已删文件名。

        取消巡检只让状态机退出，磁盘上的断点文件仍在，下次开机续跑会被当成未完成任务；
        此方法把断点文件清干净。
        """
        removed = []
        try:
            if not self.inspection_dir.is_dir():
                return removed
            for path in sorted(self.inspection_dir.glob(f"*{INSPECTION_PROGRESS_SUFFIX}")):
                self._unlink_quiet(path)
                removed.append(path.name)
        except OSError:
            logger.exception("[robot] %s 清理巡检断点文件失败", self.robot_id)
        if removed:
            logger.info("[robot] %s 已删除巡检断点文件: %s", self.robot_id, removed)
        return removed

    def _load_task_record(self, inspection_id: str) -> InspectionTask:
        """从落盘记录 ``{inspection_id}.json`` 重建巡检任务（用其中的原始楼层分段）。"""
        record = json.loads(
            (self.inspection_dir / f"{inspection_id}.json").read_text(encoding="utf-8"))
        return InspectionTask.from_payload(record["floors"])

    def goto_charge(self) -> None:
        self.sm.send("电量不足", "main")

    def switch_floor(self, go_out: bool = False) -> None:
        """触发切楼层（设置标志并激活 floor 子机）。[TODO-业务] 主机挂载入口待确认。"""
        self.state.switch_floor.flag_go_out = go_out
        if not self.sm.floor.active:
            self.sm.floor.start()

    # ------------------------------------------------------------ 上报 → 状态
    def _on_chassis(self, msg: "messages.ChassisState") -> None:
        st = self.state
        prev = st.chassis_state
        st.chassis_state = msg.state
        st.chassis_mode = msg.mode
        pose = st.pose
        # 协议 raw（mm / mm/s / ×10）-> 标准单位（m / m·s⁻¹ / 度）
        pose.x = msg.x * MM_TO_M
        pose.y = msg.y * MM_TO_M
        pose.yaw = msg.yaw * DEG10_TO_DEG
        pose.linear_x = msg.linear_x * MMPS_TO_MPS
        pose.linear_y = msg.linear_y * MMPS_TO_MPS
        pose.angular = msg.angular * DPS10_TO_DPS
        if msg.state == messages.CHASSIS_ARRIVED and prev != messages.CHASSIS_ARRIVED:
            # 到位上升沿：按当前活动子机路由到对应事件
            child = self.sm.active_child()
            if child == "charge":
                self.sm.send("到达目标位置", "charge")
            elif child == "insp":
                self.sm.send("已到达当前航点", "insp")
            elif child == "floor":
                self.sm.send("机器人到位", "floor")

    def _on_motor(self, msg: "messages.MotorState") -> None:
        """0x0E 电机状态上发：只关心伸缩杆（ID 见 prefab `lift_motor_id`），到位上升沿发"升降到位"。"""
        want = self.lift_motor_id
        if msg.motor_id != want:
            # 现场最常见的问题就是"升降状态一直不动"，而根因只是 ID 对不上。
            # 第一次见到某个 ID 就记一条，方便直接读出设备实际用的 ID。
            if msg.motor_id not in self._seen_motor_ids:
                self._seen_motor_ids.add(msg.motor_id)
                logger.info("[robot] %s 收到 0x0E 电机状态，motor_id=%d（配置的伸缩杆 ID=%d，"
                            "不一致则忽略；如设备实际用 %d 请改配置）",
                            self.robot_id, msg.motor_id, want, msg.motor_id)
            return
        lift = self.state.lift
        prev = lift.state
        lift.motor_id = msg.motor_id
        lift.state = msg.state
        lift.coord_m = msg.coord * MM_TO_M
        lift.speed = msg.speed
        lift.status_word = msg.status_word
        lift.driver_error = msg.driver_error
        lift.temperature = msg.temperature
        lift.updated_at = self._clock()
        if msg.state == messages.MOTOR_ST_ARRIVED and prev != messages.MOTOR_ST_ARRIVED:
            # 到位上升沿：仅巡检在跑时需要（其它子机暂不涉及升降）
            if self.sm.insp.active:
                self.sm.send("升降到位", "insp")

    def _apply_power(self, *, percent: float, voltage: float, current: float,
                     capacity: float, temperature: float,
                     contact: int, charge_state: int) -> None:
        # 入参均已是上位机标准单位（%、V、A、Ah、℃，float）
        bat = self.state.battery
        prev_done = bat.charge_state == CHARGE_STATE_DONE
        bat.battery_percent = percent
        bat.voltage, bat.current, bat.capacity, bat.temperature = (
            voltage, current, capacity, temperature)
        bat.contact, bat.charge_state = contact, charge_state
        # charging / contacted 由 BatteryState 的 property 依据 charge_state/contact 派生
        if charge_state == CHARGE_STATE_DONE and not prev_done:
            self.sm.send("充电到阈值", "charge")

    def _on_power_upload(self, msg: "messages.ChargeStateUpload") -> None:
        # 0x17：与 0x16 同单位（电压 10mV、电流 10mA、容量 10mAh、温度 0.1℃）——
        # 见 P17_*_SCALE 处真机实测记录；文档那行 mV/mA/mAh/℃ 与固件不符。
        self._apply_power(
            percent=float(msg.battery_percent),
            voltage=msg.voltage * P17_VOLTAGE_SCALE,
            current=msg.current * P17_CURRENT_SCALE,
            capacity=msg.capacity * P17_CAPACITY_SCALE,
            temperature=msg.temperature * P17_TEMP_SCALE,
            contact=msg.contact, charge_state=msg.charge_state)

    def _on_power_response(self, msg: "messages.PowerResponse") -> None:
        # 0x16：电压 10mV、电流 10mA、容量 10mAh、温度 0.1℃（与 0x17 相差 10 倍）
        self._apply_power(
            percent=float(msg.battery_percent),
            voltage=msg.voltage * P16_VOLTAGE_SCALE,
            current=msg.current * P16_CURRENT_SCALE,
            capacity=msg.capacity * P16_CAPACITY_SCALE,
            temperature=msg.temperature * P16_TEMP_SCALE,
            contact=msg.contact, charge_state=msg.charge_state)

    def _on_rfid(self, msg: "messages.RfidRangeEventUpload") -> None:
        if msg.type != messages.RFID_EVENT_ENTER:
            return
        rfid = self.state.rfid
        rfid.rfid, rfid.x, rfid.ts = int(msg.rfid), msg.x * MM_TO_M, self._clock()

    # ------------------------------------------------------------ 下发辅助
    def _send(self, msg) -> None:
        """单向下发，断线/未启动只告警，不抛进状态机。"""
        try:
            self.board.send(msg)
        except ConnectionError2 as exc:
            logger.warning("[robot] %s 下发失败（未连接）：%s", self.robot_id, exc)
        except RuntimeError as exc:
            logger.warning("[robot] %s 下发失败：%s", self.robot_id, exc)

    # ------------------------------------------------------------ 直接动作
    # 手动/调试用，调用即下发、不经状态机决策；上位机标准单位，内部换算协议 raw。
    def 向前(self, speed_mps: float = DEFAULT_JOG_SPEED_MPS) -> None:
        """持续向前点动，speed_mps 为速率（m/s，非负）；走行中需显式调用 停止()。"""
        speed = max(0.0, float(speed_mps))
        self._send(messages.ChassisMove(
            mode=messages.MOVE_FORWARD, linear_x=int(round(speed * MPS_TO_MMPS))))

    def 向后(self, speed_mps: float = DEFAULT_JOG_SPEED_MPS) -> None:
        """持续向后点动，speed_mps 为速率（m/s，非负）；走行中需显式调用 停止()。"""
        speed = max(0.0, float(speed_mps))
        self._send(messages.ChassisMove(
            mode=messages.MOVE_BACKWARD, linear_x=int(round(speed * MPS_TO_MMPS))))

    def 停止(self) -> None:
        """立即停车（点动或走行中均可下发）。"""
        self._send(messages.ChassisMove(mode=messages.MOVE_STOP))

    def 移动到指定位置(self, x_m: float,  speed_mps: float = DEFAULT_JOG_SPEED_MPS) -> None:
        """绝对位置移动：走到沿轨弧长 x_m（m）。挂轨单轴，到位由 0x0B ARRIVED 上报。"""

        logger.info(f'移动到指定位置 {x_m=}')
        speed = max(0.0, float(speed_mps))
        self._send(messages.ChassisMove(
            mode=messages.MOVE_GOTO, 
            linear_x=int(round(speed * MPS_TO_MMPS)),
            target_x=int(round(float(x_m) * M_TO_MM))))

    def _goto_x(self, target_x_m: float) -> None:
        """状态机内部用：绝对位置移动（等价 移动到指定位置）。"""
        self.移动到指定位置(target_x_m)

    # ====================================================================== #
    # 动作 / 检查成员函数 —— 状态机 beh_* 直接调用。
    # 已接真机的直接下发/读状态；依赖导航/任务/视觉层的为与旧 sm.py 一致的安全桩，
    # 标 [TODO-…]，未来只改方法体，状态机结构不必动。
    # ====================================================================== #

    # ---------------- 主机 ----------------
    def 手控超时(self) -> bool:
        ts = self.state.command.last_manual_ts
        if ts is None:
            return False
        return self._clock() - ts >= MANUAL_IDLE_SECONDS

    def 检查未完成的任务(self) -> bool:
        """开机续跑：有未完成巡检的断点则重新装载并返回 True（主机据此进"巡检中"）。

        恢复粒度是**断点航点**：该航点整点重做（重新走行 + 重做它的全部动作），
        已做过的动作可能重做一次（拍照/测温幂等），但不会漏做。

        以下情况视为"无未完成任务"并顺手清理断点：断点损坏/内容无效、对应任务记录
        缺失或不可解析、断点航点已走完（说明上次已实质完成）。
        """
        if self.current_inspection is not None:
            return True
        prog = self._load_progress()
        if prog is None:
            return False

        iid = str(prog["inspection_id"])
        try:
            task = self._load_task_record(iid)
        except Exception as e:  # 记录缺失/损坏/格式不符
            logger.warning("[robot] %s 断点巡检 %s 的任务记录不可用（%r），已清理断点",
                           self.robot_id, iid, e)
            self._clear_progress(iid)
            return False

        try:
            index = int(prog.get("waypoint_index") or 0)
        except (TypeError, ValueError):
            index = 0
        if index >= task.waypoint_count:
            logger.info("[robot] %s 断点巡检 %s 的航点已全部走完，视为已完成",
                        self.robot_id, iid)
            self._clear_progress(iid)
            return False

        self.current_inspection = task
        insp = self.state.insp
        insp.current_inspection_id = iid
        insp.current_waypoint_id = None
        insp.current_floor = None
        # 从落盘记录回解（中止时清过），否则 fms 的巡检续跑后会退回 platform
        insp.detect_type = task.detect_type
        # 游标指到断点航点：由"航点开始"的 检查下一个航点() 重新取出它
        insp.waypoint_cursor = index
        insp.action_cursor = 0
        insp.current_action_index = 0
        insp.current_action_id = None
        insp.current_action_type = None
        insp.target_x_m = None
        insp.arrive_handled = False
        insp.target_lift_m = None
        insp.lift_handled = False
        self._clear_watches()
        self.last_abort = None   # 已续跑，清掉中止记录
        logger.info("[robot] %s 续跑巡检 %s：从航点 %d/%d 重新开始（楼层%s，共%d动作）",
                    self.robot_id, iid, index + 1, task.waypoint_count,
                    task.floors_desc(), task.action_count)
        return True

    # ---------------- 充电：动作 ----------------
    def 回去充电(self) -> None:
        """手动回充：让主机进"去充电"（巡检中会先中止巡检再回桩）。"""
        self.sm.send("手动回充", "main")

    def 重置状态机(self) -> None:
        """重置状态机：停车、停全部子机、主机回到"启动"态重新走开机流程。

        用于状态机卡在异常态时人工复位。断点文件不清（重启会续跑；要清用
        "删除巡检中状态文件"按钮）。
        """
        try:
            self.stopRobot()
        except Exception:
            logger.exception("[robot] %s 重置状态机：停车失败", self.robot_id)
        self.sm.stop()
        self._clear_watches()
        self.last_abort = None
        self.sm.start()
        logger.info("[robot] %s 状态机已重置，主机回到启动态", self.robot_id)

    def 移动到最近的充电桩(self) -> None:
        """回桩：走到 prefab ``ChargePile`` 配置的桩坐标。

        到位由 0x0B ARRIVED 上升经 ``_on_chassis`` 按活动子机路由——此时是 charge 子机，
        故自动给 charge 发"到达目标位置"，进"就位优化"。
        跨楼层（当前楼层 != 桩楼层）只告警：切轿厢走 floor 子机，尚未接入主机回桩流程。
        """
        target_x = self.charge_pile_x
        pile_floor = self.charge_pile_floor
        cur_floor = self.state.insp.current_floor
        if cur_floor is not None and cur_floor != pile_floor:
            logger.warning(
                "[robot] %s 当前楼层 %s 与充电桩楼层 %s 不一致：跨楼层回桩（切轿厢）尚未接入，"
                "仍下发 goto 到桩坐标 %.3fm",
                self.robot_id, cur_floor, pile_floor, target_x)
        logger.info("[robot] %s 回桩：目标充电桩 X=%.3fm（楼层 %s，当前 %.3fm）",
                    self.robot_id, target_x, pile_floor, self.state.pose.x)
        self._goto_x(target_x)

    def 继续前进(self, distance) -> None:
        """沿当前方向继续前进 distance（m）：相对当前弧长下发绝对目标。"""
        self._goto_x(self.state.pose.x + float(distance))

    def 设置速度(self, x, y=0) -> None:
        """带符号点动速度（状态机用）：x 单位 m/s，>0 向前、<0 向后、=0 停止。

        协议速度字段无符号，方向由 mode 表达；挂轨单轴，y 不使用。
        """
        if x == 0:
            self.停止()
        elif x > 0:
            self.向前(x)
        else:
            self.向后(-x)

    def stopRobot(self) -> None:
        """停车（状态机用，等价 停止）。"""
        self.停止()

    # ---------------- 充电：检查 ----------------
    def 是否在充电桩里(self) -> bool:
        return self.state.battery.contacted

    def 是否最近触发了充电桩rfid(self) -> bool:
        ts = self.state.rfid.ts
        if ts <= 0:
            return False
        # [TODO-导航] 还应校验 rfid 是否属于充电桩卡集合，当前以"最近 N 秒有卡进入"近似
        return self._clock() - ts <= RFID_FRESH_SECONDS

    def 视觉检测轨道对接(self) -> bool:
        # [TODO-视觉] 接入视觉对接判定；未接前与旧草稿一致返回 True
        return True

    # ---------------- 切楼层 ----------------
    def 切楼层(self) -> None:
        # [TODO-导航] 楼层切换机构/电梯联动
        logger.debug("[robot] %s [TODO-导航] 切楼层", self.robot_id)

    def 移动机器人到0点(self) -> bool:
        """进入轿厢后移动到 0 点（绝对位置 0）；返回 True 表示已下发。"""
        self._goto_x(0)
        return True

    def 移动机器人到1号卡(self) -> None:
        # [TODO-导航] 需要 1 号卡 X 坐标（可由 latest_rfid/地图得到）
        logger.debug("[robot] %s [TODO-导航] 移动到1号卡", self.robot_id)

    def 检查机器人到位(self, x=None) -> bool:
        # [TODO-导航] 应对照目标 x 与底盘 ARRIVED；未接前与旧草稿一致返回 True
        return True

    def 检查机器人到达1号卡(self, x=None) -> bool:
        return True

    def 检查机器人到轿厢(self, x=None) -> bool:
        # [TODO-导航] 轿厢到位判定；未接前返回 True
        return True

    def 检查在1号卡前(self) -> bool:
        # [TODO-导航] 需要地图/轿厢相对位置
        return False

    def 检查在轿厢里(self) -> bool:
        # [TODO-导航] 需要地图/轿厢相对位置
        return False

    def 检查机器人在1号卡(self) -> bool:
        # [迁移补全][TODO-导航] 旧 sm.py 调用但未定义；默认未到
        return False

    # ---------------- 巡检 ----------------
    def 检查下一个航点(self) -> bool:
        """取下一个航点。

        有则设置当前航点/楼层/目标弧长并复位动作游标，返回 True；全部航点取完
        返回 False（巡检子机据此进入"巡检完成"）。
        """
        task = self.current_inspection
        insp = self.state.insp
        if task is None:
            return False
        if insp.waypoint_cursor >= len(task.waypoints):
            return False
        floor, wp = task.waypoints[insp.waypoint_cursor]
        insp.waypoint_cursor += 1
        insp.current_floor = floor
        insp.current_waypoint_id = wp.id
        insp.target_x_m = float(wp.pose.point.x)
        insp.action_cursor = 0
        insp.current_action_index = 0
        insp.current_action_id = None
        insp.current_action_type = None
        logger.info("[robot] %s 巡检航点 %d/%d：楼层%s 航点%s 目标X=%.3fm",
                    self.robot_id, insp.waypoint_cursor, task.waypoint_count,
                    floor, wp.id, insp.target_x_m)
        # 更新断点：当前正在做这个航点；中断后从这里整点重做
        self._write_progress(insp.waypoint_cursor - 1)
        return True

    def 检查下一个动作(self) -> bool:
        """取当前航点的下一个动作。

        有则设置当前动作并推进游标，返回 True；本航点动作做完返回 False
        （巡检子机回到"航点开始"取下一航点）。
        """
        task = self.current_inspection
        insp = self.state.insp
        if task is None:
            return False
        # 当前航点由游标定位（检查下一个航点已 +1），不按 id 反查：多楼层合并后
        # 不同楼层的航点 id 可能重复，反查会取到别的楼层的航点
        wp_index = insp.waypoint_cursor - 1
        if wp_index < 0 or wp_index >= len(task.waypoints):
            return False
        _, wp = task.waypoints[wp_index]
        if insp.action_cursor >= len(wp.action):
            return False
        act = wp.action[insp.action_cursor]
        insp.action_cursor += 1
        insp.current_action_index = insp.action_cursor
        insp.current_action_id = act.id
        insp.current_action_type = act.type
        # 本动作要求的升降高度（0 = 不需要升降，"调整升降杆"会直接放行）
        insp.target_lift_m = float(act.lift_height or 0.0)
        # 本动作要求的云台绝对位姿（无 ptz_param 则 None，"调整云台位姿"直接放行）
        p = act.ptz_param
        insp.target_ptz = (
            {"pan": float(p.pan), "tilt": float(p.tilt), "zoom": float(p.zoom)}
            if p is not None else None
        )
        logger.info("[robot] %s 巡检动作 %d/%d：航点%s 动作%s type=%d lift=%.3fm",
                    self.robot_id, insp.action_cursor, len(wp.action),
                    wp.id, act.id, act.type, insp.target_lift_m)
        return True

    def 移动机器人到当前航点(self) -> None:
        """移动到当前航点：复用绝对位置移动（goto，走行到航点 ``pose.point.x``）。

        到位由控制板 0x0B 的 ARRIVED 上报驱动，``_on_chassis`` 收到到位上升沿后向
        insp 子机发"已到达当前航点"，状态机随之进入"动作点开始"。
        """
        target = self.state.insp.target_x_m
        if target is None:
            logger.warning("[robot] %s 无当前航点目标弧长，跳过走行", self.robot_id)
            return
        logger.info("[robot] %s 移动到航点 %s：目标X=%.3fm（当前 %.3fm）",
                    self.robot_id, self.state.insp.current_waypoint_id,
                    float(target), self.state.pose.x)
        self.移动到指定位置(float(target))

    def 检查已到达当前航点(self) -> bool:
        """兜底到位判定：当前弧长与航点目标弧长之差在容差内即视为已到位。

        正常路径由 ``_on_chassis`` 的到位上升沿发"已到达当前航点"；本判定用于目标与
        当前位置重合（相邻航点同一 X）等控制板不再产生上升沿的场景，避免巡检卡在
        "移动到航点"。
        """
        target = self.state.insp.target_x_m
        if target is None:
            return False
        return abs(self.state.pose.x - float(target)) <= INSP_ARRIVE_TOL_M

    # ---------------- 巡检：设备无进展看门狗（底盘走行 / 伸缩杆升降） ----------------
    def _clear_watches(self) -> None:
        """清空两处看门狗（任务装载/恢复/结束/中止时调用）。

        与 :meth:`重置走行看门狗` / :meth:`重置升降看门狗` 的区别：本方法把窗口也清掉
        （未武装），后者是"开始一次动作、武装窗口并重新计时"。
        """
        self.state.insp.move_watch.clear()
        self.state.insp.lift_watch.clear()

    def 重置走行看门狗(self) -> None:
        """开始一次走行（首次下发或重发 goto）时武装无进展看门狗。

        注意不重置 ``retry``——重试计数属于"本航点"，由进入"移动到航点"时归零。
        """
        self.state.insp.move_watch.arm(self.state.pose.x, self._clock())

    def 检查走行卡住(self) -> bool:
        """底盘无进展看门狗：窗口内弧长几乎没动即认为卡住。

        控制板失联（0x0B 停更、弧长冻住）或走行机构卡死都会被这一步抓到。
        """
        return self.state.insp.move_watch.stalled(
            self.state.pose.x, self._clock(),
            self._device_stall_sec, DEVICE_PROGRESS_EPS_M)

    def 重试走行(self) -> bool:
        """卡住后重发一次 goto，并在新窗口内继续等。

        返回 True 表示已重发（调用方继续等）；False 表示重试次数已耗尽，
        调用方应转入"巡检中止"。
        """
        insp = self.state.insp
        if insp.move_watch.retry >= self._device_max_retry:
            return False
        insp.move_watch.retry += 1
        logger.warning(
            "[robot] %s 巡检航点 %s 走行 %.0fs 无进展，第 %d/%d 次重发 goto（目标X=%s，当前 %.3fm）",
            self.robot_id, insp.current_waypoint_id, self._device_stall_sec,
            insp.move_watch.retry, self._device_max_retry,
            insp.target_x_m, self.state.pose.x)
        self.重置走行看门狗()
        self.移动机器人到当前航点()
        return True

    # ---------------- 巡检：伸缩杆（升降） ----------------
    def 重置升降看门狗(self) -> None:
        """开始一次升降（首次下发或重发指令）时武装无进展看门狗。"""
        self.state.insp.lift_watch.arm(self.state.lift.coord_m, self._clock())

    def 检查升降卡住(self) -> bool:
        """伸缩杆无进展看门狗：窗口内高度几乎没动即认为卡住。

        控制板失联（0x0E 停更、高度冻住）或升降机构卡死都会被这一步抓到。
        """
        return self.state.insp.lift_watch.stalled(
            self.state.lift.coord_m, self._clock(),
            self._device_stall_sec, DEVICE_PROGRESS_EPS_M)

    def 重试调整升降杆(self) -> bool:
        """卡住后重发一次升降指令，并在新窗口内继续等。

        返回 True 表示已重发；False 表示重试次数已耗尽，调用方应转入"巡检中止"。
        """
        insp = self.state.insp
        if insp.lift_watch.retry >= self._device_max_retry:
            return False
        insp.lift_watch.retry += 1
        logger.warning(
            "[robot] %s 巡检动作 %s 升降 %.0fs 无进展，第 %d/%d 次重发指令"
            "（目标高度=%s，当前 %.3fm）",
            self.robot_id, insp.current_action_id, self._device_stall_sec,
            insp.lift_watch.retry, self._device_max_retry,
            insp.target_lift_m, self.state.lift.coord_m)
        self.重置升降看门狗()
        self.调整升降杆()
        return True

    def 调整云台位姿(self) -> None:
        """把云台摆到当前动作要求的绝对位姿（``action.ptz_param`` 的 pan/tilt/zoom）。

        定位是**阻塞式** HTTP ISAPI 调用（真机走完约 2s），不能放在节拍里，因此这里
        起一个守护线程跑 :meth:`_ptz_worker`，用 ``insp.ptz_done`` 闩锁回投结果；
        :meth:`检查云台位姿到位` 只读该闩锁，节拍不阻塞。无 ptz_param 直接放行。
        """
        insp = self.state.insp
        insp.ptz_done = False
        insp.ptz_error = None
        target = insp.target_ptz
        if not target:
            insp.ptz_done = True          # 本动作无云台要求，直接放行
            logger.debug("[robot] %s 动作 %s 无云台位姿要求，跳过",
                         self.robot_id, insp.current_action_id)
            return
        insp.ptz_busy = True
        logger.info("[robot] %s 调整云台位姿（动作 %s）：pan=%.1f tilt=%.1f zoom=%.2f",
                    self.robot_id, insp.current_action_id,
                    target["pan"], target["tilt"], target.get("zoom", 1.0))
        threading.Thread(
            target=self._ptz_worker, args=(dict(target),),
            name=f"ptz-{self.robot_id}", daemon=True,
        ).start()

    def 检查云台位姿到位(self) -> bool:
        """云台是否已到位（或无需/失败放行）。非阻塞：只读后台线程写入的闩锁。"""
        return self.state.insp.ptz_done

    def _get_ptz(self):
        """返回云台访问对象：优先用注入的工厂，否则回退全局 HkPtz 单例（懒连接）。"""
        if self._ptz_provider is not None:
            return self._ptz_provider()
        from .hkptz_runtime import get_hkptz
        return get_hkptz()

    def _云台到位(self, status: dict, target: dict) -> bool:
        """按各轴容差比对 ptz_status 回读与目标，判断云台是否到位。"""
        if not status:
            return False
        dp = abs(float(status.get("pan", 0.0)) - float(target["pan"]))
        dt = abs(float(status.get("tilt", 0.0)) - float(target["tilt"]))
        dz = abs(float(status.get("zoom", 1.0)) - float(target.get("zoom", 1.0)))
        return dp <= PTZ_PAN_TOL_DEG and dt <= PTZ_TILT_TOL_DEG and dz <= PTZ_ZOOM_TOL

    def _ptz_worker(self, target: dict) -> None:
        """后台线程：下发绝对定位 + 轮询到位。用真实墙钟，与状态机注入时钟无关。

        任何异常都只记录到 ``insp.ptz_error`` 并放行（``ptz_done=True``）——云台/相机
        不可用不应让整条巡检卡死。
        """
        insp = self.state.insp
        try:
            ptz = self._get_ptz()
            ptz.absolute_move(target["pan"], target["tilt"],
                              float(target.get("zoom", 1.0)))
            settled = False
            deadline = time.monotonic() + PTZ_SETTLE_TIMEOUT_SEC
            while True:
                if self._云台到位(ptz.ptz_status(), target):
                    settled = True
                    break
                if time.monotonic() >= deadline:
                    break
                time.sleep(PTZ_POLL_INTERVAL_SEC)
            if not settled:
                logger.warning("[robot] %s 云台定位 %.0fs 未确认到位（目标 %s），仍放行",
                               self.robot_id, PTZ_SETTLE_TIMEOUT_SEC, target)
        except Exception as e:  # noqa: BLE001  云台失败不阻断巡检
            insp.ptz_error = str(e)
            logger.warning("[robot] %s 云台定位失败（放行巡检）：%s", self.robot_id, e)
        finally:
            insp.ptz_done = True
            insp.ptz_busy = False

    # ---------------- 巡检：伸缩杆（升降） ----------------
    def 移动到指定高度(self, height_m: float) -> None:
        """伸缩杆移动到指定高度（0x0C mode=3 指定坐标，coord 为协议 mm）。"""
        self._send(messages.MotorCtrl(
            motor_id=self.lift_motor_id, mode=messages.MOTOR_GOTO,
            coord=int(round(float(height_m) * M_TO_MM))))

    def 调整升降杆(self) -> None:
        """把伸缩杆摆到当前动作要求的高度（``action.lift_height``，m）。

        已在容差内则不下发（与 calibration/control 的升降控制约定一致：先比高度再动），
        避免每个动作都白跑一次电机。
        """
        insp = self.state.insp
        target = insp.target_lift_m
        if target is None:
            return
        if self.检查升降杆到位():
            logger.debug("[robot] %s 伸缩杆已在 %.3fm（目标 %.3fm），跳过",
                         self.robot_id, self.state.lift.coord_m, float(target))
            return
        logger.info("[robot] %s 调整升降杆（动作 %s）：目标 %.3fm（当前 %.3fm）",
                    self.robot_id, insp.current_action_id,
                    float(target), self.state.lift.coord_m)
        self.state.lift.target_m = float(target)
        self.移动到指定高度(float(target))

    def 检查升降杆到位(self) -> bool:
        """伸缩杆到位判定。

        正常路径由 ``_on_motor`` 的 0x0E 到位上升沿发"升降到位"；容差兜底用于
        "目标与当前高度已重合"（不需要动）等控制板不再产生上升沿的场景。
        当前动作不要求升降（``target_lift_m`` 为 0 或 None）时直接放行。
        """
        insp = self.state.insp
        target = insp.target_lift_m
        if target is None:
            return True
        return abs(self.state.lift.coord_m - float(target)) <= LIFT_ARRIVE_TOL_M

    def 执行动作(self) -> None:
        """按当前动作类型分发（巡检子机"执行动作"状态 enter 拍调用一次）。

        拍照/全屏测温是**同步**的相机调用（见 :meth:`_run_vision`），本拍跑完并把
        ``vision_done`` 置好，状态机据此迁移到"动作完成"。相机不可用时 provider
        抛异常被接住、照样放行，不卡死巡检。跑完顺手把结果写进 SQLite。
        """
        self._reset_vision_latch()
        kind = self.state.insp.current_action_type
        if kind == ACTION_TYPE_PHOTO:
            self.拍照()
        elif kind == ACTION_TYPE_THERMOMETRY:
            self.全屏测温()
        elif kind == ACTION_TYPE_VIDEO:
            # [TODO-视觉] 录像需按 duration 起停（cmd=38 command=3/5），本轮先直接放行
            insp = self.state.insp
            insp.vision_kind = "video"
            insp.vision_done = True
            logger.info("[robot] %s 录像动作本轮未接入，直接放行（动作 %s）",
                        self.robot_id, insp.current_action_id)
        else:
            insp = self.state.insp
            insp.vision_done = True
            logger.warning("[robot] %s 未知动作类型 %s，跳过（动作 %s）",
                           self.robot_id, kind, insp.current_action_id)
        # 动作跑完（或放行）即落库：图已经落到盘上，库里那一行也要跟着翻转，
        # 下游才能轮询到"这条待处理"（detect_type=fms）或"这条待上报"（platform）
        self.记录动作结果()

    # ------------------------------------------------------------ 巡检结果落库
    def 准备巡检结果占位(self) -> None:
        """巡检开始时调用：按任务结构把 run / 动作 / 测点的占位写进 SQLite（幂等）。

        占位先行的意义：下游（检测识别 / 上报平台）可以边跑边取，不必等整次巡检
        结束；执行器崩了、机器人断电，那些没回填的 pending 行就是"卡在第几个动作"
        的答案。已生成过就跳过（续跑会再次走到这里）。
        """
        rec = self._recorder
        task = self.current_inspection
        if rec is None or task is None:
            return
        rec.ensure_placeholders(
            task,
            robot_id=self.robot_id,
            robot_ip=self.ip,
            detect_type=self.state.insp.detect_type,
        )

    def 记录动作结果(self) -> None:
        """把刚执行完的动作结果回填到 SQLite 的占位行。

        没有落库器（未注入）时直接返回：图已经落盘，落库只是给下游用的账本，
        缺了它巡检照样跑——不要让"库不可用"变成巡检停下来的理由。

        图片路径存**相对于 ``DATA_DIR/inspection/``** 的相对路径，不存绝对路径：
        前端通过 ``/data/inspection/`` 这个 Static Files 前缀直接就能加载，
        不用后端再做一次路径转换。
        """
        rec = self._recorder
        insp = self.state.insp
        if rec is None or not insp.current_inspection_id:
            return
        res = insp.vision_result or {}
        kind = insp.vision_kind or ""
        raw_path = res.get("path") or ""
        # 绝对路径 -> 相对于 inspection 根目录的相对路径
        # 例如：D:\...\data\inspection\iid\xxx.jpg -> iid/xxx.jpg
        rel_path = self._to_inspection_rel_path(raw_path)
        if kind == "video" or not insp.vision_kind:
            status = STATUS_SKIPPED      # 录像未接入 / 未知类型：放行但不产出数据
        else:
            status = STATUS_OK if res.get("ok") else STATUS_FAILED

        # 把当前动作配置里的 steer_point_name 加进 raw_json，供前端树显示航点名
        raw = dict(res or {})
        if self.current_inspection is not None:
            for floor, wp in self.current_inspection.waypoints:
                if wp.id == insp.current_waypoint_id:
                    for act in wp.action:
                        if act.id == insp.current_action_id:
                            raw["steer_point_name"] = act.steer_point_name
                            break
                    break

        rec.finish_action(
            inspection_id=insp.current_inspection_id,
            floor=insp.current_floor,
            waypoint_id=insp.current_waypoint_id or "",
            action_id=insp.current_action_id or "",
            status=status,
            picture=rel_path if kind == "visible" else "",
            infrared=rel_path if kind == "thermometry" else "",
            local_path=rel_path,
            thermometry=res.get("thermometry"),
            raw=raw or None,
        )

    @staticmethod
    def _to_inspection_rel_path(abs_path: str) -> str:
        """绝对路径 -> 可直接用于 ``<img src>`` 的 Web 路径。

        返回 ``/data/inspection/<相对路径>`` 形式，与 FastAPI 挂载的
        ``StaticFiles(directory=DATA_DIR/inspection, name="inspection-files")``
        前缀对齐——前端拿到直接就能用，不用再拼前缀。

        如果路径已经是 http/data: 开头的 URL，原样返回。
        兜底：实在算不出来就返回原字符串，别让落库因为路径处理失败而丢数据。
        """
        s = str(abs_path or "").strip()
        if not s:
            return ""
        low = s.lower()
        if low.startswith("http://") or low.startswith("https://") or low.startswith("data:"):
            return s
        try:
            insp_root = (DATA_DIR / "inspection").resolve()
            candidate = Path(s).resolve()
            rel = str(candidate.relative_to(insp_root)).replace("\\", "/")
            return f"/data/inspection/{rel}"
        except (ValueError, OSError):
            # 不在 inspection 根下 / 路径非法 —— 原样返回，别丢数据
            return s

    def 检查动作完成(self) -> bool:
        """视觉动作是否完成（成功或失败都放行）。

        视觉是**同步**跑的（见 :meth:`_run_vision`）："执行动作"的 enter 拍里就已经
        跑完并把 ``vision_done`` 置好，所以这里只是读闩锁让状态机迁移，不再需要
        超时兜底——不存在"跑到一半还没回来"这个中间态了。
        """
        return self.state.insp.vision_done

    # ---------------- 巡检：视觉（拍照 / 全屏测温） ----------------
    def _reset_vision_latch(self) -> None:
        insp = self.state.insp
        insp.vision_kind = None
        insp.vision_busy = False
        insp.vision_done = False
        insp.vision_error = None
        insp.vision_result = None
        insp.vision_handled = False

    def _get_vision(self):
        """视觉访问对象：优先注入工厂，否则默认海康双光相机（复用云台会话工厂）。"""
        if self._vision_provider is not None:
            return self._vision_provider()
        return HkPtzVision(self._ptz_provider)

    def _vision_result_dir(self) -> Path:
        """本次巡检的结果目录 data/inspection/{inspection_id}/。"""
        iid = self.state.insp.current_inspection_id or "unknown"
        d = self.inspection_dir / iid
        d.mkdir(parents=True, exist_ok=True)
        return d

    def _action_file_stem(self) -> str:
        """当前动作结果文件名前缀：f{楼层}_wp{航点序号}_a{动作序号}_{动作id短码}。"""
        insp = self.state.insp
        aid = (insp.current_action_id or "")[:8]
        return (f"f{insp.current_floor}_wp{insp.waypoint_cursor:03d}"
                f"_a{insp.current_action_index:02d}_{aid}")

    def _vision_ctx(self) -> dict:
        """本次视觉动作的上下文（落盘目录 / 文件名前缀 / 业务定位）。"""
        insp = self.state.insp
        return {
            "inspection_id": insp.current_inspection_id,
            "floor": insp.current_floor,
            "waypoint_id": insp.current_waypoint_id,
            "action_id": insp.current_action_id,
            "action_type": insp.current_action_type,
            "result_dir": str(self._vision_result_dir()),
            "file_stem": self._action_file_stem(),
        }

    def _run_vision(self, kind: str) -> bool:
        """同步执行一次视觉动作（拍照 / 全屏测温），把结果写进闩锁，返回是否成功。

        ⚠️ **阻塞调用，直接跑在状态机线程里**（占住这一拍）。相机 SDK 是同步接口，
        而"执行动作"本来就是一个"等结果"的状态——起后台线程反而要额外准备代际
        校验（防迟到结果）、超时兜底（防线程挂死）、结果回投三套机制，收益为零。

        代价是真机相机挂起时这一拍会卡住（原方案的超时兜底只是让巡检跳过动作
        继续跑，图一样拿不到）。相机不可用时 provider 抛异常，这里接住并放行，
        巡检不会停在"执行动作"。
        """
        insp = self.state.insp
        insp.vision_kind = kind
        insp.vision_busy = False       # 同步执行：没有"进行中"这个对外可见的中间态
        insp.vision_done = False
        insp.vision_error = None
        insp.vision_result = None
        try:
            provider = self._get_vision()
            if kind == "visible":
                res: VisionResult = provider.capture_visible(self._vision_ctx())
            else:
                res = provider.full_thermometry(self._vision_ctx())
        except Exception as e:  # noqa: BLE001  视觉失败不阻断巡检
            res = VisionResult(kind=kind, ok=False, error=str(e))
        insp.vision_result = res.as_dict()
        insp.vision_error = res.error
        if res.ok:
            logger.info("[robot] %s 视觉动作完成（%s）：%s",
                        self.robot_id, kind, res.path or res.thermometry)
        else:
            logger.warning("[robot] %s 视觉动作失败（放行巡检，%s）：%s",
                           self.robot_id, kind, res.error)
        insp.vision_done = True
        return bool(res.ok)

    def 拍照(self) -> bool:
        """可见光拍照：同步抓一张 JPEG 落盘，成功返回 True。

        结果在 ``state.insp.vision_result``（含落盘路径）；相机不可用时记录
        ``vision_error`` 并放行，不卡死巡检。
        """
        return self._run_vision("visible")

    def 全屏测温(self) -> bool:
        """全屏测温：同步抓红外热像落盘（温度矩阵待热像仪测温能力接入）。

        与 :meth:`拍照` 同理，同步执行、失败放行。
        """
        return self._run_vision("thermometry")


# =========================================================================== #
# 工具
# =========================================================================== #
def _find_node(node, cls):
    """DFS 在 prefab 节点树中找第一个 cls 类型节点（含根）。"""
    if isinstance(node, cls):
        return node
    for child in node.child_nodes:
        found = _find_node(child, cls)
        if found is not None:
            return found
    return None
