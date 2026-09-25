import { useCallback, useEffect, useRef, useState } from 'react'
import {
  Card, Button, Tag, Space, Slider, InputNumber, Switch, Toast, Typography, Spin,
} from '@douyinfe/semi-ui'
import {
  IconArrowUp, IconArrowDown, IconArrowLeft, IconArrowRight,
  IconStop, IconPlus, IconMinus, IconRefresh, IconCamera, IconLink, IconClose,
} from '@douyinfe/semi-icons'
import {
  fetchPtzState, ptzConnect, ptzDisconnect, ptzMove, ptzStop, ptzPreset, ptzSnapshot,
  type PtzCommand, type PtzState,
} from '../api/railPtz'

const { Text } = Typography

// 方向/变焦按钮统一样式
const padBtn = (extra: React.CSSProperties = {}): React.CSSProperties => ({
  width: 64, height: 56, fontSize: 16, userSelect: 'none', touchAction: 'none', ...extra,
})

// Semi Slider/InputNumber 拖拽或清空时 onChange 可能给出 undefined/空串，直接 Number() 会得到 NaN。
// 仅在解析出有限数时返回夹取到 [min,max] 的整数，否则返回 null（调用方保持原值）。
const parseClamped = (v: unknown, min: number, max: number): number | null => {
  if (v === '' || v === null || v === undefined) return null
  const n = Number(v)
  if (!Number.isFinite(n)) return null
  return Math.min(max, Math.max(min, Math.round(n)))
}

export default function PtzPanel() {
  const [st, setSt] = useState<PtzState | null>(null)
  const [speed, setSpeed] = useState<number>(4)
  const [preset, setPreset] = useState<number>(1)
  const [img, setImg] = useState<string>('')
  const [live, setLive] = useState<boolean>(false)
  const [snapBusy, setSnapBusy] = useState(false)
  const holdRef = useRef<PtzCommand | null>(null)
  const imgRef = useRef<string>('')       // 当前 object URL，替换/卸载时 revoke

  const connected = !!st?.connected

  const refreshState = useCallback(async () => {
    try { setSt(await fetchPtzState()) } catch { /* 拦截器已提示 */ }
  }, [])

  // 抓图并更新预览（复用/释放 object URL，避免泄漏）
  const grab = useCallback(async () => {
    setSnapBusy(true)
    try {
      const url = await ptzSnapshot()
      if (imgRef.current) URL.revokeObjectURL(imgRef.current)
      imgRef.current = url
      setImg(url)
    } catch {
      /* 拦截器已提示 */
    } finally {
      setSnapBusy(false)
    }
  }, [])

  useEffect(() => { refreshState() }, [refreshState])

  // 实时预览：开启后按间隔抓图
  useEffect(() => {
    if (!live || !connected) return
    grab()
    const t = setInterval(grab, 1200)
    return () => clearInterval(t)
  }, [live, connected, grab])

  // 全局松手 -> 停止云台（按住式控制）
  const endHold = useCallback(() => {
    if (!holdRef.current) return
    holdRef.current = null
    ptzStop().catch(() => {})
  }, [])

  useEffect(() => {
    const up = () => endHold()
    window.addEventListener('pointerup', up)
    window.addEventListener('pointercancel', up)
    return () => {
      window.removeEventListener('pointerup', up)
      window.removeEventListener('pointercancel', up)
      if (holdRef.current) { holdRef.current = null; ptzStop().catch(() => {}) }
      if (imgRef.current) URL.revokeObjectURL(imgRef.current)
    }
  }, [endHold])

  const startHold = (cmd: PtzCommand) => (e: React.PointerEvent<HTMLButtonElement>) => {
    e.preventDefault()
    try { e.currentTarget.setPointerCapture(e.pointerId) } catch { /* 忽略 */ }
    if (holdRef.current) return
    holdRef.current = cmd
    ptzMove(cmd, { speed }).catch(() => { holdRef.current = null })
  }

  const run = useCallback(async (fn: () => Promise<unknown>, ok?: string) => {
    try { await fn(); if (ok) Toast.success(ok) } catch { /* 拦截器已提示 */ }
    setTimeout(refreshState, 300)
  }, [refreshState])

  const doConnect = () => run(async () => { await ptzConnect(); await grab() }, '云台已连接')
  const doDisconnect = () => run(() => ptzDisconnect(), '已断开')

  if (st && !st.configured) {
    return (
      <Card className="card-shadow" bordered={false} title="云台控制">
        <Text type="tertiary">未配置云台相机：请在 robot.prefab.json 的机器人节点下添加 HkPtzConfig。</Text>
      </Card>
    )
  }

  return (
    <Card
      className="card-shadow" bordered={false} title="云台控制"
      headerExtraContent={
        <Space>
          {st && <Tag color={connected ? 'green' : 'grey'} size="large">{connected ? '已连接' : '未连接'}</Tag>}
          {connected
            ? <Button size="small" icon={<IconClose />} onClick={doDisconnect}>断开</Button>
            : <Button size="small" theme="solid" type="primary" icon={<IconLink />} onClick={doConnect}>连接</Button>}
        </Space>
      }
    >
      {!st ? (
        <div style={{ display: 'flex', justifyContent: 'center', padding: '40px 0' }}><Spin /></div>
      ) : (
        <>
          {st.connected && st.device_info && (
            <div className="mb-12">
              <Text type="tertiary" size="small">
                {st.ip}:{st.port} · 通道{st.channel} · SN {st.device_info.serial_number}
              </Text>
            </div>
          )}

          {/* 画面预览 */}
          <div style={{ textAlign: 'center', marginBottom: 12 }}>
            {img
              ? <img src={img} alt="云台画面" style={{ maxWidth: '100%', borderRadius: 6, background: '#000' }} />
              : <div style={{ height: 180, display: 'flex', alignItems: 'center', justifyContent: 'center', background: '#f2f2f5', borderRadius: 6, color: '#8a8a8a' }}>暂无画面</div>}
            <Space style={{ marginTop: 8 }}>
              <Button size="small" icon={<IconCamera />} loading={snapBusy} disabled={!connected} onClick={grab}>抓拍</Button>
              <Space>
                <Text type="tertiary" size="small">实时</Text>
                <Switch size="small" checked={live} disabled={!connected} onChange={(v) => setLive(v)} />
              </Space>
              {live && <Button size="small" icon={<IconRefresh />} loading={snapBusy} onClick={grab} />}
            </Space>
          </div>

          {/* 方向盘 + 变焦 */}
          <Space align="start" spacing={24} style={{ width: '100%', justifyContent: 'center' }}>
            <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 64px)', gridAutoRows: '56px', gap: 6, justifyContent: 'center' }}>
              <span />
              <Button theme="solid" type="primary" icon={<IconArrowUp />} disabled={!connected} style={padBtn()}
                onPointerDown={startHold('up')} onContextMenu={(e) => e.preventDefault()} />
              <span />
              <Button theme="solid" type="primary" icon={<IconArrowLeft />} disabled={!connected} style={padBtn()}
                onPointerDown={startHold('left')} onContextMenu={(e) => e.preventDefault()} />
              <Button theme="solid" type="danger" icon={<IconStop />} disabled={!connected} style={padBtn()}
                onClick={() => ptzStop().catch(() => {})} onContextMenu={(e) => e.preventDefault()} />
              <Button theme="solid" type="primary" icon={<IconArrowRight />} disabled={!connected} style={padBtn()}
                onPointerDown={startHold('right')} onContextMenu={(e) => e.preventDefault()} />
              <span />
              <Button theme="solid" type="primary" icon={<IconArrowDown />} disabled={!connected} style={padBtn()}
                onPointerDown={startHold('down')} onContextMenu={(e) => e.preventDefault()} />
              <span />
            </div>

            <Space vertical spacing={8} align="center">
              <Button theme="solid" type="primary" icon={<IconPlus />} disabled={!connected} style={padBtn({ width: 88 })}
                onPointerDown={startHold('zoomin')} onContextMenu={(e) => e.preventDefault()}>变倍+</Button>
              <Button theme="solid" type="primary" icon={<IconMinus />} disabled={!connected} style={padBtn({ width: 88 })}
                onPointerDown={startHold('zoomout')} onContextMenu={(e) => e.preventDefault()}>变倍-</Button>
            </Space>
          </Space>

          <div className="mb-12" style={{ display: 'flex', alignItems: 'center', gap: 12, marginTop: 12 }}>
            <Text type="tertiary" style={{ whiteSpace: 'nowrap' }}>云台速度</Text>
            <Slider value={speed} min={1} max={7} step={1} marks={{ 1: '1', 4: '4', 7: '7' }}
              style={{ flex: '1 1 auto', minWidth: 220 }} onChange={(v) => { const n = parseClamped(v, 1, 7); if (n !== null) setSpeed(n) }} />
          </div>

          {/* 预置点 */}
          <Space>
            <Text type="tertiary">预置点</Text>
            <InputNumber min={1} max={255} value={preset} onChange={(v) => { const n = parseClamped(v, 1, 255); if (n !== null) setPreset(n) }} style={{ width: 100 }} />
            <Button disabled={!connected} onClick={() => run(() => ptzPreset('goto', preset), `已转到预置点 ${preset}`)}>转到</Button>
            <Button disabled={!connected} onClick={() => run(() => ptzPreset('set', preset), `已设置预置点 ${preset}`)}>设置</Button>
            <Button disabled={!connected} onClick={() => run(() => ptzPreset('clean', preset), `已清除预置点 ${preset}`)}>清除</Button>
          </Space>
          <div style={{ marginTop: 8 }}>
            <Text type="tertiary" size="small">方向/变倍为按住持续运动，松手自动停止。</Text>
          </div>
        </>
      )}
    </Card>
  )
}
