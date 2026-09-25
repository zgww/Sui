"""节点树运行时：激活 / 失活 / tick / 定时器调度。"""
from __future__ import annotations

from apscheduler.schedulers.background import BackgroundScheduler

from .base import Context
from .loader import PrefabLoader, PrefabTree


class PrefabRuntime:
    """管理所有已加载 prefab 树的生命周期。

    - activate_all: 激活全部树（父先子 DFS，子节点失败隔离）
    - tick_all:     由外部周期驱动（如 APScheduler 秒级任务）
    - deactivate_all: 逆序失活并关闭调度器
    """

    def __init__(self, loader: PrefabLoader) -> None:
        self.loader = loader
        self.contexts: dict[str, Context] = {}
        self.scheduler: BackgroundScheduler | None = None

    def boot_tree(self):
        """启动树（`data/prefabs/启动.prefab.json`）——常驻内存的对象树。

        常驻任务（如「巡检计划调度节点」的后台线程）挂在这棵树上，所以它必须
        **先于**其它 prefab 激活：否则别的规则链先跑起来，读到的是"调度还没起来"
        的状态。返回 `None` 表示这一版数据里没有启动文件（不算错误）。
        """
        from ..config import BOOT_PREFAB_FILE

        want = BOOT_PREFAB_FILE.name
        for tree in self.loader.trees.values():
            if tree.path.replace("\\", "/").endswith("/" + want) \
                    or tree.path.replace("\\", "/").endswith(want):
                return tree
        return None

    def activate_all(self) -> None:
        self.scheduler = BackgroundScheduler(timezone="UTC")
        self.scheduler.start()
        # 启动树优先：它承载常驻任务，别的树可能依赖它已经就绪
        boot = self.boot_tree()
        if boot is not None:
            self._activate_tree(boot.name, boot)
        for name, tree in self.loader.trees.items():
            if boot is not None and tree is boot:
                continue
            self._activate_tree(name, tree)

    def _activate_tree(self, name: str, tree: PrefabTree) -> None:
        ctx = Context()
        self.contexts[name] = ctx
        ctx.kv["__scheduler__"] = self.scheduler  # 供 CronTimer 等注册任务
        if tree.root is None:
            tree.state = "error"
            tree.error = "根节点为空"
            return
        try:
            tree.root.activate(ctx)
            if tree.root.state == "error":
                tree.state = "error"
                tree.error = tree.root.error
            elif tree.root.state == "active":
                tree.state = "active"
                tree.error = None
            else:
                # 树被禁用（root.enabled=false）：不是错误，前端单独以提示呈现
                tree.state = "disabled"
                tree.error = None
        except Exception as exc:
            tree.state = "error"
            tree.error = str(exc)

    def tick_all(self, dt: float = 1.0) -> None:
        for name, tree in self.loader.trees.items():
            if tree.state != "active" or tree.root is None:
                continue
            ctx = self.contexts.get(name)
            if ctx is None:
                continue
            tree.root.tick(ctx, dt)
            if tree.root.state == "error":
                tree.state = "error"
                tree.error = tree.root.error

    def deactivate_all(self) -> None:
        for name, tree in self.loader.trees.items():
            if tree.root is not None and tree.state in ("active", "error"):
                ctx = self.contexts.get(name)
                if ctx is not None:
                    tree.root.deactivate(ctx)
            tree.state = "loaded"
            tree.error = None
        self.contexts.clear()
        if self.scheduler is not None:
            self.scheduler.shutdown(wait=False)
            self.scheduler = None

    def reload(self) -> list[str]:
        """停旧树 -> 重新加载全部 -> 重新激活。返回错误列表。"""
        self.deactivate_all()
        errors = self.loader.load_all()
        self.activate_all()
        return errors


# ---------------------------------------------------------------- 模块级单例

_runtime: PrefabRuntime | None = None


def init_runtime(loader: PrefabLoader) -> PrefabRuntime:
    global _runtime
    _runtime = PrefabRuntime(loader)
    return _runtime


def get_runtime() -> PrefabRuntime:
    if _runtime is None:
        raise RuntimeError("prefab runtime 未初始化（应在启动时调用 init_runtime）")
    return _runtime
