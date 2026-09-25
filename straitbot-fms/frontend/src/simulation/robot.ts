/**
 * 挂轨机器人运动学（1D 沿轨弧长 + 伸缩杆升降）。
 * 单位: mm / mm/s / mm/s²; 状态语义对齐协议 V2.0(0x09/0x0A/0x0B/0x0C/0x0E)。
 * 环形轨道: s ∈ [0, loopLenMm), 越过边界取模绕圈。
 */

export type ChassisState = 0 | 1 | 2 | 3 // 0空闲 1运行中 2已到达(瞬态) 3初始化中
export type MotorState = 0 | 1 | 2 | 3

export const CHASSIS_IDLE = 0
export const CHASSIS_RUNNING = 1
export const CHASSIS_ARRIVED = 2
export const CHASSIS_INITING = 3

export const MOTOR_STOP = 0
export const MOTOR_UP = 1
export const MOTOR_DOWN = 2
export const MOTOR_GOTO = 3

/** 轨道障碍物(用于避障测试) */
export interface Obstacle {
  id: number
  s: number // 弧长中心 mm
  width: number // 沿轨宽度 mm
  enabled: boolean
}

export interface RobotSnapshot {
  s: number // 弧长 mm
  v: number // 线速度 mm/s
  state: ChassisState
  mode: number // 固定 2(嵌入式控制)
  yawX10: number // 偏航角*10(由页面注入)
  extH: number // 伸缩杆当前高度 mm
  extV: number // 伸缩速度 mm/s
  extState: MotorState
  blocked: boolean // 前方避障中(速度被障碍物限制)
  obstacleDist: number | null // 前方最近障碍物距离 mm(到障碍物前缘, 无则 null)
}

export interface MoveCmd {
  mode: number // 0停 1前进 2后退 5移动到指定位置 6设定速度 10复位
  linearX: number // mm/s
  targetX: number // mm(模式5)
}

export interface ExtCmd {
  mid: number
  mode: number // 0停 1正转(升) 2反转(降) 3指定坐标 4复位 6设速度
  speed: number // mm/s
  coord: number // mm 目标高度
}

const ARRIVAL_MS = 150 // "已到达/已到位"瞬态保持时长(>100ms 上报周期, 保证至少上报一帧状态2)
const SAFE_STOP_DIST = 300 // 避障安全停车距离 mm(前方障碍物进入此距离则减速停车)

export class RobotKinematics {
  readonly loopLenMm: number
  s = 0
  v = 0
  state: ChassisState = CHASSIS_IDLE
  mode = 2
  private target: number | null = null // 目标弧长(mm), 模式5
  private desiredV = 0 // 目标速度(mm/s), 前进/后退/停止
  private speedLimit = 1000 // mm/s 限速(0x09 模式6 可设定)
  private accel = 250 // mm/s²
  private arrivalUntil = 0
  private obstacles: Obstacle[] = []
  private blocked = false
  private obstacleDist: number | null = null

  extH = 0
  extV = 0
  extState: MotorState = MOTOR_STOP
  extSpeedLimit = 150 // 伸缩限速 mm/s
  extMax = 600 // 伸缩杆最大高度 mm
  private extTarget: number | null = null
  private extDesiredV = 0
  private extAccel = 120 // 伸缩加减速 mm/s²
  private extArrivalUntil = 0

  constructor(loopLenMeters: number) {
    this.loopLenMm = loopLenMeters * 1000
  }

  /** 每帧推进 dtMs 毫秒 */
  step(dtMs: number, nowMs: number) {
    const dt = dtMs / 1000
    // 底盘
    if (this.state === CHASSIS_INITING) {
      this.s = 0
      this.v = 0
      this.desiredV = 0
      this.target = null
      this.state = CHASSIS_IDLE
    } else {
      this._stepChassis(dt, nowMs)
    }
    // 伸缩杆
    this._stepExt(dt, nowMs)
  }

  private _stepChassis(dt: number, nowMs: number) {
    // "已到达"瞬态: 保持 ARRIVAL_MS 再转空闲
    if (this.state === CHASSIS_ARRIVED) {
      if (nowMs >= this.arrivalUntil) this.state = CHASSIS_IDLE
      return
    }
    const vmax = this.speedLimit
    if (this.target !== null) {
      // 模式5: 梯形速度曲线 → 目标弧长
      const dist = this._wrapDelta(this.target - this.s)
      if (Math.abs(dist) < 10 && Math.abs(this.v) < 15) {
        this.s = this._wrap(this.target)
        this.v = 0
        this.desiredV = 0
        this.target = null
        this.blocked = false
        this.obstacleDist = null
        this.state = CHASSIS_ARRIVED
        this.arrivalUntil = nowMs + ARRIVAL_MS
        return
      }
      const dir = Math.sign(dist)
      // 避障: 前方 SAFE_STOP_DIST 内有障碍物 → 减速停车(target 保留, 障碍移开后继续)
      const obs = this._frontObstacle(this.s, dir)
      this.obstacleDist = obs?.dist ?? null
      this.blocked = obs !== null && obs.dist < SAFE_STOP_DIST
      const needDecel = (this.v * this.v) / (2 * this.accel)
      let vTarget = 0
      if (!this.blocked && Math.abs(dist) > needDecel + 10) vTarget = dir * vmax
      this.v = this._moveToward(this.v, vTarget, this.accel, dt)
      this.s = this._wrap(this.s + this.v * dt)
      this.state = CHASSIS_RUNNING
    } else {
      // 恒速/减速: 向目标速度收敛
      const dir = Math.sign(this.desiredV)
      const obs = dir !== 0 ? this._frontObstacle(this.s, dir) : null
      this.obstacleDist = obs?.dist ?? null
      this.blocked = obs !== null && obs.dist < SAFE_STOP_DIST
      const vTarget = this.blocked ? 0 : this.desiredV
      this.v = this._moveToward(this.v, vTarget, this.accel, dt)
      if (Math.abs(this.v) >= 0.5) {
        this.s = this._wrap(this.s + this.v * dt)
        this.state = CHASSIS_RUNNING
      } else {
        this.v = 0
        this.state = CHASSIS_IDLE
      }
    }
  }

  /** 前方最近障碍物(沿运动方向, 到障碍物前缘距离)。无则 null。 */
  private _frontObstacle(s: number, dir: number): { dist: number } | null {
    if (dir === 0 || this.obstacles.length === 0) return null
    let best: number | null = null
    for (const o of this.obstacles) {
      const d = dir > 0 ? this._wrapDelta(o.s - s) : this._wrapDelta(s - o.s)
      const front = d - o.width / 2
      if (front >= 0 && (best === null || front < best)) best = front
    }
    return best === null ? null : { dist: best }
  }

  private _stepExt(dt: number, nowMs: number) {
    // "已到位"瞬态(协议状态2): 保持 ARRIVAL_MS 后转空闲
    if (this.extState === 2) {
      if (nowMs >= this.extArrivalUntil) this.extState = MOTOR_STOP
      return
    }
    if (this.extTarget !== null) {
      // 模式3/4: 目标高度
      const dist = this.extTarget - this.extH
      if (Math.abs(dist) < 3 && Math.abs(this.extV) < 5) {
        this.extH = this._clampExt(this.extTarget)
        this.extV = 0
        this.extDesiredV = 0
        this.extTarget = null
        this.extState = 2 // 已到位(协议语义)
        this.extArrivalUntil = nowMs + ARRIVAL_MS
        return
      }
      const dir = Math.sign(dist)
      const needDecel = (this.extV * this.extV) / (2 * this.extAccel)
      if (Math.abs(dist) <= needDecel + 3) {
        this.extV = this._moveToward(this.extV, 0, this.extAccel, dt)
      } else {
        this.extV = this._moveToward(this.extV, dir * this.extSpeedLimit, this.extAccel, dt)
      }
      this.extH = this._clampExt(this.extH + this.extV * dt)
      this.extState = 1 // 运行中(协议语义)
    } else {
      this.extV = this._moveToward(this.extV, this.extDesiredV, this.extAccel, dt)
      if (Math.abs(this.extV) >= 0.5) {
        this.extH = this._clampExt(this.extH + this.extV * dt)
        this.extState = 1 // 运行中(协议语义)
      } else {
        this.extV = 0
        this.extState = MOTOR_STOP
      }
    }
  }

  // ---------- 指令 ----------
  applyMove(c: MoveCmd) {
    switch (c.mode) {
      case 0: // 停止
        this.target = null
        this.desiredV = 0
        break
      case 1: // 前进
        this.target = null
        this.desiredV = Math.max(0, Math.min(this.speedLimit, Math.abs(c.linearX)))
        break
      case 2: // 后退
        this.target = null
        this.desiredV = -Math.max(0, Math.min(this.speedLimit, Math.abs(c.linearX)))
        break
      case 5: // 移动到指定位置
        this.target = c.targetX
        this.desiredV = 0
        break
      case 6: // 设定速度
        if (Math.abs(c.linearX) > 0) this.speedLimit = Math.min(3000, Math.abs(c.linearX))
        this.target = null
        break
      case 10: // 初始化复位
        this.state = CHASSIS_INITING
        this.target = null
        this.desiredV = 0
        this.v = 0
        break
      default:
        break
    }
  }

  applyExt(c: ExtCmd) {
    if (c.mid !== 1) return // 仿真只定义电机1=伸缩杆
    switch (c.mode) {
      case 0:
        this.extTarget = null
        this.extDesiredV = 0
        break
      case 1: // 正转(升)
        this.extTarget = null
        this.extDesiredV = Math.max(0, Math.min(this.extSpeedLimit, Math.abs(c.speed)))
        break
      case 2: // 反转(降)
        this.extTarget = null
        this.extDesiredV = -Math.max(0, Math.min(this.extSpeedLimit, Math.abs(c.speed)))
        break
      case 3: // 指定坐标(目标高度)
        this.extTarget = this._clampExt(c.coord)
        this.extDesiredV = 0
        break
      case 4: // 复位(回零)
        this.extTarget = 0
        this.extDesiredV = 0
        break
      case 6: // 设定速度
        if (Math.abs(c.speed) > 0) this.extSpeedLimit = Math.min(600, Math.abs(c.speed))
        this.extTarget = null
        break
      default:
        break
    }
  }

  reset() {
    this.s = 0
    this.v = 0
    this.state = CHASSIS_IDLE
    this.target = null
    this.desiredV = 0
    this.blocked = false
    this.obstacleDist = null
  }

  /** 更新障碍物列表(仅启用项参与避障) */
  setObstacles(list: Obstacle[]) {
    this.obstacles = list.filter((o) => o.enabled)
  }

  snapshot(yawX10 = 0): RobotSnapshot {
    return {
      s: Math.round(this.s),
      v: Math.round(this.v),
      state: this.state,
      mode: this.mode,
      yawX10,
      extH: Math.round(this.extH),
      extV: Math.round(this.extV),
      extState: this.extState,
      blocked: this.blocked,
      obstacleDist: this.obstacleDist === null ? null : Math.max(0, Math.round(this.obstacleDist)),
    }
  }

  // ---------- 内部 ----------
  private _moveToward(v: number, target: number, accel: number, dt: number): number {
    const dv = target - v
    const step = accel * dt
    if (Math.abs(dv) <= step) return target
    return v + Math.sign(dv) * step
  }

  private _wrap(s: number): number {
    const S = this.loopLenMm
    return ((s % S) + S) % S
  }

  /** 环形最短有向增量 */
  private _wrapDelta(d: number): number {
    const S = this.loopLenMm
    let dd = ((d % S) + S) % S
    if (dd > S / 2) dd -= S
    return dd
  }

  private _clampExt(h: number): number {
    return Math.max(0, Math.min(this.extMax, h))
  }
}
