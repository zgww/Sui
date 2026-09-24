"""检测告警模型。

算法服务把识别结果回调给 FMS 后，FMS 继续跑该检测框绑定的**检测算法流程**
（`DetectPipelineNode`），流程里的告警节点（`AlarmNode` / `NumericAlarmNode` /
`RangeAlarmNode`）命中条件，就产生一条 Alarm。

与 `monitor.RobotAlert` 的区别：RobotAlert 是机器人**设备自身**的上下线/电量等
运维告警；本模型是**巡检检测业务**告警（人员入侵、吸烟、表计越限…），两者来源、
处理人、页面都不同，不混在一张表里。
"""
from datetime import datetime
from sqlalchemy import Column, Integer, String, DateTime, ForeignKey, JSON, Text

from ..database import Base


def now():
    return datetime.utcnow()


class Alarm(Base):
    """一条检测告警。"""

    __tablename__ = "inspection_alarms"

    id = Column(Integer, primary_key=True)
    # —— 来源 ——
    run_id = Column(Integer, ForeignKey("inspection_runs.id"), index=True)
    action_result_id = Column(Integer,
                              ForeignKey("inspection_action_results.id"), index=True)
    inspection_id = Column(String(64), default="", index=True)
    floor = Column(Integer, default=0)
    waypoint_id = Column(String(64), default="")
    action_id = Column(String(64), default="")
    point_id = Column(String(64), default="", index=True)
    point_name = Column(String(128), default="")
    #: 检测框身份（`DetectBoxNode.box_id`，编排处生成）。⚠️ `point_id` 可能为空
    #: （本站场景里常常没绑测点），box_id 一定有 —— 同一个动作下多个未绑测点的框，
    #: 只有靠它才分得开（否则去重窗口会把它们合成一条告警）。
    box_id = Column(String(64), default="", index=True)
    box_name = Column(String(128), default="")
    # —— 分类 ——
    #: 告警类型：检测流程名（如「人员入侵」），给告警列表按类型筛
    alarm_type = Column(String(128), default="", index=True)
    #: 算法编码（检测框 box.name，如 0_0_0_3006_0_0）
    algorithm = Column(String(128), default="")
    #: 告警级别：预警 / 一般告警 / 严重告警 / 危急告警
    level = Column(String(16), default="一般告警", index=True)
    title = Column(String(256), default="")
    content = Column(Text, default="")
    picture = Column(String(512), default="")       # 证据图（巡检图 web 路径）
    extra_json = Column(JSON)                       # 检测框 / 读数 / 原始结果
    # —— 状态 ——
    #: unack 未确认 / ack 已确认
    status = Column(String(16), default="unack", index=True)
    triggered_at = Column(DateTime, default=now)   # 告警产生时间
    acknowledged_at = Column(DateTime)
    acknowledged_by = Column(String(64), default="")
    created_at = Column(DateTime, default=now)
    updated_at = Column(DateTime, default=now, onupdate=now)
