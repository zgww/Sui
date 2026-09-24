import { useRef, useState, useEffect, useImperativeHandle, forwardRef } from 'react'
import { RadioGroup, Radio, ButtonGroup, Button, Toast } from '@douyinfe/semi-ui'
import { IconPlay, IconStop, IconRefresh, IconLoading } from '@douyinfe/semi-icons'
import { getVideoConfig, webrtcSignalUrl, postWebrtcSignal } from '../api/video'

export interface WebRTCPlayerRef {
  snapshot: () => string | null
  start: () => void
  stop: () => void
  restart: () => void
  state: string
  channel: string
}

interface Props {
  rid: number | null
  autoplay?: boolean
  signalUrlOverride?: string | null
}

type PlayerState = 'idle' | 'connecting' | 'playing' | 'no-config' | 'error'

const WebRTCPlayer = forwardRef<WebRTCPlayerRef, Props>(({ rid, autoplay = true, signalUrlOverride = null }, ref) => {
  const videoRef = useRef<HTMLVideoElement>(null)
  const pcRef = useRef<RTCPeerConnection | null>(null)
  const restartTimer = useRef<ReturnType<typeof setTimeout> | null>(null)
  const [channel, setChannel] = useState<'visible' | 'thermal'>('visible')
  const [state, setState] = useState<PlayerState>('idle')
  const [errMsg, setErrMsg] = useState('')

  const stop = () => {
    if (restartTimer.current) clearTimeout(restartTimer.current)
    if (pcRef.current) {
      try { pcRef.current.getSenders().forEach((s) => s.track && s.track.stop()) } catch { /* */ }
      try { pcRef.current.close() } catch { /* */ }
      pcRef.current = null
    }
    if (videoRef.current) {
      try { videoRef.current.srcObject = null } catch { /* */ }
    }
    setState((s) => (s === 'no-config' || s === 'error' ? s : 'idle'))
  }

  const fail = (e: any) => {
    setState('error')
    setErrMsg(e?.message || String(e))
  }

  const setupPeer = async () => {
    pcRef.current = new RTCPeerConnection({ iceServers: [] })
    pcRef.current.addTransceiver('video', { direction: 'recvonly' })
    pcRef.current.addTransceiver('audio', { direction: 'recvonly' })
    pcRef.current.ontrack = (ev) => {
      const v = videoRef.current
      if (v && ev.streams && ev.streams[0]) {
        v.srcObject = ev.streams[0]
        v.play().catch(() => {})
        setState('playing')
      }
    }
    pcRef.current.onconnectionstatechange = () => {
      const s = pcRef.current?.connectionState
      if (s === 'failed' || s === 'disconnected') {
        if (state === 'playing') {
          scheduleReconnect()
        } else {
          fail(new Error('连接断开 (' + s + ')'))
        }
      }
    }
  }

  const start = async () => {
    if (!rid) return
    stop()
    setState('connecting')
    setErrMsg('')
    try {
      if (signalUrlOverride) {
        // 使用自定义信令 URL, 跳过后端配置检查
        await setupPeer()
        const offer = await pcRef.current!.createOffer({ offerToReceiveVideo: true, offerToReceiveAudio: true })
        await pcRef.current!.setLocalDescription(offer)
        const token = localStorage.getItem('fms_token')
        const answer = await postWebrtcSignal(signalUrlOverride, offer.sdp!, token)
        await pcRef.current!.setRemoteDescription(new RTCSessionDescription({ type: 'answer', sdp: answer }))
        return
      }
      const { data } = await getVideoConfig(rid)
      if (!data.configured) {
        setState('no-config')
        setErrMsg('未配置 ZLM 视频服务器地址')
        return
      }
      await setupPeer()
      const offer = await pcRef.current!.createOffer({ offerToReceiveVideo: true, offerToReceiveAudio: true })
      await pcRef.current!.setLocalDescription(offer)
      const url = webrtcSignalUrl(rid, channel)
      const token = localStorage.getItem('fms_token')
      const answer = await postWebrtcSignal(url, offer.sdp!, token)
      await pcRef.current!.setRemoteDescription(new RTCSessionDescription({ type: 'answer', sdp: answer }))
    } catch (e) {
      fail(e)
    }
  }

  const scheduleReconnect = () => {
    if (restartTimer.current) clearTimeout(restartTimer.current)
    restartTimer.current = setTimeout(() => { if (rid) start() }, 2000)
  }

  const snapshot = (): string | null => {
    const v = videoRef.current
    if (!v || state !== 'playing') return null
    const canvas = document.createElement('canvas')
    canvas.width = v.videoWidth || 640
    canvas.height = v.videoHeight || 360
    canvas.getContext('2d')!.drawImage(v, 0, 0, canvas.width, canvas.height)
    return canvas.toDataURL('image/jpeg', 0.85)
  }

  useImperativeHandle(ref, () => ({ snapshot, start, stop, restart: () => { stop(); start() }, state, channel }))

  useEffect(() => {
    stop()
    if (rid && autoplay) start()
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [rid, signalUrlOverride])

  useEffect(() => () => stop(), [])

  return (
    <div className="webrtc-player" style={{ width: '100%' }}>
      <div className={`video-wrap ${channel === 'thermal' ? 'is-thermal' : ''}`}>
        <video ref={videoRef} autoPlay playsInline muted style={{ width: '100%', height: '100%', objectFit: 'contain', display: 'block' }} />
        {state !== 'playing' && (
          <div className="overlay">
            {state === 'connecting' && <IconLoading spin size="large" />}
            <span style={{ marginLeft: 8 }}>
              {state === 'connecting' ? '连接中...' :
               state === 'no-config' ? '未配置视频流' :
               state === 'error' ? (errMsg || '连接失败') : '点击播放'}
            </span>
          </div>
        )}
        <div className="toolbar">
          <RadioGroup
            type="button"
            value={channel}
            onChange={(e) => { setChannel(e.target.value); if (state === 'playing' || state === 'connecting') start() }}
          >
            <Radio value="visible">可见光</Radio>
            <Radio value="thermal">红外</Radio>
          </RadioGroup>
          <ButtonGroup size="small">
            <Button icon={<IconPlay />} disabled={!rid || state === 'connecting'} onClick={start}>播放</Button>
            <Button icon={<IconRefresh />} disabled={!rid} onClick={() => { stop(); start() }}>重连</Button>
            <Button icon={<IconStop />} onClick={stop}>停止</Button>
          </ButtonGroup>
        </div>
        {state === 'playing' && (
          <div className={`badge ${channel === 'thermal' ? 'badge-thermal' : 'badge-vis'}`}>
            {channel === 'thermal' ? '红外' : '可见光'} · LIVE
          </div>
        )}
      </div>
      <style>{`
        .video-wrap { position: relative; width: 100%; background: #000; border-radius: 6px; overflow: hidden; aspect-ratio: 16 / 9; }
        .overlay { position: absolute; inset: 0; display: flex; align-items: center; justify-content: center; color: #909399; background: rgba(0,0,0,.6); font-size: 14px; }
        .toolbar { position: absolute; top: 8px; left: 8px; right: 8px; display: flex; align-items: center; justify-content: space-between; opacity: 0; transition: opacity .2s; z-index: 2; }
        .video-wrap:hover .toolbar { opacity: 1; }
        .badge { position: absolute; bottom: 8px; right: 8px; padding: 2px 8px; border-radius: 3px; font-size: 12px; color: #fff; z-index: 2; }
        .badge-vis { background: rgba(64,158,255,.85); }
        .badge-thermal { background: rgba(245,108,108,.85); }
      `}</style>
    </div>
  )
})

export default WebRTCPlayer
