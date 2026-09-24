import React, { Suspense } from 'react'
import { createBrowserRouter, Navigate, useLocation } from 'react-router-dom'
import { Spin } from '@douyinfe/semi-ui'
import { useUser } from '../store/user'
import MainLayout from '../layout/MainLayout'

// 懒加载视图
const Login = React.lazy(() => import('../views/Login'))
const Dashboard = React.lazy(() => import('../views/Dashboard'))
const RobotList = React.lazy(() => import('../views/RobotList'))
const RobotDetail = React.lazy(() => import('../views/RobotDetail'))
const Alerts = React.lazy(() => import('../views/Alerts'))
const Alarms = React.lazy(() => import('../views/Alarms'))
const LogCenter = React.lazy(() => import('../views/LogCenter'))
const InspectionTasks = React.lazy(() => import('../views/business/InspectionTasks'))
const InspectionLog = React.lazy(() => import('../views/business/InspectionLog'))
const InspectionLogDetail = React.lazy(() => import('../views/business/InspectionLogDetail'))
const WaypointManager = React.lazy(() => import('../views/waypoint/WaypointManager'))
const WaypointTreeManager = React.lazy(() => import('../views/waypoint/WaypointTreeManager'))
const WaypointTreePrefab = React.lazy(() => import('../views/WaypointTreePrefab'))
const InspectionPlanPrefab = React.lazy(() => import('../views/InspectionPlanPrefab'))
const DetectPrefab = React.lazy(() => import('../views/DetectPrefab'))
const EnumPrefab = React.lazy(() => import('../views/EnumPrefab'))
const OtaCenter = React.lazy(() => import('../views/OtaCenter'))
const RobotConfig = React.lazy(() => import('../views/RobotConfig'))
const CmdDebug = React.lazy(() => import('../views/CmdDebug'))
const Terminal = React.lazy(() => import('../views/Terminal'))
const Settings = React.lazy(() => import('../views/Settings'))
const AiCenter = React.lazy(() => import('../views/AiCenter'))
const ThingModel = React.lazy(() => import('../views/admin/ThingModel'))
const PreFab = React.lazy(() => import('../views/PreFab'))
const RobotSimulation = React.lazy(() => import('../views/RobotSimulation'))
const RobotControl = React.lazy(() => import('../views/RobotControl'))
const FsmEditor = React.lazy(() => import('../views/FsmEditor'))
// 下沉静态界面（测点档案 / 巡检计划 / 巡检日志 / 告警模板 / 航点绑定测点，评审用）
const SinkPointArchive = React.lazy(() => import('../views/sink/PointArchive'))
const SinkInspectionPlan = React.lazy(() => import('../views/sink/InspectionPlan'))
const SinkInspectionLog = React.lazy(() => import('../views/sink/InspectionLog'))
const SinkAlarmTemplate = React.lazy(() => import('../views/sink/AlarmTemplate'))
const SinkWaypointBinding = React.lazy(() => import('../views/sink/WaypointBinding'))

function Loading() {
  return <div style={{ display: 'flex', justifyContent: 'center', alignItems: 'center', height: '60vh' }}><Spin size="large" /></div>
}

/** 认证守卫 */
function RequireAuth({ children, roles }: { children: React.ReactNode; roles?: string[] }) {
  const user = useUser()
  const loc = useLocation()
  if (!user.isLogin) return <Navigate to="/login" state={{ from: loc }} replace />
  if (roles && !roles.includes(user.role)) return <Navigate to="/dashboard" replace />
  return <>{children}</>
}

function S(C: React.LazyExoticComponent<React.ComponentType<any>>) {
  return (
    <Suspense fallback={<Loading />}>
      <C />
    </Suspense>
  )
}

export interface MenuRoute {
  path: string
  name: string
  title: string
  icon: string
  roles: string[] | null
  hidden?: boolean
}

/** 侧栏菜单(从路由表派生) */
export const menuRoutes: MenuRoute[] = [
  { path: '/dashboard', name: 'dashboard', title: '监控大盘', icon: 'IconDesktop', roles: null },
  { path: '/robots', name: 'robots', title: '机器人列表', icon: 'IconLayers', roles: null },
  { path: '/alerts', name: 'alerts', title: '告警中心', icon: 'IconAlertTriangle', roles: null },
  { path: '/alarms', name: 'alarms', title: '检测告警', icon: 'IconBell', roles: null },
  { path: '/logs', name: 'logs', title: '日志中心', icon: 'IconFile', roles: null },
//   { path: '/inspection/tasks', name: 'insp-tasks', title: '巡检任务', icon: 'IconList', roles: ['engineer'] },
  { path: '/inspection/log', name: 'insp-log', title: '巡检日志', icon: 'IconHistory', roles: ['engineer'] },
  { path: '/sink/point-archive', name: 'sink-point', title: '测点档案（下沉）', icon: 'IconHash', roles: ['engineer'] },
//   { path: '/sink/inspection-plan', name: 'sink-plan', title: '巡检计划（下沉）', icon: 'IconRoute', roles: ['engineer'] },
//   { path: '/sink/inspection-log', name: 'sink-log', title: '巡检日志（下沉）', icon: 'IconCamera', roles: ['engineer'] },
//   { path: '/sink/alarm-template', name: 'sink-alarm', title: '告警模板（下沉）', icon: 'IconBell', roles: ['engineer'] },
//   { path: '/sink/waypoint-binding', name: 'sink-wpbinding', title: '航点绑定测点（下沉）', icon: 'IconLink', roles: ['engineer'] },
  { path: '/waypoints', name: 'waypoints', title: '航点管理', icon: 'IconMapPin', roles: ['engineer'] },
  { path: '/waypoint-tree', name: 'waypoint-tree', title: '航点树管理', icon: 'IconTreeTriangleDown', roles: ['engineer'] },
  { path: '/waypoint-prefab', name: 'waypoint-prefab', title: '航点树编排', icon: 'IconBranch', roles: ['engineer'] },
  { path: '/inspection-plan-prefab', name: 'inspection-plan-prefab', title: '巡检计划编排', icon: 'IconCalendar', roles: ['engineer'] },
  { path: '/detect-prefab', name: 'detect-prefab', title: '检测算法编排', icon: 'IconEyeOpened', roles: ['engineer'] },
  { path: '/enum-prefab', name: 'enum-prefab', title: '枚举配置', icon: 'IconMenu', roles: ['engineer'] },
  { path: '/ota', name: 'ota', title: 'OTA 中心', icon: 'IconSend', roles: ['engineer'] },
  { path: '/robot-config', name: 'robot-config', title: '机器人参数配置', icon: 'IconSetting', roles: ['engineer'] },
  { path: '/cmd-debug', name: 'cmd-debug', title: '指令调试', icon: 'IconTool', roles: ['engineer'] },
  { path: '/terminal', name: 'terminal', title: '终端调试', icon: 'IconTerminal', roles: ['engineer'] },
  { path: '/ai-center', name: 'ai-center', title: 'AI 中心', icon: 'IconStar', roles: ['engineer'] },
  { path: '/prefab', name: 'prefab', title: 'Prefab 编排', icon: 'IconTreeTriangleDown', roles: ['engineer'] },
  { path: '/simulation', name: 'simulation', title: '机器人仿真', icon: 'IconCamera', roles: ['engineer'] },
  { path: '/robot-control', name: 'robot-control', title: '机器人控制', icon: 'IconActivity', roles: ['engineer'] },
//   { path: '/fsm', name: 'fsm', title: '状态机编辑器', icon: 'IconBranch', roles: ['engineer'] },
//   { path: '/thing-model', name: 'thing-model', title: '物模型管理', icon: 'IconSetting', roles: ['engineer'] },
  { path: '/settings', name: 'settings', title: '系统设置', icon: 'IconSetting', roles: ['engineer'] },
]

export const router = createBrowserRouter([
  {
    path: '/login',
    element: S(Login),
  },
  {
    path: '/',
    element: <MainLayout />,
    children: [
      { index: true, element: <Navigate to="/dashboard" replace /> },
      { path: 'dashboard', element: <RequireAuth>{S(Dashboard)}</RequireAuth> },
      { path: 'robots', element: <RequireAuth>{S(RobotList)}</RequireAuth> },
      { path: 'robots/:id', element: <RequireAuth>{S(RobotDetail)}</RequireAuth> },
      { path: 'alerts', element: <RequireAuth>{S(Alerts)}</RequireAuth> },
      { path: 'alarms', element: <RequireAuth>{S(Alarms)}</RequireAuth> },
      { path: 'logs', element: <RequireAuth>{S(LogCenter)}</RequireAuth> },
      { path: 'inspection/tasks', element: <RequireAuth roles={['engineer']}>{S(InspectionTasks)}</RequireAuth> },
      { path: 'inspection/log', element: <RequireAuth roles={['engineer']}>{S(InspectionLog)}</RequireAuth> },
      { path: 'inspection/log/:id', element: <RequireAuth roles={['engineer']}>{S(InspectionLogDetail)}</RequireAuth> },
      { path: 'sink/point-archive', element: <RequireAuth roles={['engineer']}>{S(SinkPointArchive)}</RequireAuth> },
      { path: 'sink/inspection-plan', element: <RequireAuth roles={['engineer']}>{S(SinkInspectionPlan)}</RequireAuth> },
      { path: 'sink/inspection-log', element: <RequireAuth roles={['engineer']}>{S(SinkInspectionLog)}</RequireAuth> },
      { path: 'sink/alarm-template', element: <RequireAuth roles={['engineer']}>{S(SinkAlarmTemplate)}</RequireAuth> },
      { path: 'sink/waypoint-binding', element: <RequireAuth roles={['engineer']}>{S(SinkWaypointBinding)}</RequireAuth> },
      { path: 'waypoints', element: <RequireAuth roles={['engineer']}>{S(WaypointManager)}</RequireAuth> },
      { path: 'waypoint-tree', element: <RequireAuth roles={['engineer']}>{S(WaypointTreeManager)}</RequireAuth> },
      { path: 'waypoint-prefab', element: <RequireAuth roles={['engineer']}>{S(WaypointTreePrefab)}</RequireAuth> },
      { path: 'inspection-plan-prefab', element: <RequireAuth roles={['engineer']}>{S(InspectionPlanPrefab)}</RequireAuth> },
      { path: 'detect-prefab', element: <RequireAuth roles={['engineer']}>{S(DetectPrefab)}</RequireAuth> },
      { path: 'enum-prefab', element: <RequireAuth roles={['engineer']}>{S(EnumPrefab)}</RequireAuth> },
      { path: 'ota', element: <RequireAuth roles={['engineer']}>{S(OtaCenter)}</RequireAuth> },
      { path: 'robot-config', element: <RequireAuth roles={['engineer']}>{S(RobotConfig)}</RequireAuth> },
      { path: 'cmd-debug', element: <RequireAuth roles={['engineer']}>{S(CmdDebug)}</RequireAuth> },
      { path: 'terminal', element: <RequireAuth roles={['engineer']}>{S(Terminal)}</RequireAuth> },
      { path: 'settings', element: <RequireAuth roles={['engineer']}>{S(Settings)}</RequireAuth> },
      { path: 'ai-center', element: <RequireAuth roles={['engineer']}>{S(AiCenter)}</RequireAuth> },
      { path: 'prefab', element: <RequireAuth roles={['engineer']}>{S(PreFab)}</RequireAuth> },
      { path: 'simulation', element: <RequireAuth roles={['engineer']}>{S(RobotSimulation)}</RequireAuth> },
      { path: 'robot-control', element: <RequireAuth roles={['engineer']}>{S(RobotControl)}</RequireAuth> },
      { path: 'fsm', element: <RequireAuth roles={['engineer']}>{S(FsmEditor)}</RequireAuth> },
      { path: 'thing-model', element: <RequireAuth roles={['engineer']}>{S(ThingModel)}</RequireAuth> },
    ],
  },
  { path: '*', element: <Navigate to="/dashboard" replace /> },
])
