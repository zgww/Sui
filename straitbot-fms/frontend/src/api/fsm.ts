import http from './http'

/** 状态动作图对象类型 */
export type FsmObjType = 'state_machine' | 'state' | 'signal_action' | 'sm_activate_action'

/** 画布对象：坐标 + 属性（x/y 为画布逻辑坐标，缩放平移不影响） */
export interface FsmObject {
  id: string
  type: FsmObjType
  name: string
  x: number
  y: number
  description?: string
  /** 信号迁移动作：监听的信号名 */
  signal?: string
  /** 状态机：初始状态名 */
  initial_state?: string
  /** 状态机：结束信号名（收到后通知激活者） */
  end_signal?: string
}

/** 对象间连线（pin 到 pin） */
export interface FsmConnection {
  id: string
  from: string
  fromPin: string
  to: string
  toPin: string
}

/** .fsm.json 文件内容 */
export interface FsmSpec {
  version: number
  name: string
  description?: string
  objects: FsmObject[]
  connections: FsmConnection[]
}

export interface FsmFileSummary {
  name: string
  path: string
  /** 相对 fsm 根目录的路径（POSIX 分隔符） */
  rel_path: string
}

export interface FsmTreeList {
  files: FsmFileSummary[]
  dirs: string[]
}

export interface FsmTreeDetail {
  name: string
  path: string
  rel_path: string
  spec: FsmSpec
}

export const getFsmTrees = () => http.get<FsmTreeList>('/api/fsm/trees')

export const getFsmTree = (relPath: string) =>
  http.get<FsmTreeDetail>(`/api/fsm/trees/${encodeURIComponent(relPath)}`)

export const saveFsmTree = (relPath: string, spec: FsmSpec) =>
  http.post<{ ok: boolean }>(`/api/fsm/trees/${encodeURIComponent(relPath)}`, spec)

/* ---- 目录/文件管理 ---- */

export const createFsmDir = (relPath: string) =>
  http.post<{ ok: boolean; rel_path: string }>('/api/fsm/dirs', { rel_path: relPath })

export const deleteFsmDir = (relPath: string) =>
  http.delete<{ ok: boolean }>('/api/fsm/dirs', { data: { rel_path: relPath } })

export const createFsmFile = (relPath: string) =>
  http.post<{ ok: boolean; rel_path: string }>('/api/fsm/files', { rel_path: relPath })

export const deleteFsmFile = (relPath: string) =>
  http.delete<{ ok: boolean }>('/api/fsm/files', { data: { rel_path: relPath } })

export const renameFsmEntry = (relPath: string, newName: string) =>
  http.post<{ ok: boolean }>('/api/fsm/rename', { rel_path: relPath, new_name: newName })

export const moveFsmEntry = (relPath: string, destDir: string) =>
  http.post<{ ok: boolean }>('/api/fsm/move', { rel_path: relPath, dest_dir: destDir })
