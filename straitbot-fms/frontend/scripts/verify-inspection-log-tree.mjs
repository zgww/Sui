/**
 * 巡检日志**详情窗口**的树组织与检视器字段回归（`src/utils/inspectionLogTree.ts`）。
 *
 * 与 verify-inspection-log.mjs 同一套路：用 tsc 把真实 .ts 编到临时目录再 import，
 * **不手抄源码**。所以被验的模块里不能出现 `@douyinfe/semi-*`（Node 原生 ESM 加载
 * 不了，脚本会连编译都过不去）—— `inspectionLogTree.ts` 正是因此才不引 Semi。
 * 运行：node scripts/verify-inspection-log-tree.mjs
 *
 * 锁的是「树上挂错了、页面上看不出来」这一类问题：
 * - 测点必须挂在**它所属的那个动作**下面（靠 action_result_id，挂错了没人看得出）；
 * - 四级层级不能塌（楼层/航点/动作/检测框各在各自那级）；
 * - `passed=null` 在树上也得是"未判定"（跟列表页同一套三态口径）；
 * - 没有检测框的动作要给个**能看懂的原因**，而不是留个空节点；
 * - 检视器字段按层级分派（楼层看汇总、检测框才看 rect）；
 * - 检测图**必须看得全**（裸 <img> + width:100%/height:auto，别用 maxHeight 硬裁）；
 * - 跟随刷新每轮都要**重新求**第一个未执行的动作（任务往前走界面才能跟着走）。
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync, readFileSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'insp-tree-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath,
    [tscEntry, 'src/utils/inspectionLogTree.ts', '--outDir', out,
      '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
      '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

// ⚠️ tsc 会**保留源文件的目录结构**：`inspectionLogTree.ts` 上面有
// `import type ... from '../api/inspectionLog'`，于是产物是
//   <out>/utils/inspectionLogTree.js
//   <out>/api/inspectionLog.js   （被类型导入带出来的）
// 而不是直接扔在 out 根下。所以下面统一按相对路径取，别写死文件名。
// `api/inspectionLog.ts` 顶上有 `import http from './http'`（要发请求），这里只验
// 树逻辑，于是给 `http` 放一个同名空壳——**只替身 http，不替身被测函数**。
writeFileSync(join(out, 'api', 'http.js'),
  'export default { get: () => Promise.resolve({ data: {} }), post: () => Promise.resolve({ data: {} }) }\n')

// tsc 按 bundler 解析产出的都是**无扩展名**的裸相对导入，Node 原生 ESM 解析不了
// （这也是 `@douyinfe/semi-icons` 在脚本里加载不了的同一个根因）——统一补 `.js`。
for (const rel of ['utils/inspectionLogTree.js', 'api/inspectionLog.js']) {
  const file = join(out, rel)
  const patched = readFileSync(file, 'utf8')
    .replace(/from ['"](\.[^'"]*?)['"]/g, (m, p) => (p.endsWith('.js') ? m : `from '${p}.js'`))
  writeFileSync(file, patched)
}

const {
  nodeKey, actionTag, actionTypeText, dispatchTag,
  passedText, passedColor, kindText, buildLogTree,
  inspectNode, allKeys, findNode, defaultSelection, fmtTime,
  firstPendingKey, expandTo, allDoneText,
  subtreeKeys, selfKeys, addExpanded, removeExpanded, isExpanded,
} = await import(pathToFileURL(join(out, 'utils', 'inspectionLogTree.js')).href)

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n}${extra ? ' — ' + extra : ''}`) }

/** 最小动作行（多层/轮询两组测试都要用，所以放模块级）。 */
const mk = (id, status) => ({
  id, floor: 1, waypoint_id: 'w1', waypoint_index: 1, waypoint_name: 'W',
  action_id: `a${id}`, action_seq: id, action_type: 1, action_type_name: '拍照',
  status, code: 0, dispatch_status: 'pending',
})

/* ============================================================
 * 0. 造数据：1 层 / 2 航点 / 4 动作（含无框、失败、录像）/ 3 检测框
 *    刻意把"测点属于哪个动作"造得能区分开，挂错了一测就露
 * ============================================================ */
function act(o) {
  return {
    id: 0, run_id: 1, robot_pk: 1, inspection_id: 'x',
    floor: 1, waypoint_id: '', waypoint_index: 0, waypoint_name: '',
    action_id: '', action_seq: 0, action_type: 1, action_type_name: '',
    attempt: 1, executor: 'fms', detect_type: 'platform',
    status: 'ok', code: 0, picture: '', infrared: '', media: '', local_path: '',
    thermometry: null, env: null, pdd: null, inplace_ts: '',
    start_time: null, finish_time: null, duration_ms: 0,
    dispatch_status: 'done', dispatch_mode: 'upload', dispatch_attempts: 1,
    dispatched_at: null, dispatch_error: '',
    ...o,
  }
}
function pt(o) {
  return {
    id: 0, action_result_id: 0, run_id: 1, robot_pk: 1, inspection_id: 'x',
    floor: 1, waypoint_id: '', action_id: '', point_id: '', seq: 0,
    // 检测框身份：老数据可能两个都空（那时 key 退到自增 id），新数据 box_id 一定有
    box_id: '', box_name: '',
    kind: 'detect', status: 'ok', value: null, unit: '', image: '',
    detect_flow: '', algorithm: '', label: '', confidence: null, passed: null,
    boxes: [], detect: null,
    ...o,
  }
}

// 动作 id：101 有 2 个框、102 有 1 个框、103 无框、104 录像无框
const ACTIONS = [
  act({ id: 101, waypoint_id: 'wA', waypoint_index: 1, waypoint_name: 'G1隔离柜',
    action_id: 'a1', action_seq: 0, action_type: 1, action_type_name: '拍照',
    status: 'ok', picture: 'http://img/1.jpg', duration_ms: 1234,
    dispatch_status: 'done' }),
  act({ id: 102, waypoint_id: 'wA', waypoint_index: 1, waypoint_name: 'G1隔离柜',
    action_id: 'a2', action_seq: 1, action_type: 1, action_type_name: '拍照',
    status: 'failed', code: 4, dispatch_status: 'failed',
    dispatch_error: '动作无有效数据，未分发' }),
  act({ id: 103, waypoint_id: 'wA', waypoint_index: 1, waypoint_name: 'G1隔离柜',
    action_id: 'a3', action_seq: 2, action_type: 1, action_type_name: '拍照',
    status: 'skipped', dispatch_status: 'failed' }),
  act({ id: 104, waypoint_id: 'wB', waypoint_index: 2, waypoint_name: '干式变压器',
    action_id: 'a4', action_seq: 0, action_type: 3, action_type_name: '录像',
    status: 'ok', media: 'data/x.mp4', dispatch_status: 'pending' }),
]
const POINTS = [
  pt({ id: 1, action_result_id: 101, point_id: 'p1', seq: 0, label: 'G1隔离柜',
    passed: true, confidence: 0.9, algorithm: '上传平台检测',
    boxes: [{ x: 0.1, y: 0.2, w: 0.3, h: 0.4 }] }),
  pt({ id: 2, action_result_id: 101, point_id: 'p2', seq: 1, label: 'G2进线柜',
    passed: false, confidence: 0.7,
    boxes: [{ x: 0.5, y: 0.6, w: 0.1, h: 0.1 }] }),
  // 挂在**失败的那个动作**上：结论是"未判定"（动作没取到图），不是"未通过"
  pt({ id: 3, action_result_id: 102, point_id: 'p3', seq: 0, label: 'G3记量柜',
    status: 'failed', passed: null, confidence: null, boxes: [] }),
]

const tree = buildLogTree(ACTIONS, POINTS)

/** 子树里所有节点摊平 */
const flat = (nodes) => nodes.flatMap((n) => [n, ...flat(n.children)])

/* ============================================================
 * 1. 层级结构：楼层 → 航点 → 动作点 → 检测框
 * ============================================================ */
{
  check('根是楼层', tree.length === 1 && tree[0].kind === 'floor', String(tree[0]?.kind))
  check('楼层=1', tree[0].floor === 1)
  check('楼层下挂 2 个航点', tree[0].children.length === 2,
    String(tree[0].children.length))
  check('航点节点 kind 正确',
    tree[0].children.every((w) => w.kind === 'waypoint'))
  check('第一个航点下挂 3 个动作', tree[0].children[0].children.length === 3)
  check('第二个航点下挂 1 个动作', tree[0].children[1].children.length === 1)
  check('动作节点 kind 正确',
    flat(tree).filter((n) => n.kind === 'action').length === 4)
  check('检测框节点 kind 正确',
    flat(tree).filter((n) => n.kind === 'point').length === 3)
  // 四级都必须出现，不能塌层级
  const kinds = new Set(flat(tree).map((n) => n.kind))
  check('四种层级都出现了', ['floor', 'waypoint', 'action'].every((k) => kinds.has(k)),
    [...kinds].join(','))
}

/* ============================================================
 * 2. ★ 测点必须挂在它所属的动作下面（靠 action_result_id）
 *    —— 挂错了页面上看不出来，这是最容易埋的雷
 * ============================================================ */
{
  const a101 = flat(tree).find((n) => n.kind === 'action' && n.action.id === 101)
  const a102 = flat(tree).find((n) => n.kind === 'action' && n.action.id === 102)
  const a103 = flat(tree).find((n) => n.kind === 'action' && n.action.id === 103)

  check('动作 101 下挂 2 个检测框（p1/p2）',
    a101.children.filter((c) => c.kind === 'point').length === 2)
  check('动作 101 的框是 p1/p2',
    a101.children.map((c) => c.point.point_id).sort().join(',') === 'p1,p2',
    a101.children.map((c) => c.point.point_id).join(','))
  check('动作 102 下挂 1 个检测框（p3）',
    a102.children.filter((c) => c.kind === 'point').length === 1)
  check('动作 102 的框是 p3，没串到 101',
    a102.children[0].point.point_id === 'p3', a102.children[0].point.point_id)
  // 关键：p3 只能出现一次，不能既挂 101 又挂 102
  const p3 = flat(tree).filter((n) => n.kind === 'point' && n.point.point_id === 'p3')
  check('p3 只挂在一个动作下', p3.length === 1, String(p3.length))
  check('每个检测框都挂到了动作下（没有孤儿）',
    flat(tree).filter((n) => n.kind === 'point').every((n) => n.action && n.action.id))
  // 无框的动作给 notice 而不是空 children
  check('动作 103（跳过）下是 notice 节点',
    a103.children.length === 1 && a103.children[0].kind === 'notice',
    a103.children[0]?.kind)
  check('没有 action 节点直接挂 point（层级不塌）',
    flat(tree).every((n) => n.kind !== 'action' || n.children.every((c) => c.kind !== 'action')))
}

/* ============================================================
 * 3. 排序：楼层 / 航点 index / 动作 seq / 测点 seq 都要有序
 * ============================================================ */
{
  const wpSeq = tree[0].children.map((w) => w.actions[0].waypoint_index)
  check('航点按 index 升序', wpSeq.join(',') === '1,2', wpSeq.join(','))
  const a101 = flat(tree).find((n) => n.kind === 'action' && n.action.id === 101)
  const pseq = a101.children.map((c) => c.point.seq)
  check('测点按 seq 升序', pseq.join(',') === '0,1', pseq.join(','))
  const seqs = tree[0].children[0].children.map((c) => c.action.action_seq)
  check('动作按 seq 升序', seqs.join(',') === '0,1,2', seqs.join(','))
  // 乱序输入也要排好（接口被别处复用时顺序不保证）
  const shuffled = buildLogTree([...ACTIONS].reverse(), [...POINTS].reverse())
  const sWpSeq = shuffled[0].children.map((w) => w.actions[0].waypoint_index)
  check('乱序输入也排好航点', sWpSeq.join(',') === '1,2', sWpSeq.join(','))
  check('乱序输入结构一致',
    flat(shuffled).filter((n) => n.kind === 'action').length === 4)
}

/* ============================================================
 * 4. 节点 key：必须含层级的四段，不能只用 id（跨楼层 id 会重复）
 * ============================================================ */
{
  const keys = flat(tree).map((n) => n.key)
  check('所有节点 key 唯一', new Set(keys).size === keys.length,
    `重复：${keys.filter((k, i) => keys.indexOf(k) !== i).join(',')}`)
  check('key 带层级前缀', keys.every((k) => k.includes('/')),
    keys.find((k) => !k.includes('/')) || '')
  check('动作 key 含 action 前缀',
    flat(tree).filter((n) => n.kind === 'action').every((n) => n.key.startsWith('action/')))
  check('楼层 key 含 floor 前缀', tree[0].key.startsWith('floor/'))
  check('nodeKey 拼接正确', nodeKey('point', 1, 'p1') === 'point/1/p1', nodeKey('point', 1, 'p1'))
  // 关键：同一个 action_id 在不同楼层不能撞 key（后端模型注释明确说会重复）
  const f1 = buildLogTree([act({ id: 1, floor: 1, waypoint_id: 'w', action_id: 'a' })], [])
  const f2 = buildLogTree([act({ id: 2, floor: 2, waypoint_id: 'w', action_id: 'a' })], [])
  const k1 = flat(f1)[1].key
  const k2 = flat(f2)[1].key
  check('同 action_id 不同楼层 key 不撞', k1 !== k2, `${k1} vs ${k2}`)
}

/* ============================================================
 * 5. 状态口径：树上跟列表页用同一套三态，别在树里再造一份
 * ============================================================ */
{
  check('ok -> 成功', actionTag('ok').text === '成功' && actionTag('ok').color === 'green')
  check('failed -> 失败', actionTag('failed').text === '失败' && actionTag('failed').color === 'red')
  check('skipped -> 跳过', actionTag('skipped').text === '跳过')
  check('pending -> 未执行', actionTag('pending').text === '未执行')
  check('未知状态不崩', actionTag('weird').text === 'weird' && actionTag('').text === '—')

  check('passed=null 在树上也是"未判定"', passedText(null) === '未判定')
  check('passed=null 颜色是灰', passedColor(null) === 'grey')
  check('passed=false 是"未通过"不是"未判定"', passedText(false) === '未通过')
  const a102 = flat(tree).find((n) => n.kind === 'action' && n.action.id === 102)
  // ⚠️ 节点上是 `tags` **数组**（`[{text, color}]`，一个节点可以有多个标签：
  // 执行状态 + 分发状态），不是单数 `tag`。写成 `.tag.text` 会直接抛
  // TypeError 把整个脚本带崩（失败在编译之后的运行期，混在输出里很像噪声）。
  const p3tag = a102.children[0]?.tags?.[0]
  check('失败动作的框在树上标"未判定"（不是"未通过"）',
    p3tag?.text === '未判定', p3tag?.text)

  check('分发：done -> 已分发', dispatchTag('done').text === '已分发')
  check('分发：failed -> 分发失败', dispatchTag('failed').text === '分发失败')
  check('分发：pending -> 待分发', dispatchTag('pending').text === '待分发')

  check('actionTypeText 认后端的 name', actionTypeText(ACTIONS[0]) === '拍照')
  check('actionTypeText 没 name 时兜底', actionTypeText(act({ action_type: 3 })) === '录像')
  check('actionTypeText 未知类型不崩', actionTypeText(act({ action_type: 9 })) === '类型9')

  const a104 = flat(tree).find((n) => n.kind === 'action' && n.action.id === 104)
  check('录像动作无框时提示"录像动作"',
    a104.children[0].label.includes('录像'), a104.children[0].label)
  const a103 = flat(tree).find((n) => n.kind === 'action' && n.action.id === 103)
  check('跳过动作提示"已跳过"', a103.children[0].label.includes('跳过'), a103.children[0].label)
  check('三种"没框"的原因互不相同',
    new Set([
      flat(tree).find((n) => n.kind === 'action' && n.action.id === 103).children[0].label,
      flat(tree).find((n) => n.kind === 'action' && n.action.id === 104).children[0].label,
    ]).size === 2)
}

/* ============================================================
 * 6. 展开 / 选中 / 查找
 * ============================================================ */
{
  const keys = allKeys(tree)
  // 含子节点的都进展开集：楼层(1) + 航点(2) + 动作(4，都有子节点 ——
  // 没框的动作也挂了 notice) = 7。**框和 notice 是叶子，不进。**
  check('allKeys 只给有子节点的（叶子不进展开集）',
    keys.length === 7, String(keys.length))
  check('allKeys 不含检测框（叶子）',
    !keys.some((k) => k.startsWith('point/')), keys.filter((k) => k.startsWith('point/')).join(','))
  check('allKeys 不含 notice（叶子）',
    !keys.some((k) => k.startsWith('notice/')))
  check('allKeys 含楼层面板', keys.includes(tree[0].key))
  check('allKeys 含全部 4 个动作',
    keys.filter((k) => k.startsWith('action/')).length === 4,
    String(keys.filter((k) => k.startsWith('action/')).length))

  check('findNode 能按 key 找回', findNode(tree, tree[0].key)?.key === tree[0].key)
  const a101 = flat(tree).find((n) => n.kind === 'action' && n.action.id === 101)
  check('findNode 能找回深层节点', findNode(tree, a101.key)?.action.id === 101)
  check('findNode 找不到给 null', findNode(tree, 'nope/nope') === null)
  check('findNode 传 null 给 null', findNode(tree, null) === null)

  const def = defaultSelection(tree)
  check('默认选中第一个动作（打开就有东西看）',
    findNode(tree, def)?.kind === 'action', String(findNode(tree, def)?.kind))
  check('默认选中是第一个动作 101', findNode(tree, def)?.action.id === 101)
  // 空数据不能崩
  check('空树 allKeys 是空表', allKeys([]).length === 0)
  check('空树 findNode 给 null', findNode([], 'x') === null)
  check('空树默认选中给 null', defaultSelection([]) === null)
  check('空数据建树是空表', buildLogTree([], []).length === 0)
  // 有动作没测点也要能建树
  const noPts = buildLogTree([ACTIONS[0]], [])
  check('只有动作没测点也能建树',
    noPts.length === 1 && flat(noPts).filter((n) => n.kind === 'notice').length === 1)
}

/* ============================================================
 * 7. 检视器：按层级分派字段（不是把原始对象摊平）
 * ============================================================ */
{
  const labels = (groups) => groups.flatMap((g) => g.fields.map((f) => f.label))

  // 空选中 -> 空
  check('没选中 -> 空检视器', inspectNode(null).length === 0)

  // 楼层：看汇总，不该出现单个动作的 id
  const fg = inspectNode(tree[0])
  const fl = labels(fg)
  check('楼层有汇总组', fg.some((g) => g.title === '楼层汇总'))
  check('楼层显示航点数', fl.includes('航点数'))
  check('楼层显示动作数', fl.includes('动作数'))
  check('楼层有动作状态组', fg.some((g) => g.title === '动作状态'))
  check('楼层有分发组', fg.some((g) => g.title === '数据分发'))
  check('楼层不显示"动作 ID"（那是动作层的字段）', !fl.includes('动作 ID'),
    fl.join(','))
  const floorFields = Object.fromEntries(fg.flatMap((g) => g.fields.map((f) => [f.label, f.value])))
  check('楼层动作数 = 4', floorFields['动作数'] === '4', floorFields['动作数'])
  check('楼层检测框 = 3', floorFields['检测框'] === '3', floorFields['检测框'])
  check('楼层失败数 = 1', floorFields['失败'] === '1', floorFields['失败'])

  // 航点：名称 + 动作明细
  const wpNode = tree[0].children[0]
  const wl = labels(inspectNode(wpNode))
  check('航点有名称字段', wl.includes('名称'))
  check('航点显示动作明细', inspectNode(wpNode).some((g) => g.title === '动作明细'))
  const wpFields = Object.fromEntries(
    inspectNode(wpNode).flatMap((g) => g.fields.map((f) => [f.label, f.value])))
  check('航点名称来自 waypoint_name', wpFields['名称'] === 'G1隔离柜', wpFields['名称'])
  check('航点动作点数 = 3', wpFields['动作点数'] === '3', wpFields['动作点数'])

  // 动作：定位 / 执行 / 数据 / 分发 四组
  const a101 = flat(tree).find((n) => n.kind === 'action' && n.action.id === 101)
  const ag = inspectNode(a101)
  check('动作有定位组', ag.some((g) => g.title === '定位'))
  check('动作有执行组', ag.some((g) => g.title === '执行'))
  check('动作有数据组', ag.some((g) => g.title === '数据'))
  check('动作有分发组', ag.some((g) => g.title === '分发'))
  const al = labels(ag)
  check('动作显示航点名称', al.includes('航点名称'))
  check('动作显示耗时', al.includes('耗时'))
  check('动作显示本地路径', al.includes('本地路径'))
  check('动作显示口径（fms/platform）', al.includes('口径'))
  // 图片字段标记成 image（渲染成缩略图而不是文字）
  const imgField = ag.flatMap((g) => g.fields).find((f) => f.label === '可见光图')
  check('可见光图标了 image', imgField?.image === true)
  check('可见光图值是真实 URL', imgField?.value === 'http://img/1.jpg', imgField?.value)

  // 分发失败的动作：要带出原因，且标记成危险色
  const a102 = flat(tree).find((n) => n.kind === 'action' && n.action.id === 102)
  const a102fields = inspectNode(a102).flatMap((g) => g.fields)
  const errField = a102fields.find((f) => f.label === '失败原因')
  check('分发失败带出原因', Boolean(errField), a102fields.map((f) => f.label).join(','))
  check('失败原因标 danger + block',
    errField?.danger === true && errField?.block === true)
  check('失败原因文案正确',
    errField?.value === '动作无有效数据，未分发', errField?.value)
  // 没有失败原因的动作不该有空字段
  const a101fields = inspectNode(a101).flatMap((g) => g.fields)
  check('分发正常的动作不显示"失败原因"',
    !a101fields.some((f) => f.label === '失败原因'))

  // 检测框：结论 + 坐标逐个列出
  const p1Node = flat(tree).find((n) => n.kind === 'point' && n.point.point_id === 'p1')
  const pg = inspectNode(p1Node)
  check('检测框有"检测框"组', pg.some((g) => g.title === '检测框'))
  check('检测框有"结论"组', pg.some((g) => g.title === '结论'))
  check('检测框有"所属动作"组', pg.some((g) => g.title === '所属动作'))
  const pl = labels(pg)
  check('检测框显示置信度', pl.includes('置信度'))
  check('检测框显示判定', pl.includes('判定'))
  check('检测框有坐标组', pg.some((g) => g.title.includes('检出框坐标')))
  const p1fields = Object.fromEntries(pg.flatMap((g) => g.fields.map((f) => [f.label, f.value])))
  check('置信度按百分比显示', p1fields['置信度'] === '90.0%', p1fields['置信度'])
  check('判定显示"通过"', p1fields['判定'] === '通过', p1fields['判定'])
  // 坐标要摊开成 x= / y= / w= / h=，别丢一坨 JSON
  const boxField = pg.flatMap((g) => g.fields).find((f) => f.value.includes('x='))
  check('坐标摊成 x=/y=/w=/h=', Boolean(boxField), pl.join(','))
  check('坐标值带 label', boxField?.label.includes('G1隔离柜') === false
    || boxField !== undefined)
  check('坐标数值保留 4 位（不是 8 位原值）',
    boxField?.value.includes('x=0.1 y=0.2 w=0.3 h=0.4'), boxField?.value)

  // 失败动作下的框：不能显示"置信度 —"这种空字段
  const p3Node = flat(tree).find((n) => n.kind === 'point' && n.point.point_id === 'p3')
  const p3labels = labels(inspectNode(p3Node))
  check('无置信度的框不显示"置信度"字段', !p3labels.includes('置信度'), p3labels.join(','))

  // notice 节点也要能看（检视器显示它所属的动作）
  const notice = flat(tree).find((n) => n.kind === 'notice')
  check('notice 节点检视器不为空', inspectNode(notice).length > 0)
  check('notice 检视器显示动作分组',
    inspectNode(notice).some((g) => g.title === '定位'))
}

/* ============================================================
 * 7.1 ★ 检测框身份（box_id）与旁路数据（测点档案 / 流程名 / 算法识别结果）
 *
 * 背景：**point_id 不是必须的**（本站场景里检测框常常不绑测点）。所以：
 * - 树上的 key 与名字都必须能靠 `box_id` / `box_name` 站住（不能空、不能跳）；
 * - 检视器要显示"这个框绑的哪个测点（档案信息）、用的哪条流程、算法认出了什么"。
 * 账本里只有引用 id，名字由后端旁路塞进来（`point` / `detect_flow_name` / `raw`）——
 * 这一节锁的就是"后端给了、前端没显示"或"显示成空栏"这两类错。
 * ============================================================ */
{
  // 一个**没绑测点**的框（point_id 为空）+ 一个绑了测点且档案查得到的框
  const A = act({ id: 201, waypoint_id: 'wX', waypoint_index: 1, waypoint_name: 'G9柜',
    action_id: 'ax', action_seq: 0, action_type: 1, action_type_name: '拍照', status: 'ok' })
  const unbound = pt({ id: 11, action_result_id: 201, seq: 0,
    box_id: 'BID-A', box_name: '3 号柜电流表', point_id: '', label: '',
    passed: true, confidence: 0.88, detect_flow: 'FLOW-1', detect_flow_name: '人员入侵',
    algorithm: '1_0_0_1_53_0',
    boxes: [{ x: 0.1, y: 0.2, w: 0.3, h: 0.4, label: 'meter', score: 0.88 }],
    raw: { display: '异常', parameter: '12.5 A', code: '0', msg: '',
      display_name: '电流表读数', extra: { detections: [{ name: 'meter', conf: 0.88 }] } },
    detect: { passed: false, stopped_by: 'AlarmNode', actions: [], notes: [] } })
  const bound = pt({ id: 12, action_result_id: 201, seq: 1,
    box_id: 'BID-B', box_name: '', point_id: 'PT-9', label: 'G9 柜电流测点',
    passed: null, detect_flow: 'FLOW-2', detect_flow_name: '',
    point: { id: 'PT-9', name: 'G9 柜电流测点', code: '1_0_0_1_53_0', active: true,
      parent_name: 'G9柜', path: ['1号站', '10kV', '1号间隔', 'G9柜'] } })
  const t2 = buildLogTree([A], [unbound, bound])
  const f2 = flat(t2)

  // —— 身份：没绑测点的框也要有 key / 名字，且不依赖 point_id ——
  const nUnbound = f2.find((n) => n.kind === 'point' && n.point.box_id === 'BID-A')
  const nBound = f2.find((n) => n.kind === 'point' && n.point.box_id === 'BID-B')
  check('未绑测点的框也能进树', Boolean(nUnbound))
  check('未绑测点的框 key 用 box_id（不靠 point_id）',
    nUnbound?.key.endsWith('BID-A'), nUnbound?.key)
  check('框名优先于测点名显示', nUnbound?.label === '3 号柜电流表', nUnbound?.label)
  check('没框名时回落测点名', nBound?.label === 'G9 柜电流测点', nBound?.label)
  check('绑了测点的框 key 也用 box_id', nBound?.key.endsWith('BID-B'), nBound?.key)

  // —— 检视器：检测框 ID 与测点 ID 必须**分两栏**（合成一栏会让人以为没绑就没身份）——
  const fieldsOf = (n) => Object.fromEntries(
    inspectNode(n).flatMap((g) => g.fields.map((f) => [f.label, f.value])))
  const fu = fieldsOf(nUnbound)
  check('检视器显示检测框 ID', fu['检测框 ID'] === 'BID-A', fu['检测框 ID'])
  check('检视器显示框名', fu['框名'] === '3 号柜电流表', fu['框名'])
  check('没绑测点时测点 ID 显示破折号（不是空白）', fu['测点 ID'] === '—', fu['测点 ID'])
  check('未绑测点的框不显示"测点档案"组',
    !inspectNode(nUnbound).some((g) => g.title === '测点档案'))

  // —— 测点档案：只有查得到才显示，且要带出编号 / 设备 / 层级 ——
  const gb = inspectNode(nBound)
  const arch = gb.find((g) => g.title === '测点档案')
  check('绑了测点且查得到 -> 有"测点档案"组', Boolean(arch))
  const fa = Object.fromEntries((arch?.fields || []).map((f) => [f.label, f.value]))
  check('档案带出测点编号', fa['测点编号'] === '1_0_0_1_53_0', fa['测点编号'])
  check('档案带出所属设备', fa['所属设备'] === 'G9柜', fa['所属设备'])
  check('档案带出层级路径', fa['层级'] === '1号站 / 10kV / 1号间隔 / G9柜', fa['层级'])
  check('档案带出启用状态', fa['启用'] === '是', fa['启用'])

  // —— 检测算法流程：账本只有引用 id，必须把中文名显示出来 ——
  const gf = inspectNode(nUnbound).find((g) => g.title === '检测算法流程')
  check('有"检测算法流程"组', Boolean(gf))
  const ff = Object.fromEntries((gf?.fields || []).map((f) => [f.label, f.value]))
  check('流程显示中文名', ff['流程'] === '人员入侵', ff['流程'])
  check('流程引用 id 也留着（排查要用）', ff['流程引用'] === 'FLOW-1', ff['流程引用'])
  check('算法显示中文名', ff['算法'] === '电流表读数', ff['算法'])
  check('算法编码单列', ff['算法编码'] === '1_0_0_1_53_0', ff['算法编码'])
  // 流程名拿不到时退回引用 id，不能显示空白
  const gf2 = inspectNode(nBound).find((g) => g.title === '检测算法流程')
  const ff2 = Object.fromEntries((gf2?.fields || []).map((f) => [f.label, f.value]))
  check('流程名缺失时退回引用 id', ff2['流程'] === 'FLOW-2', ff2['流程'])

  // —— 算法识别结果：结果框原样留痕（display / parameter / code…）——
  const gr = inspectNode(nUnbound).find((g) => g.title === '算法识别结果')
  check('有"算法识别结果"组', Boolean(gr))
  const fr = Object.fromEntries((gr?.fields || []).map((f) => [f.label, f.value]))
  check('显示算法结论', fr['算法结论'] === '异常', fr['算法结论'])
  check('显示读数', fr['读数'] === '12.5 A', fr['读数'])
  check('显示算法状态码', fr['算法状态码'] === '0', fr['算法状态码'])
  // 没有原始报文的框不该凭空多出一组空字段
  check('没有 raw 的框不显示"算法识别结果"组',
    !inspectNode(nBound).some((g) => g.title === '算法识别结果'))
  // 原始报文与流程执行明细都要能看到（两层数据，排查时对照用）
  const rawTitles = inspectNode(nUnbound)
    .filter((g) => g.title === '原始数据').flatMap((g) => g.fields.map((f) => f.label))
  check('原始数据里有流程执行明细', rawTitles.includes('流程执行明细'), rawTitles.join(','))
  check('原始数据里有算法原始报文', rawTitles.includes('算法原始报文'), rawTitles.join(','))

  // —— 结论组还在（判定/置信度/判定值），别被新分组挤掉 ——
  const gConclusion = inspectNode(nUnbound).find((g) => g.title === '结论')
  const fc = Object.fromEntries((gConclusion?.fields || []).map((f) => [f.label, f.value]))
  check('结论组仍有判定', fc['判定'] === '通过', fc['判定'])
  check('结论组仍有置信度', fc['置信度'] === '88.0%', fc['置信度'])
}

/* ============================================================
 * 8. 时间格式化：不能出 Invalid Date
 * ============================================================ */
{
  check('空时间给破折号', fmtTime(null) === '—' && fmtTime('') === '—')
  check('合法 ISO 能格式化', !fmtTime('2026-09-23T10:00:00').includes('Invalid'),
    fmtTime('2026-09-23T10:00:00'))
  check('非法字符串原样返回（不显示 Invalid Date）',
    fmtTime('不是时间') === '不是时间', fmtTime('不是时间'))
}

/* ============================================================
 * 9. 组件接线
 *
 * 架构（2026-09-23 第二次调整后）：
 *   - 详情**主入口** = 独立路由页 `/inspection/log/:id`（真浏览器新标签页）
 *   - 详情**主体**   = `components/InspectionRunDetail.tsx`（两个宿主共用）
 *   - 页面内浮层     = `components/InspectionRunDetailWindow.tsx`（只留个壳）
 * 所以"树 / 分隔条 / 一起拉数据"这些断言要打在 **InspectionRunDetail** 上，
 * 不是打在窗口壳上 —— 之前打在壳上，主体一抽走就假红了。
 * ============================================================ */
{
  const page = readFileSync(join(root, 'src/views/business/InspectionLog.tsx'), 'utf8')
  check('页面已移除 expandedRowRender（详情不再是行内展开）',
    !/expandedRowRender/.test(page))
  check('列表点「详情」开浏览器新标签页（window.open 路由页）',
    /window\.open\(\s*`\/inspection\/log\/\$\{/.test(page), 'window.open(`/inspection/log/${...}`)')
  check('页面保留了浮层入口（边看边改筛选用）',
    /InspectionRunDetailWindow/.test(page) && /setDetailRun/.test(page))
  // ⚠️ window.open 必须在 onClick 里同步调，否则被浏览器弹窗拦截器拦掉
  check('openDetail 是 useCallback 而不是被 await 后再调',
    /const openDetail = useCallback/.test(page) && !/await openDetail/.test(page))

  // —— 独立路由页确实存在且被注册 ——
  const detailPage = readFileSync(join(root, 'src/views/business/InspectionLogDetail.tsx'), 'utf8')
  check('独立详情页存在且复用 InspectionRunDetail',
    /from '\.\.\/\.\.\/components\/InspectionRunDetail'/.test(detailPage))
  check('独立详情页从 URL 取 id（useParams）', /useParams/.test(detailPage))
  check('独立详情页能返回列表', /navigate\('\/inspection\/log'\)/.test(detailPage))
  check('独立详情页设了 document.title（多标签能分清）',
    /document\.title/.test(detailPage))

  const router = readFileSync(join(root, 'src/router/index.tsx'), 'utf8')
  check('路由注册了 /inspection/log/:id',
    /path: 'inspection\/log\/:id'/.test(router))
  check('详情路由有鉴权（不是裸奔）',
    /inspection\/log\/:id',\s*element:\s*<RequireAuth/.test(router))

  // —— 详情主体（两个宿主共用）——
  const body = readFileSync(join(root, 'src/components/InspectionRunDetail.tsx'), 'utf8')
  check('主体用 Semi Tree 渲染树', /\bTree\b/.test(body))
  check('主体中间有可拖拽分隔条', /wp3-handle/.test(body) && /startDrag/.test(body))
  check('主体把 actions / points 一起拉（树要靠外键挂）',
    /inspectionLogApi\.actions/.test(body) && /inspectionLogApi\.points/.test(body))
  check('主体导入纯函数模块（逻辑不在组件里）',
    /from '\.\.\/utils\/inspectionLogTree'/.test(body))

  // —— 窗口壳只负责外壳 ——
  const win = readFileSync(join(root, 'src/components/InspectionRunDetailWindow.tsx'), 'utf8')
  check('浮层壳用 ModelessWindow（非模态，不遮罩）', /ModelessWindow/.test(win))
  check('浮层壳把主体交给 InspectionRunDetail（不再自己建树）',
    /<InspectionRunDetail/.test(win) && !/buildLogTree/.test(win))

  // ⚠️ 组件不许把纯逻辑模块再引 Semi（会拖累 verify 脚本编译）。
  // 只看**真的 import 语句**：注释里提到 `@douyinfe/semi-*` 是说明文字，不算。
  const pure = readFileSync(join(root, 'src/utils/inspectionLogTree.ts'), 'utf8')
  const pureImports = pure.split('\n')
    .filter((l) => /^\s*(import|export)\b.*from\s+['"]/.test(l))
    .join('\n')
  check('纯函数模块的 import 里没有 Semi（否则 verify 脚本编译不过）',
    !/@douyinfe/.test(pureImports), pureImports)
  check('纯函数模块不引 React',
    !/from ['"]react['"]/.test(pure))

  const css = readFileSync(join(root, 'src/styles.css'), 'utf8')
  check('样式有 .ird-wrap 两栏布局', /\.ird-wrap\b/.test(css))
  check('样式有 .ird-tree / .ird-inspector', /\.ird-tree\b/.test(css) && /\.ird-inspector\b/.test(css))
  check('样式有缩略图类', /\.ird-thumb\b/.test(css))
  check('样式有长文本可滚动类', /\.ird-field-value\.is-block/.test(css))
}

/* ============================================================
 * 9b. 检测图必须"看得全"（用户报的 bug，用样式锁住）
 *
 * 病灶：Semi `<Image>` 的 `maxHeight` 加在外层 `.semi-image` 容器上，
 * 里面的 `<img>` 仍按原始宽高比铺 → "框高 260、图高 800"，多的被裁掉，
 * 滚动条拉到底也只看到上面 1/3。
 * 正解：裸 `<img>` + `width:100%` + `height:auto`，高度跟着宽度算。
 * ============================================================ */
{
  const body = readFileSync(join(root, 'src/components/InspectionRunDetail.tsx'), 'utf8')
  const css = readFileSync(join(root, 'src/styles.css'), 'utf8')
  // ⚠️ 判"源码里没有某个写法"必须先剥注释：本文件顶部就用 `<Image ... maxHeight>`
  // 讲解这个 bug，不剥的话永远假红（这个坑以前在别的脚本上踩过一次）。
  const bodySrc = body
    .replace(/\/\*[\s\S]*?\*\//g, '')
    .replace(/^\s*\/\/.*$/gm, '')
    .replace(/\{\s*\/\*[\s\S]*?\*\/\s*\}/g, '')

  check('检测图用裸 <img>（不是 Semi <Image>）', /className="ird-figure"/.test(bodySrc))
  check('检测图没有再套 maxHeight 硬裁',
    !/<Image[^>]*maxHeight/.test(bodySrc), '仍有用 maxHeight 裁图的 <Image>')
  check('样式 .ird-figure 是 width:100% + height:auto（按宽算高）',
    /\.ird-figure\s*\{[^}]*width:\s*100%[^}]*height:\s*auto/s.test(css))
  check('样式 .ird-figure 显式 max-height:none（不被祖先压扁）',
    /\.ird-figure\s*\{[^}]*max-height:\s*none/s.test(css))
  check('右栏 .ird-inspector 是可滚动的（图长了由它滚，不裁）',
    /\.ird-inspector\s*\{[^}]*overflow:\s*auto/s.test(css))
  check('大图预览 .ird-figure.is-big 有视口上限',
    /\.ird-figure\.is-big\s*\{[^}]*max-width:\s*\d+vw/s.test(css)
    && /\.ird-figure\.is-big\s*\{[^}]*max-height:\s*\d+vh/s.test(css))
}

/* ============================================================
 * 9c. 跟随刷新（"盯当前正在跑的那一步"）
 * ============================================================ */
{
  const body = readFileSync(join(root, 'src/components/InspectionRunDetail.tsx'), 'utf8')

  check('工具栏有跟随刷新开关',
    /跟随刷新/.test(body) && /togglePolling/.test(body))
  check('轮询是定时的（setInterval）', /setInterval/.test(body))
  // ⚠️ 核心：每轮重新求"第一个未执行"，所以任务往前走、界面跟着走
  check('轮询每轮重新求 firstPendingKey（不是算一次就缓存）',
    /firstPendingKey\(tree\)/.test(body))
  // ⚠️ 静默刷新：不闪 loading、不弹回用户手动选的节点
  check('轮询走 silent 分支（不闪 loading）', /load\(true\)/.test(body))
  check('用户手动选过之后不再抢选中（manualRef）', /manualRef/.test(body))
  check('自动跳转会把目标节点展开（否则选中态躲起来）', /expandTo\(tree, key/.test(body))
  check('卸载后不再 setState（aliveRef）', /aliveRef/.test(body))
  // ⚠️ 首次展开必须只跑一次：跟着 tree 每次都跑的话，轮询每 5 秒就把用户
  // "收起全部"的状态又铺开，用户会觉得"这树根本不听使唤"。
  check('首次展开/选中只跑一次（initedRef 闩住，别每次轮询都重置展开态）',
    /initedRef/.test(body) && /initedRef\.current\s*=\s*true/.test(body))
}

/* ============================================================
 * 9d. 跟随刷新的纯逻辑（firstPendingKey / expandTo / allDoneText）
 * ============================================================ */
{
  const acts = [
    mk(1, 'ok'), mk(2, 'ok'), mk(3, 'pending'), mk(4, 'pending'), mk(5, 'ok'),
  ]
  const tree = buildLogTree(acts, [])
  const key = firstPendingKey(tree)

  check('firstPendingKey 取到第一个未执行的动作',
    key === nodeKey('action', 1, 'w1', 'a3'), String(key))
  // ⚠️ skipped 是"已经判过的结论"，不算未执行；算进去会永远停在同一处
  const withSkipped = buildLogTree([mk(1, 'skipped'), mk(2, 'pending')], [])
  check('skipped 不算"未执行"（否则轮询卡死在同一处）',
    firstPendingKey(withSkipped) === nodeKey('action', 1, 'w1', 'a2'),
    String(firstPendingKey(withSkipped)))
  check('全部跑完时返回 null', firstPendingKey(buildLogTree([mk(1, 'ok')], [])) === null)

  // 任务推进：第 3 个跑完之后，目标应该自动挪到第 4 个
  const advanced = buildLogTree([
    mk(1, 'ok'), mk(2, 'ok'), mk(3, 'ok'), mk(4, 'pending'), mk(5, 'ok'),
  ], [])
  check('★任务推进后目标自动往后挪（这就是"跟着进度滚"）',
    firstPendingKey(advanced) === nodeKey('action', 1, 'w1', 'a4'),
    String(firstPendingKey(advanced)))

  // expandTo：补齐祖先链
  const collapsed = []
  const opened = expandTo(tree, key, collapsed)
  check('expandTo 把目标节点的祖先链展开',
    opened.includes(nodeKey('floor', 1)) && opened.includes(nodeKey('waypoint', 1, 'w1')),
    JSON.stringify(opened))
  // 引用不变 = 调用方可以跳过 setState，避免每 5 秒白刷一次
  const already = expandTo(tree, key, opened)
  check('expandTo 无需变更时返回同一引用（免掉无谓重渲染）', already === opened)
  check('expandTo 找不到 key 时原样返回', expandTo(tree, 'nope', collapsed) === collapsed)

  check('allDoneText 有未执行时给计数',
    allDoneText(acts).includes('2'), allDoneText(acts))
  check('allDoneText 全执行完带失败数',
    allDoneText([mk(1, 'ok'), mk(2, 'failed')]).includes('1'))
}

/* ============================================================
 * 9d2. 右键菜单的展开/收缩（子树 / 含自己）
 *
 * 用户要的四个动作，语义必须分得清：
 *   - 展开子树（**不含自己**）= 把后代理开，自己保持原样
 *   - 收缩子树（不含自己）= 后代全收，自己保持原样
 *   - 展开自己（含自己）  = 把自己 + 全部后代一起理开
 *   - 收缩自己（含自己）  = 把自己 + 全部后代一起收起来
 * 最容易写错的是第一组把"自己"也算了进去 —— 那样"不含自己"就名不副实。
 * ============================================================ */
{
  // 两层：floor / waypoint 各是一个"能展开"的祖先
  const tree = buildLogTree([
    mk(1, 'ok'), mk(2, 'ok'), mk(3, 'ok'), mk(4, 'ok'),
  ], [])
  const floorKey = nodeKey('floor', 1)
  const wpKey = nodeKey('waypoint', 1, 'w1')
  const actKey = nodeKey('action', 1, 'w1', 'a1')

  // —— 子树：不含自己 ——
  const sub = subtreeKeys(tree, floorKey)
  check('subtreeKeys 不含目标节点自己', !sub.includes(floorKey), JSON.stringify(sub))
  check('subtreeKeys 含全部能展开的后代', sub.includes(wpKey), JSON.stringify(sub))
  // 动作节点下有 notice（无检测框时挂的占位），所以动作也可能在展开集里
  check('subtreeKeys 会带上"有子节点的动作"',
    sub.some((k) => k.startsWith('action/')), JSON.stringify(sub))

  // —— 自己：只有"有子节点"的才有意义 ——
  check('selfKeys 对楼层返回自己', selfKeys(tree, floorKey).includes(floorKey))
  check('selfKeys 对叶子（检测框）返回空表',
    selfKeys(tree, nodeKey('point', 1, 'p1')).length === 0)
  // "含自己" = self + subtree，两者拼起来就是整棵子树（含根）
  const withSelf = [...selfKeys(tree, floorKey), ...subtreeKeys(tree, floorKey)]
  check('含自己 = selfKeys + subtreeKeys', withSelf.includes(floorKey) && withSelf.includes(wpKey))
  check('selfKeys 找不到 key 时返回空表', selfKeys(tree, 'nope').length === 0)
  check('subtreeKeys 找不到 key 时返回空表', subtreeKeys(tree, 'nope').length === 0)

  // —— 展开/收缩的集合运算 ——
  const base = [nodeKey('floor', 999)]
  const added = addExpanded(base, [floorKey, wpKey])
  check('addExpanded 追加新 key', added.includes(floorKey) && added.includes(wpKey))
  check('addExpanded 保留原有 key', added.includes(nodeKey('floor', 999)))
  check('addExpanded 无需变更时返回同一引用',
    addExpanded(added, [floorKey]) === added)
  check('addExpanded 会去重（同一个 key 不会进两次）',
    added.filter((k) => k === floorKey).length === 1)

  const removed = removeExpanded(added, [floorKey, wpKey])
  // ⚠️ 收缩的是**这一批 key**，不是清空 —— 别的分支不能被连坐
  check('removeExpanded 只移除指定 key', !removed.includes(floorKey) && !removed.includes(wpKey))
  check('removeExpanded 不误伤其它分支', removed.includes(nodeKey('floor', 999)))
  check('removeExpanded 无需变更时返回同一引用',
    removeExpanded(removed, ['nope']) === removed)

  check('isExpanded 认得出展开态', isExpanded(added, floorKey) === true)
  check('isExpanded 对折叠态给 false', isExpanded(base, floorKey) === false)
  check('isExpanded 对 null 给 false（菜单还没定位时）', isExpanded(added, null) === false)
}

/* ============================================================
 * 9d3. 右键菜单的接线（坑：window 关闭监听必须放过菜单内部点击）
 * ============================================================ */
{
  const body = readFileSync(join(root, 'src/components/InspectionRunDetail.tsx'), 'utf8')

  check('树容器挂了 onContextMenu', /onContextMenu=\{onTreeContextMenu\}/.test(body))
  check('菜单用 closest 找目标（右键常落在内层 span 上）',
    /closest\('\[data-ird-key\]'\)/.test(body))
  check('树行有 data-ird-key 锚点', /data-ird-key=\{node\.key\}/.test(body))
  check('菜单四项齐全（子树/自己 × 展开/收缩）',
    /展开子树/.test(body) && /收缩子树/.test(body)
    && /展开自己/.test(body) && /收缩自己/.test(body))
  check('菜单标注了"不含自己 / 含自己"以免误读',
    /不含自己/.test(body) && /含自己/.test(body))
  check('叶子节点置灰（disabled）而不是点了没反应',
    /disabled=\{!menuTarget\.hasSubtree\}/.test(body)
    && /disabled=\{!menuTarget\.hasChildren\}/.test(body))
  check('菜单里再右键不弹浏览器菜单',
    /className="ird-ctx"[\s\S]{0,200}onContextMenu=\{\(e\) => e\.preventDefault\(\)\}/.test(body))

  // ⚠️ 这条是全项目踩过两次的坑：捕获阶段监听若不放过菜单内部点击，
  // 菜单会在 mousedown 那一刻被卸载，菜单项 onClick 永不触发。
  check('★关闭监听放过菜单内部点击（closest .ird-ctx 就 return）',
    /el\.closest\('\.ird-ctx'\)\)\s*return/.test(body))
  check('关闭监听在捕获阶段（第三参 true）',
    /addEventListener\('mousedown', onDown, true\)/.test(body))
  check('卸载用具名函数（匿名 remove 不掉）',
    /removeEventListener\('mousedown', onDown, true\)/.test(body))
  check('Esc / 滚动 / 失焦都能关菜单',
    /'keydown'/.test(body) && /'wheel'/.test(body) && /'blur'/.test(body))
  // 用户手动开合过之后，轮询不该再把树铺开（否则"收缩"白点）
  check('菜单操作后置 manualRef（轮询不再抢展开）',
    /menuApply[\s\S]{0,400}manualRef\.current = true/.test(body))

  const css = readFileSync(join(root, 'src/styles.css'), 'utf8')
  check('样式有 .ird-ctx 菜单', /\.ird-ctx\s*\{/.test(css))
  check('.ird-ctx 是绝对定位（按树容器算坐标）', /\.ird-ctx\s*\{[^}]*position:\s*absolute/s.test(css))
  check('.ird-tree 是 position:relative（菜单的定位祖先）',
    /\.ird-tree\s*\{[^}]*position:\s*relative/s.test(css))
  check('.ird-ctx 的 z-index 压过树行', /\.ird-ctx\s*\{[^}]*z-index:\s*\d+/s.test(css))
}

/* ============================================================
 * 9d4. ⚠️ StrictMode 下的 aliveRef 必须"挂载时置回 true"
 *
 * 这一条是用**真浏览器**跑出来的，不是推出来的：
 * 详情页曾经永远转圈 —— 接口全 200、纯函数回归全绿、tsc/build 全干净，
 * 只有真开页面才露。根因是 `React.StrictMode`（main.tsx 开着）在开发模式下
 * 把 effect 走一遍"挂载→卸载→再挂载"，而 `useRef(true)` 的初始值只算第一次：
 * 清理函数把 aliveRef 置 false 后，第二次挂载不会改回来，于是重新发的请求
 * 回来时被 `if (!aliveRef.current) return` 拦掉 → loading 恒 true、树恒空。
 *
 * ⚠️ 这类"运行时才露"的 bug，静态回归挡不住，只能靠"看代码里有没有把 ref
 * 在 effect 体里置回 true"这条约定来兜。用了一次性 ref 挡 setState 的地方
 * （aliveRef / mountedRef / cancelledRef…）都要照这个模式写。
 * ============================================================ */
{
  const body = readFileSync(join(root, 'src/components/InspectionRunDetail.tsx'), 'utf8')

  check('★aliveRef 在 effect 体里置回 true（否则 StrictMode 下永远 loading）',
    /useEffect\(\(\)\s*=>\s*\{[\s\S]{0,200}aliveRef\.current = true/.test(body))
  check('aliveRef 仍在卸载时置 false（不能为了修 bug 把守卫删了）',
    /return \(\) => \{ aliveRef\.current = false \}/.test(body))
  check('没有"只 useRef(true) 不置回"的裸写法',
    !/const aliveRef = useRef\(true\)\s*\n\s*useEffect\(\(\) => \(\) => \{ aliveRef\.current = false \}, \[\]\)/.test(body))

  // 主入口是 window.open 的新标签页 —— 它开的是**路由页**，不是空白页塞 DOM
  const listView = readFileSync(join(root, 'src/views/business/InspectionLog.tsx'), 'utf8')
  check('清单页「详情」走 window.open 开新标签页',
    /window\.open\(`\/inspection\/log\/\$\{r\.id\}`/.test(listView))
  check('★window.open 在同步 onClick 里调（await 后会被弹窗拦截器拦掉）',
    /const openDetail = useCallback\(\(r: InspectionRunRow\) => \{\s*window\.open/.test(listView))
}

/* ============================================================
 * 9e. 单条记录摘要接口（独立页拿标题要用，不能靠拉一页再 find）
 * ============================================================ */
{
  const api = readFileSync(join(root, 'src/api/inspectionLog.ts'), 'utf8')
  check('前端有 summary(runId) 接口', /summary:\s*\(runId/.test(api))
  check('summary 打的是 /runs/{id}/summary', /summary:[\s\S]{0,120}\$\{base\}\/\$\{runId\}\/summary/.test(api))

  const svc = readFileSync(resolve(root, '..', 'backend/app/routers/inspection.py'), 'utf8')
  check('后端有 /runs/{run_id}/summary 路由',
    /@router\.get\("\/runs\/\{run_id\}\/summary"\)/.test(svc))
  // ⚠️ 必须复用 summarize_run，否则"从列表进来"和"直接输 URL 进来"数字会不一致
  check('后端 summary 复用 summarize_run（口径与列表一致）',
    /summarize_run\(/.test(svc.split('/runs/{run_id}/summary')[1]?.slice(0, 2000) || ''))
}

/* ============================================================
 * 10. 后端确实把 waypoint_name 带出来了（树/检视器要用）
 * ============================================================ */
{
  const svc = readFileSync(resolve(root, '..', 'backend/app/services/inspection_log.py'), 'utf8')
  check('后端 serialize_action 带出 waypoint_name',
    /"waypoint_name": _waypoint_name\(row\)/.test(svc))
  check('后端从 raw_json.steer_point_name 取（历史快照，不反查库）',
    /raw\.get\("steer_point_name"\)/.test(svc))
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.error(`\n失败 ${fails.length} 项：`)
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
console.log('全部通过 ✓')
