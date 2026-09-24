#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""上传安装包到自动部署服务器(Windows/Git Bash 下 sshpass/expect 不可用时的兜底)。

用法:
    python upload.py <本地文件路径>

配置(写死, 也可通过环境变量覆盖):
    FMS_DEPLOY_HOST  默认 hxzh@192.168.8.91
    FMS_DEPLOY_PATH  默认 /home/hxzh/autodeploy/public/fms
    FMS_DEPLOY_PASS  默认 HXZH2019
"""
import os
import sys
import posixpath
import paramiko

HOST = os.environ.get("FMS_DEPLOY_HOST", "hxzh@192.168.8.91")
PATH = os.environ.get("FMS_DEPLOY_PATH", "/home/hxzh/autodeploy/public/fms")
PASS = os.environ.get("FMS_DEPLOY_PASS", "HXZH2019")


def main():
    if len(sys.argv) < 2:
        print("用法: python upload.py <本地文件路径>")
        sys.exit(1)

    local = sys.argv[1]
    if not os.path.isfile(local):
        print(f"✗ 文件不存在: {local}")
        sys.exit(1)

    # 解析 host(user@ip)
    if "@" in HOST:
        user, ip = HOST.split("@", 1)
    else:
        user, ip = "hxzh", HOST

    name = os.path.basename(local)
    remote = posixpath.join(PATH, name)
    size_mb = os.path.getsize(local) / 1048576
    print(f"[上传] {name} ({size_mb:.1f}MB) -> {HOST}:{PATH}")
    print(f"       连接 {ip} ...")

    c = paramiko.SSHClient()
    c.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    try:
        c.connect(ip, username=user, password=PASS, timeout=15,
                  look_for_keys=False, allow_agent=False)
    except Exception as e:
        print(f"✗ 连接失败: {e}")
        sys.exit(1)

    # 确保远程目录存在
    try:
        c.exec_command(f"mkdir -p '{PATH}'")[1].channel.recv_exit_status()
    except Exception:
        pass

    sftp = c.open_sftp()
    try:
        # 带进度
        last = [0]
        def cb(sent, total):
            pct = sent * 100 // total if total else 0
            if pct - last[0] >= 10 or sent == total:
                last[0] = pct
                print(f"\r       {pct}% ({sent//1024}KB/{total//1024}KB)", end="", flush=True)

        sftp.put(local, remote, callback=cb)
        print()
    finally:
        sftp.close()
        c.close()

    print(f"✓ 已上传: {HOST}:{remote}")
    print(f"  下载地址(若开了 http): http://{ip}/fms/{name}")


if __name__ == "__main__":
    main()
