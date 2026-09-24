import http from './http'

/** 底盘位姿/速度（上位机标准单位） */
export interface Pose {
  x: number          // m（挂轨弧长）
  y: number          // m
  yaw: number        // 度
  linear_x: number   // m/s
  linear_y: number   // m/s
  angular: number    // 度/s
}

export interface Battery {
  battery_percent: number  // %
  voltage: number          // V
  current: number          // A（正充负放）
  capacity: number         // Ah
  temperature: number      // ℃
  contact: number
  charge_state: number
  contacted: boolean
  charging: boolean
}

export interface Rfid {
  rfid: number   // 卡号，0 表示未触发
  x: number      // m
  ts: number
}

/** 伸缩杆（升降）状态（0x0E 电机状态上发，motor_id=1） */
export interface Lift {
  motor_id: number
  state: number            // 0空闲 1运行 2已到位 3初始化
  coord_m: number          // 当前高度 m
  speed: number            // mm/s
  status_word: number
  driver_error: number
  temperature: number
  updated_at: number
  target_m: number | null
  arrived: boolean
}

/** 单个状态机的当前状态（main/charge/floor/insp） */
export interface SmStateInfo {
  state: string | null
  active: boolean
  signal: string | null
}

/** 巡检断点（存在即"有未完成巡检"，开机据此续跑） */
export interface InspectionProgress {
  inspection_id?: string
  waypoint_index?: number
  updated_at?: string
  [k: string]: unknown
}

/** 当前巡检运行时状态 */
export interface InspectionState {
  busy: boolean
  inspection_id: string | null
  current_floor: number | null
  current_waypoint_id: string | null
  waypoint_cursor: number
  current_action_index: number
  current_action_id: string | null
  current_action_type: number | null
  target_x_m: number | null
  target_lift_m: number | null
  move_retry: number
  lift_retry: number
  last_abort: Record<string, unknown> | null
  target_ptz: { pan: number; tilt: number; zoom?: number } | null
  ptz_busy: boolean
  ptz_done: boolean
  ptz_error: string | null
  vision_kind: string | null
  vision_busy: boolean
  vision_done: boolean
  vision_error: string | null
  vision_result: Record<string, unknown> | null
  abort_reason: string | null
}

export interface RobotControlState {
  robot_id: string
  name: string
  version: string
  robot_type: string
  ip: string
  port: number
  online: boolean
  board_status: string
  firmware_version: string
  chassis_state: number
  chassis_mode: number
  state_path: string[]
  pose: Pose
  battery: Battery
  rfid: Rfid
  lift: Lift
  inspection: InspectionState
  /** 状态机各子机当前状态（main/charge/floor/insp），按名称做 key */
  sm: Record<string, SmStateInfo>
  progress: InspectionProgress | null
  /**
   * robot.state（RobotState）原始字段树。
   *
   * 字段与后端 dataclass 一一对应（command/insp/switch_floor/charge/battery/
   * nudge/online/board_status/firmware_version/chassis_state/chassis_mode/pose/
   * rfid/lift），刻意不做业务重组——新字段会自动出现，便于与代码逐项对照。
   */
  raw_state?: Record<string, unknown>
}

export async function fetchRobotControlState(): Promise<RobotControlState> {
  const r = await http.get<RobotControlState>('/api/rail/robot/state')
  return r.data
}

/** 点动向前（底盘持续走，直到调用 stopRobot）；speed 不传用后端默认点动速度 */
export async function jogForward(speed?: number): Promise<void> {
  await http.post('/api/rail/robot/jog/forward', speed == null ? {} : { speed })
}

/** 点动向后 */
export async function jogBackward(speed?: number): Promise<void> {
  await http.post('/api/rail/robot/jog/backward', speed == null ? {} : { speed })
}

/** 立即停车 */
export async function stopRobot(): Promise<void> {
  await http.post('/api/rail/robot/stop')
}

/** 绝对位置移动到弧长 x（m） */
export async function gotoX(x: number): Promise<void> {
  await http.post('/api/rail/robot/goto', { x })
}

/** 巡检任务下发结果（/inspection 与 /inspection/test 共用） */
export interface InspectionDispatchResult {
  accepted: boolean
  inspection_id: string
  name?: string
  floors?: string
  waypoint_count?: number
  action_count?: number
  record_path?: string
  source?: string
  reason?: string
  current_inspection_id?: string
}

/**
 * 下发一个自定义巡检任务。
 *
 * body 与 `tests/test_inspection.json` 同构：楼层分段对象或其数组
 * （同 id 的多个分段视为同一次巡检的多楼层）。后端不要求控制板在线——
 * 任务先落盘、状态机进巡检，连上后执行。已有未完成巡检时返回 409。
 */
export async function dispatchInspection(payload: unknown): Promise<InspectionDispatchResult> {
  const r = await http.post<InspectionDispatchResult>('/api/rail/robot/inspection', payload)
  return r.data
}

/** 一键下发内置测试巡检任务（后端 tests/test_inspection.json，多楼层）；忙时后端返回 409 */
export async function startTestInspection(): Promise<InspectionDispatchResult> {
  const r = await http.post<InspectionDispatchResult>('/api/rail/robot/inspection/test')
  return r.data
}

/** 取消当前正在进行的巡检（向状态机发送"取消巡检"信号） */
export async function cancelInspection(): Promise<{ code: number; msg: string }> {
  const r = await http.post<{ code: number; msg: string }>('/api/rail/robot/inspection/cancel')
  return r.data
}

/** 删除 data/inspection 下全部巡检断点文件（*.progress.json），清理"巡检中"残留状态 */
export async function clearInspectionProgress(): Promise<{ code: number; msg: string; removed: string[]; count: number }> {
  const r = await http.post<{ code: number; msg: string; removed: string[]; count: number }>('/api/rail/robot/inspection/progress/clear')
  return r.data
}

/** 手动回去充电：主机进"去充电"，走到充电桩坐标 */
export async function goCharge(): Promise<{ code: number; msg: string }> {
  const r = await http.post<{ code: number; msg: string }>('/api/rail/robot/charge/go')
  return r.data
}

/** 重置状态机：停车、停全部子机、主机回到启动态 */
export async function resetStateMachine(): Promise<{ code: number; msg: string }> {
  const r = await http.post<{ code: number; msg: string }>('/api/rail/robot/state/reset')
  return r.data
}
