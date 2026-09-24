/**
 * 轨道节点（平铺）-> 贝塞尔曲线 的回归测试。
 *
 * 轨道不再由航点派生、也不再是地图组件的内部状态，而是树上真实存在的
 * TrackNode：children 里**平铺**着端点节点与控制点节点，靠顺序表达路径。
 * 这段转换是整条链路的地基——解析错了，地图上画出来的就是另一条轨道，
 * 航点也会跟着铺错位置。
 *
 * 关键：**不手抄源码**——用 tsc 编译真实 TS 源再 import。
 * 运行：node scripts/verify-track-nodes.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, writeFileSync, existsSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'tn-'))

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
  parseTrackNodes, handlesOf, trackPointsFromNodes, sampleTrack, pointAtFraction,
} = g

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps

/** 构造节点的小工具 */
const E = (x, y, path = `e${x}_${y}`) => ({ kind: 'endpoint', path, x, y })
const C = (x, y, path = `c${x}_${y}`) => ({ kind: 'control', path, x, y })

/* ============================================================
 * 1. 解析：端点序列与分段
 * ============================================================ */
{
  const nodes = [E(0, 0), C(50, -80), E(100, 0), E(200, 0)]
  const { endpoints, segments, orphans } = parseTrackNodes(nodes)
  check('端点数正确', endpoints.length === 3)
  check('控制点不算端点', endpoints.every((e) => e.kind === 'endpoint'))
  check('段数 = 端点数 - 1', segments.length === 2)
  check('第一段带 1 个控制点', segments[0].controls.length === 1, JSON.stringify(segments[0]))
  check('第二段无控制点（直线）', segments[1].controls.length === 0)
  check('段起点/终点下标正确',
    segments[0].a === 0 && segments[0].b === 1 && segments[1].a === 1 && segments[1].b === 2)
  check('没有游离控制点', orphans.length === 0)
}

/* ============================================================
 * 2. 第一个端点之前的控制点是"游离"的，必须容忍而不是崩
 *
 * 树里允许这种中间状态（比如用户先拖出一个控制点还没建端点），
 * 解析若抛异常或错位，整条轨道会画不出来。
 * ============================================================ */
{
  const nodes = [C(10, 10), C(20, 20), E(0, 0), E(100, 0)]
  const { endpoints, segments, orphans } = parseTrackNodes(nodes)
  check('游离控制点被单独收集', orphans.length === 2)
  check('游离控制点不影响端点解析', endpoints.length === 2)
  check('游离控制点不进任何段', segments.length === 1 && segments[0].controls.length === 0)

  // 只有控制点、没有端点 -> 画不出轨道，但不能抛
  const onlyC = parseTrackNodes([C(0, 0), C(1, 1)])
  check('只有控制点时端点为空', onlyC.endpoints.length === 0)
  check('只有控制点时无段', onlyC.segments.length === 0)
  check('空轨道不抛异常', trackPointsFromNodes([]).length === 0)
  check('只有控制点 -> 曲线为空', trackPointsFromNodes([C(0, 0)]).length === 0)
}

/* ============================================================
 * 3. handlesOf：0 / 1 / 2 个控制点的三种退化
 * ============================================================ */
{
  const a = { x: 0, y: 0 }
  const b = { x: 100, y: 0 }

  // 0 个 -> 直线：手柄退化到各自端点（否则端点会往回勾、弧长虚长）
  const h0 = handlesOf({ a, b, controls: [] })
  check('0 控制点：c1 退化到终点', h0.c1.x === b.x && h0.c1.y === b.y)
  check('0 控制点：c2 退化到起点', h0.c2.x === a.x && h0.c2.y === a.y)

  // 1 个 -> 二次：该点兼作两个手柄
  const h1 = handlesOf({ a, b, controls: [{ x: 50, y: -60 }] })
  check('1 控制点：c1 = c2 = 该点',
    h1.c1.x === 50 && h1.c1.y === -60 && h1.c2.x === 50 && h1.c2.y === -60)

  // 2 个 -> 三次：第一个作出手柄，第二个作入手柄
  const h2 = handlesOf({ a, b, controls: [{ x: 30, y: -40 }, { x: 70, y: -40 }] })
  check('2 控制点：c2 取第一个', h2.c2.x === 30 && h2.c2.y === -40)
  check('2 控制点：c1 取第二个', h2.c1.x === 70 && h2.c1.y === -40)

  // 3 个及以上 -> 只取前两个（多余忽略，不崩）
  const h3 = handlesOf({ a, b, controls: [{ x: 1, y: 1 }, { x: 2, y: 2 }, { x: 3, y: 3 }] })
  check('3 控制点：忽略多余', h3.c2.x === 1 && h3.c1.x === 2)
}

/* ============================================================
 * 4. trackPointsFromNodes：手柄由左右两段分别决定
 *
 * 中间点的 c2 属于"以它为起点"的段，c1 属于"以它为终点"的段，
 * 两侧必须各算各的——取错一侧会让曲线整体错位一段。
 * ============================================================ */
{
  const nodes = [
    E(0, 0), C(30, -50), C(70, -50), E(100, 0), C(150, 60), C(180, 60), E(200, 0),
  ]
  const pts = trackPointsFromNodes(nodes)
  check('端点数 = TrackPoint 数', pts.length === 3)

  check('首点 c1 退化到自身', pts[0].c1.x === 0 && pts[0].c1.y === 0)
  check('末点 c2 退化到自身', pts[2].c2.x === 200 && pts[2].c2.y === 0)

  // 中间点：c1 来自第一段（第二个控制点 70,-50），c2 来自第二段（第一个控制点 150,60）
  check('中间点 c1 取自「以它为终点」的段',
    pts[1].c1.x === 70 && pts[1].c1.y === -50, JSON.stringify(pts[1].c1))
  check('中间点 c2 取自「以它为起点」的段',
    pts[1].c2.x === 150 && pts[1].c2.y === 60, JSON.stringify(pts[1].c2))

  // p 永远等于端点自身，绝不能被手柄覆盖
  check('TrackPoint.p 等于端点坐标',
    pts.every((q, i) => near(q.p.x, [0, 100, 200][i]) && near(q.p.y, 0)))

  // 采样后曲线必须穿过每个端点
  const s = sampleTrack(pts, 48)
  for (let i = 0; i < pts.length; i++) {
    check(`曲线穿过端点${i}`,
      s.pts.some((q) => Math.hypot(q.x - pts[i].p.x, q.y - pts[i].p.y) < 1e-6))
  }
  check('采样结果有限', s.pts.every((q) => Number.isFinite(q.x) && Number.isFinite(q.y)))
}

/* ============================================================
 * 5. 纯直线轨道：手柄退化后弧长必须等于实际距离（不能虚长）
 *
 * 这是之前踩过的坑（端点手柄伸出段外 -> 回勾 -> 直线采样成 1.3 倍）。
 * 现在直线段是"0 控制点"，必须同样守这条不变量。
 * ============================================================ */
{
  const nodes = [E(0, 0), E(100, 0), E(250, 0)]
  const pts = trackPointsFromNodes(nodes)
  const s = sampleTrack(pts, 48)
  check('直线轨道弧长 = 实际距离', near(s.total, 250, 1e-6), `total=${s.total}`)
  check('直线轨道 x 单调不减',
    s.pts.every((q, i) => i === 0 || q.x >= s.pts[i - 1].x - 1e-9))

  // 航点按 u 铺上去应当落在正确的世界坐标
  const mid = pointAtFraction(s, 0.5)
  check('直线轨道 u=0.5 落在中点', near(mid.x, 125, 1e-6), `x=${mid.x}`)
  const q = pointAtFraction(s, 0.25)
  check('直线轨道 u=0.25 落在 1/4 处', near(q.x, 62.5, 1e-6), `x=${q.x}`)
}

/* ============================================================
 * 6. 单端点轨道（画了第一个点还没画第二个）也要能正常出结果
 * ============================================================ */
{
  const pts = trackPointsFromNodes([E(10, 20)])
  check('单端点 -> 1 个 TrackPoint', pts.length === 1)
  check('单端点手柄退化到自身',
    pts[0].c1.x === 10 && pts[0].c2.x === 10 && pts[0].c1.y === 20 && pts[0].c2.y === 20)
  // sampleTrack 在不足 2 点时提前返回空采样（不抛异常即可）
  const s = sampleTrack(pts, 48)
  check('单端点采样不崩且无长度', s.total === 0 && Array.isArray(s.pts))
  check('单端点时 pointAtFraction 也不崩',
    Number.isFinite(pointAtFraction(s, 0.5).x))
}

/* ============================================================
 * 7. 控制点坐标是用户显式摆的，不能被"平滑重算"覆盖
 *
 * 若这里调用了 recomputeHandles，用户拖出来的手柄会被抹平，
 * "控制点节点"就失去意义了。
 * ============================================================ */
{
  const nodes = [E(0, 0), C(50, -120), E(100, 0)]
  const pts = trackPointsFromNodes(nodes)
  check('控制点被原样保留（未被平滑重算）',
    near(pts[0].c2.x, 50) && near(pts[0].c2.y, -120)
    && near(pts[1].c1.x, 50) && near(pts[1].c1.y, -120),
    `c2=(${pts[0].c2.x},${pts[0].c2.y}) c1=(${pts[1].c1.x},${pts[1].c1.y})`)

  // 曲线应当真的被这个手柄拉弯（顶点明显高于两端）
  const s = sampleTrack(pts, 48)
  const minY = Math.min(...s.pts.map((p) => p.y))
  check('控制点确实把曲线拉弯了', minY < -40, `minY=${minY.toFixed(2)}`)
}

/* ============================================================
 * 8. path 必须被保留（地图与树的选中联动依赖它）
 * ============================================================ */
{
  const ePath = 'root/children/0/children/1'
  const cPath = 'root/children/0/children/3'
  const nodes = [E(0, 0, ePath), C(50, -30, cPath), E(100, 0)]
  const { endpoints, segments } = parseTrackNodes(nodes)
  check('端点保留 path（选中联动靠它）', endpoints[0].path === ePath)
  check('段内控制点保留完整节点（含 path）',
    segments[0].controls[0].path === cPath, JSON.stringify(segments[0].controls[0]))
  check('段内控制点保留坐标',
    segments[0].controls[0].x === 50 && segments[0].controls[0].y === -30)
}

/* ============================================================
 * 9. 闭合（成环）：末端点连回首端点
 * ============================================================ */
{
  const X = (path = 'x') => ({ kind: 'close', path, x: 0, y: 0 })

  // 三个端点 + 每段一个控制点 + 闭合
  const nodes = [E(0, 0), C(50, -80, 'c1'), E(200, 0), C(300, -80, 'c2'), E(400, 0),
    C(200, 120, 'c3'), X('close')]
  const p = parseTrackNodes(nodes)
  check('识别为闭合', p.closed === true)
  check('闭合后仍是 3 个端点', p.endpoints.length === 3)
  check('闭合多出最后一段（末点 -> 首点）', p.segments.length === 3)
  check('闭合段的起止正确',
    p.segments[2].a === 2 && p.segments[2].b === 0,
    JSON.stringify(p.segments[2]))
  check('末端点之后的控制点归闭合段（不再被丢弃）',
    p.segments[2].controls.length === 1 && p.segments[2].controls[0].path === 'c3')
  check('闭合后无孤儿', p.orphans.length === 0)

  // 手柄：闭合段给末点的出手柄 + 首点的入手柄
  const pts = trackPointsFromNodes(nodes)
  check('闭合不改变点数', pts.length === 3)
  check('首点拿到入手柄（来自闭合段）', pts[0].c1.y === 120, JSON.stringify(pts[0].c1))
  check('末点拿到出手柄（来自闭合段）', pts[2].c2.y === 120, JSON.stringify(pts[2].c2))
  check('首点出手柄仍由第一段决定', pts[0].c2.y === -80)

  // 采样：闭合段必须真的被采样到，否则环是断的
  const open = sampleTrack(pts, 32, false)
  const closed = sampleTrack(pts, 32, true)
  check('闭合采样更长（多了一整段）', closed.total > open.total,
    `open=${open.total.toFixed(1)} closed=${closed.total.toFixed(1)}`)
  const first = closed.pts[0]
  const last = closed.pts[closed.pts.length - 1]
  check('闭合采样终点回到起点', near(last.x, first.x, 1e-6) && near(last.y, first.y, 1e-6),
    `${JSON.stringify(last)} vs ${JSON.stringify(first)}`)
  check('开口采样终点不回到起点',
    !near(open.pts[open.pts.length - 1].x, open.pts[0].x, 1e-6))

  // 航点仍能沿闭合曲线铺开
  const mid = pointAtFraction(closed, 0.5)
  check('闭合曲线上取点有定义', Number.isFinite(mid.x) && Number.isFinite(mid.y))

  /* 边界：不足两个端点时闭合没有意义，不应该成环 */
  const one = parseTrackNodes([E(0, 0), X()])
  check('单个端点闭合不成环', one.closed === false)
  check('单个端点闭合不产生段', one.segments.length === 0)
  check('没有闭合标记就不成环', parseTrackNodes([E(0, 0), C(1, 1), E(2, 2)]).closed === false)

  /* 闭合标记在中间：只闭合"它之前的路径" */
  const mid2 = parseTrackNodes([E(0, 0), E(100, 0), X(), E(200, 0)])
  check('中间的闭合标记生效', mid2.closed === true)
  check('闭合段连回第一个端点', mid2.segments[1].a === 1 && mid2.segments[1].b === 0)
  check('闭合之后的端点继续往后接', mid2.segments[2].a === 0 && mid2.segments[2].b === 2)

  /* 直线闭合（无控制点）也不能崩 */
  const rect = parseTrackNodes([E(0, 0), E(100, 0), E(100, 100), E(0, 100), X()])
  check('矩形闭合 4 段', rect.segments.length === 4)
  check('矩形闭合段无控制点（直线）', rect.segments[3].controls.length === 0)
  const rp = trackPointsFromNodes([E(0, 0), E(100, 0), E(100, 100), E(0, 100), X()])
  const rs = sampleTrack(rp, 16, true)
  check('矩形闭合采样回到起点',
    near(rs.pts[rs.pts.length - 1].x, 0, 1e-6) && near(rs.pts[rs.pts.length - 1].y, 0, 1e-6))
  check('矩形周长约 400', near(rs.total, 400, 1e-3), `total=${rs.total}`)
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.log(`\n失败 ${fails.length} 项：`)
  fails.forEach((f) => console.log('  ✗ ' + f))
  process.exit(1)
}
console.log('全部通过 ✓\n')
