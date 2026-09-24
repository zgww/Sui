/**
 * 检测流程 prefab 的前端显示规则：节点类型 → 中文名 / 颜色 / 树上摘要。
 * 后端只给英文字段名，中文口径集中在这一个文件，改文案不用翻组件。
 *
 * 算法节点不再是"一个通用 DetectorNode + 下拉"，而是每种算法一个子类
 * （后端 nodes/algorithms.py），节点类型即算法身份，因此这里要逐个登记
 * 中文名与配色；新增算法节点时在 ALGORITHM_NODE_TEXT / 配色里补一条。
 *
 * ⚠️ 本文件**只能放纯逻辑**（不引 React、不引组件库）：`verify-detect-prefab.mjs`
 * 用 tsc 单独编译它再 import，`@douyinfe/semi-icons` 在 Node 原生 ESM 下加载不了。
 * 图标在 `detectSelectIcons.tsx`（页面/画布引那边）。
 */

/** 视觉算法节点类型 → 中文名（与 data/algorithms.json 的 name 对齐） */
const ALGORITHM_NODE_TEXT: Record<string, string> = {
  // 状态识别
  SwitchStateNode: '开关分合状态',
  IndicatorLightNode: '指示灯状态',
  CabinetDoorNode: '柜门开合',
  ValveStateNode: '阀门状态',
  // 表计读数
  MeterPointerNode: '指针表读数',
  MeterDigitalNode: '数字表读数',
  MeterLevelNode: '液位计读数',
  CounterReadNode: '计数器读数',
  // 缺陷检测
  InsulatorDamageNode: '绝缘子破损',
  EquipmentRustNode: '设备锈蚀',
  CableDamageNode: '线缆破损',
  WaterLeakNode: '渗漏水渍',
  // 安全告警
  PersonIntrusionNode: '人员入侵',
  SmokeFireNode: '烟雾火焰',
  ForeignObjectNode: '异物悬挂',
  HelmetCheckNode: '安全帽佩戴',
}

/** 全部算法检测节点类型名（DetectorNode 子类），供摘要 / 配色判定 */
export const ALGORITHM_NODE_TYPES = new Set(Object.keys(ALGORITHM_NODE_TEXT))

/** 某类型是否为视觉算法检测节点 */
export function isDetectorNode(type?: string): boolean {
  return !!type && ALGORITHM_NODE_TYPES.has(type)
}

export const NODE_TYPE_TEXT: Record<string, string> = {
  DetectPipelineNode: '检测流程',
  ...ALGORITHM_NODE_TEXT,
  // 不在这份"每种算法一个子类"的登记表里（它不是 algorithms.json 里的算法，
  // 而是"一个节点 + 算法下拉"对接现有推理服务），所以单独补中文名 ——
  // 不补的话类型选择器里显示的是裸英文 MeterAlgorithmNode。
  MeterAlgorithmNode: '通用算法（推理服务）',
  FrameSourceNode: '取帧源',
  FrameSkipNode: '抽帧节流',
  RoiFilterNode: 'ROI 过滤',
  TimeWindowNode: '时段窗口',
  ResultFilterNode: '结果过滤',
  EvidenceNode: '存证',
  AlarmNode: '事件告警',
  NumericAlarmNode: '数值告警',
  RangeAlarmNode: '数值范围告警',
  ForwardNode: '转发',
  SmsNotifyNode: '短信通知',
  EmailNotifyNode: '邮件通知',
}

/** 节点类型 → Semi Tag 颜色（视觉算法按四大类别配色） */
export const DETECT_TYPE_COLOR: Record<string, any> = {
  DetectPipelineNode: 'blue',
  // 状态识别 = blue
  SwitchStateNode: 'blue', IndicatorLightNode: 'blue',
  CabinetDoorNode: 'blue', ValveStateNode: 'blue',
  // 表计读数 = green
  MeterPointerNode: 'green', MeterDigitalNode: 'green',
  MeterLevelNode: 'green', CounterReadNode: 'green',
  // 缺陷检测 = orange
  InsulatorDamageNode: 'orange', EquipmentRustNode: 'orange',
  CableDamageNode: 'orange', WaterLeakNode: 'orange',
  // 安全告警 = red
  PersonIntrusionNode: 'red', SmokeFireNode: 'red',
  ForeignObjectNode: 'red', HelmetCheckNode: 'red',
  FrameSourceNode: 'cyan',
  FrameSkipNode: 'cyan',
  RoiFilterNode: 'cyan',
  TimeWindowNode: 'violet',
  ResultFilterNode: 'teal',
  EvidenceNode: 'light-blue',
  AlarmNode: 'red',
  NumericAlarmNode: 'amber',
  RangeAlarmNode: 'lime',
  ForwardNode: 'indigo',
  SmsNotifyNode: 'pink',
  EmailNotifyNode: 'purple',
}

/** 连线端点小色块：取帧/检测/过滤/结果/告警/外发，一眼看出节点角色 */
export const DETECT_COLOR = {
  source: '#0fb5b5',
  detector: '#165dff',
  filter: '#0fc6c2',
  result: '#3491fa',
  alarm: '#f53f3f',
  action: '#722ed1',
}
export const LEADER = {
  source: { color: DETECT_COLOR.source, label: '帧' },
  detector: { color: DETECT_COLOR.detector, label: '检' },
  filter: { color: DETECT_COLOR.filter, label: '滤' },
  result: { color: DETECT_COLOR.result, label: '果' },
  alarm: { color: DETECT_COLOR.alarm, label: '警' },
  action: { color: DETECT_COLOR.action, label: '发' },
}

export function detectTypeLabel(type?: string): string {
  if (!type) return '未命名节点'
  return NODE_TYPE_TEXT[type] || type
}

/** 检测树节点是否允许继续挂子节点（叶子节点不能加） */
export const DETECT_LEAF_TYPES = new Set([
  'FrameSourceNode', 'FrameSkipNode', 'RoiFilterNode', 'TimeWindowNode',
  'ResultFilterNode', ...ALGORITHM_NODE_TYPES, 'MeterAlgorithmNode',
  'EvidenceNode', 'AlarmNode', 'NumericAlarmNode', 'RangeAlarmNode',
  'ForwardNode', 'SmsNotifyNode', 'EmailNotifyNode',
])

export function isDetectLeaf(type?: string): boolean {
  return !!type && DETECT_LEAF_TYPES.has(type)
}

/** 节点类型选择器分组（供"添加节点"弹窗用；中文名取 NODE_TYPE_TEXT） */
export function buildTypeTreeOptions(types: Record<string, unknown>): any[] {
  const groups: { label: string; types: string[] }[] = [
    { label: '流程', types: ['DetectPipelineNode'] },
    { label: '取帧 / 过滤', types: ['FrameSourceNode', 'FrameSkipNode', 'RoiFilterNode', 'TimeWindowNode'] },
    { label: '视觉算法', types: Object.keys(ALGORITHM_NODE_TEXT) },
    { label: '结果 / 存证', types: ['ResultFilterNode', 'EvidenceNode'] },
    { label: '告警', types: ['AlarmNode', 'NumericAlarmNode', 'RangeAlarmNode'] },
    { label: '外发', types: ['ForwardNode', 'SmsNotifyNode', 'EmailNotifyNode'] },
  ]
  const avail = new Set(Object.keys(types))
  const out: any[] = []
  for (const g of groups) {
    const children = g.types.filter(t => avail.has(t)).map(t => ({
      value: t,
      label: `${detectTypeLabel(t)}  ${t}`,
    }))
    if (children.length) out.push({ value: `g:${g.label}`, label: g.label, children, disabled: true })
  }
  return out
}

/** 从后端拉取视觉算法目录（检测流程与航点检测框共用同一份） */
export interface DetectAlgorithm {
  id: string
  name: string
  category?: string
  description?: string
  color?: string
}
export async function getDetectAlgorithms(): Promise<DetectAlgorithm[]> {
  const r = await fetch('/api/waypoint-prefab/algorithms')
  if (!r.ok) return []
  const data = await r.json()
  return Array.isArray(data?.algorithms) ? data.algorithms : []
}

function isNum(v: unknown): v is number {
  return typeof v === 'number' && Number.isFinite(v)
}
function round(v: number): string {
  return String(Math.round(v * 100) / 100)
}

/** 画布节点卡片上的一行小字摘要（每个节点挑最关键的配置，不把整张表单搬上来） */
export function detectNodeSummary(type: string, props: Record<string, any>): string {
  const p = props || {}
  // 视觉算法节点（DetectorNode 各子类）：共性阈值/类别 + 类别专属字段
  if (isDetectorNode(type)) {
    const parts: string[] = []
    if (isNum(p.threshold)) parts.push(`阈值 ${round(p.threshold)}`)
    if (Array.isArray(p.labels) && p.labels.length) parts.push(p.labels.join('/'))
    if (isNum(p.max_results) && p.max_results > 0) parts.push(`最多 ${p.max_results}`)
    if (p.expected_state) parts.push(`期望 ${p.expected_state}`)
    if (p.expected_color) parts.push(`灯色 ${p.expected_color}`)
    if (p.unit) parts.push(`单位 ${p.unit}`)
    if (isNum(p.range_max) && p.range_max > 0)
      parts.push(`量程 ${round(p.range_min)}~${round(p.range_max)}`)
    if (isNum(p.decimals) && p.decimals > 0) parts.push(`${p.decimals}位小数`)
    if (isNum(p.min_area_ratio) && p.min_area_ratio > 0) parts.push(`面积≥${round(p.min_area_ratio)}`)
    if (isNum(p.min_box_ratio) && p.min_box_ratio > 0) parts.push(`框≥${round(p.min_box_ratio)}`)
    return parts.join(' · ')
  }
  switch (type) {
    case 'DetectPipelineNode':
      return [p.scene && `场景：${p.scene}`, p.manual_confirm && '需人工确认'].filter(Boolean).join(' · ')
    case 'FrameSourceNode': {
      const src = []
      if (p.camera_id) src.push(`相机 ${p.camera_id}`)
      if (p.image_dir) src.push('目录轮询')
      if (p.topic) src.push(`话题 ${p.topic}`)
      if (p.interval_seconds) src.push(`每 ${p.interval_seconds}s`)
      return src.join(' · ')
    }
    case 'FrameSkipNode': {
      if (p.mode === 'fps') return `限流 ${p.fps ?? 1} 帧/秒`
      if (p.mode === 'interval') return `每 ${p.interval_seconds ?? 10} 秒一帧`
      const m: Record<string, string> = { 1: '每帧', 2: '隔 1 帧', 5: '隔 4 帧', 10: '隔 9 帧', 30: '隔 29 帧' }
      return m[String(p.every_n ?? 1)] || `每 ${p.every_n ?? 1} 帧`
    }
    case 'RoiFilterNode':
      if (p.zone_ids?.length) return `区域 ${p.zone_ids.join('/')}`
      if (p.box) return `矩形 ${Math.round((p.box.w || 0) * 100)}%×${Math.round((p.box.h || 0) * 100)}%`
      if (p.polygon?.length) return `${p.polygon.length} 边形`
      return '未框选区域'
    case 'TimeWindowNode':
      if (!p.enabled_windows?.length) return '未设时段（全天）'
      return p.enabled_windows.map((w: any) =>
        `${w.days?.join('') || '每天'} ${w.start || '00:00'}-${w.end || '23:59'}`).join('；')
    case 'ResultFilterNode': {
      const r = []
      if (isNum(p.min_confidence)) r.push(`置信度≥${round(p.min_confidence)}`)
      if (isNum(p.max_per_frame) && p.max_per_frame > 0) r.push(`每帧≤${p.max_per_frame}`)
      if (p.require_labels?.length) r.push(`需 ${p.require_labels.join('/')}`)
      if (p.exclude_labels?.length) r.push(`排除 ${p.exclude_labels.join('/')}`)
      return r.join(' · ')
    }
    case 'EvidenceNode':
      return [
        p.save_image ? '存图' : null,
        p.save_video ? `存视频 ${p.video_seconds ?? 5}s` : null,
        p.storage_days ? `保留 ${p.storage_days} 天` : null,
      ].filter(Boolean).join(' · ')
    case 'AlarmNode':
      return [p.level || '预警', p.dedup_seconds ? `去重 ${p.dedup_seconds}s` : ''].filter(Boolean).join(' · ')
    case 'MeterAlgorithmNode': {
      // 这个节点**没有阈值**（置信度阈值/其他参数已下线，见后端同名节点文档），
      // 所以不能走上面 isDetectorNode 那条分支（那边第一句就是「阈值 x」）。
      // 保留下来的只有两个结果口径字段；算法本身是 panel_algorithm 编码，
      // 对人不友好，不往摘要里塞。
      const parts: string[] = []
      if (Array.isArray(p.labels) && p.labels.length) parts.push(p.labels.join('/'))
      if (isNum(p.max_results) && p.max_results > 0) parts.push(`最多 ${p.max_results}`)
      return parts.join(' · ')
    }
    case 'NumericAlarmNode': {
      const m: Record<string, string> = { '>': '>', '>=': '≥', '<': '<', '<=': '≤', '==': '=' }
      return [`${p.metric || '数值'} ${m[p.op as string] || p.op} ${round(p.threshold ?? 0)}${p.unit || ''}`,
        p.level || '一般告警'].join(' · ')
    }
    case 'RangeAlarmNode':
      return [`${p.metric || '数值'} ${round(p.min_value ?? 0)}~${round(p.max_value ?? 0)}${p.unit || ''}`,
        p.mode === '区间外告警' ? '区间外告警' : '区间内告警', p.level || '一般告警'].join(' · ')
    case 'ForwardNode': {
      const map: Record<string, string> = { webhook: 'Webhook', mqtt: 'MQTT', kafka: 'Kafka', internal_topic: '内部总线' }
      return [map[p.target as string] || p.target, p.topic].filter(Boolean).join(' · ')
    }
    case 'SmsNotifyNode':
      return [p.phones?.length ? `${p.phones.length} 个号码` : '', `等级≥${p.min_level || '一般告警'}`]
        .filter(Boolean).join(' · ')
    case 'EmailNotifyNode':
      return [p.emails?.length ? `${p.emails.length} 个收件人` : '', `等级≥${p.min_level || '一般告警'}`]
        .filter(Boolean).join(' · ')
    default:
      return ''
  }
}

/**
 * 粘贴出来的检测子树要换掉业务 id（与 planSelect.regeneratePlanIds 同理）。
 *
 * 检测树节点目前**没有实例级业务编号**：节点在流程里以树路径定位，
 * camera_id / zone_ids / topic 都是对外部资源的**引用**，必须照抄、不能换。
 * 故当前只递归、返回 0；以后若给流程根或某类节点引入业务编号，在此按
 * node.type 换新并计数即可，调用方 Toast 已按返回值决定是否提示
 * "重新生成 N 个检测编号"。
 */
export function regenerateDetectIds(node: any): number {
  if (!node || typeof node !== 'object') return 0
  let n = 0
  for (const c of node.children || []) n += regenerateDetectIds(c)
  return n
}

/** 新建节点时给的默认值（按类型），让用户少填几个字段 */
export const DEFAULT_VALUES: Record<string, Record<string, any>> = {
  FrameSourceNode: { mode: 'camera', camera_id: '', interval_seconds: 10 },
  FrameSkipNode: { mode: 'every_n', every_n: 5 },
  RoiFilterNode: { zone_ids: [] },
  TimeWindowNode: { enabled_windows: [{ days: [1, 2, 3, 4, 5], start: '08:00', end: '18:00' }] },
  ResultFilterNode: { min_confidence: 0.5 },
  EvidenceNode: { save_image: true, save_video: false, storage_days: 30 },
  AlarmNode: { level: '一般告警', dedup_seconds: 60 },
  NumericAlarmNode: { level: '一般告警', op: '>', threshold: 0, hysteresis: 0, unit: '' },
  RangeAlarmNode: { level: '一般告警', min_value: 0, max_value: 100, mode: '区间内告警', inclusive: true, unit: '' },
  ForwardNode: { target: 'webhook' },
  SmsNotifyNode: { phones: [], min_level: '严重告警' },
  EmailNotifyNode: { emails: [], min_level: '严重告警' },
}

/** 运行状态 → 中文 + 颜色（画布节点状态点 / 树标签用） */
export const RUN_STATE_TEXT: Record<string, { text: string; color: string }> = {
  idle: { text: '未激活', color: '#86909c' },
  loaded: { text: '已加载', color: '#165dff' },
  running: { text: '运行中', color: '#00b42a' },
}

/** 流程整体运行状态 → 中文 */
export function runStateText(state?: string): string {
  return RUN_STATE_TEXT[state || 'idle']?.text || state || ''
}
