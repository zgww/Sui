/**
 * 「从目录/树里挑一批东西」的**通用**纯函数 —— 无 React 依赖，可被回归脚本直接编译后 import。
 *
 * 两个挑选面板共用它（`waypointPick` 挑航点、`pointPick` 挑测点），
 * 因为它们要的手势完全一样，只有"节点从哪来"不同：
 * 点选切换、Shift 按**可见顺序**整段加选、Alt 移除、地图框选回写。
 *
 * ## 为什么 key 与 path 是**两个**东西
 *
 * - `key` 是写进 `waypoint_ids` / `point_ids` 的**业务引用**（`wp_id`、测点 id）；
 * - `path` 是这棵树里的**唯一位置**（Semi Tree 的 React key、范围选的坐标）。
 *
 * 分开是因为业务 id 在脏数据里可能重复（两个航点共用一个 `wp_id`），
 * 拿它当 React key 会撞、当范围区间会"选了一个另一个跟着亮"。
 * 路径一定唯一，所以**范围选一律走 path，最后一步才换成 key**。
 *
 * ## 顺序即语义
 *
 * 合并一律**保持原顺序、新增的排到末尾**（`waypoint_ids` 是数组，顺序有含义），
 * 所以不能用 `Set` 直接当返回值——`applyPickMode` 那种给地图用的才用 Set。
 */
import type { PickMode } from './marqueeSelect'

/** 树视图里的一个节点：分组（可展开）或叶子（可挑选） */
export interface PickNode<T = unknown> {
  /** 写进 `*_ids` 的值（叶子才有意义；分组用不到，但也给个唯一值便于排查） */
  key: string
  /** 显示名 */
  label: string
  /** 树内唯一路径（React key / 范围选坐标） */
  path: string
  isLeaf: boolean
  /** 叶子带的数据（航点摘要 / 测点摘要…） */
  data?: T
  children?: PickNode<T>[]
}

/* ------------------------------------------------------------ 查询 */

/**
 * 关键字过滤。
 *
 * 规则：
 * - **叶子**：标签 / key / 路径 / `extra(n)`（额外可搜索文本，例如测点编号）任一命中；
 * - **分组**：只看自己的标签。命中就把**整枝**留下（搜"出线间隔"要能看到它下面
 *   的所有测点——大档案里这是最常用的一条路）；
 * - 分组没命中但子孙有命中的，保留这条祖先链。
 *
 * @param extra 额外的可搜索文本（只对叶子调用；返回空串表示没有）
 */
export function filterPickTree<T>(
  nodes: PickNode<T>[],
  kw: string,
  extra?: (n: PickNode<T>) => string,
): PickNode<T>[] {
  const k = String(kw || '').trim().toLowerCase()
  if (!k) return nodes
  const walk = (list: PickNode<T>[], keepAll: boolean): PickNode<T>[] => list.flatMap((n) => {
    if (n.isLeaf) {
      if (keepAll) return [n]
      const hay = `${n.label} ${n.key} ${n.path} ${extra?.(n) || ''}`.toLowerCase()
      return hay.includes(k) ? [n] : []
    }
    // 分组自己命中 -> 整枝原样保留
    if (keepAll || String(n.label).toLowerCase().includes(k)) return [{ ...n }]
    const children = walk(n.children || [], false)
    return children.length ? [{ ...n, children }] : []
  })
  return walk(nodes, false)
}

/** 所有分组节点的 key（"全部展开"用） */
export function expandableKeys(nodes: PickNode<any>[]): string[] {
  const out: string[] = []
  const walk = (list: PickNode<any>[]) => {
    for (const n of list) {
      if (n.isLeaf) continue
      out.push(n.key)
      walk(n.children || [])
    }
  }
  walk(nodes)
  return out
}

/** 所有叶子（树中顺序，与树视图从上到下一致） */
export function leavesOf<T>(nodes: PickNode<T>[]): PickNode<T>[] {
  const out: PickNode<T>[] = []
  const walk = (list: PickNode<T>[]) => {
    for (const n of list) {
      if (n.isLeaf) out.push(n)
      else walk(n.children || [])
    }
  }
  walk(nodes)
  return out
}

/** `path → 节点` 与 `path → 叶子数` 两个索引（渲染树行时按 path 回查） */
export function indexPickTree(nodes: PickNode<any>[]): {
  index: Map<string, PickNode<any>>
  counts: Map<string, number>
} {
  const index = new Map<string, PickNode<any>>()
  const counts = new Map<string, number>()
  const count = (n: PickNode<any>): number => {
    const c = n.isLeaf ? 1 : (n.children || []).reduce((s, k) => s + count(k), 0)
    counts.set(n.path, c)
    return c
  }
  nodes.forEach(count)
  const walk = (list: PickNode<any>[]) => {
    for (const n of list) {
      index.set(n.path, n)
      if (!n.isLeaf) walk(n.children || [])
    }
  }
  walk(nodes)
  return { index, counts }
}

/** `path → key` 映射（地图回传的是路径集合，要换算成业务 id） */
export function keyByPath(nodes: PickNode<any>[]): Record<string, string> {
  const out: Record<string, string> = {}
  for (const n of leavesOf(nodes)) out[n.path] = n.key
  return out
}

/* ------------------------------------------------------------ 分组勾选 */

/**
 * 一个节点（含自身）下的**全部叶子 key**，树中顺序、**按 key 去重**。
 *
 * 去重是必须的：两个叶子可能共用同一个业务 id（`wp_id` 重复），那时选了一个
 * 等于两个都选上了，`total` 计成 2 的话这个分组**永远到不了"全选"**——
 * 勾满了看上去还是半选，用户会以为点击没生效。
 */
export function leafKeysOf<T>(n: PickNode<T>): string[] {
  const out: string[] = []
  const seen = new Set<string>()
  const walk = (x: PickNode<T>) => {
    if (x.isLeaf) {
      if (!seen.has(x.key)) { seen.add(x.key); out.push(x.key) }
      return
    }
    for (const c of x.children || []) walk(c)
  }
  walk(n)
  return out
}

/** 一个分组的勾选态：`none` 没选 / `part` 半选 / `all` 全选 */
export type GroupPickState = 'none' | 'part' | 'all'

/** 分组的勾选概况（半选要不要显示、行尾"已选 2/5 个"怎么用都看它） */
export interface GroupPickInfo {
  state: GroupPickState
  /** 已选中的叶子 key 数（去重后） */
  hit: number
  /** 子树里一共有多少个叶子 key（去重后） */
  total: number
}

/**
 * 分组的勾选概况。
 *
 * 叶子也接受（当作只有一个元素的分组），这样组件里不用分两路写。
 *
 * **空分组（`total === 0`）一律 `none`**：测点档案里刚建好还没放测点的目录是
 * 正常状态，它既不是"没勾"也不是"勾了一半"，点它也不该有任何反应
 * （下面 `groupToggleMode` 因此返回 `null`）。
 */
export function groupPickInfo<T>(n: PickNode<T>, picked: Set<string>): GroupPickInfo {
  const keys = leafKeysOf(n)
  let hit = 0
  for (const k of keys) if (picked.has(k)) hit++
  const state: GroupPickState = hit === 0 ? 'none' : (hit === keys.length ? 'all' : 'part')
  return { state, hit, total: keys.length }
}

/**
 * 点分组的勾选框该做什么：`add`（整枝加上）/ `remove`（整枝去掉）/ `null`（什么都不做）。
 *
 * - 已经全选了 -> 取消（这是勾选框的通用习惯，也是"再点一次能撤回"）；
 * - 没选或半选 -> 全加上。**不能用 `replace`**：那是"整份选择换成这一枝"，
 *   会把别的分组挑好的东西一起清掉，而且没有任何提示；
 * - 空分组 -> `null`。
 *
 * 调用方按修饰键覆盖：Shift = `add`、Alt = `remove`（与叶子行的手势一致）。
 */
export function groupToggleMode<T>(n: PickNode<T>, picked: Set<string>): PickMode | null {
  const { state, total } = groupPickInfo(n, picked)
  if (total === 0) return null
  return state === 'all' ? 'remove' : 'add'
}

/**
 * **当前可见**的叶子**路径**顺序（折叠的分组不展开，它的叶子不算"看得见"）。
 *
 * Shift 范围选择必须按这个顺序取区间，而不是按整棵树的顺序：用户按下 Shift 时
 * 看到的就是这些行，如果区间把折叠分组里藏着的项也划进来，他会发现
 * "我明明只框了三行，怎么勾了十几个"。
 */
export function flattenPickTree(nodes: PickNode<any>[], expanded: Iterable<string>): string[] {
  const open = new Set(expanded)
  const out: string[] = []
  const walk = (list: PickNode<any>[]) => {
    for (const n of list) {
      if (n.isLeaf) { out.push(n.path); continue }
      if (open.has(n.key)) walk(n.children || [])
    }
  }
  walk(nodes)
  return out
}

/* ------------------------------------------------------------ 范围选 */

/**
 * Shift 范围：`anchor`（上次点的）到 `target`（这次点的）之间的**全部可见路径**，含两端。
 *
 * - `anchor` 缺失或已经不在可见列表里（换了筛选条件、折叠了分组）时**退化成只选
 *   `target`**——绝不能"按下标硬取"，那样会选中一串用户没看见的项；
 * - `target` 不在列表里返回空数组（不该发生，但返回 `[target]` 会让一个
 *   看不见的项被悄悄勾上，宁可什么都不做）。
 */
export function rangePaths(
  order: string[],
  anchor: string | null | undefined,
  target: string,
): string[] {
  const j = order.indexOf(String(target ?? ''))
  if (j < 0) return []
  const i = anchor ? order.indexOf(String(anchor)) : -1
  if (i < 0) return [order[j]]
  return order.slice(Math.min(i, j), Math.max(i, j) + 1)
}

/**
 * 路径 -> key，**去重且保持顺序**。
 *
 * 两个节点共用同一个业务 id 时只留一个：`*_ids` 里存的就是这个 key，
 * 重复写两遍在消费侧没有任何区别，只会让"已选 N 个"的数字虚高。
 */
export function keysOfPaths(byPath: Record<string, string>, paths: string[]): string[] {
  const out: string[] = []
  const seen = new Set<string>()
  for (const p of paths) {
    const k = byPath[p]
    if (k == null || seen.has(k)) continue
    seen.add(k)
    out.push(k)
  }
  return out
}

/* ------------------------------------------------------------ 合并 */

/** 单个 key 的增删，**保持原顺序、新增的排到末尾** */
export function toggleKey(list: unknown, key: string): string[] {
  const arr = Array.isArray(list) ? list.map(String) : []
  const k = String(key)
  return arr.includes(k) ? arr.filter((x) => x !== k) : [...arr, k]
}

/** 把一批 key 并进已选列表（不重复、保持顺序；"全选"用） */
export function unionPick(list: unknown, keys: string[]): string[] {
  const arr = Array.isArray(list) ? list.map(String) : []
  const seen = new Set(arr)
  const out = [...arr]
  for (const k of keys) if (!seen.has(k)) { seen.add(k); out.push(k) }
  return out
}

/**
 * 把一批 key 按 `replace` / `add` / `remove` 并进已选列表，**保持原顺序**。
 *
 * 与 `marqueeSelect.applyPickMode` 是同一套语义，差别只在数据形状：
 * 那个产出 `Set`（地图的选中路径就是 Set），这个产出**有序数组**
 * （`*_ids` 是数组，顺序即语义）。两边都留是因为调用方各自顺手，
 * 而"顺序被 Set 打乱"这种错很隐蔽——所以有序的那份单独测。
 */
export function mergePick(list: unknown, keys: string[], mode: PickMode): string[] {
  const arr = Array.isArray(list) ? list.map(String) : []
  if (mode === 'replace') return [...keys]
  if (mode === 'remove') {
    const drop = new Set(keys)
    return arr.filter((x) => !drop.has(x))
  }
  return unionPick(arr, keys)
}

/**
 * 「只在某一块能表示的范围内替换」。
 *
 * 典型场景：地图（`TrackMap`）只画得出**当前楼层**的航点，它回传的选中集合里
 * 天然不含别的楼层的航点。如果直接把那个集合当成最终答案，切到 2 楼框一下，
 * 1 楼挑好的就全没了——而且不会有任何提示，等下发任务时才发现少了一整层。
 *
 * 所以：`scope` 内的按 `hit` 结果走（不在 `hit` 里的就是"被取消勾选"），
 * `scope` 外的原样保留、顺序照旧；`hit` 里新出现的排到末尾。
 */
export function mergeScopedPick(
  list: unknown,
  hit: string[],
  scope: Iterable<string>,
): string[] {
  const arr = Array.isArray(list) ? list.map(String) : []
  const inScope = new Set(scope)
  const keep = new Set(hit)
  const out: string[] = []
  const seen = new Set<string>()
  for (const k of arr) {
    if (inScope.has(k) && !keep.has(k)) continue
    if (seen.has(k)) continue
    seen.add(k)
    out.push(k)
  }
  for (const k of hit) if (!seen.has(k)) { seen.add(k); out.push(k) }
  return out
}

/* ------------------------------------------------------------ Semi Tree */

/**
 * `PickNode[]` -> Semi `Tree` 要的树数据。
 *
 * **key 用路径**而不是业务 id（见文件头）。勾选状态、展开状态都由上层自己管
 * （不用 Semi 的 `value`/`onChange`）——那边的语义是"选树节点"，
 * 而这里是"挑一批东西"（多点累积、Shift 整段、Alt 移除），两套模型硬凑会互相打架。
 */
export function toSemiTree(nodes: PickNode<any>[]): any[] {
  return nodes.map((n) => ({
    key: n.path,
    label: n.label,
    isLeaf: n.isLeaf,
    children: n.isLeaf ? undefined : toSemiTree(n.children || []),
  }))
}
