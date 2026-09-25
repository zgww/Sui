import { useRef, useState, useEffect } from 'react'
import { Card, Row, Col, Button, InputNumber, Slider, Divider, Descriptions, Tag, Empty, Modal, Toast } from '@douyinfe/semi-ui'
import { IconUpload } from '@douyinfe/semi-icons'
import { useRobotId } from '../../store/robot'
import WebRTCPlayer, { WebRTCPlayerRef } from '../../components/WebRTCPlayer'
import { fetchInspection, importInspection, gotoWaypoint, captureCalibration, orbCompare } from '../../api/orb'
import { motionMove, ptzAction, liftControl } from '../../api/control'

const miniHbStyle: React.CSSProperties = {
  width: 34, height: 34, borderRadius: '50%', border: '1px solid #dcdfe6',
  background: '#409eff', color: '#fff', display: 'flex', alignItems: 'center', justifyContent: 'center',
  cursor: 'pointer', userSelect: 'none', WebkitUserSelect: 'none', WebkitTapHighlightColor: 'transparent',
  fontSize: 13, transition: 'transform .1s', touchAction: 'none', padding: 0,
}

const fmt = (v: any) => (v != null ? Number(v).toFixed(2) : '-')
const imgUrl = (path: string) => (path ? window.location.origin + path : '')
const wpTypeText = (t: number) => ({ 0: '定点', 1: '途经', 2: '充电', 3: '返回' } as Record<number, string>)[t] ?? '?'

interface OrbWaypoint {
  id?: number
  index: number
  name: string
  type: number
  floor?: number | null
  pose?: { x: number; y: number; theta: number; point?: { x: number; y: number } }
  lift_height?: number | null
  ptz?: { pan: number; tilt: number; zoom: number }
  ptz_param?: { pan: number; tilt: number; zoom: number }
  action?: any[]
  [k: string]: any
}

export default function OrbCalibration() {
  const { selectedRid: rid } = useRobotId()
  const visPlayerRef = useRef<WebRTCPlayerRef>(null)
  const thmPlayerRef = useRef<WebRTCPlayerRef>(null)
  const [wps, setWps] = useState<OrbWaypoint[]>([])
  const [source, setSource] = useState('')
  const [selected, setSelected] = useState<OrbWaypoint | null>(null)
  const [curIdx, setCurIdx] = useState(-1)
  const [loading, setLoading] = useState(false)
  const [going, setGoing] = useState(false)
  const [capturing, setCapturing] = useState(false)
  const [orbResult, setOrbResult] = useState<any>(null)
  const [orbRefImg, setOrbRefImg] = useState('')
  const [orbCurImg, setOrbCurImg] = useState('')
  const [comparing, setComparing] = useState('')
  const [mvSpeed, setMvSpeed] = useState(0.2)
  const [mvLift, setMvLift] = useState(0)
  const [liftH, setLiftH] = useState(1)
  const [previewUrl, setPreviewUrl] = useState('')
  const moveTimer = useRef<ReturnType<typeof setTimeout> | null>(null)
  const ptzTimer = useRef<ReturnType<typeof setTimeout> | null>(null)
  const importFileRef = useRef<HTMLInputElement>(null)

  // 定标图路径(computed)
  const calibVisible = (() => {
    if (!selected) return ''
    const wpId = selected.id || `wp_${selected.index}`
    return `/data/calibration/${wpId}_visible.jpg`
  })()
  const calibThermal = (() => {
    if (!selected) return ''
    const wpId = selected.id || `wp_${selected.index}`
    return `/data/calibration/${wpId}_thermal.jpg`
  })()

  // 切换机器人时清除状态
  useEffect(() => {
    setSelected(null)
    setOrbResult(null)
  }, [rid])

  // ---------- 航点 ----------
  const extractWaypoints = (data: any): OrbWaypoint[] => {
    if (!data) return []
    if (Array.isArray(data)) return data
    if (data.waypoint) return data.waypoint
    if (data.waypoints) return data.waypoints
    if (data.maps) {
      const all: OrbWaypoint[] = []
      for (const m of data.maps) {
        for (const w of (m.waypoints || m.waypoint || [])) {
          if (m.floor != null && w.floor == null) w.floor = m.floor
          all.push(w)
        }
      }
      return all
    }
    return []
  }

  const loadInspection = async () => {
    if (!rid) return
    setLoading(true)
    try {
      const { data } = await fetchInspection(rid)
      if (data.ok) {
        setWps(extractWaypoints(data.data))
        setSource(data.source)
        Toast.success(`拉取: ${extractWaypoints(data.data).length} 个航点`)
      } else {
        Toast.warning(data.msg || '拉取失败')
      }
    } finally { setLoading(false) }
  }

  const onImportFile = (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0]
    if (!file) return
    const reader = new FileReader()
    reader.onload = async (ev) => {
      try {
        const data = JSON.parse(ev.target?.result as string)
        await importInspection(rid!, data)
        setWps(extractWaypoints(data))
        setSource('手动导入')
        Toast.success('已导入')
      } catch {
        Toast.error('JSON 解析失败')
      }
    }
    reader.readAsText(file)
  }

  const selectWp = (w: OrbWaypoint) => {
    const f: OrbWaypoint = { ...w }
    if (w.pose?.point && w.pose.x == null) {
      f.pose = { x: w.pose.point.x, y: w.pose.point.y, theta: (w.pose as any).theta ?? 0 }
    }
    if (!f.ptz && w.ptz_param) {
      f.ptz = { pan: w.ptz_param.pan, tilt: w.ptz_param.tilt, zoom: w.ptz_param.zoom }
    }
    if (!f.ptz && w.action?.length) {
      const a = w.action[0]
      if (a.ptz_param) f.ptz = { pan: a.ptz_param.pan, tilt: a.ptz_param.tilt, zoom: a.ptz_param.zoom }
      if (a.lift_height != null && f.lift_height == null) f.lift_height = a.lift_height
    }
    setSelected(f)
    setCurIdx(w.index ?? 0)
  }

  // ---------- 控制(hold-to-move, 微挪用 speed) ----------
  const hMove = async (cmd: number) => {
    if (!rid) return
    if (moveTimer.current) clearTimeout(moveTimer.current)
    try { await motionMove(rid, cmd, mvSpeed) } catch { /* */ }
  }
  const stopMove = async () => {
    if (!rid) return
    if (moveTimer.current) clearTimeout(moveTimer.current)
    moveTimer.current = setTimeout(async () => {
      try { await motionMove(rid, 0) } catch { /* */ }
    }, 100)
  }
  const hPtz = async (cmd: number) => {
    if (!rid) return
    if (ptzTimer.current) clearTimeout(ptzTimer.current)
    try { await ptzAction(rid, { command: cmd, stop: false, channel: 1 }) } catch { /* */ }
  }
  const stopPtz = async () => {
    if (!rid) return
    if (ptzTimer.current) clearTimeout(ptzTimer.current)
    ptzTimer.current = setTimeout(async () => {
      try { await ptzAction(rid, { command: 0, stop: true, channel: 1 }) } catch { /* */ }
    }, 100)
  }
  const ptzAct = async (cmd: number) => {
    if (!rid) return
    await ptzAction(rid, { command: cmd, stop: false, channel: 1 })
  }
  const liftCmd = async (cmd: number, h?: number) => {
    if (!rid) return
    await liftControl(rid, cmd, h || 0)
  }
  const liftMicro = async (h: number) => {
    if (h > 0 && rid) {
      await liftControl(rid, 3, h)
      Toast.success(`升降→${h}m`)
    }
  }

  // ---------- 前往航点 ----------
  const onGoto = async () => {
    if (!selected || !rid) return
    setGoing(true)
    try {
      const d = selected
      const { data } = await gotoWaypoint(rid, {
        x: d.pose?.x ?? 0, y: d.pose?.y ?? 0, theta: d.pose?.theta ?? 0,
        lift_height: d.lift_height ?? 0, ptz_pan: d.ptz?.pan ?? 0, ptz_tilt: d.ptz?.tilt ?? 0,
        ptz_zoom: d.ptz?.zoom ?? 0, wait_arrive: true,
      })
      Toast.success(data.arrived ? '已到位' : '指令已下发')
    } catch (e: any) {
      Toast.error('前往失败: ' + (e.response?.data?.detail || e.message))
    } finally { setGoing(false) }
  }

  // ---------- 拍照存档 ----------
  const onCapture = async () => {
    if (!selected || !rid) return
    setCapturing(true)
    try {
      const { data } = await captureCalibration(rid, {
        wp_id: selected.id || `wp_${selected.index}`,
        note: selected.name,
      })
      Toast.success('已保存: ' + (data.images?.visible || ''))
    } catch {
      Toast.error('拍照失败')
    } finally { setCapturing(false) }
  }

  // ---------- ORB 比对(通用) ----------
  const doOrbCompare = async (channel: 'visible' | 'thermal', curB64: string) => {
    if (!selected || !rid) return
    setOrbResult(null)
    setOrbCurImg(curB64)
    setOrbRefImg(channel === 'thermal' ? calibThermal : calibVisible)
    try {
      const { data } = await orbCompare(rid, {
        wp_id: selected.id || `wp_${selected.index}`,
        channel, cur_image_base64: curB64,
      })
      setOrbResult(data)
    } catch (e: any) {
      Toast.error('ORB 比对失败: ' + (e.response?.data?.detail || e.message))
    }
  }

  // 截屏(视频)+ORB
  const snapAndCompare = async (channel: 'visible' | 'thermal') => {
    const player = channel === 'thermal' ? thmPlayerRef.current : visPlayerRef.current
    const snap = player?.snapshot()
    if (!snap) { Toast.warning('视频未播放, 请先点播放'); return }
    setComparing(channel)
    await doOrbCompare(channel, snap)
    setComparing('')
  }

  // 拍照(cmd=38)+ORB
  const cmdCaptureAndCompare = async (channel: 'visible' | 'thermal') => {
    setComparing('cmd' + (channel === 'thermal' ? 'thm' : 'vis'))
    try {
      const wpId = selected!.id || `wp_${selected!.index}`
      await captureCalibration(rid!, { wp_id: wpId, note: 'orb-' + channel })
      Toast.success('已拍照并保存')
      // 重新 ORB 比对(用刚保存的图)
      await doOrbCompare(channel, '')
    } catch {
      Toast.error('拍照失败')
    } finally { setComparing('') }
  }

  // D-pad helper
  const moveBtn = (cmd: number, label: string) => (
    <button
      style={miniHbStyle}
      onMouseDown={() => hMove(cmd)} onMouseUp={stopMove} onMouseLeave={stopMove}
      onTouchStart={(e) => { e.preventDefault(); hMove(cmd) }} onTouchEnd={(e) => { e.preventDefault(); stopMove() }}
    >{label}</button>
  )
  const ptzBtn = (cmd: number, label: string) => (
    <button
      style={{ ...miniHbStyle, background: '#67c23a' }}
      onMouseDown={() => hPtz(cmd)} onMouseUp={stopPtz} onMouseLeave={stopPtz}
      onTouchStart={(e) => { e.preventDefault(); hPtz(cmd) }} onTouchEnd={(e) => { e.preventDefault(); stopPtz() }}
    >{label}</button>
  )

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>ORB 配准调试</h2>
        <div className="flex gap-8">
          <Button icon={<IconUpload />} loading={loading} onClick={loadInspection}>拉取航点</Button>
          <div onClick={() => importFileRef.current?.click()} style={{ cursor: 'pointer', display: 'inline-flex' }}>
            <Button icon={<IconUpload />}>导入 JSON</Button>
            <input ref={importFileRef} type="file" accept=".json" style={{ display: 'none' }} onChange={onImportFile} />
          </div>
        </div>
      </div>

      {rid && (
        <Row gutter={[10, 10]}>
          <Col xs={24} md={8}>
            <Card className="card-shadow mb-12" bordered={false} title="可见光视频">
              <WebRTCPlayer ref={visPlayerRef} rid={rid} autoplay={false} />
            </Card>
          </Col>
          <Col xs={24} md={8}>
            <Card className="card-shadow mb-12" bordered={false} title="红外视频">
              <WebRTCPlayer ref={thmPlayerRef} rid={rid} autoplay={false} />
            </Card>
          </Col>
          <Col xs={24} md={8}>
            <Card
              className="card-shadow"
              bordered={false}
              title={
                <div className="flex gap-8" style={{ alignItems: 'center' }}>
                  <span>航点列表 ({wps.length})</span>
                  {source && <Tag color="cyan" size="small">{source}</Tag>}
                </div>
              }
            >
              <div style={{ maxHeight: 260, overflow: 'auto' }} className="mb-12">
                {wps.map((w) => (
                  <div
                    key={w.index}
                    className={`wp-chip ${curIdx === w.index ? 'active' : ''}`}
                    onClick={() => selectWp(w)}
                    style={{
                      padding: '6px 8px', border: '1px solid #ebeef5', borderRadius: 4, marginBottom: 4,
                      cursor: 'pointer', display: 'flex', alignItems: 'center', gap: 6, fontSize: 13,
                      transition: 'all .15s',
                      borderColor: curIdx === w.index ? '#409eff' : undefined,
                      background: curIdx === w.index ? '#ecf5ff' : undefined,
                    }}
                  >
                    <span style={{ color: '#909399', fontFamily: 'monospace', minWidth: 30 }}>#{w.index}</span>
                    <span style={{ fontWeight: 500, flex: 1, overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>{w.name || '(未命名)'}</span>
                    <Tag size="small">{wpTypeText(w.type)}</Tag>
                  </div>
                ))}
                {wps.length === 0 && <Empty description="点击「拉取航点」或「导入 JSON」" />}
              </div>

              {/* 定标图缩略图 */}
              {(calibVisible || calibThermal) && (
                <div className="mb-12">
                  <div className="text-muted" style={{ fontSize: 11 }}>定标图</div>
                  <div className="flex gap-8">
                    {calibVisible && (
                      <img
                        src={calibVisible}
                        style={{ width: 80, height: 60, objectFit: 'cover', borderRadius: 4, cursor: 'pointer' }}
                        onClick={() => setPreviewUrl(calibVisible)}
                        alt="visible"
                      />
                    )}
                    {calibThermal && (
                      <img
                        src={calibThermal}
                        style={{ width: 80, height: 60, objectFit: 'cover', borderRadius: 4, cursor: 'pointer' }}
                        onClick={() => setPreviewUrl(calibThermal)}
                        alt="thermal"
                      />
                    )}
                  </div>
                </div>
              )}

              {/* 选中航点详情 */}
              {selected && (
                <div>
                  <Divider align="left" style={{ margin: '6px 0' }}>详情: {selected.name}</Divider>
                  <Descriptions
                    size="small"
                    row
                    data={[
                      { key: '位姿 X', value: fmt(selected.pose?.x) },
                      { key: 'Y', value: fmt(selected.pose?.y) },
                      { key: 'θ°', value: fmt(selected.pose?.theta) + '°' },
                      { key: '楼层', value: String(selected.floor ?? '-') },
                      { key: '升降', value: fmt(selected.lift_height) + 'm' },
                      { key: 'PTZ', value: `${fmt(selected.ptz?.pan)}/${fmt(selected.ptz?.tilt)}/${fmt(selected.ptz?.zoom)}` },
                    ]}
                  />
                  <div className="flex gap-8 mt-8" style={{ flexWrap: 'wrap' }}>
                    <Button theme="solid" type="primary" size="small" loading={going} onClick={onGoto}>前往航点</Button>
                    <Button theme="solid" type="tertiary" size="small" loading={capturing} onClick={onCapture}>拍照存档</Button>
                  </div>
                </div>
              )}
            </Card>
          </Col>
        </Row>
      )}

      {/* 手动控制 + 微挪 */}
      {rid && (
        <Card className="card-shadow mt-12" bordered={false} title="机器人控制 / 微挪">
          <Row gutter={8}>
            <Col span={6}>
              <div className="text-muted" style={{ fontSize: 11 }}>运动 (按住)</div>
              <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 4, maxWidth: 130, placeItems: 'center', marginTop: 4 }}>
                <div />
                {moveBtn(1, '▲')}
                <div />
                {moveBtn(3, '◀')}
                <button style={{ ...miniHbStyle, background: '#f56c6c' }} onClick={stopMove}>■</button>
                {moveBtn(4, '▶')}
                <div />
                {moveBtn(2, '▼')}
                <div />
              </div>
              {/* 微挪速度 */}
              <div className="flex mt-8" style={{ alignItems: 'center', gap: 4 }}>
                <span className="text-muted" style={{ fontSize: 11 }}>微挪速度:</span>
                <Slider value={mvSpeed} onChange={(v) => setMvSpeed(v as number)} step={0.05} min={0.05} max={0.8} style={{ width: 120 }} />
              </div>
              <div className="flex mt-8" style={{ alignItems: 'center', gap: 4 }}>
                <span className="text-muted" style={{ fontSize: 11 }}>升降微调(m):</span>
                <InputNumber value={mvLift} step={0.05} min={0} size="small" style={{ width: 110 }} onChange={(v) => setMvLift(Number(v) || 0)} />
              </div>
            </Col>
            <Col span={6}>
              <div className="text-muted" style={{ fontSize: 11 }}>云台 (按住)</div>
              <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 4, maxWidth: 130, placeItems: 'center', marginTop: 4 }}>
                <div />
                {ptzBtn(1, '▲')}
                <div />
                {ptzBtn(3, '◀')}
                <button style={{ ...miniHbStyle, background: '#909399' }} onClick={() => ptzAct(0)}>⟲</button>
                {ptzBtn(4, '▶')}
                <div />
                {ptzBtn(2, '▼')}
                <div />
              </div>
            </Col>
            <Col span={6}>
              <div className="text-muted" style={{ fontSize: 11 }}>升降杆</div>
              <div className="flex mt-8" style={{ flexWrap: 'wrap', gap: 4 }}>
                <Button size="small" onClick={() => liftCmd(1)}>展开</Button>
                <Button size="small" onClick={() => liftCmd(2)}>收缩</Button>
                <InputNumber value={liftH} step={0.1} min={0} size="small" style={{ width: 90 }} onChange={(v) => setLiftH(Number(v) || 0)} />
                <Button size="small" theme="solid" type="primary" onClick={() => liftCmd(3, liftH)}>前往</Button>
              </div>
              <div className="mt-8">
                <Button size="small" theme="solid" type="warning" onClick={() => liftMicro(mvLift)}>微调升降</Button>
              </div>
            </Col>
            <Col span={6}>
              <div className="text-muted" style={{ fontSize: 11 }}>拍照比对</div>
              <div className="mt-8" style={{ display: 'flex', flexDirection: 'column', gap: 4 }}>
                <Button size="small" loading={comparing === 'visible'} onClick={() => snapAndCompare('visible')}>截屏+ORB(可见光)</Button>
                <Button size="small" loading={comparing === 'thermal'} onClick={() => snapAndCompare('thermal')}>截屏+ORB(红外)</Button>
                <Button size="small" theme="solid" type="primary" loading={comparing === 'cmdvis'} onClick={() => cmdCaptureAndCompare('visible')}>拍照+ORB(可见光)</Button>
                <Button size="small" theme="solid" type="primary" loading={comparing === 'cmdthm'} onClick={() => cmdCaptureAndCompare('thermal')}>拍照+ORB(红外)</Button>
              </div>
            </Col>
          </Row>
        </Card>
      )}

      {/* ORB 对比: 定标图 vs 当前图 并排 */}
      {orbResult && (
        <Card
          className="card-shadow mt-12"
          bordered={false}
          title={
            <div className="flex gap-8" style={{ alignItems: 'center' }}>
              <span>ORB 比对结果</span>
              <Tag color={orbResult.same_scene ? 'green' : 'red'} size="small">{orbResult.same_scene ? '匹配' : '不匹配'}</Tag>
            </div>
          }
        >
          <Descriptions
            size="small"
            row
            data={[
              { key: 'pHash距离', value: String(orbResult.phash_distance) },
              { key: '总匹配数', value: String(orbResult.total_matches) },
              { key: '内点数', value: String(orbResult.inlier_count) },
              { key: '内点率', value: String(orbResult.inlier_ratio) },
              { key: '覆盖网格', value: String(orbResult.coverage_count) },
              { key: '面积比', value: String(orbResult.area_ratio) },
              { key: '角点在内', value: String(orbResult.corners_in_bounds) },
              { key: '参考特征点', value: String(orbResult.ref_keypoints) },
            ]}
          />
          {/* 并排对比: 定标图 vs 当前图 */}
          <Divider align="left">定标图 vs 当前图</Divider>
          <Row gutter={8}>
            <Col span={12}>
              <div className="text-muted" style={{ fontSize: 11, marginBottom: 4 }}>定标图(参考)</div>
              {orbRefImg && (
                <img src={orbRefImg} style={{ width: '100%', maxHeight: 300, objectFit: 'contain', cursor: 'pointer' }} onClick={() => setPreviewUrl(orbRefImg)} alt="ref" />
              )}
            </Col>
            <Col span={12}>
              <div className="text-muted" style={{ fontSize: 11, marginBottom: 4 }}>当前图</div>
              {orbCurImg && (
                <img src={orbCurImg} style={{ width: '100%', maxHeight: 300, objectFit: 'contain', cursor: 'pointer' }} onClick={() => setPreviewUrl(orbCurImg)} alt="cur" />
              )}
            </Col>
          </Row>
          {/* 过程图 */}
          <Divider align="left">ORB 过程图</Divider>
          <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(200px, 1fr))', gap: 8 }}>
            {Object.entries(orbResult.images || {}).map(([k, v]) => (
              <div key={k} style={{ textAlign: 'center' }}>
                <div style={{ fontSize: 11, color: '#909399', marginBottom: 2 }}>{k}</div>
                <img src={imgUrl(v as string)} style={{ width: '100%', maxHeight: 180, objectFit: 'contain', cursor: 'pointer' }} onClick={() => setPreviewUrl(imgUrl(v as string))} alt={k} />
              </div>
            ))}
          </div>
        </Card>
      )}

      {/* 图片预览 */}
      <Modal visible={!!previewUrl} title="图片预览" onCancel={() => setPreviewUrl('')} footer={null} width={800}>
        {previewUrl && <img src={previewUrl} style={{ width: '100%' }} alt="preview" />}
      </Modal>

      <style>{`
        .wp-chip:hover { border-color: #b3d8ff; background: #f5faff; }
      `}</style>
    </div>
  )
}
