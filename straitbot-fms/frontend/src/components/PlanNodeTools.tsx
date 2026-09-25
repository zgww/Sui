/**
 * 巡检计划编排的三个「选什么 / 什么时候」面板。
 *
 * 它们是**检视器的第一项**（走 `InspectorForm` 的 `top` 插槽），与检测框工具
 * 的位置约定一致：先给"这个节点具体在说什么"的专用界面，再往下才是通用字段表单。
 *
 * 为什么单独做面板而不是全靠通用表单：
 * - 「航点指定」要从**另一棵树**（航点树）里挑航点，通用表单填不了引用。
 *   挑法有两套（用户点名要的）：**树视图**（支持 Shift 按可见顺序整段选）与
 *   **地图画布**（框选 / Shift 框选增加 / 框选移除，复用 `TrackMap` 的只读挑选模式）。
 *   两者写的是同一份 `waypoint_ids`，不会各存一套；
 * - 「测点指定」要查**测点档案**的目录，同样用树视图 + Shift 整段选，
 *   树形按档案里真实存在的目录层级（`directories` 的 `parent_id`）展开；
 * - 「每日调度」的 `HH:MM` 字符串填错了通用表单不会报错，只会算不出时刻。
 *   面板能当场把"每天会触发几次、分别在几点"算给人看——这是文本输入框给不了的。
 *
 * 两个挑选面板共用 `utils/pickTree.ts` 的树算法与 `utils/marqueeSelect.ts` 的
 * 合并语义：范围选、Alt 移除、顺序保持只有一份实现，不会两边跑偏。
 *
 * 参数仍然落在**普通 prefab 节点字段**上（不另存一份状态）：面板只是这些字段的
 * 一个更好用的编辑器，关掉面板数据也还在，导出的 JSON 与手填的完全一样。
 */
import { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import { Button, Checkbox, Empty, Input, Select, Spin, Tag, Tree } from '@douyinfe/semi-ui'
import { IconRefresh, IconSearch } from '@douyinfe/semi-icons'
import { getWaypointTree, listWaypointTrees, type WaypointTreeSummary } from '../api/waypointPrefab'
import { catalogApi, type Directory, type Entity } from '../api/pointArchive'
import { formatHm, parseHm, scheduleSlots } from '../utils/planSelect'
import {
  expandableKeys, filterPickTree, flattenPickTree, groupPickInfo, groupToggleMode,
  indexPickTree, keyByPath, keysOfPaths, leafKeysOf, leavesOf, mergePick,
  mergeScopedPick, rangePaths, toSemiTree, toggleKey, unionPick, type PickNode,
} from '../utils/pickTree'
import {
  buildPickTree, floorsOf, outOfTrackKeys, pickMapWaypoints, pickTrackOf,
  type FloorFilter, type PickTreeNode,
} from '../utils/waypointPick'
import {
  buildPointPickTree, type PickPointNode,
} from '../utils/pointPick'
import type { PickMode } from '../utils/marqueeSelect'
import TrackMap from './TrackMap'

interface ToolProps {
  /** 当前节点的 properties（面板只读它，写走 onChange） */
  value: Record<string, any>
  /** 打补丁到当前选中节点的 properties */
  onChange: (patch: Record<string, any>) => void
}

const boxStyle: React.CSSProperties = {
  border: '1px solid var(--semi-color-border)', borderRadius: 6, padding: 8,
  marginBottom: 12,
}
const headStyle: React.CSSProperties = {
  display: 'flex', alignItems: 'center', justifyContent: 'space-between',
  marginBottom: 8, gap: 8, flexWrap: 'wrap',
}
const hintStyle: React.CSSProperties = { fontSize: 12, color: 'var(--semi-color-text-2)' }

/* ============================================================ 共用：挑选树 */

/**
 * 挑选树（「航点指定」「测点指定」共用）：Semi `Tree` + 自己画的勾选行。
 *
 * 几个刻意的选择：
 *
 * 1. **不用 Semi 自己的选中**（`value` / `onChange`）：那边的语义是"选树节点"，
 *    而这里是"挑一批东西"（多点累积、Shift 整段、Alt 移除），两套模型硬凑会
 *    互相打架（Semi 会把我们的多选当成它的单选，高亮和实际选择对不上）。
 *    行的点击由 `renderLabel` 里的元素接管并 `stopPropagation`，Semi 那条路走不到。
 * 2. **勾选框是纯展示的**（`.pp-row .semi-checkbox { pointer-events: none }`）：
 *    Semi 的 Checkbox 把 `onClick` 挂在根节点上且**不** `stopPropagation`，
 *    行上再来一个就是一次点击触发两遍、一开一关正好抵消（"点了没反应"）。
 *    所以点击由**行**（叶子）或**勾选框外面那格 `.pp-pick`**（分组）处理，
 *    Semi 那个 Checkbox 从头到尾只负责画勾 / 半选的样子。
 * 3. **`key` 用路径不用业务 id**：脏数据里业务 id 可能重复（两个航点共用一个
 *    `wp_id`），拿它当 React key 会撞，当范围区间会"选了一个另一个跟着亮"。
 * 4. **分组行自己处理展开**：Semi 的 `expandAction` 默认是 `false`（点行不展开），
 *    而我们又把行的点击截住了，所以分组行的展开要自己 toggle。
 * 5. **分组也能勾**（整枝全选/取消，部分选中时显示半选）：勾选框套在自己的
 *    `.pp-pick` 里接管点击并 `stopPropagation`，点行其它地方仍然是展开/收起——
 *    要是让勾选框的点击冒到行上，就会"选一下顺便收起"，没法连着勾几个分组。
 */
function PickTreeView<T>({
  nodes, expanded, onExpandedChange, pickedSet, onLeafClick, onGroupClick, leafExtra, emptyText,
}: {
  nodes: PickNode<T>[]
  expanded: Set<string>
  onExpandedChange: (next: Set<string>) => void
  pickedSet: Set<string>
  /** 叶子行点击（点选 / Shift 整段 / Alt 移除） */
  onLeafClick: (n: PickNode<T>, e: React.MouseEvent) => void
  /** 分组的**勾选框**点击（整枝全选 / 取消；Shift = 加、Alt = 移除） */
  onGroupClick: (n: PickNode<T>, e: React.MouseEvent) => void
  /** 叶子行右侧的附加内容（"无 wp_id""已停用"之类的提示） */
  leafExtra?: (n: PickNode<T>) => React.ReactNode
  emptyText: string
}) {
  const { index } = useMemo(() => indexPickTree(nodes), [nodes])
  const semiTree = useMemo(() => toSemiTree(nodes), [nodes])

  const toggleExpand = (path: string) => {
    const next = new Set(expanded)
    next.has(path) ? next.delete(path) : next.add(path)
    onExpandedChange(next)
  }

  return (
    <div className="pp-tree">
      {nodes.length === 0 ? (
        <div style={{ padding: 8, ...hintStyle }}>{emptyText}</div>
      ) : (
        <Tree
          treeData={semiTree}
          expandedKeys={[...expanded]}
          onExpand={(keys) => onExpandedChange(new Set(keys as string[]))}
          renderLabel={(_label, node) => {
            const n = index.get(String(node?.key ?? ''))
            if (!n) return <span>{_label}</span>
            if (!n.isLeaf) {
              const info = groupPickInfo(n, pickedSet)
              const cls = ['pp-row', 'pp-row-group']
              if (info.state === 'all') cls.push('pp-row-on')
              if (info.state === 'part') cls.push('pp-row-part')
              return (
                <span
                  className={cls.join(' ')}
                  onClick={(e) => { e.stopPropagation(); toggleExpand(n.path) }}
                >
                  {/* 勾选框单独一格：点它只勾不展开（所以要把点击掐在这里）。
                      空分组（测点档案里刚建的目录）没有可勾的东西，置灰。 */}
                  <span
                    className="pp-pick"
                    title={info.total
                      ? (info.state === 'all' ? '取消整枝' : '选中整枝')
                      : '这个分组里没有可选项'}
                    onMouseDown={(e) => e.preventDefault()}
                    onClick={(e) => { e.stopPropagation(); onGroupClick(n, e) }}
                  >
                    <Checkbox
                      checked={info.state === 'all'}
                      indeterminate={info.state === 'part'}
                      disabled={info.total === 0}
                    />
                  </span>
                  <span className="pp-name">{n.label}</span>
                  <span className="pp-cnt">
                    {info.hit > 0 ? `${info.hit}/${info.total} 个` : `${info.total} 个`}
                  </span>
                </span>
              )
            }
            const on = pickedSet.has(n.key)
            return (
              <span
                className={on ? 'pp-row pp-row-on' : 'pp-row'}
                /* 按住 Shift 点选时浏览器会顺手选中一片文字，把默认行为掐掉 */
                onMouseDown={(e) => e.preventDefault()}
                onClick={(e) => { e.stopPropagation(); onLeafClick(n, e) }}
              >
                <Checkbox checked={on} />
                <span className="pp-name">{n.label}</span>
                {leafExtra ? leafExtra(n) : null}
              </span>
            )
          }}
        />
      )}
    </div>
  )
}

/** "全选 / 反选 / 清空 + 已选 N 个"那一排按钮（两个面板共用） */
function PickBulkBar({
  idsField, visibleKeys, picked, list, onChange, scopeText,
}: {
  /** 写哪个字段（`waypoint_ids` / `point_ids`） */
  idsField: 'waypoint_ids' | 'point_ids'
  /** 当前可见叶子的 key（"全选/反选"只作用在这些上） */
  visibleKeys: string[]
  picked: string[]
  /** 当前字段的原始值（脏数据也要能兜住，交给纯函数去容错） */
  list: unknown
  onChange: (patch: Record<string, any>) => void
  /** 按钮上的范围后缀（"本层" / "当前筛选"） */
  scopeText: string
}) {
  return (
    <div style={{ display: 'flex', gap: 6, marginTop: 6, flexWrap: 'wrap', alignItems: 'center' }}>
      <Button size="small" onClick={() =>
        onChange({ [idsField]: unionPick(list, visibleKeys) })}>
        全选{scopeText}
      </Button>
      <Button size="small" onClick={() => {
        // 反选 = 对每个可见 key 逐个 toggle。**不能"求补集"**：
        // 补集是"全部减去可见"，会把没显示出来的（别的楼层 / 被筛掉的）也一起翻掉。
        let next = Array.isArray(list) ? list.map(String) : []
        for (const k of visibleKeys) next = toggleKey(next, k)
        onChange({ [idsField]: next })
      }}>反选{scopeText}</Button>
      <Button size="small" onClick={() => onChange({ [idsField]: [] })}>清空</Button>
      <span style={{ ...hintStyle, alignSelf: 'center' }}>已选 {picked.length} 个</span>
    </div>
  )
}

/** 一行"点选 / Shift / Alt / 分组"的提示（两个面板一样，抽出来免得抄两遍走样） */
const PICK_HINT = '点选切换 · Shift 点选 = 从上次点到这点整段加选 · Alt 点选 = 移除'
  + ' · 点分组的勾选框 = 整枝全选/取消'

/** "全部展开 / 全部收起 + 手势提示"那一排（两个面板共用） */
function PickExpandBar({
  expandable, onExpandedChange,
}: {
  /** 当前（可能已被筛选过的）树上所有分组的 key */
  expandable: string[]
  onExpandedChange: (next: Set<string>) => void
}) {
  return (
    <div style={{ display: 'flex', gap: 6, marginTop: 6, alignItems: 'center', flexWrap: 'wrap' }}>
      <Button size="small" theme="borderless"
        onClick={() => onExpandedChange(new Set(expandable))}>全部展开</Button>
      <Button size="small" theme="borderless"
        onClick={() => onExpandedChange(new Set())}>全部收起</Button>
      <span style={{ ...hintStyle }}>{PICK_HINT}</span>
    </div>
  )
}

/* ============================================================ 航点指定 */

export function WaypointSelectTool({ value, onChange }: ToolProps) {
  const [trees, setTrees] = useState<WaypointTreeSummary[]>([])
  /** 整棵航点树 spec：树视图与地图画布都从它派生，只拉一次 */
  const [spec, setSpec] = useState<any>(null)
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState('')
  const [kw, setKw] = useState('')
  const [floor, setFloor] = useState<FloorFilter>('all')
  const [expanded, setExpanded] = useState<Set<string>>(new Set())
  /**
   * Shift 范围选择的锚点（**路径**）。存 ref 不存 state：它纯是手势状态，
   * 变了不需要重渲染（重渲染反而会让树闪一下）。
   */
  const anchor = useRef<string | null>(null)

  const source = String(value?.source || '')
  const includeAll = value?.include_all !== false
  const picked = useMemo<string[]>(
    () => (Array.isArray(value?.waypoint_ids) ? value.waypoint_ids.map(String) : []),
    [value?.waypoint_ids],
  )
  const pickedSet = useMemo(() => new Set(picked), [picked])

  const refreshTrees = useCallback(async () => {
    try {
      const { data } = await listWaypointTrees()
      setTrees(data.trees || [])
    } catch { /* 拦截器已提示 */ }
  }, [])

  useEffect(() => { refreshTrees() }, [refreshTrees])

  // 换文件就重新解析。`alive` 挡住快速切换时先到的旧响应（否则会把上一棵树的
  // 航点留在画布上，看起来像"文件切了但内容没变"）。
  useEffect(() => {
    if (!source) { setSpec(null); setError(''); return }
    let alive = true
    setLoading(true); setError('')
    getWaypointTree(source)
      .then(({ data }) => {
        if (!alive) return
        const s = data.spec || null
        setSpec(s)
        // 换了文件，筛选/展开/锚点全都作废：留着只会指向已经不存在的节点
        setKw('')
        setFloor('all')
        anchor.current = null
        // 默认全展开——折叠着的话用户得先点一遍"展开"才能挑，多一道没意义的手续
        setExpanded(new Set(expandableKeys(buildPickTree(s, 'all'))))
      })
      .catch((e: any) => {
        if (!alive) return
        setSpec(null)
        setError(e?.response?.data?.detail || e?.message || '读取航点树失败')
      })
      .finally(() => { if (alive) setLoading(false) })
    return () => { alive = false }
  }, [source])

  /* ---- 派生数据 ---- */

  /** 当前楼层下的树（树视图与地图都用它，两边不会各算一套） */
  const treeData = useMemo(() => buildPickTree(spec, floor), [spec, floor])
  /** 不筛楼层的完整树：判断"已选的航点在不在树里"必须用它，
   *  否则切到 2 楼就会把 1 楼挑好的全报成"找不到" */
  const allLeaves = useMemo(() => leavesOf(buildPickTree(spec, 'all')), [spec])
  const floors = useMemo(() => floorsOf(spec), [spec])
  const filtered = useMemo(() => filterPickTree(treeData, kw), [treeData, kw])
  /** 搜了关键字就强制全展开：不然命中的行藏在折叠分组里，等于没搜 */
  const openKeys = useMemo(
    () => (kw.trim() ? expandableKeys(filtered) : [...expanded]),
    [kw, filtered, expanded],
  )
  const visiblePaths = useMemo(() => flattenPickTree(filtered, openKeys), [filtered, openKeys])
  /** 树实际用的展开集合 = `openKeys`（搜关键字时被强制成全展开）。
   *  可见顺序与树显示必须是**同一份**，否则 Shift 区间会和眼睛看到的不一致。 */
  const openKeysSet = useMemo(() => new Set(openKeys), [openKeys])
  const leaves = useMemo(() => leavesOf(treeData), [treeData])
  const byPath = useMemo(() => keyByPath(leaves), [leaves])

  const mapWaypoints = useMemo(() => pickMapWaypoints(leaves), [leaves])
  const track = useMemo(() => pickTrackOf(spec), [spec])
  /** 地图上要高亮的路径（一个 key 可能对应多个路径——wp_id 重复时） */
  const mapSelPaths = useMemo(
    () => new Set(leaves.filter((l) => pickedSet.has(l.key)).map((l) => l.path)),
    [leaves, pickedSet],
  )
  /** 地图上能表示的 key 集合（"只在这个范围内替换"用，见 mergeScopedPick） */
  const mapScopeKeys = useMemo(() => leaves.map((l) => l.key), [leaves])
  const outOfTrack = useMemo(
    () => outOfTrackKeys(leaves, track.lengthM),
    [leaves, track.lengthM],
  )
  const missing = useMemo(() => {
    const known = new Set(allLeaves.map((l) => l.key))
    return picked.filter((k) => !known.has(k))
  }, [picked, allLeaves])

  /* ---- 改选择 ---- */

  /** 按 key 批量改选择（**合并不是替换**：整枝全选也要保住别的分组挑好的） */
  const applyKeys = useCallback((keys: string[], mode: PickMode) => {
    if (!keys.length && mode !== 'replace') return
    onChange({ waypoint_ids: mergePick(value?.waypoint_ids, keys, mode) })
  }, [onChange, value?.waypoint_ids])

  /** 按路径批量改选择（树的 Shift 范围选走这里） */
  const applyPaths = useCallback((paths: string[], mode: PickMode) => {
    applyKeys(keysOfPaths(byPath, paths), mode)
  }, [applyKeys, byPath])

  /**
   * 地图框选结果回写。
   *
   * 用 `mergeScopedPick` 而不是直接替换：地图只画得出当前楼层的航点，
   * 直接替换会把别的楼层挑好的清空（而且毫无提示）。
   *
   * 另外这里**不**再套一遍"增加/移除"：框选模式已经在 `TrackMap` 内部
   * 按"按下那一刻的快照"合过了，传回来的是最终结果，再合一次会把
   * 刚被移除的点又加回来。
   */
  const onMapSelect = useCallback((paths: Set<string>) => {
    const hit = keysOfPaths(byPath, [...paths])
    onChange({ waypoint_ids: mergeScopedPick(value?.waypoint_ids, hit, mapScopeKeys) })
  }, [byPath, onChange, value?.waypoint_ids, mapScopeKeys])

  /** 树行点击：Shift = 从锚点到这点整段加选；Alt = 移除这一点；否则切换这一点 */
  const onLeafClick = (n: PickTreeNode, e: React.MouseEvent) => {
    if (e.shiftKey) {
      const paths = rangePaths(visiblePaths, anchor.current, n.path)
      if (paths.length) applyPaths(paths, 'add')
    } else if (e.altKey) {
      applyPaths([n.path], 'remove')
    } else {
      onChange({ waypoint_ids: toggleKey(value?.waypoint_ids, n.key) })
    }
    // Shift 连点时段区间要从**同一个锚点**重算（Windows 资源管理器的习惯）；
    // 锚点跟着跑的话，第二次 Shift 点只会选中相邻的两行。
    if (!e.shiftKey) anchor.current = n.path
  }

  /**
   * 分组的勾选框：整枝全选 / 取消。
   *
   * **不动锚点**：锚点是**叶子路径**，分组行不在可见顺序里（`flattenPickTree`
   * 只收叶子），把锚点设成分组路径会让下一次 Shift 点选退化成"只选一个"。
   * 留着上次点的叶子，勾完分组再 Shift 点一个航点，区间仍然从那儿起算。
   */
  const onGroupClick = (n: PickTreeNode, e: React.MouseEvent) => {
    const keys = leafKeysOf(n)
    if (!keys.length) return
    // Shift = 加、Alt = 移除，与叶子行同一套手势；不加修饰键时"全选了就取消"
    const auto = groupToggleMode(n, pickedSet)
    const mode: PickMode = e.shiftKey ? 'add' : e.altKey ? 'remove' : (auto ?? 'add')
    applyKeys(keys, mode)
  }

  const visibleKeys = useMemo(
    () => keysOfPaths(byPath, visiblePaths),
    [byPath, visiblePaths],
  )

  return (
    <div style={boxStyle}>
      <div style={headStyle}>
        <span style={{ fontWeight: 600 }}>航点指定</span>
        <span style={hintStyle}>
          {loading ? '读取中…' : leaves.length ? `共 ${leaves.length} 个航点` : ''}
        </span>
      </div>

      <div style={{ display: 'flex', gap: 6, alignItems: 'center', marginBottom: 8 }}>
        <span style={{ ...hintStyle, flexShrink: 0 }}>航点树文件</span>
        <Select
          value={source || undefined}
          placeholder="选择一棵航点树"
          style={{ flex: 1, minWidth: 0 }}
          filter
          onChange={(v) => onChange({ source: String(v || ''), waypoint_ids: [] })}
          optionList={trees.map((t) => ({ label: t.rel_path, value: t.rel_path }))}
          emptyContent={<div style={{ padding: 12, ...hintStyle }}>还没有航点树文件</div>}
        />
        <Button icon={<IconRefresh />} theme="borderless" onClick={refreshTrees} />
      </div>

      <Checkbox
        checked={includeAll}
        onChange={(e: any) => onChange({ include_all: !!e.target.checked })}
      >
        该航点树里的航点全都要
      </Checkbox>

      {includeAll && (
        <div style={{ ...hintStyle, marginTop: 8 }}>
          已勾「全部航点」，下面的选择被忽略（内容仍保留，取消勾选即可恢复）。
        </div>
      )}

      {!source ? (
        <div style={{ ...hintStyle, marginTop: 8 }}>
          先选一棵航点树，才能指定具体巡检哪些航点。
        </div>
      ) : error ? (
        <div style={{ marginTop: 8, color: 'var(--semi-color-danger)', fontSize: 12 }}>{error}</div>
      ) : loading ? (
        <div style={{ textAlign: 'center', padding: 12 }}><Spin /></div>
      ) : leaves.length === 0 ? (
        <Empty title="这棵航点树里没有航点" style={{ padding: '12px 0' }} />
      ) : (
        /* 勾了「全部航点」时整块置灰且不可点：让人一眼看出"现在改这里没有用"，
           而不是点了半天才发现被忽略。 */
        <div style={includeAll ? { opacity: 0.55, pointerEvents: 'none' } : undefined}>
          {floors.length > 1 && (
            <div style={{ display: 'flex', gap: 6, alignItems: 'center', marginTop: 8 }}>
              <span style={{ ...hintStyle, flexShrink: 0 }}>楼层</span>
              <Select
                value={floor === 'all' ? 'all' : String(floor)}
                style={{ width: 132 }}
                onChange={(v) => {
                  const raw = String(v)
                  setFloor(raw === 'all' ? 'all' : Number(raw))
                  // 换楼层后锚点那个航点多半已经不在列表里，留着会让下一次
                  // Shift 点选的范围莫名其妙
                  anchor.current = null
                }}
                optionList={[
                  { label: `全部（${floors.length} 层）`, value: 'all' },
                  ...floors.map((f) => ({ label: `楼层 ${f}`, value: String(f) })),
                ]}
              />
              <span style={{ ...hintStyle }}>本层 {leaves.length} 个</span>
            </div>
          )}

          <Input
            prefix={<IconSearch />}
            placeholder="按名称 / ID / 楼层筛选"
            value={kw}
            onChange={(v) => setKw(String(v))}
            style={{ marginTop: 8 }}
          />

          <PickBulkBar
            idsField="waypoint_ids"
            visibleKeys={visibleKeys}
            picked={picked}
            list={value?.waypoint_ids}
            onChange={onChange}
            scopeText={kw.trim() ? '（当前筛选）' : '本层'}
          />

          <PickExpandBar
            expandable={expandableKeys(filtered)}
            onExpandedChange={setExpanded}
          />

          <PickTreeView
            nodes={filtered}
            expanded={openKeysSet}
            onExpandedChange={setExpanded}
            pickedSet={pickedSet}
            onLeafClick={onLeafClick}
            onGroupClick={onGroupClick}
            emptyText="无匹配航点"
            leafExtra={(n) => (n.data?.wp_id
              ? null
              : <Tag size="small" color="amber">无 wp_id，按路径标识</Tag>)}
          />

          <div className="pp-map">
            {/* 地图画布：只读挑选模式（没有绘制/图层/背景图入口，右键也不弹菜单），
                选中结果按"只替换地图上画得出的那些"并回 waypoint_ids。 */}
            <TrackMap
              waypoints={mapWaypoints}
              selectedPaths={mapSelPaths}
              onSelectionChange={onMapSelect}
              trackNodes={track.nodes}
              trackName={track.count === 1 ? '轨道' : undefined}
              trackCount={track.count}
              pickerMode
              height={200}
            />
          </div>

          {track.count > 1 && (
            <div className="pp-hint">
              这棵航点树里有 {track.count} 条轨道，地图只画了第一条；航点仍按各自的
              弧长定位，框选只影响画出来的那些。
            </div>
          )}
          {outOfTrack.length > 0 && (
            <div style={{ ...hintStyle, marginTop: 6, color: 'var(--semi-color-warning)' }}>
              有 {outOfTrack.length} 个航点的弧长超出了轨道范围（轨道长约{' '}
              {track.lengthM.toFixed(1)} m），在地图上会贴到端点显示。
            </div>
          )}
          {missing.length > 0 && (
            <div style={{ marginTop: 6, fontSize: 12, color: 'var(--semi-color-warning)' }}>
              有 {missing.length} 个已指定的航点在当前树里找不到（航点树被改过？）：
              {missing.slice(0, 3).join('、')}{missing.length > 3 ? ' …' : ''}
            </div>
          )}
        </div>
      )}
    </div>
  )
}

/* ============================================================ 测点指定 */

/** 一次最多拉多少条测点（后端 `page_size` 上限 200） */
const POINT_PAGE = 200
/**
 * 最多拉多少页（200 × 50 = 10000 条）。
 *
 * 拉全量是**故意**的：树要按目录层级完整展开、Shift 范围选要覆盖到没展开的目录，
 * 都得手里有全量数据；分页列表做不到这两件事。真到一万条以上多半是档案本身
 * 出了问题，那时如实提示"只加载了前 N 个"，而不是假装加载完了。
 */
const POINT_MAX_PAGES = 50

/**
 * 测点指定：**测点档案的目录树** + Shift 整段选。
 *
 * 为什么按目录分层而不是像原来那样摊成一页 100 条的平列表：
 * - 平列表要翻页，翻过去的页一离开就看不见，Shift 范围选跨不了页，
 *   "把某个设备下的测点全选上"这种事根本没做；
 * - 档案里本来就有目录层级，摊平等于把用户自己维护的结构扔了。
 */
export function PointSelectTool({ value, onChange }: ToolProps) {
  const [dirs, setDirs] = useState<Directory[]>([])
  const [points, setPoints] = useState<Entity[]>([])
  const [total, setTotal] = useState(0)
  const [truncated, setTruncated] = useState(false)
  const [kw, setKw] = useState('')
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState('')
  const [expanded, setExpanded] = useState<Set<string>>(new Set())
  const anchor = useRef<string | null>(null)

  const includeAll = value?.include_all !== false
  const picked = useMemo<string[]>(
    () => (Array.isArray(value?.point_ids) ? value.point_ids.map(String) : []),
    [value?.point_ids],
  )
  const pickedSet = useMemo(() => new Set(picked), [picked])

  const load = useCallback(async () => {
    setLoading(true); setError('')
    try {
      const meta = await catalogApi.directories()
      const ds = meta.items || []
      setDirs(ds)

      // 第一页先拿到 total，剩下的页**并行**拉：串行 25 页要等好几秒
      const first = await catalogApi.points({ page: 1, page_size: POINT_PAGE })
      const totalCount = Number(first.total || 0)
      const pages = Math.max(1, Math.ceil(totalCount / POINT_PAGE))
      const want = Math.min(pages, POINT_MAX_PAGES)
      setTruncated(pages > want)
      const rest = want > 1
        ? await Promise.all(Array.from({ length: want - 1 }, (_, i) =>
            catalogApi.points({ page: i + 2, page_size: POINT_PAGE })))
        : []
      const all = [first, ...rest].flatMap((r) => r.items || [])
      setPoints(all)
      setTotal(totalCount)

      // 默认全展开：小档案（≤ 一页）直接可挑；大档案只展开到一级，
      // 免得一打开就渲染几千行把面板拖卡
      const tree = buildPointPickTree(ds, all)
      setExpanded(totalCount <= POINT_PAGE
        ? new Set(expandableKeys(tree))
        : new Set(tree.map((n) => n.key)))
    } catch (e: any) {
      setDirs([]); setPoints([]); setTotal(0)
      setError(e?.response?.data?.detail || e?.message || '读取测点档案失败')
    } finally { setLoading(false) }
  }, [])

  useEffect(() => { load() }, [load])

  /* ---- 派生数据 ---- */

  const treeData = useMemo(() => buildPointPickTree(dirs, points), [dirs, points])
  const filtered = useMemo(
    // 编号（`code`）不在标签里，得靠 extra 补进可搜索文本，
    // 否则"按编号找测点"会一条都搜不到（placeholder 里承诺了能按编号搜）
    () => filterPickTree(treeData, kw, (n) => n.data?.code || ''),
    [treeData, kw],
  )
  /** 搜了关键字就强制全展开：不然命中的行藏在折叠目录里，等于没搜 */
  const openKeys = useMemo(
    () => (kw.trim() ? expandableKeys(filtered) : [...expanded]),
    [kw, filtered, expanded],
  )
  const openKeysSet = useMemo(() => new Set(openKeys), [openKeys])
  const visiblePaths = useMemo(() => flattenPickTree(filtered, openKeys), [filtered, openKeys])
  const leaves = useMemo(() => leavesOf(treeData), [treeData])
  const byPath = useMemo(() => keyByPath(leaves), [leaves])
  const visibleKeys = useMemo(() => keysOfPaths(byPath, visiblePaths), [byPath, visiblePaths])

  /** 已指定但档案里找不到的测点 id（档案被改过 / 导入换了一批） */
  const missing = useMemo(() => {
    const known = new Set(leaves.map((l) => l.key))
    return picked.filter((k) => !known.has(k))
  }, [picked, leaves])

  /** 按 key 批量改选择（**合并不是替换**：整枝全选也要保住别处挑好的） */
  const applyKeys = useCallback((keys: string[], mode: PickMode) => {
    if (!keys.length && mode !== 'replace') return
    onChange({ point_ids: mergePick(value?.point_ids, keys, mode) })
  }, [onChange, value?.point_ids])

  const applyPaths = useCallback((paths: string[], mode: PickMode) => {
    applyKeys(keysOfPaths(byPath, paths), mode)
  }, [applyKeys, byPath])

  /** 树行点击：Shift = 从锚点到这点整段加选；Alt = 移除这一点；否则切换这一点 */
  const onLeafClick = (n: PickPointNode, e: React.MouseEvent) => {
    if (e.shiftKey) {
      const paths = rangePaths(visiblePaths, anchor.current, n.path)
      if (paths.length) applyPaths(paths, 'add')
    } else if (e.altKey) {
      applyPaths([n.path], 'remove')
    } else {
      onChange({ point_ids: toggleKey(value?.point_ids, n.key) })
    }
    // Shift 连点时段区间要从**同一个锚点**重算（Windows 资源管理器的习惯）
    if (!e.shiftKey) anchor.current = n.path
  }

  /** 分组（目录）的勾选框：整枝全选 / 取消。**不动锚点**，理由同航点面板 */
  const onGroupClick = (n: PickPointNode, e: React.MouseEvent) => {
    const keys = leafKeysOf(n)
    if (!keys.length) return    // 空目录：档案里刚建的目录，没有可勾的东西
    const auto = groupToggleMode(n, pickedSet)
    const mode: PickMode = e.shiftKey ? 'add' : e.altKey ? 'remove' : (auto ?? 'add')
    applyKeys(keys, mode)
  }

  return (
    <div style={boxStyle}>
      <div style={headStyle}>
        <span style={{ fontWeight: 600 }}>测点指定</span>
        <span style={hintStyle}>
          {loading ? '读取中…' : total ? `共 ${total} 个测点 · ${dirs.length} 个目录` : ''}
        </span>
      </div>

      <Checkbox
        checked={includeAll}
        onChange={(e: any) => onChange({ include_all: !!e.target.checked })}
      >
        测点档案里的测点全都要
      </Checkbox>

      {includeAll && (
        <div style={{ ...hintStyle, marginTop: 8 }}>
          已勾「全部测点」，下面的选择被忽略（内容仍保留，取消勾选即可恢复）。
        </div>
      )}

      {error ? (
        <div style={{ marginTop: 8, color: 'var(--semi-color-danger)', fontSize: 12 }}>{error}</div>
      ) : loading ? (
        <div style={{ textAlign: 'center', padding: 12 }}><Spin /></div>
      ) : leaves.length === 0 ? (
        <Empty title="测点档案里还没有测点" style={{ padding: '12px 0' }} />
      ) : (
        /* 勾了「全部测点」时整块置灰且不可点：让人一眼看出"现在改这里没有用" */
        <div style={includeAll ? { opacity: 0.55, pointerEvents: 'none' } : undefined}>
          {truncated && (
            <div style={{ ...hintStyle, marginTop: 8, color: 'var(--semi-color-warning)' }}>
              测点太多，只加载了前 {points.length} 个（共 {total} 个）——
              建议先按名称筛选，或到「测点档案」里整理目录。
            </div>
          )}

          <Input
            prefix={<IconSearch />}
            placeholder="按名称 / 编号 / id 筛选（含目录名）"
            value={kw}
            onChange={(v) => {
              setKw(String(v))
              // 换了筛选条件，锚点那个测点多半已经不在可见列表里了
              anchor.current = null
            }}
            style={{ marginTop: 8 }}
          />

          <PickBulkBar
            idsField="point_ids"
            visibleKeys={visibleKeys}
            picked={picked}
            list={value?.point_ids}
            onChange={onChange}
            scopeText={kw.trim() ? '（当前筛选）' : '（可见）'}
          />

          <PickExpandBar
            expandable={expandableKeys(filtered)}
            onExpandedChange={setExpanded}
          />

          <PickTreeView
            nodes={filtered}
            expanded={openKeysSet}
            onExpandedChange={setExpanded}
            pickedSet={pickedSet}
            onLeafClick={onLeafClick}
            onGroupClick={onGroupClick}
            emptyText="没有匹配的测点"
            leafExtra={(n) => (<>
              <span style={{ ...hintStyle, marginLeft: 'auto', flexShrink: 0 }}>{n.key}</span>
              {n.data?.active === false ? <Tag size="small" color="grey">已停用</Tag> : null}
            </>)}
          />

          {missing.length > 0 && (
            <div style={{ marginTop: 6, fontSize: 12, color: 'var(--semi-color-warning)' }}>
              有 {missing.length} 个已指定的测点在档案里找不到（档案被改过？）：
              {missing.slice(0, 3).join('、')}{missing.length > 3 ? ' …' : ''}
            </div>
          )}

          <div style={{ ...hintStyle, marginTop: 6 }}>
            这里存的是**测点档案**的测点 id，与检测框绑定的测点是同一份档案；
            未归类的测点收在「未归类」分组里。
          </div>
        </div>
      )}
    </div>
  )
}

/* ============================================================ 每日调度 */

/** 预览里最多列出几个时刻（一天排几百次时全列出来只会把面板撑爆） */
const PREVIEW_LIMIT = 12

export function DailyScheduleTool({ value, onChange }: ToolProps) {
  const start = String(value?.start_time ?? '')
  const end = String(value?.end_time ?? '')
  const interval = value?.interval_minutes

  const slots = useMemo(() => scheduleSlots(start, end, interval), [start, end, interval])
  const startOk = parseHm(start) !== null
  const endOk = parseHm(end) !== null
  const intervalOk = Number.isFinite(Number(interval)) && Number(interval) > 0

  const setTime = (field: 'start_time' | 'end_time', raw: string) =>
    onChange({ [field]: raw })

  const bad = (ok: boolean): React.CSSProperties => (
    ok ? {} : { borderColor: 'var(--semi-color-danger)' }
  )

  return (
    <div style={boxStyle}>
      <div style={headStyle}>
        <span style={{ fontWeight: 600 }}>每日调度</span>
        <span style={hintStyle}>每天在时间范围内按间隔执行</span>
      </div>

      <div style={{ display: 'flex', gap: 8, alignItems: 'center', flexWrap: 'wrap' }}>
        <span style={hintStyle}>从</span>
        <Input
          value={start}
          placeholder="HH:MM"
          style={{ width: 96, ...bad(startOk) }}
          onChange={(v) => setTime('start_time', String(v))}
          onBlur={() => {
            // 失焦时顺手规范化：填 "8:5" 这种半截写法直接纠正成 "08:05"，
            // 留着不管的话后端拿到的就是个解析不出来的值
            const m = parseHm(start)
            if (m !== null && formatHm(m) !== start) setTime('start_time', formatHm(m))
          }}
        />
        <span style={hintStyle}>到</span>
        <Input
          value={end}
          placeholder="HH:MM"
          style={{ width: 96, ...bad(endOk) }}
          onChange={(v) => setTime('end_time', String(v))}
          onBlur={() => {
            const m = parseHm(end)
            if (m !== null && formatHm(m) !== end) setTime('end_time', formatHm(m))
          }}
        />
        <span style={hintStyle}>每隔</span>
        <Input
          value={String(interval ?? '')}
          placeholder="分钟"
          style={{ width: 84, ...bad(intervalOk) }}
          onChange={(v) => {
            const n = Number(String(v).trim())
            onChange({ interval_minutes: Number.isFinite(n) ? n : 0 })
          }}
        />
        <span style={hintStyle}>分钟</span>
      </div>

      <div style={{ marginTop: 10 }}>
        {!startOk || !endOk ? (
          <div style={{ fontSize: 12, color: 'var(--semi-color-danger)' }}>
            时间要写成 HH:MM（24 小时制），例如 08:00。
          </div>
        ) : !intervalOk ? (
          <div style={{ fontSize: 12, color: 'var(--semi-color-danger)' }}>间隔要大于 0 分钟。</div>
        ) : slots.length === 0 ? (
          <div style={{ fontSize: 12, color: 'var(--semi-color-danger)' }}>
            结束时间早于开始时间——不支持跨零点，夜间巡检请拆成两条计划。
          </div>
        ) : (
          <div>
            <div style={{ fontSize: 12, marginBottom: 6 }}>
              每天触发 <b>{slots.length}</b> 次（末次不晚于结束时间）：
            </div>
            <div style={{ display: 'flex', gap: 4, flexWrap: 'wrap' }}>
              {slots.slice(0, PREVIEW_LIMIT).map((s) => (
                <Tag key={s} size="small" color="blue">{s}</Tag>
              ))}
              {slots.length > PREVIEW_LIMIT
                ? <Tag size="small" color="grey">… 还有 {slots.length - PREVIEW_LIMIT} 次</Tag>
                : null}
            </div>
          </div>
        )}
      </div>
    </div>
  )
}

/** 计划树节点 -> 对应的专用面板；没有专用面板的类型返回 null（只看通用表单） */
export function PlanNodeTool({ node, onChange }: { node: any; onChange: (patch: Record<string, any>) => void }) {
  const value = node?.properties || {}
  if (node?.type === 'WaypointSelectNode') return <WaypointSelectTool value={value} onChange={onChange} />
  if (node?.type === 'PointSelectNode') return <PointSelectTool value={value} onChange={onChange} />
  if (node?.type === 'DailyScheduleNode') return <DailyScheduleTool value={value} onChange={onChange} />
  return null
}
