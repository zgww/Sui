"""巡检模型(框架, 结构待确认后完善)。"""
from datetime import datetime
from sqlalchemy import Boolean, Column, Integer, String, DateTime, Float, ForeignKey, JSON, Text

from ..database import Base


def now():
    return datetime.utcnow()


class InspectionTask(Base):
    """巡检任务定义(框架)。"""
    __tablename__ = "inspection_tasks"
    id = Column(Integer, primary_key=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    name = Column(String(128))
    plan_json = Column(JSON)          # 巡检内容(航点+动作)
    schedule_json = Column(JSON)      # 时间排期
    archive_snapshot = Column(JSON, nullable=True)  # Immutable configuration used when task was created
    status = Column(String(32), default="idle")  # idle/running/paused/done
    created_at = Column(DateTime, default=now)
    updated_at = Column(DateTime, default=now, onupdate=now)


class InspectionRun(Base):
    """巡检执行记录。"""
    __tablename__ = "inspection_runs"
    id = Column(Integer, primary_key=True)
    task_id = Column(Integer, ForeignKey("inspection_tasks.id"), index=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    inspection_id = Column(String(128))   # 机器人侧的巡检 ID
    status = Column(String(32), default="started")  # started/done/failed/canceled
    start_time = Column(DateTime)
    finish_time = Column(DateTime)
    remark = Column(Text, default="")
    created_at = Column(DateTime, default=now)
    # —— 报表生成（异步任务）——
    report_status = Column(String(32), default="")  # "" / pending / running / done / failed
    report_path = Column(String(512), default="")   # 生成的 Excel 文件路径
    report_error = Column(Text, default="")       # 生成失败的错误信息
    report_generated_at = Column(DateTime)         # 报表生成完成时间


class InspectionResult(Base):
    """巡检结果(单条航点+动作)。"""
    __tablename__ = "inspection_results"
    id = Column(Integer, primary_key=True)
    run_id = Column(Integer, ForeignKey("inspection_runs.id"), index=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    waypoint_id = Column(String(64))
    action_id = Column(String(64))
    code = Column(Integer)             # 0 成功
    picture = Column(String(512))      # 可见光照片 URL
    infrared = Column(String(512))     # 红外照片 URL
    media = Column(String(512))        # 录音/录像 URL
    thermometry_json = Column(JSON)    # 测温数据
    env_json = Column(JSON)            # 环境数据
    pdd_json = Column(JSON)            # 局放数据
    inplace_ts = Column(String(64))    # 到位时间戳
    created_at = Column(DateTime, default=now)


class InspectionActionResult(Base):
    """巡检动作结果 —— 一次巡检里「一个航点下的一个动作」一条。

    ## 先占位后回填

    巡检**开始时**就按任务结构把整批行插好（``status='pending'``），动作执行完
    再回填数据与 ``status``。这么做有三个理由：

    - 下游（检测识别 / 上报平台）可以只轮询 ``status='pending'`` 的行，不用去猜
      执行器现在跑到哪；
    - 执行器崩了、机器人断电，也能看得出卡在第几个动作（占位在那里、没回填）；
    - 断点续跑重做同一个动作时靠 ``attempt`` 区分，不会把上一次的结果覆盖掉。

    ## 定位键

    ``waypoint_id`` / ``action_id`` 是 32 位 hex 业务 id，**跨楼层会重复**
    （见 ``rail/robot.py`` 动作游标注释），所以 ``floor`` 必须进键。
    """
    __tablename__ = "inspection_action_results"
    id = Column(Integer, primary_key=True)
    run_id = Column(Integer, ForeignKey("inspection_runs.id"), index=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    inspection_id = Column(String(64), index=True)
    # —— 定位：这个动作在哪 ——
    floor = Column(Integer, default=0)
    waypoint_id = Column(String(64), default="")
    waypoint_index = Column(Integer, default=0)   # 楼层内序号
    action_id = Column(String(64), default="")
    action_seq = Column(Integer, default=0)       # 航点内动作序号
    action_type = Column(Integer, default=0)      # 设备协议口径 1拍照 2测温 3录像
    attempt = Column(Integer, default=1)          # 第几次执行（续跑/重试 +1）
    # —— 谁执行的、数据往哪送 ——
    executor = Column(String(16), default="fms")        # fms / robot
    detect_type = Column(String(16), default="platform")  # fms 本地消化 / platform 上传平台
    # —— 结果 ——
    status = Column(String(16), default="pending", index=True)  # pending/ok/failed/skipped
    code = Column(Integer, default=0)
    picture = Column(String(512), default="")     # 可见光图
    infrared = Column(String(512), default="")    # 红外图
    media = Column(String(512), default="")       # 录像/录音
    local_path = Column(String(512), default="")  # FMS 执行器落盘的图（相对/绝对）
    reference_image = Column(String(512), default="")  # 抓拍图（参考图）web 路径，算法 referenceImageUrl
    thermometry_json = Column(JSON)
    env_json = Column(JSON)
    pdd_json = Column(JSON)
    raw_json = Column(JSON)                       # 原始结果无损兜底
    inplace_ts = Column(String(64), default="")
    start_time = Column(DateTime)
    finish_time = Column(DateTime)
    duration_ms = Column(Integer, default=0)
    # —— 分发（任务执行器用）——
    # ⚠️ 与 `status` 是**两件事**：status=ok 只说明动作执行完了，不说明数据送出去了。
    # 执行器可能上传失败 / 检测报错 / 正好在这一刻重启，所以要单独记分发状态，
    # 否则一条上传失败的 ok 行下一轮就再也不会被重试（看着像处理完了）。
    dispatch_status = Column(String(16), default="pending", index=True)  # pending/done/failed
    dispatch_mode = Column(String(16), default="")        # upload / detect（分发到哪条路）
    dispatch_attempts = Column(Integer, default=0)        # 分发尝试次数
    dispatched_at = Column(DateTime)                      # 分发成功时刻
    dispatch_error = Column(String(512), default="")      # 最后一次分发失败原因
    # —— 推理对接留痕（detect 路）——
    infer_request_json = Column(JSON)     # 发送推理请求的参数（url/file/form/headers）
    infer_response_json = Column(JSON)    # 同步响应 {http_status, body}（失败也记录）
    infer_result_json = Column(JSON)      # 算法回调的最终处理结果
    schema_version = Column(Integer, default=1)
    created_at = Column(DateTime, default=now)
    updated_at = Column(DateTime, default=now, onupdate=now)


class InspectionPointResult(Base):
    """测温点 / 检测结果 —— 一个动作下的**一个测点**一条（先占位后回填，同上）。

    ## 两种来源

    - **测温点**：来自任务里 ``action.thermometry_points``（配置），巡检开始时就能
      把整批占位插好；温度值等热像仪测温能力接入才有，现在占位先留 ``value=None``。
    - **检测点**：任务执行器跑完检测框流程后回填 —— 一条动作结果可能对应多个检测点
      （一个动作下绑了多个测点，每个测点各有独立检测框与算法流程）。检测结果按
      ``(action_result_id, box_id)`` **更新**已有占位行，不新插行（否则续跑一次多一条）；
      老数据（没有 box_id）退回按 ``(action_result_id, point_id)`` 匹配。

    ## 检测结果为什么放本表而不是新表

    测点维度天然一致（都是「动作 → 测点 → 一个判定值」），共用一个 ``status`` 与
    ``value`` 列能让平台侧只查一张表；算法细节（类别/置信度/检出框）放 JSON 列，
    一期够用，真要按类别做统计再拆子表。
    """
    __tablename__ = "inspection_point_results"
    id = Column(Integer, primary_key=True)
    action_result_id = Column(Integer, ForeignKey("inspection_action_results.id"), index=True)
    run_id = Column(Integer, ForeignKey("inspection_runs.id"), index=True)
    robot_pk = Column(Integer, ForeignKey("robots.id"), index=True)
    inspection_id = Column(String(64), index=True)
    floor = Column(Integer, default=0)
    waypoint_id = Column(String(64), default="")
    action_id = Column(String(64), default="")
    point_id = Column(String(64), default="")
    # —— 检测框身份（kind='detect'）——
    # ⚠️ 与 point_id 是**两件事**：point_id 指向测点档案（可以不绑，本站场景里常常没有），
    # box_id 是检测框自己的唯一 id（`DetectBoxNode.box_id`，编排处生成）。算法回调
    # 的结果框靠 box_id 才能对回"是哪一块区域"，没有它就只能整条丢掉（见
    # `services/alarm_processor.py::_upsert_point`）。老数据没有这两列，为 ""。
    box_id = Column(String(64), default="", index=True)
    box_name = Column(String(128), default="")
    seq = Column(Integer, default=0)              # 动作内测点序号
    kind = Column(String(16), default="thermometry")  # thermometry 测温点 / detect 检测点
    status = Column(String(16), default="pending", index=True)  # pending/ok/failed/skipped
    value = Column(Float)                         # 温度 ℃；检测点写置信度或量测值
    unit = Column(String(16), default="℃")
    image = Column(String(512), default="")       # 测点对应的红外图
    # —— 检测结果（kind='detect' 时回填）——
    detect_flow = Column(String(128), default="")      # 命中的检测流程引用 id
    algorithm = Column(String(128), default="")        # 最终判定算法（DetectorNode 的算法 id）
    label = Column(String(128), default="")            # 判定标签 / 类别名
    confidence = Column(Float)                         # 置信度 0~1
    passed = Column(Boolean)                           # 流程结论：是否通过（None=未判定）
    boxes_json = Column(JSON)                          # 检出框列表 [{x,y,w,h,label,score}]
    detect_json = Column(JSON)                         # 流程跑出来的动作/备注等无损兜底
    raw_json = Column(JSON)                            # 测点配置/原始结果兜底
    created_at = Column(DateTime, default=now)
    updated_at = Column(DateTime, default=now, onupdate=now)
