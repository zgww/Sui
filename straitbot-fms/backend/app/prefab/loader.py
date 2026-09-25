"""prefab 目录扫描与加载。

目录可任意嵌套，每个 xx.prefab.json 描述一棵节点树。
单文件失败只记录错误，不影响其它 prefab 加载。
"""
from __future__ import annotations

import json
from dataclasses import dataclass
from pathlib import Path

from .base import NodeBase
from .registry import build


@dataclass
class PrefabTree:
    """一棵已加载的 prefab 树。"""

    name: str
    path: str
    spec: dict
    root: NodeBase | None = None
    state: str = "loaded"  # loaded | active | error | disabled
    error: str | None = None


class PrefabLoader:
    """扫描 prefab 目录并构建节点树，收集全部错误。"""

    def __init__(self, root: Path, exclude: tuple[str, ...] = ()) -> None:
        self.root = Path(root)
        # 相对根的第一级目录名命中 exclude 的子树整体跳过（如纯数据的 waypoint/ 航点树，
        # 它们走独立 loader，不应作为规则被 runtime 激活）。
        self.exclude = tuple(exclude)
        self.trees: dict[str, PrefabTree] = {}
        self.errors: list[str] = []

    def load_all(self) -> list[str]:
        """重新扫描目录并加载全部 prefab，返回错误列表（空列表 = 全部成功）。"""
        self.trees.clear()
        self.errors.clear()
        if not self.root.exists():
            self.errors.append(f"prefab 目录不存在: {self.root}")
            return self.errors
        for p in sorted(self.root.rglob("*.prefab.json")):
            rel = p.relative_to(self.root)
            if self.exclude and rel.parts and rel.parts[0] in self.exclude:
                continue
            self._load_file(p)
        return self.errors

    def _load_file(self, path: Path) -> None:
        try:
            spec = json.loads(path.read_text(encoding="utf-8"))
            if not isinstance(spec, dict):
                raise ValueError("prefab 顶层必须是 JSON 对象")
            name = spec.get("name") or path.stem
            if name in self.trees:
                raise ValueError(f"prefab 名称重复: {name}")
            root = build(spec.get("root") or {})
            self.trees[name] = PrefabTree(name=name, path=str(path), spec=spec, root=root)
        except Exception as exc:
            self.errors.append(f"{path}: {exc}")

    def get(self, name: str) -> PrefabTree | None:
        return self.trees.get(name)
