"""算法目录（data/algorithms.json）：GET 透出示意图、POST 把示意图写回去。

写接口的三条硬要求，都在这里锁着：
1. **只改命中那一条的 `image`**，别把整份文件重写一遍（文件是运维手改的，
   重写会丢掉手写的换行/排版，diff 也没法看）；
2. 只认 `data:image/xxx;base64,...`（`svg` 不放行，它能带脚本）；
3. 有大小上限——algorithms.json 每次开页面都要整体拉一次。
"""
import json
from types import SimpleNamespace

import pytest
from fastapi import FastAPI
from fastapi.testclient import TestClient

from app.auth import engineer_only, get_current_user
from app.routers import waypoint_prefab as wp

PREFIX = "/api/waypoint-prefab"

#: 一份"像人手写的"目录：有 note、有 version，条目里没有 image 字段
DOC = {
    "version": 1,
    "updated": "2026-09-21",
    "note": "手改的运维文件，写完还得是人能读的样子",
    "algorithms": [
        {"id": "meter_pointer", "name": "指针表读数", "category": "表计读数",
         "color": "#00b42a", "description": "读取指针式仪表的示数"},
        {"id": "switch_state", "name": "开关分合状态", "category": "状态识别",
         "color": "#0064fa", "description": "识别分闸、合闸"},
    ],
}

IMG = "data:image/jpeg;base64," + "QUJD" * 16


@pytest.fixture
def context(tmp_path, monkeypatch):
    f = tmp_path / "algorithms.json"
    f.write_text(json.dumps(DOC, ensure_ascii=False, indent=2), encoding="utf-8")
    monkeypatch.setattr(wp, "ALGORITHMS_FILE", f)
    app = FastAPI()
    app.include_router(wp.router)
    app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role="engineer", enabled=True)
    app.dependency_overrides[engineer_only] = lambda: SimpleNamespace(role="engineer", enabled=True)
    with TestClient(app) as c:
        yield c, f, app


def saved(f):
    return json.loads(f.read_text(encoding="utf-8"))


def test_get_returns_image_field_empty_by_default(context):
    client, _, _ = context
    items = client.get(PREFIX + "/algorithms").json()["algorithms"]
    assert len(items) == 2
    assert all(a["image"] == "" for a in items)


def test_save_image_round_trips(context):
    client, f, _ = context
    r = client.post(PREFIX + "/algorithms/image", json={"id": "meter_pointer", "image": IMG})
    assert r.status_code == 200 and r.json()["has_image"] is True
    # 端到端闭环：存完再拉目录要能看到图
    got = {a["id"]: a["image"] for a in client.get(PREFIX + "/algorithms").json()["algorithms"]}
    assert got["meter_pointer"] == IMG
    assert got["switch_state"] == ""


def test_only_the_matched_entry_is_touched(context):
    client, f, _ = context
    client.post(PREFIX + "/algorithms/image", json={"id": "meter_pointer", "image": IMG})
    doc = saved(f)
    # 别人的字段一个都不许动（尤其不许给没传图的条目塞一个空 image）
    assert "image" not in doc["algorithms"][1]
    assert doc["algorithms"][1]["name"] == "开关分合状态"
    # 文件级的元信息也原样留着
    assert doc["note"] == DOC["note"] and doc["version"] == 1 and doc["updated"] == "2026-09-21"
    assert doc["algorithms"][0]["image"] == IMG


def test_empty_string_deletes(context):
    client, f, _ = context
    client.post(PREFIX + "/algorithms/image", json={"id": "meter_pointer", "image": IMG})
    r = client.post(PREFIX + "/algorithms/image", json={"id": "meter_pointer", "image": ""})
    assert r.json()["has_image"] is False
    assert "image" not in saved(f)["algorithms"][0]


def test_rejects_non_image_and_svg(context):
    client, f, _ = context
    for bad in ["javascript:alert(1)", "data:image/svg+xml;base64,QUJD", "data:text/html;base64,QUJD",
                "not-a-data-url", "data:image/png,QUJD"]:
        assert client.post(PREFIX + "/algorithms/image",
                           json={"id": "meter_pointer", "image": bad}).status_code == 422
    assert "image" not in saved(f)["algorithms"][0]


def test_rejects_oversized(context):
    client, _, _ = context
    huge = "data:image/jpeg;base64," + "A" * (wp.ALGO_IMAGE_MAX_CHARS + 1)
    r = client.post(PREFIX + "/algorithms/image", json={"id": "meter_pointer", "image": huge})
    assert r.status_code == 413
    assert "320px" in r.json()["detail"]


def test_unknown_id_is_404(context):
    client, f, _ = context
    assert client.post(PREFIX + "/algorithms/image",
                       json={"id": "nope", "image": IMG}).status_code == 404
    assert saved(f) == DOC


def test_missing_fields_are_422(context):
    client, _, _ = context
    assert client.post(PREFIX + "/algorithms/image", json={"image": IMG}).status_code == 422
    assert client.post(PREFIX + "/algorithms/image", json={"id": "meter_pointer"}).status_code == 422
    assert client.post(PREFIX + "/algorithms/image",
                       json={"id": "meter_pointer", "image": 123}).status_code == 422


def test_operator_cannot_write(context):
    """示意图是改运维数据，操作员不该能写（走真实的 `engineer_only`，不覆写它）。"""
    client, f, app = context
    app.dependency_overrides.pop(engineer_only)
    app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role="operator", enabled=True)
    assert client.post(PREFIX + "/algorithms/image",
                       json={"id": "meter_pointer", "image": IMG}).status_code == 403
    assert saved(f) == DOC


def test_no_temp_file_left_behind(context):
    client, f, _ = context
    client.post(PREFIX + "/algorithms/image", json={"id": "meter_pointer", "image": IMG})
    leftovers = [p.name for p in f.parent.iterdir() if p.suffix == ".tmp"]
    assert leftovers == []


def test_missing_catalog_file(context):
    client, f, _ = context
    f.unlink()
    assert client.get(PREFIX + "/algorithms").json()["ok"] is False
    assert client.post(PREFIX + "/algorithms/image",
                       json={"id": "meter_pointer", "image": IMG}).status_code == 404
