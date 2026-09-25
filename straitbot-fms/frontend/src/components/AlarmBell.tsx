import { useCallback, useEffect, useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { Badge } from '@douyinfe/semi-ui'
import { IconBell } from '@douyinfe/semi-icons'
import { getUnackCount } from '../api/alarm'

/**
 * 顶栏右上角告警铃铛：未确认数量角标，点击进入告警列表。
 * 每 30s 轮询一次，页面重新可见时立即刷新。count=0 时不显示角标。
 */
export default function AlarmBell() {
  const navigate = useNavigate()
  const [count, setCount] = useState(0)

  const refresh = useCallback(async () => {
    try {
      const { data } = await getUnackCount()
      setCount(data.count || 0)
    } catch { /* 角标刷新失败静默 */ }
  }, [])

  useEffect(() => {
    refresh()
    const timer = setInterval(refresh, 30000)
    const onVis = () => {
      if (document.visibilityState === 'visible') refresh()
    }
    document.addEventListener('visibilitychange', onVis)
    return () => {
      clearInterval(timer)
      document.removeEventListener('visibilitychange', onVis)
    }
  }, [refresh])

  return (
    <Badge count={count} type="danger" overflowCount={99}>
      <button
        type="button"
        className="fms-header-alarm"
        aria-label="告警中心"
        title="告警中心"
        onClick={() => navigate('/alarms')}
      >
        <IconBell />
      </button>
    </Badge>
  )
}
