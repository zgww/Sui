"""AI 日志分析服务。

采用 OpenAI 兼容协议(一套代码支持 DeepSeek/智谱GLM/通义/OpenAI/Ollama 等)。
模型配置存在数据库 settings 表, 由前端系统设置页配置。
"""
from __future__ import annotations
import json
from typing import Optional, Iterator
from openai import OpenAI
from sqlalchemy.orm import Session

from ..models import Setting
# anthropic 按需在 _build_client 内 import, 避免未配置时也强制安装


# 默认服务商预设: {key -> (label, base_url, 推荐模型, 协议)}
# 协议: "openai" 或 "anthropic"
PROVIDERS = {
    "zhipu":    ("智谱 GLM-5.2", "https://open.bigmodel.cn/api/anthropic", "glm-5.2", "anthropic"),
    "deepseek": ("DeepSeek", "https://api.deepseek.com", "deepseek-v4-flash", "openai"),
    "deepseek-anthropic": ("DeepSeek(Anthropic协议)", "https://api.deepseek.com/anthropic", "deepseek-v4-flash", "anthropic"),
    "qwen":     ("通义千问", "https://dashscope.aliyuncs.com/compatible-mode/v1", "qwen-plus", "openai"),
    "openai":   ("OpenAI", "https://api.openai.com/v1", "gpt-4o-mini", "openai"),
    "moonshot": ("月之暗面 Kimi", "https://api.moonshot.cn/v1", "moonshot-v1-8k", "openai"),
    "ollama":   ("Ollama(本地)", "http://127.0.0.1:11434/v1", "qwen2.5:7b", "openai"),
    "custom":   ("自定义", "", "", "openai"),
}

# 各服务商常用模型列表(前端下拉用; 含 DeepSeek 新模型)
MODELS_BY_PROVIDER = {
    "zhipu": ["glm-5.2", "glm-5.2[1m]", "glm-4-flash", "glm-4", "glm-4-plus", "glm-4-air"],
    "deepseek": ["deepseek-v4-flash", "deepseek-v4-pro", "deepseek-chat(旧,7/24弃用)", "deepseek-reasoner(旧)"],
    "deepseek-anthropic": ["deepseek-v4-flash", "deepseek-v4-pro"],
    "qwen": ["qwen-plus", "qwen-turbo", "qwen-max", "qwen2.5-72b-instruct"],
    "openai": ["gpt-4o-mini", "gpt-4o", "gpt-4.1-mini", "gpt-4.1", "o4-mini"],
    "moonshot": ["moonshot-v1-8k", "moonshot-v1-32k", "moonshot-v1-128k"],
    "ollama": ["qwen2.5:7b", "qwen2.5:14b", "llama3.1:8b", "deepseek-r1:7b"],
    "custom": [],
}


# settings 表的 key
K_PROVIDER = "ai_provider"
K_BASE_URL = "ai_base_url"
K_API_KEY  = "ai_api_key"
K_MODEL    = "ai_model"
K_ENABLED  = "ai_enabled"
K_EXTRA_INSTRUCTIONS = "ai_extra_instructions"   # 额外分析要求


def get_setting(db: Session, key: str, default: str = "") -> str:
    s = db.query(Setting).filter(Setting.key == key).first()
    return s.value if s and s.value else default


def set_setting(db: Session, key: str, value: str) -> None:
    s = db.query(Setting).filter(Setting.key == key).first()
    if s:
        s.value = value
    else:
        db.add(Setting(key=key, value=value))
    db.commit()


def get_all_settings(db: Session) -> dict:
    """读取全部 AI 配置(api_key 做脱敏返回)。"""
    prov = get_setting(db, K_PROVIDER, "zhipu")
    return {
        "provider": prov,
        "base_url": get_setting(db, K_BASE_URL, PROVIDERS["zhipu"][1]),
        "api_key": _mask(get_setting(db, K_API_KEY)),
        "api_key_set": bool(get_setting(db, K_API_KEY)),
        "model": get_setting(db, K_MODEL, PROVIDERS["zhipu"][2]),
        "protocol": detect_protocol(db),
        "enabled": get_setting(db, K_ENABLED, "0") == "1",
        "extra_instructions": get_setting(db, K_EXTRA_INSTRUCTIONS, ""),
    }


def _mask(key: str) -> str:
    if not key:
        return ""
    if len(key) <= 8:
        return "*" * len(key)
    return key[:4] + "*" * (len(key) - 8) + key[-4:]


def update_settings(db: Session, payload: dict) -> dict:
    """更新配置。api_key 为空字符串表示不改(保留原值)。"""
    if "provider" in payload and payload["provider"]:
        set_setting(db, K_PROVIDER, payload["provider"])
        # 选预设服务商时, 自动带出 base_url / 推荐模型 / 协议(若用户未单独提供)
        prov = payload["provider"]
        if prov in PROVIDERS:
            if "base_url" not in payload or not payload["base_url"]:
                set_setting(db, K_BASE_URL, PROVIDERS[prov][1])
            if "model" not in payload or not payload["model"]:
                set_setting(db, K_MODEL, PROVIDERS[prov][2])
            # 同步协议(GLM-5.2 = anthropic, 其他 = openai)
            set_setting(db, "ai_protocol", PROVIDERS[prov][3])
    if payload.get("base_url") is not None:
        set_setting(db, K_BASE_URL, payload["base_url"])
    if payload.get("api_key"):           # 空字符串视为不改
        set_setting(db, K_API_KEY, payload["api_key"])
    if payload.get("model") is not None:
        set_setting(db, K_MODEL, payload["model"])
    if "enabled" in payload:
        set_setting(db, K_ENABLED, "1" if payload["enabled"] else "0")
    if "extra_instructions" in payload:
        set_setting(db, K_EXTRA_INSTRUCTIONS, payload["extra_instructions"])
    if payload.get("protocol") in ("openai", "anthropic"):
        set_setting(db, "ai_protocol", payload["protocol"])
    return get_all_settings(db)


def detect_protocol(db: Session) -> str:
    """判断当前配置走哪种协议。

    规则:
      1) settings 表显式记录的 ai_protocol(用户在设置页选过)
      2) 否则按 base_url 推断: 含 /anthropic -> anthropic; 否则 openai
      3) 默认 openai
    """
    explicit = get_setting(db, "ai_protocol")
    if explicit in ("openai", "anthropic"):
        return explicit
    base_url = get_setting(db, K_BASE_URL, "")
    if "/anthropic" in base_url:
        return "anthropic"
    return "openai"


def _build_client(db: Session):
    """根据协议返回对应 SDK 客户端(openai 或 anthropic)。"""
    base_url = get_setting(db, K_BASE_URL)
    api_key = get_setting(db, K_API_KEY)
    if not api_key:
        return None, None
    proto = detect_protocol(db)
    if proto == "anthropic":
        import anthropic
        # anthropic key 不能为空; 本地代理可能用占位
        client = anthropic.Anthropic(api_key=api_key, base_url=base_url or None, timeout=60)
        return client, "anthropic"
    else:
        client = OpenAI(base_url=base_url or None, api_key=api_key, timeout=60)
        return client, "openai"


SYSTEM_PROMPT = """你是一名资深的机器人运维专家, 擅长分析 Straitbot 巡检机器人的日志。
用户会给你一段机器人日志(可能来自 decision/http/critical 等日志文件)。
请用中文进行分析, 输出包含以下部分(用 Markdown):

## 概要
一句话总结日志时段内机器人的整体状态。

## 异常与错误
列出日志中出现的 ERROR/WARN/告警/异常堆栈, 每条给出:
- 时间
- 类别(如 通信/驱动/云台/巡检/定位/系统)
- 简要描述

## 根因分析
对关键异常推断可能的原因。

## 影响评估
这些异常对机器人运行/巡检任务的潜在影响。

## 处理建议
给出可操作的排查/修复步骤(优先级排序)。

## 时间线
按时间顺序列出关键事件。

注意:
- 日志里的 cmd 数字对应 Straitbot API 指令码(如 cmd=20 状态上报, cmd=21 获取状态, cmd=10 告警)。
- 告警 id 含义: 2xxxx 本体(20105 电量低, 20301-20305 云台, 21001/21002 前后避障), 1xxxx 下位机/驱动器。
- 若日志无明显异常, 如实说明"运行正常", 不要编造问题。
- 聚焦事实, 不要泛泛而谈。
"""


def analyze_stream(db: Session, log_text: str, extra: str = "",
                  history: list = None, question: str = "",
                  knowledge: str = "") -> Iterator[str]:
    """流式分析/对话。knowledge 注入到 system prompt(给 AI 提供背景知识)。"""
    client, proto = _build_client(db)
    model = get_setting(db, K_MODEL, "glm-5.2")
    if client is None:
        yield "❌ 未配置 AI API Key, 请到「系统设置」配置后再试。"
        return

    if history:
        messages = list(history) + [{"role": "user", "content": question or "请继续"}]
    else:
        max_chars = 100000
        if len(log_text) > max_chars:
            log_text = log_text[:max_chars] + f"\n...(已截断, 原文共 {len(log_text)} 字符)"
        user_msg = "【机器人日志】\n```\n" + log_text + "\n```\n"
        if extra: user_msg += "\n【附加分析要求】\n" + extra + "\n"
        if question: user_msg += "\n【本次问题】\n" + question + "\n"
        messages = [{"role": "user", "content": user_msg}]

    full_system = (knowledge + "\n\n") if knowledge else ""
    full_system += SYSTEM_PROMPT

    try:
        if proto == "anthropic":
            yield from _stream_anthropic(
                base_url=get_setting(db, K_BASE_URL),
                api_key=get_setting(db, K_API_KEY),
                model=model, messages=messages, system=full_system)
        else:
            yield from _stream_openai(client, model, messages, system=full_system)
    except Exception as e:
        yield f"\n\n❌ AI 调用失败: {e}\n请检查「系统设置」中的 协议/base_url/api_key/模型名是否正确。"
    finally:
        # OpenAI 客户端持有 httpx 连接池(线程+连接), 用完必须关闭, 否则泄漏
        if client is not None and proto == "openai":
            try:
                client.close()
            except Exception:
                pass


def _stream_openai(client, model: str, messages: list, system: str = None) -> Iterator[str]:
    """OpenAI 协议流式。"""
    full = [{"role": "system", "content": system or SYSTEM_PROMPT}] + messages
    stream = client.chat.completions.create(
        model=model, messages=full, stream=True, temperature=0.3,
    )
    for chunk in stream:
        try:
            delta = chunk.choices[0].delta
            if delta and delta.content:
                yield delta.content
        except (IndexError, AttributeError):
            continue


def _stream_anthropic(base_url: str, api_key: str, model: str, messages: list, system: str = None) -> Iterator[str]:
    """Anthropic 协议流式 — 用 httpx 直连。"""
    import httpx
    url = f"{base_url.rstrip('/')}/v1/messages"
    headers = {"x-api-key": api_key, "anthropic-version": "2023-06-01", "content-type": "application/json"}
    body = {"model": model, "max_tokens": 8192, "system": system or SYSTEM_PROMPT,
            "messages": messages, "stream": True, "temperature": 0.3}
    with httpx.Client(timeout=120) as http:
        with http.stream("POST", url, json=body, headers=headers) as resp:
            # 非 200 抛出异常(带响应体, 方便排查)
            if resp.status_code != 200:
                text = resp.text[:500]
                raise RuntimeError(f"Anthropic API {resp.status_code}: {text}")
            # 逐行解析 SSE
            for line in resp.iter_lines():
                if not line or not line.startswith("data: "):
                    continue
                data = line[6:]  # 去掉 "data: " 前缀
                if data == "[DONE]":
                    continue
                try:
                    import json
                    event = json.loads(data)
                except Exception:
                    continue
                t = event.get("type", "")
                if t == "content_block_delta":
                    delta = event.get("delta", {}) or {}
                    text = delta.get("text", "")
                    if text:
                        yield text
                elif t == "message_stop":
                    break
