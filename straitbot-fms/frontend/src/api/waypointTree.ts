import http from './http'
import type { TreeNode } from '../types'

// ========== 树读写 ==========
export const getTree = (rid: number) =>
  http.get<TreeNode>(`/api/waypoint-tree/${rid}/tree`)

export const saveTree = (rid: number, tree: TreeNode) =>
  http.put(`/api/waypoint-tree/${rid}/tree`, { tree })

// ========== 从 inspection.json 导入 ==========
export const importInspection = (rid: number, data: any, replace = true) =>
  http.post(`/api/waypoint-tree/${rid}/import-inspection`, { data, replace })

export const importInspectionFile = (rid: number, file: File, replace = true, merge = false) => {
  const form = new FormData()
  form.append('file', file)
  return http.post(`/api/waypoint-tree/${rid}/import-inspection/file?replace=${replace}&merge=${merge}`, form)
}

// ========== 节点 CRUD ==========
export const createNode = (rid: number, nodeType: string, name: string, parentId: string | null, extra: Record<string, any> = {}) =>
  http.post<TreeNode>(`/api/waypoint-tree/${rid}/node`, { nodeType, name, parentId, extra })

export const updateNode = (rid: number, nodeId: string, data: TreeNode) =>
  http.put<TreeNode>(`/api/waypoint-tree/${rid}/node/${nodeId}`, { data })

export const deleteNode = (rid: number, nodeId: string) =>
  http.delete(`/api/waypoint-tree/${rid}/node/${nodeId}`)

export const copyNode = (rid: number, nodeId: string, targetParentId: string | null) =>
  http.post<TreeNode>(`/api/waypoint-tree/${rid}/node/copy`, { nodeId, targetParentId })

export const moveNode = (rid: number, nodeId: string, targetParentId: string | null, position: number = -1) =>
  http.post(`/api/waypoint-tree/${rid}/node/move`, { nodeId, targetParentId, position })

// ========== 创建分组 (多选) ==========
export const createGroup = (rid: number, nodeIds: string[], name: string = '分组') =>
  http.post<TreeNode>(`/api/waypoint-tree/${rid}/node/group`, { nodeIds, name })

// ========== 导出文件 ==========
export const exportFileUrl = (rid: number) => `/api/waypoint-tree/${rid}/export/file`

// ========== ORB 配准参考图抓拍 ==========
export const captureRefImage = (rid: number, image: string) =>
  http.post<{ ok: boolean; path: string; filename: string }>(
    `/api/waypoint-tree/${rid}/capture-ref-image`, { image }
  )

/** 拼接参考图的访问 URL (refImageRelPath 形如 navRefImg/xxx.jpg) */
export const refImageUrl = (rid: number, refImageRelPath: string) => {
  if (!refImageRelPath) return ''
  // 提取 filename (navRefImg/xxx.jpg → xxx.jpg)
  const filename = refImageRelPath.split('/').pop() || refImageRelPath
  return `/api/waypoint-tree/${rid}/ref-image/${filename}`
}
