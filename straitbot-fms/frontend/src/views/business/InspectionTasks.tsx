import React, { useState, useMemo, useEffect } from 'react'
import { Button, Card, Table, Empty, Tag, Modal, Input, TextArea, Banner, Toast } from '@douyinfe/semi-ui'
import { useRobotId } from '../../store/robot'
import { inspectionTasks, inspectionCreate, inspectionControl } from '../../api/control'
import http from '../../api/http'
import type { InspectionTask } from '../../types'

function statusColor(s: string): string {
  const m: Record<string, string> = {
    running: 'green',
    paused: 'orange',
    done: 'blue',
    failed: 'red',
    canceled: 'grey',
    idle: 'grey',
  }
  return m[s] || 'grey'
}

function statusText(s: string): string {
  const m: Record<string, string> = {
    running: '进行中',
    paused: '已暂停',
    done: '已完成',
    failed: '失败',
    canceled: '已取消',
    idle: '待执行',
  }
  return m[s] || s
}

export default function InspectionTasks() {
  const { selectedRid: rid } = useRobotId()
  const [tasks, setTasks] = useState<InspectionTask[]>([])
  const [showCreate, setShowCreate] = useState(false)
  const [showInfo, setShowInfo] = useState(false)
  const [infoData, setInfoData] = useState('')
  const [creating, setCreating] = useState(false)
  const [form, setForm] = useState({ name: '', content: '', schedule: '' })

  const load = async (id: number) => {
    try {
      const { data } = await inspectionTasks(id)
      setTasks(data)
    } catch {
      /* http 拦截器已处理错误提示 */
    }
  }

  // 切换机器人时重新加载任务列表
  useEffect(() => {
    if (rid) load(rid)
  }, [rid])

  const create = async () => {
    if (!rid) return
    setCreating(true)
    try {
      let content: any = null
      let schedule: any = null
      if (form.content.trim()) content = JSON.parse(form.content)
      if (form.schedule.trim()) schedule = JSON.parse(form.schedule)
      const { data } = await inspectionCreate({
        robot_pk: rid,
        name: form.name,
        content,
        schedule,
      })
      Toast.success(data.msg || '已创建')
      setShowCreate(false)
      setForm({ name: '', content: '', schedule: '' })
      load(rid)
    } catch (e: any) {
      Toast.error('JSON 格式错误或创建失败')
    } finally {
      setCreating(false)
    }
  }

  const control = async (taskId: number, action: number) => {
    try {
      await inspectionControl(taskId, action)
      Toast.success('已下发')
      if (rid) load(rid)
    } catch {
      /* http 拦截器已处理错误提示 */
    }
  }

  const queryInfo = async (row: InspectionTask) => {
    try {
      const { data } = await http.get(`/api/inspection/tasks/${row.id}/info`)
      setInfoData(JSON.stringify(data, null, 2))
      setShowInfo(true)
    } catch {
      /* http 拦截器已处理错误提示 */
    }
  }

  const columns = useMemo(
    () => [
      { title: 'ID', dataIndex: 'id', key: 'id', width: 60 },
      { title: '名称', dataIndex: 'name', key: 'name' },
      {
        title: '状态',
        dataIndex: 'status',
        key: 'status',
        width: 100,
        render: (text: string) => (
          <Tag color={statusColor(text) as any} size="small">
            {statusText(text)}
          </Tag>
        ),
      },
      {
        title: '创建时间',
        dataIndex: 'created_at',
        key: 'created_at',
        width: 170,
        render: (text: string) =>
          text ? text.slice(0, 16).replace('T', ' ') : '-',
      },
      {
        title: '操作',
        key: 'op',
        width: 240,
        render: (_: any, row: InspectionTask) => (
          <>
            <Button size="small" theme="borderless" onClick={() => control(row.id, 2)}>
              恢复
            </Button>
            <Button size="small" theme="borderless" onClick={() => control(row.id, 1)}>
              暂停
            </Button>
            <Button size="small" theme="borderless" type="danger" onClick={() => control(row.id, 0)}>
              取消
            </Button>
            <Button size="small" theme="borderless" onClick={() => queryInfo(row)}>
              详情
            </Button>
          </>
        ),
      },
    ],
    [rid] // eslint-disable-line react-hooks/exhaustive-deps
  )

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>巡检任务</h2>
      </div>

      <Card
        bordered={false}
        className="card-shadow mt-12"
        title="巡检任务列表"
        headerExtraContent={
          <Button
            size="small"
            theme="solid"
            type="primary"
            onClick={() => setShowCreate(true)}
            disabled={!rid}
          >
            创建任务
          </Button>
        }
      >
        {tasks.length === 0 ? (
          <Empty description="暂无巡检任务" />
        ) : (
          <Table
            columns={columns}
            dataSource={tasks}
            pagination={false}
            rowKey="id"
            size="small"
          />
        )}
      </Card>

      {/* 创建任务 */}
      <Modal
        visible={showCreate}
        title="创建巡检任务 (cmd=100)"
        width={640}
        onCancel={() => setShowCreate(false)}
        footer={null}
      >
        <Banner type="info" fullMode={false} className="mb-12" description="巡检任务详细数据结构(航点/动作/排期)待确认, 当前为基础框架。" />
        <div style={{ marginBottom: 12 }}>
          <label style={{ display: 'block', marginBottom: 4 }}>任务名称</label>
          <Input
            value={form.name}
            onChange={(v) => setForm({ ...form, name: v })}
            placeholder="如: A区日常巡检"
          />
        </div>
        <div style={{ marginBottom: 12 }}>
          <label style={{ display: 'block', marginBottom: 4 }}>巡检内容</label>
          <TextArea
            value={form.content}
            onChange={(v) => setForm({ ...form, content: v })}
            rows={5}
            placeholder='JSON 格式: {"plan":"plan_1","waypoint":[...]}'
            className="text-mono"
          />
        </div>
        <div style={{ marginBottom: 12 }}>
          <label style={{ display: 'block', marginBottom: 4 }}>时间排期</label>
          <TextArea
            value={form.schedule}
            onChange={(v) => setForm({ ...form, schedule: v })}
            rows={3}
            placeholder='可选 JSON, 如 {"begin_time":"2024-01-16 00:00:00","interval":3600}'
            className="text-mono"
          />
        </div>
        <div style={{ textAlign: 'right' }}>
          <Button onClick={() => setShowCreate(false)} style={{ marginRight: 8 }}>
            取消
          </Button>
          <Button theme="solid" type="primary" loading={creating} onClick={create}>
            创建并下发
          </Button>
        </div>
      </Modal>

      {/* 巡检详情 */}
      <Modal
        visible={showInfo}
        title="巡检详情 (cmd=102)"
        width={600}
        onCancel={() => setShowInfo(false)}
        footer={null}
      >
        <pre className="log-box" style={{ maxHeight: 400 }}>
          {infoData}
        </pre>
      </Modal>
    </div>
  )
}
