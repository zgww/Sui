# 多地图巡检验证记录 — 2026-09-18

## 自动化验证

- Python 3.11 发布镜像：`python -m pytest tests -q --disable-warnings`，**220 passed，17 subtests passed，4 warnings**。测试挂载独立测试目录和 FSM fixtures，没有使用正式数据卷。
- 新增 `test_inspection_multimap.py`：有效楼层继承/覆盖、跨地图和跨机器人范围、分段内重复外部 ID 检查、后续地图删除保护、快照不可变、重复继续、超时不重发、跨段 HTTP 上报/权限和旧版 NULL stages 往返。
- 前端 Node 20 Docker 构建：`tsc -b && vite build` 成功，最终镜像 `straitbot-fms-frontend:multimap-20260918`。
- `git diff --check` 通过；未提交生成缓存、凭据或现场数据。

## 浏览器与 Demo

地址：`http://192.168.6.88:8912/sink/inspection-plan`，选择“【DEMO】跨楼层巡检机器人”。

- 三张地图：配电楼、主控楼、地下设备间；四段：配电楼 1F/2F、主控楼 1F、地下 B1。
- 96 个测点、24 个航点、48 个动作；三个示例计划。另有一个空数据机器人用于范围隔离。
- 实际操作验证：路线列表、编辑器布局、取消单点勾选后翻页、切换楼层保留选择、上移分段保留测点、确认下一段、执行历史和定时日历。
- 执行 `fms-24de5d7d504b4b67a5fa25828820810e` 完成全部四段，历史显示 `done / 第 4 段`。
- 首段完成后重启 Demo 后端，仍停留在 `waiting_transition`，未自动推进。后续重复确认未重复推进；最后一段完成释放占用。
- Demo 仅通过专用入口模拟 `robot_api.call`；未下发任何真实设备命令。每日/每周示例在验证中已启用，可在日历查看。

## 发布验证

- 正式地址：`http://192.168.6.88:8900/sink/inspection-plan`，前后端均为 `multimap-20260918` 镜像，后端 healthy。
- 登录、计划列表、地图楼层选项 API 和页面均返回 200。
- 发布前停后端完成一致性备份：`/home/hxzh/fms-backups/20260918-multimap/deployment-before.tar.gz`。
- 备份 SHA-256：`bef52ae70bcf179a9213f10c4c8ecae1733b060aad5c791b354746cda199e4a0`。
- 正式测点档案发布前后 SHA-256 相同。Demo 使用独立容器、网络和数据目录，未向正式档案写入演示测点。

## 验证边界

已验证 FMS 编排、模拟指令和浏览器交互；未验证真实机器人自动乘梯、换图或跨层导航。跨段需要人工确认到达及定位，不能将 Demo 通过表述为现场联调完成。
