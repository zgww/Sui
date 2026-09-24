# 项目文档 (docs/)

本目录存放项目文档, 供开发/运维/沟通使用。

## 文档清单

| 文档 | 用途 | 受众 |
|---|---|---|
| [ARCHITECTURE.md](../ARCHITECTURE.md) | 系统架构(物模型/数据库/模块/数据流/部署模式) | 开发 |
| [MENU_SPEC.md](./MENU_SPEC.md) | 菜单规格(结构/属性/角色/模式/变更沟通方式) | 沟通 |
| [CHANGELOG.md](../CHANGELOG.md) | 版本变更记录 | 所有人 |
| [README.md](../README.md) | 部署/使用说明 | 运维/用户 |

## 文档约定

### 文件命名
- 大写 + 下划线: `MENU_SPEC.md`, `THING_MODEL.md`
- 中文标题 + 英文文件名

### 更新规则
- 每次架构/功能变更, 同步更新对应文档
- 打包发版前确认文档与代码一致
- 重大变更记录到 CHANGELOG.md

## 如何沟通需求

### 改菜单
→ 参照 [MENU_SPEC.md](./MENU_SPEC.md) 的"如何沟通菜单变更"

### 改架构
→ 参照 [ARCHITECTURE.md](../ARCHITECTURE.md) 的模块划分和数据流

### 改机器人交互
→ 参照 [THING_MODEL.md](./THING_MODEL.md) 的物模型定义

### 加新功能
→ 说明:
  1. 功能名称和目标
  2. 属于哪个模块(监控/控制/巡检/系统管理)
  3. 调用哪些机器人 API(cmd 号)
  4. 菜单放在哪里(参照 MENU_SPEC.md)
  5. 角色权限(engineer / 所有)
