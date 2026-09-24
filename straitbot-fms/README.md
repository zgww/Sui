# Straitbot FMS · 机器人运维管理平台

面向 Straitbot 机器人的运维平台: 监控、日志、OTA、参数配置、指令调试。
Web 后台, 电脑/手机浏览器均可访问。

## ✨ 功能

| 模块 | 运维(operator) | 工程师(engineer) |
|---|:--:|:--:|
| 监控大盘 / 机器人列表 / 单机详情(电量·CPU·温度曲线) | ✅ | ✅ |
| 告警中心 | ✅ | ✅ |
| 日志查看(浏览/下载/**AI 分析**) | ✅ | ✅ |
| **在线拉日志** (SFTP 远程目录浏览→下载) | — | ✅ |
| **日志上传管理** (兼机器人文件服务 upload) | — | ✅ |
| **OTA 升级中心** (复用现场 install.sh, 自动备份) | — | ✅ |
| 安装包管理 (上传/下载/删除, 自动解析版本号) | — | ✅ |
| **机器人参数配置** (cmd=4 读 / cmd=5 写, 含变更历史) | — | ✅ |
| **指令调试** (任意 cmd 透传, 快捷指令) | — | ✅ |
| 系统设置 | — | ✅ |

## 🚀 部署

### 前置
- Linux 服务器 + Docker + Docker Compose v2
- 服务器能 SSH 到机器人、能 HTTP 访问机器人 API(`http://机器人IP:6002/`)

### 一键部署
```bash
tar -xzf straitbot-fms.tar.gz
cd straitbot-fms
./install.sh          # 首次: 自动复制 .env, 提示修改
# 编辑 backend/.env (改 JWT_SECRET 和默认密码)
./install.sh up       # 构建并启动
```

访问 `http://<服务器IP>:8900`  
默认账号:
- `admin` / `admin` (工程师, 全功能)
- `operator` / `operator` (运维, 只读监控)

### 手机访问
手机与服务器在同一内网时, 浏览器输入 `http://192.168.x.x:8900` 即可, 界面自适应。

## 🔧 常用命令
```bash
./install.sh up        # 启动/更新
./install.sh down      # 停止
./install.sh rebuild   # 重建(改代码后)
./install.sh logs      # 看日志
./install.sh status    # 看容器状态
```

## 📦 移植 / 备份
所有持久化数据在 `backend/data/`:
```
backend/data/
├── fms.db              # SQLite (机器人配置/账号/监控时序/任务记录)
├── logs/<robot_id>/    # 拉取与上传的日志
└── packages/           # OTA 安装包
```
**整目录打包即可移植**:
```bash
tar -czf straitbot-fms-backup.tar.gz straitbot-fms/
# 拷到新机器解压后 ./install.sh up, 数据完整恢复
```

## 🏗 架构
```
浏览器 ── http://IP:8900 ──> nginx(前端SPA) ──/api/──> FastAPI 后端
                                                          ├── SQLite
                                                          ├── APScheduler(轮询)
                                                          ├── paramiko(SSH/SFTP)──> 机器人(22)
                                                          └── httpx ──────────> 机器人 API(6002)
```

## 🔌 机器人接入

平台通过两种方式访问机器人:
1. **HTTP API**: `POST http://机器人IP:6002/`, Header `X-ROBOT_ID` (cmd=4/6/10/21/22…)
2. **SSH/SFTP**: 拉日志、执行 OTA (复用机器人现有 `/home/nav/robot/install.sh`)

在「机器人列表 - 添加」中配置 IP、SSH 账号、日志目录、安装目录即可。

### OTA 流程(上位机)
1. SSH 连通性检查
2. 读取当前版本(cmd=6 / version 文件)
3. 非强制且版本相同 → 跳过
4. SCP 上传安装包到安装目录
5. SSH 执行: 解压 → 运行 install.sh(自带备份到 robot_backup/)
6. stop + start 重启上位机程序
7. 等待并校验新版本

### 机器人主动上传日志(文件服务)
平台 `/api/logs/upload` 兼容 API 文档「文件服务 上传」接口:
- `POST /api/logs/upload` (multipart: `file`, `robot_id`, `filename`, `source`)
- 需携带登录 token。如需让机器人本体免鉴权直传, 可在后端为该路由加白名单(见代码注释)。

## ⚙️ 配置项 (backend/.env)
| 变量 | 默认 | 说明 |
|---|---|---|
| FMS_PORT | 8900 | 对外端口 |
| JWT_SECRET | (需修改) | 登录令牌密钥 |
| DEFAULT_ENGINEER_USER/PASS | admin/admin | 首次创建的工程师账号 |
| DEFAULT_OPERATOR_USER/PASS | operator/operator | 首次创建的运维账号 |
| POLL_STATUS_INTERVAL_SEC | 10 | 状态轮询间隔(秒) |
| POLL_META_INTERVAL_SEC | 60 | 版本/告警/配置轮询间隔(秒) |
| DEFAULT_LOG_RETENTION_DAYS | 30 | 默认日志保留天数 |

## 📝 备注
- 下位机(嵌入式)固件 OTA 本期预留接口(`ota_packages.channel='firmware'`), 待补充下位机烧录方式后扩展
- Socket 长连接接入本期未实现(采用 HTTP 主动轮询), `robot_api.py` 结构便于后续扩展

## 🤖 AI 日志分析
平台内置 AI 日志分析能力, 支持 OpenAI 兼容协议的任意服务商。

**配置**(`系统设置 → AI 分析设置`, 仅工程师可见):
1. 选择服务商(内置 DeepSeek/智谱GLM/通义千问/OpenAI/Kimi/Ollama 预设)
2. 填写 API Key + 模型名
3. 开启「启用 AI 分析」开关

**使用**: `日志查看` → 任一日志 → 「AI分析」按钮 → 流式输出分析报告(概要/异常/根因/影响/处理建议/时间线)。

推荐: **智谱 GLM-5.2**(`glm-5.2`, 长任务旗舰, 1M 上下文用 `glm-5.2[1m]`) 或 DeepSeek(便宜)。本地部署可用 Ollama。

数据安全: API Key 仅存本平台数据库, 不会外传; 日志内容会发送给你配置的 AI 服务商进行分析。

## 🩺 故障排查
- **机器人显示离线**: 检查「机器人列表 - 连通性」, 确认 SSH/API 是否可达
- **OTA 失败**: 任务「日志」列显示完整步骤, 重点看 SSH 执行输出
- **端口冲突**: 改 `.env` 的 `FMS_PORT` 后 `./install.sh up`
