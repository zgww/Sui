#pragma once

#include "Predef.h"
#include "Vec2.h"
#include "Vec3.h"

struct Mat2d {
	float data[6] = {1, 0, 0, 1, 0, 0};

	void identity() {
		data[0] = 1; data[1] = 0;
		data[2] = 0; data[3] = 1;
		data[4] = 0; data[5] = 0;
	}

	void translate(float x, float y, float z) {
		(void)z;
		data[4] += data[0] * x + data[2] * y;
		data[5] += data[1] * x + data[3] * y;
	}

	void scale(float x, float y, float z) {
		(void)z;
		data[0] *= x;
		data[1] *= x;
		data[2] *= y;
		data[3] *= y;
	}

	void rotate(float x, float y, float z) {
		(void)x;
		(void)y;
		float c = cosf(z);
		float s = sinf(z);
		float a0 = data[0], a1 = data[1];
		float a2 = data[2], a3 = data[3];
		data[0] = a0 * c + a2 * s;
		data[1] = a1 * c + a3 * s;
		data[2] = a0 * -s + a2 * c;
		data[3] = a1 * -s + a3 * c;
	}

	void multiply(const Mat2d& b) {
		float a0 = data[0], a1 = data[1], a2 = data[2], a3 = data[3], a4 = data[4], a5 = data[5];
		data[0] = a0 * b.data[0] + a2 * b.data[1];
		data[1] = a1 * b.data[0] + a3 * b.data[1];
		data[2] = a0 * b.data[2] + a2 * b.data[3];
		data[3] = a1 * b.data[2] + a3 * b.data[3];
		data[4] = a0 * b.data[4] + a2 * b.data[5] + a4;
		data[5] = a1 * b.data[4] + a3 * b.data[5] + a5;
	}

	void premultiply(const Mat2d& b) {
		Mat2d tmp = b;
		tmp.multiply(*this);
		*this = tmp;
	}

	void inverse() {
		float a = data[0], b = data[1], c = data[2], d = data[3], e = data[4], f = data[5];
		float det = a * d - b * c;
		if (eqFloat(det, 0)) {
			identity();
			return;
		}
		float invDet = 1.0f / det;
		data[0] = d * invDet;
		data[1] = -b * invDet;
		data[2] = -c * invDet;
		data[3] = a * invDet;
		data[4] = (c * f - d * e) * invDet;
		data[5] = (b * e - a * f) * invDet;
	}

	Mat2d inverseNew() const {
		Mat2d m = *this;
		m.inverse();
		return m;
	}

	Vec3 transformPoint(float x, float y, float z) const {
		Vec3 ret;
		ret.x = data[0] * x + data[2] * y + data[4] * z;
		ret.y = data[1] * x + data[3] * y + data[5] * z;
		ret.z = z;
		return ret;
	}
};

inline Mat2d mkMat2d() {
	Mat2d m;
	m.identity();
	return m;
}
