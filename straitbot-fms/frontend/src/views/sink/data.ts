// ========== 下沉静态界面 — 示例数据 ==========
// 测点档案 / 巡检计划 / 巡检日志 三个下沉页面的静态演示数据。
// 后端接口开发完成后，本文件将被真实 API 调用替换。

export interface SubstationRow {
  id: number
  name: string
  code: string
  robot: string
  voltage: string
  mapCount: number
}

export interface BayRow {
  id: number
  name: string
  code: string
  voltage: string
  type: string
  typeColor: string
}

export interface EquipmentRow {
  id: number
  name: string
  code: string
  voltage: string
  type: string
  typeColor: string
  map: string
}

export interface PointRow {
  id: number
  name: string
  parent: string
  code: string
  detectType: string
  detectColor: string
  times: number
  steerPoint: string
  bound: boolean
}

export interface PlanRow {
  id: number
  name: string
  timeDesc: string
  weekDesc: string
  type: '全站' | '例行' | '特定'
  trip: string
  cycleType: '循环' | '间隔'
  cycle: string
  effective: boolean
  expired?: boolean
  autoBlock?: boolean
}

export interface LogRow {
  id: number
  plan: string
  total: number | null
  done: number | null
  error: number
  planStart: string
  start: string
  end: string
  status: 'done' | 'running' | 'interrupted' | 'pending'
}

// ---------- 测点档案：台账树（变电站 → 电压等级 → 间隔 → 设备 → 测点） ----------

export interface SinkTreeNode {
  key: string
  label: string
  code?: string
  children?: SinkTreeNode[]
}

export const ARCHIVE_TREE: SinkTreeNode[] = [
  {
    key: 'st-110001',
    label: '110kV 东郊变电站',
    code: '110001',
    children: [
      {
        key: 'vg-110',
        label: '110kV（电压等级）',
        children: [
          {
            key: 'bay-110001001',
            label: '#1主变间隔',
            code: '110001001',
            children: [
              {
                key: 'eqt-110001001001',
                label: '#1主变压器',
                code: '110001001001',
                children: [
                  { key: 'pt-110001001001001', label: '油温表 A相', code: '…001' },
                  { key: 'pt-110001001001002', label: '呼吸器', code: '…002' },
                  { key: 'pt-110001001001003', label: '本体红外测温', code: '…003' },
                ],
              },
              {
                key: 'eqt-110001001002',
                label: '#1主变110kV侧断路器',
                code: '110001001002',
                children: [
                  { key: 'pt-110001001002001', label: 'SF6 气压表', code: '…001' },
                  { key: 'pt-110001001002002', label: '避雷器动作计数器', code: '…002' },
                ],
              },
            ],
          },
          {
            key: 'bay-110001002',
            label: '110kV出线Ⅰ回间隔',
            code: '110001002',
            children: [
              { key: 'eqt-110001002001', label: '出线断路器', code: '110001002001' },
            ],
          },
        ],
      },
      {
        key: 'vg-10',
        label: '10kV（电压等级）',
        children: [
          { key: 'bay-110001003', label: '10kV开关室间隔', code: '110001003' },
        ],
      },
    ],
  },
  {
    key: 'st-220002',
    label: '220kV 滨湖变电站',
    code: '220002',
    children: [
      { key: 'vg-220', label: '220kV（电压等级）' },
    ],
  },
]

// 新建计划弹窗（例行 / 特定）里的设备-测点勾选树
export interface CheckNode {
  key: string
  label: string
  children?: CheckNode[]
}

export const PLAN_POINT_TREE: CheckNode[] = [
  {
    key: 'eqt-1',
    label: '#1主变压器（110001001001）',
    children: [
      { key: 'pt-1', label: '油温表 A相' },
      { key: 'pt-2', label: '呼吸器' },
      { key: 'pt-3', label: '本体红外测温' },
    ],
  },
  {
    key: 'eqt-2',
    label: '#1主变110kV侧断路器（110001001002）',
    children: [
      { key: 'pt-4', label: 'SF6 气压表' },
      { key: 'pt-5', label: '避雷器动作计数器' },
    ],
  },
  {
    key: 'eqt-3',
    label: '出线断路器（110001002001）',
    children: [
      { key: 'pt-6', label: '断路器机构外观' },
    ],
  },
]

export const SUBS: SubstationRow[] = [
  { id: 1, name: '110kV 东郊变电站', code: '110001', robot: '机器人1（192.168.8.60）', voltage: '110kV / 10kV', mapCount: 3 },
  { id: 2, name: '220kV 滨湖变电站', code: '220002', robot: '机器人2（192.168.8.61）', voltage: '220kV / 110kV / 10kV', mapCount: 5 },
]

export const BAYS: BayRow[] = [
  { id: 1, name: '#1主变间隔', code: '110001001', voltage: '110kV', type: '主变间隔', typeColor: 'blue' },
  { id: 2, name: '110kV出线Ⅰ回间隔', code: '110001002', voltage: '110kV', type: '出线间隔', typeColor: 'cyan' },
]

export const EQTS: EquipmentRow[] = [
  { id: 1, name: '#1主变压器', code: '110001001001', voltage: '110kV', type: '主变', typeColor: 'blue', map: '东郊站总图 v3' },
  { id: 2, name: '#1主变110kV侧断路器', code: '110001001002', voltage: '110kV', type: '断路器', typeColor: 'cyan', map: '东郊站总图 v3' },
]

export const POINTS: PointRow[] = [
  { id: 1, name: '油温表 A相', parent: '#1主变压器 · 表计识别', code: '110001001001001', detectType: '表计识别', detectColor: 'blue', times: 1, steerPoint: 'P110-3', bound: true },
  { id: 2, name: '呼吸器', parent: '#1主变压器 · 外观识别', code: '110001001001002', detectType: '外观识别', detectColor: 'cyan', times: 1, steerPoint: 'P110-4', bound: true },
  { id: 3, name: '本体红外测温', parent: '#1主变压器 · 红外测温', code: '110001001001003', detectType: '红外测温', detectColor: 'orange', times: 2, steerPoint: 'P110-5', bound: true },
  { id: 4, name: 'SF6 气压表', parent: '#1主变110kV侧断路器 · 表计识别', code: '110001001002001', detectType: '表计识别', detectColor: 'blue', times: 1, steerPoint: '', bound: false },
  { id: 5, name: '避雷器动作计数器', parent: '#1主变110kV侧断路器 · 表计识别', code: '110001001002002', detectType: '表计识别', detectColor: 'blue', times: 1, steerPoint: 'P112-1', bound: true },
  { id: 6, name: '局放传感器 UHF', parent: '#1主变压器 · 局放检测', code: '110001001001004', detectType: '局放检测', detectColor: 'purple', times: 1, steerPoint: '', bound: false },
]

// ---------- 巡检计划 ----------

export const PLANS: PlanRow[] = [
  { id: 1, name: '全站巡检-日巡', timeDesc: '07:30 – 09:30', weekDesc: '每天（一~日全选）', type: '全站', trip: '单程往返', cycleType: '循环', cycle: '24 小时', effective: true },
  { id: 2, name: '例行-主变区巡检', timeDesc: '10:00 – 11:00', weekDesc: '周一至周五', type: '例行', trip: '交替往返', cycleType: '循环', cycle: '24 小时', effective: true },
  { id: 3, name: '特殊-夜间红外', timeDesc: '22:00 – 23:00', weekDesc: '每天', type: '特定', trip: '单程', cycleType: '循环', cycle: '48 小时', effective: false },
  { id: 4, name: '例行-10kV开关室', timeDesc: '14:00 – 14:40', weekDesc: '周一 / 三 / 五', type: '例行', trip: '单程往返', cycleType: '循环', cycle: '72 小时', effective: true },
  { id: 5, name: '全站巡检-周末加强', timeDesc: '08:00 – 10:30', weekDesc: '周六 / 日', type: '全站', trip: '交替往返', cycleType: '间隔', cycle: '12 小时', effective: true, autoBlock: true },
  { id: 6, name: '特定-局放专项（已过期）', timeDesc: '09:00 – 09:30', weekDesc: '每月 1 日', type: '特定', trip: '单程', cycleType: '循环', cycle: '720 小时', effective: false, expired: true },
]

export interface HistoryRow {
  id: number
  name: string
  planStart: string
  start: string
  end: string
  state: 'done-cached' | 'done-generating' | 'interrupted' | 'canceled'
}

export const HISTORY_ROWS: HistoryRow[] = [
  { id: 1024, name: '全站巡检-日巡', planStart: '2026-08-24 07:30', start: '2026-08-24 07:31', end: '2026-08-24 09:12', state: 'done-generating' },
  { id: 1023, name: '全站巡检-日巡', planStart: '2026-08-23 07:30', start: '2026-08-23 07:31', end: '2026-08-23 09:05', state: 'done-cached' },
  { id: 1022, name: '全站巡检-日巡', planStart: '2026-08-22 07:30', start: '2026-08-22 07:30', end: '2026-08-22 07:58', state: 'interrupted' },
  { id: 1021, name: '全站巡检-日巡', planStart: '2026-08-21 07:30', start: '', end: '', state: 'canceled' },
]

// ---------- 巡检日志 ----------

export const LOGS: LogRow[] = [
  { id: 1024, plan: '全站巡检-日巡', total: 104, done: 104, error: 3, planStart: '2026-08-24 07:30', start: '2026-08-24 07:31', end: '2026-08-24 09:12', status: 'done' },
  { id: 1023, plan: '例行-主变区巡检', total: 42, done: 42, error: 1, planStart: '2026-08-24 10:00', start: '2026-08-24 10:00', end: '2026-08-24 10:46', status: 'done' },
  { id: 1025, plan: '例行-10kV开关室', total: 38, done: 21, error: 0, planStart: '2026-08-24 14:00', start: '2026-08-24 14:00', end: '', status: 'running' },
  { id: 1022, plan: '特殊-夜间红外', total: 26, done: 26, error: 2, planStart: '2026-08-23 22:00', start: '2026-08-23 22:01', end: '2026-08-23 23:01', status: 'done' },
  { id: 1021, plan: '全站巡检-日巡', total: 104, done: 57, error: 0, planStart: '2026-08-22 07:30', start: '2026-08-22 07:30', end: '2026-08-22 07:58', status: 'interrupted' },
  { id: 1026, plan: '例行-主变区巡检', total: 42, done: null, error: 0, planStart: '2026-08-25 10:00', start: '', end: '', status: 'pending' },
]

export interface PointResultRow {
  id: number
  point: string
  detect: string
  detectColor: string
  result: string
  value: string
  ok: boolean
  review: '待复核' | '已确认' | 'none'
}

export const POINT_RESULTS: PointResultRow[] = [
  { id: 1, point: '油温表 A相', detect: '表计识别', detectColor: 'blue', result: '识别成功', value: '86.3 ℃（阈值 85）', ok: false, review: '待复核' },
  { id: 2, point: '呼吸器', detect: '外观识别', detectColor: 'cyan', result: '识别成功', value: '外观正常 · 硅胶变色 30%', ok: true, review: 'none' },
  { id: 3, point: '本体红外测温', detect: '红外测温', detectColor: 'orange', result: '识别成功', value: '最高温 71.2 ℃ / 环温 32.5 ℃', ok: false, review: '已确认' },
  { id: 4, point: 'SF6 气压表', detect: '表计识别', detectColor: 'blue', result: '识别成功', value: '0.52 MPa', ok: true, review: 'none' },
]

export const SNAPSHOT_TIMES = [
  '07:31:05', '07:33:41', '07:36:12', '07:39:58', '07:42:15', '07:45:33',
  '07:48:20', '07:51:07', '07:55:44', '08:01:19', '08:06:52', '08:12:30',
]

export const IMAGE_THUMBS = [
  { label: 'P110-3', abnormal: false },
  { label: 'P110-3 红', abnormal: false },
  { label: 'P110-4', abnormal: true },
  { label: 'P110-4 红', abnormal: false },
  { label: 'P110-5', abnormal: false },
  { label: 'P112-1', abnormal: false },
  { label: 'P112-2', abnormal: false },
  { label: 'P113-1', abnormal: false },
  { label: 'P113-2', abnormal: false },
]

// ---------- 日历视图 ----------

export interface CalPill {
  cls: 'pp-all' | 'pp-reg' | 'pp-spec'
  label: string
}

export interface CalCell {
  /** 显示的日 */
  day: number
  /** 是否本月 */
  inMonth: boolean
  today?: boolean
  pills: CalPill[]
}

/** 生成 2026 年 8 月的月历（周一起始，6 行 × 7 列），计划胶囊按周期规则铺排 */
export function buildCalendar(): CalCell[] {
  const cells: CalCell[] = []
  const start = new Date(2026, 6, 27) // 2026-07-27 周一
  for (let i = 0; i < 42; i++) {
    const d = new Date(start.getFullYear(), start.getMonth(), start.getDate() + i)
    const inMonth = d.getMonth() === 7
    const wd = d.getDay() // 0=周日
    const isWeekend = wd === 0 || wd === 6
    const isWeekday = !isWeekend
    const pills: CalPill[] = []
    if (inMonth) {
      pills.push({ cls: 'pp-all', label: '【全】全站日巡 07:30-09:30' })
      pills.push({ cls: 'pp-spec', label: '【特】夜间红外 22:00-23:00' })
      if (isWeekday) pills.push({ cls: 'pp-reg', label: '【例】主变区 10:00-11:00' })
      if (wd === 1 || wd === 3 || wd === 5) pills.push({ cls: 'pp-reg', label: '【例】开关室 14:00-14:40' })
      if (isWeekend) pills.push({ cls: 'pp-all', label: '【全】周末加强 08:00-10:30' })
    }
    cells.push({
      day: d.getDate(),
      inMonth,
      today: d.getDate() === 24 && inMonth,
      pills,
    })
  }
  return cells
}

export interface DayPlanItem {
  name: string
  time: string
  type: string
  typeColor: string
  active?: boolean
}

export const DAY_PLANS: DayPlanItem[] = [
  { name: '全站巡检-日巡', time: '07:30 – 09:30', type: '全站', typeColor: 'blue', active: true },
  { name: '例行-主变区巡检', time: '10:00 – 11:00', type: '例行', typeColor: 'green' },
  { name: '特殊-夜间红外', time: '22:00 – 23:00', type: '特定', typeColor: 'orange' },
]

export const TIMEFLOW = [
  { time: '07:30-09:30', name: '全站巡检-日巡', on: true },
  { time: '10:00-11:00', name: '例行-主变区巡检', on: true },
  { time: '14:00-14:40', name: '例行-10kV开关室', on: true },
  { time: '22:00-23:00', name: '特殊-夜间红外', on: false },
]

// ---------- 告警模板（检测类型） ----------

export interface AlarmTemplateRow {
  id: number
  name: string
  type: string
  sensor: string
  sensorColor: string
  algorithm: string
}

export const ALARM_TEMPLATES: AlarmTemplateRow[] = [
  { id: 1, name: '油温表-指针读数', type: '油温表', sensor: '温度传感器', sensorColor: 'orange', algorithm: 'meter-read-v3' },
  { id: 2, name: 'SF6气压表-指针读数', type: 'SF6气压表', sensor: '压力传感器', sensorColor: 'blue', algorithm: 'meter-read-v3' },
  { id: 3, name: '红外-区域最高温', type: '红外热像', sensor: '红外热像仪', sensorColor: 'red', algorithm: 'infrared-max-v2' },
  { id: 4, name: '外观-破损渗漏识别', type: '外观图像', sensor: '图像摄像头', sensorColor: 'cyan', algorithm: 'appearance-defect-v1' },
  { id: 5, name: '局放-特高频', type: '局放检测', sensor: '局放传感器', sensorColor: 'purple', algorithm: 'pd-uhf-v1' },
]

export interface TemplatePointRow {
  id: number
  substation: string
  bay: string
  equipment: string
  point: string
  time: string
}

export const TEMPLATE_POINTS: TemplatePointRow[] = [
  { id: 1, substation: '110kV 东郊变电站', bay: '#1主变间隔', equipment: '#1主变压器', point: '油温表 A相', time: '2026-08-20 14:32' },
  { id: 2, substation: '110kV 东郊变电站', bay: '#1主变间隔', equipment: '#1主变压器', point: '油温表 B相', time: '2026-08-20 14:32' },
  { id: 3, substation: '110kV 东郊变电站', bay: '#1主变间隔', equipment: '#1主变110kV侧断路器', point: '油温表 C相', time: '2026-08-18 09:15' },
  { id: 4, substation: '220kV 滨湖变电站', bay: '#2主变间隔', equipment: '#2主变压器', point: '油温表 A相', time: '2026-08-17 16:40' },
]

// ---------- 航点绑定测点 / 检测算法选择 ----------

export interface WpRow {
  id: number
  name: string
  type: '定点' | '途经' | '充电' | '返回'
  floor: string
  actionCount: number
  boundCount: number
}

export const WAYPOINTS: WpRow[] = [
  { id: 1, name: 'P110-3', type: '定点', floor: '1F', actionCount: 1, boundCount: 2 },
  { id: 2, name: 'P110-4', type: '定点', floor: '1F', actionCount: 1, boundCount: 1 },
  { id: 3, name: 'P110-5', type: '定点', floor: '1F', actionCount: 1, boundCount: 1 },
  { id: 4, name: '充电桩位', type: '充电', floor: '1F', actionCount: 0, boundCount: 0 },
  { id: 5, name: '途经点-12', type: '途经', floor: '2F', actionCount: 0, boundCount: 0 },
  { id: 6, name: '返回点-1', type: '返回', floor: '1F', actionCount: 0, boundCount: 0 },
]

export interface WpBoundRow {
  id: number
  point: string
  equipment: string
  detect: string
  detectColor: string
  algorithm: string
}

export const WP_BOUND: WpBoundRow[] = [
  { id: 1, point: '油温表 A相', equipment: '#1主变压器', detect: '表计识别', detectColor: 'blue', algorithm: 'meter-read-v3' },
  { id: 2, point: '呼吸器', equipment: '#1主变压器', detect: '外观识别', detectColor: 'cyan', algorithm: 'appearance-defect-v1' },
]

export const DETECT_TYPES = ['可见光', '红外', '视频', '局放-开放式超声波', '局放-接触式超声波', '局放-特高频', '局放-地电法']

export const ALGORITHMS = [
  'meter-read-v3 · 表计读数',
  'infrared-max-v2 · 红外区域最高温',
  'appearance-defect-v1 · 外观破损渗漏',
  'pd-uhf-v1 · 局放特高频',
  'pd-ae-v1 · 局放接触式超声波',
]

export interface DetectRow {
  id: number
  box: string
  result: string
  bound: string
}

export const DETECT_ROWS: DetectRow[] = [
  { id: 1, box: '识别框 1', result: '油温 86.3 ℃（越限）', bound: '油温表 A相' },
  { id: 2, box: '识别框 2', result: '液位 62 %', bound: '未绑定' },
]
