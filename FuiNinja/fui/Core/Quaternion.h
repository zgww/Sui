#pragma once

#include "Predef.h"
#include "Vec3.h"
#include "Vec4.h"

struct Euler;
class Mat;

struct Quaternion {
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1;

	std::string toString() const {
		char b[128];
		snprintf(b, sizeof(b), "Quaternion(%f,%f,%f,%f)", x, y, z, w);
		return std::string(b);
	}

	Quaternion* set(float x, float y, float z, float w) {
		this->x = x; this->y = y; this->z = z; this->w = w;
		return this;
	}

	Quaternion clone() const { return *this; }
	Quaternion* copy(const Quaternion& q) { x=q.x; y=q.y; z=q.z; w=q.w; return this; }

	Quaternion* identity() { x=0; y=0; z=0; w=1; return this; }

	Quaternion* multiplyLocal(const Quaternion& q) {
		float qx = q.x, qy = q.y, qz = q.z, qw = q.w;
		float tx = x, ty = y, tz = z, tw = w;
		x = tw*qx + tx*qw + ty*qz - tz*qy;
		y = tw*qy - tx*qz + ty*qw + tz*qx;
		z = tw*qz + tx*qy - ty*qx + tz*qw;
		w = tw*qw - tx*qx - ty*qy - tz*qz;
		return this;
	}
	Quaternion* setFromRotationMatrix(Mat& m);
	
	Quaternion* premultiplyLocal(Quaternion q);

	Quaternion* multiplyQuaternionsLocal(Quaternion a, Quaternion b);


	Quaternion* conjugateLocal() { x=-x; y=-y; z=-z; return this; }
	Quaternion* invertLocal() { return conjugateLocal(); }

	float dot(const Quaternion& q) const { return x*q.x + y*q.y + z*q.z + w*q.w; }
	float lengthSq() const { return x*x + y*y + z*z + w*w; }
	float length() const { return sqrtf(lengthSq()); }

	Quaternion* normalizeLocal() {
		float l = length();
		if (eqFloat(l, 0)) { x=0; y=0; z=0; w=1; return this; }
		float inv = 1.0f / l;
		x *= inv; y *= inv; z *= inv; w *= inv;
		return this;
	}

	float angleTo(const Quaternion& q) const {
		float d = dot(q) / (sqrtf(lengthSq() * q.lengthSq()));
		return 2.0f * acosf(clampFloat(fabsf(d), -1.0f, 1.0f));
	}

	Quaternion* rotateTowardsLocal(const Quaternion& q, float step) {
		float a = angleTo(q);
		if (eqFloat(a, 0)) return this;
		float t = minFloat(1.0f, step / a);
		return slerpLocal(q, t);
	}

	Quaternion* slerpLocal(const Quaternion& qb, float t) {
		if (t == 0) return this;
		if (t == 1) return copy(qb);

		float ax = x, ay = y, az = z, aw = w;
		float bx = qb.x, by = qb.y, bz = qb.z, bw = qb.w;

		float cosHalfTheta = ax*bx + ay*by + az*bz + aw*bw;
		if (cosHalfTheta < 0) {
			bx = -bx; by = -by; bz = -bz; bw = -bw;
			cosHalfTheta = -cosHalfTheta;
		}

		if (cosHalfTheta >= 1.0f) return this;

		float sqrSinHalfTheta = 1.0f - cosHalfTheta * cosHalfTheta;
		float sinHalfTheta = sqrHalfThetaSqrt(sqrSinHalfTheta);

		float halfTheta = acosf(cosHalfTheta);
		float ratioA = sinf((1 - t) * halfTheta) / sinHalfTheta;
		float ratioB = sinf(t * halfTheta) / sinHalfTheta;

		x = ax * ratioA + bx * ratioB;
		y = ay * ratioA + by * ratioB;
		z = az * ratioA + bz * ratioB;
		w = aw * ratioA + bw * ratioB;
		return this;
	}

	static float sqrHalfThetaSqrt(float v) {
		return sqrtf(maxFloat(0.0f, v));
	}

	Quaternion* setFromAxisAngle(const Vec3& axis, float angle) {
		float halfAngle = angle / 2.0f;
		float s = sinf(halfAngle);
		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
		w = cosf(halfAngle);
		return this;
	}

	Quaternion* setFromEuler( Euler& euler);
	Quaternion* setFromUnitVectors(Vec3 vFrom, Vec3 vTo);

	bool equals(const Quaternion& q) const {
		return fabsf(x-q.x) < EPSILON && fabsf(y-q.y) < EPSILON &&
		       fabsf(z-q.z) < EPSILON && fabsf(w-q.w) < EPSILON;
	}

	Vec3* multiplyVec3(Vec3* v) const {
		float qx=x, qy=y, qz=z, qw=w;
		float vx=v->x, vy=v->y, vz=v->z;
		float tx = 2.0f * (qy*vz - qz*vy);
		float ty = 2.0f * (qz*vx - qx*vz);
		float tz = 2.0f * (qx*vy - qy*vx);
		v->x = vx + tx*qw + (qy*tz - qz*ty);
		v->y = vy + ty*qw + (qz*tx - qx*tz);
		v->z = vz + tz*qw + (qx*ty - qy*tx);
		return v;
	}
};

inline Quaternion mkQuaternion(float x, float y, float z, float w) {
	Quaternion q; q.x = x; q.y = y; q.z = z; q.w = w; return q;
}
