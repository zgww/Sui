/**
 * 缩放/平移后的交互正确性验证。
 *
 * 视口数学本身由 verify-viewport.mjs 覆盖；这里验证的是**把视口接进交互之后**
 * 是否还成立——最容易出错的正是这一层：
 *
 * 1. 命中容差用世界单位还是屏幕像素？用错的话放大后点不中、缩小后到处点中。
 * 2. 框选矩形要不要反投影？不反投影的话缩放后框选范围会错位。
 * 3. 拖动曲线点时，屏幕位移换算成世界位移要不要除以 scale？
 * 4. 滚轮缩放后，原本在鼠标下的航点不能跑掉。
 *
 * 复刻 TrackMap.tsx 里对应的调用方式（与源码一一对应），跑真实几何函数。
 * 运行：node scripts/verify-zoom-interaction.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, writeFileSync, existsSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'zi-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) { console.error('请先 npm install'); process.exit(1) }
try {
  execFileSync(process.execPath, [tscEntry,
    'src/components/trackGeometry.ts', '--outDir', out,
    '--target', 'es2020', '--module', 'es2020', '--skipLibCheck', '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.message); process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

const g = await import(pathToFileURL(join(out, 'trackGeometry.js')).href)
const {
  defaultTrack, sampleTrack, pointAtFraction, hitTrack, xToU, uToX,
  worldToScreen, screenToWorld, zoomAt, panBy, fitViewport, pixelTolerance,
  normalizeRect, rectsIntersect, boundsOf,
} = g

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps

/* -------- 复刻组件里"航点摆到画布上"的流程 -------- */
function layout(xs, track, vp) {
  const s = sampleTrack(track, 48)
  // 轨道画多长就是多少米，采样弧长即量程
  const us = xs.map((x) => xToU(s.total, x))
  return us.map((u, i) => {
    const w = pointAtFraction(s, u)
    return { path: `w${i}`, u, world: { x: w.x, y: w.y }, canvas: worldToScreen(vp, w) }
  })
}
const nearestWaypoint = (placed, pt) => {
  let bi = -1
  let bd = 13
  placed.forEach((w, i) => {
    const d = Math.hypot(w.canvas.x - pt.x, w.canvas.y - pt.y)
    if (d < bd) { bd = d; bi = i }
  })
  return bi
}

/* ============================================================
 * 1. 缩放后仍能用屏幕像素命中航点
 * ============================================================ */
{
  const xs = [0.814, 5, 12, 28, 55.04]
  const track = defaultTrack(4, 55.04)
  const size = { w: 800, h: 300 }
  const base = fitViewport(boundsOf(sampleTrack(track, 48).pts), size, 40)

  let bad = 0
  const details = []
  for (const factor of [0.3, 0.6, 1, 2, 5, 12]) {
    const vp = zoomAt(base, { x: size.w / 2, y: size.h / 2 }, factor)
    const placed = layout(xs, track, vp)
    placed.forEach((w, i) => {
      // 正对着某个航点"点击"，必须命中它自己
      const hit = nearestWaypoint(placed, w.canvas)
      if (hit !== i) {
        bad++
        details.push(`f=${factor} 点${i} 命中到 ${hit}`)
      }
    })
  }
  check('各种缩放下正对航点点击都能命中', bad === 0, details.slice(0, 3).join(' | '))

  // 缩得很小时航点会挤在一起，此时"点中最近的那个"仍应是合法结果，
  // 但不能出现"完全点不中"（返回 -1）
  const tiny = zoomAt(base, { x: 0, y: 0 }, 0.05)
  const tp = layout(xs, track, tiny)
  const anyHit = tp.some((w) => nearestWaypoint(tp, w.canvas) >= 0)
  check('极限缩小时至少能命中航点', anyHit)
}

/* ============================================================
 * 2. 命中轨道：容差必须按 scale 换算
 * ============================================================ */
{
  const track = defaultTrack(4, 55.04)
  const s = sampleTrack(track, 48)
  const size = { w: 800, h: 300 }
  const base = fitViewport(boundsOf(s.pts), size, 40)

  let bad = 0
  const details = []
  for (const factor of [0.5, 1, 3, 10]) {
    const vp = zoomAt(base, { x: size.w / 2, y: size.h / 2 }, factor)
    // 取曲线上的点，屏幕上往上偏 6px（在 14px 容差内）应命中
    for (const u of [0.2, 0.5, 0.8]) {
      const wpt = pointAtFraction(s, u)
      const scr = worldToScreen(vp, wpt)
      const probeScreen = { x: scr.x, y: scr.y - 6 }
      const uHit = hitTrack(s, screenToWorld(vp, probeScreen), pixelTolerance(vp, 14))
      if (uHit === null) { bad++; details.push(`f=${factor} u=${u} 屏幕偏 6px 却未命中`) }
    }
  }
  check('各种缩放下屏幕偏 6px 仍命中轨道', bad === 0, details.slice(0, 3).join(' | '))

  // 屏幕上偏 30px（超出 14px 容差）不应命中——除非缩小到 30px 对应的世界距离
  // 仍然很近，所以只在放大倍率下断言
  let bad2 = 0
  for (const factor of [2, 5, 10]) {
    const vp = zoomAt(base, { x: size.w / 2, y: size.h / 2 }, factor)
    const wpt = pointAtFraction(s, 0.5)
    const scr = worldToScreen(vp, wpt)
    const probe = { x: scr.x, y: scr.y - 40 }
    if (hitTrack(s, screenToWorld(vp, probe), pixelTolerance(vp, 14)) !== null) bad2++
  }
  check('放大后屏幕偏 40px 不命中轨道', bad2 === 0, `${bad2} 例误命中`)

  // 反例：如果**忘了**换算（直接用像素当世界容差），放大后命中范围会宽得离谱
  {
    const vp = zoomAt(base, { x: size.w / 2, y: size.h / 2 }, 10)
    const wpt = pointAtFraction(s, 0.5)
    const scr = worldToScreen(vp, wpt)
    const probe = { x: scr.x, y: scr.y - 40 }
    const wrongWay = hitTrack(s, screenToWorld(vp, probe), 14) // 错：没换算
    check('未换算容差会误命中（证明换算确有必要）', wrongWay !== null)
  }
}

/* ============================================================
 * 3. 框选：反投影到世界坐标后缩放不影响结果
 * ============================================================ */
{
  const xs = [0, 10, 20, 30, 40, 50]
  const track = defaultTrack(4, 55.04)
  const s = sampleTrack(track, 48)
  const size = { w: 800, h: 300 }
  const base = fitViewport(boundsOf(s.pts), size, 40)

  // 用世界坐标定义"要框住的航点区间"，然后在不同缩放下换算成屏幕矩形去框
  const runMarquee = (vp, worldRect) => {
    const placed = layout(xs, track, vp)
    const tol = pixelTolerance(vp, 7)
    const hit = new Set()
    for (const w of placed) {
      const r = { x: w.world.x - tol, y: w.world.y - tol, w: tol * 2, h: tol * 2 }
      if (rectsIntersect(worldRect, r)) hit.add(w.path)
    }
    return hit
  }

  // 世界坐标里框住中段（轨道只有 55.04 m，所以用米数而不是原来的 100~500）
  const wRect = { x: 15, y: -1e6, w: 30, h: 2e6 }
  let bad = 0
  const ref = runMarquee(base, wRect).size
  for (const factor of [0.5, 1, 2, 4, 8]) {
    const vp = zoomAt(base, { x: size.w / 2, y: size.h / 2 }, factor)
    if (runMarquee(vp, wRect).size !== ref) bad++
  }
  check('框选用世界坐标时结果与缩放无关', bad === 0, `基准 ${ref} 个，${bad} 例不一致`)
  check('框选确实选中了部分航点（非空非全）', ref > 0 && ref < xs.length, `选中 ${ref}/${xs.length}`)

  // 对比：如果框选**不**反投影（拿屏幕矩形当世界矩形），缩放后结果就会错
  const screenRectAsWorld = (vp, scrRect) => {
    const placed = layout(xs, track, vp)
    const hit = new Set()
    for (const w of placed) {
      if (rectsIntersect(scrRect, { x: w.world.x - 7, y: w.world.y - 7, w: 14, h: 14 })) hit.add(w.path)
    }
    return hit
  }
  const vpSmall = zoomAt(base, { x: size.w / 2, y: size.h / 2 }, 0.5)
  const scrRect = { x: 200, y: -1e6, w: 200, h: 2e6 }
  const wrong = screenRectAsWorld(vpSmall, scrRect).size
  // 反投影要取**轨道所在的那条水平线**（画布中线 y=size.h/2），取屏幕 y=0
  // 会投影到轨道上方很远处，框永远框不到东西
  const right = runMarquee(vpSmall, normalizeRect(
    screenToWorld(vpSmall, { x: scrRect.x, y: size.h / 2 }),
    screenToWorld(vpSmall, { x: scrRect.x + scrRect.w, y: size.h / 2 }),
  )).size
  check('不反投影会给出不同结果（证明反投影必要）', wrong !== right,
    `错误做法 ${wrong} 个 vs 正确 ${right} 个`)
}

/* ============================================================
 * 4. 拖曲线点：屏幕位移要除以 scale 才是世界位移
 * ============================================================ */
{
  const track = defaultTrack(4, 55.04)
  const size = { w: 800, h: 300 }
  const base = fitViewport(boundsOf(sampleTrack(track, 48).pts), size, 40)

  for (const factor of [0.5, 1, 4, 10]) {
    const vp = zoomAt(base, { x: size.w / 2, y: size.h / 2 }, factor)
    const startScreen = { x: 300, y: 150 }
    const startWorld = screenToWorld(vp, startScreen)
    const movedScreen = { x: 300 + 50, y: 150 + 30 } // 屏幕右下移 (50,30)
    const movedWorld = screenToWorld(vp, movedScreen)
    check(`f=${factor}：屏幕位移换算出的世界位移 = 像素/scale`,
      near(movedWorld.x - startWorld.x, 50 / vp.scale, 1e-9)
      && near(movedWorld.y - startWorld.y, 30 / vp.scale, 1e-9),
      `得到 (${(movedWorld.x - startWorld.x).toFixed(4)}, ${(movedWorld.y - startWorld.y).toFixed(4)})`)
  }

  // 拖动后曲线仍穿过该点（用真实 recomputeHandles 收尾）
  {
    const vp = zoomAt(base, { x: size.w / 2, y: size.h / 2 }, 3)
    const next = track.map((q) => ({ p: { ...q.p }, c1: { ...q.c1 }, c2: { ...q.c2 } }))
    const startScreen = worldToScreen(vp, next[1].p)
    const nowWorld = screenToWorld(vp, { x: startScreen.x + 20, y: startScreen.y - 40 })
    next[1].p.y = nowWorld.y
    next[1].p.x = Math.max(next[0].p.x + 4, Math.min(next[2].p.x - 4, nowWorld.x))
    const after = g.recomputeHandles(next)
    const s = sampleTrack(after, 48)
    check('缩放后拖动曲线点，曲线仍穿过该点',
      s.pts.some((q) => Math.hypot(q.x - after[1].p.x, q.y - after[1].p.y) < 1e-6))
  }
}

/* ============================================================
 * 5. 滚轮缩放：鼠标下的航点不能跑
 * ============================================================ */
{
  const xs = [2, 15, 30, 45]
  const track = defaultTrack(4, 55.04)
  const s = sampleTrack(track, 48)
  const size = { w: 900, h: 320 }
  const base = fitViewport(boundsOf(s.pts), size, 40)

  let maxDrift = 0
  let worst = ''
  const anchor = { x: 520, y: 160 } // 模拟鼠标停在画布某处
  for (const target of [1, 3, 8, 20, 0.4, 0.15]) {
    let vp = { ...base, offset: { ...base.offset } }
    const placedBefore = layout(xs, track, vp)
    // 找到锚点下最近的航点，记录它在**屏幕**上的位置
    const anchorWorld = screenToWorld(vp, anchor)
    let best = null
    let bd = Infinity
    for (const w of placedBefore) {
      const d = Math.hypot(w.world.x - anchorWorld.x, w.world.y - anchorWorld.y)
      if (d < bd) { bd = d; best = w }
    }
    if (!best) continue
    const beforeScreen = worldToScreen(vp, best.world)

    // 反复滚轮缩放，锚点始终在鼠标处。
    // 迭代必须**有上限**：目标倍率可能超出 MIN/MAX_SCALE 被夹住，
    // 此时 `vp.scale` 永远逼近不到 target，无上限的 while 会死循环。
    for (let step = 0; step < 400; step++) {
      if (Math.abs(vp.scale - target) <= target * 0.01) break
      const f = vp.scale < target ? 1.06 : 1 / 1.06
      const nextVp = zoomAt(vp, anchor, f)
      if (nextVp.scale === vp.scale) break // 已顶到缩放边界，停
      vp = nextVp
    }
    const afterScreen = worldToScreen(vp, best.world)
    const drift = Math.hypot(afterScreen.x - beforeScreen.x, afterScreen.y - beforeScreen.y)
    if (drift > maxDrift) { maxDrift = drift; worst = `目标 ${target}×` }
  }
  /**
   * 注意：这里**不能**要求"航点漂移 ≤ 某个小像素值"。
   * 围绕锚点缩放时，离锚点越远的点必然移动越多（这是缩放的几何本质，
   * 不是 bug）。真正该守的不变量是"锚点本身零漂移"，由下面那条断言把关。
   * 此处只做粗筛：确保没有出现指数级发散/视口被甩飞。
   */
  check('滚轮缩放不出现发散（漂移量级可控）', maxDrift < 4000,
    `最大漂移 ${maxDrift.toFixed(1)}px（${worst}）`)

  // 严格版：锚点正下方的世界点零漂移
  let vp = { ...base, offset: { ...base.offset } }
  const w0 = screenToWorld(vp, anchor)
  for (let i = 0; i < 30; i++) vp = zoomAt(vp, anchor, 1.08)
  for (let i = 0; i < 30; i++) vp = zoomAt(vp, anchor, 1 / 1.08)
  const w1 = screenToWorld(vp, anchor)
  check('滚轮反复缩放后锚点世界坐标复原',
    near(w0.x, w1.x, 1e-6) && near(w0.y, w1.y, 1e-6),
    `(${w0.x.toFixed(4)},${w0.y.toFixed(4)}) vs (${w1.x.toFixed(4)},${w1.y.toFixed(4)})`)

  /* 用**真实滚轮事件**的参数走一遍：组件里是
     `factor = Math.exp(-deltaY * unit * 0.0015)`，一格 deltaY≈100。
     对一连串随机滚动，锚点世界坐标必须始终不动。 */
  {
    let v = { ...base, offset: { ...base.offset } }
    const a = { x: 610, y: 90 }
    const wStart = screenToWorld(v, a)
    let maxErr = 0
    let r = 987654321
    const rnd = () => { r = (r * 1103515245 + 12345) & 0x7fffffff; return r / 0x7fffffff }
    for (let i = 0; i < 200; i++) {
      const deltaY = (rnd() - 0.5) * 600 // 正向/反向滚动混合
      const unit = 1
      const factor = Math.exp(-deltaY * unit * 0.0015)
      // 镜像组件里的边界行为
      const before = v.scale
      v = zoomAt(v, a, factor)
      const wNow = screenToWorld(v, a)
      if (v.scale !== before) {
        maxErr = Math.max(maxErr, Math.hypot(wNow.x - wStart.x, wNow.y - wStart.y))
      }
    }
    check('真实滚轮序列下锚点世界坐标零漂移', maxErr < 1e-6,
      `最大误差 ${maxErr.toExponential(3)}`)
  }
}

/* ============================================================
 * 6. 平移后一切照常
 * ============================================================ */
{
  const xs = [5, 25, 40]
  const track = defaultTrack(4, 55.04)
  const s = sampleTrack(track, 48)
  const size = { w: 800, h: 300 }
  const base = fitViewport(boundsOf(s.pts), size, 40)

  // 平移 (120, -60) 后，每个航点的屏幕坐标应整体平移同样距离
  const moved = panBy(base, 120, -60)
  const a = layout(xs, track, base)
  const b = layout(xs, track, moved)
  check('平移后所有航点屏幕位置同步位移',
    a.every((w, i) =>
      near(b[i].canvas.x - w.canvas.x, 120, 1e-9)
      && near(b[i].canvas.y - w.canvas.y, -60, 1e-9)),
    JSON.stringify(a.map((w, i) => [b[i].canvas.x - w.canvas.x, b[i].canvas.y - w.canvas.y])))

  // 平移后世界坐标不变 -> 右键加航点仍能命中
  const uOk = hitTrack(s, screenToWorld(moved, worldToScreen(moved, pointAtFraction(s, 0.6))),
    pixelTolerance(moved, 14))
  check('平移后仍能命中轨道', uOk !== null && Math.abs(uOk - 0.6) < 0.02, `u=${uOk}`)
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.log(`\n失败 ${fails.length} 项：`)
  fails.forEach((f) => console.log('  ✗ ' + f))
  process.exit(1)
}
console.log('全部通过 ✓\n')
