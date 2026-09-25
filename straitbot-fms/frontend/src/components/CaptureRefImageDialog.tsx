import { useState, useRef } from 'react'
import { Modal, Button, Toast, Spin, Tag } from '@douyinfe/semi-ui'
import { IconCamera } from '@douyinfe/semi-icons'
import WebRTCPlayer, { WebRTCPlayerRef } from './WebRTCPlayer'
import { captureRefImage } from '../api/waypointTree'
import { motionGetPose, ptzGetPose, liftStatus } from '../api/control'

interface Props {
  rid: number | null
  visible: boolean
  onClose: () => void
  onCaptured: (data: {
    refImagePath: string
    pose: { theta: number; point: { x: number; y: number; z: number } }
    ptz: { pan: number; tilt: number; zoom: number; focus: number; focal_len: number }
    liftHeight: number
  }) => void
}

export default function CaptureRefImageDialog({ rid, visible, onClose, onCaptured }: Props) {
  const playerRef = useRef<WebRTCPlayerRef>(null)
  const [capturing, setCapturing] = useState(false)
  const [preview, setPreview] = useState<string | null>(null)

  const doCapture = async () => {
    if (!rid) return
    if (!playerRef.current) return
    const snap = playerRef.current.snapshot()
    if (!snap) {
      Toast.warning('视频流未就绪, 请等待画面出现后再抓拍')
      return
    }
    setPreview(snap)
    setCapturing(true)
    try {
      // 1. 上传图片
      const { data: cap } = await captureRefImage(rid, snap)
      const refImagePath = cap.path

      // 2. 并行获取机器人位姿 / 云台位姿 / 升降杆高度
      const [poseResp, ptzResp, liftResp] = await Promise.allSettled([
        motionGetPose(rid),
        ptzGetPose(rid),
        liftStatus(rid),
      ])

      // 解析位姿
      let pose: { theta: number; point: { x: number; y: number; z: number } } = {
        theta: 0, point: { x: 0, y: 0, z: 0 },
      }
      if (poseResp.status === 'fulfilled') {
        const d = poseResp.value.data?.data || poseResp.value.data || {}
        const px = Number(d.x ?? d.point?.x ?? 0)
        const py = Number(d.y ?? d.point?.y ?? 0)
        const pz = Number(d.z ?? d.point?.z ?? 0)
        const th = Number(d.theta ?? 0)
        pose = { theta: th, point: { x: px, y: py, z: pz } }
      }

      // 解析云台
      let ptz: { pan: number; tilt: number; zoom: number; focus: number; focal_len: number } = {
        pan: 0, tilt: 0, zoom: 0, focus: 0, focal_len: 0,
      }
      if (ptzResp.status === 'fulfilled') {
        const d = ptzResp.value.data?.data || ptzResp.value.data || {}
        ptz = {
          pan: Number(d.pan ?? 0),
          tilt: Number(d.tilt ?? 0),
          zoom: Number(d.zoom ?? 0),
          focus: Number(d.focus ?? 0),
          focal_len: Number(d.focal_len ?? 0),
        }
      }

      // 解析升降杆
      let liftHeight = 0
      if (liftResp.status === 'fulfilled') {
        const d = liftResp.value.data?.data || liftResp.value.data || {}
        liftHeight = Number(d.height ?? d.lift_height ?? d.position ?? 0)
      }

      onCaptured({ refImagePath, pose, ptz, liftHeight })
      Toast.success('抓拍完成, 已获取位姿/云台/升降杆数据')
      onClose()
      setPreview(null)
    } catch {
      /* http 拦截器已提示 */
    } finally {
      setCapturing(false)
    }
  }

  return (
    <Modal
      visible={visible}
      title="ORB 配准参考图抓拍"
      onCancel={onClose}
      footer={null}
      width={760}
    >
      {!rid ? (
        <div className="text-muted" style={{ padding: '40px 0', textAlign: 'center' }}>
          请先选择机器人
        </div>
      ) : (
        <>
          <div style={{ marginBottom: 8, display: 'flex', alignItems: 'center', gap: 8 }}>
            <Tag color="blue" size="small">可见光</Tag>
            <span className="text-muted" style={{ fontSize: 13 }}>
              等待画面出现后点击「抓拍」, 将自动获取当前机器人位姿、云台位姿和升降杆高度
            </span>
          </div>

          <WebRTCPlayer ref={playerRef} rid={rid} autoplay />

          {preview && (
            <div style={{ marginTop: 12 }}>
              <div className="text-muted" style={{ fontSize: 12, marginBottom: 4 }}>抓拍预览:</div>
              <img
                src={preview}
                alt="capture preview"
                style={{ maxWidth: '100%', maxHeight: 200, borderRadius: 6, border: '1px solid #e4e7ed' }}
              />
            </div>
          )}

          <div style={{ marginTop: 12, display: 'flex', justifyContent: 'flex-end', gap: 8 }}>
            <Button onClick={onClose}>取消</Button>
            <Button
              theme="solid"
              type="primary"
              icon={<IconCamera />}
              loading={capturing}
              onClick={doCapture}
            >
              {capturing ? '抓拍中...' : '抓拍'}
            </Button>
          </div>

          {capturing && (
            <div style={{ textAlign: 'center', padding: 12 }}>
              <Spin /> <span className="text-muted" style={{ marginLeft: 8 }}>正在上传图片并获取机器人数据...</span>
            </div>
          )}
        </>
      )}
    </Modal>
  )
}
