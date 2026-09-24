"""挂轨控制板模拟器（开发/联调/端到端验证）。

在本地起一个 TCP 服务端扮演"控制板"。后端 RailClient 作为上位机连上来后：

- 回应心跳 0x06（同序号、空 payload），避免 BoardSrv 判定心跳丢失
- 周期上发 0x0B 底盘状态（state 0空闲/1运行/2已到达，x 为弧长 mm）
- 收到 0x09 底盘运动指令时模拟走行：按 ``--speed`` 逼近 target_x，到位后上报 2(已到达)
  - mode=5(GOTO) 绝对位置移动；mode=1/2 点动；mode=0 停车
  - 接受 GOTO 后立即上报一次"运行"，使"运行 → 已到达"构成到位上升沿
- 周期上发 0x0E 电机状态，收到 0x0C 时模拟伸缩杆升降：按 ``--lift-speed`` 逼近 coord，
  到位后上报 2(已到位)
  - mode=3(GOTO) 指定高度；mode=1/2 展开/收缩（按 ±1000mm 简化）；mode=0 停；mode=4 复位

故障注入：
- ``--silent-after-goto N`` 收到第 N 次 GOTO 后彻底静默（验证"设备失联"看门狗）
- ``--lift-stuck`` 升降机构卡死（收 0x0C 但不动、不报到位）

用途：没有真机时联调后端巡检/充电等依赖"到位事件"的状态机流程。

用法::

    python scripts/sim_board.py                    # 监听 127.0.0.1:50000
    python scripts/sim_board.py --speed 8 --x0 0   # 走行速度 m/s、初始弧长 m
    python scripts/sim_board.py --lift-stuck       # 注入升降卡死
"""
from __future__ import annotations

import argparse
import asyncio
import logging
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from app.rail import messages                      # noqa: E402
from app.simulation.protocol import (              # noqa: E402
    FrameParser, decode_frame, encode_frame,
)

logger = logging.getLogger("sim.board")

# 状态上发周期（秒）
UPLOAD_INTERVAL = 0.1


class SimBoard:
    """一台挂轨控制板的简化模型（单客户端）。"""

    def __init__(self, speed_mps: float = 6.0, x0_mm: float = 0.0,
                 silent_after_goto: int = 0, lift_speed_mmps: float = 200.0) -> None:
        self.x = float(x0_mm)                  # 当前弧长 mm
        self.target = float(x0_mm)             # 目标弧长 mm
        self.state = messages.CHASSIS_IDLE
        self.jog_dir = 0                       # 点动方向：+1 向前 / -1 向后 / 0 无
        self.speed = max(1.0, speed_mps * 1000.0)   # mm/s
        self._seq = 0
        # 故障注入：收到第 N 次 GOTO 后彻底静默（不上发 0x0B/0x0E、不回心跳、不处理指令），
        # 用于验证上位机"设备无进展看门狗"——控制板失联时不能无限等到位。0 = 不注入。
        self.silent_after_goto = int(silent_after_goto)
        self.goto_count = 0
        self.silent = False
        # 伸缩杆（升降，motor_id=1）：0x0C 控制 → 0x0E 状态上发
        self.lift_coord = 0.0
        self.lift_target = 0.0
        self.lift_state = messages.MOTOR_ST_IDLE
        self.lift_speed = max(1.0, float(lift_speed_mmps))
        self.lift_stuck = False                # 故障注入：升降机构卡死（收指令但不动）

    # ------------------------------------------------------------ 指令处理
    def on_frame(self, frame: bytes, writer: asyncio.StreamWriter) -> None:
        if self.silent:
            return                             # 静默：模拟控制板失联
        decoded = decode_frame(frame)
        if decoded is None:
            logger.warning("控制板: 收到坏帧，已丢弃")
            return
        seq, _marker, cmd, payload = decoded

        if cmd == messages.CMD_HEARTBEAT:
            writer.write(encode_frame(seq, cmd))
            return

        if cmd == messages.CMD_MOTOR_CTRL:
            self._on_motor_ctrl(payload, writer)
            return

        if cmd == messages.CMD_CHASSIS_MOVE:
            try:
                m = messages.ChassisMove.from_bytes(payload)
            except ValueError as e:
                logger.warning("控制板: 0x09 负载异常 %s", e)
                return
            if m.mode == messages.MOVE_GOTO:
                self.goto_count += 1
                if self.silent_after_goto and self.goto_count >= self.silent_after_goto:
                    self.silent = True
                    logger.warning("控制板: 收到第 %d 次 GOTO，进入静默（模拟失联）",
                                   self.goto_count)
                    return
                self.target = float(m.target_x)
                self.jog_dir = 0
                self.state = messages.CHASSIS_RUNNING
                logger.info("控制板: GOTO x=%.0fmm（当前 %.0fmm）", self.target, self.x)
                # 立即上报"运行"，保证后续"已到达"是上升沿
                self._upload(writer)
            elif m.mode in (messages.MOVE_FORWARD, messages.MOVE_BACKWARD):
                self.jog_dir = 1 if m.mode == messages.MOVE_FORWARD else -1
                self.speed = max(1.0, float(m.linear_x) or self.speed)
                self.state = messages.CHASSIS_RUNNING
                self._upload(writer)
            elif m.mode == messages.MOVE_STOP:
                self.jog_dir = 0
                self.state = messages.CHASSIS_IDLE
                logger.info("控制板: STOP @ x=%.0fmm", self.x)
                self._upload(writer)
            else:
                logger.info("控制板: 忽略 0x09 mode=%s（模拟器未建模）", m.mode)
            return

        # 其余下发指令（0x01/0x02/…）模拟器统一回 2B 错误码 0
        logger.info("控制板: 指令 0x%02X 回错误码 0", cmd)
        writer.write(encode_frame(seq, cmd, b"\x00\x00"))

    # ------------------------------------------------------------ 伸缩杆
    def _on_motor_ctrl(self, payload: bytes, writer: asyncio.StreamWriter) -> None:
        try:
            m = messages.MotorCtrl.from_bytes(payload)
        except ValueError as e:
            logger.warning("控制板: 0x0C 负载异常 %s", e)
            return
        if m.motor_id != 1:
            logger.info("控制板: 忽略电机 %d（模拟器只建模 1=伸缩杆）", m.motor_id)
            return
        if self.lift_stuck:
            logger.warning("控制板: 伸缩杆卡死中，忽略 0x0C mode=%s", m.mode)
            return
        if m.mode == messages.MOTOR_GOTO:
            self.lift_target = float(m.coord)
            self.lift_state = messages.MOTOR_ST_RUNNING
            logger.info("控制板: 伸缩杆 GOTO %.0fmm（当前 %.0fmm）",
                        self.lift_target, self.lift_coord)
            # 立即上报"运行"，保证后续"已到位"是上升沿
            self._upload_motor(writer)
        elif m.mode == messages.MOTOR_RESET:
            self.lift_target = 0.0
            self.lift_state = messages.MOTOR_ST_RUNNING
            self._upload_motor(writer)
        elif m.mode in (messages.MOTOR_UP, messages.MOTOR_DOWN):
            # 点动：模拟器按 ±1000mm 行程简化处理
            delta = 1000.0 if m.mode == messages.MOTOR_UP else -1000.0
            self.lift_target = self.lift_coord + delta
            self.lift_state = messages.MOTOR_ST_RUNNING
            self._upload_motor(writer)
        elif m.mode == messages.MOTOR_STOP:
            self.lift_state = messages.MOTOR_ST_IDLE
            self._upload_motor(writer)
        else:
            logger.info("控制板: 忽略 0x0C mode=%s（模拟器未建模）", m.mode)

    def _step_lift(self, dt: float) -> None:
        if self.lift_state != messages.MOTOR_ST_RUNNING:
            return
        step = self.lift_speed * dt
        delta = self.lift_target - self.lift_coord
        if abs(delta) <= step:
            self.lift_coord = self.lift_target
            self.lift_state = messages.MOTOR_ST_ARRIVED
            logger.info("控制板: 伸缩杆已到位 %.0fmm", self.lift_coord)
        else:
            self.lift_coord += step if delta > 0 else -step

    def _upload_motor(self, writer: asyncio.StreamWriter) -> None:
        self._seq = (self._seq + 1) & 0xFFFF
        msg = messages.MotorState(
            error_code=0, motor_id=1, state=self.lift_state,
            speed=int(self.lift_speed) if self.lift_state == messages.MOTOR_ST_RUNNING else 0,
            coord=int(round(self.lift_coord)))
        writer.write(encode_frame(self._seq, messages.CMD_UPLOAD_MOTOR, msg.to_bytes()))

    # ------------------------------------------------------------ 周期推进
    def step(self, dt: float) -> None:
        self._step_lift(dt)
        if self.state != messages.CHASSIS_RUNNING:
            return
        step = self.speed * dt
        if self.jog_dir:
            self.x += self.jog_dir * step
            return
        delta = self.target - self.x
        if abs(delta) <= step:
            self.x = self.target
            self.state = messages.CHASSIS_ARRIVED
            logger.info("控制板: 已到达 x=%.0fmm", self.x)
        else:
            self.x += step if delta > 0 else -step

    def _upload(self, writer: asyncio.StreamWriter) -> None:
        self._seq = (self._seq + 1) & 0xFFFF
        msg = messages.ChassisState(state=self.state, x=int(round(self.x)))
        writer.write(encode_frame(self._seq, messages.CMD_UPLOAD_CHASSIS, msg.to_bytes()))

    # ------------------------------------------------------------ 连接处理
    async def handle(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        peer = writer.get_extra_info("peername")
        logger.info("控制板: 上位机已连接 %s", peer)
        parser = FrameParser()

        async def upload_loop() -> None:
            while True:
                await asyncio.sleep(UPLOAD_INTERVAL)
                if self.silent:
                    continue
                self.step(UPLOAD_INTERVAL)
                self._upload(writer)
                self._upload_motor(writer)
                await writer.drain()

        task = asyncio.create_task(upload_loop())
        try:
            while True:
                data = await reader.read(4096)
                if not data:
                    logger.info("控制板: 上位机关闭连接 %s", peer)
                    break
                for frame in parser.feed(data):
                    self.on_frame(frame, writer)
                await writer.drain()
        except (ConnectionResetError, asyncio.CancelledError):
            pass
        finally:
            task.cancel()
            try:
                writer.close()
                await writer.wait_closed()
            except Exception:
                pass
            logger.info("控制板: 连接结束 %s", peer)


async def main() -> None:
    ap = argparse.ArgumentParser(description="挂轨控制板模拟器")
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--port", type=int, default=50000)
    ap.add_argument("--speed", type=float, default=6.0, help="走行速度 m/s（默认 6）")
    ap.add_argument("--x0", type=float, default=0.0, help="初始弧长 m（默认 0）")
    ap.add_argument("--silent-after-goto", type=int, default=0, metavar="N",
                    help="收到第 N 次 GOTO 后静默，模拟控制板失联（默认 0=不静默）")
    ap.add_argument("--lift-speed", type=float, default=200.0, help="伸缩杆速度 mm/s（默认 200）")
    ap.add_argument("--lift-stuck", action="store_true",
                    help="模拟升降机构卡死：收 0x0C 但不动、不报到位")
    args = ap.parse_args()

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s %(levelname)s %(name)s %(message)s",
    )
    board = SimBoard(speed_mps=args.speed, x0_mm=args.x0 * 1000.0,
                     silent_after_goto=args.silent_after_goto,
                     lift_speed_mmps=args.lift_speed)
    board.lift_stuck = args.lift_stuck
    server = await asyncio.start_server(board.handle, args.host, args.port)
    logger.info("控制板模拟器已启动 %s:%s（速度 %.1f m/s，初始 %.1f m）",
                args.host, args.port, args.speed, args.x0)
    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
