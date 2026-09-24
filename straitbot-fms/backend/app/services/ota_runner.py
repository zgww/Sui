"""OTA 升级执行引擎(后台线程)。

复用机器人现有 install.sh(自带备份到 robot_backup)。
步骤见 routers/ota.py 顶部注释。
"""
import os
import time
import threading
from datetime import datetime
from sqlalchemy.orm import Session

from ..database import SessionLocal
from ..models import Robot, OtaPackage, OtaTask, RobotVersion
from . import ssh_client, robot_api

# 同机串行锁
_machine_locks: dict = {}
_locks_guard = threading.Lock()


def _machine_lock(pk: int):
    with _locks_guard:
        lk = _machine_locks.get(pk)
        if lk is None:
            lk = threading.Lock()
            _machine_locks[pk] = lk
        return lk


def _append(task: OtaTask, line: str, db: Session):
    task.log = (task.log or "") + f"\n[{datetime.now().strftime('%H:%M:%S')}] {line}"
    db.commit()


def _read_current_version(r: Robot) -> str:
    """优先 cmd=6; 失败则 cat version 文件。"""
    try:
        code, msg, d = robot_api.call(r.ip, r.api_port, r.robot_id, 6)
        if code == 0:
            return d.get("application", "") or ""
    except Exception:
        pass
    try:
        out, _, _ = ssh_client.run(r.ip, f"cat {r.version_file} 2>/dev/null",
                                   r.ssh_port, r.ssh_user, r.ssh_pass, timeout=10)
        # version 文件可能是多行, 取含 application 或版本号的
        for line in out.splitlines():
            low = line.lower()
            if "application" in low or re_ver_match(line):
                return line.split(":", 1)[-1].strip().strip('"') or line.strip()
        return out.strip().splitlines()[0] if out.strip() else ""
    except Exception:
        return ""


import re as _re
def re_ver_match(s: str) -> bool:
    return bool(_re.search(r"\d+\.\d+\.\d+", s))


def run_task_safe(task_id: int):
    """带异常兜底的入口。"""
    try:
        run_task(task_id)
    except Exception as e:  # noqa: BLE001
        db = SessionLocal()
        try:
            t = db.query(OtaTask).filter(OtaTask.id == task_id).first()
            if t:
                t.status = "failed"
                t.log = (t.log or "") + f"\n[error] {e}"
                t.finished_at = datetime.utcnow()
                db.commit()
        finally:
            db.close()


def run_task(task_id: int):
    db = SessionLocal()
    try:
        t = db.query(OtaTask).filter(OtaTask.id == task_id).first()
        if not t:
            return
        r = db.query(Robot).filter(Robot.id == t.robot_pk).first()
        pkg = db.query(OtaPackage).filter(OtaPackage.id == t.package_id).first() if t.package_id else None
        if not r or not pkg:
            t.status = "failed"
            t.log = (t.log or "") + "\n机器人或安装包不存在"
            db.commit()
            return

        # 同机串行
        lk = _machine_lock(r.id)
        if not lk.acquire(blocking=False):
            _append(t, "该机器人已有升级任务在执行, 等待重试", db)
            time.sleep(5)
            # 重新排队: 由前端 retry 或自动策略再触发
            t.status = "pending"
            db.commit()
            return

        try:
            t.status = "running"
            t.started_at = datetime.utcnow()
            _append(t, f"开始升级 {r.name}({r.ip}) 目标版本={t.to_version} 强制={t.force}", db)

            # 1. 连通性
            ok, msg = ssh_client.check(r.ip, r.ssh_port, r.ssh_user, r.ssh_pass)
            if not ok:
                raise RuntimeError(f"SSH 不通: {msg}")
            _append(t, f"SSH OK: {msg}", db)

            # 2. 当前版本
            cur = _read_current_version(r)
            t.from_version = cur
            _append(t, f"当前版本: {cur or '(未知)'}", db)
            if not t.force and t.to_version and cur and cur == t.to_version:
                t.status = "skipped"
                _append(t, "版本相同且非强制, 跳过", db)
                t.finished_at = datetime.utcnow()
                db.commit()
                return

            # 3. 找安装包物理文件
            from ..config import PKG_DIR
            files = list(PKG_DIR.glob(f"*_{pkg.filename}"))
            if not files:
                raise RuntimeError("安装包文件丢失")
            local_pkg = str(files[0])

            # 4. SCP 上传
            remote_pkg = f"{r.install_dir.rstrip('/')}/{pkg.filename}"
            _append(t, f"上传 {pkg.filename} ({os.path.getsize(local_pkg)//1024//1024}MB) -> {remote_pkg}", db)
            ssh_client.upload_file(r.ip, local_pkg, remote_pkg,
                                   r.ssh_port, r.ssh_user, r.ssh_pass)
            _append(t, "上传完成", db)

            # 5. 执行 install.sh(自带备份)。注意 install.sh 期望当前目录有 package.tar.gz?
            #    实测它直接解压变量 PACKAGE_NAME=package.tar.gz, 而现场安装包是 zip。
            #    所以这里: 解压 zip 到临时目录, 检查是否有 install.sh / package.tar.gz,
            #    适配两种现场形态。
            script = _build_install_script(r, remote_pkg)
            _append(t, "执行安装脚本(含备份)...", db)
            out, err, rc = ssh_client.run_as_script(
                r.ip, script, r.ssh_port, r.ssh_user, r.ssh_pass, timeout=600)
            _append(t, f"install rc={rc}\nstdout(尾):\n{out[-1500:]}\nstderr(尾):\n{err[-800:]}", db)
            if rc != 0:
                raise RuntimeError(f"安装脚本失败 rc={rc}")

            # 6. 重启上位机程序
            _append(t, "重启上位机程序...", db)
            rs = _build_restart_script(r)
            out2, err2, rc2 = ssh_client.run_as_script(
                r.ip, rs, r.ssh_port, r.ssh_user, r.ssh_pass, timeout=60)
            _append(t, f"restart rc={rc2} out={out2.strip()[-300:]}", db)

            # 7. 等待并校验新版本
            _append(t, "等待程序就绪, 校验版本...", db)
            new_ver = ""
            for i in range(8):
                time.sleep(8)
                new_ver = _read_current_version(r)
                if new_ver:
                    break
            _append(t, f"升级后版本: {new_ver or '(未读到)'}", db)

            # 8. 结果判定
            if t.to_version and new_ver:
                success = (new_ver == t.to_version)
            else:
                success = new_ver != "" and (not cur or new_ver != cur)
            t.status = "success" if success else "failed"
            if success:
                _append(t, "✅ 升级成功", db)
            else:
                _append(t, "⚠️ 版本校验未通过, 请人工确认(可用 robot_backup 回滚)", db)
            t.finished_at = datetime.utcnow()
            db.commit()

        finally:
            try:
                lk.release()
            except Exception:
                pass
    finally:
        db.close()


def _build_install_script(r: Robot, remote_pkg: str) -> str:
    """构建安装脚本。

    现场 install.sh 期望: 在 install_dir 下解压 package.tar.gz(变量名),
    但安装包实际是 zip。本脚本做适配:
      - 进 install_dir
      - 解压 zip -> 临时目录
      - 若临时目录里有 package.tar.gz -> 解压再跑其中的 install.sh
      - 若临时目录里有 install.sh -> 直接跑(它内部解压 package.tar.gz)
      - 若 zip 里直接是 bin/lib/scripts 结构, 且有顶层 install.sh -> 跑它
    """
    return f"""set -e
cd {r.install_dir}
WORK=$(mktemp -d)
echo "解压 {remote_pkg} -> $WORK"
if command -v unzip >/dev/null 2>&1; then
  unzip -o -q {remote_pkg} -d "$WORK" || tar -zxf {remote_pkg} -C "$WORK"
else
  tar -zxf {remote_pkg} -C "$WORK"
fi

# 定位 install.sh
INSTALL_SH=$(find "$WORK" -maxdepth 3 -name install.sh -type f | head -1)
if [ -n "$INSTALL_SH" ]; then
  DIR=$(dirname "$INSTALL_SH")
  echo "进入 $DIR 执行 install.sh"
  cd "$DIR"
  chmod +x install.sh
  ./install.sh
else
  echo "未发现 install.sh, 假定 zip 已含 package 结构"
  # 尝试直接执行已存在的 install.sh(in install_dir)
  if [ -x ./install.sh ]; then ./install.sh; fi
fi
rm -rf "$WORK"
echo "INSTALL_DONE"
"""


def _build_restart_script(r: Robot) -> str:
    return f"""cd {r.install_dir}/robot 2>/dev/null || cd {r.install_dir}
if [ -x ./stop.sh ]; then ./stop.sh 2>/dev/null || true; fi
pkill -9 -f '/bin/robot' 2>/dev/null || true
sleep 2
if [ -x ./start.sh ]; then
  nohup ./start.sh >> /tmp/fms_ota_restart.log 2>&1 &
  echo RESTART_OK
else
  echo NO_START_SH
fi
"""
