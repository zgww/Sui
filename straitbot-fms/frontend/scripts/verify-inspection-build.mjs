/**
 * 航点树 -> 巡检任务 JSON 的组装回归测试。
 *
 * 这段逻辑是要**下发给真机**的：字段写错本地不会报错，而是机器人走到一半
 * 才发现动作类型不对、测温框丢了。所以这里除了常规的单测，还做两件更硬的校验：
 *
 * 1. **与真实任务文件的字段对照**：拿 `backend/tests/test_inspection.json` 里
 *    真实出现的键集合，逐个比对生成的 JSON（缺字段、多字段都算错）。
 * 2. **与后端转换器的往返**：调后端的 `inspection_to_spec`（巡检任务 -> 树），
 *    再用前端的 `buildInspection`（树 -> 巡检任务）转回去，逐字段比对原文件。
 *    —— 手抄副本会与源码漂移，所以两边都用**真实实现**跑。
 *
 * 关键：**不手抄源码**——用 tsc 编译真实 TS 源再 import。
 * 运行：node scripts/verify-inspection-build.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, writeFileSync, readFileSync, readdirSync, statSync, existsSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'ib-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath, [tscEntry,
    'src/utils/inspectionBuild.ts', '--outDir', out,
    '--target', 'es2020', '--module', 'es2020', '--skipLibCheck', '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
// tsc 不给相对 import 补 .js，Node 的 ESM 又要求写全
;(function fixRelativeExts(dir) {
  for (const f of readdirSync(dir)) {
    const p = join(dir, f)
    if (statSync(p).isDirectory()) { fixRelativeExts(p); continue }
    if (!f.endsWith('.js')) continue
    const src = readFileSync(p, 'utf8')
    const fixed = src.replace(/(\bfrom\s*['"])(\.[^'"]*?)(['"])/g,
      (m, a, spec, b) => (/\.js$/.test(spec) ? m : `${a}${spec}.js${b}`))
    if (fixed !== src) writeFileSync(p, fixed)
  }
})(out)
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

const M = await import(pathToFileURL(join(out, 'utils', 'inspectionBuild.js')).href)
const {
  DEFAULT_FLOOR, randomHex, regenerateIds, ensureBoxIds, floorFromName, floorOfPath, floorOfWaypoint,
  collectWaypoints, buildInspection, waypointToJson, actionToJson, measurePointToJson,
} = M

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const near = (a, b, eps = 1e-6) => Math.abs(Number(a) - Number(b)) <= eps
const SEP = '/'

/**
 * 跑一段 python，依次试可用的解释器。
 *
 * 为什么不能只认一个：后端用了 pydantic，而本机有的 python（managed 3.13）
 * 没装它、只有系统 3.12 装了；而 `inspection_to_spec` 只依赖 typing，两个都行。
 * 逐个试到能出结果为止，都跑不出就报失败（不静默放过）。
 */
const PY_CANDIDATES = [
  process.env.PY,
  'python',
  'C:/Users/Administrator/AppData/Local/Programs/Python/Python312/python.exe',
  'python3',
].filter(Boolean)
function runPy(script, cwd) {
  for (const py of PY_CANDIDATES) {
    try {
      const s = execFileSync(py, ['-c', script],
        { cwd, encoding: 'utf8', stdio: ['ignore', 'pipe', 'pipe'], maxBuffer: 64 * 1024 * 1024 })
      if (s && s.trim()) return s
    } catch { /* 换下一个解释器 */ }
  }
  return null
}
const keys = (o) => Object.keys(o || {}).sort()

/* ============================================================
 * 1. randomHex
 * ============================================================ */
{
  const a = randomHex()
  check('默认 32 位', a.length === 32, `${a.length}`)
  check('纯十六进制小写', /^[0-9a-f]{32}$/.test(a), a)
  check('可指定长度', randomHex(8).length === 8)
  check('奇数长度也能取', randomHex(7).length === 7)
  check('长度 0 不炸', randomHex(0) === '')
  const set = new Set()
  for (let i = 0; i < 500; i++) set.add(randomHex())
  check('500 次不重复', set.size === 500, `${set.size}`)
}

/* ============================================================
 * 2. regenerateIds —— 粘贴时必须换掉业务 id
 * ============================================================ */
{
  const spec = {
    root: {
      type: 'GroupNode', properties: { name: '楼层1' },
      children: [{
        type: 'WaypointNode',
        properties: { name: '航点1', wp_id: 'aaa', x: 1 },
        children: [{
          type: 'ActionPointNode',
          properties: { name: '拍照', action_id: 'bbb', action_type: 1 },
          children: [{ type: 'MeasurePointNode', properties: { point_id: 'ccc' } }],
        }],
      }],
    },
  }
  const n = regenerateIds(spec.root)
  const wp = spec.root.children[0]
  const act = wp.children[0]
  const mp = act.children[0]
  check('重生成 3 个 id', n === 3, `${n}`)
  check('航点 id 变了', wp.properties.wp_id !== 'aaa' && /^[0-9a-f]{32}$/.test(wp.properties.wp_id))
  check('动作 id 变了', act.properties.action_id !== 'bbb' && /^[0-9a-f]{32}$/.test(act.properties.action_id))
  check('测点 id 变了', mp.properties.point_id !== 'ccc' && /^[0-9a-f]{32}$/.test(mp.properties.point_id))
  check('名称不被改', wp.properties.name === '航点1')
  check('坐标不被改', wp.properties.x === 1)

  // 非业务节点（图标/区段/轨道）没有这些 id，别给它们乱加字段
  const other = { type: 'IconMarkNode', properties: { icon: '门', color: '#0068FF' } }
  const n2 = regenerateIds(other)
  check('非业务节点不生成 id', n2 === 0, `${n2}`)
  check('非业务节点字段不变', keys(other.properties).join() === 'color,icon')

  // 复制两份同源子树，粘贴后 id 必须互不相同
  const mk = () => JSON.parse(JSON.stringify(spec.root))
  const c1 = mk(), c2 = mk()
  regenerateIds(c1); regenerateIds(c2)
  check('两份粘贴件 id 不同',
    c1.children[0].properties.wp_id !== c2.children[0].properties.wp_id)

  check('空节点不炸', regenerateIds(null) === 0 && regenerateIds(undefined) === 0)
  check('无 properties 不炸', regenerateIds({ type: 'WaypointNode' }) === 1)
}

/* ============================================================
 * 3. 楼层回解（导入时楼层只落在分组名里）
 * ============================================================ */
{
  check('楼层1', floorFromName('楼层1') === 1)
  check('楼层-1（负楼层）', floorFromName('楼层-1') === -1)
  check('带空格', floorFromName('楼层 2') === 2)
  check('名字里带中文也能解', floorFromName('楼层3 东区') === 3)
  check('解不出回落默认', floorFromName('东区') === DEFAULT_FLOOR)
  check('空值回落默认', floorFromName(undefined) === DEFAULT_FLOOR)

  const spec = {
    root: {
      type: 'GroupNode', properties: { name: '任务' },
      children: [{
        type: 'GroupNode', properties: { name: '楼层2' },
        children: [{
          type: 'GroupNode', properties: { name: '区域A' },
          children: [{ type: 'WaypointNode', properties: { x: 1 } }],
        }],
      }],
    },
  }
  const deep = `root${SEP}children${SEP}0${SEP}children${SEP}0${SEP}children${SEP}0`
  check('楼层在外层也能解（逐级向外找）', floorOfPath(spec, deep) === 2, `${floorOfPath(spec, deep)}`)
  check('非分组祖先不算', floorOfPath(spec, `root${SEP}children${SEP}0`, 7) === 7)
}

/* ============================================================
 * 3b. 航点自己的 `floor` 字段（WaypointNode.floor）
 *     分组名是给人看的、改个名就没了；floor 是数据，所以**它说了算**
 * ============================================================ */
{
  const mk = (wpProps, groupName = '楼层2') => ({
    root: {
      type: 'GroupNode', properties: { name: '任务' },
      children: [{
        type: 'GroupNode', properties: { name: groupName },
        children: [{ type: 'WaypointNode', properties: wpProps }],
      }],
    },
  })
  const at = (s) => s.root.children[0].children[0]
  const path = `root${SEP}children${SEP}0${SEP}children${SEP}0`

  const s5 = mk({ floor: 5 })
  check('航点自己的 floor 优先于分组名', floorOfWaypoint(s5, path, at(s5)) === 5,
    `${floorOfWaypoint(s5, path, at(s5))}`)
  // 0 和负数都是合法楼层（0 层 / 地下室），不能当成"没写"
  const s0 = mk({ floor: 0 })
  check('0 层算数（不是"没写"）', floorOfWaypoint(s0, path, at(s0)) === 0)
  const sNeg = mk({ floor: -2 })
  check('负楼层（地下室）算数', floorOfWaypoint(sNeg, path, at(sNeg)) === -2)
  const sStr = mk({ floor: '3' })
  check('存成字符串也算数', floorOfWaypoint(sStr, path, at(sStr)) === 3)

  // 没写 -> 退回老的"从分组名解"，再不行才用默认
  check('没写 floor 时退回分组名', floorOfWaypoint(mk({ x: 1 }), path, at(mk({ x: 1 }))) === 2)
  const sNull = mk({ floor: null })
  check('floor=null 是"没写"而不是 0 层', floorOfWaypoint(sNull, path, at(sNull)) === 2)
  const sEmpty = mk({ floor: '' })
  check('floor="" 也算没写', floorOfWaypoint(sEmpty, path, at(sEmpty)) === 2)
  const sBad = mk({ floor: 'abc' })
  check('floor 不是数字时退回', floorOfWaypoint(sBad, path, at(sBad)) === 2)
  const sNoGrp = mk({ x: 1 }, '区域A')
  check('分组名也解不出就回落默认', floorOfWaypoint(sNoGrp, path, at(sNoGrp)) === DEFAULT_FLOOR)

  // 收集航点时用的就是它
  check('collectWaypoints 认航点的 floor',
    collectWaypoints(mk({ floor: 7 }), [path])[0].floor === 7,
    `${collectWaypoints(mk({ floor: 7 }), [path])[0].floor}`)

  /* 端到端：分组名写着 楼层1，但航点上写着 4 -> 必须进 4 楼那一段。
     这正是"楼层只落在分组名里"会错的场景（导入后用户改了分组名）。 */
  const mixed = {
    root: {
      type: 'GroupNode', properties: { name: '任务' },
      children: [{
        type: 'GroupNode', properties: { name: '楼层1' },
        children: [
          { type: 'WaypointNode', properties: { x: 1, floor: 4 } },
          { type: 'WaypointNode', properties: { x: 2, floor: 2 } },
          { type: 'WaypointNode', properties: { x: 3 } },      // 没写 -> 跟分组名 = 1
        ],
      }],
    },
  }
  const r = buildInspection(mixed, ['root'],
    { name: 'T', inspectionId: 'ID', plan: 'P', substationMapsId: 'S' })
  check('按航点的 floor 分段（不看分组名）', r.payload.map((f) => f.floor).join() === '1,2,4',
    r.payload.map((f) => f.floor).join())
  check('没写 floor 的那个跟着分组名走',
    r.payload.find((f) => f.floor === 1)?.waypoint.length === 1)
}

/* ============================================================
 * 4. collectWaypoints —— 按**树中顺序**，不是按 x
 * ============================================================ */
{
  const wp = (x, i) => ({ type: 'WaypointNode', properties: { x, name: `w${i}` } })
  const spec = {
    root: {
      type: 'GroupNode', properties: { name: '楼层1' },
      children: [
        { type: 'GroupNode', properties: { name: 'A' }, children: [wp(50, 1), wp(10, 2)] },
        wp(30, 3),
        { type: 'ActionPointNode', properties: {} },
      ],
    },
  }
  const picked = collectWaypoints(spec, ['root'])
  check('只收航点', picked.length === 3, `${picked.length}`)
  check('按树中先序（不是按 x 排序）',
    picked.map((p) => p.node.properties.name).join() === 'w1,w2,w3',
    picked.map((p) => p.node.properties.name).join())

  // 同时选中分组和它下面的航点 -> 不重复
  const dup = collectWaypoints(spec, ['root', `root${SEP}children${SEP}0${SEP}children${SEP}0`])
  check('重叠路径去重', dup.length === 3, `${dup.length}`)

  // 只选一个分组 -> 只收它下面的
  const sub = collectWaypoints(spec, [`root${SEP}children${SEP}0`])
  check('限定子树', sub.length === 2, `${sub.length}`)
  check('不存在的路径不炸', collectWaypoints(spec, ['root/x/y']).length === 0)
}

/* ============================================================
 * 5. 生成的 JSON 形状 —— 与真实任务文件逐键对照
 * ============================================================ */
const REAL = JSON.parse(readFileSync(resolve(root, '../backend/tests/test_inspection.json'), 'utf-8'))
const realFloors = Array.isArray(REAL) ? REAL : [REAL]
{
  const realWpKeys = new Set()
  const realActKeys = new Set()
  const realTpKeys = new Set()
  const realPrmKeys = new Set()
  for (const f of realFloors) {
    for (const w of f.waypoint || []) {
      Object.keys(w).forEach((k) => realWpKeys.add(k))
      for (const a of w.action || []) {
        Object.keys(a).forEach((k) => realActKeys.add(k))
        for (const tp of a.thermometry_points || []) {
          Object.keys(tp).forEach((k) => realTpKeys.add(k))
          Object.keys(tp.thermometry_param || {}).forEach((k) => realPrmKeys.add(k))
        }
      }
    }
  }
  check('真实航点键集合非空', realWpKeys.size >= 4, [...realWpKeys].join())

  // 用真实文件里的第一条动作/测点喂进去，比对键
  const firstAct = realFloors[0].waypoint[0].action[0]
  const gen = actionToJson({
    type: 'ActionPointNode',
    properties: { action_id: 'x', action_type: 1, lift_height: 0, duration_ms: 0, pan: 1, tilt: 2, zoom: 1, focal_len: 520, focus: 1, steer_point_name: 'AO' },
    children: [],
  })
  // 真实文件里 duration 只出现在 type=3，其余动作没有这个键；我们恒定输出，故允许它多出来
  const missing = [...realActKeys].filter((k) => !(k in gen))
  const extra = keys(gen).filter((k) => !realActKeys.has(k))
  check('动作字段不缺', missing.length === 0, missing.join())
  check('动作字段不多（除 duration）', extra.every((k) => k === 'duration'), extra.join())
  check('ptz_param 键与真实一致',
    keys(gen.ptz_param).join() === keys(firstAct.ptz_param).join(),
    `${keys(gen.ptz_param).join()} vs ${keys(firstAct.ptz_param).join()}`)
  check('thermometry_param 键与真实一致',
    keys(measurePointToJson({ type: 'MeasurePointNode', properties: {} }).thermometry_param).join()
    === [...realPrmKeys].sort().join(),
    [...realPrmKeys].sort().join())
  check('rect 键与真实一致',
    keys(measurePointToJson({ type: 'MeasurePointNode', properties: {} }).thermometry_param.rect).join()
    === 'h,w,x,y')

  const gw = waypointToJson({ type: 'WaypointNode', properties: { wp_id: 'y' }, children: [] }, 1)
  const missingWp = [...realWpKeys].filter((k) => !(k in gw))
  check('航点字段不缺', missingWp.length === 0, missingWp.join())
  check('pose 结构与真实一致', keys(gw.pose).join() === keys(realFloors[0].waypoint[0].pose).join())
  check('point 结构与真实一致',
    keys(gw.pose.point).join() === keys(realFloors[0].waypoint[0].pose.point).join())
  // 必须有航点才会产出楼层分段，否则 payload 是空的、无从比对键
  check('楼层分段键与真实一致',
    keys(buildInspection({
      root: { type: 'GroupNode', properties: {}, children: [{ type: 'WaypointNode', properties: { x: 1 } }] },
    }, ['root'], { inspectionId: 'i', plan: 'p', substationMapsId: 's' }).payload[0]).join()
    === keys(realFloors[0]).sort().join(),
    keys(realFloors[0]).sort().join())

  // duration：只有录像(type=3)给时长，其余归零
  const d3 = actionToJson({ type: 'ActionPointNode', properties: { action_type: 3, duration_ms: 3000 } })
  const d1 = actionToJson({ type: 'ActionPointNode', properties: { action_type: 1, duration_ms: 3000 } })
  check('type=3 带录像时长', d3.duration === 3000, `${d3.duration}`)
  check('非录像时长归零', d1.duration === 0, `${d1.duration}`)
}

/* ============================================================
 * 6. buildInspection 语义
 * ============================================================ */
{
  const wp = (x, id) => ({
    type: 'WaypointNode', properties: { x, wp_id: id, theta: 1, y: 2, z: 3 },
    children: [{ type: 'ActionPointNode', properties: { action_id: 'a' } }],
  })
  const floor = (n, kids) => ({
    type: 'GroupNode', properties: { name: `楼层${n}` }, children: kids,
  })
  const spec = {
    root: {
      type: 'GroupNode', properties: { name: '任务' },
      children: [floor(2, [wp(9, 'w1')]), floor(1, [wp(1, 'w2'), wp(2, 'w3')])],
    },
  }
  const r = buildInspection(spec, ['root'], { name: 'T', inspectionId: 'ID', plan: 'P', substationMapsId: 'S' })
  check('按楼层分段', r.payload.length === 2, `${r.payload.length}`)
  check('楼层升序', r.payload.map((f) => f.floor).join() === '1,2', r.payload.map((f) => f.floor).join())
  check('航点总数', r.waypointCount === 3, `${r.waypointCount}`)
  check('动作总数', r.actionCount === 3, `${r.actionCount}`)
  check('各段共用同一任务 id', r.payload.every((f) => f.id === 'ID'))
  check('各段共用 plan', r.payload.every((f) => f.plan === 'P'))
  check('任务名透传', r.payload.every((f) => f.name === 'T'))
  const f1 = r.payload.find((f) => f.floor === 1)
  const f2 = r.payload.find((f) => f.floor === 2)
  check('楼层内 index 从 1 递增',
    f1.waypoint.map((w) => w.index).join() === '1,2', f1.waypoint.map((w) => w.index).join())
  check('另一层 index 也重新从 1 起',
    f2.waypoint.map((w) => w.index).join() === '1', f2.waypoint.map((w) => w.index).join())
  check('沿用树上的 wp_id', f1.waypoint.map((w) => w.id).join() === 'w2,w3')
  check('位姿落到 pose.point', near(f1.waypoint[0].pose.point.x, 1) && near(f1.waypoint[0].pose.point.y, 2))
  check('theta 落到 pose', near(f1.waypoint[0].pose.theta, 1))

  // 缺省 id -> 随机补全（32 位 hex）
  const noId = buildInspection({
    root: { type: 'GroupNode', properties: {}, children: [wp(1, '')] },
  }, ['root'])
  check('缺 id 时补随机 32 位', /^[0-9a-f]{32}$/.test(noId.payload[0].waypoint[0].id),
    noId.payload[0].waypoint[0].id)
  check('任务 id 随机 32 位', /^[0-9a-f]{32}$/.test(noId.inspectionId), noId.inspectionId)
  check('freshIds 会换掉已有 id',
    buildInspection({ root: { type: 'GroupNode', properties: {}, children: [wp(1, 'w1')] } },
      ['root'], { freshIds: true }).payload[0].waypoint[0].id !== 'w1')

  // 只有非航点节点时：不给后端发空任务
  const empty = buildInspection({
    root: { type: 'GroupNode', properties: {}, children: [{ type: 'IconMarkNode', properties: {} }] },
  }, ['root'])
  check('没有航点 -> 空 payload', empty.payload.length === 0 && empty.waypointCount === 0)
}

/* ============================================================
 * 6b. 检测框（DetectBoxNode）不进巡检任务
 *
 * 动作点底下除了测温点，现在还会挂检测框。这段是**下发给真机**的数据，
 * 混进一个后端不认识的字段比本地报错糟糕得多（机器人走到一半才发现），
 * 所以"检测框被正确忽略"要显式锁住，不能只靠"现在恰好 filter 掉了"。
 * ============================================================ */
{
  /** 算法配置节点：挂在检测框下面，同样**不该**进下发给真机的任务 */
  const cfg = () => ({
    type: 'AlgorithmConfigNode',
    properties: {
      name: '指针表读数 配置', algorithm: 'meter_pointer',
      threshold: 0.6, level: '严重', params: { range: '0-100A' },
    },
  })
  const box = (shape) => ({
    type: 'DetectBoxNode',
    properties: {
      name: `检测框 ${shape}`, shape,
      points: [{ x: 0.1, y: 0.1 }, { x: 0.5, y: 0.1 }, { x: 0.5, y: 0.5 }, { x: 0.1, y: 0.5 }],
      algorithm: 'meter_pointer',
    },
    children: [cfg()],
  })
  const mp = { type: 'MeasurePointNode', properties: { point_id: 'm1' } }

  // 单个动作点：混着测温点与检测框，只有测温点该进 thermometry_points
  const act = actionToJson({
    type: 'ActionPointNode',
    properties: { action_id: 'a1', action_type: 1 },
    children: [box('rect'), mp, box('polygon')],
  })
  check('检测框不进测温点列表', act.thermometry_points.length === 1,
    `${act.thermometry_points.length}`)
  check('测温点本身照常进入', act.thermometry_points[0].id === 'm1')
  check('action 的字段集合不变',
    keys(act).join() === 'duration,id,lift_height,ptz_param,steer_point_name,thermometry_points,type',
    keys(act).join())

  // 整棵任务：航点数/动作数都不该因为检测框变化
  const specWithBoxes = {
    root: {
      type: 'GroupNode', properties: { name: '楼层1' },
      children: [{
        type: 'WaypointNode', properties: { x: 1, wp_id: 'w1' },
        children: [{
          type: 'ActionPointNode',
          properties: { action_id: 'a1', action_type: 1 },
          children: [box('rect'), box('polygon'), mp],
        }],
      }],
    },
  }
  const r = buildInspection(specWithBoxes, ['root'])
  check('带检测框：航点数不变', r.waypointCount === 1, `${r.waypointCount}`)
  check('带检测框：动作数不变', r.actionCount === 1, `${r.actionCount}`)
  const a = r.payload[0].waypoint[0].action[0]
  check('带检测框：测温点仍是 1 个', a.thermometry_points.length === 1,
    `${a.thermometry_points.length}`)
  check('带检测框：任务 JSON 里搜不到检测框痕迹',
    !JSON.stringify(r.payload).includes('DetectBox')
    && !JSON.stringify(r.payload).includes('meter_pointer'))
  // 算法配置节点在检测框下面，比检测框更深一层——同样一个字都不能漏下去
  const dumped = JSON.stringify(r.payload)
  check('算法配置节点不进任务', !dumped.includes('AlgorithmConfig'))
  check('算法的自定义参数不进任务', !dumped.includes('0-100A') && !dumped.includes('threshold'))

  // ⚠️ 检测框**也要**换 id：`box_id` 是"算法回调认回本框"的键（不是下发给机器人的
  // 动作 id，所以早年这里写的是"不把检测框算进去"）。两个框共用一个 box_id 时，
  // 回调结果会被两边抢着写，而树上看不出任何异常 —— 这条必须锁住。
  const cloned = JSON.parse(JSON.stringify(specWithBoxes.root))
  const n = regenerateIds(cloned)
  check('regenerateIds 覆盖 航点+动作+测温点+2 个检测框', n === 5, `${n}`)
  const boxesIn = []
  const walk = (nd) => {
    if (nd.type === 'DetectBoxNode') boxesIn.push(nd)
    for (const c of nd.children || []) walk(c)
  }
  walk(cloned)
  check('两个检测框都被赋了 box_id',
    boxesIn.length === 2 && boxesIn.every((b) => String(b.properties.box_id || '').length === 32),
    boxesIn.map((b) => b.properties.box_id).join(','))
  check('两个检测框的 box_id 互不相同',
    boxesIn[0].properties.box_id !== boxesIn[1].properties.box_id)
}

/* ============================================================
 * 6c. ensureBoxIds —— 老数据补 box_id（加载/保存时补，已有不动）
 *
 * 检测框的身份字段是后加的：改造前编的树里没有 `box_id`，下发推理任务时框是
 * 匿名的（算法结果回来认不回是哪个框）。所以打开老树时要自动补上并落盘。
 * ⚠️ 补的动作**只对缺的做**：`box_id` 是稳定标识，重新生成等于把历史识别结果
 * 全部解绑 —— 那比"少一个 id"严重得多。
 * ============================================================ */
{
  const spec = {
    root: {
      type: 'GroupNode', properties: { name: '楼层1' },
      children: [{
        type: 'ActionPointNode', properties: { action_id: 'a1' },
        children: [
          { type: 'DetectBoxNode', properties: { name: '框1' } },
          { type: 'DetectBoxNode', properties: { name: '框2', box_id: 'KEEP-ME' } },
          { type: 'DetectBoxNode', properties: { name: '框3', box_id: '   ' } },
          { type: 'MeasurePointNode', properties: { point_id: 'm1' } },
        ],
      }],
    },
  }
  const n = ensureBoxIds(spec.root)
  check('ensureBoxIds 只补缺失的（2 个空 + 1 个空白）', n === 2, `${n}`)
  const kids = spec.root.children[0].children
  check('已有 box_id 不被覆盖', kids[1].properties.box_id === 'KEEP-ME',
    kids[1].properties.box_id)
  check('空白 box_id 视为缺失，补成 32 位',
    /^[0-9a-f]{32}$/.test(String(kids[2].properties.box_id)), kids[2].properties.box_id)
  check('补出来的两个互不相同',
    kids[0].properties.box_id !== kids[2].properties.box_id)
  check('补出来的不碰别的节点', kids[3].properties.box_id === undefined)
  check('再跑一次不重复补（幂等）', ensureBoxIds(spec.root) === 0)
  check('空节点不炸', ensureBoxIds(null) === 0 && ensureBoxIds(undefined) === 0)
}

/* ============================================================
 * 7. 与后端转换器的往返（真实文件 -> 树 -> 任务 JSON）
 * ============================================================ */
{
  const specJson = runPy([
    'import sys, json',
    'sys.path.insert(0, ".")',
    'from app.prefab.waypoint_import import inspection_to_spec',
    'p = json.load(open("tests/test_inspection.json", encoding="utf-8"))',
    'print(json.dumps(inspection_to_spec(p), ensure_ascii=False))',
  ].join('\n'), resolve(root, '../backend'))
  check('能调到后端 inspection_to_spec', !!specJson, `尝试过 ${PY_CANDIDATES.join(' / ')}`)

  if (specJson) {
    const spec = JSON.parse(specJson)
    const r = buildInspection(spec, ['root'])
    check('往返：楼层数一致', r.payload.length === realFloors.length,
      `${r.payload.length} vs ${realFloors.length}`)
    let wpN = 0, actN = 0, tpN = 0
    let bad = []
    for (const realF of realFloors) {
      const mine = r.payload.find((f) => f.floor === realF.floor)
      if (!mine) { bad.push(`缺楼层${realF.floor}`); continue }
      const rw = realF.waypoint || []
      if (mine.waypoint.length !== rw.length) {
        bad.push(`楼层${realF.floor} 航点数 ${mine.waypoint.length}!=${rw.length}`)
        continue
      }
      rw.forEach((w, i) => {
        wpN++
        const m = mine.waypoint[i]
        if (m.index !== i + 1) bad.push(`楼层${realF.floor} 航点${i} index=${m.index}`)
        if (w.id && m.id !== w.id) bad.push(`楼层${realF.floor} 航点${i} id 不一致`)
        if (!near(m.pose.point.x, w.pose.point.x)) bad.push(`楼层${realF.floor} 航点${i} x`)
        if (!near(m.pose.point.y, w.pose.point.y)) bad.push(`楼层${realF.floor} 航点${i} y`)
        if (!near(m.pose.point.z, w.pose.point.z)) bad.push(`楼层${realF.floor} 航点${i} z`)
        if (!near(m.pose.theta, w.pose.theta)) bad.push(`楼层${realF.floor} 航点${i} theta`)

        const ra = w.action || []
        if (m.action.length !== ra.length) {
          bad.push(`楼层${realF.floor} 航点${i} 动作数 ${m.action.length}!=${ra.length}`)
          return
        }
        ra.forEach((a, j) => {
          actN++
          const ma = m.action[j]
          if (a.id && ma.id !== a.id) bad.push(`动作 id 不一致 ${a.id}`)
          if (ma.type !== a.type) bad.push(`动作 type ${ma.type}!=${a.type}`)
          if (!near(ma.lift_height, a.lift_height)) bad.push('动作 lift_height')
          if (a.duration != null && !near(ma.duration, a.duration)) bad.push(`动作 duration ${ma.duration}!=${a.duration}`)
          if (String(ma.steer_point_name) !== String(a.steer_point_name ?? '')) bad.push('动作 steer_point_name')
          for (const k of ['pan', 'tilt', 'zoom', 'focal_len', 'focus']) {
            if (!near(ma.ptz_param[k], (a.ptz_param || {})[k])) bad.push(`动作 ptz.${k}`)
          }
          const rt = a.thermometry_points || []
          if (ma.thermometry_points.length !== rt.length) {
            bad.push(`测温点数 ${ma.thermometry_points.length}!=${rt.length}`)
            return
          }
          rt.forEach((tp, k) => {
            tpN++
            const mt = ma.thermometry_points[k]
            if (tp.id && mt.id !== tp.id) bad.push('测点 id')
            const rp = tp.thermometry_param || {}, mp2 = mt.thermometry_param
            if (!near(mp2.distance, rp.distance)) bad.push('测点 distance')
            if (!near(mp2.emissivity, rp.emissivity)) bad.push('测点 emissivity')
            if (mp2.enable_reflective !== rp.enable_reflective) bad.push('测点 enable_reflective')
            if (!near(mp2.reflective_temperature, rp.reflective_temperature)) bad.push('测点 reflective_temperature')
            for (const kk of ['x', 'y', 'w', 'h']) {
              if (!near(mp2.rect[kk], (rp.rect || {})[kk])) bad.push(`测点 rect.${kk}`)
            }
          })
        })
      })
    }
    check('往返：航点/动作/测点逐字段一致', bad.length === 0, bad.slice(0, 6).join(' | '))
    check('往返：确实覆盖到数据', wpN > 30 && actN > 100 && tpN > 0, `${wpN} 航点/${actN} 动作/${tpN} 测点`)

    /* ---- 8. 交给后端自己的模型解析：它读出来的才是机器人真正执行的顺序 ---- */
    const pf = join(out, 'payload.json').replace(/\\/g, '/')
    writeFileSync(pf, JSON.stringify(r.payload))
    const parsed = runPy([
      'import sys, json',
      'sys.path.insert(0, ".")',
      'from app.rail.inspection import InspectionTask',
      `t = InspectionTask.from_payload(json.load(open("${pf}", encoding="utf-8")))`,
      'print(json.dumps({"id": t.inspection_id, "name": t.name, "floors": t.floors_desc(),',
      '  "wp": t.waypoint_count, "act": t.action_count,',
      '  "seq": [[fl, w.id, w.index, w.pose.point.x] for fl, w in t.waypoints]}, ensure_ascii=False))',
    ].join('\n'), resolve(root, '../backend'))
    check('后端 InspectionTask 能解析生成的 payload', !!parsed, '解析失败')
    if (parsed) {
      const t = JSON.parse(parsed)
      check('后端读到的航点数一致', t.wp === r.waypointCount, `${t.wp} vs ${r.waypointCount}`)
      check('后端读到的动作数一致', t.act === r.actionCount, `${t.act} vs ${r.actionCount}`)
      check('后端读到的楼层一致', t.floors.join() === r.floors.join(), `${t.floors} vs ${r.floors}`)
      check('后端读到的任务 id 一致', t.id === r.inspectionId)

      // 后端遍历顺序 = (floor 升序, index 升序)；我们写的顺序就是树中顺序
      const mine = []
      for (const f of [...r.payload].sort((a, b) => a.floor - b.floor)) {
        for (const w of f.waypoint) mine.push([f.floor, w.id, w.index, w.pose.point.x])
      }
      const same = t.seq.length === mine.length
        && t.seq.every((s, i) => s[0] === mine[i][0] && s[1] === mine[i][1]
          && s[2] === mine[i][2] && near(s[3], mine[i][3]))
      check('后端执行顺序 == 树中顺序', same,
        `${JSON.stringify(t.seq.slice(0, 3))} vs ${JSON.stringify(mine.slice(0, 3))}`)
    }
  }
}

rmSync(out, { recursive: true, force: true })
console.log(`\n巡检任务组装回归：${pass} 项通过，${fails.length} 项失败`)
for (const f of fails) console.log('  x ' + f)
process.exit(fails.length ? 1 : 0)
