"""Reusable isolated point archive fixtures."""


def archive_fixture(n=1):
    return {
        "schema_version": 1, "revision": 1,
        "stations": [{"id": "s1", "name": "测试站", "code": "001"}],
        "bays": [{"id": "b1", "name": "测试间隔", "station_id": "s1"}],
        "equipment": [{"id": "e1", "name": "测试设备", "bay_id": "b1"}],
        "points": [{"id": f"p{i}", "name": f"测点{i}", "code": f"P{i:05d}",
                    "equipment_id": "e1", "assay_type": 1, "times": 1, "active": True}
                   for i in range(1, n + 1)],
    }
