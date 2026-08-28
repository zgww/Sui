#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/MouseEvent.h"

class Switch : public View {
public:
	bool checked = false;
	int circleSize = 14;
	int trackOnColor = 0xff1677ff;
	int trackOffColor = 0x40cccccc;
	Ref<View> circle{nullptr, this};
	Ref<Closure<void(Switch*)>> onCheckedChanged{nullptr, this};

	Switch();
	void setChecked(bool v);
	float calcToX();
	void draw_self(Canvas* canvas) override;
	void onEvent(Event* ev) override;

	virtual const char* getClassName() const override { return "Switch"; }
};
