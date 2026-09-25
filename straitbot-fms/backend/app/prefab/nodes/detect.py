"""检测流程编排节点（纯数据，不参与规则 runtime 的动作执行）。

一个 `data/prefabs/检测算法/*.prefab.json` = **一条检测逻辑**（如"人员入侵"）。
它描述的不是"用哪个算法"这一件事，而是**从取帧到通知的完整链路**：

    DetectPipelineNode          检测流程（根，一条检测逻辑）
      ├ DetectGroupNode          分组（stage = 前处理 / 检测 / 后处理）
      │   ├ FrameSourceNode      取帧：图像从哪来（抓拍图 / 视频流 / 热像仪）
      │   ├ ThrottleNode         节流：时间窗内最多放行几条
      │   ├ FrameSkipNode        抽帧：每 N 帧才处理 1 帧
      │   ├ RoiFilterNode        区域过滤：只处理（或排除）画面里的某块区域
      │   ├ TimeWindowNode       生效时段：只在某些时段 / 某些星期几生效
      │   └ ImagePreprocessNode  图像预处理：缩放 / 灰度 / 降噪
      ├ DetectorNode（抽象基类，不注册）算法检测的共性：置信度阈值 / 类别白名单 / 最多结果数
      │   └ 每种视觉算法一个子类（见 algorithms.py，节点类型即算法身份，共 16 个）：
      │       状态识别 SwitchState/IndicatorLight/CabinetDoor/ValveState
      │       表计读数 MeterPointer/MeterDigital/MeterLevel/CounterRead（带单位/量程/小数位）
      │       缺陷检测 InsulatorDamage/EquipmentRust/CableDamage/WaterLeak（带最小面积占比）
      │       安全告警 PersonIntrusion/SmokeFire/ForeignObject/HelmetCheck（带最小目标框占比）
      └ 后处理
          ├ ResultFilterNode     结果过滤：按置信度 / 类别 / 数量再筛一道
          ├ ConfirmNode          连续确认：连续 N 次命中才认定（去重抖）
          ├ EvidenceNode         抓拍留存：存证据图、保留天数
          ├ AlarmNode            事件告警：命中即报（二值判定，不看数值）
          ├ NumericAlarmNode     数值告警：数值 op 阈值（温度 82℃、电流 210A）
          ├ RangeAlarmNode       数值范围告警：跑出（或落进）一个区间
          ├ ForwardNode          转发：HTTP 推送到第三方平台
          ├ SmsNotifyNode        短信通知
          └ EmailNotifyNode      邮件通知

**为什么用 prefab 而不是在检测框上挂几个字段**：算法只是链路中的一环。
同一类事件在不同测点上的处理要求完全不同——有的要抽帧省算力，有的要连续
三次命中才报，有的只是记一笔，有的要发短信。把这些塞进检测框的字段里，
每加一种诉求就要改一次数据模型；做成节点后，加一种处理方式只是多一个节点
类型，老流程一个字节都不用动。

与 `waypoint.py` / `plan.py` 一样是**第三棵独立的树**：同一套 NodeBase 注册与
schema 机制，但中间基类是 `DetectNodeBase`，后端 `node-types` 按基类过滤，
三棵树的类型目录互不串门（见 `routers/prefab_store.py`）。

层级自由编排，不在模型层强制：前处理节点放在算法后面不会报错，只是语义上
通常没意义。真正让顺序产生意义的是**执行侧按 children 顺序走**。

⚠️ **当前只落在编排侧**：这些节点目前只被读写与校验，不驱动任何执行
（与航点树的检测框不下发、计划树不直接调度是同一类缺口）。要真正跑起来，
需要一次"检测流程树 -> 执行管线"的映射：由执行侧按顺序构造
「取帧 -> 前处理 -> 算法 -> 后处理」，把 `enabled=false` 的节点整棵子树跳过。
字段现在按"执行侧要什么"来定，就是为了那次映射不用再改数据结构。
"""
from __future__ import annotations

from typing import Any, ClassVar, Literal

from ..base import NodeBase, ui_field

#: 告警级别（**由低到高**，顺序即语义）。
#:
#: 三棵树里凡是"命中后要上报"的节点都复用这一组，别各写一份——级别是**对外契约**
#: （告警列表、短信网关、转发报文、值班排班都按它分流），一边多一个"紧急"
#: 另一边不认，现场就会出现"明明报了却没人收到"。
#:
#: 执行侧 `detect_pipeline.LEVELS` 与这一组**必须一致**（靠下标比大小），
#: 改这里要同步改那边，`tests/test_detect_pipeline.py` 有断言盯着。
LEVEL_OPTIONS = ["预警", "一般告警", "严重告警", "危急告警"]


class DetectNodeBase(NodeBase):
    """检测流程树节点共同基类（中间类，不注册）。纯数据节点，不实现运行时动作。"""

    __type_name__: ClassVar[str | None] = None


# ---------------------------------------------------------------- 容器

class DetectPipelineNode(DetectNodeBase):
    """检测流程：**一条检测逻辑**（一个文件就是一条）。

    它是文件的根（`routers/detect_prefab._detect_root`），前处理 / 算法 /
    后处理都挂在它下面。之所以要一个专门的根节点而不是用分组代替：一条检测
    逻辑有自己的对外身份（检测编号、适用场景），这些不属于任何一个处理步骤，
    但又必须跟着文件一起存。

    `detect_id` 是**对外引用这条流程的键**（检测框 / 测点绑定它时用这个值），
    与算法 id 不是一回事：同一算法（人员入侵）在不同测点上可以配出松紧不同
    的好几条流程，靠算法 id 区分不开。
    """

    detect_id: str = ui_field("text", group="检测流程", title="检测编号", default="",
                              description="对外引用这条流程的编号（可空 = 只用文件名）。"
                                          "同一算法可以有多条流程，别用算法 id 代替它")
    scene: str = ui_field("text", group="检测流程", title="适用场景", default="",
                          description="一句话说明这条流程用在哪（如「配电室夜间人员入侵」），"
                                      "给现场挑流程时看")
    note: str = ui_field("textarea", group="检测流程", title="备注", default="", rows=3,
                         description="给现场看的说明（不影响运行）")


class DetectGroupNode(DetectNodeBase):
    """分组：把若干处理步骤组织在一起，本身不产生任何语义。

    `stage` 只是**标注**（前处理 / 检测 / 后处理 / 自定义），执行侧不会因为
    它改变顺序——顺序由 children 数组决定。留着它是为了让一棵几十个节点的
    流程在树上看得出段落，也让"添加子节点"时有个落点。

    与航点树的 `GroupNode`、计划树的 `PlanGroupNode` 同名不同类：三棵树的
    类型目录是分开过滤的，共用名字会让"添加子节点"里混进另一棵树的类型。
    右键菜单的「归入分组」建的就是它。
    """

    stage: Literal["前处理", "检测", "后处理", "自定义"] = ui_field(
        "select", group="分组", title="阶段", default="自定义",
        options=["前处理", "检测", "后处理", "自定义"],
        description="仅作标注与展示，执行顺序仍按树上的先后")


# ---------------------------------------------------------------- 前处理

class FrameSourceNode(DetectNodeBase):
    """取帧：这一条流程的图从哪来。

    放在最前面而不是写死在算法节点上：**同一算法可能跑在不同的图上**
    （可见光抓拍图做入侵识别、热像图做过热识别），取哪路图是流程的属性，
    不是算法的属性。

    ⚠️ 只描述"哪一路"，**不写通道号**：真机是单可见光通道，通道号是设备
    侧的事，写死在编排数据里换台设备就全错（相机/云台的通道号教训）。
    """

    source: Literal["抓拍图", "实时视频流", "热像仪"] = ui_field(
        "select", group="取帧", title="图像来源", default="抓拍图",
        options=["抓拍图", "实时视频流", "热像仪"],
        description="抓拍图=到航点后拍的那张；实时视频流=连续帧；热像仪=红外画面")
    note: str = ui_field("textarea", group="取帧", title="备注", default="", rows=2)


class ThrottleNode(DetectNodeBase):
    """节流：一个时间窗内最多放行几条检测结果。

     detections 源源不断（尤其实时视频流），不做节流就是一秒几十条同样内容的
    告警。`window_seconds` + `max_events` 是"窗口内最多 N 条"的经典节流；
    `strategy` 决定超出的部分怎么办——**丢弃**是常态（抖动的中间帧没价值），
    **延后到窗末**适合"每一条都要留痕、但可以合并着报"的场景。

    `max_events = 0` 表示"窗口内一条都不放行"（等于临时关掉这条流程的后续），
    不是"不限制"——不限制就把窗口设成 0 或直接停用本节点，语义更清楚。
    """

    window_seconds: float = ui_field("number", group="节流", title="时间窗 (秒)",
                                     default=10.0, min=0, max=3600, step=0.5,
                                     description="滑动窗口长度；0 = 不做窗口（每条都算一次判定）")
    max_events: int = ui_field("number", group="节流", title="窗内最多放行", default=1,
                               min=0, max=9999,
                               description="窗口内最多放行几条；0 = 一条都不放行")
    strategy: Literal["丢弃", "延后到窗末"] = ui_field(
        "select", group="节流", title="超出策略", default="丢弃",
        options=["丢弃", "延后到窗末"],
        description="超出的结果直接丢弃，还是攒到窗口结束时一起放行")
    note: str = ui_field("textarea", group="节流", title="备注", default="", rows=2)


class FrameSkipNode(DetectNodeBase):
    """抽帧：每 N 帧才交给算法处理 1 帧。

    与节流的区别：**节流在时间维度上限量**（一秒最多几条），**抽帧在输入
    维度上降采样**（每 N 帧看一帧）。视频流场景两者通常一起用：抽帧降算力，
    节流控告警量。

    `every_n_frames = 1` = 不抽帧（每帧都处理）。
    """

    every_n_frames: int = ui_field("number", group="抽帧", title="每 N 帧处理 1 帧",
                                   default=1, min=1, max=600,
                                   description="1 = 每帧都处理；10 = 每 10 帧处理第 1 帧")
    note: str = ui_field("textarea", group="抽帧", title="备注", default="", rows=2)


class RoiFilterNode(DetectNodeBase):
    """区域过滤：画面里只处理（或排除）某一块区域。

    坐标**归一化 0~1**（相对画面宽高），与航点树的检测框同一套约定：换相机、
    换分辨率、重新标定，区域都还落在同一个位置上。

    之所以要"排除"这一向：机房里常有"画面边缘是走廊、人来人往很正常"的
    情况，与其把 ROI 画成一块奇形区域绕开走廊，不如圈出走廊排除掉。
    """

    roi: list[dict[str, float]] = ui_field("json", group="区域", title="区域顶点（归一化 0~1）",
                                           default=[], rows=6,
                                           description='[{"x":0.1,"y":0.2}, …] 按顺序连成闭合区域；'
                                                       '矩形同样用 4 个点')
    mode: Literal["只处理框内", "排除框内"] = ui_field(
        "select", group="区域", title="模式", default="只处理框内",
        options=["只处理框内", "排除框内"],
        description="只处理框内=ROI 之外的结果丢掉；排除框内=ROI 之内的结果丢掉")
    note: str = ui_field("textarea", group="区域", title="备注", default="", rows=2)


class TimeWindowNode(DetectNodeBase):
    """生效时段：只在每天某个时间范围（和某些星期几）内生效。

    时间一律 `HH:MM`（24 小时制、本地时区）——这个值要能原样出现在检视器
    文本框里、能被手改、能导成人看的 JSON，`datetime.time` 在 schema 里是
    一串前端不好渲染的结构。

    **跨零点刻意不支持**（与计划树的 `DailyScheduleNode` 同一取舍）：22:00–06:00
    这种"跨天的那一段算今天还是明天"必然要跟执行侧对齐语义，含糊处理只会让
    现场对不上账。要夜间生效就拆成两条流程（或两段节点）。

    `every_day=True` 时忽略 `days`（表示每天都生效）。用显式开关而不是
    "空列表 == 全部"：后者会让"我特意一天都没勾"和"我没勾过"变成同一件事，
    用户取消最后一个星期几时数据会悄悄变义。
    """

    start_time: str = ui_field("text", group="生效时段", title="开始时间", default="00:00",
                               description="HH:MM（24 小时制），如 08:00")
    end_time: str = ui_field("text", group="生效时段", title="结束时间", default="23:59",
                             description="HH:MM，必须不早于开始时间；不支持跨零点")
    every_day: bool = ui_field("checkbox", group="生效时段", title="每天生效", default=True,
                               description="勾上 = 忽略下面的星期几")
    days: list[int] = ui_field("json", group="生效时段", title="星期几", default=[],
                               rows=2,
                               description="1=周一 … 7=周日，如 [1,2,3,4,5] 表示工作日；"
                                           "every_day 勾上时忽略")
    note: str = ui_field("textarea", group="生效时段", title="备注", default="", rows=2)


class ImagePreprocessNode(DetectNodeBase):
    """图像预处理：交给算法之前先对画面做固定几件事。

    只留三个**跨算法通用**的开关（缩放 / 灰度 / 降噪）。算法自己的特殊前处理
    放到 `DetectorNode.params` 里——这里每加一个开关，所有流程的检视器都要
    多一个用不到的控件。

    `resize_short_side = 0` 表示不缩放。之所以按**短边**而不是给宽高：
    换相机分辨率变了也只要填一个数，不用跟着改两个数还担心拉伸。
    """

    resize_short_side: int = ui_field("number", group="预处理", title="缩放短边 (像素)",
                                      default=0, min=0, max=4096,
                                      description="0 = 不缩放；非 0 时按短边等比缩放")
    grayscale: bool = ui_field("checkbox", group="预处理", title="转灰度", default=False,
                               description="省算力，但对颜色敏感的算法不能开")
    denoise: bool = ui_field("checkbox", group="预处理", title="降噪", default=False,
                             description="画面噪点多时开；会额外耗一点算力")
    note: str = ui_field("textarea", group="预处理", title="备注", default="", rows=2)


# ---------------------------------------------------------------- 检测

class DetectorNode(DetectNodeBase):
    """算法检测节点的**共同基类**（中间类，不注册）：真正跑视觉算法的那一步。

    本类**不会**直接出现在"添加节点"里——每种算法是它的一个具体子类
    （见 `nodes/algorithms.py`，如 `PersonIntrusionNode` = 人员入侵、
    `MeterDigitalNode` = 数字表读数）。一条流程通常放一个算法节点。

    为什么不再用"一个通用节点 + 算法下拉"：不同算法要配的东西根本不一样——
    表计读数要量程 / 单位 / 小数位，状态识别要期望状态，缺陷检测要最小面积。
    下拉只能把这些差异全塞进一个自由 `params` JSON，检视器给不出像样的表单，
    执行侧也拿不到结构化字段。改成继承后，每个算法节点在自己类上声明字段，
    schema 表单自动渲染；新增一种算法 = 在 `algorithms.py` 加一个子类，
    前端零改动。

    `algorithm` 字段保留但**只读**：它存 `data/algorithms.json` 里的 **id**，
    是执行侧把一次命中（`DetectEvent.algorithm`）对上节点的键，值由子类的
    `algorithm_id` 类属性固定，不让人手选——算法身份已经由节点类型本身表达。

    字段分层：每个算法都有的共性字段（阈值 / 类别白名单 / 最多结果数）放本类；
    一类算法通用的字段放 `algorithms.py` 的类别基类（表计 / 状态 / 缺陷 / 安全）；
    单个算法独有的字段直接写在具体子类上。`params` 仍是自由 JSON 兜底口，
    留给还没固化成专属字段的参数。
    """

    __type_name__: ClassVar[str | None] = None

    #: 绑定的算法 id（对应 `data/algorithms.json`），具体子类必须覆盖
    algorithm_id: ClassVar[str] = ""

    #: 本节点的 `threshold` 是否参与 `detect_pipeline._gate_detector` 的置信度闸门。
    #: 下线了阈值字段的算法节点把它置 False（见 `MeterAlgorithmNode`）——
    #: 字段虽然还留在模型上（老数据兼容），但**不能再悄悄生效**，
    #: 否则用户在界面上看不到的旧值会继续拦结果。
    __threshold_gate__: ClassVar[bool] = True

    algorithm: str = ui_field("readonly", group="算法", title="算法", default="",
                              description="对应 data/algorithms.json 的算法 id，"
                                          "由节点类型固定，不可手选")
    threshold: float = ui_field("number", group="算法", title="置信度阈值", default=0.5,
                                min=0, max=1, step=0.05,
                                description="低于该置信度的识别结果不采纳（0~1）")
    labels: list[str] = ui_field("json", group="算法", title="只保留类别", default=[],
                                 rows=3,
                                 description='算法输出的类别白名单，如 ["person"]；'
                                             '空数组 = 全部类别都要')
    max_results: int = ui_field("number", group="算法", title="最多结果数", default=0,
                                min=0, max=999,
                                description="0 = 不限；超过时按置信度取前 N 个")
    params: dict = ui_field("json", group="参数", title="其他参数", default={}, rows=5,
                            description="还没固化成专属字段的算法参数，自由 JSON 兜底；"
                                        "换算法时通常要一起改")
    note: str = ui_field("textarea", group="参数", title="备注", default="", rows=2)

    def __init_subclass__(cls, **kwargs: Any) -> None:
        super().__init_subclass__(**kwargs)
        # 子类用 algorithm_id 绑定算法后，把只读 algorithm 字段的默认值固定成它
        aid = cls.__dict__.get("algorithm_id", "")
        if aid and "algorithm" in cls.model_fields:
            cls.model_fields["algorithm"].default = aid


class MeterAlgorithmNode(DetectorNode):
    """通用算法节点（**兼容现有算法推理服务**）：从算法清单里选择算法类型。

    与 `nodes/algorithms.py` 里"一种算法一个子类"的节点不同，本节点是
    **一个通用节点 + 算法下拉**，专门对接现有算法推理服务。可选用的算法有
    60+ 种（电流表 / 电压表 / 数显 / 旋转开关 / 压板 / 指示灯 / 综保 /
    圆形表盘 / 接地开关，以及安全帽、烟火、跑冒滴漏、人员越界…，清单见
    `data/panel_list.json`），逐个做子类既不现实也没必要——它们打的是同一个
    推理接口（`/upload_tactics`），区别只在每个检测框的 `box.name` 编码。

    `panel_algorithm` 存选中算法的 **name 编码**（panel_list 里的 `name`，
    如 `1_0_0_1_53_0`），提交推理时直接作为 `boxs[].name`；选项由前端从
    `/api/detect-prefab/panel-list` 拉取（`optionsFrom="panelList"`）。
    数字 id 与中文名在需要时按 name 反查 panel_list，不在节点上重复抄，
    避免清单更新后镜像漂移。

    ⚠️ **本节点只负责"把框交给推理服务"，不做任何筛选**（2026-09-24 定）：
    从 `DetectorNode` 继承来的 `threshold`（置信度阈值）、`params`（其他参数）
    与只读 `algorithm` 镜像在本节点上**没有意义**，已用 `__hidden_fields__`
    从检视器下线 —— 推理服务不认这些参数，"要不要告警"由后面的
    `ResultFilterNode` / `AlarmNode` / `NumericAlarmNode` 决定。

    保留下来的只有两个**结果口径**字段：`labels`（只保留类别）与
    `max_results`（最多结果数）。它们是"这条流程要哪种结论"，
    与推理服务怎么跑无关，所以留在算法节点上。
    """

    __type_name__: ClassVar[str] = "MeterAlgorithmNode"

    #: 算法身份由 panel_algorithm 选择决定，而非节点子类，故不固定 algorithm_id
    algorithm_id: ClassVar[str] = ""

    #: 检视器上不渲染的继承字段：对现有推理服务无意义（详见类文档）。
    #: ⚠️ 只是**不下发**，模型仍然接受这些键 —— 存量 prefab 里带着它们照样能 build。
    __hidden_fields__: ClassVar[tuple[str, ...]] = ("algorithm", "threshold", "params")

    #: 阈值字段已下线，不再参与置信度闸门（老数据里残留的旧值也不生效）
    __threshold_gate__: ClassVar[bool] = False

    panel_algorithm: str = ui_field(
        "select", group="算法", title="算法类型", default="",
        optionsFrom="panelList",
        description="从算法推理服务的算法清单（data/panel_list.json）中选择。"
                    "存的是 name 编码，提交推理时作为检测框 box.name")


# ---------------------------------------------------------------- 后处理

class ResultFilterNode(DetectNodeBase):
    """结果过滤：算法出来之后再按置信度 / 类别 / 数量筛一道。

    与 `DetectorNode.threshold` 的分工：**阈值是喂给算法的**（影响算法内部
    怎么判），**这里是算法出来之后的外层筛选**（不进算法、纯过滤）。同一算法
    换个测点只想收紧"最终采纳线"时，改这里比调算法参数安全。

    三个条件都是"不填 = 不过滤"（`max_count=0` 不限数量），缺省语义统一，
    免得记住"哪个是 0 表示全砍、哪个是 0 表示全放"。
    """

    min_confidence: float = ui_field("number", group="结果过滤", title="最低置信度",
                                     default=0.0, min=0, max=1, step=0.05,
                                     description="0 = 不过滤；高于算法阈值时才有效果")
    labels: list[str] = ui_field("json", group="结果过滤", title="只保留类别", default=[],
                                 rows=3, description="空数组 = 全部类别")
    max_count: int = ui_field("number", group="结果过滤", title="最多保留", default=0,
                              min=0, max=999, description="0 = 不限")
    note: str = ui_field("textarea", group="结果过滤", title="备注", default="", rows=2)


class ConfirmNode(DetectNodeBase):
    """连续确认：连续 N 次命中才认定（防抖 / 去误报）。

    单帧误报是这类系统最常见的噪声来源（一张图糊了、一只猫过去了）。
    `require_count` 次都命中才往下走，是**最便宜也最有效**的一招。

    `within_seconds` 是这 N 次必须落在多久之内：不设上限的话，上午一次、
    下午一次的两次命中也会被算成"连续"，语义就散了。
    `reset_on_miss=False` 时允许中间断一次（累计计数不清零），适合遮挡多的场景。
    """

    require_count: int = ui_field("number", group="连续确认", title="连续命中次数",
                                  default=1, min=1, max=100,
                                  description="连续命中几次才认定；1 = 不确认（命中即报）")
    within_seconds: float = ui_field("number", group="连续确认", title="时间窗 (秒)",
                                     default=0, min=0, max=3600, step=0.5,
                                     description="这几次命中必须落在多久之内；0 = 不限时间")
    reset_on_miss: bool = ui_field("checkbox", group="连续确认", title="中断即清零",
                                   default=True,
                                   description="勾上 = 中间有一次没命中就从头数；"
                                               "不勾 = 累计计数（遮挡多的场景用）")
    note: str = ui_field("textarea", group="连续确认", title="备注", default="", rows=2)


class EvidenceNode(DetectNodeBase):
    """抓拍留存：把命中时的画面存下来当证据。

    告警要能复盘，光有一条"几点几分谁入侵了"的文本没有说服力。这一步负责
    把那一帧（可选画上检测框）落到磁盘。

    `keep_days = 0` 表示**不清理**（一直留着）；磁盘是有限的，现场一般填 7~30。
    """

    dir: str = ui_field("text", group="留存", title="保存目录", default="",
                        description="相对数据目录的路径，如 data/evidence；"
                                    "留空 = 用系统默认目录")
    keep_days: int = ui_field("number", group="留存", title="保留天数", default=30,
                              min=0, max=3650, description="0 = 不清理")
    with_box: bool = ui_field("checkbox", group="留存", title="画上检测框", default=True,
                              description="把命中的框画在图上再存，复盘时一眼能看到")
    note: str = ui_field("textarea", group="留存", title="备注", default="", rows=2)


class AlarmNode(DetectNodeBase):
    """事件告警：检测**命中**就报（不看数值）。

    与 `NumericAlarmNode` / `RangeAlarmNode` 的分工：本节点回答"有没有这回事"
    （画面里有没有人、开关是不是分了），数值类回答"这个数是不是不正常"
    （温度 82℃、电流 210A）。前者是二值判定，后者要跟阈值/区间比——
    判据不同、字段也不同，所以不是一个节点加两个字段能解决的。

    `template` 引用 `data/prefabs/告警模板/` 下的文件（相对路径），标题与正文
    留在这里手填——模板管"这类告警长什么样、发给谁"，这里是"这条流程报出来的
    具体措辞"。两者分开，改措辞不用动模板，改模板不影响已配好的流程。

    `dedup_seconds` 是**同一目标的合并窗口**：同一个测点在窗口内重复命中只出
    一条告警（更新最后命中时间），不合并的话一次入侵能刷出几十条一样的告警，
    值班的人就只能全部忽略——等于告警白配。
    """

    level: Literal["预警", "一般告警", "严重告警", "危急告警"] = ui_field(
        "select", group="告警", title="告警级别", default="预警", options=LEVEL_OPTIONS,
        description="命中后上报的级别；短信/邮件/转发里的「最低级别」按它分流")
    template: str = ui_field("text", group="告警", title="告警模板", default="",
                             description="data/prefabs/告警模板/ 下的相对路径，"
                                         "如 人员入侵告警.prefab.json；留空 = 不用模板")
    title: str = ui_field("text", group="告警", title="告警标题", default="",
                          description="支持 {var} 占位（来自流程上下文，如 {point_name}）")
    content: str = ui_field("textarea", group="告警", title="告警正文", default="", rows=3,
                            description="支持 {var} 占位")
    dedup_seconds: float = ui_field("number", group="告警", title="合并窗口 (秒)",
                                    default=0, min=0, max=86400, step=1,
                                    description="同一目标在该窗口内重复命中只出一条告警；"
                                                "0 = 不合并")
    note: str = ui_field("textarea", group="告警", title="备注", default="", rows=2)


class NumericAlarmNode(DetectNodeBase):
    """数值告警：一个**数值越过阈值**就报（温度 82℃、电流 210A、表计读数超量程）。

    与 `AlarmNode`（事件告警）的区别：那边是"有没有这回事"的二值判定，这边是
    "这个数是不是不正常"——判据不同，所以要单独成节点，不是一个 `threshold`
    字段能糊过去的（事件告警根本没有数值可比）。

    `op` + `threshold` 是判据；`hysteresis`（回差）**刻意留着**：数值在阈值附近
    抖动是最常见的误报来源（80.1 / 79.9 来回跳），没有回差就会一秒一条告警。
    回差的语义是"报警之后要回落 `hysteresis` 才解除"，要在执行侧配合状态使用。

    `duration_seconds` = 连续超标多久才报（滤掉瞬时尖峰）；0 = 立即报。

    ⚠️ **数值从哪来**：取**测点识别结果的 `parameter`**（算法服务对这块区域给出的
    读数，如 `"82.5"`），由执行侧 `alarm_processor._read_value` 解析成数字后喂给
    `detect_pipeline.numeric_alarm_hit`。取不出数字（`parameter` 空 / 没有数字）
    时**跳过、不报**——不拿 0 顶替，否则"没采到"会被当成"0℃"报一堆假告警。
    编排数据只管判据，不该知道设备协议（这一点与 `AlarmNode` 一致）。
    """

    level: Literal["预警", "一般告警", "严重告警", "危急告警"] = ui_field(
        "select", group="告警", title="告警级别", default="一般告警", options=LEVEL_OPTIONS,
        description="数值越限后上报的级别；短信/邮件按它分流")
    metric: str = ui_field("text", group="判据", title="监测项", default="",
                           description="这个数值叫什么（如 温度 / A相电流 / 表计读数），"
                                       "给人和告警正文看")
    unit: str = ui_field("text", group="判据", title="单位", default="",
                         description="如 ℃ / A / kV；只作展示，不参与比较")
    op: Literal[">", ">=", "<", "<=", "==", "!="] = ui_field(
        "select", group="判据", title="比较", default=">", options=[">", ">=", "<", "<=", "==", "!="],
        description="识别结果的 parameter 与阈值比较，表达式成立就报警")
    threshold: float = ui_field("number", group="判据", title="阈值", default=0.0, step=0.1,
                                description="与识别结果 parameter 比较的那个数（与 unit 同一量纲）")
    hysteresis: float = ui_field("number", group="判据", title="回差", default=0.0,
                                 min=0, step=0.1,
                                 description="报警后要回落这么多才解除；0 = 不设回差。"
                                             "数值在阈值附近抖动时不设回差会刷屏")
    duration_seconds: float = ui_field("number", group="判据", title="持续 (秒)", default=0,
                                       min=0, max=86400, step=1,
                                       description="连续超标多久才报；0 = 立即报（瞬时尖峰也会报）")
    template: str = ui_field("text", group="告警", title="告警模板", default="",
                             description="data/prefabs/告警模板/ 下的相对路径；留空 = 不用模板")
    title: str = ui_field("text", group="告警", title="告警标题", default="",
                          description="支持 {var} 占位（{value} / {metric} / {threshold} / {point_name}…）")
    content: str = ui_field("textarea", group="告警", title="告警正文", default="", rows=3,
                            description="支持 {var} 占位")
    dedup_seconds: float = ui_field("number", group="告警", title="合并窗口 (秒)",
                                    default=0, min=0, max=86400, step=1,
                                    description="同一目标在该窗口内重复超限只出一条告警；0 = 不合并")
    note: str = ui_field("textarea", group="告警", title="备注", default="", rows=2)


class RangeAlarmNode(DetectNodeBase):
    """数值范围告警：数值**跑出（或落进）一个区间**就报。

    与 `NumericAlarmNode` 的分工：那边是"单向越限"（>80 就报），这边是"正常区间"
    （60~80 之外都算异常）。写成区间更贴近现场的"额定范围"说法，而且上下限
    两个方向一次配完——用两个 `NumericAlarmNode`（一个 >max、一个 <min）也能
    表达，但那时要配两遍等级、模板、收件人，改一处还容易漏另一处。

    `mode` 两种：**区间外告警**（正常区间，越界就报，最常见）与
    **区间内告警**（危险区间，落在里面才报，如"转速落在共振区"）。

    数值来源与 `NumericAlarmNode` 相同：测点识别结果的 `parameter`
    （见 `alarm_processor._read_value`）；取不出数字就跳过、不报。
    """

    level: Literal["预警", "一般告警", "严重告警", "危急告警"] = ui_field(
        "select", group="告警", title="告警级别", default="严重告警", options=LEVEL_OPTIONS,
        description="越界后上报的级别")
    metric: str = ui_field("text", group="判据", title="监测项", default="",
                           description="这个数值叫什么（如 温度 / 电压）")
    unit: str = ui_field("text", group="判据", title="单位", default="")
    min_value: float = ui_field("number", group="判据", title="下限", default=0.0, step=0.1)
    max_value: float = ui_field("number", group="判据", title="上限", default=100.0, step=0.1,
                                description="上限必须不小于下限，否则区间是空的、永远不报")
    inclusive: bool = ui_field("checkbox", group="判据", title="含边界", default=True,
                               description="勾上 = 正好等于上下限也算**正常**（区间内）")
    mode: Literal["区间外告警", "区间内告警"] = ui_field(
        "select", group="判据", title="模式", default="区间外告警",
        options=["区间外告警", "区间内告警"],
        description="区间外=越界就报（最常见）；区间内=落在区间里才报（危险区间）")
    duration_seconds: float = ui_field("number", group="判据", title="持续 (秒)", default=0,
                                       min=0, max=86400, step=1,
                                       description="连续满足条件多久才报；0 = 立即报")
    template: str = ui_field("text", group="告警", title="告警模板", default="")
    title: str = ui_field("text", group="告警", title="告警标题", default="",
                          description="支持 {var} 占位（{value} / {metric} / {min} / {max}…）")
    content: str = ui_field("textarea", group="告警", title="告警正文", default="", rows=3)
    dedup_seconds: float = ui_field("number", group="告警", title="合并窗口 (秒)",
                                    default=0, min=0, max=86400, step=1)
    note: str = ui_field("textarea", group="告警", title="备注", default="", rows=2)


class ForwardNode(DetectNodeBase):
    """转发：把命中推给第三方平台（HTTP）。

    上级平台 / 客户自己的系统通常只认一个 HTTP 接口，这一步就是把告警按对方
    要的形状发出去。`body` 支持 `{var}` 占位。

    `retry` 只重投**网络层失败**（连不上 / 超时），收到非 2xx 响应**不重投**
    ——对方明确回了错，再发一遍通常还是错，还会把对方的错误计数打翻倍。
    """

    url: str = ui_field("text", group="转发", title="目标地址", default="",
                        placeholder="http://…", description="接收方的接口地址")
    method: str = ui_field("select", options=["POST", "PUT", "GET"], group="转发",
                           title="方法", default="POST")
    headers: dict = ui_field("json", group="转发", title="请求头", default={}, rows=4,
                             description='如 {"Content-Type": "application/json"}')
    body: str = ui_field("textarea", group="转发", title="请求体", default="", rows=5,
                         description="支持 {var} 占位；GET 时忽略")
    timeout: float = ui_field("number", min=1, max=300, group="转发", title="超时 (秒)",
                              default=5.0)
    retry: int = ui_field("number", group="转发", title="失败重试次数", default=0,
                          min=0, max=10, description="只重投网络层失败；收到非 2xx 不重投")
    note: str = ui_field("textarea", group="转发", title="备注", default="", rows=2)


class SmsNotifyNode(DetectNodeBase):
    """短信通知：命中后给一组手机号发短信。

    短信是**有成本、有打扰**的通道，所以带 `min_level` 闸门：只有达到该级别的
    告警才发。配流程时默认级别"严重"，别让"提示"级也去打扰值班的人。

    `receivers` 是手机号数组（不是逗号分隔的字符串）：要加要删一目了然，
    也不用约定转义规则。
    """

    min_level: Literal["预警", "一般告警", "严重告警", "危急告警"] = ui_field(
        "select", group="短信", title="最低级别", default="危急告警", options=LEVEL_OPTIONS,
        description="达到该级别才发；短信有打扰，默认只发严重")
    receivers: list[str] = ui_field("json", group="短信", title="接收手机号", default=[],
                                    rows=4, description='如 ["13800000000", …]')
    template_id: str = ui_field("text", group="短信", title="短信模板 ID", default="",
                                description="短信服务商侧的模板编号；留空则用下面的正文")
    content: str = ui_field("textarea", group="短信", title="短信内容", default="", rows=3,
                            description="支持 {var} 占位；填了模板 ID 时通常由模板决定正文")
    note: str = ui_field("textarea", group="短信", title="备注", default="", rows=2)


class EmailNotifyNode(DetectNodeBase):
    """邮件通知：命中后给一组邮箱发邮件。

    与短信同构（`min_level` 闸门 + 收件人数组），区别只在正文更长、能带附件。
    `attach_snapshot=True` 时把 `EvidenceNode` 存下的那张证据图作为附件——
    所以**邮件节点要放在留存节点之后**，否则没有图可带（顺序按树上的先后）。
    """

    min_level: Literal["预警", "一般告警", "严重告警", "危急告警"] = ui_field(
        "select", group="邮件", title="最低级别", default="一般告警", options=LEVEL_OPTIONS,
        description="达到该级别才发")
    to: list[str] = ui_field("json", group="邮件", title="收件人", default=[], rows=4,
                             description='邮箱数组，如 ["ops@example.com", …]')
    subject: str = ui_field("text", group="邮件", title="标题", default="",
                            description="支持 {var} 占位")
    body: str = ui_field("textarea", group="邮件", title="正文", default="", rows=5,
                         description="支持 {var} 占位")
    attach_snapshot: bool = ui_field("checkbox", group="邮件", title="带上证据图",
                                     default=True,
                                     description="把抓拍留存的那张图作为附件；"
                                                 "本节点要排在「留存」之后才有图可带")
    note: str = ui_field("textarea", group="邮件", title="备注", default="", rows=2)
