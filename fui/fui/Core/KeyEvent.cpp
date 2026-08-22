#include "KeyEvent.h"
#include "Node.h"
#include "Window.h"
#include "Focus.h"
#include "App.h"

void TextEventBase::dispatch() {
	if (!window) return;
	Focus* focus = insFocus();
	Node* target = focus->getFocusNode();
	if (target) {
		target->emit(this);
	}
}



//输入法合成事件
void dispatchImeEndComposition(long long windowId) {
	printf("输入法合成结束事件\n");
}

//结束输入法合成
void dispatchImeComposition(
	const char* text,
	int start,
	int length,
	long long windowId
) {
	printf("输入法合成事件 text:%s, start:%d, length:%d, windowId:%lld\n",
		text, start, length, windowId);

	Ref<App> app = App_use();
	Ref<Window> win = app->findWindowById(windowId);

	Ref<TextEditingEvent> e = new TextEditingEvent();
	e->text = (text);
	e->start = start;
	e->length = length;
	e->window = win;

	dispatchEventToFocusNode(e, win);
}




void dispatchTextInputEvent(const char* text, long long windowId) {
	Ref<App> app = App_use();
	Ref<Window> win = app->findWindowById(windowId);

	Ref<TextInputEvent > e = new TextInputEvent();
	e->text = (text);
	e->window = win;
	printf("dispatchTextInputEvent:%s\n", e->text.c_str());

	dispatchEventToFocusNode(e.get(), win.get());
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

void dispatchEventToFocusNode(Event* evt, Window* window) {
	Focus* f = insFocus();
	//分发到焦点节点
	if (f->focusNode != nullptr) {
		f->focusNode->emit(evt);
	}
	//分发到window
	if (!evt->isStopPropagation && window != nullptr) {
		window->emit(evt);
	}
}
