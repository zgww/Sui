"""端到端验证：整条巡检链路（航点走行 → 动作 → 下一航点 → 巡检完成）+ 断点续跑。

不依赖真机：本脚本自己起一块控制板模拟器（见 sim_board.py），把真实 Robot
（真 RailClient + 真协议帧 + 真状态机）接上去，下发真实巡检任务 JSON，
然后按节拍观察状态机推进，最后判定覆盖情况。

覆盖点：
- "移动到航点" 是否真的复用 goto 下发（0x09 mode=5，target_x = 航点 pose.point.x）
- 控制板 0x0B 到位上升沿是否驱动 insp 进入 "动作点开始"
- 航点 / 动作游标是否按任务数据顺序推进（不漏不重）
- 巡检完成后任务是否清空、是否回 "空闲"、能否再次接收新任务
- ``--crash-after N``：完成第 N 个航点后模拟掉电，再用同一落盘目录新建 Robot，
  验证开机自动从断点航点续跑并跑完剩余部分
- ``--board-silent-after-goto N``：控制板收到第 N 次 GOTO 后彻底静默（失联），
  验证走行看门狗重发 goto → 重试耗尽 → 停车中止 → 释放 busy → 保留断点

用法::

    python scripts/e2e_rail_inspection.py
    python scripts/e2e_rail_inspection.py --crash-after 2               # 额外验证断点续跑
    python scripts/e2e_rail_inspection.py --board-silent-after-goto 1   # 额外验证走行看门狗
    python scripts/e2e_rail_inspection.py --port 50001 --speed 20

注意：后端进程的仿真桥占用 50000，并行验证时用 ``--port`` 换端口
（脚本会在构造 Robot 前把 RobotConfig.port 改到该端口）。
"""
from __future__ import annotations

import argparse
import asyncio
import json
import logging
import shutil
import sys
import tempfile
import time
from dataclasses import dataclass, field
from pathlib import Path

BACKEND = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(BACKEND))
sys.path.insert(0, str(BACKEND / "scripts"))

import app.prefab  # noqa: E402,F401  触发节点类型注册（含 nodes.robot.RobotConfig）
from app.prefab.nodes.robot import RobotConfig  # noqa: E402
from app.prefab.registry import build  # noqa: E402
from app.rail import messages  # noqa: E402
from app.rail.inspection import InspectionTask  # noqa: E402
from app.rail.robot import INSPECTION_PROGRESS_SUFFIX, Robot, _find_node  # noqa: E402
from sim_board import SimBoard  # noqa: E402

DEFAULT_PREFAB = BACKEND / "data" / "prefabs" / "robot.prefab.json"
DEFAULT_TASK = BACKEND / "tests" / "test_inspection.json"


@dataclass
class RunResult:
    """一次驱动的观测结果。"""

    finished: bool = False
    seen_wp: set = field(default_factory=set)
    seen_act: set = field(default_factory=set)
    leaf: str = ""
    path: str = ""
    busy: bool = False
    got_x: list = field(default_factory=list)


def goto_targets(sent: list) -> list[int]:
    """已下发帧里的 goto 目标（协议 mm）。"""
    return [m.target_x for m in sent
            if isinstance(m, messages.ChassisMove) and m.mode == messages.MOVE_GOTO]


class FakePtz:
    """假云台：立即"到位"，不连真机相机。

    必须注入——``Robot`` 未注入 ``ptz_provider`` 时会回退全局 ``get_hkptz()``，
    真的去连现场相机（192.168.6.170）。后果不是报错而是**静默变慢**：每个云台动作
    都要在 ``_ptz_worker`` 里轮询到 ``PTZ_SETTLE_TIMEOUT_SEC=15s`` 才超时放行，
    34 个动作 ≈ 多耗 8.5 分钟，脚本会误判成"巡检跑不完"。
    """

    def absolute_move(self, pan, tilt, zoom=1.0, **kw):
        self.last = (pan, tilt, zoom)

    def ptz_status(self):
        pan, tilt, zoom = getattr(self, "last", (0.0, 0.0, 1.0))
        return {"pan": pan, "tilt": tilt, "zoom": zoom}


class FakeVision:
    """假视觉：在结果目录写占位 JPEG 并立即返回，不连真机相机。

    同 ``FakePtz``：不注入就会去连现场相机（真机为单可见光设备，测温动作会白跑）。
    """

    def capture_visible(self, ctx):
        return self._snap("visible", ctx)

    def full_thermometry(self, ctx):
        return self._snap("thermometry", ctx)

    def _snap(self, kind, ctx):
        from app.rail.vision import VisionResult
        d = Path(ctx["result_dir"])
        d.mkdir(parents=True, exist_ok=True)
        p = d / f"{ctx['file_stem']}_{kind}.jpg"
        p.write_bytes(b"\xff\xd8\xff\xe0fake-jpeg")
        return VisionResult(kind=kind, ok=True, path=str(p))


def build_robot(prefab: Path, port: int, inspection_dir: Path,
                stall_sec: float | None = None, max_retry: int | None = None):
    """按 prefab 构造 Robot（端口改到模拟器），并拦截下发给控制板的帧。

    真实 BoardSrv 不保留发送历史，核对 goto 需自己包一层 ``board.send``。
    ``stall_sec`` / ``max_retry`` 为 None 时用 robot.py 里的默认值。
    """
    spec = json.loads(prefab.read_text(encoding="utf-8"))
    root = build(spec["root"])
    _find_node(root, RobotConfig).port = port
    extra: dict = {}
    if stall_sec is not None:
        extra["device_stall_sec"] = stall_sec
    if max_retry is not None:
        extra["device_max_retry"] = max_retry
    r = Robot(prefab_root=root, tick_interval=0.02, inspection_dir=inspection_dir,
              ptz_provider=lambda: FakePtz(), vision_provider=lambda: FakeVision(),
              **extra)
    sent: list = []
    raw_send = r.board.send

    def spy_send(msg):
        sent.append(msg)
        raw_send(msg)

    r.board.send = spy_send
    return r, sent


async def wait_online(r, timeout: float = 10.0) -> bool:
    deadline = time.time() + timeout
    while time.time() < deadline:
        if r.state.online:
            return True
        await asyncio.sleep(0.1)
    return False


async def drive(r, sent, stop_after_wp: int | None = None,
                timeout: float = 300.0) -> RunResult:
    """驱动巡检推进；``stop_after_wp`` 非 None 时在取到该航点后立即停下（模拟掉电）。"""
    res = RunResult()
    arrived = 0
    started = time.time()
    last_key = None
    while time.time() - started < timeout:
        insp = r.state.insp
        if insp.current_waypoint_id:
            res.seen_wp.add(insp.current_waypoint_id)
        if insp.current_action_id:
            res.seen_act.add(insp.current_action_id)
        key = (r.sm.leaf_state(), insp.waypoint_cursor, insp.current_action_index)
        if key != last_key:
            last_key = key
            print(f"[e2e] {'/'.join(r.sm.state_path())} floor={insp.current_floor} "
                  f"wp={insp.waypoint_cursor} act={insp.action_cursor} "
                  f"x={r.state.pose.x:.3f}/{insp.target_x_m} "
                  f"wp_seen={len(res.seen_wp)} act_seen={len(res.seen_act)}")
        if stop_after_wp is not None and insp.waypoint_cursor > stop_after_wp:
            break
        if not r.巡检进行中:
            res.finished = True
            break
        await asyncio.sleep(0.02)

    if res.finished:
        for _ in range(40):          # 等主机迁回空闲
            if r.sm.leaf_state() == "空闲":
                break
            await asyncio.sleep(0.05)
    # stop() 会清空状态，快照必须取在此之前
    res.leaf = r.sm.leaf_state()
    res.path = "/".join(r.sm.state_path())
    res.busy = r.巡检进行中
    res.got_x = goto_targets(sent)
    return res


async def run(args: argparse.Namespace) -> int:
    payload = json.loads(Path(args.task).read_text(encoding="utf-8"))
    merged = InspectionTask.from_payload(payload)
    expect_x = [int(round(w.pose.point.x * 1000)) for _, w in merged.waypoints]
    all_wp_ids = {w.id for _, w in merged.waypoints}
    all_act_ids = {a.id for _, w in merged.waypoints for a in w.action}
    total_wp, total_act = merged.waypoint_count, merged.action_count

    # 看门狗参数：默认用 robot.py 里的值；故障注入模式下默认短窗口（否则要等 3 分钟）
    watchdog_mode = bool(args.board_silent_after_goto)
    stall_sec = args.stall_sec if args.stall_sec is not None else (2.0 if watchdog_mode else None)
    max_retry = args.max_retry if args.max_retry is not None else (1 if watchdog_mode else None)

    # 1) 控制板模拟器
    board = SimBoard(speed_mps=args.speed, x0_mm=args.x0 * 1000.0,
                     silent_after_goto=args.board_silent_after_goto)
    server = await asyncio.start_server(board.handle, args.host, args.port)
    print(f"[e2e] 控制板模拟器 127.0.0.1:{args.port}（速度 {args.speed} m/s）")

    # 落盘到系统临时目录，不污染 backend/data/inspection
    tmp_dir = Path(tempfile.mkdtemp(prefix="e2e_inspection_"))
    prefab = Path(args.prefab)
    checks: dict[str, bool] = {}
    try:
        # ---------------- 阶段 1：下发并推进（可选中途掉电） ----------------
        r, sent = build_robot(prefab, args.port, tmp_dir, stall_sec, max_retry)
        await r.start()
        if not await wait_online(r):
            print("[e2e] 结果: FAIL（控制板未连上）")
            return 1
        print(f"[e2e] 控制板在线={r.state.online} status={r.state.board_status}")

        result = r.接收巡检任务(payload)
        print(f"[e2e] 下发结果: {json.dumps(result, ensure_ascii=False)}")
        if not result.get("accepted"):
            print("[e2e] 结果: FAIL（任务未被接收）")
            return 1

        phase1 = await drive(r, sent, stop_after_wp=args.crash_after)
        await r.stop()

        if watchdog_mode:
            # ---------------- 故障注入：控制板失联 → 走行看门狗中止 ----------------
            prog_file = tmp_dir / f"{merged.inspection_id}{INSPECTION_PROGRESS_SUFFIX}"
            prog = json.loads(prog_file.read_text(encoding="utf-8")) if prog_file.exists() else {}
            stops = [m for m in sent
                     if isinstance(m, messages.ChassisMove) and m.mode == messages.MOVE_STOP]
            expect_goto = 1 + (max_retry if max_retry is not None else 0)
            print(f"[e2e] 控制板在收到第 {board.goto_count} 次 GOTO 后静默；"
                  f"共下发 goto {len(phase1.got_x)} 次、停车 {len(stops)} 次；"
                  f"断点={json.dumps(prog, ensure_ascii=False)}")
            abort = dict(r.last_abort or {})     # 接收新任务会清掉，先快照
            can_again = r.接收巡检任务(payload).get("accepted") is True
            checks.update({
                "控制板已进入静默": board.silent,
                "看门狗重发 goto 到上限": len(phase1.got_x) == expect_goto,
                "重发目标与航点 X 一致": phase1.got_x == [expect_x[0]] * expect_goto,
                "中止时已停车": len(stops) >= 1,
                "中止后释放 busy": phase1.busy is False,
                "中止后回空闲": phase1.leaf == "空闲",
                "中止保留断点": prog.get("waypoint_index") == 0,
                "中止原因已记录": abort.get("reason") == "move_stalled",
                "可再接收新任务": can_again,
            })
        elif args.crash_after is None:
            # 先取快照再复检（复检会再下发一次任务、重新写出断点）
            prog_gone = not (tmp_dir / f"{merged.inspection_id}"
                             f"{INSPECTION_PROGRESS_SUFFIX}").exists()
            can_again = r.接收巡检任务(payload).get("accepted") is True
            checks.update({
                "巡检跑完": phase1.finished,
                "航点全覆盖": phase1.seen_wp == all_wp_ids,
                "动作全覆盖": phase1.seen_act == all_act_ids,
                "每航点一次 goto": len(phase1.got_x) == total_wp,
                "goto 目标与航点 X 一致": phase1.got_x == expect_x,
                "结束回空闲": phase1.leaf == "空闲",
                "断点已删除": prog_gone,
                "可再接收新任务": can_again,
            })
        else:
            # ---------------- 阶段 2：模拟掉电重启后续跑 ----------------
            crash = args.crash_after
            prog_file = tmp_dir / f"{merged.inspection_id}{INSPECTION_PROGRESS_SUFFIX}"
            prog = json.loads(prog_file.read_text(encoding="utf-8")) if prog_file.exists() else {}
            print(f"[e2e] 阶段1 在航点 {crash} 掉电；断点={json.dumps(prog, ensure_ascii=False)}")

            r2, sent2 = build_robot(prefab, args.port, tmp_dir, stall_sec, max_retry)
            await r2.start()
            if not await wait_online(r2):
                print("[e2e] 结果: FAIL（重启后控制板未连上）")
                return 1
            resumed = r2.巡检进行中 and r2.state.insp.current_inspection_id == merged.inspection_id
            # 开机即进巡检，断点航点由"航点开始"重新取出
            await asyncio.sleep(0.5)
            print(f"[e2e] 重启后: busy={r2.巡检进行中} "
                  f"state={'/'.join(r2.sm.state_path())} "
                  f"wp={r2.state.insp.waypoint_cursor} "
                  f"target_x={r2.state.insp.target_x_m}")

            phase2 = await drive(r2, sent2)
            await r2.stop()

            resumed_targets = phase2.got_x
            prog_gone = not prog_file.exists()
            can_again = r2.接收巡检任务(payload).get("accepted") is True
            checks.update({
                "掉电时断点已落盘": prog.get("waypoint_index") == crash,
                "重启后自动进巡检": resumed,
                "从断点航点续跑": resumed_targets == expect_x[crash:],
                "两阶段航点全覆盖": (phase1.seen_wp | phase2.seen_wp) == all_wp_ids,
                "两阶段动作全覆盖": (phase1.seen_act | phase2.seen_act) == all_act_ids,
                "续跑后巡检完成": phase2.finished and phase2.leaf == "空闲",
                "完成后断点已删除": prog_gone,
                "可再接收新任务": can_again,
            })
    finally:
        server.close()
        await server.wait_closed()
        shutil.rmtree(tmp_dir, ignore_errors=True)

    for name, ok in checks.items():
        print(f"[e2e]   {'✓' if ok else '✗'} {name}")
    ok = bool(checks) and all(checks.values())
    print("[e2e] 结果:", "PASS" if ok else "FAIL")
    return 0 if ok else 1


def main() -> int:
    ap = argparse.ArgumentParser(description="挂轨巡检链路端到端验证")
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--port", type=int, default=50001,
                    help="控制板模拟器端口（避开后端仿真桥占用的 50000）")
    ap.add_argument("--speed", type=float, default=20.0, help="模拟走行速度 m/s")
    ap.add_argument("--x0", type=float, default=0.0, help="初始弧长 m")
    ap.add_argument("--prefab", default=str(DEFAULT_PREFAB))
    ap.add_argument("--task", default=str(DEFAULT_TASK), help="巡检任务 JSON")
    ap.add_argument("--timeout", type=float, default=300.0, help="单阶段超时秒")
    ap.add_argument("--crash-after", type=int, default=None, metavar="N",
                    help="完成第 N 个航点后模拟掉电，再验证断点续跑（默认不启用）")
    ap.add_argument("--board-silent-after-goto", type=int, default=0, metavar="N",
                    help="控制板收到第 N 次 GOTO 后静默，验证走行看门狗中止（默认 0=不启用）")
    ap.add_argument("--stall-sec", type=float, default=None,
                    help="走行看门狗无进展窗口秒（默认用 robot.py 里的值）")
    ap.add_argument("--max-retry", type=int, default=None,
                    help="走行看门狗重发 goto 次数上限（默认用 robot.py 里的值）")
    args = ap.parse_args()
    logging.basicConfig(level=logging.WARNING,
                        format="%(asctime)s %(levelname)s %(name)s %(message)s")
    return asyncio.run(run(args))


if __name__ == "__main__":
    raise SystemExit(main())
