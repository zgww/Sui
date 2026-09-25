"""日志: 在线列目录、SFTP 拉取、上传(兼机器人文件服务)、下载、删除、保留策略。

上传接口 /api/logs/upload 同时充当 API 文档中的"文件服务 upload"。
机器人本体可 POST 上传日志到这里(参数: robot_id + filename + file)。
"""
import os
import time
import shutil
import zipfile
import tempfile
import asyncio
import subprocess
from pathlib import Path
from typing import List, Optional
from fastapi import APIRouter, Depends, HTTPException, UploadFile, File, Form, Query
from fastapi.responses import FileResponse, StreamingResponse
from sqlalchemy.orm import Session

from ..database import get_db
from ..models import Robot, UploadedLog, FetchedLog
from ..schemas import LogEntry, FetchLogIn, Ok
from ..auth import get_current_user, engineer_only
from ..services import ssh_client
from ..config import LOGS_DIR, settings

router = APIRouter(prefix="/api/logs", tags=["logs"])


def _robot(rid, db):
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    return r


def _robot_dir(robot_pk: int) -> Path:
    d = LOGS_DIR / str(robot_pk)
    d.mkdir(parents=True, exist_ok=True)
    return d


# ---------- 远程目录浏览(在线拉日志) ----------
@router.get("/{rid}/remote/list", response_model=List[LogEntry])
def remote_list(rid: int, sub: str = Query("", description="相对 log_dir 的子目录"),
                db: Session = Depends(get_db), _=Depends(engineer_only)):
    r = _robot(rid, db)
    target = (r.log_dir.rstrip("/") + "/" + sub.lstrip("/")) if sub else r.log_dir
    try:
        files = ssh_client.list_dir(r.ip, target, r.ssh_port, r.ssh_user, r.ssh_pass)
    except Exception as e:  # noqa: BLE001
        raise HTTPException(500, f"列目录失败: {e}")
    files.sort(key=lambda x: (x.is_dir, x.name), reverse=True)
    return files


@router.post("/{rid}/fetch", response_model=Ok)
def fetch_remote(rid: int, body: FetchLogIn,
                 db: Session = Depends(get_db), user=Depends(engineer_only)):
    """从机器人 SFTP 下载指定文件到平台归档。返回本地路径。"""
    r = _robot(rid, db)
    saved = []
    fail = []
    for rel in body.files:
        remote = r.log_dir.rstrip("/") + "/" + rel.lstrip("/")
        local = _robot_dir(r.id) / ("fetch_" + str(int(time.time())) + "_" +
                                     os.path.basename(rel))
        try:
            ssh_client.download_file(r.ip, remote, str(local),
                                     r.ssh_port, r.ssh_user, r.ssh_pass)
            size = local.stat().st_size
            db.add(FetchedLog(robot_pk=r.id, remote_path=remote, stored_path=str(local),
                              filename=os.path.basename(rel), size=size,
                              fetched_by=user.username))
            saved.append(os.path.basename(rel))
        except Exception as e:  # noqa: BLE001
            fail.append({"file": rel, "err": str(e)})
    db.commit()
    return Ok(ok=not fail, msg=f"已拉取 {len(saved)} 个; 失败 {len(fail)} 个",
              )


# ---------- 本地已归档日志(含上传的) ----------
@router.get("/{rid}/archived")
def archived_list(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    ups = (db.query(UploadedLog).filter(UploadedLog.robot_pk == rid)
           .order_by(UploadedLog.created_at.desc()).all())
    fets = (db.query(FetchedLog).filter(FetchedLog.robot_pk == rid)
            .order_by(FetchedLog.fetched_at.desc()).all())
    return {
        "uploaded": [{
            "id": u.id, "filename": u.filename, "size": u.size,
            "source": u.source, "ts": u.created_at.isoformat() if u.created_at else None,
        } for u in ups],
        "fetched": [{
            "id": f.id, "filename": f.filename, "size": f.size,
            "remote_path": f.remote_path,
            "ts": f.fetched_at.isoformat() if f.fetched_at else None,
        } for f in fets],
    }


@router.get("/{rid}/archived/{kind}/{log_id}/download")
def archived_download(rid: int, kind: str, log_id: int,
                      db: Session = Depends(get_db), _=Depends(get_current_user)):
    if kind == "uploaded":
        rec = db.query(UploadedLog).filter(UploadedLog.id == log_id,
                                           UploadedLog.robot_pk == rid).first()
        path = rec.stored_path if rec else None
        fname = rec.filename if rec else None
    elif kind == "fetched":
        rec = db.query(FetchedLog).filter(FetchedLog.id == log_id,
                                          FetchedLog.robot_pk == rid).first()
        path = rec.stored_path if rec else None
        fname = rec.filename if rec else None
    else:
        raise HTTPException(400, "kind 必须是 uploaded|fetched")
    if not path or not os.path.exists(path):
        raise HTTPException(404, "文件不存在")
    return FileResponse(path, filename=fname or os.path.basename(path))


@router.delete("/{rid}/archived/{kind}/{log_id}", response_model=Ok)
def archived_delete(rid: int, kind: str, log_id: int,
                    db: Session = Depends(get_db), user=Depends(engineer_only)):
    if kind == "uploaded":
        rec = db.query(UploadedLog).filter(UploadedLog.id == log_id,
                                           UploadedLog.robot_pk == rid).first()
    else:
        rec = db.query(FetchedLog).filter(FetchedLog.id == log_id,
                                          FetchedLog.robot_pk == rid).first()
    if not rec:
        raise HTTPException(404, "记录不存在")
    try:
        if rec.stored_path and os.path.exists(rec.stored_path):
            os.remove(rec.stored_path)
    except Exception:
        pass
    db.delete(rec)
    db.commit()
    return Ok(msg="已删除")


# ---------- 上传(兼机器人文件服务) ----------
@router.post("/upload", response_model=Ok)
def upload_log(
    file: UploadFile = File(...),
    robot_id: int = Form(...),
    filename: str = Form(None),
    source: str = Form("manual"),
    db: Session = Depends(get_db),
    _=Depends(get_current_user),
):
    """上传日志到平台, 归档到对应机器人目录。

    注: 机器人本体调用此接口时不带 JWT。本期先要求登录; 如需放开给机器人直传,
    可在此处加 token 校验开关或单独路由。详见 README。
    """
    r = db.query(Robot).filter(Robot.id == robot_id).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    name = filename or file.filename or "unnamed.log"
    # 防目录穿越
    name = name.replace("..", "").replace("/", "_").replace("\\", "_")
    dest = _robot_dir(r.id) / name
    size = 0
    with open(dest, "wb") as f:
        while True:
            chunk = file.file.read(1 << 20)
            if not chunk:
                break
            f.write(chunk)
            size += len(chunk)
    db.add(UploadedLog(robot_pk=r.id, robot_id_label=str(r.robot_id), filename=name,
                       stored_path=str(dest), size=size, source=source))
    db.commit()
    return Ok(msg=f"已上传 {name} ({size}B)")


# ---------- 文件服务: 机器人下载(GET /api/files/download/...) ----------
@router.get("/files/download/{path:path}")
def file_service_download(path: str, _=Depends(get_current_user)):
    """对应 API 文档"文件下载"。path 相对 LOGS_DIR。"""
    safe = (LOGS_DIR / path).resolve()
    if not str(safe).startswith(str(LOGS_DIR.resolve())):
        raise HTTPException(403, "非法路径")
    if not safe.exists():
        raise HTTPException(404, "文件不存在")
    return FileResponse(str(safe), filename=safe.name)


# ========== 后端日志查看 ==========

DOCKER_SOCK = "/var/run/docker.sock"
CONTAINER_NAME = "straitbot-fms-backend"


def _docker_logs_api(lines: int = 200) -> str:
    """通过 Docker Unix Socket API 获取容器日志。"""
    url = f"http://localhost/containers/{CONTAINER_NAME}/logs?stdout=1&stderr=1&tail={lines}"
    try:
        # 用 subprocess + curl 读取, 二进制模式避免 UTF-8 解码错误
        result = subprocess.run(
            ["curl", "-s", "--unix-socket", DOCKER_SOCK, url],
            capture_output=True, timeout=15,
        )
        if result.returncode != 0:
            return f"获取日志失败: curl rc={result.returncode}"
        # Docker multiplex stream: strip 8-byte header per frame
        # Header: [1B stream_type][3B padding][4B size BE]
        raw = result.stdout
        cleaned: list[str] = []
        i = 0
        while i + 8 <= len(raw):
            size = int.from_bytes(raw[i+4:i+8], 'big')
            i += 8
            chunk = raw[i:i+size]
            i += size
            cleaned.append(chunk.decode('utf-8', errors='replace'))
        return "\n".join(cleaned)
    except Exception as e:
        return f"获取日志失败: {e}"


@router.get("/backend/tail")
def backend_log_tail(
    lines: int = Query(200, ge=10, le=5000),
    filter: Optional[str] = Query(None, description="关键字过滤"),
    _=Depends(engineer_only),
):
    """获取后端最近 N 行日志, 支持关键字过滤。"""
    raw = _docker_logs_api(lines)
    if filter:
        raw = "\n".join(l for l in raw.split("\n") if filter.lower() in l.lower())
    return {"lines": raw.split("\n")[-lines:], "total": len(raw.split("\n"))}


@router.get("/backend/export")
def backend_log_export(_=Depends(engineer_only)):
    """导出完整后端日志为文本文件。"""
    try:
        url = f"http://localhost/containers/{CONTAINER_NAME}/logs?stdout=1&stderr=1&tail=all"
        result = subprocess.run(
            ["curl", "-s", "--unix-socket", DOCKER_SOCK, url],
            capture_output=True, timeout=30,
        )
        # Strip Docker multiplex headers
        raw = result.stdout
        out = bytearray()
        i = 0
        while i + 8 <= len(raw):
            size = int.from_bytes(raw[i+4:i+8], 'big')
            i += 8
            out.extend(raw[i:i+size])
            i += size
        content = out.decode('utf-8', errors='replace')
    except Exception as e:
        content = f"导出失败: {e}"

    tmp = tempfile.NamedTemporaryFile(mode="w", suffix=".log", delete=False, encoding="utf-8")
    tmp.write(content)
    tmp.close()
    return FileResponse(tmp.name, filename=f"fms-backend-{time.strftime('%Y%m%d_%H%M%S')}.log",
                        media_type="text/plain")


@router.get("/backend/stream")
async def backend_log_stream(
    filter: Optional[str] = Query(None),
    _=Depends(engineer_only),
):
    """SSE 实时推送后端日志。"""
    async def generate():
        proc = None
        try:
            url = f"http://localhost/containers/{CONTAINER_NAME}/logs?stdout=1&stderr=1&tail=50&follow=1"
            proc = await asyncio.create_subprocess_exec(
                "curl", "-s", "-N", "--unix-socket", DOCKER_SOCK, url,
                stdout=asyncio.subprocess.PIPE,
                stderr=asyncio.subprocess.STDOUT,
            )
            while True:
                line = await proc.stdout.readline()
                if not line:
                    break
                text = line.decode(errors="replace").rstrip()
                if filter and filter.lower() not in text.lower():
                    continue
                yield f"data: {text}\n\n"
        except asyncio.CancelledError:
            pass
        finally:
            if proc:
                try:
                    proc.kill()
                except Exception:
                    pass

    return StreamingResponse(generate(), media_type="text/event-stream")
