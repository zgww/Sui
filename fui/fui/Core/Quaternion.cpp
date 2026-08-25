#include "./Quaternion.h"
#include "./Mat.h"

inline Quaternion* Quaternion::setFromRotationMatrix(Mat& m) {

	// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

	// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

	float* te = m.data;

	float m11 = te[0]; float m12 = te[4]; float m13 = te[8];
	float m21 = te[1]; float m22 = te[5]; float m23 = te[9];
	float m31 = te[2]; float m32 = te[6]; float m33 = te[10];

	float trace = m11 + m22 + m33;

	if (trace > 0) {

		float s = 0.5 / sqrt(trace + 1.0);

		this->w = 0.25 / s;
		this->x = (m32 - m23) * s;
		this->y = (m13 - m31) * s;
		this->z = (m21 - m12) * s;

	}
	else if (m11 > m22 && m11 > m33) {

		float s = 2.0 * sqrt(1.0 + m11 - m22 - m33);

		this->w = (m32 - m23) / s;
		this->x = 0.25 * s;
		this->y = (m12 + m21) / s;
		this->z = (m13 + m31) / s;

	}
	else if (m22 > m33) {

		float s = 2.0 * sqrt(1.0 + m22 - m11 - m33);

		this->w = (m13 - m31) / s;
		this->x = (m12 + m21) / s;
		this->y = 0.25 * s;
		this->z = (m23 + m32) / s;

	}
	else {

		float s = 2.0 * sqrt(1.0 + m33 - m11 - m22);

		this->w = (m21 - m12) / s;
		this->x = (m13 + m31) / s;
		this->y = (m23 + m32) / s;
		this->z = 0.25 * s;

	}

	// this->_onChangeCallback();

	return this;
}

Quaternion* Quaternion::premultiplyLocal(Quaternion q) {

	return multiplyQuaternionsLocal(q, *this);

}

Quaternion* Quaternion::multiplyQuaternionsLocal(Quaternion a, Quaternion b) {

	// from http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/code/index.htm

	float qax = a.x; float qay = a.y; float qaz = a.z; float qaw = a.w;
	float qbx = b.x; float qby = b.y; float qbz = b.z; float qbw = b.w;

	this->x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
	this->y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
	this->z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
	this->w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

	// self._onChangeCallback();

	return this;

}
