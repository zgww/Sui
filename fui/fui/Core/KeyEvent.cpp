#include "KeyEvent.h"
#include "Node.h"
#include "Window.h"
#include "Focus.h"

void TextEventBase::dispatch() {
	if (!window) return;
	Focus* focus = insFocus();
	Node* target = focus->getFocusNode();
	if (target) {
		target->emit(this);
	}
}

void dispatchImeEndComposition(TextEditingEvent* event) {
	event->dispatch();
}

void dispatchImeComposition(TextEditingEvent* event) {
	event->dispatch();
}

void dispatchTextInputEvent(TextInputEvent* event) {
	event->dispatch();
}

void KeyEvent::dispatch() {
	if (!window) return;
	Focus* focus = insFocus();
	Node* target = focus->getFocusNode();
	if (target) {
		target->emit(this);
	}
	window->emit(this);
}

void dispatchWindowFocusEvent(WindowFocusEvent* event) {
	if (!event || !event->window) return;
	event->window->emit(event);
}

void dispatchEventToFocusNode(Node* node, Event* event) {
	if (node) {
		node->emit(event);
	}
}
