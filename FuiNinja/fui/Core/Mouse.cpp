#include "Mouse.h"
#include "MouseEvent.h"
#include "ViewBase.h"
#include "Window.h"
#include "App.h"
#include "Cursor.h"
#include "../Urgc/GcList.h"

#ifdef _WIN32
#include <windows.h>
#endif

Vec2 Mouse_getPos() {
#ifdef _WIN32
	POINT pt;
	GetCursorPos(&pt);
	return mkVec2((float)pt.x, (float)pt.y);
#else
	return mkVec2(0, 0);
#endif
}

Vec2 Mouse_getPosOfWindow(int64_t windowId) {
#ifdef _WIN32
	POINT pt;
	GetCursorPos(&pt);
	HWND hwnd = (HWND)windowId;
	ScreenToClient(hwnd, &pt);
	return mkVec2((float)pt.x, (float)pt.y);
#else
	return mkVec2(0, 0);
#endif
}

static float mouseDownClientX = 0;
static float mouseDownClientY = 0;
void setMouseEventFromMouseData(MouseEvent* event, MouseData* md, Window* win) {
	if (md->isMouseDown) {
		mouseDownClientX = md->clientX;
		mouseDownClientY = md->clientY;
	}

	event->clientX = md->clientX;
	event->clientY = md->clientY;
	event->mouseDownClientX = mouseDownClientX;
	event->mouseDownClientY = mouseDownClientY;
	event->button = md->button;
	event->window = win;
	event->isMouseDown = md->isMouseDown;
	event->isMouseUp = md->isMouseUp;
	event->isMouseMove = md->isMouseMove;
	event->ctrl = md->ctrl;
	event->shift = md->shift;
	event->alt = md->alt;

	if (md->isMouseDown) {
		event->name = "mousedown";
	} else if (md->isMouseUp) {
		event->name = "mouseup";
	} else if (md->isMouseMove) {
		event->name = "mousemove";
	}
}

MouseEvent* newMouseEventFromMouseData(MouseData* md, Window* win) {
	Ref<MouseEvent> event{new MouseEvent()};
	setMouseEventFromMouseData(event, md, win);
	return event;
}

void dispatchMouseEvent(ViewBase* rootView, MouseData* md, Window* win) {
	if (!rootView) return;
	ViewBase* hit = rootView->hitTest(md->clientX, md->clientY);
	if (!hit) return;

	if (md->isMouseDown) {
		printf("mousedown\n");
	}

	Ref<MouseEvent> event{ new MouseEvent() };
	setMouseEventFromMouseData(event, md, win);

	event->target = hit;
	preprocessMouseEvent(event);
	propagateViewEvent(event);
}

void dispatchMouseMoveEvent(ViewBase* rootView, MouseData* md, Window* win) {
	if (!win || !rootView) {
		return;
	}

	Ref<MouseEvent> event{new MouseEvent()};
	setMouseEventFromMouseData(event, md, win);

	ViewBase* hit = rootView->hitTest(md->clientX, md->clientY) ;

	if (!hit) {
		hit = rootView;
	}
	event->target = hit;
	propagateViewEvent(event);

	HoverSentive* hs = sinsHoverSentive();
	if (hs) {
		hs->onmousemove(rootView, md->clientX, md->clientY);
	}
}

void Mouse_onMouseDown(int64_t windowId, float x, float y, int button, bool shift, bool alt, bool ctrl) {
	App* app = App_use();
	Window* win = app->findWindowById(windowId);
	if (!win || !win->rootView) return;

	MouseData md;
	md.clientX = x;
	md.clientY = y;
	md.button = button;
	md.windowId = windowId;
	md.isMouseDown = true;
	md.shift = shift;
	md.alt = alt;
	md.ctrl = ctrl;

	dispatchMouseEvent(win->rootView, &md, win);
}

void Mouse_onMouseMove(int64_t windowId, float x, float y, bool shift, bool alt, bool ctrl) {
	App* app = App_use();
	Window* win = app->findWindowById(windowId);
	if (!win || !win->rootView) return;

	MouseData md;
	md.clientX = x;
	md.clientY = y;
	md.windowId = windowId;
	md.isMouseMove = true;
	md.shift = shift;
	md.alt = alt;
	md.ctrl = ctrl;
	//printf("dispatchMouseMoveEvent :%s\n", win->getTitle().c_str());

	dispatchMouseMoveEvent(win->rootView, &md, win);
}

void Mouse_onMouseUp(int64_t windowId, float x, float y, int button, bool shift, bool alt, bool ctrl) {
	App* app = App_use();
	Window* win = app->findWindowById(windowId);
	if (!win || !win->rootView) return;

	MouseData md;
	md.clientX = x;
	md.clientY = y;
	md.button = button;
	md.windowId = windowId;
	md.isMouseUp = true;
	md.shift = shift;
	md.alt = alt;
	md.ctrl = ctrl;

	dispatchMouseEvent(win->rootView, &md, win);
}

void Mouse_onWheel(int64_t windowId, float x, float y, float deltaY, float deltaX, bool shift, bool alt, bool ctrl) {
	App* app = App_use();
	Window* win = app->findWindowById(windowId);
	if (!win || !win->rootView) return;

	ViewBase* hit = win->rootView->hitTest(x, y);
	if (!hit) return;

	Ref<WheelEvent> event{new WheelEvent()};
	event->name = "wheel";
	event->clientX = x;
	event->clientY = y;
	event->button = 0;
	event->window = win;
	event->isWheel = true;
	event->deltaY = deltaY;
	event->deltaX = deltaX;
	event->shift = shift;
	event->alt = alt;
	event->ctrl = ctrl;
	event->target = hit;

	propagateViewEvent(event);
}

void printMouseData(MouseData* md) {
	printf("MouseData: client(%f,%f) button:%d down:%d move:%d up:%d\n",
		md->clientX, md->clientY, md->button, md->isMouseDown, md->isMouseMove, md->isMouseUp);
}


Vec2 Mouse_getPosOfWindow(Window* window) {
	if (window) {
		Vec2 pos = Mouse_getPos();
		Vec2 winPos = window->getPos();
		return mkVec2(pos.x - winPos.x, pos.y - winPos.y);
	}
	return mkVec2(0.f, 0.f);
}