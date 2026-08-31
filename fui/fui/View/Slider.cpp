#include "Slider.h"
#include "../Core/Rect.h"
#include "../Core/Canvas.h"

Slider::Slider() {
	CtorGuard g(this);

	
	height = 16;
	cursor = "pointer"; 


	circle = new View();
	circle->width = 16;
	circle->height = 16;
	circle->backgroundColor = 0xffffffff;
	circle->radius.setAll(8);
	circle->border.setAll(4, 0xff1677ff);
	appendChild(circle);


	Ref<Slider> self = this;
	drag->onDrag = CLOSURE([=](Drag* d) {
		if (d->isDragging || d->isDragStart) {
			Rect r = self->get_abs_rect();
			float v = (d->currentClientPos.x - r.x) / r.w;
			v = clampFloat(v, 0.0f, 1.0f);
			self->setRatio(v);
		}
	});
	printf("drag:%p, Slider:%p\n", drag.get(), this);


	initInnerReact();
}

void Slider::setRatio(float v) {
	v = clampFloat(v, 0.0f, 1.0f);
	if (ratio != v) {
		ratio = v;
		invalidDraw();
		if (onChanged) {
			onChanged->invoke(getValue());
		}
	}
}

float Slider::getValue() {
	return (toValue - fromValue) * ratio + fromValue;
}

void Slider::setRatioByValue(float v) {
	float r = (v - fromValue) / (toValue - fromValue);
	setRatio(r);
}

float Slider::calcToX() {
	Rect vr = getViewRect();
	return vr.w * ratio - circle->width / 2.0f;
}

float Slider::calcToY() {
	auto rect = getContentRect();
	auto ret = rect.h / 2.0f - circle->frame.height / 2.0f;
	return ret;
}

void Slider::layoutContent(Frame* ctx) {
	Frame saved = *ctx;
	View::layoutContent(ctx);
	*ctx = saved;
}

void Slider::draw_self(Canvas* canvas) {
	View::draw_self(canvas);
	if (!canvas || !canvas->data) return;

	Vec2 size = getSizeWithoutMargin();
	float w = size.x;
	float h = size.y;

	float trackY = h / 2.0f - 3.0f;
	canvas->beginPath();
	canvas->roundRect(0, trackY, w, 6, 3);
	canvas->fillColorByInt32(0xffcccccc);
	canvas->fill();

	float fillW = w * ratio;
	if (fillW > 0) {
		canvas->beginPath();
		canvas->roundRect(0, trackY, fillW, 6, 3);
		canvas->fillColorByInt32(0xff1677ff);
		canvas->fill();
	}

	circle->frame.x = calcToX();
	circle->frame.y = calcToY();
}

void Slider::onEvent(Event* ev) {
	View::onEvent(ev);
	if (ev->isStopPropagation) return;

	MouseEvent* me = dynamic_cast<MouseEvent*>(ev);
	if (!me) return;

	if (me->isMouseDown && me->isBubble()) {
		drag->onMouseDown(ev);

		Rect r = get_abs_rect();
		float v = (me->clientX - r.x) / r.w;
		setRatio(v);
	}
}
