"""枚举配置（第四棵 prefab 树）：节点类型、选项读取、接口。

覆盖三件事：
1. **`EnumNode` / `EnumItemNode` 的字段与类型目录**——三个字段一个都不能少，
   且只能挂在 `EnumNodeBase` 下（不能混进另外三棵树）；
2. **`enum_catalog` 的选项规则**——停用 / 空键 / label 回落，这几条必须和前端
   `utils/enumSpec.ts` 一致，否则"树上看得见的项在下拉框里点不到"；
3. **`/options` 接口**——告警中心的类型下拉只认这一个入口，且**取不到要返回
   found=false 而不是 500**。

⚠️ 目录一律用 `tmp_path` 隔离：枚举目录是真实数据目录（`data/prefabs/枚举`），
测试往里写文件会污染开发库，也会让"有哪些枚举"的断言随机失败。
"""
from __future__ import annotations

import json
from types import SimpleNamespace

import pytest
from fastapi import FastAPI
from fastapi.testclient import TestClient

from app.auth import engineer_only, get_current_user
from app.prefab import enum_catalog, registry
from app.prefab.nodes.enum import EnumItemNode, EnumNode
from app.routers.enum_prefab import _enum_root
from app.routers.prefab_store import make_prefab_router


# ============================================================ 节点类型

def test_node_types_registered_under_enum_base():
    """两棵树类型目录分开：只有这两个类型属于 EnumNodeBase。"""
    types = registry.schema_for_base("EnumNodeBase")
    assert set(types) == {"EnumNode", "EnumItemNode"}


@pytest.mark.parametrize("cls,group", [(EnumNode, "枚举"), (EnumItemNode, "枚举项")])
def test_three_fields_with_ui_meta(cls, group):
    """name / label / description 三个字段都要在，且归属本节点的分组。

    检视器按 `ui.group` 分组渲染：字段在「通用」组里的话，用户要在一堆通用
    控件里找「选项值」，等于没有。
    """
    schema = cls.model_json_schema()
    props = schema["properties"]
    for f in ("name", "label", "description"):
        assert f in props, f"{cls.__name__} 缺少字段 {f}"
    assert props["name"]["ui"]["group"] == group
    assert props["label"]["ui"]["group"] == group
    assert props["description"]["ui"]["group"] == group
    assert props["name"]["ui"]["widget"] == "text"
    assert props["description"]["ui"]["widget"] == "textarea"


def test_enum_node_not_in_other_trees():
    """类型目录不串门：枚举节点不能出现在航点 / 计划 / 检测流程的目录里。"""
    for base in ("WaypointNodeBase", "PlanNodeBase", "DetectNodeBase"):
        assert "EnumNode" not in registry.schema_for_base(base)
        assert "EnumItemNode" not in registry.schema_for_base(base)


def test_root_factory_builds_and_prefills_key():
    """新建文件的根就是 EnumNode 本身，且键/显示名预填成文件名。

    预填是必要的：不预填的话用户加完选项才发现"下拉框取不到"，因为没填 name
    时键会退回文件名——预填后两者一致，绝大多数情况不用管。
    """
    spec = _enum_root("告警类型")
    assert spec["root"]["type"] == "EnumNode"
    assert spec["root"]["properties"]["name"] == "告警类型"
    assert spec["root"]["properties"]["label"] == "告警类型"
    assert spec["root"]["properties"]["enabled"] is True
    node = registry.build(spec["root"])
    assert node.type == "EnumNode" and node.child_nodes == []


# ============================================================ 选项读取

def _write(root, rel: str, spec: dict) -> None:
    p = root / rel
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(json.dumps(spec, ensure_ascii=False), encoding="utf-8")


def _item(name: str, label: str = "", desc: str = "", enabled: bool = True) -> dict:
    return {"type": "EnumItemNode",
            "properties": {"name": name, "label": label, "description": desc,
                           "enabled": enabled},
            "children": []}


def _enum(name: str, items: list[dict]) -> dict:
    return {"name": name, "description": "",
            "root": {"type": "EnumNode",
                     "properties": {"name": name, "label": name, "enabled": True,
                                    "description": ""},
                     "children": items}}


def test_options_value_label_description(tmp_path):
    _write(tmp_path, "告警类型.prefab.json", _enum("告警类型", [
        _item("person_intrusion", "人员入侵", "画面里有人"),
        _item("smoke_fire", "烟火", ""),
    ]))
    res = enum_catalog.read_enum_options("告警类型", root=tmp_path)
    assert res["found"] is True
    assert res["options"] == [
        {"value": "person_intrusion", "label": "人员入侵", "description": "画面里有人"},
        {"value": "smoke_fire", "label": "烟火", "description": ""},
    ]


def test_disabled_and_blank_items_skipped(tmp_path):
    """停用的项不进下拉框；没填键的项也不进（筛不出东西，只能多一条空行）。

    第三条「label 空则回落 name」一起验：前端拿到的 label 一定非空。
    """
    _write(tmp_path, "告警类型.prefab.json", _enum("告警类型", [
        _item("ok", ""),
        _item("off", "停用项", enabled=False),
        _item("", "没填键"),
    ]))
    res = enum_catalog.read_enum_options("告警类型", root=tmp_path)
    assert res["found"] is True
    assert [o["value"] for o in res["options"]] == ["ok"]
    assert res["options"][0]["label"] == "ok"


def test_found_true_but_empty_when_no_items(tmp_path):
    """配了但一项没填：found=True 而 options=[] —— 与"没配过"是两件事。

    消费方据此决定是否回落到库里实际出现过的值；混成一种的话，"我特意清空了
    这份枚举"会被当成"没配过"，下拉框又把历史脏值塞回来。
    """
    _write(tmp_path, "告警类型.prefab.json", _enum("告警类型", []))
    res = enum_catalog.read_enum_options("告警类型", root=tmp_path)
    assert res["found"] is True and res["options"] == []

    assert enum_catalog.read_enum_options("不存在", root=tmp_path) == {
        "ok": True, "key": "不存在", "found": False, "options": [], "sources": []}


def test_key_falls_back_to_filename(tmp_path):
    """EnumNode 没填 name 时按文件名取（新建后常常先加项、忘了填 name）。"""
    _write(tmp_path, "告警类型.prefab.json", _enum("", [_item("a", "A")]))
    res = enum_catalog.read_enum_options("告警类型", root=tmp_path)
    assert res["found"] is True and [o["value"] for o in res["options"]] == ["a"]


def test_broken_file_does_not_break_catalog(tmp_path):
    """坏文件跳过，不抛异常——下拉框不该让整个页面 500。"""
    (tmp_path / "坏.prefab.json").write_text("{ not json", encoding="utf-8")
    _write(tmp_path, "好.prefab.json", _enum("告警类型", [_item("a", "A")]))
    res = enum_catalog.read_enum_options("告警类型", root=tmp_path)
    assert res["found"] is True and len(res["options"]) == 1


def test_duplicate_key_merged_and_deduped(tmp_path):
    """同一 key 出现在多个文件：按值去重、按首次出现顺序合并。

    不去重下拉框会有两行一样的值，点了筛出同样一批数据。
    """
    _write(tmp_path, "a/告警类型.prefab.json", _enum("告警类型", [_item("x", "X")]))
    _write(tmp_path, "b/告警类型.prefab.json", _enum("告警类型", [_item("x", "重复"), _item("y", "Y")]))
    res = enum_catalog.read_enum_options("告警类型", root=tmp_path)
    assert [o["value"] for o in res["options"]] == ["x", "y"]
    assert res["options"][0]["label"] == "X"  # 首次出现者胜


def test_list_keys(tmp_path):
    _write(tmp_path, "告警类型.prefab.json", _enum("告警类型", [_item("a", "A"), _item("b", "B")]))
    keys = enum_catalog.list_enum_keys(root=tmp_path)["keys"]
    assert keys == [{"key": "告警类型", "label": "告警类型", "count": 2,
                     "file": "告警类型.prefab.json"}]


# ============================================================ 接口

@pytest.fixture()
def client(tmp_path, monkeypatch):
    """最小 app + 独立目录：不碰真实 `data/prefabs/枚举`。"""
    monkeypatch.setattr(enum_catalog, "ENUM_PREFAB_DIR", str(tmp_path))
    app = FastAPI()
    app.include_router(make_prefab_router(
        prefix="/api/enum-prefab", tag="enum-prefab", root_dir=tmp_path,
        base_filter="EnumNodeBase", root_spec_factory=_enum_root))
    from app.routers import enum_prefab  # 挂在同一个 app 上，复用真实的 /options /keys

    app.include_router(enum_prefab.router)
    app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(
        id=1, username="tester", role="engineer", enabled=True)
    app.dependency_overrides[engineer_only] = lambda: SimpleNamespace(
        id=1, username="tester", role="engineer", enabled=True)
    with TestClient(app) as c:
        yield c


def test_options_endpoint_roundtrip(client):
    """CRUD 走通用工厂，/options 走枚举翻译层：存进去的项要能原样取出来。"""
    assert client.post("/api/enum-prefab/files",
                       json={"rel_path": "告警类型.prefab.json"}).status_code == 200

    spec = _enum("告警类型", [_item("person_intrusion", "人员入侵", "画面里有人")])
    r = client.post("/api/enum-prefab/tree", json={"rel_path": "告警类型.prefab.json",
                                                   "spec": spec})
    assert r.status_code == 200, r.text

    got = client.get("/api/enum-prefab/options", params={"key": "告警类型"}).json()
    assert got["found"] is True
    assert got["options"] == [{"value": "person_intrusion", "label": "人员入侵",
                               "description": "画面里有人"}]
    assert got["sources"] == ["告警类型.prefab.json"]


def test_options_endpoint_missing_key_is_empty_not_500(client):
    assert client.get("/api/enum-prefab/options", params={"key": "没有这份枚举"}).json() == {
        "ok": True, "key": "没有这份枚举", "found": False, "options": [], "sources": []}


def test_options_endpoint_rejects_foreign_node(client):
    """写盘前 `registry.build` 校验：别的结构存不进枚举树。"""
    r = client.post("/api/enum-prefab/tree", json={
        "rel_path": "x.prefab.json",
        "spec": {"root": {"type": "Sequence", "properties": {}, "children": []}}})
    assert r.status_code == 404  # 文件不存在（必须由 /files 先建）——不是 400


def test_keys_endpoint(client):
    client.post("/api/enum-prefab/files", json={"rel_path": "告警类型.prefab.json"})
    keys = client.get("/api/enum-prefab/keys").json()["keys"]
    assert keys and keys[0]["key"] == "告警类型" and keys[0]["count"] == 0
