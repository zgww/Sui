/**
 * 轨道节点写入 spec 的回归测试。
 *
 * 轨道是树上真实的 TrackNode，children 里**平铺**着端点与控制点，
 * **顺序即语义**：两个端点之间夹着的控制点归属于这一段。控制点写反
 * （放到新端点之后）不报错，只是曲线画歪——属于最难查的那类 bug，
 * 所以规则集中在 `src/utils/trackSpec.ts`，由这里锁住。
 *
 * 关键：**不手抄源码**——用 tsc 编译真实 TS 源再 import。
 * 运行：node scripts/verify-track-spec.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, writeFileSync, existsSync } from 'node:fs'
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
    'src/utils/trackSpec.ts', 'src/components/trackGeometry.ts',
    '--outDir', out,
    '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
    '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

// 编译产物落在 out/utils/*.js 与 out/components/*.js（保留了目录结构）
const S = await import(pathToFileURL(join(out, 'utils', 'trackSpec.js')).href)
const G = await import(pathToFileURL(join(out, 'components', 'trackGeometry.js')).href)
const {
  childPath, parentPathOf, countOfType, pickTrackPath, trackNodesOf, roundPt, pointProps,
  appendEndpoint, appendEndpointWithControl, withMovedPoint,
  ancestorPaths, nearestTrackPath, placeNewEndpoint, placeNewControl, insertBeside,
  siblingInsertIndex, insertBesidePoint, meanSegmentMeters, meanXGapMeters,
  closeIndexOf, ENDPOINT_TYPE, CONTROL_TYPE, TRACK_TYPE, CLOSE_TYPE,
} = S
const { parseTrackNodes, trackPointsFromNodes, sampleTrack, pointAtFraction } = G

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps

/** 造一个空轨道节点 */
const emptyTrack = () => ({ type: TRACK_TYPE, properties: { name: '轨道 1' }, children: [] })
const EP = (x, y) => ({ type: ENDPOINT_TYPE, properties: { name: 'e', x, y } })
const CP = (x, y) => ({ type: CONTROL_TYPE, properties: { name: 'c', x, y } })

/* ============================================================
 * 1. 路径与计数
 * ============================================================ */
{
  check('childPath 拼接', childPath('root/children/2', 3) === 'root/children/2/children/3')
  check('childPath 根', childPath('root', 0) === 'root/children/0')

  const kids = [EP(0, 0), CP(1, 1), EP(2, 2), CP(3, 3)]
  check('countOfType 端点', countOfType(kids, ENDPOINT_TYPE) === 2)
  check('countOfType 控制点', countOfType(kids, CONTROL_TYPE) === 2)
  check('countOfType 空数组不炸', countOfType([], ENDPOINT_TYPE) === 0)
  check('countOfType undefined 不炸', countOfType(undefined, ENDPOINT_TYPE) === 0)
}

/* ============================================================
 * 2. 当前轨道的选择：选中端点也要归属到它所在的那条轨道
 * ============================================================ */
{
  const tracks = [{ key: 'root/children/0' }, { key: 'root/children/5' }]
  check('无轨道返回 null', pickTrackPath([], 'root') === null)
  check('默认第一条', pickTrackPath(tracks, 'root') === 'root/children/0')
  check('选中轨道本身', pickTrackPath(tracks, 'root/children/5') === 'root/children/5')
  check('选中轨道下的端点 -> 归属该轨道',
    pickTrackPath(tracks, 'root/children/5/children/2') === 'root/children/5')
  // 前缀必须是"整段"：不能把 root/children/50 误判成 root/children/5 的子孙
  check('前缀判定按分隔符整段匹配（不串味）',
    pickTrackPath(tracks, 'root/children/50') === 'root/children/0')
  check('选中无关节点时退回第一条',
    pickTrackPath(tracks, 'root/children/9') === 'root/children/0')
}

/* ============================================================
 * 3. 轨道 -> 平铺点
 * ============================================================ */
{
  const track = emptyTrack()
  track.children = [EP(0, 0), CP(50, -80), EP(100, 0)]
  const ns = trackNodesOf('root/children/0', track)
  check('全部解析出', ns.length === 3)
  check('kind 正确', ns[0].kind === 'endpoint' && ns[1].kind === 'control' && ns[2].kind === 'endpoint')
  check('path 顺序正确',
    ns[0].path === 'root/children/0/children/0'
    && ns[1].path === 'root/children/0/children/1'
    && ns[2].path === 'root/children/0/children/2')

  // 坐标缺失 / 非法 -> 跳过而不是把 NaN 带进采样
  const dirty = { type: TRACK_TYPE, children: [
    EP(0, 0), { type: ENDPOINT_TYPE, properties: { name: 'bad' } }, EP(10, 0),
    { type: 'WaypointNode', properties: { x: 1, y: 1 } },
  ] }
  const dn = trackNodesOf('root/children/0', dirty)
  check('坐标非法者被跳过', dn.length === 2, `实际 ${dn.length}`)
  check('跳过者不影响其余路径', dn[1].path === 'root/children/0/children/2')
  check('非轨道子节点不参与解析', !dn.some((n) => n.path.endsWith('children/3')))

  // 更深层的东西一律不解析，免得误把别的节点当控制点
  const nested = { type: TRACK_TYPE, children: [
    EP(0, 0), { type: ENDPOINT_TYPE, properties: { x: 1, y: 1 }, children: [CP(2, 2)] },
  ] }
  check('孙节点不解析', trackNodesOf('root/children/0', nested).length === 2)
  check('空轨道不炸', trackNodesOf('root/children/0', emptyTrack()).length === 0)
  check('无 children 不炸', trackNodesOf('root/children/0', { type: TRACK_TYPE }).length === 0)
}

/* ============================================================
 * 4. 追加端点：不改动入参 + 路径正确 + 命名递增
 * ============================================================ */
{
  const track = emptyTrack()
  const before = track.children.length
  const r1 = appendEndpoint(track.children, 'root/children/0', { x: 0, y: 0 })
  check('追加端点不改入参', track.children.length === before)
  check('追加端点长度', r1.children.length === 1)
  check('追加端点类型', r1.children[0].type === ENDPOINT_TYPE)
  check('追加端点路径', r1.paths.length === 1 && r1.paths[0] === 'root/children/0/children/0')
  check('追加端点命名', r1.children[0].properties.name === '端点 1')

  const r2 = appendEndpoint(r1.children, 'root/children/0', { x: 100, y: 20 })
  check('第二次追加路径', r2.paths[0] === 'root/children/0/children/1')
  check('第二次追加命名', r2.children[1].properties.name === '端点 2')
  check('坐标写入', r2.children[1].properties.x === 100 && r2.children[1].properties.y === 20)

  // 夹在中间的控制点不应被打乱命名
  const mixed = [EP(0, 0), CP(5, 5)]
  const r3 = appendEndpoint(mixed, 'root/children/0', { x: 9, y: 9 })
  check('端点计数只数端点', r3.children[2].properties.name === '端点 2')
}

/* ============================================================
 * 5. 追加「控制点 + 端点」：顺序即语义
 * ============================================================ */
{
  const r = appendEndpointWithControl([EP(0, 0)], 'root/children/0',
    { x: 50, y: -80 }, { x: 100, y: 0 })
  check('一次追加两个', r.children.length === 3)
  check('控制点在前（顺序即语义）', r.children[1].type === CONTROL_TYPE)
  check('端点在后', r.children[2].type === ENDPOINT_TYPE)
  check('返回路径顺序', r.paths[0].endsWith('children/1') && r.paths[1].endsWith('children/2'))
  check('控制点命名', r.children[1].properties.name === '控制点 1')
  check('端点命名', r.children[2].properties.name === '端点 2')
  check('控制点坐标', r.children[1].properties.x === 50 && r.children[1].properties.y === -80)
  check('端点坐标', r.children[2].properties.x === 100 && r.children[2].properties.y === 0)

  /* 反序写入会得到完全不同的曲线：这里锁住"正序 -> 控制点归属这一段" */
  const good = trackNodesOf('root/children/0', { children: r.children })
  const seg = parseTrackNodes(good).segments
  check('解析出一段', seg.length === 1)
  check('控制点归属该段', seg[0].controls.length === 1)
  check('段首为旧端点', seg[0].a === 0 && seg[0].b === 1)

  const nodes = trackNodesOf('root/children/0', { children: r.children })
  const pts = trackPointsFromNodes(nodes)
  check('三点成两点', pts.length === 2)
  check('曲线确实被控制点拉弯', pts[0].p.y === 0 && pts[0].c2.y === -80)

  // 反过来的写法：控制点放在端点之后 -> 变成"无控制点的直线 + 一个孤儿控制点"
  const bad = [EP(0, 0), EP(100, 0), CP(50, -80)]
  const badNodes = bad.map((n, i) => ({
    kind: n.type === ENDPOINT_TYPE ? 'endpoint' : 'control',
    path: `p${i}`, x: n.properties.x, y: n.properties.y,
  }))
  const badSeg = parseTrackNodes(badNodes).segments
  check('反序后该段没有控制点（曲线会变直）', badSeg[0].controls.length === 0)
  // 尾部的控制点没有"下一段"可归属，会被整段丢弃（orphans 只记第一个端点之前的）
  const badParsed = parseTrackNodes(badNodes)
  check('反序后尾部控制点不进任何段',
    badParsed.segments.every((s) => s.controls.length === 0))
  check('反序后端点仍只有 2 个', badParsed.endpoints.length === 2)
  check('反序后无孤儿（尾部丢弃不计入 orphans）', badParsed.orphans.length === 0)
}

/* ============================================================
 * 6. 连续绘制：直线 -> 曲线 -> 再曲线，航点仍能吸附
 * ============================================================ */
{
  let kids = []
  const TP = 'root/children/0'
  kids = appendEndpoint(kids, TP, { x: 0, y: 0 }).children
  kids = appendEndpointWithControl(kids, TP, { x: 150, y: -120 }, { x: 300, y: 0 }).children
  kids = appendEndpointWithControl(kids, TP, { x: 450, y: 120 }, { x: 600, y: 0 }).children
  kids = appendEndpoint(kids, TP, { x: 700, y: 0 }).children

  const nodes = trackNodesOf(TP, { children: kids })
  check('连续绘制后节点数', nodes.length === 6)
  check('端点数', countOfType(kids, ENDPOINT_TYPE) === 4)
  check('控制点数', countOfType(kids, CONTROL_TYPE) === 2)
  const segs = parseTrackNodes(nodes).segments
  check('段数 = 端点数 - 1', segs.length === 3, `实际 ${segs.length}`)
  check('第一段有 1 个控制点', segs[0].controls.length === 1)
  check('第二段有 1 个控制点', segs[1].controls.length === 1)
  check('最后一段无控制点（直线）', segs[2].controls.length === 0)

  const pts = trackPointsFromNodes(nodes)
  const sp = sampleTrack(pts, 64)
  check('能采样出曲线', sp.pts.length > 2 && sp.total > 0)
  // 曲线上下摆动，总弧长必然大于首尾直线距离
  check('弧长大于直线距离（说明确实弯了）', sp.total > 700, `total=${sp.total.toFixed(1)}`)

  // 航点按 x 归一化后仍应落在曲线上
  const p0 = pointAtFraction(sp, 0)
  const p1 = pointAtFraction(sp, 1)
  check('u=0 落在起点', near(p0.x, 0, 1e-6) && near(p0.y, 0, 1e-6))
  check('u=1 落在终点', near(p1.x, 700, 1e-6) && near(p1.y, 0, 1e-6))
  const mid = pointAtFraction(sp, 0.5)
  check('u=0.5 有定义', Number.isFinite(mid.x) && Number.isFinite(mid.y))
}

/* ============================================================
 * 7. 移动点位：只改坐标，不动类型/名称/顺序
 * ============================================================ */
{
  const kids = [EP(0, 0), CP(50, -80), EP(100, 0)]
  const moved = withMovedPoint(kids, 1, { x: 60, y: -30 })
  check('移动不改长度', moved.length === 3)
  check('移动不改类型', moved[1].type === CONTROL_TYPE)
  check('移动写入坐标', moved[1].properties.x === 60 && moved[1].properties.y === -30)
  check('移动保留名称', moved[1].properties.name === 'c')
  check('移动不改入参', kids[1].properties.x === 50)
  check('其他节点不受影响', moved[2].properties.x === 100)
  check('越界下标原样返回', withMovedPoint(kids, 9, { x: 0, y: 0 }).length === 3)
  check('空数组不炸', withMovedPoint([], 0, { x: 0, y: 0 }).length === 0)
}

/* ============================================================
 * 8. 坐标收敛与 schema 默认值
 * ============================================================ */
{
  const r = roundPt({ x: 1.23456, y: -9.87654 })
  check('坐标收敛到 3 位', r.x === 1.235 && r.y === -9.877)
  check('整数不被污染', roundPt({ x: 10, y: 0 }).x === 10)

  const p = pointProps({ name: 'x', z: 0 }, '端点 9', { x: 1.1111, y: 2 })
  check('默认值被保留', p.z === 0)
  check('名称覆盖默认值', p.name === '端点 9')
  check('坐标覆盖默认值', p.x === 1.111 && p.y === 2)
  check('无默认值不炸', pointProps(undefined, 'a', { x: 0, y: 0 }).name === 'a')
}

/* ============================================================
 * 9. 清空轨道后再画：不残留、可继续
 * ============================================================ */
{
  let kids = appendEndpointWithControl([], 'root/children/0',
    { x: 10, y: 10 }, { x: 20, y: 20 }).children
  kids = []
  check('清空后无节点', trackNodesOf('root/children/0', { children: kids }).length === 0)
  const again = appendEndpoint(kids, 'root/children/0', { x: 0, y: 0 })
  check('清空后可继续画', again.children.length === 1)
  check('清空后命名从 1 重新开始', again.children[0].properties.name === '端点 1')
}

/* ============================================================
 * 10. 树上「添加子节点」：端点/控制点要归到所属轨道，且落位合理
 * ============================================================ */
{
  // 祖先链（由长到短）
  check('祖先链含自身', ancestorPaths('root/children/1/children/2')[0] === 'root/children/1/children/2')
  check('祖先链到 root 为止',
    ancestorPaths('root/children/1/children/2').join('|') === 'root/children/1/children/2|root/children/1|root')
  check('root 的祖先链只有自己', ancestorPaths('root').join('|') === 'root')

  /* 构造：root -> [Group(0) -> [Track(0) -> [E(0), C(1), E(2)]], Waypoint(1)] */
  const trackKey = 'root/children/0/children/0'
  const flat = [
    { key: 'root', node: { type: 'GroupNode' } },
    { key: 'root/children/0', node: { type: 'GroupNode' } },
    { key: trackKey, node: { type: TRACK_TYPE, children: [EP(0, 0), CP(50, -60), EP(100, 0)] } },
    { key: 'root/children/0/children/0/children/0', node: EP(0, 0) },
    { key: 'root/children/0/children/0/children/1', node: CP(50, -60) },
    { key: 'root/children/0/children/0/children/2', node: EP(100, 0) },
    { key: 'root/children/1', node: { type: 'WaypointNode' } },
  ]

  check('选中轨道 -> 自己', nearestTrackPath(flat, trackKey) === trackKey)
  check('选中端点 -> 归到所属轨道',
    nearestTrackPath(flat, 'root/children/0/children/0/children/2') === trackKey)
  check('选中控制点 -> 归到所属轨道',
    nearestTrackPath(flat, 'root/children/0/children/0/children/1') === trackKey)
  check('选中无关节点 -> 找不到轨道', nearestTrackPath(flat, 'root/children/1') === null)
  check('空树 -> null', nearestTrackPath([], 'root') === null)
  check('parentPathOf 与 childPath 互逆',
    parentPathOf(childPath('root/children/0', 3)) === 'root/children/0')

  /* 端点：追加到末尾 + 坐标不叠在原点 */
  const kids = [EP(0, 0), CP(50, -60), EP(100, 0)]
  const pe = placeNewEndpoint(kids)
  check('端点追加到末尾', pe.index === 3)
  // 外扩 = 平均段长（这段是 100 m），不是"默认轨道 1000 宽"时代写死的常数
  check('端点接在最后一点之后', pe.point.x === 200 && pe.point.y === 0, JSON.stringify(pe.point))
  check('外扩距离可显式指定', placeNewEndpoint(kids, 7).point.x === 107)
  // 单位统一为米之后：几十米的轨道新点也只外扩几十米，不会再被甩出视野
  check('短轨道外扩贴合自身尺度',
    placeNewEndpoint([EP(0, 0), EP(5, 0)]).point.x === 10)

  /* 平均段长：只看端点（跳过夹在中间的控制点），带 y 走欧氏距离 */
  check('平均段长跳过控制点', meanSegmentMeters(kids) === 100)
  check('平均段长走欧氏距离', near(meanSegmentMeters([EP(0, 0), EP(3, 4)]), 5))
  check('平均段长不足两个端点 -> null', meanSegmentMeters([EP(0, 0)]) === null)
  check('平均段长空数组 -> null', meanSegmentMeters([]) === null)

  check('空轨道端点落在原点', placeNewEndpoint([]).point.x === 0)
  check('空轨道端点也是追加', placeNewEndpoint([]).index === 0)
  // 只挑有坐标的点，坏数据不该让落位变成 NaN
  const dirtyKids = [EP(0, 0), { type: ENDPOINT_TYPE, properties: { name: 'bad' } }]
  check('坏坐标不污染落位', Number.isFinite(placeNewEndpoint(dirtyKids).point.x))

  /* 控制点：插到最后一个端点之前 */
  const pc = placeNewControl(kids)
  check('控制点插到最后一个端点之前', pc !== null && pc.index === 2)
  check('控制点落在弦中点上方',
    pc.point.x === 50 && pc.point.y === -60, JSON.stringify(pc.point))
  check('不足两个端点时不给加控制点', placeNewControl([EP(0, 0)]) === null)
  check('空轨道不给加控制点', placeNewControl([]) === null)

  /* 插进去之后必须真的被解析成"这一段的控制点" —— 否则等于加了没用 */
  const after = kids.slice()
  after.splice(pc.index, 0, { type: CONTROL_TYPE, properties: { name: 'c', ...pc.point } })
  const parsed = parseTrackNodes(trackNodesOf(trackKey, { children: after }))
  check('插入后仍是一段', parsed.segments.length === 1)
  check('插入后该段有 2 个控制点', parsed.segments[0].controls.length === 2)
  check('插入后无孤儿', parsed.orphans.length === 0)

  /* 反例锁住：若当年写成"追加到末尾"，控制点会被静默丢弃 */
  const wrong = kids.slice()
  wrong.push({ type: CONTROL_TYPE, properties: { name: 'c', x: 50, y: -60 } })
  const wrongParsed = parseTrackNodes(trackNodesOf(trackKey, { children: wrong }))
  check('追加到末尾 -> 该段控制点不增加', wrongParsed.segments[0].controls.length === 1)
  check('追加到末尾 -> 尾部控制点被丢弃', wrongParsed.orphans.length === 0)
}

/* ============================================================
 * 11. 闭合（closePath）：端点/控制点必须排在它之前
 * ============================================================ */
{
  const CL = () => ({ type: CLOSE_TYPE, properties: { name: '闭合' } })
  const TP = 'root/children/0'

  check('找闭合标记下标', closeIndexOf([EP(0, 0), CL(), EP(1, 1)]) === 1)
  check('没有闭合标记返回 -1', closeIndexOf([EP(0, 0), EP(1, 1)]) === -1)
  check('空数组不炸', closeIndexOf([]) === -1)

  /* 端点必须插在闭合标记之前 —— 否则闭合连回的是新端点而不是首端点 */
  const withClose = [EP(0, 0), EP(100, 0), CL()]
  const pe = placeNewEndpoint(withClose)
  check('端点插在闭合标记之前', pe.index === 2, `index=${pe.index}`)
  const inserted = withClose.slice()
  inserted.splice(pe.index, 0, { type: ENDPOINT_TYPE, properties: { ...pe.point, name: 'e' } })
  check('插入后闭合标记仍在最后', inserted[inserted.length - 1].type === CLOSE_TYPE)
  check('插入后端点都在闭合标记之前',
    inserted.findIndex((n) => n.type === CLOSE_TYPE) === 3)

  /* 地图绘制追加端点时同理 */
  const ar = appendEndpoint(withClose, TP, { x: 200, y: 0 })
  check('appendEndpoint 也在闭合标记之前', ar.children.findIndex((n) => n.type === CLOSE_TYPE) === 3)
  check('appendEndpoint 返回的路径正确', ar.paths[0] === 'root/children/0/children/2')
  const ar2 = appendEndpointWithControl(withClose, TP, { x: 150, y: -50 }, { x: 200, y: 0 })
  check('append 控制点+端点也在闭合之前',
    ar2.children.findIndex((n) => n.type === CLOSE_TYPE) === 4)
  check('append 返回两条路径', ar2.paths.length === 2
    && ar2.paths[0].endsWith('children/2') && ar2.paths[1].endsWith('children/3'))

  /* 成环后加控制点：应该归到"末点 -> 首点"那一段，插在末端点之后 */
  const pc = placeNewControl(withClose)
  check('成环时可以加控制点', pc !== null)
  check('成环时控制点插在末端点之后（而非之前）', pc.index === 2, `index=${pc.index}`)
  check('成环时弦取末点->首点', pc.point.x === 50 && pc.point.y === -60, JSON.stringify(pc.point))
  const afterC = withClose.slice()
  afterC.splice(pc.index, 0, { type: CONTROL_TYPE, properties: { name: 'c', ...pc.point } })
  const parsedC = parseTrackNodes(trackNodesOf(TP, { children: afterC }))
  check('成环后闭合段拿到这个控制点',
    parsedC.closed && parsedC.segments[parsedC.segments.length - 1].controls.length === 1)
  check('成环后闭合段仍是末点->首点',
    parsedC.segments[parsedC.segments.length - 1].a === 1
    && parsedC.segments[parsedC.segments.length - 1].b === 0)

  /* 未成环时行为不变（插在最后一个端点之前） */
  const pc2 = placeNewControl([EP(0, 0), EP(100, 0)])
  check('未成环仍插在末端点之前', pc2.index === 1)

  /* 闭合标记本身不参与曲线，但必须能被解析出来 */
  const ns = trackNodesOf(TP, { children: withClose })
  check('闭合标记被解析成 close', ns.length === 3 && ns[2].kind === 'close')
  check('闭合标记保留 path', ns[2].path === 'root/children/0/children/2')
  check('闭合轨道解析为成环', parseTrackNodes(ns).closed === true)
  check('闭合轨道端点只有 2 个', parseTrackNodes(ns).endpoints.length === 2)
}

/* ============================================================
 * 10. 在前 / 后插入：insertBeside
 * ============================================================ */
{
  // [e0(0,0), c(50,40), e1(100,0), e2(300,0)]
  const kids = [EP(0, 0), CP(50, 40), EP(100, 0), EP(300, 0)]

  // 在 e1（下标2）之前 -> 下标2，坐标取 prev 端点 e0 与 e1 的中点
  let r = insertBeside(kids, 2, 'before')
  check('在前插入下标 = 目标下标', r.index === 2)
  check('在前插入坐标 = 与上一端点中点', r.point.x === 50 && r.point.y === 0, JSON.stringify(r.point))

  // 在 e1 之后 -> 下标3，坐标取 e1 与下一端点 e2 的中点
  r = insertBeside(kids, 2, 'after')
  check('在后插入下标 = 目标下标+1', r.index === 3)
  check('在后插入坐标 = 与下一端点中点', r.point.x === 200 && r.point.y === 0, JSON.stringify(r.point))

  // 控制点抬升：y 再往上抬 lift
  r = insertBeside(kids, 2, 'before', { lift: 60 })
  check('控制点抬升生效', r.point.x === 50 && r.point.y === -60, JSON.stringify(r.point))

  // 首端点之前 / 末端点之后：没有相邻端点，沿 x 外扩——
  // 距离取平均段长（端点 0/100/300 -> 段长 100 与 200，均值 150 m），不是写死常数
  check('外扩距离 = 平均段长', meanSegmentMeters(kids) === 150)
  r = insertBeside(kids, 0, 'before')
  check('首端点之前：外扩平均段长', r.index === 0 && r.point.x === -150, JSON.stringify(r))
  r = insertBeside(kids, 3, 'after')
  check('末端点之后：外扩平均段长', r.index === 4 && r.point.x === 450, JSON.stringify(r))
  r = insertBeside(kids, 3, 'after', { span: 25 })
  check('外扩距离可配', r.point.x === 325, JSON.stringify(r))

  // 相邻端点判定要跳过控制点：e1 的"上一个端点"是 e0（不是控制点）
  r = insertBeside([EP(0, 0), CP(50, 40), EP(100, 0)], 2, 'before')
  check('找相邻端点时跳过控制点', r.point.x === 50 && r.point.y === 0, JSON.stringify(r))

  // 闭合标记必须留在最后
  const withClose = [EP(0, 0), EP(100, 0), { type: CLOSE_TYPE, properties: {} }]
  r = insertBeside(withClose, 1, 'after')
  check('闭合轨道：插在末端点之后仍排在闭合标记前', r.index === 2, JSON.stringify(r))
  r = insertBeside(withClose, 1, 'before')
  check('闭合轨道：插在末端点之前', r.index === 1 && r.point.x === 50, JSON.stringify(r))

  // 非法下标
  check('下标越界返回 null', insertBeside(kids, 9, 'before') === null)
  check('负下标返回 null', insertBeside(kids, -1, 'before') === null)
  check('非整数下标返回 null', insertBeside(kids, 1.5, 'before') === null)
  check('空数组返回 null', insertBeside([], 0, 'before') === null)

  // 落位后仍能被正确解析：在 e1 前插一个端点 -> 3 个端点、控制点归到新段
  const inserted = kids.slice()
  const place = insertBeside(kids, 2, 'before')
  inserted.splice(place.index, 0, EP(place.point.x, place.point.y))
  const ns = trackNodesOf('root/children/0', { children: inserted })
  const parsed = parseTrackNodes(ns)
  check('插入后解析出 4 个端点', parsed.endpoints.length === 4, JSON.stringify(parsed.endpoints.length))
  check('插入后控制点不再是孤儿', parsed.orphans.length === 0, JSON.stringify(parsed.orphans))
  check('插入后段数 = 端点数-1', parsed.segments.length === 3, JSON.stringify(parsed.segments.length))
  // 原控制点现在归到「e0 -> 新端点」这一段
  check('原控制点归到前一段', parsed.segments[0].controls.length === 1,
    JSON.stringify(parsed.segments[0]))
  check('后一段是直线（无控制点）', parsed.segments[1].controls.length === 0,
    JSON.stringify(parsed.segments[1]))
}

/* ============================================================
 * 11. 通用同级插入：siblingInsertIndex / insertBesidePoint
 *      （"在前/后添加子节点"对航点这类非轨道节点同样成立）
 * ============================================================ */
{
  // 一串航点：x = 0 / 10 / 20（没有控制点、没有轨道语义）
  const wp = (x) => ({ type: 'WaypointNode', properties: { name: 'w', x, y: 0 } })
  const kids = [wp(0), wp(10), wp(20)]

  check('通用：在前插入下标 = 目标下标', siblingInsertIndex(kids, 1, 'before') === 1)
  check('通用：在后插入下标 = 目标下标+1', siblingInsertIndex(kids, 1, 'after') === 2)
  check('通用：末尾之后不越界', siblingInsertIndex(kids, 2, 'after') === 3)
  check('通用：非法下标返回 null', siblingInsertIndex(kids, 9, 'before') === null)

  // 航点：x 取相邻兄弟的中点，保证树序 == 轨道左右顺序
  let r = insertBesidePoint(kids, 1, 'before')
  check('航点在前：x 取左邻居中点', r.index === 1 && r.point.x === 5, JSON.stringify(r))
  r = insertBesidePoint(kids, 1, 'after')
  check('航点在后：x 取右邻居中点', r.index === 2 && r.point.x === 15, JSON.stringify(r))

  // 首 / 末：没有邻居 -> 沿 x 外扩一段（默认取兄弟的平均 x 间距，米）
  r = insertBesidePoint(kids, 0, 'before')
  check('首个之前：外扩平均间距',
    r.index === 0 && r.point.x === -10, JSON.stringify(r))
  r = insertBesidePoint(kids, 2, 'after')
  check('末个之后：外扩平均间距',
    r.index === 3 && r.point.x === 30, JSON.stringify(r))
  r = insertBesidePoint(kids, 2, 'after', 5)
  check('外扩距离可配', r.point.x === 25, JSON.stringify(r))

  /* 平均 x 间距：只看 x（航点的 x 是沿轨米数，没有 y 参与） */
  check('平均 x 间距', meanXGapMeters(kids) === 10)
  check('平均 x 间距忽略缺 x 的兄弟',
    meanXGapMeters([wp(0), { type: 'WaypointNode', properties: {} }, wp(20)]) === 20)
  check('平均 x 间距不足两个 -> null', meanXGapMeters([wp(0)]) === null)

  // 邻居缺 x（脏数据）时跳过它继续找，而不是算出 NaN
  const dirty = [wp(0), { type: 'WaypointNode', properties: { name: 'bad' } }, wp(20)]
  r = insertBesidePoint(dirty, 1, 'before')
  check('邻居 x 缺失时跳过继续找', r.point.x === 0, JSON.stringify(r))
  r = insertBesidePoint(dirty, 1, 'after')
  check('另一侧同样跳过', r.point.x === 10, JSON.stringify(r))
  check('全程无有效 x 也不出 NaN', Number.isFinite(insertBesidePoint(
    [{ type: 'WaypointNode', properties: {} }], 0, 'after').point.x))

  // 与轨道系 insertBeside 的分工：端点场景要跳过控制点找端点，这里不用
  const mixed = [EP(0, 0), CP(50, 40), EP(100, 0)]
  check('轨道系仍走 insertBeside（跳过控制点）',
    insertBeside(mixed, 2, 'before').point.x === 50)
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.log('失败：')
  fails.forEach((f) => console.log('  ✗ ' + f))
  process.exit(1)
}
console.log('全部通过 ✓')
