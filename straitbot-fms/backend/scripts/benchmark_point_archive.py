"""Synthetic archive benchmark; stdlib only, temporary files, no FMS imports/data.

Run: python benchmark_point_archive.py --sizes 1000 10000 50000
File reads are warm-cache reads, not cold-disk measurements. Timings exclude HTTP,
Pydantic validation, authentication, binding joins, and concurrent traffic.
"""
import argparse
import gc
import json
import math
import os
import platform
import statistics
import tempfile
import time
import tracemalloc
from collections import defaultdict
from pathlib import Path


def make_rows(n):
    return [dict(
        id=f"001001001{i // 100:03d}{i % 100:03d}",
        code=f"PT-{i:08d}", name=f"主变压器油温表测点-{i}",
        equipment_id=f"EQ-{i // 100:05d}", station_id="001001",
        bay_id=f"BAY-{i // 1000:03d}", voltage_level="110kV",
        assay_type=i % 5 + 1, meter_type=1, times=2,
        scope="0-150", warn_setting="", active=True,
        position={"x": round(i * 0.1, 2), "y": 20.0},
        unit="摄氏度", description="用于巡检的静态测点基本档案，结果单独保存。",
        source={"system": "legacy-platform", "point_id": f"legacy-{i}"},
        created_at="2026-09-17T00:00:00+08:00",
        updated_at="2026-09-17T00:00:00+08:00",
        extensions={"asset_tag": f"ASSET-{i:08d}", "notes": ""},
    ) for i in range(n)]


def indexes(rows):
    by_id, by_code, by_equipment = {}, {}, defaultdict(list)
    for row in rows:
        by_id[row["id"]] = row
        by_code[row["code"]] = row
        by_equipment[row["equipment_id"]].append(row)
    return by_id, by_code, by_equipment


def measure(fn, repeats=50, batch=1):
    fn()
    samples = []
    for _ in range(repeats):
        start = time.perf_counter_ns()
        for _ in range(batch):
            fn()
        samples.append((time.perf_counter_ns() - start) / batch / 1e6)
    return {"median_ms": round(statistics.median(samples), 6),
            "p95_ms": round(sorted(samples)[math.ceil(len(samples) * .95)-1], 6),
            "repeats": repeats, "batch": batch}


def run(n):
    with tempfile.TemporaryDirectory(prefix="fms-archive-bench-") as tmp:
        path = Path(tmp) / "archive.json"
        path.write_text(json.dumps({"schema_version": 1, "revision": 1,
                                    "points": make_rows(n)}, ensure_ascii=False), encoding="utf-8")
        load = lambda: json.loads(path.read_text(encoding="utf-8"))
        gc.collect()
        tracemalloc.start()
        document = load()
        rows = document["points"]
        by_id, by_code, by_equipment = indexes(rows)
        retained, peak = tracemalloc.get_traced_memory()
        tracemalloc.stop()
        target = rows[-1]["id"]
        equipment = rows[-1]["equipment_id"]
        keyword = "油温"
        scan = lambda: next(row for row in rows if row["id"] == target)
        reread = lambda: next(row for row in load()["points"] if row["id"] == target)
        exact = lambda: by_id[target]
        filtered = lambda: [row for row in rows if keyword in row["name"] and row["assay_type"] == 2]
        equipment_query = lambda: by_equipment[equipment][:50]
        page = lambda: json.dumps({"total": n, "items": rows[:50]}, ensure_ascii=False)
        def publish():
            candidate = path.with_suffix(".tmp")
            with candidate.open("w", encoding="utf-8") as stream:
                json.dump(document, stream, ensure_ascii=False)
                stream.flush()
                os.fsync(stream.fileno())
            os.replace(candidate, path)
            if hasattr(os, "O_DIRECTORY"):
                fd = os.open(tmp, os.O_RDONLY | os.O_DIRECTORY)
                try:
                    os.fsync(fd)
                finally:
                    os.close(fd)
        assert scan() == reread() == exact()
        assert len(filtered()) == n // 5
        assert len(equipment_query()) == 50
        result = {"points": n, "file_mib": round(path.stat().st_size / 2**20, 3),
                  "python_retained_mib": round(retained / 2**20, 3),
                  "python_peak_mib": round(peak / 2**20, 3),
                  "read_parse": measure(load, 20),
                  "build_indexes": measure(lambda: indexes(rows), 20),
                  "read_parse_scan": measure(reread, 20),
                  "memory_scan_last_id": measure(scan),
                  "memory_index_id": measure(exact, batch=10000),
                  "memory_equipment_page": measure(equipment_query, batch=1000),
                  "memory_keyword_type_filter": measure(filtered),
                  "serialize_50_rows": measure(page),
                  "atomic_publish": measure(publish, 5)}
        return result


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--sizes", nargs="+", type=int, default=[1000, 10000, 50000])
    args = parser.parse_args()
    if any(n < 100 or n % 100 for n in args.sizes):
        parser.error("sizes must be positive multiples of 100")
    print(json.dumps({"python": platform.python_version(), "arch": platform.machine(),
                      "platform": platform.platform(), "synthetic": True,
                      "results": [run(n) for n in args.sizes]}, ensure_ascii=False, indent=2))
