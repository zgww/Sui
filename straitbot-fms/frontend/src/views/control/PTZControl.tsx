import { useRef, useState } from 'react'
import { Card, Row, Col, Button, InputNumber, Descriptions, Toast } from '@douyinfe/semi-ui'
import { IconArrowUp, IconArrowDown, IconArrowLeft, IconArrowRight, IconRefresh } from '@douyinfe/semi-icons'
import { useRobotId } from '../../store/robot'
import { ptzGetPose, ptzSetPose, ptzAction, cameraCapture, liftStatus, liftControl } from '../../api/control'

interface Ptz {
  pan: number
  tilt: number
  zoom: number
}

const holdBtnStyle: React.CSSProperties = {
  width: 58,
  height: 58,
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
  fontSize: 13,
  padding: 0,
}

export default function PTZControl() {
  const { selectedRid: rid } = useRobotId()
  const [ptz, setPtz] = useState<Ptz>({ pan: 0, tilt: 0, zoom: 0 })
  const [captureResult, setCaptureResult] = useState<any>(null)
  const [lift, setLift] = useState<any>({})
  const [liftHeight, setLiftHeight] = useState(1)
  const ptzStopTimer = useRef<ReturnType<typeof setTimeout> | null>(null)

  const setField = (k: keyof Ptz, v: any) =>
    setPtz((p) => ({ ...p, [k]: v == null ? 0 : Number(v) }))

  // 按住: 开始云台动作(stop=false)
  const holdPtz = async (cmd: number) => {
    if (!rid) return
    if (ptzStopTimer.current) clearTimeout(ptzStopTimer.current)
    try { await ptzAction(rid, { command: cmd, stop: false, channel: 1 }) } catch { /* */ }
  }

  // 松开: 停止云台动作(stop=true)
  const stopPtz = async () => {
    if (!rid) return
    if (ptzStopTimer.current) clearTimeout(ptzStopTimer.current)
    ptzStopTimer.current = setTimeout(async () => {
      try { await ptzAction(rid, { command: 0, stop: true, channel: 1 }) } catch { /* */ }
    }, 100)
  }

  const action = async (cmd: number) => {
    if (!rid) return
    await ptzAction(rid, { command: cmd, stop: false, channel: 1 })
  }

  const setPose = async () => {
    const { data } = await ptzSetPose(rid!, ptz)
    Toast.success(data.msg)
  }

  const getPose = async () => {
    const { data } = await ptzGetPose(rid!)
    if (data.ok && data.data) {
      setPtz({ pan: data.data.pan, tilt: data.data.tilt, zoom: data.data.zoom })
    }
  }

  const capture = async (cmd: number) => {
    const { data } = await cameraCapture(rid!, cmd)
    if (data.ok) {
      setCaptureResult(data.data)
      Toast.success('完成')
    } else {
      Toast.warning(data.msg)
    }
  }

  const getLift = async () => {
    const { data } = await liftStatus(rid!)
    if (data.ok) setLift(data.data || {})
  }

  const liftCmd = async (cmd: number, h?: number) => {
    const { data } = await liftControl(rid!, cmd, h || 0)
    Toast.success(data.msg)
  }

  const btnProps = (cmd: number) => ({
    onMouseDown: () => holdPtz(cmd),
    onMouseUp: stopPtz,
    onMouseLeave: stopPtz,
    onTouchStart: (e: React.TouchEvent) => { e.preventDefault(); holdPtz(cmd) },
    onTouchEnd: (e: React.TouchEvent) => { e.preventDefault(); stopPtz() },
    disabled: !rid,
  })

  return (
    <div className="page-container">
      <div className="mb-12"><h2 style={{ margin: 0 }}>云台控制</h2></div>

      <Row gutter={[12, 12]} className="mt-12">
        <Col xs={24} sm={12}>
          <Card className="card-shadow" bordered={false} title="方向控制 (按住转动, 松开停止)">
            <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 8, maxWidth: 240, margin: '0 auto', placeItems: 'center' }}>
              <div />
              <button className="hold-btn" style={holdBtnStyle} {...btnProps(1)}>
                <IconArrowUp size="large" />
              </button>
              <div />
              <button className="hold-btn" style={holdBtnStyle} {...btnProps(3)}>
                <IconArrowLeft size="large" />
              </button>
              <button
                className="hold-btn reset-btn"
                style={{ ...holdBtnStyle, background: '#909399' }}
                onMouseDown={() => action(0)}
                onTouchStart={(e) => { e.preventDefault(); action(0) }}
                disabled={!rid}
              >
                <IconRefresh size="large" />
              </button>
              <button className="hold-btn" style={holdBtnStyle} {...btnProps(4)}>
                <IconArrowRight size="large" />
              </button>
              <div />
              <button className="hold-btn" style={holdBtnStyle} {...btnProps(2)}>
                <IconArrowDown size="large" />
              </button>
              <div />
            </div>
            <div className="mt-12 flex gap-8" style={{ justifyContent: 'center' }}>
              <button
                className="hold-btn zoom-btn"
                style={{ ...holdBtnStyle, width: 'auto', padding: '0 16px', borderRadius: 20, background: '#67c23a' }}
                {...btnProps(9)}
              >变倍+</button>
              <button
                className="hold-btn zoom-btn"
                style={{ ...holdBtnStyle, width: 'auto', padding: '0 16px', borderRadius: 20, background: '#67c23a' }}
                {...btnProps(10)}
              >变倍-</button>
            </div>
          </Card>
        </Col>

        <Col xs={24} sm={12}>
          <Card className="card-shadow" bordered={false} title="精确位姿 (cmd=36)">
            <div style={{ display: 'grid', gridTemplateColumns: '80px 1fr', rowGap: 8, alignItems: 'center' }}>
              <span>水平</span>
              <InputNumber value={ptz.pan} step={1} onChange={(v) => setField('pan', v)} />
              <span>垂直</span>
              <InputNumber value={ptz.tilt} step={1} onChange={(v) => setField('tilt', v)} />
              <span>变倍</span>
              <InputNumber value={ptz.zoom} step={0.1} onChange={(v) => setField('zoom', v)} />
              <div />
              <div className="flex gap-8">
                <Button theme="solid" type="primary" disabled={!rid} onClick={setPose}>转到此位姿</Button>
                <Button disabled={!rid} onClick={getPose}>读取当前</Button>
              </div>
            </div>
          </Card>
        </Col>
      </Row>

      {/* 拍照 + 升降杆 */}
      <Row gutter={[12, 12]} className="mt-12">
        <Col xs={24} sm={12}>
          <Card className="card-shadow" bordered={false} title="拍照 / 录像 / 测温 (cmd=38)">
            <div className="flex gap-8" style={{ flexWrap: 'wrap' }}>
              <Button disabled={!rid} onClick={() => capture(1)}>可见光拍照</Button>
              <Button disabled={!rid} onClick={() => capture(2)}>红外拍照</Button>
              <Button disabled={!rid} onClick={() => capture(3)}>开始录像</Button>
              <Button theme="solid" type="danger" disabled={!rid} onClick={() => capture(5)}>停止录像</Button>
              <Button theme="solid" type="warning" disabled={!rid} onClick={() => capture(4)}>红外测温</Button>
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
          </Card>
        </Col>

        <Col xs={24} sm={12}>
          <Card className="card-shadow" bordered={false} title="升降杆 (cmd=41)">
            <div style={{ display: 'grid', gridTemplateColumns: '80px 1fr', rowGap: 8, alignItems: 'center' }}>
              <span>当前状态</span>
              <div className="flex gap-8" style={{ alignItems: 'center' }}>
                <span className="text-muted">{lift.height ?? '-'} m / {lift.speed ?? '-'} m/s</span>
                <Button size="small" theme="borderless" disabled={!rid} onClick={getLift}>刷新</Button>
              </div>
              <span>指定高度</span>
              <div className="flex gap-8" style={{ alignItems: 'center' }}>
                <InputNumber value={liftHeight} step={0.1} min={0} onChange={(v) => setLiftHeight(Number(v) || 0)} />
                <Button size="small" theme="solid" type="primary" disabled={!rid} onClick={() => liftCmd(3, liftHeight)}>前往</Button>
              </div>
              <div />
              <div className="flex gap-8" style={{ flexWrap: 'wrap' }}>
                <Button disabled={!rid} onClick={() => liftCmd(1)}>展开</Button>
                <Button disabled={!rid} onClick={() => liftCmd(2)}>收缩</Button>
                <Button disabled={!rid} onClick={() => liftCmd(4)}>复位</Button>
                <Button theme="solid" type="danger" disabled={!rid} onClick={() => liftCmd(0)}>停止</Button>
              </div>
            </div>
          </Card>
        </Col>
      </Row>

      <style>{`
        .hold-btn:active { transform: scale(0.9); }
        .hold-btn:disabled { opacity: .4; cursor: not-allowed; }
      `}</style>
    </div>
  )
}
