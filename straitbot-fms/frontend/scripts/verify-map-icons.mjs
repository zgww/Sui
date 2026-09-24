/**
 * 地图内置图标回归测试。
 *
 * 为什么要测：
 * - 图标是**手写坐标**，写歪/写出 24×24 盒子外面，画出来就是一团糊，
 *   而 typecheck 对"坐标写错了"完全无感；
 * - 所有图形用**同一个颜色**填充，实心块上再叠同色实心块是**看不见的**
 *   （门框里画个同色的把手 = 白画）。这条只能靠人工约定 + 测试盯住形状数量；
 * - 后端 select 里存的是**中文名**，前端表里是 key + 中文名，
 *   两边一旦漂移，用户选了"消防栓"却画出一个"位置点"（还不报错）。
 *
 * 运行：node scripts/verify-map-icons.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, writeFileSync, existsSync, readFileSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'mi-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath, [tscEntry,
    'src/components/mapIcons.ts', '--outDir', out,
    '--target', 'es2020', '--module', 'es2020', '--skipLibCheck', '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

const {
  ICONS, ICON_KEYS, ICON_LABELS, ICON_GRID,
  DEFAULT_ICON_KEY, DEFAULT_ICON_COLOR, DEFAULT_ICON_SIZE, ICON_MIN_SIZE, ICON_MAX_SIZE,
  normalizeIconKey, iconOf, iconLabel, normalizeIconSize, drawIcon,
} = await import(pathToFileURL(join(out, 'mapIcons.js')).href)

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps

/* ============================================================
 * 1. 清单本身
 * ============================================================ */
{
  check('内置 20 个图标', ICONS.length === 20, `实际 ${ICONS.length}`)
  check('key 唯一', new Set(ICON_KEYS).size === ICON_KEYS.length)
  check('中文名唯一', new Set(ICON_LABELS).size === ICON_LABELS.length)
  check('key 全是小写英文', ICON_KEYS.every((k) => /^[a-z]+$/.test(k)), ICON_KEYS.join(','))
  check('中文名都不为空', ICON_LABELS.every((l) => typeof l === 'string' && l.trim().length > 0))
  for (const def of ICONS) {
    check(`${def.key} 至少有一个图形`, Array.isArray(def.shapes) && def.shapes.length > 0)
  }
  check('默认图标在清单里', ICON_KEYS.includes(DEFAULT_ICON_KEY))
}

/* ============================================================
 * 2. 所有坐标必须落在 24×24 的盒子里（写出去就画糊了）
 * ============================================================ */
{
  const EPS = 0.001
  const nums = (sh) => {
    switch (sh.t) {
      case 'rect': return [sh.x, sh.y, sh.w, sh.h]
      case 'circle': return [sh.cx, sh.cy, sh.r]
      case 'poly': return sh.pts.flat()
      case 'ring': return [sh.cx, sh.cy, sh.r, sh.w]
      case 'line': return [sh.x0, sh.y0, sh.x1, sh.y1, sh.w]
      default: return []
    }
  }
  for (const def of ICONS) {
    for (const sh of def.shapes) {
      const vs = nums(sh)
      check(`${def.key}/${sh.t} 坐标都是有限数`, vs.length > 0 && vs.every(Number.isFinite),
        JSON.stringify(sh))
      check(`${def.key}/${sh.t} 无负数`, vs.every((v) => v >= -EPS), JSON.stringify(sh))
    }
  }
  // 逐个图形的"外框"不能溢出设计网格（rect/poly 按角点，circle/ring 按圆心±半径）
  for (const def of ICONS) {
    let maxX = 0
    let maxY = 0
    for (const sh of def.shapes) {
      if (sh.t === 'rect') { maxX = Math.max(maxX, sh.x + sh.w); maxY = Math.max(maxY, sh.y + sh.h) }
      else if (sh.t === 'poly') { for (const [x, y] of sh.pts) { maxX = Math.max(maxX, x); maxY = Math.max(maxY, y) } }
      else if (sh.t === 'circle') { maxX = Math.max(maxX, sh.cx + sh.r); maxY = Math.max(maxY, sh.cy + sh.r) }
      else if (sh.t === 'ring') { maxX = Math.max(maxX, sh.cx + sh.r); maxY = Math.max(maxY, sh.cy + sh.r) }
      else if (sh.t === 'line') { maxX = Math.max(maxX, sh.x0, sh.x1); maxY = Math.max(maxY, sh.y0, sh.y1) }
    }
    check(`${def.key} 不溢出 ${ICON_GRID}×${ICON_GRID}`,
      maxX <= ICON_GRID + EPS && maxY <= ICON_GRID + EPS, `maxX=${maxX} maxY=${maxY}`)
  }
  // 尺寸必须为正（负宽高的矩形在 canvas 上是画反的，很难看出来）
  for (const def of ICONS) {
    for (const sh of def.shapes) {
      const ok = sh.t === 'rect' ? sh.w > 0 && sh.h > 0
        : sh.t === 'circle' || sh.t === 'ring' ? sh.r > 0 && sh.r + sh.r <= ICON_GRID
          : sh.t === 'line' || sh.t === 'ring' ? sh.w > 0
            : sh.t === 'poly' ? sh.pts.length >= 3
              : false
      check(`${def.key}/${sh.t} 尺寸合法`, ok, JSON.stringify(sh))
    }
  }
}

/* ============================================================
 * 3. normalizeIconKey：脏输入兜底，永不返回 undefined
 * ============================================================ */
{
  check('英文 key 原样认', normalizeIconKey('hydrant') === 'hydrant')
  check('中文名反查 key', normalizeIconKey('消防栓') === 'hydrant')
  check('大小写不敏感', normalizeIconKey('HYDRANT') === 'hydrant')
  check('首尾空格容忍', normalizeIconKey('  消防栓  ') === 'hydrant')
  check('空串 -> 默认', normalizeIconKey('') === DEFAULT_ICON_KEY)
  check('undefined -> 默认', normalizeIconKey(undefined) === DEFAULT_ICON_KEY)
  check('null -> 默认', normalizeIconKey(null) === DEFAULT_ICON_KEY)
  check('数字 -> 默认', normalizeIconKey(42) === DEFAULT_ICON_KEY)
  check('乱码 -> 默认', normalizeIconKey('不存在的图标') === DEFAULT_ICON_KEY)
  check('iconOf 永不 undefined', ICON_KEYS.every((k) => iconOf(k) && iconOf(k).shapes.length > 0))
  check('iconOf 脏值也给得出定义', iconOf('zzz').key === DEFAULT_ICON_KEY)
  check('iconLabel 中文名', iconLabel('camera') === '摄像头')
  check('iconLabel 脏值给默认名', iconLabel('zzz') === iconOf(DEFAULT_ICON_KEY).label)
}

/* ============================================================
 * 4. normalizeIconSize：夹取，别画出 0 像素或糊满屏的图标
 * ============================================================ */
{
  check('合法值原样', normalizeIconSize(30) === 30)
  check('小于下限夹到下限', normalizeIconSize(1) === ICON_MIN_SIZE)
  check('大于上限夹到上限', normalizeIconSize(999) === ICON_MAX_SIZE)
  check('0 -> 默认', normalizeIconSize(0) === DEFAULT_ICON_SIZE)
  check('负数 -> 默认', normalizeIconSize(-5) === DEFAULT_ICON_SIZE)
  check('NaN -> 默认', normalizeIconSize(NaN) === DEFAULT_ICON_SIZE)
  check('undefined -> 默认', normalizeIconSize(undefined) === DEFAULT_ICON_SIZE)
  check('默认大小在合法区间', DEFAULT_ICON_SIZE >= ICON_MIN_SIZE && DEFAULT_ICON_SIZE <= ICON_MAX_SIZE)
  check('默认颜色是合法 hex', /^#[0-9a-fA-F]{6}$/.test(DEFAULT_ICON_COLOR))
}

/* ============================================================
 * 5. drawIcon：用假 ctx 把绘制过程录下来
 * ============================================================ */
function fakeCtx() {
  const log = []
  const rec = (op) => (...a) => log.push({ op, a })
  const ctx = {
    log,
    fillStyle: '', strokeStyle: '', lineWidth: 0,
    save: rec('save'), restore: rec('restore'),
    beginPath: rec('beginPath'), closePath: rec('closePath'),
    moveTo: rec('moveTo'), lineTo: rec('lineTo'),
    arc: rec('arc'), fill: rec('fill'), stroke: rec('stroke'),
    fillRect: rec('fillRect'),
  }
  return ctx
}

{
  const ctx = fakeCtx()
  drawIcon(ctx, 'camera', 100, 200, 24, '#FF0000')
  check('drawIcon 有绘制动作', ctx.log.length > 1)
  check('drawIcon 成对 save/restore',
    ctx.log[0].op === 'save' && ctx.log[ctx.log.length - 1].op === 'restore')
  check('drawIcon 至少真的填充/描边过',
    ctx.log.some((l) => l.op === 'fill' || l.op === 'stroke' || l.op === 'fillRect'))
  check('未知图标也能画（不抛）', (() => {
    try { drawIcon(fakeCtx(), 'zzz', 0, 0, 24, '#000'); return true } catch { return false }
  })())

  // 24px 时缩放系数应为 1：设计坐标 == 屏幕坐标（偏移后）
  const s = 24 / ICON_GRID
  const ctx2 = fakeCtx()
  drawIcon(ctx2, 'pin', 100, 200, 24, '#0068FF')
  const ox = 100 - 12 * s
  const oy = 200 - 12 * s
  const firstArc = ctx2.log.find((l) => l.op === 'arc')
  check('圆心按 size 缩放并居中',
    near(firstArc.a[0], ox + 12 * s) && near(firstArc.a[1], oy + 9 * s),
    `得到 (${firstArc.a[0]}, ${firstArc.a[1]})`)

  // 放大一倍：圆心不变、半径翻倍
  const ctx3 = fakeCtx()
  drawIcon(ctx3, 'pin', 100, 200, 48, '#0068FF')
  const arc3 = ctx3.log.find((l) => l.op === 'arc')
  check('放大后圆心不动', near(arc3.a[0], 100) && near(arc3.a[1], 200 - 3 * (48 / ICON_GRID)))
  check('放大后半径翻倍', near(arc3.a[2], 6.5 * (48 / ICON_GRID)))

  // 颜色必须落到 ctx 上，否则画出来全是黑的
  const ctx4 = fakeCtx()
  drawIcon(ctx4, 'hydrant', 10, 10, 24, '#FF7D00')
  check('颜色写进了 fillStyle/strokeStyle',
    ctx4.fillStyle === '#FF7D00' && ctx4.strokeStyle === '#FF7D00',
    `${ctx4.fillStyle} / ${ctx4.strokeStyle}`)

  // 20 个图标全部能画，且不抛异常
  let allOk = true
  for (const k of ICON_KEYS) {
    try {
      const c = fakeCtx()
      drawIcon(c, k, 0, 0, 24, '#000')
      if (c.log.length < 3) allOk = false
    } catch { allOk = false }
  }
  check('20 个图标全部可绘制', allOk)
}

/* ============================================================
 * 6. 与后端 IconMarkNode 的选项必须一致
 *    （后端存中文名，前端表里有 key + 中文名，漂移了就是"选 A 画出 B"）
 * ============================================================ */
{
  const pyPath = join(root, '..', 'backend', 'app', 'prefab', 'nodes', 'waypoint.py')
  check('能读到后端节点文件', existsSync(pyPath), pyPath)
  if (existsSync(pyPath)) {
    const src = readFileSync(pyPath, 'utf8')
    // 取 IconMarkNode 类体里的 icon: ... options=[...]
    const cls = src.slice(src.indexOf('class IconMarkNode'))
    const m = /options=\[(.*?)\]/s.exec(cls)
    check('后端 IconMarkNode 有 icon options', !!m)
    if (m) {
      const opts = [...m[1].matchAll(/["']([^"']+)["']/g)].map((x) => x[1])
      check('后端选项也是 20 个', opts.length === 20, `实际 ${opts.length}`)
      check('后端选项与前端中文名完全一致',
        opts.length === ICON_LABELS.length && opts.every((o, i) => o === ICON_LABELS[i]),
        `后端 ${JSON.stringify(opts)}\n     前端 ${JSON.stringify(ICON_LABELS)}`)
      check('后端默认图标前端也认',
        /default="([^"]+)"/.test(cls.slice(0, cls.indexOf('options=')))
          ? normalizeIconKey(/default="([^"]+)"/.exec(cls.slice(0, cls.indexOf('options=')))[1]) !== DEFAULT_ICON_KEY
            || ICON_LABELS.includes(/default="([^"]+)"/.exec(cls.slice(0, cls.indexOf('options=')))[1])
          : false)
    }
  }
}

rmSync(out, { recursive: true, force: true })

console.log(`\n地图图标回归：${pass} 项通过，${fails.length} 项失败`)
if (fails.length) {
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
