"""节点类型自动发现：启动时 import 包内全部模块，触发 __init_subclass__ 注册。

新增节点类型 = 在本包下新建一个模块并继承 NodeBase，无需改任何现有文件。
"""
import importlib
import pkgutil

for _m in pkgutil.iter_modules(__path__):
    importlib.import_module(f"{__name__}.{_m.name}")
