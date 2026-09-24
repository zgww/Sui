/**
 * 地图内置图标：20 个矢量图标，**不依赖任何图片资源**，直接用 canvas 画。
 *
 * 为什么不用图片 / 不用 Semi 的图标组件：
 * - 地图是 canvas，React 组件画不上去，SVG 要先转 Path2D 再缩放，链路长；
 * - 图标节点要能改颜色（同一个图标在不同区段是不同颜色），图片做不到；
 * - 内置在代码里就不会出现"文件丢了图标变问号"。
 *
 * 所以每个图标就是 24×24 设计网格上的一组**基本图形**（矩形 / 圆 / 多边形 /
 * 圆环 / 线段），`drawIcon` 按 size 缩放、按 color 上色后画到画布上。
 *
 * ⚠️ 两个约定：
 * 1. **图标是"空心轮廓 + 实心点缀"的画法**。因为所有图形都用同一个颜色填充，
 *    实心块上面再叠同色的实心块是**看不见的**（门框里画个同色的门把手等于没画）。
 *    所以主体一律画成"框"，只有需要突出的小部件（把手、眼珠、箭头）才实心。
 * 2. **这份清单与后端 `IconMarkNode.icon` 的选项必须一致**（后端存的是中文 label）。
 *    加图标时两边一起加，`scripts/verify-map-icons.mjs` 会比对，不一致会红。
 */

export type IconShape =
  /** 实心矩形 */
  | { t: 'rect'; x: number; y: number; w: number; h: number }
  /** 实心圆 */
  | { t: 'circle'; cx: number; cy: number; r: number }
  /** 实心多边形（首尾自动闭合） */
  | { t: 'poly'; pts: [number, number][] }
  /** 圆环（描边圆），用来画"禁止""齿轮"这类空心圆 */
  | { t: 'ring'; cx: number; cy: number; r: number; w: number }
  /** 线段（描边），三角形警示框就是三条线段围出来的 */
  | { t: 'line'; x0: number; y0: number; x1: number; y1: number; w: number }

export interface IconDef {
  /** 稳定标识：写进节点属性、跨语言可读 */
  key: string
  /** 中文名：给下拉框和后端 select 用 */
  label: string
  shapes: IconShape[]
}

/** 设计网格边长：所有坐标都在这个 24×24 的盒子里 */
export const ICON_GRID = 24

export const DEFAULT_ICON_KEY = 'pin'
export const DEFAULT_ICON_COLOR = '#0068FF'
export const DEFAULT_ICON_SIZE = 24
export const ICON_MIN_SIZE = 12
export const ICON_MAX_SIZE = 64

export const ICONS: IconDef[] = [
  {
    key: 'door', label: '门', shapes: [
      { t: 'rect', x: 6, y: 3, w: 12, h: 1.8 },
      { t: 'rect', x: 6, y: 19.2, w: 12, h: 1.8 },
      { t: 'rect', x: 6, y: 3, w: 1.8, h: 18 },
      { t: 'rect', x: 16.2, y: 3, w: 1.8, h: 18 },
      { t: 'circle', cx: 14, cy: 12, r: 1.3 },
    ],
  },
  {
    key: 'window', label: '窗', shapes: [
      { t: 'rect', x: 4, y: 5, w: 16, h: 1.6 },
      { t: 'rect', x: 4, y: 17.4, w: 16, h: 1.6 },
      { t: 'rect', x: 4, y: 5, w: 1.6, h: 14 },
      { t: 'rect', x: 18.4, y: 5, w: 1.6, h: 14 },
      { t: 'rect', x: 11.2, y: 6.6, w: 1.6, h: 10.8 },
      { t: 'rect', x: 5.6, y: 11.2, w: 12.8, h: 1.6 },
    ],
  },
  {
    key: 'elevator', label: '电梯', shapes: [
      { t: 'rect', x: 5, y: 3, w: 14, h: 1.6 },
      { t: 'rect', x: 5, y: 19.4, w: 14, h: 1.6 },
      { t: 'rect', x: 5, y: 3, w: 1.6, h: 18 },
      { t: 'rect', x: 17.4, y: 3, w: 1.6, h: 18 },
      { t: 'poly', pts: [[9, 12.4], [12, 8.4], [15, 12.4]] },
      { t: 'poly', pts: [[9, 13.6], [12, 17.6], [15, 13.6]] },
    ],
  },
  {
    key: 'stairs', label: '楼梯', shapes: [
      { t: 'rect', x: 3, y: 16, w: 5, h: 4 },
      { t: 'rect', x: 8, y: 12, w: 5, h: 8 },
      { t: 'rect', x: 13, y: 8, w: 5, h: 12 },
    ],
  },
  {
    key: 'restroom', label: '卫生间', shapes: [
      { t: 'circle', cx: 12, cy: 6, r: 2.6 },
      { t: 'poly', pts: [[8, 21], [8, 13.5], [16, 13.5], [16, 21]] },
    ],
  },
  {
    key: 'hydrant', label: '消防栓', shapes: [
      { t: 'circle', cx: 12, cy: 6.5, r: 2.6 },
      { t: 'rect', x: 9.5, y: 8.5, w: 5, h: 9.5 },
      { t: 'rect', x: 6.5, y: 11.5, w: 11, h: 2.4 },
      { t: 'rect', x: 10, y: 18, w: 4, h: 2 },
    ],
  },
  {
    key: 'extinguisher', label: '灭火器', shapes: [
      { t: 'rect', x: 10, y: 9.5, w: 4.4, h: 10.5 },
      { t: 'rect', x: 9, y: 6.8, w: 6, h: 3 },
      { t: 'rect', x: 14.6, y: 7.4, w: 4, h: 1.9 },
      { t: 'rect', x: 7.6, y: 5, w: 3.4, h: 1.8 },
    ],
  },
  {
    key: 'camera', label: '摄像头', shapes: [
      { t: 'rect', x: 5, y: 3, w: 7, h: 2 },
      { t: 'rect', x: 8, y: 5, w: 2, h: 4.5 },
      { t: 'rect', x: 3, y: 9, w: 11, h: 7 },
      { t: 'poly', pts: [[14, 11], [21, 7], [21, 17], [14, 13]] },
    ],
  },
  {
    key: 'cabinet', label: '机柜', shapes: [
      { t: 'rect', x: 6, y: 3, w: 12, h: 1.6 },
      { t: 'rect', x: 6, y: 19.4, w: 12, h: 1.6 },
      { t: 'rect', x: 6, y: 3, w: 1.6, h: 18 },
      { t: 'rect', x: 16.4, y: 3, w: 1.6, h: 18 },
      { t: 'rect', x: 9.5, y: 7, w: 5, h: 2 },
      { t: 'rect', x: 9.5, y: 11, w: 5, h: 2 },
      { t: 'rect', x: 9.5, y: 15, w: 5, h: 2 },
    ],
  },
  {
    key: 'electric', label: '带电', shapes: [
      { t: 'poly', pts: [[13, 2], [5.5, 13], [10, 13], [8, 22], [17, 10], [12, 10]] },
    ],
  },
  {
    key: 'warning', label: '警示', shapes: [
      { t: 'line', x0: 12, y0: 3, x1: 21.5, y1: 20, w: 2 },
      { t: 'line', x0: 21.5, y0: 20, x1: 2.5, y1: 20, w: 2 },
      { t: 'line', x0: 2.5, y0: 20, x1: 12, y1: 3, w: 2 },
      { t: 'rect', x: 11, y: 9, w: 2, h: 5.5 },
      { t: 'circle', cx: 12, cy: 17.2, r: 1.2 },
    ],
  },
  {
    key: 'forbidden', label: '禁止', shapes: [
      { t: 'ring', cx: 12, cy: 12, r: 8.6, w: 2.2 },
      { t: 'line', x0: 6.4, y0: 17.6, x1: 17.6, y1: 6.4, w: 2.2 },
    ],
  },
  {
    key: 'cone', label: '路锥', shapes: [
      { t: 'poly', pts: [[12, 3], [17.5, 19], [6.5, 19]] },
      { t: 'rect', x: 5, y: 18.6, w: 14, h: 2.2 },
    ],
  },
  {
    key: 'exit', label: '安全出口', shapes: [
      { t: 'rect', x: 3, y: 5, w: 10, h: 14 },
      { t: 'rect', x: 15, y: 11, w: 5, h: 2 },
      { t: 'poly', pts: [[20, 7.5], [23.5, 12], [20, 16.5]] },
    ],
  },
  {
    key: 'light', label: '照明', shapes: [
      { t: 'circle', cx: 12, cy: 9, r: 5.5 },
      { t: 'rect', x: 10, y: 14, w: 4, h: 3 },
      { t: 'rect', x: 10.5, y: 17, w: 3, h: 2.6 },
    ],
  },
  {
    key: 'vent', label: '通风口', shapes: [
      { t: 'ring', cx: 12, cy: 12, r: 9, w: 1.8 },
      { t: 'rect', x: 11, y: 4.2, w: 2, h: 15.6 },
      { t: 'rect', x: 4.2, y: 11, w: 15.6, h: 2 },
      { t: 'circle', cx: 12, cy: 12, r: 2 },
    ],
  },
  {
    key: 'water', label: '水', shapes: [
      { t: 'poly', pts: [[12, 2.5], [18.5, 13.5], [12, 21.5], [5.5, 13.5]] },
    ],
  },
  {
    key: 'gear', label: '设备', shapes: [
      { t: 'ring', cx: 12, cy: 12, r: 7.4, w: 2.2 },
      { t: 'circle', cx: 12, cy: 12, r: 3 },
      { t: 'rect', x: 11, y: 2.6, w: 2, h: 2.6 },
      { t: 'rect', x: 11, y: 18.8, w: 2, h: 2.6 },
      { t: 'rect', x: 2.6, y: 11, w: 2.6, h: 2 },
      { t: 'rect', x: 18.8, y: 11, w: 2.6, h: 2 },
    ],
  },
  {
    key: 'robot', label: '机器人', shapes: [
      { t: 'rect', x: 6, y: 7, w: 12, h: 1.5 },
      { t: 'rect', x: 6, y: 15.5, w: 12, h: 1.5 },
      { t: 'rect', x: 6, y: 7, w: 1.5, h: 10 },
      { t: 'rect', x: 16.5, y: 7, w: 1.5, h: 10 },
      { t: 'circle', cx: 9.5, cy: 12, r: 1.5 },
      { t: 'circle', cx: 14.5, cy: 12, r: 1.5 },
      { t: 'rect', x: 10.5, y: 3.5, w: 3, h: 3.5 },
      { t: 'circle', cx: 12, cy: 2.8, r: 1.6 },
      { t: 'rect', x: 9, y: 17, w: 6, h: 3 },
    ],
  },
  {
    key: 'pin', label: '位置点', shapes: [
      { t: 'circle', cx: 12, cy: 9, r: 6.5 },
      { t: 'poly', pts: [[12, 22], [5.5, 12.5], [18.5, 12.5]] },
    ],
  },
]

export const ICON_KEYS: string[] = ICONS.map((i) => i.key)
export const ICON_LABELS: string[] = ICONS.map((i) => i.label)

/**
 * 把任意输入（key / 中文名 / 空 / 乱码）收敛成一个合法的图标 key。
 *
 * 后端 select 里存的是**中文 label**（下拉框显示中文更好认），节点里也可能是
 * 旧数据里的英文 key，所以两种都认；都不认识就退回默认图标，绝不返回 undefined
 * ——画的时候拿到 undefined 会直接抛异常把整个画布搞白。
 */
export function normalizeIconKey(raw: any): string {
  const s = typeof raw === 'string' ? raw.trim() : ''
  if (!s) return DEFAULT_ICON_KEY
  const byKey = ICONS.find((i) => i.key === s)
  if (byKey) return byKey.key
  const byLabel = ICONS.find((i) => i.label === s)
  if (byLabel) return byLabel.key
  const low = s.toLowerCase()
  const byLooser = ICONS.find((i) => i.key.toLowerCase() === low || i.label === low)
  return byLooser ? byLooser.key : DEFAULT_ICON_KEY
}

/** 取图标定义（永远有返回值） */
export function iconOf(raw: any): IconDef {
  const key = normalizeIconKey(raw)
  return ICONS.find((i) => i.key === key) as IconDef
}

/** 图标中文名（用于标签、提示） */
export function iconLabel(raw: any): string {
  return iconOf(raw).label
}

/**
 * 图标大小：夹到 [ICON_MIN_SIZE, ICON_MAX_SIZE]，非法值退回默认。
 *
 * 存的是**屏幕像素**，不随地图缩放变化——图标是注记，缩到看不清就没意义了，
 * 跟航点/设施一样固定大小更好认。
 */
export function normalizeIconSize(raw: any): number {
  const n = Number(raw)
  if (!Number.isFinite(n) || n <= 0) return DEFAULT_ICON_SIZE
  return Math.min(ICON_MAX_SIZE, Math.max(ICON_MIN_SIZE, n))
}

/**
 * 画一个图标到画布：以 (cx, cy) 为中心，边长 size 像素，颜色 color。
 *
 * 只依赖 canvas 的基本 API（fillRect / arc / moveTo / lineTo），
 * 不碰 Path2D，这样回归脚本里拿一个假的 ctx 就能把绘制过程录下来断言。
 */
export function drawIcon(
  ctx: CanvasRenderingContext2D,
  icon: any,
  cx: number,
  cy: number,
  size: number,
  color: string,
): void {
  const def = iconOf(icon)
  const s = normalizeIconSize(size) / ICON_GRID
  // 设计网格的原点（图标左上角）对齐到"中心 - 半格"
  const ox = cx - (ICON_GRID / 2) * s
  const oy = cy - (ICON_GRID / 2) * s
  const px = (v: number) => ox + v * s
  const py = (v: number) => oy + v * s

  ctx.save()
  ctx.fillStyle = color
  ctx.strokeStyle = color
  for (const sh of def.shapes) {
    switch (sh.t) {
      case 'rect':
        ctx.fillRect(px(sh.x), py(sh.y), sh.w * s, sh.h * s)
        break
      case 'circle':
        ctx.beginPath()
        ctx.arc(px(sh.cx), py(sh.cy), sh.r * s, 0, Math.PI * 2)
        ctx.fill()
        break
      case 'poly':
        ctx.beginPath()
        sh.pts.forEach(([x, y], k) => (k === 0 ? ctx.moveTo(px(x), py(y)) : ctx.lineTo(px(x), py(y))))
        ctx.closePath()
        ctx.fill()
        break
      case 'ring':
        ctx.beginPath()
        ctx.arc(px(sh.cx), py(sh.cy), sh.r * s, 0, Math.PI * 2)
        ctx.lineWidth = sh.w * s
        ctx.stroke()
        break
      case 'line':
        ctx.beginPath()
        ctx.moveTo(px(sh.x0), py(sh.y0))
        ctx.lineTo(px(sh.x1), py(sh.y1))
        ctx.lineWidth = sh.w * s
        ctx.stroke()
        break
    }
  }
  ctx.restore()
}
