import React, { useState } from 'react'
import { Tabs } from '@douyinfe/semi-ui'
import AiChat from './AiChat'
import AiSettings from './AiSettings'

export default function AiCenter() {
  const [tab, setTab] = useState('chat')

  return (
    <div className="page-container">
      <div className="mb-12"><h2 style={{ margin: 0 }}>AI 中心</h2></div>

      <Tabs type="line" activeKey={tab} onChange={(k) => setTab(k)} className="card-shadow">
        <Tabs.TabPane tab="💬 AI 对话" itemKey="chat">
          {tab === 'chat' && <AiChat />}
        </Tabs.TabPane>
        <Tabs.TabPane tab="⚙️ AI 配置" itemKey="config">
          {tab === 'config' && <AiSettings />}
        </Tabs.TabPane>
      </Tabs>
    </div>
  )
}
