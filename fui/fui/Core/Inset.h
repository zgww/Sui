#pragma once

#include "Predef.h"

struct Inset {
	float left = 0;
	float top = 0;
	float right = 0;
	float bottom = 0;

	void setAll(float v) {
		left = v;
		top = v;
		right = v;
		bottom = v;
	}
	void setAxis(float v, float h) {
		left = h;
		right = h;
		top = v;
		bottom = v;
	}
	void setHor(float v) {
		left = v;
		right = v;
	}
	void setVer(float v) {
		top = v;
		bottom = v;
	}
	float hor() const { return left + right; }
	float ver() const { return top + bottom; }
	void invert() {
		left = -left;
		top = -top;
		right = -right;
		bottom = -bottom;
	}
};

inline Inset mkInset0() {
	Inset ret;
	return ret;
}

inline Inset mkInset(float t, float r, float b, float l) {
	Inset ret;
	ret.top = t;
	ret.right = r;
	ret.bottom = b;
	ret.left = l;
	return ret;
}
