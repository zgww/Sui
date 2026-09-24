import { useRef, useState, useEffect } from 'react'
import { Card, Row, Col, Button, Popconfirm, InputNumber, Divider, Toast } from '@douyinfe/semi-ui'
import { IconArrowUp, IconArrowDown, IconArrowLeft, IconArrowRight, IconStop } from '@douyinfe/semi-icons'
import { useRobotId } from '../../store/robot'
import { motionMove, motionSetPose, motionGetPose, motionHome, motionEStop, liftStatus } from '../../api/control'

interface Pose {
  x: number
  y: number
  theta: number
}

const holdBtnStyle: React.CSSProperties = {
  width: 64,
  height: 64,
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

export default function MotionControl() {
  const { selectedRid: rid } = useRobotId()
  const [pose, setPose] = useState<Pose>({ x: 0, y: 0, theta: 0 })
  const [curPose, setCurPose] = useState<any>(null)
  const [curLift, setCurLift] = useState<any>(null)
  const stopTimer = useRef<ReturnType<typeof setTimeout> | null>(null)

  // 切换机器人时自动获取升降杆状态
  useEffect(() => {
    if (!rid) { setCurLift(null); return }
    liftStatus(rid).then(({ data }) => {
      if (data.ok) setCurLift(data.data)
    }).catch(() => {})
  }, [rid])

  const setField = (k: keyof Pose, v: any) =>
    setPose((p) => ({ ...p, [k]: v == null ? 0 : Number(v) }))

  // 按住: 发送运动指令
  const holdMove = async (cmd: number) => {
    if (!rid) return
    if (stopTimer.current) clearTimeout(stopTimer.current)
    try { await motionMove(rid, cmd) } catch { /* */ }
  }

  // 松开: 发送停止指令(防抖)
  const stopMove = async () => {
    if (!rid) return
    if (stopTimer.current) clearTimeout(stopTimer.current)
    stopTimer.current = setTimeout(async () => {
      try { await motionMove(rid, 0) } catch { /* */ }
    }, 100)
  }

  const home = async () => {
    const { data } = await motionHome(rid!, true)
    Toast.success(data.msg || '已下发返航')
  }

  const estop = async () => {
    const { data } = await motionEStop(rid!, true)
    Toast.warning(data.msg || '急停已触发')
  }

  const setPoseFn = async () => {
    const { data } = await motionSetPose(rid!, pose)
    Toast.success(data.msg || '已下发')
  }

  const getPose = async () => {
    const { data } = await motionGetPose(rid!)
    if (data.ok) {
      setCurPose(data.data)
      if (data.data?.point) {
        setPose({
          x: data.data.point.x,
          y: data.data.point.y,
          theta: data.data.theta,
        })
      }
    }
    // 同时读取升降杆状态
    try {
      const { data: ld } = await liftStatus(rid!)
      if (ld.ok) setCurLift(ld.data)
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

  return (
    <div className="page-container">
      <div className="mb-12"><h2 style={{ margin: 0 }}>运动控制</h2></div>

      <Row gutter={[12, 12]} className="mt-12">
        {/* 方向控制 */}
        <Col xs={24} sm={12}>
          <Card className="card-shadow" bordered={false} title="方向控制 (按住移动, 松开停止)">
            <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 8, maxWidth: 240, margin: '0 auto', placeItems: 'center' }}>
              <div />
              <button className="pad-btn hold-btn" style={holdBtnStyle} {...btnProps(1)}>
                <IconArrowUp size="large" />
              </button>
              <div />
              <button className="pad-btn hold-btn" style={holdBtnStyle} {...btnProps(3)}>
                <IconArrowLeft size="large" />
              </button>
              <button
                className="pad-btn hold-btn stop-btn"
                style={{ ...holdBtnStyle, background: '#f56c6c' }}
                onMouseDown={stopMove}
                onTouchStart={(e) => { e.preventDefault(); stopMove() }}
                disabled={!rid}
              >
                <IconStop size="large" />
              </button>
              <button className="pad-btn hold-btn" style={holdBtnStyle} {...btnProps(4)}>
                <IconArrowRight size="large" />
              </button>
              <div />
              <button className="pad-btn hold-btn" style={holdBtnStyle} {...btnProps(2)}>
                <IconArrowDown size="large" />
              </button>
              <div />
            </div>
            <div className="mt-12 text-muted" style={{ fontSize: 12, textAlign: 'center' }}>
              按住方向键持续移动, 松开自动停止
            </div>
          </Card>
        </Col>

        {/* 快捷操作 */}
        <Col xs={24} sm={12}>
          <Card className="card-shadow" bordered={false} title="快捷操作">
            <div className="flex gap-8" style={{ flexWrap: 'wrap' }}>
              <Button theme="solid" type="warning" disabled={!rid} onClick={home}>返航复位 (cmd=33)</Button>
              <Popconfirm title="确认急停?" onConfirm={estop}>
                <Button theme="solid" type="danger" disabled={!rid}>急停 (cmd=51)</Button>
              </Popconfirm>
            </div>
            <Divider align="left">设定位姿 (cmd=31)</Divider>
            <div style={{ display: 'grid', gridTemplateColumns: '60px 1fr', rowGap: 8, alignItems: 'center' }}>
              <span>X</span>
              <InputNumber value={pose.x} step={0.1} onChange={(v) => setField('x', v)} />
              <span>Y</span>
              <InputNumber value={pose.y} step={0.1} onChange={(v) => setField('y', v)} />
              <span>角度</span>
              <InputNumber value={pose.theta} step={1} onChange={(v) => setField('theta', v)} />
              <div />
              <div className="flex gap-8">
                <Button theme="solid" type="primary" disabled={!rid} onClick={setPoseFn}>前往此位姿</Button>
                <Button disabled={!rid} onClick={getPose}>读取当前位姿</Button>
              </div>
            </div>
            {curPose && (
              <div className="text-muted text-mono mt-12" style={{ fontSize: 12 }}>
                当前: x={curPose.point?.x?.toFixed(2)} y={curPose.point?.y?.toFixed(2)} θ={curPose.theta?.toFixed(1)}°
                {curLift?.height != null && <> | 升降: {Number(curLift.height).toFixed(2)}m</>}
              </div>
            )}
          </Card>
        </Col>
      </Row>

      <style>{`
        .hold-btn:active { transform: scale(0.9); background: #337ecc; }
        .hold-btn:disabled { opacity: .4; cursor: not-allowed; }
        .stop-btn:active { background: #dd6161; }
      `}</style>
    </div>
  )
}
