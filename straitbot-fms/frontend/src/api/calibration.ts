import http from './http'

// ========== 校准接口 ==========

export interface CalibResponse {
  ok: boolean
  message: string
  steps: string[]
  details?: {
    x_offset_px: number
    y_offset_px?: number
    total_matches: number
    inlier_count: number
    homography?: number[][]
    scale_m_per_px?: number
    delta_d_m?: number
    pan_coef?: number
    move_distance_m?: number
    world_dx?: number
    world_dy?: number
    from?: { x: number; y: number; theta: number }
    to?: { x: number; y: number; theta: number }
  }
  iterations?: Array<{
    iteration: number
    x_offset_px: number
    y_offset_px: number
    total_offset_px: number
    total_matches: number
    inlier_count: number
    converged?: boolean
    pan_delta?: number
    tilt_delta?: number
    ptz_from?: { pan: number; tilt: number; zoom: number }
    ptz_to?: { pan: number; tilt: number; zoom: number }
    move_distance_m?: number
    from?: { x: number; y: number; theta: number }
    to?: { x: number; y: number; theta: number }
    error?: string
    debug_images?: string[]
  }>
  converged?: boolean
  max_iterations?: number
  threshold_px?: number
  calibrated?: boolean
  registered?: boolean
  debug_session?: string
  debug_images?: string[]
}

/** 仅配准(不移动机器人) */
export const calibRegister = (rid: number, nodeId: string) =>
  http.post<CalibResponse>('/api/calibration/register', { rid, node_id: nodeId })

/** 单次X轴定位校准 */
export const calibXAxisStep = (rid: number, nodeId: string) =>
  http.post<CalibResponse>('/api/calibration/x-axis-step', { rid, node_id: nodeId })

/** 迭代X轴定位校准 (收敛阈值15px, 最多10次) */
export const calibXAxisIter = (rid: number, nodeId: string) =>
  http.post<CalibResponse>('/api/calibration/x-axis-iter', { rid, node_id: nodeId })

/** 单次云台校准 */
export const calibPtzStep = (rid: number, nodeId: string) =>
  http.post<CalibResponse>('/api/calibration/ptz-step', { rid, node_id: nodeId })

/** 迭代云台校准 (收敛阈值10px, 最多8次) */
export const calibPtzIter = (rid: number, nodeId: string) =>
  http.post<CalibResponse>('/api/calibration/ptz-iter', { rid, node_id: nodeId })

/** 移动到航点位置 */
export const calibMoveToWaypoint = (rid: number, nodeId: string) =>
  http.post<CalibResponse>('/api/calibration/move-to-waypoint', { rid, node_id: nodeId })

/** 调试图片URL (path是calib_debug下的相对路径或绝对路径, 自动处理) */
export const debugImageUrl = (rid: number, path: string) => {
  // 处理绝对路径: /app/data/robot/1/calib_debug/xxx → xxx
  const p = path.replace(/.*calib_debug[\/\\]?/, '')
  return `/api/calibration/debug-image/${rid}/${p}`
}

/** 列出机器人所有调试会话(树形+文件+指标) */
export const listDebugSessions = (rid: number, nodeId?: string) =>
  http.get<{ sessions: any; files: string[]; metrics: Record<string, any> }>(
    `/api/calibration/debug-sessions/${rid}`,
    { params: nodeId ? { node_id: nodeId } : {} },
  )
