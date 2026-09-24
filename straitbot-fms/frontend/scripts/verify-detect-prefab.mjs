/**
 * 检测流程编排的回归测试。
 *
 * 与 `verify-plan-prefab.mjs` 同一套路，锁两件事：
 * 1. **纯函数**（`utils/detectSelect.ts`）——类型中文名、树上那句摘要、粘贴换
 *    检测编号。这些错了不会报错，只会"看错"（节流参数看不出来、粘贴出两条
 *    同编号流程），必须能算。
 * 2. **源码级断言**（`views/DetectPrefab.tsx` + 后端节点/路由模块）——
 *    三棵树的类型目录必须分开、检测流程树不能进规则 runtime 这类约定，
 *    删掉不会有任何类型错误，只能在这里锁。
 *
 * **不手抄源码**：用 tsc 把真实 .ts 编到临时目录再 import。
 * 运行：node scripts/verify-detect-prefab.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync, readFileSync, readdirSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'detectpf-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath,
    [tscEntry, 'src/utils/detectSelect.ts', '--outDir', out,
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

const modPath = ['utils/detectSelect.js', 'detectSelect.js']
  .map((p) => join(out, p)).find((p) => existsSync(p))
if (!modPath) {
  console.error('编译产物里找不到 detectSelect.js：', out)
  process.exit(1)
}
const D = await import(pathToFileURL(modPath).href)
const {
  detectTypeLabel, detectNodeSummary, regenerateDetectIds, DETECT_TYPE_COLOR,
  isDetectorNode, ALGORITHM_NODE_TYPES,
} = D

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const eq = (n, got, want) => check(n, got === want, `got=${JSON.stringify(got)} want=${JSON.stringify(want)}`)

/* ============================================================ 1. 类型中文名 */

eq('1.1 根节点', detectTypeLabel('DetectPipelineNode'), '检测流程')
// 算法节点**逐一登记**（没有通用的 DetectorNode——每种算法一个子类，
// 见后端 nodes/algorithms.py；这里顺带锁住"别退化成通用节点"）
eq('1.2 算法节点（状态识别）', detectTypeLabel('SwitchStateNode'), '开关分合状态')
eq('1.3 算法节点（表计读数）', detectTypeLabel('MeterDigitalNode'), '数字表读数')
eq('1.4 算法节点（缺陷检测）', detectTypeLabel('InsulatorDamageNode'), '绝缘子破损')
eq('1.5 算法节点（安全告警）', detectTypeLabel('SmokeFireNode'), '烟雾火焰')
eq('1.6 前处理', detectTypeLabel('FrameSourceNode'), '取帧源')
eq('1.7 后处理', detectTypeLabel('SmsNotifyNode'), '短信通知')
eq('1.8 未登记的类型原样返回（不显示成 undefined）',
  detectTypeLabel('FooNode'), 'FooNode')
check('1.9 空输入给"未命名节点"', detectTypeLabel('') === '未命名节点')
check('1.10 每个类型都有配色', Object.values(DETECT_TYPE_COLOR ?? {}).length > 0)

/* 算法节点判定：逐个登记的类型才算，通用 DetectorNode 不算 */
check('1.11 算法节点判定认子类', isDetectorNode('SwitchStateNode') === true)
check('1.12 通用 DetectorNode 不再算算法节点（已废弃）',
  isDetectorNode('DetectorNode') === false)
check('1.13 非算法节点不算', isDetectorNode('FrameSourceNode') === false)
check('1.14 空值不炸', isDetectorNode('') === false && isDetectorNode(undefined) === false)
check('1.15 算法节点集合与中文名表同源',
  ALGORITHM_NODE_TYPES.size === 16, `${ALGORITHM_NODE_TYPES.size}`)
// MeterAlgorithmNode 不在 ALGORITHM_NODE_TEXT 里（它不是 algorithms.json 的算法，
// 是"一个节点 + 算法下拉"对接现有推理服务），但中文名必须单独补上，
// 否则类型选择器里显示裸英文。
eq('1.16 通用算法节点（推理服务）', detectTypeLabel('MeterAlgorithmNode'), '通用算法（推理服务）')
check('1.17 它不算"逐个登记的算法子类"（摘要/配色走单独分支）',
  isDetectorNode('MeterAlgorithmNode') === false)

/* ============================================================ 2. 树上摘要 */
/* 口径：detectNodeSummary(type, props) —— 两个参数，不是 (node) */

eq('2.1 流程：只给场景',
  detectNodeSummary('DetectPipelineNode', { scene: '配电室' }), '场景：配电室')
eq('2.2 流程：需人工确认',
  detectNodeSummary('DetectPipelineNode', { manual_confirm: true }), '需人工确认')
eq('2.3 流程：两者都有，用 · 拼',
  detectNodeSummary('DetectPipelineNode', { scene: '配电室', manual_confirm: true }),
  '场景：配电室 · 需人工确认')
eq('2.4 流程：都没有则空串',
  detectNodeSummary('DetectPipelineNode', {}), '')
eq('2.5 抽帧=1 是"每帧"',
  detectNodeSummary('FrameSkipNode', { every_n: 1 }), '每帧')
eq('2.6 抽帧=5 是"隔 4 帧"',
  detectNodeSummary('FrameSkipNode', { every_n: 5 }), '隔 4 帧')
eq('2.7 抽帧：限流模式',
  detectNodeSummary('FrameSkipNode', { mode: 'fps', fps: 2 }), '限流 2 帧/秒')
eq('2.8 抽帧：间隔模式',
  detectNodeSummary('FrameSkipNode', { mode: 'interval', interval_seconds: 10 }), '每 10 秒一帧')
eq('2.9 算法：只给阈值',
  detectNodeSummary('SwitchStateNode', { threshold: 0.6 }), '阈值 0.6')
eq('2.10 算法：阈值 + 期望状态',
  detectNodeSummary('SwitchStateNode', { threshold: 0.6, expected_state: '分闸' }),
  '阈值 0.6 · 期望 分闸')
eq('2.11 算法：类别标签 + 上限',
  detectNodeSummary('SmokeFireNode', { threshold: 0.5, labels: ['smoke', 'fire'], max_results: 3 }),
  '阈值 0.5 · smoke/fire · 最多 3')
eq('2.12 算法：量程 + 小数位',
  detectNodeSummary('MeterDigitalNode', { unit: 'kV', range_min: 0, range_max: 10, decimals: 2 }),
  '单位 kV · 量程 0~10 · 2位小数')
check('2.13 结果过滤：置信度',
  detectNodeSummary('ResultFilterNode', { min_confidence: 0.5 }) === '置信度≥0.5')
check('2.14 结果过滤：每帧上限 + 排除',
  detectNodeSummary('ResultFilterNode', { max_per_frame: 3, exclude_labels: ['a'] })
    === '每帧≤3 · 排除 a')
check('2.15 告警：级别 + 去重窗口',
  detectNodeSummary('AlarmNode', { level: '严重告警', dedup_seconds: 300 })
    === '严重告警 · 去重 300s')
check('2.16 短信：号码数 + 等级门槛',
  detectNodeSummary('SmsNotifyNode', { phones: ['138', '139'], min_level: '严重告警' })
    === '2 个号码 · 等级≥严重告警')
check('2.17 邮件：收件人数 + 等级门槛',
  detectNodeSummary('EmailNotifyNode', { emails: ['a@b.c'], min_level: '一般告警' })
    === '1 个收件人 · 等级≥一般告警')
check('2.18 生效时段：未设 = 全天',
  detectNodeSummary('TimeWindowNode', {}) === '未设时段（全天）')
check('2.19 生效时段：有窗口时拼 星期 + 起止',
  detectNodeSummary('TimeWindowNode',
    { enabled_windows: [{ days: [1, 2, 3], start: '08:00', end: '18:00' }] })
    === '123 08:00-18:00')
check('2.20 存证：存图 + 保留天数',
  detectNodeSummary('EvidenceNode', { save_image: true, storage_days: 30 })
    === '存图 · 保留 30 天')
check('2.21 未知类型给空串（不是 undefined）',
  detectNodeSummary('FooNode', {}) === '')
check('2.22 props 缺失不炸', typeof detectNodeSummary('EvidenceNode', undefined) === 'string')

/* MeterAlgorithmNode 的阈值/其他参数已下线（后端 __hidden_fields__），
   摘要里**不能**再出现「阈值 x」——那是 isDetectorNode 那条分支的第一句。
   老 prefab 里残留的 threshold 也不能被摘要捡起来。 */
eq('2.23 通用算法节点：残留阈值不进摘要',
  detectNodeSummary('MeterAlgorithmNode', { threshold: 0.6, panel_algorithm: '0_0_0_4010_0_0' }), '')
eq('2.24 通用算法节点：保留的类别 + 上限仍显示',
  detectNodeSummary('MeterAlgorithmNode', { threshold: 0.6, labels: ['吸烟'], max_results: 2 }),
  '吸烟 · 最多 2')

/* ============================================================ 3. 粘贴换编号 */
/* 检测树目前**没有实例级业务编号**（节点靠树路径定位，camera_id/zone_ids/topic
   都是外部引用必须照抄），所以 regenerateDetectIds 只递归、恒返回 0。
   这组断言锁的是"别误以为它换了编号"，也锁住将来真加编号时这里会先红。 */

const tree = {
  type: 'DetectPipelineNode',
  properties: { detect_id: 'D-1' },
  children: [{ type: 'AlarmNode', properties: { level: '严重' } }],
}
eq('3.1 当前不换编号（返回 0 是设计如此）', regenerateDetectIds(tree), 0)
check('3.2 原编号纹丝不动', tree.properties.detect_id === 'D-1')
eq('3.3 子树递归也不计数', regenerateDetectIds(tree.children[0]), 0)
eq('3.4 空输入不炸', regenerateDetectIds(undefined), 0)
eq('3.5 null 不炸', regenerateDetectIds(null), 0)
eq('3.6 非对象不炸', regenerateDetectIds('x'), 0)
const a = { type: 'DetectPipelineNode', properties: { detect_id: 'D-1' } }
const b = { type: 'DetectPipelineNode', properties: { detect_id: 'D-1' } }
regenerateDetectIds(a); regenerateDetectIds(b)
check('3.7 两次"粘贴"后编号仍相同（因为压根没换）',
  a.properties.detect_id === b.properties.detect_id)

/* ============================================================ 4. 源码级断言 */

const view = readFileSync(resolve(root, 'src/views/DetectPrefab.tsx'), 'utf8')
check('4.1 走检测流程专用 API', view.includes("/api/detect-prefab") || view.includes('detectPrefab'))
check('4.2 拉的是本棵树的 node-types', view.includes('getDetectNodeTypes'))
check('4.3 算法下拉用 optionsFrom 数据源', view.includes('optionSources'))
check('4.4 停用的子树一起灰（复用通用 collectDisabled）', view.includes('collectDisabled'))
check('4.5 归入分组建的是 DetectGroupNode', view.includes("type: 'DetectGroupNode'"))
check('4.6 粘贴换检测编号', view.includes('regenerateDetectIds'))
check('4.7 保存走 spec 键', view.includes('saveDetectTree'))

const nodesPy = readFileSync(resolve(root, '../backend/app/prefab/nodes/detect.py'), 'utf8')
check('4.8 中间基类不注册', nodesPy.includes('__type_name__: ClassVar[str | None] = None'))
check('4.9 有前处理节点', /class ThrottleNode\(DetectNodeBase\)/.test(nodesPy))
check('4.10 有算法检测节点', /class DetectorNode\(DetectNodeBase\)/.test(nodesPy))
check('4.11 有后处理节点（告警/转发/短信/邮件）',
  ['AlarmNode', 'ForwardNode', 'SmsNotifyNode', 'EmailNotifyNode']
    .every((n) => new RegExp(`class ${n}\\(DetectNodeBase\\)`).test(nodesPy)))
// 算法目录由**航点树**的 nodes/waypoint.py 提供（三处共用同一份 algorithms.json），
// 检测流程这边只有算法子类，`optionsFrom="algorithms"` 不在 detect.py 里
const wpPyForAlgo = readFileSync(resolve(root, '../backend/app/prefab/nodes/waypoint.py'), 'utf8')
check('4.12 算法下拉不写死选项', wpPyForAlgo.includes('optionsFrom="algorithms"'))
check('4.13 取帧不写死通道号', !/channel\s*[:=]/.test(nodesPy))

const routerPy = readFileSync(resolve(root, '../backend/app/routers/detect_prefab.py'), 'utf8')
check('4.14 路由前缀', routerPy.includes('prefix="/api/detect-prefab"'))
check('4.15 类型过滤按 DetectNodeBase', routerPy.includes('base_filter="DetectNodeBase"'))
check('4.16 根是检测流程节点', routerPy.includes('"type": "DetectPipelineNode"'))
check('4.17 算法目录与航点树同一份', routerPy.includes('read_algorithms'))

const prefabPy = readFileSync(resolve(root, '../backend/app/routers/prefab.py'), 'utf8')
// 启动时**只遍历启动目录** `data/prefab/启动`：编排数据、告警模板、示例都不会
// 被悄悄激活（以前靠排除名单维护，漏一个就是一棵被跑起来的树）
check('4.18 启动时只遍历启动目录', prefabPy.includes('PrefabLoader(BOOT_PREFAB_DIR)'))
const cfgPy = readFileSync(resolve(root, '../backend/app/config.py'), 'utf8')
check('4.19 配置里有独立目录常量', cfgPy.includes('DETECT_PREFAB_DIR'))
check('4.20 启动即建目录', /BOOT_PREFAB_DIR\)/.test(cfgPy))
check('4.21 启动目录是独立常量', cfgPy.includes('BOOT_PREFAB_DIR = PREFAB_DIR / "启动"'))
// ⚠️ 启动目录**只管启动时加载谁**，编排页照样要列出 data/prefabs 下全部文件
// （用户明确纠正过：不能因为不加载就不显示，那就点不开也编不了）
check('4.22 编排页扫全目录', prefabPy.includes('_scan_all_trees')
  && prefabPy.includes('os.walk(PREFAB_DIR)'))
check('4.23 文件 CRUD 的根仍是整个 prefabs', prefabPy.includes('p = PREFAB_DIR / rel'))

/* ---- 4.3 检测框引用检测流程（只存引用，不抄流程内容） ---- */
const wpPy = readFileSync(resolve(root, '../backend/app/prefab/nodes/waypoint.py'), 'utf8')
check('4.24 检测框有 detect_flow 字段', /detect_flow: str = ui_field/.test(wpPy))
const boxTool = readFileSync(resolve(root, 'src/components/DetectBoxTool.tsx'), 'utf8')
check('4.25 检测框项带 detectFlow', boxTool.includes('detectFlow: string'))
check('4.26 下拉走 onSetDetectFlow', boxTool.includes('onSetDetectFlow'))
check('4.27 引用了但流程文件不在列表里时不丢值（补一项提示）',
  boxTool.includes('流程已不存在'))
const wpView = readFileSync(resolve(root, 'src/views/WaypointTreePrefab.tsx'), 'utf8')
check('4.28 航点页拉检测流程目录', wpView.includes('listDetectTrees'))
check('4.29 写的是 detect_flow 一个字段', wpView.includes("detect_flow: rel"))
check('4.30 下拉的 value 就是相对路径', wpView.includes('value: t.rel_path'))

/* ============================================================ 5. 告警细分与级别 */

// 告警不只是"命中就报"：数值类要跟阈值 / 区间比，判据不同所以单独成节点
eq('5.1 数值告警', detectTypeLabel('NumericAlarmNode'), '数值告警')
eq('5.2 数值范围告警', detectTypeLabel('RangeAlarmNode'), '数值范围告警')
eq('5.3 事件告警（原告警节点）', detectTypeLabel('AlarmNode'), '事件告警')
check('5.4 两个数值告警节点已定义',
  /class NumericAlarmNode\(DetectNodeBase\)/.test(nodesPy)
  && /class RangeAlarmNode\(DetectNodeBase\)/.test(nodesPy))
check('5.5 数值告警有比较符与阈值',
  /op: Literal\[/.test(nodesPy) && /threshold: float/.test(nodesPy))
check('5.6 数值告警有回差（防阈值附近抖动刷屏）', nodesPy.includes('hysteresis'))
check('5.7 范围告警有上下限与模式',
  /min_value: float/.test(nodesPy) && /max_value: float/.test(nodesPy)
  && nodesPy.includes('区间内告警'))

// 四级告警：预警 < 一般告警 < 严重告警 < 危急告警
check('5.8 后端四级告警', nodesPy.includes('"预警", "一般告警", "严重告警", "危急告警"'))
const pipelinePy = readFileSync(resolve(root, '../backend/app/prefab/detect_pipeline.py'), 'utf8')
check('5.9 执行侧级别与节点定义一致（否则比大小会错）',
  pipelinePy.includes('("预警", "一般告警", "严重告警", "危急告警")'))
check('5.10 数值判据在执行侧', pipelinePy.includes('def numeric_alarm_hit')
  && pipelinePy.includes('def range_alarm_hit'))
check('5.11 事件没带数值时不拿 0 顶替', pipelinePy.includes('没带数值'))
check('5.12 上下限填反不报（宁可漏报也不全判越界）', pipelinePy.includes('配反'))
check('5.13 前端摘要认得数值告警',
  readFileSync(resolve(root, 'src/utils/detectSelect.ts'), 'utf8')
    .includes("case 'NumericAlarmNode'"))

/* MeterAlgorithmNode 只负责"把框交给推理服务"，不做筛选（2026-09-24 定）：
   阈值 / 其他参数 / 只读算法镜像从检视器下线，只留类别 + 最多结果数。 */
check('5.14 通用算法节点声明了下线字段',
  /class MeterAlgorithmNode\(DetectorNode\)/.test(nodesPy)
  && nodesPy.includes('__hidden_fields__: ClassVar[tuple[str, ...]] = ("algorithm", "threshold", "params")'))
check('5.15 下线的阈值不再参与置信度闸门',
  nodesPy.includes('__threshold_gate__: ClassVar[bool] = False')
  && pipelinePy.includes('_NO_THRESHOLD_GATE_TYPES'))
check('5.16 下线机制是"不下发"而不是"删字段"（删了存量 prefab 会打不开）',
  readFileSync(resolve(root, '../backend/app/prefab/base.py'), 'utf8')
    .includes('__hidden_fields__')
  && readFileSync(resolve(root, '../backend/app/prefab/registry.py'), 'utf8')
    .includes('def _visible_schema'))

// 数值告警的判据来自**测点识别结果的 parameter**（不是按算法名字猜）
const alarmPy = readFileSync(resolve(root, '../backend/app/services/alarm_processor.py'), 'utf8')
check('5.17 数值从结果框的 parameter 取',
  alarmPy.includes('def _read_value') && alarmPy.includes('rb.get("parameter")'))
check('5.18 🔴 不再按 name 的 0_ 前缀判"无读数"（panel_list 里 37/63 个算法以 0_ 开头，'
  + '含电流表_中_* / 电压表_中_*，判断一错数值告警永不触发）',
  !alarmPy.includes('startswith("0_")'))

/* ============================================================ 汇总 */

rmSync(out, { recursive: true, force: true })
if (fails.length) {
  console.error(`\n检测流程编排回归：${pass} 项通过，${fails.length} 项失败`)
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
console.log(`检测流程编排回归：${pass} 项通过，0 项失败`)
