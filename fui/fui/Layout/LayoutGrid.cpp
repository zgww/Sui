#include "LayoutGrid.h"
#include "../Core/ViewBase.h"

void LayoutGrid::layout(Frame* ctx) {
	updateFrame_forSelfWidthHeight(ctx);
	initLayoutSize(ctx);

	if (!ctx->isTightWidth()) return;
	if (rowCount > 0 && !ctx->isTightHeight()) return;

	View::layout(ctx);
}

void LayoutGrid::resetOccupyGrid() {
	for (auto& cell : occupyGrid) {
		cell.occupy = false;
	}
}

void LayoutGrid::extendOccupyGrid(int row, bool erase) {
	int cnt = row * colCount;
	if ((int)occupyGrid.size() < cnt) {
		for (int i = (int)occupyGrid.size(); i < cnt; i++) {
			occupyGrid.push_back(LayoutGridOccupyCell{});
		}
	} else if (erase && (int)occupyGrid.size() > cnt) {
		occupyGrid.resize(cnt);
	}
}

void LayoutGrid::occupy(int c, int r, int colSpan, int rowSpan) {
	for (int rr = 0; rr < rowSpan; rr++) {
		for (int cc = 0; cc < colSpan; cc++) {
			int idx = (r + rr) * colCount + (c + cc);
			if (idx >= 0 && idx < (int)occupyGrid.size()) {
				occupyGrid[idx].occupy = true;
			}
		}
	}
}

bool LayoutGrid::checkFreeSpace(int c, int r, int colSpan, int rowSpan) {
	int gridRowCount = (int)occupyGrid.size() / colCount;
	for (int rr = 0; rr < rowSpan; rr++) {
		for (int cc = 0; cc < colSpan; cc++) {
			int posR = r + rr;
			int posC = c + cc;
			if (posR >= gridRowCount || posC >= colCount) return false;
			int idx = posR * colCount + posC;
			if (idx >= 0 && idx < (int)occupyGrid.size()) {
				if (occupyGrid[idx].occupy) return false;
			}
		}
	}
	return true;
}

bool LayoutGrid::findNextAvailableGridPos(int startC, int startR, int colSpan, int rowSpan, int* outC, int* outR) {
	int c = startC;
	for (int ri = 0; ; ri++) {
		int r = ri + startR;
		if (rowCount < 1) {
			extendOccupyGrid(r + rowSpan, true);
		} else if (r >= rowCount) {
			break;
		}

		for (; c < colCount; c++) {
			if (checkFreeSpace(c, r, colSpan, rowSpan)) {
				*outC = c;
				*outR = r;
				return true;
			}
		}
		c = 0;
	}
	return false;
}

void LayoutGrid::updateOccupyViewInfo(Frame* kidctx, int c, int r, int colSpan, int rowSpan) {
	float desiredHeight = (kidctx->height - (rowSpan - 1) * rowGap) / rowSpan;
	for (int j = 0; j < rowSpan; j++) {
		for (int i = 0; i < colSpan; i++) {
			int idx = (j + r) * colCount + c + i;
			if (idx >= 0 && idx < (int)occupyGrid.size()) {
				occupyGrid[idx].desiredHeight = desiredHeight;
				occupyGrid[idx].restRowSpan = rowSpan - 1 - j;
			}
		}
	}
}

float LayoutGrid::calcMaxHeight_ofRow(int r) {
	float maxHeight = 0.0f;
	for (int c = 0; c < colCount; c++) {
		int idx = r * colCount + c;
		if (idx >= 0 && idx < (int)occupyGrid.size()) {
			maxHeight = maxFloat(maxHeight, occupyGrid[idx].desiredHeight);
		}
	}
	return maxHeight;
}

void LayoutGrid::adjustRestRowsDesiredHeight(int r, float maxHeight) {
	for (int c = 0; c < colCount; c++) {
		int idx = r * colCount + c;
		if (idx < 0 || idx >= (int)occupyGrid.size()) continue;
		float delta = maxHeight - occupyGrid[idx].desiredHeight;
		if (delta > 0.001f && occupyGrid[idx].restRowSpan > 0) {
			float averDelta = delta / occupyGrid[idx].restRowSpan;
			for (int j = 0; j < occupyGrid[idx].restRowSpan; j++) {
				int restIdx = (r + j + 1) * colCount + c;
				if (restIdx >= 0 && restIdx < (int)occupyGrid.size()) {
					occupyGrid[restIdx].desiredHeight = maxFloat(0.0f, occupyGrid[restIdx].desiredHeight - averDelta);
				}
			}
		}
	}
}

void LayoutGrid::layoutContent(Frame* ctx) {
	if (colCount < 1) {
		printf("warning: LayoutGrid invalid colCount:%d, rowCount:%d\n", colCount, rowCount);
		return;
	}

	float colSize = (ctx->width - colGap * (colCount - 1)) / colCount;
	float rowSize = 10.0f;
	bool wrapHeight = false;

	if (rowSizeRatio > 0.001f) {
		rowSize = colSize * rowSizeRatio;
	} else if (rowSize > 0.001f) {
		// use fixed rowSize
	} else if (rowCount > 0 && ctx->isTightHeight()) {
		rowSize = (ctx->height - rowGap * (rowCount - 1)) / rowCount;
	} else {
		wrapHeight = true;
	}

	std::vector<LayoutGridItem> items;

	resetOccupyGrid();
	if (rowCount > 0) {
		extendOccupyGrid(rowCount, true);
	}

	int c = 0;
	int r = 0;
	int maxRowCount = 0;
	int l = getChildrenCount();

	for (int i = 0; i < l; i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->canLayoutByParent()) {
			int cs = colSpan;
			int rs = rowSpan;
			LayoutGridCell* cell = view->getLayoutCellByType<LayoutGridCell>();
			if (cell) {
				cs = cell->colSpan;
				rs = cell->rowSpan;
			}
			if (cs < 1) cs = 1;
			if (rs < 1) rs = 1;

			if (findNextAvailableGridPos(c, r, cs, rs, &c, &r)) {
				occupy(c, r, cs, rs);

				LayoutGridItem item;
				item.col = c;
				item.row = r;
				item.colSpan = cs;
				item.rowSpan = rs;
				item.view = view;
				item.width = cs * colSize + (cs - 1) * colGap;
				item.x = c * (colSize + colGap);

				items.push_back(item);
				maxRowCount = (int)maxFloat((float)r + rs, (float)maxRowCount);

				c += cs;
			} else {
				view->frame.setTight(0, 0);
			}
		}
	}

	float maxHeight = 0.0f;

	if (wrapHeight) {
		std::vector<LayoutGridRowInfo> rowHeights(maxRowCount);

		for (int i = 0; i < (int)items.size(); i++) {
			LayoutGridItem& item = items[i];
			ViewBase* view = item.view;
			view->frame.setTightWidth(item.width);
			view->frame.setHeightConstraint(0.0f, ctx->maxHeight);
			view->layout(&view->frame);

			item.desiredHeight = view->frame.height;
			updateOccupyViewInfo(&view->frame, item.col, item.row, item.colSpan, item.rowSpan);
		}

		for (int j = 0; j < (int)rowHeights.size(); j++) {
			float height = calcMaxHeight_ofRow(j);
			rowHeights[j].height = height;
			adjustRestRowsDesiredHeight(j, height);
		}

		float y = 0.0f;
		for (int j = 0; j < (int)rowHeights.size(); j++) {
			rowHeights[j].y = y;
			y += rowHeights[j].height + rowGap;
		}

		for (int i = 0; i < (int)items.size(); i++) {
			LayoutGridItem& item = items[i];
			float actualHeight = (item.rowSpan - 1) * rowGap;
			for (int _r = item.row; _r < item.row + item.rowSpan; _r++) {
				if (_r >= 0 && _r < (int)rowHeights.size()) {
					actualHeight += rowHeights[_r].height;
				}
			}
			if (actualHeight != item.desiredHeight) {
				item.view->frame.setTight(item.width, actualHeight);
				item.view->layout(&item.view->frame);
			}

			if (item.row >= 0 && item.row < (int)rowHeights.size()) {
				item.view->frame.setPosition(item.x, rowHeights[item.row].y);
			}
			maxHeight = maxFloat(maxHeight, item.view->frame.getBottom());
		}
	} else {
		for (int i = 0; i < (int)items.size(); i++) {
			LayoutGridItem& item = items[i];
			ViewBase* view = item.view;

			view->frame.setTight(
				item.width,
				item.rowSpan * rowSize + (item.rowSpan - 1) * rowGap
			);
			view->layout(&view->frame);
			view->frame.setPosition(
				item.x,
				item.row * (rowSize + rowGap)
			);
			maxHeight = maxFloat(maxHeight, view->frame.getBottom());
		}
	}

	ctx->setHeight(maxHeight);
}
