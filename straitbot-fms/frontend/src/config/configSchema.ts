// ===== 机器人配置 Schema 驱动 =====
// 前端配置树+表单完全由此文件驱动。调整字段/分类/顺序只需改此文件。

export interface ConfigField {
  key: string
  label: string
  type: 'float' | 'int' | 'bool' | 'string' | 'select' | 'json'
  unit?: string
  desc?: string
  min?: number
  max?: number
  step?: number
  options?: { label: string; value: any }[]
  writable: boolean
}

export interface ConfigCategory {
  key: string
  label: string
  fields: string[]
}

// ===== 字段定义 =====
export const configFields: ConfigField[] = [
  // ── 运动/速度 ──
  { key: 'move_speed',         label: '行进速度',       type: 'float',  unit: 'm/s',   desc: '轨道最大行进速度',                    min: 0.01, max: 1.0,  step: 0.01, writable: true },
  { key: 'angular_speed',      label: '角速度',         type: 'float',  unit: '°/s',  desc: '转向角速度',                           min: 0,    max: 90,   step: 1,    writable: true },
  { key: 'director',           label: '轨道方向',       type: 'select',               desc: '0=正向 1=反向',                        options: [{ label: '正向', value: 0 }, { label: '反向', value: 1 }], writable: true },
  { key: 'is_ring',            label: '环形轨道',       type: 'bool',                 desc: '环形轨道则无终点限位',                   writable: true },

  // ── 限位 ──
  { key: 'limit_x0',           label: 'X轴最小限位',    type: 'float',  unit: 'm',    desc: '轨道起点坐标',                          min: 0, max: 100, step: 0.1, writable: true },
  { key: 'limit_x1',           label: 'X轴最大限位',    type: 'float',  unit: 'm',    desc: '轨道终点坐标',                          min: 0, max: 100, step: 0.1, writable: true },

  // ── 到位容差 ──
  { key: 'inplace.distance',   label: '距离容差',       type: 'float',  unit: 'm',    desc: '到位判定距离误差',                      min: 0.01, max: 1,     step: 0.01, writable: true },
  { key: 'inplace.angle',      label: '角度容差',       type: 'float',  unit: '°',    desc: '到位判定角度误差',                      min: 0.1,  max: 10,   step: 0.1,  writable: true },
  { key: 'inplace.duration',   label: '时间容差',       type: 'int',    unit: 'ms',   desc: '到位后稳定等待时间',                    min: 500,  max: 60000, step: 500, writable: true },

  // ── Home点 ──
  { key: 'home.x',             label: 'Home X',         type: 'float',  unit: 'm',    desc: '初始位置 X',                            writable: true },
  { key: 'home.y',             label: 'Home Y',         type: 'float',  unit: 'm',    desc: '初始位置 Y',                            writable: true },

  // ── 电池 ──
  { key: 'battery.low',               label: '低电量阈值',   type: 'int',   unit: '%', desc: '低于此值触发低电告警',               min: 5,   max: 90, step: 5,    writable: true },
  { key: 'battery.normal',            label: '恢复正常',     type: 'int',   unit: '%', desc: '高于此值解除低电告警',               min: 10,  max: 95, step: 5,    writable: true },
  { key: 'battery.low_voltage',       label: '低电压阈值',   type: 'float', unit: 'V', desc: '电池低电压门槛',                     min: 10,  max: 48, step: 0.1,  writable: true },
  { key: 'battery.charge_full_current', label: '满电电流',  type: 'float', unit: 'A', desc: '充电电流低于此值判定充满',           min: 0,   max: 10, step: 0.1,  writable: true },
  { key: 'battery.charge_full_voltage', label: '满电电压',  type: 'float', unit: 'V', desc: '充电电压达到此值判定充满',           min: 0,   max: 48, step: 0.1,  writable: true },

  // ── 云台 ──
  { key: 'ptz.addr',           label: 'PTZ地址',         type: 'string',              desc: '海康威视云台 IP',                       writable: true },
  { key: 'realtime_thermal',   label: '实时测温',        type: 'bool',                desc: '红外实时温度测量',                      writable: true },

  // ── 升降杆 ──
  { key: 'with_lift',          label: '有升降杆',       type: 'bool',                desc: '是否安装升降杆硬件',                    writable: false },
  { key: 'lift_limit',         label: '升降杆限位',     type: 'float',  unit: 'm',   desc: '最大高度',                              min: 0, max: 3,   step: 0.1,   writable: true },
  { key: 'lift_speed',         label: '升降杆速度',     type: 'float',  unit: 'm/s', desc: '升降速度',                              min: 0, max: 0.05, step: 0.01, writable: true },

  // ── 电梯 ──
  { key: 'elevator.enable',    label: '电梯模块',       type: 'bool',                desc: '多楼层电梯功能',                        writable: true },

  // ── 传感器 ──
  { key: 'obstacle_light',     label: '光电避障',       type: 'bool',                desc: '光电开关避障检测',                      writable: true },
  { key: 'obstacle_sound',     label: '超声波避障',     type: 'bool',                desc: '超声波探头避障检测',                    writable: true },
  { key: 'obstacle_cancel_sec', label: '避障超时取消',  type: 'int',    unit: 's',   desc: '持续避障超过此时长自动取消巡检',       min: 10, max: 3600, step: 10, writable: true },

  // ── 环境传感器 ──
  { key: 'env_sensors',        label: '传感器列表',     type: 'json',                desc: 'JSON数组: [{\"model\":\"SHT30\",\"dev\":\"/dev/ttyUSB0\",\"baud\":9600}]', writable: true },
  { key: 'print_env_sensor',   label: '打印原始数据',   type: 'bool',                desc: '打印传感器原始 HEX 数据 (调试)',        writable: true },

  // ── 网络 ──
  { key: 'server',              label: '业务服务器',    type: 'string',              desc: 'FMS 主服务器地址',                      writable: true },
  { key: 'oss',                 label: '文件服务器',    type: 'string',              desc: 'OSS 上传地址',                          writable: true },
  { key: 'board_addr',          label: '下位机地址',    type: 'string',              desc: 'MCU 底盘控制板地址',                    writable: true },

  // ── 调试 ──
  { key: 'log_level',           label: '日志级别',      type: 'select',              desc: '运行日志输出级别',                       options: [{ label: 'DEBUG', value: 0 }, { label: 'INFO', value: 1 }, { label: 'WARN', value: 2 }, { label: 'ERROR', value: 3 }], writable: true },
  { key: 'log_days',            label: '日志保留天数',  type: 'int',    unit: '天',  desc: '自动清理 N 天前的日志',                  min: 1, max: 365, step: 1, writable: true },
  { key: 'log_max_size',        label: '单文件上限',    type: 'int',    unit: 'MB',  desc: '单个日志文件最大大小',                   min: 1, max: 100, step: 1, writable: true },
  { key: 'bt_trace',            label: '行为树追踪',    type: 'bool',               desc: '打印行为树执行轨迹',                     writable: true },
  { key: 'groot',               label: 'Groot可视化',   type: 'bool',               desc: '行为树在 Groot 中实时查看',              writable: true },

  // ── 故障恢复 ──
  { key: 'reboot_enable',       label: '自动重启',      type: 'bool',               desc: '启用定时自动重启',                       writable: true },
  { key: 'reboot_timeout_sec',  label: '重启超时',      type: 'int',   unit: 's',   desc: '无响应多久后自动重启',                   min: 3600, max: 864000, step: 3600, writable: true },
]

// ===== 分类树 =====
export const configCategories: ConfigCategory[] = [
  { key: 'motion',   label: '运动/速度',     fields: ['move_speed', 'angular_speed', 'director', 'is_ring'] },
  { key: 'limit',    label: '限位/轨道',     fields: ['limit_x0', 'limit_x1'] },
  { key: 'inplace',  label: '到位容差',      fields: ['inplace.distance', 'inplace.angle', 'inplace.duration'] },
  { key: 'home',     label: 'Home点',        fields: ['home.x', 'home.y'] },
  { key: 'battery',  label: '电池/电源',     fields: ['battery.low', 'battery.normal', 'battery.low_voltage', 'battery.charge_full_current', 'battery.charge_full_voltage'] },
  { key: 'ptz',      label: '云台/相机',     fields: ['ptz.addr', 'realtime_thermal'] },
  { key: 'lift',     label: '升降杆/电梯',   fields: ['with_lift', 'lift_limit', 'lift_speed', 'elevator.enable'] },
  { key: 'sensor',   label: '传感器',        fields: ['obstacle_light', 'obstacle_sound', 'obstacle_cancel_sec', 'env_sensors', 'print_env_sensor'] },
  { key: 'network',  label: '网络/服务',     fields: ['server', 'oss', 'board_addr'] },
  { key: 'debug',    label: '调试/日志',     fields: ['log_level', 'log_days', 'log_max_size', 'bt_trace', 'groot'] },
  { key: 'recovery', label: '故障恢复',      fields: ['reboot_enable', 'reboot_timeout_sec'] },
]

// 辅助函数
export function getField(key: string): ConfigField | undefined {
  return configFields.find(f => f.key === key)
}
