"""巡检计划编排节点（纯数据，不参与规则 runtime 的动作执行）。

与 `waypoint.py`（航点树编排）是**两棵独立的树**，只是共用同一套 prefab 机制：
同一份 NodeBase 注册表、同一套 JSON Schema 聚合、同一个前端 inspector 表单。
本模块描述"什么时候、巡检哪些航点 / 哪些测点"，航点树描述"每个航点长什么样、
到了之后拍什么照、画哪些检测框"。两者靠 **id 引用**（`wp_id` / `point_id`）关联，
不互相嵌套——否则改一个航点要在两棵树里各改一遍。

层级约定（仅约定，不在模型层强制，便于自由编排）：
    PlanGroupNode                 分组（**根**：一个文件里可挂多条计划）
      └ InspectionPlanNode            巡检计划（一条计划）
          ├ PlanGroupNode             分组（容器，"归入分组"建的就是它）
          ├ WaypointSelectNode        航点指定（要巡检哪些航点）
          ├ PointSelectNode           测点指定（要巡检哪些测点）
          └ DailyScheduleNode         每日调度（每天的时间范围 + 间隔）

根是分组而不是单条计划：一个文件只有一个根，根是单条计划就等于"一个文件只能
配一条计划"。同一台机器人要排"白天每小时一遍、夜里两小时一遍"就得开两个文件，
`source` 之类的配置还得抄两遍。

⚠️ **这些节点目前只落在编排侧**：`app/rail/inspection.py` 的巡检任务模型里
没有"计划"这个概念，真正按计划触发巡检由 `services/inspection_plans.py`
那套（数据库表 + 调度器）负责。本模块的产物是**给人和后续对接用的编排数据**，
要真正驱动执行，需要另做一次"计划树 -> 调度配置"的映射（与航点树的检测框
不下发是同一类缺口，见 `frontend/src/utils/inspectionBuild.ts` 的注释）。

**谁在消费这些文件**：`app/prefab/nodes/plan_scheduler.py` 的
`InspectionPlanSchedulerNode` 定时扫描 `data/prefabs/plan/**/*.prefab.json`，
按这里的「每日调度」算出到期时刻并触发（默认 dry_run，真下发回调由
`app/prefab/plan_scheduler.set_inspection_trigger` 注册）。
所以改这里的字段（尤其 `DailyScheduleNode`）会**直接影响**触发结果。
"""
from __future__ import annotations

import logging
from typing import Any, ClassVar

from pydantic import field_validator

from ..base import NodeBase, ui_field

logger = logging.getLogger(__name__)


class PlanNodeBase(NodeBase):
    """巡检计划树节点共同基类（中间类，不注册）。纯数据节点，不实现运行时动作。"""

    __type_name__: ClassVar[str | None] = None


class InspectionPlanNode(PlanNodeBase):
    """巡检计划：**一条**计划，把"巡检什么"和"什么时候巡检"组织在一起。

    之所以单独成节点而不是直接用分组代替：计划有自己的元信息（计划编号、
    目标机器人、优先级），这些不属于任何一条"指定"，但又必须跟树一起存，
    而且多条计划各自要有一份（挂分组上的话"这条计划给哪台机器人"就没地方写）。

    ⚠️ 它**不再是根**：根固定是 `PlanGroupNode`，一个文件下挂 N 条本节点。
    老文件的根是单条计划时，前端读取时会在内存里包一层分组（不写盘）。
    """

    plan_id: str = ui_field("text", group="计划", title="计划编号", default="",
                            description="对外标识这条计划的编号（可空；与后端巡检计划的 id "
                                        "不是一回事，这里只是编排数据里的一个标签）")
    robot_name: str = ui_field("text", group="计划", title="目标机器人", default="",
                               description="这条计划给哪台机器人用（可空 = 不限）。"
                                           "下发/调度侧按名字匹配，不写死数据库主键")
    priority: int = ui_field("number", group="计划", title="优先级", default=0,
                             description="数值越大越优先；冲突时由调度侧决定怎么用")
    detect_type: str = ui_field("select", group="计划", title="检测方式", default="fms",
                                options=["fms", "platform"],
                                description="这次巡检的动作数据怎么作用到检测："
                                            "fms = 本机跑检测流程（调外部推理服务）；"
                                            "platform = 上传给平台处理（旧版行为）。"
                                            "下发时写进巡检任务的 detectType，每个楼层段一致")
    note: str = ui_field("textarea", group="计划", title="备注", default="", rows=3,
                         description="给现场看的说明（不影响运行）")

    @field_validator("detect_type", mode="before")
    @classmethod
    def _normalize_detect_type(cls, v: Any) -> str:
        """未知值一律回落 `fms`（本模块的默认），**不抛错**。

        ⚠️ 这里的默认与 `rail/inspection.py::FloorTask.detect_type` **特意不同**：
        那边的缺省是 `platform`（要兼容老的下发 JSON —— 老任务里没这个字段，
        按旧版行为上传平台最安全）；而这里是**编排侧**的显式配置项，默认值就是
        "本机检测"，用户在检视器里看到的就是 `fms`。两边只在"值缺失"时走各自的
        缺省，一旦编排侧真的写了下发 JSON，字段是明确带上来的，不会两边打架。
        """
        s = str(v or "").strip().lower()
        if s in ("fms", "platform"):
            return s
        if s:
            logger.warning("[prefab] 巡检计划的 detect_type=%r 不认识，按 fms 处理", v)
        return "fms"


class PlanGroupNode(PlanNodeBase):
    """分组：把若干"计划 / 指定 / 调度"节点组织在一起，本身不产生任何语义。

    **它也是计划文件的根**（`routers/plan_prefab._plan_root`）：一个文件只有一个
    根，根是容器才能让一个文件里放多条 `InspectionPlanNode`。

    与航点树的 `GroupNode` 同名不同类（`GroupNode` 属于 WaypointNodeBase）：
    两棵树的类型目录是分开过滤的，共用名字会让"添加子节点"里混进另一棵树的类型。
    右键菜单的「归入分组」建的就是它。
    """


class WaypointSelectNode(PlanNodeBase):
    """航点指定：说明这次巡检要覆盖**哪些航点**。

    引用方式：`source` 指向一棵航点树文件（`data/prefabs/waypoint` 下的
    `rel_path`），`waypoint_ids` 再从里面挑具体的航点。**只存 id 不存航点的
    坐标/位姿**——航点树才是那些字段的唯一真相，计划里抄一份必然会漂移。

    `include_all=True` 时 `waypoint_ids` 被忽略（表示"这棵树的航点全都要"）。
    用显式开关而不是"空列表 == 全部"：后者会让"我特意一个都没勾"和
    "我没勾过"变成同一件事，用户取消最后一个勾选时数据会悄悄变义。

    空 `source` 表示还没指定航点树，节点是"待补全"状态，不是错误。
    """

    source: str = ui_field("text", group="航点指定", title="航点树文件", default="",
                           description="航点树编排里的相对路径，如 floor1.prefab.json。"
                                       "由「航点指定」面板下拉选择，一般不用手填")
    include_all: bool = ui_field("checkbox", group="航点指定", title="全部航点", default=True,
                                 description="勾上 = 该航点树里的航点全都要，忽略下面的指定列表")
    waypoint_ids: list[str] = ui_field("json", group="航点指定", title="指定航点", default=[],
                                       rows=6,
                                       description='航点的 key 列表，如 ["AO-RC-001", …]。'
                                                   '有 wp_id 用 wp_id，手工画的航点没有 wp_id，'
                                                   '用它在树里的路径（root/children/0/…）兜底')
    note: str = ui_field("textarea", group="航点指定", title="备注", default="", rows=3)


class PointSelectNode(PlanNodeBase):
    """测点指定：说明这次巡检要覆盖**哪些测点**。

    与航点指定同构：`point_ids` 存的是**测点档案**（`/api/point-archive/catalog/points`）
    里的测点 id，不是检测框/测温点节点上的路径——测点档案才是测点属性的唯一真相。
    `include_all=True` 时忽略 `point_ids`。
    """

    include_all: bool = ui_field("checkbox", group="测点指定", title="全部测点", default=True,
                                 description="勾上 = 测点档案里的测点全都要，忽略下面的指定列表")
    point_ids: list[str] = ui_field("json", group="测点指定", title="指定测点", default=[],
                                    rows=6,
                                    description='测点 id 列表，如 ["P-0001", …]。'
                                                '由「测点指定」面板勾选写入，一般不用手填')
    note: str = ui_field("textarea", group="测点指定", title="备注", default="", rows=3)


class DailyScheduleNode(PlanNodeBase):
    """每日调度：每天在 `[start_time, end_time]` 这个时间范围内，每隔
    `interval_minutes` 分钟触发一次巡检。

    时间一律用 `HH:MM`（24 小时制、本地时区）。之所以是**字符串而不是
    `time` 类型**：这个值要能原样出现在检视器文本框里、能被手改、能被导出成
    人看的 JSON，`datetime.time` 会在 schema 里变成一串前端不好渲染的结构。

    跨零点（如 22:00–06:00）**刻意不支持**：真机上"跨天的那一段算今天还是
    明天"必然要跟调度器对齐语义，含糊处理只会让现场对不上账。要夜间巡检就
    拆成两条计划。起止相等时算"整天只有一个时刻"，不展开成 24 小时。

    末次触发必须**早于** `end_time`（`start + n*interval <= end`），否则
    "08:00–18:00 每 1 分钟"会在 18:00 这个边界上多触发一次，与"范围"的
    直觉不符。规则见前端 `utils/planSelect.ts::scheduleSlots`。
    """

    start_time: str = ui_field("text", group="每日调度", title="开始时间", default="08:00",
                               description="HH:MM（24 小时制），如 08:00")
    end_time: str = ui_field("text", group="每日调度", title="结束时间", default="18:00",
                             description="HH:MM（24 小时制），必须不早于开始时间；"
                                         "不支持跨零点，夜间巡检请拆成两条计划")
    interval_minutes: int = ui_field("number", group="每日调度", title="间隔 (分钟)",
                                     default=60, min=1, max=1440,
                                     description="两次巡检之间隔多久；末次触发不会晚于结束时间")
    note: str = ui_field("textarea", group="每日调度", title="备注", default="", rows=3)
