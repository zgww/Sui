/**
 * 「测点指定」面板里**测点专属**的那部分纯函数 —— 无 React 依赖。
 *
 * 通用的树算法在 `pickTree.ts`（与「航点指定」共用同一套范围选/合并语义）。
 *
 * ## 树是按**档案目录**分的，不是硬摊成一层
 *
 * 测点档案里本来就有目录层级（`directories` 的 `parent_id`），面板如实把它
 * 画出来：变电站 > 电压等级 > 间隔 > 设备 > 测点。硬摊成一层的话，
 * 上千条测点会糊成一片，"我想把某个设备下的测点全选上"这件事就做不了。
 *
 * ## 两个必须处理的边界
 *
 * 1. **测点可以不属于任何目录**（`directory_id` 为 `null`，或指向一个已经被删掉的
 *    目录）。这种点在按目录展开的树里永远出不来，所以单独收进一个「未归类」分组——
 *    没有它，用户会看到"档案里明明有 300 个测点，这里只有 280 个"却找不到原因。
 * 2. **空目录要留着**——注意这与航点树"不含航点的分组整枝丢掉"的规则**相反**。
 *    测点档案的目录是用户自己维护的结构，一个刚建好、还没放测点的目录是**正常状态**；
 *    藏起来会让人以为"我建的目录没了"，甚至以为数据丢了。目录本身就是有效信息，
 *    多几行空分组比"目录凭空消失"好得多。
 */
import type { Directory, Entity } from '../api/pointArchive'
import type { PickNode } from './pickTree'

/** 测点在挑选树里的摘要 */
export interface PointBrief {
  id: string
  name: string
  code: string
  active: boolean
  /** 直属目录 id；`null` = 未归类 */
  directory_id: string | null
  /** 目录名（后端给了 `parent_name`，没给就自己查） */
  directory_name: string
}

/** 测点挑选树的一个节点 */
export type PickPointNode = PickNode<PointBrief>

/** 未归类分组用的伪目录 id（真实目录 id 不会长这样，不会撞） */
export const ROOT_GROUP = '__root__'

/** 目录/测点在树里的路径前缀（保证 path 唯一） */
const dirPath = (id: string) => `d:${id}`
const pointPath = (id: string) => `p:${id}`

/** 叶子短名（测点没有"楼层/米数"那套后缀） */
export function pointLabel(p: PointBrief): string {
  return (p.name || '').trim() || p.id
}

/**
 * `parent_id -> 子目录` 索引。
 *
 * 顺序就是接口给的顺序（后端按档案里的目录顺序返回，与档案页面一致）——
 * 这里**不重排**，否则同一个目录在两个页面上位置不同，看着像两份数据。
 */
export function childrenOfDirs(dirs: Directory[]): Map<string | null, Directory[]> {
  const m = new Map<string | null, Directory[]>()
  for (const d of dirs) {
    const a = m.get(d.parent_id ?? null) || []
    a.push(d)
    m.set(d.parent_id ?? null, a)
  }
  return m
}

/** 一个目录的所有后代目录 id（含自身；"展开全部"用） */
export function descendantDirs(dirs: Directory[], id: string): string[] {
  const kids = childrenOfDirs(dirs)
  const out: string[] = []
  const stack = [id]
  while (stack.length) {
    const cur = stack.pop() as string
    out.push(cur)
    for (const c of kids.get(cur) || []) stack.push(c.id)
  }
  return out
}

/** 整棵树的目录 id（面板默认展开用） */
export function allDirIds(dirs: Directory[]): string[] {
  return dirs.map((d) => d.id)
}

/**
 * 测点档案 -> 挑选树。
 *
 * @param dirs    `catalogApi.directories()` 的 items
 * @param points  **已加载的**测点（面板会把所有页拉全再传进来）
 *
 * 未归类判定：`directory_id` 为空，或指向一个**不在 `dirs` 里**的目录
 * （目录被删了但测点还挂着——档案的引用保护不保证这一点，宁可多收一层）。
 */
export function buildPointPickTree(
  dirs: Directory[],
  points: Entity[],
): PickPointNode[] {
  const known = new Set(dirs.map((d) => d.id))
  const byDir = new Map<string, Entity[]>()
  const loose: Entity[] = []
  for (const p of points) {
    const d = p.directory_id == null ? null : String(p.directory_id)
    if (!d || !known.has(d)) { loose.push(p); continue }
    const a = byDir.get(d) || []
    a.push(p)
    byDir.set(d, a)
  }

  const dirName = new Map(dirs.map((d) => [d.id, d.name || d.id]))

  const pointNode = (p: Entity, dir: string | null): PickPointNode => {
    const brief: PointBrief = {
      id: String(p.id),
      name: String(p.name ?? ''),
      code: String(p.code ?? ''),
      active: p.active !== false,
      directory_id: dir,
      directory_name: dir ? (dirName.get(dir) || String(p.parent_name ?? '根目录')) : '未归类',
    }
    return {
      key: brief.id,
      label: pointLabel(brief),
      path: pointPath(brief.id),
      isLeaf: true,
      data: brief,
    }
  }

  const kids = childrenOfDirs(dirs)
  const walk = (parent: string | null): PickPointNode[] =>
    (kids.get(parent) || []).map((d) => {
      const children: PickPointNode[] = [
        ...(byDir.get(d.id) || []).map((p) => pointNode(p, d.id)),
        ...walk(d.id),
      ]
      return {
        key: dirPath(d.id),
        label: d.name || d.id,
        path: dirPath(d.id),
        isLeaf: false,
        children,
      }
    })

  const tree = walk(null)
  // 未归类的点单独一组：没有它，这些点在"按目录展开"的树里永远出不来
  if (loose.length) {
    tree.push({
      key: dirPath(ROOT_GROUP),
      label: '未归类',
      path: dirPath(ROOT_GROUP),
      isLeaf: false,
      children: loose.map((p) => pointNode(p, null)),
    })
  }
  return tree
}

/** 测点 -> 树外展示用的短名（`name → id`，**不许出现 undefined**） */
export function pointSummary(p: PointBrief): string {
  const parts = [pointLabel(p)]
  if (p.code) parts.push(p.code)
  return parts.join(' · ')
}
