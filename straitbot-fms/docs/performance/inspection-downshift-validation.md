# 巡检计划与航点绑定下沉验证（2026-09-18）

## 结果
- ARM64 / Python 3.11 镜像全量 pytest：213 passed、17 subtests passed、4 warnings，18.36 秒。
- 新增计划测试覆盖时区/DST、单次/每日/每周、无效排期、乐观版本、重复名称、引用保护、权限与机器人隔离、快照、重复执行、忙碌/离线/超时、重启认领、错机器人上报和迟到消息。
- 绑定 API 测试覆盖机器人过滤、完整批次校验与回滚、重复/错误目标和字符串测点 ID。
- 前端 Node 20 镜像 `npm run build`：TypeScript 与 Vite 通过。既有大包体积与 calibration 混合导入告警仍存在。
- 首轮全量测试缺少 FSM 文件夹夹具导致两项 FileNotFoundError；补挂仓库 backend/data/fsm 后通过。未修改这些既有测试。

## 浏览器与调度验证
在独立预览容器、独立 SQLite/JSON、两台 localhost 虚拟机器人和 mock robot_api 中完成：
1. 未选机器人提示、机器人航点列表、选择两个真实测试测点并批量绑定。
2. 计划创建读取上述绑定、保存手动计划、确认执行后显示 accepted、核对模拟状态后显示 done。
3. 编辑为每日排期，日历显示对应日期 09:00 任务。
4. 切到第二台机器人后，第一台计划不出现，航点列表变为第二台航点。
5. 重建预览容器并挂载保存的数据，计划、两个绑定及机器人隔离仍成立。
6. 新建到下一分钟执行的单次计划，由实际 APScheduler 后台扫描触发，历史恰好一条 accepted；无真实设备请求。

## 现场发布
- 地址：192.168.6.88:8900；前后端镜像均为 `inspection-downshift-20260918` 标签。
- 后端沿用已验证 catalog-v2 镜像依赖，仅更新 /app/app；没有升级依赖。
- 备份：`/home/hxzh/fms-backups/20260918-inspection-downshift/deployment-before.tar.gz`。
- 备份 SHA256：`5bacc93e9d9db8f83bbd3b8bfe48a11ffc2ebd1f17b7bb5f5e6d53dded16a6e4`。
- 发布前后档案 revision=6、300 点；JSON SHA256 均为 `794b4e7ebad009240114d41aabec6ac4b80fa070a102bf8c29e76a7c1ab60e88`。
- 发布后保留 1 台机器人、2 个账号；新计划和执行表均为空。后端 healthy，计划列表和机器人范围的航点选项接口返回真实空列表。
- 浏览器确认 .88 的两个页面已切换为真实接口，顶部机器人选择有效。现场本地地图、航点、动作尚未配置，因此不能创建可执行计划；没有创建模拟数据到现场库，也没有下发真实巡检。

## 回退
停止新后端调度器后，使用备份目录的 `docker-compose.release.before.yml` 恢复镜像配置并启动旧服务。旧后端忽略新增表；如需恢复整个数据集，先备份发布后的数据，再在停服状态恢复 deployment-before.tar.gz。不要覆盖发布后的业务修改。
