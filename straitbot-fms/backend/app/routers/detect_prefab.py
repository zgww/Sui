"""检测流程编排 API：基于 prefab 机制的纯数据检测逻辑树。

与航点树（`/api/waypoint-prefab`）、计划树（`/api/plan-prefab`）是**三棵
独立的树**，同一套机制、同一套接口形状（目录/文件 CRUD + 树读写 + node-types），
由 `prefab_store.make_prefab_router` 生成，只是换了根目录与类型过滤：

- 根目录固定为 `data/prefabs/检测算法`（可嵌套目录、多个 *.prefab.json）；
- 节点类型仅暴露检测系（`DetectNodeBase` 子类：取帧 / 节流 / 抽帧 / 区域过滤 /
  生效时段 / 图像预处理 / 算法检测 / 结果过滤 / 连续确认 / 抓拍留存 / 告警 /
  转发 / 短信 / 邮件），**不会**混进航点系或计划系的类型——三棵树的类型目录
  必须分开，否则"添加子节点"里选中一个航点节点，就会在这棵树里存出一个
  本树读不懂的脏节点；
- 同样只做文件读写与 `registry.build` 校验，不激活、不进规则 runtime。

**一个文件 = 一条检测逻辑**（如"人员入侵"）：从取帧、前处理，到算法本身，
再到后处理（告警 / 转发 / 短信 / 邮件）都在这一棵树里排出来。节点定义见
`app/prefab/nodes/detect.py`。

⚠️ **本接口目前只负责"编排数据"**：把检测流程存下来、读回来、校验结构。
真正按这棵树跑检测（取帧 -> 前处理 -> 算法 -> 后处理）尚未对接执行侧，
见 `prefab/nodes/detect.py` 的模块 docstring。
"""
import json
from typing import Any

from fastapi import Depends

from ..auth import get_current_user
from ..config import DATA_DIR, DETECT_PREFAB_DIR
from .prefab_store import make_prefab_router
from .waypoint_prefab import read_algorithms

PANEL_LIST_FILE = DATA_DIR / "panel_list.json"


def read_panel_list() -> dict[str, Any]:
    """读一次 `data/panel_list.json`（算法推理服务可选算法清单，不做缓存）。

    每项 `{id, name, display_name}`：`name` 是算法服务 boxs[].name 编码
    （如 1_0_0_1_53_0），`id` 是算法模板编号，`display_name` 是中文名。
    文件缺失/损坏不抛异常（避免检视器打不开），返回空列表 + warning。
    """
    if not PANEL_LIST_FILE.is_file():
        return {"ok": False, "panels": [], "warning": f"缺少 {PANEL_LIST_FILE}"}
    try:
        raw = json.loads(PANEL_LIST_FILE.read_text(encoding="utf-8"))
    except Exception as exc:  # noqa: BLE001 - json 损坏不该让接口 500
        return {"ok": False, "panels": [], "warning": f"解析失败: {exc}"}
    out = []
    for item in raw or []:
        if not isinstance(item, dict):
            continue
        name = str(item.get("name") or "").strip()
        if not name:
            continue  # name 是构建 box.name 的键，缺了没法用
        out.append({
            "id": item.get("id"),
            "name": name,
            "display_name": str(item.get("display_name") or name),
        })
    return {"ok": True, "panels": out}


def _detect_root(name: str) -> dict[str, Any]:
    """新建检测流程文件时的初始 spec：一个**空流程**当根。

    根用 `DetectPipelineNode` 而不是分组：一条检测逻辑有自己的对外身份
    （检测编号、适用场景），这些不属于任何一个处理步骤，而分组是纯容器——
    根是分组的话"这条流程叫什么、用在哪"就没地方写。

    内容一律留空：前处理要不要节流、要不要连续确认、命中后发不发短信，
    是现场按测点配的事，不替用户猜。
    """
    return {
        "name": name,
        "description": "",
        "root": {
            "type": "DetectPipelineNode",
            "properties": {"name": name, "enabled": True, "description": ""},
            "children": [],
        },
    }


router = make_prefab_router(
    prefix="/api/detect-prefab",
    tag="detect-prefab",
    root_dir=DETECT_PREFAB_DIR,
    base_filter="DetectNodeBase",
    root_spec_factory=_detect_root,
)


@router.get("/algorithms", dependencies=[Depends(get_current_user)])
def get_algorithms():
    """算法目录（`data/algorithms.json`），给「算法检测」节点的下拉用。

    与 `/api/waypoint-prefab/algorithms` **同一份数据**（`read_algorithms`）：
    算法目录是全局的，检测框能选的算法跟检测流程里能选的必须是同一批，
    否则同一个算法在两棵树里会选出不一样的 id。
    """
    return read_algorithms()


@router.get("/panel-list", dependencies=[Depends(get_current_user)])
def get_panel_list():
    """算法推理服务可选算法清单（`data/panel_list.json`）。

    给检测算法编排里的「MeterAlgorithmNode」算法类型下拉用：该节点用于兼容
    现有算法推理服务，从这份清单里选择具体算法（存 name 编码）。
    """
    return read_panel_list()
