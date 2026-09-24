/**
 * 检测框纯函数的回归测试（utils/detectBoxBinding.ts）。
 *
 * 与 verify-detect-box.mjs 同一套路：**不手抄源码**，用 tsc 把真实 .ts
 * 编到临时目录再 import。运行：node scripts/verify-detect-binding.mjs
 *
 * 这里锁两件最容易写错的事：
 * - `nextBox`：批量给一批框挨个绑测点 / 指定检测流程时，"设置并切下一个框"
 *   跳到谁、走到末尾怎么回绕、只有一个框 / 没选中时别卡死。
 * - `collectPointUsage`：整棵树的测点占用表（一个测点只能绑一处、绑在哪要看得见、
 *   不成框不占位、测温点也算、序号不跳号、名字缺失不出现 undefined）。
 *
 * 注：早年"在检测框下挂 AlgorithmConfigNode 选单个算法"的 bind/unbind 用例已随
 * 该模型下线而移除——检测框现在直接在 `DetectBoxNode.detect_flow` 引用一条检测
 * 算法流程，不再有绑定 / 解绑子节点这回事。
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync, readFileSync, readdirSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'dbind-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath,
    [tscEntry, 'src/utils/detectBoxBinding.ts', '--outDir', out,
      '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
      '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

/**
 * tsc 不会给相对导入补 `.js`（它假定打包器会处理），但 Node 原生 ESM
 * **必须带扩展名**。被一起编出来的依赖也踩这条，统一把 `from './x'` 补成 `.js`。
 */
const fixExt = (dir) => {
  for (const name of readdirSync(dir, { withFileTypes: true })) {
    const p = join(dir, name.name)
    if (name.isDirectory()) { fixExt(p); continue }
    if (!name.name.endsWith('.js')) continue
    const src = readFileSync(p, 'utf8')
    const next = src.replace(/(from\s+['"])(\.[^'"]*?)(['"])/g,
      (m, a, spec, c) => (spec.endsWith('.js') ? m : `${a}${spec}.js${c}`))
    if (next !== src) writeFileSync(p, next)
  }
}
fixExt(out)

// tsc 会把依赖一起编出来，路径跟着 rootDir 走
const modPath = ['utils/detectBoxBinding.js', 'detectBoxBinding.js']
  .map((p) => join(out, p)).find((p) => existsSync(p))
if (!modPath) {
  console.error('编译产物里找不到 detectBoxBinding.js：', out)
  process.exit(1)
}
const B = await import(pathToFileURL(modPath).href)
const { nextBox, collectPointUsage } = B

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }

/* ============================================================
 * 1. 「绑定并切下一个检测框」的下一个是谁
 *
 * 给一批框挨个绑测点 / 指定流程时靠它连着走，卡住或跳错都会让人以为按钮坏了。
 * ============================================================ */
{
  const boxes = [{ path: 'a' }, { path: 'b' }, { path: 'c' }]
  const n1 = nextBox(boxes, 'a')
  check('下一个是 b', n1?.path === 'b' && n1?.index === 1, JSON.stringify(n1))
  check('中间不标回绕', n1?.wrapped === false)

  const n2 = nextBox(boxes, 'c')
  check('最后一个回到第一个', n2?.path === 'a' && n2?.index === 0, JSON.stringify(n2))
  check('回绕要标出来（调用方据此提示"一轮走完了"）', n2?.wrapped === true)

  // 一个框：下一个是它自己，别返回 null 把流程卡死
  const one = nextBox([{ path: 'a' }], 'a')
  check('只有一个框 -> 还是它', one?.path === 'a' && one?.wrapped === true, JSON.stringify(one))

  // 没选中任何框（刚画完还没点列表）：从第一个开始
  const none = nextBox(boxes, null)
  check('没选中时从第一个开始', none?.path === 'a' && none?.index === 0)

  // 选中项已经不在列表里（框刚被删掉）
  const stale = nextBox(boxes, 'zzz')
  check('选中项失效时回第一个', stale?.path === 'a')

  check('没有框 -> null', nextBox([], 'a') === null)
}

/* ============================================================
 * 2. 整棵树的测点占用表（一个测点只能绑一处 + 绑在哪要看得见）
 *
 * 这张表是"绑重了"和"不知道绑哪了"的唯一依据，写错的地方都很隐蔽：
 * 序号数错（把没绑测点的框跳过去）、只看当前动作点、测温点不算占用、
 * 名字没有时整行变成 "undefined / undefined"。
 * ============================================================ */
{
  /** n 个归一化顶点；<3 的框不成框（和列表同一个门槛） */
  const pts = (n) => Array.from({ length: n }, (_, i) => ({ x: 0.1 * (i + 1), y: 0.2 }))
  const box = (pointId, n = 4, extra = {}) => ({
    type: 'DetectBoxNode',
    properties: { point_id: pointId, points: pts(n), ...extra },
  })
  const mp = (pointId) => ({ type: 'MeasurePointNode', properties: { point_id: pointId } })
  const act = (props, children) => ({
    type: 'ActionPointNode', properties: props, children,
  })
  const wp = (props, children) => ({ type: 'WaypointNode', properties: props, children })
  const group = (children) => ({ type: 'GroupNode', properties: { name: '一楼' }, children })

  // 一棵常规树：航点 1 号柜 -> 拍照动作点 -> [框#1(p1), 不成框(p2), 框#2(没绑), 框#3(p3), 测温点(m1)]
  const tree = group([wp({ name: '1 号柜', wp_id: 'W1' }, [
    act({ name: '拍照点A', action_type: 1 }, [
      box('p1'),
      box('p2', 2),          // 只有 2 个点：围不出区域，不算框，也不占测点
      box(''),               // 成框但没绑测点：序号照样占一位
      box('p3'),
      mp('m1'),
    ]),
  ])])

  const u = collectPointUsage(tree)
  check('绑在检测框上的测点有路径',
    u.p1 === '1 号柜 / 拍照点A · 拍照 / 检测框 #1', JSON.stringify(u.p1))
  check('不成框的检测框不占测点', u.p2 === undefined, String(u.p2))
  // 序号按**框**数，不是按"绑了测点的框"数：跳号会让人去错框里找
  check('序号不因前面的框没绑测点而跳号',
    u.p3 === '1 号柜 / 拍照点A · 拍照 / 检测框 #3', JSON.stringify(u.p3))
  check('测温点也算占用（和检测框抢同一份测点档案）',
    u.m1 === '1 号柜 / 拍照点A · 拍照 / 测温点 #1', JSON.stringify(u.m1))
  check('没绑测点的不进表', Object.keys(u).length === 3, JSON.stringify(Object.keys(u)))

  // 名字缺失：退回 wp_id / steer_point_name / 类型 + 序号，不许出现 undefined
  const bare = group([wp({}, [
    act({ action_type: 2 }, [box('q1')]),
  ])])
  const ub = collectPointUsage(bare)
  check('没名字时退回序号和类型，不是 undefined',
    ub.q1 === '航点 #1 / 动作点 · 测温 / 检测框 #1', JSON.stringify(ub.q1))

  const byCode = group([wp({}, [act({ steer_point_name: 'AO-RC-057' }, [box('q2')])])])
  check('没 name 时用 steer_point_name',
    collectPointUsage(byCode).q2 === '航点 #1 / AO-RC-057 / 检测框 #1',
    JSON.stringify(collectPointUsage(byCode).q2))

  // 别的航点 / 别的动作点绑走也算占用 —— 只看当前动作点就会放过这种情况
  const cross = group([
    wp({ name: 'A 柜' }, [act({ name: '动作1', action_type: 1 }, [box('x1')])]),
    wp({ name: 'B 柜' }, [act({ name: '动作2', action_type: 1 }, [box('x1')])]),
  ])
  const uc = collectPointUsage(cross)
  check('跨航点的重复绑定只记先扫到的那处',
    uc.x1 === 'A 柜 / 动作1 · 拍照 / 检测框 #1', JSON.stringify(uc.x1))

  // 分组嵌套：航点藏在分组里也要扫到
  const deep = group([group([wp({ name: 'C 柜' }, [act({ name: '动作3', action_type: 1 }, [box('d1')])])])])
  check('嵌套分组里的航点也能扫到',
    collectPointUsage(deep).d1 === 'C 柜 / 动作3 · 拍照 / 检测框 #1',
    JSON.stringify(collectPointUsage(deep).d1))

  // 测温点序号：没绑测点的测温点也占一位
  const mps = group([wp({ name: 'D 柜' }, [act({ name: '测温', action_type: 2 }, [
    { type: 'MeasurePointNode', properties: {} }, mp('z1'),
  ])])])
  check('测温点序号同样按顺序',
    collectPointUsage(mps).z1 === 'D 柜 / 测温 · 测温 / 测温点 #2',
    JSON.stringify(collectPointUsage(mps).z1))

  // 健壮性：空树 / 缺字段不该抛异常（页面一开始就是 null）
  check('null -> 空表', JSON.stringify(collectPointUsage(null)) === '{}')
  check('空对象 -> 空表', JSON.stringify(collectPointUsage({})) === '{}')
  let threw = false
  try {
    collectPointUsage({ type: 'WaypointNode', children: [{ type: 'ActionPointNode' }] })
  } catch { threw = true }
  check('缺 properties / children 不抛异常', !threw)
  // point_id 是空串（属性在但没填）不能进表，否则所有框都显示"已绑"
  check('空 point_id 不进表',
    JSON.stringify(collectPointUsage(group([wp({ name: 'E' }, [act({}, [box('')])])]))) === '{}')
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.log('失败：')
  for (const f of fails) console.log('  ✗', f)
  process.exit(1)
}
console.log('全部通过 ✓')
