# gizmo2d/3d 设计

imgui/rmgui 本质是一样的。可以采用auto react方式融合在一起。
imgui也不是直接绘制的。 也是需要有状态的。只是状态是自动管理的。
imgui的好处在于声明式，只需要声明期望。

gizmo主要是给以下使用的：

* 工具
* 选中的
* 特殊节点，如相机、粒子、灯光、风场

在drawCtx.draw之后调用.draw到同一个fbo中。共用depthBuffer, stencilBuffer


gizmo有draw和响应鼠标事件的能力。。

gizmo节点和正常的结点没啥区别。。。