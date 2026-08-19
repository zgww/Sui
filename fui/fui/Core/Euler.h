#pragma once

#include "Predef.h"
#include "Vec3.h"
#include "Quaternion.h"

struct Euler {
	enum class RotationOrder { XYZ, YXZ, ZXY, ZYX, YZX, XZY };
	float x = 0;
	float y = 0;
	float z = 0;
	RotationOrder order = RotationOrder::XYZ;

	std::string toString() const {
		char b[128];
		snprintf(b, sizeof(b), "Euler(%f,%f,%f)", x, y, z);
		return std::string(b);
	}

	Euler* set(float x, float y, float z, RotationOrder o = RotationOrder::XYZ) {
		this->x = x; this->y = y; this->z = z; this->order = o;
		return this;
	}

	Euler clone() const { return *this; }
	Euler* copy(const Euler& e) { x=e.x; y=e.y; z=e.z; order=e.order; return this; }

	Euler* setFromQuaternion(const Quaternion& q, RotationOrder o = RotationOrder::XYZ) {
		order = o;
		float test = q.x;
		switch (o) {
			case RotationOrder::XZY: test = q.y; break;
			case RotationOrder::YXZ: test = q.x; break;
			case RotationOrder::YZX: test = q.z; break;
			case RotationOrder::ZXY: test = q.x; break;
			case RotationOrder::ZYX: test = q.y; break;
			default: break;
		}

		float qx2 = q.x * q.x, qy2 = q.y * q.y, qz2 = q.z * q.z, qw2 = q.w * q.w;
		float unit = qx2 + qy2 + qz2 + qw2;

		switch (o) {
			case RotationOrder::XYZ: {
				x = atan2f(2.0f * (q.x * q.w - q.y * q.z), qw2 - qx2 - qy2 + qz2);
				y = asinf(clampFloat(2.0f * (q.x * q.z + q.y * q.w), -1.0f, 1.0f));
				z = atan2f(2.0f * (q.z * q.w - q.x * q.y), qw2 + qx2 - qy2 - qz2);
				break;
			}
			case RotationOrder::YXZ: {
				y = atan2f(2.0f * (q.x * q.z + q.y * q.w), qw2 - qx2 - qy2 + qz2);
				x = asinf(clampFloat(2.0f * (q.x * q.w - q.y * q.z), -1.0f, 1.0f));
				z = atan2f(2.0f * (q.z * q.w - q.x * q.y), qw2 + qx2 - qy2 - qz2);
				break;
			}
			case RotationOrder::ZXY: {
				z = atan2f(2.0f * (q.x * q.y + q.z * q.w), qw2 - qx2 - qy2 + qz2);
				x = asinf(clampFloat(2.0f * (q.x * q.w - q.y * q.z), -1.0f, 1.0f));
				y = atan2f(2.0f * (q.y * q.w - q.x * q.z), qw2 + qx2 - qy2 - qz2);
				break;
			}
			case RotationOrder::ZYX: {
				z = atan2f(2.0f * (q.x * q.y + q.z * q.w), qw2 - qx2 - qy2 + qz2);
				y = asinf(clampFloat(2.0f * (q.y * q.w - q.x * q.z), -1.0f, 1.0f));
				x = atan2f(2.0f * (q.x * q.w - q.y * q.z), qw2 + qx2 - qy2 - qz2);
				break;
			}
			case RotationOrder::YZX: {
				y = atan2f(2.0f * (q.y * q.w - q.x * q.z), qw2 - qx2 + qy2 - qz2);
				z = asinf(clampFloat(2.0f * (q.x * q.y + q.z * q.w), -1.0f, 1.0f));
				x = atan2f(2.0f * (q.x * q.w - q.y * q.z), qw2 + qx2 - qy2 - qz2);
				break;
			}
			case RotationOrder::XZY: {
				x = atan2f(2.0f * (q.x * q.w - q.y * q.z), qw2 - qx2 + qy2 - qz2);
				z = asinf(clampFloat(2.0f * (q.x * q.y + q.z * q.w), -1.0f, 1.0f));
				y = atan2f(2.0f * (q.y * q.w - q.x * q.z), qw2 + qx2 - qy2 - qz2);
				break;
			}
		}
		return this;
	}
};

inline Quaternion* Quaternion::setFromEuler(const Euler& euler) {
	float cx = cosf(euler.x / 2.0f), sx = sinf(euler.x / 2.0f);
	float cy = cosf(euler.y / 2.0f), sy = sinf(euler.y / 2.0f);
	float cz = cosf(euler.z / 2.0f), sz = sinf(euler.z / 2.0f);

	switch (euler.order) {
		case Euler::RotationOrder::XYZ:
			x = sx * cy * cz + cx * sy * sz;
			y = cx * sy * cz - sx * cy * sz;
			z = cx * cy * sz + sx * sy * cz;
			w = cx * sy * sz - sx * cy * cz;
			break;
		case Euler::RotationOrder::YXZ:
			x = sx * cy * cz + cx * sy * sz;
			y = cx * sy * cz - sx * cy * sz;
			z = cx * cy * sz - sx * sy * cz;
			w = cx * sy * sz + sx * cy * cz;
			break;
		case Euler::RotationOrder::ZXY:
			x = sx * cy * cz - cx * sy * sz;
			y = cx * sy * cz + sx * cy * sz;
			z = cx * cy * sz + sx * sy * cz;
			w = cx * sy * sz - sx * cy * cz;
			break;
		case Euler::RotationOrder::ZYX:
			x = sx * cy * cz - cx * sy * sz;
			y = cx * sy * cz + sx * cy * sz;
			z = cx * cy * sz - sx * sy * cz;
			w = cx * sy * sz + sx * cy * cz;
			break;
		case Euler::RotationOrder::YZX:
			x = sx * cy * cz + cx * sy * sz;
			y = cx * sy * cz - sx * cy * sz;
			z = cx * cy * sz - sx * sy * cz;
			w = cx * sy * sz + sx * cy * cz;
			break;
		case Euler::RotationOrder::XZY:
			x = sx * cy * cz - cx * sy * sz;
			y = cx * sy * cz + sx * cy * sz;
			z = cx * cy * sz + sx * sy * cz;
			w = cx * sy * sz - sx * cy * cz;
			break;
	}
	return this;
}

inline Quaternion* Quaternion::setFromUnitVectors(const Vec3& vFrom, const Vec3& vTo) {
	float r = vFrom.dot(vTo) + 1;
	if (eqFloat(r, 0)) {
		if (fabsf(vFrom.z) > fabsf(vFrom.x)) {
			set(0, -vFrom.z, 0, vFrom.y);
		} else {
			set(-vFrom.y, 0, 0, vFrom.x);
		}
	} else {
		Vec3 cross;
		cross.x = vFrom.y * vTo.z - vFrom.z * vTo.y;
		cross.y = vFrom.z * vTo.x - vFrom.x * vTo.z;
		cross.z = vFrom.x * vTo.y - vFrom.y * vTo.x;
		set(cross.x, cross.y, cross.z, r);
	}
	return normalizeLocal();
}

inline Euler mkEuler(float x, float y, float z) {
	Euler e; e.x = x; e.y = y; e.z = z; return e;
}
