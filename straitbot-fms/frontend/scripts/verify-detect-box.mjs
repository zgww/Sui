/**
 * 检测框几何回归测试（拍照动作点检视器里的「检测框绑定」）。
 *
 * 与 verify-track-geometry.mjs 同一套路：**不手抄源码**，用 tsc 把
 * src/components/detectBoxGeometry.ts 编到临时目录再 import。
 * 运行：node scripts/verify-detect-box.mjs
 *
 * 这里锁住的全是"画歪了但看不出来"的那类：坐标没夹到 0~1、矩形顶点顺序反了、
 * 命中小框永远选不中、脏数据把画布画成 NaN。
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync, readFileSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'dbx-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath,
    [tscEntry, 'src/components/detectBoxGeometry.ts', '--outDir', out,
      '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
      '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

const G = await import(pathToFileURL(join(out, 'detectBoxGeometry.js')).href)
const {
  fitImageRect, clamp01, clampNorm, normToScreen, screenToNorm, rectPoints,
  polygonArea, isTinyBox, MIN_BOX_AREA, boxCenter, pointInPolygon, hitBoxIndex,
  dedupePoints, sanitizePoints,
  fitViewport, worldToScreen, screenToWorld, normToWorld, worldToNorm,
  panFrom, zoomAt, ZOOM_MIN, ZOOM_MAX, VERTEX_PX, DRAG_THRESHOLD_PX, isDrag,
  hitVertexIndex, translatePoints, moveRectVertex,
} = G

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps

/* ============================================================
 * 1. contain 适配：等比、居中、绝不拉伸
 * ============================================================ */
{
  // 宽图放进窄画布 -> 左右不留边、上下留边
  const r = fitImageRect(1000, 500, 400, 400)
  check('等比：宽度铺满', near(r.w, 400))
  check('等比：高度按原始比例', near(r.h, 200), `${r.h}`)
  check('居中：上下留边相等', near(r.y, (400 - 200) / 2))
  check('居中：左右不留边', near(r.x, 0))

  // 高图反过来
  const r2 = fitImageRect(500, 1000, 400, 400)
  check('高图：高度铺满', near(r2.h, 400))
  check('高图：宽度按原始比例', near(r2.w, 200))
  check('高图：左右留边相等', near(r2.x, 100))

  // 长宽比一致 -> 刚好铺满，没有留边
  const r3 = fitImageRect(800, 400, 400, 200)
  check('同比例：刚好铺满', near(r3.w, 400) && near(r3.h, 200) && near(r3.x, 0) && near(r3.y, 0))

  // 脏数据（0 / 负数）不炸，退化成空矩形而不是 NaN
  const bad = fitImageRect(0, 0, 400, 200)
  check('零尺寸图 -> 空矩形', bad.w === 0 && bad.h === 0)
  check('负尺寸画布 -> 空矩形', fitImageRect(10, 10, -5, 100).w === 0)
}

/* ============================================================
 * 2. 归一化 <-> 屏幕 换算（唯一的换算入口，中间必过视口）
 * ============================================================ */
{
  // 1000x500 的图，contain 进 400x400 画布 -> 缩到 0.4，纵向居中留 100
  const iw = 1000
  const ih = 500
  const vp = fitViewport(iw, ih, 400, 400)
  check('fit 视口缩放', near(vp.k, 0.4), `${vp.k}`)
  check('fit 视口居中', near(vp.x, 0) && near(vp.y, 100))

  check('(0,0) -> 图左上角', near(normToScreen({ x: 0, y: 0 }, vp, iw, ih).x, 0)
    && near(normToScreen({ x: 0, y: 0 }, vp, iw, ih).y, 100))
  check('(1,1) -> 图右下角', near(normToScreen({ x: 1, y: 1 }, vp, iw, ih).x, 400)
    && near(normToScreen({ x: 1, y: 1 }, vp, iw, ih).y, 300))
  check('(0.5,0.5) -> 图中心', near(normToScreen({ x: 0.5, y: 0.5 }, vp, iw, ih).x, 200)
    && near(normToScreen({ x: 0.5, y: 0.5 }, vp, iw, ih).y, 200))

  // 往返必须还原，否则"拖完再读回来"会漂
  const p = { x: 0.37, y: 0.62 }
  const back = screenToNorm(normToScreen(p, vp, iw, ih), vp, iw, ih)
  check('往返一致', near(back.x, p.x) && near(back.y, p.y), JSON.stringify(back))

  // 拖到图外要夹住，不能存出 -0.3 这种越界值
  check('左上越界夹到 0', screenToNorm({ x: -50, y: -50 }, vp, iw, ih).x === 0
    && screenToNorm({ x: -50, y: -50 }, vp, iw, ih).y === 0)
  check('右下越界夹到 1', screenToNorm({ x: 9999, y: 9999 }, vp, iw, ih).x === 1
    && screenToNorm({ x: 9999, y: 9999 }, vp, iw, ih).y === 1)

  // 世界坐标（图片像素）也要能往返
  check('世界 -> 屏幕 -> 世界', near(screenToWorld(worldToScreen({ x: 250, y: 125 }, vp), vp).x, 250))
  check('归一化 <-> 世界', near(normToWorld({ x: 0.5, y: 0.5 }, iw, ih).x, 500))
  check('世界 -> 归一化', near(worldToNorm({ x: 500, y: 250 }, iw, ih).y, 0.5))

  // 零尺寸不炸
  check('零尺寸图 -> 单位视口', fitViewport(0, 0, 400, 200).k === 1)
  check('k=0 的视口不除零', screenToWorld({ x: 10, y: 10 }, { x: 0, y: 0, k: 0 }).x === 0)
  check('worldToNorm 零尺寸 -> 0', worldToNorm({ x: 5, y: 5 }, 0, 0).x === 0)
  check('clamp01 处理 NaN', clamp01(NaN) === 0)
  check('clampNorm 双向夹取', clampNorm({ x: -1, y: 2 }).x === 0 && clampNorm({ x: -1, y: 2 }).y === 1)
}

/* ============================================================
 * 2b. 平移与缩放（画布手势的核心，错了最难查）
 * ============================================================ */
{
  const iw = 1000
  const ih = 500
  const base = fitViewport(iw, ih, 400, 400)

  /* 平移必须**绝对计算**：同一帧两个 move 都从 base 重算，不累加 */
  const p1 = panFrom(base, { x: 0, y: 0 }, { x: 30, y: 10 })
  const p2 = panFrom(base, { x: 0, y: 0 }, { x: 50, y: 20 })
  check('平移：位移量正确', near(p1.x, base.x + 30) && near(p1.y, base.y + 10))
  // 关键不变量：两次独立计算的差 == 一次大位移的结果（增量累加做不到这点）
  check('平移：不是增量累加',
    near(p2.x - base.x, 50) && near(p1.x - base.x, 30), `${p1.x} ${p2.x}`)
  check('平移：不动缩放', p1.k === base.k)

  /* 缩放：锚点下的那个点必须不动 */
  const anchor = { x: 120, y: 200 }
  const worldBefore = screenToWorld(anchor, base)
  const z = zoomAt(base, anchor, 2, base.k)
  const worldAfter = screenToWorld(anchor, z)
  check('缩放：倍数生效', near(z.k, base.k * 2))
  check('缩放：锚点下的世界点不动',
    near(worldAfter.x, worldBefore.x) && near(worldAfter.y, worldBefore.y),
    `${JSON.stringify(worldBefore)} -> ${JSON.stringify(worldAfter)}`)

  /* 缩放上下限：相对 contain 的倍数，不能无限放大/缩到看不见 */
  const zoomIn = zoomAt(base, anchor, 1e6, base.k)
  check('放大有上限', near(zoomIn.k, base.k * ZOOM_MAX), `${zoomIn.k}`)
  const zoomOut = zoomAt(base, anchor, 1e-6, base.k)
  check('缩小有下限', near(zoomOut.k, base.k * ZOOM_MIN), `${zoomOut.k}`)

  /* 拖动阈值：斜着拖 2+2px 也算拖（欧拉距离，不是分别比 x/y） */
  check('阈值内不算拖', !isDrag({ x: 0, y: 0 }, { x: 2, y: 2 }))
  check('斜着拖过阈值算拖', isDrag({ x: 0, y: 0 }, { x: 3, y: 3 }))
  check('阈值常量为正', DRAG_THRESHOLD_PX > 0)
}

/* ============================================================
 * 2c. 端点命中与整体平移
 * ============================================================ */
{
  const iw = 1000
  const ih = 1000
  const vp = fitViewport(iw, ih, 500, 500)   // k = 0.5
  const sq = rectPoints({ x: 0.2, y: 0.2 }, { x: 0.6, y: 0.6 })

  const v0 = normToScreen(sq[0], vp, iw, ih)
  check('端点正上命中', hitVertexIndex(v0, sq, vp, iw, ih) === 0)
  check('端点外一个半径不命中',
    hitVertexIndex({ x: v0.x + VERTEX_PX + 2, y: v0.y }, sq, vp, iw, ih) === -1)
  check('框中心不命中端点',
    hitVertexIndex(normToScreen({ x: 0.4, y: 0.4 }, vp, iw, ih), sq, vp, iw, ih) === -1)
  // 放大后同一个端点在屏幕上挪了地方，命中半径仍是屏幕 7px（手感不变）
  const zvp = zoomAt(vp, { x: 250, y: 250 }, 4, vp.k)
  const zv0 = normToScreen(sq[0], zvp, iw, ih)
  check('放大后端点仍能命中', hitVertexIndex(zv0, sq, zvp, iw, ih) === 0)

  /* 整体平移：形状不变、只是挪位置 */
  const moved = translatePoints(sq, { x: 0.1, y: -0.1 })
  check('平移后点数不变', moved.length === sq.length)
  check('平移后相对形状不变',
    near(moved[1].x - moved[0].x, sq[1].x - sq[0].x)
    && near(moved[2].y - moved[1].y, sq[2].y - sq[1].y))
  check('平移量正确', near(moved[0].x, sq[0].x + 0.1) && near(moved[0].y, sq[0].y - 0.1))
  // 拖出画面外要夹住，不能让框消失在画布外找不回来
  const clamped = translatePoints(sq, { x: -9, y: -9 })
  check('平移越界被夹回', clamped.every((p) => p.x >= 0 && p.y >= 0))
  check('平移空数组不炸', translatePoints([], { x: 1, y: 1 }).length === 0)
}

/* ============================================================
 * 3. 矩形：轴对齐 + 顶点顺序固定（左上起顺时针）
 * ============================================================ */
{
  // 故意从右下往左上拖，结果必须和正着拖一样
  const a = rectPoints({ x: 0.2, y: 0.3 }, { x: 0.6, y: 0.8 })
  const b = rectPoints({ x: 0.6, y: 0.8 }, { x: 0.2, y: 0.3 })
  check('反向拖拽得到同一个矩形',
    JSON.stringify(a) === JSON.stringify(b), JSON.stringify(b))
  check('矩形是 4 点', a.length === 4)
  check('第 0 点是左上角', a[0].x === 0.2 && a[0].y === 0.3, JSON.stringify(a[0]))
  check('第 1 点是右上角', a[1].x === 0.6 && a[1].y === 0.3)
  check('第 2 点是右下角', a[2].x === 0.6 && a[2].y === 0.8)
  check('第 3 点是左下角', a[3].x === 0.2 && a[3].y === 0.8)

  // 矩形面积退化成 w*h —— 这样两种形状才能共用同一个"太小不算框"的阈值
  check('矩形面积 = w*h', near(polygonArea(a), 0.4 * 0.5), `${polygonArea(a)}`)
}

/* ============================================================
 * 4. 面积与"太小不算框"
 * ============================================================ */
{
  check('少于 3 点面积为 0', polygonArea([{ x: 0, y: 0 }, { x: 1, y: 1 }]) === 0)
  check('空数组面积为 0', polygonArea([]) === 0)

  // 三角形：底 1 高 1 -> 0.5
  check('三角形面积', near(polygonArea([{ x: 0, y: 0 }, { x: 1, y: 0 }, { x: 0, y: 1 }]), 0.5))
  // 逆时针给同样的点，面积取绝对值 -> 一样
  check('顶点反向绕面积不变',
    near(polygonArea([{ x: 0, y: 1 }, { x: 1, y: 0 }, { x: 0, y: 0 }]), 0.5))

  const big = rectPoints({ x: 0.1, y: 0.1 }, { x: 0.5, y: 0.5 })
  const tiny = rectPoints({ x: 0.5, y: 0.5 }, { x: 0.505, y: 0.505 })
  check('正常框不算小', !isTinyBox(big), `${polygonArea(big)}`)
  check('手抖点一下算小', isTinyBox(tiny), `${polygonArea(tiny)}`)
  check('阈值本身有意义', MIN_BOX_AREA > 0 && MIN_BOX_AREA < 0.01)
  // 1000px 图上的阈值换算：至少得有十几个像素见方，否则选不中
  check('阈值换算到 1000px 图 >= 12px 见方',
    Math.sqrt(MIN_BOX_AREA) * 1000 >= 12, `${Math.sqrt(MIN_BOX_AREA) * 1000}`)
}

/* ============================================================
 * 5. 命中测试：矩形/多边形共用一份，后画的盖在上面
 * ============================================================ */
{
  const sq = [{ x: 0, y: 0 }, { x: 1, y: 0 }, { x: 1, y: 1 }, { x: 0, y: 1 }]
  check('中心命中', pointInPolygon({ x: 0.5, y: 0.5 }, sq))
  check('外部不命中', !pointInPolygon({ x: 1.5, y: 0.5 }, sq))
  check('靠边内命中', pointInPolygon({ x: 0.01, y: 0.5 }, sq))

  // 凹多边形：射线法要能穿过凹口
  const L = [{ x: 0, y: 0 }, { x: 1, y: 0 }, { x: 1, y: 0.4 },
    { x: 0.4, y: 0.4 }, { x: 0.4, y: 1 }, { x: 0, y: 1 }]
  check('凹多边形：凹口内命中', pointInPolygon({ x: 0.2, y: 0.9 }, L))
  check('凹多边形：凹口外不命中', !pointInPolygon({ x: 0.8, y: 0.9 }, L))
  check('凹多边形：短臂内命中', pointInPolygon({ x: 0.8, y: 0.2 }, L))

  const boxes = [
    { points: sq },                                              // 铺满整图
    { points: rectPoints({ x: 0.2, y: 0.2 }, { x: 0.4, y: 0.4 }) }, // 压在上面
  ]
  check('重叠处命中后画的那个', hitBoxIndex({ x: 0.3, y: 0.3 }, boxes) === 1)
  check('只在底层框内的点命中底层', hitBoxIndex({ x: 0.7, y: 0.7 }, boxes) === 0)
  check('都不命中返回 -1', hitBoxIndex({ x: 5, y: 5 }, boxes) === -1)
  check('空列表返回 -1', hitBoxIndex({ x: 0.5, y: 0.5 }, []) === -1)
  // 少于 3 点的"框"围不出区域，不该被命中（pointInPolygon 对线段恒 false）
  check('2 点的退化框不命中', hitBoxIndex({ x: 0.5, y: 0.5 },
    [{ points: [{ x: 0, y: 0.5 }, { x: 1, y: 0.5 }] }]) === -1)
}

/* ============================================================
 * 6. 顶点清洗（脏数据 / 连点重复 / 首尾重合）
 * ============================================================ */
{
  check('去掉连续重复点',
    dedupePoints([{ x: 0.1, y: 0.1 }, { x: 0.1, y: 0.1 }, { x: 0.5, y: 0.5 }]).length === 2)
  // 中间隔了一个点再回到原处，是真·自交多边形，不能当成重复点吃掉
  check('不去掉非相邻的重复点',
    dedupePoints([{ x: 0.1, y: 0.1 }, { x: 0.5, y: 0.5 },
      { x: 0.1, y: 0.1 }, { x: 0.9, y: 0.9 }]).length === 4)
  // 闭合由绘制负责，点序列里不该存一个重复的首点
  check('首尾重复时去掉尾点',
    dedupePoints([{ x: 0, y: 0 }, { x: 1, y: 0 }, { x: 0, y: 0 }]).length === 2)
  // 「点两下就回起点」的收尾手势：洗完只剩 2 点，靠调用方的 `length < 3` 拦掉，
  // 不至于建出一个围不出区域的"多边形"
  check('回到起点的收尾手势洗成 2 点（会被 <3 拦掉）',
    dedupePoints([{ x: 0.2, y: 0.2 }, { x: 0.6, y: 0.6 }, { x: 0.2, y: 0.2 }]).length === 2)
  check('dedupe 空数组不炸', dedupePoints([]).length === 0)

  check('sanitize：非数组 -> []', sanitizePoints(undefined).length === 0)
  check('sanitize：字符串 x 被转成数字',
    sanitizePoints([{ x: '0.5', y: '0.25' }])[0].x === 0.5)
  check('sanitize：缺字段的点被丢弃',
    sanitizePoints([{ x: 0.1 }, { y: 0.2 }, { x: 0.3, y: 0.4 }]).length === 1)
  check('sanitize：越界值被夹回', sanitizePoints([{ x: -3, y: 9 }])[0].x === 0
    && sanitizePoints([{ x: -3, y: 9 }])[0].y === 1)
  check('sanitize：null 元素不炸', sanitizePoints([null, { x: 0.2, y: 0.2 }]).length === 1)
}

/* ============================================================
 * 7. 中心点（序号标签位置）
 * ============================================================ */
{
  const sq = [{ x: 0, y: 0 }, { x: 1, y: 0 }, { x: 1, y: 1 }, { x: 0, y: 1 }]
  const c = boxCenter(sq)
  check('正方形中心', near(c.x, 0.5) && near(c.y, 0.5))
  check('空数组给画面中心', boxCenter([]).x === 0.5 && boxCenter([]).y === 0.5)
  // 三角形重心（算术平均，不是几何重心，标签位置够用就行）
  check('三角形中心', near(boxCenter([{ x: 0, y: 0 }, { x: 1, y: 0 }, { x: 0, y: 1 }]).x, 1 / 3))
}

/* ============================================================
 * 8. 拖矩形的端点：必须还是矩形（不能拖成梯形）
 *
 * 用户画的时候选的是"矩形"，拖完却不是矩形，属于最让人困惑的那类
 * "我明明没做错什么"。这里按四个角逐个锁。
 * ============================================================ */
{
  /** 轴对齐 + 顶点顺序为 左上→右上→右下→左下 */
  const axisAligned = (p) => p.length === 4
    && near(p[0].y, p[1].y) && near(p[1].x, p[2].x)
    && near(p[2].y, p[3].y) && near(p[3].x, p[0].x)

  const sq = rectPoints({ x: 0.2, y: 0.2 }, { x: 0.6, y: 0.8 })
  // sq: 左上(0.2,0.2) 右上(0.6,0.2) 右下(0.6,0.8) 左下(0.2,0.8)

  /* 拖左上角：左上角过去，右下角钉死 */
  const a = moveRectVertex(sq, 0, { x: 0.05, y: 0.05 })
  check('拖左上角仍是矩形', axisAligned(a), JSON.stringify(a))
  check('拖左上角：右下角不动', near(a[2].x, 0.6) && near(a[2].y, 0.8), JSON.stringify(a[2]))
  check('拖左上角：新左上角跟随', near(a[0].x, 0.05) && near(a[0].y, 0.05))
  // 关键是"两条边一起动"：右上角跟着变 x 但保持 y = 上边
  check('拖左上角：上边整体移动', near(a[1].x, 0.6) && near(a[1].y, 0.05))
  check('拖左上角：左边整体移动', near(a[3].x, 0.05) && near(a[3].y, 0.8))

  /* 其余三个角同理 */
  const b = moveRectVertex(sq, 1, { x: 0.9, y: 0.1 })
  check('拖右上角仍是矩形', axisAligned(b), JSON.stringify(b))
  check('拖右上角：左下角不动', near(b[3].x, 0.2) && near(b[3].y, 0.8))
  check('拖右上角：右边到新 x', near(b[1].x, 0.9) && near(b[2].x, 0.9))
  check('拖右上角：上边到新 y', near(b[0].y, 0.1) && near(b[1].y, 0.1))

  const c = moveRectVertex(sq, 2, { x: 0.7, y: 0.9 })
  check('拖右下角仍是矩形', axisAligned(c))
  check('拖右下角：左上角不动', near(c[0].x, 0.2) && near(c[0].y, 0.2))

  const d = moveRectVertex(sq, 3, { x: 0.1, y: 0.95 })
  check('拖左下角仍是矩形', axisAligned(d))
  check('拖左下角：右上角不动', near(d[1].x, 0.6) && near(d[1].y, 0.2))

  /* 拖过对角会翻转 —— 和常见画图软件一致，不算错，但形状必须还是矩形 */
  const flip = moveRectVertex(sq, 0, { x: 0.9, y: 0.95 })
  check('拖过对角翻转后仍是矩形', axisAligned(flip), JSON.stringify(flip))
  check('翻转后顶点顺序仍固定', flip[0].x <= flip[1].x && flip[0].y <= flip[3].y)

  /* 面积必须真的变了（证明不是原样返回） */
  check('拖角确实改变了框', !near(polygonArea(a), polygonArea(sq)))

  /* 越界要夹住 */
  const out = moveRectVertex(sq, 0, { x: -5, y: -5 })
  check('拖角越界被夹回 0', out.every((p) => p.x >= 0 && p.y >= 0))
  check('拖角越界后仍是矩形', axisAligned(out))

  /* 顶点顺序被手改乱时，按"落在哪一侧"判断归属，照样对。
   * 注意：rectPoints 会把 bbox 归整成 左上→右上→右下→左下，
   * 所以拖完之后**下标不再对应原来那个角**，断言只能打在 bbox 上。 */
  const bboxOf = (p) => ({
    x0: Math.min(...p.map((q) => q.x)), x1: Math.max(...p.map((q) => q.x)),
    y0: Math.min(...p.map((q) => q.y)), y1: Math.max(...p.map((q) => q.y)),
  })
  const sameBox = (p, x0, y0, x1, y1) => {
    const b = bboxOf(p)
    return near(b.x0, x0) && near(b.y0, y0) && near(b.x1, x1) && near(b.y1, y1)
  }

  const messy = [sq[2], sq[0], sq[3], sq[1]]   // 故意打乱：第 0 个其实是右下角
  // 往右下拖（没过对角）：右下角跟着走，对角 (0.2,0.2) 钉死
  const m1 = moveRectVertex(messy, 0, { x: 0.9, y: 0.9 })
  check('顶点顺序打乱也认得角', axisAligned(m1) && sameBox(m1, 0.2, 0.2, 0.9, 0.9),
    JSON.stringify(m1))
  // 往左上拖过对角：翻转成 (0,0)-(0.2,0.2)，被拖的那个点变成新的左上角
  const m2 = moveRectVertex(messy, 0, { x: 0.0, y: 0.0 })
  check('打乱后拖过对角照样是矩形', axisAligned(m2), JSON.stringify(m2))
  check('打乱后拖过对角：对角不动', sameBox(m2, 0.0, 0.0, 0.2, 0.2), JSON.stringify(m2))

  /* 不是 4 点就无所谓"保持矩形"，退化成普通拖拽（多边形不该被它改成矩形） */
  const tri = [{ x: 0.2, y: 0.2 }, { x: 0.8, y: 0.3 }, { x: 0.5, y: 0.9 }]
  const t = moveRectVertex(tri, 1, { x: 0.9, y: 0.4 })
  check('3 点退化成单点拖拽', near(t[1].x, 0.9) && near(t[1].y, 0.4))
  check('3 点拖拽不影响其它点', near(t[0].x, 0.2) && near(t[2].y, 0.9))
}

/* ============================================================
 * 9. 组件里的两条产品约定（源码级，防止手一抖改回去）
 *
 * 这类"画完一个框该不该退出工具"的行为没有 DOM 可测，只能锁源码：
 *  - 画完矩形/多边形后**留在原工具**，好接着画下一个；
 *  - 只有 Esc / 取消 才回"选择"；
 *  - 拖顶点时矩形走 moveRectVertex（保形），多边形走自由单点；
 *  - **关菜单的监听必须放过菜单内部点击**（否则菜单项 onClick 永不触发）。
 * ============================================================ */
{
  const srcPath = join(root, 'src', 'components', 'DetectBoxTool.tsx')
  check('找得到组件源码', existsSync(srcPath))
  const src = readFileSync(srcPath, 'utf8')

  // onUp 里 drawRect 那一段（到下一个注释块为止）
  const from = src.indexOf("if (d.mode === 'drawRect') {")
  // 锚点用 `const zoomPct`（紧跟在 selBox 后面）：`const selBox` 在 onMove 里还有一个同名的。
  // （原来锚的是 `const pickBox`，算法窗口改成跟着选中框走之后那行没了）
  const to = src.indexOf('const zoomPct')
  check('截得到 drawRect 收尾分支', from > 0 && to > from)
  const seg = src.slice(from, to)

  check('画完矩形不把人踢回选择工具', !/cancel\s*\(/.test(seg), seg.slice(0, 120))
  const resets = (seg.match(/resetDrawing\(\)/g) || []).length
  check('矩形三条出口都只清草稿、不换工具', resets === 3, `${resets} 处 resetDrawing`)

  // 多边形收尾同样只清草稿
  const poly = src.slice(src.indexOf('const finishPolygon'), src.indexOf('useEffect', src.indexOf('const finishPolygon')))
  check('画完多边形也留在原工具', !/setTool\(/.test(poly) && /resetDrawing\(\)/.test(poly), poly.slice(-120))

  // 只有 Esc / 取消 才回选择
  check('取消 = 清草稿 + 回到选择', /resetDrawing\(\);\s*setTool\('select'\)/.test(src))
  check('Esc 才退出绘制', /Escape[\s\S]{0,160}cancel\(\)/.test(src))

  // 拖顶点：矩形保形，多边形自由
  check('矩形顶点走 moveRectVertex', /d\.shape === 'rect'\s*\?\s*moveRectVertex/.test(src))
  check('多边形顶点仍是自由单点', /\?\s*d\.orig\.map\(\(p, i\) => \(i === d\.vertex \? now : p\)\)/.test(src)
    || /d\.orig\.map\(\(p, i\) => \(i === d\.vertex/.test(src))

  // 提示文案要告诉用户可以接着画
  check('提示里说了可以接着画', /接着画下一个|继续画下一个|下一个/.test(src))

  /* ---- 右键菜单：关菜单的监听必须放过菜单内部的点击 ----
   * 实测 bug：window 上无差别的 mousedown -> setMenu(null)，菜单在按下那一刻就被卸载，
   * 浏览器凑不齐 click 的 down/up 配对 -> 菜单项 onClick 永不触发，表现为
   * "菜单弹得出来，点删除没反应"。轨道地图踩过一次，这里是同一个坑。 */
  const d1 = src.indexOf('/* ---- 菜单开着时')
  const d2 = src.indexOf('/* ---- 绘制', d1)
  check('截得到关菜单那段', d1 > 0 && d2 > d1)
  const dis = src.slice(d1, d2)

  check('关菜单监听放过菜单内部点击', /\.closest\('\.dbx-ctx'\)/.test(dis), dis.slice(0, 160))
  const mds = [...dis.matchAll(/addEventListener\('mousedown',[^)]*\)/g)].map((m) => m[0])
  check('关菜单的 mousedown 走捕获阶段', mds.length > 0 && mds.every((s) => /,\s*true\)$/.test(s)),
    mds.join(' | '))
  const rms = [...dis.matchAll(/removeEventListener\('mousedown',[^)]*\)/g)]
  check('mousedown 监听有对称卸载', rms.length === mds.length, `${mds.length} 挂 / ${rms.length} 卸`)
  // 匿名函数 remove 不掉，会漏监听（blur 那行当年就差写成匿名）
  check('卸载的都是具名函数', !/removeEventListener\(\s*'[a-z]+',\s*\(\)\s*=>/.test(dis))

  check('菜单里右键不弹浏览器菜单',
    /className="dbx-ctx"[\s\S]{0,220}onContextMenu=\{\(e\) => e\.preventDefault\(\)\}/.test(src))

  /* ---- 工具条只占一行：工具按钮与缩放按钮必须在同一段里 ----
   * 检视器这一栏很窄，缩放单独起一行会把画布往下挤（用户明确要求合并）。 */
  const headCount = (src.match(/className="dbx-head"/g) || []).length
  check('工具条只有一行', headCount === 1, `${headCount} 行 dbx-head`)
  const headSeg = src.slice(src.indexOf('className="dbx-head"'), src.indexOf('<div ref={wrapRef}'))
  check('工具按钮在这一行里', /startTool\('select'\)/.test(headSeg))
  check('缩放按钮也在这一行里', /onClick={fitNow}/.test(headSeg) && /zoomBtn\(true\)/.test(headSeg))
  check('缩放百分比也在这一行里', /\{zoomPct\}/.test(headSeg))
  // 「绑定测点」也归到这一行（原来单独挂在下面选中信息那一行）
  check('绑定测点按钮在同一行工具条里', /\n\s*绑定测点\s*\n/.test(headSeg))
  check('没框时绑定测点禁用', /onClick=\{openBindPoint\} disabled=\{!boxes\.length\}/.test(src))
  check('窗口开着时按钮变实心', /theme=\{bindOpen \? 'solid' : 'light'\}/.test(src))
  const selSeg = src.slice(src.indexOf('className="dbx-sel"'), src.indexOf('{!imageSrc ?'))
  check('截得到选中信息那段', selSeg.length > 80, `${selSeg.length}`)
  check('选中信息那行不再放按钮', !/绑定测点/.test(selSeg) && !/<Button/.test(selSeg))

  /* ---- 非模态窗口开着时，外面的框可能被删掉 ----
   * 目标必须**唯一确定**：不能 `|| boxes[0]` 兜底，否则标题显示的和真绑上的
   * 不是同一个框（用户以为在给 #3 绑，其实写进了 #1）。没了就关掉窗口。 */
  check('选中框没了会自动关窗口',
    /if \(bindOpen && !boxes\.some\(\(b\) => b\.path === selPath\)\) setBindOpen\(false\)/.test(src))
  check('窗口只认 selBox（没有 boxes[0] 兜底）',
    /\{bindOpen && selBox \? \(/.test(src)
    && !/BindPointModal[\s\S]{0,320}\|\| boxes\[0\]/.test(src))

  /* ---- 绑定测点：按钮 + 弹窗 + "已绑"要看得出来 ---- */
  // JSX 里按钮文字是单独一行（带缩进），别按 `>文字<` 去匹配
  check('有「绑定测点」按钮', /\n\s*绑定测点\s*\n/.test(src))
  check('绑定走 BindPointModal', /<BindPointModal/.test(src))
  check('切下一个走 nextBox（不自己算下标）', /nextBox\(boxes,/.test(src))
  check('绑测点回调存在', /onBindPoint/.test(src))
  // 测点 id / 名字是**一起写**的镜像，只写 id 会让列表为了显示名字再查一次档案。
  // 这段在页面里（DetectBoxTool 只拿到回调），所以去看 WaypointTreePrefab。
  const pageSrc = readFileSync(join(root, 'src', 'views', 'WaypointTreePrefab.tsx'), 'utf8')
  check('绑定时 id 与 name 一起写',
    /point_id: pointId,\s*point_name: pointName/.test(pageSrc))
  // 换节点必须整个重挂：框是按路径认的，路径在不同节点下是同一套，
  // 而绑定窗口是非模态的（开着时还能去点树），不重挂就会绑到别的节点的框上
  check('切换节点会重挂检测框工具', /<DetectBoxTool\s*\n\s*key=\{selectedPath/.test(pageSrc))
  check('已绑测点的框用成功色标出来', /is-bound/.test(src))
  const cssText = readFileSync(join(root, 'src', 'styles.css'), 'utf8')
  check('CSS 里有已绑测点的样式', /\.bp-row\.is-bound/.test(cssText) && /\.dbx-pts\.is-bound/.test(cssText))

  /* ---- 非模态窗口外壳（components/ModelessWindow.tsx） ----
   * Semi 的 Modal 没有 modeless，一显示就上遮罩 + 锁 body 滚动，而这两个窗口
   * （绑测点 / 选算法）开着的时候用户还得在**画布上点框、画框**，挡住就没法干活。
   * 外壳只有一份，两个窗口都套它——拖拽那三条硬规矩不能写两遍。
   * 这几条锁的是"别有人图省事又给改回 <Modal>"。 */
  const bpSrc = readFileSync(join(root, 'src', 'components', 'BindPointModal.tsx'), 'utf8')
  const mwSrc = readFileSync(join(root, 'src', 'components', 'ModelessWindow.tsx'), 'utf8')
  check('绑定测点窗口不用 Modal（非模态）', !/<Modal\b/.test(bpSrc))
  check('窗口挂到 body 的 portal 上', /createPortal\(/.test(mwSrc) && /document\.body/.test(mwSrc))
  check('绑定测点窗口套 ModelessWindow 外壳', /<ModelessWindow/.test(bpSrc))
  check('CSS 里窗口是 fixed 定位', /\.mw \{[\s\S]{0,160}position: fixed/.test(cssText))
  check('只有标题栏能拖', /className="mw-head"[\s\S]{0,120}onMouseDown=\{onHeadDown\}/.test(mwSrc))
  check('标题栏上点关闭按钮不算拖', /onHeadDown[\s\S]{0,400}closest\('button'\)/.test(mwSrc))
  // 位置数学（夹视口 / 绝对位移）在 utils/windowDrag.ts 里，数值回归见
  // verify-window-drag.mjs；这里只锁"组件确实走它、没有自己再写一遍算术"
  check('拖动位移走 dragTo', /setPos\(dragTo\(/.test(mwSrc))
  check('dragTo 拿到的是按下那一刻的快照 base',
    /dragTo\(\s*\n?\s*\{ x: d\.ox, y: d\.oy \}/.test(mwSrc))
  check('组件里没有自己重写一遍位移算术', !/d\.ox \+ \(e\.clientX/.test(mwSrc))
  check('拖完不关窗口（onHeadDown 里没有 onClose）',
    !/const onHeadDown[\s\S]{0,500}?onClose/.test(mwSrc))
  check('位置夹在视口内（拖不丢）', /clampPos\(p\.x, p\.y, vpOf\(\)\)/.test(mwSrc)
    && /window\.innerWidth/.test(mwSrc))
  check('双击标题栏复位', /onDoubleClick=\{\(\) => setPos\(defaultPos\(vpOf\(\)\)\)\}/.test(mwSrc))
  // 不吃 Esc：Esc 是画布的"放弃绘制"，被窗口抢走就没法取消画到一半的框了
  check('非模态窗口不吃 Esc', !/Escape/.test(mwSrc) && !/closeOnEsc/.test(mwSrc))

  /* ---- 两个"能跑但不对"的写法，锁住别退回去 ---- */
  // 加载的取消函数必须交回 effect，否则 alive 守卫是死的（加载途中切走节点照样 setState）
  check('加载的取消函数交给了 effect', /if \(visible\) return loadDirs\(\)/.test(bpSrc))
  // 副作用不能写在 setState 的 updater 里：StrictMode 下 updater 跑两遍 = 请求发两次。
  // 截取整个 toggle 函数来看（正则跨不出"updater 结束"这个边界）
  const toggleSeg = bpSrc.slice(bpSrc.indexOf('const toggle'), bpSrc.indexOf('const menuFor'))
  check('截得到 toggle 整段', toggleSeg.length > 80, `${toggleSeg.length}`)
  // 找**调用**（注释里也会提到 ensurePoints，indexOf 会先撞上注释）
  check('ensurePoints 不在 updater 里',
    toggleSeg.indexOf('ensurePoints([') > toggleSeg.indexOf('return next'),
    `updater 结束于 ${toggleSeg.indexOf('return next')}，调用在 ${toggleSeg.indexOf('ensurePoints([')}`)
  check('展开后才去拉测点', /if \(opening\) ensurePoints\(\[d\.id\]\)/.test(bpSrc))
  /* ---- 右键菜单：必须受控，否则点完不关 ----
   * Semi 的"点一项就收起"只对 Dropdown.Menu/Item 生效，自定义 render（纯 div）
   * 点了不会关（用户报的 bug）。所以 visible 受控 + 每个菜单项自己 setCtxRow(null)。 */
  check('右键菜单是受控的', /visible=\{ctxRow === row\.key\}/.test(bpSrc)
    && /onVisibleChange=\{\(v\) => setCtxRow\(v \? row\.key : null\)\}/.test(bpSrc))
  const menuSeg = bpSrc.slice(bpSrc.indexOf('const menuFor'), bpSrc.indexOf('if (!visible) return null'))
  const items = (menuSeg.match(/bp-ctx-item/g) || []).length
  const closes = (menuSeg.match(/setCtxRow\(null\)/g) || []).length
  // 被别处占住的测点那一项是 **disabled**（"已绑在 xxx"，点了没反应就别做成能点的），
  // 它没有 onClick，自然也不关菜单 —— 只对"可点的项"数配平。
  const deadItems = (menuSeg.match(/bp-ctx-item"\s+disabled/g) || []).length
  check('每个可点菜单项都会关菜单',
    items > 0 && closes === items - deadItems, `${items} 项 / ${closes} 次关闭 / ${deadItems} 项禁用`)

  /* ---- 列表行：算法按钮按内容宽度 + 能就地解绑测点 ---- */
  // 注意别用 `[^}]*width: 100%` 去匹配：会撞上 `max-width: 100%`（这条是要保留的）。
  // 取规则体再按行判。
  const algoRule = (() => {
    const at = cssText.indexOf('.dbx-algo .semi-button {')
    if (at < 0) return ''
    return cssText.slice(at, cssText.indexOf('}', at))
  })()
  check('截得到算法按钮的样式规则', algoRule.length > 20, `${algoRule.length}`)
  check('算法按钮不再撑满整列', !/style=\{\{ width: '100%' \}\}/.test(src)
    && !/^\s*width: 100%/m.test(algoRule))
  check('算法按钮可伸缩但有上限', /\.dbx-algo \{[^}]*flex: 0 1 auto/.test(cssText)
    && /\.dbx-algo \{[^}]*max-width/.test(cssText))
  // 省略号打在内层 span 上：Semi Button 把 children 包在 <span> 里，
  // 写在按钮上只会把长算法名硬裁掉
  check('长算法名是省略而不是硬裁', /\.dbx-algo \.semi-button > span \{[^}]*text-overflow: ellipsis/.test(cssText))
  /* 取消绑定按钮要**挨着测点名**（用户原话："取消绑定按钮和要测点名称靠近啊"）。
     旧写法把 margin-left:auto 打在名字上：名字被推到最右，按钮留在算法按钮旁边，
     两边隔一大片空白，看不出这个按钮解的是哪个测点。
     现在整组（名字 + 按钮）一起靠右，auto 打在组上。 */
  const ptRule = (() => {
    const at = cssText.indexOf('.dbx-pt {')
    if (at < 0) return ''
    return cssText.slice(at, cssText.indexOf('}', at))
  })()
  check('测点名+解绑是一组', /\.dbx-pt \{[^}]*display: inline-flex/.test(cssText))
  check('整组靠右撑开', /\.dbx-pt \{[^}]*margin-left: auto/.test(ptRule))
  // 名字上不能再有 auto：两个 auto 会把名和按钮分到两头（正是这次要修的样子）
  const ptsRule = (() => {
    const at = cssText.indexOf('.dbx-pts {')
    if (at < 0) return ''
    return cssText.slice(at, cssText.indexOf('}', at))
  })()
  check('测点名自身不再 auto 推开', ptsRule.length > 20 && !/margin-left: auto/.test(ptsRule))
  // 窗口取 1200：组内还夹着两段 Tooltip 和"为什么不带图标"的注释（实测按钮在 +894 处）
  const grpAt = src.indexOf('<span className="dbx-pt">')
  const grp = grpAt < 0 ? '' : src.slice(grpAt, grpAt + 1200)
  check('解绑按钮和测点名在同一个组里', grp.includes('dbx-pts') && grp.includes('onUnbindPoint(b.path)'))
  check('按钮紧跟在测点名后面', grp.indexOf('dbx-pts') > 0
    && grp.indexOf('dbx-pts') < grp.indexOf('onUnbindPoint(b.path)'))
  // 解绑：列表里有按钮、页面里有回调、且**两个字段一起清**
  check('列表项有取消绑定按钮', /onUnbindPoint\(b\.path\)/.test(src)
    && /\n\s*取消绑定\s*\n/.test(src))
  // 窗口给宽一点：中间还夹着"为什么不带图标"的注释
  check('解绑只在绑了之后出现', /\{b\.pointId \? \([\s\S]{0,900}onUnbindPoint\(b\.path\)/.test(src))
  // 只看按钮**前面**那一段有没有 icon=（别去全文件搜 IconLink：注释里就写着它）
  const unbindAt = src.indexOf('onUnbindPoint(b.path)')
  const beforeBtn = src.slice(Math.max(0, unbindAt - 260), unbindAt)
  check('解绑按钮不带图标（图标语义会反）', unbindAt > 0 && !/icon=\{/.test(beforeBtn))
  check('页面传了解绑回调', /onUnbindPoint=\{unbindBoxPoint\}/.test(pageSrc))
  check('解绑把 id 与 name 一起清',
    /patchNodeProps\(path, \{ point_id: '', point_name: '' \}\)/.test(pageSrc))

  /* ---- 绑定测点窗口里也要能解绑（用户选的下一步） ----
   * 已绑在本框的测点：行内第一个按钮变成「取消绑定」，右键菜单给「取消绑定本框」。
   * 解绑后**窗口不关**——绑错了要能立刻改绑另一个测点。 */
  check('窗口里能解绑（行内按钮按本框状态切换）', /\{mine \? \([\s\S]{0,300}onUnbind\(\)/.test(bpSrc))
  check('右键菜单里有取消绑定本框', /取消绑定本框/.test(bpSrc)
    && /\{mine \? \([\s\S]{0,300}onUnbind\(\)/.test(menuSeg))
  check('窗口收到 onUnbind 回调', /onUnbind=\{doUnbindPoint\}/.test(src))
  const unbindFn = src.slice(src.indexOf('const doUnbindPoint'), src.indexOf('const doBindPoint'))
  check('解绑只清当前框', /onUnbindPoint\(selBox\.path\)/.test(unbindFn))
  check('解绑后窗口不关（好让人立刻改绑）', !/setBindOpen\(false\)/.test(unbindFn))

  /* ---- 本轮三件事：① 绑定后不关窗口 ② 一个测点只能绑一处 ③ 绑在哪要看得见 ----
   * ②③ 都靠一张**整棵树**的占用表（测点 id -> "航点 / 动作点 / 检测框 #n"）：
   * 检测框工具只看得到当前动作点，判断不了"这测点是不是早被别处用了"，
   * 所以表必须由页面（有整棵 spec）算好往下传。 */
  const bindAt = src.indexOf('const doBindPoint')
  const bindEnd = src.indexOf('\n  return (', bindAt)
  const bindFn = bindAt < 0 || bindEnd < 0 ? '' : src.slice(bindAt, bindEnd)
  check('截得到 doBindPoint', bindFn.length > 100, `${bindFn.length}`)
  // 之前是 `if (!advance) { setBindOpen(false); return }`：绑一个就得重开一次窗口
  check('绑定后不关窗口', !/setBindOpen\(false\)/.test(bindFn))
  check('绑定后仍然会切下一个框', /nextBox\(boxes, target\.path\)/.test(bindFn))
  check('重复绑定被挡住', /pointUsage\[pointId\]/.test(bindFn) && /Toast\.warning/.test(bindFn))
  check('挡在写入之前（先查后写）',
    bindFn.indexOf('pointUsage[pointId]') < bindFn.indexOf('onBindPoint(target.path'))
  check('本框重绑自己不算重复', /pointId !== target\.pointId/.test(bindFn))
  check('页面算整棵树的占用表',
    /const pointUsage = useMemo\(\(\) => collectPointUsage\(spec\), \[spec\]\)/.test(pageSrc))
  check('占用表传进工具', /pointUsage=\{pointUsage\}/.test(pageSrc))
  check('工具把占用表转给窗口', /pointUsage=\{pointUsage\}/.test(src))
  check('窗口收占用表', /pointUsage = \{\}/.test(bpSrc)
    && /pointUsage\?: Record<string, string>/.test(bpSrc))
  check('行样式把"别处占住"也算已绑',
    /boundPointIds\.has\(row\.id\) \|\| Boolean\(used\)/.test(bpSrc))
  check('占用路径显示出来', /bp-path/.test(bpSrc) && /\.bp-path \{/.test(cssText))
  check('长路径不撑破行', /\.bp-path \{[^}]*text-overflow: ellipsis/.test(cssText))
  check('"别处占住"和"本框已绑"颜色分开', /\.bp-row\.is-taken/.test(cssText))
  check('禁用的菜单项不响应 hover', /bp-ctx-item:hover:not\(\[disabled\]\)/.test(cssText))
  const actAt = bpSrc.indexOf('<span className="bp-actions">')
  const actSeg = actAt < 0 ? '' : bpSrc.slice(actAt, actAt + 1400)
  check('截得到行内动作区', actSeg.length > 100, `${actSeg.length}`)
  check('本框已绑优先于被占住', actSeg.indexOf('mine ? (') >= 0
    && actSeg.indexOf('mine ? (') < actSeg.indexOf('taken ? ('))
  // 绑定按钮必须落在"没被占住"的那一支里，不能无条件渲染
  check('被占住时不给绑定按钮', actSeg.indexOf('taken ? (') >= 0
    && actSeg.indexOf('onBind(row.id') > actSeg.indexOf('taken ? ('))

  /* ---- 航点树里，绑了测点的检测框是绿的 ----
   * 颜色只认 point_id（point_name 只是给人看的镜像，清了 id 却留着名字会误判） */
  check('树节点按 point_id 判绿', /pointBound = typeName === 'DetectBoxNode' && Boolean\(props\.point_id\)/.test(pageSrc))
  check('绑了测点类型标签变绿', /color=\{pointBound \? 'green'/.test(pageSrc))
  check('绑了测点整行文字也变绿', /color: pointBound \? 'var\(--semi-color-success\)'/.test(pageSrc))

  /* ---- 测点信息确实挂在**检测框节点**上（用户要确认的那条） ----
   * 直接读后端源码：point_id / point_name 必须落在 class DetectBoxNode 的字段区里，
   * 而不是别处（MeasurePointNode 也有个 point_id，别认错人） */
  const nodesSrc = readFileSync(
    join(root, '..', 'backend', 'app', 'prefab', 'nodes', 'waypoint.py'), 'utf8')
  const clsAt = nodesSrc.indexOf('class DetectBoxNode')
  const nextCls = nodesSrc.indexOf('\nclass ', clsAt + 1)
  const boxSeg = nodesSrc.slice(clsAt, nextCls > 0 ? nextCls : undefined)
  check('截得到 DetectBoxNode 定义', clsAt > 0 && boxSeg.length > 200, `${boxSeg.length}`)
  check('point_id / point_name 是检测框自己的字段',
    /point_id: str = ui_field/.test(boxSeg) && /point_name: str = ui_field/.test(boxSeg))

  const dragKeys = ['mousemove', 'mouseup']
  check('拖拽监听成对挂卸',
    dragKeys.every((k) => new RegExp(`addEventListener\\('${k}'`).test(mwSrc)
      && new RegExp(`removeEventListener\\('${k}'`).test(mwSrc)))
  check('窗口有关闭按钮', /IconClose/.test(mwSrc) && /onClick=\{onClose\}/.test(mwSrc))

  /* ---- 右下角手柄：拖它改窗口大小（两个窗口都套外壳，所以两个都有） ----
   * 跟拖拽同一套规矩：只在**手柄**上按下才算缩放（整块窗口都能拖的话，
   * 点树行/按钮会变成"抖一下就当成缩放"）；尺寸**绝对计算**（起点尺寸 + 总位移），
   * 不逐帧累加；上界跟着窗口当前位置走，被拖到右下角时上下界会交叉，得兜底。 */
  const wdSrc = readFileSync(join(root, 'src', 'utils', 'windowDrag.ts'), 'utf8')
  // ⚠️ 只截到根节点自己的 `>` 为止：多截一点就会把标题栏的 onMouseDown 也算进来，
  //    "只有手柄能缩放"这条就变成空断言了
  const rootTag = (mwSrc.match(/className=\{`mw\$\{dragging[\s\S]*?\n\s*>/) || [''])[0]
  check('截得到窗口根节点', rootTag.length > 80, `${rootTag.length}`)
  check('宽高由 size 状态给（不再只给 width）',
    /style=\{\{ left: pos\.x, top: pos\.y, width: size\.w, height: size\.h \}\}/.test(mwSrc))
  check('右下角有缩放手柄', /className="mw-grip"/.test(mwSrc))
  check('只有手柄能缩放（根节点自己不接 onMouseDown）', !/onMouseDown/.test(rootTag), rootTag)
  check('手柄按下才记快照', /onMouseDown=\{onResizeDown\}/.test(mwSrc))
  check('缩放位移走 resizeTo', /setSize\(resizeTo\(/.test(mwSrc))
  check('resizeTo 拿到的是按下那一刻的快照 base',
    /resizeTo\(\s*\n?\s*\{ w: d\.ow, h: d\.oh \}/.test(mwSrc))
  check('组件里没有自己重写一遍尺寸算术', !/d\.ow \+ \(e\.clientX/.test(mwSrc))
  check('缩放中加 is-resize（禁掉选中，不然拖一下就刷蓝一片）', /is-resize/.test(mwSrc))
  check('双击手柄复位尺寸', /setSize\(defaultSize\(vpOf\(\), pos\)\)/.test(mwSrc))
  check('位置变了要重夹尺寸（不然拖到右下角会越界）',
    /setSize\(\(s\) => clampSize\(s\.w, s\.h, pos, vpOf\(\)\)\)/.test(mwSrc))
  check('视口变化也要重夹尺寸',
    /setSize\(\(s\) => clampSize\(s\.w, s\.h, clampPos\(pos\.x, pos\.y, vp\), vp\)\)/.test(mwSrc))
  check('缩放监听成对挂卸（拖和缩放各一套）',
    (mwSrc.match(/addEventListener\('mousemove'/g) || []).length === 2
    && (mwSrc.match(/removeEventListener\('mousemove'/g) || []).length === 2,
    `${(mwSrc.match(/addEventListener\('mousemove'/g) || []).length} 套`)
  // 尺寸数学只在纯函数里，别在组件里再写一遍（数值回归见 verify-window-drag.mjs）
  check('尺寸数学在 windowDrag.ts 里，组件不自己算',
    /export function clampSize/.test(wdSrc) && /export function resizeTo/.test(wdSrc)
    && !/function clampSize/.test(mwSrc))
  check('CSS 里手柄钉在右下角', /\.mw-grip \{[\s\S]{0,220}position: absolute/.test(cssText)
    && /\.mw-grip \{[\s\S]{0,220}right: 0/.test(cssText)
    && /\.mw-grip \{[\s\S]{0,220}bottom: 0/.test(cssText))
  check('CSS 里手柄是 nwse 光标', /\.mw-grip \{[\s\S]{0,260}cursor: nwse-resize/.test(cssText))
  /* ⚠️ 判"CSS 里没有某属性"时必须先剥注释：旁边特意写了"别再写 max-height"的说明，
     全量搜必然撞上（源码级断言的老坑）。 */
  const cssCode = cssText.replace(/\/\*[\s\S]*?\*\//g, '')
  // 宽高既然由 JS 给，CSS 里就别再写 max-height：两边都夹会互相打架把内容挤掉几像素
  check('CSS 里窗口不再写死 max-height', !/\.mw \{[\s\S]{0,320}max-height/.test(cssCode))
  // 窗口拉高了树要跟着长，写死 300px 等于"白拉"
  check('测点树跟着窗口长', /\.bp-tree \{[\s\S]{0,200}flex: 1 1 auto/.test(cssCode)
    && !/\.bp-tree \{[\s\S]{0,200}max-height/.test(cssCode))
  // 手柄压在右下角，底栏按钮紧贴右边的话会被它盖住一角（点"关闭"变成开始缩放）
  check('底栏右边给手柄留出空位（> 16px）',
    /\.mw-foot \{[\s\S]{0,220}padding: 8px 20px 8px 12px/.test(cssCode))

  /* ---- 检测框直接选「检测算法流程」（= 算法 + 参数的检测管线）----
   * 旧模型在框下挂 AlgorithmConfigNode 选单个算法已下线：现在框列表每一行都有一个
   * 检测流程下拉，引用 id（流程的 detect_id，留空用文件名）直接写进框的 detect_flow，
   * 不再有算法弹窗 / 子节点。 */
  const listSeg = src.slice(src.indexOf('boxes.length === 0'), src.indexOf('dbx-sel'))
  check('截得到框列表那段', listSeg.length > 100, `${listSeg.length}`)
  check('框列表每行有检测流程下拉',
    /<Select/.test(listSeg) && /optionList=\{flowOpts\}/.test(listSeg)
    && /onSetDetectFlow\(b\.path/.test(listSeg))
  check('流程下拉含"未指定流程"空项', /label: '未指定流程'/.test(listSeg))
  check('引用的流程已删除时补失效项', /（流程已不存在）/.test(listSeg))

  /* ---- 旧的"选算法弹窗 / 挂算法子节点"链路必须彻底移除 ---- */
  check('框数据不再带 algorithm / hasConfig / algoOf',
    !/b\.algorithm|hasConfig|algoOf/.test(src))
  check('不再挂算法配置弹窗、不建算法子节点',
    !/AlgorithmConfigModal|setPickOpen|onBindAlgorithm|onUnbindAlgorithm|onEditConfig|doPickAlgorithm/.test(src))
  check('工具条不再有"设置算法"按钮', !/设置算法/.test(src))
  check('框颜色按序号轮换（检测流程本身不带颜色）', /BOX_PALETTE/.test(src))
  // 选中框被删时，绑定测点的非模态窗口要跟着关，不能留个"开着"的招牌
  check('选中框没了绑定测点窗口关闭', /if \(bindOpen && !boxes\.some/.test(src))
  // 不许再另存一个"挑算法目标"（pickPath 那类老 bug）；剥掉注释再搜
  const codeOnly = src
    .replace(/\/\*[\s\S]*?\*\//g, '')
    .replace(/^\s*\/\/.*$/gm, '')
  check('不再有挑算法的独立目标 / 弹窗状态',
    !/pickPath|pickBox|pickOpen/.test(codeOnly), (codeOnly.match(/pick\w*/g) || []).join(','))

  /* ---- 页面（WaypointTreePrefab）：流程选项与引用 id ---- */
  check('页面把检测流程选项传给工具', /detectFlows=\{detectFlowChoices\}/.test(pageSrc))
  check('页面提供 onSetDetectFlow', /onSetDetectFlow=\{setBoxDetectFlow\}/.test(pageSrc))
  check('引用 id 优先取流程的 detect_id', pageSrc.includes('t.root?.detect_id'))
  check('引用 id 留空时回落文件名（flowRefKey）', pageSrc.includes('flowRefKey'))
  check('检视器数据源含 detectFlows（含未指定空项）',
    /detectFlows: \[\{ value: '', label: '未指定检测流程' \}/.test(pageSrc))
  check('废弃节点从添加目录过滤（hidden）', /if \(info\.hidden\) continue/.test(pageSrc))

  /* ---- 后端：检测框引用流程、算法配置节点废弃隐藏 ---- */
  const wpNodeSrc = readFileSync(
    join(root, '..', 'backend', 'app', 'prefab', 'nodes', 'waypoint.py'), 'utf8')
  check('detect_flow 是 select + optionsFrom=detectFlows',
    /detect_flow: str = ui_field\("select"[\s\S]{0,200}?optionsFrom="detectFlows"/.test(wpNodeSrc))
  check('旧 algorithm 字段改成只读',
    /algorithm: str = ui_field\("readonly"/.test(wpNodeSrc))
  check('AlgorithmConfigNode 标记隐藏',
    /class AlgorithmConfigNode[\s\S]{0,1600}?__hidden__: ClassVar\[bool\] = True/.test(wpNodeSrc))
  const regSrc = readFileSync(
    join(root, '..', 'backend', 'app', 'prefab', 'registry.py'), 'utf8')
  check('schema 条目透出 hidden', /"hidden": bool\(getattr\(cls, "__hidden__"/.test(regSrc))

  /* ---- 算法示意图的**后端**接口仍保留（算法目录维护能力，与检测框解耦）：
   * 原"选算法弹窗"随检测框改为引用检测流程而下线，但 data/algorithms.json 的示意图
   * 读写接口不删，将来可在独立的算法目录维护页重新接入。 */
  const pySrc = readFileSync(
    join(root, '..', 'backend', 'app', 'routers', 'waypoint_prefab.py'), 'utf8')
  check('目录 GET 一并返回 image', /"image": str\(a\.get\("image"\) or ""\)/.test(pySrc))
  check('后端有写示意图的接口', /@router\.post\("\/algorithms\/image"/.test(pySrc))
  check('写示意图要工程师权限', /\/algorithms\/image", dependencies=\[Depends\(engineer_only\)\]/.test(pySrc))
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.log('失败：')
  fails.forEach((f) => console.log('  ✗ ' + f))
  process.exit(1)
}
console.log('全部通过 ✓')
