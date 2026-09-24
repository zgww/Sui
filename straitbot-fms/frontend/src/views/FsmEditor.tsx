import { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import {
  ReactFlow, ReactFlowProvider, Background, Controls, Handle, Position,
  Node, Edge, Connection, NodeProps, OnNodesChange, OnEdgesChange, OnConnect,
  useReactFlow, useUpdateNodeInternals, useStore,
} from '@xyflow/react'
import '@xyflow/react/dist/style.css'
import { Button, Empty, Input, Modal, Space, Tag, Toast, Tree } from '@douyinfe/semi-ui'
import { IconBranch, IconDelete, IconPlus, IconSave } from '@douyinfe/semi-icons'
import InspectorForm from '../components/InspectorForm'
import {
  FsmObject, FsmObjType, FsmConnection, FsmSpec, FsmFileSummary, FsmTreeList,
  getFsmTrees, getFsmTree, saveFsmTree, createFsmDir, deleteFsmDir,
  createFsmFile, deleteFsmFile, renameFsmEntry,
} from '../api/fsm'

/* ================= 对象类型元数据（pin 由对象定义） ================= */

interface PinDef { name: string; side: 'in' | 'out' }
interface ObjMeta {
  label: string
  shape: 'circle' | 'rect' | 'diamond'
  color: string
  pins: PinDef[]
  schema: Record<string, any>
  defaults: Partial<FsmObject>
}

const OBJ_META: Record<FsmObjType, ObjMeta> = {
  state_machine: {
    label: '状态机', shape: 'circle', color: '#4F6B9A',
    pins: [
      { name: 'activator', side: 'in' },
      { name: 'end', side: 'out' },
    ],
    schema: {
      type: 'object',
      properties: {
        name: { type: 'string', title: '名称', ui: { widget: 'text', placeholder: '状态机名称' } },
        initial_state: { type: 'string', title: '初始状态', ui: { widget: 'text', placeholder: '进入状态机时激活的状态名' } },
        end_signal: { type: 'string', title: '结束信号', default: 'sm_close', ui: { widget: 'text', placeholder: '结束信号名（默认 sm_close）' } },
        description: { type: 'string', title: '描述', ui: { widget: 'textarea', rows: 3 } },
      },
    },
    defaults: { end_signal: 'sm_close' },
  },
  state: {
    label: '状态', shape: 'rect', color: '#35705A',
    pins: [
      { name: 'in', side: 'in' },
      { name: 'actions', side: 'out' },
    ],
    schema: {
      type: 'object',
      properties: {
        name: { type: 'string', title: '名称', ui: { widget: 'text', placeholder: '状态名称' } },
        description: { type: 'string', title: '描述', ui: { widget: 'textarea', rows: 3 } },
      },
    },
    defaults: {},
  },
  signal_action: {
    label: '信号迁移动作', shape: 'diamond', color: '#9A6A2F',
    pins: [
      { name: 'in', side: 'in' },
      { name: 'out', side: 'out' },
    ],
    schema: {
      type: 'object',
      properties: {
        name: { type: 'string', title: '名称', ui: { widget: 'text', placeholder: '动作名称' } },
        signal: { type: 'string', title: '信号', ui: { widget: 'text', placeholder: '收到该信号时执行迁移' } },
        description: { type: 'string', title: '描述', ui: { widget: 'textarea', rows: 3 } },
      },
    },
    defaults: {},
  },
  sm_activate_action: {
    label: '状态机激活动作', shape: 'diamond', color: '#7A6F9E',
    pins: [
      { name: 'in', side: 'in' },
      { name: 'target_sm', side: 'out' },
      { name: 'complete', side: 'out' },
    ],
    schema: {
      type: 'object',
      properties: {
        name: { type: 'string', title: '名称', ui: { widget: 'text', placeholder: '动作名称' } },
        description: { type: 'string', title: '描述', ui: { widget: 'textarea', rows: 3 } },
      },
    },
    defaults: {},
  },
}

export const OBJ_TYPES: FsmObjType[] = ['state_machine', 'state', 'signal_action', 'sm_activate_action']

const EMPTY_SPEC: FsmSpec = { version: 1, name: '', description: '', objects: [], connections: [] }

/* ================= 自定义节点组件 ================= */

const NODE_W = 130
const NODE_H = 84

function FsmNode({ id, data }: NodeProps) {
  const obj = data.obj as FsmObject
  const meta = OBJ_META[obj.type]
  const cx = NODE_W / 2
  const cy = NODE_H / 2
  // 自定义节点内容固定，挂载后让 React Flow 重新测量节点内部信息（含 handleBounds），
  // 否则显式尺寸 + 受控节点下 pin 连线无法定位渲染。
  const updateNodeInternals = useUpdateNodeInternals()
  useEffect(() => {
    const t = setTimeout(() => { try { updateNodeInternals(id) } catch { /* */ } }, 30)
    return () => clearTimeout(t)
  }, [updateNodeInternals, id])

  // 选中高亮：直接订阅 React Flow 内部选中状态（nodeLookup 里 node.selected 由
  // 内部选中动作维护），不写入受控 nodes 数组，避免 nodes 引用变化引发
  // setNodes 死循环（会清空 handleBounds 导致连线不渲染）。
  const selected = useStore(
    useCallback((s) => { const n = s.nodeLookup.get(id); return !!n && !!n.selected }, [id]),
  )

  const shapeNode = (() => {
    if (meta.shape === 'circle') {
      const d = 96
      return (
        <div style={{
          position: 'absolute', left: (NODE_W - d) / 2, top: (NODE_H - d) / 2,
          width: d, height: d, borderRadius: '50%',
          background: meta.color + '1A', border: `2px solid ${meta.color}`,
          boxSizing: 'border-box',
        }} />
      )
    }
    if (meta.shape === 'rect') {
      return (
        <div style={{
          position: 'absolute', left: 4, top: 8, right: 4, bottom: 8,
          borderRadius: 8, background: meta.color + '14',
          border: `2px solid ${meta.color}`, boxSizing: 'border-box',
        }} />
      )
    }
    // diamond
    return (
      <svg width={NODE_W} height={NODE_H} style={{ position: 'absolute', left: 0, top: 0 }}>
        <polygon
          points={`${cx},2 ${NODE_W - 2},${cy} ${cx},${NODE_H - 2} 2,${cy}`}
          fill={meta.color + '1A'} stroke={meta.color} strokeWidth={2}
        />
      </svg>
    )
  })()

  return (
    <div style={{
      position: 'relative', width: NODE_W, height: NODE_H, borderRadius: 12,
      outline: selected ? `2px solid ${meta.color}` : 'none', outlineOffset: 2,
    }}>
      {shapeNode}
      <div style={{
        position: 'absolute', inset: 0, display: 'flex', flexDirection: 'column',
        alignItems: 'center', justifyContent: 'center', pointerEvents: 'none', padding: '0 14px',
      }}>
        <div style={{
          fontSize: 13, fontWeight: 600, color: '#1A1B1C', maxWidth: '100%',
          overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap',
        }}>
          {obj.name || meta.label}
        </div>
        <div style={{ fontSize: 11, color: meta.color, marginTop: 2 }}>{meta.label}</div>
      </div>
      {meta.pins.map((pin) => (
        <Handle
          key={pin.name}
          id={pin.name}
          type={pin.side === 'in' ? 'target' : 'source'}
          position={pin.side === 'in' ? Position.Left : Position.Right}
          title={pin.name}
          style={{ background: '#fff', border: `2px solid ${meta.color}`, width: 10, height: 10 }}
        />
      ))}
    </div>
  )
}

const nodeTypes = {
  state_machine: FsmNode,
  state: FsmNode,
  signal_action: FsmNode,
  sm_activate_action: FsmNode,
}

/* ================= 目录树（左栏） ================= */

interface DirNode { dirs: Record<string, DirNode>; files: FsmFileSummary[] }

function buildDirTree(dirList: string[], files: FsmFileSummary[]): DirNode {
  const root: DirNode = { dirs: {}, files: [] }
  for (const d of dirList) {
    if (!d) continue
    const parts = d.split('/')
    let cur = root
    for (const p of parts) {
      if (!cur.dirs[p]) cur.dirs[p] = { dirs: {}, files: [] }
      cur = cur.dirs[p]
    }
  }
  for (const f of files) {
    const parts = f.rel_path.split('/')
    parts.pop()
    let cur = root
    for (const p of parts) {
      if (!p) continue
      if (!cur.dirs[p]) cur.dirs[p] = { dirs: {}, files: [] }
      cur = cur.dirs[p]
    }
    cur.files.push(f)
  }
  return root
}

/* ================= 右键菜单 ================= */

interface MenuItem { label: string; danger?: boolean; onClick: () => void }
interface MenuState { x: number; y: number; items: MenuItem[] }

function ContextMenu({ menu, onClose }: { menu: MenuState; onClose: () => void }) {
  useEffect(() => {
    const close = () => onClose()
    const onCtx = () => onClose()
    // 延迟注册：避免"打开本次菜单的那次 contextmenu"冒泡到 window 时立即关闭自己
    const t = setTimeout(() => {
      window.addEventListener('click', close)
      window.addEventListener('contextmenu', onCtx)
      window.addEventListener('blur', close)
    }, 80)
    return () => {
      clearTimeout(t)
      window.removeEventListener('click', close)
      window.removeEventListener('contextmenu', onCtx)
      window.removeEventListener('blur', close)
    }
  }, [onClose])

  return (
    <div style={{
      position: 'fixed', left: menu.x, top: menu.y, zIndex: 2000,
      background: '#fff', border: '1px solid #e4e3dd', borderRadius: 6,
      boxShadow: '0 4px 12px rgba(0,0,0,.14)', padding: 4, minWidth: 150,
    }}>
      {menu.items.map((it) => (
        <div
          key={it.label}
          onClick={(e) => { e.stopPropagation(); it.onClick(); onClose() }}
          style={{
            padding: '6px 10px', fontSize: 13, cursor: 'pointer', borderRadius: 4,
            color: it.danger ? '#d5434c' : '#1A1B1C', userSelect: 'none',
          }}
          onMouseEnter={(e) => { e.currentTarget.style.background = '#f2f3f5' }}
          onMouseLeave={(e) => { e.currentTarget.style.background = 'transparent' }}
        >
          {it.label}
        </div>
      ))}
    </div>
  )
}

/* ================= 输入弹窗（新建/重命名） ================= */

interface InputModalState {
  mode: 'file' | 'dir' | 'rename'
  title: string
  placeholder: string
  value: string
  relPath?: string
}

/* ================= 编辑器主体 ================= */

function FsmEditorInner() {
  const rf = useReactFlow()
  const counter = useRef(1)
  const uid = () => `${Date.now().toString(36)}_${(counter.current++).toString(36)}`

  const [trees, setTrees] = useState<FsmTreeList>({ files: [], dirs: [] })
  const [currentPath, setCurrentPath] = useState<string | null>(null)
  const [spec, setSpec] = useState<FsmSpec>(EMPTY_SPEC)
  const [selectedIds, setSelectedIds] = useState<Set<string>>(new Set())
  const [menu, setMenu] = useState<MenuState | null>(null)
  const [modal, setModal] = useState<InputModalState | null>(null)
  const [loading, setLoading] = useState(false)
  const [dirty, setDirty] = useState(false)

  /* ---- 目录树 ---- */
  const refreshTrees = useCallback(async () => {
    try {
      const { data } = await getFsmTrees()
      setTrees(data)
    } catch { /* http 已 Toast */ }
  }, [])

  useEffect(() => { refreshTrees() }, [refreshTrees])

  /* ---- 打开 / 新建 / 保存 ---- */
  const openFile = useCallback(async (rel: string) => {
    try {
      setLoading(true)
      const { data } = await getFsmTree(rel)
      const s: FsmSpec = {
        version: data.spec?.version ?? 1,
        name: data.spec?.name ?? '',
        description: data.spec?.description ?? '',
        objects: (data.spec?.objects || []).map((o, i) => ({
          ...o,
          x: typeof o.x === 'number' ? o.x : 80 + i * 60,
          y: typeof o.y === 'number' ? o.y : 80,
        })),
        connections: data.spec?.connections || [],
      }
      setSpec(s)
      setCurrentPath(rel)
      setSelectedIds(new Set())
      setDirty(false)
      // 等节点挂载 + 测量完成后再 fitView（双保险，避免视口漂移导致节点被侧栏遮挡）
      setTimeout(() => { try { rf.fitView({ padding: 0.3 }) } catch { /* */ } }, 120)
      setTimeout(() => { try { rf.fitView({ padding: 0.3 }) } catch { /* */ } }, 400)
      requestAnimationFrame(() => { try { rf.fitView({ padding: 0.3 }) } catch { /* */ } })
    } catch { /* */ } finally {
      setLoading(false)
    }
  }, [rf])

  const doSave = useCallback(async () => {
    if (!currentPath) { Toast.warning('请先新建或打开一个状态机文件'); return }
    try {
      await saveFsmTree(currentPath, spec)
      setDirty(false)
      Toast.success('已保存')
    } catch { /* */ }
  }, [currentPath, spec])

  const doCreateFile = useCallback(async (rel: string) => {
    const r = rel.endsWith('.fsm.json') ? rel : rel + '.fsm.json'
    try {
      await createFsmFile(r)
      await refreshTrees()
      await openFile(r)
      Toast.success(`已创建 ${r}`)
    } catch { /* */ }
  }, [refreshTrees, openFile])

  const doDelete = useCallback(async (rel: string) => {
    try {
      await deleteFsmFile(rel)
      if (currentPath === rel) {
        setCurrentPath(null)
        setSpec(EMPTY_SPEC)
        setSelectedIds(new Set())
        setDirty(false)
      }
      await refreshTrees()
    } catch { /* */ }
  }, [currentPath, refreshTrees])

  /* ---- React Flow 数据（spec 为唯一数据源） ---- */
  // 注意：nodes 依赖 spec 与 selectedIds。
  // onSelectionChange 必须 useCallback 稳定：SelectionListener 的 useEffect 依赖该回调引用，
  // 若内联箭头函数每次 re-render 都是新引用，会导致 onSelectionChange 反复触发 → 死循环。
  const nodes: Node[] = useMemo(
    () => spec.objects.map((obj) => ({
      id: obj.id,
      type: obj.type,
      position: { x: obj.x, y: obj.y },
      width: NODE_W,
      height: NODE_H,
      data: { obj },
      selected: selectedIds.has(obj.id),
    })),
    [spec, selectedIds],
  )

  const edges: Edge[] = useMemo(
    () => spec.connections.map((c) => ({
      id: c.id,
      source: c.from,
      sourceHandle: c.fromPin,
      target: c.to,
      targetHandle: c.toPin,
      data: { fromPin: c.fromPin, toPin: c.toPin },
    })),
    [spec],
  )

  const onNodesChange: OnNodesChange = useCallback((changes) => {
    let objects = spec.objects
    let conns = spec.connections
    let objChanged = false
    let connChanged = false
    for (const ch of changes) {
      if (ch.type === 'position' && ch.position) {
        const obj = objects.find((o) => o.id === ch.id)
        if (obj) { obj.x = ch.position.x; obj.y = ch.position.y; objChanged = true }
      } else if (ch.type === 'remove') {
        objects = objects.filter((o) => o.id !== ch.id)
        conns = conns.filter((c) => c.from !== ch.id && c.to !== ch.id)
        objChanged = true
        connChanged = true
      } else if (ch.type === 'select') {
        setSelectedIds((prev) => {
          const n = new Set(prev)
          if (ch.selected) n.add(ch.id); else n.delete(ch.id)
          return n
        })
      }
    }
    if (objChanged || connChanged) {
      setSpec({ ...spec, objects, connections: conns })
      setDirty(true)
    }
  }, [spec])

  const onEdgesChange: OnEdgesChange = useCallback((changes) => {
    let conns = spec.connections
    let changed = false
    for (const ch of changes) {
      if (ch.type === 'remove') {
        conns = conns.filter((c) => c.id !== ch.id)
        changed = true
      }
    }
    if (changed) { setSpec({ ...spec, connections: conns }); setDirty(true) }
  }, [spec])

  // 选中回调必须稳定引用（见 nodes useMemo 注释），否则 SelectionListener 反复触发形成死循环
  const handleSelectionChange = useCallback(
    ({ nodes: ns }: { nodes: Array<{ id: string }> }) => {
      setSelectedIds(new Set(ns.map((n) => n.id)))
    },
    [],
  )

  const onConnect: OnConnect = useCallback((conn: Connection) => {
    if (!conn.source || !conn.target) return
    const c: FsmConnection = {
      id: uid(),
      from: conn.source,
      fromPin: conn.sourceHandle || '',
      to: conn.target,
      toPin: conn.targetHandle || '',
    }
    setSpec((s) => ({ ...s, connections: [...s.connections, c] }))
    setDirty(true)
  }, [])

  /* ---- 添加对象 ---- */
  const addObject = useCallback((type: FsmObjType, pos: { x: number; y: number }) => {
    const meta = OBJ_META[type]
    const obj: FsmObject = {
      id: uid(), type, name: `${meta.label}${counter.current}`,
      x: Math.round(pos.x), y: Math.round(pos.y),
      ...meta.defaults,
    }
    setSpec((s) => ({ ...s, objects: [...s.objects, obj] }))
    setSelectedIds(new Set([obj.id]))
    setDirty(true)
    // 添加对象后归位视口，保证新节点在画布可视区
    setTimeout(() => { try { rf.fitView({ padding: 0.3 }) } catch { /* */ } }, 150)
  }, [rf])

  /* ---- 修改对象属性 ---- */
  const patchObject = useCallback((id: string, patch: Record<string, any>) => {
    setSpec((s) => ({
      ...s,
      objects: s.objects.map((o) => (o.id === id ? { ...o, ...patch } : o)),
    }))
    setDirty(true)
  }, [])

  /* ---- 右键菜单 ---- */
  const onPaneContextMenu = useCallback((e: React.MouseEvent | MouseEvent) => {
    e.preventDefault()
    const pos = rf.screenToFlowPosition({ x: e.clientX, y: e.clientY })
    setMenu({
      x: e.clientX, y: e.clientY,
      items: OBJ_TYPES.map((t) => ({
        label: `添加${OBJ_META[t].label}`,
        onClick: () => addObject(t, pos),
      })),
    })
  }, [rf, addObject])

  const onNodeContextMenu = useCallback((e: React.MouseEvent, node: Node) => {
    e.preventDefault()
    setMenu({
      x: e.clientX, y: e.clientY,
      items: [{
        label: `删除「${(node.data as any).obj?.name || node.id}」`,
        danger: true,
        onClick: () => {
          setSpec((s) => ({
            ...s,
            objects: s.objects.filter((o) => o.id !== node.id),
            connections: s.connections.filter((c) => c.from !== node.id && c.to !== node.id),
          }))
          setSelectedIds((prev) => { const n = new Set(prev); n.delete(node.id); return n })
          setDirty(true)
        },
      }],
    })
  }, [])

  /* ---- 目录树数据 ---- */
  const treeData = useMemo(() => {
    const root = buildDirTree(trees.dirs, trees.files)
    const build = (node: DirNode, path: string): any[] => {
      const out: any[] = []
      for (const [dn, child] of Object.entries(node.dirs).sort(([a], [b]) => a.localeCompare(b))) {
        const p = path ? `${path}/${dn}` : dn
        out.push({
          key: `dir:${p}`,
          label: (
            <span
              onContextMenu={(e) => {
                e.preventDefault(); e.stopPropagation()
                setMenu({
                  x: e.clientX, y: e.clientY,
                  items: [
                    { label: '新建目录', onClick: () => setModal({ mode: 'dir', title: '新建目录', placeholder: '目录名（可含子路径）', value: p ? `${p}/` : '' }) },
                    { label: '新建文件', onClick: () => setModal({ mode: 'file', title: '新建状态机文件', placeholder: '文件名（自动补 .fsm.json）', value: p ? `${p}/` : '' }) },
                    { label: '重命名', onClick: () => setModal({ mode: 'rename', title: '重命名目录', placeholder: '新目录名', value: dn, relPath: p }) },
                    { label: '删除目录', danger: true, onClick: () => {
                      Modal.confirm({
                        title: '确认删除',
                        content: `将递归删除目录 ${p} 及其中的全部状态机文件，确定？`,
                        okText: '删除', okButtonProps: { theme: 'solid', type: 'danger' } as any,
                        onOk: async () => {
                          try { await deleteFsmDir(p); await refreshTrees() } catch { /* */ }
                        },
                      })
                    } },
                  ],
                })
              }}
              style={{ display: 'inline-block', width: '100%' }}
            >
              📁 {dn}
            </span>
          ),
          children: build(child, p),
        })
      }
      for (const f of node.files.sort((a, b) => a.name.localeCompare(b.name))) {
        out.push({
          key: `file:${f.rel_path}`,
          isLeaf: true,
          label: (
            <span
              onContextMenu={(e) => {
                e.preventDefault(); e.stopPropagation()
                setMenu({
                  x: e.clientX, y: e.clientY,
                  items: [
                    { label: '重命名', onClick: () => setModal({ mode: 'rename', title: '重命名文件', placeholder: '新文件名（含 .fsm.json）', value: f.name, relPath: f.rel_path }) },
                    { label: '删除文件', danger: true, onClick: () => {
                      Modal.confirm({
                        title: '确认删除',
                        content: `删除 ${f.rel_path}？`,
                        okText: '删除', okButtonProps: { theme: 'solid', type: 'danger' } as any,
                        onOk: async () => { await doDelete(f.rel_path) },
                      })
                    } },
                  ],
                })
              }}
              style={{ display: 'inline-block', width: '100%' }}
            >
              ⚙️ {f.name}
            </span>
          ),
        })
      }
      return out
    }
    return build(root, '')
  }, [trees, doDelete, refreshTrees])

  /* ---- 选中对象（检视器） ---- */
  const selectedObj = useMemo(() => {
    if (selectedIds.size !== 1) return null
    return spec.objects.find((o) => o.id === [...selectedIds][0]) || null
  }, [selectedIds, spec.objects])

  const modalConfirm = useCallback(async () => {
    if (!modal) return
    const v = (modal.value || '').trim()
    if (!v) { Toast.warning('请输入名称'); return }
    try {
      if (modal.mode === 'file') {
        await doCreateFile(v)
      } else if (modal.mode === 'dir') {
        await createFsmDir(v)
        await refreshTrees()
        Toast.success(`已创建目录 ${v}`)
      } else if (modal.mode === 'rename' && modal.relPath) {
        await renameFsmEntry(modal.relPath, v)
        if (currentPath === modal.relPath) {
          const parts = modal.relPath.split('/')
          parts[parts.length - 1] = v
          setCurrentPath(parts.join('/'))
        }
        await refreshTrees()
        Toast.success('已重命名')
      }
      setModal(null)
    } catch { /* */ }
  }, [modal, doCreateFile, refreshTrees, currentPath])

  return (
    <div style={{ height: '100%', display: 'flex', flexDirection: 'column' }}>
      {/* 工具栏 */}
      <div style={{
        display: 'flex', alignItems: 'center', gap: 8, padding: '8px 12px',
        background: '#fff', borderBottom: '1px solid #ebeef5', flexShrink: 0,
      }}>
        <IconBranch style={{ color: '#4F6B9A' }} size="large" />
        <span style={{ fontWeight: 600, fontSize: 14 }}>状态机编辑器</span>
        <Tag size="small" color="light-blue">{currentPath || '未打开文件'}</Tag>
        {dirty && <Tag size="small" color="orange">未保存</Tag>}
        <Space style={{ marginLeft: 12 }}>
          <Button size="small" icon={<IconPlus />} onClick={() => setModal({ mode: 'file', title: '新建状态机文件', placeholder: '文件名（可含子目录，自动补 .fsm.json）', value: '' })}>
            新建
          </Button>
          <Button size="small" theme="solid" icon={<IconSave />} disabled={!currentPath} onClick={doSave}>
            保存
          </Button>
        </Space>
        <span style={{ marginLeft: 'auto', fontSize: 12, color: '#999' }}>
          对象 {spec.objects.length} · 连线 {spec.connections.length}
        </span>
      </div>

      <div style={{ flex: 1, display: 'flex', minHeight: 0 }}>
        {/* 左栏：目录树 */}
        <div style={{
          width: 240, background: '#fff', borderRight: '1px solid #ebeef5',
          overflow: 'auto', padding: '8px 4px', flexShrink: 0,
        }}>
          <div style={{ padding: '0 8px 6px', fontSize: 12, color: '#999' }}>状态机文件</div>
          {treeData.length ? (
            <Tree
              treeData={treeData}
              defaultExpandAll
              selectedKey={currentPath ? `file:${currentPath}` : undefined}
              onSelect={(key: string) => {
                if (key?.startsWith('file:')) openFile(key.slice(5))
              }}
              style={{ fontSize: 13 }}
            />
          ) : (
            <Empty title="暂无状态机文件" description="右键或点新建创建" style={{ padding: 24 }} />
          )}
        </div>

        {/* 中栏：画布 */}
        <div style={{ flex: 1, position: 'relative', minWidth: 0 }}>
          {loading && (
            <div style={{
              position: 'absolute', inset: 0, zIndex: 5, background: 'rgba(255,255,255,.6)',
              display: 'flex', alignItems: 'center', justifyContent: 'center',
            }}>
              <Tag color="blue">加载中…</Tag>
            </div>
          )}
          <ReactFlow
            nodes={nodes}
            edges={edges}
            nodeTypes={nodeTypes}
            onNodesChange={onNodesChange}
            onEdgesChange={onEdgesChange}
            onConnect={onConnect}
            onPaneContextMenu={onPaneContextMenu}
            onNodeContextMenu={onNodeContextMenu}
            onSelectionChange={handleSelectionChange}
            fitView
            fitViewOptions={{ padding: 0.3 }}
            deleteKeyCode={['Backspace', 'Delete']}
            multiSelectionKeyCode={['Control', 'Shift']}
            defaultEdgeOptions={{ type: 'default', style: { stroke: '#8A8F98', strokeWidth: 1.5 }, markerEnd: { type: 'arrowclosed', color: '#8A8F98' } }}
            proOptions={{ hideAttribution: true }}
          >
            <Background gap={20} size={1} color="#dfe3e8" />
            <Controls showInteractive={false} />
          </ReactFlow>
          <div style={{
            position: 'absolute', left: 10, bottom: 10, zIndex: 5,
            fontSize: 11, color: '#999', background: 'rgba(255,255,255,.85)',
            padding: '4px 8px', borderRadius: 6, pointerEvents: 'none',
          }}>
            画布空白右键 → 添加对象 · 从 pin 拖出连线 · Delete 删除选中
          </div>
        </div>

        {/* 右栏：检视器 */}
        <div style={{
          width: 300, background: '#fff', borderLeft: '1px solid #ebeef5',
          overflow: 'auto', padding: 12, flexShrink: 0,
        }}>
          {selectedObj ? (
            <>
              <div style={{ fontSize: 13, fontWeight: 600, marginBottom: 10, display: 'flex', alignItems: 'center', gap: 6 }}>
                <span style={{ color: OBJ_META[selectedObj.type].color }}>●</span>
                {OBJ_META[selectedObj.type].label} · {selectedObj.name}
              </div>
              <InspectorForm
                schema={OBJ_META[selectedObj.type].schema}
                value={selectedObj}
                onChange={(patch) => patchObject(selectedObj.id, patch)}
              />
              <div style={{ marginTop: 16 }}>
                <div style={{ fontSize: 12, color: '#999', marginBottom: 6 }}>Pin 点（由对象定义，左入右出）</div>
                <Space spacing={6} wrap>
                  {OBJ_META[selectedObj.type].pins.map((p) => (
                    <Tag key={p.name} size="small" color={p.side === 'in' ? 'blue' : 'green'}>
                      {p.side === 'in' ? '←' : '→'} {p.name}
                    </Tag>
                  ))}
                </Space>
              </div>
            </>
          ) : (
            <Empty
              title={selectedIds.size > 1 ? `${selectedIds.size} 个对象已选中` : '未选中对象'}
              description="在画布上选中一个对象以编辑属性"
              style={{ padding: 24 }}
            />
          )}
        </div>
      </div>

      {/* 右键菜单 */}
      {menu && <ContextMenu menu={menu} onClose={() => setMenu(null)} />}

      {/* 新建/重命名输入弹窗 */}
      <Modal
        title={modal?.title || ''}
        visible={!!modal}
        onCancel={() => setModal(null)}
        onOk={modalConfirm}
        okText="确定"
        cancelText="取消"
        style={{ width: 420 }}
      >
        <Input
          value={modal?.value || ''}
          autoFocus
          placeholder={modal?.placeholder}
          onChange={(v) => setModal((m) => (m ? { ...m, value: v } : m))}
          onEnterPress={modalConfirm}
        />
      </Modal>
    </div>
  )
}

export default function FsmEditor() {
  return (
    <ReactFlowProvider>
      <FsmEditorInner />
    </ReactFlowProvider>
  )
}
