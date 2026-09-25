"""物模型定义加载器。

从 data/thing_model.json 加载物模型定义, 提供:
- get_model()     获取完整定义
- get_property()  获取某属性定义
- get_alert_text() 告警 ID → 中文描述
- get_status_text() 状态 ID → 中文描述
"""
from __future__ import annotations
import json
from pathlib import Path
from typing import Any, Optional
from functools import lru_cache

from ..config import DATA_DIR

MODEL_FILE = DATA_DIR / "thing_model.json"


@lru_cache(maxsize=1)
def _load() -> dict:
    if not MODEL_FILE.exists():
        return {}
    try:
        return json.loads(MODEL_FILE.read_text(encoding="utf-8"))
    except Exception:
        return {}


def reload():
    """重新加载(修改 thing_model.json 后调用)。"""
    _load.cache_clear()


def get_model() -> dict:
    return _load()


def get_property(group: str, field: str) -> Optional[dict]:
    props = _load().get("properties", {})
    return props.get(group, {}).get(field)


def get_alert_text(alert_id: int | str) -> str:
    return _load().get("alerts", {}).get(str(alert_id), f"未知告警({alert_id})")


def get_status_text(status: int | str) -> str:
    return _load().get("status_map", {}).get(str(status), f"状态{status}")


def get_product_type_text(pt: int | str) -> str:
    return _load().get("product_types", {}).get(str(pt), "未知")


def save_model(data: dict) -> None:
    """保存物模型定义(UI 编辑用)。"""
    MODEL_FILE.write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding="utf-8")
    reload()
