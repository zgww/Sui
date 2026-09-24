import { useState, useEffect, useCallback, useRef } from 'react'
import { Row, Col, Card, Tag, Button, List, Progress, Tooltip } from '@douyinfe/semi-ui'
import { IconRefresh } from '@douyinfe/semi-icons'
import dayjs from 'dayjs'
import { fetchRobotControlState, type RobotControlState } from '../api/railRobot'
import { listAlarms, type AlarmRow } from '../api/alarm'
import { useRobotId } from '../store/robot'
import WebRTCPlayer from '../components/WebRTCPlayer'

const LEVEL_COLOR: Record<string, string> = {
  info: 'blue', warning: 'orange', major: 'red', critical: 'red',
  error: 'red', fatal: 'red',
}

export default function Dashboard() {
  const { selectedRid } = useRobotId()
  const [st, setSt] = useState<RobotControlState | null>(null)
  const [alarms, setAlarms] = useState<AlarmRow[]>([])
  const [loading, setLoading] = useState(false)
  const timerRef = useRef<ReturnType<typeof setInterval> | null>(null)

  const loadState = useCallback(async () => {
    try {
      const s = await fetchRobotControlState()
      setSt(s)
    } catch { /* 拦截器已提示 */ }
  }, [])

  const loadAlarms = useCallback(async () => {
    try {
      const { data } = await listAlarms({ page: 1, page_size: 8, status: '' })
      setAlarms(data.items || [])
    } catch { /* */ }
  }, [])

  const load = useCallback(async () => {
    setLoading(true)
    await Promise.all([loadState(), loadAlarms()])
    setLoading(false)
  }, [loadState, loadAlarms])

  useEffect(() => {
    load()
    timerRef.current = setInterval(loadState, 3000)
    const t2 = setInterval(loadAlarms, 10000)
    return () => {
      if (timerRef.current) clearInterval(timerRef.current)
      clearInterval(t2)
    }
  }, [loadState, loadAlarms])

  const online = st?.online
  const bat = st?.battery
  const batPct = bat?.battery_percent ?? 0
  const batColor = batPct <= 20 ? 'red' : batPct <= 40 ? 'orange' : 'green'
  const unack = alarms.filter((a) => a.status === 'unack').length
  const path = st?.state_path?.join(' / ') || '-'

  const envItems = [
    { label: '当前位置 X', value: st ? `${st.pose.x.toFixed(2)} m` : '-', unit: 'm' },
    { label: '运行速度', value: st ? `${Math.abs(st.pose.linear_x).toFixed(2)} m/s` : '-' },
    { label: '当前楼层', value: st?.inspection.current_floor ?? '-' },
    { label: '升降高度', value: st ? `${st.lift.coord_m.toFixed(2)} m` : '-' },
    { label: '电池温度', value: bat ? `${bat.temperature.toFixed(1)} ℃` : '-' },
    { label: '电池电压', value: bat ? `${bat.voltage.toFixed(1)} V` : '-' },
    { label: '电池电流', value: bat ? `${bat.current.toFixed(1)} A` : '-' },
    { label: '充电桩 RFID', value: st?.rfid.rfid ? `#${st.rfid.rfid}` : '未触发' },
  ]

  const statCards = [
    { num: online ? '在线' : '离线', lbl: '机器人状态', color: online ? '#67c23a' : '#f56c6c' },
    { num: `${Math.round(batPct)}%`, lbl: '电量', color: batPct <= 20 ? '#f56c6c' : '#409eff' },
    { num: unack, lbl: '未确认告警', color: unack > 0 ? '#f56c6c' : '#67c23a' },
    { num: st?.inspection.busy ? '巡检中' : '空闲', lbl: '任务状态', color: st?.inspection.busy ? '#e6a23c' : '#909399' },
  ]

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>监控大盘</h2>
        <Button icon={<IconRefresh />} loading={loading} onClick={load}>刷新</Button>
      </div>

      <Row gutter={[12, 12]} className="mb-12">
        {statCards.map((c, i) => (
          <Col xs={12} sm={6} key={i}>
            <Card className="card-shadow stat-card" bordered={false}>
              <div className="num" style={{ color: c.color }}>{c.num}</div>
              <div className="lbl">{c.lbl}</div>
            </Card>
          </Col>
        ))}
      </Row>

      <Row gutter={[12, 12]}>
        {/* 机器人列表 */}
        <Col xs={24} lg={6}>
          <Card className="card-shadow" title="机器人" bordered={false} bodyStyle={{ padding: 12 }}>
            {st ? (
              <div>
                <div style={{ display: 'flex', alignItems: 'center', gap: 8, marginBottom: 8 }}>
                  <span className={`online-dot ${online ? 'dot-on' : 'dot-off'}`} />
                  <strong>{st.name || st.robot_id}</strong>
                  <Tag size="small" color={online ? 'green' : 'grey'}>{st.board_status}</Tag>
                </div>
                <div style={{ fontSize: 13, lineHeight: 2, color: 'var(--semi-color-text-1)' }}>
                  <div>型号：{st.robot_type}</div>
                  <div>地址：{st.ip}:{st.port}</div>
                  <div>状态机：
                    <Tooltip content={path}>
                      <span style={{ wordBreak: 'break-all' }}>{path}</span>
                    </Tooltip>
                  </div>
                  <div>充电：{bat?.charging ? <Tag size="small" color="green">充电中</Tag> : <Tag size="small" color="grey">未充电</Tag>}</div>
                </div>
                <Progress
                  percent={Math.round(batPct)} size="small" style={{ marginTop: 8 }}
                  stroke={batColor}
                />
              </div>
            ) : (
              <span className="text-muted">加载中…</span>
            )}
          </Card>
        </Col>

        {/* 视频监控 */}
        <Col xs={24} lg={12}>
          <Card className="card-shadow" title="视频监控" bordered={false} bodyStyle={{ padding: 8 }}>
            {selectedRid
              ? <WebRTCPlayer rid={selectedRid} autoplay />
              : <span className="text-muted">未选择机器人</span>}
          </Card>
        </Col>

        {/* 告警列表 */}
        <Col xs={24} lg={6}>
          <Card className="card-shadow" title={`告警（最近 ${alarms.length} 条）`} bordered={false} bodyStyle={{ padding: 8 }}>
            <List
              size="small"
              dataSource={alarms}
              style={{ maxHeight: 360, overflow: 'auto' }}
              renderItem={(a: AlarmRow) => (
                <List.Item style={{ padding: '8px 4px' }}>
                  <div style={{ width: '100%' }}>
                    <div style={{ display: 'flex', justifyContent: 'space-between', gap: 6 }}>
                      <span style={{ fontSize: 13 }}>{a.title || a.point_name || a.alarm_type}</span>
                      <Tag size="small" color={(LEVEL_COLOR[a.level] || 'grey') as any}>
                        {a.status === 'unack' ? '未确认' : '已确认'}
                      </Tag>
                    </div>
                    <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)', marginTop: 2 }}>
                      {dayjs(a.triggered_at || a.created_at).format('MM-DD HH:mm')} · {a.point_name || ''}
                    </div>
                  </div>
                </List.Item>
              )}
            />
          </Card>
        </Col>
      </Row>

      {/* 环境 / 设备遥测 */}
      <Card className="card-shadow mt-12" title="环境 / 设备数据" bordered={false}>
        <Row gutter={[12, 12]}>
          {envItems.map((e, i) => (
            <Col xs={12} sm={6} md={3} key={i}>
              <div className="stat-card" style={{ padding: 12 }}>
                <div className="lbl" style={{ fontSize: 12 }}>{e.label}</div>
                <div style={{ fontSize: 20, fontWeight: 600, marginTop: 4, color: 'var(--semi-color-text-0)' }}>
                  {e.value}
                </div>
              </div>
            </Col>
          ))}
        </Row>
      </Card>
    </div>
  )
}
