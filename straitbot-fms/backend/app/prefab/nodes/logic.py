"""组合节点：子节点激活策略（规则链 / 编排的核心）。"""
from __future__ import annotations

from typing import ClassVar

from ..base import Context, NodeBase


class CompositeNode(NodeBase):
    """组合节点基类（中间类，不注册）。策略由子类覆写 _activate_children。"""

    __type_name__: ClassVar[str | None] = None


class Sequence(CompositeNode):
    """顺序链：子节点按序激活，任一失败则整链中断并标记错误。"""

    def _activate_children(self, ctx: Context) -> None:
        for c in self._children:
            c.activate(ctx)
            if c.state == "error":
                raise RuntimeError(f"Sequence 子节点 {c.name or c.type} 失败: {c.error}")


class Parallel(CompositeNode):
    """并行：所有子节点全部激活，单个失败不影响其它子节点。"""

    def _activate_children(self, ctx: Context) -> None:
        for c in self._children:
            c.activate(ctx)


class Selector(CompositeNode):
    """选择：依次尝试子节点，遇到第一个激活成功的即停止（可用作条件分支）。"""

    def _activate_children(self, ctx: Context) -> None:
        for c in self._children:
            c.activate(ctx)
            if c.state == "active":
                return
