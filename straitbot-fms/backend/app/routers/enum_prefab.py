"""枚举配置编排 API：基于 prefab 机制的纯数据枚举树。

与航点树（`/api/waypoint-prefab`）、计划树（`/api/plan-prefab`）、检测流程
（`/api/detect-prefab`）是**四棵独立的树**，同一套机制、同一套接口形状
（目录/文件 CRUD + 树读写 + node-types），由 `prefab_store.make_prefab_router`
生成，只是换了根目录与类型过滤：

- 根目录固定为 `data/prefabs/枚举`（可嵌套目录、多个 *.prefab.json）；
- 节点类型仅暴露枚举系（`EnumNodeBase` 子类：`EnumNode` / `EnumItemNode`），
  **不会**混进其它三棵树的类型——类型目录必须分开，否则"添加子节点"里选中
  一个航点节点，就会在这棵树里存出一个本树读不懂的脏节点；
- 同样只做文件读写与 `registry.build` 校验，不激活、不进规则 runtime。

**一个文件 = 一份枚举配置**，根固定是 `EnumNode`（一个 key）下面挂若干
`EnumItemNode`（选项）。告警中心的「类型」筛选下拉就取名为 `告警类型` 的那份
枚举。节点定义见 `app/prefab/nodes/enum.py`。

## 与另外三棵树的差别：多了一个 `/options`

另外三棵树的产物只有"文件"，消费方（执行侧）自己按文件名去读。枚举多一个
`/options?key=告警类型` 是因为它的消费方是**页面上的下拉框**：告警中心不该
知道枚举存在哪个文件、节点挂在第几层，它只要"告警类型有哪些选项"。翻译层在
`prefab/enum_catalog.py`（纯函数、可单测），本路由只做鉴权与参数转发。
"""
from typing import Any

from fastapi import Depends, Query

from ..auth import get_current_user
from ..config import ENUM_PREFAB_DIR
from ..prefab.enum_catalog import list_enum_keys, read_enum_options
from .prefab_store import make_prefab_router


def _enum_root(name: str) -> dict[str, Any]:
    """新建枚举文件时的初始 spec：一个**空枚举**当根。

    根就是 `EnumNode` 本身（不再包一层分组）——一份配置对应一个 key，多一层
    容器只会让"这份配置的键叫什么"有两个地方可写。

    `name` 与 `label` 都预填成文件名：新建时最常见的意图就是"文件名即枚举名"，
    预填了用户通常不用改，也就不会出现"配好了选项却因为没填 name 而取不到"
    这种最难排查的情况（取不到时 `enum_catalog` 会退回文件名，两者一致）。
    选项一律留空——有哪些值该由现场按实际业务填，不替用户猜。
    """
    return {
        "name": name,
        "description": "",
        "root": {
            "type": "EnumNode",
            "properties": {"name": name, "label": name, "enabled": True,
                           "description": ""},
            "children": [],
        },
    }


router = make_prefab_router(
    prefix="/api/enum-prefab",
    tag="enum-prefab",
    root_dir=ENUM_PREFAB_DIR,
    base_filter="EnumNodeBase",
    root_spec_factory=_enum_root,
)


@router.get("/options", dependencies=[Depends(get_current_user)])
def get_options(key: str = Query("", description="枚举键，如 告警类型")):
    """取一份枚举的选项（下拉框用）。

    返回 `{ok, key, found, options, sources}`：

    - `options` = `[{value, label, description}]`，**已排好序、已去重**，
      `value` 是存进数据库的值（`alarm_type`），`label` 是显示名；
    - `found` = 目录里**有没有**这个 key 的 `EnumNode`。⚠️ 与 `options`
      非空是两件事：配了但一项都没填时 `found=True` 而 `options=[]`，
      消费方据此区分"没配过"（可回落到库里实际出现过的值）与"配了但为空"
      （就该是空的）；
    - 目录缺失 / 文件损坏**不报错**，返回 `found=False` + 空选项——下拉框
      是筛选区的装饰性控件，不该让整个页面 500。
    """
    return read_enum_options(key)


@router.get("/keys", dependencies=[Depends(get_current_user)])
def get_keys():
    """目录里全部枚举的键（有哪些枚举可引用）。

    给"选一个枚举"的场合用（调试、后续把更多下拉框接到枚举上时挑 key），
    顺带带上每份枚举的选项条数，一眼能看出哪份是空壳。
    """
    return list_enum_keys()
