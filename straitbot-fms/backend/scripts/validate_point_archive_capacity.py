"""Isolated actual HTTP-router benchmark (no robots or production data)."""
import concurrent.futures
import json
import math
import multiprocessing
import statistics
import tempfile
import socket
import threading

import httpx
import uvicorn
import time
import tracemalloc
from pathlib import Path
from types import SimpleNamespace

from fastapi import FastAPI
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from app.auth import get_current_user
from app.database import Base, get_db
from app.models import PointBinding
from app.point_archive.runtime import get_archive_store
from app.point_archive.schema import empty_snapshot
from app.point_archive.store import ArchiveStore
from app.routers.point_archive import router, install_error_handlers
from scripts.benchmark_point_archive import make_rows


def run():
    with tempfile.TemporaryDirectory(prefix="fms-capacity-") as tmp:
        root = Path(tmp)
        document = empty_snapshot()
        document.update(stations=[{"id": "001001", "name": "隔离性能测试站"}],
                        bays=[{"id": f"BAY-{i:03d}", "station_id": "001001", "name": f"间隔{i}", "voltage_level": "110kV"} for i in range(10)],
                        equipment=[{"id": f"EQ-{i:05d}", "bay_id": f"BAY-{i//10:03d}", "name": f"设备{i}"} for i in range(100)],
                        points=make_rows(10000))
        store = ArchiveStore(root / "archive.json")
        store.initialize(document)
        tracemalloc.start()
        store.load()
        retained, peak = tracemalloc.get_traced_memory()
        tracemalloc.stop()
        reload_samples = []
        for _ in range(3):
            start = time.perf_counter()
            store.load()
            reload_samples.append((time.perf_counter()-start)*1000)
        load_ms = statistics.median(reload_samples)
        engine = create_engine("sqlite:///" + str(root / "test.db"), connect_args={"check_same_thread": False})
        Base.metadata.create_all(engine)
        sessions = sessionmaker(bind=engine)
        app = FastAPI()
        app.include_router(router)
        install_error_handlers(app)
        def db_dep():
            with sessions() as db:
                yield db
        app.dependency_overrides[get_db] = db_dep
        app.dependency_overrides[get_archive_store] = lambda: store
        app.dependency_overrides[get_current_user] = lambda: SimpleNamespace(role="engineer")
        # One real HTTP keep-alive connection per worker. Unlike TestClient this
        # does not route every client operation through a shared AnyIO portal.
        local = threading.local()
        clients = []
        def request(i):
            if not hasattr(local, "client"):
                local.client = httpx.Client(base_url=base_url, timeout=30, trust_env=False)
                clients.append(local.client)
            client = local.client
            params = {"page_size": 50, "name": "油温", "bound": False}
            if i % 2:
                params["equipment_id"] = "EQ-00001"
            started = time.perf_counter()
            result = client.get("/api/point-archive/entities/points", params=params)
            elapsed = (time.perf_counter()-started)*1000
            assert result.status_code == 200, result.text
            body = result.json()
            assert body["total"] == (100 if i % 2 else 10000)
            assert len(body["items"]) == 50
            return elapsed
        listener = socket.socket()
        listener.bind(("127.0.0.1", 0))
        base_url = f"http://127.0.0.1:{listener.getsockname()[1]}"
        server = uvicorn.Server(uvicorn.Config(app, log_level="error", lifespan="off"))
        # Linux: distinct GIL as browser and backend run in separate processes.
        separate_process = "fork" in multiprocessing.get_all_start_methods()
        if separate_process:
            worker = multiprocessing.get_context("fork").Process(target=server.run, kwargs={"sockets": [listener]}, daemon=True)
        else:
            worker = threading.Thread(target=server.run, kwargs={"sockets": [listener]}, daemon=True)
        worker.start()
        deadline = time.monotonic() + 15
        while True:
            if time.monotonic() > deadline or not worker.is_alive():
                raise RuntimeError("isolated benchmark server failed to start")
            try:
                with httpx.Client(trust_env=False, timeout=.5) as probe:
                    if probe.get(base_url + "/api/point-archive/meta").status_code == 200:
                        break
            except httpx.TransportError:
                time.sleep(.01)
        try:
            with concurrent.futures.ThreadPoolExecutor(max_workers=10) as pool:
                cold_values = list(pool.map(request, range(10)))
                values = list(pool.map(request, range(100)))
        finally:
            for client in clients:
                client.close()
            if separate_process:
                worker.terminate()
            else:
                server.should_exit = True
            worker.join(timeout=15)
            listener.close()
        def timed(operation, repeats=30):
            durations = []
            for _ in range(repeats):
                started = time.perf_counter()
                operation()
                durations.append((time.perf_counter()-started)*1000)
            return round(statistics.median(durations), 3)
        def binding_query():
            with sessions() as db:
                return {row[0] for row in db.query(PointBinding.point_id).distinct()}
        payload = store.list_points(page_size=50, name="油温", bound=False, bound_ids=set())
        components = {
            "store_global_filter_median_ms": timed(lambda: store.list_points(page_size=50, name="油温", bound=False, bound_ids=set())),
            "store_equipment_filter_median_ms": timed(lambda: store.list_points(page_size=50, name="油温", bound=False, bound_ids=set(), equipment_id="EQ-00001")),
            "sqlite_binding_query_median_ms": timed(binding_query),
            "json_response_encoding_median_ms": timed(lambda: json.dumps(payload, ensure_ascii=False, allow_nan=False, separators=(",", ":"))),
        }
        values.sort()
        result = {"points": 10000, "requests": 100, "concurrency": 10, "page_size": 50,
                  "file_mib": round(store.path.stat().st_size/2**20, 3),
                  "median_ms": round(statistics.median(values), 2),
                  "p95_ms": round(values[math.ceil(len(values)*.95)-1], 2),
                  "max_ms": round(max(values), 2), "cold_batch_max_ms": round(max(cold_values), 2),
                  "reload_ms": round(load_ms, 2), "reload_samples_ms": [round(v, 2) for v in reload_samples],
                  "components": components, "server_separate_process": separate_process,
                  "retained_python_mib": round(retained/2**20, 2), "reload_peak_python_mib": round(peak/2**20, 2),
                  "notes": "Real loopback TCP Uvicorn; 10 persistent HTTP clients, 10 warmup and 100 measured requests; engineer dependency mocked; real temporary SQLite with empty bindings; no TLS or real device. Client/server share host; server_separate_process indicates independent GIL (Linux) versus shared GIL (Windows fallback). Reload median of 3; tracemalloc excludes old snapshot allocations."}
        engine.dispose()
        print(json.dumps(result, ensure_ascii=False, indent=2))
        return result


if __name__ == "__main__":
    run()
