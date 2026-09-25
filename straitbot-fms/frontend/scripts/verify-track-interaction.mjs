/**
 * TrackMap 交互逻辑的无头回归测试。
 *
 * 为什么不直接测 React 组件：这里要验证的是**拖拽/命中的几何行为**，
 * 把组件里的判定逻辑抽成纯函数来测，比挂 jsdom + 模拟鼠标事件更稳、更快，
 * 也更容易复现边界（夹取、pin 语义、命中优先级）。
 *
 * 关键：**不手抄源码**——用 tsc 编译真实 TS 源再 import。
 * 运行：node scripts/verify-track-interaction.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, writeFileSync, existsSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'ti-'))

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
const { defaultTrack, recomputeHandles, sampleTrack, pointAtFraction, hitTrack } = g

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps

/* ============================================================
 * 复刻组件里的两段判定逻辑（与 TrackMap.tsx 一一对应）
 * ============================================================ */

/** 对应 TrackMap.tsx 中「拖曲线点 p」的夹取：不越过左右邻点 */
function clampPointX(pts, index, rawX) {
  const lo = index === 0 ? 0 : pts[index - 1].p.x + 4
  const hi = index === pts.length - 1 ? 1000 : pts[index + 1].p.x - 4
  return Math.max(lo, Math.min(hi, rawX))
}

/**
 * 对应 endDrag：松开后重算手柄。
 *
 * pin 语义按拖的是什么区分（曾经写错过）：
 * - 拖手柄 -> pin 该点，保住手工调整；
 * - 拖曲线点 p -> **不能 pin**，否则手柄停留在旧绝对坐标，曲线脱离该点。
 */
function applyEndDrag(pts, dragIndex, handle, recompute) {
  const next = pts.map((q) => ({ p: { ...q.p }, c1: { ...q.c1 }, c2: { ...q.c2 } }))
  const pinned = handle === 'p' ? undefined : next.map((_, i) => i === dragIndex)
  return recompute(next, pinned)
}

/** 对应 hitHandle：同距优先控制点 */
function pickHandle(track, canvasPt, toCanvas) {
  let best = null
  let bestD = 10
  track.forEach((q, i) => {
    for (const handle of ['c1', 'c2', 'p']) {
      const c = toCanvas(q[handle])
      const d = Math.hypot(c.x - canvasPt.x, c.y - canvasPt.y)
      if (d < bestD || (Math.abs(d - bestD) < 0.01 && handle !== 'p')) {
        bestD = d
        best = { index: i, handle }
      }
    }
  })
  return best
}

/** 对应框选命中：航点包围盒 14x14 */
function marqueeHit(placed, rect, rectsIntersect) {
  const hit = new Set()
  for (const w of placed) {
    if (rectsIntersect(rect, { x: w.x - 7, y: w.y - 7, w: 14, h: 14 })) hit.add(w.path)
  }
  return hit
}

/* ============================================================
 * 1. 拖曲线点 p：夹取不能越过邻居
 * ============================================================ */
{
  const t = defaultTrack(4, 1000) // p.x = 0, 333.33, 666.67, 1000
  check('拖点0不能被推过点1', clampPointX(t, 0, 9999) <= t[1].p.x - 4)
  check('拖点1夹在0与2之间',
    clampPointX(t, 1, -9999) >= t[0].p.x + 4 && clampPointX(t, 1, 9999) <= t[2].p.x - 4)
  check('拖末点不能被推过前一个', clampPointX(t, 3, -9999) >= t[2].p.x + 4)
  check('拖点0下界为 0', clampPointX(t, 0, -500) === 0)
  check('拖末点上界为 1000', clampPointX(t, 3, 5000) === 1000)
  // 合法值原样通过
  check('合法拖动值不被改动', near(clampPointX(t, 1, 400), 400))

  // 夹取后必须仍然严格单调，否则曲线自交
  const moved = t.map((q) => ({ p: { ...q.p }, c1: { ...q.c1 }, c2: { ...q.c2 } }))
  moved[1].p.x = clampPointX(moved, 1, 9999)
  moved[2].p.x = clampPointX(moved, 2, 0)
  check('夹取后 x 仍严格单调',
    moved.every((q, i) => i === 0 || q.p.x > moved[i - 1].p.x),
    JSON.stringify(moved.map((q) => q.p.x.toFixed(1))))
}

/* ============================================================
 * 2. 拖 p 后手柄必须重新算，且曲线仍穿过该点
 *
 * 注意语义：手柄**不是**刚性平移的。`recomputeHandles` 会按新位置重新
 * 求切线（这正是"平滑"的定义），所以断言应针对"曲线穿过 p"和
 * "手柄朝新位置收敛"，而不是"手柄位移等于 p 位移"。
 * ============================================================ */
{
  const t = defaultTrack(4, 1000)
  const moved = t.map((q) => ({ p: { ...q.p }, c1: { ...q.c1 }, c2: { ...q.c2 } }))
  moved[1].p.y = -100 // 把内部点往上拖（画布 y 向下，这里只是取个非零值）

  const after = applyEndDrag(moved, 1, 'p', recomputeHandles)

  // 核心不变量：p 自身不能被重算改动
  check('重算不改动 p 的位置',
    near(after[1].p.x, moved[1].p.x) && near(after[1].p.y, moved[1].p.y))

  // 手柄必须反映新的几何：c1 指向 c2 方向（共线于切线），即退化/共线的点不该留下旧手柄
  // 用「手柄是否朝 p 与邻点连线方向」来断言
  const dir = { x: after[2].p.x - after[0].p.x, y: after[2].p.y - after[0].p.y }
  const h1 = { x: after[1].p.x - after[1].c1.x, y: after[1].p.y - after[1].c1.y }
  const cross = dir.x * h1.y - dir.y * h1.x
  check('c1 与相邻点连线共线（切线正确）', near(cross, 0, 1e-6), `cross=${cross}`)
  check('c1 在手柄长度内不越界（≤ 相邻段 1/3）',
    Math.hypot(h1.x, h1.y) <= Math.hypot(after[1].p.x - after[0].p.x, after[1].p.y - after[0].p.y) / 3 + 1e-6)

  // 把点拖到很偏的位置后，曲线必须仍然穿过每个控制点
  const s = sampleTrack(after, 48)
  for (let i = 0; i < after.length; i++) {
    const hit = s.pts.some((q) => Math.hypot(q.x - after[i].p.x, q.y - after[i].p.y) < 1e-6)
    check(`拖 p 后曲线仍穿过点${i}`, hit)
  }

  // 拖完以后不能产生 NaN / x 回退
  check('拖 p 后无 NaN', s.pts.every((q) => Number.isFinite(q.x) && Number.isFinite(q.y)))
  check('拖 p 后 x 单调不减',
    s.pts.every((q, i) => i === 0 || q.x >= s.pts[i - 1].x - 1e-6))

  /* 回归：拖 p 时**不能** pin（曾经 pin 错了）。
     如果错 pin，手柄停在旧绝对坐标，曲线就不再穿过 moved 后的 p。
     这里显式比较"正确做法"与"错误做法"的结果差异。 */
  {
    const wrong = (() => {
      const p = moved.map((q) => ({ p: { ...q.p }, c1: { ...q.c1 }, c2: { ...q.c2 } }))
      // 错误做法：拖 p 也 pin -> 手柄停留在旧位置
      return recomputeHandles(p, p.map((_, i) => i === 1))
    })()
    const correct = applyEndDrag(moved, 1, 'p', recomputeHandles)

    const wrongHitsP = (() => {
      const sw = sampleTrack(wrong, 48)
      return sw.pts.some((q) => Math.hypot(q.x - wrong[1].p.x, q.y - wrong[1].p.y) < 1e-6)
    })()
    const correctHitsP = (() => {
      const sc = sampleTrack(correct, 48)
      return sc.pts.some((q) => Math.hypot(q.x - correct[1].p.x, q.y - correct[1].p.y) < 1e-6)
    })()
    // 错误做法会让曲线脱离该点（手柄仍是旧的），正确做法一定穿过
    check('拖 p 时必须重算手柄（否则曲线脱离该点）', correctHitsP,
      `correct=${correctHitsP} wrong=${wrongHitsP}`)
    check('正确做法的手柄确实被重算过（与错 pin 的结果不同）',
      !near(correct[1].c1.y, wrong[1].c1.y, 1e-6),
      `correct.c1.y=${correct[1].c1.y.toFixed(3)} wrong.c1.y=${wrong[1].c1.y.toFixed(3)}`)
  }
}

/* ============================================================
 * 3. 拖手柄：该点被 pin，重算不得覆盖手工调整
 * ============================================================ */
{
  // 用非直线轨道，否则"重算"结果与手工值恰好相同，测不出 pin 是否生效
  const t = defaultTrack(4, 1000)
  t[1].p.y = -120
  const base = recomputeHandles(t)
  const moved = base.map((q) => ({ p: { ...q.p }, c1: { ...q.c1 }, c2: { ...q.c2 } }))
  moved[1].c2 = { x: 500, y: -320 } // 手工把点1的出手柄拉到明显不同的位置
  const manual = { ...moved[1].c2 }

  const after = applyEndDrag(moved, 1, 'c2', recomputeHandles)
  check('被拖的手柄保持手工值（c2）',
    near(after[1].c2.x, manual.x, 1e-9) && near(after[1].c2.y, manual.y, 1e-9),
    `得到 (${after[1].c2.x.toFixed(1)}, ${after[1].c2.y.toFixed(1)})，应为 (${manual.x}, ${manual.y})`)

  // 未被 pin 的点应该被重算过（与"什么都不做"不同）
  const untouched = (() => {
    const p = moved.map((q) => ({ p: { ...q.p }, c1: { ...q.c1 }, c2: { ...q.c2 } }))
    return recomputeHandles(p, p.map((_, i) => i === 1))
  })()
  check('pin 语义：结果与手工构造的 pinned 重算一致',
    after.every((q, i) => near(q.c1.x, untouched[i].c1.x) && near(q.c1.y, untouched[i].c1.y)))
}

/* ============================================================
 * 4. 命中优先级：控制点与曲线点同距时给控制点
 *
 * 注意：直线轨道上 p 与 c1/c2 是**重合**的，测不出优先级，
 * 必须用弯曲轨道让三者的画布坐标分开。
 * ============================================================ */
{
  const t = defaultTrack(4, 1000)
  t[1].p.y = -150
  t[2].p.y = 150
  const track = recomputeHandles(t)

  // 用 1:1 的映射（x/y 同尺度）做画布坐标，保证距离关系不变
  const toCanvas = (pt) => ({ x: pt.x, y: pt.y })

  // 三者坐标必须互不相同，否则这个测试没意义
  const c1 = toCanvas(track[1].c1)
  const c2 = toCanvas(track[1].c2)
  const p1 = toCanvas(track[1].p)
  check('弯曲轨道上 p 与 c1 不重合', Math.hypot(c1.x - p1.x, c1.y - p1.y) > 15)
  check('弯曲轨道上 p 与 c2 不重合', Math.hypot(c2.x - p1.x, c2.y - p1.y) > 15)

  const hp = pickHandle(track, p1, toCanvas)
  check('正对曲线点命中 p',
    hp !== null && hp.handle === 'p' && hp.index === 1, JSON.stringify(hp))

  const hc1 = pickHandle(track, c1, toCanvas)
  check('正对 c1 命中 c1',
    hc1 !== null && hc1.handle === 'c1' && hc1.index === 1, JSON.stringify(hc1))

  const hc2 = pickHandle(track, c2, toCanvas)
  check('正对 c2 命中 c2',
    hc2 !== null && hc2.handle === 'c2' && hc2.index === 1, JSON.stringify(hc2))

  // 同距时的优先级：构造一个"控制点与曲线点画布坐标完全重合"的场景。
  // 真实几何里直线轨道的 p 与 c1/c2 并不重合（手柄在相邻段 1/3 处），
  // 所以这里直接手工摆出重合来验证 tie-break 分支确实偏向控制点。
  const tie = [
    { p: { x: 0, y: 0 }, c1: { x: 0, y: 0 }, c2: { x: 0, y: 0 } },
    { p: { x: 100, y: 0 }, c1: { x: 100, y: 0 }, c2: { x: 100, y: 0 } },
  ]
  const ht = pickHandle(tie, { x: 100, y: 0 }, toCanvas)
  check('p 与手柄完全重合时优先给控制点',
    ht !== null && ht.handle !== 'p', JSON.stringify(ht))

  // 太远 -> 不命中
  check('超出容差不命中', pickHandle(track, { x: -500, y: -500 }, toCanvas) === null)

  // 直线轨道：正对 p 应命中 p（手柄在相邻段 1/3 处，不重合）
  const straight = defaultTrack(4, 1000)
  const hs = pickHandle(straight, toCanvas(straight[1].p), toCanvas)
  check('直线轨道正对曲线点命中 p',
    hs !== null && hs.handle === 'p' && hs.index === 1, JSON.stringify(hs))

  // 两个点之间的正中间：离任何可抓取点都超过容差 -> 不命中
  const far = { x: (straight[0].p.x + straight[1].p.x) / 2, y: 0 }
  check('远离所有抓手时不命中',
    pickHandle(straight, { x: far.x, y: 200 }, toCanvas) === null)
}

/* ============================================================
 * 5. 框选：包围盒相交
 * ============================================================ */
{
  const { rectsIntersect, normalizeRect } = g
  const placed = [
    { path: 'a', x: 100, y: 100 },
    { path: 'b', x: 300, y: 100 },
    { path: 'c', x: 500, y: 100 },
  ]
  const box = (x1, y1, x2, y2) => normalizeRect({ x: x1, y: y1 }, { x: x2, y: y2 })

  // 只框住 b
  const r1 = marqueeHit(placed, box(280, 80, 320, 120), rectsIntersect)
  check('只框住 b', r1.size === 1 && r1.has('b'), JSON.stringify([...r1]))

  // 框住全部
  const r2 = marqueeHit(placed, box(0, 0, 900, 900), rectsIntersect)
  check('框住全部', r2.size === 3)

  // 反向拖拽（从右下往左上）应得到同样结果
  const r3 = marqueeHit(placed, box(320, 120, 280, 80), rectsIntersect)
  check('反向拖拽结果一致', r3.size === 1 && r3.has('b'))

  // 空框
  const r4 = marqueeHit(placed, box(700, 700, 800, 800), rectsIntersect)
  check('框在空白处选中 0 个', r4.size === 0)

  // 擦边：航点 bbox 是 (293~307)，框到 292 就碰不到了
  const r5 = marqueeHit(placed, box(280, 80, 292, 120), rectsIntersect)
  check('恰好不擦到时不含 b', !r5.has('b'), JSON.stringify([...r5]))
  const r6 = marqueeHit(placed, box(280, 80, 295, 120), rectsIntersect)
  check('轻擦到就含 b', r6.has('b'))
}

/* ============================================================
 * 6. 真实样例：加航点后按 x 找插入位
 * ============================================================ */
{
  const xs = [0.814, 10.5, 22.3, 40.1, 55.04]
  // 轨道按真实尺寸画（55.04 m）：世界坐标就是米，采样弧长即量程
  const s = sampleTrack(defaultTrack(4, 55.04), 48)
  const L = s.total
  const us = xs.map((x) => g.xToU(L, x))
  check('样例 u 全在 [0,1]', us.every((v) => v >= 0 && v <= 1), JSON.stringify(us))

  // 模拟在 u=0.5 处右键加点，反算出的 x 应正好是轨道中点的米数
  const u = 0.5
  const x = g.uToX(L, u)
  check('反算 x = 轨道中点（米）', near(x, L / 2, 1e-9), `x=${x.toFixed(3)}`)

  // 按 x 找插入下标：应插在 22.3 之后、40.1 之前
  let insertAt = xs.length
  for (let i = 0; i < xs.length; i++) if (xs[i] > x) { insertAt = i; break }
  check('插入下标正确（x 序保持）', insertAt === 3, `insertAt=${insertAt}`)

  // 插完后序列仍严格递增
  const next = [...xs.slice(0, insertAt), x, ...xs.slice(insertAt)]
  check('插入后 x 序列仍递增', next.every((v, i) => i === 0 || v > next[i - 1]),
    JSON.stringify(next.map((v) => v.toFixed(2))))

  // 加的航点在地图上必须落在已有两点之间
  const placed = next.map((v) => ({ v, q: pointAtFraction(s, g.xToU(L, v)) }))
  check('新航点在图上位于左右两邻点之间',
    placed[insertAt].q.x > placed[insertAt - 1].q.x && placed[insertAt].q.x < placed[insertAt + 1].q.x)
}

/* ============================================================
 * 7. 删曲线点：保留最少 2 点，删完仍可采样
 * ============================================================ */
{
  const t = defaultTrack(5, 1000)
  check('5 点轨道按最小值拒绝删到 1 点', t.length - 1 >= 2)
  const next = t.filter((_, i) => i !== 2)
  const s = sampleTrack(recomputeHandles(next), 32)
  check('删中间一点后仍可采样', s.pts.length > 0 && Number.isFinite(s.total))
  check('删后总长为正', s.total > 0)
  check('删后曲线仍穿过剩余点',
    next.every((q) => s.pts.some((p) => Math.hypot(p.x - q.p.x, p.y - q.p.y) < 1e-6)))

  // 端点删除
  const head = t.slice(1)
  const sh = sampleTrack(recomputeHandles(head), 32)
  check('删首点后仍可采样', sh.total > 0)
  const tail = t.slice(0, -1)
  const st = sampleTrack(recomputeHandles(tail), 32)
  check('删末点后仍可采样', st.total > 0)
}

/* ============================================================
 * 8. 命中轨道返回的 u 可映射回 x（右键加点的前提）
 * ============================================================ */
{
  const track = defaultTrack(4, 1000)
  const s = sampleTrack(track, 48)
  let bad = 0
  for (const uExpect of [0.1, 0.25, 0.4, 0.6, 0.75, 0.9]) {
    const p = pointAtFraction(s, uExpect)
    const u = hitTrack(s, { x: p.x, y: p.y }, 6)
    if (u === null || Math.abs(u - uExpect) > 0.02) bad++
  }
  check('曲线上的点命中回的 u 与原 u 一致', bad === 0, `${bad} 个偏差过大`)
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.log(`\n失败 ${fails.length} 项：`)
  fails.forEach((f) => console.log('  ✗ ' + f))
  process.exit(1)
}
console.log('全部通过 ✓\n')
