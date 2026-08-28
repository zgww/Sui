#pragma once

#include "../Core/Predef.h"
#include "../Layout/LayoutLinear.h"
#include "../Core/MouseEvent.h"
#include "TextView.h"
#include <functional>

class Panel : public LayoutLinear {
public:
	std::string title;
	bool open = true;

	//int titleBg = 0xfff0f0f0;
	int titleColor = 0xff333333;
	int titleFontSize = 14;

	//Ref<TextView> titleView{nullptr, this};
	//Ref<View> bodyView{nullptr, this};

	//Ref<Closure<void(Node*)>> cbRenderContent{nullptr, this};

	Panel();
	void setTitle(const std::string& t);
	void setOpen(bool v);
	//void setBody(View* v);
	void onEvent(Event* ev) override;
	//void onEvent_forHead(Event* e);
	void react();

	virtual const char* getClassName() const override { return "Panel"; }
};
