import { useState, useEffect, useCallback } from 'react'
import { Card, Table, Button, Tag, Select } from '@douyinfe/semi-ui'
import { IconRefresh } from '@douyinfe/semi-icons'
import dayjs from 'dayjs'
import { useRobotId } from '../store/robot'
import { alerts as fetchAlerts } from '../api/robots'
import type { Alert } from '../types'

const LEVEL_COLOR: Record<string, any> = {
  warning: 'orange',
  error: 'red',
  fatal: 'red',
  info: 'blue',
}

export default function Alerts() {
  const { selectedRid: rid } = useRobotId()
  const [level, setLevel] = useState<string>('')
  const [list, setList] = useState<Alert[]>([])
  const [loading, setLoading] = useState(false)

  const load = useCallback(async () => {
    if (!rid) return
    setLoading(true)
    try {
      const { data } = await fetchAlerts(rid, { limit: 200, level })
      setList(data)
    } finally { setLoading(false) }
  }, [rid, level])

  useEffect(() => {
    if (rid) load()
  }, [rid, load])

  const fmt = (t: string) => (t ? dayjs(t).format('MM-DD HH:mm:ss') : '-')

  const columns = [
    {
      title: '时间', dataIndex: 'ts', width: 170,
      render: (t: string) => <span>{fmt(t)}</span>,
    },
    { title: '告警ID', dataIndex: 'alert_id', width: 100 },
    {
      title: '等级', dataIndex: 'level', width: 100,
      render: (l: string) => <Tag color={LEVEL_COLOR[l] || 'blue'} size="small">{l}</Tag>,
    },
    { title: '内容', dataIndex: 'content', minWidth: 240 },
  ]

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>告警中心</h2>
        <div className="flex gap-8">
          <Select
            style={{ width: 120 }}
            value={level || undefined}
            placeholder="全部"
            onChange={(v) => { setLevel(v as string); }}
            optionList={[
              { value: '', label: '全部' },
              { value: 'warning', label: 'warning' },
              { value: 'error', label: 'error' },
              { value: 'fatal', label: 'fatal' },
            ]}
          />
          <Button icon={<IconRefresh />} loading={loading} onClick={load}>刷新</Button>
        </div>
      </div>

      <Card className="card-shadow" bordered={false}>
        <Table
          columns={columns as any}
          dataSource={list}
          rowKey="id"
          size="small"
          pagination={false}
          loading={loading}
          empty="暂无告警"
        />
      </Card>
    </div>
  )
}
