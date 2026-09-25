/**
 * 轨道地图（画布）。
 *
 * 背景：挂轨机器人是**单轴**的，航点的 `x` 是「沿轨弧长」(m)，`y` 恒为 0，
 * 系统里并不存在真实的二维地图。所以这里的"地图"是一张**二维可视化图**。
 *
 * ## 轨道是独立数据，不是航点算出来的
 *
 * 轨道在航点树里是一条条真实的 `TrackNode`，children 里**平铺**着
 * `TrackEndpointNode`（端点）与 `TrackControlNode`（控制点），靠顺序表达
 * 路径走向。它不挂在组件内部状态里，因此能被树编辑、导入导出与版本化。
 * 本组件只负责**渲染与绘制交互**，所有写回都通过回调交给上层落到 spec。
 *
 * 平铺 -> 曲线的解析规则见 `trackGeometry.ts` 的 `parseTrackNodes`：
 * 两段端点之间夹着的控制点归属于这一段，0/1/2 个分别对应直线 / 二次 / 三次。
 *
 * ## 交互
 *
 * - **绘制轨道**工具：左键点击空白处 = 追加一个端点（与前一点之间是直线）；
 *   左键**按住拖拽** = 追加端点 + 拖出一个控制点（该段变曲线）。
 *   已有点（端点/控制点）可直接拖动微调。
 * - **选择**工具：点选 / Shift 加选 / 框选航点与沿轨设施；在轨道上右键可添加
 *   航点 / 充电桩 / RFID 卡。
 * - 视口：滚轮缩放（以鼠标为锚点）、中键 / 空格+左键 / **右键拖拽**平移、适应窗口。
 */
import { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import { Button, Checkbox, Dropdown, Toast, Tooltip } from '@douyinfe/semi-ui'
import {
  IconHandle, IconEdit, IconPlus, IconRefresh, IconDelete,
  IconMinus, IconExpand, IconAppCenter, IconEyeOpened, IconEyeClosed, IconImage,
} from '@douyinfe/semi-icons'
import {
  sampleTrack, pointAtFraction,
  hitTrack, nearestU, rectsIntersect, normalizeRect, distToSegment,
  worldToScreen, screenToWorld, panFrom, isDrag, zoomAt, fitViewport, boundsOf,
  parseTrackNodes, trackPointsFromNodes, backgroundRect, backgroundScaleAt,
  sectionRange, sectionPoints,
  pixelTolerance, niceStep, formatLength, spanText, xToU, uToX, trackLengthOf,
  MIN_SCALE, MAX_SCALE,
  type MapWaypoint, type MapMarker, type MarkerKind, type MapBackground, type MapSection,
  type MapIcon, type Pt, type Rect, type TrackNodePoint, type Viewport,
} from './trackGeometry'
import {
  drawIcon, iconLabel, normalizeIconSize, DEFAULT_ICON_COLOR, DEFAULT_ICON_SIZE,
} from './mapIcons'
import {
  applyPickMode, resolvePickMode, PICK_MODES, PICK_MODE_LABEL, PICK_MODE_HINT,
  type PickMode,
} from '../utils/marqueeSelect'

export type MapTool = 'select' | 'draw'

/**
 * 靠近轨道的容差（屏幕像素）：右键落在这里才认为"有东西可操作"。
 *
 * 判定"值不值得弹菜单"与"菜单项实际执行"必须用**同一个**容差，
 * 否则会出现菜单弹出来了、点下去却提示"请右键点击轨道"的矛盾。
 */
const NEAR_TRACK_PX = 14
/** 右键按下后位移超过这个像素数才算"拖拽"，否则视为原地点击 */
const DRAG_THRESHOLD = 3
/** 拖动画布上已有点时，命中判定的屏幕半径 */
const NODE_HIT_PX = 9
/** 背景图右下角缩放手柄的命中半径（屏幕像素） */
const BG_HANDLE_PX = 10
/** 背景图缩放下限：再小就成一个点，拖歪了找不回来 */
const BG_MIN_SCALE = 0.001
/**
 * 刻度数字文本：去掉浮点尾巴。
 * `i * step` 在 step 为 0.2 这类值上会算出 `0.6000000000000001`，
 * 直接塞进模板字符串会把一长串小数画到画布上。
 */
const tickText = (v: number): string => String(Number(v.toFixed(3)))

/**
 * 正在拖拽的东西是哪一类（决定"松手时按什么坐标回写"）。
 *
 * - `track`：轨道端点 / 控制点 —— **世界坐标**，只在绘制工具下可拖
 * - `waypoint` / `marker` / `section`：挂在轨道上的 —— **沿轨弧长 u**（松手再换算成 x）
 * - `icon`：图标标记 —— **世界坐标**，不吸附轨道
 */
type MoveKind = 'track' | 'waypoint' | 'marker' | 'section' | 'icon'

/** 地图图层：`waypoint` 是航点，`background` 是底图，`section` 是区段标记，
 *  `icon` 是图标标记，其余两种沿轨设施与 `MarkerKind` 同名 */
export type MapLayerKey = 'waypoint' | 'background' | 'section' | 'icon' | MarkerKind
const LAYER_ITEMS: { key: MapLayerKey; label: string }[] = [
  { key: 'waypoint', label: '航点' },
  { key: 'charging', label: '充电桩' },
  { key: 'rfid', label: 'RFID 卡' },
  { key: 'section', label: '区段标记' },
  { key: 'icon', label: '图标' },
]
/**
 * 背景图单独一项：只有树里真的有 `BackgroundImageNode` 时才出现在下拉里。
 * 没有底图时勾它毫无意义（还会让"显示 N/M"看着像少画了东西）。
 */
const BG_LAYER_ITEM: { key: MapLayerKey; label: string } = { key: 'background', label: '背景图' }
/** 图层全关时的空数组常量：用同一个引用，免得每次渲染都造新数组触发重算 */
const EMPTY_WAYPOINTS: MapWaypoint[] = []
const EMPTY_SECTIONS: MapSection[] = []
const EMPTY_ICONS: MapIcon[] = []

interface Props {
  /** 航点列表（已带上 path / x / label），按 x 归一化后铺在当前轨道上 */
  waypoints: MapWaypoint[]
  /** 树中被选中的节点路径集合，用于高亮 */
  selectedPaths: Set<string>
  /** 点选/框选结果回写（调用方通常是树的 nodeSel） */
  onSelectionChange: (paths: Set<string>) => void
  /**
   * 当前轨道的平铺节点（端点 + 控制点，按 children 顺序）。
   * **受控**：组件不再自己持有轨道，改由上层从 TrackNode 读出来传入。
   */
  trackNodes: TrackNodePoint[]
  /** 当前轨道名（显示在角标），便于确认自己在编辑哪一条 */
  trackName?: string
  /** 共有几条轨道 */
  trackCount?: number
  /** 新建一条轨道 */
  onCreateTrack?: () => void
  /** 追加一个端点（世界坐标）；与前一端点之间为直线段 */
  onAddEndpoint?: (p: Pt) => void
  /** 追加"控制点 + 端点"（世界坐标）；顺序由上层决定，控制点要落在端点之前 */
  onAddEndpointWithControl?: (control: Pt, endpoint: Pt) => void
  /** 移动已有的端点/控制点 */
  onMovePoint?: (path: string, p: Pt) => void
  /** 清空当前轨道（删掉它下面所有端点与控制点） */
  onClearTrack?: () => void
  /** 需要新增一个航点（在轨道某处右键），u 为归一化位置 */
  onAddWaypoint?: (u: number) => void
  /**
   * 拖动航点改它的 `x`（**沿轨弧长，已由 u 换算好**）。
   *
   * 与 `onMovePoint` 的区别：那个是绘制工具下拖轨道端点/控制点（世界坐标，米）。
   *
   * u 反推 x 用的量程是**轨道总长 (m)**，与航点自身数据无关，所以哪怕只剩
   * 一个航点也照样算得出米数——不存在"值域退化反推不出来"的情况。
   */
  onMoveWaypoint?: (path: string, x: number) => void
  /**
   * 沿轨设施：充电桩 / RFID 卡。与航点共用 `x`（弧长）定位，
   * 只是形状不同（方形=充电桩、菱形=RFID）。
   */
  markers?: MapMarker[]
  /** 在轨道某处右键新增沿轨设施，u 为归一化位置 */
  onAddMarker?: (kind: MarkerKind, u: number) => void
  /**
   * 拖动沿轨设施改它的 `x`（**沿轨弧长，已由 u 换算好**）。
   *
   * u -> x 的换算在地图里做：量程（轨道总长 `lengthM`）是地图算的，上层拿不到，
   * 交给上层换算只会导致"地图按一把尺子画、写回按另一把算"的错位。
   */
  onMoveMarker?: (path: string, x: number) => void
  /**
   * 沿轨区段标记（门 / 窗 / 减速…）：`x ± 半径` 的一段弧长，
   * 画成贴在轨道曲线上的彩色带。与航点/设施共用同一把尺子（米）。
   */
  sections?: MapSection[]
  /** 在轨道某处右键新增区段标记，u 为归一化位置 */
  onAddSection?: (u: number) => void
  /** 拖动区段标记改它的**中心** `x`（半径保持不变，只是整段挪位置） */
  onMoveSection?: (path: string, x: number) => void
  /**
   * 让机器人走到轨道某处（u 为归一化位置）。
   *
   * 上层负责把 u 换算成米再下发——`uToX(轨道总长, u)` 与新增航点共用同一把
   * 尺子（`trackLengthOf`），免得地图按一套长度画、下发按另一套算。
   */
  onMoveRobot?: (u: number) => void
  /**
   * 图标标记：地图**任意位置**（世界坐标 x/y）放一个内置矢量图标。
   *
   * 与区段/设施不同，它不吸附轨道——没有轨道、或想标在背景图某个房间里时也能用。
   */
  icons?: MapIcon[]
  /** 在地图任意处右键新增图标标记（世界坐标） */
  onAddIcon?: (world: Pt) => void
  /** 拖动图标标记改它的世界坐标（不吸附轨道） */
  onMoveIcon?: (path: string, world: Pt) => void
  /**
   * 地图背景图（可选，整张地图一张）。
   *
   * 它铺在**最底层**，照着它摆轨道 / 航点。定位用「锚点 + 缩放」：
   * `x/y` 是图片**左上角**的世界坐标，`scale` 是 1 图片像素等于多少米
   * （图片按自身宽高 × scale 铺开，不拉伸变形）。
   */
  background?: MapBackground | null
  /**
   * 背景图微调写回（拖动整张图改 x/y，拖右下角手柄改 scale）。
   * 只传真正变了的字段；`src` / `opacity` 留给检视器改。
   */
  onBackgroundChange?: (patch: { x?: number; y?: number; scale?: number }) => void
  /** 上传 / 更换背景图（图片从哪来由上层决定） */
  onPickBackground?: () => void
  /** 双击航点定位（例如滚动树到该节点） */
  onLocate?: (path: string) => void
  /**
   * **只读挑选模式**：只保留「选择 + 框选 + 缩放」，藏掉绘制轨道 / 图层 / 背景图
   * 这些编辑入口，右键也不再弹"在此添加…"菜单。
   *
   * 给"从地图上挑几个航点"这类场景用（例如巡检计划编排的「航点指定」面板）。
   * 不做这个开关的话，面板里会摆出一排**点了没反应**的按钮——比没有按钮更糟。
   */
  pickerMode?: boolean
  height?: number
}

/* ---------------------------------------------------------------- 组件 */

export default function TrackMap({
  waypoints,
  selectedPaths,
  onSelectionChange,
  trackNodes,
  trackName,
  trackCount = 0,
  onCreateTrack,
  onAddEndpoint,
  onAddEndpointWithControl,
  onMovePoint,
  onClearTrack,
  onAddWaypoint,
  onMoveWaypoint,
  markers = [],
  onAddMarker,
  onMoveMarker,
  sections = [],
  onAddSection,
  onMoveSection,
  onMoveRobot,
  icons = [],
  onAddIcon,
  onMoveIcon,
  background = null,
  onBackgroundChange,
  onPickBackground,
  onLocate,
  pickerMode = false,
  height = 260,
}: Props) {
  const canvasRef = useRef<HTMLCanvasElement>(null)
  const wrapRef = useRef<HTMLDivElement>(null)

  const [tool, setTool] = useState<MapTool>('select')
  const [size, setSize] = useState({ w: 800, h: height })
  /** 框选中的矩形（画布坐标） */
  const [marquee, setMarquee] = useState<Rect | null>(null)
  const [hoverPath, setHoverPath] = useState<string | null>(null)
  /**
   * 拖动已有点时的**本地预览**：path -> 新坐标。
   *
   * 拖动期间只改这里（不写 spec），松手才 `onMovePoint` 提交一次。
   * 否则每帧都要深拷贝整棵 spec 并触发全树重渲染，拖起来会顿。
   */
  const [draft, setDraft] = useState<Record<string, Pt>>({})
  /**
   * 拖**挂在轨道上的东西**（航点 / 充电桩 / RFID / 区段）时的预览：path -> 新 u。
   *
   * 与 `draft` 分开是因为量纲不同：那三类最终要的是**弧长 x**（一维），
   * 而轨道端点与图标要的是**世界坐标**（二维）。混在一个 map 里，
   * 松手时就得靠"这个 path 到底是哪种节点"去猜该按哪个字段读——猜错就是静默错位。
   */
  const [draftU, setDraftU] = useState<Record<string, number>>({})
  /** 正在拖拽的已有点 */
  const [movingPath, setMovingPath] = useState<string | null>(null)
  /** 正在拖的是哪一类东西（松手时决定按什么坐标回写） */
  const [movingKind, setMovingKind] = useState<MoveKind | null>(null)
  /**
   * 正在"拉"出来的新段预览：锚点（将成为端点）+ 可选控制点（世界坐标）。
   * 与 draft 同理，松手才提交。
   */
  const [pending, setPending] = useState<{ anchor: Pt; control: Pt | null } | null>(null)

  /** 拖动光标用的重绘计数器：平移起止只改 ref，视觉状态靠它推进 */
  const [cursorTick, setCursorTick] = useState(0)

  /**
   * 2D 视口。初始值是个占位，等拿到真实画布尺寸后由 fitViewport 适配一次
   * （用 `fittedRef` 保证只在首次/显式"适应窗口"时重置，不然后续任何
   * 依赖变化都会把用户的缩放平移冲掉）。
   */
  const [vp, setVp] = useState<Viewport>({ scale: 1, offset: { x: 0, y: 0 } })
  const panning = useRef(false)
  /**
   * 右键菜单（画布坐标，null 表示未打开）。
   *
   * 必须用 state 而不是 ref：它在**原地右键松手**时才写入，而松手这个动作
   * 本身不一定会引起别的渲染（视口一像素没动），用 ref 的话菜单永远不出现。
   */
  const [ctxMenu, setCtxMenu] = useState<Pt | null>(null)

  /**
   * 图层开关：控制地图里画哪些东西（航点 / 充电桩 / RFID 卡）。
   *
   * 只影响**显示与可交互性**（隐藏的图层不画、也点不中），不动 spec。
   * 注意隐藏航点时**不能改变量程**（轨道总长米数）——否则桩/卡会跟着挪位置，
   * "关掉一个图层结果别的都跑了"是最让人困惑的一类 bug。
   */
  const [layers, setLayers] = useState<Record<MapLayerKey, boolean>>({
    waypoint: true, background: true, section: true, icon: true, charging: true, rfid: true,
  })
  const [layerOpen, setLayerOpen] = useState(false)
  const toggleLayer = (key: MapLayerKey) =>
    setLayers((prev) => ({ ...prev, [key]: !prev[key] }))
  /** 下拉里实际列出的图层：没有背景图节点时不给"背景图"这一项 */
  const layerItems = useMemo(
    () => (background ? [...LAYER_ITEMS, BG_LAYER_ITEM] : LAYER_ITEMS),
    [background],
  )

  const marqueeStart = useRef<Pt | null>(null)
  const panStart = useRef<{ screen: Pt; vp: Viewport } | null>(null)

  /**
   * 框选的**基准模式**（工具栏上选的），与本次拖拽的**实际模式**分开：
   *
   * - `pickMode`（state）：工具栏上那个"替换 / 增加 / 移除"开关的当前值；
   * - `marqueeMode`（ref）：本次拖拽真正生效的模式 = 按住 Shift/Alt 时被临时覆盖
   *   的结果。它必须存 ref 而不是 state——mousedown 里算出来、mousemove 里读，
   *   中间隔着一次 setState 的话读到的是**上一帧**的值（第一次拖拽会串味）。
   */
  const [pickMode, setPickMode] = useState<PickMode>('replace')
  const marqueeMode = useRef<PickMode>('replace')
  /**
   * 按下那一刻的选择快照（框选合并的基准，见 `marqueeSelect` 的文件头）。
   *
   * 存 ref 同理：拖拽途中 `selectedPaths` 一直在被我们自己的 `onSelectionChange`
   * 改，实时读它会让"增加"越框越多、"移除"把刚去掉的又加回来。
   */
  const marqueeBase = useRef<Set<string>>(new Set())
  const fittedRef = useRef(false)
  /** 按住空格时左键 = 平移（与画图工具一致的肌肉记忆） */
  const panModifier = useRef(false)

  /**
   * 右键手势的三个状态（一起出现、一起清理）。
   *
   * 规则刻意做得简单可预测：
   * - **任何位置**右键按下都先"预备平移"，拖过阈值就真的平移；
   * - **原地松手**（没拖过）且按下处有可操作对象，才弹菜单。
   */
  const press = useRef<{ screen: Pt; vp: Viewport; onTarget: boolean } | null>(null)
  /** 右键按下后是否已经拖过阈值（决定松手时弹不弹菜单） */
  const pressMoved = useRef(false)
  /** 绘制工具下"按下但还没决定是点击还是拖拽"的起点（画布坐标） */
  const drawStart = useRef<Pt | null>(null)

  /* 空格键切换平移态。用 keydown/keyup 跟踪，blur 时清掉避免卡住。 */
  useEffect(() => {
    const down = (e: KeyboardEvent) => { if (e.code === 'Space') panModifier.current = true }
    const up = (e: KeyboardEvent) => { if (e.code === 'Space') panModifier.current = false }
    const clear = () => { panModifier.current = false }
    window.addEventListener('keydown', down)
    window.addEventListener('keyup', up)
    window.addEventListener('blur', clear)
    return () => {
      window.removeEventListener('keydown', down)
      window.removeEventListener('keyup', up)
      window.removeEventListener('blur', clear)
    }
  }, [])

  /* ---- 尺寸自适应：容器多大画布就多大，并处理 DPR 保证高清 ---- */
  useEffect(() => {
    const el = wrapRef.current
    if (!el) return
    const apply = () => {
      const w = Math.max(240, el.clientWidth)
      setSize({ w, h: height })
    }
    apply()
    const ro = new ResizeObserver(apply)
    ro.observe(el)
    return () => ro.disconnect()
  }, [height])

  /* ---- 轨道：受控节点 + 本地拖动预览 ---- */

  /** 把拖动预览叠到受控节点上（拖动中看到的即时反馈） */
  const nodes = useMemo<TrackNodePoint[]>(
    () => trackNodes.map((n) => {
      const d = draft[n.path]
      return d ? { ...n, x: d.x, y: d.y } : n
    }),
    [trackNodes, draft],
  )

  const parsed = useMemo(() => parseTrackNodes(nodes), [nodes])
  const trackPts = useMemo(() => trackPointsFromNodes(nodes), [nodes])
  /** 成环时必须额外采样"末点 -> 首点"那一段，否则环是断的 */
  const sampled = useMemo(() => sampleTrack(trackPts, 48, parsed.closed), [trackPts, parsed.closed])

  /** 轨道是否真的能画出来（至少 2 个端点才有段） */
  const hasTrack = sampled.pts.length >= 2 && sampled.total > 0

  /** 按图层开关过滤后的可见集合（隐藏的图层既不画也点不中） */
  const shownWaypoints = useMemo(
    () => (layers.waypoint ? waypoints : EMPTY_WAYPOINTS),
    [layers.waypoint, waypoints],
  )
  const shownMarkers = useMemo(
    () => markers.filter((m) => layers[m.kind]),
    [markers, layers],
  )
  const shownIcons = useMemo(
    () => (layers.icon ? icons : EMPTY_ICONS),
    [layers.icon, icons],
  )
  const shownSections = useMemo(
    () => (layers.section ? sections : EMPTY_SECTIONS),
    [layers.section, sections],
  )

  /* ---- 背景图 ----

     整张地图一张底图（树里的 `BackgroundImageNode`），铺在**最底层**当描图参考。
     定位用「锚点 + 缩放」：`x/y` 是图片**左上角**的世界坐标，`scale` 是
     "1 图片像素 = 多少米"——图片按自身宽高 × scale 铺开，永不拉伸变形。

     微调只在这张图**被选中**时才生效：否则点一下空白想框选，结果把底图拖走了，
     是非常恼人的一类误操作。

     这一段必须排在 `contentBounds` 之前——"适应窗口"要把底图一并框进来。 */

  /** 拖动中的本地预览（松手才提交一次），与拖动轨道点同理 */
  const [bgDraft, setBgDraft] = useState<MapBackground | null>(null)
  const bgDrag = useRef<{ mode: 'move' | 'scale'; start: Pt; origin: MapBackground } | null>(null)
  /** 指针在背景图上的位置（只影响光标形状） */
  const [bgHover, setBgHover] = useState<'move' | 'scale' | null>(null)

  /** 实际生效的参数：拖动预览优先，这样拖动中就能看到即时反馈 */
  const bgLive = bgDraft ?? background
  /** 是否被"激活"：选中了它这个节点 + 选择工具。激活后才能在图上拖 */
  const bgActive = !!bgLive && tool === 'select' && selectedPaths.has(bgLive.path)

  /** 图片对象：`src` 变了（或图层关掉）才重新加载 */
  const [bgImage, setBgImage] = useState<HTMLImageElement | null>(null)
  useEffect(() => {
    const src = background?.src?.trim()
    if (!src || !layers.background) { setBgImage(null); return }
    let alive = true
    const img = new Image()
    img.onload = () => { if (alive) setBgImage(img) }
    img.onerror = () => { if (alive) setBgImage(null) }
    img.src = src
    return () => { alive = false }
  }, [background?.src, layers.background])

  /** 背景图在世界坐标里的矩形（图片没加载出来时算不出来） */
  const bgRect = useMemo<Rect | null>(() => {
    if (!bgImage || !bgLive) return null
    return backgroundRect(bgLive, bgImage.naturalWidth, bgImage.naturalHeight)
  }, [bgImage, bgLive])

  /** 不透明度：夹进 (0,1]——0 就是完全看不见，等于白加一张图 */
  const bgAlpha = (() => {
    const o = Number(bgLive?.opacity)
    if (!Number.isFinite(o)) return 0.5
    return Math.min(1, Math.max(0.02, o))
  })()

  /** 背景图矩形（屏幕坐标）：命中测试与缩放手柄都以它为准 */
  const bgScreenRect = useMemo<Rect | null>(() => {
    if (!bgRect || !layers.background) return null
    return normalizeRect(
      worldToScreen(vp, { x: bgRect.x, y: bgRect.y }),
      worldToScreen(vp, { x: bgRect.x + bgRect.w, y: bgRect.y + bgRect.h }),
    )
  }, [bgRect, layers.background, vp])

  /** 是否真的画得出来（有图 + 算得出矩形 + 图层开着） */
  const bgVisible = !!bgImage && !!bgRect && layers.background

  /** 命中右下角缩放手柄 */
  const hitBgHandle = useCallback((pt: Pt): boolean => {
    if (!bgActive || !bgScreenRect) return false
    const c = { x: bgScreenRect.x + bgScreenRect.w, y: bgScreenRect.y + bgScreenRect.h }
    return Math.hypot(c.x - pt.x, c.y - pt.y) <= BG_HANDLE_PX
  }, [bgActive, bgScreenRect])

  /** 命中图片内部（拖动整张图） */
  const hitBgInside = useCallback((pt: Pt): boolean => {
    if (!bgActive || !bgScreenRect) return false
    const { x, y, w, h } = bgScreenRect
    return pt.x >= x && pt.x <= x + w && pt.y >= y && pt.y <= y + h
  }, [bgActive, bgScreenRect])

  /**
   * **里程 (m)**：沿轨弧长 x ↔ 归一化位置 u 之间唯一的换算量程。
   *
   * 有轨道时 = 曲线采样出来的弧长——世界坐标就是米，所以采样弧长直接就是
   * 轨道真实长度；闭合轨道的收口段也被 `sampleTrack(…, closed)` 采样进去了，
   * 不会少算一截。没画轨道时退回兜底量程，免得 `xToU` 一律给 0、点全堆在原点。
   *
   * 航点 / 充电桩 / RFID / 区段**共用这一个量程**，它们才会在同一把尺子上对齐。
   */
  const lengthM = useMemo(
    () => trackLengthOf(
      hasTrack ? sampled.total : 0,
      [...waypoints.map((w) => w.x), ...markers.map((m) => m.x)],
    ),
    [hasTrack, sampled, waypoints, markers],
  )

  /**
   * 提示栏里的"轨道总长"。没画轨道时显示 `—`（此时没有长度可言）。
   * 另外把航点弧长区间一并显示，方便和刻度互相印证。
   */
  const lengthText = formatLength(hasTrack ? sampled.total : 0)
  const meterSpan = useMemo(
    () => spanText(waypoints.map((w) => w.x)),
    [waypoints],
  )

  /**
   * 世界坐标系下需要被"适应窗口"覆盖的点：曲线采样点 + 航点。
   * 没有轨道时用航点的退化排布兜底，否则首次 fit 会把视口缩到极小。
   */
  const contentBounds = useMemo(() => {
    // 背景图也算进"内容范围"：否则加了底图再点「适应窗口」，底图会被甩到视野外，
    // 用户只会以为"底图没加上"
    // 图标也算进"内容范围"：它们是**任意位置**摆的，很可能离轨道很远，
    // 不纳进来的话点「适应窗口」会把图标甩到视野外，用户只会以为没加上
    const iconPts: Pt[] = shownIcons
      .filter((i) => Number.isFinite(i.x) && Number.isFinite(i.y))
      .map((i) => ({ x: i.x, y: i.y }))
    const extra: Pt[] = (bgVisible && bgRect)
      ? [{ x: bgRect.x, y: bgRect.y }, { x: bgRect.x + bgRect.w, y: bgRect.y + bgRect.h }, ...iconPts]
      : iconPts
    if (hasTrack) return boundsOf([...sampled.pts, ...extra])
    const xs = shownWaypoints.map((w) => w.x).filter((v) => Number.isFinite(v))
    if (!xs.length && !extra.length) return null
    // 退化水平线上，航点的横坐标就是它的弧长米数（夹到量程内）
    return boundsOf([
      ...xs.map((x) => ({ x: Math.max(0, Math.min(x, lengthM)), y: 0 })),
      ...extra,
    ])
  }, [hasTrack, sampled, shownWaypoints, bgVisible, bgRect, shownIcons, lengthM])

  /** 适应窗口：把整条轨道装进画布 */
  const fitToContent = useCallback(() => {
    if (!contentBounds) return
    // 纵向留一点空间，避免直线轨道（h=0）被放大到离谱的倍率
    const b = contentBounds.h < 1e-6
      ? { ...contentBounds, y: contentBounds.y - 120, h: 240 }
      : contentBounds
    setVp(fitViewport(b, size, 46))
  }, [contentBounds, size])

  /** 首次拿到尺寸后自动适应一次（之后不再自动，避免打断用户操作） */
  useEffect(() => {
    if (fittedRef.current) return
    if (!size.w || !contentBounds) return
    fittedRef.current = true
    fitToContent()
  }, [size, contentBounds, fitToContent])

  /* ---- 航点坐标：按 u 落到轨道上，再经视口投影到屏幕 ---- */

  const placed = useMemo(() => {
    return shownWaypoints.map((w) => {
      // 拖动预览优先：draftU 是"指针在轨道上的投影"，直接用它重算落点
      const u = draftU[w.path] ?? xToU(lengthM, w.x)
      // 没有轨道时退化成一条水平线，至少让航点还在图上（而不是全部堆在原点）
      const q = hasTrack
        ? pointAtFraction(sampled, u)
        : { x: u * lengthM, y: 0, angle: 0 }
      return {
        ...w,
        u,
        world: { x: q.x, y: q.y },
        canvas: worldToScreen(vp, q),
        angle: q.angle,
      }
    })
  }, [shownWaypoints, sampled, vp, hasTrack, draftU, lengthM])

  /**
   * 沿轨设施（充电桩 / RFID 卡）的落位。
   *
   * **必须与航点共用同一个量程 `lengthM`**：各用一把尺子的话，桩/卡会跑到
   * 完全不相关的位置上去（试过——桩落在了轨道另一头）。
   * 量程为 0（没画轨道也没有任何沿轨点）时 `xToU` 给 0，至少都停在起点而不是 NaN。
   */
  const placedMarkers = useMemo(() => {
    return shownMarkers.map((m) => {
      const u = draftU[m.path] ?? xToU(lengthM, m.x)
      const q = hasTrack
        ? pointAtFraction(sampled, u)
        : { x: u * lengthM, y: 0, angle: 0 }
      return { ...m, u, world: { x: q.x, y: q.y }, canvas: worldToScreen(vp, q) }
    })
  }, [shownMarkers, lengthM, sampled, vp, hasTrack, draftU])

  /**
   * 区段标记的落位。
   *
   * 与充电桩/RFID 卡**共用同一个量程 `lengthM`**：区段标的是"这一段轨道"，
   * 各用一把尺子的话，"这一段是门"会标到轨道别的地方去。
   * 没有轨道时退化成水平线上的一段（至少还看得见）。
   */
  const placedSections = useMemo(() => {
    type Placed = MapSection & {
      u0: number
      u1: number
      /** 曲线上的世界坐标点（画带子用） */
      world: Pt[]
      /** 对应的屏幕点（命中测试用） */
      canvas: Pt[]
      center: Pt
      centerCanvas: Pt
    }
    const out: Placed[] = []
    if (!(lengthM > 0)) return out
    for (const s of shownSections) {
      const r = sectionRange(lengthM, s)
      if (!r) continue
      /**
       * 拖动区段 = 挪**中心**，半径（在 u 上占的半宽）保持不动：
       * 用户拖的是"这一段整体往哪儿去"，不是"把它拉长"。
       * 半宽按拖动**前**的区间算，免得每帧重算把漂移累积进去。
       */
      const du = draftU[s.path]
      const range = du == null
        ? r
        : (() => {
          const half = (r.u1 - r.u0) / 2
          return { u0: du - half, u1: du + half }
        })()
      const world = hasTrack
        ? sectionPoints(sampled, range.u0, range.u1)
        : [{ x: range.u0 * lengthM, y: 0 }, { x: range.u1 * lengthM, y: 0 }]
      const canvas = world.map((p) => worldToScreen(vp, p))
      const mid = world[Math.floor(world.length / 2)]
      out.push({ ...s, ...range, world, canvas, center: mid, centerCanvas: worldToScreen(vp, mid) })
    }
    return out
  }, [shownSections, lengthM, sampled, vp, hasTrack, draftU])

  /**
   * 图标标记的落位：**不吸附轨道**，直接按世界坐标 x/y 放。
   *
   * 这是图标与区段/设施的根本区别——它标的是"地图上的这个位置"
   * （比如背景图里的某个房间），不是"轨道上的这一段"。
   */
  const placedIcons = useMemo(() => {
    return shownIcons
      .filter((i) => Number.isFinite(i.x) && Number.isFinite(i.y))
      .map((i) => {
        const d = draft[i.path]
        const p = d ? { x: d.x, y: d.y } : { x: i.x, y: i.y }
        return { ...i, x: p.x, y: p.y, canvas: worldToScreen(vp, p) }
      })
  }, [shownIcons, vp, draft])

  /* ---- 绘制 ---- */
  useEffect(() => {
    const cv = canvasRef.current
    if (!cv) return
    const ctx = cv.getContext('2d')
    if (!ctx) return

    const dpr = window.devicePixelRatio || 1
    cv.width = Math.round(size.w * dpr)
    cv.height = Math.round(size.h * dpr)
    cv.style.width = `${size.w}px`
    cv.style.height = `${size.h}px`
    ctx.setTransform(dpr, 0, 0, dpr, 0, 0)

    const cs = getComputedStyle(document.documentElement)
    const v = (n: string, fb: string) => cs.getPropertyValue(n).trim() || fb
    const C = {
      bg: v('--semi-color-bg-2', '#fff'),
      grid: 'rgba(100,122,148,.16)',
      axis: 'rgba(100,122,148,.42)',
      track: v('--semi-color-primary', '#0064fa'),
      trackGlow: 'rgba(0,100,250,.14)',
      text: v('--semi-color-text-0', '#1c1f23'),
      text2: v('--semi-color-text-2', '#8f959e'),
      wp: v('--semi-color-success', '#00b42a'),
      wpSel: v('--semi-color-primary', '#0064fa'),
      wpStroke: v('--semi-color-bg-2', '#fff'),
      handle: v('--semi-color-warning', '#ff7d00'),
      handleLine: 'rgba(255,125,0,.55)',
      node: v('--semi-color-primary', '#0064fa'),
      sel: v('--semi-color-primary', '#0064fa'),
      preview: 'rgba(0,100,250,.55)',
      // 沿轨设施：充电桩用 warning（与"电"的直觉一致），RFID 用 info/紫蓝，
      // 都不写死颜色，暗色主题下跟着 token 走
      pile: v('--semi-color-warning', '#ff7d00'),
      rfid: v('--semi-color-violet', '#7c3aed'),
    }

    ctx.clearRect(0, 0, size.w, size.h)
    // 画布底色用 Theme token，避免写死颜色在暗色主题下刺眼
    ctx.fillStyle = C.bg
    ctx.fillRect(0, 0, size.w, size.h)

    const W = size.w
    const H = size.h
    /** 世界 -> 屏幕；绘制里到处要用，抽成局部函数 */
    const S = (p: Pt) => worldToScreen(vp, p)

    /* --- 背景图：铺在网格与轨道之下，当描图参考 --- */
    if (bgVisible && bgRect && bgImage) {
      const a = S({ x: bgRect.x, y: bgRect.y })
      const b = S({ x: bgRect.x + bgRect.w, y: bgRect.y + bgRect.h })
      ctx.save()
      ctx.globalAlpha = bgAlpha
      ctx.imageSmoothingEnabled = true
      ctx.drawImage(bgImage, a.x, a.y, b.x - a.x, b.y - a.y)
      ctx.restore()

      /**
       * 激活态（选中了背景图节点）才描边 + 画缩放手柄。
       * 半透明底图与网格混在一起时看不出边界，没有这个框就无从下手拖动。
       */
      if (bgActive) {
        ctx.save()
        ctx.strokeStyle = C.sel
        ctx.lineWidth = 1.5
        ctx.setLineDash([6, 4])
        ctx.strokeRect(a.x, a.y, b.x - a.x, b.y - a.y)
        ctx.setLineDash([])
        // 右下角缩放手柄
        ctx.beginPath()
        ctx.arc(b.x, b.y, 4.5, 0, Math.PI * 2)
        ctx.fillStyle = C.wpStroke
        ctx.fill()
        ctx.strokeStyle = C.sel
        ctx.lineWidth = 1.5
        ctx.stroke()
        ctx.restore()
      }
    }

    /* --- 二维网格：步长随缩放自适应，保证屏显密度稳定 --- */
    const step = niceStep(vp, 88)
    // 可见世界范围（屏幕四角反投影）
    const tl = screenToWorld(vp, { x: 0, y: 0 })
    const br = screenToWorld(vp, { x: W, y: H })
    const i0 = Math.floor(tl.x / step)
    const i1 = Math.ceil(br.x / step)
    const j0 = Math.floor(tl.y / step)
    const j1 = Math.ceil(br.y / step)
    // 缩放很小时步数会爆炸，加个上限自保（正常不会触发）
    const maxLines = 400
    ctx.lineWidth = 1
    ctx.strokeStyle = C.grid
    if (i1 - i0 <= maxLines && j1 - j0 <= maxLines) {
      ctx.beginPath()
      for (let i = i0; i <= i1; i++) {
        const x = Math.round(S({ x: i * step, y: 0 }).x) + 0.5
        ctx.moveTo(x, 0)
        ctx.lineTo(x, H)
      }
      for (let j = j0; j <= j1; j++) {
        const y = Math.round(S({ x: 0, y: j * step }).y) + 0.5
        ctx.moveTo(0, y)
        ctx.lineTo(W, y)
      }
      ctx.stroke()
    }

    /* --- 世界坐标轴（x=0 / y=0），比普通网格明显 --- */
    ctx.strokeStyle = C.axis
    ctx.lineWidth = 1.5
    const ax = S({ x: 0, y: 0 })
    ctx.beginPath()
    ctx.moveTo(Math.round(ax.x) + 0.5, 0)
    ctx.lineTo(Math.round(ax.x) + 0.5, H)
    ctx.stroke()
    if (ax.y > -1 && ax.y < H + 1) {
      ctx.beginPath()
      ctx.moveTo(0, Math.round(ax.y) + 0.5)
      ctx.lineTo(W, Math.round(ax.y) + 0.5)
      ctx.stroke()
    }

    /* --- 刻度值：沿 x 轴标世界坐标，让缩放后仍能读数 --- */
    ctx.fillStyle = C.text2
    ctx.font = '10px -apple-system, "PingFang SC", "Microsoft YaHei", sans-serif'
    ctx.textAlign = 'center'
    ctx.textBaseline = 'top'
    const labelY = Math.min(H - 14, Math.max(2, ax.y + 3))
    for (let i = i0; i <= i1; i++) {
      if (i === 0) continue
      const wx = i * step
      const sx = S({ x: wx, y: 0 }).x
      if (sx < 16 || sx > W - 16) continue
      ctx.fillText(tickText(wx), sx, labelY)
    }

    /**
     * 单位说明（画在画布**左上角**）。
     *
     * 现在全局只有一种单位：**米**。网格刻度、轨道端点坐标、图标位置、
     * 按钮区段的沿轨弧长全是米——轨道画多长就是多少米，所以刻度读数可以和
     * 航点的 `x` 直接对比（22.5 m 的航点就落在离起点 22.5 m 处）。
     *
     * 曾经这里有两套单位（世界坐标是"示意单位"、航点 x 走归一化），
     * 表现为"航点 x 才 22.5，怎么显示在好几百米的位置"。这行提示留着，
     * 是为了让人一眼确认刻度读的到底是什么。
     * 放在顶部而不是跟着 x 轴走：轴跑到视野上方时 `labelY` 会被夹到 2，
     * 跟刻度数字挤在同一行。
     */
    ctx.textAlign = 'left'
    ctx.fillText('网格刻度单位：米', 10, 4)

    /* --- 轨道曲线 --- */
    if (hasTrack) {
      // 线宽不随缩放变粗：屏幕像素宽度固定，视觉才稳定
      ctx.lineJoin = 'round'
      ctx.lineCap = 'round'
      ctx.strokeStyle = C.trackGlow
      ctx.lineWidth = 10
      ctx.beginPath()
      sampled.pts.forEach((q, i) => {
        const c = S(q)
        i === 0 ? ctx.moveTo(c.x, c.y) : ctx.lineTo(c.x, c.y)
      })
      ctx.stroke()

      ctx.strokeStyle = C.track
      ctx.lineWidth = 3
      ctx.beginPath()
      sampled.pts.forEach((q, i) => {
        const c = S(q)
        i === 0 ? ctx.moveTo(c.x, c.y) : ctx.lineTo(c.x, c.y)
      })
      ctx.stroke()
    }

    /* --- 区段标记：贴在轨道上的一条彩色带（门 / 窗 / 减速…） --- */
    for (const sec of placedSections) {
      const hot = selectedPaths.has(sec.path) || hoverPath === sec.path
      // 颜色来自节点属性；填了非十六进制就退回 warning 色，别把整段画成透明
      const color = /^#[0-9a-fA-F]{3,8}$/.test((sec.color || '').trim())
        ? sec.color.trim()
        : C.handle
      ctx.save()
      ctx.lineCap = 'round'
      ctx.lineJoin = 'round'
      ctx.strokeStyle = color
      // 半透明宽带：既要显眼，又不能把底下的轨道与航点糊住
      ctx.globalAlpha = hot ? 0.6 : 0.34
      ctx.lineWidth = hot ? 16 : 12
      ctx.beginPath()
      sec.canvas.forEach((c, i) => (i === 0 ? ctx.moveTo(c.x, c.y) : ctx.lineTo(c.x, c.y)))
      ctx.stroke()

      // 两端点个小圆点标出起止：光是一条带子看不出边界在哪
      ctx.globalAlpha = hot ? 1 : 0.7
      ctx.fillStyle = color
      for (const c of [sec.canvas[0], sec.canvas[sec.canvas.length - 1]]) {
        ctx.beginPath()
        ctx.arc(c.x, c.y, hot ? 4 : 3, 0, Math.PI * 2)
        ctx.fill()
      }
      ctx.restore()

      // 标签只在选中/悬停时出现，否则一堆"门""减速"会把地图糊满
      if (hot && sec.label) {
        const t = sec.canvas[Math.floor(sec.canvas.length / 2)]
        ctx.save()
        ctx.font = '11px -apple-system, "PingFang SC", "Microsoft YaHei", sans-serif'
        ctx.textAlign = 'center'
        ctx.textBaseline = 'middle'
        const w = ctx.measureText(sec.label).width
        ctx.globalAlpha = 0.9
        ctx.fillStyle = C.bg
        ctx.fillRect(t.x - w / 2 - 5, t.y - 24, w + 10, 16)
        ctx.globalAlpha = 1
        ctx.fillStyle = C.text
        ctx.fillText(sec.label, t.x, t.y - 16)
        ctx.restore()
      }
    }

    /* --- 图标标记：任意位置的矢量图标（门 / 电梯 / 消防栓…） --- */
    for (const it of placedIcons) {
      const { x, y } = it.canvas
      if (x < -60 || x > W + 60 || y < -60 || y > H + 60) continue
      const sel = selectedPaths.has(it.path)
      const hov = hoverPath === it.path
      const size = normalizeIconSize(it.size)
      // 颜色同样是节点属性，脏数据退回主题色而不是画出个透明图标
      const color = /^#[0-9a-fA-F]{3,8}$/.test((it.color || '').trim())
        ? it.color.trim()
        : DEFAULT_ICON_COLOR

      // 选中/悬停时先垫一个浅色圆底：图标本身可能是细线条，
      // 光靠描边看不出选中了哪个
      if (sel || hov) {
        ctx.save()
        ctx.globalAlpha = sel ? 0.22 : 0.12
        ctx.fillStyle = sel ? C.wpSel : color
        ctx.beginPath()
        ctx.arc(x, y, size / 2 + 4, 0, Math.PI * 2)
        ctx.fill()
        ctx.restore()
      }

      drawIcon(ctx, it.icon, x, y, size, color)

      // 名称只在选中/悬停时显示：图标可能摆十几二十个，全标会糊成一片
      if ((sel || hov) && it.label) {
        ctx.save()
        ctx.font = '11px -apple-system, "PingFang SC", "Microsoft YaHei", sans-serif'
        ctx.textAlign = 'center'
        ctx.textBaseline = 'middle'
        const text = `${it.label}（${iconLabel(it.icon)}）`
        const w = ctx.measureText(text).width
        ctx.globalAlpha = 0.9
        ctx.fillStyle = C.bg
        ctx.fillRect(x - w / 2 - 5, y + size / 2 + 2, w + 10, 16)
        ctx.globalAlpha = 1
        ctx.fillStyle = C.text
        ctx.fillText(text, x, y + size / 2 + 10)
        ctx.restore()
      }
    }

    /* --- 正在拉的新段预览 --- */
    if (pending && parsed.endpoints.length) {
      const from = parsed.endpoints[parsed.endpoints.length - 1]
      const a = { x: from.x, y: from.y }
      const b = pending.anchor
      const ctrl = pending.control ?? { x: (a.x + b.x) / 2, y: (a.y + b.y) / 2 }
      ctx.strokeStyle = C.preview
      ctx.lineWidth = 2
      ctx.setLineDash([6, 4])
      ctx.beginPath()
      // 用 24 段折线近似这段三次贝塞尔即可（预览不用太精细）
      for (let i = 0; i <= 24; i++) {
        const t = i / 24
        const mt = 1 - t
        const x = mt ** 3 * a.x + 3 * mt ** 2 * t * ctrl.x + 3 * mt * t ** 2 * ctrl.x + t ** 3 * b.x
        const y = mt ** 3 * a.y + 3 * mt ** 2 * t * ctrl.y + 3 * mt * t ** 2 * ctrl.y + t ** 3 * b.y
        const c = S({ x, y })
        i === 0 ? ctx.moveTo(c.x, c.y) : ctx.lineTo(c.x, c.y)
      }
      ctx.stroke()
      ctx.setLineDash([])

      // 控制点及其与两端点的连线
      const pc = S(ctrl)
      ctx.strokeStyle = C.handleLine
      ctx.lineWidth = 1
      ctx.setLineDash([4, 3])
      ctx.beginPath()
      for (const end of [a, b]) {
        const e = S(end)
        ctx.moveTo(e.x, e.y)
        ctx.lineTo(pc.x, pc.y)
      }
      ctx.stroke()
      ctx.setLineDash([])
      ctx.beginPath()
      ctx.arc(pc.x, pc.y, 4, 0, Math.PI * 2)
      ctx.fillStyle = C.handle
      ctx.fill()
      ctx.strokeStyle = C.wpStroke
      ctx.lineWidth = 1.5
      ctx.stroke()
    }

    /* --- 绘制工具：控制点手柄连线（先画线，点后画，保证点在最上层） --- */
    if (tool === 'draw') {
      ctx.strokeStyle = C.handleLine
      ctx.lineWidth = 1
      ctx.setLineDash([4, 3])
      ctx.beginPath()
      for (const seg of parsed.segments) {
        const a = parsed.endpoints[seg.a]
        const b = parsed.endpoints[seg.b]
        const pa = S(a)
        const pb = S(b)
        seg.controls.forEach((c, i) => {
          const pc = S(c)
          // 0 个 -> 无连线；1 个 -> 连两端；2 个 -> 分别连最近那一端
          if (seg.controls.length === 1 || i === 0) { ctx.moveTo(pa.x, pa.y); ctx.lineTo(pc.x, pc.y) }
          if (seg.controls.length === 1 || i === 1) { ctx.moveTo(pb.x, pb.y); ctx.lineTo(pc.x, pc.y) }
        })
      }
      ctx.stroke()
      ctx.setLineDash([])
    }

    /* --- 角标：当前轨道 + 缩放倍率 --- */
    ctx.fillStyle = C.text2
    ctx.font = '10px -apple-system, "PingFang SC", "Microsoft YaHei", sans-serif'
    ctx.textAlign = 'center'
    ctx.textBaseline = 'top'
    const title = hasTrack
      ? `▲ ${trackName || '轨道'}${parsed.closed ? '（闭合）' : ''} · ${vp.scale.toFixed(2)}×`
      : `▲ 暂无轨道 · ${vp.scale.toFixed(2)}×`
    ctx.fillText(title, W / 2, 4)

    /* --- 航点：圆点 + 编号（不再画从顶部垂下来的引线，太吵） --- */
    placed.forEach((w, i) => {
      const sel = selectedPaths.has(w.path)
      const hov = hoverPath === w.path
      const { x, y } = w.canvas
      // 视口外的不画（航点上百个时省掉大量无用绘制）
      if (x < -40 || x > W + 40 || y < -40 || y > H + 40) return

      const r = sel ? 6 : hov ? 5.5 : 4.5
      ctx.beginPath()
      ctx.arc(x, y, r, 0, Math.PI * 2)
      ctx.fillStyle = sel ? C.wpSel : C.wp
      ctx.fill()
      ctx.strokeStyle = C.wpStroke
      ctx.lineWidth = 2
      ctx.stroke()

      // 序号标签：选中的加粗
      ctx.fillStyle = sel ? C.wpSel : C.text2
      ctx.font = `${sel ? 'bold ' : ''}10px -apple-system, "PingFang SC", sans-serif`
      ctx.textAlign = 'center'
      ctx.textBaseline = 'bottom'
      const ly = y + (i % 2 === 0 ? 16 : 28)
      ctx.fillText(String(i + 1), x, ly)
    })

    /* --- 沿轨设施：充电桩（方）/ RFID 卡（菱）——两者形状刻意不同，
           缩得很小也能分清，不靠颜色区分（色弱/暗色主题下颜色不可靠）--- */
    placedMarkers.forEach((m) => {
      const { x, y } = m.canvas
      if (x < -40 || x > W + 40 || y < -40 || y > H + 40) return
      const sel = selectedPaths.has(m.path)
      const hov = hoverPath === m.path
      const s = sel ? 12 : hov ? 11 : 10
      const fill = m.kind === 'charging' ? C.pile : C.rfid
      ctx.beginPath()
      if (m.kind === 'charging') {
        // 正方形（充电桩）
        ctx.rect(x - s / 2, y - s / 2, s, s)
      } else {
        // 菱形（RFID）
        ctx.moveTo(x, y - s / 2)
        ctx.lineTo(x + s / 2, y)
        ctx.lineTo(x, y + s / 2)
        ctx.lineTo(x - s / 2, y)
        ctx.closePath()
      }
      ctx.fillStyle = fill
      ctx.fill()
      ctx.strokeStyle = sel ? C.wpSel : C.wpStroke
      ctx.lineWidth = sel ? 2.5 : 1.5
      ctx.stroke()

      // 内部符号：充电桩画一道"电"折线，RFID 画一个圆点，小尺寸下也能认出来
      ctx.strokeStyle = '#fff'
      ctx.lineWidth = 1.2
      if (m.kind === 'charging') {
        ctx.beginPath()
        ctx.moveTo(x + 1.6, y - 3.2)
        ctx.lineTo(x - 1.4, y + 0.4)
        ctx.lineTo(x + 1.0, y + 0.4)
        ctx.lineTo(x - 1.6, y + 3.2)
        ctx.stroke()
      } else {
        ctx.beginPath()
        ctx.arc(x, y, 1.6, 0, Math.PI * 2)
        ctx.fillStyle = '#fff'
        ctx.fill()
      }

      // 名称只在选中/悬停时显示：桩和卡可能有十几个，全都标会糊成一片
      if (sel || hov) {
        ctx.fillStyle = C.text2
        ctx.font = '10px -apple-system, "PingFang SC", "Microsoft YaHei", sans-serif'
        ctx.textAlign = 'center'
        ctx.textBaseline = 'bottom'
        ctx.fillText(m.label, x, y - s / 2 - 3)
      }
    })

    /* --- 绘制工具：端点与控制点画在最上层，保证能抓取 --- */
    if (tool === 'draw') {
      // 控制点（圆）
      for (const n of nodes) {
        if (n.kind !== 'control') continue
        const c = S(n)
        const sel = selectedPaths.has(n.path)
        ctx.beginPath()
        ctx.arc(c.x, c.y, sel ? 5 : 4, 0, Math.PI * 2)
        ctx.fillStyle = sel ? C.sel : C.handle
        ctx.fill()
        ctx.strokeStyle = C.wpStroke
        ctx.lineWidth = 1.5
        ctx.stroke()
      }
      // 端点（方）
      for (const n of nodes) {
        if (n.kind !== 'endpoint') continue
        const c = S(n)
        const sel = selectedPaths.has(n.path)
        const hov = hoverPath === n.path
        const s = sel ? 9 : hov ? 8 : 7
        ctx.beginPath()
        ctx.rect(c.x - s / 2, c.y - s / 2, s, s)
        ctx.fillStyle = sel ? C.sel : C.node
        ctx.fill()
        ctx.strokeStyle = C.wpStroke
        ctx.lineWidth = 2
        ctx.stroke()
      }
    }

    /* --- 框选矩形 --- */
    if (marquee && marquee.w > 1 && marquee.h > 1) {
      ctx.fillStyle = 'rgba(0,100,250,.12)'
      ctx.fillRect(marquee.x, marquee.y, marquee.w, marquee.h)
      ctx.strokeStyle = C.sel
      ctx.lineWidth = 1
      ctx.setLineDash([5, 4])
      ctx.strokeRect(marquee.x, marquee.y, marquee.w, marquee.h)
      ctx.setLineDash([])
    }
  }, [
    size, vp, sampled, nodes, parsed, placed, placedMarkers, placedSections, placedIcons,
    selectedPaths, hoverPath, tool,
    marquee, pending, trackName, hasTrack,
    bgVisible, bgRect, bgImage, bgAlpha, bgActive,
  ])

  /* ---- 命中测试：画布(屏幕)坐标 -> 最近的可抓取对象 ---- */

  /** 命中某个航点（屏幕半径 12px 内） */
  const hitWaypoint = useCallback((pt: Pt): number => {
    let best = -1
    let bestD = 13
    placed.forEach((w, i) => {
      const d = Math.hypot(w.canvas.x - pt.x, w.canvas.y - pt.y)
      if (d < bestD) { bestD = d; best = i }
    })
    return best
  }, [placed])

  /** 命中某个沿轨设施（充电桩 / RFID 卡，屏幕半径 12px 内） */
  const hitMarker = useCallback((pt: Pt): number => {
    let best = -1
    let bestD = 13
    placedMarkers.forEach((m, i) => {
      const d = Math.hypot(m.canvas.x - pt.x, m.canvas.y - pt.y)
      if (d < bestD) { bestD = d; best = i }
    })
    return best
  }, [placedMarkers])

  /**
   * 命中某个区段标记：点到"带子"的屏幕距离 ≤ 10px。
   *
   * 用整条折线判定而不是只判中心点——区段可能很长，
   * 只让中心那一小块可点的话，用户点了半天点不中，会以为标记没加上。
   */
  const hitSection = useCallback((pt: Pt): number => {
    let best = -1
    let bestD = 10
    placedSections.forEach((s, i) => {
      const c = s.canvas
      for (let k = 0; k + 1 < c.length; k++) {
        const d = distToSegment(pt, c[k], c[k + 1])
        if (d < bestD) { bestD = d; best = i }
      }
    })
    return best
  }, [placedSections])

  /**
   * 命中某个图标标记。
   *
   * 容差跟着图标大小走（至少 12px）：小图标按 12px 兜底，不然 12px 的图标
   * 画出来才巴掌大，鼠标很难点中；大图标则按自身半径算，点边上就能选中。
   */
  const hitIcon = useCallback((pt: Pt): number => {
    let best = -1
    let bestD = Number.POSITIVE_INFINITY
    placedIcons.forEach((it, i) => {
      const tol = Math.max(12, normalizeIconSize(it.size) / 2 + 2)
      const d = Math.hypot(it.canvas.x - pt.x, it.canvas.y - pt.y)
      if (d <= tol && d < bestD) { bestD = d; best = i }
    })
    return best
  }, [placedIcons])

  /** 命中轨道上的某个端点/控制点（绘制工具下可拖动） */
  const hitNode = useCallback((pt: Pt): TrackNodePoint | null => {
    let best: TrackNodePoint | null = null
    let bestD = NODE_HIT_PX
    nodes.forEach((n) => {
      const c = worldToScreen(vp, n)
      const d = Math.hypot(c.x - pt.x, c.y - pt.y)
      // 控制点通常压在端点连线上，同距时优先控制点，免得小的抓不到
      if (d < bestD || (Math.abs(d - bestD) < 0.01 && n.kind === 'control')) {
        bestD = d
        best = n
      }
    })
    return best
  }, [nodes, vp])

  /**
   * 指针下方是否有"值得弹右键菜单"的东西。
   * 只有选择工具才弹（在轨道上添加航点）；绘制工具下右键一律是平移，
   * 免得画到一半被菜单打断。
   */
  const ctxMenuWorthy = useCallback((pt: Pt): boolean => {
    // 挑选模式下没有任何"添加"动作可做，右键只当平移，别弹一个空菜单出来
    if (pickerMode) return false
    if (tool !== 'select') return false
    // 图标是**任意位置**添加的（不吸附轨道），所以支持加图标时，
    // 空白处右键同样"有东西可操作"——否则用户想标个房间里的设备却弹不出菜单。
    if (onAddIcon) return true
    return hitTrack(sampled, screenToWorld(vp, pt), pixelTolerance(vp, NEAR_TRACK_PX)) !== null
  }, [tool, sampled, vp, onAddIcon, pickerMode])

  /* ---- 鼠标事件 ---- */

  const canvasPos = (e: React.MouseEvent): Pt => {
    const rect = canvasRef.current!.getBoundingClientRect()
    return { x: e.clientX - rect.left, y: e.clientY - rect.top }
  }

  /**
   * 滚轮缩放。
   *
   * 必须 `preventDefault` 阻止页面跟着滚（passive 监听器拦不住，
   * 所以不能用 React 的 onWheel，得手动 addEventListener({ passive: false })）。
   * 缩放锚点取鼠标位置，保证鼠标下的世界坐标不动。
   */
  useEffect(() => {
    const cv = canvasRef.current
    if (!cv) return
    const onWheel = (e: WheelEvent) => {
      e.preventDefault()
      const rect = cv.getBoundingClientRect()
      const anchor = { x: e.clientX - rect.left, y: e.clientY - rect.top }
      // deltaMode: 0=像素 1=行 2=页；统一折算成"倍率"
      const unit = e.deltaMode === 1 ? 16 : e.deltaMode === 2 ? 100 : 1
      const dy = e.deltaY * unit
      // 指数映射让每一"格"滚动的视觉变化一致，且天然不会 <= 0
      const factor = Math.exp(-dy * 0.0015)
      setVp((prev) => {
        const next = zoomAt(prev, anchor, factor)
        /**
         * 平移途中滚轮缩放：把平移的**基准视口**一起推进。
         * 否则基准还停在按下那一刻，下一次 mousemove 会用旧基准重算，
         * 缩放结果被整体覆盖掉（表现为"拖着拖着滚一下，视图突然跳回去"）。
         * 这里的赋值是幂等的（同样输入算出的 next 相同），
         * 即使 StrictMode 重复调用 updater 也不会有副作用。
         */
        if (press.current) press.current.vp = next
        if (panStart.current) panStart.current.vp = next
        return next
      })
    }
    cv.addEventListener('wheel', onWheel, { passive: false })
    return () => cv.removeEventListener('wheel', onWheel)
  }, [])

  /** 进入/退出平移态：顺带在 body 上落一个光标类，见 styles.css 的 .wp3-panning */
  const setPanningState = useCallback((on: boolean) => {
    panning.current = on
    document.body.classList.toggle('wp3-panning', on)
    setCursorTick((t) => t + 1)
  }, [])

  /** 卸载时兜底清掉 body 上的光标类，避免平移中被切走页面后光标卡在 grabbing */
  useEffect(() => () => { document.body.classList.remove('wp3-panning') }, [])

  /**
   * 指针位置对应轨道上的哪个 u（**不看阈值**，专供拖拽用）。
   *
   * 没有轨道时退回"退化水平线"的反解：`placed` 用的是 `u * lengthM`，
   * 这里就反过来除回去，保证"画在哪儿、拖到哪儿"是同一套映射。
   */
  const uAtPointer = useCallback((pt: Pt): number | null => {
    const w = screenToWorld(vp, pt)
    if (hasTrack) return nearestU(sampled, w)
    if (!Number.isFinite(w.x) || !(lengthM > 0)) return null
    return Math.max(0, Math.min(1, w.x / lengthM))
  }, [vp, sampled, hasTrack, lengthM])

  /**
   * 按下后"预备拖动"。
   *
   * 只记起点，**不动坐标**：没超过 `DRAG_THRESHOLD` 就没有任何预览写入，
   * `endDrag` 也就不会提交——所以"点一下选中"与"拖一下改坐标"共用一条路径，
   * 不需要在 mousedown 时猜用户想干嘛。
   */
  const beginMove = useCallback((pt: Pt, kind: MoveKind, path: string) => {
    drawStart.current = pt
    setMovingPath(path)
    setMovingKind(kind)
  }, [])

  const onMouseDown = (e: React.MouseEvent) => {
    const pt = canvasPos(e)

    /* 右键：任何位置都先"预备平移"，拖过阈值就真平移；原地松手才考虑菜单 */
    if (e.button === 2) {
      e.preventDefault()
      press.current = { screen: pt, vp, onTarget: ctxMenuWorthy(pt) }
      pressMoved.current = false
      return
    }

    /* 中键 / 空格+左键 = 平移画布 */
    const wantPan = e.button === 1 || (e.button === 0 && panModifier.current)
    if (wantPan) {
      e.preventDefault()
      panStart.current = { screen: pt, vp }
      setPanningState(true)
      return
    }
    if (e.button !== 0) return

    /* ---- 绘制工具：拖已有点 / 拉新段 ---- */
    if (tool === 'draw') {
      const hit = hitNode(pt)
      if (hit) {
        // 选中它并准备拖动（拖动只改本地 draft，松手才提交）
        onSelectionChange(new Set([hit.path]))
        beginMove(pt, 'track', hit.path)
        e.preventDefault()
        return
      }
      if (!trackCount) {
        Toast.info('请先用「新增轨道」创建一条轨道，再在地图上画端点')
        return
      }
      // 空白处按下：锚点先定在这里，拖出去的方向决定控制点
      drawStart.current = pt
      setPending({ anchor: screenToWorld(vp, pt), control: null })
      e.preventDefault()
      return
    }

    /* ---- 选择工具 ---- */
    const wi = hitWaypoint(pt)
    if (wi >= 0) {
      const w = placed[wi]
      const next = new Set(selectedPaths)
      /**
       * 挑选模式（`pickerMode`）下单击即**切换**：那里的语义是"挑几个航点"，
       * 连点几个当然要攒起来，单击把前面挑的全清掉会让人疯掉。
       * 编排页保持原语义（单击 = 只选它）不变——那边单击之后多半还要拖着改坐标，
       * 顺手把别的清掉才是对的。
       */
      if (pickerMode || e.shiftKey || e.ctrlKey || e.metaKey) {
        next.has(w.path) ? next.delete(w.path) : next.add(w.path)
      } else {
        next.clear()
        next.add(w.path)
      }
      onSelectionChange(next)
      /* 允许按住已选中的点做框选起点（shift 时不预备拖动，交给下面的框选）。
         回调没给（挑选模式）就别预备拖动——否则拖起来有个"点跟着跑"的假预览，
         松手却什么都不写，看起来像拖拽失灵。 */
      if (!pickerMode && !e.shiftKey && next.has(w.path) && onMoveWaypoint) {
        beginMove(pt, 'waypoint', w.path); return
      }
    }

    // 沿轨设施（充电桩 / RFID）：与航点同一套点选规则，选中后检视器就能改它
    const mi = hitMarker(pt)
    if (mi >= 0) {
      const m = placedMarkers[mi]
      const next = new Set(selectedPaths)
      if (e.shiftKey || e.ctrlKey || e.metaKey) {
        next.has(m.path) ? next.delete(m.path) : next.add(m.path)
      } else {
        next.clear()
        next.add(m.path)
      }
      onSelectionChange(next)
      if (!e.shiftKey && next.has(m.path) && onMoveMarker) { beginMove(pt, 'marker', m.path); return }
    }

    // 区段标记：与航点同一套点选规则，选中后检视器里就能改半径 / 颜色
    const si = hitSection(pt)
    if (si >= 0) {
      const s = placedSections[si]
      const next = new Set(selectedPaths)
      if (e.shiftKey || e.ctrlKey || e.metaKey) {
        next.has(s.path) ? next.delete(s.path) : next.add(s.path)
      } else {
        next.clear()
        next.add(s.path)
      }
      onSelectionChange(next)
      if (!e.shiftKey && next.has(s.path) && onMoveSection) { beginMove(pt, 'section', s.path); return }
    }

    // 图标标记：同一套点选规则，选中后检视器里就能换图标 / 颜色 / 大小
    const ii = hitIcon(pt)
    if (ii >= 0) {
      const it = placedIcons[ii]
      const next = new Set(selectedPaths)
      if (e.shiftKey || e.ctrlKey || e.metaKey) {
        next.has(it.path) ? next.delete(it.path) : next.add(it.path)
      } else {
        next.clear()
        next.add(it.path)
      }
      onSelectionChange(next)
      if (!e.shiftKey && next.has(it.path) && onMoveIcon) { beginMove(pt, 'icon', it.path); return }
    }

    /**
     * 背景图微调（只有**选中它**之后才可拖）：
     * 拖右下角手柄 = 缩放，拖图片内部 = 移动锚点。
     * 都只改本地 `bgDraft`，松手才 `onBackgroundChange` 提交一次。
     */
    if (bgActive && bgLive) {
      const mode = hitBgHandle(pt) ? 'scale' : hitBgInside(pt) ? 'move' : null
      if (mode) {
        bgDrag.current = { mode, start: pt, origin: bgLive }
        setBgDraft(bgLive)
        e.preventDefault()
        return
      }
    }

    /**
     * 空白处按下 -> 开始框选。
     *
     * 基准选择与实际模式都在**按下这一刻**定死（存 ref）：
     * 拖拽途中会不停 `onSelectionChange`，实时读 `selectedPaths` 会让
     * "增加"越框越多、"移除"把刚去掉的又加回来。详见 `marqueeSelect` 文件头。
     *
     * `replace` 模式下顺手把旧选择清掉，是为了**按下即见反馈**——否则要等到
     * 指针划出第一个点，用户才看得出"这次是替换不是增加"。清空这一步
     * 不影响最终结果（`applyPickMode` 的 replace 分支根本不读 base）。
     */
    marqueeBase.current = new Set(selectedPaths)
    const mode = resolvePickMode(e, pickMode)
    marqueeMode.current = mode
    marqueeStart.current = pt
    setMarquee({ x: pt.x, y: pt.y, w: 0, h: 0 })
    if (mode === 'replace') onSelectionChange(new Set())
  }

  /**
   * 把指针当前位置（画布坐标）换算成平移量。
   *
   * 由 **window 的 mousemove** 调用，不挂在 canvas 上：指针一旦移出画布，
   * canvas 自己的 onMouseMove 就不再触发，平移会当场卡住（表现为"拖出
   * 画布外就拖不动了"）。换算用的 rect 仍是 canvas 的，指针在画布外时
   * 得到的坐标会超出 [0, size] —— 这对求**相对位移**毫无影响，
   * `panFrom` 做的是减法，负值一样算得对。
   */
  const applyPan = useCallback((pt: Pt) => {
    if (press.current) {
      const { screen, vp: baseVp } = press.current
      if (!pressMoved.current && isDrag(screen, pt, DRAG_THRESHOLD)) {
        pressMoved.current = true
        setPanningState(true)
      }
      if (pressMoved.current) setVp(panFrom(baseVp, screen, pt))
      return
    }
    if (panStart.current) {
      setVp(panFrom(panStart.current.vp, panStart.current.screen, pt))
    }
  }, [setPanningState])

  /**
   * 拖拽预览（只改本地 draft / draftU，松手才提交）。
   *
   * 与平移一样**挂在 window 上**而不是 canvas 上：canvas 自己的 onMouseMove
   * 在指针移出画布后就不再触发，拖到边缘外面会当场卡住（表现为"拖出画布
   * 就拖不动了"）。指针在画布外时算出的坐标会超出 [0, size]，但对求投影
   * 毫无影响——`screenToWorld` 是线性的。
   *
   * 抽成函数是为了让 canvas 的 onMouseMove 与这里的 window 监听共用，
   * 免得两处各写一份、改了一处忘了另一处。
   */
  const updateDragPreview = useCallback((pt: Pt) => {
    if (!movingPath || !drawStart.current) return false
    if (movingKind === 'waypoint' || movingKind === 'marker' || movingKind === 'section') {
      /**
       * 沿轨的三类：过阈值才开始跟，否则"点一下选中"也会被当成拖动提交一次。
       * 投影用 `nearestU`（不看阈值）——拖拽时指针常常不在轨道上，
       * 用带阈值的 `hitTrack` 会一离开就断、点卡住不动。
       */
      if (!isDrag(drawStart.current, pt, DRAG_THRESHOLD)) return true
      const u = uAtPointer(pt)
      if (u != null) setDraftU((prev) => ({ ...prev, [movingPath]: u }))
    } else {
      const w = screenToWorld(vp, pt)
      setDraft((prev) => ({ ...prev, [movingPath]: { x: w.x, y: w.y } }))
    }
    return true
  }, [movingPath, movingKind, vp, uAtPointer])

  /* 平移 / 拖拽期间在 window 上跟随指针，这样拖出画布也能继续 */
  useEffect(() => {
    const move = (e: MouseEvent) => {
      // 没事就不打扰，避免每帧都做无谓的 getBoundingClientRect
      if (!press.current && !panStart.current && !movingPath) return
      const rect = canvasRef.current?.getBoundingClientRect()
      if (!rect) return
      const pt = { x: e.clientX - rect.left, y: e.clientY - rect.top }
      if (movingPath) { updateDragPreview(pt); return }
      applyPan(pt)
    }
    window.addEventListener('mousemove', move)
    return () => window.removeEventListener('mousemove', move)
  }, [applyPan, updateDragPreview, movingPath])

  const onMouseMove = (e: React.MouseEvent) => {
    const pt = canvasPos(e)

    /* 平移由上面的 window 监听统一处理（它同样覆盖指针在画布内的情况），
       这里直接让开，免得重复计算；顺带也避免平移途中 hover 高亮乱跳。 */
    if (press.current || panStart.current) return

    /* 背景图：移动锚点 / 缩放（只改本地预览，松手才提交） */
    if (bgDrag.current && bgLive) {
      const { mode, start, origin } = bgDrag.current
      const w0 = screenToWorld(vp, start)
      const w1 = screenToWorld(vp, pt)
      if (mode === 'move') {
        setBgDraft({
          ...origin,
          x: origin.x + (w1.x - w0.x),
          y: origin.y + (w1.y - w0.y),
        })
      } else if (bgImage) {
        // 手柄是右下角：让对角跟着指针走（数学在 trackGeometry.backgroundScaleAt，
        // 抽出去是为了能进回归脚本——组件里的逻辑测不到）
        const s = backgroundScaleAt(
          origin, bgImage.naturalWidth, bgImage.naturalHeight, w1, BG_MIN_SCALE,
        )
        setBgDraft({ ...origin, scale: Number(s.toFixed(5)) })
      }
      return
    }

    /* 拖动已有点：预览统一由 window 监听处理（指针移出画布也能继续拖），
       这里只让开，顺带避免拖动途中 hover 高亮乱跳。 */
    if (movingPath) return

    /* 绘制工具：正在拉新段 —— 拖出阈值后才产生控制点 */
    if (pending && drawStart.current) {
      if (!isDrag(drawStart.current, pt, DRAG_THRESHOLD)) {
        if (pending.control) setPending({ anchor: pending.anchor, control: null })
      } else {
        setPending({ anchor: pending.anchor, control: screenToWorld(vp, pt) })
      }
      return
    }

    /* 框选 */
    if (marqueeStart.current) {
      const rect = normalizeRect(marqueeStart.current, pt)
      setMarquee(rect)
      // 实时预览选区。注意把屏幕矩形反投影到世界坐标再和航点世界坐标比，
      // 而不是拿屏幕矩形直接比——否则缩放的瞬间框选范围就错位了。
      const wRect = normalizeRect(
        screenToWorld(vp, marqueeStart.current),
        screenToWorld(vp, pt),
      )
      const tol = pixelTolerance(vp, 7)
      const hit = new Set<string>()
      for (const w of placed) {
        const r = { x: w.world.x - tol, y: w.world.y - tol, w: tol * 2, h: tol * 2 }
        if (rectsIntersect(wRect, r)) hit.add(w.path)
      }
      for (const m of placedMarkers) {
        const r = { x: m.world.x - tol, y: m.world.y - tol, w: tol * 2, h: tol * 2 }
        if (rectsIntersect(wRect, r)) hit.add(m.path)
      }
      // 区段按**整条带子**进框选（逐点判），只判中心的话长区段框不中
      for (const s of placedSections) {
        for (const p of s.world) {
          if (p.x >= wRect.x && p.x <= wRect.x + wRect.w
            && p.y >= wRect.y && p.y <= wRect.y + wRect.h) { hit.add(s.path); break }
        }
      }
      // 图标按中心点进框选（它就是个点）
      for (const it of placedIcons) {
        if (it.x >= wRect.x && it.x <= wRect.x + wRect.w
          && it.y >= wRect.y && it.y <= wRect.y + wRect.h) hit.add(it.path)
      }
      // 合并规则（替换 / 增加 / 移除）在纯函数里，见 `marqueeSelect`：
      // 基准是**按下那一刻**的快照，不是实时的 selectedPaths。
      onSelectionChange(applyPickMode(marqueeBase.current, hit, marqueeMode.current))
      return
    }

    /* 悬停高亮 */
    if (tool === 'draw') {
      setBgHover(null)
      const n = hitNode(pt)
      setHoverPath(n ? n.path : null)
      return
    }
    const wi = hitWaypoint(pt)
    if (wi >= 0) { setBgHover(null); setHoverPath(placed[wi].path); return }
    const mi = hitMarker(pt)
    if (mi >= 0) { setBgHover(null); setHoverPath(placedMarkers[mi].path); return }
    const si = hitSection(pt)
    if (si >= 0) { setBgHover(null); setHoverPath(placedSections[si].path); return }
    const ii = hitIcon(pt)
    if (ii >= 0) { setBgHover(null); setHoverPath(placedIcons[ii].path); return }
    // 背景图激活时指针落在图上：只改光标形状（移动 / 缩放），不高亮节点
    setBgHover(hitBgHandle(pt) ? 'scale' : hitBgInside(pt) ? 'move' : null)
    setHoverPath(null)
  }

  const endDrag = useCallback(() => {
    if (panStart.current) {
      panStart.current = null
      setPanningState(false)
    }
    /* 右键手势收尾：**唯一的菜单决策点**。
       没拖过 + 按下处有可操作对象 -> 原地弹菜单；否则纯平移，什么都不弹。
       放在 mouseup 而不是 contextmenu 里，是因为 contextmenu 的触发时机
       跨平台不一致（Windows 在 mouseup 之后，macOS 在之前），只有 mouseup
       能确定"到底拖没拖"。 */
    if (press.current) {
      const { screen, onTarget } = press.current
      const wasDrag = pressMoved.current
      press.current = null
      pressMoved.current = false
      setPanningState(false)
      if (!wasDrag && onTarget) setCtxMenu(screen)
    }

    /* 拖动已有点 -> 松手才提交一次（没动过就什么都不写） */
    if (movingPath) {
      if (movingKind === 'waypoint' || movingKind === 'marker' || movingKind === 'section') {
        const u = draftU[movingPath]
        if (u != null) {
          const t = Math.max(0, Math.min(1, u))
          /**
           * 反推 x：量程是**轨道总长 (m)**，与数据无关，所以航点、充电桩、
           * RFID、区段**全都走同一条** `uToX(lengthM, u)`——写进去再读出来
           * 一定还是同一个 u，松手即所得，不需要任何补偿。
           *
           * 旧版航点要单独走 `dragXForU`（拿"除自己以外的极值"反推）是因为
           * 那时量程取自航点自身的 min-max：改一个点会动值域，极值点松手后
           * 会弹回端点。单位统一成米之后这个坑不存在了。
           */
          const x = uToX(lengthM, t)
          if (Number.isFinite(x)) {
            const v = Number(x.toFixed(3))
            if (movingKind === 'waypoint') onMoveWaypoint?.(movingPath, v)
            else if (movingKind === 'marker') onMoveMarker?.(movingPath, v)
            else onMoveSection?.(movingPath, v)
          }
        }
      } else if (movingKind === 'icon') {
        const moved = draft[movingPath]
        if (moved && onMoveIcon) {
          onMoveIcon(movingPath, { x: Number(moved.x.toFixed(3)), y: Number(moved.y.toFixed(3)) })
        }
      } else {
        const moved = draft[movingPath]
        if (moved && onMovePoint) onMovePoint(movingPath, moved)
      }
      setMovingPath(null)
      setMovingKind(null)
      drawStart.current = null
      setDraft({})
      setDraftU({})
    }

    /* 背景图：松手才提交一次（只传真正变了的字段，省掉无意义的写回） */
    if (bgDrag.current && bgDraft) {
      const o = bgDrag.current.origin
      const patch: { x?: number; y?: number; scale?: number } = {}
      if (Math.abs(bgDraft.x - o.x) > 1e-6) patch.x = Number(bgDraft.x.toFixed(3))
      if (Math.abs(bgDraft.y - o.y) > 1e-6) patch.y = Number(bgDraft.y.toFixed(3))
      if (Math.abs(bgDraft.scale - o.scale) > 1e-9) patch.scale = Number(bgDraft.scale.toFixed(5))
      bgDrag.current = null
      setBgDraft(null)
      if (Object.keys(patch).length) onBackgroundChange?.(patch)
    }

    /* 绘制：新段 -> 松手才提交（端点 / 端点+控制点） */
    if (pending) {
      const dragged = drawStart.current
        ? pending.control !== null
        : false
      if (dragged && pending.control) {
        onAddEndpointWithControl?.(pending.control, pending.anchor)
      } else {
        onAddEndpoint?.(pending.anchor)
      }
      setPending(null)
      drawStart.current = null
    }

    if (marqueeStart.current) {
      marqueeStart.current = null
      setMarquee(null)
    }
  }, [
    setPanningState, movingPath, movingKind, draft, draftU, onMovePoint, pending,
    onAddEndpoint, onAddEndpointWithControl, bgDraft, onBackgroundChange,
    onMoveWaypoint, onMoveMarker, onMoveSection, onMoveIcon, lengthM,
  ])

  /**
   * 在 window 上常驻 mouseup，统一收尾所有手势。
   *
   * **不要加"当前是否在拖动"的前置守卫**：右键平移与中键平移都只改 ref
   * （避免每帧 setState），而 ref 的变化不会触发重渲染——守卫会在拖动的
   * 那一拍读到 false，于是监听根本没挂上，松手就漏掉收尾（菜单不弹、
   * 光标卡在 grab）。改成常驻监听，`endDrag` 内部各分支自带判空，
   * 空跑一次的成本可以忽略。
   */
  useEffect(() => {
    const up = () => endDrag()
    window.addEventListener('mouseup', up)
    return () => window.removeEventListener('mouseup', up)
  }, [endDrag])

  /**
   * 右键菜单项要执行的动作（画布坐标 pt）。
   *
   * 菜单打开时记下的是**画布坐标**，不是世界坐标——这样菜单显示期间视口
   * 一动（比如菜单弹出后滚了下滚轮），菜单项点下去仍会按"当初右键的那一点"
   * 重新做命中测试，不会误删旁边的东西。
   */
  const uAt = (pt: Pt): number | null =>
    // 容差要换成世界尺度，否则放大后几乎点不中曲线
    hitTrack(sampled, screenToWorld(vp, pt), pixelTolerance(vp, NEAR_TRACK_PX))

  const runContextAction = (
    pt: Pt,
    kind: 'waypoint' | MarkerKind | 'section' | 'icon' | 'move',
  ) => {
    /* 图标是**任意位置**添加的：直接用世界坐标，不需要也不该吸附轨道 */
    if (kind === 'icon') {
      if (!onAddIcon) { Toast.warning('当前上下文不支持添加图标'); return }
      onAddIcon(screenToWorld(vp, pt))
      return
    }
    const u = uAt(pt)
    if (u === null) { Toast.info('请右键点击轨道曲线上的位置'); return }
    if (kind === 'move') {
      if (!onMoveRobot) { Toast.warning('当前上下文不支持移动机器人'); return }
      onMoveRobot(u)
      return
    }
    if (kind === 'waypoint') {
      if (!onAddWaypoint) { Toast.warning('当前上下文不支持添加航点'); return }
      onAddWaypoint(u)
      return
    }
    if (kind === 'section') {
      if (!onAddSection) { Toast.warning('当前上下文不支持添加区段标记'); return }
      onAddSection(u)
      return
    }
    if (!onAddMarker) { Toast.warning('当前上下文不支持添加沿轨设施'); return }
    onAddMarker(kind, u)
  }

  /**
   * 画布右键：只负责**阻止浏览器原生菜单**，不做任何决策。
   *
   * 为什么不在这里弹菜单：`contextmenu` 的触发时机跨平台不一致——
   * Windows 是 down → up → contextmenu，macOS 是 down → contextmenu → up。
   * 在 macOS 上它甚至早于任何 mousemove，那时根本无法知道用户接下来
   * 是想拖着看图还是要点菜单。所以菜单的决策**统一放在 mouseup**
   * （见 `endDrag`），这里保持无副作用，两种平台顺序下行为就一致了。
   */
  const onContextMenu = (e: React.MouseEvent) => {
    e.preventDefault()
  }

  const onDoubleClick = (e: React.MouseEvent) => {
    const pt = canvasPos(e)
    const wi = hitWaypoint(pt)
    if (wi >= 0 && onLocate) { onLocate(placed[wi].path); return }
    const mi = hitMarker(pt)
    if (mi >= 0 && onLocate) { onLocate(placedMarkers[mi].path); return }
    const si = hitSection(pt)
    if (si >= 0 && onLocate) { onLocate(placedSections[si].path); return }
    const ii = hitIcon(pt)
    if (ii >= 0 && onLocate) onLocate(placedIcons[ii].path)
  }

  /* ---- 工具栏动作 ---- */

  /** 以画布中心为锚点缩放，按钮点击时用 */
  const zoomByButton = (factor: number) => {
    setVp((prev) => zoomAt(prev, { x: size.w / 2, y: size.h / 2 }, factor))
  }
  const zoomIn = () => zoomByButton(1.25)
  const zoomOut = () => zoomByButton(1 / 1.25)

  /**
   * 右键菜单项。
   *
   * 菜单本身只是个"动作入口"，真正的语义仍然由 `runContextAction` 按
   * 点击位置决定——所以这里只有一项：在此添加航点。
   */
  const ctxMenuItems: { label: string; disabled?: boolean; run: () => void }[] = (() => {
    if (!ctxMenu) return []
    const pt = ctxMenu
    /* 沿轨的那几项只在"右键落在轨道上"时才列出来。
       之所以是**不列**而不是"列出来置灰"：置灰会让用户在空白处右键后
       看到一排点不动的项，而它们本来就与这个位置无关（早先就是这么
       踩过一次"菜单弹出来但点了没反应"的坑）。 */
    const items: { label: string; disabled?: boolean; run: () => void }[] = []
    if (uAt(pt) !== null) {
      items.push(
        { label: '在此添加航点', disabled: !onAddWaypoint, run: () => runContextAction(pt, 'waypoint') },
        { label: '在此添加充电桩', disabled: !onAddMarker, run: () => runContextAction(pt, 'charging') },
        { label: '在此添加 RFID 卡', disabled: !onAddMarker, run: () => runContextAction(pt, 'rfid') },
        { label: '在此添加区段标记', disabled: !onAddSection, run: () => runContextAction(pt, 'section') },
        /* 走行放在添加类之后：它不改树，只是"让机器人动起来"，
           放在一排"添加xx"里更不容易被顺手点错。 */
        { label: '移动机器人到此位置', disabled: !onMoveRobot, run: () => runContextAction(pt, 'move') },
      )
    }
    // 图标不挑位置：轨道上、空白处都能标
    if (onAddIcon) {
      items.push({
        label: uAt(pt) !== null ? '在此添加图标' : '在此处添加图标',
        run: () => runContextAction(pt, 'icon'),
      })
    }
    return items
  })()

  const onLayers = layerItems.filter((it) => layers[it.key]).length
  const allLayersOn = onLayers === layerItems.length

  /* cursorTick 只是用来让下面的表达式在"拖动起止"时重新求值（拖动本身
     只改 ref，不触发渲染），所以这里显式引用一下，避免被判成未使用。 */
  void cursorTick
  const cursor = panning.current
    ? 'grabbing'
    : bgDrag.current
      ? (bgDrag.current.mode === 'scale' ? 'nwse-resize' : 'move')
      : tool === 'draw'
        ? (movingPath || pending ? 'grabbing' : 'crosshair')
        /* 选择工具下按住节点拖动也是"抓着"的手感（先选中、再拖走坐标） */
        : movingPath
          ? 'grabbing'
          : hoverPath
            ? 'pointer'
            : bgHover
              ? (bgHover === 'scale' ? 'nwse-resize' : 'move')
              : 'default'

  return (
    <div className="wp3-map">
      {/* 工具栏：图标按钮 + 悬浮说明 */}
      <div className="wp3-map-bar">
        {/* 挑选模式下工具恒为「选择」，这两个按钮（尤其「绘制轨道」）只会让人
            以为能画轨道——藏掉，位置让给框选模式开关。 */}
        {!pickerMode && (
          <>
            <Tooltip content="选择工具：点选 / Shift 加选 / 拖拽框选航点、沿轨设施、区段与图标，右键轨道可添加航点 / 充电桩 / RFID 卡 / 区段标记，任意位置右键可添加图标">
              <Button
                size="small"
                theme={tool === 'select' ? 'solid' : 'borderless'}
                type={tool === 'select' ? 'primary' : 'tertiary'}
                icon={<IconHandle />}
                onClick={() => setTool('select')}
              >选择</Button>
            </Tooltip>
            <Tooltip content="绘制轨道：左键点击加端点（直线），按住拖拽则拉出控制点（曲线）；已有端点/控制点可直接拖动">
              <Button
                size="small"
                theme={tool === 'draw' ? 'solid' : 'borderless'}
                type={tool === 'draw' ? 'primary' : 'tertiary'}
                icon={<IconEdit />}
                onClick={() => { setTool('draw'); onSelectionChange(new Set()) }}
              >绘制轨道</Button>
            </Tooltip>
          </>
        )}

        {/* 框选模式：`替换` 是原有行为（也是默认值），`增加` / `移除` 是这次加的。
            拖拽时按住 Shift / Alt 可以**临时**覆盖它，但键盘用法不写在界面上
            没人会知道，所以这里给一个看得见的开关。 */}
        {pickerMode && (
          <>
            <span className="wp3-map-hint" style={{ marginRight: 2 }}>框选</span>
            {PICK_MODES.map((m) => (
              <Tooltip key={m} content={`${PICK_MODE_HINT[m]}（拖拽时按住 Shift = 增加，Alt = 移除，可临时覆盖）`}>
                <Button
                  size="small"
                  theme={pickMode === m ? 'solid' : 'borderless'}
                  type={pickMode === m ? 'primary' : 'tertiary'}
                  onClick={() => setPickMode(m)}
                >{PICK_MODE_LABEL[m]}</Button>
              </Tooltip>
            ))}
          </>
        )}

        <span className="wp3-map-sep" />

        {/* 图层开关：地图上画哪些东西。
            受控 Dropdown（`visible` + `onVisibleChange`）—— Semi 默认点一项就收起，
            而这里是"连着勾好几项"的场景，收起反而烦；点外面照样关。

            触发元素的**嵌套顺序是有讲究的**，别随便改：
            Semi 的 Dropdown 底层就是 Tooltip，它把触发用的 onClick 挂在
            **直接子元素**上（cloneElement 合并进 children 的 props）。
            如果直接子元素是另一个 Semi 组件（比如 Tooltip），这个 onClick
            会被它吃掉——Semi 的 Tooltip **不透传**自己收到的未知 props，
            于是下拉框怎么点都打不开（正是"显示开关下拉不了"这个 bug）。
            所以这里用一层普通 <span> 做"事件垫片"：
              外层 Tooltip → 挂 hover 到 span；内层 Dropdown → 挂 click 到 Button。
            两边各有一个真实 DOM 节点，谁也不抢谁的。 */}
        {/* 图层开关只对"这张图上有很多种东西"有意义。挑选模式下只画航点，
            留个「显示 1/1」的下拉纯属噪声。 */}
        {!pickerMode && (
          <Tooltip content="选择地图中显示哪些信息（隐藏的图层不会画出来，也点不中）">
            <span className="wp3-map-trigger">
              <Dropdown
                visible={layerOpen}
                onVisibleChange={setLayerOpen}
                trigger="click"
                position="bottomLeft"
                render={
                  <div className="wp3-map-layer">
                    <div className="wp3-map-layer-title">地图中显示</div>
                    {/* 整行都由 Checkbox 自己接管点击：**不能再给外层加 onClick** ——
                        Semi 的 Checkbox 根节点本身就是 span + onClick，
                        两个都会触发，一开一关正好抵消（点了没反应）。 */}
                    {layerItems.map((it) => (
                      <div key={it.key} className="wp3-map-layer-item">
                        <Checkbox
                          checked={layers[it.key]}
                          onChange={() => toggleLayer(it.key)}
                        >{it.label}</Checkbox>
                      </div>
                    ))}
                  </div>
                }
              >
                <Button size="small" theme="borderless" type="tertiary"
                  icon={allLayersOn ? <IconEyeOpened /> : <IconEyeClosed />}>
                  显示 {onLayers}/{layerItems.length}
                </Button>
              </Dropdown>
            </span>
          </Tooltip>
        )}

        {/* 背景图：上传/更换。图片来源由上层决定（上传接口在页面那一层），
            组件只留一个入口，免得把 API 依赖带进通用组件。 */}
        {onPickBackground && (
          <Tooltip content={background
            ? '更换地图背景图；选中「背景图」节点后可在图上拖动微调，或在检视器里改路径 / 缩放 / 不透明度'
            : '为地图添加一张背景图（照着它摆轨道与航点）'}>
            <Button size="small" theme="borderless" type="tertiary" icon={<IconImage />}
              onClick={() => onPickBackground()}>
              {background ? '背景图' : '添加背景图'}
            </Button>
          </Tooltip>
        )}

        {tool === 'draw' ? (
          <>
            <Tooltip content="新建一条轨道（在航点树中新增一个轨道节点）">
              <Button size="small" theme="borderless" type="tertiary" icon={<IconPlus />}
                onClick={() => onCreateTrack?.()}>新增轨道</Button>
            </Tooltip>
            <Tooltip content="清空当前轨道的所有端点与控制点">
              <Button size="small" theme="borderless" type="tertiary" icon={<IconDelete />}
                disabled={!nodes.length} onClick={() => onClearTrack?.()}>
                清空
              </Button>
            </Tooltip>
            <span className="wp3-map-hint">
              左键点击 = 端点（直线） · 按住拖拽 = 端点 + 控制点（曲线）
            </span>
          </>
        ) : (
          <span className="wp3-map-hint">
            {pickerMode
              ? `点选切换单个航点 · 拖拽框选（Shift 框选 = 增加，Alt 框选 = 移除，当前模式：${PICK_MODE_LABEL[pickMode]}）`
              : '点选 / Shift 加选 / 拖拽框选；在轨道上右键添加航点 / 充电桩 / RFID 卡 / 区段标记，任意位置右键添加图标'}
          </span>
        )}

        <span style={{ flex: 1 }} />

        {/* 视图控制：缩放 + 适应窗口 */}
        <Tooltip content="缩小（也可滚轮向下）">
          <Button size="small" theme="borderless" type="tertiary" icon={<IconMinus />}
            disabled={vp.scale <= MIN_SCALE * 1.001} onClick={zoomOut} />
        </Tooltip>
        <span className="wp3-map-zoom">{vp.scale.toFixed(2)}×</span>
        <Tooltip content="放大（也可滚轮向上）">
          <Button size="small" theme="borderless" type="tertiary" icon={<IconPlus />}
            disabled={vp.scale >= MAX_SCALE * 0.999} onClick={zoomIn} />
        </Tooltip>
        <Tooltip content="适应窗口：把整条轨道装进画布并居中">
          <Button size="small" theme="borderless" type="tertiary" icon={<IconExpand />}
            onClick={fitToContent} />
        </Tooltip>
        <Tooltip content="缩放 1:1">
          <Button size="small" theme="borderless" type="tertiary" icon={<IconAppCenter />}
            onClick={() => setVp((prev) => zoomAt(prev, { x: size.w / 2, y: size.h / 2 }, 1 / prev.scale))} />
        </Tooltip>

        <span className="wp3-map-count">
          {placed.length} 航点
          {selectedPaths.size > 0 ? ` · 选中 ${selectedPaths.size}` : ''}
          {tool === 'draw'
            ? ` · ${parsed.endpoints.length} 端点 / ${nodes.length - parsed.endpoints.length - (parsed.closed ? 1 : 0)} 控制点`
            : ''}
          {parsed.closed ? ' · 已闭合' : ''}
          {placedSections.length ? ` · ${placedSections.length} 区段` : ''}
          {placedIcons.length ? ` · ${placedIcons.length} 图标` : ''}
          {background
            ? ` · 背景图${bgImage ? ` ${bgImage.naturalWidth}×${bgImage.naturalHeight}` : '（加载失败）'}`
            : ''}
        </span>
      </div>

      {/* 画布 */}
      <div ref={wrapRef} className="wp3-map-canvas-wrap" style={{ height }}>
        <canvas
          ref={canvasRef}
          style={{ display: 'block', cursor }}
          onMouseDown={onMouseDown}
          onMouseMove={onMouseMove}
          /* 平移途中允许指针划出画布：手势由 window 上的 move/mouseup 继续
             跟随，这里若也 endDrag 一下，拖出画布外就断成一截一截的了。
             其余手势（拖点、框选）没有 window 跟随，离开即收尾。 */
          onMouseLeave={() => {
            setHoverPath(null)
            if (!press.current && !panStart.current) endDrag()
          }}
          onContextMenu={onContextMenu}
          onDoubleClick={onDoubleClick}
        />

        {/* 右键菜单：只在"轨道曲线上原地右键"时出现。
            用 wrap 的 padding 偏移换算成画布内坐标，避免定位到卡片外。 */}
        {ctxMenu && (
          <div className="wp3-map-ctx-host" onMouseDown={(e) => e.stopPropagation()}
            onContextMenu={(e) => e.preventDefault()}>
            <div
              className="wp3-map-ctx"
              style={{ left: Math.round(ctxMenu.x), top: Math.round(ctxMenu.y) }}
            >
              {ctxMenuItems.map((it) => (
                <button
                  key={it.label}
                  type="button"
                  className="wp3-map-ctx-item"
                  disabled={it.disabled}
                  onClick={() => { setCtxMenu(null); it.run() }}
                >{it.label}</button>
              ))}
            </div>
          </div>
        )}
      </div>

      {/* 菜单打开时点别处 / 按 Esc / 滚轮都应该关掉它 */}
      {ctxMenu && <CtxMenuDismiss onClose={() => setCtxMenu(null)} />}

      <div className="wp3-map-foot">
        滚轮缩放（以鼠标为锚点） · 中键 / 空格+左键 / 右键拖拽 平移 · 双击航点/设施/区段/图标定位到树
        {trackCount > 1 ? ` · 共 ${trackCount} 条轨道，当前编辑「${trackName || '轨道'}」` : ''}
        {' · '}
        <Tooltip content={
          hasTrack
            ? '沿当前轨道曲线采样计算的弧长，单位米——世界坐标就是米，轨道画多长就是多少米'
            : '当前没有可用轨道（至少需要 2 个端点）'
        }>
          <span className="wp3-map-len">轨道总长 {lengthText}</span>
        </Tooltip>
        {meterSpan ? ` · 航点弧长 ${meterSpan}` : ''}
        {bgActive ? ' · 拖动背景图移动，拖右下角手柄缩放' : ''}
      </div>
    </div>
  )
}

/**
 * 关掉右键菜单的通用手段：点任意处、按 Esc、滚动、窗口失焦。
 * 拆成组件是为了让"菜单开着"这件事与这些监听的挂/卸严格同步。
 */
function CtxMenuDismiss({ onClose }: { onClose: () => void }) {
  useEffect(() => {
    /**
     * **必须放过菜单内部的点击**。
     *
     * 这里是 window 的**捕获阶段**监听，一定先于菜单项的 React 处理器执行。
     * 若不加区分地 onClose()，菜单会在 mousedown 那一刻就被卸载，
     * 于是浏览器凑不齐 click 所需的 down/up 配对，菜单项的 onClick
     * **永远不触发**（表现为"点菜单没反应"）。
     */
    const onDown = (e: MouseEvent) => {
      const el = e.target
      if (el instanceof Element && el.closest('.wp3-map-ctx')) return
      onClose()
    }
    const onKey = (e: KeyboardEvent) => { if (e.key === 'Escape') onClose() }
    const onWheel = () => onClose()
    window.addEventListener('mousedown', onDown, true)
    window.addEventListener('wheel', onWheel, true)
    window.addEventListener('keydown', onKey)
    window.addEventListener('blur', onClose)
    return () => {
      window.removeEventListener('mousedown', onDown, true)
      window.removeEventListener('wheel', onWheel, true)
      window.removeEventListener('keydown', onKey)
      window.removeEventListener('blur', onClose)
    }
  }, [onClose])
  return null
}
