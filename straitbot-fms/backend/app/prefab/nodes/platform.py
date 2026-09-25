"""平台对接配置节点：FMS 往旧平台（或第三方平台）上报巡检动作数据的地址与凭据。

挂在 `data/prefabs/robot.prefab.json` 的 `RobotConfig` 下（与 `HkPtzConfig`
同一层），因为"这台机器人把数据发给哪个平台"是**机器人属性**，不是某条巡检
任务的属性——换平台就是改这一个节点，不用去动每条计划/每个执行器。

## 为什么是一个节点而不是一堆环境变量

上报地址、鉴权头、超时、重试这些必须跟着"机器人实例"走，而机器人实例本来就
是 prefab 树（`Robot.from_prefab`）。放进 `.env` 的话，同一份镜像部署到车间 A
和车间 B 要改环境变量，而 prefab 是随现场数据一起备份/迁移的。

## 与「任务执行器」的关系

`TaskExecutorNode` 拿到一条动作数据后按 `detect_type` 分流，两个去处都由本节点
给地址，都用本节点的超时/重试/鉴权头：

- `detect_type=platform` 的动作数据 -> `upload_url`（旧平台 cmd=104 的接收口）；
- `detect_type=fms` 的检测框检测 -> `infer_url`（**外部推理服务**）。

⚠️ **算法推理不在本系统里跑**：本系统只描述"用哪个算法、什么参数"（检测流程树），
真正算的那一步是一次 HTTP POST 到 `infer_url`（见 `prefab/task_executor.py`）。
两个地址放同一个节点，是因为它们都属于"这台机器跟外界怎么对接"这一件事——
分开成两个节点只会让现场多改一处。
"""
from __future__ import annotations

from typing import ClassVar

from ..base import Context, NodeBase, ui_field


class PlatformConfigNode(NodeBase):
    """旧平台（cmd=104 的对端）上报配置。

    `upload_url` 留空 = **不真发**：执行器会记日志并跳过，不会去猜一个地址。
    这条"宁可不发也不乱发"的约定是故意的——把巡检数据 POST 到一个猜出来的
    地址，比不发更糟（对方可能收下一堆格式不对的东西）。
    """

    __type_name__: ClassVar[str] = "PlatformConfig"

    upload_url: str = ui_field(
        "text", group="平台", title="上报地址", default="",
        placeholder="http://10.0.0.5:8080/api/inspection/report/result",
        description="动作数据上报的 POST 地址。**留空 = 不真发**（执行器只记日志）；"
                    "旧平台的接收口是 `/api/inspection/report/result`（cmd=104 同款）")
    infer_url: str = ui_field(
        "text", group="推理服务", title="推理接口地址", default="",
        placeholder="http://10.0.0.6:9000/infer",
        description="**外部推理服务**的 POST 地址（算法推理不在本系统里跑，见"
                    "「任务执行器」的说明）。留空 = 检测框那一路无法执行，执行器只记日志。"
                    "请求体形状见 `prefab/task_executor.py::infer_payload`")
    auth_header: str = ui_field(
        "text", group="平台", title="鉴权头", default="",
        placeholder="Authorization: Bearer xxx",
        description="原样附上去的一整行头，形如 `名字: 值`；留空则不带鉴权。"
                    "用整行而不是「键/值」两个字段，是为了能应付非标头（多个头用 `;` 分隔）。"
                    "**上报平台与推理服务共用这一个头**")
    timeout: float = ui_field(
        "number", group="平台", title="超时（秒）", default=5.0,
        min=0.5, max=120, step=0.5,
        description="单次上报的 HTTP 超时；超了就按失败重试")
    retry: int = ui_field(
        "number", group="平台", title="重试次数", default=2,
        min=0, max=10, step=1,
        description="失败后的重试次数（不含首次）。重试全失败则留待下一轮轮询再试")
    verify_tls: bool = ui_field(
        "checkbox", group="平台", title="校验 TLS 证书", default=True,
        description="上报地址是 https 时校验证书；自签名证书的内网平台可取消勾选")
    enabled: bool = ui_field(
        "checkbox", group="通用", default=True,
        description="停用后该节点及其子树不参与运行")

    def on_active(self, ctx: Context) -> None:
        """把自己写进 Context，`TaskExecutorNode` 优先从 Context 取。

        找不到本节点时执行器会回落到"按 robot.prefab.json 现找"，所以这里
        即使没被激活（比如手工只跑了执行器那棵树）也不至于完全没人可用。
        """
        info = self.info()
        ctx.kv["platform.upload_url"] = info["upload_url"]
        ctx.kv["platform.infer_url"] = info["infer_url"]
        ctx.kv["platform.auth_header"] = info["auth_header"]
        ctx.kv["platform.timeout"] = str(info["timeout"])
        ctx.kv["platform.retry"] = str(info["retry"])
        ctx.kv["platform.verify_tls"] = str(info["verify_tls"])
        ctx.emit("platform_config", {"node": self.name, **info})

    def info(self) -> dict:
        """普通 dict 形式的配置（执行器/状态接口用）。"""
        return {
            "upload_url": str(self.upload_url or "").strip(),
            "infer_url": str(self.infer_url or "").strip(),
            "auth_header": str(self.auth_header or "").strip(),
            "timeout": float(self.timeout or 5.0),
            "retry": int(self.retry or 0),
            "verify_tls": bool(self.verify_tls),
        }

    @property
    def configured(self) -> bool:
        """配没配上报地址。执行器据此决定"真发"还是"只记日志"。"""
        return bool(self.info()["upload_url"])

    @property
    def infer_configured(self) -> bool:
        """配没配推理服务地址（fms 分支能不能真跑）。"""
        return bool(self.info()["infer_url"])
