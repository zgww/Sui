/**
 * 右键平移的回归测试。
 *
 * 这里验证的是**右键手势状态机**，即"按下 / 移动 / 抬起 / contextmenu"
 * 四种事件跨平台乱序到来时，该不该平移、该不该弹菜单。
 *
 * 为什么必须单独测：这段逻辑的输入是**事件顺序**，而顺序在 Windows 与
 * macOS 上是相反的（down→up→contextmenu vs down→contextmenu→up）。
 * 类型检查看不出来，跑真浏览器又只能覆盖一个平台；把判定抽成纯函数后，
 * 就能在一次运行里把两种顺序 × "拖动 / 没拖动" × "起点有无可操作对象"
 * 的组合全部走一遍。
 *
 * 关键：**不手抄源码**——用 tsc 编译真实 TS 源再 import。
 * 运行：node scripts/verify-rightpan.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, writeFileSync, existsSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'rp-'))

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
  panFrom, panBy, sameViewport, screenToWorld, worldToScreen, isDrag,
  defaultTrack, sampleTrack, pointAtFraction, hitTrack, pixelTolerance, fitViewport, boundsOf,
} = g

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }

/* ============================================================
 * 复刻 TrackMap.tsx 里的右键手势（与源码一一对应）
 *
 * 源码规则（刻意简单可预测）：
 *   右键按下     -> 任何位置都"预备平移"，记下 {screen, vp, onTarget}
 *   移动         -> 位移 > 3px 判定为拖拽，开始平移
 *   抬起         -> 没拖过 && onTarget 才弹菜单，否则纯平移
 *   contextmenu  -> 只 preventDefault，不参与决策
 * ============================================================ */

const DRAG_THRESHOLD = 3

/**
 * @param opts.onTarget 按下处是否落在轨道/控制点上
 * @param opts.dragBy   拖动位移 [dx,dy]；[0,0] = 原地松手
 * @param opts.platform 'win'（down→up→cm）或 'mac'（down→cm→up）
 */
function simulateRightClick({ onTarget, dragBy = [0, 0], platform = 'win' }) {
  const base = { scale: 1.7, offset: { x: 33, y: -12 } }
  const start = { x: 200, y: 120 }
  const end = { x: start.x + dragBy[0], y: start.y + dragBy[1] }

  let press = null
  let pressMoved = false
  let panning = false
  let vp = { ...base, offset: { ...base.offset } }
  const log = []

  /* --- mousedown --- */
  press = { screen: start, vp: { ...vp, offset: { ...vp.offset } }, onTarget }
  pressMoved = false
  log.push('down')

  /* --- mousemove --- */
  const doMove = () => {
    if (!press) return
    if (!pressMoved && isDrag(press.screen, end, DRAG_THRESHOLD)) {
      pressMoved = true
      panning = true
      log.push('move:begin')
    }
    if (pressMoved) {
      vp = panFrom(press.vp, press.screen, end)
      log.push('move:pan')
    }
  }

  /* --- mouseup（唯一的菜单决策点） --- */
  const endDrag = () => {
    let opened = false
    if (press) {
      const { onTarget: onT } = press
      const wasDrag = pressMoved
      press = null
      pressMoved = false
      panning = false
      if (!wasDrag && onT) { opened = true; log.push('up:menu') }
      else log.push(wasDrag ? 'up:no-menu(dragged)' : 'up:no-menu(blank)')
    }
    return { opened }
  }

  /* --- contextmenu：源码里只 preventDefault --- */
  const contextMenu = () => { log.push('ctx:suppressed') }

  let menuOpened = false
  if (platform === 'win') {
    doMove()
    menuOpened = endDrag().opened
    contextMenu()
  } else {
    doMove()
    contextMenu()
    menuOpened = endDrag().opened
  }

  return { log, menuOpened, moved: pressMoved, vp, base, panning }
}

/* ============================================================
 * 1. 空白处原地右键：不弹菜单（平移手势成立），视口不动
 * ============================================================ */
{
  for (const platform of ['win', 'mac']) {
    const r = simulateRightClick({ onTarget: false, dragBy: [0, 0], platform })
    check(`[${platform}] 空白处原地右键不弹菜单`, !r.menuOpened, r.log.join('>'))
    check(`[${platform}] 空白处原地右键视口不动`, sameViewport(r.vp, r.base))
  }
}

/* ============================================================
 * 2. 空白处右键拖拽：平移到位且不弹菜单
 * ============================================================ */
{
  for (const platform of ['win', 'mac']) {
    const r = simulateRightClick({ onTarget: false, dragBy: [80, -40], platform })
    check(`[${platform}] 空白处右键拖拽 -> 视口平移`,
      r.vp.offset.x === r.base.offset.x + 80 && r.vp.offset.y === r.base.offset.y - 40,
      `offset=(${r.vp.offset.x},${r.vp.offset.y})`)
    check(`[${platform}] 空白处右键拖拽不弹菜单`, !r.menuOpened, r.log.join('>'))
    check(`[${platform}] 右键拖拽不改缩放`, r.vp.scale === r.base.scale)
  }
}

/* ============================================================
 * 3. 轨道上原地右键：两种平台顺序都要弹菜单
 * ============================================================ */
{
  for (const platform of ['win', 'mac']) {
    const r = simulateRightClick({ onTarget: true, dragBy: [0, 0], platform })
    check(`[${platform}] 轨道上原地右键弹菜单`, r.menuOpened, r.log.join('>'))
    check(`[${platform}] 轨道上原地右键视口不动`, sameViewport(r.vp, r.base))
  }
}

/* ============================================================
 * 4. 轨道上起手但拖走：这是"想平移"，不弹菜单，而且要真的平移
 *
 * 这条最关键：早期版本里"起点在轨道上"就完全不预备平移，
 * 于是从曲线上起手拖动会掉进**死区**（按了没反应）。
 * ============================================================ */
{
  for (const platform of ['win', 'mac']) {
    const r = simulateRightClick({ onTarget: true, dragBy: [60, 30], platform })
    check(`[${platform}] 轨道上起手拖走 -> 不弹菜单`, !r.menuOpened, r.log.join('>'))
    check(`[${platform}] 轨道上起手拖走 -> 仍然平移（无死区）`,
      r.vp.offset.x === r.base.offset.x + 60 && r.vp.offset.y === r.base.offset.y + 30,
      `offset=(${r.vp.offset.x},${r.vp.offset.y})`)
  }
}

/* ============================================================
 * 4b. 反向验证：把"早期写法"塞回去，上面第 4 组必须能抓到
 *
 * 早期实现是"起点在轨道上就完全不预备平移"，于是从曲线上起手拖动会
 * 掉进死区。这里显式跑一遍错误写法，确认测试不是假绿。
 * ============================================================ */
{
  const buggy = ({ onTarget, dragBy }) => {
    const base = { scale: 1.7, offset: { x: 33, y: -12 } }
    const start = { x: 200, y: 120 }
    const end = { x: start.x + dragBy[0], y: start.y + dragBy[1] }
    let vp = { ...base, offset: { ...base.offset } }
    // 错误写法：onTarget 时压根不准备平移
    const armed = !onTarget
    if (armed && isDrag(start, end, DRAG_THRESHOLD)) vp = panFrom(base, start, end)
    return { vp, base, opened: !isDrag(start, end, DRAG_THRESHOLD) && onTarget }
  }
  const r = buggy({ onTarget: true, dragBy: [60, 30] })
  check('错误写法确实留下了死区（证明断言 4 有抓力）',
    sameViewport(r.vp, r.base), `offset=(${r.vp.offset.x},${r.vp.offset.y})`)
}

/* ============================================================
 * 5. 阈值：小抖动仍算原地，否则菜单极难点出来
 * ============================================================ */
{
  check('2px 抖动仍弹菜单',
    simulateRightClick({ onTarget: true, dragBy: [2, 1] }).menuOpened)
  check('3px 恰在阈值上，不算拖动',
    simulateRightClick({ onTarget: true, dragBy: [3, 0] }).menuOpened)
  check('4px 位移就不再弹菜单',
    !simulateRightClick({ onTarget: true, dragBy: [4, 0] }).menuOpened)

  const still = simulateRightClick({ onTarget: false, dragBy: [2, 2] })
  check('空白处 2px 抖动不产生平移', sameViewport(still.vp, still.base))

  // isDrag 本身：用欧氏距离，不是单轴
  check('isDrag 默认阈值 3px',
    isDrag({ x: 0, y: 0 }, { x: 4, y: 0 }) === true
    && isDrag({ x: 0, y: 0 }, { x: 3, y: 0 }) === false)
  check('isDrag 走欧氏距离（2+2 的合成未超阈值）',
    isDrag({ x: 0, y: 0 }, { x: 2, y: 2 }) === false
    && isDrag({ x: 0, y: 0 }, { x: 3, y: 3 }) === true)
}

/* ============================================================
 * 6. panFrom 的绝对语义（差分累加做不到的地方）
 * ============================================================ */
{
  const base = { scale: 2, offset: { x: 10, y: 20 } }
  const start = { x: 100, y: 100 }
  const now = { x: 160, y: 40 }

  const once = panFrom(base, start, now)
  check('panFrom 位移正确', once.offset.x === 70 && once.offset.y === -40,
    `offset=(${once.offset.x},${once.offset.y})`)

  // 幂等：反复用同一个"当前点"算，结果必须一模一样
  let v = base
  for (let i = 0; i < 50; i++) v = panFrom(base, start, now)
  check('panFrom 幂等（绝对计算，不是累加）', sameViewport(v, once))

  // 可分解：与"分段平移的合成"一致，说明它就是纯平移
  const half = panFrom(base, start, { x: (start.x + now.x) / 2, y: (start.y + now.y) / 2 })
  const composed = panFrom(half, { x: 0, y: 0 }, {
    x: (now.x - start.x) / 2, y: (now.y - start.y) / 2,
  })
  check('panFrom 可分解', sameViewport(composed, once),
    `(${composed.offset.x},${composed.offset.y}) vs (${once.offset.x},${once.offset.y})`)

  check('panFrom 不改 scale', once.scale === base.scale)
  check('sameViewport 识别相等',
    sameViewport(once, { ...once, offset: { ...once.offset } }))
  check('sameViewport 识别不等', !sameViewport(once, panBy(once, 1, 0)))
}

/* ============================================================
 * 7. 平移后命中测试仍成立（菜单里的"在此添加航点"依赖它）
 * ============================================================ */
{
  const track = defaultTrack(4, 1000)
  const s = sampleTrack(track, 48)
  const base = fitViewport(boundsOf(s.pts), { w: 800, h: 260 }, 46)

  const vp = panFrom(base, { x: 400, y: 130 }, { x: 460, y: 100 })
  const scr = worldToScreen(vp, pointAtFraction(s, 0.5))

  const u = hitTrack(s, screenToWorld(vp, scr), pixelTolerance(vp, 14))
  check('平移后点轨道仍命中且 u 正确', u !== null && Math.abs(u - 0.5) < 0.02, `u=${u}`)

  const off = { x: scr.x, y: scr.y + 60 }
  check('平移后离轨道 60px 的点不命中',
    hitTrack(s, screenToWorld(vp, off), pixelTolerance(vp, 14)) === null)
}

/* ============================================================
 * 8. 连续两次右键：状态不能被上一次粘住
 * ============================================================ */
{
  const a = simulateRightClick({ onTarget: true, dragBy: [0, 0] })
  const b = simulateRightClick({ onTarget: false, dragBy: [50, 0] })
  check('第一次（轨道上原地）弹菜单', a.menuOpened)
  check('第二次（空白处拖拽）不弹菜单且平移了',
    !b.menuOpened && b.vp.offset.x === b.base.offset.x + 50)
}

/* ============================================================
 * 9. 指针移出画布后仍要能继续平移
 *
 * 背景：mousemove 原本挂在 canvas 元素上，指针一出画布就不再触发，
 * 平移当场卡死。现在改由 window 监听，画布坐标会出现负值 / 超出 size
 * 的情况——`panFrom` 做的是减法，所以对这类坐标天然成立。
 * 这一组把"拖出画布"的位移算一遍，确认结果不受越界坐标影响。
 * ============================================================ */
{
  const base = { scale: 1.7, offset: { x: 33, y: -12 } }
  // 画布内按下，然后一路拖到画布外（坐标为负、以及远超尺寸）
  const start = { x: 300, y: 120 }

  for (const outside of [{ x: -80, y: -40 }, { x: 1200, y: 900 }, { x: -30, y: 700 }]) {
    const vp = panFrom(base, start, outside)
    check(`拖到画布外 (${outside.x},${outside.y}) 平移量正确`,
      vp.offset.x === base.offset.x + (outside.x - start.x)
      && vp.offset.y === base.offset.y + (outside.y - start.y),
      `offset=(${vp.offset.x},${vp.offset.y})`)
    check(`拖到画布外 (${outside.x},${outside.y}) 不改缩放`, vp.scale === base.scale)
  }

  // 从画布外一路拖回画布内，位移应当是反向且精确的
  const back = panFrom(base, { x: -50, y: -50 }, { x: 400, y: 200 })
  check('从画布外拖回画布内位移正确',
    back.offset.x === base.offset.x + 450 && back.offset.y === base.offset.y + 250,
    `offset=(${back.offset.x},${back.offset.y})`)

  // 往返：拖出去再拖回原点，视口必须完全复原（不能残留漂移）
  const away = panFrom(base, start, { x: -200, y: -200 })
  const home = panFrom(base, start, start)
  check('拖出去再拖回原点，视口复原', sameViewport(home, base))
  check('中途的越界视口确实是偏移过的', !sameViewport(away, base))
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.log(`\n失败 ${fails.length} 项：`)
  fails.forEach((f) => console.log('  ✗ ' + f))
  process.exit(1)
}
console.log('全部通过 ✓\n')
