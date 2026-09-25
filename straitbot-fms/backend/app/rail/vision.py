"""巡检视觉动作（可见光拍照 / 全屏测温）访问层。

与 :mod:`hkptz_runtime` 同构：真机走海康相机 HCNetSDK（``HkPtz.snapshot``），
该调用是**阻塞**的（登录 + 抓图），由 Robot 的后台工作线程调用，状态机节拍只读
闩锁、不阻塞。仿真 / 无相机环境由 Robot 注入假 provider 做端到端验证。

相机 / 热像仪不可用**不应卡死巡检**：provider 把异常包成 ``VisionResult(ok=False)``
返回，Robot 记录后放行到下一动作。

**热像通道号不能硬编码**。早期按"海康双光球机 = 可见光 ch1 / 热像 ch2"的通用约定
写死 ch2，在真机 ``DS-2DY3423IW-D``（单可见光通道、能力集 ``isSupportHeatmap=false``、
无 ``Thermal`` 节点）上抓图直接报 ``err=4 NET_DVR_CHANNEL_ERROR``，每个测温动作白跑
一次并留下一条告警。改为**按设备实际能力探测**：

- 登录后能用 ``device_info()`` 读到 ``analog_chan_num`` / ``ip_chan_num``；
- 是否有热像以能力集为准（``isSupportHeatmap`` 或存在 ``Thermal`` 节点）；
- 探测不出来就**不下发**、直接回投 ``ok=False``，并给出明确原因，
  既不误报成"相机故障"，也不再浪费一次抓图往返。
"""
from __future__ import annotations

import logging
import time
import xml.etree.ElementTree as ET
from dataclasses import dataclass
from pathlib import Path
from typing import Callable, Optional, Protocol

logger = logging.getLogger("rail.vision")


@dataclass
class VisionResult:
    """一次视觉动作的结果。"""

    kind: str                          # "visible"（拍照）/ "thermometry"（全屏测温）
    ok: bool
    path: Optional[str] = None         # 落盘图片（JPEG）路径
    thermometry: Optional[dict] = None  # 全屏测温数据（最高温/温度矩阵等）；热像仪接入前为 None
    error: Optional[str] = None
    elapsed_ms: float = 0.0

    def as_dict(self) -> dict:
        return {
            "kind": self.kind,
            "ok": self.ok,
            "path": self.path,
            "thermometry": self.thermometry,
            "error": self.error,
            "elapsed_ms": round(self.elapsed_ms, 1),
        }


class VisionProvider(Protocol):
    """视觉能力接口；真机与仿真各自实现。"""

    def capture_visible(self, ctx: dict) -> VisionResult: ...

    def full_thermometry(self, ctx: dict) -> VisionResult: ...


class HkPtzVision:
    """默认视觉 provider：海康相机。

    - 可见光拍照：抓可见光通道的 JPEG 落盘；
    - 全屏测温：抓红外热像 JPEG 落盘。温度数值（最高温 / 温度矩阵 / 测温点）依赖
      现场热像仪的测温 SDK / ISAPI，**未接入前 ``thermometry=None``，不伪造温度**，
      仅保留红外画面。

    热像通道号**不做硬编码假设**，先经 :meth:`_thermal_channel` 按设备能力探测；
    设备无热像能力时直接回投失败并说明原因，不白跑一次抓图。
    """

    VISIBLE_CHANNEL = 1
    # 探测不到热像通道时的兜底候选（仅在设备能力集确实声明有热像、又没给出通道号时用）
    THERMAL_CHANNEL_FALLBACK = 2

    def __init__(self, ptz_provider: Optional[Callable[[], object]] = None) -> None:
        self._ptz_provider = ptz_provider
        # 探测结果缓存挂在**实例**上：不能放类级——不同相机/不同进程共享会串味，
        # 现场换相机后也不会重新探测。0 = 已探测、确认不支持热像。
        self._thermal_channel_cache: Optional[int] = None
        self._thermal_cap_cache: dict = {}

    def _get_ptz(self):
        if self._ptz_provider is not None:
            return self._ptz_provider()
        from .hkptz_runtime import get_hkptz
        return get_hkptz()

    def capture_visible(self, ctx: dict) -> VisionResult:
        return self._snap(self.VISIBLE_CHANNEL, ctx, "visible", "可见光")

    def full_thermometry(self, ctx: dict) -> VisionResult:
        ch = self._thermal_channel()
        if ch is None:
            reason = self._thermal_unsupported_reason()
            logger.warning("[vision] 全屏测温跳过（放行巡检）：%s", reason)
            return VisionResult(kind="thermometry", ok=False, error=reason)
        return self._snap(ch, ctx, "thermometry", "红外热像")

    # ------------------------------------------------------------ 热像能力探测
    def _thermal_channel(self) -> Optional[int]:
        """返回本相机可用的热像抓图通道号；设备无热像能力时返回 None。"""
        if self._thermal_channel_cache is not None:
            return self._thermal_channel_cache or None
        try:
            ptz = self._get_ptz()
            if not self._supports_thermal(ptz):
                self._thermal_channel_cache = 0        # 0 = 已探测、不支持
                return None
            ch = self._pick_thermal_channel(ptz)
            self._thermal_channel_cache = ch or 0
            logger.info("[vision] 热像通道探测结果：channel=%s", ch)
            return ch
        except Exception as e:  # noqa: BLE001  探测失败按"不支持"处理并说明
            logger.warning("[vision] 热像通道探测失败：%s", e)
            self._thermal_channel_cache = 0
            return None

    def _supports_thermal(self, ptz) -> bool:
        """按能力集判断设备是否有热像能力（``isSupportHeatmap`` 或存在 ``Thermal`` 节点）。"""
        ip = getattr(ptz, "ip", "")
        if ip and ip in self._thermal_cap_cache:
            return self._thermal_cap_cache[ip]
        supported = False
        try:
            raw = ptz.isapi("GET", "/ISAPI/System/capabilities")
            supported = _capabilities_has_thermal(raw)
        except Exception as e:  # noqa: BLE001
            logger.warning("[vision] 读取相机能力集失败，按无热像处理：%s", e)
        if ip:
            self._thermal_cap_cache[ip] = supported
        return supported

    def _pick_thermal_channel(self, ptz) -> Optional[int]:
        """在声明有热像的设备上挑抓图通道号。

        单通道设备（``analog_chan_num<=1`` 且无 IP 通道）的热像与可见光同通道（ch1）；
        多通道设备沿用探测到的通道数向上取（真机接入时按能力集核对即可）。
        """
        info: dict = {}
        try:
            info = ptz.device_info() or {}
        except Exception:  # noqa: BLE001
            pass
        chan_total = int(info.get("analog_chan_num") or 0) + int(info.get("ip_chan_num") or 0)
        if chan_total <= 1:
            return self.VISIBLE_CHANNEL
        return self.THERMAL_CHANNEL_FALLBACK

    def _thermal_unsupported_reason(self) -> str:
        return ("相机无热像能力（能力集 isSupportHeatmap=false 且无 Thermal 节点），"
                "全屏测温动作跳过；如需测温请接入带热像镜头的双光设备")

    def _snap(self, channel: int, ctx: dict, kind: str, label: str) -> VisionResult:
        t0 = time.monotonic()
        out_dir = Path(ctx["result_dir"])
        out_dir.mkdir(parents=True, exist_ok=True)
        out = out_dir / f"{ctx['file_stem']}_{kind}.jpg"
        try:
            ptz = self._get_ptz()
            ptz.snapshot(channel=channel, path=out)
            logger.info("[vision] %s完成：%s", label, out)
            return VisionResult(
                kind=kind, ok=True, path=str(out),
                elapsed_ms=(time.monotonic() - t0) * 1000.0,
            )
        except Exception as e:  # noqa: BLE001  视觉失败不阻断巡检
            logger.warning("[vision] %s失败（放行巡检）：%s", label, e)
            return VisionResult(
                kind=kind, ok=False, error=str(e),
                elapsed_ms=(time.monotonic() - t0) * 1000.0,
            )


def _capabilities_has_thermal(raw: str) -> bool:
    """从 ``/ISAPI/System/capabilities`` 响应判断设备是否具备热像能力。

    判定依据（任一成立即认为有）：
    - ``<isSupportHeatmap>true</isSupportHeatmap>``；
    - 文档里出现 ``Thermal`` 相关节点（双光设备的测温能力节点）。

    只看 ``isSupportHeatmap`` 会漏判：部分双光机型把测温能力放在 ``Thermal`` 子树，
    而热力图（heatmap 伪彩）另有开关。
    """
    if not raw:
        return False
    try:
        root = ET.fromstring(raw)
    except ET.ParseError:
        root = None
    if root is not None:
        for node in root.iter():
            tag = node.tag.rsplit("}", 1)[-1]
            if tag == "isSupportHeatmap":
                if (node.text or "").strip().lower() == "true":
                    return True
            elif "thermal" in tag.lower():
                return True
    # XML 解析失败或结构异常：退化做文本匹配，宁可多判也不漏判（漏判会让测温动作空跑）
    lowered = raw.lower()
    return "issupportheatmap>true" in lowered or "thermal" in lowered
