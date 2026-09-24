import { Link } from 'react-router-dom'
import DirectorySelect from '../../components/DirectorySelect'
import { catalogApi, Directory } from '../../api/pointArchive'
import { useEffect, useState } from 'react'
import { Button, Input, Pagination, Select, Table, Tag } from '@douyinfe/semi-ui'
import { FloorOption, PlanStage, planApi } from '../../api/inspectionPlans'

export const floorLabel = (floor: number | null) => floor === null ? '全部楼层（旧计划）' : floor === 0 ? '楼层 0' : floor < 0 ? `B${Math.abs(floor)}` : `${floor}F`

type Props = { robotPk: number; stages: PlanStage[]; options: FloorOption[]; disabled: boolean; onChange: (stages: PlanStage[]) => void; onError: (message: string) => void }

export default function InspectionRouteEditor({ robotPk, stages, options, disabled, onChange, onError }: Props) {
  const [directories, setDirectories] = useState<Directory[]>([])
  const [directory, setDirectory] = useState<string | null>(null)
  useEffect(() => { let alive = true; catalogApi.directories().then(r => { if (alive) setDirectories(r.items) }).catch(() => { if (alive) onError('档案目录加载失败，请重新打开编辑器') }); return () => { alive = false } }, [])
  const [active, setActive] = useState(0)
  const [query, setQuery] = useState('')
  const [page, setPage] = useState(1)
  const [points, setPoints] = useState<{ id: string; name: string; code?: string }[]>([])
  const [total, setTotal] = useState(0)
  const [loading, setLoading] = useState(false)
  const [loadError, setLoadError] = useState('')
  const [retry, setRetry] = useState(0)
  const stage = stages[active]
  useEffect(() => { setPage(1); setQuery('') }, [active, stage?.map_pk, stage?.floor])
  useEffect(() => {
    setPoints([]); setTotal(0); setLoadError('')
    if (!stage) { setLoading(false); return }
    let alive = true; setLoading(true)
    const timer = setTimeout(() => {
      planApi.points(robotPk, stage.map_pk, query, page, stage.floor, directory).then(r => {
        if (alive) { setPoints(r.items); setTotal(r.total) }
      }).catch(e => { if (alive) setLoadError(e.response?.data?.detail || '测点加载失败，请重试') })
        .finally(() => { if (alive) setLoading(false) })
    }, 180)
    return () => { alive = false; clearTimeout(timer) }
  }, [robotPk, stage?.map_pk, stage?.floor, active, query, page, retry, directory])
  const update = (next: PlanStage) => onChange(stages.map((s, i) => i === active ? next : s))
  const add = () => {
    if (!options.length) { onError('当前机器人没有地图，请先配置地图、楼层和航点绑定'); return }
    const option = options.find(o => !stages.some(s => s.map_pk === o.map_pk && s.floor === o.floor)) || options[0]
    onChange([...stages, { map_pk: option.map_pk, floor: option.floor, point_ids: [] }]); setActive(stages.length)
  }
  const move = (offset: number) => {
    const next = [...stages]; const index = active + offset
    if (index < 0 || index >= next.length) return
    ;[next[active], next[index]] = [next[index], next[active]]
    onChange(next); setActive(index)
  }
  return <div className="inspection-route-editor">
    <aside className="inspection-route-sidebar">
      <div className="inspection-section-heading"><strong>巡检顺序</strong><span>{stages.length} 段</span></div>
      <div className="inspection-stage-list">
        {stages.map((s, i) => <button key={i} type="button" disabled={disabled} aria-current={active === i ? 'step' : undefined} className={`inspection-stage ${active === i ? 'is-active' : ''}`} onClick={() => setActive(i)}>
          <span className="inspection-stage-number">{String(i + 1).padStart(2, '0')}</span>
          <span className="inspection-stage-text"><strong>{options.find(o => o.map_pk === s.map_pk)?.map_name || `地图 ${s.map_pk}`}</strong><small>{floorLabel(s.floor)} · {s.point_ids.length} 个测点</small></span>
          {!s.point_ids.length && <span className="inspection-stage-empty">待选</span>}
        </button>)}
      </div>
      <Button block disabled={disabled || stages.length >= 100} onClick={add}>＋ 添加地图 / 楼层</Button>
      <p className="inspection-route-hint">按分段顺序巡检。跨段前确认机器人已到达目标地图和楼层，并完成定位。</p>
    </aside>
    <section className="inspection-point-picker">
      {stage ? <>
        <div className="inspection-section-heading"><strong>第 {active + 1} 段 · 地图与楼层</strong><div className="flex gap-8">
          <Button size="small" disabled={disabled || active === 0} onClick={() => move(-1)}>上移</Button>
          <Button size="small" disabled={disabled || active === stages.length - 1} onClick={() => move(1)}>下移</Button>
          <Button size="small" type="danger" disabled={disabled} onClick={() => { onChange(stages.filter((_, i) => i !== active)); setActive(Math.max(0, active - 1)) }}>移除</Button>
        </div></div>
        <Select aria-label="分段地图和楼层" disabled={disabled} style={{ width: '100%' }} value={`${stage.map_pk}:${stage.floor}`} optionList={[
          ...(stage.floor === null ? [{ value: `${stage.map_pk}:null`, label: '旧计划：请重新指定楼层后选择测点' }] : []),
          ...options.map(o => ({ value: `${o.map_pk}:${o.floor}`, label: `${o.map_name || `地图 ${o.map_pk}`} / ${floorLabel(o.floor)}` })),
        ]} onChange={value => { const [map, floor] = String(value).split(':'); update({ map_pk: Number(map), floor: Number(floor), point_ids: [] }) }} />
        <div className="inspection-directory-filter"><DirectorySelect directories={directories} value={directory} label="筛选计划测点目录" rootLabel="全部档案目录" disabled={disabled} onChange={v => { setDirectory(v); setPage(1) }} /></div>
        <div className="inspection-point-toolbar"><Input placeholder="搜索本段测点名称、编码" value={query} onChange={value => { setQuery(value); setPage(1) }} showClear />
          <Button aria-label="刷新本段测点" size="small" onClick={() => setRetry(v => v + 1)}>刷新</Button><Tag color="blue">已选 {stage.point_ids.length}</Tag><Button size="small" disabled={disabled || !stage.point_ids.length} onClick={() => update({ ...stage, point_ids: [] })}>清空</Button></div>
        {loadError ? <div role="alert" className="inspection-empty">{loadError}<Button onClick={() => setRetry(v => v + 1)}>重试</Button></div> : <Table rowKey="id" loading={loading} dataSource={points} pagination={false} size="small" scroll={{ x: 420, y: 260 }} empty="该地图 / 楼层没有匹配测点，请先启用测点并绑定航点。"
          columns={[{ title: '测点名称', dataIndex: 'name' }, { title: '编码', dataIndex: 'code', width: 160 }]}
          rowSelection={{ selectedRowKeys: stage.point_ids, getCheckboxProps: () => ({ disabled: disabled || loading }), onChange: keys => update({ ...stage, point_ids: [...new Set([...stage.point_ids.filter(id => !points.some(p => p.id === id)), ...(keys || []).map(String)])] }) }} />}
        <div className="inspection-picker-footer"><span>仅显示已启用且绑定本段航点的测点 <Link target="_blank" rel="noopener noreferrer" to={`/sink/waypoint-binding?robot_pk=${robotPk}&map_pk=${stage.map_pk}&floor=${stage.floor ?? 0}`}>管理本段绑定 ↗</Link></span><Pagination size="small" currentPage={page} pageSize={20} total={total} onPageChange={setPage} /></div>
      </> : <div className="inspection-empty"><strong>先添加巡检地图与楼层</strong><p>每一段分别选择测点，支持同一地图的多个楼层。</p><Button theme="solid" disabled={disabled} onClick={add}>添加第一段</Button></div>}
    </section>
  </div>
}
