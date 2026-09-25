/**
 * 分栏拖拽（splitter）的公共实现。
 *
 * 三处编排页（`PreFab` / `WaypointTreePrefab` / `InspectionPlanPrefab`）都有
 * "一条竖条拖动改宽度"的需求，逻辑一样：**在 window 上监听**，这样鼠标拖出分隔条
 * 甚至拖出窗口外也不会丢事件（挂分隔条自己身上，一移动到子元素上就断了）。
 *
 * 拖动期间给 `body` 加 `wp-resizing-h/v` 锁住光标与文本选择，见 `styles.css`。
 */
import type { MouseEvent as ReactMouseEvent } from 'react'

/**
 * 生成分隔条的 `onMouseDown`。
 *
 * @param start  拖动开始时的尺寸（px）
 * @param apply  应用新尺寸
 * @param min    最小尺寸
 * @param max    最大尺寸
 * @param dir    1 = 向右拖变宽（分隔条左边是目标栏）；-1 = 向右拖变窄（右边是目标栏）；
 *               0 = 不改符号（垂直分隔条用）
 * @param vertical  true = 上下拖动改**高度**
 */
export function startDrag(
  e: ReactMouseEvent,
  start: number,
  apply: (v: number) => void,
  min: number,
  max: number,
  dir: number,
  vertical = false,
) {
  e.preventDefault()
  const startPos = vertical ? e.clientY : e.clientX
  document.body.classList.add(vertical ? 'wp-resizing-v' : 'wp-resizing-h')
  const onMove = (ev: MouseEvent) => {
    const delta = vertical ? ev.clientY - startPos : ev.clientX - startPos
    const next = start + delta * dir
    apply(Math.max(min, Math.min(max, next)))
  }
  const onUp = () => {
    document.body.classList.remove('wp-resizing-v', 'wp-resizing-h')
    window.removeEventListener('mousemove', onMove)
    window.removeEventListener('mouseup', onUp)
  }
  window.addEventListener('mousemove', onMove)
  window.addEventListener('mouseup', onUp)
}
