#!/usr/bin/env bash
# ============================================================
# Straitbot FMS 一键部署脚本(增强兼容版)
#
# 用法:
#   ./install.sh              # 默认: 构建并启动(up)
#   ./install.sh up           # 构建并启动(同上)
#   ./install.sh build        # 仅构建镜像
#   ./install.sh down         # 停止并删除容器
#   ./install.sh restart      # 重启容器
#   ./install.sh rebuild      # 停止+重建+启动
#   ./install.sh logs         # 查看日志
#   ./install.sh status       # 查看容器状态
#   ./install.sh backup       # 备份数据到 backup_时间.tar.gz
#   ./install.sh env          # 编辑 .env 配置
#
# 兼容性:
#   - Docker 18.09+ / Compose v1 (docker-compose) 和 v2 (docker compose) 均支持
#   - 自动处理老版本 Docker 的坑(no name 字段 / 旧 compose 等)
# ============================================================
set -e

cd "$(dirname "$0")"
ROOT="$(pwd)"
ENV_FILE="backend/.env"
ACTION="${1:-up}"
VERSION="$(cat VERSION 2>/dev/null || echo 'unknown')"

echo ""
echo "╔══════════════════════════════════════════╗"
echo "║   Straitbot FMS 机器人运维管理平台        ║"
echo "║   版本: v$VERSION"
echo "╚══════════════════════════════════════════╝"
echo ""

# ---- 颜色 ----
G() { printf "\033[32m%s\033[0m\n" "$1"; }
Y() { printf "\033[33m%s\033[0m\n" "$1"; }
R() { printf "\033[31m%s\033[0m\n" "$1"; }
B() { printf "\033[36m%s\033[0m\n" "$1"; }

# ---- 1. 环境检查 ----
echo "=== 1) 环境检查 ==="

# Docker
if ! command -v docker >/dev/null 2>&1; then
  R "✗ 未检测到 docker!"
  echo "  请先安装 Docker:"
  echo "    curl -fsSL https://get.docker.com | sh"
  echo "  或参考: https://docs.docker.com/engine/install/"
  exit 1
fi
DOCKER_VER=$(docker --version 2>/dev/null)
G "✓ $DOCKER_VER"

# Docker 服务是否运行
if ! docker info >/dev/null 2>&1; then
  Y "! Docker daemon 未运行, 尝试启动..."
  if command -v systemctl >/dev/null 2>&1; then
    sudo systemctl start docker 2>/dev/null || {
      Y "请手动启动 docker: sudo systemctl start docker"
      exit 1
    }
    sleep 2
  else
    Y "请手动启动 docker 服务后重试"
    exit 1
  fi
fi
G "✓ Docker daemon 运行中"

# Compose(优先 v2, 回退 v1)
DC=""
if docker compose version >/dev/null 2>&1; then
  DC="docker compose"
  G "✓ Compose v2 ($(docker compose version --short 2>/dev/null))"
elif command -v docker-compose >/dev/null 2>&1; then
  DC="docker-compose"
  V1_VER=$(docker-compose version --short 2>/dev/null || echo "未知")
  Y "! 使用 Compose v1 ($V1_VER) - 已兼容老版本 compose 格式"
  # v1 老版本(< 1.27)不支持 3.7 的某些特性, 但基本够用
else
  R "✗ 未检测到 docker compose!"
  echo "  请安装 Docker Compose:"
  echo "    方式1(推荐, v2): apt-get install docker-compose-plugin"
  echo "    方式2(v1):"
  echo "      sudo curl -L https://github.com/docker/compose/releases/download/v2.24.5/docker-compose-\$(uname -s)-\$(uname -m) -o /usr/local/bin/docker-compose"
  echo "      sudo chmod +x /usr/local/bin/docker-compose"
  exit 1
fi

# ---- 2. .env 配置 ----
echo ""
echo "=== 2) 配置检查 ==="
if [ ! -f "$ENV_FILE" ]; then
  Y "! 未发现 $ENV_FILE, 从模板创建"
  cp backend/.env.example "$ENV_FILE"
  Y "✓ 已创建 $ENV_FILE"
  Y ""
  Y "═══════════════════════════════════════════════════"
  Y " 重要: 请修改以下配置后再运行 ./install.sh up"
  Y "═══════════════════════════════════════════════════"
  Y " 编辑: vi $ENV_FILE"
  Y ""
  Y " 必改项:"
  Y "   JWT_SECRET=改成随机长串(建议 openssl rand -hex 32)"
  Y "   DEFAULT_ENGINEER_PASS=改成你的密码"
  Y "   DEFAULT_OPERATOR_PASS=改成运维密码"
  Y ""
  Y " 可选项:"
  Y "   FMS_PORT=8900  (对外端口, 改了要确认防火墙放行)"
  Y ""
  Y " 改完后重新运行: ./install.sh up"
  exit 0
fi
G "✓ 配置文件存在: $ENV_FILE"

# 端口
PORT=$(grep -E '^FMS_PORT=' "$ENV_FILE" 2>/dev/null | head -1 | cut -d= -f2 | tr -d '[:space:]')
PORT="${PORT:-8900}"
echo "  对外端口: $PORT"

# 端口占用检查
if ss -tln 2>/dev/null | grep -q ":$PORT " || netstat -tln 2>/dev/null | grep -q ":$PORT "; then
  Y "! 端口 $PORT 可能被占用, 检查中..."
  OCCUPANT=$(ss -tlnp 2>/dev/null | grep ":$PORT " | head -1)
  if [ -n "$OCCUPANT" ]; then
    Y "  占用: $OCCUPANT"
    Y "  若要换端口, 修改 .env 的 FMS_PORT 后重试"
  fi
fi

# ---- 离线镜像检测 ----
# 如果存在 images/fms_final.tar, 自动加载(离线部署模式)
IMAGES_TAR="$ROOT/images/fms_final.tar"
OFFLINE_MODE=false
if [ -f "$IMAGES_TAR" ]; then
  B "检测到离线镜像包: images/fms_final.tar ($(du -h "$IMAGES_TAR" | cut -f1))"
  B "进入离线部署模式(不需要外网, 直接加载预构建镜像)..."
  OFFLINE_MODE=true
  if ! docker images | grep -q "straitbot-fms-backend"; then
    docker load -i "$IMAGES_TAR" 2>&1 | tail -5
    G "✓ 离线镜像已加载"
  else
    G "✓ 镜像已存在, 跳过加载"
  fi
fi

# ---- 外网预检(仅在线模式) ----
if [ "$OFFLINE_MODE" = "false" ]; then
  B "外网连通性预检..."
  NET_OK=true
  # 测 docker registry
  if timeout 8 curl -fsI https://registry-1.docker.io/v2/ >/dev/null 2>&1; then
    G "  ✓ Docker Hub 可达(在线拉镜像)"
  else
    Y "  ! Docker Hub 不可达(可能需要镜像加速或离线部署)"
    # 测国内镜像源
    if timeout 8 curl -fsI https://docker.m.daocloud.io/v2/ >/dev/null 2>&1; then
      G "  ✓ daocloud 镜像源可达"
    else
      Y "  ! 国内镜像源也不通"
      Y "    如果构建失败, 请用离线模式:"
      Y "    1. 把 images/fms_final.tar 放到本项目 images/ 目录"
      Y "    2. 重新 ./install.sh up"
      NET_OK=false
    fi
  fi
  # 测 PyPI(pip install 用)
  if timeout 8 curl -fsI https://pypi.tuna.tsinghua.edu.cn/simple/ >/dev/null 2>&1; then
    G "  ✓ 清华 PyPI 可达"
  else
    Y "  ! 清华 PyPI 不通, 后端构建可能失败"
    NET_OK=false
  fi
  if [ "$NET_OK" = "false" ]; then
    Y ""
    Y "  ⚠ 外网受限, 强烈建议用离线模式部署(详见 README)"
  fi
fi

# 磁盘空间检查(至少 2GB)
AVAIL_GB=$(df -BG . 2>/dev/null | awk 'NR==2{print $4}' | tr -d 'G')
if [ -n "$AVAIL_GB" ] && [ "$AVAIL_GB" -lt 2 ] 2>/dev/null; then
  R "✗ 磁盘空间不足! 剩余 ${AVAIL_GB}GB, 至少需要 2GB"
  df -h .
  exit 1
fi
G "✓ 磁盘空间充足(剩余 ${AVAIL_GB:-?}GB)"

# ---- 3. 权限检查(data 目录可写) ----
mkdir -p backend/data/logs backend/data/packages
chmod -R 777 backend/data 2>/dev/null || sudo chmod -R 777 backend/data 2>/dev/null || true
G "✓ 数据目录就绪: backend/data/"

# ---- 兼容老版本 Docker(18.x) ----
# 老 Docker 的 BuildKit 支持不稳定, 多阶段构建可能报错。禁用 BuildKit 走经典构建器。
export DOCKER_BUILDKIT=0
export COMPOSE_DOCKER_CLI_BUILD=0
# 老 compose v1 对并行构建支持差
if [ "$DC" = "docker-compose" ]; then
  export COMPOSE_INTERACTIVE_NO_CLI=1
fi

# 生成离线模式的 compose 文件(只引用镜像, 不 build)
_gen_offline_compose() {
  cat > "$ROOT/docker-compose.offline.yml" <<EOF
version: "3.7"
services:
  backend:
    image: straitbot-fms-backend:latest
    container_name: straitbot-fms-backend
    restart: unless-stopped
    env_file:
      - ./backend/.env
    volumes:
      - ./backend/data:/app/data
    expose:
      - "8000"
    networks:
      - fms-net
  frontend:
    image: straitbot-fms-frontend:latest
    container_name: straitbot-fms-frontend
    restart: unless-stopped
    depends_on:
      - backend
    ports:
      - "${PORT:-8900}:80"
    networks:
      - fms-net
networks:
  fms-net:
    driver: bridge
EOF
  # 临时替换 DC, 指向 offline compose
  DC="$DC -f docker-compose.offline.yml"
}

# ---- 4. 执行动作 ----
echo ""
echo "=== 3) 执行: $ACTION ==="

case "$ACTION" in
  build)
    B "构建镜像(首次约 5-10 分钟, 取决于网络)..."
    $DC build
    G "✓ 构建完成"
    ;;

  up)
    if [ "$OFFLINE_MODE" = "true" ]; then
      B "离线模式: 用预构建镜像启动(秒级, 不构建)..."
      # 切换到离线 compose(不 build, 只用 image)
      _gen_offline_compose
      $DC up -d
      G "✓ 容器已启动(离线模式)"
    else
      B "在线模式: 构建镜像并启动(首次约 5-10 分钟)..."
      $DC up -d --build
      G "✓ 镜像构建完成, 容器已启动"
    fi

    # 等待健康检查
    B "等待后端就绪..."
    HEALTH_OK=false
    for i in $(seq 1 40); do
      if curl -fs "http://127.0.0.1:$PORT/api/health" >/dev/null 2>&1; then
        HEALTH_OK=true
        break
      fi
      # 检查容器是否还在(可能启动失败)
      if ! docker ps --format '{{.Names}}' 2>/dev/null | grep -q straitbot-fms-backend; then
        # 容器没了, 看日志
        if [ $i -gt 5 ]; then
          R "✗ 后端容器启动失败!"
          Y "最近日志:"
          $DC logs --tail=30 backend 2>&1 | tail -30
          exit 1
        fi
      fi
      printf "  [%d/40] 等待后端启动...\r" "$i"
      sleep 5
    done
    echo ""

    if [ "$HEALTH_OK" = "true" ]; then
      # 取本机 IP 用于提示
      LOCAL_IP=$(hostname -I 2>/dev/null | awk '{print $1}' || ip -4 addr show 2>/dev/null | grep -oP '(?<=inet\s)\d+(\.\d+){3}' | grep -v '^127\.' | head -1 || echo "本机IP")
      echo ""
      G "═══════════════════════════════════════════════════"
      G " ✅ 部署成功!"
      G "═══════════════════════════════════════════════════"
      echo ""
      B "  访问地址:  http://$LOCAL_IP:$PORT"
      B "             http://127.0.0.1:$PORT"
      echo ""
      B "  默认账号:"
      B "    工程师: admin / admin     (全功能)"
      B "    运维:   operator / operator (监控只读)"
      echo ""
      Y "  ⚠️  请尽快登录后修改默认密码!"
      echo ""
      B "  常用命令:"
      B "    ./install.sh status   # 查看状态"
      B "    ./install.sh logs     # 查看日志"
      B "    ./install.sh down     # 停止"
      B "    ./install.sh backup   # 备份数据"
      echo ""
    else
      R "✗ 后端启动超时(40 次健康检查未通过)"
      Y "排查:"
      Y "  1) 查看日志: $DC logs backend"
      Y "  2) 端口 $PORT 是否被占用: ss -tln | grep $PORT"
      Y "  3) .env 配置是否正确"
      exit 1
    fi
    ;;

  down)
    $DC down
    G "✓ 已停止"
    ;;

  restart)
    $DC restart
    G "✓ 已重启"
    ;;

  rebuild)
    B "停止并重建..."
    $DC down
    $DC up -d --build
    G "✓ 重建完成"
    ;;

  logs)
    B "实时日志(Ctrl+C 退出):"
    $DC logs -f --tail=200
    ;;

  status)
    $DC ps
    echo ""
    B "健康检查:"
    if curl -fs "http://127.0.0.1:$PORT/api/health" >/dev/null 2>&1; then
      G "  ✓ 服务正常"
    else
      R "  ✗ 服务不可达"
    fi
    ;;

  backup)
    TS=$(date +%Y%m%d_%H%M%S)
    BACKUP="straitbot-fms-backup-$TS.tar.gz"
    B "备份数据到 $BACKUP (含数据库+日志+安装包+配置)..."
    # 停容器避免数据库写竞争(可选, 但更安全)
    $DC stop >/dev/null 2>&1 || true
    tar -czf "$BACKUP" \
        backend/data \
        backend/.env \
        docker-compose.yml \
        install.sh 2>/dev/null
    $DC start >/dev/null 2>&1 || true
    SIZE=$(du -h "$BACKUP" | cut -f1)
    G "✓ 备份完成: $BACKUP ($SIZE)"
    echo ""
    B "恢复方法(在新机器):"
    B "  tar -xzf $BACKUP -C straitbot-fms/"
    B "  cd straitbot-fms && ./install.sh up"
    ;;

  env)
    B "打开配置编辑器..."
    EDITOR="${EDITOR:-vi}"
    $EDITOR "$ENV_FILE"
    ;;

  update)
    B "更新代码后重建(保留数据)..."
    $DC up -d --build
    G "✓ 更新完成"
    ;;

  *)
    R "未知动作: $ACTION"
    echo ""
    echo "用法: $0 [动作]"
    echo ""
    echo "动作:"
    echo "  up        构建并启动(默认)"
    echo "  build     仅构建镜像"
    echo "  down      停止并删除容器"
    echo "  restart   重启容器"
    echo "  rebuild   停止+重建+启动"
    echo "  update    更新代码后重建(保留数据)"
    echo "  logs      查看实时日志"
    echo "  status    查看容器状态+健康检查"
    echo "  backup    备份数据(数据库+日志+配置)"
    echo "  env       编辑 .env 配置"
    exit 1
    ;;
esac
