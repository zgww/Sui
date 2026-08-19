#pragma once

#include "Predef.h"

struct KeyboardData {
	int char_code = 0;
	const char* key = nullptr;
	int64_t windowId = 0;
	bool isKeyDown = false;
	bool isKeyUp = false;
	bool shift = false;
	bool ctrl = false;
	bool alt = false;
};

class KeyEvent;

KeyEvent* newKeyEvent_fromKeyboardData(KeyboardData* kd);
void Keyboard_onKeyDown(int64_t windowId, int char_code, const char* key, bool shift, bool ctrl, bool alt);
void Keyboard_onKeyUp(int64_t windowId, int char_code, const char* key, bool shift, bool ctrl, bool alt);
void printKeyboardData(KeyboardData* kd);
