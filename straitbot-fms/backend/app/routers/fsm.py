"""机器人状态机(状态动作图)文件管理 API。

状态动作图 = 画布对象(objects) + 对象间连线(connections)，保存为 .fsm.json。
本模块只负责文件级读写与目录树管理（前端编辑器落盘入口），
状态机的运行语义由后续后端执行器解释，此处不涉及。
"""
import json
import os
import shutil
from typing import Any

from fastapi import APIRouter, Depends, HTTPException

from ..auth import engineer_only, get_current_user
from ..config import FSM_DIR

router = APIRouter(prefix="/api/fsm", tags=["fsm"])

EMPTY_SPEC = {
    "version": 1,
    "name": "",
    "description": "",
    "objects": [],
    "connections": [],
}


def _safe_rel(rel: Any, *, must_file: bool = False, must_dir: bool = False,
              allow_empty: bool = False, require_exists: bool = True) -> str:
    """把前端传的相对路径规范化为 fsm 根下的安全路径（防目录穿越）。

    require_exists=False 用于创建（对象尚不存在）。
    """
    if not isinstance(rel, str):
        raise HTTPException(status_code=422, detail="rel_path 必填")
    rel = rel.strip().strip("/\\").replace("\\", "/")
    if not rel:
        if allow_empty:
            return ""
        raise HTTPException(status_code=422, detail="rel_path 必填")
    if must_file and not rel.endswith(".fsm.json"):
        raise HTTPException(status_code=422, detail="状态机文件必须以 .fsm.json 结尾")
    root = FSM_DIR.resolve()
    p = (FSM_DIR / rel).resolve()
    if p != root and root not in p.parents:
        raise HTTPException(status_code=400, detail="路径越界")
    if require_exists:
        if must_dir and not p.is_dir():
            raise HTTPException(status_code=404, detail=f"目录不存在: {rel}")
        if must_file and not p.is_file():
            raise HTTPException(status_code=404, detail=f"文件不存在: {rel}")
    return rel


def _read_spec(p: os.PathLike) -> dict[str, Any]:
    """读取 .fsm.json 并做基本校验，解析失败抛 422。"""
    try:
        with open(p, "r", encoding="utf-8") as f:
            data = json.load(f)
    except json.JSONDecodeError as exc:
        raise HTTPException(status_code=422, detail=f"JSON 解析失败: {exc}")
    except OSError as exc:
        raise HTTPException(status_code=500, detail=f"读取失败: {exc}")
    if not isinstance(data, dict):
        raise HTTPException(status_code=422, detail="文件内容必须是对象")
    return data


@router.get("/trees")
def list_trees(_=Depends(get_current_user)):
    """状态机文件列表 + 相对路径 + 真实目录（前端目录树视图用）。"""
    files_out = []
    for p in sorted(FSM_DIR.rglob("*.fsm.json")):
        rel = os.path.relpath(p, FSM_DIR).replace("\\", "/")
        files_out.append({
            "name": p.name,
            "path": str(p),
            "rel_path": rel,
        })
    dirs: list[str] = []
    for root_dir, dnames, _ in os.walk(FSM_DIR):
        for dn in sorted(dnames):
            rel = os.path.relpath(os.path.join(root_dir, dn), FSM_DIR).replace("\\", "/")
            dirs.append(rel)
    return {"files": files_out, "dirs": dirs}


@router.get("/trees/{name}")
def get_tree(name: str, _=Depends(get_current_user)):
    """读取单个状态机文件（name = 相对路径，含 .fsm.json）。"""
    rel = _safe_rel(name, must_file=True)
    p = FSM_DIR / rel
    return {"name": p.name, "path": str(p), "rel_path": rel, "spec": _read_spec(p)}


@router.post("/trees/{name}")
def save_tree(name: str, body: dict[str, Any], _=Depends(engineer_only)):
    """保存状态机 spec 写回文件（编辑器保存入口）。"""
    rel = _safe_rel(name, must_file=True)
    if not isinstance(body, dict) or not isinstance(body.get("objects"), list) \
            or not isinstance(body.get("connections"), list):
        raise HTTPException(status_code=422, detail="spec 必须包含 objects/connections 列表")
    p = FSM_DIR / rel
    try:
        with open(p, "w", encoding="utf-8") as f:
            json.dump(body, f, ensure_ascii=False, indent=2)
    except OSError as exc:
        raise HTTPException(status_code=500, detail=f"写入失败: {exc}")
    return {"ok": True}


@router.post("/dirs")
def create_dir(body: dict[str, Any], _=Depends(engineer_only)):
    """创建目录（可嵌套，如 rules/sub）。"""
    rel = _safe_rel(body.get("rel_path"), require_exists=False)
    p = FSM_DIR / rel
    if p.exists():
        raise HTTPException(status_code=409, detail=f"已存在: {rel}")
    p.mkdir(parents=True, exist_ok=False)
    return {"ok": True, "rel_path": rel}


@router.delete("/dirs")
def delete_dir(body: dict[str, Any], _=Depends(engineer_only)):
    """递归删除目录（含其中全部 .fsm.json）。"""
    rel = _safe_rel(body.get("rel_path"), must_dir=True)
    shutil.rmtree(FSM_DIR / rel)
    return {"ok": True}


@router.post("/files")
def create_file(body: dict[str, Any], _=Depends(engineer_only)):
    """创建空状态机文件（xx.fsm.json，默认空图）。"""
    rel = _safe_rel(body.get("rel_path"), must_file=True, require_exists=False)
    p = FSM_DIR / rel
    if p.exists():
        raise HTTPException(status_code=409, detail=f"已存在: {rel}")
    name = p.stem[:-len(".fsm")] if p.stem.endswith(".fsm") else p.stem
    spec = {**EMPTY_SPEC, "name": name}
    p.parent.mkdir(parents=True, exist_ok=True)
    with open(p, "w", encoding="utf-8") as f:
        json.dump(spec, f, ensure_ascii=False, indent=2)
    return {"ok": True, "rel_path": rel}


@router.delete("/files")
def delete_file(body: dict[str, Any], _=Depends(engineer_only)):
    """删除单个状态机文件。"""
    rel = _safe_rel(body.get("rel_path"), must_file=True)
    (FSM_DIR / rel).unlink()
    return {"ok": True}


@router.post("/rename")
def rename_entry(body: dict[str, Any], _=Depends(engineer_only)):
    """重命名文件或目录（new_name 含扩展名/目录名）。"""
    rel = _safe_rel(body.get("rel_path"))
    new_name = body.get("new_name")
    if not isinstance(new_name, str) or not new_name.strip():
        raise HTTPException(status_code=422, detail="new_name 必填")
    new_name = new_name.strip()
    src = FSM_DIR / rel
    if not src.exists():
        raise HTTPException(status_code=404, detail=f"不存在: {rel}")
    dst = src.parent / new_name
    if dst.exists():
        raise HTTPException(status_code=409, detail=f"已存在: {new_name}")
    src.rename(dst)
    return {"ok": True}


@router.post("/move")
def move_entry(body: dict[str, Any], _=Depends(engineer_only)):
    """移动文件/目录到目标目录（dest_dir 为空表示根目录）。"""
    rel = _safe_rel(body.get("rel_path"))
    dest_dir = _safe_rel(body.get("dest_dir") or "", allow_empty=True)
    src = FSM_DIR / rel
    if not src.exists():
        raise HTTPException(status_code=404, detail=f"不存在: {rel}")
    if dest_dir and (dest_dir == rel or dest_dir.startswith(rel + "/")):
        raise HTTPException(status_code=400, detail="不能移动到自身或其子目录")
    dst_dir = FSM_DIR / dest_dir if dest_dir else FSM_DIR
    if not dst_dir.is_dir():
        raise HTTPException(status_code=404, detail=f"目录不存在: {dest_dir or '(根)'}")
    dst = dst_dir / src.name
    if dst.exists():
        raise HTTPException(status_code=409, detail=f"已存在: {dst.relative_to(FSM_DIR)}")
    shutil.move(str(src), str(dst))
    return {"ok": True}
