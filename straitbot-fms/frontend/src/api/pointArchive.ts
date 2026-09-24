import http from './http'
export type Kind = 'stations' | 'bays' | 'equipment' | 'points'
export type Entity = { id: string; name: string; code?: string; active?: boolean; [key: string]: any }
export type Node = {
  id: string
  name: string
  type: 'station' | 'voltage' | 'bay' | 'equipment' | 'point'
  has_children: boolean
  voltage_level?: string
}
export type Page<T> = { revision: number; total: number; items: T[] }
export type Preview = {
  revision: number
  counts: Record<Kind, number>
  changes: Record<string, unknown>
  warnings: string[]
}
const base = '/api/point-archive'
const config = (revision: number) => ({
  headers: { 'If-Match': String(revision), 'Content-Type': 'application/json' },
})
export const archiveApi = {
  meta: () =>
    http
      .get<{ revision: number; counts: Record<Kind, number>; status: string }>(`${base}/meta`)
      .then((r) => r.data),
  list: (kind: Kind, params: Record<string, unknown>) =>
    http.get<Page<Entity>>(`${base}/entities/${kind}`, { params }).then((r) => r.data),
  detail: (kind: Kind, id: string) =>
    http
      .get<{ revision: number; item: Entity }>(`${base}/entities/${kind}/${encodeURIComponent(id)}`)
      .then((r) => r.data),
  create: (kind: Kind, item: Entity, revision: number) =>
    http.post(`${base}/entities/${kind}`, item, config(revision)),
  update: (kind: Kind, item: Entity, revision: number) =>
    http.put(`${base}/entities/${kind}/${encodeURIComponent(item.id)}`, item, config(revision)),
  remove: (kind: Kind, id: string, revision: number) =>
    http.delete(`${base}/entities/${kind}/${encodeURIComponent(id)}`, config(revision)),
  tree: (params: Record<string, unknown>) =>
    http.get<Page<Node>>(`${base}/tree`, { params }).then((r) => r.data),
  preview: (raw: string) =>
    http
      .post<Preview>(`${base}/import/preview`, raw, { headers: { 'Content-Type': 'application/json' } })
      .then((r) => r.data),
  publish: (raw: string, revision: number) => http.put(`${base}/snapshot`, raw, config(revision)),
  export: () => http.get(`${base}/export`, { responseType: 'blob' }).then((r) => r.data as Blob),
}

export type Binding = {
  robot_name?: string
  map_name?: string
  plan_names?: string[]
  point_name?: string
  point_active?: boolean
  id: number
  point_id: string
  waypoint_pk: number
  action_pk?: number
  waypoint_name: string
  action_name?: string
  robot_pk: number
  map_pk: number
}
export type BindingOption = {
  id: number
  name: string
  robot_name: string
  map_name: string
  robot_pk: number
  map_pk: number
  floor?: number
  wp_id?: string
  binding_count: number
  actions: { id: number; name: string; action_type: number }[]
}
export const bindingApi = {
  scopedList: (robot_pk: number, waypoint_pk: number) => http.get<{ items: Binding[] }>(`${base}/bindings`, { params: { robot_pk, waypoint_pk } }).then(r => r.data),
  batch: (robot_pk: number, waypoint_pk: number, point_ids: string[], action_pk?: number) => http.post(`${base}/bindings/batch`, { robot_pk, waypoint_pk, point_ids, action_pk }),
  list: (point_id: string, robot_pk?: number) =>
    http.get<{ items: Binding[] }>(`${base}/bindings`, { params: { point_id, robot_pk } }).then((r) => r.data),
  options: (name: string, page: number, robot_pk?: number, filters: { map_pk?: number; floor?: number; waypoint_pk?: number } = {}) =>
    http
      .get<{
        items: BindingOption[]
        total: number
      }>(`${base}/binding-options`, { params: { name: name || undefined, page, page_size: 50, robot_pk, ...filters } })
      .then((r) => r.data),
  create: (point_id: string, waypoint_pk: number, action_pk?: number) =>
    http.post(`${base}/bindings`, {
      point_id,
      waypoint_pk,
      ...(action_pk === undefined ? {} : { action_pk }),
    }),
  remove: (id: number) => http.delete(`${base}/bindings/${id}`),
}

export type Directory = Entity & { parent_id: string | null; role: string; child_count: number; point_count: number }
export type CatalogKind = 'directories' | 'points'
export type PlatformCheck = { valid: boolean; revision: number; message: string; issues: { id: string; name: string; kind: string; message: string }[] }
export const catalogApi = {
  directories: () => http.get<{ revision: number; point_count: number; items: Directory[] }>(`${base}/catalog/directories`).then(r => r.data),
  points: (params: Record<string, unknown>) => http.get<Page<Entity>>(`${base}/catalog/points`, { params }).then(r => r.data),
  create: (kind: CatalogKind, item: Entity, revision: number) => http.post(`${base}/catalog/${kind}`, item, config(revision)),
  update: (kind: CatalogKind, item: Entity, revision: number) => http.put(`${base}/catalog/${kind}/${encodeURIComponent(item.id)}`, item, config(revision)),
  remove: (kind: CatalogKind, id: string, revision: number) => http.delete(`${base}/catalog/${kind}/${encodeURIComponent(id)}`, config(revision)),
  check: () => http.get<PlatformCheck>(`${base}/catalog/platform-check`).then(r => r.data),
  export: (platform: boolean) => http.get(`${base}/catalog/export`, { params: { platform }, responseType: 'blob' }).then(r => r.data as Blob),
  preview: (raw: string) => http.post<Preview>(`${base}/catalog/import/preview`, raw, { headers: { 'Content-Type': 'application/json' } }).then(r => r.data),
  publish: (raw: string, revision: number) => http.put(`${base}/catalog/import`, raw, config(revision)),
}
