import http from './http'
import type { NodeTypeInfo } from './prefab'

/** 检测流程文件摘要（与航点树 / 计划树同形，接口由后端 prefab_store 工厂生成） */
export interface DetectTreeSummary {
  rel_path: string
  name: string
  root: {
    type: string | null
    name: string | null
    /** DetectPipelineNode 的检测编号（对外引用 id，可空 = 用文件名）；其他树为空 */
    detect_id?: string
    /** 适用场景（DetectPipelineNode），挑流程时辅助辨识；其他树为空 */
    scene?: string
  } | null
  error: string | null
}

export interface DetectTreeDetail {
  rel_path: string
  spec: Record<string, any>
}

/** 算法目录条目（`data/algorithms.json`，与航点树那份是同一份数据） */
export interface AlgorithmItem {
  id: string
  name: string
  category: string
  color: string
  description: string
  image: string
}

const BASE = '/api/detect-prefab'

/**
 * 检测流程树的节点类型（只含 `DetectNodeBase` 子类）。
 *
 * ⚠️ 与航点树的 `/api/waypoint-prefab/node-types`、计划树的
 * `/api/plan-prefab/node-types` **不是同一份**：后端按中间基类过滤，
 * 三棵树的类型目录互不串门。前端各拉各的，别图省事共用。
 */
export const getDetectNodeTypes = () =>
  http.get<Record<string, NodeTypeInfo>>(`${BASE}/node-types`)

export const listDetectTrees = () =>
  http.get<{ trees: DetectTreeSummary[]; dirs: string[] }>(`${BASE}/trees`)

export const getDetectTree = (relPath: string) =>
  http.get<DetectTreeDetail>(`${BASE}/tree`, { params: { rel_path: relPath } })

/**
 * 覆盖保存一棵检测流程树。
 *
 * ⚠️ body 的键是 **`spec`**（不是 `tree`）；且该接口**不创建文件**，
 * 文件不存在会 404 —— 新建必须先调 `createDetectFile`。
 */
export const saveDetectTree = (relPath: string, spec: Record<string, any>) =>
  http.post<{ ok: boolean; rel_path: string }>(`${BASE}/tree`, { rel_path: relPath, spec })

export const createDetectFile = (relPath: string) =>
  http.post<{ ok: boolean; rel_path: string }>(`${BASE}/files`, { rel_path: relPath })

export const deleteDetectFile = (relPath: string) =>
  http.delete(`${BASE}/files`, { data: { rel_path: relPath } })

export const createDetectDir = (relPath: string) =>
  http.post(`${BASE}/dirs`, { rel_path: relPath })

export const deleteDetectDir = (relPath: string) =>
  http.delete(`${BASE}/dirs`, { data: { rel_path: relPath } })

export const renameDetectEntry = (relPath: string, newName: string) =>
  http.post(`${BASE}/rename`, { rel_path: relPath, new_name: newName })

export const moveDetectEntry = (relPath: string, destDir: string) =>
  http.post(`${BASE}/move`, { rel_path: relPath, dest_dir: destDir })

/**
 * 算法目录（给「算法检测」节点的下拉用）。
 *
 * 与 `/api/waypoint-prefab/algorithms` 是**同一份 `data/algorithms.json`**：
 * 检测框能选的算法和检测流程里能选的必须是同一批，否则同一个算法在两棵树里
 * 会选出不一样的 id。
 */
export const getDetectAlgorithms = () =>
  http.get<{ ok: boolean; algorithms: AlgorithmItem[]; warning?: string }>(`${BASE}/algorithms`)

/** 算法推理服务可选算法条目（`data/panel_list.json`），给 MeterAlgorithmNode 用 */
export interface PanelItem {
  id: number | null
  /** name 编码（如 1_0_0_1_53_0），提交推理时作为 boxs[].name */
  name: string
  display_name: string
}

/**
 * 算法推理服务可选算法清单（给「MeterAlgorithmNode」的算法类型下拉用）。
 * 该节点用于兼容现有算法推理服务，选中后存 name 编码。
 */
export const getDetectPanelList = () =>
  http.get<{ ok: boolean; panels: PanelItem[]; warning?: string }>(`${BASE}/panel-list`)
