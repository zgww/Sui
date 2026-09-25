"""巡检任务接收/落盘/装载/忙时忽略 的编排层测试（不连真实控制板）。

用 FakeBoard + FakeClock 手动逐拍驱动状态机；巡检记录落盘到 tmp_path，
不污染 backend/data/inspection。
"""
import json
from pathlib import Path

from app.config import PREFAB_DIR
from app.rail import messages
from app.rail.client import ConnStatus
from app.rail.inspection import (
    DETECT_TYPE_FMS,
    DETECT_TYPE_PLATFORM,
    InspectionTask,
)
from app.rail.robot import DEVICE_MAX_RETRY, DEVICE_STALL_SEC, Robot
from app.rail.vision import VisionResult

DATA_FILE = Path(__file__).parent / "test_inspection.json"
TASK_ID = "79b11cccfde80c36cea7db09e376903b"


class FakeClock:
    def __init__(self):
        self.t = 0.0

    def __call__(self):
        return self.t


class FakeBoard:
    def __init__(self):
        self.status = ConnStatus.IDLE
        self.connected = False
        self.sent = []
        self.status_handlers = []
        self.requested = []

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
        for fn in list(self.status_handlers):
            fn(s)


class FakePtz:
    """假云台：absolute_move 记录目标，ptz_status 立即回读该目标（首个轮询拍即判到位）。

    避免测试连真实相机（192.168.6.170）阻塞 _ptz_worker。
    """

    def __init__(self):
        self.moves = []
        self.last = {"pan": 0.0, "tilt": 0.0, "zoom": 1.0}

    def absolute_move(self, pan, tilt, zoom=1.0, *, channel=None):
        self.last = {"pan": float(pan), "tilt": float(tilt), "zoom": float(zoom)}
        self.moves.append(dict(self.last))

    def ptz_status(self, channel=None):
        return dict(self.last)


class FakeVision:
    """假视觉：拍照/测温立即写占位 JPEG 并返回成功，避免 worker 连真实相机。"""

    def __init__(self):
        self.calls = []

    def _snap(self, kind, ctx):
        self.calls.append(kind)
        d = Path(ctx["result_dir"])
        d.mkdir(parents=True, exist_ok=True)
        p = d / f"{ctx['file_stem']}_{kind}.jpg"
        p.write_bytes(b"fake-jpeg")
        return VisionResult(kind=kind, ok=True, path=str(p))

    def capture_visible(self, ctx):
        return self._snap("visible", ctx)

    def full_thermometry(self, ctx):
        return self._snap("thermometry", ctx)


def make_robot(tmp_path, clock=None, recorder=None):
    clock = clock or FakeClock()
    fake_ptz = FakePtz()
    fake_vision = FakeVision()
    r = Robot.from_prefab(
        PREFAB_DIR / "robot.prefab.json",
        board=FakeBoard(),
        clock=clock,
        tick_interval=0.02,
        inspection_dir=tmp_path,
        ptz_provider=lambda: fake_ptz,
        vision_provider=lambda: fake_vision,
        recorder=recorder,
    )
    r.fake_ptz = fake_ptz
    r.fake_vision = fake_vision
    return r, clock


def pump(r, clk, n=1, step=1.0):
    for _ in range(n):
        clk.t += step
        r.sm.tick()


def until(r, clk, target, max_ticks=120, step=1.0):
    for _ in range(max_ticks):
        if r.sm.leaf_state() == target:
            return
        clk.t += step
        r.sm.tick()
    raise AssertionError(f"期望叶子状态 {target!r}，实际 {r.sm.state_path()}")


def pump_until(r, clk, cond, max_ticks=3000, step=1.0, what=""):
    """按拍推进直到 cond() 成立；超时即断言失败。用于看门狗这类依赖时间推进的场景。"""
    for _ in range(max_ticks):
        if cond():
            return
        clk.t += step
        r.sm.tick()
    raise AssertionError(f"等待超时：{what or cond}（当前 {r.sm.state_path()}）")


def load_payload():
    return json.loads(DATA_FILE.read_text(encoding="utf-8"))


# --------------------------------------------------------------------------- #
# 模拟控制板：0x0B 上报 + 跑完一次巡检
# --------------------------------------------------------------------------- #
def feed_chassis(r, state, x_m):
    """模拟控制板 0x0B 上报：x 为弧长 m（协议 raw 为 mm）。"""
    r._on_chassis(messages.ChassisState(state=state, x=int(round(x_m * 1000))))


def goto_frames(r):
    """已下发的 goto 帧（target_x 为协议 mm）。"""
    return [m for m in r.board.sent
            if isinstance(m, messages.ChassisMove) and m.mode == messages.MOVE_GOTO]


def drive_inspection(r, clk, max_ticks=5000, stop_when=None):
    """模拟控制板把整条巡检跑完，返回按顺序访问过的航点 id。

    每检测到一次新的 goto 下发，就上报"运行 → 已到达"，驱动
    移动到航点 → 动作点开始 → 动作 → 下一航点 → 巡检完成。
    ``stop_when()`` 返回 True 时立即停下（模拟中途掉电，用于续跑测试）。
    """
    visited: list[str] = []
    last_wp = None
    arrived = 0
    for _ in range(max_ticks):
        if stop_when is not None and stop_when():
            return visited
        if not r.巡检进行中:
            return visited
        wp_id = r.state.insp.current_waypoint_id
        if wp_id != last_wp:
            last_wp = wp_id
            if wp_id is not None:
                visited.append(wp_id)
        if r.sm.leaf_state() == "移动到航点":
            target = r.state.insp.target_x_m
            if target is not None and len(goto_frames(r)) > arrived:
                arrived += 1
                feed_chassis(r, messages.CHASSIS_RUNNING, r.state.pose.x)
                feed_chassis(r, messages.CHASSIS_ARRIVED, target)
        clk.t += 1.0
        r.sm.tick()
    raise AssertionError(f"巡检未在 {max_ticks} 拍内完成：{r.sm.state_path()}")


# --------------------------------------------------------------------------- #
# 接收：多楼层合并、落盘、装载、发信号进入巡检
# --------------------------------------------------------------------------- #
def test_receive_inspection_merges_floors_saves_and_starts(tmp_path):
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")

    result = r.接收巡检任务(load_payload())

    # 数组合并：同 id 的两个楼层（1、2）= 一次巡检
    assert result["accepted"] is True
    assert result["inspection_id"] == TASK_ID
    assert result["floors"] == [1, 2]
    assert result["waypoint_count"] == 34       # 15 + 19
    assert result["action_count"] == 122        # 61 + 61

    # 落盘记录存在且无损（含两个楼层原始分段）
    record_file = tmp_path / f"{TASK_ID}.json"
    assert record_file.exists()
    rec = json.loads(record_file.read_text(encoding="utf-8"))
    assert rec["inspection_id"] == TASK_ID
    assert rec["floor_count"] == 2
    assert len(rec["floors"]) == 2

    # 装载并发信号：main 进巡检中、insp 子机走到"移动到航点"等待到位
    assert r.巡检进行中 is True
    assert r.state.insp.current_inspection_id == TASK_ID
    until(r, clk, "移动到航点")
    assert r.sm.current_state() == "巡检中"
    assert r.sm.active_child() == "insp"
    assert r.state.insp.current_waypoint_id is not None
    assert isinstance(r.state.insp.target_x_m, float)


# --------------------------------------------------------------------------- #
# 忙时忽略：已有未完成任务，新任务不接收、不落盘
# --------------------------------------------------------------------------- #
def test_busy_ignores_new_task(tmp_path):
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")

    first = r.接收巡检任务(load_payload())
    assert first["accepted"] is True
    until(r, clk, "移动到航点")

    # 另一次巡检（不同 id）应被忽略
    other = {"floor": 3, "id": "f" * 32, "name": "另一次", "plan": "p", "waypoint": []}
    result = r.接收巡检任务(other)
    assert result["accepted"] is False
    assert result["reason"] == "busy"
    assert result["current_inspection_id"] == TASK_ID
    # 当前任务不变，新任务不落盘
    assert r.state.insp.current_inspection_id == TASK_ID
    assert not (tmp_path / ("f" * 32 + ".json")).exists()


# --------------------------------------------------------------------------- #
# 航点 / 动作游标按任务数据推进
# --------------------------------------------------------------------------- #
def test_waypoint_and_action_cursors(tmp_path):
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")
    r.接收巡检任务(load_payload())
    until(r, clk, "移动到航点")

    # 状态机 enter"航点开始"已取走第 0 个航点
    first_wp = r.current_inspection.waypoints[0][1]
    assert r.state.insp.current_waypoint_id == first_wp.id
    n_action = len(first_wp.action)
    assert n_action > 0

    # 当前航点动作依次可取，取完返回 False
    for _ in range(n_action):
        assert r.检查下一个动作() is True
    assert r.检查下一个动作() is False
    assert r.state.insp.current_action_type in (1, 2, 3)

    # 后续航点仍可顺序取出
    assert r.检查下一个航点() is True


# --------------------------------------------------------------------------- #
# 空任务：无航点 → 巡检立即完成并清空，回到可接收状态
# --------------------------------------------------------------------------- #
def test_empty_inspection_finishes_and_clears(tmp_path):
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")

    empty = {"floor": 1, "id": "e" * 32, "name": "空巡检", "plan": "p", "waypoint": []}
    result = r.接收巡检任务(empty)
    assert result["accepted"] is True
    assert result["waypoint_count"] == 0

    pump(r, clk, 12)  # 航点开始→巡检完成→main 回空闲
    assert r.巡检进行中 is False
    assert r.current_inspection is None
    assert r.state.insp.current_inspection_id is None
    assert r.sm.leaf_state() == "空闲"

    # 完成后可再次接收
    again = r.接收巡检任务(load_payload())
    assert again["accepted"] is True


# --------------------------------------------------------------------------- #
# 航点走行闭环：goto 下发 → 控制板到位 → 动作 → 下一航点 → 巡检完成
# --------------------------------------------------------------------------- #
def test_waypoint_move_and_arrival_runs_whole_inspection(tmp_path):
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")

    r.接收巡检任务(load_payload())
    until(r, clk, "移动到航点")

    task = r.current_inspection
    expected_wp_ids = [w.id for _, w in task.waypoints]
    expected_act_ids = [a.id for _, w in task.waypoints for a in w.action]

    # 走行复用 goto：目标弧长 = 当前航点 pose.point.x（协议 mm）
    # until 在 exit 拍即返回，再 pump 两拍让 enter 拍执行"移动机器人到当前航点"
    first_target = r.state.insp.target_x_m
    pump(r, clk, 2)
    frames = goto_frames(r)
    assert frames and frames[-1].target_x == int(round(first_target * 1000))

    # 统计真正执行到的动作（按航点顺序、动作顺序）
    executed: list[str] = []
    orig_exec = r.执行动作

    def spy_exec():
        executed.append(r.state.insp.current_action_id)
        orig_exec()

    r.执行动作 = spy_exec

    visited = drive_inspection(r, clk)

    # 航点按楼层/序号顺序全部走完，动作全部执行
    assert visited == expected_wp_ids
    assert len(visited) == task.waypoint_count == 34
    assert executed == expected_act_ids
    assert len(executed) == task.action_count == 122

    # 每个航点一次 goto，目标弧长与航点 X 一一对应
    assert [f.target_x for f in goto_frames(r)] == [
        int(round(w.pose.point.x * 1000)) for _, w in task.waypoints
    ]

    # 巡检完成：任务清空、可再接收新任务
    assert r.巡检进行中 is False
    assert r.current_inspection is None
    assert r.state.insp.current_inspection_id is None

    # "巡检结束"清空后主机还需两拍迁移，等它回空闲
    until(r, clk, "空闲")
    assert r.sm.leaf_state() == "空闲"
    assert r.接收巡检任务(load_payload())["accepted"] is True


# --------------------------------------------------------------------------- #
# 兜底：相邻航点同一 X，控制板不再产生到位上升沿也不卡死
# --------------------------------------------------------------------------- #
def test_same_x_waypoints_advance_without_arrival_edge(tmp_path):
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")

    same = {
        "floor": 1, "id": "a" * 32, "name": "同点巡检", "plan": "p",
        "waypoint": [
            {"id": "w1", "index": 1, "pose": {"point": {"x": 5.0, "y": 0, "z": 0}},
             "action": [{"id": "a1", "type": 1}]},
            {"id": "w2", "index": 2, "pose": {"point": {"x": 5.0, "y": 0, "z": 0}},
             "action": [{"id": "a2", "type": 1}]},
        ],
    }
    r.接收巡检任务(same)
    until(r, clk, "移动到航点")
    assert r.state.insp.target_x_m == 5.0

    # 第一个航点：正常到位上升沿
    feed_chassis(r, messages.CHASSIS_RUNNING, 0.0)
    feed_chassis(r, messages.CHASSIS_ARRIVED, 5.0)

    # 第二个航点与当前位置重合：不再上报任何到位事件，靠容差兜底走完
    until(r, clk, "空闲")
    assert len(goto_frames(r)) == 2
    assert r.巡检进行中 is False
    assert r.sm.leaf_state() == "空闲"


# --------------------------------------------------------------------------- #
# 断点续跑：开机从断点航点恢复，完成后断点删除
# --------------------------------------------------------------------------- #
def test_resume_unfinished_inspection_after_restart(tmp_path):
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")

    r.接收巡检任务(load_payload())
    until(r, clk, "移动到航点")
    pump(r, clk, 2)
    task = r.current_inspection

    # 走到第 3 个航点时"掉电"（不再推进）
    drive_inspection(r, clk, stop_when=lambda: r.state.insp.waypoint_cursor >= 3)
    index = r.state.insp.waypoint_cursor - 1
    assert index == 2
    assert r.巡检进行中 is True

    # 断点已落盘，指向当前正在做的航点
    prog_file = tmp_path / f"{TASK_ID}.progress.json"
    assert prog_file.exists()
    prog = json.loads(prog_file.read_text(encoding="utf-8"))
    assert prog["inspection_id"] == TASK_ID
    assert prog["waypoint_index"] == index

    # 重启：同一落盘目录新建 Robot，开机自动续跑
    r2, clk2 = make_robot(tmp_path)
    r2.sm.start()
    until(r2, clk2, "移动到航点")
    assert r2.巡检进行中 is True
    assert r2.state.insp.current_inspection_id == TASK_ID
    # 从断点航点重新开始（而不是回到第 0 个航点）
    assert r2.state.insp.waypoint_cursor == index + 1
    assert r2.state.insp.current_waypoint_id == task.waypoints[index][1].id

    # 跑完剩余 → 巡检完成、断点删除
    drive_inspection(r2, clk2)
    until(r2, clk2, "空闲")
    assert r2.巡检进行中 is False
    assert not prog_file.exists()


def test_finished_inspection_is_not_resumed(tmp_path):
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")
    r.接收巡检任务(load_payload())
    until(r, clk, "移动到航点")
    pump(r, clk, 2)

    drive_inspection(r, clk)
    until(r, clk, "空闲")

    # 记录保留（历史），断点已删
    assert (tmp_path / f"{TASK_ID}.json").exists()
    assert not (tmp_path / f"{TASK_ID}.progress.json").exists()

    # 重启后不应被当成未完成任务
    r2, clk2 = make_robot(tmp_path)
    r2.sm.start()
    until(r2, clk2, "空闲")
    assert r2.巡检进行中 is False
    assert r2.sm.leaf_state() == "空闲"


def test_invalid_progress_is_cleared_without_resume(tmp_path):
    # 1) 只有断点、没有对应任务记录 → 不续跑并清理断点
    prog_file = tmp_path / f"{TASK_ID}.progress.json"
    prog_file.write_text(
        json.dumps({"inspection_id": TASK_ID, "waypoint_index": 1}), encoding="utf-8")
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")
    assert r.巡检进行中 is False
    assert not prog_file.exists()

    # 2) 断点文件本身损坏 → 清理且不续跑
    bad = tmp_path / "deadbeef.progress.json"
    bad.write_text("{ 这不是 json", encoding="utf-8")
    r2, clk2 = make_robot(tmp_path)
    r2.sm.start()
    until(r2, clk2, "空闲")
    assert not bad.exists()

    # 3) 断点航点已走完 → 视为上次已完成，不续跑
    task = InspectionTask.from_payload(load_payload())
    task.save(tmp_path)
    done_prog = tmp_path / f"{TASK_ID}.progress.json"
    done_prog.write_text(
        json.dumps({"inspection_id": TASK_ID, "waypoint_index": task.waypoint_count}),
        encoding="utf-8")
    r3, clk3 = make_robot(tmp_path)
    r3.sm.start()
    until(r3, clk3, "空闲")
    assert r3.巡检进行中 is False
    assert not done_prog.exists()


# --------------------------------------------------------------------------- #
# 走行看门狗：控制板失联不能无限等（重发 goto → 重试耗尽 → 中止并释放 busy）
# --------------------------------------------------------------------------- #
def test_move_watchdog_retries_then_aborts_and_frees_busy(tmp_path):
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")
    r.接收巡检任务(load_payload())
    until(r, clk, "移动到航点")
    pump(r, clk, 2)   # enter 拍：下发 goto + 武装看门狗

    # 首个航点 x=0.814，与当前位置（0）差得远，不会走容差兜底
    assert len(goto_frames(r)) == 1
    assert r.state.insp.move_watch.retry == 0

    # 控制板失联：此后不再上报 0x0B，弧长冻住
    pump(r, clk, int(DEVICE_STALL_SEC) - 5)
    assert r.sm.leaf_state() == "移动到航点"    # 窗口内不触发
    assert len(goto_frames(r)) == 1

    # 每个窗口到期重发一次 goto（首发之外再发 DEVICE_MAX_RETRY 次）
    for expected in range(2, DEVICE_MAX_RETRY + 2):
        pump_until(r, clk, lambda e=expected: len(goto_frames(r)) >= e,
                   what=f"第 {expected} 次 goto 下发")
        assert r.state.insp.move_watch.retry == expected - 1
        assert r.sm.leaf_state() == "移动到航点"

    # 重试耗尽 → 中止巡检 → 主机退出"巡检中"释放 busy
    pump_until(r, clk, lambda: r.sm.leaf_state() == "空闲", what="中止后回空闲")
    assert len(goto_frames(r)) == 1 + DEVICE_MAX_RETRY
    assert r.巡检进行中 is False
    assert r.current_inspection is None
    assert r.state.insp.current_inspection_id is None

    # 安全：中止时已下发停车
    assert any(isinstance(m, messages.ChassisMove) and m.mode == messages.MOVE_STOP
               for m in r.board.sent)

    # 断点保留（下次开机可续跑），指向触发中止的那个航点
    prog_file = tmp_path / f"{TASK_ID}.progress.json"
    assert prog_file.exists()
    assert json.loads(prog_file.read_text(encoding="utf-8"))["waypoint_index"] == 0

    # 中止原因留痕（现场不必翻日志）
    assert r.last_abort is not None
    assert r.last_abort["reason"] == "move_stalled"
    assert r.last_abort["inspection_id"] == TASK_ID
    assert r.last_abort["waypoint_index"] == 0
    assert r.last_abort["retry"] == DEVICE_MAX_RETRY

    # busy 已释放：这正是加看门狗的目的——后续任务不再被 409 拒绝
    assert r.接收巡检任务(load_payload())["accepted"] is True
    assert r.last_abort is None      # 新任务开始，中止记录清空


def test_move_watchdog_ignores_slow_but_steady_move(tmp_path):
    """慢速但持续走行不会被误判：看门狗看的是"无进展"而不是绝对时长。"""
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")

    slow = {
        "floor": 1, "id": "s" * 32, "name": "慢速走行", "plan": "p",
        "waypoint": [
            {"id": "w1", "index": 1, "pose": {"point": {"x": 5.0, "y": 0, "z": 0}},
             "action": [{"id": "a1", "type": 1}]},
        ],
    }
    r.接收巡检任务(slow)
    until(r, clk, "移动到航点")
    pump(r, clk, 2)
    assert len(goto_frames(r)) == 1

    # 每拍只前进 1cm（0.01 m/s）：整段耗时远超一个看门狗窗口，但一直在动
    ticks = 0
    while r.sm.leaf_state() == "移动到航点":
        ticks += 1
        assert ticks < 2000, "慢速走行被看门狗误判或未推进"
        feed_chassis(r, messages.CHASSIS_RUNNING, min(5.0, 0.01 * ticks))
        clk.t += 1.0
        r.sm.tick()

    assert ticks > DEVICE_STALL_SEC * 2      # 确实跨过了多个窗口
    assert len(goto_frames(r)) == 1             # 从未重发
    assert r.state.insp.move_watch.retry == 0


def test_aborted_progress_is_not_resumed_as_other_inspection(tmp_path):
    """中止保留的断点，在接收新巡检时被清掉——否则新巡检跑完后残留会被开机续跑误捡。"""
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")
    r.接收巡检任务(load_payload())
    until(r, clk, "移动到航点")
    pump(r, clk, 2)
    pump_until(r, clk, lambda: r.sm.leaf_state() == "空闲", what="走行卡住后中止")

    aborted = tmp_path / f"{TASK_ID}.progress.json"
    assert aborted.exists()   # 中止是"这次先不跑了"，断点留着

    # 另一次巡检（不同 id）：接收时清掉中止残留，避免"单槽断点"被旧文件占住
    other = {
        "floor": 1, "id": "b" * 32, "name": "第二次", "plan": "p",
        "waypoint": [
            {"id": "w1", "index": 1, "pose": {"point": {"x": 1.0, "y": 0, "z": 0}},
             "action": [{"id": "a1", "type": 1}]},
        ],
    }
    assert r.接收巡检任务(other)["accepted"] is True
    assert not aborted.exists()

    until(r, clk, "移动到航点")
    drive_inspection(r, clk)
    until(r, clk, "空闲")
    assert not (tmp_path / f"{'b' * 32}.progress.json").exists()

    # 重启：无断点可续，直接空闲
    r2, clk2 = make_robot(tmp_path)
    r2.sm.start()
    until(r2, clk2, "空闲")
    assert r2.巡检进行中 is False


# --------------------------------------------------------------------------- #
# detectType：动作点数据怎么作用到检测
#
# 老巡检任务没有这个键，语义上就是 platform（= 数据走 cmd=104 上传平台，由平台
# 处理检测）。所以"缺省值"不是随手挑的，它就是旧版行为本身，改了就是破坏兼容。
# --------------------------------------------------------------------------- #
def one_floor_payload(detect_type=None, floor=1, iid=None, key="detectType"):
    """单楼层单航点单动作的巡检载荷。

    ``detect_type`` 为 ``None`` 时**不写这个键**，用来模拟旧数据；``key`` 可切成
    蛇形 ``detect_type``（后端两边都认）。
    """
    seg = {
        "floor": floor,
        "id": iid or "c" * 32,
        "name": "detectType 测试",
        "plan": "p",
        "waypoint": [
            {"id": "w1", "index": 1, "pose": {"point": {"x": 1.0, "y": 0, "z": 0}},
             "action": [{"id": "a1", "type": 1}]},
        ],
    }
    if detect_type is not None:
        seg[key] = detect_type
    return [seg]


def test_detect_type_defaults_to_platform_when_absent(tmp_path):
    """旧数据缺 detectType：按 platform 处理，不报错。"""
    task = InspectionTask.from_payload(one_floor_payload())
    assert task.detect_type == DETECT_TYPE_PLATFORM

    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")
    result = r.接收巡检任务(one_floor_payload())

    assert result["accepted"] is True
    assert result["detect_type"] == DETECT_TYPE_PLATFORM
    assert r.state.insp.detect_type == DETECT_TYPE_PLATFORM
    # 落盘记录顶层提一份，翻记录时不用去 floors 里逐段找
    rec = json.loads((tmp_path / f"{'c' * 32}.json").read_text(encoding="utf-8"))
    assert rec["detect_type"] == DETECT_TYPE_PLATFORM


def test_detect_type_fms_reaches_state_and_record(tmp_path):
    """fms：动作数据由 FMS 自己的执行器消化，一路透传到状态和落盘记录。"""
    task = InspectionTask.from_payload(one_floor_payload("fms"))
    assert task.detect_type == DETECT_TYPE_FMS

    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")
    result = r.接收巡检任务(one_floor_payload("fms"))

    assert result["detect_type"] == DETECT_TYPE_FMS
    assert r.state.insp.detect_type == DETECT_TYPE_FMS
    rec = json.loads((tmp_path / f"{'c' * 32}.json").read_text(encoding="utf-8"))
    assert rec["detect_type"] == DETECT_TYPE_FMS
    # 原始分段里也要留着（落盘无损，重建任务才能回解出同一个值）
    assert rec["floors"][0]["detectType"] == "fms"


def test_detect_type_normalizes_snake_case_and_rejects_unknown():
    """蛇形键与大小写都认；认不出来的值回落 platform，不让整份任务加载失败。"""
    assert InspectionTask.from_payload(one_floor_payload("fms", key="detect_type")).detect_type == DETECT_TYPE_FMS
    assert InspectionTask.from_payload(one_floor_payload("FMS")).detect_type == DETECT_TYPE_FMS
    assert InspectionTask.from_payload(one_floor_payload(" Platform ")).detect_type == DETECT_TYPE_PLATFORM
    # 未知值（含写错成 robot 的）：回落旧版行为并告警，不抛异常
    assert InspectionTask.from_payload(one_floor_payload("robot")).detect_type == DETECT_TYPE_PLATFORM
    assert InspectionTask.from_payload(one_floor_payload("")).detect_type == DETECT_TYPE_PLATFORM


def test_detect_type_conflicting_floors_use_first_segment():
    """各楼层段不一致时以第一个段为准并告警，不猜哪个更"特殊"。"""
    segs = one_floor_payload("fms", floor=1) + one_floor_payload("platform", floor=2)
    task = InspectionTask.from_payload(segs)
    assert task.floor_count == 2
    assert task.detect_type == DETECT_TYPE_FMS


def test_detect_type_survives_resume_from_progress(tmp_path):
    """续跑时 detect_type 要从落盘记录回解——中止清过状态，不回解会退回 platform。"""
    r, clk = make_robot(tmp_path)
    r.sm.start()
    until(r, clk, "空闲")
    r.接收巡检任务(one_floor_payload("fms"))
    assert r.state.insp.detect_type == DETECT_TYPE_FMS

    # 手工落一个"走到一半"的断点，换一台机器人（= 重启）从断点恢复
    prog = tmp_path / f"{'c' * 32}.progress.json"
    prog.write_text(json.dumps({"inspection_id": "c" * 32, "waypoint_index": 0}),
                    encoding="utf-8")

    r2, _ = make_robot(tmp_path)
    assert r2.检查未完成的任务() is True
    assert r2.state.insp.detect_type == DETECT_TYPE_FMS
