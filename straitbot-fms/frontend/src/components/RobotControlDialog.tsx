import { useState, useEffect, useRef } from 'react'
import { Card, Button, InputNumber, Tag, Popconfirm, Toast, Descriptions, Tabs, TabPane } from '@douyinfe/semi-ui'
import {
  IconArrowUp, IconArrowDown, IconArrowLeft, IconArrowRight,
  IconStop, IconRefresh, IconPlus, IconMinus, IconCamera,
} from '@douyinfe/semi-icons'
import FloatPanel from './FloatPanel'
import { liveStatus } from '../api/robots'
import { motionMove, motionEStop, motionSetPose, motionHome, ptzSetPose, ptzAction, liftControl, liftStatus } from '../api/control'

interface Props {
  visible: boolean
  rid: number | null
  robotName?: string
  onClose: () => void
}

interface Pose {
  x: number
  y: number
  theta: number
}

interface Ptz {
  pan: number
  tilt: number
  zoom: number
}

const STATUS_MAP: Record<number, string> = {
  0: '正常', 1: '开始充电', 2: '充电中', 3: '前往充电',
  4: '自检中', 5: '巡检中', 6: '巡检暂停', 7: '巡检挂起', 8: '前往电梯',
}

const holdBtnStyle: React.CSSProperties = {
  width: 44,
  height: 44,
  borderRadius: '50%',
  border: '2px solid #dcdfe6',
  background: '#409eff',
  color: '#fff',
  display: 'flex',
  alignItems: 'center',
  justifyContent: 'center',
  cursor: 'pointer',
  userSelect: 'none',
  WebkitUserSelect: 'none',
  WebkitTapHighlightColor: 'transparent',
  transition: 'all .1s',
  touchAction: 'none',
  padding: 0,
}

const ptzBtnStyle: React.CSSProperties = {
  ...holdBtnStyle,
  width: 36,
  height: 36,
  background: '#67c23a',
}

const statusText = (s: number | undefined | null) =>
  s == null ? '-' : (STATUS_MAP[s] ?? ('状态' + s))

export default function RobotControlDialog({ visible, rid, robotName, onClose }: Props) {
  const [live, setLive] = useState<any>(null)
  const [pose, setPose] = useState<Pose>({ x: 0, y: 0, theta: 0 })
  const [ptz, setPtz] = useState<Ptz>({ pan: 0, tilt: 0, zoom: 0 })
  const [liftHeight, setLiftHeight] = useState(1)
  const [liftSt, setLiftSt] = useState<any>(null)
  const stopTimer = useRef<ReturnType<typeof setTimeout> | null>(null)
  const timerRef = useRef<ReturnType<typeof setInterval> | null>(null)

  const st = live?.data || {}

  const refreshLive = async () => {
    if (!rid) return
    try {
      const { data } = await liveStatus(rid)
      setLive(data)
    } catch { /* */ }
    try {
      const { data: ls } = await liftStatus(rid)
      setLiftSt(ls)
    } catch { /* */ }
  }

  /** 从实时状态同步云台位姿到 ptz state (用于初始加载和命令执行后) */
  const syncPtzFromLive = async () => {
    if (!rid) return
    try {
      const { data } = await liveStatus(rid)
      setLive(data)
      const livePtz = data?.data?.pose?.ptz
      if (livePtz) {
        setPtz({
          pan: Number(livePtz.pan) || 0,
          tilt: Number(livePtz.tilt) || 0,
          zoom: Number(livePtz.zoom) || 0,
        })
      }
    } catch { /* */ }
  }

  useEffect(() => {
    if (!visible || !rid) {
      if (timerRef.current) { clearInterval(timerRef.current); timerRef.current = null }
      return
    }
    refreshLive()
    syncPtzFromLive()
    timerRef.current = setInterval(refreshLive, 3000)
    return () => {
      if (timerRef.current) { clearInterval(timerRef.current); timerRef.current = null }
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [visible, rid])

  useEffect(() => {
    if (!visible) {
      setLive(null)
      if (timerRef.current) { clearInterval(timerRef.current); timerRef.current = null }
    }
  }, [visible])

  // ===== 运动控制 =====
  const holdMove = async (cmd: number) => {
    if (!rid) return
    if (stopTimer.current) clearTimeout(stopTimer.current)
    try { await motionMove(rid, cmd) } catch { /* */ }
  }

  const stopMove = async () => {
    if (!rid) return
    if (stopTimer.current) clearTimeout(stopTimer.current)
    stopTimer.current = setTimeout(async () => {
      try { await motionMove(rid, 0) } catch { /* */ }
    }, 100)
  }

  const estop = async () => {
    if (!rid) return
    try {
      const { data } = await motionEStop(rid, true)
      Toast.warning(data?.msg || '急停已触发')
      setTimeout(refreshLive, 500)
    } catch { /* */ }
  }

  const home = async () => {
    if (!rid) return
    try {
      const { data } = await motionHome(rid, true)
      Toast.success(data?.msg || '已下发返航')
      setTimeout(refreshLive, 1000)
    } catch { /* */ }
  }

  const setPoseFn = async () => {
    if (!rid) return
    try {
      const { data } = await motionSetPose(rid, pose)
      Toast.success(data?.msg || '已下发')
    } catch { /* */ }
  }

  const btnProps = (cmd: number) => ({
    onMouseDown: () => holdMove(cmd),
    onMouseUp: stopMove,
    onMouseLeave: stopMove,
    onTouchStart: (e: React.TouchEvent) => { e.preventDefault(); holdMove(cmd) },
    onTouchEnd: (e: React.TouchEvent) => { e.preventDefault(); stopMove() },
    disabled: !rid,
  })

  // ===== 云台控制 =====
  const holdPtz = async (cmd: number) => {
    if (!rid) return
    if (stopTimer.current) clearTimeout(stopTimer.current)
    try { await ptzAction(rid, { command: cmd, stop: false }) } catch { /* */ }
  }

  /** 停止云台移动 (发送相同方向 + stop=true, 而非 command=0 复位) */
  const stopPtz = (cmd: number) => {
    if (!rid) return
    if (stopTimer.current) clearTimeout(stopTimer.current)
    stopTimer.current = setTimeout(async () => {
      try { await ptzAction(rid, { command: cmd, stop: true }) } catch { /* */ }
    }, 100)
  }

  const ptzBtnProps = (cmd: number) => ({
    onMouseDown: () => holdPtz(cmd),
    onMouseUp: () => stopPtz(cmd),
    onTouchStart: (e: React.TouchEvent) => { e.preventDefault(); holdPtz(cmd) },
    onTouchEnd: (e: React.TouchEvent) => { e.preventDefault(); stopPtz(cmd) },
    disabled: !rid,
  })

  const zoomStep = async (dir: 'in' | 'out') => {
    if (!rid) return
    const newZoom = dir === 'in' ? ptz.zoom + 0.5 : Math.max(0, ptz.zoom - 0.5)
    setPtz((p) => ({ ...p, zoom: newZoom }))
    try {
      await ptzSetPose(rid, { ...ptz, zoom: newZoom })
      setTimeout(syncPtzFromLive, 1000)
    } catch { /* */ }
  }

  const ptzReset = async () => {
    if (!rid) return
    try {
      await ptzAction(rid, { command: 0, stop: false })
      setPtz({ pan: 0, tilt: 0, zoom: 0 })
      Toast.success('云台已复位')
      setTimeout(syncPtzFromLive, 1000)
    } catch { /* */ }
  }

  const setPtzField = (k: keyof Ptz, v: any) =>
    setPtz((p) => ({ ...p, [k]: v == null ? 0 : Number(v) }))

  const setPtzPose = async () => {
    if (!rid) return
    try {
      const { data } = await ptzSetPose(rid, ptz)
      Toast.success(data?.msg || '已下发')
      setTimeout(syncPtzFromLive, 1000)
    } catch { /* */ }
  }

  // ===== 升降杆控制 =====
  const liftCmd = async (cmd: number, h?: number) => {
    if (!rid) return
    try {
      const { data } = await liftControl(rid, cmd, h || 0)
      Toast.success(data?.msg || '已下发')
    } catch { /* */ }
  }

  const setPoseField = (k: keyof Pose, v: any) =>
    setPose((p) => ({ ...p, [k]: v == null ? 0 : Number(v) }))

  const fieldGrid: React.CSSProperties = {
    display: 'grid', gridTemplateColumns: '60px 1fr', rowGap: 6, alignItems: 'center',
  }

  return (
    <FloatPanel visible={visible} title={`机器人控制${robotName ? ' - ' + robotName : ''}`} onClose={onClose} width={420}>
      {/* 状态信息 */}
      <Card className="mb-8" bordered={false} style={{ background: '#f5f7fa' }}
        header={
          <div style={{ display: 'flex', alignItems: 'center', gap: 8, fontSize: 13 }}>
            <span>状态</span>
            <Tag size="small" color={live?.code === 0 ? 'green' : 'grey'}>
              {live?.code === 0 ? '在线' : (live ? '离线' : '读取中')}
            </Tag>
            {st.battery != null && <Tag size="small" color="blue">{st.battery}%</Tag>}
            <Button size="small" theme="borderless" icon={<IconRefresh />} onClick={refreshLive} />
          </div>
        }
        bodyStyle={{ padding: '8px 12px' }}
      >
        {!live ? (
          <div className="text-muted" style={{ fontSize: 12 }}>正在读取状态...</div>
        ) : (
          <Descriptions size="small" row data={[
            { key: '状态', value: `${st.status ?? '-'} (${statusText(st.status)})` },
            { key: '位置', value: `(${st.pose?.point?.x != null ? Number(st.pose.point.x).toFixed(2) : '-'}, ${st.pose?.point?.y != null ? Number(st.pose.point.y).toFixed(2) : '-'}) θ=${st.pose?.theta != null ? Number(st.pose.theta).toFixed(1) : '-'}` },
            { key: 'CPU/温', value: `${st.cpu != null ? Number(st.cpu).toFixed(1) : '-'}% / ${st.temperature != null ? Number(st.temperature).toFixed(1) : '-'}°` },
            { key: '云台', value: `P:${st.pose?.ptz?.pan != null ? Number(st.pose.ptz.pan).toFixed(1) : '-'} T:${st.pose?.ptz?.tilt != null ? Number(st.pose.ptz.tilt).toFixed(1) : '-'} Z:${st.pose?.ptz?.zoom != null ? Number(st.pose.ptz.zoom).toFixed(1) : '-'}` },
            { key: '升降', value: liftSt?.data?.height != null ? `${Number(liftSt.data.height).toFixed(2)}m` : '-' },
            { key: '任务', value: st.doing || '-' },
          ]} />
        )}
      </Card>

      <Tabs type="line" size="small">
        {/* 运动控制 */}
        <TabPane tab="运动" itemKey="motion">
          <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 6, maxWidth: 180, margin: '8px auto', placeItems: 'center' }}>
            <div />
            <button className="rc-hold-btn" style={holdBtnStyle} {...btnProps(1)}><IconArrowUp size="large" /></button>
            <div />
            <button className="rc-hold-btn" style={holdBtnStyle} {...btnProps(3)}><IconArrowLeft size="large" /></button>
            <button className="rc-hold-btn rc-stop-btn" style={{ ...holdBtnStyle, background: '#f56c6c' }} onMouseDown={stopMove} onTouchStart={(e) => { e.preventDefault(); stopMove() }} disabled={!rid}><IconStop size="large" /></button>
            <button className="rc-hold-btn" style={holdBtnStyle} {...btnProps(4)}><IconArrowRight size="large" /></button>
            <div />
            <button className="rc-hold-btn" style={holdBtnStyle} {...btnProps(2)}><IconArrowDown size="large" /></button>
            <div />
          </div>
          <div className="flex gap-8" style={{ justifyContent: 'center', flexWrap: 'wrap', marginBottom: 8 }}>
            <Button size="small" theme="solid" type="warning" disabled={!rid} onClick={home}>回充</Button>
            <Popconfirm title="确认急停?" onConfirm={estop}>
              <Button size="small" theme="solid" type="danger" disabled={!rid}>急停</Button>
            </Popconfirm>
          </div>
        </TabPane>

        {/* 云台控制 */}
        <TabPane tab="云台" itemKey="ptz">
          <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 4, maxWidth: 150, margin: '8px auto', placeItems: 'center' }}>
            <div />
            <button className="rc-hold-btn rc-ptz-btn" style={ptzBtnStyle} {...ptzBtnProps(1)} title="上仰"><IconArrowUp /></button>
            <div />
            <button className="rc-hold-btn rc-ptz-btn" style={ptzBtnStyle} {...ptzBtnProps(3)} title="左转"><IconArrowLeft /></button>
            <button className="rc-hold-btn rc-ptz-btn" style={{ ...ptzBtnStyle, background: '#909399' }} onClick={ptzReset} disabled={!rid} title="复位"><IconRefresh /></button>
            <button className="rc-hold-btn rc-ptz-btn" style={ptzBtnStyle} {...ptzBtnProps(4)} title="右转"><IconArrowRight /></button>
            <div />
            <button className="rc-hold-btn rc-ptz-btn" style={ptzBtnStyle} {...ptzBtnProps(2)} title="下俯"><IconArrowDown /></button>
            <div />
          </div>
          <div className="flex gap-8" style={{ justifyContent: 'center', marginBottom: 8 }}>
            <Button size="small" icon={<IconPlus />} disabled={!rid} onClick={() => zoomStep('in')}>放大</Button>
            <Button size="small" icon={<IconMinus />} disabled={!rid} onClick={() => zoomStep('out')}>缩小</Button>
            <Button size="small" icon={<IconCamera />} disabled={!rid} onClick={ptzReset}>复位</Button>
          </div>
        </TabPane>

        {/* 升降杆控制 */}
        <TabPane tab="升降" itemKey="lift">
          <div style={fieldGrid}>
            <span>高度</span>
            <div className="flex gap-8" style={{ alignItems: 'center' }}>
              <InputNumber size="small" value={liftHeight} step={0.1} min={0} onChange={(v) => setLiftHeight(Number(v) || 0)} />
              <Button size="small" theme="solid" type="primary" disabled={!rid} onClick={() => liftCmd(3, liftHeight)}>前往</Button>
            </div>
          </div>
          <div className="flex gap-8" style={{ flexWrap: 'wrap', marginTop: 8 }}>
            <Button size="small" disabled={!rid} onClick={() => liftCmd(1)}>上升</Button>
            <Button size="small" disabled={!rid} onClick={() => liftCmd(2)}>下降</Button>
            <Button size="small" theme="solid" type="danger" disabled={!rid} onClick={() => liftCmd(0)}>停止</Button>
            <Button size="small" theme="solid" type="tertiary" icon={<IconRefresh />} disabled={!rid} onClick={() => liftCmd(4)}>复位</Button>
          </div>
        </TabPane>

        {/* 位姿设置 */}
        <TabPane tab="位姿" itemKey="pose">
          <div style={{ marginBottom: 12 }}>
            <div style={{ fontSize: 12, color: '#909399', marginBottom: 4 }}>前往位姿</div>
            <div style={fieldGrid}>
              <span>X</span>
              <InputNumber size="small" value={pose.x} step={0.1} onChange={(v) => setPoseField('x', v)} />
              <span>Y</span>
              <InputNumber size="small" value={pose.y} step={0.1} onChange={(v) => setPoseField('y', v)} />
              <span>角度</span>
              <InputNumber size="small" value={pose.theta} step={1} onChange={(v) => setPoseField('theta', v)} />
              <div />
              <Button size="small" theme="solid" type="primary" disabled={!rid} onClick={setPoseFn}>前往此位姿</Button>
            </div>
          </div>
          <div>
            <div style={{ fontSize: 12, color: '#909399', marginBottom: 4 }}>云台位姿</div>
            <div style={fieldGrid}>
              <span>Pan</span>
              <InputNumber size="small" value={ptz.pan} step={1} onChange={(v) => setPtzField('pan', v)} />
              <span>Tilt</span>
              <InputNumber size="small" value={ptz.tilt} step={1} onChange={(v) => setPtzField('tilt', v)} />
              <span>Zoom</span>
              <InputNumber size="small" value={ptz.zoom} step={0.1} onChange={(v) => setPtzField('zoom', v)} />
              <div />
              <Button size="small" theme="solid" type="primary" disabled={!rid} onClick={setPtzPose}>设置位姿</Button>
            </div>
          </div>
        </TabPane>
      </Tabs>

      <style>{`
        .rc-hold-btn:active { transform: scale(0.9); background: #337ecc; }
        .rc-hold-btn:disabled { opacity: .4; cursor: not-allowed; }
        .rc-stop-btn:active { background: #dd6161; }
        .rc-ptz-btn:active { transform: scale(0.9); background: #5daf34; }
        .rc-ptz-btn:disabled { opacity: .4; cursor: not-allowed; }
      `}</style>
    </FloatPanel>
  )
}
