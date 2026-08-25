#include "./Euler.h"

#include "./Mat.h"

Euler* Euler::set(float x, float y, float z, const char* order) {

	this->x = x;
	this->y = y;
	this->z = z;
	this->order = order == nullptr ? Euler_Default : order;

	// this->_onChangeCallback();

	return this;
}

Euler* Euler::copy(Euler euler) {

	this->x = euler.x;
	this->y = euler.y;
	this->z = euler.z;
	this->order = euler.order;

	// this->_onChangeCallback();

	return this;

}

Euler* Euler::setFromRotationMatrix(Mat& m, const char* order) {
	if (order == nullptr) {
		order = Euler_Default;
	}

	// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

	float* te = m.data;
	float m11 = te[0]; float m12 = te[4]; float m13 = te[8];
	float m21 = te[1]; float m22 = te[5]; float m23 = te[9];
	float m31 = te[2]; float m32 = te[6]; float m33 = te[10];


	if (strcmp(order, "XYZ") == 0) {
		this->y = asin(clampFloat(m13, -1, 1));

		if (absFloat(m13) < 0.9999999) {

			this->x = atan2(-m23, m33);
			this->z = atan2(-m12, m11);

		}
		else {

			this->x = atan2(m32, m22);
			this->z = 0;

		}
	}

	else if (strcmp(order, "YXZ") == 0) {

		this->x = asin(-clampFloat(m23, -1, 1));

		if (absFloat(m23) < 0.9999999) {

			this->y = atan2(m13, m33);
			this->z = atan2(m21, m22);

		}
		else {

			this->y = atan2(-m31, m11);
			this->z = 0;

		}

	}

	else if (strcmp(order, "ZXY") == 0) {
		this->x = asin(clampFloat(m32, -1, 1));

		if (absFloat(m32) < 0.9999999) {

			this->y = atan2(-m31, m33);
			this->z = atan2(-m12, m22);
		}
		else {
			this->y = 0;
			this->z = atan2(m21, m11);
		}

	}

	else if (strcmp(order, "ZYX") == 0) {

		this->y = asin(-clampFloat(m31, -1, 1));

		if (absFloat(m31) < 0.9999999) {
			this->x = atan2(m32, m33);
			this->z = atan2(m21, m11);
		}
		else {
			this->x = 0;
			this->z = atan2(-m12, m22);
		}
	}

	else if (strcmp(order, "YZX") == 0) {
		this->z = asin(clampFloat(m21, -1, 1));

		if (absFloat(m21) < 0.9999999) {

			this->x = atan2(-m23, m22);
			this->y = atan2(-m31, m11);

		}
		else {
			this->x = 0;
			this->y = atan2(m13, m33);
		}
	}

	else if (strcmp(order, "XZY") == 0) {

		this->z = asin(-clampFloat(m12, -1, 1));

		if (absFloat(m12) < 0.9999999) {

			this->x = atan2(m32, m22);
			this->y = atan2(m13, m11);

		}
		else {

			this->x = atan2(-m23, m33);
			this->y = 0;

		}

	}

	else {
		printf(" setFromRotationMatrix() encountered an unknown order::%s ", order);
	}

	this->order = order;
	// if ( update == true ) this->_onChangeCallback();

	return this;

}

Euler* Euler::setFromQuaternion(Quaternion q, const char* order) {
	Mat _matrix;

	_matrix.makeRotationFromQuaternion(q);

	return this->setFromRotationMatrix(_matrix, order);

}

Euler* Euler::setFromVector3(Vec3 v, const char* order) {

	return this->set(v.x, v.y, v.z, order);

}

Euler* Euler::reorder(const char* newOrder) {
	// WARNING: self discards revolution information -bhouston
	Quaternion q;
	q.setFromEuler(*this);
	return this->setFromQuaternion(q, newOrder);
}

bool Euler::equals(Euler euler) {

	return eqFloat(euler.x, this->x)
		&& eqFloat(euler.y, this->y)
		&& eqFloat(euler.z, this->z) && (strcmp(euler.order, this->order) == 0);

}

Euler* Euler::fromArray(float* array) {

	this->x = array[0];
	this->y = array[1];
	this->z = array[2];
	// if ( array[ 3 ] !== undefined ) this->_order = array[ 3 ];

	// this->_onChangeCallback();

	return this;
}

float* Euler::toArray(float* array, int offset) {
	array[offset] = this->x;
	array[offset + 1] = this->y;
	array[offset + 2] = this->z;
	// array[ offset + 3 ] = this->_order;
	return array;
}
