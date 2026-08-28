#pragma once

#include "Predef.h"
#include "Vec3.h"
#include "Quaternion.h"

#define Euler_XYZ  "XYZ"
#define Euler_YXZ  "YXZ"
#define Euler_ZXY  "ZXY"
#define Euler_ZYX  "ZYX"
#define Euler_YZX  "YZX"
#define Euler_XZY  "XZY"
#define Euler_Default  "XYZ"

class Mat;

struct Euler {
	//enum class RotationOrder { XYZ, YXZ, ZXY, ZYX, YZX, XZY };
	float x = 0;
	float y = 0;
	float z = 0;
	//RotationOrder order = RotationOrder::XYZ;
	const char* order = Euler_Default;

	std::string toString() const {
		char b[128];
		snprintf(b, sizeof(b), "Euler(%f,%f,%f)", x, y, z);
		return std::string(b);
	}

	inline bool isXYZ() {
		return strcmp(this->order, "XYZ") == 0;
	}
	inline bool isYXZ() {
		return strcmp(this->order, "YXZ") == 0;
	}
	inline bool isZXY() {
		return strcmp(this->order, "ZXY") == 0;
	}
	inline bool isZYX() {
		return strcmp(this->order, "ZYX") == 0;
	}
	inline bool isYZX() {
		return strcmp(this->order, "YZX") == 0;
	}
	inline bool isXZY() {
		return strcmp(this->order, "XZY") == 0;
	}

	inline Euler clone() {
		return *this;
	}

	inline Euler* copy(Euler euler);

	Euler* setFromRotationMatrix(Mat& m, const char* order);

	Euler* setFromQuaternion(Quaternion q, const char* order);

	Euler* setFromVector3(Vec3 v, const char* order);
	Euler* reorder(const char* newOrder);

	Euler* set(float x, float y, float z, const char* order);

	bool equals(Euler euler);

	Euler* fromArray(float* array);

	float* toArray(float* array, int offset);
};
//
//inline Quaternion* Quaternion::setFromEuler(const Euler& euler) {
//	float cx = cosf(euler.x / 2.0f), sx = sinf(euler.x / 2.0f);
//	float cy = cosf(euler.y / 2.0f), sy = sinf(euler.y / 2.0f);
//	float cz = cosf(euler.z / 2.0f), sz = sinf(euler.z / 2.0f);
//
//	switch (euler.order) {
//		case Euler::RotationOrder::XYZ:
//			x = sx * cy * cz + cx * sy * sz;
//			y = cx * sy * cz - sx * cy * sz;
//			z = cx * cy * sz + sx * sy * cz;
//			w = cx * sy * sz - sx * cy * cz;
//			break;
//		case Euler::RotationOrder::YXZ:
//			x = sx * cy * cz + cx * sy * sz;
//			y = cx * sy * cz - sx * cy * sz;
//			z = cx * cy * sz - sx * sy * cz;
//			w = cx * sy * sz + sx * cy * cz;
//			break;
//		case Euler::RotationOrder::ZXY:
//			x = sx * cy * cz - cx * sy * sz;
//			y = cx * sy * cz + sx * cy * sz;
//			z = cx * cy * sz + sx * sy * cz;
//			w = cx * sy * sz - sx * cy * cz;
//			break;
//		case Euler::RotationOrder::ZYX:
//			x = sx * cy * cz - cx * sy * sz;
//			y = cx * sy * cz + sx * cy * sz;
//			z = cx * cy * sz - sx * sy * cz;
//			w = cx * sy * sz + sx * cy * cz;
//			break;
//		case Euler::RotationOrder::YZX:
//			x = sx * cy * cz + cx * sy * sz;
//			y = cx * sy * cz - sx * cy * sz;
//			z = cx * cy * sz - sx * sy * cz;
//			w = cx * sy * sz + sx * cy * cz;
//			break;
//		case Euler::RotationOrder::XZY:
//			x = sx * cy * cz - cx * sy * sz;
//			y = cx * sy * cz + sx * cy * sz;
//			z = cx * cy * sz + sx * sy * cz;
//			w = cx * sy * sz - sx * cy * cz;
//			break;
//	}
//	return this;
//}
//
//inline Quaternion* Quaternion::setFromUnitVectors(const Vec3& vFrom, const Vec3& vTo) {
//	float r = vFrom.dot(vTo) + 1;
//	if (eqFloat(r, 0)) {
//		if (fabsf(vFrom.z) > fabsf(vFrom.x)) {
//			set(0, -vFrom.z, 0, vFrom.y);
//		} else {
//			set(-vFrom.y, 0, 0, vFrom.x);
//		}
//	} else {
//		Vec3 cross;
//		cross.x = vFrom.y * vTo.z - vFrom.z * vTo.y;
//		cross.y = vFrom.z * vTo.x - vFrom.x * vTo.z;
//		cross.z = vFrom.x * vTo.y - vFrom.y * vTo.x;
//		set(cross.x, cross.y, cross.z, r);
//	}
//	return normalizeLocal();
//}

inline Euler mkEuler(float x, float y, float z) {
	Euler e; e.x = x; e.y = y; e.z = z; return e;
}
