"""Local civil-time schedules, persisted as UTC instants. No device I/O."""
from datetime import date, datetime, time, timedelta, timezone
from typing import Literal
from zoneinfo import ZoneInfo, ZoneInfoNotFoundError
from pydantic import BaseModel, Field, model_validator


class PlanSchedule(BaseModel):
    mode: Literal["manual", "once", "daily", "weekly"] = "manual"
    timezone: str = "Asia/Shanghai"
    start_date: date | None = None
    end_date: date | None = None
    time: str = "09:00"
    weekdays: list[int] = Field(default_factory=list)

    @model_validator(mode="after")
    def valid(self):
        try:
            ZoneInfo(self.timezone)
        except (ZoneInfoNotFoundError, ValueError):
            raise ValueError("无效时区")
        try:
            parsed = time.fromisoformat(self.time)
            if len(self.time) != 5 or parsed.tzinfo:
                raise ValueError()
        except ValueError:
            raise ValueError("执行时间必须为 HH:mm")
        if self.mode != "manual" and self.start_date is None:
            raise ValueError("请选择开始日期")
        if self.end_date and self.start_date and self.end_date < self.start_date:
            raise ValueError("结束日期不能早于开始日期")
        if any(type(d) is not int or not 0 <= d <= 6 for d in self.weekdays) or len(set(self.weekdays)) != len(self.weekdays):
            raise ValueError("星期必须为不重复的 0–6（周一至周日）")
        if self.mode == "weekly" and not self.weekdays:
            raise ValueError("每周计划至少选择一天")
        return self


def next_occurrence(schedule, after):
    s = PlanSchedule.model_validate(schedule)
    if s.mode == "manual":
        return None
    zone = ZoneInfo(s.timezone)
    after = after.replace(tzinfo=timezone.utc) if after.tzinfo is None else after.astimezone(timezone.utc)
    day = max(s.start_date, after.astimezone(zone).date())
    # Weekly recurrence needs at most eight civil dates; once has one candidate.
    for offset in range(9):
        d = day + timedelta(days=offset)
        if s.end_date and d > s.end_date or s.mode == "once" and d != s.start_date:
            return None
        if s.mode == "weekly" and d.weekday() not in s.weekdays:
            continue
        local = datetime.combine(d, time.fromisoformat(s.time), zone)
        utc = local.astimezone(timezone.utc)
        # Skip nonexistent local times on DST jumps; fold=0 runs repeated times once.
        if utc.astimezone(zone).replace(tzinfo=None) != local.replace(tzinfo=None):
            continue
        if utc > after:
            return utc.replace(tzinfo=None)
    return None
