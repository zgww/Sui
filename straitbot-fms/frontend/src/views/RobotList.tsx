import { useState, useEffect, useRef } from 'react'
import { useNavigate } from 'react-router-dom'
import {
  Card, Table, Button, Tag, Modal, Form, Input, InputNumber, Select, Switch,
  Divider, Popconfirm, Toast, Collapse, TextArea,
} from '@douyinfe/semi-ui'
import { IconRefresh, IconPlus, IconSearch } from '@douyinfe/semi-icons'
import { useUser } from '../store/user'
import { listRobots, createRobot, updateRobot, deleteRobot, pingRobot } from '../api/robots'
import { scanNetwork, addBatch, getLocalNetworks } from '../api/scan'
import type { Robot, ScanItem } from '../types'

function blankForm() {
  return {
    name: '', robot_id: 1, ip: '', api_port: 6002, product_type: '',
    ssh_user: 'nav', ssh_pass: 'nav2022', ssh_port: 22,
    log_dir: '/home/nav/robot/robot/filelog', install_dir: '/home/nav/robot',
    version_file: '/home/nav/robot/robot/version',
    poll_status: true, poll_meta: true, log_retention_days: 30, enabled: true, note: '',
    video_server: 'http://192.168.6.54:30080',
    video_secret: 'gHbMcpaSxOGf4wnRq75BQBUrxt680UiF',
    video_visible_stream: '', video_thermal_stream: '',
    video_protocol: 'webrtc', video_use_robot_ip: false,
  }
}

function buildHkStream(ip: string, ch: number, ssm: number) {
  const p = (ip || '').split('.')
  if (p.length < 4) return `channel-${ch}-subStream-${ssm}-hk-video-???-rtspPortundefined`
  return `channel-${ch}-subStream-${ssm}-hk-video-${p[2]}${p[3]}-rtspPortundefined`
}

export default function RobotList() {
  const navigate = useNavigate()
  const user = useUser()
  const [list, setList] = useState<Robot[]>([])
  const [loading, setLoading] = useState(false)
  const [dlgVisible, setDlgVisible] = useState(false)
  const [editId, setEditId] = useState<number | null>(null)
  const [saving, setSaving] = useState(false)
  const [form, setForm] = useState<any>(blankForm())

  // 扫描发现
  const [scanPanel, setScanPanel] = useState(false)
  const [scanCidr, setScanCidr] = useState('')
  const [scanPort, setScanPort] = useState(6002)
  const [scanning, setScanning] = useState(false)
  const [scanItems, setScanItems] = useState<(ScanItem & { name: string; product_type: string; ssh_user: string; ssh_pass: string })[]>([])
  const [scanChecked, setScanChecked] = useState<any[]>([])
  const [localNets, setLocalNets] = useState<any[]>([])

  const load = async () => {
    setLoading(true)
    try { const { data } = await listRobots(); setList(data) }
    finally { setLoading(false) }
  }

  useEffect(() => { load() }, [])

  const openScanPanel = async () => {
    setScanPanel(true)
    if (!localNets.length) {
      try {
        const { data } = await getLocalNetworks()
        setLocalNets(data.networks || [])
        if (!scanCidr && data.default) setScanCidr(data.default)
      } catch { /* */ }
    }
  }

  const openAdd = () => { setForm(blankForm()); setEditId(null); setDlgVisible(true) }

  const openEdit = (row: Robot) => {
    const { id, created_at, updated_at, last_battery, last_version, last_seen, online, ...rest } = row
    setForm({ ...rest }); setEditId(id); setDlgVisible(true)
  }

  const save = async () => {
    setSaving(true)
    try {
      if (editId) await updateRobot(editId, form)
      else await createRobot(form)
      Toast.success('已保存')
      setDlgVisible(false)
      load()
    } finally { setSaving(false) }
  }

  const del = async (row: Robot) => {
    await deleteRobot(row.id)
    Toast.success('已删除')
    load()
  }

  const ping = async (row: Robot) => {
    const { data } = await pingRobot(row.id)
    data.ok ? Toast.success(data.msg) : Toast.warning(data.msg)
  }

  const doScan = async () => {
    if (!scanCidr.trim()) { Toast.warning('请输入网段'); return }
    setScanning(true)
    setScanItems([])
    try {
      const { data } = await scanNetwork(scanCidr.trim(), scanPort)
      setScanItems(data.items.map((r: ScanItem) => ({
        ...r, name: '', product_type: ({ 0: 'indoor', 1: 'outdoor', 2: 'mini' } as any)[r.product || 0] || 'outdoor',
        ssh_user: r.ssh_user || 'nav', ssh_pass: r.ssh_pass || 'nav2022',
      })))
      const found = data.items.length
      const added = data.items.filter((i: ScanItem) => i.already_added).length
      Toast.success(`发现 ${found} 台 (${added} 台已添加, ${found - added} 台待添加)`)
    } catch (e: any) {
      if (e.response?.data?.detail) Toast.error(e.response.data.detail)
    } finally { setScanning(false) }
  }

  const doAddFound = async () => {
    if (!scanChecked.length) return
    const robots = scanChecked.map((r) => ({
      ip: r.ip, robot_id: r.robot_id || 1,
      name: r.name || `机器人-${r.ip.split('.')[3]}`,
      product_type: r.product_type || 'outdoor', ssh_user: r.ssh_user || 'nav', ssh_pass: r.ssh_pass || 'nav2022',
    }))
    const { data } = await addBatch(robots)
    Toast.success(data.msg)
    await load()
    doScan()
  }

  const columns = [
    { title: '名称', dataIndex: 'name', minWidth: 120, render: (text: string, r: Robot) => <a onClick={() => navigate(`/robots/${r.id}`)}>{text}</a> },
    { title: 'IP', dataIndex: 'ip', width: 140 },
    { title: '本体ID', dataIndex: 'robot_id', width: 80 },
    { title: 'API端口', dataIndex: 'api_port', width: 90 },
    { title: '类型', dataIndex: 'product_type', width: 90 },
    { title: '版本', dataIndex: 'last_version', width: 100 },
    {
      title: '启用', dataIndex: 'enabled', width: 70,
      render: (v: boolean) => <Tag color={v ? 'green' : 'grey'} size="small">{v ? '是' : '否'}</Tag>,
    },
  ]

  if (user.isEngineer) {
    columns.push({
      title: '操作', width: 260,
      render: (_: any, r: Robot) => (
        <>
          <Button size="small" onClick={() => ping(r)}>连通性</Button>
          <Button size="small" theme="solid" type="primary" onClick={() => openEdit(r)} style={{ marginLeft: 4 }}>编辑</Button>
          <Popconfirm title="确认删除?" onConfirm={() => del(r)}>
            <Button size="small" type="danger" style={{ marginLeft: 4 }}>删除</Button>
          </Popconfirm>
        </>
      ),
    } as any)
  }

  const setField = (k: string, v: any) => setForm((f: any) => ({ ...f, [k]: v }))

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>机器人列表</h2>
        <div className="flex gap-8">
          <Button icon={<IconRefresh />} loading={loading} onClick={load}>刷新</Button>
          {user.isEngineer && (
            <Button icon={<IconSearch />} onClick={() => scanPanel ? setScanPanel(false) : openScanPanel()}>
              {scanPanel ? '收起扫描' : '扫描发现'}
            </Button>
          )}
          {user.isEngineer && <Button icon={<IconPlus />} theme="solid" type="primary" onClick={openAdd}>添加</Button>}
        </div>
      </div>

      {scanPanel && (
        <Card className="card-shadow mb-12" bordered={false}
          header={
            <div className="flex-between">
              <span><IconSearch /> 扫描网段发现机器人</span>
              <div className="flex gap-8">
                <Button size="small" theme="solid" type="primary" loading={scanning} icon={<IconSearch />} onClick={doScan}>开始扫描</Button>
                <Button size="small" type="primary" disabled={!scanChecked.length || scanning} onClick={doAddFound}>添加勾选 ({scanChecked.length})</Button>
              </div>
            </div>
          }
        >
          <div className="flex gap-8" style={{ flexWrap: 'wrap', marginBottom: 12 }}>
            <span>网段:</span>
            <Select style={{ width: 240 }} filter allowCreate value={scanCidr || undefined} placeholder="选择或输入网段"
              optionList={localNets.map((n) => ({ value: n.cidr, label: `${n.cidr} (${n.interface}: ${n.ip})` }))}
              onChange={(v) => setScanCidr(v as string)} />
            <span>API端口:</span>
            <InputNumber value={scanPort} min={1} max={65535} onChange={(v) => setScanPort(Number(v) || 6002)} style={{ width: 110 }} />
          </div>
          <Table
            columns={[
              { title: 'IP', dataIndex: 'ip', minWidth: 130, render: (t: string) => <span className="text-mono">{t}</span> },
              { title: '本体ID', dataIndex: 'robot_id', width: 100 },
              { title: '名称', dataIndex: 'name', minWidth: 140 },
              { title: '类型', dataIndex: 'product_type', width: 120 },
              { title: 'SSH账号', dataIndex: 'ssh_user', width: 110 },
              { title: 'SSH密码', dataIndex: 'ssh_pass', width: 130 },
              { title: '固件版本', dataIndex: 'firmware', width: 100, render: (_: any, r: any) => r.firmware || r.motion || '-' },
              { title: 'SN', dataIndex: 'sn', minWidth: 140 },
            ]}
            dataSource={scanItems}
            rowKey="ip"
            size="small"
            pagination={false}
            loading={scanning}
            rowSelection={{
              onChange: (keys, rows) => setScanChecked(rows || []),
              getCheckboxProps: (r) => ({ disabled: (r as any).already_added }),
            }}
          />
        </Card>
      )}

      <Card className="card-shadow" bordered={false}>
        <Table columns={columns as any} dataSource={list} rowKey="id" size="small" pagination={false} loading={loading} />
      </Card>

      <Modal visible={dlgVisible} title={editId ? '编辑机器人' : '添加机器人'} onCancel={() => setDlgVisible(false)} footer={null} width={640}>
        <Form labelPosition="inset" style={{ maxWidth: 540 }}>
          <Form.Slot label="名称">
            <Input value={form.name} onChange={(v) => setField('name', v)} />
          </Form.Slot>
          <Form.Slot label="本体ID">
            <InputNumber value={form.robot_id} min={1} onChange={(v) => setField('robot_id', Number(v) || 1)} />
          </Form.Slot>
          <Form.Slot label="IP">
            <Input value={form.ip} placeholder="192.168.6.109" onChange={(v) => setField('ip', v)} />
          </Form.Slot>
          <Form.Slot label="API端口">
            <InputNumber value={form.api_port} min={1} max={65535} onChange={(v) => setField('api_port', Number(v) || 6002)} />
          </Form.Slot>
          <Form.Slot label="产品类型">
            <Select value={form.product_type || undefined} allowCreate
              optionList={[{ value: '', label: '未知' }, { value: 'floor', label: '室内' }, { value: 'outdoor', label: '室外' }, { value: 'mini', label: 'Mini' }]}
              onChange={(v: any) => setField('product_type', v)} />
          </Form.Slot>
          <Divider align="left">SSH</Divider>
          <Form.Slot label="SSH用户">
            <Input value={form.ssh_user} onChange={(v) => setField('ssh_user', v)} />
          </Form.Slot>
          <Form.Slot label="SSH密码">
            <Input mode="password" value={form.ssh_pass} onChange={(v) => setField('ssh_pass', v)} />
          </Form.Slot>
          <Form.Slot label="SSH端口">
            <InputNumber value={form.ssh_port} onChange={(v) => setField('ssh_port', Number(v) || 22)} />
          </Form.Slot>
          <Divider align="left">路径</Divider>
          <Form.Slot label="日志目录">
            <Input value={form.log_dir} onChange={(v) => setField('log_dir', v)} />
          </Form.Slot>
          <Form.Slot label="安装目录">
            <Input value={form.install_dir} onChange={(v) => setField('install_dir', v)} />
          </Form.Slot>
          <Form.Slot label="版本文件">
            <Input value={form.version_file} onChange={(v) => setField('version_file', v)} />
          </Form.Slot>
          <Divider align="left">视频流 (ZLMediaKit)</Divider>
          <div className="text-muted" style={{ fontSize: 12, marginBottom: 8 }}>
            填好 IP + ZLM 地址即可播放。流名按海康规律自动生成。
          </div>
          <Form.Slot label="ZLM地址">
            <Input value={form.video_server} placeholder="http://192.168.6.54:30080" onChange={(v) => setField('video_server', v)} />
          </Form.Slot>
          <Form.Slot label="ZLM Secret">
            <Input mode="password" value={form.video_secret} onChange={(v) => setField('video_secret', v)} />
          </Form.Slot>
          <div style={{ marginBottom: 8 }}>
            <div className="text-muted" style={{ fontSize: 12 }}>流名预览:</div>
            <div style={{ color: '#67c23a', fontSize: 12, fontFamily: 'Consolas,monospace' }}>可见光: live/{buildHkStream(form.ip, 1, 1)}</div>
            <div style={{ color: '#e6a23c', fontSize: 12, fontFamily: 'Consolas,monospace' }}>红外: live/{buildHkStream(form.ip, 2, 2)}</div>
          </div>
          <Collapse>
            <Collapse.Panel header="高级(自定义流名, 留空用上面的规律)" itemKey="adv">
              <Form.Slot label="可见光流">
                <Input className="text-mono" placeholder="留空=自动" value={form.video_visible_stream} onChange={(v) => setField('video_visible_stream', v)} />
              </Form.Slot>
              <Form.Slot label="红外流">
                <Input className="text-mono" placeholder="留空=自动" value={form.video_thermal_stream} onChange={(v) => setField('video_thermal_stream', v)} />
              </Form.Slot>
            </Collapse.Panel>
          </Collapse>
          <Divider align="left">策略</Divider>
          <div className="flex gap-12" style={{ flexWrap: 'wrap' }}>
            <span>轮询状态: <Switch checked={form.poll_status} onChange={(v) => setField('poll_status', v)} /></span>
            <span>轮询元数据: <Switch checked={form.poll_meta} onChange={(v) => setField('poll_meta', v)} /></span>
            <span>启用: <Switch checked={form.enabled} onChange={(v) => setField('enabled', v)} /></span>
          </div>
          <Form.Slot label="日志保留天数">
            <InputNumber value={form.log_retention_days} min={0} onChange={(v) => setField('log_retention_days', Number(v) || 0)} />
          </Form.Slot>
          <Form.Slot label="备注">
            <TextArea value={form.note} rows={2} onChange={(v) => setField('note', v)} />
          </Form.Slot>
        </Form>
        <div style={{ textAlign: 'right', marginTop: 12 }}>
          <Button onClick={() => setDlgVisible(false)} style={{ marginRight: 8 }}>取消</Button>
          <Button theme="solid" type="primary" loading={saving} onClick={save}>保存</Button>
        </div>
      </Modal>
    </div>
  )
}
