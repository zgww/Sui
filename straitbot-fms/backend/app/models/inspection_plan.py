"""Persisted configuration and durable execution claims, separate from device tasks."""
from datetime import datetime
from sqlalchemy import Boolean, Column, DateTime, ForeignKey, Integer, JSON, String, Text, UniqueConstraint
from ..database import Base


class InspectionPlan(Base):
    __tablename__ = "inspection_plans"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), nullable=False, index=True)
    map_pk = Column(Integer, ForeignKey("robot_maps.id"), nullable=False)
    name = Column(String(128), nullable=False)
    point_ids = Column(JSON, nullable=False)
    stages = Column(JSON)  # Ordered map/floor selections; NULL preserves legacy plans.
    schedule = Column(JSON, nullable=False)
    enabled = Column(Boolean, default=False, nullable=False)
    deleted = Column(Boolean, default=False, nullable=False)
    version = Column(Integer, default=1, nullable=False)
    next_run_at = Column(DateTime, index=True)
    created_at = Column(DateTime, default=datetime.utcnow)
    updated_at = Column(DateTime, default=datetime.utcnow, onupdate=datetime.utcnow)


class InspectionPlanPoint(Base):
    __tablename__ = "inspection_plan_points"
    __table_args__ = (UniqueConstraint("plan_id", "point_id"),)
    id = Column(Integer, primary_key=True)
    plan_id = Column(Integer, ForeignKey("inspection_plans.id"), nullable=False, index=True)
    point_id = Column(String(256), nullable=False, index=True)


class PlanExecution(Base):
    __tablename__ = "inspection_plan_executions"
    __table_args__ = (UniqueConstraint("plan_id", "request_key"),)
    id = Column(String(64), primary_key=True)
    plan_id = Column(Integer, ForeignKey("inspection_plans.id"), nullable=False, index=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), nullable=False, index=True)
    task_id = Column(Integer, ForeignKey("inspection_tasks.id"))
    request_key = Column(String(128), nullable=False)
    trigger = Column(String(16), nullable=False)
    scheduled_at = Column(DateTime)
    status = Column(String(32), nullable=False, default="dispatching")
    message = Column(Text, default="")
    content = Column(JSON)
    route = Column(JSON)  # Immutable compiled segments, never rebuilt between stages.
    stage_index = Column(Integer, default=0)
    created_at = Column(DateTime, default=datetime.utcnow)
    finished_at = Column(DateTime)


class InspectionRobotLease(Base):
    __tablename__ = "inspection_robot_leases"
    robot_pk = Column(Integer, ForeignKey("robots.id"), primary_key=True)
    execution_id = Column(String(64), ForeignKey("inspection_plan_executions.id"), nullable=False, unique=True)
