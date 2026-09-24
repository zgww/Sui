"""航点树编排节点（纯数据，不参与规则 runtime 的动作执行）。

本模块的节点描述"机器人巡检航点树"：分组 → 航点 → 动作点 → 测点。
它们与规则链节点（HttpAction/CronTimer 等）共用同一套 NodeBase 注册、
JSON Schema 聚合与前端 inspector 机制，但只作为编排数据被读写/导入导出，
on_active / on_tick 不做任何事（即使被 loader 扫到也无副作用）。

层级约定（仅约定，不在模型层强制，便于自由编排）：
    GroupNode      分组（可嵌套，容器）
      ├ TrackNode        轨道（端点与控制点**平铺**在 children 里，靠顺序表达）
      ├ WaypointNode    航点（轨道弧长位置 + 位姿）
      │    └ ActionPointNode   动作点（拍照/测温/录像 + 升降 + 云台参数）
      │         ├ MeasurePointNode  测温点（热像画面归一化矩形 + 测温参数）
      │         └ DetectBoxNode     检测框（抓拍图上的归一化区域 + 绑定的算法）
      │                └ AlgorithmConfigNode  算法配置（该框跑哪个算法 + 该算法的参数）
      ├ ChargingPileNode 充电桩（沿轨弧长定位的充电位）
      ├ RfidCardNode     RFID 卡（沿轨定位标签，卡号 + 感应范围）
      ├ SectionMarkNode  区段标记（给**一段**轨道加注记：门 / 窗 / 减速…）
      └ IconMarkNode     图标标记（地图**任意位置**的矢量图标，世界坐标 x/y）

充电桩与 RFID 卡**按 x（沿轨弧长，与航点同一坐标系）定位**，与航点同层排序，
这样树里的先后顺序就等于轨道上从起点到终点的先后顺序（前端按 x 插入、按 x 画）。
它们只是编排数据：运行时（导航去充电桩 / 去 1 号卡）目前是桩函数，
后续把这里的坐标喂给 `rail/robot.py` 的那几个 TODO 即可。

轨道的平铺约定（由前端解释，模型层不强制）：
    TrackNode.children 里 TrackEndpointNode（端点）与 TrackControlNode（控制点）
    按**出现顺序**表达路径：扫描时以上一个端点为段起点，中间夹着的
    TrackControlNode 都属于这一段。
        - 0 个控制点 -> 直线段（两端手柄退化到端点自身）
        - 1 个控制点 -> 二次（该点兼作出手柄与入手柄）
        - 2 个控制点 -> 三次（第一个作段起点的出手柄，第二个作段终点的入手柄）
    坐标就是地图的世界坐标，单位**米**——轨道画多长就是多少米，曲线采样出来的
    弧长即轨道真实长度，与航点/充电桩的 `x`（沿轨弧长，米）是同一把尺子。
    （曾经这里是"纯示意单位"，导致"航点 x 才 22.5 却显示在刻度 1900 处"的错觉，
    已统一为米，不要再退回两套单位。）

    轨道可以**成环**：children 里放一个 ClosePathNode（闭合标记，无坐标）即可，
    表示最后一个端点连回第一个端点；排在末端点之后、闭合标记之前的控制点
    就归属于这最后一段。详见 ClosePathNode 的文档。
"""
from __future__ import annotations

from typing import ClassVar, Literal

from ..base import NodeBase, ui_field


class WaypointNodeBase(NodeBase):
    """航点树节点共同基类（中间类，不注册）。纯数据节点，不实现运行时动作。"""

    __type_name__: ClassVar[str | None] = None

    # ---------------------------------------------------------- 组装巡检任务
    def to_inspection_json(self, *args, **kwargs) -> dict | None:
        """把自己组织成**巡检任务 JSON** 里的那一段（见 `inspection_build.py`）。

        返回 `None` = 这个节点不进巡检任务（分组、轨道、图标标记…都只是编排信息，
        设备不认识）。要参与的子类覆写它——**每个节点只管自己的字段**，
        子节点让自己的子节点去组织（"父亲问孩子要"，不要在上层硬拆别人的字段）。

        ⚠️ 用 `self.child_nodes`（`registry.build` 建出来的**实例**）而不是
        `self.children`（那还是原始 spec dict，拿不到子类的字段与方法）。
        """
        return None


class GroupNode(WaypointNodeBase):
    """分组：把航点/动作点/测点或子分组组织在一起，本身不产生动作。"""


class TrackNode(WaypointNodeBase):
    """轨道：一条独立存在的路径，与航点无派生关系。

    children 里**平铺** TrackEndpointNode 与 TrackControlNode，靠顺序表达
    路径走向（详见模块 docstring 的"平铺约定"）。轨道单独成节点，是为了让
    路径能被树编辑、导入导出与版本化管理，而不是藏在地图组件的内部状态里。
    """


class TrackEndpointNode(WaypointNodeBase):
    """轨道端点：路径实际经过的锚点。"""

    x: float = ui_field("number", group="坐标", title="X (m)", default=0.0, step=0.01,
                        description="地图世界坐标 X（米）")
    y: float = ui_field("number", group="坐标", title="Y (m)", default=0.0, step=0.01,
                        description="地图世界坐标 Y（米）")


class TrackControlNode(WaypointNodeBase):
    """轨道控制点：贝塞尔手柄，按出现顺序归属于它所在的那一段。"""

    x: float = ui_field("number", group="坐标", title="X (m)", default=0.0, step=0.01,
                        description="地图世界坐标 X（米）")
    y: float = ui_field("number", group="坐标", title="Y (m)", default=0.0, step=0.01,
                        description="地图世界坐标 Y（米）")


class ClosePathNode(WaypointNodeBase):
    """闭合标记：让所在轨道首尾相连，成为一条**成环**的曲线。

    有些轨道（如环形巡检路线）是闭合的。它不携带坐标，只是一个标记：
    出现在 TrackNode.children 里，表示"到它这里为止的路径，最后一个端点
    要连回**第一个端点**"。

    与平铺约定的关系：最后一段（末端点 -> 首端点）的控制点，就是排在
    末端点之后、闭合标记之前的那些控制点。例如

        [端点1, 控制点a, 端点2, 控制点b, 端点3, 控制点c, 闭合]

    得到三段：端点1->端点2(a)、端点2->端点3(b)、端点3->端点1(c)。
    **没有闭合标记时，末端点之后的控制点会被丢弃**（没有段可归属），
    这也是闭合标记必须单独存在的原因。
    """


class WaypointNode(WaypointNodeBase):
    """航点：轨道上的一个走行目标位置（挂轨以弧长 X 为主）。"""

    wp_id: str = ui_field("text", group="航点", title="航点ID", default="",
                          description="来源巡检任务中的航点唯一 id（可空）")
    index: int = ui_field("number", group="航点", title="序号", default=0,
                          description="航点在楼层中的顺序序号")
    #: 楼层。**航点自己带**而不是只看它挂在哪个分组下：
    #  巡检任务下发是按楼层分段的（`floor` 是段的字段），而树里的分组可以随便套
    #  （`任务 > 楼层1 > 区域A > 航点`），只从分组名回解楼层是有损的——
    #  导入时楼层只写在分组名 `楼层N` 里，改个名就丢了，反向组装巡检任务也就错了。
    #  负数给地下室（-1 = B1），0 也是合法的（有些现场把一层记作 0）。
    floor: int = ui_field("number", group="航点", title="楼层", default=1,
                          description="航点所属楼层（地下室用负数，如 -1 = B1）；"
                                      "巡检任务按它分段下发")
    x: float = ui_field("number", group="位姿", title="弧长 X (m)", default=0.0, step=0.01)
    y: float = ui_field("number", group="位姿", title="Y (m)", default=0.0, step=0.01)
    z: float = ui_field("number", group="位姿", title="Z (m)", default=0.0, step=0.01)
    theta: float = ui_field("number", group="位姿", title="朝向 theta (度)",
                            default=0.0, step=0.1)

    def to_inspection_json(self, index: int = 1, fresh_id: bool = False,
                           point_ids: set | None = None,
                           image_base: str = "") -> dict:
        """航点 -> 巡检任务的 `waypoint` 成员；动作点由**子节点自己**组织。

        `index` 是**楼层内**序号（从 1 递增）：后端 `InspectionTask` 的排序键是
        `(floor, index)`，用全局序号在多楼层时会乱序。
        """
        from ..inspection_build import hex_id

        wid = str(self.wp_id or "").strip()
        actions = [c.to_inspection_json(fresh_id, point_ids, image_base)
                   for c in self.child_nodes if c.type == "ActionPointNode"]
        return {
            "id": hex_id() if (fresh_id or not wid) else wid,
            "index": int(index),
            "pose": {
                "point": {"x": float(self.x or 0), "y": float(self.y or 0),
                          "z": float(self.z or 0)},
                "theta": float(self.theta or 0),
            },
            "action": actions,
        }


class ActionPointNode(WaypointNodeBase):
    """动作点：到达航点后执行的一次相机/云台动作。子节点为测温点。"""

    action_id: str = ui_field("text", group="动作", title="动作ID", default="",
                              description="来源巡检任务中的动作唯一 id（可空）")
    action_type: int = ui_field("select", group="动作", title="动作类型", default=1,
                                options=[1, 2, 3],
                                description="1=可见光拍照，2=全屏测温(红外)，3=录像")
    steer_point_name: str = ui_field("text", group="动作", title="航点名", default="",
                                     description="steer_point_name，如 AO-RC-057")
    lift_height: float = ui_field("number", group="动作", title="升降高度 (m)",
                                  default=0.0, step=0.01,
                                  description="伸缩杆目标高度")
    duration_ms: int = ui_field("number", group="动作", title="录像时长 (ms)",
                                default=0, description="仅动作类型=3 时使用")
    imageUrl: str = ui_field("image", group="动作", title="抓拍图片", default="",
                             description="云台拍照得到的图片路径。存的是**相对本 prefab 文件**的"
                                         "相对路径（如 images/xxx.jpg），整棵航点树（含图片目录）"
                                         "挪位置或改名都不会断链；「重新拍照」会覆盖它。")
    pan: float = ui_field("number", group="云台", title="水平 pan (度)",
                          default=0.0, step=0.01)
    tilt: float = ui_field("number", group="云台", title="俯仰 tilt (度)",
                           default=0.0, step=0.01)
    zoom: float = ui_field("number", group="云台", title="变倍 zoom",
                           default=1.0, step=0.1)
    focal_len: int = ui_field("number", group="云台", title="焦距 focal_len", default=0)
    focus: int = ui_field("number", group="云台", title="聚焦 focus", default=0)

    def to_inspection_json(self, fresh_id: bool = False,
                           point_ids: set | None = None,
                           image_base: str = "") -> dict:
        """动作点 -> 巡检任务的 `action` 成员；测温点/检测框由**子节点自己**组织。

        `point_ids` 非空时只保留测点 id 在里面的测温点（计划的「测点指定」筛出来
        的那些）——**拍照/录像动作不受影响**，它们本来就不带测点。
        """
        from ..inspection_build import hex_id

        aid = str(self.action_id or "").strip()
        atype = int(self.action_type or 1)
        pts = []
        boxes = []
        for c in self.child_nodes:
            if c.type == "MeasurePointNode":
                if point_ids is not None and str(c.point_id or "") not in point_ids:
                    continue
                pts.append(c.to_inspection_json(fresh_id))
            elif c.type == "DetectBoxNode":
                boxes.append(c.to_inspection_json(fresh_id))
        # 抓拍图（参考图）：imageUrl 相对本 prefab 文件，拼 web 基路径
        img_rel = str(self.imageUrl or "").strip().lstrip("/")
        reference_image = f"{image_base}/{img_rel}" if (img_rel and image_base) else ""
        return {
            "id": hex_id() if (fresh_id or not aid) else aid,
            "type": atype,
            "lift_height": float(self.lift_height or 0),
            # duration 只有录像(type=3)用得上，其余给 0（缺字段设备侧默认也是 0）
            "duration": int(self.duration_ms or 0) if atype == 3 else 0,
            "ptz_param": {
                "focal_len": int(self.focal_len or 0),
                "focus": int(self.focus or 0),
                "pan": float(self.pan or 0),
                "tilt": float(self.tilt or 0),
                "zoom": float(self.zoom or 1),
            },
            "steer_point_name": str(self.steer_point_name or ""),
            "reference_image": reference_image,
            "thermometry_points": pts,
            "detect_boxes": boxes,
        }


class MeasurePointNode(WaypointNodeBase):
    """测温点：热像画面内的一个归一化测温矩形及其测温参数。"""

    point_id: str = ui_field("text", group="测点", title="测点ID", default="")

    def to_inspection_json(self, fresh_id: bool = False) -> dict:  # noqa: D102
        from ..inspection_build import hex_id

        pid = str(self.point_id or "").strip()
        return {
            "id": hex_id() if (fresh_id or not pid) else pid,
            "thermometry_param": {
                "distance": int(self.distance or 0),
                "emissivity": float(self.emissivity),
                "enable_reflective": int(self.enable_reflective),
                "reflective_temperature": float(self.reflective_temperature),
                "rect": {"x": float(self.rect_x), "y": float(self.rect_y),
                         "w": float(self.rect_w), "h": float(self.rect_h)},
            },
        }
    rect_x: float = ui_field("number", group="测温框(归一化 0~1)", title="x",
                             default=0.0, min=0, max=1, step=0.001)
    rect_y: float = ui_field("number", group="测温框(归一化 0~1)", title="y",
                             default=0.0, min=0, max=1, step=0.001)
    rect_w: float = ui_field("number", group="测温框(归一化 0~1)", title="宽 w",
                             default=0.0, min=0, max=1, step=0.001)
    rect_h: float = ui_field("number", group="测温框(归一化 0~1)", title="高 h",
                             default=0.0, min=0, max=1, step=0.001)
    distance: int = ui_field("number", group="测温参数", title="测距 distance",
                             default=0, description="热像仪测距原始值")
    emissivity: float = ui_field("number", group="测温参数", title="发射率",
                                 default=0.96, min=0, max=1, step=0.01)
    enable_reflective: int = ui_field("select", group="测温参数", title="启用反射温度",
                                      default=0, options=[0, 1])
    reflective_temperature: float = ui_field("number", group="测温参数",
                                             title="反射温度 (℃)", default=0.0)


class DetectBoxNode(WaypointNodeBase):
    """检测框：挂在拍照动作点上的一块图像区域，以及它要执行的**检测算法流程**。

    坐标是**归一化**的（0~1，相对抓拍图宽高），不是像素：换相机、换分辨率、
    重新拍一张不同尺寸的图，框都还落在同一个位置上。矩形也是 4 个点
    （且轴对齐），所以前端画布只有"一串点"这一种内部表示，不用分两套。

    `detect_flow` 是这个框要跑的**检测算法流程**的引用 id，指向第三棵树
    （`data/prefabs/检测算法`）里的一条流程（见 `nodes/detect.py` 的
    DetectPipelineNode）。这跟游戏里的材质是同一个思路：材质 = shader + 参数，
    是一条渲染管线；检测流程 = 算法 + 参数（节流 / ROI / 连续确认 / 告警 / 短信…），
    是一条检测管线。框只负责"画面上哪块区域"，"拍到之后怎么判定、要不要告警"
    全是那条流程的事。**只存引用不抄内容**——流程改一次，所有引用它的框自动
    跟着变，抄一份必然漂移。

    引用 id 取流程根的 `detect_id`（检测编号）；编号留空时用文件名（不含
    `.prefab.json`）。选项由前端从检测流程目录拉取（`optionsFrom="detectFlows"`），
    不在此写死；留空表示这个框还没指定检测流程。

    `algorithm` 是**旧模型遗留的只读镜像**：早年要在框下挂一个 AlgorithmConfigNode
    来选单个算法（`data/algorithms.json`），现已改为直接引用整条流程、不再挂子节点。
    字段保留只读，只为打开旧数据与导出/导入链路不报错，新数据不要再用。

    `box_id` 是本框的**身份**（与 `point_id` 是两件事）：`point_id` 指向测点档案、
    可以不绑，`box_id` 一定有。下发推理任务时作为报文的 `box_id`，算法回调靠它
    把结果对回本框；编排处生成、复制粘贴时重新生成。
    """

    # ⚠️ box_id 是**检测框自己的身份**，与 point_id 是两件事：
    # point_id 指向测点档案（可以不绑，我们的场景里常常没有），box_id 一定有。
    # 没有它的话，一个没绑测点的框在下发给算法服务时是匿名的 —— 结果回来了
    # 也不知道是哪一块区域出的（见 `task_executor._infer_async` 的 box_id 字段）。
    # 由航点树编排处生成（`WaypointTreePrefab.addDetectBox`），**复制粘贴时重新生成**
    # （`inspectionBuild.regenerateIds`）——沿用原 id 会让两个框抢同一份结果。
    box_id: str = ui_field("text", group="检测框", title="检测框 ID", default="",
                           description="检测框自己的稳定唯一 id（32 位 hex），由编排自动生成、"
                                       "复制粘贴时重新生成。下发推理任务时作为报文的 box_id，"
                                       "回调靠它把算法结果对回本框 —— **测点可以不绑，box_id 不能没有**")
    # 用 Literal 而不是裸 str：坏值（手改 json 写错）在 build 时就被挡下，
    # 而不是等前端画的时候才发现"这形状我不认识"默默退化成矩形
    shape: Literal["rect", "polygon"] = ui_field("select", group="检测框", title="形状",
                                                 default="rect", options=["rect", "polygon"],
                                                 description="rect=矩形（轴对齐 4 点）；"
                                                             "polygon=多边形（至少 3 点）")
    points: list[dict[str, float]] = ui_field("json", group="检测框",
                                              title="顶点（归一化 0~1）", default=[],
                                              description='[{"x":0.1,"y":0.2}, …]，按顺序连成闭合区域；'
                                                          '矩形同样是 4 个点')
    note: str = ui_field("text", group="检测框", title="备注", default="",
                         description="给现场看的说明，例如「这个框拍的是 3 号柜电流表」")
    algorithm: str = ui_field("readonly", group="检测流程", title="算法类型（旧，已停用）",
                              default="",
                              description="旧模型字段：早年在框下挂 AlgorithmConfigNode 选单个"
                                          "算法时留下的镜像。新模型请选择上面的「检测算法流程」"
                                          "（= 算法 + 参数的整条检测管线），此字段只读、不再使用")
    point_id: str = ui_field("text", group="测点", title="测点 ID", default="",
                             description="测点档案（/api/point-archive/catalog/points）里的测点 id。"
                                         "由检测框工具的「绑定测点」写入")
    point_name: str = ui_field("text", group="测点", title="测点名称", default="",
                               description="绑定时一起写进来的**镜像**，列表和导出直接看它，"
                                           "不用为了显示一个名字再去查一次档案")
    detect_flow: str = ui_field("select", group="检测流程", title="检测算法流程",
                                default="", optionsFrom="detectFlows",
                                description="这个框要执行的检测算法流程（`data/prefabs/检测算法` "
                                            "下的一条）。存的是流程引用 id：优先取流程根的检测编号 "
                                            "detect_id，编号留空时用文件名。**只存引用不抄内容**："
                                            "流程里的算法、阈值、连续确认、告警/短信都在那棵树维护，"
                                            "框这里抄一份必然漂移。留空 = 还没指定流程")

    def to_inspection_json(self, fresh_id: bool = False) -> dict:
        """检测框 -> 巡检任务的 detect_boxes 成员。

        ``id`` 就是**检测框自己的 box_id**（不再拿 point_id 顶替）。早年的写法是
        `point_id or 随机 hex`：框绑了测点就借用测点 id、没绑就每次 build 现摇一个，
        于是"没绑测点的框"下发给执行侧后**没有稳定身份**，算法回调回来了也不知道
        是哪一块区域出的（见 `task_executor._infer_async` 与 `services/alarm_processor.py`）。
        现在 box_id 由编排处生成并落盘，`point_id` 只表示"顺手绑了哪个测点"。
        """
        from ..inspection_build import hex_id

        # 归一化顶点 -> 轴对齐矩形（x, y, w, h）
        rect = {"x": 0.0, "y": 0.0, "w": 0.0, "h": 0.0}
        pts = self.points or []
        if pts:
            xs = [float(p.get("x", 0)) for p in pts]
            ys = [float(p.get("y", 0)) for p in pts]
            x0, x1 = min(xs), max(xs)
            y0, y1 = min(ys), max(ys)
            rect = {"x": x0, "y": y0, "w": max(0.0, x1 - x0), "h": max(0.0, y1 - y0)}

        box_id = str(self.box_id or "").strip()
        if fresh_id or not box_id:
            # 老数据没写 box_id（或调用方明确要求换一个）：这里现摇一个。
            # ⚠️ 摇出来的**不会写回树**，所以同一棵老树每次 build 都是不同的 id ——
            # 前端保存时会用 `ensureBoxIds` 把它落盘（见 `utils/inspectionBuild.ts`），
            # 这里只是"不报错、有值可用"的兜底，不是正路。
            box_id = hex_id()
        return {
            "id": box_id,
            "box_id": box_id,
            # 框名：给现场看的（列表、回调定位、告警文案都用它）。
            # 没写名字时由执行侧回落到 测点名 → 检测框N（见 `_detect_targets`）
            "box_name": str(self.name or ""),
            "shape": self.shape,
            "rect": rect,
            "points": pts,
            "point_id": str(self.point_id or "").strip(),
            "point_name": str(self.point_name or ""),
            "detect_flow": str(self.detect_flow or ""),
            "note": str(self.note or ""),
        }


class AlgorithmConfigNode(WaypointNodeBase):
    """[已废弃] 算法配置节点（旧模型，不要再用）。

    旧模型在检测框下挂一个本节点来选单个算法（`data/algorithms.json`）及其参数；
    新模型检测框直接在 `DetectBoxNode.detect_flow` 上引用一整条**检测算法流程**
    （`data/prefabs/检测算法`，= 算法 + 参数的检测管线），不再挂本子节点。

    ``__hidden__ = True``：旧文件里若已存在该节点仍能正常打开（build 不报错、
    检视器可见），但它不再出现在"添加节点"类型目录里，检测框工具也不再创建它。

    ---- 以下为旧文档，留作参考 ----

    挂在 `DetectBoxNode` 下面，**一个框只绑一个**——换算法就是换掉这个节点。
    之所以单独成节点：算法之间的参数长得完全不一样（表计读数要量程，
    缺陷检测要阈值和类别过滤），塞成一坨字段会让每个框都拖着一堆用不到的属性。

    它是**普通 prefab 节点**：在树里能选中，检视器按 schema 自动出表单，
    跟改航点坐标没有区别——没有为它写任何专用编辑 UI。

    `params` 是给各算法自定义参数留的口子（JSON，随便塞）。共性的三个
    （算法类型 / 置信度阈值 / 告警级别）单独成字段，是为了让列表和告警规则
    不用解析 JSON 就能读到。
    """

    # 废弃节点：能解析旧数据，但不进"添加节点"目录
    __hidden__: ClassVar[bool] = True

    algorithm: str = ui_field("select", group="算法", title="算法类型", default="",
                              optionsFrom="algorithms",
                              description="data/algorithms.json 里的算法 id。"
                                          "选项**不在 schema 里写死**，由前端拿 "
                                          "/api/waypoint-prefab/algorithms 填充，"
                                          "所以往目录里加算法不用动这里")
    threshold: float = ui_field("number", group="算法", title="置信度阈值", default=0.5,
                                min=0, max=1, step=0.05,
                                description="低于该置信度的识别结果不采纳（0~1）")
    # Literal 而不是裸 str：手改 json 写个"很严重"在 build 时就被挡下，
    # 而不是等告警规则拿到一个不认识的级别再默默降级
    level: Literal["提示", "一般", "严重"] = ui_field(
        "select", group="告警", title="告警级别", default="提示",
        options=["提示", "一般", "严重"],
        description="命中后上报的告警级别")
    params: dict = ui_field("json", group="参数", title="自定义参数", default={},
                            rows=6,
                            description="各算法自己的参数（量程、类别过滤、ROI…），"
                                        "自由 JSON；换算法时会被重置成新的默认值")
    note: str = ui_field("textarea", group="参数", title="备注", default="", rows=3,
                         description="给现场看的说明，例如「量程 0~100A，超 80 报警」")


class BackgroundImageNode(WaypointNodeBase):
    """地图背景图：贴在地图**最底层**的一张底图（照着它画轨道、摆航点）。

    只有"锚点 + 缩放"两个自由度（没有旋转）：锚点是**图片左上角**对应的
    世界坐标（米），`scale` 是"1 图片像素 = 多少米"。图片按自身宽高乘
    `scale` 铺开，所以换一张不同尺寸的图不会跟着变形。

    `src` 可以是后端上传接口返回的 `/data/calibration/background/xxx.png`，
    也可以是任意 http(s) 图片地址（前端直接塞给 `<img>`）。
    """

    src: str = ui_field("text", group="图片", title="图片路径 / URL", default="",
                        description="/data/calibration/background/xxx.png 或 http(s) 链接")
    x: float = ui_field("number", group="位置", title="锚点 X（图片左上角，m）", default=0.0,
                        step=0.01, description="图片左上角对齐到的世界坐标 X（米）")
    y: float = ui_field("number", group="位置", title="锚点 Y（图片左上角，m）", default=0.0,
                        step=0.01, description="图片左上角对齐到的世界坐标 Y（米）")
    scale: float = ui_field("number", group="位置", title="缩放（米 / 像素）",
                            default=1.0, step=0.01, min=0.0001,
                            description="1 图片像素铺多少米；图上 100px 占 100 m 时填 1")
    opacity: float = ui_field("number", group="图片", title="不透明度", default=0.5,
                              min=0, max=1, step=0.05,
                              description="0 全透明 / 1 完全盖住；0.4~0.6 才不会压住轨道")


class ChargingPileNode(WaypointNodeBase):
    """充电桩：轨道上的一个充电位，按**沿轨弧长**定位。

    `rail/robot.py` 的「移动到最近的充电桩」目前是桩函数（[TODO-导航] 需要充电桩
    坐标）——本节点就是那个坐标的来源。桩位精定位靠 RFID：机器人读到桩位绑定的
    卡号后做微挪对位（见 `是否最近触发了充电桩rfid`），所以这里留了 `rfid` 关联字段。
    """

    pile_id: str = ui_field("text", group="充电桩", title="桩编号", default="",
                            description="充电桩编号 / 标签（可空）")
    x: float = ui_field("number", group="位置", title="弧长 X (m)", default=0.0, step=0.01,
                        description="沿轨弧长，与航点 x 同一坐标系")
    rfid: int = ui_field("number", group="充电桩", title="关联 RFID 卡号", default=0,
                         description="桩位精定位用的卡号（协议 uint16；0 = 未绑定）")
    charge_minutes: int = ui_field("number", group="充电", title="计划充电时长 (min)",
                                   default=60, min=0, description="充满/定时退出用的参考时长")


class RfidCardNode(WaypointNodeBase):
    """RFID 卡：轨道上的一个定位标签。

    对应下位机地图标签（0x21/0x22 `MapTag`，tag_type=2）与 0x30 的进入/离开事件：
    卡号是协议里的 uint16，位置与感应范围按协议原单位记录（mm），
    工程侧统一用 `x`（m）排布。`rail/robot.py` 的「移动到1号卡」同样是桩函数，
    本节点即它的坐标来源。
    """

    card_id: int = ui_field("number", group="RFID", title="卡号", default=0,
                            description="协议 uint16 卡号（0x29 / 0x30 上报值）")
    x: float = ui_field("number", group="位置", title="弧长 X (m)", default=0.0, step=0.01,
                        description="沿轨弧长，与航点 x 同一坐标系")
    range_mm: int = ui_field("number", group="位置", title="感应范围 (mm)", default=0,
                             description="标签感应范围（协议 range 字段，mm）")


class SectionMarkNode(WaypointNodeBase):
    """区段标记：给轨道上**一段**区间加注记（门 / 窗 / 减速 / 禁停…）。

    与充电桩、RFID 卡一样按 `x`（沿轨弧长，m）定位，但它覆盖的是
    `[x - radius, x + radius]` 这段**区间**而不是一个点：
    前端把它画成贴在轨道曲线上的一条彩色带，用来提示"这一段是门"
    "这一段要减速"之类的额外信息。

    纯编排数据：**不参与任何运行时决策**，只是给人看的注记
    （要真做限速，得由执行侧读这棵树的节点另做处理）。
    """

    x: float = ui_field("number", group="位置", title="中心弧长 X (m)", default=0.0, step=0.01,
                        description="区段中心的沿轨弧长，与航点 x 同一坐标系")
    radius: float = ui_field("number", group="位置", title="半径 (m)", default=1.0, step=0.1,
                             min=0.01, description="沿轨向两侧各延伸多少米（区段 = x ± 半径）")
    kind: str = ui_field("select", group="区段", title="类型", default="自定义",
                         options=["门", "窗", "减速", "禁停", "危险", "自定义"],
                         description="区段用途，仅作注记分类")
    color: str = ui_field("color", group="区段", title="颜色", default="#FF7D00",
                          description="地图上该区段的显示颜色（十六进制，如 #FF7D00）")
    note: str = ui_field("textarea", group="区段", title="备注", default="", rows=3,
                         description="给现场看的补充说明（不影响运行）")


class IconMarkNode(WaypointNodeBase):
    """图标标记：地图**任意位置**放一个可配置的内置矢量图标（门 / 电梯 / 消防栓…）。

    与充电桩 / RFID 卡 / 区段标记的根本区别：那三个都挂在轨道上（按沿轨弧长 `x`
    定位），图标用的是**地图世界坐标 x/y**，可以摆在背景图里的任意位置，
    **没有轨道时也能摆**——比如标"这间是配电室""这里有台阶"。

    造型由 `icon` 指定，取自前端内置图标表
    `frontend/src/components/mapIcons.ts`（20 个矢量图标，canvas 直接画，
    不依赖图片资源）。⚠️ **这里的 options 必须与那份表的中文名一一对应**，
    加图标时两边一起加（`scripts/verify-map-icons.mjs` 会比对，不一致会红）。
    存的是中文名而不是英文 key，因为检视器的下拉框直接显示它。

    同样是纯编排数据，不参与任何运行时决策。
    """

    x: float = ui_field("number", group="位置", title="X (m)", default=0.0, step=0.01,
                        description="地图世界坐标 X（米，与轨道端点同一坐标系）")
    y: float = ui_field("number", group="位置", title="Y (m)", default=0.0, step=0.01,
                        description="地图世界坐标 Y（米，与轨道端点同一坐标系）")
    icon: str = ui_field("select", group="图标", title="图标", default="位置点",
                         options=["门", "窗", "电梯", "楼梯", "卫生间", "消防栓", "灭火器",
                                  "摄像头", "机柜", "带电", "警示", "禁止", "路锥", "安全出口",
                                  "照明", "通风口", "水", "设备", "机器人", "位置点"],
                         description="图标造型（内置矢量图标，见前端 mapIcons.ts）")
    color: str = ui_field("color", group="图标", title="颜色", default="#0068FF",
                          description="图标颜色（十六进制，如 #0068FF）")
    size: float = ui_field("number", group="图标", title="大小 (px)", default=24,
                           min=12, max=64, step=1,
                           description="屏幕像素，**不随地图缩放变化**")
    note: str = ui_field("textarea", group="图标", title="备注", default="", rows=3,
                         description="给现场看的补充说明（不影响运行）")
