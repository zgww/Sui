import React, { useMemo, useState } from 'react'
import {
  Button, Card, Table, Tag, Input, Select, Modal, Checkbox,
  Banner, Typography,
} from '@douyinfe/semi-ui'
import { IconPlus, IconSearch } from '@douyinfe/semi-icons'
import { ALARM_TEMPLATES, TEMPLATE_POINTS } from './data'
import { FormRow, SectionTitle } from './shared'
import './sink.css'

const { Title, Text } = Typography

type Dlg = '' | 'tpl' | 'rebind' | 'bind' | 'unbind' | 'delete'

export default function AlarmTemplate() {
  const [dlg, setDlg] = useState<Dlg>('')
  const [tplIdx, setTplIdx] = useState(0)

  const open = (d: Dlg) => () => setDlg(d)
  const close = () => setDlg('')

  // ---------- 模板列表列 ----------

  const tplColumns = useMemo(() => [
    { title: 'ID', dataIndex: 'id', key: 'id', width: 45 },
    { title: '模板名称', dataIndex: 'name', key: 'name' },
    { title: '类型', dataIndex: 'type', key: 'type', width: 90 },
    {
      title: '传感器类型', dataIndex: 'sensor', key: 'sensor', width: 100,
      render: (v: string, r: { sensorColor: string }) => <Tag color={r.sensorColor as any} size="small">{v}</Tag>,
    },
    { title: '算法标识', dataIndex: 'algorithm', key: 'algorithm', width: 120, render: (v: string) => <Text code>{v}</Text> },
    {
      title: '操作', key: 'op', width: 130,
      render: (v: unknown, r: { id: number }) => (
        <div style={{ display: 'flex', gap: 2 }}>
          <Button size="small" theme="borderless" type="primary" onClick={() => setTplIdx(r.id - 1)}>详情</Button>
          <Button size="small" theme="borderless" type="primary" onClick={open('tpl')}>编辑</Button>
          <Button size="small" theme="borderless" type="danger" onClick={open('delete')}>删除</Button>
        </div>
      ),
    },
  ], [])

  // ---------- 已关联测点列 ----------

  const ptColumns = useMemo(() => [
    { title: 'ID', dataIndex: 'id', key: 'id', width: 45 },
    { title: '变电站名称', dataIndex: 'substation', key: 'substation', width: 120 },
    { title: '间隔', dataIndex: 'bay', key: 'bay', width: 95 },
    { title: '设备名称', dataIndex: 'equipment', key: 'equipment', width: 125 },
    { title: '测点名称', dataIndex: 'point', key: 'point', width: 95 },
    {
      title: '操作', key: 'op', width: 105,
      render: () => (
        <div style={{ display: 'flex', gap: 2 }}>
          <Button size="small" theme="borderless" type="primary" onClick={open('rebind')}>换绑</Button>
          <Button size="small" theme="borderless" type="danger" onClick={open('unbind')}>解绑</Button>
        </div>
      ),
    },
  ], [])

  // ---------- 换绑 / 批量绑定的多选表列 ----------

  const pickColumns = useMemo(() => [
    { title: '变电站名称', dataIndex: 'substation', key: 'substation', width: 150 },
    { title: '间隔', dataIndex: 'bay', key: 'bay', width: 110 },
    { title: '设备名称', dataIndex: 'equipment', key: 'equipment', width: 160 },
    { title: '测点名称', dataIndex: 'point', key: 'point', width: 110 },
    { title: '绑定状态', key: 'bound', width: 90, render: (v: unknown, r: { id: number }) => (r.id <= 4 ? <Tag color="grey" size="small">已绑其他</Tag> : <Tag color="green" size="small">未绑定</Tag>) },
  ], [])

  return (
    <div style={{ padding: '4px 2px' }}>
      {/* 页头 */}
      <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between', flexWrap: 'wrap', gap: 10, marginBottom: 12 }}>
        <div style={{ display: 'flex', alignItems: 'baseline', gap: 10 }}>
          <Title heading={5} style={{ margin: 0 }}>告警模板</Title>
          <Text type="tertiary" size="small">模板 CRUD · 检测项与告警规则 · 测点绑定 / 换绑 / 批量绑定（下沉自平台「告警模板（新）」）</Text>
        </div>
        <div style={{ display: 'flex', gap: 6, flexWrap: 'wrap' }}>
          <Tag>模板 5</Tag><Tag color="blue">关联测点 12</Tag><Tag color="orange">待换绑 2</Tag>
        </div>
      </div>

      <Banner
        type="info"
        closeIcon={null}
        style={{ marginBottom: 12 }}
        description={<>点击左侧模板行，右侧展示该模板已关联测点；换绑 = 解绑旧模板并按新模板重建阈值链（四级克隆快照），可选是否覆盖原告警设置。</>}
      />

      {/* 筛选条 */}
      <Card style={{ marginBottom: 12 }} bodyStyle={{ paddingTop: 12, paddingBottom: 12 }}>
        <div style={{ display: 'flex', alignItems: 'center', flexWrap: 'wrap', gap: 10 }}>
          <span>模板名称</span>
          <Input placeholder="请输入" style={{ width: 200 }} />
          <Button theme="solid" type="primary" size="small" icon={<IconSearch />}>查询</Button>
          <Button size="small">重置</Button>
          <span style={{ flex: 1 }} />
          <Button size="small" onClick={open('rebind')}>测点换绑</Button>
          <Button size="small" onClick={open('bind')}>批量绑定</Button>
          <Button size="small" theme="solid" type="primary" icon={<IconPlus />} onClick={open('tpl')}>新增</Button>
        </div>
      </Card>

      {/* 左列表 + 右关联测点 */}
      <div style={{ display: 'flex', gap: 12, alignItems: 'stretch' }}>
        <Card title="模板列表" style={{ flex: '0 0 55%' }} bodyStyle={{ paddingTop: 12 }}>
          <Table
            columns={tplColumns as any}
            dataSource={ALARM_TEMPLATES}
            pagination={{ pageSize: 5 }}
            size="small"
            onRow={((r: { id: number }) => ({
              onClick: () => setTplIdx(r.id - 1),
              style: { cursor: 'pointer', background: r.id - 1 === tplIdx ? 'rgba(0,119,250,.06)' : undefined },
            })) as any}
          />
        </Card>

        <Card title={`已关联测点 — ${ALARM_TEMPLATES[tplIdx]?.name ?? ''}`} style={{ flex: 1 }} bodyStyle={{ paddingTop: 12 }}>
          <div style={{ display: 'flex', alignItems: 'center', gap: 8, marginBottom: 12 }}>
            <Input placeholder="测点 / 变电站 / 设备 / 间隔" style={{ width: 220 }} />
            <Button size="small" theme="solid" type="primary">查询</Button>
            <Button size="small">重置</Button>
          </div>
          <Table columns={ptColumns as any} dataSource={TEMPLATE_POINTS} pagination={{ pageSize: 5 }} size="small" />
        </Card>
      </div>

      <Text type="tertiary" size="small" style={{ display: 'block', marginTop: 10 }}>
        本页为下沉静态界面（示例数据），接口与业务逻辑待开发。
      </Text>

      {/* ==================== 弹窗：新增 / 编辑模板（详情共用） ==================== */}
      <Modal
        title="新增 / 编辑告警模板（详情共用此表单）"
        visible={dlg === 'tpl'}
        onCancel={close}
        width={860}
        footer={(
          <>
            <Text type="tertiary" size="small" style={{ marginRight: 'auto' }}>编辑保存时可选择是否同步覆盖已关联测点的阈值（不覆盖 / 覆盖全部 / 仅覆盖指定测点）</Text>
            <Button onClick={close}>取消</Button>
            <Button theme="solid" type="primary" onClick={close}>保存</Button>
          </>
        )}
      >
        <div style={{ maxHeight: '62vh', overflow: 'auto', padding: '2px 2px 8px' }}>
          <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', columnGap: 20 }}>
            <FormRow label="传感器类型" required hint="决定可用的算法与检测项；批量绑定时校验测点传感器类型一致">
              <Select style={{ width: '100%' }} defaultValue="temp" optionList={[
                { value: 'temp', label: '温度传感器' }, { value: 'press', label: '压力传感器' },
                { value: 'ir', label: '红外热像仪' }, { value: 'cam', label: '图像摄像头' }, { value: 'pd', label: '局放传感器' },
              ]} />
            </FormRow>
            <FormRow label="基础类型">
              <Select style={{ width: '100%' }} defaultValue="vis" optionList={[{ value: 'vis', label: '可见光' }, { value: 'ir', label: '红外' }, { value: 'video', label: '视频' }]} />
            </FormRow>
            <FormRow label="检测类型名称" required hint="20 字以内"><Input defaultValue="油温表-指针读数" /></FormRow>
            <FormRow label="算法标识">
              <Select style={{ width: '100%' }} defaultValue="a1" optionList={[
                { value: 'a1', label: 'meter-read-v3' }, { value: 'a2', label: 'infrared-max-v2' }, { value: 'a3', label: 'appearance-defect-v1' },
              ]} />
            </FormRow>
          </div>

          <SectionTitle>检测项</SectionTitle>
          <div style={{ border: '1px solid var(--semi-color-border)', borderRadius: 6, padding: 12 }}>
            <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', columnGap: 20 }}>
              <FormRow label="数据名称" required><Input defaultValue="指针示值" /></FormRow>
              <FormRow label="代码"><Input defaultValue="value" /></FormRow>
              <FormRow label="数值类型" required>
                <Select style={{ width: '100%' }} defaultValue="f" optionList={[{ value: 'i', label: '整数' }, { value: 'f', label: '小数' }, { value: 'e', label: '枚举' }, { value: 'b', label: '布尔' }]} />
              </FormRow>
              <FormRow label="数值单位" required>
                <Select style={{ width: '100%' }} defaultValue="c" optionList={[{ value: 'c', label: '℃' }, { value: 'mpa', label: 'MPa' }, { value: 'kv', label: 'kV' }, { value: 'pct', label: '%' }]} />
              </FormRow>
            </div>
            <FormRow label="量程范围">
              <div style={{ display: 'flex', gap: 8, alignItems: 'center', flexWrap: 'wrap' }}>
                <Input defaultValue="0" style={{ width: 80 }} /> – <Input defaultValue="120" style={{ width: 80 }} />
                精度 <Input defaultValue="0.1" style={{ width: 70 }} />
                <Button size="small">＋ 行</Button><Button size="small" type="danger" theme="light">－ 行</Button>
              </div>
            </FormRow>
            <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', columnGap: 20 }}>
              <FormRow label="默认值" required><Input defaultValue="0" /></FormRow>
              <FormRow label="告警描述" required><Input defaultValue="主变油温越限" /></FormRow>
            </div>
            <FormRow label="默认告警设置">
              <div style={{ display: 'flex', flexDirection: 'column', gap: 8 }}>
                <div style={{ display: 'flex', gap: 6, flexWrap: 'wrap', alignItems: 'center' }}>
                  <Select defaultValue="th" style={{ width: 100 }} optionList={[{ value: 'th', label: '阈值' }, { value: 'rg', label: '范围值' }, { value: 'en', label: '枚举值' }, { value: 'bo', label: '布尔值' }]} />
                  <Select defaultValue="gt" style={{ width: 76 }} optionList={[{ value: 'gt', label: '>' }, { value: 'ge', label: '>=' }, { value: 'lt', label: '<' }, { value: 'le', label: '<=' }]} />
                  <Input defaultValue="85" style={{ width: 72 }} />
                  <Select defaultValue="c" style={{ width: 70 }} optionList={[{ value: 'c', label: '℃' }]} />
                  <Select defaultValue="g1" style={{ width: 100 }} optionList={[{ value: 'g0', label: '预告警' }, { value: 'g1', label: '一般告警' }, { value: 'g2', label: '严重告警' }]} />
                  <Button size="small">＋</Button><Button size="small" type="danger" theme="light">－</Button>
                </div>
                <div style={{ display: 'flex', gap: 6, flexWrap: 'wrap', alignItems: 'center' }}>
                  <Select defaultValue="th" style={{ width: 100 }} optionList={[{ value: 'th', label: '阈值' }]} />
                  <Select defaultValue="gt" style={{ width: 76 }} optionList={[{ value: 'gt', label: '>' }]} />
                  <Input defaultValue="95" style={{ width: 72 }} />
                  <Select defaultValue="c" style={{ width: 70 }} optionList={[{ value: 'c', label: '℃' }]} />
                  <Select defaultValue="g2" style={{ width: 100 }} optionList={[{ value: 'g2', label: '严重告警' }]} />
                  <Button size="small">＋</Button><Button size="small" type="danger" theme="light">－</Button>
                </div>
              </div>
            </FormRow>
          </div>
        </div>
      </Modal>

      {/* ==================== 弹窗：测点换绑 ==================== */}
      <Modal
        title="测点换绑"
        visible={dlg === 'rebind'}
        onCancel={close}
        width={960}
        footer={(
          <>
            <Button onClick={close}>取消</Button>
            <Button theme="solid" type="primary" onClick={close}>确定</Button>
          </>
        )}
      >
        <div style={{ display: 'flex', gap: 12, alignItems: 'center', flexWrap: 'wrap', marginBottom: 12 }}>
          <span>原模板</span>
          <Select style={{ width: 200 }} defaultValue="t1" optionList={ALARM_TEMPLATES.map((t) => ({ value: 't' + t.id, label: t.name }))} />
          <span>新模板</span>
          <Select style={{ width: 200 }} defaultValue="t2" optionList={ALARM_TEMPLATES.filter((t) => t.id !== 1).map((t) => ({ value: 't' + t.id, label: t.name }))} />
          <Checkbox defaultChecked>覆盖告警设置</Checkbox>
        </div>
        <Banner
          type="warning" closeIcon={null} style={{ marginBottom: 12 }}
          description={<>勾选「覆盖告警设置」= 按新模板重建阈值链；不勾选则保留测点上已修改过的告警设置。换绑要求新旧模板传感器类型一致。</>}
        />
        <div style={{ display: 'flex', alignItems: 'center', gap: 8, marginBottom: 12 }}>
          <Select style={{ width: 180 }} defaultValue="s1" optionList={[{ value: 's1', label: '110kV 东郊变电站' }, { value: 's2', label: '220kV 滨湖变电站' }]} />
          <Input placeholder="设备名称" style={{ width: 150 }} />
          <Input placeholder="测点名称" style={{ width: 150 }} />
          <Button size="small" theme="solid" type="primary">查询</Button>
          <Button size="small">重置</Button>
        </div>
        <Table columns={pickColumns as any} dataSource={TEMPLATE_POINTS} pagination={{ pageSize: 5 }} size="small" rowSelection={{}} />
      </Modal>

      {/* ==================== 弹窗：批量绑定 ==================== */}
      <Modal
        title="批量绑定测点"
        visible={dlg === 'bind'}
        onCancel={close}
        width={960}
        footer={(
          <>
            <Text type="tertiary" size="small" style={{ marginRight: 'auto' }}>仅列出未绑定该模板的测点；提交后返回成功 / 失败数量与明细</Text>
            <Button onClick={close}>取消</Button>
            <Button theme="solid" type="primary" onClick={close}>保存</Button>
          </>
        )}
      >
        <div style={{ display: 'flex', alignItems: 'center', gap: 8, marginBottom: 12 }}>
          <span>告警模板</span>
          <Select style={{ width: 220 }} defaultValue="t1" optionList={ALARM_TEMPLATES.map((t) => ({ value: 't' + t.id, label: t.name }))} />
          <span style={{ flex: 1 }} />
          <Select style={{ width: 180 }} defaultValue="s1" optionList={[{ value: 's1', label: '110kV 东郊变电站' }, { value: 's2', label: '220kV 滨湖变电站' }]} />
          <Input placeholder="设备名称" style={{ width: 140 }} />
          <Input placeholder="测点名称" style={{ width: 140 }} />
          <Button size="small" theme="solid" type="primary">查询</Button>
        </div>
        <Table columns={pickColumns as any} dataSource={TEMPLATE_POINTS} pagination={{ pageSize: 5 }} size="small" rowSelection={{}} />
      </Modal>

      {/* ==================== 弹窗：解绑确认 ==================== */}
      <Modal
        title="解绑确认"
        visible={dlg === 'unbind'}
        onCancel={close}
        width={420}
        footer={(
          <>
            <Button onClick={close}>取消</Button>
            <Button theme="solid" type="danger" onClick={close}>解绑</Button>
          </>
        )}
      >
        <div style={{ fontSize: 13, lineHeight: 1.8 }}>
          确认将该测点与当前模板解绑？解绑后测点不再参与该模板的阈值判断与告警生成（示意规则）。
        </div>
      </Modal>

      {/* ==================== 弹窗：删除确认 ==================== */}
      <Modal
        title="删除确认"
        visible={dlg === 'delete'}
        onCancel={close}
        width={420}
        footer={(
          <>
            <Button onClick={close}>取消</Button>
            <Button theme="solid" type="danger" onClick={close}>删除</Button>
          </>
        )}
      >
        <div style={{ fontSize: 13, lineHeight: 1.8 }}>
          确认删除该告警模板？已绑定该模板的测点将同时解绑（示意规则，随迁确认）。
        </div>
      </Modal>
    </div>
  )
}
