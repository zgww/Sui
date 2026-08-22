#include "MenuNative.h"
#include "../Core/Mouse.h"

#ifdef _WIN32
#include <windows.h>
#endif

static int gMenuId = 10000;
static Ref<MenuNative> currentMenuNative = nullptr;

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
		if (kid->children->size() > 0) {
			flags = MF_POPUP;
			HMENU hSubMenu = _buildNativeMenuRecursive(kid);
			AppendMenuW(hMenu, flags | MF_STRING, (UINT_PTR)hSubMenu, L">");
			ModifyMenuW(hMenu, (UINT_PTR)hSubMenu, MF_POPUP | MF_STRING, (UINT_PTR)hSubMenu,
				std::wstring(kid->label.begin(), kid->label.end()).c_str());
		} else {
			std::wstring wlabel(kid->label.begin(), kid->label.end());
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
	POINT pt;
	pt.x = clientX;
	pt.y = clientY;
	ClientToScreen(hwnd, &pt);
	TrackPopupMenu((HMENU)id, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, hwnd, nullptr);
#endif
}

void MenuNative::showAtScreenPosition(int screenX, int screenY) {
#ifdef _WIN32
	HWND hwnd = (HWND)windowId;
	if (!hwnd) {
		hwnd = GetForegroundWindow();
	}
	TrackPopupMenu((HMENU)id, TPM_LEFTALIGN | TPM_TOPALIGN, screenX, screenY, 0, hwnd, nullptr);
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
		DestroyMenu((HMENU)id);
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
