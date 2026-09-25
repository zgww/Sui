import React, { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import {
  Button, Dropdown, Empty, Input, Space, Spin, Tag, Tooltip, Typography,
} from '@douyinfe/semi-ui'
import { IconChevronDown, IconChevronRight, IconRefresh } from '@douyinfe/semi-icons'
import ModelessWindow from './ModelessWindow'
import { catalogApi, type Directory, type Entity } from '../api/pointArchive'

/**
 * 绑定测点窗口：主体是**测点档案的目录树**，目录展开后列出它下面的测点，
 * 每个测点后面「绑定 / 绑定并切下一个检测框」两个按钮。
 *
 * 之所以做成树 + 两个按钮：给一批检测框挨个绑测点是**高频批量操作**，
 * 「绑定并切下一个」让手一直停在树上，不用 "点框 → 点绑定 → 再点框" 来回挪。
 *
 * 数据是**懒加载**的：目录一次性拉全（`catalogApi.directories`），
 * 测点只在目录被展开时才拉（`catalogApi.points`）——档案里测点可能上千条，
 * 全量拉下来会让弹窗卡一下，也没人一次看得完。
 *
 * **非模态 + 可拖拽**（这里是刻意自己画的，没用 Semi 的 `Modal`）：
 * Semi Modal 没有 `modal={false}`，它一显示就会挂遮罩、锁 `body` 滚动、把焦点圈在框里，
 * 而绑测点这活儿**必须能一边开着它一边在画布上点框、画框**——挡住画布等于废掉一半功能。
 * 所以它走 `createPortal` 挂到 `body`：没有遮罩、不锁滚动、不抢焦点、也不吃 Esc
 * （Esc 留给画布的"放弃绘制"）。位置由标题栏拖拽决定，双击标题栏复位。
 */

/** 一次最多拉多少条测点（后端 page_size 上限 200） */
const PAGE_SIZE = 200

const ROLE_TEXT: Record<string, string> = {
  station: '变电站', voltage: '电压等级', bay: '间隔', equipment: '设备', custom: '目录',
}

interface Props {
  visible: boolean
  /** 正在给哪个框绑（标题里显示，切下一个后标题要跟着变） */
  boxLabel: string
  /** 当前框已绑的测点 id，'' = 还没绑 */
  currentPointId: string
  /** 本动作点下**所有**检测框已绑的测点 id —— 树里要标成不同颜色 */
  boundPointIds: Set<string>
  /**
   * 整棵树的测点占用表：测点 id -> "航点名 / 动作点名 / 检测框 #2"。
   * 有它的测点就是**被占住了**（含别的航点、别的动作点，以及测温点），
   * 不给「绑定」按钮——一个测点只能绑一处；同时把路径显示出来，
   * 让人知道想去改的话该去哪儿找。
   */
  pointUsage?: Record<string, string>
  /** @param advance true = 绑完自动切到下一个检测框 */
  onBind: (pointId: string, pointName: string, advance: boolean) => void
  /**
   * 解绑**当前框**的测点。
   *
   * 解绑之后**不关窗口**：绑错了要能立刻改绑另一个测点，关掉再开一次太绕。
   */
  onUnbind: () => void
  onClose: () => void
}

type Row =
  | { kind: 'dir'; key: string; id: string; name: string; depth: number; dir: Directory }
  | { kind: 'point'; key: string; id: string; name: string; code: string; depth: number }

export default function BindPointModal({
  visible, boxLabel, currentPointId, boundPointIds, pointUsage = {},
  onBind, onUnbind, onClose,
}: Props) {
  const [dirs, setDirs] = useState<Directory[]>([])
  const [expanded, setExpanded] = useState<Set<string>>(new Set())
  const [pointsOf, setPointsOf] = useState<Record<string, Entity[]>>({})
  const [selected, setSelected] = useState<string | null>(null)
  const [kw, setKw] = useState('')
  const [hits, setHits] = useState<Entity[] | null>(null)
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState('')

  /** 右键菜单开在哪一行上（存 row.key；null = 没开）。受控，见 `menuFor` 的注释 */
  const [ctxRow, setCtxRow] = useState<string | null>(null)

  /** 目录的父子关系：整棵树就靠它展开 */
  const childrenOf = useMemo(() => {
    const m = new Map<string | null, Directory[]>()
    for (const d of dirs) {
      const a = m.get(d.parent_id) || []
      a.push(d)
      m.set(d.parent_id, a)
    }
    return m
  }, [dirs])

  const loadDirs = useCallback(() => {
    let alive = true
    setLoading(true)
    setError('')
    catalogApi.directories()
      .then((r) => { if (alive) setDirs(r.items || []) })
      .catch((e: any) => { if (alive) setError(e?.message || '测点档案加载失败') })
      .finally(() => { if (alive) setLoading(false) })
    return () => { alive = false }
  }, [])

  // 必须把 loadDirs 返回的取消函数交出去，否则 alive 守卫是死的：
  // 加载途中切走节点，请求回来照样 setState
  useEffect(() => { if (visible) return loadDirs() }, [visible, loadDirs])

  /** 拉某个目录**直属**的测点（不递归：递归会把子目录的也混进来，树就乱了） */
  const ensurePoints = useCallback((dirIds: string[]) => {
    const missing = dirIds.filter((id) => pointsOf[id] === undefined)
    if (!missing.length) return
    // 先占位成空数组，避免"展开中"时重复发同一批请求
    setPointsOf((prev) => {
      const next = { ...prev }
      for (const id of missing) if (next[id] === undefined) next[id] = []
      return next
    })
    for (const id of missing) {
      catalogApi.points({ directory_id: id, recursive: false, page: 1, page_size: PAGE_SIZE })
        .then((r) => setPointsOf((prev) => ({ ...prev, [id]: r.items || [] })))
        .catch(() => setPointsOf((prev) => ({ ...prev, [id]: [] })))
    }
  }, [pointsOf])

  /* ---- 搜索：走后端的 q（名字 / 编码 / id），不做前端全量过滤 ---- */
  const timer = useRef<number | null>(null)
  useEffect(() => {
    if (!visible) return
    const q = kw.trim()
    if (!q) { setHits(null); return }
    if (timer.current) window.clearTimeout(timer.current)
    timer.current = window.setTimeout(() => {
      catalogApi.points({ q, recursive: true, page: 1, page_size: PAGE_SIZE })
        .then((r) => setHits(r.items || []))
        .catch(() => setHits([]))
    }, 250)
    return () => { if (timer.current) window.clearTimeout(timer.current) }
  }, [kw, visible])

  const rows = useMemo<Row[]>(() => {
    if (hits) {
      return hits.map((p) => ({
        kind: 'point' as const, key: `p:${p.id}`, id: p.id,
        name: String(p.name || p.id), code: String(p.code || ''), depth: 0,
      }))
    }
    const out: Row[] = []
    const walk = (list: Directory[], depth: number) => {
      for (const d of list) {
        out.push({ kind: 'dir', key: `d:${d.id}`, id: d.id, name: d.name, depth, dir: d })
        if (!expanded.has(d.id)) continue
        for (const p of pointsOf[d.id] || []) {
          out.push({
            kind: 'point', key: `p:${p.id}`, id: p.id,
            name: String(p.name || p.id), code: String(p.code || ''), depth: depth + 1,
          })
        }
        walk(childrenOf.get(d.id) || [], depth + 1)
      }
    }
    walk(childrenOf.get(null) || [], 0)
    return out
  }, [hits, expanded, pointsOf, childrenOf])

  /** 一个目录的所有后代目录 id（展开全部 / 收缩全部用） */
  const descendants = useCallback((id: string): string[] => {
    const out: string[] = []
    const stack = [id]
    while (stack.length) {
      const cur = stack.pop()!
      for (const c of childrenOf.get(cur) || []) { out.push(c.id); stack.push(c.id) }
    }
    return out
  }, [childrenOf])

  const expandAll = (id: string) => {
    const ids = [id, ...descendants(id)]
    setExpanded((prev) => new Set([...prev, ...ids]))
    ensurePoints(ids)
  }
  const collapseAll = (id: string) => {
    const ids = new Set([id, ...descendants(id)])
    setExpanded((prev) => new Set([...prev].filter((k) => !ids.has(k))))
  }
  const toggle = (d: Directory) => {
    // ensurePoints 是副作用，不能写在 setState 的 updater 里：StrictMode 下
    // updater 会被跑两遍，同一个目录就发了两次请求（两次都读到还没更新的 pointsOf）
    const opening = !expanded.has(d.id)
    setExpanded((prev) => {
      const next = new Set(prev)
      if (next.has(d.id)) next.delete(d.id)
      else next.add(d.id)
      return next
    })
    if (opening) ensurePoints([d.id])
  }

  /**
   * 右键菜单。
   *
   * ⚠️ 菜单的开关是**受控**的（`visible` + `onVisibleChange`），不是扔给 Semi 自己管：
   * Semi 的"点一项就收起"只对 `Dropdown.Menu` / `Dropdown.Item` 生效，
   * 我们这里是自定义 `render`（纯 div + 自己的 `.bp-ctx-item`），
   * Semi 不知道哪一项算"选完了"，**点了不会关**——必须自己收。
   * （TrackMap 的图层下拉是同一个套路，差别是那边"连着勾好几项"要**故意**不关。）
   */
  const menuFor = (row: Row) => {
    const used = row.kind === 'point' ? (pointUsage[row.id] || '') : ''
    const mine = row.kind === 'point' && row.id === currentPointId
    // 被别处占了：一个测点只能绑一处，菜单里也不给绑定项
    const taken = Boolean(used) && !mine
    return (
      <div className="bp-ctx">
        {row.kind === 'dir' ? (
          <>
            <button type="button" className="bp-ctx-item"
              onClick={() => { setCtxRow(null); expandAll(row.id) }}>展开全部</button>
            <button type="button" className="bp-ctx-item"
              onClick={() => { setCtxRow(null); collapseAll(row.id) }}>收缩全部</button>
          </>
        ) : (
          <>
            {/* 已经绑在本框上的测点，给的是**取消绑定**而不是"绑定"——
                对它再点一次绑定是空操作，放个点了没反应的按钮是误导 */}
            {mine ? (
              <button type="button" className="bp-ctx-item"
                onClick={() => { setCtxRow(null); onUnbind() }}>取消绑定本框</button>
            ) : taken ? (
              <button type="button" className="bp-ctx-item" disabled>
                已绑在 {used}
              </button>
            ) : (
              <>
                <button type="button" className="bp-ctx-item"
                  onClick={() => { setCtxRow(null); onBind(row.id, row.name, false) }}>绑定</button>
                <button type="button" className="bp-ctx-item"
                  onClick={() => { setCtxRow(null); onBind(row.id, row.name, true) }}>
                  绑定并切下一个检测框
                </button>
              </>
            )}
          </>
        )}
      </div>
    )
  }

  if (!visible) return null

  return (
    <ModelessWindow
      title={`绑定测点 · ${boxLabel}`}
      hint="拖动这里平移"
      bodyClass="bp"
      onClose={onClose}
      footer={
        <Space>
          <Button size="small" type="tertiary" icon={<IconRefresh />}
            onClick={loadDirs}>刷新档案</Button>
          <Button type="tertiary" onClick={onClose}>关闭</Button>
        </Space>
      }
    >
    <Input
      prefix="搜索" showClear value={kw} onChange={setKw}
      placeholder="按测点名称 / 编码 / id 搜索（搜到的是平铺列表）"
    />

      {error ? <Typography.Text type="danger" size="small">{error}</Typography.Text> : null}

      <div className="bp-tree">
        {loading && !rows.length ? (
          <div className="bp-center"><Spin size="small" /> 正在加载测点档案…</div>
        ) : null}

        {!loading && !rows.length ? (
          <Empty style={{ padding: '18px 0' }} title="没有可绑定的测点"
            description={kw ? '换个关键词试试' : '测点档案里还没有目录/测点'} />
        ) : null}

        {rows.map((row) => {
          const isDir = row.kind === 'dir'
          /** 绑在哪（整棵树范围）；'' = 还没被任何地方绑走 */
          const used = !isDir ? (pointUsage[row.id] || '') : ''
          const mine = !isDir && row.id === currentPointId
          /** 被**别处**占住了：不给绑定按钮，只显示它绑在哪 */
          const taken = Boolean(used) && !mine
          const bound = !isDir && (boundPointIds.has(row.id) || Boolean(used))
          const open = isDir && expanded.has(row.id)
          return (
            <Dropdown
              key={row.key}
              trigger="contextMenu"
              position="bottomLeft"
              visible={ctxRow === row.key}
              onVisibleChange={(v) => setCtxRow(v ? row.key : null)}
              render={menuFor(row)}
            >
              <div
                className={`bp-row${selected === row.id ? ' is-sel' : ''}`
                  + `${bound ? ' is-bound' : ''}${taken ? ' is-taken' : ''}`}
                style={{ paddingLeft: 6 + row.depth * 14 }}
                onClick={() => {
                  setSelected(row.id)
                  if (isDir) toggle(row.dir)
                }}
              >
                <span className="bp-caret">
                  {isDir
                    ? (open ? <IconChevronDown size="small" /> : <IconChevronRight size="small" />)
                    : null}
                </span>
                <span className="bp-name">{row.name}</span>
                {isDir ? (
                  <>
                    <Tag size="small" color="grey">{ROLE_TEXT[row.dir.role] || row.dir.role}</Tag>
                    {row.dir.point_count ? (
                      <span className="bp-meta">{row.dir.point_count} 测点</span>
                    ) : null}
                  </>
                ) : (
                  <>
                    {row.code ? <span className="bp-meta">{row.code}</span> : null}
                    {/* 绑在哪要写成**航点 / 动作点**的路径：只写"已绑定"等于没说，
                        想挪一下这个测点的人得知道去哪找 */}
                    {used ? (
                      <Tooltip content={mine ? `本框已绑：${used}` : `已绑在：${used}`}
                        position="top">
                        <span className="bp-path">{used}</span>
                      </Tooltip>
                    ) : null}
                    <span className="bp-actions">
                      {mine ? (
                        <Button size="small" theme="light" type="danger"
                          onClick={(e) => { e.stopPropagation(); onUnbind() }}>
                          取消绑定
                        </Button>
                      ) : taken ? (
                        <Tooltip content={`已绑在：${used}。一个测点只能绑一处，先去那边解绑`}
                          position="top">
                          <Tag size="small" color="amber">已绑定</Tag>
                        </Tooltip>
                      ) : (
                        <>
                          <Button size="small" theme="light" type="primary"
                            onClick={(e) => { e.stopPropagation(); onBind(row.id, row.name, false) }}>
                            绑定
                          </Button>
                          <Button size="small" type="tertiary"
                            onClick={(e) => { e.stopPropagation(); onBind(row.id, row.name, true) }}>
                            绑定并切下一个检测框
                          </Button>
                        </>
                      )}
                    </span>
                  </>
                )}
              </div>
            </Dropdown>
          )
        })}
      </div>

      <Typography.Text type="tertiary" size="small">
        测点后面那串「航点 / 动作点 / 检测框」是它**已经绑在哪**——一个测点只能绑一处，
        被占住的测点不给「绑定」按钮，要先去那边解绑（别的航点、测温点也算占用）。
        右键节点可以「展开全部 / 收缩全部」；
        「绑定并切下一个检测框」绑完自动跳下一个框，一路点下去就能把整批框绑完。
        绑定 / 解绑之后**窗口都不关**：接着绑下一个，或者绑错了立刻改绑。
      </Typography.Text>
    </ModelessWindow>
  )
}
