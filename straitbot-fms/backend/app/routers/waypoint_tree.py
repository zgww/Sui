"""航点树管理: 基于文件的树形航点 CRUD + 从 inspection.json 导入。

数据存储: data/robot/{robot_pk}/WaypointsTree.json
树形结构, 任意层级, 节点类型: WaypointNode / ActionNode / TaskPointNode / OrbRegistration。
"""
import json
import uuid
from pathlib import Path
from typing import Any, Optional

from fastapi import APIRouter, Depends, HTTPException, UploadFile, File
from pydantic import BaseModel
from sqlalchemy.orm import Session

from ..database import get_db
from ..models import Robot
from ..auth import engineer_only, get_current_user
from ..config import DATA_DIR

router = APIRouter(prefix="/api/waypoint-tree", tags=["waypoint-tree"])


def _robot_dir(rid: int) -> Path:
    """机器人数据目录: data/robot/{rid}/"""
    d = DATA_DIR / "robot" / str(rid)
    d.mkdir(parents=True, exist_ok=True)
    return d


def _tree_path(rid: int) -> Path:
    return _robot_dir(rid) / "WaypointsTree.json"


def _robot(rid: int, db: Session) -> Robot:
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    return r


def _new_id() -> str:
    return uuid.uuid4().hex


def _make_root() -> dict:
    """创建空的根节点。"""
    return {
        "name": "航点树",
        "enable": True,
        "id": "root",
        "nodeType": "Root",
        "children": [],
    }


# ========== 树读写 ==========

@router.get("/{rid}/tree")
def get_tree(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """读取机器人的航点树 JSON。不存在则返回空树。"""
    _robot(rid, db)
    p = _tree_path(rid)
    if p.exists():
        try:
            return json.loads(p.read_text(encoding="utf-8"))
        except Exception:
            pass
    return _make_root()


class TreeSaveIn(BaseModel):
    tree: dict


@router.put("/{rid}/tree")
def save_tree(rid: int, body: TreeSaveIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """保存整个航点树 JSON。"""
    _robot(rid, db)
    p = _tree_path(rid)
    p.write_text(json.dumps(body.tree, ensure_ascii=False, indent=2), encoding="utf-8")
    return {"ok": True, "msg": "已保存"}


# ========== 从 inspection.json 导入 ==========

class ImportInspectionIn(BaseModel):
    data: dict  # inspection.json 解析后的 dict
    replace: bool = True  # True=替换整棵树; False=追加到根节点 children
    merge: bool = False   # True=按index匹配合并, 保留OrbRegistration节点


@router.post("/{rid}/import-inspection")
def import_inspection(rid: int, body: ImportInspectionIn,
                      db: Session = Depends(get_db), _=Depends(engineer_only)):
    """从 inspection.json 格式导入, 生成航点树。

    inspection.json 结构:
      { "waypoint": [ { id, index, type, pose, action: [...] } ] }

    转换规则:
      - 每个 waypoint → WaypointNode (保留 id)
      - waypoint 下的每个 action → ActionNode (保留 id), 作为该 waypoint 的子节点
    """
    _robot(rid, db)
    data = body.data
    waypoints = data.get("waypoint", [])
    if not isinstance(waypoints, list):
        raise HTTPException(400, "inspection.json 缺少 waypoint 数组")

    children = []
    for wp in waypoints:
        wp_node = {
            "name": f"航点{wp.get('index', '?')}",
            "enable": True,
            "id": wp.get("id") or _new_id(),
            "nodeType": "WaypointNode",
            "pose": wp.get("pose", {"theta": 0.0, "point": {"x": 0, "y": 0, "z": 0}}),
            "index": wp.get("index", 0),
            "type": wp.get("type", 0),
            "children": [],
        }
        for act in wp.get("action", []):
            act_node = {
                "name": act.get("steer_point_name") or f"动作{act.get('type', '')}",
                "enable": True,
                "id": act.get("id") or _new_id(),
                "nodeType": "ActionNode",
                "ptz_param": act.get("ptz_param", {}),
                "lift_height": act.get("lift_height", 0.0),
                "thermometry_points": act.get("thermometry_points", []),
                "snap_shot_url": act.get("snap_shot_url", ""),
                "type": act.get("type", 0),
                "steer_point_name": act.get("steer_point_name", ""),
                "children": [],
            }
            wp_node["children"].append(act_node)
        children.append(wp_node)

    if body.replace:
        tree = _make_root()
        tree["children"] = children
    elif body.merge:
        # 合并模式: 按 index 匹配已有航点, 更新 actions, 保留 OrbRegistration
        p = _tree_path(rid)
        if p.exists():
            try:
                tree = json.loads(p.read_text(encoding="utf-8"))
            except Exception:
                tree = _make_root()
        else:
            tree = _make_root()
        old_children = tree.get("children", [])
        # 建立 old waypoint index → node 映射
        old_by_idx: dict[int, dict] = {}
        for old in old_children:
            if old.get("nodeType") == "WaypointNode":
                idx = old.get("index")
                if idx is not None:
                    old_by_idx[idx] = old
        merged = []
        for wp_node in children:
            idx = wp_node.get("index")
            if idx is not None and idx in old_by_idx:
                old_wp = old_by_idx[idx]
                # 保留 OrbRegistration 子节点
                orb_nodes = [c for c in old_wp.get("children", []) if c.get("nodeType") == "OrbRegistration"]
                # 保留非 ActionNode 子节点
                other_nodes = [c for c in old_wp.get("children", [])
                              if c.get("nodeType") not in ("ActionNode", "OrbRegistration")]
                # 合并: 新 actions + 旧 OrbRegistration + 旧其他节点
                new_children = wp_node.get("children", []) + orb_nodes + other_nodes
                old_wp["children"] = new_children
                # 更新 action 列表（用新的覆盖旧的同 ID）
                merged.append(old_wp)
            else:
                merged.append(wp_node)
        tree["children"] = merged
    else:
        # 追加: 读取现有树, 添加到根 children
        p = _tree_path(rid)
        if p.exists():
            try:
                tree = json.loads(p.read_text(encoding="utf-8"))
            except Exception:
                tree = _make_root()
        else:
            tree = _make_root()
        tree.setdefault("children", []).extend(children)

    p = _tree_path(rid)
    p.write_text(json.dumps(tree, ensure_ascii=False, indent=2), encoding="utf-8")

    cnt_wp = len(children)
    cnt_act = sum(len(c.get("children", [])) for c in children)
    return {"ok": True, "msg": f"导入完成: {cnt_wp} 航点 / {cnt_act} 动作", "tree": tree}


# ========== 上传 inspection.json 文件导入 ==========

@router.post("/{rid}/import-inspection/file")
async def import_inspection_file(rid: int, replace: bool = True, merge: bool = False,
                                 file: UploadFile = File(...),
                                 db: Session = Depends(get_db),
                                 _=Depends(engineer_only)):
    """上传 inspection.json 文件并导入。"""
    _robot(rid, db)
    content = await file.read()
    try:
        data = json.loads(content)
    except Exception:
        raise HTTPException(400, "无效的 JSON 文件")
    return import_inspection(rid, ImportInspectionIn(data=data, replace=replace, merge=merge), db, _)


# ========== 新建节点 ==========

class CreateNodeIn(BaseModel):
    nodeType: str = "WaypointNode"
    name: str = ""
    parentId: Optional[str] = None  # None=添加到根 children
    # 可选初始字段
    extra: dict = {}


@router.post("/{rid}/node")
def create_node(rid: int, body: CreateNodeIn,
                db: Session = Depends(get_db), _=Depends(engineer_only)):
    """新建节点并挂到指定父节点下。返回新节点。"""
    _robot(rid, db)
    p = _tree_path(rid)
    tree = json.loads(p.read_text(encoding="utf-8")) if p.exists() else _make_root()

    node = _create_default_node(body.nodeType, body.name, body.extra)

    parent = _find_node(tree, body.parentId) if body.parentId else tree
    if parent is None:
        raise HTTPException(404, f"父节点 {body.parentId} 不存在")
    parent.setdefault("children", []).append(node)

    p.write_text(json.dumps(tree, ensure_ascii=False, indent=2), encoding="utf-8")
    return node


def _create_default_node(node_type: str, name: str, extra: dict) -> dict:
    """按节点类型创建默认节点。"""
    nid = _new_id()
    base = {
        "name": name or f"新节点",
        "enable": True,
        "id": nid,
        "nodeType": node_type,
        "children": [],
    }
    if node_type == "WaypointNode":
        base["pose"] = extra.get("pose", {"theta": 0.0, "point": {"x": 0, "y": 0, "z": 0}})
        base["index"] = extra.get("index", 0)
        base["type"] = extra.get("type", 0)
    elif node_type == "ActionNode":
        base["ptz_param"] = extra.get("ptz_param", {"focus": 0, "zoom": 1.0, "tilt": 0.0, "pan": 0.0, "focal_len": 0})
        base["lift_height"] = extra.get("lift_height", 0.0)
        base["thermometry_points"] = extra.get("thermometry_points", [])
        base["snap_shot_url"] = extra.get("snap_shot_url", "")
        base["type"] = extra.get("type", 1000)
        base["steer_point_name"] = extra.get("steer_point_name", "")
    elif node_type == "OrbRegistration":
        base["refImageUrl"] = extra.get("refImageUrl", "")
        base["ptz"] = extra.get("ptz", {"focus": 0, "zoom": 1.0, "tilt": 0.0, "pan": 0.0, "focal_len": 0})
        base["lift_height"] = extra.get("lift_height", 0.0)
        base["pose"] = extra.get("pose", {"theta": 0.0, "point": {"x": 0, "y": 0, "z": 0}})
    # TaskPointNode / GroupNode 无额外字段
    return base


def _find_node(tree: dict, node_id: str) -> Optional[dict]:
    """深度搜索树, 找到指定 id 的节点。"""
    if tree.get("id") == node_id:
        return tree
    for child in tree.get("children", []):
        found = _find_node(child, node_id)
        if found is not None:
            return found
    return None


# ========== 更新节点 ==========

class UpdateNodeIn(BaseModel):
    data: dict  # 完整节点数据


@router.put("/{rid}/node/{node_id}")
def update_node(rid: int, node_id: str, body: UpdateNodeIn,
                db: Session = Depends(get_db), _=Depends(engineer_only)):
    """更新指定节点。"""
    _robot(rid, db)
    p = _tree_path(rid)
    if not p.exists():
        raise HTTPException(404, "航点树不存在")
    tree = json.loads(p.read_text(encoding="utf-8"))

    node = _find_node(tree, node_id)
    if node is None:
        raise HTTPException(404, f"节点 {node_id} 不存在")

    # 更新字段 (保留 id, nodeType, children)
    saved_children = node.get("children", [])
    node.clear()
    node.update(body.data)
    node["id"] = node_id  # 确保 id 不变
    if "children" not in node:
        node["children"] = saved_children

    p.write_text(json.dumps(tree, ensure_ascii=False, indent=2), encoding="utf-8")
    return node


# ========== 删除节点 ==========

@router.delete("/{rid}/node/{node_id}")
def delete_node(rid: int, node_id: str,
                db: Session = Depends(get_db), _=Depends(engineer_only)):
    """删除指定节点 (及其子树)。"""
    _robot(rid, db)
    p = _tree_path(rid)
    if not p.exists():
        raise HTTPException(404, "航点树不存在")
    tree = json.loads(p.read_text(encoding="utf-8"))

    # 不能删根节点
    if tree.get("id") == node_id:
        raise HTTPException(400, "不能删除根节点")

    parent = _find_parent(tree, node_id)
    if parent is None:
        raise HTTPException(404, f"节点 {node_id} 不存在")
    parent["children"] = [c for c in parent.get("children", []) if c.get("id") != node_id]

    p.write_text(json.dumps(tree, ensure_ascii=False, indent=2), encoding="utf-8")
    return {"ok": True, "msg": "已删除"}


def _find_parent(tree: dict, node_id: str) -> Optional[dict]:
    """找到指定 id 节点的父节点。"""
    for child in tree.get("children", []):
        if child.get("id") == node_id:
            return tree
        found = _find_parent(child, node_id)
        if found is not None:
            return found
    return None


# ========== 复制节点 ==========

class CopyNodeIn(BaseModel):
    nodeId: str
    targetParentId: Optional[str] = None  # None=根 children


@router.post("/{rid}/node/copy")
def copy_node(rid: int, body: CopyNodeIn,
              db: Session = Depends(get_db), _=Depends(engineer_only)):
    """复制节点 (含子树) 到目标父节点下, 所有 id 重新生成。"""
    _robot(rid, db)
    p = _tree_path(rid)
    if not p.exists():
        raise HTTPException(404, "航点树不存在")
    tree = json.loads(p.read_text(encoding="utf-8"))

    src = _find_node(tree, body.nodeId)
    if src is None:
        raise HTTPException(404, f"节点 {body.nodeId} 不存在")

    import copy
    cloned = copy.deepcopy(src)
    _regenerate_ids(cloned)

    parent = _find_node(tree, body.targetParentId) if body.targetParentId else tree
    if parent is None:
        raise HTTPException(404, f"目标父节点 {body.targetParentId} 不存在")
    parent.setdefault("children", []).append(cloned)

    p.write_text(json.dumps(tree, ensure_ascii=False, indent=2), encoding="utf-8")
    return cloned


def _regenerate_ids(node: dict):
    """递归重新生成所有节点的 id。"""
    node["id"] = _new_id()
    for child in node.get("children", []):
        _regenerate_ids(child)


# ========== 移动节点 (拖拽排序) ==========

class MoveNodeIn(BaseModel):
    nodeId: str
    targetParentId: Optional[str] = None  # None=根
    position: int = -1  # -1=末尾; 否则=目标位置


@router.post("/{rid}/node/move")
def move_node(rid: int, body: MoveNodeIn,
              db: Session = Depends(get_db), _=Depends(engineer_only)):
    """移动节点到目标父节点下的指定位置。"""
    _robot(rid, db)
    p = _tree_path(rid)
    if not p.exists():
        raise HTTPException(404, "航点树不存在")
    tree = json.loads(p.read_text(encoding="utf-8"))

    if tree.get("id") == body.nodeId:
        raise HTTPException(400, "不能移动根节点")

    # 从原位置移除
    old_parent = _find_parent(tree, body.nodeId)
    if old_parent is None:
        raise HTTPException(404, f"节点 {body.nodeId} 不存在")
    node = None
    new_children = []
    for c in old_parent.get("children", []):
        if c.get("id") == body.nodeId:
            node = c
        else:
            new_children.append(c)
    old_parent["children"] = new_children
    if node is None:
        raise HTTPException(404, f"节点 {body.nodeId} 不存在")

    # 不能移动到自己的子树里
    if body.targetParentId and _is_descendant(node, body.targetParentId):
        raise HTTPException(400, "不能移动到自身的子节点下")

    # 插入到目标位置
    target_parent = _find_node(tree, body.targetParentId) if body.targetParentId else tree
    if target_parent is None:
        raise HTTPException(404, f"目标父节点 {body.targetParentId} 不存在")
    children = target_parent.setdefault("children", [])
    if body.position < 0 or body.position >= len(children):
        children.append(node)
    else:
        children.insert(body.position, node)

    p.write_text(json.dumps(tree, ensure_ascii=False, indent=2), encoding="utf-8")
    return {"ok": True, "msg": "已移动"}


def _is_descendant(node: dict, target_id: str) -> bool:
    """检查 target_id 是否是 node 的后代 (防止循环移动)。"""
    for child in node.get("children", []):
        if child.get("id") == target_id:
            return True
        if _is_descendant(child, target_id):
            return True
    return False


# ========== 创建分组 (多选) ==========

class CreateGroupIn(BaseModel):
    nodeIds: list[str]  # 要分组的节点 id 列表
    name: str = "分组"


@router.post("/{rid}/node/group")
def create_group(rid: int, body: CreateGroupIn,
                 db: Session = Depends(get_db), _=Depends(engineer_only)):
    """创建分组节点, 将选中的多个节点收纳到分组下。

    逻辑:
      1. DFS 遍历找到第一个选中节点在树中的位置 (parent + index) 作为插入点
      2. 从树中移除所有选中节点
      3. 创建 GroupNode, 将移除的节点按原顺序作为其 children
      4. 将 GroupNode 插入到第 1 步确定的位置
    """
    _robot(rid, db)
    p = _tree_path(rid)
    if not p.exists():
        raise HTTPException(404, "航点树不存在")
    tree = json.loads(p.read_text(encoding="utf-8"))

    if not body.nodeIds:
        raise HTTPException(400, "请至少选择一个节点")

    selected_set = set(body.nodeIds)

    # 不能对根节点分组
    if tree.get("id") in selected_set:
        raise HTTPException(400, "不能对根节点创建分组")

    # 1. DFS 找到第一个选中节点的位置 (parent, index)
    insert_parent: Optional[dict] = None
    insert_index = 0

    def _find_first(node: dict, parent: Optional[dict]) -> bool:
        nonlocal insert_parent, insert_index
        if parent is not None:
            for i, child in enumerate(node.get("children", [])):
                if child.get("id") in selected_set:
                    insert_parent = node
                    insert_index = i
                    return True
                if _find_first(child, node):
                    return True
        else:
            # 根节点
            for i, child in enumerate(node.get("children", [])):
                if child.get("id") in selected_set:
                    insert_parent = node
                    insert_index = i
                    return True
                if _find_first(child, node):
                    return True
        return False

    if not _find_first(tree, None):
        raise HTTPException(404, "未找到选中的节点")

    # 2. 从树中收集并移除所有选中节点 (保持 DFS 顺序)
    collected: list[dict] = []

    def _collect_and_remove(node: dict):
        children = node.get("children", [])
        remaining = []
        for child in children:
            if child.get("id") in selected_set:
                collected.append(child)
            else:
                remaining.append(child)
        node["children"] = remaining
        for child in node["children"]:
            _collect_and_remove(child)

    _collect_and_remove(tree)

    if not collected:
        raise HTTPException(404, "未找到选中的节点")

    # 3. 创建 GroupNode
    group_node = {
        "name": body.name or "分组",
        "enable": True,
        "id": _new_id(),
        "nodeType": "GroupNode",
        "children": collected,
    }

    # 4. 插入 GroupNode 到原第一个选中节点的位置
    if insert_parent is not None:
        insert_parent["children"].insert(insert_index, group_node)
    else:
        tree["children"].insert(insert_index, group_node)

    p.write_text(json.dumps(tree, ensure_ascii=False, indent=2), encoding="utf-8")
    return group_node


# ========== 导出为文件 ==========

from fastapi.responses import StreamingResponse, FileResponse
from io import BytesIO
from datetime import datetime
import base64
import re


@router.get("/{rid}/export/file")
def export_file(rid: int, db: Session = Depends(get_db)):
    """导出航点树为可下载的 JSON 文件（无需认证，方便新窗口下载）。"""
    from urllib.parse import quote
    r = _robot(rid, db)
    p = _tree_path(rid)
    tree = json.loads(p.read_text(encoding="utf-8")) if p.exists() else _make_root()
    content = json.dumps(tree, ensure_ascii=False, indent=2).encode("utf-8")
    fname = f"WaypointsTree_{r.name}_{datetime.utcnow().strftime('%Y%m%d_%H%M%S')}.json"
    encoded_fname = quote(fname, safe='')
    return StreamingResponse(
        BytesIO(content),
        media_type="application/octet-stream",
        headers={
            "Content-Disposition": f"attachment; filename*=UTF-8''{encoded_fname}",
        },
    )


# ========== ORB 配准参考图抓拍 ==========

def _nav_ref_dir(rid: int) -> Path:
    """机器人导航参考图目录: data/robot/{rid}/navRefImg/"""
    d = _robot_dir(rid) / "navRefImg"
    d.mkdir(parents=True, exist_ok=True)
    return d


class CaptureRefImageIn(BaseModel):
    image: str  # base64 data URL (data:image/jpeg;base64,xxxx)


@router.post("/{rid}/capture-ref-image")
def capture_ref_image(rid: int, body: CaptureRefImageIn,
                      db: Session = Depends(get_db), _=Depends(engineer_only)):
    """保存抓拍的参考图到 data/robot/{rid}/navRefImg/{uuid}.jpg。

    返回相对路径 navRefImg/{uuid}.jpg, 前端可直接拼接为 /api/waypoint-tree/{rid}/ref-image/{filename} 访问。
    """
    _robot(rid, db)

    # 解析 base64 data URL
    m = re.match(r"data:image/\w+;base64,(.+)", body.image)
    if not m:
        raise HTTPException(400, "无效的图片数据 (期望 data:image/...;base64,...)")
    raw = base64.b64decode(m.group(1))

    filename = f"{_new_id()}.jpg"
    filepath = _nav_ref_dir(rid) / filename
    filepath.write_bytes(raw)

    rel_path = f"navRefImg/{filename}"
    return {"ok": True, "path": rel_path, "filename": filename}


@router.get("/{rid}/ref-image/{filename}")
def get_ref_image(rid: int, filename: str,
                  db: Session = Depends(get_db)):
    """获取 ORB 配准参考图 (公开接口, <img> 标签直接加载无需 token)。"""
    _robot(rid, db)
    # 防止路径穿越
    if "/" in filename or "\\" in filename or ".." in filename:
        raise HTTPException(400, "非法文件名")
    filepath = _nav_ref_dir(rid) / filename
    if not filepath.exists():
        raise HTTPException(404, "参考图不存在")
    return FileResponse(str(filepath), media_type="image/jpeg")
