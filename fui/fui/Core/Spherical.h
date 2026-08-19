#pragma once

#include "Predef.h"
#include "Vec3.h"

struct Spherical {
	float radius = 1.0f;
	float phi = 0;
	float theta = 0;

	Spherical() = default;
	Spherical(float r, float p, float t) : radius(r), phi(p), theta(t) {}

	std::string toString() const {
		char b[128];
		snprintf(b, sizeof(b), "Spherical(r:%f, phi:%f, theta:%f)", radius, phi, theta);
		return std::string(b);
	}

	Spherical* set(float r, float p, float t) { radius = r; phi = p; theta = t; return this; }
	Spherical clone() const { return *this; }
	Spherical* copy(const Spherical& s) { radius = s.radius; phi = s.phi; theta = s.theta; return this; }

	Spherical* setFromVector3(const Vec3& v) {
		radius = v.length();
		if (eqFloat(radius, 0)) { phi = 0; theta = 0; return this; }
		theta = atan2f(v.x, v.z);
		phi = acosf(clampFloat(v.y / radius, -1.0f, 1.0f));
		return this;
	}

	Spherical* setFromCartesianCoords(const Vec3& v) {
		return setFromVector3(v);
	}

	Vec3 toVec3() const {
		Vec3 ret;
		float sinPhiRadius = sinf(phi) * radius;
		ret.x = sinPhiRadius * sinf(theta);
		ret.y = cosf(phi) * radius;
		ret.z = sinPhiRadius * cosf(theta);
		return ret;
	}

	bool equals(const Spherical& s) const {
		return fabsf(radius - s.radius) < EPSILON &&
		       fabsf(phi - s.phi) < EPSILON &&
		       fabsf(theta - s.theta) < EPSILON;
	}
};

inline Spherical mkSpherical(float r, float p, float t) {
	Spherical s; s.radius = r; s.phi = p; s.theta = t; return s;
}
