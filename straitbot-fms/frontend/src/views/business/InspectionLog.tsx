import React, { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import {
  Button, Card, Table, Empty, Tag, Tooltip, DatePicker, Select, Input, Banner, Space, Toast,
} from '@douyinfe/semi-ui'
import { IconRefresh, IconSearch, IconEyeOpened, IconExternalOpen, IconExcel, IconDownload, IconStop } from '@douyinfe/semi-icons'
import { useNavigate } from 'react-router-dom'
import { listRobots } from '../../api/robots'
import {
  inspectionLogApi, displayStatusColor, displayStatusText,
  progressText, type InspectionRunRow,
} from '../../api/inspectionLog'
import InspectionRunDetailWindow from '../../components/InspectionRunDetailWindow'

/**
 * 巡检日志：列出数据库里**全部** InspectionRun（不限机器人、不分页面入口）。
 *
 * ## 详情为什么开浏览器新标签页
 *
 * 一次巡检动辄上百个动作、几十个检测框，清单页塞不下（行内展开会把表格撑到几千
 * 像素，翻页与筛选全被顶走）。详情走**独立路由** `/inspection/log/:id` 用
 * `window.open` 开真浏览器标签页，好处是页面内的浮层给不了的：
 *
 * - 地址栏里有 URL → **可以直接分享、刷新、加书签**（浮层做不到，只能截图）；
 * - 内容区铺满整个视口 → 检测图那种要纵览的东西才看得全；
 * - 能同时开好几条记录横向对比。
 *
 * ⚠️ 不是 `window.open` 一个空白页再往里塞 DOM —— 那样绕开了路由与鉴权，一刷新
 * 就白屏。开的是**路由页**，`RequireAuth` 和侧栏都照常。
 *
 * 详情页与页面内浮层（`InspectionRunDetailWindow`，保留给"边看详情边改筛选"）
 * 共用 `components/InspectionRunDetail.tsx`，两处实现不会漂移。
 */
type TagColorLike = React.ComponentProps<typeof Tag>['color']

const fmtTime = (v: string | null | undefined) => (v ? new Date(v).toLocaleString() : '—')

export default function InspectionLog() {
  const navigate = useNavigate()
  // —— 机器人下拉（全库列表，不依赖顶部选中）——
  const [robots, setRobots] = useState<{ id: number; name: string }[]>([])
  // —— 筛选（robotPk 为 undefined 即"全部机器人"）——
  const [robotPk, setRobotPk] = useState<number | undefined>(undefined)
  const [status, setStatus] = useState('')
  const [keyword, setKeyword] = useState('')
  const [keywordDraft, setKeywordDraft] = useState('')
  const [range, setRange] = useState<[Date, Date] | null>(null)
  // —— 列表 ——
  const [rows, setRows] = useState<InspectionRunRow[]>([])
  const [total, setTotal] = useState(0)
  const [page, setPage] = useState(1)
  const [pageSize, setPageSize] = useState(20)
  const [loading, setLoading] = useState(false)
  // —— 页面内浮层：只有"浮层查看"这一个入口才会用到（主入口是新标签页）——
  const [detailRun, setDetailRun] = useState<InspectionRunRow | null>(null)
  // —— 报表生成轮询 ——
  const [reportLoading, setReportLoading] = useState<number | null>(null)  // 正在生成报表的 run_id
  const pollTimer = useRef<ReturnType<typeof setInterval> | null>(null)

  /**
   * 开新标签页看详情。
   *
   * ⚠️ `window.open` 会被浏览器的弹窗拦截器盯上：**必须由用户的点击事件
   * 同步调起**。所以这个函数只能在 onClick 里直接调，不能 `await` 之后
   * 再调（那时已经脱离用户手势，会被拦）。
   */
  const openDetail = useCallback((r: InspectionRunRow) => {
    window.open(`/inspection/log/${r.id}`, '_blank', 'noopener')
  }, [])

  useEffect(() => {
    listRobots().then(r => {
      setRobots((r.data || []).map((x: any) => ({ id: x.id, name: x.name })))
    }).catch(() => { /* 拉不到机器人不影响看日志 */ })
  }, [])

  // ⚠️ `load` 的 deps 里**故意不放** page / pageSize：
  // 两者一律由调用方显式传进来（翻页传目标页、改页长传 1），放进来只会让
  // 这个 callback 每次翻页都换一次身份，进而把下面的筛选 effect 也带着多跑一遍。
  const load = useCallback(async (nextPage: number, nextSize: number) => {
    setLoading(true)
    try {
      const data = await inspectionLogApi.list({
        robot_pk: robotPk ?? null,
        status,
        keyword,
        start: range?.[0] ? fmtDate(range[0]) : '',
        end: range?.[1] ? fmtDate(range[1]) : '',
        page: nextPage,
        page_size: nextSize,
      })
      setRows(data.items || [])
      setTotal(data.total || 0)
      setPage(data.page || nextPage)
      setPageSize(nextSize)
    } catch { /* http 拦截器已弹错误 */ }
    finally { setLoading(false) }
  }, [robotPk, status, keyword, range])

  /** 触发生成报表（异步），并开始轮询状态。 */
  const handleGenerateReport = useCallback(async (r: InspectionRunRow) => {
    if (reportLoading) return  // 正在生成中
    setReportLoading(r.id)
    try {
      const res = await inspectionLogApi.generateReport(r.id, true)  // 每次都重新生成
      if (res.status === 'done') {
        Toast.success('报表已生成，可直接下载')
        setReportLoading(null)
        load(page, pageSize)
        return
      }
      // 开始轮询状态
      let polls = 0
      pollTimer.current = setInterval(async () => {
        polls++
        try {
          const st = await inspectionLogApi.reportStatus(r.id)
          if (st.status === 'done') {
            clearInterval(pollTimer.current!)
            pollTimer.current = null
            setReportLoading(null)
            Toast.success('报表生成完成')
            load(page, pageSize)
          } else if (st.status === 'failed') {
            clearInterval(pollTimer.current!)
            pollTimer.current = null
            setReportLoading(null)
            Toast.error(`报表生成失败：${st.error || '未知错误'}`)
            load(page, pageSize)
          }
        } catch { /* 网络错误，继续轮询 */ }
        if (polls > 60) {  // 最多轮询 60 次（约 2 分钟）
          clearInterval(pollTimer.current!)
          pollTimer.current = null
          setReportLoading(null)
          Toast.warning('报表生成超时，请稍后刷新查看')
        }
      }, 2000)
    } catch (e: any) {
      setReportLoading(null)
      Toast.error(e?.message || '生成报表失败')
    }
  }, [reportLoading, load, page, pageSize])

  /** 下载报表（用 fetch 带 Authorization header，再转 blob 下载）。 */
  const handleDownloadReport = useCallback(async (r: InspectionRunRow) => {
    try {
      const res = await fetch(`/api/inspection/runs/${r.id}/report/download`, {
        headers: { Authorization: 'Bearer ' + (localStorage.getItem('fms_token') || '') },
      })
      if (!res.ok) throw new Error(`下载失败 (${res.status})`)
      const blob = await res.blob()
      const url = URL.createObjectURL(blob)
      const a = document.createElement('a')
      a.href = url
      a.download = `巡检报表_${r.inspection_id?.slice(0, 12) || r.id}.xlsx`
      a.click()
      URL.revokeObjectURL(url)
      Toast.success('报表下载已开始')
    } catch (e: any) {
      Toast.error(e?.message || '下载报表失败')
    }
  }, [])

  // 筛选条件变了就回到第 1 页 —— 留在第 5 页很可能直接翻到空列表
  useEffect(() => { load(1, pageSize) /* eslint-disable-next-line react-hooks/exhaustive-deps */ },
    [robotPk, status, keyword, range])

  const columns = useMemo(() => [
    { title: 'ID', dataIndex: 'id', width: 62 },
    {
      title: '巡检ID', dataIndex: 'inspection_id', width: 148,
      render: (v: string) => (
        <Tooltip content={v}>
          <span style={{ fontFamily: 'monospace', fontSize: 12 }}>{v ? `${v.slice(0, 14)}…` : '—'}</span>
        </Tooltip>
      ),
    },
    {
      title: '机器人', dataIndex: 'robot_name', width: 118,
      render: (v: string | null, r: InspectionRunRow) =>
        v || (r.robot_pk != null ? `#${r.robot_pk}` : <Tooltip content="该记录未关联机器人（机器人未在平台登记）"><span style={{ color: '#999' }}>未关联</span></Tooltip>),
    },
    {
      title: '状态', dataIndex: 'display_status', width: 92,
      render: (v: string, r: InspectionRunRow) => (
        <Tooltip content={v !== r.status ? `库内状态：${r.status}（该次巡检开跑后一直没有动作回填）` : undefined}>
          <Tag color={displayStatusColor(v) as TagColorLike}>{displayStatusText(v)}</Tag>
        </Tooltip>
      ),
    },
    {
      title: '进度', width: 178,
      render: (_: unknown, r: InspectionRunRow) => {
        const pct = r.progress_pct ?? 0
        const color = r.display_status === 'done' ? '#52c41a'
          : r.display_status === 'failed' ? '#ff4d4f' : '#1890ff'
        return (
          <div style={{ display: 'flex', alignItems: 'center', gap: 6 }}>
            <div style={{ flex: 1, height: 14, background: '#eee', borderRadius: 7, overflow: 'hidden' }}>
              <div style={{ height: '100%', width: `${pct}%`, background: color, borderRadius: 7 }} />
            </div>
            <span style={{ fontSize: 11, color: '#666', whiteSpace: 'nowrap' }}>
              {progressText(r.done_actions, r.total_actions, r.progress_pct)}
            </span>
          </div>
        )
      },
    },
    {
      title: '异常', dataIndex: 'failed_actions', width: 66,
      render: (v: number) => (v > 0 ? <Tag color="red" size="small">{v}</Tag> : <Tag color="grey" size="small">0</Tag>),
    },
    {
      title: '检测框', width: 86,
      render: (_: unknown, r: InspectionRunRow) => (
        r.point_count
          ? <span style={{ fontSize: 12 }}>{r.point_count}</span>
          : <span style={{ color: '#bbb' }}>—</span>
      ),
    },
    { title: '开始时间', dataIndex: 'start_time', width: 152, render: fmtTime },
    { title: '结束时间', dataIndex: 'finish_time', width: 152, render: fmtTime },
    {
      title: '备注', dataIndex: 'remark', width: 120, ellipsis: true,
      render: (v: string) => v || <span style={{ color: '#bbb' }}>—</span>,
    },
    {
      title: '报表', width: 90,
      render: (_: unknown, r: InspectionRunRow) => {
        const st = r.report_status || ''
        if (!st) return <span style={{ color: '#bbb' }}>—</span>
        if (st === 'pending' || st === 'running') return <Tag color="blue" size="small">生成中…</Tag>
        if (st === 'done') return <Tag color="green" size="small">已生成</Tag>
        if (st === 'failed') return (
          <Tooltip content={r.report_error || '生成失败'}>
            <Tag color="red" size="small">失败</Tag>
          </Tooltip>
        )
        return <span>{st}</span>
      },
    },
    {
      title: '操作', width: 200, fixed: 'right' as const,
      render: (_: unknown, r: InspectionRunRow) => (
        <Space>
          <Tooltip content="在新的浏览器标签页打开（地址可分享、可刷新）">
            <Button
              size="small" theme="light" type="primary" icon={<IconExternalOpen />}
              onClick={() => openDetail(r)}
            >
              详情
            </Button>
          </Tooltip>
          <Tooltip content="按模板格式生成 Excel 巡检报告">
            <Button
              size="small" theme="light" type="secondary" icon={<IconExcel />}
              loading={reportLoading === r.id}
              disabled={!!reportLoading && reportLoading !== r.id}
              onClick={() => handleGenerateReport(r)}
            >
              生成报表
            </Button>
          </Tooltip>
          {r.report_status === 'done' && (
            <Tooltip content="下载已生成的 Excel 报表">
              <Button
                size="small" theme="borderless" type="tertiary" icon={<IconDownload />}
                onClick={() => handleDownloadReport(r)}
                aria-label="下载报表"
              />
            </Tooltip>
          )}
          <Tooltip content="在当前页浮层里看，不遮罩，可以边看边改筛选条件">
            <Button
              size="small" theme="borderless" type="tertiary" icon={<IconEyeOpened />}
              onClick={() => setDetailRun(r)}
              aria-label="浮层查看"
            />
          </Tooltip>
          {(r.status === 'started' || r.status === 'running') && (
            <Tooltip content="取消这次巡检">
              <Button
                size="small" theme="light" type="danger" icon={<IconStop />}
                onClick={async () => {
                  try {
                    await inspectionLogApi.cancelRun(r.id)
                    Toast.success('巡检已取消')
                    load(page, pageSize)
                  } catch (e: any) {
                    Toast.error(e?.message || '取消失败')
                  }
                }}
              >
                取消
              </Button>
            </Tooltip>
          )}
        </Space>
      ),
    },
  ], [openDetail])

  return (
    <div className="page-container">
      <div className="flex-between mb-12">
        <h2 style={{ margin: 0 }}>巡检日志</h2>
        <Button icon={<IconRefresh />} loading={loading} onClick={() => load(page, pageSize)}>刷新</Button>
      </div>

      <Banner
        type="info"
        closeIcon={null}
        style={{ marginBottom: 12 }}
        description="列出数据库中全部巡检执行记录（不限机器人）。点「详情」在浏览器新标签页打开：左侧按 楼层 → 航点 → 动作点 → 检测框 组织，右侧检视器显示选中项的全部字段。新标签页里地址可分享、可刷新，还能开好几条记录对比着看。"
      />

      <Card className="card-shadow" bordered={false} style={{ marginBottom: 12 }}
        bodyStyle={{ paddingTop: 12, paddingBottom: 12 }}>
        <div style={{ display: 'flex', alignItems: 'center', flexWrap: 'wrap', gap: 10 }}>
          <span>机器人</span>
          <Select
            style={{ width: 180 }} value={robotPk ?? 'all'}
            onChange={v => setRobotPk(v === 'all' ? undefined : Number(v))}
            optionList={[{ value: 'all', label: '全部' },
              ...robots.map(r => ({ value: r.id, label: r.name }))]}
          />
          <span>状态</span>
          <Select
            style={{ width: 130 }} value={status || 'all'}
            onChange={v => setStatus(v === 'all' ? '' : String(v))}
            optionList={[
              { value: 'all', label: '全部' },
              { value: 'started', label: '进行中' },
              { value: 'done', label: '已完成' },
              { value: 'failed', label: '失败' },
              { value: 'canceled', label: '已取消' },
            ]}
          />
          <span>时间范围</span>
          <DatePicker
            type="dateTimeRange" style={{ width: 340 }}
            value={range as any} onChange={v => setRange((v as any) || null)}
          />
          <span>关键字</span>
          <Input
            style={{ width: 180 }} value={keywordDraft} placeholder="巡检ID / 备注"
            onChange={setKeywordDraft}
            onEnterPress={() => setKeyword(keywordDraft.trim())}
          />
          <Button theme="solid" type="primary" icon={<IconSearch />}
            onClick={() => setKeyword(keywordDraft.trim())}>查询</Button>
          <span style={{ flex: 1 }} />
          <span style={{ fontSize: 12, color: '#999' }}>共 {total} 条</span>
        </div>
      </Card>

      <Card className="card-shadow" bordered={false} bodyStyle={{ padding: 0 }}>
        <Table
          columns={columns as any}
          dataSource={rows}
          rowKey="id"
          loading={loading}
          size="small"
          scroll={{ x: 1420 }}
          pagination={{
            currentPage: page,
            pageSize,
            total,
            showSizeChanger: true,
            pageSizeOpts: [10, 20, 50, 100],
            onPageChange: (p: number) => load(p, pageSize),
            onPageSizeChange: (s: number) => load(1, s),
          }}
          empty={<Empty description="暂无巡检记录" />}
        />
      </Card>

      {/* 浮层详情：非模态，不遮罩，开着的时候还能改上面的筛选（主入口是新标签页） */}
      {detailRun && (
        <InspectionRunDetailWindow
          key={detailRun.id}
          run={detailRun}
          onOpenExternal={() => openDetail(detailRun)}
          onClose={() => setDetailRun(null)}
        />
      )}
    </div>
  )
}

/** 本地时间 -> `YYYY-MM-DD HH:mm`（后端认这种格式，带 T 也认，但不给自己找麻烦）。 */
function fmtDate(d: Date): string {
  const p = (n: number) => String(n).padStart(2, '0')
  return `${d.getFullYear()}-${p(d.getMonth() + 1)}-${p(d.getDate())} ${p(d.getHours())}:${p(d.getMinutes())}`
}
