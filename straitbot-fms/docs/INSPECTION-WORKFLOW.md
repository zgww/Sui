# 测点档案、航点绑定与巡检计划联动

## 范围与业务归属

FMS 负责本地档案、测点到航点/动作的关联、计划编排、本地调度与执行审计；机器人负责执行已下发动作。参考旧 Vue `src/views/confManager/module/BindCeDialog.vue` 和 `file_configuar` 相关接口，复用 FMS 的档案存储、`PointBinding` 和路线编译器。本次未修改 Java/Vue 集成平台，两套架构继续维护。

## 使用链路

1. 在“测点档案”创建或导入测点，所属目录支持任意深度树形选择及名称、编码、ID、完整路径模糊搜索。选中后显示完整目录路径。
2. 档案详情按顶部当前机器人显示航点关联；“前往航点绑定”带入稳定测点 ID。
3. 在“航点绑定测点”按地图、楼层、航点名称或外部编号筛选，选择整个航点或指定动作。绑定弹窗支持目录树、测点名称/编码/ID 搜索及跨页勾选；重复目标禁用选择。
4. “用这些测点创建计划”带入当前机器人、地图、楼层和已启用测点，生成未保存草稿。计划编辑器支持多段地图/楼层、目录筛选，并可跳转维护分段绑定后刷新选项。
5. 保存后可“预览路线”，查看各段测点、航点、动作及映射。“立即执行”再次校验路线和计划版本，确认后沿用现有执行接口。

绑定和预览均不发送机器人指令。解除绑定会提示受影响计划，保留档案及历史执行快照；后续计划预览/执行重新校验绑定。切换机器人会清除旧航点、候选项和未提交选择，避免跨机器人误绑定。跨地图/楼层执行仍遵循 `INSPECTION-MULTIMAP.md` 的到达确认流程，不包含自动乘梯或自动换图。

## 标识与接口

- 测点 `id` 是可移植档案稳定 ID；目录 `id` 及 `parent_id` 只表达档案层级。
- `robot_pk`、`map_pk`、`waypoint_pk`、`action_pk` 是当前 FMS SQLite 主键；设备 `robot_id`、`wp_id` 不与本地主键混用。跨项目导入 JSON 不移植本地机器人绑定。
- `GET /api/point-archive/binding-options` 新增 `map_pk`、`floor`、`waypoint_pk` 条件，返回去重测点数。楼层取航点覆盖值，否则继承地图，最后回退为 0。
- `GET /api/point-archive/bindings` 增加机器人、地图名称及受影响计划名称，原有字段保持兼容。
- `GET /api/point-archive/catalog/points?q=...` 支持名称/编码/ID 子串匹配；保留旧 `name` 和 `code` 的语义。
- `GET /api/inspection-plans/options/points` 新增 `directory_id`，包含后代目录并兼容旧 V1 档案层级。
- `GET /api/inspection-plans/{id}/preview?robot_pk=...` 使用同一编译器只读生成路线，返回计划版本、分段统计、航点/动作及测点映射；无数据库写入或设备调用。

新增接口沿用工程师权限。执行时固化路线、测点和关联快照；之后编辑目录、档案或绑定不改写历史任务。本次联动不增加数据库字段，也不修改档案文件格式。

## 界面规范

左侧菜单按运行总览、巡检业务、机器人配置、工程工具分组，保留既有页面和权限；支持桌面折叠、窄屏抽屉、选中状态和键盘焦点。三条链路统一弹窗间距、滚动内容区、底部按钮区；桌面上下至少 32px、窄屏四周至少 16px。窄屏宽表横向滚动，避免测点名称被挤成竖排。

## 验证记录（2026-09-18）

- 后端 Docker/Python 3.11 执行 `python -m pytest tests -q --disable-warnings`：235 passed，17 subtests passed，4 warnings。新增 `test_inspection_workflow.py` 覆盖 HTTP 联动、只读预览、解绑后的校验、不可变快照、机器人隔离、目录继承兼容和权限；既有测试覆盖批量原子性、重复绑定、停用测点及协议异常。
- 前端 Docker 中 `npm run build`（TypeScript + Vite）通过。最终镜像 ID：`59637a5f1110`。
- 浏览器在隔离 8912 完成：新增 `workflow-ui-20260918`（联动验收 · 轴承温度）→ 绑定航点 1 的红外测温动作 2 → 草稿 → 保存计划 4“【DEMO】档案绑定计划 · 联动验收”→ 预览 → 模拟执行完成。执行 ID：`fms-6c91d3138df648ccacbd2855ddd691b2`；任务快照确认测点、动作、地图 1、楼层 1 对应正确。
- Demo 保留三级目录“联动演示 / 配电楼 / 设备温度”和上述测点，合计 97 个测点。验证目录模糊搜索保留祖先路径、递归筛选、已绑定目标禁用、跨页选中保留、地图/楼层过滤及空机器人上下文重置。
- 检查 1280×720 与 390×844：计划/绑定弹窗及底部操作区均在视口内；窄屏表格可横向滚动，导航可展开/收起，键盘 Tab 可到保存按钮。浏览器未见脚本错误。
- 模拟环境所有 `robot_api.call` 由 Demo 入口拦截；本轮未向真实机器人下发巡检任务。真实固件联调仍须现场验证。

## 发布与回退

已更新 `192.168.6.88:8900` 及隔离 Demo `:8912`，使用 `straitbot-fms-backend:workflow-20260918`、`straitbot-fms-frontend:workflow-20260918`。两端 `/api/health` 返回 200。

8900 沿用 `/home/hxzh/straitbot-fms/data` 和现有环境配置；8912 沿用独立 Demo 数据卷。8900 更新前后档案 SHA-256 均为 `794b4e7ebad009240114d41aabec6ac4b80fa070a102bf8c29e76a7c1ab60e88`，保留第 6 版、300 个测点和 55 个目录。未用 Demo 覆盖 8900 数据。

源代码/构建日志位于服务器 `/home/hxzh/fms-releases/20260918-workflow`。8900 原镜像保留为后端 `immediate-api-20260918` 和前端 `directory-tree-20260918`，Compose 镜像配置已备份为 `docker-compose.release.before-workflow.yml`。回退本次联动时在 `/home/hxzh/straitbot-fms` 执行：

```sh
cp docker-compose.release.before-workflow.yml docker-compose.release.yml
docker compose -f docker-compose.yml -f docker-compose.release.yml up -d --no-build
```

该回退仅恢复到本次更新前已经支持多地图和立即执行的版本，不恢复或覆盖数据。若回退至更早、不支持分段计划的版本，须遵循 `INSPECTION-MULTIMAP.md` 的数据库及执行兼容流程。
