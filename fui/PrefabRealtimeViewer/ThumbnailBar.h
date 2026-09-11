// Converted from ThumbnailBar.ixx (C++20 module) to classic header/source.
#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "View/ScrollArea.h"
#include "View/ImageView.h"
#include "View/HoverViewEffect.h"
#include "Core/Node.h"
#include "Core/Vec2.h"
#include "Core/MouseEvent.h"
#include "Core/Event.h"
#include "Urgc/Urgc.h"

class ThumbnailBar : public ScrollArea {
public:
	std::string directory;
	std::vector<std::string> imageFiles;
	int selectedIndex = -1;

	Ref<Closure<void(int)>> onSelect{nullptr, this};

	ThumbnailBar();

	virtual const char* getClassName() const override;

	void setDirectory(const std::string& dir);

	void setSelectedIndex(int index);

	void scanImages();

	void react();

	void updateHighlight(int index);
};
