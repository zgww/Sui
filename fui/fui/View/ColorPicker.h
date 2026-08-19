#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/Event.h"
#include "../Core/MouseEvent.h"
#include "ColorPalete.h"
#include <string>

class ColorPicker : public View {
public:
	Ref<Closure<void(int)>> onChanged{nullptr, this};

	void fire_onChanged(int newcolor);
	ColorPicker();
	void showWindow_colorPalete();
	void onEvent(Event* e) override;
	void onMouseEvent(MouseEvent* me);

	virtual const char* getClassName() const override { return "ColorPicker"; }
};
