/**
 * 2D 视口（缩放/平移）回归测试。
 *
 * 缩放锚点是最容易写错的地方：一旦算错，滚轮缩放时视图会"跑偏"——
 * 用户明明把鼠标放在某个航点上缩放，那个航点却往旁边溜走。
 * 这里用**不变量**来锁：锚点下的世界坐标在缩放前后必须完全不变。
 *
 * 运行：node scripts/verify-viewport.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, writeFileSync, existsSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'vp-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath, [tscEntry,
    'src/components/trackGeometry.ts', '--outDir', out,
    '--target', 'es2020', '--module', 'es2020', '--skipLibCheck', '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

const g = await import(pathToFileURL(join(out, 'trackGeometry.js')).href)
const {
  worldToScreen, screenToWorld, panBy, zoomAt, fitViewport, boundsOf,
  pixelTolerance, niceStep, MIN_SCALE, MAX_SCALE,
} = g

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps

/* ============================================================
 * 1. 正逆变换必须互逆
 * ============================================================ */
{
  const vp = { scale: 2.5, offset: { x: 40, y: 30 } }
  for (const p of [{ x: 0, y: 0 }, { x: 1000, y: 250 }, { x: -300, y: -80 }]) {
    const back = screenToWorld(vp, worldToScreen(vp, p))
    check(`正逆变换互逆 (${p.x},${p.y})`, near(back.x, p.x, 1e-9) && near(back.y, p.y, 1e-9),
      `得到 (${back.x}, ${back.y})`)
  }
  // offset 就是世界原点在屏幕上的位置
  const o = worldToScreen(vp, { x: 0, y: 0 })
  check('世界原点映射到 offset', near(o.x, 40) && near(o.y, 30))
}

/* ============================================================
 * 2. 缩放锚点不变量（核心）
 * ============================================================ */
{
  const vp = { scale: 1, offset: { x: 0, y: 0 } }
  let bad = 0
  const details = []
  // 在屏幕上多个位置、多种倍率下反复缩放，锚点世界坐标都不该动
  for (const anchor of [{ x: 0, y: 0 }, { x: 100, y: 50 }, { x: 400, y: 180 }, { x: 800, y: 300 }]) {
    for (const factor of [1.1, 0.9, 1.5, 0.5, 2, 0.8]) {
      let v = { ...vp, offset: { ...vp.offset } }
      const before = screenToWorld(v, anchor)
      v = zoomAt(v, anchor, factor)
      const after = screenToWorld(v, anchor)
      if (!near(before.x, after.x, 1e-6) || !near(before.y, after.y, 1e-6)) {
        bad++
        details.push(`anchor(${anchor.x},${anchor.y}) f=${factor}: (${before.x.toFixed(3)},${before.y.toFixed(3)}) -> (${after.x.toFixed(3)},${after.y.toFixed(3)})`)
      }
    }
  }
  check('缩放时锚点下的世界坐标不变', bad === 0,
    `${bad} 例漂移；样例：${details.slice(0, 2).join(' | ')}`)

  // 连续缩放后再缩回来应回到原位（近似可逆）
  let v = { scale: 1, offset: { x: 33, y: 77 } }
  const anchor = { x: 250, y: 120 }
  const start = screenToWorld(v, anchor)
  for (let i = 0; i < 10; i++) v = zoomAt(v, anchor, 1.2)
  for (let i = 0; i < 10; i++) v = zoomAt(v, anchor, 1 / 1.2)
  check('放大再缩回，scale 复原', near(v.scale, 1, 1e-9), `scale=${v.scale}`)
  const end = screenToWorld(v, anchor)
  check('放大再缩回，锚点世界坐标复原',
    near(start.x, end.x, 1e-6) && near(start.y, end.y, 1e-6),
    `(${start.x},${start.y}) vs (${end.x},${end.y})`)
}

/* ============================================================
 * 3. 缩放上下限
 * ============================================================ */
{
  let v = { scale: 1, offset: { x: 0, y: 0 } }
  const a = { x: 100, y: 100 }
  for (let i = 0; i < 100; i++) v = zoomAt(v, a, 2)
  check('放大被 MAX_SCALE 限制', near(v.scale, MAX_SCALE), `scale=${v.scale}`)
  for (let i = 0; i < 200; i++) v = zoomAt(v, a, 0.5)
  check('缩小被 MIN_SCALE 限制', near(v.scale, MIN_SCALE), `scale=${v.scale}`)

  // 顶到边界后不应产生漂移（提前返回）
  const atMax = zoomAt({ scale: MAX_SCALE, offset: { x: 5, y: 6 } }, a, 2)
  check('已达上限时视口原样返回',
    atMax.scale === MAX_SCALE && atMax.offset.x === 5 && atMax.offset.y === 6)
  const atMin = zoomAt({ scale: MIN_SCALE, offset: { x: 5, y: 6 } }, a, 0.5)
  check('已达下限时视口原样返回',
    atMin.scale === MIN_SCALE && atMin.offset.x === 5 && atMin.offset.y === 6)

  // 非法倍率不能产生 NaN
  const nan = zoomAt({ scale: 1, offset: { x: 0, y: 0 } }, a, NaN)
  check('NaN 倍率不产生 NaN 视口',
    Number.isFinite(nan.scale) && Number.isFinite(nan.offset.x))
}

/* ============================================================
 * 4. 平移
 * ============================================================ */
{
  const vp = { scale: 3, offset: { x: 10, y: 20 } }
  const p = panBy(vp, 50, -30)
  check('平移累加到 offset', p.offset.x === 60 && p.offset.y === -10)
  check('平移不改 scale', p.scale === 3)
  // 平移 N 像素 = 世界坐标反向移动 N/scale
  const w0 = screenToWorld(vp, { x: 100, y: 100 })
  const w1 = screenToWorld(p, { x: 150, y: 70 })
  check('平移与屏幕位移一致',
    near(w1.x, w0.x, 1e-9) && near(w1.y, w0.y, 1e-9),
    `(${w0.x},${w0.y}) vs (${w1.x},${w1.y})`)
}

/* ============================================================
 * 5. fitViewport：把包围盒装进视口
 * ============================================================ */
{
  const size = { w: 800, h: 400 }
  const b = { x: 0, y: -100, w: 1000, h: 200 }
  const vp = fitViewport(b, size, 40)
  // 包围盒四角必须都落在视口内（含边距）
  const corners = [
    { x: b.x, y: b.y },
    { x: b.x + b.w, y: b.y + b.h },
  ]
  const sc = corners.map((c) => worldToScreen(vp, c))
  check('fit 后包围盒在横向视口内',
    sc[0].x >= 39.5 && sc[1].x <= size.w - 39.5,
    `x: ${sc[0].x.toFixed(1)} ~ ${sc[1].x.toFixed(1)}`)
  check('fit 后包围盒在纵向视口内',
    Math.min(sc[0].y, sc[1].y) >= 39.5 && Math.max(sc[0].y, sc[1].y) <= size.h - 39.5,
    `y: ${sc[0].y.toFixed(1)} ~ ${sc[1].y.toFixed(1)}`)
  // 居中：包围盒中心映射到画布中心
  const mid = worldToScreen(vp, { x: b.x + b.w / 2, y: b.y + b.h / 2 })
  check('fit 后包围盒居中', near(mid.x, size.w / 2, 1e-6) && near(mid.y, size.h / 2, 1e-6),
    `中心映射到 (${mid.x.toFixed(1)}, ${mid.y.toFixed(1)})`)

  // 退化包围盒（直线轨道，h=0）不能崩
  const flat = fitViewport({ x: 0, y: 0, w: 1000, h: 0 }, size, 40)
  check('退化包围盒（h=0）的 scale 有限且为正',
    Number.isFinite(flat.scale) && flat.scale > 0, `scale=${flat.scale}`)
  const flatMid = worldToScreen(flat, { x: 500, y: 0 })
  check('退化包围盒仍居中', near(flatMid.y, size.h / 2, 1e-6))

  // 单点包围盒（w=h=0）
  const dot = fitViewport({ x: 5, y: 5, w: 0, h: 0 }, size, 40)
  check('单点包围盒的 scale 被夹在范围内',
    dot.scale >= MIN_SCALE && dot.scale <= MAX_SCALE, `scale=${dot.scale}`)

  // 超大画布 / 极小画布
  check('极小画布不崩', Number.isFinite(fitViewport(b, { w: 1, h: 1 }).scale))
  check('超大画布 scale 不越界',
    fitViewport(b, { w: 100000, h: 100000 }).scale <= MAX_SCALE)
}

/* ============================================================
 * 6. boundsOf
 * ============================================================ */
{
  check('空数组返回 null', boundsOf([]) === null)
  const b = boundsOf([{ x: 0, y: 5 }, { x: 10, y: -5 }, { x: -10, y: 0 }])
  check('包围盒正确', b.x === -10 && b.y === -5 && b.w === 20 && b.h === 10,
    JSON.stringify(b))
  // NaN 被跳过而不是污染极值
  const bn = boundsOf([{ x: 0, y: 0 }, { x: NaN, y: NaN }, { x: 10, y: 10 }])
  check('NaN 不污染包围盒', bn.x === 0 && bn.y === 0 && bn.w === 10 && bn.h === 10,
    JSON.stringify(bn))
  check('全是 NaN 返回 null', boundsOf([{ x: NaN, y: 0 }]) === null)
}

/* ============================================================
 * 7. 像素容差换算（命中测试的关键）
 * ============================================================ */
{
  // 放大后，同样 12px 屏幕容差对应的世界距离应更小
  const tolAt1 = pixelTolerance({ scale: 1, offset: { x: 0, y: 0 } }, 12)
  const tolAt4 = pixelTolerance({ scale: 4, offset: { x: 0, y: 0 } }, 12)
  check('scale=1 时像素容差 = 世界容差', near(tolAt1, 12))
  check('放大 4 倍后世界容差缩小 4 倍', near(tolAt4, 3))
  check('缩小时世界容差变大',
    pixelTolerance({ scale: 0.25, offset: { x: 0, y: 0 } }, 12) === 48)

  // 真实语义验证：屏幕上 12px 外的点在任意缩放下都应判为"超容差"
  let bad = 0
  for (const scale of [0.1, 1, 3, 20]) {
    const vp = { scale, offset: { x: 17, y: 23 } }
    const anchorScreen = { x: 200, y: 150 }
    const world = screenToWorld(vp, anchorScreen)
    const farWorld = screenToWorld(vp, { x: 200 + 30, y: 150 }) // 屏幕上右移 30px
    if (Math.abs(farWorld.x - world.x) <= pixelTolerance(vp, 12)) bad++
  }
  check('屏幕 30px 外的点在各种缩放下都超容差', bad === 0, `${bad} 例误判`)
}

/* ============================================================
 * 8. 网格步长（1/2/5 × 10^n）
 * ============================================================ */
{
  const steps = [0.05, 0.5, 1, 5, 50, 500].map((s) =>
    niceStep({ scale: s, offset: { x: 0, y: 0 } }, 80))
  check('网格步长恒为正', steps.every((s) => s > 0 && Number.isFinite(s)), JSON.stringify(steps))
  // 步长在屏幕上的像素宽度应落在合理区间（约 80~400px）
  const px = steps.map((s, i) => s * [0.05, 0.5, 1, 5, 50, 500][i])
  check('网格屏显尺寸在合理范围',
    px.every((v) => v >= 70 && v <= 400), JSON.stringify(px.map((v) => v.toFixed(0))))
  // 步长必须是 1/2/5 × 10^n 形式
  const mantissa = steps.map((s) => {
    const e = Math.floor(Math.log10(s))
    return Number((s / 10 ** e).toFixed(6))
  })
  check('步长为 1/2/5 的整幂形式',
    mantissa.every((m) => [1, 2, 5].some((v) => Math.abs(m - v) < 1e-6)),
    JSON.stringify(mantissa))
  check('极小 scale 不产生 0 或 NaN', niceStep({ scale: 1e-6, offset: { x: 0, y: 0 } }) > 0)
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.log(`\n失败 ${fails.length} 项：`)
  fails.forEach((f) => console.log('  ✗ ' + f))
  process.exit(1)
}
console.log('全部通过 ✓\n')
