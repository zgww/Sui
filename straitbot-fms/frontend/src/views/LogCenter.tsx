import React, { useState } from 'react'
import { Tabs } from '@douyinfe/semi-ui'
import { useUser } from '../store/user'
import LogsView from './LogsView'
import LogFetch from './LogFetch'
import LogUpload from './LogUpload'
import BackendLogViewer from './BackendLogViewer'

export default function LogCenter() {
  const user = useUser()
  const [activeTab, setActiveTab] = useState('view')

  return (
    <div className="page-container">
      <div className="mb-12"><h2 style={{ margin: 0 }}>日志中心</h2></div>

      <Tabs type="line" activeKey={activeTab} onChange={(k) => setActiveTab(k)} className="card-shadow">
        {/* 日志查看 + AI 分析（所有角色） */}
        <Tabs.TabPane tab="📋 日志查看 / AI 分析" itemKey="view">
          {activeTab === 'view' && <LogsView />}
        </Tabs.TabPane>

        {/* 在线拉日志（工程师） */}
        {user.isEngineer && (
          <Tabs.TabPane tab="📥 在线拉日志" itemKey="fetch">
            {activeTab === 'fetch' && <LogFetch />}
          </Tabs.TabPane>
        )}

        {/* 日志上传管理（工程师） */}
        {user.isEngineer && (
          <Tabs.TabPane tab="📤 日志上传" itemKey="upload">
            {activeTab === 'upload' && <LogUpload />}
          </Tabs.TabPane>
        )}

        {/* 后端日志（工程师） */}
        {user.isEngineer && (
          <Tabs.TabPane tab="🖥 后端日志" itemKey="backend">
            {activeTab === 'backend' && <BackendLogViewer />}
          </Tabs.TabPane>
        )}
      </Tabs>
    </div>
  )
}
