#pragma once

class SkSurface;
class GrDirectContext;

// 由 WindowWin32Skia 在每帧绘制前调用：
// 将当前窗口的 SkSurface(SkCanvas) 与 GrDirectContext 绑定到共享的 SkiaCtx，
// 随后 Canvas::beginFrame/endFrame 在该目标上工作。
void skiaCanvasBindFrame(SkSurface* surface, GrDirectContext* grContext);
