"""Archive references live in SQLite; point IDs retain their original strings."""
from datetime import datetime

from sqlalchemy import Column, DateTime, ForeignKey, Index, Integer, String, UniqueConstraint, func

from ..database import Base


class PointBinding(Base):
    __tablename__ = "point_bindings"
    id = Column(Integer, primary_key=True)
    point_id = Column(String(256), nullable=False, index=True)
    waypoint_pk = Column(Integer, ForeignKey("waypoints.id"), nullable=False, index=True)
    action_pk = Column(Integer, ForeignKey("waypoint_actions.id"), nullable=True, index=True)
    created_at = Column(DateTime, default=datetime.utcnow)


# SQLite considers NULL values distinct; normalize an absent action for uniqueness.
Index("uq_point_binding_target", PointBinding.point_id, PointBinding.waypoint_pk,
      func.coalesce(PointBinding.action_pk, -1), unique=True)


class ArchiveTaskPoint(Base):
    __tablename__ = "archive_task_points"
    __table_args__ = (UniqueConstraint("task_id", "point_id"),)
    id = Column(Integer, primary_key=True)
    task_id = Column(Integer, ForeignKey("inspection_tasks.id"), nullable=False, index=True)
    point_id = Column(String(256), nullable=False, index=True)
