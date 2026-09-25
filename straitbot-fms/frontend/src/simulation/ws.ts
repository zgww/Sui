/**
 * 仿真页 WebSocket 客户端(二进制协议帧 + 文本保活)。
 * 连接后端 /ws/simulation(经 vite 代理), 后端再与 TCP 上位机双向转发。
 * 注意: 前端是"机器人"侧, 不主动发协议心跳(0x06 由上位机下发, 前端响应)。
 *
 * 健壮性:
 * - 指数退避自动重连(500ms 起, 上限 10s);
 * - 应用层 ping/pong 看门狗: 每 5s 发文本 "ping", 服务端回 "pong";
 *   若连续约 15s 收不到任何消息(含 pong / 协议帧), 判定 WS 半开并强制重建
 *   (后端被强杀重启、代理静默断链时, 浏览器可能收不到 close, onclose 不触发);
 * - 页面从后台切回前台(visibilitychange)立即做一次健康检查/重连。
 */
import { decodeFrame, type DecodedFrame } from './protocol'

export type WsStatus = 'connecting' | 'open' | 'closed'

const MAX_RETRY = 10000 // 重连退避上限 ms
const PING_INTERVAL = 5000 // 保活探测周期 ms
const STALE_TIMEOUT = 15000 // 超过该时长无任何入站消息即判定半开 ms

export class SimWs {
  private ws: WebSocket | null = null
  private gen = 0 // 代次: 每次(重)连自增, 使旧连接回调失效
  private retryMs = 500
  private retryTimer: ReturnType<typeof setTimeout> | null = null
  private pingTimer: ReturnType<typeof setInterval> | null = null
  private lastRxAt = 0
  private closed = false
  private onFrame: (f: DecodedFrame) => void
  private onStatus: (s: WsStatus) => void
  private pending: Uint8Array[] = [] // 连接中暂存待发帧
  private readonly _onVisible = () => {
    if (document.visibilityState === 'visible') this._healthCheck()
  }

  constructor(onFrame: (f: DecodedFrame) => void, onStatus: (s: WsStatus) => void) {
    this.onFrame = onFrame
    this.onStatus = onStatus
  }

  connect() {
    this.closed = false
    document.addEventListener('visibilitychange', this._onVisible)
    if (this.pingTimer === null) {
      this.pingTimer = setInterval(() => this._tick(), PING_INTERVAL)
    }
    this._open()
  }

  private _open() {
    if (this.closed) return
    // 关闭并作废旧连接
    const old = this.ws
    if (old) {
      try {
        old.onclose = null
        old.onerror = null
        old.onmessage = null
        old.onopen = null
        old.close()
      } catch { /* noop */ }
    }
    if (this.retryTimer !== null) {
      clearTimeout(this.retryTimer)
      this.retryTimer = null
    }
    const g = ++this.gen
    this.ws = null
    this.onStatus('connecting')

    const proto = location.protocol === 'https:' ? 'wss' : 'ws'
    const url = `${proto}://${location.host}/ws/simulation`
    let ws: WebSocket
    try {
      ws = new WebSocket(url)
    } catch {
      this._scheduleRetry()
      return
    }
    this.ws = ws
    ws.binaryType = 'arraybuffer'

    ws.onopen = () => {
      if (g !== this.gen || this.closed) return
      this.retryMs = 500
      this.lastRxAt = Date.now()
      this.onStatus('open')
      for (const f of this.pending) ws.send(f)
      this.pending = []
      try { ws.send('ping') } catch { /* noop */ }
    }
    ws.onmessage = (ev) => {
      if (g !== this.gen || this.closed) return
      this.lastRxAt = Date.now() // pong 与协议帧都视为链路存活
      if (typeof ev.data === 'string') return // 文本仅为 pong 保活
      if (!(ev.data instanceof ArrayBuffer)) return
      const f = decodeFrame(new Uint8Array(ev.data))
      if (f) this.onFrame(f)
    }
    ws.onclose = () => {
      if (g !== this.gen || this.closed) return
      this.onStatus('closed')
      this._scheduleRetry()
    }
    ws.onerror = () => {
      try { ws.close() } catch { /* noop, 随后 onclose 触发重连 */ }
    }
  }

  /** 周期保活 + 半开门狗 */
  private _tick() {
    if (this.closed) return
    const ws = this.ws
    if (ws && ws.readyState === WebSocket.OPEN) {
      try { ws.send('ping') } catch { /* noop */ }
      if (this.lastRxAt && Date.now() - this.lastRxAt > STALE_TIMEOUT) {
        // 长时间无任何响应: 链路半开, 立即强制重建
        this.onStatus('connecting')
        this._open()
      }
    } else if (!ws || ws.readyState === WebSocket.CLOSED) {
      // 兜底: 没有存活连接且未在退避流程中时, 主动尝试
      if (this.retryTimer === null) this._open()
    }
  }

  /** 回到前台时立即探测; 死链/陈旧则立即重连 */
  private _healthCheck() {
    if (this.closed) return
    const ws = this.ws
    if (!ws || ws.readyState !== WebSocket.OPEN) {
      this._open()
      return
    }
    if (this.lastRxAt && Date.now() - this.lastRxAt > STALE_TIMEOUT) {
      this.onStatus('connecting')
      this._open()
    } else {
      try { ws.send('ping') } catch { /* noop */ }
    }
  }

  private _scheduleRetry() {
    if (this.closed) return
    if (this.retryTimer !== null) return
    const wait = this.retryMs
    this.retryMs = Math.min(this.retryMs * 2, MAX_RETRY)
    this.retryTimer = setTimeout(() => {
      this.retryTimer = null
      this._open()
    }, wait)
  }

  /** 发送协议帧; 连接中暂存, 打开后发出 */
  send(frame: Uint8Array) {
    if (this.ws && this.ws.readyState === WebSocket.OPEN) {
      this.ws.send(frame)
    } else if (this.pending.length < 200) {
      this.pending.push(frame)
    }
  }

  close() {
    this.closed = true
    if (this.pingTimer !== null) {
      clearInterval(this.pingTimer)
      this.pingTimer = null
    }
    if (this.retryTimer !== null) {
      clearTimeout(this.retryTimer)
      this.retryTimer = null
    }
    document.removeEventListener('visibilitychange', this._onVisible)
    if (this.ws) {
      try { this.ws.close() } catch { /* noop */ }
      this.ws = null
    }
  }
}
