import React from 'react'
import { Button, Space, Tag } from '@douyinfe/semi-ui'
import ModelessWindow from './ModelessWindow'
import InspectionRunDetail from './InspectionRunDetail'
import type { InspectionRunRow } from '../api/inspectionLog'

/**
 * 巡检日志**详情窗口**（页面内非模态浮层）。
 *
 * ⚠️ 现在的**主入口是独立路由页** `/inspection/log/:id`（清单页点「详情」会
 * `window.open` 开真浏览器标签页，地址栏可分享、可刷新、内容区铺满）。
 * 这个浮层保留下来是因为有场景确实更合适：**一边看详情一边改筛选条件**
 * （非模态不遮罩，点外面还能操作），以及不想多开标签页的时候。
 *
 * 内容整体复用 `InspectionRunDetail`，所以两个宿主下的树、检视器、跟随刷新、
 * 检测图显示行为完全一致 —— 这里只负责外面那层窗口壳与标题/底栏。
 */
interface Props {
  run: InspectionRunRow
  /** 在新标签页打开这条记录（清单页传路由跳转的封装） */
  onOpenExternal?: () => void
  onClose: () => void
}

export default function InspectionRunDetailWindow({ run, onOpenExternal, onClose }: Props) {
  return (
    <ModelessWindow
      title={
        <span style={{ display: 'inline-flex', alignItems: 'center', gap: 8 }}>
          <span>巡检详情</span>
          <Tag size="small" color={run.display_status === 'done' ? 'green'
            : run.display_status === 'failed' ? 'red' : 'blue'}>
            {run.status}
          </Tag>
          <span style={{ fontFamily: 'monospace', fontSize: 12, color: 'var(--semi-color-text-2)' }}>
            {run.inspection_id?.slice(0, 16)}…
          </span>
        </span>
      }
      hint="拖动这里平移 · 右下角可缩放"
      width={1080}
      bodyClass="ird"
      onClose={onClose}
      footer={
        <Space>
          <span style={{ flex: 1 }} />
          <Button size="small" type="tertiary" onClick={onClose}>关闭</Button>
        </Space>
      }
    >
      <InspectionRunDetail
        runId={run.id}
        run={run}
        onOpenExternal={onOpenExternal}
        extraToolbar={<Button size="small" type="tertiary" onClick={onClose}>关闭</Button>}
      />
    </ModelessWindow>
  )
}
