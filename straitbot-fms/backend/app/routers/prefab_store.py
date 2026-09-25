"""prefab 文件树的通用 CRUD 路由工厂。

航点树编排（`/api/waypoint-prefab`）与巡检计划编排（`/api/plan-prefab`）是**两棵
独立的树**，但"在 data/prefabs/<kind>/ 下管一堆 *.prefab.json"这件事一模一样：
同样的目录/文件增删改名移动、同样的树读写、同样的路径越界防护、同样的
`registry.build` 写前校验。差别只有三处，全部做成参数：

- `prefix` / `tag`：挂到哪个 URL 前缀下；
- `root_dir`：这棵树的根目录；
- `base_filter`：`node-types` 只暴露哪个中间基类的子类
  （`WaypointNodeBase` / `PlanNodeBase`）——两棵树的类型目录必须分开，
  否则"添加子节点"里会混进另一棵树的类型，选中就存出一个跨树的脏节点；
- `root_spec_factory`：新建文件时的初始 spec（航点树是 GroupNode 根，
  计划树是 InspectionPlanNode 根）。

**为什么不是各写一份**：这套接口有若干容易写错又不好发现的地方（路径穿越、
覆盖写不建文件、body 键名、写前 build 校验），复制一份出来迟早会有一边漏改。
抽成工厂后新增一棵树只需要写十行。

各接口的语义与坑见下面每个函数的 docstring。
"""
from __future__ import annotations

import json
import os
import shutil
from pathlib import Path
from typing import Any, Callable

from fastapi import APIRouter, Depends, HTTPException

from ..auth import engineer_only, get_current_user
from ..prefab import registry


def make_prefab_router(
    *,
    prefix: str,
    tag: str,
    root_dir: Path,
    base_filter: str,
    root_spec_factory: Callable[[str], dict[str, Any]],
) -> APIRouter:
    """生成一棵 prefab 文件树的路由。

    :param prefix: URL 前缀，如 `/api/waypoint-prefab`
    :param tag: OpenAPI 分组名
    :param root_dir: 该树的根目录（会在需要时 mkdir）
    :param base_filter: `node-types` 只返回 `base == base_filter` 的类型
    :param root_spec_factory: `名称 -> 初始 spec`，用于新建文件
    """
    router = APIRouter(prefix=prefix, tags=[tag])

    def _root() -> Path:
        root_dir.mkdir(parents=True, exist_ok=True)
        return root_dir

    def _safe_rel(rel: Any, *, must_file: bool = False, must_dir: bool = False,
                  allow_empty: bool = False, require_exists: bool = True) -> str:
        """把相对路径规范化为树根下的安全路径（防目录穿越）。"""
        if not isinstance(rel, str):
            raise HTTPException(status_code=422, detail="rel_path 必填")
        rel = rel.strip().strip("/\\").replace("\\", "/")
        if not rel:
            if allow_empty:
                return ""
            raise HTTPException(status_code=422, detail="rel_path 必填")
        if must_file and not rel.endswith(".prefab.json"):
            raise HTTPException(status_code=422, detail="prefab 文件必须以 .prefab.json 结尾")
        root = _root().resolve()
        p = (root / rel).resolve()
        if p != root and root not in p.parents:
            raise HTTPException(status_code=400, detail="路径越界")
        if require_exists:
            if must_dir and not p.is_dir():
                raise HTTPException(status_code=404, detail=f"目录不存在: {rel}")
            if must_file and not p.is_file():
                raise HTTPException(status_code=404, detail=f"文件不存在: {rel}")
        return rel

    # ------------------------------------------------------------ 节点类型

    @router.get("/node-types", dependencies=[Depends(get_current_user)])
    def get_node_types():
        """返回本棵树根基类（`base_filter`）之下的节点类型 JSON Schema。

        按继承关系（issubclass）过滤，而不是直接父类名相等：隔了一层类别
        基类的节点（如各算法节点 -> DetectorNode -> DetectNodeBase）也得被
        收进来。中间基类不注册，不会出现在结果里。
        """
        return registry.schema_for_base(base_filter)

    # ------------------------------------------------------------ 目录/文件 CRUD

    @router.post("/dirs", dependencies=[Depends(engineer_only)])
    def create_dir(body: dict[str, Any]):
        rel = _safe_rel(body.get("rel_path"), require_exists=False)
        p = _root() / rel
        if p.exists():
            raise HTTPException(status_code=409, detail=f"已存在: {rel}")
        p.mkdir(parents=True, exist_ok=False)
        return {"ok": True, "rel_path": rel}

    @router.delete("/dirs", dependencies=[Depends(engineer_only)])
    def delete_dir(body: dict[str, Any]):
        rel = _safe_rel(body.get("rel_path"), must_dir=True)
        shutil.rmtree(_root() / rel)
        return {"ok": True}

    @router.post("/files", dependencies=[Depends(engineer_only)])
    def create_file(body: dict[str, Any]):
        """新建一棵空树。

        ⚠️ 与 `POST /tree` 的分工：**这个接口负责建文件**，`/tree` 只覆盖写。
        直接往一个不存在的 rel_path 存树会 404，得先来这里建一次。
        """
        rel = _safe_rel(body.get("rel_path"), must_file=True, require_exists=False)
        p = _root() / rel
        if p.exists():
            raise HTTPException(status_code=409, detail=f"已存在: {rel}")
        name = p.stem[:-len(".prefab")] if p.stem.endswith(".prefab") else p.stem
        spec = root_spec_factory(name)
        p.parent.mkdir(parents=True, exist_ok=True)
        with open(p, "w", encoding="utf-8") as f:
            json.dump(spec, f, ensure_ascii=False, indent=2)
        return {"ok": True, "rel_path": rel}

    @router.delete("/files", dependencies=[Depends(engineer_only)])
    def delete_file(body: dict[str, Any]):
        rel = _safe_rel(body.get("rel_path"), must_file=True)
        (_root() / rel).unlink()
        return {"ok": True}

    @router.post("/rename", dependencies=[Depends(engineer_only)])
    def rename_entry(body: dict[str, Any]):
        rel = _safe_rel(body.get("rel_path"))
        new_name = body.get("new_name")
        if not isinstance(new_name, str) or not new_name.strip():
            raise HTTPException(status_code=422, detail="new_name 必填")
        new_name = new_name.strip()
        src = _root() / rel
        if not src.exists():
            raise HTTPException(status_code=404, detail=f"不存在: {rel}")
        dst = src.parent / new_name
        if dst.exists():
            raise HTTPException(status_code=409, detail=f"已存在: {new_name}")
        src.rename(dst)
        return {"ok": True}

    @router.post("/move", dependencies=[Depends(engineer_only)])
    def move_entry(body: dict[str, Any]):
        rel = _safe_rel(body.get("rel_path"))
        dest_dir = _safe_rel(body.get("dest_dir") or "", allow_empty=True)
        root = _root()
        src = root / rel
        if not src.exists():
            raise HTTPException(status_code=404, detail=f"不存在: {rel}")
        if dest_dir and (dest_dir == rel or dest_dir.startswith(rel + "/")):
            raise HTTPException(status_code=400, detail="不能移动到自身或其子目录")
        dst_dir = root / dest_dir if dest_dir else root
        if not dst_dir.is_dir():
            raise HTTPException(status_code=404, detail=f"目录不存在: {dest_dir or '(根)'}")
        dst = dst_dir / src.name
        if dst.exists():
            raise HTTPException(status_code=409, detail=f"已存在: {dst.relative_to(root)}")
        shutil.move(str(src), str(dst))
        return {"ok": True}

    # ------------------------------------------------------------ 树读写

    @router.get("/trees", dependencies=[Depends(get_current_user)])
    def list_trees():
        """树文件列表（rel_path 唯一键）+ 全部子目录，供文件选择与目录树。"""
        root = _root()
        trees_out: list[dict[str, Any]] = []
        dirs: list[str] = []
        for dirpath, dnames, fnames in os.walk(root):
            dnames.sort()
            for dn in dnames:
                dirs.append(os.path.relpath(os.path.join(dirpath, dn), root)
                            .replace("\\", "/"))
            for fn in sorted(fnames):
                if not fn.endswith(".prefab.json"):
                    continue
                fp = os.path.join(dirpath, fn)
                rel = os.path.relpath(fp, root).replace("\\", "/")
                item: dict[str, Any] = {"rel_path": rel, "name": fn, "root": None,
                                        "error": None}
                try:
                    spec = json.loads(open(fp, encoding="utf-8").read())
                    r = spec.get("root") or {}
                    props = r.get("properties") or {}
                    item["name"] = spec.get("name") or fn
                    item["root"] = {
                        "type": r.get("type"),
                        "name": props.get("name"),
                        # DetectPipelineNode 的对外身份；航点/计划树根没有这两个
                        # 字段，回落空串即可（检测框引用检测流程时用 detect_id||文件名）
                        "detect_id": props.get("detect_id") or "",
                        "scene": props.get("scene") or "",
                    }
                except Exception as exc:  # 单个文件损坏不影响列表
                    item["error"] = str(exc)
                trees_out.append(item)
        trees_out.sort(key=lambda t: t["rel_path"])
        dirs.sort()
        return {"trees": trees_out, "dirs": dirs}

    @router.get("/tree", dependencies=[Depends(get_current_user)])
    def get_tree(rel_path: str):
        rel = _safe_rel(rel_path, must_file=True)
        try:
            spec = json.loads((_root() / rel).read_text(encoding="utf-8"))
        except Exception as exc:
            raise HTTPException(status_code=400, detail=f"读取失败: {exc}")
        return {"rel_path": rel, "spec": spec}

    @router.post("/tree", dependencies=[Depends(engineer_only)])
    def save_tree(body: dict[str, Any]):
        """覆盖写一棵树。

        ⚠️ body 的键是 **`spec`**（不是 `tree`），写错报 422；
        且**不创建文件**——文件不存在时 `_safe_rel(must_file=True)` 直接 404，
        要先 `POST /files`。
        """
        rel = _safe_rel(body.get("rel_path"), must_file=True)
        spec = body.get("spec")
        if not isinstance(spec, dict):
            raise HTTPException(status_code=422, detail="body 需要 spec 对象")
        root_spec = spec.get("root")
        if not isinstance(root_spec, dict):
            raise HTTPException(status_code=422, detail="prefab 必须包含 root 节点")
        try:
            registry.build(root_spec)  # 能 build 成功才允许写盘
        except registry.UnknownNodeType as exc:
            raise HTTPException(status_code=400, detail=str(exc))
        except Exception as exc:
            # pydantic ValidationError 等：回传首条错误，便于前端定位字段
            raise HTTPException(status_code=400, detail=f"节点校验失败: {exc}")
        p = _root() / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        with open(p, "w", encoding="utf-8") as f:
            json.dump(spec, f, ensure_ascii=False, indent=2)
        return {"ok": True, "rel_path": rel}

    return router
