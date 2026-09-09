#pragma once

#include <string>

#include "Core/Predef.h"
#include "Core/Timer.h"
#include "Core/Window.h"
#include "Layout/LayoutAlign.h"

class ImageCanvasView;
class ThumbnailBar;
class View;

class ImageViewerState : public GcObj {
public:
	Ref<Window> win{nullptr, this};
	Ref<LayoutAlign> root{nullptr, this};

	std::string currentPath;
	std::string currentDir;
	int currentIndex = -1;
	float currentZoom = 1.0f;

	ImageCanvasView* canvasPtr = nullptr;
	ThumbnailBar* thumbPtr = nullptr;

	std::string tooltipText;
	float tooltipX = 0;
	float tooltipY = 0;
	View* tooltipOverlay = nullptr;
	Ref<Timer> invalidRender{nullptr, this};

	ImageViewerState();

	void showTooltip(const std::string& text, float x, float y);
	void hideTooltip();
	void render();
	void openFile(const std::string& path);
	void onThumbnailSelect(int index);
	void onOpenFile();
};

void runImageViewer(const std::string& initialFile);
