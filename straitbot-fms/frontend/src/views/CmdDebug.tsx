import { useState } from 'react'
import { Card, Button, Form, InputNumber, TextArea, Toast } from '@douyinfe/semi-ui'
import { useRobotId } from '../store/robot'
import {
  rawCmd, cmdHome, cmdCharge, cmdSelfCheck, cmdClearAlert, cmdRestartApp,
} from '../api/robots'

export default function CmdDebug() {
  const { selectedRid: rid } = useRobotId()
  const [form, setForm] = useState({ cmd: 21, dataStr: '{}' })
  const [result, setResult] = useState('')
  const [busy, setBusy] = useState(false)

  const go = async (kind: string, arg?: number) => {
    if (!rid) { Toast.warning('请先选择机器人'); return }
    setBusy(true)
    try {
      let r
      if (kind === 'home') r = await cmdHome(rid, true)
      else if (kind === 'charge') r = await cmdCharge(rid, arg!)
      else if (kind === 'selfcheck') r = await cmdSelfCheck(rid)
      else if (kind === 'clear_alert') r = await cmdClearAlert(rid)
      else if (kind === 'restart_app') r = await cmdRestartApp(rid)
      setResult(JSON.stringify(r?.data, null, 2))
      Toast.success(r?.data?.msg || '已下发')
    } finally { setBusy(false) }
  }

  const sendRaw = async () => {
    if (!rid) { Toast.warning('请先选择机器人'); return }
    let payload: any = {}
    try {
      payload = form.dataStr.trim() ? JSON.parse(form.dataStr) : {}
    } catch {
      Toast.error('data 不是合法 JSON')
      return
    }
    setBusy(true)
    try {
      const { data } = await rawCmd(rid, form.cmd, payload)
      setResult(JSON.stringify(data, null, 2))
    } finally { setBusy(false) }
  }

  return (
    <div className="page-container">
      <div className="mb-12"><h2 style={{ margin: 0 }}>指令调试</h2></div>
      <Card className="card-shadow mb-12" bordered={false} title="常用指令">
        <div className="flex gap-8" style={{ flexWrap: 'wrap' }}>
          <Button onClick={() => go('home')} loading={busy}>返航复位</Button>
          <Button onClick={() => go('charge', 1)} loading={busy}>开始充电</Button>
          <Button onClick={() => go('charge', 0)} loading={busy}>停止充电</Button>
          <Button onClick={() => go('selfcheck')} loading={busy}>触发自检</Button>
          <Button onClick={() => go('clear_alert')} loading={busy}>清除告警</Button>
          <Button type="warning" theme="solid" onClick={() => go('restart_app')} loading={busy}>重启上位机</Button>
        </div>
      </Card>

      <Card className="card-shadow mb-12" bordered={false} title="自定义指令透传 (cmd + data)">
        <Form labelPosition="left" labelWidth={80} style={{ maxWidth: 600 }}>
          <Form.Slot label="cmd">
            <InputNumber
              value={form.cmd}
              min={1}
              max={999}
              onChange={(v) => setForm((f) => ({ ...f, cmd: Number(v) || 1 }))}
              style={{ width: 200 }}
            />
          </Form.Slot>
          <Form.Slot label="data">
            <TextArea
              value={form.dataStr}
              rows={4}
              placeholder='JSON, 如 {"go_home": true}'
              className="text-mono"
              onChange={(v) => setForm((f) => ({ ...f, dataStr: v }))}
            />
          </Form.Slot>
          <Form.Slot>
            <Button theme="solid" type="primary" onClick={sendRaw} loading={busy}>发送</Button>
          </Form.Slot>
        </Form>
      </Card>

      <Card className="card-shadow" bordered={false} title="响应">
        <pre className="log-box" style={{ margin: 0, minHeight: 60 }}>{result || '(无)'}</pre>
      </Card>
    </div>
  )
}
