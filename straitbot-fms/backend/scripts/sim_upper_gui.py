# -*- coding: utf-8 -*-
"""PySide6 图形化上位机 — 机器人控制板通信协议 V2.0 (对接后端 50000 仿真桥)。

功能:
    1. 输入 IP / 端口(默认 127.0.0.1:50000) 连接下位机(仿真桥 TCP 服务端)
    2. 底盘运动控制(0x09): 前进 / 后退 / 停止 / 移动到指定弧长 / 设定速度 / 初始化复位
    3. 伸缩杆控制(0x0C): 上升 / 下降 / 停止 / 伸缩到指定高度 / 复位 / 设定速度
    4. 系统指令: 心跳(0x06) / 查询底盘状态(0x0A) / 查询电机状态(0x0D)
    5. 实时接收并显示: 底盘状态上传(0x0B) / 电机状态上传(0x0E)

用法:
    python scripts/sim_upper_gui.py          # 启动图形界面
    python scripts/sim_upper_gui.py --selftest   # 无界面自测(offscreen, 自动连接+发指令+验证接收)

依赖: PySide6 (pip install PySide6)
"""
import argparse
import socket
import struct
import sys
import time

try:
    from PySide6.QtCore import QThread, Signal, Qt
    from PySide6.QtGui import QFont
    from PySide6.QtWidgets import (
        QApplication, QWidget, QLabel, QLineEdit, QSpinBox, QPushButton,
        QGroupBox, QGridLayout, QHBoxLayout, QVBoxLayout, QPlainTextEdit,
        QFrame, QSizePolicy,
    )
except ImportError:  # pragma: no cover
    sys.stderr.write("缺少 PySide6, 请先安装: pip install PySide6\n")
    raise

# ---------------- 协议层 (与 backend/app/simulation/protocol.py 同规格) ----------------
HEAD, TAIL = 0xA0AB, 0xCD
HEADER_LEN, CRC_LEN = 8, 2
MAX_PAYLOAD = 4096

CMD = {
    "INIT": 0x01, "GET_CONFIG": 0x02, "REBOOT": 0x03, "GET_VERSION": 0x04,
    "TIME_SYNC": 0x05, "HEARTBEAT": 0x06, "MOTOR_POWER": 0x07,
    "CHASSIS_MOVE": 0x09, "GET_CHASSIS": 0x0A, "UPLOAD_CHASSIS": 0x0B,
    "MOTOR_CTRL": 0x0C, "GET_MOTOR": 0x0D, "UPLOAD_MOTOR": 0x0E,
}

# 底盘模式(0x09)
MODE_CHASSIS = {0: "停止", 1: "前进", 2: "后退", 5: "到指定位置", 6: "设定速度", 10: "复位"}
# 电机模式(0x0C)
MODE_MOTOR = {0: "停止", 1: "正转(上升)", 2: "反转(下降)", 3: "指定坐标", 4: "复位", 6: "设定速度"}
# 状态
STATE_CHASSIS = {0: "空闲", 1: "运行", 2: "已到达", 3: "初始化"}
STATE_MOTOR = {0: "停止", 1: "运行中", 2: "已到位", 3: "异常"}


def crc16(data: bytes, init: int = 0x0000) -> int:
    """下位机实际算法 CRC-16/KERMIT（反射 poly 0x8408 / init 0），见 app/simulation/protocol.py。"""
    crc = init & 0xFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ 0x8408 if crc & 1 else crc >> 1
    return crc & 0xFFFF


def make_frame(seq: int, cmd: int, payload: bytes = b"") -> bytes:
    payload = bytes(payload)
    body = struct.pack(">HHHBB", HEAD, seq & 0xFFFF, len(payload), 0, cmd & 0xFF) + payload
    return body + struct.pack(">H", crc16(body)) + bytes([TAIL])


def decode_frame(frame: bytes):
    if len(frame) < HEADER_LEN + CRC_LEN + 1 or frame[0] != 0xA0 or frame[1] != 0xAB or frame[-1] != TAIL:
        return None
    _head, seq, mlen, marker, cmd = struct.unpack_from(">HHHBB", frame, 0)
    if mlen > MAX_PAYLOAD or len(frame) != HEADER_LEN + mlen + CRC_LEN + 1:
        return None
    if struct.unpack_from(">H", frame, HEADER_LEN + mlen)[0] != crc16(frame[:HEADER_LEN + mlen]):
        return None
    return seq, marker, cmd, frame[HEADER_LEN:HEADER_LEN + mlen]


def _split_frames(data: bytes) -> list:
    """字节流 → 完整帧列表(联调用简单拆包, 与后端 FrameParser 等价)。"""
    frames, buf = [], data
    while True:
        idx = buf.find(b"\xA0\xAB")
        if idx < 0:
            break
        buf = buf[idx:]
        if len(buf) < HEADER_LEN:
            break
        _h, _s, mlen, _m, _c = struct.unpack_from(">HHHBB", buf, 0)
        if mlen > MAX_PAYLOAD:
            buf = buf[2:]
            continue
        total = HEADER_LEN + mlen + CRC_LEN + 1
        if len(buf) < total:
            break
        fr = buf[:total]
        buf = buf[total:]
        got = decode_frame(fr)
        if got:
            frames.append(got)
    return frames


def i16(b: bytes) -> int:
    return struct.unpack(">h", b)[0]


def u16(b: bytes) -> int:
    return struct.unpack(">H", b)[0]


def i32(b: bytes) -> int:
    return struct.unpack(">i", b)[0]


def chassis_payload(mode: int, speed: int = 0, target: int = 0) -> bytes:
    """0x09 底盘运动控制 payload: 模式(1) LinearX(2) LinearY(2) Angular(2) TargetX(4) TargetY(4) TargetYaw(2)。"""
    return (struct.pack(">B", mode) + struct.pack(">H", speed) + struct.pack(">H", 0)
            + struct.pack(">H", 0) + struct.pack(">i", target) + struct.pack(">i", 0)
            + struct.pack(">h", 0))


def motor_payload(mode: int, speed: int = 100, coord: int = 0) -> bytes:
    """0x0C 电机控制 payload: ID(1,=1 伸缩杆) 模式(1) 速度(2 有符号) 坐标(4)。"""
    return struct.pack(">BB", 1, mode) + struct.pack(">h", speed) + struct.pack(">i", coord)


def fmt_frame(cmd: int, payload: bytes, tx: bool = False) -> str:
    """帧摘要(日志用)。"""
    try:
        if cmd == CMD["HEARTBEAT"]:
            return "心跳 " + ("请求" if tx else "响应") + "(空)"
        if cmd == CMD["CHASSIS_MOVE"]:
            if tx and len(payload) >= 17:
                m, v, t = payload[0], i16(payload[1:3]), i32(payload[7:11])
                return f"底盘 {MODE_CHASSIS.get(m, m)} 速度={v}mm/s 目标={t}mm"
            return f"底盘响应 错误码={u16(payload[:2])}"
        if cmd == CMD["GET_CHASSIS"]:
            if tx:
                return "查询底盘状态"
            err, st, m = u16(payload[:2]), payload[2], payload[3]
            x, y, yaw = i32(payload[4:8]), i32(payload[8:12]), i16(payload[12:14])
            lx, ly, ang = i16(payload[14:16]), i16(payload[16:18]), i16(payload[18:20])
            return (f"底盘状态 状态={STATE_CHASSIS.get(st, st)} 模式={MODE_CHASSIS.get(m, m)} "
                    f"X={x} Y={y} YAW={yaw / 10:.1f}° LinearX={lx} LinearY={ly} Angular={ang}")
        if cmd == CMD["UPLOAD_CHASSIS"]:
            st, m = payload[0], payload[1]
            x, y, yaw = i32(payload[2:6]), i32(payload[6:10]), i16(payload[10:12])
            lx, ly, ang = i16(payload[12:14]), i16(payload[14:16]), i16(payload[16:18])
            return (f"底盘上传 状态={STATE_CHASSIS.get(st, st)} 模式={MODE_CHASSIS.get(m, m)} "
                    f"X={x} Y={y} YAW={yaw / 10:.1f}° LinearX={lx} LinearY={ly} Angular={ang}")
        if cmd == CMD["MOTOR_CTRL"]:
            if tx and len(payload) >= 8:
                mid, m, v, c = payload[0], payload[1], i16(payload[2:4]), i32(payload[4:8])
                return f"电机{mid} {MODE_MOTOR.get(m, m)} 速度={v}mm/s 高度={c}mm"
            return f"电机响应 错误码={u16(payload[:2])}"
        if cmd in (CMD["GET_MOTOR"], CMD["UPLOAD_MOTOR"]):
            if tx:
                return "查询电机状态"
            mid, st = payload[0], payload[1]
            v, h = i16(payload[2:4]), i32(payload[4:8])
            sw, err = u16(payload[8:10]), u16(payload[10:12])
            i1, i2, tmp = i32(payload[12:16]), i32(payload[16:20]), i32(payload[20:24])
            return (f"电机{mid} 状态={STATE_MOTOR.get(st, st)} 速度={v} 高度={h} 状态字={sw} "
                    f"错误码={err} 电流1={i1} 电流2={i2} 温度={tmp}")
        return f"0x{cmd:02X} {'发送' if tx else '接收'} payload={payload.hex()}"
    except Exception:
        return f"0x{cmd:02X} payload={payload.hex()}"


# ---------------- 接收线程 ----------------
class RecvThread(QThread):
    frame_received = Signal(int, int, bytes)   # cmd, seq, payload
    disconnected = Signal(str)

    def __init__(self, sock: socket.socket, parent=None):
        super().__init__(parent)
        self._sock = sock

    def run(self):
        parser_buf = bytearray()
        while True:
            try:
                data = self._sock.recv(4096)
            except OSError as e:
                self.disconnected.emit(f"连接断开: {e}")
                return
            if not data:
                self.disconnected.emit("连接已断开(对端关闭)")
                return
            parser_buf.extend(data)
            # 增量拆包: 半包/粘包/坏帧重同步
            while True:
                idx = parser_buf.find(b"\xA0\xAB")
                if idx < 0:
                    parser_buf.clear()
                    break
                del parser_buf[:idx]
                if len(parser_buf) < HEADER_LEN:
                    break
                _h, _s, mlen, _m, _c = struct.unpack_from(">HHHBB", parser_buf, 0)
                if mlen > MAX_PAYLOAD:
                    del parser_buf[:2]
                    continue
                total = HEADER_LEN + mlen + CRC_LEN + 1
                if len(parser_buf) < total:
                    break
                fr = bytes(parser_buf[:total])
                del parser_buf[:total]
                got = decode_frame(fr)
                if got:
                    self.frame_received.emit(got[2], got[0], got[3])


# ---------------- 主窗口 ----------------
class UpperWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("机器人仿真上位机 (协议 V2.0)")
        self.resize(940, 720)
        self._sock = None
        self._recv_thread = None
        self._seq = 0
        self._build_ui()

    # ---------- UI ----------
    def _build_ui(self):
        root = QVBoxLayout(self)
        root.setContentsMargins(10, 10, 10, 10)
        root.setSpacing(8)

        # 顶部连接栏
        conn = QHBoxLayout()
        conn.addWidget(QLabel("下位机地址"))
        self.ip_edit = QLineEdit("127.0.0.1")
        self.ip_edit.setFixedWidth(130)
        conn.addWidget(self.ip_edit)
        conn.addWidget(QLabel("端口"))
        self.port_edit = QSpinBox()
        self.port_edit.setRange(1, 65535)
        self.port_edit.setValue(50000)
        self.port_edit.setFixedWidth(90)
        conn.addWidget(self.port_edit)
        self.btn_connect = QPushButton("连接")
        self.btn_connect.setFixedWidth(80)
        self.btn_connect.clicked.connect(self._toggle_connect)
        conn.addWidget(self.btn_connect)
        self.lbl_status = QLabel("未连接")
        self.lbl_status.setStyleSheet(
            "color:#A14E50;font-weight:bold;padding:2px 10px;border:1px solid #A14E50;border-radius:4px;")
        conn.addWidget(self.lbl_status)
        conn.addStretch(1)
        root.addLayout(conn)

        body = QHBoxLayout()
        body.setSpacing(8)

        # 左侧: 指令区
        left = QVBoxLayout()
        left.setSpacing(8)

        # --- 底盘控制 ---
        g_chassis = QGroupBox("底盘运动 (0x09)")
        gl = QGridLayout(g_chassis)
        gl.addWidget(QLabel("速度(mm/s)"), 0, 0)
        self.spd_chassis = QSpinBox()
        self.spd_chassis.setRange(0, 3000)
        self.spd_chassis.setValue(300)
        gl.addWidget(self.spd_chassis, 0, 1)
        gl.addWidget(QLabel("目标弧长(mm)"), 0, 2)
        self.target_chassis = QSpinBox()
        self.target_chassis.setRange(0, 30000)
        self.target_chassis.setValue(2000)
        gl.addWidget(self.target_chassis, 0, 3)

        self.btn_fwd = QPushButton("↑ 前进")
        self.btn_back = QPushButton("↓ 后退")
        self.btn_stop = QPushButton("■ 停止")
        self.btn_goto = QPushButton("移动到位置")
        self.btn_setv = QPushButton("设定速度")
        self.btn_reset = QPushButton("初始化复位")
        for b in (self.btn_fwd, self.btn_back, self.btn_stop, self.btn_goto, self.btn_setv, self.btn_reset):
            b.setFixedHeight(34)
            b.setEnabled(False)
        gl.addWidget(self.btn_fwd, 1, 0)
        gl.addWidget(self.btn_back, 1, 1)
        gl.addWidget(self.btn_stop, 1, 2)
        gl.addWidget(self.btn_goto, 2, 0, 1, 2)
        gl.addWidget(self.btn_setv, 2, 2)
        gl.addWidget(self.btn_reset, 2, 3)

        self.btn_fwd.clicked.connect(lambda: self._send_chassis(1, self.spd_chassis.value(), 0))
        self.btn_back.clicked.connect(lambda: self._send_chassis(2, self.spd_chassis.value(), 0))
        self.btn_stop.clicked.connect(lambda: self._send_chassis(0, 0, 0))
        self.btn_goto.clicked.connect(lambda: self._send_chassis(5, self.spd_chassis.value(), self.target_chassis.value()))
        self.btn_setv.clicked.connect(lambda: self._send_chassis(6, self.spd_chassis.value(), 0))
        self.btn_reset.clicked.connect(lambda: self._send_chassis(10, 0, 0))
        left.addWidget(g_chassis)

        # --- 伸缩杆 ---
        g_ext = QGroupBox("伸缩杆 电机1 (0x0C)")
        gl = QGridLayout(g_ext)
        gl.addWidget(QLabel("速度(mm/s)"), 0, 0)
        self.spd_ext = QSpinBox()
        self.spd_ext.setRange(0, 300)
        self.spd_ext.setValue(100)
        gl.addWidget(self.spd_ext, 0, 1)
        gl.addWidget(QLabel("目标高度(mm)"), 0, 2)
        self.target_ext = QSpinBox()
        self.target_ext.setRange(0, 600)
        self.target_ext.setValue(300)
        gl.addWidget(self.target_ext, 0, 3)

        self.btn_ext_up = QPushButton("↑ 上升")
        self.btn_ext_down = QPushButton("↓ 下降")
        self.btn_ext_stop = QPushButton("■ 停止")
        self.btn_ext_goto = QPushButton("伸缩到高度")
        self.btn_ext_reset = QPushButton("复位")
        self.btn_ext_setv = QPushButton("设定速度")
        for b in (self.btn_ext_up, self.btn_ext_down, self.btn_ext_stop, self.btn_ext_goto, self.btn_ext_reset, self.btn_ext_setv):
            b.setFixedHeight(34)
            b.setEnabled(False)
        gl.addWidget(self.btn_ext_up, 1, 0)
        gl.addWidget(self.btn_ext_down, 1, 1)
        gl.addWidget(self.btn_ext_stop, 1, 2)
        gl.addWidget(self.btn_ext_goto, 2, 0, 1, 2)
        gl.addWidget(self.btn_ext_setv, 2, 2)
        gl.addWidget(self.btn_ext_reset, 2, 3)

        self.btn_ext_up.clicked.connect(lambda: self._send_motor(1, self.spd_ext.value(), 0))
        self.btn_ext_down.clicked.connect(lambda: self._send_motor(2, self.spd_ext.value(), 0))
        self.btn_ext_stop.clicked.connect(lambda: self._send_motor(0, 0, 0))
        self.btn_ext_goto.clicked.connect(lambda: self._send_motor(3, self.spd_ext.value(), self.target_ext.value()))
        self.btn_ext_setv.clicked.connect(lambda: self._send_motor(6, self.spd_ext.value(), 0))
        self.btn_ext_reset.clicked.connect(lambda: self._send_motor(4, 0, 0))
        left.addWidget(g_ext)

        # --- 系统指令 ---
        g_sys = QGroupBox("系统指令")
        gl = QGridLayout(g_sys)
        self.btn_heartbeat = QPushButton("心跳 (0x06)")
        self.btn_get_chassis = QPushButton("查询底盘状态 (0x0A)")
        self.btn_get_motor = QPushButton("查询电机状态 (0x0D)")
        for b in (self.btn_heartbeat, self.btn_get_chassis, self.btn_get_motor):
            b.setFixedHeight(34)
            b.setEnabled(False)
        gl.addWidget(self.btn_heartbeat, 0, 0)
        gl.addWidget(self.btn_get_chassis, 0, 1)
        gl.addWidget(self.btn_get_motor, 0, 2)
        self.btn_heartbeat.clicked.connect(lambda: self._send(CMD["HEARTBEAT"], b""))
        self.btn_get_chassis.clicked.connect(lambda: self._send(CMD["GET_CHASSIS"], b""))
        self.btn_get_motor.clicked.connect(lambda: self._send(CMD["GET_MOTOR"], struct.pack(">B", 1)))
        left.addWidget(g_sys)
        left.addStretch(1)

        # 右侧: 状态区
        right = QVBoxLayout()
        right.setSpacing(8)

        g_st = QGroupBox("底盘状态")
        gst = QGridLayout(g_st)
        self.lbls = {}
        fields = [
            ("st", "状态"), ("mode", "控制模式"), ("x", "弧长 X (mm)"),
            ("y", "Y (mm)"), ("yaw", "YAW (°)"), ("lx", "速度 LinearX (mm/s)"),
            ("ly", "LinearY (mm/s)"), ("ang", "Angular (°/s)"),
        ]
        for i, (k, name) in enumerate(fields):
            gst.addWidget(QLabel(name), i // 2, (i % 2) * 2)
            v = QLabel("—")
            v.setFrameShape(QFrame.StyledPanel)
            v.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
            gst.addWidget(v, i // 2, (i % 2) * 2 + 1)
            self.lbls[k] = v
        right.addWidget(g_st)

        g_mt = QGroupBox("电机状态 (伸缩杆 电机1)")
        gmt = QGridLayout(g_mt)
        mfields = [
            ("mid", "电机ID"), ("mst", "状态"), ("mv", "速度 (mm/s)"),
            ("mh", "高度 (mm)"), ("msw", "状态字"), ("merr", "错误码"),
            ("mi1", "电流1 (mA)"), ("mi2", "电流2 (mA)"), ("mtmp", "温度 (°C)"),
        ]
        for i, (k, name) in enumerate(mfields):
            gmt.addWidget(QLabel(name), i // 3, (i % 3) * 2)
            v = QLabel("—")
            v.setFrameShape(QFrame.StyledPanel)
            v.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
            gmt.addWidget(v, i // 3, (i % 3) * 2 + 1)
            self.lbls[k] = v
        right.addWidget(g_mt)
        right.addStretch(1)

        body.addLayout(left, 3)
        body.addLayout(right, 2)
        root.addLayout(body, 3)

        # 底部日志
        g_log = QGroupBox("通讯日志")
        vl = QVBoxLayout(g_log)
        self.log_view = QPlainTextEdit()
        self.log_view.setReadOnly(True)
        self.log_view.setMaximumBlockCount(2000)
        font = QFont("Consolas")
        font.setPointSize(9)
        self.log_view.setFont(font)
        vl.addWidget(self.log_view)
        root.addWidget(g_log, 2)

    # ---------- 连接 ----------
    def _toggle_connect(self):
        if self._sock:
            self._disconnect()
        else:
            host = self.ip_edit.text().strip() or "127.0.0.1"
            port = self.port_edit.value()
            try:
                sock = socket.create_connection((host, port), timeout=5)
                sock.settimeout(None)
            except OSError as e:
                self._log(f"[连接失败] {host}:{port} → {e}")
                return
            self._sock = sock
            self._seq = 0
            self._set_connected(True, f"已连接 {host}:{port}")
            self._recv_thread = RecvThread(sock)
            self._recv_thread.frame_received.connect(self._on_frame)
            self._recv_thread.disconnected.connect(self._on_remote_close)
            self._recv_thread.start()
            self._log(f"[连接成功] {host}:{port} (协议 V2.0, 帧头 0xA0AB)")

    def _disconnect(self):
        if self._recv_thread:
            self._recv_thread.disconnected.disconnect(self._on_remote_close)
            self._recv_thread.terminate()
            self._recv_thread.wait(1000)
            self._recv_thread = None
        if self._sock:
            try:
                self._sock.close()
            except OSError:
                pass
            self._sock = None
        self._set_connected(False, "未连接")
        self._log("[已断开]")

    def _on_remote_close(self, msg: str):
        if not self._sock:
            return
        try:
            self._sock.close()
        except OSError:
            pass
        self._sock = None
        self._set_connected(False, "未连接")
        self._log(f"[连接断开] {msg}")
        if self._recv_thread:
            self._recv_thread.disconnected.disconnect(self._on_remote_close)
            self._recv_thread = None

    def _set_connected(self, ok: bool, text: str):
        self.lbl_status.setText(text)
        self.lbl_status.setStyleSheet(
            "color:#35705A;font-weight:bold;padding:2px 10px;border:1px solid #35705A;border-radius:4px;"
            if ok else "color:#A14E50;font-weight:bold;padding:2px 10px;border:1px solid #A14E50;border-radius:4px;")
        self.btn_connect.setText("断开" if ok else "连接")
        for b in (self.btn_fwd, self.btn_back, self.btn_stop, self.btn_goto, self.btn_setv, self.btn_reset,
                  self.btn_ext_up, self.btn_ext_down, self.btn_ext_stop, self.btn_ext_goto, self.btn_ext_reset,
                  self.btn_ext_setv, self.btn_heartbeat, self.btn_get_chassis, self.btn_get_motor):
            b.setEnabled(ok)

    # ---------- 发送 ----------
    def _send(self, cmd: int, payload: bytes):
        if not self._sock:
            self._log("[未连接] 无法发送")
            return
        frame = make_frame(self._seq, cmd, payload)
        self._seq = (self._seq + 1) & 0xFFFF
        try:
            self._sock.sendall(frame)
        except OSError as e:
            self._log(f"[发送失败] {e}")
            return
        self._log(f"[TX] 0x{cmd:02X}  {fmt_frame(cmd, payload, tx=True)}")

    def _send_chassis(self, mode: int, speed: int, target: int):
        self._send(CMD["CHASSIS_MOVE"], chassis_payload(mode, speed, target))

    def _send_motor(self, mode: int, speed: int, coord: int):
        self._send(CMD["MOTOR_CTRL"], motor_payload(mode, speed, coord))

    # ---------- 接收 ----------
    def _on_frame(self, cmd: int, seq: int, payload: bytes):
        self._log(f"[RX] 0x{cmd:02X}  {fmt_frame(cmd, payload)}")
        try:
            if cmd == CMD["UPLOAD_CHASSIS"]:
                st, m = payload[0], payload[1]
                x, y, yaw = i32(payload[2:6]), i32(payload[6:10]), i16(payload[10:12])
                lx, ly, ang = i16(payload[12:14]), i16(payload[14:16]), i16(payload[16:18])
                self.lbls["st"].setText(STATE_CHASSIS.get(st, str(st)))
                self.lbls["mode"].setText(MODE_CHASSIS.get(m, str(m)))
                self.lbls["x"].setText(str(x))
                self.lbls["y"].setText(str(y))
                self.lbls["yaw"].setText(f"{yaw / 10:.1f}")
                self.lbls["lx"].setText(str(lx))
                self.lbls["ly"].setText(str(ly))
                self.lbls["ang"].setText(str(ang))
            elif cmd == CMD["GET_CHASSIS"]:
                st, m = payload[2], payload[3]
                x, y, yaw = i32(payload[4:8]), i32(payload[8:12]), i16(payload[12:14])
                lx, ly, ang = i16(payload[14:16]), i16(payload[16:18]), i16(payload[18:20])
                self.lbls["st"].setText(STATE_CHASSIS.get(st, str(st)))
                self.lbls["mode"].setText(MODE_CHASSIS.get(m, str(m)))
                self.lbls["x"].setText(str(x))
                self.lbls["y"].setText(str(y))
                self.lbls["yaw"].setText(f"{yaw / 10:.1f}")
                self.lbls["lx"].setText(str(lx))
                self.lbls["ly"].setText(str(ly))
                self.lbls["ang"].setText(str(ang))
            elif cmd in (CMD["GET_MOTOR"], CMD["UPLOAD_MOTOR"]):
                mid, st = payload[0], payload[1]
                v, h = i16(payload[2:4]), i32(payload[4:8])
                sw, err = u16(payload[8:10]), u16(payload[10:12])
                i1, i2, tmp = i32(payload[12:16]), i32(payload[16:20]), i32(payload[20:24])
                self.lbls["mid"].setText(str(mid))
                self.lbls["mst"].setText(STATE_MOTOR.get(st, str(st)))
                self.lbls["mv"].setText(str(v))
                self.lbls["mh"].setText(str(h))
                self.lbls["msw"].setText(str(sw))
                self.lbls["merr"].setText(str(err))
                self.lbls["mi1"].setText(str(i1))
                self.lbls["mi2"].setText(str(i2))
                self.lbls["mtmp"].setText(str(tmp))
        except Exception:
            pass

    def _log(self, text: str):
        ts = time.strftime("%H:%M:%S")
        self.log_view.appendPlainText(f"[{ts}] {text}")
        sb = self.log_view.verticalScrollBar()
        sb.setValue(sb.maximum())


# ---------------- 自测模式 (无界面) ----------------
def selftest(host: str, port: int):
    """offscreen 自测: 连接仿真桥 → 心跳 → 查询 → 移动 goto → 伸缩 goto → 验证响应与上传。"""
    ok = []

    def check(name: str, cond: bool):
        ok.append(cond)
        print(f"[{'PASS' if cond else 'FAIL'}] {name}")

    sock = socket.create_connection((host, port), timeout=5)
    sock.settimeout(3)
    seq = 0
    seen = {"hb": False, "chassis": 0, "ext": 0, "state2": False, "ext_done": False}

    def send(cmd: int, payload: bytes = b""):
        nonlocal seq
        sock.sendall(make_frame(seq, cmd, payload))
        seq = (seq + 1) & 0xFFFF

    def drain(seconds: float) -> list:
        end = time.time() + seconds
        out, buf = [], bytearray()
        while time.time() < end:
            try:
                data = sock.recv(4096)
            except socket.timeout:
                continue
            if not data:
                break
            buf.extend(data)
            while True:
                idx = buf.find(b"\xA0\xAB")
                if idx < 0:
                    buf.clear()
                    break
                del buf[:idx]
                if len(buf) < HEADER_LEN:
                    break
                _h, _s, mlen, _m, _c = struct.unpack_from(">HHHBB", buf, 0)
                if mlen > MAX_PAYLOAD:
                    del buf[:2]
                    continue
                total = HEADER_LEN + mlen + CRC_LEN + 1
                if len(buf) < total:
                    break
                fr = bytes(buf[:total])
                del buf[:total]
                got = decode_frame(fr)
                if got:
                    out.append(got)
        return out

    # 1) 心跳
    send(CMD["HEARTBEAT"])
    frames = drain(1)
    check("心跳 0x06 收到响应", any(f[2] == CMD["HEARTBEAT"] for f in frames))

    # 2) 查询底盘, 拿当前 X(环形最短路径确定相对目标)
    send(CMD["GET_CHASSIS"])
    frames = drain(1)
    cur_x = None
    for f in frames:
        if f[2] == CMD["GET_CHASSIS"] and len(f[3]) >= 12:
            cur_x = i32(f[3][4:8])
    check(f"查询底盘 0x0A 收到响应(当前 X={cur_x})", any(f[2] == CMD["GET_CHASSIS"] for f in frames))

    # 3) 移动 goto: 相对当前 X 前进 3000mm (环形, 路径确定约 3000mm)
    if cur_x is None:
        cur_x = 0
    target_x = (cur_x + 3000) % 21425
    send(CMD["CHASSIS_MOVE"], chassis_payload(5, 1000, target_x))
    frames = drain(1)
    check("移动 0x09 收到响应", any(f[2] == CMD["CHASSIS_MOVE"] for f in frames))
    # 等 0x0B 上传(10Hz, 环形最短路径最长约 18m, 留 15s)
    end = time.time() + 15
    last_x, saw2 = None, False
    while time.time() < end:
        for f in drain(2):
            if f[2] == CMD["UPLOAD_CHASSIS"]:
                last_x = i32(f[3][2:6])
                if f[3][0] == 2:
                    saw2 = True
    check(f"移动到位 X={last_x} (目标{target_x})", last_x is not None and abs(last_x - target_x) < 50)
    check("移动过程中出现 已到达(状态2)", saw2)

    # 4) 伸缩 goto 350mm
    send(CMD["MOTOR_CTRL"], motor_payload(3, 100, 350))
    frames = drain(1)
    check("伸缩 0x0C 收到响应", any(f[2] == CMD["MOTOR_CTRL"] for f in frames))
    end = time.time() + 8
    last_h, done = None, False
    while time.time() < end:
        for f in drain(2):
            if f[2] == CMD["UPLOAD_MOTOR"]:
                last_h = i32(f[3][4:8])
                if f[3][1] == 2:
                    done = True
    check(f"伸缩到位 高度={last_h} (目标350)", last_h is not None and abs(last_h - 350) < 30)
    check("伸缩过程出现 已到位(状态2)", done)

    sock.close()
    print(f"\n自测结果: {sum(ok)}/{len(ok)} 通过")
    return all(ok)


def main():
    ap = argparse.ArgumentParser(description="PySide6 机器人仿真上位机 (协议 V2.0)")
    ap.add_argument("--host", default="127.0.0.1", help="下位机地址(默认 127.0.0.1)")
    ap.add_argument("--port", type=int, default=50000, help="端口(默认 50000)")
    ap.add_argument("--selftest", action="store_true", help="无界面自测模式(需仿真桥已启动)")
    args = ap.parse_args()

    if args.selftest:
        import os
        os.environ.setdefault("QT_QPA_PLATFORM", "offscreen")
        sys.exit(0 if selftest(args.host, args.port) else 1)

    app = QApplication(sys.argv)
    win = UpperWindow()
    win.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
