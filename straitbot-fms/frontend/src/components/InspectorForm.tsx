import React, { useMemo, useState } from 'react'
import {
  Button, ColorPicker, Image, Input, InputNumber, Select, Slider, Space, Switch,
  Tag, TextArea,
} from '@douyinfe/semi-ui'
import { IconCamera, IconDelete } from '@douyinfe/semi-icons'
import { DEFAULT_HEX, normalizeHex, toColorValue, valueToHex } from './colorValue'

/**
 * InspectorForm：由 JSON Schema（含 ui 元数据）驱动的通用属性表单。
 *
 * 后端新增节点类后，schema 自动多一条，本组件零改动即可渲染出新表单。
 * ui.widget 分发：text / textarea / number / select / checkbox / slider /
 *                color / readonly / kv / json / children / info / image
 */

interface UiMeta {
  widget?: string
  group?: string
  /**
   * 静态选项。两种写法都收：
   * - 裸值（`"GET"` / `0`）：label 直接取该值的字符串形式；
   * - `{ label, value }`：值与显示名不同时用（如 方向 0→"正向"）。
   */
  options?: (string | number | boolean | { label: string; value: any })[]
  /**
   * 选项不在 schema 里写死，而是**按名字去拿数据**（如 `algorithms`）。
   * 具体数据由调用方通过 `optionSources` 注入——本组件是通用的，
   * 不该知道"算法目录从哪个接口来"。
   */
  optionsFrom?: string
  min?: number
  max?: number
  step?: number
  placeholder?: string
  rows?: number
  text?: string
  [k: string]: any
}

interface FieldDef {
  type?: string
  title?: string
  description?: string
  default?: any
  enum?: any[]
  ui?: UiMeta
}

interface Props {
  schema: Record<string, any>
  value: Record<string, any>
  onChange: (patch: Record<string, any>) => void
  /**
   * `image` 控件的「重新拍照」：返回**新的图片路径**，null = 取消或失败。
   *
   * 由上层注入而不是在这里调接口：检视器是通用的（规则 prefab 也用它），
   * 而"拍照"这件事只有航点树页面有（要拿云台快照 + 当前 prefab 的 rel_path）。
   * 没传时按钮置灰，控件退化成"只读缩略图 + 手填路径"。
   */
  onCaptureImage?: () => Promise<string | null>
  /**
   * 把控件里的值（多数是相对 prefab 的相对路径）解析成 `<img src>`。
   * 不传就按原样当 URL——老数据里手填的绝对地址走这条路。
   */
  resolveImageSrc?: (v: string) => string
  /**
   * 渲染在**表单最前面**的自定义块（"检视器的第一项"）。
   *
   * 给那些"不是字段、但又必须跟属性在一起看"的工具用——比如拍照动作点的
   * 检测框绑定画布。放在这里而不是由调用方塞在组件外面，是为了让它真的
   * 落在检视器内部、跟着"未知类型/多选"的分支一起显隐。
   */
  top?: React.ReactNode
  /**
   * `ui.optionsFrom` 的数据源（`{ 名字: [{ value, label }] }`）。
   *
   * 与 `onCaptureImage` 同理：检视器是通用的，而算法目录这种东西只有
   * 航点树页面会去拉。没传（或找不到对应名字）时，select 退回到
   * schema 里写死的 options —— **不会渲染成空下拉框**。
   */
  optionSources?: Record<string, { value: any; label: string }[]>
  /**
   * 在**指定分组的字段下方**追加自定义块（键为分组名，如 "云台"）。
   *
   * 给那些归属某个分组、但又不是字段的工具用——比如「云台」分组下的
   * 「使用当前云台位姿」。与 `top`（渲染在表单最前面）互补。
   */
  groupExtra?: Record<string, React.ReactNode>
}

/**
 * 图片字段：缩略图 + 拍照/重新拍照 + 手填路径。
 *
 * 单独抽成组件是因为**它要用到 hook**（拍照中的 loading 态），而
 * `renderField` 是在 `.map` 里被调的普通函数——在里面写 hook 会让每次渲染
 * 的 hook 数量随字段数变化，直接违反 hook 规则。
 */
function ImageField({
  value, onChange, onCapture, resolveSrc, placeholder, disabledHint,
}: {
  value: string
  onChange: (v: string) => void
  onCapture?: () => Promise<string | null>
  resolveSrc?: (v: string) => string
  placeholder?: string
  disabledHint?: string
}) {
  const [busy, setBusy] = useState(false)
  const src = resolveSrc ? resolveSrc(value) : value

  const capture = async () => {
    if (!onCapture) return
    setBusy(true)
    try {
      const next = await onCapture()
      // 返回 null 表示用户取消/拍照失败，此时**保持原值**——
      // 清掉用户已经拍好的图比"没拍上"更糟
      if (next) onChange(next)
    } finally {
      setBusy(false)
    }
  }

  return (
    <div>
      <div style={{ display: 'flex', gap: 10, alignItems: 'flex-start' }}>
        <div style={{
          width: 96, height: 64, flex: '0 0 auto', borderRadius: 4, overflow: 'hidden',
          border: '1px solid var(--semi-color-border)',
          background: 'var(--semi-color-fill-0)',
          display: 'flex', alignItems: 'center', justifyContent: 'center',
        }}>
          {src
            /* Semi 的 Image 自带点击放大预览，不用自己搭 Modal */
            ? <Image src={src} width={96} height={64} style={{ objectFit: 'cover' }} />
            : <span style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>未拍照</span>}
        </div>
        <div style={{ flex: 1, minWidth: 0 }}>
          <Space wrap>
            <Button
              size="small" theme="light" type="primary"
              icon={<IconCamera />} loading={busy}
              disabled={!onCapture}
              onClick={capture}
            >
              {value ? '重新拍照' : '拍照'}
            </Button>
            {value
              ? <Button size="small" type="tertiary" icon={<IconDelete />}
                onClick={() => onChange('')}>清除</Button>
              : null}
          </Space>
          {!onCapture && disabledHint ? (
            <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)', marginTop: 2 }}>
              {disabledHint}
            </div>
          ) : null}
        </div>
      </div>
      <div style={{ marginTop: 6 }}>
        <Input
          value={value} placeholder={placeholder || '图片路径（相对当前文件）'}
          onChange={(v) => onChange(v)}
        />
      </div>
    </div>
  )
}

function guessWidget(def: FieldDef): string {
  if (def.type === 'boolean') return 'checkbox'
  if (def.type === 'integer' || def.type === 'number') return 'number'
  if (Array.isArray(def.enum)) return 'select'
  return 'text'
}

export default function InspectorForm({
  schema, value, onChange, onCaptureImage, resolveImageSrc, top, optionSources, groupExtra,
}: Props) {
  const groups = useMemo(() => {
    const props: Record<string, FieldDef> = schema?.properties || {}
    const order: string[] = []
    const map: Record<string, [string, FieldDef][]> = {}
    for (const [name, def] of Object.entries(props)) {
      const g = def.ui?.group || '通用'
      if (!map[g]) { map[g] = []; order.push(g) }
      map[g].push([name, def])
    }
    return order.map((g) => ({ group: g, fields: map[g] }))
  }, [schema])

  const patch = (name: string, v: any) => onChange({ ...value, [name]: v })

  const renderField = (name: string, def: FieldDef): React.ReactNode => {
    const ui = def.ui || {}
    const widget = ui.widget || guessWidget(def)
    const current = value[name] !== undefined ? value[name] : def.default
    const commonDesc = def.description && (
      <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)', marginTop: 2 }}>{def.description}</div>
    )

    switch (widget) {
      case 'readonly':
        return (
          <>
            <Tag size="small" color="blue">{String(current ?? '')}</Tag>
            {commonDesc}
          </>
        )
      case 'textarea':
        return (
          <>
            <TextArea
              value={String(current ?? '')} rows={ui.rows || 3}
              placeholder={ui.placeholder}
              onChange={(v) => patch(name, v)}
            />
            {commonDesc}
          </>
        )
      case 'number':
        return (
          <>
            <InputNumber
              value={current ?? null} min={ui.min} max={ui.max} step={ui.step}
              style={{ width: '100%' }}
              onChange={(v) => patch(name, v)}
            />
            {commonDesc}
          </>
        )
      case 'select': {
        // 动态选项优先：optionsFrom 指向的数据源拿不到时**退回静态 options**，
        // 别渲染成一个空下拉框（老数据在没拉到目录时也得能看能改）
        const from = ui.optionsFrom ? optionSources?.[ui.optionsFrom] : undefined
        const optionList = from && from.length
          ? from
          : (ui.options || def.enum || []).map((o) =>
            (o && typeof o === 'object' && 'value' in o)
              ? { label: String(o.label ?? o.value), value: o.value }
              : { label: String(o), value: o })
        return (
          <>
            <Select
              value={current}
              style={{ width: '100%' }}
              onChange={(v) => patch(name, v)}
              optionList={optionList}
            />
            {commonDesc}
          </>
        )
      }
      case 'checkbox':
        return (
          <div>
            <Switch checked={!!current} onChange={(v) => patch(name, v)} />
            {commonDesc}
          </div>
        )
      case 'slider':
        return (
          <>
            <Slider
              value={Number(current ?? ui.min ?? 0)}
              min={ui.min} max={ui.max ?? 100} step={ui.step ?? 1}
              onChange={(v) => patch(name, v)}
            />
            {commonDesc}
          </>
        )
      case 'color': {
        // Semi 的 ColorPicker 不是"字符串受控组件"：value 必须是
        // { hsva, rgba, hex } 对象，而节点里存的是 "#RRGGBB" 字符串。
        // 直接把字符串传进去，renderPicker 读 currentColor.hsva.h 时会抛
        // "Cannot read properties of undefined (reading 'h')" → 整个检视器白屏。
        // 所以这里做一次 字符串 ⇄ 对象 的转换（详见 components/colorValue.ts）。
        const fb = normalizeHex(def.default, DEFAULT_HEX)
        return (
          <>
            <ColorPicker
              value={toColorValue(current, fb)}
              alpha={false}
              onChange={(c: any) => patch(name, valueToHex(c, fb))}
            />
            {commonDesc}
          </>
        )
      }
      case 'kv':
        return (
          <>
            <TextArea
              className="text-mono"
              value={JSON.stringify(current ?? {}, null, 2)}
              rows={ui.rows || 4}
              onChange={(t) => {
                try {
                  const obj = JSON.parse(t)
                  if (obj && typeof obj === 'object' && !Array.isArray(obj)) patch(name, obj)
                } catch { /* 编辑中的非法 JSON 不提交 */ }
              }}
            />
            {commonDesc}
          </>
        )
      case 'json':
        // 与 kv 的区别：**接受数组**（kv 只收对象）。检测框的顶点就是
        // `[{x,y}, …]`，硬塞进 kv 会因为 `!Array.isArray` 那道判断被静默丢弃
        // ——改了半天没反应，属于最难查的那类。
        return (
          <>
            <TextArea
              className="text-mono"
              value={JSON.stringify(current ?? [], null, 2)}
              rows={ui.rows || 4}
              onChange={(t) => {
                try {
                  patch(name, JSON.parse(t))
                } catch { /* 编辑中的非法 JSON 不提交 */ }
              }}
            />
            {commonDesc}
          </>
        )
      case 'children':
        return (
          <>
            <Tag size="small" color="grey">
              {Array.isArray(current) ? current.length : 0} 个子节点
            </Tag>
            {commonDesc}
          </>
        )
      case 'info':
        return <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>{String(ui.text ?? def.description ?? '')}</div>
      case 'image':
        return (
          <>
            <ImageField
              value={String(current ?? '')}
              onChange={(v) => patch(name, v)}
              onCapture={onCaptureImage}
              resolveSrc={resolveImageSrc}
              placeholder={ui.placeholder}
              disabledHint="当前页面不支持拍照，可手填图片路径"
            />
            {commonDesc}
          </>
        )
      default:
        if (def.type === 'boolean') {
          return (
            <div>
              <Switch checked={!!current} onChange={(v) => patch(name, v)} />
              {commonDesc}
            </div>
          )
        }
        if (def.type === 'integer' || def.type === 'number') {
          return (
            <>
              <InputNumber value={current ?? null} style={{ width: '100%' }}
                onChange={(v) => patch(name, v)} />
              {commonDesc}
            </>
          )
        }
        return (
          <>
            <Input value={String(current ?? '')} placeholder={ui.placeholder}
              onChange={(v) => patch(name, v)} />
            {commonDesc}
          </>
        )
    }
  }

  return (
    <div>
      {top}
      {groups.map(({ group, fields }) => (
        <div key={group} style={{ marginBottom: 16 }}>
          <div style={{
            fontSize: 13, fontWeight: 600, color: 'var(--semi-color-text-0)',
            borderLeft: '3px solid var(--semi-color-primary)',
            paddingLeft: 8, marginBottom: 8,
          }}>
            {group}
          </div>
          {fields.map(([name, def]) => (
            <div key={name} style={{ marginBottom: 12 }}>
              <div style={{
                fontSize: 13, color: 'var(--semi-color-text-1)',
                marginBottom: 4, fontWeight: 500,
              }}>
                {def.title || name}
              </div>
              {renderField(name, def)}
            </div>
          ))}
          {groupExtra?.[group]}
        </div>
      ))}
      {groups.length === 0 && <div style={{ color: 'var(--semi-color-text-2)' }}>该节点没有可编辑属性</div>}
    </div>
  )
}
