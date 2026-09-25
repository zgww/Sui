"""升降杆配置节点：描述这台机器人有没有升降杆、以及它的行程范围。

挂在 `data/prefabs/robot.prefab.json` 的 `RobotConfig` 下（与 `HkPtzConfig`、
`PlatformConfig` 同一层），因为"这台机器人带不带升降杆、行程多大"是**机器人硬件属性**，
跟着机器人实例走，不是某条巡检任务的属性。

与根节点上已有的 `lift_motor_id`（0x0E 电机 ID）分工：
- `lift_motor_id`：告诉状态机 0x0E 上发帧里哪个电机才是升降杆（硬件 ID 过滤）；
- 本节点：告诉运行时**这台机有没有升降杆**、**升降行程的上下限**（发升降指令时限位、
  无升降杆的机型直接跳过升降动作）。
"""
from __future__ import annotations

from typing import ClassVar

from ..base import Context, NodeBase, ui_field


class LiftConfigNode(NodeBase):
    """升降杆（伸缩杆）配置：有无升降杆 + 行程上下限。"""

    __type_name__: ClassVar[str] = "LiftConfig"

    has_lift: bool = ui_field(
        "checkbox", group="升降杆", title="有无升降杆", default=False,
        description="这台机器人是否配备升降杆（伸缩杆）。无升降杆的机型，巡检中的"
                    "升降动作会被直接跳过")
    min_distance: float = ui_field(
        "number", group="升降杆", title="最小距离 (m)", default=0.0,
        min=0, max=10, step=0.01,
        description="升降杆最低位置（m）。下发升降目标时会被钳制到不小于此值")
    max_distance: float = ui_field(
        "number", group="升降杆", title="最大距离 (m)", default=0.0,
        min=0, max=10, step=0.01,
        description="升降杆最高位置（m）。下发升降目标时会被钳制到不大于此值")
    enabled: bool = ui_field(
        "checkbox", group="通用", default=True,
        description="停用后该节点及其子树不参与运行")

    def on_active(self, ctx: Context) -> None:
        info = self.info()
        ctx.kv["lift.has_lift"] = str(info["has_lift"])
        ctx.kv["lift.min_distance"] = str(info["min_distance"])
        ctx.kv["lift.max_distance"] = str(info["max_distance"])
        ctx.emit("lift_config", {"node": self.name, **info})

    def info(self) -> dict:
        """普通 dict 形式的配置（状态接口/运行时用）。"""
        return {
            "has_lift": bool(self.has_lift),
            "min_distance": float(self.min_distance or 0.0),
            "max_distance": float(self.max_distance or 0.0),
        }
