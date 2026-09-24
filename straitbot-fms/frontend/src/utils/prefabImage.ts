/**
 * 航点树抓拍图（ActionPointNode.imageUrl）的路径处理。
 *
 * 抽成纯函数是为了能进回归脚本——组件里的逻辑测不到，
 * 而"相对路径拼错"这类问题只在换目录层级的 prefab 上才暴露，手点很难碰上。
 *
 * 存储约定（后端 `routers/waypoint_prefab.py` 的 `/capture` 定）：
 *   - 图片落在**当前 prefab 文件所在目录**下的 `images/`；
 *   - `imageUrl` 存的是**相对 prefab 文件**的路径，如 `images/cap_1a2b3c4d.jpg`。
 *
 * 存相对路径而不是绝对 URL，是为了让整棵航点树（含 images 目录）整体搬走
 * 或改名时不断链；绝对地址一旦换了部署目录就全成死图。
 */

/** 后端 main.py 把整个 WAYPOINT_PREFAB_DIR 挂到了这个前缀下 */
export const PREFAB_STATIC_PREFIX = '/data/prefabs/waypoint'

/** 抓拍图存放的子目录名（与后端 CAPTURE_SUBDIR 一致） */
export const CAPTURE_SUBDIR = 'images'

/**
 * `a/b/c.prefab.json` -> `a/b`（根目录返回空串，拼 URL 时不留双斜杠）。
 */
export function prefabDir(rel: unknown): string {
  const s = typeof rel === 'string' ? rel.replace(/\\/g, '/').trim() : ''
  const i = s.lastIndexOf('/')
  return i > 0 ? s.slice(0, i) : ''
}

/** 看起来就是绝对地址（http(s) / 根路径 / data URI）的路径，不再拼前缀 */
export function isAbsoluteImage(v: string): boolean {
  return /^(https?:)?\/\//i.test(v) || v.startsWith('/') || v.startsWith('data:')
}

/**
 * 把 `imageUrl` 变成能塞进 `<img src>` 的地址。
 *
 * - 空值 -> 空串（调用方据此渲染"未拍照"占位，别把空串塞给 img，
 *   否则浏览器会用当前页面 URL 去请求，刷出一堆 404）；
 * - 绝对地址 -> 原样返回（老数据可能是手填的 URL）；
 * - 相对路径 -> 拼上静态挂载点 + prefab 所在目录。
 */
export function resolveImageUrl(imageUrl: unknown, prefabRel: unknown): string {
  const v = typeof imageUrl === 'string' ? imageUrl.trim() : ''
  if (!v) return ''
  if (isAbsoluteImage(v)) return v
  // 允许 "images/x.jpg" 与 "./images/x.jpg" 两种写法
  const rel = v.replace(/^\.\/+/, '')
  const dir = prefabDir(prefabRel)
  return dir
    ? `${PREFAB_STATIC_PREFIX}/${dir}/${rel}`
    : `${PREFAB_STATIC_PREFIX}/${rel}`
}
