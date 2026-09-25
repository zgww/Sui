/**
 * 把内置图标渲染成一张 HTML 预览页（临时文件），用来**用眼睛验收**。
 *
 * 图标是手写坐标画出来的，typecheck 和回归脚本只能保证"坐标合法"，
 * 保证不了"看着像不像一扇门"。所以每次增删图标都跑一下这个，人工过一遍。
 *
 * 用法：node scripts/preview-map-icons.mjs
 *   会打印生成的 html 路径（系统临时目录），内容 = 20 个图标 × 3 种大小 × 2 种颜色。
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, writeFileSync, existsSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'mi-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
execFileSync(process.execPath, [tscEntry,
  'src/components/mapIcons.ts', '--outDir', out,
  '--target', 'es2020', '--module', 'es2020', '--skipLibCheck', '--moduleResolution', 'bundler'],
  { cwd: root, stdio: 'pipe' })
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

const { ICONS, ICON_GRID } = await import(pathToFileURL(join(out, 'mapIcons.js')).href)

/** 把一组基本图形转成 SVG 片段（与 drawIcon 的画法一一对应） */
function svgOf(def, color) {
  const parts = def.shapes.map((sh) => {
    switch (sh.t) {
      case 'rect':
        return `<rect x="${sh.x}" y="${sh.y}" width="${sh.w}" height="${sh.h}" fill="${color}"/>`
      case 'circle':
        return `<circle cx="${sh.cx}" cy="${sh.cy}" r="${sh.r}" fill="${color}"/>`
      case 'poly':
        return `<polygon points="${sh.pts.map(([x, y]) => `${x},${y}`).join(' ')}" fill="${color}"/>`
      case 'ring':
        return `<circle cx="${sh.cx}" cy="${sh.cy}" r="${sh.r}" fill="none" stroke="${color}" stroke-width="${sh.w}"/>`
      case 'line':
        return `<line x1="${sh.x0}" y1="${sh.y0}" x2="${sh.x1}" y2="${sh.y1}" stroke="${color}" stroke-width="${sh.w}" stroke-linecap="round"/>`
      default:
        return ''
    }
  })
  return `<svg viewBox="0 0 ${ICON_GRID} ${ICON_GRID}" xmlns="http://www.w3.org/2000/svg">${parts.join('')}</svg>`
}

const SIZES = [16, 24, 40]
const COLORS = ['#0068FF', '#FF7D00']

const cards = ICONS.map((def) => {
  const rows = COLORS.map((c) => `
      <div class="row">
        ${SIZES.map((s) => `<div class="cell" title="${def.label} ${s}px"><div class="ico" style="width:${s}px;height:${s}px">${svgOf(def, c)}</div></div>`).join('')}
      </div>`).join('')
  return `<div class="card"><div class="name">${def.label}</div><div class="key">${def.key}</div>${rows}</div>`
}).join('')

const html = `<!DOCTYPE html><html lang="zh-CN"><head><meta charset="utf-8">
<title>地图内置图标预览（${ICONS.length} 个）</title>
<style>
  body { font: 13px/1.5 -apple-system, "PingFang SC", "Microsoft YaHei", sans-serif;
         margin: 24px; background: #fff; color: #1c1f23; }
  h1 { font-size: 16px; margin: 0 0 4px; }
  .hint { color: #6b7280; margin-bottom: 18px; }
  .grid { display: grid; grid-template-columns: repeat(auto-fill, minmax(150px, 1fr)); gap: 12px; }
  .card { border: 1px solid #e5e7eb; border-radius: 8px; padding: 10px; }
  .name { font-weight: 600; }
  .key { color: #9ca3af; font-size: 11px; margin-bottom: 8px; }
  .row { display: flex; align-items: center; gap: 10px; margin-top: 6px; }
  .cell { display: flex; align-items: center; justify-content: center;
          width: 44px; height: 44px; border: 1px dashed #e5e7eb; border-radius: 4px; }
  .ico { display: flex; align-items: center; justify-content: center; }
  .ico svg { width: 100%; height: 100%; display: block; }
</style></head><body>
<h1>地图内置图标预览（${ICONS.length} 个）</h1>
<div class="hint">每行从左到右 ${SIZES.join(' / ')} px；上排蓝色、下排橙色。图标是 canvas 手绘的，这里用同一份图形数据渲染成 SVG 供核对。</div>
<div class="grid">${cards}</div>
</body></html>`

const file = join(out, 'map-icons-preview.html')
writeFileSync(file, html, 'utf8')
console.log(file)
