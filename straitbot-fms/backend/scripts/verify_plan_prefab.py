"""巡检计划编排（/api/plan-prefab）端到端验证 + 航点树未回归（临时文件，跑完即删）。

覆盖：
- 两棵树的 `node-types` **互不串门**（计划树里不该出现 WaypointNode，反之亦然）；
- 新建 -> 存一棵含全部 5 种节点的树 -> 回读逐字段核对 -> 删除；
- 校验/防护：缺 root(422)、未知类型(400)、字段类型错(400)、
  「覆盖写不建文件」(404)、路径穿越(400)；
- 顺带把 `/api/waypoint-prefab` 的建/存/读/删再走一遍——通用路由工厂是从那边
  抽出来的，这条路径必须仍然通（抽取时最容易漏改的就是它）。

用法（需后端已在 127.0.0.1:8000 运行）：
    cd backend && PYTHONPATH=. python scripts/verify_plan_prefab.py
"""
from __future__ import annotations

import datetime as dt
import json
import urllib.error
import urllib.parse
import urllib.request

import jwt

from app.config import settings

HOST = "http://127.0.0.1:8000"
PLAN = HOST + "/api/plan-prefab"
WP = HOST + "/api/waypoint-prefab"
PLAN_REL = "_verify/__tmp_计划验证.prefab.json"
WP_REL = "_verify/__tmp_航点验证.prefab.json"

PLAN_TYPES = {"InspectionPlanNode", "PlanGroupNode", "WaypointSelectNode",
              "PointSelectNode", "DailyScheduleNode"}

SPEC = {
    "name": "验证用计划",
    "description": "",
    "root": {
        "type": "InspectionPlanNode",
        "properties": {"name": "日常巡检", "enabled": True, "description": "",
                       "plan_id": "P-001", "robot_name": "1号挂轨机器人",
                       "priority": 5, "note": ""},
        "children": [
            {"type": "WaypointSelectNode",
             "properties": {"name": "全部航点", "enabled": True, "description": "",
                            "source": "floor1.prefab.json", "include_all": True,
                            "waypoint_ids": [], "note": ""}},
            {"type": "PointSelectNode",
             "properties": {"name": "重点测点", "enabled": True, "description": "",
                            "include_all": False, "point_ids": ["P-0001", "P-0002"],
                            "note": ""}},
            {"type": "PlanGroupNode",
             "properties": {"name": "调度", "enabled": True, "description": ""},
             "children": [
                 {"type": "DailyScheduleNode",
                  "properties": {"name": "白班", "enabled": True, "description": "",
                                 "start_time": "08:00", "end_time": "18:00",
                                 "interval_minutes": 60, "note": ""}}]},
        ],
    },
}


def token() -> str:
    exp = dt.datetime.now(dt.timezone.utc) + dt.timedelta(minutes=5)
    return jwt.encode({"sub": "admin", "role": "engineer", "uid": 1, "exp": exp},
                      settings.jwt_secret, algorithm="HS256")


def call(method: str, url: str, body=None):
    data = json.dumps(body).encode() if body is not None else None
    req = urllib.request.Request(
        url, data=data, method=method,
        headers={"Authorization": f"Bearer {token()}", "Content-Type": "application/json"})
    try:
        with urllib.request.urlopen(req) as r:
            return r.status, json.loads(r.read().decode() or "{}")
    except urllib.error.HTTPError as e:
        return e.code, json.loads(e.read().decode() or "{}")


fails: list[str] = []
count = 0


def check(label: str, cond: bool, extra: str = "") -> None:
    global count
    count += 1
    if cond:
        print(f"  ✓ {label}")
    else:
        print(f"  ✗ {label} {extra}")
        fails.append(label)


def expect_status(label: str, method: str, url: str, body, want: int):
    code, _ = call(method, url, body)
    check(f"{label}（期望 {want}）", code == want, f"实际 {code}")


def main() -> int:
    print("1) 两棵树的类型目录互不串门")
    _, plan_nt = call("GET", PLAN + "/node-types")
    _, wp_nt = call("GET", WP + "/node-types")
    check("计划树恰好 5 种类型", set(plan_nt) == PLAN_TYPES, str(sorted(plan_nt)))
    check("计划树里没有航点系类型", "WaypointNode" not in plan_nt and "GroupNode" not in plan_nt)
    check("航点树里没有计划系类型", "InspectionPlanNode" not in wp_nt)
    check("航点树仍暴露航点类型", "WaypointNode" in wp_nt)

    print("2) 计划树：新建 -> 保存 -> 回读")
    call("DELETE", PLAN + "/files", {"rel_path": PLAN_REL})       # 清掉可能的上次残留
    code, _ = call("POST", PLAN + "/files", {"rel_path": PLAN_REL})
    check("新建文件", code == 200, f"实际 {code}")
    _, got = call("GET", PLAN + "/tree?rel_path=" + urllib.parse.quote(PLAN_REL))
    check("新建的根是巡检计划节点",
          got["spec"]["root"]["type"] == "InspectionPlanNode",
          str(got["spec"]["root"].get("type")))

    code, _ = call("POST", PLAN + "/tree", {"rel_path": PLAN_REL, "spec": SPEC})
    check("保存成功", code == 200, f"实际 {code}")
    _, back = call("GET", PLAN + "/tree?rel_path=" + urllib.parse.quote(PLAN_REL))
    check("回读与写入完全一致", back["spec"] == SPEC)
    props = back["spec"]["root"]["properties"]
    check("计划元信息保留", props["plan_id"] == "P-001" and props["priority"] == 5)
    sched = back["spec"]["root"]["children"][2]["children"][0]["properties"]
    check("每日调度字段保留",
          sched["start_time"] == "08:00" and sched["end_time"] == "18:00"
          and sched["interval_minutes"] == 60)
    check("航点指定保留引用",
          back["spec"]["root"]["children"][0]["properties"]["source"] == "floor1.prefab.json")
    check("测点指定保留 id 列表",
          back["spec"]["root"]["children"][1]["properties"]["point_ids"] == ["P-0001", "P-0002"])

    _, trees = call("GET", PLAN + "/trees")
    hit = [t for t in trees["trees"] if t["rel_path"] == PLAN_REL]
    check("列表里能看到它且带根类型",
          bool(hit) and hit[0]["root"]["type"] == "InspectionPlanNode")

    print("3) 校验与防护")
    expect_status("缺 root 报 422", "POST", PLAN + "/tree",
                  {"rel_path": PLAN_REL, "spec": {"name": "x"}}, 422)
    expect_status("未知节点类型报 400", "POST", PLAN + "/tree",
                  {"rel_path": PLAN_REL, "spec": {"root": {"type": "NopeNode", "properties": {}}}}, 400)
    expect_status("字段类型错报 400", "POST", PLAN + "/tree",
                  {"rel_path": PLAN_REL,
                   "spec": {"root": {"type": "DailyScheduleNode",
                                     "properties": {"interval_minutes": "abc"}}}}, 400)
    expect_status("覆盖写不创建文件（404）", "POST", PLAN + "/tree",
                  {"rel_path": "_verify/__nope.prefab.json", "spec": SPEC}, 404)
    expect_status("路径穿越报 400", "POST", PLAN + "/files",
                  {"rel_path": "../evil.prefab.json"}, 400)

    print("4) 航点树未回归（通用路由工厂是从这边抽出来的）")
    call("DELETE", WP + "/files", {"rel_path": WP_REL})
    code, _ = call("POST", WP + "/files", {"rel_path": WP_REL})
    check("新建航点树文件", code == 200, f"实际 {code}")
    _, w = call("GET", WP + "/tree?rel_path=" + urllib.parse.quote(WP_REL))
    check("航点树根仍是分组", w["spec"]["root"]["type"] == "GroupNode")
    w["spec"]["root"]["children"].append(
        {"type": "WaypointNode", "properties": {"name": "航点 1", "wp_id": "A-1", "x": 1.5}})
    code, _ = call("POST", WP + "/tree", {"rel_path": WP_REL, "spec": w["spec"]})
    check("保存航点树", code == 200, f"实际 {code}")
    _, w2 = call("GET", WP + "/tree?rel_path=" + urllib.parse.quote(WP_REL))
    check("回读航点字段",
          w2["spec"]["root"]["children"][0]["properties"]["wp_id"] == "A-1")
    code, _ = call("GET", WP + "/algorithms")
    check("航点树专有接口（算法目录）仍在", code == 200, f"实际 {code}")

    print("5) 清理")
    call("DELETE", PLAN + "/files", {"rel_path": PLAN_REL})
    call("DELETE", WP + "/files", {"rel_path": WP_REL})
    code, _ = call("GET", PLAN + "/tree?rel_path=" + urllib.parse.quote(PLAN_REL))
    check("临时计划文件已删除", code == 404, f"实际 {code}")

    print()
    if fails:
        print(f"{count - len(fails)}/{count} 项通过，失败 {len(fails)} 项：")
        for f in fails:
            print("  - " + f)
        return 1
    print(f"全部通过 ✓（{count} 项）")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
