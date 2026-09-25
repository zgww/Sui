/**
 * 巡检日志详情的**树组织**与**检视器字段**（纯函数，无 React、无 Semi 依赖）。
 *
 * ## 为什么单独一个模块
 *
 * 详情窗口要做两件事：把三张表的数据拼成"楼层 → 航点 → 动作点 → 检测框"四级树，
 * 以及把选中节点的字段摊成键值对给检视器。这两件事都是**口径问题**（谁挂在谁下面、
 * 动作失败时检测框还显不显示、`passed=null` 该说"未判定"而不是"未通过"），
 * 需要单独测。所以逻辑全放这里，组件只做渲染。
 *
 * ⚠️ 本模块是**纯逻辑模块**，不能 import `@douyinfe/semi-*`（该包在 Node 原生 ESM 下
 * 加载不了，`verify-*.mjs` 会连编译都过不去）。要用图标的话拆到同目录 `.tsx`。
 *
 * ## 树为什么是这四级
 *
 * 这与巡检本身的层级严格对应，不是硬凑的：
 *
 * - **楼层**：`action.floor`。虽然是单层站，但字段在键里（跨楼层航点 id 会重复）；
 * - **航点**：`action.waypoint_id` + `waypoint_index`。一个航点下可能多个动作；
 * - **动作点**：`action_id`。这是"拍到一张图 / 录一段像"的粒度；
 * - **检测框**：`kind='detect'` 的测点。**一个动作下的一个检测区域**，
 *   这才是有 rect、有算法、有结论的那一层。定位键优先用 `box_id`（检测框自己的
 *   身份，没绑测点也一定有），`point_id` 只是"顺手绑了哪个测点档案"。
 *
 * ## 检视器为什么要"旁路数据"
 *
 * 账本（三张表）里只有**引用 id**：流程引用、测点 id。而人要看的名字（流程叫
 * 「人员入侵」、测点是「G1 柜电流表」）不在账本里 —— 由后端一次查好塞进
 * `detect_flow_name` / `point` 两个字段（见 `services/inspection_log.py`）。
 * 本模块**只渲染**，不做任何查询：它是纯函数，要被回归脚本直接调用。
 *
 * ## 为什么要按 id 分组建树、而不是直接用平面列表
 *
 * 三个接口返回的是三份**独立的平面列表**（动作 107 条、测点 19 条），它们之间只有
 * `action_result_id` 这个外键。所以要自己分组：先按楼层、再按航点、再按动作，
 * 最后把测点挂到它所属的动作下面。测点挂错父节点的话，页面上会出现"检测框挂在
 * 没图的动作上"这种看不出来的错。
 */
import type {
  ActionResultRow, InspectionRunRow, PointArchiveLite, PointResultRow,
} from '../api/inspectionLog'

/** 树节点类型：四级 + 一个"空动作占位"提示节点。 */
export type LogNodeKind = 'floor' | 'waypoint' | 'action' | 'point' | 'notice'

export interface LogTreeNode {
  /** 稳定 key（展开态、选中态都用它）。格式见 `nodeKey()` */
  key: string
  kind: LogNodeKind
  /** 树上显示的文字 */
  label: string
  /** 显示在 label 右边的小标签（可多个：执行状态 + 分发状态…） */
  tags: { text: string; color: string }[]
  /** 该节点下方还有几个子节点（楼层/航点显示"N 个动作"这类计数） */
  meta: string
  children: LogTreeNode[]
  /** 挂回去的原始数据，检视器要用 */
  floor?: number
  action?: ActionResultRow
  point?: PointResultRow
  /** 楼层/航点没有单一原始行，用这两个字段兜住聚合结果 */
  actions?: ActionResultRow[]
  points?: PointResultRow[]
}

/** 节点 key 的构造：四段用 `/` 分隔，避免不同层级的同名 id 撞车。 */
export function nodeKey(kind: LogNodeKind, ...parts: (string | number)[]): string {
  return [kind, ...parts.map((p) => String(p))].join('/')
}

/** 动作状态 -> 树上小标签。与列表页 `actionStatusTag` 同一套文案，别写两遍。 */
export function actionTag(s: string): { text: string; color: string } {
  const map: Record<string, { text: string; color: string }> = {
    pending: { text: '未执行', color: 'grey' },
    ok: { text: '成功', color: 'green' },
    failed: { text: '失败', color: 'red' },
    skipped: { text: '跳过', color: 'orange' },
  }
  return map[s] || { text: s || '—', color: 'grey' }
}

/** 动作类型 -> 中文。后端 `action_type_name` 已经给了就用它，这里兜底。 */
export function actionTypeText(row: ActionResultRow): string {
  if (row.action_type_name) return row.action_type_name
  return { 1: '拍照', 2: '测温', 3: '录像' }[row.action_type] || `类型${row.action_type}`
}

/** 分发状态 -> 树上的小标签（只在动作节点上显示）。 */
export function dispatchTag(s: string): { text: string; color: string } {
  const map: Record<string, { text: string; color: string }> = {
    pending: { text: '待分发', color: 'grey' },
    done: { text: '已分发', color: 'green' },
    failed: { text: '分发失败', color: 'red' },
  }
  return map[s] || { text: s || '—', color: 'grey' }
}

/** 检测结论 -> 文案（**三态**，`null` 是"未判定"不是"未通过"）。 */
export function passedText(passed: boolean | null | undefined): string {
  if (passed === true) return '通过'
  if (passed === false) return '未通过'
  return '未判定'
}

/** 检测结论 -> 标签色（同上三态）。 */
export function passedColor(passed: boolean | null | undefined): string {
  if (passed === true) return 'green'
  if (passed === false) return 'red'
  return 'grey'
}

/** 测点来源 -> 文案。 */
export function kindText(kind: string): string {
  return { thermometry: '测温点', detect: '检测点' }[kind] || kind || '—'
}

/**
 * 把三个平面列表组织成四级树。
 *
 * @param run      列表行（取 remark 做根节点文案；没有也照样建树）
 * @param actions  动作结果（`/runs/{id}/actions` 的 items）
 * @param points   测点结果（`/runs/{id}/points` 的 items）
 *
 * 排序：楼层升序 → 航点 index 升序 → 动作 seq 升序 → 测点 seq 升序。
 * **后端已经排过一遍**，这里再排是因为接口可能被别的地方复用（比如按状态筛选后
 * 顺序变了），树视图乱序比列表乱序更难看出来。
 */
export function buildLogTree(
  actions: ActionResultRow[],
  points: PointResultRow[],
): LogTreeNode[] {
  // 1) 测点按 action_result_id 分组 —— 挂哪去只能靠这个外键
  const pointsByAction = new Map<number, PointResultRow[]>()
  for (const p of points) {
    const key = p.action_result_id ?? -1
    const list = pointsByAction.get(key)
    if (list) list.push(p)
    else pointsByAction.set(key, [p])
  }

  // 2) 动作按 楼层 -> 航点 两级分组
  const byFloor = new Map<number, Map<string, ActionResultRow[]>>()
  for (const a of actions) {
    const floorMap = byFloor.get(a.floor) ?? new Map<string, ActionResultRow[]>()
    if (!byFloor.has(a.floor)) byFloor.set(a.floor, floorMap)
    const list = floorMap.get(a.waypoint_id)
    if (list) list.push(a)
    else floorMap.set(a.waypoint_id, [a])
  }

  const floors = [...byFloor.keys()].sort((x, y) => x - y)
  const out: LogTreeNode[] = []

  for (const floor of floors) {
    const wpMap = byFloor.get(floor)!
    const floorActions: ActionResultRow[] = []
    const wpNodes: LogTreeNode[] = []

    // 航点按 waypoint_index 升序；index 缺失时退回 id 字典序（不能因为没 index 就丢）
    const wpIds = [...wpMap.keys()].sort((x, y) => {
      const ax = wpMap.get(x)![0]
      const ay = wpMap.get(y)![0]
      return (ax.waypoint_index - ay.waypoint_index) || x.localeCompare(y)
    })

    for (const wpId of wpIds) {
      const acts = wpMap.get(wpId)!.slice()
        .sort((x, y) => (x.action_seq - y.action_seq) || (x.id - y.id))
      floorActions.push(...acts)

      const actNodes: LogTreeNode[] = []
      const wpPoints: PointResultRow[] = []
      for (const act of acts) {
        const pts = (pointsByAction.get(act.id) || []).slice()
          .sort((x, y) => (x.seq - y.seq) || (x.id - y.id))
        wpPoints.push(...pts)
        actNodes.push(actionNode(act, pts))
      }

      const wpLabel = acts[0].waypoint_name
        ? `航点 ${acts[0].waypoint_index || '?'} · ${acts[0].waypoint_name}`
        : `航点 ${acts[0].waypoint_index || wpId.slice(0, 8)}`
      wpNodes.push({
        key: nodeKey('waypoint', floor, wpId),
        kind: 'waypoint',
        label: wpLabel,
        tags: [],
        meta: countMeta(actNodes.length, '动作', wpPoints.length, '检测框'),
        children: actNodes,
        floor,
        actions: acts,
        points: wpPoints,
      })
    }

    const floorPoints = wpNodes.flatMap((w) => w.points || [])
    out.push({
      key: nodeKey('floor', floor),
      kind: 'floor',
      label: `第 ${floor} 层`,
      tags: [],
      meta: countMeta(floorActions.length, '动作', wpNodes.length, '航点'),
      children: wpNodes,
      floor,
      actions: floorActions,
      points: floorPoints,
    })
  }

  return out
}

/** 动作节点。没有检测框时挂一个 notice 子节点，别让"没有子节点"看起来像加载失败。 */
function actionNode(act: ActionResultRow, pts: PointResultRow[]): LogTreeNode {
  // 动作节点两个标签：执行状态（成功/失败）+ 分发状态（已分发/待分发）
  // 分发失败用红色，和执行失败区分开——一眼就能看出"图拍到了但没传上去"
  const tags = [actionTag(act.status)]
  // 只有 fms 本地检测才有"数据分发"这回事；platform 是机器人自己上传的，不显示
  if (act.detect_type === 'fms') {
    tags.push(dispatchTag(act.dispatch_status))
  }
  const children: LogTreeNode[] = pts.length
    ? pts.map((p) => ({
        // key 优先用 box_id（检测框自己的身份，**没绑测点也一定有**）：
        // 拿 point_id 当 key 的话，未绑测点的框只能退到自增 id，轮询刷新时
        // 行号一变选中态就跟着跳（详情页 5 秒刷一次，很容易看到）
        key: nodeKey('point', act.id, p.box_id || p.point_id || p.id),
        kind: 'point' as const,
        label: pointLabel(p),
        tags: [{ text: passedText(p.passed), color: passedColor(p.passed) }],
        meta: boxesMeta(p),
        children: [],
        floor: act.floor,
        action: act,
        point: p,
      }))
    : [{
        key: nodeKey('notice', act.id),
        kind: 'notice' as const,
        label: noPointReason(act),
        tags: [],
        meta: '',
        children: [],
        floor: act.floor,
        action: act,
      }]

  return {
    key: nodeKey('action', act.floor, act.waypoint_id, act.action_id),
    kind: 'action',
    label: `${actionTypeText(act)} · ${act.waypoint_name || act.action_id.slice(0, 8)}`,
    tags,
    meta: children.length ? `${children.length} 检测框` : '',
    children,
    floor: act.floor,
    action: act,
    points: pts,
  }
}

/** "为什么没有检测框" —— 三种原因要分清，否则看起来都像"丢了"。 */
function noPointReason(act: ActionResultRow): string {
  if (act.status === 'pending') return '未执行，没有数据'
  if (act.status === 'failed') return '执行失败，没有取到图'
  if (act.status === 'skipped') return '已跳过'
  if (act.action_type === 3) return '录像动作，没有检测框'
  return '该动作没有绑定检测框'
}

/**
 * 检测框节点在树上的文字。
 *
 * 优先级：**框名 → 测点名 → 测点 ID → 检测框#序号**。
 * 框名在最前是因为它是"这一块区域"的名字（编排时人起的，如「3 号柜电流表」）；
 * 没绑测点的框只有框名可看，而绑了测点的框通常框名就来自测点名。
 * ⚠️ 最后兜底不能留空：一条没有名字的行在树里看着像加载失败。
 */
function pointLabel(p: PointResultRow): string {
  return p.box_name || p.label || p.point_id || `检测框#${p.seq + 1}`
}

/** `N 个 A · M 个 B`；某一项为 0 就不写它，免得"0 个检测框"占地方。 */
function countMeta(n1: number, u1: string, n2: number, u2: string): string {
  const parts: string[] = []
  if (n1) parts.push(`${n1} 个${u1}`)
  if (n2) parts.push(`${n2} 个${u2}`)
  return parts.join(' · ')
}

/** 检测框节点的副标题：几个框 + 置信度。 */
function boxesMeta(p: PointResultRow): string {
  const bits: string[] = []
  const boxes = p.boxes?.length || 0
  if (boxes) bits.push(`${boxes} 框`)
  if (p.confidence != null) bits.push(`置信 ${(p.confidence * 100).toFixed(1)}%`)
  return bits.join(' · ')
}

// ------------------------------------------------------------------ 检视器
export interface InspectField {
  label: string
  value: string
  /** 等宽字体（id / 路径 / JSON） */
  mono?: boolean
  /** 图片字段：检视器渲染成可点开的缩略图 */
  image?: boolean
  /** 长文本（JSON / 错误原因）：换行显示 */
  block?: boolean
  /** 危险色（失败原因） */
  danger?: boolean
}

/** 检视器分组：一组字段一个小标题。 */
export interface InspectGroup {
  title: string
  fields: InspectField[]
}

const dash = (v: unknown): string => {
  if (v === null || v === undefined || v === '') return '—'
  return String(v)
}

/** JSON 友好展示：对象/数组转缩进字符串；空的给 `—`。 */
function jsonText(v: unknown): string {
  if (v === null || v === undefined) return '—'
  if (Array.isArray(v) && v.length === 0) return '—'
  if (typeof v === 'object' && !Object.keys(v as object).length) return '—'
  try {
    return JSON.stringify(v, null, 2)
  } catch {
    return String(v)
  }
}

/** 时间：ISO -> 本地字符串。解析不出来就原样显示（别显示 Invalid Date）。 */
export function fmtTime(v: string | null | undefined): string {
  if (!v) return '—'
  const d = new Date(v)
  return Number.isNaN(d.getTime()) ? String(v) : d.toLocaleString()
}

/**
 * 按选中节点生成检视器内容。
 *
 * 每个层级关心的事不一样，所以字段是**按 kind 分派**的，不是"把原始对象摊平"：
 * 楼层只关心汇总、检测框才关心 rect 与置信度。摊平会把没用的字段堆满一屏。
 */
export function inspectNode(node: LogTreeNode | null): InspectGroup[] {
  if (!node) return []
  switch (node.kind) {
    case 'floor': return floorGroups(node)
    case 'waypoint': return waypointGroups(node)
    case 'action': return actionGroups(node.action!)
    case 'point': return pointGroups(node.point!, node.action)
    case 'notice': return actionGroups(node.action!)
    default: return []
  }
}

function floorGroups(node: LogTreeNode): InspectGroup[] {
  const acts = node.actions || []
  const pts = node.points || []
  const st = tally(acts.map((a) => a.status))
  const dp = tally(acts.map((a) => a.dispatch_status))
  return [{
    title: '楼层汇总',
    fields: [
      { label: '楼层', value: `第 ${node.floor} 层` },
      { label: '航点数', value: String(node.children.length) },
      { label: '动作数', value: String(acts.length) },
      { label: '检测框', value: String(pts.length) },
    ],
  }, {
    title: '动作状态',
    fields: [
      { label: '成功', value: `${st.ok || 0}` },
      { label: '失败', value: `${st.failed || 0}`, danger: Boolean(st.failed) },
      { label: '跳过', value: `${st.skipped || 0}` },
      { label: '未执行', value: `${st.pending || 0}` },
    ],
  }, {
    title: '数据分发',
    fields: [
      { label: '已分发', value: `${dp.done || 0}` },
      { label: '分发失败', value: `${dp.failed || 0}`, danger: Boolean(dp.failed) },
      { label: '待分发', value: `${dp.pending || 0}` },
    ],
  }]
}

function waypointGroups(node: LogTreeNode): InspectGroup[] {
  const acts = node.actions || []
  const pts = node.points || []
  const first = acts[0]
  return [{
    title: '航点',
    fields: [
      { label: '楼层', value: `第 ${node.floor} 层` },
      { label: '序号', value: dash(first?.waypoint_index) },
      { label: '名称', value: dash(first?.waypoint_name) },
      { label: '航点 ID', value: dash(first?.waypoint_id), mono: true },
      { label: '动作点数', value: String(acts.length) },
      { label: '检测框', value: String(pts.length) },
    ],
  }, {
    title: '动作明细',
    fields: acts.map((a) => ({
      label: `seq ${a.action_seq}`,
      value: `${actionTypeText(a)} · ${actionTag(a.status).text}`
        + (a.picture || a.media ? ' · 有图' : ''),
    })),
  }]
}

function actionGroups(act: ActionResultRow): InspectGroup[] {
  const groups: InspectGroup[] = [{
    title: '定位',
    fields: [
      { label: '楼层', value: `第 ${act.floor} 层` },
      { label: '航点序号', value: dash(act.waypoint_index) },
      { label: '航点名称', value: dash(act.waypoint_name) },
      { label: '航点 ID', value: dash(act.waypoint_id), mono: true },
      { label: '动作 ID', value: dash(act.action_id), mono: true },
      { label: '动作序号', value: `第 ${act.action_seq + 1} 个` },
    ],
  }, {
    title: '执行',
    fields: [
      { label: '类型', value: actionTypeText(act) },
      { label: '状态', value: actionTag(act.status).text },
      { label: '错误码', value: String(act.code ?? 0) },
      { label: '执行方', value: act.executor === 'robot' ? '机器人' : '本站' },
      { label: '尝试次数', value: `第 ${act.attempt || 1} 次` },
      { label: '耗时', value: act.duration_ms > 0 ? `${(act.duration_ms / 1000).toFixed(1)} s` : '—' },
      { label: '开始', value: fmtTime(act.start_time) },
      { label: '完成', value: fmtTime(act.finish_time) },
    ],
  }, {
    title: '数据',
    fields: [
      { label: '可见光图', value: dash(act.picture), image: true },
      { label: '红外图', value: dash(act.infrared), image: true },
      { label: '录像 / 录音', value: dash(act.media), mono: true },
      { label: '本地路径', value: dash(act.local_path), mono: true },
      { label: '在场时刻', value: dash(act.inplace_ts) },
    ],
  }, {
    title: '分发',
    fields: [
      { label: '口径', value: act.detect_type === 'fms' ? '本站检测' : '上传平台' },
      { label: '状态', value: dispatchTag(act.dispatch_status).text },
      { label: '方向', value: act.dispatch_mode === 'detect' ? '本地检测' : act.dispatch_mode === 'upload' ? '上报平台' : '—' },
      { label: '尝试次数', value: String(act.dispatch_attempts || 0) },
      { label: '分发时刻', value: fmtTime(act.dispatched_at) },
      ...(act.dispatch_error
        ? [{ label: '失败原因', value: act.dispatch_error, block: true, danger: true }]
        : []),
    ],
  }]

  // 有原始数据才给这一组，免得空 JSON 占一屏
  const raw: InspectField[] = []
  if (act.pdd) raw.push({ label: '局部放电', value: jsonText(act.pdd), mono: true })
  if (act.thermometry) raw.push({ label: '测温配置', value: jsonText(act.thermometry), mono: true })
  if (act.env) raw.push({ label: '环境量', value: jsonText(act.env), mono: true })
  if (raw.length) groups.push({ title: '原始数据', fields: raw })

  return groups
}

function pointGroups(p: PointResultRow, act?: ActionResultRow): InspectGroup[] {
  const groups: InspectGroup[] = [{
    title: '检测框',
    fields: [
      { label: '来源', value: kindText(p.kind) },
      // 检测框 ID 与测点 ID **分开显示**：前者是这块区域自己的身份（一定有），
      // 后者指向测点档案（可以不绑）。合成一栏会让人以为"没绑测点就没身份"。
      { label: '检测框 ID', value: dash(p.box_id), mono: true },
      { label: '框名', value: dash(p.box_name) },
      { label: '测点 ID', value: dash(p.point_id), mono: true },
      { label: '测点名', value: dash(p.label) },
      { label: '序号', value: `第 ${p.seq + 1} 个` },
      { label: '状态', value: actionTag(p.status).text },
    ],
  }, {
    title: '结论',
    fields: [
      { label: '判定', value: passedText(p.passed) },
      ...(p.confidence != null
        ? [{ label: '置信度', value: `${(p.confidence * 100).toFixed(1)}%` }]
        : []),
      { label: '判定值', value: p.value != null ? `${p.value}${p.unit || ''}` : '—' },
    ],
  }]

  // —— 测点档案：绑了测点且档案里查得到才给这一组 ——
  // 后端按 point_id 查好带出来（`point` 字段）；查不到说明档案被删过或没绑，
  // 这时给一栏空字段没有意义，不如不显示。
  const ar: PointArchiveLite | null | undefined = p.point
  if (ar) {
    const fields: InspectField[] = [
      { label: '测点编号', value: dash(ar.code), mono: true },
      { label: '测点名', value: dash(ar.name) },
      { label: '所属设备', value: dash(ar.parent_name) },
    ]
    if (ar.path?.length) fields.push({ label: '层级', value: ar.path.join(' / ') })
    fields.push({ label: '启用', value: ar.active ? '是' : '否（已停用）', danger: !ar.active })
    fields.push({ label: '档案 ID', value: dash(ar.id), mono: true })
    groups.push({ title: '测点档案', fields })
  }

  // —— 检测算法流程：账本里只有引用 id，中文名由后端解析（`detect_flow_name`）——
  const raw = (p.raw || {}) as Record<string, any>
  const flowFields: InspectField[] = [
    { label: '流程', value: dash(p.detect_flow_name || p.detect_flow) },
  ]
  if (p.detect_flow_name) flowFields.push({ label: '流程引用', value: dash(p.detect_flow), mono: true })
  // 算法：`raw.display_name` 是算法服务回的中文名（panel_list.json 的 display_name），
  // `algorithm` 是它的编码。有中文名就先给中文名，编码另外单列（对日志要用编码）。
  if (raw.display_name) flowFields.push({ label: '算法', value: String(raw.display_name) })
  flowFields.push({ label: '算法编码', value: dash(p.algorithm), mono: true })
  groups.push({ title: '检测算法流程', fields: flowFields })

  // —— 算法识别结果：结果框原样留痕（display / parameter / code…）——
  const res: InspectField[] = []
  if (raw.display !== undefined && raw.display !== '') {
    res.push({ label: '算法结论', value: String(raw.display) })
  }
  if (raw.parameter !== undefined && raw.parameter !== '') {
    res.push({ label: '读数', value: String(raw.parameter), mono: true })
  }
  if (raw.code !== undefined && raw.code !== '') {
    res.push({ label: '算法状态码', value: String(raw.code), danger: String(raw.code) !== '0' })
  }
  if (raw.msg) res.push({ label: '算法提示', value: String(raw.msg) })
  if (raw.error) res.push({ label: '算法错误', value: String(raw.error), block: true, danger: true })
  if (res.length) groups.push({ title: '算法识别结果', fields: res })

  // 检出框：归一化坐标逐个列出来，比丢一坨 JSON 好查
  const boxes = p.boxes || []
  if (boxes.length) {
    groups.push({
      title: `检出框坐标（归一化 0~1）`,
      fields: boxes.map((b, i) => ({
        label: `#${i + 1}${b.label ? ` ${b.label}` : ''}`,
        value: `x=${num(b.x)} y=${num(b.y)} w=${num(b.w)} h=${num(b.h)}`
          + (b.score != null ? ` score=${num(b.score)}` : ''),
        mono: true,
      })),
    })
  }

  if (act) {
    groups.push({
      title: '所属动作',
      fields: [
        { label: '类型', value: actionTypeText(act) },
        { label: '状态', value: actionTag(act.status).text },
        { label: '航点', value: act.waypoint_name || dash(act.waypoint_index) },
        { label: '可见光图', value: dash(act.picture), image: true },
      ],
    })
  }

  const rawData: InspectField[] = []
  // 流程执行明细（`detect`）与算法原始报文（`raw`）是**两层**数据：
  // 前者是"流程跑完的结论（过了哪些闸门、要发什么告警）"，后者是"算法到底认出了什么"。
  // 排查时经常要对照着看，所以两栏都留。
  if (p.detect) rawData.push({ label: '流程执行明细', value: jsonText(p.detect), mono: true, block: true })
  if (p.raw) rawData.push({ label: '算法原始报文', value: jsonText(p.raw), mono: true, block: true })
  if (rawData.length) groups.push({ title: '原始数据', fields: rawData })

  return groups
}

/** 数字保留 4 位小数（归一化坐标动辄 8 位，全显示没人看）。 */
function num(v: unknown): string {
  const n = Number(v)
  return Number.isFinite(n) ? String(Math.round(n * 10000) / 10000) : '—'
}

/** 计数助手：`['ok','ok','failed']` -> `{ok:2, failed:1}`。 */
function tally(values: string[]): Record<string, number> {
  const out: Record<string, number> = {}
  for (const v of values) out[v] = (out[v] || 0) + 1
  return out
}

/** 树的全量展开 key（首次打开时用）。 */
export function allKeys(nodes: LogTreeNode[]): string[] {
  const out: string[] = []
  const walk = (list: LogTreeNode[]) => {
    for (const n of list) {
      if (n.children.length) {
        out.push(n.key)
        walk(n.children)
      }
    }
  }
  walk(nodes)
  return out
}

/** 按 key 在树里找节点（选中态回填用）。 */
export function findNode(nodes: LogTreeNode[], key: string | null): LogTreeNode | null {
  if (!key) return null
  for (const n of nodes) {
    if (n.key === key) return n
    const hit = findNode(n.children, key)
    if (hit) return hit
  }
  return null
}

/** 默认选中：第一个有内容的动作（打开窗口就有东西看，不用让人先点两下）。 */
export function defaultSelection(nodes: LogTreeNode[]): string | null {
  const walk = (list: LogTreeNode[]): string | null => {
    for (const n of list) {
      if (n.kind === 'action') return n.key
      const hit = walk(n.children)
      if (hit) return hit
    }
    return null
  }
  return walk(nodes) || (nodes[0]?.key ?? null)
}

/* ------------------------------------------------------------------ */
/*  跟随刷新（"盯当前正在跑的那一步"）                                    */
/* ------------------------------------------------------------------ */

/**
 * 还没跑完的动作状态。
 *
 * ⚠️ 只有 `pending` 算"未执行"——`skipped` 是**已经判过**的结论（这台设备不需要做），
 * 把它算进去会让轮询永远停在同一个动作上，看着像卡住了。
 */
const UNFINISHED = 'pending'

/**
 * 取**第一个还没执行的动作**的 key —— 轮询要盯的那个。
 *
 * 每轮都按新数据重新算，所以随着机器人往前跑，这个值会自动往后挪：
 * 第 1 个动作跑完了，下一轮就轮到第 2 个 —— 用户什么都不用点，
 * 界面自己跟着任务进度滚。
 *
 * 全部跑完时返回 `null`（调用方据此停轮询或显示"已全部执行完"）。
 */
export function firstPendingKey(nodes: LogTreeNode[]): string | null {
  const walk = (list: LogTreeNode[]): string | null => {
    for (const n of list) {
      if (n.kind === 'action') {
        if (n.action?.status === UNFINISHED) return n.key
        continue
      }
      const hit = walk(n.children)
      if (hit) return hit
    }
    return null
  }
  return walk(nodes)
}

/**
 * 收窄展开集：把目标节点的**祖先链**补进展开集，其余原样保留。
 *
 * 轮询跳到后面的节点时，如果那个节点所在的分支是折叠的，用户只看到"树没动"
 * （选中态在看不见的地方），像是轮询坏了。所以每次跳转都要把它这条链展开。
 *
 * 返回值与入参引用相同时说明不需要变 —— 调用方可以直接跳过 `setState`，
 * 避免每 5 秒白刷一次导致整棵树重渲染。
 */
export function expandTo(nodes: LogTreeNode[], key: string | null, expanded: string[]): string[] {
  if (!key) return expanded
  const path: string[] = []
  const walk = (list: LogTreeNode[], trail: string[]): boolean => {
    for (const n of list) {
      if (n.key === key) { path.push(...trail); return true }
      if (walk(n.children, [...trail, n.key])) return true
    }
    return false
  }
  if (!walk(nodes, [])) return expanded
  const have = new Set(expanded)
  const add = path.filter((k) => !have.has(k))
  return add.length ? [...expanded, ...add] : expanded
}

/** 轮询到"没有未执行的动作了"时的提示文案（给工具栏/摘要条用）。 */
export function allDoneText(actions: ActionResultRow[]): string {
  if (!actions.length) return '没有动作数据'
  const pending = actions.filter((a) => a.status === UNFINISHED).length
  if (pending) return `还有 ${pending} 个动作未执行`
  const failed = actions.filter((a) => a.status === 'failed').length
  return failed ? `已全部执行完 · ${failed} 个失败` : '已全部执行完'
}

/* ------------------------------------------------------------------ */
/*  右键菜单：展开/收缩（子树 / 含自己）                                  */
/* ------------------------------------------------------------------ */

/**
 * 收集节点自身及其**所有后代**里能展开的 key（有子节点的才算）。
 *
 * ⚠️ 只收"有子节点"的：Semi `Tree` 的 `expandedKeys` 里塞一个叶子 key 是无害的，
 * 但它会一直留在集合里 —— 折叠叶子再展开父节点时，这些无效 key 会让
 * "展开和收缩的 key 集合"比较变得没意义。只放真的能展开的，语义更干净。
 *
 * ⚠️ 不含目标节点自己 —— 那是 `selfKeys` 的事。"展开子树（不含自己）"的意思是
 * "把它的后代理开，但保持它自己原来的状态"，两者刻意分开。
 */
export function subtreeKeys(nodes: LogTreeNode[], key: string | null): string[] {
  const node = findNode(nodes, key)
  if (!node) return []
  const out: string[] = []
  const walk = (n: LogTreeNode) => {
    for (const c of n.children) {
      if (c.children.length) { out.push(c.key); walk(c) }
    }
  }
  walk(node)
  return out
}

/**
 * 节点自身（**仅当它自己有子节点时**）的 key。
 *
 * 用来做"展开/收缩自己（含自己）"：把 `[自身, ...子树的展开 key]` 一起
 * 加进 / 移出展开集，效果就是"这一个节点连它下面整棵树一起开合"。
 * 叶子节点返回空表 —— 叶子没有"展开自己"这回事，菜单项应该置灰。
 */
export function selfKeys(nodes: LogTreeNode[], key: string | null): string[] {
  const node = findNode(nodes, key)
  if (!node || !node.children.length) return []
  return [node.key]
}

/**
 * 把一个 key 集合整体**加进**展开集（去重、保序、原有项不动）。
 *
 * 保序很重要：`expandedKeys` 的数组顺序不影响渲染，但反复 setState 时
 * 顺序稳定能让 React 的 diff 更省事，也让调试输出可比对。
 * 无需变更（全都已展开）时**返回同一引用** —— 调用方可跳过 `setState`。
 */
export function addExpanded(expanded: string[], keys: string[]): string[] {
  const have = new Set(expanded)
  const add = keys.filter((k) => !have.has(k))
  return add.length ? [...expanded, ...add] : expanded
}

/**
 * 把一个 key 集合从展开集里**移除**（其余项原样保留）。
 *
 * ⚠️ 移的是**这一批 key**，不是"清空"：收缩一个楼层不该把别的楼层也收掉。
 * 同样在无需变更时返回同一引用。
 */
export function removeExpanded(expanded: string[], keys: string[]): string[] {
  const drop = new Set(keys)
  const out = expanded.filter((k) => !drop.has(k))
  return out.length === expanded.length ? expanded : out
}

/** 该节点当前是否处于展开态（判断菜单里该显示"展开"还是"收缩"）。 */
export function isExpanded(expanded: string[], key: string | null): boolean {
  return !!key && expanded.includes(key)
}
