import http from './http'
import type { NodeTypeInfo } from './prefab'

/** 航点树文件摘要 */
export interface WaypointTreeSummary {
  rel_path: string
  name: string
  root: { type: string | null; name: string | null } | null
  error: string | null
}

export interface WaypointTreeDetail {
  rel_path: string
  spec: Record<string, any>
}

export interface ImportResult {
  ok: boolean
  spec: Record<string, any>
  counts: Record<string, number>
}

const BASE = '/api/waypoint-prefab'

export const getWaypointNodeTypes = () =>
  http.get<Record<string, NodeTypeInfo>>(`${BASE}/node-types`)

export const listWaypointTrees = () =>
  http.get<{ trees: WaypointTreeSummary[]; dirs: string[] }>(`${BASE}/trees`)

export const getWaypointTree = (relPath: string) =>
  http.get<WaypointTreeDetail>(`${BASE}/tree`, { params: { rel_path: relPath } })

export const saveWaypointTree = (relPath: string, spec: Record<string, any>) =>
  http.post<{ ok: boolean; rel_path: string }>(`${BASE}/tree`, { rel_path: relPath, spec })

export const createWaypointFile = (relPath: string) =>
  http.post<{ ok: boolean; rel_path: string }>(`${BASE}/files`, { rel_path: relPath })

export const deleteWaypointFile = (relPath: string) =>
  http.delete(`${BASE}/files`, { data: { rel_path: relPath } })

export const createWaypointDir = (relPath: string) =>
  http.post(`${BASE}/dirs`, { rel_path: relPath })

export const deleteWaypointDir = (relPath: string) =>
  http.delete(`${BASE}/dirs`, { data: { rel_path: relPath } })

export const renameWaypointEntry = (relPath: string, newName: string) =>
  http.post(`${BASE}/rename`, { rel_path: relPath, new_name: newName })

export const moveWaypointEntry = (relPath: string, destDir: string) =>
  http.post(`${BASE}/move`, { rel_path: relPath, dest_dir: destDir })

/** 巡检任务 JSON（楼层对象或数组）→ 航点树 spec（不落盘，前端载入后保存） */
export const importInspectionToWaypoint = (payload: unknown) =>
  http.post<ImportResult>(`${BASE}/import-inspection`, payload)

export interface AlgorithmItem {
  /** 写进 DetectBoxNode.algorithm 的值（稳定契约，改名不影响已绑好的框） */
  id: string
  name: string
  category: string
  /** 画布上框的描边色（#RRGGBB）；空串时用前端兜底色 */
  color: string
  description: string
  /**
   * 算法示意图：`data:image/...;base64,...`，空串 = 还没上传。
   * **直接内联在 algorithms.json 里**（不走文件、不走静态目录）——
   * 一份目录就一个文件，搬走/拷给别人不断链。代价是文件会变大，
   * 所以前端上传前先压到 320px（见 utils/algoImage.ts）。
   */
  image: string
}

/** 检测框可绑的算法类型目录（读后端 data/algorithms.json，改完刷新页面即生效） */
export const getWaypointAlgorithms = () =>
  http.get<{ ok: boolean; algorithms: AlgorithmItem[]; warning?: string }>(
    `${BASE}/algorithms`)

/**
 * 给某个算法存 / 删示意图（**写回 data/algorithms.json**，需要工程师权限）。
 * @param image `data:image/...;base64,...`；传**空串 = 删掉**示意图
 */
export const saveWaypointAlgorithmImage = (id: string, image: string) =>
  http.post<{ ok: boolean; id: string; has_image: boolean }>(
    `${BASE}/algorithms/image`, { id, image })

export interface BackgroundUploadResult {
  ok: boolean
  /** 可直接塞进 BackgroundImageNode.src 的相对路径 */
  path: string
  /** 图片原始像素尺寸（后端读不出来时为 0），前端拿它估算初始缩放 */
  width: number
  height: number
}

/** 上传地图背景图（存 data/calibration/background/，静态目录可直接访问） */
export const uploadWaypointBackground = (file: File) => {
  const fd = new FormData()
  fd.append('file', file)
  return http.post<BackgroundUploadResult>(`${BASE}/background`, fd)
}

export interface CaptureUploadResult {
  ok: boolean
  /** 相对**当前 prefab 文件**的路径，写进 ActionPointNode.imageUrl */
  rel: string
  /** 可直接塞进 `<img src>` 的地址（`<img>` 带不了鉴权头，只能走静态挂载） */
  url: string
  file: string
}

/**
 * 上传云台抓拍图：存到**该 prefab 文件所在目录**下的 `images/`。
 *
 * `relPath` 是当前编辑的 prefab 的 rel_path ——必须一起传，后端才知道该放哪儿，
 * 也才能顺手做一次"这个文件真的存在"的校验。
 */
export const uploadWaypointCapture = (file: File, relPath: string) => {
  const fd = new FormData()
  fd.append('file', file)
  fd.append('rel_path', relPath)
  return http.post<CaptureUploadResult>(`${BASE}/capture`, fd)
}

/** 云台当前位姿（后端按 robot.prefab.json 配置的云台走 ISAPI 现取） */
export interface PtzPose {
  ok: boolean
  pan: number | null
  tilt: number | null
  zoom: number | null
}

/** 读取当前云台位姿：不查数据库，直接根据 robot.prefab.json 的云台配置实时取。 */
export const getWaypointPtzPose = () =>
  http.get<PtzPose>(`${BASE}/ptz-pose`)
