"""充电桩 / RFID 卡端到端落盘验证（临时文件，跑完即删）。

走的是前端「保存」按钮的同一条链路：POST /api/waypoint-prefab/tree
（内部 registry.build 校验）-> 写盘 -> GET /tree 回读。
用法：python scripts/verify_facility_nodes.py
"""
from __future__ import annotations

import datetime as dt
import json
import urllib.error
import urllib.request

import jwt

from app.config import settings

BASE = "http://127.0.0.1:8000/api/waypoint-prefab"
REL = "floor1/__tmp_设施验证.prefab.json"


def token() -> str:
    exp = dt.datetime.now(dt.timezone.utc) + dt.timedelta(minutes=5)
    return jwt.encode(
        {"sub": "admin", "role": "engineer", "uid": 1, "exp": exp},
        settings.jwt_secret, algorithm="HS256",
    )


def call(method: str, path: str, body=None, tok=None):
    data = json.dumps(body).encode() if body is not None else None
    req = urllib.request.Request(
        BASE + path, data=data, method=method,
        headers={"Authorization": f"Bearer {tok or token()}",
                 "Content-Type": "application/json"},
    )
    try:
        with urllib.request.urlopen(req) as r:
            return r.status, json.loads(r.read().decode() or "{}")
    except urllib.error.HTTPError as e:
        return e.code, json.loads(e.read().decode() or "{}")


SPEC = {
    "root": {
        "type": "GroupNode",
        "properties": {"name": "验证用"},
        "children": [
            {"type": "WaypointNode", "properties": {"name": "航点 1", "x": 0.0}},
            {"type": "WaypointNode", "properties": {"name": "航点 2", "x": 55.0}},
            {"type": "ChargingPileNode",
             "properties": {"name": "充电桩 1", "x": 12.5, "pile_id": "CP-01",
                            "rfid": 7, "charge_minutes": 90}},
            {"type": "RfidCardNode",
             "properties": {"name": "RFID 卡 1", "x": 30.0, "card_id": 1, "range_mm": 200}},
        ],
    }
}

ok = True


def check(name: str, cond: bool, extra: str = "") -> None:
    global ok
    if cond:
        print(f"  ✓ {name}")
    else:
        ok = False
        print(f"  ✗ {name} {extra}")


print("1) 创建临时文件")
st, _ = call("POST", "/files", {"rel_path": REL})
check("创建成功", st == 200, f"status={st}")

print("2) 保存（registry.build 校验 + 写盘）")
st, res = call("POST", "/tree", {"rel_path": REL, "spec": SPEC})
check("保存成功", st == 200 and res.get("ok"), f"status={st} {res}")

print("3) 回读并核对")
st, res = call("GET", f"/tree?rel_path={urllib.request.quote(REL)}")
check("读取成功", st == 200, f"status={st}")
types = [c.get("type") for c in res.get("spec", {}).get("root", {}).get("children", [])]
check("类型齐全", types == ["WaypointNode", "WaypointNode", "ChargingPileNode", "RfidCardNode"],
      str(types))
if len(types) == 4:
    pile = res["spec"]["root"]["children"][2]["properties"]
    rfid = res["spec"]["root"]["children"][3]["properties"]
    check("充电桩字段保留", pile.get("pile_id") == "CP-01" and pile.get("x") == 12.5
          and pile.get("rfid") == 7, json.dumps(pile, ensure_ascii=False))
    check("RFID 字段保留", rfid.get("card_id") == 1 and rfid.get("x") == 30.0
          and rfid.get("range_mm") == 200, json.dumps(rfid, ensure_ascii=False))

print("4) 清理临时文件")
st, _ = call("DELETE", "/files", {"rel_path": REL})
check("删除成功", st == 200, f"status={st}")

print("\n全部通过 ✓" if ok else "\n有失败项 ✗")
raise SystemExit(0 if ok else 1)
