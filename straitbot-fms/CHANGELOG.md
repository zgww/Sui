# 更新日志 / Changelog

所有版本变更记录。打包时 `pack.sh` 会提示填写本版本说明。
格式遵循 [Keep a Changelog](https://keepachangelog.com/zh-CN/), 版本号遵循语义化版本。

---

## [Unreleased] / 待发布

(下一次打包会写入这里)

### ✨ 新增
- **Prefab 节点树系统**：目录 + `xx.prefab.json` 描述节点树，启动自动加载实例化
  - 类定义即注册（NodeBase.__init_subclass__），**新增节点类零前端改动**
  - Pydantic Schema 驱动 Inspector 表单（json_schema_extra.ui 元数据约定）
  - 内置节点：Sequence / Parallel / Selector、CronTimer / IntervalTimer、LogAction / HttpAction、ConfigNode
  - 生命周期：on_active / on_deactive / on_tick / on_error，父先子激活、子节点失败隔离
  - 配置信息 / 规则链 / 定时任务统一组织为 prefab，共享 Context（KV + 事件总线）
  - 前端「Prefab 编排」页：树导航 + Inspector 编辑 + 保存热重载

---

## [v1.0.2] - 2026-07-21

- 修复网段扫描在大网段(/16)下的超时问题
- 优化 AI 对话的上下文内存管理

---

## [v1.0.1] - 2026-07-21

- 新增打包脚本 pack.sh(支持版本号、版本说明录入、自动排除运行时数据)
- docker-compose 兼容老版本 Docker(18.09+, 去掉 name 字段)
- install.sh 增强: 环境检测、健康检查重试、备份/更新命令、版本号显示

---

## [1.0.0] - 2026-07-21 · 首个正式版

### ✨ 新增
- **机器人监控**：实时状态(电量/CPU/温度/位姿)、24h 趋势曲线、告警中心、版本历史
- **机器人管理**：CRUD、SSH+API 连通性测试、**网段自动扫描发现**(扫 6002 端口 + 自动探测 robot_id)
- **日志中心**(Tab 合并)：
  - 日志查看 + **AI 对话分析**(多轮对话、流式输出、导出 MD/HTML/PDF)
  - 在线拉日志(SFTP 远程目录浏览 + 勾选下载)
  - 日志上传(兼机器人文件服务、按机器人归档、保留期自动清理)
- **OTA 升级**：安装包管理(自动解析版本号)、升级任务(复用现场 install.sh、自带备份)、强制/版本检测
- **机器人参数配置**：cmd=4 读 / cmd=5 写，配置变更历史
- **指令调试**：任意 cmd 透传、快捷指令(返航/充电/自检/重启)
- **角色权限**：工程师(engineer 全功能) / 运维(operator 只读监控)
- **AI 多服务商支持**：智谱 GLM-5.2(Anthropic 协议)、DeepSeek、通义、OpenAI、Kimi、Ollama
- 手机响应式(同内网浏览器直接访问)

### 🏗 技术
- 后端：Python 3.11 + FastAPI + SQLAlchemy(SQLite) + APScheduler + paramiko
- 前端：Vue3 + Element Plus + Vite + ECharts
- 部署：Docker Compose(兼容 Docker 18.09+ / Compose v1&v2)、一键 install.sh
- 数据可移植：整目录打包即带走，`./install.sh backup` 一键备份

### 📌 已知限制
- 下位机(嵌入式)固件 OTA 仅预留接口，待补充烧录方式
- 机器人接入采用 HTTP 主动轮询(Socket 长连接未实现，结构已预留)
