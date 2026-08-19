#pragma once

#include "Predef.h"
#include "Vec2.h"

struct Rect {
	float x = 0;
	float y = 0;
	float w = 0;
	float h = 0;

	std::string toString() const {
		char tmp[128];
		snprintf(tmp, sizeof(tmp), "Rect(%f,%f,%f,%f)", x, y, w, h);
		return std::string(tmp);
	}

	void setAll(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	bool isEmpty() const {
		return fabsf(w) < 0.00001f && fabsf(h) < 0.00001f;
	}

	void set_ltrb(float left, float top, float right, float bottom) {
		if (left > right) { float tmp = left; left = right; right = tmp; }
		if (top > bottom) { float tmp = top; top = bottom; bottom = tmp; }
		x = left;
		y = top;
		w = right - left;
		h = bottom - top;
	}

	bool containsPosition(float px, float py) const {
		return x <= px && px <= x + w
			&& y <= py && py <= y + h;
	}

	float right() const { return x + w; }
	float bottom() const { return y + h; }
	float centerX() const { return x + w / 2.0f; }
	float centerY() const { return y + h / 2.0f; }
	Vec2 centerPos() const {
		Vec2 ret;
		ret.x = centerX();
		ret.y = centerY();
		return ret;
	}
	Vec2 leftTop() const {
		Vec2 ret;
		ret.x = x;
		ret.y = y;
		return ret;
	}
	Vec2 leftBottom() const {
		Vec2 ret;
		ret.x = x;
		ret.y = bottom();
		return ret;
	}
	Vec2 rightTop() const {
		Vec2 ret;
		ret.x = right();
		ret.y = y;
		return ret;
	}
	Vec2 rightBottom() const {
		Vec2 ret;
		ret.x = right();
		ret.y = bottom();
		return ret;
	}

	void offset(float dx, float dy) {
		x += dx;
		y += dy;
	}

	Rect inset(float dx, float dy) const {
		Rect ret;
		ret.x = x + dx;
		ret.y = y + dy;
		ret.w = w - dx * 2.0f;
		ret.h = h - dy * 2.0f;
		return ret;
	}

	void normal() {
		if (w < 0) { x += w; w = -w; }
		if (h < 0) { y += h; h = -h; }
	}

	bool isIntersect(const Rect& b) const {
		float cx = fabsf(centerX() - b.centerX());
		float cy = fabsf(centerY() - b.centerY());
		float hw = (w + b.w) / 2.0f;
		float hh = (h + b.h) / 2.0f;
		return cx <= hw && cy <= hh;
	}

	bool equals(const Rect& b) const {
		return fabsf(x - b.x) < 0.00001f
			&& fabsf(y - b.y) < 0.00001f
			&& fabsf(w - b.w) < 0.00001f
			&& fabsf(h - b.h) < 0.00001f;
	}

	Rect containsPositionIn5Patch(float px, float py, const Rect& centerRatio) const {
		float cx0 = x + w * centerRatio.x;
		float cy0 = y + h * centerRatio.y;
		float cx1 = cx0 + w * centerRatio.w;
		float cy1 = cy0 + h * centerRatio.h;

		if (px < cx0) {
			Rect r; r.setAll(x, cy0, cx0 - x, cy1 - cy0); return r;
		}
		if (px >= cx1) {
			Rect r; r.setAll(cx1, cy0, x + w - cx1, cy1 - cy0); return r;
		}
		if (py < cy0) {
			Rect r; r.setAll(cx0, y, cx1 - cx0, cy0 - y); return r;
		}
		if (py >= cy1) {
			Rect r; r.setAll(cx0, cy1, cx1 - cx0, y + h - cy1); return r;
		}
		Rect r; r.setAll(cx0, cy0, cx1 - cx0, cy1 - cy0); return r;
	}

	Rect containsPositionIn5Patch_withOutType(float px, float py, const Rect& centerRatio, int* geoType) const {
		float cx0 = x + w * centerRatio.x;
		float cy0 = y + h * centerRatio.y;
		float cx1 = cx0 + w * centerRatio.w;
		float cy1 = cy0 + h * centerRatio.h;

		if (px < cx0) { if (geoType) *geoType = 1; Rect r; r.setAll(x, cy0, cx0 - x, cy1 - cy0); return r; }
		if (px >= cx1) { if (geoType) *geoType = 3; Rect r; r.setAll(cx1, cy0, x + w - cx1, cy1 - cy0); return r; }
		if (py < cy0) { if (geoType) *geoType = 0; Rect r; r.setAll(cx0, y, cx1 - cx0, cy0 - y); return r; }
		if (py >= cy1) { if (geoType) *geoType = 4; Rect r; r.setAll(cx0, cy1, cx1 - cx0, y + h - cy1); return r; }
		if (geoType) *geoType = 2;
		Rect r; r.setAll(cx0, cy0, cx1 - cx0, cy1 - cy0); return r;
	}
};

inline float cross2d(float x1, float y1, float x2, float y2, float x, float y) {
	float a0 = x2 - x1;
	float a1 = y2 - y1;
	float b0 = x - x1;
	float b1 = y - y1;
	return a0 * b1 - a1 * b0;
}

inline bool isInRect(float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4, float x, float y) {
	return cross2d(x1, y1, x2, y2, x, y) * cross2d(x3, y3, x4, y4, x, y) >= 0
		&& cross2d(x2, y2, x3, y3, x, y) * cross2d(x4, y4, x1, y1, x, y) >= 0;
}

inline Rect mkRect0() {
	Rect r;
	return r;
}

inline Rect mkRect(float x, float y, float w, float h) {
	Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

inline Rect mkRectByCenterWH(float cx, float cy, float w, float h) {
	Rect r;
	r.x = cx - w / 2.0f;
	r.y = cy - h / 2.0f;
	r.w = w;
	r.h = h;
	return r;
}

inline Rect mkRectByCenterRadius(float cx, float cy, float rad) {
	Rect r;
	r.x = cx - rad;
	r.y = cy - rad;
	r.w = rad * 2;
	r.h = rad * 2;
	return r;
}
