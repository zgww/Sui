#include "ColorPicker.h"
#include "../Core/Window.h"
#include "../Layout/LayoutLinear.h"
#include "../Core/NodeLib.h"

void ColorPicker::fire_onChanged(int newcolor) {
	if (onChanged) {
		onChanged->invoke(newcolor);
	}
}

ColorPicker::ColorPicker() {
	width = 14;
	height = 14;
	border->setAll(2, 0xffffffff);
	backgroundColor = 0xff00ff00;
}

void ColorPicker::showWindow_colorPalete() {
	Ref<Window> win{new Window()};
	win->initData();

	Ref<LayoutLinear> root{new LayoutLinear()};
	root->direction = "column";
	root->alignItems = "center";
	root->padding.setAll(8);
	win->setRootView(root.get());

	ColorView* cv = gocNode<ColorView>(root.get(), 0);
	if (cv) {
		cv->hsva = mkHsva_byInt(backgroundColor);
		auto selfRef = this;
		auto winRef = win;
		cv->onChanged = CLOSURE([=](int c) {
			ColorPicker* self = selfRef;
			if (!self) return;
			self->backgroundColor = c;
			self->fire_onChanged(c);
			self->invalidDraw();
		});
	}

	win->setOwner(getWindow());
	win->setTitle("ColorPicker");
	win->setSize(300, 300);
	win->moveToCenter();
	win->show();
}

void ColorPicker::onEvent(Event* e) {
	View::onEvent(e);
	if (e->isStopPropagation) return;
	MouseEvent* me = dynamic_cast<MouseEvent*>(e);
	if (me) {
		onMouseEvent(me);
	}
}

void ColorPicker::onMouseEvent(MouseEvent* me) {
	if (me->isClickInBubble()) {
		showWindow_colorPalete();
	}
}
