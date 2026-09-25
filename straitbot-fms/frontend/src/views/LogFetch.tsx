import React, { useState, useCallback, useMemo, useEffect } from 'react'
import { Button, Card, Table, Empty, Toast } from '@douyinfe/semi-ui'
import { IconRefresh, IconFolderOpen, IconFile } from '@douyinfe/semi-icons'
import { useRobotId } from '../store/robot'
import { remoteList, fetchRemote } from '../api/robots'
import type { RemoteEntry } from '../types'

function human(b: number): string {
  if (!b) return '-'
  if (b < 1024) return b + 'B'
  if (b < 1048576) return (b / 1024).toFixed(1) + 'K'
  return (b / 1048576).toFixed(1) + 'M'
}

export default function LogFetch() {
  const { selectedRid: rid } = useRobotId()
  const [sub, setSub] = useState<string[]>([])
  const [entries, setEntries] = useState<RemoteEntry[]>([])
  const [selected, setSelected] = useState<RemoteEntry[]>([])
  const [fetching, setFetching] = useState(false)
  const [cwd, setCwd] = useState('')

  const loadDir = useCallback(
    async (currentRid: number | null, currentSub: string[]) => {
      if (!currentRid) return
      try {
        const { data } = await remoteList(currentRid, currentSub.join('/'))
        setEntries(data)
        setCwd(currentSub.length ? '/' + currentSub.join('/') : '/ (根目录)')
      } catch {
        /* http 拦截器已处理错误提示 */
      }
    },
    []
  )

  // 切换机器人时重置并重新加载
  useEffect(() => {
    setSub([])
    setSelected([])
    if (rid) loadDir(rid, [])
  }, [rid])

  const enterDir = (name: string) => {
    const next = [...sub, name]
    setSub(next)
    setSelected([])
    loadDir(rid, next)
  }

  const goUp = () => {
    const next = sub.slice(0, -1)
    setSub(next)
    setSelected([])
    loadDir(rid, next)
  }

  const handleFetch = async () => {
    if (!rid || !selected.length) return
    setFetching(true)
    try {
      const files = selected.map((r) => [...sub, r.name].join('/'))
      const { data } = await fetchRemote(rid, files)
      Toast.success(data.msg || '拉取完成')
      setSelected([])
    } catch {
      /* http 拦截器已处理错误提示 */
    } finally {
      setFetching(false)
    }
  }

  const columns = useMemo(
    () => [
      {
        title: '名称',
        dataIndex: 'name',
        key: 'name',
        render: (text: string, record: RemoteEntry) => (
          <span>
            {record.is_dir ? (
              <IconFolderOpen style={{ color: '#e6a23c' }} />
            ) : (
              <IconFile style={{ color: '#909399' }} />
            )}
            {record.is_dir ? (
              <a
                style={{ marginLeft: 6, color: '#409eff', cursor: 'pointer' }}
                onClick={() => enterDir(record.name)}
              >
                {record.name}
              </a>
            ) : (
              <span style={{ marginLeft: 6 }} className="text-mono">
                {record.name}
              </span>
            )}
          </span>
        ),
      },
      {
        title: '大小',
        dataIndex: 'size',
        key: 'size',
        width: 100,
        render: (text: number, record: RemoteEntry) =>
          record.is_dir ? '-' : human(record.size),
      },
      {
        title: '修改时间',
        dataIndex: 'modify_time',
        key: 'modify_time',
        width: 170,
      },
    ],
    [sub, rid] // eslint-disable-line react-hooks/exhaustive-deps
  )

  return (
    <div className="log-tab-pane">
      <div className="flex-between mb-12">
        <Button
          size="small"
          icon={<IconRefresh />}
          onClick={() => loadDir(rid, sub)}
          disabled={!rid}
        >
          刷新目录
        </Button>
      </div>

      {rid ? (
        <Card
          bordered={false}
          className="card-shadow mb-12"
          title={
            <div className="flex-between">
              <span>远程目录: {cwd || '(请选择机器人)'}</span>
              {sub.length > 0 && (
                <Button size="small" theme="borderless" onClick={goUp}>
                  返回上级
                </Button>
              )}
            </div>
          }
        >
          <Table
            columns={columns}
            dataSource={entries}
            rowKey="name"
            size="small"
            pagination={false}
            rowSelection={{
              onChange: (_keys, rows) => setSelected(rows as RemoteEntry[]),
              getCheckboxProps: (record: RemoteEntry) => ({
                disabled: record.is_dir,
              }),
            }}
          />
          <div className="mt-12 flex gap-8">
            <Button
              theme="solid"
              type="primary"
              disabled={!selected.length}
              loading={fetching}
              onClick={handleFetch}
            >
              拉取选中 {selected.length} 个文件
            </Button>
          </div>
        </Card>
      ) : (
        <Empty description="请先选择机器人" />
      )}
    </div>
  )
}
