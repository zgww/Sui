"""动作类节点：激活时执行具体动作（日志 / HTTP 请求）。"""
from __future__ import annotations

import httpx

from ..base import Context, NodeBase, ui_field

class 每日删除目录动作 (NodeBase):
    """每日某时删除目录

    message 支持 {var} 占位，从 Context.kv 取值替换。
    """

    hour: str = ui_field("text", group="调度",
                            description="小时, 如  5")
    dir: str = ui_field("text", group="调度",
                            description="目录, 如  data/images")

    def _render(self, ctx: Context) -> str:
        text = self.message
        for k, v in ctx.kv.items():
            text = text.replace("{" + k + "}", str(v))
        return text

    def on_active(self, ctx: Context) -> None:
        self.hour
        self.dir 
        msg = self._render(ctx)
        print(f"[prefab] {self.name or self.type}: {msg}")
        ctx.emit("log", {"node": self.name, "message": msg})
        self.thread = threading.Thread()

    def on_deactive(self, ctx: Context) -> None:
        self.thread.stop()



class KeepAliveAction(NodeBase):
    """写一条日志：输出到服务端标准输出并 emit "log" 事件。

    message 支持 {var} 占位，从 Context.kv 取值替换。
    """

    processMark: str = ui_field("text", group="动作",
                            description="保活进程标记")

    def _render(self, ctx: Context) -> str:
        text = self.message
        for k, v in ctx.kv.items():
            text = text.replace("{" + k + "}", str(v))
        return text

    def on_active(self, ctx: Context) -> None:
        msg = self._render(ctx)
        print(f"[prefab] {self.name or self.type}: {msg}")
        ctx.emit("log", {"node": self.name, "message": msg})


class LogAction(NodeBase):
    """写一条日志：输出到服务端标准输出并 emit "log" 事件。

    message 支持 {var} 占位，从 Context.kv 取值替换。
    """

    message: str = ui_field("text", group="动作",
                            description="日志内容，支持 {var} 占位（来自 Context.kv）")

    def _render(self, ctx: Context) -> str:
        text = self.message
        for k, v in ctx.kv.items():
            text = text.replace("{" + k + "}", str(v))
        return text

    def on_active(self, ctx: Context) -> None:
        msg = self._render(ctx)
        print(f"[prefab] {self.name or self.type}: {msg}")
        ctx.emit("log", {"node": self.name, "message": msg})


class HttpAction(NodeBase):
    """发起一次 HTTP 请求（激活时执行）。"""

    url: str = ui_field("text", group="请求", placeholder="http://…")
    method: str = ui_field("select", options=["GET", "POST", "PUT", "DELETE"],
                           group="请求", default="GET")
    body: str = ui_field("textarea", group="请求", description="请求体（可选）",
                         default="")
    timeout: float = ui_field("number", min=1, max=300, group="请求", default=5.0)
    expect_status: int = ui_field("number", min=100, max=599, group="请求", default=0,
                                  description="期望状态码，0 表示不校验")

    def on_active(self, ctx: Context) -> None:
        resp = httpx.request(
            self.method, self.url,
            content=self.body or None,
            timeout=self.timeout,
        )
        if self.expect_status and resp.status_code != self.expect_status:
            raise RuntimeError(
                f"HTTP {resp.status_code} != 期望 {self.expect_status}（{self.url}）")
        ctx.emit("http", {"node": self.name, "url": self.url,
                          "status": resp.status_code})
