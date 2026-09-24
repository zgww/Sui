/**
 * 巡检计划编排的纯函数 —— **无 React 依赖**，可被回归脚本直接编译后 import。
 *
 * 抽出来的理由与 `specTree.ts` / `detectBoxBinding.ts` 一致：这里的逻辑错了
 * 不会报错，只会"看起来对但数不对"（调度时刻算错一次、航点 key 对不上档案），
 * 埋在组件的事件处理器里根本没法验证。
 */

/** 巡检计划树里一个航点的摘要（给"航点指定"面板列选用） */
export interface WaypointBrief {
  /** 树内路径 `root/children/0/…`，只在同一棵航点树内有意义 */
  path: string
  /** 写进 WaypointSelectNode.waypoint_ids 的值（见 `waypointKey`） */
  key: string
  wp_id: string
  name: string
  floor: number
  index: number
  x: number
}

/**
 * 航点在"航点指定"里的标识。
 *
 * 优先 `wp_id`——它是业务 id，跨文件重排也稳定；手工在地图上画的航点没有
 * `wp_id`，退回树内路径。**不用 name**：name 可重复（样例数据里多个航点同名
 * 甚至为 None），拿它当 key 会让"勾了 A 结果 B 也被算进去"。
 *
 * ⚠️ 路径兜底对"航点树被重新排序"是敏感的，所以面板上要如实显示用的是哪一种，
 * 别让人以为它跟 `wp_id` 一样稳。
 */
export function waypointKey(node: any, path: string): string {
  const id = String(node?.properties?.wp_id ?? '').trim()
  return id || path
}

/** 从一棵航点树 spec 里抽出所有航点（按树中顺序，保持与航点树页面一致） */
export function collectWaypoints(spec: any): WaypointBrief[] {
  const out: WaypointBrief[] = []
  const walk = (node: any, path: string) => {
    if (!node || typeof node !== 'object') return
    if (node.type === 'WaypointNode') {
      const p = node.properties || {}
      const floor = Number(p.floor)
      const index = Number(p.index)
      const x = Number(p.x)
      out.push({
        path,
        key: waypointKey(node, path),
        wp_id: String(p.wp_id ?? ''),
        name: String(p.name ?? ''),
        floor: Number.isFinite(floor) ? floor : 1,
        index: Number.isFinite(index) ? index : 0,
        x: Number.isFinite(x) ? x : 0,
      })
    }
    const kids: any[] = node.children || []
    kids.forEach((c, i) => walk(c, `${path}/children/${i}`))
  }
  if (spec?.root) walk(spec.root, 'root')
  return out
}

/** 航点的展示名（缺失时回退链，**不许出现 undefined**） */
export function waypointLabel(w: WaypointBrief): string {
  const name = (w.name || '').trim() || w.wp_id || `航点 #${w.index}`
  return `${name}（F${w.floor} · ${w.x.toFixed(3)} m）`
}

/* ------------------------------------------------------------ 调度时段 */

/** `"HH:MM"` -> 当日分钟数；不合法返回 null（**不接受 `"8:5"` 这种半截写法**） */
export function parseHm(v: unknown): number | null {
  if (typeof v !== 'string') return null
  const m = /^(\d{1,2}):(\d{2})$/.exec(v.trim())
  if (!m) return null
  const h = Number(m[1])
  const mi = Number(m[2])
  if (h > 23 || mi > 59) return null
  return h * 60 + mi
}

/** 当日分钟数 -> `"HH:MM"`（超出 0~1439 会被夹住，避免算出 `"25:00"` 这种值） */
export function formatHm(minutes: number): string {
  const v = Math.max(0, Math.min(1439, Math.round(minutes)))
  return `${String(Math.floor(v / 60)).padStart(2, '0')}:${String(v % 60).padStart(2, '0')}`
}

/** 一天最多能排多少个时刻（每分钟一次也只有 1440 个），用于兜住脏数据 */
export const MAX_SLOTS_PER_DAY = 1440

/**
 * 每日调度的触发时刻列表（`HH:MM`，含首含尾）。
 *
 * 规则（与后端 `DailyScheduleNode` 的 docstring 一一对应）：
 * - 末次触发**不晚于** `end`：`start + n*interval <= end`；
 * - `end < start`（跨零点）**返回空数组**——真机上"跨天那段算今天还是明天"
 *   必须跟调度器对齐语义，含糊处理只会让现场对不上账，宁可不排；
 * - `start === end` 算"整天只有一个时刻"，返回 `[start]`，不展开成 24 小时；
 * - 时间串或间隔不合法（含 `interval <= 0`）返回空数组，由调用方提示。
 */
export function scheduleSlots(start: unknown, end: unknown, intervalMinutes: unknown): string[] {
  const a = parseHm(start)
  const b = parseHm(end)
  const step = Number(intervalMinutes)
  if (a === null || b === null) return []
  if (!Number.isFinite(step) || step <= 0) return []
  if (b < a) return []
  if (b === a) return [formatHm(a)]
  const out: string[] = []
  for (let t = a; t <= b && out.length < MAX_SLOTS_PER_DAY; t += step) out.push(formatHm(t))
  return out
}

/* ------------------------------------------------------------ 根：必须是分组 */

/**
 * 计划树的**根类型**：分组。
 *
 * 为什么根不能是 `InspectionPlanNode`（一条计划）：一个文件只能有一个根，
 * 根是单条计划就等于"一个文件只能配一条计划"——想给同一台机器人排"白天每小时
 * 走一遍、晚上两小时走一遍"就得开两个文件，`source` 之类的配置还得抄两遍。
 * 根是**分组**，下面挂 N 条 `InspectionPlanNode`，每条计划自带编号/机器人/优先级。
 *
 * 老文件的根可能是单条计划（早期就那么建的）：`ensureGroupRoot` 在读取时
 * 把它包一层分组，**只改内存、不动磁盘**，用户点保存才落盘。
 */
export const PLAN_GROUP_TYPE = 'PlanGroupNode'

/**
 * 保证 spec 的根节点是分组：不是就把它包进一个新分组。
 *
 * 返回新的 spec（**深拷贝**，不碰入参）与 `wrapped`（是否动过，供页面提示）。
 * 分组名取文件名（`spec.name`）——它就是"这个文件装了什么"的名字。
 */
export function ensureGroupRoot(spec: any): { spec: any; wrapped: boolean } {
  const root = spec?.root
  if (!root || typeof root !== 'object') return { spec, wrapped: false }
  if (root.type === PLAN_GROUP_TYPE) return { spec, wrapped: false }
  const next = JSON.parse(JSON.stringify(spec))
  const inner = next.root
  next.root = {
    type: PLAN_GROUP_TYPE,
    properties: {
      name: String(next?.name || inner?.properties?.name || '巡检计划').trim() || '巡检计划',
      enabled: true,
      description: '',
    },
    children: [inner],
  }
  return { spec: next, wrapped: true }
}

/* ------------------------------------------------------------ 停用（变灰） */

/** 树路径分隔符（与 `utils/trackSpec.ts` 的 `SEP` 同值；这里不引它是为了
 *  让本模块保持零依赖，能被回归脚本单独编译） */
const PATH_SEP = '/'

/**
 * 收集"停用"的节点：`disabled` 是**自己**被停用的，`muted` 是**自己或祖先**
 * 被停用的（即整棵子树，树上要变灰的那些）。
 *
 * 为什么子树要跟着灰：`enabled` 的语义是"该节点及其子树不参与运行"
 * （后端 `NodeBase.enabled` 的 docstring）。一条计划停了，它下面的航点指定 /
 * 每日调度同样不会跑，只把计划那一行变灰会让人以为"计划停了但调度还在"。
 *
 * `properties.enabled` 缺省视为 true（老数据里可能整个字段都没写），
 * 只有**显式等于 false** 才算停用。
 */
export function collectDisabled(root: any): {
  disabled: Set<string>
  muted: Set<string>
} {
  const disabled = new Set<string>()
  const muted = new Set<string>()
  const walk = (node: any, path: string, parentMuted: boolean) => {
    if (!node || typeof node !== 'object') return
    const off = node?.properties?.enabled === false
    if (off) disabled.add(path)
    const dim = parentMuted || off
    if (dim) muted.add(path)
    const kids: any[] = node.children || []
    kids.forEach((c, i) => walk(c, `${path}${PATH_SEP}children${PATH_SEP}${i}`, dim))
  }
  walk(root, 'root', false)
  return { disabled, muted }
}

/* ------------------------------------------------------------ 树节点摘要 */

const NODE_TYPE_TEXT: Record<string, string> = {
  InspectionPlanNode: '巡检计划',
  PlanGroupNode: '分组',
  WaypointSelectNode: '航点指定',
  PointSelectNode: '测点指定',
  DailyScheduleNode: '每日调度',
}

/** 计划树节点类型 -> 中文名（树上的 Tag 与添加子节点弹窗共用） */
export function planTypeLabel(type: string): string {
  return NODE_TYPE_TEXT[type] || type
}

/** 计划树节点类型的显示色（Semi Tag 的 color；用 any 免得把 Semi 的类型引进来） */
export const PLAN_TYPE_COLOR: Record<string, any> = {
  InspectionPlanNode: 'blue',
  PlanGroupNode: 'grey',
  WaypointSelectNode: 'green',
  PointSelectNode: 'teal',
  DailyScheduleNode: 'orange',
}

/**
 * 树上那个"一眼看出这个节点在说什么"的摘要。
 *
 * 只吃节点自己，不去读被引用的航点树 / 测点档案——树标签是**同步**渲染的，
 * 为了显示一句话去发请求会让整棵树跟着闪。所以摘要说的是"配置了什么"，
 * 不是"解析出来有多少个"。
 */
export function planNodeSummary(node: any): string {
  const type = node?.type
  const p = node?.properties || {}
  if (type === 'WaypointSelectNode') {
    const src = String(p.source || '').trim()
    const scope = p.include_all === false
      ? `${Array.isArray(p.waypoint_ids) ? p.waypoint_ids.length : 0} 个航点`
      : '全部航点'
    return src ? `${src} · ${scope}` : `未指定航点树 · ${scope}`
  }
  if (type === 'PointSelectNode') {
    return p.include_all === false
      ? `${Array.isArray(p.point_ids) ? p.point_ids.length : 0} 个测点`
      : '全部测点'
  }
  if (type === 'DailyScheduleNode') {
    const slots = scheduleSlots(p.start_time, p.end_time, p.interval_minutes)
    const span = `${String(p.start_time || '?')}–${String(p.end_time || '?')}`
    const every = Number(p.interval_minutes)
    const everyText = Number.isFinite(every) && every > 0 ? `每 ${every} 分` : '间隔未设置'
    return slots.length
      ? `${span} · ${everyText} · 每天 ${slots.length} 次`
      : `${span} · ${everyText}（无法排出时刻，请检查时间/间隔）`
  }
  if (type === 'InspectionPlanNode') {
    const id = String(p.plan_id || '').trim()
    return id ? `计划 ${id}` : ''
  }
  if (type === 'PlanGroupNode') {
    // 根是分组、一个文件多条计划——分组行上直接报条数，省得展开才知道有几条
    let n = 0
    const walk = (x: any) => {
      if (!x || typeof x !== 'object') return
      if (x.type === 'InspectionPlanNode') n += 1
      for (const c of x.children || []) walk(c)
    }
    for (const c of node?.children || []) walk(c)
    return n ? `${n} 条计划` : ''
  }
  return ''
}

/* ------------------------------------------------------------ 复制粘贴 */

let planSeq = 0

/**
 * 粘贴出来的计划子树要换掉**业务 id**（目前只有计划编号）。
 *
 * 与 `inspectionBuild.regenerateIds` 同理：复制件沿用原编号的话，两份计划在
 * 调度侧会被当成同一条，改一处等于改两处。航点指定 / 测点指定里存的是**引用**
 * （航点 key、测点 id），那是要照抄的，不能动。
 *
 * 返回改动的个数，供调用方在 Toast 里如实说明。
 */
export function regeneratePlanIds(node: any): number {
  if (!node || typeof node !== 'object') return 0
  let n = 0
  if (node.type === 'InspectionPlanNode') {
    planSeq += 1
    node.properties = { ...(node.properties || {}) }
    node.properties.plan_id = `PLAN-${Date.now().toString(36)}-${planSeq}`
    n += 1
  }
  for (const c of node.children || []) n += regeneratePlanIds(c)
  return n
}
