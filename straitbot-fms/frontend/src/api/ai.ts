import http from './http'
import type { AiProvider, AiSettings, PromptItem } from '../types'

export const getProviders = () => http.get<AiProvider[]>('/api/ai/providers')
export const getAiSettings = () => http.get<AiSettings>('/api/ai/settings')
export const saveAiSettings = (data: Partial<AiSettings>) => http.put('/api/ai/settings', data)
export const getLogContent = (kind: string, logId: number) => http.get(`/api/ai/log_content/${kind}/${logId}`)
export const getPrompts = () => http.get<{ prompts: PromptItem[] }>('/api/ai/prompts')
export const savePrompts = (prompts: PromptItem[]) => http.put('/api/ai/prompts', { prompts })

/**
 * 流式分析/对话日志。返回 async generator, yield 文本片段。
 * history: 之前的对话; question: 本次提问
 */
export async function* analyzeLog(kind: string, logId: number, history: { role: string; content: string }[] = [], question = ''): AsyncGenerator<string> {
  const tok = localStorage.getItem('fms_token')
  const resp = await fetch(`/api/ai/analyze/${kind}/${logId}`, {
    method: 'POST',
    headers: {
      Authorization: 'Bearer ' + tok,
      'Content-Type': 'application/json',
      Accept: 'text/event-stream',
    },
    body: JSON.stringify({ history, question }),
  })
  if (!resp.ok) {
    const txt = await resp.text().catch(() => '')
    throw new Error('分析失败 ' + resp.status + ' ' + txt)
  }
  const reader = resp.body!.getReader()
  const dec = new TextDecoder('utf-8')
  let buf = ''
  while (true) {
    const { value, done } = await reader.read()
    if (done) break
    buf += dec.decode(value, { stream: true })
    const lines = buf.split('\n')
    buf = lines.pop() || ''
    for (const line of lines) {
      const t = line.trim()
      if (!t.startsWith('data:')) continue
      const payload = t.slice(5).trim()
      if (payload === '[DONE]') return
      try {
        const obj = JSON.parse(payload)
        if (obj.text) yield obj.text
        if (obj.error) throw new Error(obj.error)
      } catch { /* skip malformed */ }
    }
  }
}

/**
 * AI 对话(支持附件)。返回 async generator, yield 文本片段。
 */
export async function* aiChat(
  history: { role: string; content: string }[],
  question: string,
  robotName = '',
  attachments: { name: string; content: string }[] = []
): AsyncGenerator<string> {
  const tok = localStorage.getItem('fms_token')
  const resp = await fetch('/api/ai/chat', {
    method: 'POST',
    headers: {
      Authorization: 'Bearer ' + tok,
      'Content-Type': 'application/json',
      Accept: 'text/event-stream',
    },
    body: JSON.stringify({ history, question, robot_name: robotName, attachments }),
  })
  if (!resp.ok) {
    const txt = await resp.text().catch(() => '')
    throw new Error('对话失败 ' + resp.status + ' ' + txt)
  }
  const reader = resp.body!.getReader()
  const dec = new TextDecoder('utf-8')
  let buf = ''
  while (true) {
    const { value, done } = await reader.read()
    if (done) break
    buf += dec.decode(value, { stream: true })
    const lines = buf.split('\n')
    buf = lines.pop() || ''
    for (const line of lines) {
      const t = line.trim()
      if (!t.startsWith('data:')) continue
      const payload = t.slice(5).trim()
      if (payload === '[DONE]') return
      try {
        const obj = JSON.parse(payload)
        if (obj.text) yield obj.text
        if (obj.error) throw new Error(obj.error)
      } catch { /* skip */ }
    }
  }
}
