"""算法检测节点：**每种视觉算法一个 `DetectorNode` 子类**。

与"一个通用节点 + 算法下拉"的旧做法不同，这里用继承表达算法身份：

    DetectorNode（detect.py，抽象基类，不注册；共性：阈值 / 类别白名单 / 最多结果数）
      ├ StateRecognitionDetector   状态识别（共性：期望状态）
      │   ├ SwitchStateNode        开关分合状态   switch_state
      │   ├ IndicatorLightNode     指示灯状态     indicator_light
      │   ├ CabinetDoorNode        柜门开合       cabinet_door
      │   └ ValveStateNode         阀门状态       valve_state
      ├ MeterReadingDetector      表计读数（共性：单位 / 量程 / 小数位）
      │   ├ MeterPointerNode      指针表读数     meter_pointer
      │   ├ MeterDigitalNode      数字表读数     meter_digital
      │   ├ MeterLevelNode        液位计读数     meter_level
      │   └ CounterReadNode       计数器读数     counter_read
      ├ DefectDetector            缺陷检测（共性：最小缺陷面积占比）
      │   ├ InsulatorDamageNode   绝缘子破损     insulator_damage
      │   ├ EquipmentRustNode     设备锈蚀       equipment_rust
      │   ├ CableDamageNode       线缆破损       cable_damage
      │   └ WaterLeakNode         渗漏水渍       water_leak
      └ SafetyAlarmDetector       安全告警（共性：最小目标框占比）
          ├ PersonIntrusionNode   人员入侵       person_intrusion
          ├ SmokeFireNode         烟雾火焰       smoke_fire
          ├ ForeignObjectNode     异物悬挂       foreign_object
          └ HelmetCheckNode       安全帽佩戴     helmet_check

`algorithm_id` 与 `data/algorithms.json` 的 id **一一对应**（也是执行侧
`DetectEvent.algorithm` 的取值）；中文名 / 颜色 / 描述以算法目录为准，本文件
只负责"这个算法在流程里要配哪些字段"。

**给单个算法加专属字段**：直接在具体子类上用 `ui_field` 声明即可，前端检视器
自动渲染，不用动基类、不用动前端。例如指示灯独有的「期望灯色」就声明在
`IndicatorLightNode` 上而不是状态识别基类上——只有它用得到。

⚠️ 类别基类里的这些配置字段目前只落在编排侧（被 schema 表单读写），执行侧
真正跑算法时再消费它们，与 detect.py 其余节点"编排先行"的现状一致。
"""
from __future__ import annotations

from typing import ClassVar

from ..base import ui_field
from .detect import DetectorNode


# ============================================================ 类别基类（不注册）

class StateRecognitionDetector(DetectorNode):
    """状态识别类算法的共同基类（中间类，不注册）：识别"设备现在是什么状态"。"""

    __type_name__: ClassVar[str | None] = None

    expected_state: str = ui_field(
        "text", group="状态", title="期望状态", default="",
        description='识别后期望看到的状态，如「合闸」「红灯亮」「关门」；'
                    '留空 = 只识别记录，不与期望值比对')


class MeterReadingDetector(DetectorNode):
    """表计读数类算法的共同基类（中间类，不注册）：读出一个连续数值。"""

    __type_name__: ClassVar[str | None] = None

    unit: str = ui_field("text", group="量程", title="单位", default="",
                         description="如 ℃ / A / kV / m；只作展示与告警正文拼接")
    range_min: float = ui_field("number", group="量程", title="量程下限", default=0.0, step=0.1,
                                description="表计量程下限；读数超出量程通常视为误读")
    range_max: float = ui_field("number", group="量程", title="量程上限", default=0.0, step=0.1,
                                description="表计量程上限；0 = 不设上限")
    decimals: int = ui_field("number", group="量程", title="小数位数", default=0,
                             min=0, max=6, description="读数保留几位小数")


class DefectDetector(DetectorNode):
    """缺陷检测类算法的共同基类（中间类，不注册）：画面里有没有某种缺陷。"""

    __type_name__: ClassVar[str | None] = None

    min_area_ratio: float = ui_field(
        "number", group="缺陷", title="最小缺陷面积占比", default=0.0,
        min=0, max=1, step=0.01,
        description="缺陷框面积占画面比例低于该值则忽略（滤远处噪点）；0 = 不过滤")


class SafetyAlarmDetector(DetectorNode):
    """安全告警类算法的共同基类（中间类，不注册）：禁入 / 烟火 / 佩戴等。"""

    __type_name__: ClassVar[str | None] = None

    min_box_ratio: float = ui_field(
        "number", group="目标", title="最小目标框占比", default=0.0,
        min=0, max=1, step=0.01,
        description="目标框面积占画面比例低于该值则忽略（滤远处误检）；0 = 不过滤")


# ============================================================ 状态识别

class SwitchStateNode(StateRecognitionDetector):
    """开关分合状态：识别断路器 / 刀闸的分闸、合闸位置。"""

    algorithm_id: ClassVar[str] = "switch_state"


class IndicatorLightNode(StateRecognitionDetector):
    """指示灯状态：识别指示灯亮 / 灭及颜色。"""

    algorithm_id: ClassVar[str] = "indicator_light"

    expected_color: str = ui_field(
        "select", group="状态", title="期望灯色", default="",
        options=["", "红", "黄", "绿", "蓝", "白"],
        description="需要判定灯色时选择；留空 = 只记录识别到的颜色")


class CabinetDoorNode(StateRecognitionDetector):
    """柜门开合：识别配电柜门是否关严。"""

    algorithm_id: ClassVar[str] = "cabinet_door"


class ValveStateNode(StateRecognitionDetector):
    """阀门状态：识别阀门手轮 / 手柄朝向。"""

    algorithm_id: ClassVar[str] = "valve_state"


# ============================================================ 表计读数

class MeterPointerNode(MeterReadingDetector):
    """指针表读数：读取指针式仪表的示数。"""

    algorithm_id: ClassVar[str] = "meter_pointer"


class MeterDigitalNode(MeterReadingDetector):
    """数字表读数：读取数码管 / 液晶读数。"""

    algorithm_id: ClassVar[str] = "meter_digital"


class MeterLevelNode(MeterReadingDetector):
    """液位计读数：读取液位、油位高度。"""

    algorithm_id: ClassVar[str] = "meter_level"


class CounterReadNode(MeterReadingDetector):
    """计数器读数：读取电表 / 水表累计读数。"""

    algorithm_id: ClassVar[str] = "counter_read"


# ============================================================ 缺陷检测

class InsulatorDamageNode(DefectDetector):
    """绝缘子破损：检测绝缘子裂纹、缺片、闪络痕迹。"""

    algorithm_id: ClassVar[str] = "insulator_damage"


class EquipmentRustNode(DefectDetector):
    """设备锈蚀：检测金属件锈蚀、掉漆。"""

    algorithm_id: ClassVar[str] = "equipment_rust"


class CableDamageNode(DefectDetector):
    """线缆破损：检测线缆外皮破损、老化。"""

    algorithm_id: ClassVar[str] = "cable_damage"


class WaterLeakNode(DefectDetector):
    """渗漏水渍：检测墙面 / 地面渗漏水痕。"""

    algorithm_id: ClassVar[str] = "water_leak"


# ============================================================ 安全告警

class PersonIntrusionNode(SafetyAlarmDetector):
    """人员入侵：检测禁入区域出现人员。"""

    algorithm_id: ClassVar[str] = "person_intrusion"


class SmokeFireNode(SafetyAlarmDetector):
    """烟雾火焰：检测烟雾、明火。"""

    algorithm_id: ClassVar[str] = "smoke_fire"


class ForeignObjectNode(SafetyAlarmDetector):
    """异物悬挂：检测设备上悬挂、堆积的异物。"""

    algorithm_id: ClassVar[str] = "foreign_object"


class HelmetCheckNode(SafetyAlarmDetector):
    """安全帽佩戴：检测作业人员是否佩戴安全帽。"""

    algorithm_id: ClassVar[str] = "helmet_check"
