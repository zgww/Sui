#include "ScrollArea.h"
#include "../Core/Canvas.h"

ScrollArea::ScrollArea() {
	direction = "column";
	alignItems = "start";
	needClip = true;
}

Vec2 ScrollArea::calcScrollSize() {
	return mkVec2(contentCtx.width, contentCtx.height);
}

void ScrollArea::clampScrollOffset() {
	Vec2 scrollSize = calcScrollSize();
	Rect clientRect = getContentLocalRect();
	float clientW = clientRect.w;
	float clientH = clientRect.h;

	float maxScrollX = maxFloat(0.0f, scrollSize.x - clientW);
	float maxScrollY = maxFloat(0.0f, scrollSize.y - clientH);
	scrollLeft = clampFloat(scrollLeft, 0.0f, maxScrollX);
	scrollTop = clampFloat(scrollTop, 0.0f, maxScrollY);
}

void ScrollArea::fireScrollChanged() {
	if (onScrollChanged) {
		onScrollChanged->invoke(this);
	}
}

float ScrollArea::getVRate() {
	Rect clientRect = getContentLocalRect();
	return minFloat(1.0f, clientRect.h / maxFloat(1.0f, contentCtx.height));
}

float ScrollArea::getHRate() {
	Rect clientRect = getContentLocalRect();
	return minFloat(1.0f, clientRect.w / maxFloat(1.0f, contentCtx.width));
}

float ScrollArea::getVLength(float fullSize) {
	return maxFloat(30.0f, fullSize * getVRate());
}

float ScrollArea::getVPos(float fullSize) {
	float trackSize = fullSize - getVLength(fullSize);
	if (trackSize <= 0) return 0;
	return trackSize * (scrollTop / maxFloat(1.0f, contentCtx.height - getContentLocalRect().h));
}

float ScrollArea::getHLength(float fullSize) {
	return maxFloat(30.0f, fullSize * getHRate());
}

float ScrollArea::getHPos(float fullSize) {
	float trackSize = fullSize - getHLength(fullSize);
	if (trackSize <= 0) return 0;
	return trackSize * (scrollLeft / maxFloat(1.0f, contentCtx.width - getContentLocalRect().w));
}

void ScrollArea::onWheelEvent(WheelEvent* e) {
	bool isHor = e->shift;
	float delta = isHor ? e->deltaX : e->deltaY;
	Rect clientRect = getContentLocalRect();

	if (!isHor) {
		float maxStep = clientRect.h / 2.0f;
		delta = clampFloat(delta, -maxStep, maxStep);
		scrollTop -= delta;
	} else {
		float maxStep = clientRect.w / 2.0f;
		delta = clampFloat(delta, -maxStep, maxStep);
		scrollLeft -= delta;
	}

	clampScrollOffset();
	fireScrollChanged();
	invalidLayout();
}

void ScrollArea::onEvent(Event* ev) {
	LayoutLinear::onEvent(ev);
	if (ev->isStopPropagation) return;

	WheelEvent* we = dynamic_cast<WheelEvent*>(ev);
	if (we && we->isBubble()) {
		onWheelEvent(we);
	}
}

void ScrollArea::draw_children(Canvas* canvas) {
	Rect contentRect = getContentLocalRect();

	if (scrollDirection == "vertical" || scrollDirection == "both") {
		float rate = getVRate();
		if (rate < 1.0f) {
			float barX = contentRect.x + contentRect.w - scrollbarSize;
			float barY = contentRect.y;
			float barH = contentRect.h;
			canvas->beginPath();
			canvas->roundRect(barX, barY, scrollbarSize, barH, scrollbarSize / 2);
			canvas->fillColorByInt32(scrollbarBg);
			canvas->fill();

			float thumbH = getVLength(barH);
			float thumbY = barY + getVPos(barH);
			canvas->beginPath();
			canvas->roundRect(barX, thumbY, scrollbarSize, thumbH, scrollbarSize / 2);
			canvas->fillColorByInt32(scrollbarBarBg);
			canvas->fill();
		}
	}

	canvas->save();
	clip(canvas);
	canvas->translate(-scrollLeft, -scrollTop);
	View::draw_children(canvas);
	canvas->restore();
}

void ScrollArea::layout(Frame* ctx) {
	updateFrame_forSelfWidthHeight(ctx);
	ctx->setSize_ifAnyTight();

	Frame contentLayoutCtx = makeContentLayoutCtx(ctx);
	contentCtx = contentLayoutCtx;

	if (useMinWidthConstraint) {
		contentCtx.minWidth = contentLayoutCtx.minWidth;
	}
	if (useMaxWidthConstraint) {
		contentCtx.maxWidth = contentLayoutCtx.maxWidth;
	}

	View::layoutContent(&contentCtx);

	Inset inset = getInsetOfFrameToContent();
	ctx->width = contentCtx.width + inset.hor();
	ctx->height = contentCtx.height + inset.ver();

	clampScrollOffset();
	ctx->saveConstraints();
}
