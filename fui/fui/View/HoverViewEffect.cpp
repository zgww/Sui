#include "HoverViewEffect.h"

#include <rttr/registration>

void HoverViewEffect::onMounted() {
	Node* p = parent;
	if (p) {
		View* v = dynamic_cast<View*>(p);
		if (v) {
			auto hve = Ref(this);
			v->cbOnHoverChanged = CLOSURE([=]() {
				hve->applyEffect();
				if (hve->cbOnHoverChanged) {
					hve->cbOnHoverChanged->invoke(v);
				}
			});
			//if (onClick || onHostEvent) {
				v->cbOnEvent = CLOSURE([=](Event* e) {
					if (hve->onHostEvent) {
						if (hve->onHostEvent->invoke(e)) return;
					}
					MouseEvent* me = dynamic_cast<MouseEvent*>(e);
					if (me && me->isClickInBubble()) {

						if (me->button == 0 ) {
							if (hve->onClick) {
								hve->onClick->invoke(me);
							}
						}
					}
				});
			//}
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
			Border b = border;

			if (isActive) {
				bgColor = activeBackgroundColor;
				b = activeBorder;
			} else if (hover) {
				bgColor = hoverBackgroundColor;
				b = hoverBorder;

			}
			else {
			}



			v->backgroundColor = bgColor;
			v->border.copyFrom(&b);
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
			v->cbOnEvent = nullptr;
			applyEffect();
		}
	}
}

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<HoverViewEffect>("HoverViewEffect")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("backgroundColor", &HoverViewEffect::backgroundColor)
		.property("border", &HoverViewEffect::border)
		.property("hoverBackgroundColor", &HoverViewEffect::hoverBackgroundColor)
		.property("hoverBorder", &HoverViewEffect::hoverBorder)
		.property("activeBackgroundColor", &HoverViewEffect::activeBackgroundColor)
		.property("activeBorder", &HoverViewEffect::activeBorder)
		.property("hoverCursor", &HoverViewEffect::hoverCursor)
		.property("isActive", &HoverViewEffect::isActive)
		.method("applyEffect", &HoverViewEffect::applyEffect)
		.method("getClassName", &HoverViewEffect::getClassName);
}
