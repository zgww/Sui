"""任务执行器节点：起后台线程轮询未分发的动作数据，按 `detect_type` 分流处理。

配在 `data/prefabs/启动.prefab.json` 里（启动时这棵树先于其它 prefab 激活）。
节点 `on_active` 起一个**守护线程**，每 `poll_interval` 秒扫一遍
`inspection_action_results` 里 `status='ok'` 且 `dispatch_status='pending'` 的行，
按每条数据的 `detect_type` 决定走哪条路：

    detect_type=platform   ->  HTTP POST 到「平台配置」的 upload_url（旧平台口径）
    detect_type=fms        ->  跑检测框引用的检测流程：调**外部推理服务**拿结果，
                               再按流程算"要不要报"，结果写回测点

分流与载荷构造全在 `app/prefab/task_executor.py`（纯函数，有单测），
本文件只管线程、数据库读写、HTTP 发送、结果回写。

## 为什么是"轮询"而不是"事件"

动作执行完成的那一刻（`rail/robot.py::记录动作结果`）确实知道有新数据了，但：

- 执行器节点可能压根没启动（配置被停用、程序刚重启），事件发出去没人接就丢了；
- 巡检可能正在跑，执行器中途重启，内存里的事件队列一起没了；
- 而 `dispatch_status='pending'` 是**落在库里**的，重启后照样能接着处理。

轮询是"至少一次"的：代价是多一次查询，换来的是"数据不会因为谁没在听而丢"。
真正的幂等靠 `dispatch_status` 状态机保证（见 `task_executor.py` 的说明）。

## 一次处理成不成功，怎么算

- **成功**：置 `dispatch_status='done'` + `dispatched_at`，下一轮扫不到；
- **失败**：`dispatch_attempts += 1`、`dispatch_status='failed'`、`dispatch_error` 记原因。
  `failed` 的行**下一轮还会被捞起来重试**（`max_attempts` 未耗尽时）——上传失败
  的数据下一轮不重试，就等于永久丢了。所以候选条件是
  `dispatch_status != 'done'`（不是 `== 'pending'`）。
- **跳过**（录像动作 / 没配地址 / 没框没流程）：直接置 `done` 并记原因，
  别一直以同一个理由失败刷 attempts。

## ⚠️ 算法推理在外部 HTTP 服务里

`detect_type=fms` 的算法推理**不在本进程**：`DetectorNode` 只说"用哪个算法、
什么参数"，真正算的那一步是 HTTP POST 到「平台配置」节点的 `infer_url`
（见 `task_executor.py::infer_payload` 的请求形状）。
"""
from __future__ import annotations

import json
import logging
import threading
import time
from datetime import datetime
from pathlib import Path
from typing import Any, ClassVar, NamedTuple, Optional

from pydantic import PrivateAttr

from ..base import Context, NodeBase, ui_field
from ..task_executor import (
    DISPATCH_DONE,
    DISPATCH_FAILED,
    DISPATCH_PENDING,
    PendingAction,
    PointResult,
    apply_flow_result,
    group_plans,
    index_flows,
    infer_payload,
    infer_result,
    normalize_detect_type,
    plan_dispatch,
    to_pending,
    upload_header,
    upload_payload,
)

logger = logging.getLogger(__name__)


class DetectTarget(NamedTuple):
    """一个检测框摊平后的"要检测什么"。

    用 `NamedTuple` 而不是裸元组：字段涨到 8 个之后，`t[6]` / `t[7]` 这种下标
    在调用点读不出意思（而元组解包一改长度，两处调用一起悄悄错位）。
    保持可解包 / 可下标，所以老的 `t[0]` 写法照旧能用。
    """

    flow_ref: str        # 检测流程引用 id（流程根 detect_id 或文件名）
    algorithm: str       # 流程里 DetectorNode 绑定的算法 id（可空）
    point_id: str        # 绑定的测点档案 id（**可空**，本站场景里常常没有）
    point_name: str      # 测点名（镜像，可空）
    region: dict         # 归一化区域 {shape, points}
    params: dict         # 算法参数
    box_id: str          # 检测框自己的唯一 id（一定有）
    box_name: str        # 框名：框节点名 → 测点名 → 检测框N


class TaskExecutorNode(NodeBase):
    """任务执行器：把巡检动作数据分发给平台或本地检测流程。

    这个节点是"巡检数据从库里出去"的唯一出口——没有它，动作数据就只是一堆
    `pending` 行躺在 SQLite 里（旧系统靠 cmd=104 同一时刻上报，现在改成了
    "先落库、再异步分发"，两个阶段解耦后各自都能重试）。
    """

    # ------------------------------------------------------------ 配置
    poll_interval: float = ui_field(
        "number", min=0.5, max=600, group="执行", default=5,
        title="轮询间隔（秒）",
        description="扫一遍待分发动作数据的间隔。巡检动作是秒级产生的，"
                    "间隔太小只是空转查询，太大则数据要等一会儿才上报")
    batch_size: int = ui_field(
        "number", min=1, max=500, group="执行", default=50, title="每轮最多处理",
        description="一次轮询最多取多少条。取小一点可以让长时间运行的巡检"
                    "（数据持续产生）边跑边报，不必等全部攒完")
    max_attempts: int = ui_field(
        "number", min=0, max=100, group="执行", default=5, title="最大重试次数",
        description="同一条数据分发失败多少次后不再重试（0 = 不限次）。"
                    "超限的数据保持 failed 不动——它是「还没送出去」，"
                    "改成 done 会让它永远消失")
    executor: str = ui_field(
        "select", group="执行", default="fms", options=["fms"],
        description="谁产生的这批数据。当前只有 fms（本系统执行动作）；"
                    "留作区分 robot 直传的扩展位")
    upload_url: str = ui_field(
        "text", group="平台", default="", title="上报地址（覆盖）",
        description="临时覆盖「平台配置」节点里的上报地址；留空 = 用平台配置节点的值。"
                    "**正常情况下不要填**——地址是机器人属性，应该改 platform 节点")
    infer_url: str = ui_field(
        "text", group="推理服务", default="", title="推理地址（覆盖）",
        description="临时覆盖「平台配置」节点里的推理服务地址；留空 = 用平台配置节点的值")
    dry_run: bool = ui_field(
        "checkbox", group="执行", default=False, title="演练（不外发）",
        description="只记日志、只算检测结论，**不发 HTTP、不回写库**。"
                    "刚配上去时建议先勾上，确认分流和载荷都对再取消")
    timeout: float = ui_field(
        "number", group="执行", default=5.0, min=0.5, max=120, step=0.5,
        title="HTTP 超时（秒）",
        description="留空/0 = 用「平台配置」节点的超时")

    # ------------------------------------------------------------ 运行时
    _thread: Optional[threading.Thread] = PrivateAttr(default=None)
    _stop: Optional[threading.Event] = PrivateAttr(default=None)
    _ctx: Optional[Context] = PrivateAttr(default=None)
    # ⚠️ 不能叫 `_state`：那是 NodeBase 的节点状态（inactive/active/error）
    #: 检测流程引用 id -> 已 build 的流程根节点（懒加载 + 缓存）
    _flows: dict = PrivateAttr(default_factory=dict)
    #: 检测流程目录的 mtime 快照，目录变了就重新加载（改了流程不用重启）
    _flows_stamp: Optional[float] = PrivateAttr(default=None)
    #: 跨事件的检测状态（节流 / 连续确认），按"流程 + 测点"分桶
    _detect_state: Any = PrivateAttr(default=None)
    #: 计数字段（status() 展示用）
    _stats: dict = PrivateAttr(default_factory=dict)

    # ============================================================ 生命周期

    def on_active(self, ctx: Context) -> None:
        from ..detect_pipeline import DetectState

        self._ctx = ctx
        self._detect_state = DetectState()
        self._stats = {"uploaded": 0, "detected": 0, "skipped": 0, "failed": 0}
        self._stop = threading.Event()
        self._thread = threading.Thread(
            target=self._run, name="prefab-task-executor", daemon=True)
        self._thread.start()
        logger.info("[prefab] %s: 任务执行器已启动（间隔 %ss，批量 %s，dry_run=%s）",
                    self.name or self.type, self.poll_interval,
                    self.batch_size, self.dry_run)

    def on_deactive(self, ctx: Context) -> None:
        stop = self._stop
        if stop is not None:
            stop.set()
        th = self._thread
        # 最多等两个轮询周期：线程里可能正好有一个 HTTP 请求在跑
        if th is not None and th.is_alive():
            th.join(timeout=max(1.0, float(self.poll_interval) * 2 + float(self.timeout or 5)))
        self._thread, self._stop, self._ctx = None, None, None
        logger.info("[prefab] %s: 任务执行器已停止", self.name or self.type)

    # ============================================================ 线程体

    def _run(self) -> None:
        stop = self._stop
        while stop is not None and not stop.is_set():
            try:
                self._scan_once()
            except Exception:
                # 一次扫描出错不能让线程死掉（否则"上报悄无声息停了"）
                logger.exception("[prefab] %s: 任务执行器扫描异常", self.name or self.type)
            if stop is not None:
                stop.wait(max(0.5, float(self.poll_interval)))

    # ============================================================ 一轮扫描

    def _scan_once(self) -> None:
        pending = self._load_pending()
        if not pending:
            return
        plans = [
            plan_dispatch(pa, flows=self._flows_for(pa), max_attempts=int(self.max_attempts))
            for pa in pending
        ]
        grouped = group_plans(plans)
        for plan in grouped.get("skip", []):
            self._finish_skip(plan.pending, plan.reason)
        for plan in grouped.get("upload", []):
            self._do_upload(plan.pending)
        for plan in grouped.get("detect", []):
            self._do_detect(plan.pending, plan.flows, plan.image)

    # ------------------------------------------------------------ 取待处理

    def _load_pending(self) -> list[PendingAction]:
        """查 `status='ok'` 且**还没分发成功**的动作行。

        ⚠️ 条件是 `dispatch_status != 'done'` 而不是 `== 'pending'`：`failed` 的行
        必须能被捞起来重试。只查 pending 的话，一条上传失败的数据会被永久搁浅
        ——已经标了 failed、又永远不再被选中，现场再也看不到它去哪了。
        真正的重试上限由 `max_attempts` 在 `plan_dispatch` 里兜。
        """
        from ...database import SessionLocal
        from ...models import InspectionActionResult
        from ...rail.recorder import STATUS_OK

        db = SessionLocal()
        try:
            rows = (
                db.query(InspectionActionResult)
                .filter(
                    InspectionActionResult.status == STATUS_OK,
                    InspectionActionResult.dispatch_status != DISPATCH_DONE,
                )
                .order_by(InspectionActionResult.id)
                .limit(int(self.batch_size))
                .all()
            )
            out: list[PendingAction] = []
            for r in rows:
                if self.executor and str(getattr(r, "executor", "") or "") not in ("", self.executor):
                    continue
                out.append(to_pending(r))
            return out
        except Exception:
            logger.exception("[prefab] %s: 查询待分发数据失败", self.name or self.type)
            return []
        finally:
            db.close()

    # ------------------------------------------------------------ 分流：跳过

    def _finish_skip(self, pa: PendingAction, reason: str) -> None:
        """跳过不是错误：置 done + 记原因，别一直以同一个理由刷 attempts。"""
        self._stats["skipped"] = int(self._stats.get("skipped", 0)) + 1
        logger.info("[prefab] %s: 动作数据 %s 跳过（%s）",
                    self.name or self.type, pa.key, reason or "无原因")
        self._mark(pa, DISPATCH_DONE, mode="", error=reason or "")

    # ------------------------------------------------------------ 分流：上报平台

    def _do_upload(self, pa: PendingAction) -> None:
        cfg = self._platform_cfg()
        url = str(self.upload_url or "").strip() or cfg["upload_url"]
        if not url:
            # 没配地址**不算失败**：用户可能就是还没接平台。置 done 并记原因，
            # 免得这条数据每 5 秒重试一次把日志刷满。
            self._finish_skip(pa, "未配置平台上报地址（平台配置节点）")
            return

        payload = upload_payload(pa, extra=self._extra_fields(pa))
        if self.dry_run:
            self._stats["uploaded"] = int(self._stats.get("uploaded", 0)) + 1
            self._finish_skip(pa, f"[dry_run] 应上报到 {url}")
            return

        try:
            ok, detail = self._post(url, payload, cfg)
        except Exception as exc:  # noqa: BLE001 - 网络异常一律按"这轮失败"处理
            ok, detail = False, str(exc)
        if ok:
            self._stats["uploaded"] = int(self._stats.get("uploaded", 0)) + 1
            logger.info("[prefab] %s: 动作数据 %s 已上报平台 %s",
                        self.name or self.type, pa.key, url)
            self._mark(pa, DISPATCH_DONE, mode="upload", error="")
        else:
            self._stats["failed"] = int(self._stats.get("failed", 0)) + 1
            logger.warning("[prefab] %s: 动作数据 %s 上报失败（%s）",
                           self.name or self.type, pa.key, detail)
            self._mark(pa, DISPATCH_FAILED, mode="upload", error=detail)

    # ------------------------------------------------------------ 分流：本地检测

    def _do_detect(self, pa: PendingAction, flows: list[str], image: str) -> None:
        """跑检测框引用的流程：异步调外部推理服务 -> 等回调 -> 写回测点。

        ⚠️ 现在改成异步模式：
        1. 提交推理任务到算法服务（带 callbackUrl）
        2. 立即返回，不等结果
        3. 算法服务识别完成后，回调 callbackUrl，由回调接口处理结果
        """
        cfg = self._platform_cfg()
        infer_url = str(self.infer_url or "").strip() or cfg["infer_url"]
        if not infer_url:
            self._finish_skip(pa, "未配置推理服务地址（平台配置节点）")
            return

        flow_map = self._flow_map()
        targets = self._detect_targets(pa, flows)
        if not targets:
            self._finish_skip(pa, "检测框没有绑定测点，检测结果无处可写")
            return

        # 构造回调地址：算法服务识别完成后回调这个地址
        # 从 RobotConfig 拿 fmsHost（FMS 的 ip:port），拼接出完整的回调 URL
        fms_host = self._fms_host()
        if not fms_host:
            self._finish_skip(pa, "未配置 FMS 地址（RobotConfig.fmsHost），算法回调无法到达")
            return
        callback_url = f"http://{fms_host}/api/inspection/report/detect_callback"

        # 过滤掉流程不存在的框
        valid = []
        missing = 0
        for t in targets:
            flow_ref = t[0]
            if flow_map.get(flow_ref) is None:
                logger.warning("[prefab] %s: 检测流程 %r 不存在，跳过该框",
                               self.name or self.type, flow_ref)
                missing += 1
                continue
            valid.append(t)

        if not valid:
            self._stats["failed"] = int(self._stats.get("failed", 0)) + 1
            self._mark(pa, DISPATCH_FAILED, mode="detect",
                       error="检测流程均不存在")
            return

        # 一个动作（一张图）= 一次请求，所有框打包进 info.boxs
        try:
            self._infer_async(
                infer_url, pa, cfg,
                image=image,
                targets=valid,
                callback_url=callback_url,
            )
        except Exception as exc:
            self._stats["failed"] = int(self._stats.get("failed", 0)) + 1
            self._mark(pa, DISPATCH_FAILED, mode="detect",
                       error=f"提交推理任务失败: {exc}")
            logger.warning("[prefab] %s: 提交推理任务失败: %s",
                           self.name or self.type, exc)
            return

        if self.dry_run:
            self._stats["detected"] = int(self._stats.get("detected", 0)) + 1
            logger.info("[prefab] %s: [dry_run] 提交 1 个推理任务（%d 框），未回写库",
                        self.name or self.type, len(valid))
            self._finish_skip(pa, f"[dry_run] 提交推理任务（{len(valid)} 框）")
            return

        # 提交成功，标记 done（测点结果由回调接口写回）
        self._stats["detected"] = int(self._stats.get("detected", 0)) + 1
        self._mark(pa, DISPATCH_DONE, mode="detect", error="", points=[])
        logger.info("[prefab] %s: 已提交推理任务（%d 框%s），等待算法回调",
                    self.name or self.type, len(valid),
                    f"，{missing} 框流程缺失" if missing else "")

    def _event_from(self, raw: Any, algorithm: str):
        """推理服务响应 -> `DetectEvent`（喂给流程树）。"""
        from ..detect_pipeline import DetectEvent

        norm = infer_result(raw)
        if norm.get("raw") is None:
            return None
        if norm.get("ok") and norm.get("passed") is None and not norm.get("boxes"):
            # 有响应但没有结构化结论：当作"没检出"，而不是解析失败——
            # 格式对不上时最安全的语义是"这次没报"，而不是让数据卡在 failed
            pass
        box = (norm.get("boxes") or [None])[0] or {}
        return DetectEvent(
            algorithm=str(algorithm or ""),
            label=str(norm.get("label") or ""),
            confidence=float(norm.get("confidence") or 0.0),
            source="抓拍图",
            point_id="",
            point_name="",
            value=norm.get("value"),
            # 命中位置取置信度最高那个框的中心（区域过滤用归一化坐标）
            x=(float(box.get("x", 0.0)) + float(box.get("w", 1.0)) / 2.0) if box else None,
            y=(float(box.get("y", 0.0)) + float(box.get("h", 1.0)) / 2.0) if box else None,
        )

    def _run_flow(self, root: Any, event: Any, flow_ref: str, point_id: str):
        """跑一遍流程树（纯函数）。状态按"流程 + 测点"分桶，节流/确认才有记忆。"""
        from ..detect_pipeline import run_flow

        key = f"{flow_ref}::{point_id}"
        return run_flow(root, event, state=self._detect_state, key=key)

    # ============================================================ 检测目标解析

    def _flows_for(self, pa: PendingAction) -> list[str]:
        """这条动作数据"该跑哪些流程"—— 从它所在航点/动作下挂的检测框查。

        实时查航点树（不缓存整棵树）：检测框是编排数据，改一次就该生效，
        缓存会让"改了框却没反应"这种最容易被当成 bug 的行为成立。
        查不到（航点树被删/改名）返回空 = skip，不是错误。
        """
        if normalize_detect_type(pa.detect_type) != "fms":
            return []
        try:
            action = self._find_action_node(pa)
        except Exception:
            logger.exception("[prefab] %s: 查航点树失败（%s）",
                             self.name or self.type, pa.key)
            return []
        if action is None:
            return []
        refs: list[str] = []
        for box in self._detect_boxes(action):
            ref = str(getattr(box, "detect_flow", "") or "").strip()
            if ref and ref not in refs:
                refs.append(ref)
        return refs

    def _detect_targets(self, pa: PendingAction, flows: list[str]) -> list[DetectTarget]:
        """把"要检测什么"摊平成逐框清单（见 `DetectTarget`）。

        一个动作下可能挂多个检测框，**每个框是一个测点**（框可以绑定测点 id）。
        一个测点只能绑一处（占用表由页面维护），所以按 point_id 去重、先到先得。

        ⚠️ `point_id` **不是必须的**（本站场景里常常没有），所以每个框还要带上
        自己的 `box_id`：算法结果回来时靠它对回"是哪一块区域"（见
        `services/alarm_processor.py`）。`box_name` 取 框节点名 → 测点名 → 检测框N。
        """
        if normalize_detect_type(pa.detect_type) != "fms":
            return []
        try:
            action = self._find_action_node(pa)
        except Exception:
            return []
        if action is None:
            return []
        want = {str(f) for f in flows}
        out: list[DetectTarget] = []
        seen_points: set[str] = set()
        for box in self._detect_boxes(action):
            ref = str(getattr(box, "detect_flow", "") or "").strip()
            if not ref or (want and ref not in want):
                continue
            pid = str(getattr(box, "point_id", "") or "").strip()
            if pid and pid in seen_points:
                logger.warning("[prefab] %s: 测点 %s 被多个检测框绑定，只取先到的那一个",
                               self.name or self.type, pid)
                continue
            if pid:
                seen_points.add(pid)
            pts = list(getattr(box, "points", None) or [])
            region = {
                "shape": str(getattr(box, "shape", "") or "rect"),
                "points": [{"x": float(p.get("x", 0.0)), "y": float(p.get("y", 0.0))}
                           for p in pts if isinstance(p, dict)],
            }
            algo, params = self._algorithm_of(ref, box)
            point_name = str(getattr(box, "point_name", "") or "")
            box_id = str(getattr(box, "box_id", "") or "").strip()
            if not box_id:
                # 老数据（`box_id` 字段加进来之前编的树）没有框身份：退回 point_id，
                # 至少让**绑了测点**的框还能对上（与改造前的行为一致）。
                # ⚠️ 没绑测点的老框这里认不出来 —— 打开一次航点树编排页会自动补
                # `box_id` 并落盘（见 `utils/inspectionBuild.ensureBoxIds`），补过之后就正常了。
                box_id = pid
                if not box_id:
                    logger.warning(
                        "[prefab] %s: 检测框 %r 既没有 box_id 也没有 point_id，"
                        "算法结果将无法回写（请在航点树编排页打开并保存一次以补生成检测框 ID）",
                        self.name or self.type, str(getattr(box, "name", "") or ""))
            out.append(DetectTarget(
                flow_ref=ref,
                algorithm=algo,
                point_id=pid,
                point_name=point_name,
                region=region,
                params=params,
                box_id=box_id,
                # 框名优先级：框节点名 → 测点名 → 检测框N（N 是动作内第几个框）
                box_name=str(getattr(box, "name", "") or "").strip()
                         or point_name or f"检测框{len(out) + 1}",
            ))
        return out

    @staticmethod
    def _detect_boxes(action: Any) -> list[Any]:
        """动作点下挂的检测框（只认直接子节点，与前端工具一致）。"""
        out = []
        for c in getattr(action, "child_nodes", None) or []:
            if getattr(c, "type", "") == "DetectBoxNode":
                out.append(c)
        return out

    def _algorithm_of(self, flow_ref: str, box: Any) -> tuple[str, dict]:
        """这条检测要交给推理服务的算法 id 与参数。

        算法从**流程树里的算法节点**取（`DetectorNode` 子类的 `algorithm` 字段，
        由类属性固定）——这与 `detect_pipeline` 判定时用的键一致。
        流程里没有算法节点时，退回检测框上那个已废弃的只读 `algorithm` 镜像
        （老数据里可能只有它）。
        """
        root = self._flow_map().get(flow_ref)
        if root is not None:
            node = self._first_detector(root)
            if node is not None:
                return (self._node_algorithm(node), self._algo_params(node))
        legacy = str(getattr(box, "algorithm", "") or "").strip()
        return legacy, {}

    @staticmethod
    def _node_algorithm(node: Any) -> str:
        """算法节点对应的算法标识。

        - MeterAlgorithmNode（兼容现有推理服务）：用选中的 panel_algorithm
          （panel_list 的 name 编码，如 1_0_0_1_53_0）；
        - 其余固定算法节点：用类属性绑定的 algorithm（如 person_intrusion）。
        """
        if getattr(node, "type", "") == "MeterAlgorithmNode":
            return str(getattr(node, "panel_algorithm", "") or "").strip()
        return str(getattr(node, "algorithm", "") or "")

    def _panel_of(self, flow_ref: str, name_map: dict) -> tuple[str, str]:
        """从流程引用里的 MeterAlgorithmNode 取算法类型，返回 (name编码, 中文名)。

        `_infer_async` 专用：当前算法推理服务只认 MeterAlgorithmNode 配置的算法，
        box.name 必须是 panel_list 的 name 编码。流程里没有该节点 / 有但没选
        算法，返回 ("", "")，调用方据此跳过该框。
        """
        root = self._flow_map().get(flow_ref)
        if root is None:
            return "", ""
        node = self._first_detector(root)
        if node is None or getattr(node, "type", "") != "MeterAlgorithmNode":
            return "", ""
        name = str(getattr(node, "panel_algorithm", "") or "").strip()
        if not name:
            return "", ""
        return name, str(name_map.get(name) or name)

    @staticmethod
    def _load_panel_name_map() -> dict:
        """加载 panel_list.json：name 编码 -> 中文显示名（每次读取，不做缓存）。"""
        try:
            from ...config import DATA_DIR
            f = DATA_DIR / "panel_list.json"
            if f.is_file():
                raw = json.loads(f.read_text(encoding="utf-8"))
                return {
                    str(it.get("name")): str(it.get("display_name") or it.get("name"))
                    for it in (raw or [])
                    if isinstance(it, dict) and it.get("name")
                }
        except Exception:  # noqa: BLE001 - 清单读不到不应让提交整体崩
            pass
        return {}

    @staticmethod
    def _algo_params(node: Any) -> dict:
        """算法节点上除通用字段外的配置（喂给推理服务）。"""
        dump = getattr(node, "model_dump", None)
        if not callable(dump):
            return {}
        try:
            data = dict(dump(exclude={"children"}))
        except Exception:  # noqa: BLE001
            return {}
        for k in ("type", "name", "enabled", "description", "algorithm", "note",
                  "threshold", "labels", "max_results", "params"):
            data.pop(k, None)
        return data

    @staticmethod
    def _first_detector(root: Any):
        """流程树里的第一个算法检测节点（DFS）。"""
        from ..detect_pipeline import _DETECTOR_TYPES

        stack = [root]
        while stack:
            node = stack.pop(0)
            if getattr(node, "type", "") in _DETECTOR_TYPES:
                return node
            stack.extend(getattr(node, "child_nodes", None) or [])
        return None

    # ------------------------------------------------------------ 航点树查找

    def _find_action_node(self, pa: PendingAction):
        """按 (楼层, 航点 id, 动作 id) 在航点树里找那个 `ActionPointNode`。

        楼层必须进键：`waypoint_id` / `action_id` 是 32 位 hex 业务 id，**跨楼层
        会重复**（见 `models/inspection.py` 的定位键说明）。找不到返回 None。
        """
        from ..inspection_build import collect_waypoints
        from ..registry import build

        for spec in self._iter_waypoint_specs():
            try:
                root = build(spec.get("root") or {})
            except Exception:
                continue
            for pick in collect_waypoints(root):
                if pick.floor != pa.floor:
                    continue
                if str(getattr(pick.node, "wp_id", "") or "") != pa.waypoint_id:
                    continue
                for c in getattr(pick.node, "child_nodes", None) or []:
                    if getattr(c, "type", "") != "ActionPointNode":
                        continue
                    if str(getattr(c, "action_id", "") or "") != pa.action_id:
                        continue
                    return c
        # 退回按动作 id 找（老数据里动作 id 可空）
        for spec in self._iter_waypoint_specs():
            try:
                root = build(spec.get("root") or {})
            except Exception:
                continue
            stack = [root]
            while stack:
                node = stack.pop(0)
                if getattr(node, "type", "") == "ActionPointNode" \
                        and str(getattr(node, "action_id", "") or "") == pa.action_id:
                    return node
                stack.extend(getattr(node, "child_nodes", None) or [])
        return None

    @staticmethod
    def _iter_waypoint_specs():
        """遍历 `data/prefabs/waypoint` 下全部航点树 spec。"""
        from ...config import WAYPOINT_PREFAB_DIR

        root = Path(WAYPOINT_PREFAB_DIR)
        if not root.exists():
            return
        for p in sorted(root.rglob("*.prefab.json")):
            if not p.is_file():
                continue
            try:
                yield json.loads(p.read_text(encoding="utf-8"))
            except Exception as exc:  # noqa: BLE001 - 单个坏文件不影响其它树
                logger.warning("[prefab] 航点树 %s 解析失败: %s", p, exc)

    # ============================================================ 检测流程树

    def _flow_map(self) -> dict:
        """`{引用 id: 流程根节点实例}`，目录 mtime 变了就重新加载。

        与 `waypoint_prefab.read_algorithms` 同一个取舍：编排数据改了就该生效，
        **不做长期缓存**——只是目录 mtime 没变时跳过重读，避免每轮都 build 全目录。
        """
        from ...config import DETECT_PREFAB_DIR

        root_dir = Path(DETECT_PREFAB_DIR)
        stamp = self._dir_stamp(root_dir)
        if self._flows and stamp is not None and stamp == self._flows_stamp:
            return self._flows
        specs: list[tuple[str, dict]] = []
        if root_dir.exists():
            for p in sorted(root_dir.rglob("*.prefab.json")):
                if not p.is_file():
                    continue
                try:
                    specs.append((p.name, json.loads(p.read_text(encoding="utf-8"))))
                except Exception as exc:  # noqa: BLE001
                    logger.warning("[prefab] %s: 检测流程 %s 解析失败: %s",
                                   self.name or self.type, p, exc)
        self._flows = index_flows(specs)
        self._flows_stamp = stamp
        return self._flows

    @staticmethod
    def _dir_stamp(root: Path) -> Optional[float]:
        """目录内容变更的时间戳（取最新文件 mtime + 文件数），目录不存在返回 None。"""
        if not root.exists():
            return None
        latest = 0.0
        n = 0
        for p in root.rglob("*.prefab.json"):
            if not p.is_file():
                continue
            n += 1
            try:
                latest = max(latest, p.stat().st_mtime)
            except OSError:
                pass
        return latest * 1000 + n

    # ============================================================ HTTP

    def _post(self, url: str, payload: dict, cfg: dict) -> tuple[bool, str]:
        """POST 一份 JSON，按配置重试。返回 `(成功?, 说明/错误)`。"""
        retry = int(cfg.get("retry") or 0)
        attempts = max(1, retry + 1)
        last = ""
        for i in range(attempts):
            ok, detail = self._post_once(url, payload, cfg)
            if ok:
                return True, detail
            last = detail
            if i + 1 < attempts:
                time.sleep(min(2.0, 0.3 * (i + 1)))
        return False, last

    def _post_once(self, url: str, payload: dict, cfg: dict) -> tuple[bool, str]:
        import httpx

        headers = {"Content-Type": "application/json"}
        headers.update(upload_header(cfg.get("auth_header") or ""))
        try:
            resp = httpx.post(url, json=payload, headers=headers,
                              timeout=float(self._timeout(cfg)),
                              verify=bool(cfg.get("verify_tls", True)))
        except Exception as exc:  # noqa: BLE001 - 网络异常交给调用方判失败
            return False, f"{type(exc).__name__}: {exc}"
        if 200 <= resp.status_code < 300:
            return True, f"HTTP {resp.status_code}"
        body = (resp.text or "")[:200]
        return False, f"HTTP {resp.status_code} {body}"

    def _infer(self, url: str, pa: PendingAction, cfg: dict, *, image: str,
               flow: str, algorithm: str, region: dict, params: dict) -> Any:
        """调外部推理服务，返回**原始响应体**（能是 dict 就直接是 dict）。"""
        import httpx

        payload = infer_payload(pa, flow=flow, algorithm=algorithm, image=image,
                                region=region, extra=params)
        headers = {"Content-Type": "application/json"}
        headers.update(upload_header(cfg.get("auth_header") or ""))
        resp = httpx.post(url, json=payload, headers=headers,
                          timeout=float(self._timeout(cfg)),
                          verify=bool(cfg.get("verify_tls", True)))
        if not (200 <= resp.status_code < 300):
            raise RuntimeError(f"推理服务 HTTP {resp.status_code} {(resp.text or '')[:200]}")
        try:
            return resp.json()
        except Exception:  # noqa: BLE001 - 非 JSON 响应按"无结构化结论"处理
            return resp.text

    def _infer_async(self, url: str, pa: PendingAction, cfg: dict, *, image: str,
                     targets: list, callback_url: str) -> None:
        """异步调外部推理服务（multipart/form-data），带 callbackUrl。

        一个动作点（一张图）= **一次请求**：这张图上的所有检测框都构建进
        info.boxs，算法服务一次处理完再回调 callbackUrl。本方法立即返回。

        Args:
            url: 算法服务地址（如 http://127.0.0.1:10086/upload_tactics）
            pa: 待处理的动作数据
            cfg: 平台配置
            image: 图片路径（web 路径 /data/inspection/... 或本地路径）
            targets: 该动作的检测目标列表，每项 `DetectTarget`
                     （流程引用 / 算法 / 测点 / 区域 / 参数 / 框 id / 框名）
            callback_url: 回调地址
        """
        import httpx
        from pathlib import Path

        # 图片文件：web 路径（/data/inspection/...）转本地文件路径
        img_str = str(image or "").strip()
        if img_str.startswith("/data/inspection/"):
            from ...config import DATA_DIR
            rel = img_str[len("/data/inspection/"):]
            img_path = DATA_DIR / "inspection" / rel
        else:
            img_path = Path(img_str)
        if not img_path.exists():
            raise RuntimeError(f"图片文件不存在: {image}")

        # 构造 info.boxs：每个检测框一项（id 从 1 递增）
        # 注意算法服务用 Python eval 解析 info，不能出现 JSON 的 null/true/false
        img_w, img_h = self._image_size(img_path)
        # box.name 直接从该流程的 MeterAlgorithmNode 取算法类型（name 编码），
        # 中文名反查 panel_list.json。当前推理服务只认 MeterAlgorithmNode。
        panel_name_map = self._load_panel_name_map()
        boxs = []
        #: 只存请求留痕、不发给算法：每个实际提交框对应哪个流程/测点/区域。
        #: 回调时结果框靠它定位流程（提交时跳过了无算法框，顺序对不上检测框）
        box_flow = []
        for t in targets:
            mark_name, mark_display = self._panel_of(t.flow_ref, panel_name_map)
            if not mark_name:
                # 流程里没有 MeterAlgorithmNode，或有但没选算法：该框无可执行算法
                logger.warning("[prefab] %s: 流程 %r 未在 MeterAlgorithmNode 选择算法，跳过该框",
                               self.name or self.type, t.flow_ref)
                continue
            px_box = self._region_to_pixel_box(t.region, img_w, img_h)
            boxs.append({
                "id": len(boxs) + 1,
                "pointId": str(t.point_id or ""),
                # box_id / box_name：本框的**身份**与**人看的名字**。
                # ⚠️ 加这两个字段是因为 pointId 可能是空的（本站场景常常没绑测点）：
                # 只靠 pointId，结果回来了没法确认是哪一个检测框出的。算法服务一般会把
                # 入参原样带回结果框，回调时就能靠 box_id 对回流程/测点（见
                # `services/alarm_processor.py::_lookup_bf`）。
                "box_id": str(t.box_id or ""),
                "box_name": str(t.box_name or ""),
                "box": px_box,
                "name": mark_name,
                "display_name": mark_display,
                "boxType": "1",
                "parameter": "0",
                "code": "0",
                "msg": "",
                "scores": "",
                "display": "",
                "error": "",
                "angle": "",
                "correction": "0",
            })
            box_flow.append({
                "id": len(boxs),
                "flow_ref": t.flow_ref,
                "point_id": str(t.point_id or ""),
                "point_name": str(t.point_name or ""),
                "box_id": str(t.box_id or ""),
                "box_name": str(t.box_name or ""),
                "region": t.region,
            })
        if not boxs:
            raise RuntimeError("检测流程未在 MeterAlgorithmNode 配置算法，无可提交的 boxs")
        info = {
            "boxs": boxs,
            "locals": [],
        }

        # 参考图 referenceImageUrl：用航点树编排时拍照动作点配置的"抓拍图片"
        # （pa.reference_image，web 路径）。人员越界(3006)这类"大框 AI 检测"，
        # 算法服务 fix_object 必须在"有参考图"分支才走 dispatch_task_handlers
        # → TaskIntrusion（无参考图会退回 match_model，mapping 不含 3006）。
        fms_host = self._fms_host() or ""
        ref_img = (getattr(pa, "reference_image", "") or "").strip()
        if ref_img.startswith("/data/") and fms_host:
            reference_url = f"http://{fms_host}{ref_img}"
        elif ref_img:
            # 已是完整 URL 或其它可解析形式，原样传
            reference_url = ref_img
        elif img_str.startswith("/data/inspection/") and fms_host:
            # 兜底：动作点没配抓拍图时，用当前巡检图自己
            reference_url = f"http://{fms_host}{img_str}"
        else:
            reference_url = img_path.name

        # algorithmTempId：唯一标识这一次请求 -> 用动作结果 id（一个动作一次请求）
        algorithm_temp_id = str(pa.action_result_id or pa.id)

        # 构造 multipart/form-data
        file_size = img_path.stat().st_size
        file_handle = open(img_path, "rb")
        files = {
            "file": (img_path.name, file_handle, "image/jpeg"),
        }
        data = {
            "mark_id": "24",          # 24 = 通用目标检测（mark_dic_24，异步回调模式）
            "filename": img_path.name,
            "algorithmTempId": algorithm_temp_id,
            "info": json.dumps(info, ensure_ascii=False),
            "referenceImageUrl": reference_url,
            "callbackUrl": callback_url,
            "taskResultId": algorithm_temp_id,
            "taskExeDate": datetime.now().strftime("%Y%m%d"),
        }

        headers = {}
        headers.update(upload_header(cfg.get("auth_header") or ""))

        # 打印请求参数（文件只打印名称和大小，不打印二进制内容）
        logger.info(
            "[infer] POST %s\n  headers=%s\n  file=%s (%d bytes)\n  form=%s",
            url, headers, img_path.name, file_size,
            {k: v for k, v in data.items()},
        )

        # 记录请求参数（file 只记名称/大小，不含二进制）
        request_trace = {
            "url": url, "method": "POST", "headers": headers,
            "file": {"name": img_path.name, "size": file_size,
                     "content_type": "image/jpeg"},
            "form": {k: v for k, v in data.items()},
            "box_flow": box_flow,
            "sent_at": datetime.now().isoformat(),
        }
        self._save_infer_trace(pa, request=request_trace)

        try:
            resp = httpx.post(url, data=data, files=files, headers=headers,
                              timeout=float(self._timeout(cfg)),
                              verify=bool(cfg.get("verify_tls", True)))
        except Exception as exc:
            # 连接失败等：记录响应（无 http_status），再抛出
            self._save_infer_trace(pa, response={
                "http_status": None, "body": "", "error": str(exc),
                "received_at": datetime.now().isoformat(),
            })
            raise
        finally:
            file_handle.close()

        # 打印响应
        logger.info("[infer] <- HTTP %d body=%s",
                    resp.status_code, resp.text or "")

        # 记录同步响应（含 http status，失败也记录）
        self._save_infer_trace(pa, response={
            "http_status": resp.status_code,
            "body": (resp.text or "")[:2000],
            "received_at": datetime.now().isoformat(),
        })

        if not (200 <= resp.status_code < 300):
            raise RuntimeError(f"算法服务 HTTP {resp.status_code} {(resp.text or '')[:200]}")

        logger.info("[prefab] %s: 已提交算法推理任务 action_result_id=%s 框数=%d",
                    self.name or self.type, algorithm_temp_id, len(boxs))

    def _timeout(self, cfg: dict) -> float:
        t = float(self.timeout or 0)
        return t if t > 0 else float(cfg.get("timeout") or 5.0)

    @staticmethod
    def _image_size(img_path: Path) -> tuple[int, int]:
        """读取图片宽高（像素）。"""
        try:
            from PIL import Image
            with Image.open(img_path) as im:
                return int(im.width), int(im.height)
        except Exception:  # noqa: BLE001 - PIL 不可用时退回 cv2
            import cv2
            img = cv2.imread(str(img_path))
            if img is None:
                raise RuntimeError(f"图片读取失败: {img_path}")
            h, w = img.shape[:2]
            return int(w), int(h)

    @staticmethod
    def _region_to_pixel_box(region: dict, img_w: int, img_h: int) -> list[int]:
        """归一化检测区域 → 轴对齐像素框 [x1, y1, x2, y2]。

        region.points 是归一化顶点（0~1），取包围盒后乘以图片宽高。
        """
        pts = []
        for p in (region or {}).get("points", []) or []:
            if isinstance(p, dict) and "x" in p and "y" in p:
                pts.append((float(p["x"]), float(p["y"])))
        if not pts:
            return [0, 0, int(img_w), int(img_h)]
        xs = [p[0] for p in pts]
        ys = [p[1] for p in pts]
        x1 = max(0, min(xs)) * img_w
        y1 = max(0, min(ys)) * img_h
        x2 = min(1, max(xs)) * img_w
        y2 = min(1, max(ys)) * img_h
        return [int(x1), int(y1), int(x2), int(y2)]

    # ============================================================ 配置

    def _platform_cfg(self) -> dict:
        """平台/推理服务配置：优先 Context（平台配置节点 on_active 写的），
        没有就现去 `robot.prefab.json` 找节点（手工只跑执行器那棵树时兜底）。

        ⚠️ 与 `platform.py` 的取舍一致：绝不返回一个猜出来的默认地址。
        """
        ctx = self._ctx
        if ctx is not None and ctx.kv.get("platform.upload_url") is not None:
            return {
                "upload_url": str(ctx.kv.get("platform.upload_url") or ""),
                "infer_url": str(ctx.kv.get("platform.infer_url") or ""),
                "auth_header": str(ctx.kv.get("platform.auth_header") or ""),
                "timeout": _safe_float(ctx.kv.get("platform.timeout"), 5.0),
                "retry": int(_safe_float(ctx.kv.get("platform.retry"), 0)),
                "verify_tls": str(ctx.kv.get("platform.verify_tls", "True")) != "False",
            }
        node = self._find_platform_node()
        if node is not None:
            return node.info()
        return {"upload_url": "", "infer_url": "", "auth_header": "",
                "timeout": 5.0, "retry": 0, "verify_tls": True}

    def _fms_host(self) -> str:
        """从 RobotConfig 拿 fmsHost（FMS 的 ip:port）。

        优先从 Context 拿（RobotConfig.on_active 写的），
        没有就现去 `robot.prefab.json` 找 RobotConfig 节点。
        """
        ctx = self._ctx
        if ctx is not None:
            host = str(ctx.kv.get("robot.fms_host") or "").strip()
            if host:
                return host
        # 兜底：从 prefab 文件里找
        node = self._find_robot_config_node()
        if node is not None:
            return str(getattr(node, "fms_host", "") or "").strip()
        return ""

    @staticmethod
    def _find_platform_node():
        """从 `robot.prefab.json` 里找 `PlatformConfigNode`（DFS）。"""
        from ...config import PREFAB_DIR
        from ..registry import build

        path = Path(PREFAB_DIR) / "robot.prefab.json"
        if not path.is_file():
            return None
        try:
            spec = json.loads(path.read_text(encoding="utf-8"))
            root = build(spec.get("root") or {})
        except Exception:
            logger.exception("[prefab] 读取 robot.prefab.json 失败")
            return None
        stack = [root]
        while stack:
            node = stack.pop(0)
            if getattr(node, "type", "") == "PlatformConfig":
                return node
            stack.extend(getattr(node, "child_nodes", None) or [])
        return None

    @staticmethod
    def _find_robot_config_node():
        """从 `robot.prefab.json` 里找 `RobotConfig` 节点（DFS）。"""
        from ...config import PREFAB_DIR
        from ..registry import build

        path = Path(PREFAB_DIR) / "robot.prefab.json"
        if not path.is_file():
            return None
        try:
            spec = json.loads(path.read_text(encoding="utf-8"))
            root = build(spec.get("root") or {})
        except Exception:
            logger.exception("[prefab] 读取 robot.prefab.json 失败")
            return None
        stack = [root]
        while stack:
            node = stack.pop(0)
            if getattr(node, "type", "") == "RobotConfig":
                return node
            stack.extend(getattr(node, "child_nodes", None) or [])
        return None

    def _extra_fields(self, pa: PendingAction) -> dict:
        """平台上报时可带的业务字段（测温/环境/局放），从动作行现取。

        目前巡检的视觉链只产出图片与测温占位，这几项多为空；留着是因为
        cmd=104 的载荷里本来就有它们，缺了平台侧可能解析报错。
        """
        return {}

    # ============================================================ 回写

    def _save_infer_trace(self, pa: PendingAction, *, request=None,
                          response=None, result=None) -> None:
        """记录推理请求参数 / 同步响应 / 回调结果到动作行（只更新给了的字段）。

        三个字段独立写：提交时写 request/response，算法回调时只写 result，
        互不覆盖；dry_run 不落库。
        """
        if self.dry_run:
            return
        from ...database import SessionLocal
        from ...models import InspectionActionResult

        db = SessionLocal()
        try:
            row = db.query(InspectionActionResult).filter(
                InspectionActionResult.id == pa.action_result_id).first()
            if row is None:
                return
            if request is not None:
                row.infer_request_json = request
            if response is not None:
                row.infer_response_json = response
            if result is not None:
                row.infer_result_json = result
            db.commit()
        except Exception:
            db.rollback()
            logger.exception("[prefab] %s: 记录推理留痕失败（%s）",
                             self.name or self.type, pa.key)
        finally:
            db.close()

    def _mark(self, pa: PendingAction, status: str, *, mode: str, error: str,
              points: Optional[list[PointResult]] = None) -> None:
        """回写分发状态（成功置 done，失败 +1 次并留原因）。

        ⚠️ **不回写 `status`**：那是"动作执行结果"（rail 侧写的），这里是"分发
        结果"。两件事分开记才不会互相覆盖（一条上传失败的动作照样是执行成功的）。
        """
        if self.dry_run:
            return
        from ...database import SessionLocal
        from ...models import InspectionActionResult, InspectionPointResult

        db = SessionLocal()
        try:
            row = db.query(InspectionActionResult).filter(
                InspectionActionResult.id == pa.action_result_id).first()
            if row is None:
                logger.warning("[prefab] %s: 动作结果行 %s 已不存在，跳过回写",
                               self.name or self.type, pa.action_result_id)
                return
            row.dispatch_status = status
            row.dispatch_mode = mode
            row.dispatch_attempts = int(row.dispatch_attempts or 0) + 1
            row.dispatch_error = str(error or "")[:500]
            if status == DISPATCH_DONE:
                row.dispatched_at = datetime.utcnow()
            if points:
                self._write_points(db, row, points)
            db.commit()
        except Exception:
            db.rollback()
            logger.exception("[prefab] %s: 回写分发状态失败（%s）",
                             self.name or self.type, pa.key)
        finally:
            db.close()

    def _write_points(self, db: Any, row: Any, points: list[PointResult]) -> None:
        """按 `(action_result_id, point_id)` **更新**测点行（不新插，保证幂等）。

        没有对应占位行时**补插一行**：老任务（占位机制之前）没有测点行，
        但检测结果是真的算出来了，丢掉它比多一行更糟。
        """
        from ...models import InspectionPointResult

        existing = {
            str(p.point_id or ""): p
            for p in db.query(InspectionPointResult).filter(
                InspectionPointResult.action_result_id == row.id).all()
        }
        for i, res in enumerate(points):
            if not res.point_id:
                # 检测框没绑测点：结果无处归属，但仍要让人看得见
                logger.warning("[prefab] %s: 检测结果无测点可写（流程 %s，label=%s）",
                               self.name or self.type, res.detect_flow, res.label)
                continue
            target = existing.get(res.point_id)
            if target is None:
                target = InspectionPointResult(
                    action_result_id=row.id, run_id=row.run_id,
                    robot_pk=row.robot_pk, inspection_id=row.inspection_id,
                    floor=row.floor, waypoint_id=row.waypoint_id,
                    action_id=row.action_id, point_id=res.point_id, seq=res.seq or i,
                )
                db.add(target)
                existing[res.point_id] = target
            target.kind = "detect"
            target.status = res.status
            target.detect_flow = res.detect_flow
            target.algorithm = res.algorithm
            target.label = res.label
            target.confidence = res.confidence
            target.passed = res.passed
            target.boxes_json = res.boxes or None
            target.detect_json = res.detect or None
            if res.value is not None:
                target.value = float(res.value)
            if res.unit:
                target.unit = res.unit

    # ============================================================ 状态展示

    def status(self) -> dict[str, Any]:
        """给运维看的一小份状态（日志 / 后续接口用）。"""
        return {
            "node": self.name or self.type,
            "running": bool(self._thread and self._thread.is_alive()),
            "poll_interval": self.poll_interval,
            "batch_size": self.batch_size,
            "dry_run": self.dry_run,
            "max_attempts": self.max_attempts,
            "flows": sorted(self._flows.keys()),
            "stats": dict(self._stats),
        }


def _safe_float(v: Any, default: float) -> float:
    try:
        return float(v)
    except (TypeError, ValueError):
        return default
