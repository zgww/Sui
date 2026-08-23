#include "ColorPicker.h"
#include "../Core/Window.h"
#include "../Layout/LayoutLinear.h"
#include "../Core/NodeLib.h"


void ColorPicker::fire_onChanged(int newcolor) {
	if (this->onChanged) {
		this->onChanged->invoke(newcolor);
	}
}

ColorPicker::ColorPicker() {
	this->width = 14;
	this->height = 14;
	this->border.setAll(2, 0xffffffff);
	this->backgroundColor = 0xff00ff00;

	initInnerReact();
}

void ColorPicker::showWindow_colorPalete() {
	auto self = Ref(this);

	auto root = Ref(new LayoutLinear());
	RINS(root.get()) {

		o.direction = ("column");
		o.alignItems = ("center");
		// o.justifyContent.set("center")
		o.padding.setAll(8);

		// mkTextView(o, 0).{
		// 	o.setText(str("你好"))
		// }
		R(ColorView) {
			if (o.created) {
				o.hsva = mkHsva_byInt(this->backgroundColor);
			}
			o.onChanged = CLOSURE([=](int c) {
				self->backgroundColor = c;
				self->fire_onChanged(c);
				self->invalidDraw();
				});
		} REND;
	} REND;

	auto win = Ref(new Window());
	win->setRootView(root);
	win->setOwner(this->getWindow());
	win->setTitle("ColorPicker");
	win->setSize(300, 300);
	win->moveToCenter();
	win->show();
}

void ColorPicker::onEvent(Event* e) {
	if (dynamic_cast<MouseEvent*>(e)) {
		this->onMouseEvent((MouseEvent*)e);
	}
}


void ColorPicker::onMouseEvent(MouseEvent* me) {
	if (me->isClickInBubble()) {
		this->showWindow_colorPalete();
		// Toast_make("HI")
		// this->drag.onDrag = ^void (Drag *d){
		// 	this->onDrag(d)
		// }
		// this->drag.onMouseDown(me)
	}
}
