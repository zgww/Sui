#pragma once

#include "Predef.h"
#include "Vec2.h"

struct Bezier {
	Vec2 p0;
	Vec2 p1;
	Vec2 p2;
	Vec2 p3;

	Vec2 getPoint(float t) const {
		float u = 1.0f - t;
		float tt = t * t;
		float uu = u * u;
		float uuu = uu * u;
		float ttt = tt * t;

		Vec2 p;
		p.x = uuu * p0.x + 3 * uu * t * p1.x + 3 * u * tt * p2.x + ttt * p3.x;
		p.y = uuu * p0.y + 3 * uu * t * p1.y + 3 * u * tt * p2.y + ttt * p3.y;
		return p;
	}

	Vec2 getTangent(float t) const {
		float u = 1.0f - t;
		Vec2 p;
		p.x = 3 * u * u * (p1.x - p0.x) + 6 * u * t * (p2.x - p1.x) + 3 * t * t * (p3.x - p2.x);
		p.y = 3 * u * u * (p1.y - p0.y) + 6 * u * t * (p2.y - p1.y) + 3 * t * t * (p3.y - p2.y);
		return p;
	}
};

inline Bezier mkBezier(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3) {
	Bezier b;
	b.p0 = p0;
	b.p1 = p1;
	b.p2 = p2;
	b.p3 = p3;
	return b;
}
