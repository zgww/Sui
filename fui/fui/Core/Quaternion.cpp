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

Quaternion* Quaternion::setFromEuler(Euler& euler) {
	auto& self = *this;
	float x = euler.x;
	float y = euler.y;
	float z = euler.z;
		const char* order = euler.order;

	// http://www.mathworks.com/matlabcentral/fileexchange/
	// 	20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors/
	//	content/SpinCalc.m


	float c1 = cos(x / 2.0);
	float c2 = cos(y / 2.0);
	float c3 = cos(z / 2.0);

	float s1 = sin(x / 2.0);
	float s2 = sin(y / 2.0);
	float s3 = sin(z / 2.0);


	if (strcmp(order, "XYZ") == 0) {
		self.x = s1 * c2 * c3 + c1 * s2 * s3;
		self.y = c1 * s2 * c3 - s1 * c2 * s3;
		self.z = c1 * c2 * s3 + s1 * s2 * c3;
		self.w = c1 * c2 * c3 - s1 * s2 * s3;
	}

	else if (strcmp(order, "YXZ") == 0) {
		self.x = s1 * c2 * c3 + c1 * s2 * s3;
		self.y = c1 * s2 * c3 - s1 * c2 * s3;
		self.z = c1 * c2 * s3 - s1 * s2 * c3;
		self.w = c1 * c2 * c3 + s1 * s2 * s3;
	}

	else if (strcmp(order, "ZXY") == 0 ){
		self.x = s1 * c2 * c3 - c1 * s2 * s3;
		self.y = c1 * s2 * c3 + s1 * c2 * s3;
		self.z = c1 * c2 * s3 + s1 * s2 * c3;
		self.w = c1 * c2 * c3 - s1 * s2 * s3;
	}

	else if (strcmp(order, "ZYX") == 0) {
		self.x = s1 * c2 * c3 - c1 * s2 * s3;
		self.y = c1 * s2 * c3 + s1 * c2 * s3;
		self.z = c1 * c2 * s3 - s1 * s2 * c3;
		self.w = c1 * c2 * c3 + s1 * s2 * s3;
	}

	else if (strcmp(order, "YZX") == 0) {
		self.x = s1 * c2 * c3 + c1 * s2 * s3;
		self.y = c1 * s2 * c3 + s1 * c2 * s3;
		self.z = c1 * c2 * s3 - s1 * s2 * c3;
		self.w = c1 * c2 * c3 - s1 * s2 * s3;
	}

	else if ( strcmp(order, "XZY") == 0) {
		self.x = s1 * c2 * c3 - c1 * s2 * s3;
		self.y = c1 * s2 * c3 - s1 * c2 * s3;
		self.z = c1 * c2 * s3 + s1 * s2 * c3;
		self.w = c1 * c2 * c3 + s1 * s2 * s3;
	}

	else {
		printf("Quaternion: .setFromEuler() encountered an unknown order: %s", order);
	}


	// if ( update != false ) self._onChangeCallback();

	return this;

}
