"""AI 日志分析路由。

- GET  /api/ai/providers        服务商预设
- GET  /api/ai/settings         当前配置(api_key 脱敏)
- PUT  /api/ai/settings         更新配置(engineer)
- POST /api/ai/analyze/{kind}/{log_id}  分析指定已归档日志(流式 SSE)
"""
import os
import json
from fastapi import APIRouter, Depends, HTTPException, Request
from fastapi.responses import StreamingResponse
from pydantic import BaseModel
from typing import Optional
from sqlalchemy.orm import Session

from ..database import get_db
from ..models import UploadedLog, FetchedLog
from ..schemas import Ok
from ..auth import engineer_only, get_current_user
from ..services import ai_analyzer
from ..config import DATA_DIR

router = APIRouter(prefix="/api/ai", tags=["ai"])


@router.get("/providers")
def providers(_=Depends(get_current_user)):
    return [{"key": k, "label": v[0], "base_url": v[1], "model": v[2],
             "protocol": v[3],
             "models": ai_analyzer.MODELS_BY_PROVIDER.get(k, [])}
            for k, v in ai_analyzer.PROVIDERS.items()]


@router.get("/settings")
def get_settings(db: Session = Depends(get_db), _=Depends(get_current_user)):
    return ai_analyzer.get_all_settings(db)


class AiSettingsIn(BaseModel):
    provider: Optional[str] = None
    base_url: Optional[str] = None
    api_key: Optional[str] = None
    model: Optional[str] = None
    enabled: Optional[bool] = None
    extra_instructions: Optional[str] = None


@router.put("/settings")
def put_settings(body: AiSettingsIn, db: Session = Depends(get_db), user=Depends(engineer_only)):
    cfg = ai_analyzer.update_settings(db, body.model_dump(exclude_none=False))
    return {"ok": True, "msg": "已保存", "settings": cfg}


def _read_log(db: Session, kind: str, log_id: int) -> str:
    """读取已归档日志全文。kind: uploaded|fetched"""
    if kind == "uploaded":
        rec = db.query(UploadedLog).filter(UploadedLog.id == log_id).first()
    elif kind == "fetched":
        rec = db.query(FetchedLog).filter(FetchedLog.id == log_id).first()
    else:
        raise HTTPException(400, "kind 必须是 uploaded|fetched")
    if not rec:
        raise HTTPException(404, "日志不存在")
    path = rec.stored_path
    if not path or not os.path.exists(path):
        raise HTTPException(404, "日志文件丢失")
    try:
        with open(path, "rb") as f:
            raw = f.read()
        # 尝试 utf-8, 失败回退 gbk(部分 Windows 生成日志)
        try:
            return raw.decode("utf-8")
        except UnicodeDecodeError:
            return raw.decode("gbk", errors="replace")
    except Exception as e:
        raise HTTPException(500, f"读取失败: {e}")


class ChatAttachment(BaseModel):
    name: str = ""
    content: str = ""   # 文本内容(txt/log/md) 或 base64(图片)


class ChatIn(BaseModel):
    history: list = []
    question: str = ""
    robot_name: str = ""    # 可选, 帮助 AI 理解上下文
    attachments: list = []  # [ChatAttachment]


@router.post("/analyze/{kind}/{log_id}")
def analyze(kind: str, log_id: int,
            body: ChatIn,
            db: Session = Depends(get_db), user=Depends(get_current_user)):
    """流式分析/对话。返回 text/event-stream (SSE)。

    多轮对话:
      - 首轮: body.history 为空, AI 读完整日志做默认分析
      - 后续: body.history 带上之前的对话, body.question 是本次追问
    """
    cfg = ai_analyzer.get_all_settings(db)
    if not cfg["enabled"]:
        raise HTTPException(400, "AI 分析未启用, 请到「系统设置」开启并配置 API Key")
    log_text = _read_log(db, kind, log_id)
    extra = cfg.get("extra_instructions", "")

    def gen():
        try:
            for piece in ai_analyzer.analyze_stream(
                    db, log_text, extra,
                    history=body.history, question=body.question):
                yield "data: " + json.dumps({"text": piece}, ensure_ascii=False) + "\n\n"
            yield "data: [DONE]\n\n"
        except Exception as e:  # noqa: BLE001
            yield "data: " + json.dumps({"error": str(e)}, ensure_ascii=False) + "\n\n"

    return StreamingResponse(gen(), media_type="text/event-stream")


@router.post("/chat")
def chat_ai(body: ChatIn, db: Session = Depends(get_db), user=Depends(get_current_user)):
    """通用 AI 对话(不绑定日志文件)。支持附件和机器人上下文。

    流式返回 SSE, 与 /analyze 同样格式。
    """
    cfg = ai_analyzer.get_all_settings(db)
    if not cfg["enabled"]:
        raise HTTPException(400, "AI 分析未启用")

    ext = cfg.get("extra_instructions", "")
    # 读取知识库
    _ensure_prompts_file()
    knowledge = ""
    try:
        data = json.loads(PROMPTS_FILE.read_text(encoding="utf-8"))
        knowledge = (data.get("knowledge", "") if isinstance(data, dict) else "")
    except Exception:
        pass
    # 构造上下文
    context = ""
    if body.robot_name:
        context += f"【话题机器人】{body.robot_name}\n"
    for att in body.attachments:
        context += f"\n【附件: {att.name}】\n{att.content[:10000]}\n"
    if context:
        context += "\n---\n"

    def gen():
        try:
            for piece in ai_analyzer.analyze_stream(
                    db, "", ext,
                    history=body.history,
                    question=context + body.question,
                    knowledge=knowledge):
                yield "data: " + json.dumps({"text": piece}, ensure_ascii=False) + "\n\n"
            yield "data: [DONE]\n\n"
        except Exception as e:
            yield "data: " + json.dumps({"error": str(e)}, ensure_ascii=False) + "\n\n"

    return StreamingResponse(gen(), media_type="text/event-stream")


@router.post("/test")
def test_connection(db: Session = Depends(get_db), user=Depends(engineer_only)):
    """测试 AI 连通性: 发一条简单消息, 返回 {ok, msg, model}。"""
    cfg = ai_analyzer.get_all_settings(db)
    if not cfg["enabled"]:
        return {"ok": False, "msg": "AI 分析未启用"}

    proto = ai_analyzer.detect_protocol(db)
    base_url = cfg.get("base_url", "")
    api_key = ai_analyzer.get_setting(db, ai_analyzer.K_API_KEY)
    model = cfg.get("model", "")
    if not api_key:
        return {"ok": False, "msg": "未配置 API Key"}

    try:
        if proto == "anthropic":
            import httpx
            url = f"{base_url.rstrip('/')}/v1/messages"
            resp = httpx.post(url, json={
                "model": model, "max_tokens": 16,
                "messages": [{"role": "user", "content": "Hi"}],
            }, headers={
                "x-api-key": api_key,
                "anthropic-version": "2023-06-01",
                "content-type": "application/json",
            }, timeout=20)
            if resp.status_code == 200:
                data = resp.json()
                reply = data.get("content", [{}])[0].get("text", "")[:50]
                return {"ok": True, "msg": f"✓ 连通 {model}", "reply": reply}
            else:
                detail = resp.text[:300]
                return {"ok": False, "msg": f"API 返回 {resp.status_code}", "detail": detail}
        else:
            # OpenAI 协议
            from openai import OpenAI
            client = OpenAI(base_url=base_url, api_key=api_key, timeout=20)
            resp = client.chat.completions.create(
                model=model, messages=[{"role": "user", "content": "Hi"}],
                max_tokens=16,
            )
            reply = resp.choices[0].message.content[:50] if resp.choices else ""
            return {"ok": True, "msg": f"✓ 连通 {model}", "reply": reply}
    except Exception as e:
        return {"ok": False, "msg": str(e)[:300]}


# ---- 快捷模版(存在 backend/data/prompts.json) ----
PROMPTS_FILE = DATA_DIR / "prompts.json"

_DEFAULT_PROMPTS = {
    "prompts": [
        {"title": "常见告警排查", "prompt": "Straitbot 巡检机器人常见的告警代码有哪些? 如何根据告警 ID 快速定位问题?"},
        {"title": "下位机通信异常", "prompt": "机器人下位机(chassis)通信异常的常见原因和排查步骤是什么?"},
        {"title": "OTA 升级流程", "prompt": "OTA 升级上位机和下位机的标准流程是什么? 有哪些注意事项和回滚策略?"},
        {"title": "日志分析要点", "prompt": "分析机器人 decision 日志时, 应该重点关注哪些字段和异常模式?"},
        {"title": "电池与充电", "prompt": "机器人电池低电量保护机制是怎样的? 充电异常如何排查?"},
        {"title": "云台故障诊断", "prompt": "海康云台(PTZ)常见故障(断开连接/避障/操作失败)的原因和处理方法?"},
    ],
    "knowledge": """你是 Straitbot 智能巡检机器人的运维 AI 助手。以下是相关背景知识：

## 机器人 API 指令码(常用)
- cmd=2: 心跳包(3s/次, 含 robot_id)
- cmd=3: 设置机器人 ID
- cmd=4: 获取参数配置(含版本/云台/电池/限位等)
- cmd=5: 配置系统参数(速度/电池阈值/Home点)
- cmd=6: 获取版本信息(application/firmware/hardware/motion/sdk)
- cmd=7: 触发自检 / cmd=8: 获取自检结果 / cmd=9: 上传自检结果
- cmd=10: 获取告警列表 / cmd=11: 实时上传告警
- cmd=12: 清除导航告警 / cmd=13: 清除驱动器告警
- cmd=20: 上传状态(电量/CPU/温度/速度/位姿/连接) / cmd=21: 获取状态
- cmd=22: 电源信息 / cmd=23: 充电控制
- cmd=30: 获取位姿 / cmd=31: 设定位姿 / cmd=32: 运动控制 / cmd=33: 复位返航
- cmd=35/36/37/38: 云台控制(拍照/测温/录像)
- cmd=40/41: 升降杆控制
- cmd=100: 创建巡检 / cmd=101: 控制巡检(暂停/取消/恢复)
- cmd=102: 获取巡检信息 / cmd=103/104/105/106: 巡检状态/结果/进度上传
- cmd=107: 上传设备状态
- cmd=130-137: 电梯控制相关

## 告警代码(关键)
- 2xxxx: 机器人本体告警
  - 20001: 嵌入式板未连接
  - 20002: 与服务器断开连接
  - 20105: 电量低
  - 20106: 充电失败
  - 20107-20109: 轻度/中度/严重打滑
  - 20110: 底盘异常 / 20111: 急停触发
  - 20114-20117: 定位/规划/控制/决策异常
  - 20301-20305: 云台相关(初始化/登录/断开/操作失败/避障)
  - 21001/21002: 前后避障
- 1xxxx: 下位机/控制板告警
  - 10001: 下位机不支持的功能
  - 10003: 下位机正在初始化坐标
  - 10010: 超速 / 10011: 移动驱动器告警
  - 10014: 到达限位
  - 10101: 水平驱动器告警 / 10401: 升降杆驱动器告警

## 产品类型
- 0: 室内挂轨 / 1: 室外挂轨 / 2: Mini挂轨
- 3: 室内轮式 / 4: 室外轮式

## OTA 版本
- 上位机(application): 工控机上的主程序, 版本如 2.0.15
- 下位机(firmware): 嵌入式控制板固件, 版本如 2.1.42
- motion: 运动控制模块版本
- sdk: SDK 版本

## 部署结构
- 上位机路径: /home/nav/robot/robot/bin/robot
- 日志目录: /home/nav/robot/robot/filelog/ (decision*.log / http*.log / critical*.log)
- 安装脚本: /home/nav/robot/install.sh (自动备份到 robot_backup)
- OTA 安装包命名: straitbot-<floor|outdoor>-master-v<版本>-<时间>.zip

## 机器人状态 ID
- 0: 正常运行 / 1: 开始充电 / 2: 充电中 / 3: 前往充电
- 4: 自检中 / 5: 巡检中 / 6: 巡检暂停 / 7: 巡检挂起 / 8: 前往电梯口
"""
}


def _ensure_prompts_file():
    """文件不存在时自动创建默认模板。"""
    if not PROMPTS_FILE.exists():
        try:
            PROMPTS_FILE.parent.mkdir(parents=True, exist_ok=True)
            PROMPTS_FILE.write_text(
                json.dumps(_DEFAULT_PROMPTS, ensure_ascii=False, indent=2),
                encoding="utf-8")
        except Exception:
            pass


@router.get("/prompts")
def get_prompts(_=Depends(get_current_user)):
    """读取模板 + 知识库。"""
    _ensure_prompts_file()
    try:
        data = json.loads(PROMPTS_FILE.read_text(encoding="utf-8"))
        return {
            "prompts": data.get("prompts", []) if isinstance(data, dict) else [],
            "knowledge": data.get("knowledge", "") if isinstance(data, dict) else "",
        }
    except Exception:
        return {"prompts": [], "knowledge": ""}


@router.put("/prompts")
def save_prompts(body: dict, _=Depends(engineer_only)):
    """保存模板和知识库。body: {prompts: [...], knowledge: "..."}"""
    prompts = body.get("prompts", [])
    knowledge = body.get("knowledge", "")
    if not isinstance(prompts, list):
        raise HTTPException(400, "prompts 必须是数组")
    clean = {"prompts": [{"title": p.get("title", ""), "prompt": p.get("prompt", "")}
                        for p in prompts if p.get("title")],
             "knowledge": str(knowledge)}
    PROMPTS_FILE.write_text(json.dumps(clean, ensure_ascii=False, indent=2), encoding="utf-8")
    return {"ok": True, "msg": f"已保存 {len(clean['prompts'])} 条模板 + 知识库({len(clean['knowledge'])} 字符)"}
def log_content(kind: str, log_id: int,
                db: Session = Depends(get_db), user=Depends(get_current_user)):
    """获取日志全文(用于分析前预览, 限 200KB)。"""
    text = _read_log(db, kind, log_id)
    if len(text) > 200000:
        text = text[:200000] + f"\n...(已截断, 共 {len(text)} 字符)"
    return {"text": text, "length": len(text)}
