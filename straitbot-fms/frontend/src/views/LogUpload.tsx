import React, { useState, useMemo, useEffect, useCallback } from 'react'
import { Card, Button, Table, Upload, Empty, Toast } from '@douyinfe/semi-ui'
import { IconRefresh, IconUpload } from '@douyinfe/semi-icons'
import dayjs from 'dayjs'
import http from '../api/http'
import { useRobotId } from '../store/robot'
import { listRobots, archivedList } from '../api/robots'
import type { ArchivedLog } from '../types'

interface UploadedItem extends ArchivedLog {
  robotId: number
  robotName: string
}

interface Group {
  id: number
  name: string
  items: UploadedItem[]
}

function human(b: number): string {
  if (!b) return '-'
  if (b < 1048576) return (b / 1024).toFixed(1) + 'K'
  return (b / 1048576).toFixed(1) + 'M'
}

function fmt(t: string): string {
  return t ? dayjs(t).format('MM-DD HH:mm') : '-'
}

const itemColumns = [
  { title: '文件名', dataIndex: 'filename', key: 'filename' },
  {
    title: '大小',
    dataIndex: 'size',
    key: 'size',
    width: 90,
    render: (text: number) => human(text),
  },
  {
    title: '时间',
    dataIndex: 'ts',
    key: 'ts',
    width: 150,
    render: (text: string) => fmt(text),
  },
]

export default function LogUpload() {
  const { selectedRid: rid } = useRobotId()
  const [allUploaded, setAllUploaded] = useState<UploadedItem[]>([])

  const loadAll = useCallback(async () => {
    try {
      const { data: robots } = await listRobots()
      const result: UploadedItem[] = []
      await Promise.all(
        robots.map(async (r) => {
          try {
            const { data } = await archivedList(r.id)
            ;(data.uploaded || []).forEach((u: ArchivedLog) => {
              result.push({ ...u, robotId: r.id, robotName: r.name })
            })
          } catch {
            /* ignore */
          }
        })
      )
      setAllUploaded(result)
    } catch {
      /* ignore */
    }
  }, [])

  const doUpload = useCallback(
    async (file: File) => {
      if (!rid) return
      const form = new FormData()
      form.append('file', file)
      form.append('robot_id', String(rid))
      form.append('source', 'manual')
      try {
        await http.post('/api/logs/upload', form, {
          timeout: 600000,
        })
        Toast.success(file.name + ' 上传成功')
        loadAll()
      } catch {
        /* http 拦截器已处理错误提示 */
      }
    },
    [rid, loadAll]
  )

  const handleBeforeUpload = ({ file }: any) => {
    const rawFile = file?.originFile || file
    if (rawFile) {
      doUpload(rawFile as File)
    }
    return false
  }

  const grouped = useMemo<Group[]>(() => {
    const m: Record<number, Group> = {}
    allUploaded.forEach((u) => {
      if (!m[u.robotId]) {
        m[u.robotId] = { id: u.robotId, name: u.robotName, items: [] }
      }
      m[u.robotId].items.push(u)
    })
    return Object.values(m).sort((a, b) => a.name.localeCompare(b.name))
  }, [allUploaded])

  useEffect(() => {
    loadAll()
  }, [loadAll])

  return (
    <div className="log-tab-pane">
      <Card bordered={false} className="card-shadow mb-12" title="上传日志到选中机器人">
        <Upload
          beforeUpload={handleBeforeUpload}
          multiple
          draggable
          disabled={!rid}
          showUploadList
          accept="*"
        >
          <div style={{ padding: '24px 0', textAlign: 'center' }}>
            <IconUpload style={{ fontSize: 36, color: '#909399' }} />
            <div style={{ marginTop: 8, color: '#606266' }}>
              拖拽文件到此处, 或<em style={{ color: '#409eff', fontStyle: 'normal' }}>点击选择</em>
            </div>
          </div>
        </Upload>
        <div className="text-muted" style={{ marginTop: 8 }}>
          日志将归档到该机器人目录下, 按保留策略自动清理
        </div>
      </Card>

      <Card
        bordered={false}
        className="card-shadow"
        title="所有机器人已上传日志"
        headerExtraContent={
          <Button size="small" icon={<IconRefresh />} onClick={loadAll}>
            刷新
          </Button>
        }
      >
        {grouped.length === 0 ? (
          <Empty description="暂无已上传日志" />
        ) : (
          grouped.map((g) => (
            <div key={g.id} className="mb-12">
              <div className="text-muted" style={{ fontWeight: 600, marginBottom: 4 }}>
                {g.name} ({g.items.length})
              </div>
              <Table
                columns={itemColumns}
                dataSource={g.items}
                pagination={false}
                rowKey="id"
                size="small"
              />
            </div>
          ))
        )}
      </Card>
    </div>
  )
}
