#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/MouseEvent.h"
#include "../Core/KeyEvent.h"
#include "../Core/Timer.h"
#include <string>

class EditText : public View {
public:
	std::string value;
	std::string placeholder;
	int fontSize = 14;
	int color = 0xff333333;
	int caretColor = 0xff1677ff;
	int placeholderColor = 0xff999999;
	int bgColor = 0xffffffff;

	int caretPos = 0;
	bool caretVisible = false;
	bool focused = false;
	Ref<Timer> caretTimer{nullptr, this};

	Ref<Closure<void(const std::string&)>> onChanged{nullptr, this};

	EditText();
	void setValue(const std::string& v);
	void focus();
	void blur();
	void insertText(const std::string& text);
	void deleteBackward();
	void deleteForward();
	void moveCaret(int delta);
	void draw_self(Canvas* canvas) override;
	void onEvent(Event* ev) override;
	void onUnmounting() override;

	virtual const char* getClassName() const override { return "EditText"; }
};
