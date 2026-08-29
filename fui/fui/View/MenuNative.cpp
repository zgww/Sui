#include "MenuNative.h"
#include "../Core/Mouse.h"

#ifdef _WIN32
#include <windows.h>
#include <windowsx.h>
#include "../Naga/Utf8Util.h"
#endif

static int gMenuId = 10000;
static Ref<MenuNative> currentMenuNative = nullptr;





//弹出菜单的消息勾子
static LRESULT HookProc(int code, WPARAM wp, LPARAM lp) {
	if (code == MSGF_MENU) {
		PMSG pMsg = (PMSG)lp;
		if (pMsg->message == WM_MOUSEMOVE) {
			auto clientX = (int)(short)LOWORD(lp);
			auto clientY = (int)(short)HIWORD(lp);

			// URGC_VAR_CLEANUP SuiCore$App *app = NULL;
			// SuiCore$App_use(&app);
			// app->layoutAndDrawAllWindows(app);

			//auto win = get_window_by_hwnd(pMsg->hwnd);
			//auto r = win->getClientRect();

			POINT p = { 0 };
			ClientToScreen(pMsg->hwnd, &p);
			// GetWindowRect(pMsg->hwnd, &rect);

			RECT clientRect = {};
			GetClientRect(pMsg->hwnd, &clientRect);

			auto screenX = GET_X_LPARAM(pMsg->lParam);
			auto screenY = GET_Y_LPARAM(pMsg->lParam);


			//SuiCore$MouseData md = { 0 };
			//md.clientX = screenX - p.x;
			//md.clientY = screenY - p.y;
			//md.button = 0;
			//md.isMouseMove = true;
			//md.windowId = (long long)pMsg->hwnd;

			//// printf("HOokProc WM_MOUSEMOVE. %d,%d. %d,%d\n", clientX, clientY
			//// , md.clientX, md.clientY);

			//SuiCore$Mouse_onMouseMove(md);
			//SuiCore$App_repaintWindowById((long long)pMsg->hwnd);

			Mouse_onMouseMove((long long)pMsg->hwnd, screenX - p.x, screenY - p.y, false, false, false);
			App_repaintWindowById((long long)pMsg->hwnd);
			// App::ins()->_remap_up_position.remap_onmove(&e);
			// e.dispatchMouseMove();


			//printf("mousemove hook: %d %d window:%d\n", e.client_x, e.client_y, win->getId());
			//_mouse_move(win, pMsg->wParam, pMsg->lParam);
		}

	}
	return CallNextHookEx(NULL, code, wp, lp);

}





MenuNativeItem::MenuNativeItem() {
	commandId = gMenuId;
	id = gMenuId;
	gMenuId++;
}

void MenuNativeItem::append(MenuNativeItem* item) {
	children->push(item);
}

Ref<MenuNativeItem> mkMenuNativeItem(MenuNativeItem* parent, const std::string& label, Ref<Closure<void(MenuNativeItem*)>> onActive) {
	Ref<MenuNativeItem> ins{ new MenuNativeItem() };
	ins->label = label;
	ins->cmd = label;
	ins->onActive = onActive;
	if (parent) {
		parent->append(ins);
	}
	return ins;
}

Ref<MenuNative> MenuNative::mk(MenuNativeItem* root) {
	auto ret = Ref(new MenuNative());
	ret->create(root);
	return ret;
}
MenuNative::MenuNative() {
	//CtorGuard(this);

	currentMenuNative = this;
}

#ifdef _WIN32
static HMENU _buildNativeMenuRecursive(MenuNativeItem* item) {
	HMENU hMenu = CreatePopupMenu();
	if (!item) return hMenu;
	int l = item->children->size();
	for (int i = 0; i < l; i++) {
		MenuNativeItem* kid = item->children->get(i);
		if (!kid) continue;
		UINT flags = MF_STRING;
		std::wstring wlabel = Utf8Util::toutf16(kid->label);
		if (kid->children->size() > 0) {
			flags = MF_POPUP;
			HMENU hSubMenu = _buildNativeMenuRecursive(kid);
			AppendMenuW(hMenu, flags | MF_STRING, (UINT_PTR)hSubMenu, L">");
			ModifyMenuW(hMenu, (UINT_PTR)hSubMenu, MF_POPUP | MF_STRING, (UINT_PTR)hSubMenu,
				wlabel.c_str()
			
			);
		} else {
			AppendMenuW(hMenu, flags, (UINT_PTR)kid->commandId, wlabel.c_str());
		}
	}
	return hMenu;
}
#endif

void MenuNative::create(MenuNativeItem* root) {
	this->root = root;
#ifdef _WIN32
	HMENU hMenu = _buildNativeMenuRecursive(root);
	this->id = (int64_t)hMenu;
#endif
}

void MenuNative::show() {
	Vec2 s = Mouse_getPos();
	showAtScreenPosition((int)s.x, (int)s.y);
}




void MenuNative::showAt(int clientX, int clientY) {
#ifdef _WIN32
	HWND hwnd = (HWND)windowId;
	if (!hwnd) {
		hwnd = GetForegroundWindow();
	}
	POINT pt;
	pt.x = clientX;
	pt.y = clientY;
	ClientToScreen(hwnd, &pt);



	auto hook = SetWindowsHookEx(WH_MSGFILTER, HookProc, NULL, GetCurrentThreadId());
	TrackPopupMenu((HMENU)id, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, hwnd, nullptr);
	UnhookWindowsHookEx(hook);
	onDismiss();
#endif
}

void MenuNative::showAtScreenPosition(int screenX, int screenY) {
#ifdef _WIN32
	HWND hwnd = (HWND)windowId;
	if (!hwnd) {
		hwnd = GetForegroundWindow();
	}
	auto hook = SetWindowsHookEx(WH_MSGFILTER, HookProc, NULL, GetCurrentThreadId());
	TrackPopupMenu((HMENU)id, TPM_LEFTALIGN | TPM_TOPALIGN, screenX, screenY, 0, hwnd, nullptr);
	UnhookWindowsHookEx(hook);
	onDismiss();
	PostMessage(hwnd, WM_NULL, 0, 0);
#endif
}

void MenuNative::showAtMouse() {
	Vec2 p = Mouse_getPos();
	showAtScreenPosition((int)p.x, (int)p.y);
}

void MenuNative::onDismiss() {
	if (cbOnDismiss) {
		cbOnDismiss->invoke();
	}
	auto t = mkTimerTimeout(CLOSURE([=]() {
		currentMenuNative = nullptr;
	}), 200);
}

void MenuNative::destroy() {
#ifdef _WIN32
	if (id) {
		EndMenu(); //关闭菜单
		auto ok = DestroyMenu((HMENU)id);//释放菜单资源
		auto err = GetLastError();
		id = 0;
	}
#endif
}

bool MenuNative::dispatchCommand(MenuNativeItem* item, Window* win, int commandId) {
	if (!item) return false;
	if (item->commandId == commandId) {
		if (item->onActive) {
			item->onActive->invoke(item);
		}
		return true;
	}
	int l = item->children->size();
	for (int i = 0; i < l; i++) {
		MenuNativeItem* kid = item->children->get(i);
		if (!kid) continue;
		bool succ = dispatchCommand(kid, win, commandId);
		if (succ) return true;
	}
	return false;
}

void MenuNative_doCommand(int64_t windowId, int commandId) {
	if (currentMenuNative && currentMenuNative->root) {
		currentMenuNative->dispatchCommand(currentMenuNative->root, nullptr, commandId);
	}
}
