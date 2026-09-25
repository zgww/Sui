# 巡检计划与航点绑定下沉

## 职责与接口映射
旧 Java/Vue 保持维护，不改数据库、不双写。FMS 使用自己的机器人主键、地图/航点/动作主键和测点字符串 ID。

| 旧入口 | FMS 目标 | 职责 |
|---|---|---|
| task/getTaskListByRobotId、createTask2、updateTask、updateTaskStatus | /api/inspection-plans | 本地持久化计划、启停、周期和测点选择 |
| task/executeTask2、getTaskHistory、getTaskListByDate | 计划执行、历史和日历接口 | 保存计划不下发；显式执行或到期调度才创建执行记录 |
| steerPointsPoints/pointsListBySteerPoinnts、saveSteerPointsPointsNew、removeSteerPointsPoints | /api/point-archive/bindings 与 binding-options | 复用 PointBinding，按机器人/航点查询，批量原子绑定及解绑 |

旧平台通过 TaskVo 定义周期、日期、星期和测点，通过任务服务持久化后独立执行。FMS 原有 POST /inspection/tasks 会立即调用 cmd=100，不能作为保存计划接口。新计划须独立存储，执行复用既有设备协议及任务快照，不能把 Python 字典字符串当作设备内容。

## 验收要求
- 两页面使用顶部 selectedRid；切换机器人清空旧选择、关闭编辑弹窗，忽略旧请求结果。
- 航点和动作从本地航点管理读取；绑定实时复用测点档案关系。支持搜索、分页、绑定/解绑，拒绝停用测点、跨机器人目标、错误动作和重复关系。批量失败不能部分落库。
- 计划支持新增、编辑、删除、启停、立即执行、单次/每日/每周排期、日历和执行历史。名称、有效日期、时区、星期、检测点必须校验。
- 计划引用保护测点，执行保存不可变的测点及绑定快照。执行状态区分已保存、下发中、成功接受、失败/结果未知，不把接受命令视为巡检完成。
- 重复请求和调度竞争不得重复下发；离线、忙碌、失效绑定明确报错。调度恢复策略及协议按实际代码验证后记录。
- 工程师写权限，运维读取遵循现有接口权限；配置保存和浏览不触发真实设备控制。
- 原有下沉静态示例数据退出这两个页面，不显示虚假的成功、统计或报表。

## 发布与回退
使用隔离 SQLite、JSON 与模拟 robot_api 验证。发布到 192.168.6.88 前备份 SQLite/档案与 compose 镜像配置；仅新增表及可兼容列。回退镜像时先停用新调度器，保留新数据备份。现场真实巡检需单独联调，不以构建或模拟通过代替。

## 已实现的调度与协议约定
- 用户确认采用 FMS 本地调度。支持手动、单次、每日、每周；时区默认 Asia/Shanghai，星期 0–6 对应周一至周日。持久化时间为 UTC，界面按浏览器本地时区展示。
- 每 15 秒扫描排期，容错窗口 5 分钟。超窗排期记为 skipped，继续计算下次；不会集中补发停机期间任务。
- 每次执行先提交唯一的 `(plan_id, request_key)`、机器人占用、InspectionTask/InspectionRun 和不可变档案/绑定快照，再进行设备调用。保存/编辑配置不下发。
- cmd=102 确认设备状态，只有无当前任务或状态 -1/1 时才发送 cmd=100。内容最初参考旧平台 `Common/.../Cmd100DTO.java`、`NavSocket/.../Cmd100.java`，现按 Straitbot API V2.1.7 适配：content 为 JSON 字符串，包含 plan/id/name/waypoint；延时动作使用 action_delay_msec，不发送旧平台数据库键 substationMapsId。详见 `INSPECTION-IMMEDIATE-API.md`。
- Waypoint.wp_id 作为外部航点 ID，空值回退其主键字符串；动作 ID 与地图 ID 使用 FMS 本地主键字符串。编排保留航点 index 和动作 seq 的顺序；同一地图外部航点 ID 重复则拒绝执行。
- 测点与整个航点绑定时包含全部动作，与特定动作绑定时仅包含选择的动作。多个测点共用动作只下发一次。检测动作参数仍来自已有航点管理，不复制旧平台告警模板/算法数据库。
- HTTP 成功仅为 accepted，不等同于巡检完成。cmd=103 状态上报及每 30 秒 cmd=102 核对更新实际状态；上传结束本身不释放机器人占用。已终态不被迟到的开始消息回退。
- 下发超时为 unknown，不自动重发。崩溃后遗留的 dispatching 在核对后转为待确认。工程师可核对状态，只有设备确认空闲后才允许关闭本地占用；关闭不冒充完成。
- 删除计划为软删除，停止未来排期，保留执行记录，不取消已下发任务。动作控制继续复用巡检任务页，传输新任务的全局执行 ID。
- 新增四张表：inspection_plans、inspection_plan_points、inspection_plan_executions、inspection_robot_leases。已有 JSON 和原表数据不转换。

## 现场启用顺序
1. 在顶部选择机器人，在“航点管理”建立/导入地图、航点和动作。
2. 在测点档案确认测点检测类型及配置，启用需要执行的测点。
3. 在“航点绑定测点（下沉）”选择航点，按需指定动作，批量绑定测点。
4. 新建计划，选地图和已绑定测点，设置排期；默认停用。确认现场具备执行条件后启用。
5. 通过日历查看排期，通过执行历史查看下发/完成/失败/待确认状态。真实设备联调需核对坐标、动作参数和上报地址。
