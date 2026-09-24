import React, { useMemo, useState } from 'react'
import {
  Button, Card, Table, Tag, Input, Select, Modal, Checkbox, Banner, Typography,
} from '@douyinfe/semi-ui'
import { IconChevronLeft, IconChevronRight, IconRefresh, IconSearch } from '@douyinfe/semi-icons'
import { LOGS, POINT_RESULTS, SNAPSHOT_TIMES, IMAGE_THUMBS } from './data'
import './sink.css'

const { Title, Text } = Typography

type Dlg = '' | 'image' | 'video' | 'snapshot' | 'points' | 'report'

export default function InspectionLog() {
  const [dlg, setDlg] = useState<Dlg>('')
  const [thumbIdx, setThumbIdx] = useState(1)

  const open = (d: Dlg) => () => setDlg(d)
  const close = () => setDlg('')

  // ---------- 日志表列 ----------

  const columns = useMemo(() => [
    { title: 'ID', dataIndex: 'id', key: 'id', width: 70 },
    { title: '计划名称', dataIndex: 'plan', key: 'plan', width: 160 },
    { title: '巡检总点数', dataIndex: 'total', key: 'total', width: 100, render: (v: number | null) => (v == null ? '—' : v) },
    {
      title: '已完成测点数', key: 'done', width: 120,
      render: (v: unknown, r: (typeof LOGS)[number]) =>
        r.status === 'running' && r.done != null ? `${r.done} / ${r.total}` : (r.done == null ? '—' : r.done),
    },
    {
      title: '异常点数', dataIndex: 'error', key: 'error', width: 90,
      render: (v: number) => (v > 0 ? <Tag color="red" size="small">{v}</Tag> : <Tag color="grey" size="small">0</Tag>),
    },
    { title: '计划开始时间', dataIndex: 'planStart', key: 'planStart', width: 150 },
    { title: '开始时间', key: 'start', width: 150, render: (v: unknown, r: (typeof LOGS)[number]) => r.start || '—' },
    {
      title: '结束时间', key: 'end', width: 150,
      render: (v: unknown, r: (typeof LOGS)[number]) => {
        if (r.status === 'running') return <Text type="success">执行中…</Text>
        return r.end || '—'
      },
    },
    {
      title: '操作', key: 'op',
      render: (v: unknown, r: (typeof LOGS)[number]) => {
        if (r.status === 'done') {
          return (
            <div style={{ display: 'flex', gap: 4, flexWrap: 'wrap', alignItems: 'center' }}>
              {r.id === 1024 ? (
                <Button size="small" onClick={open('report')}>任务报表 68%</Button>
              ) : (
                <Button size="small" theme="solid" type="primary" onClick={open('report')}>任务报表</Button>
              )}
              <Button size="small" onClick={open('report')}>环境报表</Button>
              <Button size="small" onClick={open('video')}>视频回放</Button>
              <Button size="small" onClick={open('image')}>图像查看</Button>
              <Button size="small" onClick={open('snapshot')}>边走边拍</Button>
              <Button size="small" theme="borderless" type="primary" onClick={open('points')}>测点明细</Button>
            </div>
          )
        }
        if (r.status === 'running') {
          return (
            <div style={{ display: 'flex', gap: 6, alignItems: 'center' }}>
              <Tag color="green" size="small">进行中</Tag>
              <Button size="small" onClick={open('snapshot')}>边走边拍</Button>
            </div>
          )
        }
        if (r.status === 'interrupted') {
          return (
            <div style={{ display: 'flex', gap: 4, alignItems: 'center' }}>
              <Tag color="red" size="small">异常中断</Tag>
              <Button size="small" onClick={open('video')}>视频回放</Button>
              <Button size="small" onClick={open('snapshot')}>边走边拍</Button>
            </div>
          )
        }
        return <Tag color="grey" size="small">待执行</Tag>
      },
    },
  ], [])

  // ---------- 测点明细列 ----------

  const pointColumns = useMemo(() => [
    { title: 'ID', dataIndex: 'id', key: 'id', width: 50 },
    { title: '测点', dataIndex: 'point', key: 'point' },
    { title: '检测类型', dataIndex: 'detect', key: 'detect', width: 100, render: (v: string, r: { detectColor: string }) => <Tag color={r.detectColor as any} size="small">{v}</Tag> },
    { title: '识别结果', dataIndex: 'result', key: 'result', width: 100 },
    { title: '数值', dataIndex: 'value', key: 'value', width: 190 },
    {
      title: '状态', dataIndex: 'ok', key: 'ok', width: 80,
      render: (v: boolean) => <Tag color={v ? 'green' : 'red'} size="small">{v ? '正常' : '异常'}</Tag>,
    },
    {
      title: '复核', dataIndex: 'review', key: 'review', width: 90,
      render: (v: string) => {
        if (v === '待复核') return <Tag color="orange" size="small">待复核</Tag>
        if (v === '已确认') return <Tag color="green" size="small">已确认</Tag>
        return <Tag color="grey" size="small">—</Tag>
      },
    },
    {
      title: '操作', key: 'op', width: 150,
      render: () => (
        <div style={{ display: 'flex', gap: 2 }}>
          <Button size="small" theme="borderless" type="primary" onClick={open('image')}>查看图像</Button>
          <Button size="small" theme="borderless" type="primary">审核确认</Button>
        </div>
      ),
    },
  ], [])

  return (
    <div style={{ padding: '4px 2px' }}>
      {/* 页头 */}
      <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between', flexWrap: 'wrap', gap: 10, marginBottom: 12 }}>
        <div style={{ display: 'flex', alignItems: 'baseline', gap: 10 }}>
          <Title heading={5} style={{ margin: 0 }}>巡检日志</Title>
          <Text type="tertiary" size="small">日志查询 · 任务/环境报表 · 图像查看 · 视频回放 · 边走边拍 · 测点明细与复核（下沉自平台「巡检日志（新版）」）</Text>
        </div>
        <div style={{ display: 'flex', gap: 6, flexWrap: 'wrap' }}>
          <Tag>今日执行 3</Tag><Tag color="green">进行中 1</Tag><Tag color="red">今日异常点 4</Tag><Tag color="orange">待复核 2</Tag>
        </div>
      </div>

      {/* 筛选 */}
      <Card style={{ marginBottom: 12 }} bodyStyle={{ paddingTop: 12, paddingBottom: 12 }}>
        <div style={{ display: 'flex', alignItems: 'center', flexWrap: 'wrap', gap: 10 }}>
          <span>机器人</span>
          <Select style={{ width: 200 }} defaultValue="r1" optionList={[
            { value: 'all', label: '全部' },
            { value: 'r1', label: '机器人1（192.168.8.60）' },
            { value: 'r2', label: '机器人2（192.168.8.61）' },
          ]} />
          <span>计划</span>
          <Select style={{ width: 200 }} defaultValue="p1" optionList={[
            { value: 'all', label: '全部' },
            { value: 'p1', label: '全站巡检-日巡' },
            { value: 'p2', label: '例行-主变区巡检' },
            { value: 'p3', label: '特殊-夜间红外' },
          ]} />
          <Button theme="solid" type="primary" size="small" icon={<IconSearch />}>查询</Button>
          <span style={{ flex: 1 }} />
          <Button size="small" icon={<IconRefresh />}>刷新</Button>
        </div>
      </Card>

      {/* 日志列表 */}
      <Card>
        <Table columns={columns as any} dataSource={LOGS} pagination={{ pageSize: 10 }} size="small" />
        <Banner
          type="info"
          closeIcon={null}
          style={{ marginTop: 12 }}
          description={<>数据写入链路示意：CMD103 更新任务状态 → CMD104 逐测点写结果 + 图片视频入对象存储 → 算法复核 + 越限判级生成告警 → CMD105 结束并触发下一轮计划。报表生成进度经 WebSocket 推送；图像 / 视频存储与算法服务归属待确认。</>}
        />
      </Card>

      <Text type="tertiary" size="small" style={{ display: 'block', marginTop: 10 }}>
        本页为下沉静态界面（示例数据），接口与业务逻辑待开发。
      </Text>

      {/* ==================== 弹窗：图像查看 ==================== */}
      <Modal
        title="图像查看 — 机器人1 · 全站巡检-日巡（2026-08-24）"
        visible={dlg === 'image'}
        onCancel={close}
        width={1100}
        footer={<Button onClick={close}>关闭</Button>}
      >
        <div style={{ padding: '2px 2px 6px' }}>
          {/* 信息与筛选 */}
          <div style={{
            border: '1px solid rgba(0,119,250,.35)', background: 'rgba(0,119,250,.03)',
            borderRadius: 6, padding: '10px 14px', marginBottom: 12, fontSize: 13,
            color: 'var(--semi-color-text-2)', display: 'flex', gap: 20, flexWrap: 'wrap', alignItems: 'center',
          }}>
            <span>机器人：<b>机器人1</b></span>
            <span>计划：<b>全站巡检-日巡</b></span>
            <span>巡检时间：<b>07:31 – 09:12</b></span>
            <span>正常与否：<Select size="small" style={{ width: 100 }} defaultValue="all" optionList={[{ value: 'all', label: '全部' }, { value: 'ok', label: '正常' }, { value: 'abn', label: '异常' }]} /></span>
            <span>采集信息：<Select size="small" style={{ width: 100 }} defaultValue="all" optionList={[{ value: 'all', label: '全部' }, { value: 'vis', label: '可见光' }, { value: 'ir', label: '红外' }]} /></span>
            <span>识别状态：<Select size="small" style={{ width: 100 }} defaultValue="all" optionList={[{ value: 'all', label: '全部' }, { value: 'yes', label: '识别' }, { value: 'no', label: '未识别' }]} /></span>
          </div>
          <div style={{ display: 'flex', alignItems: 'center', flexWrap: 'wrap', gap: 10, marginBottom: 12 }}>
            <span>设备名称</span><Input placeholder="请输入" style={{ width: 140 }} />
            <span>点位名称</span><Input defaultValue="油温表 A相" style={{ width: 140 }} />
            <span>识别结果</span><Input placeholder="请输入" style={{ width: 140 }} />
            <Button size="small" theme="solid" type="primary">搜索</Button>
            <span style={{ flex: 1 }} />
            <Text type="tertiary" size="small">提示：键盘 ← → 翻图</Text>
          </div>

          {/* 看图区（占位示意） */}
          <div className="sink-stage">
            <span className="sink-stage-label">{IMAGE_THUMBS[thumbIdx]?.label ?? 'P110-3 红'} · 油温表 A相 · 2026-08-24 07:42:15 · P110-3</span>
            <Button
              theme="borderless" icon={<IconChevronLeft />}
              onClick={() => setThumbIdx((i) => Math.max(0, i - 1))}
              style={{ position: 'absolute', left: 14, top: '50%', transform: 'translateY(-50%)', color: '#cfe4ff', fontSize: 20 }}
            />
            <Button
              theme="borderless" icon={<IconChevronRight />}
              onClick={() => setThumbIdx((i) => Math.min(IMAGE_THUMBS.length - 1, i + 1))}
              style={{ position: 'absolute', right: 14, top: '50%', transform: 'translateY(-50%)', color: '#cfe4ff', fontSize: 20 }}
            />
            <div className="sink-detect-box" style={{ left: '46%', top: '36%', width: 180, height: 120 }}>
              <span className="db-tag">油温 86.3 ℃ · 越限</span>
            </div>
            <div className="sink-detect-box ok" style={{ left: '20%', top: '55%', width: 90, height: 60 }}>
              <span className="db-tag">液位 62%</span>
            </div>
          </div>

          {/* 缩略图胶片带 */}
          <div className="sink-filmstrip">
            <Button size="small" icon={<IconChevronLeft />} />
            <div className="sink-fs-list">
              {IMAGE_THUMBS.map((t, i) => (
                <div
                  key={i}
                  className={`sink-thumb${i === thumbIdx ? ' active' : ''}${t.abnormal ? ' abn' : ''}`}
                  onClick={() => setThumbIdx(i)}
                >
                  {t.label}
                </div>
              ))}
            </div>
            <Button size="small" icon={<IconChevronRight />} />
          </div>
          <Banner
            type="info"
            closeIcon={null}
            style={{ marginTop: 12 }}
            description={<>同一测点的可见光与红外为两条记录；缩略图红色角标为异常；胶片带可点击定位，键盘左右键翻页。</>}
          />
        </div>
      </Modal>

      {/* ==================== 弹窗：视频回放 ==================== */}
      <Modal
        title="全站巡检-日巡 计划 的视频回放"
        visible={dlg === 'video'}
        onCancel={close}
        width={900}
        footer={<Button onClick={close}>关闭</Button>}
      >
        <div style={{ fontSize: 13, color: 'var(--semi-color-text-2)', marginBottom: 10 }}>
          本视频总时长：<b>12 m 36 s</b>
        </div>
        <div className="sink-video">
          <div className="play-circle" />
          <span style={{ fontSize: 13 }}>flv.js 拉流播放 · 行走过程实时录制（30 秒心跳保流）</span>
          <div className="v-timeline" />
        </div>
      </Modal>

      {/* ==================== 弹窗：边走边拍 ==================== */}
      <Modal
        title="边走边拍 — 全站巡检-日巡（行走抓拍图集）"
        visible={dlg === 'snapshot'}
        onCancel={close}
        width={960}
        footer={<Button onClick={close}>关闭</Button>}
      >
        <div style={{ display: 'flex', alignItems: 'center', flexWrap: 'wrap', gap: 10, marginBottom: 12 }}>
          <span>时间范围</span>
          <Input defaultValue="2026-08-24 07:31" disabled style={{ width: 140 }} />
          <span>～</span>
          <Input defaultValue="2026-08-24 09:12" disabled style={{ width: 140 }} />
          <Button size="small" theme="solid" type="primary">筛选</Button>
          <span style={{ flex: 1 }} />
          <Button size="small">导出图集</Button>
        </div>
        <div style={{ display: 'grid', gridTemplateColumns: 'repeat(6, 1fr)', gap: 10 }}>
          {SNAPSHOT_TIMES.map((t, i) => (
            <div key={t} className={`sink-thumb wide${i === 2 ? ' abn' : ''}`}>{t}</div>
          ))}
        </div>
      </Modal>

      {/* ==================== 弹窗：测点明细（含人工复核） ==================== */}
      <Modal
        title="测点明细 — 全站巡检-日巡（ID 1024）"
        visible={dlg === 'points'}
        onCancel={close}
        width={1000}
        footer={<Button onClick={close}>关闭</Button>}
      >
        <div style={{ display: 'flex', alignItems: 'center', flexWrap: 'wrap', gap: 10, marginBottom: 12 }}>
          <span>设备名称</span><Input placeholder="请输入" style={{ width: 140 }} />
          <span>点位名称</span><Input placeholder="请输入" style={{ width: 140 }} />
          <span>结果状态</span>
          <Select style={{ width: 110 }} defaultValue="all" optionList={[
            { value: 'all', label: '全部' }, { value: 'ok', label: '正常' }, { value: 'abn', label: '异常' }, { value: 'review', label: '待复核' },
          ]} />
          <Button size="small" theme="solid" type="primary">查询</Button>
          <span style={{ flex: 1 }} />
          <Button size="small">导出报表</Button>
        </div>
        <Table columns={pointColumns as any} dataSource={POINT_RESULTS} pagination={{ pageSize: 10 }} size="small" />
        <Banner
          type="info"
          closeIcon={null}
          style={{ marginTop: 12 }}
          description={<>范围提示：测点明细 / 人工复核 / 异常点报表属于「测点级日志」能力，随日志一并下沉；「巡检结果 / 巡检分析」独立页面是否纳入范围待确认。</>}
        />
      </Modal>

      {/* ==================== 弹窗：报表下载选项 ==================== */}
      <Modal
        title="下载选项"
        visible={dlg === 'report'}
        onCancel={close}
        width={420}
        footer={(
          <>
            <Button onClick={close}>取消</Button>
            <Button theme="solid" type="primary" onClick={close}>确定</Button>
          </>
        )}
      >
        <div style={{ display: 'flex', flexDirection: 'column', gap: 10, padding: '6px 0' }}>
          <Checkbox defaultChecked>导出图片（报表内嵌巡检截图）</Checkbox>
          <Checkbox>清除缓存重新下载</Checkbox>
        </div>
      </Modal>
    </div>
  )
}
