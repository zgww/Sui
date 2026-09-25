/**
 * 非模态浮动窗口的位置数学回归（绑定测点窗口在用它）。
 *
 * 与 verify-track-geometry.mjs 同一套路：**不手抄源码**，用 tsc 把
 * src/utils/windowDrag.ts 编到临时目录再 import。
 * 运行：node scripts/verify-window-drag.mjs
 *
 * 这里锁的是"拖一下就找不着窗口"那类数值 bug：视口比窗口还窄时上下界交叉、
 * 位移累加丢步、底部留白不够导致窗口整个沉到屏幕外。
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'wdg-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath,
    [tscEntry, 'src/utils/windowDrag.ts', '--outDir', out,
      '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
      '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

const {
  WIN_W, WIN_H, EDGE, BOTTOM_KEEP, MIN_W, MIN_H,
  clampPos, defaultPos, dragTo, clampSize, defaultSize, resizeTo,
} = await import(pathToFileURL(join(out, 'windowDrag.js')).href)

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n}${extra ? ' — ' + extra : ''}`) }
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps
const same = (p, x, y, what) => check(what, near(p.x, x) && near(p.y, y), `得到 (${p.x},${p.y}) 期望 (${x},${y})`)
const sameSize = (s, w, h, what) => check(what, near(s.w, w) && near(s.h, h), `得到 ${s.w}x${s.h} 期望 ${w}x${h}`)

/** 常见桌面视口 */
const VP = { w: 1600, h: 900 }

/* ============================================================
 * 1. 夹取：正常视口
 * ============================================================ */
{
  same(clampPos(300, 200, VP), 300, 200, '视口内的位置原样返回')
  same(clampPos(-500, 200, VP), EDGE, 200, '左边拖过头夹到 EDGE')
  same(clampPos(-500, -500, VP), EDGE, EDGE, '左上角拖过头两个方向都夹')
  const right = VP.w - WIN_W - EDGE
  same(clampPos(9999, 200, VP), right, 200, '右边拖过头夹到 w-W-EDGE')
  const bottom = VP.h - BOTTOM_KEEP
  same(clampPos(300, 9999, VP), 300, bottom, '下边拖过头留得住标题栏')
  same(clampPos(9999, 9999, VP), right, bottom, '右下角两个方向都夹')

  // 幂等：夹过一次再夹一次不变（否则 resize 反复触发会越夹越偏）
  const once = clampPos(9999, 9999, VP)
  same(clampPos(once.x, once.y, VP), once.x, once.y, '夹取是幂等的')
}

/* ============================================================
 * 2. 退化视口：上下界交叉是这类窗口最经典的坑
 *    没有 Math.max(EDGE, ...) 兜底时，maxX < EDGE，
 *    Math.min(Math.max(x, EDGE), maxX) 会取到更小（更靠左/上）的值，
 *    窗口反而被推得更远。
 * ============================================================ */
{
  // 比窗口还窄：x 的上下界交叉（maxX < EDGE），靠 Math.max(EDGE, ...) 兜成"贴左边"；
  // y 的上下界没交叉，所以该是多少就是多少（300-120=180），别顺手也压成 EDGE
  const tiny = { w: 400, h: 300 }
  same(clampPos(9999, 9999, tiny), EDGE, tiny.h - BOTTOM_KEEP, '视口比窗口窄：贴左边而不是被推出去')
  check('窄视口下 x 不小于 EDGE', clampPos(9999, 9999, tiny).x >= EDGE)

  const flat = { w: 1600, h: 60 }          // 比 BOTTOM_KEEP 还矮
  same(clampPos(0, 9999, flat), EDGE, EDGE, '视口很矮：y 夹到 EDGE 而不是负数')

  // 正好放得下（w = WIN_W + 2*EDGE）：maxX == EDGE，此时只有唯一合法 x
  const exact = { w: WIN_W + 2 * EDGE, h: 900 }
  same(clampPos(500, 300, exact), EDGE, 300, '刚好放得下时只有唯一合法 x')
  // 稍微宽一点就能挪动了
  const roomy = { w: WIN_W + 2 * EDGE + 200, h: 900 }
  same(clampPos(500, 300, roomy), 208, 300, '有富余时按实际位置放')
}

/* ============================================================
 * 3. 默认位置：水平居中、靠上
 * ============================================================ */
{
  const p = defaultPos(VP)
  same(p, Math.round((VP.w - WIN_W) / 2), 84, '默认位置水平居中、y=84')
  const p2 = defaultPos({ w: 400, h: 300 })
  check('窄视口下默认位置也夹得住', p2.x >= EDGE && p2.y >= EDGE, `(${p2.x},${p2.y})`)
}

/* ============================================================
 * 4. 拖动：起点 + 总位移（绝对计算）
 * ============================================================ */
{
  const base = { x: 200, y: 100 }
  const start = { x: 500, y: 400 }

  same(dragTo(base, start, start, VP), 200, 100, '没位移就不动')
  same(dragTo(base, start, { x: 530, y: 380 }, VP), 230, 80, '按总位移平移')
  same(dragTo(base, start, { x: 470, y: 420 }, VP), 170, 120, '反方向也能拖')

  const mid = { x: 530, y: 380 }
  const end = { x: 560, y: 360 }
  const once = dragTo(base, start, end, VP)
  same(once, 260, 60, '最终位置 = 起点 + 总位移')

  // 同一帧来两个 mousemove。正解是**每次都用按下那一刻的快照当 base**
  // （组件里就是 dragRef 存的那份），中间帧只是白算一遍：
  let fixed = base
  for (const now of [mid, end]) fixed = dragTo(base, start, now, VP)
  same(fixed, once.x, once.y, 'base 恒为按下快照：中间帧不影响结果')

  // 反例：把上一帧的结果当 base 就是累加，位移会多算一截。
  // 这条断言同时证明上面那条不是空断言（两种写法结果确实不同）。
  let acc = base
  for (const now of [mid, end]) acc = dragTo(acc, start, now, VP)
  check('增量累加的写法结果不同（所以必须传同一个 base）',
    !near(acc.x, once.x) || !near(acc.y, once.y), `累加得 (${acc.x},${acc.y})`)

  // 一路拖出视口：还是得夹回来
  const outP = dragTo(base, start, { x: 5000, y: 5000 }, VP)
  same(outP, VP.w - WIN_W - EDGE, VP.h - BOTTOM_KEEP, '拖出视口后被夹住')
  // 往左上拖出视口
  const outL = dragTo(base, start, { x: -5000, y: -5000 }, VP)
  same(outL, EDGE, EDGE, '往左上拖出视口后被夹住')

  // 顺序无关：中途多绕几下，只要手停在同一个点，位置就一样
  let wander = base
  for (const now of [{ x: 505, y: 395 }, { x: 600, y: 300 }, end]) {
    wander = dragTo(base, start, now, VP)
  }
  same(wander, once.x, once.y, '拖动只认起点和当前点，与中途绕的路无关')
}

/* ============================================================
 * 5. 尺寸夹取：右下角最多拖到视口边，所以上界跟**窗口位置**有关
 * ============================================================ */
{
  const pos = { x: 520, y: 84 }                 // 默认位置
  // maxW = 1600-520-8 = 1072，maxH = 900-84-8 = 808
  sameSize(clampSize(WIN_W, WIN_H, pos, VP), 560, 520, '默认尺寸放得下就原样返回')
  sameSize(clampSize(9999, 9999, pos, VP), 1072, 808, '拉过头夹到"视口边 - 窗口左上角"')
  sameSize(clampSize(1, 1, pos, VP), MIN_W, MIN_H, '缩过头夹到下限')

  // 幂等：夹过一次再夹一次不变（组件里 pos 一变就要重夹，非幂等会越夹越小）
  const once = clampSize(9999, 9999, pos, VP)
  sameSize(clampSize(once.w, once.h, pos, VP), once.w, once.h, '尺寸夹取是幂等的')

  /* 上下界交叉：窗口被拖到很右 / 很下时，`视口边 - 窗口左上` 会**小于下限**。
     没有 `Math.max(MIN_W, maxW)` 兜底就会夹出一个比下限还小（甚至负数）的窗口，
     标题栏和两个按钮直接挤没了。 */
  sameSize(clampSize(9999, 9999, { x: 1300, y: 84 }, VP), MIN_W, 808,
    '窗口贴右边：宽兜成下限而不是负数')
  sameSize(clampSize(9999, 9999, { x: 520, y: 850 }, VP), 1072, MIN_H,
    '窗口贴下边：高兜成下限而不是负数')
  sameSize(clampSize(1, 1, { x: 1590, y: 890 }, VP), MIN_W, MIN_H, '右下角两边都交叉')

  // 不管怎么夹，尺寸永远是正的、且不小于下限
  let ok = true
  for (const x of [0, 8, 520, 1032, 1300, 1600]) {
    for (const y of [0, 84, 500, 780, 900]) {
      for (const [w, h] of [[0, 0], [560, 520], [9999, 9999]]) {
        const s = clampSize(w, h, { x, y }, VP)
        if (!(s.w >= MIN_W && s.h >= MIN_H)) { ok = false; break }
      }
    }
  }
  check('任意位置 / 任意尺寸夹出来都 >= 下限', ok)

  // 上界确实随位置变化（不然"贴右边时能拉多宽"就算错了）
  check('上界跟着窗口位置走',
    clampSize(9999, 9999, { x: 100, y: 84 }, VP).w > clampSize(9999, 9999, { x: 900, y: 84 }, VP).w)
  check('上界跟着窗口高度位置走',
    clampSize(9999, 9999, { x: 520, y: 100 }, VP).h > clampSize(9999, 9999, { x: 520, y: 700 }, VP).h)
}

/* ============================================================
 * 6. 默认尺寸：默认那套，按视口夹一次
 * ============================================================ */
{
  const p = defaultPos(VP)
  sameSize(defaultSize(VP, p), WIN_W, WIN_H, '常见视口下就是默认尺寸')
  // 矮视口：h 先被"视口高 - 上下留白"压一次，再进 clampSize
  const short = { w: 1600, h: 420 }
  const sp = defaultPos(short)
  const ss = defaultSize(short, sp)
  const wantShort = clampSize(WIN_W, short.h - 2 * BOTTOM_KEEP, sp, short)
  sameSize(ss, wantShort.w, wantShort.h, '矮视口下按可用高度压')
  check('矮视口下高度不小于下限', ss.h >= MIN_H, `${ss.h}`)

  // 极小视口：上下界交叉，兜成下限（窗口会比视口大，但总比 0 强）
  const tiny = { w: 400, h: 300 }
  const tp = defaultPos(tiny)
  const ts = defaultSize(tiny, tp)
  check('极小视口下尺寸也是正的', ts.w >= MIN_W && ts.h >= MIN_H, `${ts.w}x${ts.h}`)
}

/* ============================================================
 * 7. 缩放：起点尺寸 + 总位移（跟拖动一个道理，绝对计算）
 * ============================================================ */
{
  const base = { w: 560, h: 520 }
  const pos = { x: 200, y: 100 }
  const start = { x: 500, y: 400 }

  sameSize(resizeTo(base, start, start, pos, VP), 560, 520, '没位移就不变')
  sameSize(resizeTo(base, start, { x: 560, y: 460 }, pos, VP), 620, 580, '按总位移放大')
  sameSize(resizeTo(base, start, { x: 480, y: 380 }, pos, VP), 540, 500, '往左上拖是缩小')

  const mid = { x: 560, y: 460 }
  const end = { x: 600, y: 500 }
  const once = resizeTo(base, start, end, pos, VP)
  sameSize(once, 660, 620, '最终尺寸 = 起点尺寸 + 总位移')

  // 同一帧来两个 mousemove：base 恒为按下那一刻的快照，中间帧只是白算一遍
  let fixed = base
  for (const now of [mid, end]) fixed = resizeTo(base, start, now, pos, VP)
  sameSize(fixed, once.w, once.h, 'base 恒为按下快照：中间帧不影响结果')

  // 反例：把上一帧当 base 就是累加，尺寸会多涨一截（这条证明上面不是空断言）
  let acc = base
  for (const now of [mid, end]) acc = resizeTo(acc, start, now, pos, VP)
  check('增量累加的写法结果不同（所以必须传同一个 base）',
    !near(acc.w, once.w) || !near(acc.h, once.h), `累加得 ${acc.w}x${acc.h}`)

  // 缩到最小、拉到最大都夹得住
  sameSize(resizeTo(base, start, { x: -5000, y: -5000 }, pos, VP), MIN_W, MIN_H, '缩到底夹到下限')
  sameSize(resizeTo(base, start, { x: 5000, y: 5000 }, pos, VP),
    VP.w - pos.x - EDGE, VP.h - pos.y - EDGE, '拉到底夹到视口边')

  // 只动 x / 只动 y：另一个方向不该跟着变
  const onlyX = resizeTo(base, start, { x: 600, y: start.y }, pos, VP)
  check('只横拖不改高度', near(onlyX.h, base.h), `${onlyX.h}`)
  const onlyY = resizeTo(base, start, { x: start.x, y: 500 }, pos, VP)
  check('只竖拖不改宽度', near(onlyY.w, base.w), `${onlyY.w}`)

  // 单调：越往右下拖，尺寸单调不减（夹住之前）
  check('越往右下拖越大', resizeTo(base, start, { x: 600, y: 500 }, pos, VP).w
    >= resizeTo(base, start, { x: 560, y: 460 }, pos, VP).w)
}

/* ============================================================
 * 8. 常量口径（改这些值会让布局跟着变，别悄悄改）
 * ============================================================ */
{
  check('窗口宽度 560', WIN_W === 560, `${WIN_W}`)
  check('窗口高度 520', WIN_H === 520, `${WIN_H}`)
  check('边距 8', EDGE === 8, `${EDGE}`)
  check('底部至少留 120', BOTTOM_KEEP === 120, `${BOTTOM_KEEP}`)
  check('底部留白小于窗口高度才有意义', BOTTOM_KEEP < 900)
  check('缩放下限 420x240（再小标题栏和两个按钮就挤没了）',
    MIN_W === 420 && MIN_H === 240, `${MIN_W}x${MIN_H}`)
  check('下限不大于默认尺寸', MIN_W <= WIN_W && MIN_H <= WIN_H)
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.error(`\n失败 ${fails.length} 项：`)
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
console.log('全部通过 ✓')
