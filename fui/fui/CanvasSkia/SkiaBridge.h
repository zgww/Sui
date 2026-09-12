#pragma once

class SkSurface;
class GrDirectContext;

// 由 WindowWin32Skia 在每帧绘制前调用：
// 将当前窗口的 SkSurface(SkCanvas) 与 GrDirectContext 绑定到共享的 SkiaCtx，
// 随后 Canvas::beginFrame/endFrame 在该目标上工作。
void skiaCanvasBindFrame(SkSurface* surface, GrDirectContext* grContext);

// ---- 全 GPU 视频播放支持（HwVideoPlayerView）----
// 可选：在创建任何 fui Window 之前注入外部 D3D11 设备。
// ANGLE 将基于该设备创建 EGL Display，FFmpeg D3D11VA 解码器与
// Skia/GL 渲染共享同一 ID3D11Device，解码帧纹理才能零拷贝导入。
void skiaSetExternalD3D11Device(void* d3d11Device);
void* skiaGetExternalD3D11Device();

// 窗口层将 EGL Display 注册到共享上下文（HwVideoPlayerView 创建 EGLImage 需要）
void skiaSetEGLDisplay(void* eglDisplay);
void* skiaGetEGLDisplay();

// 当前帧绑定目标（每帧 skiaCanvasBindFrame 之后有效）：
// GrDirectContext* —— 视频 GPU 纹理必须创建在窗口同一个 Skia GPU 上下文上
void* skiaCanvasGetGrContext();

// 在当前帧 SkCanvas 上按源区域->目标区域绘制外部 SkImage（void* 传入，避免头依赖）
void skiaCanvasDrawImageAtRect(void* skImage, float sx, float sy, float sw, float sh,
                               float dx, float dy, float dw, float dh, float alpha);
