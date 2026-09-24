/**
 * 枚举配置编排 —— 「下拉框里有哪些选项」的配置页。
 *
 * 与「航点树编排」「巡检计划编排」「检测算法编排」是**四棵独立的树**：
 * - 航点树说"每个航点长什么样"；
 * - 计划树说"每天什么时候巡哪些"；
 * - 检测流程说"一个事件从取帧到通知怎么走"；
 * - 本页说"一个下拉框里有哪些可选值"（如告警中心的「类型」筛选）。
 *
 * 一个 `data/prefabs/枚举/*.prefab.json` = **一份枚举配置**，根固定是
 * `EnumNode`（一个 key）下面挂若干 `EnumItemNode`（选项）。告警中心的「类型」
 * 下拉取的就是名为 `告警类型` 的那份。
 *
 * ## 为什么枚举要做成一棵树而不是代码里的常量
 *
 * 告警类型、缺陷类别这些"下拉框里有什么"的清单是**随现场变的业务数据**。
 * 写死在代码里，加一种类型要发一次版本；写死在数据库里，每种枚举都要建一张
 * 表。挂到 prefab 上之后它跟另外三棵树一样可编辑、可导入导出——加一个选项
 * 只是加一个节点。
 *
 * ## 三个字段的分工（改错会很难收拾）
 *
 * `name` 是**机器键**（写进数据库，告警的 `alarm_type` 存的就是它）、`label`
 * 是**显示名**（随便改）、`description` 是**说明**。改 `name` 等于改历史数据
 * 的含义，要改语义请新增一项。
 *
 * 结构操作的规则都在纯函数模块里，本页只做事件接线：
 * - `utils/specTree.ts` —— 树结构通用操作 + 拖拽落点（四棵树共用）；
 * - `utils/enumSpec.ts` —— 枚举树的中文名 / 配色 / 摘要 / 选项提取
 *   （**纯逻辑，不引 Semi**，要被回归脚本直接编译执行）。
 */
import { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import {
  Button, Card, Empty, Input, Modal, Select, Space, Spin, Tag, Toast, Tree,
} from '@douyinfe/semi-ui'
import {
  IconChevronDown, IconChevronUp, IconDelete, IconPlus, IconRefresh, IconSave,
} from '@douyinfe/semi-icons'
import {
  getEnumNodeTypes, listEnumTrees, getEnumTree, saveEnumTree,
  createEnumFile, deleteEnumFile,
} from '../api/enumPrefab'
import type { NodeTypeInfo } from '../api/prefab'
import InspectorForm from '../components/InspectorForm'
import { SEP, parentPathOf } from '../utils/trackSpec'
import {
  getNodeByPath, removeManyByPaths, moveNodeInSpec, resolveDropKind, type DropKind,
} from '../utils/specTree'
import { startDrag } from '../utils/splitter'
import {
  ENUM_TYPE_COLOR, enumNodeLabel, enumNodeSummary, enumTypeLabel,
  findEnumOptions, appendChildNode, insertSiblingNode, defaultsFrom,
} from '../utils/enumSpec'

const MENU_STYLE: React.CSSProperties = {
  position: 'fixed', minWidth: 168, background: '#fff',
  border: '1px solid var(--semi-color-border)', borderRadius: 6,
  boxShadow: '0 6px 20px rgba(0,0,0,.14)', padding: 4, zIndex: 1001, fontSize: 13,
}

interface CtxMenu { x: number; y: number; target: string }

/* ------------------------------------------------------------ 小工具 */

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
  const summary = enumNodeSummary(node)
  const treeNode: any = {
    key: path,
    value: path,
    label: (
      <span style={{ display: 'inline-flex', alignItems: 'center', gap: 6 }}>
        <span>{enumNodeLabel(node)}</span>
        <Tag size="small" color={ENUM_TYPE_COLOR[typeName] || 'grey'}>
          {enumTypeLabel(typeName)}
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

export default function EnumPrefab() {
  const [loading, setLoading] = useState(true)
  const [saving, setSaving] = useState(false)
  const [trees, setTrees] = useState<{ rel_path: string; name: string }[]>([])
  const [currentRel, setCurrentRel] = useState('')
  const [spec, setSpec] = useState<Record<string, any> | null>(null)
  const [nodeTypes, setNodeTypes] = useState<Record<string, NodeTypeInfo>>({})

  const [selectedPath, setSelectedPath] = useState('root')
  const [expandedKeys, setExpandedKeys] = useState<Set<string>>(new Set())
  const [dragPath, setDragPath] = useState<string | null>(null)
  const [ctxMenu, setCtxMenu] = useState<CtxMenu | null>(null)
  const [treeWidth, setTreeWidth] = useState(420)

  const [newFileOpen, setNewFileOpen] = useState(false)
  const [newFileName, setNewFileName] = useState('')
  const [jsonTarget, setJsonTarget] = useState<string | null>(null)
  const specRef = useRef<Record<string, any> | null>(null)
  specRef.current = spec

  /* ------------------------------------------------------------ 载入 */

  const refreshFiles = useCallback(async () => {
    const { data } = await listEnumTrees()
    setTrees(data.trees || [])
    return data.trees || []
  }, [])

  const loadTree = useCallback(async (rel: string) => {
    const { data } = await getEnumTree(rel)
    setCurrentRel(rel)
    setSpec(data.spec)
    setSelectedPath('root')
    setExpandedKeys(new Set(collectParentKeys(data.spec?.root || {})))
  }, [])

  useEffect(() => {
    (async () => {
      try {
        const [list, types] = await Promise.all([refreshFiles(), getEnumNodeTypes()])
        setNodeTypes(types.data || {})
        if (list.length > 0) await loadTree(list[0].rel_path)
      } catch { /* 拦截器已提示 */ } finally { setLoading(false) }
    })()
  }, [refreshFiles, loadTree])

  const treeData = useMemo(() => (spec?.root ? toTreeData(spec.root) : []), [spec])
  const selectedNode = useMemo(
    () => (spec ? getNodeByPath(spec, selectedPath) : null), [spec, selectedPath])
  const selectedSchema = useMemo(
    () => (selectedNode?.type ? nodeTypes[selectedNode.type]?.schema || null : null),
    [selectedNode, nodeTypes])

  /**
   * 当前文件能给出哪些选项——**保存前**就能看到。
   *
   * 下拉框真正取数走 `/api/enum-prefab/options`（后端读全目录），这里是同一套
   * 规则在前端的即时复算（`findEnumOptions` 与后端 `enum_catalog` 口径一致），
   * 目的就是让人在点上「保存」之前先确认"我配出来的就是下拉框会显示的"。
   */
  const preview = useMemo(() => {
    if (!spec?.root) return { key: '', options: [] as { value: string; label: string }[] }
    const stem = (currentRel.split('/').pop() || '')
      .replace(/\.prefab\.json$/i, '')
    const key = String(spec.root?.properties?.name || '').trim() || stem
    const { options } = findEnumOptions(spec, key, stem)
    return { key, options }
  }, [spec, currentRel])

  /* ------------------------------------------------------------ 编辑操作 */

  const patchNodeProps = (path: string, patch: Record<string, any>) => {
    const cur = specRef.current
    if (!cur) return
    const next = JSON.parse(JSON.stringify(cur))
    const node = getNodeByPath(next, path)
    if (!node) return
    node.properties = { ...(node.properties || {}), ...patch }
    setSpec(next)
  }

  /** 添加子节点：`position` 有值时贴着目标插到同一层，否则追加到目标子级末尾 */
  const addChild = (targetPath: string, typeName: string, position?: 'before' | 'after') => {
    const cur = specRef.current
    if (!cur || !typeName) return
    const next = JSON.parse(JSON.stringify(cur))

    let parentPath = targetPath
    let at: number
    if (position && targetPath !== 'root') {
      parentPath = parentPathOf(targetPath)
      const idx = Number(targetPath.split(SEP).pop())
      if (!Number.isInteger(idx)) { Toast.warning('无法确定插入位置，请刷新后重试'); return }
      at = position === 'before' ? idx : idx + 1
    } else {
      at = ((getNodeByPath(next, targetPath)?.children || []) as any[]).length
    }

    const props = defaultsFrom(nodeTypes[typeName]?.schema)
    props.name = `${enumTypeLabel(typeName)} ${at + 1}`
    const node = { type: typeName, properties: props }
    const ok = position && targetPath !== 'root'
      ? insertSiblingNode(next, targetPath, node, position)
      : appendChildNode(next, targetPath, node)
    if (!ok) { Toast.warning('目标节点不存在，请刷新后重试'); return }

    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(parentPath))
    setSelectedPath(`${parentPath}${SEP}children${SEP}${at}`)
  }

  /** 上移 / 下移：复用拖拽那套移动逻辑，保证"摘除后下标修正"只写一处 */
  const moveBy = (path: string, delta: -1 | 1) => {
    const cur = specRef.current
    if (!cur || path === 'root') return
    const parentPath = parentPathOf(path)
    const kids: any[] = getNodeByPath(cur, parentPath)?.children || []
    const idx = Number(path.split(SEP).pop())
    const sibIdx = idx + delta
    if (!Number.isInteger(idx) || sibIdx < 0 || sibIdx >= kids.length) return
    const next = JSON.parse(JSON.stringify(cur))
    const sibPath = `${parentPath}${SEP}children${SEP}${sibIdx}`
    const res = moveNodeInSpec(next.root, path, sibPath, delta < 0 ? 'before' : 'after')
    if (!res.ok) { Toast.warning(res.reason || '无法移动'); return }
    setSpec(next)
    setSelectedPath(sibPath)
  }

  const doDelete = (path: string) => {
    const cur = specRef.current
    if (!cur || path === 'root') { Toast.warning('根节点不可删除'); return }
    const next = JSON.parse(JSON.stringify(cur))
    removeManyByPaths(next.root, [path])
    setSpec(next)
    setSelectedPath('root')
    Toast.success('已删除（保存后落盘）')
  }

  const doSave = async () => {
    const cur = specRef.current
    if (!cur || !currentRel) { Toast.warning('请先新建或选择一个枚举文件'); return }
    setSaving(true)
    try {
      await saveEnumTree(currentRel, cur)
      Toast.success('已保存')
      await refreshFiles()
    } catch { /* 拦截器已提示 */ } finally { setSaving(false) }
  }

  const normRel = (raw: string) => {
    let rel = raw.trim()
    if (!rel.endsWith('.prefab.json')) rel = `${rel.replace(/\.prefab\.json$/i, '')}.prefab.json`
    return rel
  }

  const doCreateFile = async () => {
    const rel = normRel(newFileName)
    if (!rel || rel === '.prefab.json') { Toast.warning('文件名不能为空'); return }
    try {
      await createEnumFile(rel)
      Toast.success('已创建')
      setNewFileOpen(false); setNewFileName('')
      const list = await refreshFiles()
      if (list.some((t: any) => t.rel_path === rel)) await loadTree(rel)
    } catch { /* 拦截器已提示 */ }
  }

  const doDeleteFile = () => {
    if (!currentRel) return
    Modal.confirm({
      title: `删除枚举文件 ${currentRel}`,
      content: '文件会从磁盘删除，不可恢复。确定删除？',
      okType: 'danger',
      onOk: async () => {
        await deleteEnumFile(currentRel)
        Toast.success('已删除')
        setSpec(null); setCurrentRel('')
        await refreshFiles()
      },
    })
  }

  /* ------------------------------------------------------------ 拖拽 */

  const onNodeDrop = (props: any) => {
    const cur = specRef.current
    setDragPath(null)
    if (!cur) return
    const drag: string = props.dragNode?.key || ''
    const target: string = props.node?.key || ''
    if (!drag || !target) return
    const kind: DropKind = resolveDropKind(props)
    const next = JSON.parse(JSON.stringify(cur))
    const res = moveNodeInSpec(next.root, drag, target, kind)
    if (!res.ok) { Toast.warning(res.reason || '无法移动到该位置'); return }
    setSpec(next)
    if (kind === 'on') setExpandedKeys((prev) => new Set(prev).add(target))
    Toast.success('已移动，保存后落盘')
  }

  /* ------------------------------------------------------------ 右键菜单 */

  const menuItems = (() => {
    if (!ctxMenu) return [] as any[]
    const p = ctxMenu.target
    const parentPath = p === 'root' ? '' : parentPathOf(p)
    const kids: any[] = (parentPath ? getNodeByPath(spec, parentPath)?.children
      : []) || []
    const idx = p === 'root' ? -1 : Number(p.split(SEP).pop())
    const canUp = idx > 0
    const canDown = idx >= 0 && idx < kids.length - 1
    return [
      { label: '添加子节点', onClick: () => addChild(p, 'EnumItemNode') },
      ...(p !== 'root'
        ? [
          { label: '在前添加同级项', onClick: () => addChild(p, 'EnumItemNode', 'before') },
          { label: '在后添加同级项', onClick: () => addChild(p, 'EnumItemNode', 'after') },
          { divider: true },
          { label: '上移', disabled: !canUp, onClick: () => moveBy(p, -1) },
          { label: '下移', disabled: !canDown, onClick: () => moveBy(p, 1) },
        ]
        : []),
      { divider: true },
      { label: '查看 JSON 数据', onClick: () => setJsonTarget(p) },
      ...(p !== 'root'
        ? [{ divider: true }, { label: '删除节点', danger: true, onClick: () => doDelete(p) }]
        : []),
    ]
  })()

  const jsonNode = jsonTarget && spec ? getNodeByPath(spec, jsonTarget) : null
  const selStyle: React.CSSProperties = { display: 'block', padding: '2px 4px', borderRadius: 4 }

  if (loading) {
    return <div style={{ display: 'flex', justifyContent: 'center', padding: 80 }}><Spin size="large" /></div>
  }

  return (
    <div className="page-container">
      <div className="mb-12" style={{ display: 'flex', alignItems: 'center', gap: 12, flexWrap: 'wrap' }}>
        <h2 style={{ margin: 0 }}>枚举配置</h2>
        <Select
          value={currentRel || undefined}
          placeholder="选择枚举文件"
          style={{ width: 280 }}
          onChange={(v) => v && loadTree(v as string)}
          optionList={trees.map((t) => ({ label: t.rel_path, value: t.rel_path }))}
        />
        <Space wrap>
          <Button icon={<IconPlus />} onClick={() => { setNewFileName(''); setNewFileOpen(true) }}>新建文件</Button>
          <Button icon={<IconDelete />} disabled={!currentRel} onClick={doDeleteFile}>删除文件</Button>
          <Button icon={<IconRefresh />} onClick={() => refreshFiles()}>刷新列表</Button>
          <Button icon={<IconChevronDown />} onClick={() => setExpandedKeys(new Set(collectParentKeys(spec?.root || {})))}>展开全部</Button>
          <Button icon={<IconChevronUp />} onClick={() => setExpandedKeys(new Set())}>收起全部</Button>
          <Button theme="solid" type="primary" icon={<IconSave />} loading={saving} onClick={doSave}>保存</Button>
        </Space>
      </div>

      <div className="wp3-wrap">
        {/* 左：枚举树 */}
        <div className="wp3-tree" style={{ width: treeWidth }}
          onContextMenu={(e) => {
            e.preventDefault()
            setCtxMenu({ x: e.clientX, y: e.clientY, target: 'root' })
          }}>
          <Card className="card-shadow" bordered={false}
            header={<span style={{ fontWeight: 600 }}>枚举树{currentRel ? ` · ${currentRel}` : '（未选择文件）'}</span>}
            style={{ height: '100%' }}>
            {!spec?.root ? (
              <Empty title="还没有枚举文件"
                description="点「新建文件」建一份（一个文件 = 一份枚举），根节点的「枚举键」就是下拉框引用它的名字，如 告警类型" />
            ) : (
              <>
                <div style={{ marginBottom: 8 }}>
                  <Space wrap>
                    <Tag color="violet" size="small">枚举键：{preview.key || '（未填写）'}</Tag>
                    <Tag color="light-blue" size="small">{preview.options.length} 个选项</Tag>
                  </Space>
                  <div style={{ marginTop: 6, color: 'var(--semi-color-text-2)', fontSize: 12 }}>
                    下拉框预览：{preview.options.length
                      ? preview.options.map((o) => o.label).join(' / ')
                      : '（还没有选项，在根节点上右键「添加子节点」加枚举项）'}
                  </div>
                </div>
                <Tree
                  treeData={treeData}
                  draggable
                  autoExpandWhenDragEnter
                  expandedKeys={[...expandedKeys]}
                  onExpand={(keys: string[]) => setExpandedKeys(new Set(keys))}
                  onSelect={(_k: string, _s: boolean, node: any) => setSelectedPath(node.key || node.value)}
                  onContextMenu={(e: React.MouseEvent, node: any) => {
                    e.preventDefault(); e.stopPropagation()
                    setCtxMenu({ x: e.clientX, y: e.clientY, target: (node?.key || 'root') as string })
                  }}
                  onDragStart={({ node }: any) => setDragPath((node?.key || null) as string | null)}
                  onDragEnd={() => setDragPath(null)}
                  onDrop={onNodeDrop}
                  renderLabel={(label: React.ReactNode, node: any) => (
                    <span
                      style={{
                        ...selStyle,
                        opacity: dragPath === node.key ? 0.45 : 1,
                        outline: dragPath === node.key ? '1px dashed var(--semi-color-primary)' : undefined,
                      }}
                      className={selectedPath === node.key ? 'wp-prefab-node-sel' : undefined}
                    >
                      {label}
                    </span>
                  )}
                />
              </>
            )}
            <div style={{ marginTop: 8, color: 'var(--semi-color-text-2)', fontSize: 12 }}>
              右键加 / 删 / 移节点；拖拽调整顺序（拖到节点中间 = 成为它的子级，拖到上下边缘 = 插到前后）。
              「选项值」是存进数据库的值（改它会改变历史告警的类型），「显示名」只影响下拉框显示。
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
                  <Tag size="small" color={ENUM_TYPE_COLOR[selectedNode.type] || 'blue'}>
                    {enumTypeLabel(selectedNode.type)}
                  </Tag>
                )}
              </div>
            }>
            {!selectedNode ? (
              <Empty title="请选择节点" />
            ) : selectedSchema ? (
              <InspectorForm
                schema={selectedSchema}
                value={{ ...(selectedNode.properties || {}), children: selectedNode.children || [] }}
                onChange={(patch) => {
                  const { children: _c, ...rest } = patch
                  patchNodeProps(selectedPath, rest)
                }}
              />
            ) : (
              <Empty title="未知节点类型" description={`schema 未找到: ${selectedNode.type}`} />
            )}
          </Card>
        </div>
      </div>

      {/* 右键菜单 */}
      {ctxMenu && (
        <div className="en-ctx-root" style={{ position: 'fixed', inset: 0, zIndex: 1000 }}
          onMouseDown={() => setCtxMenu(null)}
          onContextMenu={(e) => { e.preventDefault(); setCtxMenu(null) }}>
          <div className="en-ctx" style={{
            left: Math.min(ctxMenu.x, window.innerWidth - 190),
            top: Math.min(ctxMenu.y, Math.max(8, window.innerHeight - 300)),
            maxHeight: 320, overflowY: 'auto',
            ...MENU_STYLE,
          }}
            onMouseDown={(e) => e.stopPropagation()}
            onContextMenu={(e) => { e.preventDefault(); e.stopPropagation() }}>
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

      {/* 查看 JSON */}
      <Modal title="节点 JSON 数据" visible={jsonTarget !== null}
        onCancel={() => setJsonTarget(null)} footer={null} style={{ width: 620 }}>
        <pre style={{ maxHeight: '60vh', overflow: 'auto', background: 'var(--semi-color-fill-0)', padding: 12, borderRadius: 6, fontSize: 12 }}>
          {jsonNode ? JSON.stringify(jsonNode, null, 2) : ''}
        </pre>
      </Modal>

      {/* 新建文件 */}
      <Modal title="新建枚举文件" visible={newFileOpen}
        onOk={doCreateFile} onCancel={() => setNewFileOpen(false)}
        okText="创建" cancelText="取消" style={{ width: 460 }}>
        <Input autoFocus value={newFileName} onChange={(v) => setNewFileName(v as string)}
          placeholder="文件名，可含子目录，如 告警类型（自动补 .prefab.json）"
          onEnterPress={doCreateFile} />
        <div style={{ marginTop: 8, color: 'var(--semi-color-text-2)', fontSize: 12 }}>
          文件名会作为这份枚举的「枚举键」与「显示名」预填——下拉框按该键取选项，
          所以名字要和引用方（如告警中心的「告警类型」）对得上。
        </div>
      </Modal>
    </div>
  )
}
