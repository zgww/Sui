/**
 * 机器人控制板通信协议 V2.0 — 帧编解码（与后端 Python 同规格）。
 * 帧结构(大端): 帧头0xA0AB(2) | 帧序号(2) | 消息长度(2) | 标记字(1) | 指令码(1) | 内容(可变) | CRC16(2) | 帧尾0xCD(1)
 */

export const FRAME_HEAD = 0xa0ab
export const FRAME_TAIL = 0xcd
export const HEADER_LEN = 8
export const CRC_LEN = 2

export const CMD = {
  INIT: 0x01,
  GET_CONFIG: 0x02,
  REBOOT: 0x03,
  GET_VERSION: 0x04,
  TIME_SYNC: 0x05,
  HEARTBEAT: 0x06,
  MOTOR_POWER: 0x07,
  CHASSIS_MOVE: 0x09,
  GET_CHASSIS: 0x0a,
  UPLOAD_CHASSIS: 0x0b,
  MOTOR_CTRL: 0x0c,
  GET_MOTOR: 0x0d,
  UPLOAD_MOTOR: 0x0e,
} as const

/**
 * 下位机实际使用的校验：CRC-16/KERMIT
 * poly=0x1021(反射 0x8408), init=0x0000, refin/refout=true, xorout=0x0000。
 * check: crc16Kermit("123456789") === 0x2189
 *
 * ⚠️ 别换回 CCITT-FALSE(poly 0x1021/init 0xFFFF/无反射)：文档只写"CRC16-CCITT 标准"，
 * 但真机固件实现的是反射版 init=0（2026-09-24 用 53 帧真机报文反推并全部复核通过）。
 * 与 backend/app/simulation/protocol.py 的 crc16_kermit 必须保持一致。
 */
export function crc16Kermit(data: Uint8Array, init = 0x0000): number {
  let crc = init & 0xffff
  for (const b of data) {
    crc ^= b
    for (let i = 0; i < 8; i++) {
      crc = crc & 1 ? (crc >> 1) ^ 0x8408 : crc >> 1
    }
  }
  return crc & 0xffff
}

/** 对照用：CRC16-CCITT (CCITT-FALSE)。下位机不用它，仅保留给排查/单测。 */
export function crc16ccitt(data: Uint8Array, init = 0xffff): number {
  let crc = init
  for (const b of data) {
    crc ^= b << 8
    for (let i = 0; i < 8; i++) {
      crc = crc & 0x8000 ? ((crc << 1) ^ 0x1021) & 0xffff : (crc << 1) & 0xffff
    }
  }
  return crc
}

export interface DecodedFrame {
  seq: number
  marker: number
  cmd: number
  payload: Uint8Array
}

export function encodeFrame(seq: number, cmd: number, payload: Uint8Array | number[] = [], marker = 0): Uint8Array {
  const pl = payload instanceof Uint8Array ? payload : new Uint8Array(payload)
  const buf = new Uint8Array(HEADER_LEN + pl.length + CRC_LEN + 1)
  const dv = new DataView(buf.buffer)
  dv.setUint16(0, FRAME_HEAD, false)
  dv.setUint16(2, seq & 0xffff, false)
  dv.setUint16(4, pl.length, false)
  dv.setUint8(6, marker & 0xff)
  dv.setUint8(7, cmd & 0xff)
  buf.set(pl, HEADER_LEN)
  const crc = crc16Kermit(buf.subarray(0, HEADER_LEN + pl.length))
  dv.setUint16(HEADER_LEN + pl.length, crc, false)
  buf[buf.length - 1] = FRAME_TAIL
  return buf
}

export function decodeFrame(buf: Uint8Array): DecodedFrame | null {
  if (buf.length < HEADER_LEN + CRC_LEN + 1) return null
  const dv = new DataView(buf.buffer, buf.byteOffset, buf.byteLength)
  if (dv.getUint16(0, false) !== FRAME_HEAD) return null
  const seq = dv.getUint16(2, false)
  const mlen = dv.getUint16(4, false)
  const marker = dv.getUint8(6)
  const cmd = dv.getUint8(7)
  if (buf.length !== HEADER_LEN + mlen + CRC_LEN + 1) return null
  if (buf[buf.length - 1] !== FRAME_TAIL) return null
  const got = dv.getUint16(HEADER_LEN + mlen, false)
  if (crc16Kermit(buf.subarray(0, HEADER_LEN + mlen)) !== got) return null
  return { seq, marker, cmd, payload: buf.slice(HEADER_LEN, HEADER_LEN + mlen) }
}

/** 大端工具 */
export const be = {
  u16: (b: Uint8Array, o = 0) => new DataView(b.buffer, b.byteOffset, b.byteLength).getUint16(o, false),
  i16: (b: Uint8Array, o = 0) => new DataView(b.buffer, b.byteOffset, b.byteLength).getInt16(o, false),
  u32: (b: Uint8Array, o = 0) => new DataView(b.buffer, b.byteOffset, b.byteLength).getUint32(o, false),
  i32: (b: Uint8Array, o = 0) => new DataView(b.buffer, b.byteOffset, b.byteLength).getInt32(o, false),
  packU16: (v: number) => {
    const b = new Uint8Array(2)
    new DataView(b.buffer).setUint16(0, v & 0xffff, false)
    return b
  },
  packI16: (v: number) => {
    const b = new Uint8Array(2)
    new DataView(b.buffer).setInt16(0, Math.max(-32768, Math.min(32767, Math.round(v))), false)
    return b
  },
  packI32: (v: number) => {
    const b = new Uint8Array(4)
    new DataView(b.buffer).setInt32(0, Math.max(-2147483648, Math.min(2147483647, Math.round(v))), false)
    return b
  },
}
