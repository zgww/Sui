import http from './http'
export type Schedule = { mode: 'manual' | 'once' | 'daily' | 'weekly'; timezone: string; start_date: string | null; end_date: string | null; time: string; weekdays: number[] }
export type PlanStage = { map_pk: number; floor: number | null; point_ids: string[] }
export type FloorOption = { map_pk: number; map_name: string; floor: number }
export type Plan = { id: number; robot_pk: number; map_pk: number; stages?: PlanStage[] | null; name: string; point_ids: string[]; schedule: Schedule; enabled: boolean; version: number; next_run_at: string | null }
export type Execution = { stage_index: number; stages: (PlanStage & { map_name: string })[]; id: string; plan_id: number; robot_pk: number; task_id: number | null; trigger: string; status: string; message: string; created_at: string; finished_at: string | null }
export type PlanPreview = { version: number; point_count: number; stages: { map_pk: number; map_name: string; floor: number | null; point_count: number; waypoint_count: number; action_count: number; waypoints: { id: string; point_ids: string[]; actions: { id: string; type: number; steer_point_name: string }[] }[] }[] }
export type Occurrence = { plan_id: number; name: string; at: string }
const base = '/api/inspection-plans'
export const planApi = {
  preview: (p: Plan) => http.get<PlanPreview>(`${base}/${p.id}/preview`, { params: { robot_pk: p.robot_pk } }).then(r => r.data),
  list: (robot_pk: number, name: string, page: number) => http.get<{ total: number; items: Plan[] }>(base, { params: { robot_pk, name, page } }).then(r => r.data),
  save: (body: Omit<Plan, 'id' | 'next_run_at'>, id?: number) => (id ? http.put(`${base}/${id}`, body) : http.post(base, body)).then(r => r.data as Plan),
  remove: (p: Plan) => http.delete(`${base}/${p.id}`, { params: { robot_pk: p.robot_pk, version: p.version } }),
  execute: (p: Plan, request_key: string) => http.post<Execution>(`${base}/${p.id}/execute`, { robot_pk: p.robot_pk, version: p.version, request_key }).then(r => r.data),
  history: (p: Plan, page: number) => http.get<{ total: number; items: Execution[] }>(`${base}/${p.id}/history`, { params: { robot_pk: p.robot_pk, page } }).then(r => r.data),
  calendar: (robot_pk: number, start: string, end: string) => http.get<{ items: Occurrence[] }>(`${base}/calendar/occurrences`, { params: { robot_pk, start, end } }).then(r => r.data),
  points: (robot_pk: number, map_pk: number, name: string, page: number, floor?: number | null, directory_id?: string | null) => http.get<{ total: number; items: { id: string; name: string; code?: string }[] }>(`${base}/options/points`, { params: { robot_pk, map_pk, name, page, floor, directory_id: directory_id || undefined } }).then(r => r.data),
  floors: (robot_pk: number) => http.get<{ items: FloorOption[] }>(`${base}/options/floors`, { params: { robot_pk } }).then(r => r.data),
  continue: (execution: Execution) => http.post<Execution>(`${base}/executions/${execution.id}/continue`, { robot_pk: execution.robot_pk, stage_index: execution.stage_index, confirmed: true }).then(r => r.data),
  reconcile: (execution: Execution, close_idle = false) => http.post<Execution>(`${base}/executions/${execution.id}/reconcile`, { robot_pk: execution.robot_pk, close_idle }).then(r => r.data),
}
