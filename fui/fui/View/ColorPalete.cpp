#include "ColorPalete.h"
#include "TextView.h"
#include "../Core/NodeLib.h"
#include "../Core/Inset.h"

static char* new_createChessBg_inMemory(int w, int h, int r, int g, int b, int a) {
	char* data = (char*)malloc(w * h * 4);
	int hw = w / 2;
	int hh = h / 2;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int i = (y * w + x) * 4;
			data[i] = r;
			data[i + 1] = g;
			data[i + 2] = b;
			data[i + 3] = (x < hw && y < hh) || (x >= hw && y >= hh) ? a : 0;
		}
	}

	return data;
}
static Ref<Image> gocChessBgImage(Canvas* canvas) {
	static Ref<Image> img;
	if (img == nullptr) {
		int w = 16;
		int h = 16;

		char* imgData = new_createChessBg_inMemory(w, h,
			128, 128, 128, 255);

		img = canvas->createImageRGBA(w, h, (const unsigned char*)imgData);

		free(imgData);
	}
	return img;
}

Vec2 ColorPalete::calcIndicatorPosInPixel() {
	Rect r = this->getContentLocalRect();
	return mkVec2(
		r.w * this->indicatorPos.x,
		r.h * (1.0 - this->indicatorPos.y)
	);
}

void ColorPalete::onEvent(Event* e) {
	if (dynamic_cast<MouseEvent*>(e)) {
		this->onMouseEvent((MouseEvent*)e);
	}
}

void ColorPalete::onMouseEvent(MouseEvent* me) {
	if (me->isMouseDown) {
		auto self = Ref(this);
		this->drag->onDrag = CLOSURE([=](Drag* d) {
			self->onDrag(d);
			});
		this->drag->onMouseDown(me);
	}
}

void ColorPalete::onDrag(Drag* drag) {
	auto& d = *drag;
	if (d.isDragging || d.isDragStart || d.isDragChecking) {
		Rect r = this->getContentLocalRect();
		Vec2 pos = this->calcIndicatorPosInPixel();

		int tox = (int)(pos.x + d.deltaPos.x);
		int toy = (int)(pos.y + d.deltaPos.y);

		{
			Rect r = this->getContentClientRect();
			tox = d.currentClientPos.x - r.x;
			toy = d.currentClientPos.y - r.y;
			printf("tox:%d, toy:%d cur:%f, %f, r:%f,%f\n",
				tox, toy,
				d.currentClientPos.x,
				d.currentClientPos.y,
				r.x, r.y);
		}

		printf("tox:%d, toy:%d\n", tox, toy);
		tox = clampInt(tox, 0, r.w);
		toy = clampInt(toy, 0, r.h);

		float xRatio = 0;
		if (r.w > 0) {
			xRatio = tox / r.w;
		}
		float yRatio = 0;
		if (r.h > 0) {
			yRatio = toy / r.h;
		}

		if (this->xDraggale) {
			this->indicatorPos.x = xRatio;
		}
		if (this->yDraggale) {
			this->indicatorPos.y = 1.0 - yRatio;
		}

		if (this->onChanged) {
			this->onChanged->invoke(this->indicatorPos);
		}

		this->invalidDraw();
	}
}

//色盘
void ColorPalete::drawCircle(Canvas* canvas, int x, int y) {
	// Marker on
	canvas->strokeWidth(2.0f);
	canvas->beginPath();
	// nvgRect(vg, -2, y - h / 2, w + 4, h)
	canvas->circle(x, y, 4);
	canvas->strokeColor(255, 255, 255, 192);
	canvas->stroke();
}

//色盘
void ColorPalete::drawMark(Canvas* canvas, int w, int y) {
	int h = 8;
	// Marker on
	canvas->strokeWidth(2.0f);
	canvas->beginPath();
	canvas->rect(-2.f, y - h / 2, w + 4.f, h);
	canvas->strokeColor(255, 255, 255, 192);
	canvas->stroke();
}

void ColorPalete::drawHue(Canvas* pcanvas, int w, int h) {
	auto& canvas = *pcanvas;
	// w = 20
	float seg = h / 6.0;
	for (int i = 0; i < 6; i++) {
		float y = i * seg;
		canvas.beginPath();
		canvas.rect(0, y, w, seg + (i == 5 ? 0 : 1));

		canvas.linearGradient(true,
			0, y,
			0, y + seg,
			mkHsla(1.0 - (i / 6.0), 1.0f, 0.55, 255).toRgbaInt(),
			mkHsla(1.0 - ((i + 1) / 6.0), 1.0f, 0.55, 255).toRgbaInt()
		);
		canvas.fill();
	}
}

//透明度
void ColorPalete::drawAlpha(Canvas* pcanvas, int w, int h) {
	auto& canvas = *pcanvas;
	canvas.beginPath();
	// nvgFillColor(vg, nvgRGBA(255, 0, 0, 255))
	// nvgRoundedRect(vg, 0, 0, w, h, 15)
	canvas.rect(0, 0, w, h);

	Image* bg = gocChessBgImage(pcanvas);
	//绘制背景
	canvas.imagePattern(
		true,
		0, 0, 16, 16, 0, bg, 1
	);
	// nvgFillPaint(vg, bp)	
	canvas.fill();


	// NVGpaint lg = nvgLinearGradient(vg, 
	// 	0.0, 0.0, 0.0, h, 
	// 	nvgRGBA(255, 255, 255, 255),
	// 	// nvgRGBA(255, 255, 255, 0),
	// 	nvgRGBA(0, 0, 0, 200),
	// )
	// nvgFillPaint(vg, lg)

	canvas.linearGradient(true,
		0.0, 0.0, 0.0, h,
		mkIntByRgba(255, 255, 255, 255),
		// nvgRGBA(255, 255, 255, 0),
		mkIntByRgba(0, 0, 0, 200)
	);
	canvas.fill();
}

//饱和度和亮度
void ColorPalete::drawSv(Canvas* pcanvas, int w, int h) {
	auto& canvas = *pcanvas;
	canvas.beginPath();
	// nvgFillColor(vg, nvgRGBA(255, 0, 0, 255))
	// nvgRoundedRect(vg, 0, 0, w, h, 15)
	canvas.rect(0, 0, w, h);

	// nvgFillColor(vg, nvgRGBA(255, 0, 0, 255))
	canvas.fillColorByInt32(this->color);
	canvas.fill();

	// NVGpaint lg = nvgLinearGradient(vg, 
	// 	0.0, 0.0, w, 0.0,
	// 	nvgRGBA(255, 255, 255, 255),
	// 	nvgRGBA(255, 255, 255, 0),
	// )
	// nvgFillPaint(vg, lg)
	canvas.linearGradient(true,
		0.0, 0.0, w, 0.0,
		mkIntByRgba(255, 255, 255, 255),
		mkIntByRgba(255, 255, 255, 0)
	);
	canvas.fill();

	{
		// NVGpaint lg = nvgLinearGradient(vg, 
		// 	0.0, 0.0, 0.0, h,
		// 	nvgRGBA(0, 0, 0, 0),
		// 	nvgRGBA(0, 0, 0, 255),
		// )
		// nvgFillPaint(vg, lg)
		canvas.linearGradient(true,
			0.0, 0.0, 0.0, h,
			mkIntByRgba(0, 0, 0, 0),
			mkIntByRgba(0, 0, 0, 255)
		);
		canvas.fill();
	}
}

void ColorPalete::draw_self(Canvas* canvas) {
	Rect r = this->getContentLocalRect();
	int w = r.w;
	int h = r.h;

	this->backgroundColor = 0xff000000;

	View::draw_self(canvas);

	if (this->kind == ("sv")) {
		this->drawSv(canvas, w, h);
	}
	if (this->kind == ("alpha")) {
		this->drawAlpha(canvas, w, h);
	}
	if (this->kind == ("hue")) {
		this->drawHue(canvas, w, h);
	}

	Vec2 indiPos = this->calcIndicatorPosInPixel();
	if (this->indicatorKind == ("rect")) {
		this->drawMark(canvas, w, indiPos.y);
	}
	if (this->indicatorKind == "circle") {
		this->drawCircle(canvas, indiPos.x, indiPos.y);
	}

}

void ColorView::fire_onChanged() {
	if (this->onChanged) {
		int color = this->hsva.toRgbaInt();
		this->onChanged->invoke(color);
	}
}

ColorView::ColorView() {
	initInnerReact();
}

// 	// this->color = c
// }
void ColorView::setColor(int c) {
	// this->color = c
	Rgba rgba = mkRgbaByInt(c);
	this->hsva = rgbaToHsva(rgba);
}

void ColorView::draw_self(Canvas* canvas) {
	View::draw_self(canvas);
}

void ColorView::react() {
	auto& o = this->startInnerReact();
	auto self = Ref(this);


	Hsva sv = mkHsva(this->hsva.h, 1.0, 1.0, 255);
	int svColor = sv.toRgbaInt();

	this->direction = ("column");
	this->alignItems = ("stretch");

	R(LayoutLinear) {
		R(ColorPalete) {
			o.indicatorPos.set(this->hsva.s, this->hsva.v);

			o.color = svColor;
			o.kind = ("sv");
			o.indicatorKind = ("circle");
			o.width = 200;
			o.height = 200;
			// o.margin.left = 100
			o.margin.right = 6;
			o.onChanged = CLOSURE([=](Vec2 ratio) {
				printf("ratio:%f,%f\n", ratio.x, ratio.y);
				this->hsva.s = ratio.x;
				this->hsva.v = ratio.y;

				this->fire_onChanged();

				// this->color = hsva.toRgbaInt()
				this->invalidReact();
				});
		} REND;
		R(ColorPalete) {
			o.indicatorPos.y = this->hsva.h / 360.0f;
			printf("hue:%f\n", this->hsva.h);

			o.kind = ("hue");
			o.width = 20;
			o.height = 200;
			o.margin.right = 6;
			o.onChanged = CLOSURE([=](Vec2 ratio) {
				this->hsva.h = ratio.y * 360.0f;
				printf("hue ratio:%f,%f. hue:%f\n", ratio.x, ratio.y, this->hsva.h);


				this->fire_onChanged();
				// this->color = this->hsva.toRgbaInt()
				this->invalidReact();
				});
		} REND;

		R(ColorPalete) {
			o.indicatorPos.y = this->hsva.a / 255.0f;

			o.kind = ("alpha");
			o.width = 20;
			o.height = 200;
			o.onChanged = CLOSURE([=](Vec2 ratio) {

				// hsla.a = ratio.y * 255.0
				// rgba.a = ratio.y * 255.0
				this->hsva.a = ratio.y * 255.0f;


				this->fire_onChanged();
				printf("alpha ratio:%f,%f. alpha:%d\n", ratio.x, ratio.y, this->hsva.a);
				// this->color = rgba.toInt()
				this->invalidReact();
				});
		} REND;
	} REND;
	R(LayoutLinear) {
		R(View) {
			o.backgroundColor = this->hsva.toRgbaInt();
			o.width = 16;
			o.height = 16;
			o.border.setAll(1, 0xff000000);
			o.padding.setAll(1);
			o.margin.setVer(6);
			o.margin.right = 6;
		} REND;
		R(LayoutLinear) {
			o.direction = ("column");
			o.alignItems = ("start");
			if (this->showHsva) {
				R(TextView, LINE_KEY) {
					std::string s = this->hsva.toString();
					o.setText(s);
				} REND;
			}
			if (this->showRgba) {
				R(TextView, LINE_KEY) {
					Rgba r = this->hsva.toRgba();
					std::string s = r.toString();
					o.setText(s);
				} REND;
			}
			if (this->showHsla) {
				R(TextView, LINE_KEY) {
					Rgba r = this->hsva.toRgba();
					Hsla hsl = rgbaToHsla(r);

					std::string s = hsl.toString();
					o.setText(s);
				} REND;
			}
		} REND;

	} REND;

	this->endInnerReact();
}
