/**
 * 抓拍图路径解析 + 拖拽投影回归。
 *
 * 两块内容放在一个脚本里，因为它们服务于同一个功能：
 * 「航点右键创建拍照动作点 → 图存到 prefab 旁的 images/ → imageUrl 记相对路径」
 * 与「地图上拖着航点沿轨道走」。前者是纯路径拼接，后者是拖拽时把指针投影
 * 回轨道（`nearestU`）——都容易在换目录层级 / 指针离开轨道时暴露问题。
 *
 * 关键：**不从源码手抄函数**，用 tsc 把真实 .ts 编译到临时目录再 import。
 * 运行：node scripts/verify-prefab-image.mjs
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

/** 编译单个 .ts 到独立临时目录（各自一个 rootDir，输出路径才确定） */
function compile(relTs) {
  const outDir = mkdtempSync(join(tmpdir(), 'pi-'))
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
  // 没有 package.json 时 node 会先按 CJS 解析再回退 ESM，刷一堆警告
  writeFileSync(join(outDir, 'package.json'), JSON.stringify({ type: 'module' }))
  const name = relTs.split('/').pop().replace(/\.ts$/, '.js')
  return import(pathToFileURL(join(outDir, name)).href)
}

const img = await compile('src/utils/prefabImage.ts')
const geo = await compile('src/components/trackGeometry.ts')
const { prefabDir, isAbsoluteImage, resolveImageUrl, PREFAB_STATIC_PREFIX, CAPTURE_SUBDIR } = img
const {
  defaultTrack, sampleTrack, pointAtFraction, hitTrack, nearestU,
  parseTrackNodes, trackPointsFromNodes, xToU, uToX, trackLengthOf,
} = geo

/* ---- 断言 ---- */

let pass = 0
const failures = []
function check(name, cond, extra = '') {
  if (cond) { pass++; return }
  failures.push(`${name} ${extra}`)
}
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps

/* ============ 1. prefabDir ============ */

check('根目录 prefab 没有目录部分', prefabDir('a.prefab.json') === '')
check('一层目录', prefabDir('sub/a.prefab.json') === 'sub')
check('多层目录', prefabDir('x/y/z.prefab.json') === 'x/y')
check('反斜杠也认（Windows 手改过的数据）', prefabDir('x\\y\\z.prefab.json') === 'x/y')
check('空输入不炸', prefabDir('') === '' && prefabDir(null) === '' && prefabDir(undefined) === '')
check('非字符串不炸', prefabDir(123) === '')

/* ============ 2. isAbsoluteImage ============ */

check('http 是绝对', isAbsoluteImage('http://x.com/a.jpg'))
check('https 是绝对', isAbsoluteImage('https://x.com/a.jpg'))
check('协议相对是绝对', isAbsoluteImage('//x.com/a.jpg'))
check('根路径是绝对', isAbsoluteImage('/data/calibration/a.jpg'))
check('data URI 是绝对', isAbsoluteImage('data:image/png;base64,AAA'))
check('相对路径不是绝对', !isAbsoluteImage('images/a.jpg'))

/* ============ 3. resolveImageUrl ============ */

const P = PREFAB_STATIC_PREFIX
check('相对路径拼上目录', resolveImageUrl('images/a.jpg', 'sub/tree.prefab.json')
  === `${P}/sub/images/a.jpg`)
check('根目录 prefab 不留双斜杠', resolveImageUrl('images/a.jpg', 'tree.prefab.json')
  === `${P}/images/a.jpg`)
check('多层目录', resolveImageUrl('images/a.jpg', 'x/y/tree.prefab.json')
  === `${P}/x/y/images/a.jpg`)
check('./ 前缀归一化', resolveImageUrl('./images/a.jpg', 'sub/t.prefab.json')
  === `${P}/sub/images/a.jpg`)
check('空值返回空串（别把空串塞给 img）', resolveImageUrl('', 'a.prefab.json') === '')
check('空白串返回空串', resolveImageUrl('   ', 'a.prefab.json') === '')
check('null/undefined 返回空串', resolveImageUrl(null, 'a.prefab.json') === ''
  && resolveImageUrl(undefined, 'a.prefab.json') === '')
check('绝对地址原样返回', resolveImageUrl('https://x/a.jpg', 'sub/t.prefab.json') === 'https://x/a.jpg')
check('根路径原样返回', resolveImageUrl('/data/calibration/bg/x.png', 'sub/t.prefab.json')
  === '/data/calibration/bg/x.png')
check('后端 /capture 返回的 rel 能直接解析',
  resolveImageUrl(`${CAPTURE_SUBDIR}/cap_1234.jpg`, 'floor1/t.prefab.json')
  === `${P}/floor1/${CAPTURE_SUBDIR}/cap_1234.jpg`)

/* ============ 4. nearestU：拖拽投影 ============ */

const nodes = defaultTrack(4, 900, 0)
const parsed = parseTrackNodes(
  nodes.map((n, i) => ({ path: `root/children/0/children/${i}`, x: n.p.x, y: n.p.y })),
)
const pts = trackPointsFromNodes(
  nodes.map((n, i) => ({ path: `root/children/0/children/${i}`, x: n.p.x, y: n.p.y })),
)
const sampled = sampleTrack(pts, 48, parsed.closed)
const tol = 12

check('采样成功', sampled.pts.length > 2 && sampled.total > 0)

/* 轨道上一点：nearestU 与 hitTrack 都给得出 u，且一致 */
const onTrack = pointAtFraction(sampled, 0.4)
const uOn = nearestU(sampled, onTrack)
check('轨道上能投影', uOn != null)
check('轨道上投影接近原 u', near(uOn, 0.4, 0.02), `uOn=${uOn}`)
check('轨道上 hitTrack 也给得出', hitTrack(sampled, onTrack, tol) != null)

/* 关键差异：指针离开轨道时 hitTrack 断掉、nearestU 仍然给 u。
   拖拽时指针常常在轨道外侧（把点往外推 / 手抖），用带阈值的 hitTrack
   会让点"卡住不动"。 */
const offTrack = { x: onTrack.x, y: onTrack.y + 400 }
const uOff = nearestU(sampled, offTrack)
check('远离轨道时 hitTrack 断掉（阈值生效）', hitTrack(sampled, offTrack, tol) === null)
check('远离轨道时 nearestU 仍给得出 u（拖拽不断线）', uOff != null)
check('远离轨道时的投影仍在 [0,1]', uOff >= 0 && uOff <= 1, `uOff=${uOff}`)
check('垂直外推不改变沿轨位置', near(uOff, uOn, 0.03), `uOff=${uOff} uOn=${uOn}`)

/* 沿轨道方向移动指针，投影必须单调跟着走 */
const us = [0.1, 0.25, 0.5, 0.75, 0.9].map((t) => {
  const p = pointAtFraction(sampled, t)
  // 稍微离开轨道（+60 世界单位），模拟拖拽时指针在轨道外侧
  return nearestU(sampled, { x: p.x, y: p.y + 60 })
})
let mono = true
for (let i = 1; i < us.length; i++) if (!(us[i] > us[i - 1])) mono = false
check('沿轨移动指针，投影单调递增', mono, JSON.stringify(us))
check('起点投影接近 0.1', near(us[0], 0.1, 0.04), `${us[0]}`)
check('终点投影接近 0.9', near(us[4], 0.9, 0.04), `${us[4]}`)

/* 退化：只有一个点时 sampleTrack 给不出段，nearestU 应当返回 null 而不是 NaN */
const tiny = sampleTrack([{ p: { x: 0, y: 0 }, c1: { x: 0, y: 0 }, c2: { x: 0, y: 0 } }], 8, false)
const uTiny = nearestU(tiny, { x: 5, y: 5 })
check('单点轨道投影为 null 而不是 NaN', uTiny === null || Number.isFinite(uTiny), `${uTiny}`)

/* ============ 5. 拖拽闭环：u -> 画出来的位置 -> 再投影回来 ============ */
/* 拖到哪儿画到哪儿：用 u 落点画、再把画出来的点投影回去，应当回到同一个 u。
   对不上就说明"画的映射"和"拖的映射"不是同一套，松手瞬间会跳。 */
let roundTripOk = true
for (const t of [0, 0.2, 0.45, 0.7, 1]) {
  const p = pointAtFraction(sampled, t)
  const back = nearestU(sampled, p)
  if (back == null || Math.abs(back - t) > 0.02) roundTripOk = false
}
check('u -> 落点 -> u 闭环一致', roundTripOk)

/* ============ 6. 拖完写回的 x：往返必须还在松手位置（量程 = 轨道总长，米） ============ */

/** 一条 55.04 m 的轨道（真实数据量级）：量程与数据无关，是"米"这把尺子本身 */
const L = 55.04

/** 拖到 u 写回 x，再按同一个量程读回 u（= 用户实际看到的落点） */
function afterDrag(xs, i, u) {
  const x = uToX(L, u)
  const next = xs.slice()
  next[i] = x
  return { x, u: xToU(L, x), next }
}

/* 中间点 */
{
  const xs = [0, 5, 10]
  const r = afterDrag(xs, 1, 0.3)
  check('中间点拖到 0.3 -> x = 0.3 × 轨道长度', r && near(r.x, L * 0.3, 1e-9), JSON.stringify(r))
  check('中间点落点 == 0.3（不弹回）', r && near(r.u, 0.3, 1e-9), JSON.stringify(r))
}

/* 首点（u=0 的极值点）：量程与数据无关，照样拖得动（旧 min-max 实现会弹回起点） */
{
  const r = afterDrag([0, 5, 10], 0, 0.2)
  check('首点拖到 0.2 -> x = 0.2 × 轨道长度', near(r.x, L * 0.2, 1e-9), JSON.stringify(r))
  check('首点落点 == 0.2（不再弹回起点）', near(r.u, 0.2, 1e-9), JSON.stringify(r))
}

/* 末点（u=1 的极值点）：同理 */
{
  const r = afterDrag([0, 5, 10], 2, 0.6)
  check('末点落点 == 0.6（不再弹回终点）', near(r.u, 0.6, 1e-9), JSON.stringify(r))
}

/* 拖到端点是**合法**的（贴到轨道尽头），不再是"拖不动" */
check('拖到 u=0 -> x=0', near(uToX(L, 0), 0))
check('拖到 u=1 -> x=轨道总长', near(uToX(L, 1), L))
check('拖过终点也夹住（u=1.4）', near(uToX(L, 1.4), L))
check('拖过起点也夹住（u=-0.2）', near(uToX(L, -0.2), 0))

/* 退化：绝不出 NaN */
check('量程为 0 -> x=0（不是 NaN）', uToX(0, 0.5) === 0)
check('u 为 NaN -> x=0（不是 NaN）', uToX(L, NaN) === 0)
check('量程非法 -> x=0', uToX(NaN, 0.5) === 0)

/* 关键改进：改一个点的 x **不会挪动别的点**
   （旧 min-max 实现里量程取自航点自身，动一个点会整体重排，
   还会把充电桩/区段的对齐一起带歪） */
{
  const xs = [0.8, 12, 25, 40, 54.5]
  const before = xs.map((x) => xToU(L, x))
  const moved = xs.slice()
  moved[0] = uToX(L, 0.9) // 把首点一路拖到接近终点
  const after = moved.map((x) => xToU(L, x))
  check('拖动一个点，其余点位置纹丝不动',
    after.slice(1).every((u, i) => near(u, before[i + 1], 1e-9)),
    JSON.stringify({ before, after }))
  check('被拖的点确实到了 0.9', near(after[0], 0.9, 1e-9), `${after[0]}`)
}

/* 没画轨道时退回兜底量程，也能正常反推 */
{
  const fb = trackLengthOf(0, [0.8, 12, 55.04])
  check('无轨道时量程 = 最远航点弧长', near(fb, 55.04, 1e-9), `${fb}`)
  check('无轨道时拖到 0.5 -> x = 27.52', near(uToX(fb, 0.5), 27.52, 1e-9))
}

/* 穷举：往返一致 */
{
  const xs = [0.8, 12, 25, 40, 54.5]
  let worst = 0
  let n = 0
  for (let i = 0; i < xs.length; i++) {
    for (let k = 0; k <= 20; k++) {
      const t = k / 20
      const r = afterDrag(xs, i, t)
      n++
      worst = Math.max(worst, Math.abs(r.u - t))
    }
  }
  check(`穷举 ${n} 个落点全部精确（最大误差 ${worst.toExponential(2)}）`, worst < 1e-9)
  check('确实穷举到了足够多的落点', n >= 100, `n=${n}`)
}

/* ---- 结果 ---- */
console.log(`\n抓拍图路径 + 拖拽投影回归：${pass} 项通过，${failures.length} 项失败`)
if (failures.length) {
  for (const f of failures) console.log('  ✗', f)
  process.exit(1)
}
console.log('全部通过 ✓')
