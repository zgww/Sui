import React, { useState, useEffect, useRef, useCallback } from 'react'
import { Button, Input, Tag, Toast } from '@douyinfe/semi-ui'
import { IconPlay, IconPause, IconClear, IconDownload, IconSearch } from '@douyinfe/semi-icons'

export default function BackendLogViewer() {
  const [lines, setLines] = useState<string[]>([])
  const [paused, setPaused] = useState(false)
  const [filter, setFilter] = useState('')
  const logEndRef = useRef<HTMLDivElement>(null)
  const eventSourceRef = useRef<EventSource | null>(null)
  const pausedLinesRef = useRef<string[]>([])

  // Load initial tail
  const loadTail = useCallback(async () => {
    try {
      const token = localStorage.getItem('fms_token')
      const params = new URLSearchParams({ lines: '200' })
      if (filter) params.set('filter', filter)
      const resp = await fetch(`/api/logs/backend/tail?${params}`, {
        headers: { Authorization: `Bearer ${token}` },
      })
      const data = await resp.json()
      setLines(data.lines || [])
    } catch { /* */ }
  }, [filter])

  // Start SSE stream
  const startStream = useCallback(() => {
    if (eventSourceRef.current) return
    const token = localStorage.getItem('fms_token')
    const params = new URLSearchParams()
    if (filter) params.set('filter', filter)
    const es = new EventSource(`/api/logs/backend/stream?${params}&token=${token}`)
    eventSourceRef.current = es

    es.onmessage = (event) => {
      const line = event.data
      if (!paused) {
        setLines(prev => [...prev.slice(-1999), line])
      } else {
        pausedLinesRef.current.push(line)
      }
    }

    es.onerror = () => {
      es.close()
      eventSourceRef.current = null
      // Retry after 3s
      setTimeout(() => { if (!paused) startStream() }, 3000)
    }
  }, [paused, filter])

  // Stop SSE stream
  const stopStream = useCallback(() => {
    if (eventSourceRef.current) {
      eventSourceRef.current.close()
      eventSourceRef.current = null
    }
  }, [])

  // Toggle pause
  const togglePause = () => {
    if (paused) {
      // Resume - flush buffered lines
      const buffered = pausedLinesRef.current
      pausedLinesRef.current = []
      setLines(prev => [...prev, ...buffered].slice(-2000))
      setPaused(false)
      startStream()
    } else {
      stopStream()
      setPaused(true)
    }
  }

  const clearLogs = () => {
    setLines([])
    pausedLinesRef.current = []
  }

  const doExport = async () => {
    const token = localStorage.getItem('fms_token')
    window.open(`/api/logs/backend/export?token=${token}`, '_blank')
  }

  const applyFilter = () => {
    stopStream()
    setLines([])
    loadTail()
    if (!paused) setTimeout(startStream, 500)
  }

  // Init
  useEffect(() => {
    loadTail()
    startStream()
    return () => stopStream()
  }, [])

  // Auto scroll
  useEffect(() => {
    logEndRef.current?.scrollIntoView({ behavior: 'smooth' })
  }, [lines])

  const filteredLines = filter
    ? lines.filter(l => l.toLowerCase().includes(filter.toLowerCase()))
    : lines

  return (
    <div>
      {/* Toolbar */}
      <div style={{
        display: 'flex', alignItems: 'center', gap: 8, marginBottom: 12,
        padding: '8px 12px', background: '#f5f5f5', borderRadius: 6,
      }}>
        <Button size="small" icon={paused ? <IconPlay /> : <IconPause />}
          onClick={togglePause}
          type={paused ? 'primary' : 'tertiary'}>
          {paused ? '继续' : '暂停'}
        </Button>
        <Button size="small" icon={<IconClear />} onClick={clearLogs}>清屏</Button>
        <Button size="small" icon={<IconDownload />} onClick={doExport}>导出</Button>
        <div style={{ flex: 1 }} />
        <Input
          size="small"
          placeholder="关键字过滤..."
          prefix={<IconSearch />}
          value={filter}
          onChange={(v: string) => setFilter(v)}
          onEnterPress={applyFilter}
          style={{ width: 200 }}
        />
        <Button size="small" onClick={applyFilter}>过滤</Button>
        <Tag color={paused ? 'orange' : 'green'} size="small">
          {paused ? '已暂停' : `实时 (${lines.length} 行)`}
        </Tag>
      </div>

      {/* Log content */}
      <div style={{
        background: '#1e1e1e', color: '#d4d4d4',
        fontFamily: 'Consolas, Monaco, "Courier New", monospace',
        fontSize: 12, lineHeight: 1.6,
        height: 'calc(100vh - 260px)', overflow: 'auto',
        borderRadius: 6, padding: '12px 16px',
        whiteSpace: 'pre-wrap', wordBreak: 'break-all',
      }}>
        {filteredLines.length === 0 ? (
          <div style={{ color: '#666', textAlign: 'center', paddingTop: 40 }}>
            暂无日志
          </div>
        ) : (
          filteredLines.map((line, i) => {
            let color = '#d4d4d4'
            if (/error|ERROR|FATAL/i.test(line)) color = '#f44747'
            else if (/warn|WARNING|WARN/i.test(line)) color = '#cca700'
            else if (/info|INFO/i.test(line)) color = '#6a9955'
            return (
              <div key={i} style={{ color }}>
                {line}
              </div>
            )
          })
        )}
        <div ref={logEndRef} />
      </div>
    </div>
  )
}
