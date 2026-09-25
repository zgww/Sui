import { useState, useEffect, useMemo } from 'react'
import { Card, Button, Tag, TextArea, Toast, Banner } from '@douyinfe/semi-ui'
import { getThingModel, saveThingModel } from '../../api/control'

export default function ThingModel() {
  const [modelText, setModelText] = useState('')
  const [saving, setSaving] = useState(false)

  const modelSize = useMemo(() => modelText.length, [modelText])

  const load = async () => {
    try {
      const { data } = await getThingModel()
      setModelText(JSON.stringify(data, null, 2))
    } catch {
      Toast.error('加载失败')
    }
  }

  const save = async () => {
    setSaving(true)
    try {
      const parsed = JSON.parse(modelText)
      await saveThingModel(parsed)
      Toast.success('物模型已保存')
    } catch {
      Toast.error('JSON 格式错误, 保存失败')
    } finally { setSaving(false) }
  }

  useEffect(() => { load() }, [])

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>物模型管理</h2>
        <div className="flex gap-8">
          <Button onClick={load}>重新加载</Button>
          <Button theme="solid" type="primary" loading={saving} onClick={save}>保存</Button>
        </div>
      </div>

      <Banner
        className="mb-12"
        type="info"
        fullMode={false}
        closeIcon={null}
        description={
          <div>
            物模型定义了机器人的属性、配置、服务和告警码。修改后保存即生效, 影响所有机器人。
            <br />可直接编辑 JSON, 也可 SSH 到服务器修改 <code>backend/data/thing_model.json</code>。
          </div>
        }
      />

      <Card className="card-shadow" bordered={false}
        header={
          <div className="flex-between">
            <span>物模型 JSON</span>
            <Tag size="small">{modelSize} 字符</Tag>
          </div>
        }
      >
        <TextArea
          value={modelText}
          rows={28}
          className="text-mono"
          placeholder="加载中..."
          onChange={(v) => setModelText(v)}
        />
      </Card>
    </div>
  )
}
