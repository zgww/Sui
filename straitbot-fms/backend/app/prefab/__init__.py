"""prefab 节点树系统：类定义即注册，schema 驱动 inspector，prefab.json 描述节点树。

对外用法：
    from app.prefab import build, PrefabLoader, PrefabRuntime, schema_for_all
"""
from . import nodes  # noqa: F401  # 触发节点类型注册（自动发现）
from .base import Context, NodeBase, ui_field
from .loader import PrefabLoader, PrefabTree
from .registry import (PrefabError, UnknownNodeType, build, node_schema,
                       registered_types, schema_for_all, tree_to_dict)
from .runtime import PrefabRuntime, get_runtime, init_runtime

__all__ = [
    "Context", "NodeBase", "ui_field",
    "PrefabLoader", "PrefabTree", "PrefabRuntime",
    "PrefabError", "UnknownNodeType",
    "build", "node_schema", "schema_for_all", "registered_types", "tree_to_dict",
    "get_runtime", "init_runtime",
]
