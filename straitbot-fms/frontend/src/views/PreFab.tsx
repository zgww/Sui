import { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import {
  Banner, Button, Card, Empty, Input, Modal, Space, Spin, Tag, Toast, Tree,
} from '@douyinfe/semi-ui'
import {
  createDir, createFile, deleteDir, deleteFile, getNodeTypes, getTree, getTrees,
  moveEntry, reloadTrees, renameEntry, saveTree,
  NodeTypeInfo, TreeDetail, TreeSummary,
} from '../api/prefab'
import type { ReactNode } from 'react'
import InspectorForm from '../components/InspectorForm'
import { regenerateIds } from '../utils/inspectionBuild'
import { dirIconKey, fileDisplayName, fileRelPath } from '../utils/prefabDirLabel'
import { startDrag } from '../utils/splitter'
import {
  IconFolder, IconFile, IconComponent, IconMapPin, IconVideo, IconPulse,
  IconRoute, IconFlag, IconBranch, IconLink, IconBolt, IconCreditCard,
  IconImage, IconStar, IconCrop, IconSetting, IconCalendar, IconCalendarClock,
  IconShield, IconCamera, IconHourglass, IconFastForward, IconClock, IconEdit,
  IconBulb, IconLock, IconHistogram, IconHash, IconOrderedList, IconAlertTriangle,
  IconAlertCircle, IconUnlink, IconSearch, IconUser, IconBell, IconBox,
  IconFilter, IconCheckList, IconSave, IconForward, IconSendMsgStroked, IconMail,
} from '@douyinfe/semi-icons'

const SEP = '/'

function stateText(s?: string): string {
  if (s === 'active') return '运行中'
  if (s === 'error') return '错误'
  if (s === 'loaded') return '已加载'
  if (s === 'disabled') return '未激活'
  if (s === 'inactive') return '未激活'
  // **不在启动目录里**的 prefab：能被打开、能编辑，但程序启动时不会加载它
  if (s === '未加载') return '不在启动目录'
  return s || ''
}

function stateColor(s?: string): any {
  if (s === 'active') return 'green'
  if (s === 'error') return 'red'
  return 'grey'
}

/** 树节点上的小图标样式：中性灰、14px，和文字基线对齐 */
function treeIcon(children: ReactNode): ReactNode {
  return (
    <span style={{ display: 'inline-flex', alignItems: 'center', fontSize: 14,
      color: 'var(--semi-color-text-2)', flex: '0 0 auto' }}>
      {children}
    </span>
  )
}

/**
 * 三棵 prefab 树的节点类型 -> 图标（通用页节点树统一用）。
 * 三棵树的类名互不冲突，平铺一张表即可，按节点类型一眼分类；
 * 未登记的新类型回落通用组件图标，不至于空白。
 */
const NODE_TYPE_ICON: Record<string, ReactNode> = {
  // —— 航点树 ——
  GroupNode: <IconFolder />,
  WaypointNode: <IconMapPin />,
  ActionPointNode: <IconVideo />,
  MeasurePointNode: <IconPulse />,
  TrackNode: <IconRoute />,
  TrackEndpointNode: <IconFlag />,
  TrackControlNode: <IconBranch />,
  ClosePathNode: <IconLink />,
  ChargingPileNode: <IconBolt />,
  RfidCardNode: <IconCreditCard />,
  BackgroundImageNode: <IconImage />,
  SectionMarkNode: <IconFlag />,
  IconMarkNode: <IconStar />,
  DetectBoxNode: <IconCrop />,
  AlgorithmConfigNode: <IconSetting />,
  // —— 巡检计划树 ——
  InspectionPlanNode: <IconCalendar />,
  PlanGroupNode: <IconFolder />,
  WaypointSelectNode: <IconRoute />,
  PointSelectNode: <IconPulse />,
  DailyScheduleNode: <IconCalendarClock />,
  // —— 检测流程树：骨架 / 前处理 ——
  DetectPipelineNode: <IconShield />,
  DetectGroupNode: <IconFolder />,
  FrameSourceNode: <IconCamera />,
  ThrottleNode: <IconHourglass />,
  FrameSkipNode: <IconFastForward />,
  RoiFilterNode: <IconCrop />,
  TimeWindowNode: <IconClock />,
  ImagePreprocessNode: <IconEdit />,
  // 状态识别
  SwitchStateNode: <IconSetting />,
  IndicatorLightNode: <IconBulb />,
  CabinetDoorNode: <IconLock />,
  ValveStateNode: <IconBranch />,
  // 表计读数
  MeterPointerNode: <IconHistogram />,
  MeterDigitalNode: <IconHash />,
  MeterLevelNode: <IconPulse />,
  CounterReadNode: <IconOrderedList />,
  // 缺陷检测
  InsulatorDamageNode: <IconAlertTriangle />,
  EquipmentRustNode: <IconAlertCircle />,
  CableDamageNode: <IconUnlink />,
  WaterLeakNode: <IconSearch />,
  // 安全告警
  PersonIntrusionNode: <IconUser />,
  SmokeFireNode: <IconBell />,
  ForeignObjectNode: <IconBox />,
  HelmetCheckNode: <IconShield />,
  // 后处理 / 外发
  ResultFilterNode: <IconFilter />,
  ConfirmNode: <IconCheckList />,
  EvidenceNode: <IconSave />,
  AlarmNode: <IconBell />,
  NumericAlarmNode: <IconPulse />,
  RangeAlarmNode: <IconHistogram />,
  ForwardNode: <IconForward />,
  SmsNotifyNode: <IconSendMsgStroked />,
  EmailNotifyNode: <IconMail />,
}

function nodeIcon(type?: string): ReactNode {
  return treeIcon(NODE_TYPE_ICON[type || ''] ?? <IconComponent />)
}

/**
 * prefab 目录（`data/prefabs` 下的一级子目录与「启动」）-> 图标。
 * 认目录只看相对路径的第一段（`waypoint/楼层1` 也用航点树的图标）；
 * 查表逻辑在 `utils/prefabDirLabel.ts`（纯函数，有回归脚本），
 * 这里只把键映射成图标组件。
 */
const DIR_ICON_BY_KEY: Record<string, ReactNode> = {
  bolt: <IconBolt />,
  'map-pin': <IconMapPin />,
  calendar: <IconCalendar />,
  shield: <IconShield />,
  folder: <IconFolder />,
}

function dirIcon(rel: string): ReactNode {
  return DIR_ICON_BY_KEY[dirIconKey(rel)] ?? <IconFolder />
}

/** 把（spec 合并状态后的）节点树转成 Semi Tree 数据，key = 节点路径 */
function toTreeData(status: any, path = 'root'): any[] {
  const st = status?._state
  // 节点名称在 properties.name（与右侧检视器编辑的是同一个字段）；
  // 没填名称时才回落到类型名，顶层 name 仅作旧数据兜底
  const displayName = status?.properties?.name || status?.name || status?.type || '?'
  const node: any = {
    key: path,
    value: path,
    label: (
      <span className="pf3-label" title={status?.type ? `${displayName} · ${status.type}` : displayName}>
        {nodeIcon(status?.type)}
        <span className="pf3-name">{displayName}</span>
        {st ? <Tag size="small" color={stateColor(st)}>{stateText(st)}</Tag> : null}
      </span>
    ),
  }
  if (Array.isArray(status?.children) && status.children.length) {
    node.children = status.children.map((c: any, i: number) =>
      toTreeData(c, `${path}${SEP}children${SEP}${i}`)[0])
  }
  return [node]
}

/** 把运行状态(_state/_error)合并进 spec 节点，使中栏树结构随编辑实时变化 */
function mergeStatus(specNode: any, statusNode: any): any {
  if (!specNode) return statusNode
  const out: any = { ...specNode }
  if (statusNode) {
    if (statusNode._state !== undefined) out._state = statusNode._state
    if (statusNode._error !== undefined) out._error = statusNode._error
  }
  if (Array.isArray(specNode.children)) {
    out.children = specNode.children.map((c: any, i: number) =>
      mergeStatus(c, statusNode?.children?.[i]))
  }
  return out
}

function getNodeByPath(spec: any, path: string): any {
  const parts = path.split(SEP)
  let cur = spec
  for (const p of parts) {
    if (cur === undefined || cur === null) return undefined
    cur = cur[p]
  }
  return cur
}

/** 按路径从 spec 移除节点（root 不可移除） */
function removeNodeByPath(specRoot: any, path: string): boolean {
  const parts = path.split(SEP)
  if (parts.length < 3) return false
  const parentPath = parts.slice(0, -2).join(SEP)
  const idx = Number(parts[parts.length - 1])
  const parent = getNodeByPath(specRoot, parentPath)
  if (parent?.children && idx >= 0 && idx < parent.children.length) {
    parent.children.splice(idx, 1)
    return true
  }
  return false
}

/** 在 spec 内移动节点：pos -1 前 / 0 内 / 1 后 */
function moveNodeInSpec(specRoot: any, dragPath: string, targetPath: string, pos: number): boolean {
  if (dragPath === targetPath) return false
  if (targetPath.startsWith(dragPath + SEP)) return false // 不能移到自己子孙

  const dp = dragPath.split(SEP)
  const dragParentPath = dp.slice(0, -2).join(SEP)
  const dragIdx = Number(dp[dp.length - 1])
  const tp = targetPath.split(SEP)
  let targetParentPath = tp.slice(0, -2).join(SEP)
  let targetIdx = Number(tp[tp.length - 1])

  const dragParent = getNodeByPath(specRoot, dragParentPath)
  if (!dragParent?.children || dragIdx < 0 || dragIdx >= dragParent.children.length) return false
  const [moved] = dragParent.children.splice(dragIdx, 1)

  // 同父且 drag 在 target 前：移除后 target 索引前移
  if (dragParentPath === targetParentPath && dragIdx < targetIdx) targetIdx -= 1

  if (pos === 0) {
    // 用调整后的 targetIdx 重建完整路径（splice 已移除 drag 节点，绝对索引会失效）
    const targetPath2 = `${targetParentPath}${SEP}children${SEP}${targetIdx}`
    const target = getNodeByPath(specRoot, targetPath2)
    if (!target) { dragParent.children.splice(dragIdx, 0, moved); return false }
    target.children = target.children || []
    target.children.unshift(moved)
  } else {
    const tParent = getNodeByPath(specRoot, targetParentPath)
    if (!tParent?.children) { dragParent.children.splice(dragIdx, 0, moved); return false }
    const at = Math.max(0, pos === -1 ? targetIdx : targetIdx + 1)
    tParent.children.splice(at, 0, moved)
  }
  return true
}

function defaultsFrom(schema: any): Record<string, any> {
  const out: Record<string, any> = {}
  const props = schema?.properties || {}
  for (const [k, d] of Object.entries<any>(props)) {
    if (k === 'type' || k === 'children') continue
    if ('default' in d) out[k] = d.default
  }
  return out
}

/** 目录树：目录节点 + prefab 文件叶子 */
interface DirNode {
  dirs: Record<string, DirNode>
  files: TreeSummary[]
}

function buildDirTree(dirList: string[], list: TreeSummary[]): DirNode {
  const root: DirNode = { dirs: {}, files: [] }
  // 先建真实目录（含空目录），再挂 prefab 文件
  for (const d of dirList) {
    if (!d) continue
    const parts = d.split(SEP)
    let cur = root
    for (const p of parts) {
      if (!cur.dirs[p]) cur.dirs[p] = { dirs: {}, files: [] }
      cur = cur.dirs[p]
    }
  }
  for (const t of list) {
    const parts = fileRelPath(t).split(SEP)
    parts.pop()
    let cur = root
    for (const p of parts) {
      if (!p) continue
      if (!cur.dirs[p]) cur.dirs[p] = { dirs: {}, files: [] }
      cur = cur.dirs[p]
    }
    cur.files.push(t)
  }
  return root
}

/** 节点 value 编码：目录 dir/<rel>，文件 file/<rel>，根 dir/ */
function dirToTreeData(dir: DirNode, dirRel: string): any[] {
  const nodes: any[] = []
  for (const [name, sub] of Object.entries(dir.dirs).sort(([a], [b]) => a.localeCompare(b))) {
    const rel = dirRel ? `${dirRel}${SEP}${name}` : name
    const folderIcon = dirIcon(rel)
    nodes.push({
      key: `dir${SEP}${rel}`, value: `dir${SEP}${rel}`,
      label: (
        <span className="pf3-label" title={rel}>
          {treeIcon(folderIcon)}
          <span className="pf3-name">{name}</span>
        </span>
      ),
      children: dirToTreeData(sub, rel),
    })
  }
  for (const f of [...dir.files].sort((a, b) => a.name.localeCompare(b.name))) {
    const rel = fileRelPath(f)
    // 文件名显示**全名**（含 .prefab.json），和磁盘上的实际文件名一致——
    // 目录下同名不同后缀的文件（如 `a.json` 与 `a.prefab.json`）靠后缀区分，
    // 裁掉后缀会出现两行一模一样的 "a"，看不出在编辑哪个。
    const fname = fileDisplayName(rel)
    nodes.push({
      key: `file${SEP}${rel}`,
      label: (
        <span className="pf3-label" title={rel}>
          {treeIcon(<IconFile />)}
          {/* 全名可能很长，靠 CSS 省略；title 给完整相对路径 */}
          <span className="pf3-name">{fname}</span>
          <Tag size="small" color={stateColor(f.state)}>{stateText(f.state)}</Tag>
        </span>
      ),
      value: `file${SEP}${rel}`,
    })
  }
  return nodes
}

/** 树扁平化（用于 shift 区间选择） */
function flattenTree(nodes: any[]): { key: string; value: string }[] {
  const out: { key: string; value: string }[] = []
  const walk = (list: any[]) => {
    for (const n of list) {
      out.push({ key: n.key, value: n.value })
      if (n.children?.length) walk(n.children)
    }
  }
  walk(nodes)
  return out
}

/** 节点类型继承树：NodeBase(根) -> 中间基类(如 CompositeNode) -> 各注册类型叶子 */
function buildTypeTree(types: Record<string, NodeTypeInfo>): any[] {
  const bases = new Set<string>()
  for (const info of Object.values(types)) {
    if (info.base && info.base !== 'NodeBase') bases.add(info.base)
  }
  const root: any = {
    key: 'NodeBase',
    value: 'NodeBase',
    label: (
      <span className="pf3-label" style={{ fontWeight: 600 }}>
        {treeIcon(<IconComponent />)}
        NodeBase <span style={{ fontWeight: 400, color: 'var(--semi-color-text-2)' }}>· 全部节点类型</span>
      </span>
    ),
    children: [] as any[],
  }
  for (const b of [...bases].sort()) {
    root.children.push({
      key: `base/${b}`, value: b,
      label: (
        <span className="pf3-label">
          {treeIcon(<IconFolder />)}
          <span className="pf3-name">{b}</span>
        </span>
      ),
      children: [] as any[],
    })
  }
  for (const name of Object.keys(types).sort()) {
    const info = types[name]
    const leaf: any = {
      key: `type/${name}`,
      value: name,
      typeName: name,
      label: (
        <span className="pf3-label" title={info.description || name}>
          {nodeIcon(name)}
          <span style={{ display: 'flex', flexDirection: 'column', gap: 2, minWidth: 0 }}>
            <span className="pf3-name" style={{ fontWeight: 500 }}>{name}</span>
            {info.description ? (
              <span style={{
                fontSize: 12, color: 'var(--semi-color-text-2)',
                overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap',
              }}>{info.description}</span>
            ) : null}
          </span>
        </span>
      ),
    }
    const base = info.base && info.base !== 'NodeBase' ? info.base : null
    if (base) {
      const parent = root.children.find((c: any) => c.key === `base/${base}`)
      if (parent) parent.children.push(leaf)
      else root.children.push(leaf)
    } else {
      root.children.push(leaf)
    }
  }
  return [root]
}

/** 按关键字过滤类型树：命中叶子或其子树有命中则保留祖先链 */
function filterTypeTree(nodes: any[], kw: string): any[] {
  const out: any[] = []
  for (const n of nodes) {
    const hit = (n.typeName || '').toLowerCase().includes(kw)
      || (n.desc || '').toLowerCase().includes(kw)
    const children = n.children?.length ? filterTypeTree(n.children, kw) : []
    if (hit || children.length) {
      out.push({ ...n, children: children.length ? children : undefined })
    }
  }
  return out
}

interface CtxMenu {
  x: number
  y: number
  kind: 'blank' | 'dir' | 'file' | 'node' | 'nodeBlank'
  target?: string
}

interface DialogState {
  mode: 'newDir' | 'newFile' | 'rename'
  parentRel: string
  relPath: string
  value: string
  title: string
  placeholder: string
}

const MENU_STYLE: React.CSSProperties = {
  position: 'fixed', minWidth: 168, background: '#fff',
  border: '1px solid var(--semi-color-border)', borderRadius: 6,
  boxShadow: '0 6px 20px rgba(0,0,0,.14)', padding: 4, zIndex: 1001,
  fontSize: 13,
}

export default function PreFab() {
  const [loading, setLoading] = useState(true)
  const [nodeTypes, setNodeTypes] = useState<Record<string, NodeTypeInfo>>({})
  const [trees, setTrees] = useState<TreeSummary[]>([])
  const [dirs, setDirs] = useState<string[]>([])
  const [loadErrors, setLoadErrors] = useState<string[]>([])
  const [selectedName, setSelectedName] = useState<string>('')
  const [detail, setDetail] = useState<TreeDetail | null>(null)
  const [spec, _setSpec] = useState<Record<string, any> | null>(null)
  const setSpec = (v: any) => _setSpec(v)
  const [selectedPath, setSelectedPath] = useState('root')
  const [saving, setSaving] = useState(false)

  /* 三栏布局：目录 / 节点树 / 检视器，两条分隔条可拖。
     中间的节点树是"剩下的"（flex:1），拖左右两栏就等于在改三栏的宽窄。 */
  const [dirWidth, setDirWidth] = useState(400)
  const [inspectorWidth, setInspectorWidth] = useState(600)

  /* ---- 多选与右键菜单 ---- */
  const [dirSel, setDirSel] = useState<Set<string>>(new Set())
  const [nodeSel, setNodeSel] = useState<Set<string>>(new Set())
  const dirAnchor = useRef('')
  const nodeAnchor = useRef('')
  const mods = useRef({ shift: false, ctrl: false })
  const [ctxMenu, setCtxMenu] = useState<CtxMenu | null>(null)
  const [dialog, setDialog] = useState<DialogState | null>(null)
  const [addDialog, setAddDialog] = useState<{
    targetPath: string
    /** before / after：贴着目标节点插到同一层；不传则挂成目标的子节点 */
    position?: 'before' | 'after'
  } | null>(null)
  const [addType, setAddType] = useState<string | undefined>(undefined)
  const [addKeyword, setAddKeyword] = useState('')
  const [clipboard, setClipboard] = useState<{
    mode: 'copy' | 'cut'
    nodes: Record<string, any>[]
    fromTree: string
  } | null>(null)

  useEffect(() => {
    const sync = (e: KeyboardEvent) => {
      mods.current.shift = e.shiftKey
      mods.current.ctrl = e.ctrlKey || e.metaKey
    }
    const clear = () => { mods.current.shift = false; mods.current.ctrl = false }
    window.addEventListener('keydown', sync)
    window.addEventListener('keyup', sync)
    window.addEventListener('blur', clear)
    return () => {
      window.removeEventListener('keydown', sync)
      window.removeEventListener('keyup', sync)
      window.removeEventListener('blur', clear)
    }
  }, [])

  const refreshTrees = useCallback(async () => {
    const { data } = await getTrees()
    setTrees(data.trees)
    setDirs(data.dirs || [])
    setLoadErrors(data.errors)
    return data.trees
  }, [])

  const loadSeq = useRef(0)
  const loadTree = useCallback(async (name: string) => {
    const seq = ++loadSeq.current
    const { data } = await getTree(name)
    if (seq !== loadSeq.current) return // 过期响应：期间用户已切换/编辑，丢弃
    setDetail(data)
    setSpec(JSON.parse(JSON.stringify(data.spec)))
    setSelectedPath('root')
    setNodeSel(new Set())
  }, [])

  useEffect(() => {
    (async () => {
      try {
        const [t, types] = await Promise.all([refreshTrees(), getNodeTypes()])
        setNodeTypes(types.data)
        if (t.length > 0) {
          setSelectedName(t[0].name)
          await loadTree(t[0].name)
        }
      } catch { /* http 拦截器已提示 */ }
      finally { setLoading(false) }
    })()
  }, [refreshTrees, loadTree])

  /* ---- 目录树数据 ---- */
  const dirTree = useMemo(() => {
    if (trees.length === 0 && dirs.length === 0) return []
    const root = buildDirTree(dirs, trees)
    return [{
      key: 'dir/',
      label: <span style={{ fontWeight: 600 }}>prefabs/</span>,
      value: 'dir/',
      children: dirToTreeData(root, ''),
    }]
  }, [trees, dirs])

  const dirFlat = useMemo(() => flattenTree(dirTree), [dirTree])

  /** value(file/<rel>) -> TreeSummary */
  const treeByRel = useCallback((rel: string) => trees.find((t) => fileRelPath(t) === rel), [trees])

  const onSelectDir = (key: string) => {
    const m = mods.current
    if (m.ctrl) {
      setDirSel((prev) => {
        const n = new Set(prev)
        if (n.has(key)) n.delete(key); else n.add(key)
        return n
      })
    } else if (m.shift && dirAnchor.current && dirAnchor.current !== key) {
      const ks = dirFlat.map((d) => d.key)
      const a = ks.indexOf(dirAnchor.current)
      const b = ks.indexOf(key)
      if (a >= 0 && b >= 0) {
        const [lo, hi] = a <= b ? [a, b] : [b, a]
        setDirSel(new Set(ks.slice(lo, hi + 1)))
      }
      dirAnchor.current = key
    } else {
      setDirSel(new Set([key]))
      dirAnchor.current = key
    }
    // 单击 prefab 文件 -> 加载详情
    if (key.startsWith(`file${SEP}`)) {
      const t = treeByRel(key.slice(`file${SEP}`.length))
      if (t) { setSelectedName(t.name); loadTree(t.name) }
    }
  }

  const onDirCtx = (e: React.MouseEvent, node: any) => {
    e.preventDefault()
    const key = (node?.key || node?.value || '') as string
    if (key) {
      if (!dirSel.has(key)) { setDirSel(new Set([key])); dirAnchor.current = key }
      setCtxMenu({
        x: e.clientX, y: e.clientY,
        kind: key.startsWith(`dir${SEP}`) ? 'dir' : 'file',
        target: key,
      })
    } else {
      setCtxMenu({ x: e.clientX, y: e.clientY, kind: 'blank' })
    }
  }

  const confirmDeleteEntry = (kind: 'file' | 'dir', rel: string) => {
    Modal.confirm({
      title: kind === 'dir' ? '删除目录' : '删除 prefab',
      content: kind === 'dir'
        ? `将递归删除目录 ${rel} 及其中的全部 prefab，此操作不可恢复。`
        : `确定删除 ${rel} ？`,
      okType: 'danger',
      onOk: async () => {
        try {
          if (kind === 'dir') await deleteDir(rel); else await deleteFile(rel)
          Toast.success('已删除')
          await afterFsChange()
        } catch { /* 拦截器已提示 */ }
      },
    })
  }

  const doDialogOk = async () => {
    if (!dialog) return
    const v = dialog.value.trim()
    if (!v) { Toast.warning('名称不能为空'); return }
    try {
      if (dialog.mode === 'newDir') {
        const parent = dialog.parentRel ? `${dialog.parentRel}${SEP}` : ''
        await createDir(`${parent}${v}`)
        Toast.success('目录已创建')
      } else if (dialog.mode === 'newFile') {
        const parent = dialog.parentRel ? `${dialog.parentRel}${SEP}` : ''
        const fileRel = `${parent}${v.replace(/\.prefab\.json$/i, '')}.prefab.json`
        const { data } = await createFile(fileRel)
        const name = fileRel.split(SEP).pop()!.replace(/\.prefab\.json$/i, '')
        Toast.success('prefab 已创建')
        setDialog(null)
        await afterFsChange()
        if (data.errors?.length) { Toast.error(data.errors.join('; ')); return }
        setSelectedName(name)
        await loadTree(name)
        const rel = fileRel
        setDirSel(new Set([`file${SEP}${rel}`]))
        return
      } else {
        await renameEntry(dialog.relPath, v)
        Toast.success('已重命名')
      }
      setDialog(null)
      await afterFsChange()
    } catch { /* 拦截器已提示 */ }
  }

  const afterFsChange = async () => {
    const t = await refreshTrees()
    if (selectedName && !t.find((x) => x.name === selectedName)) {
      setSelectedName('')
      setDetail(null)
      setSpec(null)
      setDirSel(new Set())
    }
  }

  /** 拖拽移动目录/文件 */
  const onDirDrop = async (props: any) => {
    const dragVal: string = props.dragNode?.key || props.dragNode?.value || ''
    const targetVal: string = props.node?.key || props.node?.value || ''
    const pos: number = props.dropPosition
    if (!dragVal || !targetVal || dragVal === targetVal) return

    // Semi 的 dropPosition 是“相对偏移 + 目标索引”的实际插入位置，用目标 eventKey 的末段索引还原相对 -1/0/1
    const evKey: string = props.node?.eventKey || ''
    const tIdx = Number(evKey.split('-').pop() || '0')
    const relPos = pos - tIdx

    const dragRel = dragVal.startsWith(`file${SEP}`) ? dragVal.slice(`file${SEP}`.length) : dragVal.slice(`dir${SEP}`.length)

    let destDir: string
    if (relPos === 0) {
      if (targetVal === `dir${SEP}`) destDir = ''
      else if (targetVal.startsWith(`dir${SEP}`)) destDir = targetVal.slice(`dir${SEP}`.length)
      else return // 文件不可作为容器
    } else {
      const tRel = targetVal.startsWith(`file${SEP}`)
        ? targetVal.slice(`file${SEP}`.length)
        : targetVal.slice(`dir${SEP}`.length)
      const parts = tRel.split(SEP)
      parts.pop()
      destDir = parts.join(SEP)
    }
    if (destDir === dragRel || (destDir.startsWith(dragRel + SEP))) {
      Toast.warning('不能移动到自身或其子目录')
      return
    }
    try {
      await moveEntry(dragRel, destDir)
      Toast.success(`已移动到 ${destDir || '(根目录)'}`)
      await afterFsChange()
    } catch { /* 拦截器已提示 */ }
  }

  /* ---- 节点树数据（spec 合并运行状态） ---- */
  const treeData = useMemo(() => {
    if (!spec?.root) return []
    return toTreeData(mergeStatus(spec.root, detail?.status_tree))
  }, [spec, detail])

  const nodeFlat = useMemo(() => flattenTree(treeData), [treeData])

  const selectedNode = useMemo(() => {
    if (!spec) return null
    return getNodeByPath(spec, selectedPath)
  }, [spec, selectedPath])

  const selectedStatus = useMemo(() => {
    if (!detail?.status_tree) return null
    return getNodeByPath(detail.status_tree, selectedPath)
  }, [detail, selectedPath])

  const selectedSchema = useMemo(() => {
    if (!selectedNode?.type) return null
    return nodeTypes[selectedNode.type]?.schema || null
  }, [selectedNode, nodeTypes])

  const updateProps = (patch: Record<string, any>) => {
    if (!spec) return
    const next = JSON.parse(JSON.stringify(spec))
    const node = getNodeByPath(next, selectedPath)
    if (!node) return
    node.properties = { ...(node.properties || {}), ...patch }
    setSpec(next)
  }

  /**
   * 添加子节点。
   *
   * `position` 为 'before' / 'after' 时是**同级插入**：贴着目标节点插到它的
   * 前 / 后（规则与航点树编排页一致：before = 目标下标，after = 目标下标 + 1）。
   * 不给位置才是"挂成目标的子节点"。
   */
  /**
   * 打开"添加子节点"对话框。
   * 带 position 时是同级插入，默认把类型预置成目标自身类型（同层插同类最常用）。
   */
  const openAddDialog = (targetPath: string, position?: 'before' | 'after') => {
    const sameType = position && targetPath !== 'root'
      ? getNodeByPath(spec, targetPath)?.type : undefined
    setAddType(sameType)
    setAddKeyword('')
    setAddDialog({ targetPath, position })
  }

  const addChild = (targetPath: string, type?: string, position?: 'before' | 'after') => {
    if (!spec) return
    const t = type || addType
    if (!t) return
    const next = JSON.parse(JSON.stringify(spec))
    const created = { type: t, properties: defaultsFrom(nodeTypes[t]?.schema) }

    if (position && targetPath !== 'root') {
      const parentPath = targetPath.split(SEP).slice(0, -2).join(SEP)
      const idx = Number(targetPath.split(SEP).pop())
      const parent = getNodeByPath(next, parentPath)
      if (!parent || !Number.isInteger(idx)) { Toast.warning('无法确定插入位置'); return }
      parent.children = parent.children || []
      const at = Math.min(position === 'before' ? idx : idx + 1, parent.children.length)
      parent.children.splice(at, 0, created)
      setSpec(next)
      setSelectedPath(`${parentPath}${SEP}children${SEP}${at}`)
      return
    }

    const node = getNodeByPath(next, targetPath)
    if (!node) return
    node.children = node.children || []
    node.children.push(created)
    setSpec(next)
  }

  const deleteNode = () => {
    if (!spec) return
    const parts = selectedPath.split(SEP)
    if (parts.length < 3) { Toast.warning('根节点不可删除'); return }
    const parentPath = parts.slice(0, -2).join(SEP)
    const idx = Number(parts[parts.length - 1])
    const next = JSON.parse(JSON.stringify(spec))
    const parent = getNodeByPath(next, parentPath)
    if (parent?.children) {
      parent.children.splice(idx, 1)
      setSpec(next)
      setSelectedPath(parentPath)
    }
  }

  /* ---- 节点树多选 / 右键 / 拖拽 ---- */
  const onNodeSelect = (key: string) => {
    const m = mods.current
    if (m.ctrl) {
      setNodeSel((prev) => {
        const n = new Set(prev)
        if (n.has(key)) n.delete(key); else n.add(key)
        return n
      })
    } else if (m.shift && nodeAnchor.current && nodeAnchor.current !== key) {
      const ks = nodeFlat.map((d) => d.key)
      const a = ks.indexOf(nodeAnchor.current)
      const b = ks.indexOf(key)
      if (a >= 0 && b >= 0) {
        const [lo, hi] = a <= b ? [a, b] : [b, a]
        setNodeSel(new Set(ks.slice(lo, hi + 1)))
      }
      nodeAnchor.current = key
    } else {
      setNodeSel(new Set([key]))
      nodeAnchor.current = key
    }
    setSelectedPath(key)
  }

  const onNodeCtx = (e: React.MouseEvent, node: any) => {
    e.preventDefault()
    const key = (node?.key || node?.value || 'root') as string
    if (!nodeSel.has(key)) setNodeSel(new Set([key]))
    setCtxMenu({ x: e.clientX, y: e.clientY, kind: key === 'root' ? 'nodeBlank' : 'node', target: key })
  }

  const copyNodes = () => {
    if (nodeSel.size === 0 || !spec) { Toast.warning('请先选中节点'); return }
    const nodes = [...nodeSel]
      .map((p) => getNodeByPath(spec, p))
      .filter(Boolean)
      .map((n) => JSON.parse(JSON.stringify(n)))
    if (!nodes.length) return
    setClipboard({ mode: 'copy', nodes, fromTree: selectedName })
    Toast.success(`已复制 ${nodes.length} 个节点`)
  }

  const cutNodes = () => {
    if (nodeSel.size === 0 || !spec) { Toast.warning('请先选中节点'); return }
    if ([...nodeSel].includes('root')) { Toast.warning('根节点不可剪切'); return }
    const nodes = [...nodeSel]
      .map((p) => getNodeByPath(spec, p))
      .filter(Boolean)
      .map((n) => JSON.parse(JSON.stringify(n)))
    if (!nodes.length) return
    const next = JSON.parse(JSON.stringify(spec))
    for (const p of nodeSel) removeNodeByPath(next, p)
    setSpec(next)
    if (nodeSel.has(selectedPath)) setSelectedPath('root')
    setNodeSel(new Set())
    setClipboard({ mode: 'cut', nodes, fromTree: selectedName })
    Toast.success(`已剪切 ${nodes.length} 个节点，可在当前树内粘贴`)
  }

  const pasteTo = (targetPath: string) => {
    if (!clipboard || !spec) return
    if (clipboard.mode === 'cut' && clipboard.fromTree !== selectedName) {
      setClipboard({ ...clipboard, mode: 'copy' })
      Toast.info('跨树粘贴，按复制处理（原树节点保留）')
    }
    const next = JSON.parse(JSON.stringify(spec))
    const target = getNodeByPath(next, targetPath)
    if (!target) { Toast.error('目标节点不存在'); return }
    const clones = clipboard.nodes.map((n) => JSON.parse(JSON.stringify(n)))
    /* 与航点树页同规则：粘贴件必须换掉业务 id（航点/动作/测点），
       否则复制出来的两处指向同一航点，下发后分不清走到了哪一份。
       这里是通用 prefab，树里未必有这几类节点——没有就什么都不做。 */
    let fresh = 0
    for (const c of clones) fresh += regenerateIds(c)
    target.children = target.children || []
    target.children.push(...clones)
    setSpec(next)
    const count = clones.length
    setNodeSel(new Set())
    if (clipboard.mode === 'cut') setClipboard(null)
    Toast.success(
      fresh ? `已粘贴 ${count} 个节点（重新生成 ${fresh} 个 id）` : `已粘贴 ${count} 个节点`,
    )
  }

  const confirmDeleteNodes = () => {
    const targets = [...nodeSel]
    if (!targets.length || targets.includes('root')) { Toast.warning('根节点不可删除'); return }
    Modal.confirm({
      title: `删除 ${targets.length} 个节点`,
      content: '删除后点击「保存」才落盘生效。确定删除？',
      okType: 'danger',
      onOk: () => {
        if (!spec) return
        const next = JSON.parse(JSON.stringify(spec))
        for (const p of targets) removeNodeByPath(next, p)
        setSpec(next)
        if (targets.includes(selectedPath)) setSelectedPath('root')
        setNodeSel(new Set())
        Toast.success(`已删除 ${targets.length} 个节点`)
      },
    })
  }

  const onNodeDrop = (props: any) => {
    if (!spec) return
    const dragPath: string = props.dragNode?.key || ''
    const targetPath: string = props.node?.key || ''
    const pos: number = props.dropPosition
    if (!dragPath || !targetPath) return
    // Semi 的 dropPosition 是“相对偏移 + 目标索引”的实际插入位置，还原为相对 -1/0/1
    const tIdx = Number(targetPath.split(SEP).pop() || '0')
    const relPos = pos - tIdx
    const next = JSON.parse(JSON.stringify(spec))
    if (moveNodeInSpec(next, dragPath, targetPath, relPos)) {
      setSpec(next)
      Toast.success('已移动节点，点击「保存」落盘生效')
    } else {
      Toast.warning('无法移动到该位置（不能移到自身/子孙）')
    }
  }

  /* ---- 通用右键菜单 ---- */
  const buildMenuItems = (): {
    label?: string; danger?: boolean; disabled?: boolean; divider?: boolean; onClick?: () => void
  }[] => {
    if (!ctxMenu) return []
    const k = ctxMenu.kind
    const t = ctxMenu.target || ''
    if (k === 'blank' || k === 'dir') {
      const parentRel = k === 'dir' ? t.slice(`dir${SEP}`.length) : ''
      const items: any[] = [
        { label: '新建目录', onClick: () => setDialog({ mode: 'newDir', parentRel, relPath: '', value: '', title: '新建目录', placeholder: '目录名（可用 / 嵌套）' }) },
        { label: '新建 prefab 文件', onClick: () => setDialog({ mode: 'newFile', parentRel, relPath: '', value: '', title: '新建 prefab 文件', placeholder: '文件名（自动补 .prefab.json）' }) },
      ]
      if (k === 'dir') {
        items.push({ divider: true })
        items.push({
          label: '重命名',
          onClick: () => setDialog({
            mode: 'rename', parentRel: '', relPath: t.slice(`dir${SEP}`.length),
            value: t.split(SEP).pop()!, title: '重命名目录', placeholder: '新目录名',
          }),
        })
        items.push({ divider: true })
        items.push({
          label: '删除', danger: true,
          onClick: () => confirmDeleteEntry('dir', t.slice(`dir${SEP}`.length)),
        })
      }
      return items
    }
    if (k === 'file') {
      const rel = t.slice(`file${SEP}`.length)
      const curName = rel.split(SEP).pop()!
      return [
        { label: '重命名', onClick: () => setDialog({ mode: 'rename', parentRel: '', relPath: rel, value: curName, title: '重命名 prefab', placeholder: '新文件名（含 .prefab.json）' }) },
        { divider: true },
        { label: '删除', danger: true, onClick: () => confirmDeleteEntry('file', rel) },
      ]
    }
    if (k === 'node' || k === 'nodeBlank') {
      const p = t || 'root'
      const items: any[] = []
      items.push({
        label: '添加子节点',
        disabled: p === 'root' ? false : false,
        onClick: () => openAddDialog(p),
      })
      // 前 / 后：与航点树编排页同一条规则——贴着目标插到同一层（root 没有"前后"）
      if (p !== 'root') {
        items.push({ label: '在前添加子节点', onClick: () => openAddDialog(p, 'before') })
        items.push({ label: '在后添加子节点', onClick: () => openAddDialog(p, 'after') })
      }
      items.push({ divider: true })
      items.push({ label: '复制', onClick: copyNodes })
      items.push({ label: '剪切', onClick: cutNodes })
      items.push({ label: '粘贴', disabled: !clipboard, onClick: () => pasteTo(p) })
      if (p !== 'root') {
        items.push({ divider: true })
        items.push({ label: '删除', danger: true, onClick: confirmDeleteNodes })
      }
      return items
    }
    return []
  }

  const doSave = async () => {
    if (!spec || !selectedName) return
    setSaving(true)
    try {
      const { data } = await saveTree(selectedName, spec)
      if (data.errors.length > 0) {
        Toast.error(`保存成功但重载有错误: ${data.errors.join('; ')}`)
      } else {
        Toast.success('已保存并热重载')
      }
      await refreshTrees()
      await loadTree(selectedName)
    } catch { /* 拦截器已提示 */ }
    finally { setSaving(false) }
  }

  const doReload = async () => {
    try {
      const { data } = await reloadTrees()
      if (data.errors.length > 0) Toast.error(`重载有错误: ${data.errors.join('; ')}`)
      else Toast.success('已重载全部 prefab')
      const t = await refreshTrees()
      if (t.length > 0 && t.find((x) => x.name === selectedName)) await loadTree(selectedName)
    } catch { /* 拦截器已提示 */ }
  }

  const typeTree = useMemo(() => buildTypeTree(nodeTypes), [nodeTypes])

  const typeTreeFiltered = useMemo(() => {
    const kw = addKeyword.trim().toLowerCase()
    if (!kw) return typeTree
    return filterTypeTree(typeTree, kw)
  }, [typeTree, addKeyword])

  const menuItems = ctxMenu ? buildMenuItems() : []

  const selStyle: React.CSSProperties = {
    background: 'var(--semi-color-primary-light-default)',
    display: 'block', padding: '2px 4px', borderRadius: 4,
  }

  if (loading) {
    return <div style={{ display: 'flex', justifyContent: 'center', padding: 80 }}><Spin size="large" /></div>
  }

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>Prefab 编排</h2>
        <Space>
          <Button onClick={doReload}>重载全部</Button>
          <Button theme="solid" type="primary" loading={saving} onClick={doSave}>保存</Button>
        </Space>
      </div>

      {loadErrors.length > 0 && (
        <Banner className="mb-12" type="warning" fullMode={false} closeIcon={null}
          description={<div>部分 prefab 加载失败：{loadErrors.map((e, i) => <div key={i} style={{ fontSize: 12 }}>{e}</div>)}</div>} />
      )}
      {detail?.error && (
        <Banner className="mb-12" type="danger" fullMode={false} closeIcon={null}
          description={`整树运行错误：${detail.error}`} />
      )}

      <div className="pf3-wrap">
        {/* 左：prefab 目录树（宽度可拖拽，默认 400） */}
        <div className="pf3-col" style={{ width: dirWidth }}
          onContextMenu={(e: React.MouseEvent) => {
          const t = e.target as HTMLElement
          if (t === e.currentTarget || t.classList?.contains('semi-card') || t.classList?.contains('semi-card-body')) {
            e.preventDefault()
            setCtxMenu({ x: e.clientX, y: e.clientY, kind: 'blank' })
          }
        }}>
        <Card className="card-shadow" bordered={false}
          header={<span style={{ fontWeight: 600 }}>Prefab 目录</span>}>
          {trees.length === 0 && dirs.length === 0 ? (
            <Empty title="暂无 prefab" description="右键新建或放到 backend/data/prefabs/ 下" />
          ) : (
            <div onMouseDown={(e) => { mods.current.shift = e.shiftKey; mods.current.ctrl = e.ctrlKey || e.metaKey }}>
            <Tree
              treeData={dirTree}
              draggable
              expandAll
              defaultExpandAll
              onSelect={(_k: string, _s: boolean, node: any) => onSelectDir(node.key || node.value)}
              onContextMenu={onDirCtx}
              onDrop={onDirDrop}
              renderLabel={(label: React.ReactNode, node: any) => (
                <span style={dirSel.has(node.key) ? selStyle : { display: 'block', padding: '2px 4px', borderRadius: 4 }}>{label}</span>
              )}
            />
            </div>
          )}
          {/* 目录树列的是 data/prefabs 下**全部**文件，但只有「启动」目录里的会在
              程序启动时加载——不打这句招呼，"不在启动目录"这个标签会被当成故障。 */}
          <div style={{ marginTop: 8, fontSize: 12, color: 'var(--semi-color-text-2)' }}>
            这里列出 <code>data/prefabs</code> 下全部 prefab；只有放在<b>「启动」目录</b>里的
            会在程序启动时加载（其余标「不在启动目录」，可照常打开编辑）。
            航点树 / 巡检计划 / 检测流程各有编排页。
          </div>
        </Card>
        </div>

        {/* 分隔条：目录 | 节点树 */}
        <div className="pf3-handle" title="拖拽调整 prefab 目录宽度"
          onMouseDown={(e) => startDrag(e, dirWidth, setDirWidth, 200, 720, 1)} />

        {/* 中：节点树（吃掉剩下的宽度） */}
        <div className="pf3-mid"
          onContextMenu={(e: React.MouseEvent) => {
          const t = e.target as HTMLElement
          if (t === e.currentTarget || t.classList?.contains('semi-card') || t.classList?.contains('semi-card-body')) {
            e.preventDefault()
            setCtxMenu({ x: e.clientX, y: e.clientY, kind: 'nodeBlank', target: 'root' })
          }
        }}>
        <Card className="card-shadow" bordered={false}
          header={
            <span style={{ fontWeight: 600 }}>
              节点树{detail ? ` · ${detail.path}` : ''}
            </span>
          }>
          {treeData.length === 0 ? (
            <Empty title="空树" />
          ) : (
            <div onMouseDown={(e) => { mods.current.shift = e.shiftKey; mods.current.ctrl = e.ctrlKey || e.metaKey }}>
            <Tree
              treeData={treeData}
              draggable
              expandAll
              defaultExpandAll
              onSelect={(_k: string, _s: boolean, node: any) => onNodeSelect(node.key || node.value)}
              onContextMenu={onNodeCtx}
              onDrop={onNodeDrop}
              renderLabel={(label: React.ReactNode, node: any) => (
                <span style={nodeSel.has(node.key) ? selStyle : { display: 'block', padding: '2px 4px', borderRadius: 4 }}>{label}</span>
              )}
            />
            </div>
          )}
        </Card>
        </div>

        {/* 分隔条：节点树 | 检视器 */}
        <div className="pf3-handle" title="拖拽调整检视器宽度"
          onMouseDown={(e) => startDrag(e, inspectorWidth, setInspectorWidth, 280, 720, -1)} />

        {/* 右：Inspector（宽度可拖拽，默认 360） */}
        <div className="pf3-col" style={{ width: inspectorWidth }}>
        <Card className="card-shadow" bordered={false}
          header={
            <div className="flex-between" style={{ width: '100%' }}>
              <span style={{ fontWeight: 600 }}>Inspector</span>
              {selectedStatus && (
                <Space>
                  <Tag size="small" color="blue">{selectedNode?.type}</Tag>
                  <Tag size="small" color={stateColor(selectedStatus._state)}>{stateText(selectedStatus._state)}</Tag>
                  {selectedStatus._error && <Tag size="small" color="red">{'出错'}</Tag>}
                </Space>
              )}
            </div>
          }>
          {!selectedNode ? (
            <Empty title="请选择节点" />
          ) : (
            <>
              {selectedSchema ? (
                <InspectorForm
                  schema={selectedSchema}
                  value={{ ...(selectedNode.properties || {}), children: selectedNode.children || [] }}
                  onChange={(patch) => {
                    const { children: _c, ...rest } = patch
                    updateProps(rest)
                  }}
                />
              ) : (
                <Empty title="未知节点类型" description={`schema 未找到: ${selectedNode.type}`} />
              )}
            </>
          )}
        </Card>
        </div>
      </div>

      {/* 右键菜单 */}
      {ctxMenu && (
        <div style={{ position: 'fixed', inset: 0, zIndex: 1000 }}
          onMouseDown={() => setCtxMenu(null)}
          onContextMenu={(e) => { e.preventDefault(); setCtxMenu(null) }}>
          <div style={{ left: Math.min(ctxMenu.x, window.innerWidth - 190), top: Math.min(ctxMenu.y, window.innerHeight - 260), ...MENU_STYLE }}
            onMouseDown={(e) => e.stopPropagation()}>
            {menuItems.map((it, i) => it.divider ? (
              <div key={i} style={{ borderTop: '1px solid var(--semi-color-border)', margin: '4px 6px' }} />
            ) : (
              <div key={i} onClick={() => { if (!it.disabled) { setCtxMenu(null); it.onClick?.() } }}
                style={{
                  padding: '6px 12px', borderRadius: 4, cursor: it.disabled ? 'not-allowed' : 'pointer',
                  color: it.danger ? 'var(--semi-color-danger)' : 'var(--semi-color-text-0)',
                  opacity: it.disabled ? 0.45 : 1,
                }}>
                {it.label}
              </div>
            ))}
          </div>
        </div>
      )}

      {/* 新建 / 重命名对话框 */}
      <Modal
        title={dialog?.title}
        visible={!!dialog}
        onOk={doDialogOk}
        onCancel={() => setDialog(null)}
        okText="确定"
        cancelText="取消"
        style={{ width: 420 }}>
        {dialog && (
          <Input
            autoFocus
            value={dialog.value}
            onChange={(v) => setDialog({ ...dialog, value: v as string })}
            placeholder={dialog.placeholder}
            onEnterPress={doDialogOk}
          />
        )}
      </Modal>

      {/* 添加子节点对话框：筛选框 + 类型继承树 */}
      <Modal
        title={
          addDialog?.position === 'before' ? '在前添加子节点'
            : addDialog?.position === 'after' ? '在后添加子节点' : '添加子节点'
        }
        visible={!!addDialog}
        onOk={() => {
          if (addDialog && addType) {
            addChild(addDialog.targetPath, addType, addDialog.position)
            setAddDialog(null)
            setAddType(undefined)
            setAddKeyword('')
          } else {
            Toast.warning('请先选择节点类型')
          }
        }}
        onCancel={() => { setAddDialog(null); setAddType(undefined); setAddKeyword('') }}
        okText="添加"
        cancelText="取消"
        style={{ width: 560 }}>
        {addDialog && (
          <div>
            <Input
              autoFocus
              placeholder="筛选节点类型（按名称或描述）…"
              value={addKeyword}
              onChange={(v) => setAddKeyword(v as string)}
              prefix={<span style={{ color: 'var(--semi-color-text-2)' }}>🔍</span>}
              style={{ marginBottom: 8 }}
            />
            <div style={{
              maxHeight: 320, overflow: 'auto',
              border: '1px solid var(--semi-color-border)', borderRadius: 6, padding: 4,
            }}>
              {typeTreeFiltered.length === 0 ? (
                <Empty title="无匹配类型" style={{ padding: '24px 0' }} />
              ) : (
                <Tree
                  treeData={typeTreeFiltered}
                  expandAll
                  defaultExpandAll
                  onSelect={(_k: string, _s: boolean, node: any) => {
                    if (node?.key?.toString().startsWith('type/')) {
                      setAddType(node.typeName as string)
                    }
                  }}
                  renderLabel={(label: React.ReactNode, node: any) => {
                    const isLeaf = node?.key?.toString().startsWith('type/')
                    const sel = addType === node?.typeName
                    return (
                      <span style={{
                        display: 'block', padding: '2px 4px', borderRadius: 4, cursor: isLeaf ? 'pointer' : 'default',
                        background: sel ? 'var(--semi-color-primary-light-default)' : undefined,
                      }}>
                        {label}
                      </span>
                    )
                  }}
                />
              )}
            </div>
          </div>
        )}
      </Modal>
    </div>
  )
}
