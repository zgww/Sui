#include "View.h"
#include "Canvas.h"
#include "Color.h"

Rect View::getViewRect_baseClient() {
	Rect vr = getViewRect();
	Vec2 pos = localToWorld(vr.x, vr.y);
	Vec2 sizePos = localToWorld(vr.x + vr.w, vr.y + vr.h);
	Vec2 sz = sizePos.sub(pos);
	return mkRect(pos.x, pos.y, sz.x, sz.y);
}

bool View::_hitTestSelf(float x, float y) {
	Rect r = getViewRect_baseClient();
	return _hitTestClientRect(&r, x, y);
}

Rect View::getFrameRect() {
	return mkRect(frame.x, frame.y, frame.width, frame.height);
}

Rect View::getViewRect() {
	float w = frame.width - margin.hor();
	float h = frame.height - margin.ver();
	return mkRect(margin.left, margin.top, w, h);
}

Rect View::getContentRect() {
	return mkRect(
		margin.left + border.l.w + padding.left,
		margin.top + border.t.w + padding.top,
		maxFloat(0.0f, frame.width - margin.hor() - border.hor() - padding.hor()),
		maxFloat(0.0f, frame.height - margin.ver() - border.ver() - padding.ver())
	);
}

Vec2 View::getNonContentSize() {
	float w = margin.hor() + border.l.w + border.r.w + padding.hor();
	float h = margin.ver() + border.l.w + border.r.w + padding.ver();
	return mkVec2(w, h);
}

Inset View::getInsetOfFrameToContent() {
	float l = margin.left + border.l.w + padding.left;
	float t = margin.top + border.t.w + padding.top;
	float r = margin.right + border.r.w + padding.right;
	float b = margin.bottom + border.b.w + padding.bottom;
	return mkInset(t, r, b, l);
}

Vec2 View::getSizeWithoutMargin() {
	float w = frame.width;
	float h = frame.height;
	return mkVec2(w - margin.hor(), h - margin.ver());
}

float View::getOutWidth() {
	if (std::isnan(width)) return NAN_F;
	return width + margin.hor();
}

float View::getOutHeight() {
	if (std::isnan(height)) return NAN_F;
	return height + margin.ver();
}

float View::getOutMinWidth() {
	if (std::isnan(minWidth)) return NAN_F;
	return minWidth + margin.hor();
}

float View::getOutMinHeight() {
	if (std::isnan(minHeight)) return NAN_F;
	return minHeight + margin.ver();
}

float View::getOutMaxWidth() {
	if (std::isnan(maxWidth)) return NAN_F;
	return maxWidth + margin.hor();
}

float View::getOutMaxHeight() {
	if (std::isnan(maxHeight)) return NAN_F;
	return maxHeight + margin.ver();
}

void View::updateFrame_forSelfWidthHeight(Frame* ctx) {
	float w = getOutWidth();
	float h = getOutHeight();
	if (!std::isnan(w)) {
		ctx->clampTightWidthConstraint(w);
	}
	if (!std::isnan(h)) {
		ctx->clampTightHeightConstraint(h);
	}
	ctx->plusConstraints(
		getOutMinWidth(),
		getOutMaxWidth(),
		getOutMinHeight(),
		getOutMaxHeight()
	);
}

Rect View::getContentLocalRect() {
	return mkRect(
		margin.left + border.l.w + padding.left,
		margin.top + border.t.w + padding.top,
		maxFloat(0.0f, frame.width - margin.hor() - border.hor() - padding.hor()),
		maxFloat(0.0f, frame.height - margin.ver() - border.ver() - padding.ver())
	);
}

Rect View::getContentRect_baseViewRect() {
	return mkRect(
		border.l.w + padding.left,
		border.t.w + padding.top,
		frame.width - margin.hor() - border.hor() - padding.hor(),
		frame.height - margin.ver() - border.ver() - padding.ver()
	);
}

Vec2 View::getViewSize() {
	float w = frame.width - margin.hor();
	float h = frame.height - margin.ver();
	return mkVec2(w, h);
}

void View::layoutContent_fromOutBox(Frame* ctx) {
	Inset inset = getInsetOfFrameToContent();
	Frame contentCtx = ctx->insetByInset(inset);

	layoutContent(&contentCtx);

	*ctx = contentCtx.outsetByInset(inset);
}

void View::layoutContent(Frame* contentCtx) {
	float right = 0.0f;
	float bottom = 0.0f;

	int l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		ViewBase* v = getChildAsView(i);
		if (v) {
			v->frame.minWidth = 0;
			v->frame.minHeight = 0;
			v->frame.maxWidth = infinity;
			v->frame.maxHeight = infinity;
			v->layout(&v->frame);

			right = maxFloat(v->frame.getRight(), right);
			bottom = maxFloat(v->frame.getBottom(), bottom);
		}
	}
	contentCtx->setSize(right, bottom);
}

void View::initLayoutSize(Frame* ctx) {
	ctx->width = ctx->minWidth;
	ctx->height = ctx->minHeight;
	ctx->setSize_ifAnyTight();
}

bool View::callCbLayout(Frame* ctx) {
	if (cb && cb->cbLayout(this, ctx)) {
		return true;
	}
	return false;
}

void View::layout(Frame* ctx) {
	updateFrame_forSelfWidthHeight(ctx);
	initLayoutSize(ctx);

	if (cb && cb->cbLayout(this, ctx)) {
		return;
	}

	layoutContent_fromOutBox(ctx);

	ctx->saveConstraints();
}

void View::updateFrame_byContentCtx(Frame* targetCtx, Frame* contentCtx) {
	if (targetCtx->isTight()) {
		return;
	}
	Vec2 ncSize = getNonContentSize();
	targetCtx->setSize(
		contentCtx->width + ncSize.x,
		contentCtx->height + ncSize.y
	);
}

Frame View::makeContentLayoutCtx(Frame* ctx) {
	Frame ret = mkFrame();
	Vec2 ncSize = getNonContentSize();
	ret.setMinWidth(ctx->minWidth - ncSize.x);
	if (ctx->maxWidth != infinity) {
		ret.maxWidth = ctx->maxWidth - ncSize.x;
	}
	ret.setMinHeight(ctx->minHeight - ncSize.y);
	if (ctx->maxHeight != infinity) {
		ret.maxHeight = ctx->maxHeight - ncSize.y;
	}
	ret.setSize_ifAnyTight();
	return ret;
}

Rect View::get_abs_rect() {
	return ViewBase::get_abs_rect();
}

Rect View::getContentClientRect() {
	Rect lr = getContentLocalRect();
	Vec2 pos = localToWorld(lr.x, lr.y);
	lr.x = pos.x;
	lr.y = pos.y;
	return lr;
}

void View::clip(Canvas* canvas) {
	float w = frame.width - margin.hor();
	float h = frame.height - margin.ver();
	canvas->intersectScissor(0.0f, 0.0f, w, h);
}

void View::draw(Canvas* canvas) {
	if (cb && cb->cbDraw(this, canvas)) {
		return;
	}
	canvas->save();

	float l = frame.x;
	float t = frame.y;

	canvas->translate(l, t);
	canvas->transform(transform);
	canvas->currentTransform(&_world_transform);

	canvas->translate(margin.left, margin.top);

	bool need_draw = true;

	if (needClip && need_draw) {
		clip(canvas);
	}

	{
		if (need_draw) {
			if (cb && cb->cbDrawSelf(this, canvas)) {
			} else {
				draw_self(canvas);
				if (cb) {
					cb->afterDrawSelf(this, canvas);
				}
			}
		}

		canvas->save();
		canvas->translate(
			padding.left + border.l.w,
			padding.top + border.t.w
		);
		draw_children(canvas);
		canvas->restore();

		if (need_draw) {
			drawSelfBorder(canvas);
		}
	}

	canvas->restore();
}

void View::drawSelfBorder(Canvas* canvas) {
	int tc = border.t.color;
	int rc = border.r.color;
	int bc = border.b.color;
	int lc = border.l.color;

	if (colorGetA(tc) > 0 || colorGetA(rc) > 0 || colorGetA(bc) > 0 || colorGetA(lc) > 0) {
		Rect viewRect = getViewRect();
		float w = viewRect.w;
		float h = viewRect.h;

		if (border.isAllHasWidth()) {
			canvas->beginPath();
			if (border.t.w <= 1.001f) {
				canvas->strokeWidth(1.0f);
				canvas->roundRect(0.5f, 0.5f, w - 0.5f, h - 0.5f, radius.tl);
			} else {
				canvas->roundRect(0.5f, 0.5f, w - 0.5f, h - 0.5f, radius.tl);
				canvas->strokeWidth(border.t.w);
			}
			canvas->strokeColorByInt32(border.t.color);
			canvas->stroke();
		} else {
			if (border.t.w > 0.0f) {
				canvas->beginPath();
				canvas->moveTo(0.5f, 0.5f);
				canvas->lineTo(w + 0.5f, 0.5f);
				canvas->strokeWidth(border.t.w);
				canvas->strokeColorByInt32(border.t.color);
				canvas->stroke();
			}
			if (border.r.w > 0.0f) {
				canvas->beginPath();
				canvas->moveTo(w + 0.5f, 0.5f);
				canvas->lineTo(w + 0.5f, h + 0.5f);
				canvas->strokeWidth(border.r.w);
				canvas->strokeColorByInt32(border.r.color);
				canvas->stroke();
			}
			if (border.b.w > 0.0f) {
				canvas->beginPath();
				canvas->moveTo(0.5f, h + 0.5f);
				canvas->lineTo(w + 0.5f, h + 0.5f);
				canvas->strokeWidth(border.b.w);
				canvas->strokeColorByInt32(border.b.color);
				canvas->stroke();
			}
			if (border.l.w > 0.0f) {
				canvas->beginPath();
				canvas->moveTo(0.5f, 0.5f);
				canvas->lineTo(0.5f, h + 0.5f);
				canvas->strokeWidth(border.l.w);
				canvas->strokeColorByInt32(border.l.color);
				canvas->stroke();
			}
		}
	}
}

void View::draw_self(Canvas* canvas) {
	float bga = (float)colorGetA(backgroundColor);
	if (bga > 0.0f) {
		Vec2 size = getSizeWithoutMargin();
		float w = size.x;
		float h = size.y;
		canvas->beginPath();
		canvas->roundRect(0.0f, 0.0f, w, h, radius.tl);
		canvas->fillColorByInt32(backgroundColor);
		canvas->fill();
	}
}
