#include "./Vec3.h"
#include "./Quaternion.h"
#include "./Mat.h"
#include "./Euler.h"
Vec3* Vec3::fromArray(float* array, int offset) {
	x = array[offset];
	y = array[offset + 1];
	z = array[offset + 2];
	return this;
}
float* Vec3::toArray(float* array, int offset) {

	array[offset] = x;
	array[offset + 1] = y;
	array[offset + 2] = z;

	return array;
}

Vec3* Vec3::setFromEuler(Euler& e) {

	x = e.x;
	y = e.y;
	z = e.z;

	return this;
}

Vec3* Vec3::setFromMatrixPosition(Mat& m) {
	float* e = m.data;

	x = e[12];
	y = e[13];
	z = e[14];

	return this;
}

Vec3* Vec3::applyQuaternionLocal(Quaternion& q) {

	float x = this->x;
	float y = this->y;
	float z = this->z;
	float qx = q.x;
	float qy = q.y;
	float qz = q.z;
	float qw = q.w;

	// calculate quat * vector

	float ix = qw * x + qy * z - qz * y;
	float iy = qw * y + qz * x - qx * z;
	float iz = qw * z + qx * y - qy * x;
	float iw = -qx * x - qy * y - qz * z;

	// calculate result * inverse quat

	this->x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
	this->y = iy * qw + iw * -qy + iz * -qx - ix * -qz;
	this->z = iz * qw + iw * -qz + ix * -qy - iy * -qx;

	return this;
}

Vec3 Vec3::applyMatrix4(Mat& m) {
	Vec3 r = *this;
	r.applyMatrix4Local(m);
	return r;
}

Vec3* Vec3::applyMatrix4Local(Mat& m) {

	float x = this->x;
	float y = this->y;
	float z = this->z;
	float* e = m.data;

	float w = 1 / (e[3] * x + e[7] * y + e[11] * z + e[15]);

	this->x = (e[0] * x + e[4] * y + e[8] * z + e[12]) * w;
	this->y = (e[1] * x + e[5] * y + e[9] * z + e[13]) * w;
	this->z = (e[2] * x + e[6] * y + e[10] * z + e[14]) * w;

	return this;

}
