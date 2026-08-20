#pragma once

#include "Predef.h"
#include "Vec2.h"
#include "Vec3.h"

struct Mat2d {
	float data[6] = {1, 0, 0, 1, 0, 0};

	void identity() {
		nvgTransformIdentity(this->data);
	}

	void translate(float x, float y, float z) {
		float tmp[16] = { 0 };
		nvgTransformTranslate(tmp, x, y);
		nvgTransformPremultiply(this->data, tmp);
	}

	void scale(float x, float y, float z) {


		float tmp[16] = { 0 };
		nvgTransformScale(tmp, x, y);
		nvgTransformPremultiply(this->data, tmp);
	}

	void rotate(float x, float y, float z) {

		float tmp[16] = { 0 };
		nvgTransformRotate(tmp, z);
		nvgTransformPremultiply(this->data, tmp);
	}

	void multiply(const Mat2d& b) {
		nvgTransformMultiply(this->data, b.data);
	}

	void premultiply(const Mat2d& b) {
		nvgTransformPremultiply(this->data, b.data);
	}

	void inverse() {
		float data[16];
		nvgTransformInverse(data, this->data);
		memcpy(this->data, data, sizeof(*this->data));
	}

	Mat2d inverseNew() const {
		Mat2d m = *this;
		m.inverse();
		return m;
	}

	Vec3 transformPoint(float x, float y, float z) const {
		Vec3 ret;

		nvgTransformPoint(&ret.x, &ret.y, data, x, y);
		return ret;
	}
};

inline Mat2d mkMat2d() {
	Mat2d m;
	m.identity();
	return m;
}
