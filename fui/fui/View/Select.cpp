#include "Select.h"

Select::Select() {
	direction = "row";
	alignItems = "center";
	justifyContent = "space-between";
	cursor = "pointer";
	backgroundColor = normalBg;
	border->setAll(1, 0xffcccccc);
	radius->setAll(4);
	padding.setAxis(4, 8);
	width = 120;
	height = 28;

	labelView = new TextView();
	labelView->text = "select...";
	labelView->fontSize = 14;
	labelView->color = textColor;
	appendChild(labelView);

	arrowView = new TextView();
	arrowView->text = "v";
	arrowView->fontSize = 12;
	arrowView->color = 0xff999999;
	appendChild(arrowView);
}

void Select::appendOption(const std::string& text) {
	options.push_back(text);
	if (selectedIndex < 0 && !options.empty()) {
		setSelectedIndex(0);
	}
}

void Select::setSelectedIndex(int i) {
	if (i >= 0 && i < (int)options.size()) {
		selectedIndex = i;
		if (labelView) {
			labelView->setText(options[i]);
		}
		if (onChanged) {
			onChanged->invoke(i, options[i]);
		}
	}
}

void Select::togglePopup() {
	isActive = !isActive;
	if (arrowView) {
		arrowView->setText(isActive ? "^" : "v");
	}
	invalidDraw();
}

void Select::onEvent(Event* ev) {
	LayoutLinear::onEvent(ev);
	if (ev->isStopPropagation) return;

	MouseEvent* me = dynamic_cast<MouseEvent*>(ev);
	if (!me) return;

	if (me->isClickInBubble()) {
		togglePopup();
		me->stopPropagation();
	}
}

void Select::onHoverChanged() {
	backgroundColor = hover ? hoverBg : normalBg;
	invalidDraw();
}
