import React, { useState, useMemo, useEffect } from 'react'
import { Card, Button, Input, TextArea, Select, Switch, Tag, Banner, Tooltip, Toast } from '@douyinfe/semi-ui'
import { getProviders, getAiSettings, saveAiSettings } from '../api/ai'
import http from '../api/http'
import type { AiProvider, AiSettings as AiSettingsType } from '../types'

export default function AiSettings() {
  const [providers, setProviders] = useState<AiProvider[]>([])
  const [form, setForm] = useState<AiSettingsType>({
    provider: 'zhipu',
    base_url: '',
    api_key: '',
    api_key_set: false,
    model: '',
    protocol: 'anthropic',
    enabled: false,
    extra_instructions: '',
  })
  const [saving, setSaving] = useState(false)
  const [testing, setTesting] = useState(false)
  const [testResult, setTestResult] = useState({ green: false, red: false, msg: '' })

  const currentModels = useMemo(() => {
    const p = providers.find((x) => x.key === form.provider)
    return p?.models || []
  }, [providers, form.provider])

  const testButtonType = testResult.green ? 'primary' : testResult.red ? 'danger' : 'tertiary'
  const testMsg = testResult.msg || ''

  const updateForm = (key: keyof AiSettingsType, value: any) => {
    setForm((prev) => ({ ...prev, [key]: value }))
  }

  const load = async () => {
    try {
      const [p, s] = await Promise.all([getProviders(), getAiSettings()])
      setProviders(p.data)
      setForm({ ...s.data, api_key: '' })
    } catch {
      /* http 拦截器已处理错误提示 */
    }
  }

  const onProvider = (key: string) => {
    const p = providers.find((x) => x.key === key)
    if (p && key !== 'custom') {
      setForm((prev) => ({
        ...prev,
        provider: key,
        base_url: p.base_url,
        model: p.model,
        protocol: p.protocol,
      }))
    } else {
      setForm((prev) => ({ ...prev, provider: key }))
    }
  }

  const save = async () => {
    setSaving(true)
    try {
      const payload: any = { ...form }
      if (!payload.api_key) delete payload.api_key
      const { data } = await saveAiSettings(payload)
      setForm({ ...data.settings, api_key: '' })
      Toast.success('已保存')
    } catch {
      /* http 拦截器已处理错误提示 */
    } finally {
      setSaving(false)
    }
  }

  const testConn = async () => {
    setTesting(true)
    setTestResult({ green: false, red: false, msg: '测试中...' })
    try {
      const payload: any = { ...form }
      if (!payload.api_key) delete payload.api_key
      await saveAiSettings(payload)
      const { data } = await http.post('/api/ai/test')
      let msg = data.msg || (data.ok ? '连通成功' : '连通失败')
      if (data.reply) msg += ' - ' + data.reply
      setTestResult({ green: data.ok, red: !data.ok, msg })
    } catch (e: any) {
      setTestResult({
        green: false,
        red: true,
        msg: '测试异常: ' + (e.response?.data?.msg || e.message),
      })
    } finally {
      setTesting(false)
    }
  }

  useEffect(() => {
    load()
  }, [])

  const labelStyle: React.CSSProperties = {
    width: 120,
    flexShrink: 0,
    textAlign: 'right',
    paddingRight: 12,
    lineHeight: '32px',
  }
  const rowStyle: React.CSSProperties = {
    marginBottom: 16,
    display: 'flex',
    alignItems: 'flex-start',
  }

  return (
    <div className="page-container">
      <div className="mb-12">
        <h2 style={{ margin: 0 }}>AI 分析设置</h2>
      </div>

      <Card bordered={false} className="card-shadow mb-12" title="大模型服务商配置">
        <div style={{ maxWidth: 720 }}>
          {/* 启用 AI 分析 */}
          <div style={rowStyle}>
            <label style={labelStyle}>启用 AI 分析</label>
            <div style={{ display: 'flex', alignItems: 'center' }}>
              <Switch checked={form.enabled} onChange={(v) => updateForm('enabled', v)} />
              <span className="text-muted" style={{ marginLeft: 8 }}>
                开启后, 日志查看页将出现「AI分析」按钮
              </span>
            </div>
          </div>

          {/* 服务商 */}
          <div style={rowStyle}>
            <label style={labelStyle}>服务商</label>
            <Select
              value={form.provider}
              onChange={(v) => onProvider(v as string)}
              style={{ width: 280 }}
            >
              {providers.map((p) => (
                <Select.Option key={p.key} value={p.key}>
                  {p.label + (p.key === 'custom' ? '' : ' (' + p.model + ')')}
                </Select.Option>
              ))}
            </Select>
          </div>

          {/* API 地址 */}
          <div style={rowStyle}>
            <label style={labelStyle}>API 地址</label>
            <Input
              value={form.base_url}
              onChange={(v) => updateForm('base_url', v)}
              placeholder="https://open.bigmodel.cn/api/anthropic"
              className="text-mono"
            />
          </div>

          {/* 协议 */}
          <div style={rowStyle}>
            <label style={labelStyle}>协议</label>
            <div style={{ display: 'flex', alignItems: 'center' }}>
              <Tag size="small" color={form.protocol === 'anthropic' ? 'green' : 'blue'}>
                {form.protocol === 'anthropic'
                  ? 'Anthropic (GLM-5.2 / Claude / DeepSeek)'
                  : 'OpenAI (DeepSeek/通义/Kimi等)'}
              </Tag>
              <span className="text-muted" style={{ fontSize: 12, marginLeft: 6 }}>
                选服务商时自动匹配
              </span>
            </div>
          </div>

          {/* API Key */}
          <div style={rowStyle}>
            <label style={labelStyle}>API Key</label>
            <div style={{ flex: 1 }}>
              <Input
                mode="password"
                value={form.api_key}
                onChange={(v) => updateForm('api_key', v)}
                placeholder={form.api_key_set ? '已配置(留空表示不修改)' : '粘贴你的 API Key'}
              />
              <div className="text-muted" style={{ fontSize: 12 }}>
                Key 仅存在本平台数据库, 不会外传。当前: {form.api_key || '(未设置)'}
              </div>
            </div>
          </div>

          {/* 模型名 */}
          <div style={rowStyle}>
            <label style={labelStyle}>模型名</label>
            <div style={{ flex: 1 }}>
              <div style={{ display: 'flex', gap: 6 }}>
                <Input
                  value={form.model}
                  onChange={(v) => updateForm('model', v)}
                  placeholder="选择或输入模型 ID"
                  className="text-mono"
                />
                <Tooltip content={testMsg || '测试连通性'} position="top">
                  <Button
                    loading={testing}
                    type={testButtonType as any}
                    disabled={!form.api_key_set || !form.enabled}
                    onClick={testConn}
                  >
                    测试
                  </Button>
                </Tooltip>
              </div>
              <div className="text-muted" style={{ fontSize: 12, marginTop: 4 }}>
                下拉预设模型或直接输入自定义模型名。
                {currentModels.length > 0 && (
                  <span style={{ marginLeft: 8 }}>
                    预设:
                    {currentModels.map((m) => (
                      <a
                        key={m}
                        onClick={() => updateForm('model', m)}
                        style={{ margin: '0 4px', cursor: 'pointer', color: '#409eff' }}
                      >
                        {m}
                      </a>
                    ))}
                  </span>
                )}
                {testResult.green && (
                  <span style={{ color: '#67c23a', marginLeft: 8 }}>✓ {testResult.msg}</span>
                )}
                {testResult.red && (
                  <span style={{ color: '#f56c6c', marginLeft: 8 }}>✗ {testResult.msg}</span>
                )}
              </div>
            </div>
          </div>

          {/* 附加分析要求 */}
          <div style={rowStyle}>
            <label style={labelStyle}>附加分析要求</label>
            <div style={{ flex: 1 }}>
              <TextArea
                value={form.extra_instructions}
                onChange={(v) => updateForm('extra_instructions', v)}
                rows={3}
                placeholder="可选, 例如: 重点关注云台通信异常; 或: 请用更通俗的语言"
              />
            </div>
          </div>

          {/* 按钮 */}
          <div style={{ ...rowStyle, paddingLeft: 120 }}>
            <Button theme="solid" type="primary" loading={saving} onClick={save}>
              保存配置
            </Button>
            <Button onClick={load} style={{ marginLeft: 8 }}>
              重新读取
            </Button>
          </div>
        </div>
      </Card>

      <Banner
        type="info"
        fullMode={false}
        title="如何获取 API Key？"
        description={
          <ul style={{ margin: '6px 0 0', paddingLeft: 18, fontSize: 13 }}>
            <li>
              <b>智谱 GLM-5.2</b>(推荐): https://bigmodel.cn → API Keys, 模型填{' '}
              <code>glm-5.2</code>(超长日志用 <code>glm-5.2[1m]</code>)
            </li>
            <li>
              <b>DeepSeek</b>: https://platform.deepseek.com → API Keys, 模型{' '}
              <code>deepseek-v4-flash</code> 或 <code>deepseek-v4-pro</code>
              (OpenAI/Anthropic 双协议均支持)
            </li>
            <li>
              <b>通义千问</b>: https://dashscope.aliyun.com → API-KEY
            </li>
            <li>
              <b>OpenAI</b>: https://platform.openai.com → API Keys(需外网)
            </li>
            <li>
              <b>Ollama 本地</b>: 先 <code>ollama pull qwen2.5:7b</code> 再启动{' '}
              <code>ollama serve</code>, API Key 随便填
            </li>
          </ul>
        }
      />
    </div>
  )
}
