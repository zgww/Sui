#include "MouseEvent.h"
#include "ViewBase.h"
#include "Window.h"
#include "Node.h"
#include "Cursor.h"
#include "../Urgc/GcList.h"

bool MouseEvent::isClick() {
	if (isMouseUp) {
		float dx = clientX - mouseDownClientX;
		float dy = clientY - mouseDownClientY;
		return dx * dx + dy * dy < MouseEvent_clickOffsetThreshold * MouseEvent_clickOffsetThreshold;
	}
	return false;
}

bool MouseEvent::isClickInBubble() {
	return !isCapture && isClick();
}

bool MouseEvent::isDblClickInBubble() {
	return !isCapture && isDblClick;
}

static Ref<HoverSentive> g_hoverSentive;

HoverSentive* sinsHoverSentive() {
	if (!g_hoverSentive) {
		g_hoverSentive = new HoverSentive();
	}
	return g_hoverSentive;
}

void HoverSentive::onmousemove(ViewBase* rootView, float x, float y) {
	Ref<GcList<ViewBase>> addlist{new GcList<ViewBase>()};
	Ref<GcList<ViewBase>> dellist{new GcList<ViewBase>()};

	ViewBase* hitTestView = rootView ? rootView->hitTest(x, y) : nullptr;

	if (hitTestView) {
		printf("hitTestView:%s                      ============\n", hitTestView->name.c_str());
	}

	Ref<GcList<Node>> parents = hitTestView ? hitTestView->getAncients(true) : Ref<GcList<Node>>(new GcList<Node>());
	std::string cursor = "unset";

	for (int i = hoverings->size() - 1; i >= 0; i--) {
		ViewBase* v = hoverings->get(i);
		bool found = false;
		for (int j = 0; j < parents->size(); j++) {
			if (parents->get(j) == v) {
				found = true;
				break;
			}
		}
		if (!found) {
			printf("mouse leave:%s\n", v->name.c_str());
			dellist->push(v);
			hoverings->remove_at(i);
			v->setHover(false);
		}
	}

	for (int i = 0; i < parents->size(); i++) {
		ViewBase* v = dynamic_cast<ViewBase*>(parents->get(i));
		if (v) {
			if (v->cursor != "" && v->cursor != "unset") {
				cursor = v->cursor;
			}
			bool inHover = false;
			for (int j = 0; j < hoverings->size(); j++) {
				if (hoverings->get(j) == v) {
					inHover = true;
					break;
				}
			}
			if (!inHover) {
				printf("mouse enter:%s\n", v->name.c_str());
				addlist->push(v);
				hoverings->push(v);
				v->setHover(true);
			}
		}
	}

	Ref<MouseLeaveEvent> leave{new MouseLeaveEvent()};
	leave->name = "mouseleave";
	leave->clientX = x;
	leave->clientY = y;
	leave->button = 0;

	for (int i = 0; i < dellist->size(); i++) {
		ViewBase* v = dellist->get(i);
		v->emit(leave);
	}

	Ref<MouseEnterEvent> enter{new MouseEnterEvent()};
	enter->name = "mouseenter";
	enter->clientX = x;
	enter->clientY = y;
	enter->button = 0;

	for (int i = 0; i < addlist->size(); i++) {
		ViewBase* v = addlist->get(i);
		v->emit(enter);
	}

	Cursor_ins()->setCursor(cursor.c_str());
}

void HoverSentive::onmouseleave() {
	Ref<MouseEvent> leave{new MouseEvent()};
	leave->name = "mouseleave";
	leave->clientX = 0;
	leave->clientY = 0;
	leave->button = 0;

	int l = hoverings->size();
	for (int i = 0; i < l; i++) {
		ViewBase* v = hoverings->get(i);
		if (v) {
			v->setHover(false);
			v->emit(leave);
		}
	}
	hoverings->clear();
}

static ClickRecord g_clickRecord;

void preprocessMouseEvent(MouseEvent* ev) {
	if (ev->isClick()) {
		int64_t nowMs = time_unixMs();
		float dx = ev->clientX - (float)g_clickRecord.downX;
		float dy = ev->clientY - (float)g_clickRecord.downY;
		int64_t msThreshold = 400;
		int64_t msGap = nowMs - g_clickRecord.downTime;

		if (g_clickRecord.button == ev->button && msGap < msThreshold
			&& dx * dx < MouseEvent_clickOffsetThreshold * MouseEvent_clickOffsetThreshold
			&& dy * dy < MouseEvent_clickOffsetThreshold * MouseEvent_clickOffsetThreshold) {
			ev->isDblClick = true;
		} else {
			ev->isDblClick = false;
		}

		g_clickRecord.downX = ev->clientX;
		g_clickRecord.downY = ev->clientY;
		g_clickRecord.downTime = nowMs;
		g_clickRecord.button = ev->button;
	}
}

void propagateViewEvent(ViewEvent* event) {
	ViewBase* view = dynamic_cast<ViewBase*>(event->target.get());
	if (!view) return;

	Ref<GcList<Node>> nodes = view->getAncients(true);

	event->isCapture = true;
	for (int i = nodes->size() - 1; i >= 0; i--) {
		ViewBase* n = dynamic_cast<ViewBase*>(nodes->get(i));
		if (n) {
			event->currentTarget = n;
			n->emit(event);
			if (event->isStopPropagation) break;
		}
	}

	if (!event->isStopPropagation) {
		event->isCapture = false;
		int l = nodes->size();
		for (int i = 0; i < l; i++) {
			ViewBase* n = dynamic_cast<ViewBase*>(nodes->get(i));
			if (n) {
				event->currentTarget = n;
				n->emit(event);
				if (event->isStopPropagation) break;
			}
		}
	}

	event->currentTarget = nullptr;
}
