# -*- coding: utf-8 -*-
"""prefab 系统自检：注册 / schema / 加载 / 生命周期 / tick。

运行方式（在 backend/ 目录下）:
    python scripts/prefab_selfcheck.py
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

from app.prefab import (PrefabLoader, build, registered_types, schema_for_all,
                        tree_to_dict)
from app.prefab.base import Context, NodeBase
from app.prefab.runtime import PrefabRuntime

PASS = 0
FAIL = 0


def check(name: str, cond: bool, extra: str = "") -> None:
    global PASS, FAIL
    if cond:
        PASS += 1
        print(f"  [PASS] {name} {extra}")
    else:
        FAIL += 1
        print(f"  [FAIL] {name} {extra}")


def main() -> int:
    print("== 1. 注册表（__init_subclass__ 自动注册）==")
    types = registered_types()
    print(f"  已注册类型: {sorted(types)}")
    check("组合节点已注册", "Sequence" in types and "Parallel" in types and "Selector" in types)
    check("定时节点已注册", "CronTimer" in types and "IntervalTimer" in types)
    check("动作节点已注册", "LogAction" in types and "HttpAction" in types)
    check("配置节点已注册", "ConfigNode" in types)
    check("中间类不注册", "CompositeNode" not in types)

    print("\n== 2. type 默认值 = 注册名 ==")
    n = types["LogAction"](message="hi")
    check("type 自动填充", n.type == "LogAction", f"got={n.type!r}")

    print("\n== 3. JSON Schema 含 ui 元数据 ==")
    schema = schema_for_all()
    log_schema = schema["LogAction"]["schema"]
    msg_prop = log_schema["properties"].get("message", {})
    check("message.ui.widget=text", msg_prop.get("ui", {}).get("widget") == "text")
    check("通用字段在 schema 中", "name" in log_schema["properties"] and "enabled" in log_schema["properties"])
    check("schema 数量 == 注册数量", len(schema) == len(types))

    print("\n== 4. 加载 prefab 目录（含嵌套）==")
    prefab_dir = Path(__file__).resolve().parent.parent / "app" / "prefab" / "prefabs"
    loader = PrefabLoader(prefab_dir)
    errors = loader.load_all()
    print(f"  加载错误: {errors}")
    check("全部加载成功", len(errors) == 0, f"errors={errors}")
    check("加载树数量 >= 3", len(loader.trees) >= 3, f"trees={list(loader.trees)}")
    tree = loader.get("示例-配置注入")
    check("示例-配置注入已加载", tree is not None)
    if tree and tree.root:
        check("嵌套结构构建", len(tree.root.child_nodes) == 2,
              f"children={[c.type for c in tree.root.child_nodes]}")
        check("ConfigNode 实例化", tree.root.child_nodes[0].type == "ConfigNode")

    print("\n== 5. 生命周期（激活/事件/tick/失活）==")
    runtime = PrefabRuntime(loader)
    runtime.activate_all()
    tree = loader.get("示例-配置注入")
    check("树激活", tree is not None and tree.state == "active", f"state={tree.state}")
    if tree and tree.root:
        check("节点状态 active", all(c.state == "active" for c in tree.root.child_nodes),
              f"states={[c.state for c in tree.root.child_nodes]}")
        ctx = runtime.contexts["示例-配置注入"]
        check("ConfigNode 注入 Context.kv", ctx.kv.get("site") == "A区", f"kv={ctx.kv}")

    # 事件总线机制：激活后再订阅 + 手动 emit 验证
    ctx = runtime.contexts["示例-配置注入"]
    evts: list = []
    ctx.on("test-event", lambda p: evts.append(p))
    ctx.emit("test-event", {"k": 1})
    check("Context 事件总线收发", len(evts) == 1 and evts[0]["k"] == 1, f"events={evts}")

    print("\n== 5.1 IntervalTimer tick 驱动 ==")
    from app.prefab import build
    it_tree = build({
        "type": "Sequence",
        "properties": {"name": "定时测试"},
        "children": [{
            "type": "IntervalTimer",
            "properties": {"name": "秒表", "interval": 0.5},
        }],
    })
    it_ctx = Context()
    it_events: list = []
    it_ctx.on("timer", lambda p: it_events.append(p))
    it_tree.activate(it_ctx)
    check("IntervalTimer 激活", it_tree.state == "active")
    it_tree.tick(it_ctx, 0.3)
    it_tree.tick(it_ctx, 0.3)
    check("IntervalTimer 到点 emit timer", len(it_events) == 1, f"events={it_events}")

    print("\n== 6. 错误隔离（未知类型文件）==")
    bad_dir = Path(__file__).resolve().parent / "_bad_prefab"
    bad_dir.mkdir(exist_ok=True)
    (bad_dir / "bad.prefab.json").write_text(
        '{"name":"bad","root":{"type":"NotExistNode","properties":{}}}', encoding="utf-8")
    bad_loader = PrefabLoader(bad_dir)
    bad_errors = bad_loader.load_all()
    check("错误被收集而非崩溃", len(bad_errors) == 1 and "未知节点类型" in bad_errors[0],
          f"errors={bad_errors}")
    (bad_dir / "bad.prefab.json").unlink()
    bad_dir.rmdir()

    print("\n== 7. tree_to_dict 状态标注 ==")
    if tree and tree.root:
        d = tree_to_dict(tree.root)
        check("状态标注存在", d.get("_state") == "active" and isinstance(d.get("children"), list))
        check("业务字段保留", "message" in d.get("children", [{}])[1],
              f"children[1] keys={list(d.get('children', [{}])[1].keys())}")

    runtime.deactivate_all()
    if tree and tree.root:
        check("失活后状态 inactive",
              all(c.state == "inactive" for c in tree.root.child_nodes),
              f"states={[c.state for c in tree.root.child_nodes]}")

    print(f"\n结果: PASS={PASS} FAIL={FAIL}")
    return 1 if FAIL else 0


if __name__ == "__main__":
    sys.exit(main())
