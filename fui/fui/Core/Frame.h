#pragma once

#include "Predef.h"
#include "Inset.h"
#include "Vec2.h"
#include "Rect.h"

struct Frame {
	int timesInOneLayout = 0;
	int applyCacheTimes = 0;

	float minWidth = 0.0f;
	float minHeight = 0.0f;
	float maxWidth = infinity;
	float maxHeight = infinity;

	float prevMinWidth = -1.0f;
	float prevMinHeight = -1.0f;
	float prevMaxWidth = -1.0f;
	float prevMaxHeight = -1.0f;

	float x = 0.0f;
	float y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;

	Frame copy() const {
		Frame ret;
		ret.minWidth = minWidth;
		ret.minHeight = minHeight;
		ret.maxWidth = maxWidth;
		ret.maxHeight = maxHeight;
		ret.x = x;
		ret.y = y;
		ret.width = width;
		ret.height = height;
		return ret;
	}

	bool isConstraintsNotChanged() const {
		return prevMinWidth == minWidth
			&& prevMinHeight == minHeight
			&& prevMaxWidth == maxWidth
			&& prevMaxHeight == maxHeight;
	}

	bool checkAndUseCacheResult() {
		if (isConstraintsNotChanged()) {
			applyCacheTimes++;
			return true;
		}
		return false;
	}

	void saveConstraints() {
		prevMinWidth = minWidth;
		prevMinHeight = minHeight;
		prevMaxWidth = maxWidth;
		prevMaxHeight = maxHeight;
	}

	void incTimesInOneLayout() { timesInOneLayout++; }

	Frame insetByInset(const Inset& ins) const {
		Frame ret = copy();
		ret.minWidth = ret.minWidth - ins.hor();
		ret.minHeight = ret.minHeight - ins.ver();
		if (ret.maxWidth != infinity) {
			ret.maxWidth = maxFloat(ret.minWidth, ret.maxWidth - ins.hor());
		}
		if (ret.maxHeight != infinity) {
			ret.maxHeight = maxFloat(ret.minHeight, ret.maxHeight - ins.ver());
		}
		ret.x = ret.x + ins.left;
		ret.y = ret.y + ins.top;
		ret.width = maxFloat(0.0f, ret.width - ins.hor());
		ret.height = maxFloat(0.0f, ret.height - ins.ver());
		return ret;
	}

	Frame outsetByInset(const Inset& ins) const {
		Inset inverted = ins;
		inverted.invert();
		return insetByInset(inverted);
	}

	Rect toRect() const {
		return mkRect(x, y, width, height);
	}

	void copyConstraints(const Frame* ctx) {
		copyWidthConstraint(ctx);
		copyHeightConstraint(ctx);
	}
	void copyMaxConstraints(const Frame* ctx) {
		maxHeight = ctx->maxHeight;
		maxWidth = ctx->maxWidth;
	}
	void copyMinConstraints(const Frame* ctx) {
		minHeight = ctx->minHeight;
		minWidth = ctx->minWidth;
	}
	void setMinConstraints(float w, float h) {
		minWidth = w;
		minHeight = h;
	}
	void setMaxConstraints(float w, float h) {
		maxWidth = w;
		maxHeight = h;
	}
	void setMinWidth(float minV) { minWidth = maxFloat(0.0f, minV); }
	void setMinHeight(float minV) { minHeight = maxFloat(0.0f, minV); }
	void setWidthConstraint(float minv, float maxv) {
		minWidth = minv;
		maxWidth = maxv;
	}
	void setHeightConstraint(float minv, float maxv) {
		minHeight = minv;
		maxHeight = maxv;
	}
	void clampTightWidthConstraint(float v) {
		v = clampFloat(v, minWidth, maxWidth);
		minWidth = maxFloat(minWidth, v);
		maxWidth = minFloat(maxWidth, v);
	}
	void clampTightHeightConstraint(float v) {
		v = clampFloat(v, minHeight, maxHeight);
		minHeight = maxFloat(minHeight, v);
		maxHeight = minFloat(maxHeight, v);
	}
	void plusWidthConstraint(float minW, float maxW) {
		if (minWidth < minW) {
			minWidth = minFloat(minW, maxWidth);
		}
		if (maxW < maxWidth) {
			maxWidth = maxFloat(maxW, minWidth);
		}
		minWidth = minFloat(minWidth, maxWidth);
	}
	void plusHeightConstraint(float minW, float maxW) {
		if (minHeight < minW) {
			minHeight = minFloat(minW, maxHeight);
		}
		if (maxW < maxHeight) {
			maxHeight = maxFloat(maxW, minHeight);
		}
		minHeight = minFloat(minHeight, maxHeight);
	}
	void plusConstraints(float minW, float maxW, float minH, float maxH) {
		plusWidthConstraint(minW, maxW);
		plusHeightConstraint(minH, maxH);
	}
	void clampWidth(float v, float minW, float maxW) {
		width = clampFloat(v, maxFloat(minW, minWidth), minFloat(maxW, maxWidth));
	}
	void clampHeight(float v, float minW, float maxW) {
		height = clampFloat(v, maxFloat(minW, minHeight), minFloat(maxW, maxHeight));
	}
	void setSize(float w, float h) {
		width = clampFloat(w, minWidth, maxWidth);
		height = clampFloat(h, minHeight, maxHeight);
	}
	Vec2 getSize() const { return mkVec2(width, height); }
	void setWidth(float w) { width = clampFloat(w, minWidth, maxWidth); }
	void setHeight(float h) { height = clampFloat(h, minHeight, maxHeight); }
	void setRect(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		setSize(w, h);
	}
	void setPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
	float getBottom() const { return y + height; }
	float getRight() const { return x + width; }

	bool setSize_ifAnyTight() {
		bool ret = false;
		if (isTightWidth()) { width = minWidth; ret = true; }
		if (isTightHeight()) { height = minHeight; ret = true; }
		return ret;
	}
	bool setSize_ifTight() {
		if (isTight()) {
			width = minWidth;
			height = minHeight;
			return true;
		}
		return false;
	}

	void copyWidthConstraint(const Frame* ctx) {
		minWidth = ctx->minWidth;
		maxWidth = ctx->maxWidth;
	}
	void copyHeightConstraint(const Frame* ctx) {
		minHeight = ctx->minHeight;
		maxHeight = ctx->maxHeight;
	}
	void setTightWidth(float w) { width = minWidth = maxWidth = w; }
	void setTightHeight(float h) { height = minHeight = maxHeight = h; }
	void setTight(float w, float h) {
		width = minWidth = maxWidth = w;
		height = minHeight = maxHeight = h;
	}
	bool isTightWidth() const { return minWidth == maxWidth; }
	bool isTightHeight() const { return minHeight == maxHeight; }
	bool isTight() const { return minWidth == maxWidth && minHeight == maxHeight; }
	bool isLoose() const { return !isTight(); }

	void reset() { *this = Frame(); }

	bool isSizeSatisfy_otherFrameConstraints(const Frame* ctx) const {
		if (width < ctx->minWidth || width > ctx->maxWidth) return false;
		if (height < ctx->minHeight || height > ctx->maxHeight) return false;
		return true;
	}
};

inline Frame mkFrame() {
	Frame f;
	f.minWidth = 0.0f;
	f.minHeight = 0.0f;
	f.maxWidth = infinity;
	f.maxHeight = infinity;
	f.prevMinWidth = -1.0f;
	f.prevMinHeight = -1.0f;
	f.prevMaxWidth = -1.0f;
	f.prevMaxHeight = -1.0f;
	f.x = 0.0f;
	f.y = 0.0f;
	f.width = 0.0f;
	f.height = 0.0f;
	return f;
}
