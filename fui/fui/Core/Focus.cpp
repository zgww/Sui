#include "Focus.h"
#include "Node.h"

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
