/**
 * Prefab 目录树显示名与图标归属回归。
 *
 * 两件事都在页面上改过一次就踩一次，所以锁在纯函数里：
 *  1. 文件名要显示**全名**（带 `.prefab.json`）。裁掉后缀会让 `a.json` 与
 *     `a.prefab.json` 在树上显示成两行一模一样的 `a`。
 *  2. 目录图标只按相对路径的**第一段**认（`waypoint/楼层1` 也用航点树图标）。
 *
 * 关键：**不从源码手抄函数**，用 tsc 把真实 .ts 编译到临时目录再 import。
 * 运行：node scripts/verify-prefab-dir-label.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, existsSync, writeFileSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const frontendRoot = resolve(here, '..')
const tscEntry = join(frontendRoot, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}

function compile(relTs) {
  const outDir = mkdtempSync(join(tmpdir(), 'pdl-'))
  try {
    execFileSync(
      process.execPath,
      [tscEntry, relTs, '--outDir', outDir,
        '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
        '--moduleResolution', 'bundler'],
      { cwd: frontendRoot, stdio: 'pipe' },
    )
  } catch (e) {
    console.error(`编译 ${relTs} 失败：\n`, e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
    process.exit(1)
  }
  writeFileSync(join(outDir, 'package.json'), JSON.stringify({ type: 'module' }))
  const name = relTs.split('/').pop().replace(/\.tsx?$/, '.js')
  return import(pathToFileURL(join(outDir, name)).href)
}

const mod = await compile('src/utils/prefabDirLabel.ts')
const {
  DIR_ICON_KEY, DIR_ICON_FALLBACK,
  dirIconKey, fileDisplayName, dirDisplayName, fileRelPath,
} = mod

/* ---- 断言 ---- */

let pass = 0
const failures = []
function check(name, cond, extra = '') {
  if (cond) { pass++; return }
  failures.push(`${name} ${extra}`)
}

/* ============ 1. fileDisplayName：全名 + 后缀必须保住 ============ */

check('文件名带 .prefab.json 后缀（本次改动的核心）',
  fileDisplayName('waypoint/tree.prefab.json') === 'tree.prefab.json')
check('根目录文件名带后缀',
  fileDisplayName('tree.prefab.json') === 'tree.prefab.json')
check('多层目录取最后一段',
  fileDisplayName('x/y/z.prefab.json') === 'z.prefab.json')
check('反斜杠也认（Windows 手改过的数据）',
  fileDisplayName('x\\y\\z.prefab.json') === 'z.prefab.json')

/* 关键：同名不同后缀必须区分得开——裁后缀时这两行显示成同一个 "a" */
check('a.prefab.json 与 a.json 显示名不同',
  fileDisplayName('d/a.prefab.json') !== fileDisplayName('d/a.json'),
  `${fileDisplayName('d/a.prefab.json')} vs ${fileDisplayName('d/a.json')}`)
check('a.prefab.json 保留后缀', fileDisplayName('d/a.prefab.json') === 'a.prefab.json')
check('a.json 原样', fileDisplayName('d/a.json') === 'a.json')

/* 退化输入不炸（一条脏数据不该让整棵树渲染不出来） */
check('空串返回空串', fileDisplayName('') === '')
check('null 返回空串', fileDisplayName(null) === '')
check('undefined 返回空串', fileDisplayName(undefined) === '')
check('非字符串不炸', fileDisplayName(123) === '123')
check('末尾斜杠往上找一段', fileDisplayName('a/b/') === 'b')
check('纯斜杠返回空串', fileDisplayName('///') === '')

/* 目录显示名走同一条规则 */
check('目录名不带后缀照常', dirDisplayName('waypoint/楼层1') === '楼层1')
check('根目录为空', dirDisplayName('') === '')

/* ============ 2. fileRelPath：兜底口径只有一处 ============ */

check('后端给了 rel_path 就用它', fileRelPath({ rel_path: 'x/y.prefab.json', name: 'y' }) === 'x/y.prefab.json')
check('没给 rel_path 时由 name 拼后缀', fileRelPath({ name: 'y' }) === 'y.prefab.json')
check('空对象给空串', fileRelPath({}) === '')
check('null 给空串', fileRelPath(null) === '')
check('undefined 给空串', fileRelPath(undefined) === '')
check('rel_path 为空串时回落 name', fileRelPath({ rel_path: '', name: 'y' }) === 'y.prefab.json')
check('rel_path 兜底结果能直接喂 fileDisplayName',
  fileDisplayName(fileRelPath({ name: 'y' })) === 'y.prefab.json')

/* ============ 3. dirIconKey：只认第一段 ============ */

check('启动 目录有专属图标', dirIconKey('启动') !== DIR_ICON_FALLBACK)
check('waypoint 有专属图标', dirIconKey('waypoint') !== DIR_ICON_FALLBACK)
check('plan 有专属图标', dirIconKey('plan') !== DIR_ICON_FALLBACK)
check('检测算法 有专属图标', dirIconKey('检测算法') !== DIR_ICON_FALLBACK)

/* 关键：子目录跟父目录同一个图标，不能因为多一层就回落 */
check('waypoint/楼层1 与 waypoint 同图标',
  dirIconKey('waypoint/楼层1') === dirIconKey('waypoint'))
check('plan/2026Q3 与 plan 同图标', dirIconKey('plan/2026Q3') === dirIconKey('plan'))
check('多层也认', dirIconKey('waypoint/a/b/c') === dirIconKey('waypoint'))

/* 认不出来回落，不抛 */
check('未知目录回落文件夹', dirIconKey('whatever') === DIR_ICON_FALLBACK)
check('空串回落文件夹', dirIconKey('') === DIR_ICON_FALLBACK)
check('null 回落文件夹', dirIconKey(null) === DIR_ICON_FALLBACK)
check('undefined 回落文件夹', dirIconKey(undefined) === DIR_ICON_FALLBACK)

/* 反斜杠归一化后照样认得出 */
check('反斜杠路径也认第一段', dirIconKey('waypoint\\楼层1') === dirIconKey('waypoint'))

/* 表里每个键都能映射到图标组件（页面侧表不含空值） */
check('图标键表非空', Object.keys(DIR_ICON_KEY).length >= 4,
  `${Object.keys(DIR_ICON_KEY).length}`)
check('每个目录都给了图标键',
  Object.values(DIR_ICON_KEY).every((v) => typeof v === 'string' && v.length > 0))
check('回落键有定义', DIR_ICON_FALLBACK === 'folder')

/* 与 config.DATA_PREFAB_SUBDIRS 对齐：三个数据目录名都在表里 */
for (const d of ['waypoint', 'plan', '检测算法']) {
  check(`数据目录 ${d} 在图标表里`, Object.prototype.hasOwnProperty.call(DIR_ICON_KEY, d))
}

/* ---- 结果 ---- */
console.log(`\nPrefab 目录树显示名 / 图标回归：${pass} 项通过，${failures.length} 项失败`)
if (failures.length) {
  for (const f of failures) console.log('  ✗', f)
  process.exit(1)
}
console.log('全部通过 ✓')
