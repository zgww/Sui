"""机器人扫描发现: 扫网段 + 一键批量添加。

- POST /api/scan       扫描网段(异步, 直接返回结果)
- GET  /api/scan/known 返回已添加 IP 集合(前端用来标记"已添加")
- POST /api/scan/add   批量添加选中的机器人
"""
from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel, Field
from sqlalchemy.orm import Session
from typing import List, Optional

from ..database import get_db
from ..models import Robot
from ..schemas import Ok
from ..auth import engineer_only, get_current_user
from ..services import scanner

router = APIRouter(prefix="/api/scan", tags=["scan"])


@router.get("/local_networks")
def local_networks(_=Depends(get_current_user)):
    """探测本机所在的所有网段, 供前端扫描面板默认填充。"""
    nets = scanner.detect_local_networks()
    return {"networks": nets, "default": nets[0]["cidr"] if nets else "192.168.1.0/24"}


class ScanIn(BaseModel):
    cidr: str = Field(default="192.168.6.0/24", description="网段, 如 192.168.6.0/24")
    api_port: int = 6002
    timeout: float = 1.0


@router.post("")
def scan(body: ScanIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """扫描网段, 返回在线机器人列表(含是否已添加 + 已添加机器人的 SSH 凭据)。"""
    try:
        results = scanner.scan_network(body.cidr, body.api_port, body.timeout)
    except ValueError as e:
        raise HTTPException(400, str(e))
    # 标记已添加 + 回填当前 SSH 凭据
    added = {r.ip: r for r in db.query(Robot).all()}
    for r in results:
        ex = added.get(r["ip"])
        if ex:
            r["already_added"] = True
            r["existing_name"] = ex.name
            r["existing_robot_id"] = ex.robot_id
            r["ssh_user"] = ex.ssh_user
            r["ssh_pass"] = ex.ssh_pass  # 已配置的, 显示给工程师(便于核对)
        else:
            r["already_added"] = False
            r["ssh_user"] = "nav"
            r["ssh_pass"] = "nav2022"  # 默认值, 用户可在前端改
    return {"count": len(results), "items": results, "scanned_cidr": body.cidr}


@router.get("/known")
def known_ips(db: Session = Depends(get_db), _=Depends(engineer_only)):
    """已添加的机器人 IP/robot_id 集合。"""
    return [{"ip": r.ip, "robot_id": r.robot_id, "name": r.name} for r in db.query(Robot).all()]


class AddOne(BaseModel):
    ip: str
    robot_id: int
    name: Optional[str] = None
    ssh_user: str = "nav"
    ssh_pass: str = "nav2022"
    ssh_port: int = 22
    product_type: str = ""


class AddBatch(BaseModel):
    robots: List[AddOne]


@router.post("/add", response_model=Ok)
def add_batch(body: AddBatch, db: Session = Depends(get_db), user=Depends(engineer_only)):
    """批量添加扫描发现的机器人。"""
    existing_ips = {r.ip for r in db.query(Robot).all()}
    added = 0
    skipped = 0
    for r in body.robots:
        if r.ip in existing_ips:
            skipped += 1
            continue
        # 产品类型: 用户传了就用, 否则默认 outdoor(用户可后改)
        pt = r.product_type or "outdoor"
        name = r.name or f"机器人-{r.ip.split('.')[-1]}"
        robot = Robot(
            name=name, robot_id=r.robot_id, ip=r.ip, api_port=6002, product_type=pt,
            ssh_user=r.ssh_user, ssh_pass=r.ssh_pass, ssh_port=r.ssh_port,
            log_dir="/home/nav/robot/robot/filelog", install_dir="/home/nav/robot",
            version_file="/home/nav/robot/robot/version",
            poll_status=True, poll_meta=True, log_retention_days=30, enabled=True,
        )
        db.add(robot)
        added += 1
    db.commit()
    return Ok(ok=True, msg=f"已添加 {added} 台, 跳过 {skipped} 台(已存在)")
