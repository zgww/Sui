"""WiFi AP 热点配置: 通过 SSH 让机器人开启/关闭 WiFi 热点。

用途: 部署到机器人上时, 手机连热点后访问机器人 IP 使用 FMS。

POST /api/hotspot/{rid}/enable   开启热点
POST /api/hotspot/{rid}/disable  关闭热点
GET  /api/hotspot/{rid}/status   查看热点状态
"""
from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel
from sqlalchemy.orm import Session
from typing import Optional

from ..database import get_db
from ..models import Robot
from ..schemas import Ok
from ..auth import engineer_only
from ..services import ssh_client

router = APIRouter(prefix="/api/hotspot", tags=["hotspot"])


class HotspotConfig(BaseModel):
    ssid: str = "Straitbot-FMS"
    password: str = "12345678"   # WPA 密码至少 8 位
    channel: int = 6
    # 热点 IP(手机连上后访问这个 IP:8900)
    gateway: str = "192.168.4.1"


def _robot(rid: int, db: Session) -> Robot:
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    return r


def _find_wifi_iface(ip, port, user, pwd) -> str:
    """探测无线网卡名(wlan0/wlx...)。"""
    out, _, _ = ssh_client.run(
        ip,
        "iw dev 2>/dev/null | grep Interface | awk '{print $2}' | head -1 || "
        "ip link | grep -oP 'wlan\\d+|wlx[a-f0-9]+' | head -1",
        port=port, user=user, pwd=pwd, timeout=10)
    iface = out.strip()
    return iface if iface else "wlan0"


@router.post("/{rid}/enable")
def enable_hotspot(rid: int, body: HotspotConfig,
                   db: Session = Depends(get_db), user=Depends(engineer_only)):
    """开启 WiFi 热点(用 nmcli 或 hostapd)。"""
    r = _robot(rid, db)
    # 探测无线网卡
    iface = _find_wifi_iface(r.ip, r.ssh_port, r.ssh_user, r.ssh_pass)

    # 方案1: NetworkManager (Ubuntu 18.04+ 自带)
    script = f"""set -e
# 检查 nmcli 是否可用
if command -v nmcli >/dev/null 2>&1; then
  echo "使用 NetworkManager 创建热点"
  # 删除旧的同名连接(忽略错误)
  nmcli connection delete "{body.ssid}" 2>/dev/null || true
  # 创建热点
  nmcli device wifi hotspot ifname {iface} con-name "{body.ssid}" \\
    ssid "{body.ssid}" password "{body.password}" channel {body.channel} \\
    band bg
  # 设置静态 IP
  nmcli connection modify "{body.ssid}" ipv4.addresses {body.gateway}/24
  nmcli connection modify "{body.ssid}" ipv4.method shared
  nmcli connection up "{body.ssid}"
  echo "HOTSPOT_OK_NM"
else
  echo "nmcli 不可用, 尝试 hostapd"
  if ! command -v hostapd >/dev/null 2>&1; then
    apt-get install -y hostapd dnsmasq 2>/dev/null || true
  fi
  # 配置静态 IP
  ip addr add {body.gateway}/24 dev {iface} 2>/dev/null || true
  ip link set {iface} up 2>/dev/null || true
  # dnsmasq (DHCP)
  cat > /etc/dnsmasq.d/hotspot.conf <<EOF
interface={iface}
dhcp-range=192.168.4.10,192.168.4.100,255.255.255.0,12h
EOF
  systemctl restart dnsmasq 2>/dev/null || dnsmasq --conf-file=/etc/dnsmasq.d/hotspot.conf &
  # hostapd
  cat > /etc/hostapd/hostapd.conf <<EOF
interface={iface}
driver=nl80211
ssid={body.ssid}
hw_mode=g
channel={body.channel}
wmm_enabled=0
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase={body.password}
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
EOF
  hostapd /etc/hostapd/hostapd.conf &
  echo "HOTSPOT_OK_HOSTAPD"
fi
# 显示结果
echo "=== 热点信息 ==="
echo "SSID: {body.ssid}"
echo "密码: {body.password}"
echo "IP: {body.gateway}:8900"
echo "网卡: {iface}"
ip addr show {iface} 2>/dev/null | grep "inet " || true
"""
    try:
        out, err, rc = ssh_client.run_as_script(
            r.ip, script, r.ssh_port, r.ssh_user, r.ssh_pass, timeout=30)
        ok = "HOTSPOT_OK" in out
        return Ok(ok=ok, msg=(out.strip()[-500:] if ok else f"失败:\n{out[-300:]}\n{err[-200:]}"))
    except Exception as e:
        return Ok(ok=False, msg=str(e))


@router.post("/{rid}/disable")
def disable_hotspot(rid: int, body: HotspotConfig = None,
                    db: Session = Depends(get_db), user=Depends(engineer_only)):
    """关闭热点。"""
    r = _robot(rid, db)
    ssid = body.ssid if body else "Straitbot-FMS"
    script = f"""nmcli connection delete "{ssid}" 2>/dev/null && echo DELETED || echo NOT_FOUND
pkill hostapd 2>/dev/null || true
pkill dnsmasq 2>/dev/null || true
echo DONE
"""
    try:
        out, _, rc = ssh_client.run_as_script(
            r.ip, script, r.ssh_port, r.ssh_user, r.ssh_pass, timeout=15)
        return Ok(ok=True, msg=out.strip()[-300:])
    except Exception as e:
        return Ok(ok=False, msg=str(e))


@router.get("/{rid}/status")
def hotspot_status(rid: int, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """查看热点状态和无线网卡信息。"""
    r = _robot(rid, db)
    script = """echo "=== 无线网卡 ==="
iw dev 2>/dev/null || ip link | grep -E "wlan|wlx"
echo "=== NM 连接 ==="
nmcli connection show 2>/dev/null | head -10 || echo "无 nmcli"
echo "=== hostapd ==="
pgrep hostapd >/dev/null && echo "hostapd 运行中" || echo "hostapd 未运行"
echo "=== IP ==="
ip addr show | grep "inet " | grep -v "127.0.0.1"
"""
    try:
        out, _, _ = ssh_client.run_as_script(
            r.ip, script, r.ssh_port, r.ssh_user, r.ssh_pass, timeout=10)
        return {"status": out.strip()}
    except Exception as e:
        return {"status": f"查询失败: {e}"}
