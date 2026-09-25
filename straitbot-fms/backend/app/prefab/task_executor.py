"""任务执行器的执行逻辑（**尽量纯函数**：吃一批待处理的动作数据，吐"每条该怎么办"）。

与 `plan_scheduler.py` / `detect_pipeline.py` 同一个套路：**算的东西必须能单测**。
节点（`nodes/task_executor.py`）只管线程、轮询、调 HTTP；本模块回答
"这条动作数据该走哪条路、要发给谁、检测结果怎么写回去"。

## 数据从哪来、到哪去

```
rail 状态机执行动作  →  recorder 占位/回填  →  inspection_action_results
                                                      │  status='ok' 且未分发
                                                      ▼
                                              任务执行器（本模块）
                                        ┌─────────────┴─────────────┐
                                  detect_type=platform        detect_type=fms
                                        │                          │
                                   HTTP POST 平台            跑检测框引用的流程
                                        │                          │
                                        └────────────→ 结果回写 inspection_point_results
```

## 为什么要"未分发"这个标记

`status='ok'` 只说明**动作执行完了**，不说明**数据送出去了**。执行器可能：
上传失败、检测流程报错、或者程序正好在这一刻重启。所以回写时要区分
"执行完成"与"分发完成"两件事，否则一条上传失败的数据下一轮就再也不会被
重试（`status` 已经 ok 了，看着像处理完了）。

标记落在 `InspectionActionResult.dispatch_status` 上（见 `models/inspection.py`）：
`pending` → 待分发；`done` → 已分发（上传成功 / 检测结果已写回）；
`failed` → 分发失败（可重试，`dispatch_attempts` 记次数）。

## 幂等

同一批数据被处理两次不能产生两条上传/两份检测结果。靠三点：
1. 只有 `dispatch_status='pending'` 的才进候选；
2. 处理成功立刻置 `done`（同一事务里），下一轮扫不到；
3. 检测结果写测点是**按 (action_result_id, point_id) 更新**，不是盲目插入。

## fms 分支：算法推理在**外部 HTTP 服务**里

⚠️ 这一条容易搞错：本系统**不跑模型**。`DetectorNode`（每种算法一个子类）
描述的是"用哪个算法、配了什么参数"，`DetectPipelineNode` 描述的是一条检测管线
（取帧 / 节流 / 区域过滤 / 连续确认 / 告警 / 短信…）。真正算的那一步是一次
HTTP POST 到一个独立的**推理服务**（地址配在平台配置节点同一处的
`infer_url`；`infer_payload` / `infer_result` 负责请求与响应的形状适配）。

于是 fms 分支的流程是：

```
取检测框引用的流程 → 取该框绑定的测点 + 归一化区域
   → HTTP POST 推理服务（image + algorithm + region）
   → infer_result() 归一化响应 → DetectEvent
   → detect_pipeline.run_flow(流程树, event)   # 纯函数，算"要不要报"
   → 结果写回 inspection_point_results
```

流程树本身**不发短信、不推 HTTP**（`run_flow` 只吐 `actions` dict）——外发是
后一步的事，本期只把 `actions` 记进 `detect_json` 供查证，不动短信/邮件网关。
"""
from __future__ import annotations

import logging
from dataclasses import dataclass, field
from typing import Any, Optional

logger = logging.getLogger("prefab.task_executor")

# ---------------------------------------------------------------- 常量

#: 动作结果的分发状态（与 models/inspection.py 的列约定一致）
DISPATCH_PENDING = "pending"
DISPATCH_DONE = "done"
DISPATCH_FAILED = "failed"

#: 检测类型：FMS 本地消化 / 上传平台。**与 rail 侧的 DETECT_TYPE_* 同一套值**，
#: 这里不 import rail 的常量是为了让本模块保持"不依赖 rail 包"（可独立单测）。
DETECT_FMS = "fms"
DETECT_PLATFORM = "platform"

#: 设备协议口径的动作类型：1 拍照 / 2 测温 / 3 录像。
#: 只有 1、2 会产生可检测的图像；录像（3）没有图像输入，检测无意义。
ACTION_TYPE_PICTURE = 1
ACTION_TYPE_THERMOMETRY = 2
ACTION_TYPE_VIDEO = 3

#: 平台上传用的默认路径（旧平台 cmd=104 的接收口）。仅用于日志提示，
#: 真正地址一律取自「平台配置」节点——不替用户猜地址。
PLATFORM_RESULT_PATH = "/api/inspection/report/result"


def normalize_detect_type(value: Any) -> str:
    """`detect_type` 归一化：**只有明确写了 `fms` 才本地检测，其余一律 platform**。

    与 `rail/inspection.py` 的 `FloorTask._normalize_detect_type` 同一约定
    （不传 = 兼容旧数据 = 走平台）。空串、None、大小写混写、未知值都回落
    platform 并告警——旧版机器人本来就不做检测，静默改成"FMS 自己跑算法"
    会让老数据突然开始产生检测结论，那比不处理更危险。
    """
    s = str(value or "").strip().lower()
    if s == DETECT_FMS:
        return DETECT_FMS
    if s and s != DETECT_PLATFORM:
        logger.warning("[task-executor] 未知 detect_type=%r，按 %s 处理",
                       value, DETECT_PLATFORM)
    return DETECT_PLATFORM


def is_dispatchable(action_type: Any) -> bool:
    """这类动作有没有"可分发"的数据。

    录像（3）没有图像，检测和上传都没有意义 → 不分发（否则会一直重试，
    每次都以"没有图片"失败，把 `dispatch_attempts` 刷上去）。
    """
    try:
        t = int(action_type or 0)
    except (TypeError, ValueError):
        return False
    return t in (ACTION_TYPE_PICTURE, ACTION_TYPE_THERMOMETRY)


def action_image(row: Any, *, prefer_infrared: Optional[bool] = None) -> str:
    """从动作行里挑**可用于检测的图**。

    测温动作优先红外图（测点框是画在热像画面上的），拍照动作用可见光图。
    都没有就回落到 `local_path`（FMS 执行器落盘的图）——旧数据里
    `picture`/`infrared` 是外部路径、`local_path` 才是本地那张。

    `prefer_infrared` 留空时**由行自己的 `action_type` 决定**（2=测温取红外）：
    默认值比调用方可靠——多一个调用点就多一次"忘了传"的机会，而漏传的后果是
    "测温流程拿可见光图去测点区域找框"，跑得出结论但全是错的。
    """
    def _s(v: Any) -> str:
        return str(v or "").strip()

    if prefer_infrared is None:
        try:
            prefer_infrared = int(getattr(row, "action_type", 0) or 0) == ACTION_TYPE_THERMOMETRY
        except (TypeError, ValueError):
            prefer_infrared = False

    if prefer_infrared:
        for v in (_s(getattr(row, "infrared", "")), _s(getattr(row, "picture", "")),
                  _s(getattr(row, "local_path", ""))):
            if v:
                return v
        return ""
    for v in (_s(getattr(row, "picture", "")), _s(getattr(row, "local_path", "")),
              _s(getattr(row, "infrared", ""))):
        if v:
            return v
    return ""


# ---------------------------------------------------------------- 待处理动作

@dataclass
class PendingAction:
    """一条待分发的动作数据（从 `inspection_action_results` 摘出来的最小集）。

    刻意**不带 ORM 行对象**：本模块的纯函数只吃这个 dataclass，测试不用起数据库，
    也避免"顺手改了一下行"这种跨层副作用。
    """

    action_result_id: int
    inspection_id: str = ""
    floor: int = 0
    waypoint_id: str = ""
    action_id: str = ""
    action_type: int = 0
    detect_type: str = DETECT_PLATFORM
    picture: str = ""
    infrared: str = ""
    local_path: str = ""
    reference_image: str = ""
    inplace_ts: str = ""
    #: 已分发尝试次数（决定这一轮还值不值得现试；见 `should_retry`）
    dispatch_attempts: int = 0
    robot_pk: Optional[int] = None

    @property
    def key(self) -> str:
        """日志/去重用的短标识。"""
        return f"{self.inspection_id}/{self.floor}/{self.waypoint_id}/{self.action_id}"

    @property
    def image(self) -> str:
        """按动作类型选图（测温取红外）。"""
        return action_image(self)


def to_pending(row: Any) -> PendingAction:
    """ORM 行 → `PendingAction`（容忍缺列，便于测试用轻量假行）。"""
    def _s(v: Any) -> str:
        return str(v or "")

    return PendingAction(
        action_result_id=int(getattr(row, "id", 0) or 0),
        inspection_id=_s(getattr(row, "inspection_id", "")),
        floor=int(getattr(row, "floor", 0) or 0),
        waypoint_id=_s(getattr(row, "waypoint_id", "")),
        action_id=_s(getattr(row, "action_id", "")),
        action_type=int(getattr(row, "action_type", 0) or 0),
        detect_type=normalize_detect_type(getattr(row, "detect_type", "")),
        picture=_s(getattr(row, "picture", "")),
        infrared=_s(getattr(row, "infrared", "")),
        local_path=_s(getattr(row, "local_path", "")),
        reference_image=_s(getattr(row, "reference_image", "")),
        inplace_ts=_s(getattr(row, "inplace_ts", "")),
        dispatch_attempts=int(getattr(row, "dispatch_attempts", 0) or 0),
        robot_pk=getattr(row, "robot_pk", None),
    )


def should_retry(pa: PendingAction, max_attempts: int) -> bool:
    """还值不值得再试。

    `max_attempts<=0` 表示不限次数（由节点上的「重试次数」控制）。
    超限的数据**保持 failed 不动**（不改成 done）：它是"还没送出去"而不是
    "处理完了"，改 done 会让它永远消失，现场就再也查不到这条数据去哪了。
    """
    if max_attempts <= 0:
        return True
    return pa.dispatch_attempts < max_attempts


# ---------------------------------------------------------------- 分流决策

@dataclass
class DispatchPlan:
    """一条动作数据该怎么处理。"""

    pending: PendingAction
    mode: str                      # "upload" | "detect" | "skip"
    reason: str = ""               # skip 的原因（给人看）
    #: detect 模式：要跑的检测流程引用 id（来自检测框的 detect_flow）
    flows: list[str] = field(default_factory=list)
    #: detect 模式：要检测的原图（空字符串表示这条数据没有图）
    image: str = ""


def plan_dispatch(pa: PendingAction, *, flows: Optional[list[str]] = None,
                  max_attempts: int = 0) -> DispatchPlan:
    """决定一条动作数据走哪条路。

    :param flows: 该动作下检测框引用的流程 id 列表（调用方查航点树得到）。
                  fms 模式下为空 = 没配检测框 → skip（不是错误，只是没活干）
    :param max_attempts: 重试上限；超过则 skip
    """
    if not is_dispatchable(pa.action_type):
        return DispatchPlan(pa, "skip", f"动作类型 {pa.action_type} 无图像数据")

    if not should_retry(pa, max_attempts):
        return DispatchPlan(pa, "skip",
                            f"已重试 {pa.dispatch_attempts} 次达上限")

    if pa.detect_type == DETECT_FMS:
        img = pa.image
        if not img:
            return DispatchPlan(pa, "skip", "没有可检测的图片")
        fs = [f for f in (flows or []) if str(f).strip()]
        if not fs:
            return DispatchPlan(pa, "skip", "动作上没有引用检测流程的检测框")
        return DispatchPlan(pa, "detect", flows=fs, image=img)

    # platform：原样上传，不要求有图（图路径可能就是平台自己用的）
    return DispatchPlan(pa, "upload")


def group_plans(plans: list[DispatchPlan]) -> dict[str, list[DispatchPlan]]:
    """按 mode 分组，方便节点一次上传/一次检测（也便于日志汇总）。"""
    out: dict[str, list[DispatchPlan]] = {}
    for p in plans:
        out.setdefault(p.mode, []).append(p)
    return out


# ---------------------------------------------------------------- 上报载荷

def upload_payload(pa: PendingAction, *, extra: Optional[dict] = None) -> dict:
    """构造给平台的上报体（**与旧平台 cmd=104 的 `/report/result` 同形状**）。

    形状必须跟旧平台对得上，否则老平台收到会解析失败——字段名沿用 cmd=104 那一套
    （`inspection_id` / `floor` / `results[]` + `code`/`waypoint_id`/`action_id`/
    `picture`/`infrared`/`media`/`inplace_timestamp`）。

    `detect_type` / `local_path` 这类 **FMS 内部字段不放进去**：
    它们是本系统自己的账本信息，平台不认，与下发真机前裁掉 `detectType`
    是同一个理由（见 `services/inspection_protocol.py`）。
    """
    item: dict[str, Any] = {
        "code": 0,
        "waypoint_id": pa.waypoint_id,
        "action_id": pa.action_id,
        "picture": pa.picture,
        "infrared": pa.infrared,
        "media": "",
        "inplace_timestamp": pa.inplace_ts,
    }
    if extra:
        # 只补平台认得的业务字段；内部账本字段由 extra 里显式挑，不整体合并
        for k in ("thermometry_points", "env", "pdd_data"):
            if extra.get(k) is not None:
                item[k] = extra[k]
    return {
        "inspection_id": pa.inspection_id,
        "floor": pa.floor,
        "results": [item],
    }


def upload_header(auth_header: str) -> dict:
    """把「鉴权头」那一行解析成 HTTP 头字典。

    用一整行文本（而不是"键/值"两个字段）是为了能写非标头；
    多个头用 `;` 分隔。解析不出 `名字: 值` 形式的整段忽略并告警——
    与其发一个坏头出去让平台返回 401，不如不带鉴权发（至少日志里看得见）。
    """
    out: dict[str, str] = {}
    for chunk in str(auth_header or "").split(";"):
        piece = chunk.strip()
        if not piece:
            continue
        if ":" not in piece:
            logger.warning("[task-executor] 鉴权头格式不对（缺冒号），已忽略: %r", piece)
            continue
        name, _, value = piece.partition(":")
        name, value = name.strip(), value.strip()
        if name and value:
            out[name] = value
    return out


# ---------------------------------------------------------------- 检测流程引用

def flow_ref(root: Any, file_stem: str = "") -> str:
    """一条检测流程树根 -> **对外引用 id**。

    优先取流程根的 `detect_id`（检测编号），留空时用文件名（不含 `.prefab.json`）。
    与前端 `utils/detectSelect.ts` 里给下拉用的取值规则**必须一致**：检测框存的
    就是这里算出来的那个串，两边算法不一样就会出现"下拉选中了、执行时却找不到
    流程"——一个只在真跑的时候才暴露的错。

    ⚠️ 与 `nodes/detect.py::DetectPipelineNode.detect_id` 的文档一致：编号可空，
    空则用文件名。
    """
    p = getattr(root, "detect_id", None)
    s = str(p or "").strip()
    if s:
        return s
    stem = str(file_stem or "").strip()
    if stem.endswith(".prefab.json"):
        stem = stem[: -len(".prefab.json")]
    return stem


def index_flows(specs: list[tuple[str, dict]]) -> dict[str, Any]:
    """`[(文件名, spec)]` -> `{引用 id: 流程根节点实例}`。

    真正执行检测要**已 build 的节点实例**（`detect_pipeline.run_flow` 吃实例，
    不是 spec dict）。build 失败的流程**跳过并告警**：一条流程写坏了不该让整个
    执行器起不来（现场还有别的流程要跑），但必须留下日志——静默丢流程的表现是
    "这条检测框永远没结果"，最难查。
    """
    from .registry import build

    out: dict[str, Any] = {}
    for stem, spec in specs:
        root_spec = (spec or {}).get("root") if isinstance(spec, dict) else None
        if not isinstance(root_spec, dict):
            logger.warning("[task-executor] 检测流程 %s 顶层缺少 root 节点，已跳过", stem)
            continue
        try:
            root = build(root_spec)
        except Exception as exc:  # noqa: BLE001 - 单条流程坏了不该拖垮执行器
            logger.warning("[task-executor] 检测流程 %s 构建失败，已跳过: %s", stem, exc)
            continue
        ref = flow_ref(root, stem)
        if not ref:
            logger.warning("[task-executor] 检测流程 %s 既无检测编号也无文件名，已跳过", stem)
            continue
        if ref in out:
            # 重名：后来的不覆盖先来的（下拉里也一样按先到的算），但要告警
            logger.warning("[task-executor] 检测流程引用 id 重复: %r（%s），保留先到的那条",
                           ref, stem)
            continue
        out[ref] = root
    return out


# ---------------------------------------------------------------- 推理请求

def infer_payload(pa: PendingAction, *, flow: str = "", algorithm: str = "",
                  image: str = "", region: Optional[dict] = None,
                  extra: Optional[dict] = None) -> dict:
    """构造发给**外部推理服务**的请求体。

    ⚠️ 算法推理不在本进程里跑——`DetectorNode` 描述的是"用哪个算法、配了什么参数"，
    真正的模型是一套独立的 HTTP 服务（见 `task_executor` 模块 docstring 的分流图）。
    所以这里只负责把"要算什么"说清楚：

    - `image`：图片地址（本地路径或 URL，由推理服务自己决定怎么取）；
    - `algorithm`：算法 id（`data/algorithms.json` 的 id，也是
      `DetectEvent.algorithm` 的取值口径）；
    - `flow`：哪条检测流程触发的（推理服务不解析流程，只记日志/计费好用）；
    - `region`：归一化区域（检测框顶点 + 形状），让推理服务只在框内找——
      **框是"哪块区域"由本系统定，算法只负责在那块里认**；
    - `params`/`threshold`/`labels`：节点上配的算法参数。

    形状刻意做得扁平（不做嵌套包一层 `data`）：推理服务大概率是别人写的，
    字段越少越好对齐。
    """
    out: dict[str, Any] = {
        "image": str(image or ""),
        "algorithm": str(algorithm or ""),
        "flow": str(flow or ""),
        "inspection_id": pa.inspection_id,
        "floor": pa.floor,
        "waypoint_id": pa.waypoint_id,
        "action_id": pa.action_id,
    }
    if region:
        out["region"] = region
    if extra:
        # 只透传推理服务认得的算法参数字段（别把内部账本塞进去）
        for k in ("threshold", "labels", "max_results", "params",
                  "unit", "range_min", "range_max", "decimals",
                  "expected_state", "min_area_ratio", "min_box_ratio"):
            v = extra.get(k)
            if v not in (None, "", [], {}):
                out[k] = v
    return out


def infer_result(raw: Any) -> dict:
    """**外部推理服务的响应** -> 归一化结果。

    刻意**宽容**：推理服务是外部系统，字段名与嵌套深度不受本系统控制。这里认几种
    常见形状，认不出就返回"没检出"而不是抛异常——一次响应格式对不上不该让整条
    动作数据永久失败（`dispatch_status` 一直 failed、每轮重试）。

    认得的形状（按优先级）：
    - `{"detections":[{"label","score","x","y","w","h"}], ...}`
    - `{"results":[{...同上...}]}`
    - `{"label":..., "confidence":..., "box":{...}}`（单结果）
    - 顶层直接就是一个列表

    输出统一为：
    `{ok, label, confidence, passed, boxes, value, raw}`

    - `ok=True`：响应**能当结论用**（哪怕结论是"没检出"）；
    - `ok=False`：响应解析不出任何结论（空响应 / 纯文本 / 形状完全不认识）。
      调用方应把这条测点记 `failed` —— 与"没检出"分开，否则推理服务没接上时
      日志里全是"检测通过"，最难查。
    - `passed=False` + `ok=True`：确实分析了，结论是"画面里没有目标"；
    - `passed=None`：只有 `ok=False` 时出现（未判定）。

    其中 `boxes` 每项 `{x,y,w,h,label,score}`（归一化 0~1）。
    `value` 是量测值（表计读数类算法会给），没有就是 None。
    """
    out: dict[str, Any] = {
        "ok": True, "label": "", "confidence": 0.0,
        "passed": None, "boxes": [], "value": None, "raw": raw,
    }
    if raw is None:
        # 空响应：不是"没检出"，是"没结论"（服务没起来 / 连接被截断）
        return {**out, "ok": False}
    if isinstance(raw, str):
        # 纯文本响应（如 "ok"）：不解析，按"没结论"处理
        return {**out, "ok": False}

    items: list[Any] = []
    recognized = False       # 认出了结果容器（或单结果形状），才敢说"确实分析了"
    if isinstance(raw, list):
        items = raw
        recognized = True
    elif isinstance(raw, dict):
        for key in ("detections", "results", "data", "objects"):
            v = raw.get(key)
            if isinstance(v, list):
                items = v
                recognized = True
                break
        if not recognized:
            # 单结果形状：本层自己就是一条结果（有类别/分数/框才算认得）
            if _one_box(raw) is not None:
                items = [raw]
                recognized = True
        # 顶层统计字段（有的服务会把量测值放在外面）
        if out["value"] is None:
            for key in ("value", "reading", "number", "measure"):
                v = raw.get(key)
                if isinstance(v, (int, float)) and not isinstance(v, bool):
                    out["value"] = float(v)
                    recognized = True
                    break
        for key in ("passed", "ok", "hit"):
            v = raw.get(key)
            if isinstance(v, bool):
                out["passed"] = v
                recognized = True
                break
    else:
        # 既不是对象也不是数组（数字 / 布尔）：形状不认识，记"没结论"
        return {**out, "ok": False}

    if not recognized:
        # 是个 JSON 对象，但里面没有任何本系统认得的字段：形状对不上，
        # 记"没结论"而不是"没检出"——否则推理服务改了字段名之后，日志里
        # 会安静地全是"检测通过"。
        return {**out, "ok": False}

    best: Optional[dict] = None
    for it in items:
        if not isinstance(it, dict):
            continue
        box = _one_box(it)
        if box is None:
            continue
        out["boxes"].append(box)
        if best is None or box["score"] > best["score"]:
            best = box

    if best is not None:
        out["label"] = best["label"]
        out["confidence"] = best["score"]
        if out["value"] is None and best.get("value") is not None:
            out["value"] = best["value"]
        if out["passed"] is None:
            out["passed"] = True        # 检出即"命中"（算法只说有没有）
    elif out["passed"] is None:
        out["passed"] = False           # 一条都没检出：确实分析了，结论是"没有"
    return out


def _one_box(it: dict) -> Optional[dict]:
    """一条检测结果 -> `{x,y,w,h,label,score,value}`；不是框就返回 None。

    坐标兼容 `[x,y,w,h]` 数组与 `{x,y,w,h}` / `{left,top,width,height}` 对象：
    不同推理服务的框表示法就差这点，多认一种能让现场少改一次代码。
    """
    if not isinstance(it, dict):
        return None
    label = str(it.get("label") or it.get("class") or it.get("category") or "").strip()
    score: Optional[float] = None
    for key in ("score", "confidence", "conf", "prob", "probability"):
        v = it.get(key)
        if isinstance(v, (int, float)) and not isinstance(v, bool):
            score = float(v)
            break
    box = it.get("box") if isinstance(it.get("box"), dict) else it
    rect = it.get("bbox") if isinstance(it.get("bbox"), (list, tuple)) else None

    coords: Optional[tuple] = None
    if rect is not None and len(rect) == 4:
        coords = tuple(rect)
    elif isinstance(box, dict):
        if all(k in box for k in ("x", "y", "w", "h")):
            coords = (box["x"], box["y"], box["w"], box["h"])
        elif all(k in box for k in ("left", "top", "width", "height")):
            coords = (box["left"], box["top"], box["width"], box["height"])
    elif isinstance(it.get("box"), (list, tuple)) and len(it["box"]) == 4:
        coords = tuple(it["box"])

    def _f(v: Any) -> float:
        try:
            return float(v)
        except (TypeError, ValueError):
            return 0.0

    out = {
        "label": label,
        "score": 0.0 if score is None else max(0.0, min(1.0, score)),
        "value": None,
    }
    if coords is not None:
        out.update({"x": _f(coords[0]), "y": _f(coords[1]),
                    "w": _f(coords[2]), "h": _f(coords[3])})
    else:
        # 没有框（纯分类算法）也算一条结果：语义上等价于"整图命中"
        out.update({"x": 0.0, "y": 0.0, "w": 1.0, "h": 1.0})
    if score is None and not label:
        return None          # 既无类别也无分数：不是一条有效结果
    for key in ("value", "reading", "number"):
        v = it.get(key)
        if isinstance(v, (int, float)) and not isinstance(v, bool):
            out["value"] = float(v)
            break
    return out


# ---------------------------------------------------------------- 测点回写

@dataclass
class PointResult:
    """一条要写回 `inspection_point_results` 的检测结果。"""

    point_id: str
    seq: int = 0
    status: str = "ok"             # ok / failed
    detect_flow: str = ""
    algorithm: str = ""
    label: str = ""
    confidence: Optional[float] = None
    passed: Optional[bool] = None
    value: Optional[float] = None
    unit: str = ""
    boxes: list[dict] = field(default_factory=list)
    detect: dict = field(default_factory=dict)
    error: str = ""


def apply_flow_result(res: PointResult, run: Any, *, algorithm: str = "") -> PointResult:
    """把一次流程跑的结果（`detect_pipeline.FlowRun`）并进 `PointResult`。

    `passed=False` 是**正常结论**（这次不报），不是失败：状态照样写 ok，
    `passed` 字段带上去（平台/页面靠它区分"检测了但不通过"和"没检测"）。
    只有流程**抛异常**才算 failed。
    """
    if run is None:
        return res
    res.passed = bool(getattr(run, "passed", False))
    notes = list(getattr(run, "notes", []) or [])
    actions = list(getattr(run, "actions", []) or [])
    res.detect = {
        "passed": res.passed,
        "stopped_by": getattr(run, "stopped_by", None),
        "actions": actions,
        "notes": notes,
    }
    if algorithm:
        res.algorithm = algorithm
    return res


def points_for_plan(pa: PendingAction, box_points: dict[str, list[dict]]) -> list[str]:
    """这条动作数据要检测哪几个测点（按 `point_id`）。

    `box_points` 是调用方从航点树算出来的 `{测点 id: [框…]}` 占用表（一个测点
    只能绑一处，见检测框画布的"占用"约定）。**只返回真的有框的测点**：
    在测点档案里挂了测点、但没画框的动作，检测无从谈起。
    """
    return [str(pid) for pid in box_points if str(pid or "").strip()]
