#include "SystemTrayIcon.h"
#include "MenuNative.h"
#include "../Core/Mouse.h"
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#include "../Core/Defines_win.h"
#endif

static int gTrayUid = 100;
static std::vector<SystemTrayIcon*> gTrays;
static bool gAtExitRegistered = false;

static void onAppExit() {
	for (int i = (int)gTrays.size() - 1; i >= 0; i--) {
		SystemTrayIcon* tray = gTrays[i];
		if (tray) tray->destroy();
	}
}

SystemTrayIcon::SystemTrayIcon() {
	gTrayUid++;
	uid = gTrayUid;
}

void SystemTrayIcon::setIconPath(const char* path) {
	iconPath = path ? path : "";
}

#ifdef _WIN32

static bool _initTrayData(SystemTrayIcon* tray) {
	HWND hwnd = GetForegroundWindow();
	if (!hwnd) hwnd = CreateWindowEx(0, L"Static", L"", 0, 0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr);

	static NOTIFYICONDATAW nid = {0};
	nid.cbSize = sizeof(nid);
	nid.hWnd = hwnd;
	nid.uID = tray->uid;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = FUI_WM_TRAYICON;
	nid.uVersion = NOTIFYICON_VERSION_4;

	std::wstring wpath(tray->iconPath.begin(), tray->iconPath.end());
	HICON hIcon = (HICON)LoadImageW(nullptr, wpath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	if (!hIcon) hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	nid.hIcon = hIcon;
	wcscpy_s(nid.szTip, L"fui");



	BOOL ok = Shell_NotifyIconW(NIM_ADD, &nid);
	Shell_NotifyIconW(NIM_SETVERSION, &nid);


	tray->data = hwnd;
	return ok ? true : false;
}

static bool _destroyTrayData(SystemTrayIcon* tray) {
	if (!tray->data) return false;
	NOTIFYICONDATAW nid = {0};
	nid.cbSize = sizeof(nid);
	nid.hWnd = (HWND)tray->data;
	nid.uID = tray->uid;
	nid.uFlags = 0;
	BOOL ok = Shell_NotifyIconW(NIM_DELETE, &nid);
	tray->data = nullptr;
	return ok ? true : false;
}
#endif

bool SystemTrayIcon::init() {
#ifdef _WIN32
	if (!gAtExitRegistered) {
		gAtExitRegistered = true;
		atexit(onAppExit);
	}
	bool ok = _initTrayData(this);
	if (ok) {
		gTrays.push_back(this);
	}
	return ok;
#else
	return false;
#endif
}

void SystemTrayIcon::destroy() {
#ifdef _WIN32
	bool ok = _destroyTrayData(this);
	if (ok) {
		for (auto it = gTrays.begin(); it != gTrays.end(); ++it) {
			if (*it == this) {
				gTrays.erase(it);
				break;
			}
		}
	}
#endif
}

SystemTrayIcon* SystemTrayIcons_findByUid(int uid) {
	for (auto tray : gTrays) {
		if (tray && tray->uid == uid) return tray;
	}
	return nullptr;
}

void SystemTrayIcon_onMouseData(MouseData* md) {
	if (!md) return;
	SystemTrayIcon* tray = SystemTrayIcons_findByUid(md->uid);
	if (!tray) return;

	if (md->isDoubleClick) {
		Ref<Closure<void(MenuNativeItem*)>> onActive = CLOSURE([=](MenuNativeItem* item) {
			if (item->label == "exit") {
				exit(0);
			}
			if (item->label == "delete icon") {
				tray->destroy();
			}
		});

		MenuNativeItem* root = mkMenuNativeItem(nullptr, "", onActive);
		mkMenuNativeItem(root, "exit", onActive);
		mkMenuNativeItem(root, "delete icon", onActive);
		mkMenuNativeItem(root, "menu3", onActive);
		mkMenuNativeItem(root, "menu4", onActive);
		mkMenuNativeItem(root, "menu5", onActive);

		MenuNative* n = new MenuNative();
		n->windowId = md->windowId;
		n->create(root);
		n->showAtMouse();
	}
}
