"""机器人自动扫描: 扫指定网段的 6002(API) 端口, 对在线的探测 robot_id。

- 并发 socket 探测(线程池), 快速扫一个 /24 约几秒
- 对开放 6002 的 IP, 调 cmd=4 取 robot_id
"""
from __future__ import annotations
import socket
import ipaddress
import platform
import subprocess
from concurrent.futures import ThreadPoolExecutor, as_completed
from typing import List, Dict
import httpx

from ..config import settings


def detect_local_networks() -> List[Dict]:
    """探测本机所有 IPv4 网段(排除 docker/loopback)。

    返回 [{"interface": "eno1", "ip": "192.168.13.2", "cidr": "192.168.13.0/24"}]
    """
    results = []
    try:
        # 跨平台: 用 socket 取本机 IP, 推断 /24
        hostname = socket.gethostname()
        try:
            local_ip = socket.gethostbyname(hostname)
        except Exception:
            local_ip = None

        # Linux: 用 ip 命令精确取
        if platform.system() == "Linux":
            try:
                out = subprocess.run(["ip", "-4", "addr"], capture_output=True,
                                     text=True, timeout=5).stdout
                for line in out.splitlines():
                    line = line.strip()
                    if not line.startswith("inet "):
                        continue
                    # 行如: inet 192.168.13.2/24 brd ... scope global eno1
                    parts = line.split()
                    if len(parts) < 6:
                        continue
                    addr_full = parts[1]   # 192.168.13.2/24
                    scope_idx = parts.index("scope") if "scope" in parts else -1
                    iface = parts[scope_idx + 2] if scope_idx > 0 and scope_idx + 2 < len(parts) else ""
                    # 排除 docker/bridge/loopback
                    if iface.startswith(("docker", "br-", "veth", "lo")):
                        continue
                    ip_mask = addr_full.split("/")
                    if len(ip_mask) != 2:
                        continue
                    ip, mask = ip_mask
                    if ip.startswith("127."):
                        continue
                    if ip.startswith("172.") and (16 <= int(ip.split(".")[1]) <= 31):
                        continue  # docker 默认网段
                    # 算 CIDR 网段
                    try:
                        net = ipaddress.ip_network(f"{ip}/{mask}", strict=False)
                        results.append({
                            "interface": iface,
                            "ip": ip,
                            "cidr": str(net),
                        })
                    except ValueError:
                        continue
            except (FileNotFoundError, subprocess.TimeoutExpired):
                pass

        # 兜底: socket 取到的 IP, 推断 /24; 排除 docker 网段
        if not results and local_ip and not local_ip.startswith("127."):
            parts = local_ip.split(".")
            if len(parts) == 4 and not (parts[0] == "172" and 16 <= int(parts[1]) <= 31):
                results.append({
                    "interface": "default",
                    "ip": local_ip,
                    "cidr": f"{parts[0]}.{parts[1]}.{parts[2]}.0/24",
                })
    except Exception:
        pass

    # 优先排序: 非 docker 网段排前面, default 网段选第一个非 docker 的
    def _score(n: str) -> int:
        if n.startswith("172.") and 16 <= int(n.split(".")[1]) <= 31:
            return 2   # docker 最低优先
        return 0
    results.sort(key=lambda x: _score(x["cidr"]))
    return results


def _port_open(ip: str, port: int, timeout: float = 1.0) -> bool:
    try:
        with socket.create_connection((ip, port), timeout=timeout):
            return True
    except (OSError, socket.timeout):
        return False


def _probe_api(ip: str, port: int, robot_id: int = 1, timeout: float = 3.0) -> Dict:
    """调 cmd=4 取机器人信息。返回 dict 或 None。"""
    url = f"http://{ip}:{port}/"
    try:
        with httpx.Client(timeout=timeout) as cli:
            # cmd=4 配置(含 robot_id, product, version)
            r = cli.post(url, json={"cmd": 4},
                         headers={"X-ROBOT_ID": str(robot_id), "Content-Type": "application/json"})
            r.raise_for_status()
            obj = r.json()
            if obj.get("code") != 0:
                return None
            data = obj.get("data", {}) or {}
            ver = data.get("version", {}) or {}
            return {
                "robot_id": data.get("robot_id"),
                "product": data.get("product"),
                "sn": data.get("sn", ""),
                "application": ver.get("application", ""),
                "firmware": ver.get("firmware", ""),
                "motion": ver.get("motion", ""),
                "sdk": ver.get("sdk", ""),
            }
    except Exception:
        return None


def scan_network(cidr: str, api_port: int = 6002, timeout: float = 1.0,
                 max_workers: int = 80) -> List[Dict]:
    """扫描一个 CIDR 网段(如 192.168.6.0/24)。

    返回所有 6002 端口开放且 API 可达的 IP 列表:
      [{ip, port, robot_id, product, sn, application, firmware, ...}]
    """
    try:
        net = ipaddress.ip_network(cidr, strict=False)
    except ValueError as e:
        raise ValueError(f"无效的网段: {cidr} ({e})")

    hosts = [str(ip) for ip in net.hosts()]
    # 大网段(/16)会很多, 截断避免扫太久
    if len(hosts) > 1024:
        hosts = hosts[:1024]

    found_ips: List[str] = []
    with ThreadPoolExecutor(max_workers=max_workers) as ex:
        futs = {ex.submit(_port_open, ip, api_port, timeout): ip for ip in hosts}
        for fut in as_completed(futs):
            ip = futs[fut]
            try:
                if fut.result():
                    found_ips.append(ip)
            except Exception:
                continue

    # 对端口开放的 IP 探测 API 信息
    results: List[Dict] = []
    with ThreadPoolExecutor(max_workers=20) as ex:
        futs = {ex.submit(_probe_api, ip, api_port): ip for ip in found_ips}
        for fut in as_completed(futs):
            ip = futs[fut]
            try:
                info = fut.result()
                if info:
                    info["ip"] = ip
                    info["port"] = api_port
                    results.append(info)
            except Exception:
                continue

    results.sort(key=lambda x: x["ip"])
    return results
