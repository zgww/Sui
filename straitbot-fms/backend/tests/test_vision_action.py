"""巡检视觉动作（可见光拍照 / 全屏测温）测试。

不连真机：注入 FakeVision（在结果目录写占位 JPEG），用 FakeBoard + FakeClock 逐拍
驱动；视觉工作线程是真实线程，故每拍之间留少量真实时间让其回投闩锁。
"""
import time
from pathlib import Path

from app.config import PREFAB_DIR
from app.rail import messages
from app.rail.client import ConnStatus
from app.rail.robot import Robot
from app.rail.vision import VisionResult

JPEG_HEAD = b"\xff\xd8\xff\xe0fake-jpeg"


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


class FakeVision:
    """假视觉 provider：在结果目录写占位 JPEG；可配置某类动作失败。"""

    def __init__(self, fail=()):
        self.fail = set(fail)
        self.calls = []

    def _snap(self, kind, ctx):
        self.calls.append(kind)
        if kind in self.fail:
            return VisionResult(kind=kind, ok=False, error="fake camera error")
        d = Path(ctx["result_dir"])
        d.mkdir(parents=True, exist_ok=True)
        p = d / f"{ctx['file_stem']}_{kind}.jpg"
        p.write_bytes(JPEG_HEAD)
        return VisionResult(kind=kind, ok=True, path=str(p))

    def capture_visible(self, ctx):
        return self._snap("visible", ctx)

    def full_thermometry(self, ctx):
        return self._snap("thermometry", ctx)


def make_robot(tmp_path, vision):
    clk = FakeClock()
    r = Robot.from_prefab(
        PREFAB_DIR / "robot.prefab.json",
        board=FakeBoard(),
        clock=clk,
        tick_interval=0.02,
        inspection_dir=tmp_path,
        vision_provider=lambda: vision,
    )
    return r, clk


def wait_true(r, clk, pred, timeout=8.0, step=0.02):
    end = time.monotonic() + timeout
    while time.monotonic() < end:
        clk.t += step
        r.sm.tick()
        time.sleep(step)
        if pred():
            return
    raise AssertionError(f"条件未满足，当前 {r.sm.state_path()}")


def wait_leaf(r, clk, target, timeout=8.0, step=0.02):
    wait_true(r, clk, lambda: r.sm.leaf_state() == target, timeout, step)


def task(actions):
    """单楼层、单航点（x=0 容差即到位）、动作无云台/升降要求，直达执行动作。"""
    return {
        "floor": 1, "id": "v" * 32, "name": "视觉测试", "plan": "plan1",
        "waypoint": [{
            "id": "wp1", "index": 1,
            "pose": {"point": {"x": 0.0, "y": 0.0, "z": 0.0}, "theta": 0.0},
            "action": actions,
        }],
    }


def action(aid, atype):
    return {"id": aid, "type": atype, "lift_height": 0.0,
            "steer_point_name": "", "thermometry_points": []}


def test_photo_and_thermometry_capture_and_finish(tmp_path):
    vision = FakeVision()
    r, clk = make_robot(tmp_path, vision)
    r.sm.start()
    wait_leaf(r, clk, "空闲")

    payload = task([action("a1photo0000000000000000000000", 1),
                    action("a2thermo000000000000000000000", 2)])
    assert r.接收巡检任务(payload)["accepted"] is True

    # 先确认巡检真的启动（离开空闲），再等它跑完
    wait_leaf(r, clk, "移动到航点")
    wait_leaf(r, clk, "空闲")

    # 两类视觉动作各执行一次，结果图落盘到 data/inspection/{id}/
    assert vision.calls == ["visible", "thermometry"]
    result_dir = tmp_path / ("v" * 32)
    visible = list(result_dir.glob("*_visible.jpg"))
    thermo = list(result_dir.glob("*_thermometry.jpg"))
    assert len(visible) == 1 and visible[0].read_bytes() == JPEG_HEAD
    assert len(thermo) == 1 and thermo[0].read_bytes() == JPEG_HEAD
    # 巡检正常结束，释放 busy
    assert r.巡检进行中 is False


def test_vision_failure_does_not_block_inspection(tmp_path):
    vision = FakeVision(fail={"visible"})
    r, clk = make_robot(tmp_path, vision)
    r.sm.start()
    wait_leaf(r, clk, "空闲")

    r.接收巡检任务(task([action("a1photo0000000000000000000000", 1)]))
    wait_leaf(r, clk, "移动到航点")
    wait_leaf(r, clk, "空闲")

    # 拍照失败也放行，巡检照样结束，错误被记录，不产生图片
    assert r.巡检进行中 is False
    assert r.state.insp.vision_error == "fake camera error"
    assert not list((tmp_path / ("v" * 32)).glob("*_visible.jpg"))


def test_video_action_passes_without_vision_call(tmp_path):
    vision = FakeVision()
    r, clk = make_robot(tmp_path, vision)
    r.sm.start()
    wait_leaf(r, clk, "空闲")

    r.接收巡检任务(task([action("a3video0000000000000000000000", 3)]))
    wait_leaf(r, clk, "移动到航点")
    wait_leaf(r, clk, "空闲")

    # 录像本轮未接入：直接放行，不调用视觉 provider，巡检仍正常结束
    assert vision.calls == []
    assert r.巡检进行中 is False


# --------------------------------------------------------------------------- #
# 热像通道探测：不能硬编码 channel=2
# --------------------------------------------------------------------------- #
class FakeDualPtz:
    """假海康相机（可配置是否为双光/热像设备），用于热像通道探测测试。"""

    def __init__(self, *, heatmap: bool = False, thermal_node: bool = False,
                 analog_chan_num: int = 1, ip_chan_num: int = 0):
        self.ip = "192.168.6.170"
        self.heatmap = heatmap
        self.thermal_node = thermal_node
        self._analog = analog_chan_num
        self._ip = ip_chan_num
        self.snapshots = []          # 记录实际抓图用的通道号

    def isapi(self, method, path, body=None):
        if path.endswith("/capabilities") and "System" in path:
            parts = [f"<isSupportHeatmap>{str(self.heatmap).lower()}</isSupportHeatmap>"]
            if self.thermal_node:
                parts.append("<ThermalCap><channels>2</channels></ThermalCap>")
            return "<cap>" + "".join(parts) + "</cap>"
        raise AssertionError(f"未预期的 ISAPI 调用 {method} {path}")

    def device_info(self):
        return {"ip": self.ip, "analog_chan_num": self._analog,
                "start_chan": 1, "ip_chan_num": self._ip, "start_d_chan": 0}

    def snapshot(self, channel=None, path=None):
        self.snapshots.append(channel)
        if path:
            Path(path).write_bytes(JPEG_HEAD)
        return JPEG_HEAD


def _vision_ctx(tmp_path):
    return {"result_dir": str(tmp_path), "file_stem": "f1_wp001_a01_abc",
            "floor": "1", "waypoint_id": "wp1", "action_id": "a01"}


def test_thermometry_skipped_when_device_has_no_thermal(tmp_path):
    """单光设备（真机 DS-2DY3423IW-D：heatmap=false、无 Thermal 节点）：
    测温动作不再向不存在的 channel=2 抓图，直接跳过并给出明确原因。"""
    from app.rail.vision import HkPtzVision
    ptz = FakeDualPtz(heatmap=False, thermal_node=False)
    v = HkPtzVision(ptz_provider=lambda: ptz)

    res = v.full_thermometry(_vision_ctx(tmp_path))

    assert res.ok is False
    assert "无热像能力" in res.error
    # 关键：一次抓图都不发（旧实现会往 channel=2 发一次并拿到 err=4）
    assert ptz.snapshots == []


def test_thermometry_uses_visible_channel_on_single_channel_thermal_device(tmp_path):
    """声明有热像但只有单通道的设备：热像与可见光同通道（ch1），而不是 ch2。"""
    from app.rail.vision import HkPtzVision
    ptz = FakeDualPtz(heatmap=True, analog_chan_num=1, ip_chan_num=0)
    v = HkPtzVision(ptz_provider=lambda: ptz)

    res = v.full_thermometry(_vision_ctx(tmp_path))

    assert res.ok is True
    assert ptz.snapshots == [1]


def test_thermal_capability_detected_from_thermal_node(tmp_path):
    """部分双光机型只有 Thermal 节点、heatmap 为 false，也要判为支持热像。"""
    from app.rail.vision import HkPtzVision
    ptz = FakeDualPtz(heatmap=False, thermal_node=True, analog_chan_num=2)
    v = HkPtzVision(ptz_provider=lambda: ptz)

    res = v.full_thermometry(_vision_ctx(tmp_path))

    assert res.ok is True
    assert ptz.snapshots == [2]      # 双通道设备沿用探测到的热像通道


def test_thermal_capability_probed_once_per_inspection(tmp_path):
    """能力集只探测一次：多个测温动作不应反复请求 capabilities。"""
    from app.rail.vision import HkPtzVision
    calls = []

    class CountingPtz(FakeDualPtz):
        def isapi(self, method, path, body=None):
            calls.append(path)
            return super().isapi(method, path, body)

    ptz = CountingPtz(heatmap=False)
    v = HkPtzVision(ptz_provider=lambda: ptz)

    for _ in range(3):
        v.full_thermometry(_vision_ctx(tmp_path))

    assert len(calls) == 1


# --------------------------------------------------------------------------- #
# 热像通道探测：不能硬编码 channel=2
# --------------------------------------------------------------------------- #
class FakeDualPtz:
    """假海康相机（可配置是否为双光/热像设备），用于热像通道探测测试。"""

    def __init__(self, *, heatmap: bool = False, thermal_node: bool = False,
                 analog_chan_num: int = 1, ip_chan_num: int = 0):
        self.ip = "192.168.6.170"
        self.heatmap = heatmap
        self.thermal_node = thermal_node
        self._analog = analog_chan_num
        self._ip = ip_chan_num
        self.snapshots = []          # 记录实际抓图用的通道号

    def isapi(self, method, path, body=None):
        if path.endswith("/capabilities") and "System" in path:
            parts = [f"<isSupportHeatmap>{str(self.heatmap).lower()}</isSupportHeatmap>"]
            if self.thermal_node:
                parts.append("<ThermalCap><channels>2</channels></ThermalCap>")
            return "<cap>" + "".join(parts) + "</cap>"
        raise AssertionError(f"未预期的 ISAPI 调用 {method} {path}")

    def device_info(self):
        return {"ip": self.ip, "analog_chan_num": self._analog,
                "start_chan": 1, "ip_chan_num": self._ip, "start_d_chan": 0}

    def snapshot(self, channel=None, path=None):
        self.snapshots.append(channel)
        if path:
            Path(path).write_bytes(JPEG_HEAD)
        return JPEG_HEAD


def _vision_ctx(tmp_path):
    return {"result_dir": str(tmp_path), "file_stem": "f1_wp001_a01_abc",
            "floor": "1", "waypoint_id": "wp1", "action_id": "a01"}


def test_thermometry_skipped_when_device_has_no_thermal(tmp_path):
    """单光设备（真机 DS-2DY3423IW-D：heatmap=false、无 Thermal 节点）：
    测温动作不再向不存在的 channel=2 抓图，直接跳过并给出明确原因。"""
    from app.rail.vision import HkPtzVision
    ptz = FakeDualPtz(heatmap=False, thermal_node=False)
    v = HkPtzVision(ptz_provider=lambda: ptz)

    res = v.full_thermometry(_vision_ctx(tmp_path))

    assert res.ok is False
    assert "无热像能力" in res.error
    # 关键：一次抓图都不发（旧实现会往 channel=2 发一次并拿到 err=4）
    assert ptz.snapshots == []


def test_thermometry_uses_visible_channel_on_single_channel_thermal_device(tmp_path):
    """声明有热像但只有单通道的设备：热像与可见光同通道（ch1），而不是 ch2。"""
    from app.rail.vision import HkPtzVision
    ptz = FakeDualPtz(heatmap=True, analog_chan_num=1, ip_chan_num=0)
    v = HkPtzVision(ptz_provider=lambda: ptz)

    res = v.full_thermometry(_vision_ctx(tmp_path))

    assert res.ok is True
    assert ptz.snapshots == [1]


def test_thermal_capability_detected_from_thermal_node(tmp_path):
    """部分双光机型只有 Thermal 节点、heatmap 为 false，也要判为支持热像。"""
    from app.rail.vision import HkPtzVision
    ptz = FakeDualPtz(heatmap=False, thermal_node=True, analog_chan_num=2)
    v = HkPtzVision(ptz_provider=lambda: ptz)

    res = v.full_thermometry(_vision_ctx(tmp_path))

    assert res.ok is True
    assert ptz.snapshots == [2]      # 双通道设备沿用探测到的热像通道


def test_thermal_capability_probed_once_per_inspection(tmp_path):
    """能力集只探测一次：多个测温动作不应反复请求 capabilities。"""
    from app.rail.vision import HkPtzVision
    calls = []

    class CountingPtz(FakeDualPtz):
        def isapi(self, method, path, body=None):
            calls.append(path)
            return super().isapi(method, path, body)

    ptz = CountingPtz(heatmap=False)
    v = HkPtzVision(ptz_provider=lambda: ptz)

    for _ in range(3):
        v.full_thermometry(_vision_ctx(tmp_path))

    assert len(calls) == 1
