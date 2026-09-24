import { useEffect, useState } from 'react'
import { Link } from 'react-router-dom'
import { Banner, Button, Table, Tag } from '@douyinfe/semi-ui'
import { bindingApi, Binding } from '../../api/pointArchive'
import { useRobotId } from '../../store/robot'

export default function PointArchiveBindings({ pointId, active, onChange }: { pointId: string; active: boolean; onChange: () => void }) {
  const { selectedRid } = useRobotId()
  const [items, setItems] = useState<Binding[]>([]), [loading, setLoading] = useState(false), [error, setError] = useState(''), [tick, setTick] = useState(0)
  useEffect(() => {
    setItems([]); setError('')
    if (!selectedRid) { setLoading(false); return }
    let alive = true; setLoading(true)
    bindingApi.list(pointId, selectedRid).then(r => { if (alive) setItems(r.items) })
      .catch(e => { if (alive) setError(e.response?.data?.detail || '关联加载失败') }).finally(() => { if (alive) setLoading(false) })
    return () => { alive = false }
  }, [pointId, selectedRid, tick])
  const url = `/sink/waypoint-binding?point_id=${encodeURIComponent(pointId)}&robot_pk=${selectedRid}`
  return <section className="archive-binding-section">
    <div className="binding-pane-heading"><div><h3>航点关联</h3><p>仅显示顶部所选机器人的绑定，已绑定测点可用于巡检计划。</p></div><Button size="small" onClick={() => { setTick(t => t + 1); onChange() }}>刷新关联</Button></div>
    {!selectedRid ? <Banner type="info" closeIcon={null} description="请先在顶部选择机器人，再维护测点关联。" /> : <>
      {error && <Banner type="danger" closeIcon={null} description={error} />}
      <Table size="small" rowKey="id" loading={loading} pagination={{ pageSize: 5 }} scroll={{ x: 540 }} dataSource={items} empty="当前机器人尚未关联此测点" columns={[
        { title: '地图 / 航点', render: (_: unknown, b: Binding) => <div>{b.map_name}<strong className="archive-binding-target">{b.waypoint_name}</strong></div> },
        { title: '执行动作', render: (_: unknown, b: Binding) => b.action_name || '整个航点 · 全部动作' },
        { title: '巡检计划', render: (_: unknown, b: Binding) => b.plan_names?.length ? b.plan_names.map(n => <Tag key={n}>{n}</Tag>) : '尚未配置' },
        { title: '操作', render: (_: unknown, b: Binding) => <Link to={`${url}&waypoint_pk=${b.waypoint_pk}`}>管理绑定</Link> },
      ]} />
      {!active && <Banner type="warning" closeIcon={null} description="测点已停用，启用并保存后可新增绑定和加入巡检计划。" />}
      <div className="archive-binding-footer"><span>保存档案后，前往绑定页选择航点或动作。</span><Link className="workflow-link-button" to={url}>前往航点绑定</Link></div>
    </>}
  </section>
}
