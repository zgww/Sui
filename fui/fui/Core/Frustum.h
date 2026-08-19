#pragma once

#include "Predef.h"
#include "Vec3.h"
#include "Plane.h"

struct Frustum {
	Plane planes[6];
	Vec3 points[8];

	Frustum() = default;

	std::string toString() const {
		char b[256];
		snprintf(b, sizeof(b), "Frustum()");
		return std::string(b);
	}

	Frustum* set(const Plane& p0, const Plane& p1, const Plane& p2,
	             const Plane& p3, const Plane& p4, const Plane& p5) {
		planes[0] = p0; planes[1] = p1; planes[2] = p2;
		planes[3] = p3; planes[4] = p4; planes[5] = p5;
		return this;
	}

	Frustum clone() const { return *this; }
	Frustum* copy(const Frustum& f) {
		for (int i = 0; i < 6; i++) planes[i] = f.planes[i];
		return this;
	}

	Frustum* setFromProjection(float* m) {
		planes[0].setComponents(m[3] - m[0], m[7] - m[4], m[11] - m[8], m[15] - m[12]);
		planes[1].setComponents(m[3] + m[0], m[7] + m[4], m[11] + m[8], m[15] + m[12]);
		planes[2].setComponents(m[3] + m[1], m[7] + m[5], m[11] + m[9], m[15] + m[13]);
		planes[3].setComponents(m[3] - m[1], m[7] - m[5], m[11] - m[9], m[15] - m[13]);
		planes[4].setComponents(m[3] - m[2], m[7] - m[6], m[11] - m[10], m[15] - m[14]);
		planes[5].setComponents(m[3] + m[2], m[7] + m[6], m[11] + m[10], m[15] + m[14]);
		for (int i = 0; i < 6; i++) planes[i].normalizeLocal();
		return this;
	}

	bool containsPoint(const Vec3& point) const {
		for (int i = 0; i < 6; i++) {
			if (planes[i].distanceToPoint(point) < 0) return false;
		}
		return true;
	}

	bool intersectsSphere(const Vec3& center, float radius) const {
		for (int i = 0; i < 6; i++) {
			if (planes[i].distanceToPoint(center) < -radius) return false;
		}
		return true;
	}

	bool intersectsBox(const Vec3& min, const Vec3& max) const {
		Vec3 p;
		for (int i = 0; i < 6; i++) {
			p.x = planes[i].normal.x > 0 ? max.x : min.x;
			p.y = planes[i].normal.y > 0 ? max.y : min.y;
			p.z = planes[i].normal.z > 0 ? max.z : min.z;
			if (planes[i].distanceToPoint(p) < 0) return false;
		}
		return true;
	}
};

inline Frustum mkFrustum() {
	Frustum f; return f;
}
