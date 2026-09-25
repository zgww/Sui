/**
 * 巡检日志展示口径的回归（`src/api/inspectionLog.ts`）。
 *
 * 与 verify-algo-image.mjs 同一套路：**不手抄源码**，用 tsc 把真实 .ts 编到
 * 临时目录再 import —— 所以这个模块里**不能**出现 `@douyinfe/semi-*` 的 import
 * （该包在 Node 原生 ESM 下加载不了，会让脚本连编译都过不去）。颜色值返回宽
 * string，页面那边窄化。
 * 运行：node scripts/verify-inspection-log.mjs
 *
 * 锁的是那些"看着像小事、错了很难查"的地方：
 * - `passed` 是三态，None 不能被算成"未通过"（否则凭空造出异常点）；
 * - 进度在 total=0 时要给 "—" 而不是 "0%"（"没数据"和"一条没跑"是两回事）；
 * - 状态的展示文案要认得 stalled（库里的 started 不等于页面上还在跑）。
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync, readFileSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'insp-log-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath,
    [tscEntry, 'src/api/inspectionLog.ts', '--outDir', out,
      '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
      '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

// `inspectionLog.ts` 顶上有 `import http from './http'`（要发请求，绕不开）。
// 这里只验纯函数，不想把 axios + Semi 拖进来，于是就地做两件事：
//   ① 放一个同名空壳替身 http.js；
//   ② 把编译产物里那句 `from './http'` 补上 `.js`。
//      tsc 按 bundler 解析产出的都是**无扩展名**的裸相对导入，Node 原生 ESM
//      解析不了（这也是 `@douyinfe/semi-icons` 在脚本里加载不了的同一个根因）。
// **只替身 http，不替身被测函数** —— 被测的 8 个纯函数全部来自真实源码。
writeFileSync(join(out, 'http.js'),
  'export default { get: () => Promise.resolve({ data: {} }), post: () => Promise.resolve({ data: {} }) }\n')
{
  const emitted = join(out, 'inspectionLog.js')
  const patched = readFileSync(emitted, 'utf8')
    .replace(/from ['"]\.\/http['"]/g, "from './http.js'")
  writeFileSync(emitted, patched)
}

const {
  displayStatusColor, displayStatusText, dispatchText, dispatchColor,
  kindText, passedText, passedColor, progressText,
} = await import(pathToFileURL(join(out, 'inspectionLog.js')).href)

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n}${extra ? ' — ' + extra : ''}`) }

/* ============================================================
 * 1. passed 是三态 —— 这个页面最容易造出"假异常"的地方
 * ============================================================ */
{
  check('true -> 通过', passedText(true) === '通过' && passedColor(true) === 'green')
  check('false -> 未通过', passedText(false) === '未通过' && passedColor(false) === 'red')
  // 关键：null / undefined 是"还没判定"，既不是通过也不是未通过
  check('null -> 未判定（不是未通过）', passedText(null) === '未判定', passedText(null))
  check('undefined -> 未判定', passedText(undefined) === '未判定', passedText(undefined))
  check('null 的颜色是灰不是红', passedColor(null) === 'grey', passedColor(null))
  check('undefined 的颜色是灰不是红', passedColor(undefined) === 'grey', passedColor(undefined))
  // 三态互不相等（防止有人把 null 和 false 合并成一个分支）
  const texts = new Set([passedText(true), passedText(false), passedText(null)])
  check('三种结论文案互不相同', texts.size === 3, [...texts].join(' / '))
  const colors = new Set([passedColor(true), passedColor(false), passedColor(null)])
  check('三种结论颜色互不相同', colors.size === 3, [...colors].join(' / '))
}

/* ============================================================
 * 2. 进度：total 为 0 必须是 "—"，不能是 "0%"
 * ============================================================ */
{
  check('total=0 给破折号（没数据 ≠ 一条没跑）', progressText(0, 0, null) === '—',
    progressText(0, 0, null))
  check('total=0 且 pct 是 0 也给破折号', progressText(0, 0, 0) === '—')
  check('正常进度带百分比', progressText(3, 10, 30) === '3/10 (30%)', progressText(3, 10, 30))
  check('跑完显示 100%', progressText(5, 5, 100) === '5/5 (100%)')
  check('pct 为 null 但 total 有值 -> 按 0%',
    progressText(1, 4, null) === '1/4 (0%)', progressText(1, 4, null))
  check('pct 为 undefined 也不出 NaN', !progressText(1, 4, undefined).includes('NaN'))
  check('0/0 与 0/5 文案不同', progressText(0, 0, null) !== progressText(0, 5, 0))
}

/* ============================================================
 * 3. 状态文案 / 颜色 —— stalled 是展示口径，别丢掉
 * ============================================================ */
{
  check('started -> 进行中', displayStatusText('started') === '进行中')
  check('done -> 已完成', displayStatusText('done') === '已完成')
  check('failed -> 失败', displayStatusText('failed') === '失败')
  check('canceled -> 已取消', displayStatusText('canceled') === '已取消')
  check('stalled -> 疑似中断（后端加的展示态）',
    displayStatusText('stalled') === '疑似中断', displayStatusText('stalled'))
  check('stalled 有独立的颜色',
    displayStatusColor('stalled') !== displayStatusColor('started'),
    `${displayStatusColor('stalled')} vs ${displayStatusColor('started')}`)
  check('failed 是红', displayStatusColor('failed') === 'red')
  check('done 是绿', displayStatusColor('done') === 'green')
  // 认不出的状态：不能崩，也不能冒充已知状态
  check('未知状态原样显示', displayStatusText('weird') === 'weird')
  check('未知状态给灰', displayStatusColor('weird') === 'grey')
  check('空串不崩', displayStatusText('') === '未知' && displayStatusColor('') === 'grey')
}

/* ============================================================
 * 4. 分发状态：三态 + 与动作执行状态是两件事
 * ============================================================ */
{
  check('pending -> 待分发', dispatchText('pending') === '待分发')
  check('done -> 已分发', dispatchText('done') === '已分发')
  check('failed -> 分发失败', dispatchText('failed') === '分发失败')
  check('done 是绿、failed 是红、pending 是灰',
    dispatchColor('done') === 'green' && dispatchColor('failed') === 'red'
    && dispatchColor('pending') === 'grey')
  check('空分发状态显示破折号', dispatchText('') === '—')
  check('未知分发状态原样显示', dispatchText('xyz') === 'xyz')
}

/* ============================================================
 * 5. 测点来源
 * ============================================================ */
{
  check('thermometry -> 测温点', kindText('thermometry') === '测温点')
  check('detect -> 检测点', kindText('detect') === '检测点')
  check('空来源给破折号', kindText('') === '—')
}

/* ============================================================
 * 6. 前后端口径要对齐（两处都得改，别只改一边）
 * ============================================================ */
{
  const tsSrc = readFileSync(join(root, 'src', 'api', 'inspectionLog.ts'), 'utf8')
  // 纯逻辑模块不许引 Semi —— 引了脚本连编译都过不去
  check('纯逻辑模块不 import Semi',
    !/from\s+['"]@douyinfe\/semi/.test(tsSrc),
    '这个文件会被 verify 脚本 tsc 编译，Semi 在 Node ESM 下加载不了')
  // 只允许 import `./http`（唯一的外部依赖，脚本里会给它放替身）
  const badImports = (tsSrc.match(/^import .*from .*$/gm) || [])
    .filter(l => !/from\s+['"]\.\/http['"]/.test(l))
  check('静态 import 只有 ./http', badImports.length === 0, badImports.join(' | '))

  // 状态枚举必须跟后端 services/inspection_log.py 一致
  const pySrc = readFileSync(
    join(root, '..', 'backend', 'app', 'services', 'inspection_log.py'), 'utf8')
  for (const s of ['started', 'done', 'failed', 'canceled']) {
    check(`后端 RUN 状态含 ${s}`, pySrc.includes(`"${s}"`))
  }
  check('后端定义了 stalled 展示态', /stalled/.test(pySrc))
  check('后端的 STALL_HOURS 是个明确常量', /STALL_HOURS = \d+/.test(pySrc))
  // 状态 -> 桶 的映射必须显式存在（直接把 'ok' 当键会让 done 永远是 0）
  check('后端有 status -> bucket 的显式映射', /_ACTION_BUCKET = \{/.test(pySrc))

  // passed 的三态判定落在路由的测点摘要里（service 只透传原值，不在这判）
  const routerSrc = readFileSync(
    join(root, '..', 'backend', 'app', 'routers', 'inspection.py'), 'utf8')
  check('后端 passed 保留三态（is True / is False 分开判）',
    /passed is True/.test(routerSrc) && /passed is False/.test(routerSrc),
    '把 None 并进 false 就会凭空造出异常点')

  // 分页响应形状与 inspection_plans 的惯例一致
  check('列表返回 {total, items} 形状', /"total":[\s\S]{0,80}"items":/.test(routerSrc))
  check('列表按 page / page_size 分页',
    /page: Optional\[int\] = None/.test(routerSrc) && /page_size: int = Query\(/.test(routerSrc)
    && /page_size=page_size/.test(routerSrc))
  check('不传 page 时回退成裸数组（老调用方不受影响）',
    /if page is None:/.test(routerSrc) && /return items/.test(routerSrc))
  check('新表已 import 进路由',
    /InspectionActionResult/.test(routerSrc.split('from ..models import')[1]?.slice(0, 400) || ''))
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.error(`\n失败 ${fails.length} 项：`)
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
console.log('全部通过 ✓')
