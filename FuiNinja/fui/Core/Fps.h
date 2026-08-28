#pragma once

#include "Predef.h"

class Canvas;

struct Fps {
	float fps = 0;
	float layoutFps = 0;
	float drawFps = 0;

	int64_t costMs = 0;
	int64_t layoutCostMs = 0;
	int64_t drawCostMs = 0;

	int64_t startMs = 0;
	int64_t endMs = 0;

	int64_t layoutStartMs = 0;
	int64_t layoutEndMs = 0;
	int64_t drawStartMs = 0;
	int64_t drawEndMs = 0;

	void startFrame() { startMs = time_unixMs(); }
	void endFrame();
	void startLayout() { layoutStartMs = time_unixMs(); }
	void endLayout() { layoutEndMs = time_unixMs(); }
	void startDraw() { drawStartMs = time_unixMs(); }
	void endDraw() { drawEndMs = time_unixMs(); }
	void draw(Canvas* canvas, int h);
};
