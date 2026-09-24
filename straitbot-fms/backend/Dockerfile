FROM python:3.11-slim

# 换阿里云 debian 源(兼容 trixie 新格式 + bookworm 旧格式), 解决内网访问官方源超时
RUN set -x; \
    if [ -f /etc/apt/sources.list.d/debian.sources ]; then \
      sed -i 's|deb.debian.org|mirrors.aliyun.com|g; s|security.debian.org|mirrors.aliyun.com|g' /etc/apt/sources.list.d/debian.sources; \
    fi; \
    if [ -f /etc/apt/sources.list ]; then \
      sed -i 's|deb.debian.org|mirrors.aliyun.com|g; s|security.debian.org|mirrors.aliyun.com|g' /etc/apt/sources.list; \
    fi; \
    true

# 系统依赖(paramiko 需要 libffi/openssl, bcrypt/gcc 用于编译; curl 用于健康检查; unzip 备用)
RUN apt-get update && apt-get install -y --no-install-recommends \
        gcc g++ libffi-dev libssl-dev curl unzip \
        libglib2.0-0 libgomp1 ffmpeg \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# 先装依赖(利用层缓存) - 用清华 PyPI 镜像加速
COPY requirements.txt .
RUN pip install --no-cache-dir -i https://pypi.tuna.tsinghua.edu.cn/simple \
    --trusted-host pypi.tuna.tsinghua.edu.cn \
    -r requirements.txt

# 业务代码
COPY app ./app
COPY VERSION /app/VERSION

# 内置默认数据(物模型/prompts, 启动时若 data 卷缺失则拷过去, 避免重建丢失)
COPY data/thing_model.json data/prompts.json /app/defaults/

# 数据目录(挂载卷)
RUN mkdir -p /app/data/logs /app/data/packages
ENV PYTHONUNBUFFERED=1

EXPOSE 8000

HEALTHCHECK --interval=30s --timeout=5s --start-period=20s --retries=3 \
    CMD curl -fs http://127.0.0.1:8000/api/health || exit 1

CMD ["uvicorn", "app.main:app", "--host", "0.0.0.0", "--port", "8000"]
