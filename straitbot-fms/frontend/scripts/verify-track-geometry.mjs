/**
 * 轨道曲线几何回归测试。
 *
 * 关键：**不从源码手抄函数**，而是先用 tsc 把 src/components/trackGeometry.ts
 * 编译成临时 JS 再 import —— 手抄副本会和源码漂移（第一版就是这么抄出假绿/假红的）。
 * 运行：node scripts/verify-track-geometry.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const frontendRoot = resolve(here, '..')
const outDir = mkdtempSync(join(tmpdir(), 'tg-'))

// 直接调本地 node_modules 里的 tsc 入口，绕开 npx：
// Windows 上 spawnSync('npx.cmd') 会 EINVAL（.cmd 不是可执行 PE，node 不认）。
const tscEntry = join(frontendRoot, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}

try {
  execFileSync(
    process.execPath,
    [tscEntry, 'src/components/trackGeometry.ts', '--outDir', outDir,
      '--target', 'es2020', '--module', 'es2020', '--skipLibCheck', '--moduleResolution', 'bundler'],
    { cwd: frontendRoot, stdio: 'pipe' },
  )
} catch (e) {
  console.error('编译 trackGeometry.ts 失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}

// tsc 的 outDir 里没有 package.json，node 会把它按 CommonJS 解析一遍再回退到 ESM，
// 每跑一次就刷一段 MODULE_TYPELESS_PACKAGE_JSON 警告。放个 type:module 声明消掉它。
writeFileSync(join(outDir, 'package.json'), JSON.stringify({ type: 'module' }))

const mod = await import(pathToFileURL(join(outDir, 'trackGeometry.js')).href)
const {
  defaultTrack, recomputeHandles, sampleTrack, pointAtFraction,
  hitTrack, distToSegment, closestT, rectsIntersect, cubicAt,
  nearestIndex, normalizeRect, evenFractions,
  formatLength, spanText, parseTrackNodes, trackPointsFromNodes,
  xToU, uToX, trackLengthOf, fallbackLengthM, FALLBACK_MIN_M,
  backgroundRect, backgroundScaleAt, sectionRange, sectionPoints,
} = mod

/* ---- 断言 ---- */

let pass = 0
const failures = []
function check(name, cond, extra = '') {
  if (cond) { pass++; return }
  failures.push(`${name} ${extra}`)
}
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps

/* 1. 默认轨道 */
{
  const t = defaultTrack(4, 1000)
  check('默认轨道点数', t.length === 4)
  check('默认轨道水平等分',
    near(t[0].p.x, 0) && near(t[3].p.x, 1000) && near(t[1].p.x, 1000 / 3))
  check('默认轨道 y 全为 0', t.every((q) => near(q.p.y, 0)))
  check('首点 c1 退化到自身（防起点回勾）', near(t[0].c1.x, 0) && near(t[0].c1.y, 0))
  check('末点 c2 退化到自身', near(t[3].c2.x, 1000))
}

/* 2. 采样：直线长度必须等于几何长度（这是曲线数学是否自洽的硬指标） */
{
  const t = defaultTrack(4, 1000)
  const s = sampleTrack(t, 32)
  check('直线采样总长 = 1000', near(s.total, 1000, 1e-6), `实际 ${s.total}`)
  check('采样点数 = 段数*每段+1', s.pts.length === 3 * 32 + 1)
  check('累计弧长单调不减', s.cum.every((v, i) => i === 0 || v >= s.cum[i - 1]))
  check('累计弧长末项 = 总长', near(s.cum[s.cum.length - 1], s.total))

  // x 必须严格单调（否则航点会左右乱排）
  const xs = s.pts.map((q) => q.x)
  check('直线采样 x 无回退', xs.every((v, i) => i === 0 || v > xs[i - 1]))
}

/* 3. 每段各自为直线段长的 1/3 */
{
  const t = defaultTrack(4, 900)
  const s = sampleTrack(t, 32)
  check('三段等分总长 = 900', near(s.total, 900, 1e-6), `实际 ${s.total}`)
}

/* 4. 拉弯后弧长变长，且仍穿过控制点 */
{
  const t = defaultTrack(4, 1000)
  t[1].p.y = -150
  t[2].p.y = 150
  recomputeHandles(t)
  const s = sampleTrack(t, 32)
  check('弯曲后弧长 > 直线长', s.total > 1000, `实际 ${s.total}`)
  for (let i = 0; i < t.length; i++) {
    const hit = s.pts.some((q) => Math.hypot(q.x - t[i].p.x, q.y - t[i].p.y) < 1e-6)
    check(`曲线穿过第 ${i} 个控制点`, hit)
  }
}

/* 5. 手柄限幅：不得伸出到所属段之外 */
{
  const t = recomputeHandles([
    { p: { x: 0, y: 0 }, c1: {}, c2: {} },
    { p: { x: 100, y: 0 }, c1: {}, c2: {} },
    { p: { x: 900, y: 0 }, c1: {}, c2: {} },
    { p: { x: 1000, y: 0 }, c1: {}, c2: {} },
  ])
  // 点1 的 c2 属于段 1→2（长 800），点2 的 c1 也属于该段
  check('短段后的手柄不越界（c2 ≤ 下一点）', t[1].c2.x <= t[2].p.x + 1e-9, `c2=${t[1].c2.x}`)
  check('长段前的手柄不越界（c1 ≥ 上一点）', t[2].c1.x >= t[1].p.x - 1e-9, `c1=${t[2].c1.x}`)
  // 注意：限幅是**逐段独立**的，不等距控制点上手柄因此不再是 p 的对称镜像。
  // 对称性只在等距（且未触发限幅）时成立 —— 这里点 1/2 各有一段被限幅。
  check('点1 手柄被短段限幅（c2 不越界且不为默认值）',
    t[1].c2.x <= t[2].p.x + 1e-9 && t[1].c2.x > t[1].p.x)
  check('点2 手柄被短段限幅（c1 不越界且不为默认值）',
    t[2].c1.x >= t[1].p.x - 1e-9 && t[2].c1.x < t[2].p.x)
  {
    // 等距直线上没有限幅触发，此时**内部点**必须严格对称；
    // 首点的 c1、末点的 c2 被刻意退化到自身（防端点回勾），不参与对称性。
    const eq = recomputeHandles(defaultTrack(4, 900))
    const interior = eq.slice(1, -1)
    check('等距轨道内部点手柄对称于 p',
      interior.length > 0 && interior.every((q) =>
        near(q.c1.x + q.c2.x, 2 * q.p.x) && near(q.c1.y + q.c2.y, 2 * q.p.y)),
      JSON.stringify(interior.map((q) => [q.c1.x + q.c2.x, 2 * q.p.x])))
    check('等距轨道首点 c1 退化到自身', near(eq[0].c1.x, eq[0].p.x) && near(eq[0].c1.y, eq[0].p.y))
    check('等距轨道末点 c2 退化到自身',
      near(eq[eq.length - 1].c2.x, eq[eq.length - 1].p.x)
      && near(eq[eq.length - 1].c2.y, eq[eq.length - 1].p.y))
  }
  const s = sampleTrack(t, 32)
  check('不等距控制点仍有单调 x', s.pts.every((q, i) => i === 0 || q.x > s.pts[i - 1].x))
  check('不等距总长 = 1000', near(s.total, 1000, 1e-4), `实际 ${s.total}`)
}

/* 6. 按比例取点 */
{
  const t = defaultTrack(4, 1000)
  const s = sampleTrack(t, 32)
  check('u=0 取到起点', near(pointAtFraction(s, 0).x, 0))
  check('u=1 取到终点', near(pointAtFraction(s, 1).x, 1000))
  check('u=0.5 在中间', near(pointAtFraction(s, 0.5).x, 500, 1e-3))
  check('u 越界被夹取', near(pointAtFraction(s, -5).x, 0) && near(pointAtFraction(s, 9).x, 1000))
  check('直线切线角为 0', near(pointAtFraction(s, 0.5).angle, 0, 1e-9))
}

/* 7. u 与 x 单调对应 */
{
  const t = defaultTrack(3, 900)
  const s = sampleTrack(t, 24)
  const xs = [0, 0.1, 0.25, 0.5, 0.75, 0.9, 1].map((u) => pointAtFraction(s, u).x)
  check('u 与 x 单调对应', xs.every((v, i) => i === 0 || v > xs[i - 1]), JSON.stringify(xs))
}

/* 8. 均匀铺开：n 个航点按 evenFractions 排布时间距近似相等 */
{
  const t = defaultTrack(4, 1000)
  const s = sampleTrack(t, 64)
  const n = 6
  const us = Array.from({ length: n }, (_, i) => i / (n - 1))
  const xs = us.map((u) => pointAtFraction(s, u).x)
  const gaps = xs.slice(1).map((v, i) => v - xs[i])
  const maxGap = Math.max(...gaps)
  const minGap = Math.min(...gaps)
  check('航点沿直线均匀铺开', maxGap - minGap < 1e-3, `间距 ${gaps.map((g) => g.toFixed(2))}`)
}

/* 9. 命中测试 */
{
  const t = defaultTrack(4, 1000, 200)
  const s = sampleTrack(t, 32)
  const u = hitTrack(s, { x: 500, y: 200 }, 12)
  check('命中轨道并返回比例', u !== null && near(u, 0.5, 1e-3), `实际 ${u}`)
  check('远离轨道不命中', hitTrack(s, { x: 500, y: 400 }, 12) === null)
  const u0 = hitTrack(s, { x: 0, y: 200 }, 12)
  check('起点命中返回 0', u0 !== null && near(u0, 0, 1e-3), `实际 ${u0}`)
  const u1 = hitTrack(s, { x: 1000, y: 200 }, 12)
  check('终点命中返回 1', u1 !== null && near(u1, 1, 1e-3), `实际 ${u1}`)
  check('容差内命中', hitTrack(s, { x: 300, y: 208 }, 12) !== null)
  check('容差外不命中', hitTrack(s, { x: 300, y: 215 }, 12) === null)
}

/* 10. 命中比例随位置单调递增（决定右键加点的插入位置） */
{
  const t = defaultTrack(4, 1000)
  const s = sampleTrack(t, 32)
  const us = [50, 200, 400, 600, 800, 950].map((x) => hitTrack(s, { x, y: 0 }, 10))
  check('命中比例单调递增', us.every((v, i) => i === 0 || (v !== null && v > us[i - 1])), JSON.stringify(us))
}

/* 11. 距离函数 */
{
  check('点到线段距离-垂足在内', near(distToSegment({ x: 5, y: 3 }, { x: 0, y: 0 }, { x: 10, y: 0 }), 3))
  check('点到线段距离-垂足在外取端点',
    near(distToSegment({ x: 15, y: 0 }, { x: 0, y: 0 }, { x: 10, y: 0 }), 5))
  check('退化线段', near(distToSegment({ x: 3, y: 4 }, { x: 0, y: 0 }, { x: 0, y: 0 }), 5))
  check('closestT 夹取到 0~1',
    near(closestT({ x: -5, y: 0 }, { x: 0, y: 0 }, { x: 10, y: 0 }), 0)
    && near(closestT({ x: 20, y: 0 }, { x: 0, y: 0 }, { x: 10, y: 0 }), 1))
}

/* 12. 框选相交 */
{
  const box = { x: 0, y: 0, w: 10, h: 10 }
  check('完全包含', rectsIntersect(box, { x: 2, y: 2, w: 3, h: 3 }))
  check('部分重叠', rectsIntersect(box, { x: 8, y: 8, w: 5, h: 5 }))
  check('边角相接不算相交', !rectsIntersect(box, { x: 10, y: 10, w: 5, h: 5 }))
  check('完全分离', !rectsIntersect(box, { x: 20, y: 20, w: 5, h: 5 }))
}

/* 13. 边界与退化输入不抛异常 */
{
  const s1 = sampleTrack([], 8)
  check('空轨道采样安全', s1.pts.length === 0 && s1.total === 0)
  check('空轨道取点安全', pointAtFraction(s1, 0.5).x === 0)
  check('空轨道命中返回 null', hitTrack(s1, { x: 0, y: 0 }, 10) === null)
  const s2 = sampleTrack([{ p: { x: 5, y: 5 }, c1: { x: 5, y: 5 }, c2: { x: 5, y: 5 } }], 8)
  check('单点轨道无采样点', s2.pts.length === 0 && s2.total === 0)
  check('单点轨道不抛', (() => { try { recomputeHandles([{ p: { x: 0, y: 0 }, c1: {}, c2: {} }]); return true } catch { return false } })())
}

/* 14. 重合控制点不产生 NaN */
{
  const t = [
    { p: { x: 0, y: 0 }, c1: { x: 0, y: 0 }, c2: { x: 0, y: 0 } },
    { p: { x: 0, y: 0 }, c1: { x: 0, y: 0 }, c2: { x: 0, y: 0 } },
  ]
  const s = sampleTrack(t, 8)
  check('重合控制点无 NaN', s.pts.every((q) => Number.isFinite(q.x) && Number.isFinite(q.y)))
  const pt = pointAtFraction(s, 0.5)
  check('重合时取点无 NaN', Number.isFinite(pt.x) && Number.isFinite(pt.y))
  check('重合时切线角有限', Number.isFinite(pt.angle))
}

/* 15. 两控制点（最少可编辑轨道） */
{
  const t = defaultTrack(2, 500)
  const s = sampleTrack(t, 32)
  check('两点轨道总长 = 500', near(s.total, 500, 1e-6), `实际 ${s.total}`)
  check('两点轨道 c1/c2 退化在端点', near(t[0].c1.x, 0) && near(t[1].c2.x, 500))
}

/* 16. 随机扰动下不产生 NaN、不丢单调性（模糊测试） */
{
  let bad = 0
  const details = []
  for (let seed = 0; seed < 300; seed++) {
    // 简单线性同余，避免依赖随机源
    let r = seed * 1103515245 + 12345
    const rnd = () => { r = (r * 1103515245 + 12345) & 0x7fffffff; return (r % 10000) / 10000 }
    const n = 2 + (seed % 6)
    const pts = []
    for (let i = 0; i < n; i++) {
      pts.push({ p: { x: i * (1000 / (n - 1)), y: (rnd() - 0.5) * 400 }, c1: {}, c2: {} })
    }
    recomputeHandles(pts)
    const s = sampleTrack(pts, 16)
    if (!s.pts.every((q) => Number.isFinite(q.x) && Number.isFinite(q.y)) || !Number.isFinite(s.total)) {
      bad++
      details.push(`seed=${seed} 出现 NaN`)
      continue
    }
    if (!s.pts.every((q, i) => i === 0 || q.x >= s.pts[i - 1].x - 1e-6)) {
      bad++
      details.push(`seed=${seed} x 非单调`)
    }
  }
  check('300 组随机曲线：无 NaN 且 x 单调不减', bad === 0,
    `失败 ${bad} 组；样例：${details.slice(0, 3).join('; ')}`)
}

/* 17. 弧长 x (m) -> u：量程是**轨道总长**，不是航点自身的 min-max */
{
  const L = 55.04 // 一条 55.04 m 的轨道（真实数据量级）
  check('x=0 -> u=0', near(xToU(L, 0), 0))
  check('x=轨道总长 -> u=1', near(xToU(L, L), 1))
  check('中间值按米数比例', near(xToU(L, L / 2), 0.5, 1e-9))
  check('22.562 m 落在 41%（绝对值有意义，与别的航点在哪无关）',
    near(xToU(L, 22.562), 22.562 / L, 1e-9))

  // 超出轨道范围必须夹取，不能溢出（溢出会让 pointAtFraction 之外的计算全歪）
  check('超出轨道夹到 1', xToU(L, 99) === 1)
  check('负值夹到 0', xToU(L, -3) === 0)
  // 非有限值一律停在起点（不产生 NaN 坐标，也不会把点甩到终点）
  check('NaN -> 0（不产生 NaN 坐标）', xToU(L, NaN) === 0)
  check('Infinity -> 0', xToU(L, Infinity) === 0)

  // 没画轨道：量程为 0，一律停在起点而不是 NaN
  check('量程为 0 -> 0', xToU(0, 22.5) === 0)
  check('量程非法 -> 0', xToU(NaN, 22.5) === 0 && xToU(-1, 22.5) === 0)

  // uToX 是它的逆运算，拖完写回再读出来必须还是同一个位置
  check('uToX 是 xToU 的逆', near(uToX(L, xToU(L, 22.5)), 22.5, 1e-9))
  check('uToX 夹到 [0, L]', uToX(L, -1) === 0 && uToX(L, 2) === L)
  check('uToX 量程为 0 -> 0（不是 NaN）', uToX(0, 0.5) === 0)
  check('uToX NaN -> 0', uToX(L, NaN) === 0)

  // 同一条弧长在不同长度的轨道上 u 不同——这正是"单位是米"该有的行为
  check('同一 x 在更长的轨道上 u 更小',
    xToU(110, 22.5) < xToU(55.04, 22.5), `${xToU(110, 22.5)} vs ${xToU(55.04, 22.5)}`)

  // u 必须落在 [0,1]，否则航点会画到画布外
  const many = Array.from({ length: 50 }, (_, i) => 0.814 + i * (54.23 / 49))
  check('u 全在 [0,1]', many.every((x) => {
    const u = xToU(L, x)
    return u >= 0 && u <= 1
  }))
}

/* 17b. 里程取值：有轨道用弧长，没轨道退兜底量程 */
{
  check('trackLengthOf 有轨道用弧长', trackLengthOf(866.478, [1, 2, 3]) === 866.478)
  check('trackLengthOf 无轨道退兜底', trackLengthOf(0, [1, 55.04]) === 55.04)
  check('trackLengthOf 非法弧长退兜底', trackLengthOf(NaN, [1, 55.04]) === 55.04)
  check('fallbackLengthM 取最大值', fallbackLengthM([0.8, 12, 55.04]) === 55.04)
  check('fallbackLengthM 全为 0 时给下限', fallbackLengthM([0, 0]) === FALLBACK_MIN_M)
  check('fallbackLengthM 空数组给下限', fallbackLengthM([]) === FALLBACK_MIN_M)
  check('fallbackLengthM 跳过非有限值', fallbackLengthM([5, NaN, 90]) === 90)
  check('fallbackLengthM 结果不小于下限', fallbackLengthM([5, NaN, 9]) === FALLBACK_MIN_M)
  check('兜底量程不小于下限', fallbackLengthM([0.5]) === FALLBACK_MIN_M)
}

/* 18. 最近下标查找 */
{
  check('nearestIndex 空数组返回 -1', nearestIndex([], 0.5) === -1)
  check('nearestIndex 命中自身', nearestIndex([0, 0.5, 1], 0.5) === 1)
  check('nearestIndex 取更近的一侧', nearestIndex([0, 0.5, 1], 0.52) === 1)
  check('nearestIndex 越界夹到端点', nearestIndex([0, 0.5, 1], 9) === 2)
}

/* 19. 矩形规范化（框选时起止点顺序任意） */
{
  const r1 = normalizeRect({ x: 100, y: 80 }, { x: 20, y: 10 })
  check('反向拖拽得到正向矩形',
    r1.x === 20 && r1.y === 10 && r1.w === 80 && r1.h === 70,
    JSON.stringify(r1))
  const r2 = normalizeRect({ x: 10, y: 10 }, { x: 30, y: 40 })
  check('正向拖拽矩形不变',
    r2.x === 10 && r2.y === 10 && r2.w === 20 && r2.h === 30)
  const r3 = normalizeRect({ x: 5, y: 5 }, { x: 5, y: 5 })
  check('零面积矩形', r3.w === 0 && r3.h === 0)
  check('规范化的矩形可与航点包围盒相交判定',
    rectsIntersect(r1, { x: 30, y: 20, w: 10, h: 10 }))
}

/* 20. evenFractions */
{
  check('evenFractions(0) 为空', evenFractions(0).length === 0)
  check('evenFractions(1) 居中', near(evenFractions(1)[0], 0.5))
  const f = evenFractions(5)
  check('evenFractions 首尾为 0/1', near(f[0], 0) && near(f[4], 1))
  check('evenFractions 等距',
    f.slice(1).every((v, i) => near(v - f[i], 0.25)))
}

/* 21. 真实样例数据：航点 x -> u -> 曲线上取点，全程有限且 x 单调 */
{
  const xs = [0.814, 1.234, 2.089, 3.9, 5.2, 8.8, 12.1, 20.5, 33.3, 44.7, 55.04]
  // 轨道按真实尺寸画：55.04 m 的水平线，采样出来的弧长就是量程（米）
  const t = defaultTrack(4, 55.04)
  const s = sampleTrack(t, 48)
  const us = xs.map((x) => xToU(s.total, x))
  check('样例数据 u 单调递增（x 本身递增）', us.every((v, i) => i === 0 || v > us[i - 1]))
  check('最远航点落在轨道终点附近', us[us.length - 1] > 0.99, `u=${us[us.length - 1]}`)

  const pts = us.map((u) => pointAtFraction(s, u))
  check('所有航点都能取到曲线上的点', pts.every((q) => Number.isFinite(q.x) && Number.isFinite(q.y)))
  check('曲线上的航点横向单调（不交叉）', pts.every((q, i) => i === 0 || q.x > pts[i - 1].x + 1e-6))
  // 单位统一后：航点的横坐标（米）应当**就是**它的弧长 x，可以直接和刻度比
  check('航点横坐标 ≈ 弧长 x（米，同一把尺子）',
    pts.every((q, i) => near(q.x, xs[i], 0.05)),
    JSON.stringify(pts.map((q, i) => [q.x.toFixed(2), xs[i]])))

  // 弯曲轨道上仍然单调（这是"航点不左右乱排"的关键）
  const curved = defaultTrack(4, 55.04)
  curved[1].p.y = -12
  curved[2].p.y = 16
  recomputeHandles(curved)
  const cs = sampleTrack(curved, 48)
  const cp = xs.map((x) => xToU(cs.total, x)).map((u) => pointAtFraction(cs, u))
  check('弯曲轨道上航点仍横向单调', cp.every((q, i) => i === 0 || q.x > cp[i - 1].x - 1e-6),
    JSON.stringify(cp.map((q) => q.x.toFixed(1))))
}

/* 22. 提示栏「轨道总长」的格式化 */
{
  check('formatLength(0) 显示 —', formatLength(0) === '—')
  check('formatLength(NaN) 显示 —', formatLength(NaN) === '—')
  check('formatLength(Infinity) 显示 —', formatLength(Infinity) === '—')
  // 统一为米之后必须**带单位**，否则又会退回"这个数字到底是不是米"的困惑
  check('formatLength 大数不带小数', formatLength(1234.56) === '1235 m', formatLength(1234.56))
  check('formatLength 三位数不带小数', formatLength(100) === '100 m', formatLength(100))
  check('formatLength 两位数一位小数', formatLength(55.04) === '55.0 m', formatLength(55.04))
  check('formatLength 个位数一位小数', formatLength(8.88) === '8.9 m', formatLength(8.88))
  check('formatLength 小于 1 两位小数', formatLength(0.814) === '0.81 m', formatLength(0.814))
  check('formatLength 都带 m 后缀', [1234.56, 100, 55.04, 8.88, 0.814]
    .every((v) => formatLength(v).endsWith(' m')))

  check('spanText 少于两个值返回空', spanText([]) === '' && spanText([3]) === '')
  check('spanText 取 min~max（与顺序无关）',
    spanText([5, 1, 3]) === '1.0 m ~ 5.0 m', spanText([5, 1, 3]))
  check('spanText 跳过非有限值',
    spanText([2, NaN, 8, Infinity]) === '2.0 m ~ 8.0 m', spanText([2, NaN, 8, Infinity]))
  check('spanText 可换 formatter', spanText([1, 2], (v) => `${v}`) === '1 ~ 2')

  // 总长必须真的等于采样弧长，且**闭合时含收口段**（少算一截是老 bug）
  const open = sampleTrack(trackPointsFromNodes([
    { kind: 'endpoint', path: 'a', x: 0, y: 0 },
    { kind: 'endpoint', path: 'b', x: 300, y: 0 },
    { kind: 'endpoint', path: 'c', x: 300, y: 400 },
  ]), 48, false)
  check('开口轨道总长 = 300+400', near(open.total, 700, 1e-6), `实际 ${open.total}`)

  const closed = sampleTrack(trackPointsFromNodes([
    { kind: 'endpoint', path: 'a', x: 0, y: 0 },
    { kind: 'endpoint', path: 'b', x: 300, y: 0 },
    { kind: 'endpoint', path: 'c', x: 300, y: 400 },
    { kind: 'close', path: 'z', x: 0, y: 0 },
  ]), 48, true)
  check('闭合轨道多出收口段（3-4-5 直角边为 500）',
    near(closed.total, 1200, 1e-6), `实际 ${closed.total}`)
  check('闭合总长 > 开口总长', closed.total - open.total > 499)
  const p = parseTrackNodes([
    { kind: 'endpoint', path: 'a', x: 0, y: 0 },
    { kind: 'endpoint', path: 'b', x: 300, y: 0 },
    { kind: 'endpoint', path: 'c', x: 300, y: 400 },
    { kind: 'close', path: 'z', x: 0, y: 0 },
  ])
  check('parseTrackNodes 认出闭合', p.closed === true && p.endpoints.length === 3)
}

/* 23. 沿轨设施（充电桩 / RFID 卡）与航点共用同一把尺子：轨道总长 (m) */
{
  const L = 55.04 // 轨道真实长度
  // 关键契约：设施与航点**同一个量程**——20 m 既落在航点上、也落在设施该在的位置
  const uWp = xToU(L, 20)
  const uMarker = xToU(L, 20)
  check('设施与航点同量程（同 x 同 u）', near(uWp, uMarker) && near(uWp, 20 / L))

  // 反例：设施**各自**做 min-max 归一化会跑到完全不同的位置（旧实现写错过这里）。
  // 取 x=15（在 55.04 m 轨道上的 0.27 处）才看得出差别：单独归一化会给 0.5。
  const correct = xToU(L, 15)
  check('设施按轨道长度换算（不是自身归一化）', near(correct, 15 / L), `${correct}`)
  check('反例：单独归一化会错位到 0.5', !near(correct, 0.5), `${correct}`)

  // 采样取点：设施落在与同 x 航点相同的曲线位置
  const t = defaultTrack(4, 55.04)
  const s = sampleTrack(t, 48)
  const pWp = pointAtFraction(s, xToU(s.total, 20))
  const pMarker = pointAtFraction(s, xToU(s.total, 20))
  check('同 x 的航点与设施落在同一处', near(pWp.x, pMarker.x) && near(pWp.y, pMarker.y))

  // 拖完写回：量程与数据无关，写进去再读出来必须还是同一个 u（松手即所得）
  const dropped = uToX(L, 0.41)
  check('拖到 41% 处写回的 x，再读回仍是 41%', near(xToU(L, dropped), 0.41, 1e-9))
  // 这条在旧 min-max 实现下是不成立的（极值点会弹回端点）
  check('拖到端点也能精确写回', near(xToU(L, uToX(L, 1)), 1) && near(xToU(L, uToX(L, 0)), 0))
}

/* 24. 背景图矩形（锚点 + 缩放，不拉伸变形） */
{
  const bg = { path: 'root/children/0', src: '/data/x.png', x: -100, y: -50, scale: 0.5, opacity: 0.5 }
  const r = backgroundRect(bg, 800, 400)
  check('backgroundRect 锚点是左上角', r.x === -100 && r.y === -50)
  // 宽高都乘同一个 scale —— 这是"不拉伸变形"的核心
  check('backgroundRect 宽高 = 像素 × scale', r.w === 400 && r.h === 200)
  check('backgroundRect 保持图片长宽比', near(r.w / r.h, 800 / 400))

  const r2 = backgroundRect({ ...bg, scale: 2 }, 800, 400)
  check('scale 翻倍则宽高翻倍', r2.w === 1600 && r2.h === 800)
  check('缩放只改变尺寸，不改变锚点', r2.x === -100 && r2.y === -50)

  // 坏数据一律返回 null：调用方拿到 null 就不画，比画出一个 NaN 矩形把
  // 画布搞崩（NaN 会让 drawImage 直接抛）要安全得多
  check('图片未加载（尺寸 0）-> null', backgroundRect(bg, 0, 400) === null)
  check('负尺寸 -> null', backgroundRect(bg, -800, 400) === null)
  check('scale <= 0 -> null',
    backgroundRect({ ...bg, scale: 0 }, 800, 400) === null
    && backgroundRect({ ...bg, scale: -1 }, 800, 400) === null)
  check('锚点非有限值 -> null',
    backgroundRect({ ...bg, x: NaN }, 800, 400) === null
    && backgroundRect({ ...bg, y: Infinity }, 800, 400) === null)
  check('scale 非有限值 -> null', backgroundRect({ ...bg, scale: NaN }, 800, 400) === null)

  // scale = 米/像素：铺满多少米 / 图片像素宽。铺满 1000 m 的图（宽 1000px）-> scale = 1
  const fitted = backgroundRect({ ...bg, x: 0, y: 0, scale: 1000 / 1000 }, 1000, 500)
  check('scale = 米/像素：铺满米数 / 图片宽', near(fitted.w, 1000))

  /* 拖右下角手柄缩放：锚点 (0,0)、图 800×400 时，把角拖到 (1200,600) 应为 1.5 */
  const s1 = backgroundScaleAt({ ...bg, x: 0, y: 0 }, 800, 400, { x: 1200, y: 600 })
  check('手柄缩放：等比拖动', near(s1, 1.5), `实际 ${s1}`)
  // 横竖不一致时取大者：斜着拖手抖一下不至于把图缩回去
  const s2 = backgroundScaleAt({ ...bg, x: 0, y: 0 }, 800, 400, { x: 1200, y: 200 })
  check('手柄缩放：横竖不一致取大者', near(s2, 1.5), `实际 ${s2}`)
  const s3 = backgroundScaleAt({ ...bg, x: 0, y: 0 }, 800, 400, { x: 400, y: 800 })
  check('手柄缩放：竖向更大时按高算', near(s3, 2), `实际 ${s3}`)
  // 锚点不在原点时算的是"相对锚点"的距离，不能把锚点当 0
  const s4 = backgroundScaleAt({ ...bg, x: 100, y: 100 }, 800, 400, { x: 500, y: 300 })
  check('手柄缩放：按相对锚点计算', near(s4, 0.5), `实际 ${s4}`)
  // 拖到锚点左边/上方（负缩放）必须被夹住，不能出现负尺寸
  const s5 = backgroundScaleAt({ ...bg, x: 0, y: 0 }, 800, 400, { x: -800, y: -400 })
  check('手柄缩放：负值夹到下限', s5 > 0 && s5 <= 0.001, `实际 ${s5}`)
  // 图没加载出来（尺寸 0）时保持原值，绝不返回 NaN（NaN 会让 drawImage 抛异常）
  const s6 = backgroundScaleAt({ ...bg, scale: 0.75 }, 0, 0, { x: 100, y: 100 })
  check('手柄缩放：尺寸未知时保持原值', s6 === 0.75, `实际 ${s6}`)
  const s7 = backgroundScaleAt({ ...bg, scale: 0.75 }, 800, 400, { x: NaN, y: NaN })
  check('手柄缩放：指针坐标非法时保持原值', s7 === 0.75, `实际 ${s7}`)
}

/* 25. 区段标记（门 / 窗 / 减速…）：x ± 半径 的一段弧长 */
{
  const L = 40                              // 轨道真实长度 40 m
  const r = sectionRange(L, { x: 20, radius: 5 })
  check('sectionRange 中心 ± 半径', near(r.u0, 15 / 40) && near(r.u1, 25 / 40), JSON.stringify(r))
  check('sectionRange 区间非空且有序', r.u0 < r.u1)

  const r0 = sectionRange(L, { x: 20, radius: 0 })
  check('sectionRange 半径为 0 退化成一点', r0.u0 === r0.u1 && near(r0.u0, 0.5))
  // 半径不能是负的（检视器里有 min=0.01，但手改 JSON 可能填负）
  const rNeg = sectionRange(L, { x: 20, radius: -3 })
  check('sectionRange 负半径当 0 处理', rNeg.u0 === rNeg.u1 && near(rNeg.u0, 0.5))
  const rNaN = sectionRange(L, { x: 20, radius: NaN })
  check('sectionRange 半径非法当 0 处理', rNaN.u0 === rNaN.u1)

  // 区段伸到轨道外要夹住，不能溢出（溢出会让整条带子画到画布外）
  const rOut = sectionRange(L, { x: 12, radius: 40 })
  check('sectionRange 超出轨道夹到 0/1', rOut.u0 === 0 && rOut.u1 === 1, JSON.stringify(rOut))
  // 关键：量程缺失时返回 null（画不出区间）——退化成 0 会让所有区段堆在轨道起点
  check('sectionRange 量程为 0 -> null', sectionRange(0, { x: 20, radius: 5 }) === null)
  check('sectionRange 量程非法 -> null',
    sectionRange(NaN, { x: 20, radius: 5 }) === null
    && sectionRange(-1, { x: 20, radius: 5 }) === null)
  check('sectionRange 中心非法 -> null',
    sectionRange(L, { x: NaN, radius: 5 }) === null
    && sectionRange(L, { x: Infinity, radius: 5 }) === null)

  // 与航点同一把尺子：同 x 的航点与区段中心必须落在同一个 u
  const uWp = xToU(L, 20)
  const uSec = (sectionRange(L, { x: 20, radius: 0 }).u0)
  check('区段与航点同量程（同 x 同 u）', near(uWp, uSec))

  const t = defaultTrack(4, 40)
  const s = sampleTrack(t, 48)
  const pts = sectionPoints(s, 0.25, 0.75)
  check('sectionPoints 点数 = per+1', pts.length === 25, String(pts.length))
  // 端点必须与 pointAtFraction 一致，否则带子会和轨道错开
  check('sectionPoints 起点对齐',
    near(pts[0].x, pointAtFraction(s, 0.25).x) && near(pts[0].y, pointAtFraction(s, 0.25).y))
  check('sectionPoints 终点对齐',
    near(pts[pts.length - 1].x, pointAtFraction(s, 0.75).x))
  check('sectionPoints 沿轨单调不回退',
    pts.every((p, i) => i === 0 || p.x >= pts[i - 1].x))
  // 退化为一点时给两个相同点：配合 round 线帽能画出一个圆点（而不是整段消失）
  const dot = sectionPoints(s, 0.5, 0.5)
  check('sectionPoints 退化成一点仍返回 2 点',
    dot.length >= 2 && near(dot[0].x, dot[dot.length - 1].x))
  check('sectionPoints 逆序输入也能画', sectionPoints(s, 0.75, 0.25).length === 25)
  check('sectionPoints 越界 u 夹取', sectionPoints(s, -1, 2).length === 25)
}

rmSync(outDir, { recursive: true, force: true })
console.log(`\n通过 ${pass} 项断言`)
if (failures.length) {
  console.log(`\n失败 ${failures.length} 项：`)
  failures.forEach((f) => console.log('  ✗ ' + f))
  process.exit(1)
}
console.log('全部通过 ✓\n')
