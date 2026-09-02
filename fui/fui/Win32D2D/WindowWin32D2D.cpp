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

#include "../Core/Defines_win.h"

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
} WindowDataWin32;


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


void Window::initData() {
	cleanData();

	WindowDataWin32* data = (WindowDataWin32*)calloc(1, sizeof(WindowDataWin32));

	HWND hwnd = _createWindow();
	SetPropA(hwnd, "fuiWindow", this);

	this->id = (int64_t)hwnd;

	canvas->bindWindow(hwnd);

	HDC hdc = GetDC(hwnd);
	devicePixelRatio = (float)GetDeviceCaps(hdc, LOGPIXELSX) / 96.0f;
	ReleaseDC(hwnd, hdc);

	data->hwnd = hwnd;

	this->data = data;

}

void Window::cleanData() {
	if (!data) return;
	WindowDataWin32* d = (WindowDataWin32*)data;
	canvas->unbindWindow();
	if (d->hwnd) {
		RemovePropA(d->hwnd, "fuiWindow");
		DestroyWindow(d->hwnd);
		d->hwnd = nullptr;
	}
	free(d);
	data = nullptr;
}
