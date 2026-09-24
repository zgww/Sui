import { useState, useEffect, forwardRef, useImperativeHandle, useCallback } from 'react'
import { listRobots } from '../api/robots'
import type { Robot } from '../types'

export interface RobotTabsRef {
  reload: () => Promise<void>
  list: Robot[]
}

interface Props {
  value?: number | string | null
  autoSelectFirst?: boolean
  onChange?: (v: number) => void
  onLoaded?: (list: Robot[]) => void
}

const RobotTabs = forwardRef<RobotTabsRef, Props>(({ value, autoSelectFirst = true, onChange, onLoaded }, ref) => {
  const [list, setList] = useState<Robot[]>([])

  const reload = useCallback(async () => {
    const { data } = await listRobots()
    setList(data)
    onLoaded?.(data)
    if (autoSelectFirst && value == null && data.length) {
      onChange?.(data[0].id)
    } else if (value != null) {
      onChange?.(value as number)
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [autoSelectFirst])

  useEffect(() => { reload() }, [reload])

  useImperativeHandle(ref, () => ({ reload, list }))

  const batClass = (b: number | null | undefined) => {
    if (b == null) return ''
    if (b <= 20) return 'low'
    if (b <= 40) return 'mid'
    return 'ok'
  }

  if (!list.length) {
    return <div className="text-muted" style={{ padding: '8px 0' }}>暂无机器人, 请先到「机器人列表」添加或扫描</div>
  }

  return (
    <div className="robot-tabs" style={{ marginBottom: 8 }}>
      <div className="tabs-row">
        {list.map((r) => (
          <div
            key={r.id}
            className={`robot-chip ${Number(value) === Number(r.id) ? 'active' : ''}`}
            onClick={() => onChange?.(r.id)}
          >
            <span className={`dot ${r.online ? 'on' : 'off'}`} />
            <span className="name">{r.name}</span>
            <span className="ip text-mono">{r.ip}</span>
            {r.last_battery != null && (
              <span className={`bat ${batClass(r.last_battery)}`}>{r.last_battery}%</span>
            )}
          </div>
        ))}
      </div>
      <style>{`
        .tabs-row { display: flex; flex-wrap: wrap; gap: 8px; background: #fff; padding: 10px; border-radius: 8px; border: 1px solid #ebeef5; }
        .robot-chip { display: inline-flex; align-items: center; gap: 6px; padding: 6px 12px; border-radius: 16px; cursor: pointer; background: #f5f7fa; border: 1px solid #e4e7ed; font-size: 13px; transition: all .15s; user-select: none; }
        .robot-chip:hover { background: #ecf5ff; border-color: #b3d8ff; }
        .robot-chip.active { background: #409eff; color: #fff; border-color: #409eff; box-shadow: 0 2px 6px rgba(64,158,255,.3); }
        .robot-chip.active .ip { color: #d4ecff; }
        .robot-chip .dot { width: 8px; height: 8px; border-radius: 50%; }
        .dot.on { background: #67c23a; }
        .dot.off { background: #c0c4cc; }
        .robot-chip .name { font-weight: 500; }
        .robot-chip .ip { color: #909399; font-size: 12px; }
        .robot-chip .bat { font-size: 11px; padding: 1px 6px; border-radius: 8px; font-weight: 600; }
        .bat.ok { background: #67c23a; color: #fff; }
        .bat.mid { background: #e6a23c; color: #fff; }
        .bat.low { background: #f56c6c; color: #fff; }
        .robot-chip.active .bat { background: rgba(255,255,255,.25); }
        @media (max-width: 768px) { .tabs-row { padding: 8px; gap: 6px; } .robot-chip { padding: 5px 10px; font-size: 12px; } .robot-chip .ip { display: none; } }
      `}</style>
    </div>
  )
})

export default RobotTabs
