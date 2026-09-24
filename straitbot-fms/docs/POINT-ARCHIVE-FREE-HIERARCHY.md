# 自由目录与跨项目静态档案

## 本次范围
FMS 承接测点档案自由组织；旧 Java/Vue 平台继续维护。本次只修改 FMS，不改变平台接口或下发机器人控制。旧 Vue `confManager/module/fileConfigurationFile/pointConf.vue` 的 level1–4 分别定位变电站/电压/间隔/设备，测点为第5层；该约束仅在同步准备校验时应用。

## 档案组织
目录使用平铺的 `id` / `parent_id` 表示树，无固定业务深度限制，迭代校验可处理长链，拒绝不存在父节点及循环。测点使用 `directory_id`，可在根目录或任意目录。单套上限为10,000测点及10,000目录，文件上限32 MiB。JSON嵌套安全上限32不限制树的层数。

可选 `role`：custom、station、voltage、bay、equipment。日常维护不限制父子role；在“同步选项”中可校验 `station → voltage → bay → equipment → point`。勾选“导出前执行平台层级校验”仅约束本次页面会话的导出。没有实际上传平台功能，不会把校验成功当作已同步。

## 静态格式

```json
{
  "format": "straitbot.point-archive",
  "schema_version": 2,
  "directories": [
    {"id": "area-001", "name": "现场区域", "parent_id": null, "role": "custom"},
    {"id": "group-001", "name": "温度测点组", "parent_id": "area-001", "role": "custom"}
  ],
  "points": [
    {"id": "000001", "name": "油温", "code": "T-001", "directory_id": "group-001", "assay_type": 1, "times": 1, "active": true, "unit": "℃", "extensions": {}}
  ]
}
```

文件不携带服务端revision、账号、机器人连接或SQLite绑定。项目A导出，项目B导入并预览后替换目录与测点；B独立生成新revision。已有同ID测点配置会覆盖，本地航点绑定保留；不能移除已被绑定或历史任务引用的点。未知测点业务字段进入extensions。对接其他项目需实现此v2格式，旧版FMS需升级后才能读取自由目录。

## 兼容与接口
读取v1档案时只在内存投影，不修改磁盘。第一次新版维护或导入发布时写v2，沿用原子备份、If-Match和引用锁。旧版站/间隔/设备ID可在不同表重复，因此目录迁移使用类型+确定性SHA256生成目录ID，并保留legacy_id；测点ID和配置保持不变，已有绑定及任务快照仍有效。

- `/api/point-archive/catalog/directories`：目录及直接子项计数。
- `/catalog/points`：目录/子树、名称、编码、状态和绑定分页查询。
- `/catalog/{directories|points}`：新增；带ID路径可更新/删除。ID不可修改。
- `/catalog/export`：静态JSON；`platform=true`强制校验层级。
- `/catalog/import/preview`、`PUT /catalog/import`：校验预览及版本化发布。
- `/catalog/platform-check`：只读层级检查。

所有接口仍要求工程师鉴权。旧固定层级写接口在v2数据上明确拒绝，以免旧客户端破坏自由目录；旧v1数据仍保留其原接口行为。

## 界面设计
面向现场配置人员的目录工作区：左树右表，目录路径、直接子目录与测点分开；统一头部JSON工具及同步选项。深蓝文字#1c3049、灰蓝背景#f3f6fa、边框#e4eaf1、主操作蓝#285ad6、状态绿#3b8570；标题使用Segoe UI/微软雅黑，ID使用Consolas。树和表单均有空态、错误态和焦点状态。搜索防抖并忽略过时请求；目录与测点分别记录读取版本，避免列表并发刷新覆盖编辑版本。

## 验证和发布
测试：`backend/tests/test_point_archive_catalog.py`；容量：`backend/scripts/validate_catalog_capacity.py`。最终执行结果和部署记录见 `performance/point-archive-v2-validation.md`。回退前应先保存新数据；v2文件不能直接交给v1镜像，需要恢复成对的发布前JSON与SQLite备份，或保留兼容v2的后端。
