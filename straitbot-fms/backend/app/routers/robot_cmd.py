"""指令调试 + 高频控制指令。engineer 专用。"""
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session
from ..database import get_db
from ..models import Robot
from ..schemas import CmdIn, CmdOut, Ok
from ..auth import engineer_only
from ..services import robot_api, ssh_client

router = APIRouter(prefix="/api/cmd", tags=["cmd"])


def _robot(rid, db):
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    return r


@router.post("/{rid}/raw", response_model=CmdOut)
def raw_cmd(rid: int, body: CmdIn, db: Session = Depends(get_db), user=Depends(engineer_only)):
    """任意 cmd 透传。"""
    r = _robot(rid, db)
    try:
        code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, body.cmd, body.data)
        return CmdOut(ok=(code == 0), raw={"code": code, "msg": msg, "data": data}, msg=msg)
    except Exception as e:  # noqa: BLE001
        return CmdOut(ok=False, msg=str(e))


@router.post("/{rid}/charge", response_model=CmdOut)
def cmd_charge(rid: int, action: int = 1, pile: int = 0,
               db: Session = Depends(get_db), user=Depends(engineer_only)):
    r = _robot(rid, db)
    try:
        robot_api.charge(r.ip, r.api_port, r.robot_id, action, pile)
        return CmdOut(ok=True, msg="已下发")
    except Exception as e:
        return CmdOut(ok=False, msg=str(e))


@router.post("/{rid}/home", response_model=CmdOut)
def cmd_home(rid: int, go_home: bool = True,
             db: Session = Depends(get_db), user=Depends(engineer_only)):
    r = _robot(rid, db)
    try:
        robot_api.reset_and_home(r.ip, r.api_port, r.robot_id, go_home)
        return CmdOut(ok=True, msg="已下发返航")
    except Exception as e:
        return CmdOut(ok=False, msg=str(e))


@router.post("/{rid}/selfcheck", response_model=CmdOut)
def cmd_selfcheck(rid: int, db: Session = Depends(get_db), user=Depends(engineer_only)):
    r = _robot(rid, db)
    try:
        robot_api.self_check(r.ip, r.api_port, r.robot_id)
        return CmdOut(ok=True, msg="已触发自检")
    except Exception as e:
        return CmdOut(ok=False, msg=str(e))


@router.post("/{rid}/clear_alert", response_model=CmdOut)
def cmd_clear_alert(rid: int, db: Session = Depends(get_db), user=Depends(engineer_only)):
    r = _robot(rid, db)
    try:
        robot_api.clear_nav_alert(r.ip, r.api_port, r.robot_id)
        return CmdOut(ok=True, msg="已清除导航告警")
    except Exception as e:
        return CmdOut(ok=False, msg=str(e))


@router.post("/{rid}/restart_app", response_model=CmdOut)
def cmd_restart_app(rid: int, db: Session = Depends(get_db), user=Depends(engineer_only)):
    """通过 SSH 重启机器人上位机程序(stop+start)。"""
    r = _robot(rid, db)
    script = f"""set -e
cd {r.install_dir}/robot 2>/dev/null || cd {r.install_dir}
./stop.sh 2>/dev/null || true
sleep 2
nohup ./start.sh >/tmp/restart_app.log 2>&1 &
sleep 1
echo restarted
"""
    try:
        out, err, rc = ssh_client.run_as_script(
            r.ip, script, r.ssh_port, r.ssh_user, r.ssh_pass, timeout=30)
        return CmdOut(ok=(rc == 0 and "restarted" in out),
                      raw={"stdout": out[-500:], "stderr": err[-500:], "rc": rc},
                      msg=("已重启" if rc == 0 else "重启失败"))
    except Exception as e:
        return CmdOut(ok=False, msg=str(e))


@router.post("/{rid}/reboot_os", response_model=CmdOut)
def cmd_reboot_os(rid: int, db: Session = Depends(get_db), user=Depends(engineer_only)):
    """重启整机(谨慎)。"""
    r = _robot(rid, db)
    try:
        ssh_client.run(r.ip, "sudo -n reboot || reboot", r.ssh_port, r.ssh_user, r.ssh_pass, timeout=8)
        return CmdOut(ok=True, msg="重启指令已发送")
    except Exception as e:
        return CmdOut(ok=False, msg=str(e))
