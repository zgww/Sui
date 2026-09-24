import React, { useCallback, useEffect, useRef, useState } from 'react'
import { createPortal } from 'react-dom'
import { Button } from '@douyinfe/semi-ui'
import { IconClose } from '@douyinfe/semi-icons'
import {
  WIN_W, clampPos, clampSize, defaultPos, defaultSize, dragTo, resizeTo,
  type Pos, type Size, type Viewport,
} from '../utils/windowDrag'

/**
 * 非模态窗口外壳：`createPortal` 到 body，**没有遮罩、不锁滚动、不抢焦点、不吃 Esc**，
 * 标题栏可拖拽平移（双击复位），**右下角有手柄可缩放**（双击复位）。
 * 绑定测点、选择算法两个窗口都用它。
 *
 * 为什么不用 Semi 的 `Modal`：它没有 `modal={false}`，一显示就挂遮罩 +
 * `document.body.style.overflow='hidden'`，而这两个窗口开着的时候用户还得在
 * **画布上点框 / 画框**，挡住画布等于废掉一半功能；Esc 也得留给画布当"放弃绘制"。
 *
 * 自画窗口的三条硬规矩（都在 `utils/windowDrag.ts` 的数值回归里锁着）：
 *   ① 拖拽只认**标题栏**（整块可拖会把点行变成"抖一下算拖"），标题栏上的按钮
 *      用 `closest('button')` 排除；
 *   ② 位移**绝对计算**：`起点 + 总位移`，用按下那一刻的快照，不能逐帧累加增量
 *      （同一帧两个 mousemove 会读到旧值，丢位移）；
 *   ③ 位置 `clampPos` 夹在视口内，resize 也要重夹，否则拖出去等于"窗口没了"；
 *   ④ 缩放同理：`resizeTo` 也是**起点尺寸 + 总位移**，且上界跟着**窗口当前位置**走
 *      （右下角最多到视口边），窗口被拖到右下角时上下界会交叉，`clampSize` 兜底成下限。
 *      缩放手柄只认右下角那一小块，别整块窗口都能拖。
 *
 * 窗口**只由用户关**（标题栏 × / 自己的底部按钮）：设完算法、绑完测点都不自动关，
 * 还要接着弄下一个框。
 */
interface Props {
  title: React.ReactNode
  /** 标题栏右侧的一句提示（比如"拖动这里平移"） */
  hint?: React.ReactNode
  /** 初次出现时的窗口宽度，默认 `WIN_W`（右下角手柄可以再改） */
  width?: number
  /** 内容区的 class：窗口外壳的样式不跟业务走，业务自己带（`.bp` / `.alg-pick`） */
  bodyClass?: string
  footer?: React.ReactNode
  onClose: () => void
  children: React.ReactNode
}

/** 当前视口：位置数学都在 `utils/windowDrag.ts`（纯函数，好测），这里只负责喂真实尺寸 */
const vpOf = (): Viewport => ({ w: window.innerWidth, h: window.innerHeight })

export default function ModelessWindow({
  title, hint, width = WIN_W, bodyClass = '', footer, onClose, children,
}: Props) {
  const [pos, setPos] = useState<Pos>(() => defaultPos(vpOf()))
  const [size, setSize] = useState<Size>(() => {
    const p = defaultPos(vpOf())
    return clampSize(width, defaultSize(vpOf(), p).h, p, vpOf())
  })
  const [dragging, setDragging] = useState(false)
  /** 按下那一刻的快照：鼠标起点 + 窗口起点，拖动全程都拿它算 */
  const dragRef = useRef<{ sx: number; sy: number; ox: number; oy: number } | null>(null)
  /** 缩放同理：鼠标起点 + **按下那一刻**的窗口尺寸 */
  const resizeRef = useRef<{ sx: number; sy: number; ow: number; oh: number } | null>(null)
  const [resizing, setResizing] = useState(false)

  /** 挂载时夹一次：视口可能比窗口还窄（上下界会交叉） */
  useEffect(() => { setPos((p) => clampPos(p.x, p.y, vpOf())) }, [])

  // 位置变了（拖动 / 视口变化）尺寸的上界也跟着变：窗口贴到右边时
  // 能拉多宽是"视口右边 - 窗口左边"，不重夹就会出现"窗口比屏幕还宽"
  useEffect(() => { setSize((s) => clampSize(s.w, s.h, pos, vpOf())) }, [pos])

  useEffect(() => {
    const onWinResize = () => {
      const vp = vpOf()
      setPos((p) => clampPos(p.x, p.y, vp))
      setSize((s) => clampSize(s.w, s.h, clampPos(pos.x, pos.y, vp), vp))
    }
    window.addEventListener('resize', onWinResize)
    return () => window.removeEventListener('resize', onWinResize)
  }, [pos])

  /** 只有标题栏能拖：整块可拖的话，点树行/按钮会变成"抖一下就当成拖" */
  const onHeadDown = useCallback((e: React.MouseEvent) => {
    if (e.button !== 0) return
    // 关闭按钮自己有活儿干，别把它当成拖拽手柄
    if ((e.target as HTMLElement).closest('button')) return
    dragRef.current = { sx: e.clientX, sy: e.clientY, ox: pos.x, oy: pos.y }
    setDragging(true)
  }, [pos.x, pos.y])

  useEffect(() => {
    if (!dragging) return
    const onMove = (e: MouseEvent) => {
      const d = dragRef.current
      if (!d) return
      // 绝对计算（起点 + 总位移）与"拖出视口就夹回来"都在 windowDrag.ts 里
      setPos(dragTo(
        { x: d.ox, y: d.oy },
        { x: d.sx, y: d.sy },
        { x: e.clientX, y: e.clientY },
        vpOf(),
      ))
    }
    const onUp = () => { dragRef.current = null; setDragging(false) }
    window.addEventListener('mousemove', onMove)
    window.addEventListener('mouseup', onUp)
    return () => {
      window.removeEventListener('mousemove', onMove)
      window.removeEventListener('mouseup', onUp)
    }
  }, [dragging])

  /**
   * 右下角手柄：按下才记快照（鼠标起点 + 那一刻的窗口尺寸），
   * 之后全程 `resizeTo(base, start, now)` 绝对计算，不累加增量。
   */
  const onResizeDown = useCallback((e: React.MouseEvent) => {
    if (e.button !== 0) return
    e.stopPropagation()
    resizeRef.current = { sx: e.clientX, sy: e.clientY, ow: size.w, oh: size.h }
    setResizing(true)
  }, [size.w, size.h])

  useEffect(() => {
    if (!resizing) return
    const onMove = (e: MouseEvent) => {
      const d = resizeRef.current
      if (!d) return
      setSize(resizeTo(
        { w: d.ow, h: d.oh },
        { x: d.sx, y: d.sy },
        { x: e.clientX, y: e.clientY },
        pos,
        vpOf(),
      ))
    }
    const onUp = () => { resizeRef.current = null; setResizing(false) }
    window.addEventListener('mousemove', onMove)
    window.addEventListener('mouseup', onUp)
    return () => {
      window.removeEventListener('mousemove', onMove)
      window.removeEventListener('mouseup', onUp)
    }
  }, [resizing, pos])

  return createPortal(
    <div
      className={`mw${dragging ? ' is-drag' : ''}${resizing ? ' is-resize' : ''}`}
      style={{ left: pos.x, top: pos.y, width: size.w, height: size.h }}
    >
      <div
        className="mw-head"
        onMouseDown={onHeadDown}
        onDoubleClick={() => setPos(defaultPos(vpOf()))}
        title="拖动标题栏可以平移窗口，双击复位"
      >
        <span className="mw-title">{title}</span>
        {hint ? <span className="mw-hint">{hint}</span> : null}
        <Button
          size="small" theme="borderless" type="tertiary" icon={<IconClose />}
          onClick={onClose} aria-label="关闭"
        />
      </div>

      <div className={`mw-body${bodyClass ? ` ${bodyClass}` : ''}`}>{children}</div>

      {footer ? <div className="mw-foot">{footer}</div> : null}

      {/*
        右下角手柄：拖它改窗口大小（往右上 = 变窄变高，往左下 = 变窄变矮）。
        只在手柄上按下才算缩放——整块窗口都能拖的话，点树行/按钮会变成"抖一下就当成缩放"。
        双击复位成默认大小，跟标题栏双击复位位置一个意思。
      */}
      <div
        className="mw-grip"
        onMouseDown={onResizeDown}
        onDoubleClick={() => setSize(defaultSize(vpOf(), pos))}
        title="拖动这里调节窗口大小，双击复位"
      />
    </div>,
    document.body,
  )
}
