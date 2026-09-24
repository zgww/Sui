"""航点/地图模型: RobotMap(地图,可多层 floor) + Waypoint(航点) + WaypointAction(动作)。

floor 设计: 地图层有 floor(整层归属), 航点也有 floor(可在地图层基础上覆盖/跨层)。
定标图存文件(data/calibration/), DB 存相对路径。
动作的算法参数另有独立表, 本模型不含算法字段。
"""
from datetime import datetime
from sqlalchemy import Column, Integer, String, Float, DateTime, ForeignKey, JSON, Text
from sqlalchemy.orm import relationship

from ..database import Base


def now():
    return datetime.utcnow()


class RobotMap(Base):
    """机器人地图(可多张/多层楼)。"""
    __tablename__ = "robot_maps"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    name = Column(String(128), default="")
    floor = Column(Integer, default=0, comment="地图所属楼层(可空/0)")
    image_path = Column(String(512), default="", comment="地图图片相对路径")
    scale = Column(Float, default=1.0, comment="像素→米 比例")
    origin_x = Column(Float, default=0.0)
    origin_y = Column(Float, default=0.0)
    note = Column(String(256), default="")
    created_at = Column(DateTime, default=now)
    updated_at = Column(DateTime, default=now, onupdate=now)

    waypoints = relationship("Waypoint", back_populates="robot_map",
                             cascade="all, delete-orphan", order_by="Waypoint.index")


class Waypoint(Base):
    """航点: 机器人巡检的关键位置点。"""
    __tablename__ = "waypoints"
    id = Column(Integer, primary_key=True)
    map_pk = Column(Integer, ForeignKey("robot_maps.id"), index=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    index = Column(Integer, default=0, comment="序号, 列表顺序")
    wp_id = Column(String(64), default="", comment="对外唯一标识, 如 wp_001; 导入/导出用")
    name = Column(String(128), default="", comment="航点名称, 如 变压器A")
    type = Column(Integer, default=0, comment="0定点 1途经 2充电 3返回")
    floor = Column(Integer, default=None, comment="航点楼层; NULL 时继承地图 floor")
    # 位姿
    pose_x = Column(Float, default=0.0)
    pose_y = Column(Float, default=0.0)
    pose_theta = Column(Float, default=0.0, comment="偏航角 °")
    # 设备状态
    lift_height = Column(Float, default=0.0, comment="升降杆高度 m")
    ptz_pan = Column(Float, default=0.0)
    ptz_tilt = Column(Float, default=0.0)
    ptz_zoom = Column(Float, default=0.0)
    # 定标图(存文件相对路径)
    calib_visible = Column(String(512), default="", comment="可见光定标图路径")
    calib_thermal = Column(String(512), default="", comment="红外定标图路径")
    note = Column(String(256), default="")
    created_at = Column(DateTime, default=now)
    updated_at = Column(DateTime, default=now, onupdate=now)

    robot_map = relationship("RobotMap", back_populates="waypoints")
    actions = relationship("WaypointAction", back_populates="waypoint",
                           cascade="all, delete-orphan", order_by="WaypointAction.seq")


class WaypointAction(Base):
    """航点动作: 到达航点后执行的动作(拍照/测温/录像/局放/延时...)。"""
    __tablename__ = "waypoint_actions"
    id = Column(Integer, primary_key=True)
    waypoint_pk = Column(Integer, ForeignKey("waypoints.id"), index=True)
    seq = Column(Integer, default=0, comment="动作顺序")
    action_type = Column(Integer, default=1, comment="1可见光拍照 2红外拍照 3录像 4录音 5测温 6环境 7局放 100开门 200充电 201延时")
    name = Column(String(128), default="")
    # 动作专属设备参数(覆盖航点默认值)
    ptz_pan = Column(Float, default=None, comment="NULL=继承航点")
    ptz_tilt = Column(Float, default=None)
    ptz_zoom = Column(Float, default=None)
    lift_height = Column(Float, default=None)
    # 动作参数
    duration_ms = Column(Integer, default=0, comment="录像/录音/延时 毫秒")
    note = Column(String(256), default="")
    created_at = Column(DateTime, default=now)

    waypoint = relationship("Waypoint", back_populates="actions")
