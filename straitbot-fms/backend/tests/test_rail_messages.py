"""下位机消息定义测试：roundtrip、长度校验、前端仿真布局兼容、decode 路由。"""
import unittest

from app.rail import messages as m


class RailMessagesTest(unittest.TestCase):

    def _roundtrip(self, msg: m.IBoardMsg):
        payload = msg.to_bytes()
        back = type(msg).from_bytes(payload)
        self.assertEqual(back, msg, f"{type(msg).__name__} roundtrip 不一致")
        return payload

    # ---------- 请求类 roundtrip ----------
    def test_init_request(self):
        self._roundtrip(m.InitRequest(id=3, director=1, is_ring=1, track_photo_avoid=1,
                                      ultrasonic_avoid=1, low_battery_threshold=25,
                                      x_min=-1000, x_max=21000,
                                      y_min=0, y_max=0, z_min=0, z_max=600))
        self.assertEqual(len(m.InitRequest().to_bytes()), 26)
        # 与《协议 V2.0》0x01 字段表一致：12 字段 / 26 字节（曾误合并"环形轨道"与
        # "光电避障"成一个字节 → 25 字节，真机整帧错位）
        raw = m.InitRequest(id=1, director=1, is_ring=1, track_photo_avoid=0,
                            ultrasonic_avoid=1, low_battery_threshold=20,
                            x_min=-1, x_max=2, y_min=-3, y_max=4,
                            z_min=-5, z_max=6).to_bytes()
        self.assertEqual(raw, bytes([1, 1, 1, 0, 1, 20])
                         + (-1).to_bytes(4, "big", signed=True)
                         + (2).to_bytes(4, "big", signed=True)
                         + (-3).to_bytes(4, "big", signed=True)
                         + (4).to_bytes(4, "big", signed=True)
                         + (-5).to_bytes(2, "big", signed=True)
                         + (6).to_bytes(2, "big", signed=True))
        with self.assertRaises(ValueError):
            m.InitRequest.from_bytes(bytes(25))   # 老口径 25B 必须被拒

    def test_reboot_request(self):
        self._roundtrip(m.RebootRequest(command=1))
        with self.assertRaises(ValueError):
            m.RebootRequest.from_bytes(b"\x00\x00")

    def test_time_sync_request(self):
        self._roundtrip(m.TimeSyncRequest(year=26, month=9, day=16, hour=14, minute=30, second=5))

    def test_heartbeat_empty(self):
        self.assertEqual(m.HeartbeatMsg().to_bytes(), b"")
        self._roundtrip(m.HeartbeatMsg())
        with self.assertRaises(ValueError):
            m.HeartbeatMsg.from_bytes(b"\x00")

    def test_motor_power(self):
        self._roundtrip(m.MotorPowerRequest(motor_id=1, power=1))

    def test_chassis_move(self):
        msg = m.ChassisMove(mode=m.MOVE_GOTO, linear_x=1000, target_x=12345, target_y=-500,
                            target_yaw=-120)
        raw = self._roundtrip(msg)
        self.assertEqual(len(raw), 17)
        # 与前端 TS 打包布局一致：mode, u16 u16 u16, i32, i32, i16
        self.assertEqual(raw[0], m.MOVE_GOTO)
        self.assertEqual(int.from_bytes(raw[1:3], "big"), 1000)
        self.assertEqual(int.from_bytes(raw[7:11], "big", signed=True), 12345)
        self.assertEqual(int.from_bytes(raw[15:17], "big", signed=True), -120)

    def test_motor_ctrl(self):
        msg = m.MotorCtrl(motor_id=1, mode=m.MOTOR_GOTO, speed=100, coord=350)
        raw = self._roundtrip(msg)
        self.assertEqual(len(raw), 8)

    def test_get_motor_request(self):
        self._roundtrip(m.GetMotorRequest(motor_id=2))

    # ---------- 响应/上发 roundtrip ----------
    def test_config_response(self):
        self._roundtrip(m.ConfigResponse(error_code=0, move_limit=1000, lift_limit=150,
                                         lift_min=0, lift_max=600))

    def test_version_response(self):
        msg = m.VersionResponse(error_code=0, version=b"\x01\x0a\x00", sn=b"SIMROBOT0001")
        raw = self._roundtrip(msg)
        self.assertEqual(len(raw), 17)

    def test_chassis_state_roundtrip(self):
        msg = m.ChassisState(error_code=0, state=m.CHASSIS_RUNNING, mode=m.MODE_EMBEDDED,
                             x=12345, y=0, yaw=0, linear_x=500, linear_y=0, angular=0)
        raw = self._roundtrip(msg)
        self.assertEqual(len(raw), 20)

    def test_motor_state_roundtrip(self):
        msg = m.MotorState(error_code=0, motor_id=1, state=m.MOTOR_ST_ARRIVED, speed=0,
                           coord=350, status_word=120, driver_error=118,
                           current_1=32, current_2=0, temperature=25)
        raw = self._roundtrip(msg)
        self.assertEqual(len(raw), 30)

    def test_obstacle_state(self):
        self._roundtrip(m.ObstacleStateResponse(error_code=0, ultrasonic=0x1110,
                                                bumper=0x1111, drop=0x0000, estop=0x01))

    def test_power(self):
        self._roundtrip(m.PowerResponse(error_code=0, battery_percent=88, voltage=25300,
                                        current=1200, capacity=20000, temperature=270,
                                        contact=1, charge_state=5))
        self._roundtrip(m.ChargeStateUpload(battery_percent=88, voltage=25300, current=1200,
                                            capacity=20000, temperature=270, contact=1,
                                            charge_state=5))

    def test_charge_ctrl(self):
        self._roundtrip(m.ChargeControlRequest(control_type=1, pile_index=0,
                                               exit_distance=0xFF, speed=200))

    def test_hardware_mark_event(self):
        # 磁钉 0B 附加
        self._roundtrip(m.HardwareMarkEvent(mark_type=m.MARK_MAGNET, index=0, x=1000, speed=0))
        # RFID 8B 附加
        msg = m.HardwareMarkEvent(mark_type=m.MARK_RFID, index=3, x=8000, speed=300,
                                  extra=b"\x00\x01\x02\x03\x04\x05\x06\x07")
        raw = msg.to_bytes()
        self.assertEqual(len(raw), 17)
        back = m.HardwareMarkEvent.from_bytes(raw)
        self.assertEqual(back.extra, msg.extra)

    def test_board_log(self):
        msg = m.BoardLogUpload(level=3, content="[10011]:移动驱动器告警".encode("utf-8"))
        self._roundtrip(msg)
        back = m.BoardLogUpload.from_bytes(msg.to_bytes())
        self.assertEqual(back.text, "[10011]:移动驱动器告警")

    def test_rfid_range_event(self):
        self._roundtrip(m.RfidRangeEventUpload(type=m.RFID_EVENT_ENTER, rfid=42, x=8000,
                                               speed=300, x_before_calibrated=7900))

    def test_latest_rfid(self):
        self._roundtrip(m.LatestRfidResponse(rfid=42, x=8000, range=500))

    def test_map_tag(self):
        self._roundtrip(m.MapTagResponse(error_code=0, total=2, count=2, tags=[
            m.MapTag(tag_type=m.MARK_MAGNET, index=0, x=0, range=200),
            m.MapTag(tag_type=m.MARK_RFID, index=1, x=5000, range=300, extra=b"\x00" * 8),
        ]))

    # ---------- 前端仿真布局兼容（无错误码前缀 / 旧字段序） ----------
    def test_chassis_state_simulator_18b(self):
        """前端仿真器 0x0B 上传不带错误码前缀(18B)。"""
        payload = bytes([m.CHASSIS_RUNNING, m.MODE_EMBEDDED]) + \
            (12345).to_bytes(4, "big", signed=True) + (0).to_bytes(4, "big", signed=True) + \
            (0).to_bytes(2, "big", signed=True) + (500).to_bytes(2, "big", signed=True) + \
            (0).to_bytes(2, "big", signed=True) + (0).to_bytes(2, "big", signed=True)
        self.assertEqual(len(payload), 18)
        st = m.ChassisState.from_bytes(payload)
        self.assertEqual(st.error_code, 0)
        self.assertEqual(st.state, m.CHASSIS_RUNNING)
        self.assertEqual(st.x, 12345)
        self.assertEqual(st.linear_x, 500)

    def test_motor_state_simulator_28b(self):
        """前端仿真器 0x0E 上传：状态(1) mode(1) 速度(2) 坐标(4) 状态字 错误码 电流1 电流2 温度。"""
        payload = bytes([m.MOTOR_ST_ARRIVED, 1]) + \
            (0).to_bytes(2, "big", signed=True) + (350).to_bytes(4, "big", signed=True) + \
            (120).to_bytes(4, "big", signed=True) + (118).to_bytes(4, "big", signed=True) + \
            (32).to_bytes(4, "big", signed=True) + (0).to_bytes(4, "big", signed=True) + \
            (25).to_bytes(4, "big", signed=True)
        self.assertEqual(len(payload), 28)
        st = m.MotorState.from_bytes(payload)
        self.assertEqual(st.error_code, 0)
        self.assertEqual(st.motor_id, 1)
        self.assertEqual(st.state, m.MOTOR_ST_ARRIVED)
        self.assertEqual(st.coord, 350)
        self.assertEqual(st.temperature, 25)

    # ---------- decode 路由 ----------
    def test_decode_error_only_cmds(self):
        for cmd in (m.CMD_INIT, m.CMD_CHASSIS_MOVE, m.CMD_MOTOR_CTRL, m.CMD_CHARGE_CTRL):
            msg = m.decode(cmd, (0).to_bytes(2, "big"))
            self.assertIsInstance(msg, m.ErrorResponse)
            self.assertEqual(msg.error_code, 0)
        # 错误码非 0
        msg = m.decode(m.CMD_CHASSIS_MOVE, (10011).to_bytes(2, "big"))
        self.assertEqual(msg.error_code, m.ERR_DRIVE_ALERT)

    def test_decode_upload(self):
        ch = m.decode(m.CMD_UPLOAD_CHASSIS, bytes([1, 2]) + (8000).to_bytes(4, "big", signed=True)
                      + (0).to_bytes(4, "big", signed=True) + b"\x00\x00" * 4)
        self.assertIsInstance(ch, m.ChassisState)
        self.assertEqual(ch.x, 8000)

    def test_decode_unknown(self):
        with self.assertRaises(ValueError):
            m.decode(0xFE, b"")

    def test_decode_length_error(self):
        with self.assertRaises(ValueError):
            m.decode(m.CMD_UPLOAD_CHASSIS, b"\x00")  # 非法长度


if __name__ == "__main__":
    unittest.main()
