// NanoVG GLES2 后端实现（独立翻译单元，供 ES2 上下文使用）
// 注意包含顺序: nanovg_gl.h 的声明区使用 NVGcontext/GLuint，
// 需先包含 GL 头和 nanovg.h（与 main.cpp 中的用法一致）
#include <GLES2/gl2.h>

#include "nanovg/nanovg.h"

#define NANOVG_GLES2_IMPLEMENTATION
#include "nanovg/nanovg_gl.h"
