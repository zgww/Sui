/**
 * spec 树的结构操作 + 拖拽落点计算 —— **纯函数，无 React 依赖**。
 *
 * ## 为什么抽出来
 *
 * 拖拽落点是最容易写错又最难肉眼发现的逻辑：错了不报错，只是"节点插到了隔壁"。
 * 这两个坑都踩过：
 *
 * 1. **Semi 的 `dropPosition` 不是方向**。onDrop 里拿到的是
 *    `calcDropActualPosition(pos, rel)` = `rel(-1/0/1) + 目标在同级中的下标`，
 *    也就是**同级绝对下标**；方向信息在 `dropToGap` + 差值里。
 *    直接写 `dropPosition < 0 ? 'before' : 'after'`，只有目标是同级第一个节点时
 *    才成立（0 + (-1) = -1），其余全部被误判成 'after' —— 表现为
 *    "我要插到 A 前面，结果插到了 A 后面"。
 * 2. **同一棵树里两套下标**：摘除节点后兄弟下标会前移，插入点必须按"摘除前"
 *    的位置算完再修正，否则同父内移动会差一位。
 *
 * 这些规则必须能被回归脚本直接验证，不能埋在组件的事件处理器里。
 */
import { SEP, parentPathOf } from './trackSpec'

export { SEP, parentPathOf }

/** 路径 -> 节点。路径形如 `root/children/0/children/2` */
export function getNodeByPath(spec: any, path: string): any {
  let cur: any = spec
  for (const p of path.split(SEP)) {
    if (cur === undefined || cur === null) return undefined
    cur = cur[p]
  }
  return cur
}

export function isAncestorPath(ancestorPath: string, path: string): boolean {
  return path === ancestorPath || path.startsWith(ancestorPath + SEP)
}

/** 路径集合 -> 顶层（去掉是集合内其他路径祖先的项），保持顺序 */
export function topLevelPaths(paths: string[]): string[] {
  const sorted = [...paths].sort((a, b) => a.length - b.length)
  const kept: string[] = []
  for (const p of sorted) {
    if (!kept.some((k) => p !== k && p.startsWith(k + SEP))) kept.push(p)
  }
  return kept
}

/* ------------------------------------------------------------ 落点判定 */

/** 拖拽落点：on 目标节点内部（成为其首个子节点）/ before 目标之前 / after 目标之后 */
export type DropKind = 'on' | 'before' | 'after'

export interface MoveResult { ok: boolean; reason?: string }

/** Semi Tree onDrop 回调参数的形状（只取用得到的字段） */
export interface DropEventLike {
  dragNode?: { key?: string; pos?: string } | null
  node?: { key?: string; pos?: string } | null
  dropPosition?: number | null
  dropToGap?: boolean
}

/**
 * 目标节点在同级中的下标。
 *
 * 优先用 Semi 给的 `node.pos`（形如 `0-1-2`，最后一段就是同级下标），
 * 拿不到时退回从 key 里取——本页 key 就是路径，同样以 `/children/N` 结尾。
 * 都拿不到返回 null，调用方按"落在节点上"处理。
 */
function targetSiblingIndex(props: DropEventLike): number | null {
  const pos = props?.node?.pos
  if (typeof pos === 'string' && pos) {
    const n = Number(pos.split('-').pop())
    if (Number.isInteger(n)) return n
  }
  const key = String(props?.node?.key ?? '')
  if (key && key !== 'root') {
    const n = Number(key.split(SEP).pop())
    if (Number.isInteger(n)) return n
  }
  return null
}

/**
 * onDrop 参数 -> 落点语义。
 *
 * 核心：`dropPosition` 是**绝对下标**，要用它减去目标下标还原出方向
 * （-1 前 / 0 上 / 1 后）。见文件头。
 */
export function resolveDropKind(props: DropEventLike | undefined | null): DropKind {
  if (!props || !props.dropToGap) return 'on'
  const targetIdx = targetSiblingIndex(props)
  const raw = Number(props.dropPosition)
  if (targetIdx === null || !Number.isFinite(raw)) return 'on'
  const rel = raw - targetIdx
  if (rel === 0) return 'on'
  return rel < 0 ? 'before' : 'after'
}

/* ------------------------------------------------------------ 移动 */

/**
 * 移动单个节点。
 *
 * 落点用 `DropKind` 表达（由 `resolveDropKind` 从 Semi 事件里还原），
 * 不再在移动逻辑里碰 `dropPosition` 这种"半个方向半个下标"的量。
 */
export function moveNodeInSpec(
  root: any,
  dragPath: string,
  targetPath: string,
  kind: DropKind,
): MoveResult {
  if (dragPath === targetPath) return { ok: false, reason: '拖拽节点与目标节点相同' }
  if (isAncestorPath(dragPath, targetPath)) {
    return { ok: false, reason: '不能把节点拖入它自己的子孙节点' }
  }
  if (kind === 'on' && dragPath === 'root') {
    return { ok: false, reason: '根节点不能作为被拖动节点' }
  }

  const dp = dragPath.split(SEP)
  const dragParentPath = dp.slice(0, -2).join(SEP)
  const dragIdx = Number(dp[dp.length - 1])
  const dragParent = getNodeByPath({ root }, dragParentPath)
  if (!dragParent?.children || !Number.isInteger(dragIdx)
    || dragIdx < 0 || dragIdx >= dragParent.children.length) {
    return { ok: false, reason: '拖拽节点已失效，请刷新后重试' }
  }

  // 先把节点摘出来，失败时再原样放回，保证 spec 不被改坏
  const [moved] = dragParent.children.splice(dragIdx, 1)
  const rollback = () => { dragParent.children.splice(dragIdx, 0, moved) }

  if (kind === 'on') {
    const target = getNodeByPath({ root }, targetPath)
    if (!target) { rollback(); return { ok: false, reason: '目标节点不存在' } }
    target.children = target.children || []
    target.children.unshift(moved)
    return { ok: true }
  }

  const targetParentPath = parentPathOf(targetPath)
  const targetIdx = Number(targetPath.split(SEP).pop())
  const targetParent = getNodeByPath({ root }, targetParentPath)
  if (!targetParent?.children) { rollback(); return { ok: false, reason: '目标节点的父级不存在' } }

  // 同父内移动：摘除后目标下标可能前移
  let insertIdx = kind === 'before' ? targetIdx : targetIdx + 1
  if (dragParentPath === targetParentPath && dragIdx < insertIdx) insertIdx -= 1
  insertIdx = Math.max(0, Math.min(insertIdx, targetParent.children.length))
  if (dragParentPath === targetParentPath && insertIdx === dragIdx) {
    rollback()
    return { ok: false, reason: '位置未发生变化' }
  }
  targetParent.children.splice(insertIdx, 0, moved)
  return { ok: true }
}

/**
 * 批量移动同父的多个节点，落到目标节点内部（on）或前后间隙（before/after）。
 *
 * 要求选中节点同父：不同父的节点索引语义不在一套坐标系里，插序会产生歧义，
 * 这种情况直接拒绝并提示，避免"看起来动了其实顺序乱掉"。
 */
export function batchMoveNodes(
  root: any,
  paths: string[],
  targetPath: string,
  kind: DropKind,
): MoveResult {
  const tops = topLevelPaths(paths)
    .filter((p) => p !== 'root' && p !== targetPath && !isAncestorPath(p, targetPath))
  if (!tops.length) return { ok: false, reason: '没有可移动的节点' }
  if (tops.length !== topLevelPaths(paths).filter((p) => p !== 'root').length) {
    return { ok: false, reason: '不能把节点拖入它自己的子孙节点' }
  }

  const parents = new Set(tops.map(parentPathOf))
  if (parents.size !== 1) {
    return { ok: false, reason: '批量拖动要求选中的节点在同一父级下' }
  }
  const fromParentPath = [...parents][0]
  const fromParent = getNodeByPath({ root }, fromParentPath)
  if (!fromParent?.children) return { ok: false, reason: '源父级不存在' }
  if (kind === 'on' && fromParentPath === targetPath) {
    return { ok: false, reason: '这些节点已经在目标节点内了' }
  }

  // 目标位置必须在摘除之前解析完，之后下标会位移
  let destParentPath: string
  let baseIdx: number
  if (kind === 'on') {
    const target = getNodeByPath({ root }, targetPath)
    if (!target) return { ok: false, reason: '目标节点不存在' }
    destParentPath = targetPath
    baseIdx = 0
  } else {
    const targetParent = getNodeByPath({ root }, parentPathOf(targetPath))
    if (!targetParent?.children) return { ok: false, reason: '目标节点的父级不存在' }
    destParentPath = parentPathOf(targetPath)
    const targetIdx = Number(targetPath.split(SEP).pop())
    baseIdx = kind === 'before' ? targetIdx : targetIdx + 1
  }

  // 同父内移动时，被摘除的节点若都在插入点之前，插入点要整体前移
  const pickedIdx = tops.map((p) => Number(p.split(SEP).pop()))
  if (fromParentPath === destParentPath) {
    const beforeCount = pickedIdx.filter((i) => i < baseIdx).length
    baseIdx -= beforeCount
    if (kind === 'before' || kind === 'after') {
      const alreadyInPlace = pickedIdx.length === 1 && pickedIdx[0] === baseIdx
      if (alreadyInPlace) return { ok: false, reason: '位置未发生变化' }
    }
  }
  const destParent = fromParentPath === destParentPath ? fromParent : getNodeByPath({ root }, destParentPath)
  if (!destParent?.children) return { ok: false, reason: '目标父级不存在' }

  // 按原顺序取出，保证多选节点相对次序不变
  const picked = tops
    .map((p, order) => ({ order, idx: Number(p.split(SEP).pop()) }))
    .sort((a, b) => b.idx - a.idx)
    .map(({ order, idx }) => ({ order, node: fromParent.children.splice(idx, 1)[0] }))
    .sort((a, b) => a.order - b.order)
    .map((x) => x.node)
  if (picked.some((n) => !n)) return { ok: false, reason: '拖拽节点已失效，请刷新后重试' }

  destParent.children = destParent.children || []
  const insertAt = Math.max(0, Math.min(baseIdx, destParent.children.length))
  destParent.children.splice(insertAt, 0, ...picked)
  return { ok: true }
}

/**
 * 批量删除多个节点（自动顶层化、排除 root）。
 * 关键：按父级分组、组内按索引从大到小 splice，避免删掉一个后兄弟索引前移
 * 导致同父多选时漏删/错删。返回实际删除数量。
 */
export function removeManyByPaths(root: any, paths: string[]): number {
  const tops = topLevelPaths(paths).filter((p) => p !== 'root')
  const groups = new Map<string, number[]>()
  for (const p of tops) {
    const pp = parentPathOf(p)
    const idx = Number(p.split(SEP).pop())
    if (!groups.has(pp)) groups.set(pp, [])
    groups.get(pp)!.push(idx)
  }
  let removed = 0
  for (const [pp, idxs] of groups) {
    const parent = getNodeByPath({ root }, pp)
    if (!parent?.children) continue
    for (const idx of idxs.sort((a, b) => b - a)) {
      if (idx >= 0 && idx < parent.children.length) {
        parent.children.splice(idx, 1)
        removed += 1
      }
    }
  }
  return removed
}
