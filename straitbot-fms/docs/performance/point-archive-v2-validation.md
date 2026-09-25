# 自由层级测点档案：测试与部署记录

2026-09-17 21:16（北京时间）已部署到 http://192.168.6.88:8900/sink/point-archive。

## 十轮验证

1. 数据契约：原schema/legacy校验回归，包括类型、重复键、NaN、稳定字符串ID和扩展字段。
2. 自由层级：新增目录测试覆盖2000层长链、循环/自引用/孤儿拒绝、目录ID重复和非法role。
3. 目录与测点维护：新增、移动、重命名、非空目录删除保护、带斜杠ID操作、版本冲突和If-Match。
4. 静态JSON：旧v1导入、v2跨项目往返、预览不落盘、独立revision、禁止运行时关系迁移、Content-Disposition。
5. 平台同步选项：本地自由层级允许保存，校验时报告错误；标准旧层级迁移后通过；platform=true在服务端拒绝不符合层级的导出。
6. 绑定与历史兼容：保留已有绑定、引用点禁止删/导入移除，迁移后任务配置快照隔离、查询筛选不破坏旧数据。
7. 生产构建：ARM64 Docker内tsc -b与vite build通过，已有大包提示不影响构建。发现并修正新增弹窗footer显式undefined导致按钮消失的问题。
8. 浏览器交互：隔离环境实际登录、6目录65测点导入预览和发布、分页第3页、无结果搜索、逐层展开到第6层、增加第7层及其测点、刷新持久化、目录移动保持测点归属，最终构建验证通过。开启导出校验后明确阻断非标准档案。
9. 容量：1万点/10并发/50条页，独立进程loopback TCP。优化后median56.15ms、p9568.49ms、最大76.21ms；冷批次最大168.81ms；重载中位1097.76ms。新增保留Python分配24.33MiB，采样峰值73.40MiB（非总RSS）。样例字段约6.642MiB，鉴权为工程师替身，SQLite绑定表为空；未测外部网络/真实设备。
10. 最终全量回归和发布核验：194 passed +17 subtests，14.38秒，4条既有弃用警告。health及实际登录鉴权的catalog目录/测点/校验/导出接口均200，容器healthy/running，浏览器刷新后显示新版界面。

## 部署与数据

- 镜像straitbot-fms-backend:catalog-v2-20260917（21c814368ac1）、straitbot-fms-frontend:catalog-v2-20260917（c3d0b620c3ab）。VERSION保持2.1.0，通过镜像标签识别本次发布。
- 源码快照/home/hxzh/fms-releases/20260917-catalog-v2；日志tests-final.log、capacity-final.log、frontend-build.log、backend-build-final.log、deploy.log。
- 运行目录/home/hxzh/straitbot-fms；原.env与data挂载保留。原有1机器人、2账号保持；正式档案仍schema1/revision1/0测点，首次新维护才写v2。
- 发布前后正式archive.json SHA256相同：c3f189c2dd9f9614aabae46ee1f3488a788ebe5745cde87dbd5135698455a37f。未注入样例。
- 121个后端源码文件与本地SHA256清单全部一致；详见point-archive-v2-release-manifest.json。
- 停止后端后备份完整部署到/home/hxzh/fms-backups/20260917-catalog-v2/deployment-before.tar.gz，父目录700。SHA256：114112f9f497b3f408e36e672dec6564c85fa7e70f2456ab8c1f5236b6cc2bca。

## 回退和边界

备份目录的docker-compose.rollback.yml指向上一版point-archive-20260917镜像。若尚未写v2可回退镜像；已经写v2时，先备份最新完整data，再配对恢复发布前JSON与SQLite，不能让旧镜像直接加载自由层级档案。运行仍使用docker-compose.yml加docker-compose.release.yml，保持单worker。

平台同步选项目前是格式/层级校验与文件导出，没有向管理平台上传或真实设备联调。导出按钮已触发静态文件生成，内置浏览器未提供Blob下载事件，因此不宣称已核验用户下载目录落盘；导出HTTP内容和跨项目往返由API测试验证。

旧Java/Vue未修改。其他业务下沉页面不在本次范围。Git尚未提交/推送。