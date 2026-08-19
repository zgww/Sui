#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/MouseEvent.h"

class Checkbox : public View {
public:
	bool checked = false;
	int checkColor = 0xff1677ff;
	int uncheckedBg = 0xffffffff;
	int checkedBg = 0xff1677ff;
	int borderColor = 0xff999999;
	Ref<Closure<void(bool)>> onChanged{nullptr, this};

	Checkbox();
	void setChecked(bool v);
	void draw_self(Canvas* canvas) override;
	void onEvent(Event* ev) override;

	virtual const char* getClassName() const override { return "Checkbox"; }
};
