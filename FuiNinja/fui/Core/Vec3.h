#pragma once

#include "Predef.h"

struct Euler;
struct Mat3;
struct Quaternion;
class Mat;

struct Vec3 {
	float x = 0;
	float y = 0;
	float z = 0;

	std::string toString() const {
		char b[128];
		snprintf(b, sizeof(b), "Vec3(%f,%f,%f)", x, y, z);
		return std::string(b);
	}
	float width() const { return x; }
	float height() const { return y; }


	Vec3* fromArray(float* array, int offset);

	float* toArray(float* array, int offset);

	Vec3* set(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
		return this;
	}
	Vec3* setScalar(float scalar) {
		x = scalar;
		y = scalar;
		z = scalar;
		return this;
	}
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	void setZ(float z) { this->z = z; }

	void setComponent(int index, float value) {
		if (index == 0) x = value;
		else if (index == 1) y = value;
		else if (index == 2) z = value;
	}
	float getComponent(int index) const {
		if (index == 0) return x;
		else if (index == 1) return y;
		else if (index == 2) return z;
		return 0.0f;
	}

	Vec3 clone() const { return *this; }

	Vec3* copy(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return this;
	}

	Vec3* addLocal(const Vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return this;
	}
	Vec3* addScalarLocal(float s) {
		x += s;
		y += s;
		z += s;
		return this;
	}
	Vec3* addVectorsLocal(const Vec3& a, const Vec3& b) {
		x = a.x + b.x;
		y = a.y + b.y;
		z = a.z + b.z;
		return this;
	}
	Vec3* addScaledVectorLocal(const Vec3& v, float s) {
		x += v.x * s;
		y += v.y * s;
		z += v.z * s;
		return this;
	}

	Vec3* subLocal(const Vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return this;
	}
	Vec3* subScalarLocal(float s) {
		x -= s;
		y -= s;
		z -= s;
		return this;
	}
	Vec3* subVectorsLocal(const Vec3& a, const Vec3& b) {
		x = a.x - b.x;
		y = a.y - b.y;
		z = a.z - b.z;
		return this;
	}

	Vec3* multiplyLocal(const Vec3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return this;
	}
	Vec3* multiplyScalarLocal(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return this;
	}
	Vec3* setFromEuler(Euler& e);
	Vec3* applyMatrix3Local(const Mat3& m);
	Vec3* setFromMatrixPosition(Mat& m);
	Vec3* minLocal(const Vec3& v) {
		x = minFloat(x, v.x);
		y = minFloat(y, v.y);
		z = minFloat(z, v.z);
		return this;
	}
	Vec3* maxLocal(const Vec3& v) {
		x = maxFloat(x, v.x);
		y = maxFloat(y, v.y);
		z = maxFloat(z, v.z);
		return this;
	}

	Vec3* floorLocal() {
		x = floorFloat(x);
		y = floorFloat(y);
		z = floorFloat(z);
		return this;
	}
	Vec3* ceilLocal() {
		x = ceilFloat(x);
		y = ceilFloat(y);
		z = ceilFloat(z);
		return this;
	}
	Vec3* roundLocal() {
		x = roundFloat(x);
		y = roundFloat(y);
		z = roundFloat(z);
		return this;
	}
	Vec3* negateLocal() {
		x = -x;
		y = -y;
		z = -z;
		return this;
	}

	float dot(const Vec3& v) const {
		return x * v.x + y * v.y + z * v.z;
	}
	float lengthSq() const {
		return x * x + y * y + z * z;
	}
	float length() const {
		return sqrtf(x * x + y * y + z * z);
	}
	float manhattanLength() const {
		return absFloat(x) + absFloat(y) + absFloat(z);
	}

	Vec3* normalizeLocal() {
		float l = length();
		return multiplyScalarLocal(eqFloat(l, 0) ? 1.0f : 1.0f / l);
	}
	//归一化
	Vec3 normalize() {
		Vec3 ret = *this;
		ret.normalizeLocal();
		return ret;
	}
	Vec3* setLength(float length) {
		return normalizeLocal()->multiplyScalarLocal(length);
	}



	float distanceTo(const Vec3& v) const {
		return sqrtf(distanceToSquared(v));
	}
	float distanceToSquared(const Vec3& v) const {
		float dx = x - v.x;
		float dy = y - v.y;
		float dz = z - v.z;
		return dx * dx + dy * dy + dz * dz;
	}

	Vec3 scale(float f) const {
		Vec3 ret;
		ret.x = x * f;
		ret.y = y * f;
		ret.z = z * f;
		return ret;
	}

	Vec3 add(const Vec3& b) const {
		Vec3 ret;
		ret.x = x + b.x;
		ret.y = y + b.y;
		ret.z = z + b.z;
		return ret;
	}
	Vec3 sub(const Vec3& b) const {
		Vec3 ret;
		ret.x = x - b.x;
		ret.y = y - b.y;
		ret.z = z - b.z;
		return ret;
	}

	Vec3 cross(const Vec3& b) const {
		Vec3 ret;
		ret.x = y * b.z - z * b.y;
		ret.y = z * b.x - x * b.z;
		ret.z = x * b.y - y * b.x;
		return ret;
	}

	Vec3* lerpLocal(const Vec3& v, float alpha) {
		x += (v.x - x) * alpha;
		y += (v.y - y) * alpha;
		z += (v.z - z) * alpha;
		return this;
	}

	Vec3* clampLocal(const Vec3& mn, const Vec3& mx) {
		x = maxFloat(mn.x, minFloat(mx.x, x));
		y = maxFloat(mn.y, minFloat(mx.y, y));
		z = maxFloat(mn.z, minFloat(mx.z, z));
		return this;
	}

	bool equals(const Vec3& b) const {
		return fabsf(x - b.x) < 0.00001f
			&& fabsf(y - b.y) < 0.00001f
			&& fabsf(z - b.z) < 0.00001f;
	}




	Vec3* crossLocal(Vec3 v) {
		return crossVectorsLocal(*this, v);
	}

	Vec3* crossVectorsLocal(Vec3 a, Vec3 b) {

		float ax = a.x;
		float ay = a.y;
			float az = a.z;
			float bx = b.x;
			float by = b.y;
			float bz = b.z;

		x = ay * bz - az * by;
		y = az * bx - ax * bz;
		z = ax * by - ay * bx;

		return this;

	}


	Vec3* applyQuaternionLocal(Quaternion& q);



	Vec3 clamp(Vec3 min, Vec3 max) {

		auto& self = *this;
		// assumes min < max, componentwise
		Vec3 r;

		r.x = maxFloat(min.x, minFloat(max.x, self.x));
		r.y = maxFloat(min.y, minFloat(max.y, self.y));
		r.z = maxFloat(min.z, minFloat(max.z, self.z));

		return r;

	}

	Vec3 clampScalar(float minVal, float maxVal) {
		auto& self = *this;
		Vec3 r;

		r.x = maxFloat(minVal, minFloat(maxVal, self.x));
		r.y = maxFloat(minVal, minFloat(maxVal, self.y));
		r.z = maxFloat(minVal, minFloat(maxVal, self.z));

		return r;

	}

	Vec3 clampLength(float min, float max) {

		float length = this->length();

		Vec3 tmp = this->scale(1 / (length == 0 ? 1 : length));
		return tmp.scale(maxFloat(min, minFloat(max, length)));
	}



	Vec3 applyMatrix4(Mat& m);
	Vec3* applyMatrix4Local(Mat& m);


};

inline Vec3 mkVec3(float x, float y, float z) {
	Vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

inline Vec3 mkVec3_0() {
	Vec3 v;
	return v;
}
