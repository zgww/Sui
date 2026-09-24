"""一次性迁移：为 inspection_action_results 补 reference_image（抓拍图/参考图）。

背景：算法服务 /upload_tactics 的 referenceImageUrl 要用航点树编排时拍照动作点
配置的"抓拍图片"。早期动作结果没存这个字段，本脚本：

  1. init_db() 触发补列（与启动时 _ensure_columns 同一套，幂等）；
  2. 扫描所有航点 prefab，按 action_id 建立 -> 抓拍图 web 路径映射；
  3. 回填 reference_image 为空的历史动作结果。

运行（系统 Python，在 backend/ 目录下）：
    "C:\\Users\\Administrator\\AppData\\Local\\Programs\\Python\\Python312\\python.exe" \
        migrate_reference_image.py
"""
import json
from pathlib import Path

from app.config import WAYPOINT_PREFAB_DIR
from app.database import SessionLocal, init_db
from app.models.inspection import InspectionActionResult
from app.prefab.inspection_build import image_base_for_source
from app.prefab.registry import build


def iter_action_nodes(node):
    """递归产出树中所有 ActionPointNode。"""
    if node is None:
        return
    if getattr(node, "type", "") == "ActionPointNode":
        yield node
    for c in getattr(node, "child_nodes", []) or []:
        yield from iter_action_nodes(c)


def main() -> None:
    init_db()  # 建表 / 补缺失列（reference_image）

    # action_id -> reference_image web 路径
    mapping: dict[str, str] = {}
    root = Path(WAYPOINT_PREFAB_DIR)
    for p in root.rglob("*.prefab.json"):
        rel = str(p.relative_to(root)).replace("\\", "/")
        try:
            spec = json.loads(p.read_text(encoding="utf-8"))
        except Exception as e:  # noqa: BLE001
            print(f"跳过（解析失败）{rel}: {e}")
            continue
        image_base = image_base_for_source(rel)
        tree = build(spec.get("root") or {})
        for an in iter_action_nodes(tree):
            aid = str(getattr(an, "action_id", "") or "").strip()
            img = str(getattr(an, "imageUrl", "") or "").strip().lstrip("/")
            if aid and img:
                mapping[aid] = f"{image_base}/{img}"

    print(f"prefab 中带抓拍图的动作点: {len(mapping)}")

    db = SessionLocal()
    try:
        rows = (
            db.query(InspectionActionResult)
            .filter(
                (InspectionActionResult.reference_image == "")
                | (InspectionActionResult.reference_image.is_(None))
            )
            .all()
        )
        updated = 0
        for r in rows:
            ref = mapping.get(str(r.action_id or "").strip())
            if ref:
                r.reference_image = ref
                updated += 1
        db.commit()
        print(f"回填动作结果: {updated} / 待处理 {len(rows)}")
    finally:
        db.close()


if __name__ == "__main__":
    main()
