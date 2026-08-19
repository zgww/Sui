#include "Checkbox.h"
#include "../Core/Canvas.h"

Checkbox::Checkbox() {
	width = 16;
	height = 16;
	cursor = "pointer";
	radius->setAll(3);
	border->setAll(1, 0xff999999);
	backgroundColor = uncheckedBg;
}

void Checkbox::setChecked(bool v) {
	if (checked != v) {
		checked = v;
		backgroundColor = checked ? checkedBg : uncheckedBg;
		border->setAll(1, checked ? 0xff1677ff : 0xff999999);
		invalidDraw();
		if (onChanged) {
			onChanged->invoke(checked);
		}
	}
}

void Checkbox::draw_self(Canvas* canvas) {
	View::draw_self(canvas);
	if (!canvas || !canvas->data) return;

	Vec2 size = getSizeWithoutMargin();
	float w = size.x;
	float h = size.y;

	if (checked) {
		float cx = w / 2.0f;
		float cy = h / 2.0f;
		canvas->beginPath();
		canvas->moveTo(w * 0.2f, h * 0.5f);
		canvas->lineTo(w * 0.4f, h * 0.7f);
		canvas->lineTo(w * 0.8f, h * 0.3f);
		canvas->strokeColorByInt32(0xffffffff);
		canvas->strokeWidth(2);
		canvas->stroke();
	}
}

void Checkbox::onEvent(Event* ev) {
	View::onEvent(ev);
	if (ev->isStopPropagation) return;

	MouseEvent* me = dynamic_cast<MouseEvent*>(ev);
	if (!me) return;

	if (me->isClickInBubble()) {
		setChecked(!checked);
		me->stopPropagation();
	}
}
