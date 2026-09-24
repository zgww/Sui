# Straitbot FMS 架构文档

> 版本: v2.0 | 更新: 2026-07-22 | 状态: 架构设计

## 1. 系统概述

Straitbot FMS 是面向 Straitbot 巡检机器人的运维管理平台, 支持:
- **服务器模式**: 一台服务器管理多台机器人(车队)
- **工控机模式**: 部署到机器人本机, 手机直连使用

两种模式共用一套代码, 通过 `FMS_MODE` 环境变量切换。

### 1.1 技术栈

| 层 | 技术 | 版本 |
|---|---|---|
| 后端 | Python + FastAPI | 3.11 / 0.111 |
| 前端 | Vue3 + Element Plus + Vite | 3.4 / 2.7 / 5.2 |
| 数据库 | SQLite (SQLAlchemy ORM) | 单文件, 可移植 |
| 调度 | APScheduler | 定时轮询 |
| SSH | paramiko | 日志拉取 / OTA / 热点 |
| AI | OpenAI/Anthropic 兼容协议 | DeepSeek / GLM-5.2 |
| 部署 | Docker Compose | 兼容 Docker 18.09+ |

### 1.2 部署模式

```
模式 A — 服务器模式 (FMS_MODE=server, 默认)
┌──────────┐         ┌──────────────────────┐
│  手机/PC  │────────→│  服务器 (FMS)         │
│  浏览器   │  HTTP   │  frontend + backend   │
└──────────┘         └─────────┬────────────┘
                               │ SSH/HTTP
                    ┌──────────┼──────────┐
                    ▼          ▼          ▼
                机器人A     机器人B     机器人C

模式 B — 工控机模式 (FMS_MODE=robot)
┌──────────┐  WiFi    ┌──────────────────────┐
│  手机     │──AP────→│  机器人 (FMS + 机器人程序)│
│  浏览器   │         │  frontend + backend   │
└──────────┘         │  + robot 本体程序      │
                     └──────────────────────┘
                     (localhost 通信, 无需跨网络)
```

### 1.3 数据规模

| 指标 | 值 |
|---|---|
| 机器人数量 | ≤ 10 台 |
| 数据保留 | 1 个月 |
| 状态采样 | 10s / 台 → 8,640 条/天/台 → 86,400 条/天(10台) → 260 万条/月 |
| 存储 | 工控机 256G / 服务器 512G |
| 数据库 | SQLite, 时序按月分表 |

---

## 2. 物模型 (Thing Model)

物模型是对机器人的标准化抽象, 所有数据交互都基于物模型。

### 2.1 模型结构

```
Straitbot 物模型
│
├── properties (属性 — 持续上报, 只读)
│   ├── identity         身份信息
│   │   ├── sn               string   序列号
│   │   ├── robot_id         int      本体 ID
│   │   ├── product_type     int      0室内挂轨/1室外挂轨/2Mini/3室内轮式/4室外轮式
│   │   └── name             string   平台侧名称
│   │
│   ├── version          版本 (变更时快照)
│   │   ├── application       string   上位机程序版本
│   │   ├── firmware          string   下位机固件版本
│   │   ├── hardware          string   硬件版本
│   │   ├── hardware_sn       string   硬件序列号
│   │   ├── motion            string   运动模块版本
│   │   └── sdk               string   SDK 版本
│   │
│   ├── runtime          运行状态 (10s 上报, cmd=20/21)
│   │   ├── status           int      状态 ID (见状态表)
│   │   ├── doing            string   正在做的事
│   │   ├── cpu              float    CPU 使用率 %
│   │   ├── temperature      float    CPU 温度 °C
│   │   ├── speed            float    当前速度 m/s
│   │   ├── angular_speed    float    角速度 °/s
│   │   ├── battery          int      电量 %
│   │   ├── pose             object   { x, y, theta }
│   │   └── floor            int      当前楼层
│   │
│   ├── power            电源 (60s 上报, cmd=22)
│   │   ├── mode             int      0 电池 / 1 外接
│   │   ├── voltage          float    电压 V
│   │   ├── current          float    电流 A
│   │   ├── capacity         int      容量 %
│   │   ├── remaining        int      剩余 %
│   │   └── charging         int      是否充电中
│   │
│   ├── connections       连接状态
│   │   ├── chassis           bool     下位机
│   │   ├── server            bool     主服务器
│   │   └── elevator          bool     电梯
│   │
│   └── ptz              云台位姿 (cmd=35/39)
│       ├── pan              float    水平角度
│       ├── tilt             float    垂直角度
│       ├── zoom             float    变倍
│       ├── focus            int      对焦
│       └── focal_len        int      焦距
│
├── configs (配置 — 可读可写, cmd=4/5)
│   ├── motion           运动参数
│   │   ├── move_speed          float    行进速度 m/s
│   │   ├── angular_speed       float    角速度 °/s
│   │   ├── is_ring             bool     环形轨道
│   │   └── limit_position      object   { x:[min,max], y:[min,max] }
│   │
│   ├── battery          电池阈值
│   │   ├── low                int      低电量阈值 %
│   │   ├── normal             int      恢复正常 %
│   │   ├── low_voltage        float    低电压阈值
│   │   └── charge_full_current float   满电充电电流
│   │
│   ├── home_pose        Home 点
│   │   ├── x, y, theta
│   │
│   ├── inplace_tolerance 到位容差
│   │   ├── distance            float    距离容差 m
│   │   ├── angle               float    角度容差 °
│   │   └── duration            int      时间容差 ms
│   │
│   ├── ptz              云台配置
│   │   ├── addr                string   地址
│   │   └── model               string   型号
│   │
│   └── lift             升降杆
│       ├── speed              float    速度 m/s
│       └── limit              object   { min, max }
│
├── services (服务 — 可调用, 有返回)
│   ├── motion
│   │   ├── move(command, instant_speed)         # cmd=32 运动控制
│   │   ├── setPose(point, theta, ptz)           # cmd=31 设定位姿
│   │   ├── resetAndHome(go_home)                # cmd=33 复位返航
│   │   ├── emergencyStop(action)                # cmd=51 急停(挂轨)
│   │   └── getPose()                            # cmd=30 获取位姿
│   │
│   ├── ptz
│   │   ├── getPose()                            # cmd=35
│   │   ├── setPose(pan, tilt, zoom)             # cmd=36
│   │   ├── action(command, stop, channel)       # cmd=37
│   │   └── capture(command, duration)           # cmd=38 拍照/录像/测温
│   │
│   ├── lift
│   │   ├── getStatus()                          # cmd=40
│   │   └── control(command, height)             # cmd=41
│   │
│   ├── power
│   │   ├── getInfo()                            # cmd=22
│   │   └── charge(action, pile_index)           # cmd=23
│   │
│   ├── inspection
│   │   ├── create(file/content, schedule)       # cmd=100
│   │   ├── control(action, target)              # cmd=101
│   │   └── getInfo(inspection_id)               # cmd=102
│   │
│   ├── map
│   │   ├── control(type, x_begin, x_end)        # cmd=90
│   │   ├── getProgress()                        # cmd=91
│   │   └── getLabels(type, floor)               # cmd=93
│   │
│   ├── elevator
│   │   ├── call(floor)                          # cmd=130
│   │   └── takeFloor(floor, ctrlType, comeOut)  # cmd=132
│   │
│   ├── audio.play(command, file)                # cmd=47
│   ├── pdd.detect(command)                      # cmd=48 局放
│   ├── selfcheck.start() / getResult()          # cmd=7/8
│   ├── alert.list() / clearNav() / clearDriver() # cmd=10/12/13
│   └── raw(cmd, data)                           # 透传
│
├── events (事件 — 机器人主动推送)
│   ├── alert.changed         告警变化 (cmd=11)
│   ├── status.changed        状态变化 (cmd=20)
│   ├── pose.adjusted         位姿调整结果 (cmd=29)
│   ├── ptz.changed           云台位姿 (cmd=39)
│   ├── lift.changed          升降杆 (cmd=42)
│   ├── env.changed           环境数据 (cmd=46)
│   ├── inspection.status     巡检状态 (cmd=103)
│   ├── inspection.result     巡检结果 (cmd=104)
│   ├── inspection.progress   巡检进度 (cmd=106)
│   ├── device.status         设备状态 (cmd=107)
│   └── robot.event           机器人事件 (cmd=138)
│
└── history (历史 — 平台侧存储)
    ├── status_logs            状态时序 (按月分表)
    ├── power_logs             电源时序
    ├── alert_history          告警记录
    ├── version_history        版本变更
    ├── config_history         配置变更
    ├── inspection_history     巡检记录
    └── ota_history            OTA 记录
```

### 2.2 状态 ID 映射

| ID | 说明 |
|---|---|
| 0 | 默认, 正常运行 |
| 1 | 开始充电 |
| 2 | 充电中 |
| 3 | 前往充电 |
| 4 | 自检中 |
| 5 | 巡检中/正在巡检 |
| 6 | 巡检已暂停 |
| 7 | 巡检已挂起 |
| 8 | 前往电梯口 |

### 2.3 物模型存储

物模型定义存为 JSON 文件, 支持 UI 编辑:

```
backend/data/thing_model.json
```

```json
{
  "product_types": {
    "0": "室内挂轨",
    "1": "室外挂轨",
    "2": "Mini挂轨",
    "3": "室内轮式",
    "4": "室外轮式"
  },
  "status_map": {
    "0": "正常运行",
    "1": "开始充电",
    ...
  },
  "properties": {
    "runtime.battery": { "type": "int", "unit": "%", "desc": "电量" },
    "runtime.cpu": { "type": "float", "unit": "%", "desc": "CPU使用率" },
    ...
  },
  "alerts": {
    "20001": "嵌入式板未连接",
    "20105": "电量低",
    ...
  }
}
```

---

## 3. 数据库设计

### 3.1 存储策略

| 数据类型 | 存储 | 生命周期 |
|---|---|---|
| 配置/账号/任务 | SQLite 主表 | 永久 |
| 状态/电源时序 | SQLite 月分表 | 1 个月自动清理 |
| 巡检结果文件 | 文件系统 | 按 retention 配置 |
| 日志文件 | 文件系统 | 按机器人 retention |

### 3.2 表清单

```sql
-- ========== 基础 ==========
users(id, username, pwd_hash, role, enabled, created_at)
robots(id, name, robot_id, ip, api_port, product_type,
       ssh_user, ssh_pass, ssh_port,
       log_dir, install_dir, version_file,
       poll_status, poll_meta, log_retention_days,
       enabled, note, created_at, updated_at)

-- ========== 物模型快照 ==========
robot_properties(
  robot_pk FK, sn, product_type,
  -- runtime
  status, doing, cpu, temperature, speed, angular_speed,
  battery, pose_x, pose_y, theta, floor,
  -- power
  power_mode, voltage, current, capacity, remaining, charging,
  -- connections
  conn_chassis, conn_server, conn_elevator,
  -- ptz
  ptz_pan, ptz_tilt, ptz_zoom,
  -- version
  app_version, fw_version, hw_version, motion_version, sdk_version,
  -- meta
  last_seen, updated_at,
  PRIMARY KEY(robot_pk)
)

-- ========== 时序(按月分表) ==========
status_logs_YYYYMM(
  id, robot_pk, ts, status, doing, cpu, temperature,
  speed, angular_speed, battery, pose_x, pose_y, theta, floor,
  conn_chassis, conn_server, conn_elevator
)
power_logs_YYYYMM(
  id, robot_pk, ts, mode, voltage, current, capacity, remaining, charging
)

-- ========== 事件 ==========
alerts(id, robot_pk, ts, alert_id, content, level, params, resolved)
config_snapshots(id, robot_pk, ts, source, operator, config_json)
version_history(id, robot_pk, ts, application, firmware, hardware, motion, sdk)

-- ========== OTA ==========
ota_packages(id, filename, version, product_type, channel, size, md5, notes, force_flag, created_at, created_by)
ota_tasks(id, robot_pk, package_id, from_version, to_version, force, status, log, started_at, finished_at, created_at, created_by)

-- ========== 日志 ==========
uploaded_logs(id, robot_pk, filename, stored_path, size, source, created_at)
fetched_logs(id, robot_pk, remote_path, stored_path, filename, size, fetched_at, fetched_by)

-- ========== 巡检 (框架, 结构待定) ==========
inspection_tasks(id, robot_pk, name, plan_json, schedule_json, status, created_at, updated_at)
inspection_runs(id, task_id FK, robot_pk, inspection_id, status, start_time, finish_time, remark)
inspection_results(id, run_id FK, waypoint_id, action_id, code, picture, infrared, media, thermometry_json, env_json, pdd_json)

-- ========== 设置 ==========
settings(key PK, value)
```

### 3.3 分表策略

```python
# poller.py 写入时自动按月建表
TABLE = f"status_logs_{datetime.now().strftime('%Y%m')}"
# 例: status_logs_202607

# log_retention.py 清理时删旧月表
# 保留最近 N 个月的表
```

---

## 4. 代码模块划分

### 4.1 后端目录

```
backend/app/
├── main.py                    # 入口: 注册 router + 启动调度
├── config.py                  # 配置(FMS_MODE / .env)
├── database.py                # 引擎 + 会话 + 分表工具
│
├── core/                      # 核心层(跨模块)
│   ├── auth.py                # 鉴权 + RBAC
│   ├── deps.py                # 公共依赖(get_robot / get_db)
│   └── errors.py              # 统一异常
│
├── thing_model/               # ★ 物模型层
│   ├── definition.py          # 模型定义(从 thing_model.json 加载)
│   ├── mapper.py              # API 响应 → 物模型字段映射
│   └── accessor.py            # 物模型读写(fetch + save)
│
├── models/                    # ORM(按领域)
│   ├── __init__.py
│   ├── user.py
│   ├── robot.py               # Robot + RobotProperty
│   ├── monitor.py             # StatusLog + PowerLog + Alert + VersionHistory
│   ├── ota.py
│   ├── log.py
│   ├── inspection.py          # 巡检(框架)
│   └── setting.py
│
├── schemas/                   # Pydantic(按领域)
│   ├── __init__.py
│   ├── robot.py
│   ├── monitor.py
│   ├── ota.py
│   ├── inspection.py
│   └── ai.py
│
├── services/                  # 业务服务层
│   ├── robot_api.py           # HTTP 客户端(按物模型 services 组织)
│   ├── ssh_client.py
│   ├── poller.py              # 轮询(走 thing_model.accessor)
│   ├── ai_analyzer.py
│   ├── ota_runner.py
│   ├── scanner.py
│   └── log_retention.py
│
├── routers/                   # HTTP 路由(按业务模块)
│   ├── __init__.py            # 统一注册
│   ├── auth.py
│   ├── robots.py
│   ├── scan.py
│   ├── monitor.py             # 状态 + 告警 + 历史
│   ├── logs.py
│   ├── ai.py
│   ├── ota.py
│   ├── config_robot.py
│   ├── cmd_debug.py
│   ├── hotspot.py
│   ├── settings.py
│   ├── thing_model.py         # ★ 物模型管理(UI 编辑)
│   ├── inspection/            # ★ 巡检(子路由组)
│   │   ├── __init__.py
│   │   ├── tasks.py
│   │   └── results.py
│   └── control/               # ★ 控制(子路由组)
│       ├── __init__.py
│       ├── motion.py
│       ├── ptz.py
│       ├── lift.py
│       └── camera.py
│
└── data/
    ├── fms.db
    ├── thing_model.json       # 物模型定义
    ├── prompts.json           # AI 模板 + 知识库
    ├── logs/<robot_pk>/
    └── packages/
```

### 4.2 前端目录

```
frontend/src/
├── views/
│   ├── foundation/
│   │   ├── Login.vue
│   │   ├── RobotList.vue       # 含扫描面板
│   │   ├── RobotDetail.vue
│   │   └── Settings.vue
│   ├── monitor/
│   │   ├── Dashboard.vue
│   │   ├── Alerts.vue
│   │   ├── LogCenter.vue
│   │   ├── LogsView.vue
│   │   ├── LogFetch.vue
│   │   └── LogUpload.vue
│   ├── control/
│   │   ├── MotionControl.vue
│   │   ├── PTZControl.vue
│   │   ├── LiftControl.vue
│   │   ├── CameraView.vue
│   │   ├── RobotConfig.vue
│   │   └── CmdDebug.vue
│   ├── business/
│   │   ├── InspectionCenter.vue   # 框架
│   │   ├── InspectionTasks.vue
│   │   ├── InspectionResults.vue
│   │   ├── MapCenter.vue
│   │   ├── ElevatorControl.vue
│   │   ├── Environment.vue
│   │   ├── OtaCenter.vue
│   │   └── Packages.vue
│   ├── ai/
│   │   ├── AiCenter.vue
│   │   ├── AiChat.vue
│   │   └── AiSettings.vue
│   └── admin/
│       └── ThingModel.vue         # ★ 物模型管理
├── api/
│   ├── http.js
│   ├── auth.js
│   ├── robots.js
│   ├── monitor.js
│   ├── control.js
│   ├── business.js
│   └── ai.js
├── components/
│   ├── RobotTabs.vue
│   └── StatusBadge.vue
├── layout/
│   └── MainLayout.vue
├── router/
│   └── index.js                # 按模块分组
├── store/
│   ├── user.js
│   └── mode.js
└── utils/
    └── md.js
```

### 4.3 侧栏菜单结构

```
📊 监控中心
   ├─ 监控大盘
   ├─ 告警中心
   └─ 日志中心

🎮 控制中心 (engineer)
   ├─ 运动控制
   ├─ 云台控制
   ├─ 升降杆
   ├─ 拍照测温
   ├─ 参数配置
   └─ 指令调试

📋 巡检中心 (engineer)
   ├─ 巡检任务
   └─ 巡检结果

🔧 系统管理 (engineer)
   ├─ 机器人列表
   ├─ OTA 中心
   ├─ 安装包管理
   ├─ 建图管理
   ├─ 电梯控制
   ├─ 环境监测
   ├─ AI 中心
   ├─ 物模型管理
   └─ 系统设置
```

---

## 5. 数据流

### 5.1 轮询数据流(物模型)

```
APScheduler (10s)
    │
    ▼
poller.tick_status()
    │
    ▼
thing_model.accessor.fetch_runtime(robot)
    │
    ├──→ robot_api.get_status(ip, port, robot_id)   # HTTP cmd=21
    │       ↓
    │     raw JSON
    │       ↓
    ├──→ thing_model.mapper.map_runtime(raw)
    │       ↓
    │     RuntimeProperties 对象
    │       ↓
    ├──→ accessor.save(robot, properties)
    │       ├──→ UPDATE robot_properties (最新快照)
    │       └──→ INSERT status_logs_YYYYMM (时序)
    │
    └──→ done
```

### 5.2 控制指令流

```
前端 POST /api/control/{rid}/motion/move
    │
    ▼
routers.control.motion.move(rid, command)
    │
    ▼
robot_api.motion.move(ip, port, robot_id, command)
    │
    ▼
HTTP POST http://{ip}:{port}/  body={"cmd":32,"command":N}
    │
    ▼
机器人执行 → 返回 {code:0, msg:"Ok"}
    │
    ▼
返回前端
```

### 5.3 AI 对话流(含知识库)

```
前端 POST /api/ai/chat {history, question}
    │
    ▼
routers.ai.chat_ai()
    │
    ├──→ 读取 thing_model.json 知识库
    ├──→ 读取 prompts.json 自定义知识
    │
    ▼
ai_analyzer.analyze_stream(knowledge=full_knowledge)
    │
    ├──→ Anthropic: httpx POST /v1/messages (SSE stream)
    ├──→ OpenAI:    openai SDK stream
    │
    ▼
yield text chunks → SSE → 前端流式渲染
```

---

## 6. API 设计规范

### 6.1 URL 规范

```
GET    /api/{module}/{resource}           列表
POST   /api/{module}/{resource}           创建
GET    /api/{module}/{resource}/{id}      详情
PUT    /api/{module}/{resource}/{id}      更新
DELETE /api/{module}/{resource}/{id}      删除
POST   /api/{module}/{resource}/{id}/{action}  动作
```

### 6.2 模块前缀

| 模块 | 前缀 | 示例 |
|---|---|---|
| 鉴权 | /api/auth | /api/auth/login |
| 机器人 | /api/robots | /api/robots, /api/robots/1/ping |
| 扫描 | /api/scan | /api/scan, /api/scan/add |
| 监控 | /api/monitor | /api/monitor/1/status |
| 控制 | /api/control | /api/control/1/motion/move |
| 巡检 | /api/inspection | /api/inspection/tasks |
| 日志 | /api/logs | /api/logs/1/archived |
| OTA | /api/ota | /api/ota/packages |
| AI | /api/ai | /api/ai/chat |
| 物模型 | /api/thing-model | /api/thing-model |
| 设置 | /api/settings | /api/settings/info |

### 6.3 统一响应

```json
// 成功
{ "ok": true, "msg": "ok", "data": {...} }

// 失败 (HTTP 4xx/5xx)
{ "detail": "错误描述" }
```

---

## 7. 模式切换 (server / robot)

### 7.1 配置

```bash
# .env
FMS_MODE=server    # server | robot
```

### 7.2 行为差异

| 行为 | server 模式 | robot 模式 |
|---|---|---|
| 启动时 | 加载所有机器人 | 自动注册 localhost 机器人 |
| 扫描发现 | ✅ 可用 | ❌ 隐藏 |
| 机器人列表 | 可增删改 | 锁定本机(只读) |
| 轮询 | 轮询所有启用的机器人 | 只轮询 localhost |
| OTA | 可推送到任意机器人 | 只能升本机 |
| UI 菜单 | 完整 | 简化(隐藏扫描/多机管理) |

### 7.3 前端切换

```javascript
// store/mode.js
const mode = ref('server')  // 从 /api/settings/info 获取

// MainLayout.vue
const menuItems = computed(() => {
  if (mode.value === 'robot') {
    return allMenuItems.filter(item => !item.serverOnly)
  }
  return allMenuItems
})
```

---

## 8. 实施路线

| 步骤 | 内容 | 预计 | 依赖 |
|---|---|---|---|
| 1 | 架构文档(本文档) | ✅ 完成 | - |
| 2 | 物模型定义文件 thing_model.json | 小 | 1 |
| 3 | 代码模块化拆分(models/schemas/routers) | 中 | 2 |
| 4 | 物模型层(thing_model/mapper/accessor) | 中 | 2,3 |
| 5 | 轮询改造(走物模型) | 小 | 4 |
| 6 | 时序分表 + 自动清理 | 小 | 5 |
| 7 | 物模型管理 UI | 中 | 4 |
| 8 | 控制模块(运动/云台/升降杆/拍照) | 大 | 3 |
| 9 | 巡检框架(表+路由+空页面) | 中 | 3 |
| 10 | FMS_MODE 模式切换 | 小 | 3 |
| 11 | PWA 安装优化 | 小 | - |

每步完成后部署到 6.54 验证, 不影响现有功能。

---

## 9. 约定

### 9.1 命名

- 后端: snake_case (Python)
- 前端: camelCase (JS) / PascalCase (Vue 组件)
- 数据库: snake_case, 复数表名
- API: kebab-case URL

### 9.2 版本

- 遵循语义化版本: MAJOR.MINOR.PATCH
- VERSION 文件为唯一来源
- 打包时 pack.sh 写入 RELEASE_NOTES.md

### 9.3 安全

- API Key / SSH 密码 仅存数据库, 不入日志
- JWT 密钥在 .env 配置
- AI 对话内容发送给配置的 AI 服务商
- 工控机模式下默认密码必须修改
