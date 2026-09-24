import { useRef, useState, useEffect } from 'react'
import { Card, Row, Col, Button, Select, InputNumber, Input, TextArea, Divider, Empty, Modal, Checkbox, Tag, Popconfirm, Toast } from '@douyinfe/semi-ui'
import { IconDownload, IconUpload, IconPlus, IconEdit, IconDelete } from '@douyinfe/semi-icons'
import { useRobotId } from '../../store/robot'
import WebRTCPlayer, { WebRTCPlayerRef } from '../../components/WebRTCPlayer'
import {
  listMaps, createMap, updateMap, deleteMap,
  listWaypoints, createWaypoint, updateWaypoint,
  saveCalibrationBase64, currentPose, exportRobot, importRobot, exportFileUrl,
} from '../../api/waypoint'
import { motionMove, ptzAction, liftControl } from '../../api/control'
import type { WaypointMap, Waypoint } from '../../types'

interface Editing {
  id: number | null
  name: string
  type: number
  floor: number | null
  pose_x: number
  pose_y: number
  pose_theta: number
  lift_height: number
  ptz_pan: number
  ptz_tilt: number
  ptz_zoom: number
  calib_visible: string
  calib_thermal: string
  note: string
}

const emptyEditing: Editing = {
  id: null, name: '', type: 0, floor: null,
  pose_x: 0, pose_y: 0, pose_theta: 0,
  lift_height: 0, ptz_pan: 0, ptz_tilt: 0, ptz_zoom: 0,
  calib_visible: '', calib_thermal: '', note: '',
}

const miniHbStyle: React.CSSProperties = {
  width: 38, height: 38, borderRadius: '50%', border: '1px solid #dcdfe6',
  background: '#409eff', color: '#fff', display: 'flex', alignItems: 'center', justifyContent: 'center',
  cursor: 'pointer', userSelect: 'none', WebkitUserSelect: 'none', WebkitTapHighlightColor: 'transparent',
  fontSize: 14, transition: 'transform .1s', touchAction: 'none', padding: 0,
}

const wpTypeText = (t: number) => ({ 0: '定点', 1: '途经', 2: '充电', 3: '返回' } as Record<number, string>)[t] ?? '?'
const wpTypeColor = (t: number) => ({ 0: 'blue', 1: 'cyan', 2: 'orange', 3: 'green' } as Record<number, string>)[t] ?? 'blue'
const fmt = (n: any) => (n != null ? Number(n).toFixed(2) : '-')

export default function WaypointManager() {
  const { selectedRid: rid } = useRobotId()
  const playerRef = useRef<WebRTCPlayerRef>(null)
  const [maps, setMaps] = useState<WaypointMap[]>([])
  const [curMapId, setCurMapId] = useState<number | null>(null)
  const [wps, setWps] = useState<Waypoint[]>([])
  const [saving, setSaving] = useState(false)
  const [savingCalib, setSavingCalib] = useState('')
  const [liftH, setLiftH] = useState(1)
  const moveTimer = useRef<ReturnType<typeof setTimeout> | null>(null)
  const ptzTimer = useRef<ReturnType<typeof setTimeout> | null>(null)
  const snapCache = useRef<{ visible: string; thermal: string }>({ visible: '', thermal: '' })
  const [editing, setEditing] = useState<Editing>({ ...emptyEditing })
  const [mapDlgVisible, setMapDlgVisible] = useState(false)
  const [mapDlgId, setMapDlgId] = useState<number | null>(null)
  const [mapDlgData, setMapDlgData] = useState({ name: '', floor: null as number | null, scale: 1.0, note: '' })
  const [showImport, setShowImport] = useState(false)
  const [importReplace, setImportReplace] = useState(false)
  const [importing, setImporting] = useState(false)
  const importData = useRef<any>(null)
  const [previewUrl, setPreviewUrl] = useState('')
  const importFileRef = useRef<HTMLInputElement>(null)

  const setEdit = (patch: Partial<Editing>) => setEditing((e) => ({ ...e, ...patch }))

  // 切换机器人时重新加载地图
  useEffect(() => {
    setEditing({ ...emptyEditing })
    snapCache.current = { visible: '', thermal: '' }
    setCurMapId(null)
    if (rid) loadMaps(rid)
  }, [rid])

  // ---------- 机器人/地图切换 ----------
  const loadMaps = async (ridVal?: number) => {
    const id = ridVal ?? rid
    if (!id) return
    const { data } = await listMaps(id)
    setMaps(data)
    const next = data.length ? data[0].id : null
    setCurMapId(next)
    if (next) await loadWaypoints(next)
  }

  const loadWaypoints = async (mid?: number) => {
    const id = mid ?? curMapId
    if (!id) { setWps([]); return }
    const { data } = await listWaypoints(id)
    setWps(data)
  }

  // ---------- 地图 ----------
  const newMap = () => {
    setMapDlgId(null)
    setMapDlgData({ name: '', floor: null, scale: 1.0, note: '' })
    setMapDlgVisible(true)
  }

  const editMap = () => {
    const m = maps.find((x) => x.id === curMapId)
    if (!m) return
    setMapDlgId(m.id)
    setMapDlgData({ name: m.name, floor: m.floor, scale: m.scale, note: m.note || '' })
    setMapDlgVisible(true)
  }

  const saveMapDlg = async () => {
    const d = mapDlgData
    if (!d.name) { Toast.warning('请填名称'); return }
    if (mapDlgId) {
      await updateMap(mapDlgId, d)
    } else {
      const { data } = await createMap(rid!, d)
      setCurMapId(data.id)
    }
    setMapDlgVisible(false)
    await loadMaps()
  }

  const removeMap = async () => {
    await deleteMap(curMapId!)
    setCurMapId(null)
    await loadMaps()
  }

  // ---------- 航点 ----------
  const resetForm = () => {
    const m = maps.find((x) => x.id === curMapId)
    setEditing({ ...emptyEditing, floor: m?.floor ?? null })
    snapCache.current = { visible: '', thermal: '' }
  }

  const selectWp = (w: Waypoint) => {
    setEditing({
      id: w.id, name: w.name, type: w.type, floor: w.floor,
      pose_x: w.pose.x, pose_y: w.pose.y, pose_theta: w.pose.theta,
      lift_height: w.lift_height,
      ptz_pan: w.ptz.pan, ptz_tilt: w.ptz.tilt, ptz_zoom: w.ptz.zoom,
      calib_visible: w.calib_visible, calib_thermal: w.calib_thermal,
      note: w.note,
    })
    snapCache.current = { visible: '', thermal: '' }
  }

  const saveWaypoint = async () => {
    if (!curMapId) { Toast.warning('请先选择地图'); return }
    setSaving(true)
    try {
      const payload = {
        name: editing.name, type: editing.type, floor: editing.floor,
        pose_x: editing.pose_x, pose_y: editing.pose_y, pose_theta: editing.pose_theta,
        lift_height: editing.lift_height,
        ptz_pan: editing.ptz_pan, ptz_tilt: editing.ptz_tilt, ptz_zoom: editing.ptz_zoom,
        calib_visible: editing.calib_visible, calib_thermal: editing.calib_thermal,
        note: editing.note,
      }
      if (editing.id) {
        await updateWaypoint(editing.id, payload)
      } else {
        const { data } = await createWaypoint(curMapId, payload)
        setEdit({ id: data.id })
      }
      Toast.success('已保存')
      await loadWaypoints()
    } finally { setSaving(false) }
  }

  const readCurrent = async () => {
    if (!rid) return
    try {
      const { data } = await currentPose(rid)
      if (data.pose) {
        setEdit({
          pose_x: data.pose.x ?? 0,
          pose_y: data.pose.y ?? 0,
          pose_theta: data.pose.theta ?? 0,
          floor: (data.floor != null && editing.floor == null) ? data.floor : editing.floor,
        })
      }
      if (data.ptz) {
        setEdit({
          ptz_pan: data.ptz.pan ?? 0,
          ptz_tilt: data.ptz.tilt ?? 0,
          ptz_zoom: data.ptz.zoom ?? 0,
        })
      }
      if (data.lift) setEdit({ lift_height: data.lift.height ?? editing.lift_height })
      Toast.success('已读取当前位姿')
    } catch (e: any) {
      Toast.warning('读取失败: ' + (e.message || e))
    }
  }

  // ---------- 定标图 ----------
  const snapshotTo = (channel: 'visible' | 'thermal') => {
    const img = playerRef.current?.snapshot()
    if (!img) { Toast.warning('视频未播放, 无法截屏'); return }
    snapCache.current[channel] = img
    setEdit({ ['calib_' + channel]: img } as Partial<Editing>)
    Toast.success('已截屏, 点击「保存」存档')
  }

  const saveCalib = async (channel: 'visible' | 'thermal') => {
    if (!editing.id) { Toast.warning('请先保存航点'); return }
    const img = snapCache.current[channel]
    if (!img) { Toast.warning('请先截屏'); return }
    setSavingCalib(channel)
    try {
      const { data } = await saveCalibrationBase64(editing.id, channel, img)
      setEdit({ ['calib_' + channel]: data.path } as Partial<Editing>)
      snapCache.current[channel] = ''
      Toast.success('定标图已保存')
      await loadWaypoints()
    } finally { setSavingCalib('') }
  }

  const previewImg = (url: string) => { if (url) setPreviewUrl(url) }

  // ---------- 控制 ----------
  const hMove = async (cmd: number) => {
    if (!rid) return
    if (moveTimer.current) clearTimeout(moveTimer.current)
    try { await motionMove(rid, cmd) } catch { /* */ }
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

  // ---------- 导入/导出 ----------
  const exportJson = async () => {
    const { data } = await exportRobot(rid!)
    const blob = new Blob([JSON.stringify(data, null, 2)], { type: 'application/json' })
    const a = document.createElement('a')
    a.href = URL.createObjectURL(blob)
    a.download = `waypoints_${Date.now()}.json`
    a.click()
    Toast.success('已导出')
  }
  const downloadFile = () => {
    window.open(exportFileUrl(rid!), '_blank')
  }

  const onPickFile = (e: React.ChangeEvent<HTMLInputElement>) => {
    const f = e.target.files?.[0]
    if (!f) return
    const reader = new FileReader()
    reader.onload = (ev) => {
      try {
        importData.current = JSON.parse(ev.target?.result as string)
        Toast.success('文件已加载')
      } catch {
        Toast.error('JSON 解析失败')
      }
    }
    reader.readAsText(f)
  }

  const doImport = async () => {
    if (!importData.current) { Toast.warning('请先选择文件'); return }
    setImporting(true)
    try {
      const { data } = await importRobot(rid!, importData.current, importReplace)
      Toast.success(data.msg)
      setShowImport(false)
      await loadMaps()
    } finally { setImporting(false) }
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

  const calibCell = (channel: 'visible' | 'thermal', label: string) => {
    const calibUrl = channel === 'visible' ? editing.calib_visible : editing.calib_thermal
    return (
    <div style={{ flex: 1, textAlign: 'center' }}>
      {calibUrl ? (
        <img
          src={calibUrl}
          style={{ width: '100%', aspectRatio: '4/3', objectFit: 'cover', borderRadius: 4, cursor: 'pointer', border: '1px solid #ebeef5' }}
          onClick={() => previewImg(calibUrl)}
          alt={label}
        />
      ) : (
        <div style={{ width: '100%', aspectRatio: '4/3', border: '1px dashed #dcdfe6', borderRadius: 4, display: 'flex', alignItems: 'center', justifyContent: 'center', color: '#c0c4cc', fontSize: 13 }}>
          {label}
        </div>
      )}
      <div style={{ marginTop: 6, display: 'flex', flexDirection: 'column', gap: 4 }}>
        <Button size="small" onClick={() => snapshotTo(channel)}>截屏</Button>
        <Button size="small" theme="solid" type="primary" loading={savingCalib === channel} disabled={!editing.id} onClick={() => saveCalib(channel)}>保存</Button>
      </div>
    </div>
    )
  }

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>航点管理 / 录点</h2>
        <div className="flex gap-8">
          <Button icon={<IconDownload />} disabled={!rid} onClick={exportJson}>导出 JSON</Button>
          <Button icon={<IconUpload />} disabled={!rid} onClick={() => setShowImport(true)}>导入</Button>
          <Button icon={<IconDownload />} disabled={!rid} onClick={downloadFile}>下载文件</Button>
        </div>
      </div>

      {/* 地图选择条 */}
      {rid && (
        <Card className="card-shadow mb-12" bordered={false} bodyStyle={{ padding: '10px 14px' }}>
          <div className="flex gap-8" style={{ alignItems: 'center', flexWrap: 'wrap' }}>
            <span className="text-muted">地图:</span>
            <Select
              value={curMapId ?? undefined}
              placeholder="选择地图"
              style={{ width: 240 }}
              onChange={(v) => { setCurMapId(v as number); loadWaypoints(v as number) }}
              optionList={maps.map((m) => ({
                value: m.id,
                label: `${m.name || '未命名'} ${m.floor != null ? '(F' + m.floor + ')' : ''} [${m.waypoint_count || 0}]`,
              }))}
            />
            <Button size="small" icon={<IconPlus />} onClick={newMap}>新建地图</Button>
            <Button size="small" icon={<IconEdit />} disabled={!curMapId} onClick={editMap}>编辑地图</Button>
            <Popconfirm title="删除地图会连同航点一起删除?" onConfirm={removeMap} disabled={!curMapId}>
              <Button size="small" theme="solid" type="danger" icon={<IconDelete />} disabled={!curMapId}>删除地图</Button>
            </Popconfirm>
          </div>
        </Card>
      )}

      {rid && curMapId && (
        <Row gutter={[12, 12]}>
          {/* 左: 视频 + 控制 */}
          <Col xs={24} md={10}>
            <Card className="card-shadow mb-12" bordered={false} title="实时视频">
              <WebRTCPlayer ref={playerRef} rid={rid} autoplay={false} />
            </Card>

            <Card className="card-shadow" bordered={false} title="机器人控制 (按住移动)">
              <Row gutter={8}>
                <Col span={12}>
                  <div className="text-muted" style={{ fontSize: 12, marginBottom: 4 }}>运动</div>
                  <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 5, maxWidth: 150, placeItems: 'center' }}>
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
                </Col>
                <Col span={12}>
                  <div className="text-muted" style={{ fontSize: 12, marginBottom: 4 }}>云台</div>
                  <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 5, maxWidth: 150, placeItems: 'center' }}>
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
              </Row>
              <Divider align="left">升降杆</Divider>
              <div className="flex gap-8" style={{ flexWrap: 'wrap' }}>
                <Button size="small" onClick={() => liftCmd(1)}>展开</Button>
                <Button size="small" onClick={() => liftCmd(2)}>收缩</Button>
                <InputNumber value={liftH} step={0.1} min={0} size="small" style={{ width: 110 }} onChange={(v) => setLiftH(Number(v) || 0)} />
                <Button size="small" theme="solid" type="primary" onClick={() => liftCmd(3, liftH)}>前往</Button>
                <Button size="small" theme="solid" type="danger" onClick={() => liftCmd(0)}>停</Button>
              </div>
            </Card>
          </Col>

          {/* 中: 航点表单 */}
          <Col xs={24} md={8}>
            <Card
              className="card-shadow"
              bordered={false}
              title={
                <div className="flex-between">
                  <span>{editing.id ? '编辑航点' : '新增航点'}</span>
                  <Button size="small" theme="borderless" type="primary" disabled={!rid} onClick={readCurrent}>读取当前位姿</Button>
                </div>
              }
            >
              <div style={{ display: 'grid', gridTemplateColumns: '76px 1fr', rowGap: 8, alignItems: 'center' }}>
                <span>名称</span>
                <Input value={editing.name} placeholder="如 变压器A" onChange={(v) => setEdit({ name: v })} />
                <span>类型</span>
                <Select
                  value={editing.type}
                  onChange={(v) => setEdit({ type: v as number })}
                  style={{ width: '100%' }}
                  optionList={[
                    { value: 0, label: '定点' }, { value: 1, label: '途经' },
                    { value: 2, label: '充电' }, { value: 3, label: '返回' },
                  ]}
                />
                <span>楼层</span>
                <InputNumber value={editing.floor ?? undefined} step={1} onChange={(v) => setEdit({ floor: v != null ? Number(v) : null })} />
              </div>
              <Divider align="left">位姿</Divider>
              <div style={{ display: 'grid', gridTemplateColumns: '76px 1fr', rowGap: 8, alignItems: 'center' }}>
                <span>X</span>
                <InputNumber value={editing.pose_x} step={0.01} onChange={(v) => setEdit({ pose_x: Number(v) || 0 })} />
                <span>Y</span>
                <InputNumber value={editing.pose_y} step={0.01} onChange={(v) => setEdit({ pose_y: Number(v) || 0 })} />
                <span>θ°</span>
                <InputNumber value={editing.pose_theta} step={0.1} onChange={(v) => setEdit({ pose_theta: Number(v) || 0 })} />
              </div>
              <Divider align="left">设备</Divider>
              <div style={{ display: 'grid', gridTemplateColumns: '76px 1fr', rowGap: 8, alignItems: 'center' }}>
                <span>升降m</span>
                <InputNumber value={editing.lift_height} step={0.1} min={0} onChange={(v) => setEdit({ lift_height: Number(v) || 0 })} />
                <span>云台P</span>
                <InputNumber value={editing.ptz_pan} step={1} onChange={(v) => setEdit({ ptz_pan: Number(v) || 0 })} />
                <span>云台T</span>
                <InputNumber value={editing.ptz_tilt} step={1} onChange={(v) => setEdit({ ptz_tilt: Number(v) || 0 })} />
                <span>云台Z</span>
                <InputNumber value={editing.ptz_zoom} step={0.1} onChange={(v) => setEdit({ ptz_zoom: Number(v) || 0 })} />
                <span>备注</span>
                <TextArea value={editing.note} onChange={(v) => setEdit({ note: v })} rows={2} />
              </div>

              <Divider align="left">定标图</Divider>
              <div style={{ display: 'flex', gap: 10 }}>
                {calibCell('visible', '可见光')}
                {calibCell('thermal', '红外')}
              </div>

              <div style={{ marginTop: 12 }} className="flex gap-8">
                <Button theme="solid" type="primary" loading={saving} onClick={saveWaypoint}>保存航点</Button>
                <Button onClick={resetForm}>清空</Button>
              </div>
            </Card>
          </Col>

          {/* 右: 航点列表 */}
          <Col xs={24} md={6}>
            <Card
              className="card-shadow"
              bordered={false}
              title={
                <div className="flex-between">
                  <span>航点列表 ({wps.length})</span>
                  <Button size="small" theme="borderless" type="primary" onClick={resetForm}>+ 新增</Button>
                </div>
              }
            >
              <div style={{ maxHeight: '70vh', overflow: 'auto' }}>
                {wps.map((w) => (
                  <div
                    key={w.id}
                    className={`wp-item ${editing.id === w.id ? 'active' : ''}`}
                    onClick={() => selectWp(w)}
                    style={{
                      position: 'relative', padding: '8px 10px', border: '1px solid #ebeef5', borderRadius: 6,
                      marginBottom: 6, cursor: 'pointer', transition: 'all .15s',
                      borderColor: editing.id === w.id ? '#409eff' : undefined,
                      background: editing.id === w.id ? '#ecf5ff' : undefined,
                    }}
                  >
                    <div style={{ display: 'flex', alignItems: 'center', gap: 6, fontSize: 13 }}>
                      <Tag color={wpTypeColor(w.type) as any} size="small">{wpTypeText(w.type)}</Tag>
                      <span style={{ color: '#909399', fontFamily: 'monospace' }}>#{w.index}</span>
                      <span style={{ fontWeight: 500, flex: 1, overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>{w.name || '(未命名)'}</span>
                      {w.floor != null && <span style={{ fontSize: 11, color: '#fff', background: '#909399', padding: '0 5px', borderRadius: 8 }}>F{w.floor}</span>}
                    </div>
                    <div className="text-muted" style={{ fontSize: 11, marginTop: 2 }}>
                      ({fmt(w.pose.x)}, {fmt(w.pose.y)}, {fmt(w.pose.theta)}°)
                      {w.actions?.length ? ` · ${w.actions.length}动作` : ''}
                    </div>
                    <div style={{ position: 'absolute', top: 6, right: 8, fontSize: 12 }}>
                      {w.calib_visible && <span title="有可见光定标图">📷</span>}
                      {w.calib_thermal && <span title="有红外定标图">🌡</span>}
                    </div>
                  </div>
                ))}
                {wps.length === 0 && <Empty description="暂无航点" />}
              </div>
            </Card>
          </Col>
        </Row>
      )}

      {/* 地图编辑弹窗 */}
      <Modal
        visible={mapDlgVisible}
        title={mapDlgId ? '编辑地图' : '新建地图'}
        onCancel={() => setMapDlgVisible(false)}
        footer={null}
        width={460}
      >
        <div style={{ display: 'grid', gridTemplateColumns: '80px 1fr', rowGap: 12, alignItems: 'center' }}>
          <span>名称</span>
          <Input value={mapDlgData.name} onChange={(v) => setMapDlgData((d) => ({ ...d, name: v }))} />
          <span>楼层</span>
          <InputNumber value={mapDlgData.floor ?? undefined} step={1} onChange={(v) => setMapDlgData((d) => ({ ...d, floor: v != null ? Number(v) : null }))} />
          <span>比例</span>
          <InputNumber value={mapDlgData.scale} step={0.1} min={0.01} onChange={(v) => setMapDlgData((d) => ({ ...d, scale: Number(v) || 1 }))} />
          <span>备注</span>
          <Input value={mapDlgData.note} onChange={(v) => setMapDlgData((d) => ({ ...d, note: v }))} />
        </div>
        <div className="flex gap-8 mt-12" style={{ justifyContent: 'flex-end' }}>
          <Button onClick={() => setMapDlgVisible(false)}>取消</Button>
          <Button theme="solid" type="primary" onClick={saveMapDlg}>确定</Button>
        </div>
      </Modal>

      {/* 导入弹窗 */}
      <Modal
        visible={showImport}
        title="导入航点 JSON"
        onCancel={() => setShowImport(false)}
        footer={null}
        width={520}
      >
        <div onClick={() => importFileRef.current?.click()} style={{ cursor: 'pointer' }}>
          <Button icon={<IconUpload />}>选择 JSON 文件</Button>
          <input ref={importFileRef} type="file" accept=".json" style={{ display: 'none' }} onChange={onPickFile} />
        </div>
        <div className="mt-12">
          <Checkbox checked={importReplace} onChange={(e) => setImportReplace(!!e.target.checked)}>覆盖(先清空该机器人旧数据)</Checkbox>
        </div>
        <div className="flex gap-8 mt-12" style={{ justifyContent: 'flex-end' }}>
          <Button onClick={() => setShowImport(false)}>取消</Button>
          <Button theme="solid" type="primary" loading={importing} onClick={doImport}>导入</Button>
        </div>
      </Modal>

      {/* 图片预览 */}
      <Modal visible={!!previewUrl} title="图片预览" onCancel={() => setPreviewUrl('')} footer={null} width={720}>
        {previewUrl && <img src={previewUrl} style={{ width: '100%' }} alt="preview" />}
      </Modal>

      <style>{`
        .wp-item:hover { border-color: #b3d8ff; background: #f5faff; }
      `}</style>
    </div>
  )
}
