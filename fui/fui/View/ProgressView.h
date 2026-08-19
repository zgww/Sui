#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/Canvas.h"

class ProgressView : public View {
public:
	float value = 0.0f;
	int trackColor = 0xffefefef;
	int fillColor = 0xff1677ff;

	ProgressView();
	void setValue(float v);
	void draw_self(Canvas* canvas) override;

	virtual const char* getClassName() const override { return "ProgressView"; }
};
