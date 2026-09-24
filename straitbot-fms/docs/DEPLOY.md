# FMS 部署文档 v2.0

## 架构说明

| 组件 | 技术 | CPU 架构 |
|---|---|---|
| 后端 | Python 3.11 + FastAPI + uvicorn | **必须匹配目标机器** |
| 前端 | Vue3 + nginx (静态文件) | 架构无关(JS/CSS) |
| 数据库 | SQLite (data/fms.db) | 架构无关 |

**关键**: Docker 镜像分 amd64(x86_64) 和 arm64(aarch64)，不可混用。

## 一、部署模式

### 模式 A: 全量 Docker（首次部署 / 环境变更）

当**依赖变化**(requirements.txt / Dockerfile)时必须重建镜像。

```
1. 代码上传到服务器
2. docker compose build      # 构建镜像(拉取基础镜像 + pip install + npm build)
3. docker compose up -d       # 启动
```

### 模式 B: 增量部署（日常改代码）

当**只改 Python/JS 代码**，依赖不变时，直接推送代码文件即可，无需重建镜像。

#### 后端增量
```bash
# 1. 同步代码到服务器(rsync/scp/sftp)
rsync -avz ./backend/app/ user@host:~/straitbot-fms/backend/app/

# 2. 重启容器(代码已挂载为 volume)
docker restart straitbot-fms-backend
```

#### 前端增量
```bash
# 1. 本地构建前端
cd frontend && npm install && npm run build

# 2. 上传 dist 到服务器
scp -r dist/* user@host:~/straitbot-fms/frontend/dist/

# 3. 拷贝到容器（或 nginx 直接读挂载目录）
docker cp dist/. straitbot-fms-frontend:/usr/share/nginx/html/
docker exec straitbot-fms-frontend nginx -s reload
```

### 模式 C: 无 Docker（裸机 Python）
```
pip install -r requirements.txt
uvicorn app.main:app --host 0.0.0.0 --port 8000
```
前端用 nginx 直接 serve dist/ 目录。

---

## 二、版本号

- 版本号在 `VERSION` 文件（项目根 & backend/ 各一份）
- 后端: `GET /api/health` 和 `GET /api/settings/info` 都返回版本号
- 前端: 系统设置页显示版本号
- 每次修改代码，更新 VERSION 文件

---

## 三、环境准备

### 安装 Docker (amd64)
```bash
# Ubuntu/Debian
curl -fsSL https://get.docker.com | bash

# 麒麟 V10 / CentOS (无外网时用静态二进制)
curl -fsSL https://mirrors.tuna.tsinghua.edu.cn/docker-ce/linux/static/stable/x86_64/docker-26.tgz -o /tmp/docker.tgz
tar xzf /tmp/docker.tgz -C /tmp/ && sudo cp /tmp/docker/* /usr/local/bin/
sudo dockerd --data-root /var/lib/docker &
```

### 配置国内镜像加速（无外网必备）
```bash
sudo mkdir -p /etc/docker
cat > /etc/docker/daemon.json << EOF
{
  "registry-mirrors": [
    "https://docker.m.daocloud.io",
    "https://registry.cn-hangzhou.aliyuncs.com"
  ]
}
EOF
sudo systemctl restart docker
```

---

## 四、跨架构部署

| 源 | amd64 目标 | arm64 目标 |
|---|---|---|
| amd64 构建机 | ✅ 直接 push/load | ❌ 需交叉编译 |
| arm64 构建机 | ❌ 需交叉编译 | ✅ 直接 push/load |
| 多架构构建 | `docker buildx build --platform linux/amd64,linux/arm64` | |

### 导出/导入镜像（离线传输）
```bash
# 构建机
docker save straitbot-fms-backend straitbot-fms-frontend | gzip > fms-images.tar.gz
# 传输到目标机
scp fms-images.tar.gz target:~/
# 目标机
docker load < fms-images.tar.gz
```

---

## 五、快速启动命令

```bash
cd ~/straitbot-fms

# 创建网络
docker network create fms-net 2>/dev/null

# 启动后端
docker run -d --name straitbot-fms-backend --restart unless-stopped \
  --network fms-net --network-alias backend \
  --env-file ./backend/.env \
  -v ./backend/data:/app/data \
  -v ./backend/app:/app/app \
  -v ./VERSION:/app/VERSION \
  straitbot-fms-backend:latest

# 启动前端
docker run -d --name straitbot-fms-frontend --restart unless-stopped \
  -p 8900:80 --network fms-net \
  -v ./frontend/dist:/usr/share/nginx/html \
  straitbot-fms-frontend:latest
```

**关键 volume 挂载**:
- `-v ./backend/app:/app/app` → 后端代码变更只需 `docker restart`
- `-v ./frontend/dist:/usr/share/nginx/html` → 前端变更只需本地 `npm run build` 后同步
