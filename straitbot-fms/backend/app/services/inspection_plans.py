"""Transactional plan maintenance. Configuration never sends a device command."""
from datetime import datetime
from fastapi import HTTPException
from pydantic import BaseModel, Field, StrictStr, field_validator, model_validator
from ..models import InspectionPlan, InspectionPlanPoint
from .inspection_schedule import PlanSchedule, next_occurrence
from .inspection_compile import compile_route


class PlanStage(BaseModel):
    map_pk: int = Field(gt=0)
    floor: int | None = None
    point_ids: list[StrictStr] = Field(min_length=1, max_length=10000)


class PlanInput(BaseModel):
    robot_pk: int = Field(gt=0)
    map_pk: int | None = Field(default=None, gt=0)
    stages: list[PlanStage] = Field(default_factory=list, max_length=100)
    name: str = Field(min_length=1, max_length=128)
    point_ids: list[StrictStr] = Field(default_factory=list, max_length=10000)
    schedule: PlanSchedule = Field(default_factory=PlanSchedule)
    enabled: bool = False
    version: int | None = Field(default=None, ge=1)

    @field_validator('stages', mode='before')
    @classmethod
    def legacy_null_stages(cls, value):
        return [] if value is None else value

    @model_validator(mode='after')
    def normalize_route(self):
        if self.stages:
            if any(stage.floor is None for stage in self.stages):
                raise ValueError('分段必须指定楼层')
            self.map_pk = self.stages[0].map_pk
            self.point_ids = list(dict.fromkeys(pid for stage in self.stages for pid in stage.point_ids))
            if len(self.point_ids) > 10000:
                raise ValueError('计划最多支持 10000 个测点')
        elif self.map_pk is None or not self.point_ids:
            raise ValueError('请选择地图和测点')
        return self

    @field_validator('name')
    @classmethod
    def trim_name(cls, value):
        if not value.strip():
            raise ValueError('计划名称不能为空')
        return value.strip()


def plan_out(p):
    return {key: getattr(p, key) for key in ('id', 'robot_pk', 'map_pk', 'stages', 'name', 'point_ids', 'schedule', 'enabled', 'version', 'next_run_at', 'created_at', 'updated_at')}


def get_plan(db, plan_id, robot_pk):
    p = db.get(InspectionPlan, plan_id)
    if not p or p.deleted or p.robot_pk != robot_pk:
        raise HTTPException(404, '当前机器人的计划不存在')
    return p


def save_plan(db, store, body, plan_id=None):
    with store.lock:
        p = get_plan(db, plan_id, body.robot_pk) if plan_id else InspectionPlan(robot_pk=body.robot_pk, version=0)
        if plan_id and body.version != p.version:
            raise HTTPException(409, '计划已被修改，请刷新后重试')
        duplicate = db.query(InspectionPlan).filter(InspectionPlan.robot_pk == body.robot_pk,
            InspectionPlan.deleted.is_(False), InspectionPlan.name == body.name)
        if plan_id:
            duplicate = duplicate.filter(InspectionPlan.id != plan_id)
        if duplicate.first():
            raise HTTPException(409, '当前机器人已有同名计划')
        stages = [stage.model_dump() for stage in body.stages] or None
        if body.enabled or not plan_id or p.map_pk != body.map_pk or p.point_ids != body.point_ids or p.stages != stages:
            compile_route(db, store, body.robot_pk, stages or [{'map_pk': body.map_pk, 'point_ids': body.point_ids}], 'preview', body.name)
        schedule = body.schedule.model_dump(mode='json')
        next_at = next_occurrence(schedule, datetime.utcnow()) if body.enabled else None
        if body.enabled and schedule['mode'] != 'manual' and next_at is None:
            raise HTTPException(422, '排期没有未来执行时间，请调整日期')
        p.name, p.map_pk, p.point_ids = body.name, body.map_pk, body.point_ids
        p.stages = stages
        p.schedule, p.enabled, p.next_run_at = schedule, body.enabled, next_at
        p.version += 1
        db.add(p); db.flush()
        db.query(InspectionPlanPoint).filter_by(plan_id=p.id).delete()
        db.add_all([InspectionPlanPoint(plan_id=p.id, point_id=pid) for pid in body.point_ids])
        db.commit(); db.refresh(p)
        return plan_out(p)


def delete_plan(db, store, plan_id, robot_pk, version):
    with store.lock:
        p = get_plan(db, plan_id, robot_pk)
        if p.version != version:
            raise HTTPException(409, '计划已被修改，请刷新后重试')
        p.deleted, p.enabled, p.next_run_at = True, False, None
        p.version += 1
        db.query(InspectionPlanPoint).filter_by(plan_id=p.id).delete()
        db.commit()
        return {'ok': True}
