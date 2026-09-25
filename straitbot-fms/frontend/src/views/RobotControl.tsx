import { useCallback, useEffect, useRef, useState } from 'react'
import {
  Card, Button, InputNumber, Tag, Spin, Toast, Row, Col, Space, Typography,
} from '@douyinfe/semi-ui'
import { IconArrowUp, IconArrowDown, IconStop, IconMapPin, IconPlay, IconDelete, IconHome, IconRefresh } from '@douyinfe/semi-icons'
import {
  fetchRobotControlState, jogForward, jogBackward, stopRobot, gotoX, startTestInspection,
  cancelInspection, clearInspectionProgress, goCharge, resetStateMachine,
  type RobotControlState,
} from '../api/railRobot'
import PtzPanel from '../components/PtzPanel'
import RobotStateTree from '../components/RobotStateTree'

const { Text } = Typography

/** 连接状态中文/颜色 */
function statusTag(online: boolean, boardStatus: string) {
  const map: Record<string, { color: string; text: string }> = {
    connected: { color: 'green', text: '已连接' },
    connecting: { color: 'blue', text: '连接中' },
    reconnecting: { color: 'orange', text: '重连中' },
    idle: { color: 'grey', text: '未连接' },
    error: { color: 'red', text: '错误' },
    close: { color: 'grey', text: '已关闭' },
  }
  const s = map[boardStatus] || { color: online ? 'green' : 'grey', text: boardStatus || '未知' }
  return <Tag color={s.color as any} size="large">{s.text}</Tag>
}

export default function RobotControl() {
  const [state, setState] = useState<RobotControlState | null>(null)
  const [speed, setSpeed] = useState<number>(0.3)   // 点动/持续速度 m/s
  const [targetX, setTargetX] = useState<number>(0) // 移动目标 m
  const [busy, setBusy] = useState(false)
  // 自动刷新（1 秒）：默认开启；关掉后只手动刷新，避免现场调试时数据一直跳
  const [autoRefresh, setAutoRefresh] = useState(true)
  const [refreshing, setRefreshing] = useState(false)
  const [lastUpdated, setLastUpdated] = useState<number | null>(null)
  const holdingRef = useRef<'f' | 'b' | null>(null)

  // silent=true 用于自动刷新：不点亮手动刷新按钮的 loading（否则按钮每秒闪一下）
  const refresh = useCallback(async (silent = false) => {
    if (!silent) setRefreshing(true)
    try {
      setState(await fetchRobotControlState())
      setLastUpdated(Date.now())
    } catch {
      /* 401/网络错误已由 http 拦截器提示 */
    } finally {
      if (!silent) setRefreshing(false)
    }
  }, [])

  useEffect(() => {
    refresh()
  }, [refresh])

  // 自动刷新：仅在开关打开时挂定时器，关闭立即清除
  useEffect(() => {
    if (!autoRefresh) return
    const t = setInterval(() => refresh(true), 1000)
    return () => clearInterval(t)
  }, [autoRefresh, refresh])

  // 离开页面时若仍按住点动，确保停车
  useEffect(() => () => {
    if (holdingRef.current) {
      holdingRef.current = null
      stopRobot().catch(() => {})
    }
  }, [])

  /** 动作包裹：busy + 动作后稍后刷新一次状态 */
  const run = useCallback(async (fn: () => Promise<unknown>, ok?: string) => {
    setBusy(true)
    try {
      await fn()
      if (ok) Toast.success(ok)
      setTimeout(refresh, 300)
    } catch {
      /* 拦截器已提示 */
    } finally {
      setBusy(false)
    }
  }, [refresh])

  /** 一键下发内置测试巡检任务（tests/test_inspection.json）；忙时后端返回 409，拦截器提示 */
  const runTestInspection = useCallback(async () => {
    setBusy(true)
    try {
      const res = await startTestInspection()
      Toast.success(
        `测试巡检已启动：${res.floors ?? ''}，${res.waypoint_count ?? 0} 航点 / ${res.action_count ?? 0} 动作`,
      )
      setTimeout(refresh, 300)
    } catch {
      /* 409 忙碌/网络错误已由 http 拦截器提示 */
    } finally {
      setBusy(false)
    }
  }, [refresh])

  // ---- 按住点动 ----
  // 注意: 不能用 onPointerLeave 作为"松开"信号——setPointerCapture 后/在按钮内子元素间
  // 移动时，按下过程中(buttons 仍=1)会产生 pointerleave 抖动，会把刚发出的点动立刻停掉。
  // 改为: pointerdown 发车并捕获指针；停车只认全局 pointerup / pointercancel（捕获后即使
  // 指针移出按钮再松开，window 仍能收到 pointerup）。
  const endHold = useCallback(() => {
    if (!holdingRef.current) return
    holdingRef.current = null
    stopRobot().catch(() => {})
    setTimeout(refresh, 300)
  }, [refresh])

  const startHold = (dir: 'f' | 'b') => (e: React.PointerEvent<HTMLButtonElement>) => {
    e.preventDefault()
    try { e.currentTarget.setPointerCapture(e.pointerId) } catch { /* 忽略 */ }
    if (holdingRef.current) return
    holdingRef.current = dir
    const v = Number.isFinite(speed) && speed > 0 ? speed : undefined
    ;(dir === 'f' ? jogForward(v) : jogBackward(v)).catch(() => {})
  }

  useEffect(() => {
    const up = () => endHold()
    window.addEventListener('pointerup', up)
    window.addEventListener('pointercancel', up)
    return () => {
      window.removeEventListener('pointerup', up)
      window.removeEventListener('pointercancel', up)
      // 离开页面时若仍按住点动，确保停车
      if (holdingRef.current) {
        holdingRef.current = null
        stopRobot().catch(() => {})
      }
    }
  }, [endHold])

  return (
    <div className="page-container">
      <div className="mb-12" style={{ display: 'flex', alignItems: 'center', gap: 12 }}>
        <h2 style={{ margin: 0 }}>机器人控制</h2>
        {state && (
          <Space>
            {statusTag(state.online, state.board_status)}
            <Text strong>{state.name}</Text>
            <Text type="tertiary">{state.robot_id} · {state.ip}:{state.port}</Text>
          </Space>
        )}
      </div>

      {!state ? (
        <div style={{ display: 'flex', justifyContent: 'center', padding: '80px 0' }}><Spin size="large" /></div>
      ) : (
        <Row gutter={16}>
          <Col span={14}>
            {/* 按住点动 */}
            <Card className="card-shadow mb-12" bordered={false} title="点动控制（按住走行，松开停止）">
              <Space spacing={24} style={{ width: '100%', justifyContent: 'center', padding: '12px 0' }}>
                <Button
                  theme="solid" type="primary" size="large" icon={<IconArrowUp />}
                  style={{ width: 150, height: 72, fontSize: 18, userSelect: 'none', touchAction: 'none' }}
                  onPointerDown={startHold('f')}
                  onContextMenu={(e) => e.preventDefault()}
                >按住向前</Button>
                <Button
                  theme="solid" type="primary" size="large" icon={<IconArrowDown />}
                  iconPosition="right"
                  style={{ width: 150, height: 72, fontSize: 18, userSelect: 'none', touchAction: 'none' }}
                  onPointerDown={startHold('b')}
                  onContextMenu={(e) => e.preventDefault()}
                >按住向后</Button>
              </Space>
              <div style={{ display: 'flex', alignItems: 'center', gap: 8, justifyContent: 'center' }}>
                <Text type="tertiary">点动速度</Text>
                <InputNumber min={0} max={2} step={0.05} value={speed} onChange={(v) => setSpeed(Number(v))} style={{ width: 120 }} suffix="m/s" />
              </div>
            </Card>

            {/* 持续走行 + 停止 */}
            <Card className="card-shadow mb-12" bordered={false} title="走行控制">
              <Space wrap>
                <Button size="large" icon={<IconArrowUp />} loading={busy}
                  onClick={() => run(() => jogForward(Number.isFinite(speed) && speed > 0 ? speed : undefined))}>
                  一直向前
                </Button>
                <Button size="large" icon={<IconArrowDown />} loading={busy}
                  onClick={() => run(() => jogBackward(Number.isFinite(speed) && speed > 0 ? speed : undefined))}>
                  一直向后
                </Button>
                <Button size="large" theme="solid" type="danger" icon={<IconStop />} loading={busy}
                  onClick={() => run(() => stopRobot(), '已停止')}>
                  停止
                </Button>
              </Space>
              <div style={{ marginTop: 8 }}>
                <Text type="tertiary" size="small">"一直向前/向后"会持续走行，点击"停止"停车。</Text>
              </div>
            </Card>

            {/* 移动到指定位置 */}
            <Card className="card-shadow mb-12" bordered={false} title="移动到指定位置">
              <Space>
                <Text type="tertiary">目标 X（弧长）</Text>
                <InputNumber value={targetX} onChange={(v) => setTargetX(Number(v))}
                  step={0.1} style={{ width: 160 }} suffix="m" />
                <Button theme="solid" type="primary" size="large" icon={<IconMapPin />} loading={busy}
                  onClick={() => run(() => gotoX(targetX), `已下发移动到 ${targetX} m`)}>
                  移动到
                </Button>
              </Space>
            </Card>

            {/* 巡检 */}
            <Card className="card-shadow mb-12" bordered={false} title="巡检">
              <Space vertical align="start" spacing={8}>
                <Space>
                  <Button theme="solid" type="primary" size="large" icon={<IconPlay />} loading={busy}
                    onClick={runTestInspection}>
                    测试巡检
                  </Button>
                  <Button theme="solid" type="danger" size="large" icon={<IconStop />} loading={busy}
                    onClick={() => run(() => cancelInspection(), '取消巡检信号已发送')}>
                    取消巡检
                  </Button>
                  <Button size="large" icon={<IconDelete />} loading={busy}
                    onClick={() => run(async () => {
                      const res = await clearInspectionProgress()
                      Toast.success(`已删除 ${res.count} 个巡检断点文件`)
                    }, '已删除巡检断点文件')}>
                    删除巡检中状态文件
                  </Button>
                  <Button theme="solid" type="warning" size="large" icon={<IconHome />} loading={busy}
                    onClick={() => run(() => goCharge(), '已下发回充')}>
                    回去充电
                  </Button>
                  <Button size="large" icon={<IconRefresh />} loading={busy}
                    onClick={() => {
                      if (!window.confirm('重置状态机会停车并中止当前任务，主机回到启动态。继续？')) return
                      run(() => resetStateMachine(), '状态机已重置')
                    }}>
                    重置状态机
                  </Button>
                </Space>
                <Text type="tertiary" size="small">
                  一键下发内置测试任务（tests/test_inspection.json，多楼层），机器人按航点执行走行、升降、云台、拍照/测温；已有未完成巡检时本次下发会被忽略。
                </Text>
              </Space>
            </Card>

            {/* 云台控制（海康相机 HCNetSDK） */}
            <div className="mb-12">
              <PtzPanel />
            </div>
          </Col>

          {/* 实时状态（树视图：RobotState 各状态块与关键字段） */}
          <Col span={10}>
            <Card className="card-shadow mb-12" bordered={false} title="实时状态">
              <RobotStateTree
                state={state}
                autoRefresh={autoRefresh}
                onAutoRefreshChange={setAutoRefresh}
                lastUpdated={lastUpdated}
                onRefresh={() => refresh()}
                refreshing={refreshing}
              />
            </Card>
          </Col>
        </Row>
      )}
    </div>
  )
}
