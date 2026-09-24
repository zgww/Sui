import React, { useCallback, useEffect, useState } from 'react'
import { useNavigate, useParams } from 'react-router-dom'
import { Button, Card, Empty, Space, Spin, Tag, Toast, Tooltip } from '@douyinfe/semi-ui'
import { IconArrowLeft, IconRefresh, IconExternalOpen, IconDownload, IconExcel, IconStop } from '@douyinfe/semi-icons'
import InspectionRunDetail from '../../components/InspectionRunDetail'
import { inspectionLogApi, displayStatusColor, displayStatusText, type InspectionRunRow } from '../../api/inspectionLog'

/**
 * 巡检日志**详情页**（独立路由 `/inspection/log/:id`）。
 *
 * ## 为什么要有这一页
 *
 * 清单页原本是弹一个 `ModelessWindow`（`createPortal` 到 body 的页面内浮层）：
 * 它确实能动、能缩，但**本质上还在同一个标签页里**，右上角只有一个 ×，没有地址栏 ——
 * 想把"这条巡检的详情"发给同事，只能截图。而且浮层始终要跟下面的表格抢地方，
 * 检测框那种需要大图纵览的页面尤其憋屈。
 *
 * 改成**真·浏览器新窗口**（`window.open('...')` 开独立标签页）之后：
 * 地址栏里有 `/inspection/log/12` 可以直接分享、刷新、加书签；内容区铺满整个
 * 视口（左侧不再被侧栏压着看，图片能一路撑到底）；还能同时开好几条记录横向对比。
 *
 * ⚠️ 之所以不是"`window.open` 一个空白页再塞 DOM"：那就绕开了路由与鉴权，
 * 刷新页面会白屏。用**独立路由**承载，`RequireAuth` 与侧栏都还在，行为一致。
 *
 * ## 数据
 *
 * 页面只拿得到 URL 里的 id，所以 `robot_name` / `status` 由
 * `/runs/{id}/summary` 单独补（见 `InspectionRunDetail`）；树与检视器复用
 * `InspectionRunDetail`，与浮层里是**同一份实现**，不会两处漂移。
 */
type TagColorLike = React.ComponentProps<typeof Tag>['color']

export default function InspectionLogDetail() {
  const { id } = useParams<{ id: string }>()
  const navigate = useNavigate()
  const runId = Number(id)
  const [run, setRun] = useState<InspectionRunRow | null>(null)
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState('')

  const badId = !id || !Number.isFinite(runId)

  const load = useCallback(async () => {
    if (badId) return
    setLoading(true)
    setError('')
    try {
      setRun(await inspectionLogApi.summary(runId))
    } catch (e: any) {
      setError(e?.message || '加载失败')
    } finally {
      setLoading(false)
    }
  }, [runId, badId])

  useEffect(() => { load() }, [load])

  /** 浏览器标签页标题跟着记录走，开好几个标签时能一眼分清 */
  useEffect(() => {
    const base = '巡检详情'
    document.title = run?.inspection_id
      ? `${base} · ${run.inspection_id.slice(0, 12)}`
      : base
    return () => { document.title = 'Straitbot FMS' }
  }, [run])

  if (badId) {
    return (
      <div className="page-container">
        <Empty title="链接里的巡检记录 ID 不对" description={`拿到的 id 是「${id ?? ''}」`} />
      </div>
    )
  }

  return (
    <div className="page-container ild-page">
      <div className="flex-between mb-12">
        <Space>
          <Button icon={<IconArrowLeft />} onClick={() => navigate('/inspection/log')}>
            返回列表
          </Button>
          <h2 style={{ margin: 0 }}>巡检详情</h2>
          {run ? (
            <>
              <Tag color={displayStatusColor(run.display_status) as TagColorLike}>
                {displayStatusText(run.display_status)}
              </Tag>
              <Tooltip content={run.inspection_id}>
                <span style={{ fontFamily: 'monospace', fontSize: 12, color: 'var(--semi-color-text-2)' }}>
                  {run.inspection_id?.slice(0, 20)}…
                </span>
              </Tooltip>
            </>
          ) : null}
        </Space>
        <Space>
          <Tooltip content="重新拉取这条巡检的动作账本">
            <Button icon={<IconRefresh />} loading={loading} onClick={load}>刷新</Button>
          </Tooltip>
          <Tooltip content="把这个地址发给别人，或在另一个标签页里对比着看">
            <Button
              icon={<IconExternalOpen />}
              onClick={() => window.open(window.location.href, '_blank', 'noopener')}
            >
              新标签页打开
            </Button>
          </Tooltip>
          <Tooltip content="按模板格式生成 Excel 巡检报告（异步生成，完成后可下载）">
            <Button
              icon={<IconExcel />}
              type="primary"
              onClick={async () => {
                try {
                  await inspectionLogApi.generateReport(runId, true)  // 每次都重新生成
                  Toast.success('报表生成任务已提交，请稍后刷新查看状态')
                } catch (e: any) {
                  Toast.error(e?.message || '生成报表失败')
                }
              }}
            >
              生成报表
            </Button>
          </Tooltip>
          <Tooltip content="下载已生成的 Excel 报表">
            <Button
              icon={<IconDownload />}
              onClick={async () => {
                try {
                  const res = await fetch(`/api/inspection/runs/${runId}/report/download`, {
                    headers: { Authorization: 'Bearer ' + (localStorage.getItem('fms_token') || '') },
                  })
                  if (!res.ok) throw new Error(`下载失败 (${res.status})`)
                  const blob = await res.blob()
                  const url = URL.createObjectURL(blob)
                  const a = document.createElement('a')
                  a.href = url
                  a.download = `巡检报表_${runId}.xlsx`
                  a.click()
                  URL.revokeObjectURL(url)
                  Toast.success('报表下载已开始')
                } catch (e: any) {
                  Toast.error(e?.message || '下载报表失败')
                }
              }}
            >
              下载报表
            </Button>
          </Tooltip>
          {run && (run.status === 'started' || run.status === 'running') && (
            <Tooltip content="取消这次巡检">
              <Button
                icon={<IconStop />}
                type="danger"
                onClick={async () => {
                  try {
                    await inspectionLogApi.cancelRun(runId)
                    Toast.success('巡检已取消')
                    load()
                  } catch (e: any) {
                    Toast.error(e?.message || '取消失败')
                  }
                }}
              >
                取消巡检
              </Button>
            </Tooltip>
          )}
        </Space>
      </div>

      {error ? (
        <Card className="card-shadow" bordered={false}>
          <Empty
            title="没能加载这条巡检记录"
            description={error}
          />
        </Card>
      ) : loading && !run ? (
        <div className="ird-center"><Spin size="large" /></div>
      ) : (
        // 详情主体铺满剩余高度：卡片自己撑开，内部左右两栏各自滚动
        <Card className="card-shadow ild-card" bordered={false} bodyStyle={{ padding: 0 }}>
          <InspectionRunDetail
            runId={runId}
            run={run}
            onOpenExternal={() => window.open(window.location.href, '_blank', 'noopener')}
          />
        </Card>
      )}
    </div>
  )
}
