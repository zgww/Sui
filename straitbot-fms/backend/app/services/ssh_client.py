"""SSH/SFTP 封装(paramiko)。提供: 连通性、执行命令、SCP 上传/下载、列目录。

每个调用自建短连接, 避免长连接状态污染(轮询场景下足够轻量)。
"""
from __future__ import annotations
import socket
import time as _time
from dataclasses import dataclass
from typing import List, Optional, Tuple
import paramiko

from ..config import settings


class SSHError(Exception):
    pass


@dataclass
class RemoteFile:
    name: str
    size: int
    modify_time: str
    is_dir: bool


def _connect(ip: str, port: int, user: str, pwd: str) -> paramiko.SSHClient:
    client = paramiko.SSHClient()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    try:
        client.connect(
            ip, port=port, username=user, password=pwd,
            timeout=settings.ssh_connect_timeout,
            banner_timeout=settings.ssh_connect_timeout,
            auth_timeout=settings.ssh_connect_timeout,
            look_for_keys=False, allow_agent=False,
        )
    except (paramiko.AuthenticationException, paramiko.SSHException, socket.timeout, OSError) as e:
        # 连接失败时必须关闭半开的 transport, 否则其后台线程与 socket 会泄漏
        try:
            client.close()
        except Exception:
            pass
        raise SSHError(f"SSH 连接 {ip}:{port} 失败: {e}") from e
    return client


def check(ip: str, port: int = 22, user: str = "nav", pwd: str = "nav2022") -> Tuple[bool, str]:
    """连通性 + 认证测试。返回 (ok, message)。"""
    c = None
    try:
        c = _connect(ip, port, user, pwd)
        _, stdout, _ = c.exec_command("echo ok; uname -m", timeout=8)
        out = stdout.read().decode("utf-8", "replace").strip()
        return True, out or "ok"
    except SSHError as e:
        return False, str(e)
    except Exception as e:  # noqa: BLE001
        return False, f"未知错误: {e}"
    finally:
        # 任何路径都必须关闭连接, 否则 paramiko transport 线程泄漏
        if c is not None:
            try:
                c.close()
            except Exception:
                pass


def run(ip: str, cmd: str, port=22, user="nav", pwd="nav2022", timeout=None,
        max_output: int = 2 * 1024 * 1024) -> Tuple[str, str, int]:
    """执行命令, 返回 (stdout, stderr, rc)。max_output 限制输出大小(默认2MB)。

    ⚠ stdout 与 stderr 必须并发排空: 只读 stdout 时, 远端往 stderr 写满流控窗口
    (约64KB)后会阻塞远端进程, 表现为"输出到一定长度后整体卡死"。
    另设墙钟兜底超时, 防远端命令挂起导致调用方无限等待。
    """
    c = _connect(ip, port, user, pwd)
    try:
        t = timeout or settings.ssh_cmd_timeout
        _, stdout, _ = c.exec_command(cmd, timeout=t)
        chan = stdout.channel
        deadline = _time.monotonic() + t + 5.0  # 比命令超时多 5s 兜底

        out_chunks: list[bytes] = []
        err_chunks: list[bytes] = []
        out_total = 0
        err_total = 0
        timed_out = False

        while True:
            got = 0
            # 排空 stdout
            while chan.recv_ready():
                chunk = chan.recv(65536)
                if not chunk:
                    break
                got += len(chunk)
                out_total += len(chunk)
                if out_total <= max_output:
                    out_chunks.append(chunk)
            # 排空 stderr (关键: 不读会写满远端流控窗口导致死锁)
            while chan.recv_stderr_ready():
                echunk = chan.recv_stderr(65536)
                if not echunk:
                    break
                got += len(echunk)
                err_total += len(echunk)
                if err_total <= max_output:
                    err_chunks.append(echunk)

            # 进程退出且两路数据都读完 → 结束
            if (chan.exit_status_ready() or chan.closed) \
                    and not chan.recv_ready() and not chan.recv_stderr_ready():
                break

            # 墙钟兜底: 远端挂起时强制中断, 不让调用方无限等
            if _time.monotonic() > deadline:
                timed_out = True
                try:
                    chan.close()
                except Exception:
                    pass
                break

            if got == 0:
                _time.sleep(0.01)

        out = b"".join(out_chunks).decode("utf-8", "replace")
        if out_total > max_output:
            out += f"\n\n[输出已截断, 超过 {max_output // 1024 // 1024}MB]"
        err = b"".join(err_chunks).decode("utf-8", "replace")
        if err_total > max_output:
            err += f"\n\n[stderr已截断, 超过 {max_output // 1024 // 1024}MB]"
        if timed_out:
            err += f"\n[超时 {t}s 强制中断]"
        rc = chan.recv_exit_status() if chan.exit_status_ready() else -1
        return out, err, rc
    finally:
        c.close()


def run_as_script(ip: str, script: str, port=22, user="nav", pwd="nav2022", timeout=None) -> Tuple[str, str, int]:
    """把脚本整体通过 stdin 喂给 bash 执行, 避免 shell 转义坑。"""
    c = _connect(ip, port, user, pwd)
    try:
        t = timeout or settings.ssh_cmd_timeout
        chan = c.get_transport().open_session()
        chan.settimeout(t)
        chan.exec_command("bash -s")
        chan.sendall(script.encode("utf-8"))
        # 发送 EOF, 让远端 bash 知道脚本结束
        try:
            chan.shutdown_write()
        except Exception:
            pass
        out = b""
        while True:
            try:
                data = chan.recv(65536)
            except socket.timeout:
                break
            if not data:
                break
            out += data
        err = b""
        while chan.recv_stderr_ready():
            err += chan.recv_stderr(65536)
        rc = chan.recv_exit_status()
        return out.decode("utf-8", "replace"), err.decode("utf-8", "replace"), rc
    finally:
        c.close()


def upload_file(ip: str, local_path: str, remote_path: str,
                port=22, user="nav", pwd: str = "nav2022") -> None:
    c = _connect(ip, port, user, pwd)
    try:
        sftp = c.open_sftp()
        try:
            sftp.put(local_path, remote_path)
        finally:
            sftp.close()
    finally:
        c.close()


def download_file(ip: str, remote_path: str, local_path: str,
                  port=22, user="nav", pwd: str = "nav2022") -> None:
    c = _connect(ip, port, user, pwd)
    try:
        sftp = c.open_sftp()
        try:
            sftp.get(remote_path, local_path)
        finally:
            sftp.close()
    finally:
        c.close()


def list_dir(ip: str, remote_dir: str, port=22, user="nav", pwd: str = "nav2022") -> List[RemoteFile]:
    c = _connect(ip, port, user, pwd)
    try:
        sftp = c.open_sftp()
        try:
            entries = []
            for name in sftp.listdir(remote_dir):
                full = remote_dir.rstrip("/") + "/" + name
                try:
                    st = sftp.stat(full)
                    entries.append(RemoteFile(
                        name=name, size=int(st.st_size),
                        modify_time=_time.strftime("%Y-%m-%d %H:%M:%S", _time.localtime(st.st_mtime)),
                        is_dir=False if (st.st_mode & 0o170000) != 0o040000 else True,
                    ))
                except IOError:
                    continue
            return entries
        finally:
            sftp.close()
    finally:
        c.close()
