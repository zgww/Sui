#pragma once

#include "Predef.h"
#include "Vec3.h"
#include "Plane.h"

struct Triangle {
	Vec3 a;
	Vec3 b;
	Vec3 c;

	Triangle() = default;
	Triangle(const Vec3& a_, const Vec3& b_, const Vec3& c_) : a(a_), b(b_), c(c_) {}

	std::string toString() const {
		char b[256];
		snprintf(b, sizeof(b), "Triangle(a:%s, b:%s, c:%s)",
			a.toString().c_str(), b.toString().c_str(), c.toString().c_str());
		return std::string(b);
	}

	Triangle* set(const Vec3& a_, const Vec3& b_, const Vec3& c_) {
		a = a_; b = b_; c = c_; return this;
	}
	Triangle clone() const { return *this; }
	Triangle* copy(const Triangle& t) { a = t.a; b = t.b; c = t.c; return this; }

	float area() const {
		Vec3 ab; ab.x = b.x - a.x; ab.y = b.y - a.y; ab.z = b.z - a.z;
		Vec3 ac; ac.x = c.x - a.x; ac.y = c.y - a.y; ac.z = c.z - a.z;
		Vec3 cross;
		cross.x = ab.y * ac.z - ab.z * ac.y;
		cross.y = ab.z * ac.x - ab.x * ac.z;
		cross.z = ab.x * ac.y - ab.y * ac.x;
		return 0.5f * cross.length();
	}

	Vec3 midpoint() const {
		Vec3 ret;
		ret.x = (a.x + b.x + c.x) / 3.0f;
		ret.y = (a.y + b.y + c.y) / 3.0f;
		ret.z = (a.z + b.z + c.z) / 3.0f;
		return ret;
	}

	Vec3 normal() const {
		Vec3 ab; ab.x = b.x - a.x; ab.y = b.y - a.y; ab.z = b.z - a.z;
		Vec3 ac; ac.x = c.x - a.x; ac.y = c.y - a.y; ac.z = c.z - a.z;
		Vec3 n;
		n.x = ab.y * ac.z - ab.z * ac.y;
		n.y = ab.z * ac.x - ab.x * ac.z;
		n.z = ab.x * ac.y - ab.y * ac.x;
		n.normalizeLocal();
		return n;
	}

	Plane plane() const {
		Plane p;
		p.setFromCoplanarPoints(a, b, c);
		return p;
	}

	Vec3 barycoordFromPoint(const Vec3& point) const {
		Vec3 ab; ab.x = b.x - a.x; ab.y = b.y - a.y; ab.z = b.z - a.z;
		Vec3 ac; ac.x = c.x - a.x; ac.y = c.y - a.y; ac.z = c.z - a.z;
		Vec3 ap; ap.x = point.x - a.x; ap.y = point.y - a.y; ap.z = point.z - a.z;

		float v0 = ab.dot(ab);
		float v1 = ab.dot(ac);
		float v2 = ab.dot(ap);
		float v3 = ac.dot(ac);
		float v4 = ac.dot(ap);

		float denom = v0 * v3 - v1 * v1;
		float v = (v3 * v2 - v1 * v4) / denom;
		float w = (v0 * v4 - v1 * v2) / denom;

		Vec3 ret;
		ret.x = 1.0f - v - w;
		ret.y = v;
		ret.z = w;
		return ret;
	}

	bool containsPoint(const Vec3& point) const {
		Vec3 bc = barycoordFromPoint(point);
		return bc.x >= 0 && bc.y >= 0 && bc.x + bc.y <= 1;
	}

	bool equals(const Triangle& t) const {
		return a.equals(t.a) && b.equals(t.b) && c.equals(t.c);
	}
};

inline Triangle mkTriangle(const Vec3& a, const Vec3& b, const Vec3& c) {
	Triangle t; t.a = a; t.b = b; t.c = c; return t;
}
