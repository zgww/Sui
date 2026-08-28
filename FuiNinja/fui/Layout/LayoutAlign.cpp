#include "LayoutAlign.h"
#include "../Core/ViewBase.h"

void LayoutAlign::layoutContent(Frame* ctx) {
	float maxWidth = 0;
	float maxHeight = 0;
	int l = getChildrenCount();

	for (int i = 0; i < l; i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->canLayoutByParent()) {
			LayoutCell* cell = view->getLayoutCellByType<LayoutCell>();

			LayoutAlignPositionCell* pcell = dynamic_cast<LayoutAlignPositionCell*>(cell);
			if (pcell) {
				continue;
			}

			if (useMaxConstraint) {
				view->frame.copyMaxConstraints(ctx);
			}

			LayoutAlignCell* ac = dynamic_cast<LayoutAlignCell*>(cell);
			if (ac) {
				if (!std::isnan(ac->sizeRatio.x)) {
					view->frame.setTightWidth(ctx->width * ac->sizeRatio.x);
				}
				if (!std::isnan(ac->sizeRatio.y)) {
					view->frame.setTightHeight(ctx->height * ac->sizeRatio.y);
				}
			}

			view->layout(&view->frame);

			maxWidth = maxFloat(maxWidth, view->frame.width);
			maxHeight = maxFloat(maxHeight, view->frame.height);
		}
	}

	ctx->setSize(maxWidth, maxHeight);

	l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->canLayoutByParent()) {
			LayoutCell* cell = view->getLayoutCellByType<LayoutCell>();

			LayoutAlignPositionCell* pcell = dynamic_cast<LayoutAlignPositionCell*>(cell);
			if (pcell) {
				view->frame.reset();

				if (!std::isnan(pcell->left) && !std::isnan(pcell->right)) {
					float w = ctx->width - pcell->left - pcell->right;
					view->frame.setWidthConstraint(w, w);
				}
				if (!std::isnan(pcell->top) && !std::isnan(pcell->bottom)) {
					float h = ctx->height - pcell->top - pcell->bottom;
					view->frame.setHeightConstraint(h, h);
				}

				view->layout(&view->frame);

				if (!std::isnan(pcell->left)) {
					view->frame.x = pcell->left;
				}
				if (!std::isnan(pcell->top)) {
					view->frame.y = pcell->top;
				}
				if (!std::isnan(pcell->right)) {
					view->frame.x = ctx->width - pcell->right - view->frame.width;
				}
				if (!std::isnan(pcell->bottom)) {
					view->frame.y = ctx->height - pcell->bottom - view->frame.height;
				}
			} else {
				Vec2 anchor;
				Vec2 align;
				getAnchorAndAlign_byView(view, &anchor, &align);
				view->frame.x = ctx->width * align.x - view->frame.width * anchor.x;
				view->frame.y = ctx->height * align.y - view->frame.height * anchor.y;
			}
		}
	}
}

void LayoutAlign::getAnchorAndAlign_byView(ViewBase* view, Vec2* anchor, Vec2* align) {
	LayoutAlignCell* cell = view->getLayoutCellByType<LayoutAlignCell>();
	if (cell) {
		*anchor = cell->anchor;
		*align = cell->align;
	} else {
		*anchor = this->anchor;
		*align = this->align;
	}
}
