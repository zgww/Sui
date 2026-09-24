"""航点的 `floor` 字段。

楼层**必须挂在航点自己身上**，不能只落在分组名 `楼层N` 里：
分组名是给人看的，改个名（或再套一层"区域A"）就解不出来了，
而巡检任务是**按楼层分段**下发的——楼层一错，整段航点的执行顺序就错了。
"""
from app.prefab.nodes.waypoint import WaypointNode
from app.prefab.waypoint_import import inspection_to_spec


def _payload(floor: int, indices=(1, 2)):
    return {
        "floor": floor,
        "id": "a" * 32,
        "name": f"{floor} 层巡检",
        "waypoint": [
            {"id": f"w{i}", "index": i, "pose": {"point": {"x": i * 1.5, "y": 0, "z": 0},
                                                 "theta": 0},
             "action": []}
            for i in indices
        ],
    }


def waypoints_of(spec):
    """先序遍历取出所有 WaypointNode 的 properties。"""
    out = []

    def walk(n):
        if n.get("type") == "WaypointNode":
            out.append(n["properties"])
            return
        for c in n.get("children") or []:
            walk(c)
    walk(spec["root"])
    return out


def test_waypoint_node_has_floor_field():
    assert "floor" in WaypointNode.model_fields
    # 默认 1：老 spec 没有这个字段时反序列化出来就是 1，跟前端 DEFAULT_FLOOR 一致
    assert WaypointNode().floor == 1


def test_import_writes_floor_on_each_waypoint():
    spec = inspection_to_spec(_payload(2))
    floors = [w["floor"] for w in waypoints_of(spec)]
    assert floors == [2, 2]


def test_import_keeps_floor_per_segment():
    spec = inspection_to_spec([_payload(1), _payload(3)])
    floors = [w["floor"] for w in waypoints_of(spec)]
    # 两个楼层段各 2 个航点，先序遍历 -> 前两个 1 楼、后两个 3 楼
    assert floors == [1, 1, 3, 3]


def test_basement_floor_survives():
    spec = inspection_to_spec(_payload(-1))
    assert [w["floor"] for w in waypoints_of(spec)] == [-1, -1]


def test_group_name_still_carries_floor_for_humans():
    """分组名 `楼层N` 保留（老的回解逻辑还在用），但它不再是楼层唯一的家。"""
    spec = inspection_to_spec(_payload(2))
    groups = [c for c in spec["root"]["children"] if c.get("type") == "GroupNode"]
    assert groups[0]["properties"]["name"] == "楼层2"


def test_missing_floor_defaults_to_one():
    payload = _payload(1)
    payload.pop("floor")
    assert [w["floor"] for w in waypoints_of(inspection_to_spec(payload))] == [1, 1]
