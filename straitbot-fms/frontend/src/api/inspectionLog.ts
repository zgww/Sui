import http from './http'

/**
 * 巡检日志 API（`/api/inspection/runs*`）。
 *
 * 与 `api/control.ts` 里那几个旧函数是同一批接口 —— 那边只有"按机器人 + 裸数组"
 * 的形态（老页面在用，不动它），这里要的是**全库 + 分页 + 筛选**，所以单独放一个
 * 文件，把请求/响应类型也写清楚，页面里就不用到处 `any`。
 */

/** 巡检执行记录（列表行）。 */
export interface InspectionRunRow {
  id: number
  inspection_id: string
  task_id: number | null
  robot_pk: number | null
  robot_name: string | null
  /** 库里的原始状态：started / done / failed / canceled */
  status: string
  /** 展示口径：库状态 + 卡死兜底（stalled） */
  display_status: string
  total_actions: number
  done_actions: number
  failed_actions: number
  pending_actions: number
  /** total=0 时为 null（前端渲染成 "—"，别显示 0%） */
  progress_pct: number | null
  point_count: number
  detect_count: number
  thermometry_count: number
  /** 计数来源：action_results / inspection_results / progress_cache */
  counts_source: string
  start_time: string | null
  finish_time: string | null
  created_at: string | null
  remark: string
  progress: Record<string, any>
  /** 报表生成状态："" / pending / running / done / failed */
  report_status?: string
  report_path?: string
  report_error?: string
  report_generated_at?: string | null
}

/** 报表生成状态响应。 */
export interface ReportStatus {
  status: string
  path: string
  error: string
  generated_at: string | null
}

/** 动作结果（新表 inspection_action_results）。 */
export interface ActionResultRow {
  id: number
  run_id: number
  robot_pk: number | null
  inspection_id: string
  floor: number
  waypoint_id: string
  waypoint_index: number
  /** 航点/设备名（巡检当次的快照，如「G10联络柜」）；老记录可能为空 */
  waypoint_name: string
  action_id: string
  action_seq: number
  action_type: number
  action_type_name: string
  attempt: number
  executor: string
  /** fms 本地消化 / platform 上传平台 */
  detect_type: string
  /** 动作执行结果：pending / ok / failed / skipped */
  status: string
  code: number
  picture: string
  infrared: string
  media: string
  local_path: string
  thermometry: any
  env: any
  pdd: any
  inplace_ts: string
  start_time: string | null
  finish_time: string | null
  duration_ms: number
  /** 数据分发状态：pending / done / failed —— 与 status 是两件事 */
  dispatch_status: string
  dispatch_mode: string
  dispatch_attempts: number
  dispatched_at: string | null
  dispatch_error: string
  /** 动作点配置的抓拍参考图（web 相对路径） */
  reference_image: string
  /** 推理留痕：请求参数 / 同步响应(含 http_status) / 算法回调结果 */
  infer_request: any
  infer_response: any
  infer_result: any
}

/**
 * 测点档案的**精简视图**（后端按 `point_id` 查好带出来的那一小份）。
 *
 * 不是整条档案记录 —— 巡检详情只需要"这个测点是谁"，不需要档案的全部配置。
 * 查不到（没绑测点 / 档案里没有该 id / 档案文件坏了）时后端给 `null`。
 */
export interface PointArchiveLite {
  id: string
  name: string
  /** 测点编号（现场用的那个号，如 `1_0_0_1_53_0`） */
  code: string
  active: boolean
  /** 直属设备目录名 */
  parent_name: string
  /** 从外到内的层级名，如 `['1号站', '10kV', '1号间隔', 'G1柜']` */
  path: string[]
}

/** 测点结果（测温点 / 检测点共用）。 */
export interface PointResultRow {
  id: number
  action_result_id: number | null
  run_id: number
  robot_pk: number | null
  floor: number
  waypoint_id: string
  action_id: string
  point_id: string
  /** 检测框自己的唯一 id（`DetectBoxNode.box_id`）。⚠️ 与 `point_id` 是两件事：
   *  测点可以不绑（本站场景常常没有），检测框 ID 一定有 —— 算法回调靠它认回本框 */
  box_id: string
  /** 框名（框节点名 → 测点名 → 检测框N） */
  box_name: string
  seq: number
  /** thermometry 测温点 / detect 检测点 */
  kind: string
  status: string
  value: number | null
  unit: string
  image: string
  detect_flow: string
  /** 检测流程的中文名（后端解析；流程目录读不到时为空） */
  detect_flow_name?: string
  algorithm: string
  label: string
  confidence: number | null
  passed: boolean | null
  boxes: any[]
  detect: any
  /** 算法**原始识别结果**（回调结果框原样留痕：display / parameter / code / extra…） */
  raw?: any
  /** 测点档案（按 `point_id` 查；没绑 / 查不到为 null） */
  point?: PointArchiveLite | null
  action_type?: number
  action_type_name?: string
  picture?: string
}

/** 分页响应（对齐 inspection_plans 的 `{total, items}` 惯例）。 */
export interface Page<T> {
  total: number
  page: number
  page_size: number
  items: T[]
}

export interface RunQuery {
  robot_pk?: number | null
  status?: string
  keyword?: string
  start?: string
  end?: string
  page?: number
  page_size?: number
}

const base = '/api/inspection/runs'

export const inspectionLogApi = {
  /** 全库巡检记录（分页）。`robot_pk` 不传 = 全部机器人。 */
  list: (q: RunQuery) =>
    http.get<Page<InspectionRunRow>>(base, {
      params: {
        page: q.page ?? 1,
        page_size: q.page_size ?? 20,
        robot_pk: q.robot_pk ?? undefined,
        status: q.status || undefined,
        keyword: q.keyword || undefined,
        start: q.start || undefined,
        end: q.end || undefined,
      },
    }).then(r => r.data),

  /** 动作结果明细（FMS 账本，含分发状态）。 */
  actions: (runId: number) =>
    http.get<{ run_id: number; inspection_id: string; summary: any; items: ActionResultRow[] }>(
      `${base}/${runId}/actions`,
    ).then(r => r.data),

  /** 测点结果（测温点 / 检测点）。`kind` 留空取全部。 */
  points: (runId: number, kind?: string) =>
    http.get<{ run_id: number; inspection_id: string; summary: any; items: PointResultRow[] }>(
      `${base}/${runId}/points`, { params: kind ? { kind } : {} },
    ).then(r => r.data),

  /**
   * 单条巡检记录的列表行（与 `list` 的 items **同形状**）。
   *
   * 独立详情页 `/inspection/log/:id` 只拿得到一个 id，标题栏要的
   * `robot_name` / `status` / `remark` 得靠它 —— **不要**退化成"拉一页列表再本地 find"，
   * 记录一多就漏，还平白多传一页数据。
   */
  summary: (runId: number) =>
    http.get<InspectionRunRow>(`${base}/${runId}/summary`).then(r => r.data),

  /** 单次巡检详情（旧表口径：按航点分组 + 校准数据 + 结论摘要）。 */
  detail: (runId: number) => http.get<any>(`${base}/${runId}`).then(r => r.data),

  /** 异步触发生成巡检报表。 */
  generateReport: (runId: number, regenerate = false) =>
    http.post<{ status: string; path?: string }>(`${base}/${runId}/report/generate`, null, {
      params: { regenerate },
    }).then(r => r.data),

  /** 查询报表生成状态。 */
  reportStatus: (runId: number) =>
    http.get<ReportStatus>(`${base}/${runId}/report/status`).then(r => r.data),

  /** 手动触发指定动作的检测。 */
  triggerDetect: (runId: number, actionResultId: number) =>
    http.post<{ code: number; msg: string }>(
      `${base}/${runId}/actions/${actionResultId}/trigger_detect`,
    ).then(r => r.data),

  /** 取消巡检。 */
  cancelRun: (runId: number) =>
    http.post<{ code: number; msg: string }>(`${base}/${runId}/cancel`).then(r => r.data),
}

// —— 展示口径（纯函数，供页面与 verify 脚本共用）——
//
// 返回类型统一用宽 `string`：本模块是纯逻辑模块，不能 import Semi 的类型
// （`@douyinfe/semi-*` 在 Node 原生 ESM 下加载不了，verify 脚本会连编译都过不去），
// 由调用方在传进 `<Tag color={...}>` 处做一次窄化。

/** 展示状态 -> Semi Tag 颜色。 */
export function displayStatusColor(s: string): string {
  const map: Record<string, string> = {
    started: 'blue', running: 'blue', done: 'green',
    failed: 'red', canceled: 'grey', stalled: 'orange',
  }
  return map[s] || 'grey'
}

/** 展示状态 -> 中文文案。 */
export function displayStatusText(s: string): string {
  const map: Record<string, string> = {
    started: '进行中', running: '进行中', done: '已完成',
    failed: '失败', canceled: '已取消', stalled: '疑似中断',
  }
  return map[s] || s || '未知'
}

/** 动作分发状态 -> 中文文案。 */
export function dispatchText(s: string): string {
  const map: Record<string, string> = {
    pending: '待分发', done: '已分发', failed: '分发失败',
  }
  return map[s] || s || '—'
}

/** 动作分发状态 -> Tag 颜色。 */
export function dispatchColor(s: string): string {
  const map: Record<string, string> = { pending: 'grey', done: 'green', failed: 'red' }
  return map[s] || 'grey'
}

/** 测点来源 -> 中文文案。 */
export function kindText(k: string): string {
  const map: Record<string, string> = { thermometry: '测温点', detect: '检测点' }
  return map[k] || k || '—'
}

/**
 * 检测结论 -> 中文文案。
 *
 * ⚠️ ``passed`` 是 **三态**：true 通过 / false 未通过 / null 还没判定。
 * 把 null 混进 false 会凭空造出一堆"异常"，这是这个页面最容易出错的地方。
 */
export function passedText(passed: boolean | null | undefined): string {
  if (passed === true) return '通过'
  if (passed === false) return '未通过'
  return '未判定'
}

/** 检测结论 -> Tag 颜色（同上，三态）。 */
export function passedColor(passed: boolean | null | undefined): string {
  if (passed === true) return 'green'
  if (passed === false) return 'red'
  return 'grey'
}

/** 进度百分比文案；`total` 为 0 时给 "—" 而不是 "0%"。 */
export function progressText(done: number, total: number, pct: number | null): string {
  if (!total) return '—'
  return `${done}/${total} (${pct ?? 0}%)`
}
