#include "Window.h"
#include "ViewBase.h"
#include "View.h"
#include "App.h"
#include "Screen.h"
#include "Canvas.h"
#include "Frame.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "../Urgc/Urgc.h"
#include "../View/MenuNative.h"
#include "../View/SystemTrayIcon.h"


#ifdef _WIN32
#include <windows.h>
#include <windowsx.h>

#include "../nanovg/nanovg.h"
#include "../GL/glew.h"
#include "../GL/wglew.h"
#include "Defines_win.h"

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

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


class GetAssisKey {
public:
	GetAssisKey() {
		lctrl = (GetKeyState(VK_LCONTROL) & 0x8000);
		rctrl = (GetKeyState(VK_RCONTROL) & 0x8000);
		lshift = (GetKeyState(VK_LSHIFT) & 0x8000);
		rshift = (GetKeyState(VK_RSHIFT) & 0x8000);
		lalt = (GetKeyState(VK_MENU) & 0x8000);
		ralt = (GetKeyState(VK_RMENU) & 0x8000);

		ctrl = lctrl || rctrl;
		shift = lshift || rshift;
		alt = lalt || ralt;
	}
	bool lctrl = false;
	bool rctrl = false;
	bool ctrl = false;
	bool lshift = false;
	bool rshift = false;
	bool shift = false;

	bool lalt = false;
	bool ralt = false;
	bool alt = false;
};

static void _registerWinClass() {
	static bool registered = false;
	if (registered) return;
	registered = true;

	WNDCLASSW wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = L"fuiWindow";
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = nullptr;
	RegisterClassW(&wc);
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

static const char* vkToKeyName(WPARAM vk) {
	switch (vk) {
	case VK_BACK: return "Backspace";
	case VK_TAB: return "Tab";
	case VK_RETURN: return "Enter";
	case VK_ESCAPE: return "Escape";
	case VK_DELETE: return "Delete";
	case VK_LEFT: return "ArrowLeft";
	case VK_RIGHT: return "ArrowRight";
	case VK_UP: return "ArrowUp";
	case VK_DOWN: return "ArrowDown";
	case VK_HOME: return "Home";
	case VK_END: return "End";
	case VK_PRIOR: return "PageUp";
	case VK_NEXT: return "PageDown";
	case VK_SHIFT: return "Shift";
	case VK_CONTROL: return "Control";
	case VK_MENU: return "Alt";
	case VK_CAPITAL: return "CapsLock";
	case VK_SPACE: return " ";
	default: break;
	}
	if (vk >= 'A' && vk <= 'Z') {
		static char buf[2];
		buf[0] = (char)vk;
		buf[1] = 0;
		return buf;
	}
	if (vk >= '0' && vk <= '9') {
		static char buf[2];
		buf[0] = (char)vk;
		buf[1] = 0;
		return buf;
	}
	return "";
}

static int _command(HWND win, WPARAM wp, LPARAM lp) {


	auto ok = IDOK;
	auto cancel = IDCANCEL;
	auto type = HIWORD(wp);
	auto realid = LOWORD(wp);

	int id = wp;

	MenuNative_doCommand((long long)win, id);
	/* if (g_current_native_menu) {

		 auto item = g_current_native_menu->root->by_id(id);
		 if (item) {
			 if (item->click) {
				 try {
					 item->click->call();
				 }
				 catch (std::exception& e) {
					 printf("_command捕获到异常:%s\n", e.what());
				 }
			 }
		 }
		 g_current_native_menu = nullptr;
	 }*/
	return 0;
}
static void _build_md_for_ontrayicon(
	MouseData* md,
	HWND hwnd, WPARAM wp, LPARAM lp, int button
	, int type//0:down,1:move,2:up, 3: dblclick
) {
	// SuiCore$MouseData md = { 0 };
	auto msg = LOWORD(lp);
	auto uid = HIWORD(lp);

	//md.eventType = "mousedown";
	md->button = button;
	md->clientX = GET_X_LPARAM(wp);
	md->clientY = GET_Y_LPARAM(wp);
	md->windowId = (long long)hwnd;
	md->isMouseDown = type == 0;
	md->isMouseMove = type == 1;
	md->isMouseUp = type == 2;
	md->isDoubleClick = type == 3;

	GetAssisKey ak;
	md->ctrl = ak.ctrl;
	md->shift = ak.shift;
	md->alt = ak.alt;
}

static LRESULT _ontrayicon(HWND hwnd, WPARAM wp, LPARAM lp)
{
	auto msg = LOWORD(lp);
	auto uid = HIWORD(lp);
	MouseData md = { 0 };
	md.button = -1;
	md.uid = uid;

	//注意。 实际上并不会在按下时，就触发事件。而是在up时，同时触发down/up
	if (msg == WM_LBUTTONDOWN) { _build_md_for_ontrayicon(&md, hwnd, wp, lp, 1, 0); }
	if (msg == WM_MBUTTONDOWN) { _build_md_for_ontrayicon(&md, hwnd, wp, lp, 2, 0); }
	if (msg == WM_RBUTTONDOWN) { _build_md_for_ontrayicon(&md, hwnd, wp, lp, 3, 0); }

	if (msg == WM_MOUSEMOVE) { _build_md_for_ontrayicon(&md, hwnd, wp, lp, 1, 1); }

	if (msg == WM_LBUTTONUP) { _build_md_for_ontrayicon(&md, hwnd, wp, lp, 1, 2); }
	if (msg == WM_MBUTTONUP) { _build_md_for_ontrayicon(&md, hwnd, wp, lp, 2, 2); }
	if (msg == WM_RBUTTONUP) { _build_md_for_ontrayicon(&md, hwnd, wp, lp, 3, 2); }

	if (msg == WM_LBUTTONDBLCLK) { _build_md_for_ontrayicon(&md, hwnd, wp, lp, 1, 3); }
	if (msg == WM_MBUTTONDBLCLK) { _build_md_for_ontrayicon(&md, hwnd, wp, lp, 2, 3); }
	if (msg == WM_RBUTTONDBLCLK) { _build_md_for_ontrayicon(&md, hwnd, wp, lp, 3, 3); }

	if (md.button != -1) {//说明是鼠标相关事件
		// if (md.isDoubleClick){
		//     POINT pt{};
		//     GetCursorPos(&pt);//取鼠标坐标
		//     ::SetForegroundWindow(hwnd);//解决在菜单外单击左键菜单不消失的问题
		//     auto hMenu = CreatePopupMenu();//生成菜单
		//     //为托盘菜单添加两个选项
		//     AppendMenu(hMenu, MF_STRING, 1, TEXT("update"));
		//     AppendMenu(hMenu, MF_STRING, 2, TEXT("show"));
		//     AppendMenu(hMenu, MF_STRING, 3, TEXT("about"));
		//     auto id = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, hwnd, NULL);
		//     printf("on menu activate:%d\n", id);
		// }
		//SuiCore$printMouseData(&md, "_mousedown");
		SystemTrayIcon_onMouseData(&md);
	}
	return 0;
}
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int64_t winId = (int64_t)hWnd;

	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY: {
		Window* win = (Window*)GetPropA(hWnd, "fuiWindow");
		if (win) {
			win->onDestroy();
		}
		break;
	}
	case WM_SIZE: {
		App_use()->invalidDraw();
		break;
	}
	case WM_MOUSEMOVE: {
		float x = (float)GET_X_LPARAM(lParam);
		float y = (float)GET_Y_LPARAM(lParam);
		bool shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
		bool alt = (GetKeyState(VK_MENU) & 0x8000) != 0;
		bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
		Mouse_onMouseMove(winId, x, y, shift, alt, ctrl);
		break;
	}
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN: {
		float x = (float)GET_X_LPARAM(lParam);
		float y = (float)GET_Y_LPARAM(lParam);
		int button = (uMsg == WM_LBUTTONDOWN) ? 0 : (uMsg == WM_RBUTTONDOWN ? 1 : 2);
		bool shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
		bool alt = (GetKeyState(VK_MENU) & 0x8000) != 0;
		bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
		Mouse_onMouseDown(winId, x, y, button, shift, alt, ctrl);
		SetCapture(hWnd);
		break;
	}
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP: {
		float x = (float)GET_X_LPARAM(lParam);
		float y = (float)GET_Y_LPARAM(lParam);
		int button = (uMsg == WM_LBUTTONUP) ? 0 : (uMsg == WM_RBUTTONUP ? 1 : 2);
		bool shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
		bool alt = (GetKeyState(VK_MENU) & 0x8000) != 0;
		bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
		Mouse_onMouseUp(winId, x, y, button, shift, alt, ctrl);
		ReleaseCapture();
		break;
	}
	case WM_LBUTTONDBLCLK: {
		float x = (float)GET_X_LPARAM(lParam);
		float y = (float)GET_Y_LPARAM(lParam);
		Mouse_onMouseDown(winId, x, y, 0, false, false, false);
		break;
	}
	case WM_MOUSEWHEEL: {
		POINT pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hWnd, &pt);
		float x = (float)pt.x;
		float y = (float)pt.y;
		float deltaY = -(float)GET_WHEEL_DELTA_WPARAM(wParam) / 120.0f * 40.0f;
		float deltaX = 0;
		bool shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
		bool alt = (GetKeyState(VK_MENU) & 0x8000) != 0;
		bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
		Mouse_onWheel(winId, x, y, deltaY, deltaX, shift, alt, ctrl);
		break;
	}
	case WM_KEYDOWN: {
		bool shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
		bool alt = (GetKeyState(VK_MENU) & 0x8000) != 0;
		bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
		const char* keyName = vkToKeyName(wParam);
		Keyboard_onKeyDown(winId, (int)wParam, keyName, shift, ctrl, alt);
		break;
	}
	case WM_KEYUP: {
		bool shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
		bool alt = (GetKeyState(VK_MENU) & 0x8000) != 0;
		bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
		const char* keyName = vkToKeyName(wParam);
		Keyboard_onKeyUp(winId, (int)wParam, keyName, shift, ctrl, alt);
		break;
	}
	case WM_CHAR: {
		wchar_t wc = (wchar_t)wParam;
		if (wc >= 32) {
			char buf[8] = {0};
			WideCharToMultiByte(CP_UTF8, 0, &wc, 1, buf, sizeof(buf), nullptr, nullptr);
			if (buf[0] != 0) {
				char keyStr[2] = {buf[0], 0};
				Keyboard_onKeyDown(winId, (int)buf[0], keyStr, false, false, false);
			}
		}
		break;
	}
	// 菜单事件
	case WM_COMMAND:
	{
		return _command(hWnd, wParam, lParam);
	}
	case FUI_WM_TRAYICON://自定义的托盘消息
	{
		// lParam是消息类型
		return _ontrayicon(hWnd, wParam, lParam);
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

Window::Window() {
	CtorGuard _(this);

	Ref<View> defaultView{new View()};
	defaultView->backgroundColor = 0x00000000;
	rootView = defaultView;

	canvas = new Canvas();

	rootView->setOwnerWindow(this);
	rootView->setMounted(true);

	App* app = App_use();
	app->addWindow(this);
}

Window::~Window() {
	cleanData();
	printf("release Window %p\n", this);
}

void Window::setTransparent() {}

void Window::setRootView(ViewBase* v) {
	if (v == rootView) return;
	if (rootView) {
		rootView->setMounted(false);
		rootView->setOwnerWindow(nullptr);
	}
	rootView = v;
	if (rootView) {
		rootView->setOwnerWindow(this);
		rootView->setMounted(true);
	}
}

void Window::show() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) ShowWindow(data->hwnd, SW_SHOW);
	App_use()->invalidDraw();
}

void Window::hide() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) ShowWindow(data->hwnd, SW_HIDE);
}

void Window::maximize() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) ShowWindow(data->hwnd, SW_MAXIMIZE);
}

void Window::minimize() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) ShowWindow(data->hwnd, SW_MINIMIZE);
}

void Window::normal() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) ShowWindow(data->hwnd, SW_NORMAL);
}

void Window::enable(bool enable) {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) EnableWindow(data->hwnd, enable ? TRUE : FALSE);
}

void Window::close() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) DestroyWindow(data->hwnd);
}

void Window::setOwner(Window* ownerWindow) {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	WindowDataWin32* ownerData = ownerWindow ? (WindowDataWin32*)ownerWindow->data : nullptr;
	if (data && ownerData) {
		SetWindowLongPtr(data->hwnd, GWLP_HWNDPARENT, (LONG_PTR)ownerData->hwnd);
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

void Window::layout() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data && rootView) {
		Vec2 clientSize = getClientSize();
		Frame* ctx = &rootView->frame;
		ctx->setTight(clientSize.x, clientSize.y);
		rootView->layout(ctx);
	}
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

bool Window::isVisible() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) return IsWindowVisible(data->hwnd) != 0;
	return false;
}

void Window::layoutAndDraw() {
	if (!isVisible()) return;
	layoutTimes++;
	fps.startFrame();
	{
		fps.startLayout();
		layout();
		fps.endLayout();
	}
	{
		fps.startDraw();
		draw();
		fps.endDraw();
	}
	fps.endFrame();
}

void Window::onDestroy() {
	App* app = App_use();
	app->removeWindow(this);
}

void Window::setTitle(const char* title) {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) {
		int wlen = MultiByteToWideChar(CP_UTF8, 0, title, -1, nullptr, 0);
		wchar_t* wstr = new wchar_t[wlen];
		MultiByteToWideChar(CP_UTF8, 0, title, -1, wstr, wlen);
		SetWindowTextW(data->hwnd, wstr);
		delete[] wstr;
	}
}

std::string Window::getTitle() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) {
		int wlen = GetWindowTextLengthW(data->hwnd) + 1;
		wchar_t* wstr = new wchar_t[wlen];
		GetWindowTextW(data->hwnd, wstr, wlen);
		int alen = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
		std::string result(alen - 1, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &result[0], alen, nullptr, nullptr);
		delete[] wstr;
		return result;
	}
	return "";
}

Vec2 Window::getPos() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) {
		RECT rect;
		GetWindowRect(data->hwnd, &rect);
		return mkVec2((float)rect.left, (float)rect.top);
	}
	return mkVec2(0, 0);
}

void Window::setPos(float x, float y) {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) {
		SetWindowPos(data->hwnd, nullptr, (int)x, (int)y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
}

Vec2 Window::getSize() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) {
		RECT rect;
		GetWindowRect(data->hwnd, &rect);
		return mkVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));
	}
	return mkVec2(0, 0);
}

void Window::setSize(float x, float y) {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) {
		RECT rect;
		GetWindowRect(data->hwnd, &rect);
		int adjustedW = (int)x;
		int adjustedH = (int)y;
		AdjustWindowRect(&rect, GetWindowLong(data->hwnd, GWL_STYLE), FALSE);
		int nonClientW = (rect.right - rect.left) - (rect.right - rect.left);
		int nonClientH = (rect.bottom - rect.top) - (rect.bottom - rect.top);
		SetWindowPos(data->hwnd, nullptr, 0, 0, adjustedW, adjustedH, SWP_NOMOVE | SWP_NOZORDER);
	}
}

void Window::setRect(float x, float y, float w, float h) {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) {
		SetWindowPos(data->hwnd, nullptr, (int)x, (int)y, (int)w, (int)h, SWP_NOZORDER);
	}
}

Vec2 Window::getClientSize() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) {
		RECT rect;
		GetClientRect(data->hwnd, &rect);
		return mkVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));
	}
	return mkVec2(0, 0);
}

Inset Window::getNonClientInset() {
	WindowDataWin32* data = (WindowDataWin32*)this->data;
	if (data) {
		RECT winRect, clientRect;
		GetWindowRect(data->hwnd, &winRect);
		GetClientRect(data->hwnd, &clientRect);
		POINT pt{ clientRect.left, clientRect.top };
		ClientToScreen(data->hwnd, &pt);
		Inset ret;
		ret.left = (float)(pt.x - winRect.left);
		ret.top = (float)(pt.y - winRect.top);
		ret.right = (float)(winRect.right - (pt.x + clientRect.right - clientRect.left));
		ret.bottom = (float)(winRect.bottom - (pt.y + clientRect.bottom - clientRect.top));
		return ret;
	}
	return mkInset0();
}

void Window::moveToCenter() {
	Vec2 screenSize = Screen_get_usable_size();
	Vec2 size = getSize();
	setPos(
		(screenSize.x - size.x) / 2.0f,
		(screenSize.y - size.y) / 2.0f
	);
}

void DragCrossWindowIndicator::_start() {}
void DragCrossWindowIndicator::_end() {}
void DragCrossWindowIndicator::_dragMove() {}

void DragCrossWindowIndicator::start() {
	dragging = true;
	_start();
	Ref<DragCrossWindowIndicator> self = this;
	requestAnimationFrame(CLOSURE([=]() -> bool {
		self->onDragMove(mkVec2(0, 0));
		return !self->dragging;
	}));
}

void DragCrossWindowIndicator::end() {
	dragging = false;
	_end();
}

void DragCrossWindowIndicator::onDragMove(Vec2 clientPos) {
	_dragMove();
}

#else

Window::Window() {}
Window::~Window() {}
void Window::setTransparent() {}
void Window::setRootView(ViewBase* v) {}
void Window::show() {}
void Window::hide() {}
void Window::maximize() {}
void Window::minimize() {}
void Window::normal() {}
void Window::enable(bool) {}
void Window::close() {}
void Window::setOwner(Window*) {}
void Window::initData() {}
void Window::cleanData() {}
void Window::layout() {}
void Window::draw() {}
bool Window::isVisible() { return false; }
void Window::layoutAndDraw() {}
void Window::onDestroy() {}
void Window::setTitle(const char*) {}
std::string Window::getTitle() { return ""; }
Vec2 Window::getPos() { return mkVec2(0, 0); }
void Window::setPos(float, float) {}
Vec2 Window::getSize() { return mkVec2(0, 0); }
void Window::setSize(float, float) {}
void Window::setRect(float, float, float, float) {}
Vec2 Window::getClientSize() { return mkVec2(0, 0); }
Inset Window::getNonClientInset() { return mkInset0(); }
void Window::moveToCenter() {}

#endif
