/**
 * 航点树编排「拖拽落点」回归脚本。
 *
 * 验证两块东西：
 *   1. Semi Tree 的 onDrop 参数 -> 落点语义（`resolveDropKind`）。
 *      Semi 给的 dropPosition 是「相对方向 + 目标同级下标」的**绝对下标**，
 *      拿它当方向用会把绝大多数"插到前面"误判成"插到后面"。
 *   2. 落点 -> spec 改写（moveNodeInSpec / batchMoveNodes）：
 *      非法落点被拒且 spec 不被改坏、同父/跨父/多选的插入位置正确。
 *
 * 关键：**不手抄源码**——用 tsc 编译真实 TS 源再 import。
 * 运行：node scripts/verify-tree-drag.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, writeFileSync, existsSync, readFileSync, readdirSync, statSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'ts-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath, [tscEntry,
    'src/utils/specTree.ts', 'src/utils/trackSpec.ts',
    '--outDir', out, '--rootDir', 'src',
    '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
    '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

// tsc 不会给相对 import 补 .js，Node 的 ESM 又强制要求带扩展名 —— 补一下
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

const M = await import(pathToFileURL(join(out, 'utils', 'specTree.js')).href)
const {
  SEP, getNodeByPath, parentPathOf, topLevelPaths,
  moveNodeInSpec, batchMoveNodes, resolveDropKind,
} = M

/* ---- 真实数据构造 spec ---- */

function buildSpec() {
  const raw = JSON.parse(readFileSync(resolve(here, '../../backend/tests/test_inspection.json'), 'utf-8'))
  const floors = {}
  for (const f of raw) floors[f.floor] = f
  const root = { type: 'GroupNode', properties: { name: '巡检任务' }, children: [] }
  let wpCount = 0
  let actCount = 0
  for (const floorNo of Object.keys(floors).sort()) {
    const f = floors[floorNo]
    const fg = { type: 'GroupNode', properties: { name: `楼层${f.floor}` }, children: [] }
    for (const wp of f.waypoint || []) {
      const wnode = {
        type: 'WaypointNode',
        properties: { name: wp.steer_point_name, x: wp.x, y: wp.y },
        children: [],
      }
      wpCount++
      for (const a of wp.action || []) {
        wnode.children.push({
          type: 'ActionPointNode',
          properties: { name: `动作-${a.type}`, action_type: a.type },
        })
        actCount++
      }
      fg.children.push(wnode)
    }
    root.children.push(fg)
  }
  // 样例数据里 name 可能缺失且重复（实测 steer_point_name 全是 None），
  // 顺序断言必须靠自打的 __uid，否则全是 undefined===undefined 的假绿。
  let uid = 0
  ;(function tag(n) { n.__uid = ++uid; (n.children || []).forEach(tag) })(root)
  return { root, wpCount, actCount }
}

/* ---- 断言工具 ---- */

let pass = 0
const failures = []
function check(name, cond, extra = '') {
  if (cond) { pass++; return }
  failures.push(`${name} ${extra}`)
}
/** 子节点的唯一标记序列（不是名字：样例数据里名字可能全是空） */
function marks(node) {
  return (node.children || []).map((c) => c.__uid)
}
function snapshot(spec) { return JSON.stringify(spec) }

const SEP_ = SEP

/* ---- 0. 落点判定：Semi 的 dropPosition 是绝对下标，不是方向 ---- */

/** 造一个 Semi 会传给 onDrop 的参数（dropPosition = 相对方向 + 目标同级下标） */
const dropProps = (targetIdx, rel, level = 0) => ({
  dragNode: { key: `root${SEP}children${SEP}9`, pos: `0-9` },
  node: { key: `root${SEP}children${SEP}${level}${SEP}children${SEP}${targetIdx}`, pos: `0-${level}-${targetIdx}` },
  dropPosition: targetIdx + rel,
  dropToGap: rel !== 0,
})

{
  // 落在节点上：dropToGap=false，与 dropPosition 无关
  check('落在节点上 -> on（索引0）',
    resolveDropKind({ ...dropProps(0, 0), dropToGap: false }) === 'on')
  check('落在节点上 -> on（索引5，dropPosition=5）',
    resolveDropKind({ ...dropProps(5, 0), dropToGap: false }) === 'on')

  // 前后间隙：任意下标都要判对（这里就是"插到 A 前变成插到 A 后"的那个 bug）
  for (let i = 0; i <= 6; i++) {
    check(`目标下标 ${i} + 上间隙 -> before`, resolveDropKind(dropProps(i, -1)) === 'before',
      JSON.stringify(dropProps(i, -1)))
    check(`目标下标 ${i} + 下间隙 -> after`, resolveDropKind(dropProps(i, 1)) === 'after',
      JSON.stringify(dropProps(i, 1)))
  }

  // 明确复现用户报的现象：目标是同级第 5 个，想插到它前面
  const bugCase = { dropToGap: true, dropPosition: 4, node: { key: 'root/children/0/children/5', pos: '0-0-5' } }
  check('回归：目标下标5、dropPosition=4 判定为 before（不是 after）',
    resolveDropKind(bugCase) === 'before')
  check('回归：旧写法 dropPosition<0 在该例上确实是错的（说明 bug 真实存在）',
    !(bugCase.dropPosition < 0))

  // 没有 pos 时退回从 key 取下标
  check('无 pos 时从 key 解析下标 -> before',
    resolveDropKind({ dropToGap: true, dropPosition: 3, node: { key: 'root/children/0/children/4' } }) === 'before')
  check('无 pos 时从 key 解析下标 -> after',
    resolveDropKind({ dropToGap: true, dropPosition: 5, node: { key: 'root/children/0/children/4' } }) === 'after')

  // 边界/异常输入不许抛异常
  check('目标是 root 时不炸（退化成 on）',
    resolveDropKind({ dropToGap: true, dropPosition: 0, node: { key: 'root', pos: '0' } }) === 'on')
  check('dropPosition 为 null 时不炸', resolveDropKind({ dropToGap: true, dropPosition: null }) === 'on')
  check('空参数不炸', resolveDropKind(undefined) === 'on')
}

/* ---- 0b. 端到端：Semi 事件 -> 落点 -> spec，位置与意图一致 ---- */
{
  const f0 = `root${SEP}children${SEP}0`
  const p = (i) => `${f0}${SEP}children${SEP_}${i}`
  const semiDrop = (dragIdx, targetIdx, rel) => ({
    dragNode: { key: p(dragIdx), pos: `0-0-${dragIdx}` },
    node: { key: p(targetIdx), pos: `0-0-${targetIdx}` },
    dropPosition: targetIdx + rel,
    dropToGap: rel !== 0,
  })

  // 把第 0 个拖到第 4 个「之前」-> 期望落在下标 3（第4个让位后移）
  let { root } = buildSpec()
  let n0 = marks(getNodeByPath({ root }, f0))
  let kind = resolveDropKind(semiDrop(0, 4, -1))
  check('端到端：拖到第4之前 判定为 before', kind === 'before', kind)
  let r = moveNodeInSpec(root, p(0), p(4), kind)
  let n1 = marks(getNodeByPath({ root }, f0))
  check('端到端：拖到第4之前 执行成功', r.ok, JSON.stringify(r))
  // 摘掉第0个后，原第4个前移到下标3，插进去 => [1,2,3,0,4,5]
  check('端到端：拖到第4之前 落点紧跟在原第4个前面',
    n1[3] === n0[0] && n1[4] === n0[4] && n1[5] === n0[5],
    `实际 [${n1.slice(3, 6)}] 期望 [${n0[0]},${n0[4]},${n0[5]}]`)
  check('端到端：拖到第4之前 节点数不变', n1.length === n0.length)

  // 把第 0 个拖到第 4 个「之后」-> 期望落在下标 4
  ;({ root } = buildSpec())
  n0 = marks(getNodeByPath({ root }, f0))
  kind = resolveDropKind(semiDrop(0, 4, 1))
  check('端到端：拖到第4之后 判定为 after', kind === 'after', kind)
  r = moveNodeInSpec(root, p(0), p(4), kind)
  n1 = marks(getNodeByPath({ root }, f0))
  check('端到端：拖到第4之后 执行成功', r.ok, JSON.stringify(r))
  // [1,2,3,4,0,5]：插到原第4个的后面
  check('端到端：拖到第4之后 紧跟在原第4个后面',
    n1[3] === n0[4] && n1[4] === n0[0] && n1[5] === n0[5],
    `实际 [${n1.slice(3, 6)}] 期望 [${n0[4]},${n0[0]},${n0[5]}]`)

  // before 与 after 必须给出**不同**结果（否则说明方向被吃掉了）。
  // 注意用自打的 __uid 比较：样例数据里 name 可能缺失且重复，靠名字比对不出差异。
  ;({ root } = buildSpec())
  let uid = 0
  ;(function tag(n) { n.__uid = ++uid; (n.children || []).forEach(tag) })(root)
  const rBefore = JSON.parse(snapshot(root))
  const rAfter = JSON.parse(snapshot(root))
  moveNodeInSpec(rBefore, p(0), p(4), resolveDropKind(semiDrop(0, 4, -1)))
  moveNodeInSpec(rAfter, p(0), p(4), resolveDropKind(semiDrop(0, 4, 1)))
  const uidsOf = (r) => (getNodeByPath({ root: r }, f0).children || []).map((c) => c.__uid).join('|')
  check('端到端：before 与 after 结果不同', uidsOf(rBefore) !== uidsOf(rAfter),
    `before [${uidsOf(rBefore)}] after [${uidsOf(rAfter)}]`)
}

/* ---- 1. 非法落点必须被拒绝且不改坏 spec ---- */
{
  const { root } = buildSpec()
  const before = snapshot(root)

  // 拖到自身
  let r = moveNodeInSpec(root, `root${SEP_}children${SEP_}0`, `root${SEP_}children${SEP_}0`, 'on')
  check('拖到自身被拒绝', !r.ok)
  // 拖入自己的子树（楼层0 拖进它的第一个航点）
  r = moveNodeInSpec(root, `root${SEP_}children${SEP_}0`,
    `root${SEP_}children${SEP_}0${SEP_}children${SEP_}0${SEP_}children${SEP_}0`, 'on')
  check('拖入自己子孙被拒绝', !r.ok, JSON.stringify(r))
  // 拖入更深的后代内部
  r = moveNodeInSpec(root, `root${SEP_}children${SEP_}0`, `root${SEP_}children${SEP_}0`, 'before')
  check('拖到自己前一位（同一位置）被拒绝', !r.ok)
  check('非法操作后 spec 未被改坏', snapshot(root) === before, '  <-- spec 变了！')
}

/* ---- 2. 同父内排序 ---- */
{
  const f0 = `root${SEP_}children${SEP_}0`
  const p = (i) => `${f0}${SEP_}children${SEP_}${i}`

  // 把第 0 个移到第 2 个之后 -> 期望 [1,2,0,...]
  let { root } = buildSpec()
  let n0 = marks(getNodeByPath({ root }, f0))
  let r = moveNodeInSpec(root, p(0), p(2), 'after')
  check('同父 0 -> 第2之后 成功', r.ok, JSON.stringify(r))
  let n1 = marks(getNodeByPath({ root }, f0))
  check('同父 0 -> 第2之后 顺序正确',
    n1[0] === n0[1] && n1[1] === n0[2] && n1[2] === n0[0] && n1.length === n0.length,
    `期望 [${n0[1]},${n0[2]},${n0[0]}] 实际 [${n1.slice(0, 3)}]`)

  // 把中间节点上移到最前
  ;({ root } = buildSpec())
  n0 = marks(getNodeByPath({ root }, f0))
  r = moveNodeInSpec(root, p(3), p(0), 'before')
  n1 = marks(getNodeByPath({ root }, f0))
  check('同父 3 -> 第0之前 成功', r.ok, JSON.stringify(r))
  check('同父 3 -> 第0之前 落点在第0位', n1[0] === n0[3], `实际首位 ${n1[0]} 期望 ${n0[3]}`)
  check('同父移动不丢节点', n1.length === n0.length)

  // 相邻交换：把 1 移到 0 之前
  ;({ root } = buildSpec())
  n0 = marks(getNodeByPath({ root }, f0))
  r = moveNodeInSpec(root, p(1), p(0), 'before')
  n1 = marks(getNodeByPath({ root }, f0))
  check('相邻交换 1->0之前', r.ok && n1[0] === n0[1] && n1[1] === n0[0], `[${n1.slice(0, 2)}]`)

  // 把 0 移到 1 之后（等价于相邻交换的另一方向）
  ;({ root } = buildSpec())
  n0 = marks(getNodeByPath({ root }, f0))
  r = moveNodeInSpec(root, p(0), p(1), 'after')
  n1 = marks(getNodeByPath({ root }, f0))
  check('相邻交换 0->1之后', r.ok && n1[0] === n0[1] && n1[1] === n0[0], `[${n1.slice(0, 2)}]`)
}

/* ---- 3. 拖到节点内部（成为首个子节点） ---- */
{
  const f0 = `root${SEP_}children${SEP_}0`
  const p = (i) => `${f0}${SEP_}children${SEP_}${i}`
  const { root } = buildSpec()
  const n0 = marks(getNodeByPath({ root }, f0))
  const target0 = getNodeByPath({ root }, p(0))
  const origKidCount = (target0.children || []).length
  const origKidUid = target0.children?.[0]?.__uid
  const r = moveNodeInSpec(root, p(2), p(0), 'on')
  check('拖到节点内部成功', r.ok, JSON.stringify(r))
  const target = getNodeByPath({ root }, p(0))
  check('成为目标首个子节点', target.children[0].__uid === n0[2],
    `实际 ${target.children[0].__uid}`)
  check('目标原有子节点被保留', target.children.length === origKidCount + 1,
    `子节点数 ${target.children.length}，期望 ${origKidCount + 1}`)
  check('原有首个子节点被挤到第二位', target.children[1]?.__uid === origKidUid)
  check('源父级少了一个节点', marks(getNodeByPath({ root }, f0)).length === n0.length - 1)
}

/* ---- 4. 跨父移动 ---- */
{
  const f0 = `root${SEP_}children${SEP_}0`
  const f1 = `root${SEP_}children${SEP_}1`
  const { root } = buildSpec()
  const a0 = marks(getNodeByPath({ root }, f0))
  const b0 = marks(getNodeByPath({ root }, f1))
  const r = moveNodeInSpec(root, `${f0}${SEP_}children${SEP_}0`, `${f1}${SEP_}children${SEP_}0`, 'before')
  check('跨父插到目标之前成功', r.ok, JSON.stringify(r))
  const a1 = marks(getNodeByPath({ root }, f0))
  const b1 = marks(getNodeByPath({ root }, f1))
  check('跨父：源楼层减少1', a1.length === a0.length - 1)
  check('跨父：目标楼层增加1', b1.length === b0.length + 1)
  check('跨父：插入位置正确', b1[0] === a0[0], `实际首位 ${b1[0]} 期望 ${a0[0]}`)

  // 跨父拖到楼层内部
  const { root: root2 } = buildSpec()
  const r2 = moveNodeInSpec(root2, `${f0}${SEP_}children${SEP_}0`, f1, 'on')
  check('跨父拖入楼层内部成功', r2.ok, JSON.stringify(r2))
  const t = getNodeByPath({ root: root2 }, f1)
  check('跨父拖入：成为首个子节点', t.children[0].__uid === a0[0])
  check('跨父拖入未丢节点', t.children.length === b0.length + 1)
}

/* ---- 5. 多选整批移动 ---- */
{
  const f0 = `root${SEP_}children${SEP_}0`
  const f1 = `root${SEP_}children${SEP_}1`
  const p = (i) => `${f0}${SEP_}children${SEP_}${i}`

  // 同父把连续 3 个移到末尾
  let { root } = buildSpec()
  let n0 = marks(getNodeByPath({ root }, f0))
  let r = batchMoveNodes(root, [p(0), p(1), p(2)], p(n0.length - 1), 'after')
  check('批量移到末尾成功', r.ok, JSON.stringify(r))
  let n1 = marks(getNodeByPath({ root }, f0))
  check('批量移到末尾：长度不变', n1.length === n0.length)
  check('批量移到末尾：相对次序保持',
    n1.slice(-3).join('|') === [n0[0], n0[1], n0[2]].join('|'),
    `实际尾部 ${n1.slice(-3)} 期望 ${[n0[0], n0[1], n0[2]]}`)
  check('批量移到末尾：其余节点仍在', n1.slice(0, 3).join('|') === [n0[3], n0[4], n0[5]].join('|'))

  // 批量拖入另一个节点的内部
  ;({ root } = buildSpec())
  n0 = marks(getNodeByPath({ root }, f0))
  const kidCount0 = (getNodeByPath({ root }, p(0)).children || []).length
  r = batchMoveNodes(root, [p(1), p(2), p(3)], p(0), 'on')
  check('批量拖入节点内部成功', r.ok, JSON.stringify(r))
  const t = getNodeByPath({ root }, p(0))
  check('批量拖入：3 个都进去了', t.children.length === kidCount0 + 3,
    `子节点数 ${t.children.length}，期望 ${kidCount0 + 3}`)
  check('批量拖入：相对次序保持',
    [t.children[0], t.children[1], t.children[2]].map((c) => c.__uid).join('|')
      === [n0[1], n0[2], n0[3]].join('|'))
  check('批量拖入：源楼层减少3', marks(getNodeByPath({ root }, f0)).length === n0.length - 3)

  // 批量插到某节点之前
  ;({ root } = buildSpec())
  n0 = marks(getNodeByPath({ root }, f0))
  r = batchMoveNodes(root, [p(0), p(1)], p(n0.length - 1), 'before')
  check('批量插到倒数第一之前成功', r.ok, JSON.stringify(r))
  n1 = marks(getNodeByPath({ root }, f0))
  check('批量插到之前：落点正确',
    n1[n0.length - 3] === n0[0] && n1[n0.length - 2] === n0[1],
    `实际 ${n1.slice(-4)}`)

  // 跨父批量
  ;({ root } = buildSpec())
  n0 = marks(getNodeByPath({ root }, f0))
  const crossKidCount = (getNodeByPath({ root }, `${f1}${SEP_}children${SEP_}0`).children || []).length
  r = batchMoveNodes(root, [p(0), p(1)], `${f1}${SEP_}children${SEP_}0`, 'on')
  check('跨父批量移动成功', r.ok, JSON.stringify(r))
  const t2 = getNodeByPath({ root }, `${f1}${SEP_}children${SEP_}0`)
  check('跨父批量：目标收到2个', t2.children.length === crossKidCount + 2,
    `${t2.children.length}，期望 ${crossKidCount + 2}`)
  check('跨父批量：相对次序保持',
    [t2.children[0], t2.children[1]].map((c) => c.__uid).join('|') === [n0[0], n0[1]].join('|'))
  check('跨父批量：源楼层减少2', marks(getNodeByPath({ root }, f0)).length === n0.length - 2)

  // 不同父的多选必须被拒绝
  ;({ root } = buildSpec())
  r = batchMoveNodes(root, [p(0), `${f1}${SEP_}children${SEP_}0`], p(5), 'before')
  check('不同父多选被拒绝', !r.ok && /同一父级/.test(r.reason), JSON.stringify(r))

  // 批量拖入自己子孙被拒绝
  ;({ root } = buildSpec())
  r = batchMoveNodes(root, [p(0), p(1)], `${p(0)}${SEP_}children${SEP_}0`, 'on')
  check('批量拖入自己子孙被拒绝', !r.ok, JSON.stringify(r))

  // 已经在目标内部
  ;({ root } = buildSpec())
  r = batchMoveNodes(root, [p(0), p(1)], p(0), 'on')
  check('批量拖到已在自己的父节点被拒绝', !r.ok, JSON.stringify(r))
}

/* ---- 6. 穷举：任意两节点 + 三种落点不抛异常、不丢节点 ---- */
{
  const { root } = buildSpec()
  // 给每个节点打上唯一标记，用于检测"节点被复制/丢失"
  let uid = 0
  ;(function tag(n) {
    n.__uid = ++uid
    ;(n.children || []).forEach(tag)
  })(root)

  const flat = []
  ;(function walk(node, path = 'root') {
    flat.push(path)
    ;(node.children || []).forEach((c, i) => walk(c, `${path}${SEP_}children${SEP_}${i}`))
  })(root)

  const totalNodes = flat.length
  let cases = 0
  let bad = 0
  const sampleFailures = []
  for (const a of flat) {
    for (const b of flat) {
      for (const kind of ['on', 'before', 'after']) {
        const clone = JSON.parse(snapshot(root))
        const before = countNodes(clone)
        let threw = false
        try {
          moveNodeInSpec(clone, a, b, kind)
        } catch (e) {
          threw = true
          if (sampleFailures.length < 6) sampleFailures.push(`(${a})->(${b}) ${kind} 抛异常: ${e.message}`)
        }
        cases++
        if (threw) { bad++; continue }
        if (countNodes(clone) !== before) {
          bad++
          if (sampleFailures.length < 6) {
            sampleFailures.push(`(${a})->(${b}) ${kind} 节点数 ${before} -> ${countNodes(clone)}`)
          }
          continue
        }
        const uids = collectUids(clone)
        if (uids.size !== before) {
          bad++
          if (sampleFailures.length < 6) {
            sampleFailures.push(`(${a})->(${b}) ${kind} 节点重复/丢失 (唯一uid ${uids.size}/${before})`)
          }
        }
      }
    }
  }
  check(`穷举 ${cases} 个落点组合：不抛异常、不丢节点、不产生副本`, bad === 0,
    `失败 ${bad} 例；样例：\n      ` + sampleFailures.join('\n      '))
  console.log(`穷举规模：${totalNodes} 个节点 × ${totalNodes} × 3 落点 = ${cases} 例`)
}

function countNodes(node) {
  return 1 + (node.children || []).reduce((s, c) => s + countNodes(c), 0)
}
function collectUids(node, acc = new Set()) {
  acc.add(node.__uid)
  ;(node.children || []).forEach((c) => collectUids(c, acc))
  return acc
}

/* ---- 输出 ---- */
console.log(`\n通过 ${pass} 项断言`)
if (failures.length) {
  console.log(`\n失败 ${failures.length} 项：`)
  failures.forEach((f) => console.log('  ✗ ' + f))
  process.exit(1)
}
console.log('全部通过 ✓\n')
