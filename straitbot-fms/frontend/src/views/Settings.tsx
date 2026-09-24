import { useState, useEffect } from 'react'
import { useNavigate } from 'react-router-dom'
import { Card, Button, Tag, Banner, Descriptions } from '@douyinfe/semi-ui'
import { useUser } from '../store/user'
import { fetchSettings } from '../api/robots'
import type { SettingsInfo } from '../types'

export default function Settings() {
  const navigate = useNavigate()
  const user = useUser()
  const [info, setInfo] = useState<Partial<SettingsInfo>>({})

  useEffect(() => {
    fetchSettings().then(({ data }) => setInfo(data)).catch(() => {})
  }, [])

  const logout = () => {
    user.logout()
    navigate('/login')
  }

  return (
    <div className="page-container">
      <div className="mb-12"><h2 style={{ margin: 0 }}>系统设置</h2></div>

      <Card className="card-shadow mb-12" bordered={false} title="平台信息">
        <Descriptions data={[
          { key: '应用名称', value: info.app_name || '-' },
          { key: '版本', value: <Tag size="small">v{info.version || 'unknown'}</Tag> },
          { key: '状态轮询间隔', value: `${info.poll_status_interval_sec ?? '-'} 秒` },
          { key: '元数据轮询间隔', value: `${info.poll_meta_interval_sec ?? '-'} 秒` },
          { key: '默认日志保留', value: `${info.default_log_retention_days ?? '-'} 天` },
        ]} row />
      </Card>

      <Card className="card-shadow" bordered={false} title="当前账号">
        <Descriptions data={[
          { key: '用户名', value: user.username },
          { key: '角色', value: <Tag color={user.isEngineer ? 'green' : 'orange'} size="small">{user.isEngineer ? '工程师(engineer)' : '运维(operator)'}</Tag> },
        ]} row />
        <div style={{ marginTop: 12 }}>
          <Button type="danger" theme="solid" onClick={logout}>退出登录</Button>
        </div>
      </Card>

      <Banner
        className="mt-12"
        type="info"
        fullMode={false}
        closeIcon={null}
        title="提示"
        description={
          <div>
            <div>· 轮询间隔、日志保留等参数在 .env 文件中配置, 修改后需重启容器生效</div>
            <div>· 单个机器人的轮询开关和保留天数在「机器人列表 - 编辑」中独立设置</div>
            <div>· 完整数据保存在 backend/data/ 目录, 整目录打包即可移植</div>
            <div>· 想用 AI 分析日志? 去 <b>「AI 分析设置」</b> 配置 API Key(支持 DeepSeek/智谱/通义/OpenAI 等)</div>
          </div>
        }
      />
    </div>
  )
}
