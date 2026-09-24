"""轨道机器人（挂轨）导航域。

分层：
- client.py       通用 TCP 连接客户端（内置状态机 / 自动重连 / 接收超时）
- messages/       协议 V2.0 语义层（每个消息一个文件，IBoardMsg/to_bytes/from_bytes）
- services/       服务层（BoardSrv：请求-响应 / 心跳 / 上发事件分发；Navigator 后续）
- routers/        REST + WS 对外接口 ——后续
"""
