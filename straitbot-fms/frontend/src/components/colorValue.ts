/**
 * 颜色值的纯函数转换。
 *
 * 为什么要单独一个文件：后端 `ui_field("color", ...)` 存的是**字符串**
 * （如 "#FF7D00"），而 Semi 的 `ColorPicker` 并不是字符串受控组件——它的
 * `value` 必须是 `{ hsva, rgba, hex }` 对象，`renderPicker` 会直接读
 * `currentColor.hsva.h`。把字符串原样传进去，`hsva` 就是 undefined，
 * 读 `.h` 立刻抛
 *   `TypeError: Cannot read properties of undefined (reading 'h')`
 * 整个检视器白屏。
 *
 * 所以：**存字符串、传对象**，两边用这里的函数对起来。
 * 转换口径与 `@douyinfe/semi-foundation/lib/es/colorPicker/utils/convert`
 * 保持一致（rgba 用 0~255，hsva 的 h 用 0~360、s/v 用 0~100），
 * 这样 Semi 内部再算回来的 hex 与传入值相同，不会来回跳。
 *
 * 不复用 Semi 自带的 `ColorPicker.colorStringToValue`：
 * 它对任何不以 # / rgb / rgba / hsv 开头的字符串**直接 throw**，
 * 而且 3 位简写（#F70）会被 `parseInt` 解析出 NaN，一样炸。
 */

export interface Rgba { r: number; g: number; b: number; a: number }
export interface Hsva { h: number; s: number; v: number; a: number }
export interface ColorValue { hsva: Hsva; rgba: Rgba; hex: string }

/** 兜底色：非法 / 空值时用它，保证界面永远能画出来。 */
export const DEFAULT_HEX = '#FF7D00'

const RE_HEX3 = /^#[0-9a-fA-F]{3}$/
const RE_HEX6 = /^#[0-9a-fA-F]{6}$/
const RE_HEX8 = /^#[0-9a-fA-F]{8}$/

/**
 * 把任意输入（字符串 / Semi 的颜色对象 / null / 数字…）收敛成一个合法 hex。
 * 3 位简写会展开成 6 位（Semi 的 hexToRgba 只认 6/8 位，简写会解析出 NaN）。
 * 大小写原样保留；认不出来就返回 fallback。
 */
export function normalizeHex(raw: any, fallback: string = DEFAULT_HEX): string {
  let s = typeof raw === 'string' ? raw.trim() : ''
  if (!s && raw && typeof raw === 'object') s = String((raw as any).hex ?? '').trim()
  if (!s) return fallback
  if (!s.startsWith('#')) s = `#${s}`
  if (RE_HEX3.test(s)) s = `#${s[1]}${s[1]}${s[2]}${s[2]}${s[3]}${s[3]}`
  if (RE_HEX6.test(s) || RE_HEX8.test(s)) return s
  return fallback
}

/** hex → rgba（r/g/b 为 0~255，a 为 0~1）。8 位 hex 的末两位是 alpha。 */
export function hexToRgba(hex: string, fallback: string = DEFAULT_HEX): Rgba {
  const h = normalizeHex(hex, fallback).slice(1)
  const aRaw = h.substring(6, 8)
  return {
    r: parseInt(h.substring(0, 2), 16),
    g: parseInt(h.substring(2, 4), 16),
    b: parseInt(h.substring(4, 6), 16),
    a: aRaw ? parseInt(aRaw, 16) / 255 : 1,
  }
}

/** rgba → hsva，口径与 Semi 的 rgbaToHsva 一致。 */
export function rgbaToHsva({ r, g, b, a }: Rgba): Hsva {
  const max = Math.max(r, g, b)
  const delta = max - Math.min(r, g, b)
  const hh = delta
    ? (max === r ? (g - b) / delta : max === g ? 2 + (b - r) / delta : 4 + (r - g) / delta)
    : 0
  return {
    h: Math.round(60 * (hh < 0 ? hh + 6 : hh)),
    s: Math.round(max ? (delta / max) * 100 : 0),
    v: Math.round((max / 255) * 100),
    a,
  }
}

/** 存的值 → 传给 ColorPicker 的 value（对象）。 */
export function toColorValue(raw: any, fallback: string = DEFAULT_HEX): ColorValue {
  const hex = normalizeHex(raw, fallback)
  const rgba = hexToRgba(hex, fallback)
  return { hsva: rgbaToHsva(rgba), rgba, hex }
}

/** ColorPicker 的 onChange 回调值 → 要存回节点的字符串。 */
export function valueToHex(v: any, fallback: string = DEFAULT_HEX): string {
  if (typeof v === 'string') return normalizeHex(v, fallback)
  return normalizeHex(v?.hex, fallback)
}
