/**
 * 巡检计划编排的回归测试。
 *
 * 两件事一起锁：
 * 1. **纯函数**（`utils/planSelect.ts`）——航点 key 的取法、每日调度的时刻展开、
 *    树上那句摘要。这些错了不会报错，只会"数不对"（少触发一次、勾了 A 结果 B
 *    也算进去），必须能算。
 * 2. **源码级断言**（`views/InspectionPlanPrefab.tsx` + 后端节点模块）——
 *    右键菜单那几项是用户点名要的，删掉一项不会有任何类型错误，只能在这里锁。
 *
 * 与其它脚本同一套路：**不手抄源码**，用 tsc 把真实 .ts 编到临时目录再 import。
 * 运行：node scripts/verify-plan-prefab.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync, readFileSync, readdirSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'planpf-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath,
    [tscEntry, 'src/utils/planSelect.ts', '--outDir', out,
      '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
      '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

/** tsc 不给相对导入补 `.js`，Node 原生 ESM 必须要，产物里补一遍 */
const fixExt = (dir) => {
  for (const name of readdirSync(dir, { withFileTypes: true })) {
    const p = join(dir, name.name)
    if (name.isDirectory()) { fixExt(p); continue }
    if (!name.name.endsWith('.js')) continue
    const src = readFileSync(p, 'utf8')
    const next = src.replace(/(from\s+['"])(\.[^'"]*?)(['"])/g,
      (m, a, spec, c) => (spec.endsWith('.js') ? m : `${a}${spec}.js${c}`))
    if (next !== src) writeFileSync(p, next)
  }
}
fixExt(out)

const modPath = ['utils/planSelect.js', 'planSelect.js']
  .map((p) => join(out, p)).find((p) => existsSync(p))
if (!modPath) {
  console.error('编译产物里找不到 planSelect.js：', out)
  process.exit(1)
}
const P = await import(pathToFileURL(modPath).href)
const {
  waypointKey, collectWaypoints, waypointLabel,
  parseHm, formatHm, scheduleSlots, MAX_SLOTS_PER_DAY,
  planNodeSummary, planTypeLabel, regeneratePlanIds,
  PLAN_GROUP_TYPE, ensureGroupRoot, collectDisabled,
} = P

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const eq = (n, got, want) => check(n, got === want, `got=${JSON.stringify(got)} want=${JSON.stringify(want)}`)
const deep = (n, got, want) => check(n, JSON.stringify(got) === JSON.stringify(want),
  `got=${JSON.stringify(got)} want=${JSON.stringify(want)}`)

/* ============================================================ 1. 航点 key */

eq('1.1 有 wp_id 时用 wp_id',
  waypointKey({ properties: { wp_id: 'AO-RC-001' } }, 'root/children/3'), 'AO-RC-001')
eq('1.2 wp_id 为空白串时回落到路径',
  waypointKey({ properties: { wp_id: '   ' } }, 'root/children/3'), 'root/children/3')
eq('1.3 没有 wp_id 字段时回落到路径',
  waypointKey({ properties: {} }, 'root/children/0'), 'root/children/0')
eq('1.4 properties 整个缺失也不炸',
  waypointKey(undefined, 'root/children/9'), 'root/children/9')
// name 不能当 key：样例数据里多个航点同名甚至为 None，用它会让"勾了 A 也算 B"
check('1.5 绝不用 name 当 key',
  waypointKey({ properties: { name: 'AO-RC-001' } }, 'root/children/1') === 'root/children/1')

/* ============================================================ 2. 航点提取 */

const wpSpec = {
  root: {
    type: 'InspectionPlanNode',
    properties: {},
    children: [
      {
        type: 'GroupNode',
        properties: {},
        children: [
          {
            type: 'WaypointNode',
            properties: { wp_id: 'A-1', name: '一号柜', floor: 2, index: 1, x: 12.5 },
            children: [{ type: 'ActionPointNode', properties: {} }],
          },
          { type: 'WaypointNode', properties: { name: '手工画的', x: 3.25 } },
        ],
      },
      { type: 'WaypointNode', properties: { wp_id: 'B-1', name: '三号柜', floor: -1, index: 7, x: 0 } },
    ],
  },
}
const wps = collectWaypoints(wpSpec)
eq('2.1 递归抽出全部航点（含分组里的）', wps.length, 3)
eq('2.2 保持树中顺序', wps.map((w) => w.key).join(','), 'A-1,root/children/0/children/1,B-1')
eq('2.3 路径按 children 下标拼', wps[1].path, 'root/children/0/children/1')
eq('2.4 floor / index / x 原样带出', `${wps[0].floor},${wps[0].index},${wps[0].x}`, '2,1,12.5')
eq('2.5 缺 floor 回落 1', wps[1].floor, 1)
eq('2.6 负楼层（地下室）保留', wps[2].floor, -1)
eq('2.7 x=0 不被当成"缺失"', wps[2].x, 0)
eq('2.8 空 spec 返回空数组', collectWaypoints({}).length, 0)
eq('2.9 root 缺失也不炸', collectWaypoints(null).length, 0)

eq('2.10 名字缺失时回退到 wp_id', waypointLabel({ name: '', wp_id: 'X-9', index: 0, floor: 1, x: 0 }), 'X-9（F1 · 0.000 m）')
eq('2.11 名字与 id 都缺时回退到序号',
  waypointLabel({ name: '', wp_id: '', index: 4, floor: 1, x: 0 }), '航点 #4（F1 · 0.000 m）')
check('2.12 标签里绝不出现 undefined',
  !waypointLabel({ name: '', wp_id: '', index: 0, floor: 1, x: 0 }).includes('undefined'))

/* ============================================================ 3. HH:MM */

eq('3.1 正常解析', parseHm('08:30'), 510)
eq('3.2 零点', parseHm('00:00'), 0)
eq('3.3 末刻', parseHm('23:59'), 1439)
eq('3.4 单位数小时可解析', parseHm('8:05'), 485)
eq('3.5 半截写法不接受', parseHm('8:5'), null)
eq('3.6 小时越界', parseHm('24:00'), null)
eq('3.7 分钟越界', parseHm('12:60'), null)
eq('3.8 非字符串', parseHm(830), null)
eq('3.9 空串', parseHm(''), null)
eq('3.10 前后空格容忍', parseHm(' 09:00 '), 540)

eq('3.11 格式化补零', formatHm(485), '08:05')
eq('3.12 格式化零点', formatHm(0), '00:00')
eq('3.13 负数夹到 0', formatHm(-10), '00:00')
eq('3.14 超上限夹到 23:59', formatHm(99999), '23:59')
eq('3.15 小数四舍五入', formatHm(59.6), '01:00')

/* ============================================================ 4. 每日调度时刻 */

const slots1 = scheduleSlots('08:00', '18:00', 60)
eq('4.1 08:00–18:00 每 60 分 = 11 次', slots1.length, 11)
eq('4.2 首刻是开始时间', slots1[0], '08:00')
eq('4.3 末刻恰好落在结束时间', slots1[slots1.length - 1], '18:00')
eq('4.4 08:00–18:00 每 30 分 = 21 次', scheduleSlots('08:00', '18:00', 30).length, 21)

// 末次必须 <= end：08:00–18:30 每 60 分只能排到 18:00，不能多出 19:00
const slots2 = scheduleSlots('08:00', '18:30', 60)
eq('4.5 末次不越过结束时间', slots2[slots2.length - 1], '18:00')
check('4.6 排出来的时刻全在范围内',
  slots2.every((s) => parseHm(s) >= parseHm('08:00') && parseHm(s) <= parseHm('18:30')))

deep('4.7 起止相等 = 只触发一次', scheduleSlots('09:00', '09:00', 30), ['09:00'])
deep('4.8 跨零点不支持（返回空）', scheduleSlots('22:00', '06:00', 60), [])
deep('4.9 间隔为 0 返回空', scheduleSlots('08:00', '18:00', 0), [])
deep('4.10 间隔为负返回空', scheduleSlots('08:00', '18:00', -30), [])
deep('4.11 间隔非数字返回空', scheduleSlots('08:00', '18:00', 'abc'), [])
deep('4.12 时间非法返回空', scheduleSlots('8:5', '18:00', 30), [])
deep('4.13 缺字段返回空', scheduleSlots(undefined, undefined, 60), [])

const full = scheduleSlots('00:00', '23:59', 1)
eq('4.14 每分钟一次 = 1440 次（刚好到上限）', full.length, 1440)
eq('4.15 上限常量一致', MAX_SLOTS_PER_DAY, 1440)
check('4.16 上限兜住脏数据', scheduleSlots('00:00', '23:59', 0.0001).length <= MAX_SLOTS_PER_DAY)

/* ============================================================ 5. 树上摘要 */

eq('5.1 航点指定（全部）',
  planNodeSummary({ type: 'WaypointSelectNode', properties: { source: 'f1.prefab.json', include_all: true } }),
  'f1.prefab.json · 全部航点')
eq('5.2 航点指定（部分）',
  planNodeSummary({ type: 'WaypointSelectNode', properties: { source: 'f1.prefab.json', include_all: false, waypoint_ids: ['a', 'b'] } }),
  'f1.prefab.json · 2 个航点')
eq('5.3 没选航点树要如实说',
  planNodeSummary({ type: 'WaypointSelectNode', properties: { source: '', include_all: true } }),
  '未指定航点树 · 全部航点')
eq('5.4 测点指定（全部）',
  planNodeSummary({ type: 'PointSelectNode', properties: { include_all: true } }), '全部测点')
eq('5.5 测点指定（部分）',
  planNodeSummary({ type: 'PointSelectNode', properties: { include_all: false, point_ids: ['P1'] } }), '1 个测点')
eq('5.6 每日调度含次数',
  planNodeSummary({ type: 'DailyScheduleNode', properties: { start_time: '08:00', end_time: '18:00', interval_minutes: 60 } }),
  '08:00–18:00 · 每 60 分 · 每天 11 次')
check('5.7 排不出时刻时摘要要说清原因',
  planNodeSummary({ type: 'DailyScheduleNode', properties: { start_time: '22:00', end_time: '06:00', interval_minutes: 60 } })
    .includes('无法排出时刻'))
eq('5.8 计划编号进摘要',
  planNodeSummary({ type: 'InspectionPlanNode', properties: { plan_id: 'P-001' } }), '计划 P-001')
eq('5.9 分组没有摘要',
  planNodeSummary({ type: 'PlanGroupNode', properties: {} }), '')
eq('5.10 未知类型不炸', planNodeSummary({ type: 'Nope', properties: {} }), '')
eq('5.11 类型中文名', planTypeLabel('DailyScheduleNode'), '每日调度')
eq('5.12 未知类型回落原名', planTypeLabel('Nope'), 'Nope')

/* ============================================================ 6. 粘贴换 id */

const pasted = {
  type: 'InspectionPlanNode',
  properties: { plan_id: 'P-001' },
  children: [
    { type: 'WaypointSelectNode', properties: { source: 'f1.prefab.json', waypoint_ids: ['A-1'] } },
    { type: 'InspectionPlanNode', properties: { plan_id: 'P-002' }, children: [] },
  ],
}
const changed = regeneratePlanIds(pasted)
eq('6.1 递归换掉每个计划编号', changed, 2)
check('6.2 计划编号确实变了', pasted.properties.plan_id !== 'P-001' && pasted.children[1].properties.plan_id !== 'P-002')
check('6.3 换出来的编号非空', !!pasted.properties.plan_id && !!pasted.children[1].properties.plan_id)
check('6.4 两个编号不相同', pasted.properties.plan_id !== pasted.children[1].properties.plan_id)
deep('6.5 航点指定里的引用照抄不动', pasted.children[0].properties.waypoint_ids, ['A-1'])
eq('6.6 没有计划节点的子树改动数为 0',
  regeneratePlanIds({ type: 'PlanGroupNode', properties: {}, children: [] }), 0)

/* ============================================================ 6b. 根必须是分组 */

// 一个文件只能有一个根：根是单条计划 = 一个文件只能配一条计划。
// 根是分组，下面挂 N 条 InspectionPlanNode，才谈得上"一个文件多条计划"。
eq('6b.1 分组类型名', PLAN_GROUP_TYPE, 'PlanGroupNode')

const oldSpec = {
  name: '日常巡检',
  description: '',
  root: {
    type: 'InspectionPlanNode',
    properties: { name: '日常巡检', enabled: true, plan_id: 'P-001' },
    children: [{ type: 'DailyScheduleNode', properties: { start_time: '08:00' } }],
  },
}
const wrapped = ensureGroupRoot(oldSpec)
eq('6b.2 老文件（根是单条计划）会被包一层', wrapped.wrapped, true)
eq('6b.3 包出来的根是分组', wrapped.spec.root.type, 'PlanGroupNode')
eq('6b.4 分组名取文件名', wrapped.spec.root.properties.name, '日常巡检')
eq('6b.5 原计划成了分组的第一个子节点', wrapped.spec.root.children[0].type, 'InspectionPlanNode')
eq('6b.6 原计划的内容一字不动', wrapped.spec.root.children[0].properties.plan_id, 'P-001')
eq('6b.7 原计划的子树也保留', wrapped.spec.root.children[0].children[0].type, 'DailyScheduleNode')
eq('6b.8 分组默认启用', wrapped.spec.root.properties.enabled, true)
// 不能改到入参（页面还要拿它跟"改没改"比较，被就地改了就比不出来）
eq('6b.9 不就地改入参', oldSpec.root.type, 'InspectionPlanNode')
eq('6b.10 产物与入参不是同一个对象', wrapped.spec === oldSpec, false)
wrapped.spec.root.properties.name = '改过'
eq('6b.11 产物是深拷贝（改产物不污染入参）', oldSpec.root.properties.name, '日常巡检')

const groupSpec = {
  name: 'multi', root: { type: 'PlanGroupNode', properties: { name: 'multi' }, children: [] },
}
const kept = ensureGroupRoot(groupSpec)
eq('6b.12 根已经是分组时不动它', kept.wrapped, false)
eq('6b.13 根已经是分组时原样返回', kept.spec === groupSpec, true)

const bad = ensureGroupRoot({})
eq('6b.14 空 spec 不炸', bad.wrapped, false)
eq('6b.15 root 缺失时不炸', ensureGroupRoot(null).wrapped, false)
// 文件名缺失时分组名要有兜底（不许出现 undefined / 空名）
eq('6b.16 文件名缺失时分组名兜底',
  ensureGroupRoot({ root: { type: 'InspectionPlanNode', properties: {} } })
    .spec.root.properties.name, '巡检计划')

// 根是分组 -> 一个文件能放多条计划：包完再往里加第二条
const two = ensureGroupRoot(oldSpec).spec
two.root.children.push({ type: 'InspectionPlanNode', properties: { name: '夜间巡检', plan_id: 'P-002' } })
eq('6b.17 一个文件可以挂多条计划', two.root.children.length, 2)
check('6b.18 分组摘要报条数', planNodeSummary(two.root).includes('2 条计划'))

/* ============================================================ 6c. 停用变灰 */

/**
 * 造一棵：根分组 > [计划A(停用) > 航点指定, 计划B > 每日调度]。
 * 计划 A 停了 -> 它**自己**打「已停用」，它下面的航点指定也要跟着灰。
 */
const offSpec = {
  type: 'PlanGroupNode',
  properties: { name: '根', enabled: true },
  children: [
    {
      type: 'InspectionPlanNode',
      properties: { name: '计划A', enabled: false },
      children: [
        { type: 'WaypointSelectNode', properties: { name: '航点指定', enabled: true } },
      ],
    },
    {
      type: 'InspectionPlanNode',
      properties: { name: '计划B', enabled: true },
      children: [
        { type: 'DailyScheduleNode', properties: { name: '每日调度', enabled: true } },
      ],
    },
  ],
}
const { disabled, muted } = collectDisabled(offSpec)
eq('6c.1 只有自己停用的进 disabled', disabled.size, 1)
check('6c.2 停用的是计划A', disabled.has('root/children/0'))
eq('6c.3 子树一起进 muted（计划A + 它的航点指定）', muted.size, 2)
check('6c.4 被连带的子节点也在 muted 里', muted.has('root/children/0/children/0'))
check('6c.5 兄弟计划不受影响', !muted.has('root/children/1'))
check('6c.6 兄弟计划的子节点也不受影响', !muted.has('root/children/1/children/0'))
check('6c.7 根不在 muted 里', !muted.has('root'))

// 多层：停用会一路传下去（计划A > 分组 > 航点指定 三层都要灰）
const deepOff = {
  type: 'PlanGroupNode', properties: { enabled: true },
  children: [{
    type: 'InspectionPlanNode', properties: { enabled: false },
    children: [{
      type: 'PlanGroupNode', properties: { enabled: true },
      children: [{ type: 'WaypointSelectNode', properties: { enabled: true } }],
    }],
  }],
}
const d2 = collectDisabled(deepOff)
eq('6c.8 停用穿透多层', d2.muted.size, 3)
check('6c.9 最深的叶子也在 muted 里', d2.muted.has('root/children/0/children/0/children/0'))
eq('6c.10 disabled 只记自己停的那个', d2.disabled.size, 1)

// 根自己停用 -> 整棵树都灰
const rootOff = {
  type: 'PlanGroupNode', properties: { enabled: false },
  children: [{ type: 'InspectionPlanNode', properties: { enabled: true } }],
}
const d3 = collectDisabled(rootOff)
eq('6c.11 根停用时整棵树都灰', d3.muted.size, 2)
check('6c.12 根自己在 muted 里', d3.muted.has('root'))

// 老数据里可能整个 enabled 字段都没写 -> 视为启用（只有显式 false 才算停用）
const noField = {
  type: 'PlanGroupNode', properties: { name: '根' },
  children: [{ type: 'InspectionPlanNode', properties: { name: '计划' } }],
}
eq('6c.13 没写 enabled 视为启用', collectDisabled(noField).muted.size, 0)
eq('6c.14 空树不炸', collectDisabled(null).muted.size, 0)
eq('6c.15 空 root 不炸', collectDisabled({}).muted.size, 0)

/* ============================================================ 7. 源码级断言 */

const strip = (s) => s.replace(/\/\*[\s\S]*?\*\//g, '').replace(/^\s*\/\/.*$/gm, '')
const page = strip(readFileSync(join(root, 'src/views/InspectionPlanPrefab.tsx'), 'utf8'))

// 用户点名的右键菜单项，一项都不能少
for (const label of ['展开子树', '收起子树', '添加子节点', '在前添加子节点',
  '在后添加子节点', '复制节点', '剪切节点', '归入分组', '删除节点']) {
  check(`7.x 右键菜单含「${label}」`, page.includes(`'${label}'`))
}
// 复制/剪切必须配套粘贴，否则那两个菜单项是死的
check('7.x 右键菜单含「粘贴」', page.includes("'粘贴'"))
check('7.x 根节点不给"在前/后添加子节点"', /const canInsertBeside = p !== 'root'/.test(page))
check('7.x 根节点不给"删除节点"', /if \(p !== 'root'\) items\.push/.test(page))

// 结构操作必须走共用纯函数，别在本页再写一份
check('7.x 拖拽落点用 specTree.resolveDropKind', page.includes('resolveDropKind'))
check('7.x 移动用 specTree.moveNodeInSpec', page.includes('moveNodeInSpec'))
check('7.x 批量移动用 specTree.batchMoveNodes', page.includes('batchMoveNodes'))
check('7.x 删除用 specTree.removeManyByPaths', page.includes('removeManyByPaths'))
check('7.x 粘贴用 planSelect.regeneratePlanIds', page.includes('regeneratePlanIds'))
check('7.x 本页不再自写 getNodeByPath', !/function getNodeByPath/.test(page))

// 保存必须打计划树的接口，不能误调航点树那个
check('7.x 保存走 savePlanTree', page.includes('savePlanTree('))
check('7.x 不误用 saveWaypointTree', !page.includes('saveWaypointTree'))

// 三个专用面板挂在检视器的 top 插槽（是检视器的第一项）
check('7.x 检视器 top 插槽挂 PlanNodeTool', /top=\{<PlanNodeTool/.test(page))
check('7.x PlanNodeTool 按 key 重挂', /PlanNodeTool key=/.test(page))

// 两栏布局：左树 + 分隔条 + 检视器，页面本身不挂地图/视频
// （地图只在「航点指定」面板里出现，那是检视器的一部分，见 PlanNodeTools）
check('7.x 左栏是树', page.includes('className="wp3-tree"'))
check('7.x 右栏是检视器', page.includes('className="wp3-inspector"'))
check('7.x 页面本身没有地图（地图只在航点指定面板里）', !page.includes('<TrackMap'))

const tools = strip(readFileSync(join(root, 'src/components/PlanNodeTools.tsx'), 'utf8'))
check('7.x 三个面板都导出了',
  ['WaypointSelectTool', 'PointSelectTool', 'DailyScheduleTool'].every((n) => tools.includes(`function ${n}(`)))
check('7.x 航点面板读航点树接口', tools.includes('getWaypointTree'))
check('7.x 测点面板读测点档案', tools.includes('catalogApi.points'))
check('7.x 调度面板复用 scheduleSlots', tools.includes('scheduleSlots('))
// 航点面板已升级成"树视图 + 地图画布"，测点面板升级成"档案目录树 + Shift 整段选"。
// 两套挑选逻辑都在纯函数模块里（范围选、楼层回解、测点未归类、地图回写的范围合并），
// 逐条锁在 verify-pick-tree.mjs。
check('7.x 航点面板用树视图挑选', tools.includes('<PickTreeView'))
check('7.x 航点面板挂了地图画布', tools.includes('<TrackMap'))
check('7.x 航点面板的纯函数在 waypointPick', tools.includes("from '../utils/waypointPick'"))
check('7.x 测点面板的纯函数在 pointPick', tools.includes("from '../utils/pointPick'"))

// ⚠️ 两个面板**都不再**是"落数据的条目不可点、只有 Checkbox 能改选中"（算法卡片
//    那次踩过的规矩）——它们现在是树视图，整行必须可点（Shift 整段选就靠行点击）。
//    新规则（行接管点击、勾选框 pointer-events:none、两个面板共用 PickTreeView）
//    锁在 scripts/verify-pick-tree.mjs 的 5.12~5.34 里，这里不要重复断言。

// 后端：5 个节点类型都在，且都挂在 PlanNodeBase 下
const py = readFileSync(resolve(root, '../backend/app/prefab/nodes/plan.py'), 'utf8')
check('7.x 中间基类不注册', /__type_name__: ClassVar\[str \| None\] = None/.test(py))
for (const cls of ['InspectionPlanNode', 'PlanGroupNode', 'WaypointSelectNode',
  'PointSelectNode', 'DailyScheduleNode']) {
  check(`7.x 后端有 ${cls}`, new RegExp(`^class ${cls}\\(PlanNodeBase\\)`, 'm').test(py))
}
check('7.x 每日调度说明不支持跨零点', py.includes('不支持跨零点'))

// 根必须是分组（一个文件多条计划）+ 停用要看出来
check('7.x 页面用 ensureGroupRoot 归一化根', page.includes('ensureGroupRoot('))
check('7.x 归一化的结果写回 spec', /setSpec\(norm\.spec\)/.test(page))
// 包分组只是**内存里**的归一化，不能偷偷写盘（用户点保存才算数）
check('7.x 包成分组时如实提示（不静默改数据）',
  /if \(norm\.wrapped\)[\s\S]{0,200}?Toast\.info/.test(page))
check('7.x 提示里说明要保存才落盘', page.includes('保存'))
check('7.x 树行按 muted 变灰', /mutedSet\.has\(k\)/.test(page))
check('7.x 自己停用的打「已停用」标',
  /disabledSet\.has\(k\)/.test(page) && page.includes('已停用</Tag>'))
check('7.x 变灰用 collectDisabled 判定（子树连带）', page.includes('collectDisabled('))
check('7.x 空树提示说明根是分组、可放多条计划',
  page.includes('新建文件后在根节点（分组）上右键'))
check('7.x 页面导入了 PLAN_GROUP_TYPE 这套之外的归一化函数',
  /from '..\/utils\/planSelect'/.test(page) && page.includes('ensureGroupRoot'))

const planRouter = readFileSync(resolve(root, '../backend/app/routers/plan_prefab.py'), 'utf8')
check('7.x 新建计划文件的根是 PlanGroupNode',
  /"type": "PlanGroupNode"/.test(planRouter))
check('7.x 新建计划文件的根不再是 InspectionPlanNode',
  !/def _plan_root[\s\S]*?"type": "InspectionPlanNode"/.test(planRouter))
check('7.x 后端说明了"根是分组才能一个文件多条计划"',
  planRouter.includes('一个文件只能配一条计划'))
const py2 = readFileSync(resolve(root, '../backend/app/prefab/nodes/plan.py'), 'utf8')
check('7.x 计划节点文档注明不再是根', py2.includes('它**不再是根**'))
check('7.x 分组文档注明它是文件根', py2.includes('它也是计划文件的根'))

// 后端路由：两棵树的类型目录分开过滤，别把航点系混进计划树
const router = readFileSync(resolve(root, '../backend/app/routers/plan_prefab.py'), 'utf8')
check('7.x 计划路由按 PlanNodeBase 过滤', router.includes('base_filter="PlanNodeBase"'))
check('7.x 计划路由根目录是 plan', router.includes('PLAN_PREFAB_DIR'))
check('7.x 计划路由前缀', router.includes('prefix="/api/plan-prefab"'))
const store = readFileSync(resolve(root, '../backend/app/routers/prefab_store.py'), 'utf8')
// 过滤从路由搬到了 registry.schema_for_base（改用 issubclass，
// 这样隔多层的中间基类也能收进来——如 PersonIntrusionNode -> SafetyAlarmDetector
// -> DetectorNode -> DetectNodeBase）。路由只负责把 base_filter 透传下去。
check('7.x 通用工厂把 base_filter 透传给 registry',
  store.includes('registry.schema_for_base(base_filter)'))
const registry = readFileSync(resolve(root, '../backend/app/prefab/registry.py'), 'utf8')
check('7.x 类型过滤用 issubclass（支持多层中间基类）',
  /def schema_for_base\(base_name: str\)/.test(registry) && registry.includes('issubclass(cls, base_cls)'))
check('7.x 保存前先 build 校验', store.includes('registry.build(root_spec)'))
const wpr = readFileSync(resolve(root, '../backend/app/routers/waypoint_prefab.py'), 'utf8')
check('7.x 航点路由复用同一个工厂', wpr.includes('make_prefab_router('))
check('7.x 航点路由类型过滤未变', wpr.includes('base_filter="WaypointNodeBase"'))
check('7.x 航点路由没有自己再写一份 _safe_rel 全量版',
  wpr.includes('抓拍图上传用的一小段路径校验'))

/* ============================================================ 汇总 */

rmSync(out, { recursive: true, force: true })
if (fails.length) {
  console.error(`\n巡检计划编排回归：${pass} 项通过，${fails.length} 项失败`)
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
console.log(`巡检计划编排回归：${pass} 项通过，0 项失败`)
