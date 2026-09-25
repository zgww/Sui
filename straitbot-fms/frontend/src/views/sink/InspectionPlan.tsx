import { useLocation, useNavigate } from 'react-router-dom'
import { useEffect, useRef, useState } from 'react'
import { Banner, Button, Card, Checkbox, Input, Modal, Pagination, Select, Switch, Table, Tag, Toast } from '@douyinfe/semi-ui'
import { IconPlus, IconRefresh } from '@douyinfe/semi-icons'
import { useRobotId } from '../../store/robot'
import { Execution, Occurrence, Plan, PlanStage, FloorOption, PlanPreview, Schedule, planApi } from '../../api/inspectionPlans'

import InspectionRouteEditor, { floorLabel } from './InspectionRouteEditor'
import './inspection-plan.css'

const blankSchedule = (): Schedule => ({ mode: 'manual', timezone: 'Asia/Shanghai', start_date: null, end_date: null, time: '09:00', weekdays: [] })
const errorText = (e: any) => { const d = e.response?.data?.detail; return typeof d === 'string' ? d : Array.isArray(d) ? d.map((x: any) => x.msg).join('；') : e.message || '操作失败' }
const modes = { manual: '手动', once: '单次', daily: '每日', weekly: '每周' }
const states: Record<string, string> = { waiting_transition: '待跨段确认', dispatching: '下发中', accepted: '已接受', running: '运行中', paused: '暂停', suspended: '挂起', done: '已完成', canceled: '已取消', failed: '失败', unknown: '结果待确认', skipped: '已跳过', closed: '已关闭占用' }
const finished = new Set(['done', 'canceled', 'failed', 'skipped', 'closed'])
const formatTime = (s: string | null) => s ? new Date(s.endsWith('Z') ? s : s + 'Z').toLocaleString('zh-CN', { hour12: false }) : '—'

export default function InspectionPlan() {
  const { selectedRid, setSelectedRid } = useRobotId()
  const location = useLocation(), navigate = useNavigate()
  const consumedDraft = useRef<string>()
  const ridRef = useRef(selectedRid); ridRef.current = selectedRid
  const [plans, setPlans] = useState<Plan[]>([])
  const [name, setName] = useState('')
  const [page, setPage] = useState(1)
  const [total, setTotal] = useState(0)
  const [tick, setTick] = useState(0)
  const [loading, setLoading] = useState(false)
  const [busy, setBusy] = useState(false)
  const [error, setError] = useState('')
  const [view, setView] = useState('list')
  const [month, setMonth] = useState(() => { const d = new Date(); return `${d.getFullYear()}-${String(d.getMonth()+1).padStart(2, '0')}` })
  const [occurrences, setOccurrences] = useState<Occurrence[]>([])
  const [maps, setMaps] = useState<FloorOption[]>([])
  const [editor, setEditor] = useState(false)
  const [editing, setEditing] = useState<Plan>()
  const [draftName, setDraftName] = useState('')
  const [stages, setStages] = useState<PlanStage[]>([])
  const [continueExecution, setContinueExecution] = useState<Execution>()
  const [schedule, setSchedule] = useState<Schedule>(blankSchedule)
  const [enabled, setEnabled] = useState(false)
  const [confirmation, setConfirmation] = useState<{ kind: 'delete' | 'execute' | 'preview'; plan: Plan; key: string }>()
  const [routePreview, setRoutePreview] = useState<PlanPreview>()
  const [previewError, setPreviewError] = useState('')
  const [previewLoading, setPreviewLoading] = useState(false)
  const [history, setHistory] = useState<Plan>()
  const [executions, setExecutions] = useState<Execution[]>([])
  const [historyPage, setHistoryPage] = useState(1)
  const [historyTotal, setHistoryTotal] = useState(0)
  const [closeExecution, setCloseExecution] = useState<Execution>()

  useEffect(() => {
    setPlans([]); setMaps([]); setName(''); setPage(1); setError(''); setEditor(false)
    setConfirmation(undefined); setHistory(undefined); setCloseExecution(undefined); setContinueExecution(undefined); setOccurrences([])
  }, [selectedRid])
  useEffect(() => {
    if (!selectedRid) return
    let alive = true
    planApi.floors(selectedRid).then(r => { if (alive) setMaps(r.items) }).catch(e => { if (alive) setError(errorText(e)) })
    return () => { alive = false }
  }, [selectedRid, tick])
  useEffect(() => {
    if (!selectedRid) return
    let alive = true; setLoading(true)
    const timer = setTimeout(() => {
      planApi.list(selectedRid, name, page).then(r => { if (alive) { setPlans(r.items); setTotal(r.total) } })
        .catch(e => { if (alive) { setPlans([]); setError(errorText(e)) } }).finally(() => { if (alive) setLoading(false) })
    }, 200)
    return () => { alive = false; clearTimeout(timer) }
  }, [selectedRid, name, page, tick])
  useEffect(() => {
    if (!selectedRid || view !== 'calendar' || !month) return
    let alive = true
    const [y, m] = month.split('-').map(Number)
    planApi.calendar(selectedRid, new Date(y, m-1, 1).toISOString(), new Date(y, m, 1).toISOString())
      .then(r => { if (alive) setOccurrences(r.items) }).catch(e => { if (alive) setError(errorText(e)) })
    return () => { alive = false }
  }, [selectedRid, month, view, tick])
  useEffect(() => {
    if (!history || history.robot_pk !== selectedRid) return
    let alive = true
    planApi.history(history, historyPage).then(r => { if (alive) { setExecutions(r.items); setHistoryTotal(r.total) } })
      .catch(e => { if (alive) setError(errorText(e)) })
    return () => { alive = false }
  }, [history, historyPage, tick, selectedRid])

  const edit = (p?: Plan) => {
    setEditing(p); setDraftName(p?.name || ''); setStages(p ? (p.stages?.map(s => ({ ...s, point_ids: [...s.point_ids] })) || [{ map_pk: p.map_pk, floor: null, point_ids: [...p.point_ids] }]) : [])
    setSchedule(p ? { ...p.schedule, weekdays: [...p.schedule.weekdays] } : blankSchedule())
    setEnabled(p?.enabled || false)
    setError(''); setEditor(true)
  }
  useEffect(() => {
    const draft = location.state?.bindingDraft as { robotPk: number; name: string; stages: PlanStage[] } | undefined
    if (!draft || consumedDraft.current === location.key) return
    if (selectedRid !== draft.robotPk) { setSelectedRid(draft.robotPk); return }
    consumedDraft.current = location.key
    setEditing(undefined); setDraftName(draft.name); setStages(draft.stages); setSchedule(blankSchedule()); setEnabled(false); setError(''); setEditor(true)
    navigate(location.pathname, { replace: true, state: null })
  }, [location.key, selectedRid])
  useEffect(() => {
    setRoutePreview(undefined); setPreviewError('')
    if (!confirmation || confirmation.kind === 'delete') { setPreviewLoading(false); return }
    let alive = true; setPreviewLoading(true)
    planApi.preview(confirmation.plan).then(r => {
      if (alive) { if (r.version !== confirmation.plan.version) setPreviewError('计划已变更，请关闭弹窗并刷新列表后重试'); else setRoutePreview(r) }
    }).catch(e => { if (alive) setPreviewError(errorText(e)) }).finally(() => { if (alive) setPreviewLoading(false) })
    return () => { alive = false }
  }, [confirmation])
  const perform = async (work: () => Promise<unknown>, done: () => void) => {
    if (busy) return
    const rid = selectedRid; setBusy(true); setError('')
    try { await work(); if (ridRef.current === rid) { done(); setTick(v => v+1) } }
    catch (e) { if (ridRef.current === rid) setError(errorText(e)) }
    finally { setBusy(false) }
  }
  const save = () => {
    if (!selectedRid || !draftName.trim() || !stages.length || stages.some(s => !s.point_ids.length)) { setError('请填写名称，并为每个巡检分段选择测点'); return }
    const legacy = stages.length === 1 && stages[0].floor === null
    if (!legacy && stages.some(s => s.floor === null)) { setError('请为旧计划分段指定楼层并重新选择测点'); return }
    const pointIds = [...new Set(stages.flatMap(s => s.point_ids))]
    perform(() => planApi.save({ robot_pk: selectedRid, map_pk: stages[0].map_pk, stages: legacy ? [] : stages, name: draftName, point_ids: pointIds, schedule, enabled, version: editing?.version || 1 }, editing?.id), () => { setEditor(false); Toast.success('计划已保存') })
  }
  const confirm = () => {
    if (!confirmation) return
    const c = confirmation
    if (c.kind === 'preview') { setConfirmation(undefined); return }
    if (c.kind === 'execute' && !routePreview) return
    perform(async () => {
      if (c.kind === 'delete') await planApi.remove(c.plan)
      else {
        const r = await planApi.execute(c.plan, c.key)
        if (ridRef.current === c.plan.robot_pk) {
          const message = `${states[r.status] || r.status}：${r.message}`
          if (r.status === 'failed') Toast.error(message)
          else if (r.status === 'unknown') Toast.warning(message)
          else Toast.success(message)
          setHistory(c.plan); setHistoryPage(1); setExecutions([r])
        }
      }
    }, () => setConfirmation(undefined))
  }
  const newConfirmation = (kind: 'delete' | 'execute' | 'preview', plan: Plan) => setConfirmation({ kind, plan, key: `${Date.now()}-${Math.random().toString(36).slice(2)}` })
  const scheduleText = (s: Schedule) => s.mode === 'manual' ? '仅手动执行' : `${modes[s.mode]} ${s.time}${s.mode === 'weekly' ? ' · ' + s.weekdays.map(d => '一二三四五六日'[d]).join('、') : ''} (${s.timezone})`
  const cellStyle = { padding: 10, minHeight: 95, border: '1px solid #e4eaf1', background: '#fff', minWidth: 0 }
  const [year, mo] = month.split('-').map(Number)
  const days = new Date(year, mo, 0).getDate()
  const offset = (new Date(year, mo-1, 1).getDay()+6)%7

  if (!selectedRid) return <div className="page-container"><Banner type="info" description="请先在顶部选择机器人，再维护巡检计划。" closeIcon={null} /></div>
  return <div className="page-container inspection-plan">
    {error && <Banner type="danger" description={error} closeIcon={null} style={{ marginBottom: 12 }} />}
    <div className="flex-between" style={{ marginBottom: 12 }}><h2 style={{ margin: 0, fontSize: 18 }}>巡检计划</h2>
      <div className="flex gap-8"><Button icon={<IconRefresh />} onClick={() => setTick(v => v+1)}>刷新</Button><Button theme="solid" icon={<IconPlus />} onClick={() => edit()}>新增计划</Button></div>
    </div>
    <Card>
      <div className="flex-between" style={{ marginBottom: 16 }}>
        <Input placeholder="搜索计划名称" value={name} onChange={v => { setName(v); setPage(1) }} style={{ width: 240 }} />
        <div className="flex gap-8"><Button theme={view === 'list' ? 'solid' : 'light'} onClick={() => setView('list')}>列表</Button><Button theme={view === 'calendar' ? 'solid' : 'light'} onClick={() => setView('calendar')}>日历</Button></div>
      </div>
      {view === 'list' ? <>
        <Table loading={loading} rowKey="id" dataSource={plans} scroll={{ x: 960 }} pagination={false} size="small" empty="当前机器人还没有巡检计划" columns={[
          { title: '计划名称', render: (_: unknown, p: Plan) => <><div className="inspection-plan-name">{p.name}</div><div className="inspection-plan-subline">{p.stages?.length || 1} 段 · {p.point_ids.length} 个测点</div></> },
          { title: '巡检路线', render: (_: unknown, p: Plan) => <div className="inspection-route-summary">{(p.stages || [{ map_pk: p.map_pk, floor: null }]).map((stage, i) => <span key={i}>{i + 1}. {maps.find(m => m.map_pk === stage.map_pk)?.map_name || `地图 ${stage.map_pk}`} / {floorLabel(stage.floor)}</span>)}</div> },
          { title: '排期', render: (_: unknown, p: Plan) => scheduleText(p.schedule) },
          { title: '下次执行', render: (_: unknown, p: Plan) => formatTime(p.next_run_at) },
          { title: '启用', render: (_: unknown, p: Plan) => <Switch checked={p.enabled} disabled={busy} onChange={v => perform(() => planApi.save({ ...p, enabled: v }, p.id), () => Toast.success(v ? '计划已启用' : '计划已停用'))} /> },
          { title: '操作', width: 330, render: (_: unknown, p: Plan) => <div className="flex gap-8" style={{ flexWrap: 'wrap' }}><Button size="small" onClick={() => edit(p)}>编辑</Button><Button size="small" onClick={() => newConfirmation('preview', p)}>预览路线</Button><Button size="small" disabled={!p.enabled || busy} onClick={() => newConfirmation('execute', p)}>立即执行</Button><Button size="small" onClick={() => { setError(''); setHistory(p); setHistoryPage(1); setExecutions([]) }}>历史</Button><Button size="small" type="danger" onClick={() => newConfirmation('delete', p)}>删除</Button></div> },
        ]} />
        <Pagination currentPage={page} pageSize={20} total={total} onPageChange={setPage} style={{ marginTop: 16 }} />
      </> : <>
        <div style={{ marginBottom: 12 }}><input aria-label="日历月份" type="month" value={month} onChange={e => setMonth(e.target.value)} /> <span className="text-muted">显示已启用计划的排期，时间按浏览器本地时区展示</span></div>
        <div style={{ overflowX: 'auto' }}><div style={{ display: 'grid', gridTemplateColumns: 'repeat(7,minmax(120px,1fr))', minWidth: 840 }}>
          {'一二三四五六日'.split('').map(d => <div key={d} style={{ padding: 10, background: '#f3f6fa' }}>周{d}</div>)}
          {Array.from({ length: offset+days }, (_, i) => {
            const day = i-offset+1
            return <div key={i} style={cellStyle}>{day > 0 && <><strong>{day}</strong>{occurrences.filter(o => { const d = new Date(o.at+'Z'); return d.getDate() === day && d.getMonth() === mo-1 }).map(o => <div key={`${o.plan_id}-${o.at}`} style={{ marginTop: 6, padding: 5, background: '#eef4ff', borderRadius: 4, fontSize: 12, overflowWrap: 'anywhere' }}>{new Date(o.at+'Z').toLocaleTimeString('zh-CN', { hour: '2-digit', minute: '2-digit' })} {o.name}</div>)}</>}</div>
          })}
        </div></div>
      </>}
    </Card>
    <Modal title={editing ? '编辑巡检计划' : '新增巡检计划'} visible={editor} className="inspection-editor workflow-modal" width="min(1120px, calc(100vw - 32px))" onCancel={() => { if (!busy) setEditor(false) }} footer={<><span className="inspection-editor-total">{stages.length} 段 · {[...new Set(stages.flatMap(s => s.point_ids))].length} 个测点</span><Button disabled={busy} onClick={() => setEditor(false)}>取消</Button><Button theme="solid" loading={busy} onClick={save}>保存计划</Button></>}>
      {error && <Banner type="danger" description={error} closeIcon={null} />}
      <div className="inspection-editor-top"><label>计划名称<Input placeholder="例如：配电楼全楼巡检" value={draftName} maxLength={128} onChange={setDraftName} disabled={busy} /></label><label>启用计划<div><Switch checked={enabled} onChange={setEnabled} disabled={busy} /> <span className="text-muted">FMS 本地调度</span></div></label></div>
      {editor && <InspectionRouteEditor key={`${selectedRid}-${editing?.id || 'new'}`} robotPk={selectedRid} stages={stages} options={maps} disabled={busy} onChange={setStages} onError={setError} />}
      <div className="inspection-schedule-heading">调度设置</div>
      <div className="inspection-schedule-grid">
        <label>执行方式<Select style={{ width: '100%' }} value={schedule.mode} onChange={v => setSchedule({ ...schedule, mode: v as Schedule['mode'] })} optionList={Object.entries(modes).map(([value, label]) => ({ value, label }))} /></label>
        <div className="inspection-route-hint">保存配置不会立即执行。定时计划由 FMS 发起首段，后续分段在执行历史中确认继续。</div>
        {schedule.mode !== 'manual' && <>
          <label>开始日期<input aria-label="开始日期" type="date" value={schedule.start_date || ''} onChange={e => setSchedule({ ...schedule, start_date: e.target.value || null })} style={{ display: 'block', padding: 6 }} /></label>
          <label>结束日期（可选）<input aria-label="结束日期" type="date" value={schedule.end_date || ''} onChange={e => setSchedule({ ...schedule, end_date: e.target.value || null })} style={{ display: 'block', padding: 6 }} /></label>
          <label>执行时间<input aria-label="执行时间" type="time" value={schedule.time} onChange={e => setSchedule({ ...schedule, time: e.target.value })} style={{ display: 'block', padding: 6 }} /></label>
          <label>时区<Input value={schedule.timezone} onChange={v => setSchedule({ ...schedule, timezone: v })} /></label>
        </>}
      </div>
      {schedule.mode === 'weekly' && <div style={{ marginBottom: 16 }}>{'一二三四五六日'.split('').map((d, i) => <Checkbox key={i} checked={schedule.weekdays.includes(i)} onChange={e => setSchedule({ ...schedule, weekdays: e.target.checked ? [...schedule.weekdays, i].sort() : schedule.weekdays.filter(v => v !== i) })}>周{d}</Checkbox>)}</div>}
    </Modal>
    <Modal className="workflow-modal" width={820} okText={confirmation?.kind === 'execute' ? '确认执行' : confirmation?.kind === 'preview' ? '关闭' : '确认删除'} cancelText="取消" okButtonProps={{ disabled: confirmation?.kind === 'execute' && (!routePreview || previewLoading || !!previewError) }} title={confirmation?.kind === 'execute' ? '立即执行巡检' : confirmation?.kind === 'preview' ? '巡检路线预览' : '删除巡检计划'} visible={!!confirmation} onCancel={() => { if (!busy) setConfirmation(undefined) }} onOk={confirm} confirmLoading={busy}>
      {error && <Banner type="danger" description={error} closeIcon={null} />}
      {confirmation?.kind === 'execute' ? `将向当前机器人发送“${confirmation.plan.name}”，机器人可能开始移动和检测。确认现场允许执行后继续。` : confirmation?.kind === 'preview' ? '依据当前测点档案和绑定关系生成，不下发机器人指令。' : `删除“${confirmation?.plan.name}”并停止未来排期？已下发任务不会被取消，历史记录会保留。`}
      {confirmation?.kind !== 'delete' && <div className="workflow-preview">
        {previewLoading && <p>正在核对测点与航点绑定…</p>}
        {previewError && <Banner type="danger" closeIcon={null} description={<span>{previewError}。请检查测点状态与航点绑定。</span>} />}
        {routePreview?.stages.map((stage, index) => <section key={index}><div className="binding-pane-heading"><strong>第 {index + 1} 段 · {stage.map_name} / {floorLabel(stage.floor)}</strong><span>{stage.point_count} 测点 · {stage.waypoint_count} 航点 · {stage.action_count} 动作</span></div>
          <Table size="small" pagination={{ pageSize: 5 }} rowKey="id" scroll={{ x: 680 }} dataSource={stage.waypoints} columns={[{ title: '航点编号', dataIndex: 'id' }, { title: '关联测点', render: (_: unknown, w: PlanPreview['stages'][number]['waypoints'][number]) => w.point_ids.join('、') }, { title: '执行动作', render: (_: unknown, w: PlanPreview['stages'][number]['waypoints'][number]) => w.actions.map(a => a.steer_point_name || `动作 ${a.id}`).join('、') }]} />
        </section>)}
      </div>}
    </Modal>
    <Modal className="workflow-modal" title={`执行历史 · ${history?.name || ''}`} visible={!!history} width={1050} onCancel={() => setHistory(undefined)} footer={<Button onClick={() => setTick(v => v+1)}>刷新历史</Button>}>
      {error && <Banner type="danger" description={error} closeIcon={null} />}
      <Table rowKey="id" dataSource={executions} scroll={{ x: 860 }} pagination={false} size="small" columns={[
        { title: '创建时间', render: (_: unknown, e: Execution) => formatTime(e.created_at) },
        { title: '触发', render: (_: unknown, e: Execution) => e.trigger === 'manual' ? '手动' : '定时' },
        { title: '执行进度', render: (_: unknown, e: Execution) => <><Tag color={e.status === 'done' ? 'green' : e.status === 'waiting_transition' ? 'amber' : 'blue'}>{states[e.status] || e.status}</Tag><div className="inspection-history-route">第 {e.stage_index + 1} / {e.stages?.length || 1} 段 {e.stages?.[e.stage_index]?.map_name} {e.stages?.[e.stage_index] && floorLabel(e.stages[e.stage_index].floor)}</div></> },
        { title: '说明', dataIndex: 'message' },
        { title: '操作', render: (_: unknown, e: Execution) => !finished.has(e.status) && <div className="flex gap-8">{e.status === 'waiting_transition' && <Button size="small" theme="solid" disabled={busy} onClick={() => { setError(''); setContinueExecution(e) }}>继续下一段</Button>}<Button size="small" disabled={busy} onClick={() => perform(() => planApi.reconcile(e), () => {})}>核对状态</Button><Button size="small" disabled={busy} onClick={() => setCloseExecution(e)}>关闭占用</Button></div> },
      ]} />
      <Pagination currentPage={historyPage} pageSize={20} total={historyTotal} onPageChange={setHistoryPage} style={{ marginTop: 12 }} />
    </Modal>
    <Modal className="workflow-modal" title="确认到达下一段" visible={!!continueExecution} onCancel={() => setContinueExecution(undefined)} confirmLoading={busy} onOk={() => continueExecution && perform(() => planApi.continue(continueExecution), () => { setContinueExecution(undefined); Toast.success('下一段已提交，请查看执行状态') })}>
      {error && <Banner type="danger" description={error} closeIcon={null} />}
      {continueExecution && <><p>下一段：<strong>{continueExecution.stages[continueExecution.stage_index + 1]?.map_name} / {floorLabel(continueExecution.stages[continueExecution.stage_index + 1]?.floor ?? null)}</strong></p><p>请确认机器人已到达该地图 / 楼层并完成定位。确认后将下发该段巡检，机器人可能开始移动。本操作不自动控制乘梯或切换地图。</p></>}
    </Modal>
    <Modal className="workflow-modal" title="核对并关闭本地占用" visible={!!closeExecution} onCancel={() => setCloseExecution(undefined)} confirmLoading={busy} onOk={() => closeExecution && perform(() => planApi.reconcile(closeExecution, true), () => setCloseExecution(undefined))}>
      仅在机器人确认空闲时关闭本地执行占用，不会重发任务，也不代表本次巡检已完成。请先核对现场情况。
    </Modal>
  </div>
}
