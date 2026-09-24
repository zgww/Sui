"""枚举配置目录的**只读**访问：把 `data/prefabs/枚举/` 下的树读成下拉选项。

下拉框要的其实只有一件事——"这个 key 有哪些选项"。这一层把它从"prefab 文件
树"翻译成"[{value, label, description}]"，让告警中心这类消费方不需要知道
prefab 长什么样、节点挂在几层。

⚠️ **每次现读、不做缓存**：枚举是给人随时改的编排数据，改完要立刻在下拉框里
生效。缓存就得配失效策略（文件 mtime 监听、手动刷新接口…），而这里的数据量
是几十个选项、几个文件，读一次的代价远低于"改了不生效"带来的困惑。

⚠️ **读失败一律降级成空选项，不抛异常**：下拉框是筛选区的装饰性控件，枚举
目录坏了、文件 JSON 写坏了，最坏的结果应该是"类型下拉只剩「全部类型」"
（此时消费方回落到库里实际出现过的值），而不是整个告警中心 500。
"""
from __future__ import annotations

import json
from pathlib import Path
from typing import Any, Iterator

from ..config import ENUM_PREFAB_DIR

ENUM_NODE = "EnumNode"
ENUM_ITEM_NODE = "EnumItemNode"


def enum_files() -> list[Path]:
    """枚举目录下全部 `*.prefab.json`（排序，保证多次读取顺序稳定）。"""
    root = Path(ENUM_PREFAB_DIR)
    if not root.is_dir():
        return []
    return sorted(p for p in root.rglob("*.prefab.json") if p.is_file())


def _node_type(node: Any) -> str:
    return str((node or {}).get("type") or "")


def _props(node: Any) -> dict[str, Any]:
    p = (node or {}).get("properties")
    return p if isinstance(p, dict) else {}


def iter_nodes(root: Any) -> Iterator[dict[str, Any]]:
    """深度优先遍历整棵树（含 root 自己）。"""
    if not isinstance(root, dict):
        return
    yield root
    for c in root.get("children") or []:
        yield from iter_nodes(c)


def iter_enum_nodes(spec: Any) -> Iterator[dict[str, Any]]:
    """一份 spec 里所有 `EnumNode`（root 通常就是它，也容许嵌在别处）。"""
    if not isinstance(spec, dict):
        return
    for n in iter_nodes(spec.get("root")):
        if _node_type(n) == ENUM_NODE:
            yield n


def options_of(node: Any) -> list[dict[str, str]]:
    """一个 `EnumNode` 的直接 `EnumItemNode` 子节点 -> 选项列表。

    - **`enabled=False` 的项跳过**：那是"暂时停用"，不是"停用但要显示"；
    - **空 `name` 的项跳过**：没有键的选项筛不出任何东西，留着只会让下拉框
      多一条点了没反应的空行；
    - **`label` 为空时回落 `name`**：前端拿到的一定有显示文本，不必再判断一次。
    """
    out: list[dict[str, str]] = []
    for c in node.get("children") or []:
        if _node_type(c) != ENUM_ITEM_NODE:
            continue
        p = _props(c)
        if p.get("enabled") is False:
            continue
        name = str(p.get("name") or "").strip()
        if not name:
            continue
        out.append({
            "value": name,
            "label": str(p.get("label") or "").strip() or name,
            "description": str(p.get("description") or ""),
        })
    return out


def _key_of(node: Any, file_stem: str) -> str:
    """枚举的对外键：`EnumNode.name` 优先，没写时退回文件名。

    退回文件名是必要的兜底：新建文件后用户往往先在树上改项、忘了填 name，
    这时按文件名还能取到（前端新建时已经把 name 预填成文件名，多数情况下
    两者一致）。
    """
    p = _props(node)
    return str(p.get("name") or "").strip() or file_stem


def read_enum_options(key: str, *, root: Path | None = None) -> dict[str, Any]:
    """按 key 取一份枚举的选项。

    :return: `{"ok", "key", "found", "options", "sources"}`
        - `found`：目录里**存在**这个 key 的 EnumNode（选项可以是空数组——
          配了但一项都没填，与"没配过"是两件事，消费方据此决定要不要回落）；
        - `sources`：命中的文件相对路径，便于排查"为什么取到的是这一份"。
    """
    key = (key or "").strip()
    base = Path(root) if root is not None else Path(ENUM_PREFAB_DIR)
    result: dict[str, Any] = {"ok": True, "key": key, "found": False,
                              "options": [], "sources": []}
    if not key or not base.is_dir():
        return result

    options: list[dict[str, str]] = []
    seen: set[str] = set()
    for p in sorted(q for q in base.rglob("*.prefab.json") if q.is_file()):
        try:
            spec = json.loads(p.read_text(encoding="utf-8"))
        except Exception:  # noqa: BLE001 - 坏文件跳过，不让整个下拉框挂掉
            continue
        stem = p.stem[:-len(".prefab")] if p.stem.endswith(".prefab") else p.stem
        for n in iter_enum_nodes(spec):
            if _key_of(n, stem) != key:
                continue
            result["found"] = True
            rel = p.relative_to(base).as_posix()
            if rel not in result["sources"]:
                result["sources"].append(rel)
            # 同一 key 出现在多个文件里：按值去重、按首次出现顺序合并。
            # 不去重的话下拉框会出现两行一样的值，点了筛出同样的数据。
            for opt in options_of(n):
                if opt["value"] in seen:
                    continue
                seen.add(opt["value"])
                options.append(opt)
    result["options"] = options
    return result


def list_enum_keys(*, root: Path | None = None) -> dict[str, Any]:
    """目录里全部枚举的键与选项条数（给"有哪些枚举可引用"的下拉/调试用）。"""
    base = Path(root) if root is not None else Path(ENUM_PREFAB_DIR)
    out: list[dict[str, Any]] = []
    if not base.is_dir():
        return {"ok": True, "keys": out}
    for p in sorted(q for q in base.rglob("*.prefab.json") if q.is_file()):
        try:
            spec = json.loads(p.read_text(encoding="utf-8"))
        except Exception:  # noqa: BLE001
            continue
        stem = p.stem[:-len(".prefab")] if p.stem.endswith(".prefab") else p.stem
        for n in iter_enum_nodes(spec):
            key = _key_of(n, stem)
            if not key:
                continue
            out.append({"key": key, "label": str(_props(n).get("label") or "").strip() or key,
                        "count": len(options_of(n)),
                        "file": p.relative_to(base).as_posix()})
    return {"ok": True, "keys": out}
