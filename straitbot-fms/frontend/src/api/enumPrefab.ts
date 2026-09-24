import http from './http'
import type { NodeTypeInfo } from './prefab'

/** 枚举文件摘要（与航点树 / 计划树 / 检测流程同形，接口由后端 prefab_store 工厂生成） */
export interface EnumTreeSummary {
  rel_path: string
  name: string
  root: {
    type: string | null
    name: string | null
    detect_id?: string
    scene?: string
  } | null
  error: string | null
}

export interface EnumTreeDetail {
  rel_path: string
  spec: Record<string, any>
}

/** 一个下拉选项：`value` 是存库的值，`label` 是显示名 */
export interface EnumOption {
  value: string
  label: string
  description?: string
}

/**
 * 一份枚举的查询结果。
 *
 * ⚠️ `found` 与 `options` 非空是**两件事**：`found=true` 只说明目录里有这个
 * key 的 EnumNode，配了但一项都没填时 `options` 就是空数组。消费方据此区分
 * 「没配过」（可回落到库里实际出现过的值）与「配了但为空」（就该是空的）。
 */
export interface EnumOptionsResult {
  ok: boolean
  key: string
  found: boolean
  options: EnumOption[]
  sources: string[]
}

export interface EnumKeySummary {
  key: string
  label: string
  count: number
  file: string
}

const BASE = '/api/enum-prefab'

/**
 * 枚举树的节点类型（只含 `EnumNodeBase` 子类：EnumNode / EnumItemNode）。
 *
 * ⚠️ 与另外三棵树的 `node-types` **不是同一份**：后端按中间基类过滤，
 * 四棵树的类型目录互不串门。前端各拉各的，别图省事共用。
 */
export const getEnumNodeTypes = () =>
  http.get<Record<string, NodeTypeInfo>>(`${BASE}/node-types`)

export const listEnumTrees = () =>
  http.get<{ trees: EnumTreeSummary[]; dirs: string[] }>(`${BASE}/trees`)

export const getEnumTree = (relPath: string) =>
  http.get<EnumTreeDetail>(`${BASE}/tree`, { params: { rel_path: relPath } })

/**
 * 覆盖保存一棵枚举树。
 *
 * ⚠️ body 的键是 **`spec`**（不是 `tree`）；且该接口**不创建文件**，
 * 文件不存在会 404 —— 新建必须先调 `createEnumFile`。
 */
export const saveEnumTree = (relPath: string, spec: Record<string, any>) =>
  http.post<{ ok: boolean; rel_path: string }>(`${BASE}/tree`, { rel_path: relPath, spec })

export const createEnumFile = (relPath: string) =>
  http.post<{ ok: boolean; rel_path: string }>(`${BASE}/files`, { rel_path: relPath })

export const deleteEnumFile = (relPath: string) =>
  http.delete(`${BASE}/files`, { data: { rel_path: relPath } })

export const createEnumDir = (relPath: string) =>
  http.post(`${BASE}/dirs`, { rel_path: relPath })

export const deleteEnumDir = (relPath: string) =>
  http.delete(`${BASE}/dirs`, { data: { rel_path: relPath } })

export const renameEnumEntry = (relPath: string, newName: string) =>
  http.post(`${BASE}/rename`, { rel_path: relPath, new_name: newName })

export const moveEnumEntry = (relPath: string, destDir: string) =>
  http.post(`${BASE}/move`, { rel_path: relPath, dest_dir: destDir })

/**
 * 取一份枚举的选项（下拉框用），如 `getEnumOptions('告警类型')`。
 *
 * 这是**下拉框唯一的取数入口**：消费方（告警中心）不该知道枚举存在哪个文件、
 * 节点挂在第几层。目录缺失 / 文件损坏时后端返回 `found=false` + 空选项，
 * 不 500 —— 调用方要准备回落方案。
 */
export const getEnumOptions = (key: string) =>
  http.get<EnumOptionsResult>(`${BASE}/options`, { params: { key } })

/** 目录里全部枚举的键（有哪些枚举可引用） */
export const getEnumKeys = () =>
  http.get<{ ok: boolean; keys: EnumKeySummary[] }>(`${BASE}/keys`)
