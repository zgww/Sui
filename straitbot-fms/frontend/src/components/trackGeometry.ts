/**
 * 轨道曲线数学 + 画布命中测试（纯函数，便于回归测试）。
 *
 * 背景：挂轨机器人是**单轴**的，航点的 `x` 是「沿轨弧长」(m)，`y` 恒为 0。
 * 因此这里没有真实二维地图，轨道曲线纯粹是**可视化**——把一维弧长铺开成一条
 * 可编辑的贝塞尔曲线，方便排布与观察。曲线控制点**不写回**任何航点坐标。
 *
 * ## 单位：全局统一为**米**两套坐标共用一把尺子
 *
 * - **世界坐标**（轨道端点/控制点、图标标记、背景锚点、网格刻度）单位是米。
 *   轨道画多长就是多少米，`sampleTrack().total` 即轨道真实长度 (m)。
 * - **沿轨弧长** `x`（航点 / 充电桩 / RFID 卡 / 区段中心）也是米，指从轨道
 *   **起点**算起的弧长。它与世界坐标是同一把尺子，换算只有一条：
 *      `u = x / 轨道总长(m)`，`x = u * 轨道总长(m)`
 *   于是"航点 22.5 m"就画在离起点 22.5 m 的曲线位置，网格读数也对得上。
 *
 * 曾经这里有两套单位（世界坐标是"示意单位"、航点 x 走 min-max 归一化），
 * 表现为"航点 x 才 22.5，怎么画在刻度 1900 的地方"。已统一为米，
 * **不要再退回 min-max 归一化**——那会让 x 的绝对值失去意义。
 */

/** 曲线控制点：p 为曲线经过的点，c1/c2 为两侧手柄（绝对坐标） */
export interface TrackPoint {
  p: { x: number; y: number }
  c1: { x: number; y: number }
  c2: { x: number; y: number }
}

export interface Pt { x: number; y: number }

/**
 * 地图上显示的航点：由航点节点的 `x`（沿轨弧长，m）除以轨道总长得到 `u`。
 * 注意 `x` 只是**排布依据**——曲线本身与该坐标无关，纯可视化。
 */
export interface MapWaypoint {
  /** 树中的节点路径，用于与树选中联动 */
  path: string
  /** 沿轨弧长 (m) */
  x: number
  /** 归一化到 [0,1] 的位置参数 */
  u: number
  label: string
  type: string
}

/** 沿轨设施（充电桩 / RFID 卡）——与航点共用 `x`（沿轨弧长 m）定位，只是画法不同 */
export type MarkerKind = 'charging' | 'rfid'

export interface MapMarker {
  /** 树中的节点路径，用于与树选中联动 */
  path: string
  kind: MarkerKind
  /** 沿轨弧长 (m)，与航点 `x` 同一坐标系 */
  x: number
  label: string
}

/**
 * 沿轨**区段**标记（门 / 窗 / 减速…）：给一段轨道加注记。
 *
 * 与充电桩/RFID 卡的区别：那两个是**点**，区段是 `[x - 半径, x + 半径]`
 * 一段**区间**，画成贴在轨道曲线上的一条彩色带。
 * 同样是纯注记，不参与任何运行时决策。
 */
export interface MapSection {
  /** 树中的节点路径，用于与树选中联动 */
  path: string
  /** 中心弧长 (m)，与航点 `x` 同一坐标系 */
  x: number
  /** 半径 (m)：沿轨向两侧各延伸多少 */
  radius: number
  /** 十六进制颜色（节点属性，空则由前端兜底） */
  color: string
  label: string
}

/**
 * **图标**标记：地图任意位置放一个可配置的内置矢量图标（门 / 电梯 / 消防栓…）。
 *
 * 与充电桩 / RFID / 区段的区别：那三个都挂在轨道上（靠弧长 `x` 定位），
 * 图标用的是**地图世界坐标 x/y**，可以摆在背景图的任意位置，没有轨道时也能摆。
 * 造型 `icon` 取自 `mapIcons.ts` 的内置图标表，`size` 是屏幕像素（不随缩放变）。
 */
export interface MapIcon {
  /** 树中的节点路径，用于与树选中联动 */
  path: string
  /** 世界坐标 X (m)（与轨道端点同一坐标系） */
  x: number
  /** 世界坐标 Y (m) */
  y: number
  /** 图标 key 或中文名（非法值由 normalizeIconKey 兜底） */
  icon: string
  /** 十六进制颜色（节点属性，空则由前端兜底） */
  color: string
  /** 显示大小（屏幕像素） */
  size: number
  label: string
}

/**
 * 区段在轨道上覆盖的 u 区间（按弧长 ÷ 轨道总长换算）。
 *
 * 轨道长度缺失（没画轨道 / total 为 0）时返回 null（画不出区间）——
 * **不能退化成 0**，否则所有区段会堆到轨道起点，看起来像"加了但都叠在一起"。
 */
export function sectionRange(
  trackLengthM: number,
  sec: { x: number; radius: number },
): { u0: number; u1: number } | null {
  if (!(trackLengthM > 0) || !Number.isFinite(sec.x)) return null
  const r = Number.isFinite(sec.radius) ? Math.max(0, sec.radius) : 0
  const a = xToU(trackLengthM, sec.x - r)
  const b = xToU(trackLengthM, sec.x + r)
  return { u0: Math.min(a, b), u1: Math.max(a, b) }
}

/**
 * 取 `[u0, u1]` 之间均匀铺开的曲线点，画区段带用。
 *
 * 退化为一点时返回两个相同点：配合 `lineCap = 'round'` 能画出一个圆点，
 * 至少让"半径为 0 的区段"还看得见（而不是整段消失）。
 */
export function sectionPoints(
  sampled: { pts: Pt[]; cum: number[]; total: number },
  u0: number, u1: number, per = 24,
): Pt[] {
  const a = Math.max(0, Math.min(1, u0))
  const b = Math.max(0, Math.min(1, u1))
  const n = Math.max(2, Math.min(Math.floor(per), 64))
  const out: Pt[] = []
  for (let i = 0; i <= n; i++) {
    out.push(pointAtFraction(sampled, a + (b - a) * (i / n)))
  }
  return out
}

/** 地图背景图：铺在最底层的一张底图（照着它画轨道 / 摆航点） */
export interface MapBackground {
  /** 树中节点路径（写回微调结果用） */
  path: string
  /** 图片地址：/data/calibration/background/xxx.png 或 http(s) 链接 */
  src: string
  /** 锚点：**图片左上角**对应的世界坐标 (m) */
  x: number
  y: number
  /** 1 图片像素 = 多少米（图片按自身宽高 × scale 铺开，不拉伸变形） */
  scale: number
  /** 0~1，太大就会盖住轨道 */
  opacity: number
}

/** 背景图在世界坐标里占的矩形（图片没加载出来时算不出来，返回 null） */
export function backgroundRect(
  bg: MapBackground, imgW: number, imgH: number,
): Rect | null {
  if (!Number.isFinite(bg.x) || !Number.isFinite(bg.y)) return null
  if (!Number.isFinite(bg.scale) || bg.scale <= 0) return null
  if (!(imgW > 0) || !(imgH > 0)) return null
  return { x: bg.x, y: bg.y, w: imgW * bg.scale, h: imgH * bg.scale }
}

/**
 * 拖背景图右下角手柄时的新缩放：让对角跟着指针走。
 *
 * 横竖各算一次**取大者**——斜着拖两者本该接近，取大可以容忍手抖
 * （取小会让图一抖就缩回去）。算不出来就保持原值，绝不返回 NaN
 * （NaN 会让 `drawImage` 直接抛，整张地图一起白屏）。
 */
export function backgroundScaleAt(
  bg: MapBackground, imgW: number, imgH: number, corner: Pt, minScale = 0.001,
): number {
  if (!(imgW > 0) || !(imgH > 0)) return bg.scale
  const sx = (corner.x - bg.x) / imgW
  const sy = (corner.y - bg.y) / imgH
  const s = Math.max(sx, sy)
  if (!Number.isFinite(s)) return bg.scale
  return Math.max(minScale, s)
}

export interface Rect { x: number; y: number; w: number; h: number }

/**
 * 造一段默认轨道：一条占满宽度的水平线，等分成 n-1 段。
 * 每段的控制点放在两端连线的 1/3、2/3 处 —— 水平线上这些点与 p 重合，
 * 但一旦拖动 p 就能立刻看出曲线效果。
 */
export function defaultTrack(count = 4, width = 1000, y = 0): TrackPoint[] {
  const n = Math.max(2, Math.floor(count))
  const pts: TrackPoint[] = []
  for (let i = 0; i < n; i++) {
    pts.push({ p: { x: (width * i) / (n - 1), y }, c1: { x: 0, y }, c2: { x: 0, y } })
  }
  recomputeHandles(pts)
  return pts
}

/**
 * 重算曲线手柄，使曲线平滑穿过每个 p 点。
 *
 * 用 Fritsch-Carlson 的**保单调**思路限制手柄长度，而不是照搬 Catmull-Rom：
 * 直接把 `前后邻点跨度 / 3` 当手柄，端点处手柄会伸到区间之外（c1 落到起点左边），
 * 曲线在那里往回勾一下——既让采样弧长虚长（实测直线会算成 1.3 倍），
 * 也会把附近的航点排到轨道外面。这里对手柄做限幅：
 *
 * - 端点取该段自身长度的 1/3（方向指向唯一邻点）；
 * - 中间点用标准 Catmull-Rom 切线，但**不超过相邻两段长的 1/3**；
 * - 拖动手柄（c1/c2 离开默认位置）时用 `pinned` 标记跳过，保留手工调整。
 *
 * 这样一条水平直线采样出来的弧长就等于两端实际距离，航点才能均匀铺满。
 */
export function recomputeHandles(pts: TrackPoint[], pinned?: boolean[]): TrackPoint[] {
  const n = pts.length
  if (n < 2) return pts
  const T = 1 / 3

  for (let i = 0; i < n; i++) {
    if (pinned?.[i]) continue
    const px = pts[i].p.x
    const py = pts[i].p.y

    // c1 控制「前一段」的入场方向，c2 控制「后一段」的出场方向。
    // 两侧必须**分别限幅**：手柄各自不得超过自己那一段的长度 1/3。
    // 用两段中较短者统一限幅是错的——长段会被短段拖短、短段的手柄又可能
    // 伸出到段外，曲线于是先冲过去再勾回来，采样弧长虚长、x 还会非单调。
    if (i > 0) {
      const ax = px - pts[i - 1].p.x
      const ay = py - pts[i - 1].p.y
      const prevLen = Math.hypot(ax, ay)
      let hx: number
      let hy: number
      if (i === n - 1) {
        hx = ax * T
        hy = ay * T
      } else {
        hx = (pts[i + 1].p.x - pts[i - 1].p.x) * T
        hy = (pts[i + 1].p.y - pts[i - 1].p.y) * T
        const limit = prevLen * T
        const len = Math.hypot(hx, hy)
        if (len > limit && len > 1e-9) { hx *= limit / len; hy *= limit / len }
      }
      pts[i].c1 = { x: px - hx, y: py - hy }
    } else {
      // 首点没有来向：c1 退化到点自身，否则曲线会在起点往回勾
      pts[i].c1 = { x: px, y: py }
    }

    if (i < n - 1) {
      const bx = pts[i + 1].p.x - px
      const by = pts[i + 1].p.y - py
      const nextLen = Math.hypot(bx, by)
      let hx: number
      let hy: number
      if (i === 0) {
        hx = bx * T
        hy = by * T
      } else {
        hx = (pts[i + 1].p.x - pts[i - 1].p.x) * T
        hy = (pts[i + 1].p.y - pts[i - 1].p.y) * T
        const limit = nextLen * T
        const len = Math.hypot(hx, hy)
        if (len > limit && len > 1e-9) { hx *= limit / len; hy *= limit / len }
      }
      pts[i].c2 = { x: px + hx, y: py + hy }
    } else {
      pts[i].c2 = { x: px, y: py }
    }
  }
  return pts
}

/** 单个三次贝塞尔段上 t 处的点 */
export function cubicAt(p0: Pt, c1: Pt, c2: Pt, p1: Pt, t: number): Pt {
  const mt = 1 - t
  const a = mt * mt * mt
  const b = 3 * mt * mt * t
  const c = 3 * mt * t * t
  const d = t * t * t
  return {
    x: a * p0.x + b * c1.x + c * c2.x + d * p1.x,
    y: a * p0.y + b * c1.y + c * c2.y + d * p1.y,
  }
}

/**
 * 把整条轨道按段采样成折线，同时记录每段的累计弧长，
 * 供「按弧长定位航点」使用。
 */
/**
 * @param closed 成环时额外采样「最后一个点 -> 第一个点」这一段。
 *   闭合段在数组里**不是相邻的两个点**，只按相邻对采样会把它漏掉，
 *   环就断了一截（看着像一条开口的弧线）。
 */
export function sampleTrack(
  pts: TrackPoint[],
  perSeg = 24,
  closed = false,
): { pts: Pt[]; cum: number[]; total: number } {
  const out: Pt[] = []
  const cum: number[] = []
  let total = 0
  if (pts.length < 2) return { pts: out, cum, total }

  const addSeg = (a: TrackPoint, b: TrackPoint) => {
    for (let s = 1; s <= perSeg; s++) {
      // 一段三次贝塞尔由「起点 + 起点的出手柄 c2 + 终点的入手柄 c1 + 终点」构成。
      // 这里若误用 a.c1 当第一控制点，画出来的就不是同一条曲线，
      // 采样弧长会明显偏大（实测水平直线会算成 1.12 倍）。
      const pt = cubicAt(a.p, a.c2, b.c1, b.p, s / perSeg)
      const prev = out[out.length - 1]
      total += Math.hypot(pt.x - prev.x, pt.y - prev.y)
      out.push(pt)
      cum.push(total)
    }
  }

  out.push({ ...pts[0].p })
  cum.push(0)
  for (let i = 0; i < pts.length - 1; i++) addSeg(pts[i], pts[i + 1])
  if (closed) addSeg(pts[pts.length - 1], pts[0])
  return { pts: out, cum, total }
}

/**
 * 按归一化弧长比例 u∈[0,1] 在采样折线上取点（含切线方向）。
 * 这样航点能沿曲线均匀铺开，而不是按控制点的段号扎堆。
 */
export function pointAtFraction(sampled: { pts: Pt[]; cum: number[]; total: number }, u: number): Pt & { angle: number } {
  const { pts, cum, total } = sampled
  if (!pts.length) return { x: 0, y: 0, angle: 0 }
  if (pts.length === 1 || total <= 0) return { ...pts[0], angle: 0 }

  const target = Math.max(0, Math.min(1, u)) * total
  // 二分找到 target 落在哪一段
  let lo = 0
  let hi = cum.length - 1
  while (lo < hi) {
    const mid = (lo + hi) >> 1
    if (cum[mid] < target) lo = mid + 1
    else hi = mid
  }
  const i = Math.max(1, lo)
  const segLen = cum[i] - cum[i - 1]
  const t = segLen > 1e-9 ? (target - cum[i - 1]) / segLen : 0
  const a = pts[i - 1]
  const b = pts[i]
  return {
    x: a.x + (b.x - a.x) * t,
    y: a.y + (b.y - a.y) * t,
    angle: Math.atan2(b.y - a.y, b.x - a.x),
  }
}

/** 点到线段的距离（用于「点在轨道上」判定与命中） */
export function distToSegment(p: Pt, a: Pt, b: Pt): number {
  const dx = b.x - a.x
  const dy = b.y - a.y
  const len2 = dx * dx + dy * dy
  if (len2 < 1e-12) return Math.hypot(p.x - a.x, p.y - a.y)
  let t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / len2
  t = Math.max(0, Math.min(1, t))
  return Math.hypot(p.x - (a.x + t * dx), p.y - (a.y + t * dy))
}

/**
 * 求点在线段上的**最近点参数 t**（0~1）。
 * 右键在轨道上添加航点时，需要知道落点对应的弧长比例，就用它。
 */
export function closestT(p: Pt, a: Pt, b: Pt): number {
  const dx = b.x - a.x
  const dy = b.y - a.y
  const len2 = dx * dx + dy * dy
  if (len2 < 1e-12) return 0
  const t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / len2
  return Math.max(0, Math.min(1, t))
}

/** 采样折线上离 p 最近的位置：`u` 归一化弧长比例，`dist` 到折线的距离 */
function nearestOnTrack(
  sampled: { pts: Pt[]; cum: number[]; total: number },
  p: Pt,
): { u: number; dist: number } | null {
  const { pts, cum } = sampled
  if (pts.length < 2) return null
  let best = Infinity
  let bestU = 0
  for (let i = 0; i < pts.length - 1; i++) {
    const t = distToSegment(p, pts[i], pts[i + 1])
    if (t < best) {
      best = t
      const segLen = cum[i + 1] - cum[i]
      const localT = closestT(p, pts[i], pts[i + 1])
      bestU = cum[i] + segLen * localT
    }
  }
  const total = cum[cum.length - 1]
  return { u: total > 0 ? bestU / total : 0, dist: best }
}

/**
 * 轨道上离 p 最近的位置（**不看阈值**），返回归一化弧长 u。
 *
 * 拖拽用这个而不是 `hitTrack`：拖拽时指针常常不在轨道上（尤其是把点往轨道
 * 外侧推开的时候），带阈值的话一离开轨道投影就断掉、点会卡住不动。
 */
export function nearestU(
  sampled: { pts: Pt[]; cum: number[]; total: number },
  p: Pt,
): number | null {
  const r = nearestOnTrack(sampled, p)
  return r ? r.u : null
}

/**
 * 命中轨道，返回归一化弧长比例 u（0~1）；不在阈值内返回 null。
 * 用采样折线求最近段，够快也够准。
 */
export function hitTrack(
  sampled: { pts: Pt[]; cum: number[]; total: number },
  p: Pt,
  tolerance: number,
): number | null {
  const r = nearestOnTrack(sampled, p)
  if (!r || r.dist > tolerance) return null
  return r.u
}

/** 矩形与矩形是否相交（框选） */
export function rectsIntersect(
  a: { x: number; y: number; w: number; h: number },
  b: { x: number; y: number; w: number; h: number },
): boolean {
  return a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y
}

/** 把一串点归一化到 [0,1] 的 u 值（按数组顺序当轨道顺序） */
export function evenFractions(count: number): number[] {
  if (count <= 0) return []
  if (count === 1) return [0.5]
  return Array.from({ length: count }, (_, i) => i / (count - 1))
}

/**
 * 沿轨弧长 x (m) -> 归一化位置 u∈[0,1]。
 *
 * 除以**轨道总长 (m)**，而不是对所有航点做 min-max 归一化：
 * 世界坐标就是米，轨道画出来多长就是多少米，所以 x 的绝对值本身有意义——
 * 22.5 m 就该落在离起点 22.5 m 的地方，而不是"在所有航点里排第几"。
 * min-max 那套会让网格刻度上的米数与航点 x 对不上（曾经的 bug：
 * x=22.5 的航点被画到刻度 1900 的位置）。
 *
 * 超出轨道范围时**夹取**到 0/1（贴在端点），不抛错也不溢出。
 * 轨道长度为 0/非法时返回 0——没画轨道时本来也无处可放。
 */
export function xToU(trackLengthM: number, x: number): number {
  if (!Number.isFinite(trackLengthM) || trackLengthM <= 0) return 0
  if (!Number.isFinite(x)) return 0
  const u = x / trackLengthM
  return u < 0 ? 0 : u > 1 ? 1 : u
}

/**
 * 归一化位置 u -> 沿轨弧长 (m)。
 *
 * `xToU` 的逆运算，同样夹取到 [0, 轨道总长]。
 * 拖航点/充电桩落位后要把 u 写回节点的 `x`，就用它——因为量程是**轨道总长**
 * 这个与数据无关的固定量，写进去再读出来一定还是同一个 u，不需要任何
 * "除自己之外的极值反推"之类的补偿。
 */
export function uToX(trackLengthM: number, u: number): number {
  if (!Number.isFinite(trackLengthM) || trackLengthM <= 0) return 0
  const t = Number.isFinite(u) ? Math.max(0, Math.min(1, u)) : 0
  return t * trackLengthM
}

/**
 * 没画轨道时的兜底量程 (m)：取最远的沿轨点 x，但不小于 `FALLBACK_MIN_M`。
 *
 * 退化成一条水平线时用它当轨道长度，于是 x=55 m 的点就画在离起点 55 m 处，
 * 刻度读数仍与航点 x 对得上。给下限是因为只有一两个点时跨度会趋近 0，
 * 视口会被"适应窗口"放大到离谱的倍率。
 */
export const FALLBACK_MIN_M = 10

export function fallbackLengthM(xs: number[]): number {
  const ok = xs.filter((v) => Number.isFinite(v) && v > 0)
  return Math.max(ok.length ? Math.max(...ok) : 0, FALLBACK_MIN_M)
}

/**
 * 里程 (m)：有轨道用采样弧长，没有就退回兜底量程。
 *
 * 地图内部与页面侧（新建沿轨节点时把 u 反推成 x）都必须用它取量程，
 * 否则两边各算一把尺子，新加的点会落在别的地儿。
 */
export function trackLengthOf(sampledTotal: number, xs: number[]): number {
  return Number.isFinite(sampledTotal) && sampledTotal > 0
    ? sampledTotal
    : fallbackLengthM(xs)
}

/** 在一串已排序的 u 上找与目标 u 最接近的下标（用于"定位到航点"） */
export function nearestIndex(sortedUs: number[], u: number): number {
  if (!sortedUs.length) return -1
  let best = 0
  let bestD = Infinity
  for (let i = 0; i < sortedUs.length; i++) {
    const d = Math.abs(sortedUs[i] - u)
    if (d < bestD) { bestD = d; best = i }
  }
  return best
}

/** 把矩形规范化为 x/y/w/h（左上角 + 正宽高），框选时起止点顺序不定 */
export function normalizeRect(a: Pt, b: Pt): Rect {
  return {
    x: Math.min(a.x, b.x),
    y: Math.min(a.y, b.y),
    w: Math.abs(b.x - a.x),
    h: Math.abs(b.y - a.y),
  }
}

/* ---------------------------------------------------------------- 视口 */

/**
 * 2D 视口变换：世界坐标（米）↔ 屏幕坐标。
 *
 * 用「缩放 + 平移」而不是"每次重算把整条曲线塞进画布"：
 * 后者在缩放/平移后无法保持稳定——用户滚一下轮子，视图就重新自适应回原位了。
 *
 * 约定：
 * - `scale` 是世界->屏幕的倍率（px per world unit）。>1 放大。
 * - `offset` 是**世界坐标原点**在屏幕上的落点（px）。缩放围绕它做数学，
 *   具体绕哪个点缩放由 `zoomAt` 负责换算，保证"鼠标下的世界点不动"。
 */
export interface Viewport {
  scale: number
  offset: Pt
}

export const MIN_SCALE = 0.08
export const MAX_SCALE = 40

/** 世界坐标 -> 屏幕坐标 */
export function worldToScreen(vp: Viewport, p: Pt): Pt {
  return { x: p.x * vp.scale + vp.offset.x, y: p.y * vp.scale + vp.offset.y }
}

/** 屏幕坐标 -> 世界坐标 */
export function screenToWorld(vp: Viewport, p: Pt): Pt {
  return { x: (p.x - vp.offset.x) / vp.scale, y: (p.y - vp.offset.y) / vp.scale }
}

/** 平移视口（屏幕像素增量） */
export function panBy(vp: Viewport, dx: number, dy: number): Viewport {
  return { scale: vp.scale, offset: { x: vp.offset.x + dx, y: vp.offset.y + dy } }
}

/**
 * 以**按下时的视口**为基准，按"从按下点到当前点的总屏幕位移"求新视口。
 *
 * 与 `panBy` 的区别在于这是**绝对**计算而不是增量累加。拖动时应当用它：
 * `vp` 是 React state，同一帧里连着来了两个 mousemove 的话，第二次读到的
 * `prev` 还是旧值，增量累加会把前一次的位移丢掉，快速拖动时画面明显追不上
 * 鼠标。按住起点算总量则天然幂等，重复调用同一坐标也给出同一结果。
 */
export function panFrom(base: Viewport, startScreen: Pt, nowScreen: Pt): Viewport {
  return panBy(base, nowScreen.x - startScreen.x, nowScreen.y - startScreen.y)
}

/** 视口是否真的变了（拖动收尾时用，避免无谓的 setState） */
export function sameViewport(a: Viewport, b: Viewport): boolean {
  return a.scale === b.scale && a.offset.x === b.offset.x && a.offset.y === b.offset.y
}

/* ---------------------------------------------------- 轨道节点 -> 曲线 */

/**
 * 平铺在 TrackNode.children 里的节点（端点 / 控制点）。
 *
 * 坐标就是地图的世界坐标，单位是**米**（画多长就是多少米）。
 * `path` 是它在树里的节点路径，供地图与树做选中联动；控制点也需要，
 * 因为它可以被单独选中拖动。
 */
export interface TrackNodePoint {
  kind: 'endpoint' | 'control' | 'close'
  path: string
  x: number
  y: number
}

/** 由平铺节点解析出的一段路径 */
export interface TrackSegment {
  /** 段起点（端点）下标，指向 `endpoints` */
  a: number
  /** 段终点（端点）下标 */
  b: number
  /**
   * 这一段夹着的控制点（按出现顺序，通常 0~2 个）。
   * 保留完整节点而不是只留坐标——控制点要能被单独选中/拖动，
   * 需要它自己在树里的 `path`。
   */
  controls: TrackNodePoint[]
}

/**
 * 把 TrackNode.children 里的**平铺**节点解析成「端点序列 + 每段的控制点」。
 *
 * 规则（与后端 waypoint.py 的平铺约定一致）：
 * 扫描时以上一个端点为段起点，两个端点之间夹着的 TrackControlNode
 * 全部归属于这一段；出现在**第一个端点之前**的控制点无段可归属，直接丢弃
 * （树里允许这种"游离"状态，解析时必须能容忍，否则整条轨道会画不出来）。
 *
 * **闭合（成环）**：如果 children 里出现 `kind === 'close'` 的闭合标记，
 * 就额外补一段「最后一个端点 -> 第一个端点」，控制点取排在末端点之后、
 * 闭合标记之前的那些。**没有闭合标记时末端点之后的控制点会被丢弃**
 * （没有段可归属），所以闭合标记不只是"画个圈"，它还决定了这些控制点归谁。
 * 闭合之后 current 回到第一个端点（已经绕回来了），后续端点继续往后接。
 *
 * 至少要 2 个端点闭合才有意义（1 个点闭合等于原地打转，段是零长度）。
 */
export function parseTrackNodes(nodes: TrackNodePoint[]): {
  endpoints: TrackNodePoint[]
  segments: TrackSegment[]
  /** 被丢弃的游离控制点（第一个端点之前的），供上层提示 */
  orphans: TrackNodePoint[]
  /** 是否成环（children 里有闭合标记） */
  closed: boolean
} {
  const endpoints: TrackNodePoint[] = []
  const segments: TrackSegment[] = []
  const orphans: TrackNodePoint[] = []
  let closed = false

  let openIdx = -1 // 当前段的起点在 endpoints 里的下标；-1 = 还没遇到端点
  let pending: TrackNodePoint[] = []

  for (const n of nodes) {
    if (n.kind === 'close') {
      // 末端点连回首端点；不足两个端点时这段没意义，跳过（pending 也随之丢弃）
      if (openIdx >= 1) {
        segments.push({ a: openIdx, b: 0, controls: pending })
        closed = true
        openIdx = 0 // 已经绕回起点，后续端点从起点继续往后接
      }
      pending = []
      continue
    }
    if (n.kind === 'control') {
      if (openIdx < 0) orphans.push(n)
      else pending.push(n)
      continue
    }
    // 端点
    const idx = endpoints.length
    endpoints.push(n)
    if (openIdx >= 0) segments.push({ a: openIdx, b: idx, controls: pending })
    pending = []
    openIdx = idx
  }

  return { endpoints, segments, orphans, closed }
}

/**
 * 段内控制点 -> 贝塞尔的两个手柄。
 *
 * 三种情况统一用**三次**贝塞尔表达，这样采样代码完全不用改：
 * - 0 个：直线段——两个手柄各自退化到端点自身（否则会往回勾、弧长虚长）；
 * - 1 个：二次——该点兼作出手柄与入手柄；
 * - ≥2 个：三次——第一个作起点的出手柄，第二个作终点的入手柄（多余忽略）。
 */
export function handlesOf(
  seg: { a: { x: number; y: number }; b: { x: number; y: number }; controls: { x: number; y: number }[] },
): { c1: Pt; c2: Pt } {
  const { a, b, controls } = seg
  /**
   * 注意谁归谁：`c2` 是**段起点 a** 的出手柄，`c1` 是**段终点 b** 的入手柄
   * （采样时一段写成 `cubicAt(a.p, a.c2, b.c1, b.p, t)`）。
   * 所以退化时 c2 落在 a 自己身上、c1 落在 b 自己身上——写反了虽然对纯直线
   * 段看起来一样（两点共线时曲线仍重合于该线段），但语义是错的，
   * 一旦有 y 差就会画出一条"先冲出去再回来"的怪曲线。
   */
  if (!controls.length) return { c1: { x: b.x, y: b.y }, c2: { x: a.x, y: a.y } }
  if (controls.length === 1) return { c1: { ...controls[0] }, c2: { ...controls[0] } }
  return { c1: { ...controls[1] }, c2: { ...controls[0] } }
}

/**
 * 平铺节点 -> `TrackPoint[]`（可直接喂给 `sampleTrack`）。
 *
 * 每个端点得到一个 TrackPoint，其 c1/c2 由**左右两段**分别决定：
 * c2（出手柄）取自它作为起点的那一段，c1（入手柄）取自它作为终点的那一段。
 * 两端没有邻段时手柄退化到自身——与 `recomputeHandles` 的端点约定一致。
 *
 * 注意：这里**不**调用 `recomputeHandles`。控制点坐标是用户显式摆的，
 * 平滑重算会把它覆盖掉，那就失去"控制点"的意义了。
 */
export function trackPointsFromNodes(nodes: TrackNodePoint[]): TrackPoint[] {
  const { endpoints, segments } = parseTrackNodes(nodes)
  if (!endpoints.length) return []

  const out: TrackPoint[] = endpoints.map((e) => ({
    p: { x: e.x, y: e.y },
    c1: { x: e.x, y: e.y },
    c2: { x: e.x, y: e.y },
  }))

  for (const seg of segments) {
    const a = endpoints[seg.a]
    const b = endpoints[seg.b]
    const { c1, c2 } = handlesOf({ a, b, controls: seg.controls })
    out[seg.a].c2 = c2
    out[seg.b].c1 = c1
  }

  return out
}

/**
 * 右键"拖拽 vs 点击"的判定阈值（屏幕像素）。
 *
 * 判定必须放在 **mouseup** 上做：右键的 down/up/contextmenu 顺序跨平台
 * 不一致（Windows 是 down→up→contextmenu，macOS 是 down→contextmenu→up），
 * 而"到底拖没拖"只有到 mouseup 才确定得下来。
 */
export function isDrag(start: Pt, end: Pt, threshold = 3): boolean {
  return Math.hypot(end.x - start.x, end.y - start.y) > threshold
}

/**
 * 以屏幕上某点为锚点缩放。
 *
 * 关键不变量：**锚点下方的世界坐标在缩放前后必须不变**。
 * 做法是先记住锚点对应的世界点，缩放后反解出新的 offset，
 * 使它重新映射到同一屏幕位置。少了这一步，滚轮缩放会"跑偏"。
 */
export function zoomAt(vp: Viewport, anchorScreen: Pt, factor: number): Viewport {
  // 先挡住非法倍率：`Math.max/min` 遇到 NaN 会原样传出 NaN，
  // 一旦写进 viewport，之后每次变换都是 NaN，整张图会彻底消失（且无法自愈）。
  if (!Number.isFinite(factor) || factor <= 0) return vp
  if (!Number.isFinite(anchorScreen.x) || !Number.isFinite(anchorScreen.y)) return vp
  const nextScale = Math.max(MIN_SCALE, Math.min(MAX_SCALE, vp.scale * factor))
  // 已经顶到缩放边界就不用算了，避免无意义的漂移
  if (nextScale === vp.scale) return vp
  const anchorWorld = screenToWorld(vp, anchorScreen)
  return {
    scale: nextScale,
    offset: {
      x: anchorScreen.x - anchorWorld.x * nextScale,
      y: anchorScreen.y - anchorWorld.y * nextScale,
    },
  }
}

/**
 * 计算能把给定世界包围盒完整装进视口（留 pad 边距）的视口。
 * 用于"适应窗口"按钮与首次进入。
 */
export function fitViewport(
  bounds: Rect,
  size: { w: number; h: number },
  pad = 40,
): Viewport {
  const availW = Math.max(1, size.w - pad * 2)
  const availH = Math.max(1, size.h - pad * 2)
  // 退化包围盒（宽度或高度为 0，例如直线轨道）不能直接相除，给个兜底尺寸
  const bw = bounds.w > 1e-6 ? bounds.w : 1
  const bh = bounds.h > 1e-6 ? bounds.h : 1
  const raw = Math.min(availW / bw, availH / bh)
  const scale = Math.max(MIN_SCALE, Math.min(MAX_SCALE, raw))
  const cx = bounds.x + bounds.w / 2
  const cy = bounds.y + bounds.h / 2
  return {
    scale,
    offset: { x: size.w / 2 - cx * scale, y: size.h / 2 - cy * scale },
  }
}

/** 一组点的包围盒；空输入返回 null */
export function boundsOf(points: Pt[]): Rect | null {
  if (!points.length) return null
  let minX = Infinity
  let minY = Infinity
  let maxX = -Infinity
  let maxY = -Infinity
  for (const p of points) {
    if (!Number.isFinite(p.x) || !Number.isFinite(p.y)) continue
    if (p.x < minX) minX = p.x
    if (p.y < minY) minY = p.y
    if (p.x > maxX) maxX = p.x
    if (p.y > maxY) maxY = p.y
  }
  if (!Number.isFinite(minX)) return null
  return { x: minX, y: minY, w: maxX - minX, h: maxY - minY }
}

/**
 * 视口下的屏幕像素 -> 世界坐标的容差换算。
 * 命中测试给的是屏幕像素（"离 12px 内算点中"），但几何运算在世界坐标里，
 * 所以要把像素容差除以 scale 换到世界尺度，否则放大后命中范围会变得极小。
 */
export function pixelTolerance(vp: Viewport, px: number): number {
  return px / vp.scale
}

/**
 * 生成"好看的"网格步长（1/2/5 × 10^n）。
 * 目标是在屏幕上大约每 `targetPx` 像素画一条线，避免缩放后网格过密或过疏。
 */
export function niceStep(vp: Viewport, targetPx = 80): number {
  const raw = targetPx / vp.scale
  const mag = 10 ** Math.floor(Math.log10(Math.max(raw, 1e-9)))
  for (const m of [1, 2, 5, 10]) {
    if (mag * m >= raw) return mag * m
  }
  return mag * 10
}

/**
 * 长度显示格式：按量级选精度（大的省小数位，小的留住有效位），**带 ` m` 后缀**。
 *
 * 世界坐标与沿轨弧长都是米，所以统一带单位。不带单位的那版曾经让人把
 * 网格刻度读成"米"以外的东西，反过来又把航点的米数当成刻度值对比。
 * 非有限数/0 统一显示 `—`（没画轨道时 total 就是 0，会走这条）。
 */
export function formatLength(v: number): string {
  if (!Number.isFinite(v) || v === 0) return '—'
  const abs = Math.abs(v)
  const digits = abs >= 100 ? 0 : abs >= 1 ? 1 : 2
  return `${v.toFixed(digits)} m`
}

/**
 * 一组数值的跨度文本 `min~max`（用于把航点的"沿轨弧长"显示成区间）。
 * 少于两个有效值返回空串——一个点没有跨度可言。
 */
export function spanText(xs: number[], fmt = formatLength): string {
  const ok = xs.filter((v) => Number.isFinite(v))
  if (ok.length < 2) return ''
  return `${fmt(Math.min(...ok))} ~ ${fmt(Math.max(...ok))}`
}
