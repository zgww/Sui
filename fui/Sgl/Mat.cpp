module;
#include "Core/Vec3.h"
#include "Core/Euler.h"
#include "Core/Quaternion.h"

module Sgl;

Mat Mat::extractYRotationMatrix() {
	Quaternion q;
	this->decompose(nullptr, &q, nullptr);
	Vec3 forward = mkVec3(0, 0, -1);
	//q.applyToVec3Local(forward);
	forward.applyQuaternionLocal(q);
	forward.y = 0; // 
	forward.normalizeLocal();

	Quaternion q2;
	q2.setFromUnitVectors(mkVec3(0, 0, -1), forward);
	Mat ret;
	ret.makeRotationFromQuaternion(q2);
	return ret;
}
Mat* Mat::makeRotationFromQuaternion(Quaternion q) {
	Vec3 _zero = mkVec3(0, 0, 0);
	Vec3 _one = mkVec3(1, 1, 1);

	return this->compose(_zero, q, _one);

}
Mat* Mat::compose(Vec3 position, Quaternion& quaternion, Vec3 scale) {

	float* te = this->data;
	float x = quaternion.x; float y = quaternion.y; float z = quaternion.z; float w = quaternion.w;
	float x2 = x + x; float	y2 = y + y; float z2 = z + z;
	float xx = x * x2; float xy = x * y2; float xz = x * z2;
	float yy = y * y2; float yz = y * z2; float zz = z * z2;
	float wx = w * x2; float wy = w * y2; float wz = w * z2;

	float sx = scale.x; float sy = scale.y; float sz = scale.z;

	te[0] = (1 - (yy + zz)) * sx;
	te[1] = (xy + wz) * sx;
	te[2] = (xz - wy) * sx;
	te[3] = 0;

	te[4] = (xy - wz) * sy;
	te[5] = (1 - (xx + zz)) * sy;
	te[6] = (yz + wx) * sy;
	te[7] = 0;

	te[8] = (xz + wy) * sz;
	te[9] = (yz - wx) * sz;
	te[10] = (1 - (xx + yy)) * sz;
	te[11] = 0;

	te[12] = position.x;
	te[13] = position.y;
	te[14] = position.z;
	te[15] = 1;

	return this;
}


Mat* Mat::decompose(Vec3* position, Quaternion* quaternion, Vec3* scale) {

	float* te = this->data;

	Vec3 _v1;
	Mat _m1;

	float sx = _v1.set(te[0], te[1], te[2])->length();
	float sy = _v1.set(te[4], te[5], te[6])->length();
	float sz = _v1.set(te[8], te[9], te[10])->length();

	// if determine is negative, we need to invert one scale
	float det = this->determinant();
	if (det < 0) { sx = -sx; }

	if (position != nullptr) {
		position->x = te[12];
		position->y = te[13];
		position->z = te[14];
	}

	// scale the rotation part
	_m1.copy(*this);

	float invSX = 1 / sx;
	float invSY = 1 / sy;
	float invSZ = 1 / sz;

	_m1.data[0] *= invSX;
	_m1.data[1] *= invSX;
	_m1.data[2] *= invSX;

	_m1.data[4] *= invSY;
	_m1.data[5] *= invSY;
	_m1.data[6] *= invSY;

	_m1.data[8] *= invSZ;
	_m1.data[9] *= invSZ;
	_m1.data[10] *= invSZ;

	if (quaternion != nullptr) {
		*quaternion = _m1.toQuaternionAsRotationMatrix();
		//quaternion->setFromRotationMatrix(_m1);
	}

	if (scale != nullptr) {
		scale->x = sx;
		scale->y = sy;
		scale->z = sz;
	}

	return this;
}

Mat* Mat::makeRotationFromEuler(Euler& euler) {

	float* te = this->data;

	float x = euler.x;
	float y = euler.y;
	float z = euler.z;
	float a = cos(x); float b = sin(x);
	float c = cos(y); float d = sin(y);
	float e = cos(z); float f = sin(z);

	if (euler.isXYZ()) {

		float ae = a * e; float af = a * f;float be = b * e;float bf = b * f;

		te[0] = c * e;
		te[4] = -c * f;
		te[8] = d;

		te[1] = af + be * d;
		te[5] = ae - bf * d;
		te[9] = -b * c;

		te[2] = bf - ae * d;
		te[6] = be + af * d;
		te[10] = a * c;

	}
	else if (euler.isYXZ()) {

		float ce = c * e;float cf = c * f;float de = d * e;float df = d * f;

		te[0] = ce + df * b;
		te[4] = de * b - cf;
		te[8] = a * d;

		te[1] = a * f;
		te[5] = a * e;
		te[9] = -b;

		te[2] = cf * b - de;
		te[6] = df + ce * b;
		te[10] = a * c;

	}
	else if (euler.isZXY()) {

		float ce = c * e;float cf = c * f;float de = d * e;float df = d * f;

		te[0] = ce - df * b;
		te[4] = -a * f;
		te[8] = de + cf * b;

		te[1] = cf + de * b;
		te[5] = a * e;
		te[9] = df - ce * b;

		te[2] = -a * d;
		te[6] = b;
		te[10] = a * c;

	}
	else if (euler.isZYX()) {

		float ae = a * e;float af = a * f;float be = b * e;float bf = b * f;

		te[0] = c * e;
		te[4] = be * d - af;
		te[8] = ae * d + bf;

		te[1] = c * f;
		te[5] = bf * d + ae;
		te[9] = af * d - be;

		te[2] = -d;
		te[6] = b * c;
		te[10] = a * c;

	}
	else if (euler.isYZX()) {

		float ac = a * c;float ad = a * d;float bc = b * c;float bd = b * d;

		te[0] = c * e;
		te[4] = bd - ac * f;
		te[8] = bc * f + ad;

		te[1] = f;
		te[5] = a * e;
		te[9] = -b * e;

		te[2] = -d * e;
		te[6] = ad * f + bc;
		te[10] = ac - bd * f;

	}
	else if (euler.isXZY()) {

		float ac = a * c;float ad = a * d;float bc = b * c;float bd = b * d;

		te[0] = c * e;
		te[4] = -f;
		te[8] = d * e;

		te[1] = ac * f + bd;
		te[5] = a * e;
		te[9] = ad * f - bc;

		te[2] = bc * f - ad;
		te[6] = b * e;
		te[10] = bd * f + ac;

	}

	// bottom row
	te[3] = 0;
	te[7] = 0;
	te[11] = 0;

	// last column
	te[12] = 0;
	te[13] = 0;
	te[14] = 0;
	te[15] = 1;

	return this;

}