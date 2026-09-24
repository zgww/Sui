import { useState, useEffect, useRef, useMemo } from 'react'
import { useParams, useNavigate } from 'react-router-dom'
import { Row, Col, Card, Tag, Button, RadioGroup, Radio, Popconfirm, Toast, Spin } from '@douyinfe/semi-ui'
import { IconChevronLeft, IconRefresh, IconSetting } from '@douyinfe/semi-icons'
import * as echarts from 'echarts'
import { useUser } from '../store/user'
import { listRobots, liveStatus, history, cmdHome, cmdCharge, cmdSelfCheck, cmdClearAlert, cmdRestartApp, cmdRebootOs } from '../api/robots'
import type { Robot } from '../types'

const STATUS_MAP: Record<number, string> = { 0: '正常', 1: '开始充电', 2: '充电中', 3: '前往充电', 4: '自检中', 5: '巡检中', 6: '巡检暂停', 7: '巡检挂起', 8: '前往电梯' }

export default function RobotDetail() {
  const { id } = useParams()
  const navigate = useNavigate()
  const user = useUser()
  const rid = Number(id)
  const [robot, setRobot] = useState<Robot | null>(null)
  const [live, setLive] = useState<any>(null)
  const [hours, setHours] = useState(24)
  const [busy, setBusy] = useState(false)
  const [histData, setHistData] = useState<any[]>([])
  const chartRef = useRef<HTMLDivElement>(null)
  const chartInstance = useRef<echarts.ECharts | null>(null)
  const timerRef = useRef<ReturnType<typeof setInterval> | null>(null)

  const st = useMemo(() => live?.data || {}, [live])
  const liveJson = useMemo(() => JSON.stringify(live?.data || {}, null, 2), [live])

  const statusText = (s: number | undefined) => s == null ? '-' : (STATUS_MAP[s] ?? ('状态' + s))

  const loadRobot = async () => {
    const { data } = await listRobots()
    setRobot(data.find((r) => String(r.id) === String(rid)) || data[0])
  }

  const refreshLive = async () => {
    try { const { data } = await liveStatus(rid); setLive(data) } catch { /* */ }
  }

  const loadHistory = async () => {
    try {
      const { data } = await history(rid, hours)
      setHistData(data.status || [])
      renderChart()
    } catch { /* */ }
  }

  const renderChart = () => {
    if (!chartRef.current) return
    if (!chartInstance.current) chartInstance.current = echarts.init(chartRef.current)
    const xs = histData.map((p) => p.ts.slice(5, 16))
    chartInstance.current.setOption({
      tooltip: { trigger: 'axis' },
      legend: { data: ['电量', 'CPU', '温度'] },
      grid: { left: 40, right: 40, bottom: 30, top: 40 },
      xAxis: { type: 'category', data: xs, axisLabel: { fontSize: 10 } },
      yAxis: [{ type: 'value', name: '%', max: 100 }, { type: 'value', name: '°C' }],
      series: [
        { name: '电量', type: 'line', data: histData.map((p) => p.battery), smooth: true, itemStyle: { color: '#67c23a' } },
        { name: 'CPU', type: 'line', data: histData.map((p) => p.cpu), smooth: true, itemStyle: { color: '#409eff' } },
        { name: '温度', type: 'line', yAxisIndex: 1, data: histData.map((p) => p.temperature), smooth: true, itemStyle: { color: '#e6a23c' } },
      ],
    })
  }

  const quick = async (kind: string, arg?: number) => {
    setBusy(true)
    try {
      let r
      if (kind === 'home') r = await cmdHome(rid, true)
      else if (kind === 'charge') r = await cmdCharge(rid, arg!)
      else if (kind === 'selfcheck') r = await cmdSelfCheck(rid)
      else if (kind === 'clear_alert') r = await cmdClearAlert(rid)
      else if (kind === 'restart_app') r = await cmdRestartApp(rid)
      else if (kind === 'reboot_os') r = await cmdRebootOs(rid)
      Toast.success(r?.data?.msg || '已下发')
      setTimeout(refreshLive, 3000)
    } catch { /* */ } finally { setBusy(false) }
  }

  useEffect(() => {
    (async () => {
      await loadRobot()
      await Promise.all([refreshLive(), loadHistory()])
      timerRef.current = setInterval(refreshLive, 10000)
    })()
    const onResize = () => chartInstance.current?.resize()
    window.addEventListener('resize', onResize)
    return () => {
      if (timerRef.current) clearInterval(timerRef.current)
      window.removeEventListener('resize', onResize)
      chartInstance.current?.dispose()
    }
  }, [])

  const statCards = [
    { num: `${st.battery ?? '-'}%`, lbl: '电量' },
    { num: `${st.cpu ?? '-'}%`, lbl: 'CPU' },
    { num: `${st.temperature ?? '-'}°`, lbl: 'CPU温度' },
    { num: statusText(st.status), lbl: st.doing || '-', small: true },
  ]

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <div className="flex gap-8" style={{ alignItems: 'center' }}>
          <Button icon={<IconChevronLeft />} theme="borderless" onClick={() => navigate('/robots')}>返回</Button>
          <h2 style={{ margin: 0 }}>{robot?.name || '...'}</h2>
          {robot && <Tag size="small">{robot.ip}:{robot.api_port}</Tag>}
          {robot && <Tag size="small" color={live?.code === 0 ? 'green' : 'grey'}>{live?.code === 0 ? '在线' : '离线'}</Tag>}
        </div>
        <div className="flex gap-8">
          <Button icon={<IconRefresh />} onClick={refreshLive}>实时刷新</Button>
          {user.isEngineer && <Button icon={<IconSetting />} onClick={() => navigate('/cmd-debug')}>指令调试</Button>}
        </div>
      </div>

      <Row gutter={[12, 12]} className="mb-12">
        {statCards.map((c, i) => (
          <Col xs={12} sm={6} key={i}>
            <Card className="card-shadow stat-card" bordered={false}>
              <div className="num" style={c.small ? { fontSize: 16 } : undefined}>{c.num}</div>
              <div className="lbl">{c.lbl}</div>
            </Card>
          </Col>
        ))}
      </Row>

      <Row gutter={[12, 12]}>
        <Col xs={24} md={12}>
          <Card className="card-shadow mb-12" bordered={false}
            header={
              <div className="flex-between">
                <span>电量 / 温度趋势</span>
                <RadioGroup type="button" value={hours} onChange={(e) => { setHours(Number(e.target.value)); setTimeout(loadHistory, 0) }}>
                  <Radio value={6}>6h</Radio>
                  <Radio value={24}>24h</Radio>
                  <Radio value={168}>7d</Radio>
                </RadioGroup>
              </div>
            }
          >
            <div ref={chartRef} style={{ height: 280 }} />
          </Card>
        </Col>
        <Col xs={24} md={12}>
          <Card className="card-shadow mb-12" title="实时状态(JSON)" bordered={false}>
            <pre className="log-box" style={{ maxHeight: 280 }}>{liveJson}</pre>
          </Card>
        </Col>
      </Row>

      {user.isEngineer && (
        <Card className="card-shadow mb-12" title="快捷指令" bordered={false}>
          <div className="flex gap-8" style={{ flexWrap: 'wrap' }}>
            <Button loading={busy} onClick={() => quick('home')}>返航复位</Button>
            <Button loading={busy} onClick={() => quick('charge', 1)}>开始充电</Button>
            <Button loading={busy} onClick={() => quick('charge', 0)}>停止充电</Button>
            <Button loading={busy} onClick={() => quick('selfcheck')}>自检</Button>
            <Button loading={busy} onClick={() => quick('clear_alert')}>清除告警</Button>
            <Button type="warning" loading={busy} onClick={() => quick('restart_app')}>重启上位机</Button>
            <Popconfirm title="确认重启整机? 机器人将离线约 1 分钟" onConfirm={() => quick('reboot_os')}>
              <Button type="danger">重启整机</Button>
            </Popconfirm>
          </div>
        </Card>
      )}
    </div>
  )
}
