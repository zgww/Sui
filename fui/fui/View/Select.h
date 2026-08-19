#pragma once

#include "../Core/Predef.h"
#include "../Layout/LayoutLinear.h"
#include "../Core/MouseEvent.h"
#include "TextView.h"
#include <vector>
#include <string>

class Select : public LayoutLinear {
public:
	std::vector<std::string> options;
	int selectedIndex = -1;
	bool isActive = false;

	int normalBg = 0xffffffff;
	int hoverBg = 0xfff0f0f0;
	int activeBg = 0xffe0e0e0;
	int textColor = 0xff333333;

	Ref<TextView> labelView{nullptr, this};
	Ref<TextView> arrowView{nullptr, this};

	Ref<Closure<void(int, const std::string&)>> onChanged{nullptr, this};

	Select();
	void appendOption(const std::string& text);
	void setSelectedIndex(int i);
	void togglePopup();
	void onEvent(Event* ev) override;
	void onHoverChanged() override;

	virtual const char* getClassName() const override { return "Select"; }
};
