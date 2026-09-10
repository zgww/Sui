#include "./Vec3.h"
#include "./Mat3.h"
#include "./Quaternion.h"
#include "./Mat.h"
#include "./Euler.h"

#include <rttr/registration>
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

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Vec3>("Vec3")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Vec3(*)(float, float, float)>(&mkVec3))
		.property("x", &Vec3::x)
		.property("y", &Vec3::y)
		.property("z", &Vec3::z)
		.method("toString", &Vec3::toString)
		.method("width", &Vec3::width)
		.method("height", &Vec3::height)
		.method("fromArray", &Vec3::fromArray)
		.method("toArray", &Vec3::toArray)
		.method("set", &Vec3::set)
		.method("setScalar", &Vec3::setScalar)
		.method("setX", &Vec3::setX)
		.method("setY", &Vec3::setY)
		.method("setZ", &Vec3::setZ)
		.method("setComponent", &Vec3::setComponent)
		.method("getComponent", &Vec3::getComponent)
		.method("clone", &Vec3::clone)
		.method("copy", &Vec3::copy)
		.method("addLocal", &Vec3::addLocal)
		.method("addScalarLocal", &Vec3::addScalarLocal)
		.method("addVectorsLocal", &Vec3::addVectorsLocal)
		.method("addScaledVectorLocal", &Vec3::addScaledVectorLocal)
		.method("subLocal", &Vec3::subLocal)
		.method("subScalarLocal", &Vec3::subScalarLocal)
		.method("subVectorsLocal", &Vec3::subVectorsLocal)
		.method("multiplyLocal", &Vec3::multiplyLocal)
		.method("multiplyScalarLocal", &Vec3::multiplyScalarLocal)
		.method("setFromEuler", &Vec3::setFromEuler)
		.method("setFromMatrixPosition", &Vec3::setFromMatrixPosition)
		.method("minLocal", &Vec3::minLocal)
		.method("maxLocal", &Vec3::maxLocal)
		.method("floorLocal", &Vec3::floorLocal)
		.method("ceilLocal", &Vec3::ceilLocal)
		.method("roundLocal", &Vec3::roundLocal)
		.method("negateLocal", &Vec3::negateLocal)
		.method("dot", &Vec3::dot)
		.method("lengthSq", &Vec3::lengthSq)
		.method("length", &Vec3::length)
		.method("manhattanLength", &Vec3::manhattanLength)
		.method("normalizeLocal", &Vec3::normalizeLocal)
		.method("normalize", &Vec3::normalize)
		.method("setLength", &Vec3::setLength)
		.method("distanceTo", &Vec3::distanceTo)
		.method("distanceToSquared", &Vec3::distanceToSquared)
		.method("scale", &Vec3::scale)
		.method("add", &Vec3::add)
		.method("sub", &Vec3::sub)
		.method("cross", &Vec3::cross)
		.method("lerpLocal", &Vec3::lerpLocal)
		.method("clampLocal", &Vec3::clampLocal)
		.method("equals", &Vec3::equals)
		.method("crossLocal", &Vec3::crossLocal)
		.method("crossVectorsLocal", &Vec3::crossVectorsLocal)
		.method("applyQuaternionLocal", &Vec3::applyQuaternionLocal)
		.method("clamp", &Vec3::clamp)
		.method("clampScalar", &Vec3::clampScalar)
		.method("clampLength", &Vec3::clampLength)
		.method("applyMatrix4", &Vec3::applyMatrix4)
		.method("applyMatrix4Local", &Vec3::applyMatrix4Local);
}
