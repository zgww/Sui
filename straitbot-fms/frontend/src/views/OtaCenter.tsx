import { useState } from 'react'
import { Tabs } from '@douyinfe/semi-ui'
import OtaTasks from './OtaTasks'
import Packages from './Packages'

export default function OtaCenter() {
  const [otaTab, setOtaTab] = useState('tasks')

  return (
    <div className="page-container">
      <div className="mb-12">
        <h2 style={{ margin: 0 }}>OTA 中心</h2>
      </div>
      <Tabs type="line" activeKey={otaTab} onChange={(k) => setOtaTab(k)}>
        <Tabs.TabPane tab="升级任务" itemKey="tasks">
          {otaTab === 'tasks' && <OtaTasks />}
        </Tabs.TabPane>
        <Tabs.TabPane tab="安装包管理" itemKey="packages">
          {otaTab === 'packages' && <Packages />}
        </Tabs.TabPane>
      </Tabs>
    </div>
  )
}
