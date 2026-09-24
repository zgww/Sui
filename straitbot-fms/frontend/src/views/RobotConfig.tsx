import { useState, useEffect, useCallback } from 'react'
import { Card, Button, InputNumber, Switch, Select, Input, TextArea, Timeline, Toast, Row, Col, Tag } from '@douyinfe/semi-ui'
import { IconRefresh, IconSave } from '@douyinfe/semi-icons'
import { useRobotId } from '../store/robot'
import { readRobotConfig, writeRobotConfig, configHistory } from '../api/robots'
import type { ConfigHistoryItem } from '../types'
import { configCategories, configFields, getField } from '../config/configSchema'
import type { ConfigField } from '../config/configSchema'

// ===== 工具函数 =====

/** 把 CMD=4 返回的嵌套对象拍平成 key->value 映射 */
function flatten(obj: any, prefix = ''): Record<string, any> {
  const result: Record<string, any> = {}
  for (const [k, v] of Object.entries(obj || {})) {
    const path = prefix ? `${prefix}.${k}` : k
    if (v && typeof v === 'object' && !Array.isArray(v)) {
      Object.assign(result, flatten(v, path))
    } else {
      result[path] = v
    }
  }
  return result
}

/** 格式化值显示 */
function fmtVal(v: any, f: ConfigField): string {
  if (v == null) return '—'
  if (f.type === 'bool') return v ? '✓' : '✗'
  if (f.type === 'select') return f.options?.find(o => o.value === v)?.label ?? String(v)
  return String(v) + (f.unit ? ` ${f.unit}` : '')
}

// ===== 表单控件 =====

function FieldInput({ field, value, onChange }: {
  field: ConfigField; value: any; onChange: (v: any) => void
}) {
  if (field.type === 'bool') {
    return <Switch checked={!!value} onChange={onChange} size="small" />
  }
  if (field.type === 'select') {
    return (
      <Select
        value={value}
        onChange={onChange}
        optionList={field.options?.map(o => ({ value: o.value, label: o.label })) || []}
        size="small"
        style={{ width: 160 }}
      />
    )
  }
  if (field.type === 'string') {
    return <Input value={value ?? ''} onChange={onChange} size="small" style={{ width: 220 }} />
  }
  if (field.type === 'json') {
    const text = typeof value === 'object' ? JSON.stringify(value, null, 2) : (value ?? '')
    return (
      <div>
        <TextArea
          value={text}
          onChange={v => {
            try { onChange(JSON.parse(v)) } catch { onChange(v) }
          }}
          rows={4}
          style={{ fontFamily: 'Consolas, Monaco, monospace', fontSize: 12, width: 360 }}
        />
        {typeof value === 'string' && <div style={{ fontSize: 11, color: '#f56c6c', marginTop: 2 }}>JSON 格式错误, 请修正</div>}
      </div>
    )
  }
  // int / float
  return (
    <InputNumber
      value={value ?? 0}
      onChange={v => onChange(v != null ? Number(v) : 0)}
      min={field.min}
      max={field.max}
      step={field.step}
      size="small"
      style={{ width: 140 }}
      suffix={field.unit}
    />
  )
}

// ===== 主组件 =====

export default function RobotConfig() {
  const { selectedRid: rid } = useRobotId()
  const [rawConfig, setRawConfig] = useState<Record<string, any>>({})
  const [flatConfig, setFlatConfig] = useState<Record<string, any>>({})
  const [editValues, setEditValues] = useState<Record<string, any>>({})
  const [activeCat, setActiveCat] = useState<string>(configCategories[0]?.key ?? '')
  const [history, setHistory] = useState<ConfigHistoryItem[]>([])
  const [saving, setSaving] = useState(false)
  const [loading, setLoading] = useState(false)

  // 扁平化配置
  useEffect(() => {
    setFlatConfig(flatten(rawConfig))
  }, [rawConfig])

  // 读取配置
  const load = useCallback(async () => {
    if (!rid) return
    setLoading(true)
    try {
      const { data } = await readRobotConfig(rid)
      if (data.ok) {
        setRawConfig(data.config || {})
        setEditValues({})
      }
      const { data: hv } = await configHistory(rid)
      setHistory(hv || [])
    } catch { /* */ }
    finally { setLoading(false) }
  }, [rid])

  useEffect(() => { if (rid) load() }, [rid, load])

  // 获取字段值 (编辑优先 > 原始)
  const getValue = (key: string) => {
    if (key in editValues) return editValues[key]
    return flatConfig[key]
  }

  // 修改字段
  const setValue = (key: string, val: any) => {
    setEditValues(prev => ({ ...prev, [key]: val }))
  }

  // 保存
  const save = async () => {
    if (!rid || Object.keys(editValues).length === 0) {
      Toast.warning('没有修改过任何字段')
      return
    }
    setSaving(true)
    try {
      // 把扁平的 editValues 恢复成嵌套结构提交
      const nested: Record<string, any> = {}
      for (const [k, v] of Object.entries(editValues)) {
        const parts = k.split('.')
        let cur = nested
        for (let i = 0; i < parts.length - 1; i++) {
          if (!cur[parts[i]]) cur[parts[i]] = {}
          cur = cur[parts[i]]
        }
        cur[parts[parts.length - 1]] = v
      }
      const { data } = await writeRobotConfig(rid, nested)
      if (data.ok) {
        Toast.success('配置已保存')
        setEditValues({})
        load()
      } else {
        Toast.error(data.msg || '保存失败')
      }
    } catch { /* */ }
    finally { setSaving(false) }
  }

  // 当前激活分类的字段列表
  const cat = configCategories.find(c => c.key === activeCat)
  const activeFields = cat
    ? cat.fields.map(k => getField(k)).filter(Boolean) as ConfigField[]
    : []

  // 统计已修改字段数
  const dirtyCount = Object.keys(editValues).length

  return (
    <div className="page-container" style={{ height: 'calc(100vh - 80px)', display: 'flex', flexDirection: 'column' }}>
      <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between', marginBottom: 12 }}>
        <h2 style={{ margin: 0 }}>机器人参数配置</h2>
        <div style={{ display: 'flex', gap: 8 }}>
          <Button icon={<IconRefresh />} loading={loading} onClick={load}>读取当前</Button>
          <Button
            icon={<IconSave />}
            theme="solid"
            type="primary"
            loading={saving}
            disabled={dirtyCount === 0}
            onClick={save}
          >
            保存配置{dirtyCount > 0 ? ` (${dirtyCount})` : ''}
          </Button>
        </div>
      </div>

      {!rid ? (
        <Card><span style={{ color: '#909399' }}>请在头部下拉框选择机器人</span></Card>
      ) : (
        <Row gutter={12} style={{ flex: 1, overflow: 'hidden' }}>
          {/* 左侧分类树 */}
          <Col span={5} style={{ overflow: 'auto' }}>
            <Card bodyStyle={{ padding: 8 }}>
              {configCategories.map(c => (
                <div
                  key={c.key}
                  onClick={() => setActiveCat(c.key)}
                  style={{
                    padding: '8px 12px', borderRadius: 4, cursor: 'pointer',
                    fontSize: 13, fontWeight: activeCat === c.key ? 600 : 400,
                    color: activeCat === c.key ? '#fff' : '#333',
                    background: activeCat === c.key ? '#409eff' : 'transparent',
                    marginBottom: 2,
                    transition: 'all .15s',
                  }}
                >
                  {c.label}
                </div>
              ))}
            </Card>
          </Col>

          {/* 右侧表单 + 历史 */}
          <Col span={19} style={{ overflow: 'auto', height: '100%' }}>
            <Card
              title={cat?.label || '配置'}
              bodyStyle={{ padding: '12px 20px' }}
            >
              {activeFields.length === 0 ? (
                <div style={{ color: '#909399', padding: 20, textAlign: 'center' }}>点击左侧分类查看配置项</div>
              ) : (
                <div style={{ display: 'grid', gridTemplateColumns: '160px 1fr', rowGap: 12, columnGap: 16, alignItems: 'center' }}>
                  {activeFields.map(f => {
                    const val = getValue(f.key)
                    const dirty = f.key in editValues
                    return (
                      <>
                        <div key={`l-${f.key}`} style={{ fontSize: 13, color: '#606266' }}>
                          {f.label}
                          {f.desc && <div style={{ fontSize: 11, color: '#aaa' }}>{f.desc}</div>}
                        </div>
                        <div key={`v-${f.key}`} style={{ display: 'flex', alignItems: 'center', gap: 8 }}>
                          {f.writable ? (
                            <FieldInput field={f} value={val} onChange={v => setValue(f.key, v)} />
                          ) : (
                            <span style={{ fontSize: 13 }}>{fmtVal(val, f)}</span>
                          )}
                          {dirty && <Tag size="small" color="blue">已修改</Tag>}
                        </div>
                      </>
                    )
                  })}
                </div>
              )}
            </Card>

            {/* 变更历史 */}
            {history.length > 0 && (
              <Card title="变更历史" style={{ marginTop: 12 }} bodyStyle={{ padding: '8px 16px', maxHeight: 200, overflow: 'auto' }}>
                <Timeline>
                  {history.map((h, i) => (
                    <Timeline.Item key={i} time={h.ts?.substring(0, 19)?.replace('T', ' ')} type="success">
                      {h.operator || '—'} 修改了配置
                    </Timeline.Item>
                  ))}
                </Timeline>
              </Card>
            )}
          </Col>
        </Row>
      )}
    </div>
  )
}
