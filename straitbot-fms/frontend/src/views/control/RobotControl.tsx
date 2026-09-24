import { useState } from 'react'
import { Tabs, Button, Toast, Space } from '@douyinfe/semi-ui'
import { IconStop } from '@douyinfe/semi-icons'
import MotionControl from './MotionControl'
import PTZControl from './PTZControl'
import VideoStream from './VideoStream'
import { useRobotId } from '../../store/robot'
import { cancelInspection } from '../../api/control'

export default function RobotControl() {
  const [tab, setTab] = useState('motion')
  const { selectedRid: rid } = useRobotId()

  const handleCancelInspection = async () => {
    if (!rid) return
    try {
      await cancelInspection(rid)
      Toast.success('取消巡检信号已发送')
    } catch (e: any) {
      Toast.error(e?.message || '取消巡检失败')
    }
  }

  return (
    <div>
      <Space style={{ marginBottom: 16 }}>
        <Button
          icon={<IconStop />}
          type="danger"
          onClick={handleCancelInspection}
        >
          取消巡检
        </Button>
      </Space>
      <Tabs type="line" activeKey={tab} onChange={(k) => setTab(k)}>
        <Tabs.TabPane tab="运动控制" itemKey="motion">
          {tab === 'motion' && <MotionControl />}
        </Tabs.TabPane>
        <Tabs.TabPane tab="云台 / 拍照 / 升降杆" itemKey="ptz">
          {tab === 'ptz' && <PTZControl />}
        </Tabs.TabPane>
        <Tabs.TabPane tab="视频流 / 抓拍" itemKey="video">
          {tab === 'video' && <VideoStream />}
        </Tabs.TabPane>
      </Tabs>
    </div>
  )
}
