import { useMemo, useState, useCallback } from 'react'
import { Tree, Tag, Typography, Button, Space, Switch, Tooltip } from '@douyinfe/semi-ui'
import { IconRefresh } from '@douyinfe/semi-icons'
import type { TreeNodeData } from '@douyinfe/semi-ui/lib/es/tree/interface'
import type { RobotControlState } from '../api/railRobot'

const { Text } = Typography

/** 标量叶子渲染：布尔/数字/字符串/null 分别着色，长文本可换行 */
function ValueLeaf({ value }: { value: unknown }) {
  if (value === null || value === undefined) return <Text type="tertiary">null</Text>
  if (typeof value === 'boolean') {
    return <Tag size="small" color={value ? 'green' : 'grey'}>{String(value)}</Tag>
  }
  if (typeof value === 'number') {
    return (
      <Text style={{ fontVariantNumeric: 'tabular-nums' }}>
        {Number.isInteger(value) ? String(value) : value.toFixed(3)}
      </Text>
    )
  }
  const s = String(value)
  if (s === '') return <Text type="tertiary">""</Text>
  return <Text style={{ wordBreak: 'break-all' }}>{s}</Text>
}

type CtxHandler = (key: string, e: React.MouseEvent) => void

/** 递归构造节点：对象/数组展开为子节点，标量作为叶子 */
function buildNode(key: string, label: string, value: unknown, onCtx?: CtxHandler): TreeNodeData {
  // 数组：逐项展开（元素为基础类型时直接作为叶子值显示）
  if (Array.isArray(value)) {
    if (value.length === 0) {
      return { key, label: <Field label={label} value={<Text type="tertiary">[]</Text>} onContextMenu={(e) => onCtx?.(key, e)} />, isLeaf: true }
    }
    return {
      key,
      label: <Field label={label} value={<Text type="tertiary">[{value.length}]</Text>} onContextMenu={(e) => onCtx?.(key, e)} />,
      children: value.map((v, i) => buildNode(`${key}[${i}]`, `[${i}]`, v, onCtx)),
    }
  }
  // 对象：展开为子节点
  if (value !== null && typeof value === 'object') {
    const entries = Object.entries(value as Record<string, unknown>)
    if (entries.length === 0) {
      return { key, label: <Field label={label} value={<Text type="tertiary">{'{}'}</Text>} onContextMenu={(e) => onCtx?.(key, e)} />, isLeaf: true }
    }
    return {
      key,
      label: <Field label={label} value={<Text type="tertiary">{`{${entries.length}}`}</Text>} onContextMenu={(e) => onCtx?.(key, e)} />,
      children: entries.map(([k, v]) => buildNode(`${key}.${k}`, k, v, onCtx)),
    }
  }
  // 标量
  return { key, label: <Field label={label} value={<ValueLeaf value={value} />} onContextMenu={(e) => onCtx?.(key, e)} />, isLeaf: true }
}

/** 在整棵树里找到 target 节点，返回它自身 + 所有后代的 key（用于整枝展开/收缩） */
function subtreeKeys(nodes: TreeNodeData[], target: string): string[] {
  const out: string[] = []
  const collect = (n: TreeNodeData) => {
    out.push(n.key as string)
    n.children?.forEach(collect)
  }
  const walk = (list: TreeNodeData[]): boolean => {
    for (const n of list) {
      if (n.key === target) {
        collect(n)
        return true
      }
      if (n.children && walk(n.children)) return true
    }
    return false
  }
  walk(nodes)
  return out
}

/** 一行：字段名 + 值 */
function Field({ label, value, onContextMenu }: { label: string; value: React.ReactNode; onContextMenu?: (e: React.MouseEvent) => void }) {
  return (
    <span style={{ display: 'inline-flex', alignItems: 'center', gap: 6 }} onContextMenu={onContextMenu}>
      <span style={{ color: 'var(--semi-color-text-1)' }}>{label}</span>
      {value}
    </span>
  )
}

type Props = {
  state: RobotControlState
  autoRefresh: boolean
  onAutoRefreshChange: (v: boolean) => void
  lastUpdated: number | null
  onRefresh: () => void
  refreshing?: boolean
}

/**
 * ``robot.state``（RobotState）结构树。
 *
 * 直接渲染后端 ``raw_state`` 的字段树——这就是状态对象本身，不做业务语义重组，
 * 因此字段增删会自动反映，可与代码里的 dataclass 逐项对照。
 * 节点上右键可「展开子树 / 收缩子树」。
 */
export default function RobotStateTree({
  state, autoRefresh, onAutoRefreshChange, lastUpdated, onRefresh, refreshing,
}: Props) {
  const raw = state.raw_state as unknown as Record<string, unknown> | undefined
  const sm = state.sm as unknown as Record<string, unknown> | undefined

  // 默认展开：状态机 + robot.state 的顶层字段（level 1），一眼可见；
  // 子结构（insp.* / battery.* 等）保持收起，避免整屏铺满。
  const defaultExpanded = useMemo(() => {
    const keys: string[] = ['sm']
    if (raw) keys.push(...Object.keys(raw))
    return keys
    // 只在首次挂载时算一次；后续刷新不重置用户的展开/收起
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [])

  // 受控展开：默认展开只在挂载时初始化一次，之后由用户操作驱动
  const [expandedKeys, setExpandedKeys] = useState<string[]>(defaultExpanded)

  // 右键菜单位置 + 目标节点 key；null = 菜单关闭
  const [ctx, setCtx] = useState<{ x: number; y: number; key: string } | null>(null)

  const tree = useMemo<TreeNodeData[]>(() => {
    const nodes: TreeNodeData[] = []
    // 状态机状态（main/charge/floor/insp）放在最前面，调试时最先看
    if (sm) {
      nodes.push(buildNode('sm', 'sm 状态机', sm, (key, e) => {
        e.preventDefault()
        setCtx({ x: e.clientX, y: e.clientY, key })
      }))
    }
    if (raw) {
      nodes.push(...Object.entries(raw).map(([k, v]) => buildNode(k, k, v, (key, e) => {
        e.preventDefault()
        setCtx({ x: e.clientX, y: e.clientY, key })
      })))
    }
    return nodes
  }, [raw, sm])

  const expandSubtree = useCallback(() => {
    if (!ctx) return
    const keys = subtreeKeys(tree, ctx.key)
    setExpandedKeys((prev) => Array.from(new Set([...prev, ...keys])))
    setCtx(null)
  }, [ctx, tree])

  const collapseSubtree = useCallback(() => {
    if (!ctx) return
    const keys = new Set(subtreeKeys(tree, ctx.key))
    setExpandedKeys((prev) => prev.filter((k) => !keys.has(k)))
    setCtx(null)
  }, [ctx, tree])

  return (
    <div>
      <div style={{
        display: 'flex', alignItems: 'center', gap: 10,
        marginBottom: 10, flexWrap: 'wrap',
      }}>
        <Space spacing={6}>
          <Text type="tertiary" size="small">自动刷新（1 秒）</Text>
          <Switch
            size="small" checked={autoRefresh} onChange={onAutoRefreshChange}
            aria-label="自动刷新"
          />
        </Space>
        <Button
          size="small" icon={<IconRefresh spin={refreshing} />}
          onClick={onRefresh} disabled={refreshing}
        >
          刷新
        </Button>
        <Tooltip content="robot.state（RobotState）原始字段树，字段与后端 dataclass 一一对应；节点右键可展开/收缩整枝">
          <Text type="tertiary" size="small">
            {lastUpdated
              ? `更新于 ${new Date(lastUpdated).toLocaleTimeString('zh-CN')}`
              : '—'}
          </Text>
        </Tooltip>
      </div>
      {raw ? (
        <Tree
          treeData={tree}
          expandedKeys={expandedKeys}
          onExpand={(keys) => setExpandedKeys(keys as string[])}
          /* 关掉展开动画：1 秒一次刷新时动画会让整棵树闪 */
          motion={false}
          style={{ maxHeight: 640, overflow: 'auto' }}
        />
      ) : (
        <Text type="tertiary">后端未返回 raw_state（请确认 /state 接口已更新）</Text>
      )}

      {/* 右键菜单：透明遮罩点别处关闭，菜单本体 stopPropagation */}
      {ctx && (
        <>
          <div
            style={{ position: 'fixed', inset: 0, zIndex: 1000 }}
            onClick={() => setCtx(null)}
            onContextMenu={(e) => { e.preventDefault(); setCtx(null) }}
          />
          <div
            style={{
              position: 'fixed', left: ctx.x, top: ctx.y, zIndex: 1001,
              background: 'var(--semi-color-bg-2)', border: '1px solid var(--semi-color-border)',
              borderRadius: 6, padding: 4, boxShadow: '0 2px 8px rgba(0,0,0,.15)',
              display: 'flex', flexDirection: 'column', gap: 2, minWidth: 120,
            }}
            onClick={(e) => e.stopPropagation()}
            onContextMenu={(e) => e.stopPropagation()}
          >
            <Button size="small" type="tertiary" onClick={expandSubtree}>展开子树</Button>
            <Button size="small" type="tertiary" onClick={collapseSubtree}>收缩子树</Button>
          </div>
        </>
      )}
    </div>
  )
}
