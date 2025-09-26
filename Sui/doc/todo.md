

* [o] 项目管理面板列表
* [o] 项目管理面板保存
* [o] 项目管理面板加载
* [o] 项目管理面板导入
* [o] 项目管理面板双击打开项目
* [o] 颜色面板 
* [o] 树视图 arrow 图标
* [o] 曲线编辑器 (Tip: nanovg fill曲线有问题。无法绘制非凸包. 像素格式要选择带stencil buffer的，就可以了)
* [o] 树视图多选(ctrl)
* [o] 树视图多选(shift)
* [o] 场景编辑-细化
* [o] 资源预览
* [o] orc 嵌套closure对self的捕获bug: 嵌套的closure没有加入对blockInfo的捕获导致的
* [o] orc 返回值为结构体的 扩展函数调用，会生成错误的 &returnStruct() 代码。 不能对返回值取地址
* [-] orc UiAction.orc中  o.cb = new ChessBgViewCallback 代码生成错误。。应该生成urgc_set_field_class的
* [-] TileEditor.orc中  类字段 Vec2 tilePos = mkVec2 程序崩溃
* [-] TileEditor.orc中  闭包对for循环的Int的引用有问题,编译不过

* [-] 列表编辑器

* [o] 菜单栏整理
- [o] 实现MessageDialog_confirm
- [o] 实现MessageDialog_prompt
* [o] MenuNativeItem strId改为cmd
* [o] String成员改为静态函数

* [o] 在当前目录view右键-删除文件
* [o] 在当前目录view右键-重命名文件
* [o] 在当前目录view-ctrl多选文件
* [o] 在当前目录view-shift多选文件
* [o] 在当前目录view右键-创建prefab
* [o] 在当前目录view空白处-右键-创建prefab
* [o] 在当前目录view右键-创建目录
* [o] 在当前目bbview右键-打开Prefab
* [o] 在当前目录view右键-新窗口显示图片
* [-] 在当前目录view右键-拖拽移动文件

* [o] 在project右键-删除目录
* [o] 在project右键-创建目录
* [o] 在project右键-重命名目录
* [o] 在project空白处-右键-创建目录
* [-] 在project右键-拖拽移动目录

* [o] 场景树右键菜单
* [o] 保存prefab
* [o] 关闭场景
* [o] 组件菜单
* [o] 添加组件
* [o] 多选视图(ctrl/shift)
* [o] 右键菜单-在场景中定位视图
* [o] 右键-删除组件
* [o] 右键-剪切视图
* [o] 右键-复制视图
* [o] 右键-粘贴视图
* [o] 右键-重命名视图
* [-] 拖拽移动组件

* [o] 场景-缩放
* [o] 场景-gizmo机制
* [o] 场景-gizmo-rect
* [o] 场景-gizmo-resize
* [>] 场景-gizmo-旋转

* [o] 检视器-按继承显示属性
* [o] 检视器-文本编辑
* [o] 检视器-数字编辑
* [o] 检视器-颜色编辑
* [o] 检视器-图片选择
* [o] 检视器-图片搜索选择窗口
* [o] 检视器-switch
* [o] 检视器-文件引用
* [o] 检视器-下拉选择
* [o] 检视器-slider
* [o] 检视器-vector编辑
* [>] 检视器-视图引用; 延后。 视图引用并不方便.更好的方案是生成绑定代码, 并可以自动更新。 手拖还是比较麻烦的
* [o] 检视器-曲线编辑

* [>] 检视器-动态表达式 延后，包括if/for。。先实现最普通的prefab
* [>] prefab-for
* [>] prefab-if
* [>] prefab-include
* [>] 生成绑定代码-带有prefab id
* [>] 更新绑定代码-通过prefab id去搜索

* [o] 检视器-预览-图片
* [o] 检视器-弹窗-模型
* [o] 检视器-弹窗-文本文件
* [>] 检视器-弹窗-音频
* [o] 检视器-弹窗-文件的基本信息

* [-] hierachy 拖拽顺序

* [-] 快捷键-ctrl+s 保存
* [-] 增加枚举的元数据
* [o] orc增加结构体判断

* [-] 运行按钮
* [-] 运行预览预制

* [o] 精灵图动画编辑
* [o] 瓦片图编辑

* [o] Sgl-buffer
* [o] Sgl-vbo
* [o] Sgl-vao
* [o] Sgl-Tex2d
* [o] Sgl-Program
* [o] Sgl-Mat4
* [o] Sgl-Geometry
* [o] Sgl-Geometry-导入json格式
* [o] Sgl-Geometry-导入obj
* [o] Sgl-draw 设置材质和geometry就可以绘制
* [o] Sgl-fbo
* [o] Sgl-rbo
* [o] Sgl-材质
* [o] Sgl-材质Insp
* [o] Sgl-材质预览，，拖拽旋转模型、缩放模型
* [o] Sgl-材质保存
* [o] Sgl-材质创建
* [o] Sgl-材质加载


# 场景编辑

## 设计思路


设计器本身不直接编辑视图。
为什么，因为场景并不只是纯粹由视图构成的。
场景是含有逻辑的。。

特别是场景需要支持
虚拟块、包含子场景、if/for、属性表达式。

如果直接在视图上编辑，那就需要有额外的地方来存放
这些逻辑信息。
同时，默认的属性值、非编辑的属性值怎么从原视图
区分出来，也是很麻烦的事情。

引入虚拟节点。。 使整个设计器，设计的是原来的代码编辑ui
文件的工作。类似于vue中的模板。。
vue的模板，是DSL，不是视图树本身。


### 组件库

### 组件注册

注册到NodeLib?

### 虚拟块

### 包含include

### if

### for

### 属性表达式

## 序列化

prefab元数据包一层，然后root根结点表示ANode树

### 保存

转成json直接存

### 加载

从json反序列化


### inspector 


## tilemap

结构:
tilemap
    width
    height
    tileWidth
    tileHeight

    tilesets[]
        imgPath
        startGid
    layers[]

TileLayer extends Layer
    IntArray data

ObjectLayer extends Layer
    TileObjects[] objects


Attr:
    String name
    String value

TileObject
    shape
    Attr[] attrs


TileShape

TileShapeRect extends TileShape
    int x
    int y
    int width
    int height

TileShapeCircle extends TileShape
    int cx
    int cy

TileShapePolygon extends TileShape
    Vec2Array points

TileShapePolyline extends TileShape
    Vec2Array points

### 窗口
菜单栏
工具栏(保存、创建、绘制对象)
层列表  地图  检视器

瓦片工具栏(创建自动瓦片autotile)
tilesets列表    tileset瓦片