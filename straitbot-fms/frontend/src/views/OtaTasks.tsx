import { useState, useEffect } from 'react'
import { Card, Button, Modal, Select, Switch, Table, Tag, Toast } from '@douyinfe/semi-ui'
import { IconRefresh, IconSend } from '@douyinfe/semi-icons'
import dayjs from 'dayjs'
import { listRobots, listPackages, listTasks, createTasks, retryTask } from '../api/robots'
import type { Robot, OtaPackage, OtaTask } from '../types'

const stColorMap: Record<string, string> = {
  success: 'green',
  failed: 'red',
  running: 'orange',
  skipped: 'grey',
  pending: 'blue',
}
const stTextMap: Record<string, string> = {
  success: '成功',
  failed: '失败',
  running: '执行中',
  skipped: '跳过',
  pending: '排队中',
}

export default function OtaTasks() {
  const [robots, setRobots] = useState<Robot[]>([])
  const [packages, setPackages] = useState<OtaPackage[]>([])
  const [tasks, setTasks] = useState<OtaTask[]>([])
  const [dlgVisible, setDlgVisible] = useState(false)
  const [robotIds, setRobotIds] = useState<number[]>([])
  const [packageId, setPackageId] = useState<number | null>(null)
  const [force, setForce] = useState(false)
  const [saving, setSaving] = useState(false)
  const [logVisible, setLogVisible] = useState(false)
  const [logText, setLogText] = useState('')

  const robotName = (pk: number) => robots.find((r) => r.id === pk)?.name || '#' + pk
  const fmt = (t?: string | null) => (t ? dayjs(t).format('MM-DD HH:mm:ss') : '-')

  const viewLog = (row: OtaTask) => {
    setLogText(row.log || '(空)')
    setLogVisible(true)
  }

  const loadTasks = async () => {
    const [rt, pk, tk] = await Promise.all([listRobots(), listPackages(), listTasks()])
    setRobots(rt.data)
    setPackages(pk.data)
    setTasks(tk.data)
  }

  const submit = async () => {
    if (!robotIds.length || !packageId) { Toast.warning('请选择机器人和安装包'); return }
    setSaving(true)
    try {
      await createTasks({ robot_ids: robotIds, package_id: packageId, force })
      Toast.success('已创建升级任务')
      setDlgVisible(false)
      setRobotIds([])
      setPackageId(null)
      setForce(false)
      loadTasks()
    } finally { setSaving(false) }
  }

  const retry = async (row: OtaTask) => {
    await retryTask(row.id)
    Toast.success('已重新排队')
    loadTasks()
  }

  useEffect(() => { loadTasks() }, [])

  const columns = [
    {
      title: '机器人',
      minWidth: 100,
      render: (_text: any, row: OtaTask) => robotName(row.robot_pk),
    },
    { title: '安装包', dataIndex: 'package_filename', minWidth: 220, ellipsis: true },
    {
      title: '版本',
      width: 160,
      render: (_text: any, row: OtaTask) => `${row.from_version || '?'} → ${row.to_version || '?'}`,
    },
    {
      title: '状态',
      width: 100,
      render: (_text: any, row: OtaTask) => (
        <Tag color={(stColorMap[row.status] || 'blue') as any} size="small">{stTextMap[row.status] || row.status}</Tag>
      ),
    },
    {
      title: '强制',
      width: 70,
      render: (_text: any, row: OtaTask) => (row.force ? '是' : '-'),
    },
    { title: '发起人', dataIndex: 'created_by', width: 100 },
    {
      title: '开始/完成时间',
      width: 320,
      render: (_text: any, row: OtaTask) => (
        <div className="text-muted" style={{ fontSize: 12 }}>{fmt(row.started_at)} ~ {fmt(row.finished_at)}</div>
      ),
    },
    {
      title: '操作',
      width: 160,
      render: (_text: any, row: OtaTask) => (
        <>
          <Button size="small" theme="borderless" onClick={() => viewLog(row)}>日志</Button>
          {(row.status === 'failed' || row.status === 'pending') && (
            <Button size="small" theme="borderless" type="primary" onClick={() => retry(row)}>重试</Button>
          )}
        </>
      ),
    },
  ]

  return (
    <div>
      <div className="flex-between mb-12">
        <div />
        <div className="flex gap-8">
          <Button icon={<IconRefresh />} onClick={loadTasks}>刷新</Button>
          <Button theme="solid" type="primary" icon={<IconSend />} onClick={() => setDlgVisible(true)}>发起升级</Button>
        </div>
      </div>

      <Card className="card-shadow mb-12" bordered={false} title="升级任务">
        <Table columns={columns} dataSource={tasks} pagination={false} rowKey="id" size="small" />
      </Card>

      <Modal
        visible={dlgVisible}
        title="发起 OTA 升级"
        onCancel={() => setDlgVisible(false)}
        footer={null}
        width={640}
      >
        <div style={{ display: 'grid', gridTemplateColumns: '100px 1fr', rowGap: 12, alignItems: 'center' }}>
          <span>目标机器人</span>
          <Select
            multiple
            filter
            value={robotIds}
            onChange={(v) => setRobotIds(v as number[])}
            style={{ width: '100%' }}
            optionList={robots.map((r) => ({
              value: r.id,
              label: `${r.name} (${r.ip}) ${r.last_version ? 'v' + r.last_version : ''}`,
            }))}
          />
          <span>安装包</span>
          <Select
            value={packageId ?? undefined}
            onChange={(v) => setPackageId(v as number)}
            style={{ width: '100%' }}
            optionList={packages.map((p) => ({
              value: p.id,
              label: `${p.filename} ${p.version ? '(v' + p.version + ')' : ''}`,
            }))}
          />
          <span>强制升级</span>
          <div className="flex gap-8" style={{ alignItems: 'center' }}>
            <Switch checked={force} onChange={setForce} />
            <span className="text-muted">忽略版本对比, 全量覆盖</span>
          </div>
        </div>
        <div className="flex gap-8 mt-12" style={{ justifyContent: 'flex-end' }}>
          <Button onClick={() => setDlgVisible(false)}>取消</Button>
          <Button theme="solid" type="primary" loading={saving} onClick={submit}>确定</Button>
        </div>
      </Modal>

      <Modal
        visible={logVisible}
        title="任务日志"
        onCancel={() => setLogVisible(false)}
        footer={null}
        width={720}
      >
        <pre className="log-box">{logText}</pre>
      </Modal>
    </div>
  )
}
