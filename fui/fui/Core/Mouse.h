#pragma once

#include "Predef.h"
#include "Vec2.h"

struct MouseData {
	float clientX = 0;
	float clientY = 0;
	int button = 0;
	int64_t windowId = 0;
	bool isMouseDown = false;
	bool isMouseMove = false;
	bool isMouseUp = false;
	bool isDoubleClick = false;
	int uid = 0;
	bool shift = false;
	bool alt = false;
	bool ctrl = false;
};

Vec2 Mouse_getPos();
Vec2 Mouse_getPosOfWindow(int64_t windowId);

class MouseEvent;
class ViewBase;
class Window;

void setMouseEventFromMouseData(MouseEvent* event, MouseData* md, Window* win);
MouseEvent* newMouseEventFromMouseData(MouseData* md, Window* win);
void dispatchMouseEvent(ViewBase* rootView, MouseData* md, Window* win);
void dispatchMouseMoveEvent(ViewBase* rootView, MouseData* md, Window* win);
void Mouse_onMouseDown(int64_t windowId, float x, float y, int button, bool shift, bool alt, bool ctrl);
void Mouse_onMouseMove(int64_t windowId, float x, float y, bool shift, bool alt, bool ctrl);
void Mouse_onMouseUp(int64_t windowId, float x, float y, int button, bool shift, bool alt, bool ctrl);
void Mouse_onWheel(int64_t windowId, float x, float y, float deltaY, float deltaX, bool shift, bool alt, bool ctrl);
void printMouseData(MouseData* md);
