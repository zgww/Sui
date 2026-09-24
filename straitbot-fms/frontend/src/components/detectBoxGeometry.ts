/**
 * 检测框（DetectBoxNode）的几何与坐标换算——**纯函数**，不碰 DOM。
 *
 * 与 `trackGeometry.ts` 同一套分层约定：画布组件（`DetectBoxTool.tsx`）只管
 * 画和收事件，凡是能脱离 DOM 验算的都放这里，回归脚本直接编出来跑。
 *
 * ## 坐标系
 *
 * 节点里存的是**归一化**坐标（0~1，相对抓拍图宽高），不是像素：
 * 换相机、换分辨率、重新拍一张不同尺寸的图，框都还在同一个位置。
 * 屏幕上画的时候才换算成像素——`normToScreen` / `screenToNorm` 是唯一入口，
 * 别在组件里手写 `x * width`，否则改一次布局就错位一次。
 *
 * ## 一个内部表示
 *
 * **矩形也是 4 个点**（轴对齐，顺序固定 左上→右上→右下→左下），所以画布
 * 只有"一串点"这一种表示，矩形/多边形共用绘制、命中测试与面积判定，
 * 不用分两套代码——分两套迟早有一边忘了同步。
 */
export interface NormPt {
  x: number
  y: number
}

/** 图片在画布上铺开的像素矩形（contain 适配，居中留边） */
export interface ImageRect {
  x: number
  y: number
  w: number
  h: number
}

/**
 * 把图片按 **contain** 铺进画布：等比缩放、居中，不裁不拉变形。
 *
 * 检测框是照着画面内容画的，一旦拉伸变形，框住的东西就对不上了——
 * 所以这里宁可留黑边也不能用 cover。
 */
export function fitImageRect(
  imgW: number, imgH: number, canvasW: number, canvasH: number,
): ImageRect {
  if (!(imgW > 0) || !(imgH > 0) || !(canvasW > 0) || !(canvasH > 0)) {
    return { x: 0, y: 0, w: 0, h: 0 }
  }
  const s = Math.min(canvasW / imgW, canvasH / imgH)
  const w = imgW * s
  const h = imgH * s
  return { x: (canvasW - w) / 2, y: (canvasH - h) / 2, w, h }
}

export function clamp01(v: number): number {
  if (!Number.isFinite(v)) return 0
  return v < 0 ? 0 : v > 1 ? 1 : v
}

export function clampNorm(p: NormPt): NormPt {
  return { x: clamp01(p.x), y: clamp01(p.y) }
}

/* ------------------------------------------------------------ 视口（平移 / 缩放）

   画布要能平移缩放，所以"归一化 -> 屏幕"中间必须夹一层视口，而不是直接
   拿 contain 出来的矩形算。世界坐标取**图片像素**：缩放系数 k 就是
   "1 图片像素 = 多少屏幕像素"，平移量 x/y 也是屏幕像素。
   （不拿归一化坐标当世界坐标，是因为那样 k 会随图片尺寸变，缩放手感不一致。）

   viewport 的基准由 `fitViewport` 给（contain），之后全靠 `panFrom` /
   `zoomAt` 生成新视口——**不要增量累加**（见 panFrom 的说明）。 */

export interface Viewport {
  /** 屏幕像素平移量 */
  x: number
  y: number
  /** 屏幕像素 / 图片像素 */
  k: number
}

/** contain 适配出的初始视口（还没平移缩放） */
export function fitViewport(
  imgW: number, imgH: number, canvasW: number, canvasH: number,
): Viewport {
  const r = fitImageRect(imgW, imgH, canvasW, canvasH)
  if (!(r.w > 0) || !(r.h > 0)) return { x: 0, y: 0, k: 1 }
  return { x: r.x, y: r.y, k: r.w / imgW }
}

/** 图片像素 -> 屏幕像素 */
export function worldToScreen(p: { x: number; y: number }, vp: Viewport) {
  return { x: p.x * vp.k + vp.x, y: p.y * vp.k + vp.y }
}

/** 屏幕像素 -> 图片像素 */
export function screenToWorld(p: { x: number; y: number }, vp: Viewport) {
  if (!(vp.k > 0)) return { x: 0, y: 0 }
  return { x: (p.x - vp.x) / vp.k, y: (p.y - vp.y) / vp.k }
}

/** 归一化 -> 图片像素 */
export function normToWorld(p: NormPt, imgW: number, imgH: number) {
  return { x: clamp01(p.x) * imgW, y: clamp01(p.y) * imgH }
}

/** 图片像素 -> 归一化（越界夹到 0~1） */
export function worldToNorm(p: { x: number; y: number }, imgW: number, imgH: number): NormPt {
  if (!(imgW > 0) || !(imgH > 0)) return { x: 0, y: 0 }
  return clampNorm({ x: p.x / imgW, y: p.y / imgH })
}

/** 归一化 -> 屏幕像素（画框与命中测试都走它，别在组件里手写 `x * width`） */
export function normToScreen(
  p: NormPt, vp: Viewport, imgW: number, imgH: number,
): { x: number; y: number } {
  return worldToScreen(normToWorld(p, imgW, imgH), vp)
}

/**
 * 屏幕像素 -> 归一化（**超出图片范围的部分夹到 0~1**）。
 *
 * 拖到画布边缘之外时夹一下，比"松手得到一个越界的框"友好；
 * 反过来说，落在留边区域里的点会被夹到图边，这也是符合直觉的。
 */
export function screenToNorm(
  p: { x: number; y: number }, vp: Viewport, imgW: number, imgH: number,
): NormPt {
  return worldToNorm(screenToWorld(p, vp), imgW, imgH)
}

/**
 * 平移：按**起点与当前点的绝对差**算，不是增量累加。
 *
 * 增量累加（`vp.x += dx`）会在同一帧收到两个 mousemove 时读到旧的 vp，
 * 丢掉一部分位移，表现为"拖快了画布跟不上手"。这里每次都从按下时的
 * 基准视口重算，天然免疫。
 */
export function panFrom(
  base: Viewport, start: { x: number; y: number }, now: { x: number; y: number },
): Viewport {
  return { ...base, x: base.x + (now.x - start.x), y: base.y + (now.y - start.y) }
}

/** 缩放上下限（相对 contain 的倍数）：再大也看不出细节，再小就找不回图了 */
export const ZOOM_MIN = 0.2
export const ZOOM_MAX = 20

/**
 * 以 `anchor`（屏幕像素）为中心缩放：锚点下的那个点保持不动。
 *
 * 直接改 k 而不补平移量的话，图会往左上角跑——滚轮缩放最常见的 bug。
 */
export function zoomAt(
  vp: Viewport, anchor: { x: number; y: number }, factor: number,
  fitK: number, minScale = ZOOM_MIN, maxScale = ZOOM_MAX,
): Viewport {
  const lo = (fitK > 0 ? fitK : 1) * minScale
  const hi = (fitK > 0 ? fitK : 1) * maxScale
  const k = Math.min(hi, Math.max(lo, vp.k * factor))
  const s = vp.k > 0 ? k / vp.k : 1
  return {
    k,
    x: anchor.x - (anchor.x - vp.x) * s,
    y: anchor.y - (anchor.y - vp.y) * s,
  }
}

/** 端点手柄的命中半径（屏幕像素） */
export const VERTEX_PX = 7
/** 超过这个位移才算"拖"，否则算"点"（右键靠它区分平移与弹菜单） */
export const DRAG_THRESHOLD_PX = 3

/** 位移是否算拖动（欧拉距离，不是分别比较 x/y——斜着拖 2+2px 也算） */
export function isDrag(a: { x: number; y: number }, b: { x: number; y: number }): boolean {
  return Math.hypot(b.x - a.x, b.y - a.y) > DRAG_THRESHOLD_PX
}

/**
 * 命中端点的下标（找不到返回 -1）。
 *
 * 只在**屏幕空间**比距离：放大后端点看起来更大，但手柄的"好点程度"应该
 * 保持不变（恒为 7px 见方），不然放大后得眯着眼点。
 */
export function hitVertexIndex(
  screen: { x: number; y: number }, pts: NormPt[],
  vp: Viewport, imgW: number, imgH: number, radius = VERTEX_PX,
): number {
  let best = -1
  let bestD = radius
  for (let i = 0; i < pts.length; i++) {
    const s = normToScreen(pts[i], vp, imgW, imgH)
    const d = Math.hypot(s.x - screen.x, s.y - screen.y)
    if (d <= bestD) { bestD = d; best = i }
  }
  return best
}

/** 整体平移一串顶点（越界夹回 0~1，避免把框拖出画面外再也找不着） */
export function translatePoints(pts: NormPt[], d: NormPt): NormPt[] {
  return pts.map((p) => clampNorm({ x: p.x + d.x, y: p.y + d.y }))
}

/**
 * 拖**矩形**的一个端点：只动它所在的横边与竖边，形状仍是轴对齐矩形。
 *
 * 直接改那一个点会把矩形拖成梯形——用户画的时候选的是"矩形"，拖完却不是
 * 矩形，属于最让人困惑的那类"我明明没做错什么"。所以矩形不走通用的
 * 「改单个点」，而是重算包围盒。
 *
 * 顶点归属按**它落在包围盒的哪一侧**判断（而不是第几个点），这样哪怕
 * 顶点顺序被人手改乱也照样对。
 *
 * 拖过对角会让矩形翻转——和常见画图软件一致，不是 bug。
 */
export function moveRectVertex(pts: NormPt[], i: number, to: NormPt): NormPt[] {
  if (pts.length !== 4) {
    // 不是 4 点就无所谓"保持矩形"了，退化成普通拖拽
    return pts.map((p, k) => (k === i ? clampNorm(to) : p))
  }
  const p = clampNorm(to)
  const xs = pts.map((q) => q.x)
  const ys = pts.map((q) => q.y)
  let x0 = Math.min(...xs)
  let x1 = Math.max(...xs)
  let y0 = Math.min(...ys)
  let y1 = Math.max(...ys)

  const v = pts[i]
  if (v.x <= (x0 + x1) / 2) x0 = p.x; else x1 = p.x
  if (v.y <= (y0 + y1) / 2) y0 = p.y; else y1 = p.y

  // rectPoints 内部再取一次 min/max，所以拖过对角翻转也是干净的矩形
  return rectPoints({ x: x0, y: y0 }, { x: x1, y: y1 })
}

/**
 * 拖拽两点 -> 轴对齐矩形的 4 个顶点（左上→右上→右下→左下）。
 *
 * 顺序固定，这样"第 0 点就是左上角"这件事在绘制标签、命中测试里都能直接用。
 */
export function rectPoints(a: NormPt, b: NormPt): NormPt[] {
  const x0 = Math.min(a.x, b.x)
  const x1 = Math.max(a.x, b.x)
  const y0 = Math.min(a.y, b.y)
  const y1 = Math.max(a.y, b.y)
  return [
    { x: x0, y: y0 },
    { x: x1, y: y0 },
    { x: x1, y: y1 },
    { x: x0, y: y1 },
  ]
}

/**
 * 多边形面积（鞋带公式，取绝对值）。
 *
 * 归一化坐标系下面积是个"占画面的比例"：0.01 就是画面 1%（1000×1000 图约
 * 100×100 像素）。矩形自然退化成 w*h，所以两种形状共用同一个阈值判定。
 */
export function polygonArea(pts: NormPt[]): number {
  const n = pts.length
  if (n < 3) return 0
  let s = 0
  for (let i = 0; i < n; i++) {
    const a = pts[i]
    const b = pts[(i + 1) % n]
    s += a.x * b.y - b.x * a.y
  }
  return Math.abs(s) / 2
}

/**
 * 太小就不算一个框（默认千分之四 ≈ 1000px 图上 20×20）。
 *
 * 没有这道闸，"手抖点一下"就会建出一个看不见的框，然后在列表里变成一个
 * 永远选不中的幽灵条目。
 */
export const MIN_BOX_AREA = 4e-4

export function isTinyBox(pts: NormPt[]): boolean {
  return polygonArea(pts) < MIN_BOX_AREA
}

/** 顶点序列的算术中心（放序号标签用；空数组给画面中心） */
export function boxCenter(pts: NormPt[]): NormPt {
  if (!pts.length) return { x: 0.5, y: 0.5 }
  let sx = 0
  let sy = 0
  for (const p of pts) { sx += p.x; sy += p.y }
  return { x: sx / pts.length, y: sy / pts.length }
}

/**
 * 射线法判点是否落在多边形内。
 *
 * 矩形是 4 点多边形，所以**命中测试也只有这一份**——矩形不需要单独的
 * bbox 判断。边界上（正好压在边上）的行为不做保证，画框用不到那么严。
 */
export function pointInPolygon(p: NormPt, poly: NormPt[]): boolean {
  let inside = false
  for (let i = 0, j = poly.length - 1; i < poly.length; j = i++) {
    const a = poly[i]
    const b = poly[j]
    // 只在 p 的 y 落在 [a.y, b.y) 半开区间时统计，避免顶点被重复计数
    if ((a.y > p.y) !== (b.y > p.y)) {
      const t = (p.y - a.y) / (b.y - a.y)
      if (p.x < a.x + t * (b.x - a.x)) inside = !inside
    }
  }
  return inside
}

/**
 * 命中的那个框在数组里的下标，**从后往前找**（后画的盖在上面，符合直觉）。
 * 没命中返回 -1。
 */
export function hitBoxIndex(p: NormPt, boxes: { points: NormPt[] }[]): number {
  for (let i = boxes.length - 1; i >= 0; i--) {
    if (pointInPolygon(p, boxes[i].points || [])) return i
  }
  return -1
}

/**
 * 去掉**连续重复**的顶点。
 *
 * 多边形是"点一下加一个点"，手抖连点两下会留下两个一模一样的顶点，
 * 画出来看不出问题，导出给算法时却多一个退化边。收尾时统一清一遍。
 */
export function dedupePoints(pts: NormPt[]): NormPt[] {
  const out: NormPt[] = []
  for (const p of pts) {
    const last = out[out.length - 1]
    if (last && Math.abs(last.x - p.x) < 1e-9 && Math.abs(last.y - p.y) < 1e-9) continue
    out.push(p)
  }
  // 首尾也重合时去掉尾点（闭合由绘制负责，不需要重复存一个点）
  const first = out[0]
  const last = out[out.length - 1]
  if (out.length > 1 && first && last
    && Math.abs(first.x - last.x) < 1e-9 && Math.abs(first.y - last.y) < 1e-9) {
    out.pop()
  }
  return out
}

/** 节点里的 `points` 可能是脏数据（缺字段 / 字符串 / null），统一洗成可用数组 */
export function sanitizePoints(raw: any): NormPt[] {
  if (!Array.isArray(raw)) return []
  const out: NormPt[] = []
  for (const p of raw) {
    const x = Number(p?.x)
    const y = Number(p?.y)
    if (Number.isFinite(x) && Number.isFinite(y)) out.push(clampNorm({ x, y }))
  }
  return out
}
