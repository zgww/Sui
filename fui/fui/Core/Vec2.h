#pragma once

#include "Predef.h"

struct Mat3;

struct IntVec2 {
	int x = 0;
	int y = 0;
};

struct Vec2 {
	float x = 0;
	float y = 0;

	std::string toString() const {
		char b[128];
		snprintf(b, sizeof(b), "Vec2(%f,%f)", x, y);
		return std::string(b);
	}
	float width() const { return x; }
	float height() const { return y; }

	Vec2* set(float x, float y) {
		this->x = x;
		this->y = y;
		return this;
	}
	Vec2* setScalar(float scalar) {
		x = scalar;
		y = scalar;
		return this;
	}
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }

	void setComponent(int index, float value) {
		if (index == 0) x = value;
		else if (index == 1) y = value;
	}
	float getComponent(int index) const {
		if (index == 0) return x;
		else if (index == 1) return y;
		return 0.0f;
	}

	Vec2 clone() const { return *this; }

	Vec2* copy(const Vec2& v) {
		x = v.x;
		y = v.y;
		return this;
	}

	Vec2* addLocal(const Vec2& v) {
		x += v.x;
		y += v.y;
		return this;
	}
	Vec2* addScalarLocal(float s) {
		x += s;
		y += s;
		return this;
	}
	Vec2* addVectorsLocal(const Vec2& a, const Vec2& b) {
		x = a.x + b.x;
		y = a.y + b.y;
		return this;
	}
	Vec2* addScaledVectorLocal(const Vec2& v, float s) {
		x += v.x * s;
		y += v.y * s;
		return this;
	}

	Vec2* subLocal(const Vec2& v) {
		x -= v.x;
		y -= v.y;
		return this;
	}
	Vec2* subScalarLocal(float s) {
		x -= s;
		y -= s;
		return this;
	}
	Vec2* subVectorsLocal(const Vec2& a, const Vec2& b) {
		x = a.x - b.x;
		y = a.y - b.y;
		return this;
	}

	Vec2* multiplyLocal(const Vec2& v) {
		x *= v.x;
		y *= v.y;
		return this;
	}
	Vec2* multiplyScalarLocal(float scalar) {
		x *= scalar;
		y *= scalar;
		return this;
	}

	Vec2* divideLocal(const Vec2& v) {
		x /= v.x;
		y /= v.y;
		return this;
	}
	Vec2* divideScalarLocal(float scalar) {
		return multiplyScalarLocal(1.0f / scalar);
	}

	Vec2* applyMatrix3Local(const Mat3& m);

	Vec2* minLocal(const Vec2& v) {
		x = minFloat(x, v.x);
		y = minFloat(y, v.y);
		return this;
	}
	Vec2* maxLocal(const Vec2& v) {
		x = maxFloat(x, v.x);
		y = maxFloat(y, v.y);
		return this;
	}

	Vec2* floorLocal() {
		x = floorFloat(x);
		y = floorFloat(y);
		return this;
	}
	Vec2* ceilLocal() {
		x = ceilFloat(x);
		y = ceilFloat(y);
		return this;
	}
	Vec2* roundLocal() {
		x = roundFloat(x);
		y = roundFloat(y);
		return this;
	}
	Vec2* roundToZeroLocal() {
		x = (x < 0) ? ceilFloat(x) : floorFloat(x);
		y = (y < 0) ? ceilFloat(y) : floorFloat(y);
		return this;
	}
	Vec2* negateLocal() {
		x = -x;
		y = -y;
		return this;
	}

	float dot(const Vec2& v) const {
		return x * v.x + y * v.y;
	}
	float cross(const Vec2& v) const {
		return x * v.y - y * v.x;
	}
	float lengthSq() const {
		return x * x + y * y;
	}
	float length() const {
		return sqrtf(x * x + y * y);
	}
	float manhattanLength() const {
		return absFloat(x) + absFloat(y);
	}

	Vec2* normalizeLocal() {
		float l = length();
		return divideScalarLocal(eqFloat(l, 0) ? 1 : l);
	}

	float angle() const {
		return atan2f(-y, -x) + PIf;
	}

	float angleTo(const Vec2& v) const {
		float denominator = sqrtf(lengthSq() * v.lengthSq());
		if (eqFloat(denominator, 0)) {
			return PIf / 2.0f;
		}
		float theta = dot(v) / denominator;
		return acosf(clampFloat(theta, -1, 1));
	}

	float distanceTo(const Vec2& v) const {
		return sqrtf(distanceToSquared(v));
	}
	float distanceToSquared(const Vec2& v) const {
		float dx = x - v.x;
		float dy = y - v.y;
		return dx * dx + dy * dy;
	}
	float manhattanDistanceTo(const Vec2& v) const {
		return absFloat(x - v.x) + absFloat(y - v.y);
	}

	Vec2* setLengthLocal(float len) {
		return normalizeLocal()->multiplyScalarLocal(len);
	}
	Vec2* lerpLocal(const Vec2& v, float alpha) {
		x += (v.x - x) * alpha;
		y += (v.y - y) * alpha;
		return this;
	}
	Vec2* lerpVectorsLocal(const Vec2& v1, const Vec2& v2, float alpha) {
		x = v1.x + (v2.x - v1.x) * alpha;
		y = v1.y + (v2.y - v1.y) * alpha;
		return this;
	}

	Vec2* fromArray(const float* array, int offset) {
		x = array[offset];
		y = array[offset + 1];
		return this;
	}
	float* toArray(float* array, int offset) const {
		array[offset] = x;
		array[offset + 1] = y;
		return array;
	}

	Vec2* rotateAroundLocal(const Vec2& center, float ang) {
		float c = cosf(ang);
		float s = sinf(ang);
		float dx = x - center.x;
		float dy = y - center.y;
		x = dx * c - dy * s + center.x;
		y = dx * s + dy * c + center.y;
		return this;
	}

	Vec2* randomLocal() {
		x = (float)rand() / RAND_MAX;
		y = (float)rand() / RAND_MAX;
		return this;
	}

	Vec2 scale(float f) const {
		Vec2 ret;
		ret.x = x * f;
		ret.y = y * f;
		return ret;
	}

	Vec2* clampLengthLocal(float mn, float mx) {
		float l = length();
		divideScalarLocal(eqFloat(l, 0) ? 1 : l)->multiplyScalarLocal(
			maxFloat(mn, minFloat(mx, l)));
		return this;
	}
	void clampLocal(const Vec2& mn, const Vec2& mx) {
		x = maxFloat(mn.x, minFloat(mx.x, x));
		y = maxFloat(mn.y, minFloat(mx.y, y));
	}
	Vec2 clamp(const Vec2& mn, const Vec2& mx) const {
		Vec2 r;
		r.x = maxFloat(mn.x, minFloat(mx.x, x));
		r.y = maxFloat(mn.y, minFloat(mx.y, y));
		return r;
	}
	Vec2* clampScalarLocal(float minVal, float maxVal) {
		x = maxFloat(minVal, minFloat(maxVal, x));
		y = maxFloat(minVal, minFloat(maxVal, y));
		return this;
	}
	Vec2 clampScalar(float minVal, float maxVal) const {
		Vec2 r;
		r.x = maxFloat(minVal, minFloat(maxVal, x));
		r.y = maxFloat(minVal, minFloat(maxVal, y));
		return r;
	}

	Vec2 add(const Vec2& b) const {
		Vec2 ret;
		ret.x = x + b.x;
		ret.y = y + b.y;
		return ret;
	}
	Vec2 sub(const Vec2& b) const {
		Vec2 ret;
		ret.x = x - b.x;
		ret.y = y - b.y;
		return ret;
	}

	float radToXAxis() const {
		return atan2f(y, x);
	}

	bool equals(const Vec2& b) const {
		return fabsf(x - b.x) < EPSILON && fabsf(y - b.y) < EPSILON;
	}
};

inline Vec2 mkVec2(float x, float y) {
	Vec2 v;
	v.x = x;
	v.y = y;
	return v;
}

inline Vec2 mkVec2_0() {
	Vec2 v;
	v.x = 0;
	v.y = 0;
	return v;
}
