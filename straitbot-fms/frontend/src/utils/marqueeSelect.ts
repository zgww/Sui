/**
 * 框选的三种模式 —— **纯函数，无 React 依赖**，可被回归脚本直接编译后 import。
 *
 * 抽出来的理由与 `specTree.ts` / `trackGeometry.ts` 一致：这段逻辑错了**不会报错**，
 * 只会"少选几个 / 多选几个"，而且是在拖拽过程中逐帧体现的，埋在事件处理器里
 * 根本没法验证。
 *
 * ## 为什么"基准选择"必须由调用方在**按下那一刻**快照
 *
 * 拖拽途中会不停地把结果回写（实时预览）。如果每帧都拿"上一帧的结果"当基准
 * 去合并，结果就不再等于 `f(按下时的选择, 当前框, 模式)`，而是变成一条
 * **不可逆的累积路径**：
 * - `add`：划过的点一直留着，把框拖回去也撤不掉（"粘住了"）；
 * - `remove`：一旦被框划走就再也回不来，把框移开也不恢复。
 *
 * 拿按下时的快照当基准，则两个方向都是"所见即所得"：框罩住就生效、框移开就
 * 还原。所以 `applyPickMode(base, hit, mode)` 的 `base` **必须是按下那一刻的
 * 快照**，不是实时值，也不是上一帧的结果。这一点在回归脚本里用
 * "同一基准、连续两帧、第二帧的 hit 是子集"的用例锁着。
 */

/** 框选模式：替换 / 并入 / 移除 */
export type PickMode = 'replace' | 'add' | 'remove'

/** 工具栏上的顺序（替换在最左，与"默认行为"一致） */
export const PICK_MODES: PickMode[] = ['replace', 'add', 'remove']

export const PICK_MODE_LABEL: Record<PickMode, string> = {
  replace: '替换',
  add: '增加',
  remove: '移除',
}

export const PICK_MODE_HINT: Record<PickMode, string> = {
  replace: '框选结果替换当前选择',
  add: '框选结果并入当前选择',
  remove: '框选结果从当前选择里去掉',
}

/** 脏值一律回落 `replace`（**不做**"看起来像 add 就当 add"的猜测） */
export function normalizePickMode(v: unknown): PickMode {
  return v === 'add' || v === 'remove' ? v : 'replace'
}

/**
 * 本次拖拽实际用哪种模式。
 *
 * 按住 **Shift** = 增加、按住 **Alt** = 移除，两者都没按就用工具栏上选的基准模式。
 * Shift 优先于 Alt：两个一起按时用户多半是想"加"（Shift 是更常见的加选键），
 * 而且这样 Shift 的行为与"点选时 Shift = 加选"一致，不会自相矛盾。
 *
 * 参数只要求 `shiftKey` / `altKey` 两个字段，好让回归脚本能直接喂普通对象，
 * 不必造一个真的 MouseEvent。
 */
export function resolvePickMode(
  ev: { shiftKey?: boolean; altKey?: boolean } | null | undefined,
  base: PickMode,
): PickMode {
  if (ev?.shiftKey) return 'add'
  if (ev?.altKey) return 'remove'
  return normalizePickMode(base)
}

/**
 * 把这一框命中的 `hit` 并进基准选择 `base`。
 *
 * - `replace`：结果**只有** `hit`（`base` 完全不参与——所以清空动作也可以省掉，
 *   调用方不必在按下时先清一次）
 * - `add`：`base ∪ hit`
 * - `remove`：`base \ hit`
 *
 * 返回 `Set`（调用方普遍就是拿 Set 存选中路径）。`hit` 里的重复项由 Set 天然去重。
 */
export function applyPickMode(
  base: Iterable<string>,
  hit: Iterable<string>,
  mode: PickMode,
): Set<string> {
  const keys = [...hit]
  if (mode === 'remove') {
    const out = new Set<string>(base)
    for (const k of keys) out.delete(k)
    return out
  }
  const out = new Set<string>(mode === 'replace' ? [] : base)
  for (const k of keys) out.add(k)
  return out
}
