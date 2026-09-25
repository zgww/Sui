import http from './http'

const BASE = '/api/alarms'

/** 检测告警 */
export interface AlarmRow {
  id: number
  run_id: number | null
  action_result_id: number | null
  inspection_id: string
  floor: number
  waypoint_id: string
  action_id: string
  point_id: string
  point_name: string
  alarm_type: string
  algorithm: string
  level: string
  title: string
  content: string
  picture: string
  extra: any
  status: 'unack' | 'ack'
  triggered_at: string | null
  acknowledged_at: string | null
  acknowledged_by: string
  created_at: string | null
}

export interface AlarmQuery {
  status?: string
  alarm_type?: string
  level?: string
  keyword?: string
  start?: string
  end?: string
  page?: number
  page_size?: number
}

export interface AlarmPage {
  total: number
  page: number
  page_size: number
  items: AlarmRow[]
}

export interface AlarmMeta {
  types: string[]
  levels: string[]
}

/** 告警分页列表（筛选） */
export const listAlarms = (params: AlarmQuery) =>
  http.get<AlarmPage>(BASE, { params })

/** 未确认告警数量（角标） */
export const getUnackCount = () =>
  http.get<{ count: number }>(`${BASE}/unack-count`)

/** 筛选项元数据（类型 / 级别） */
export const getAlarmMeta = () =>
  http.get<AlarmMeta>(`${BASE}/meta`)

/** 确认单条 */
export const ackAlarm = (id: number) =>
  http.post<{ id: number; status: string }>(`${BASE}/${id}/ack`)

/** 确认所有符合筛选条件的未确认告警 */
export const ackAllAlarms = (filters: Partial<AlarmQuery>) =>
  http.post<{ acknowledged: number }>(`${BASE}/ack-all`, filters)
