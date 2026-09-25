import { useState, useRef, useCallback, useEffect, type ReactNode } from 'react'
import { IconClose } from '@douyinfe/semi-icons'

interface Props {
  visible: boolean
  title: string
  onClose: () => void
  width?: number
  height?: number | string
  initialX?: number
  initialY?: number
  headerExtra?: ReactNode
  children: ReactNode
}

/**
 * 非模态可拖拽浮动面板。
 * - 不遮罩页面 (无 mask), 可同时操作背景内容
 * - 拖拽标题栏移动位置
 * - 自动边界约束, 不会拖出视口
 */
export default function FloatPanel({
  visible, title, onClose, width = 800, height, initialX, initialY, headerExtra, children,
}: Props) {
  const [pos, setPos] = useState({ x: initialX ?? 100, y: initialY ?? 80 })
  const [dragging, setDragging] = useState(false)
  const dragStart = useRef({ mx: 0, my: 0, px: 0, py: 0 })

  // 初始定位居中偏上
  useEffect(() => {
    if (visible && initialX == null) {
      const vw = window.innerWidth
      setPos({ x: Math.max(20, Math.round((vw - width) / 2)), y: initialY ?? 80 })
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [visible])

  const onMouseDown = useCallback((e: React.MouseEvent) => {
    setDragging(true)
    dragStart.current = { mx: e.clientX, my: e.clientY, px: pos.x, py: pos.y }
  }, [pos.x, pos.y])

  useEffect(() => {
    if (!dragging) return
    const onMove = (e: MouseEvent) => {
      const dx = e.clientX - dragStart.current.mx
      const dy = e.clientY - dragStart.current.my
      const maxX = window.innerWidth - 100  // 至少留 100px 可见
      const maxY = window.innerHeight - 40
      setPos({
        x: Math.max(-width + 100, Math.min(maxX, dragStart.current.px + dx)),
        y: Math.max(0, Math.min(maxY, dragStart.current.py + dy)),
      })
    }
    const onUp = () => setDragging(false)
    window.addEventListener('mousemove', onMove)
    window.addEventListener('mouseup', onUp)
    return () => {
      window.removeEventListener('mousemove', onMove)
      window.removeEventListener('mouseup', onUp)
    }
  }, [dragging, width])

  if (!visible) return null

  return (
    <div
      className="float-panel"
      style={{
        position: 'fixed',
        left: pos.x,
        top: pos.y,
        width,
        height: typeof height === 'number' ? height : 'auto',
        maxHeight: typeof height === 'string' ? height : 'calc(100vh - 100px)',
        zIndex: 999,
      }}
    >
      <div className="float-panel-header" onMouseDown={onMouseDown} style={{ cursor: dragging ? 'grabbing' : 'grab' }}>
        <span className="float-panel-title">{title}</span>
        <div className="float-panel-header-right">
          {headerExtra}
          <button className="float-panel-close" onClick={onClose}>
            <IconClose />
          </button>
        </div>
      </div>
      <div className="float-panel-body" style={{ maxHeight: 'calc(100vh - 140px)', overflow: 'auto' }}>
        {children}
      </div>
      <style>{`
        .float-panel {
          background: #fff;
          border-radius: 8px;
          box-shadow: 0 8px 32px rgba(0,0,0,.18);
          display: flex;
          flex-direction: column;
          overflow: hidden;
        }
        .float-panel-header {
          display: flex; align-items: center; justify-content: space-between;
          padding: 10px 16px; background: #f5f7fa; border-bottom: 1px solid #ebeef5;
          user-select: none; -webkit-user-select: none;
        }
        .float-panel-title { font-weight: 600; font-size: 14px; }
        .float-panel-close {
          border: none; background: transparent; cursor: pointer; padding: 4px;
          color: #909399; display: flex; align-items: center; border-radius: 4px; transition: all .15s;
        }
        .float-panel-close:hover { color: #f56c6c; background: #fef0f0; }
        .float-panel-header-right { display: flex; align-items: center; gap: 4px; }
        .float-panel-header-right button, .float-panel-header-right .header-btn {
          border: none; background: transparent; cursor: pointer; padding: 4px;
          color: #909399; display: flex; align-items: center; border-radius: 4px; transition: all .15s;
        }
        .float-panel-header-right .header-btn:hover { color: #409eff; background: #ecf5ff; }
        .float-panel-body { flex: 1; overflow: auto; padding: 16px; }
      `}</style>
    </div>
  )
}
