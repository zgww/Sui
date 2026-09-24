import { useCallback, useEffect, useMemo, useState } from 'react'
import {
  Card, Table, Button, Tag, Select, Input, DatePicker, Space, Modal, Image, Toast,
} from '@douyinfe/semi-ui'
import { IconRefresh, IconSearch } from '@douyinfe/semi-icons'
import dayjs from 'dayjs'
import {
  listAlarms, getAlarmMeta, ackAlarm, ackAllAlarms,
  type AlarmRow, type AlarmQuery,
} from '../api/alarm'
import { getEnumOptions } from '../api/enumPrefab'

const PAGE_SIZE = 20

/**
 * 「类型」下拉取哪份枚举。
 *
 * 与「枚举配置」页（`data/prefabs/枚举/告警类型.prefab.json`）的根 EnumNode
 * 的「枚举键」对应。改这里或改那份配置的键，两边要对得上——对不上时下拉框
 * 会静默回落到"库里实际出现过的值"，表现为"加了选项却不显示"。
 */
const ALARM_TYPE_ENUM_KEY = '告警类型'

const LEVEL_COLOR: Record<string, any> = {
  预警: 'blue', 一般告警: 'cyan', 严重告警: 'orange', 危急告警: 'red',
}

export default function Alarms() {
  const [rows, setRows] = useState<AlarmRow[]>([])
  const [total, setTotal] = useState(0)
  const [page, setPage] = useState(1)
  const [loading, setLoading] = useState(false)

  // 筛选
  const [status, setStatus] = useState('')
  const [alarmType, setAlarmType] = useState('')
  const [level, setLevel] = useState('')
  const [inputKw, setInputKw] = useState('')
  const [keyword, setKeyword] = useState('')
  const [dateStr, setDateStr] = useState<[string, string]>(['', ''])
  const [meta, setMeta] = useState<{ types: string[]; levels: string[] }>({
    types: [], levels: [],
  })
  /**
   * 枚举配置给的「类型」选项。**空数组 = 回落**到 `meta.types`（库里实际出现过
   * 的值）——没配过这份枚举时，至少还能按历史值筛，不至于只剩"全部类型"。
   */
  const [enumTypes, setEnumTypes] = useState<{ value: string; label: string }[]>([])
  const [detail, setDetail] = useState<AlarmRow | null>(null)

  /** 枚举配置里的显示名（列表「类型」列/详情 Tag 用）；没有配置时原样显示值 */
  const typeLabel = useMemo(() => {
    const m: Record<string, string> = {}
    enumTypes.forEach((o) => { m[o.value] = o.label })
    return (v: string) => m[v] || v
  }, [enumTypes])

  const filters = useMemo<AlarmQuery>(() => {
    const f: AlarmQuery = { page, page_size: PAGE_SIZE }
    if (status) f.status = status
    if (alarmType) f.alarm_type = alarmType
    if (level) f.level = level
    if (keyword) f.keyword = keyword
    if (dateStr[0]) f.start = dateStr[0]
    if (dateStr[1]) f.end = dateStr[1]
    return f
  }, [page, status, alarmType, level, keyword, dateStr])

  const load = useCallback(async () => {
    setLoading(true)
    try {
      const { data } = await listAlarms(filters)
      setRows(data.items)
      setTotal(data.total)
    } finally {
      setLoading(false)
    }
  }, [filters])

  useEffect(() => { load() }, [load])

  useEffect(() => {
    getAlarmMeta().then(({ data }) => setMeta(data)).catch(() => {})
  }, [])

  useEffect(() => {
    getEnumOptions(ALARM_TYPE_ENUM_KEY)
      // 取不到就保持空数组 -> 自动回落到 meta.types；下拉框是筛选区的装饰性
      // 控件，枚举目录没配/坏了不该让整个页面报错
      .then(({ data }) => setEnumTypes(data?.options || []))
      .catch(() => {})
  }, [])

  const doSearch = () => { setKeyword(inputKw.trim()); setPage(1) }

  const onAck = async (r: AlarmRow) => {
    await ackAlarm(r.id)
    Toast.success('已确认')
    load()
  }

  /** 确认所有当前筛选（状态固定为未确认）的告警。 */
  const onAckAll = async () => {
    const f: Partial<AlarmQuery> = {}
    if (alarmType) f.alarm_type = alarmType
    if (level) f.level = level
    if (keyword) f.keyword = keyword
    if (dateStr[0]) f.start = dateStr[0]
    if (dateStr[1]) f.end = dateStr[1]
    const { data } = await ackAllAlarms(f)
    Toast.success(`已确认 ${data.acknowledged} 条告警`)
    load()
  }

  const columns = [
    {
      title: '级别', dataIndex: 'level', width: 92,
      render: (l: string) => <Tag color={LEVEL_COLOR[l] || 'blue'} size="small">{l}</Tag>,
    },
    {
      title: '标题', dataIndex: 'title',
      render: (t: string, r: AlarmRow) => (
        <Button theme="borderless" size="small" style={{ padding: 0 }}
          onClick={() => setDetail(r)}>
          {t || r.alarm_type}
        </Button>
      ),
    },
    {
      title: '类型', dataIndex: 'alarm_type', width: 130,
      render: (v: string) => typeLabel(v || '-'),
    },
    {
      title: '测点', dataIndex: 'point_name', width: 150,
      render: (v: string, r: AlarmRow) => v || r.point_id || '-',
    },
    {
      title: '触发时间', dataIndex: 'triggered_at', width: 165,
      render: (t: string) => (t ? dayjs(t).format('YYYY-MM-DD HH:mm:ss') : '-'),
    },
    {
      title: '状态', dataIndex: 'status', width: 90,
      render: (s: string) => (
        <Tag size="small" color={s === 'ack' ? 'green' : 'red'}>
          {s === 'ack' ? '已确认' : '未确认'}
        </Tag>
      ),
    },
    {
      title: '操作', width: 90,
      render: (_: any, r: AlarmRow) => (r.status === 'unack'
        ? <Button size="small" onClick={() => onAck(r)}>确认</Button>
        : <span style={{ color: 'var(--semi-color-text-2)' }}>-</span>),
    },
  ]

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>告警中心</h2>
        <Space>
          <Button onClick={onAckAll}>确认所有筛选的告警</Button>
          <Button icon={<IconRefresh />} loading={loading} onClick={load}>刷新</Button>
        </Space>
      </div>

      <Card className="card-shadow" bordered={false} style={{ marginBottom: 12 }}>
        <Space wrap>
          <Select
            style={{ width: 120 }} value={status}
            onChange={(v) => { setStatus(v as string); setPage(1) }}
            optionList={[
              { value: '', label: '全部状态' },
              { value: 'unack', label: '未确认' },
              { value: 'ack', label: '已确认' },
            ]}
          />
          <Select
            style={{ width: 160 }} value={alarmType}
            placeholder="全部类型"
            onChange={(v) => { setAlarmType(v as string); setPage(1) }}
            optionList={[
              { value: '', label: '全部类型' },
              // 枚举配置优先（`label` 是显示名，提交的是 `value`）；没配过时
              // 回落到库里实际出现过的值，见 enumTypes 的注释
              ...(enumTypes.length
                ? enumTypes
                : meta.types.map((t) => ({ value: t, label: t }))),
            ]}
          />
          <Select
            style={{ width: 130 }} value={level}
            onChange={(v) => { setLevel(v as string); setPage(1) }}
            optionList={[
              { value: '', label: '全部级别' },
              ...meta.levels.map((l) => ({ value: l, label: l })),
            ]}
          />
          <Input
            style={{ width: 210 }} value={inputKw} onChange={setInputKw}
            onEnterPress={doSearch} placeholder="搜索标题 / 正文 / 测点"
            prefix={<IconSearch />}
          />
          <Button onClick={doSearch}>搜索</Button>
          <DatePicker
            type="dateRange" style={{ width: 270 }}
            value={dateStr[0]
              ? [dayjs(dateStr[0]).toDate(), dayjs(dateStr[1]).toDate()]
              : undefined}
            onChange={(_d, ds) => {
              const arr = (ds as string[]) || ['', '']
              setDateStr([arr[0] || '', arr[1] || ''])
              setPage(1)
            }}
          />
        </Space>
      </Card>

      <Card className="card-shadow" bordered={false}>
        <Table
          columns={columns as any} dataSource={rows} rowKey="id"
          size="small" loading={loading} empty="暂无告警"
          pagination={{
            currentPage: page, pageSize: PAGE_SIZE, total,
            onPageChange: setPage, showSizeChanger: false,
          }}
        />
      </Card>

      <Modal
        visible={!!detail} onCancel={() => setDetail(null)} footer={null}
        title={detail?.title} width={660}
      >
        {detail && (
          <div>
            {detail.picture
              ? <Image src={detail.picture} style={{ maxWidth: '100%' }} />
              : null}
            <div style={{ marginTop: 12 }}>
              <Space wrap>
                <Tag color={LEVEL_COLOR[detail.level] || 'blue'}>{detail.level}</Tag>
                <Tag>{typeLabel(detail.alarm_type)}</Tag>
                <Tag color={detail.status === 'ack' ? 'green' : 'red'}>
                  {detail.status === 'ack' ? '已确认' : '未确认'}
                </Tag>
              </Space>
            </div>
            {detail.content
              ? <p style={{ marginTop: 12, whiteSpace: 'pre-wrap' }}>{detail.content}</p>
              : null}
            <div style={{ color: 'var(--semi-color-text-2)', fontSize: 12, marginTop: 8 }}>
              测点：{detail.point_name || detail.point_id || '-'}　触发：{detail.triggered_at}
            </div>
          </div>
        )}
      </Modal>
    </div>
  )
}
