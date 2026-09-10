#include "Focus.h"
#include "Node.h"

#include <rttr/registration>

void Focus::focus(Node* node) {
	if (node == focusNode) return;
	if (focusNode != nullptr) {
		Ref<FocusEvent> ev{new FocusEvent()};
		ev->init(focusNode, false);
		focusNode->emit(ev);
	}
	focusNode = node;
	if (focusNode != nullptr) {
		Ref<FocusEvent> ev{new FocusEvent()};
		ev->init(focusNode, true);
		focusNode->emit(ev);
	}
}

void Focus::blurNode(Node* n) {
	if (focusNode == n) {
		blur();
	}
}

void Focus::blur() {
	if (focusNode != nullptr) {
		Ref<FocusEvent> ev{new FocusEvent()};
		ev->init(focusNode, false);
		focusNode->emit(ev);
		focusNode = nullptr;
	}
}

static Ref<Focus> g_focus;

Focus* insFocus() {
	if (!g_focus) {
		g_focus = new Focus();
	}
	return g_focus;
}

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<FocusEvent>("FocusEvent")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("isFocus", &FocusEvent::isFocus)
		.property("isBlur", &FocusEvent::isBlur)
		.method("init", &FocusEvent::init);

	registration::class_<Focus>("Focus")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.method("focus", &Focus::focus)
		.method("blurNode", &Focus::blurNode)
		.method("blur", &Focus::blur)
		.method("getFocusNode", &Focus::getFocusNode)
		.method("isFocus", &Focus::isFocus)
		.method("hasFocus", &Focus::hasFocus);
}
