#pragma once

#include "Core/Predef.h"
#include "View/ScrollArea.h"

class ThumbnailBar : public ScrollArea {
public:
	std::string directory;
	std::vector<std::string> imageFiles;
	int selectedIndex = -1;

	Ref<Closure<void(int)>> onSelect{nullptr, this};

	ThumbnailBar();

	virtual const char* getClassName() const override { return "ThumbnailBar"; }

	void setDirectory(const std::string& dir);
	void setSelectedIndex(int index);
	void scanImages();
	void react() override;

private:
	void updateHighlight(int index);
};
