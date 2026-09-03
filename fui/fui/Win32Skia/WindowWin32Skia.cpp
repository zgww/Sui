// Win32 窗口 + ANGLE(EGL/GLES3) + Skia GPU 渲染
// initData: 初始化 EGL/GLES3 上下文与 Skia GrDirectContext
// cleanData: 清理本窗口的渲染资源
// draw: 使用 skia + es3 渲染一帧

#define NOMINMAX

// Skia 头文件须在 fui 头文件之前包含: fui 的 Core/Node.h 定义了 R/STATIC/CLASS 等宏,
// 会污染 Skia 模板(如 GrGLFunctions.h 中的模板参数 R), 导致 C1075。
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"
#include "include/gpu/ganesh/GrBackendSurface.h"
#include "include/gpu/ganesh/GrDirectContext.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "include/gpu/ganesh/gl/GrGLAssembleInterface.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLInterface.h"

#include "../Core/Window.h"
#include "../Core/ViewBase.h"
#include "../Core/View.h"
#include "../Core/App.h"
#include "../Core/Screen.h"
#include "../Core/Canvas.h"
#include "../Core/Frame.h"
#include "../Core/Mouse.h"
#include "../Core/Keyboard.h"
#include "../Core/KeyEvent.h"
#include "../Naga/Utf8Util.h"
#include "../Urgc/Urgc.h"
#include "../View/MenuNative.h"
#include "../View/SystemTrayIcon.h"
#include "../CanvasSkia/SkiaBridge.h"

#include <windows.h>
#include <windowsx.h>
#include "../Naga/Win32Utf8Util.h"

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include <dwmapi.h>
#include <CommCtrl.h>
#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "Imm32.lib")
#pragma comment(lib, "comctl32.lib")

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

#define CLASS_NAME "fuiWindow"

typedef struct {
	HWND hwnd;
	EGLSurface surface;                 // 每窗口独立的窗口表面
	EGLContext context;                 // 每窗口独立的GLES3上下文
	sk_sp<GrDirectContext> grContext;   // 每窗口独立的Skia GPU上下文
	sk_sp<SkSurface> skSurface;         // 包装FBO0的后台缓冲
	int width;
	int height;
	float devicePixelRatio;
} WindowDataWin32Skia;

static EGLDisplay g_eglDisplay = EGL_NO_DISPLAY;
static EGLConfig g_eglConfig = nullptr;

void _registerWinClass();


HWND _getWindowHwnd(Window* win) {
	auto data = (WindowDataWin32Skia*)win->data;
	if (data) {
		return data->hwnd;
	}
	return NULL;
}

static HWND _createWindow() {
	_registerWinClass();
	HWND hwnd = CreateWindowExW(
		0,
		L"fuiWindow",
		L"",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, GetModuleHandle(nullptr), nullptr
	);
	return hwnd;
}

static GrGLFuncPtr _egl_get_proc(void*, const char name[]) {
	return (GrGLFuncPtr)eglGetProcAddress(name);
}

// 全局初始化 EGL(ANGLE) 显示与配置, 进程内只执行一次
static bool _ensure_egl() {
	if (g_eglDisplay != EGL_NO_DISPLAY) {
		return true;
	}
	g_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (g_eglDisplay == EGL_NO_DISPLAY) {
		printf("fui skia: eglGetDisplay failed\n");
		return false;
	}
	EGLint major = 0, minor = 0;
	if (!eglInitialize(g_eglDisplay, &major, &minor)) {
		printf("fui skia: eglInitialize failed (0x%x)\n", eglGetError());
		g_eglDisplay = EGL_NO_DISPLAY;
		return false;
	}
	if (!eglBindAPI(EGL_OPENGL_ES_API)) {
		printf("fui skia: eglBindAPI failed (0x%x)\n", eglGetError());
		return false;
	}

	const EGLint configAttribs[] = {
		EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
		EGL_RED_SIZE,        8,
		EGL_GREEN_SIZE,      8,
		EGL_BLUE_SIZE,       8,
		EGL_ALPHA_SIZE,      8,
		EGL_DEPTH_SIZE,      0,
		EGL_STENCIL_SIZE,    8,
		EGL_NONE
	};
	EGLint numConfigs = 0;
	if (!eglChooseConfig(g_eglDisplay, configAttribs, &g_eglConfig, 1, &numConfigs) || numConfigs < 1) {
		printf("fui skia: eglChooseConfig failed (0x%x)\n", eglGetError());
		return false;
	}
	return true;
}

void Window::initData() {
	cleanData();

	WindowDataWin32Skia* data = new WindowDataWin32Skia();

	_registerWinClass();
	HWND hwnd = _createWindow();
	SetPropA(hwnd, "fuiWindow", this);

	this->id = (int64_t)hwnd;
	data->hwnd = hwnd;

	if (_ensure_egl()) {
		// 每窗口独立的表面 + GLES3上下文
		data->surface = eglCreateWindowSurface(g_eglDisplay, g_eglConfig, (EGLNativeWindowType)hwnd, nullptr);
		if (data->surface == EGL_NO_SURFACE) {
			printf("fui skia: eglCreateWindowSurface failed (0x%x)\n", eglGetError());
		} else {
			const EGLint contextAttribs[] = {
				EGL_CONTEXT_CLIENT_VERSION, 3,
				EGL_NONE
			};
			data->context = eglCreateContext(g_eglDisplay, g_eglConfig, EGL_NO_CONTEXT, contextAttribs);
			if (data->context == EGL_NO_CONTEXT) {
				printf("fui skia: eglCreateContext failed (0x%x)\n", eglGetError());
			} else {
				eglMakeCurrent(g_eglDisplay, data->surface, data->surface, data->context);
				eglSwapInterval(g_eglDisplay, 0);

				// Skia GPU 上下文 (基于ANGLE GLES3)
				sk_sp<const GrGLInterface> glInterface = GrGLMakeAssembledInterface(nullptr, _egl_get_proc);
				if (glInterface) {
					data->grContext = GrDirectContexts::MakeGL(glInterface);
				}
				if (!data->grContext) {
					printf("fui skia: GrDirectContexts::MakeGL failed\n");
				}
				eglMakeCurrent(g_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			}
		}
	}

	// 共享的Canvas状态(画笔/路径/字体/图像), 每帧由draw绑定目标
	canvas->init();

	HDC hdc = GetDC(hwnd);
	data->devicePixelRatio = (float)GetDeviceCaps(hdc, LOGPIXELSX) / 96.0f;
	ReleaseDC(hwnd, hdc);
	devicePixelRatio = data->devicePixelRatio;

	this->data = data;
}

void Window::cleanData() {
	if (!data) return;
	WindowDataWin32Skia* d = (WindowDataWin32Skia*)data;

	if (g_eglDisplay != EGL_NO_DISPLAY && d->context != EGL_NO_CONTEXT && d->surface != EGL_NO_SURFACE) {
		// 绑定上下文后清理GL/Skia资源
		eglMakeCurrent(g_eglDisplay, d->surface, d->surface, d->context);
		if (d->grContext) {
			d->grContext->flushAndSubmit();
		}
		d->skSurface.reset();
		d->grContext.reset();
		eglMakeCurrent(g_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	} else {
		d->skSurface.reset();
		d->grContext.reset();
	}
	if (g_eglDisplay != EGL_NO_DISPLAY) {
		if (d->surface != EGL_NO_SURFACE) {
			eglDestroySurface(g_eglDisplay, d->surface);
			d->surface = EGL_NO_SURFACE;
		}
		if (d->context != EGL_NO_CONTEXT) {
			eglDestroyContext(g_eglDisplay, d->context);
			d->context = EGL_NO_CONTEXT;
		}
	}
	if (d->hwnd) {
		RemovePropA(d->hwnd, "fuiWindow");
		DestroyWindow(d->hwnd);
		d->hwnd = nullptr;
	}
	delete d;
	data = nullptr;
}

void Window::draw() {
	WindowDataWin32Skia* data = (WindowDataWin32Skia*)this->data;
	if (!data || data->surface == EGL_NO_SURFACE || !data->grContext) return;

	RECT rect = {};
	GetClientRect(data->hwnd, &rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;
	if (w <= 0 || h <= 0) return;

	// 窗口尺寸变化时重建后台缓冲
	if (!data->skSurface || data->width != w || data->height != h) {
		data->skSurface.reset();
		EGLint stencilBits = 0, sampleCnt = 0;
		eglGetConfigAttrib(g_eglDisplay, g_eglConfig, EGL_STENCIL_SIZE, &stencilBits);
		eglGetConfigAttrib(g_eglDisplay, g_eglConfig, EGL_SAMPLES, &sampleCnt);

		GrGLFramebufferInfo fbInfo;
		fbInfo.fFBOID = 0;
		fbInfo.fFormat = GL_RGBA8;
		GrBackendRenderTarget rt = GrBackendRenderTargets::MakeGL(w, h, sampleCnt, stencilBits, fbInfo);

		data->skSurface = SkSurfaces::WrapBackendRenderTarget(
			data->grContext.get(), rt, kBottomLeft_GrSurfaceOrigin,
			kRGBA_8888_SkColorType, nullptr, nullptr);
		data->width = w;
		data->height = h;
		if (!data->skSurface) {
			printf("fui skia: WrapBackendRenderTarget failed (%dx%d)\n", w, h);
			return;
		}
	}

	eglMakeCurrent(g_eglDisplay, data->surface, data->surface, data->context);

	// 绑定本帧渲染目标, 然后通过Canvas接口绘制
	skiaCanvasBindFrame(data->skSurface.get(), data->grContext.get());

	canvas->beginFrame((float)w, (float)h, data->devicePixelRatio);
	if (rootView) {
		rootView->draw(canvas);
	}
	fps.draw(canvas, h);
	canvas->endFrame();

	eglSwapBuffers(g_eglDisplay, data->surface);
}
