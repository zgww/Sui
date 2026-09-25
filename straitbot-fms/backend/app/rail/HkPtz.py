"""HkPtz：海康相机（云台）访问客户端，基于海康原生 **HCNetSDK**（ctypes 调用）。

用官方 ``HCNetSDK.dll``（Windows，位于 SDK ``库文件/`` 目录）登录设备并做云台控制/抓图，
比 ISAPI(HTTP) 更贴合厂商能力（云台速度、预置点、JPEG 抓图走 SDK 私有协议）。
连接参数来自 prefab 节点 :class:`app.prefab.nodes.hkptz.HkPtzConfig`
（可在 data/prefabs/robot.prefab.json 中配置，与 ``RobotConfig`` 同源加载）。

典型用法::

    from app.rail.HkPtz import HkPtz

    ptz = HkPtz.from_prefab_root(robot.prefab_root)   # 从机器人 prefab 树里找 HkPtzConfig
    with ptz:                                          # 等价 connect()/close()
        info = ptz.device_info()
        ptz.pan_left(speed=4)                          # 左转（持续）
        ptz.pan_left(stop=True)                        # 停止
        ptz.goto_preset(1)                             # 转到预置点 1
        jpeg = ptz.snapshot()                          # 抓图，返回 bytes

SDK 依赖：需将海康 ``HCNetSDKV*_Win64`` 的 ``库文件/`` 目录放到 ``docs/`` 下（自动探测），
或在 ``HkPtzConfig.sdk_path`` 显式指定含 ``HCNetSDK.dll`` 的目录。SDK 初始化进程内只做一次。

注意：所有调用均为**同步阻塞**（原生 SDK）。不要在状态机节拍（``Robot._tick_loop``）
里直接调用，应放到异步任务 / 线程池中执行——与 ``app/services/robot_api.py`` 拍照/测温同源约定。
"""
from __future__ import annotations

import ctypes
import logging
import os
import threading
import xml.etree.ElementTree as ET
from ctypes import (CFUNCTYPE, POINTER, Structure, byref, c_bool, c_byte, c_char,
                    c_char_p, c_long, c_uint16, c_uint32, c_ushort, c_void_p,
                    create_string_buffer)
from pathlib import Path
from typing import Optional

from app.config import PROJECT_ROOT
from app.prefab.nodes.hkptz import HkPtzConfig

logger = logging.getLogger("rail.hkptz")

# ============================================================ 云台/预置点命令（HCNetSDK 常量）
ZOOM_IN = 11
ZOOM_OUT = 12
FOCUS_NEAR = 13
FOCUS_FAR = 14
IRIS_OPEN = 15
IRIS_CLOSE = 16
TILT_UP = 21
TILT_DOWN = 22
PAN_LEFT = 23
PAN_RIGHT = 24
PAN_AUTO = 29
SET_PRESET = 8
CLE_PRESET = 9
GOTO_PRESET = 39

# 云台速度 1..7（NET_DVR_PTZControlWithSpeed_Other 的 dwSpeed）
DEFAULT_PTZ_SPEED = 4
# 抓图缓冲上限（4MB，足以容纳常规分辨率 JPEG）
_JPEG_BUF_SIZE = 4 * 1024 * 1024

# ---- ISAPI 绝对定位（HTTP + digest 鉴权；SDK 的 STDXMLConfig 写通道在部分固件上不稳定）----
# AbsoluteHigh 坐标：azimuth(水平)/elevation(垂直) 为 0.1° 整数；absoluteZoom 为设备 ZRange 整数。
# 度 -> 0.1° 整数
_PAN_SCALE = 10.0
_TILT_SCALE = 10.0
# 倍率比例 -> absoluteZoom：本机族 1.0x 对应 absoluteZoom=10（ZRange Min），即 ratio*10。
_ZOOM_SCALE = 10.0
# 能力集读取失败时的兜底范围（xmin,xmax,ymin,ymax,zmin,zmax）；正常情况下用设备实测范围。
_FALLBACK_RANGES = (0, 3600, -900, 900, 1, 1000)
# HTTP ISAPI 超时（秒）
_ISAPI_HTTP_TIMEOUT = 8.0

# 常见 NET_DVR_GetLastError 码 -> 中文（便于现场定位，未覆盖的显示原始码）
_ERR_TEXT = {
    0: "无错误",
    1: "用户名密码错误",
    2: "权限不足",
    3: "SDK 未初始化",
    # 4 在抓图/预览类接口里实际表现为 NET_DVR_CHANNEL_ERROR（通道号错误）——
    # 双光球机的热像通道号与可见光不同，配错就是这条。
    4: "通道号错误（设备无此通道；双光相机热像通道号与可见光不同，需按能力集核对）",
    5: "设备连接数超过上限",
    6: "SDK 与设备版本不匹配",
    7: "连接设备失败（网络/端口不通）",
    8: "发送失败",
    10: "接收超时",
    11: "数据传输错误",
    12: "调用次序错误",
    17: "参数错误",
    23: "设备不支持该操作",
    29: "设备不支持",
    43: "用户名或密码错误",
    47: "用户被锁定",
    91: "用户不存在",
    153: "命令发送频率过高",
}


def _err_text(code: int) -> str:
    return _ERR_TEXT.get(int(code), "未知错误")


# ============================================================ ctypes 结构体（对齐官方 SDK 定义）
class NET_DVR_DEVICEINFO_V30(Structure):
    _fields_ = [
        ("sSerialNumber", c_byte * 48),
        ("byAlarmInPortNum", c_byte), ("byAlarmOutPortNum", c_byte),
        ("byDiskNum", c_byte), ("byDVRType", c_byte),
        ("byChanNum", c_byte), ("byStartChan", c_byte),
        ("byAudioChanNum", c_byte), ("byIPChanNum", c_byte),
        ("byZeroChanNum", c_byte), ("byMainProto", c_byte), ("bySubProto", c_byte),
        ("bySupport", c_byte), ("bySupport1", c_byte), ("bySupport2", c_byte),
        ("wDevType", c_uint16),
        ("bySupport3", c_byte), ("byMultiStreamProto", c_byte),
        ("byStartDChan", c_byte), ("byStartDTalkChan", c_byte),
        ("byHighDChanNum", c_byte), ("bySupport4", c_byte), ("byLanguageType", c_byte),
        ("byVoiceInChanNum", c_byte), ("byStartVoiceInChanNo", c_byte),
        ("bySupport5", c_byte), ("bySupport6", c_byte), ("byMirrorChanNum", c_byte),
        ("wStartMirrorChanNo", c_uint16), ("bySupport7", c_byte), ("byRes2", c_byte),
    ]


_LP_DEVINFO_V30 = POINTER(NET_DVR_DEVICEINFO_V30)
_LOGIN_RESULT_CB = CFUNCTYPE(None, c_uint32, c_uint32, _LP_DEVINFO_V30, c_void_p)


class NET_DVR_DEVICEINFO_V40(Structure):
    _fields_ = [
        ("struDeviceV30", NET_DVR_DEVICEINFO_V30),
        ("bySupportLock", c_byte), ("byRetryLoginTime", c_byte),
        ("byPasswordLevel", c_byte), ("byProxyType", c_byte),
        ("dwSurplusLockTime", c_uint32),
        ("byCharEncodeType", c_byte), ("bySupportDev5", c_byte),
        ("bySupport", c_byte), ("byLoginMode", c_byte),
        ("dwOEMCode", c_uint32), ("iResidualValidity", c_uint32),
        ("byResidualValidity", c_byte), ("bySingleStartDTalkChan", c_byte),
        ("bySingleDTalkChanNums", c_byte), ("byPassWordResetLevel", c_byte),
        ("bySupportStreamEncrypt", c_byte), ("byMarketType", c_byte),
        ("byRes2", c_byte * 238),
    ]


class NET_DVR_USER_LOGIN_INFO(Structure):
    _fields_ = [
        ("sDeviceAddress", c_char * 129),
        ("byUseTransport", c_byte),
        ("wPort", c_uint16),
        ("sUserName", c_char * 64),
        ("sPassword", c_char * 64),
        ("cbLoginResult", _LOGIN_RESULT_CB),
        ("pUser", c_void_p),
        ("bUseAsynLogin", c_uint32),
        ("byProxyType", c_byte), ("byUseUTCTime", c_byte),
        ("byLoginMode", c_byte), ("byHttps", c_byte),
        ("iProxyID", c_uint32), ("byVerifyMode", c_byte),
        ("byRes2", c_byte * 119),
    ]


class NET_DVR_LOCAL_SDK_PATH(Structure):
    _fields_ = [("sPath", c_char * 256), ("byRes", c_byte * 128)]


class NET_DVR_JPEGPARA(Structure):
    _fields_ = [("wPicSize", c_ushort), ("wPicQuality", c_ushort)]


# ============================================================ SDK 加载（进程内单例）
class HkPtzError(Exception):
    """海康 SDK 调用错误（未找到库 / 登录失败 / 接口返回失败）。"""


_sdk_lock = threading.Lock()
_sdk = None                       # 已加载并初始化的 HCNetSDK CDLL
_sdk_dir: Optional[Path] = None   # 已加载库所在目录（缓存，避免重复探测）


def _resolve_sdk_dir(cfg_path: str = "") -> Path:
    """定位含 HCNetSDK.dll 的库目录：优先配置项，否则在 docs/HCNetSDK*/库文件 下探测。"""
    lib_name = "HCNetSDK.dll" if os.name == "nt" else "libhcnetsdk.so"
    if cfg_path:
        p = Path(cfg_path).expanduser()
        cand = p if (p / lib_name).exists() else p / "库文件"
        if (cand / lib_name).exists():
            return cand
        raise HkPtzError(f"sdk_path 下未找到 {lib_name}: {p}")
    for dll in sorted(PROJECT_ROOT.glob(f"docs/HCNetSDK*/库文件/{lib_name}")):
        return dll.parent
    for dll in sorted(PROJECT_ROOT.glob(f"docs/HCNetSDK*/**/{lib_name}")):
        return dll.parent
    raise HkPtzError(
        f"未找到海康 SDK 库（{lib_name}）。请把 SDK 的 库文件/ 目录放到 docs/ 下，"
        "或在 HkPtzConfig.sdk_path 指定其绝对路径。")


def _path_bytes(p: Path) -> bytes:
    """SDK 组件路径按本地编码传字节：中文路径在 Windows 用 gbk（官方 demo 同此约定）。"""
    enc = "gbk" if os.name == "nt" else "utf-8"
    return str(p).encode(enc, errors="replace")


def _configure_signatures(sdk) -> None:
    """显式声明 argtypes/restype：64 位下句柄/指针默认按 c_int 截断会踩坑，必须固定。"""
    sdk.NET_DVR_Init.restype = c_bool
    sdk.NET_DVR_Cleanup.restype = c_bool
    sdk.NET_DVR_GetLastError.restype = c_uint32
    sdk.NET_DVR_SetConnectTime.restype = c_bool
    sdk.NET_DVR_SetConnectTime.argtypes = [c_uint32, c_uint32]
    sdk.NET_DVR_SetReconnect.restype = c_bool
    sdk.NET_DVR_SetReconnect.argtypes = [c_uint32, c_bool]
    sdk.NET_DVR_SetSDKInitCfg.restype = c_bool
    sdk.NET_DVR_SetSDKInitCfg.argtypes = [c_uint32, c_void_p]
    sdk.NET_DVR_Login_V40.restype = c_long
    sdk.NET_DVR_Login_V40.argtypes = [POINTER(NET_DVR_USER_LOGIN_INFO),
                                      POINTER(NET_DVR_DEVICEINFO_V40)]
    sdk.NET_DVR_Logout.restype = c_bool
    sdk.NET_DVR_Logout.argtypes = [c_long]
    sdk.NET_DVR_PTZControlWithSpeed_Other.restype = c_bool
    sdk.NET_DVR_PTZControlWithSpeed_Other.argtypes = [
        c_long, c_long, c_uint32, c_uint32, c_uint32]
    sdk.NET_DVR_PTZPreset_Other.restype = c_bool
    sdk.NET_DVR_PTZPreset_Other.argtypes = [c_long, c_long, c_uint32, c_uint32]
    sdk.NET_DVR_CaptureJPEGPicture_NEW.restype = c_bool
    sdk.NET_DVR_CaptureJPEGPicture_NEW.argtypes = [
        c_long, c_long, POINTER(NET_DVR_JPEGPARA), c_char_p, c_uint32, POINTER(c_uint32)]


def _ensure_sdk(sdk_dir_hint: str = ""):
    """加载并初始化 HCNetSDK（进程内只做一次，返回已就绪的 CDLL）。"""
    global _sdk, _sdk_dir
    with _sdk_lock:
        if _sdk is not None:
            return _sdk
        sdk_dir = _resolve_sdk_dir(sdk_dir_hint)
        lib_name = "HCNetSDK.dll" if os.name == "nt" else "libhcnetsdk.so"
        if os.name == "nt":
            # 让依赖 DLL（HCCore.dll / HCNetSDKCom/*.dll）能被解析
            try:
                os.add_dll_directory(str(sdk_dir))
            except (AttributeError, OSError):
                pass
            os.environ["PATH"] = str(sdk_dir) + os.pathsep + os.environ.get("PATH", "")
        sdk = ctypes.CDLL(str(sdk_dir / lib_name))
        _configure_signatures(sdk)

        # 组件库目录（HCNetSDKCom 所在处）= sdk_dir
        cfg = NET_DVR_LOCAL_SDK_PATH()
        cfg.sPath = _path_bytes(sdk_dir)
        sdk.NET_DVR_SetSDKInitCfg(2, byref(cfg))
        # OpenSSL（本 SDK 版本为 libcrypto-3-x64.dll / libssl-3-x64.dll），存在才设
        for cfg_type, pattern in ((3, "libcrypto*.dll"), (4, "libssl*.dll")):
            hits = sorted(sdk_dir.glob(pattern))
            if hits:
                sdk.NET_DVR_SetSDKInitCfg(cfg_type, create_string_buffer(_path_bytes(hits[0])))

        if not sdk.NET_DVR_Init():
            raise HkPtzError(f"NET_DVR_Init 失败, err={sdk.NET_DVR_GetLastError()}")
        sdk.NET_DVR_SetConnectTime(3000, 3)
        sdk.NET_DVR_SetReconnect(30000, True)
        _sdk = sdk
        _sdk_dir = sdk_dir
        logger.info("[hkptz] HCNetSDK 已初始化，库目录 %s", sdk_dir)
        return _sdk


# ============================================================ HkPtz
class HkPtz:
    """一台海康相机的 HCNetSDK 访问客户端（登录、云台控制、预置点、抓图）。"""

    def __init__(self, config: HkPtzConfig) -> None:
        self._config = config
        self._sdk = None
        self._user_id: int = -1
        self._dev_info: Optional[NET_DVR_DEVICEINFO_V40] = None
        # 云台坐标范围缓存（首次绝对定位/读状态时从能力集解析）：(xmin,xmax,ymin,ymax,zmin,zmax)
        self._ranges: Optional[tuple] = None

    # ------------------------------------------------------------ 配置（prefab 单点）
    @property
    def ip(self) -> str:
        return self._config.ip

    @property
    def port(self) -> int:
        return int(self._config.port)

    @property
    def http_port(self) -> int:
        return int(self._config.http_port)

    @property
    def username(self) -> str:
        return self._config.username

    @property
    def channel(self) -> int:
        return int(self._config.channel)

    @property
    def user_id(self) -> int:
        return self._user_id

    # ------------------------------------------------------------ 构建
    @classmethod
    def from_prefab_root(cls, prefab_root) -> "HkPtz":
        """在 prefab 节点树中查找 ``HkPtzConfig`` 并构造 HkPtz。找不到抛 ValueError。"""
        node = _find_node(prefab_root, HkPtzConfig)
        if node is None:
            raise ValueError("prefab_root 中未找到 HkPtzConfig 配置节点")
        return cls(node)

    @classmethod
    def from_prefab(cls, path: str | Path) -> "HkPtz":
        """从 data/prefabs/xx.prefab.json 加载配置树并构造 HkPtz。"""
        import json

        import app.prefab  # noqa: F401  触发节点类型注册（含 HkPtzConfig）
        from app.prefab.registry import build

        spec = json.loads(Path(path).read_text(encoding="utf-8"))
        root = build(spec.get("root") or {})
        return cls.from_prefab_root(root)

    # ------------------------------------------------------------ 连接生命周期
    def connect(self) -> None:
        """初始化 SDK（若尚未）并登录设备。失败抛 HkPtzError。"""
        if self._user_id >= 0:
            return
        self._sdk = _ensure_sdk(self._config.sdk_path)
        login = NET_DVR_USER_LOGIN_INFO()
        login.sDeviceAddress = self.ip.encode("utf-8")
        login.wPort = self.port
        login.sUserName = self.username.encode("utf-8")
        login.sPassword = self._config.password.encode("utf-8")
        login.bUseAsynLogin = 0            # 同步登录
        login.byLoginMode = 0             # 0-Private（SDK 私有协议）
        dev_info = NET_DVR_DEVICEINFO_V40()
        uid = self._sdk.NET_DVR_Login_V40(byref(login), byref(dev_info))
        if uid < 0:
            err = self._sdk.NET_DVR_GetLastError()
            raise HkPtzError(
                f"登录相机失败 {self.ip}:{self.port} user={self.username} "
                f"err={err}({_err_text(err)})")
        self._user_id = int(uid)
        self._dev_info = dev_info
        logger.info("[hkptz] 已登录相机 %s:%s 通道%d userId=%d",
                    self.ip, self.port, self.channel, self._user_id)

    def close(self) -> None:
        """注销登录（幂等）。SDK 全局初始化不在此释放（进程级单例）。"""
        if self._user_id >= 0 and self._sdk is not None:
            try:
                self._sdk.NET_DVR_Logout(self._user_id)
            finally:
                logger.info("[hkptz] 已注销相机 %s:%s userId=%d",
                            self.ip, self.port, self._user_id)
        self._user_id = -1
        self._dev_info = None

    @property
    def connected(self) -> bool:
        return self._user_id >= 0

    def __enter__(self) -> "HkPtz":
        self.connect()
        return self

    def __exit__(self, *exc) -> None:
        self.close()

    # ------------------------------------------------------------ 内部
    def _require(self):
        """返回 (sdk, userId, channel)；未登录抛 HkPtzError。"""
        if self._sdk is None or self._user_id < 0:
            raise HkPtzError("相机未登录，请先 connect() 或使用 with 上下文")
        return self._sdk, self._user_id, self.channel

    def _check(self, ok: bool, action: str) -> None:
        if not ok:
            err = self._sdk.NET_DVR_GetLastError()
            raise HkPtzError(f"{action}失败 ip={self.ip} err={err}({_err_text(err)})")

    # ------------------------------------------------------------ 设备信息
    def device_info(self) -> dict:
        """登录后缓存的设备信息：序列号 / 设备型号 / 通道数 / 起始通道。"""
        if self._dev_info is None:
            raise HkPtzError("尚未登录，无设备信息")
        v30 = self._dev_info.struDeviceV30
        serial = bytes(v30.sSerialNumber).split(b"\x00", 1)[0].decode("ascii", "replace")
        return {
            "ip": self.ip, "port": self.port,
            "serial_number": serial,
            "device_type": int(v30.wDevType),
            "analog_chan_num": int(v30.byChanNum),
            "start_chan": int(v30.byStartChan),
            "ip_chan_num": int(v30.byIPChanNum) + int(v30.byHighDChanNum) * 256,
            "start_d_chan": int(v30.byStartDChan),
        }

    # ------------------------------------------------------------ 云台控制
    def ptz(self, command: int, *, stop: bool = False,
            speed: int = DEFAULT_PTZ_SPEED, channel: Optional[int] = None) -> None:
        """云台控制（NET_DVR_PTZControlWithSpeed_Other）。

        command 为 HCNetSDK 云台命令（如 PAN_LEFT/TILT_UP/ZOOM_IN）；``stop=True`` 停止该动作。
        speed 1..7。方向类命令会持续运动，需再调一次 ``stop=True`` 才停。
        """
        sdk, uid, ch = self._require()
        ch = channel or ch
        ok = sdk.NET_DVR_PTZControlWithSpeed_Other(
            uid, ch, int(command), 1 if stop else 0, max(1, min(7, int(speed))))
        self._check(ok, "云台控制")

    # —— 便捷方向/变焦（speed 生效，stop=True 停止）——
    def pan_left(self, *, stop: bool = False, speed: int = DEFAULT_PTZ_SPEED) -> None:
        self.ptz(PAN_LEFT, stop=stop, speed=speed)

    def pan_right(self, *, stop: bool = False, speed: int = DEFAULT_PTZ_SPEED) -> None:
        self.ptz(PAN_RIGHT, stop=stop, speed=speed)

    def tilt_up(self, *, stop: bool = False, speed: int = DEFAULT_PTZ_SPEED) -> None:
        self.ptz(TILT_UP, stop=stop, speed=speed)

    def tilt_down(self, *, stop: bool = False, speed: int = DEFAULT_PTZ_SPEED) -> None:
        self.ptz(TILT_DOWN, stop=stop, speed=speed)

    def zoom_in(self, *, stop: bool = False, speed: int = DEFAULT_PTZ_SPEED) -> None:
        self.ptz(ZOOM_IN, stop=stop, speed=speed)

    def zoom_out(self, *, stop: bool = False, speed: int = DEFAULT_PTZ_SPEED) -> None:
        self.ptz(ZOOM_OUT, stop=stop, speed=speed)

    def stop(self) -> None:
        """停止全部云台运动（对已下发的方向命令逐一 stop）。"""
        for cmd in (PAN_LEFT, PAN_RIGHT, TILT_UP, TILT_DOWN, ZOOM_IN, ZOOM_OUT):
            try:
                self.ptz(cmd, stop=True)
            except HkPtzError:
                # 某个方向未在动时设备可能返回失败，忽略即可
                pass

    # ------------------------------------------------------------ 预置点
    def _preset(self, cmd: int, index: int, channel: Optional[int] = None) -> None:
        sdk, uid, ch = self._require()
        ch = channel or ch
        ok = sdk.NET_DVR_PTZPreset_Other(uid, ch, int(cmd), int(index))
        self._check(ok, f"预置点({cmd},{index})")

    def goto_preset(self, index: int) -> None:
        """转到预置点 index（1..255，取决于设备）。"""
        self._preset(GOTO_PRESET, index)

    def set_preset(self, index: int) -> None:
        """在当前位姿设置预置点 index。"""
        self._preset(SET_PRESET, index)

    def clean_preset(self, index: int) -> None:
        """清除预置点 index。"""
        self._preset(CLE_PRESET, index)

    # ------------------------------------------------------------ 抓图
    def snapshot(self, channel: Optional[int] = None, path: Optional[str | Path] = None) -> bytes:
        """抓图，返回 JPEG 字节（NET_DVR_CaptureJPEGPicture_NEW，抓进内存缓冲）。

        ``path`` 非空时同时把 JPEG 落盘。使用当前分辨率、最好画质。
        """
        sdk, uid, ch = self._require()
        ch = channel or ch
        para = NET_DVR_JPEGPARA()
        para.wPicSize = 0xff          # 0xff = 当前编码分辨率
        para.wPicQuality = 0          # 0 = 最好画质
        buf = create_string_buffer(_JPEG_BUF_SIZE)
        returned = c_uint32(0)
        ok = sdk.NET_DVR_CaptureJPEGPicture_NEW(
            uid, ch, byref(para), buf, _JPEG_BUF_SIZE, byref(returned))
        self._check(ok, "抓图")
        size = int(returned.value)
        if size <= 0:
            raise HkPtzError(f"抓图返回空数据 ip={self.ip} 通道{ch}")
        data = buf.raw[:size]
        if path:
            Path(path).write_bytes(data)
        return data

    # ------------------------------------------------------------ ISAPI（HTTP + digest）/ 绝对定位
    def _isapi_http(self, method: str, path: str, body: Optional[str] = None) -> str:
        """向相机发一条 HTTP ISAPI 请求（digest 鉴权），返回响应文本。

        云台绝对定位用 HTTP ISAPI 而非 SDK 的 STDXMLConfig 隧道——后者在部分固件上写操作
        不稳定（返回 err=11 且不一定执行）。HTTP 路径与 SDK 登录相互独立。
        """
        import requests
        from requests.auth import HTTPDigestAuth

        url = f"http://{self.ip}:{self.http_port}{path}"
        auth = HTTPDigestAuth(self.username, self._config.password)
        headers = {"Content-Type": "application/xml"} if body else None
        try:
            resp = requests.request(method.upper(), url, data=body.encode("utf-8") if body else None,
                                    auth=auth, headers=headers, timeout=_ISAPI_HTTP_TIMEOUT)
        except requests.RequestException as e:
            raise HkPtzError(f"ISAPI HTTP 请求失败 {method} {path}: {e}")
        if resp.status_code >= 400:
            raise HkPtzError(
                f"ISAPI HTTP {method} {path} 返回 {resp.status_code}: {resp.text[:200]}")
        return resp.text

    def isapi(self, method: str, path: str, body: Optional[str] = None) -> str:
        """发一条 ISAPI 请求（method + path，可选 body），返回响应文本。"""
        return self._isapi_http(method, path, body)

    def ptz_ranges(self, channel: Optional[int] = None, refresh: bool = False) -> tuple:
        """云台坐标范围 ``(xmin,xmax,ymin,ymax,zmin,zmax)``，来自能力集（缓存）。

        能力集读取/解析失败时回退到 :data:`_FALLBACK_RANGES`（设备仍会在下发时校验越界）。
        """
        if self._ranges is not None and not refresh:
            return self._ranges
        ch = channel or self.channel
        try:
            raw = self._isapi_http("GET", f"/ISAPI/PTZCtrl/channels/{ch}/capabilities")
            parsed = _parse_ptz_ranges(raw)
        except (HkPtzError, ValueError):
            parsed = None
        self._ranges = parsed or _FALLBACK_RANGES
        return self._ranges

    def absolute_move(self, pan_deg: float, tilt_deg: float, zoom: float = 1.0,
                      *, channel: Optional[int] = None) -> None:
        """云台绝对定位到 (pan, tilt, zoom)。

        pan/tilt 单位度（映射到 azimuth/elevation 的 0.1° 整数，按设备范围夹取，
        elevation 可为负）；zoom 为倍率比例（1.0=最广，absoluteZoom=round(ratio*10)，
        按设备 ZRange 夹取）。经 ISAPI ``PUT /ISAPI/PTZCtrl/channels/{ch}/absolute`` 下发。
        """
        ch = channel or self.channel
        xmin, xmax, ymin, ymax, zmin, zmax = self.ptz_ranges(ch)
        azimuth = _clamp_int(round(float(pan_deg) * _PAN_SCALE), xmin, xmax)
        elevation = _clamp_int(round(float(tilt_deg) * _TILT_SCALE), ymin, ymax)
        zoom_abs = _clamp_int(round(max(0.0, float(zoom)) * _ZOOM_SCALE), zmin, zmax)
        xml = (
            '<?xml version="1.0" encoding="UTF-8"?>'
            "<PTZData><AbsoluteHigh>"
            f"<elevation>{elevation}</elevation>"
            f"<azimuth>{azimuth}</azimuth>"
            f"<absoluteZoom>{zoom_abs}</absoluteZoom>"
            "</AbsoluteHigh></PTZData>"
        )
        self._isapi_http("PUT", f"/ISAPI/PTZCtrl/channels/{ch}/absolute", xml)
        logger.info("[hkptz] 绝对定位 通道%d pan=%.2f°(%d) tilt=%.2f°(%d) zoom=%.3f(%d)",
                    ch, float(pan_deg), azimuth, float(tilt_deg), elevation,
                    float(zoom), zoom_abs)

    def ptz_status(self, channel: Optional[int] = None) -> dict:
        """读取云台当前位姿（尽力解析 ISAPI status）。

        返回 ``{"pan":度, "tilt":度, "zoom":比例, "raw":原始XML文本}``；无法解析的字段为 None。
        """
        ch = channel or self.channel
        raw = self._isapi_http("GET", f"/ISAPI/PTZCtrl/channels/{ch}/status")
        return _parse_ptz_status(raw)

    def ptz_capabilities(self, channel: Optional[int] = None) -> str:
        """读取云台能力集原始 XML（含 pan/tilt/zoom 范围），用于现场标定坐标映射。"""
        ch = channel or self.channel
        return self._isapi_http("GET", f"/ISAPI/PTZCtrl/channels/{ch}/capabilities")


def _clamp_int(v: float, lo: int, hi: int) -> int:
    return max(lo, min(hi, int(v)))


def _strip_ns(tag: str) -> str:
    """去掉 XML 标签的命名空间前缀（ISAPI 响应带 xmlns）。"""
    return tag.rsplit("}", 1)[-1]


def _find_text(node, *names):
    """在子树中按去命名空间的标签名深度优先找第一个非空文本，返回 float 或 None。"""
    stack = [node]
    while stack:
        cur = stack.pop()
        for child in cur:
            if _strip_ns(child.tag) in names:
                text = (child.text or "").strip()
                if text:
                    try:
                        return float(text)
                    except ValueError:
                        return None
            stack.append(child)
    return None


def _parse_ptz_status(raw: str) -> dict:
    """尽力从 ISAPI PTZ status 响应解析 pan/tilt/zoom。解析不到的字段为 None。"""
    result: dict = {"pan": None, "tilt": None, "zoom": None, "raw": raw}
    try:
        root = ET.fromstring(raw)
    except ET.ParseError:
        return result
    azimuth = _find_text(root, "azimuth")
    elevation = _find_text(root, "elevation")
    zoom_abs = _find_text(root, "absoluteZoom")
    if azimuth is not None:
        result["pan"] = azimuth / _PAN_SCALE
    if elevation is not None:
        result["tilt"] = elevation / _TILT_SCALE
    if zoom_abs is not None:
        result["zoom"] = zoom_abs / _ZOOM_SCALE
    return result


def _parse_ptz_ranges(raw: str) -> Optional[tuple]:
    """从能力集 XML 解析 ``(xmin,xmax,ymin,ymax,zmin,zmax)``；解析不全返回 None。"""
    try:
        root = ET.fromstring(raw)
    except ET.ParseError:
        return None

    def range_of(space_tag: str, range_tag: str):
        for space in root.iter():
            if _strip_ns(space.tag) != space_tag:
                continue
            for rng in space:
                if _strip_ns(rng.tag) != range_tag:
                    continue
                lo = _find_text(rng, "Min")
                hi = _find_text(rng, "Max")
                if lo is not None and hi is not None:
                    return int(lo), int(hi)
        return None

    x = range_of("AbsolutePanTiltPositionSpace", "XRange")
    y = range_of("AbsolutePanTiltPositionSpace", "YRange")
    z = range_of("AbsoluteZoomPositionSpace", "ZRange")
    if not (x and y and z):
        return None
    return (x[0], x[1], y[0], y[1], z[0], z[1])


def _find_node(node, cls):
    """DFS 在 prefab 节点树中找第一个 cls 类型节点（含根）。"""
    if isinstance(node, cls):
        return node
    for child in node.child_nodes:
        found = _find_node(child, cls)
        if found is not None:
            return found
    return None
