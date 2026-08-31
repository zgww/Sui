#include "Button.h"
#include "TextView.h"
#include "ImageView.h"
#include <format>
#include "Core/MouseEvent.h"

Button::Button() {
	CtorGuard(this);


	cursor = "pointer";
	direction = "row";
	justifyContent = "center";
	alignItems = "center";
	padding.setAxis(6, 12);
	radius.setAll(6);
	backgroundColor = normalBg;

	this->initInnerReact();
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

	if (auto me = dynamic_cast<MouseEnterEvent*>(ev)){
		this->backgroundColor = this->hoverBg;
		//this->labelColor = 0xff0000ff;
		this->react();
		this->invalidDraw();
	}
	if (auto me = dynamic_cast<MouseLeaveEvent*>(ev)) {
		this->backgroundColor = this->normalBg;
		//this->labelColor = 0xffffffff;
		this->react();
		this->invalidDraw();
	}
	if (auto me = dynamic_cast<MouseEvent*>(ev)){
		if (me->isClickInBubble()) {
			//if (self.clickListener){
				//self.clickListener.onEvent(me);
			//}

			if (this->onClick) {
				this->onClick->invoke(me);
			}
		}
	}
	if (auto me = dynamic_cast<ViewEvent*>(ev)) {
			// printf("Button.onEvent: %s isCapture:%d\n", Object_getClassName(ev), ve.isCapture)
	}
}


void Button::react()
{
	startInnerReact();

	auto& o = *this;
	if (src != "") {
		R(ImageView, LINE_KEY) {
			o.setSrc(src);
			o.margin.right = !src.empty() && !label.empty() ? 6.f : 0.f;
		}REND;
	}

	if (label != "") {
		R(TextView, LINE_KEY) {
			o.setText(label);
			//o.backgroundColor = 0xff0000ff;
			o.color = labelColor;
			o.setFontSize(fontSize);
		}REND;
	}

	endInnerReact();
}
