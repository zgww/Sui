#pragma once

#include "Predef.h"
#include "Vec2.h"
#include "Vec3.h"

// 2D仿射变换 [a,b,c,d,e,f]（与nanovg布局一致）
// 点变换: x' = a*x + c*y + e;  y' = b*x + d*y + f
inline void mat2dIdentity(float* t) {
	t[0] = 1.0f; t[1] = 0.0f;
	t[2] = 0.0f; t[3] = 1.0f;
	t[4] = 0.0f; t[5] = 0.0f;
}

inline void mat2dTranslate(float* t, float tx, float ty) {
	t[0] = 1.0f; t[1] = 0.0f;
	t[2] = 0.0f; t[3] = 1.0f;
	t[4] = tx; t[5] = ty;
}

inline void mat2dScale(float* t, float sx, float sy) {
	t[0] = sx; t[1] = 0.0f;
	t[2] = 0.0f; t[3] = sy;
	t[4] = 0.0f; t[5] = 0.0f;
}

inline void mat2dRotate(float* t, float a) {
	float cs = cosf(a), sn = sinf(a);
	t[0] = cs; t[1] = sn;
	t[2] = -sn; t[3] = cs;
	t[4] = 0.0f; t[5] = 0.0f;
}

inline void mat2dSkewX(float* t, float a) {
	t[0] = 1.0f; t[1] = 0.0f;
	t[2] = tanf(a); t[3] = 1.0f;
	t[4] = 0.0f; t[5] = 0.0f;
}

inline void mat2dSkewY(float* t, float a) {
	t[0] = 1.0f; t[1] = tanf(a);
	t[2] = 0.0f; t[3] = 1.0f;
	t[4] = 0.0f; t[5] = 0.0f;
}

// t = t * s （先应用t，再应用s）
inline void mat2dMultiply(float* t, const float* s) {
	float t0 = t[0] * s[0] + t[1] * s[2];
	float t2 = t[2] * s[0] + t[3] * s[2];
	float t4 = t[4] * s[0] + t[5] * s[2] + s[4];
	t[1] = t[0] * s[1] + t[1] * s[3];
	t[3] = t[2] * s[1] + t[3] * s[3];
	t[5] = t[4] * s[1] + t[5] * s[3] + s[5];
	t[0] = t0;
	t[2] = t2;
	t[4] = t4;
}

// t = s * t （先应用s，再应用t）
inline void mat2dPremultiply(float* t, const float* s) {
	float s2[6];
	memcpy(s2, s, sizeof(float) * 6);
	mat2dMultiply(s2, t);
	memcpy(t, s2, sizeof(float) * 6);
}

inline int mat2dInverse(float* inv, const float* t) {
	double invdet, det = (double)t[0] * t[3] - (double)t[2] * t[1];
	if (det > -1e-6 && det < 1e-6) {
		mat2dIdentity(inv);
		return 0;
	}
	invdet = 1.0 / det;
	inv[0] = (float)(t[3] * invdet);
	inv[2] = (float)(-t[2] * invdet);
	inv[4] = (float)(((double)t[2] * t[5] - (double)t[3] * t[4]) * invdet);
	inv[1] = (float)(-t[1] * invdet);
	inv[3] = (float)(t[0] * invdet);
	inv[5] = (float)(((double)t[1] * t[4] - (double)t[0] * t[5]) * invdet);
	return 1;
}

inline void mat2dTransformPoint(float* dx, float* dy, const float* t, float sx, float sy) {
	*dx = sx * t[0] + sy * t[2] + t[4];
	*dy = sx * t[1] + sy * t[3] + t[5];
}

struct Mat2d {
	float data[6] = {1, 0, 0, 1, 0, 0};

	void identity() {
		mat2dIdentity(this->data);
	}

	void translate(float x, float y, float z) {
		float tmp[6] = { 0 };
		mat2dTranslate(tmp, x, y);
		mat2dPremultiply(this->data, tmp);
	}

	void scale(float x, float y, float z) {


		float tmp[16] = { 0 };
		mat2dScale(tmp, x, y);
		mat2dPremultiply(this->data, tmp);
	}

	void rotate(float x, float y, float z) {

		float tmp[16] = { 0 };
		mat2dRotate(tmp, z);
		mat2dPremultiply(this->data, tmp);
	}

	void multiply(const Mat2d& b) {
		mat2dMultiply(this->data, b.data);
	}

	void premultiply(const Mat2d& b) {
		mat2dPremultiply(this->data, b.data);
	}

	void inverse() {
		float data[16];
		mat2dInverse(data, this->data);
		memcpy(this->data, data, sizeof(*this->data));
	}

	Mat2d inverseNew() const {
		Mat2d m = *this;
		m.inverse();
		return m;
	}

	Vec3 transformPoint(float x, float y, float z) const {
		Vec3 ret;

		mat2dTransformPoint(&ret.x, &ret.y, data, x, y);
		return ret;
	}
};

inline Mat2d mkMat2d() {
	Mat2d m;
	m.identity();
	return m;
}
