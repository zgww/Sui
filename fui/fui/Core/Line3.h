#pragma once

#include "Predef.h"
#include "Vec3.h"

struct Line3 {
	Vec3 start;
	Vec3 end;

	Line3() = default;
	Line3(const Vec3& s, const Vec3& e) : start(s), end(e) {}

	std::string toString() const {
		char b[256];
		snprintf(b, sizeof(b), "Line3(start:%s end:%s)", start.toString().c_str(), end.toString().c_str());
		return std::string(b);
	}

	Line3* set(const Vec3& s, const Vec3& e) { start = s; end = e; return this; }
	Line3 clone() const { return *this; }
	Line3* copy(const Line3& l) { start = l.start; end = l.end; return this; }

	Vec3 delta() const {
		Vec3 d;
		d.x = end.x - start.x;
		d.y = end.y - start.y;
		d.z = end.z - start.z;
		return d;
	}

	Vec3 deltaDirection() const {
		Vec3 d = delta();
		d.normalizeLocal();
		return d;
	}

	float length() const {
		Vec3 d = delta();
		return d.length();
	}

	float distance() const { return length(); }

	Vec3 at(float t) const {
		Vec3 r;
		r.x = start.x + (end.x - start.x) * t;
		r.y = start.y + (end.y - start.y) * t;
		r.z = start.z + (end.z - start.z) * t;
		return r;
	}

	Vec3 closestPointToPoint(const Vec3& point, bool clampToLine = true) const {
		Vec3 r;
		r.x = point.x - start.x;
		r.y = point.y - start.y;
		r.z = point.z - start.z;

		Vec3 d = delta();
		float deltaLengthSq = d.lengthSq();
		float t = deltaLengthSq > 0 ? (r.dot(d) / deltaLengthSq) : -1;
		if (clampToLine) t = clampFloat(t, 0, 1);
		return at(t);
	}
};

inline Line3 mkLine3(const Vec3& start, const Vec3& end) {
	Line3 l; l.start = start; l.end = end; return l;
}
