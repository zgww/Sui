#include "KeyEvent.h"
#include "Node.h"
#include "Window.h"
#include "Focus.h"
#include "App.h"

#include <rttr/registration>

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

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<TextEventBase>("TextEventBase")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.method("dispatch", &TextEventBase::dispatch);

	registration::class_<TextEditingEvent>("TextEditingEvent")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("text", &TextEditingEvent::text)
		.property("start", &TextEditingEvent::start)
		.property("length", &TextEditingEvent::length)
		.method("reset", &TextEditingEvent::reset)
		.method("is_editing", &TextEditingEvent::is_editing)
		.method("total_rune_length", &TextEditingEvent::total_rune_length);

	registration::class_<TextInputEvent>("TextInputEvent")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("text", &TextInputEvent::text);

	registration::class_<KeyEvent>("KeyEvent")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("char_code", &KeyEvent::char_code)
		.property("key", &KeyEvent::key)
		.property("isKeyDown", &KeyEvent::isKeyDown)
		.property("isKeyUp", &KeyEvent::isKeyUp)
		.property("shift", &KeyEvent::shift)
		.property("ctrl", &KeyEvent::ctrl)
		.property("alt", &KeyEvent::alt)
		.method("setIsKeyDown", &KeyEvent::setIsKeyDown)
		.method("dispatch", &KeyEvent::dispatch);

	registration::class_<WindowFocusEvent>("WindowFocusEvent")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("isFocus", &WindowFocusEvent::isFocus)
		.property("isBlur", &WindowFocusEvent::isBlur);
}
