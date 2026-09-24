/**
 * 算法示意图的压缩 / 校验回归（`src/utils/algoImage.ts`）。
 *
 * 与 verify-window-drag.mjs 同一套路：**不手抄源码**，用 tsc 把真实 .ts 编到
 * 临时目录再 import。
 * 运行：node scripts/verify-algo-image.mjs
 *
 * 这里锁的是"存进 algorithms.json 的那串 base64"该长什么样：
 * 只缩不放、长边夹住、只认能安全塞进 `<img src>` 的 data URL、超上限要拦住。
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'agi-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath,
    [tscEntry, 'src/utils/algoImage.ts', '--outDir', out,
      '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
      '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

const {
  IMAGE_MAX_SIDE, IMAGE_QUALITY, IMAGE_MAX_CHARS,
  fittedSize, isImageDataUrl, b64Bytes, acceptable,
} = await import(pathToFileURL(join(out, 'algoImage.js')).href)

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n}${extra ? ' — ' + extra : ''}`) }
const near = (a, b, eps = 1e-6) => Math.abs(a - b) <= eps
const same = (s, w, h, what) => check(what, near(s.w, w) && near(s.h, h), `得到 ${s.w}x${s.h} 期望 ${w}x${h}`)

/* ============================================================
 * 1. 缩放：长边夹到 320，短边等比
 * ============================================================ */
{
  same(fittedSize(1600, 1200), 320, 240, '横向大图：长边夹到 320')
  same(fittedSize(1200, 1600), 240, 320, '纵向大图：长边是 h')
  same(fittedSize(320, 240), 320, 240, '正好等于上限就不动')
  same(fittedSize(40, 30), 40, 30, '小图只缩不放（放大只会糊 + 白占体积）')
  same(fittedSize(1, 1), 1, 1, '极小图原样')
  // 宽高比要保住：压缩完的比例跟原图差不超过取整误差
  const s = fittedSize(1000, 333)
  // 容差只吃到取整误差（106.56 -> 107 是四舍五入，不是比例算错）
  check('保持宽高比', Math.abs(s.w / s.h - 1000 / 333) < 0.02, `${s.w}x${s.h}`)

  // 幂等：缩过一次再缩一次不变（重复上传同一张图不该越压越小）
  const once = fittedSize(1600, 1200)
  same(fittedSize(once.w, once.h), once.w, once.h, '缩放是幂等的')

  // 任意图缩完都不得超过上限，且两边都 >= 1（canvas 给 0 宽会直接不画）
  let ok = true
  for (const [w, h] of [[1, 1], [100, 100], [4000, 3000], [3000, 4000], [1920, 1080], [7, 9000]]) {
    const r = fittedSize(w, h)
    if (r.w > IMAGE_MAX_SIDE || r.h > IMAGE_MAX_SIDE || r.w < 1 || r.h < 1) ok = false
  }
  check('任意尺寸缩完都在 1..320 内', ok)

  // 退化输入：0 / 负数不能算出 NaN 或负数
  same(fittedSize(0, 100), 0, 0, '宽为 0 时判为无效图')
  same(fittedSize(-5, -5), 0, 0, '负数判为无效图')
  check('max 为 0 时也不出 NaN', fittedSize(100, 100, 0).w === 0)
}

/* ============================================================
 * 2. 格式白名单：能安全塞进 <img src> 的才收
 * ============================================================ */
{
  const good = [
    'data:image/png;base64,iVBORw0KGgo=',
    'data:image/jpeg;base64,/9j/4AAQSkZJRg==',
    'data:image/webp;base64,UklGRg==',
  ]
  for (const g of good) check(`收 ${g.slice(5, 16)}…`, isImageDataUrl(g))
  check('base64 段可以是空的（只有前缀）', isImageDataUrl('data:image/png;base64,' + 'A'.repeat(4)))

  // 危险的 / 不是图的：一律不收
  const bad = [
    'data:image/svg+xml;base64,PHN2Zz48',                 // svg 能带脚本，XSS 面
    'data:text/html;base64,PGgxPg==',
    'javascript:alert(1)',
    'data:image/png,QUJD',                                // 没有 ;base64,
    'http://x.com/a.png',                                 // 外链：文件要能离线读
    '/data/prefabs/a.png',                                // 相对路径：同上，不是 base64
    'data:image/png;base64,****',                         // 非法字符
    '',
  ]
  for (const b of bad) check(`拒 ${b.slice(0, 22) || '(空串)'}`, !isImageDataUrl(b), b)

  // 后端是同一套白名单（两处都得改，别只改前端）
  const pySrc = (await import('node:fs')).readFileSync(
    join(root, '..', 'backend', 'app', 'routers', 'waypoint_prefab.py'), 'utf8')
  check('后端 data URL 白名单同款（png/jpeg/jpg/webp/gif/bmp）',
    /_DATA_URL_RE = re\.compile\(\s*r"\^data:image\/\(png\|jpeg\|jpg\|webp\|gif\|bmp\);base64,/.test(pySrc))
  check('后端也拒 svg', !/svg/.test(pySrc.match(/_DATA_URL_RE = re\.compile\([^)]*\)/)?.[0] || 'svg'))
}

/* ============================================================
 * 3. 体积：能算得出压完多大，超上限要拦
 * ============================================================ */
{
  check('前缀不占解码后的体积', b64Bytes('data:image/jpeg;base64,AAAA') === 3,
    `${b64Bytes('data:image/jpeg;base64,AAAA')}`)
  check('1 个填充位少 1 字节', b64Bytes('data:image/png;base64,AAA=') === 2)
  check('2 个填充位少 2 字节', b64Bytes('data:image/png;base64,AA==') === 1)
  check('空串是 0 字节', b64Bytes('') === 0)

  const small = 'data:image/jpeg;base64,' + 'A'.repeat(1000)
  check('小图合规', acceptable(small))
  const huge = 'data:image/jpeg;base64,' + 'A'.repeat(IMAGE_MAX_CHARS + 10)
  check('超上限不合规', !acceptable(huge), `${huge.length} 字符`)
  const PREFIX = 'data:image/jpeg;base64,'
  check('正好等于上限合规', acceptable(PREFIX + 'A'.repeat(IMAGE_MAX_CHARS - PREFIX.length)))
  check('多一个字符就不合规', !acceptable(PREFIX + 'A'.repeat(IMAGE_MAX_CHARS - PREFIX.length + 1)))
  // 格式不对就不收，哪怕很小
  check('格式不对再小也不收', !acceptable('data:image/svg+xml;base64,AAAA'))
  // 空串走的是"删除"，不算"可以存一张图"
  check('空串不算一张可存的图（走删除接口）', !acceptable(''))

  // 压完一张 320x240 的 JPEG 大致就在几十 KB，离 512KB 上限有量级余量——
  // 这条不是精确断言，是防止有人把上限/质量改得离谱（比如质量 1.0 + 边长 2000）
  const rough = 320 * 240 * 3 * IMAGE_QUALITY / 8     // 未压缩 RGB 的粗估，实际 JPEG 更小
  check('上限相对一张缩略图有量级余量', IMAGE_MAX_CHARS > rough * 4, `${Math.round(rough)}B`)
}

/* ============================================================
 * 4. 常量口径（后端是同一个数，别悄悄改）
 * ============================================================ */
{
  check('最长边 320', IMAGE_MAX_SIDE === 320, `${IMAGE_MAX_SIDE}`)
  check('质量 0.85', IMAGE_QUALITY === 0.85, `${IMAGE_QUALITY}`)
  check('上限 512K 字符', IMAGE_MAX_CHARS === 512 * 1024, `${IMAGE_MAX_CHARS}`)
  const pySrc = (await import('node:fs')).readFileSync(
    join(root, '..', 'backend', 'app', 'routers', 'waypoint_prefab.py'), 'utf8')
  check('后端上限与前端同口径',
    /ALGO_IMAGE_MAX_CHARS = 512 \* 1024/.test(pySrc))
}

rmSync(out, { recursive: true, force: true })

console.log(`\n通过 ${pass} 项断言`)
if (fails.length) {
  console.error(`\n失败 ${fails.length} 项：`)
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
console.log('全部通过 ✓')
