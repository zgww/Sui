"""prefab 节点基类：定义即注册 + schema UI 元数据约定。

新增一个节点类型的完整流程（前端零改动）：
  1. 在 app/prefab/nodes/ 下新建一个模块
  2. 继承 NodeBase，覆写 on_active / on_deactive 等生命周期钩子
  3. 字段用 ui_field() 声明 UI 元数据
注册、schema 聚合、加载器、前端 inspector 表单全部自动生效。
"""
from __future__ import annotations

from abc import ABC
from typing import Any, ClassVar, Optional, Type

from pydantic import BaseModel, ConfigDict, Field, PrivateAttr


# ---------------------------------------------------------------- Context

class Context:
    """节点树共享上下文：KV 存储 + 轻量事件总线。

    节点之间不直接互相引用，通过 Context 通信，保证 prefab 可移植、可复制。
    """

    def __init__(self) -> None:
        self.kv: dict[str, Any] = {}
        self._handlers: dict[str, list[Any]] = {}

    def emit(self, event: str, payload: Any = None) -> None:
        for h in list(self._handlers.get(event, [])):
            try:
                h(payload)
            except Exception:
                pass

    def on(self, event: str, handler: Any) -> None:
        self._handlers.setdefault(event, []).append(handler)

    def off(self, event: str, handler: Any) -> None:
        handlers = self._handlers.get(event)
        if handlers and handler in handlers:
            handlers.remove(handler)


# ---------------------------------------------------------------- ui_field

_MISSING = object()


def ui_field(widget: str, *, group: str | None = None,
             description: str | None = None, title: str | None = None,
             default: Any = _MISSING, **kw: Any) -> Any:
    """声明带 UI 元数据的字段，供前端 inspector 自动渲染。

    widget 取值约定：
      text / textarea / number / select / checkbox / slider /
      color / readonly / kv / json / children / image（内置）

      `json` 是"任意 JSON 的多行文本框"（对象或数组都收），给检测框顶点
      这类结构化但又不值得单独做控件的值用；`kv` 只收对象，别混用。

      `image` 是"图片预览 + 重新拍照"：值是一张图片的路径（多数情况是
      相对当前 prefab 文件的相对路径，随 prefab 一起搬走也不会断链），
      前端渲染缩略图并给一个重新抓拍的按钮。
      `select` 的选项有两种来源：静态 `options=[...]`（写死在代码里，改了要重启），
      或 `optionsFrom="algorithms"`——**选项由前端按名字去拿数据**（见
      AlgorithmConfigNode.algorithm）。目录型的值（算法、图标…）用后者，
      否则加一条数据就要改一次后端。

    kw 里的键会原样放进 ui 元数据：min / max / step / options / optionsFrom /
    placeholder 等。
    title 为表单显示名（不传则前端回退字段名）；description 映射到 pydantic
    原生描述（同时进入 JSON Schema description）。
    default 设置 pydantic 字段默认值（不传则该字段必填）。
    """
    meta: dict[str, Any] = {"widget": widget}
    if group:
        meta["group"] = group
    meta.update(kw)
    if default is _MISSING:
        f = Field(description=description, title=title,
                  json_schema_extra={"ui": meta})
    else:
        f = Field(default, description=description, title=title,
                  json_schema_extra={"ui": meta})
    return f


# ---------------------------------------------------------------- NodeBase

class NodeBase(BaseModel, ABC):
    """所有 prefab 节点的基类。子类定义即自动注册，无需装饰器。"""

    model_config = ConfigDict(extra="forbid")

    #: 废弃 / 内部节点标记。True 时**仍然注册**（旧文件里的该节点能照常 build、
    #: 能打开），但不进 node-types 的"添加节点"类型目录（registry 透出为
    #: ``hidden``，前端类型选择器据此过滤）。用于平滑下线一种节点而不破坏存量数据。
    __hidden__: ClassVar[bool] = False

    #: **不下发到检视器**的字段名（含从基类继承来的）。用于平滑下线某个字段：
    #: 模型上**仍然保留**该字段（所以旧 prefab 里带着它照样能 build，
    #: 不会撞上 `extra="forbid"`），但 `node-types` 的 schema 里把它摘掉，
    #: 检视器就不再渲染它 —— 用户看不见、也改不了，等于下线。
    #:
    #: ⚠️ 为什么不是直接把字段从模型里删掉：`extra="forbid"` 是**故意**开着抓拼写
    #: 错误的，删字段会让所有存量文件当场打不开（见 `DetectBoxNode.algorithm`
    #: 当年就是"保留只读镜像"而不是删掉）。字段下线一律走本机制。
    #: 配套：执行侧要同步**停止读取**这些字段，否则用户改了看不到的旧值会继续生效。
    __hidden_fields__: ClassVar[tuple[str, ...]] = ()

    # ---- 通用字段（所有节点自带，inspector 通用分组）----
    type: str = ui_field("readonly", group="通用", default="",
                         description="节点类型（注册名，自动填充）")
    name: str = ui_field("text", group="通用", placeholder="节点名称", default="")
    enabled: bool = ui_field("checkbox", group="通用", default=True,
                             description="停用后该节点及其子树不参与运行")
    description: str = ui_field("textarea", group="通用", default="")
    children: list[dict[str, Any]] = Field(
        default_factory=list,
        json_schema_extra={"ui": {"widget": "children", "group": "通用"}},
    )

    # 注册表：所有 NodeBase 子类共享同一张表
    _registry: ClassVar[dict[str, Type["NodeBase"]]] = {}

    # 运行时引用（不进 schema、不参与校验）
    _children: list["NodeBase"] = PrivateAttr(default_factory=list)
    _parent: Optional["NodeBase"] = PrivateAttr(default=None)
    _state: str = PrivateAttr(default="inactive")  # inactive | active | error
    _error: Optional[str] = PrivateAttr(default=None)

    def __init_subclass__(cls, **kwargs: Any) -> None:
        super().__init_subclass__(**kwargs)  # 先让 pydantic 完成模型构建
        # 中间基类约定：__type_name__ = None 表示不注册（见 nodes/logic.py CompositeNode）
        type_name = cls.__dict__.get("__type_name__", cls.__name__)
        if type_name is None:
            return
        if type_name in cls._registry:
            raise TypeError(f"prefab 节点类型重复注册: {type_name}")
        cls._registry[type_name] = cls
        # 让 type 字段默认值 = 注册名，build 时无需手动传入
        if "type" in cls.model_fields:
            cls.model_fields["type"].default = type_name

    # ------------------------------------------------------------ 生命周期钩子

    def on_active(self, ctx: Context) -> None:
        """节点被激活时调用（父先子，DFS）。抛异常会进入 error 状态。"""

    def on_deactive(self, ctx: Context) -> None:
        """节点被失活时调用（子先父，与激活顺序对称）。"""

    def on_tick(self, ctx: Context, dt: float) -> None:
        """可选：由运行时按 tick 周期驱动。"""

    def on_error(self, ctx: Context, exc: Exception) -> None:
        """节点激活/运行出错后调用。"""

    # ------------------------------------------------------------ 运行时框架

    @property
    def state(self) -> str:
        return self._state

    @property
    def error(self) -> Optional[str]:
        return self._error

    @property
    def parent(self) -> Optional["NodeBase"]:
        return self._parent

    @property
    def child_nodes(self) -> list["NodeBase"]:
        return list(self._children)

    def activate(self, ctx: Context) -> None:
        """激活入口：on_active -> 子节点。子节点失败隔离在自身，不中断兄弟。"""
        if not self.enabled or self._state == "active":
            return
        self._state = "activating"
        try:
            self.on_active(ctx)
            self._state = "active"
            self._activate_children(ctx)
        except Exception as exc:
            self._state = "error"
            self._error = str(exc)
            try:
                self.on_error(ctx, exc)
            except Exception:
                pass

    def deactivate(self, ctx: Context) -> None:
        """失活入口：子节点先失活，再 on_deactive。"""
        if self._state not in ("active", "error"):
            return
        for c in reversed(self._children):
            c.deactivate(ctx)
        try:
            self.on_deactive(ctx)
        except Exception as exc:
            self._state = "error"
            self._error = str(exc)
            return
        self._state = "inactive"
        self._error = None

    def tick(self, ctx: Context, dt: float) -> None:
        """tick 入口：on_tick 后向下传播。出错标记本节点，不阻断兄弟。"""
        if self._state != "active":
            return
        try:
            self.on_tick(ctx, dt)
        except Exception as exc:
            self._state = "error"
            self._error = str(exc)
            return
        for c in self._children:
            c.tick(ctx, dt)

    def _activate_children(self, ctx: Context) -> None:
        """子节点激活策略，组合节点可覆写（见 nodes/logic.py）。"""
        for c in self._children:
            c.activate(ctx)
