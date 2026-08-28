#pragma once

#include "../Core/Predef.h"
#include "../Core/Mouse.h"
#include "../Core/Vec2.h"
#include "../Core/Timer.h"
#include "../Core/App.h"
#include "../Core/Window.h"
#include <vector>


#define HIER(Expr) {auto _tmp = Expr; auto o = _tmp;
#define HEND }


class MenuNativeItem : public GcObj {
public:
	int commandId = 0;
	int id = 0;
	std::string cmd;
	std::string label;
	Ref<Closure<void(MenuNativeItem*)>> onActive{nullptr, this};

	Ref<GcList<MenuNativeItem>> children{new GcList<MenuNativeItem>(), this};

	MenuNativeItem();
	void append(MenuNativeItem* item);
};

Ref<MenuNativeItem> mkMenuNativeItem(MenuNativeItem* parent, const std::string& label, Ref<Closure<void(MenuNativeItem*)>> onActive = nullptr);

class MenuNative : public GcObj {
public:
	int64_t id = 0;
	Ref<MenuNativeItem> root{nullptr, this};
	int64_t windowId = 0;

	Ref<Closure<void()>> cbOnDismiss{nullptr, this};

	MenuNative();
	void create(MenuNativeItem* root);
	void show();
	void showAt(int clientX, int clientY);
	void showAtScreenPosition(int screenX, int screenY);
	void showAtMouse();
	void onDismiss();
	void destroy();
	bool dispatchCommand(MenuNativeItem* item, Window* win, int commandId);

	static Ref<MenuNative> mk(MenuNativeItem* root);

	virtual const char* getClassName() const { return "MenuNative"; }
};

void MenuNative_doCommand(int64_t windowId, int commandId);
