#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/Timer.h"
#include "../Core/Canvas.h"
#include "../View/TextView.h"
#include <string>

class Toast : public View {
public:
	std::string message;
	int bgColor = 0xcc333333;
	int textColor = 0xffffffff;
	int duration = 2000;
	Ref<Timer> dismissTimer{nullptr, this};

	Toast();
	void showMessage(const std::string& msg, int durationMs = 2000);
	void draw_self(Canvas* canvas) override;

	virtual const char* getClassName() const override { return "Toast"; }
};

void showToast(const std::string& message, int durationMs = 2000);
