"""Robot 编排层测试（if/else Sm 版）。

不连真实控制板：注入 FakeBoard；用 FakeClock 手动推进时间，逐拍 pump 状态机
（Sm 一次 setState 占 exit/enter 两拍，行为迁移需要 pump 若干拍）。
"""
import asyncio
from pathlib import Path

import pytest

from app.config import PREFAB_DIR
from app.rail import messages
from app.rail.client import ConnStatus
from app.rail.robot import (
    Robot,
    RobotSm,
    RobotState,
    Pose,
    BatteryState,
    RfidState,
    ChargeSlightMoveState,
    MANUAL_IDLE_SECONDS,
)


class FakeClock:
    def __init__(self):
        self.t = 0.0

    def __call__(self):
        return self.t


class FakeBoard:
    """不连网的 BoardSrv 替身。"""

    def __init__(self):
        self.status = ConnStatus.IDLE
        self.connected = False
        self.sent = []
        self.status_handlers = []   # 连接状态订阅回调（Robot 靠它发 0x01 初始化）
        self.requested = []         # 走过的 request() 消息

    async def start(self):
        self.connected = True
        self.status = ConnStatus.CONNECTED

    async def stop(self):
        self.connected = False
        self.status = ConnStatus.IDLE

    def send(self, msg):
        self.sent.append(msg)

    def on(self, *a, **k):
        return lambda: None

    def on_link_loss(self, *a, **k):
        return lambda: None

    def on_status_change(self, fn):
        self.status_handlers.append(fn)
        return lambda: self.status_handlers.remove(fn)

    async def request(self, msg, *, timeout=None):
        self.requested.append(msg)
        return messages.ErrorResponse(error_code=0)

    def fire_status(self, s):
        """测试里手动触发连接状态变化。"""
        for fn in list(self.status_handlers):
            fn(s)


def make_robot(board=None, clock=None, inspection_dir=None):
    """构造测试用 Robot。

    ``inspection_dir`` 必须隔离（默认用 pytest 的 tmp_path）：开机流程会调
    ``检查未完成的任务()`` 扫描该目录里的 ``*.progress.json``，若落到运行时目录
    ``backend/data/inspection``，真机/联调留下的断点会让"启动直接进巡检"，
    与"启动进空闲"的用例互相打架（表现为随机 4 个用例失败）。
    """
    board = board or FakeBoard()
    clock = clock or FakeClock()
    if inspection_dir is None:
        import tempfile
        inspection_dir = Path(tempfile.mkdtemp(prefix="robot-test-insp-"))
    return Robot.from_prefab(
        PREFAB_DIR / "robot.prefab.json", board=board, clock=clock,
        tick_interval=0.02, inspection_dir=inspection_dir,
    ), board, clock


def pump(r, clk, n=1, step=1.0):
    """推进 n 个节拍，每拍时钟前进 step 秒。"""
    for _ in range(n):
        clk.t += step
        r.sm.tick()


def until(r, clk, target, max_ticks=120, step=1.0):
    """推进直到叶子状态 == target，否则报错并给出当前路径。"""
    for _ in range(max_ticks):
        if r.sm.leaf_state() == target:
            return
        clk.t += step
        r.sm.tick()
    raise AssertionError(f"期望叶子状态 {target!r}，实际 {r.sm.state_path()}")


# --------------------------------------------------------------------------- #
# 配置加载
# --------------------------------------------------------------------------- #
def test_robot_from_prefab_loads_config():
    r, board, _ = make_robot()
    cfg = r._config_node
    # 基础信息实时取自 prefab 树中的 RobotConfig 节点（单点数据源，无平铺副本）。
    # ⚠️ ip/port 不写死：data/prefabs/robot.prefab.json 是**部署配置**，会随现场在
    # 仿真(127.0.0.1:50000)/真机(192.168.8.91:16122)之间切换，写死必然漂红。
    assert r.robot_id == cfg.robot_id == "R001"
    assert r.name == cfg.name
    assert r.robot_type == cfg.robot_type
    assert r.version == ""
    assert (r.ip, r.port) == (cfg.ip, int(cfg.port))
    assert cfg.type == "RobotConfig"
    assert r.prefab_root is cfg
    assert isinstance(r.state, RobotState)
    assert isinstance(r.state.pose, Pose)
    # 不再缓存 config 副本、也无平铺 id
    assert not hasattr(r, "config")
    assert not hasattr(r, "id")
    # 单点：直接改 prefab 节点，property 立即反映
    cfg.ip = "192.168.1.10"
    cfg.port = 50001
    assert (r.ip, r.port) == ("192.168.1.10", 50001)
    assert isinstance(r.state.battery, BatteryState)
    assert isinstance(r.state.rfid, RfidState)
    assert isinstance(r.sm, RobotSm)
    assert board is r.board


# --------------------------------------------------------------------------- #
# 启动 → 空闲
# --------------------------------------------------------------------------- #
def test_sm_has_four_machines_and_boots_to_idle():
    r, _, clk = make_robot()
    assert [s.name for s in r.sm.sms] == ["main", "charge", "floor", "insp"]
    assert not r.sm.running
    r.sm.start()
    assert r.sm.running
    until(r, clk, "空闲")
    assert r.sm.current_state() == "空闲"
    assert r.sm.active_child() is None
    assert r.sm.state_path() == ["main:空闲"]


def test_boot_resumes_unfinished_inspection():
    """有未完成任务时启动直接进巡检，并激活巡检子机。"""
    r, _, clk = make_robot()
    r.检查未完成的任务 = lambda: True
    r.检查下一个航点 = lambda: True   # 让巡检机停在"移动到航点"等待到位
    r.sm.start()
    until(r, clk, "移动到航点")
    assert r.sm.current_state() == "巡检中"
    assert r.sm.active_child() == "insp"
    assert r.sm.insp.st == "移动到航点"


# --------------------------------------------------------------------------- #
# 充电完整闭环（上报驱动）
# --------------------------------------------------------------------------- #
def test_charge_flow_with_reported_power_and_rfid():
    r, board, clk = make_robot()
    r.sm.start()
    until(r, clk, "空闲")

    # 1) 上位机/事件：去充电
    r.goto_charge()
    until(r, clk, "移动中")
    assert r.sm.active_child() == "charge"

    # 2) 底盘上报到位（上升沿）→ 就位优化；enter 拍因未对接而继续前进 300mm
    r._on_chassis(messages.ChassisState(state=messages.CHASSIS_ARRIVED, x=0))
    until(r, clk, "就位优化")
    # until 在 exit 拍即返回；再 pump 让 enter 拍执行"继续前进(300)"
    pump(r, clk, 3)
    goto = [m for m in board.sent if isinstance(m, messages.ChassisMove)
            and m.mode == messages.MOVE_GOTO]
    assert goto and goto[-1].target_x == 300

    # 3) RFID 进入（充电桩卡）→ 充电微挪
    r._on_rfid(messages.RfidRangeEventUpload(
        type=messages.RFID_EVENT_ENTER, rfid=88, x=290))
    until(r, clk, "充电微挪")
    assert isinstance(r.state.nudge, ChargeSlightMoveState)

    # 4) 充电中上报（contact=1, charge_state=5）→ 充电中
    r._on_power_upload(messages.ChargeStateUpload(contact=1, charge_state=5))
    until(r, clk, "充电中")
    assert r.state.battery.contacted and r.state.battery.charging

    # 5) 充满（charge_state=6 上升沿）→ 子机结束、主机回空闲
    r._on_power_upload(messages.ChargeStateUpload(contact=1, charge_state=6))
    until(r, clk, "空闲")
    assert not r.sm.charge.active
    assert r.sm.active_child() is None


def test_nudge_emits_speed_then_stop_cycle():
    """未充上时微挪：微挪开始下发点动速度，微挪时间到下发停止。"""
    r, board, clk = make_robot()
    r.sm.start()
    until(r, clk, "空闲")
    r.goto_charge()
    until(r, clk, "移动中")
    r._on_chassis(messages.ChassisState(state=messages.CHASSIS_ARRIVED))
    until(r, clk, "就位优化")
    r._on_rfid(messages.RfidRangeEventUpload(type=messages.RFID_EVENT_ENTER, rfid=1))
    until(r, clk, "充电微挪")
    board.sent.clear()

    # until 在 exit 拍返回：pump 经过 enter（重置+emit微挪开始）到"微挪开始"拍执行 step
    # 拍1 消费 exit，拍2 enter 发"微挪开始"，拍3 step 前进点动并 arm 2s 时间到
    pump(r, clk, 3)
    fwd = [m for m in board.sent if isinstance(m, messages.ChassisMove)
           and m.mode == messages.MOVE_FORWARD]
    assert fwd and fwd[-1].linear_x == 1

    # step 武装 2s"微挪时间到"；推进到点后应下发 stopRobot
    board.sent.clear()
    pump(r, clk, 4, step=1.0)
    stops = [m for m in board.sent if isinstance(m, messages.ChassisMove)
             and m.mode == messages.MOVE_STOP]
    assert stops, "微挪时间到应下发停止"


# --------------------------------------------------------------------------- #
# 手控模式与超时
# --------------------------------------------------------------------------- #
def test_manual_mode_idle_timeout():
    r, _, clk = make_robot()
    r.sm.start()
    until(r, clk, "空闲")

    clk.t = 100.0
    r.enter_manual()
    until(r, clk, "手控模式")
    assert r.state.command.last_manual_ts == 100.0

    # 未超时：保持手控
    clk.t = 100.0 + MANUAL_IDLE_SECONDS - 1
    pump(r, clk, 3, step=0)
    assert r.sm.current_state() == "手控模式"

    # 超时：回空闲
    clk.t = 100.0 + MANUAL_IDLE_SECONDS + 1
    until(r, clk, "空闲", step=0)


# --------------------------------------------------------------------------- #
# 动作下发
# --------------------------------------------------------------------------- #
def test_speed_frames():
    r, board, _ = make_robot()
    # 入参为标准单位 m/s；协议 linear_x 为 mm/s（无符号，方向靠 mode）
    r.设置速度(0)
    r.设置速度(0.03)
    r.设置速度(-0.02)
    modes = [(m.mode, m.linear_x) for m in board.sent]
    assert modes == [
        (messages.MOVE_STOP, 0),
        (messages.MOVE_FORWARD, 30),
        (messages.MOVE_BACKWARD, 20),
    ]


def test_pose_unit_conversion():
    """0x0B 上报 raw（mm / mm/s / ×10）-> Pose 标准单位（m / m·s⁻¹ / 度）。"""
    r, _, _ = make_robot()
    r._on_chassis(messages.ChassisState(
        x=12345, y=2000, yaw=123, linear_x=2000, linear_y=-1000, angular=50))
    p = r.state.pose
    assert p.x == 12.345 and p.y == 2.0
    assert p.yaw == 12.3 and p.angular == 5.0
    assert p.linear_x == 2.0 and p.linear_y == -1.0
    assert all(isinstance(v, float) for v in
               (p.x, p.y, p.yaw, p.linear_x, p.linear_y, p.angular))


def test_forward_uses_relative_goto():
    r, board, clk = make_robot()
    r.state.pose.x = 1.0          # m
    r.继续前进(0.3)               # 再走 0.3 m
    msg = board.sent[-1]
    assert msg.mode == messages.MOVE_GOTO and msg.target_x == 1300  # 协议 mm


def test_goto_zero_targets_origin():
    r, board, _ = make_robot()
    assert r.移动机器人到0点() is True
    msg = board.sent[-1]
    assert msg.mode == messages.MOVE_GOTO and msg.target_x == 0


def test_direct_motion_actions():
    """四个直接动作：向前/向后/停止/移动到指定位置，立即下发对应帧。"""
    r, board, _ = make_robot()
    r.向前(0.5)
    r.向后(0.2)
    r.停止()
    r.移动到指定位置(1.25)
    got = [(m.mode, m.linear_x, m.target_x) for m in board.sent]
    assert got == [
        (messages.MOVE_FORWARD, 500, 0),    # 0.5 m/s -> 500 mm/s
        (messages.MOVE_BACKWARD, 200, 0),   # 0.2 m/s -> 200 mm/s
        (messages.MOVE_STOP, 0, 0),
        (messages.MOVE_GOTO, 0, 1250),      # 1.25 m -> 1250 mm
    ]


def test_direct_motion_default_jog_speed():
    """向前/向后不传速度时用默认点动速度（0.3 m/s -> 300 mm/s）。"""
    r, board, _ = make_robot()
    r.向前()
    r.向后()
    assert [(m.mode, m.linear_x) for m in board.sent] == [
        (messages.MOVE_FORWARD, 300),
        (messages.MOVE_BACKWARD, 300),
    ]


def test_contacted_reads_power_report():
    """0x17 上发：10mV/10mA/10mAh/0.1℃ -> V/A/Ah/℃。

    ⚠️ 协议文档把这行写成 mV/mA/mAh/℃，与真机不符。真机 payload 实测
    `5f 0b22 ff77 070a 0145 00 00`（battery=95, voltage=2850, current=-137,
    capacity=1802, temperature=321）→ 28.50V / -1.37A / 18.02Ah / 32.1℃，
    与 0x16 完全同一口径。若按文档的 mV/mA/mAh/℃ 解，会算出 2.85V / 325℃。
    """
    r, _, _ = make_robot()
    assert r.是否在充电桩里() is False
    r._on_power_upload(messages.ChargeStateUpload(
        battery_percent=80, voltage=2400, current=150, capacity=2000,
        temperature=310, contact=1, charge_state=3))
    bat = r.state.battery
    assert r.是否在充电桩里() is True
    assert bat.charging is False
    assert (bat.battery_percent, bat.voltage, bat.current, bat.capacity,
            bat.temperature) == (80.0, 24.0, 1.5, 20.0, 31.0)
    assert all(isinstance(v, float) for v in (
        bat.battery_percent, bat.voltage, bat.current, bat.capacity, bat.temperature))
    # 状态枚举保持整数
    assert isinstance(bat.contact, int) and isinstance(bat.charge_state, int)


def test_power_0x16_and_0x17_use_same_units():
    """0x16 与 0x17 单位一致（均为 10mV/10mA/10mAh/0.1℃）→ 相同原始值应得相同工程值。

    曾误以为两者差 10 倍（照抄文档里 0x17 那行 mV/mA/mAh/℃），真机实测推翻。
    """
    r, _, _ = make_robot()
    r._on_power_response(messages.PowerResponse(
        battery_percent=80, voltage=2400, current=150, capacity=2000,
        temperature=310, contact=1, charge_state=5))
    from16 = r.state.battery
    r2, _, _ = make_robot()
    r2._on_power_upload(messages.ChargeStateUpload(
        battery_percent=80, voltage=2400, current=150, capacity=2000,
        temperature=310, contact=1, charge_state=5))
    from17 = r2.state.battery
    for f in ("voltage", "current", "capacity", "temperature"):
        assert getattr(from16, f) == getattr(from17, f)
    assert (from16.voltage, from16.current, from16.capacity, from16.temperature) == (
        24.0, 1.5, 20.0, 31.0)
    assert from16.charging is True and from16.contacted is True


def test_rfid_fresh_window():
    r, _, clk = make_robot()
    clk.t = 50.0
    assert r.是否最近触发了充电桩rfid() is False
    r._on_rfid(messages.RfidRangeEventUpload(
        type=messages.RFID_EVENT_ENTER, rfid=7, x=1234))   # 协议 mm
    # rfid 为整数卡号、x 为标准单位 m
    assert r.state.rfid.rfid == 7
    assert isinstance(r.state.rfid.rfid, int)
    assert r.state.rfid.x == 1.234
    assert isinstance(r.state.rfid.x, float)
    assert r.是否最近触发了充电桩rfid() is True
    clk.t = 50.0 + 6.0
    assert r.是否最近触发了充电桩rfid() is False


# --------------------------------------------------------------------------- #
# 生命周期（async，FakeBoard）
# --------------------------------------------------------------------------- #
@pytest.mark.asyncio
async def test_robot_start_stop_lifecycle():
    r, board, clk = make_robot()
    await r.start()
    try:
        assert r._running and board.connected
        assert r.sm.running
        await asyncio.sleep(0.05)
        r.设置速度(1)
        await asyncio.sleep(0.05)
        assert board.sent  # 速度帧已下发
    finally:
        await r.stop()
    assert not r._running
    assert not board.connected
    assert not r.sm.running


# --------------------------------------------------------------------------- #
# 控制板初始化（0x01）：连接建立 / 每次重连都要下发
# --------------------------------------------------------------------------- #
@pytest.mark.asyncio
async def test_send_init_on_connect():
    """连上就发 0x01 初始化控制板，并把结果写进 state（现场排查靠它）。"""
    r, board, _ = make_robot()
    await r.start()
    try:
        await asyncio.sleep(0.05)
        assert board.requested, "连接建立后应下发 0x01 初始化控制板"
        init = board.requested[0]
        assert init.cmd == messages.CMD_INIT
        assert len(init.to_bytes()) == 26          # 文档口径 12 字段
        assert r.state.board_init_ok is True
        assert r.state.board_init_error == ""
    finally:
        await r.stop()


@pytest.mark.asyncio
async def test_send_init_again_on_reconnect():
    """重连后必须重发（控制板掉电重启就丢了初始化）。"""
    r, board, _ = make_robot()
    await r.start()
    try:
        await asyncio.sleep(0.05)
        n1 = len(board.requested)
        board.connected = False
        board.fire_status(ConnStatus.RECONNECTING)
        await asyncio.sleep(0.02)
        assert len(board.requested) == n1, "断开时不应再发"
        board.connected = True
        board.fire_status(ConnStatus.CONNECTED)
        await asyncio.sleep(0.05)
        assert len(board.requested) == n1 + 1, "重连后应重发 0x01"
    finally:
        await r.stop()


@pytest.mark.asyncio
async def test_init_params_come_from_prefab():
    """0x01 的参数必须来自 RobotConfig（prefab 单点数据源），不能在 Python 里硬编码。"""
    r, board, _ = make_robot()
    cfg = r._config_node
    cfg.director = 1
    cfg.is_ring = True
    cfg.track_photo_avoid = False
    cfg.ultrasonic_avoid = True
    cfg.low_battery_threshold = 42
    cfg.x_min, cfg.x_max = -1000, 2000
    await r.start()
    try:
        await asyncio.sleep(0.05)
        init = board.requested[0]
        assert (init.director, init.is_ring) == (1, 1)
        assert (init.track_photo_avoid, init.ultrasonic_avoid) == (0, 1)
        assert init.low_battery_threshold == 42
        assert (init.x_min, init.x_max) == (-1000, 2000)
    finally:
        await r.stop()


@pytest.mark.asyncio
async def test_init_can_be_disabled_and_reports_error():
    """配置里关掉初始化则不发；控制板回错误码时 state 要如实记录。"""
    r, board, _ = make_robot()
    r._config_node.init_on_connect = False
    await r.start()
    try:
        await asyncio.sleep(0.05)
        assert board.requested == []
    finally:
        await r.stop()

    r2, board2, _ = make_robot()
    orig = board2.request

    async def _reject(msg, *, timeout=None):
        board2.requested.append(msg)
        return messages.ErrorResponse(error_code=7)

    board2.request = _reject
    await r2.start()
    try:
        await asyncio.sleep(0.05)
        assert r2.state.board_init_ok is False
        assert "7" in r2.state.board_init_error
    finally:
        await r2.stop()
    board2.request = orig
