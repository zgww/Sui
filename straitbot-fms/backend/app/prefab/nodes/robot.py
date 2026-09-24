"""机器人配置节点：在 prefab 里描述一台机器人的基础信息。

由 :class:`app.rail.robot.Robot` 加载（data/prefabs/robot.prefab.json），读取 ip/port 等用于
建立 BoardSrv 连接。字段类型化，前端 inspector 依据 JSON Schema 自动渲染表单，新增字段无需改前端。

命名约定（与 NodeBase 通用字段避让）：
- 机器人名称直接复用基类的 ``name``；
- 节点类型 ``type`` 是基类保留字段（= 注册名，只读），故"机型"字段命名为 ``robot_type``；
- 机器人唯一标识用 ``robot_id``，避免与 Python 内置/通用 ``id`` 混淆。
"""
from __future__ import annotations

from typing import ClassVar

from ..base import Context, NodeBase, ui_field

# 支持的机型（后续新增机型在此追加，inspector 下拉自动更新）
ROBOT_TYPES = ["挂轨机器人", "轮式机器人"]


class RobotConfig(NodeBase):
    """一台机器人的基础配置：id / 名称 / 版本 / ip / 端口 / 机型。

    名称取通用字段 ``name``；连接信息与机型见下方字段。可作为 prefab 根节点，
    其下再挂规则链、定时任务等子节点。
    """

    __type_name__: ClassVar[str] = "RobotConfig"

    robot_id: str = ui_field("text", group="机器人", placeholder="如 R001",
                            description="机器人唯一标识")
    version: str = ui_field("text", group="机器人", default="",
                            description="固件/硬件版本，留空则在连接后由下位机上报填充")
    robot_type: str = ui_field("select", group="机器人", options=ROBOT_TYPES,
                               default="挂轨机器人", description="机型")
    ip: str = ui_field("text", group="连接", default="127.0.0.1",
                       placeholder="控制板 IP", description="控制板 TCP 地址")
    port: int = ui_field("number", group="连接", default=50000, min=1, max=65535, step=1,
                         description="控制板 TCP 端口（真机为 server，本机连接过去）")
    fms_host: str = ui_field("text", group="FMS", default="",
                            placeholder="192.168.1.100:8000",
                            description="FMS 服务的 ip:port，算法服务回调时用这个地址")
    task_min_battery: float = ui_field("number", group="任务", title="允许任务电量阈值(%)", default=0.0,
                            min=0, max=100, step=1,
                            description="电量低于此值且未在充电时，拒绝下发巡检任务（返回 low_battery）。0=不限制")
    heartbeat_interval: float = ui_field("number", group="连接", default=2.0,
                                         min=0.2, max=30, step=0.5,
                                         description="心跳周期（秒）。下位机约 3s 收不到任何"
                                                     "数据就主动断开，所以必须明显小于 3s")
    lift_motor_id: int = ui_field("number", group="连接", default=1,
                                  min=0, max=255, step=1,
                                  description="伸缩杆（升降）电机 ID。0x0E 上发里 ID 不等于它"
                                              "会被忽略；真机实测上报的是 0，按现场约定填")

    # ---------------------------------------------------------------- 控制板初始化（0x01）
    # 连接建立（含每次重连）后由 Robot 下发 0x01「初始化控制板」时携带的参数。
    # 字段与协议 0x01 报文一一对应，也与前端下位机配置项（configSchema.ts）对齐：
    #   director↔director · is_ring↔is_ring · track_photo_avoid↔obstacle_light
    #   ultrasonic_avoid↔obstacle_sound · low_battery_threshold↔battery.low
    #   x_min/x_max↔limit_x0/limit_x1
    # 全部带默认值，存量 prefab 文件不加这些字段也能正常加载（走默认）。
    init_on_connect: bool = ui_field("checkbox", group="控制板初始化", default=True,
                                     description="连接建立后自动下发 0x01 初始化控制板（每次重连都会重发）")
    board_id: int = ui_field("number", group="控制板初始化", default=0, min=0, max=255, step=1,
                             description="控制板 ID（协议字段 ID，单机通常为 0）")
    director: int = ui_field("select", group="控制板初始化", default=0,
                             options=[{"label": "正向", "value": 0}, {"label": "反向", "value": 1}],
                             description="轨道方向：0-正向 1-反向")
    is_ring: bool = ui_field("checkbox", group="控制板初始化", default=False,
                             description="环形轨道：环形轨道无终点限位")
    track_photo_avoid: bool = ui_field("checkbox", group="控制板初始化", default=True,
                                       description="轨道光电避障：0-关 1-开")
    ultrasonic_avoid: bool = ui_field("checkbox", group="控制板初始化", default=True,
                                      description="超声波避障：0-关 1-开")
    low_battery_threshold: int = ui_field("number", group="控制板初始化", default=30,
                                          min=0, max=100, step=1,
                                          description="低电量阈值（0-100，%）")
    x_min: int = ui_field("number", group="控制板初始化", default=-2_147_483_648,
                          description="X 轴最小限位（下位机坐标单位；取 int32 最小值=不设置）")
    x_max: int = ui_field("number", group="控制板初始化", default=2_147_483_647,
                          description="X 轴最大限位（取 int32 最大值=不设置）")
    y_min: int = ui_field("number", group="控制板初始化", default=-2_147_483_648,
                          description="Y 轴最小限位（取 int32 最小值=不设置）")
    y_max: int = ui_field("number", group="控制板初始化", default=2_147_483_647,
                          description="Y 轴最大限位（取 int32 最大值=不设置）")
    z_min: int = ui_field("number", group="控制板初始化", default=-32_768,
                          description="Z 轴最小限位（取 int16 最小值=不设置）")
    z_max: int = ui_field("number", group="控制板初始化", default=32_767,
                          description="Z 轴最大限位（取 int16 最大值=不设置）")

    def on_active(self, ctx: Context) -> None:
        info = self.info()
        ctx.kv.update({
            "robot.id": info["robot_id"],
            "robot.name": info["name"],
            "robot.ip": info["ip"],
            "robot.port": str(info["port"]),
            "robot.type": info["robot_type"],
            "robot.fms_host": info["fms_host"],
        })
        ctx.emit("robot_config", {"node": self.name, **info})

    def info(self) -> dict:
        """以普通 dict 返回机器人基础信息（供 Robot 构造连接与展示）。"""
        return {
            "robot_id": self.robot_id,
            "name": self.name,
            "version": self.version,
            "robot_type": self.robot_type,
            "ip": self.ip,
            "port": int(self.port),
            "fms_host": self.fms_host,
        }

    # ---------------------------------------------------------------- 0x01 初始化
    def init_params(self) -> dict:
        """0x01 初始化控制板的参数快照（协议字段名，bool → 0/1）。"""
        return {
            "id": int(self.board_id),
            "director": 1 if int(self.director) else 0,
            "is_ring": 1 if self.is_ring else 0,
            "track_photo_avoid": 1 if self.track_photo_avoid else 0,
            "ultrasonic_avoid": 1 if self.ultrasonic_avoid else 0,
            "low_battery_threshold": int(self.low_battery_threshold),
            "x_min": int(self.x_min), "x_max": int(self.x_max),
            "y_min": int(self.y_min), "y_max": int(self.y_max),
            "z_min": int(self.z_min), "z_max": int(self.z_max),
        }

    def init_request(self):
        """按本配置构造 0x01 初始化控制板消息对象。"""
        from app.rail.messages import InitRequest  # 延迟导入：避免 prefab 注册期拉入 rail 包
        return InitRequest(**self.init_params())
