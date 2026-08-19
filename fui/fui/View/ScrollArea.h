#pragma once

#include "../Core/Predef.h"
#include "../Layout/LayoutLinear.h"
#include "../Core/Vec2.h"
#include "../Core/Frame.h"
#include "../Core/MouseEvent.h"
#include "../Core/View.h"

class ScrollArea : public LayoutLinear {
public:
	float scrollLeft = 0.0f;
	float scrollTop = 0.0f;
	float scrollbarSize = 8.0f;
	int scrollbarBg = 0x20000000;
	int scrollbarBarBg = 0x80000000;
	std::string scrollDirection = "vertical";

	Frame contentCtx;
	bool useMaxWidthConstraint = false;
	bool useMinWidthConstraint = true;

	Ref<Closure<void(ScrollArea*)>> onScrollChanged{nullptr, this};

	ScrollArea();
	Vec2 calcScrollSize();
	void clampScrollOffset();
	void fireScrollChanged();
	void onEvent(Event* ev) override;
	void onWheelEvent(WheelEvent* e);
	void draw_children(Canvas* canvas) override;
	void layout(Frame* ctx) override;

	float getVRate();
	float getHRate();
	float getVLength(float fullSize);
	float getVPos(float fullSize);
	float getHLength(float fullSize);
	float getHPos(float fullSize);

	virtual const char* getClassName() const override { return "ScrollArea"; }
};
