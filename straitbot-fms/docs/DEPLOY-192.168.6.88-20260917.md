# FMS 192.168.6.88 部署记录

- 时间：2026-09-17，北京时间约 17:44。
- 地址：http://192.168.6.88:8900/。
- 来源：`develop-0824`，提交 `0e2a1d8`（rail/sm.py 状态机实现 机器人行为）。
- 应用 VERSION 仍为 `2.1.0`；本次通过镜像标签区分部署提交，未修改业务版本号。
- 主机：ARM64；SSH 使用现有 `192.168.6.88` 配置、用户 `hxzh`。

## 目录与运行配置

- 现有部署配置：`/home/hxzh/straitbot-fms/`。
- 当前代码快照：`/home/hxzh/fms-releases/20260917-0e2a1d8/`，通过 `git archive HEAD` 上传。
- 持久化数据继续挂载 `/home/hxzh/straitbot-fms/data` 到 `/app/data`。
- 环境配置继续使用 `/home/hxzh/straitbot-fms/backend/.env`；保留既有账号和配置。
- 镜像：`straitbot-fms-backend:0e2a1d8`、`straitbot-fms-frontend:0e2a1d8`。
- 后端依赖文件 SHA256 与原部署一致，复用原 ARM64 依赖镜像并加入当前应用源码；前端执行项目 Dockerfile 构建。

后续启动使用两个 Compose 文件，避免误用旧源码或旧 latest 镜像：

```bash
cd /home/hxzh/straitbot-fms
docker compose -p straitbot-fms -f docker-compose.yml -f docker-compose.release.yml up -d --no-build
```

## 备份与回退

停止原后端后备份整个原部署目录（含数据和环境配置）：
`/home/hxzh/fms-backups/20260917-0e2a1d8/deployment-before.tar.gz`。
备份父目录权限为 700。

原镜像保留标签 `before-20260917-0e2a1d8`。仅回退应用镜像：

```bash
cd /home/hxzh/straitbot-fms
docker compose -p straitbot-fms -f docker-compose.yml -f /home/hxzh/fms-backups/20260917-0e2a1d8/docker-compose.rollback.yml up -d --no-build
```

数据恢复须先停止后端、备份更新后的数据并确认恢复范围；镜像回退不会自动恢复数据库。恢复后续启动时应同步选择对应 Compose 配置。

## 验证结果与范围

- 前端 `tsc -b && vite build` 成功；存在大资源包提示，未阻止构建。
- 隔离后端容器安装 pytest，挂载测试及 FSM 示例数据：99 项测试通过。
- 后端容器状态 healthy，外部 `/api/health` 返回 HTTP 200、`ok: true`。
- 浏览器实际登录成功，监控大盘正常，原有 1 条机器人记录保留。
- 航点绑定测点页面可打开，但页面明确为静态示例，接口与业务逻辑待开发；不代表业务下沉已完成。
- 部署后容器 `app/rail/sm.py` SHA256 与本地一致。
- 未执行真实机器人控制、OTA 或现场业务联调。
