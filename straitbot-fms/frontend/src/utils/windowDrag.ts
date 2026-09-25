/**
 * 非模态浮动窗口的**位置 / 尺寸数学**（纯函数，不碰 `window`，回归脚本能直接测）。
 *
 * 为什么单独拎出来：这类窗口最典型的 bug 是"拖到屏幕外就抓不回来了"——
 * 代码看着对（`Math.min/max` 夹一下），但视口比窗口还窄时上下界会**交叉**，
 * 夹出来的坐标反而更离谱。缩放也是同一类问题：右下角手柄往外拖，
 * 上界是"视口右边 - 窗口左边"，窗口本身被拖到右边时上界会小于下界。
 * 这种数值问题源码级断言锁不住，只能算。
 *
 * 视口尺寸由调用方传进来（`{ w, h }`），就是为了让这里保持纯函数。
 */

/** 初次出现时的窗口宽度（右下角手柄可以再改） */
export const WIN_W = 560
/** 初次出现时的窗口高度：够放十来行目录，太高会盖住整个画布 */
export const WIN_H = 520
/** 离视口边至少留这么多，否则拖出去就抓不回来了 */
export const EDGE = 8
/** 底部至少留这么多：再怎么拖也得露出标题栏，不然用户以为窗口没了 */
export const BOTTOM_KEEP = 120
/** 缩放下限：再小标题栏和两个按钮就挤没了 */
export const MIN_W = 420
export const MIN_H = 240

export interface Pos { x: number; y: number }
export interface Size { w: number; h: number }
export interface Viewport { w: number; h: number }

/**
 * 把位置夹回视口内。
 * 注意两个 `Math.max(EDGE, ...)`：视口比窗口还窄 / 还矮时上下界会交叉
 * （`maxX < EDGE`），直接 `Math.min(Math.max(x, EDGE), maxX)` 会取到更小的那个，
 * 窗口反而被推到更外面。兜底成"至少贴左边/上边"。
 */
export function clampPos(x: number, y: number, vp: Viewport): Pos {
  const maxX = Math.max(EDGE, vp.w - WIN_W - EDGE)
  const maxY = Math.max(EDGE, vp.h - BOTTOM_KEEP)
  return {
    x: Math.min(Math.max(x, EDGE), maxX),
    y: Math.min(Math.max(y, EDGE), maxY),
  }
}

/** 初次出现的位置：水平居中、靠上一点，尽量别压住画布正中间的东西 */
export function defaultPos(vp: Viewport): Pos {
  return clampPos(Math.round((vp.w - WIN_W) / 2), 84, vp)
}

/**
 * 拖动到新位置：**起点 + 总位移**的绝对计算。
 * 别写成"上一次位置 + 本次增量"——同一帧里来两个 mousemove 会读到还没更新的旧位置，
 * 位移就丢了（TrackMap 的平移踩过一模一样的坑）。
 */
export function dragTo(
  base: Pos,
  start: { x: number; y: number },
  now: { x: number; y: number },
  vp: Viewport,
): Pos {
  return clampPos(base.x + (now.x - start.x), base.y + (now.y - start.y), vp)
}

/**
 * 把尺寸夹回"放得下"的范围。
 *
 * 上界跟**窗口当前位置**有关（右下角最多到视口边），所以要把 `pos` 传进来：
 * 窗口被拖到右下角时 `maxW` 会小于 `MIN_W`，上下界交叉——跟 `clampPos` 一样，
 * 兜底成"至少留下限那么大"，别夹出一个负数或者比下限还小的窗口。
 */
export function clampSize(w: number, h: number, pos: Pos, vp: Viewport): Size {
  const maxW = vp.w - pos.x - EDGE
  const maxH = vp.h - pos.y - EDGE
  return {
    w: Math.min(Math.max(w, MIN_W), Math.max(MIN_W, maxW)),
    h: Math.min(Math.max(h, MIN_H), Math.max(MIN_H, maxH)),
  }
}

/** 初次出现的尺寸：默认那套，再按视口夹一次（小屏上别一出来就超出屏幕） */
export function defaultSize(vp: Viewport, pos: Pos): Size {
  return clampSize(WIN_W, Math.min(WIN_H, vp.h - 2 * BOTTOM_KEEP), pos, vp)
}

/**
 * 拖右下角手柄到新尺寸：**起点尺寸 + 总位移**，跟 `dragTo` 一个道理——
 * 绝对计算，不能逐帧累加增量。
 */
export function resizeTo(
  base: Size,
  start: { x: number; y: number },
  now: { x: number; y: number },
  pos: Pos,
  vp: Viewport,
): Size {
  return clampSize(base.w + (now.x - start.x), base.h + (now.y - start.y), pos, vp)
}
