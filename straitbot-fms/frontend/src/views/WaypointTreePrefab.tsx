import { useCallback, useEffect, useMemo, useRef, useState } from 'react'
import {
  Button, Card, Empty, Input, Modal, Space, Spin, Tag, Tree, Select, Toast,
} from '@douyinfe/semi-ui'
import {
  IconChevronDown, IconChevronUp, IconSave, IconUpload,
  IconMapPin, IconPlus,
} from '@douyinfe/semi-icons'
import {
  getWaypointNodeTypes, listWaypointTrees, getWaypointTree, saveWaypointTree,
  createWaypointFile, importInspectionToWaypoint, uploadWaypointBackground,
  uploadWaypointCapture, getWaypointAlgorithms, getWaypointPtzPose,
  type WaypointTreeSummary, type AlgorithmItem,
} from '../api/waypointPrefab'
import { listDetectTrees, type DetectTreeSummary } from '../api/detectPrefab'
import type { NodeTypeInfo } from '../api/prefab'
import { gotoX, dispatchInspection, fetchRobotControlState } from '../api/railRobot'
import { ptzSnapshotBlob } from '../api/railPtz'
import { buildInspection, regenerateIds, ensureBoxIds, randomHex } from '../utils/inspectionBuild'
import { resolveImageUrl } from '../utils/prefabImage'
import { collectPointUsage } from '../utils/detectBoxBinding'
import InspectorForm from '../components/InspectorForm'
import WebRTCPlayer from '../components/WebRTCPlayer'
import RobotControlInline from '../components/RobotControlInline'
import TrackMap from '../components/TrackMap'
import DetectBoxTool from '../components/DetectBoxTool'
import type { DetectBoxItem } from '../components/DetectBoxTool'
import { sanitizePoints, type NormPt } from '../components/detectBoxGeometry'
import { uToX, trackLengthOf, sampleTrack, trackPointsFromNodes } from '../components/trackGeometry'
import type {
  MapWaypoint, MapMarker, MarkerKind, MapBackground, MapSection, MapIcon,
  TrackNodePoint, Pt,
} from '../components/trackGeometry'
import {
  SEP, parentPathOf,
  pickTrackPath, trackNodesOf, childPath, countOfType, roundPt, closeIndexOf,
  nearestTrackPath, placeNewEndpoint, placeNewControl,
  appendEndpoint, appendEndpointWithControl, withMovedPoint,
  insertBeside, insertBesidePoint,
} from '../utils/trackSpec'
import {
  getNodeByPath, topLevelPaths, removeManyByPaths,
  moveNodeInSpec, batchMoveNodes, resolveDropKind,
  type DropKind,
} from '../utils/specTree'
import { startDrag } from '../utils/splitter'
import { useRobotId } from '../store/robot'

const TYPE_LABEL: Record<string, string> = {
  GroupNode: '分组',
  WaypointNode: '航点',
  ActionPointNode: '动作点',
  MeasurePointNode: '测点',
  TrackNode: '轨道',
  TrackEndpointNode: '端点',
  TrackControlNode: '控制点',
  ClosePathNode: '闭合',
  ChargingPileNode: '充电桩',
  RfidCardNode: 'RFID 卡',
  BackgroundImageNode: '背景图',
  SectionMarkNode: '区段标记',
  IconMarkNode: '图标',
  DetectBoxNode: '检测框',
  AlgorithmConfigNode: '算法配置',
}
const TYPE_COLOR: Record<string, any> = {
  GroupNode: 'blue',
  WaypointNode: 'green',
  ActionPointNode: 'orange',
  MeasurePointNode: 'grey',
  TrackNode: 'violet',
  TrackEndpointNode: 'cyan',
  TrackControlNode: 'amber',
  ClosePathNode: 'purple',
  ChargingPileNode: 'amber',
  RfidCardNode: 'violet',
  BackgroundImageNode: 'cyan',
  SectionMarkNode: 'teal',
  IconMarkNode: 'light-blue',
  DetectBoxNode: 'cyan',
  AlgorithmConfigNode: 'purple',
}
const ACTION_TYPE_TEXT: Record<number, string> = { 1: '拍照', 2: '测温', 3: '录像' }

/** 地图上的"沿轨设施"种类 -> 树里的节点类型名 */
const MARKER_TYPE: Record<MarkerKind, string> = {
  charging: 'ChargingPileNode',
  rfid: 'RfidCardNode',
}

/** 背景图初始缩放的兜底跨度（米）：还没有轨道时，让图片宽度铺满这么多米 */
const BG_FIT_FALLBACK_M = 50

/* ------------------------------------------------------------ spec 纯函数（见 utils/specTree.ts） */

function defaultsFrom(schema: any): Record<string, any> {
  const out: Record<string, any> = {}
  for (const [k, d] of Object.entries<any>(schema?.properties || {})) {
    if (k === 'type' || k === 'children') continue
    if ('default' in d) out[k] = d.default
  }
  return out
}

function flattenNodes(node: any, path = 'root', acc: { key: string; node: any }[] = []): any[] {
  acc.push({ key: path, node })
  ;(node?.children || []).forEach((c: any, i: number) =>
    flattenNodes(c, `${path}${SEP}children${SEP}${i}`, acc))
  return acc
}

function collectParentKeys(node: any, path = 'root', acc: string[] = []): string[] {
  if (Array.isArray(node?.children) && node.children.length) {
    acc.push(path)
    node.children.forEach((c: any, i: number) =>
      collectParentKeys(c, `${path}${SEP}children${SEP}${i}`, acc))
  }
  return acc
}

function toTreeData(node: any, path = 'root'): any[] {
  const typeName = node?.type || '?'
  const props = node?.properties || {}
  let labelText = props.name || TYPE_LABEL[typeName] || typeName
  if (typeName === 'ActionPointNode' && props.action_type) {
    labelText += ` · ${ACTION_TYPE_TEXT[props.action_type] || ''}`
  }
  // 检测框**绑了测点的**整节点变绿：扫树的时候一眼看出哪些框还没绑，
  // 不用一个个点开看属性。颜色只认 point_id（name 只是给人看的镜像）
  const pointBound = typeName === 'DetectBoxNode' && Boolean(props.point_id)
  const treeNode: any = {
    key: path,
    value: path,
    label: (
      <span
        style={{
          display: 'inline-flex', alignItems: 'center', gap: 6,
          color: pointBound ? 'var(--semi-color-success)' : undefined,
        }}
        title={pointBound ? `已绑测点：${props.point_name || props.point_id}` : undefined}
      >
        <span>{labelText}</span>
        <Tag size="small" color={pointBound ? 'green' : (TYPE_COLOR[typeName] || 'grey')}>
          {TYPE_LABEL[typeName] || typeName}
        </Tag>
        {pointBound ? <Tag size="small" color="green">{props.point_name || props.point_id}</Tag> : null}
      </span>
    ),
  }
  if (Array.isArray(node?.children) && node.children.length) {
    treeNode.children = node.children.map((c: any, i: number) =>
      toTreeData(c, `${path}${SEP}children${SEP}${i}`)[0])
  }
  return [treeNode]
}

/* 类型继承树（仅航点系） */
function buildTypeTree(types: Record<string, NodeTypeInfo>): any[] {
  const root: any = {
    key: 'WaypointNodeBase', value: 'WaypointNodeBase',
    label: <span style={{ fontWeight: 600 }}>航点节点类型</span>, children: [] as any[],
  }
  for (const name of Object.keys(types).sort()) {
    const info = types[name]
    // 废弃节点（后端 __hidden__，如旧的 AlgorithmConfigNode）仍能解析旧数据，
    // 但不再出现在"添加节点"类型目录里
    if (info.hidden) continue
    root.children.push({
      key: `type/${name}`, value: name, typeName: name,
      label: (
        <span style={{ display: 'flex', flexDirection: 'column', gap: 2 }}>
          <span style={{ fontWeight: 500 }}>{TYPE_LABEL[name] || name} <span style={{ color: 'var(--semi-color-text-2)', fontWeight: 400 }}>{name}</span></span>
          {info.description ? <span style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>{info.description}</span> : null}
        </span>
      ),
    })
  }
  return [root]
}

function filterTypeTree(nodes: any[], kw: string): any[] {
  const out: any[] = []
  for (const n of nodes) {
    const hit = (n.typeName || '').toLowerCase().includes(kw)
      || (TYPE_LABEL[n.typeName] || '').includes(kw)
    const children = n.children?.length ? filterTypeTree(n.children, kw) : []
    if (hit || children.length) out.push({ ...n, children: children.length ? children : undefined })
  }
  return out
}

const MENU_STYLE: React.CSSProperties = {
  position: 'fixed', minWidth: 168, background: '#fff',
  border: '1px solid var(--semi-color-border)', borderRadius: 6,
  boxShadow: '0 6px 20px rgba(0,0,0,.14)', padding: 4, zIndex: 1001, fontSize: 13,
}

interface CtxMenu { x: number; y: number; target: string }
interface Clipboard { mode: 'copy' | 'cut'; nodes: any[] }

function sanitizeFileName(name: string): string {
  return (name || '巡检任务').replace(/[\\/:*?"<>|]/g, '_').trim() || '巡检任务'
}

/* ------------------------------------------------------------ 页面 */

export default function WaypointTreePrefab() {
  const [loading, setLoading] = useState(true)
  const [nodeTypes, setNodeTypes] = useState<Record<string, NodeTypeInfo>>({})
  const [algorithms, setAlgorithms] = useState<AlgorithmItem[]>([])
  /**
   * 可选检测流程（`data/prefabs/检测算法` 下的文件）。
   *
   * 检测框可以**引用**一条流程（只存路径）：框说"画面上哪块区域"，
   * 流程说"拍到之后怎么判定、要不要发短信"。这里只是下拉的数据源，
   * 拉不到不影响画框与绑算法。
   */
  const [detectFlows, setDetectFlows] = useState<DetectTreeSummary[]>([])
  const [trees, setTrees] = useState<WaypointTreeSummary[]>([])
  const [currentRel, setCurrentRel] = useState('')
  const [spec, setSpec] = useState<Record<string, any> | null>(null)
  const [selectedPath, setSelectedPath] = useState('root')
  const [nodeSel, setNodeSel] = useState<Set<string>>(new Set())
  const [dragPaths, setDragPaths] = useState<Set<string>>(new Set())

  /* 三栏布局：树宽 / 右栏宽 / 视频区高，均可拖拽调整 */
  const [treeWidth, setTreeWidth] = useState(400)
  const [rightWidth, setRightWidth] = useState(360)
  const [videoHeight, setVideoHeight] = useState(260)
  const { selectedRid } = useRobotId()
  const [expandedKeys, setExpandedKeys] = useState<Set<string>>(new Set())
  const [saving, setSaving] = useState(false)
  const [ctxMenu, setCtxMenu] = useState<CtxMenu | null>(null)
  const [clipboard, setClipboard] = useState<Clipboard | null>(null)
  const [addDialog, setAddDialog] = useState<{
    targetPath: string
    /** before / after：贴着目标节点插入（"在前 / 后添加子节点"）；不传则追加到末尾 */
    position?: 'before' | 'after'
  } | null>(null)
  const [addType, setAddType] = useState<string | undefined>(undefined)
  const [addKeyword, setAddKeyword] = useState('')
  const [jsonTarget, setJsonTarget] = useState<string | null>(null)
  const [newFileName, setNewFileName] = useState('')
  const [newFileOpen, setNewFileOpen] = useState(false)
  const fileInputRef = useRef<HTMLInputElement>(null)
  /** 背景图上传：地图工具栏点「添加背景图」时触发这个隐藏 input */
  const bgFileRef = useRef<HTMLInputElement>(null)
  const nodeAnchor = useRef('root')
  const mods = useRef({ shift: false, ctrl: false })

  useEffect(() => {
    const sync = (e: KeyboardEvent) => {
      mods.current.shift = e.shiftKey
      mods.current.ctrl = e.ctrlKey || e.metaKey
    }
    const clear = () => { mods.current.shift = false; mods.current.ctrl = false }
    window.addEventListener('keydown', sync)
    window.addEventListener('keyup', sync)
    window.addEventListener('blur', clear)
    return () => {
      window.removeEventListener('keydown', sync)
      window.removeEventListener('keyup', sync)
      window.removeEventListener('blur', clear)
    }
  }, [])

  const refreshFiles = useCallback(async () => {
    const { data } = await listWaypointTrees()
    setTrees(data.trees)
    return data.trees
  }, [])

  const applySpec = useCallback((sp: Record<string, any>) => {
    // 老数据补 box_id：检测框的身份字段是后加的，改造前编的树里没有它 ——
    // 那样下发推理任务时框是匿名的（算法结果回来认不回是哪个框）。
    // 在**加载时**补一次，保存后落盘；已经有 id 的绝不动（它是稳定标识，
    // 重新生成等于把历史识别结果全部解绑）。
    const patched = ensureBoxIds(sp?.root)
    if (patched) Toast.info(`已为 ${patched} 个检测框补生成检测框 ID，保存后生效`)
    setSpec(sp)
    setSelectedPath('root')
    setNodeSel(new Set())
    setExpandedKeys(new Set(collectParentKeys(sp.root || {})))
  }, [])

  const loadTree = useCallback(async (rel: string) => {
    const { data } = await getWaypointTree(rel)
    setCurrentRel(rel)
    applySpec(data.spec)
  }, [applySpec])

  useEffect(() => {
    (async () => {
      try {
        const [list, types] = await Promise.all([refreshFiles(), getWaypointNodeTypes()])
        setNodeTypes(types.data)
        // 算法目录单独拉：它读的是 data/algorithms.json，缺了/写坏了也只是
        // 下拉没选项，不该把"打开页面"这件事一起搞挂
        try {
          const { data: ag } = await getWaypointAlgorithms()
          setAlgorithms(ag.algorithms || [])
          if (ag.warning) Toast.warning(`算法类型目录读取异常：${ag.warning}`)
        } catch { /* 拦截器已提示 */ }
        // 检测流程目录同样单独拉：它属于**第三棵 prefab 树**，缺了只是下拉没选项
        try {
          const { data: dt } = await listDetectTrees()
          setDetectFlows(dt.trees || [])
        } catch { /* 拦截器已提示 */ }
        if (list.length > 0) await loadTree(list[0].rel_path)
      } catch { /* 拦截器已提示 */ } finally { setLoading(false) }
    })()
  }, [refreshFiles, loadTree])

  const treeData = useMemo(() => (spec?.root ? toTreeData(spec.root) : []), [spec])
  const nodeFlat = useMemo(() => (spec?.root ? flattenNodes(spec.root) : []), [spec])

  /**
   * 地图用航点列表：把树里所有 WaypointNode 的 `x`（沿轨弧长）抽出来。
   *
   * 只取航点、不取动作点/测点/分组——地图上每个点代表"机器人会停的位置"，
   * 动作点是挂在航点上执行的动作，画上去只会让图变糊。
   * 注意 `x` 只用于**排布**，曲线控制点与它无关（用户已确认曲线纯可视化）。
   */
  const mapWaypoints = useMemo<MapWaypoint[]>(() => {
    if (!spec?.root) return []
    return flattenNodes(spec.root)
      .filter(({ node }) => node?.type === 'WaypointNode')
      .map(({ key, node }) => ({
        path: key,
        x: Number(node.properties?.x),
        label: node.properties?.name || '航点',
        type: node.type,
        u: 0,
      }))
      .filter((w) => Number.isFinite(w.x))
  }, [spec])

  /**
   * 地图上的**沿轨设施**：充电桩与 RFID 卡。
   *
   * 与航点一样按 `x`（沿轨弧长，米）定位，只是画法不同（方=桩、菱=卡）。
   * 它们和航点**共用同一把尺子**（轨道总长，米），
   * 否则会各用一套量程、桩/卡跑到与航点完全对不上的位置。
   */
  const mapMarkers = useMemo<MapMarker[]>(() => {
    if (!spec?.root) return []
    return flattenNodes(spec.root)
      .filter(({ node }) => node?.type === 'ChargingPileNode' || node?.type === 'RfidCardNode')
      .map(({ key, node }) => ({
        path: key,
        kind: (node.type === 'ChargingPileNode' ? 'charging' : 'rfid') as MarkerKind,
        x: Number(node.properties?.x),
        label: node.properties?.name
          || (node.type === 'ChargingPileNode' ? '充电桩' : 'RFID 卡'),
      }))
      .filter((m) => Number.isFinite(m.x))
  }, [spec])

  /**
   * 地图上的**区段标记**：给一段轨道加注记（门 / 窗 / 减速…）。
   *
   * 覆盖 `[x - 半径, x + 半径]` 这段弧长（米），与航点/设施共用同一把尺子
   * （轨道总长），否则"这一段是门"会标到轨道别的位置上去。
   */
  const mapSections = useMemo<MapSection[]>(() => {
    if (!spec?.root) return []
    return flattenNodes(spec.root)
      .filter(({ node }) => node?.type === 'SectionMarkNode')
      .map(({ key, node }) => ({
        path: key,
        x: Number(node.properties?.x),
        radius: Number(node.properties?.radius),
        color: String(node.properties?.color || '').trim(),
        label: node.properties?.name || node.properties?.kind || '区段',
      }))
      .filter((s) => Number.isFinite(s.x))
      .map((s) => ({ ...s, radius: Number.isFinite(s.radius) && s.radius > 0 ? s.radius : 0 }))
  }, [spec])

  /**
   * 地图上的**图标标记**：任意位置（世界坐标 x/y）摆一个内置矢量图标。
   *
   * 与区段/设施不同：不吸附轨道、不共用弧长这把尺子，坐标就是地图世界坐标（米），
   * 所以没有轨道、或者想标在背景图某个房间里时照样能摆。
   * `icon` / `color` / `size` 都交给 `TrackMap` 里的 normalize* 兜底，
   * 这里不做校验——脏数据的兜底规则只应存在一处。
   */
  const mapIcons = useMemo<MapIcon[]>(() => {
    if (!spec?.root) return []
    return flattenNodes(spec.root)
      .filter(({ node }) => node?.type === 'IconMarkNode')
      .map(({ key, node }) => ({
        path: key,
        x: Number(node.properties?.x),
        y: Number(node.properties?.y),
        icon: String(node.properties?.icon || '').trim(),
        color: String(node.properties?.color || '').trim(),
        size: Number(node.properties?.size),
        label: node.properties?.name || '图标',
      }))
      .filter((i) => Number.isFinite(i.x) && Number.isFinite(i.y))
  }, [spec])

  /**
   * 地图背景图：整张地图**只认一个** `BackgroundImageNode`（取树里第一个）。
   *
   * 上传是"添加/更换"语义：已经有底图时就改它的 `src`，不会叠加第二张——
   * 两张半透明底图压在一起只会导致谁也看不清、谁也拖不动。
   * 手填路径也走同一个节点（检视器里改 `src` 即可）。
   */
  const mapBackground = useMemo<MapBackground | null>(() => {
    if (!spec?.root) return null
    const found = flattenNodes(spec.root)
      .filter(({ node }) => node?.type === 'BackgroundImageNode')
      .map(({ key, node }) => ({
        path: key,
        src: String(node.properties?.src || '').trim(),
        x: Number(node.properties?.x),
        y: Number(node.properties?.y),
        scale: Number(node.properties?.scale),
        opacity: Number(node.properties?.opacity),
      }))
      .filter((b) => b.src)
    if (!found.length) return null
    const b = found[0]
    return {
      ...b,
      x: Number.isFinite(b.x) ? b.x : 0,
      y: Number.isFinite(b.y) ? b.y : 0,
      scale: Number.isFinite(b.scale) && b.scale > 0 ? b.scale : 1,
      opacity: Number.isFinite(b.opacity) ? Math.min(1, Math.max(0, b.opacity)) : 0.5,
    }
  }, [spec])

  /** 背景图在地图上的微调（拖动 / 缩放）写回节点属性 */
  const applyBackground = (patch: { x?: number; y?: number; scale?: number }) => {
    if (!spec || !mapBackground) return
    const next = JSON.parse(JSON.stringify(spec))
    const node = getNodeByPath(next, mapBackground.path)
    if (!node) return
    node.properties = { ...(node.properties || {}), ...patch }
    setSpec(next)
  }

  /**
   * 上传背景图：存到后端静态目录，再把路径写进 `BackgroundImageNode`。
   *
   * 初始缩放让图片宽度铺满"当前轨道那么长"的米数（世界坐标就是米，
   * 再写死一个常数就会把几十米的轨道压成一小撮，或者把图撑到天外）；
   * 之后在检视器里改 `scale`，或在图上拖右下角手柄就行。
   */
  const onBackgroundFile = async (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0]
    // 立即清空，否则连着选同一个文件不会再触发 change
    e.target.value = ''
    if (!file || !spec) return
    if (!nodeTypes.BackgroundImageNode) {
      Toast.warning('后端未提供 BackgroundImageNode 节点类型，请重启后端服务后重试')
      return
    }
    try {
      const { data: r } = await uploadWaypointBackground(file)
      if (!r?.ok || !r?.path) { Toast.error('背景图上传失败：后端未返回图片路径'); return }
      // 还没有轨道时给个不夸张的默认跨度，别让 scale 变成 0
      const fitM = trackLengthM > 0 ? trackLengthM : BG_FIT_FALLBACK_M
      const scale = r.width > 0 ? Number((fitM / r.width).toFixed(5)) : 1
      const next = JSON.parse(JSON.stringify(spec))
      let path = ''
      if (mapBackground) {
        const node = getNodeByPath(next, mapBackground.path)
        if (!node) { Toast.error('背景图节点已失效，请刷新后重试'); return }
        node.properties = { ...(node.properties || {}), src: r.path, scale }
        path = mapBackground.path
      } else {
        const props = defaultsFrom(nodeTypes.BackgroundImageNode?.schema)
        props.name = '背景图'
        props.src = r.path
        props.scale = scale
        props.x = 0
        props.y = 0
        next.root.children = next.root.children || []
        next.root.children.push({ type: 'BackgroundImageNode', properties: props })
        path = childPath('root', next.root.children.length - 1)
        setExpandedKeys((prev) => new Set(prev).add('root'))
      }
      setSpec(next)
      setSelectedPath(path)
      setNodeSel(new Set([path]))
      Toast.success('背景图已就绪 · 选中它即可在地图上拖动微调，或在检视器里改路径 / 缩放 / 不透明度')
    } catch (err: any) {
      Toast.error(`背景图上传失败：${err?.response?.data?.detail || err?.message || err}`)
    }
  }

  /* ------------------------------------------------------------ 轨道（独立于航点的数据）

     轨道不是从航点算出来的，而是树里一条条真实的 `TrackNode`：
     children 中**平铺**着端点与控制点，靠顺序表达走向（解析规则见
     `trackGeometry.parseTrackNodes`）。航点仍然只按 `x`（沿轨弧长）吸附到
     当前轨道上显示，两者互不写回。 */

  /** 树里所有 TrackNode */
  const tracks = useMemo(
    () => (spec?.root
      ? flattenNodes(spec.root).filter(({ node }) => node?.type === 'TrackNode')
      : []),
    [spec],
  )

  /**
   * 当前编辑的轨道路径：优先"选中节点所属的那条"，否则第一条。
   * 判定规则（含端点/控制点归属）见 `utils/trackSpec.pickTrackPath`。
   */
  const currentTrackPath = useMemo(
    () => pickTrackPath(tracks, selectedPath),
    [tracks, selectedPath],
  )

  const currentTrack = useMemo(
    () => (currentTrackPath && spec ? getNodeByPath(spec, currentTrackPath) : null),
    [spec, currentTrackPath],
  )

  /** 传给地图的平铺节点（顺序即路径走向），转换规则见 `utils/trackSpec` */
  const trackNodes = useMemo<TrackNodePoint[]>(
    () => (currentTrackPath ? trackNodesOf(currentTrackPath, currentTrack) : []),
    [currentTrackPath, currentTrack],
  )

  /**
   * 当前轨道的真实长度 (m)。
   *
   * 世界坐标就是米，所以把平铺节点还原成曲线再采样，得到的弧长就是米数。
   * 页面侧也要能算这个数，是因为"在地图上点一下加个航点"要把 u 反推成 x——
   * 必须和地图里那把尺子（`trackLengthOf`）是同一个值，否则点在 A 处、
   * 存进去的 x 却对应 B 处。
   */
  const trackLengthM = useMemo(() => {
    const pts = trackPointsFromNodes(trackNodes)
    if (pts.length < 2) return 0
    const closed = trackNodes.some((n) => n.kind === 'close')
    return sampleTrack(pts, 24, closed).total
  }, [trackNodes])

  const selectedNode = useMemo(() => {
    if (!spec) return null
    return getNodeByPath(spec, selectedPath)
  }, [spec, selectedPath])

  const selectedSchema = useMemo(() => {
    if (!selectedNode?.type) return null
    return nodeTypes[selectedNode.type]?.schema || null
  }, [selectedNode, nodeTypes])

  /* ------------------------------------------------------------ 检测框（拍照动作点）

     检测框是**动作点底下的 DetectBoxNode**，不是画布的内部状态：
     画布画的东西、列表列的东西、树里躺的东西始终是同一份 spec，
     所以保存/导入导出/版本对比全都自动带上，不存在"画了没存上"。

     只在**拍照**动作点上出现——测温(2)/录像(3)没有那张可见光抓拍图，
     框也无从画起。 */

  /** 拍照动作点：action_type=1（可见光拍照）；字段缺失时按默认 1 处理 */
  const isPhotoAction = useMemo(
    () => selectedNode?.type === 'ActionPointNode'
      && Number(selectedNode.properties?.action_type ?? 1) === 1,
    [selectedNode],
  )

  const detectImageSrc = useMemo(() => {
    const v = String(selectedNode?.properties?.imageUrl || '')
    return v ? resolveImageUrl(v, currentRel) : ''
  }, [selectedNode, currentRel])

  const detectBoxes = useMemo<DetectBoxItem[]>(() => {
    if (!isPhotoAction) return []
    const kids: any[] = selectedNode?.children || []
    const out: DetectBoxItem[] = []
    kids.forEach((n, i) => {
      if (n?.type !== 'DetectBoxNode') return
      const pts = sanitizePoints(n.properties?.points)
      if (pts.length < 3) return  // 少于 3 点围不出区域，画出来只是条线
      out.push({
        path: childPath(selectedPath, i),
        shape: n.properties?.shape === 'polygon' ? 'polygon' : 'rect',
        points: pts,
        pointId: String(n.properties?.point_id || ''),
        pointName: String(n.properties?.point_name || ''),
        detectFlow: String(n.properties?.detect_flow || ''),
        name: String(n.properties?.name || ''),
      })
    })
    return out
  }, [isPhotoAction, selectedNode, selectedPath])

  /**
   * 整棵树的测点占用表：测点 id -> "航点名 / 动作点名 / 检测框 #2"。
   *
   * **必须扫整棵树**：被别的航点 / 别的动作点（含测温点）绑走的测点一样算占用，
   * 检测框工具只看得到当前动作点，判断不了"这个测点是不是早被别处用了"。
   */
  const pointUsage = useMemo(() => collectPointUsage(spec), [spec])

  /**
   * 检测流程的引用 id（写进检测框 `detect_flow` 的值）：优先流程根的检测编号
   * detect_id，编号留空时用文件名（不含 .prefab.json）。
   */
  const flowRefKey = (t: DetectTreeSummary) => {
    const id = String(t.root?.detect_id || '').trim()
    if (id) return id
    return t.rel_path.split('/').pop()!.replace(/\.prefab\.json$/i, '')
  }
  /** 流程下拉显示名：文件名为主，带编号 / 场景作辅助辨识 */
  const flowLabel = (t: DetectTreeSummary) => {
    const stem = t.rel_path.split('/').pop()!.replace(/\.prefab\.json$/i, '')
    const id = String(t.root?.detect_id || '').trim()
    const scene = String(t.root?.scene || '').trim()
    let label = id ? `${stem}（${id}）` : stem
    if (scene) label += ` · ${scene}`
    return label
  }

  /** 检测框可选的检测流程（损坏文件不列）；空项 / 失效项由检测框工具自行补 */
  const detectFlowChoices = useMemo(
    () => detectFlows.filter((t) => t.root && !t.error)
      .map((t) => ({ value: flowRefKey(t), label: flowLabel(t) })),
    [detectFlows],
  )

  /**
   * 检视器里 `ui.optionsFrom` 的数据源。
   *
   * - `detectFlows`：检测框「检测算法流程」下拉（optionsFrom="detectFlows"），
   *   选项在第三棵树 `data/prefabs/检测算法`，不在 schema 写死，含一个"未指定"空项。
   * - `algorithms`：仅为打开旧数据里残留的 AlgorithmConfigNode（已废弃、隐藏）兜底，
   *   新数据不再产生这种节点。
   */
  const optionSources = useMemo(() => ({
    detectFlows: [{ value: '', label: '未指定检测流程' }, ...detectFlowChoices],
    algorithms: algorithms.map((a) => ({
      value: a.id,
      label: a.category ? `${a.category} · ${a.name}` : a.name,
    })),
  }), [algorithms, detectFlowChoices])

  /** 新建检测框：挂在动作点**末尾**，返回新节点路径给画布选中 */
  const addDetectBox = (shape: 'rect' | 'polygon', points: NormPt[]): string | null => {
    if (!spec || !selectedNode) return null
    const props = defaultsFrom(nodeTypes.DetectBoxNode?.schema)
    props.name = `检测框 ${detectBoxes.length + 1}`
    // ⚠️ box_id 必须**在这里**生成：它是检测框自己的身份（算法回调靠它认回本框），
    // 不能等下发时现摇 —— 那样每次 build 都是新 id，历史结果全对不上。
    props.box_id = randomHex()
    props.shape = shape
    props.points = points.map((p) => ({ x: Number(p.x.toFixed(4)), y: Number(p.y.toFixed(4)) }))
    const next = JSON.parse(JSON.stringify(spec))
    const parent = getNodeByPath(next, selectedPath)
    if (!parent) return null
    parent.children = parent.children || []
    const idx = parent.children.length
    parent.children.push({ type: 'DetectBoxNode', properties: props })
    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(selectedPath))
    return childPath(selectedPath, idx)
  }

  /**
   * 给检测框绑测点。
   *
   * id 与 name **一起写**：列表和导出要显示"这个框拍的是哪个测点"，
   * 不写名字就得为了显示再去查一次档案（和 algorithm 那份镜像同理）。
   */
  const bindBoxPoint = (path: string, pointId: string, pointName: string) =>
    patchNodeProps(path, { point_id: pointId, point_name: pointName })

  /**
   * 解绑测点：`point_id` 与 `point_name` **一起清**。
   * 只清 id 会留下一个"看着还绑着"的名字（列表按 id 判断、名字却还在，对不上）。
   */
  const unbindBoxPoint = (path: string) =>
    patchNodeProps(path, { point_id: '', point_name: '' })

  /**
   * 给检测框指定**引用哪条检测流程**。
   *
   * 只写一个路径字符串：流程的内容（节流 / 连续确认 / 告警 / 短信）在那棵树里，
   * 抄一份到框上必然漂移（改一次流程要改 N 个框）。
   */
  const setBoxDetectFlow = (path: string, rel: string) =>
    patchNodeProps(path, { detect_flow: rel })

  /** 画布上拖框搬家 / 拖端点改形状（松手才调一次，不逐帧改树） */
  const setBoxPoints = (path: string, points: NormPt[]) =>
    patchNodeProps(path, {
      points: points.map((p) => ({ x: Number(p.x.toFixed(4)), y: Number(p.y.toFixed(4)) })),
    })

  const removeDetectBox = (path: string) => {
    if (!spec) return
    const next = JSON.parse(JSON.stringify(spec))
    const removed = removeManyByPaths(next.root, [path])
    if (removed > 0) setSpec(next)
  }

  const typeTreeFiltered = useMemo(() => {
    const tree = buildTypeTree(nodeTypes)
    const kw = addKeyword.trim().toLowerCase()
    const filtered = kw ? filterTypeTree(tree, kw) : tree

    /**
     * 往**轨道的扁平子节点序列**里插时，只保留端点与控制点。
     *
     * 轨道的 children 是"顺序即语义"的（两个端点之间夹着的控制点归属这一段），
     * 往里塞航点/分组会破坏解析。其余父级（分组下的航点序列等）不限制类型。
     */
    if (!addDialog?.position) return filtered
    const parent = addDialog.targetPath === 'root'
      ? null
      : getNodeByPath(spec, parentPathOf(addDialog.targetPath))
    if (parent?.type !== 'TrackNode') return filtered
    const allowed = new Set(['TrackEndpointNode', 'TrackControlNode'])
    const keep = (nodes: any[]): any[] => nodes
      .filter((n) => !n.typeName || allowed.has(n.typeName))
      .map((n) => ({ ...n, children: n.children?.length ? keep(n.children) : undefined }))
    return keep(filtered)
  }, [nodeTypes, addKeyword, addDialog?.position, addDialog?.targetPath, spec])

  /* ------------------------------------------------------------ 选择/右键 */

  const onNodeSelect = (key: string) => {
    const m = mods.current
    if (m.ctrl) {
      setNodeSel((prev) => {
        const n = new Set(prev)
        if (n.has(key)) n.delete(key); else n.add(key)
        return n
      })
    } else if (m.shift && nodeAnchor.current && nodeAnchor.current !== key) {
      const ks = nodeFlat.map((d) => d.key)
      const a = ks.indexOf(nodeAnchor.current)
      const b = ks.indexOf(key)
      if (a >= 0 && b >= 0) {
        const [lo, hi] = a <= b ? [a, b] : [b, a]
        setNodeSel(new Set(ks.slice(lo, hi + 1)))
      }
      nodeAnchor.current = key
    } else {
      setNodeSel(new Set([key]))
      nodeAnchor.current = key
    }
    setSelectedPath(key)
  }

  const onNodeCtx = (e: React.MouseEvent, node: any) => {
    e.preventDefault()
    e.stopPropagation()
    const key = (node?.key || node?.value || 'root') as string
    if (!nodeSel.has(key)) { setNodeSel(new Set([key])); setSelectedPath(key) }
    setCtxMenu({ x: e.clientX, y: e.clientY, target: key })
  }

  /* ------------------------------------------------------------ 编辑操作 */

  /**
   * 给**任意路径**的节点打属性补丁。
   *
   * 与 `updateProps` 的区别：那个固定写当前选中节点（检视器用）。
   * 地图拖拽、重新拍照这类操作动的是"地图上那一个"，未必等于当前选中项，
   * 所以要从路径走。
   */
  const patchNodeProps = (path: string, patch: Record<string, any>) => {
    if (!spec) return
    const next = JSON.parse(JSON.stringify(spec))
    const node = getNodeByPath(next, path)
    if (!node) return
    node.properties = { ...(node.properties || {}), ...patch }
    setSpec(next)
  }

  const updateProps = (patch: Record<string, any>) => patchNodeProps(selectedPath, patch)

  /** 选中的是动作点（拍照/测温/录像都算，云台位姿 pan/tilt/zoom 通用） */
  const isActionPoint = selectedNode?.type === 'ActionPointNode'
  const isWaypoint = selectedNode?.type === 'WaypointNode'
  const [ptzPoseLoading, setPtzPoseLoading] = useState(false)

  /** 使用当前云台位姿：后端按 robot.prefab.json 的云台配置现取，回填 pan/tilt/zoom。 */
  const useCurrentPtzPose = useCallback(async () => {
    setPtzPoseLoading(true)
    try {
      const { data } = await getWaypointPtzPose()
      const patch: Record<string, any> = {}
      if (data.pan != null) patch.pan = Number(data.pan.toFixed(2))
      if (data.tilt != null) patch.tilt = Number(data.tilt.toFixed(2))
      if (data.zoom != null) patch.zoom = Number(data.zoom.toFixed(2))
      if (Object.keys(patch).length) {
        updateProps(patch)
        Toast.success(`已使用当前云台位姿 pan=${patch.pan}° tilt=${patch.tilt}° zoom=${patch.zoom}`)
      } else {
        Toast.warning('未能从云台解析到 pan/tilt/zoom')
      }
    } catch { /* http 拦截器已提示 */ } finally {
      setPtzPoseLoading(false)
    }
  }, [updateProps])

  const [poseLoading, setPoseLoading] = useState(false)

  /** 使用当前位姿：从机器人 runtime 读底盘实时位姿，回填航点 x/y/theta（z 不动）。 */
  const useCurrentPose = useCallback(async () => {
    setPoseLoading(true)
    try {
      const st = await fetchRobotControlState()
      const pose = st.pose
      const patch: Record<string, any> = {}
      if (pose?.x != null) patch.x = Number(pose.x.toFixed(3))
      if (pose?.y != null) patch.y = Number(pose.y.toFixed(3))
      if (pose?.yaw != null) patch.theta = Number(pose.yaw.toFixed(1))
      if (Object.keys(patch).length) {
        updateProps(patch)
        Toast.success(`已使用当前位姿 x=${patch.x}m y=${patch.y}m theta=${patch.theta}°`)
      } else {
        Toast.warning('未能读取到机器人当前位姿')
      }
    } catch { /* http 拦截器已提示 */ } finally {
      setPoseLoading(false)
    }
  }, [updateProps])

  /**
   * 地图拖动航点 / 充电桩 / RFID / 区段：改它的沿轨弧长 `x`。
   *
   * u -> x 的换算已经在 `TrackMap` 里做掉了（量程是地图按轨道总长算的），
   * 这里只管落属性——否则两边各算一套长度，松手瞬间点会跳。
   */
  const moveAlongX = (path: string, x: number) => patchNodeProps(path, { x })

  /** 地图拖动图标标记：改世界坐标 x/y（图标不吸附轨道） */
  const moveIconXY = (path: string, p: Pt) => patchNodeProps(path, { x: p.x, y: p.y })

  /**
   * 添加子节点。
   *
   * **端点/控制点会被归到它所属的那条轨道下**：平铺约定只认 TrackNode 的
   * 直接子节点。若用户在树上选中一个端点再"添加子节点"，直接挂成子级会让它
   * 变成孙节点——地图读不到，表现为"加了却看不见"。所以这里先向上找最近轨道。
   *
   * 落位也讲究（详见 `utils/trackSpec`）：
   * - 端点追加到末尾，坐标接在最后一个点之后（不然会叠在原点，像没加上）；
   * - 控制点插到**最后一个端点之前**，且要求已有 ≥2 个端点（没有段可归属时
   *   追加到末尾会被解析丢弃，同样"加了没反应"）。
   */
  /**
   * 添加子节点。
   *
   * `position` 为 'before' / 'after' 时，新节点**紧贴**目标节点插到同一层
   * （"在前 / 后添加子节点"）——对任何非根节点都成立：航点、动作点、端点…
   * 只有 root 没有"前后"可言。
   *
   * 轨道系（端点 / 控制点）哪怕目标是别处，也要归到它所属的轨道下，
   * 并且要遵守"控制点归属哪一段"的顺序语义，所以走 `insertBeside`；
   * 其余类型就是普通的同级插入，走 `insertBesidePoint`（x 取相邻兄弟中点，
   * 保证树序与地图上的左右顺序一致）。
   * 落位规则都在 utils/trackSpec.ts 里。
   */
  const addChild = (
    targetPath: string,
    typeName?: string,
    position?: 'before' | 'after',
  ) => {
    if (!spec || !typeName) return
    const next = JSON.parse(JSON.stringify(spec))
    const trackChild = typeName === 'TrackEndpointNode' || typeName === 'TrackControlNode'
      || typeName === 'ClosePathNode'

    let parentPath = targetPath
    let insertAt: number | null = null
    let coord: Pt | null = null
    const targetIdx = Number(targetPath.split(SEP).pop())

    if (position && targetPath !== 'root') {
      if (trackChild) {
        parentPath = nearestTrackPath(nodeFlat, targetPath) || ''
        if (!parentPath) {
          Toast.warning('端点 / 控制点 / 闭合 必须挂在「轨道」节点下，请先添加一个轨道')
          return
        }
        const kids: any[] = getNodeByPath(next, parentPath)?.children || []
        // 闭合标记只是个哨兵，永远挂轨道末尾，说不上"前后"
        if (typeName === 'ClosePathNode') {
          insertAt = kids.length
        } else {
          if (typeName === 'TrackControlNode' && countOfType(kids, 'TrackEndpointNode') < 2) {
            Toast.warning('控制点需要归属一段路径，请先让轨道上有至少两个端点')
            return
          }
          // 目标是轨道本身时没有"前后"，贴着插没有意义 -> 退回追加
          const place = parentPath === targetPath ? null : insertBeside(kids, targetIdx, position,
            { lift: typeName === 'TrackControlNode' ? 60 : 0 })
          if (!place) { Toast.warning('无法确定插入位置，请刷新后重试'); return }
          insertAt = place.index
          coord = place.point
        }
      } else {
        parentPath = parentPathOf(targetPath)
        const kids: any[] = getNodeByPath(next, parentPath)?.children || []
        const place = insertBesidePoint(kids, targetIdx, position)
        if (!place) { Toast.warning('无法确定插入位置，请刷新后重试'); return }
        insertAt = place.index
        // 只有带 x 的类型（航点这类）才给坐标，动作点/测点没有 x，别硬塞
        coord = nodeTypes[typeName]?.schema?.properties?.x ? place.point : null
      }
    } else if (trackChild) {
      parentPath = nearestTrackPath(nodeFlat, targetPath) || ''
      if (!parentPath) {
        Toast.warning('端点 / 控制点 / 闭合 必须挂在「轨道」节点下，请先添加一个轨道')
        return
      }
      const kids: any[] = getNodeByPath(next, parentPath)?.children || []

      // 闭合标记只是个哨兵：挂在轨道末尾，表示"最后一个端点连回第一个端点"
      if (typeName === 'ClosePathNode') {
        if (closeIndexOf(kids) >= 0) { Toast.warning('这条轨道已经闭合了'); return }
        if (countOfType(kids, 'TrackEndpointNode') < 2) {
          Toast.warning('闭合需要轨道上至少有 2 个端点')
          return
        }
        insertAt = kids.length
      } else {
        const place = typeName === 'TrackEndpointNode'
          ? placeNewEndpoint(kids)
          : placeNewControl(kids)
        if (!place) {
          Toast.warning('控制点需要归属一段路径，请先让轨道上有至少两个端点')
          return
        }
        insertAt = place.index
        coord = place.point
      }
    }

    const parent = getNodeByPath(next, parentPath)
    if (!parent) return
    parent.children = parent.children || []
    const props = defaultsFrom(nodeTypes[typeName]?.schema)
    const n = countOfType(parent.children, typeName) + 1
    props.name = `${TYPE_LABEL[typeName] || typeName} ${n}`
    if (coord) Object.assign(props, roundPt(coord))

    const at = insertAt === null ? parent.children.length : insertAt
    parent.children.splice(at, 0, { type: typeName, properties: props })
    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(parentPath))
    // 选中新节点，方便马上在检视器里改坐标
    const newPath = childPath(parentPath, at)
    setSelectedPath(newPath)
    setNodeSel(new Set([newPath]))
  }

  /**
   * `u`（轨道归一化位置）-> 沿轨弧长 `x` (m)。
   *
   * 与地图**同源**：都用 `trackLengthOf` 取量程（有轨道 = 弧长米数，
   * 没轨道 = 兜底量程），否则地图按一把尺子画、这里按另一把算，
   * 新加的点会落在别的地儿。
   */
  const xAtU = (u: number): number => {
    const xs = nodeFlat
      .filter(({ node }) => node?.type === 'WaypointNode')
      .map(({ node }) => Number(node.properties?.x))
      .filter((v) => Number.isFinite(v))
    return Number(uToX(trackLengthOf(trackLengthM, xs), u).toFixed(3))
  }

  /**
   * 把新建的沿轨节点（航点 / 充电桩 / RFID 卡）插进树。
   *
   * 按 `x` 大小插到兄弟序列中的正确位置，保证"树里的顺序 ==
   * 轨道上从起点到终点的顺序"——否则新加的点会跑到列表末尾，
   * 与地图上的左右顺序对不上。
   */
  const insertAlongTrack = (created: any, x: number, parentPath: string): string | null => {
    if (!spec) return null
    const next = JSON.parse(JSON.stringify(spec))
    const parent = getNodeByPath(next, parentPath) || next.root
    parent.children = parent.children || []
    const sibs = parent.children
    let insertAt = sibs.length
    for (let i = 0; i < sibs.length; i++) {
      const sx = Number(sibs[i]?.properties?.x)
      if (Number.isFinite(sx) && sx > x) { insertAt = i; break }
    }
    sibs.splice(insertAt, 0, created)

    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(parentPath))
    // 新节点路径：父路径 + children + 下标
    const newPath = `${parentPath}${SEP}children${SEP}${insertAt}`
    setSelectedPath(newPath)
    setNodeSel(new Set([newPath]))
    return newPath
  }

  /**
   * 在地图上「轨道某处右键」时新增一个航点。
   *
   * `u` 是归一化位置，按**轨道总长（米）**反算出对应的沿轨弧长，
   * 再按 x 大小插到已有航点序列中的正确位置——这样树里的航点顺序
   * 与地图上的左右顺序始终一致，不会出现"新加的点跑到列表末尾"。
   *
   * 分组归属：如果所有航点都在同一个 GroupNode 下，就插进那个分组；
   * 否则插到根节点末尾（结构不一致时不做猜测）。
   */
  const addWaypointAt = (u: number) => {
    if (!spec?.root) return
    const x = xAtU(u)
    const props = defaultsFrom(nodeTypes.WaypointNode?.schema)
    props.x = x
    props.name = `航点 ${mapWaypoints.length + 1}`
    const created = { type: 'WaypointNode', properties: props }

    // 找到所有航点的共同父级，找不到就退回根
    const parents = new Set(
      mapWaypoints.map((w) => parentPathOf(w.path)),
    )
    const parentPath = parents.size === 1 ? [...parents][0] : 'root'
    if (insertAlongTrack(created, x, parentPath)) {
      Toast.success(`已在 ${x.toFixed(3)} m 处添加航点（保存后落盘）`)
    }
  }

  /**
   * 在地图上「轨道某处右键」时新增沿轨设施（充电桩 / RFID 卡）。
   *
   * 落位规则与航点完全一致（同一把尺子——轨道总长米数、同样按 x 排序插入），
   * 所以桩/卡在地图上就落在右键的那一点上，树里的顺序也对得上。
   * 归属优先级：同类型设施的**共同父级** > 航点的共同父级 > 根
   * ——结构不一致时不做猜测。
   */
  const addMarkerAt = (kind: MarkerKind, u: number) => {
    if (!spec?.root) return
    const typeName = MARKER_TYPE[kind]
    if (!nodeTypes[typeName]) {
      Toast.warning(`后端未提供节点类型 ${typeName}，请重启后端服务后重试`)
      return
    }
    const x = xAtU(u)
    const props = defaultsFrom(nodeTypes[typeName]?.schema)
    props.x = x
    const n = mapMarkers.filter((m) => m.kind === kind).length + 1
    props.name = `${kind === 'charging' ? '充电桩' : 'RFID 卡'} ${n}`
    const created = { type: typeName, properties: props }

    const sameKind = new Set(
      mapMarkers.filter((m) => m.kind === kind).map((m) => parentPathOf(m.path)),
    )
    const wpParents = new Set(mapWaypoints.map((w) => parentPathOf(w.path)))
    const parentPath = sameKind.size === 1 ? [...sameKind][0]
      : wpParents.size === 1 ? [...wpParents][0] : 'root'

    if (insertAlongTrack(created, x, parentPath)) {
      Toast.success(`已在 ${x.toFixed(3)} m 处添加${kind === 'charging' ? '充电桩' : 'RFID 卡'}（保存后落盘）`)
    }
  }

  /**
   * 在地图上「轨道某处右键」时新增**区段标记**。
   *
   * 落位规则与航点/设施完全一致（同一把尺子——轨道总长米数、按 x 排序插入），
   * 半径取 schema 默认值（1 m）——右键只能定中心，具体范围随后在检视器里改。
   * 归属优先级：已有区段的共同父级 > 航点的共同父级 > 根。
   */
  const addSectionAt = (u: number) => {
    if (!spec?.root) return
    if (!nodeTypes.SectionMarkNode) {
      Toast.warning('后端未提供 SectionMarkNode 节点类型，请重启后端服务后重试')
      return
    }
    const x = xAtU(u)
    const props = defaultsFrom(nodeTypes.SectionMarkNode?.schema)
    props.x = x
    props.name = `区段 ${mapSections.length + 1}`
    const created = { type: 'SectionMarkNode', properties: props }

    const own = new Set(mapSections.map((s) => parentPathOf(s.path)))
    const wpParents = new Set(mapWaypoints.map((w) => parentPathOf(w.path)))
    const parentPath = own.size === 1 ? [...own][0]
      : wpParents.size === 1 ? [...wpParents][0] : 'root'

    if (insertAlongTrack(created, x, parentPath)) {
      Toast.success(`已在 ${x.toFixed(3)} m 处添加区段标记（保存后落盘）`)
    }
  }

  /**
   * 在地图**任意位置**右键时新增**图标标记**。
   *
   * 与上面几个都不一样：不用弧长、不排序插入——图标标的是"地图上的这个点"，
   * 按 x 插进兄弟序列反而会把同级的航点顺序搅乱（那些是按弧长排的）。
   * 所以直接追加到父级末尾，坐标原样记下即可。
   * 归属优先级：已有图标的共同父级 > 根（**不**沿用航点的父级：图标常常
   * 是整张地图的注记，塞进航点分组里会让"航点组"里混进非航点节点）。
   */
  const addIconAt = (world: Pt) => {
    if (!spec?.root) return
    if (!nodeTypes.IconMarkNode) {
      Toast.warning('后端未提供 IconMarkNode 节点类型，请重启后端服务后重试')
      return
    }
    const props = defaultsFrom(nodeTypes.IconMarkNode?.schema)
    props.x = Number(world.x.toFixed(2))
    props.y = Number(world.y.toFixed(2))
    props.name = `图标 ${mapIcons.length + 1}`
    const created = { type: 'IconMarkNode', properties: props }

    const next = JSON.parse(JSON.stringify(spec))
    const own = new Set(mapIcons.map((i) => parentPathOf(i.path)))
    const parentPath = own.size === 1 ? [...own][0] : 'root'
    const parent = getNodeByPath(next, parentPath) || next.root
    parent.children = parent.children || []
    const at = parent.children.length
    parent.children.push(created)

    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(parentPath))
    const newPath = `${parentPath}${SEP}children${SEP}${at}`
    setSelectedPath(newPath)
    setNodeSel(new Set([newPath]))
    Toast.success('已在此处添加图标（保存后落盘；图标 / 颜色 / 大小可在检视器里改）')
  }

  /* ---- 轨道编辑：写入规则都在 utils/trackSpec.ts，这里只负责落到 spec ---- */

  /**
   * 起一次轨道写入：拿 spec 深拷贝并定位当前轨道节点。
   * 拿不到（没有 spec 或没有轨道）返回 null，调用方统一提示。
   */
  const beginTrackEdit = (): { next: any; track: any } | null => {
    if (!spec || !currentTrackPath) return null
    const next = JSON.parse(JSON.stringify(spec))
    const track = getNodeByPath(next, currentTrackPath)
    if (!track) return null
    track.children = track.children || []
    return { next, track }
  }

  /** 新增一条轨道（挂在根节点下），并立即选中它 */
  const onCreateTrack = () => {
    if (!spec) return
    const next = JSON.parse(JSON.stringify(spec))
    next.root.children = next.root.children || []
    const props = defaultsFrom(nodeTypes.TrackNode?.schema)
    props.name = `轨道 ${tracks.length + 1}`
    next.root.children.push({ type: 'TrackNode', properties: props })
    setSpec(next)
    const newPath = childPath('root', next.root.children.length - 1)
    setExpandedKeys((prev) => new Set(prev).add('root').add(newPath))
    setSelectedPath(newPath)
    setNodeSel(new Set([newPath]))
    Toast.success('已新增轨道 · 切到「绘制轨道」即可在地图上画端点')
  }

  const noTrackHint = () => Toast.info('请先点「新增轨道」创建一条轨道')

  /** 追加一个端点：与上一个端点之间是直线段 */
  const onAddEndpoint = (p: Pt) => {
    const e = beginTrackEdit()
    if (!e) { noTrackHint(); return }
    const r = appendEndpoint(
      e.track.children,
      currentTrackPath!,
      p,
      defaultsFrom(nodeTypes.TrackEndpointNode?.schema),
    )
    e.track.children = r.children
    setSpec(e.next)
    setExpandedKeys((prev) => new Set(prev).add(currentTrackPath!))
  }

  /** 追加"控制点 + 端点"（顺序语义见 `appendEndpointWithControl`） */
  const onAddEndpointWithControl = (control: Pt, endpoint: Pt) => {
    const e = beginTrackEdit()
    if (!e) { noTrackHint(); return }
    const r = appendEndpointWithControl(
      e.track.children,
      currentTrackPath!,
      control,
      endpoint,
      defaultsFrom(nodeTypes.TrackControlNode?.schema),
      defaultsFrom(nodeTypes.TrackEndpointNode?.schema),
    )
    e.track.children = r.children
    setSpec(e.next)
    setExpandedKeys((prev) => new Set(prev).add(currentTrackPath!))
  }

  /** 拖动已有的端点/控制点。地图只在松手时调一次，不会每帧写 spec */
  const onMovePoint = (path: string, p: Pt) => {
    if (!spec) return
    const next = JSON.parse(JSON.stringify(spec))
    const parent = getNodeByPath(next, parentPathOf(path))
    const idx = Number(path.split(SEP).pop())
    if (!parent?.children || !Number.isInteger(idx)) return
    parent.children = withMovedPoint(parent.children, idx, p)
    setSpec(next)
  }

  /** 清空当前轨道下的所有端点与控制点（轨道节点本身保留） */
  const onClearTrack = () => {
    if (!currentTrackPath) return
    Modal.confirm({
      title: '清空当前轨道',
      content: `将删除「${currentTrack?.properties?.name || '轨道'}」下的所有端点与控制点，确定？`,
      okType: 'danger',
      onOk: () => {
        const e = beginTrackEdit()
        if (!e) return
        e.track.children = []
        setSpec(e.next)
        setSelectedPath(currentTrackPath)
        setNodeSel(new Set([currentTrackPath]))
      },
    })
  }

  const doDelete = () => {    const targets = topLevelPaths([...nodeSel]).filter((p) => p !== 'root')
    if (!targets.length) { Toast.warning('根节点不可删除'); return }
    const next = JSON.parse(JSON.stringify(spec))
    const removed = removeManyByPaths(next.root, targets)
    setSpec(next)
    if (targets.includes(selectedPath)) setSelectedPath('root')
    setNodeSel(new Set())
    Toast.success(`已删除 ${removed} 个节点（保存后落盘）`)
  }

  const confirmDelete = () => {
    if (!nodeSel.size || [...nodeSel].includes('root')) { Toast.warning('根节点不可删除'); return }
    Modal.confirm({
      title: `删除 ${topLevelPaths([...nodeSel]).filter((p) => p !== 'root').length} 个节点`,
      content: '删除后点击「保存」才落盘生效，确定删除？',
      okType: 'danger',
      onOk: doDelete,
    })
  }

  const copyNodes = () => {
    if (!spec || !nodeSel.size) { Toast.warning('请先选中节点'); return }
    const tops = topLevelPaths([...nodeSel]).filter((p) => p !== 'root')
    const nodes = tops.map((p) => JSON.parse(JSON.stringify(getNodeByPath(spec, p)))).filter(Boolean)
    if (!nodes.length) { Toast.warning('根节点不可复制'); return }
    setClipboard({ mode: 'copy', nodes })
    Toast.success(`已复制 ${nodes.length} 个节点`)
  }

  const cutNodes = () => {
    if (!spec || !nodeSel.size) { Toast.warning('请先选中节点'); return }
    const tops = topLevelPaths([...nodeSel]).filter((p) => p !== 'root')
    if (!tops.length) { Toast.warning('根节点不可剪切'); return }
    const nodes = tops.map((p) => JSON.parse(JSON.stringify(getNodeByPath(spec, p)))).filter(Boolean)
    const next = JSON.parse(JSON.stringify(spec))
    removeManyByPaths(next.root, tops)
    setSpec(next)
    if (tops.includes(selectedPath)) setSelectedPath('root')
    setNodeSel(new Set())
    setClipboard({ mode: 'cut', nodes })
    Toast.success(`已剪切 ${nodes.length} 个节点，右键目标节点粘贴`)
  }

  /**
   * 粘贴。
   *
   * ⚠️ 粘贴出来的子树**必须换掉业务 id**（航点 / 动作 / 测点）：复制件若沿用
   * 原 id，下发巡检后两处指向同一个航点，机器人的 `current_waypoint_id`
   * 分不清走到了哪一份，断点续跑也会串。名称、坐标这些可以照抄，id 不行。
   */
  const pasteTo = (targetPath: string) => {
    if (!clipboard || !spec) return
    const next = JSON.parse(JSON.stringify(spec))
    const target = getNodeByPath(next, targetPath)
    if (!target) { Toast.error('目标节点不存在'); return }
    const clones = clipboard.nodes.map((n) => JSON.parse(JSON.stringify(n)))
    let fresh = 0
    for (const c of clones) fresh += regenerateIds(c)
    target.children = target.children || []
    target.children.push(...clones)
    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(targetPath))
    if (clipboard.mode === 'cut') setClipboard(null)
    Toast.success(
      fresh
        ? `已粘贴 ${clones.length} 个节点（重新生成 ${fresh} 个 id）`
        : `已粘贴 ${clones.length} 个节点`,
    )
  }

  /** 归入分组：在同父选中节点的父级下新建分组，并把它们移入 */
  const groupInto = () => {
    if (!spec) return
    const tops = topLevelPaths([...nodeSel]).filter((p) => p !== 'root')
    if (!tops.length) { Toast.warning('请先选中要归入分组的节点'); return }
    const parents = new Set(tops.map(parentPathOf))
    if (parents.size !== 1) { Toast.warning('批量归入分组要求选中节点在同一父级下'); return }
    const parentPath = [...parents][0]
    const next = JSON.parse(JSON.stringify(spec))
    const parent = getNodeByPath(next, parentPath)
    if (!parent?.children) return
    const picked = tops
      .map((p) => ({ p, idx: Number(p.split(SEP).pop()) }))
      .sort((a, b) => b.idx - a.idx)
      .map(({ p, idx }) => {
        const node = parent.children[idx]
        parent.children.splice(idx, 1)
        return node
      })
    const groupProps = defaultsFrom(nodeTypes.GroupNode?.schema)
    groupProps.name = '新分组'
    const group = { type: 'GroupNode', properties: groupProps, children: picked.reverse() }
    parent.children.push(group)
    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(parentPath))
    Toast.success('已归入新分组')
  }

  /* ------------------------------------------------------------ 展开/收起 */

  const expandSubtree = (path: string) => {
    if (!spec) return
    const node = getNodeByPath(spec, path)
    if (!node) return
    const keys = new Set(collectParentKeys(node, path))
    keys.add(path)
    setExpandedKeys((prev) => new Set([...prev, ...keys]))
  }
  const collapseSubtree = (path: string) => {
    if (!spec) return
    const node = getNodeByPath(spec, path)
    if (!node) return
    const keys = new Set([path, ...collectParentKeys(node, path)])
    setExpandedKeys((prev) => {
      const n = new Set(prev)
      keys.forEach((k) => n.delete(k))
      return n
    })
  }
  const expandAll = () => { if (spec?.root) setExpandedKeys(new Set(collectParentKeys(spec.root))) }
  const collapseAll = () => setExpandedKeys(new Set())

  /* ------------------------------------------------------------ 拖拽 */

  const onNodeDrop = (props: any) => {
    if (!spec) return
    setDragPaths(new Set())
    const dragPath: string = props.dragNode?.key || ''
    const targetPath: string = props.node?.key || ''
    if (!dragPath || !targetPath) return

    // dropPosition 是「相对方向 + 目标同级下标」的绝对下标，不能直接当方向用
    const kind: DropKind = resolveDropKind(props)
    const next = JSON.parse(JSON.stringify(spec))

    // 拖动的是多选集合 -> 整体移动并保持相对次序
    if (nodeSel.has(dragPath) && nodeSel.size > 1) {
      const res = batchMoveNodes(next.root, [...nodeSel], targetPath, kind)
      if (res.ok) {
        setSpec(next)
        Toast.success(`已移动 ${nodeSel.size} 个节点，保存后落盘`)
      } else {
        Toast.warning(res.reason || '无法移动到该位置')
      }
      return
    }

    const res = moveNodeInSpec(next.root, dragPath, targetPath, kind)
    if (res.ok) {
      setSpec(next)
      if (kind === 'on') setExpandedKeys((prev) => new Set(prev).add(targetPath))
      Toast.success('已移动节点，保存后落盘')
    } else {
      Toast.warning(res.reason || '无法移动到该位置')
    }
  }

  /** 多选拖动时，把所有被拖节点一起高亮，让用户知道"拖走的是一批" */
  const onNodeDragStart = ({ node }: any) => {
    const key: string = node?.key || ''
    if (!key) return
    if (nodeSel.has(key) && nodeSel.size > 1) setDragPaths(new Set(nodeSel))
    else setDragPaths(new Set([key]))
  }

  /* Delete 删除 */
  useEffect(() => {
    const onKey = (e: KeyboardEvent) => {
      if (e.key !== 'Delete') return
      const t = e.target as HTMLElement
      if (t && /INPUT|TEXTAREA|SELECT/.test(t.tagName)) return
      if (nodeSel.size) { e.preventDefault(); confirmDelete() }
    }
    window.addEventListener('keydown', onKey)
    return () => window.removeEventListener('keydown', onKey)
  })

  /* ------------------------------------------------------------ 工具栏动作 */

  const doSave = async () => {
    if (!spec || !currentRel) { Toast.warning('请先新建或选择一个航点树文件'); return }
    setSaving(true)
    try {
      await saveWaypointTree(currentRel, spec)
      Toast.success('已保存')
      await refreshFiles()
    } catch { /* 拦截器已提示 */ } finally { setSaving(false) }
  }

  const doCreateFile = async () => {
    let rel = newFileName.trim()
    if (!rel) { Toast.warning('文件名不能为空'); return }
    if (!rel.endsWith('.prefab.json')) rel = `${rel.replace(/\.prefab\.json$/i, '')}.prefab.json`
    try {
      await createWaypointFile(rel)
      Toast.success('已创建')
      setNewFileOpen(false); setNewFileName('')
      const list = await refreshFiles()
      if (list.find((t) => t.rel_path === rel)) await loadTree(rel)
    } catch { /* 拦截器已提示 */ }
  }

  /** 下发"走到弧长 x"——工具栏按钮与地图右键共用这一份提示 */
  const gotoAndToast = (x: number, what: string) => {
    gotoX(x)
      .then(() => Toast.success(`${what}：已下发移动到 ${x.toFixed(3)} m`))
      .catch(() => { /* 拦截器已提示 */ })
  }

  const moveToSelectedWaypoint = () => {
    if (!spec) return
    const candidates = nodeSel.size ? [...nodeSel] : [selectedPath]
    const wp = candidates
      .map((p) => getNodeByPath(spec, p))
      .find((n) => n?.type === 'WaypointNode')
    if (!wp) { Toast.warning('请先选中一个航点节点'); return }
    const x = Number(wp.properties?.x)
    if (!Number.isFinite(x)) { Toast.warning('该航点缺少有效的 x 坐标'); return }
    gotoAndToast(x, wp.properties?.name || '选中航点')
  }

  /** 地图轨道上右键「移动机器人到此位置」：u -> 弧长，与新增航点同源 */
  const moveRobotToU = (u: number) => {
    const x = xAtU(u)
    gotoAndToast(x, '轨道右键')
  }

  /**
   * 调云台抓图接口 -> 存到**当前 prefab 文件所在目录**的 images/ -> 返回相对路径。
   *
   * 检视器的「重新拍照」与航点右键的「创建云台拍照动作点」共用这一份：
   * 两处都是"拍一张、存下来、拿到相对路径"，分开写迟早会有一边忘了 revoke
   * 或者用了不同的文件名规则。
   *
   * 失败/取消返回 null，调用方据此**保持原值**——把用户已经拍好的图清掉
   * 比"这次没拍上"糟得多。
   */
  const captureImage = useCallback(async (): Promise<string | null> => {
    if (!currentRel) {
      Toast.warning('请先选择（或新建）一个航点树文件，抓拍图要存在它旁边')
      return null
    }
    try {
      const blob = await ptzSnapshotBlob()
      // 后端按扩展名落盘，object URL 那套在这里用不上（转不回二进制）
      const ext = blob.type === 'image/png' ? 'png' : 'jpg'
      const file = new File([blob], `capture.${ext}`, { type: blob.type || 'image/jpeg' })
      const { data } = await uploadWaypointCapture(file, currentRel)
      if (!data?.ok || !data?.rel) {
        Toast.error('抓拍图保存失败：后端未返回图片路径')
        return null
      }
      return data.rel
    } catch (err: any) {
      Toast.error(`云台抓图失败：${err?.response?.data?.detail || err?.message || err}`)
      return null
    }
  }, [currentRel])

  /**
   * 航点右键「创建云台拍照动作点」：先抓图存盘，再在该航点下建一个
   * ActionPointNode（动作类型=1 可见光拍照）把相对路径记进 `imageUrl`。
   *
   * **先存图再建节点**：顺序反了会出现"节点建好了、图没存上"，
   * 于是树里躺着一个 imageUrl 为空的动作点，比什么都没建更让人困惑。
   */
  const addCaptureActionPoint = async (wpPath: string) => {
    if (!spec) return
    const wp = getNodeByPath(spec, wpPath)
    if (!wp || wp.type !== 'WaypointNode') {
      Toast.warning('「创建云台拍照动作点」要在航点上使用')
      return
    }
    if (!nodeTypes.ActionPointNode) {
      Toast.warning('后端未提供 ActionPointNode 节点类型，请重启后端服务后重试')
      return
    }
    const rel = await captureImage()
    if (!rel) return

    const next = JSON.parse(JSON.stringify(spec))
    const parent = getNodeByPath(next, wpPath)
    if (!parent) return
    parent.children = parent.children || []
    const props = defaultsFrom(nodeTypes.ActionPointNode?.schema)
    props.name = `拍照动作 ${countOfType(parent.children, 'ActionPointNode') + 1}`
    props.action_type = 1
    // 沿用它所属航点的名字：下发任务时 steer_point_name 就是这么用的
    props.steer_point_name = String(wp.properties?.name || '')
    props.imageUrl = rel
    parent.children.push({ type: 'ActionPointNode', properties: props })
    setSpec(next)
    setExpandedKeys((prev) => new Set(prev).add(wpPath))
    const newPath = childPath(wpPath, parent.children.length - 1)
    setSelectedPath(newPath)
    setNodeSel(new Set([newPath]))
    Toast.success(`已创建拍照动作点（图片 ${rel}），点击「保存」落盘`)
  }

  const onPickInspectionFile = () => fileInputRef.current?.click()
  const onInspectionFileChosen = async (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0]
    e.target.value = ''
    if (!file) return
    let payload: any
    try {
      payload = JSON.parse(await file.text())
    } catch {
      Toast.error('文件不是合法 JSON'); return
    }
    try {
      const { data } = await importInspectionToWaypoint(payload)
      applySpec(data.spec)
      let rel = currentRel
      if (!rel) {
        rel = `${sanitizeFileName(data.spec.name)}.prefab.json`
        if (trees.some((t) => t.rel_path === rel)) {
          rel = `${sanitizeFileName(data.spec.name)}-${Date.now()}.prefab.json`
        }
        await createWaypointFile(rel)
        await refreshFiles()
      }
      setCurrentRel(rel)
      const c = data.counts
      Toast.success(`已导入：${c.GroupNode || 0} 分组 / ${c.WaypointNode || 0} 航点 / ${c.ActionPointNode || 0} 动作点 / ${c.MeasurePointNode || 0} 测点，点击保存落盘`)
    } catch { /* 拦截器已提示 */ }
  }

  /* ------------------------------------------------------------ 右键菜单 */

  /**
   * 用选中的航点组装巡检任务并下发。
   *
   * 走的是与「测试巡检」同一个后端接口（POST /api/rail/robot/inspection），
   * 只是 body 由树现场组装：按**树中顺序**取航点，楼层从祖先分组名
   * `楼层N` 回解（导入时就是这么写的），任务 id 随机。
   *
   * 下发会让机器人真的开始走，所以**必须确认**：弹窗里把航点数/动作数/
   * 楼层摆出来，让用户确认没选错。
   */
  const dispatchInspectionFromTree = () => {
    if (!spec) { Toast.warning('请先加载航点树文件'); return }
    /* 右键目标没被多选覆盖时，就用它自己（及其子树）——
       否则右键一个分组会"什么都没选中"，看着像点了没反应。 */
    const paths = nodeSel.size ? [...nodeSel] : [ctxMenu?.target || 'root']
    const built = buildInspection(spec, paths, {
      name: `${currentRel ? currentRel.replace(/\.prefab\.json$/i, '') : '航点树'} 下发任务`,
    })
    if (!built.waypointCount) {
      Toast.warning('选中的节点里没有航点（请选中航点或其所在的分组）')
      return
    }
    const floorsDesc = built.floors.join(' / ')
    Modal.confirm({
      title: '下发巡检任务',
      content: (
        <div>
          <div>将用 <b>{built.waypointCount}</b> 个航点、<b>{built.actionCount}</b> 个动作
            下发一次巡检任务（楼层 {floorsDesc}）。</div>
          <div style={{ marginTop: 8 }}>任务 id：<code>{built.inspectionId}</code></div>
          <div style={{ marginTop: 8, opacity: 0.75 }}>
            下发后机器人会立即开始走行；若已有未完成的巡检，后端会拒绝（409）。
          </div>
        </div>
      ),
      okText: '下发',
      cancelText: '取消',
      onOk: async () => {
        try {
          const res = await dispatchInspection(built.payload)
          Toast.success(
            `已下发：${res.waypoint_count ?? built.waypointCount} 航点 / `
            + `${res.action_count ?? built.actionCount} 动作（id ${res.inspection_id || built.inspectionId}）`,
          )
        } catch { /* 拦截器已提示（含 409 忙时拒绝） */ }
      },
    })
  }

  const openAddDialog = (targetPath: string, position?: 'before' | 'after') => {
    // 前 / 后插入默认选**与目标同类型**——在航点前插一个，多半就是想再插个航点
    const sameType = position && targetPath !== 'root'
      ? getNodeByPath(spec, targetPath)?.type
      : undefined
    setAddType(sameType); setAddKeyword('')
    setAddDialog({ targetPath, position })
  }

  const menuItems = (() => {
    if (!ctxMenu) return [] as any[]
    const p = ctxMenu.target || 'root'
    /**
     * 「在前 / 后添加子节点」：除了 root（没有"前后"可言）之外都给。
     *
     * 别按节点类型卡——这棵树上常见的是航点而不是端点，卡死类型的话用户
     * 右键航点永远看不到这两项（实测第一个反馈就是"没效果"）。
     */
    const canInsertBeside = p !== 'root'
    /** 拍照动作点必须挂在航点下：右键别处时置灰，而不是点下去才报错 */
    const targetIsWaypoint = getNodeByPath(spec, p)?.type === 'WaypointNode'
    const items: any[] = [
      { label: '展开子树', onClick: () => expandSubtree(p) },
      { label: '收起子树', onClick: () => collapseSubtree(p) },
      { divider: true },
      { label: '添加子节点', onClick: () => openAddDialog(p) },
      ...(canInsertBeside
        ? [
          { label: '在前添加子节点', onClick: () => openAddDialog(p, 'before') },
          { label: '在后添加子节点', onClick: () => openAddDialog(p, 'after') },
        ]
        : []),
      { divider: true },
      { label: '复制节点', onClick: copyNodes },
      { label: '剪切节点', onClick: cutNodes },
      { label: '粘贴', disabled: !clipboard, onClick: () => pasteTo(p) },
      { label: '归入分组', onClick: groupInto },
      { divider: true },
      {
        label: '创建云台拍照动作点',
        disabled: !targetIsWaypoint,
        onClick: () => addCaptureActionPoint(p),
      },
      { label: '移动机器人到选中航点', onClick: moveToSelectedWaypoint },
      { label: '用选中航点下发巡检任务', onClick: dispatchInspectionFromTree },
    ]
    if (p !== 'root') items.push({ divider: true }, { label: '删除节点', danger: true, onClick: confirmDelete })
    items.push({ divider: true }, { label: '查看 JSON 数据', onClick: () => setJsonTarget(p) })
    return items
  })()

  const jsonNode = jsonTarget && spec ? getNodeByPath(spec, jsonTarget) : null
  // 拖拽态下节点 label 自带上下边框做出落点指示，选中底色交由 CSS 承担
  const selStyle: React.CSSProperties = { display: 'block', padding: '2px 4px', borderRadius: 4 }

  if (loading) {
    return <div style={{ display: 'flex', justifyContent: 'center', padding: 80 }}><Spin size="large" /></div>
  }

  return (
    <div className="page-container">
      <div className="mb-12" style={{ display: 'flex', alignItems: 'center', gap: 12, flexWrap: 'wrap' }}>
        <h2 style={{ margin: 0 }}>航点树编排</h2>
        <Select
          value={currentRel || undefined}
          placeholder="选择航点树文件"
          style={{ width: 280 }}
          onChange={(v) => loadTree(v as string)}
          optionList={trees.map((t) => ({ label: t.rel_path, value: t.rel_path }))}
        />
        <Space wrap>
          <Button icon={<IconPlus />} onClick={() => { setNewFileName(''); setNewFileOpen(true) }}>新建文件</Button>
          <Button icon={<IconChevronDown />} onClick={expandAll}>展开全部</Button>
          <Button icon={<IconChevronUp />} onClick={collapseAll}>收起全部</Button>
          <Button icon={<IconMapPin />} onClick={moveToSelectedWaypoint}>移动到选中航点</Button>
          <Button icon={<IconUpload />} onClick={onPickInspectionFile}>从 inspection.json 导入</Button>
          <Button theme="solid" type="primary" icon={<IconSave />} loading={saving} onClick={doSave}>保存</Button>
        </Space>
        <input ref={fileInputRef} type="file" accept=".json,application/json" style={{ display: 'none' }}
          onChange={onInspectionFileChosen} />
      </div>

      <div className="wp3-wrap">
        {/* 左：航点树（宽度可拖拽，默认 300） */}
        <div className="wp3-tree" style={{ width: treeWidth }}
          onContextMenu={(e) => {
            e.preventDefault()
            setCtxMenu({ x: e.clientX, y: e.clientY, target: 'root' })
          }}>
          <Card className="card-shadow" bordered={false}
            header={<span style={{ fontWeight: 600 }}>航点树{currentRel ? ` · ${currentRel}` : '（未选择文件）'}</span>}
            style={{ height: '100%' }}>
            {!spec || treeData.length === 0 ? (
              <Empty title="空树" description="新建文件或从 inspection.json 导入；在树中可拖拽移动节点" />
            ) : (
              <div onMouseDown={(e) => { mods.current.shift = e.shiftKey; mods.current.ctrl = e.ctrlKey || e.metaKey }}>
                <Tree
                  treeData={treeData}
                  draggable
                  autoExpandWhenDragEnter
                  expandedKeys={[...expandedKeys]}
                  onExpand={(keys: string[]) => setExpandedKeys(new Set(keys))}
                  onSelect={(_k: string, _s: boolean, node: any) => onNodeSelect(node.key || node.value)}
                  onContextMenu={onNodeCtx}
                  onDragStart={onNodeDragStart}
                  onDragEnd={() => setDragPaths(new Set())}
                  onDrop={onNodeDrop}
                  renderLabel={(label: React.ReactNode, node: any) => {
                    const k = node.key as string
                    const isSel = nodeSel.has(k)
                    const isDragging = dragPaths.has(k)
                    return (
                      <span style={{
                        ...selStyle,
                        opacity: isDragging ? 0.45 : 1,
                        outline: isDragging ? '1px dashed var(--semi-color-primary)' : undefined,
                      }} className={isSel ? 'wp-prefab-node-sel' : undefined}>{label}</span>
                    )
                  }}
                />
              </div>
            )}
            <div style={{ marginTop: 8, color: 'var(--semi-color-text-2)', fontSize: 12 }}>
              Ctrl 点选 / Shift 区间多选；Delete 删除选中；拖拽移动（拖到节点上下边缘=插到前后，拖到节点中间=归入其子级）；右键更多操作。
            </div>
          </Card>
        </div>

        {/* 分隔条：树 | 检视器 */}
        <div className="wp3-handle" title="拖拽调整树视图宽度"
          onMouseDown={(e) => startDrag(e, treeWidth, setTreeWidth, 200, 720, 1)} />

        {/* 中：地图（轨道可视化）+ 检视器 */}
        <div className="wp3-inspector">
          <Card className="card-shadow" bordered={false}
            header={
              <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', width: '100%' }}>
                <span style={{ fontWeight: 600 }}>轨道地图</span>
                <span style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>
                  轨道由树中的「轨道」节点定义；航点按沿轨弧长吸附显示
                </span>
              </div>
            }>
            {/* 只要 spec 存在就渲染地图：轨道是「从零画出来的」，
                若因为"暂无航点"把地图藏起来，用户就连「新增轨道」按钮也够不着了。 */}
            {!spec ? (
              <Empty
                title="未选择航点树"
                description="新建文件或从 inspection.json 导入后，即可在此绘制轨道"
                style={{ padding: '24px 0' }}
              />
            ) : (
              <TrackMap
                waypoints={mapWaypoints}
                selectedPaths={nodeSel}
                onSelectionChange={(paths) => {
                  setNodeSel(paths)
                  // 地图选中同步到检视器；多选时不动，避免检视器来回跳
                  if (paths.size === 1) setSelectedPath([...paths][0])
                }}
                trackNodes={trackNodes}
                trackName={currentTrack?.properties?.name}
                trackCount={tracks.length}
                onCreateTrack={onCreateTrack}
                onAddEndpoint={onAddEndpoint}
                onAddEndpointWithControl={onAddEndpointWithControl}
                onMovePoint={onMovePoint}
                onClearTrack={onClearTrack}
                onAddWaypoint={addWaypointAt}
                onMoveWaypoint={moveAlongX}
                markers={mapMarkers}
                onAddMarker={addMarkerAt}
                onMoveMarker={moveAlongX}
                sections={mapSections}
                onAddSection={addSectionAt}
                onMoveSection={moveAlongX}
                onMoveRobot={moveRobotToU}
                icons={mapIcons}
                onAddIcon={addIconAt}
                onMoveIcon={moveIconXY}
                background={mapBackground}
                onBackgroundChange={applyBackground}
                onPickBackground={() => bgFileRef.current?.click()}
                onLocate={(path) => { setSelectedPath(path); expandSubtree(parentPathOf(path)) }}
                height={440}
              />
            )}
            {/* 背景图上传：隐藏的 file input，由地图工具栏的按钮触发 */}
            <input
              ref={bgFileRef}
              type="file"
              accept="image/*"
              style={{ display: 'none' }}
              onChange={onBackgroundFile}
            />
          </Card>

          <Card className="card-shadow" bordered={false}
            header={
              <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', width: '100%' }}>
              <span style={{ fontWeight: 600 }}>检视器</span>
              {selectedNode && <Tag size="small" color={TYPE_COLOR[selectedNode.type] || 'blue'}>{TYPE_LABEL[selectedNode.type] || selectedNode.type}</Tag>}
            </div>
          }>
          {nodeSel.size > 1 ? (
            <Empty title={`已选中 ${nodeSel.size} 个节点`} description="多选状态下不可批量编辑，请选择单个节点查看属性" />
          ) : !selectedNode ? (
            <Empty title="请选择节点" />
          ) : selectedSchema ? (
            <InspectorForm
              schema={selectedSchema}
              value={{ ...(selectedNode.properties || {}), children: selectedNode.children || [] }}
              onChange={(patch) => {
                const { children: _c, ...rest } = patch
                updateProps(rest)
              }}
              onCaptureImage={captureImage}
              resolveImageSrc={(v) => resolveImageUrl(v, currentRel)}
              optionSources={optionSources}
              top={isPhotoAction ? (
                // 换节点就整个重挂（key）：它内部"选中哪个框"是按**路径**记的，
                // 而路径在不同节点下是同一套（`root/children/0/...`）。
                // 不重挂的话，在 A 节点选中框 #2 后切到 B 节点，同一个路径会解析到
                // B 的另一个框上——绑定测点写进去就绑错了（绑定窗口是非模态的，
                // 开着的时候照样能去点树）。
                <DetectBoxTool
                  key={selectedPath || 'none'}
                  imageSrc={detectImageSrc}
                  boxes={detectBoxes}
                  onAdd={addDetectBox}
                  onUpdatePoints={setBoxPoints}
                  onBindPoint={bindBoxPoint}
                  onUnbindPoint={unbindBoxPoint}
                  detectFlows={detectFlowChoices}
                  onSetDetectFlow={setBoxDetectFlow}
                  pointUsage={pointUsage}
                  onRemove={removeDetectBox}
                />
              ) : null}
              groupExtra={isActionPoint ? {
                云台: (
                  <div className="wp-ptz-pose-tool">
                    <Button size="small" loading={ptzPoseLoading} onClick={useCurrentPtzPose} block>
                      使用当前云台位姿
                    </Button>
                  </div>
                ),
              } : isWaypoint ? {
                位姿: (
                  <div className="wp-ptz-pose-tool">
                    <Button size="small" loading={poseLoading} onClick={useCurrentPose} block>
                      使用当前位姿
                    </Button>
                  </div>
                ),
              } : undefined}
            />
          ) : (
            <Empty title="未知节点类型" description={`schema 未找到: ${selectedNode.type}`} />
          )}
          </Card>
        </div>

        {/* 分隔条：检视器 | 视频+控制 */}
        <div className="wp3-handle" title="拖拽调整右侧面板宽度"
          onMouseDown={(e) => startDrag(e, rightWidth, setRightWidth, 260, 560, -1)} />

        {/* 右：实时视频 + 机器人控制 */}
        <div className="wp3-right" style={{ width: rightWidth }}>
          <Card className="card-shadow" bordered={false}
            header={
              <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', width: '100%' }}>
                <span style={{ fontWeight: 600 }}>实时视频</span>
                {selectedRid
                  ? <Tag size="small" color="blue">机器人 #{selectedRid}</Tag>
                  : <Tag size="small" color="grey">未选择</Tag>}
              </div>
            }>
            {selectedRid ? (
              <WebRTCPlayer rid={selectedRid} autoplay={false} />
            ) : (
              <Empty
                title="未选择机器人"
                description="请在顶部工具栏选择一台机器人，用于查看实时视频与下发控制指令"
                style={{ padding: '32px 0' }}
              />
            )}
          </Card>

          {/* 垂直分隔条：视频 | 控制 */}
          <div className="wp3-handle-v" title="拖拽调整视频区高度"
            onMouseDown={(e) => startDrag(e, videoHeight, setVideoHeight, 160, 620, 0, true)} />

          <Card className="card-shadow" bordered={false}
            header={<span style={{ fontWeight: 600 }}>机器人控制</span>}>
            {selectedRid ? (
              <RobotControlInline rid={selectedRid} />
            ) : (
              <Empty title="未选择机器人" description="选择机器人后可在此控制运动 / 云台 / 升降 / 位姿" style={{ padding: '24px 0' }} />
            )}
          </Card>
        </div>
      </div>

      {/* 右键菜单 */}
      {ctxMenu && (
        <div style={{ position: 'fixed', inset: 0, zIndex: 1000 }}
          onMouseDown={() => setCtxMenu(null)}
          onContextMenu={(e) => { e.preventDefault(); setCtxMenu(null) }}>
          {/*
            菜单项有多有少（端点会多出"在前/后添加子节点"两项），高度不能写死：
            顶部钳一下保证上方至少留得下菜单，再按剩余空间限高 + 滚动，
            避免在屏幕底部右键时末尾几项被挤出视口、点不到。
          */}
          <div style={{
            left: Math.min(ctxMenu.x, window.innerWidth - 190),
            top: Math.min(ctxMenu.y, Math.max(8, window.innerHeight - 340)),
            maxHeight: window.innerHeight - Math.min(ctxMenu.y, Math.max(8, window.innerHeight - 340)) - 8,
            overflowY: 'auto',
            ...MENU_STYLE,
          }}
            onMouseDown={(e) => e.stopPropagation()}>
            {menuItems.map((it, i) => it.divider ? (
              <div key={i} style={{ borderTop: '1px solid var(--semi-color-border)', margin: '4px 6px' }} />
            ) : (
              <div key={i} onClick={() => { if (!it.disabled) { setCtxMenu(null); it.onClick?.() } }}
                style={{
                  padding: '6px 12px', borderRadius: 4,
                  cursor: it.disabled ? 'not-allowed' : 'pointer',
                  color: it.danger ? 'var(--semi-color-danger)' : 'var(--semi-color-text-0)',
                  opacity: it.disabled ? 0.45 : 1,
                }}>
                {it.label}
              </div>
            ))}
          </div>
        </div>
      )}

      {/* 添加子节点：筛选 + 类型树 */}
      <Modal
        title={addDialog?.position === 'before' ? '在前添加子节点'
          : addDialog?.position === 'after' ? '在后添加子节点' : '添加子节点'}
        visible={!!addDialog}
        onOk={() => {
          if (addDialog && addType) {
            addChild(addDialog.targetPath, addType, addDialog.position)
            setAddDialog(null); setAddType(undefined); setAddKeyword('')
          } else Toast.warning('请先选择节点类型')
        }}
        onCancel={() => { setAddDialog(null); setAddType(undefined); setAddKeyword('') }}
        okText="添加" cancelText="取消" style={{ width: 560 }}>
        {addDialog && (
          <div>
            {addDialog.position && (
              <div style={{ marginBottom: 8, fontSize: 12, color: 'var(--semi-color-text-2)' }}>
                新节点将插到「{getNodeByPath(spec, addDialog.targetPath)?.properties?.name || '该端点'}」
                {addDialog.position === 'before' ? '之前' : '之后'}，坐标取相邻端点的中点。
              </div>
            )}
            <Input autoFocus placeholder="筛选节点类型（名称，如 轨道/端点/控制点/航点/动作点/测点）…"
              value={addKeyword} onChange={(v) => setAddKeyword(v as string)}
              style={{ marginBottom: 8 }} />
            <div style={{ maxHeight: 320, overflow: 'auto', border: '1px solid var(--semi-color-border)', borderRadius: 6, padding: 4 }}>
              {typeTreeFiltered.length === 0 ? <Empty title="无匹配类型" style={{ padding: '24px 0' }} /> : (
                <Tree treeData={typeTreeFiltered} expandAll defaultExpandAll
                  onSelect={(_k: string, _s: boolean, node: any) => {
                    if (node?.key?.toString().startsWith('type/')) setAddType(node.typeName as string)
                  }}
                  renderLabel={(label: React.ReactNode, node: any) => {
                    const isLeaf = node?.key?.toString().startsWith('type/')
                    const sel = addType === node?.typeName
                    return (
                      <span style={{
                        display: 'block', padding: '2px 4px', borderRadius: 4,
                        cursor: isLeaf ? 'pointer' : 'default',
                        background: sel ? 'var(--semi-color-primary-light-default)' : undefined,
                      }}>{label}</span>
                    )
                  }}
                />
              )}
            </div>
          </div>
        )}
      </Modal>

      {/* 查看 JSON */}
      <Modal title="节点 JSON 数据" visible={jsonTarget !== null}
        onCancel={() => setJsonTarget(null)} footer={null} style={{ width: 620 }}>
        <pre style={{ maxHeight: '60vh', overflow: 'auto', background: 'var(--semi-color-fill-0)', padding: 12, borderRadius: 6, fontSize: 12 }}>
          {jsonNode ? JSON.stringify(jsonNode, null, 2) : ''}
        </pre>
      </Modal>

      {/* 新建文件 */}
      <Modal title="新建航点树文件" visible={newFileOpen}
        onOk={doCreateFile} onCancel={() => setNewFileOpen(false)}
        okText="创建" cancelText="取消" style={{ width: 460 }}>
        <Input autoFocus value={newFileName} onChange={(v) => setNewFileName(v as string)}
          placeholder="文件名，可含子目录，如 floor1/航线A（自动补 .prefab.json）"
          onEnterPress={doCreateFile} />
      </Modal>
    </div>
  )
}
