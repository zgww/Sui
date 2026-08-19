#include "ColorPalete.h"
#include "TextView.h"
#include "../Core/NodeLib.h"
#include "../Core/Inset.h"

static unsigned char* createChessBgData(int w, int h, int r, int g, int b, int a) {
	unsigned char* data = (unsigned char*)malloc(w * h * 4);
	int hw = w / 2;
	int hh = h / 2;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int i = (y * w + x) * 4;
			data[i] = (unsigned char)r;
			data[i + 1] = (unsigned char)g;
			data[i + 2] = (unsigned char)b;
			data[i + 3] = (unsigned char)((x < hw && y < hh) || (x >= hw && y >= hh) ? a : 0);
		}
	}
	return data;
}

static Image* gocChessBgImage(Canvas* canvas) {
	static Ref<Image> img;
	if (img == nullptr) {
		int w = 16, h = 16;
		unsigned char* imgData = createChessBgData(w, h, 128, 128, 128, 255);
		img = canvas->createImageRGBA(w, h, imgData);
		free(imgData);
	}
	return img.get();
}

Vec2 ColorPalete::calcIndicatorPosInPixel() {
	Rect r = getContentLocalRect();
	return Vec2(r.w * indicatorPos.x, r.h * (1.0f - indicatorPos.y));
}

void ColorPalete::onEvent(Event* e) {
	View::onEvent(e);
	if (e->isStopPropagation) return;
	MouseEvent* me = dynamic_cast<MouseEvent*>(e);
	if (me) {
		onMouseEvent(me);
	}
}

void ColorPalete::onMouseEvent(MouseEvent* me) {
	if (me->isMouseDown) {
		auto selfRef = this;
		drag->onDrag = CLOSURE([=](Drag* d) {
			ColorPalete* self = selfRef;
			if (!self) return;
			self->onDrag(d);
		});
		drag->onMouseDown(me);
	}
}

void ColorPalete::onDrag(Drag* d) {
	if (d->isDragging || d->isDragStart || d->isDragChecking) {
		Rect r = getContentLocalRect();
		Rect cr = getContentClientRect();
		float tox = d->currentClientPos.x - cr.x;
		float toy = d->currentClientPos.y - cr.y;
		tox = clampFloat(tox, 0, r.w);
		toy = clampFloat(toy, 0, r.h);

		float xRatio = r.w > 0 ? tox / r.w : 0;
		float yRatio = r.h > 0 ? toy / r.h : 0;

		if (xDraggale) indicatorPos.x = xRatio;
		if (yDraggale) indicatorPos.y = 1.0f - yRatio;

		if (onChanged) {
			onChanged->invoke(indicatorPos);
		}
		invalidDraw();
	}
}

void ColorPalete::drawCircle(Canvas* canvas, float x, float y) {
	canvas->strokeWidth(2.0f);
	canvas->beginPath();
	canvas->circle(x, y, 4);
	canvas->strokeColor(255, 255, 255, 192);
	canvas->stroke();
}

void ColorPalete::drawMark(Canvas* canvas, float w, float y) {
	float h = 8;
	canvas->strokeWidth(2.0f);
	canvas->beginPath();
	canvas->rect(-2.0f, y - h / 2, w + 4.0f, h);
	canvas->strokeColor(255, 255, 255, 192);
	canvas->stroke();
}

void ColorPalete::drawHue(Canvas* canvas, float w, float h) {
	float seg = h / 6.0f;
	for (int i = 0; i < 6; i++) {
		float y = i * seg;
		canvas->beginPath();
		canvas->rect(0, y, w, seg + (i == 5 ? 0 : 1));
		canvas->linearGradient(true,
			0, y, 0, y + seg,
			mkHsla(1.0f - (i / 6.0f), 1.0f, 0.55f, 255).toRgbaInt(),
			mkHsla(1.0f - ((i + 1) / 6.0f), 1.0f, 0.55f, 255).toRgbaInt());
		canvas->fill();
	}
}

void ColorPalete::drawAlpha(Canvas* canvas, float w, float h) {
	canvas->beginPath();
	canvas->rect(0, 0, w, h);
	Image* bg = gocChessBgImage(canvas);
	canvas->imagePattern(true, 0, 0, 16, 16, 0, bg, 1);
	canvas->fill();

	canvas->linearGradient(true,
		0, 0, 0, h,
		mkIntByRgba(255, 255, 255, 255),
		mkIntByRgba(0, 0, 0, 200));
	canvas->fill();
}

void ColorPalete::drawSv(Canvas* canvas, float w, float h) {
	canvas->beginPath();
	canvas->rect(0, 0, w, h);
	canvas->fillColorByInt32(color);
	canvas->fill();

	canvas->linearGradient(true,
		0, 0, w, 0,
		mkIntByRgba(255, 255, 255, 255),
		mkIntByRgba(255, 255, 255, 0));
	canvas->fill();

	canvas->linearGradient(true,
		0, 0, 0, h,
		mkIntByRgba(0, 0, 0, 0),
		mkIntByRgba(0, 0, 0, 255));
	canvas->fill();
}

void ColorPalete::draw_self(Canvas* canvas) {
	Rect r = getContentLocalRect();
	float w = r.w;
	float h = r.h;
	backgroundColor = 0xff000000;
	View::draw_self(canvas);

	if (kind == "sv") drawSv(canvas, w, h);
	if (kind == "alpha") drawAlpha(canvas, w, h);
	if (kind == "hue") drawHue(canvas, w, h);

	Vec2 indiPos = calcIndicatorPosInPixel();
	if (indicatorKind == "rect") drawMark(canvas, w, indiPos.y);
	if (indicatorKind == "circle") drawCircle(canvas, indiPos.x, indiPos.y);
}

void ColorView::fire_onChanged() {
	if (onChanged) {
		int c = hsva.toRgbaInt();
		onChanged->invoke(c);
	}
}

void ColorView::setColor(int c) {
	Rgba rgba = mkRgbaByInt(c);
	hsva = rgbaToHsva(rgba);
}

void ColorView::draw_self(Canvas* canvas) {
	LayoutLinear::draw_self(canvas);
}

void ColorView::react() {
	startInnerReact();
	ColorView* o = this;

	Hsva sv = mkHsva(hsva.h, 1.0f, 1.0f, 255);
	int svColor = sv.toRgbaInt();

	direction = "column";
	alignItems = "stretch";

	LayoutLinear* row1 = gocLayoutLinear(o, 0);
	if (row1) {
		row1->direction = "row";

		ColorPalete* svPal = gocNode<ColorPalete>(row1, 1);
		if (svPal) {
			svPal->indicatorPos.x = hsva.s;
			svPal->indicatorPos.y = hsva.v;
			svPal->color = svColor;
			svPal->kind = "sv";
			svPal->indicatorKind = "circle";
			svPal->width = 200;
			svPal->height = 200;
			svPal->margin.right = 6;
			auto selfRef = this;
			svPal->onChanged = CLOSURE([=](Vec2 ratio) {
				ColorView* self = selfRef;
				if (!self) return;
				self->hsva.s = ratio.x;
				self->hsva.v = ratio.y;
				self->fire_onChanged();
				self->invalidReact();
			});
		}

		ColorPalete* huePal = gocNode<ColorPalete>(row1, 2);
		if (huePal) {
			huePal->indicatorPos.y = hsva.h / 360.0f;
			huePal->kind = "hue";
			huePal->width = 20;
			huePal->height = 200;
			huePal->margin.right = 6;
			auto selfRef = this;
			huePal->onChanged = CLOSURE([=](Vec2 ratio) {
				ColorView* self = selfRef;
				if (!self) return;
				self->hsva.h = ratio.y * 360.0f;
				self->fire_onChanged();
				self->invalidReact();
			});
		}

		ColorPalete* alphaPal = gocNode<ColorPalete>(row1, 3);
		if (alphaPal) {
			alphaPal->indicatorPos.y = hsva.a / 255.0f;
			alphaPal->kind = "alpha";
			alphaPal->width = 20;
			alphaPal->height = 200;
			auto selfRef = this;
			alphaPal->onChanged = CLOSURE([=](Vec2 ratio) {
				ColorView* self = selfRef;
				if (!self) return;
				self->hsva.a = ratio.y * 255.0f;
				self->fire_onChanged();
				self->invalidReact();
			});
		}
	}

	LayoutLinear* row2 = gocLayoutLinear(o, 1);
	if (row2) {
		row2->direction = "row";

		View* colorBox = gocView(row2, 0);
		if (colorBox) {
			colorBox->backgroundColor = hsva.toRgbaInt();
			colorBox->width = 16;
			colorBox->height = 16;
			colorBox->border->setAll(1, 0xff000000);
			colorBox->padding.setAll(1);
			colorBox->margin.setVer(6);
			colorBox->margin.right = 6;
		}

		LayoutLinear* infoCol = gocLayoutLinear(row2, 1);
		if (infoCol) {
			infoCol->direction = "column";
			infoCol->alignItems = "start";

			if (showHsva) {
				TextView* tv = gocTextView(infoCol, 0);
				if (tv) tv->setText(hsva.toString());
			}
			if (showRgba) {
				TextView* tv = gocTextView(infoCol, 1);
				if (tv) {
					Rgba r = hsva.toRgba();
					tv->setText(r.toString());
				}
			}
			if (showHsla) {
				TextView* tv = gocTextView(infoCol, 2);
				if (tv) {
					Rgba r = hsva.toRgba();
					Hsla hsl = rgbaToHsla(r);
					tv->setText(hsl.toString());
				}
			}
		}
	}

	endInnerReact();
}
