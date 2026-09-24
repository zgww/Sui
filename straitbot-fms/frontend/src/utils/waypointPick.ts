/**
 * 「航点指定」面板里**航点专属**的那部分纯函数 —— 无 React 依赖。
 *
 * 通用的树算法（范围选、合并、Semi 树数据）在 `pickTree.ts`；
 * 这里只管"航点树 spec 怎么摊成树"和"怎么喂给地图画布"。
 *
 * ## 楼层只能从**祖先分组名**回解
 *
 * 航点节点上**没有** `floor` 字段（导入时只写进分组名 `楼层N`，见
 * `inspectionBuild.floorOfPath`）。所以这里一律用 `floorOfPath` 回解，
 * 不能读 `properties.floor`——那样所有航点都会显示成 F1，
 * 多楼层航线看起来像"全在同一层"（旧面板就是这个毛病）。
 */
import { trackNodesOf } from './trackSpec'
import { floorOfPath } from './inspectionBuild'
import { waypointKey, waypointLabel, type WaypointBrief } from './planSelect'
import {
  sampleTrack, trackPointsFromNodes,
  type MapWaypoint, type TrackNodePoint,
} from '../components/trackGeometry'
import type { PickNode } from './pickTree'

/** 楼层筛选：`'all'` 表示不筛 */
export type FloorFilter = number | 'all'

/** 航点挑选树的一个节点 */
export type PickTreeNode = PickNode<WaypointBrief>

/** 叶子的短名（画在地图点下面用；带上楼层与米数会太长） */
export function shortLabel(b: WaypointBrief): string {
  return (b.name || '').trim() || b.wp_id || `航点 #${b.index}`
}

/** 分组节点的显示名（缺名回落类型名，**不许出现 undefined**） */
function containerLabel(node: any): string {
  const name = String(node?.properties?.name ?? '').trim()
  if (name) return name
  if (node?.type === 'GroupNode') return '分组'
  return String(node?.type || '节点')
}

/** 航点节点 -> 摘要（楼层从祖先分组名回解，见文件头） */
function briefOf(spec: any, node: any, path: string): WaypointBrief {
  const p = node?.properties || {}
  const index = Number(p.index)
  const x = Number(p.x)
  return {
    path,
    key: waypointKey(node, path),
    wp_id: String(p.wp_id ?? ''),
    name: String(p.name ?? ''),
    floor: floorOfPath(spec, path),
    index: Number.isFinite(index) ? index : 0,
    x: Number.isFinite(x) ? x : 0,
  }
}

/**
 * 航点树 spec -> 树视图数据（**跳过根节点**）。
 *
 * 根节点就是那个文件本身（面板上方已经用下拉框显示文件名了），再画一层
 * "全程TT > 楼层2 > 航点1"只是白占一行缩进。唯一的例外是根节点**自己就是
 * 航点**（单航点的树），那时它就是唯一的内容，必须保留。
 *
 * 不含航点的分支（轨道 `TrackNode`、背景图…）整枝丢掉——它们在"挑航点"这件
 * 事上没有意义，列出来只会让用户以为能选。
 */
export function buildPickTree(spec: any, floor: FloorFilter = 'all'): PickTreeNode[] {
  const root = spec?.root
  if (!root) return []

  const walk = (node: any, path: string): PickTreeNode | null => {
    if (!node || typeof node !== 'object') return null

    if (node.type === 'WaypointNode') {
      const brief = briefOf(spec, node, path)
      if (floor !== 'all' && brief.floor !== floor) return null
      return {
        key: brief.key,
        label: waypointLabel(brief),
        path,
        isLeaf: true,
        data: brief,
      }
    }

    const kids: any[] = node.children || []
    const children = kids
      .map((c, i) => walk(c, `${path}/children/${i}`))
      .filter((c): c is PickTreeNode => !!c)
    if (!children.length) return null
    return { key: path, label: containerLabel(node), path, isLeaf: false, children }
  }

  if (root.type === 'WaypointNode') {
    const only = walk(root, 'root')
    return only ? [only] : []
  }
  const kids: any[] = root.children || []
  return kids
    .map((c, i) => walk(c, `root/children/${i}`))
    .filter((c): c is PickTreeNode => !!c)
}

/** 树里出现过的楼层（升序）；一个都解不出来时返回空数组（面板就不显示筛选项） */
export function floorsOf(spec: any): number[] {
  const seen = new Set<number>()
  const walk = (node: any, path: string) => {
    if (!node || typeof node !== 'object') return
    if (node.type === 'WaypointNode') { seen.add(floorOfPath(spec, path)); return }
    const kids: any[] = node.children || []
    kids.forEach((c, i) => walk(c, `${path}/children/${i}`))
  }
  if (spec?.root) walk(spec.root, 'root')
  return [...seen].sort((a, b) => a - b)
}

/* ------------------------------------------------------------ 地图 */

/** 叶子 -> `TrackMap` 要的航点列表（同一份 key/path，两边不会各算一套） */
export function pickMapWaypoints(leaves: PickTreeNode[]): MapWaypoint[] {
  return leaves.map((n) => ({
    path: n.path,
    x: Number(n.data?.x ?? 0),
    label: shortLabel(n.data as WaypointBrief),
    type: 'WaypointNode',
    u: 0,
  }))
}

/** 地图上要画的那条轨道（取树里**第一条** `TrackNode`） */
export interface PickTrack {
  path: string
  nodes: TrackNodePoint[]
  /** 树里一共有几条轨道（>1 时面板要提示"只画了第一条"） */
  count: number
  /**
   * 轨道采样弧长 (m)，与地图内部那把尺子（`trackLengthOf`）**同源**。
   *
   * 没画轨道（端点不足 2 个）时为 0——那时地图会退回兜底量程，面板也就
   * 不该拿 0 去判"航点是不是超出轨道"（会全员误报）。
   */
  lengthM: number
}

/**
 * 取第一条轨道。
 *
 * 与航点树页面不同，这里**不做**"跟随选中节点"的轨道切换：挑选面板里没有
 * 轨道树可点，让地图自己跳来跳去只会让人不知道在看哪条。多条轨道时如实报个数，
 * 由面板提示用户"这里只画了第一条"。
 */
export function pickTrackOf(spec: any): PickTrack {
  const found: { path: string; node: any }[] = []
  const walk = (node: any, path: string) => {
    if (!node || typeof node !== 'object') return
    if (node.type === 'TrackNode') found.push({ path, node })
    const kids: any[] = node.children || []
    kids.forEach((c, i) => walk(c, `${path}/children/${i}`))
  }
  if (spec?.root) walk(spec.root, 'root')
  const first = found[0]
  const nodes = first ? trackNodesOf(first.path, first.node) : []
  const pts = trackPointsFromNodes(nodes)
  const sampled = pts.length >= 2
    ? sampleTrack(pts, 48, nodes.some((n) => n.kind === 'close'))
    : null
  return {
    path: first?.path || '',
    nodes,
    count: found.length,
    lengthM: sampled && sampled.total > 0 ? sampled.total : 0,
  }
}

/**
 * 弧长超出轨道量程的航点 key（地图上会被 `xToU` 夹到端点、看起来"叠在一起"）。
 *
 * `lengthM <= 0`（没画轨道）时返回空数组——那时地图用的是兜底量程，
 * 拿 0 去比会把每个航点都判成越界。
 */
export function outOfTrackKeys(leaves: PickTreeNode[], lengthM: number): string[] {
  if (!(lengthM > 0)) return []
  return leaves
    .filter((n) => {
      const x = Number(n.data?.x)
      return !Number.isFinite(x) || x < 0 || x > lengthM
    })
    .map((n) => n.key)
}
