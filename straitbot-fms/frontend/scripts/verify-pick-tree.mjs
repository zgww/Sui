/**
 * 两个「挑选」面板的回归测试（航点指定 / 测点指定）。
 *
 * 三件事一起锁：
 * 1. **纯函数** `utils/marqueeSelect.ts` —— 框选的替换 / 增加 / 移除怎么合并。
 *    错了不报错，只会"少选几个 / 多选几个"，而且是在拖拽过程中逐帧体现的。
 * 2. **纯函数** `utils/pickTree.ts` + `waypointPick.ts` + `pointPick.ts` ——
 *    树怎么搭、Shift 范围怎么取、合并怎么保序。楼层回解、锚点失效、
 *    换楼层清空、wp_id 重复、测点未归类这些坑都在这里。
 * 3. **源码级断言** —— 三处"删掉不会有任何类型错误、但行为会悄悄退化"的约定：
 *    TrackMap 的框选必须走 `applyPickMode` 且基准是按下时的快照；
 *    挑选面板的行必须自己接管点击（勾选框 `pointer-events: none`）；
 *    挑选模式必须藏掉绘制/图层这些编辑入口。
 *
 * 与其它脚本同一套路：**不手抄源码**，用 tsc 把真实 .ts 编到临时目录再 import。
 * 运行：node scripts/verify-pick-tree.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync, readFileSync, readdirSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'picktree-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath,
    [tscEntry,
      'src/utils/marqueeSelect.ts', 'src/utils/pickTree.ts',
      'src/utils/waypointPick.ts', 'src/utils/pointPick.ts',
      '--outDir', out,
      '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
      '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

/** tsc 不给相对导入补 `.js`，Node 原生 ESM 必须要，产物里补一遍 */
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

const load = (name) => {
  const p = ['utils/' + name, name].map((x) => join(out, x)).find((x) => existsSync(x))
  if (!p) { console.error(`编译产物里找不到 ${name}：`, out); process.exit(1) }
  return pathToFileURL(p).href
}

const M = await import(load('marqueeSelect.js'))
const T = await import(load('pickTree.js'))
const W = await import(load('waypointPick.js'))
const P = await import(load('pointPick.js'))
const {
  PICK_MODES, PICK_MODE_LABEL, normalizePickMode, resolvePickMode, applyPickMode,
} = M
const {
  filterPickTree, expandableKeys, leavesOf, flattenPickTree, rangePaths, keysOfPaths,
  toggleKey, unionPick, mergePick, mergeScopedPick, indexPickTree, keyByPath, toSemiTree,
  leafKeysOf, groupPickInfo, groupToggleMode,
} = T
const {
  buildPickTree, pickMapWaypoints, pickTrackOf, floorsOf, outOfTrackKeys, shortLabel,
} = W
const {
  buildPointPickTree, childrenOfDirs, descendantDirs, pointLabel, ROOT_GROUP,
} = P

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const eq = (n, got, want) => check(n, got === want, `got=${JSON.stringify(got)} want=${JSON.stringify(want)}`)
const deep = (n, got, want) => check(n, JSON.stringify(got) === JSON.stringify(want),
  `got=${JSON.stringify(got)} want=${JSON.stringify(want)}`)

/* ============================================================ 1. 框选模式 */

eq('1.1 PICK_MODES 三项齐全', PICK_MODES.join(','), 'replace,add,remove')
check('1.2 三个模式都有中文名',
  PICK_MODES.every((m) => typeof PICK_MODE_LABEL[m] === 'string' && PICK_MODE_LABEL[m]))

eq('1.3 normalize: add 保留', normalizePickMode('add'), 'add')
eq('1.4 normalize: remove 保留', normalizePickMode('remove'), 'remove')
eq('1.5 normalize: replace 保留', normalizePickMode('replace'), 'replace')
eq('1.6 normalize: 脏值回落 replace', normalizePickMode('ADD'), 'replace')
eq('1.7 normalize: undefined 回落 replace', normalizePickMode(undefined), 'replace')
eq('1.8 normalize: null 回落 replace', normalizePickMode(null), 'replace')

eq('1.9 Shift 覆盖成增加', resolvePickMode({ shiftKey: true }, 'replace'), 'add')
eq('1.10 Alt 覆盖成移除', resolvePickMode({ altKey: true }, 'replace'), 'remove')
// Shift 优先于 Alt：两者同按时用户多半是想"加"，而且这样与"点选时 Shift = 加选"一致
eq('1.11 Shift+Alt 时 Shift 优先', resolvePickMode({ shiftKey: true, altKey: true }, 'remove'), 'add')
eq('1.12 无修饰键用基准模式', resolvePickMode({}, 'remove'), 'remove')
eq('1.13 事件为 null 不炸', resolvePickMode(null, 'add'), 'add')
eq('1.14 事件为 undefined 不炸', resolvePickMode(undefined, 'add'), 'add')

deep('1.15 replace 无视基准',
  [...applyPickMode(['a', 'b'], ['c'], 'replace')].sort(), ['c'])
deep('1.16 add 并集',
  [...applyPickMode(['a', 'b'], ['b', 'c'], 'add')].sort(), ['a', 'b', 'c'])
deep('1.17 remove 差集',
  [...applyPickMode(['a', 'b', 'c'], ['b'], 'remove')].sort(), ['a', 'c'])
deep('1.18 hit 为空时 replace 清空',
  [...applyPickMode(['a', 'b'], [], 'replace')], [])
deep('1.19 hit 为空时 add 保持基准',
  [...applyPickMode(['a', 'b'], [], 'add')].sort(), ['a', 'b'])
deep('1.20 remove 移除不存在的 key 不炸',
  [...applyPickMode(['a'], ['z'], 'remove')], ['a'])

// 核心不变量：基准必须是**按下那一刻的快照**。
// 用同一份快照连续算两帧、第二帧的 hit 是第一帧的子集（框拖回去），
// 结果必须跟着缩回去——拿上一帧结果当基准就会"粘住"。
const snap = ['x']
const f1add = applyPickMode(snap, ['a', 'b'], 'add')
const f2add = applyPickMode(snap, ['a'], 'add')
check('1.21 add: 框拖回去能撤销（无残留）', !f2add.has('b') && f2add.has('a'))
deep('1.22 add: 快照基准下第二帧 = {x,a}', [...f2add].sort(), ['a', 'x'])
// 反例（错误用法）：拿上一帧结果当基准，b 就留下了
const buggy = applyPickMode(f1add, ['a'], 'add')
check('1.23 反例：用上一帧结果当基准会残留（说明快照是必需的）', buggy.has('b'))

const f1rm = applyPickMode(['a', 'b'], ['a'], 'remove')
check('1.24 remove: 框罩住就移除', !f1rm.has('a') && f1rm.has('b'))
deep('1.25 remove: 框移开后恢复',
  [...applyPickMode(['a', 'b'], [], 'remove')].sort(), ['a', 'b'])

/* ============================================================ 2. 树视图数据 */

/**
 * 造一棵**贴近真实**的航点树：根 -> 楼层分组 -> 航点，
 * 外加一个不含航点的 TrackNode 分支（应当整枝丢掉）。
 *
 * 注意航点节点上**故意不写 `floor`**——真机上就是这样（楼层只存在于分组名里），
 * 这是本项目最容易踩的坑：读 `properties.floor` 会得到 undefined，
 * 所有航点都显示成 F1。
 */
const wp = (name, wpId, index, x, kids = []) => ({
  type: 'WaypointNode',
  properties: { name, wp_id: wpId, index, x, y: 0 },
  children: kids,
})
const grp = (name, children) => ({
  type: 'GroupNode', properties: { name, enabled: true }, children,
})
const spec = {
  name: 'T',
  root: grp('全程TT', [
    grp('楼层2', [
      wp('航点1', 'AAA', 1, 55.042),
      wp('航点2', 'BBB', 2, 54.27),
      wp('', '', 3, 48.491),          // 无 name 无 wp_id：回退链要兜住
    ]),
    grp('楼层3', [
      wp('航点4', 'CCC', 4, 12.5),
      wp('航点5', 'DDD', 5, 8.0),
    ]),
    {
      type: 'TrackNode',
      properties: { name: '轨道' },
      children: [
        { type: 'TrackEndpointNode', properties: { x: 0, y: 0 } },
        { type: 'TrackEndpointNode', properties: { x: 60, y: 0 } },
      ],
    },
    grp('空分组', []),
  ]),
}

const tree = buildPickTree(spec, 'all')
// 根节点是文件本身（面板上方已有文件名下拉），跳过；「空分组」没有航点，整枝丢掉
eq('2.1 跳过根节点', tree.length, 2)
deep('2.2 顶层是两个有航点的分组', tree.map((n) => n.label), ['楼层2', '楼层3'])
eq('2.3 不含航点的分组整枝丢掉', tree.some((n) => n.label === '空分组'), false)
eq('2.4 TrackNode 分支不进树', JSON.stringify(tree).includes('轨道'), false)
eq('2.5 楼层2 下三个航点', tree[0].children.length, 3)

const l2 = tree[0].children
eq('2.6 key 优先 wp_id', l2[0].key, 'AAA')
eq('2.7 无 wp_id 时 key 回落路径', l2[2].key, 'root/children/0/children/2')
eq('2.8 楼层从分组名回解（不是读 properties.floor）', l2[0].data.floor, 2)
eq('2.9 楼层3 也解得出来', tree[1].children[0].data.floor, 3)
check('2.10 标签带楼层与米数', l2[0].label.includes('F2') && l2[0].label.includes('55.042'))
check('2.11 无名字无 id 的航点标签不出现 undefined',
  l2[2].label.includes('航点 #3') && !l2[2].label.includes('undefined'))
check('2.12 分组名保留', tree[1].label === '楼层3')

const only2 = buildPickTree(spec, 2)
eq('2.13 楼层筛选只留命中层', only2.length, 1)
eq('2.14 楼层筛选后该层航点数不变', only2[0].children.length, 3)
deep('2.15 floorsOf 升序去重', floorsOf(spec), [2, 3])

// 根节点自己就是航点的单航点树
const single = { root: wp('只有一个', 'ZZZ', 1, 1.5) }
deep('2.16 根就是航点时保留它', buildPickTree(single, 'all').map((n) => n.key), ['ZZZ'])
deep('2.17 没有 root 时返回空', buildPickTree({}, 'all'), [])
deep('2.18 root 为 null 时返回空', buildPickTree({ root: null }, 'all'), [])

/* ---- 筛选 ---- */
const hit = filterPickTree(tree, '航点4')
eq('2.19 关键字命中叶子', leavesOf(hit).length, 1)
eq('2.20 命中的叶子保留祖先链', hit.length, 1)
eq('2.21 祖先链是楼层3', hit[0].label, '楼层3')
eq('2.22 关键字命中 wp_id', leavesOf(filterPickTree(tree, 'BBB')).length, 1)
eq('2.23 关键字不命中就空', filterPickTree(tree, 'zzzz').length, 0)
eq('2.24 空关键字原样返回', filterPickTree(tree, '  ').length, tree.length)

/* ---- 可见顺序 ---- */
const allKeys = expandableKeys(tree)
eq('2.25 expandableKeys 含所有分组', allKeys.length, 2)
const pathsOf = (nodes) => leavesOf(nodes).map((l) => l.path)
deep('2.26 全展开时可见顺序 = 树顺序',
  flattenPickTree(tree, allKeys), pathsOf(tree))
// 收起"楼层3"后，它的两个航点不算"看得见"
const collapsed3 = allKeys.filter((k) => !k.includes('children/1'))
const vis3 = flattenPickTree(tree, collapsed3)
eq('2.27 收起的分组里的叶子不算可见', vis3.length, 3)
deep('2.28 全部收起时没有可见叶子', flattenPickTree(tree, []), [])

/* ---- Shift 范围 ---- */
const order = flattenPickTree(tree, allKeys)
deep('2.29 范围含两端', rangePaths(order, order[0], order[2]), order.slice(0, 3))
deep('2.30 反着选也是同一段',
  rangePaths(order, order[3], order[1]), order.slice(1, 4))
deep('2.31 锚点与目标相同就一个', rangePaths(order, order[1], order[1]), [order[1]])
deep('2.32 锚点缺失时退化成只选目标', rangePaths(order, null, order[2]), [order[2]])
deep('2.33 锚点已不可见时退化成只选目标',
  rangePaths(order, 'root/children/9/children/0', order[1]), [order[1]])
deep('2.34 目标不可见时什么都不选', rangePaths(order, order[0], 'nope'), [])
deep('2.35 空顺序不炸', rangePaths([], null, 'x'), [])
// 跨分组连选（楼层2 的最后一个 -> 楼层3 的第一个），中间不能被折叠的叶子插进来
deep('2.36 跨分组连选只含可见项',
  rangePaths(order, order[2], order[3]), [order[2], order[3]])
// 收起楼层3 后它的叶子不可见：拿它当目标就什么都不选（宁可不动，也不能悄悄
// 勾上一个用户看不见的航点），拿它当锚点则退化成只选目标
deep('2.37 目标在收起的分组里 -> 不选', rangePaths(vis3, order[2], order[3]), [])
deep('2.37b 锚点在收起的分组里 -> 只选目标', rangePaths(vis3, order[3], order[0]), [order[0]])

/* ---- 路径 -> key ---- */
const byPath = keyByPath(tree)
eq('2.38 keyByPath 覆盖全部叶子', Object.keys(byPath).length, 5)
deep('2.39 keysOfPaths 按顺序取 key', keysOfPaths(byPath, order.slice(0, 3)), ['AAA', 'BBB', order[2]])
deep('2.40 keysOfPaths 跳过未知路径', keysOfPaths(byPath, ['nope']), [])
// 两个航点共用 wp_id：只能算一个（waypoint_ids 里写两遍没有意义，只会让计数虚高）
const dup = { root: grp('g', [wp('a', 'SAME', 1, 1), wp('b', 'SAME', 2, 2)]) }
const dupLeaves = leavesOf(buildPickTree(dup, 'all'))
deep('2.41 wp_id 重复时去重', keysOfPaths(keyByPath(dupLeaves), dupLeaves.map((l) => l.path)), ['SAME'])
eq('2.42 但两个路径都还在树上（不会被吞掉）', dupLeaves.length, 2)

/* ---- 单点 / 批量合并 ---- */
deep('2.43 toggleKey 加上去排末尾', toggleKey(['a'], 'b'), ['a', 'b'])
deep('2.44 toggleKey 已有就删掉', toggleKey(['a', 'b'], 'a'), ['b'])
deep('2.45 toggleKey 保持原顺序', toggleKey(['a', 'b', 'c'], 'b'), ['a', 'c'])
deep('2.46 unionPick 不重复且保持顺序', unionPick(['a', 'b'], ['b', 'c']), ['a', 'b', 'c'])
deep('2.47 mergePick replace', mergePick(['a'], ['c', 'd'], 'replace'), ['c', 'd'])
deep('2.48 mergePick add', mergePick(['a'], ['b'], 'add'), ['a', 'b'])
deep('2.49 mergePick remove', mergePick(['a', 'b', 'c'], ['b'], 'remove'), ['a', 'c'])
deep('2.50 mergePick 脏 list 当空处理', mergePick(null, ['a'], 'add'), ['a'])

/* ---- 地图回写的"范围替换" ---- */
// 场景：先在楼层 2 挑了 AAA，再切到楼层 3 用地图框选 CCC。
// 地图只画得出楼层 3 的航点，直接替换会把 AAA 清掉（而且毫无提示）。
const scope3 = ['CCC', 'DDD']
deep('2.51 范围外已选的保留',
  mergeScopedPick(['AAA'], ['CCC'], scope3), ['AAA', 'CCC'])
deep('2.52 范围内被取消勾选的去掉',
  mergeScopedPick(['AAA', 'CCC'], [], scope3), ['AAA'])
deep('2.53 范围内的顺序照旧',
  mergeScopedPick(['CCC', 'AAA'], ['CCC', 'DDD'], scope3), ['CCC', 'AAA', 'DDD'])
deep('2.54 新出现的排末尾', mergeScopedPick([], ['DDD'], scope3), ['DDD'])
deep('2.55 空 scope 时什么都不动（地图没画出来就影响不到）',
  mergeScopedPick(['AAA'], [], []), ['AAA'])
deep('2.56 去重', mergeScopedPick(['AAA', 'AAA'], ['AAA'], scope3), ['AAA'])

/* ---- 分组勾选（整枝全选 / 半选） ---- */
// 分组自己不存"选了哪个分组"，勾它 = 把它下面所有叶子的 key 加进 *_ids。
// 所以半选/全选全靠叶子反推：这样筛选、楼层切换、档案变动都不会留下悬空引用。
const g2 = tree[0]                      // 楼层2：AAA / BBB / 无 wp_id 那个
const g3 = tree[1]                      // 楼层3：CCC / DDD
const g2keys = leafKeysOf(g2)
deep('2.57 leafKeysOf 取整枝叶子 key（树序）', g2keys, ['AAA', 'BBB', l2[2].key])
eq('2.58 没选任何子节点 -> none', groupPickInfo(g2, new Set()).state, 'none')
eq('2.59 子节点全选 -> all（勾选框打勾）',
  groupPickInfo(g2, new Set(g2keys)).state, 'all')
eq('2.60 只选了一部分 -> part（半选）', groupPickInfo(g2, new Set(['AAA'])).state, 'part')
eq('2.61 半选时 hit 与 total 分开报（行尾"1/3 个"）',
  `${groupPickInfo(g2, new Set(['AAA'])).hit}/${groupPickInfo(g2, new Set(['AAA'])).total}`,
  '1/3')
eq('2.62 兄弟分组不受影响', groupPickInfo(g3, new Set(['AAA'])).state, 'none')
eq('2.63 全选后再点 -> remove（再点一次能撤回）',
  groupToggleMode(g2, new Set(g2keys)), 'remove')
eq('2.64 半选时点 -> add', groupToggleMode(g2, new Set(['AAA'])), 'add')
eq('2.65 没选时点 -> add', groupToggleMode(g2, new Set()), 'add')
// 关键：整枝全选必须是 add 不能是 replace，否则会把别的分组挑好的清掉
deep('2.66 整枝全选不吞掉别处已选的（add 而非 replace）',
  mergePick(['CCC'], g2keys, groupToggleMode(g2, new Set())), ['CCC', ...g2keys])
deep('2.67 整枝取消只去掉这一枝',
  mergePick([...g2keys, 'CCC'], g2keys, groupToggleMode(g2, new Set(g2keys))), ['CCC'])
eq('2.68 空分组 -> null（点了什么都不做）',
  groupToggleMode({ key: 'x', label: 'x', path: 'x', isLeaf: false, children: [] }, new Set()),
  null)
// 叶子当"只有一个元素的分组"用：组件里就不必分两路写
eq('2.69 叶子也能走 groupPickInfo', groupPickInfo(l2[0], new Set(['AAA'])).state, 'all')
eq('2.70 叶子没选时是 none', groupPickInfo(l2[0], new Set()).state, 'none')

// wp_id 重复：去重后 total 才是 1，否则勾满了也永远显示半选
const dupNodes = buildPickTree(dup, 'all')
eq('2.71 重复 wp_id 的分组 total 去重', groupPickInfo(dupNodes[0], new Set()).total, 1)
eq('2.72 重复的分组选一个就到 all（不会一直半选）',
  groupPickInfo(dupNodes[0], new Set(['SAME'])).state, 'all')

// 筛选态下勾分组 = 只勾命中的那些（与"全选（当前筛选）"同一口径）
const fh = filterPickTree(tree, '航点4')
eq('2.73 筛选后分组只剩命中的叶子', groupPickInfo(fh[0], new Set()).total, 1)

/* ============================================================ 3. 地图数据 */

const mw = pickMapWaypoints(leavesOf(tree))
eq('3.1 地图航点数 = 叶子数', mw.length, 5)
check('3.2 地图航点带 path（回查 key 用）', mw.every((w) => typeof w.path === 'string' && w.path))
check('3.3 地图航点 x 都是有限数', mw.every((w) => Number.isFinite(w.x)))
check('3.4 地图航点 label 不带 undefined', mw.every((w) => !w.label.includes('undefined')))
eq('3.5 地图上的短名优先 name', mw[0].label, '航点1')
eq('3.6 无 name 时短名回落 wp_id', shortLabel({ name: '', wp_id: 'ZZZ', index: 9 }), 'ZZZ')
eq('3.7 都没有时回落航点 #n', shortLabel({ name: '', wp_id: '', index: 9 }), '航点 #9')

const tr = pickTrackOf(spec)
eq('3.8 找到第一条轨道', tr.nodes.length, 2)
eq('3.9 轨道条数', tr.count, 1)
check('3.10 轨道长度 = 采样弧长 (m)', Math.abs(tr.lengthM - 60) < 0.5, `got=${tr.lengthM}`)
eq('3.11 没有轨道时 nodes 为空', pickTrackOf({ root: grp('g', [wp('a', 'A', 1, 1)]) }).nodes.length, 0)
eq('3.12 没有轨道时 lengthM 为 0（面板据此不报越界）',
  pickTrackOf({ root: grp('g', [wp('a', 'A', 1, 1)]) }).lengthM, 0)
eq('3.13 多条轨道时只取第一条并报数',
  pickTrackOf({
    root: grp('g', [
      { type: 'TrackNode', properties: {}, children: [{ type: 'TrackEndpointNode', properties: { x: 0, y: 0 } }, { type: 'TrackEndpointNode', properties: { x: 10, y: 0 } }] },
      { type: 'TrackNode', properties: {}, children: [] },
    ]),
  }).count, 2)

const leaves2 = leavesOf(buildPickTree(spec, 2))
deep('3.14 越界判定：楼层2 的都在 60 m 内', outOfTrackKeys(leaves2, 60), [])
deep('3.15 越界判定：量程很小时全报',
  outOfTrackKeys(leaves2, 5).length, 3)
deep('3.16 量程为 0 时一条都不报（没画轨道，地图用兜底量程）',
  outOfTrackKeys(leaves2, 0), [])
deep('3.17 负弧长也算越界',
  outOfTrackKeys([{ key: 'N', data: { x: -1 } }], 60), ['N'])

/* ============================================================ 4. 测点树 */

/**
 * 造一份贴近真实的测点档案：变电站 > 电压等级 > 间隔 > 设备 的四层目录，
 * 外加一个**空目录**（刚建好还没放测点）和一个**未归类测点**。
 *
 * 未归类那条是重点：它不在任何目录里，按目录展开的树永远碰不到它。
 * 没有「未归类」分组的话，用户会看到"档案里明明有 N 个测点，这里只有 N-1 个"
 * 却找不到原因。
 */
const dir = (id, name, parent_id = null) => ({
  id, name, parent_id, role: 'custom', child_count: 0, point_count: 0,
})
const pt = (id, name, directory_id, code = '', active = true) => ({
  id, name, code, directory_id, active,
})
const dirs = [
  dir('D1', '变电站A'),
  dir('D2', '10kV', 'D1'),
  dir('D3', '出线间隔1', 'D2'),
  dir('D4', '主变柜', 'D3'),
  dir('D5', '出线间隔2', 'D2'),
  dir('D9', '空设备', 'D3'),            // 空目录：要留着
]
const pts = [
  pt('P1', '温度1', 'D4', 'T-01'),
  pt('P2', '温度2', 'D4', 'T-02'),
  pt('P3', '湿度1', 'D5', 'H-01', false),
  pt('P4', '孤立点', null),              // 未归类
  pt('P5', '孤儿点', 'DX'),              // 指向一个已经不存在的目录 -> 也算未归类
]

const ptree = buildPointPickTree(dirs, pts)
eq('4.1 顶层是根目录 + 未归类两组', ptree.length, 2)
eq('4.2 根目录名', ptree[0].label, '变电站A')
eq('4.3 目录 key 带前缀（与测点 id 不会撞）', ptree[0].key, 'd:D1')
eq('4.4 空目录要留着', JSON.stringify(ptree).includes('空设备'), true)
const pleaves = leavesOf(ptree)
eq('4.5 叶子数 = 测点数（未归类的也在）', pleaves.length, 5)
deep('4.6 叶子 key 就是测点 id',
  pleaves.map((n) => n.key).sort(), ['P1', 'P2', 'P3', 'P4', 'P5'])
eq('4.7 叶子路径带前缀', pleaves[0].path.startsWith('p:'), true)
check('4.8 未归类分组存在', JSON.stringify(ptree).includes('未归类'))
check('4.9 未归类分组的 key 是伪目录 id', JSON.stringify(ptree).includes(ROOT_GROUP))
eq('4.10 未归类里收了两个（null 与失效目录）',
  leavesOf(ptree).filter((n) => n.data.directory_id === null).length, 2)
eq('4.11 测点目录名回填', pleaves.find((n) => n.key === 'P1').data.directory_name, '主变柜')
eq('4.12 未归类点的 directory_name 是「未归类」',
  pleaves.find((n) => n.key === 'P4').data.directory_name, '未归类')
eq('4.13 停用状态带出来', pleaves.find((n) => n.key === 'P3').data.active, false)
eq('4.14 编号带出来', pleaves.find((n) => n.key === 'P1').data.code, 'T-01')

// 目录顺序必须跟着接口给的顺序（不重排），否则同一目录在两个页面上位置不同
deep('4.15 子目录顺序跟着输入顺序',
  (ptree[0].children.find((n) => n.key === 'd:D2')).children.map((n) => n.key),
  ['d:D3', 'd:D5'])
// 直属测点排在子目录之前（"这个设备自己的点"比"它的子设备"更常用）
deep('4.16 直属测点排在子目录前',
  buildPointPickTree(
    [dir('A', '甲'), dir('B', '乙', 'A')],
    [pt('X', '点', 'A')],
  )[0].children.map((n) => n.key), ['X', 'd:B'])
deep('4.16b 设备下的测点顺序跟着接口给的点序',
  ptree[0].children[0].children[0].children[0].children.map((n) => n.key), ['P1', 'P2'])

deep('4.17 childrenOfDirs 分组', childrenOfDirs(dirs).get('D2').map((d) => d.id), ['D3', 'D5'])
deep('4.18 descendantDirs 含自身与全部后代',
  descendantDirs(dirs, 'D2').sort(), ['D2', 'D3', 'D4', 'D5', 'D9'])
deep('4.19 空档案不炸', buildPointPickTree([], []), [])
deep('4.20 只有未归类测点时也能出树',
  buildPointPickTree([], [pt('P9', '孤', null)]).map((n) => n.label), ['未归类'])
eq('4.21 没有测点但有目录时目录还在',
  buildPointPickTree([dir('D1', '甲')], []).length, 1)

// 筛选 / 范围选 / 合并：与航点树**共用**同一套实现，这里验一遍"接得上"
const pon = expandableKeys(ptree)
eq('4.22 可展开的分组数', pon.length, 7)   // 5 个目录 + 未归类 + ... 见下
const pvis = flattenPickTree(ptree, pon)
eq('4.23 全展开时可见叶子数', pvis.length, 5)
deep('4.24 Shift 整段选（两个点之间）',
  rangePaths(pvis, pvis[0], pvis[1]), [pvis[0], pvis[1]])
deep('4.25 收起全部后没有可见项', flattenPickTree(ptree, []), [])
eq('4.26 关键字命中测点名', leavesOf(filterPickTree(ptree, '湿度')).length, 1)
// 编号不在标签里，要靠 extra 回调补进可搜索文本（面板传的是测点 code）
eq('4.27 关键字命中测点编号（走 extra 回调）',
  leavesOf(filterPickTree(ptree, 'T-02', (n) => n.data?.code || '')).length, 1)
eq('4.27b 不传 extra 时编号搜不到（说明 extra 是必需的）',
  leavesOf(filterPickTree(ptree, 'T-02')).length, 0)
// 目录名命中 -> 整枝带出来（出线间隔1 下 2 个 + 出线间隔2 下 1 个）
eq('4.28 关键字命中目录名时整枝带出',
  leavesOf(filterPickTree(ptree, '出线间隔')).length, 3)
deep('4.29 pointLabel 优先 name', pointLabel({ name: '甲', id: 'X' }), '甲')
deep('4.30 pointLabel 无 name 回落 id', pointLabel({ name: '', id: 'X' }), 'X')

const pByPath = keyByPath(ptree)
deep('4.31 keysOfPaths 换成测点 id', keysOfPaths(pByPath, pvis), ['P1', 'P2', 'P3', 'P4', 'P5'])
deep('4.32 地图式范围替换在测点面板同样成立',
  mergeScopedPick(['P1'], ['P3'], ['P3']), ['P1', 'P3'])

/* ---- pickTree 的通用件 ---- */
const idx = indexPickTree(ptree)
eq('4.33 indexPickTree 覆盖全部节点', idx.index.size, 12)   // 6 目录 + 未归类 + 5 测点
eq('4.34 目录的叶子计数（含后代，不含未归类的）', idx.counts.get('d:D1'), 3)
eq('4.35 空目录计数为 0', idx.counts.get('d:D9'), 0)
eq('4.36 测点行计数为 1', idx.counts.get('p:P1'), 1)
const semi = toSemiTree(ptree)
eq('4.37 Semi 树数据用路径当 key', semi[0].key, 'd:D1')
eq('4.38 叶子标成 isLeaf', leavesOf(ptree)[0] && toSemiTree([leavesOf(ptree)[0]])[0].isLeaf, true)
eq('4.39 分组不给 isLeaf', semi[0].isLeaf, false)

/* ---- 分组（目录）勾选 ---- */
const dAll = ptree[0]                   // 变电站A -> P1 P2 P3（P4/P5 在未归类里）
eq('4.40 目录的 total 含全部后代', groupPickInfo(dAll, new Set()).total, 3)
deep('4.41 目录的叶子 key 是测点 id（树序）', leafKeysOf(dAll), ['P1', 'P2', 'P3'])
eq('4.42 目录下选一个 -> part', groupPickInfo(dAll, new Set(['P1'])).state, 'part')
eq('4.43 目录下全选 -> all', groupPickInfo(dAll, new Set(['P1', 'P2', 'P3'])).state, 'all')
deep('4.44 勾目录 = 整枝加进来（保序、追加到末尾）',
  mergePick(['P4'], leafKeysOf(dAll), groupToggleMode(dAll, new Set())),
  ['P4', 'P1', 'P2', 'P3'])
// 子目录（主变柜）只管自己那一枝
const dMain = idx.index.get('d:D4')
eq('4.45 子目录只算自己这一枝', groupPickInfo(dMain, new Set(['P1', 'P2'])).state, 'all')
eq('4.46 父目录此时是半选', groupPickInfo(dAll, new Set(['P1', 'P2'])).state, 'part')
// 空目录：档案里刚建好还没放测点的目录，没有可勾的东西
const dEmpty = idx.index.get('d:D9')
eq('4.47 空目录 total 为 0', groupPickInfo(dEmpty, new Set()).total, 0)
eq('4.48 空目录状态 none（不显示半选）', groupPickInfo(dEmpty, new Set()).state, 'none')
eq('4.49 点空目录什么都不做', groupToggleMode(dEmpty, new Set()), null)
// 未归类分组同样是"整枝"
const dLoose = ptree[1]
deep('4.50 未归类分组整枝全选', leafKeysOf(dLoose), ['P4', 'P5'])

/* ============================================================ 5. 源码级断言 */

const strip = (s) => s.replace(/\/\*[\s\S]*?\*\//g, '').replace(/^\s*\/\/.*$/gm, '')
const read = (p) => strip(readFileSync(join(root, p), 'utf8'))

const map = read('src/components/TrackMap.tsx')
// 框选必须走共用纯函数，别在组件里再写一遍合并逻辑
check('5.1 TrackMap 用 applyPickMode 合并框选', map.includes('applyPickMode('))
check('5.2 TrackMap 用 resolvePickMode 解析修饰键', map.includes('resolvePickMode('))
check('5.3 框选的基准是按下时的快照（marqueeBase.current）',
  /marqueeBase\.current = new Set\(selectedPaths\)/.test(map))
check('5.4 实际模式存在 ref 里（拖拽途中读 state 会串味）',
  /marqueeMode\.current = mode/.test(map))
check('5.5 框选回写读的是 ref 而不是 state',
  /applyPickMode\(marqueeBase\.current, hit, marqueeMode\.current\)/.test(map))
// replace 模式下按下即清空：否则要等指针划到第一个点才有反馈
check('5.6 replace 按下时先清空选择', /if \(mode === 'replace'\) onSelectionChange\(new Set\(\)\)/.test(map))
// 挑选模式：藏掉编辑入口、右键不弹菜单、单击即切换
check('5.7 pickerMode 下右键不弹菜单', /if \(pickerMode\) return false/.test(map))
check('5.8 pickerMode 下藏掉绘制轨道按钮', /\{!pickerMode && \(/.test(map))
check('5.9 pickerMode 下单击即切换（挑选语义）', /if \(pickerMode \|\| e\.shiftKey/.test(map))
check('5.10 pickerMode 下不预备拖动航点（没有回写回调，拖了也没用）',
  /onMoveWaypoint\) \{/.test(map))
check('5.11 工具栏有框选模式开关', map.includes('PICK_MODES.map('))

const tools = read('src/components/PlanNodeTools.tsx')
// 两个面板共用同一套树视图/按钮条/手势，别各写一份
check('5.12 共用 PickTreeView', /function PickTreeView</.test(tools))
check('5.13 两个面板都挂了 PickTreeView', (tools.match(/<PickTreeView/g) || []).length === 2)
check('5.14 共用 PickBulkBar / PickExpandBar',
  (tools.match(/<PickBulkBar/g) || []).length === 2
  && (tools.match(/<PickExpandBar/g) || []).length === 2)
check('5.15 行点击由 renderLabel 里的元素接管', tools.includes('renderLabel={'))
check('5.16 Shift 整段选走 rangePaths', tools.includes('rangePaths('))
check('5.17 Shift = add、Alt = remove',
  tools.includes("applyPaths(paths, 'add')") && tools.includes("applyPaths([n.path], 'remove')"))
// Shift 连点必须从同一个锚点重算区间
check('5.18 Shift 连点不移动锚点', /if \(!e\.shiftKey\) anchor\.current = n\.path/.test(tools))
check('5.19 航点面板挂了地图画布', tools.includes('<TrackMap'))
check('5.20 画布是只读挑选模式', /\n\s+pickerMode\n/.test(tools))
check('5.21 地图回写走"范围替换"', tools.includes('mergeScopedPick('))
check('5.22 航点面板不再用扁平勾选列表', !/shown\.map\(\(w\)/.test(tools))
check('5.23 航点面板不再自己抽航点（交给 waypointPick）',
  !tools.includes('collectWaypoints') && tools.includes('buildPickTree('))
check('5.24 面板不再从 properties.floor 取楼层', !tools.includes('properties?.floor'))
check('5.25 换文件时清掉筛选/展开/锚点',
  /setKw\(''\)/.test(tools) && /setFloor\('all'\)/.test(tools) && /anchor\.current = null/.test(tools))
// 测点面板：目录树 + 全量加载 + 未归类 + 按编号搜
check('5.26 测点面板用 pointPick 建树', tools.includes('buildPointPickTree('))
check('5.27 测点面板不再用分页列表', !tools.includes('上一页') && !tools.includes('下一页'))
check('5.28 测点面板按编号搜（给 filterPickTree 传 extra）',
  /filterPickTree\(treeData, kw, \(n\) => n\.data\?\.code/.test(tools))
check('5.29 测点面板有分页上限保护', /POINT_MAX_PAGES/.test(tools))
check('5.30 测点面板默认展开策略分大小档案', /totalCount <= POINT_PAGE/.test(tools))
check('5.31 测点面板写 point_ids', tools.includes("idsField=\"point_ids\""))
check('5.32 航点面板写 waypoint_ids', tools.includes("idsField=\"waypoint_ids\""))

const css = readFileSync(join(root, 'src/styles.css'), 'utf8')
// 行接管点击的前提：勾选框不能自己吃掉点击，否则一次点击触发两遍、一开一关抵消
check('5.33 勾选框 pointer-events: none（行接管点击）',
  /\.pp-row \.semi-checkbox \{\s*pointer-events: none;/.test(css))
check('5.34 树行有 pointer 光标', /\.pp-row \{[\s\S]*?cursor: pointer;/.test(css))

// 两棵树都不能把"挑选用的引用"带进下发的巡检任务（与检测框那条同源）
const build = read('src/utils/inspectionBuild.ts')
check('5.35 下发链路里没有 waypoint_ids（挑选只在编排侧）', !build.includes('waypoint_ids'))
check('5.36 下发链路里没有 point_ids', !build.includes('point_ids'))

// 分组勾选：半选要画出来、点击要被单独一格接住、全选要走 add
check('5.37 分组勾选框画半选', /indeterminate=\{info\.state === 'part'\}/.test(tools))
check('5.38 分组勾选框的点击被 .pp-pick 接住且不冒泡到行上（否则"勾一下顺便收起"）',
  /className="pp-pick"[\s\S]{0,300}?e\.stopPropagation\(\); onGroupClick\(n, e\)/.test(tools))
check('5.39 两个面板都传了 onGroupClick',
  (tools.match(/onGroupClick=\{onGroupClick\}/g) || []).length === 2)
check('5.40 分组全选走 mergePick（航点/测点各一处，且不是 replace）',
  (tools.match(/mergePick\(value\?\.waypoint_ids, keys, mode\)/g) || []).length === 1
  && (tools.match(/mergePick\(value\?\.point_ids, keys, mode\)/g) || []).length === 1)
check('5.41 分组行不再用裸 pp-group（与叶子行共用 pp-row）',
  !/className="pp-group"/.test(tools))
// 分组行不在可见叶子顺序里，把锚点挪过去会让下一次 Shift 点选退化成"只选一个"
const grpFn = tools.match(/const onGroupClick = [\s\S]*?applyKeys\(keys, mode\)/)
check('5.42 分组点击不动锚点', !!grpFn && !grpFn[0].includes('anchor.current'))
// 分组的勾选态必须由已选集合**反推**，不能在节点上另存一份（存了就会和 *_ids 打架）
check('5.43 分组勾选态走 groupPickInfo 反推', /groupPickInfo\(n, pickedSet\)/.test(tools))
check('5.44 分组默认动作走 groupToggleMode', /groupToggleMode\(n, pickedSet\)/.test(tools))
check('5.45 半选行有独立样式类', /pp-row-part/.test(tools) && /\.pp-row-part/.test(css))
check('5.46 勾选区可点（cursor: pointer）', /\.pp-pick \{[\s\S]*?cursor: pointer;/.test(css))

/* ============================================================ 汇总 */

rmSync(out, { recursive: true, force: true })
if (fails.length) {
  console.error(`\n挑选面板回归：${pass} 项通过，${fails.length} 项失败`)
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
console.log(`挑选面板回归：${pass} 项通过，0 项失败`)
