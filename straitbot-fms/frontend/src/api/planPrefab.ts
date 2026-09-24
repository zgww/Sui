import http from './http'
import type { NodeTypeInfo } from './prefab'

/** 计划树文件摘要（与航点树同形，接口由后端 prefab_store 工厂生成） */
export interface PlanTreeSummary {
  rel_path: string
  name: string
  root: { type: string | null; name: string | null } | null
  error: string | null
}

export interface PlanTreeDetail {
  rel_path: string
  spec: Record<string, any>
}

const BASE = '/api/plan-prefab'

/**
 * 计划树的节点类型（只含 `PlanNodeBase` 子类）。
 *
 * ⚠️ 与航点树的 `/api/waypoint-prefab/node-types` **不是同一份**：后端按
 * 中间基类过滤，两棵树的类型目录互不串门。前端两处都拉各自的，别图省事共用。
 */
export const getPlanNodeTypes = () =>
  http.get<Record<string, NodeTypeInfo>>(`${BASE}/node-types`)

export const listPlanTrees = () =>
  http.get<{ trees: PlanTreeSummary[]; dirs: string[] }>(`${BASE}/trees`)

export const getPlanTree = (relPath: string) =>
  http.get<PlanTreeDetail>(`${BASE}/tree`, { params: { rel_path: relPath } })

/**
 * 覆盖保存一棵计划树。
 *
 * ⚠️ body 的键是 **`spec`**（不是 `tree`）；且该接口**不创建文件**，
 * 文件不存在会 404 —— 新建必须先调 `createPlanFile`。
 */
export const savePlanTree = (relPath: string, spec: Record<string, any>) =>
  http.post<{ ok: boolean; rel_path: string }>(`${BASE}/tree`, { rel_path: relPath, spec })

export const createPlanFile = (relPath: string) =>
  http.post<{ ok: boolean; rel_path: string }>(`${BASE}/files`, { rel_path: relPath })

export const deletePlanFile = (relPath: string) =>
  http.delete(`${BASE}/files`, { data: { rel_path: relPath } })

export const createPlanDir = (relPath: string) =>
  http.post(`${BASE}/dirs`, { rel_path: relPath })

export const deletePlanDir = (relPath: string) =>
  http.delete(`${BASE}/dirs`, { data: { rel_path: relPath } })

export const renamePlanEntry = (relPath: string, newName: string) =>
  http.post(`${BASE}/rename`, { rel_path: relPath, new_name: newName })

export const movePlanEntry = (relPath: string, destDir: string) =>
  http.post(`${BASE}/move`, { rel_path: relPath, dest_dir: destDir })

/**
 * 「立即执行」的结果。
 *
 * ⚠️ **业务拒绝也是 200**：机器人忙（`busy`）、计划没挑到航点、机器人对不上……
 * 这些都由后端返回 `accepted: false` + `reason`，**不是** HTTP 错误码。
 * 所以调用方必须看 `accepted` 而不是只看有没有抛异常——用 4xx 的话 http
 * 拦截器会先弹一个通用提示，反而盖住后端给的具体原因。
 */
export interface ExecutePlanResult {
  accepted: boolean
  /** `accepted=false` 时的原因（`busy` / `没有可用的机器人实例…` / …） */
  reason?: string
  rel_path: string
  node_path: string
  plan_key?: string
  plan_name?: string
  inspection_id?: string
  floors?: number[]
  detect_type?: string
  waypoint_count?: number
  action_count?: number
  /** 机器人忙时告诉你是哪一次巡检还没跑完 */
  current_inspection_id?: string | null
}

/**
 * **立即执行**一条「巡检计划」：现在就把这条计划下发给机器人，不等排期。
 *
 * ⚠️ 执行的是**磁盘上的文件**，不是编辑器里的内存态：前端没保存的改动不会被跑。
 * 想跑新改的内容，先点「保存」。
 *
 * ⚠️ 这是**会动真格设备**的接口（机器人会出发），后端限 `engineer`。
 */
export const executePlanNow = (relPath: string, nodePath: string) =>
  http.post<ExecutePlanResult>(`${BASE}/execute`,
    { rel_path: relPath, node_path: nodePath })
