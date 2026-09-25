import { useEffect, useMemo, useRef, useState } from 'react'
import { useLocation, useNavigate, Link } from 'react-router-dom'
import { Banner, Button, Input, Modal, Pagination, Select, Table, Tag, Toast } from '@douyinfe/semi-ui'
import { IconPlus, IconRefresh, IconLink, IconMapPin } from '@douyinfe/semi-icons'
import { useRobotId } from '../../store/robot'
import { bindingApi, catalogApi, Binding, BindingOption, Directory, Entity } from '../../api/pointArchive'
import { FloorOption, planApi } from '../../api/inspectionPlans'
import DirectorySelect from '../../components/DirectorySelect'
import { floorLabel } from './InspectionRouteEditor'
import './workflow.css'

const message = (e: any) => typeof e.response?.data?.detail === 'string' ? e.response.data.detail : e.message || '操作失败，请重试'
export default function WaypointBinding() {
  const { selectedRid, setSelectedRid } = useRobotId()
  const location = useLocation(), navigate = useNavigate()
  const params = useMemo(() => new URLSearchParams(location.search), [location.search])
  const robotRef = useRef(selectedRid); robotRef.current = selectedRid
  const [waypoints, setWaypoints] = useState<BindingOption[]>([]), [waypoint, setWaypoint] = useState<BindingOption>()
  const [floors, setFloors] = useState<FloorOption[]>([]), [scope, setScope] = useState('')
  const [name, setName] = useState(''), [page, setPage] = useState(1), [total, setTotal] = useState(0)
  const [bindings, setBindings] = useState<Binding[]>([]), [loading, setLoading] = useState(false), [bindingLoading, setBindingLoading] = useState(false)
  const [error, setError] = useState(''), [modalError, setModalError] = useState(''), [tick, setTick] = useState(0)
  const [open, setOpen] = useState(false), [busy, setBusy] = useState(false), [remove, setRemove] = useState<Binding>()
  const [search, setSearch] = useState(''), [points, setPoints] = useState<Entity[]>([]), [pointPage, setPointPage] = useState(1), [pointTotal, setPointTotal] = useState(0)
  const [selected, setSelected] = useState<Record<string, string>>({}), [action, setAction] = useState<number>(), [pointLoading, setPointLoading] = useState(false)
  const [dirs, setDirs] = useState<Directory[]>([]), [directory, setDirectory] = useState<string | null>(null)
  const [incomingPoint, setIncomingPoint] = useState<string | null>(null)
  const [mapId, floor] = scope ? scope.split(':').map(Number) : []
  const incomingWaypoint = Number(params.get('waypoint_pk')) || undefined

  useEffect(() => {
    const rid = Number(params.get('robot_pk'))
    if (rid > 0 && Number.isInteger(rid)) setSelectedRid(rid)
    setIncomingPoint(params.get('point_id'))
  }, [location.key])
  useEffect(() => {
    setWaypoint(undefined); setWaypoints([]); setBindings([]); setOpen(false); setRemove(undefined)
    setPage(1); setName(''); setError(''); setSelected({}); setTotal(0)
    const sameRobot = !params.get('robot_pk') || Number(params.get('robot_pk')) === selectedRid
    setScope(sameRobot && params.has('map_pk') && params.has('floor') ? `${params.get('map_pk')}:${params.get('floor')}` : '')
  }, [selectedRid, location.key])
  useEffect(() => {
    if (!selectedRid) return
    let alive = true
    planApi.floors(selectedRid).then(r => { if (alive) setFloors(r.items) }).catch(e => { if (alive) setError(message(e)) })
    return () => { alive = false }
  }, [selectedRid, tick])
  useEffect(() => {
    if (!selectedRid) return
    let alive = true; setLoading(true)
    const timer = setTimeout(() => {
      bindingApi.options(name, page, selectedRid, { map_pk: mapId, floor }).then(r => {
        if (alive) { setWaypoints(r.items); setTotal(r.total); setError(''); setWaypoint(w => w ? r.items.find(x => x.id === w.id) || w : r.items.find(x => x.id === incomingWaypoint)) }
      }).catch(e => { if (alive) { setWaypoints([]); setError(message(e)) } }).finally(() => { if (alive) setLoading(false) })
    }, 180)
    return () => { alive = false; clearTimeout(timer) }
  }, [selectedRid, name, page, scope, tick, incomingWaypoint])
  useEffect(() => {
    if (!selectedRid || !incomingWaypoint || (params.get('robot_pk') && Number(params.get('robot_pk')) !== selectedRid)) return
    let alive = true
    bindingApi.options('', 1, selectedRid, { waypoint_pk: incomingWaypoint }).then(r => { if (alive) setWaypoint(r.items[0]) })
      .catch(e => { if (alive) setError(message(e)) })
    return () => { alive = false }
  }, [selectedRid, incomingWaypoint, location.key])
  useEffect(() => {
    setBindings([])
    if (!selectedRid || !waypoint || waypoint.robot_pk !== selectedRid) { setBindingLoading(false); return }
    let alive = true; setBindingLoading(true)
    bindingApi.scopedList(selectedRid, waypoint.id).then(r => { if (alive) setBindings(r.items) })
      .catch(e => { if (alive) setError(message(e)) }).finally(() => { if (alive) setBindingLoading(false) })
    return () => { alive = false }
  }, [selectedRid, waypoint, tick])
  useEffect(() => {
    if (!open) return
    let alive = true
    catalogApi.directories().then(r => { if (alive) setDirs(r.items) }).catch(e => { if (alive) setModalError(message(e)) })
    return () => { alive = false }
  }, [open])
  useEffect(() => {
    if (!open) return
    let alive = true; setPointLoading(true); setPoints([])
    const timer = setTimeout(() => {
      catalogApi.points({ active: true, q: search, directory_id: directory || undefined, page: pointPage, page_size: 20 }).then(r => {
        if (alive) { setPoints(r.items); setPointTotal(r.total) }
      }).catch(e => { if (alive) setModalError(message(e)) }).finally(() => { if (alive) setPointLoading(false) })
    }, 180)
    return () => { alive = false; clearTimeout(timer) }
  }, [open, search, directory, pointPage])
  const alreadyBound = (id: string) => bindings.some(b => b.point_id === id && (b.action_pk ?? undefined) === action)
  const openPicker = () => { setSelected({}); setAction(undefined); setSearch(incomingPoint || ''); setDirectory(null); setPointPage(1); setModalError(''); setOpen(true) }
  const bind = async () => {
    if (!selectedRid || !waypoint || !Object.keys(selected).length || busy) return
    const rid = selectedRid; setBusy(true); setModalError('')
    try {
      await bindingApi.batch(rid, waypoint.id, Object.keys(selected), action)
      if (robotRef.current === rid) { setOpen(false); setIncomingPoint(null); setTick(v => v + 1); Toast.success('绑定已保存，可用于巡检计划') }
    } catch (e) { if (robotRef.current === rid) setModalError(message(e)) } finally { setBusy(false) }
  }
  const unbind = async () => {
    if (!remove || busy) return
    const rid = selectedRid; setBusy(true)
    try { await bindingApi.remove(remove.id); if (robotRef.current === rid) { setRemove(undefined); setTick(v => v + 1); Toast.success('已解除绑定') } }
    catch (e) { if (robotRef.current === rid) setError(message(e)) } finally { setBusy(false) }
  }
  const activePointIds = [...new Set(bindings.filter(b => b.point_active).map(b => b.point_id))]
  const createPlan = () => {
    if (!waypoint) return
    navigate('/sink/inspection-plan', { state: { bindingDraft: { robotPk: selectedRid, name: `${waypoint.name}巡检`,
      stages: [{ map_pk: waypoint.map_pk, floor: waypoint.floor ?? 0, point_ids: activePointIds }] } } })
  }
  if (!selectedRid) return <div className="page-container workflow-page"><Banner type="info" description="请先在顶部选择机器人，再维护航点与测点的绑定关系。" closeIcon={null} /></div>
  return <div className="page-container workflow-page">
    <header className="workflow-page-header"><div><h2>航点绑定测点</h2><p>将测点档案关联到机器人航点或指定动作，再用于巡检计划。</p></div><div className="workflow-actions"><Button onClick={() => navigate('/sink/point-archive')}>测点档案</Button><Button icon={<IconRefresh />} onClick={() => setTick(v => v + 1)}>刷新</Button></div></header>
    {error && <Banner type="danger" description={error} closeIcon={null} />}
    {incomingPoint && <Banner type="info" closeIcon={null} description={`已从档案带入测点 ${incomingPoint}，请选择目标航点后点击“绑定测点”。`} />}
    <div className="binding-workspace">
      <aside className="binding-waypoints"><div className="binding-pane-heading"><strong><IconMapPin /> 选择航点</strong><span>{total} 个</span></div>
        <div className="binding-filters"><Select aria-label="筛选地图和楼层" style={{ width: '100%' }} value={scope} onChange={v => { setScope(String(v)); setPage(1); setWaypoint(undefined) }}
          optionList={[{ value: '', label: '全部地图 / 楼层' }, ...floors.map(f => ({ value: `${f.map_pk}:${f.floor}`, label: `${f.map_name} / ${floorLabel(f.floor)}` }))]} />
          <Input aria-label="搜索航点" placeholder="搜索航点名称或编号" showClear value={name} onChange={v => { setName(v); setPage(1); setWaypoint(undefined) }} /></div>
        <div className="binding-waypoint-list" aria-label="航点列表" aria-busy={loading}>
          {loading ? <div className="workflow-empty">正在加载航点…</div> : waypoints.map(w => <button type="button" key={w.id} className={`binding-waypoint ${waypoint?.id === w.id ? 'is-active' : ''}`} aria-pressed={waypoint?.id === w.id} onClick={() => { setWaypoint(w); setError('') }}>
            <span><strong>{w.name || w.wp_id || `航点 ${w.id}`}</strong><small>{w.map_name} / {floorLabel(w.floor ?? 0)} · {w.actions.length} 个动作</small></span><b>{w.binding_count}<small>测点</small></b></button>)}
          {!loading && !waypoints.length && <div className="workflow-empty">{name || scope ? '没有匹配航点，请调整筛选。' : <>当前机器人没有航点<Link to="/waypoints">前往航点管理</Link></>}</div>}
        </div><Pagination size="small" currentPage={page} pageSize={50} total={total} onPageChange={p => { setPage(p); setWaypoint(undefined) }} />
      </aside>
      <section className="binding-detail"><div className="binding-pane-heading"><div><h3>{waypoint?.name || '选择一个航点'}</h3><p>{waypoint ? `${waypoint.map_name} / ${floorLabel(waypoint.floor ?? 0)} · 航点编号 ${waypoint.wp_id || waypoint.id}` : '左侧按地图、楼层查找航点，右侧维护关联测点。'}</p></div>
        <Button icon={<IconPlus />} theme="solid" disabled={!waypoint || bindingLoading || busy} onClick={openPicker}>绑定测点</Button></div>
        {waypoint && !waypoint.actions.length && <Banner type="warning" closeIcon={null} description="此航点尚无动作，绑定可保存，但配置动作后才能用于巡检执行。" />}
        <Table rowKey="id" loading={bindingLoading} dataSource={bindings} scroll={{ x: 620 }} pagination={{ pageSize: 12 }} size="middle" empty={<div className="workflow-empty"><IconLink size="extra-large" /><strong>{waypoint ? '还没有关联测点' : '等待选择航点'}</strong><span>{waypoint ? '点击“绑定测点”，从档案目录中选择。' : '绑定后，计划会使用此航点的位置与动作。'}</span></div>} columns={[
          { title: '测点档案', render: (_: unknown, b: Binding) => <div className="workflow-entity"><Link to={`/sink/point-archive?point_id=${encodeURIComponent(b.point_id)}`}>{b.point_name}</Link><small>{b.point_id}</small></div> },
          { title: '执行动作', render: (_: unknown, b: Binding) => b.action_name || (b.action_pk ? `动作 ${b.action_pk}` : '整个航点 · 全部动作') },
          { title: '状态', render: (_: unknown, b: Binding) => <Tag color={b.point_active ? 'green' : 'grey'}>{b.point_active ? '已启用' : '已停用'}</Tag> },
          { title: '操作', render: (_: unknown, b: Binding) => <Button theme="borderless" type="danger" disabled={busy} onClick={() => setRemove(b)}>解除绑定</Button> },
        ]} />
        <div className="binding-next-step"><div><strong>用于巡检计划</strong><p>{activePointIds.length} 个已启用测点，可带入当前地图和楼层的巡检分段。</p></div><Button disabled={!waypoint || !activePointIds.length || !waypoint.actions.length || bindingLoading} onClick={createPlan}>用这些测点创建计划</Button></div>
      </section>
    </div>
    <Modal title={`绑定测点 · ${waypoint?.name || ''}`} visible={open} className="workflow-modal binding-modal" width={960} onCancel={() => { if (!busy) setOpen(false) }}
      footer={<><span className="workflow-footer-note">已选 {Object.keys(selected).length} 个测点</span><Button disabled={busy} onClick={() => setOpen(false)}>取消</Button><Button theme="solid" loading={busy} disabled={!Object.keys(selected).length} onClick={bind}>保存绑定</Button></>}>
      {modalError && <Banner type="danger" description={modalError} closeIcon={null} />}
      <div className="binding-picker-filters"><label>绑定到<Select aria-label="绑定动作" value={action ?? 0} disabled={busy} onChange={v => { setAction(Number(v) || undefined); setSelected({}) }} optionList={[{ value: 0, label: '整个航点 · 全部动作' }, ...(waypoint?.actions || []).map(a => ({ value: a.id, label: a.name || `动作 ${a.id}` }))]} /></label>
        <label>档案目录<DirectorySelect directories={dirs} value={directory} rootLabel="全部档案目录" label="筛选档案目录" disabled={busy} onChange={v => { setDirectory(v); setPointPage(1) }} /></label>
        <label>查找测点<Input aria-label="搜索可绑定测点" placeholder="测点名称、编码或 ID" showClear value={search} onChange={v => { setSearch(v); setPointPage(1) }} /></label></div>
      <p className="workflow-hint">只显示已启用的测点；支持跨页选择。选择整个航点时，巡检会执行该航点全部动作。</p>
      <Table rowKey="id" loading={pointLoading} dataSource={points} pagination={false} size="small" scroll={{ x: 660, y: 290 }} empty="没有匹配的已启用测点，请调整目录或搜索条件。"
        columns={[{ title: '测点名称', dataIndex: 'name' }, { title: '所属目录', dataIndex: 'parent_name' }, { title: '编码 / ID', render: (_: unknown, p: Entity) => <span className="text-mono">{p.code || p.id}</span> }, { title: '关联状态', render: (_: unknown, p: Entity) => alreadyBound(p.id) ? <Tag>已绑定此目标</Tag> : '可绑定' }]}
        rowSelection={{ selectedRowKeys: Object.keys(selected), onChange: keys => setSelected(current => {
          const next = { ...current }; points.forEach(p => delete next[p.id]); (keys || []).map(String).forEach(id => { if (!alreadyBound(id)) next[id] = points.find(p => p.id === id)?.name || current[id] || id }); return next
        }), getCheckboxProps: (p: Entity) => ({ disabled: busy || pointLoading || alreadyBound(p.id) }) }} />
      <div className="binding-picker-bottom"><span>共 {pointTotal} 个测点</span><Pagination currentPage={pointPage} pageSize={20} total={pointTotal} onPageChange={setPointPage} /></div>
      {!!Object.keys(selected).length && <div className="binding-selection"><span>已选测点</span>{Object.entries(selected).map(([id, label]) => <Tag key={id} closable onClose={() => setSelected(s => { const next = { ...s }; delete next[id]; return next })}>{label}</Tag>)}<Button size="small" theme="borderless" onClick={() => setSelected({})}>清空选择</Button></div>}
    </Modal>
    <Modal title="解除测点绑定" className="workflow-modal" visible={!!remove} onCancel={() => { if (!busy) setRemove(undefined) }} onOk={unbind} confirmLoading={busy} okType="danger" okText="确认解除" cancelText="取消">
      <p>解除“{remove?.point_name || remove?.point_id}”与当前航点的关联？测点档案和历史任务会保留。</p>
      {!!remove?.plan_names?.length && <Banner type="warning" closeIcon={null} description={`关联计划：${remove.plan_names.join('、')}。解除后请检查计划路线；缺少绑定的计划无法执行。`} />}
      {error && <Banner type="danger" closeIcon={null} description={error} />}
    </Modal>
  </div>
}
