#pragma once

#include "Predef.h"
#include "Vec3.h"
#include "Line3.h"
#include "Mat3.h"

struct Plane {
	Vec3 normal;
	float constant = 0;

	Plane() { normal.set(1, 0, 0); }

	std::string toString() const {
		char b[128];
		snprintf(b, sizeof(b), "Plane(normal:%s, constant:%f)", normal.toString().c_str(), constant);
		return std::string(b);
	}

	Plane* set(const Vec3& n, float c) { normal = n; constant = c; return this; }
	Plane* setComponents(float nx, float ny, float nz, float c) {
		normal.set(nx, ny, nz); constant = c; return this;
	}
	Plane* setFromNormalAndCoplanarPoint(const Vec3& n, const Vec3& p) {
		normal.copy(n);
		constant = -p.dot(normal);
		return this;
	}
	Plane* setFromCoplanarPoints(const Vec3& a, const Vec3& b, const Vec3& c) {
		Vec3 ab; ab.x = b.x - a.x; ab.y = b.y - a.y; ab.z = b.z - a.z;
		Vec3 ac; ac.x = c.x - a.x; ac.y = c.y - a.y; ac.z = c.z - a.z;
		Vec3 n;
		n.x = ab.y * ac.z - ab.z * ac.y;
		n.y = ab.z * ac.x - ab.x * ac.z;
		n.z = ab.x * ac.y - ab.y * ac.x;
		n.normalizeLocal();
		return setFromNormalAndCoplanarPoint(n, a);
	}

	Plane clone() const { return *this; }
	Plane* copy(const Plane& p) { normal = p.normal; constant = p.constant; return this; }

	Plane* normalizeLocal() {
		float invLen = 1.0f / normal.length();
		if (invLen > 0) {
			normal.multiplyScalarLocal(invLen);
			constant *= invLen;
		}
		return this;
	}

	Plane* negateLocal() {
		normal.negateLocal();
		constant = -constant;
		return this;
	}

	float distanceToPoint(const Vec3& p) const {
		return normal.dot(p) + constant;
	}

	float distanceToPointSigned(const Vec3& p) const {
		return distanceToPoint(p);
	}

	bool intersectsLine(const Line3& line, Vec3* result = nullptr) const {
		float denominator = normal.dot(line.deltaDirection());
		if (eqFloat(denominator, 0)) {
			if (eqFloat(distanceToPoint(line.start), 0)) {
				if (result) *result = line.start;
				return true;
			}
			return false;
		}
		float t = -(line.start.x * normal.x + line.start.y * normal.y + line.start.z * normal.z + constant) / denominator;
		if (t < 0 || t > 1) return false;
		if (result) *result = line.at(t);
		return true;
	}

	bool intersectsPlane(const Plane& plane) const {
		float d = normal.dot(plane.normal);
		return !eqFloat(fabsf(d), 1.0f);
	}

	Vec3* coplanarPoint(Vec3* target) const {
		if (target) {
			float d = -constant;
			target->x = normal.x * d;
			target->y = normal.y * d;
			target->z = normal.z * d;
		}
		return target;
	}

	Plane* applyMatrix4Local(float* m) {
		Mat3 m1;
		m1.elements[0] = m[0]; m1.elements[1] = m[1]; m1.elements[2] = m[2];
		m1.elements[3] = m[4]; m1.elements[4] = m[5]; m1.elements[5] = m[6];
		m1.elements[6] = m[8]; m1.elements[7] = m[9]; m1.elements[8] = m[10];
		m1.transposeLocal();
		Vec3 refPoint;
		coplanarPoint(&refPoint);
		refPoint.x += normal.x * constant;
		refPoint.y += normal.y * constant;
		refPoint.z += normal.z * constant;
		m1.applyToVec3(&normal);
		refPoint.x += normal.x; refPoint.y += normal.y; refPoint.z += normal.z;
		constant = -refPoint.dot(normal);
		return this;
	}

	Plane* translateLocal(const Vec3& offset) {
		constant = constant - offset.dot(normal);
		return this;
	}

	bool equals(const Plane& p) const {
		return normal.equals(p.normal) && fabsf(constant - p.constant) < EPSILON;
	}
};

inline Plane mkPlane(float nx, float ny, float nz, float c) {
	Plane p; p.normal.set(nx, ny, nz); p.constant = c; return p;
}
