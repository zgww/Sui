# 巡检计划立即执行接口

## 来源与范围

依据 [Straitbot API 文档.pdf](https://jcnnojumuzl2.feishu.cn/wiki/YEXbwEqfSie3tIkT1QncnQlUn0g) V2.1.7（2025-12-04，巡检接口修订）的 cmd=100、cmd=102 接入。仅修改 FMS，Java/Vue 旧架构继续维护。

## 调用链与报文

巡检计划“立即执行” → FMS 执行接口 → 固化航点/动作快照并取得机器人执行锁 → cmd=102 检查空闲 → HTTP POST 机器人根路径，请求头 X-ROBOT_ID 使用机器人外部编号。

```json
{"cmd":100,"content":"{\"plan\":\"日常巡检\",\"id\":\"fms-unique-id\",\"name\":\"日常巡检\",\"waypoint\":[{\"index\":0,\"id\":\"point-1\",\"type\":0,\"pose\":{\"point\":{\"x\":1,\"y\":2},\"theta\":90},\"action\":[{\"id\":\"delay-1\",\"type\":201,\"action_delay_msec\":1000}]}]}"}
```

- content 为标准 JSON 字符串；FMS 数据库仍保留对象快照。禁止 Python 字典 repr。
- 不发送 file 和 schedule。文档规定排期为空时单次立即执行；计划的每日/每周时间仍由 FMS 本地调度。
- type=201 延时使用 action_delay_msec（毫秒），兼容已保存快照中的 duration；拍摄/录音动作保留 duration。
- 不发送 substationMapsId；地图和楼层仍用于 FMS 分段审计。跨段继续需要人工确认现场已完成换图/到层，不代表自动乘梯或切换地图。
- 不发送 detectType（巡检任务里标记动作点数据由 FMS 处理还是上传平台处理的字段）。它是 FMS 侧的路由提示，设备协议未定义，发送前在 `immediate_payload` 里裁掉，与 substationMapsId 同一处理方式；缺省 platform 即旧版行为，老数据无需改动。

## 结果与兼容

code=0 表示机器人接受请求，前端显示返回消息并打开执行记录；完成状态仍由报告/查询推进。非零 code 显示设备错误并释放执行锁。超时、连接异常或无法解析响应记为 unknown，保留执行锁防止重复下发。相同幂等键重复请求返回既有记录。

旧 /inspection/tasks 接口同时修正对象内容序列化，已有字符串内容保持兼容。新适配器仅处理发送副本，不修改历史快照。

## 验证与回退

运行 `python -m pytest tests -q --disable-warnings`。协议测试使用 httpx.MockTransport 验证真实 HTTP 客户端封装、设备拒绝、忙碌、超时、无效响应和重复点击；Demo 覆盖机器人调用并记录 demo-last-cmd100.json，不向真实设备发指令。

回退使用部署前后端镜像和 compose 备份；本次不修改数据库结构或测点档案。模拟通过不能替代现场固件的真实联调。
