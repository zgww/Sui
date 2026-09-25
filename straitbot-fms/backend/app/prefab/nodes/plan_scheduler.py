"""巡检计划调度节点：起后台线程，按「每日调度」到点触发巡检任务。

配在 `data/prefabs/启动.prefab.json` 里（程序启动时这棵树会被加载并激活，
见 `routers/prefab.startup_prefab`）：节点 `on_active` 起一个**守护线程**，
每 `poll_interval` 秒扫一遍 `data/prefabs/plan` 下的计划文件，算出这一刻该
触发哪些计划，然后触发；`on_deactive` 停线程（停机要能干净退出）。

判断"该不该触发"的全部逻辑在 `app/prefab/plan_scheduler.py`（纯函数，有单测），
本文件只管线程与回调。

## ⚠️ 默认不下发（`dry_run=True`）

真下发 = 把一条计划变成设备动作：读计划的「航点指定」指向的航点树，让每个节点
自己组织航点/动作/测温字段，汇总成巡检任务 JSON，再交给机器人
（`Robot.接收巡检任务`）。这条链路已经接好，就是 `plan_scheduler.dispatch_inspection`
——`startup_prefab` 会把它装成默认回调。

但因为"到点就发车"是会动真格设备的动作，**节点默认 `dry_run=True`**：只记日志 +
emit `inspection_due` 事件。配上去先观察，确认时刻和内容都对，再把 `dry_run` 的
勾去掉。想换一套下发逻辑（比如先发审批、或只通知不下发）就自己注册：

    from app.prefab.plan_scheduler import set_inspection_trigger
    set_inspection_trigger(my_dispatch_fn)   # payload -> None

必须在 `startup_prefab` 之前注册，否则 `install_default_trigger` 会先把默认的装上
（它不覆盖已有注册）。
"""
from __future__ import annotations

import logging
import threading
from datetime import datetime
from typing import Any, Optional
from zoneinfo import ZoneInfo, ZoneInfoNotFoundError

from pydantic import PrivateAttr

from ..base import Context, NodeBase, ui_field
from ..plan_scheduler import (
    PlanSchedulerState, collect_jobs, due_slots, get_inspection_trigger,
)

logger = logging.getLogger(__name__)


class InspectionPlanSchedulerNode(NodeBase):
    """巡检计划调度：定时扫 `data/prefabs/plan` 下的计划，到点触发巡检任务。

    一个文件（计划树）里可挂多条 `InspectionPlanNode`，每条下面挂
    「每日调度」（时间范围 + 间隔）+「航点指定」/「测点指定」。到点后：

    - `dry_run=True`（默认）：记日志 + emit `inspection_due` 事件；
    - `dry_run=False`：调 `set_inspection_trigger()` 注册的回调（没注册则退回
      dry_run 行为并警告一次——绝不能"以为在下发其实没发"）。
    """

    plan_dir: str = ui_field("text", group="调度", default="", title="计划目录",
                             description="巡检计划编排目录；留空 = data/prefabs/plan")
    poll_interval: float = ui_field("number", min=1, max=3600, group="调度", default=30,
                                    title="扫描间隔（秒）",
                                    description="扫一遍计划文件的间隔；应小于巡检间隔，否则会漏点")
    timezone: str = ui_field("text", group="调度", default="Asia/Shanghai", title="时区",
                             description="计划里 HH:MM 所用时区，如 Asia/Shanghai")
    misfire_grace: int = ui_field("number", min=0, max=86400, group="调度", default=300,
                                  title="容错窗口（秒）",
                                  description="迟到超过这么多秒就不触发了；停机期间攒下的时刻不补")
    robot_name: str = ui_field("text", group="调度", default="", title="目标机器人",
                               description="只处理这个机器人的计划（未指定机器人的计划也处理）；留空=不限")
    dry_run: bool = ui_field("checkbox", group="调度", default=True, title="演练（不下发）",
                             description="只记日志并 emit inspection_due 事件；去掉勾选才会调 set_inspection_trigger 注册的下发回调")

    _thread: Optional[threading.Thread] = PrivateAttr(default=None)
    _stop: Optional[threading.Event] = PrivateAttr(default=None)
    _ctx: Optional[Context] = PrivateAttr(default=None)
    # ⚠️ 不能叫 `_state`：那是 NodeBase 的节点状态（inactive/active/error）
    _ledger: Optional[PlanSchedulerState] = PrivateAttr(default=None)
    _warned_no_trigger: bool = PrivateAttr(default=False)

    # ------------------------------------------------------------ 生命周期

    def on_active(self, ctx: Context) -> None:
        # 注意是 `...config`：本模块在 app/prefab/nodes/ 下，两级向上才是 app/
        from ...config import DATA_DIR, PLAN_PREFAB_DIR
        from pathlib import Path

        root = Path(self.plan_dir) if self.plan_dir.strip() else PLAN_PREFAB_DIR
        if not root.exists():
            logger.warning("[prefab] %s: 计划目录不存在: %s", self.name or self.type, root)

        self._ctx = ctx
        self._ledger = PlanSchedulerState(Path(DATA_DIR) / "plan_scheduler_state.json")
        self._stop = threading.Event()
        self._thread = threading.Thread(
            target=self._run, args=(root,), name="prefab-plan-scheduler", daemon=True)
        self._thread.start()
        logger.info("[prefab] %s: 巡检计划调度已启动（目录 %s，间隔 %ss，dry_run=%s）",
                    self.name or self.type, root, self.poll_interval, self.dry_run)

    def on_deactive(self, ctx: Context) -> None:
        stop = self._stop
        if stop is not None:
            stop.set()
        th = self._thread
        # 最多等两个扫描周期：线程里没有阻塞操作，等它是为了让"停机"在日志里看得见
        if th is not None and th.is_alive():
            th.join(timeout=max(1.0, float(self.poll_interval) * 2))
        self._thread, self._stop, self._ctx, self._ledger = None, None, None, None
        logger.info("[prefab] %s: 巡检计划调度已停止", self.name or self.type)

    # ------------------------------------------------------------ 线程体

    def _run(self, root) -> None:
        stop = self._stop
        while stop is not None and not stop.is_set():
            try:
                self._scan_once(root)
            except Exception:
                # 一次扫描出错不能让线程死掉（否则"调度悄无声息停了"）
                logger.exception("[prefab] %s: 巡检计划扫描异常",
                                 self.name or self.type)
            if stop is not None:
                stop.wait(max(1.0, float(self.poll_interval)))

    def _scan_once(self, root) -> None:
        jobs, errors = collect_jobs(root, robot_name=self.robot_name.strip())
        for err in errors:
            logger.warning("[prefab] %s: 计划文件有问题: %s", self.name or self.type, err)
        if not jobs:
            return

        now = self._now()
        ledger = self._ledger
        for job in jobs:
            for sched in job.schedules:
                since = ledger.last(job.key) if ledger is not None else None
                slots = due_slots(sched, now, since, self.misfire_grace)
                if not slots:
                    continue
                # 只补**最后一个**到期槽位：停机期间攒下的不补（见模块 docstring）
                slot = slots[-1]
                if ledger is not None and not ledger.mark(job.key, slot):
                    continue
                self._fire(job, sched, slot)

    def _now(self) -> datetime:
        try:
            return datetime.now(ZoneInfo(self.timezone))
        except (ZoneInfoNotFoundError, ValueError):
            logger.warning("[prefab] %s: 时区无效(%s)，回退系统本地时间",
                           self.name or self.type, self.timezone)
            return datetime.now()

    # ------------------------------------------------------------ 触发

    def _fire(self, job, sched, slot: datetime) -> None:
        payload = job.payload(slot, sched)
        trigger = None if self.dry_run else get_inspection_trigger()
        if trigger is None:
            if not self.dry_run and not self._warned_no_trigger:
                self._warned_no_trigger = True
                logger.warning(
                    "[prefab] %s: dry_run 已关闭但没有注册下发回调"
                    "（set_inspection_trigger），本次只记日志", self.name or self.type)
            logger.info("[prefab] %s: 巡检计划到期 %s %s（计划 %s/%s，dry_run）",
                        self.name or self.type, job.plan_name,
                        slot.strftime("%Y-%m-%d %H:%M"), job.file, sched.label or "调度")
            ctx = self._ctx
            if ctx is not None:
                ctx.emit("inspection_due", {"node": self.name, "dry_run": True, **payload})
            return
        try:
            result = trigger(payload)
            # 下发回调返回 dict 时（dispatch_inspection）能看出机器人到底接没接：
            # 拒了要按 warning 记，否则日志里"已触发"看着像成功了其实没发车
            accepted = True
            why = ""
            if isinstance(result, dict):
                accepted = result.get("accepted") is not False
                why = str(result.get("reason") or "")
            if accepted:
                logger.info("[prefab] %s: 已下发巡检 %s %s（计划 %s，航点%s 动作%s）",
                            self.name or self.type, job.plan_name,
                            slot.strftime("%Y-%m-%d %H:%M"), job.file,
                            result.get("waypoint_count", "?") if isinstance(result, dict) else "?",
                            result.get("action_count", "?") if isinstance(result, dict) else "?")
            else:
                logger.warning("[prefab] %s: 巡检 %s %s 未下发（%s）",
                               self.name or self.type, job.plan_name,
                               slot.strftime("%Y-%m-%d %H:%M"), why or "被拒绝")
            ctx = self._ctx
            if ctx is not None:
                ev = {"node": self.name, "dry_run": False, **payload}
                if isinstance(result, dict):
                    ev["result"] = result
                ctx.emit("inspection_due", ev)
        except Exception as exc:
            # 下发失败**不**回滚账本：这一刻已经"用掉"了，回滚只会下一轮再发一次
            logger.exception("[prefab] %s: 触发巡检失败 %s: %s",
                             self.name or self.type, job.plan_name, exc)

    # ------------------------------------------------------------ 状态展示

    def status(self) -> dict[str, Any]:
        """给运维看的一小份状态（日志 / 后续接口用）。"""
        return {
            "node": self.name or self.type,
            "running": bool(self._thread and self._thread.is_alive()),
            "plan_dir": self.plan_dir,
            "poll_interval": self.poll_interval,
            "dry_run": self.dry_run,
        }
