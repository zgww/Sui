import { useMemo } from 'react'
import { Button } from '@douyinfe/semi-ui'
import { IconChevronLeft, IconChevronRight } from '@douyinfe/semi-icons'
import * as SemiIcons from '@douyinfe/semi-icons'
import { menuRoutes } from '../router'
import { useUser } from '../store/user'
import './sidebar.css'

interface Props { active: string; onSelect: (path: string) => void; collapsed: boolean; onToggle: (v: boolean) => void }
const groups = [
  { title: '运行总览', paths: ['/dashboard', '/robots', '/alerts', '/logs'] },
  { title: '巡检业务 · 下沉', paths: ['/sink/point-archive', '/sink/waypoint-binding', '/sink/inspection-plan', '/sink/inspection-log', '/sink/alarm-template'] },
  { title: '机器人配置', paths: ['/waypoints', '/waypoint-tree', '/waypoint-prefab', '/inspection-plan-prefab', '/detect-prefab', '/inspection/tasks', '/inspection/log', '/ota', '/robot-config'] },
  { title: '工程工具', paths: ['/cmd-debug', '/terminal', '/ai-center', '/prefab', '/simulation', '/robot-control', '/fsm', '/thing-model', '/settings'] },
]
export default function Sidebar({ active, onSelect, collapsed, onToggle }: Props) {
  const user = useUser()
  const routes = useMemo(() => menuRoutes.filter(r => !r.hidden && (!r.roles || r.roles.includes(user.role))), [user.role])
  return <aside className={`fms-sidebar ${collapsed ? 'is-collapsed' : ''}`}>
    <div className="fms-sidebar-brand">{!collapsed && <div><strong>Straitbot <b>FMS</b></strong><small>机器人运维平台</small></div>}
      <Button aria-label={collapsed ? '展开导航菜单' : '收起导航菜单'} title={collapsed ? '展开菜单' : '收起菜单'} icon={collapsed ? <IconChevronRight /> : <IconChevronLeft />} theme="borderless" onClick={() => onToggle(!collapsed)} size="small" /></div>
    <nav className="fms-sidebar-nav" aria-label="主导航">{groups.map(group => {
      const entries = group.paths.map(path => routes.find(r => r.path === path)).filter(Boolean)
      if (!entries.length) return null
      return <section key={group.title} aria-label={group.title}><div className="fms-sidebar-group">{!collapsed && group.title}</div>{entries.map(route => {
        const r = route!; const Icon = (SemiIcons as any)[r.icon]; const selected = active === r.path || active.startsWith(r.path + '/')
        return <button key={r.path} type="button" className={`fms-nav-item ${selected ? 'is-active' : ''}`} aria-label={r.title} aria-current={selected ? 'page' : undefined} title={collapsed ? r.title : undefined} onClick={() => onSelect(r.path)}>
          {Icon && <Icon />}<span>{r.title.replace('（下沉）', '')}</span>
        </button>
      })}</section>
    })}</nav>
    {!collapsed && <div className="fms-sidebar-footer"><span /> FMS 本地管理</div>}
  </aside>
}
