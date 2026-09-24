import { useState, useEffect } from 'react'
import { useNavigate } from 'react-router-dom'
import { Card, Input, Button, Form, Toast } from '@douyinfe/semi-ui'
import { useUser } from '../store/user'
import http from '../api/http'

export default function Login() {
  const navigate = useNavigate()
  const user = useUser()
  const [form, setForm] = useState({ username: 'admin', password: 'admin' })
  const [loading, setLoading] = useState(false)
  const [version, setVersion] = useState('')

  useEffect(() => {
    http.get('/api/health').then(({ data }) => setVersion(data.version || '')).catch(() => {})
  }, [])

  const onLogin = async () => {
    setLoading(true)
    try {
      await user.login(form.username, form.password)
      Toast.success('登录成功')
      navigate('/dashboard')
    } catch {
      /* 拦截器已提示 */
    } finally {
      setLoading(false)
    }
  }

  return (
    <div style={{
      minHeight: '100vh', display: 'flex', alignItems: 'center', justifyContent: 'center',
      background: 'linear-gradient(135deg, #1e3c72 0%, #2a5298 100%)', padding: 16,
    }}>
      <Card className="card-shadow" style={{ width: '100%', maxWidth: 360, padding: '12px 20px' }}>
        <div style={{ fontSize: 24, fontWeight: 700, textAlign: 'center', color: '#303133' }}>Straitbot FMS</div>
        <div style={{ color: '#909399', textAlign: 'center', marginBottom: 20, fontSize: 13 }}>机器人运维管理平台</div>
        <Form labelPosition="inset" onSubmit={onLogin}>
          <Form.Input field="username" label="用户名" placeholder="admin / operator"
            initValue="admin" onChange={(v) => setForm((f) => ({ ...f, username: v }))} />
          <Form.Input field="password" label="密码" type="password" mode="password"
            initValue="admin" onChange={(v) => setForm((f) => ({ ...f, password: v }))}
            onEnterPress={onLogin} />
          <Button theme="solid" type="primary" loading={loading} onClick={onLogin} block>登录</Button>
        </Form>
        <div className="text-muted mt-12" style={{ textAlign: 'center', fontSize: 12 }}>
          默认账号: admin/admin (工程师) · operator/operator (运维)
        </div>
        {version && (
          <div className="text-muted" style={{ textAlign: 'center', fontSize: 11, marginTop: 8, opacity: 0.6 }}>
            Straitbot FMS v{version}
          </div>
        )}
      </Card>
    </div>
  )
}
