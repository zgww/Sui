#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/MouseEvent.h"
#include "Drag.h"

class Slider : public View {
public:
	float ratio = 0.5f;
	float fromValue = 0.0f;
	float toValue = 1.0f;
	Ref<View> circle{nullptr, this};
	Ref<Drag> drag{new Drag(), this};
	Ref<Closure<void(float)>> onChanged{nullptr, this};

	Slider();
	void setRatio(float v);
	float getValue();
	void setRatioByValue(float v);
	float calcToX();
	float calcToY();
	void draw_self(Canvas* canvas) override;
	void layoutContent(Frame* ctx) override;
	void onEvent(Event* ev) override;

	virtual const char* getClassName() const override { return "Slider"; }
};
