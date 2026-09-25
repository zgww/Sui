"""物模型管理: 读取/编辑 thing_model.json。"""
import json
from fastapi import APIRouter, Depends
from pydantic import BaseModel
from typing import Any

from ..auth import engineer_only, get_current_user
from ..thing_model import definition

router = APIRouter(prefix="/api/thing-model", tags=["thing-model"])


@router.get("")
def get_model(_=Depends(get_current_user)):
    """获取完整物模型定义。"""
    return definition.get_model()


@router.put("")
def save_model(body: dict, _=Depends(engineer_only)):
    """保存物模型定义。"""
    definition.save_model(body)
    return {"ok": True, "msg": "物模型已保存"}


@router.get("/alerts")
def get_alerts(_=Depends(get_current_user)):
    """获取告警码映射(给前端显示用)。"""
    return definition.get_model().get("alerts", {})


@router.get("/status-map")
def get_status_map(_=Depends(get_current_user)):
    """获取状态映射。"""
    return definition.get_model().get("status_map", {})


@router.get("/product-types")
def get_product_types(_=Depends(get_current_user)):
    """获取产品类型映射。"""
    return definition.get_model().get("product_types", {})
