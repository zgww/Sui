#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/Event.h"
#include "../Core/MouseEvent.h"
#include "ColorPalete.h"
#include <string>


class ColorPicker :public View {
public:
	// int value = 0xff000000;

	Ref<Closure< void(int newcolor)>>  onChanged{ nullptr, this };

	void fire_onChanged(int newcolor);

	ColorPicker();

	void showWindow_colorPalete();

	virtual void onEvent(Event* e) override;
	void onMouseEvent(MouseEvent* me);
};