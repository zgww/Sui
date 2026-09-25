"""注册表访问、prefab spec -> 节点树构建、schema 聚合。"""
from __future__ import annotations

from typing import Any

from .base import NodeBase


class PrefabError(Exception):
    """prefab 加载/构建相关错误。"""


class UnknownNodeType(PrefabError):
    """prefab 引用了未注册的节点类型。"""

    def __init__(self, type_name: str) -> None:
        self.type_name = type_name
        super().__init__(f"未知节点类型: {type_name}（是否忘了继承 NodeBase？）")


def registered_types() -> dict[str, type[NodeBase]]:
    """所有已注册的节点类型（类名 -> 类）。"""
    return dict(NodeBase._registry)


def build(spec: dict[str, Any]) -> NodeBase:
    """按 prefab 节点 spec 递归构建节点树实例。

    spec 结构：{"type": "Sequence", "properties": {...}, "children": [...]}
    校验失败抛 pydantic ValidationError / UnknownNodeType。
    """
    type_name = spec.get("type")
    cls = NodeBase._registry.get(type_name)
    if cls is None:
        raise UnknownNodeType(str(type_name))
    props = spec.get("properties") or {}
    children_spec = list(spec.get("children") or [])
    node = cls(**props, children=children_spec)
    for cs in children_spec:
        child = build(cs)
        child._parent = node
        node._children.append(child)
    return node


def node_schema(node_type: str) -> dict[str, Any]:
    """单个节点类型的 JSON Schema（含 ui 元数据）。"""
    cls = NodeBase._registry.get(node_type)
    if cls is None:
        raise UnknownNodeType(node_type)
    return _visible_schema(cls)


def schema_for_all() -> dict[str, dict[str, Any]]:
    """所有已注册节点类型的 schema，供前端 inspector 渲染。

    每个类型额外带 base（直接父类名，NodeBase 或中间基类如 CompositeNode），
    前端据此渲染"类型继承树"选择器。
    """
    out: dict[str, dict[str, Any]] = {}
    for name, cls in NodeBase._registry.items():
        doc = (cls.__doc__ or "").strip()
        # 向上找第一个用户自定义的中间基类（跳过 pydantic/object），否则 NodeBase
        base = "NodeBase"
        for b in cls.__mro__[1:]:
            if b is NodeBase:
                break
            if b.__name__ != "NodeBase" and b.__module__.startswith("app.prefab"):
                base = b.__name__
                break
        out[name] = {
            "schema": _visible_schema(cls),
            "description": doc.splitlines()[0] if doc else "",
            "base": base,
        }
    return out


def all_node_classes() -> set[type[NodeBase]]:
    """NodeBase 的全部子类（含 `__type_name__ = None` 的中间基类）。"""
    out: set[type[NodeBase]] = set()

    def walk(cls: type[NodeBase]) -> None:
        for sub in cls.__subclasses__():
            if sub not in out:
                out.add(sub)
                walk(sub)

    walk(NodeBase)
    return out


def find_node_class(name: str) -> type[NodeBase] | None:
    """按类名找节点类（中间基类不注册，不能只查 `_registry`）。"""
    for cls in all_node_classes():
        if cls.__name__ == name:
            return cls
    return None


def _schema_entry(name: str, cls: type[NodeBase]) -> dict[str, Any]:
    doc = (cls.__doc__ or "").strip()
    # 直接父类名（前端类型选择器分组用）；只认真正定义在本项目里的中间基类
    base = "NodeBase"
    for b in cls.__mro__[1:]:
        if b is NodeBase:
            break
        if b.__name__ != "NodeBase" and b.__module__.startswith("app.prefab"):
            base = b.__name__
            break
    return {
        "schema": _visible_schema(cls),
        "description": doc.splitlines()[0] if doc else "",
        "base": base,
        # 废弃节点不下发到"添加节点"目录，但类仍注册、旧数据可解析
        "hidden": bool(getattr(cls, "__hidden__", False)),
    }


def _visible_schema(cls: type[NodeBase]) -> dict[str, Any]:
    """节点 schema，并摘掉 `__hidden_fields__` 里声明下线的字段。

    这些字段**仍在模型上**（旧 prefab 带着它们照样能 build），只是不下发给
    检视器 —— 前端表单按 schema.properties 渲染，摘掉即等于"界面上没有这个属性"。
    `required` 也要一起摘：否则表单会去校验一个渲染不出来的必填项。
    """
    schema = cls.model_json_schema()
    hidden = tuple(getattr(cls, "__hidden_fields__", ()) or ())
    if hidden:
        props = schema.get("properties")
        if isinstance(props, dict):
            for f in hidden:
                props.pop(f, None)
        req = schema.get("required")
        if isinstance(req, list):
            schema["required"] = [r for r in req if r not in hidden]
    return schema


def schema_for_base(base_name: str) -> dict[str, dict[str, Any]]:
    """所有**是 `base_name` 子类**的已注册节点类型的 schema（按继承关系过滤）。

    用 issubclass 而非直接父类名：节点可以隔一层甚至多层中间基类（如
    PersonIntrusionNode -> SafetyAlarmDetector -> DetectorNode -> DetectNodeBase），
    仍应被检测树的 node-types 收进来。中间基类自身 `__type_name__ = None`
    不注册，故不会混进结果。
    """
    base_cls = find_node_class(base_name)
    out: dict[str, dict[str, Any]] = {}
    for name, cls in NodeBase._registry.items():
        if base_cls is None or issubclass(cls, base_cls):
            out[name] = _schema_entry(name, cls)
    return out


def tree_to_dict(node: NodeBase, *, with_state: bool = True) -> dict[str, Any]:
    """节点实例 -> 可序列化 dict（前端展示/状态标注用）。"""
    data = node.model_dump(exclude={"children"})
    result: dict[str, Any] = dict(data)
    if with_state:
        result["_state"] = node.state
        result["_error"] = node.error
    result["children"] = [tree_to_dict(c, with_state=with_state) for c in node.child_nodes]
    return result
