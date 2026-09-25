import React, { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import { Button, Empty, Select, Space, Tag, Toast, Tooltip, Typography } from '@douyinfe/semi-ui'
import BindPointModal from './BindPointModal'
import { nextBox } from '../utils/detectBoxBinding'
import { IconDelete, IconTick } from '@douyinfe/semi-icons'
import {
  NormPt, Viewport, VERTEX_PX, boxCenter, dedupePoints, fitViewport, hitBoxIndex,
  hitVertexIndex, isDrag, isTinyBox, moveRectVertex, normToScreen, panFrom, rectPoints,
  screenToNorm, translatePoints, zoomAt,
} from './detectBoxGeometry'

/**
 * 检测框绑定工具：拍照动作点检视器的**第一项**。
 *
 * 上面是画布（`ActionPointNode.imageUrl` 那张抓拍图当底图，可平移缩放），
 * 下面是框列表。工具栏三种模式：选择 / 绘制矩形 / 绘制多边形。
 * 每个框落地就是动作点底下一个 `DetectBoxNode`，所以列表里选检测流程 / 绑测点、
 * 删框、画布上拖框拖端点，全都是在改同一份 spec——画布不持有任何独立数据。
 *
 * 鼠标手势沿用轨道地图那套刻意简单的规则：
 * - 右键**任何位置**按下都先"预备平移"；拖过阈值 -> 真平移；
 *   **原地松手且按下处有框** -> 才弹菜单（删除）。
 * - 菜单决策点在 `mouseup` 而不是 `contextmenu`：contextmenu 的触发时机
 *   跨平台不一致（Win 是 down→up→ctx，macOS 是 down→ctx→up，后者早于
 *   任何 mousemove），在它里面判定会写出"菜单永远弹不出来"的 bug。
 * - 左键在空白处拖 = 平移；在框上拖 = 整体搬；在端点上拖 = 改这一个点。
 */

export interface DetectBoxItem {
  /** 节点在 spec 里的路径（增删改都靠它） */
  path: string
  shape: 'rect' | 'polygon'
  /** 归一化顶点 0~1 */
  points: NormPt[]
  /** 绑定的测点 id（测点档案 catalog/points 的 id）；'' = 没绑 */
  pointId: string
  /** 测点名（跟着 pointId 一起写的镜像，列表直接显示，不用回查档案） */
  pointName: string
  /**
   * 引用的检测流程（`data/prefabs/检测算法` 下的相对路径）；'' = 没指定。
   *
   * **只存引用**：框说"画面上哪块区域"，流程说"拍到之后怎么判定、要不要发短信"，
   * 抄一份到框上必然漂移，所以这里只是一个路径字符串。
   */
  detectFlow: string
  name: string
}

interface Props {
  /** 底图（已解析成可直接 `<img>` 的地址）；空则提示先拍照 */
  imageSrc: string
  boxes: DetectBoxItem[]
  /**
   * 可选检测算法流程（`data/prefabs/检测算法` 下的流程）。
   * `value` 是流程引用 id（流程根的检测编号 detect_id，留空则文件名），写进 `detect_flow`。
   * 空数组 = 还没拉到 / 一条都没有，此时下拉里只有"未指定流程"一项。
   */
  detectFlows?: { value: string; label: string }[]
  /** 新建框，返回新节点路径（父层建完才知道路径） */
  onAdd: (shape: 'rect' | 'polygon', points: NormPt[]) => string | null
  /** 改顶点（整体平移 / 拖端点都走它） */
  onUpdatePoints: (path: string, points: NormPt[]) => void
  /** 给检测框绑测点（写 point_id / point_name） */
  onBindPoint: (path: string, pointId: string, pointName: string) => void
  /** 解绑测点：两个字段一起清掉，只清 id 会留下一个"看着还绑着"的名字 */
  onUnbindPoint: (path: string) => void
  /**
   * 指定这个框**执行哪条检测算法流程**（流程引用 id，'' = 未指定）。
   *
   * 框只定"画面上哪块区域"；识别到之后怎么走（节流 / 连续确认 / 告警 / 短信）
   * 全是那条流程的事。只存引用不抄内容，流程改一次所有引用它的框自动跟着变。
   */
  onSetDetectFlow: (path: string, ref: string) => void
  /**
   * **整棵树**的测点占用表：测点 id -> "航点名 / 动作点名 / 检测框 #2"。
   * 由页面的 `collectPointUsage(spec)` 算出（页面才有整棵树，这里只有当前动作点）。
   * 一个测点只能绑一处，绑过的测点在窗口里不给「绑定」按钮 + 显示它绑在哪。
   */
  pointUsage?: Record<string, string>
  onRemove: (path: string) => void
  height?: number
}

type Tool = 'select' | 'rect' | 'polygon'

type DragMode = 'none' | 'pan' | 'maybeMenu' | 'moveBox' | 'moveVertex' | 'drawRect'

interface DragState {
  mode: DragMode
  button: number
  /** 按下时的屏幕位置（平移/拖动都按它做**绝对**计算） */
  start: { x: number; y: number }
  baseVp: Viewport
  startNorm: NormPt
  path: string | null
  vertex: number
  orig: NormPt[]
  /** 被拖那个框的形状：矩形拖端点要保持轴对齐，多边形才改单个点 */
  shape: 'rect' | 'polygon'
  moved: boolean
}

/**
 * 检测框按**列表序号**轮换的描边色：一屏多个框时彼此分得清。
 * 旧模型按"算法颜色"上色；算法已改为引用检测流程，流程本身不带颜色。
 */
const BOX_PALETTE = ['#0064fa', '#00b42a', '#ff7d00', '#f53f3f',
  '#722ed1', '#0fc6c2', '#eb2f96', '#7bc616']
/** 滚轮一格缩放的倍数 */
const WHEEL_STEP = 1.12

/** `#RRGGBB` -> `rgba(...)`；解析不出就退回主题蓝，别让脏数据把画布画成黑块 */
function withAlpha(hex: string, a: number): string {
  const m = /^#?([0-9a-f]{6})$/i.exec((hex || '').trim())
  if (!m) return `rgba(0, 100, 250, ${a})`
  const n = parseInt(m[1], 16)
  return `rgba(${(n >> 16) & 255}, ${(n >> 8) & 255}, ${n & 255}, ${a})`
}

export default function DetectBoxTool({
  imageSrc, boxes, detectFlows = [], onAdd, onUpdatePoints,
  onBindPoint, onUnbindPoint, onSetDetectFlow, onRemove,
  pointUsage = {},
  height = 240,
}: Props) {
  const wrapRef = useRef<HTMLDivElement>(null)
  const canvasRef = useRef<HTMLCanvasElement>(null)
  const [size, setSize] = useState({ w: 0, h: height })
  const [img, setImg] = useState<HTMLImageElement | null>(null)
  const [imgFailed, setImgFailed] = useState(false)
  const [vp, setVp] = useState<Viewport>({ x: 0, y: 0, k: 1 })

  const [tool, setTool] = useState<Tool>('select')
  const [dragA, setDragA] = useState<NormPt | null>(null)
  const [dragB, setDragB] = useState<NormPt | null>(null)
  const [poly, setPoly] = useState<NormPt[]>([])
  const [cursor, setCursor] = useState<{ x: number; y: number } | null>(null)
  const [selPath, setSelPath] = useState<string | null>(null)
  /** 拖动中的顶点预览（松手才写回 spec，避免每帧改一次树） */
  const [preview, setPreview] = useState<NormPt[] | null>(null)
  const [menu, setMenu] = useState<{ x: number; y: number; path: string } | null>(null)
  /** 「绑定测点」弹窗开着（给**当前选中的框**绑；没选就先选第一个） */
  const [bindOpen, setBindOpen] = useState(false)
  const [err, setErr] = useState('')

  const dragRef = useRef<DragState | null>(null)

  /* ---- 底图：只认自然宽高，画的时候才知道怎么 contain ---- */
  useEffect(() => {
    if (!imageSrc) { setImg(null); setImgFailed(false); return }
    setImgFailed(false)
    const im = new Image()
    im.onload = () => setImg(im)
    im.onerror = () => { setImgFailed(true); setImg(null) }
    im.src = imageSrc
    // 换图/卸载时摘掉回调：晚到的 onerror 会把新图的状态覆盖成"失败"
    return () => { im.onload = null; im.onerror = null }
  }, [imageSrc])

  /* ---- 画布宽度跟着容器走（检视器可以拖动改宽） ---- */
  useEffect(() => {
    const el = wrapRef.current
    if (!el) return
    const apply = () => setSize((s) => ({ ...s, w: el.clientWidth }))
    apply()
    const ro = new ResizeObserver(apply)
    ro.observe(el)
    return () => ro.disconnect()
  }, [])

  useEffect(() => { setSize((s) => ({ ...s, h: height })) }, [height])

  const iw = img?.naturalWidth || 0
  const ih = img?.naturalHeight || 0
  const hasCanvas = size.w > 0 && iw > 0 && ih > 0

  /** contain 的基准缩放：缩放上下限按它算，否则不同尺寸的图手感不一致 */
  const fitK = useMemo(
    () => (hasCanvas ? fitViewport(iw, ih, size.w, size.h).k : 1),
    [hasCanvas, iw, ih, size.w, size.h],
  )

  /* ---- 换图 / 首次量到宽度时复位视口；之后用户自己缩放的不受影响 ---- */
  const fittedRef = useRef('')
  useEffect(() => {
    if (!hasCanvas) return
    if (fittedRef.current === imageSrc) return
    fittedRef.current = imageSrc
    setVp(fitViewport(iw, ih, size.w, size.h))
  }, [hasCanvas, imageSrc, iw, ih, size.w, size.h])

  /** 检测流程引用 id -> 下拉里的显示名（查不到返回 ''） */
  const flowLabelOf = useCallback((ref: string): string =>
    (detectFlows.find((f) => f.value === ref)?.label) || '', [detectFlows])

  /** 框颜色按列表序号轮换，一屏多框彼此区分（检测流程本身不带颜色） */
  const colorOf = useCallback((b: DetectBoxItem): string => {
    const i = boxes.findIndex((x) => x.path === b.path)
    return BOX_PALETTE[(i < 0 ? 0 : i) % BOX_PALETTE.length]
  }, [boxes])

  /** 当前实际画出来的顶点：拖动中用预览，否则用 spec 里的 */
  const pointsOf = useCallback((b: DetectBoxItem): NormPt[] =>
    (b.path === selPath && preview ? preview : b.points), [selPath, preview])

  /* ---- 滚轮缩放：必须 passive:false，否则 preventDefault 无效、页面跟着滚 ---- */
  useEffect(() => {
    const cv = canvasRef.current
    if (!cv || !hasCanvas) return
    const onWheel = (e: WheelEvent) => {
      e.preventDefault()
      const r = cv.getBoundingClientRect()
      const anchor = { x: e.clientX - r.left, y: e.clientY - r.top }
      const factor = e.deltaY < 0 ? WHEEL_STEP : 1 / WHEEL_STEP
      setVp((v) => zoomAt(v, anchor, factor, fitK))
    }
    cv.addEventListener('wheel', onWheel, { passive: false })
    return () => cv.removeEventListener('wheel', onWheel)
  }, [hasCanvas, fitK])

  /* ---- 菜单开着时：点别处 / 滚动 / 失焦 / Esc 关掉 ----
   *
   * ⚠️ **必须放过菜单内部的点击**。这里是 window 的**捕获阶段**监听，一定先于
   * 菜单项的 React 处理器执行。若不加区分地 setMenu(null)，菜单会在 mousedown
   * 那一刻就被卸载，于是浏览器凑不齐 click 所需的 down/up 配对，菜单项的 onClick
   * **永远不触发**——表现就是"右键菜单能弹出来，点删除却没反应"。
   */
  useEffect(() => {
    if (!menu) return
    const onDown = (e: MouseEvent) => {
      const el = e.target
      if (el instanceof Element && el.closest('.dbx-ctx')) return
      setMenu(null)
    }
    const onWheel = () => setMenu(null)
    const onKey = (e: KeyboardEvent) => { if (e.key === 'Escape') setMenu(null) }
    const onBlur = () => setMenu(null)   // 必须是具名函数，匿名的话 remove 不掉
    window.addEventListener('mousedown', onDown, true)
    window.addEventListener('wheel', onWheel, true)
    window.addEventListener('keydown', onKey)
    window.addEventListener('blur', onBlur)
    return () => {
      window.removeEventListener('mousedown', onDown, true)
      window.removeEventListener('wheel', onWheel, true)
      window.removeEventListener('keydown', onKey)
      window.removeEventListener('blur', onBlur)
    }
  }, [menu])

  /* ---- 绘制 ---- */
  useEffect(() => {
    const cv = canvasRef.current
    if (!cv || !size.w) return
    const ctx = cv.getContext('2d')
    if (!ctx) return

    const dpr = window.devicePixelRatio || 1
    cv.width = Math.round(size.w * dpr)
    cv.height = Math.round(size.h * dpr)
    cv.style.width = `${size.w}px`
    cv.style.height = `${size.h}px`
    ctx.setTransform(dpr, 0, 0, dpr, 0, 0)

    const cs = getComputedStyle(document.documentElement)
    const v = (n: string, fb: string) => cs.getPropertyValue(n).trim() || fb
    const C = {
      bg: v('--semi-color-bg-2', '#fff'),
      text2: v('--semi-color-text-2', '#8f959e'),
      border: v('--semi-color-border', '#e4e5e7'),
      sel: v('--semi-color-warning', '#ff7d00'),
      handle: v('--semi-color-bg-5', '#fff'),
      // 绑了测点的框用成功色标出来：一眼看出"这批框里还有哪个没绑"
      bound: v('--semi-color-success', '#00b42a'),
    }

    ctx.clearRect(0, 0, size.w, size.h)
    ctx.fillStyle = C.bg
    ctx.fillRect(0, 0, size.w, size.h)

    if (img && hasCanvas) {
      // 世界坐标是图片像素：图左上角落在 vp.x/vp.y，尺寸乘 k
      ctx.drawImage(img, vp.x, vp.y, iw * vp.k, ih * vp.k)
      ctx.strokeStyle = C.border
      ctx.lineWidth = 1
      ctx.strokeRect(vp.x + 0.5, vp.y + 0.5, iw * vp.k - 1, ih * vp.k - 1)
    }

    /** 把一串归一化顶点描成闭合路径 */
    const path = (pts: NormPt[]) => {
      ctx.beginPath()
      pts.forEach((p, i) => {
        const s = normToScreen(p, vp, iw, ih)
        if (i === 0) ctx.moveTo(s.x, s.y); else ctx.lineTo(s.x, s.y)
      })
      ctx.closePath()
    }

    /* --- 已有框 --- */
    boxes.forEach((b, i) => {
      const pts = pointsOf(b)
      if (pts.length < 2) return
      const sel = b.path === selPath
      const color = colorOf(b)
      path(pts)
      ctx.fillStyle = withAlpha(color, sel ? 0.24 : 0.10)
      ctx.fill()
      ctx.lineWidth = sel ? 2 : 1.5
      ctx.strokeStyle = sel ? C.sel : color
      ctx.stroke()

      if (sel && tool === 'select') {
        // 选中态给端点手柄，一眼看出"这些点是可以单独拖的"
        for (const p of pts) {
          const s = normToScreen(p, vp, iw, ih)
          ctx.fillStyle = C.handle
          ctx.strokeStyle = C.sel
          ctx.lineWidth = 1.5
          ctx.beginPath()
          ctx.rect(s.x - 3.5, s.y - 3.5, 7, 7)
          ctx.fill()
          ctx.stroke()
        }
      }

      const c = boxCenter(pts)
      const s = normToScreen(c, vp, iw, ih)
      const label = `${i + 1}`
      ctx.font = '11px system-ui, -apple-system, "Segoe UI", sans-serif'
      const tw = ctx.measureText(label).width
      // 序号牌的颜色表达"绑没绑测点"：绑了是绿的，选中的橙框靠描边和端点手柄看
      ctx.fillStyle = b.pointId ? C.bound : withAlpha(sel ? C.sel : color, 0.9)
      ctx.fillRect(s.x - tw / 2 - 3, s.y - 8, tw + 6, 14)
      ctx.fillStyle = '#fff'
      ctx.textAlign = 'center'
      ctx.textBaseline = 'middle'
      ctx.fillText(label, s.x, s.y - 1)
    })

    /* --- 正在画的：矩形预览 --- */
    if (tool === 'rect' && dragA && dragB) {
      path(rectPoints(dragA, dragB))
      ctx.setLineDash([5, 4])
      ctx.lineWidth = 1.5
      ctx.strokeStyle = C.sel
      ctx.stroke()
      ctx.fillStyle = withAlpha(C.sel, 0.12)
      ctx.fill()
      ctx.setLineDash([])
    }

    /* --- 正在画的：多边形（已有点 + 橡皮筋 + 首点吸附圈） --- */
    if (tool === 'polygon' && poly.length && hasCanvas) {
      ctx.strokeStyle = C.sel
      ctx.lineWidth = 1.5
      ctx.beginPath()
      poly.forEach((p, i) => {
        const s = normToScreen(p, vp, iw, ih)
        if (i === 0) ctx.moveTo(s.x, s.y); else ctx.lineTo(s.x, s.y)
      })
      if (cursor) ctx.lineTo(cursor.x, cursor.y)
      ctx.stroke()

      // 首点画大一点：回到它上面就能闭合，得让用户看得见"终点在哪"
      const f = normToScreen(poly[0], vp, iw, ih)
      ctx.beginPath()
      ctx.arc(f.x, f.y, VERTEX_PX, 0, Math.PI * 2)
      ctx.fillStyle = withAlpha(C.sel, 0.18)
      ctx.fill()
      ctx.strokeStyle = C.sel
      ctx.stroke()

      for (const p of poly) {
        const s = normToScreen(p, vp, iw, ih)
        ctx.fillStyle = C.sel
        ctx.beginPath()
        ctx.arc(s.x, s.y, 3, 0, Math.PI * 2)
        ctx.fill()
      }
    }

    /* --- 没图 / 图挂了：在画布里说清楚，别让用户对着空白猜 --- */
    if (!hasCanvas) {
      ctx.fillStyle = C.text2
      ctx.font = '12px system-ui, -apple-system, "Segoe UI", sans-serif'
      ctx.textAlign = 'center'
      ctx.textBaseline = 'middle'
      ctx.fillText(
        imgFailed ? '抓拍图加载失败，请重新拍照' : '该动作点还没有抓拍图，先在下面点「拍照」',
        size.w / 2, size.h / 2,
      )
    }
  }, [boxes, img, imgFailed, vp, iw, ih, size, selPath, tool, dragA, dragB, poly, cursor,
    colorOf, pointsOf, hasCanvas])

  /* ---- 绘制状态 ---- */

  /**
   * 清掉"画了一半"的东西，但**保留当前工具**——画完一个接着画下一个。
   *
   * 画完就退回选择模式的话，画 5 个框要来回点 5 次工具按钮，很烦；
   * 想退出就按 Esc 或点「选择」。
   */
  const resetDrawing = useCallback(() => {
    setDragA(null); setDragB(null); setPoly([]); setPreview(null); setErr('')
  }, [])

  /** 彻底放弃当前工具、回到选择 */
  const cancel = useCallback(() => { resetDrawing(); setTool('select') }, [resetDrawing])

  const startTool = (t: Tool) => { resetDrawing(); setTool(t) }

  const finishPolygon = useCallback(() => {
    const pts = dedupePoints(poly)
    if (pts.length < 3) { setErr('多边形至少要 3 个点'); return }
    if (isTinyBox(pts)) { setErr('这个框太小了，重画一个'); return }
    const p = onAdd('polygon', pts)
    if (p) setSelPath(p)
    resetDrawing()   // 继续画下一个
  }, [poly, onAdd, resetDrawing])

  const fitNow = useCallback(() => {
    if (!hasCanvas) return
    setVp(fitViewport(iw, ih, size.w, size.h))
  }, [hasCanvas, iw, ih, size.w, size.h])

  const zoomBtn = (up: boolean) => {
    const a = { x: size.w / 2, y: size.h / 2 }
    setVp((v) => zoomAt(v, a, up ? WHEEL_STEP : 1 / WHEEL_STEP, fitK))
  }

  /* ---- 键盘：回车收尾 / Esc 放弃（选择模式没有"画了一半"的状态，不挂监听） ---- */
  useEffect(() => {
    if (tool === 'select') return
    const onKey = (e: KeyboardEvent) => {
      if (e.key === 'Escape') { e.preventDefault(); cancel() }
      else if (e.key === 'Enter' && tool === 'polygon') { e.preventDefault(); finishPolygon() }
    }
    window.addEventListener('keydown', onKey)
    return () => window.removeEventListener('keydown', onKey)
  }, [tool, cancel, finishPolygon])

  /* ---- 指针事件 ---- */
  const posOf = (e: React.PointerEvent<HTMLCanvasElement>) => {
    const r = e.currentTarget.getBoundingClientRect()
    return { x: e.clientX - r.left, y: e.clientY - r.top }
  }

  const onDown = (e: React.PointerEvent<HTMLCanvasElement>) => {
    if (!hasCanvas) return
    setMenu(null)
    const sc = posOf(e)
    const n = screenToNorm(sc, vp, iw, ih)
    const base: DragState = {
      mode: 'none', button: e.button, start: sc, baseVp: vp, startNorm: n,
      path: null, vertex: -1, orig: [], shape: 'rect', moved: false,
    }

    // 右键：任何位置都先"预备平移"，松手时再决定是平移还是弹菜单
    if (e.button === 2) {
      const i = hitBoxIndex(n, boxes)
      dragRef.current = { ...base, mode: 'maybeMenu', path: i >= 0 ? boxes[i].path : null }
      e.currentTarget.setPointerCapture?.(e.pointerId)
      return
    }
    if (e.button !== 0) return

    if (tool === 'rect') {
      setDragA(n); setDragB(n); setErr('')
      dragRef.current = { ...base, mode: 'drawRect' }
      e.currentTarget.setPointerCapture?.(e.pointerId)
      return
    }
    if (tool === 'polygon') {
      // 点回起点 = 收尾（比"双击"好解释，也不会被连点误触发）
      const f = poly[0]
      if (f && poly.length >= 3) {
        const fs = normToScreen(f, vp, iw, ih)
        if (Math.hypot(fs.x - sc.x, fs.y - sc.y) <= VERTEX_PX) { finishPolygon(); return }
      }
      setPoly((prev) => [...prev, n])
      setErr('')
      return
    }

    /* --- 选择模式 --- */
    // 先端点、后框内：端点压在框边上时也优先拖端点（不然永远改不了角）
    const selBox = boxes.find((b) => b.path === selPath)
    if (selBox) {
      const vi = hitVertexIndex(sc, pointsOf(selBox), vp, iw, ih)
      if (vi >= 0) {
        dragRef.current = {
          ...base, mode: 'moveVertex', path: selBox.path, vertex: vi,
          orig: pointsOf(selBox), shape: selBox.shape,
        }
        e.currentTarget.setPointerCapture?.(e.pointerId)
        return
      }
    }
    const i = hitBoxIndex(n, boxes)
    if (i >= 0) {
      const b = boxes[i]
      setSelPath(b.path)
      setErr('')
      dragRef.current = { ...base, mode: 'moveBox', path: b.path, orig: pointsOf(b) }
      e.currentTarget.setPointerCapture?.(e.pointerId)
      return
    }
    // 空白处：拖动就是平移，原地松手 = 取消选中
    dragRef.current = { ...base, mode: 'pan' }
    e.currentTarget.setPointerCapture?.(e.pointerId)
  }

  const onMove = (e: React.PointerEvent<HTMLCanvasElement>) => {
    if (!hasCanvas) return
    const sc = posOf(e)
    setCursor(sc)
    const d = dragRef.current
    if (!d) return

    // 位移过阈值才算拖（右键靠它区分"平移"与"弹菜单"）
    if (!d.moved && isDrag(d.start, sc)) d.moved = true

    if (d.mode === 'maybeMenu') {
      if (d.moved) setVp(panFrom(d.baseVp, d.start, sc))
      return
    }
    if (d.mode === 'pan') {
      if (d.moved) setVp(panFrom(d.baseVp, d.start, sc))
      return
    }
    if (d.mode === 'drawRect') { if (d.moved) setDragB(screenToNorm(sc, vp, iw, ih)); return }

    if (d.mode === 'moveBox') {
      if (!d.moved) return
      const now = screenToNorm(sc, vp, iw, ih)
      setPreview(translatePoints(d.orig, { x: now.x - d.startNorm.x, y: now.y - d.startNorm.y }))
      return
    }
    if (d.mode === 'moveVertex') {
      if (!d.moved) return
      const now = screenToNorm(sc, vp, iw, ih)
      // 矩形：重算包围盒，拖完仍是矩形；多边形：只改这一点的自由形状
      setPreview(d.shape === 'rect'
        ? moveRectVertex(d.orig, d.vertex, now)
        : d.orig.map((p, i) => (i === d.vertex ? now : p)))
    }
  }

  const onUp = (e: React.PointerEvent<HTMLCanvasElement>) => {
    const d = dragRef.current
    dragRef.current = null
    // 只有真的捕获过才释放：多边形是"点一下加个点"，没进捕获，
    // 对着没捕获的 pointerId 调 release 属于自找麻烦
    if (d) e.currentTarget.releasePointerCapture?.(e.pointerId)
    if (!d) return

    if (d.mode === 'maybeMenu') {
      // 原地松手 + 按下处有框 -> 弹菜单；否则就是刚才在平移
      if (!d.moved && d.path) {
        const r = e.currentTarget.getBoundingClientRect()
        setMenu({ x: e.clientX - r.left, y: e.clientY - r.top, path: d.path })
      }
      return
    }
    if (d.mode === 'pan') {
      if (!d.moved) setSelPath(null)   // 空白处点一下 = 取消选中
      return
    }
    if (d.mode === 'moveBox' || d.mode === 'moveVertex') {
      if (d.moved && d.path && preview) onUpdatePoints(d.path, preview)
      setPreview(null)
      return
    }
    if (d.mode === 'drawRect') {
      // 没拖动（只是点了一下）/ 框太小：留在矩形工具里让人重画，不踢回选择
      if (!d.moved || !dragA || !dragB) { resetDrawing(); return }
      const pts = rectPoints(dragA, dragB)
      if (isTinyBox(pts)) { setErr('这个框太小了，重画一个'); resetDrawing(); return }
      const p = onAdd('rect', pts)
      if (p) setSelPath(p)
      resetDrawing()   // 保持矩形工具，接着画下一个
    }
  }

  const selBox = boxes.find((b) => b.path === selPath) || null
  const zoomPct = hasCanvas && fitK > 0 ? Math.round((vp.k / fitK) * 100) : 100

  /** 本动作点下已绑走的测点 id —— 弹窗里要标成"已绑定" */
  const boundPointIds = useMemo(
    () => new Set(boxes.map((b) => b.pointId).filter(Boolean)),
    [boxes],
  )

  /**
   * 开「绑定测点」：绑的是**当前选中的框**。
   * 还没选就自动选第一个——"画完框想立刻绑测点"是最常见的路径，
   * 不该逼人先去列表里点一下。
   */
  const openBindPoint = () => {
    if (!boxes.length) return
    if (!selBox) setSelPath(boxes[0].path)
    setBindOpen(true)
  }

  /**
   * 窗口是非模态的，开着的时候外面的框照样能删。选中框一旦没了就**关掉窗口**：
   * 悄悄改绑到 `boxes[0]` 是最坏的结果——用户以为在给 #3 绑，其实写进了 #1。
   * 选中框一旦没了就关掉它。
   */
  useEffect(() => {
    if (bindOpen && !boxes.some((b) => b.path === selPath)) setBindOpen(false)
  }, [bindOpen, boxes, selPath])

  /** 在绑定窗口里解绑当前框：窗口**保持开着**，好让人立刻改绑另一个测点 */
  const doUnbindPoint = () => {
    if (!selBox) return
    onUnbindPoint(selBox.path)
  }

  /**
   * 绑定；advance=true 时绑完自动切到下一个框。
   *
   * **绑完一律不关窗口**（用户明确要的）：绑完常常还要接着绑下一个框，
   * 或者刚绑完发现绑错了要立刻改绑，关掉再开一次太绕。窗口就靠标题栏的
   * × 和底部的「关闭」关——非模态窗口本来也不该自己消失。
   */
  const doBindPoint = (pointId: string, pointName: string, advance: boolean) => {
    const target = selBox
    if (!target) return
    // 一个测点只能绑一处。窗口里的按钮已经灰掉了，这里再兜一次：
    // 防的是右键菜单、以及"数据本来就重复"的老 spec 被改到一半。
    const usedBy = pointUsage[pointId]
    if (usedBy && pointId !== target.pointId) {
      Toast.warning({
        content: `这个测点已经绑在：${usedBy}。一个测点只能绑一处，先去那边解绑`,
        duration: 3,
      })
      return
    }
    onBindPoint(target.path, pointId, pointName)
    if (!advance) return
    const n = nextBox(boxes, target.path)
    if (!n) return
    setSelPath(n.path)
    if (n.wrapped && boxes.length > 1) Toast.info('已经是最后一个，回到第 1 个检测框')
  }

  return (
    <div className="dbx">
      {/* 工具、缩放、**绑定测点**都在同一行：检视器这一栏本来就不宽，
          多一行就把画布往下挤。窄栏放不下时靠 `.dbx-head` 的 flex-wrap 换行，不会溢出。 */}
      <div className="dbx-head">
        <span style={{ fontWeight: 600, fontSize: 13 }}>检测框绑定</span>
        <Space wrap>
          <Button size="small" theme={tool === 'select' ? 'solid' : 'light'} type="primary"
            onClick={() => startTool('select')}>
            选择
          </Button>
          <Button size="small" theme={tool === 'rect' ? 'solid' : 'light'} type="primary"
            onClick={() => startTool(tool === 'rect' ? 'select' : 'rect')} disabled={!hasCanvas}>
            绘制矩形
          </Button>
          <Button size="small" theme={tool === 'polygon' ? 'solid' : 'light'} type="primary"
            onClick={() => startTool(tool === 'polygon' ? 'select' : 'polygon')} disabled={!hasCanvas}>
            绘制多边形
          </Button>

          {/* 竖线只是分组：左边"用什么工具"，右边"看多清楚" */}
          <span className="dbx-sep" />

          <Button size="small" type="tertiary" onClick={() => zoomBtn(true)}
            disabled={!hasCanvas}>+</Button>
          <Button size="small" type="tertiary" onClick={() => zoomBtn(false)}
            disabled={!hasCanvas}>−</Button>
          <Button size="small" type="tertiary" onClick={fitNow} disabled={!hasCanvas}>适应</Button>
          <span style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>{zoomPct}%</span>

          {/* 多边形的收尾按钮只在画多边形时出现，平时不占地方 */}
          {tool === 'polygon' ? (
            <>
              <span className="dbx-sep" />
              <Button size="small" type="tertiary" icon={<IconTick />}
                onClick={finishPolygon} disabled={poly.length < 3}>
                完成{poly.length ? `（${poly.length} 点）` : ''}
              </Button>
              <Button size="small" type="tertiary" onClick={cancel}>取消</Button>
            </>
          ) : null}

          {/* 「绑定测点」开一扇非模态窗口，作用在**当前选中的框**上，单独一组放最后。
              检测流程不在这弹窗：下面框列表里每一行各有一个流程下拉，批量配更快。 */}
          <span className="dbx-sep" />
          <Button size="small" theme={bindOpen ? 'solid' : 'light'} type="primary"
            onClick={openBindPoint} disabled={!boxes.length}>
            绑定测点
          </Button>
        </Space>
      </div>

      <div ref={wrapRef} className="dbx-canvas-wrap">
        <canvas
          ref={canvasRef}
          className="dbx-canvas"
          style={{ height: size.h, cursor: tool === 'select' ? 'default' : 'crosshair' }}
          onPointerDown={onDown}
          onPointerMove={onMove}
          onPointerUp={onUp}
          onPointerLeave={() => setCursor(null)}
          onContextMenu={(e) => e.preventDefault()}
        />
        {menu ? (
          // 菜单里再右键不要弹出浏览器菜单（会盖住我们的菜单）
          <div className="dbx-ctx" style={{ left: menu.x, top: menu.y }}
            onContextMenu={(e) => e.preventDefault()}>
            <button type="button" className="dbx-ctx-item"
              onClick={() => {
                onRemove(menu.path)
                if (selPath === menu.path) setSelPath(null)
                setMenu(null)
              }}>
              <IconDelete /> 删除检测框
            </button>
          </div>
        ) : null}
      </div>

      <div className="dbx-hint">
        {tool === 'rect' ? '在图上拖一下框出矩形，松手即建成，可接着画下一个（Esc 退出）'
          : tool === 'polygon' ? '逐个点击顶点，回到起点或按回车收尾，可接着画下一个（Esc 退出）'
            : err ? <span style={{ color: 'var(--semi-color-danger)' }}>{err}</span>
              : '滚轮缩放 · 右键拖动平移 · 拖框搬家 · 拖端点改形状 · 右键点框删除'}
      </div>

      {boxes.length === 0 ? (
        <div className="dbx-empty">还没有检测框</div>
      ) : (
        <div className="dbx-list">
          {boxes.map((b, i) => {
            const on = b.path === selPath
            // 引用了但流程目录里已没有（改名/删除）：补一条失效项，别让旧数据变空下拉
            const flowOpts = [
              { value: '', label: '未指定流程' },
              ...detectFlows,
              ...(b.detectFlow && !detectFlows.some((f) => f.value === b.detectFlow)
                ? [{ value: b.detectFlow, label: `${b.detectFlow}（流程已不存在）` }]
                : []),
            ]
            return (
              <div key={b.path}
                className={`dbx-row${on ? ' is-sel' : ''}${b.pointId ? ' is-bound' : ''}`}
                onClick={() => setSelPath(b.path)}>
                {/* 序号牌：绑了测点就用成功色，跟画布上的框一致 */}
                <span className="dbx-idx"
                  style={{ background: b.pointId ? 'var(--semi-color-success)' : colorOf(b) }}>
                  {i + 1}
                </span>
                <Tag size="small" color={b.shape === 'rect' ? 'blue' : 'purple'}>
                  {b.shape === 'rect' ? '矩形' : '多边形'}
                </Tag>
                {/* 检测算法流程：直接在框上选一条（= 算法 + 参数的检测管线），
                    只存引用 id（detect_flow），不再挂 AlgorithmConfigNode 子节点 */}
                <div className="dbx-algo">
                  <Select
                    size="small"
                    style={{ flex: 1, minWidth: 120, maxWidth: 220 }}
                    value={b.detectFlow || ''}
                    optionList={flowOpts}
                    placeholder="未指定流程"
                    onChange={(v) => onSetDetectFlow(b.path, String(v ?? ''))}
                  />
                </div>
                {/* 测点名 + 取消绑定是**一组**：按钮必须紧贴名字，
                    中间隔着 margin-left:auto 撑开的空白就看不出它解的是哪个测点了 */}
                <span className="dbx-pt">
                  <Tooltip content={b.pointId ? `已绑测点：${b.pointName || b.pointId}` : '还没绑测点'}
                    position="top">
                    <span className={`dbx-pts${b.pointId ? ' is-bound' : ''}`}>
                      {b.pointId ? (b.pointName || b.pointId) : `${b.points.length} 点`}
                    </span>
                  </Tooltip>
                  {/* 解绑只在**绑了之后**出现：没绑的时候放个点了没反应的按钮纯属噪音 */}
                  {b.pointId ? (
                    <Tooltip content={`取消绑定测点：${b.pointName || b.pointId}`} position="top">
                      {/* 刻意**不带图标**：semi-icons 里没有 unlink/disconnect，
                          而 IconLink（链接）用在"取消绑定"上是反的，
                          IconMinus 又容易和右边的删除按钮混。纯文字最清楚。 */}
                      <Button size="small" type="tertiary" theme="borderless"
                        onClick={(e) => { e.stopPropagation(); onUnbindPoint(b.path) }}>
                        取消绑定
                      </Button>
                    </Tooltip>
                  ) : null}
                </span>
                <Button size="small" type="tertiary" icon={<IconDelete />}
                  onClick={(e) => {
                    e.stopPropagation()
                    onRemove(b.path)
                    if (selPath === b.path) setSelPath(null)
                  }} />
              </div>
            )
          })}
        </div>
      )}

      {boxes.length ? (
        <div className="dbx-sel">
          <Typography.Text type="tertiary" size="small">
            {selBox
              ? `已选中 #${boxes.findIndex((b) => b.path === selBox.path) + 1}`
              : '还没选中检测框（点上面列表里任意一行）'}
            {selBox && flowLabelOf(selBox.detectFlow) ? ` · 流程 ${flowLabelOf(selBox.detectFlow)}` : ''}
            {selBox?.pointId ? ` · 测点 ${selBox.pointName || selBox.pointId}` : ''}
            {selBox && selBox.points.length ? ` · ${selBox.points.map(
              (p) => `(${p.x.toFixed(2)}, ${p.y.toFixed(2)})`).join(' ')}` : ''}
          </Typography.Text>
        </div>
      ) : null}

      {!imageSrc ? (
        <Empty title="没有抓拍图" description="先在下面的「抓拍图片」处拍一张，才能在图上画检测框"
          style={{ padding: '12px 0' }} />
      ) : null}

      {/* 只认 selBox：目标必须**唯一确定**，不能用 `|| boxes[0]` 兜底，
           否则标题显示的和真绑上的可能不是同一个框（删框时就会这样） */}
      {bindOpen && selBox ? (
        <BindPointModal
          visible
          boxLabel={`检测框 #${boxes.findIndex((b) => b.path === selBox.path) + 1}`}
          currentPointId={selBox.pointId}
          boundPointIds={boundPointIds}
          pointUsage={pointUsage}
          onBind={doBindPoint}
          onUnbind={doUnbindPoint}
          onClose={() => setBindOpen(false)}
        />
      ) : null}
    </div>
  )
}
