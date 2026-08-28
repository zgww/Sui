#include "Keyboard.h"
#include "KeyEvent.h"
#include "Window.h"
#include "App.h"

KeyEvent* newKeyEvent_fromKeyboardData(KeyboardData* kd) {
	Ref<KeyEvent> event{new KeyEvent()};
	event->char_code = kd->char_code;
	event->key = kd->key ? std::string(kd->key) : "";
	event->isKeyDown = kd->isKeyDown;
	event->isKeyUp = kd->isKeyUp;
	event->shift = kd->shift;
	event->ctrl = kd->ctrl;
	event->alt = kd->alt;
	return event;
}

void Keyboard_onKeyDown(int64_t windowId, int char_code, const char* key, bool shift, bool ctrl, bool alt) {
	App* app = App_use();
	Window* win = app->findWindowById(windowId);
	if (!win) return;

	Ref<KeyEvent> event{new KeyEvent()};
	event->char_code = char_code;
	event->key = key ? std::string(key) : "";
	event->isKeyDown = true;
	event->isKeyUp = false;
	event->shift = shift;
	event->ctrl = ctrl;
	event->alt = alt;
	event->window = win;
	event->name = "keydown";

	event->dispatch();
}

void Keyboard_onKeyUp(int64_t windowId, int char_code, const char* key, bool shift, bool ctrl, bool alt) {
	App* app = App_use();
	Window* win = app->findWindowById(windowId);
	if (!win) return;

	Ref<KeyEvent> event{new KeyEvent()};
	event->char_code = char_code;
	event->key = key ? std::string(key) : "";
	event->isKeyDown = false;
	event->isKeyUp = true;
	event->shift = shift;
	event->ctrl = ctrl;
	event->alt = alt;
	event->window = win;
	event->name = "keyup";

	event->dispatch();
}

void printKeyboardData(KeyboardData* kd) {
	printf("KeyboardData: char_code:%d key:%s down:%d up:%d shift:%d ctrl:%d alt:%d\n",
		kd->char_code, kd->key ? kd->key : "", kd->isKeyDown, kd->isKeyUp, kd->shift, kd->ctrl, kd->alt);
}
