import React, { useState, useRef, useEffect } from 'react'
import { Select, TextArea, Button, Tag } from '@douyinfe/semi-ui'
import { listRobots } from '../api/robots'
import { getAiSettings, getPrompts, aiChat } from '../api/ai'
import { renderMd } from '../utils/md'
import type { Robot, ChatMessage, PromptItem } from '../types'

interface Attachment {
  name: string
  content: string
}

export default function AiChat() {
  const [robots, setRobots] = useState<Robot[]>([])
  const [chatBotId, setChatBotId] = useState<number | undefined>(undefined)
  const [msgs, setMsgs] = useState<ChatMessage[]>([])
  const [input, setInput] = useState('')
  const [attachments, setAttachments] = useState<Attachment[]>([])
  const [streaming, setStreaming] = useState(false)
  const [pending, setPending] = useState('')
  const [prompts, setPrompts] = useState<PromptItem[]>([])

  const msgBoxRef = useRef<HTMLDivElement>(null)
  const fileInputRef = useRef<HTMLInputElement>(null)
  const abortRef = useRef(false)
  const streamingRef = useRef(false)

  const chatBot = robots.find((r) => r.id === chatBotId)

  const scrollBottom = () => {
    if (msgBoxRef.current) {
      msgBoxRef.current.scrollTop = msgBoxRef.current.scrollHeight
    }
  }

  useEffect(() => {
    scrollBottom()
  }, [msgs, pending])

  useEffect(() => {
    const load = async () => {
      try {
        const { data } = await listRobots()
        setRobots(data)
      } catch {
        /* ignore */
      }
      try {
        await getAiSettings()
      } catch {
        /* ignore */
      }
      try {
        const { data } = await getPrompts()
        setPrompts(data.prompts || [])
      } catch {
        /* ignore */
      }
    }
    load()
  }, [])

  const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0]
    if (!file) return
    const reader = new FileReader()
    reader.onload = (ev) => {
      setAttachments((prev) => [
        ...prev,
        { name: file.name, content: ev.target?.result as string },
      ])
    }
    reader.readAsText(file)
    e.target.value = ''
  }

  const removeAttachment = (index: number) => {
    setAttachments((prev) => prev.filter((_, i) => i !== index))
  }

  async function send(text?: string) {
    const q = (text || input).trim()
    if (!q && attachments.length === 0) return
    if (streamingRef.current) return

    const userMsg: ChatMessage = {
      role: 'user',
      content: q || '请分析以下附件内容',
      attachments: attachments.length ? attachments.map((a) => a.name) : undefined,
    }
    const newMsgs = [...msgs, userMsg]
    setMsgs(newMsgs)
    setInput('')

    const atts = attachments.map((a) => ({ name: a.name, content: a.content }))
    setAttachments([])

    streamingRef.current = true
    setStreaming(true)
    abortRef.current = false
    setPending('')
    scrollBottom()
    let received = ''

    try {
      const history = newMsgs
        .slice(0, -1)
        .map((m) => ({ role: m.role, content: m.content }))
      for await (const piece of aiChat(history, q || '请分析以下附件内容', chatBot?.name || '', atts)) {
        if (abortRef.current) break
        received += piece
        setPending(received)
        scrollBottom()
      }
      if (received) {
        setMsgs((prev) => [...prev, { role: 'assistant', content: received }])
      } else {
        setMsgs((prev) => [...prev, { role: 'assistant', content: '⚠️ 未收到回复' }])
      }
    } catch (e: any) {
      setMsgs((prev) => [...prev, { role: 'assistant', content: '❌ ' + e.message }])
    } finally {
      setPending('')
      streamingRef.current = false
      setStreaming(false)
      scrollBottom()
    }
  }

  const handleKeyDown = (e: React.KeyboardEvent) => {
    if (e.key === 'Enter' && e.shiftKey) {
      e.preventDefault()
      setInput((prev) => prev + '\n')
    } else if (e.key === 'Enter' && !e.shiftKey) {
      e.preventDefault()
      if (input.trim()) send()
    }
  }

  return (
    <div className="ai-chat">
      <style>{`
        .ai-chat { display: flex; flex-direction: column; height: calc(100vh - 160px); min-height: 500px; }
        .chat-header { padding: 8px 16px; background: #f5f7fa; border-radius: 8px 8px 0 0; border: 1px solid #e4e7ed; }
        .chat-messages {
          flex: 1; overflow-y: auto; padding: 16px;
          background: linear-gradient(135deg, #1a1a2e 0%, #16213e 50%, #0f3460 100%);
          scroll-behavior: smooth;
        }
        .chat-welcome { text-align: center; color: #b0bec5; padding: 60px 20px 30px; }
        .chat-welcome h3 { color: #eceff1; }
        .prompts-row { display: flex; flex-wrap: wrap; gap: 6px; justify-content: center; margin-top: 12px; max-width: 600px; margin-left: auto; margin-right: auto; }
        .prompt-chip {
          display: inline-block; padding: 5px 12px; background: rgba(255,255,255,.08); color: #b0bec5;
          border: 1px solid rgba(255,255,255,.12); border-radius: 16px; cursor: pointer; font-size: 12px;
          transition: all .2s; user-select: none;
        }
        .prompt-chip:hover { background: rgba(79,195,247,.2); color: #4fc3f7; border-color: rgba(79,195,247,.4); }
        .msg-row { display: flex; gap: 10px; margin-bottom: 16px; animation: fadeIn .3s; }
        .msg-row.user { flex-direction: row-reverse; }
        .msg-avatar { width: 34px; height: 34px; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: 18px; flex-shrink: 0; }
        .msg-row.user .msg-avatar { background: #1976d2; }
        .msg-row.assistant .msg-avatar { background: #2e7d32; }
        .msg-body { max-width: 78%; }
        .msg-row.user .msg-body { text-align: right; }
        .msg-bubble {
          display: inline-block; padding: 10px 14px; border-radius: 14px; text-align: left;
          word-break: break-word; user-select: text; max-width: 100%;
        }
        .msg-row.user .msg-bubble { background: #1976d2; color: #fff; }
        .msg-row.assistant .msg-bubble { background: #2d2d3f; color: #e0e0e0; border: 1px solid #3d3d5c; }
        .msg-text { white-space: pre-wrap; }
        .msg-md h1, .msg-md h2 { color: #4fc3f7; font-size: 15px; margin: 8px 0 4px; }
        .msg-md h3 { color: #81c784; font-size: 14px; margin: 6px 0 3px; }
        .msg-md code { background: rgba(255,255,255,.1); padding: 1px 5px; border-radius: 3px; color: #ffb74d; }
        .msg-md pre { background: #111; padding: 8px; border-radius: 4px; overflow-x: auto; }
        .msg-md pre code { background: none; color: #e0e0e0; }
        .msg-md blockquote { border-left: 3px solid #4fc3f7; margin: 4px 0; padding: 2px 10px; color: #90a4ae; }
        .msg-attach { margin-bottom: 6px; }
        .chat-footer { padding: 8px 12px; background: #f5f7fa; border-radius: 0 0 8px 8px; border: 1px solid #e4e7ed; }
        .attach-row { display: flex; flex-wrap: wrap; gap: 4px; margin-bottom: 6px; }
        .input-row { display: flex; gap: 8px; align-items: flex-end; }
        .typing-dots { display: flex; gap: 4px; padding: 10px 6px; }
        .typing-dots span { width: 7px; height: 7px; background: #4fc3f7; border-radius: 50%; animation: blink 1.4s infinite both; }
        .typing-dots span:nth-child(2) { animation-delay: .2s; }
        .typing-dots span:nth-child(3) { animation-delay: .4s; }
        @keyframes blink { 0%,80%,100%{opacity:.3} 40%{opacity:1} }
        @keyframes fadeIn { from{opacity:0;transform:translateY(8px)} to{opacity:1;transform:translateY(0)} }
      `}</style>

      {/* 顶部：机器人选择 + 提示 */}
      {robots.length > 0 && (
        <div className="chat-header flex-between">
          <div className="flex gap-8" style={{ alignItems: 'center' }}>
            <span style={{ fontSize: 18 }}>🤖</span>
            <Select
              value={chatBotId}
              onChange={(v) => setChatBotId(v as number | undefined)}
              placeholder="选择机器人(可选, 帮AI理解上下文)"
              size="small"
              style={{ width: 260 }}
            >
              {robots.map((r) => (
                <Select.Option key={r.id} value={r.id}>
                  {r.name} ({r.ip})
                </Select.Option>
              ))}
            </Select>
          </div>
          <div className="text-muted" style={{ fontSize: 12 }}>
            向 AI 提问关于机器人运维的任何问题
          </div>
        </div>
      )}

      {/* 对话区 */}
      <div ref={msgBoxRef} className="chat-messages">
        {msgs.length === 0 && !streaming ? (
          <div className="chat-welcome">
            <div style={{ fontSize: 48 }}>✨</div>
            <h3 style={{ margin: '12px 0 6px' }}>AI 运维助手</h3>
            <p>我能帮你分析机器人日志、诊断故障、回答运维问题。</p>
            <p style={{ color: '#78909c', fontSize: 13, marginTop: 8 }}>
              试试这些快捷提问，或直接输入你的问题：
            </p>
            <div className="prompts-row">
              {prompts.map((p, i) => (
                <span key={i} className="prompt-chip" onClick={() => send(p.prompt)}>
                  {p.title}
                </span>
              ))}
            </div>
            <div className="flex gap-8 mt-12" style={{ alignItems: 'center', justifyContent: 'center' }}>
              <input
                type="file"
                ref={fileInputRef}
                accept=".log,.txt,.md,.csv"
                style={{ display: 'none' }}
                onChange={handleFileChange}
              />
              <Button size="small" onClick={() => fileInputRef.current?.click()}>
                添加附件(日志/文本)
              </Button>
            </div>
          </div>
        ) : null}

        {/* 历史消息 */}
        {msgs.map((m, i) => (
          <div key={i} className={`msg-row ${m.role}`}>
            <div className="msg-avatar">{m.role === 'user' ? '👤' : '🤖'}</div>
            <div className="msg-body">
              <div className="msg-bubble">
                {m.attachments && m.attachments.length > 0 && (
                  <div className="msg-attach">
                    {m.attachments.map((a, j) => (
                      <Tag key={j} size="small" color="blue" style={{ margin: 2 }}>
                        📎 {a}
                      </Tag>
                    ))}
                  </div>
                )}
                {m.role === 'user' ? (
                  <div className="msg-text">{m.content}</div>
                ) : (
                  <div
                    className="msg-md"
                    dangerouslySetInnerHTML={{ __html: renderMd(m.content) }}
                  />
                )}
              </div>
            </div>
          </div>
        ))}

        {/* 流式输出 */}
        {streaming && (
          <div className="msg-row assistant">
            <div className="msg-avatar">🤖</div>
            <div className="msg-body">
              <div className="msg-bubble">
                {pending ? (
                  <div
                    className="msg-md"
                    dangerouslySetInnerHTML={{ __html: renderMd(pending) }}
                  />
                ) : (
                  <div className="typing-dots">
                    <span />
                    <span />
                    <span />
                  </div>
                )}
              </div>
            </div>
          </div>
        )}
      </div>

      {/* 输入区 */}
      <div className="chat-footer">
        {attachments.length > 0 && (
          <div className="attach-row">
            {attachments.map((a, i) => (
              <Tag
                key={i}
                size="small"
                closable
                onClose={() => removeAttachment(i)}
              >
                📎 {a.name}
              </Tag>
            ))}
          </div>
        )}
        <div className="input-row">
          <Button
            size="small"
            disabled={streaming}
            onClick={() => fileInputRef.current?.click()}
          >
            📎
          </Button>
          <TextArea
            value={input}
            onChange={(v) => setInput(v)}
            placeholder="输入问题... (Enter 发送, Shift+Enter 换行)"
            rows={2}
            disabled={streaming}
            onKeyDown={handleKeyDown}
            style={{ flex: 1 }}
          />
          <Button
            theme="solid"
            type="primary"
            disabled={!input.trim() || streaming}
            loading={streaming}
            onClick={() => send()}
          >
            发送
          </Button>
        </div>
      </div>
    </div>
  )
}
