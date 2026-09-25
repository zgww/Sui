import http from './http'

/** 节点类型 schema（后端 GET /api/prefab/node-types） */
export interface NodeTypeInfo {
  schema: Record<string, any>
  description: string
  /** 直接父类名（NodeBase 或中间基类如 CompositeNode），前端渲染继承树 */
  base?: string
  /** 废弃 / 内部节点：仍可解析旧数据，但不进"添加节点"类型目录（后端 __hidden__） */
  hidden?: boolean
}

export interface TreeSummary {
  name: string
  path: string
  /** 相对 prefab 根目录的路径（POSIX 分隔符），前端目录树视图用 */
  rel_path: string
  state: string
  error: string | null
  root: { type: string | null; name: string | null; state: string | null }
}

export interface TreeDetail {
  name: string
  path: string
  state: string
  error: string | null
  spec: Record<string, any>
  status_tree: Record<string, any> | null
}

export const getNodeTypes = () => http.get<Record<string, NodeTypeInfo>>('/api/prefab/node-types')

export const getTrees = () =>
  http.get<{ trees: TreeSummary[]; errors: string[]; dirs: string[] }>('/api/prefab/trees')

export const getTree = (name: string) =>
  http.get<TreeDetail>(`/api/prefab/trees/${encodeURIComponent(name)}`)

export const saveTree = (name: string, spec: Record<string, any>) =>
  http.post<{ ok: boolean; errors: string[] }>(`/api/prefab/trees/${encodeURIComponent(name)}`, spec)

export const reloadTrees = () =>
  http.post<{ ok: boolean; errors: string[] }>('/api/prefab/reload')

/* ---- 目录/文件管理（右击、拖拽等资源管理器式操作） ---- */

export const createDir = (relPath: string) =>
  http.post<{ ok: boolean; rel_path: string }>('/api/prefab/dirs', { rel_path: relPath })

export const deleteDir = (relPath: string) =>
  http.delete<{ ok: boolean; errors: string[] }>('/api/prefab/dirs', { data: { rel_path: relPath } })

export const createFile = (relPath: string) =>
  http.post<{ ok: boolean; errors: string[]; rel_path: string }>('/api/prefab/files', { rel_path: relPath })

export const deleteFile = (relPath: string) =>
  http.delete<{ ok: boolean; errors: string[] }>('/api/prefab/files', { data: { rel_path: relPath } })

export const renameEntry = (relPath: string, newName: string) =>
  http.post<{ ok: boolean; errors: string[] }>('/api/prefab/rename', { rel_path: relPath, new_name: newName })

export const moveEntry = (relPath: string, destDir: string) =>
  http.post<{ ok: boolean; errors: string[] }>('/api/prefab/move', { rel_path: relPath, dest_dir: destDir })
