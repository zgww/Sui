"""OTA: 安装包管理 + 升级任务 + 自动升级策略。engineer 专用。

升级流程(复用机器人现有 install.sh):
  1. SSH 连通性 + 版本检查
  2. (非强制且版本相同 -> 跳过)
  3. SCP 上传 zip 到 install_dir
  4. 执行 install.sh(自带备份到 robot_backup)
  5. stop + start 上位机程序
  6. 等待并读新版本校验
"""
import os
import re
import time
import hashlib
import threading
from pathlib import Path
from typing import List, Optional
from fastapi import APIRouter, Depends, HTTPException, UploadFile, File, Form
from fastapi.responses import FileResponse
from sqlalchemy.orm import Session

from ..database import get_db
from ..models import Robot, OtaPackage, OtaTask, RobotVersion
from ..schemas import OtaPackageOut, OtaTaskCreate, OtaTaskOut, Ok
from ..auth import engineer_only
from ..services import ssh_client, robot_api
from ..config import PKG_DIR

router = APIRouter(prefix="/api/ota", tags=["ota"])

# 后台任务执行锁池: robot_pk -> bool, 防止同机并发升级
_running: dict = {}
_lock = threading.Lock()


def _md5(path: str) -> str:
    h = hashlib.md5()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


# ---------- 包管理 ----------
@router.get("/packages", response_model=List[OtaPackageOut])
def list_packages(db: Session = Depends(get_db), _=Depends(engineer_only)):
    return db.query(OtaPackage).order_by(OtaPackage.created_at.desc()).all()


@router.post("/packages", response_model=OtaPackageOut)
def upload_package(
    file: UploadFile = File(...),
    version: str = Form(""),
    product_type: str = Form(""),
    channel: str = Form("upper"),
    notes: str = Form(""),
    force_flag: bool = Form(False),
    db: Session = Depends(get_db),
    user=Depends(engineer_only),
):
    if not file.filename:
        raise HTTPException(400, "缺少文件名")
    name = os.path.basename(file.filename)
    dest = PKG_DIR / f"{int(time.time())}_{name}"
    size = 0
    with open(dest, "wb") as f:
        while True:
            chunk = file.file.read(1 << 20)
            if not chunk:
                break
            f.write(chunk)
            size += len(chunk)
    # 尝试从文件名解析版本号: straitbot-xxx-v2.0.15-时间.zip
    parsed_ver = version
    if not parsed_ver:
        m = re.search(r"-v(\d+\.\d+\.\d+)", name)
        if m:
            parsed_ver = m.group(1)
    if not product_type:
        if "outdoor" in name.lower():
            product_type = "outdoor"
        elif "floor" in name.lower() or "indoor" in name.lower():
            product_type = "floor"
    pkg = OtaPackage(filename=name, version=parsed_ver, product_type=product_type,
                     channel=channel, size=size, md5=_md5(str(dest)), notes=notes,
                     force_flag=force_flag, created_by=user.username)
    db.add(pkg)
    db.commit()
    db.refresh(pkg)
    return pkg


@router.delete("/packages/{pid}", response_model=Ok)
def delete_package(pid: int, db: Session = Depends(get_db), _=Depends(engineer_only)):
    p = db.query(OtaPackage).filter(OtaPackage.id == pid).first()
    if not p:
        raise HTTPException(404, "包不存在")
    # 删除物理文件(按 filename 在 PKG_DIR 中找)
    for f in PKG_DIR.glob(f"*_{p.filename}"):
        try:
            f.unlink()
        except Exception:
            pass
    db.delete(p)
    db.commit()
    return Ok(msg="已删除")


@router.get("/packages/{pid}/download")
def download_package(pid: int, db: Session = Depends(get_db), _=Depends(engineer_only)):
    p = db.query(OtaPackage).filter(OtaPackage.id == pid).first()
    if not p:
        raise HTTPException(404, "包不存在")
    files = list(PKG_DIR.glob(f"*_{p.filename}"))
    if not files:
        raise HTTPException(404, "文件丢失")
    return FileResponse(str(files[0]), filename=p.filename)


# ---------- 升级任务 ----------
@router.get("/tasks", response_model=List[OtaTaskOut])
def list_tasks(limit: int = 100, db: Session = Depends(get_db), _=Depends(engineer_only)):
    return (db.query(OtaTask).order_by(OtaTask.created_at.desc())
            .limit(limit).all())


@router.get("/tasks/{tid}", response_model=OtaTaskOut)
def get_task(tid: int, db: Session = Depends(get_db), _=Depends(engineer_only)):
    t = db.query(OtaTask).filter(OtaTask.id == tid).first()
    if not t:
        raise HTTPException(404, "任务不存在")
    return t


@router.post("/tasks", response_model=Ok)
def create_tasks(body: OtaTaskCreate, db: Session = Depends(get_db), user=Depends(engineer_only)):
    pkg = db.query(OtaPackage).filter(OtaPackage.id == body.package_id).first()
    if not pkg:
        raise HTTPException(404, "安装包不存在")
    created = []
    for rid in body.robot_ids:
        r = db.query(Robot).filter(Robot.id == rid).first()
        if not r:
            continue
        t = OtaTask(robot_pk=r.id, package_id=pkg.id, package_filename=pkg.filename,
                    to_version=pkg.version, force=body.force, status="pending",
                    created_by=user.username)
        db.add(t)
        created.append(t)
    db.commit()
    # 异步触发执行
    from ..services import ota_runner
    for t in created:
        threading.Thread(target=ota_runner.run_task_safe, args=(t.id,), daemon=True).start()
    return Ok(msg=f"已创建 {len(created)} 个升级任务")


@router.post("/tasks/{tid}/retry", response_model=Ok)
def retry_task(tid: int, db: Session = Depends(get_db), _=Depends(engineer_only)):
    t = db.query(OtaTask).filter(OtaTask.id == tid).first()
    if not t:
        raise HTTPException(404, "任务不存在")
    t.status = "pending"
    t.log = (t.log or "") + "\n[retry] 重新排队"
    db.commit()
    from ..services import ota_runner
    threading.Thread(target=ota_runner.run_task_safe, args=(t.id,), daemon=True).start()
    return Ok(msg="已重新排队")
