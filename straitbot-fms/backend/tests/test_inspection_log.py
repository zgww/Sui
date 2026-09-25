"""巡检日志查询的回归测试：全部跑在临时 SQLite 上，不碰设备、不碰生产库。

这一层锁的是**页面口径**而不是 SQL 能不能跑通：

- ``counts_source`` 的三级回落（动作账本 → 旧表 → 内存进度）——回落错了
  页面上会显示"0/0"，看着像这次巡检什么都没干；
- ``stalled`` 的判定（开了很久且一个动作都没回填）——不判的话日志页会永远
  挂着半年前的"进行中"；
- 分页的过滤器复现（``count`` 与取页必须同条件，否则 ``total`` 和列表对不上）；
- ``passed`` 的**三态**：None 不能被算成"未通过"，否则凭空造出一堆异常点。
"""
import pytest
from datetime import datetime, timedelta
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from app.database import Base
from app.models import (
    InspectionActionResult,
    InspectionPointResult,
    InspectionResult,
    InspectionRun,
    Robot,
)
from app.services import inspection_log as log_svc


@pytest.fixture
def db(tmp_path):
    engine = create_engine('sqlite:///' + str(tmp_path / 'log.sqlite'))
    Base.metadata.create_all(engine)
    session = sessionmaker(bind=engine)()
    try:
        yield session
    finally:
        session.close()
        engine.dispose()


@pytest.fixture
def env(db):
    """两台机器人 + 三次巡检（全跑完 / 卡住 / 失败），动作与测点齐全。"""
    r1 = Robot(name='一号机', ip='10.0.0.1')
    r2 = Robot(name='二号机', ip='10.0.0.2')
    db.add_all([r1, r2])
    db.flush()

    now = datetime.utcnow()
    done = InspectionRun(robot_pk=r1.id, inspection_id='INSP-DONE', status='done',
                         start_time=now - timedelta(hours=3),
                         finish_time=now - timedelta(hours=2), remark='日巡')
    stalled = InspectionRun(robot_pk=r2.id, inspection_id='INSP-STALLED', status='started',
                            start_time=now - timedelta(days=3), remark='夜巡')
    failed = InspectionRun(robot_pk=None, inspection_id='INSP-FAILED', status='failed',
                           start_time=now - timedelta(hours=1), remark='临时')
    db.add_all([done, stalled, failed])
    db.flush()

    # 跑完的那次：3 个动作全 ok，其中 2 个动作各带一个检测测点
    for seq in range(3):
        row = InspectionActionResult(
            run_id=done.id, robot_pk=r1.id, inspection_id=done.inspection_id,
            floor=1, waypoint_id=f'wp{seq}', waypoint_index=seq,
            action_id=f'act{seq}', action_seq=seq, action_type=1,
            status='ok', dispatch_status='done',
        )
        db.add(row)
        db.flush()
        if seq < 2:
            db.add(InspectionPointResult(
                action_result_id=row.id, run_id=done.id, robot_pk=r1.id,
                inspection_id=done.inspection_id, floor=1, waypoint_id=f'wp{seq}',
                action_id=f'act{seq}', point_id=f'PT{seq}', seq=0, kind='detect',
                status='ok', passed=(seq == 0), confidence=0.9,
                detect_flow='flow-a', algorithm='yolo', boxes_json=[{'x': 0.1}],
            ))
    # 卡住的那次：只有占位，一个都没回填
    for seq in range(2):
        db.add(InspectionActionResult(
            run_id=stalled.id, robot_pk=r2.id, inspection_id=stalled.inspection_id,
            floor=1, waypoint_id=f'wp{seq}', action_id=f'act{seq}', action_seq=seq,
            status='pending', dispatch_status='pending',
        ))
    # 失败的那次：旧表只有它，用来验回落
    db.add_all([
        InspectionResult(run_id=failed.id, robot_pk=None, waypoint_id='wp0',
                         action_id='act0', code=0),
        InspectionResult(run_id=failed.id, robot_pk=None, waypoint_id='wp0',
                         action_id='act1', code=5),
    ])
    db.commit()
    return {'db': db, 'r1': r1, 'r2': r2, 'done': done, 'stalled': stalled, 'failed': failed}


# ---------------------------------------------------------------- 纯工具
def test_parse_dt_accepts_the_shapes_a_browser_sends():
    assert log_svc._parse_dt('2026-09-22') == datetime(2026, 9, 22)
    assert log_svc._parse_dt('2026-09-22 14:30') == datetime(2026, 9, 22, 14, 30)
    assert log_svc._parse_dt('2026-09-22T14:30:00') == datetime(2026, 9, 22, 14, 30, 0)
    # 认不出就返回 None —— 不能因为前端多传了个空串就 500
    assert log_svc._parse_dt('') is None
    assert log_svc._parse_dt(None) is None
    assert log_svc._parse_dt('不是时间') is None


def test_pct_never_divides_by_zero_and_stays_in_range():
    assert log_svc._pct(0, 0) == 0        # 不是 100、也不是除零崩掉
    assert log_svc._pct(5, 10) == 50
    assert log_svc._pct(10, 10) == 100
    assert log_svc._pct(999, 10) == 100   # 数据脏了也夹住，不让进度条冲出格子


def test_effective_status_marks_a_long_stalled_run():
    now = datetime(2026, 9, 22, 12, 0, 0)
    long_ago = now - timedelta(hours=log_svc.STALL_HOURS + 1)
    fresh = now - timedelta(minutes=5)
    # 开跑很久 + 一个动作都没回填 => 疑似中断
    assert log_svc._effective_status('started', 3, 0, long_ago, now=now) == 'stalled'
    # 有动作在回填说明还活着 => 照旧显示进行中
    assert log_svc._effective_status('started', 3, 1, long_ago, now=now) == 'started'
    # 刚开始跑 => 不能误报
    assert log_svc._effective_status('started', 3, 0, fresh, now=now) == 'started'
    # 已终结的状态一律原样透传，别拿"卡住"去盖"失败"
    assert log_svc._effective_status('failed', 3, 0, long_ago, now=now) == 'failed'
    assert log_svc._effective_status('done', 3, 3, long_ago, now=now) == 'done'
    # 没有开始时间的老数据不能算成卡住
    assert log_svc._effective_status('started', 3, 0, None, now=now) == 'started'


# ---------------------------------------------------------------- 列表
def test_lists_every_run_in_the_database(env):
    """这是本次改造的核心：不传 robot_pk 就要拿到**全部**记录。"""
    rows = log_svc.page_runs(env['db'], page=1, page_size=50)
    ids = {r.inspection_id for r in rows}
    assert ids == {'INSP-DONE', 'INSP-STALLED', 'INSP-FAILED'}
    assert log_svc.count_runs(env['db'], {}) == 3


def test_robot_filter_and_count_agree(env):
    filters = {'robot_pk': env['r1'].id}
    rows = log_svc.page_runs(env['db'], **filters)
    assert [r.inspection_id for r in rows] == ['INSP-DONE']
    # count 与取页必须同条件，"共 N 条"才不会跟列表打架
    assert log_svc.count_runs(env['db'], filters) == 1


def test_newest_first_and_stable_across_pages(env):
    """按 start_time 倒序；时间并列时靠 id 兜底，翻页不跳行不重复。"""
    db = env['db']
    same = datetime(2026, 1, 1, 0, 0, 0)
    for i in range(5):
        db.add(InspectionRun(robot_pk=env['r1'].id, inspection_id=f'SAME-{i}',
                             status='done', start_time=same))
    db.commit()
    got = []
    for page in (1, 2, 3):
        got += [r.inspection_id for r in log_svc.page_runs(db, page=page, page_size=3)]
    assert len(got) == len(set(got)), f'翻页出现重复：{got}'
    assert set(got) == {'INSP-DONE', 'INSP-STALLED', 'INSP-FAILED',
                        'SAME-0', 'SAME-1', 'SAME-2', 'SAME-3', 'SAME-4'}


def test_status_and_keyword_filters(env):
    db = env['db']
    assert [r.inspection_id for r in log_svc.page_runs(db, status='failed')] == ['INSP-FAILED']
    assert [r.inspection_id for r in log_svc.page_runs(db, keyword='夜巡')] == ['INSP-STALLED']
    assert [r.inspection_id for r in log_svc.page_runs(db, keyword='INSP-FAIL')] == ['INSP-FAILED']
    assert log_svc.page_runs(db, keyword='不存在的关键字') == []


def test_time_range_end_date_includes_that_whole_day(env):
    """只给日期时右端按"当天 23:59:59"算 —— 否则用户选的那天会被整段滤掉。"""
    db = env['db']
    day = (datetime.utcnow() - timedelta(hours=3)).strftime('%Y-%m-%d')
    rows = log_svc.page_runs(db, start=day, end=day)
    assert 'INSP-DONE' in {r.inspection_id for r in rows}


def test_summarize_prefers_action_ledger_then_falls_back(env):
    db = env['db']
    rows = {r.inspection_id: r for r in log_svc.page_runs(db, page_size=50)}
    run_ids = [r.id for r in rows.values()]
    counts = log_svc.action_counts(db, run_ids)
    legacy = log_svc.legacy_counts(db, run_ids)
    points = log_svc.detect_counts(db, run_ids)
    names = log_svc.robot_names(db, [r.robot_pk for r in rows.values()])

    # ① 新表有数据 => 用新表，带出失败/待执行与测点计数
    done = log_svc.summarize_run(rows['INSP-DONE'], counts=counts.get(rows['INSP-DONE'].id),
                                 legacy=legacy.get(rows['INSP-DONE'].id),
                                 points=points.get(rows['INSP-DONE'].id), names=names)
    assert done['counts_source'] == 'action_results'
    assert (done['total_actions'], done['done_actions']) == (3, 3)
    assert done['progress_pct'] == 100
    assert done['point_count'] == 2 and done['detect_count'] == 2
    assert done['robot_name'] == '一号机'

    # ② 新表没数据 => 回落旧表（老巡检记录不会因为这次改造变空）
    failed = log_svc.summarize_run(rows['INSP-FAILED'], counts=counts.get(rows['INSP-FAILED'].id),
                                   legacy=legacy.get(rows['INSP-FAILED'].id), names=names)
    assert failed['counts_source'] == 'inspection_results'
    assert (failed['total_actions'], failed['done_actions']) == (2, 1)
    assert failed['progress_pct'] == 50
    # robot_pk 为空时不能编一个名字出来
    assert failed['robot_name'] is None

    # ③ 都没有 => total=0 时 pct 必须是 None（前端渲染成 "—" 而不是 "0%"）
    stalled = log_svc.summarize_run(rows['INSP-STALLED'], counts=counts.get(rows['INSP-STALLED'].id),
                                    names=names)
    assert stalled['counts_source'] == 'action_results'
    assert stalled['total_actions'] == 2 and stalled['done_actions'] == 0
    assert stalled['pending_actions'] == 2
    assert stalled['progress_pct'] == 0
    empty = log_svc.summarize_run(rows['INSP-STALLED'], names=names)
    assert empty['total_actions'] == 0 and empty['progress_pct'] is None

    # ④ 内存进度兜底（cmd=106 上报的，库里还没有）
    cached = log_svc.summarize_run(rows['INSP-STALLED'], names=names,
                                   progress={'total_waypoint': 4, 'current_waypoint': 3})
    assert cached['counts_source'] == 'progress_cache'
    assert (cached['total_actions'], cached['done_actions']) == (4, 2)


def test_summarize_keeps_display_status_in_sync(env):
    """列表行里的 display_status 必须已经含 stalled 判定，别让前端自己再算一遍。"""
    db = env['db']
    counts = log_svc.action_counts(db, [env['stalled'].id])
    row = log_svc.summarize_run(env['stalled'], counts=counts.get(env['stalled'].id))
    assert row['status'] == 'started'       # 库里的原始值不动
    assert row['display_status'] == 'stalled'


# ---------------------------------------------------------------- 明细
def test_action_serializer_carries_dispatch_fields(env):
    db = env['db']
    row = db.query(InspectionActionResult).filter(
        InspectionActionResult.run_id == env['done'].id).first()
    out = log_svc.serialize_action(row)
    # 分发五件套一个都不能少 —— 缺了页面就分不清"执行完了"和"送出去了"
    for key in ('dispatch_status', 'dispatch_mode', 'dispatch_attempts',
                'dispatched_at', 'dispatch_error'):
        assert key in out, f'缺字段 {key}'
    assert out['status'] == 'ok'
    assert out['action_type_name'] == '拍照'


def test_action_type_name_maps_protocol_codes():
    assert log_svc._action_type_name(1) == '拍照'
    assert log_svc._action_type_name(2) == '测温'
    assert log_svc._action_type_name(3) == '录像'
    assert log_svc._action_type_name(None) == ''
    assert log_svc._action_type_name('乱七八糟') == ''


def test_action_serializer_exposes_waypoint_name_from_raw(env):
    """``waypoint_name`` 从 ``raw_json`` 里取 —— 详情树要靠它显示"这是哪个柜子"。

    取值口径是**那一次巡检跑的时候**记下的名字（不是反查库）：事后改了航点名字、
    甚至删了航点，历史日志还得显示当时的名字。
    """
    db = env['db']
    row = db.query(InspectionActionResult).filter(
        InspectionActionResult.run_id == env['done'].id).first()

    # 没写 raw_json 时是空串，不崩
    row.raw_json = None
    assert log_svc.serialize_action(row)['waypoint_name'] == ''

    # raw_json 不是 dict（老数据可能存了字符串）也要不崩
    row.raw_json = '不是对象'
    assert log_svc.serialize_action(row)['waypoint_name'] == ''

    # 正常情况：取 steer_point_name
    row.raw_json = {'steer_point_name': 'G10联络柜'}
    out = log_svc.serialize_action(row)
    assert out['waypoint_name'] == 'G10联络柜'
    # 字段确实进了响应（前端类型里也有）
    assert 'waypoint_name' in out
    # 超长名字要截断（这是展示字段，不该把整段文本塞进列表响应）
    row.raw_json = {'steer_point_name': '柜' * 300}
    assert len(log_svc.serialize_action(row)['waypoint_name']) == 128


def test_point_serializer_keeps_passed_three_states(env):
    """``passed`` 是三态：true / false / None。把 None 当 false 会造出假异常。"""
    db = env['db']
    rows = db.query(InspectionPointResult).filter(
        InspectionPointResult.run_id == env['done'].id).all()
    out = [log_svc.serialize_point(r) for r in rows]
    assert out[0]['passed'] is True
    assert out[1]['passed'] is False
    assert out[0]['kind'] == 'detect'
    assert out[0]['algorithm'] == 'yolo'
    assert out[0]['boxes'] == [{'x': 0.1}]

    # 没判定的测点：passed 保持 None，别被兜成 False
    blank = InspectionPointResult(run_id=env['done'].id, point_id='PT9', kind='thermometry')
    db.add(blank)
    db.commit()
    got = log_svc.serialize_point(blank)
    assert got['passed'] is None
    assert got['boxe' + 's'] == []
    assert got['kind'] == 'thermometry'


def test_point_serializer_backfills_from_its_action(env):
    """测点自己的 image 为空时要拿动作的红外图顶上（测温点就是看红外图）。"""
    db = env['db']
    action = db.query(InspectionActionResult).filter(
        InspectionActionResult.run_id == env['done'].id).first()
    action.infrared = '/data/ir/1.jpg'
    db.commit()
    point = InspectionPointResult(action_result_id=action.id, run_id=env['done'].id,
                                 point_id='PT-X', kind='thermometry')
    db.add(point)
    db.commit()
    out = log_svc.serialize_point(point, action=action)
    assert out['image'] == '/data/ir/1.jpg'
    assert out['action_type_name'] == '拍照'


def test_action_status_summary_counts_both_axes(env):
    db = env['db']
    rows = db.query(InspectionActionResult).filter(
        InspectionActionResult.run_id == env['done'].id).all()
    summary = log_svc.action_status_summary(rows)
    assert summary['total'] == 3
    assert summary['status'] == {'ok': 3}
    assert summary['dispatch'] == {'done': 3}


# ---------------------------------------------------------------- 聚合查询
def test_counts_are_grouped_not_queried_per_run(env):
    """计数必须一次 group_by 出来；这里顺手验一下数字对得上。"""
    db = env['db']
    run_ids = [env['done'].id, env['stalled'].id, env['failed'].id]
    counts = log_svc.action_counts(db, run_ids)
    assert counts[env['done'].id]['total'] == 3
    assert counts[env['done'].id]['done'] == 3
    assert counts[env['stalled'].id]['pending'] == 2

    legacy = log_svc.legacy_counts(db, run_ids)
    assert legacy[env['failed'].id] == {'total': 2, 'done': 1}

    points = log_svc.detect_counts(db, run_ids)
    assert points[env['done'].id]['detect'] == 2
    assert points[env['done'].id]['points'] == 2


def test_action_counts_maps_ok_status_onto_done_bucket(env):
    """锁死 ``status='ok'`` -> 桶 ``done`` 的映射。

    第一版直接拿状态值当字典键，于是得到 ``{"total": 3, "done": 0, ..., "ok": 3}``：
    total 是对的、done 是 0，进度条永远 0% 却看不出哪儿错。状态名与桶名不是
    一回事，这个测试专门守着这条。
    """
    db = env['db']
    counts = log_svc.action_counts(db, [env['done'].id])
    bucket = counts[env['done'].id]
    assert bucket['done'] == 3, f'成功动作没被算进 done 桶：{bucket}'
    assert bucket['failed'] == 0 and bucket['pending'] == 0
    # 原样状态值另存一份，方便以后加状态而不用改桶的代码
    assert bucket['statuses'] == {'ok': 3}


def test_action_counts_keeps_unknown_status_out_of_the_known_buckets(env):
    """库里出现没见过的状态时，不能悄悄算进 done / failed 里。"""
    db = env['db']
    db.add(InspectionActionResult(run_id=env['done'].id, status='weird'))
    db.commit()
    bucket = log_svc.action_counts(db, [env['done'].id])[env['done'].id]
    assert bucket['total'] == 4
    assert bucket['done'] == 3          # 没被污染
    assert bucket['other'] == 1
    assert bucket['statuses']['weird'] == 1


def test_empty_inputs_do_not_hit_the_database(env):
    """空列表要短路返回，别拿 `in_([])` 去查库（SQLite 会报警告、也没必要）。"""
    db = env['db']
    assert log_svc.action_counts(db, []) == {}
    assert log_svc.legacy_counts(db, []) == {}
    assert log_svc.detect_counts(db, []) == {}
    assert log_svc.robot_names(db, [None, None]) == {}


def test_robot_names_resolves_and_skips_nulls(env):
    db = env['db']
    names = log_svc.robot_names(db, [env['r1'].id, env['r2'].id, None])
    assert names[env['r1'].id] == '一号机'
    assert names[env['r2'].id] == '二号机'
    assert len(names) == 2


# ---------------------------------------------------------------- 接口层
#
# 上面测的是纯函数，这一节测**路由真的把 service 接上了**（import 漏了、
# 参数名写错、响应形状不对，纯函数测试都是绿的）。用 FastAPI TestClient +
# 临时库，不走真实鉴权。

@pytest.fixture
def client(env, monkeypatch):
    """把 router 挂到一个只带临时库的最小 app 上，鉴权依赖直接放过。"""
    from fastapi import FastAPI
    from fastapi.testclient import TestClient
    from app.database import get_db
    from app.auth import get_current_user
    from app.routers import inspection as insp_router

    app = FastAPI()
    app.include_router(insp_router.router)

    def _override_db():
        yield env['db']

    app.dependency_overrides[get_db] = _override_db
    app.dependency_overrides[get_current_user] = lambda: {'id': 1, 'role': 'engineer'}
    return TestClient(app)


def test_list_runs_returns_every_run_paged(client, env):
    """这是本次需求的核心断言：一个 robot_pk 都不传也要看到全部记录。"""
    r = client.get('/api/inspection/runs', params={'page': 1, 'page_size': 10})
    assert r.status_code == 200
    body = r.json()
    assert set(body) >= {'total', 'items', 'page', 'page_size'}
    assert body['total'] == 3
    assert {it['inspection_id'] for it in body['items']} == {
        'INSP-DONE', 'INSP-STALLED', 'INSP-FAILED'}
    # 机器人名字跟着带出来（前端拿外键没法显示）
    by_id = {it['inspection_id']: it for it in body['items']}
    assert by_id['INSP-DONE']['robot_name'] == '一号机'
    assert by_id['INSP-FAILED']['robot_name'] is None


def test_list_runs_keeps_the_legacy_bare_array(client):
    """不传 page 的老形态必须还是裸数组，且字段是旧集合的超集。

    别的页面（以及可能还在跑的旧前端）依赖它，改成对象会让它们直接白屏。
    """
    r = client.get('/api/inspection/runs')
    assert r.status_code == 200
    body = r.json()
    assert isinstance(body, list) and len(body) == 3
    legacy_keys = {'id', 'inspection_id', 'robot_pk', 'status',
                   'total_actions', 'done_actions', 'start_time',
                   'finish_time', 'remark', 'progress'}
    assert legacy_keys <= set(body[0]), legacy_keys - set(body[0])


def test_list_runs_filters(client, env):
    assert client.get('/api/inspection/runs',
                      params={'page': 1, 'robot_pk': env['r1'].id}).json()['total'] == 1
    assert client.get('/api/inspection/runs',
                      params={'page': 1, 'status': 'failed'}).json()['total'] == 1
    assert client.get('/api/inspection/runs',
                      params={'page': 1, 'keyword': '夜巡'}).json()['items'][0]['inspection_id'] \
        == 'INSP-STALLED'


def test_run_actions_endpoint(client, env):
    r = client.get(f"/api/inspection/runs/{env['done'].id}/actions")
    assert r.status_code == 200
    body = r.json()
    assert body['run_id'] == env['done'].id
    assert body['summary']['status'] == {'ok': 3}
    assert body['summary']['dispatch'] == {'done': 3}
    assert len(body['items']) == 3
    # 分发五件套必须在响应里（缺了页面就分不清"执行完了"和"送出去了"）
    for key in ('dispatch_status', 'dispatch_mode', 'dispatch_attempts',
                'dispatched_at', 'dispatch_error'):
        assert key in body['items'][0]
    assert body['items'][0]['action_type_name'] == '拍照'


def test_run_points_endpoint_and_kind_filter(client, env):
    r = client.get(f"/api/inspection/runs/{env['done'].id}/points")
    assert r.status_code == 200
    body = r.json()
    assert body['summary']['total'] == 2
    assert body['summary']['passed'] == 1 and body['summary']['failed'] == 1
    # 测点要带上自己动作的类型/图片，页面不用再去查一遍
    assert body['items'][0]['action_type_name'] == '拍照'

    only_thermo = client.get(f"/api/inspection/runs/{env['done'].id}/points",
                             params={'kind': 'thermometry'}).json()
    assert only_thermo['summary']['total'] == 0
    only_detect = client.get(f"/api/inspection/runs/{env['done'].id}/points",
                             params={'kind': 'detect'}).json()
    assert only_detect['summary']['total'] == 2


def test_run_summary_endpoint_matches_the_list_row(client, env):
    """独立详情页拿标题靠这个接口 —— 口径必须与**列表里那一条**逐字段一致。

    如果这里另算一套（哪怕只是漏了 robot_name），就会出现"从列表点进去"和
    "直接输 URL 进来"显示不同数字的诡异现象，而且极难查。
    """
    run_id = env['done'].id
    one = client.get(f'/api/inspection/runs/{run_id}/summary')
    assert one.status_code == 200
    row = one.json()

    listed = client.get('/api/inspection/runs',
                        params={'page': 1, 'page_size': 50}).json()['items']
    same = next(x for x in listed if x['id'] == run_id)
    assert row == same, 'summary 与列表行必须完全一致'


def test_run_summary_endpoint_404_on_a_missing_run(client):
    assert client.get('/api/inspection/runs/9999/summary').status_code == 404


def test_list_accepts_the_date_formats_a_datepicker_sends(client, env):
    """DatePicker 传的是 `YYYY-MM-DD HH:mm`。解析失败不能 500。"""
    ok = client.get('/api/inspection/runs', params={
        'page': 1, 'start': '2020-01-01 00:00', 'end': '2099-12-31 23:59'})
    assert ok.status_code == 200 and ok.json()['total'] == 3
    # 垃圾输入不该炸，只是筛不出东西
    junk = client.get('/api/inspection/runs', params={'page': 1, 'start': '不是时间'})
    assert junk.status_code == 200

