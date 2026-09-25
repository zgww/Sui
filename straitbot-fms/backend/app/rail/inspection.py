"""巡检任务数据模型与装载/落盘。

一次巡检任务由外部（FMS/上位机业务侧）下发，数据形如 ``tests/test_inspection.json``：
顶层是一个数组，**数组成员是同一次巡检在不同楼层的分段**（它们的 ``id/plan/name``
相同，仅 ``floor``、``substationMapsId`` 与航点不同）。因此这里把同 ``id`` 的多个
楼层分段合并为一个 :class:`InspectionTask`（= 一次巡检）。

- 航点 ``waypoint[].pose.point.x``：挂轨机器人为沿轨弧长，单位 m；
- 动作 ``action[].type``：1 可见光拍照、2 测温、3 录像（带 ``duration``，毫秒）；
- ``detectType``：动作点数据怎么作用到检测（见 :data:`DETECT_TYPE_FMS`）。

本模块只负责"解析 / 合并 / 落盘 / 游标取数"，不负责真正走行、云台、拍照（那些在
Robot 的状态机行为里逐步接入）。落盘一律保存**原始 dict**，保证未建模字段无损。
"""
from __future__ import annotations

import json
import logging
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Optional, Union

from pydantic import BaseModel, ConfigDict, Field, field_validator

logger = logging.getLogger("rail.inspection")

#: 动作点数据作用到检测的方式。
#:
#: - ``fms``：**FMS 自己的动作执行器**处理 —— 动作数据在执行侧就消化掉，
#:   检测由 FMS 跑（``detect_pipeline``），不走 cmd=104 上报；
#: - ``platform``：动作点数据**通过 cmd=104 上传平台**，由平台处理检测。
#:   这是**旧版行为**，也是缺省值：老巡检任务没有这个字段，语义上就是它。
#:
#: 字段写在**楼层段**上（同一次巡检的各段应当一致），而不是动作上——它说的是
#: "这次巡检的数据往哪送"，不是"这个动作拍什么"。
DETECT_TYPE_FMS = "fms"
DETECT_TYPE_PLATFORM = "platform"
DETECT_TYPES = (DETECT_TYPE_FMS, DETECT_TYPE_PLATFORM)


# --------------------------------------------------------------------------- #
# pydantic 模型（用于校验与字段访问；落盘仍用原始 dict，避免丢字段）
# --------------------------------------------------------------------------- #
class _Base(BaseModel):
    model_config = ConfigDict(populate_by_name=True, extra="allow")


class PtzParam(_Base):
    """云台参数（pan/tilt 单位度，zoom 倍率，focus/focal_len 镜头参数）。"""

    focal_len: float = 0.0
    focus: float = 0.0
    pan: float = 0.0
    tilt: float = 0.0
    zoom: float = 1.0


class Point3(_Base):
    x: float = 0.0   # 挂轨：沿轨弧长，m
    y: float = 0.0
    z: float = 0.0


class WaypointPose(_Base):
    point: Point3 = Field(default_factory=Point3)
    theta: float = 0.0


class InspectionAction(_Base):
    """航点下的单个动作。type: 1 可见光拍照 / 2 测温 / 3 录像。"""

    id: str = ""
    type: int = 0
    lift_height: float = 0.0          # 升降杆高度，m（按现场单位约定）
    steer_point_name: str = ""        # 航点/设备名（如 AO-RC-057）
    ptz_param: Optional[PtzParam] = None
    duration: float = 0.0             # 录像时长，毫秒（type=3）
    # 抓拍图（参考图）web 路径：航点树编排时拍照动作点配置的抓拍图片
    reference_image: str = ""
    # 测温点配置结构较杂，原样保留为 dict 列表
    thermometry_points: list[dict] = Field(default_factory=list)
    # 检测框配置（拍照动作下的多个检测区域）
    detect_boxes: list[dict] = Field(default_factory=list)


class InspectionWaypoint(_Base):
    id: str = ""
    index: int = 0
    pose: WaypointPose = Field(default_factory=WaypointPose)
    action: list[InspectionAction] = Field(default_factory=list)


class FloorTask(_Base):
    """一次巡检在单个楼层的分段。"""

    floor: int = 0
    id: str = ""                              # 巡检 id（同一次巡检各楼层相同）
    name: str = ""
    plan: str = ""                            # 巡检计划 id
    substation_maps_id: str = Field(default="", alias="substationMapsId")
    waypoint: list[InspectionWaypoint] = Field(default_factory=list)
    #: 动作点数据作用到检测的方式（缺省 platform = 旧版行为，见模块常量）
    detect_type: str = Field(default=DETECT_TYPE_PLATFORM, alias="detectType")

    @field_validator("detect_type", mode="before")
    @classmethod
    def _normalize_detect_type(cls, v: Any) -> str:
        """不传 / 空 / 非法值一律回落 ``platform``（旧版行为）并告警。

        非法值**不抛错**：这是"没有它也照样能跑完巡检"的字段，为它让整份任务
        加载失败不划算——现场手改过 JSON、或者新版本先于旧版本上线，都会遇到
        不认识的值，回落比拒绝更符合"巡检别停下来"。
        """
        s = str(v or "").strip().lower()
        if not s:
            return DETECT_TYPE_PLATFORM
        if s not in DETECT_TYPES:
            logger.warning("[inspection] 未知 detectType=%r（应为 %s），按 %s 处理",
                           v, "/".join(DETECT_TYPES), DETECT_TYPE_PLATFORM)
            return DETECT_TYPE_PLATFORM
        return s


# --------------------------------------------------------------------------- #
# 合并后的一次巡检
# --------------------------------------------------------------------------- #
class InspectionTask:
    """一次巡检（含一个或多个楼层分段）。"""

    def __init__(self, floors: list[FloorTask], raw_floors: list[dict]) -> None:
        if not floors:
            raise ValueError("巡检任务没有有效的楼层分段")
        floors = sorted(floors, key=lambda f: f.floor)
        self.floors: list[FloorTask] = floors
        self.raw_floors: list[dict] = sorted(
            raw_floors, key=lambda d: d.get("floor", 0)
        )

        self.inspection_id: str = floors[0].id
        self.name: str = next((f.name for f in floors if f.name), "")
        self.plan: str = next((f.plan for f in floors if f.plan), "")
        self.floor_ids: set[str] = {f.id for f in floors}

        # 扁平航点序列：(楼层, 航点)，按楼层升序、航点 index 升序，供状态机顺序遍历
        self.waypoints: list[tuple[int, InspectionWaypoint]] = [
            (f.floor, w)
            for f in floors
            for w in sorted(f.waypoint, key=lambda w: w.index)
        ]
        self.action_count: int = sum(len(w.action) for _, w in self.waypoints)

    # ----- 构建 -----
    @classmethod
    def from_payload(cls, payload: Union[dict, list]) -> "InspectionTask":
        """从下发的 JSON（单个楼层分段 dict 或其列表）构建并合并。"""
        if isinstance(payload, dict):
            items = [payload]
        elif isinstance(payload, list):
            items = payload
        else:
            raise ValueError(f"巡检任务数据格式不支持: {type(payload).__name__}")
        if not items:
            raise ValueError("巡检任务为空")

        floors: list[FloorTask] = []
        for raw in items:
            if not isinstance(raw, dict):
                raise ValueError("巡检任务分段必须是对象")
            f = FloorTask.model_validate(raw)
            if f.id:
                floors.append(f)
        if not floors:
            raise ValueError("巡检任务缺少有效 id")

        task = cls(floors, items)
        if len(task.floor_ids) > 1:
            logger.warning(
                "[inspection] 下发数据含多个不同巡检 id %s，已按首个 id=%s 归并",
                sorted(task.floor_ids), task.inspection_id,
            )
        return task

    # ----- 基本信息 -----
    @property
    def detect_type(self) -> str:
        """本次巡检的动作数据怎么作用到检测。

        同一次巡检的各楼层段**应当一致**（它们是同一次巡检拆出来的）。不一致时
        以**第一个段**为准并告警——与 `inspection_id` / `name` 取首个分段值的
        既有做法一致，而不是取"最特殊"的那个（猜不出来谁是对的）。
        """
        vals = [f.detect_type for f in self.floors]
        if len(set(vals)) > 1:
            logger.warning("[inspection] 巡检 %s 各楼层 detectType 不一致 %s，按 %s 处理",
                           self.inspection_id, vals, vals[0])
        return vals[0] if vals else DETECT_TYPE_PLATFORM

    @property
    def waypoint_count(self) -> int:
        return len(self.waypoints)

    @property
    def floor_count(self) -> int:
        return len(self.floors)

    def floors_desc(self) -> list[int]:
        return [f.floor for f in self.floors]

    # ----- 落盘（记录，无损保存原始数据）-----
    def to_record(self, received_at: Optional[str] = None) -> dict[str, Any]:
        return {
            "inspection_id": self.inspection_id,
            "name": self.name,
            "plan": self.plan,
            "received_at": received_at or datetime.now(timezone.utc).isoformat(),
            "floor_count": self.floor_count,
            "floors_desc": self.floors_desc(),
            "waypoint_count": self.waypoint_count,
            "action_count": self.action_count,
            # 顶层提一份，翻落盘记录时不用去 floors 里逐段找
            "detect_type": self.detect_type,
            # 原样保存各楼层分段，未建模字段不丢失
            "floors": self.raw_floors,
        }

    def save(self, base_dir: Union[str, Path]) -> Path:
        """保存为 ``{base_dir}/{inspection_id}.json``，重复 id 覆盖。返回文件路径。"""
        d = Path(base_dir)
        d.mkdir(parents=True, exist_ok=True)
        path = d / f"{self.inspection_id}.json"
        path.write_text(
            json.dumps(self.to_record(), ensure_ascii=False, indent=2),
            encoding="utf-8",
        )
        return path
