#include "RowWrap.h"
#include "../Core/ViewBase.h"

void RowWrap::alignItems_ofRow(int rowStartIdx, int rowEndIdx, float rowHeight) {
	if (alignItems == "start") return;
	bool center = alignItems == "center";
	bool end = alignItems == "end";

	for (int i = rowStartIdx; i < rowEndIdx; i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->canLayoutByParent()) {
			if (center) {
				view->frame.y += (rowHeight - view->frame.height) / 2.0f;
			} else if (end) {
				view->frame.y += (rowHeight - view->frame.height);
			}
		}
	}
}

void RowWrap::positionChildren(Frame* ctx) {
	Rect contentRect = getContentLocalRect();
	float x = 0.0f;
	float y = 0.0f;
	float rowHeight = 0.0f;
	int rowStartIdx = 0;
	float maxWidth = 0.0f;

	for (int i = 0; i < getChildrenCount(); i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->canLayoutByParent()) {
			Frame* lc = &view->frame;

			if (x + lc->width > ctx->maxWidth) {
				alignItems_ofRow(rowStartIdx, i, rowHeight);
				y += rowHeight + rowGap;
				x = 0.0f;
				rowStartIdx = i;
				rowHeight = 0.0f;
			}

			lc->x = x + contentRect.x;
			lc->y = y + contentRect.y;
			x += lc->width + colGap;

			maxWidth = maxFloat(x, maxWidth);
			rowHeight = maxFloat(rowHeight, lc->height);
		}
	}

	alignItems_ofRow(rowStartIdx, getChildrenCount(), rowHeight);

	ctx->setSize(maxWidth, y + rowHeight);
}

void RowWrap::layoutContent(Frame* contentCtx) {
	for (int i = 0; i < getChildrenCount(); i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->canLayoutByParent()) {
			Frame* kidCtx = &view->frame;
			kidCtx->maxWidth = infinity;
			kidCtx->maxHeight = infinity;
			view->layout(kidCtx);
		}
	}
	positionChildren(contentCtx);
}
