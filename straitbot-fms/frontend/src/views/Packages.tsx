import { useState, useEffect, useRef } from 'react'
import { Card, Button, Modal, Input, TextArea, Select, Switch, Table, Tag, Popconfirm, Toast } from '@douyinfe/semi-ui'
import { IconRefresh, IconUpload } from '@douyinfe/semi-icons'
import dayjs from 'dayjs'
import { listPackages, uploadPackage, deletePackage } from '../api/robots'
import type { OtaPackage } from '../types'

export default function Packages() {
  const [list, setList] = useState<OtaPackage[]>([])
  const [dlgVisible, setDlgVisible] = useState(false)
  const [file, setFile] = useState<File | null>(null)
  const [version, setVersion] = useState('')
  const [productType, setProductType] = useState('')
  const [forceFlag, setForceFlag] = useState(false)
  const [notes, setNotes] = useState('')
  const [saving, setSaving] = useState(false)
  const fileInputRef = useRef<HTMLInputElement>(null)

  const load = async () => {
    const { data } = await listPackages()
    setList(data)
  }

  const doUpload = async () => {
    if (!file) return
    setSaving(true)
    try {
      const form = new FormData()
      form.append('file', file)
      form.append('version', version)
      form.append('product_type', productType)
      form.append('force_flag', String(forceFlag))
      form.append('notes', notes)
      await uploadPackage(form)
      Toast.success('上传成功')
      setDlgVisible(false)
      setFile(null)
      setVersion('')
      setNotes('')
      load()
    } finally { setSaving(false) }
  }

  const del = async (id: number) => {
    await deletePackage(id)
    Toast.success('已删除')
    load()
  }

  const dl = (row: OtaPackage) => {
    window.open(`/api/ota/packages/${row.id}/download`, '_blank')
  }

  const human = (b: number) => (b ? (b / 1048576).toFixed(1) + 'M' : '-')
  const fmt = (t?: string) => (t ? dayjs(t).format('MM-DD HH:mm') : '-')

  const onPickFile = (e: React.ChangeEvent<HTMLInputElement>) => {
    const f = e.target.files?.[0]
    if (f) setFile(f)
  }

  useEffect(() => { load() }, [])

  const columns = [
    { title: '文件名', dataIndex: 'filename', minWidth: 280, ellipsis: true },
    { title: '版本', dataIndex: 'version', width: 100 },
    { title: '类型', dataIndex: 'product_type', width: 90 },
    {
      title: '大小',
      width: 100,
      render: (_text: any, row: OtaPackage) => human(row.size),
    },
    {
      title: '强制',
      width: 70,
      render: (_text: any, row: OtaPackage) =>
        row.force_flag ? <Tag color="orange" size="small">是</Tag> : <span>-</span>,
    },
    { title: 'MD5', dataIndex: 'md5', width: 120, ellipsis: true },
    {
      title: '上传时间',
      width: 150,
      render: (_text: any, row: OtaPackage) => fmt(row.created_at),
    },
    {
      title: '操作',
      width: 140,
      render: (_text: any, row: OtaPackage) => (
        <>
          <Button size="small" theme="borderless" onClick={() => dl(row)}>下载</Button>
          <Popconfirm title="确认删除此安装包?" onConfirm={() => del(row.id)}>
            <Button size="small" theme="borderless" type="danger">删除</Button>
          </Popconfirm>
        </>
      ),
    },
  ]

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>安装包管理</h2>
        <div className="flex gap-8">
          <Button icon={<IconRefresh />} onClick={load}>刷新</Button>
          <Button theme="solid" type="primary" icon={<IconUpload />} onClick={() => setDlgVisible(true)}>上传安装包</Button>
        </div>
      </div>

      <Card className="card-shadow" bordered={false}>
        <Table columns={columns} dataSource={list} pagination={false} rowKey="id" size="small" />
      </Card>

      {/* 上传弹窗 */}
      <Modal
        visible={dlgVisible}
        title="上传安装包"
        onCancel={() => setDlgVisible(false)}
        footer={null}
        width={560}
      >
        <div style={{ display: 'grid', gridTemplateColumns: '100px 1fr', rowGap: 12, alignItems: 'center' }}>
          <span>文件</span>
          <div
            onClick={() => fileInputRef.current?.click()}
            style={{
              border: '1px dashed #dcdfe6',
              borderRadius: 6,
              padding: '20px 12px',
              textAlign: 'center',
              cursor: 'pointer',
              color: '#909399',
              fontSize: 13,
            }}
          >
            <IconUpload style={{ marginRight: 6 }} />
            {file ? file.name : '拖拽或点击选择 zip'}
            <input
              ref={fileInputRef}
              type="file"
              accept=".zip"
              style={{ display: 'none' }}
              onChange={onPickFile}
            />
          </div>
          <span>版本号</span>
          <Input value={version} placeholder="留空则从文件名解析 (如 v2.0.15)" onChange={setVersion} />
          <span>产品类型</span>
          <Select
            value={productType}
            onChange={(v) => setProductType(v as string)}
            style={{ width: '100%' }}
            optionList={[
              { value: '', label: '自动识别' },
              { value: 'floor', label: '室内(floor)' },
              { value: 'outdoor', label: '室外(outdoor)' },
            ]}
          />
          <span>强制候选</span>
          <Switch checked={forceFlag} onChange={setForceFlag} />
          <span>说明</span>
          <TextArea value={notes} onChange={setNotes} rows={2} />
        </div>
        <div className="flex gap-8 mt-12" style={{ justifyContent: 'flex-end' }}>
          <Button onClick={() => setDlgVisible(false)}>取消</Button>
          <Button theme="solid" type="primary" loading={saving} disabled={!file} onClick={doUpload}>上传</Button>
        </div>
      </Modal>
    </div>
  )
}
