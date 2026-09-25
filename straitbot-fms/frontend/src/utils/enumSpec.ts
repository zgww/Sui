/**
 * 枚举树（`data/prefabs/枚举`）的纯逻辑：类型中文名 / 配色 / 摘要 / 选项提取。
 *
 * ⚠️ **本文件不引 Semi、不引图标**（与 `detectSelect.ts` 同一条规矩）：
 * 它会被 `scripts/verify-*.mjs` 直接用 Node 原生 ESM 编译执行，而
 * `@douyinfe/semi-icons` 在那种环境里加载不了（ES 产物是裸相对导入、
 * CJS 产物 require 了 .css），一引进来整个脚本连编译都过不去。
 * 要图标就另开一个 `.tsx`（范例 `detectSelectIcons.tsx`）。
 *
 * 页面只负责接线与渲染，判断规则一律放这里——尤其是"哪些项能进下拉框"，
 * 前端的展示与后端 `prefab/enum_catalog.py` 的口径**必须一致**，否则树上
 * 看得见的项在下拉框里点不到（或反过来）。
 */
import { SEP, parentPathOf } from './trackSpec'
import { getNodeByPath } from './specTree'

export const ENUM_NODE_TYPE = 'EnumNode'
export const ENUM_ITEM_TYPE = 'EnumItemNode'

/** 节点类型中文名（树上 Tag 与空态提示用） */
export const ENUM_TYPE_LABEL: Record<string, string> = {
  [ENUM_NODE_TYPE]: '枚举',
  [ENUM_ITEM_TYPE]: '枚举项',
}

/** 树上类型 Tag 的配色。`any` 是为了直接喂给 Semi `Tag.color`（它的 TagColor 是字面量联合） */
export const ENUM_TYPE_COLOR: Record<string, any> = {
  [ENUM_NODE_TYPE]: 'violet',
  [ENUM_ITEM_TYPE]: 'light-blue',
}

export function enumTypeLabel(type: string): string {
  return ENUM_TYPE_LABEL[type] || type || '未知类型'
}

export interface EnumOption {
  value: string
  label: string
  description: string
}

/* ------------------------------------------------------------ 选项提取 */

/**
 * 一个 `EnumNode` 的直接 `EnumItemNode` 子节点 -> 选项列表。
 *
 * 三条过滤与后端 `enum_catalog.options_of` **逐条对齐**，别只改一边：
 * - `enabled=false` 的项跳过（那是"暂时停用"，不是"停用但仍显示"）；
 * - `name` 为空的项跳过（没有键的选项筛不出东西，留着只会多一条空行）；
 * - `label` 为空时回落 `name`（前端拿到的一定有显示文本）。
 */
export function enumOptionsOf(node: any): EnumOption[] {
  const out: EnumOption[] = []
  for (const c of (node?.children || []) as any[]) {
    if (c?.type !== ENUM_ITEM_TYPE) continue
    const p = c.properties || {}
    if (p.enabled === false) continue
    const name = String(p.name || '').trim()
    if (!name) continue
    out.push({
      value: name,
      label: String(p.label || '').trim() || name,
      description: String(p.description || ''),
    })
  }
  return out
}

/**
 * 一个 `EnumNode` 的对外键：`name` 优先，没写时退回文件名。
 *
 * 与后端 `_key_of` 同一套口径：新建文件后用户常常先在树上加项、忘了填 name，
 * 这时按文件名还能取到（页面新建时已把 name 预填成文件名，多数情况两者一致）。
 */
export function enumKeyOf(node: any, fileStem = ''): string {
  const p = node?.properties || {}
  return String(p.name || '').trim() || fileStem
}

/** 深度优先遍历整棵树（含 root 自己） */
export function walkEnumTree(root: any): any[] {
  const acc: any[] = []
  const go = (n: any) => {
    if (!n || typeof n !== 'object') return
    acc.push(n)
    for (const c of (n.children || []) as any[]) go(c)
  }
  go(root)
  return acc
}

/**
 * 从一份 spec 里按 key 取选项（**页面内的即时预览**用）。
 *
 * 真正的下拉框走接口 `/api/enum-prefab/options`（后端读全目录，能跨文件命中）；
 * 这里是"当前打开的这一份文件"的即时结果，用来在页面上直接告诉用户
 * "这份配置现在能给出几个选项"，不必先保存再刷下拉框。
 *
 * @returns `found` = 这份 spec 里有没有该 key 的 EnumNode（与 options 是否
 *   非空是两件事：配了但没填项时 found=true 而 options=[]）
 */
export function findEnumOptions(spec: any, key: string, fileStem = ''): {
  found: boolean
  options: EnumOption[]
} {
  const k = String(key || '').trim()
  if (!k) return { found: false, options: [] }
  const options: EnumOption[] = []
  const seen = new Set<string>()
  let found = false
  for (const n of walkEnumTree(spec?.root)) {
    if (n?.type !== ENUM_NODE_TYPE) continue
    if (enumKeyOf(n, fileStem) !== k) continue
    found = true
    for (const opt of enumOptionsOf(n)) {
      if (seen.has(opt.value)) continue // 同 key 多份：按值去重，保首次顺序
      seen.add(opt.value)
      options.push(opt)
    }
  }
  return { found, options }
}

/** 选项 -> Semi `Select` 的 optionList（`label` 一定非空，见 `enumOptionsOf`） */
export function toOptionList(options: EnumOption[]): { value: string; label: string }[] {
  return options.map((o) => ({ value: o.value, label: o.label }))
}

/* ------------------------------------------------------------ 展示 */

/** 树上节点标签：`label` 优先（显示名），没写才回落到 `name`（键） */
export function enumNodeLabel(node: any): string {
  const p = node?.properties || {}
  return String(p.label || '').trim() || String(p.name || '').trim() || enumTypeLabel(node?.type)
}

/** 树上跟在标签后面的补充信息（枚举=项数，枚举项=与显示名不同的键） */
export function enumNodeSummary(node: any): string {
  if (node?.type === ENUM_NODE_TYPE) {
    const n = enumOptionsOf(node).length
    return n ? `${n} 项` : ''
  }
  if (node?.type === ENUM_ITEM_TYPE) {
    const p = node.properties || {}
    const name = String(p.name || '').trim()
    const label = String(p.label || '').trim()
    // 显示名就是键时不再重复一遍（Tag 里放一模一样的两个字是噪声）
    return name && (!label || label === name) ? '' : name
  }
  return ''
}

/* ------------------------------------------------------------ 结构操作 */

/**
 * 往 `parentPath` 的子级末尾追加一个节点（原地改 spec）。
 *
 * `spec` 是**整份 spec 对象**（`{name, root}`），不是 root 节点——路径以
 * `root` 开头，`getNodeByPath` 认的是这个形状，与另外三棵树一致。
 */
export function appendChildNode(spec: any, parentPath: string, node: any): boolean {
  const parent = getNodeByPath(spec, parentPath)
  if (!parent) return false
  parent.children = Array.isArray(parent.children) ? parent.children : []
  parent.children.push(node)
  return true
}

/**
 * 在 `path` 的前 / 后插入一个**同级**节点（原地改 spec）。
 *
 * `path === 'root'` 时必然失败：根没有同级可言，别静默改成一个"看起来成功了
 * 其实没动"的结果——调用方要据此提示用户。
 */
export function insertSiblingNode(spec: any, path: string, node: any,
  where: 'before' | 'after'): boolean {
  if (!spec || path === 'root') return false
  const parent = getNodeByPath(spec, parentPathOf(path))
  const idx = Number(path.split(SEP).pop())
  if (!parent || !Array.isArray(parent.children)) return false
  if (!Number.isInteger(idx) || idx < 0 || idx > parent.children.length) return false
  parent.children.splice(where === 'before' ? idx : idx + 1, 0, node)
  return true
}

/** 从节点 schema 取一份默认属性（与另外三棵树同款：跳过 type / children） */
export function defaultsFrom(schema: any): Record<string, any> {
  const out: Record<string, any> = {}
  for (const [k, d] of Object.entries<any>(schema?.properties || {})) {
    if (k === 'type' || k === 'children') continue
    if ('default' in d) out[k] = d.default
  }
  return out
}
