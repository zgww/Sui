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

#include <windows.h>
#include <windowsx.h>
#include "../Naga/Win32Utf8Util.h"

#include "../nanovg/nanovg.h"
#include "../GL/glew.h"
#include "../GL/wglew.h"
#include "../Core/Defines_win.h"

#include <dwmapi.h>
#include <CommCtrl.h>
#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "Imm32.lib")
#pragma comment(lib, "comctl32.lib")

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

#define CLASS_NAME "fuiWindow"

typedef struct {
	HWND hwnd;
	HDC hdc;
	HGLRC hrc;
	NVGcontext* vg;
	float devicePixelRatio;
} WindowDataWin32;

static HGLRC g_shareHrc = nullptr;
static NVGcontext* g_sharedVg = nullptr;



void _registerWinClass();


HWND _getWindowHwnd(Window* win) {
	auto data = (WindowDataWin32*)win->data;
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

static void _enable_opengl(HWND hWnd, HDC* hDC, HGLRC* hRC) {
	*hDC = GetDC(hWnd);

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SUPPORT_COMPOSITION | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		8,
		0,
		0, 0, 0, 0,
		24, 8, 0,
		PFD_MAIN_PLANE,
		0, 0, 0
	};

	static int iPixelFormat = 0;
	if (iPixelFormat == 0) {
		iPixelFormat = ChoosePixelFormat(*hDC, &pfd);
	}
	SetPixelFormat(*hDC, iPixelFormat, &pfd);

	if (g_shareHrc == nullptr) {
		*hRC = wglCreateContext(*hDC);
		g_shareHrc = *hRC;
	} else {
		*hRC = g_shareHrc;
	}
	wglMakeCurrent(*hDC, *hRC);

	static bool glewInited = false;
	if (!glewInited) {
		glewInited = true;
		glewInit();
		wglSwapIntervalEXT(0);
	}
}


void Window::initData() {
	cleanData();

	WindowDataWin32* data = (WindowDataWin32*)calloc(1, sizeof(WindowDataWin32));

	_registerWinClass();
	HWND hwnd = _createWindow();
	SetPropA(hwnd, "fuiWindow", this);

	HDC hdc = nullptr;
	HGLRC hrc = nullptr;
	_enable_opengl(hwnd, &hdc, &hrc);

	this->id = (int64_t)hwnd;

	if (g_sharedVg) {
		canvas->data = g_sharedVg;
	} else {
		canvas->init();
		g_sharedVg = (NVGcontext*)canvas->data;
	}

	NVGcontext* vg = (NVGcontext*)canvas->data;
	nvgCreateFont(vg, "sans", "c:\\Windows\\Fonts\\msyh.ttc");
	nvgFontFace(vg, "sans");

	data->hwnd = hwnd;
	data->hdc = hdc;
	data->hrc = hrc;
	data->vg = vg;
	data->devicePixelRatio = (float)GetDeviceCaps(hdc, LOGPIXELSX) / 96.0f;
	devicePixelRatio = data->devicePixelRatio;

	this->data = data;
}

void Window::cleanData() {
	if (!data) return;
	WindowDataWin32* d = (WindowDataWin32*)data;
	if (d->hrc) d->hrc = nullptr;
	if (d->hwnd) {
		if (d->hdc) {
			ReleaseDC(d->hwnd, d->hdc);
			d->hdc = nullptr;
		}
		RemovePropA(d->hwnd, "fuiWindow");
		DestroyWindow(d->hwnd);
		d->hwnd = nullptr;
	}
	free(d);
	data = nullptr;
}
void Window::draw() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) {
		NVGcontext* vg = data->vg;
		HWND hwnd = data->hwnd;

		RECT rect = {};
		GetClientRect(hwnd, &rect);
		float w = (float)(rect.right - rect.left);
		float h = (float)(rect.bottom - rect.top);

		wglMakeCurrent(data->hdc, data->hrc);

		glDisable(GL_SCISSOR_TEST);
		glViewport(0, 0, (int)w, (int)h);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		nvgBeginFrame(vg, w, h, data->devicePixelRatio);
		if (rootView) {
			rootView->draw(canvas);
		}
		fps.draw(canvas, (int)h);
		nvgEndFrame(vg);

		SwapBuffers(data->hdc);
	}
}
