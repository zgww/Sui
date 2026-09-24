# 菜单规格文档 (Menu Specification)

> 用途: 这是我们沟通"菜单怎么改"的共同语言。你想新增/调整/隐藏菜单时, 对照本文档描述, 我就能准确实施。

## 1. 菜单结构总览

侧栏菜单分为 **5 大组**, 每组下若干菜单项。每项有: 图标、标题、路由、角色权限、模式限制。

```
📊 监控中心 (所有角色)
   ├─ 监控大盘        /dashboard          icon=Monitor
   ├─ 告警中心        /alerts             icon=WarningFilled
   └─ 日志中心        /logs               icon=Document
                                        ├─ Tab: 日志查看
                                        ├─ Tab: 在线拉日志 (engineer)
                                        └─ Tab: 日志上传 (engineer)

🎮 控制中心 (仅 engineer)
   ├─ 运动控制        /control/motion     icon=Position
   ├─ 云台控制        /control/ptz        icon=VideoCamera
   ├─ 升降杆          /control/lift       icon=Sort
   ├─ 拍照测温        /control/camera     icon=Camera
   ├─ 参数配置        /control/config     icon=Setting
   └─ 指令调试        /control/debug      icon=Tools

📋 巡检中心 (仅 engineer)
   ├─ 航点管理        /waypoints         icon=MapLocation
   ├─ 巡检任务        /inspection/tasks   icon=List
   └─ 巡检结果        /inspection/results icon=Files

🔧 系统管理 (仅 engineer)
   ├─ 机器人列表      /robots             icon=Cpu
   ├─ OTA 中心        /ota                icon=Promotion
   ├─ 安装包管理      /packages           icon=Box
   ├─ 建图管理        /map                icon=MapLocation
   ├─ 电梯控制        /elevator           icon=OfficeBuilding
   ├─ 环境监测        /environment        icon=Odometer
   ├─ AI 中心         /ai-center          icon=MagicStick
   ├─ 物模型管理      /thing-model        icon=Operation
   └─ 系统设置        /settings           icon=Setting

👤 账号 (右上角下拉)
   └─ 退出登录
```

## 2. 菜单项属性定义

每个菜单项有如下属性, 定义在 `frontend/src/router/index.js` 的 `meta` 字段:

| 属性 | 类型 | 说明 | 示例 |
|---|---|---|---|
| `title` | string | 菜单显示文字 | `"监控大盘"` |
| `icon` | string | Element Plus 图标名 | `"Monitor"` |
| `roles` | array\|null | 允许访问的角色。`null`=所有登录用户 | `['engineer']` / `null` |
| `mode` | string\|null | 仅在指定模式显示。`null`=两种模式都显示 | `'server'` / `'robot'` / `null` |
| `group` | string | 所属分组 | `"监控中心"` |
| `hidden` | bool | 是否在菜单隐藏(详情页等) | `true` |
| `order` | int | 组内排序(数字越小越靠前) | `10` |

## 3. 角色权限

| 角色 | role 值 | 能看到的菜单 |
|---|---|---|
| 工程师 | `engineer` | 全部(5 组) |
| 运维 | `operator` | 仅"监控中心"组 |

## 4. 模式限制 (server / robot)

| 菜单项 | server 模式 | robot 模式 | 说明 |
|---|---|---|---|
| 机器人列表 | ✅ 完整 CRUD + 扫描 | ✅ 但锁定为"本机"只读 | robot 模式不能添加/删除 |
| 扫描发现面板 | ✅ | ❌ 隐藏 | robot 模式只有本机 |
| OTA 中心 | ✅ 可选任意机器人 | ✅ 但只有"本机"可选 | |
| 其他菜单 | ✅ | ✅ | 不受模式影响 |

## 5. 如何沟通菜单变更

### 场景 A: 新增菜单项

**你说**: "在控制中心加一个'门器控制', 图标用钥匙, 只有工程师能看到"

**我需要的信息**:
- 所属组: 控制中心
- 标题: 门器控制
- 图标: 钥匙(或你说"合适就行", 我选)
- 角色: engineer
- 对应页面做什么(简述功能)
- 调用什么 API(cmd 号)

### 场景 B: 调整菜单顺序

**你说**: "把'告警中心'移到'机器人列表'下面"

**我需要的信息**:
- 哪个菜单项
- 移到哪个位置(目标菜单项的上面/下面)

### 场景 C: 隐藏/删除菜单

**你说**: "工控机模式下隐藏'扫描发现'和'机器人列表'"

**我需要的信息**:
- 哪些菜单项
- 什么条件下隐藏(模式/角色)

### 场景 D: 修改名称/图标

**你说**: "把'OTA 中心'改名叫'升级管理', 图标换成 Upload"

**我需要的信息**:
- 原名 → 新名
- 新图标(Element Plus 图标名, 或你说"合适就行")

### 场景 E: 新增菜单分组

**你说**: "加一个'报表中心'分组, 里面放巡检报表、告警统计"

**我需要的信息**:
- 分组名称
- 分组下的菜单项列表
- 分组排列位置(在哪两组之间)

## 6. 快速参考: 当前所有菜单项

| # | 组 | 标题 | 路由 | 图标 | 角色 | 模式 |
|---|---|---|---|---|---|---|
| 1 | 监控中心 | 监控大盘 | /dashboard | Monitor | 所有 | 通用 |
| 2 | 监控中心 | 告警中心 | /alerts | WarningFilled | 所有 | 通用 |
| 3 | 监控中心 | 日志中心 | /logs | Document | 所有 | 通用 |
| 4 | 控制中心 | 运动控制 | /control/motion | Position | engineer | 通用 |
| 5 | 控制中心 | 云台控制 | /control/ptz | VideoCamera | engineer | 通用 |
| 6 | 控制中心 | 升降杆 | /control/lift | Sort | engineer | 通用 |
| 7 | 控制中心 | 拍照测温 | /control/camera | Camera | engineer | 通用 |
| 8 | 控制中心 | 参数配置 | /control/config | Setting | engineer | 通用 |
| 9 | 控制中心 | 指令调试 | /control/debug | Tools | engineer | 通用 |
| 10 | 巡检中心 | 航点管理 | /waypoints | MapLocation | engineer | 通用 |
| 11 | 巡检中心 | 巡检任务 | /inspection/tasks | List | engineer | 通用 |
| 12 | 巡检中心 | 巡检结果 | /inspection/results | Files | engineer | 通用 |
| 13 | 系统管理 | 机器人列表 | /robots | Cpu | engineer | 通用 |
| 14 | 系统管理 | OTA 中心 | /ota | Promotion | engineer | 通用 |
| 15 | 系统管理 | 安装包管理 | /packages | Box | engineer | 通用 |
| 16 | 系统管理 | 建图管理 | /map | MapLocation | engineer | 通用 |
| 17 | 系统管理 | 电梯控制 | /elevator | OfficeBuilding | engineer | 通用 |
| 18 | 系统管理 | 环境监测 | /environment | Odometer | engineer | 通用 |
| 19 | 系统管理 | AI 中心 | /ai-center | MagicStick | engineer | 通用 |
| 20 | 系统管理 | 物模型管理 | /thing-model | Operation | engineer | 通用 |
| 21 | 系统管理 | 系统设置 | /settings | Setting | engineer | 通用 |

## 7. 实现位置

菜单定义在代码中的位置:
- **路由+菜单**: `frontend/src/router/index.js`
- **侧栏渲染**: `frontend/src/layout/MainLayout.vue` + `components/Sidebar.vue`
- **角色过滤**: `Sidebar.vue` 中 `meta.roles` 判断
- **模式过滤**: `store/mode.js` + `Sidebar.vue` 中 `meta.mode` 判断

## 8. 图标参考

使用 Element Plus 图标库: https://element-plus.org/zh-CN/component/icon.html

常用图标:
- 监控类: Monitor, Odometer, View, DataLine
- 控制类: Position, VideoCamera, Camera, Sort, Setting, Tools
- 管理类: Cpu, Box, Promotion, Document, WarningFilled
- 导航类: House, Menu, Search, ArrowDown
- AI 类: MagicStick, ChatDotRound
