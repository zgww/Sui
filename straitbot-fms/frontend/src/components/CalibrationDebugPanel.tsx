import { useState, useRef, useEffect } from 'react'
import { Button, Divider, Tag, Spin, Collapsible } from '@douyinfe/semi-ui'
import {
  IconChevronDown, IconChevronRight, IconRefresh,
} from '@douyinfe/semi-icons'
import { motionSetPose, ptzSetPose, liftControl, liftStatus, cameraCapture, motionGetPose } from '../api/control'
import {
  calibRegister, calibXAxisStep, calibXAxisIter, calibPtzStep, calibPtzIter,
  calibMoveToWaypoint, debugImageUrl,
  type CalibResponse,
} from '../api/calibration'
import type { TreeNode, OrbRegistration, ActionNode } from '../types'

// ========== 类型 ==========

interface StepLog {
  text: string
  type: 'info' | 'success' | 'error' | 'step'
}

interface Props {
  node: TreeNode
  rid: number | null
}

// ========== 工具 ==========

const fmt = (v: number | undefined, digits = 4): string =>
  v == null ? '—' : v.toFixed(digits)

/** 调试图片标题映射 */
const IMAGE_TITLES: Record<string, string> = {
  '00_ref_mask.jpg': '参考图掩膜',
  '00_cur_mask.jpg': '当前图掩膜',
  '01_ref_keypoints.jpg': '参考图特征点',
  '01_cur_keypoints.jpg': '当前图特征点',
  '02_matches.jpg': '匹配结果',
  '03_reference_outline.jpg': '参考轮廓映射',
  '04_warped_reference.jpg': '参考图变换后',
  '05_blended.jpg': '叠加结果',
}

// ========== 主组件 ==========

export default function CalibrationDebugPanel({ node, rid }: Props) {
  const isOrb = node.nodeType === 'OrbRegistration'
  const isAction = node.nodeType === 'ActionNode'
  const [logs, setLogs] = useState<StepLog[]>([])
  const [busy, setBusy] = useState<string | null>(null) // 当前正在执行的操作名
  const [result, setResult] = useState<CalibResponse | null>(null)
  const [expanded, setExpanded] = useState(true)
  const logEndRef = useRef<HTMLDivElement>(null)

  // 切换节点时清空
  useEffect(() => {
    setLogs([])
    setResult(null)
    setBusy(null)
  }, [node.id])

  // 自动滚动到底部
  useEffect(() => {
    logEndRef.current?.scrollIntoView({ behavior: 'smooth', block: 'end' })
  }, [logs])

  const addLog = (text: string, type: StepLog['type'] = 'info') => {
    setLogs((prev) => [...prev, { text, type }])
  }

  const clearLogs = () => {
    setLogs([])
    setResult(null)
  }

  // ---- 云台调整 ----
  const handlePtzAdjust = async () => {
    if (!rid) return
    setBusy('ptz')
    setLogs([])
    setResult(null)
    try {
      const ptz = isOrb
        ? (node as OrbRegistration).ptz
        : (node as ActionNode).ptz_param
      const liftHeight = isOrb
        ? (node as OrbRegistration).lift_height ?? 0
        : (node as ActionNode).lift_height ?? 0

      addLog(`调整云台: pan=${ptz.pan}° tilt=${ptz.tilt}° zoom=${ptz.zoom}x`, 'step')
      const { data: ptzRes } = await ptzSetPose(rid, { pan: ptz.pan, tilt: ptz.tilt, zoom: ptz.zoom })
      if (ptzRes.ok) addLog('  云台指令已发送 ✓', 'success')
      else addLog(`  云台指令失败: ${ptzRes.msg}`, 'error')

      if (liftHeight > 0) {
        addLog(`调整升降杆: height=${liftHeight}m`, 'step')
        const { data: liftRes } = await liftControl(rid, 3, liftHeight)
        if (liftRes.ok) addLog('  升降杆指令已发送 ✓', 'success')
        else addLog(`  升降杆指令失败: ${liftRes.msg}`, 'error')
      }

      addLog('等待云台到位…', 'info')
      await new Promise((r) => setTimeout(r, 3000))

      addLog('云台调整完成', 'success')
    } catch {
      addLog('云台调整异常', 'error')
    } finally {
      setBusy(null)
    }
  }

  // ---- 抓拍 ----
  const handleCapture = async () => {
    if (!rid) return
    setBusy('capture')
    try {
      addLog('正在抓拍可见光图像…', 'step')
      const { data } = await cameraCapture(rid, 1)
      if (data.ok) {
        addLog('抓拍成功 ✓', 'success')
        if (data.data) {
          const d = data.data
          if (d.image || d.base64) {
            addLog(`  返回 base64 图片数据`, 'info')
          }
          if (d.file || d.path) {
            addLog(`  机器人本地文件: ${d.file || d.path}`, 'info')
          }
        }
      } else {
        addLog(`抓拍失败: ${data.msg}`, 'error')
      }
    } catch {
      addLog('抓拍异常', 'error')
    } finally {
      setBusy(null)
    }
  }

  // ---- 读取当前位姿 ----
  const handleGetPose = async () => {
    if (!rid) return
    setBusy('pose')
    try {
      addLog('读取当前机器人位姿…', 'step')
      const { data: poseRes } = await motionGetPose(rid)
      if (poseRes.ok && poseRes.data) {
        const d = poseRes.data
        const x = d.x ?? d.point?.x ?? 0
        const y = d.y ?? d.point?.y ?? 0
        const theta = d.theta ?? 0
        addLog(`  位姿: x=${fmt(x)} y=${fmt(y)} θ=${fmt(theta)}°`, 'success')
      } else {
        addLog(`读取位姿失败: ${poseRes.msg}`, 'error')
      }
    } catch {
      addLog('读取位姿异常', 'error')
    } finally {
      setBusy(null)
    }
  }

  // ---- 升降杆调整 ----
  const handleLiftAdjust = async () => {
    if (!rid) return
    setBusy('lift')
    setLogs([])
    setResult(null)
    try {
      const liftHeight = isOrb
        ? (node as OrbRegistration).lift_height ?? 0
        : (node as ActionNode).lift_height ?? 0
      if (liftHeight <= 0) {
        addLog('升降杆高度未配置 (≤0), 跳过', 'info')
        return
      }
      // 先查询当前升降杆状态
      addLog('查询当前升降杆状态…', 'info')
      const { data: ls } = await liftStatus(rid)
      const curHeight = ls?.data?.height ?? ls?.ok ? (ls as any).height : null
      if (curHeight != null) {
        addLog(`当前高度: ${Number(curHeight).toFixed(2)}m, 目标高度: ${liftHeight}m`, 'info')
        if (Math.abs(Number(curHeight) - liftHeight) < 0.05) {
          addLog('当前高度与目标高度一致 (差值<0.05m), 无需调整 ✓', 'success')
          return
        }
      } else {
        addLog('无法获取当前高度, 直接下发调整指令', 'info')
      }
      addLog(`调整升降杆: height=${liftHeight}m`, 'step')
      const { data: liftRes } = await liftControl(rid, 3, liftHeight)
      if (liftRes.ok) addLog('  升降杆指令已发送 ✓', 'success')
      else addLog(`  升降杆指令失败: ${liftRes.msg}`, 'error')
      addLog('升降杆调整完成', 'success')
    } catch {
      addLog('升降杆调整异常', 'error')
    } finally {
      setBusy(null)
    }
  }

  // ---- 仅配准 ----
  const handleRegister = async () => {
    if (!rid) return
    setBusy('register')
    setLogs([])
    setResult(null)
    try {
      addLog('调用后端配准接口(调整云台→抓拍→ORB配准)…', 'step')
      const { data } = await calibRegister(rid, node.id)
      setResult(data)
      data.steps?.forEach((s) => addLog(s, s.includes('失败') || s.includes('异常') ? 'error' : 'info'))
      if (data.ok && data.registered) {
        addLog(`配准完成: ${data.message}`, 'success')
      } else if (!data.ok) {
        addLog(`配准失败: ${data.message}`, 'error')
      }
    } catch {
      addLog('配准请求异常', 'error')
    } finally {
      setBusy(null)
    }
  }

  // ---- 移动到航点 ----
  const handleMoveToWaypoint = async () => {
    if (!rid) return
    setBusy('move')
    setLogs([])
    setResult(null)
    try {
      addLog(`调用移动到航点接口(节点: ${node.id})…`, 'step')
      const { data } = await calibMoveToWaypoint(rid, node.id)
      setResult(data)
      data.steps?.forEach((s) => addLog(s, s.includes('失败') || s.includes('异常') ? 'error' : 'info'))
      if (data.ok) {
        addLog(`移动到航点完成: ${data.message}`, 'success')
      } else {
        addLog(`移动到航点失败: ${data.message}`, 'error')
      }
    } catch {
      addLog('移动到航点请求异常', 'error')
    } finally {
      setBusy(null)
    }
  }

  // ---- 单次X轴定位校准 ----
  const handleXAxisStep = async () => {
    if (!rid) return
    setBusy('xaxis-step')
    setLogs([])
    setResult(null)
    try {
      addLog('调用单次X轴定位校准(配准→坐标变换→移动, 最小0.01m)…', 'step')
      const { data } = await calibXAxisStep(rid, node.id)
      setResult(data)
      data.steps?.forEach((s) => addLog(s, s.includes('失败') || s.includes('异常') ? 'error' : 'info'))
      if (data.ok && data.calibrated) {
        if (data.converged) {
          addLog(`已收敛: ${data.message}`, 'success')
        } else {
          addLog(`单次校准完成: ${data.message}`, 'success')
        }
      } else if (!data.ok) {
        addLog(`定位校准失败: ${data.message}`, 'error')
      }
    } catch {
      addLog('定位校准请求异常', 'error')
    } finally {
      setBusy(null)
    }
  }

  // ---- 迭代X轴定位校准 ----
  const handleXAxisIter = async () => {
    if (!rid) return
    setBusy('xaxis-iter')
    setLogs([])
    setResult(null)
    try {
      addLog('调用迭代X轴定位校准(最多10次, 阈值15px)…', 'step')
      const { data } = await calibXAxisIter(rid, node.id)
      setResult(data)
      data.steps?.forEach((s) => addLog(s, s.includes('失败') || s.includes('异常') ? 'error' : 'info'))
      if (data.ok) {
        if (data.converged) {
          addLog(`迭代校准成功: ${data.message}`, 'success')
        } else {
          addLog(`迭代未收敛: ${data.message}`, 'info')
        }
      } else {
        addLog(`迭代校准失败: ${data.message}`, 'error')
      }
    } catch {
      addLog('迭代校准请求异常', 'error')
    } finally {
      setBusy(null)
    }
  }

  // ---- 单次云台校准 ----
  const handlePtzStep = async () => {
    if (!rid) return
    setBusy('ptz-step')
    setLogs([])
    setResult(null)
    try {
      addLog('调用单次云台校准(抓拍→配准→修正pan/tilt)…', 'step')
      const { data } = await calibPtzStep(rid, node.id)
      setResult(data)
      data.steps?.forEach((s) => addLog(s, s.includes('失败') || s.includes('异常') ? 'error' : 'info'))
      if (data.ok) {
        if (data.converged) {
          addLog(`已收敛: ${data.message}`, 'success')
        } else {
          addLog(`单次云台校准完成: ${data.message}`, 'success')
        }
      } else {
        addLog(`云台校准失败: ${data.message}`, 'error')
      }
    } catch {
      addLog('云台校准请求异常', 'error')
    } finally {
      setBusy(null)
    }
  }

  // ---- 迭代云台校准 ----
  const handlePtzIter = async () => {
    if (!rid) return
    setBusy('ptz-iter')
    setLogs([])
    setResult(null)
    try {
      addLog(`调用迭代云台校准(最多8次, 阈值10px)…`, 'step')
      const { data } = await calibPtzIter(rid, node.id)
      setResult(data)
      data.steps?.forEach((s) => addLog(s, s.includes('失败') || s.includes('异常') ? 'error' : 'info'))
      if (data.ok) {
        if (data.converged) {
          addLog(`云台校准成功: ${data.message}`, 'success')
        } else {
          addLog(`云台校准未收敛: ${data.message}`, 'info')
        }
      } else {
        addLog(`云台校准失败: ${data.message}`, 'error')
      }
    } catch {
      addLog('云台校准请求异常', 'error')
    } finally {
      setBusy(null)
    }
  }

  const logColor = (type: StepLog['type']): string => {
    switch (type) {
      case 'success': return '#52c41a'
      case 'error': return '#f5222d'
      case 'step': return '#1890ff'
      default: return '#666'
    }
  }

  const logBg = (type: StepLog['type']): string => {
    switch (type) {
      case 'success': return '#f6ffed'
      case 'error': return '#fff2f0'
      case 'step': return '#e6f7ff'
      default: return '#fafafa'
    }
  }

  return (
    <div style={{ marginTop: 12 }}>
      <div
        style={{ cursor: 'pointer', userSelect: 'none', display: 'flex', alignItems: 'center', gap: 6 }}
        onClick={() => setExpanded((v) => !v)}
      >
        {expanded ? <IconChevronDown /> : <IconChevronRight />}
        <span style={{ fontWeight: 600, fontSize: 13 }}>
          逐步调试
        </span>
        <Tag size="small" color={isOrb ? 'purple' : 'orange'}>
          {isOrb ? 'ORB配准' : '动作点'}
        </Tag>
      </div>

      <Collapsible isOpen={expanded}>
        <div style={{ paddingTop: 8 }}>
          {/* 操作按钮 */}
          <div style={{ display: 'flex', flexWrap: 'wrap', gap: 6, marginBottom: 8 }}>
            <Button
              size="small"
              onClick={handlePtzAdjust}
              loading={busy === 'ptz'}
              disabled={!!busy}
            >
              云台调整
            </Button>
            <Button
              size="small"
              onClick={handleCapture}
              loading={busy === 'capture'}
              disabled={!!busy}
            >
              抓拍
            </Button>
            <Button
              size="small"
              onClick={handleGetPose}
              loading={busy === 'pose'}
              disabled={!!busy}
            >
              读位姿
            </Button>
            <Button
              size="small"
              onClick={handleLiftAdjust}
              loading={busy === 'lift'}
              disabled={!!busy}
            >
              升降杆调整
            </Button>

            {isOrb && (
              <>
                <Button
                  size="small"
                  theme="solid"
                  style={{ background: '#2e8b57' }}
                  onClick={handleRegister}
                  loading={busy === 'register'}
                  disabled={!!busy}
                >
                  配准
                </Button>
                <Button
                  size="small"
                  theme="solid"
                  type="primary"
                  onClick={handleXAxisStep}
                  loading={busy === 'xaxis-step'}
                  disabled={!!busy}
                >
                  单次X轴
                </Button>
                <Button
                  size="small"
                  theme="solid"
                  style={{ background: '#722ed1' }}
                  onClick={handleXAxisIter}
                  loading={busy === 'xaxis-iter'}
                  disabled={!!busy}
                >
                  迭代X轴
                </Button>
                <Button
                  size="small"
                  theme="solid"
                  style={{ background: '#fa8c16' }}
                  onClick={handleMoveToWaypoint}
                  loading={busy === 'move'}
                  disabled={!!busy}
                >
                  移动到航点
                </Button>
              </>
            )}

            {isAction && (
              <>
                <Button
                  size="small"
                  theme="solid"
                  type="warning"
                  onClick={handlePtzStep}
                  loading={busy === 'ptz-step'}
                  disabled={!!busy}
                >
                  单次云台
                </Button>
                <Button
                  size="small"
                  theme="solid"
                  style={{ background: '#722ed1' }}
                  onClick={handlePtzIter}
                  loading={busy === 'ptz-iter'}
                  disabled={!!busy}
                >
                  迭代云台
                </Button>
              </>
            )}

            <Button
              size="small"
              theme="borderless"
              icon={<IconRefresh />}
              onClick={clearLogs}
              disabled={!!busy}
            >
              清空
            </Button>
          </div>

          {/* 日志区 */}
          {busy && (
            <div style={{ marginBottom: 6 }}>
              <Spin size="small" />
              <span style={{ marginLeft: 8, color: '#1890ff', fontSize: 12 }}>
                执行中… (云台校准可能需要较长时间)
              </span>
            </div>
          )}

          {logs.length > 0 && (
            <div
              style={{
                maxHeight: 360,
                overflowY: 'auto',
                background: '#1e1e1e',
                borderRadius: 6,
                padding: 8,
                fontFamily: 'Consolas, Monaco, monospace',
                fontSize: 12,
                lineHeight: 1.6,
              }}
            >
              {logs.map((log, i) => (
                <div
                  key={i}
                  style={{
                    color: logColor(log.type),
                    background: logBg(log.type),
                    padding: '2px 6px',
                    borderRadius: 3,
                    marginBottom: 2,
                    wordBreak: 'break-all',
                  }}
                >
                  {log.text}
                </div>
              ))}
              <div ref={logEndRef} />
            </div>
          )}

          {/* 结果详情 */}
          {result && (
            <ResultDetails result={result} isOrb={isOrb} rid={rid} />
          )}
        </div>
      </Collapsible>
    </div>
  )
}

// ========== 结果详情子组件 ==========

function ResultDetails({ result, isOrb, rid }: { result: CalibResponse; isOrb: boolean; rid: number | null }) {
  const [showDetails, setShowDetails] = useState(true)

  if (!result.details && !result.iterations?.length && !result.debug_images?.length) return null

  return (
    <div style={{ marginTop: 8 }}>
      <div
        style={{ cursor: 'pointer', userSelect: 'none', display: 'flex', alignItems: 'center', gap: 4 }}
        onClick={() => setShowDetails((v) => !v)}
      >
        {showDetails ? <IconChevronDown size="small" /> : <IconChevronRight size="small" />}
        <span style={{ fontSize: 12, fontWeight: 600, color: '#606266' }}>配准指标详情</span>
      </div>

      {showDetails && (
        <div style={{ marginTop: 4 }}>
          {/* 配准指标 */}
          {result.details && (
            <div style={{ background: '#f6f8fa', borderRadius: 6, padding: 8, fontSize: 12, fontFamily: 'Consolas, Monaco, monospace' }}>
              <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '2px 12px' }}>
                <span>X偏移(px): <b>{fmt(result.details.x_offset_px)}</b></span>
                <span>Y偏移(px): <b>{fmt(result.details.y_offset_px ?? 0)}</b></span>
                <span>匹配数: <b>{result.details.total_matches}</b></span>
                <span>内点数: <b>{result.details.inlier_count}</b></span>
              </div>

              {/* X轴校准坐标变换 */}
              {result.details.scale_m_per_px != null && (
                <div style={{ marginTop: 6, paddingTop: 6, borderTop: '1px dashed #d0d0d0' }}>
                  <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '2px 12px' }}>
                    <span>scale(m/px): <b>{result.details.scale_m_per_px}</b></span>
                    <span>Δd(m): <b>{fmt(result.details.delta_d_m ?? 0, 6)}</b></span>
                    <span>方向系数: <b>{result.details.pan_coef?.toFixed(0)}</b></span>
                    <span>移动距离(m): <b>{fmt(result.details.move_distance_m ?? 0, 6)}</b></span>
                    <span>Δx: <b>{fmt(result.details.world_dx ?? 0, 6)}</b></span>
                    <span>Δy: <b>{fmt(result.details.world_dy ?? 0, 6)}</b></span>
                  </div>
                  {result.details.from && result.details.to && (
                    <div style={{ marginTop: 4, color: '#1890ff' }}>
                      ({fmt(result.details.from.x)} → {fmt(result.details.to.x)},{' '}
                      {fmt(result.details.from.y)} → {fmt(result.details.to.y)})
                    </div>
                  )}
                </div>
              )}

              {/* 单应矩阵 */}
              {result.details.homography && (
                <div style={{ marginTop: 6, paddingTop: 6, borderTop: '1px dashed #d0d0d0' }}>
                  <span style={{ color: '#888' }}>单应矩阵 H:</span>
                  {result.details.homography.map((row, i) => (
                    <div key={i} style={{ paddingLeft: 12 }}>
                      [{row.map((v) => v.toFixed(6)).join(', ')}]
                    </div>
                  ))}
                </div>
              )}
            </div>
          )}

          {/* 云台校准迭代列表 */}
          {result.iterations && result.iterations.length > 0 && (
            <div style={{ marginTop: 6 }}>
              <div style={{ fontSize: 12, color: '#606266', marginBottom: 4 }}>
                迭代记录 ({result.iterations.length}/{result.max_iterations} 次, 阈值 {result.threshold_px}px)
              </div>
              <div style={{ display: 'flex', flexDirection: 'column', gap: 4 }}>
                {result.iterations.map((iter) => (
                  <div
                    key={iter.iteration}
                    style={{
                      background: iter.converged ? '#f6ffed' : iter.error ? '#fff2f0' : '#f6f8fa',
                      borderRadius: 4,
                      padding: '4px 8px',
                      fontSize: 11,
                      fontFamily: 'Consolas, Monaco, monospace',
                      borderLeft: `3px solid ${iter.converged ? '#52c41a' : iter.error ? '#f5222d' : '#1890ff'}`,
                    }}
                  >
                    <div style={{ display: 'flex', justifyContent: 'space-between' }}>
                      <span>
                        第{iter.iteration}轮 {iter.converged ? '✓ 收敛' : iter.error ? '✗ 错误' : ''}
                      </span>
                      <span>
                        {iter.total_offset_px != null ? (
                          <>总偏移: <b>{fmt(iter.total_offset_px)}</b>px</>
                        ) : (
                          <>X偏移: <b>{fmt(iter.x_offset_px)}</b>px</>
                        )}
                      </span>
                    </div>
                    <div style={{ color: '#666', marginTop: 2 }}>
                      X={fmt(iter.x_offset_px)}px
                      {iter.y_offset_px != null && <> Y={fmt(iter.y_offset_px)}px</>}
                      {' | '}匹配:{iter.total_matches} 内点:{iter.inlier_count}
                    </div>
                    {iter.pan_delta != null && (
                      <div style={{ color: '#1890ff', marginTop: 2 }}>
                        pan: {iter.ptz_from?.pan.toFixed(2)}° → {iter.ptz_to?.pan.toFixed(2)}° (Δ{iter.pan_delta.toFixed(4)}°) |{' '}
                        tilt: {iter.ptz_from?.tilt.toFixed(2)}° → {iter.ptz_to?.tilt.toFixed(2)}° (Δ{iter.tilt_delta?.toFixed(4)}°)
                      </div>
                    )}
                    {iter.move_distance_m != null && (
                      <div style={{ color: '#722ed1', marginTop: 2 }}>
                        移动: {fmt(iter.move_distance_m, 6)}m
                        {iter.from && iter.to && (
                          <> | ({fmt(iter.from.x)} → {fmt(iter.to.x)}, {fmt(iter.from.y)} → {fmt(iter.to.y)})</>
                        )}
                      </div>
                    )}
                    {iter.error && (
                      <div style={{ color: '#f5222d', marginTop: 2 }}>{iter.error}</div>
                    )}
                    {iter.debug_images && iter.debug_images.length > 0 && rid != null && result.debug_session && (
                      <div style={{ marginTop: 4 }}>
                        <DebugImageGallery
                          rid={rid}
                          session={result.debug_session}
                          images={iter.debug_images}
                        />
                      </div>
                    )}
                  </div>
                ))}
              </div>
            </div>
          )}

          {/* 调试图片画廊 */}
          {result.debug_session && result.debug_images && result.debug_images.length > 0 && rid != null && (
            <div style={{ marginTop: 8 }}>
              <div style={{ fontSize: 12, fontWeight: 600, color: '#606266', marginBottom: 4 }}>
                调试可视化图片
              </div>
              <DebugImageGallery
                rid={rid}
                session={result.debug_session}
                images={result.debug_images}
              />
            </div>
          )}
        </div>
      )}
    </div>
  )
}

// ========== 调试图片画廊子组件 ==========

function DebugImageGallery({ rid, session, images }: { rid: number; session: string; images: string[] }) {
  return (
    <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(160px, 1fr))', gap: 8 }}>
      {images.map((filename) => {
        const url = debugImageUrl(rid, session + '/' + filename)
        const title = IMAGE_TITLES[filename] ?? filename
        return (
          <a
            key={filename}
            href={url}
            target="_blank"
            rel="noreferrer"
            style={{ textDecoration: 'none', display: 'block' }}
          >
            <div style={{ border: '1px solid #e0e0e0', borderRadius: 4, overflow: 'hidden', background: '#fafafa' }}>
              <div style={{ height: 200, display: 'flex', alignItems: 'center', justifyContent: 'center', background: '#1e1e1e' }}>
                <img
                  src={url}
                  alt={title}
                  style={{ maxHeight: 200, maxWidth: '100%', objectFit: 'contain', cursor: 'pointer' }}
                />
              </div>
              <div style={{ padding: '4px 6px', fontSize: 11, color: '#606266', textAlign: 'center', whiteSpace: 'nowrap', overflow: 'hidden', textOverflow: 'ellipsis' }}>
                {title}
              </div>
            </div>
          </a>
        )
      })}
    </div>
  )
}
