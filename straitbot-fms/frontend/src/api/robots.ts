import http from './http'
import type { Robot, Alert, HistoryPoint, ArchivedLogs, RemoteEntry, OtaPackage, OtaTask, RobotConfig, ConfigHistoryItem, SettingsInfo, ApiResponse } from '../types'

export const listRobots = () => http.get<Robot[]>('/api/robots')
export const createRobot = (data: Partial<Robot>) => http.post('/api/robots', data)
export const updateRobot = (id: number, data: Partial<Robot>) => http.put(`/api/robots/${id}`, data)
export const deleteRobot = (id: number) => http.delete(`/api/robots/${id}`)
export const pingRobot = (id: number) => http.get<{ ok: boolean; msg: string }>(`/api/robots/${id}/ping`)

export const liveStatus = (id: number) => http.get(`/api/monitor/${id}/status`)
export const history = (id: number, hours: number) => http.get<{ status: HistoryPoint[] }>(`/api/monitor/${id}/history`, { params: { hours } })
export const alerts = (id: number, params: Record<string, any>) => http.get<Alert[]>(`/api/monitor/${id}/alerts`, { params })
export const versions = (id: number) => http.get(`/api/monitor/${id}/versions`)
export const configHistory = (id: number) => http.get<ConfigHistoryItem[]>(`/api/monitor/${id}/configs`)

export const remoteList = (id: number, sub: string) => http.get<RemoteEntry[]>(`/api/logs/${id}/remote/list`, { params: { sub } })
export const fetchRemote = (id: number, files: string[]) => http.post(`/api/logs/${id}/fetch`, { files })
export const archivedList = (id: number) => http.get<ArchivedLogs>(`/api/logs/${id}/archived`)
export const archivedDownloadUrl = (id: number, kind: string, logId: number) => `/api/logs/${id}/archived/${kind}/${logId}/download?_t=${Date.now()}`
export const archivedDelete = (id: number, kind: string, logId: number) => http.delete(`/api/logs/${id}/archived/${kind}/${logId}`)

export const listPackages = () => http.get<OtaPackage[]>('/api/ota/packages')
export const uploadPackage = (form: FormData) => http.post('/api/ota/packages', form, { timeout: 600000 })
export const deletePackage = (id: number) => http.delete(`/api/ota/packages/${id}`)
export const listTasks = () => http.get<OtaTask[]>('/api/ota/tasks')
export const getTask = (id: number) => http.get<OtaTask>(`/api/ota/tasks/${id}`)
export const createTasks = (data: any) => http.post('/api/ota/tasks', data)
export const retryTask = (id: number) => http.post(`/api/ota/tasks/${id}/retry`)

export const readRobotConfig = (id: number) => http.get<ApiResponse<RobotConfig>>(`/api/robot_config/${id}`)
export const writeRobotConfig = (id: number, payload: Partial<RobotConfig>) => http.post(`/api/robot_config/${id}`, payload)

export const rawCmd = (id: number, cmd: number, data: any) => http.post(`/api/cmd/${id}/raw`, { cmd, data })
export const cmdCharge = (id: number, action: number, pile?: number) => http.post(`/api/cmd/${id}/charge`, null, { params: { action, pile } })
export const cmdHome = (id: number, goHome: boolean) => http.post(`/api/cmd/${id}/home`, null, { params: { go_home: goHome } })
export const cmdSelfCheck = (id: number) => http.post(`/api/cmd/${id}/selfcheck`)
export const cmdClearAlert = (id: number) => http.post(`/api/cmd/${id}/clear_alert`)
export const cmdRestartApp = (id: number) => http.post(`/api/cmd/${id}/restart_app`)
export const cmdRebootOs = (id: number) => http.post(`/api/cmd/${id}/reboot_os`)

export const fetchSettings = () => http.get<SettingsInfo>('/api/settings/info')
