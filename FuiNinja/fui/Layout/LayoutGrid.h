#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/LayoutCell.h"
#include "../Core/Vec2.h"
#include "../Core/Frame.h"
#include <vector>

class LayoutGridCell : public LayoutCell {
public:
	int colSpan = 1;
	int rowSpan = 1;

	virtual const char* getClassName() const override { return "LayoutGridCell"; }
};

struct LayoutGridItem {
	ViewBase* view = nullptr;
	int col = 0;
	int row = 0;
	int rowSpan = 1;
	int colSpan = 1;
	float width = 0.0f;
	float x = 0.0f;
	float desiredHeight = 0.0f;
};

struct LayoutGridRowInfo {
	float height = 0.0f;
	float y = 0.0f;
};

struct LayoutGridOccupyCell {
	bool occupy = false;
	float desiredHeight = 0.0f;
	int restRowSpan = 0;
};

class LayoutGrid : public View {
public:
	std::vector<LayoutGridOccupyCell> occupyGrid;

	float maxCrossSize = 0.0f;
	int colSpan = 1;
	int rowSpan = 1;
	int colCount = 3;
	float rowSize = 0.0f;
	float rowSizeRatio = 0.0f;
	int rowCount = 0;
	float colGap = 4.0f;
	float rowGap = 4.0f;

	void layout(Frame* ctx) override;
	void resetOccupyGrid();
	void extendOccupyGrid(int row, bool erase);
	void occupy(int c, int r, int colSpan, int rowSpan);
	bool checkFreeSpace(int c, int r, int colSpan, int rowSpan);
	bool findNextAvailableGridPos(int startC, int startR, int colSpan, int rowSpan, int* outC, int* outR);
	void updateOccupyViewInfo(Frame* kidctx, int c, int r, int colSpan, int rowSpan);
	float calcMaxHeight_ofRow(int r);
	void adjustRestRowsDesiredHeight(int r, float maxHeight);
	void layoutContent(Frame* ctx) override;

	virtual const char* getClassName() const override { return "LayoutGrid"; }
};
