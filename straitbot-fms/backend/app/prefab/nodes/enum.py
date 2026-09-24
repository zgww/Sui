"""枚举配置节点（纯数据，不参与规则 runtime 的动作执行）。

一个 `data/prefabs/枚举/*.prefab.json` = **一份枚举配置**（一个文件一份枚举）：

    EnumNode                    枚举（根，一份枚举配置）
      ├ EnumItemNode            枚举项：人员入侵
      ├ EnumItemNode            枚举项：烟火检测
      └ EnumItemNode            枚举项：表计异常

**为什么要做成 prefab 节点而不是在代码里写死一个常量列表**：告警类型、告警
级别、缺陷类别这些"下拉框里有什么"的清单，是**随现场变的业务数据**，不是程序
结构。写死在代码里，现场要加一种类型就得发一次版本；而写死在数据库里又要
为每种枚举建一张表。挂到 prefab 上之后，它跟航点树、计划树、检测流程一样是
可编辑、可导入导出、可版本化的一棵树——加一个选项只是加一个节点。

**为什么不直接用"库里实际出现过的值"（distinct 查询）**：那种做法看起来零
配置，实际上把"应该有哪些类型"和"碰巧报过哪些类型"混为一谈——没报过的类型
在下拉框里根本选不到，而手滑写错的一个类型会永久留在筛选条件里。枚举配置
是**先声明再使用**，下拉框给的是"系统认得的类型"，与库里真有什么无关。

与 `waypoint.py` / `plan.py` / `detect.py` 一样是**第四棵独立的树**：同一套
NodeBase 注册与 schema 机制，中间基类是 `EnumNodeBase`，后端 `node-types`
按基类过滤，四棵树的类型目录互不串门（见 `routers/prefab_store.py`）。

## 字段为什么是 name / label / description 三个

- `name`：**机器键**。写进数据库、写进接口报文，改它等于改数据，所以要短、
  稳定、不含空格（如 `person_intrusion`）。告警的 `alarm_type` 存的就是它。
- `label`：**人看的名**。中文化的展示名（如"人员入侵"），随便改不影响数据。
- `description`：**说明**。给配枚举和用枚举的人看的一句话，说明这一项指什么。

三者分开是老教训：只留一个字段时，要么为了显示好看把中文存进数据库（改个
文案就得刷历史数据），要么为了稳定存一堆英文代号（下拉框里没人看得懂）。

⚠️ **当前只落在编排侧**：这些节点只被读写、校验，以及被
`prefab/enum_catalog.py` 读成下拉选项；不驱动任何执行、不进规则 runtime。
"""
from __future__ import annotations

from typing import ClassVar

from ..base import NodeBase, ui_field


class EnumNodeBase(NodeBase):
    """枚举树节点共同基类（中间类，不注册）。纯数据节点，不实现运行时动作。"""

    __type_name__: ClassVar[str | None] = None


class EnumNode(EnumNodeBase):
    """枚举：**一份枚举配置**（一个文件一份）。

    它是文件的根（`routers/enum_prefab._enum_root`），若干 `EnumItemNode`
    挂在它下面。之所以根节点就是枚举本身、而不是再包一层"枚举分组"：一份
    配置对应一个 key（如"告警类型"），多一层容器只会让"这份配置的键叫什么"
    有两个地方可写，读的时候还要挑一个。

    `name` 是**对外引用这份枚举的键**：告警中心筛选用
    `GET /api/enum-prefab/options?key=告警类型` 取选项，匹配的就是它。
    所以改名 = 改引用，所有用到这个 key 的下拉框会一起换成空选项——
    要改名请连同引用方一起改。
    """

    name: str = ui_field("text", group="枚举", title="枚举键", default="",
                         placeholder="如 告警类型",
                         description="对外引用这份枚举的键（下拉框按它来取选项）；"
                                     "改名会让引用方取不到选项")
    label: str = ui_field("text", group="枚举", title="显示名", default="",
                          placeholder="如 告警类型",
                          description="给人看的中文名，只影响展示，改了不影响数据")
    description: str = ui_field("textarea", group="枚举", title="说明", default="",
                                rows=3,
                                description="这份枚举用来划分什么（给配枚举和用枚举的人看）")


class EnumItemNode(EnumNodeBase):
    """枚举项：枚举里的**一个可选值**（下拉框里的一行）。

    `name` 是**存进数据库的值**——告警的 `alarm_type` 存的就是它，所以它是
    事实上的数据主键：改它等于改历史数据的含义，历史告警会"变成另一种类型"。
    真要改语义请新增一项，别改老项的 name。

    `label` 只影响展示：下拉框里显示它，筛选时提交的仍是 `name`。留空时前端
    回落显示 `name`（空 name 的选项会被读选项的接口跳过——一个没有键的选项
    没法参与筛选，留着只会让下拉框多一条点了没反应的空行）。

    `enabled=False` 的项**不进下拉框**：这是"暂时停用某一项"的口子，比删掉
    安全——删了之后库里已有的老类型在下拉框里就彻底找不到了。
    """

    name: str = ui_field("text", group="枚举项", title="选项值", default="",
                         placeholder="如 person_intrusion",
                         description="存进数据库的值（告警的 alarm_type 就是它）；"
                                     "改它会改变历史数据的含义，要改语义请新增一项")
    label: str = ui_field("text", group="枚举项", title="显示名", default="",
                          placeholder="如 人员入侵",
                          description="下拉框里显示的名字；留空时显示选项值")
    description: str = ui_field("textarea", group="枚举项", title="说明", default="",
                                rows=2,
                                description="这一项指什么（下拉框悬浮提示用）")
