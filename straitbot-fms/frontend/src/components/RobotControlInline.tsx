import { useEffect, useRef, useState } from 'react'
import { Button, InputNumber, Tag, Tabs, TabPane } from '@douyinfe/semi-ui'
import {
  fetchRobotControlState, jogForward, jogBackward, stopRobot,
  type RobotControlState,
} from '../api/railRobot'
import { liftControl, motionSetPose, ptzAction, ptzSetPose } from '../api/control'

/**
 * 内嵌机器人控制面板：实时状态 + 运动 / 云台 / 升降 / 位姿。
 *
 * 走行机器人（挂轨）用 `/api/rail/robot/*` 这一套接口，与旧的按 rid 走
 * `/api/control/{rid}/*` 的轮式机器人不同，别混用。
 */

const STATUS_MAP: Record<number, string> = {
  0: '正常', 1: '开始充电', 2: '充电中', 3: '前往充电', 4: '自检中',
  5: '巡检中', 6: '巡检暂停', 7: '巡检挂起', 8: '前往电梯',
}

const btnStyle = (bg: string, size = 36, fontSize = 16): React.CSSProperties => ({
  width: size, height: size, borderRadius: '50%', border: '2px solid #dcdfe6',
  background: bg, color: '#fff', cursor: 'pointer', fontSize, padding: 0,
  userSelect: 'none', touchAction: 'none',
})

export default function RobotControlInline({ rid, active = true }: { rid: number | null; active?: boolean }) {
  const [st, setSt] = useState<RobotControlState | null>(null)
  const [loadErr, setLoadErr] = useState(false)
  const [pose, setPose] = useState({ x: 0, y: 0, theta: 0 })
  const [ptz, setPtz] = useState({ pan: 0, tilt: 0, zoom: 0 })
  const [liftH, setLiftH] = useState(1)
  const aliveRef = useRef(true)
  const stopTimer = useRef<ReturnType<typeof setTimeout> | null>(null)
  const ptzStopTimer = useRef<ReturnType<typeof setTimeout> | null>(null)

  useEffect(() => {
    aliveRef.current = true
    return () => { aliveRef.current = false }
  }, [])

  // 轮询实时状态；页面隐藏时跳过，省掉无谓请求
  useEffect(() => {
    if (!active || !rid) { setSt(null); return }
    let timer: ReturnType<typeof setInterval> | null = null
    const tick = async () => {
      if (document.hidden) return
      try {
        const data = await fetchRobotControlState()
        if (aliveRef.current) { setSt(data); setLoadErr(false) }
      } catch {
        if (aliveRef.current) setLoadErr(true)
      }
    }
    tick()
    timer = setInterval(tick, 3000)
    return () => { if (timer) clearInterval(timer) }
  }, [active, rid])

  // 卸载时兜底停车：避免长按走行中切走页面导致机器人一直在走
  useEffect(() => {
    const clearStop = () => {
      if (stopTimer.current) clearTimeout(stopTimer.current)
      if (ptzStopTimer.current) clearTimeout(ptzStopTimer.current)
    }
    return () => {
      clearStop()
      stopRobot().catch(() => { /* 拦截器已提示 */ })
    }
  }, [])

  const online = !!st?.online
  const disabled = !active || !rid || !online

  /* 走行点动：按下持续走，抬起/移出即停 */
  const move = (dir: 'forward' | 'backward') => {
    if (disabled) return
    if (stopTimer.current) clearTimeout(stopTimer.current)
    const fn = dir === 'forward' ? jogForward : jogBackward
    fn().catch(() => { /* 拦截器已提示 */ })
  }
  const halt = () => {
    if (!active) return
    if (stopTimer.current) clearTimeout(stopTimer.current)
    stopTimer.current = setTimeout(() => { stopRobot().catch(() => { /* */ }) }, 100)
  }
  const moveBtn = (dir: 'forward' | 'backward') => ({
    onMouseDown: () => move(dir),
    onMouseUp: halt,
    onMouseLeave: halt,
    onTouchStart: (e: React.TouchEvent) => { e.preventDefault(); move(dir) },
    onTouchEnd: (e: React.TouchEvent) => { e.preventDefault(); halt() },
  })

  const liftCmd = (cmd: number, h = 0) => {
    if (disabled) return
    liftControl(rid, cmd, h).catch(() => { /* 拦截器已提示 */ })
  }

  const applyPose = () => {
    if (disabled) return
    motionSetPose(rid, pose).catch(() => { /* 拦截器已提示 */ })
  }
  const applyPtz = () => {
    if (disabled) return
    ptzSetPose(rid, ptz).catch(() => { /* 拦截器已提示 */ })
  }

  /* 云台方向/变倍：按住持续转，松开下发 stop。
     停止统一用 command=0 + stop=true（一次停掉所有云台动作），与专用云台页一致。 */
  const ptzHold = (cmd: number) => {
    if (disabled) return
    if (ptzStopTimer.current) clearTimeout(ptzStopTimer.current)
    ptzAction(rid, { command: cmd, stop: false, channel: 1 }).catch(() => { /* 拦截器已提示 */ })
  }
  const ptzHalt = () => {
    if (!active || !rid) return
    if (ptzStopTimer.current) clearTimeout(ptzStopTimer.current)
    ptzStopTimer.current = setTimeout(() => {
      ptzAction(rid, { command: 0, stop: true, channel: 1 }).catch(() => { /* 拦截器已提示 */ })
    }, 100)
  }
  const ptzBtn = (cmd: number) => ({
    onMouseDown: () => ptzHold(cmd),
    onMouseUp: ptzHalt,
    onMouseLeave: ptzHalt,
    onTouchStart: (e: React.TouchEvent) => { e.preventDefault(); ptzHold(cmd) },
    onTouchEnd: (e: React.TouchEvent) => { e.preventDefault(); ptzHalt() },
  })
  /** 云台复位：常亮按钮，单击触发 */
  const ptzReset = () => {
    if (disabled) return
    ptzAction(rid, { command: 0, stop: false, channel: 1 }).catch(() => { /* 拦截器已提示 */ })
  }

  const p = st?.pose
  const batt = st?.battery

  return (
    <div style={{ fontSize: 12 }}>
      {/* 实时状态 */}
      <div style={{ background: 'var(--semi-color-fill-0)', borderRadius: 6, padding: '6px 10px', marginBottom: 8 }}>
        <div style={{ display: 'flex', alignItems: 'center', gap: 6, marginBottom: 2, flexWrap: 'wrap' }}>
          <Tag size="small" color={online ? 'green' : 'grey'}>{online ? '在线' : (st ? '离线' : '读取中')}</Tag>
          {batt?.battery_percent != null && <Tag size="small" color="blue">{batt.battery_percent}%</Tag>}
          {st?.chassis_state != null && (
            <span className="text-muted" style={{ fontSize: 11 }}>{STATUS_MAP[st.chassis_state] || st.chassis_state}</span>
          )}
        </div>
        {loadErr && <div className="text-muted" style={{ fontSize: 11 }}>状态读取失败，重试中…</div>}
        {p && (
          <div className="text-muted" style={{ fontSize: 11 }}>
            位置: x={Number(p.x || 0).toFixed(2)}m y={Number(p.y || 0).toFixed(2)}m θ={Number(p.yaw || 0).toFixed(1)}°<br />
            速度: {Number(p.linear_x || 0).toFixed(2)} m/s | 升降: {st?.lift?.coord_m != null ? Number(st.lift.coord_m).toFixed(2) + 'm' : '-'}
          </div>
        )}
      </div>

      <Tabs type="line" size="small">
        <TabPane tab="运动" itemKey="motion">
          <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 3, maxWidth: 130, margin: '4px auto', placeItems: 'center' }}>
            <div />
            <button style={btnStyle('#409eff')} disabled={disabled} {...moveBtn('forward')}>↑</button>
            <div />
            <div />
            <button style={btnStyle('#f56c6c')} disabled={disabled} onMouseDown={halt}>■</button>
            <div />
            <div />
            <button style={btnStyle('#409eff')} disabled={disabled} {...moveBtn('backward')}>↓</button>
            <div />
          </div>
          <div className="text-muted" style={{ fontSize: 11, textAlign: 'center' }}>
            按住方向键持续走行，松开即停
          </div>
        </TabPane>

        <TabPane tab="云台" itemKey="ptz">
          {/* 方向键：按住持续转动，松开停止 */}
          <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 3, maxWidth: 120, margin: '4px auto 2px', placeItems: 'center' }}>
            <div />
            <button style={btnStyle('#67c23a', 32, 14)} disabled={disabled} title="上仰" {...ptzBtn(21)}>↑</button>
            <div />
            <button style={btnStyle('#67c23a', 32, 14)} disabled={disabled} title="左转" {...ptzBtn(23)}>←</button>
            <button style={btnStyle('#909399', 32, 13)} disabled={disabled} title="云台复位" onMouseDown={ptzReset}>↺</button>
            <button style={btnStyle('#67c23a', 32, 14)} disabled={disabled} title="右转" {...ptzBtn(24)}>→</button>
            <div />
            <button style={btnStyle('#67c23a', 32, 14)} disabled={disabled} title="下俯" {...ptzBtn(22)}>↓</button>
            <div />
          </div>
          {/* 变倍：同样是按住生效 */}
          <div style={{ display: 'flex', gap: 6, justifyContent: 'center', margin: '2px 0 8px' }}>
            <button style={btnStyle('#67c23a', 26, 12)} disabled={disabled} title="放大" {...ptzBtn(11)}>＋</button>
            <button style={btnStyle('#67c23a', 26, 12)} disabled={disabled} title="缩小" {...ptzBtn(12)}>－</button>
          </div>

          <div style={{ display: 'grid', gridTemplateColumns: '36px 1fr', gap: 4, marginTop: 4, alignItems: 'center' }}>
            <span>Pan</span>
            <InputNumber size="small" value={ptz.pan} step={1}
              onChange={(v) => setPtz((s) => ({ ...s, pan: Number(v) || 0 }))} />
            <span>Tilt</span>
            <InputNumber size="small" value={ptz.tilt} step={1}
              onChange={(v) => setPtz((s) => ({ ...s, tilt: Number(v) || 0 }))} />
            <span>Zoom</span>
            <InputNumber size="small" value={ptz.zoom} step={0.1}
              onChange={(v) => setPtz((s) => ({ ...s, zoom: Number(v) || 0 }))} />
            <div />
            <Button size="small" theme="solid" type="primary" disabled={disabled} onClick={applyPtz}>设置云台位姿</Button>
          </div>
        </TabPane>

        <TabPane tab="升降" itemKey="lift">
          <div style={{ display: 'flex', gap: 6, alignItems: 'center', marginBottom: 6 }}>
            <InputNumber size="small" value={liftH} step={0.1} min={0}
              onChange={(v) => setLiftH(Number(v) || 0)} style={{ width: 70 }} />
            <Button size="small" theme="solid" type="primary" disabled={disabled}
              onClick={() => liftCmd(3, liftH)}>前往</Button>
          </div>
          <div style={{ display: 'flex', gap: 6, flexWrap: 'wrap' }}>
            <Button size="small" disabled={disabled} onClick={() => liftCmd(1)}>↑升</Button>
            <Button size="small" disabled={disabled} onClick={() => liftCmd(2)}>↓降</Button>
            <Button size="small" type="danger" disabled={disabled} onClick={() => liftCmd(0)}>停</Button>
            <Button size="small" disabled={disabled} onClick={() => liftCmd(4)}>复位</Button>
          </div>
        </TabPane>

        <TabPane tab="位姿" itemKey="pose">
          <div style={{ display: 'grid', gridTemplateColumns: '36px 1fr', gap: 4, alignItems: 'center' }}>
            <span>X</span>
            <InputNumber size="small" value={pose.x} step={0.1}
              onChange={(v) => setPose((s) => ({ ...s, x: Number(v) || 0 }))} />
            <span>Y</span>
            <InputNumber size="small" value={pose.y} step={0.1}
              onChange={(v) => setPose((s) => ({ ...s, y: Number(v) || 0 }))} />
            <span>θ</span>
            <InputNumber size="small" value={pose.theta} step={1}
              onChange={(v) => setPose((s) => ({ ...s, theta: Number(v) || 0 }))} />
            <div />
            <Button size="small" theme="solid" type="primary" disabled={disabled} onClick={applyPose}>前往</Button>
          </div>
        </TabPane>
      </Tabs>
    </div>
  )
}
