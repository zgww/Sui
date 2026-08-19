#include "Button.h"
#include "TextView.h"
#include "ImageView.h"
#include <format>

Button::Button() {
	cursor = "pointer";
	direction = "row";
	justifyContent = "center";
	alignItems = "center";
	padding.setAxis(6, 12);
	radius->setAll(6);
	backgroundColor = normalBg;


	this->react();
}


void Button::setLabel(const std::string& l) {
	if (label != l) {
		label = l;
	}
}

void Button::setSrc(const std::string& s) {
	if (src != s) {
		src = s;
	}

}

void Button::setFontSize(float s) {
	if (fontSize != s) {
		fontSize = s;
	}
}

void Button::setLabelColor(int c) {
	if (labelColor != c) {
		labelColor = c;
	}
}

void Button::setNormalBg(int c) {
	normalBg = c;
	if (!hover) {
		backgroundColor = normalBg;
		invalidDraw();
	}
}

void Button::onEvent(Event* ev) {
	LayoutLinear::onEvent(ev);
	if (ev->isStopPropagation) return;

	MouseEvent* me = dynamic_cast<MouseEvent*>(ev);
	if (!me) return;

	if (me->isClickInBubble()) {
		backgroundColor = activeBg;
		invalidDraw();
		if (onClick) {
			onClick->invoke(me);
		}
	} else if (me->isMouseDown && me->isBubble()) {
		backgroundColor = activeBg;
		invalidDraw();
	}
}

void Button::onHoverChanged() {
	if (hover) {
		backgroundColor = hoverBg;
	} else {
		backgroundColor = normalBg;
	}
	invalidDraw();
}

void Button::react()
{
	auto o = this;
	if (src != "") {
		R(ImageView, LINE_KEY) {
			o->setSrc(src);
			o->margin.right = !src.empty() && !label.empty() ? 6 : 0;
		}REND;
	}

	if (label != "") {
		R(TextView, LINE_KEY) {
			o->setText(label);
			o->color = labelColor;
			o->setFontSize(fontSize);
		}REND;
	}
}
