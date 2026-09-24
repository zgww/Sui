"""视频流模块: ZLMediaKit 配置 + WebRTC 信令代理 + 流状态。

设计:
  - FMS 不自建流媒体, 仅做"配置 + 代理"。
  - 流媒体服务(ZLMediaKit)地址/secret 存在 robots 表, 前端只跟 FMS 交互。
  - WebRTC 信令: 前端 RTCPeerConnection 生成 SDP offer → POST 到本路由
    → 后端转发给 ZLM 的 /index/api/webrtc → 返回 SDP answer → 前端 setRemoteDescription。
  - 兼容 ZLM WHEP(WHIP-like): body 直接是 SDP 文本, 响应也是 SDP 文本。
"""
from fastapi import APIRouter, Depends, HTTPException, Request, Response
from pydantic import BaseModel
from typing import Optional
from sqlalchemy.orm import Session
import httpx

from ..database import get_db
from ..models import Robot
from ..auth import get_current_user

router = APIRouter(prefix="/api/video", tags=["video"])


def _robot(rid: int, db: Session) -> Robot:
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    return r


def _build_hk_stream(ip: str, ch: int, ssm: int, rtsp_port="undefined") -> str:
    """按海康 ffmpeg 推流命名规律生成流名(参考 6.54 现网实测)。
    规律: channel-{ch}-subStream-{ssm}-hk-video-{ip第3段}{ip第4段}-rtspPort{rtspPort}
    例: ip=192.168.200.226 ch=1 ssm=1 → channel-1-subStream-1-hk-video-200226-rtspPortundefined
    """
    parts = (ip or "").split(".")
    p3 = parts[2] if len(parts) > 2 else "0"
    p4 = parts[3] if len(parts) > 3 else "0"
    return f"channel-{ch}-subStream-{ssm}-hk-video-{p3}{p4}-rtspPort{rtsp_port}"


def _resolve_stream(r: Robot, stream_key: str) -> str:
    """解析流标识。支持占位符(取机器人 IP):
      {ip_last}  - 末段, 如 226
      {ip_last2} - 后两段去点(匹配海康 ffmpeg 推流命名 192.168.200.226→200226), 如 200226
      {ip_last3} - 后三段去点, 如 168200226
      {ip_strip} - 全段去点, 如 192168200226
    """
    raw = stream_key or r.video_visible_stream or ""
    if r.ip and "{" in raw:
        parts = r.ip.split(".")
        ip_strip = "".join(parts)
        ip_last3 = "".join(parts[1:]) if len(parts) >= 3 else ip_strip
        ip_last2 = "".join(parts[2:]) if len(parts) >= 4 else ip_last3
        ip_last = parts[-1] if parts else "0"
        raw = raw.replace("{ip_strip}", ip_strip) \
                 .replace("{ip_last3}", ip_last3) \
                 .replace("{ip_last2}", ip_last2) \
                 .replace("{ip_last}", ip_last)
    if r.video_use_robot_ip and not raw and r.ip:
        # 未配置流名时, 默认按海康命名规律(后两段去点)
        parts = r.ip.split(".")
        raw = f"live/channel-1-subStream-1-hk-video-{''.join(parts[2:])}-rtspPortundefined"
    return raw.strip()


def _split_app_stream(stream: str) -> tuple[str, str]:
    """live/robot-109 -> ("live", "robot-109"); 默认 app=live。"""
    if not stream:
        return "live", ""
    if "/" in stream:
        app, _, name = stream.partition("/")
        return app or "live", name
    return "live", stream


def _server_url(r: Robot) -> str:
    return (r.video_server or "").rstrip("/")


# ========== 配置读取 ==========
@router.get("/{rid}/config")
def get_video_config(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """返回视频配置 + 解析后的流地址(供前端预览)。"""
    r = _robot(rid, db)
    srv = _server_url(r)
    # 可见光/红外流名: 优先用配置(带占位符解析), 否则按海康规律 ch/ssm + IP 自动拼
    vis = _resolve_stream(r, r.video_visible_stream) or _build_hk_stream(r.ip, 1, 1)
    thm = _resolve_stream(r, r.video_thermal_stream) or _build_hk_stream(r.ip, 2, 2)
    va, vs = _split_app_stream(vis)
    ta, ts = _split_app_stream(thm)
    return {
        "ok": True,
        "configured": bool(srv),
        "video_server": srv,
        "protocol": r.video_protocol or "webrtc",
        "visible": {"app": va, "stream": vs, "ch": 1, "ssm": 1},
        "thermal": {"app": ta, "stream": ts, "ch": 2, "ssm": 1},
        "play_urls": _play_urls(srv, r.video_protocol or "webrtc", va, vs, ta, ts),
    }


def _play_urls(srv: str, protocol: str, va: str, vs: str, ta: str, ts: str) -> dict:
    """预生成各协议播放地址。前端 WebRTC 走信令接口, 这里仅给 flv/hls 直连用。"""
    out = {"visible": {}, "thermal": {}}
    if not srv:
        return out
    for label, app, stream in (("visible", va, vs), ("thermal", ta, ts)):
        if not stream:
            continue
        base = f"{srv}/{app}/{stream}"
        out[label] = {
            "flv": f"{base}.flv",
            "hls": f"{srv}/{app}/{stream}/hls.m3u8",
        }
    return out


# ========== WebRTC 信令代理 ==========
@router.post("/{rid}/webrtc")
async def webrtc_signal(
    rid: int,
    request: Request,
    channel: str = "visible",   # visible | thermal
    ch: Optional[int] = None,   # 海康 channel 号(优先用); 可见光默认1 红外默认2
    ssm: Optional[int] = None,  # 海康 subStream 号(优先用); 可见光默认1 红外默认2
    db: Session = Depends(get_db),
    _=Depends(get_current_user),
):
    """WebRTC SDP 信令代理。

    流名两种来源(优先级递减):
      1. ch/ssm 参数 + 机器人 IP → 按海康规律自动拼(最简单, 推荐)
      2. video_visible_stream/video_thermal_stream 配置(完整流名或带占位符)

    ZLM WebRTC 接口: /index/api/webrtc?app=live&stream=xxx&type=play&schema=rtmp
    """
    r = _robot(rid, db)
    srv = _server_url(r)
    if not srv:
        raise HTTPException(400, "未配置视频服务器地址")

    # 默认 ch/ssm: 可见光 1/1, 红外 2/1(ssm 都默认 1, 对齐不同部署的 ffmpeg 推流规律)
    if ch is None:
        ch = 2 if channel == "thermal" else 1
    if ssm is None:
        ssm = 1

    # 优先用 ch/ssm + IP 自动拼流名; 否则用配置的流标识
    if r.ip:
        name = _build_hk_stream(r.ip, ch, ssm)
        app = "live"
    else:
        stream_key = r.video_thermal_stream if channel == "thermal" else r.video_visible_stream
        stream = _resolve_stream(r, stream_key)
        app, name = _split_app_stream(stream)
    if not name:
        raise HTTPException(400, "无法确定视频流标识(需机器人 IP 或配置流名)")

    sdp_offer = (await request.body()).decode("utf-8", errors="ignore")
    if not sdp_offer or "v=0" not in sdp_offer:
        raise HTTPException(400, "无效的 SDP offer")

    # schema=rtmp 是关键(参考现网 webrtc 演示页)
    params = {"app": app, "stream": name, "type": "play", "schema": "rtmp"}
    if r.video_secret:
        params["secret"] = r.video_secret
    zlm_url = f"{srv}/index/api/webrtc"

    async with httpx.AsyncClient(timeout=8.0) as cli:
        try:
            # Content-Type 用 text/plain(对齐现网 webrtc 演示页)
            resp = await cli.post(zlm_url, params=params, content=sdp_offer,
                                  headers={"Content-Type": "text/plain;charset=utf-8"})
        except Exception as e:  # noqa: BLE001
            raise HTTPException(502, f"ZLMediaKit 不可达: {e}")

    # ZLM 返回 JSON: 成功 {code:0, sdp:"v=0...", type:"answer"}, 失败 {code:-400, msg:"..."}
    try:
        obj = resp.json()
    except Exception:  # noqa: BLE001
        # 极少数版本返回裸 SDP 文本
        if resp.text.lstrip().startswith("v=0"):
            return Response(content=resp.content, media_type="application/sdp")
        raise HTTPException(502, f"ZLM 返回非 JSON: {resp.text[:200]}")

    if obj.get("code") != 0:
        raise HTTPException(502, f"ZLM 错误 code={obj.get('code')} msg={obj.get('msg')}")
    sdp_answer = obj.get("sdp") or obj.get("data", {}).get("sdp") or ""
    if not sdp_answer:
        raise HTTPException(502, f"ZLM code=0 但无 sdp 字段, keys={list(obj.keys())}")
    return Response(content=sdp_answer.encode("utf-8"), media_type="application/sdp")


# ========== 流列表 / 状态(对接 ZLM API) ==========
@router.get("/{rid}/streams")
async def list_streams(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """查询 ZLMediaKit 当前所有在线流(getMediaList)。用于配置页诊断。"""
    r = _robot(rid, db)
    srv = _server_url(r)
    if not srv:
        return {"ok": False, "msg": "未配置视频服务器", "data": []}
    params = {"secret": r.video_secret} if r.video_secret else {}
    async with httpx.AsyncClient(timeout=5.0) as cli:
        try:
            resp = await cli.get(f"{srv}/index/api/getMediaList", params=params)
            obj = resp.json()
        except Exception as e:  # noqa: BLE001
            return {"ok": False, "msg": f"ZLM 不可达: {e}", "data": []}
    if obj.get("code") != 0:
        return {"ok": False, "msg": obj.get("msg", "未知错误"), "data": []}
    return {"ok": True, "data": obj.get("data", [])}


@router.get("/{rid}/status")
async def stream_status(
    rid: int,
    channel: str = "visible",
    ch: Optional[int] = None,
    ssm: Optional[int] = None,
    db: Session = Depends(get_db),
    _=Depends(get_current_user),
):
    """查询单路流是否在线(isMediaOnline)。流名按 ch/ssm + IP 自动拼。"""
    r = _robot(rid, db)
    srv = _server_url(r)
    if not srv:
        return {"ok": False, "online": False, "msg": "未配置"}
    if ch is None:
        ch = 2 if channel == "thermal" else 1
    if ssm is None:
        ssm = 1
    if r.ip:
        name = _build_hk_stream(r.ip, ch, ssm)
    else:
        return {"ok": False, "online": False, "msg": "无机器人 IP"}
    params = {"vhost": "__defaultVhost__", "app": "live", "stream": name, "schema": "rtmp"}
    if r.video_secret:
        params["secret"] = r.video_secret
    async with httpx.AsyncClient(timeout=5.0) as cli:
        try:
            resp = await cli.get(f"{srv}/index/api/isMediaOnline", params=params)
            obj = resp.json()
        except Exception as e:  # noqa: BLE001
            return {"ok": False, "online": False, "msg": f"ZLM 不可达: {e}"}
    online = bool(obj.get("online"))
    return {"ok": obj.get("code") == 0, "online": online, "msg": obj.get("msg", "")}
