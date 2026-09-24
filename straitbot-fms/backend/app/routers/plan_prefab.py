"""巡检计划编排 API：基于 prefab 机制的纯数据计划树。

与航点树编排（`/api/waypoint-prefab`）的关系：
- 同一套机制、同一套接口形状（目录/文件 CRUD + 树读写 + node-types），
  由 `prefab_store.make_prefab_router` 生成，只是换了根目录与类型过滤；
- 根目录固定为 `data/prefabs/plan`（可嵌套目录、多个 *.prefab.json）；
- 节点类型仅暴露计划系（`PlanNodeBase` 子类：巡检计划 / 分组 / 航点指定 /
  测点指定 / 每日调度），**不会**混进航点系的类型——两棵树的类型目录必须分开，
  否则"添加子节点"里选中一个航点节点，就会在计划树里存出一个本树读不懂的脏节点；
- 同样只做文件读写与 `registry.build` 校验，不激活、不进规则 runtime。

⚠️ **本接口目前只负责"编排数据"**：把计划树存下来、读回来、校验结构。
真正按计划触发巡检的是另一套（`/api/inspection-plans` + 数据库 + 调度器）。
两边的对接（计划树 -> 调度配置）尚未做，见 `prefab/nodes/plan.py` 的模块 docstring。
"""
from datetime import datetime
from typing import Any
import json

from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel, Field

from ..auth import engineer_only
from ..config import PLAN_PREFAB_DIR
from .prefab_store import make_prefab_router


def _plan_root(name: str) -> dict[str, Any]:
    """新建计划树文件时的初始 spec：一个**空分组**当根。

    根用 PlanGroupNode 而不是 InspectionPlanNode：一个文件只有一个根，
    根是单条计划就等于"一个文件只能配一条计划"——给同一台机器人排"白天每小时
    一遍、夜里两小时一遍"得开两个文件，航点树 `source` 之类的配置还要抄两遍。
    根是分组，下面挂 N 条 InspectionPlanNode，计划编号 / 目标机器人 / 优先级
    这些元信息仍然挂在**每条计划自己身上**，不会流离失所。

    与航点树（`_group_root` 建一个空 GroupNode 根）是同一个套路：根只是容器，
    内容由用户在树上加。

    老文件的根可能是单条计划（早期就那么建的）：前端读取时用
    `planSelect.ensureGroupRoot` 在内存里包一层分组，**不写盘**，
    用户点保存才落盘（见 frontend/src/views/InspectionPlanPrefab.tsx）。
    """
    return {
        "name": name,
        "description": "",
        "root": {
            "type": "PlanGroupNode",
            "properties": {"name": name, "enabled": True, "description": ""},
            "children": [],
        },
    }


router = make_prefab_router(
    prefix="/api/plan-prefab",
    tag="plan-prefab",
    root_dir=PLAN_PREFAB_DIR,
    base_filter="PlanNodeBase",
    root_spec_factory=_plan_root,
)


# ---------------------------------------------------------------- 立即执行

class ExecuteIn(BaseModel):
    """「立即执行」的入参。"""

    #: 计划文件相对路径（`data/prefabs/plan` 下，如 `floor1.prefab.json`）
    rel_path: str = Field(min_length=1)
    #: 树内节点路径（前端树节点的 `value`），如 `root/children/0`
    node_path: str = Field(min_length=1)


def _safe_plan_file(rel_path: str):
    """把 `rel_path` 收窄到计划目录下的 `*.prefab.json`（防目录穿越）。"""
    rel = str(rel_path or "").strip().strip("/\\").replace("\\", "/")
    if not rel:
        raise HTTPException(status_code=422, detail="rel_path 必填")
    if not rel.endswith(".prefab.json"):
        raise HTTPException(status_code=422, detail="计划文件必须以 .prefab.json 结尾")
    root = PLAN_PREFAB_DIR.resolve()
    p = (root / rel).resolve()
    if p != root and root not in p.parents:
        raise HTTPException(status_code=400, detail="路径越界")
    if not p.is_file():
        raise HTTPException(status_code=404, detail=f"计划文件不存在: {rel}")
    return rel, p


@router.post("/execute", dependencies=[Depends(engineer_only)])
def execute_plan_now(body: ExecuteIn):
    """**立即执行**一条「巡检计划」：现在就把它下发给机器人，不等排期。

    与定时触发（`InspectionPlanSchedulerNode`）的区别只有"谁决定时机"：
    下发走的是**同一条链路**（`plan_job_at` 抽计划 -> `dispatch_inspection`
    组装并交给机器人），所以"立即执行"和"到点自动跑"产生的是同一种巡检任务，
    不会两套行为。

    几个刻意的选择：

    - **只读磁盘文件**（`PLAN_PREFAB_DIR` 下按 rel_path 读），不吃前端传上来的
      树内容。理由：执行的是"这个文件里那条计划"，而不是"编辑器里此刻的样子"——
      前端可能还没保存，拿内存态执行会出现"跑的东西和文件对不上账"，事后没法复现。
      要执行新改的内容，先保存。
    - **不要求「每日调度」**（见 `plan_job_at`）：草稿计划也该能试跑。
    - **不写账本**（`plan_scheduler_state.json`）：账本是给定时触发去重用的，
      手动执行不该占用某个槽位，否则"我刚手动跑过，到点反而不跑了"。
    - **不做"是否在忙"的前置检查**：机器人接不接由
      `dispatch_inspection` 里的 `接收巡检任务` 自己判（忙就是 `busy`），
      这里只把结果如实返回，前端弹提示。

    返回 `dispatch_inspection` 的结果：`accepted=True` 时含 `inspection_id` /
    `waypoint_count` / `action_count` / `floors` / `detect_type`；
    被拒时 `accepted=False` 并带 `reason`（如 `busy`）。

    ⚠️ 这是**会动真格设备**的接口（机器人会出发），所以用 `engineer_only`。
    """
    # 延迟导入：本模块被 `routers/__init__` 早期导入，顶层拖进整个调度链
    # （含 robot / rail 的重依赖）容易在启动阶段绕出循环导入。
    from ..prefab.inspection_build import build_from_plan
    from ..prefab.plan_scheduler import dispatch_inspection, plan_job_at

    rel, path = _safe_plan_file(body.rel_path)
    try:
        spec = json.loads(path.read_text(encoding="utf-8"))
    except Exception as exc:
        raise HTTPException(status_code=422, detail=f"读取计划文件失败: {exc}") from exc

    try:
        job = plan_job_at(spec, body.node_path, file_rel=rel)
    except ValueError as exc:
        # 路径不对 / 不是计划节点 / 已停用 —— 都是"你点错了"，不是服务出错
        raise HTTPException(status_code=422, detail=str(exc)) from exc
    if job is None:
        raise HTTPException(status_code=422, detail="这条计划没有可执行的内容")

    # 手动执行没有"到期时刻"，用当前时间填进 payload 的 scheduled_at
    # （`build_from_plan` 不读它，但下发记录/日志里要有）
    from datetime import datetime
    payload = job.payload(datetime.now(), job.schedules[0] if job.schedules else None)
    payload["trigger"] = "manual"

    try:
        result = dispatch_inspection(payload)
    except Exception as exc:        # dispatch_inspection 声明全程不抛，这里只是兜底
        raise HTTPException(status_code=500, detail=f"下发失败: {exc}") from exc

    # 组装失败 / 被机器人拒（busy）：不是 HTTP 错误，是业务结果。
    # 一律 200 + accepted=false，让前端按 reason 提示 —— 用 4xx 的话
    # 前端的 http 拦截器会先弹一个通用 Toast，我们自己的提示反而看不清。
    return {"rel_path": rel, "node_path": body.node_path, **result}

