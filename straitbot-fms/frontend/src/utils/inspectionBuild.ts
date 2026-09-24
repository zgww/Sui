/**
 * 航点树 <-> 巡检任务 JSON 的组装与 ID 生成 —— **纯函数，无 React 依赖**。
 *
 * ## 为什么单独一个文件
 *
 * 巡检任务是要**下发给真机**的：字段写错不会在本地报错，而是机器人走到一半
 * 才发现动作类型不对、测点框丢了。这类逻辑必须能被回归脚本直接验证，
 * 不能埋在组件的事件处理器里。
 *
 * ## 与后端导入的对称性
 *
 * `backend/app/prefab/waypoint_import.py` 的 `inspection_to_spec` 是
 * "巡检任务 -> 树"；这里是它的反向。两边的字段命名刻意一一对应：
 *
 * | 巡检任务 JSON            | 航点树节点字段                                    |
 * |--------------------------|---------------------------------------------------|
 * | `waypoint[].id`          | `WaypointNode.wp_id`                              |
 * | `waypoint[].index`       | `WaypointNode.index`（这里按树中顺序重新编号）    |
 * | `pose.point.x/y/z`       | `WaypointNode.x/y/z`                              |
 * | `pose.theta`             | `WaypointNode.theta`                              |
 * | `action[].id`            | `ActionPointNode.action_id`                       |
 * | `action[].type`          | `ActionPointNode.action_type`                     |
 * | `action[].duration`      | `ActionPointNode.duration_ms`                     |
 * | `action[].ptz_param.*`   | `ActionPointNode.pan/tilt/zoom/focal_len/focus`   |
 * | `thermometry_points[].id`| `MeasurePointNode.point_id`                       |
 *
 * **楼层**：`WaypointNode.floor` 是航点自己的字段（导入巡检任务时由楼层段写进去），
 * 组装时**优先读它**；老 spec 没有这个字段才退回从祖先分组名 `楼层N` 里回解
 * （那段兼容逻辑见 `floorOfPath`），再解不出来用 `DEFAULT_FLOOR`。
 */
import { SEP } from './trackSpec'

/** 分组名解不出楼层时的兜底值 */
export const DEFAULT_FLOOR = 1

/** 巡检任务 id 的长度（与后端 tests/test_inspection.json 里的 32 位 hex 一致） */
export const ID_HEX_LEN = 32

/* ------------------------------------------------------------------ ID 生成 */

/**
 * 随机十六进制串。
 *
 * 走 `crypto.getRandomValues`（**不**要求安全上下文，http 站点也能用；
 * 只有 `crypto.subtle` 才要求 https）。拿不到时退回 `Math.random`——
 * 巡检 id 只要求"和别人不一样"，不要求密码学强度，宁可退化也别抛异常。
 */
export function randomHex(len: number = ID_HEX_LEN): string {
  const n = Math.max(0, Math.floor(len))
  const bytes = Math.ceil(n / 2)
  try {
    const buf = new Uint8Array(bytes)
    crypto.getRandomValues(buf)
    return Array.from(buf, (b) => b.toString(16).padStart(2, '0')).join('').slice(0, n)
  } catch {
    let s = ''
    while (s.length < n) s += Math.floor(Math.random() * 16).toString(16)
    return s.slice(0, n)
  }
}

/**
 * 递归给一棵子树重新生成业务 id（航点 / 动作 / 测点 / 检测框）。
 *
 * **只在粘贴时用**：复制出来的子树如果沿用原 id，两处会指向同一个航点，
 * 下发巡检后机器人的 `current_waypoint_id` 分不清走到了哪一份。
 *
 * ⚠️ **检测框也要重生成**（`box_id`）：它不是"下发给机器人的动作 id"，
 * 而是**算法回调时认回本框**的键。两个框共用同一个 box_id，回调结果就会
 * 被两边抢着写（后到的覆盖先到的），而树上看不出任何异常。
 *
 * 传入的 node 会被**原地修改**（调用方传的都是刚 parse 出来的深拷贝）。
 * 返回新生成的 id 个数，便于提示用户。
 */
export function regenerateIds(node: any): number {
  if (!node || typeof node !== 'object') return 0
  let n = 0
  /* 缺 properties 的畸形节点也要补上：粘贴一份"没有 properties 的航点"
     会让它在下发时连 id 都没有，所以宁可给它造一个对象。 */
  const field = node.type === 'WaypointNode' ? 'wp_id'
    : node.type === 'ActionPointNode' ? 'action_id'
      : node.type === 'MeasurePointNode' ? 'point_id'
        : node.type === 'DetectBoxNode' ? 'box_id'
          : null
  if (field) {
    if (!node.properties || typeof node.properties !== 'object') node.properties = {}
    node.properties[field] = randomHex()
    n++
  }
  for (const c of Array.isArray(node.children) ? node.children : []) {
    n += regenerateIds(c)
  }
  return n
}

/**
 * 给**没有** `box_id` 的检测框补一个（原地改 spec），返回补了几个。
 *
 * 老数据（`box_id` 字段加进来之前编的树）打开时框是匿名的 —— 下发推理任务时
 * 报文里 box_id 为空，算法结果回来就认不回是哪个框（后端 `to_inspection_json`
 * 虽然会现摇一个，但**摇出来的不写回树**，同一棵树每次 build 都是新 id）。
 * 所以在**加载后 / 保存前**各补一次，把它落盘。
 *
 * 已经有 id 的**不覆盖**：box_id 是稳定标识，重新生成等于把历史结果全部解绑。
 */
export function ensureBoxIds(node: any): number {
  if (!node || typeof node !== 'object') return 0
  let n = 0
  if (node.type === 'DetectBoxNode') {
    if (!node.properties || typeof node.properties !== 'object') node.properties = {}
    if (!String(node.properties.box_id || '').trim()) {
      node.properties.box_id = randomHex()
      n++
    }
  }
  for (const c of Array.isArray(node.children) ? node.children : []) {
    n += ensureBoxIds(c)
  }
  return n
}

/* ------------------------------------------------------------------ 楼层判定 */

/** 从分组名里回解楼层：导入时写的是 `楼层{floor}` */
export function floorFromName(name: any, fallback: number = DEFAULT_FLOOR): number {
  const m = /楼层\s*(-?\d+)/.exec(String(name ?? ''))
  if (!m) return fallback
  const v = Number(m[1])
  return Number.isFinite(v) ? v : fallback
}

/**
 * 航点所属楼层：从**最近**的祖先分组名里解，一直向外找。
 *
 * 之所以逐级向外：导入生成的树是 `任务 > 楼层N > 航点`，但用户可能自己再套一层
 * 分组（`任务 > 楼层1 > 区域A > 航点`），这时楼层在再外一层。
 */
export function floorOfPath(spec: any, path: string, fallback: number = DEFAULT_FLOOR): number {
  const parts = String(path || '').split(SEP)
  // 从最内层往外剥：root/children/0/children/2 -> 依次试 root/children/0、root
  for (let i = parts.length - 2; i >= 1; i -= 2) {
    const anc = parts.slice(0, i).join(SEP)
    const node = nodeAt(spec, anc)
    if (node?.type === 'GroupNode') {
      const m = /楼层\s*(-?\d+)/.exec(String(node.properties?.name ?? ''))
      if (m) return Number(m[1])
    }
  }
  return fallback
}

/**
 * 一个航点的楼层：**航点自己写的 `floor` 说了算**，没有才去祖先分组名里解。
 *
 * 为什么自己的字段优先：分组名是给人看的（`楼层1` / `区域A`），改个名就解不出来，
 * 而 `floor` 是导入时按**楼层段**写进去的、也可以在检视器里改——它是数据，名字不是。
 *
 * 0 和负数都算数（0 层、地下室 -1），所以判"有没有写"要跟判"是多少"分开：
 * `Number(undefined)` 是 NaN、`Number(null)` 是 0，但 null 是**没写**而不是"0 层"。
 */
export function floorOfWaypoint(
  spec: any, path: string, node: any, fallback: number = DEFAULT_FLOOR,
): number {
  const raw = node?.properties?.floor
  if (raw !== undefined && raw !== null && raw !== '') {
    const v = Number(raw)
    if (Number.isFinite(v)) return v
  }
  return floorOfPath(spec, path, fallback)
}

function nodeAt(spec: any, path: string): any {
  if (!spec) return null
  if (!path || path === 'root') return spec.root
  let cur: any = spec.root
  for (const seg of path.split(SEP)) {
    if (seg === 'root') continue
    if (seg === 'children') continue
    const i = Number(seg)
    if (!Number.isFinite(i) || !Array.isArray(cur?.children)) return null
    cur = cur.children[i]
    if (!cur) return null
  }
  return cur
}

/* ------------------------------------------------------------------ 收集航点 */

export interface PickedWaypoint {
  path: string
  node: any
  floor: number
}

/**
 * 按树的**先序遍历**收集若干子树里的所有航点。
 *
 * "按航点在树中的顺序"就是这个顺序——不是按 x 排序。树里的顺序是用户
 * 编排出来的执行顺序，x 只是几何位置，两者不必一致（回头路很常见）。
 *
 * 同一个航点被多条路径覆盖时只收一次（`seen`）：比如同时选中了分组和它下面的
 * 某个航点，否则会重复下发。
 */
export function collectWaypoints(spec: any, paths: string[]): PickedWaypoint[] {
  const seen = new Set<string>()
  const out: PickedWaypoint[] = []
  for (const p of paths) {
    walk(spec, p, out, seen)
  }
  return out
}

function walk(spec: any, path: string, out: PickedWaypoint[], seen: Set<string>): void {
  const node = nodeAt(spec, path)
  if (!node || seen.has(path)) return
  seen.add(path)
  if (node.type === 'WaypointNode') {
    out.push({ path, node, floor: floorOfWaypoint(spec, path, node) })
    return // 航点下面只有动作点/测点，不会再有航点
  }
  const kids: any[] = Array.isArray(node.children) ? node.children : []
  for (let i = 0; i < kids.length; i++) {
    walk(spec, `${path}${SEP}children${SEP}${i}`, out, seen)
  }
}

/* ------------------------------------------------------------------ 组装任务 */

function f(v: any, d: number = 0): number {
  const n = Number(v)
  return Number.isFinite(n) ? n : d
}

function i(v: any, d: number = 0): number {
  const n = Number(v)
  return Number.isFinite(n) ? Math.round(n) : d
}

/** 树上的动作点 -> 巡检任务 action */
export function actionToJson(node: any, freshId: boolean = false): any {
  const p = node?.properties || {}
  const type = i(p.action_type, 1)
  const pts: any[] = Array.isArray(node.children) ? node.children : []
  return {
    id: freshId || !p.action_id ? randomHex() : String(p.action_id),
    type,
    lift_height: f(p.lift_height),
    // duration 只有录像(type=3)用得上，其余动作给 0（缺字段后端默认也是 0）
    duration: type === 3 ? i(p.duration_ms) : 0,
    ptz_param: {
      focal_len: i(p.focal_len),
      focus: i(p.focus),
      pan: f(p.pan),
      tilt: f(p.tilt),
      zoom: f(p.zoom, 1),
    },
    steer_point_name: String(p.steer_point_name ?? ''),
    thermometry_points: pts
      .filter((c) => c?.type === 'MeasurePointNode')
      .map((c) => measurePointToJson(c, freshId)),
  }
}

/** 树上的测点 -> 巡检任务 thermometry_points 成员 */
export function measurePointToJson(node: any, freshId: boolean = false): any {
  const p = node?.properties || {}
  return {
    id: freshId || !p.point_id ? randomHex() : String(p.point_id),
    thermometry_param: {
      distance: i(p.distance),
      emissivity: f(p.emissivity, 0.96),
      enable_reflective: i(p.enable_reflective),
      reflective_temperature: f(p.reflective_temperature),
      rect: {
        x: f(p.rect_x), y: f(p.rect_y), w: f(p.rect_w), h: f(p.rect_h),
      },
    },
  }
}

/** 树上的航点 -> 巡检任务 waypoint */
export function waypointToJson(node: any, index: number, freshId: boolean = false): any {
  const p = node?.properties || {}
  const acts: any[] = Array.isArray(node.children) ? node.children : []
  return {
    id: freshId || !p.wp_id ? randomHex() : String(p.wp_id),
    index,
    pose: {
      point: { x: f(p.x), y: f(p.y), z: f(p.z) },
      theta: f(p.theta),
    },
    action: acts
      .filter((c) => c?.type === 'ActionPointNode')
      .map((c) => actionToJson(c, freshId)),
  }
}

export interface BuildOptions {
  /** 任务名；缺省用文件/时间兜底 */
  name?: string
  /** 强制生成新的航点/动作/测点 id（默认沿用树里的 id，缺了才补） */
  freshIds?: boolean
  /** 随机任务 id（测试时可注入固定值） */
  inspectionId?: string
  plan?: string
  substationMapsId?: string
}

export interface BuildResult {
  /** POST /api/rail/robot/inspection 的 body：楼层分段数组 */
  payload: any[]
  inspectionId: string
  waypointCount: number
  actionCount: number
  floors: number[]
}

/**
 * 把选中的航点组装成巡检任务 JSON。
 *
 * 输出是**楼层分段数组**（哪怕只有一个楼层），与 `tests/test_inspection.json`
 * 同构：后端 `InspectionTask.from_payload` 把同 id 的分段合并成一次巡检，
 * 并按 `(floor 升序, index 升序)` 遍历。
 *
 * ⚠️ `index` 是**楼层内**序号（从 1 递增，见 test_inspection.json），
 * 不是全局序号：后端排序键是 `(floor, index)`，全局编号在多楼层时会乱序。
 */
export function buildInspection(
  spec: any,
  paths: string[],
  opts: BuildOptions = {},
): BuildResult {
  const picked = collectWaypoints(spec, paths)
  const id = opts.inspectionId || randomHex()
  const plan = opts.plan || randomHex()
  const mapsId = opts.substationMapsId || randomHex()
  const name = opts.name || '航点树下发任务'

  // 按楼层分段，段内保持树中顺序
  const byFloor = new Map<number, PickedWaypoint[]>()
  for (const w of picked) {
    const arr = byFloor.get(w.floor)
    if (arr) arr.push(w)
    else byFloor.set(w.floor, [w])
  }
  const floors = [...byFloor.keys()].sort((a, b) => a - b)

  const payload = floors.map((fl) => ({
    floor: fl,
    id,
    name,
    plan,
    substationMapsId: mapsId,
    waypoint: (byFloor.get(fl) || []).map((w, i) => waypointToJson(w.node, i + 1, opts.freshIds)),
  }))

  return {
    payload,
    inspectionId: id,
    waypointCount: picked.length,
    actionCount: picked.reduce(
      (n, w) => n + (Array.isArray(w.node.children) ? w.node.children : [])
        .filter((c: any) => c?.type === 'ActionPointNode').length,
      0,
    ),
    floors,
  }
}
