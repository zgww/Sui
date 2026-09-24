import { useState, useEffect, useCallback, useRef, useLayoutEffect } from 'react'
import type { ElementType, MouseEvent as ReactMouseEvent, DragEvent as ReactDragEvent } from 'react'
import {
  Button, Card, Input, InputNumber, Switch, Select, TextArea, Tag, Toast,
  Modal, Empty, Spin, Divider, Tabs, TabPane,
} from '@douyinfe/semi-ui'
import {
  IconBranch, IconChevronDown, IconChevronRight, IconMapPin, IconCamera,
  IconHash, IconSimilarity, IconPlus, IconCopy, IconDelete, IconSave,
  IconRefresh, IconExpand, IconShrink, IconImport, IconExport, IconRoute, IconCode,
  IconScissors, IconCopy as IconPasteIcon, IconFolderOpen,
} from '@douyinfe/semi-icons'
import Editor from '@monaco-editor/react'
import '../../monaco-setup'
import { useRobotId } from '../../store/robot'
import WebRTCPlayer, { WebRTCPlayerRef } from '../../components/WebRTCPlayer'
import {
  getTree, saveTree, importInspectionFile, createNode, updateNode,
  deleteNode, copyNode, moveNode, createGroup, exportFileUrl, refImageUrl,
} from '../../api/waypointTree'
import { calibXAxisStep, calibXAxisIter, calibPtzStep, calibPtzIter, calibRegister, calibMoveToWaypoint, debugImageUrl, listDebugSessions } from '../../api/calibration'
import CaptureRefImageDialog from '../../components/CaptureRefImageDialog'
import CalibrationDebugPanel from '../../components/CalibrationDebugPanel'
import { motionSetPose, ptzSetPose, liftControl } from '../../api/control'
import type { TreeNode } from '../../types'

// ========== 常量 ==========

interface NodeMeta {
  label: string
  icon: ElementType
  color: string   // Semi Tag 颜色名
  hex: string     // 图标颜色
}

const NODE_TYPE_META: Record<string, NodeMeta> = {
  WaypointNode: { label: '航点', icon: IconMapPin, color: 'blue', hex: '#409eff' },
  ActionNode: { label: '动作点', icon: IconCamera, color: 'orange', hex: '#e6a23c' },
  TaskPointNode: { label: '测点', icon: IconHash, color: 'green', hex: '#67c23a' },
  OrbRegistration: { label: 'ORB配准', icon: IconSimilarity, color: 'purple', hex: '#9254de' },
  Root: { label: '根节点', icon: IconBranch, color: 'grey', hex: '#909399' },
  GroupNode: { label: '分组', icon: IconFolderOpen, color: 'cyan', hex: '#06a3b7' },
}

/** 可注册的节点类型(用于"添加子节点"子菜单) */
const NODE_TYPES: { type: string; label: string; icon: ElementType; hex: string }[] = [
  { type: 'WaypointNode', label: '航点 WaypointNode', icon: IconMapPin, hex: '#409eff' },
  { type: 'ActionNode', label: '动作点 ActionNode', icon: IconCamera, hex: '#e6a23c' },
  { type: 'TaskPointNode', label: '测点 TaskPointNode', icon: IconHash, hex: '#67c23a' },
  { type: 'OrbRegistration', label: 'ORB配准 OrbRegistration', icon: IconSimilarity, hex: '#9254de' },
  { type: 'GroupNode', label: '分组 GroupNode', icon: IconFolderOpen, hex: '#06a3b7' },
]

const metaOf = (nt: string): NodeMeta =>
  NODE_TYPE_META[nt] ?? { label: nt, icon: IconHash, color: 'grey', hex: '#909399' }
const nodeTypeLabel = (nt: string): string => metaOf(nt).label

/** 调试图片中文标题 */
const IMAGE_TITLES: Record<string, string> = {
  '00_ref_mask.jpg': '参考图掩膜',
  '00_cur_mask.jpg': '当前图掩膜',
  '01_ref_keypoints.jpg': '参考图特征点',
  '01_cur_keypoints.jpg': '当前图特征点',
  '02_matches.jpg': '匹配结果',
  '03_reference_outline.jpg': '参考轮廓映射',
  '04_warped_reference.jpg': '参考图变换后',
  '05_blended.jpg': '叠加结果',
}

// ========== 工具函数 ==========

/** 内嵌控制面板: 状态 + 运动/云台/升降/位姿 */
function InlineControl({ rid }: { rid: number }) {
  const [live, setLive] = useState<any>(null)
  const [pose, setPose] = useState({ x: 0, y: 0, theta: 0 })
  const [ptz, setPtz] = useState({ pan: 0, tilt: 0, zoom: 0 })
  const [liftH, setLiftH] = useState(1)
  const stopRef = useRef<ReturnType<typeof setTimeout> | null>(null)
  const timerRef = useRef<ReturnType<typeof setInterval> | null>(null)

  const st = live?.data || {}
  const STATUS_MAP: Record<number, string> = { 0: '正常', 1: '开始充电', 2: '充电中', 3: '前往充电', 4: '自检中', 5: '巡检中', 6: '巡检暂停', 7: '巡检挂起', 8: '前往电梯' }

  const refreshLive = async () => {
    if (!rid) return
    try { const { liveStatus } = await import('../../api/robots'); const { data } = await liveStatus(rid); setLive(data) } catch { /* */ }
  }

  useEffect(() => {
    if (!rid) return
    refreshLive()
    timerRef.current = setInterval(refreshLive, 3000)
    return () => { if (timerRef.current) clearInterval(timerRef.current) }
  }, [rid])

  const holdMove = async (cmd: number) => {
    if (!rid) return
    if (stopRef.current) clearTimeout(stopRef.current)
    try { const { motionMove } = await import('../../api/control'); await motionMove(rid, cmd) } catch { /* */ }
  }
  const stopMove = async () => {
    if (!rid) return
    if (stopRef.current) clearTimeout(stopRef.current)
    stopRef.current = setTimeout(async () => {
      try { const { motionMove } = await import('../../api/control'); await motionMove(rid, 0) } catch { /* */ }
    }, 100)
  }
  const holdPtz = async (cmd: number) => {
    if (!rid) return
    if (stopRef.current) clearTimeout(stopRef.current)
    try { const { ptzAction } = await import('../../api/control'); await ptzAction(rid, { command: cmd, stop: false }) } catch { /* */ }
  }
  const stopPtz = (cmd: number) => {
    if (!rid) return
    if (stopRef.current) clearTimeout(stopRef.current)
    stopRef.current = setTimeout(async () => {
      try { const { ptzAction } = await import('../../api/control'); await ptzAction(rid, { command: cmd, stop: true }) } catch { /* */ }
    }, 100)
  }
  const liftCmd = async (cmd: number, h = 0) => {
    if (!rid) return
    try { const { liftControl } = await import('../../api/control'); await liftControl(rid, cmd, h) } catch { /* */ }
  }
  const setPtzPose = async () => {
    if (!rid) return
    try { const { ptzSetPose } = await import('../../api/control'); await ptzSetPose(rid, ptz) } catch { /* */ }
  }
  const setPoseFn = async () => {
    if (!rid) return
    try { const { motionSetPose } = await import('../../api/control'); await motionSetPose(rid, pose) } catch { /* */ }
  }

  const btn = (cmd: number) => ({
    onMouseDown: () => holdMove(cmd), onMouseUp: stopMove, onMouseLeave: stopMove,
    onTouchStart: (e: React.TouchEvent) => { e.preventDefault(); holdMove(cmd) },
    onTouchEnd: (e: React.TouchEvent) => { e.preventDefault(); stopMove() },
  })
  const ptzBtn = (cmd: number) => ({
    onMouseDown: () => holdPtz(cmd), onMouseUp: () => stopPtz(cmd), onMouseLeave: () => stopPtz(cmd),
    onTouchStart: (e: React.TouchEvent) => { e.preventDefault(); holdPtz(cmd) },
    onTouchEnd: (e: React.TouchEvent) => { e.preventDefault(); stopPtz(cmd) },
  })

  return (
    <div style={{ fontSize: 12 }}>
      {/* 实时状态 */}
      <div style={{ background: '#f5f7fa', borderRadius: 6, padding: '6px 10px', marginBottom: 8 }}>
        <div style={{ display: 'flex', alignItems: 'center', gap: 6, marginBottom: 2 }}>
          <Tag size="small" color={live?.code === 0 ? 'green' : 'grey'}>{live?.code === 0 ? '在线' : (live ? '离线' : '读取中')}</Tag>
          {st.battery != null && <Tag size="small" color="blue">{st.battery}%</Tag>}
          {st.status != null && <span className="text-muted" style={{ fontSize: 11 }}>{(STATUS_MAP[st.status] || st.status)}</span>}
        </div>
        {st.pose && <div className="text-muted" style={{ fontSize: 11 }}>
          位置: ({Number(st.pose.point?.x||0).toFixed(2)}, {Number(st.pose.point?.y||0).toFixed(2)}) θ={Number(st.pose.theta||0).toFixed(1)}<br/>
          云台: P{Number(st.pose.ptz?.pan||0).toFixed(1)} T{Number(st.pose.ptz?.tilt||0).toFixed(1)} Z{Number(st.pose.ptz?.zoom||0).toFixed(1)}<br/>
          升降: {st.lift_height != null ? Number(st.lift_height).toFixed(2)+'m' : '-'} | CPU: {st.cpu!=null?Number(st.cpu).toFixed(1)+'%':'-'}
        </div>}
      </div>

      <Tabs type="line" size="small">
        <TabPane tab="运动" itemKey="motion">
          <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 3, maxWidth: 130, margin: '4px auto', placeItems: 'center' }}>
            <div /><button style={{ width: 36, height: 36, borderRadius: '50%', border: '2px solid #dcdfe6', background: '#409eff', color: '#fff', cursor: 'pointer', fontSize: 16, padding: 0 }} {...btn(1)}>↑</button><div />
            <button style={{ width: 36, height: 36, borderRadius: '50%', border: '2px solid #dcdfe6', background: '#409eff', color: '#fff', cursor: 'pointer', fontSize: 16, padding: 0 }} {...btn(3)}>←</button>
            <button style={{ width: 36, height: 36, borderRadius: '50%', border: '2px solid #dcdfe6', background: '#f56c6c', color: '#fff', cursor: 'pointer', fontSize: 16, padding: 0 }} onMouseDown={stopMove}>■</button>
            <button style={{ width: 36, height: 36, borderRadius: '50%', border: '2px solid #dcdfe6', background: '#409eff', color: '#fff', cursor: 'pointer', fontSize: 16, padding: 0 }} {...btn(4)}>→</button>
            <div /><button style={{ width: 36, height: 36, borderRadius: '50%', border: '2px solid #dcdfe6', background: '#409eff', color: '#fff', cursor: 'pointer', fontSize: 16, padding: 0 }} {...btn(2)}>↓</button><div />
          </div>
        </TabPane>
        <TabPane tab="云台" itemKey="ptz">
          <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 2, maxWidth: 110, margin: '4px auto', placeItems: 'center' }}>
            <div /><button style={{ width: 30, height: 30, borderRadius: '50%', border: '2px solid #dcdfe6', background: '#67c23a', color: '#fff', cursor: 'pointer', fontSize: 13, padding: 0 }} {...ptzBtn(1)}>↑</button><div />
            <button style={{ width: 30, height: 30, borderRadius: '50%', border: '2px solid #dcdfe6', background: '#67c23a', color: '#fff', cursor: 'pointer', fontSize: 13, padding: 0 }} {...ptzBtn(3)}>←</button>
            <button style={{ width: 30, height: 30, borderRadius: '50%', border: '2px solid #dcdfe6', background: '#909399', color: '#fff', cursor: 'pointer', fontSize: 13, padding: 0 }} onClick={() => holdPtz(0)}>↺</button>
            <button style={{ width: 30, height: 30, borderRadius: '50%', border: '2px solid #dcdfe6', background: '#67c23a', color: '#fff', cursor: 'pointer', fontSize: 13, padding: 0 }} {...ptzBtn(4)}>→</button>
            <div /><button style={{ width: 30, height: 30, borderRadius: '50%', border: '2px solid #dcdfe6', background: '#67c23a', color: '#fff', cursor: 'pointer', fontSize: 13, padding: 0 }} {...ptzBtn(2)}>↓</button><div />
          </div>
          <div style={{ display: 'grid', gridTemplateColumns: '36px 1fr', gap: 2, marginTop: 6, alignItems: 'center' }}>
            <span>Pan</span><InputNumber size="small" value={ptz.pan} step={1} onChange={v => setPtz(p => ({...p, pan: Number(v)||0}))} />
            <span>Tilt</span><InputNumber size="small" value={ptz.tilt} step={1} onChange={v => setPtz(p => ({...p, tilt: Number(v)||0}))} />
            <span>Zoom</span><InputNumber size="small" value={ptz.zoom} step={0.1} onChange={v => setPtz(p => ({...p, zoom: Number(v)||0}))} />
            <div /><Button size="small" theme="solid" type="primary" disabled={!rid} onClick={setPtzPose}>设置</Button>
          </div>
        </TabPane>
        <TabPane tab="升降" itemKey="lift">
          <div className="flex gap-4" style={{ alignItems: 'center', marginBottom: 6 }}>
            <InputNumber size="small" value={liftH} step={0.1} min={0} onChange={v => setLiftH(Number(v)||0)} style={{ width: 60 }} />
            <Button size="small" theme="solid" type="primary" disabled={!rid} onClick={() => liftCmd(3, liftH)}>前往</Button>
          </div>
          <div className="flex gap-4" style={{ flexWrap: 'wrap' }}>
            <Button size="small" disabled={!rid} onClick={() => liftCmd(1)}>↑升</Button>
            <Button size="small" disabled={!rid} onClick={() => liftCmd(2)}>↓降</Button>
            <Button size="small" type="danger" disabled={!rid} onClick={() => liftCmd(0)}>停</Button>
            <Button size="small" disabled={!rid} onClick={() => liftCmd(4)}>复位</Button>
          </div>
        </TabPane>
        <TabPane tab="位姿" itemKey="pose">
          <div style={{ display: 'grid', gridTemplateColumns: '36px 1fr', gap: 2, alignItems: 'center' }}>
            <span>X</span><InputNumber size="small" value={pose.x} step={0.1} onChange={v => setPose(p => ({...p, x: Number(v)||0}))} />
            <span>Y</span><InputNumber size="small" value={pose.y} step={0.1} onChange={v => setPose(p => ({...p, y: Number(v)||0}))} />
            <span>θ</span><InputNumber size="small" value={pose.theta} step={1} onChange={v => setPose(p => ({...p, theta: Number(v)||0}))} />
            <div /><Button size="small" theme="solid" type="primary" disabled={!rid} onClick={setPoseFn}>前往</Button>
          </div>
        </TabPane>
      </Tabs>
    </div>
  )
}

// ========== 工具函数 ==========

const clone = <T,>(o: T): T => JSON.parse(JSON.stringify(o))

const findNode = (node: TreeNode | null, id: string): TreeNode | null => {
  if (!node) return null
  if (node.id === id) return node
  for (const c of node.children || []) {
    const f = findNode(c, id)
    if (f) return f
  }
  return null
}

/** 不可变替换树中指定 id 的节点, 返回新树; 未找到则返回原树 */
const replaceNodeById = (node: TreeNode, id: string, replacement: TreeNode): TreeNode => {
  if (node.id === id) return replacement
  return {
    ...node,
    children: (node.children || []).map((c) => replaceNodeById(c, id, replacement)),
  }
}

const collectIds = (node: TreeNode): string[] => {
  const out: string[] = [node.id]
  for (const c of node.children || []) out.push(...collectIds(c))
  return out
}

/** 按 DFS 顺序收集所有节点 id (扁平化) */
const flattenIds = (node: TreeNode): string[] => {
  const out: string[] = [node.id]
  for (const c of node.children || []) out.push(...flattenIds(c))
  return out
}

/** 获取两个节点之间的 DFS 范围 id 列表 (含两端) */
const getRangeIds = (root: TreeNode, idA: string, idB: string): string[] => {
  const all = flattenIds(root)
  const ia = all.indexOf(idA)
  const ib = all.indexOf(idB)
  if (ia === -1 || ib === -1) return [idB]
  const lo = Math.min(ia, ib)
  const hi = Math.max(ia, ib)
  return all.slice(lo, hi + 1)
}

/** 按点路径不可变更新, 例如 'pose.point.x' (沿路径浅拷贝, 不使用 any) */
const setIn = <T,>(obj: T, path: string, value: unknown): T => {
  const keys = path.split('.')
  const root: Record<string, unknown> = { ...(obj as Record<string, unknown>) }
  let cur: Record<string, unknown> = root
  for (let i = 0; i < keys.length - 1; i++) {
    const k = keys[i]
    const child = (cur[k] as Record<string, unknown> | undefined) ?? {}
    cur[k] = { ...child }
    cur = cur[k] as Record<string, unknown>
  }
  cur[keys[keys.length - 1]] = value
  return root as unknown as T
}

// ========== 树行组件(递归) ==========

type DropPos = 'before' | 'inside' | 'after'

interface TreeNodeRowProps {
  node: TreeNode
  parentId: string | null
  depth: number
  expanded: Set<string>
  selectedIds: Set<string>
  onSelect: (node: TreeNode, e: ReactMouseEvent) => void
  onToggle: (id: string) => void
  onContextMenu: (e: ReactMouseEvent, node: TreeNode, parentId: string | null) => void
  // drag-and-drop
  dragNodeId: string | null
  dropTarget: { nodeId: string; position: DropPos } | null
  onDragStart: (node: TreeNode) => void
  onDragOver: (e: ReactDragEvent, node: TreeNode) => void
  onDrop: (node: TreeNode) => void
  onDragEnd: () => void
  // 高亮ORB配准节点
  highlightOrb?: boolean
}

function TreeNodeRow(props: TreeNodeRowProps) {
  const { node, parentId, depth, expanded, selectedIds, onSelect, onToggle, onContextMenu,
    dragNodeId, dropTarget, onDragStart, onDragOver, onDrop, onDragEnd, highlightOrb } = props
  const hasChildren = !!(node.children && node.children.length)
  const isOpen = expanded.has(node.id)
  const isSelected = selectedIds.has(node.id)
  const meta = metaOf(node.nodeType)
  const RowIcon = meta.icon
  const isRoot = node.id === 'root'
  const isDragging = dragNodeId === node.id
  const isDropTarget = dropTarget?.nodeId === node.id
  const dropClass = isDropTarget ? ` drop-${dropTarget!.position}` : ''
  const isDisabled = !node.enable
  // 高亮ORB: 当开关打开时, 子树中包含OrbRegistration的航点节点(WaypointNode)变绿
  const hasOrbInSubtree = (n: TreeNode): boolean => {
    for (const c of n.children || []) {
      if (c.nodeType === 'OrbRegistration') return true
      if (hasOrbInSubtree(c)) return true
    }
    return false
  }
  const isOrbHighlight = !!highlightOrb && node.nodeType === 'WaypointNode' && hasOrbInSubtree(node)

  // 图标颜色: 高亮ORB时用绿色, 禁用时用灰色, 否则用默认
  const iconColor = isOrbHighlight ? '#52c41a' : (isDisabled ? '#c0c4cc' : meta.hex)
  // Tag颜色: 高亮ORB时用绿色, 否则用默认
  const tagColor = isOrbHighlight ? 'green' : meta.color
  // 行样式: 禁用时变灰
  const rowClass = `wt-row${isSelected ? ' selected' : ''}${dropClass}${isDragging ? ' dragging' : ''}${isDisabled ? ' disabled' : ''}${isOrbHighlight ? ' orb-highlight' : ''}`

  return (
    <div className="wt-node">
      <div
        className={rowClass}
        style={{ paddingLeft: 8 + depth * 20 }}
        draggable={!isRoot}
        onDragStart={(e) => { e.dataTransfer.effectAllowed = 'move'; onDragStart(node) }}
        onDragOver={(e) => onDragOver(e, node)}
        onDrop={(e) => { e.preventDefault(); onDrop(node) }}
        onDragEnd={onDragEnd}
        onClick={(e) => onSelect(node, e)}
        onDoubleClick={(e) => { e.stopPropagation(); if (hasChildren) onToggle(node.id) }}
        onContextMenu={(e) => onContextMenu(e, node, parentId)}
      >
        <span
          className="wt-toggle"
          onClick={(e) => { e.stopPropagation(); if (hasChildren) onToggle(node.id) }}
        >
          {hasChildren ? (isOpen ? <IconChevronDown /> : <IconChevronRight />) : null}
        </span>
        <span className="wt-icon" style={{ color: iconColor }}><RowIcon /></span>
        <span className="wt-name">{node.name || '(未命名)'}</span>
        <Tag size="small" color={tagColor as any}>{meta.label}</Tag>
        {!node.enable && <Tag size="small" color="grey">禁用</Tag>}
      </div>
      {hasChildren && isOpen && (node.children || []).map((c) => (
        <TreeNodeRow
          key={c.id}
          node={c}
          parentId={node.id}
          depth={depth + 1}
          expanded={expanded}
          selectedIds={selectedIds}
          onSelect={onSelect}
          onToggle={onToggle}
          onContextMenu={onContextMenu}
          dragNodeId={dragNodeId}
          dropTarget={dropTarget}
          onDragStart={onDragStart}
          onDragOver={onDragOver}
          onDrop={onDrop}
          onDragEnd={onDragEnd}
          highlightOrb={highlightOrb}
        />
      ))}
    </div>
  )
}

// ========== 快照图预览 ==========

function SnapShotPreview({ url }: { url: string }) {
  const [error, setError] = useState(false)
  useEffect(() => { setError(false) }, [url])
  if (!url || error) return null
  return (
    <div style={{ marginTop: 8, textAlign: 'center' }}>
      <img
        src={url}
        alt="snap_shot"
        onError={() => setError(true)}
        style={{ maxWidth: '100%', maxHeight: 240, borderRadius: 6, border: '1px solid #e4e7ed' }}
      />
    </div>
  )
}

function OrbRefPreview({ rid, relPath }: { rid: number; relPath: string }) {
  const [error, setError] = useState(false)
  const [retry, setRetry] = useState(0)
  useEffect(() => { setError(false) }, [relPath, retry])
  if (!relPath || error) {
    if (error) {
      return (
        <div style={{ marginTop: 8, textAlign: 'center', color: '#999', fontSize: 12 }}>
          图片加载失败 · <span style={{ color: '#1890ff', cursor: 'pointer' }} onClick={() => { setError(false); setRetry(r => r + 1) }}>重试</span>
        </div>
      )
    }
    return null
  }
  const url = refImageUrl(rid, relPath)
  return (
    <div style={{ marginTop: 8, textAlign: 'center' }}>
      <img
        src={`${url}?_t=${retry}`}
        alt="ref preview"
        onError={() => setError(true)}
        style={{ maxWidth: '100%', maxHeight: 200, borderRadius: 6, border: '1px solid #e4e7ed' }}
      />
    </div>
  )
}

// ========== 检视器 ==========

interface InspectorProps {
  node: TreeNode
  rid: number | null
  onField: (path: string, value: unknown) => void
  thermoText: string
  onThermoText: (v: string) => void
  thermoValid: boolean
  onSave: () => void
  saving: boolean
  onCapture: () => void
  showDebugImgs?: boolean
  debugSessions?: any
  tree?: TreeNode | null
  onOpenMetrics?: (data: { visible: boolean; iters: any[]; m: any; matchingKey: string; files: string[] }) => void
  onLoadMetrics?: () => void
  metricsLoading?: boolean
}

function Inspector(props: InspectorProps) {
  const { node, rid, onField, thermoText, onThermoText, thermoValid, onSave, saving, onCapture, debugSessions, tree, onOpenMetrics, onLoadMetrics, metricsLoading } = props
  const nt = node.nodeType

  return (
    <div className="wt-inspector">
      {/* 通用字段 */}
      <div className="wt-grid">
        <span>名称</span>
        <Input value={node.name ?? ''} onChange={(v) => onField('name', v)} placeholder="节点名称" />
        <span>启用</span>
        <Switch checked={!!node.enable} onChange={(v) => onField('enable', v)} />
        <span>节点类型</span>
        <Tag color={metaOf(nt).color as any}>{nodeTypeLabel(nt)}</Tag>
        <span>ID</span>
        <span className="text-muted text-mono" style={{ fontSize: 11, wordBreak: 'break-all' }}>{node.id}</span>
      </div>

      {/* WaypointNode */}
      {node.nodeType === 'WaypointNode' && (
        <>
          <Divider align="left">位姿 Pose</Divider>
          <div className="wt-grid">
            <span>point.x</span>
            <InputNumber value={node.pose?.point?.x ?? 0} step={0.01} onChange={(v) => onField('pose.point.x', Number(v) || 0)} />
            <span>point.y</span>
            <InputNumber value={node.pose?.point?.y ?? 0} step={0.01} onChange={(v) => onField('pose.point.y', Number(v) || 0)} />
            <span>point.z</span>
            <InputNumber value={node.pose?.point?.z ?? 0} step={0.01} onChange={(v) => onField('pose.point.z', Number(v) || 0)} />
            <span>theta</span>
            <InputNumber value={node.pose?.theta ?? 0} step={0.1} onChange={(v) => onField('pose.theta', Number(v) || 0)} />
          </div>
          <Divider align="left">航点属性</Divider>
          <div className="wt-grid">
            <span>index</span>
            <InputNumber value={node.index ?? 0} step={1} onChange={(v) => onField('index', Number(v) || 0)} />
            <span>type</span>
            <InputNumber value={node.type ?? 0} step={1} onChange={(v) => onField('type', Number(v) || 0)} />
          </div>
        </>
      )}

      {/* ActionNode */}
      {node.nodeType === 'ActionNode' && (
        <>
          <Divider align="left">云台参数 ptz_param</Divider>
          <div className="wt-grid">
            <span>pan</span>
            <InputNumber value={node.ptz_param?.pan ?? 0} step={1} onChange={(v) => onField('ptz_param.pan', Number(v) || 0)} />
            <span>tilt</span>
            <InputNumber value={node.ptz_param?.tilt ?? 0} step={1} onChange={(v) => onField('ptz_param.tilt', Number(v) || 0)} />
            <span>zoom</span>
            <InputNumber value={node.ptz_param?.zoom ?? 0} step={0.1} onChange={(v) => onField('ptz_param.zoom', Number(v) || 0)} />
            <span>focus</span>
            <InputNumber value={node.ptz_param?.focus ?? 0} step={1} onChange={(v) => onField('ptz_param.focus', Number(v) || 0)} />
            <span>focal_len</span>
            <InputNumber value={node.ptz_param?.focal_len ?? 0} step={1} onChange={(v) => onField('ptz_param.focal_len', Number(v) || 0)} />
          </div>
          <Divider align="left">动作属性</Divider>
          <div className="wt-grid">
            <span>lift_height</span>
            <InputNumber value={node.lift_height ?? 0} step={0.1} min={0} onChange={(v) => onField('lift_height', Number(v) || 0)} />
            <span>type</span>
            <InputNumber value={node.type ?? 0} step={1} onChange={(v) => onField('type', Number(v) || 0)} />
            <span>steer_point_name</span>
            <Input value={node.steer_point_name ?? ''} onChange={(v) => onField('steer_point_name', v)} />
            <span>snap_shot_url</span>
            <Input value={node.snap_shot_url ?? ''} onChange={(v) => onField('snap_shot_url', v)} />
          </div>
          <SnapShotPreview url={node.snap_shot_url ?? ''} />
          <Divider align="left">测温点 thermometry_points (JSON)</Divider>
          <TextArea
            value={thermoText}
            rows={6}
            onChange={onThermoText}
            style={{ fontFamily: 'Consolas, Monaco, monospace', fontSize: 12 }}
          />
          {!thermoValid && (
            <div style={{ color: '#f56c6c', fontSize: 12, marginTop: 4 }}>JSON 格式错误, 保存前请修正</div>
          )}
          <CalibrationDebugPanel node={node} rid={rid} />
        </>
      )}

      {/* OrbRegistration */}
      {node.nodeType === 'OrbRegistration' && (
        <>
          <Divider align="left">参考图</Divider>
          <div className="wt-grid">
            <span>refImageUrl</span>
            <div className="flex gap-8" style={{ alignItems: 'center' }}>
              <Input value={node.refImageUrl ?? ''} onChange={(v) => onField('refImageUrl', v)} placeholder="navRefImg/xxx.jpg" />
              <Button icon={<IconCamera />} theme="solid" type="primary" disabled={!rid} onClick={onCapture}>抓拍</Button>
            </div>
          </div>
          {node.refImageUrl && rid && (
            <OrbRefPreview rid={rid} relPath={node.refImageUrl} />
          )}
          <Divider align="left">云台参数 ptz</Divider>
          <div className="wt-grid">
            <span>pan</span>
            <InputNumber value={node.ptz?.pan ?? 0} step={1} onChange={(v) => onField('ptz.pan', Number(v) || 0)} />
            <span>tilt</span>
            <InputNumber value={node.ptz?.tilt ?? 0} step={1} onChange={(v) => onField('ptz.tilt', Number(v) || 0)} />
            <span>zoom</span>
            <InputNumber value={node.ptz?.zoom ?? 0} step={0.1} onChange={(v) => onField('ptz.zoom', Number(v) || 0)} />
            <span>focus</span>
            <InputNumber value={node.ptz?.focus ?? 0} step={1} onChange={(v) => onField('ptz.focus', Number(v) || 0)} />
            <span>focal_len</span>
            <InputNumber value={node.ptz?.focal_len ?? 0} step={1} onChange={(v) => onField('ptz.focal_len', Number(v) || 0)} />
          </div>
          <Divider align="left">位姿 / 升降</Divider>
          <div className="wt-grid">
            <span>point.x</span>
            <InputNumber value={node.pose?.point?.x ?? 0} step={0.01} onChange={(v) => onField('pose.point.x', Number(v) || 0)} />
            <span>point.y</span>
            <InputNumber value={node.pose?.point?.y ?? 0} step={0.01} onChange={(v) => onField('pose.point.y', Number(v) || 0)} />
            <span>point.z</span>
            <InputNumber value={node.pose?.point?.z ?? 0} step={0.01} onChange={(v) => onField('pose.point.z', Number(v) || 0)} />
            <span>theta</span>
            <InputNumber value={node.pose?.theta ?? 0} step={0.1} onChange={(v) => onField('pose.theta', Number(v) || 0)} />
            <span>lift_height</span>
            <InputNumber value={node.lift_height ?? 0} step={0.1} min={0} onChange={(v) => onField('lift_height', Number(v) || 0)} />
          </div>
          <CalibrationDebugPanel node={node} rid={rid} />
        </>
      )}

      {/* TaskPointNode - 无额外字段 */}
      {nt === 'TaskPointNode' && (
        <Empty description="测点无额外属性" style={{ marginTop: 24 }} />
      )}
      {nt === 'GroupNode' && (
        <Empty description="分组节点无额外属性, 可将多个节点拖入或创建到此分组下" style={{ marginTop: 24 }} />
      )}
      {nt === 'Root' && (
        <Empty description="根节点无额外属性, 右键根节点可添加子节点" style={{ marginTop: 24 }} />
      )}
      {!['WaypointNode', 'ActionNode', 'OrbRegistration', 'TaskPointNode', 'Root', 'GroupNode'].includes(nt) && (
        <Empty description={`未知节点类型: ${nt}`} style={{ marginTop: 24 }} />
      )}

      {/* 配准指标详情按钮 (ORB配准 / 动作点 共用) — 始终显示, 点击加载 */}
      {(nt === 'OrbRegistration' || nt === 'ActionNode') && rid && (
        <div style={{ marginTop: 8 }}>
          <Button
            theme="light"
            type="primary"
            size="small"
            icon={<IconSimilarity />}
            loading={metricsLoading}
            onClick={onLoadMetrics}
          >
            查看配准指标详情
          </Button>
        </div>
      )}

      <div className="flex gap-8" style={{ marginTop: 16 }}>
        <Button theme="solid" type="primary" icon={<IconSave />} loading={saving} onClick={onSave}>
          保存节点
        </Button>
      </div>
    </div>
  )
}

// ========== 主组件 ==========

export default function WaypointTreeManager() {
  const { selectedRid: rid } = useRobotId()
  const [tree, setTree] = useState<TreeNode | null>(null)
  const [loading, setLoading] = useState(false)
  const [expanded, setExpanded] = useState<Set<string>>(new Set())
  const [selectedIds, setSelectedIds] = useState<Set<string>>(new Set())
  const [lastClickedId, setLastClickedId] = useState<string | null>(null)
  const [editing, setEditing] = useState<TreeNode | null>(null)
  const [saving, setSaving] = useState(false)
  const [savingTree, setSavingTree] = useState(false)
  const [moving, setMoving] = useState(false)

  // 导入弹窗
  const [importVisible, setImportVisible] = useState(false)
  const [importMode, setImportMode] = useState<'replace' | 'merge' | 'append'>('merge')
  const [importFile, setImportFile] = useState<File | null>(null)
  const [importing, setImporting] = useState(false)
  const importInputRef = useRef<HTMLInputElement>(null)

  // 测温点 JSON 文本(仅 ActionNode 使用)
  const [thermoText, setThermoText] = useState('[]')
  const [thermoValid, setThermoValid] = useState(true)

  // 右键菜单 (定位到鼠标位置)
  const [ctxMenu, setCtxMenu] = useState<{
    x: number; y: number; node: TreeNode; parentId: string | null
  } | null>(null)
  const ctxMenuRef = useRef<HTMLDivElement>(null)
  const [ctxMenuPos, setCtxMenuPos] = useState<{ x: number; y: number; flipSub: boolean }>({ x: 0, y: 0, flipSub: false })

  // 右键菜单边界检测: 确保菜单和子菜单完整显示在视口内
  useLayoutEffect(() => {
    if (!ctxMenu) { setCtxMenuPos({ x: 0, y: 0, flipSub: false }); return }
    const el = ctxMenuRef.current
    let x = ctxMenu.x
    let y = ctxMenu.y
    let flipSub = false
    if (el) {
      const rect = el.getBoundingClientRect()
      // 右边缘溢出 → 左移
      if (x + rect.width > window.innerWidth - 8) {
        x = Math.max(8, window.innerWidth - rect.width - 8)
      }
      // 子菜单宽度约 220px, 若右侧空间不足则子菜单向左展开
      if (x + rect.width + 220 > window.innerWidth) {
        flipSub = true
      }
      // 下边缘溢出 → 上移
      if (y + rect.height > window.innerHeight - 8) {
        y = Math.max(8, window.innerHeight - rect.height - 8)
      }
    }
    setCtxMenuPos({ x, y, flipSub })
  }, [ctxMenu])

  // 剪切板 (存储被剪切的节点 id 列表, 支持多选)
  const [clipboard, setClipboard] = useState<string[]>([])

  // Splitter 左栏宽度
  const [leftWidth, setLeftWidth] = useState(300)
  const [rightWidth, setRightWidth] = useState(340)
  const [videoHeight, setVideoHeight] = useState(360)
  const splitterDragging = useRef(false)
  const rightDragging = useRef(false)
  const vDragging = useRef(false)

  // JSON 查看器 (Monaco editor)
  const [jsonViewer, setJsonViewer] = useState<{ node: TreeNode } | null>(null)

  // 自动加载配准过程数据
  useEffect(() => {
    if (rid) {
      import('../../api/calibration').then(m => m.listDebugSessions(rid).then(r => setDebugSessions(r.data)))
    } else {
      setDebugSessions(null)
    }
  }, [rid])
  const [highlightOrb, setHighlightOrb] = useState(true)
  const [debugSessions, setDebugSessions] = useState<any>(null)
  const [metricsModal, setMetricsModal] = useState<{
    visible: boolean; iters: any[]; m: any; matchingKey: string; files: string[]
  } | null>(null)
  const [metricsLoading, setMetricsLoading] = useState(false)

  // 实时视频
  const visPlayerRef = useRef<WebRTCPlayerRef>(null)
  const thmPlayerRef = useRef<WebRTCPlayerRef>(null)

  // ORB 抓拍弹窗
  const [captureDialog, setCaptureDialog] = useState(false)

  // 拖拽移动
  const [dragNodeId, setDragNodeId] = useState<string | null>(null)
  const [dropTarget, setDropTarget] = useState<{ nodeId: string; position: DropPos } | null>(null)

  // ---------- 加载树 ----------
  const loadTree = useCallback(async (): Promise<TreeNode | null> => {
    if (!rid) { setTree(null); return null }
    setLoading(true)
    try {
      const { data } = await getTree(rid)
      setTree(data)
      setExpanded((prev) => {
        const next = new Set(prev)
        next.add(data.id) // 默认展开根
        return next
      })
      return data
    } catch {
      return null
    } finally {
      setLoading(false)
    }
  }, [rid])

  useEffect(() => { loadTree() }, [loadTree])

  // ---------- 选择节点 (支持多选: Ctrl 切换, Shift 范围) ----------
  const selectNode = useCallback((node: TreeNode, e: ReactMouseEvent) => {
    const ctrl = e.ctrlKey || e.metaKey
    const shift = e.shiftKey

    if (ctrl) {
      // Ctrl+Click: 切换该节点的选中状态
      setSelectedIds((prev) => {
        const next = new Set(prev)
        if (next.has(node.id)) next.delete(node.id)
        else next.add(node.id)
        // 单选时显示表单, 多选时清空
        if (next.size === 1) {
          const id = [...next][0]
          const found = findNode(tree, id)
          setEditing(found ? clone(found) : null)
        } else {
          setEditing(null)
        }
        return next
      })
      setLastClickedId(node.id)
    } else if (shift && lastClickedId && tree) {
      // Shift+Click: 从上次点击到当前节点之间的范围选择
      const range = getRangeIds(tree, lastClickedId, node.id)
      setSelectedIds(new Set(range))
      setEditing(null) // 多选时不显示表单
    } else {
      // 普通点击: 仅选中该节点
      setSelectedIds(new Set([node.id]))
      setLastClickedId(node.id)
      setEditing(clone(node))
    }
  }, [lastClickedId, tree])

  // 选中节点变化时同步测温点 JSON 文本
  useEffect(() => {
    if (editing && editing.nodeType === 'ActionNode') {
      setThermoText(JSON.stringify(editing.thermometry_points ?? [], null, 2))
      setThermoValid(true)
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [editing?.id, editing?.nodeType])

  const onToggle = useCallback((id: string) => {
    setExpanded((prev) => {
      const next = new Set(prev)
      if (next.has(id)) next.delete(id)
      else next.add(id)
      return next
    })
  }, [])

  const expandAll = useCallback(() => {
    if (tree) setExpanded(new Set(collectIds(tree)))
  }, [tree])

  const collapseAll = useCallback(() => {
    setExpanded(new Set())
  }, [])

  // ---------- 工具栏: 移动 ----------
  const moveToWaypoint = async () => {
    if (!rid || !editing) return
    if (editing.nodeType !== 'WaypointNode' || !editing.pose || !editing.pose.point) {
      Toast.warning('请先选择一个航点节点(WaypointNode)')
      return
    }
    setMoving(true)
    try {
      const p = editing.pose
      await motionSetPose(rid, { x: p.point.x, y: p.point.y, theta: p.theta })
      Toast.success('已下发移动指令')
    } catch {
      /* http 拦截器已提示 */
    } finally {
      setMoving(false)
    }
  }

  const movePtzToAction = async () => {
    if (!rid || !editing) return
    if (editing.nodeType !== 'ActionNode' && editing.nodeType !== 'OrbRegistration') {
      Toast.warning('请先选择一个动作点节点(ActionNode / OrbRegistration)')
      return
    }
    const ptz = editing.nodeType === 'ActionNode' ? editing.ptz_param : editing.ptz
    setMoving(true)
    try {
      await ptzSetPose(rid, { pan: ptz.pan, tilt: ptz.tilt, zoom: ptz.zoom })
      await liftControl(rid, 3, editing.lift_height ?? 0)
      Toast.success('已下发云台指令')
    } catch {
      /* http 拦截器已提示 */
    } finally {
      setMoving(false)
    }
  }

  // ---------- 工具栏: 导入 / 导出 / 保存整棵树 ----------
  const openImport = () => {
    setImportFile(null)
    setImportMode('merge')
    setImportVisible(true)
  }

  const doImport = async () => {
    if (!rid) return
    if (!importFile) { Toast.warning('请先选择 inspection.json 文件'); return }
    setImporting(true)
    try {
      const { data } = await importInspectionFile(rid, importFile, importMode === 'replace', importMode === 'merge')
      Toast.success(data?.msg || '导入完成')
      setImportVisible(false)
      setSelectedIds(new Set())
      setEditing(null)
      await loadTree()
    } catch {
      /* */
    } finally {
      setImporting(false)
    }
  }

  const handleExport = () => {
    if (!rid) return
    window.open(exportFileUrl(rid), '_blank')
  }

  const handleSaveTree = async () => {
    if (!rid || !tree) return
    setSavingTree(true)
    try {
      // 先保存 Inspector 中未提交的编辑
      let t = tree
      if (editing) {
        t = replaceNodeById(t, editing.id, editing)
      }
      await saveTree(rid, t)
      Toast.success('整棵树已保存')
    } catch {
      /* */
    } finally {
      setSavingTree(false)
    }
  }

  // ---------- 检视器: 字段更新 / 保存节点 ----------
  const onField = useCallback((path: string, value: unknown) => {
    setEditing((e) => (e ? setIn(e, path, value) : e))
  }, [])

  const onThermoText = (v: string) => {
    setThermoText(v)
    try {
      JSON.parse(v)
      setThermoValid(true)
    } catch {
      setThermoValid(false)
    }
  }

  const saveNode = async () => {
    if (!rid || !editing) return
    if (editing.nodeType === 'ActionNode' && !thermoValid) {
      Toast.warning('测温点 JSON 格式错误, 无法保存')
      return
    }
    setSaving(true)
    try {
      let payload = clone(editing)
      if (editing.nodeType === 'ActionNode') {
        let thermo: any[]
        try {
          thermo = JSON.parse(thermoText)
        } catch {
          thermo = editing.thermometry_points ?? []
        }
        payload = setIn(payload, 'thermometry_points', thermo)
      }
      await updateNode(rid, editing.id, payload)
      Toast.success('节点已保存')
      const latest = await loadTree()
      if (latest) {
        const found = findNode(latest, editing.id)
        if (found) setEditing(clone(found))
      }
    } catch {
      /* */
    } finally {
      setSaving(false)
    }
  }

  // ---------- 右键菜单: 添加 / 复制 / 删除 ----------
  const onAddChild = async (parent: TreeNode, nodeType: string) => {
    if (!rid) return
    try {
      const { data: newNode } = await createNode(rid, nodeType, nodeTypeLabel(nodeType), parent.id)
      Toast.success(`已添加${nodeTypeLabel(nodeType)}`)
      await loadTree()
      setExpanded((prev) => new Set([...prev, parent.id]))
      setSelectedIds(new Set([newNode.id]))
      setEditing(clone(newNode))
    } catch {
      /* */
    }
  }

  const onCopy = async (nodes: TreeNode[], parentId: string | null) => {
    if (!rid || nodes.length === 0) return
    try {
      // 逐个复制到同级父节点下
      for (const node of nodes) {
        await copyNode(rid, node.id, parentId)
      }
      Toast.success(`已复制 ${nodes.length} 个节点(作为同级)`)
      await loadTree()
    } catch {
      /* */
    }
  }

  // ---------- 剪切 / 粘贴 (支持多选) ----------
  const onCut = (nodes: TreeNode[]) => {
    const valid = nodes.filter((n) => n.id !== 'root')
    if (valid.length === 0) { Toast.warning('不能剪切根节点'); return }
    setClipboard(valid.map((n) => n.id))
    Toast.info(`已剪切 ${valid.length} 个节点, 右键目标节点选择「粘贴到节点前面」`)
  }

  /** 查找节点在父节点 children 中的索引位置 */
  const findIndexInParent = (root: TreeNode, targetId: string): { parentId: string | null; index: number } | null => {
    const search = (node: TreeNode, parent: TreeNode | null): boolean => {
      if (node.id === targetId) {
        if (parent) {
          const idx = (parent.children || []).findIndex((c) => c.id === targetId)
          result = { parentId: parent.id, index: idx }
        } else {
          result = { parentId: null, index: 0 }
        }
        return true
      }
      for (const c of node.children || []) {
        if (search(c, node)) return true
      }
      return false
    }
    let result: { parentId: string | null; index: number } | null = null
    search(root, null)
    return result
  }

  /** 粘贴: 将剪切的多个节点移动到目标节点的前面(同级插入) */
  const onPasteBefore = async (targetNode: TreeNode) => {
    if (!rid || clipboard.length === 0) { Toast.warning('剪贴板为空'); return }
    if (targetNode.id === 'root') { Toast.warning('不能粘贴到根节点前面'); return }

    // 找到目标节点在父节点中的位置
    if (!tree) return
    const info = findIndexInParent(tree, targetNode.id)
    if (!info) { Toast.warning('无法定位目标节点位置'); return }

    try {
      // 按顺序逐个移动到目标位置前面 (每次插入后 index 递增)
      let insertIdx = info.index
      for (const clipId of clipboard) {
        if (clipId === targetNode.id) continue // 不能粘贴到自身前面
        await moveNode(rid, clipId, info.parentId, insertIdx)
        insertIdx++
      }
      Toast.success(`已粘贴 ${clipboard.length} 个节点到目标前面`)
      setClipboard([])
      await loadTree()
    } catch {
      /* */
    }
  }

  // ---------- 展开/收起子节点 (支持多选) ----------
  const expandSubtreeMulti = (nodes: TreeNode[]) => {
    setExpanded((prev) => {
      const next = new Set(prev)
      const walk = (n: TreeNode) => {
        if (n.children && n.children.length) {
          next.add(n.id)
          n.children.forEach(walk)
        }
      }
      nodes.forEach(walk)
      return next
    })
  }

  const collapseNodeMulti = (nodes: TreeNode[]) => {
    setExpanded((prev) => {
      const next = new Set(prev)
      nodes.forEach((n) => next.delete(n.id))
      return next
    })
  }

  const onDeleteMulti = (nodes: TreeNode[]) => {
    const valid = nodes.filter((n) => n.id !== 'root')
    if (valid.length === 0) { Toast.warning('不能删除根节点'); return }
    const names = valid.map((n) => n.name || nodeTypeLabel(n.nodeType)).join(', ')
    Modal.confirm({
      title: `删除 ${valid.length} 个节点`,
      content: `确定删除「${names}」及其所有子节点吗? 此操作不可撤销。`,
      okText: '删除',
      cancelText: '取消',
      okType: 'danger',
      onOk: async () => {
        if (!rid) return
        for (const node of valid) {
          await deleteNode(rid, node.id)
        }
        Toast.success(`已删除 ${valid.length} 个节点`)
        setSelectedIds(new Set())
        setEditing(null)
        await loadTree()
      },
    })
  }

  // ---------- 创建分组 (多选) ----------
  const onCreateGroup = async (nodes: TreeNode[]) => {
    if (!rid) return
    const valid = nodes.filter((n) => n.id !== 'root')
    if (valid.length === 0) { Toast.warning('不能对根节点创建分组'); return }
    try {
      const { data: groupNode } = await createGroup(rid, valid.map((n) => n.id), '分组')
      Toast.success(`已创建分组, 包含 ${valid.length} 个节点`)
      await loadTree()
      // 选中并展开新的分组节点
      setSelectedIds(new Set([groupNode.id]))
      setEditing(clone(groupNode))
      // 展开分组的父节点 (让分组可见)
      if (tree) {
        const parent = findParentNode(tree, groupNode.id)
        if (parent) {
          setExpanded((prev) => new Set([...prev, parent.id, groupNode.id]))
        }
      }
    } catch {
      /* */
    }
  }

  /** 查找节点的父节点 (DFS) */
  const findParentNode = (root: TreeNode, targetId: string): TreeNode | null => {
    for (const c of root.children || []) {
      if (c.id === targetId) return root
      const found = findParentNode(c, targetId)
      if (found) return found
    }
    return null
  }

  // ---------- 拖拽移动 ----------
  const handleDragStart = useCallback((node: TreeNode) => {
    if (node.id === 'root') return
    setDragNodeId(node.id)
  }, [])

  const handleDragOver = useCallback((e: ReactDragEvent, node: TreeNode) => {
    if (!dragNodeId || dragNodeId === node.id) return
    e.preventDefault()
    e.dataTransfer.dropEffect = 'move'
    const rect = (e.currentTarget as HTMLElement).getBoundingClientRect()
    const y = e.clientY - rect.top
    const h = rect.height
    let pos: DropPos
    if (node.id === 'root') {
      pos = 'inside' // 根节点只能作为父节点
    } else if (y < h * 0.33) {
      pos = 'before'
    } else if (y > h * 0.67) {
      pos = 'after'
    } else {
      pos = 'inside'
    }
    setDropTarget((prev) => {
      if (prev?.nodeId === node.id && prev?.position === pos) return prev
      return { nodeId: node.id, position: pos }
    })
  }, [dragNodeId])

  const handleDrop = useCallback(async (targetNode: TreeNode) => {
    if (!rid || !dragNodeId || !dropTarget || !tree) {
      setDragNodeId(null)
      setDropTarget(null)
      return
    }
    const dragId = dragNodeId
    const { nodeId: targetId, position } = dropTarget
    setDragNodeId(null)
    setDropTarget(null)

    // 不能拖到自身
    if (dragId === targetId) return
    // 不能拖到根节点前/后
    if (targetId === 'root' && position !== 'inside') return

    try {
      if (position === 'inside') {
        // 作为目标节点的子节点 (末尾)
        await moveNode(rid, dragId, targetId, -1)
        setExpanded((prev) => new Set([...prev, targetId]))
      } else {
        // before/after: 作为目标节点的同级
        const info = findIndexInParent(tree, targetId)
        if (!info) return
        const insertIdx = position === 'before' ? info.index : info.index + 1
        await moveNode(rid, dragId, info.parentId, insertIdx)
      }
      Toast.success('节点已移动')
      await loadTree()
    } catch {
      /* */
    }
  }, [rid, dragNodeId, dropTarget, tree, loadTree])

  const handleDragEnd = useCallback(() => {
    setDragNodeId(null)
    setDropTarget(null)
  }, [])

  // rid 现在来自全局 header 选择

  // ---------- 右键菜单 ----------
  const handleContextMenu = (e: ReactMouseEvent, node: TreeNode, parentId: string | null) => {
    e.preventDefault()
    e.stopPropagation()
    // 如果右键的节点已在选中集合中, 则对所有选中节点操作
    // 否则仅选中该节点
    if (!selectedIds.has(node.id)) {
      setSelectedIds(new Set([node.id]))
      setLastClickedId(node.id)
      setEditing(clone(node))
    }
    setCtxMenu({ x: e.clientX, y: e.clientY, node, parentId })
  }

  /** 获取当前上下文菜单操作的目标节点列表 */
  const getCtxTargetNodes = (): TreeNode[] => {
    if (!tree) return [ctxMenu!.node]
    // 收集所有选中的节点 (DFS 顺序, 保持树中顺序)
    const result: TreeNode[] = []
    const walk = (n: TreeNode) => {
      if (selectedIds.has(n.id)) result.push(n)
      for (const c of n.children || []) walk(c)
    }
    walk(tree)
    // 如果没有选中的 (不太可能), 回退到右键的节点
    return result.length > 0 ? result : [ctxMenu!.node]
  }

  // ---------- ORB 抓拍回调 ----------
  const handleCaptured = (data: {
    refImagePath: string
    pose: { theta: number; point: { x: number; y: number; z: number } }
    ptz: { pan: number; tilt: number; zoom: number; focus: number; focal_len: number }
    liftHeight: number
  }) => {
    if (!editing || editing.nodeType !== 'OrbRegistration') return
    let updated = setIn(editing, 'refImageUrl', data.refImagePath)
    updated = setIn(updated, 'pose', data.pose)
    updated = setIn(updated, 'ptz', data.ptz)
    updated = setIn(updated, 'lift_height', data.liftHeight)
    setEditing(updated)
    Toast.success('已将抓拍数据填入 ORB 节点, 请点击「保存节点」')
  }

  // ESC 关闭右键菜单
  useEffect(() => {
    if (!ctxMenu) return
    const onKey = (e: KeyboardEvent) => { if (e.key === 'Escape') setCtxMenu(null) }
    window.addEventListener('keydown', onKey)
    return () => window.removeEventListener('keydown', onKey)
  }, [ctxMenu])

  // ---------- 渲染辅助 ----------
  const canMoveWaypoint = !!editing && editing.nodeType === 'WaypointNode' && !!editing.pose
  const canMovePtz = !!editing && (
    (editing.nodeType === 'ActionNode' && !!editing.ptz_param) ||
    (editing.nodeType === 'OrbRegistration' && !!editing.ptz)
  )
  const multiSelectCount = selectedIds.size
  const inspectorTitle = multiSelectCount > 1
    ? `选中了 ${multiSelectCount} 个节点`
    : editing
      ? `${nodeTypeLabel(editing.nodeType)} · ${editing.name || '(未命名)'}`
      : '检视器'

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>航点树管理</h2>
      </div>

      {rid && (
        <Card className="card-shadow mb-12" bordered={false} bodyStyle={{ padding: '10px 14px' }}>
          <div className="flex gap-8" style={{ flexWrap: 'wrap', alignItems: 'center' }}>
            <Button icon={<IconExpand />} onClick={expandAll} disabled={!tree}>展开全部</Button>
            <Button icon={<IconShrink />} onClick={collapseAll} disabled={!tree}>收起全部</Button>
            <span className="wt-sep" />
            <Button icon={<IconRoute />} loading={moving} disabled={!canMoveWaypoint} onClick={moveToWaypoint}>
              移动到选中航点
            </Button>
            <Button icon={<IconCamera />} loading={moving} disabled={!canMovePtz} onClick={movePtzToAction}>
              云台移到选中动作点
            </Button>
            <span className="wt-sep" />
            <Button icon={<IconImport />} onClick={openImport}>从 inspection.json 导入</Button>
            <Button icon={<IconExport />} onClick={handleExport} disabled={!tree}>导出</Button>
            <Button icon={<IconSave />} theme="solid" type="primary" loading={savingTree} disabled={!tree} onClick={handleSaveTree}>
              保存
            </Button>
            <Button icon={<IconRefresh />} theme="borderless" onClick={() => loadTree()} disabled={!rid}>
              刷新
            </Button>
            <span className="wt-sep" />
            <div style={{ display: 'inline-flex', alignItems: 'center', gap: 6 }}>
              <IconSimilarity style={{ color: highlightOrb ? '#52c41a' : '#c0c4cc' }} />
              <Switch
                checked={highlightOrb}
                onChange={(v) => setHighlightOrb(v)}
                size="small"
              />
              <span style={{ fontSize: 13, color: highlightOrb ? '#52c41a' : '#606266', whiteSpace: 'nowrap' }}>
                高亮有定位图的航点
              </span>
            </div>
          </div>
        </Card>
      )}

      {rid && (
        <div style={{ display: 'flex', gap: 8, height: 'calc(100vh - 280px)', minHeight: 500 }}>
          {/* 左区: 树 + 检视器 (可拖拽分隔) */}
          <div className="wt-splitter" style={{ flex: 1, minWidth: 0 }}>
            {/* 左栏: 航点树 */}
            <div className="wt-splitter-left" style={{ width: leftWidth, flexShrink: 0 }}>
              <Card
                className="card-shadow"
                bordered={false}
                title={
                  <span style={{ display: 'inline-flex', alignItems: 'center', gap: 6 }}>
                    <IconBranch /> 航点树
                  </span>
                }
                bodyStyle={{ padding: 8 }}
                style={{ height: '100%' }}
              >
                <Spin spinning={loading}>
                  {tree ? (
                    <div className="wt-tree" style={{ maxHeight: 'calc(100vh - 360px)' }}>
                      <TreeNodeRow
                        node={tree}
                        parentId={null}
                        depth={0}
                        expanded={expanded}
                        selectedIds={selectedIds}
                        onSelect={selectNode}
                        onToggle={onToggle}
                        onContextMenu={handleContextMenu}
                        dragNodeId={dragNodeId}
                        dropTarget={dropTarget}
                        onDragStart={handleDragStart}
                        onDragOver={handleDragOver}
                        onDrop={handleDrop}
                        onDragEnd={handleDragEnd}
                        highlightOrb={highlightOrb}
                      />
                    </div>
                  ) : (
                    <Empty description="暂无数据" />
                  )}
                </Spin>
                <div className="text-muted" style={{ fontSize: 12, marginTop: 6, padding: '0 4px' }}>
                  提示: 左键选择, Ctrl+左键多选, Shift+左键范围选择, 双击展开/收起, 拖拽移动节点, 右键弹出菜单
                </div>
              </Card>
            </div>

            {/* Splitter 拖拽分隔条 */}
            <div
              className="wt-splitter-handle"
              onMouseDown={(e) => {
                e.preventDefault()
                splitterDragging.current = true
                const startX = e.clientX
                const startW = leftWidth
                const onMove = (ev: MouseEvent) => {
                  if (!splitterDragging.current) return
                  const dx = ev.clientX - startX
                  setLeftWidth(Math.max(200, Math.min(600, startW + dx)))
                }
                const onUp = () => {
                  splitterDragging.current = false
                  window.removeEventListener('mousemove', onMove)
                  window.removeEventListener('mouseup', onUp)
                }
                window.addEventListener('mousemove', onMove)
                window.addEventListener('mouseup', onUp)
              }}
            />

            {/* 中栏: 检视器 */}
            <div className="wt-splitter-right" style={{ flex: 1, minWidth: 0 }}>
              <Card className="card-shadow" bordered={false} title={inspectorTitle} bodyStyle={{ padding: 12 }} style={{ height: '100%' }}>
              {multiSelectCount > 1 ? (
                <div style={{ textAlign: 'center', marginTop: 60 }}>
                  <Empty
                    description={
                      <div>
                        <div style={{ fontSize: 16, marginBottom: 8 }}>选中了 {multiSelectCount} 个节点</div>
                        <div className="text-muted" style={{ fontSize: 13 }}>
                          多选模式下不显示具体表单。可使用右键菜单进行批量操作: 展开/收起/剪切/粘贴/复制/删除/创建分组
                        </div>
                      </div>
                    }
                  />
                </div>
              ) : editing ? (
                <Inspector
                  node={editing}
                  rid={rid}
                  onField={onField}
                  thermoText={thermoText}
                  onThermoText={onThermoText}
                  thermoValid={thermoValid}
                  onSave={saveNode}
                  saving={saving}
                  onCapture={() => setCaptureDialog(true)}
                  showDebugImgs={true}
                  debugSessions={debugSessions}
                  tree={tree}
                  onOpenMetrics={(data) => setMetricsModal(data)}
                  onLoadMetrics={async () => {
                    if (!rid || !editing) return
                    setMetricsLoading(true)
                    try {
                      const { data: fresh } = await listDebugSessions(rid, editing.id)
                      setDebugSessions(fresh)
                      const metricsMap: Record<string, any> = fresh.metrics || {}
                      const matchingKey = Object.keys(metricsMap).find(k =>
                        k.includes(editing.id?.substring(0, 12) || '___NOMATCH___'))
                      if (!matchingKey) {
                        Toast.warning('未找到该节点的配准数据')
                        return
                      }
                      const m = metricsMap[matchingKey]
                      const iters = m.iterations_detail || []
                      if (iters.length === 0) {
                        Toast.warning('该节点配准数据为空')
                        return
                      }
                      const dirFiles = (fresh.files || []).filter((f: string) =>
                        f.startsWith(matchingKey + '/') && (f.endsWith('.jpg') || f.endsWith('.png')))
                      setMetricsModal({ visible: true, iters, m, matchingKey, files: dirFiles })
                    } catch {
                      Toast.error('加载配准数据失败')
                    } finally {
                      setMetricsLoading(false)
                    }
                  }}
                  metricsLoading={metricsLoading}
                />
              ) : (
                <Empty description="选择左侧节点查看并编辑属性" style={{ marginTop: 40 }} />
              )}
            </Card>
          </div>
        </div>

        {/* 右分隔条 */}
        <div
          className="wt-splitter-handle"
          style={{ marginTop: 0, marginBottom: 0 }}
          onMouseDown={(e) => {
            e.preventDefault()
            rightDragging.current = true
            const startX = e.clientX
            const startW = rightWidth
            const onMove = (ev: MouseEvent) => {
              if (!rightDragging.current) return
              setRightWidth(Math.max(280, Math.min(520, startW + startX - ev.clientX)))
            }
            const onUp = () => {
              rightDragging.current = false
              window.removeEventListener('mousemove', onMove)
              window.removeEventListener('mouseup', onUp)
            }
            window.addEventListener('mousemove', onMove)
            window.addEventListener('mouseup', onUp)
          }}
        />

        {/* 右栏: 实时视频 + 机器人控制 */}
        <div style={{ width: rightWidth, flexShrink: 0, display: 'flex', flexDirection: 'column', gap: 0, overflow: 'hidden' }}>
          {/* 视频区 */}
          <div style={{ height: videoHeight, flexShrink: 0, overflow: 'auto' }}>
            <Card className="card-shadow" bordered={false} title="实时视频" bodyStyle={{ padding: 4 }}>
              <WebRTCPlayer ref={visPlayerRef} rid={rid} autoplay={false} />
            </Card>
          </div>
          {/* 垂直分隔条 */}
          <div
            style={{ height: 6, cursor: 'row-resize', background: '#e4e7ed', flexShrink: 0, borderRadius: 3, margin: '4px 0', transition: 'background .15s' }}
            onMouseDown={(e) => {
              e.preventDefault()
              vDragging.current = true
              const startY = e.clientY
              const startH = videoHeight
              const onMove = (ev: MouseEvent) => {
                if (!vDragging.current) return
                setVideoHeight(Math.max(200, Math.min(600, startH + ev.clientY - startY)))
              }
              const onUp = () => {
                vDragging.current = false
                window.removeEventListener('mousemove', onMove)
                window.removeEventListener('mouseup', onUp)
              }
              window.addEventListener('mousemove', onMove)
              window.addEventListener('mouseup', onUp)
            }}
          />
          {/* 控制区 */}
          <div style={{ flex: 1, overflow: 'auto' }}>
            <Card className="card-shadow" bordered={false} title="机器人控制" bodyStyle={{ padding: '6px 8px' }}>
              <InlineControl rid={rid} />
            </Card>
          </div>
        </div>
      </div>
      )}

      {/* 导入弹窗 */}
      <Modal
        visible={importVisible}
        title="从 inspection.json 导入"
        onCancel={() => setImportVisible(false)}
        footer={null}
        width={520}
      >
        <div onClick={() => importInputRef.current?.click()} style={{ marginBottom: 12, cursor: 'pointer' }}>
          <Button icon={<IconImport />}>选择 inspection.json 文件</Button>
          <input
            ref={importInputRef}
            type="file"
            accept=".json,application/json"
            style={{ display: 'none' }}
            onChange={(e) => setImportFile(e.target.files?.[0] || null)}
          />
          {importFile && <span className="text-muted" style={{ marginLeft: 10 }}>{importFile.name}</span>}
        </div>
        <div style={{ marginBottom: 12 }}>
          <span style={{ marginRight: 8 }}>导入模式:</span>
          <Select
            value={importMode}
            onChange={v => setImportMode(v as any)}
            optionList={[
              { value: 'merge', label: '合并(推荐): 按index匹配更新action, 保留OrbRegistration' },
              { value: 'replace', label: '替换: 清空现有树后导入' },
              { value: 'append', label: '追加: 追加到根节点下' },
            ]}
            style={{ width: 400 }}
            size="small"
          />
        </div>
        <div className="text-muted" style={{ fontSize: 12, marginBottom: 12 }}>
          inspection.json 结构: {'{ "waypoint": [ { id, index, type, pose, action: [...] } ] }'}。
          每个 waypoint 生成 WaypointNode, 其下 action 生成 ActionNode, id 会保留对应。
        </div>
        <div className="flex gap-8" style={{ justifyContent: 'flex-end' }}>
          <Button onClick={() => setImportVisible(false)}>取消</Button>
          <Button theme="solid" type="primary" loading={importing} onClick={doImport}>导入</Button>
        </div>
      </Modal>

      {/* 右键菜单 (自定义, 定位到鼠标位置) */}
      {ctxMenu && (() => {
        const targets = getCtxTargetNodes()
        const hasChildren = targets.some((n) => n.children && n.children.length > 0)
        const multi = targets.length > 1
        return (
        <>
          <div
            style={{ position: 'fixed', inset: 0, zIndex: 1000 }}
            onClick={() => setCtxMenu(null)}
            onContextMenu={(e) => { e.preventDefault(); setCtxMenu(null) }}
          />
          <div
            ref={ctxMenuRef}
            className={`wt-ctx-menu${ctxMenuPos.flipSub ? ' wt-ctx-flip-sub' : ''}`}
            style={{ position: 'fixed', left: ctxMenuPos.x, top: ctxMenuPos.y, zIndex: 1001 }}
          >
            {multi && (
              <div className="wt-ctx-info">
                已选中 {targets.length} 个节点
              </div>
            )}
            {/* 展开 / 收起 (仅有子节点时显示) */}
            {hasChildren && (
              <>
                <div
                  className="wt-ctx-item"
                  onClick={() => { expandSubtreeMulti(targets); setCtxMenu(null) }}
                >
                  <IconExpand /> <span>{multi ? '展开所有子树' : '展开子树'}</span>
                </div>
                <div
                  className="wt-ctx-item"
                  onClick={() => { collapseNodeMulti(targets); setCtxMenu(null) }}
                >
                  <IconShrink /> <span>{multi ? '收起所有子树' : '收起子树'}</span>
                </div>
                <div className="wt-ctx-divider" />
              </>
            )}
            <div className="wt-ctx-item wt-ctx-submenu">
              <span style={{ flex: 1 }}>添加子节点</span>
              <IconChevronRight style={{ fontSize: 12, color: '#909399' }} />
              <div className="wt-ctx-submenu-list">
                {NODE_TYPES.map((t) => {
                  const SubIcon = t.icon
                  return (
                    <div
                      key={t.type}
                      className="wt-ctx-item"
                      onClick={() => { onAddChild(ctxMenu.node, t.type); setCtxMenu(null) }}
                    >
                      <span style={{ color: t.hex, display: 'inline-flex' }}><SubIcon /></span>
                      <span>{t.label}</span>
                    </div>
                  )
                })}
              </div>
            </div>
            <div className="wt-ctx-divider" />
            <div
              className="wt-ctx-item"
              onClick={() => { onCopy(targets, ctxMenu.parentId); setCtxMenu(null) }}
            >
              <IconCopy /> <span>{multi ? `复制 ${targets.length} 个节点` : '复制节点'}</span>
            </div>
            {ctxMenu.node.id !== 'root' && (
              <div
                className="wt-ctx-item"
                onClick={() => { onCut(targets); setCtxMenu(null) }}
              >
                <IconScissors /> <span>{multi ? `剪切 ${targets.length} 个节点` : '剪切节点'}</span>
              </div>
            )}
            {clipboard.length > 0 && ctxMenu.node.id !== 'root' && (
              <div
                className="wt-ctx-item"
                onClick={() => { onPasteBefore(ctxMenu.node); setCtxMenu(null) }}
              >
                <IconPasteIcon /> <span>粘贴到节点前面 ({clipboard.length})</span>
              </div>
            )}
            {ctxMenu.node.id !== 'root' && (
              <div
                className="wt-ctx-item"
                onClick={() => { onCreateGroup(targets); setCtxMenu(null) }}
              >
                <IconFolderOpen /> <span>{multi ? `归入分组 (${targets.length})` : '归入分组'}</span>
              </div>
            )}
            <div
              className="wt-ctx-item wt-danger"
              onClick={() => { onDeleteMulti(targets); setCtxMenu(null) }}
            >
              <IconDelete /> <span>{multi ? `删除 ${targets.length} 个节点` : '删除节点'}</span>
            </div>
            <div className="wt-ctx-divider" />
            <div
              className="wt-ctx-item"
              onClick={() => { setJsonViewer({ node: ctxMenu.node }); setCtxMenu(null) }}
            >
              <IconCode /> <span>查看 JSON 数据</span>
            </div>
          </div>
        </>
        )
      })()}

      {/* JSON 查看器 (Monaco editor) */}
      {jsonViewer && (
        <Modal
          visible={!!jsonViewer}
          title={`查看 ${nodeTypeLabel(jsonViewer.node.nodeType)} JSON`}
          onCancel={() => setJsonViewer(null)}
          width={800}
          footer={null}
        >
          <Editor
            height="calc(100vh - 200px)"
            language="json"
            value={JSON.stringify(jsonViewer.node, null, 2)}
            options={{ readOnly: true, minimap: { enabled: false } }}
          />
        </Modal>
      )}

      {/* ORB 抓拍弹窗 */}
      <CaptureRefImageDialog
        rid={rid}
        visible={captureDialog}
        onClose={() => setCaptureDialog(false)}
        onCaptured={handleCaptured}
      />

      <style>{`
        .wt-splitter { display: flex; gap: 0; align-items: stretch; }
        .wt-splitter-left { min-width: 200px; }
        .wt-splitter-right { min-width: 200px; }
        .wt-splitter-handle {
          width: 6px; cursor: col-resize; background: #e4e7ed; flex-shrink: 0;
          transition: background .15s; margin: 0 2px; border-radius: 3px;
        }
        .wt-splitter-handle:hover { background: #409eff; }
        .wt-splitter-handle:active { background: #337ecc; }
        .wt-tree { max-height: calc(100vh - 300px); overflow: auto; padding: 4px; }
        .wt-row {
          display: flex; align-items: center; gap: 6px;
          padding: 4px 8px; border-radius: 4px; cursor: pointer;
          user-select: none; font-size: 13px; transition: background .12s;
        }
        .wt-row:hover { background: #f5f7fa; }
        .wt-row.selected { background: #ecf5ff; }
        .wt-row.dragging { opacity: 0.4; }
        .wt-row.disabled { opacity: 0.5; }
        .wt-row.disabled .wt-name { color: #c0c4cc; text-decoration: line-through; }
        .wt-row.orb-highlight { background: #f0f9eb; }
        .wt-row.orb-highlight.selected { background: #e1f3d8; }
        .wt-row.orb-highlight .wt-name { color: #52c41a; font-weight: 600; }
        .wt-row.drop-before { border-top: 2px solid #409eff; }
        .wt-row.drop-after { border-bottom: 2px solid #409eff; }
        .wt-row.drop-inside { background: #d9ecff; border: 1px dashed #409eff; }
        .wt-toggle { display: inline-flex; width: 16px; height: 16px; align-items: center; justify-content: center; color: #909399; flex-shrink: 0; }
        .wt-icon { display: inline-flex; flex-shrink: 0; }
        .wt-name { flex: 1; overflow: hidden; text-overflow: ellipsis; white-space: nowrap; }
        .wt-sep { display: inline-block; width: 1px; height: 20px; background: #e4e7ed; margin: 0 4px; align-self: center; }
        .wt-inspector { max-height: calc(100vh - 300px); overflow: auto; padding-right: 4px; }
        .wt-grid { display: grid; grid-template-columns: 110px 1fr; row-gap: 8px; column-gap: 10px; align-items: center; }
        .wt-grid > *:nth-child(odd) { color: #606266; font-size: 13px; }
        .wt-grid .semi-inputnumber { width: 100%; }
        .wt-grid .semi-input-wrapper { width: 100%; }
        .wt-ctx-menu { background: #fff; border: 1px solid #e4e7ed; border-radius: 6px; box-shadow: 0 4px 16px rgba(0,0,0,.12); padding: 4px 0; min-width: 160px; font-size: 13px; }
        .wt-ctx-item { display: flex; align-items: center; gap: 8px; padding: 8px 16px; cursor: pointer; transition: background .12s; user-select: none; }
        .wt-ctx-item:hover { background: #f5f7fa; }
        .wt-ctx-item.wt-danger:hover { background: #fef0f0; color: #f56c6c; }
        .wt-ctx-info { padding: 6px 16px; font-size: 12px; color: #409eff; background: #ecf5ff; border-bottom: 1px solid #d9ecff; margin-bottom: 2px; }
        .wt-ctx-divider { height: 1px; background: #ebeef5; margin: 4px 0; }
        .wt-ctx-submenu { position: relative; }
        .wt-ctx-submenu-list { display: none; position: absolute; left: 100%; top: -4px; background: #fff; border: 1px solid #e4e7ed; border-radius: 6px; box-shadow: 0 4px 16px rgba(0,0,0,.12); padding: 4px 0; min-width: 200px; }
        .wt-ctx-submenu:hover .wt-ctx-submenu-list { display: block; }
        .wt-ctx-flip-sub .wt-ctx-submenu-list { left: auto; right: 100%; }
      `}</style>

      {/* 配准指标详情弹窗 */}
      {metricsModal && (
        <Modal
          title={
            <span>
              配准指标详情
              {metricsModal.m.converged && <Tag color="green" size="small" style={{ marginLeft: 8 }}>已收敛</Tag>}
            </span>
          }
          visible={metricsModal.visible}
          onCancel={() => setMetricsModal(null)}
          footer={null}
          width={800}
          bodyStyle={{ maxHeight: '70vh', overflow: 'auto' }}
        >
          <div style={{ fontSize: 13, marginBottom: 12, color: '#606266' }}>
            迭代记录 ({metricsModal.iters.length}/{metricsModal.m.max_iterations || '?'} 次, 阈值 {metricsModal.m.threshold_px || '?'}px)
          </div>
          {metricsModal.iters.map((it: any, i: number) => {
            const iterDir = metricsModal.matchingKey + '/' + it.iteration
            const iterImgs = (metricsModal.files || []).filter((f: string) =>
              f.startsWith(iterDir + '/') && (f.endsWith('.jpg') || f.endsWith('.png')))
            return (
            <div key={i} style={{
              marginBottom: 12, padding: '10px 12px', background: it.converged ? '#f6ffed' : '#fafafa',
              borderRadius: 6, border: `1px solid ${it.converged ? '#b7eb8f' : '#f0f0f0'}`,
              borderLeft: `3px solid ${it.converged ? '#52c41a' : '#1890ff'}`,
            }}>
              <div style={{ fontWeight: 600, fontSize: 13, color: it.converged ? '#52c41a' : '#333' }}>
                第{it.iteration}轮 {it.converged ? '✓ 收敛' : ''}
              </div>
              <div style={{ fontSize: 12, color: '#606266', marginTop: 4, lineHeight: 1.8 }}>
                X={it.x_offset_px?.toFixed(2) ?? '-'}px Y={it.y_offset_px?.toFixed(2) ?? '-'}px
                {' | '}匹配:{it.total_matches ?? '-'} 内点:{it.inlier_count ?? '-'}
                {it.move_distance_m != null && <> | 移动:{it.move_distance_m.toFixed(4)}m</>}
                {it.from && it.to && <> | ({it.from.x?.toFixed(4)} → {it.to.x?.toFixed(4)}, {it.from.y?.toFixed(4)} → {it.to.y?.toFixed(4)})</>}
                {it.pan_delta != null && <> | panΔ:{it.pan_delta.toFixed(2)}° tiltΔ:{it.tilt_delta?.toFixed(2)}°</>}
              </div>
              {/* 本轮过程图 */}
              {iterImgs.length > 0 && (
                <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(140px, 1fr))', gap: 8, marginTop: 8 }}>
                  {Object.entries(IMAGE_TITLES).map(([fname, title]) => {
                    const matched = iterImgs.find((f: string) => f.endsWith('/' + fname))
                    if (!matched) return null
                    const url = debugImageUrl(rid!, matched)
                    return (
                      <div key={fname} style={{ border: '1px solid #e8e8e8', borderRadius: 4, overflow: 'hidden', background: '#fafafa' }}>
                        <div style={{ height: 120, display: 'flex', alignItems: 'center', justifyContent: 'center', background: '#1e1e1e' }}>
                          <img src={url} alt={title}
                            style={{ maxHeight: 120, maxWidth: '100%', objectFit: 'contain', cursor: 'pointer' }}
                            onClick={() => window.open(url, '_blank')} />
                        </div>
                        <div style={{ padding: '3px 6px', fontSize: 10, color: '#909399', textAlign: 'center' }}>
                          {title}
                        </div>
                      </div>
                    )
                  })}
                </div>
              )}
            </div>
          )})}
        </Modal>
      )}
    </div>
  )
}
