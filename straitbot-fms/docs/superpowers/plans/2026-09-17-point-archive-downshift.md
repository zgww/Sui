# 测点档案下沉 Implementation Plan

> **For agentic workers:** Use the available `executing-plans` skill to implement this plan task-by-task in the current session. Steps use checkbox (`- [ ]`) syntax for tracking. This document is a plan, not authorization to deploy or change production data.

**Goal:** 为单套 1 万以内、低频修改的测点档案建立 JSON 持久化与缓存索引查询，接通当前静态页面，同时保持旧平台兼容。

**Architecture:** 一个版本化 JSON 快照保存台账主数据。单进程仓储负责验证、查询和原子发布；SQLite 保存导航点绑定及运行数据。前端通过鉴权分页 API 获取数据。

**Tech Stack:** Python 3.11、FastAPI、Pydantic 2、stdlib json/os、SQLAlchemy/SQLite、React/TypeScript、pytest。

**Spec:** [设计方案](../../POINT-ARCHIVE-DOWNSHIFT-DESIGN.md)；[性能证据](../../performance/point-archive-20260917.md)。

## Global Constraints

- 单套 FMS ≤10,000 测点，初期限额 32 MiB JSON；运行数据与附件不写入快照。
- Java/Vue 继续维护，不改旧接口；字符串 ID/前导零原样保留，`isDelete=1` 映射有效。
- 一期单后端进程、唯一写入入口；`If-Match` 修订号冲突返回 409。
- 台账树分层加载，分页默认 50、最大 200，稳定 `(code, id)` 排序。
- 新增业务接口复用 `engineer_only`；运行任务走内部仓储；不开放静态 JSON 路径。
- 不新增数据库服务器、Redis、搜索引擎或框架升级。
- 既有模型与 API 不代表已存在测点绑定能力；不得将静态演示数据导入线上充当真实档案。

## Task 1：数据契约与旧档案导入校验

**Files:** 新增 `backend/app/point_archive/__init__.py`、`schema.py`、`legacy.py`；新增 `backend/tests/test_point_archive_schema.py`。

**Interfaces:** `normalize_legacy_point(row: dict) -> dict` 将 camelCase 与状态映射为方案字段；`validate_snapshot(raw: dict) -> dict` 返回校验后的规范快照，错误抛 `ArchiveValidationError`（在 schema.py 定义）。保留 source 与 extensions。

- [ ] 写下列回归，执行 `python -m pytest tests/test_point_archive_schema.py -q`，先确认缺少实现而失败。

```python
import pytest
from app.point_archive.legacy import normalize_legacy_point
from app.point_archive.schema import ArchiveValidationError

def test_preserve_legacy_identity():
    row = normalize_legacy_point({"id": "001001001001001", "code": "0007",
        "name": "油温表", "equipmentId": "001001001001", "isDelete": 1})
    assert row["id"] == "001001001001001"
    assert row["code"] == "0007"
    assert row["equipment_id"] == "001001001001"
    assert row["active"] is True

def test_invalid_legacy_status():
    with pytest.raises(ArchiveValidationError):
        normalize_legacy_point({"id": "1", "isDelete": 9})
```

- [ ] 实现 schema_version/revision、层级集合、唯一 ID、父引用/环检测、枚举/非有限数值验证；重复编码允许保留，精确查询返回多候选；重复 JSON 键在解码时拒绝。
- [ ] 添加重复 ID、悬空设备、前导零、超容量、额外字段保留的用例，全部运行通过。实际旧导出覆盖模板/克隆关联时给出显式映射清单，未映射内容阻止正式导入。
- [ ] 单独提交 `feat(point-archive): define archive schema and legacy mapping`。

## Task 2：只读仓储与索引

**Files:** 新增 `backend/app/point_archive/store.py`；新增 `backend/tests/test_point_archive_store.py`、`backend/tests/point_archive_fixtures.py`；修改 `backend/app/config.py` 定义 `ARCHIVE_DIR`，修改 `backend/app/main.py` 在 lifespan 初始化仓储。

**Interfaces:** `ArchiveStore(path: Path)`；`initialize(raw: dict)` 仅允许目标不存在；`load()`；`get(point_id: str) -> dict | None`；`list_points(name=None, code=None, equipment_id=None, page=1, page_size=50) -> dict`；`tree(parent_type, parent_id, page, page_size) -> dict`。运行时返回副本/只读视图，不暴露可变缓存。

- [ ] 在 `tests/point_archive_fixtures.py` 定义最小合法快照，不依赖生产文件：

```python
def empty_snapshot():
    return {"schema_version": 1, "revision": 1,
            "updated_at": "2026-09-17T18:00:00+08:00",
            "source": {"system": "test", "export_revision": "test-1"},
            "stations": [], "bays": [], "equipment": [], "points": []}
```
- [ ] 建立该回归，先运行失败，再实现启动加载与一次建索引：

```python
from tests.point_archive_fixtures import empty_snapshot

def test_request_does_not_reread_file(tmp_path, monkeypatch):
    from pathlib import Path
    from app.point_archive.store import ArchiveStore
    store = ArchiveStore(tmp_path / "archive.json")
    store.initialize(empty_snapshot())
    def reject_read(*args, **kwargs):
        raise AssertionError("query reread JSON")
    monkeypatch.setattr(Path, "read_text", reject_read)
    assert store.list_points()["items"] == []
    assert store.get("missing") is None
```

- [ ] 实现方案所列 ID/编码/层级/类型索引与稳定排序；过滤先缩小集合，分页后序列化；增加重复编码、尾页、组合过滤、树层级测试。
- [ ] 执行 `python -m pytest tests/test_point_archive_store.py -q`；用基准脚本的合成数据验证仓储结果与全表扫描一致。
- [ ] 单独提交 `feat(point-archive): add cached indexed reads`。

## Task 3：原子发布与关联约束

**Files:** 新增 `backend/app/point_archive/publication.py`、`backend/app/models/point_binding.py`，修改 `models/__init__.py` 注册；新增 `backend/tests/test_point_archive_publication.py`。告警模板绑定留给独立配置能力，本任务不实现模板克隆引擎。

**Interfaces:** `ArchiveStore.publish(raw: dict, expected_revision: int) -> int`；`RevisionConflict`、`ReferencedPointError` 定义在 publication.py。新增 SQLite `PointBinding`：整数主键、字符串 point_id、外键 waypoint_pk/action_pk、archive_revision；绑定服务新增前检查点存在且有效。JSON 无 SQL 外键，引用校验由服务完成。

- [ ] 在测试中初始化空快照；首次 publish 返回 2，第二次使用 expected_revision=1 应抛 RevisionConflict：

```python
from tests.point_archive_fixtures import empty_snapshot

def test_stale_publish_is_rejected(tmp_path):
    import pytest
    from app.point_archive.store import ArchiveStore
    from app.point_archive.publication import RevisionConflict
    store = ArchiveStore(tmp_path / "archive.json")
    store.initialize(empty_snapshot())
    assert store.publish(empty_snapshot(), expected_revision=1) == 2
    with pytest.raises(RevisionConflict):
        store.publish(empty_snapshot(), expected_revision=1)
```

- [ ] 实现单写锁、锁内修订号/引用重检、备份、同目录临时写入、fsync、replace、目录 fsync 与内存快照交换。新索引构建失败不改变旧版本。
- [ ] 模拟 `os.replace` 失败，验证磁盘/内存旧版本都有效；模拟磁盘发布成功后的切换失败，验证服务拒绝继续写入并从磁盘恢复。
- [ ] SQLite 测试库内覆盖：绑定不存在点失败、删除有引用点失败、逻辑停用保留历史、并发发布与绑定没有悬空引用。所有关系修改共用同一变更锁。
- [ ] 执行 schema/store/publication 三组测试后单独提交 `feat(point-archive): publish snapshots safely`。

## Task 4：鉴权 API 与前端替换静态数据

**Files:** 新增 `backend/app/routers/point_archive.py`、`frontend/src/api/pointArchive.ts`、`backend/tests/test_point_archive_api.py`；修改 `backend/app/main.py`、`frontend/src/views/sink/PointArchive.tsx`。保留其他页面使用的 `sink/data.ts` 导出，不能全文件删除。

**Interfaces:** 实现设计中的 meta/tree/points/detail/import-preview/snapshot/export；服务端返回 `{revision,total,page,page_size,items}`。API 的 binding 参数先查关系 ID 集合，再与仓储候选集合合并，禁止逐测点 SQL。

- [ ] 使用 FastAPI TestClient 和隔离临时仓储，验证未登录 401、operator 403、engineer 正常读取；通过 dependency_overrides 注入测试身份，测试结束清理 overrides。
- [ ] 校验页码/页长不合法返回 422，缺失点 404，旧 revision 或引用冲突 409，preview 不改文件及修订号。
- [ ] 前端定义明确 TS 类型与 API 包装；以实际接口替换 POINTS/ARCHIVE_TREE，树展开才加载子节点，搜索防抖、分页重置、409 刷新提示。
- [ ] 基础档案新增/编辑/停用通过候选快照发布，导入预览后再提交；只读接口尚未支持的模板克隆/Excel 操作明确禁用，不能保留可点击的假成功按钮。Excel 转换作为 JSON 契约之上的独立后续任务。
- [ ] `python -m pytest tests/test_point_archive_api.py -q` 和前端 `npm run build`；浏览器验证加载、空列表、错误、搜索、分页、编辑后刷新持久化。
- [ ] 单独提交 `feat(point-archive): connect archive APIs and UI`。

## Task 5：真实数据验收与发布准备

**Files:** 更新 `docs/POINT-ARCHIVE-DOWNSHIFT-DESIGN.md`、新增 `docs/performance/point-archive-api-validation.md`（真实执行后填写），涉及任务取配置时修改 `backend/app/routers/inspection.py` 与对应测试，任务实例保存 archive_revision 和必要配置快照。

- [ ] 导入经用户选择的真实站点导出到隔离环境，核对总数、ID、父关系、编码和检测字段；导入未知模板关系应报告，不能忽略。
- [ ] 测试任务取配置后修改档案名称/参数，验证已生成任务快照与历史结果保持原值，新任务使用新 revision。
- [ ] 运行全部 `python -m pytest tests -q` 与前端构建；使用 1 万点、50 条分页、10 并发，在目标硬件测列表 p95、启动加载、发布耗时、双快照内存峰值；目标见设计。
- [ ] 对旧平台受影响调用方做契约回归；本地档案/SQLite 备份和恢复演练必须成对记录，检查重新启动后修订号与引用一致。
- [ ] 记录成果、未覆盖范围、发布命令与回退条件。实际部署待对应任务授权；当前规划任务不部署。

## 本次规划自检

- [x] 明确规模、静态/动态边界和 JSON 查询方式。
- [x] 对照旧档案查询、层级 ID、导航点及模板关联。
- [x] 在 ARM64 部署机隔离完成合成数据基准，保存脚本与原始结果。
- [x] 覆盖并发写、损坏恢复、跨 SQLite 引用和未来扩展条件。
- [x] 标明实现路径、接口约定、回归测试与上线验收。
- [ ] 以上 Task 1–5 尚未执行；本文件不表示业务已经实现。

## 2026-09-17 实施状态补充

用户已授权开发、十轮测试及部署到 192.168.6.88，取代上文规划阶段“当前不部署”的限制。
基础档案 JSON 仓储、索引查询、原子发布、工程师 API、页面 CRUD/导入预览、SQLite 航点绑定及任务快照已实现。
实际测试与容量结果统一记录在 ../../performance/point-archive-api-validation.md（从本目录访问）；发布记录见 docs/DEPLOY-POINT-ARCHIVE-192.168.6.88.md。
上文逐项清单保留为原计划，不代表每个可选步骤均已执行：本次使用合成数据，尚无用户提供的真实站点导出；未创建 Git 提交，未执行现场设备联调。
