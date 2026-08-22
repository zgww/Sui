#pragma once

#include "Predef.h"
#include "Event.h"
#include "MouseEvent.h"

class Node;
class Window;

class TextEventBase : public ViewEvent {
public:
	Ref<Window> window{nullptr, this};
	virtual void dispatch();
};

class TextEditingEvent : public TextEventBase {
public:
	std::string text;
	int start = 0;
	int length = 0;

	void reset() { text.clear(); start = 0; length = 0; }
	bool is_editing() const { return length > 0 || !text.empty(); }
	int total_rune_length() const { return (int)text.length(); }
};

//输入法合成事件
void dispatchImeEndComposition(long long windowId);

//结束输入法合成
void dispatchImeComposition(
	const char* text,
	int start,
	int length,
	long long windowId
);

class TextInputEvent : public TextEventBase {
public:
	std::string text;
};

void dispatchTextInputEvent(const char* text, long long windowId);

class KeyEvent : public Event {
public:
	int char_code = 0;
	std::string key;
	bool isKeyDown = false;
	bool isKeyUp = false;
	bool shift = false;
	bool ctrl = false;
	bool alt = false;
	Ref<Window> window{nullptr, this};

	void setIsKeyDown(bool v) { isKeyDown = v; isKeyUp = !v; }
	void dispatch();
};

class WindowFocusEvent : public Event {
public:
	bool isFocus = false;
	bool isBlur = false;
	Ref<Window> window{nullptr, this};
};

void dispatchWindowFocusEvent(WindowFocusEvent* event);
void dispatchEventToFocusNode(Event* event, Window* window);
