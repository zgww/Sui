"""Straitbot API V2.1.7, cmd=100: inline JSON content, no device schedule.

Source: https://jcnnojumuzl2.feishu.cn/wiki/YEXbwEqfSie3tIkT1QncnQlUn0g
FMS keeps scheduling locally. This adapter is also used for later route segments.
"""
import copy
import json
from fastapi import HTTPException


def immediate_payload(content):
    if not isinstance(content, dict) or not isinstance(content.get('waypoint'), list) or not content['waypoint']:
        raise HTTPException(422, '巡检内容必须包含非空航点列表')
    wire = copy.deepcopy(content)
    # This was a legacy platform database key, not a documented robot map selector.
    wire.pop('substationMapsId', None)
    # FMS-side routing hint: where action data feeds detection. The device never
    # sees it, so older robots cannot choke on an unknown key.
    wire.pop('detectType', None)
    wire.pop('detect_type', None)
    for waypoint in wire['waypoint']:
        if not isinstance(waypoint, dict):
            raise HTTPException(422, '巡检航点格式无效')
        actions = waypoint.get('action', [])
        if not isinstance(actions, list) or any(not isinstance(action, dict) for action in actions):
            raise HTTPException(422, '巡检动作格式无效')
        for action in actions:
            if action.get('type') == 201:
                # Also adapt snapshots created before the protocol integration.
                action.setdefault('action_delay_msec', action.get('duration', 0))
                action.pop('duration', None)
    try:
        serialized = json.dumps(wire, ensure_ascii=False, allow_nan=False, separators=(',', ':'))
    except (ValueError, TypeError):
        raise HTTPException(422, '巡检内容包含无效数值或无法序列化的参数')
    # Omitted/empty schedule means one-shot immediate execution; never forward
    # the FMS plan schedule or send a competing file URL.
    return {'content': serialized}
