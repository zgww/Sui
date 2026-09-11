#include "ListItemHoverEffect.h"

#include <rttr/registration>

void ListItemHoverEffect::onMounted() {
	// 先由父类绑定 cbOnHoverChanged 与基础点击派发（onClick/onHostEvent）
	HoverViewEffect::onMounted();

	Node* p = parent;
	View* v = dynamic_cast<View*>(p);
	if (!v) return;

	// 在父类点击派发之外再包一层：左键点击即把本项置为 active(选中)，并触发兄弟互斥
	auto prevEvent = v->cbOnEvent;
	auto self = Ref(this);
	v->cbOnEvent = CLOSURE([=](Event* e) {
		if (self->selectOnClick) {
			MouseEvent* me = dynamic_cast<MouseEvent*>(e);
			if (me && me->isClickInBubble() && me->button == 0) {
				clearSiblingsActive();
				self->isActive = true;
				self->applyEffect();
			}
		}
		if (prevEvent.get() != nullptr) prevEvent->invoke(e);
	});
}

void ListItemHoverEffect::clearSiblingsActive() {
	Node* selfNode = parent;
	View* selfView = dynamic_cast<View*>(selfNode);
	if (!selfView) return;
	Node* container = selfView->parent;
	if (!container) return;

	for (int i = 0; i < container->getChildrenCount(); i++) {
		Node* sibling = container->getChild(i);
		if (!sibling || sibling == selfView) continue;
		for (int j = 0; j < sibling->getChildrenCount(); j++) {
			Node* kid = sibling->getChild(j);
			auto* other = dynamic_cast<ListItemHoverEffect*>(kid);
			if (other && other != this && other->isActive) {
				other->isActive = false;
				// 直接走基类复位，避免虚调用再次进入互斥逻辑
				other->HoverViewEffect::applyEffect();
			}
		}
	}
}

void ListItemHoverEffect::applyEffect() {
	Node* selfNode = parent;
	View* selfView = dynamic_cast<View*>(selfNode);
	if (exclusive && selfView && (isActive || selfView->hover)) {
	}
	HoverViewEffect::applyEffect();
}

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<ListItemHoverEffect>("ListItemHoverEffect")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("selectOnClick", &ListItemHoverEffect::selectOnClick)
		.property("exclusive", &ListItemHoverEffect::exclusive);
	// 普通/hover/active 的颜色、边框与 isActive 等属性均继承自 HoverViewEffect，
	// 借助 RTTR_ENABLE 继承链，get_properties() 会自动包含，无需重复注册。
}
