import { useEffect, useRef, useState, useCallback } from 'react'
import { Card, Toast } from '@douyinfe/semi-ui'
import { Terminal as XTerm } from '@xterm/xterm'
import { FitAddon } from 'xterm-addon-fit'
import '@xterm/xterm/css/xterm.css'
import { useRobotId } from '../store/robot'

// 获取 WebSocket 基础 URL
function wsBase(): string {
  const protocol = location.protocol === 'https:' ? 'wss:' : 'ws:'
  return `${protocol}//${location.host}`
}

export default function TerminalPage() {
  const { selectedRid: rid } = useRobotId()
  const [connected, setConnected] = useState(false)

  const termRef = useRef<HTMLDivElement>(null)
  const xtermRef = useRef<XTerm | null>(null)
  const fitAddonRef = useRef<FitAddon | null>(null)
  const wsRef = useRef<WebSocket | null>(null)
  const disposedRef = useRef(false)

  const cleanup = useCallback(() => {
    disposedRef.current = true
    try { wsRef.current?.close() } catch {}
    wsRef.current = null
    try { xtermRef.current?.dispose() } catch {}
    xtermRef.current = null
    setConnected(false)
  }, [])

  const connect = useCallback((robotId: number) => {
    cleanup()

    disposedRef.current = false
    const token = localStorage.getItem('fms_token') || ''
    const url = `${wsBase()}/api/terminal/${robotId}/ws?token=${encodeURIComponent(token)}`

    // 创建 xterm 实例
    const fitAddon = new FitAddon()
    fitAddonRef.current = fitAddon

    const term = new XTerm({
      cursorBlink: true,
      cursorStyle: 'bar',
      fontSize: 14,
      fontFamily: 'Consolas, Monaco, "Courier New", monospace',
      theme: {
        background: '#1e1e1e',
        foreground: '#d4d4d4',
        cursor: '#ffffff',
        selectionBackground: '#264f78',
        black: '#000000',
        red: '#cd3131',
        green: '#0dbc79',
        yellow: '#e5e510',
        blue: '#2472c8',
        magenta: '#bc3fbc',
        cyan: '#11a8cd',
        white: '#e5e5e5',
        brightBlack: '#666666',
        brightRed: '#f14c4c',
        brightGreen: '#23d18b',
        brightYellow: '#f5f543',
        brightBlue: '#3b8eea',
        brightMagenta: '#d670d6',
        brightCyan: '#29b8db',
        brightWhite: '#ffffff',
      },
      allowProposedApi: true,
      allowTransparency: false,
      cols: 120,
      rows: 30,
    })
    term.loadAddon(fitAddon)
    xtermRef.current = term

    // 挂载到 DOM
    if (termRef.current) {
      term.open(termRef.current)
      try { fitAddon.fit() } catch {}
    }

    // 用户输入 → WebSocket
    term.onData((data) => {
      if (wsRef.current?.readyState === WebSocket.OPEN) {
        wsRef.current.send(data)
      }
    })

    // 窗口大小变化 → resize PTY
    term.onResize(({ cols, rows }) => {
      if (wsRef.current?.readyState === WebSocket.OPEN) {
        wsRef.current.send(JSON.stringify({ type: 'resize', cols, rows }))
      }
    })

    // 建立 WebSocket
    const ws = new WebSocket(url)
    ws.binaryType = 'arraybuffer'
    wsRef.current = ws

    ws.onopen = () => {
      if (disposedRef.current) return
      setConnected(true)
      term.focus()
      // 发送初始大小
      ws.send(JSON.stringify({ type: 'resize', cols: term.cols, rows: term.rows }))
    }

    ws.onmessage = (ev) => {
      if (disposedRef.current) return
      if (ev.data instanceof ArrayBuffer) {
        term.write(new Uint8Array(ev.data))
      } else if (typeof ev.data === 'string') {
        term.write(ev.data)
      }
    }

    ws.onclose = () => {
      if (disposedRef.current) return
      setConnected(false)
      term.write('\r\n\x1b[33m[连接已关闭]\x1b[0m\r\n')
    }

    ws.onerror = () => {
      if (disposedRef.current) return
      term.write('\r\n\x1b[31m[连接错误]\x1b[0m\r\n')
    }
  }, [cleanup])

  // 切换机器人
  useEffect(() => {
    if (rid != null) {
      connect(rid)
    } else {
      cleanup()
    }
    return cleanup
  }, [rid])

  // 响应窗口大小变化
  useEffect(() => {
    const onResize = () => {
      try { fitAddonRef.current?.fit() } catch {}
    }
    window.addEventListener('resize', onResize)
    return () => window.removeEventListener('resize', onResize)
  }, [])

  return (
    <div className="page-container">
      <div className="mb-12">
        <h2 style={{ margin: 0 }}>终端调试</h2>
        <span className="text-muted" style={{ fontSize: 13 }}>
          {connected ? (
            <span style={{ color: '#52c41a' }}>● 已连接 — 可直接输入命令</span>
          ) : (
            <span>请选择机器人建立终端连接</span>
          )}
        </span>
      </div>

      <Card
        className="card-shadow"
        bordered={false}
        bodyStyle={{ padding: 0 }}
      >
        <div
          ref={termRef}
          style={{
            width: '100%',
            height: 'calc(100vh - 260px)',
            minHeight: 400,
          }}
        />
      </Card>
    </div>
  )
}
