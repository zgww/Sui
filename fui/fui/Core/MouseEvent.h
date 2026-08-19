#pragma once

#include "Predef.h"
#include "Event.h"
#include "Vec2.h"

class ViewBase;
class Window;

class ViewEvent : public Event {
public:
	Ref<ViewBase> target{nullptr, this};
	Ref<ViewBase> currentTarget{nullptr, this};
	bool isCapture = false;
	bool isBubble() { return !isCapture; }
};

struct ClickRecord {
	float downX = 0;
	float downY = 0;
	int64_t downTime = 0;
	int button = 0;
};

static const int MouseEvent_clickOffsetThreshold = 10;

class MouseEvent : public ViewEvent {
public:
	float clientX = 0;
	float clientY = 0;
	Ref<Window> window{nullptr, this};
	Vec2 ndcPos;
	int button = 0;
	float mouseDownClientX = 0;
	float mouseDownClientY = 0;

	bool isMouseDown = false;
	bool isMouseUp = false;
	bool isMouseMove = false;
	bool isWheel = false;

	bool ctrl = false;
	bool shift = false;
	bool alt = false;

	bool isDblClick = false;

	bool isClick();
	bool isClickInBubble();
	bool isDblClickInBubble();

	std::string toString() const {
		char tmp[256];
		snprintf(tmp, sizeof(tmp), "MouseEvent(%f,%f,btn:%d)", clientX, clientY, button);
		return std::string(tmp);
	}
};

class MouseEnterEvent : public MouseEvent {
};

class MouseLeaveEvent : public MouseEvent {
};

class WheelEvent : public MouseEvent {
public:
	float deltaY = 0;
	float deltaX = 0;
};

class MouseEventListener : public GcObj {
public:
	virtual void onEvent(MouseEvent* event) {}
};

class HoverSentive : public GcObj {
public:
	Ref<GcList<ViewBase>> hoverings{new GcList<ViewBase>(), this};

	void onmousemove(ViewBase* rootView, float x, float y);
	void onmouseleave();
};

MouseEventListener* createMouseEventListener(Ref<Closure<void(MouseEvent*)>> cb);
void propagateViewEvent(ViewEvent* event);
void preprocessMouseEvent(MouseEvent* event);
HoverSentive* sinsHoverSentive();
