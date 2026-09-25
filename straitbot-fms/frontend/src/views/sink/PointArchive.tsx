import React, { useEffect, useMemo, useRef, useState } from 'react'
import { Banner, Button, Modal, Pagination, Switch, Table, Toast } from '@douyinfe/semi-ui'
import { IconChevronDown, IconChevronRight, IconFolder, IconPlus, IconSearch, IconRefresh, IconDownload, IconUpload, IconSetting, IconMore } from '@douyinfe/semi-icons'
import { catalogApi, CatalogKind, Directory, Entity, PlatformCheck, Preview } from '../../api/pointArchive'
import DirectorySelect from '../../components/DirectorySelect'
import { useLocation, useNavigate } from 'react-router-dom'
import PointArchiveBindings from './PointArchiveBindings'
import './point-archive.css'

const roles: Record<string, string> = { custom: '普通目录', station: '变电站', voltage: '电压等级', bay: '间隔', equipment: '设备' }
const assayLabels: Record<number, string> = { 1: '类型 1', 2: '类型 2', 3: '检测类型 3', 4: '检测类型 4', 5: '检测类型 5' }
function message(e: any): string {
  const detail = e.response?.data?.detail
  return typeof detail === 'string' ? detail : detail?.message || e.message || '操作失败，请重试'
}

type Editor = { kind: CatalogKind; row: Entity; mode: 'create' | 'edit' | 'detail'; revision: number }

export default function PointArchive() {
  const navigate = useNavigate(), location = useLocation()
  const focusPoint = new URLSearchParams(location.search).get('point_id')
  const [dirs, setDirs] = useState<Directory[]>([]), [revision, setRevision] = useState<number>(), [allCount, setAllCount] = useState(0)
  const [pointsRevision, setPointsRevision] = useState<number>(), [directoryRevision, setDirectoryRevision] = useState<number>()
  const [selected, setSelected] = useState<string | null>(null), [expanded, setExpanded] = useState<Set<string>>(new Set()), [treeSearch, setTreeSearch] = useState('')
  const [kind, setKind] = useState<CatalogKind>('points'), [rows, setRows] = useState<Entity[]>([]), [total, setTotal] = useState(0)
  const [name, setName] = useState(''), [code, setCode] = useState(''), [active, setActive] = useState('all'), [bound, setBound] = useState('all')
  const [recursive, setRecursive] = useState(true), [page, setPage] = useState(1), [tick, setTick] = useState(0)
  const [loading, setLoading] = useState(true), [busy, setBusy] = useState(false), [error, setError] = useState('')
  const [editor, setEditor] = useState<Editor>(), [formError, setFormError] = useState(''), [extras, setExtras] = useState('{}'), [position, setPosition] = useState('null')
  const [remove, setRemove] = useState<{ kind: CatalogKind; row: Entity; revision: number }>()
  const [importOpen, setImportOpen] = useState(false), [raw, setRaw] = useState(''), [fileName, setFileName] = useState(''), [preview, setPreview] = useState<Preview>(), [importError, setImportError] = useState('')
  const [syncOpen, setSyncOpen] = useState(false), [strictExport, setStrictExport] = useState(false), [check, setCheck] = useState<PlatformCheck>(), [syncError, setSyncError] = useState('')
  const fileInput = useRef<HTMLInputElement>(null), fileSequence = useRef(0)
  const byId = useMemo(() => new Map(dirs.map(d => [d.id, d])), [dirs])
  const children = useMemo(() => {
    const map = new Map<string | null, Directory[]>()
    dirs.forEach(d => { const a = map.get(d.parent_id) || []; a.push(d); map.set(d.parent_id, a) })
    return map
  }, [dirs])
  const current = selected ? byId.get(selected) : undefined
  const ancestors = useMemo(() => {
    const a: Directory[] = []; let d = current
    while (d) { a.push(d); d = d.parent_id ? byId.get(d.parent_id) : undefined }
    return a.reverse()
  }, [current, byId])
  const treeRows = useMemo(() => {
    const result: { d: Directory; depth: number }[] = []
    if (treeSearch.trim()) return dirs.filter(d => d.name.toLocaleLowerCase().includes(treeSearch.toLocaleLowerCase())).map(d => ({ d, depth: 0 }))
    const stack = [...(children.get(null) || [])].reverse().map(d => ({ d, depth: 0 }))
    while (stack.length) {
      const row = stack.pop()!; result.push(row)
      if (expanded.has(row.d.id)) for (const d of [...(children.get(row.d.id) || [])].reverse()) stack.push({ d, depth: row.depth + 1 })
    }
    return result
  }, [dirs, treeSearch, children, expanded])
  const refresh = () => { setTick(t => t + 1); setCheck(undefined) }
  const select = (id: string | null) => { setSelected(id); setPage(1); setName(''); setCode('') }
  useEffect(() => {
    let alive = true
    catalogApi.directories().then(r => {
      if (!alive) return
      setDirs(r.items); setDirectoryRevision(r.revision); setRevision(r.revision); setAllCount(r.point_count)
      setSelected(s => s && !r.items.some(d => d.id === s) ? null : s)
    }).catch(e => { if (alive) setError(message(e)) })
    return () => { alive = false }
  }, [tick])
  useEffect(() => {
    if (kind !== 'points') return
    let alive = true; setLoading(true); setError('')
    const timer = setTimeout(() => {
      catalogApi.points({ directory_id: selected || undefined, recursive, name: name || undefined, code: code || undefined, q: focusPoint || undefined,
        active: active === 'all' ? undefined : active === 'yes', bound: bound === 'all' ? undefined : bound === 'yes', page, page_size: 30 })
        .then(r => { if (alive) { setRows(r.items); setTotal(r.total); setPointsRevision(r.revision); setRevision(r.revision) } })
        .catch(e => { if (alive) { setRows([]); setError(message(e)) } })
        .finally(() => { if (alive) setLoading(false) })
    }, 200)
    return () => { alive = false; clearTimeout(timer) }
  }, [selected, recursive, name, code, active, bound, page, tick, kind, focusPoint])
  const directoryRows = (children.get(selected) || []).filter(d => (!name || d.name.includes(name)) && (!code || d.code === code))
  const openEditor = (entityKind: CatalogKind, row?: Entity, detail = false) => {
    const editorRevision = row ? entityKind === 'points' ? pointsRevision : directoryRevision : revision
    if (!editorRevision) return
    setFormError('')
    const item: Entity = row ? { ...row } : { id: '', name: '', code: '', ...(entityKind === 'directories'
      ? { parent_id: selected, role: 'custom' } : { directory_id: selected, active: true, assay_type: 1, times: 1 }) }
    setEditor({ kind: entityKind, row: item, mode: row ? detail ? 'detail' : 'edit' : 'create', revision: editorRevision })
    setExtras(JSON.stringify(item.extensions || {}, null, 2)); setPosition(JSON.stringify(item.position ?? null, null, 2))
  }
  const setField = (key: string, value: any) => setEditor(e => e ? { ...e, row: { ...e.row, [key]: value } } : e)
  const save = async () => {
    if (!editor) return
    setBusy(true); setFormError('')
    try {
      const item = { ...editor.row }
      if (!item.name.trim()) throw new Error('请填写名称')
      if (!item.id.trim()) throw new Error('请填写稳定 ID')
      if (editor.kind === 'points') {
        item.extensions = JSON.parse(extras)
        if (!item.extensions || Array.isArray(item.extensions) || typeof item.extensions !== 'object') throw new Error('扩展字段必须为 JSON 对象')
        item.position = JSON.parse(position)
      }
      await catalogApi[editor.mode === 'create' ? 'create' : 'update'](editor.kind, item, editor.revision)
      setEditor(undefined); refresh(); Toast.success('档案已保存')
    } catch (e) { setFormError(message(e)) } finally { setBusy(false) }
  }
  const toggle = async (row: Entity) => {
    if (!pointsRevision) return
    setBusy(true)
    try { await catalogApi.update('points', { ...row, active: !row.active }, pointsRevision); refresh() }
    catch (e) { setError(message(e)) } finally { setBusy(false) }
  }
  const deleteItem = async () => {
    if (!remove) return
    setBusy(true)
    try { await catalogApi.remove(remove.kind, remove.row.id, remove.revision); setRemove(undefined); refresh(); Toast.success('已删除，旧版档案已保留') }
    catch (e) { setError(message(e)); setRemove(undefined) } finally { setBusy(false) }
  }
  const validatePlatform = async () => {
    setBusy(true); setSyncError('')
    try { const r = await catalogApi.check(); setCheck(r); return r }
    catch (e) { setSyncError(message(e)); return undefined } finally { setBusy(false) }
  }
  const download = async () => {
    setBusy(true); setError('')
    try {
      if (strictExport) {
        const result = await catalogApi.check(); setCheck(result)
        if (!result.valid) { setSyncOpen(true); return }
      }
      const blob = await catalogApi.export(strictExport)
      const url = URL.createObjectURL(blob), a = document.createElement('a')
      a.href = url; a.download = 'point-archive.json'; document.body.appendChild(a); a.click(); a.remove()
      setTimeout(() => URL.revokeObjectURL(url), 30000)
      Toast.success('静态 JSON 已生成')
    } catch (e) { setError(message(e)) } finally { setBusy(false) }
  }
  const readFile = async (file?: File) => {
    const seq = ++fileSequence.current
    setPreview(undefined); setRaw(''); setImportError(''); setFileName(file?.name || '')
    if (!file) return
    if (file.size > 32 * 1024 * 1024) { setImportError('文件超过32 MB，请拆分后导入'); return }
    try {
      const text = await file.text()
      const r = await catalogApi.preview(text)
      if (seq === fileSequence.current) { setRaw(text); setPreview(r) }
    } catch (e) { if (seq === fileSequence.current) setImportError(message(e)) }
  }
  const publish = async () => {
    if (!preview) return
    setBusy(true); setImportError('')
    try { await catalogApi.publish(raw, preview.revision); setImportOpen(false); setExpanded(new Set()); select(null); refresh(); Toast.success('静态档案已导入') }
    catch (e) { setImportError(message(e)); setPreview(undefined) } finally { setBusy(false) }
  }
  const navigation = (id: string) => {
    const expansion = new Set(expanded); let d = byId.get(id)
    while (d?.parent_id) { expansion.add(d.parent_id); d = byId.get(d.parent_id) }
    setExpanded(expansion); select(id)
  }
  const readOnly = editor?.mode === 'detail'

  return <main className="pa-workspace">
    {focusPoint && <Banner type="info" closeIcon={null} description={<span>正在查看关联测点 <Button theme="borderless" onClick={() => navigate('/sink/point-archive', { replace: true })}>显示全部档案</Button></span>} />}
    <header className="pa-header">
      <div className="pa-header-actions">
        <Button icon={<IconSetting />} onClick={() => { setSyncOpen(true); setSyncError('') }}>同步选项</Button>
        <Button icon={<IconUpload />} onClick={() => { setImportOpen(true); setPreview(undefined); setRaw(''); setFileName(''); setImportError('') }}>导入 JSON</Button>
        <Button icon={<IconDownload />} disabled={busy || !revision} onClick={download}>导出 JSON</Button>
      </div>
    </header>
    {error && <Banner type="danger" closeIcon={null} description={<span>{error} <button className="pa-link" onClick={refresh}>刷新重试</button></span>} />}
    <div className="pa-body">
      <aside className="pa-sidebar">
        <div className="pa-sidebar-title"><strong>档案目录</strong><span>{dirs.length} 个</span><button aria-label="新增根目录" title="新增根目录" onClick={() => { openEditor('directories'); setField('parent_id', null) }} disabled={!revision}><IconPlus /></button></div>
        <div className="pa-tree-search"><IconSearch /><input aria-label="搜索目录" placeholder="查找目录" value={treeSearch} onChange={e => setTreeSearch(e.target.value)} /></div>
        <button className={`pa-root ${selected === null ? 'selected' : ''}`} onClick={() => select(null)}><IconFolder /><span>全部档案</span><b>{allCount}</b></button>
        <div className="pa-tree" role="tree" aria-label="档案目录树">
          {treeRows.map(({ d, depth }) => <div className={`pa-tree-row ${selected === d.id ? 'selected' : ''}`} key={d.id} role="treeitem" aria-level={depth + 1} aria-selected={selected === d.id} aria-expanded={d.child_count ? expanded.has(d.id) : undefined}>
            <div className="pa-tree-indent" style={{ width: Math.min(depth, 12) * 16 }} />
            <button className="pa-expander" aria-label={`${expanded.has(d.id) ? '折叠' : '展开'} ${d.name}`} disabled={!d.child_count} onClick={() => setExpanded(s => { const v = new Set(s); v.has(d.id) ? v.delete(d.id) : v.add(d.id); return v })}>{d.child_count ? expanded.has(d.id) ? <IconChevronDown /> : <IconChevronRight /> : <span />}</button>
            <button className="pa-tree-label" title={`${d.name} · ${roles[d.role]}`} onClick={() => select(d.id)}><IconFolder /><span>{d.name}</span><small>{d.point_count || ''}</small></button>
          </div>)}
          {!treeRows.length && <div className="pa-tree-empty">{treeSearch ? '没有匹配的目录' : '从一个目录开始，按现场需要逐层组织。'}</div>}
        </div>
        <div className="pa-sidebar-foot"><span className="pa-dot" /> 静态档案 · 可跨项目迁移 <small>版本 {revision || '—'}</small></div>
      </aside>
      <section className="pa-content">
        <nav className="pa-breadcrumb" aria-label="目录路径"><button onClick={() => select(null)}>全部档案</button>{ancestors.map(d => <React.Fragment key={d.id}><IconChevronRight /><button onClick={() => navigation(d.id)}>{d.name}</button></React.Fragment>)}</nav>
        <div className="pa-content-title"><div><h2>{current?.name || '全部测点'} {current && <span>{roles[current.role]}</span>}</h2><p>{current ? '管理此目录的测点与子目录，可随时调整所属位置。' : `${allCount} 个测点，${dirs.length} 个目录。目录深度不受固定业务层级限制。`}</p></div>
          <div className="pa-title-actions">{current && <Button theme="borderless" icon={<IconMore />} onClick={() => openEditor('directories', current)}>编辑目录</Button>}<Button icon={<IconPlus />} disabled={!revision} onClick={() => openEditor('directories')}>新增目录</Button><Button theme="solid" icon={<IconPlus />} disabled={!revision} onClick={() => openEditor('points')}>新增测点</Button></div>
        </div>
        <div className="pa-tabs"><button className={kind === 'points' ? 'active' : ''} onClick={() => { setKind('points'); setPage(1) }}>测点列表 <span>{kind === 'points' ? total : ''}</span></button><button className={kind === 'directories' ? 'active' : ''} onClick={() => { setKind('directories'); setPage(1) }}>子目录 <span>{(children.get(selected) || []).length}</span></button><div className="pa-tabs-spacer" />{kind === 'points' && current && <label><input type="checkbox" checked={recursive} onChange={e => { setRecursive(e.target.checked); setPage(1) }} /> 包含下级测点</label>}</div>
        <div className="pa-filters"><div className="pa-filter-search"><IconSearch /><input aria-label="名称筛选" placeholder={kind === 'points' ? '搜索测点名称' : '搜索子目录名称'} value={name} onChange={e => { setName(e.target.value); setPage(1) }} /></div><input aria-label="编码筛选" placeholder="编码精确匹配" value={code} onChange={e => { setCode(e.target.value); setPage(1) }} />
          {kind === 'points' && <><select aria-label="状态筛选" value={active} onChange={e => { setActive(e.target.value); setPage(1) }}><option value="all">全部状态</option><option value="yes">已启用</option><option value="no">已停用</option></select><select aria-label="绑定筛选" value={bound} onChange={e => { setBound(e.target.value); setPage(1) }}><option value="all">全部绑定</option><option value="yes">已绑定航点</option><option value="no">未绑定航点</option></select></>}
          <button className="pa-link" onClick={() => { setName(''); setCode(''); setActive('all'); setBound('all'); setPage(1) }}>重置</button><Button aria-label="刷新档案" title="刷新档案" theme="borderless" icon={<IconRefresh />} onClick={refresh} /></div>
        <div className="pa-table-wrap"><Table rowKey="id" pagination={false} loading={kind === 'points' && loading} dataSource={kind === 'points' ? rows : directoryRows.slice((page - 1) * 30, page * 30)} size="middle"
          empty={<div className="pa-empty"><IconFolder size="extra-large" /><h3>{name || code || active !== 'all' || bound !== 'all' ? '没有匹配的记录' : kind === 'points' ? '这里还没有测点' : '这里还没有子目录'}</h3><p>{name || code ? '调整搜索条件，或清空筛选后重试。' : '可从已有项目导入 JSON，也可以按现场需要新增。'}</p><Button onClick={() => openEditor(kind)} disabled={!revision}>新增{kind === 'points' ? '测点' : '目录'}</Button></div>}
          columns={[
            { title: kind === 'points' ? '测点名称 / ID' : '目录名称 / ID', dataIndex: 'name', width: 230, render: (_: unknown, r: Entity) => <div className="pa-name"><button onClick={() => kind === 'directories' ? navigation(r.id) : openEditor('points', r, true)}>{r.name}</button><small title={r.id}>{r.id}</small></div> },
            { title: '编码', dataIndex: 'code', width: 130, render: (v: string) => <span className="pa-mono">{v || '—'}</span> },
            ...(kind === 'points' ? [
              { title: '所属目录', dataIndex: 'parent_name', width: 150 },
              { title: '检测类型', dataIndex: 'assay_type', width: 110, render: (v: number) => assayLabels[v] || String(v) },
              { title: '状态', dataIndex: 'active', width: 95, render: (v: boolean) => <span className={`pa-status ${v ? '' : 'muted'}`}><i />{v ? '启用' : '停用'}</span> },
              { title: '航点关联', dataIndex: 'bound', width: 100, render: (v: boolean) => <span className={v ? 'pa-bound' : 'pa-muted'}>{v ? '已绑定' : '未绑定'}</span> },
            ] : [
              { title: '平台层级', dataIndex: 'role', width: 130, render: (v: string) => roles[v] },
              { title: '直接子目录', dataIndex: 'child_count', width: 110 },
              { title: '直属测点', dataIndex: 'point_count', width: 100 },
            ]),
            { title: '操作', width: kind === 'points' ? 180 : 130, fixed: 'right' as const, render: (_: unknown, r: Entity) => <div className="pa-row-actions"><button disabled={busy} onClick={() => openEditor(kind, r)}>编辑</button>{kind === 'points' && <button disabled={busy} onClick={() => toggle(r)}>{r.active ? '停用' : '启用'}</button>}<button className="danger" disabled={busy || !revision} onClick={() => setRemove({ kind, row: r, revision: (kind === 'points' ? pointsRevision : directoryRevision)! })}>删除</button></div> },
          ]} scroll={{ x: 1030, y: 'max(260px, calc(100vh - 400px))' }} /></div>
        <div className="pa-pagination"><span>{kind === 'points' ? total : directoryRows.length} 条记录 · 每页 30 条</span><Pagination total={kind === 'points' ? total : directoryRows.length} currentPage={page} pageSize={30} onPageChange={setPage} showSizeChanger={false} /></div>
      </section>
    </div>
    <Modal className="pa-modal workflow-modal" title={`${editor?.mode === 'create' ? '新增' : readOnly ? '查看' : '编辑'}${editor?.kind === 'directories' ? '目录' : '测点'}`} visible={!!editor} width={760} onCancel={() => { if (!busy) setEditor(undefined) }} footer={<><Button disabled={busy} onClick={() => setEditor(undefined)}>{readOnly ? "关闭" : "取消"}</Button>{!readOnly && <Button theme="solid" loading={busy} onClick={save}>保存档案</Button>}</>} onOk={save} okText="保存档案" cancelText="取消" confirmLoading={busy}>
      {formError && <Banner type="danger" description={formError} closeIcon={null} />}
      {editor && <>
        <div className="pa-form-grid">
          <label>名称 <b>*</b><input aria-label="名称" disabled={readOnly} value={editor.row.name} onChange={e => setField('name', e.target.value)} maxLength={256} /></label>
          <label>稳定 ID <b>*</b><input aria-label="稳定 ID" disabled={editor.mode !== 'create'} value={editor.row.id} placeholder="如 point-001，跨项目保持一致" onChange={e => setField('id', e.target.value)} maxLength={256} /></label>
          <label>编码<input aria-label="编码" disabled={readOnly} value={editor.row.code || ''} onChange={e => setField('code', e.target.value)} /></label>
          <label>{editor.kind === 'directories' ? '上级目录' : '所属目录'}<DirectorySelect directories={dirs} disabled={readOnly}
            label={editor.kind === 'directories' ? '上级目录' : '所属目录'}
            value={editor.row[editor.kind === 'directories' ? 'parent_id' : 'directory_id']}
            excludeId={editor.kind === 'directories' && editor.mode !== 'create' ? editor.row.id : undefined}
            onChange={id => setField(editor.kind === 'directories' ? 'parent_id' : 'directory_id', id)} /></label>
          {editor.kind === 'directories' ? <label className="pa-form-wide">平台层级（可选）<select aria-label="平台层级" disabled={readOnly} value={editor.row.role || 'custom'} onChange={e => setField('role', e.target.value)}>{Object.entries(roles).map(([v, l]) => <option key={v} value={v}>{l}</option>)}</select><small>自由建档无需匹配层级；向机器人管理平台同步前，再按标准层级校验。</small></label> : <>
            <label>检测类型代码<input aria-label="检测类型代码" type="number" min={1} max={5} disabled={readOnly} value={editor.row.assay_type ?? 1} onChange={e => setField('assay_type', Number(e.target.value))} /></label>
            <label>检测次数<input aria-label="检测次数" type="number" min={1} max={1000} disabled={readOnly} value={editor.row.times ?? 1} onChange={e => setField('times', Number(e.target.value))} /></label>
            <label>表计类型代码<input aria-label="表计类型代码" type="number" min={0} disabled={readOnly} value={editor.row.meter_type ?? ''} onChange={e => setField('meter_type', e.target.value === '' ? null : Number(e.target.value))} /></label>
            <label>单位<input aria-label="单位" disabled={readOnly} value={editor.row.unit || ''} onChange={e => setField('unit', e.target.value)} /></label>
            <label>量程<input aria-label="量程" disabled={readOnly} value={editor.row.scope || ''} onChange={e => setField('scope', e.target.value)} /></label>
            <label>告警设置<input aria-label="告警设置" disabled={readOnly} value={editor.row.warn_setting || ''} onChange={e => setField('warn_setting', e.target.value)} /></label>
            <label className="pa-switch-label">启用测点<Switch aria-label="启用测点" disabled={readOnly} checked={editor.row.active !== false} onChange={v => setField('active', v)} /></label>
            <details className="pa-form-wide"><summary>高级配置 · 位置与扩展字段</summary><label>位置 JSON<textarea aria-label="位置 JSON" disabled={readOnly} rows={3} value={position} onChange={e => setPosition(e.target.value)} /></label><label>扩展字段 JSON<textarea aria-label="扩展字段 JSON" disabled={readOnly} rows={4} value={extras} onChange={e => setExtras(e.target.value)} /></label></details>
          </>}
        </div>
        {editor.kind === 'points' && editor.mode !== 'create' && <PointArchiveBindings pointId={editor.row.id} active={editor.row.active !== false} onChange={refresh} />}
      </>}
    </Modal>
    <Modal className="workflow-modal" title="删除档案" visible={!!remove} onCancel={() => { if (!busy) setRemove(undefined) }} onOk={deleteItem} confirmLoading={busy} okType="danger" okText="确认删除" cancelText="取消"><p>确认删除「{remove?.row.name}」？</p><p className="pa-muted">有内容的目录或被绑定、被历史任务引用的测点不能删除。发布前的档案版本会保留。</p></Modal>
    <Modal title="导入静态 JSON" className="pa-modal workflow-modal" visible={importOpen} width={660} onCancel={() => { if (!busy) { fileSequence.current++; setImportOpen(false) } }} onOk={publish} okText="确认替换并导入" cancelText="取消" okButtonProps={{ disabled: !preview }} confirmLoading={busy}>
      <p className="pa-modal-intro">将其他项目导出的档案移植到当前项目。目录、测点与扩展配置一并保留；机器人连接和本地航点绑定不随文件迁移。</p>
      <div className="pa-upload"><IconUpload size="extra-large" /><strong>{fileName || '选择一份档案文件'}</strong><span>UTF-8 JSON · 最大 32 MB · 兼容上一版档案</span><Button disabled={busy} onClick={() => fileInput.current?.click()}>选择 JSON 文件</Button><input ref={fileInput} type="file" accept=".json,application/json" hidden onChange={e => { readFile(e.target.files?.[0]); e.target.value = '' }} /></div>
      {importError && <Banner type="danger" description={importError} closeIcon={null} />}
      {preview && <><div className="pa-import-stats"><div><strong>{String(preview.changes.added)}</strong><span>新增记录</span></div><div><strong>{String(preview.changes.updated)}</strong><span>更新记录</span></div><div><strong>{String(preview.changes.removed)}</strong><span>移除记录</span></div></div><Banner type="warning" closeIcon={null} description={preview.warnings.join(' ')} /><p className="pa-muted">预览完成，尚未修改档案。确认后替换当前版本 {preview.revision}。</p></>}
    </Modal>
    <Modal title="机器人管理平台同步选项" className="pa-modal workflow-modal" visible={syncOpen} width={680} onCancel={() => { if (!busy) setSyncOpen(false) }} footer={<><Button onClick={() => setSyncOpen(false)}>关闭</Button><Button theme="solid" loading={busy} onClick={validatePlatform}>校验当前档案</Button></>}>
      <div className="pa-sync-rule"><strong>变电站 <span>→</span> 电压等级 <span>→</span> 间隔 <span>→</span> 设备 <span>→</span> 测点</strong><p>只在准备同步时要求层级一致，日常目录可以自由组织。</p></div>
      <label className="pa-sync-toggle"><div><strong>导出前执行平台层级校验</strong><p>开启后，不符合标准层级的档案将不能导出。本次页面会话有效。</p></div><Switch aria-label="导出前执行平台层级校验" checked={strictExport} onChange={setStrictExport} /></label>
      <p className="pa-muted">此处仅校验档案、生成静态文件，不向机器人管理平台发送数据。</p>
      {syncError && <Banner type="danger" description={syncError} closeIcon={null} />}
      {check && <><Banner type={check.valid ? 'success' : 'warning'} closeIcon={null} description={`${check.message}${check.issues.length ? `（${check.issues.length} 项）` : ''}`} /><div className="pa-issues">{check.issues.map((issue, i) => <div key={`${issue.kind}-${issue.id}-${i}`}><strong>{issue.name}</strong><span>{issue.message}</span></div>)}</div></>}
    </Modal>
  </main>
}
