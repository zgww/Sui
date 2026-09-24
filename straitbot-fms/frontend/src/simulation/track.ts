import * as THREE from 'three'

/**
 * 轨道: 支持两种形态
 * - rect: 矩形环(圆角矩形, XZ 平面, Y 为高度) — 参数化直段/半径/高度, 解析求值
 * - poly: 手动绘制轨道 — 由航点(世界坐标)生成闭合 CatmullRom 曲线
 *   定位(positionAt/tangentAt/normalAt)与几何渲染(getCurve)使用同一条曲线, 保证装饰物完全贴合管道
 * 弧长单位: 米(场景内 1 单位 = 1m)。协议 mm 由调用方换算。
 */
export interface TrackPoint {
  x: number
  y: number
  z: number
}

export interface TrackConfig {
  kind?: 'rect' | 'poly'
  straightLen?: number // rect: 直段长 m
  radius?: number      // rect: 弯道半径 m
  height?: number      // rect: 轨道中心悬挂高度 m
  tubeRadius?: number  // 轨道管径 m
  points?: TrackPoint[] // poly: 航点(建议同一高度)
}

export class Track {
  readonly cfg: TrackConfig
  readonly kind: 'rect' | 'poly'
  readonly L: number
  readonly R: number
  readonly H: number
  readonly totalLength: number
  readonly seg1: number // 下直段终点(rect)
  readonly seg2: number // 右弧终点(rect)
  readonly seg3: number // 上直段终点(rect)

  // poly: 闭合 CatmullRom 曲线(与渲染共用)
  private curve: THREE.CatmullRomCurve3 | null = null

  constructor(cfg: Partial<TrackConfig> = {}) {
    this.cfg = { kind: 'rect', straightLen: 6, radius: 1.5, height: 2.5, tubeRadius: 0.06, ...cfg }

    if (this.cfg.kind === 'poly' && this.cfg.points && this.cfg.points.length >= 3) {
      this.kind = 'poly'
      const raw = this.cfg.points.map((p) => new THREE.Vector3(p.x, p.y, p.z))
      this.curve = new THREE.CatmullRomCurve3(raw, true, 'catmullrom', 0.5)
      this.totalLength = this.curve.getLength()
      this.H = raw.reduce((s, p) => s + p.y, 0) / raw.length
      this.L = 0
      this.R = 0
      this.seg1 = 0
      this.seg2 = 0
      this.seg3 = 0
    } else {
      this.kind = 'rect'
      this.L = this.cfg.straightLen ?? 6
      this.R = this.cfg.radius ?? 1.5
      this.H = this.cfg.height ?? 2.5
      this.seg1 = this.L
      this.seg2 = this.L + Math.PI * this.R
      this.seg3 = 2 * this.L + Math.PI * this.R
      this.totalLength = this.seg3 + Math.PI * this.R
    }
  }

  /** poly: 底层曲线(渲染管道用); rect 返回 null */
  getCurve(): THREE.CatmullRomCurve3 | null {
    return this.curve
  }

  /** 弧长(m) → 归一化参数 u∈[0,1) */
  private _u(s: number): number {
    const S = this.totalLength
    return (((s % S) + S) % S) / S
  }

  /** 弧长(m) → 世界坐标 */
  positionAt(s: number): THREE.Vector3 {
    if (!Number.isFinite(s)) s = 0
    if (this.curve) {
      return this.curve.getPointAt(this._u(s))
    }
    const S = this.totalLength
    const ss = ((s % S) + S) % S
    const { L, R, H } = this
    if (ss < this.seg1) {
      return new THREE.Vector3(-L / 2 + ss, H, -R)
    }
    if (ss < this.seg2) {
      const ang = -Math.PI / 2 + (ss - this.seg1) / R
      return new THREE.Vector3(L / 2 + R * Math.cos(ang), H, R * Math.sin(ang))
    }
    if (ss < this.seg3) {
      return new THREE.Vector3(L / 2 - (ss - this.seg2), H, R)
    }
    const ang = Math.PI / 2 + (ss - this.seg3) / R
    return new THREE.Vector3(-L / 2 + R * Math.cos(ang), H, R * Math.sin(ang))
  }

  /** 弧长(m) → 单位切线(沿行进方向) */
  tangentAt(s: number): THREE.Vector3 {
    if (!Number.isFinite(s)) s = 0
    if (this.curve) {
      return this.curve.getTangentAt(this._u(s)).normalize()
    }
    const S = this.totalLength
    const ss = ((s % S) + S) % S
    const { R } = this
    if (ss < this.seg1) return new THREE.Vector3(1, 0, 0)
    if (ss < this.seg2) {
      const ang = -Math.PI / 2 + (ss - this.seg1) / R
      return new THREE.Vector3(-Math.sin(ang), 0, Math.cos(ang))
    }
    if (ss < this.seg3) return new THREE.Vector3(-1, 0, 0)
    const ang = Math.PI / 2 + (ss - this.seg3) / R
    return new THREE.Vector3(-Math.sin(ang), 0, Math.cos(ang))
  }

  /**
   * 弧长(m) → 轨道截面法线(单位)。
   * 统一定义 norm = tan × up = (-t.z, 0, t.x): 切线绕世界 +Y 逆时针转 90°,
   * 直段为轮轴方向, 弧段指向圆心。rect/poly 同源, 保证 makeBasis(tan, up, norm) 行列式恒为 +1。
   * (旧实现 rect 弧段法线取离心方向, 与直段/poly 反向, 组装出 det=-1 反射矩阵导致模型压扁。)
   */
  normalAt(s: number): THREE.Vector3 {
    const t = this.tangentAt(s)
    return new THREE.Vector3(-t.z, 0, t.x).normalize()
  }

  /** 均匀采样(闭合), 用于轨道几何 */
  sample(n = 220): THREE.Vector3[] {
    const pts: THREE.Vector3[] = []
    for (let i = 0; i < n; i++) {
      pts.push(this.positionAt((this.totalLength * i) / n))
    }
    pts.push(this.positionAt(0))
    return pts
  }

  /** 世界点 → 最近弧长(m)(3D 拖拽移动障碍物/RFID 用)。弧长均匀粗采样 + 局部细分。 */
  nearestS(p: THREE.Vector3): number {
    if (!p) return 0
    const N = 320
    let best = 0
    let bestD = Infinity
    // 粗采样: 弧长均匀(闭环绕行)
    for (let i = 0; i < N; i++) {
      const q = this.positionAt((this.totalLength * i) / N)
      const d = q.distanceToSquared(p)
      if (d < bestD) { bestD = d; best = (this.totalLength * i) / N }
    }
    // 局部细分: best 段 ± 一个采样间距内再采 40 点
    const step = this.totalLength / N
    for (let k = -40; k <= 40; k++) {
      const s = (best + (k * step) / 40 + this.totalLength) % this.totalLength
      const q = this.positionAt(s)
      const d = q.distanceToSquared(p)
      if (d < bestD) { bestD = d; best = s }
    }
    return best
  }
}
