#pragma once

#include "Predef.h"

struct Mat3;

struct Vec4 {
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1;

	std::string toString() const {
		char b[128];
		snprintf(b, sizeof(b), "Vec4(%f,%f,%f,%f)", x, y, z, w);
		return std::string(b);
	}

	Vec4* set(float x, float y, float z, float w) {
		this->x = x; this->y = y; this->z = z; this->w = w;
		return this;
	}
	Vec4* setScalar(float s) { x = y = z = w = s; return this; }

	Vec4 clone() const { return *this; }
	Vec4* copy(const Vec4& v) { x = v.x; y = v.y; z = v.z; w = v.w; return this; }

	Vec4* addLocal(const Vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return this; }
	Vec4* addScalarLocal(float s) { x += s; y += s; z += s; w += s; return this; }
	Vec4* addVectorsLocal(const Vec4& a, const Vec4& b) {
		x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; return this;
	}
	Vec4* subLocal(const Vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return this; }
	Vec4* subScalarLocal(float s) { x -= s; y -= s; z -= s; w -= s; return this; }
	Vec4* subVectorsLocal(const Vec4& a, const Vec4& b) {
		x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; return this;
	}
	Vec4* multiplyScalarLocal(float s) { x *= s; y *= s; z *= s; w *= s; return this; }
	Vec4* divideScalarLocal(float s) { return multiplyScalarLocal(1.0f / s); }

	Vec4* negateLocal() { x = -x; y = -y; z = -z; w = -w; return this; }

	float dot(const Vec4& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
	float lengthSq() const { return x * x + y * y + z * z + w * w; }
	float length() const { return sqrtf(lengthSq()); }
	float manhattanLength() const { return absFloat(x) + absFloat(y) + absFloat(z) + absFloat(w); }

	Vec4* normalizeLocal() {
		float l = length();
		return divideScalarLocal(eqFloat(l, 0) ? 1 : l);
	}

	Vec4* setLengthLocal(float len) {
		return normalizeLocal()->multiplyScalarLocal(len);
	}

	Vec4* lerpLocal(const Vec4& v, float alpha) {
		x += (v.x - x) * alpha; y += (v.y - y) * alpha;
		z += (v.z - z) * alpha; w += (v.w - w) * alpha;
		return this;
	}

	bool equals(const Vec4& b) const {
		return fabsf(x - b.x) < EPSILON && fabsf(y - b.y) < EPSILON &&
		       fabsf(z - b.z) < EPSILON && fabsf(w - b.w) < EPSILON;
	}

	Vec4* fromArray(const float* array, int offset) {
		x = array[offset]; y = array[offset+1]; z = array[offset+2]; w = array[offset+3];
		return this;
	}
	const float* toArray(float* array, int offset) const {
		array[offset] = x; array[offset+1] = y; array[offset+2] = z; array[offset+3] = w;
		return array;
	}

	Vec4* applyMat3Local(const Mat3& m);
};

inline Vec4 mkVec4(float x, float y, float z, float w) {
	Vec4 v; v.x = x; v.y = y; v.z = z; v.w = w; return v;
}
