import { useCallback, useEffect, useRef, useState } from 'react'
import { Button, Card, Descriptions, Divider, Input, InputNumber, Select, Slider, Space, Switch, Tag, Toast, Typography } from '@douyinfe/semi-ui'
import { IconArrowDown, IconArrowUp, IconStop, IconMapPin, IconUndo, IconRefresh, IconPlusCircle, IconDelete, IconSave, IconDownload, IconEdit } from '@douyinfe/semi-icons'
import { SimScene } from '../simulation/scene'
import { RobotKinematics, type RobotSnapshot, type Obstacle } from '../simulation/robot'
import { SimWs, type WsStatus } from '../simulation/ws'
import { CMD, encodeFrame, be, type DecodedFrame } from '../simulation/protocol'
import { fetchSimStatus, listScenarios, getScenario, saveScenario, deleteScenario, type ScenarioMeta, type ScenarioData } from '../api/simulation'
import type { TrackConfig, TrackPoint } from '../simulation/track'

const { Title, Text } = Typography

const CHASSIS_STATE_TEXT = ['空闲', '运行中', '已到达', '初始化中']
const EXT_STATE_TEXT = ['空闲', '运行中', '已到位', '初始化中']

/** 选中对象 */
type Selection = { type: 'robot' | 'obstacle' | 'rfid'; id: number } | null

/** 页面级障碍物 */
interface ObstacleItem { id: number; s: number; width: number; enabled: boolean }
/** 页面级 RFID 卡片 */
interface RfidItem { id: number; s: number; tagId: string }

/** 0x0A/0x0B 底盘状态 payload: 状态(1) 模式(1) X(4) Y(4) YAW(2) LinearX(2) LinearY(2) Angular(2) */
function chassisPayload(kin: RobotKinematics): Uint8Array {
  const s = kin.snapshot()
  return new Uint8Array([
    ...new Uint8Array([s.state, s.mode]),
    ...be.packI32(s.s), ...be.packI32(0),
    ...be.packI16(s.yawX10),
    ...be.packI16(s.v), ...be.packI16(0), ...be.packI16(0),
  ])
}

/** 0x0C 响应(错误码2B) */
function errResp(seq: number, cmd: number): Uint8Array {
  return encodeFrame(seq, cmd, [0, 0])
}

export default function RobotSimulation() {
  const containerRef = useRef<HTMLDivElement>(null)
  const sceneRef = useRef<SimScene | null>(null)
  const kinRef = useRef<RobotKinematics | null>(null)
  const wsRef = useRef<SimWs | null>(null)
  const seqRef = useRef(0)
  const lastReportRef = useRef(0)
  const lastUiRef = useRef(0)
  const lastExtRef = useRef({ h: -1, v: -1 })

  const [wsStatus, setWsStatus] = useState<WsStatus>('connecting')
  const [tcpConnected, setTcpConnected] = useState(false)
  const [snap, setSnap] = useState<RobotSnapshot | null>(null)
  const [speed, setSpeed] = useState(300)
  const [target, setTarget] = useState(2000)
  const [extH, setExtH] = useState(300)
  const [obstacles, setObstacles] = useState<ObstacleItem[]>([])
  const [rfids, setRfids] = useState<RfidItem[]>([])
  const [selection, setSelection] = useState<Selection>(null)
  const [rfidIdText, setRfidIdText] = useState('')
  const obstacleIdRef = useRef(1)
  const rfidIdRef = useRef(1)
  // 场景配置(多套保存/加载)
  const [scenarios, setScenarios] = useState<ScenarioMeta[]>([])
  const [scenarioName, setScenarioName] = useState('')
  const [selScenario, setSelScenario] = useState('')
  // 绘制轨道
  const [drawMode, setDrawMode] = useState(false)
  const [drawPoints, setDrawPoints] = useState<TrackPoint[]>([])
  const drawPointsRef = useRef<TrackPoint[]>([])

  const nextSeq = () => (seqRef.current = (seqRef.current + 1) & 0xffff)
  const totalLenMm = () => sceneRef.current?.track.totalLength ? Math.round(sceneRef.current.track.totalLength * 1000) : 21425

  const selectionKey = (sel: Selection) => sel ? (sel.type === 'robot' ? 'robot' : `${sel.type}-${sel.id}`) : null

  // ---------- 协议帧处理(上位机经 TCP/WS 下发) ----------
  const handleFrame = useCallback((f: DecodedFrame) => {
    const kin = kinRef.current
    const ws = wsRef.current
    if (!kin || !ws) return
    switch (f.cmd) {
      case CMD.HEARTBEAT: // 0x06 响应空
        ws.send(encodeFrame(f.seq, CMD.HEARTBEAT))
        break
      case CMD.CHASSIS_MOVE: { // 0x09
        const p = f.payload
        if (p.length >= 17) {
          kin.applyMove({ mode: p[0], linearX: be.u16(p, 1), targetX: be.i32(p, 7) })
        }
        ws.send(errResp(f.seq, CMD.CHASSIS_MOVE))
        break
      }
      case CMD.GET_CHASSIS: // 0x0A
        ws.send(encodeFrame(f.seq, CMD.GET_CHASSIS, chassisPayload(kin)))
        break
      case CMD.MOTOR_CTRL: { // 0x0C 伸缩杆
        const p = f.payload
        if (p.length >= 8) {
          kin.applyExt({ mid: p[0], mode: p[1], speed: be.i16(p, 2), coord: be.i32(p, 4) })
        }
        ws.send(errResp(f.seq, CMD.MOTOR_CTRL))
        break
      }
      case CMD.GET_MOTOR: { // 0x0D
        const s = kin.snapshot()
        const pl = new Uint8Array([
          ...new Uint8Array([1, s.extState]),
          ...be.packI16(s.extV), ...be.packI32(s.extH),
          ...be.packI32(0), ...be.packI32(0),
          ...be.packI32(120), ...be.packI32(118), ...be.packI32(32),
        ])
        ws.send(encodeFrame(f.seq, CMD.GET_MOTOR, pl))
        break
      }
      // ---- 模拟响应 ----
      case CMD.INIT:
        ws.send(errResp(f.seq, CMD.INIT))
        break
      case CMD.GET_CONFIG: {
        const pl = new Uint8Array([...be.packU16(0), ...be.packU16(1000), ...be.packU16(150), ...be.packU16(0), ...be.packU16(600)])
        ws.send(encodeFrame(f.seq, CMD.GET_CONFIG, pl))
        break
      }
      case CMD.REBOOT:
        ws.send(errResp(f.seq, CMD.REBOOT))
        break
      case CMD.GET_VERSION: {
        // 错误码(2) + 软件版本(3: V2.0.0) + SN(12)
        const pl = new Uint8Array([...be.packU16(0), 0x02, 0x00, 0x00, ...new TextEncoder().encode('SIMROBOT0001').slice(0, 12)])
        ws.send(encodeFrame(f.seq, CMD.GET_VERSION, pl))
        break
      }
      case CMD.TIME_SYNC:
        ws.send(errResp(f.seq, CMD.TIME_SYNC))
        break
      case CMD.MOTOR_POWER:
        ws.send(errResp(f.seq, CMD.MOTOR_POWER))
        break
      default:
        ws.send(encodeFrame(f.seq, f.cmd, [0xff, 0xff]))
        break
    }
  }, [])

  // ---------- 挂载 ----------
  useEffect(() => {
    const el = containerRef.current
    if (!el) return
    const scene = new SimScene(el)
    sceneRef.current = scene
    ;(window as unknown as Record<string, unknown>).__simScene = scene // 调试: 浏览器控制台取用
    const kin = new RobotKinematics(scene.track.totalLength)
    kinRef.current = kin
    const ws = new SimWs(handleFrame, (s) => setWsStatus(s))
    wsRef.current = ws
    ws.connect()

    scene.onPick((info) => {
      setSelection({ type: info.type, id: info.id })
    })
    scene.onDrawPoint((pts) => {
      drawPointsRef.current = pts
      setDrawPoints(pts)
    })
    scene.onDragMove((info) => {
      const total = totalLenMm()
      const s = Math.max(0, Math.min(total, info.sMm))
      if (info.type === 'obstacle') updateObstacle(info.id, { s })
      else updateRfid(info.id, { s })
    })
    scene.setDefaultCamera()

    listScenarios().then(setScenarios).catch(() => setScenarios([]))

    const poll = window.setInterval(async () => {
      try {
        const st = await fetchSimStatus()
        setTcpConnected(st.tcp_connected)
      } catch { /* 后端暂不可用 */ }
    }, 3000)

    // 动画 + 10Hz 状态上传 + UI 刷新
    scene.onFrame((dt) => {
      const now = performance.now()
      const kinNow = kinRef.current
      if (!kinNow) return
      kinNow.step(dt * 1000, now)
      scene.setRobot(kinNow.s / 1000, kinNow.extH / 1000, kinNow.v / 1000, kinNow.state === 1)

      if (now - lastReportRef.current >= 100) {
        lastReportRef.current = now
        // 偏航(轨道切线方位角 *10, 度, 左正右负)
        const tan = scene.track.tangentAt(kinNow.s / 1000)
        const yawDeg = (Math.atan2(tan.z, tan.x) * 180) / Math.PI
        kinNow.mode = 2
        const snapNow = kinNow.snapshot(Math.round(yawDeg * 10))
        // 0x0B 底盘状态上传(10Hz)
        ws.send(encodeFrame(nextSeq(), CMD.UPLOAD_CHASSIS, chassisPayload(kinNow)))
        // 0x0E 电机状态上传(高度/速度变化时)
        if (snapNow.extH !== lastExtRef.current.h || snapNow.extV !== lastExtRef.current.v) {
          const pl = new Uint8Array([
            ...new Uint8Array([1, snapNow.extState]),
            ...be.packI16(snapNow.extV), ...be.packI32(snapNow.extH),
            ...be.packI32(0), ...be.packI32(0),
            ...be.packI32(120), ...be.packI32(118), ...be.packI32(32),
          ])
          ws.send(encodeFrame(nextSeq(), CMD.UPLOAD_MOTOR, pl))
          lastExtRef.current = { h: snapNow.extH, v: snapNow.extV }
        }
        // UI 刷新(5Hz)
        if (now - lastUiRef.current >= 200) {
          lastUiRef.current = now
          setSnap(snapNow)
        }
      }
    })

    return () => {
      window.clearInterval(poll)
      ws.close()
      scene.dispose()
      delete (window as unknown as Record<string, unknown>).__simScene
      sceneRef.current = null
      kinRef.current = null
      wsRef.current = null
    }
  }, [handleFrame])

  // 障碍物 → 运动学避障 + 场景网格
  useEffect(() => {
    const list: Obstacle[] = obstacles.map((o) => ({ id: o.id, s: o.s, width: o.width, enabled: o.enabled }))
    kinRef.current?.setObstacles(list)
    sceneRef.current?.setObstacles(obstacles)
  }, [obstacles])

  // RFID → 场景网格
  useEffect(() => {
    sceneRef.current?.setRfids(rfids)
  }, [rfids])

  // 选中 → 场景高亮
  useEffect(() => {
    sceneRef.current?.selectObject(selectionKey(selection))
  }, [selection])

  // ---------- 障碍物 / RFID 操作 ----------
  const addObstacle = () => {
    const kin = kinRef.current
    const s = kin ? Math.round((kin.s + 1500) % totalLenMm()) : 3000
    const item: ObstacleItem = { id: obstacleIdRef.current++, s, width: 300, enabled: true }
    setObstacles((prev) => [...prev, item])
    setSelection({ type: 'obstacle', id: item.id })
  }

  const addRfid = () => {
    const kin = kinRef.current
    const s = kin ? Math.round((kin.s + 1200) % totalLenMm()) : 8000
    const item: RfidItem = { id: rfidIdRef.current++, s, tagId: `RFID-${String(rfidIdRef.current - 1).padStart(3, '0')}` }
    setRfids((prev) => [...prev, item])
    setSelection({ type: 'rfid', id: item.id })
    setRfidIdText(item.tagId)
  }

  const updateObstacle = (id: number, patch: Partial<ObstacleItem>) => {
    setObstacles((prev) => prev.map((o) => (o.id === id ? { ...o, ...patch } : o)))
  }

  const updateRfid = (id: number, patch: Partial<RfidItem>) => {
    setRfids((prev) => prev.map((r) => (r.id === id ? { ...r, ...patch } : r)))
  }

  const deleteObstacle = (id: number) => {
    setObstacles((prev) => prev.filter((o) => o.id !== id))
    setSelection(null)
  }

  const deleteRfid = (id: number) => {
    setRfids((prev) => prev.filter((r) => r.id !== id))
    setSelection(null)
  }

  const applyRfidId = () => {
    if (!selection || selection.type !== 'rfid') return
    updateRfid(selection.id, { tagId: rfidIdText.trim() || `RFID-${String(selection.id).padStart(3, '0')}` })
  }

  // ---------- 场景配置(多套保存/加载) ----------
  const trackInfoText = () => {
    const t = sceneRef.current?.track
    if (!t) return '—'
    return `${t.kind === 'rect' ? '矩形环' : '手动绘制'} · ${Math.round(t.totalLength * 1000)} mm`
  }

  const rebuildKinematics = () => {
    const scene = sceneRef.current
    if (!scene) return
    kinRef.current = new RobotKinematics(scene.track.totalLength)
  }

  /** 障碍物/RFID 弧长规范化到当前轨道长度内(环形 wrap, 与场景定位一致) */
  const normalizeArc = () => {
    const total = totalLenMm()
    if (total <= 0) return
    setObstacles((prev) => prev.map((o) => ({ ...o, s: Number.isFinite(o.s) ? o.s % total : 0 })))
    setRfids((prev) => prev.map((r) => ({ ...r, s: Number.isFinite(r.s) ? r.s % total : 0 })))
  }

  /** 弧长输入 clamp 到轨道范围(不绕圈跳跃) */
  const clampS = (v: string | number | number[] | null | undefined, total: number) => {
    const n = Array.isArray(v) ? v[0] : v
    return Math.max(0, Math.min(total, Math.round(Number(n) || 0)))
  }

  const handleSaveScenario = async () => {
    const name = scenarioName.trim()
    if (!name) {
      Toast.warning('请输入场景名称')
      return
    }
    const t = sceneRef.current?.track
    if (!t) return
    const track = {
      kind: t.kind,
      straightLen: t.cfg.straightLen,
      radius: t.cfg.radius,
      height: t.cfg.height,
      tubeRadius: t.cfg.tubeRadius,
      points: t.cfg.points,
    }
    try {
      await saveScenario(name, { track, obstacles, rfids })
      Toast.success(`已保存场景「${name}」`)
      setScenarioName('')
      setScenarios(await listScenarios())
    } catch (e) {
      Toast.error(`保存失败: ${e instanceof Error ? e.message : e}`)
    }
  }

  const handleLoadScenario = async () => {
    if (!selScenario) {
      Toast.warning('请先选择要加载的场景')
      return
    }
    try {
      const sc: ScenarioData = await getScenario(selScenario)
      const scene = sceneRef.current
      if (!scene) return
      scene.setTrack(sc.track as TrackConfig)
      rebuildKinematics()
      const total = Math.round(scene.track.totalLength * 1000)
      setObstacles(sc.obstacles.map((o) => ({ id: o.id, s: o.s % total, width: o.width, enabled: o.enabled })))
      setRfids(sc.rfids.map((r) => ({ id: r.id, s: r.s % total, tagId: r.tagId })))
      obstacleIdRef.current = Math.max(1, ...sc.obstacles.map((o) => o.id)) + 1
      rfidIdRef.current = Math.max(1, ...sc.rfids.map((r) => r.id)) + 1
      setSelection(null)
      setSnap(null)
      Toast.success(`已加载场景「${selScenario}」`)
    } catch (e) {
      Toast.error(`加载失败: ${e instanceof Error ? e.message : e}`)
    }
  }

  const handleDeleteScenario = async () => {
    if (!selScenario) return
    try {
      await deleteScenario(selScenario)
      Toast.success(`已删除「${selScenario}」`)
      setSelScenario('')
      setScenarios(await listScenarios())
    } catch (e) {
      Toast.error(`删除失败: ${e instanceof Error ? e.message : e}`)
    }
  }

  // ---------- 绘制轨道 ----------
  const startDraw = () => {
    sceneRef.current?.enterDrawMode()
    setDrawMode(true)
    drawPointsRef.current = []
    setDrawPoints([])
    setSelection(null)
  }

  const finishDraw = () => {
    const pts = drawPointsRef.current
    const ok = sceneRef.current?.exitDrawMode(true, pts) ?? false
    if (!ok) {
      Toast.warning('至少需要 3 个航点')
      return
    }
    rebuildKinematics()
    normalizeArc()
    setDrawMode(false)
    drawPointsRef.current = []
    setDrawPoints([])
    setSelection(null)
    Toast.success(`轨道已更新(航点 ${pts.length} 个)`)
  }

  const cancelDraw = () => {
    sceneRef.current?.exitDrawMode(false, [])
    setDrawMode(false)
    drawPointsRef.current = []
    setDrawPoints([])
  }

  const undoDraw = () => {
    const out = sceneRef.current?.undoDrawPoint() ?? []
    drawPointsRef.current = out
    setDrawPoints(out)
  }

  const clearDraw = () => {
    const out = sceneRef.current?.clearDrawPoints() ?? []
    drawPointsRef.current = out
    setDrawPoints(out)
  }

  // ---------- 页面指令(本地生效 + 组帧对外发送) ----------
  const sendMove = (mode: number, linearX: number, targetX = 0) => {
    const kin = kinRef.current
    const ws = wsRef.current
    if (!kin || !ws) return
    kin.applyMove({ mode, linearX, targetX })
    const pl = new Uint8Array([
      ...new Uint8Array([mode]),
      ...be.packU16(Math.max(0, Math.abs(linearX))), ...be.packU16(0), ...be.packU16(0),
      ...be.packI32(targetX), ...be.packI32(0), ...be.packI16(0),
    ])
    ws.send(encodeFrame(nextSeq(), CMD.CHASSIS_MOVE, pl))
  }

  const sendExt = (mode: number, coord = 0) => {
    const kin = kinRef.current
    const ws = wsRef.current
    if (!kin || !ws) return
    kin.applyExt({ mid: 1, mode, speed: 100, coord })
    const pl = new Uint8Array([...new Uint8Array([1, mode]), ...be.packI16(100), ...be.packI32(coord)])
    ws.send(encodeFrame(nextSeq(), CMD.MOTOR_CTRL, pl))
  }

  const wsTag = wsStatus === 'open'
    ? <Tag color="green">仿真已连接</Tag>
    : wsStatus === 'connecting'
      ? <Tag color="orange">仿真连接中…</Tag>
      : <Tag color="red">仿真未连接·重连中</Tag>

  return (
    <div style={{ display: 'flex', flexDirection: 'column', height: 'calc(100vh - 60px)' }}>
      {/* 顶栏 */}
      <div style={{ display: 'flex', alignItems: 'center', gap: 12, padding: '10px 16px', borderBottom: '1px solid var(--semi-color-border, #e8e8e8)' }}>
        <Title heading={5} style={{ margin: 0 }}>机器人仿真</Title>
        {wsTag}
        <Tag color={tcpConnected ? 'green' : 'orange'}>
          {tcpConnected ? 'TCP 上位机已连接' : '等待上位机连接 :50000'}
        </Tag>
        <Space style={{ marginLeft: 'auto' }}>
          <Button size="small" icon={<IconPlusCircle />} onClick={addObstacle}>添加障碍物</Button>
          <Button size="small" icon={<IconPlusCircle />} onClick={addRfid}>添加RFID</Button>
          <Button
            size="small"
            icon={<IconEdit />}
            type={drawMode ? 'danger' : undefined}
            onClick={drawMode ? finishDraw : startDraw}
          >
            {drawMode ? '完成绘制' : '绘制轨道'}
          </Button>
          <Text type="tertiary">挂轨机器人 · {drawMode ? '绘制轨道中' : `${sceneRef.current?.track.kind === 'poly' ? '自定义' : '矩形环'}轨道`} · 协议 V2.0 · 点选对象查看/编辑</Text>
        </Space>
      </div>

      <div style={{ display: 'flex', flex: 1, minHeight: 0 }}>
        {/* 3D 容器 */}
        <div ref={containerRef} style={{ flex: 1, position: 'relative', background: '#141a22' }} />

        {/* 右侧面板 */}
        <div style={{ width: 296, overflowY: 'auto', padding: 12, borderLeft: '1px solid var(--semi-color-border, #e8e8e8)', boxSizing: 'border-box', background: 'var(--semi-color-bg-0, #fff)' }}>
          <Card
            title="机器人状态"
            headerExtraContent={selection ? <Tag color="blue">已选中</Tag> : undefined}
            style={{ marginBottom: 12 }}
          >
            <Descriptions
              row
              data={[
                { key: '弧长 X', value: snap ? `${snap.s} mm` : '—' },
                { key: 'Y / YAW', value: snap ? `0 / ${(snap.yawX10 / 10).toFixed(1)}°` : '—' },
                { key: '速度', value: snap ? `${snap.v} mm/s` : '—' },
                { key: '底盘状态', value: snap ? CHASSIS_STATE_TEXT[snap.state] ?? String(snap.state) : '—' },
                {
                  key: '前方障碍物',
                  value: snap
                    ? snap.blocked
                      ? <Tag color="red">避障停车 {snap.obstacleDist}mm</Tag>
                      : snap.obstacleDist !== null
                        ? `${snap.obstacleDist} mm`
                        : '—'
                    : '—',
                },
                { key: '控制模式', value: '嵌入式控制' },
                { key: '伸缩高度', value: snap ? `${snap.extH} mm` : '—' },
                { key: '伸缩速度', value: snap ? `${snap.extV} mm/s` : '—' },
                { key: '伸缩状态', value: snap ? EXT_STATE_TEXT[snap.extState] ?? String(snap.extState) : '—' },
              ]}
            />
          </Card>

          <Card title="移动指令" style={{ marginBottom: 12 }}>
            <div style={{ marginBottom: 8 }}>
              <Text style={{ marginRight: 8 }}>速度(mm/s)</Text>
              <InputNumber size="small" min={0} max={3000} value={speed} onChange={(v) => setSpeed(Number(v) || 0)} style={{ width: 110 }} />
            </div>
            <Space wrap>
              <Button icon={<IconArrowUp />} onClick={() => sendMove(1, speed)}>前进</Button>
              <Button icon={<IconArrowDown />} onClick={() => sendMove(2, speed)}>后退</Button>
              <Button icon={<IconStop />} type="danger" onClick={() => sendMove(0, 0)}>停止</Button>
            </Space>
            <Divider style={{ margin: '12px 0' }} />
            <div style={{ marginBottom: 8 }}>
              <Text style={{ marginRight: 8 }}>目标弧长(mm)</Text>
              <InputNumber size="small" min={0} max={99999} value={target} onChange={(v) => setTarget(Number(v) || 0)} style={{ width: 110 }} />
            </div>
            <Space wrap>
              <Button icon={<IconMapPin />} theme="solid" onClick={() => sendMove(5, 0, target)}>移动到位置</Button>
              <Button onClick={() => sendMove(6, speed)}>设定速度</Button>
              <Button icon={<IconUndo />} onClick={() => sendMove(10, 0)}>初始化复位</Button>
            </Space>
          </Card>

          <Card title="伸缩杆(电机1)">
            <div style={{ marginBottom: 8 }}>
              <Text style={{ marginRight: 8 }}>目标高度(mm)</Text>
              <InputNumber size="small" min={0} max={600} value={extH} onChange={(v) => setExtH(Number(v) || 0)} style={{ width: 110 }} />
            </div>
            <Space wrap>
              <Button theme="solid" onClick={() => sendExt(3, extH)}>升降到高度</Button>
              <Button onClick={() => sendExt(1, 0)}>上升</Button>
              <Button onClick={() => sendExt(2, 0)}>下降</Button>
              <Button icon={<IconUndo />} onClick={() => sendExt(4, 0)}>复位回零</Button>
            </Space>
          </Card>

          {drawMode && (
            <Card title="绘制轨道" headerExtraContent={<Tag color="orange">绘制中</Tag>} style={{ marginTop: 12, marginBottom: 12 }}>
              <Text type="tertiary">在 3D 场景中点击放置航点(轨道高度 {sceneRef.current?.track.H.toFixed(1)} m, 至少 3 个形成闭合)</Text>
              <div style={{ margin: '8px 0' }}>
                <Text strong>已放置 {drawPoints.length} 个航点</Text>
                {drawPoints.length > 0 && (
                  <div style={{ marginTop: 4 }}>
                    <Text type="tertiary">最后: ({drawPoints[drawPoints.length - 1].x.toFixed(2)}, {drawPoints[drawPoints.length - 1].y.toFixed(2)}, {drawPoints[drawPoints.length - 1].z.toFixed(2)})</Text>
                  </div>
                )}
              </div>
              <Space wrap>
                <Button size="small" icon={<IconUndo />} onClick={undoDraw}>撤销</Button>
                <Button size="small" onClick={clearDraw}>清空</Button>
                <Button size="small" theme="solid" onClick={finishDraw}>完成</Button>
                <Button size="small" onClick={cancelDraw}>取消</Button>
              </Space>
            </Card>
          )}

          <Card title="场景配置" headerExtraContent={<Tag color="violet">多套</Tag>} style={{ marginTop: 12, marginBottom: 12 }}>
            <div style={{ marginBottom: 8, display: 'flex', alignItems: 'center', gap: 8 }}>
              <Text style={{ flexShrink: 0 }}>当前轨道</Text>
              <Text type="tertiary">{trackInfoText()}</Text>
            </div>
            <div style={{ marginBottom: 8, display: 'flex', gap: 8 }}>
              <Input size="small" placeholder="新场景名称" value={scenarioName} onChange={(v) => setScenarioName(v)} style={{ flex: 1 }} />
              <Button size="small" theme="solid" icon={<IconSave />} onClick={handleSaveScenario}>保存</Button>
            </div>
            <div style={{ display: 'flex', gap: 8 }}>
              <Select
                size="small"
                placeholder="选择已保存场景"
                value={selScenario || undefined}
                onChange={(v) => setSelScenario(v as string)}
                style={{ flex: 1 }}
                optionList={scenarios.map((s) => ({
                  value: s.name,
                  label: `${s.name}(${s.obstacleCount}障碍/${s.rfidCount}RFID/${s.trackKind === 'rect' ? '矩形' : '手绘'})`,
                }))}
              />
              <Button size="small" icon={<IconDownload />} onClick={handleLoadScenario}>加载</Button>
              <Button size="small" type="danger" icon={<IconDelete />} onClick={handleDeleteScenario}>删除</Button>
            </div>
          </Card>

          {selection?.type === 'obstacle' && (() => {
            const item = obstacles.find((o) => o.id === selection.id)
            if (!item) return null
            const total = totalLenMm()
            return (
              <Card title={`障碍物 #${item.id}`} headerExtraContent={<Tag color="red">避障</Tag>} style={{ marginTop: 12 }}>
                <div style={{ marginBottom: 6 }}>
                  <Text style={{ marginRight: 8 }}>位置(弧长 mm)</Text>
                  <InputNumber size="small" min={0} max={total} value={item.s} onChange={(v) => updateObstacle(item.id, { s: clampS(v, total) })} style={{ width: 110 }} />
                </div>
                <Slider
                  min={0} max={total} step={10} value={Math.max(0, Math.min(total, item.s))}
                  tooltipVisible
                  onChange={(v) => updateObstacle(item.id, { s: clampS(v, total) })}
                  style={{ marginBottom: 8 }}
                />
                <div style={{ marginBottom: 8 }}>
                  <Text style={{ marginRight: 8 }}>宽度(mm)</Text>
                  <InputNumber size="small" min={50} max={2000} step={50} value={item.width} onChange={(v) => updateObstacle(item.id, { width: Math.max(50, Number(v) || 300) })} style={{ width: 110 }} />
                </div>
                <div style={{ marginBottom: 8, display: 'flex', alignItems: 'center', gap: 8 }}>
                  <Text>启用</Text>
                  <Switch size="small" checked={item.enabled} onChange={(v) => updateObstacle(item.id, { enabled: Boolean(v) })} />
                  <div style={{ flex: 1 }} />
                  <Button size="small" type="danger" icon={<IconDelete />} onClick={() => deleteObstacle(item.id)}>删除</Button>
                </div>
              </Card>
            )
          })()}

          {selection?.type === 'rfid' && (() => {
            const item = rfids.find((r) => r.id === selection.id)
            if (!item) return null
            const total = totalLenMm()
            return (
              <Card title={`RFID 卡 #${item.id}`} headerExtraContent={<Tag color="teal">卡片</Tag>} style={{ marginTop: 12 }}>
                <div style={{ marginBottom: 6 }}>
                  <Text style={{ marginRight: 8 }}>位置(弧长 mm)</Text>
                  <InputNumber size="small" min={0} max={total} value={item.s} onChange={(v) => updateRfid(item.id, { s: clampS(v, total) })} style={{ width: 110 }} />
                </div>
                <Slider
                  min={0} max={total} step={10} value={Math.max(0, Math.min(total, item.s))}
                  tooltipVisible
                  onChange={(v) => updateRfid(item.id, { s: clampS(v, total) })}
                  style={{ marginBottom: 8 }}
                />
                <div style={{ marginBottom: 8, display: 'flex', alignItems: 'center', gap: 8 }}>
                  <Text style={{ flexShrink: 0 }}>RFID ID</Text>
                  <Input size="small" value={rfidIdText} onChange={(v) => setRfidIdText(v)} style={{ width: 130 }} />
                  <Button size="small" icon={<IconRefresh />} onClick={applyRfidId}>修改</Button>
                </div>
                <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between' }}>
                  <Text type="tertiary">当前 ID: {item.tagId}</Text>
                  <Button size="small" type="danger" icon={<IconDelete />} onClick={() => deleteRfid(item.id)}>删除</Button>
                </div>
              </Card>
            )
          })()}
        </div>
      </div>
    </div>
  )
}
