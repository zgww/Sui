#include "LayoutLinear.h"
#include "../Core/ViewBase.h"

bool LayoutLinear::isMax_in_maxOrStretch(Frame* ctx, bool isHor) {
	if (alignItems == "maxOrStretch") {
		if (isHor && ctx->maxHeight != infinity) return true;
		if (!isHor && ctx->maxWidth != infinity) return true;
	}
	return false;
}

bool LayoutLinear::calcIsHor() {
	return direction == "row" || direction == "row-reverse";
}

std::string LayoutLinear::getCrossAlign_ofKid(ViewBase* view) {
	if (view) {
		LayoutLinearCell* cell = view->getLayoutCellByType<LayoutLinearCell>();
		if (cell && !cell->alignSelf.empty()) {
			return cell->alignSelf;
		}
	}
	return alignItems;
}

void LayoutLinear::layoutCross(Frame* ctx) {
	bool isHor = calcIsHor();
	bool isStretch = alignItems == "stretch" || alignItems == "maxOrStretch";

	if (isMax_in_maxOrStretch(ctx, isHor)) {
		return;
	}

	for (int i = 0; i < getChildrenCount(); i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->canLayoutByParent()) {
			LayoutLinearCell* cell = view->getLayoutCellByType<LayoutLinearCell>();
			bool isKidStretch = false;

			if (cell && !cell->alignSelf.empty()) {
				isKidStretch = cell->alignSelf == "stretch";
			} else {
				isKidStretch = isStretch;
			}

			if (isKidStretch) {
				Frame* kidCtx = &view->frame;

				if (isHor) {
					if (kidCtx->height == ctx->height) continue;
					kidCtx->setTightWidth(kidCtx->width);
					kidCtx->maxHeight = ctx->height;
					kidCtx->minHeight = kidCtx->maxHeight;
				} else {
					if (kidCtx->width == ctx->width) continue;
					kidCtx->setTightHeight(kidCtx->height);
					kidCtx->maxWidth = ctx->width;
					kidCtx->minWidth = kidCtx->maxWidth;
				}

				view->layout(kidCtx);
			}
		}
	}
}

void LayoutLinear::positionChildren(Frame* ctx) {
	bool isHor = calcIsHor();
	float width = ctx->width;
	float height = ctx->height;
	float sumMainSize = 0.0f;
	int viewCount = getChildrenViewCount();
	int l = getChildrenCount();

	for (int i = 0; i < l; i++) {
		ViewBase* v = getChildAsView(i);
		if (v && v->canLayoutByParent()) {
			float addSize = isHor ? v->frame.width : v->frame.height;
			sumMainSize += addSize;
		}
	}

	float idleSpace = isHor ? (ctx->width - sumMainSize) : (ctx->height - sumMainSize);
	float mainPos = 0.0f;
	float delta = 0.0f;

	if (justifyContent == "center") {
		mainPos += idleSpace / 2.0f;
	} else if (justifyContent == "end") {
		mainPos += idleSpace;
	} else if (justifyContent == "space-between") {
		delta = viewCount > 1 ? idleSpace / (viewCount - 1) : 0.0f;
		delta = maxFloat(0.0f, delta);
	} else if (justifyContent == "space-around") {
		delta = viewCount > 0 ? idleSpace / viewCount : 0.0f;
		delta = maxFloat(0.0f, delta);
		mainPos += delta / 2.0f;
	} else if (justifyContent == "space-evenly") {
		delta = idleSpace / (viewCount + 1);
		delta = maxFloat(0.0f, delta);
		mainPos += delta;
	}

	bool isReverse = direction == "row-reverse" || direction == "column-reverse";
	int len = getChildrenCount();

	if (isHor) {
		for (int i = 0; i < len; i++) {
			int idx = isReverse ? (len - 1 - i) : i;
			ViewBase* view = getChildAsView(idx);
			if (view && view->canLayoutByParent()) {
				std::string crossAlign = getCrossAlign_ofKid(view);

				view->frame.x = mainPos;
				mainPos += view->frame.width + delta;
				if (crossAlign == "start") {
					view->frame.y = 0.0f;
				} else if (crossAlign == "center") {
					view->frame.y = (height - view->frame.height) / 2.0f;
				} else if (crossAlign == "end") {
					view->frame.y = height - view->frame.height;
				} else if (crossAlign == "stretch") {
					view->frame.y = 0.0f;
				}
			}
		}
	} else {
		for (int i = 0; i < len; i++) {
			int idx = isReverse ? (len - 1 - i) : i;
			ViewBase* view = getChildAsView(idx);
			if (view && view->canLayoutByParent()) {
				std::string crossAlign = getCrossAlign_ofKid(view);

				view->frame.y = mainPos;
				mainPos += view->frame.height + delta;
				if (crossAlign == "start") {
					view->frame.x = 0.0f;
				} else if (crossAlign == "center") {
					view->frame.x = (width - view->frame.width) / 2.0f;
				} else if (crossAlign == "end") {
					view->frame.x = width - view->frame.width;
				} else if (crossAlign == "stretch") {
					view->frame.x = 0.0f;
				} else {
					view->frame.x = 0.0f;
				}
			}
		}
	}
}

void LayoutLinear::setMainConstraints(Frame* kidCtx, bool isHor, float minV, float maxV) {
	if (isHor) {
		kidCtx->minWidth = minV;
		kidCtx->maxWidth = maxV;
	} else {
		kidCtx->minHeight = minV;
		kidCtx->maxHeight = maxV;
	}
}

void LayoutLinear::setCrossConstraints(Frame* kidCtx, bool isHor, float minV, float maxV) {
	if (!isHor) {
		kidCtx->minWidth = minV;
		kidCtx->maxWidth = maxV;
	} else {
		kidCtx->minHeight = 0.0f;
		kidCtx->maxHeight = maxV;
	}
}

float LayoutLinear::getMainMaxConstraint(Frame* kidCtx, bool isHor) {
	return isHor ? kidCtx->maxWidth : kidCtx->maxHeight;
}

float LayoutLinear::getCrossMaxConstraint(Frame* kidCtx, bool isHor) {
	return !isHor ? kidCtx->maxWidth : kidCtx->maxHeight;
}

void LayoutLinear::update_maxCrossSize(Frame* kidCtx, bool isHor) {
	if (isHor) {
		maxCrossSize = maxFloat(kidCtx->height, maxCrossSize);
	} else {
		maxCrossSize = maxFloat(kidCtx->width, maxCrossSize);
	}
}

bool LayoutLinear::layout_mainInf(Frame* ctx) {
	bool isHor = calcIsHor();
	bool isMainInf = isHor ? ctx->maxWidth == infinity : ctx->maxHeight == infinity;
	if (!isMainInf) return false;

	float mainSize = 0.0f;
	float crossMinContraints = 0.0f;
	if (isMax_in_maxOrStretch(ctx, isHor)) {
		crossMinContraints = getCrossMaxConstraint(ctx, isHor);
	}

	for (int i = 0; i < getChildrenCount(); i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->canLayoutByParent()) {
			Frame* kidCtx = &view->frame;
			setMainConstraints(kidCtx, isHor, 0.0f, infinity);
			setCrossConstraints(kidCtx, isHor, crossMinContraints, getCrossMaxConstraint(ctx, isHor));
			view->layout(kidCtx);

			mainSize += isHor ? kidCtx->width : kidCtx->height;
			update_maxCrossSize(kidCtx, isHor);
		}
	}

	ctx->clampWidth(isHor ? mainSize : maxCrossSize, minWidth, maxWidth);
	ctx->clampHeight(!isHor ? mainSize : maxCrossSize, minHeight, maxHeight);

	positionChildren(ctx);
	layoutCross(ctx);
	return true;
}

bool LayoutLinear::layout_mainLimit(Frame* ctx) {
	bool isHor = calcIsHor();
	float maxMain = isHor ? ctx->maxWidth : ctx->maxHeight;

	growNodes.clear();
	float sumGrow = 0.0f;
	float plainMainSum = 0.0f;
	float crossMinContraints = 0.0f;

	if (isMax_in_maxOrStretch(ctx, isHor)) {
		crossMinContraints = getCrossMaxConstraint(ctx, isHor);
	}

	for (int i = 0; i < getChildrenCount(); i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->canLayoutByParent()) {
			LayoutLinearCell* cell = view->getLayoutCellByType<LayoutLinearCell>();

			if (cell && cell->grow >= 0.0f) {
				sumGrow += cell->grow;
				growNodes.push_back(view);
				continue;
			}

			Frame* kidCtx = &view->frame;
			setMainConstraints(kidCtx, isHor, 0.0f, infinity);
			setCrossConstraints(kidCtx, isHor, crossMinContraints, getCrossMaxConstraint(ctx, isHor));
			view->layout(kidCtx);

			plainMainSum += isHor ? kidCtx->width : kidCtx->height;
			update_maxCrossSize(kidCtx, isHor);
		}
	}

	float remainMain = maxMain - plainMainSum;
	for (size_t i = 0; i < growNodes.size(); i++) {
		ViewBase* view = growNodes[i];
		if (remainMain <= 0) {
			if (isHor) view->frame.width = 0.0f;
			else view->frame.height = 0.0f;
		} else {
			LayoutLinearCell* cell = view->getLayoutCellByType<LayoutLinearCell>();
			float ratio = cell->grow / sumGrow;
			float mainSpace = remainMain * ratio;
			Frame* kidCtx = &view->frame;
			setMainConstraints(kidCtx, isHor, mainSpace, mainSpace);
			setCrossConstraints(kidCtx, isHor, crossMinContraints, getCrossMaxConstraint(ctx, isHor));
			view->layout(kidCtx);
			update_maxCrossSize(kidCtx, isHor);
		}
	}

	float mainSize = growNodes.size() > 0 ? maxMain : plainMainSum;
	ctx->width = clampFloat(isHor ? mainSize : maxCrossSize, ctx->minWidth, ctx->maxWidth);
	ctx->height = clampFloat(!isHor ? mainSize : maxCrossSize, ctx->minHeight, ctx->maxHeight);

	positionChildren(ctx);
	layoutCross(ctx);
	return true;
}

void LayoutLinear::layoutContent(Frame* ctx) {
	if (layout_mainInf(ctx)) return;
	layout_mainLimit(ctx);
}

void LayoutLinear::layout(Frame* ctx) {
	maxCrossSize = 0.0f;
	View::layout(ctx);
}
