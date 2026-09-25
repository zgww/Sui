# 测点档案部署记录：192.168.6.88

2026-09-17 20:35（北京时间）完成更新。地址：http://192.168.6.88:8900/sink/point-archive。

## 发布版本

- 基于 develop-0824 / 0e2a1d8 的本地测点档案开发结果；尚未提交 Git。
- 源码快照：/home/hxzh/fms-releases/20260917-point-archive-v1。
- 镜像：straitbot-fms-backend:point-archive-20260917（76ef57d79dbe），straitbot-fms-frontend:point-archive-20260917（1d0e9cb6b12e）。
- 应用 VERSION 仍为2.1.0，用上述镜像标签和 docs/performance/point-archive-release-manifest.json 区分版本。
- 继续使用 /home/hxzh/straitbot-fms/backend/.env 和 /home/hxzh/straitbot-fms/data。
- 基础档案：data/point_archive/archive.json；绑定和任务引用：原 data/fms.db。

## 验证

十轮测试详见 performance/point-archive-api-validation.md。最终后端177 tests +17 subtests通过；前端生产构建通过。万点容量优化后稳定请求p95=65.28ms，重载中位1155ms，冷批次最大116.68ms。合成样本、替身鉴权和空绑定表的边界详见性能报告。

部署后 health 和经实际登录鉴权的 point-archive/meta 均 HTTP200，backend healthy，frontend running。浏览器实际打开正式测点档案页。正式档案 revision1，站/间隔/设备/测点均0；原有1条机器人、2个账号保留。未将预览测试数据导入正式环境。

核验容器 store.py 与本地 SHA256一致：bbf9e081420d216369b4136a38f6d10bff2e9bcf1a1f59fd82e1d14fd23e8c12。

## 备份与回退

更新前停止后端，备份完整原部署（含SQLite和环境配置）：
/home/hxzh/fms-backups/20260917-point-archive-v1/deployment-before.tar.gz。
备份目录权限700；SHA256：9c169cb97463fc6e39d161704b167a3d12cc64a7836d6c53b459de1ee3904edf。

回退应用镜像：

```sh
cd /home/hxzh/straitbot-fms
cp /home/hxzh/fms-backups/20260917-point-archive-v1/docker-compose.rollback.yml docker-compose.release.yml
docker compose -p straitbot-fms -f docker-compose.yml -f docker-compose.release.yml up -d --no-build
```

旧镜像0e2a1d8保留。数据库变更为增加表/可空列，应用回退不会删除新增档案。需要恢复数据时，先停止后端并另备份更新后的完整data目录，再从发布前备份恢复SQLite与JSON为同一时间点；不可仅覆盖单一文件造成引用错配。

后续启动继续同时传入 docker-compose.yml 和 docker-compose.release.yml。保持单后端worker。测试日志位于 /home/hxzh/fms-point-archive-dev；构建与部署日志均保留。未执行机器人控制/OTA，其他宿主机服务未调整。

## 用户验收入口

工程师账号登录后选择“测点档案（下沉）”。按变电站、间隔、设备、测点顺序新增，或使用JSON导入预览。航点绑定在测点详情/编辑内操作；菜单中的独立“航点绑定测点（下沉）”页面仍是此前原型，不应当作本期真实绑定入口。Excel和模板克隆待后续实现。