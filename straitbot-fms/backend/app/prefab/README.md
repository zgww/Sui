# prefab 节点树系统

把「配置信息、规则链、定时任务」统一组织成目录 + `xx.prefab.json` 节点树。
类定义即注册：**新增节点类型 = 在 `nodes/` 下新建一个模块并继承 `NodeBase`**，
前端 inspector 表单、加载器、Schema API 全部自动生效，零改动。

## 目录结构

```
app/prefab/
├── base.py       NodeBase（自动注册）+ Context + ui_field
├── registry.py   注册表访问 / build / schema 聚合
├── loader.py     目录扫描加载（可嵌套，*.prefab.json）
├── runtime.py    生命周期：激活/失活/tick/定时器
├── plan_scheduler.py  巡检计划调度的纯逻辑（扫文件/算到期/去重账本）
├── nodes/        节点类型（自动发现）
│   ├── logic.py    Sequence / Parallel / Selector（组合节点）
│   ├── timer.py    CronTimer / IntervalTimer（定时任务）
│   ├── action.py   LogAction / HttpAction（动作）
│   ├── config.py   ConfigNode（配置注入）
│   ├── waypoint.py 航点树编排节点（WaypointNodeBase，纯数据）
│   ├── plan.py     巡检计划编排节点（PlanNodeBase，纯数据）
│   ├── detect.py   检测流程编排节点（DetectNodeBase，纯数据）
│   └── plan_scheduler.py  InspectionPlanSchedulerNode（巡检计划调度，起线程）
└── prefabs/      默认示例（首次启动复制到 backend/data/prefabs/）

## 启动树 `data/prefabs/启动.prefab.json`

**常驻内存的对象树**：程序启动时加载，并且**先于**其它 prefab 激活
（见 `routers/prefab.startup_prefab`）——常驻任务（后台线程、调度）挂在这里，
别的规则链可能依赖它们已经就绪。文件缺失时启动流程会建一个空的（Sequence 根）。

⚠️ `data/prefabs/waypoint/`、`data/prefabs/plan/`、`data/prefabs/检测算法/` 都是
**编排数据**，不进 runtime（loader 的 `exclude`）：
- 航点树由航点树页面消费；
- 计划树由 `InspectionPlanSchedulerNode` 按文件扫描消费；
- 检测流程树目前只被读写与校验（取帧→前处理→算法→后处理尚未对接执行侧）。

三棵树各有一个路由（`/api/waypoint-prefab`、`/api/plan-prefab`、`/api/detect-prefab`），
由 `routers/prefab_store.make_prefab_router` 生成，**节点类型按中间基类过滤**，
所以三棵树的"添加子节点"目录互不串门。
```

## prefab 文件格式

```json
{
  "name": "示例",
  "description": "可选说明",
  "root": {
    "type": "Sequence",
    "properties": { "name": "链", "enabled": true },
    "children": [
      { "type": "LogAction", "properties": { "message": "hello" } }
    ]
  }
}
```

- `type`：节点类型名，必须已注册（未注册会报「未知节点类型」）
- `properties`：节点字段，按该类 pydantic 定义校验
- `children`：子节点列表（叶子节点留空）

## ui 元数据协议（前端 inspector 渲染依据）

字段语义用 pydantic 原生类型/约束表达，UI 元数据统一放 `json_schema_extra["ui"]`：

| widget | 前端控件 | 附加键 |
|---|---|---|
| text | 单行输入 | placeholder |
| textarea | 多行输入 | rows |
| number | 数字输入 | min / max / step |
| select | 下拉 | options（字符串数组） |
| checkbox | 开关 | — |
| slider | 滑块 | min / max / step |
| color | 取色器 | — |
| kv | 键值对(JSON 编辑) | — |
| children | 子节点（内置，树面板展示） | — |

声明方式（后端）：

```python
class MyNode(NodeBase):
    threshold: float = ui_field("number", group="参数",
                                min=0, max=100, default=50.0,
                                description="触发阈值")
```

## 新增一个节点类型（前端零改动）

```python
# app/prefab/nodes/my_node.py
from app.prefab.base import Context, NodeBase, ui_field

class MyNode(NodeBase):
    """我的新节点。"""
    param: str = ui_field("text", group="参数", default="")

    def on_active(self, ctx: Context) -> None:
        # 激活时执行的自定义逻辑
        ...
```

保存文件即可：`pkgutil` 自动发现模块 → `__init_subclass__` 自动注册 →
`GET /api/prefab/node-types` 自动多一条 schema → 前端 inspector 自动出现新表单。

## 生命周期

| 钩子 | 时机 | 顺序 |
|---|---|---|
| `on_active(ctx)` | 树激活 | 父先子（DFS） |
| `on_deactive(ctx)` | 树失活 | 子先父 |
| `on_tick(ctx, dt)` | 周期驱动 | 可选 |
| `on_error(ctx, exc)` | 出错回调 | 自动 |

- 子节点激活失败**只停该分支**（标 error），不拖垮整树；组合节点策略见 `nodes/logic.py`
- 节点间通过共享 `Context`（`kv` + `on/emit` 事件总线）通信，不互相直接引用
- `root.enabled = false` 可整树停用

## API

| 端点 | 说明 | 权限 |
|---|---|---|
| `GET /api/prefab/node-types` | 所有节点类型 schema（inspector 数据源） | 登录 |
| `GET /api/prefab/boot-tree` | 启动树（常驻内存那棵）+ 状态 | 登录 |
| `GET /api/prefab/trees` | prefab 树列表 + 运行状态 | 登录 |
| `GET /api/prefab/trees/{name}` | 单棵树完整 spec + 状态标注树 | 登录 |
| `POST /api/prefab/trees/{name}` | 保存 spec 写回文件并热重载 | 工程师 |
| `POST /api/prefab/reload` | 重载全部 prefab | 工程师 |

## 三棵编排数据树

| 树 | 目录 | API | 基类 | 一个文件 = |
|---|---|---|---|---|
| 航点树 | `data/prefabs/waypoint` | `/api/waypoint-prefab` | `WaypointNodeBase` | 一层楼的航点与动作 |
| 计划树 | `data/prefabs/plan` | `/api/plan-prefab` | `PlanNodeBase` | 多条巡检计划 |
| 检测流程 | `data/prefabs/检测算法` | `/api/detect-prefab` | `DetectNodeBase` | 一条检测逻辑 |

每棵树都是同一批接口（`node-types` / `dirs` / `files` / `rename` / `move` /
`trees` / `tree`），只是根目录与类型过滤不同。检测流程的节点清单见
`nodes/detect.py`：取帧 / 节流 / 抽帧 / 区域过滤 / 生效时段 / 图像预处理
（前处理）→ 算法检测 → 结果过滤 / 连续确认 / 抓拍留存 / 告警 / 转发 /
短信 / 邮件（后处理）。
