"""巡检计划调度节点背后的纯逻辑。

这里锁的是"到点触发"这件事最容易悄悄错的地方：
- 计划抽取（停用跳过、没调度不触发、计划里嵌套分组也要收得到）；
- 时刻展开（末次不晚于 end、跨零点不排、间隔非法不排）；
- **去重**：同一时刻被扫到两次只能触发一次，且**重启后也不能重发**；
- **停机容错**：停机很久后重启，过期槽位不补。

节点类本身（线程起停）不在这里测——它需要真线程和运行时，交给冒烟。
"""
import json
from datetime import datetime, timedelta, timezone
from pathlib import Path

import pytest

from app.prefab.plan_scheduler import (
    PlanSchedulerState, ScheduleSpec, collect_jobs, due_slots, parse_hm,
    normalize_detect_type, plan_job_at,
)

TZ = timezone(timedelta(hours=8))          # 固定时区，测试不依赖机器时区
DAY = datetime(2026, 9, 21, tzinfo=TZ)     # 周一


def at(h, m=0):
    return DAY.replace(hour=h, minute=m)


def plan_file(tmp_path: Path, name: str, root: dict) -> Path:
    p = tmp_path / name
    p.write_text(json.dumps({"name": name, "description": "", "root": root},
                            ensure_ascii=False), encoding="utf-8")
    return p


def plan(name="计划", plan_id="", children=(), enabled=True, robot_name="", priority=0):
    return {
        "type": "InspectionPlanNode",
        "properties": {"name": name, "plan_id": plan_id, "enabled": enabled,
                       "robot_name": robot_name, "priority": priority},
        "children": list(children),
    }


def sched(start="08:00", end="18:00", interval=60, name="调度", enabled=True):
    return {"type": "DailyScheduleNode",
            "properties": {"name": name, "enabled": enabled,
                           "start_time": start, "end_time": end,
                           "interval_minutes": interval}}


def wp(source="floor1.prefab.json", ids=("A-1",), include_all=False):
    return {"type": "WaypointSelectNode",
            "properties": {"name": "航点指定", "enabled": True, "source": source,
                           "include_all": include_all, "waypoint_ids": list(ids)}}


def pts(ids=("P-1",), include_all=False):
    return {"type": "PointSelectNode",
            "properties": {"name": "测点指定", "enabled": True,
                           "include_all": include_all, "point_ids": list(ids)}}


def group(children, name="分组"):
    return {"type": "PlanGroupNode", "properties": {"name": name, "enabled": True},
            "children": list(children)}


# ------------------------------------------------------------ 扫描与抽取

def test_collect_one_plan(tmp_path):
    plan_file(tmp_path, "a.prefab.json",
              group([plan("日常", "P-1", [wp(), pts(), sched()])]))
    jobs, errors = collect_jobs(tmp_path)
    assert errors == []
    assert len(jobs) == 1
    j = jobs[0]
    assert j.plan_name == "日常" and j.plan_id == "P-1"
    assert len(j.schedules) == 1 and j.schedules[0].interval == 60
    assert j.waypoints[0]["source"] == "floor1.prefab.json"
    assert j.waypoints[0]["waypoint_ids"] == ["A-1"]
    assert j.points[0]["point_ids"] == ["P-1"]


def test_many_plans_in_one_file(tmp_path):
    """一个文件多条计划（根是分组的意义所在）：每条各自触发。"""
    plan_file(tmp_path, "multi.prefab.json",
              group([plan("白天", "P-1", [sched(interval=60)]),
                     plan("夜间", "P-2", [sched(interval=120)])]))
    jobs, _ = collect_jobs(tmp_path)
    assert [j.plan_id for j in jobs] == ["P-1", "P-2"]


def test_nested_group_inside_plan(tmp_path):
    plan_file(tmp_path, "n.prefab.json",
              group([plan("计划", "P-1", [group([wp(), sched()], name="子分组")])]))
    jobs, _ = collect_jobs(tmp_path)
    assert len(jobs) == 1
    assert len(jobs[0].waypoints) == 1 and len(jobs[0].schedules) == 1


def test_plan_without_schedule_is_skipped(tmp_path):
    """没有「每日调度」= 没有周期，不该触发（连日志都不该刷）。"""
    plan_file(tmp_path, "nos.prefab.json", group([plan("无调度", "P-1", [wp()])]))
    jobs, errors = collect_jobs(tmp_path)
    assert jobs == [] and errors == []


def test_disabled_nodes_are_skipped(tmp_path):
    plan_file(tmp_path, "d.prefab.json", group([
        plan("停用计划", "P-1", [sched()], enabled=False),
        plan("启用计划", "P-2", [sched(enabled=False)]),   # 调度被停用
        plan("正常", "P-3", [sched()]),
    ]))
    jobs, _ = collect_jobs(tmp_path)
    assert [j.plan_id for j in jobs] == ["P-3"]


def test_robot_filter(tmp_path):
    plan_file(tmp_path, "r.prefab.json", group([
        plan("给R1", "P-1", [sched()], robot_name="R1"),
        plan("不限", "P-2", [sched()]),
        plan("给R2", "P-3", [sched()], robot_name="R2"),
    ]))
    all_jobs, _ = collect_jobs(tmp_path)
    assert len(all_jobs) == 3
    r1, _ = collect_jobs(tmp_path, robot_name="R1")
    # 不限机器人的计划也要带上（"这条机器人也要跑"）
    assert sorted(j.plan_id for j in r1) == ["P-1", "P-2"]


def test_bad_file_reports_error_not_crash(tmp_path):
    (tmp_path / "broken.prefab.json").write_text("{不是 json", encoding="utf-8")
    plan_file(tmp_path, "ok.prefab.json", group([plan("好", "P-1", [sched()])]))
    jobs, errors = collect_jobs(tmp_path)
    assert len(jobs) == 1 and len(errors) == 1 and "broken" in errors[0]


def test_key_prefers_plan_id(tmp_path):
    """去重主键优先用 plan_id：改名字不会导致重复触发。"""
    plan_file(tmp_path, "k.prefab.json",
              group([plan("有编号", "P-1", [sched()]), plan("没编号", "", [sched()])]))
    jobs, _ = collect_jobs(tmp_path)
    assert jobs[0].key.endswith("#P-1")
    assert jobs[1].key.endswith("#没编号")


# ------------------------------------------------------------ 时刻展开

def test_parse_hm():
    assert parse_hm("08:30") == 510
    assert parse_hm("8:05") == 485
    assert parse_hm("8:5") is None
    assert parse_hm("24:00") is None
    assert parse_hm("") is None
    assert parse_hm(830) is None


def test_due_slots_basic():
    """grace 放大到一天 -> 看**当天**全部时刻（与前端 scheduleSlots 同一套展开）。"""
    s = ScheduleSpec("08:00", "18:00", 60)
    slots = due_slots(s, at(12, 0), grace_seconds=86400)
    assert [x.strftime("%H:%M") for x in slots] == ["08:00", "09:00", "10:00", "11:00", "12:00"]


def test_due_slots_last_not_later_than_end():
    s = ScheduleSpec("08:00", "18:30", 60)
    slots = due_slots(s, at(23, 0), grace_seconds=86400)
    assert slots[-1].strftime("%H:%M") == "18:00"      # 不排 19:00


def test_due_slots_same_start_end():
    slots = due_slots(ScheduleSpec("09:00", "09:00", 30), at(10, 0), grace_seconds=86400)
    assert [x.strftime("%H:%M") for x in slots] == ["09:00"]


def test_due_slots_cross_midnight_not_scheduled():
    """跨零点刻意不支持（夜间巡检拆成两条计划）。"""
    assert due_slots(ScheduleSpec("22:00", "06:00", 60), at(23, 0)) == []


def test_due_slots_invalid_inputs():
    assert due_slots(ScheduleSpec("8:5", "18:00", 60), at(12, 0)) == []
    assert due_slots(ScheduleSpec("08:00", "18:00", 0), at(12, 0)) == []
    assert due_slots(ScheduleSpec("08:00", "18:00", -1), at(12, 0)) == []


def test_due_slots_since_filters_already_fired():
    s = ScheduleSpec("08:00", "18:00", 60)
    assert [x.strftime("%H:%M") for x in due_slots(s, at(12, 0), since=at(10, 0),
                                                   grace_seconds=86400)] == ["11:00", "12:00"]


def test_due_slots_misfire_grace():
    """迟到超过容错窗口的槽位不补（停机期间攒下的不补触发）。"""
    s = ScheduleSpec("08:00", "18:00", 60)
    assert due_slots(s, at(12, 10), since=None, grace_seconds=300) == []   # 全过期
    slots = due_slots(s, at(12, 3), since=None, grace_seconds=300)
    assert [x.strftime("%H:%M") for x in slots] == ["12:00"]               # 迟到 3 分钟，还补


# ------------------------------------------------------------ 去重账本

def test_state_mark_once(tmp_path):
    st = PlanSchedulerState(tmp_path / "state.json")
    assert st.mark("k", at(9, 0)) is True
    assert st.mark("k", at(9, 0)) is False      # 同一时刻扫到两次
    assert st.mark("k", at(10, 0)) is True      # 下一个时刻照常
    assert st.last("k") == at(10, 0)


def test_state_survives_restart(tmp_path):
    """重启后账本还在 —— 否则刚触发过的那条会被再发一次。"""
    p = tmp_path / "state.json"
    PlanSchedulerState(p).mark("k", at(9, 0))
    again = PlanSchedulerState(p)
    assert again.last("k") == at(9, 0)
    assert again.mark("k", at(9, 0)) is False


def test_state_broken_file_starts_empty(tmp_path):
    p = tmp_path / "state.json"
    p.write_text("{坏文件", encoding="utf-8")
    st = PlanSchedulerState(p)
    assert st.last("k") is None


def test_state_prunes_old(tmp_path):
    st = PlanSchedulerState(tmp_path / "state.json")
    st.mark("old", DAY - timedelta(days=30))
    st.mark("new", at(9, 0))
    st._prune(DAY)
    assert st.last("old") is None and st.last("new") == at(9, 0)


# ------------------------------------------------------------ 端到端（不启线程）

def test_scan_and_decide(tmp_path):
    """把"扫 + 判 + 记"串起来：同一时刻只触发一次，下一时刻再触发一次。"""
    plan_file(tmp_path, "a.prefab.json",
              group([plan("日常", "P-1", [wp(), pts(), sched("08:00", "18:00", 60)])]))
    st = PlanSchedulerState(tmp_path / "state.json")

    def fire_at(now):
        fired = []
        jobs, _ = collect_jobs(tmp_path)
        for j in jobs:
            for s in j.schedules:
                slots = due_slots(s, now, st.last(j.key), 300)
                if not slots:
                    continue
                slot = slots[-1]
                if st.mark(j.key, slot):
                    fired.append((j.plan_id, slot.strftime("%H:%M")))
        return fired

    assert fire_at(at(9, 0)) == [("P-1", "09:00")]
    assert fire_at(at(9, 1)) == []                 # 同一槽位，扫第二次不重复
    assert fire_at(at(10, 0)) == [("P-1", "10:00")]


def test_payload_shape(tmp_path):
    """触发回调拿到的载荷要能直接 JSON 化（下发/落日志都靠它）。"""
    plan_file(tmp_path, "a.prefab.json",
              group([plan("日常", "P-1", [wp(ids=("A-1", "A-2")), pts(ids=("P-9",)), sched()],
                        robot_name="R1", priority=3)]))
    jobs, _ = collect_jobs(tmp_path)
    payload = jobs[0].payload(at(9, 0), jobs[0].schedules[0])
    assert json.loads(json.dumps(payload, ensure_ascii=False))["plan_id"] == "P-1"
    assert payload["robot_name"] == "R1" and payload["priority"] == 3
    assert payload["waypoints"][0]["waypoint_ids"] == ["A-1", "A-2"]
    assert payload["points"][0]["point_ids"] == ["P-9"]
    assert payload["scheduled_at"].startswith("2026-09-21T09:00:00")


# ------------------------------------------------------------ 检测方式 detect_type
#
# `detect_type` 决定这次巡检的动作数据往哪送（fms 本机跑流程 / platform 上传平台）。
# 这里锁两件最容易搞反的事：**默认值是哪边**、以及**未知值往哪回落**。
#
# ⚠️ 本模块（编排侧）的默认与回退方向都是 `fms`，与两处"看起来同名"的函数
# **刻意不同**：`rail/inspection.py::FloorTask.detect_type` 的缺省是 `platform`
# （要兼容老的下发 JSON），`prefab/task_executor.normalize_detect_type` 也是
# 只有明确写了 `fms` 才本地检测。改这几个默认值前先想清楚是谁在问。

def test_normalize_detect_type_defaults_to_fms():
    """缺省 / 空 -> **fms**（编排侧的显式配置，默认就是"本机检测"）。"""
    assert normalize_detect_type(None) == "fms"
    assert normalize_detect_type("") == "fms"
    assert normalize_detect_type("   ") == "fms"
    assert normalize_detect_type("fms") == "fms"


def test_normalize_detect_type_platform():
    assert normalize_detect_type("platform") == "platform"
    assert normalize_detect_type("PLATFORM") == "platform"      # 大小写不敏感
    assert normalize_detect_type(" Platform ") == "platform"


def test_normalize_detect_type_unknown_falls_back_to_fms():
    """不认识的**不抛错**，回落 fms —— 与 FloorTask（回落 platform）方向相反。"""
    assert normalize_detect_type("xxx") == "fms"
    assert normalize_detect_type(123) == "fms"
    assert normalize_detect_type("本地") == "fms"


def test_plan_detect_type_default_in_job(tmp_path):
    """计划里没写 detect_type -> PlanJob 带 fms，且写进 payload。"""
    plan_file(tmp_path, "a.prefab.json", group([plan("日常", "P-1", [wp(), sched()])]))
    jobs, _ = collect_jobs(tmp_path)
    assert jobs[0].detect_type == "fms"
    assert jobs[0].payload(at(9, 0), jobs[0].schedules[0])["detect_type"] == "fms"


def test_plan_detect_type_platform_from_file(tmp_path):
    p = plan("日常", "P-1", [wp(), sched()])
    p["properties"]["detect_type"] = "platform"
    plan_file(tmp_path, "a.prefab.json", group([p]))
    jobs, _ = collect_jobs(tmp_path)
    assert jobs[0].detect_type == "platform"
    assert jobs[0].payload(at(9, 0), jobs[0].schedules[0])["detect_type"] == "platform"


# ------------------------------------------------------------ 按路径取单条计划（立即执行）

def spec_of(*plans) -> dict:
    """直接拼一棵计划树 spec（不落盘：`plan_job_at` 只吃内存里的 spec）。"""
    return {"name": "t", "description": "", "root": group(list(plans))}


def test_plan_job_at_single():
    spec = spec_of(plan("白天", "P-1", [wp(), sched()]))
    job = plan_job_at(spec, "root/children/0")
    assert job is not None
    assert job.plan_id == "P-1" and job.plan_name == "白天"
    assert len(job.waypoints) == 1


def test_plan_job_at_nested():
    """第 0 个孩子是分组，真正的计划在它下面 —— 路径要能一层层走下去。"""
    spec = spec_of(group([plan("深", "P-9", [wp()])], name="外包一层"))
    job = plan_job_at(spec, "root/children/0/children/0")
    assert job is not None and job.plan_id == "P-9"


def test_plan_job_at_does_not_require_schedule():
    """草稿（只有航点、没配时段）也该能手动试跑 —— 这是与定时触发**唯一**的差别。

    对照：`test_plan_without_schedule_is_skipped` 锁的是"定时那条路上没有调度
    就不触发"，两边合起来才说明这个差别是有意的、不是漏了。
    """
    spec = spec_of(plan("草稿", "P-1", [wp()]))
    job = plan_job_at(spec, "root/children/0")
    assert job is not None
    assert job.schedules == []           # 没调度，但照样能取出来
    assert len(job.waypoints) == 1


def test_plan_job_at_schedule_is_kept_when_present():
    spec = spec_of(plan("带时段", "P-1", [wp(), sched("08:00", "18:00", 60)]))
    job = plan_job_at(spec, "root/children/0")
    assert len(job.schedules) == 1 and job.schedules[0].interval == 60


def test_plan_job_at_rejects_disabled():
    spec = spec_of(plan("停用", "P-1", [wp()], enabled=False))
    with pytest.raises(ValueError, match="停用"):
        plan_job_at(spec, "root/children/0")


def test_plan_job_at_rejects_non_plan_node():
    """分组节点不是计划：对着它点「立即执行」要说清楚，不能静默当成整组。"""
    spec = spec_of(group([plan("里", "P-1", [wp()])]))
    with pytest.raises(ValueError, match="巡检计划"):
        plan_job_at(spec, "root/children/0")
    # 根也是分组，同样拒绝
    with pytest.raises(ValueError, match="巡检计划"):
        plan_job_at(spec, "root")


def test_plan_job_at_rejects_bad_path():
    spec = spec_of(plan("正常", "P-1", [wp()]))
    for bad in ("", "root/children/9", "children/0", "root/0",
                "root/children", "root/children/x", "root/children/-1",
                "root/children/0/children/0/children/0"):
        with pytest.raises(ValueError, match="路径不存在"):
            plan_job_at(spec, bad)


def test_plan_job_at_rejects_child_of_plan():
    """路径确实存在，但落在计划**下面**的子节点上（航点指定）—— 也要说清楚。

    这条别和"路径不存在"混在一起：`root/children/0/children/0` 是能解析出来的，
    只是解析出来的不是计划节点。两类不同的错误给同一条报错，排查时看不出是
    "我路径写错了"还是"我点错了节点"。
    """
    spec = spec_of(plan("正常", "P-1", [wp()]))
    with pytest.raises(ValueError, match="只能立即执行"):
        plan_job_at(spec, "root/children/0/children/0")


def test_plan_job_at_reads_disk_spec_shape(tmp_path):
    """拿真文件读出来的 spec 也要能取到（路径编码与前端树节点 key 一致）。"""
    plan_file(tmp_path, "a.prefab.json", group([
        plan("第一条", "P-1", [wp()]),
        plan("第二条", "P-2", [wp(ids=("B-1",)), sched()]),
    ]))
    spec = json.loads((tmp_path / "a.prefab.json").read_text(encoding="utf-8"))
    first = plan_job_at(spec, "root/children/0", file_rel="a.prefab.json")
    second = plan_job_at(spec, "root/children/1", file_rel="a.prefab.json")
    assert first.plan_id == "P-1" and second.plan_id == "P-2"
    # 文件路径要带进 plan_key（账本/日志靠它区分同名计划）
    assert first.file == "a.prefab.json" and first.key.startswith("a.prefab.json#")

