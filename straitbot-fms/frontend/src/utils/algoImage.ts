/**
 * 算法示意图的**纯数学 / 校验**（不碰 DOM，回归脚本能直接算）。
 *
 * 为什么单独拎出来：示意图是 base64 直接写进 `data/algorithms.json` 的，
 * 而那个文件**每次开页面都要整体拉一次**——传原图（随手一张抓拍就好几 MB）
 * 会把算法目录拖慢，也没法再手改了。所以前端必须先压再传，
 * 缩放到多长边、压完还能不能收，这些判定放这里测。
 *
 * 真正画 canvas 的那几行（`FileReader` + `Image` + `canvas.toDataURL`）只能待在
 * 组件里——Node 里没有 canvas。但"缩到多大""压完合不合规"是能算的，就放这儿。
 */

/** 缩略图最长边：卡片上就显示这么大，再大纯粹是浪费 base64 */
export const IMAGE_MAX_SIDE = 320
/** JPEG 质量：0.85 眼看着没什么损失，体积比 1.0 小一半 */
export const IMAGE_QUALITY = 0.85
/** base64 **字符数**上限（后端 `ALGO_IMAGE_MAX_CHARS` 是同一个口径，两边别对不上） */
export const IMAGE_MAX_CHARS = 512 * 1024

export interface ImgSize { w: number; h: number }

/**
 * 缩放到"最长边 <= max"，短边等比。
 *
 * **只缩不放**：一张 40x30 的小图不该被拉成 320x240（那只会糊 + 白占体积）。
 * 两边都至少留 1px，canvas 给 0 宽会直接不画。
 */
export function fittedSize(w: number, h: number, max: number = IMAGE_MAX_SIDE): ImgSize {
  if (!(w > 0) || !(h > 0) || !(max > 0)) return { w: 0, h: 0 }
  const k = Math.min(1, max / Math.max(w, h))
  return {
    w: Math.max(1, Math.round(w * k)),
    h: Math.max(1, Math.round(h * k)),
  }
}

/**
 * 是不是能直接塞进 `<img src>` 的 base64 图。
 *
 * `svg` 不放行：它是 XML，能带脚本，拼进 `src` 就是一块 XSS 面；
 * 后端 `_DATA_URL_RE` 是同一套白名单，改一处要改两处。
 */
export function isImageDataUrl(s: string): boolean {
  return /^data:image\/(png|jpeg|jpg|webp|gif|bmp);base64,[A-Za-z0-9+/]+={0,2}$/.test(s)
}

/** data URL 里 base64 那一段解出来是多少**字节**（不看前缀，前缀不占解码后的体积） */
export function b64Bytes(s: string): number {
  const at = s.indexOf(',')
  const b64 = at < 0 ? s : s.slice(at + 1)
  const pad = (b64.match(/=+$/) || [''])[0].length
  return Math.max(0, Math.floor((b64.length * 3) / 4) - pad)
}

/** 压完还能不能收（尺寸合规 + 没超上限）。空串也合法，那是"删掉示意图"。 */
export function acceptable(s: string): boolean {
  if (!s) return false                       // 空串走删除接口，不在这儿判"可以存"
  return isImageDataUrl(s) && s.length <= IMAGE_MAX_CHARS
}
