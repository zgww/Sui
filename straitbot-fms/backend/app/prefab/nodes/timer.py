"""定时类节点：CronTimer（APScheduler 注册）与 IntervalTimer（tick 驱动）。"""
from __future__ import annotations

from apscheduler.triggers.cron import CronTrigger
from pydantic import PrivateAttr

from ..base import Context, NodeBase, ui_field


class CronTimer(NodeBase):
    """按 cron 表达式触发：on_active 时向运行时调度器注册，失活时注销。

    到点后向 Context 事件总线 emit "timer" 事件，整树节点可订阅。
    """

    cron: str = ui_field("text", group="调度",
                         description="cron 表达式，如 0 2 * * *（每天 02:00）")

    def on_active(self, ctx: Context) -> None:
        sched = ctx.kv.get("__scheduler__")
        if sched is None:
            raise RuntimeError("运行时未提供调度器，CronTimer 无法注册")
        job_id = self._job_id()

        def fire() -> None:
            ctx.emit("timer", {"type": "cron", "node": self.name,
                               "cron": self.cron})

        sched.add_job(fire, CronTrigger.from_crontab(self.cron),
                      id=job_id, replace_existing=True, misfire_grace_time=30)

    def on_deactive(self, ctx: Context) -> None:
        sched = ctx.kv.get("__scheduler__")
        if sched is not None:
            try:
                sched.remove_job(self._job_id())
            except Exception:
                pass

    def _job_id(self) -> str:
        return f"prefab-cron-{id(self)}"


class IntervalTimer(NodeBase):
    """按固定秒数间隔触发：由树 tick 驱动计数，到点 emit "timer" 事件。"""

    interval: float = ui_field("number", min=0.1, max=86400, group="调度",
                               description="触发间隔（秒）")

    _elapsed: float = PrivateAttr(default=0.0)

    def on_active(self, ctx: Context) -> None:
        self._elapsed = 0.0

    def on_tick(self, ctx: Context, dt: float) -> None:
        self._elapsed += dt
        if self._elapsed >= self.interval:
            self._elapsed = 0.0
            ctx.emit("timer", {"type": "interval", "node": self.name,
                               "interval": self.interval})
