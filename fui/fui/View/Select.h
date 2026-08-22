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

    int value = -1;

    Ref<Closure<void(int i, std::string label)>> onChanged{ nullptr, this };

    void fire_onChanged();

    Select();
    void appendOptionCStr(const char* text);
    void appendOption(std::string text);
    void react();

    std::string getLabel();

    void setIsActive(bool v);

    void setValue(int i);

    void showPopupMenu();

    void onEvent(Event* ev);


	virtual const char* getClassName() const override { return "Select"; }
};
