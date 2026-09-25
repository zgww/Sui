"""轨道机器人（挂轨）导航域：服务层（asyncio 单事件循环内的服务对象，非 Actor/mailbox 模式）。

- board.py      BoardSrv：帧/消息层——请求-响应、心跳、上发事件分发（内部管理 RailClient 连接）
- navigator.py  Navigator：走点任务状态机（后续实现）
"""
