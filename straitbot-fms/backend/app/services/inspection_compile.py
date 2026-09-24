"""Compile bound points into Straitbot API V2.1.7 cmd=100 content."""
from fastapi import HTTPException
from ..models import PointBinding, Robot, RobotMap, Waypoint, WaypointAction
from .inspection_protocol import immediate_payload


def compile_plan(db, store, robot_pk, map_pk, point_ids, execution_id, name, floor=None):
    robot = db.get(Robot, robot_pk)
    robot_map = db.get(RobotMap, map_pk)
    if not robot or not robot_map or robot_map.robot_pk != robot_pk:
        raise HTTPException(422, '地图不属于所选机器人')
    if not point_ids or len(point_ids) != len(set(point_ids)):
        raise HTTPException(422, '请选择不重复的测点')
    for pid in point_ids:
        point = store.get(pid)
        if not point or not point.get('active', True):
            raise HTTPException(422, f'测点不存在或已停用：{pid}')
    rows = db.query(PointBinding, Waypoint).join(Waypoint, PointBinding.waypoint_pk == Waypoint.id).filter(
        PointBinding.point_id.in_(point_ids), Waypoint.robot_pk == robot_pk, Waypoint.map_pk == map_pk
    ).all()
    if floor is not None:
        rows = [(b, w) for b, w in rows if (w.floor if w.floor is not None else robot_map.floor or 0) == floor]
    missing = set(point_ids) - {b.point_id for b, _ in rows}
    if missing:
        raise HTTPException(422, '测点未绑定当前地图的航点：' + '、'.join(sorted(missing)[:10]))
    targets = {}
    for b, w in rows:
        group = targets.setdefault(w.id, {'waypoint': w, 'all': False, 'actions': set(), 'bindings': []})
        group['all'] |= b.action_pk is None
        if b.action_pk is not None:
            group['actions'].add(b.action_pk)
        group['bindings'].append({'point_id': b.point_id, 'waypoint_pk': w.id, 'action_pk': b.action_pk})
    waypoints, snapshots, external_ids = [], [], set()
    for group in sorted(targets.values(), key=lambda g: (g['waypoint'].index, g['waypoint'].id)):
        w = group['waypoint']
        external = w.wp_id or str(w.id)
        if external in external_ids:
            raise HTTPException(422, '当前地图航点外部 ID 重复')
        external_ids.add(external)
        actions = db.query(WaypointAction).filter_by(waypoint_pk=w.id).order_by(WaypointAction.seq, WaypointAction.id).all()
        if not group['actions'].issubset({a.id for a in actions}):
            raise HTTPException(422, '绑定动作已失效，请重新绑定')
        chosen = actions if group['all'] else [a for a in actions if a.id in group['actions']]
        if not chosen:
            raise HTTPException(422, f'航点 {w.name} 没有可执行动作')
        def inherited(a, attr):
            value = getattr(a, attr)
            return value if value is not None else getattr(w, attr)
        waypoints.append({'index': len(waypoints), 'id': external, 'type': w.type,
            'pose': {'point': {'x': w.pose_x, 'y': w.pose_y, 'z': 0}, 'theta': w.pose_theta},
            'action': [{'id': str(a.id), 'type': a.action_type,
                        'lift_height': inherited(a, 'lift_height'),
                        'ptz_param': {'pan': inherited(a, 'ptz_pan'), 'tilt': inherited(a, 'ptz_tilt'), 'zoom': inherited(a, 'ptz_zoom')},
                        **({'action_delay_msec': a.duration_ms} if a.action_type == 201 else {'duration': a.duration_ms}),
                        'steer_point_name': a.name or w.name} for a in chosen]})
        snapshots.extend(group['bindings'])
    content = {'plan': name, 'id': execution_id, 'name': name, 'waypoint': waypoints}
    immediate_payload(content)  # Validate before persisting an execution claim.
    return content, snapshots


def compile_route(db, store, robot_pk, stages, execution_id, name):
    route, bindings = [], []
    for index, stage in enumerate(stages):
        stage_id = execution_id if index == 0 else f'{execution_id}-s{index + 1}'
        content, selected = compile_plan(db, store, robot_pk, stage['map_pk'], stage['point_ids'], stage_id, name, stage.get('floor'))
        robot_map = db.get(RobotMap, stage['map_pk'])
        route.append({'map_pk': robot_map.id, 'map_name': robot_map.name, 'floor': stage.get('floor'),
                      'point_ids': stage['point_ids'], 'content': content})
        bindings.extend(dict(binding, stage_index=index, map_pk=robot_map.id, floor=stage.get('floor')) for binding in selected)
    return route, bindings
