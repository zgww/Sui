#include "Switch.h"
#include "../Core/Canvas.h"

Switch::Switch() {
	CtorGuard(this);

	width = 30;
	height = 20;
	cursor = "pointer";
	radius.setAll(10);
	backgroundColor = trackOffColor;

	circle = new View();
	circle->width = circleSize;
	circle->height = circleSize;
	circle->backgroundColor = 0xffffffff;
	circle->radius.setAll(circleSize / 2.0f);
	appendChild(circle);

	initInnerReact();
}

void Switch::setChecked(bool v) {
	if (checked != v) {
		checked = v;
		backgroundColor = checked ? trackOnColor : trackOffColor;
		circle->frame.x = calcToX();
		invalidDraw();
		if (onCheckedChanged) {
			onCheckedChanged->invoke(this);
		}
	}
}

float Switch::calcToX() {
	float d = (height - circle->height) / 2.0f;
	return checked ? (width - d - circle->width) : d;
}

void Switch::draw_self(Canvas* canvas) {
	View::draw_self(canvas);
	if (!canvas || !canvas->data) return;

	circle->frame.x = calcToX();
	circle->frame.y = (height - circle->height) / 2.0f;
}

void Switch::onEvent(Event* ev) {
	View::onEvent(ev);
	if (ev->isStopPropagation) return;

	MouseEvent* me = dynamic_cast<MouseEvent*>(ev);
	if (!me) return;

	if (me->isClickInBubble()) {
		setChecked(!checked);
		me->stopPropagation();
	}
}
