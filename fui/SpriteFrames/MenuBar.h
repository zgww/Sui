// Converted from MenuBar.ixx (C++20 module) to classic header/source.
#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <string>
#include <vector>
#include <functional>

#include "Core/View.h"
#include "Core/Node.h"
#include "Core/Rect.h"
#include "Core/MouseEvent.h"
#include "Core/Event.h"
#include "Core/App.h"
#include "Core/Window.h"
#include "View/TextView.h"
#include "View/MenuNative.h"
#include "View/HoverViewEffect.h"
#include "Layout/LayoutLinear.h"
#include "Urgc/UrgcIndex.h"

class MenuBar : public LayoutLinear {
public:
	struct MenuItem {
		std::string label;
		std::vector<std::pair<std::string, std::function<void()>>> actions;
	};

	std::vector<MenuItem> menus;

	MenuBar();

	virtual const char* getClassName() const override;

	void setMenus(const std::vector<MenuItem>& m);

	void react() override;

	void showPopup(int index);

	void closePopup();

private:
	int curIndex = -1;
	Ref<MenuNative> popup{nullptr, this};
};
