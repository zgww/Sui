/**
 * 检测流程编排 —— 「一条检测逻辑从取帧到通知怎么走」的编排页。
 *
 * 与「航点树编排」「巡检计划编排」是**三棵独立的树**：
 * - 航点树说"每个航点长什么样、到了之后拍什么照、画哪些检测框"；
 * - 计划树说"每天什么时候、把哪些航点/测点巡一遍"；
 * - 本页说"某个事件从取帧、前处理（节流/抽帧/区域/时段）、算法本身，
 *   到后处理（连续确认 / 留存 / 告警 / 转发 / 短信 / 邮件）怎么走"。
 *
 * 一个 `data/prefabs/检测算法/*.prefab.json` = **一条检测逻辑**（如"人员入侵"），
 * 根固定是 `DetectPipelineNode`。算法只是链路中的一环，同一算法在不同测点上
 * 可以配出松紧不同的好几条流程——这就是为什么它不是"检测框上挂个算法字段"
 * 而是单独一棵树。
 *
 * 左栏树视图 / 右栏检视器，右键菜单与另外两棵树保持一致（展开/收起子树、
 * 前中后添加、复制/剪切/粘贴、归入分组、删除、查看 JSON）。
 *
 * ## 停用（enabled=false）要看得出来
 *
 * `enabled` 的语义是"该节点**及其子树**不参与运行"，所以树上变灰的不是
 * 一个节点而是**整棵子树**：节流停了它后面的算法、告警同样不会跑，只灰
 * 节流那一行会让人以为"只是不限流了"。判定用 `planSelect.collectDisabled`
 * （子树一起灰，纯函数，三棵树通用，不另写一份）。
 *
 * 结构操作的规则都在纯函数模块里，本页只做事件接线：
 * - `utils/specTree.ts` —— 树结构通用操作 + 拖拽落点（三棵树共用）；
 * - `utils/detectSelect.ts` —— 检测流程树的中文名 / 配色 / 摘要 / 粘贴换编号
 *   （**纯逻辑，不引 Semi**；图标在 `utils/detectSelectIcons.tsx`）。
 */
import { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import {
  Button, Card, Empty, Input, Modal, Space, Spin, Tag, Tree, Select, Toast,
} from '@douyinfe/semi-ui'
import {
  IconChevronDown, IconChevronUp, IconPlus, IconRefresh, IconSave,
} from '@douyinfe/semi-icons'
import {
  getDetectNodeTypes, listDetectTrees, getDetectTree, saveDetectTree,
  createDetectFile, getDetectAlgorithms, getDetectPanelList,
  type DetectTreeSummary, type AlgorithmItem, type PanelItem,
} from '../api/detectPrefab'
import type { NodeTypeInfo } from '../api/prefab'
import InspectorForm from '../components/InspectorForm'
import { SEP, parentPathOf } from '../utils/trackSpec'
import {
  getNodeByPath, topLevelPaths, removeManyByPaths,
  moveNodeInSpec, batchMoveNodes, resolveDropKind, type DropKind,
} from '../utils/specTree'
import { collectDisabled } from '../utils/planSelect'
import {
  DETECT_TYPE_COLOR, detectNodeSummary, detectTypeLabel, regenerateDetectIds,
} from '../utils/detectSelect'

/* ------------------------------------------------------------ 小工具 */

/** 从节点 schema 取一份默认属性（与另外两棵树同款） */
function defaultsFrom(schema: any): Record<string, any> {
  const out: Record<string, any> = {}
  for (const [k, d] of Object.entries<any>(schema?.properties || {})) {
    if (k === 'type' || k === 'children') continue
    if ('default' in d) out[k] = d.default
  }
  return out
}

function flattenNodes(node: any, path = 'root', acc: { key: string; node: any }[] = []): any[] {
  acc.push({ key: path, node })
  ;(node?.children || []).forEach((c: any, i: number) =>
    flattenNodes(c, `${path}${SEP}children${SEP}${i}`, acc))
  return acc
}

function collectParentKeys(node: any, path = 'root', acc: string[] = []): string[] {
  if (Array.isArray(node?.children) && node.children.length) {
    acc.push(path)
    node.children.forEach((c: any, i: number) =>
      collectParentKeys(c, `${path}${SEP}children${SEP}${i}`, acc))
  }
  return acc
}

function toTreeData(node: any, path = 'root'): any[] {
  const typeName = node?.type || '?'
  const props = node?.properties || {}
  const labelText = props.name || detectTypeLabel(typeName)
  const summary = detectNodeSummary(typeName, props)
  const treeNode: any = {
    key: path,
    value: path,
    label: (
      <span style={{ display: 'inline-flex', alignItems: 'center', gap: 6 }}>
        <span>{labelText}</span>
        <Tag size="small" color={DETECT_TYPE_COLOR[typeName] || 'grey'}>
          {detectTypeLabel(typeName)}
        </Tag>
        {summary ? <Tag size="small" color="light-blue">{summary}</Tag> : null}
      </span>
    ),
  }
  if (Array.isArray(node?.children) && node.children.length) {
    treeNode.children = node.children.map((c: any, i: number) =>
      toTreeData(c, `${path}${SEP}children${SEP}${i}`)[0])
  }
  return [treeNode]
}

/** 类型选择树（只有本棵树的类型，后端已按 DetectNodeBase 过滤） */
function buildTypeTree(types: Record<string, NodeTypeInfo>): any[] {
  const root: any = {
    key: 'DetectNodeBase', value: 'DetectNodeBase',
    label: <span style={{ fontWeight: 600 }}>检测流程节点类型</span>, children: [] as any[],
  }
  for (const name of Object.keys(types).sort()) {
    const info = types[name]
    root.children.push({
      key: `type/${name}`, value: name, typeName: name,
      label: (
        <span style={{ display: 'flex', flexDirection: 'column', gap: 2 }}>
          <span style={{ fontWeight: 500 }}>
            {detectTypeLabel(name)}{' '}
            <span style={{ color: 'var(--semi-color-text-2)', fontWeight: 400 }}>{name}</span>
          </span>
          {info.description
            ? <span style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>{info.description}</span>
            : null}
        </span>
      ),
    })
  }
  return [root]
}

function filterTypeTree(nodes: any[], kw: string): any[] {
  const out: any[] = []
  for (const n of nodes) {
    const hit = (n.typeName || '').toLowerCase().includes(kw)
      || detectTypeLabel(n.typeName).includes(kw)
    const children = n.children?.length ? filterTypeTree(n.children, kw) : []
    if (hit || children.length) out.push({ ...n, children: children.length ? children : undefined })
  }
  return out
}

const MENU_STYLE: React.CSSProperties = {
  position: 'fixed', minWidth: 168, background: '#fff',
  border: '1px solid var(--semi-color-border)', borderRadius: 6,
  boxShadow: '0 6px 20px rgba(0,0,0,.14)', padding: 4, zIndex: 1001, fontSize: 13,
}

interface CtxMenu { x: number; y: number; target: string }
interface Clipboard { mode: 'copy' | 'cut'; nodes: any[] }

/** 分隔条拖拽（监听挂 window，拖出栏外也不丢事件） */
function startDrag(
  e: React.MouseEvent, start: number, apply: (v: number) => void,
  min: number, max: number, dir: number,
) {
  e.preventDefault()
  const startPos = e.clientX
  document.body.classList.add('wp-resizing-h')
  const onMove = (ev: MouseEvent) => {
    apply(Math.max(min, Math.min(max, start + (ev.clientX - startPos) * dir)))
  }
  const onUp = () => {
    document.body.classList.remove('wp-resizing-h')
    window.removeEventListener('mousemove', onMove)
    window.removeEventListener('mouseup', onUp)
  }
  window.addEventListener('mousemove', onMove)
  window.addEventListener('mouseup', onUp)
}

/* ------------------------------------------------------------ 页面 */

export default function DetectPrefab() {
  const [loading, setLoading] = useState(true)
  const [nodeTypes, setNodeTypes] = useState<Record<string, NodeTypeInfo>>({})
  const [algorithms, setAlgorithms] = useState<AlgorithmItem[]>([])
  const [panels, setPanels] = useState<PanelItem[]>([])
  const [trees, setTrees] = useState<DetectTreeSummary[]>([])
  const [currentRel, setCurrentRel] = useState('')
  const [spec, setSpec] = useState<Record<string, any> | null>(null)
  const [selectedPath, setSelectedPath] = useState('root')
  const [nodeSel, setNodeSel] = useState<Set<string>>(new Set())
  const [dragPaths, setDragPaths] = useState<Set<string>>(new Set())
  const [treeWidth, setTreeWidth] = useState(580)
  const [expandedKeys, setExpandedKeys] = useState<Set<string>>(new Set())
  const [saving, setSaving] = useState(false)
  const [ctxMenu, setCtxMenu] = useState<CtxMenu | null>(null)
  const [clipboard, setClipboard] = useState<Clipboard | null>(null)
  const [addDialog, setAddDialog] = useState<{
    targetPath: string
    position?: 'before' | 'after'
  } | null>(null)
  const [addType, setAddType] = useState<string | undefined>(undefined)
  const [addKeyword, setAddKeyword] = useState('')
  const [jsonTarget, setJsonTarget] = useState<string | null>(null)
  const [newFileName, setNewFileName] = useState('')
  const [newFileOpen, setNewFileOpen] = useState(false)
  const nodeAnchor = useRef('root')
  const mods = useRef({ shift: false, ctrl: false })

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

  const refreshFiles = useCallback(async () => {
    const { data } = await listDetectTrees()
    setTrees(data.trees || [])
    return data.trees || []
  }, [])

  const applySpec = useCallback((sp: Record<string, any>) => {
    setSpec(sp)
    setSelectedPath('root')
    setNodeSel(new Set())
    setExpandedKeys(new Set(collectParentKeys(sp.root || {})))
  }, [])

  const loadTree = useCallback(async (rel: string) => {
    const { data } = await getDetectTree(rel)
    setCurrentRel(rel)
    applySpec(data.spec)
  }, [applySpec])

  useEffect(() => {
    (async () => {
      try {
        const [list, types, algos, panelRes] = await Promise.all([
          refreshFiles(), getDetectNodeTypes(), getDetectAlgorithms(), getDetectPanelList(),
        ])
        setNodeTypes(types.data)
        setAlgorithms(algos.data.algorithms || [])
        setPanels(panelRes.data.panels || [])
        if (list.length > 0) await loadTree(list[0].rel_path)
      } catch { /* 拦截器已提示 */ } finally { setLoading(false) }
    })()
  }, [refreshFiles, loadTree])

  const treeData = useMemo(() => (spec?.root ? toTreeData(spec.root) : []), [spec])
  const nodeFlat = useMemo(() => (spec?.root ? flattenNodes(spec.root) : []), [spec])

  /** 停用的节点：`disabled` = 自己停了（打「已停用」标），`muted` = 自己或上级停了（变灰） */
  const { disabled: disabledSet, muted: mutedSet } = useMemo(
    () => collectDisabled(spec?.root), [spec])

  const selectedNode = useMemo(
    () => (spec ? getNodeByPath(spec, selectedPath) : null), [spec, selectedPath])

  const selectedSchema = useMemo(() => {
    if (!selectedNode?.type) return null
    return nodeTypes[selectedNode.type]?.schema || null
  }, [selectedNode, nodeTypes])

  /**
   * 检视器里 `ui.optionsFrom` 的数据源。
   *
   * 检测流程的视觉算法已改成"每种算法一个节点子类"（见后端 nodes/algorithms.py），
   * 节点类型即算法身份，algorithm 字段只读、不再有下拉，因此本页目前没有字段
   * 消费 algorithms；拉取保留是为了和航点检测框共用同一份算法目录、并供后续
   * 按目录展示算法颜色/描述。名字 `algorithms` 与后端 optionsFrom 约定保持一致。
   */
  const optionSources = useMemo<Record<string, { value: string; label: string }[]>>(() => ({
    algorithms: algorithms.map((a) => ({
      value: a.id,
      label: a.category ? `${a.category} · ${a.name}` : a.name,
    })),
    panelList: panels.map((p) => ({
      value: p.name,
      label: p.display_name,
    })),
  }), [algorithms, panels])

  const typeTreeFiltered = useMemo(() => {
    const tree = buildTypeTree(nodeTypes)
    const kw = addKeyword.trim().toLowerCase()
    return kw ? filterTypeTree(tree, kw) : tree
  }, [nodeTypes, addKeyword])

  /* ------------------------------------------------------------ 选择/右键 */

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
    e.stopPropagation()
    const key = (node?.key || node?.value || 'root') as string
    if (!nodeSel.has(key)) { setNodeSel(new Set([key])); setSelectedPath(key) }
    setCtxMenu({ x: e.clientX, y: e.clientY, target: key })
  }

  /* ------------------------------------------------------------ 编辑操作 */

  const patchNodeProps = (path: string, patch: Record<string, any>) => {
    if (!spec) return
    const next = JSON.parse(JSON.stringify(spec))
    const node = getNodeByPath(next, path)
    if (!node) return
    node.properties = { ...(node.properties || {}), ...patch }
    setSpec(next)
  }

  const updateProps = (patch: Record<string, any>) => patchNodeProps(selectedPath, patch)

  /** 添加子节点：`position` 有值时贴着目标插到同一层，否则追加到目标子级末尾 */
  const addChild = (targetPath: string, typeName?: string, position?: 'before' | 'after') => {
    if (!spec || !typeName) return
    const next = JSON.parse(JSON.stringify(spec))

    let parentPath = targetPath
    let insertAt: number | null = null

    if (position && targetPath !== 'root') {
      parentPath = parentPathOf(targetPath)
      const kids: any[] = getNodeByPath(next, parentPath)?.children || []
      const idx = Number(targetPath.split(SEP).pop())
      if (!Number.isInteger(idx)) { Toast.warning('无法确定插入位置，请刷新后重试'); return }
      insertAt = position === 'before' ? idx : idx + 1
    }

    const parent = getNodeByPath(next, parentPath)
    if (!parent) return
    parent.children = parent.children || []
    const props = defaultsFrom(nodeTypes[typeName]?.schema)
    const same = parent.children.filter((c: any) => c?.type === typeName).length
    props.name = `${detectTypeLabel(typeName)} ${same + 1}`

    const at = insertAt === null ? parent.children.length : insertAt
    parent.children.splice(at, 0, { type: typeName, properties: props })
    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(parentPath))
    const newPath = `${parentPath}${SEP}children${SEP}${at}`
    setSelectedPath(newPath)
    setNodeSel(new Set([newPath]))
  }

  const openAddDialog = (targetPath: string, position?: 'before' | 'after') => {
    const sameType = position && targetPath !== 'root'
      ? getNodeByPath(spec, targetPath)?.type
      : undefined
    setAddType(sameType); setAddKeyword('')
    setAddDialog({ targetPath, position })
  }

  const doDelete = () => {
    const targets = topLevelPaths([...nodeSel]).filter((p) => p !== 'root')
    if (!targets.length) { Toast.warning('根节点不可删除'); return }
    const next = JSON.parse(JSON.stringify(spec))
    const removed = removeManyByPaths(next.root, targets)
    setSpec(next)
    if (targets.includes(selectedPath)) setSelectedPath('root')
    setNodeSel(new Set())
    Toast.success(`已删除 ${removed} 个节点（保存后落盘）`)
  }

  const confirmDelete = () => {
    if (!nodeSel.size || [...nodeSel].includes('root')) { Toast.warning('根节点不可删除'); return }
    Modal.confirm({
      title: `删除 ${topLevelPaths([...nodeSel]).filter((p) => p !== 'root').length} 个节点`,
      content: '删除后点击「保存」才落盘生效，确定删除？',
      okType: 'danger',
      onOk: doDelete,
    })
  }

  const copyNodes = () => {
    if (!spec || !nodeSel.size) { Toast.warning('请先选中节点'); return }
    const tops = topLevelPaths([...nodeSel]).filter((p) => p !== 'root')
    const nodes = tops.map((p) => JSON.parse(JSON.stringify(getNodeByPath(spec, p)))).filter(Boolean)
    if (!nodes.length) { Toast.warning('根节点不可复制'); return }
    setClipboard({ mode: 'copy', nodes })
    Toast.success(`已复制 ${nodes.length} 个节点`)
  }

  const cutNodes = () => {
    if (!spec || !nodeSel.size) { Toast.warning('请先选中节点'); return }
    const tops = topLevelPaths([...nodeSel]).filter((p) => p !== 'root')
    if (!tops.length) { Toast.warning('根节点不可剪切'); return }
    const nodes = tops.map((p) => JSON.parse(JSON.stringify(getNodeByPath(spec, p)))).filter(Boolean)
    const next = JSON.parse(JSON.stringify(spec))
    removeManyByPaths(next.root, tops)
    setSpec(next)
    if (tops.includes(selectedPath)) setSelectedPath('root')
    setNodeSel(new Set())
    setClipboard({ mode: 'cut', nodes })
    Toast.success(`已剪切 ${nodes.length} 个节点，右键目标节点粘贴`)
  }

  /**
   * 粘贴。
   *
   * 检测编号要**换新的**（`regenerateDetectIds`）：复制件沿用原编号的话，
   * 两条流程在引用侧会被当成同一条，改一处等于改两处。阈值、收件人这些是
   * 配置，照抄。
   */
  const pasteTo = (targetPath: string) => {
    if (!clipboard || !spec) return
    const next = JSON.parse(JSON.stringify(spec))
    const target = getNodeByPath(next, targetPath)
    if (!target) { Toast.error('目标节点不存在'); return }
    const clones = clipboard.nodes.map((n) => JSON.parse(JSON.stringify(n)))
    let fresh = 0
    for (const c of clones) fresh += regenerateDetectIds(c)
    target.children = target.children || []
    target.children.push(...clones)
    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(targetPath))
    if (clipboard.mode === 'cut') setClipboard(null)
    Toast.success(
      fresh
        ? `已粘贴 ${clones.length} 个节点（重新生成 ${fresh} 个检测编号）`
        : `已粘贴 ${clones.length} 个节点`,
    )
  }

  /** 归入分组：在同父选中节点的父级下新建分组，并把它们移入 */
  const groupInto = () => {
    if (!spec) return
    const tops = topLevelPaths([...nodeSel]).filter((p) => p !== 'root')
    if (!tops.length) { Toast.warning('请先选中要归入分组的节点'); return }
    const parents = new Set(tops.map(parentPathOf))
    if (parents.size !== 1) { Toast.warning('批量归入分组要求选中节点在同一父级下'); return }
    const parentPath = [...parents][0]
    const next = JSON.parse(JSON.stringify(spec))
    const parent = getNodeByPath(next, parentPath)
    if (!parent?.children) return
    const picked = tops
      .map((p) => ({ p, idx: Number(p.split(SEP).pop()) }))
      .sort((a, b) => b.idx - a.idx)
      .map(({ idx }) => {
        const node = parent.children[idx]
        parent.children.splice(idx, 1)
        return node
      })
    const groupProps = defaultsFrom(nodeTypes.DetectGroupNode?.schema)
    groupProps.name = '新分组'
    parent.children.push({
      type: 'DetectGroupNode', properties: groupProps, children: picked.reverse(),
    })
    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(parentPath))
    Toast.success('已归入新分组')
  }

  /* ------------------------------------------------------------ 展开/收起 */

  const expandSubtree = (path: string) => {
    if (!spec) return
    const node = getNodeByPath(spec, path)
    if (!node) return
    const keys = new Set(collectParentKeys(node, path))
    keys.add(path)
    setExpandedKeys((prev) => new Set([...prev, ...keys]))
  }

  const collapseSubtree = (path: string) => {
    if (!spec) return
    const node = getNodeByPath(spec, path)
    if (!node) return
    const keys = new Set([path, ...collectParentKeys(node, path)])
    setExpandedKeys((prev) => {
      const n = new Set(prev)
      keys.forEach((k) => n.delete(k))
      return n
    })
  }

  const expandAll = () => { if (spec?.root) setExpandedKeys(new Set(collectParentKeys(spec.root))) }
  const collapseAll = () => setExpandedKeys(new Set())

  /* ------------------------------------------------------------ 拖拽 */

  const onNodeDrop = (props: any) => {
    if (!spec) return
    setDragPaths(new Set())
    const dragPath: string = props.dragNode?.key || ''
    const targetPath: string = props.node?.key || ''
    if (!dragPath || !targetPath) return

    // dropPosition 是「相对方向 + 目标同级下标」的绝对下标，不能直接当方向用
    const kind: DropKind = resolveDropKind(props)
    const next = JSON.parse(JSON.stringify(spec))

    if (nodeSel.has(dragPath) && nodeSel.size > 1) {
      const res = batchMoveNodes(next.root, [...nodeSel], targetPath, kind)
      if (res.ok) {
        setSpec(next)
        Toast.success(`已移动 ${nodeSel.size} 个节点，保存后落盘`)
      } else {
        Toast.warning(res.reason || '无法移动到该位置')
      }
      return
    }

    const res = moveNodeInSpec(next.root, dragPath, targetPath, kind)
    if (res.ok) {
      setSpec(next)
      if (kind === 'on') setExpandedKeys((prev) => new Set(prev).add(targetPath))
      Toast.success('已移动节点，保存后落盘')
    } else {
      Toast.warning(res.reason || '无法移动到该位置')
    }
  }

  const onNodeDragStart = ({ node }: any) => {
    const key: string = node?.key || ''
    if (!key) return
    if (nodeSel.has(key) && nodeSel.size > 1) setDragPaths(new Set(nodeSel))
    else setDragPaths(new Set([key]))
  }

  useEffect(() => {
    const onKey = (e: KeyboardEvent) => {
      if (e.key !== 'Delete') return
      const t = e.target as HTMLElement
      if (t && /INPUT|TEXTAREA|SELECT/.test(t.tagName)) return
      if (nodeSel.size) { e.preventDefault(); confirmDelete() }
    }
    window.addEventListener('keydown', onKey)
    return () => window.removeEventListener('keydown', onKey)
  })

  /* ------------------------------------------------------------ 工具栏动作 */

  const doSave = async () => {
    if (!spec || !currentRel) { Toast.warning('请先新建或选择一个检测流程文件'); return }
    setSaving(true)
    try {
      await saveDetectTree(currentRel, spec)
      Toast.success('已保存')
      await refreshFiles()
    } catch { /* 拦截器已提示 */ } finally { setSaving(false) }
  }

  const doCreateFile = async () => {
    let rel = newFileName.trim()
    if (!rel) { Toast.warning('文件名不能为空'); return }
    if (!rel.endsWith('.prefab.json')) rel = `${rel.replace(/\.prefab\.json$/i, '')}.prefab.json`
    try {
      await createDetectFile(rel)
      Toast.success('已创建')
      setNewFileOpen(false); setNewFileName('')
      const list = await refreshFiles()
      if (list.find((t) => t.rel_path === rel)) await loadTree(rel)
    } catch { /* 拦截器已提示 */ }
  }

  /* ------------------------------------------------------------ 右键菜单 */

  const menuItems = (() => {
    if (!ctxMenu) return [] as any[]
    const p = ctxMenu.target || 'root'
    // 除了 root（没有"前后"可言）之外都给——别按节点类型卡，否则右键常见节点
    // 时看不到这两项，反馈就是"没效果"
    const canInsertBeside = p !== 'root'
    const items: any[] = [
      { label: '展开子树', onClick: () => expandSubtree(p) },
      { label: '收起子树', onClick: () => collapseSubtree(p) },
      { divider: true },
      { label: '添加子节点', onClick: () => openAddDialog(p) },
      ...(canInsertBeside
        ? [
          { label: '在前添加子节点', onClick: () => openAddDialog(p, 'before') },
          { label: '在后添加子节点', onClick: () => openAddDialog(p, 'after') },
        ]
        : []),
      { divider: true },
      { label: '复制节点', onClick: copyNodes },
      { label: '剪切节点', onClick: cutNodes },
      { label: '粘贴', disabled: !clipboard, onClick: () => pasteTo(p) },
      { label: '归入分组', onClick: groupInto },
    ]
    if (p !== 'root') items.push({ divider: true }, { label: '删除节点', danger: true, onClick: confirmDelete })
    items.push({ divider: true }, { label: '查看 JSON 数据', onClick: () => setJsonTarget(p) })
    return items
  })()

  const jsonNode = jsonTarget && spec ? getNodeByPath(spec, jsonTarget) : null
  const selStyle: React.CSSProperties = { display: 'block', padding: '2px 4px', borderRadius: 4 }

  if (loading) {
    return <div style={{ display: 'flex', justifyContent: 'center', padding: 80 }}><Spin size="large" /></div>
  }

  return (
    <div className="page-container">
      <div className="mb-12" style={{ display: 'flex', alignItems: 'center', gap: 12, flexWrap: 'wrap' }}>
        <h2 style={{ margin: 0 }}>检测算法编排</h2>
        <Select
          value={currentRel || undefined}
          placeholder="选择检测流程文件"
          style={{ width: 280 }}
          onChange={(v) => loadTree(v as string)}
          optionList={trees.map((t) => ({ label: t.rel_path, value: t.rel_path }))}
        />
        <Space wrap>
          <Button icon={<IconPlus />} onClick={() => { setNewFileName(''); setNewFileOpen(true) }}>新建文件</Button>
          <Button icon={<IconRefresh />} onClick={() => refreshFiles()}>刷新列表</Button>
          <Button icon={<IconChevronDown />} onClick={expandAll}>展开全部</Button>
          <Button icon={<IconChevronUp />} onClick={collapseAll}>收起全部</Button>
          <Button theme="solid" type="primary" icon={<IconSave />} loading={saving} onClick={doSave}>保存</Button>
        </Space>
      </div>

      <div className="wp3-wrap">
        {/* 左：检测流程树（宽度可拖拽） */}
        <div className="wp3-tree" style={{ width: treeWidth }}
          onContextMenu={(e) => {
            e.preventDefault()
            setCtxMenu({ x: e.clientX, y: e.clientY, target: 'root' })
          }}>
          <Card className="card-shadow" bordered={false}
            header={<span style={{ fontWeight: 600 }}>检测流程树{currentRel ? ` · ${currentRel}` : '（未选择文件）'}</span>}
            style={{ height: '100%' }}>
            {!spec || treeData.length === 0 ? (
              <Empty title="空树"
                description="新建文件后在根节点（检测流程）上右键「添加子节点」：先加前处理（取帧/节流/抽帧…），再加「算法检测」，最后加后处理（告警/转发/短信/邮件）" />
            ) : (
              <div onMouseDown={(e) => { mods.current.shift = e.shiftKey; mods.current.ctrl = e.ctrlKey || e.metaKey }}>
                <Tree
                  treeData={treeData}
                  draggable
                  autoExpandWhenDragEnter
                  expandedKeys={[...expandedKeys]}
                  onExpand={(keys: string[]) => setExpandedKeys(new Set(keys))}
                  onSelect={(_k: string, _s: boolean, node: any) => onNodeSelect(node.key || node.value)}
                  onContextMenu={onNodeCtx}
                  onDragStart={onNodeDragStart}
                  onDragEnd={() => setDragPaths(new Set())}
                  onDrop={onNodeDrop}
                  renderLabel={(label: React.ReactNode, node: any) => {
                    const k = node.key as string
                    const isSel = nodeSel.has(k)
                    const isDragging = dragPaths.has(k)
                    // 自己停了 -> 打「已停用」；整棵子树（含被上级连带的）-> 变灰
                    const off = disabledSet.has(k)
                    const dim = mutedSet.has(k)
                    return (
                      <span
                        title={off
                          ? '已停用：该节点及其子树不参与运行'
                          : dim ? '上级节点已停用，本节点不参与运行' : undefined}
                        style={{
                          ...selStyle,
                          opacity: isDragging || dim ? 0.45 : 1,
                          outline: isDragging ? '1px dashed var(--semi-color-primary)' : undefined,
                        }}
                        className={isSel ? 'wp-prefab-node-sel' : undefined}
                      >
                        {label}
                        {off ? <Tag size="small" color="grey">已停用</Tag> : null}
                      </span>
                    )
                  }}
                />
              </div>
            )}
            <div style={{ marginTop: 8, color: 'var(--semi-color-text-2)', fontSize: 12 }}>
              Ctrl 点选 / Shift 区间多选；Delete 删除选中；拖拽移动（拖到节点上下边缘=插到前后，拖到节点中间=归入其子级）；右键更多操作。
              一个文件 = 一条检测逻辑，按「前处理 → 算法检测 → 后处理」的顺序排；停用的节点（含它的子树）会变灰且不参与运行。
            </div>
          </Card>
        </div>

        {/* 分隔条：树 | 检视器 */}
        <div className="wp3-handle" title="拖拽调整树视图宽度"
          onMouseDown={(e) => startDrag(e, treeWidth, setTreeWidth, 220, 760, 1)} />

        {/* 右：检视器 */}
        <div className="wp3-inspector">
          <Card className="card-shadow" bordered={false}
            header={
              <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', width: '100%' }}>
                <span style={{ fontWeight: 600 }}>检视器</span>
                {selectedNode && (
                  <Tag size="small" color={DETECT_TYPE_COLOR[selectedNode.type] || 'blue'}>
                    {detectTypeLabel(selectedNode.type)}
                  </Tag>
                )}
              </div>
            }>
            {nodeSel.size > 1 ? (
              <Empty title={`已选中 ${nodeSel.size} 个节点`} description="多选状态下不可批量编辑，请选择单个节点查看属性" />
            ) : !selectedNode ? (
              <Empty title="请选择节点" />
            ) : selectedSchema ? (
              <InspectorForm
                schema={selectedSchema}
                value={{ ...(selectedNode.properties || {}), children: selectedNode.children || [] }}
                onChange={(patch) => {
                  const { children: _c, ...rest } = patch
                  updateProps(rest)
                }}
                optionSources={optionSources}
              />
            ) : (
              <Empty title="未知节点类型" description={`schema 未找到: ${selectedNode.type}`} />
            )}
          </Card>
        </div>
      </div>

      {/* 右键菜单 */}
      {ctxMenu && (
        <div style={{ position: 'fixed', inset: 0, zIndex: 1000 }}
          onMouseDown={() => setCtxMenu(null)}
          onContextMenu={(e) => { e.preventDefault(); setCtxMenu(null) }}>
          <div style={{
            left: Math.min(ctxMenu.x, window.innerWidth - 190),
            top: Math.min(ctxMenu.y, Math.max(8, window.innerHeight - 340)),
            maxHeight: window.innerHeight - Math.min(ctxMenu.y, Math.max(8, window.innerHeight - 340)) - 8,
            overflowY: 'auto',
            ...MENU_STYLE,
          }}
            onMouseDown={(e) => e.stopPropagation()}>
            {menuItems.map((it, i) => it.divider ? (
              <div key={i} style={{ borderTop: '1px solid var(--semi-color-border)', margin: '4px 6px' }} />
            ) : (
              <div key={i} onClick={() => { if (!it.disabled) { setCtxMenu(null); it.onClick?.() } }}
                style={{
                  padding: '6px 12px', borderRadius: 4,
                  cursor: it.disabled ? 'not-allowed' : 'pointer',
                  color: it.danger ? 'var(--semi-color-danger)' : 'var(--semi-color-text-0)',
                  opacity: it.disabled ? 0.45 : 1,
                }}>
                {it.label}
              </div>
            ))}
          </div>
        </div>
      )}

      {/* 添加子节点：筛选 + 类型树 */}
      <Modal
        title={addDialog?.position === 'before' ? '在前添加子节点'
          : addDialog?.position === 'after' ? '在后添加子节点' : '添加子节点'}
        visible={!!addDialog}
        onOk={() => {
          if (addDialog && addType) {
            addChild(addDialog.targetPath, addType, addDialog.position)
            setAddDialog(null); setAddType(undefined); setAddKeyword('')
          } else Toast.warning('请先选择节点类型')
        }}
        onCancel={() => { setAddDialog(null); setAddType(undefined); setAddKeyword('') }}
        okText="添加" cancelText="取消" style={{ width: 560 }}>
        {addDialog && (
          <div>
            {addDialog.position && (
              <div style={{ marginBottom: 8, fontSize: 12, color: 'var(--semi-color-text-2)' }}>
                新节点将插到「{getNodeByPath(spec, addDialog.targetPath)?.properties?.name || '该节点'}」
                {addDialog.position === 'before' ? '之前' : '之后'}。
              </div>
            )}
            <Input autoFocus placeholder="筛选节点类型（如 节流 / 算法检测 / 数值告警 / 范围告警 / 短信）…"
              value={addKeyword} onChange={(v) => setAddKeyword(v as string)}
              style={{ marginBottom: 8 }} />
            <div style={{ maxHeight: 320, overflow: 'auto', border: '1px solid var(--semi-color-border)', borderRadius: 6, padding: 4 }}>
              {typeTreeFiltered.length === 0 ? <Empty title="无匹配类型" style={{ padding: '24px 0' }} /> : (
                <Tree treeData={typeTreeFiltered} expandAll defaultExpandAll
                  onSelect={(_k: string, _s: boolean, node: any) => {
                    if (node?.key?.toString().startsWith('type/')) setAddType(node.typeName as string)
                  }}
                  renderLabel={(label: React.ReactNode, node: any) => {
                    const isLeaf = node?.key?.toString().startsWith('type/')
                    const sel = addType === node?.typeName
                    return (
                      <span style={{
                        display: 'block', padding: '2px 4px', borderRadius: 4,
                        cursor: isLeaf ? 'pointer' : 'default',
                        background: sel ? 'var(--semi-color-primary-light-default)' : undefined,
                      }}>{label}</span>
                    )
                  }}
                />
              )}
            </div>
          </div>
        )}
      </Modal>

      {/* 查看 JSON */}
      <Modal title="节点 JSON 数据" visible={jsonTarget !== null}
        onCancel={() => setJsonTarget(null)} footer={null} style={{ width: 620 }}>
        <pre style={{ maxHeight: '60vh', overflow: 'auto', background: 'var(--semi-color-fill-0)', padding: 12, borderRadius: 6, fontSize: 12 }}>
          {jsonNode ? JSON.stringify(jsonNode, null, 2) : ''}
        </pre>
      </Modal>

      {/* 新建文件 */}
      <Modal title="新建检测流程文件" visible={newFileOpen}
        onOk={doCreateFile} onCancel={() => setNewFileOpen(false)}
        okText="创建" cancelText="取消" style={{ width: 460 }}>
        <Input autoFocus value={newFileName} onChange={(v) => setNewFileName(v as string)}
          placeholder="文件名，可含子目录，如 人员入侵/配电室夜间（自动补 .prefab.json）"
          onEnterPress={doCreateFile} />
      </Modal>
    </div>
  )
}
