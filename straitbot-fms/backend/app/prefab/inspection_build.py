"""航点树 -> **巡检任务 JSON** 的组装（供「巡检计划调度」下发用）。

与前端 `frontend/src/utils/inspectionBuild.ts` 是同一件事的两端：那边的产物给人
下载/调试，这边的产物直接喂给 `Robot.接收巡检任务`。字段命名刻意与
`app/prefab/waypoint_import.py`（反向：巡检任务 -> 航点树）一一对应，
也与 `tests/test_inspection.json` 同构：

    [ {floor, id, name, plan, substationMapsId, waypoint:[…]}, … ]
    waypoint: {id, index, pose:{point:{x,y,z}, theta}, action:[…]}
    action:   {id, type(1拍照/2测温/3录像), lift_height, duration, steer_point_name,
               ptz_param:{pan,tilt,zoom,focal_len,focus}, thermometry_points:[…]}

## "请求各个节点"

组装不是在这里硬拆字段，而是**问每个节点要**（`to_inspection_json`，定义在
`nodes/waypoint.py` 的各节点类上）：航点问它的动作点，动作点问它的测温点，
不认识的返回 None 自动跳过。这样新增一种动作/测点字段时，只改那个节点类，
这里不用动；而"谁进巡检任务"这件事由节点自己说了算。

## 楼层

按 `WaypointNode.floor`（航点**自己**的字段，不是分组名——分组改名就解不出来了，
见该类注释）分组，段内保持**树中顺序**（用户编排的执行顺序，不是按 x 排序），
`index` 在段内从 1 重新编号。

⚠️ 楼层判定必须与前端 `utils/inspectionBuild.ts::floorOfWaypoint` **完全一致**：
航点自己写了 `floor` 就用它，**没写**才从最近祖先分组名 `楼层N` 回解，都没有才
是 1。只认 `floor` 的话，在这个字段出现之前导入的老航点树会被整个当成 1 层下发。
"""
from __future__ import annotations

import json
import logging
import re
import uuid
from pathlib import Path
from typing import Any, Iterable, NamedTuple, Optional

from .plan_scheduler import normalize_detect_type

logger = logging.getLogger(__name__)

#: 巡检任务 id / plan / substationMapsId 的长度（与 tests/test_inspection.json 一致）
ID_HEX_LEN = 32

#: 楼层解不出来时的兜底（与前端 `inspectionBuild.ts::DEFAULT_FLOOR` 一致）
DEFAULT_FLOOR = 1

_FLOOR_RE = re.compile(r"楼层\s*(-?\d+)")


def hex_id(n: int = ID_HEX_LEN) -> str:
    """随机十六进制串（只要求"和别人不一样"，uuid4 足够）。"""
    return uuid.uuid4().hex[:n]


# ---------------------------------------------------------------- 楼层判定

def floor_from_name(name: Any, fallback: int = DEFAULT_FLOOR) -> int:
    """从分组名里回解楼层：导入时写的是 `楼层{floor}`（前端同名函数）。"""
    m = _FLOOR_RE.search(str(name or ""))
    if not m:
        return fallback
    try:
        return int(m.group(1))
    except ValueError:
        return fallback


def waypoint_floor(node: Any, ancestors: Iterable[str] = (),
                   fallback: int = DEFAULT_FLOOR) -> int:
    """航点的楼层：**航点自己写的 `floor` 说了算**，没写才去祖先分组名里解。

    `ancestors` 是**由外到内**的祖先分组名，找的时候由内向外（导入生成的是
    `任务 > 楼层N > 航点`，但用户可能再套一层 `区域A`，楼层在更外面）。

    ⚠️ "有没有写 `floor`" 必须跟 "`floor` 是多少" 分开判：默认值就是 1，
    光看 `node.floor` 分不出"没写"和"写了 1"。靠 pydantic 的 `model_fields_set`
    （只有 spec 里真给了这个键才会出现在里面）。老数据（在 `floor` 字段之前导入
    的树）全靠这条回解——不然整棵树的航点都会被当成 1 层下发。
    """
    if "floor" in getattr(node, "model_fields_set", ()) or ():
        try:
            return int(getattr(node, "floor", fallback))
        except (TypeError, ValueError):
            pass
    for nm in reversed(list(ancestors)):
        m = _FLOOR_RE.search(str(nm or ""))
        if m:
            try:
                return int(m.group(1))
            except ValueError:
                continue
    return fallback


# ---------------------------------------------------------------- 收集航点

class WaypointPick(NamedTuple):
    """一个被挑中的航点：树内路径 + 节点实例 + **它的楼层** + 抓拍图基路径。"""

    path: str
    node: Any
    floor: int
    image_base: str = ""   # 抓拍图 web 基路径（如 /data/prefabs/waypoint/floor1）


def waypoint_key(node: Any, path: str) -> str:
    """航点在计划里的引用 key：**优先 `wp_id`**，没有才退回树内路径。

    与前端 `utils/planSelect.ts::waypointKey` 同一条规则（计划里存的就是它）。
    """
    return str(getattr(node, "wp_id", "") or "").strip() or path


def collect_waypoints(root: Any, path: str = "root",
                      image_base: str = "") -> list[WaypointPick]:
    """先序遍历收集 `WaypointNode` 实例 → `[WaypointPick]`。

    停用的节点（含它的整棵子树）跳过：停用的航点不该被下发。
    顺序 = 树中顺序，也就是用户编排的执行顺序。
    `image_base` 是该 prefab 抓拍图的 web 基路径，原样记录到每个 WaypointPick。
    """
    out: list[WaypointPick] = []

    def walk(node: Any, p: str, ancestors: tuple[str, ...]) -> None:
        if node is None:
            return
        if getattr(node, "enabled", True) is False:
            return
        if node.type == "WaypointNode":
            out.append(WaypointPick(p, node, waypoint_floor(node, ancestors),
                                    image_base))
            return          # 航点下面只有动作点/测温点，不会再有航点
        name = str(getattr(node, "name", "") or "")
        nxt = ancestors + ((name,) if node.type == "GroupNode" else ("",))
        for i, c in enumerate(node.child_nodes):
            walk(c, f"{p}/children/{i}", nxt)

    walk(root, path, ())
    return out


def image_base_for_source(source: str) -> str:
    """prefab 文件相对 WAYPOINT_PREFAB_DIR 的路径 → 抓拍图 web 基路径。

    例：floor1/测试航线.prefab.json → /data/prefabs/waypoint/floor1
         根目录 xxx.prefab.json     → /data/prefabs/waypoint
    """
    src_dir = str(Path(str(source)).parent).replace("\\", "/")
    if src_dir in (".", "/", ""):
        return "/data/prefabs/waypoint"
    return f"/data/prefabs/waypoint/{src_dir}"


# ---------------------------------------------------------------- 组装

def build_inspection_payload(
    spec: dict,
    selected_keys: Optional[Iterable[str]] = None,
    *,
    name: str = "巡检计划下发",
    plan: str = "",
    substation_maps_id: str = "",
    point_ids: Optional[Iterable[str]] = None,
    inspection_id: str = "",
    fresh_ids: bool = False,
    source: str = "",
) -> dict:
    """航点树 spec -> 巡检任务载荷（`Robot.接收巡检任务` 的入参）。

    - `selected_keys`：计划的「航点指定」挑出来的 key（`wp_id` 或路径）；
      `None` = 这棵树全要；
    - `point_ids`：计划的「测点指定」挑出来的测点 id；`None` = 不过滤测温点；
    - `fresh_ids`：True 时连航点/动作/测点 id 也重新生成（默认沿用树里的 id，
      缺了才补——沿用 id 才能让机器人的断点/续跑对得上）；
    - `source`：该 prefab 相对 WAYPOINT_PREFAB_DIR 的路径，用于解析抓拍图。

    返回 `{payload, inspection_id, plan, floors, waypoint_count, action_count}`；
    `payload` 是楼层分段数组（同 `tests/test_inspection.json`）。
    """
    from .registry import build

    root = build((spec or {}).get("root") or {})
    image_base = image_base_for_source(source) if source else ""
    picked = collect_waypoints(root, image_base=image_base)

    if selected_keys is not None:
        want = {str(k) for k in selected_keys}
        picked = [pk for pk in picked if waypoint_key(pk.node, pk.path) in want]

    pt_filter = {str(x) for x in point_ids} if point_ids is not None else None

    # 按楼层分段（段内保持树中顺序）
    by_floor: dict[int, list[WaypointPick]] = {}
    for pk in picked:
        by_floor.setdefault(pk.floor, []).append(pk)
    floors = sorted(by_floor)

    task_id = inspection_id or hex_id()
    plan_id = plan or hex_id()
    maps_id = substation_maps_id or hex_id()

    payload: list[dict] = []
    action_count = 0
    for fl in floors:
        waypoints: list[dict] = []
        for idx, pk in enumerate(by_floor[fl], start=1):
            w = pk.node.to_inspection_json(index=idx, fresh_id=fresh_ids,
                                           point_ids=pt_filter,
                                           image_base=pk.image_base)
            # 测温动作（type=2）被测点过滤得一个点都不剩 -> 这个动作没有意义，丢掉
            w["action"] = [a for a in w["action"]
                           if not (a.get("type") == 2 and not a.get("thermometry_points"))]
            action_count += len(w["action"])
            waypoints.append(w)
        payload.append({
            "floor": fl,
            "id": task_id,
            "name": name,
            "plan": plan_id,
            "substationMapsId": maps_id,
            "waypoint": waypoints,
        })

    return {
        "payload": payload,
        "inspection_id": task_id,
        "plan": plan_id,
        "floors": floors,
        "waypoint_count": len(picked),
        "action_count": action_count,
    }


# ---------------------------------------------------------------- 从计划组装

def load_waypoint_spec(source: str, root_dir: Optional[Path] = None) -> dict:
    """计划的 `source`（航点树 rel_path）-> spec。

    `source` 是相对 `data/prefabs/waypoint` 的路径（与航点树编排页的 rel_path
    同一份）；给绝对路径或已带目录的也认。
    """
    if root_dir is None:
        from ..config import WAYPOINT_PREFAB_DIR
        root_dir = WAYPOINT_PREFAB_DIR
    p = Path(source)
    if not p.is_absolute():
        p = Path(root_dir) / source
    return json.loads(p.read_text(encoding="utf-8"))


def build_from_plan(job: dict, *, root_dir: Optional[Path] = None,
                    fresh_ids: bool = False) -> dict:
    """一条**计划**（`PlanJob.payload()` 的形状）-> 巡检任务载荷。

    计划里可能有多个「航点指定」（多棵树）：全部按树中顺序**合成一次巡检**
    （同一个 `id`/`plan`，按楼层分段）。「测点指定」里 `include_all=False` 的那些
    列出的是要的测点，用来过滤测温点；全是"全部测点"则不过滤。
    """
    specs = job.get("waypoints") or []
    if not specs:
        raise ValueError("这条计划没有「航点指定」，不知道要巡哪些航点")

    floors: dict[int, list[WaypointPick]] = {}

    for w in specs:
        src = str(w.get("source") or "").strip()
        if not src:
            logger.warning("[prefab] 计划的「航点指定」没有选航点树，跳过")
            continue
        spec = load_waypoint_spec(src, root_dir)
        from .registry import build
        image_base = image_base_for_source(src)
        picked = collect_waypoints(build(spec.get("root") or {}),
                                  image_base=image_base)
        # 按 waypoint_key 建索引，方便按计划指定的顺序查找
        picked_by_key = {waypoint_key(pk.node, pk.path): pk for pk in picked}
        # 一处"全部航点"只让它自己那棵树不过滤，**不会**连坐其它树的挑选结果
        include_all = w.get("include_all") is not False
        if include_all:
            # 全部航点：按树中顺序
            for pk in picked:
                floors.setdefault(pk.floor, []).append(pk)
        else:
            # 指定航点：**按计划里 waypoint_ids 的顺序**，从树里找
            want_ids = [str(x) for x in (w.get("waypoint_ids") or [])]
            missing = []
            for wid in want_ids:
                pk = picked_by_key.get(wid)
                if pk is None:
                    missing.append(wid)
                    continue
                floors.setdefault(pk.floor, []).append(pk)
            if missing:
                logger.warning("[prefab] 计划指定的 %d 个航点在树里找不到: %s",
                               len(missing), missing[:5])

    if not any(floors.values()):
        raise ValueError("这条计划挑出来的航点一个都不在航点树里（航点树被改过？）")

    # 测点指定：只有显式"不是全部测点"的那些才构成过滤条件
    pt_want: Optional[set[str]] = None
    for p in job.get("points") or []:
        if p.get("include_all") is False:
            ids = {str(x) for x in (p.get("point_ids") or [])}
            pt_want = ids if pt_want is None else (pt_want | ids)

    task_id = hex_id()
    plan_id = hex_id()
    maps_id = hex_id()
    name = str(job.get("plan_name") or "巡检计划下发")
    # 动作数据怎么作用到检测（fms 本机跑流程 / platform 上传平台）。
    # ⚠️ 必须**每个楼层段都带上**：`FloorTask.detect_type` 是按段解析的，
    # `InspectionTask.detect_type` 取首个分段的值。只写第一段的话，其余楼层段
    # 会各自回落到缺省 `platform` → 同一次巡检内部不一致（那边会告警并按首段
    # 为准），看着能跑，实际是在"混着来"。
    detect_type = normalize_detect_type(job.get("detect_type"))

    payload: list[dict] = []
    action_count = 0
    for fl in sorted(floors):
        waypoints = []
        for idx, pk in enumerate(floors[fl], start=1):
            wj = pk.node.to_inspection_json(index=idx, fresh_id=fresh_ids,
                                            point_ids=pt_want,
                                            image_base=pk.image_base)
            wj["action"] = [a for a in wj["action"]
                            if not (a.get("type") == 2 and not a.get("thermometry_points"))]
            action_count += len(wj["action"])
            waypoints.append(wj)
        payload.append({"floor": fl, "id": task_id, "name": name, "plan": plan_id,
                        "substationMapsId": maps_id, "detectType": detect_type,
                        "waypoint": waypoints})

    return {
        "payload": payload,
        "inspection_id": task_id,
        "plan": plan_id,
        "detect_type": detect_type,
        "floors": sorted(floors),
        "waypoint_count": sum(len(v) for v in floors.values()),
        "action_count": action_count,
    }
