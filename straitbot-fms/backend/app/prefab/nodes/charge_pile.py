"""充电桩配置节点：描述这台机器人充电桩的坐标与所在楼层。

挂在 `data/prefabs/robot.prefab.json` 的 `RobotConfig` 下（与 `HkPtzConfig`、
`PlatformConfig`、`LiftConfig` 同层）——"充电桩在哪"是机器人现场硬件布局，跟着机器人
实例走，不是某条巡检任务的属性。

原先「移动到最近的充电桩」是个 TODO 桩（见 `rail/robot.py`）：依赖导航层知道桩坐标。
本节点给出桩的弧长坐标与楼层后，主机回桩即可 `_goto_x(桩x)`（跨楼层时再走切楼层子机）。
"""
from __future__ import annotations

from typing import ClassVar

from ..base import Context, NodeBase, ui_field


class ChargePileConfigNode(NodeBase):
    """充电桩配置：桩坐标（弧长 m）+ 所在楼层。"""

    __type_name__: ClassVar[str] = "ChargePile"

    x: float = ui_field(
        "number", group="充电桩", title="桩坐标 X（弧长 m）", default=0.0,
        min=0, max=1000, step=0.01,
        description="充电桩沿轨弧长坐标（m）。回桩时机器人走到此 X；单位与巡检航点的 pose.x 一致")
    floor: int = ui_field(
        "number", group="充电桩", title="所在楼层", default=0,
        min=-10, max=100, step=1,
        description="充电桩所在楼层编号（与巡检任务里的楼层一致）；跨楼层回桩时据此切楼层")
    enabled: bool = ui_field(
        "checkbox", group="通用", default=True,
        description="停用后该节点及其子树不参与运行")

    def on_active(self, ctx: Context) -> None:
        info = self.info()
        ctx.kv["charge_pile.x"] = str(info["x"])
        ctx.kv["charge_pile.floor"] = str(info["floor"])
        ctx.emit("charge_pile_config", {"node": self.name, **info})

    def info(self) -> dict:
        """普通 dict 形式的配置（状态接口/运行时用）。"""
        return {
            "x": float(self.x or 0.0),
            "floor": int(self.floor or 0),
        }
