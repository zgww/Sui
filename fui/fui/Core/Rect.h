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
	Rect containsPositionIn5Patch(float px, float py, Rect centerRect);

	//是否包含位置在9宫格内
	// 0 0 0
	// 1 2 3
	// 4 4 4
	// -1 表示 不包含
	// [centerRect]表示中间区域，以比例的方式表示
	// [return] 返回以比例表示的rect
	Rect containsPositionIn5Patch_withOutType(float px, float py, Rect centerRect, int* outType);

	//是否包含位置在9宫格内
	// 0 1 2
	// 3 4 5
	// 6 7 8
	// -1 表示 不包含
	Vec2 containsPositionIn9Patch(float px, float py);


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
