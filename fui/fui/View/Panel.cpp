#include "Panel.h"
#include "TextView.h"

Panel::Panel() {
	direction = "column";
	alignItems = "stretch";
	padding.setAll(0);

	titleView = new TextView();
	titleView->text = title;
	titleView->fontSize = titleFontSize;
	titleView->color = titleColor;
	titleView->backgroundColor = titleBg;
	titleView->padding.setAxis(6, 8);
	titleView->cursor = "pointer";
	appendChild(titleView);

	bodyView = new View();
	bodyView->backgroundColor = 0x00000000;
	appendChild(bodyView);
}

void Panel::setTitle(const std::string& t) {
	if (title != t) {
		title = t;
		if (titleView) {
			titleView->setText(t);
		}
	}
}

void Panel::setOpen(bool v) {
	if (open != v) {
		open = v;
		if (bodyView) {
			bodyView->setVisible(open);
		}
		invalidLayout();
	}
}

void Panel::setBody(View* v) {
	if (bodyView) {
		bodyView->removeAllChildren();
		if (v) {
			bodyView->appendChild(v);
		}
	}
}

void Panel::onEvent(Event* ev) {
	LayoutLinear::onEvent(ev);
}

void Panel::onEvent_forHead(Event* e) {
	MouseEvent* me = dynamic_cast<MouseEvent*>(e);
	if (!me) return;
	if (me->isClickInBubble()) {
		setOpen(!open);
		me->stopPropagation();
	}
}
