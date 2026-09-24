"""海康相机（云台）配置节点：在 prefab 里描述一台海康相机的连接参数。

由 :class:`app.rail.HkPtz.HkPtz` 加载（data/prefabs/robot.prefab.json），读取
ip/port/username/password/sdk_path 等，通过海康原生 **HCNetSDK**（``库文件/HCNetSDK.dll``，
ctypes 调用）登录并控制相机。字段类型化，前端 inspector 依据 JSON Schema 自动渲染表单，
新增字段无需改前端。

命名约定：节点类型 ``type`` 是基类保留字段（= 注册名，只读）；相机名称直接复用基类
``name``。``password`` 属敏感信息，会随 prefab 明文落盘（与既有配置机制一致），
部署时注意 data/prefabs 目录的访问权限。

注意：HCNetSDK 登录端口是设备 SDK 服务端口（默认 **8000**），不是 ISAPI/HTTP 的 80。
"""
from __future__ import annotations

from typing import ClassVar

from ..base import Context, NodeBase, ui_field


class HkPtzConfig(NodeBase):
    """一台海康相机的连接配置：ip / SDK 端口 / 用户名 / 密码 / 通道号 / SDK 库路径。

    可作为 ``RobotConfig`` 的子节点挂在机器人 prefab 树下，供 :class:`HkPtz` 登录使用。
    """

    __type_name__: ClassVar[str] = "HkPtzConfig"

    ip: str = ui_field("text", group="连接", default="192.168.1.64",
                       placeholder="相机 IP", description="相机 IP 地址")
    port: int = ui_field("number", group="连接", default=8000, min=1, max=65535, step=1,
                         description="HCNetSDK 登录端口（设备 SDK 服务端口，默认 8000）")
    http_port: int = ui_field("number", group="连接", default=80, min=1, max=65535, step=1,
                              description="ISAPI/HTTP 端口（云台绝对定位走 HTTP ISAPI，默认 80）")
    username: str = ui_field("text", group="认证", default="admin",
                             placeholder="登录用户名", description="相机登录用户名")
    password: str = ui_field("text", group="认证", default="",
                             placeholder="登录密码", description="相机登录密码")
    channel: int = ui_field("number", group="通道", default=1, min=1, max=512, step=1,
                            description="云台/抓图通道号（IPC 通常为 1；NVR 下挂为数字通道号）")
    sdk_path: str = ui_field("text", group="SDK", default="",
                             placeholder="留空则在 docs/HCNetSDK*/库文件 下自动查找",
                             description="HCNetSDK 库目录（含 HCNetSDK.dll / HCNetSDKCom）；留空自动探测")

    def on_active(self, ctx: Context) -> None:
        info = self.info()
        ctx.kv.update({
            "hkptz.name": info["name"],
            "hkptz.ip": info["ip"],
            "hkptz.port": str(info["port"]),
            "hkptz.username": info["username"],
            "hkptz.channel": str(info["channel"]),
        })
        ctx.emit("hkptz_config", {"node": self.name, **info})

    def info(self) -> dict:
        """以普通 dict 返回相机连接信息（供 HkPtz 登录与展示）。"""
        return {
            "name": self.name,
            "ip": self.ip,
            "port": int(self.port),
            "http_port": int(self.http_port),
            "username": self.username,
            "password": self.password,
            "channel": int(self.channel),
            "sdk_path": self.sdk_path,
        }
