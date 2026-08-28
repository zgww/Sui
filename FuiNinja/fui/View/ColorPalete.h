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


/// 颜色盘
class ColorPalete :public View {
public:
	// 都是归一化的0-1值. 原点在左下角
	Vec2 indicatorPos = mkVec2(0, 0);
	Ref<Drag> drag{ new Drag() , this};

		//sv的主色
	int color = 0xffff0000;

	bool xDraggale = true;
	bool yDraggale = true;
		//sv|alpha|hue
	std::string kind = ("sv");
		// circle|rect
	std::string indicatorKind = ("rect");
	// bool rect = false;
	Ref<Closure<void(Vec2 ratio) >> onChanged{ nullptr, this };

	Vec2 calcIndicatorPosInPixel();

	void onEvent(Event* e);
	void onMouseEvent(MouseEvent* me);
	void onDrag(Drag* drag);

	//色盘
	void drawCircle(Canvas* canvas, int x, int y);
	//色盘
	void drawMark(Canvas* canvas, int w, int y);
	void drawHue(Canvas* pcanvas, int w, int h);
	//透明度
	void drawAlpha(Canvas* pcanvas, int w, int h);
	//饱和度和亮度
	void drawSv(Canvas* pcanvas, int w, int h);
	void draw_self(Canvas* canvas);
};

class ColorView : public LayoutLinear {
public:

	// int color = 0;
	Hsva hsva = mkHsva(0.0, 1.0, 1.0, 255);
	bool showRgba = true;
	bool showHsva = false;
	bool showHsla = false;

	Ref<Closure< void(int newcolor)>> onChanged{ nullptr, this };

	void fire_onChanged();
	ColorView();
	// void ctor(){
	// 	super.ctor()

	// 	// Hsla sv = mkHsla(0.5, 0.5, 0.5, 255)

	// 	// this->color = c
	// }
	void setColor(int c);
	void draw_self(Canvas* canvas);
	void react();
};
