import { useState, useRef, useEffect } from 'react'
import { Card, Input, Button, Collapse, Descriptions, Toast } from '@douyinfe/semi-ui'
import { IconSetting } from '@douyinfe/semi-icons'
import WebRTCPlayer from './WebRTCPlayer'
import type { WebRTCPlayerRef } from './WebRTCPlayer'
import FloatPanel from './FloatPanel'
import { getVideoConfig, webrtcSignalUrl } from '../api/video'

interface Props {
  visible: boolean
  rid: number | null
  robotName?: string
  onClose: () => void
}

export default function VideoStreamDialog({ visible, rid, robotName, onClose }: Props) {
  const [showSettings, setShowSettings] = useState(false)
  const [videoConfig, setVideoConfig] = useState<any>(null)
  const [customUrl, setCustomUrl] = useState('')
  const [urlOverride, setUrlOverride] = useState<string | null>(null)
  const playerRef = useRef<WebRTCPlayerRef>(null)

  // 加载视频配置
  useEffect(() => {
    if (!rid || !showSettings) return
    getVideoConfig(rid).then(({ data }) => {
      setVideoConfig(data)
    }).catch(() => { /* */ })
  }, [rid, showSettings])

  const defaultUrl = rid ? webrtcSignalUrl(rid, 'visible') : ''

  const applyOverride = () => {
    const trimmed = customUrl.trim()
    if (trimmed) {
      setUrlOverride(trimmed)
      Toast.success('已应用自定义信令 URL')
    } else {
      setUrlOverride(null)
      Toast.info('已恢复默认信令 URL')
    }
    // 重启播放器
    setTimeout(() => playerRef.current?.restart(), 100)
  }

  const resetOverride = () => {
    setCustomUrl('')
    setUrlOverride(null)
    setTimeout(() => playerRef.current?.restart(), 100)
  }

  const headerExtra = (
    <button
      className="header-btn"
      title="视频流设置"
      onClick={() => setShowSettings((v) => !v)}
      style={{
        color: showSettings ? '#409eff' : undefined,
        background: showSettings ? '#ecf5ff' : undefined,
      }}
    >
      <IconSetting />
    </button>
  )

  return (
    <FloatPanel
      visible={visible}
      title={`视频流${robotName ? ' - ' + robotName : ''}`}
      onClose={onClose}
      width={560}
      headerExtra={headerExtra}
    >
      {rid ? (
        <>
          {showSettings && (
            <div style={{ marginBottom: 12 }}>
              <Collapse keepDOM={false}>
                <Collapse.Panel
                  header="视频流设置"
                  itemKey="settings"
                  style={{ background: '#f9fafc' }}
                >
                  <Descriptions
                    size="small"
                    row
                    data={[
                      { key: '视频服务器', value: videoConfig?.video_server || '-' },
                      { key: '协议', value: videoConfig?.protocol || '-' },
                      { key: '可见光流', value: videoConfig?.visible?.stream || '-' },
                      { key: '红外流', value: videoConfig?.thermal?.stream || '-' },
                    ]}
                    style={{ marginBottom: 12 }}
                  />
                  <div style={{ fontSize: 12, color: '#909399', marginBottom: 4 }}>
                    默认信令 URL: <code style={{ wordBreak: 'break-all' }}>{defaultUrl}</code>
                  </div>
                  <div style={{ display: 'flex', gap: 8, alignItems: 'flex-end' }}>
                    <div style={{ flex: 1 }}>
                      <div style={{ fontSize: 12, color: '#606266', marginBottom: 4 }}>自定义信令 URL (临时)</div>
                      <Input
                        size="small"
                        value={customUrl}
                        onChange={setCustomUrl}
                        placeholder="留空则使用默认 URL"
                      />
                    </div>
                    <Button size="small" theme="solid" type="primary" onClick={applyOverride}>应用</Button>
                    <Button size="small" onClick={resetOverride}>重置</Button>
                  </div>
                  {urlOverride && (
                    <div style={{ fontSize: 12, color: '#e6a23c', marginTop: 6 }}>
                      当前使用自定义 URL: <code style={{ wordBreak: 'break-all' }}>{urlOverride}</code>
                    </div>
                  )}
                </Collapse.Panel>
              </Collapse>
            </div>
          )}
          <Card bordered={false} bodyStyle={{ padding: 0 }}>
            <WebRTCPlayer ref={playerRef} rid={rid} autoplay signalUrlOverride={urlOverride} />
          </Card>
        </>
      ) : (
        <div className="text-muted" style={{ padding: '40px 0', textAlign: 'center' }}>
          请先选择一个机器人
        </div>
      )}
    </FloatPanel>
  )
}
