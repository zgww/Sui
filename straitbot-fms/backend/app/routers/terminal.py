"""终端调试: WebSocket + SSH PTY 持久会话, 真正的交互式终端。engineer 专用。"""
import asyncio
import json
import logging
import time
import socket
from fastapi import APIRouter, Depends, HTTPException, WebSocket, WebSocketDisconnect
from pydantic import BaseModel, Field
from sqlalchemy.orm import Session
import paramiko

from ..database import get_db
from ..models import Robot
from ..auth import get_current_user
from ..config import settings

logger = logging.getLogger(__name__)
router = APIRouter(prefix="/api/terminal", tags=["terminal"])


# ── REST: 单次命令执行 (保留兼容) ──────────────────────────

class ExecIn(BaseModel):
    cmd: str = Field(..., min_length=1, max_length=4096)
    timeout: int = Field(30, ge=5, le=120)


class ExecOut(BaseModel):
    ok: bool
    stdout: str = ""
    stderr: str = ""
    rc: int = -1
    elapsed_ms: float = 0
    msg: str = ""


def _robot(rid: int, db: Session) -> Robot:
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    return r


@router.post("/{rid}/exec", response_model=ExecOut)
def exec_cmd(rid: int, body: ExecIn, db: Session = Depends(get_db),
             _=Depends(get_current_user)):
    """单次执行 shell 命令。"""
    from ..services import ssh_client
    r = _robot(rid, db)
    t0 = time.perf_counter()
    try:
        out, err, rc_val = ssh_client.run(
            r.ip, body.cmd,
            port=r.ssh_port, user=r.ssh_user, pwd=r.ssh_pass,
            timeout=body.timeout,
        )
        elapsed = (time.perf_counter() - t0) * 1000
        return ExecOut(
            ok=(rc_val == 0), stdout=out, stderr=err, rc=rc_val,
            elapsed_ms=round(elapsed, 1),
            msg="执行成功" if rc_val == 0 else f"返回码 {rc_val}",
        )
    except Exception as e:
        elapsed = (time.perf_counter() - t0) * 1000
        logger.warning("[terminal/exec] 失败 rid=%d cmd=%.60s err=%s 耗时=%.0fms",
                       rid, body.cmd, e, elapsed)
        return ExecOut(ok=False, stderr=str(e), elapsed_ms=round(elapsed, 1), msg=str(e))


# ── WebSocket: 交互式 PTY 终端 ──────────────────────────

async def _ssh_to_ws(ws: WebSocket, ssh_client_obj: paramiko.SSHClient, chan: paramiko.Channel):
    """双向转发: WebSocket ↔ SSH PTY channel。

    SSH 通道结束(断开/EOF)时必须主动关闭 WebSocket 并取消读协程,
    否则前端表现为"终端卡死不响应"。
    """
    loop = asyncio.get_event_loop()

    async def ssh_reader():
        """从 SSH channel 读取输出 → 发给 WebSocket。"""
        while not chan.closed:
            try:
                if chan.recv_ready():
                    data = await loop.run_in_executor(None, lambda: chan.recv(4096))
                    if data:
                        await ws.send_bytes(data)
                    else:
                        break
                else:
                    # 没有数据时短暂等待, 避免 CPU 空转
                    await asyncio.sleep(0.02)
            except Exception:
                break
        logger.info("[terminal/ws] SSH 输出通道结束")

    async def ws_reader():
        """从 WebSocket 读取用户输入 → 发给 SSH stdin。

        前端协议: 按键原文(text, 逐字符) / resize JSON({"type":"resize",...})。
        ⚠ 单字符数字("2")也是合法 JSON 字面量, 解析结果是 int 而非 dict —
        必须 isinstance 判 dict, 否则误当控制消息崩溃导致整个会话被关闭。
        """
        async def _send_stdin(payload: bytes) -> bool:
            # 非阻塞 channel: 发送缓冲满抛 socket.timeout, 重试等待而非退出
            while payload:
                try:
                    n = chan.send(payload)
                    payload = payload[n:]
                except socket.timeout:
                    await asyncio.sleep(0.02)
                except Exception:
                    return False
            return True

        try:
            while not chan.closed:
                data = await ws.receive()
                if data.get("type") == "websocket.disconnect":
                    break
                text = data.get("text")
                if text is not None:
                    handled = False
                    s = text.strip()
                    # 仅 {..} 形态且解析为 dict 且带 type=resize 才当控制消息
                    if s.startswith("{") and s.endswith("}"):
                        try:
                            msg = json.loads(s)
                            if isinstance(msg, dict) and msg.get("type") == "resize":
                                try:
                                    chan.resize_pty(width=int(msg.get("cols", 80)),
                                                    height=int(msg.get("rows", 24)))
                                except Exception:
                                    pass
                                handled = True
                        except (json.JSONDecodeError, ValueError):
                            pass
                    if not handled:
                        if not await _send_stdin(text.encode("utf-8")):
                            break
                        continue
                b = data.get("bytes")
                if b:
                    if not await _send_stdin(bytes(b)):
                        break
        except (WebSocketDisconnect, RuntimeError):
            pass
        except Exception as e:
            logger.info("[terminal/ws] ws_reader 退出: %s", e)

    reader_task = asyncio.create_task(ssh_reader())
    writer_task = asyncio.create_task(ws_reader())

    try:
        # 任一方向结束即收尾: reader 结束(SSH断) → 取消 writer 并关 ws;
        # writer 结束(页面关闭) → 取消 reader
        done, pending = await asyncio.wait(
            {reader_task, writer_task}, return_when=asyncio.FIRST_COMPLETED)
        for t in (reader_task, writer_task):
            if not t.done():
                t.cancel()
        # 主动关闭 WebSocket, 让前端立即感知断开而不是一直等
        try:
            await ws.close()
        except Exception:
            pass
    except Exception as e:
        logger.warning("[terminal/ws] 转发异常: %s", e)
    finally:
        for t in (reader_task, writer_task):
            if not t.done():
                t.cancel()
        try:
            chan.close()
        except Exception:
            pass
        try:
            ssh_client_obj.close()
        except Exception:
            pass
        logger.info("[terminal/ws] 会话清理完成")


@router.websocket("/{rid}/ws")
async def terminal_ws(websocket: WebSocket, rid: int):
    """WebSocket 终端 — 建立 SSH PTY 到机器人工控机。"""
    # 认证: 从 query string 读取 token
    token = websocket.query_params.get("token", "")
    if not token:
        await websocket.close(code=4001, reason="缺少 token")
        return

    from ..auth import decode_token
    try:
        payload = decode_token(token)
        role = payload.get("role", "")
        if role != "engineer":
            await websocket.close(code=4003, reason="仅 engineer 可访问")
            return
    except Exception:
        await websocket.close(code=4001, reason="token 无效")
        return

    # 查机器人
    from ..database import SessionLocal
    db = SessionLocal()
    try:
        r = db.query(Robot).filter(Robot.id == rid).first()
        if not r:
            await websocket.close(code=4004, reason="机器人不存在")
            return
    finally:
        db.close()

    # 建立 SSH 连接 + PTY
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    try:
        ssh.connect(
            r.ip, port=r.ssh_port, username=r.ssh_user, password=r.ssh_pass,
            timeout=settings.ssh_connect_timeout,
            banner_timeout=settings.ssh_connect_timeout,
            auth_timeout=settings.ssh_connect_timeout,
            look_for_keys=False, allow_agent=False,
        )
    except Exception as e:
        try:
            ssh.close()
        except Exception:
            pass
        logger.warning("[terminal/ws] SSH 连接失败 rid=%d ip=%s err=%s", rid, r.ip, e)
        await websocket.accept()
        await websocket.send_text(f"\r\n\x1b[31mSSH 连接失败: {e}\x1b[0m\r\n")
        await websocket.close()
        return

    # 打开 PTY channel
    try:
        chan = ssh.invoke_shell(term="xterm-256color", width=120, height=40)
        chan.settimeout(0.0)  # 非阻塞
    except Exception as e:
        await websocket.accept()
        await websocket.send_text(f"\r\n\x1b[31m无法打开 PTY: {e}\x1b[0m\r\n")
        await websocket.close()
        ssh.close()
        return

    await websocket.accept()
    logger.info("[terminal/ws] 会话建立 rid=%d ip=%s:%s", rid, r.ip, r.ssh_port)

    try:
        await _ssh_to_ws(websocket, ssh, chan)
    except Exception as e:
        logger.warning("[terminal/ws] 会话异常: %s", e)
    finally:
        try:
            chan.close()
        except Exception:
            pass
        try:
            ssh.close()
        except Exception:
            pass
        logger.info("[terminal/ws] 会话关闭 rid=%d", rid)
