"""机器人控制板通信协议 V2.0 — 帧编解码（与前端 TS 同规格）。

帧结构（大端）:
    帧头 0xA0AB(2) | 帧序号(2) | 消息长度(2) | 标记字(1) | 指令码(1) | 消息内容(可变) | CRC16(2) | 帧尾 0xCD(1)

- 帧序号: 0~65535 循环; 响应帧序号 = 请求帧序号
- 标记字: bit7=0 正常模式 / bit7=1 工程模式; bit6~bit0 版本号
- 校验: 覆盖 帧头~消息内容，见下方 `crc16_kermit`
"""
import logging
import struct

logger = logging.getLogger("rail.protocol")

FRAME_HEAD = 0xA0AB
FRAME_TAIL = 0xCD
HEADER_LEN = 8            # 帧头2 + 序号2 + 长度2 + 标记1 + 指令1
CRC_LEN = 2
MAX_PAYLOAD = 4096

#: 收到帧的 CRC 与本端算法不一致时，**是否仍然放行**。
#:
#: 2026-09-24 真机（192.168.8.91:16122）反推出下位机实际算法 = `crc16_kermit`
#: （反射 poly 0x8408 / init 0x0000），53/53 帧全中。**所以本开关正常应保持 False**
#: —— 严格校验才能真正挡住串扰/半包残片。
#:
#: 背景：文档《机器人控制板通信协议 V2.0》只写「CRC16-CCITT 标准」，本端曾按
#: CCITT-FALSE（poly 0x1021 / init 0xFFFF）实现，与下位机**完全不是一回事**：
#:   - `FrameParser._extract_one` 当年发现对不上，就把 CRC 校验注释掉了（放行一切）；
#:   - `decode_frame` 却还在严格校验 → 解析器放行的帧被解码器全部判无效
#:     → **真机上收到的每一帧都被丢弃**（实测 19 帧全丢），表现为"连接是通的，
#:     但位置/电量/固件版本全是 0"，同时下位机也拒收我们下发的帧（心跳/0x01 无响应）。
#: 两处策略必须一致：现在两边都用 `crc16_kermit`。
#:
#: 现场应急开关：万一将来固件换了校验算法导致整片丢帧，先置 True 恢复通信，
#: 再用 `scripts/probe_board_link.py --dump` + `scripts/solve_board_crc.py` 重新反推。
ACCEPT_CRC_MISMATCH = False

_crc_mismatch_count = 0


def crc_mismatch_count() -> int:
    """自进程启动以来 CRC 不匹配的帧数，供健康检查/诊断观察。"""
    return _crc_mismatch_count


# 指令码
CMD_HEARTBEAT = 0x06          # 心跳 [下发] 请求/响应内容均空
CMD_INIT = 0x01               # 初始化控制板 [下发]
CMD_GET_CONFIG = 0x02         # 获取控制板配置 [下发]
CMD_REBOOT = 0x03             # 重启控制板 [下发]
CMD_GET_VERSION = 0x04        # 获取版本号及 SN [下发]
CMD_TIME_SYNC = 0x05          # 时间校准 [下发]
CMD_MOTOR_POWER = 0x07        # 电机驱动器电源开关 [下发]
CMD_CHASSIS_MOVE = 0x09       # 底盘运动控制 [下发]
CMD_GET_CHASSIS = 0x0A        # 获取底盘运动状态 [下发]
CMD_UPLOAD_CHASSIS = 0x0B     # 上传底盘运动状态 [上发]
CMD_MOTOR_CTRL = 0x0C         # 电机控制(伸缩杆) [下发]
CMD_GET_MOTOR = 0x0D          # 获取指定电机状态 [下发]
CMD_UPLOAD_MOTOR = 0x0E       # 上传电机状态 [上发]
CMD_UNSUPPORTED = 0xFF        # 内部: 未支持指令


def crc16_kermit(data: bytes, init: int = 0x0000) -> int:
    """下位机实际使用的校验：**CRC-16/KERMIT**。

    poly=0x1021（反射形式 0x8408）, init=0x0000, refin=true, refout=true, xorout=0x0000,
    标准 check 值 ``crc16_kermit(b"123456789") == 0x2189``。

    ⚠️ 不要换回 `crc16_ccitt`：文档写的"CRC16-CCITT 标准"指的是**反射版**，
    下位机固件实现的就是本函数（2026-09-24 用 53 帧真机报文反推并全部复核通过）。
    """
    crc = init & 0xFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ 0x8408 if crc & 1 else crc >> 1
    return crc & 0xFFFF


def crc16_ccitt(data: bytes, init: int = 0xFFFF) -> int:
    """CRC16-CCITT (CCITT-FALSE): poly=0x1021, init=0xFFFF, 无反射, 无异或输出。

    ⚠️ 仅作对照/单测用，**下位机不用它**（见 `crc16_kermit` 的说明）。
    """
    crc = init
    for b in data:
        crc ^= b << 8
        for _ in range(8):
            if crc & 0x8000:
                crc = ((crc << 1) ^ 0x1021) & 0xFFFF
            else:
                crc = (crc << 1) & 0xFFFF
    return crc


def encode_frame(seq: int, cmd: int, payload: bytes = b"", marker: int = 0) -> bytes:
    """组装完整协议帧。seq/cmd/marker 自动截断到合法范围。"""
    payload = bytes(payload)
    if len(payload) > MAX_PAYLOAD:
        raise ValueError(f"payload too long: {len(payload)} > {MAX_PAYLOAD}")
    body = struct.pack(">HHHBB", FRAME_HEAD, seq & 0xFFFF, len(payload), marker & 0xFF, cmd & 0xFF) + payload
    crc = crc16_kermit(body)
    return body + struct.pack(">H", crc) + bytes([FRAME_TAIL])


def decode_frame(frame: bytes):
    """解析单帧 → (seq, marker, cmd, payload)。校验帧头/长度/CRC/帧尾, 失败返回 None。

    ⚠️ CRC 的处置见 `ACCEPT_CRC_MISMATCH`：默认**严格校验**（与 `FrameParser`
    一致地用 `crc16_kermit`）。
    """
    global _crc_mismatch_count
    if len(frame) < HEADER_LEN + CRC_LEN + 1:
        return None
    if frame[0] != 0xA0 or frame[1] != 0xAB:
        return None
    _head, seq, mlen, marker, cmd = struct.unpack_from(">HHHBB", frame, 0)
    if mlen > MAX_PAYLOAD or len(frame) != HEADER_LEN + mlen + CRC_LEN + 1:
        return None
    if frame[-1] != FRAME_TAIL:
        return None
    got = struct.unpack_from(">H", frame, HEADER_LEN + mlen)[0]
    if crc16_kermit(frame[:HEADER_LEN + mlen]) != got:
        _crc_mismatch_count += 1
        if _crc_mismatch_count == 1 or _crc_mismatch_count % 200 == 0:
            logger.warning(
                "[protocol] CRC 不匹配第 %d 次（帧内 0x%04X / KERMIT 0x%04X, cmd=0x%02X）；"
                "按 ACCEPT_CRC_MISMATCH=%s 处置",
                _crc_mismatch_count, got, crc16_kermit(frame[:HEADER_LEN + mlen]), cmd,
                ACCEPT_CRC_MISMATCH)
        if not ACCEPT_CRC_MISMATCH:
            return None
    return seq, marker, cmd, frame[HEADER_LEN:HEADER_LEN + mlen]


class FrameParser:
    """字节流 → 完整帧列表; 处理粘包/半包/垃圾重同步/坏帧跳过。"""

    def __init__(self, max_payload: int = MAX_PAYLOAD):
        self.buf = bytearray()
        self.max_payload = max_payload
        self.discarded = 0  # 累计丢弃字节数(调试)

    def feed(self, data: bytes) -> list:
        """喂入一段字节, 返回本次解析出的完整帧列表(bytes)。"""
        self.buf.extend(data)
        frames = []
        while True:
            r = self._extract_one()
            if r is None:          # 数据不足
                break
            if r is False:         # 无效帧, 已跳过, 继续找
                continue
            frames.append(r)
        return frames

    def _extract_one(self):
        """返回: bytes=完整帧, False=无效帧(已跳垃圾/坏帧), None=数据不足。

        ⚠️ **本层不做 CRC 校验**，切帧只看 帧头 / 长度 / 帧尾；CRC 判定统一交给
        `decode_frame`（用 `crc16_kermit`）。两层职责分开、但**算法必须一致** ——
        历史上解析层把校验注释掉、解码层还在按错误的算法校验，导致真机每一帧都被丢掉。
        """
        idx = self.buf.find(b"\xA0\xAB")
        if idx < 0:
            self.discarded += len(self.buf)
            self.buf.clear()       # 无帧头, 全部丢弃(帧头至少 2 字节, find 未命中即无完整帧头)
            return None
        if idx > 0:
            self.discarded += idx
            del self.buf[:idx]     # 丢弃帧头前的垃圾
        if len(self.buf) < HEADER_LEN:
            return None
        _head, _seq, mlen, _marker, _cmd = struct.unpack_from(">HHHBB", self.buf, 0)
        if mlen > self.max_payload:
            # 长度异常: 跳过 2 字节后重同步
            self.discarded += 2
            del self.buf[:2]
            logger.debug("[parser] 长度异常 mlen=%d, 跳过 2 字节重同步", mlen)
            return False
        total = HEADER_LEN + mlen + CRC_LEN + 1
        if len(self.buf) < total:
            return None
        frame = bytes(self.buf[:total])
        del self.buf[:total]
        if frame[-1] != FRAME_TAIL:
            self.discarded += total
            logger.debug("[parser] 帧尾不符 0x%02X, 丢弃 %d 字节", frame[-1], total)
            return False
        logger.debug("[parser] 切出完整帧 len=%d cmd=0x%02X", total, _cmd)
        return frame
