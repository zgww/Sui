"""prefab 节点树 API：schema 驱动 inspector + 树管理。"""
import json
import os
import shutil
from pathlib import Path
from typing import Any

from fastapi import APIRouter, Depends, HTTPException

from ..auth import engineer_only, get_current_user
from ..config import PREFAB_DIR, BOOT_PREFAB_FILE, BOOT_PREFAB_DIR
from ..prefab import registry
from ..prefab.loader import PrefabLoader
from ..prefab.runtime import get_runtime, init_runtime

router = APIRouter(prefix="/api/prefab", tags=["prefab"])


def _ensure_runtime() -> PrefabLoader:
    """懒初始化：优先用已初始化 runtime 的 loader，否则临时构建。"""
    from ..prefab import PrefabLoader
    try:
        return get_runtime().loader
    except RuntimeError:
        from ..config import BOOT_PREFAB_DIR
        loader = PrefabLoader(BOOT_PREFAB_DIR)
        loader.load_all()
        return loader


def _runtime_or_init():
    """拿运行时单例；未初始化（如绕过 lifespan 直调）则就地初始化。"""
    from ..prefab import PrefabLoader, PrefabRuntime, init_runtime
    try:
        return get_runtime()
    except RuntimeError:
        from ..config import BOOT_PREFAB_DIR
        loader = PrefabLoader(BOOT_PREFAB_DIR)
        loader.load_all()
        runtime = init_runtime(loader)
        runtime.activate_all()
        return runtime


def _safe_rel(rel: Any, *, must_file: bool = False, must_dir: bool = False,
              allow_empty: bool = False, require_exists: bool = True) -> str:
    """把前端传的相对路径规范化为 prefab 根下的安全路径（防目录穿越）。

    require_exists=False 用于创建场景（对象尚不存在）。
    """
    if not isinstance(rel, str):
        raise HTTPException(status_code=422, detail="rel_path 必填")
    rel = rel.strip().strip("/\\").replace("\\", "/")
    if not rel:
        if allow_empty:
            return ""
        raise HTTPException(status_code=422, detail="rel_path 必填")
    if must_file and not rel.endswith(".prefab.json"):
        raise HTTPException(status_code=422, detail="prefab 文件必须以 .prefab.json 结尾")
    root = PREFAB_DIR.resolve()
    p = (PREFAB_DIR / rel).resolve()
    if p != root and root not in p.parents:
        raise HTTPException(status_code=400, detail="路径越界")
    if require_exists:
        if must_dir and not p.is_dir():
            raise HTTPException(status_code=404, detail=f"目录不存在: {rel}")
        if must_file and not p.is_file():
            raise HTTPException(status_code=404, detail=f"文件不存在: {rel}")
    return rel


@router.post("/dirs")
def create_dir(body: dict[str, Any], _=Depends(engineer_only)):
    """创建 prefab 目录（可嵌套，如 rules/sub）。"""
    rel = _safe_rel(body.get("rel_path"), require_exists=False)
    p = PREFAB_DIR / rel
    if p.exists():
        raise HTTPException(status_code=409, detail=f"已存在: {rel}")
    p.mkdir(parents=True, exist_ok=False)
    return {"ok": True, "rel_path": rel}


@router.delete("/dirs")
def delete_dir(body: dict[str, Any], _=Depends(engineer_only)):
    """递归删除 prefab 目录（含其中全部 prefab）。"""
    rel = _safe_rel(body.get("rel_path"), must_dir=True)
    shutil.rmtree(PREFAB_DIR / rel)
    errors = _runtime_or_init().reload()
    return {"ok": True, "errors": errors}


@router.post("/files")
def create_file(body: dict[str, Any], _=Depends(engineer_only)):
    """创建空 prefab 文件（xx.prefab.json，默认一棵 Sequence 空树）。"""
    rel = _safe_rel(body.get("rel_path"), must_file=True, require_exists=False)
    p = PREFAB_DIR / rel
    if p.exists():
        raise HTTPException(status_code=409, detail=f"已存在: {rel}")
    name = p.stem[:-len(".prefab")] if p.stem.endswith(".prefab") else p.stem
    spec = {
        "name": name,
        "description": "",
        "root": {
            "type": "Sequence",
            "properties": {"name": name, "enabled": True, "description": ""},
            "children": [],
        },
    }
    p.parent.mkdir(parents=True, exist_ok=True)
    with open(p, "w", encoding="utf-8") as f:
        json.dump(spec, f, ensure_ascii=False, indent=2)
    errors = _runtime_or_init().reload()
    return {"ok": True, "errors": errors, "rel_path": rel}


@router.delete("/files")
def delete_file(body: dict[str, Any], _=Depends(engineer_only)):
    """删除单个 prefab 文件。"""
    rel = _safe_rel(body.get("rel_path"), must_file=True)
    (PREFAB_DIR / rel).unlink()
    errors = _runtime_or_init().reload()
    return {"ok": True, "errors": errors}


@router.post("/rename")
def rename_entry(body: dict[str, Any], _=Depends(engineer_only)):
    """重命名 prefab 文件或目录（new_name 含扩展名/目录名）。"""
    rel = _safe_rel(body.get("rel_path"))
    new_name = body.get("new_name")
    if not isinstance(new_name, str) or not new_name.strip():
        raise HTTPException(status_code=422, detail="new_name 必填")
    new_name = new_name.strip()
    src = PREFAB_DIR / rel
    if not src.exists():
        raise HTTPException(status_code=404, detail=f"不存在: {rel}")
    dst = src.parent / new_name
    if dst.exists():
        raise HTTPException(status_code=409, detail=f"已存在: {new_name}")
    src.rename(dst)
    errors = _runtime_or_init().reload()
    return {"ok": True, "errors": errors}


@router.post("/move")
def move_entry(body: dict[str, Any], _=Depends(engineer_only)):
    """移动 prefab 文件/目录到目标目录（dest_dir 为空表示根目录）。"""
    rel = _safe_rel(body.get("rel_path"))
    dest_dir = _safe_rel(body.get("dest_dir") or "", allow_empty=True)
    src = PREFAB_DIR / rel
    if not src.exists():
        raise HTTPException(status_code=404, detail=f"不存在: {rel}")
    if dest_dir and (dest_dir == rel or dest_dir.startswith(rel + "/")):
        raise HTTPException(status_code=400, detail="不能移动到自身或其子目录")
    dst_dir = PREFAB_DIR / dest_dir if dest_dir else PREFAB_DIR
    if not dst_dir.is_dir():
        raise HTTPException(status_code=404, detail=f"目录不存在: {dest_dir or '(根)'}")
    dst = dst_dir / src.name
    if dst.exists():
        raise HTTPException(status_code=409, detail=f"已存在: {dst.relative_to(PREFAB_DIR)}")
    shutil.move(str(src), str(dst))
    errors = _runtime_or_init().reload()
    return {"ok": True, "errors": errors}


@router.get("/node-types")
def get_node_types(_=Depends(get_current_user)):
    """所有已注册节点类型的 JSON Schema（含 ui 元数据），前端 inspector 数据源。

    新增节点类后此接口自动多一条，前端零改动。
    """
    return registry.schema_for_all()


@router.get("/boot-tree")
def boot_tree(_=Depends(get_current_user)):
    """启动树（`启动.prefab.json`）：程序启动时加载、常驻内存的那棵对象树。

    常驻任务（如巡检计划调度）挂在这里，所以运维要能一眼看到它**有没有起来**、
    起了哪些节点。没有启动文件时返回 `{"tree": null}`——不是错误，只是没配。
    """
    try:
        tree = get_runtime().boot_tree()
    except RuntimeError:
        loader = _ensure_runtime()
        tree = next((t for t in loader.trees.values()
                     if t.path.replace("\\", "/").endswith(BOOT_PREFAB_FILE.name)), None)
    if tree is None:
        return {"tree": None, "file": BOOT_PREFAB_FILE.name}
    return {
        "tree": {
            "name": tree.name,
            "path": tree.path,
            "state": tree.state,
            "error": tree.error,
            "root": registry.tree_to_dict(tree.root) if tree.root else None,
        },
        "file": BOOT_PREFAB_FILE.name,
    }


def _scan_all_trees() -> list[dict[str, Any]]:
    """扫 `data/prefabs/` 下**全部** `*.prefab.json`（编排页要看全目录）。

    ⚠️ 与 runtime 的 loader **不是一回事**：loader 只扫启动目录（`BOOT_PREFAB_DIR`），
    那是"启动时加载哪些"；这里是"磁盘上有哪些"，所以编排数据（waypoint / plan /
    检测算法）、告警模板、示例都得列出来——用户要在页面里看到并编辑它们。

    单个文件读坏不影响列表：记一条 `error`，让用户在页面上看见再去修，
    好过整个列表 500。
    """
    out: list[dict[str, Any]] = []
    if not PREFAB_DIR.exists():
        return out
    for p in sorted(PREFAB_DIR.rglob("*.prefab.json")):
        rel = p.relative_to(PREFAB_DIR).as_posix()
        item: dict[str, Any] = {
            "name": p.stem[:-len(".prefab")] if p.stem.endswith(".prefab") else p.stem,
            "path": str(p),
            "rel_path": rel,
            "state": "未加载",
            "error": None,
            "root": None,
            "loaded": False,
        }
        try:
            spec = json.loads(p.read_text(encoding="utf-8"))
            r = spec.get("root") or {}
            item["name"] = spec.get("name") or item["name"]
            item["root"] = {"type": r.get("type"),
                            "name": (r.get("properties") or {}).get("name")}
        except Exception as exc:  # noqa: BLE001 - 坏文件也要列出来让人看见
            item["error"] = str(exc)
        out.append(item)
    return out


def _loaded_index() -> dict[str, Any]:
    """已被 runtime 加载的树（按**文件绝对路径**索引），用来给列表标状态。"""
    try:
        loader = _ensure_runtime()
    except Exception:  # noqa: BLE001 - runtime 没起来时列表照旧返回（只是没有状态）
        return {}
    return {str(os.path.abspath(t.path)): t for t in loader.trees.values()}


def _boot_tree():
    """启动树（`启动.prefab.json`）那棵——它不归 loader 管，是 runtime 单独认的。

    列表里要把它标成"已加载"，否则明明是唯一一棵保证会跑的树，却显示成
    "不在启动目录"，比漏标还误导。
    """
    try:
        return get_runtime().boot_tree()
    except Exception:  # noqa: BLE001 - runtime 没起来时列表照旧返回
        return None


@router.get("/trees")
def list_trees(_=Depends(get_current_user)):
    """prefab 文件列表 + 运行状态 + 全部目录（前端目录树视图用）。

    列的是 `data/prefabs/` 下**所有** `*.prefab.json`；其中只有放在启动目录
    （`data/prefabs/启动/`）里的那些会在程序启动时被加载，所以列表里带一个
    `loaded` 标记：没加载的显示成"未加载"（**不是错误**，只是不在启动目录里）。
    """
    loaded = _loaded_index()
    boot = _boot_tree()
    boot_path = os.path.abspath(str(boot.path)) if boot is not None else None
    trees_out = _scan_all_trees()
    for item in trees_out:
        if boot is not None and os.path.abspath(item["path"]) == boot_path:
            item.update(loaded=True, state=boot.state, error=boot.error or item["error"],
                        root={"type": boot.root.type if boot.root else None,
                              "name": boot.root.name if boot.root else None,
                              "state": boot.root.state if boot.root else None})
            continue
        t = loaded.get(str(os.path.abspath(item["path"])))
        if t is not None:
            item["loaded"] = True
            item["state"] = t.state
            item["error"] = t.error or item["error"]
            item["root"] = {"type": t.root.type if t.root else None,
                            "name": t.root.name if t.root else None,
                            "state": t.root.state if t.root else None}
    dirs: list[str] = []
    for root_dir, dnames, _ in os.walk(PREFAB_DIR):
        for dn in sorted(dnames):
            dirs.append(os.path.relpath(os.path.join(root_dir, dn), PREFAB_DIR)
                        .replace("\\", "/"))
    return {"trees": trees_out, "errors": [], "dirs": dirs}


@router.get("/trees/{name}")
def get_tree(name: str, _=Depends(get_current_user)):
    """单棵 prefab：完整 spec + 树结构（**在启动目录里**才带运行状态）。

    ⚠️ 按**文件**找，不按 runtime 里的树找：编排页要能打开磁盘上任意一个
    prefab，包括没被加载的那些（否则点了列表里的文件只会 404）。
    没加载的树照样给 `status_tree`，只是状态全是 inactive。
    """
    item = next((t for t in _scan_all_trees() if t["name"] == name), None)
    if item is None:
        raise HTTPException(status_code=404, detail=f"prefab 不存在: {name}")
    try:
        spec = json.loads(Path(item["path"]).read_text(encoding="utf-8"))
    except Exception as exc:  # noqa: BLE001
        raise HTTPException(status_code=400, detail=f"读取失败: {exc}")

    loaded = _loaded_index().get(str(os.path.abspath(item["path"])))
    if loaded is not None and loaded.root is not None:
        status_tree = registry.tree_to_dict(loaded.root)
        state, error = loaded.state, loaded.error
    else:
        # 没被 runtime 加载：临时 build 一棵只为画出来（状态自然都是 inactive）
        node = registry.build(spec.get("root") or {})
        status_tree = registry.tree_to_dict(node)
        state, error = "未加载", item["error"]
    return {
        "name": item["name"],
        "path": item["path"],
        "rel_path": item["rel_path"],
        "state": state,
        "error": error,
        "spec": spec,
        "status_tree": status_tree,
    }


@router.post("/trees/{name}")
def save_tree(name: str, body: dict[str, Any], _=Depends(engineer_only)):
    """保存 prefab spec 写回文件（**任意位置**都能存）并热重载。

    热重载只影响启动目录里的树——存一个别处的文件不该把正在跑的规则重启一遍，
    但存了启动目录里的文件就必须重载，否则改完看不到效果。
    """
    # 先校验：能 build 成功才允许写盘
    root_spec = body.get("root")
    if not isinstance(root_spec, dict):
        raise HTTPException(status_code=422, detail="prefab 必须包含 root 节点")
    try:
        registry.build(root_spec)  # 校验失败会抛 422/400
    except Exception as exc:  # noqa: BLE001
        raise HTTPException(status_code=400, detail=f"节点校验失败: {exc}")

    item = next((t for t in _scan_all_trees() if t["name"] == name), None)
    if item is None:
        raise HTTPException(status_code=404, detail=f"prefab 不存在: {name}")
    try:
        with open(item["path"], "w", encoding="utf-8") as f:
            json.dump(body, f, ensure_ascii=False, indent=2)
    except OSError as exc:
        raise HTTPException(status_code=500, detail=f"写入失败: {exc}")
    errors = _runtime_or_init().reload()
    return {"ok": True, "errors": errors}


@router.post("/reload")
def reload_trees(_=Depends(engineer_only)):
    """重载全部 prefab（停旧树 -> 重新加载 -> 激活）。"""
    runtime = _runtime_or_init()
    errors = runtime.reload()
    return {"ok": True, "errors": errors}


def _ensure_boot_prefab(path) -> bool:
    """启动文件缺失时建一个空的（Sequence 根），返回是否新建。

    启动树是**常驻内存的对象树**（常驻任务挂在这里），文件得先存在，运维才能在
    prefab 页面里往里加节点。内容一律留空：起什么任务是配置的事，不替用户猜。
    """
    if path.exists():
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    spec = {
        "name": path.name[:-len(".prefab.json")],
        "description": "启动树：程序启动时加载并激活，常驻内存的对象树（常驻任务挂在这里）",
        "root": {
            "type": "Sequence",
            "properties": {"name": "启动", "enabled": True, "description": ""},
            "children": [],
        },
    }
    with open(path, "w", encoding="utf-8") as f:
        json.dump(spec, f, ensure_ascii=False, indent=2)
    print(f"[prefab] 已创建启动树文件: {path}")
    return True


def startup_prefab() -> None:
    """应用启动时调用：加载并激活全部 prefab 树（**启动树优先**）。"""
    from ..config import PREFAB_DIR, BOOT_PREFAB_FILE, BOOT_PREFAB_DIR
    _ensure_boot_prefab(BOOT_PREFAB_FILE)
    # 装上"到点 -> 真下发"的默认回调（幂等，已经有人注册过就不覆盖）。
    # 节点 dry_run 默认 True，所以装上也不会立刻发车；去掉演练勾选才走这条路。
    from ..prefab.plan_scheduler import install_default_trigger
    install_default_trigger()
    # waypoint/、plan/、检测算法/ 都是**编排数据**不是规则：航点树由航点树页面
    # 消费，计划树由「巡检计划调度节点」按文件扫描消费（见 prefab/plan_scheduler.py），
    # 检测流程树目前只被读写校验。让它们进 runtime 只会多出一堆"激活了但什么
    # 也不做"的树。
    loader = PrefabLoader(BOOT_PREFAB_DIR)
    errors = loader.load_all()
    init_runtime(loader)
    runtime = get_runtime()
    runtime.activate_all()
    for err in errors:
        print(f"[prefab] 加载错误: {err}")
    print(f"[prefab] 已加载 {len(loader.trees)} 棵树, "
          f"错误 {len(errors)} 条, 类型 {len(registry.registered_types())} 个")
    boot = runtime.boot_tree()
    if boot is None:
        print(f"[prefab] 未找到启动树 {BOOT_PREFAB_FILE.name}（常驻任务不会启动）")
    else:
        print(f"[prefab] 启动树: {boot.path} 状态={boot.state}"
              + (f" 错误={boot.error}" if boot.error else ""))


def shutdown_prefab() -> None:
    """应用关闭时调用：逆序失活全部树。"""
    try:
        get_runtime().deactivate_all()
    except RuntimeError:
        pass
    print("[prefab] 已停止")
