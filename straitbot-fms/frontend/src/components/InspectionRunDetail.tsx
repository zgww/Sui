import React, { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import { Button, Empty, Image, Modal, Space, Spin, Tag, Toast, Tooltip, Tree } from '@douyinfe/semi-ui'
import {
  IconAlertCircle, IconChevronDown, IconChevronUp, IconRefresh, IconPlay, IconPause,
  IconExternalOpen,
} from '@douyinfe/semi-icons'
import { inspectionLogApi, type ActionResultRow, type InspectionRunRow, type PointResultRow } from '../api/inspectionLog'
import { startDrag } from '../utils/splitter'
import {
  addExpanded, allDoneText, allKeys, buildLogTree, defaultSelection, expandTo, findNode,
  firstPendingKey, fmtTime, inspectNode, isExpanded, removeExpanded, selfKeys, subtreeKeys,
  type LogTreeNode,
} from '../utils/inspectionLogTree'

/**
 * 巡检日志**详情内容**（左树 + 右检视器）—— 页面内窗口与独立详情页共用这一份。
 *
 * ## 为什么抽成"内容"而不是直接写成页面
 *
 * 同一块内容有两个宿主：清单页里点「详情」弹出的非模态窗口、以及直接打开的
 * 独立路由页 `/inspection/log/:id`。两边的外壳（`ModelessWindow` /
 * `page-container`）和顶部工具栏不同，但树、检视器、滚动行为必须**完全一致** ——
 * 复制一份必然漂移，所以布局与外层留白交给宿主，这里只负责内容与数据。
 *
 * ## 四级树：楼层 → 航点 → 动作点 → 检测框
 *
 * 链条是 `action.floor → action.waypoint_id → action.action_id → point.id`。
 * ⚠️ **测点只有 `action_result_id` 一个外键**，挂错了树上看着很整齐、页面上完全
 * 看不出来，所以建树逻辑放在纯函数模块并用回归脚本锁着。
 *
 * ## 跟随刷新（"盯当前正在跑的那一步"）
 *
 * 工具栏的开关打开后每 `POLL_MS` 重新拉一次账本，并**每轮重新求"第一个未执行的动作"**
 * 并自动选中它 —— 机器人往前跑一格，界面就跟一格，不用手动点。
 * `skipped` 不算"未执行"（那是已经判过的结论），否则会永远停在同一个动作上。
 *
 * ## 检测图为什么能看全
 *
 * 原来的写法是 `<Image style={{maxHeight:260, objectFit:'contain'}}>`：Semi 的
 * `Image` 外层包了 `.semi-image` 容器，`maxHeight` 只作用在**外框**上，里面的
 * `<img>` 仍按原始宽高比铺开，于是"框高 260、图高 800"——多出来的部分被裁掉，
 * 用户怎么拉滚动条都只能看到上 1/3。改成 `block` 占满整行 + `maxHeight: none`
 * 让图**按容器宽度自适应高度**，再给一个可点的「原图」入口看 1:1。
 */
interface Props {
  runId: number
  /** 已知的列表行（独立页首次加载时可能还没有，拉到了再补） */
  run?: InspectionRunRow | null
  /** 工具栏右侧的额外按钮（独立页用来放"返回列表"） */
  extraToolbar?: React.ReactNode
  /** 走独立路由页时给一个"在新标签页打开"的入口；窗口里不需要 */
  onOpenExternal?: () => void
}

/** Semi 的 TagColor 是字符串字面量联合，纯逻辑模块只返回宽 string，这里收一次口。 */
type TagColorLike = React.ComponentProps<typeof Tag>['color']

/** 跟随刷新的间隔。5 秒：够跟上机器人动作节奏，又不至于把接口打爆。 */
const POLL_MS = 5000

export default function InspectionRunDetail({ runId, run: runProp, extraToolbar, onOpenExternal }: Props) {
  const [run, setRun] = useState<InspectionRunRow | null>(runProp || null)
  const [actions, setActions] = useState<ActionResultRow[]>([])
  const [points, setPoints] = useState<PointResultRow[]>([])
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState('')
  const [selected, setSelected] = useState<string | null>(null)
  const [expanded, setExpanded] = useState<string[]>([])
  const [treeWidth, setTreeWidth] = useState(340)
  const [preview, setPreview] = useState({ visible: false, url: '', title: '' })
  // —— 跟随刷新 ——
  const [polling, setPolling] = useState(false)
  const [pollAt, setPollAt] = useState<Date | null>(null)
  /** 用户手动点过树之后就别再抢选中了（只有轮询自动跳才改选中） */
  const manualRef = useRef(false)
  /**
   * 组件卸载后回调还会跑（请求慢时），用它挡住 setState。
   *
   * ⚠️ **必须在 effect 体里重新置 `true`，不能只在 `useRef(true)` 初始化**。
   * `React.StrictMode`（`main.tsx` 里开着）在开发模式下会把 effect 走一遍
   * "挂载 → 卸载 → 再挂载"，而 `useRef` 的初始值只在**第一次**渲染时算：
   * 清理函数把 `aliveRef.current` 置 `false` 之后，第二次挂载并不会把它改回来，
   * 于是重新发起的请求回来时被 `if (!aliveRef.current) return` 拦掉 ——
   * `loading` 永远是 `true`、`tree` 永远是空表，页面**一直转圈**（接口其实 200）。
   * 只写 `useRef(true)` 的写法在纯函数回归 / build 里都发现不了，只有真开页面才露。
   */
  const aliveRef = useRef(true)
  useEffect(() => {
    aliveRef.current = true
    return () => { aliveRef.current = false }
  }, [])

  /**
   * 右键菜单：`x/y` 是**相对树容器**的坐标（容器是 `position:relative`），
   * `key` 是右键命中的节点。
   */
  const [menu, setMenu] = useState<{ x: number; y: number; key: string } | null>(null)
  const treeBoxRef = useRef<HTMLDivElement | null>(null)

  /**
   * @param silent 轮询用：不显示 loading 转圈、不重置选中 —— 否则每 5 秒
   *   整块区域闪一下 blank，眼睛受不了，而且会把用户刚点的选中弹回去。
   */
  const load = useCallback(async (silent = false) => {
    if (!silent) { setLoading(true); setError('') }
    try {
      // 一起拉：树要靠 action_result_id 把测点挂到动作下
      const [act, pts] = await Promise.all([
        inspectionLogApi.actions(runId),
        inspectionLogApi.points(runId),
      ])
      if (!aliveRef.current) return
      setActions(act.items || [])
      setPoints(pts.items || [])
      if (silent) setPollAt(new Date())
    } catch (e: any) {
      if (!aliveRef.current) return
      // 轮询失败不刷成全屏错误（可能只是后端重启了一下），只在摘要条上提示
      if (silent) Toast.warning(e?.message || '刷新失败')
      else setError(e?.message || '加载失败')
    } finally {
      if (aliveRef.current) setLoading(false)
    }
  }, [runId])

  useEffect(() => { load(false) }, [load])

  /**
   * 独立页直开 `/inspection/log/:id` 时手里只有 id，没有列表行 ——
   * 用 `/runs/{id}/summary` 补齐标题栏要的 `robot_name` / `status` / `remark`。
   * （列表行已经给了就不拉。）
   */
  useEffect(() => {
    if (runProp) { setRun(runProp); return }
    let stop = false
    inspectionLogApi.summary(runId)
      .then((row) => { if (!stop) setRun(row) })
      .catch(() => { /* 拉不到就只少个标题，树照样能看 */ })
    return () => { stop = true }
  }, [runId, runProp])

  const tree = useMemo(() => buildLogTree(actions, points), [actions, points])
  /** 首次建树才自动展开/选中 —— 之后树再变（轮询、手动刷新）不许重置用户的展开态 */
  const initedRef = useRef(false)

  /**
   * 首次拿到数据：展开全部 + 默认选中第一个动作（打开就能看到东西）。
   *
   * ⚠️ 必须只跑一次。若跟着 `tree` 每次都跑，轮询每 5 秒就会把用户
   * "收起全部"之后的状态again 铺开 —— 用户会觉得"这树根本不听使唤"。
   */
  useEffect(() => {
    if (initedRef.current || !tree.length) return
    initedRef.current = true
    setExpanded(allKeys(tree))
    setSelected(defaultSelection(tree))
  }, [tree])

  /**
   * 跟随刷新：树变了之后重新求"第一个未执行的动作"并选中它，同时把它的
   * 祖先链展开（否则选中态躲在折叠的分支里，看着像没动）。
   *
   * ⚠️ 只在用户**没有手动点过**的时候自动跳，否则每 5 秒把人家刚点开的
   * 检测框弹走，比不刷新还难受。
   */
  useEffect(() => {
    if (!polling || !tree.length) return
    const key = firstPendingKey(tree)
    if (!key) return
    if (manualRef.current) return
    setSelected((cur) => (cur === key ? cur : key))
    setExpanded((cur) => expandTo(tree, key, cur))
  }, [polling, tree])

  // 轮询定时器：只挂一次，每次触发 silent 拉数据（不闪 loading）
  useEffect(() => {
    if (!polling) return
    const t = window.setInterval(() => { load(true) }, POLL_MS)
    return () => window.clearInterval(t)
  }, [polling, load])

  const selectedNode = useMemo(() => findNode(tree, selected), [tree, selected])
  const groups = useMemo(() => inspectNode(selectedNode), [selectedNode])

  /** 手动触发检测 */
  const handleTriggerDetect = useCallback(async (action: ActionResultRow) => {
    try {
      await inspectionLogApi.triggerDetect(runId, action.id)
      Toast.success('已提交检测任务，请稍后查看结果')
    } catch (e: any) {
      Toast.error(e?.message || '触发检测失败')
    }
  }, [runId])
  const treeData = useMemo(() => toSemiTree(tree), [tree])

  const expandAll = () => setExpanded(allKeys(tree))
  const collapseAll = () => setExpanded(tree.map((n) => n.key))

  /** 用户手动选节点 —— 记一笔，之后轮询不再抢选中 */
  const onTreeSelect = (_k: string, _s: boolean, node: any) => {
    manualRef.current = true
    setSelected(node.key as string)
  }

  /** 点「跟随刷新」开关：开启时立刻跳一次，不等第一个 5 秒 */
  const togglePolling = () => {
    const next = !polling
    setPolling(next)
    if (next) {
      manualRef.current = false
      setPollAt(new Date())
      load(true)
    }
  }

  const pendingKey = useMemo(() => firstPendingKey(tree), [tree])

  /* ---- 右键菜单 ---- */

  /**
   * 菜单开着时：点别处 / 滚动 / Esc / 失焦都关掉。
   *
   * ⚠️ **必须放过菜单内部的点击**。这里是 window 的**捕获阶段**监听，一定先于
   * 菜单项的 React 处理器执行。若不加区分地 setMenu(null)，菜单会在 mousedown
   * 那一刻就被卸载，浏览器凑不齐 click 所需的 down/up 配对，菜单项的 onClick
   * **永远不触发** —— 表现就是"菜单能弹出来，点了没反应"。
   * （坑记在 `MEMORY.md` 第一条：轨道地图和检测框各踩过一次。）
   */
  useEffect(() => {
    if (!menu) return
    const onDown = (e: MouseEvent) => {
      const el = e.target
      if (el instanceof Element && el.closest('.ird-ctx')) return
      setMenu(null)
    }
    const onWheel = () => setMenu(null)
    const onKey = (e: KeyboardEvent) => { if (e.key === 'Escape') setMenu(null) }
    const onBlur = () => setMenu(null)   // 必须具名，匿名的话 remove 不掉
    window.addEventListener('mousedown', onDown, true)
    window.addEventListener('wheel', onWheel, true)
    window.addEventListener('keydown', onKey)
    window.addEventListener('blur', onBlur)
    return () => {
      window.removeEventListener('mousedown', onDown, true)
      window.removeEventListener('wheel', onWheel, true)
      window.removeEventListener('keydown', onKey)
      window.removeEventListener('blur', onBlur)
    }
  }, [menu])

  /**
   * 树行的右键。
   *
   * 用 `closest('[data-ird-key]')` 从事件目标往上找 —— 右键很可能落在 label
   * 内层的 `<span>` 上，直接读 `e.target` 拿不到节点 key。
   * 坐标按**树容器**算（容器 `position:relative`），这样分隔条拖动时菜单跟着走。
   */
  const onTreeContextMenu = (e: React.MouseEvent) => {
    const host = (e.target as HTMLElement).closest('[data-ird-key]')
    if (!host) return
    e.preventDefault()
    const rect = treeBoxRef.current?.getBoundingClientRect()
    if (!rect) return
    setMenu({
      x: e.clientX - rect.left,
      y: e.clientY - rect.top,
      key: host.getAttribute('data-ird-key') || '',
    })
  }

  /** 菜单动作：`self` = 连同自己一起开合；否则只动子孙 */
  const menuApply = (key: string, withSelf: boolean, open: boolean) => {
    const keys = [
      ...(withSelf ? selfKeys(tree, key) : []),
      ...subtreeKeys(tree, key),
    ]
    if (!keys.length) return
    setExpanded((cur) => (open ? addExpanded(cur, keys) : removeExpanded(cur, keys)))
    // ⚠️ 用户已经明确干预过树的开合 → 之后轮询别再抢着展开，否则"收起"白点
    manualRef.current = true
    setMenu(null)
  }

  /** 菜单项可用性：叶子没有"展开子树"这回事，置灰而不是让它点了没反应 */
  const menuTarget = useMemo(() => {
    const node = findNode(tree, menu?.key ?? null)
    return {
      node,
      hasChildren: !!node?.children.length,
      hasSubtree: !!menu?.key && subtreeKeys(tree, menu.key).length > 0,
      opened: isExpanded(expanded, menu?.key ?? null),
    }
  }, [tree, menu, expanded])

  // —— 加载 / 错误 / 空 ——
  if (error) {
    return (
      <div className="ird-error">
        <IconAlertCircle /> {error}
        <Button size="small" theme="borderless" onClick={() => load(false)}>重试</Button>
      </div>
    )
  }
  if (loading && !tree.length) {
    return <div className="ird-center"><Spin size="large" /></div>
  }

  return (
    <div className="ird">
      {/* 摘要条：机器人 / 计数 / 时间 */}
      <div className="ird-summary">
        <span>{run?.robot_name || (run?.robot_pk != null ? `#${run.robot_pk}` : '未关联机器人')}</span>
        <span className="ird-sep">|</span>
        <span>动作 <b>{actions.length}</b></span>
        <span>检测框 <b>{points.length}</b></span>
        <span className="ird-sep">|</span>
        <span>开始 {fmtTime(run?.start_time)}</span>
        <span>结束 {fmtTime(run?.finish_time)}</span>
        {run?.remark ? <><span className="ird-sep">|</span><span>{run.remark}</span></> : null}
        {polling ? (
          <>
            <span className="ird-sep">|</span>
            <span className="ird-poll-note">
              跟随刷新中（每 {POLL_MS / 1000}s）· {allDoneText(actions)}
              {pollAt ? ` · ${pollAt.toLocaleTimeString()}` : ''}
            </span>
          </>
        ) : null}
      </div>

      {/* 工具栏：跟随刷新开关 / 展开收起 / 刷新 / 宿主自带按钮 */}
      <div className="ird-tools">
        <Tooltip content={polling ? '停止跟随刷新' : '开启后每 5 秒刷新，并自动选中当前第一个未执行的动作点'}>
          <Button
            size="small"
            theme={polling ? 'solid' : 'light'}
            type={polling ? 'primary' : 'tertiary'}
            icon={polling ? <IconPause /> : <IconPlay />}
            onClick={togglePolling}
          >
            {polling ? '停止跟随' : '跟随刷新'}
          </Button>
        </Tooltip>
        {polling && !pendingKey ? (
          <Tag size="small" color="green">{allDoneText(actions)}</Tag>
        ) : null}

        <span className="ird-tools-gap" />

        <Button size="small" icon={<IconChevronDown />} onClick={expandAll}>展开全部</Button>
        <Button size="small" icon={<IconChevronUp />} onClick={collapseAll}>收起全部</Button>
        <Button size="small" icon={<IconRefresh />} onClick={() => load(false)}>刷新</Button>
        {onOpenExternal ? (
          <Button size="small" icon={<IconExternalOpen />} onClick={onOpenExternal}>
            新标签页打开
          </Button>
        ) : null}
        {extraToolbar}
      </div>

      {!tree.length ? (
        <Empty
          title="这次巡检没有动作账本数据"
          description="可能是改造前的老记录（旧表没有分发状态与检测框维度），或占位尚未生成"
        />
      ) : (
        <div className="ird-wrap">
          {/* 左：树（宽度可拖）。右键菜单定位在**树容器**里，所以它要 position:relative */}
          <div
            className="ird-tree"
            ref={treeBoxRef}
            style={{ width: treeWidth }}
            onContextMenu={onTreeContextMenu}
          >
            <Tree
              treeData={treeData}
              value={selected ? [selected] : []}
              expandedKeys={expanded}
              onExpand={(keys: string[]) => setExpanded(keys)}
              onSelect={onTreeSelect}
              renderLabel={(label: React.ReactNode, node: any) => (
                <TreeLabel node={node.__raw as LogTreeNode} text={label} />
              )}
            />
            {menu && menuTarget.node ? (
              <div
                className="ird-ctx"
                style={{ left: menu.x, top: menu.y }}
                // 菜单里再右键不要弹浏览器菜单（会盖住我们的）
                onContextMenu={(e) => e.preventDefault()}
              >
                <div className="ird-ctx-head">{menuTarget.node.label}</div>

                <button type="button" className="ird-ctx-item"
                  disabled={!menuTarget.hasSubtree}
                  onClick={() => menuApply(menu.key, false, true)}>
                  <IconChevronDown /> 展开子树<span className="ird-ctx-note">不含自己</span>
                </button>
                <button type="button" className="ird-ctx-item"
                  disabled={!menuTarget.hasSubtree}
                  onClick={() => menuApply(menu.key, false, false)}>
                  <IconChevronUp /> 收缩子树<span className="ird-ctx-note">不含自己</span>
                </button>

                <div className="ird-ctx-sep" />

                <button type="button" className="ird-ctx-item"
                  disabled={!menuTarget.hasChildren}
                  onClick={() => menuApply(menu.key, true, true)}>
                  <IconChevronDown /> 展开自己<span className="ird-ctx-note">含自己</span>
                </button>
                <button type="button" className="ird-ctx-item"
                  disabled={!menuTarget.hasChildren}
                  onClick={() => menuApply(menu.key, true, false)}>
                  <IconChevronUp /> 收缩自己<span className="ird-ctx-note">含自己</span>
                </button>
              </div>
            ) : null}
          </div>

          <div className="wp3-handle" title="拖拽调整树视图宽度"
            onMouseDown={(e) => startDrag(e, treeWidth, setTreeWidth, 200, 640, 1)} />

          {/* 右：检视器 */}
          <div className="ird-inspector">
            {!selectedNode ? (
              <Empty title="请选择左侧节点" description="楼层 / 航点 / 动作点 / 检测框都可以点" />
            ) : (
              <>
                <div className="ird-insp-title">
                  <Tag size="small" color={(KIND_TAG[selectedNode.kind]?.color || 'blue') as TagColorLike}>
                    {KIND_TAG[selectedNode.kind]?.text || selectedNode.kind}
                  </Tag>
                  <span className="ird-insp-name">{selectedNode.label}</span>
                  {selectedNode.tags.map((tag, i) => (
                    <Tag key={i} size="small" color={tag.color as TagColorLike}>{tag.text}</Tag>
                  ))}
                  {/* 动作节点：发起检测按钮 */}
                  {selectedNode.kind === 'action' && selectedNode.action && (
                    <Button
                      size="small" theme="light" type="primary" icon={<IconPlay />}
                      style={{ marginLeft: 'auto' }}
                      onClick={() => handleTriggerDetect(selectedNode.action!)}
                    >
                      发起检测
                    </Button>
                  )}
                </div>

                {groups.map((g) => (
                  <div key={g.title} className="ird-group">
                    <div className="ird-group-title">{g.title}</div>
                    {g.fields.map((f, i) => (
                      <div key={`${f.label}-${i}`} className="ird-field">
                        <span className="ird-field-label">{f.label}</span>
                        {f.image && f.value !== '—' ? (
                          <span
                            className="ird-thumb"
                            style={{ backgroundImage: `url(${f.value})` }}
                            title="点击查看大图"
                            onClick={() => setPreview({
                              visible: true, url: f.value,
                              title: `${selectedNode.label} · ${f.label}`,
                            })}
                          />
                        ) : (
                          <span
                            className={`ird-field-value${f.mono ? ' is-mono' : ''}`
                              + `${f.block ? ' is-block' : ''}${f.danger ? ' is-danger' : ''}`}
                            title={f.block ? undefined : f.value}
                          >
                            {f.value}
                          </span>
                        )}
                      </div>
                    ))}
                  </div>
                ))}

                {/* 图片直接放检视器里，不用再点一层弹窗 —— 看检测框就是要对着图看 */}
                {selectedNode.kind === 'point' && selectedNode.point?.image ? (
                  <div className="ird-group">
                    <div className="ird-group-title">
                      检测图
                      <Button
                        size="small" theme="borderless" type="tertiary"
                        className="ird-img-open"
                        onClick={() => setPreview({
                          visible: true, url: selectedNode.point!.image,
                          title: `${selectedNode.label} · 检测图`,
                        })}
                      >
                        原图
                      </Button>
                    </div>
                    {/*
                      ⚠️ 这里**不能**用 Semi 的 `<Image>`：它外层 `.semi-image` 容器
                      吃 `maxHeight`，里面的 `<img>` 还是按原始宽高比铺，于是"框高
                      maxHeight、图更高"→ 多出来的被裁掉，滚动条拉到底也只看到上 1/3。
                      直接渲染裸 `<img>` + `width:100%`（`height:auto` 跟着宽度走），
                      图就完整撑开、由外层 `.ird-inspector` 统一滚动。
                    */}
                    <img
                      className="ird-figure"
                      src={selectedNode.point.image}
                      alt={`${selectedNode.label} 检测图`}
                      onClick={() => setPreview({
                        visible: true, url: selectedNode.point!.image,
                        title: `${selectedNode.label} · 检测图`,
                      })}
                    />
                  </div>
                ) : null}
                {selectedNode.kind === 'action' && (selectedNode.action?.picture || selectedNode.action?.infrared) ? (
                  <div className="ird-group">
                    <div className="ird-group-title">图片</div>
                    <div style={{ display: 'flex', gap: 8, flexWrap: 'wrap' }}>
                      {[
                        { u: selectedNode.action.picture, l: '可见光' },
                        { u: selectedNode.action.infrared, l: '红外' },
                      ].filter((x) => x.u).map((x) => (
                        <div
                          key={x.l}
                          className="ird-thumb is-big"
                          style={{ backgroundImage: `url(${x.u})` }}
                          title={`点击查看大图 · ${x.l}`}
                          onClick={() => setPreview({
                            visible: true, url: x.u,
                            title: `${selectedNode.label} · ${x.l}`,
                          })}
                        >
                          <span className="ird-thumb-cap">{x.l}</span>
                        </div>
                      ))}
                    </div>
                  </div>
                ) : null}

                {/* 推理留痕：请求参数 / 同步响应(含 HTTP 状态) / 算法回调结果 */}
                {selectedNode.kind === 'action' && selectedNode.action ? (
                  <InferTrace action={selectedNode.action} />
                ) : null}
              </>
            )}
          </div>
        </div>
      )}

      {/* 大图预览：用 Modal 全屏看，图自适应视口 */}
      <Modal
        visible={preview.visible}
        onCancel={() => setPreview({ visible: false, url: '', title: '' })}
        footer={null}
        title={preview.title}
        width="fit-content"
        className="ird-preview"
      >
        <img className="ird-figure is-big" src={preview.url} alt={preview.title} />
      </Modal>
    </div>
  )
}

/** 节点类型 -> 检视器头上的标签。 */
const KIND_TAG: Record<string, { text: string; color: string }> = {
  floor: { text: '楼层', color: 'indigo' },
  waypoint: { text: '航点', color: 'cyan' },
  action: { text: '动作点', color: 'blue' },
  point: { text: '检测框', color: 'violet' },
  notice: { text: '提示', color: 'grey' },
}

/** 推理留痕：请求参数 / 同步响应 / 算法回调结果，三段可折叠 JSON。 */
function InferTrace({ action }: { action: ActionResultRow }) {
  const req = action.infer_request
  const resp = action.infer_response
  const result = action.infer_result
  if (!req && !resp && !result) return null
  const status = resp?.http_status
  return (
    <div className="ird-group">
      <div className="ird-group-title">推理留痕</div>
      <div className="ird-infer">
        {req ? <CollapseJson title="请求参数" data={req} /> : null}
        {resp ? (
          <CollapseJson
            title={`同步响应${status != null ? ` · HTTP ${status}` : ''}`}
            data={resp}
            tone={status != null && status >= 400 ? 'error' : undefined}
          />
        ) : null}
        {result ? (
          <CollapseJson
            title={`算法结果${result?.code != null ? ` · code ${result.code}` : ''}`}
            data={result}
          />
        ) : null}
      </div>
    </div>
  )
}

/** 可折叠 JSON 段，默认展开（用户明确要看请求/响应/结果三段）。 */
function CollapseJson({ title, data, tone }: {
  title: string
  data: any
  tone?: 'error'
}) {
  const [open, setOpen] = useState(true)
  return (
    <div className={`ird-infer-item${tone === 'error' ? ' is-error' : ''}`}>
      <button type="button" className="ird-infer-head" onClick={() => setOpen((v) => !v)}>
        {open ? <IconChevronDown /> : <IconChevronUp />}
        <span>{title}</span>
      </button>
      {open ? <pre className="ird-infer-json">{prettyJson(data)}</pre> : null}
    </div>
  )
}

function prettyJson(data: any): string {
  try {
    return JSON.stringify(data, null, 2)
  } catch {
    return String(data)
  }
}

/**
 * 树行：label + 状态标签 + 右侧计数。
 *
 * ⚠️ 这里不能直接用 Semi `Tree` 的 `renderLabel` 拿 `node` 的业务字段（它会包一层），
 * 所以建 `treeData` 时把原始节点塞进 `__raw`（见 `toSemiTree`）。
 *
 * ⚠️ `data-ird-key` 是**右键菜单的锚点**：右键往往落在内层 `<span>` 上，
 * `onContextMenu` 里靠 `closest('[data-ird-key]')` 往上找才能拿到是哪个节点。
 * 漏了这一行，右键会"弹不出菜单"（找不到目标节点就 return 了）。
 */
function TreeLabel({ node, text }: { node: LogTreeNode; text: React.ReactNode }) {
  const isNotice = node.kind === 'notice'
  return (
    <span
      className={`ird-node${isNotice ? ' is-notice' : ''}`}
      data-ird-key={node.key}
    >
      <span className="ird-node-label">{text}</span>
      {node.tags.map((tag, i) => (
        <Tag
          key={i}
          size="small"
          color={tag.color as TagColorLike}
          className="ird-node-tag"
        >
          {tag.text}
        </Tag>
      ))}
      {node.meta ? <span className="ird-node-meta">{node.meta}</span> : null}
    </span>
  )
}

/**
 * 业务树 -> Semi `Tree` 的 `treeData`。
 *
 * `renderLabel` 拿到的是 Semi 处理过的节点对象，**取不到我们的业务字段**（tag / meta），
 * 所以把原始节点挂在 `__raw` 上带过去。label 里只放纯文字，状态标签由 `renderLabel`
 * 用 `__raw.tag` 渲染成带颜色的 `Tag` —— 拼成字符串就丢了颜色。
 */
function toSemiTree(nodes: LogTreeNode[]): any[] {
  return nodes.map((n) => ({
    key: n.key,
    label: n.label,
    value: n.key,
    __raw: n,
    children: n.children.length ? toSemiTree(n.children) : undefined,
  }))
}
