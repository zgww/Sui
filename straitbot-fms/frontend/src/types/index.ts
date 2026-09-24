/** 全局类型定义 */

export interface Robot {
  id: number
  name: string
  ip: string
  robot_id: number
  api_port: number
  product_type: string
  enabled: boolean
  ssh_user?: string
  ssh_pass?: string
  ssh_port?: number
  log_dir?: string
  install_dir?: string
  version_file?: string
  note?: string
  poll_status?: boolean
  poll_meta?: boolean
  log_retention_days?: number
  video_server?: string
  video_secret?: string
  video_visible_stream?: string
  video_thermal_stream?: string
  video_protocol?: string
  video_use_robot_ip?: boolean
  online?: boolean
  last_battery?: number | null
  last_version?: string | null
  last_seen?: string | null
  created_at?: string
  updated_at?: string
}

export interface Alert {
  id: number
  robot_pk?: number
  ts: string
  alert_id: number
  level: string
  content: string
}

export interface LiveStatus {
  code: number
  msg?: string
  data?: Record<string, any>
}

export interface HistoryPoint {
  ts: string
  battery?: number
  cpu?: number
  temperature?: number
  status?: number
}

export interface ArchivedLog {
  id: number
  filename: string
  size: number
  ts: string
}

export interface ArchivedLogs {
  uploaded: ArchivedLog[]
  fetched: ArchivedLog[]
}

export interface RemoteEntry {
  name: string
  is_dir: boolean
  size: number
  modify_time: string
}

export interface OtaPackage {
  id: number
  filename: string
  version: string
  product_type: string
  size: number
  force_flag: boolean
  md5: string
  notes?: string
  created_at: string
}

export interface OtaTask {
  id: number
  robot_pk: number
  package_filename: string
  from_version?: string
  to_version?: string
  status: string
  force?: boolean
  created_by?: string
  started_at?: string | null
  finished_at?: string | null
  log?: string
}

export interface RobotConfig {
  move_speed?: number
  angular_speed?: number
  is_ring?: boolean
  battery?: { low: number; normal: number }
  inplace_tolerance?: { distance: number; angle: number; duration: number }
  home_pose?: { x: number; y: number; theta: number }
  [k: string]: any
}

export interface ConfigHistoryItem {
  ts: string
  source: string
  operator: string
  config: Record<string, any>
}

export interface AiProvider {
  key: string
  label: string
  model: string
  base_url: string
  protocol: string
  models?: string[]
}

export interface AiSettings {
  provider: string
  base_url: string
  api_key: string
  api_key_set: boolean
  model: string
  protocol: string
  enabled: boolean
  extra_instructions: string
}

export interface ChatMessage {
  role: 'user' | 'assistant'
  content: string
  attachments?: string[]
}

export interface PromptItem {
  title: string
  prompt: string
}

export interface WaypointMap {
  id: number
  name: string
  floor: number | null
  scale: number
  note?: string
  waypoint_count?: number
}

export interface Waypoint {
  id: number
  index: number
  name: string
  type: number
  floor: number | null
  pose: { x: number; y: number; theta: number }
  lift_height: number
  ptz: { pan: number; tilt: number; zoom: number }
  calib_visible: string
  calib_thermal: string
  note: string
  actions?: any[]
}

export interface InspectionTask {
  id: number
  name: string
  status: string
  created_at: string
}

export interface ScanItem {
  ip: string
  robot_id?: number
  name?: string
  product_type?: string
  product?: number
  ssh_user?: string
  ssh_pass?: string
  firmware?: string
  motion?: string
  sn?: string
  already_added?: boolean
}

export interface ApiResponse<T = any> {
  ok?: boolean
  msg?: string
  data?: T
  [k: string]: any
}

export interface SettingsInfo {
  app_name: string
  version: string
  poll_status_interval_sec: number
  poll_meta_interval_sec: number
  default_log_retention_days: number
}

// ========== 航点树管理 ==========

export interface Ptz {
  focus: number
  zoom: number
  tilt: number
  pan: number
  focal_len: number
}

export interface Pose {
  theta: number
  point: { x: number; y: number; z: number }
}

/** 节点基类 — 所有节点共有的字段 */
export interface BaseNode {
  name: string
  enable: boolean
  id: string
  nodeType: string
  children: TreeNode[]
}

/** 航点节点 */
export interface WaypointNode extends BaseNode {
  nodeType: 'WaypointNode'
  pose: Pose
  index: number
  type: number
}

/** 动作点节点 */
export interface ActionNode extends BaseNode {
  nodeType: 'ActionNode'
  ptz_param: Ptz
  lift_height: number
  thermometry_points: any[]
  snap_shot_url: string
  type: number
  steer_point_name: string
}

/** 测点节点 */
export interface TaskPointNode extends BaseNode {
  nodeType: 'TaskPointNode'
}

/** ORB 配准节点 */
export interface OrbRegistration extends BaseNode {
  nodeType: 'OrbRegistration'
  refImageUrl: string
  ptz: Ptz
  lift_height: number
  pose: Pose
}

/** 根节点 */
export interface RootNode extends BaseNode {
  nodeType: 'Root'
}

/** 分组节点 (用于将多个节点收纳到一个分组下) */
export interface GroupNode extends BaseNode {
  nodeType: 'GroupNode'
}

/** 树节点联合类型 (判别联合, 以 nodeType 为判别字段) */
export type TreeNode = WaypointNode | ActionNode | TaskPointNode | OrbRegistration | RootNode | GroupNode
