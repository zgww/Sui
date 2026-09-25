import http from './http'

/** 云台方向/变焦命令（与后端 _MOVE_CMDS 对应） */
export type PtzCommand = 'left' | 'right' | 'up' | 'down' | 'zoomin' | 'zoomout'
export type PresetAction = 'goto' | 'set' | 'clean'

export interface PtzDeviceInfo {
  ip: string
  port: number
  serial_number: string
  device_type: number
  analog_chan_num: number
  start_chan: number
  ip_chan_num: number
  start_d_chan: number
}

export interface PtzState {
  configured: boolean
  connected: boolean
  ip?: string
  port?: number
  channel?: number
  username?: string
  device_info?: PtzDeviceInfo | null
  reason?: string
}

export async function fetchPtzState(): Promise<PtzState> {
  const r = await http.get<PtzState>('/api/rail/ptz/state')
  return r.data
}

export async function ptzConnect(): Promise<void> {
  await http.post('/api/rail/ptz/connect')
}

export async function ptzDisconnect(): Promise<void> {
  await http.post('/api/rail/ptz/disconnect')
}

/** 云台方向/变焦；stop=true 停止该动作（按住式控制松手时调用） */
export async function ptzMove(command: PtzCommand, opts?: { stop?: boolean; speed?: number }): Promise<void> {
  await http.post('/api/rail/ptz/move', {
    command,
    stop: opts?.stop ?? false,
    speed: opts?.speed ?? 4,
  })
}

/** 停止全部云台运动 */
export async function ptzStop(): Promise<void> {
  await http.post('/api/rail/ptz/stop')
}

export async function ptzPreset(action: PresetAction, index: number): Promise<void> {
  await http.post('/api/rail/ptz/preset', { action, index })
}

/**
 * 抓图，返回 JPEG 二进制。
 *
 * 要**上传/保存**时拿这个（`new File([blob], ...)` 直接塞进 FormData）；
 * 只想预览就用 `ptzSnapshot()` 拿 object URL——但 object URL 转不回二进制，
 * 先拿 URL 再想存盘就得绕一圈 fetch，没必要。
 */
export async function ptzSnapshotBlob(): Promise<Blob> {
  const r = await http.get('/api/rail/ptz/snapshot', { responseType: 'blob' })
  return r.data as Blob
}

/** 抓图，返回 JPEG 的 object URL（调用方负责 revokeObjectURL）。 */
export async function ptzSnapshot(): Promise<string> {
  return URL.createObjectURL(await ptzSnapshotBlob())
}
