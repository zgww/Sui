#include "ProgressView.h"

ProgressView::ProgressView() {
	backgroundColor = trackColor;
	width = 200;
	height = 6;
	radius.setAll(3);
}

void ProgressView::setValue(float v) {
	v = clampFloat(v, 0.0f, 1.0f);
	if (value != v) {
		value = v;
		invalidDraw();
	}
}

void ProgressView::draw_self(Canvas* canvas) {
	View::draw_self(canvas);
	if (!canvas || !canvas->data) return;

	Vec2 size = getSizeWithoutMargin();
	float w = size.x;
	float h = size.y;

	float fillW = w * value;
	if (fillW > 0) {
		canvas->beginPath();
		canvas->roundRect(0, 0, fillW, h, radius.tl);
		canvas->fillColorByInt32(fillColor);
		canvas->fill();
	}
}
