#pragma once

#include <string>
#include <vector>
#include <functional>

#include "Core/Predef.h"
#include "Layout/LayoutLinear.h"
#include "View/MenuNative.h"

class MenuBar : public LayoutLinear {
public:
	struct MenuItem {
		std::string label;
		std::vector<std::pair<std::string, std::function<void()>>> actions;
	};

	std::vector<MenuItem> menus;

	MenuBar();

	virtual const char* getClassName() const override { return "MenuBar"; }

	void setMenus(const std::vector<MenuItem>& m);
	void react() override;
	void showPopup(int index);
	void closePopup();

private:
	int curIndex = -1;
	Ref<MenuNative> popup{nullptr, this};
};
