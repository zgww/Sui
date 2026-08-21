#include "Drag.h"
#include "../Core/ViewBase.h"
#include "../Core/Window.h"
#include "../Core/Cursor.h"

void Drag::setStatus(const char* status) {
	isDragChecking = false;
	isDragStart = false;
	isDragging = false;
	isDragEnd = false;

	if (strcmp(status, "checking") == 0) isDragChecking = true;
	else if (strcmp(status, "start") == 0) isDragStart = true;
	else if (strcmp(status, "dragging") == 0) isDragging = true;
	else if (strcmp(status, "end") == 0) isDragEnd = true;

	if (cursor != "") {
		if (isDragStart) {
			Cursor_ins()->setCursor(cursor.c_str());
			Cursor_ins()->setIsLocked(true);
		}
		else if (isDragEnd) {
			Cursor_ins()->setCursor("normal");
			Cursor_ins()->setIsLocked(false);
		}
	}
}

void Drag::onMouseDown(Event* e) {
	MouseEvent* me = dynamic_cast<MouseEvent*>(e);
	if (!me || !me->isMouseDown) return;

	mouseDownButton = me->button;
	mouseEvent = me;

	Window* win = me->window;
	if (win && win->rootView) {
		ViewBase* rootView = (ViewBase*)win->rootView;
		rootView->removeListener(this);
		rootView->addListener(this);
	}

	downClientPos = mkVec2(me->clientX, me->clientY);
	currentClientPos = downClientPos;
	deltaPos = mkVec2(0, 0);
	setStatus("checking");
	if (onDrag) onDrag->invoke(this);
}

void Drag::onMouseDown_byPrefer(Event* e, int button, bool cap, bool bubble) {
	MouseEvent* me = dynamic_cast<MouseEvent*>(e);
	if (!me || !me->isMouseDown) return;
	if (me->button != button) return;
	if (cap && !me->isCapture) return;
	if (bubble && !me->isBubble()) return;
	onMouseDown(e);
}

void Drag::onListenerEvent(Event* ev) {
	MouseEvent* me = dynamic_cast<MouseEvent*>(ev);
	if (!me) return;
	if (!me->isCapture) return;

	if (me->isMouseUp) {
		Window* win = me->window;
		if (win && win->rootView) {
			ViewBase* rootView = (ViewBase*)win->rootView;
			rootView->removeListener(this);
		}
		if (isDragging || isDragChecking) {
			me->stopPropagation();
			setStatus("end");
			if (onDrag) onDrag->invoke(this);
			setStatus("idle");
		}
		return;
	}

	if (me->isMouseMove) {
		if (isDragging) {
			me->stopImmediatePropagation();
		} else {
			me->stopPropagation();
		}

		Vec2 new_pos = mkVec2(me->clientX, me->clientY);
		deltaPos = new_pos.sub(currentClientPos);
		currentClientPos = new_pos;

		if (isDragChecking) {
			float dx = currentClientPos.x - downClientPos.x;
			float dy = currentClientPos.y - downClientPos.y;
			if (dx * dx + dy * dy >= moveThreshold * moveThreshold) {
				me->stopImmediatePropagation();
				setStatus("start");
				if (onDrag) onDrag->invoke(this);
				setStatus("dragging");
				return;
			}
		}

		if (isDragging) {
			if (onDrag) onDrag->invoke(this);
		}
	}
}
