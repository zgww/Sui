#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/Vec2.h"
#include "../Core/Rect.h"
#include "../Core/Color.h"
#include "../Core/Canvas.h"
#include "../Core/Event.h"
#include "../Core/MouseEvent.h"
#include "../Layout/LayoutLinear.h"
#include "Drag.h"
#include <string>

class ColorPalete : public View {
public:
	Vec2 indicatorPos;
	Ref<Drag> drag{new Drag(), this};
	int color = 0xffff0000;
	bool xDraggale = true;
	bool yDraggale = true;
	std::string kind = "sv";
	std::string indicatorKind = "rect";
	Ref<Closure<void(Vec2)>> onChanged{nullptr, this};

	Vec2 calcIndicatorPosInPixel();
	void onEvent(Event* e) override;
	void onMouseEvent(MouseEvent* me);
	void onDrag(Drag* d);
	void drawCircle(Canvas* canvas, float x, float y);
	void drawMark(Canvas* canvas, float w, float y);
	void drawHue(Canvas* canvas, float w, float h);
	void drawAlpha(Canvas* canvas, float w, float h);
	void drawSv(Canvas* canvas, float w, float h);
	void draw_self(Canvas* canvas) override;

	virtual const char* getClassName() const override { return "ColorPalete"; }
};

class ColorView : public LayoutLinear {
public:
	Hsva hsva;
	bool showRgba = true;
	bool showHsva = false;
	bool showHsla = false;
	Ref<Closure<void(int)>> onChanged{nullptr, this};

	void fire_onChanged();
	void setColor(int c);
	void react() override;
	void draw_self(Canvas* canvas) override;

	virtual const char* getClassName() const override { return "ColorView"; }
};
