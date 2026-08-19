#pragma once

#include "Predef.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

struct Mat3 {
	float elements[9] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};

	Mat3() = default;

	Mat3* set(float n11, float n12, float n13,
	          float n21, float n22, float n23,
	          float n31, float n32, float n33) {
		elements[0] = n11; elements[3] = n12; elements[6] = n13;
		elements[1] = n21; elements[4] = n22; elements[7] = n23;
		elements[2] = n31; elements[5] = n32; elements[8] = n33;
		return this;
	}

	Mat3* identity() {
		return set(1,0,0, 0,1,0, 0,0,1);
	}

	Mat3* copy(const Mat3& m) {
		for (int i = 0; i < 9; i++) elements[i] = m.elements[i];
		return this;
	}

	Mat3 clone() const { Mat3 r; r.copy(*this); return r; }

	Mat3* multiplyLocal(const Mat3& m) {
		const float* a = elements;
		const float* b = m.elements;
		float out[9];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				out[i * 3 + j] = a[0 * 3 + j] * b[i * 3 + 0]
				              + a[1 * 3 + j] * b[i * 3 + 1]
				              + a[2 * 3 + j] * b[i * 3 + 2];
			}
		}
		for (int i = 0; i < 9; i++) elements[i] = out[i];
		return this;
	}

	Mat3* premultiplyLocal(const Mat3& m) {
		const float* a = m.elements;
		const float* b = elements;
		float out[9];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				out[i * 3 + j] = a[0 * 3 + j] * b[i * 3 + 0]
				              + a[1 * 3 + j] * b[i * 3 + 1]
				              + a[2 * 3 + j] * b[i * 3 + 2];
			}
		}
		for (int i = 0; i < 9; i++) elements[i] = out[i];
		return this;
	}

	Mat3* multiplyMatricesLocal(const Mat3& a, const Mat3& b) {
		const float* ae = a.elements;
		const float* be = b.elements;
		float out[9];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				out[i * 3 + j] = ae[0 * 3 + j] * be[i * 3 + 0]
				              + ae[1 * 3 + j] * be[i * 3 + 1]
				              + ae[2 * 3 + j] * be[i * 3 + 2];
			}
		}
		for (int i = 0; i < 9; i++) elements[i] = out[i];
		return this;
	}

	Mat3* scaleLocal(float s) {
		for (int i = 0; i < 9; i++) elements[i] *= s;
		return this;
	}

	float determinant() const {
		const float* e = elements;
		return e[0] * (e[4]*e[8] - e[7]*e[5])
		     - e[3] * (e[1]*e[8] - e[7]*e[2])
		     + e[6] * (e[1]*e[5] - e[4]*e[2]);
	}

	Mat3* invertLocal() {
		const float* e = elements;
		float n11 = e[0], n12 = e[3], n13 = e[6];
		float n21 = e[1], n22 = e[4], n23 = e[7];
		float n31 = e[2], n32 = e[5], n33 = e[8];
		float det = n11 * (n22*n33 - n23*n32) - n12 * (n21*n33 - n23*n31) + n13 * (n21*n32 - n22*n31);
		if (eqFloat(det, 0)) return identity();
		float invDet = 1.0f / det;
		elements[0] = (n22*n33 - n23*n32) * invDet;
		elements[3] = (n13*n32 - n12*n33) * invDet;
		elements[6] = (n12*n23 - n13*n22) * invDet;
		elements[1] = (n23*n31 - n21*n33) * invDet;
		elements[4] = (n11*n33 - n13*n31) * invDet;
		elements[7] = (n13*n21 - n11*n23) * invDet;
		elements[2] = (n21*n32 - n22*n31) * invDet;
		elements[5] = (n12*n31 - n11*n32) * invDet;
		elements[8] = (n11*n22 - n12*n21) * invDet;
		return this;
	}

	Mat3* transposeLocal() {
		float tmp;
		tmp = elements[1]; elements[1] = elements[3]; elements[3] = tmp;
		tmp = elements[2]; elements[2] = elements[6]; elements[6] = tmp;
		tmp = elements[5]; elements[5] = elements[7]; elements[7] = tmp;
		return this;
	}

	Vec3* applyToVec3(Vec3* v) const {
		const float* e = elements;
		float x = v->x, y = v->y, z = v->z;
		v->x = e[0]*x + e[3]*y + e[6]*z;
		v->y = e[1]*x + e[4]*y + e[7]*z;
		v->z = e[2]*x + e[5]*y + e[8]*z;
		return v;
	}

	Mat3* fromArray(const float* array, int offset) {
		for (int i = 0; i < 9; i++) elements[i] = array[offset + i];
		return this;
	}
	const float* toArray(float* array, int offset) const {
		for (int i = 0; i < 9; i++) array[offset + i] = elements[i];
		return array;
	}
};

inline Vec2* Vec2::applyMatrix3Local(const Mat3& m) {
	const float* e = m.elements;
	float x = this->x, y = this->y;
	this->x = e[0]*x + e[3]*y + e[6];
	this->y = e[1]*x + e[4]*y + e[7];
	return this;
}

inline Vec4* Vec4::applyMat3Local(const Mat3& m) {
	const float* e = m.elements;
	float x = this->x, y = this->y, z = this->z;
	this->x = e[0]*x + e[3]*y + e[6]*z;
	this->y = e[1]*x + e[4]*y + e[7]*z;
	this->z = e[2]*x + e[5]*y + e[8]*z;
	return this;
}
