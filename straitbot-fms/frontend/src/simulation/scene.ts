import * as THREE from 'three'
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js'
import { Track, type TrackConfig, type TrackPoint } from './track'

/** 机器人 3D 位姿输入(米/弧度) */
export interface RobotPose {
  s: number // 弧长 m
  extH: number // 伸缩杆高度 m(0 = 完全收回)
  moving: boolean
  wheelSpeed: number // 轮子角速度 rad/s(动画)
}

/** 可点选对象类型 */
export type PickType = 'robot' | 'obstacle' | 'rfid'

/** 障碍物/卡片视觉数据 */
export interface ObstacleVisual {
  id: number
  s: number // 弧长 mm
  width: number // 沿轨宽度 mm
  enabled: boolean
}
export interface RfidVisual {
  id: number
  s: number // 弧长 mm
}

const WHEEL_R = 0.09
const TRACK_GAP = 0.0 // 轮顶到轨道下沿贴合间隙(视觉微调)

export class SimScene {
  track: Track
  readonly scene = new THREE.Scene()
  readonly camera: THREE.PerspectiveCamera
  readonly renderer: THREE.WebGLRenderer
  readonly controls: OrbitControls
  private container: HTMLElement
  private robot!: THREE.Group
  private wheels: THREE.Mesh[] = []
  private extRod!: THREE.Mesh
  private extBase!: THREE.Mesh
  private robotCenterY = 0 // 车体中心距轨道中心线距离(m, 下为正)
  private timer = 0
  private clock = new THREE.Clock()
  private disposed = false
  private pickTargets: THREE.Object3D[] = []
  private pickHandler?: (info: { type: PickType; id: number; name: string; pos: THREE.Vector3 }) => void
  private selectedKey: string | null = null
  private _lastS = 0
  private _frameCb: ((dt: number) => void) | null = null
  private obstacleGroup = new THREE.Group()
  private rfidGroup = new THREE.Group()
  private obstacleMeshes = new Map<number, THREE.Mesh>()
  private rfidMeshes = new Map<number, THREE.Mesh>()
  private lastObstacles: ObstacleVisual[] = []
  private lastRfids: RfidVisual[] = []
  private trackGroup = new THREE.Group()
  // 绘制轨道模式
  private drawMode = false
  private drawGroup = new THREE.Group()
  private drawPlaneY = 2.5
  private drawPts: THREE.Vector3[] = []
  private drawLine: THREE.Line | null = null
  private drawHandler?: (pts: TrackPoint[]) => void
  // 3D 拖拽移动障碍物/RFID
  private dragging: { type: 'obstacle' | 'rfid'; id: number; mesh: THREE.Mesh; hang: boolean; lastS: number; lastT: number } | null = null
  private dragHandler?: (info: { type: 'obstacle' | 'rfid'; id: number; sMm: number }) => void

  constructor(container: HTMLElement, trackCfg?: Partial<ConstructorParameters<typeof Track>[0]>) {
    this.container = container
    this.track = new Track(trackCfg)
    const w = container.clientWidth || 900
    const h = container.clientHeight || 600

    this.renderer = new THREE.WebGLRenderer({ antialias: true })
    this.renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2))
    this.renderer.setSize(w, h)
    this.renderer.shadowMap.enabled = true
    container.appendChild(this.renderer.domElement)

    this.camera = new THREE.PerspectiveCamera(55, w / h, 0.1, 200)
    this.scene.background = new THREE.Color(0x1c2430)

    this.controls = new OrbitControls(this.camera, this.renderer.domElement)
    this.controls.enableDamping = true
    this.controls.dampingFactor = 0.08
    this.controls.target.set(0, 1.5, 0)

    this.buildEnvironment()
    this.buildTrackMesh()
    this.buildRobot()
    this.setDefaultCamera()
    this.scene.add(this.obstacleGroup)
    this.scene.add(this.rfidGroup)
    this.scene.add(this.trackGroup)
    this.scene.add(this.drawGroup)

    this.renderer.domElement.addEventListener('click', this.handleClick)
    this.renderer.domElement.addEventListener('mousedown', this.handlePointerDown)
    window.addEventListener('mousemove', this.handlePointerMove)
    window.addEventListener('mouseup', this.handlePointerUp)
    window.addEventListener('resize', this.handleResize)
    this.startLoop()
  }

  // ---------- 环境 ----------
  private buildEnvironment() {
    // 地板
    const floor = new THREE.Mesh(
      new THREE.PlaneGeometry(30, 30),
      new THREE.MeshStandardMaterial({ color: 0x2b3340, roughness: 0.9 })
    )
    floor.rotation.x = -Math.PI / 2
    floor.position.y = -0.01
    floor.receiveShadow = true
    this.scene.add(floor)

    const grid = new THREE.GridHelper(30, 30, 0x4a5568, 0x3a4554)
    grid.position.y = 0.001
    this.scene.add(grid)

    // 厂房立柱(程序化)
    const pillarMat = new THREE.MeshStandardMaterial({ color: 0x556070, roughness: 0.7 })
    const pillarGeo = new THREE.BoxGeometry(0.25, 4.2, 0.25)
    for (const [x, z] of [
      [-4.5, -2.4], [4.5, -2.4], [-4.5, 2.4], [4.5, 2.4],
      [-4.5, 0], [4.5, 0],
    ]) {
      const p = new THREE.Mesh(pillarGeo, pillarMat)
      p.position.set(x, 2.1, z)
      p.castShadow = true
      this.scene.add(p)
    }
    // 顶部横梁(悬挂轨道支点)
    const beamMat = new THREE.MeshStandardMaterial({ color: 0x6b7688, roughness: 0.6, metalness: 0.2 })
    for (const z of [-this.track.R, 0, this.track.R]) {
      const beam = new THREE.Mesh(new THREE.BoxGeometry(10.5, 0.18, 0.18), beamMat)
      beam.position.set(0, this.track.H + 0.5, z)
      beam.castShadow = true
      this.scene.add(beam)
    }
    // 吊杆: 横梁 → 轨道
    const hangerMat = new THREE.MeshStandardMaterial({ color: 0x7a8494, roughness: 0.5 })
    for (const x of [-3.2, -1.6, 0, 1.6, 3.2]) {
      for (const z of [-this.track.R, 0, this.track.R]) {
        const rod = new THREE.Mesh(new THREE.CylinderGeometry(0.03, 0.03, 0.5), hangerMat)
        rod.position.set(x, this.track.H + 0.25, z)
        this.scene.add(rod)
      }
    }
    // 灯光
    const hemi = new THREE.HemisphereLight(0x9fb6d4, 0x232a33, 0.9)
    this.scene.add(hemi)
    const dir = new THREE.DirectionalLight(0xffffff, 1.6)
    dir.position.set(6, 8, 5)
    dir.castShadow = true
    dir.shadow.mapSize.set(1024, 1024)
    this.scene.add(dir)
    const amb = new THREE.AmbientLight(0xffffff, 0.35)
    this.scene.add(amb)
  }

  // ---------- 轨道 ----------
  private buildTrackMesh() {
    const tubeR = this.track.cfg.tubeRadius ?? 0.06
    // poly: 直接复用定位曲线(装饰物与管道完全贴合); rect: 采样点平滑成管
    const curve = this.track.getCurve() ?? (() => {
      const pts = this.track.sample(240)
      return new THREE.CatmullRomCurve3(pts, true, 'catmullrom', 0.5)
    })()
    const tube = new THREE.Mesh(
      new THREE.TubeGeometry(curve, 320, tubeR, 12, true),
      new THREE.MeshStandardMaterial({ color: 0xd8a13a, roughness: 0.45, metalness: 0.35 })
    )
    tube.castShadow = true
    this.trackGroup.add(tube)

    // 轨道走行面下沿提示线(视觉参考)
    const linePts = this.track.sample(240).map((p) => p.clone().add(new THREE.Vector3(0, -tubeR, 0)))
    const lineGeo = new THREE.BufferGeometry().setFromPoints(linePts)
    const line = new THREE.Line(lineGeo, new THREE.LineBasicMaterial({ color: 0xffe08a, transparent: true, opacity: 0.35 }))
    this.trackGroup.add(line)
  }

  /** 更换轨道(加载配置/绘制完成): 重建轨道几何并重放障碍物与 RFID */
  setTrack(cfg: Partial<TrackConfig>) {
    // 释放旧轨道几何
    for (const c of [...this.trackGroup.children]) {
      const mesh = c as THREE.Mesh
      mesh.geometry?.dispose()
      ;(mesh.material as THREE.Material)?.dispose?.()
      this.trackGroup.remove(c)
    }
    this.track = new Track(cfg)
    this.buildTrackMesh()
    this.drawPlaneY = this.track.H
    // 重放装饰物(新轨道弧长映射)
    this.setObstacles(this.lastObstacles)
    this.setRfids(this.lastRfids)
    // 机器人回到起点
    this._lastS = 0
    this.setRobot(0, 0, 0, false)
  }

  // ---------- 绘制轨道模式 ----------
  enterDrawMode() {
    this.drawMode = true
    this.drawPts = []
    this.drawPlaneY = this.track.H
    this.controls.enabled = false
    this.renderer.domElement.style.cursor = 'crosshair'
    this.clearDrawGroup()
  }

  /** 绘制模式下点击画布 → 添加航点(射线与 y=drawPlaneY 平面求交) */
  private drawAddAt(ndc: THREE.Vector2): boolean {
    const raycaster = new THREE.Raycaster()
    raycaster.setFromCamera(ndc, this.camera)
    const plane = new THREE.Plane(new THREE.Vector3(0, 1, 0), -this.drawPlaneY)
    const hit = new THREE.Vector3()
    if (!raycaster.ray.intersectPlane(plane, hit)) return false
    // 近平面外/离太远忽略
    if (hit.distanceTo(this.camera.position) > 80) return false
    this.drawPts.push(hit.clone())
    this.refreshDrawGroup()
    this.drawHandler?.([...this.drawPts.map((p) => ({ x: p.x, y: p.y, z: p.z }))])
    return true
  }

  private refreshDrawGroup() {
    this.clearDrawGroup()
    if (this.drawPts.length === 0) return
    const markMat = new THREE.MeshStandardMaterial({ color: 0xffd23a, emissive: 0xaa6a00, emissiveIntensity: 0.5 })
    const markGeo = new THREE.SphereGeometry(0.08, 12, 12)
    for (const p of this.drawPts) {
      const m = new THREE.Mesh(markGeo, markMat)
      m.position.copy(p)
      this.drawGroup.add(m)
    }
    if (this.drawPts.length >= 2) {
      const pts = this.drawPts.length >= 3 ? [...this.drawPts, this.drawPts[0]] : this.drawPts
      const geo = new THREE.BufferGeometry().setFromPoints(pts)
      this.drawLine = new THREE.Line(geo, new THREE.LineBasicMaterial({ color: 0x5aa9ff }))
      this.drawGroup.add(this.drawLine)
    }
  }

  private clearDrawGroup() {
    for (const c of [...this.drawGroup.children]) {
      const mesh = c as THREE.Mesh
      mesh.geometry?.dispose?.()
      ;(mesh.material as THREE.Material)?.dispose?.()
      this.drawGroup.remove(c)
    }
    this.drawLine = null
  }

  /** 退出绘制模式; apply=true 且航点>=3 时应用为新轨道 */
  exitDrawMode(apply: boolean, pts: TrackPoint[]): boolean {
    this.drawMode = false
    this.controls.enabled = true
    this.renderer.domElement.style.cursor = ''
    this.clearDrawGroup()
    if (apply && pts.length >= 3) {
      this.setTrack({ kind: 'poly', points: pts, tubeRadius: this.track.cfg.tubeRadius })
      return true
    }
    return false
  }

  onDrawPoint(cb: (pts: TrackPoint[]) => void) {
    this.drawHandler = cb
  }

  /** 撤销最后一个航点 */
  undoDrawPoint(): TrackPoint[] {
    if (this.drawPts.length > 0) this.drawPts.pop()
    this.refreshDrawGroup()
    const out = this.drawPts.map((p) => ({ x: p.x, y: p.y, z: p.z }))
    this.drawHandler?.(out)
    return out
  }

  /** 清空全部航点 */
  clearDrawPoints(): TrackPoint[] {
    this.drawPts = []
    this.refreshDrawGroup()
    const out: TrackPoint[] = []
    this.drawHandler?.(out)
    return out
  }

  // ---------- 机器人拼装(挂轨) ----------
  private buildRobot() {
    const group = new THREE.Group()
    group.name = 'robot'
    // 轨道中心线下移量 = 轮顶到车体中心
    // 车体中心在轨道中心下方 0.42m; 轮子局部 y=+0.24, 轮顶 = 0.24+0.09=0.33 → 世界 y = H-0.42+0.33 = H-0.09 ≈ 轨道下沿
    this.robotCenterY = 0.42

    const bodyMat = new THREE.MeshStandardMaterial({ color: 0x2f6faa, roughness: 0.4, metalness: 0.3 })
    const darkMat = new THREE.MeshStandardMaterial({ color: 0x1f2630, roughness: 0.6 })
    const wheelMat = new THREE.MeshStandardMaterial({ color: 0x1a1d22, roughness: 0.8 })

    // 顶部轮组(4 轮, 贴合轨道下沿): 局部 +Y 朝向轨道
    const wheelGeo = new THREE.CylinderGeometry(WHEEL_R, WHEEL_R, 0.05, 20)
    for (const [dx, dz] of [[-0.22, -0.17], [0.22, -0.17], [-0.22, 0.17], [0.22, 0.17]] as const) {
      const w = new THREE.Mesh(wheelGeo, wheelMat)
      w.rotation.x = Math.PI / 2 // 圆柱轴沿 Z? 挂轨轮轴沿轨道截面方向(水平)
      w.position.set(dx, 0.24, dz)
      w.castShadow = true
      group.add(w)
      this.wheels.push(w)
    }
    // 轮轴托架
    for (const dz of [-0.17, 0.17]) {
      const ax = new THREE.Mesh(new THREE.CylinderGeometry(0.02, 0.02, 0.5), darkMat)
      ax.rotation.z = Math.PI / 2
      ax.position.set(0, 0.24, dz)
      group.add(ax)
    }
    // 吊架(轮组→车体)
    for (const dz of [-0.17, 0.17]) {
      const h = new THREE.Mesh(new THREE.BoxGeometry(0.34, 0.18, 0.05), darkMat)
      h.position.set(0, 0.12, dz)
      group.add(h)
    }
    // 车体主机箱
    const body = new THREE.Mesh(new THREE.BoxGeometry(0.62, 0.22, 0.4), bodyMat)
    body.position.y = -0.02
    body.castShadow = true
    body.name = 'robot-body'
    group.add(body)
    this.pickTargets.push(body)
    // 指示灯(状态可视化: 前方红/绿)
    const ledMat = new THREE.MeshStandardMaterial({ color: 0x35c759, emissive: 0x35c759, emissiveIntensity: 1.2 })
    for (const dz of [-0.13, 0.13]) {
      const led = new THREE.Mesh(new THREE.SphereGeometry(0.03, 12, 12), ledMat)
      led.position.set(0.32, 0.0, dz)
      group.add(led)
    }
    // 底部传感器舱
    const sensor = new THREE.Mesh(new THREE.BoxGeometry(0.36, 0.12, 0.26), darkMat)
    sensor.position.y = -0.2
    group.add(sensor)

    // 伸缩杆(垂直, 末端带朝下巡检相机)
    this.extBase = new THREE.Mesh(
      new THREE.CylinderGeometry(0.045, 0.055, 0.3, 16),
      new THREE.MeshStandardMaterial({ color: 0x8a94a5, roughness: 0.4, metalness: 0.4 })
    )
    this.extBase.position.y = -0.26
    group.add(this.extBase)
    this.extRod = new THREE.Mesh(
      new THREE.CylinderGeometry(0.03, 0.03, 0.4, 12),
      new THREE.MeshStandardMaterial({ color: 0xb9c2cf, roughness: 0.3, metalness: 0.5 })
    )
    this.extRod.position.y = -0.56
    group.add(this.extRod)

    // 巡检相机(伸缩杆末端, 朝下)
    const camBody = new THREE.Mesh(
      new THREE.BoxGeometry(0.12, 0.1, 0.08),
      new THREE.MeshStandardMaterial({ color: 0x22262c, roughness: 0.5 })
    )
    camBody.position.y = -0.78
    group.add(camBody)
    const lens = new THREE.Mesh(
      new THREE.CylinderGeometry(0.028, 0.032, 0.04, 16),
      new THREE.MeshStandardMaterial({ color: 0x2b3a55, roughness: 0.15, metalness: 0.6 })
    )
    lens.rotation.x = Math.PI / 2
    lens.position.y = -0.84
    group.add(lens)
    // 相机视锥示意(透明)
    const cone = new THREE.Mesh(
      new THREE.ConeGeometry(0.16, 0.32, 4, 1, true),
      new THREE.MeshBasicMaterial({ color: 0x5aa9ff, transparent: true, opacity: 0.12, side: THREE.DoubleSide })
    )
    cone.rotation.x = Math.PI
    cone.position.y = -1.0
    group.add(cone)

    this.scene.add(group)
    this.robot = group
  }

  /** 更新机器人位姿 */
  setRobot(sMeters: number, extHMeters: number, wheelSpeed = 0, moving = false) {
    if (!this.robot || this.disposed) return
    const pos = this.track.positionAt(sMeters)
    const tan = this.track.tangentAt(sMeters)
    const norm = this.track.normalAt(sMeters)

    this.robot.position.copy(pos)
    this.robot.position.y = pos.y - this.robotCenterY

    // 朝向: 车体前方=切线, 顶部=世界+Y(轮子朝轨道)
    const mat = new THREE.Matrix4()
    const up = new THREE.Vector3(0, 1, 0)
    const xAxis = tan.clone().normalize()
    const zAxis = norm.clone().normalize()
    mat.makeBasis(xAxis, up, zAxis)
    this.robot.quaternion.setFromRotationMatrix(mat)

    // 轮子滚动
    const ds = sMeters - this._lastS
    this._lastS = sMeters
    const spin = moving ? (ds / WHEEL_R) : 0
    for (const w of this.wheels) {
      w.rotateOnWorldAxis(new THREE.Vector3(0, 0, 1), spin)
    }

    // 伸缩杆升降(伸长=杆向下移动)
    const ext = Math.max(0, Math.min(1, extHMeters / 0.6))
    this.extRod.position.y = -0.56 - ext * 0.5
  }

  setSelected(on: boolean) {
    this.selectObject(on ? 'robot' : null)
  }

  /** 统一选中高亮: key = 'robot' | 'obstacle-<id>' | 'rfid-<id>' | null */
  selectObject(key: string | null) {
    this.selectedKey = key
    // 清除机器人高亮
    const body = this.robot?.getObjectByName('robot-body') as THREE.Mesh | undefined
    if (body) {
      const m = body.material as THREE.MeshStandardMaterial
      m.emissive = new THREE.Color(0x000000)
      m.emissiveIntensity = 0
    }
    // 清除障碍物/RFID 高亮
    for (const mesh of this.obstacleMeshes.values()) {
      const m = mesh.material as THREE.MeshStandardMaterial
      m.emissive = new THREE.Color(0x220000)
      m.emissiveIntensity = 0
    }
    for (const mesh of this.rfidMeshes.values()) {
      const m = mesh.material as THREE.MeshStandardMaterial
      m.emissive = new THREE.Color(0x001a14)
      m.emissiveIntensity = 0
    }
    if (!key) return
    if (key === 'robot') {
      if (body) {
        const m = body.material as THREE.MeshStandardMaterial
        m.emissive = new THREE.Color(0x2f6faa)
        m.emissiveIntensity = 0.6
      }
      return
    }
    const [kind, idStr] = key.split('-')
    const id = Number(idStr)
    if (kind === 'obstacle') {
      const mesh = this.obstacleMeshes.get(id)
      if (mesh) {
        const m = mesh.material as THREE.MeshStandardMaterial
        m.emissive = new THREE.Color(0xff3b30)
        m.emissiveIntensity = 0.7
      }
    } else if (kind === 'rfid') {
      const mesh = this.rfidMeshes.get(id)
      if (mesh) {
        const m = mesh.material as THREE.MeshStandardMaterial
        m.emissive = new THREE.Color(0x00e0b0)
        m.emissiveIntensity = 0.9
      }
    }
  }

  // ---------- 障碍物 / RFID ----------
  /** 同步障碍物网格(增/删/移动) */
  setObstacles(list: ObstacleVisual[]) {
    this.lastObstacles = [...list]
    // 删除已移除的
    const ids = new Set(list.map((o) => o.id))
    for (const [id, mesh] of [...this.obstacleMeshes]) {
      if (!ids.has(id)) {
        this.obstacleGroup.remove(mesh)
        this.pickTargets = this.pickTargets.filter((t) => t !== mesh)
        mesh.geometry.dispose()
        ;(mesh.material as THREE.Material).dispose()
        this.obstacleMeshes.delete(id)
      }
    }
    // 更新/创建
    for (const o of list) {
      if (!o.enabled) continue
      let mesh = this.obstacleMeshes.get(o.id)
      if (!mesh) {
        mesh = new THREE.Mesh(
          new THREE.BoxGeometry(0.3, 0.5, 0.3),
          new THREE.MeshStandardMaterial({
            color: 0xd63a34, roughness: 0.5, metalness: 0.2,
            transparent: true, opacity: 0.92,
          })
        )
        mesh.castShadow = true
        mesh.name = `obstacle-${o.id}`
        this.obstacleGroup.add(mesh)
        this.pickTargets.push(mesh)
        this.obstacleMeshes.set(o.id, mesh)
      }
      mesh.scale.x = Math.max(0.05, o.width / 1000) / 0.3
      this._placeOnTrack(mesh, o.s, true)
    }
  }

  /** 同步 RFID 卡片网格 */
  setRfids(list: RfidVisual[]) {
    this.lastRfids = [...list]
    const ids = new Set(list.map((r) => r.id))
    for (const [id, mesh] of [...this.rfidMeshes]) {
      if (!ids.has(id)) {
        this.rfidGroup.remove(mesh)
        this.pickTargets = this.pickTargets.filter((t) => t !== mesh)
        mesh.geometry.dispose()
        ;(mesh.material as THREE.Material).dispose()
        this.rfidMeshes.delete(id)
      }
    }
    for (const r of list) {
      let mesh = this.rfidMeshes.get(r.id)
      if (!mesh) {
        mesh = new THREE.Mesh(
          new THREE.BoxGeometry(0.15, 0.1, 0.025),
          new THREE.MeshStandardMaterial({
            color: 0x17a98b, roughness: 0.35, metalness: 0.4,
            emissive: new THREE.Color(0x001a14), emissiveIntensity: 0,
          })
        )
        mesh.name = `rfid-${r.id}`
        this.rfidGroup.add(mesh)
        this.pickTargets.push(mesh)
        this.rfidMeshes.set(r.id, mesh)
      }
      this._placeOnTrack(mesh, r.s, false)
    }
  }

  /**
   * 沿轨道定位: 障碍物挂轨道下沿(向下), RFID 贴下沿(扁片朝下)。
   * 朝向基必须是右手系(det=+1): x=切线, y=世界 up, z=法线;
   * 若用 down=(0,-1,0) 会得到 det=-1 反射矩阵, setFromRotationMatrix 提取出错误四元数,
   * 盒子在弯道/反向直段被压扁或翻转(看起来像移动一段后消失)。盒子中心对称, y 取 up 无视觉差异。
   * 非有限/退化时跳过, 防止对象"消失"。
   */
  private _placeOnTrack(mesh: THREE.Mesh, sMm: number, hangDown: boolean) {
    const pos = this.track.positionAt(sMm / 1000)
    const tan = this.track.tangentAt(sMm / 1000)
    const norm = this.track.normalAt(sMm / 1000)
    if (![pos.x, pos.y, pos.z, tan.x, tan.y, tan.z, norm.x, norm.y, norm.z].every(Number.isFinite)) return
    if (tan.lengthSq() < 1e-12 || norm.lengthSq() < 1e-12) return
    const tubeR = this.track.cfg.tubeRadius ?? 0.06
    const up = new THREE.Vector3(0, 1, 0)
    const mat = new THREE.Matrix4()
    mat.makeBasis(tan, up, norm)
    mesh.quaternion.setFromRotationMatrix(mat)
    mesh.position.copy(pos)
    mesh.position.y = pos.y - tubeR - (hangDown ? 0.18 : 0.03)
  }

  // ---------- 3D 拖拽移动障碍物/RFID ----------
  onDragMove(cb: (info: { type: 'obstacle' | 'rfid'; id: number; sMm: number }) => void) {
    this.dragHandler = cb
  }

  private handlePointerDown = (e: MouseEvent) => {
    if (this.drawMode || e.button !== 0) return
    const rect = this.renderer.domElement.getBoundingClientRect()
    const ndc = new THREE.Vector2(
      ((e.clientX - rect.left) / rect.width) * 2 - 1,
      -((e.clientY - rect.top) / rect.height) * 2 + 1
    )
    const raycaster = new THREE.Raycaster()
    raycaster.setFromCamera(ndc, this.camera)
    const hits = raycaster.intersectObjects(this.pickTargets, true)
    if (hits.length === 0) return
    const name = hits[0].object.name || ''
    let type: 'obstacle' | 'rfid' | null = null
    let id = 0
    if (name.startsWith('obstacle-')) {
      type = 'obstacle'
      id = Number(name.slice('obstacle-'.length))
    } else if (name.startsWith('rfid-')) {
      type = 'rfid'
      id = Number(name.slice('rfid-'.length))
    } else {
      return
    }
    const mesh = (type === 'obstacle' ? this.obstacleMeshes : this.rfidMeshes).get(id)
    if (!mesh) return
    // 点击选中 + 进入拖拽
    this.pickHandler?.({ type, id, name, pos: mesh.position.clone() })
    this.dragging = { type, id, mesh, hang: type === 'obstacle', lastS: -1, lastT: performance.now() }
    this.controls.enabled = false
    this.renderer.domElement.style.cursor = 'grabbing'
    e.preventDefault()
  }

  private handlePointerMove = (e: MouseEvent) => {
    if (!this.dragging) return
    const rect = this.renderer.domElement.getBoundingClientRect()
    const ndc = new THREE.Vector2(
      ((e.clientX - rect.left) / rect.width) * 2 - 1,
      -((e.clientY - rect.top) / rect.height) * 2 + 1
    )
    const raycaster = new THREE.Raycaster()
    raycaster.setFromCamera(ndc, this.camera)
    const plane = new THREE.Plane(new THREE.Vector3(0, 1, 0), -this.track.H)
    const hit = new THREE.Vector3()
    if (!raycaster.ray.intersectPlane(plane, hit)) return
    const sMm = Math.round(this.track.nearestS(hit) * 1000)
    this._placeOnTrack(this.dragging.mesh, sMm, this.dragging.hang)
    const now = performance.now()
    if (Math.abs(sMm - this.dragging.lastS) >= 10 || now - this.dragging.lastT >= 80) {
      this.dragging.lastS = sMm
      this.dragging.lastT = now
      this.dragHandler?.({ type: this.dragging.type, id: this.dragging.id, sMm })
    }
  }

  private handlePointerUp = () => {
    if (!this.dragging) return
    this.dragging = null
    this.controls.enabled = true
    this.renderer.domElement.style.cursor = ''
  }

  // ---------- 相机 ----------
  setDefaultCamera() {
    // 默认视角: 从机器人下方偏仰观察(挂轨形态)
    const pos = this.track.positionAt(0)
    this.camera.position.set(pos.x + 1.2, 0.35, pos.z + 2.2)
    this.controls.target.set(pos.x, 1.6, pos.z)
    this.controls.update()
  }

  focusRobot(sMeters: number) {
    const pos = this.track.positionAt(sMeters)
    this.controls.target.copy(pos).add(new THREE.Vector3(0, 1.2, 0))
  }

  // ---------- 交互 ----------
  private handleClick = (e: MouseEvent) => {
    const rect = this.renderer.domElement.getBoundingClientRect()
    const ndc = new THREE.Vector2(
      ((e.clientX - rect.left) / rect.width) * 2 - 1,
      -((e.clientY - rect.top) / rect.height) * 2 + 1
    )
    // 绘制模式: 点击放置航点
    if (this.drawMode) {
      this.drawAddAt(ndc)
      return
    }
    const raycaster = new THREE.Raycaster()
    raycaster.setFromCamera(ndc, this.camera)
    const hits = raycaster.intersectObjects(this.pickTargets, true)
    if (hits.length === 0) return
    const obj = hits[0].object
    const name = obj.name || ''
    const pos = this.robot?.position.clone() ?? new THREE.Vector3()
    if (name === 'robot-body') {
      this.pickHandler?.({ type: 'robot', id: 0, name, pos })
    } else if (name.startsWith('obstacle-')) {
      this.pickHandler?.({ type: 'obstacle', id: Number(name.slice('obstacle-'.length)), name, pos })
    } else if (name.startsWith('rfid-')) {
      this.pickHandler?.({ type: 'rfid', id: Number(name.slice('rfid-'.length)), name, pos })
    }
  }

  onPick(cb: (info: { type: PickType; id: number; name: string; pos: THREE.Vector3 }) => void) {
    this.pickHandler = cb
  }

  // ---------- 渲染循环 (setInterval 驱动: 后台 tab 亦可持续推进仿真与状态上报) ----------
  private loop = () => {
    if (this.disposed) return
    const dt = Math.min(this.clock.getDelta(), 0.05)
    this._frameCb?.(dt)
    this.controls.update()
    this.renderer.render(this.scene, this.camera)
  }

  private startLoop() {
    this.stopLoop()
    this.timer = window.setInterval(this.loop, 16)
  }

  private stopLoop() {
    if (this.timer) {
      clearInterval(this.timer)
      this.timer = 0
    }
  }

  private handleResize = () => {
    const w = this.container.clientWidth
    const h = this.container.clientHeight
    if (w === 0 || h === 0) return
    this.camera.aspect = w / h
    this.camera.updateProjectionMatrix()
    this.renderer.setSize(w, h)
  }

  /** 每帧回调(外部驱动动画) */
  onFrame(cb: (dt: number) => void) {
    this._frameCb = cb
    this.clock.getDelta() // 重置计时
    this.startLoop()
  }

  dispose() {
    this.disposed = true
    this.stopLoop()
    window.removeEventListener('resize', this.handleResize)
    this.renderer.domElement.removeEventListener('click', this.handleClick)
    this.renderer.domElement.removeEventListener('mousedown', this.handlePointerDown)
    window.removeEventListener('mousemove', this.handlePointerMove)
    window.removeEventListener('mouseup', this.handlePointerUp)
    this.controls.dispose()
    for (const g of [this.trackGroup, this.drawGroup]) {
      for (const c of [...g.children]) {
        const mesh = c as THREE.Mesh
        mesh.geometry?.dispose?.()
        ;(mesh.material as THREE.Material)?.dispose?.()
      }
    }
    this.renderer.dispose()
    if (this.renderer.domElement.parentElement === this.container) {
      this.container.removeChild(this.renderer.domElement)
    }
  }
}
