/**
 * 颜色值转换回归测试（InspectorForm 的 color 控件）。
 *
 * 起因：后端 `ui_field("color", ...)` 存的是 "#FF7D00" 字符串，而 Semi 的
 * ColorPicker 的 value 必须是 `{hsva, rgba, hex}` 对象；传字符串会让
 * renderPicker 读 `currentColor.hsva.h` 崩掉——整个检视器白屏。
 * 这个崩溃只在节点里真的出现 color 字段时才暴露（区段标记是第一个）。
 *
 * 这里锁两件事：
 *   1. 各种脏输入（空 / 3 位简写 / 无 # / 非法 / 对象）都要收敛成合法 hex，绝不抛异常；
 *   2. 我们的转换口径必须和 Semi 内部**完全一致**，否则 ColorPicker 一渲染
 *      就会把颜色算回另一个值（来回跳色）。
 *
 * 第 2 点不靠手抄 Semi 源码：直接 require 它自带的 CJS 产物做交叉校验。
 *
 * 运行：node scripts/verify-color-value.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, writeFileSync, existsSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'
import { createRequire } from 'node:module'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'cv-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath, [tscEntry,
    'src/components/colorValue.ts', '--outDir', out,
    '--target', 'es2020', '--module', 'es2020', '--skipLibCheck', '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

const {
  DEFAULT_HEX, normalizeHex, hexToRgba, rgbaToHsva, toColorValue, valueToHex,
} = await import(pathToFileURL(join(out, 'colorValue.js')).href)

// Semi 的真实实现（CJS 产物），用来交叉校验口径
const require = createRequire(import.meta.url)
const semi = require('@douyinfe/semi-foundation/lib/cjs/colorPicker/utils/convert.js')

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps

/* ============================================================
 * 1. normalizeHex：脏输入必须收敛，绝不抛异常
 * ============================================================ */
{
  check('原样保留合法 6 位', normalizeHex('#FF7D00') === '#FF7D00', normalizeHex('#FF7D00'))
  check('小写也认', normalizeHex('#39c5bb') === '#39c5bb')
  check('补 # 前缀', normalizeHex('FF7D00') === '#FF7D00')
  check('3 位简写展开成 6 位', normalizeHex('#F70') === '#FF7700', normalizeHex('#F70'))
  check('3 位简写不带 # 也展开', normalizeHex('abc') === '#aabbcc', normalizeHex('abc'))
  check('8 位（带 alpha）保留', normalizeHex('#FF7D0080') === '#FF7D0080')
  check('空串 → 兜底', normalizeHex('') === DEFAULT_HEX)
  check('undefined → 兜底', normalizeHex(undefined) === DEFAULT_HEX)
  check('null → 兜底', normalizeHex(null) === DEFAULT_HEX)
  check('数字 → 兜底', normalizeHex(123) === DEFAULT_HEX)
  check('乱码 → 兜底', normalizeHex('red') === DEFAULT_HEX)
  check('3 位简写（#FF7）展开', normalizeHex('#FF7') === '#FFFF77', normalizeHex('#FF7'))
  check('4 位非法 → 兜底', normalizeHex('#FF77') === DEFAULT_HEX)
  check('5 位非法 → 兜底', normalizeHex('#FF77A') === DEFAULT_HEX)
  check('超长 hex → 兜底', normalizeHex('#FF7D00FF7D00') === DEFAULT_HEX)
  check('自定义兜底生效', normalizeHex('nonsense', '#123456') === '#123456')
  check('对象取 hex 字段', normalizeHex({ hex: '#112233' }) === '#112233')
  check('对象无 hex → 兜底', normalizeHex({}) === DEFAULT_HEX)
  check('对象 hex 非法 → 兜底', normalizeHex({ hex: 'zzz' }) === DEFAULT_HEX)
  check('首尾空格容忍', normalizeHex('  #FF7D00  ') === '#FF7D00')
}

/* ============================================================
 * 2. 与 Semi 的真实转换口径必须一致
 * ============================================================ */
{
  const hexes = [
    '#FF7D00', '#39C5BB', '#000000', '#FFFFFF', '#FF0000', '#00FF00', '#0000FF',
    '#808080', '#123456', '#ABCDEF', '#FF7D0080', '#010203',
  ]
  for (const hex of hexes) {
    const ours = hexToRgba(hex)
    const theirs = semi.hexToRgba(hex)
    const sameRgb = ours.r === theirs.r && ours.g === theirs.g && ours.b === theirs.b
    check(`rgba 与 Semi 一致 ${hex}`, sameRgb,
      `我们 ${JSON.stringify(ours)} vs Semi ${JSON.stringify(theirs)}`)
    check(`alpha 与 Semi 一致 ${hex}`, near(ours.a, theirs.a), `${ours.a} vs ${theirs.a}`)
  }

  for (const hex of hexes) {
    const rgba = hexToRgba(hex)
    const ours = rgbaToHsva(rgba)
    const theirs = semi.rgbaToHsva(rgba)
    check(`hsva 与 Semi 一致 ${hex}`,
      ours.h === theirs.h && ours.s === theirs.s && ours.v === theirs.v && near(ours.a, theirs.a),
      `我们 ${JSON.stringify(ours)} vs Semi ${JSON.stringify(theirs)}`)
  }

  // 回算一致性：Semi 的 hsva 是**取整**的（h 取整数度、s/v 取整数百分比），
  // 所以 hex→hsva→hex 本身就漂移 1 个色阶（#FF7D00 → #ff7b00），这点 Semi 自己也一样。
  // 这里不能断言"完全相等"，只能断言"我们不比 Semi 更差"：
  // 我们交给它的 hsva 回算出的 hex，必须和它自己 colorStringToValue 的结果一致。
  for (const hex of hexes.filter((h) => h.length === 7)) {
    const back = semi.hsvaToHex(toColorValue(hex).hsva)
    const semiBack = semi.hsvaToHex(semi.hexToHsva(hex)) // Semi 自己走一遍同样漂
    check(`回算与 Semi 自身一致 ${hex}`, back.toLowerCase() === semiBack.toLowerCase(),
      `我们 ${back} vs Semi ${semiBack}`)
    // 漂移必须被限制在 1~2 个色阶内，防止哪天换算口径写错却"看起来能用"
    const a = hexToRgba(hex)
    const b = hexToRgba(back)
    const drift = Math.max(Math.abs(a.r - b.r), Math.abs(a.g - b.g), Math.abs(a.b - b.b))
    check(`回算漂移 ≤2 色阶 ${hex}`, drift <= 2, `${drift}（${hex} → ${back}）`)
  }
}

/* ============================================================
 * 3. toColorValue：交给 ColorPicker 的对象必须"结构完整"
 *    （缺任一字段都会让 renderPicker 读 .h / .s / .r 时崩）
 * ============================================================ */
{
  const bad = [undefined, null, '', 'nonsense', {}, { hex: 'zz' }, 42, '#F70']
  for (const v of bad) {
    const cv = toColorValue(v)
    const ok = cv
      && cv.hsva && Number.isFinite(cv.hsva.h) && Number.isFinite(cv.hsva.s)
      && Number.isFinite(cv.hsva.v) && Number.isFinite(cv.hsva.a)
      && cv.rgba && Number.isFinite(cv.rgba.r) && Number.isFinite(cv.rgba.g)
      && Number.isFinite(cv.rgba.b) && Number.isFinite(cv.rgba.a)
      && typeof cv.hex === 'string' && cv.hex.startsWith('#')
    check(`脏输入也能产出完整对象 ${JSON.stringify(v)}`, !!ok, JSON.stringify(cv))
  }

  // 崩溃现场的原值：字符串直接当 value 传进去就是 undefined.hsva
  const cv = toColorValue('#FF7D00')
  check('区段标记默认色可渲染', cv.hex === '#FF7D00' && Number.isFinite(cv.hsva.h))
  check('默认色不是 undefined', typeof DEFAULT_HEX === 'string' && DEFAULT_HEX.startsWith('#'))
}

/* ============================================================
 * 4. valueToHex：onChange 回来的东西要收敛成字符串
 * ============================================================ */
{
  check('对象取 hex', valueToHex({ hsva: {}, rgba: {}, hex: '#112233' }) === '#112233')
  check('字符串直传', valueToHex('#AABBCC') === '#AABBCC')
  check('字符串缺 # 补上', valueToHex('AABBCC') === '#AABBCC')
  check('空对象 → 兜底', valueToHex({}) === DEFAULT_HEX)
  check('undefined → 兜底', valueToHex(undefined) === DEFAULT_HEX)
  check('自定义兜底生效', valueToHex(null, '#00FF00') === '#00FF00')
  // Semi 算出来的是小写，存回节点后下一次渲染必须还能认
  check('小写 hex 可二次渲染', toColorValue(valueToHex({ hex: '#ff7d00' })).hex === '#ff7d00')
}

/* ============================================================
 * 5. 存 → 渲染 → 存 的往返稳定性
 * ============================================================ */
{
  const stored = '#FF7D00'
  const round = valueToHex(toColorValue(stored))
  check('往返不丢色', round.toLowerCase() === stored.toLowerCase(), round)
  const twice = valueToHex(toColorValue(round))
  check('往返幂等', twice === round, `${twice} vs ${round}`)
}

rmSync(out, { recursive: true, force: true })

console.log(`\n颜色值转换回归：${pass} 项通过，${fails.length} 项失败`)
if (fails.length) {
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
