import { useState, useEffect, useCallback } from 'react'
import { Outlet, useLocation, useNavigate } from 'react-router-dom'
import { Layout, Tag, Dropdown, Button } from '@douyinfe/semi-ui'
import { IconChevronDown, IconMenu } from '@douyinfe/semi-icons'
import { useUser } from '../store/user'
import { useRobotId } from '../store/robot'
import Sidebar from '../components/Sidebar'
import '../views/sink/workflow.css'
import RobotSwitcher from '../components/RobotSwitcher'
import AlarmBell from '../components/AlarmBell'
import { listRobots } from '../api/robots'
import type { Robot } from '../types'

const { Sider, Header, Content } = Layout

export default function MainLayout() {
  const location = useLocation()
  const navigate = useNavigate()
  const user = useUser()
  const { selectedRid, setSelectedRid } = useRobotId()
  const [width, setWidth] = useState(window.innerWidth)
  const [drawerOpen, setDrawerOpen] = useState(false)
  const [robotsLoading, setRobotsLoading] = useState(false)
  const [robotsError, setRobotsError] = useState(false)
  const [robots, setRobots] = useState<Robot[]>([])
  const [sidebarCollapsed, setSidebarCollapsed] = useState(false)

  const isMobile = width < 768
  const noRobotPages = ['/dashboard', '/robots', '/logs', '/ota', '/settings', '/ai-center', '/thing-model',
    '/prefab', '/simulation', '/fsm']

  useEffect(() => {
    const onResize = () => setWidth(window.innerWidth)
    window.addEventListener('resize', onResize)
    return () => window.removeEventListener('resize', onResize)
  }, [])

  useEffect(() => { const close = (e: KeyboardEvent) => { if (e.key === 'Escape') setDrawerOpen(false) }; window.addEventListener('keydown', close); return () => window.removeEventListener('keydown', close) }, [])

  const loadRobots = useCallback(async () => {
    setRobotsLoading(true)
    setRobotsError(false)
    try {
      const { data } = await listRobots()
      setRobots(data)
    } catch { setRobotsError(true) }
    finally { setRobotsLoading(false) }
  }, [])

  useEffect(() => { loadRobots() }, [loadRobots])

  const go = (path: string) => navigate(path)

  const handleMenuCmd = (key: string) => {
    if (key === 'logout') {
      user.logout()
      navigate('/login')
    }
  }

  const showRobotSelect = !noRobotPages.some(p => location.pathname === p || location.pathname.startsWith(p + '/'))

  return (
    <Layout style={{ height: '100vh' }}>
      {!isMobile && (
        <Sider style={{ backgroundColor: '#14283e', width: sidebarCollapsed ? 64 : 240, flexShrink: 0 }}>
          <Sidebar active={location.pathname} onSelect={go} collapsed={sidebarCollapsed} onToggle={setSidebarCollapsed} />
        </Sider>
      )}

      <Layout style={{ minWidth: 0 }}>
        <Header className="fms-header">
          <div className="fms-header-main">
            {isMobile && (
              <Button aria-label="打开导航菜单" icon={<IconMenu />} theme="borderless" onClick={() => setDrawerOpen(true)} />
            )}
            <span className="fms-header-brand">Straitbot FMS</span>

            {showRobotSelect && (
              <RobotSwitcher robots={robots} value={selectedRid} loading={robotsLoading} error={robotsError} onChange={setSelectedRid} onRefresh={loadRobots} />
            )}

          </div>
          <div className="fms-header-user">
            <AlarmBell />
            <Tag size="small" color={user.isEngineer ? 'green' : 'orange'}>{user.isEngineer ? '工程师' : '运维'}</Tag>
            <Dropdown
              position="bottomRight"
              render={
                <Dropdown.Menu>
                  <Dropdown.Item onClick={() => handleMenuCmd('logout')}>退出登录</Dropdown.Item>
                </Dropdown.Menu>
              }
            >
              <button type="button" className="fms-header-account" aria-label="账户菜单">
                {user.username} <IconChevronDown />
              </button>
            </Dropdown>
          </div>
        </Header>

        <Content style={{ background: '#f0f2f5', overflow: 'auto' }}>
          <Outlet />
        </Content>
      </Layout>

      {/* 移动端抽屉侧栏 */}
      {isMobile && drawerOpen && (
        <div
          style={{
            position: 'fixed', inset: 0, zIndex: 1000, background: 'rgba(0,0,0,.4)',
          }}
          onClick={() => setDrawerOpen(false)}
        >
          <div
            style={{ width: 260, maxWidth: '85vw', height: '100%', background: '#14283e' }}
            onClick={(e) => e.stopPropagation()}
          >
            <Sidebar
              active={location.pathname}
              onSelect={(p) => { setDrawerOpen(false); navigate(p) }}
              collapsed={false}
              onToggle={() => setDrawerOpen(false)}
            />
          </div>
        </div>
      )}


    </Layout>
  )
}
