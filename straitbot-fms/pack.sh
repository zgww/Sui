#!/usr/bin/env bash
# ============================================================
# Straitbot FMS 安装包打包脚本
#
# 作用: 把项目打包成可分发的安装包(不含运行时数据)
#
# 用法:
#   ./pack.sh                    # 自动从 VERSION 文件读版本号
#   ./pack.sh 1.2.0              # 指定版本号
#   ./pack.sh 1.2.0 patch        # 同时把 VERSION 文件改成 1.2.0
#
# 产出: dist/straitbot-fms-v<版本>-<时间>.tar.gz
#
# 打包内容(代码 + 配置模板 + 空数据目录):
#   - backend/  (含 Dockerfile, 代码, requirements, .env.example)
#   - frontend/ (含 Dockerfile, 源码, nginx.conf)
#   - docker-compose.yml, install.sh, VERSION, README.md
#
# 排除(运行时数据 + 临时文件):
#   - backend/data/fms.db        数据库(含测试机器人)
#   - backend/data/logs/*        拉取/上传的日志
#   - backend/data/packages/*    OTA 安装包
#   - backend/.env               实际配置(只保留 .env.example)
#   - node_modules, dist, __pycache__, .venv
# ============================================================
set -e

cd "$(dirname "$0")"
ROOT="$(pwd)"
VERSION_FILE="VERSION"

# 颜色
G() { printf "\033[32m%s\033[0m\n" "$1"; }
Y() { printf "\033[33m%s\033[0m\n" "$1"; }
R() { printf "\033[31m%s\033[0m\n" "$1"; }
B() { printf "\033[36m%s\033[0m\n" "$1"; }

# ---- 1. 确定版本号 + 模式 ----
OFFLINE=false
# 解析参数: 版本号, patch/save, --offline
for arg in "$@"; do
  case "$arg" in
    --offline|-o) OFFLINE=true ;;
  esac
done

if [ -n "$1" ] && [ "$1" != "--offline" ] && [ "$1" != "-o" ]; then
  VERSION="$1"
  # 第 2/3 参数是 patch/save 时, 更新 VERSION 文件
  for arg in "${@:2}"; do
    if [ "$arg" = "patch" ] || [ "$arg" = "save" ]; then
      echo "$VERSION" > "$VERSION_FILE"
      G "✓ 已更新 $VERSION_FILE -> $VERSION"
      break
    fi
  done
else
  VERSION="$(cat "$VERSION_FILE" 2>/dev/null || echo '')"
  if [ -z "$VERSION" ]; then
    R "✗ 未指定版本号, 且 $VERSION_FILE 不存在!"
    echo "  用法: ./pack.sh <版本号>           例如: ./pack.sh 1.0.3"
    echo "        ./pack.sh <版本号> patch     更新版本号并打包"
    echo "        ./pack.sh <版本号> --offline 含镜像离线打包(部署机零外网)"
    exit 1
  fi
fi

# 规范化版本号(去掉前缀 v)
VERSION="${VERSION#v}"

TIMESTAMP=$(date +%Y%m%d_%H%M)
PKG_NAME="straitbot-fms-v${VERSION}-${TIMESTAMP}"
DIST_DIR="$ROOT/dist"
mkdir -p "$DIST_DIR"

# ---- 录入本版本说明(写到 CHANGELOG.md 顶部 + 包内 RELEASE_NOTES) ----
CHANGELOG="$ROOT/CHANGELOG.md"
DATE_TODAY=$(date +%Y-%m-%d)
echo ""
B "[版本说明] 准备记录 v$VERSION 的更新内容"
echo "  请简要描述本版本变更(可多行, 输入空行结束):"
echo "  示例: 修复 AI 对话在长日志下截断问题; 新增批量导入机器人"
echo ""

NOTES=""
if [ -t 0 ]; then  # 终端交互模式
  while IFS= read -r line; do
    [ -z "$line" ] && break
    if [ -z "$NOTES" ]; then NOTES="$line"; else NOTES="$NOTES
$line"; fi
  done
fi

# 如果用户没输入, 用默认说明
if [ -z "$NOTES" ]; then
  NOTES="例行更新/bug 修复"
  Y "  (未输入, 使用默认说明: $NOTES)"
fi

# 生成单行版备注(用于 banner)
NOTES_ONELINE=$(echo "$NOTES" | head -1)

# 更新 CHANGELOG.md: 在 [Unreleased] 后插入新版本块(并重置 Unreleased 占位)
if [ -f "$CHANGELOG" ]; then
  # 新的 Unreleased 段 + 新版本段(整体替换原 Unreleased 段)
  REPLACEMENT="## [Unreleased] / 待发布

(下一次打包会写入这里)

---

## [v$VERSION] - $DATE_TODAY

$NOTES

---"
  # awk: 遇到 [Unreleased] 开始跳过(直到下一个 "## [v" 或文件中已存在的第一个 "---" 之后),
  #      替换为 REPLACEMENT; 用 state 机实现
  awk -v rep="$REPLACEMENT" '
    BEGIN { state = 0 }
    # 进入替换区: 遇到 Unreleased
    state == 0 && /^## \[Unreleased/ { state = 1; print rep; next }
    # 替换区内: 跳过原 Unreleased 段(到第一个独立的 --- 结束)
    state == 1 && /^---[[:space:]]*$/ { state = 2; next }
    state == 1 { next }
    { print }
  ' "$CHANGELOG" > "$CHANGELOG.tmp" && mv "$CHANGELOG.tmp" "$CHANGELOG"
  G "  ✓ 已追加版本说明到 CHANGELOG.md"
fi

echo ""
B "╔══════════════════════════════════════════╗"
B "║  打包 Straitbot FMS v$VERSION"
B "║  $NOTES_ONELINE"
B "╚══════════════════════════════════════════╝"
echo ""

# ---- 2. 准备临时打包目录(复制一份干净的) ----
STAGE="/tmp/${PKG_NAME}"
rm -rf "$STAGE"
mkdir -p "$STAGE"

B "[1/4] 复制项目文件到临时目录..."
# 复制整个项目(用 rsync 方便排除; 没有 rsync 就用 cp + 手动清理)
if command -v rsync >/dev/null 2>&1; then
  rsync -a --quiet \
    --exclude='__pycache__' \
    --exclude='*.pyc' \
    --exclude='.venv' \
    --exclude='node_modules' \
    --exclude='dist' \
    --exclude='.git' \
    --exclude='backend/data/fms.db' \
    --exclude='backend/data/logs/*' \
    --exclude='backend/data/packages/*' \
    --exclude='backend/.env' \
    --exclude='*.tar.gz' \
    --exclude='backup_*.tar.gz' \
    --exclude='straitbot-fms-backup-*' \
    "$ROOT/" "$STAGE/"
else
  # 没 rsync: 先 cp 再清理
  cp -r "$ROOT/." "$STAGE/"
  # 清理运行时数据和临时文件
  find "$STAGE" -type d -name __pycache__ -exec rm -rf {} + 2>/dev/null || true
  find "$STAGE" -name '*.pyc' -delete 2>/dev/null || true
  rm -rf "$STAGE/backend/.venv" "$STAGE/frontend/node_modules" "$STAGE/frontend/dist" 2>/dev/null || true
  rm -f "$STAGE/backend/data/fms.db" 2>/dev/null || true
  rm -rf "$STAGE/backend/data/logs"/* 2>/dev/null || true
  rm -rf "$STAGE/backend/data/packages"/* 2>/dev/null || true
  rm -f "$STAGE/backend/.env" 2>/dev/null || true
  find "$STAGE" -maxdepth 1 -name '*.tar.gz' -delete 2>/dev/null || true
  find "$STAGE" -maxdepth 1 -name 'backup_*.tar.gz' -delete 2>/dev/null || true
fi
G "  ✓ 文件已复制"

# ---- 离线模式: 导出 Docker 镜像 ----
if [ "$OFFLINE" = "true" ]; then
  B "  [离线模式] 导出 Docker 镜像(需要本地已构建好 FMS 镜像)..."
  mkdir -p "$STAGE/images"
  if ! docker images | grep -q "straitbot-fms-backend"; then
    R "  ✗ 本地没有 straitbot-fms-backend 镜像!"
    Y "    请先在本机构建一次: docker compose build"
    Y "    或从已部署的机器导出: docker save -o fms_final.tar straitbot-fms-backend:latest straitbot-fms-frontend:latest"
    Y "    然后放到本项目的 images/fms_final.tar, 重新运行 pack.sh --offline"
    exit 1
  fi
  # 检查是否已有现成的 fms_final.tar(避免重复导出)
  if [ -f "$ROOT/images/fms_final.tar" ]; then
    G "  ✓ 复用现有 images/fms_final.tar ($(du -h "$ROOT/images/fms_final.tar" | cut -f1))"
    cp "$ROOT/images/fms_final.tar" "$STAGE/images/"
  else
    Y "  导出镜像(约 600MB, 需要 1-2 分钟)..."
    docker save -o "$STAGE/images/fms_final.tar" \
      straitbot-fms-backend:latest straitbot-fms-frontend:latest 2>&1 | tail -3
    if [ ! -s "$STAGE/images/fms_final.tar" ]; then
      R "  ✗ 镜像导出失败"
      exit 1
    fi
    G "  ✓ 镜像已导出 ($(du -h "$STAGE/images/fms_final.tar" | cut -f1))"
  fi
fi

# ---- 3. 确保数据目录结构存在(空) ----
B "[2/4] 确保数据目录结构..."
mkdir -p "$STAGE/backend/data/logs"
mkdir -p "$STAGE/backend/data/packages"
# 放占位文件保证空目录能被 tar 保留
touch "$STAGE/backend/data/logs/.gitkeep"
touch "$STAGE/backend/data/packages/.gitkeep"
G "  ✓ backend/data/{logs,packages} 空目录就绪"

# 确保有 .env.example
if [ ! -f "$STAGE/backend/.env.example" ]; then
  Y "  ! 未找到 backend/.env.example, 从 .env 复制(脱敏)"
  if [ -f "$STAGE/backend/.env" ]; then
    sed -E 's/(API_KEY|SECRET|PASS|PASSWORD)=.*/\1=请填入你的值/' "$STAGE/backend/.env" > "$STAGE/backend/.env.example"
  fi
fi
G "  ✓ .env.example 存在"

# install.sh 可执行
chmod +x "$STAGE/install.sh" "$STAGE/pack.sh" 2>/dev/null || true

# 生成独立的 RELEASE_NOTES.md(放包内, 收包人一眼看到本版本说明)
cat > "$STAGE/RELEASE_NOTES.md" <<EOF
# Straitbot FMS v$VERSION 发布说明

**发布日期**: $DATE_TODAY
**版本号**: v$VERSION
**构建时间**: $TIMESTAMP

## 本版本内容

$NOTES

## 部署方法

\`\`\`bash
tar -xzf straitbot-fms-v${VERSION}-*.tar.gz
cd straitbot-fms-v${VERSION}-*
./install.sh            # 首次: 自动生成 .env
vi backend/.env         # 修改密码和 JWT_SECRET
./install.sh up         # 构建并启动
\`\`\`

访问 http://<服务器IP>:8900
默认账号: admin/admin (工程师) · operator/operator (运维)

## 升级(保留数据)

\`\`\`bash
cd 旧版目录
./install.sh backup                          # 先备份
tar -xzf straitbot-fms-v${VERSION}-*.tar.gz --strip-components=1 -C .
./install.sh rebuild                         # 重建
\`\`\`

完整更新历史见 CHANGELOG.md。
EOF
G "  ✓ RELEASE_NOTES.md 已生成"

# ---- 4. 统计 + 打包 ----
B "[3/4] 统计打包内容..."
FILE_COUNT=$(find "$STAGE" -type f | wc -l | tr -d ' ')
SIZE=$(du -sh "$STAGE" | cut -f1)
echo "  文件数: $FILE_COUNT"
echo "  体积:   $SIZE"
echo ""
# 列出关键文件确认
echo "  关键文件:"
for f in install.sh pack.sh docker-compose.yml VERSION README.md CHANGELOG.md RELEASE_NOTES.md \
         backend/Dockerfile backend/requirements.txt backend/.env.example \
         frontend/Dockerfile frontend/nginx.conf; do
  if [ -f "$STAGE/$f" ]; then
    echo "    ✓ $f"
  else
    R "    ✗ $f 缺失!"
  fi
done
if [ "$OFFLINE" = "true" ]; then
  if [ -f "$STAGE/images/fms_final.tar" ]; then
    echo "    ✓ images/fms_final.tar ($(du -h "$STAGE/images/fms_final.tar" | cut -f1)) [离线模式]"
  else
    R "    ✗ images/fms_final.tar 缺失! [离线模式必需]"
  fi
fi
echo ""
echo "  排除确认(这些不应存在):"
for f in backend/data/fms.db backend/.env frontend/node_modules; do
  if [ -e "$STAGE/$f" ]; then
    R "    ✗ $f 仍在(应被排除)"
  else
    echo "    ✓ $f 已排除"
  fi
done
echo ""

B "[4/4] 压缩打包..."
cd /tmp
tar -czf "$DIST_DIR/${PKG_NAME}.tar.gz" "${PKG_NAME}"
rm -rf "$STAGE"

FINAL="$DIST_DIR/${PKG_NAME}.tar.gz"
FINAL_SIZE=$(du -h "$FINAL" | cut -f1)

echo ""
G "╔══════════════════════════════════════════════════╗"
G "║  ✅ 打包完成!"
G "╠══════════════════════════════════════════════════╣"
G "║  版本: v$VERSION"
if [ "$OFFLINE" = "true" ]; then
G "║  模式: 离线(含镜像, 部署机零外网)"
else
G "║  模式: 在线(部署机需能访问国内镜像源)"
fi
G "║  文件: $FINAL"
G "║  体积: $FINAL_SIZE"
G "╠══════════════════════════════════════════════════╣"
G "║  部署方法:"
G "║    1. 拷贝 $PKG_NAME.tar.gz 到目标机器"
G "║    2. tar -xzf $PKG_NAME.tar.gz"
G "║    3. cd $PKG_NAME"
G "║    4. ./install.sh        (首次, 生成 .env)"
G "║    5. vi backend/.env     (改密码)"
G "║    6. ./install.sh up     (启动)"
if [ "$OFFLINE" = "true" ]; then
G "║"
G "║  注: 离线模式会自动加载 images/fms_final.tar,"
G "║      不需要外网, 启动秒级"
fi
G "╚══════════════════════════════════════════════════╝"

# ---- 询问是否上传到自动部署服务器 ----
DEPLOY_HOST="hxzh@192.168.8.91"
DEPLOY_PATH="/home/hxzh/autodeploy/public/fms"
DEPLOY_PASS="HXZH2019"

echo ""
if [ -t 0 ]; then  # 终端交互模式才询问
  B "[上传] 是否上传到自动部署服务器?"
  echo "    目标: $DEPLOY_HOST:$DEPLOY_PATH"
  read -r -p "    上传? [Y/n] " ANSWER
  ANSWER="${ANSWER:-Y}"
else
  ANSWER="N"
  Y "(非交互模式, 跳过上传。如需上传, 在终端运行 ./pack.sh)"
fi

if [[ "$ANSWER" =~ ^[Yy]$ ]]; then
  echo ""
  B "开始上传 $FINAL 到 $DEPLOY_HOST:$DEPLOY_PATH ..."

  # 方法 1: 用 sshpass(若已装)
  if command -v sshpass >/dev/null 2>&1; then
    if sshpass -p "$DEPLOY_PASS" scp -o StrictHostKeyChecking=no \
        "$FINAL" "$DEPLOY_HOST:$DEPLOY_PATH/" 2>&1; then
      G "  ✓ 已上传 (sshpass)"
    else
      R "  ✗ sshpass 上传失败, 尝试其他方式"
      _try_manual_upload
    fi
  else
    _try_manual_upload
  fi
fi

# 手动上传兜底(用 expect 模拟, 或提示密码让用户输)
_try_manual_upload() {
  # 方法 2: 用 expect(若已装)
  if command -v expect >/dev/null 2>&1; then
    expect <<EOF
set timeout 120
spawn scp -o StrictHostKeyChecking=no "$FINAL" "$DEPLOY_HOST:$DEPLOY_PATH/"
expect {
  "*password:*" { send "$DEPLOY_PASS\r"; exp_continue }
  "*yes/no*" { send "yes\r"; exp_continue }
  eof
}
catch wait result
exit [lindex \$result 3]
EOF
    if [ $? -eq 0 ]; then
      G "  ✓ 已上传 (expect)"
      return 0
    fi
  fi
  # 方法 3: 用 python + paramiko(Windows/Git Bash 下推荐)
  if command -v python >/dev/null 2>&1 && python -c "import paramiko" 2>/dev/null; then
    Y "  尝试用 python+paramiko 上传..."
    if FMS_DEPLOY_HOST="$DEPLOY_HOST" FMS_DEPLOY_PATH="$DEPLOY_PATH" FMS_DEPLOY_PASS="$DEPLOY_PASS" \
       python "$ROOT/upload.py" "$FINAL"; then
      G "  ✓ 已上传 (python+paramiko)"
      return 0
    fi
  elif command -v python3 >/dev/null 2>&1 && python3 -c "import paramiko" 2>/dev/null; then
    Y "  尝试用 python3+paramiko 上传..."
    if FMS_DEPLOY_HOST="$DEPLOY_HOST" FMS_DEPLOY_PATH="$DEPLOY_PATH" FMS_DEPLOY_PASS="$DEPLOY_PASS" \
       python3 "$ROOT/upload.py" "$FINAL"; then
      G "  ✓ 已上传 (python3+paramiko)"
      return 0
    fi
  fi
  # 方法 4: 直接 scp, 让用户手动输密码
  Y "  自动上传工具未就绪, 将直接调用 scp, 请手动输入密码:"
  echo "    密码: $DEPLOY_PASS"
  if scp -o StrictHostKeyChecking=no "$FINAL" "$DEPLOY_HOST:$DEPLOY_PATH/"; then
    G "  ✓ 已上传 (手动密码)"
  else
    R "  ✗ 上传失败"
    Y "  可手动执行:"
    Y "    python upload.py $FINAL"
    Y "  或: scp $FINAL $DEPLOY_HOST:$DEPLOY_PATH/  (密码 $DEPLOY_PASS)"
  fi
}
