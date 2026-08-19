#include "HoverViewEffect.h"

void HoverViewEffect::onMounted() {
	Node* p = parent;
	if (p) {
		View* v = dynamic_cast<View*>(p);
		if (v) {
			auto selfRef = this;
			v->cbOnHoverChanged = CLOSURE([=]() {
				HoverViewEffect* hve = selfRef;
				if (!hve) return;
				hve->applyEffect();
				if (hve->cbOnHoverChanged) {
					hve->cbOnHoverChanged->invoke(v);
				}
			});
			if (onClick || onHostEvent) {
				v->cbOnEvent = CLOSURE([=](Event* e) {
					HoverViewEffect* hve = selfRef;
					if (!hve) return;
					if (hve->onHostEvent) {
						if (hve->onHostEvent->invoke(e)) return;
					}
					MouseEvent* me = dynamic_cast<MouseEvent*>(e);
					if (me && me->button == 1 && me->isClickInBubble()) {
						if (hve->onClick) {
							hve->onClick->invoke(me);
						}
					}
				});
			}
		}
	}
}

void HoverViewEffect::react() {
	applyEffect();
}

void HoverViewEffect::applyEffect() {
	Node* p = parent;
	if (p) {
		View* v = dynamic_cast<View*>(p);
		if (v) {
			bool hover = v->hover;
			int bgColor = backgroundColor;
			Border* b = border.get();

			if (isActive) {
				bgColor = activeBackgroundColor;
				b = activeBorder.get();
			} else if (hover) {
				bgColor = hoverBackgroundColor;
				b = hoverBorder.get();
			}

			v->backgroundColor = bgColor;
			if (b) {
				v->border->copyFrom(b);
			}
			v->invalidDraw();
		}
	}
}

void HoverViewEffect::onUnmounting() {
	Node* p = parent;
	if (p) {
		View* v = dynamic_cast<View*>(p);
		if (v) {
			v->cbOnHoverChanged = nullptr;
			applyEffect();
		}
	}
}
