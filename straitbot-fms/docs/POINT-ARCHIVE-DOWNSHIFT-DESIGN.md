# 测点档案下沉：JSON 存储与查询方案

日期：2026-09-17。状态：方案评估，尚未实现业务接口。用户已确认单套 FMS 测点规模在 **1 万以内**，档案建立后低频修改。

## 1. 建议结论

采用 **JSON 持久化基本档案 + 后端进程内索引查询 + 既有 SQLite 保存运行数据和关联关系**。

在上述规模和低频写入条件下，JSON 可行。查询请求不重新读取、解析整个文件：启动时加载一次并建立索引；发布新版本时校验并替换内存快照。按 ID、编码、设备查询用索引，名称包含查询先缩小范围再扫描。单文件 JSON 没有数据库索引，速度来自应用建立的内存索引，不能把文件格式等同于查询引擎。

一期使用一个逻辑快照文件，避免过早引入跨文件事务。真实数据扩大后再考虑按站分片；不按测点创建一万个小文件，也不将全部档案发到浏览器过滤。

## 2. 当前代码证据

| 来源 | 已确认行为 | 下沉影响 |
|---|---|---|
| `frontend/src/views/sink/PointArchive.tsx`、`data.ts` | 静态数组和示意弹窗；包含站/电压/间隔/设备/测点、模板及绑定展示 | 当前展示不是已经落库的档案，更不能将示例数值当真实容量 |
| 旧 `new-hxzh-admin/src/api/file_configuar/index.js` | 台账树分层加载 | 保留懒加载，不一次返回整棵测点树 |
| 旧 `RobotTaskManage/.../controller/PointController.java` | 详情、设备下分页、名称、编码、绑定状态筛选，以及巡检范围查询 | JSON 服务需要覆盖这些查询语义 |
| 旧 `RobotTaskManage/src/main/resources/mapper/PointMapper.xml` | 名称包含、编码精确；导航点与模板关联来自其他表 | 索引需要结合关系查询，不能把绑定标记当静态字段 |
| 旧 `RobotTaskManage/.../entity/Point.java`、`service/impl/PointServiceImpl.java` | `id` 是字符串；存在 6/9/12 位前缀截取；`isDelete=1` 有效、0 删除 | ID 原样保留，不能把层级编码转整数或重新编号；显式记录父关系 |
| `backend/app/thing_model/definition.py` | 已有 JSON + `lru_cache` 缓存模式 | 可借鉴加载模式，但不能复制“解析失败返回空字典”和直接覆盖写法 |
| `backend/app/models/waypoint.py`、`inspection.py` | 航点、动作、任务、执行和结果已用 SQLite | 复用已有数据归属，不重复建设 |

以上旧后端路径均相对 `../../hxzh-dev-3/backend/`。新版平台页面也须继续维护；本方案不删除 Java/Vue 能力。

## 3. 数据边界与职责

| 内容 | 推荐存储/归属 |
|---|---|
| 站点、间隔、设备、测点名称与编码、所属层级、检测类型、单位、默认检测次数、位置等基本配置 | 本次 JSON 档案 |
| 电压等级、检测类型等字典 | 快照内引用明确的字典代码；导入时带版本或必要定义 |
| 告警模板及克隆阈值 | 属于独立的告警配置能力；档案通过明确标识/版本关联，保留旧配置语义。本期不将其转换成测点实时属性 |
| 测点与航点/动作/机器人绑定、告警模板绑定 | SQLite 关系表（新接口尚需实现），关联稳定 `point_id`；“是否绑定”查询时计算 |
| 任务执行、检测结果、实时值、告警事件、更新时间序列 | 继续 SQLite，不随档案整体重写 |
| 图片、视频、音频、地图 | 文件/现有资源服务，JSON 只保存相对路径或资源标识，不内嵌 Base64 |

推荐首期：从平台导出一个档案快照，FMS 导入后由 FMS 负责本地使用和低频维护；再次导入必须预览差异并比较版本，不能默默覆盖本地修改。不建立自动双向同步或运行时直连旧平台数据库。需要平台持续作为主数据源时，改为“平台发布、FMS 只读”模式；两个写入模式不能同时开启。

## 4. JSON 结构

建议存储 `/app/data/point_archive/archive.json`（宿主机沿用已有 data 挂载），备份放同一持久化目录的 `revisions/`。通过鉴权 API 访问，不新增裸 JSON 静态下载入口。

使用扁平集合和显式父 ID，树由索引生成。示例为结构说明，不是生产数据：

```json
{
  "schema_version": 1,
  "revision": 1,
  "updated_at": "2026-09-17T18:00:00+08:00",
  "source": {"system": "legacy-platform", "export_revision": "export-001"},
  "stations": [{"id": "001001", "name": "示例站"}],
  "bays": [{"id": "001001001", "station_id": "001001", "voltage_level": "110kV", "name": "示例间隔"}],
  "equipment": [{"id": "001001001001", "bay_id": "001001001", "name": "主变压器"}],
  "points": [{
    "id": "001001001001001",
    "code": "PT-0001",
    "name": "油温表",
    "equipment_id": "001001001001",
    "assay_type": 1,
    "meter_type": 1,
    "times": 2,
    "scope": "0-150",
    "warn_setting": "",
    "active": true,
    "position": null,
    "source_id": "001001001001001",
    "extensions": {}
  }]
}
```

- ID、编码全程字符串，保留前导零。旧平台也有 UUID 注解；导入应验证真实 ID，不一律强制 15 位，更不从字符串长度推断全部关系。
- `isDelete=1` 映射 `active=true`，0 映射 false；其他异常值报导入错误，不能误判有效。
- 同一快照内 ID 唯一；编码重复返回候选项或按站限定精确查询，未证实全局唯一前不能用单值字典静默覆盖。
- 位置、枚举、阈值范围保留旧值及来源；未支持的扩展字段必须保留或明确拒绝，不能静默丢弃。
- 禁止导入悬空父关系、循环层级、重复 ID、非有限数值、未知 schema_version。JSON 标准重复键须在解析阶段检测。
- 首期限额建议 10,000 测点、32 MiB 上传体；都是应用保护与评审值，不是格式极限。示例附件不计入 JSON。

## 5. 查询设计

加载时建立 `by_id`、`by_code -> list[id]`、`by_equipment`、`by_station`、`by_bay`、`by_assay_type` 及父子节点索引；存引用/ID，避免复制整条测点。稳定排序为 `(code, id)`，规范为字符串排序。

| 查询 | 路径 | 主要代价 |
|---|---|---|
| ID 详情、运行中按点取配置 | 内存字典 | 平均 O(1)，运行任务固定一个 revision |
| 编码精确、设备/站/类型范围 | 对应索引候选集合 | 与命中记录数相关 |
| 名称包含 | 候选集合扫描；无条件时最多 1 万 | O(N)，可预计算 casefold 名称；首期不做全文索引 |
| 绑定状态/模板筛选 | SQLite 一次取所需 ID 集合，与档案候选集合求交 | 避免每点一次 SQL，即 N+1 查询 |
| 列表 | 筛选、total 计数后分页，默认 50、最大 200 | 只序列化当前页 |
| 树节点 | 按 parent/type 拉取一级，测点叶子也分页 | 不遍历返回整个档案 |

建议接口（均为待实现设计）：
- `GET /api/point-archive/meta`：revision、数量、来源、加载状态。
- `GET /api/point-archive/tree?parent_type=equipment&parent_id=...&page=1&page_size=50`。
- `GET /api/point-archive/points?equipment_id=...&name=...&code=...&bound=true&page=1&page_size=50`。
- `GET /api/point-archive/points/{id}`：不存在返回 404。
- `POST /api/point-archive/import/preview`：校验并返回变化/冲突列表，绝不写入。
- `PUT /api/point-archive/snapshot`：完整候选快照 + `If-Match` 当前 revision，通过校验后发布。
- `GET /api/point-archive/export`：授权导出完整版本。

响应分页结构 `{revision, total, page, page_size, items}`。页面续页携带 revision，版本已改变返回 409 让前端刷新。复用 `engineer_only` 与当前页面角色；运行任务由内部服务接口读取同一个档案仓储，不绕行 HTTP。

## 6. 低频修改仍需保证可靠性

一期部署约束：**单个 FMS 后端进程为唯一写入者**，不允许绕过 API 在线编辑 JSON。后续增加 Uvicorn worker 或多副本前，必须实现跨进程版本一致性，或切换 SQLite 主存储。

发布流程：解析/大小限制 → 类型与引用校验 → 获取写锁 → 重新校验 If-Match → 检查正在引用的关系 → 构建完整新快照和索引 → 保存旧版本 → 同目录临时文件写入并 flush/fsync → `os.replace` 原子替换 → fsync 目录 → 交换内存快照 → 返回新 revision。读请求固定快照，不读取半成品；失败前不替换当前有效版本。

原子替换解决半文件，不自动解决并发写丢失、跨文件事务或断电持久性。锁和 revision 必须同时存在。JSON 发布和 SQLite 关系修改共享服务级变更锁；新增绑定只允许引用有效测点，删除有绑定/任务引用的点返回 409，不自动级联删除；解除关系是显式独立操作。逻辑停用不删除历史引用。

任务生成时固化测点 ID、名称、必要算法配置及 archive_revision；之后重命名不改历史记录。不得将旧 revision 文件任意清理到历史任务无法解释；历史记录保存足够快照，备份保留策略再按部署容量设定。

运行中外部损坏文件不会替换最后有效快照；首次启动无文件需显式初始化空档案，解析损坏不能伪装“零测点”。磁盘发布成功但内存切换失败时进入不可写/未就绪状态，从磁盘重建后恢复，禁止继续用旧 revision 接受写入。

## 7. 验收与性能边界

建议验收目标（尚未进行 API 压测，不能当已达标结果）：1 万点、50 条分页、10 个并发客户端下，常用列表 API p95 ≤100 ms；重载 ≤2 s；新增常驻内存 ≤128 MiB/进程。应在实际部署及预期机器人硬件上，用真实字段长度、关联数量和权限校验复测。

以下情况重新评估 SQLite 主存储：超过当前 1 万规模或体积门槛；多人频繁批量修改；需要多 worker/多副本；复杂组合统计或关系事务；实测内存/延迟超出目标。SQLite 已是项目依赖，不需要额外数据库服务器。不要仅因达到某个理论条数自动迁移，依据真实工作负载决定。

性能基准脚本：`backend/scripts/benchmark_point_archive.py`。详见 [实测说明](performance/point-archive-20260917.md) 与 [原始结果](performance/point-archive-20260917.json)。1 万点约 6.167 MiB：逐请求读取解析查找中位数 117.357 ms；内存名称+类型过滤 1.720 ms；ID 索引查询 <0.001 ms；对象与三个索引常驻约 20.566 MiB。均为合成查询核心测试，不是完整 API 响应时间。

后续工作按 [实施计划](superpowers/plans/2026-09-17-point-archive-downshift.md) 分步进行；本次不实施业务代码和线上数据迁移。

## 8. 参考与适用范围

- [Python JSON](https://docs.python.org/3/library/json.html)：JSON 解码、大小限制及非法输入处理。
- [Python os.replace / fsync](https://docs.python.org/3/library/os.html#os.replace)：原子替换及落盘操作边界，临时文件必须在同一文件系统。
- [SQLite 适用场景](https://www.sqlite.org/whentouse.html)：应用文件、设备本地存储以及需转向客户端/服务端数据库的情况。

方案选择依据本仓库代码、用户确认的容量和合成测试；不是“JSON 在任何情况下都比数据库快”的结论。
