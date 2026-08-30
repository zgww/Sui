#pragma once

// Canvas 的 Direct2D 后端辅助接口。
// Canvas.h 的原接口保持不变；这里只提供后端切换必须的附加能力。
// 仅在编译期定义了 FUI_CANVAS_D2D 时，Canvas_d2d.cpp 才提供这些实现。

// 绑定接下来 beginFrame/endFrame 所使用的渲染目标窗口。
// 多窗口场景：每帧绘制前把当前窗口的 HWND 传进来。
// 传 nullptr 表示解除绑定（之后 beginFrame 为空操作）。
void Canvas_d2d_bindHwnd(void* hwnd);

// 窗口销毁时释放对应的 HwndRenderTarget
void Canvas_d2d_releaseHwnd(void* hwnd);

// 清空当前渲染目标（等价于 GL 后端里 Window::draw 的 glClear）
void Canvas_d2d_clear(int color);

// 注册字体文件，等价于 nanovg 的 nvgCreateFont(vg, name, path)
// 解析字体文件内部的家族名并记录别名映射；已安装的系统字体可直接按家族名使用。
bool Canvas_d2d_createFont(const char* name, const char* path);

// 查询图片句柄的尺寸（Image::width/height 在 D2D 后端下使用）
void Canvas_d2d_imageSize(void* canvasData, int img, int* w, int* h);

// 离屏渲染：绑定一个 WIC 位图目标（不依赖窗口），返回是否成功
bool Canvas_d2d_beginOffscreen(int w, int h);

// 读取离屏目标像素（BGRA 预乘），返回内部缓冲区指针；w/h 可为 nullptr
const unsigned char* Canvas_d2d_offscreenPixels(int* w, int* h);
