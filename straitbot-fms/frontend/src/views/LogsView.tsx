import React, { useState, useRef, useEffect } from 'react'
import { Button, Card, Table, Row, Col, Modal, TextArea, Banner, Popconfirm, Dropdown, Toast } from '@douyinfe/semi-ui'
import { IconRefresh, IconDownload, IconChevronDown } from '@douyinfe/semi-icons'
import dayjs from 'dayjs'
import { useRobotId } from '../store/robot'
import { useUser } from '../store/user'
import { archivedList, archivedDownloadUrl, archivedDelete } from '../api/robots'
import { getAiSettings, analyzeLog } from '../api/ai'
import { renderMd } from '../utils/md'
import type { ArchivedLog, ArchivedLogs, ChatMessage } from '../types'

function human(b: number): string {
  if (!b) return '-'
  if (b < 1024) return b + 'B'
  if (b < 1048576) return (b / 1024).toFixed(1) + 'K'
  return (b / 1048576).toFixed(1) + 'M'
}

function fmt(t: string): string {
  return t ? dayjs(t).format('MM-DD HH:mm') : '-'
}

function escapeHtml(s: string): string {
  return s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;')
}

export default function LogsView() {
  const user = useUser()
  const { selectedRid: rid } = useRobotId()
  const [archived, setArchived] = useState<ArchivedLogs>({ uploaded: [], fetched: [] })
  const [aiEnabled, setAiEnabled] = useState(false)

  // AI 对话弹窗状态
  const [aiVisible, setAiVisible] = useState(false)
  const [aiFilename, setAiFilename] = useState('')
  const [messages, setMessages] = useState<ChatMessage[]>([])
  const [pending, setPending] = useState('')
  const [input, setInput] = useState('')
  const [streaming, setStreaming] = useState(false)

  // Refs for async loop
  const chatBoxRef = useRef<HTMLDivElement>(null)
  const abortRef = useRef(false)
  const streamingRef = useRef(false)
  const kindRef = useRef('')
  const logIdRef = useRef(0)
  const filenameRef = useRef('')
  const sendRef = useRef<(q: string) => void>(() => {})

  const load = async (id?: number) => {
    const targetRid = id ?? rid
    if (!targetRid) return
    try {
      const { data } = await archivedList(targetRid)
      setArchived(data)
    } catch {
      /* http 拦截器已处理错误提示 */
    }
  }

  const loadAiEnabled = async () => {
    try {
      const { data } = await getAiSettings()
      setAiEnabled(!!data.enabled)
    } catch {
      /* ignore */
    }
  }

  useEffect(() => {
    loadAiEnabled()
  }, [])

  useEffect(() => {
    if (rid) load(rid)
  }, [rid]) // eslint-disable-line react-hooks/exhaustive-deps

  // 滚动到底部
  useEffect(() => {
    if (chatBoxRef.current) {
      chatBoxRef.current.scrollTop = chatBoxRef.current.scrollHeight
    }
  }, [messages, pending, aiVisible])

  const dl = (kind: string, row: ArchivedLog) => {
    if (!rid) return
    window.open(archivedDownloadUrl(rid, kind, row.id), '_blank')
  }

  const del = async (kind: string, row: ArchivedLog) => {
    if (!rid) return
    try {
      await archivedDelete(rid, kind, row.id)
      Toast.success('已删除')
      load()
    } catch {
      /* http 拦截器已处理错误提示 */
    }
  }

  const openAi = (kind: string, row: ArchivedLog) => {
    setAiVisible(true)
    kindRef.current = kind
    logIdRef.current = row.id
    setAiFilename(row.filename)
    filenameRef.current = row.filename
    setMessages([])
    setPending('')
    setInput('')
    setStreaming(false)
    streamingRef.current = false
    abortRef.current = false
    setTimeout(() => sendRef.current(''), 150)
  }

  async function send(question: string) {
    const q = (question || '').trim()
    if (streamingRef.current) return

    let baseMessages = messages
    if (q) {
      baseMessages = [...messages, { role: 'user' as const, content: q }]
      setMessages(baseMessages)
      setInput('')
    } else if (messages.length === 0) {
      // 首轮空问题: 后端按默认模板分析
    } else {
      Toast.warning('请输入问题')
      return
    }

    streamingRef.current = true
    setStreaming(true)
    abortRef.current = false
    setPending('')

    try {
      let received = ''
      const history = q
        ? baseMessages.slice(0, -1).map((m) => ({ role: m.role, content: m.content }))
        : []

      for await (const piece of analyzeLog(kindRef.current, logIdRef.current, history, q)) {
        if (abortRef.current) break
        received += piece
        setPending(received)
      }

      if (received.trim()) {
        setMessages((prev) => [...prev, { role: 'assistant', content: received }])
      } else if (!q) {
        setMessages((prev) => [
          ...prev,
          {
            role: 'assistant',
            content:
              '⚠️ AI 未返回内容。请检查「AI 分析设置」: 启用开关、API Key、协议(Anthropic)、地址、模型名 glm-5.2。',
          },
        ])
      } else {
        setMessages((prev) => [...prev, { role: 'assistant', content: '⚠️ 未收到回复, 请检查 AI 配置。' }])
      }
    } catch (e: any) {
      setMessages((prev) => [...prev, { role: 'assistant', content: `❌ ${e.message}` }])
    } finally {
      setPending('')
      streamingRef.current = false
      setStreaming(false)
    }
  }

  // 更新 sendRef 以便 setTimeout 调用最新版本
  sendRef.current = send

  const clearChat = () => {
    setMessages([])
    setPending('')
  }

  // ---- 导出 ----
  function downloadFile(content: string, filename: string, mime: string) {
    const blob = new Blob([content], { type: mime + ';charset=utf-8' })
    const url = URL.createObjectURL(blob)
    const a = document.createElement('a')
    a.href = url
    a.download = filename
    document.body.appendChild(a)
    a.click()
    document.body.removeChild(a)
    setTimeout(() => URL.revokeObjectURL(url), 1000)
  }

  function baseName() {
    const f = (filenameRef.current || 'ai-report').replace(/\.[^.]+$/, '')
    const ts = new Date().toISOString().slice(0, 19).replace(/[:T]/g, '')
    return `${f}_AI对话_${ts}`
  }

  function exportMd() {
    if (!messages.length) return
    const md = messages
      .map((m) => (m.role === 'user' ? `## 🧑 我\n\n${m.content}` : `## 🤖 AI\n\n${m.content}`))
      .join('\n\n---\n\n')
    downloadFile(
      `# ${filenameRef.current} AI 对话分析\n\n> 生成时间: ${new Date().toLocaleString('zh-CN')}\n\n${md}`,
      baseName() + '.md',
      'text/markdown'
    )
    Toast.success('已导出对话')
  }

  function printResult() {
    if (!messages.length) return
    const body = messages
      .map((m) => {
        const html =
          m.role === 'user'
            ? `<p style="background:#e3f2fd;padding:8px 12px;border-radius:6px;margin:8px 0"><b>我:</b> ${escapeHtml(m.content)}</p>`
            : `<div style="background:#f9fcff;padding:8px 12px;border-radius:6px;margin:8px 0;border-left:3px solid #4fc3f7"><b>AI:</b><br>${renderMd(m.content)}</div>`
        return html
      })
      .join('')
    const w = window.open('', '_blank')
    if (!w) {
      Toast.warning('弹窗被拦截')
      return
    }
    w.document.write(
      `<!DOCTYPE html><html lang="zh-CN"><head><meta charset="UTF-8"><title>${baseName()}</title>
<style>body{font-family:-apple-system,'PingFang SC','Microsoft YaHei',sans-serif;color:#222;line-height:1.7;max-width:800px;margin:20px auto;padding:0 16px}
h1,h2,h3{color:#1e3c72}code{background:#f4f4f4;padding:2px 6px;border-radius:3px;color:#c0392b}pre{background:#f4f4f4;padding:12px;border-radius:6px;overflow-x:auto}</style>
</head><body><h2>${filenameRef.current} AI 对话分析</h2>${body}</body></html>`
    )
    w.document.close()
    w.focus()
    setTimeout(() => w.print(), 300)
  }

  // 表格列定义
  const makeColumns = (kind: string) => [
    { title: '文件名', dataIndex: 'filename', key: 'filename' },
    {
      title: '大小',
      dataIndex: 'size',
      key: 'size',
      width: 90,
      render: (text: number) => human(text),
    },
    {
      title: '时间',
      dataIndex: 'ts',
      key: 'ts',
      width: 150,
      render: (text: string) => fmt(text),
    },
    {
      title: '操作',
      key: 'op',
      width: 200,
      render: (_: any, row: ArchivedLog) => (
        <>
          <Button size="small" theme="borderless" onClick={() => dl(kind, row)}>
            下载
          </Button>
          <Button
            size="small"
            theme="borderless"
            disabled={!aiEnabled}
            onClick={() => openAi(kind, row)}
          >
            AI分析
          </Button>
          {user.isEngineer && (
            <Popconfirm title="删除?" onConfirm={() => del(kind, row)}>
              <Button size="small" theme="borderless" type="danger">
                删
              </Button>
            </Popconfirm>
          )}
        </>
      ),
    },
  ]

  return (
    <div className="log-tab-pane">
      <style>{`
        .chat-box {
          height: 56vh; min-height: 320px; overflow-y: auto;
          background: #f5f7fa; border: 1px solid #e4e7ed; border-radius: 8px; padding: 16px;
        }
        .chat-empty { text-align: center; color: #909399; padding-top: 60px; }
        .chat-msg { display: flex; margin-bottom: 16px; gap: 10px; }
        .chat-msg.user { flex-direction: row-reverse; }
        .chat-avatar {
          width: 32px; height: 32px; border-radius: 50%; flex-shrink: 0;
          display: flex; align-items: center; justify-content: center;
          font-size: 12px; color: #fff; font-weight: 600;
        }
        .chat-msg.user .chat-avatar { background: #409eff; }
        .chat-msg.assistant .chat-avatar { background: #67c23a; }
        .chat-content { max-width: 78%; }
        .chat-text {
          background: #409eff; color: #fff; padding: 8px 12px; border-radius: 10px;
          display: inline-block; white-space: pre-wrap; word-break: break-word; text-align: left;
        }
        .chat-msg.user .chat-content { text-align: right; }
        .chat-md {
          background: #fff; padding: 10px 14px; border-radius: 10px; border: 1px solid #ebeef5;
          display: inline-block; text-align: left; max-width: 100%; user-select: text;
        }
        .chat-md h1, .chat-md h2 { color: #1e3c72; margin: 8px 0 4px; font-size: 15px; border-bottom: 1px solid #eee; padding-bottom: 4px; }
        .chat-md h3 { color: #2a5298; margin: 6px 0 3px; font-size: 14px; }
        .chat-md ul, .chat-md ol { padding-left: 20px; margin: 4px 0; }
        .chat-md li { margin: 2px 0; }
        .chat-md code { background: #f4f4f4; padding: 1px 5px; border-radius: 3px; color: #c0392b; font-size: 13px; }
        .chat-md pre { background: #2d2d2d; color: #f8f8f2; padding: 8px; border-radius: 4px; overflow-x: auto; }
        .chat-md pre code { background: none; color: #f8f8f2; }
        .chat-md table { border-collapse: collapse; }
        .chat-md th, .chat-md td { border: 1px solid #ddd; padding: 4px 8px; }
        .chat-md blockquote { border-left: 3px solid #4fc3f7; margin: 4px 0; padding: 2px 10px; color: #555; background: #f9fcff; }
        .chat-thinking { display: flex; gap: 4px; padding: 12px; }
        .chat-thinking span {
          width: 8px; height: 8px; background: #c0c4cc; border-radius: 50%;
          animation: chatBlink 1.4s infinite both;
        }
        .chat-thinking span:nth-child(2) { animation-delay: 0.2s; }
        .chat-thinking span:nth-child(3) { animation-delay: 0.4s; }
        @keyframes chatBlink { 0%,80%,100%{opacity:0.3} 40%{opacity:1} }
        .chat-input { display: flex; gap: 8px; align-items: stretch; }
      `}</style>

      <div className="flex-between mb-12">
        <Button size="small" icon={<IconRefresh />} onClick={() => load()}>
          刷新
        </Button>
      </div>
      {!aiEnabled && (
        <Banner
          type="info"
          fullMode={false}
          className="mb-12"
          description="AI 日志分析未启用 —— 工程师可在「系统设置」配置 API Key 后开启。"
        />
      )}

      <Row gutter={[12, 12]}>
        <Col xs={24} md={12}>
          <Card title="已上传日志" bordered={false} className="card-shadow">
            <Table
              columns={makeColumns('uploaded')}
              dataSource={archived.uploaded}
              pagination={false}
              rowKey="id"
              size="small"
              scroll={{ y: 520 }}
            />
          </Card>
        </Col>
        <Col xs={24} md={12}>
          <Card title="已拉取日志" bordered={false} className="card-shadow">
            <Table
              columns={makeColumns('fetched')}
              dataSource={archived.fetched}
              pagination={false}
              rowKey="id"
              size="small"
              scroll={{ y: 520 }}
            />
          </Card>
        </Col>
      </Row>

      {/* AI 对话弹窗 */}
      <Modal
        visible={aiVisible}
        title={`AI 对话分析 - ${aiFilename}`}
        width={920}
        onCancel={() => {
          abortRef.current = true
          setAiVisible(false)
        }}
        footer={null}
      >
        {/* 工具栏 */}
        <div className="flex-between mb-12">
          <div className="text-muted" style={{ fontSize: 13 }}>
            {streaming ? (
              <span>⏳ AI 正在回复...</span>
            ) : messages.length ? (
              <span>共 {messages.length} 条消息</span>
            ) : (
              <span>点击「开始分析」或直接输入问题</span>
            )}
          </div>
          <div className="flex gap-8">
            <Dropdown
              trigger="click"
              render={
                <Dropdown.Menu>
                  <Dropdown.Item onClick={exportMd}>导出全部对话 (Markdown)</Dropdown.Item>
                  <Dropdown.Item onClick={printResult}>打印 / 另存 PDF</Dropdown.Item>
                </Dropdown.Menu>
              }
            >
              <Button size="small" disabled={!messages.length}>
                <IconDownload /> 导出 <IconChevronDown />
              </Button>
            </Dropdown>
            <Button
              size="small"
              onClick={clearChat}
              disabled={streaming || !messages.length}
            >
              清空对话
            </Button>
          </div>
        </div>

        {/* 对话区 */}
        <div ref={chatBoxRef} className="chat-box">
          {messages.length === 0 && !streaming && (
            <div className="chat-empty">
              <div style={{ fontSize: 40, color: '#909399' }}>✨</div>
              <div className="mt-8">点击「开始分析」让 AI 先做一次完整诊断</div>
              <div className="text-muted mt-8" style={{ fontSize: 12 }}>
                之后你可以追问, 例如:
                <br />
                "详细分析第 3 个异常的原因"
                <br />
                "这个告警对巡检任务有什么影响?"
                <br />
                "给我一段排查脚本"
              </div>
              <Button
                theme="solid"
                type="primary"
                className="mt-12"
                onClick={() => send('')}
              >
                开始分析
              </Button>
            </div>
          )}

          {messages.map((m, i) => (
            <div key={i} className={`chat-msg ${m.role}`}>
              <div className="chat-avatar">{m.role === 'user' ? '我' : 'AI'}</div>
              <div className="chat-content">
                {m.role === 'user' ? (
                  <div className="chat-text">{m.content}</div>
                ) : (
                  <div
                    className="chat-md"
                    dangerouslySetInnerHTML={{ __html: renderMd(m.content) }}
                  />
                )}
              </div>
            </div>
          ))}

          {/* 流式占位 */}
          {streaming && (
            <div className="chat-msg assistant">
              <div className="chat-avatar">AI</div>
              <div className="chat-content">
                {pending ? (
                  <div
                    className="chat-md"
                    dangerouslySetInnerHTML={{ __html: renderMd(pending) }}
                  />
                ) : (
                  <div className="chat-thinking">
                    <span />
                    <span />
                    <span />
                  </div>
                )}
              </div>
            </div>
          )}
        </div>

        {/* 输入区 */}
        <div className="chat-input mt-12">
          <TextArea
            value={input}
            onChange={(v) => setInput(v)}
            rows={2}
            placeholder="追问 AI(如: 详细分析第2个异常 / 这个故障怎么处理?)"
            disabled={streaming}
            onKeyDown={(e) => {
              if (e.key === 'Enter' && !e.shiftKey) {
                e.preventDefault()
                if (input.trim()) send(input)
              }
            }}
          />
          <Button
            theme="solid"
            type="primary"
            loading={streaming}
            disabled={streaming}
            onClick={() => send(input)}
            style={{ height: '100%' }}
          >
            {streaming ? '回复中' : '发送'}
          </Button>
        </div>
      </Modal>
    </div>
  )
}
