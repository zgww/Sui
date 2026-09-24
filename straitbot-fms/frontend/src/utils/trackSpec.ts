/**
 * 轨道节点（TrackNode）在 prefab spec 里的读写 —— **纯函数，无 React 依赖**。
 *
 * ## 为什么单独抽出来
 *
 * 轨道在 spec 里是**平铺**的：TrackNode 的 children 里按顺序混着
 * `TrackEndpointNode`（端点）与 `TrackControlNode`（控制点），
 * **顺序本身就是语义**——两个端点之间夹着的控制点归属于这一段。
 * 控制点写反（放到端点之后）曲线会完全不同，而且不报错、只是"画歪了"，
 * 属于最难查的那类 bug。所以这些写入规则必须能被回归脚本直接验证，
 * 不能埋在组件的事件处理器里。
 *
 * 这里的函数一律**返回新数组**而不改动入参，深拷贝策略交给调用方
 * （页面里统一 `JSON.parse(JSON.stringify(spec))`，与既有写法一致）。
 */
import type { Pt, TrackNodePoint } from '../components/trackGeometry'

export const SEP = '/'

export const TRACK_TYPE = 'TrackNode'
export const ENDPOINT_TYPE = 'TrackEndpointNode'
export const CONTROL_TYPE = 'TrackControlNode'
export const CLOSE_TYPE = 'ClosePathNode'

/** 子节点路径：父路径 + children + 下标 */
export function childPath(parentPath: string, index: number): string {
  return `${parentPath}${SEP}children${SEP}${index}`
}

/** 父路径：去掉末尾的 "/children/N" */
export function parentPathOf(path: string): string {
  return path.split(SEP).slice(0, -2).join(SEP)
}

/** 数组里某类型节点的数量（用于生成"端点 3"这类默认名） */
export function countOfType(children: any[], type: string): number {
  return (children || []).filter((c) => c?.type === type).length
}

/**
 * 取"当前轨道"：优先选中节点所属的那条，否则第一条。
 *
 * 选中判定用 `key === selected` 或 `selected 以 key + '/' 开头`，
 * 后者覆盖"选中的是轨道下的端点/控制点"这种情况——否则用户在树里点了某个
 * 端点，地图却还停在第一条轨道上，画出来的点会落到别的轨道里。
 */
export function pickTrackPath(
  tracks: { key: string }[],
  selectedPath: string,
): string | null {
  if (!tracks.length) return null
  const owner = tracks.find(
    ({ key }) => selectedPath === key || selectedPath.startsWith(`${key}${SEP}`),
  )
  return owner ? owner.key : tracks[0].key
}

/**
 * 轨道节点 -> 地图要的平铺点。
 *
 * 只认**直接子节点**：端点与控制点就在这一层，更深层的东西一律不解析，
 * 免得误把别的节点当成控制点画进曲线。坐标不是有限数的直接跳过——
 * 宁可少画一个点，也不要把 NaN 带进采样让整条曲线消失。
 */
export function trackNodesOf(trackPath: string, trackNode: any): TrackNodePoint[] {
  const kids: any[] = trackNode?.children || []
  return kids.flatMap((child, i): TrackNodePoint[] => {
    // 闭合标记没有坐标，给 0 占位即可——解析只看 kind
    if (child?.type === CLOSE_TYPE) {
      return [{ kind: 'close', path: childPath(trackPath, i), x: 0, y: 0 }]
    }
    if (child?.type !== ENDPOINT_TYPE && child?.type !== CONTROL_TYPE) return []
    const x = Number(child.properties?.x)
    const y = Number(child.properties?.y)
    if (!Number.isFinite(x) || !Number.isFinite(y)) return []
    return [{
      kind: child.type === ENDPOINT_TYPE ? 'endpoint' : 'control',
      path: childPath(trackPath, i),
      x,
      y,
    }]
  })
}

/**
 * 闭合标记在 children 里的下标（没有则返回 -1）。
 *
 * 端点/控制点必须排在它**之前**：一旦闭合标记后面还跟着端点，
 * "最后一个端点连回第一个端点"就连错了对象。
 */
export function closeIndexOf(children: any[]): number {
  return (children || []).findIndex((c) => c?.type === CLOSE_TYPE)
}

/** 坐标按 3 位小数收敛，避免拖动时往 spec 里塞一长串浮点噪声 */
export function roundPt(p: Pt): Pt {
  return { x: Number(p.x.toFixed(3)), y: Number(p.y.toFixed(3)) }
}

/** 生成点位节点的 properties：schema 默认值 + 名称 + 坐标 */
export function pointProps(
  defaults: Record<string, any> | undefined,
  name: string,
  p: Pt,
): Record<string, any> {
  return { ...(defaults || {}), name, ...roundPt(p) }
}

export interface AppendResult {
  /** 追加后的新 children（不改动入参） */
  children: any[]
  /** 新节点的路径，顺序与写入顺序一致 */
  paths: string[]
}

/** 追加一个端点：与上一个端点之间是直线段 */
export function appendEndpoint(
  children: any[],
  trackPath: string,
  p: Pt,
  defaults?: Record<string, any>,
): AppendResult {
  const list = (children || []).slice()
  // 闭合标记之前——它是"路径到此为止"的哨兵，端点不能排到它后面
  const ci = closeIndexOf(list)
  const index = ci >= 0 ? ci : list.length
  const n = countOfType(list, ENDPOINT_TYPE) + 1
  list.splice(index, 0, { type: ENDPOINT_TYPE, properties: pointProps(defaults, `端点 ${n}`, p) })
  return { children: list, paths: [childPath(trackPath, index)] }
}

/**
 * 追加"控制点 + 端点"。
 *
 * **顺序就是语义**：控制点必须先入队，它夹在上一个端点与新端点之间，
 * 归属于这一段（解析规则见 `trackGeometry.parseTrackNodes`）。
 * 写反了不报错，只是曲线画歪——所以这里把顺序固定在一个地方，
 * 并由 `scripts/verify-track-spec.mjs` 锁住。
 */
export function appendEndpointWithControl(
  children: any[],
  trackPath: string,
  control: Pt,
  endpoint: Pt,
  controlDefaults?: Record<string, any>,
  endpointDefaults?: Record<string, any>,
): AppendResult {
  const list = (children || []).slice()
  // 同样插在闭合标记之前
  const closeAt = closeIndexOf(list)
  const ci = closeAt >= 0 ? closeAt : list.length
  const ei = ci + 1
  const nCtrl = countOfType(list, CONTROL_TYPE) + 1
  const nEnd = countOfType(list, ENDPOINT_TYPE) + 1
  list.splice(ci, 0, {
    type: CONTROL_TYPE,
    properties: pointProps(controlDefaults, `控制点 ${nCtrl}`, control),
  })
  list.splice(ei, 0, {
    type: ENDPOINT_TYPE,
    properties: pointProps(endpointDefaults, `端点 ${nEnd}`, endpoint),
  })
  return {
    children: list,
    paths: [childPath(trackPath, ci), childPath(trackPath, ei)],
  }
}

/** 路径自身及其所有祖先，由长到短（用于"向上找最近的轨道"） */
export function ancestorPaths(path: string): string[] {
  const out: string[] = [path]
  let cur = path
  while (cur.includes(SEP)) {
    cur = parentPathOf(cur)
    if (!cur) break
    out.push(cur)
  }
  return out
}

/**
 * 从某个节点向上找**最近的轨道**。
 *
 * 端点/控制点只有在 TrackNode 的**直接子节点**里才有效（平铺约定）。
 * 用户在树上选中一个端点再点"添加子节点"时，若直接挂成它的子级，
 * 新节点就成了孙节点 —— 地图上读不到，表现为"加了却看不见"。
 * 所以统一往上归到它所属的那条轨道。
 */
export function nearestTrackPath(
  flat: { key: string; node: any }[],
  fromPath: string,
): string | null {
  const trackKeys = new Set(
    (flat || []).filter(({ node }) => node?.type === TRACK_TYPE).map(({ key }) => key),
  )
  for (const p of ancestorPaths(fromPath)) {
    if (trackKeys.has(p)) return p
  }
  return null
}

export interface Placement {
  /** 插入下标（-1 表示追加到末尾由调用方决定，这里总是给具体值） */
  index: number
  point: Pt
}

/**
 * 已有相邻端点的**平均间距 (m)**，不足两个端点时返回 null。
 *
 * 新增端点的默认外扩距离按它取，而不是写死一个常数：世界坐标是米，一条真实
 * 轨道可能只有几十米，写死 100 米会让新点一下甩到视野外（那是"默认轨道
 * 1000 宽"时代留下的数）。用平均段长则天然贴合当前轨道的尺度。
 */
export function meanSegmentMeters(children: any[]): number | null {
  const pts: Pt[] = []
  for (const n of children || []) {
    if (n?.type !== ENDPOINT_TYPE) continue
    const x = Number(n.properties?.x)
    const y = Number(n.properties?.y)
    if (Number.isFinite(x) && Number.isFinite(y)) pts.push({ x, y })
  }
  if (pts.length < 2) return null
  let sum = 0
  for (let i = 1; i < pts.length; i++) {
    sum += Math.hypot(pts[i].x - pts[i - 1].x, pts[i].y - pts[i - 1].y)
  }
  const mean = sum / (pts.length - 1)
  return mean > 1e-6 ? mean : null
}

/**
 * 同层兄弟的**平均 x 间距 (m)**，不足两个有效 x 时返回 null。
 *
 * 给航点这类"x 就是沿轨米数"的节点用：它不像端点那样有 y 参与，
 * 间距就是相邻 x 之差；只看 x 也就不要求兄弟是端点类型。
 */
export function meanXGapMeters(children: any[]): number | null {
  const xs: number[] = []
  for (const n of children || []) {
    const x = Number(n?.properties?.x)
    if (Number.isFinite(x)) xs.push(x)
  }
  if (xs.length < 2) return null
  let sum = 0
  for (let i = 1; i < xs.length; i++) sum += Math.abs(xs[i] - xs[i - 1])
  const mean = sum / (xs.length - 1)
  return mean > 1e-6 ? mean : null
}

/** 默认外扩距离 (m)：贴合当前尺度（端点看平均段长、航点看平均 x 间距），都没得看时给 10 m */
const DEFAULT_SPAN_M = 10

/**
 * 新增端点的落位：追加到末尾，坐标接在最后一个点之后。
 *
 * 不默认 (0,0)：轨道已有内容时新点会**叠在原点**，看起来像"没加上"。
 */
export function placeNewEndpoint(children: any[], span?: number): Placement {
  const list = children || []
  let last: Pt | null = null
  for (let i = list.length - 1; i >= 0; i--) {
    const n = list[i]
    if (n?.type !== ENDPOINT_TYPE && n?.type !== CONTROL_TYPE) continue
    const x = Number(n.properties?.x)
    const y = Number(n.properties?.y)
    if (Number.isFinite(x) && Number.isFinite(y)) { last = { x, y }; break }
  }
  // 必须插在闭合标记之前，否则闭合连回的就是新端点而不是首端点
  const ci = closeIndexOf(list)
  const step = span ?? meanSegmentMeters(list) ?? DEFAULT_SPAN_M
  return {
    index: ci >= 0 ? ci : list.length,
    point: last ? { x: last.x + step, y: last.y } : { x: 0, y: 0 },
  }
}

/**
 * 通用版「紧贴目标插入」的下标：before = idx，after = idx + 1。
 *
 * 给**非轨道系**节点用（航点、动作点…）：它们没有"控制点归属"这种顺序语义，
 * 只要保证插在目标紧邻位置就行，不需要 insertBeside 那套坐标/闭合规则。
 */
export function siblingInsertIndex(
  children: any[],
  idx: number,
  side: 'before' | 'after',
): number | null {
  const list = children || []
  if (!Number.isInteger(idx) || idx < 0 || idx >= list.length) return null
  const i = side === 'before' ? idx : idx + 1
  return Math.min(i, list.length)
}

/**
 * 通用版「紧贴目标插入」的落位，坐标取**相邻兄弟的中点**。
 *
 * 用于航点这类带 x 的节点：在航点序列中间插一个时，x 落在左右邻居中间，
 * 树序与地图上的左右顺序才一致（否则新点会跑到列表末尾，看起来像"没加对位置"）。
 * 邻居没有可用 x 时按 span 外扩。没有相邻兄弟（插在首/末）同理外扩。
 *
 * span 不传时取兄弟的平均 x 间距（米）——写死常数在几十米长的轨道上
 * 会把新航点甩到视野外。
 */
export function insertBesidePoint(
  children: any[],
  idx: number,
  side: 'before' | 'after',
  span?: number,
): Placement | null {
  const list = children || []
  const index = siblingInsertIndex(list, idx, side)
  if (index === null) return null
  const step = span ?? meanXGapMeters(list) ?? DEFAULT_SPAN_M

  const xOf = (i: number): number | null => {
    const v = Number(list[i]?.properties?.x)
    return Number.isFinite(v) ? v : null
  }
  let prev: number | null = null
  for (let i = idx - 1; i >= 0; i--) { const v = xOf(i); if (v !== null) { prev = v; break } }
  let next: number | null = null
  for (let i = idx + 1; i < list.length; i++) { const v = xOf(i); if (v !== null) { next = v; break } }
  const self = xOf(idx) ?? 0

  let x: number
  if (side === 'before') x = prev !== null ? (prev + self) / 2 : self - step
  else x = next !== null ? (self + next) / 2 : self + step

  return { index, point: { x, y: Number(list[idx]?.properties?.y) || 0 } }
}

export interface BesideOpts {
  /** 没有相邻端点时的外扩距离（米）；不传则取当前轨道的平均段长 */
  span?: number
  /** 控制点的"抬升"：落点再往上抬一点，一眼能看出这段变弯了 */
  lift?: number
}

/**
 * 在某个已有子节点的**紧邻前 / 紧邻后**插入新节点的落位。
 *
 * 给「在前 / 后添加子节点」用：只往末尾追加的话，想在轨道中段加个折点
 * 就只能先加再一路拖，端点一多根本没法用。
 *
 * 坐标取**相邻端点的中点**，新点落在两段中间，曲线不会突然甩出去；
 * 插在首端点之前 / 末端点之后时没有相邻端点，就沿 x 外扩 span。
 *
 * 关于下标：`before = idx`、`after = idx + 1`，也就是**紧贴**目标节点。
 * 目标两侧已有的控制点保持原下标不动，于是归属按数组顺序自然重划分
 * ——这是有意为之：用户看到的就是"在这个点旁边加了一个点"，
 * 而不是"系统悄悄挪走了我原来的控制点"。
 */
export function insertBeside(
  children: any[],
  idx: number,
  side: 'before' | 'after',
  opts: BesideOpts = {},
): Placement | null {
  const list = children || []
  if (!Number.isInteger(idx) || idx < 0 || idx >= list.length) return null
  const span = opts.span ?? meanSegmentMeters(list) ?? DEFAULT_SPAN_M
  const lift = opts.lift ?? 0

  const at = (i: number): Pt => ({
    x: Number(list[i]?.properties?.x) || 0,
    y: Number(list[i]?.properties?.y) || 0,
  })
  let prev = -1
  for (let i = idx - 1; i >= 0; i--) {
    if (list[i]?.type === ENDPOINT_TYPE) { prev = i; break }
  }
  let next = -1
  for (let i = idx + 1; i < list.length; i++) {
    if (list[i]?.type === ENDPOINT_TYPE) { next = i; break }
  }

  const self = at(idx)
  let point: Pt
  if (side === 'before') {
    point = prev >= 0
      ? { x: (at(prev).x + self.x) / 2, y: (at(prev).y + self.y) / 2 }
      : { x: self.x - span, y: self.y }
  } else {
    point = next >= 0
      ? { x: (self.x + at(next).x) / 2, y: (self.y + at(next).y) / 2 }
      : { x: self.x + span, y: self.y }
  }
  if (lift) point = { x: point.x, y: point.y - lift }

  // 闭合标记必须是最后一个子节点：新节点不能插到它后面
  const ci = closeIndexOf(list)
  let index = side === 'before' ? idx : idx + 1
  if (ci >= 0 && index > ci) index = ci

  return { index: Math.min(Math.max(index, 0), list.length), point }
}

/**
 * 新增控制点的落位：插到**最后一个端点之前**。
 *
 * 控制点只有在两个端点之间才有意义。若直接追加到末尾（最后一个子节点是端点），
 * 它会落在最后一段之后被解析丢弃（`parseTrackNodes` 丢弃尾部控制点），
 * 同样表现为"加了却没反应"。
 * 轨道上不足两个端点时返回 null —— 没有段可归属，此时不该让用户加。
 */
export function placeNewControl(children: any[], lift = 60): Placement | null {
  const list = children || []
  const ends: number[] = []
  list.forEach((n, i) => { if (n?.type === ENDPOINT_TYPE) ends.push(i) })
  if (ends.length < 2) return null

  const li = ends[ends.length - 1]
  const pi = ends[ends.length - 2]
  const at = (i: number): Pt => ({
    x: Number(list[i].properties?.x) || 0,
    y: Number(list[i].properties?.y) || 0,
  })
  const ci = closeIndexOf(list)

  /**
   * 成环的轨道：控制点要归到**闭合那一段**（末端点 -> 首端点），
   * 所以插在末端点**之后**（而不是之前），弦取"末端点 -> 首端点"。
   * 没成环时仍插在最后一个端点之前，归到最后一段。
   */
  if (ci >= 0) {
    const b = at(li)
    const a = at(ends[0])
    return {
      index: Math.min(li + 1, ci),
      point: { x: (a.x + b.x) / 2, y: (a.y + b.y) / 2 - lift },
    }
  }

  const a = at(pi)
  const b = at(li)
  return {
    index: li,
    // 落在这一段弦的中点上方，一眼能看出"这段变弯了"
    point: { x: (a.x + b.x) / 2, y: (a.y + b.y) / 2 - lift },
  }
}

/** 把某个子节点挪到新坐标（返回新数组；找不到就原样返回） */
export function withMovedPoint(children: any[], index: number, p: Pt): any[] {
  const list = (children || []).slice()
  const node = list[index]
  if (!node) return list
  list[index] = {
    ...node,
    properties: { ...(node.properties || {}), ...roundPt(p) },
  }
  return list
}
