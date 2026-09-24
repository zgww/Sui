"""系统设置: 平台信息、当前账号、(可扩展)全局参数。"""
from fastapi import APIRouter, Depends
from ..config import settings, APP_VERSION, FMS_MODE
from ..schemas import UserOut
from ..auth import get_current_user

router = APIRouter(prefix="/api/settings", tags=["settings"])


@router.get("/info")
def info(_=Depends(get_current_user)):
    return {
        "app_name": settings.app_name,
        "version": APP_VERSION,
        "mode": FMS_MODE,
        "poll_status_interval_sec": settings.poll_status_interval_sec,
        "poll_meta_interval_sec": settings.poll_meta_interval_sec,
        "default_log_retention_days": settings.default_log_retention_days,
    }


@router.get("/users/me", response_model=UserOut)
def whoami(user=Depends(get_current_user)):
    return user
