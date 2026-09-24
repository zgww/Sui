import { useRef, useState, useEffect } from 'react'
import { Card, Row, Col, Button, Modal, Input, Switch, Divider, Descriptions, Table, Tag, Toast } from '@douyinfe/semi-ui'
import { useRobotId } from '../../store/robot'
import WebRTCPlayer, { WebRTCPlayerRef } from '../../components/WebRTCPlayer'
import { cameraCapture } from '../../api/control'
import { listStreams } from '../../api/video'
import { listRobots, updateRobot } from '../../api/robots'

interface VideoCfg {
  video_server: string
  video_secret: string
  video_visible_stream: string
  video_thermal_stream: string
  video_use_robot_ip: boolean
}

export default function VideoStream() {
  const { selectedRid: rid } = useRobotId()
  const playerRef = useRef<WebRTCPlayerRef>(null)
  const [captureResult, setCaptureResult] = useState<any>(null)
  const [snapshotImg, setSnapshotImg] = useState('')
  const [showConfig, setShowConfig] = useState(false)
  const [saving, setSaving] = useState(false)
  const [streams, setStreams] = useState<any[]>([])
  const [cfg, setCfg] = useState<VideoCfg>({
    video_server: '', video_secret: '', video_visible_stream: '',
    video_thermal_stream: '', video_use_robot_ip: false,
  })

  const setCfgField = (k: keyof VideoCfg, v: any) => setCfg((c) => ({ ...c, [k]: v }))

  // 切换机器人时清除状态
  useEffect(() => {
    setCaptureResult(null)
    setSnapshotImg('')
  }, [rid])

  // ---- 抓拍(机器人 cmd=38) ----
  const capture = async (cmd: number) => {
    const { data } = await cameraCapture(rid!, cmd)
    if (data.ok) {
      setCaptureResult(data.data)
      Toast.success('完成')
    } else {
      Toast.warning(data.msg)
    }
  }

  // ---- 截屏(浏览器侧, 从 video 取帧) ----
  const snapshotFromVideo = () => {
    const img = playerRef.current?.snapshot()
    if (!img) { Toast.warning('视频未播放, 无法截屏'); return }
    setSnapshotImg(img)
    Toast.success('已截屏')
  }

  const downloadSnapshot = () => {
    if (!snapshotImg) return
    const a = document.createElement('a')
    a.href = snapshotImg
    a.download = `snapshot_${Date.now()}.jpg`
    a.click()
  }

  const saveAsCalibration = () => {
    const key = `calibration_${rid}_${Date.now()}`
    localStorage.setItem(key, snapshotImg)
    Toast.success('已暂存为定标图, 可在航点管理中引用')
  }

  // ---- 视频配置 ----
  const loadConfig = async (ridVal?: number) => {
    const id = ridVal ?? rid
    if (!id) return
    const { data: list } = await listRobots()
    const r = list.find((x) => x.id === id)
    if (r) {
      setCfg({
        video_server: r.video_server || '',
        video_secret: r.video_secret || '',
        video_visible_stream: r.video_visible_stream || '',
        video_thermal_stream: r.video_thermal_stream || '',
        video_use_robot_ip: !!r.video_use_robot_ip,
      })
    }
  }

  const saveConfig = async () => {
    setSaving(true)
    try {
      const { data: list } = await listRobots()
      const r = list.find((x) => x.id === rid)
      const payload = { ...r, ...cfg }
      await updateRobot(rid!, payload)
      Toast.success('已保存')
      setShowConfig(false)
      playerRef.current?.restart()
    } finally { setSaving(false) }
  }

  const loadStreams = async () => {
    const { data } = await listStreams(rid!)
    if (data.ok) {
      setStreams(data.data)
      Toast.success(`找到 ${data.data.length} 路流`)
    } else {
      setStreams([])
      Toast.warning(data.msg)
    }
  }

  // 打开配置弹窗时加载
  useEffect(() => {
    if (showConfig) loadConfig()
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [showConfig])

  const streamColumns = [
    { title: 'app', dataIndex: 'app', width: 80 },
    { title: 'stream', dataIndex: 'stream', minWidth: 140 },
    {
      title: '协议',
      render: (_text: any, record: any) => (
        <>
          {(record.tracks || []).map((s: any, i: number) => (
            <Tag key={i} size="small" style={{ marginRight: 4 }}>{s.type}</Tag>
          ))}
        </>
      ),
    },
  ]

  return (
	    <div className="page-container">
	      <div className="mb-12"><h2 style={{ margin: 0 }}>视频流 / 抓拍</h2></div>

	      {rid && (
        <Row gutter={[12, 12]} className="mt-12">
          {/* 左: 视频播放 */}
          <Col xs={24} sm={16}>
            <Card
              className="card-shadow"
              bordered={false}
              title={
                <div className="flex-between">
                  <span>实时视频 (WebRTC)</span>
                  <Button size="small" theme="borderless" onClick={() => setShowConfig(true)}>视频配置</Button>
                </div>
              }
            >
              <WebRTCPlayer ref={playerRef} rid={rid} />
            </Card>
          </Col>

          {/* 右: 抓拍 + 定标图 */}
          <Col xs={24} sm={8}>
            <Card className="card-shadow mb-12" bordered={false} title="抓拍 / 测温 (cmd=38)">
              <div className="flex gap-8" style={{ flexWrap: 'wrap' }}>
                <Button disabled={!rid} onClick={() => capture(1)}>可见光拍照</Button>
                <Button disabled={!rid} onClick={() => capture(2)}>红外拍照</Button>
                <Button theme="solid" type="warning" disabled={!rid} onClick={() => capture(4)}>红外测温</Button>
                <Button disabled={!rid} onClick={() => capture(3)}>开始录像</Button>
                <Button theme="solid" type="danger" disabled={!rid} onClick={() => capture(5)}>停止录像</Button>
                <Button theme="solid" type="tertiary" disabled={!rid} onClick={snapshotFromVideo}>截屏存档</Button>
              </div>
              {captureResult && (
                <div className="mt-12">
                  <Descriptions
                    size="small"
                    row
                    data={[
                      { key: '文件', value: captureResult.file || '-' },
                      ...(captureResult.temperature
                        ? [{ key: '测温', value: `最高 ${captureResult.temperature.high?.temp}° / 最低 ${captureResult.temperature.low?.temp}°` }]
                        : []),
                    ]}
                  />
                </div>
              )}
              {snapshotImg && (
                <div className="mt-12">
                  <div className="text-muted" style={{ fontSize: 12 }}>截屏预览(浏览器侧):</div>
                  <img src={snapshotImg} style={{ maxWidth: '100%', borderRadius: 4, marginTop: 4 }} alt="snapshot" />
                  <div className="mt-8 flex gap-8">
                    <Button size="small" onClick={downloadSnapshot}>下载</Button>
                    <Button size="small" theme="solid" type="primary" onClick={saveAsCalibration}>存为定标图</Button>
                  </div>
                </div>
              )}
            </Card>
          </Col>
        </Row>
      )}

      {/* 视频配置弹窗 */}
      <Modal
        visible={showConfig}
        title="视频流配置 (ZLMediaKit)"
        onCancel={() => setShowConfig(false)}
        footer={null}
        width={640}
      >
        <div style={{ display: 'grid', gridTemplateColumns: '140px 1fr', rowGap: 10, alignItems: 'center' }}>
          <span>ZLMediaKit 地址</span>
          <Input value={cfg.video_server} placeholder="http://192.168.6.54" onChange={(v) => setCfgField('video_server', v)} />
          <span>API Secret</span>
          <Input value={cfg.video_secret} placeholder="ZLM secret(可空)" onChange={(v) => setCfgField('video_secret', v)} />
        </div>
        <Divider align="left">可见光流</Divider>
        <div style={{ display: 'grid', gridTemplateColumns: '140px 1fr', rowGap: 10, alignItems: 'center' }}>
          <span>流标识</span>
          <Input value={cfg.video_visible_stream} placeholder="live/robot-109 或 live/{ip_last}" onChange={(v) => setCfgField('video_visible_stream', v)} />
        </div>
        <Divider align="left">红外流</Divider>
        <div style={{ display: 'grid', gridTemplateColumns: '140px 1fr', rowGap: 10, alignItems: 'center' }}>
          <span>流标识</span>
          <Input value={cfg.video_thermal_stream} placeholder="live/thermal-109" onChange={(v) => setCfgField('video_thermal_stream', v)} />
        </div>
        <Divider align="left">选项</Divider>
        <div style={{ display: 'grid', gridTemplateColumns: '140px 1fr', rowGap: 10, alignItems: 'center' }}>
          <span>未配流名按 IP</span>
          <div className="flex gap-8" style={{ alignItems: 'center' }}>
            <Switch checked={cfg.video_use_robot_ip} onChange={(v) => setCfgField('video_use_robot_ip', v)} />
            <span className="text-muted">开启时未填流名自动用 IP 末段命名</span>
          </div>
        </div>
        <div className="flex gap-8 mt-12">
          <Button onClick={loadStreams}>查询 ZLM 在线流</Button>
          <Button theme="solid" type="primary" loading={saving} onClick={saveConfig}>保存配置</Button>
        </div>
        {streams.length > 0 && (
          <Table
            className="mt-12"
            columns={streamColumns}
            dataSource={streams}
            pagination={false}
            rowKey={(record: any) => (record.app || '') + '/' + (record.stream || '')}
            size="small"
          />
        )}
      </Modal>
    </div>
  )
}
