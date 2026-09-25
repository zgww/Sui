"""配置类节点：把键值配置写入共享 Context，供整树其它节点读取。"""
from __future__ import annotations

from ..base import Context, NodeBase, ui_field


class ConfigNode(NodeBase):
    """激活时把 values 键值对写入 Context.kv，整树可见。

    典型用途：把站点/机器人/环境等公共配置与规则链统一组织进 prefab。
    """

    values: dict[str, str] = ui_field("kv", group="配置",
                                      description="键值对，写入 Context.kv")

    def on_active(self, ctx: Context) -> None:
        ctx.kv.update(self.values)
        ctx.emit("config", {"node": self.name, "values": dict(self.values)})
