#include "Panel.h"
#include "TextView.h"
#include "../View/HoverViewEffect.h"

Panel::Panel() {
	CtorGuard g(this);

	direction = "column";
	alignItems = "stretch";
	padding.setAll(0);

	//titleView = new TextView();
	//titleView->text = title;
	//titleView->fontSize = titleFontSize;
	//titleView->color = titleColor;
	//titleView->backgroundColor = titleBg;
	//titleView->padding.setAxis(6, 8);
	//titleView->cursor = "pointer";
	//appendChild(titleView);

	//bodyView = new View();
	//bodyView->backgroundColor = 0x00000000;
	//appendChild(bodyView);


	initInnerReact();
}

void Panel::setTitle(const std::string& t) {
	if (title != t) {
		title = t;
	}
}

void Panel::setOpen(bool v) {
	if (open != v) {
		open = v;
		invalidReact();
	}
}


void Panel::onEvent(Event* ev) {
	LayoutLinear::onEvent(ev);
}

void Panel::react()
{
	auto& o = *this;
	startInnerReact();

	R(LayoutLinear) {
		o.direction = "row";
		//o.backgroundColor = 0xff0000ff;

		R(HoverViewEffect) {
			auto self = Ref(this);
			o.onClick = CLOSURE([=](MouseEvent* e) {
				self->setOpen(!self->open);
				});
		} REND;

		R(TextView) {
			std::string text = open ? "V " : "> ";
			if (this->title != "") {
				text += this->title;
				o.setColor(this->titleColor);
				o.setFontSize(this->titleFontSize);
			}
			o.setText(text);
		} REND;
		if (this->title == "") {
			o.placeKidsOfSlot(this->gocOutKids(), "head");
		}
	}REND;

	if (open) {
		o.placeKidsOfSlot(this->gocOutKids(), "");
	}
	endInnerReact();
}

//void Panel::onEvent_forHead(Event* e) {
//	MouseEvent* me = dynamic_cast<MouseEvent*>(e);
//	if (!me) return;
//	if (me->isClickInBubble()) {
//		setOpen(!open);
//		me->stopPropagation();
//	}
//}
