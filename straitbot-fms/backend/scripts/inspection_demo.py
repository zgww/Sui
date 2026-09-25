"""Isolated demo entrypoint: FMS_INSPECTION_DEMO=1 uvicorn inspection_demo:app.

Mount this file on PYTHONPATH and a NEW, empty /app/data volume. Never use the
production data volume. All robot_api commands are intercepted, including after
restart. Existing non-demo databases are refused before initialization.
"""
import json
import os
import threading
import time
from datetime import date

if os.environ.get('FMS_INSPECTION_DEMO') != '1':
    raise RuntimeError('Explicit FMS_INSPECTION_DEMO=1 is required')

from app.config import DATA_DIR, DB_PATH

marker = DATA_DIR / 'inspection-demo.marker'
if DB_PATH.exists() and not marker.exists():
    raise RuntimeError('Refusing existing non-demo database; use an empty data volume')
marker.write_text('isolated-multimap-demo-v1', encoding='utf-8')

from app.database import init_db, SessionLocal
from app.models import Robot, RobotMap, Waypoint, WaypointAction, PointBinding, InspectionPlan
from app.point_archive.runtime import archive_store
from app.services import robot_api
from app.services.inspection_plans import PlanInput, save_plan

state_file = DATA_DIR / 'demo-device-state.json'
state = json.loads(state_file.read_text()) if state_file.exists() else {}
state_lock = threading.Lock()


def simulated_call(ip, port, rid, cmd, data=None, **kwargs):
    with state_lock:
        key = str(rid)
        if cmd == 102:
            current = state.get(key, {})
            if current.get('status') == 0 and time.time() >= current.get('complete_at', 0):
                current['status'] = 1
            return 0, 'DEMO 模拟设备', current
        if cmd == 100:
            if not isinstance((data or {}).get('content'), str) or data.get('schedule'):
                return 422, 'DEMO: content 必须为 JSON 字符串且立即执行不能包含排期', {}
            content = json.loads(data['content'])
            (DATA_DIR / 'demo-last-cmd100.json').write_text(json.dumps({'cmd': 100, **data}, ensure_ascii=False), encoding='utf-8')
            state[key] = {'inspection_id': content['id'], 'status': 0, 'complete_at': time.time() + 2}
        elif cmd == 101 and key in state:
            state[key]['status'] = {0: -1, 1: 2, 2: 0, 3: 0}.get((data or {}).get('control'), 0)
        state_file.write_text(json.dumps(state), encoding='utf-8')
        return 0, 'DEMO 已接受；未连接真实机器人', {}


robot_api.call = simulated_call
init_db()
with SessionLocal() as db:
    if not db.query(Robot).first():
        points, routes = [], []
        robot = Robot(name='【DEMO】跨楼层巡检机器人', ip='127.0.0.1', robot_id=9901, poll_status=False, poll_meta=False, note='仅模拟设备')
        other = Robot(name='【DEMO】备用机器人（空数据）', ip='127.0.0.1', robot_id=9902, poll_status=False, poll_meta=False)
        db.add_all([robot, other]); db.flush()
        for map_name, floors in [('配电楼', [1, 2]), ('主控楼', [1]), ('地下设备间', [-1])]:
            robot_map = RobotMap(robot_pk=robot.id, name=map_name, floor=floors[0])
            db.add(robot_map); db.flush()
            for floor in floors:
                selected = []
                for index in range(6):
                    wp = Waypoint(robot_pk=robot.id, map_pk=robot_map.id, floor=floor, name=f'{map_name} {floor}层 柜位{index+1}', wp_id=f'{floor}-{index}', index=index, pose_x=index*2, pose_y=floor*10)
                    db.add(wp); db.flush()
                    db.add(WaypointAction(waypoint_pk=wp.id, name='可见光识别', action_type=1))
                    db.add(WaypointAction(waypoint_pk=wp.id, seq=1, name='红外测温', action_type=2))
                    for kind in ['温度', '电压', '电流', '开关状态']:
                        pid = f'demo-{len(points)+1:03d}'
                        points.append({'id': pid, 'code': f'PT-{len(points)+1:03d}', 'name': f'{map_name} {floor}层 {index+1:02d}号柜 {kind}', 'directory_id': None, 'active': True, 'assay_type': 1, 'times': 1})
                        selected.append(pid)
                        db.add(PointBinding(point_id=pid, waypoint_pk=wp.id))
                routes.append({'map_pk': robot_map.id, 'floor': floor, 'point_ids': selected})
        db.commit()
        archive_store.initialize({'schema_version': 2, 'revision': 1, 'directories': [], 'points': points})
        today = date.today().isoformat()
        for name, route, schedule in [
            ('全站联合巡检 · 4 段', routes, {'mode': 'manual'}),
            ('配电楼日常巡检 · 1F → 2F', routes[:2], {'mode': 'daily', 'start_date': today, 'time': '09:00'}),
            ('主控楼与地下设备间 · 周巡检', routes[2:], {'mode': 'weekly', 'start_date': today, 'time': '14:30', 'weekdays': [0, 2, 4]}),
        ]:
            save_plan(db, archive_store, PlanInput(robot_pk=robot.id, name=name, stages=route, schedule=schedule, enabled=False))
        p = db.query(InspectionPlan).filter_by(name='全站联合巡检 · 4 段').one()
        p.enabled = True
        db.commit()
    else:
        archive_store.load()

from app.main import app
