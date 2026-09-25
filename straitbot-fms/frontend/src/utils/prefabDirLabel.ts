/**
 * Prefab 目录树的显示名与图标归属（纯函数，供 PreFab.tsx 接线）。
 *
 * 两条规则值得单独拎出来（都在页面上改过一次就踩一次）：
 *  1. 文件名显示**全名**（带 `.prefab.json`）。`data/prefabs` 下允许放别的
 *     json（如手改的备份），裁掉后缀会让 `a.json` 与 `a.prefab.json` 在树上
 *     显示成两行一模一样的 `a`，看不出在编辑哪一个。
 *  2. 图标只按**相对路径的第一段**认目录。`waypoint/楼层1` 也该是航点树的图标；
 *     目录名是业务约定不是代码常量，认不出来回落通用文件夹图标。
 *
 * 新增业务目录时只需往 `DIR_ICON_KEY` 加一条，页面代码不用动。
 */

const SEP = '/'

/** 一级目录名 -> 图标键（页面把键映射到具体图标组件，纯函数不引 React） */
export const DIR_ICON_KEY: Record<string, string> = {
  '启动': 'bolt',
  waypoint: 'map-pin',
  plan: 'calendar',
  '检测算法': 'shield',
}

/** 认不出来时用的图标键 */
export const DIR_ICON_FALLBACK = 'folder'

/**
 * 取图标键：按相对路径的第一段查表。
 * 相对路径里的反斜杠一并归一化（Windows 上手改过的数据）。
 */
export function dirIconKey(rel: string | null | undefined): string {
  const head = String(rel ?? '').replace(/\\/g, SEP).split(SEP)[0]
  return DIR_ICON_KEY[head] ?? DIR_ICON_FALLBACK
}

/**
 * 树节点上显示的文件名 = 相对路径的最后一段，**保留 `.prefab.json`**。
 * 反斜杠归一化；空输入返回空串（不抛，树渲染时不该因为一条脏数据炸）。
 */
export function fileDisplayName(rel: string | null | undefined): string {
  const s = String(rel ?? '').replace(/\\/g, SEP)
  if (!s) return ''
  const parts = s.split(SEP)
  // 末尾是空段（"a/b/" 这种）时往上找一段
  for (let i = parts.length - 1; i >= 0; i--) {
    if (parts[i]) return parts[i]
  }
  return ''
}

/** 目录节点上显示的名字（同上，目录一般没有后缀） */
export function dirDisplayName(rel: string | null | undefined): string {
  return fileDisplayName(rel)
}

/**
 * 文件 summary 的相对路径：后端给 `rel_path` 就用它，否则由 name 拼。
 * 与页面在别处（打开/重命名/保存）的兜底口径必须一致，抽出来统一。
 */
export function fileRelPath(f: { rel_path?: string; name?: string } | null | undefined): string {
  if (!f) return ''
  return f.rel_path || (f.name ? `${f.name}.prefab.json` : '')
}
