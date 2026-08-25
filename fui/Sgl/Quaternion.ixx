module;
#include "Core/Vec3.h";

export module Sgl:Quaternion;

import :Mat;
import :Euler;

// 四元数
export class Quaternion {
public:

	float x;
	float y;
	float z;
	float w;


	Quaternion* set(float x, float y, float z, float w) {

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

		// this->_onChangeCallback();

		return this;

	}

	Quaternion clone() {
		return *this;
		// return new this->constructor( this->x, this->y, this->z, this->w );
	}

	Quaternion* copy(Quaternion quaternion) {

		this->x = quaternion.x;
		this->y = quaternion.y;
		this->z = quaternion.z;
		this->w = quaternion.w;

		// this->_onChangeCallback();

		return this;

	}

	Quaternion* setFromEuler(Euler euler) {

		float x = euler.x;
		float y = euler.y;
		float z = euler.z;
		const char* order = euler.order;

		// http://www.mathworks.com/matlabcentral/fileexchange/
		// 	20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors/
		//	content/SpinCalc.m


		float c1 = cos(x / 2.0f);
		float c2 = cos(y / 2.0f);
		float c3 = cos(z / 2.0f);

		float s1 = sin(x / 2.0f);
		float s2 = sin(y / 2.0f);
		float s3 = sin(z / 2.0f);


		if (strcmp(order, "XYZ") == 0) {
			this->x = s1 * c2 * c3 + c1 * s2 * s3;
			this->y = c1 * s2 * c3 - s1 * c2 * s3;
			this->z = c1 * c2 * s3 + s1 * s2 * c3;
			this->w = c1 * c2 * c3 - s1 * s2 * s3;
		}

		else if (strcmp(order, "YXZ") == 0) {
			this->x = s1 * c2 * c3 + c1 * s2 * s3;
			this->y = c1 * s2 * c3 - s1 * c2 * s3;
			this->z = c1 * c2 * s3 - s1 * s2 * c3;
			this->w = c1 * c2 * c3 + s1 * s2 * s3;
		}

		else if (strcmp(order, "ZXY") == 0) {
			this->x = s1 * c2 * c3 - c1 * s2 * s3;
			this->y = c1 * s2 * c3 + s1 * c2 * s3;
			this->z = c1 * c2 * s3 + s1 * s2 * c3;
			this->w = c1 * c2 * c3 - s1 * s2 * s3;
		}

		else if (strcmp(order, "ZYX") == 0) {
			this->x = s1 * c2 * c3 - c1 * s2 * s3;
			this->y = c1 * s2 * c3 + s1 * c2 * s3;
			this->z = c1 * c2 * s3 - s1 * s2 * c3;
			this->w = c1 * c2 * c3 + s1 * s2 * s3;
		}

		else if (strcmp(order, "YZX") == 0) {
			this->x = s1 * c2 * c3 + c1 * s2 * s3;
			this->y = c1 * s2 * c3 + s1 * c2 * s3;
			this->z = c1 * c2 * s3 - s1 * s2 * c3;
			this->w = c1 * c2 * c3 - s1 * s2 * s3;
		}

		else if (strcmp(order, "XZY") == 0) {
			this->x = s1 * c2 * c3 - c1 * s2 * s3;
			this->y = c1 * s2 * c3 - s1 * c2 * s3;
			this->z = c1 * c2 * s3 + s1 * s2 * c3;
			this->w = c1 * c2 * c3 + s1 * s2 * s3;
		}

		else {
			printf("Quaternion: .setFromEuler() encountered an unknown order: %s", order);
		}


		// if ( update != false ) this->_onChangeCallback();

		return this;

	}

	Quaternion* setFromAxisAngle(Vec3 axis, float angle) {

		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm

		// assumes axis is normalized

		float halfAngle = angle / 2.0;
		float s = sin(halfAngle);

		this->x = axis.x * s;
		this->y = axis.y * s;
		this->z = axis.z * s;
		this->w = cos(halfAngle);

		// this->_onChangeCallback();

		return this;

	}
	Vec3 toVec3AsEuler(const char* order) {
		Euler e;
		e.setFromQuaternion(*this, order == nullptr ? Euler_Default : order);
		Vec3 r = e.toVec3();
		return r;
	}

	Quaternion* setFromRotationMatrix(Mat m) {

		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

		// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

		float* te = m.data;

		float m11 = te[0]; float m12 = te[4]; float m13 = te[8];
		float m21 = te[1]; float m22 = te[5]; float m23 = te[9];
		float m31 = te[2]; float m32 = te[6]; float m33 = te[10];

		float trace = m11 + m22 + m33;

		if (trace > 0) {

			float s = 0.5 / sqrt(trace + 1.0);

			this->w = 0.25 / s;
			this->x = (m32 - m23) * s;
			this->y = (m13 - m31) * s;
			this->z = (m21 - m12) * s;

		}
		else if (m11 > m22 && m11 > m33) {

			float s = 2.0 * sqrt(1.0 + m11 - m22 - m33);

			this->w = (m32 - m23) / s;
			this->x = 0.25 * s;
			this->y = (m12 + m21) / s;
			this->z = (m13 + m31) / s;

		}
		else if (m22 > m33) {

			float s = 2.0 * sqrt(1.0 + m22 - m11 - m33);

			this->w = (m13 - m31) / s;
			this->x = (m12 + m21) / s;
			this->y = 0.25 * s;
			this->z = (m23 + m32) / s;

		}
		else {

			float s = 2.0 * sqrt(1.0 + m33 - m11 - m22);

			this->w = (m21 - m12) / s;
			this->x = (m13 + m31) / s;
			this->y = (m23 + m32) / s;
			this->z = 0.25 * s;

		}

		// this->_onChangeCallback();

		return this;

	}

	Quaternion* setFromUnitVectors(Vec3 vFrom, Vec3 vTo) {

		// assumes direction vectors vFrom and vTo are normalized

		float r = vFrom.dot(vTo) + 1;

		if (r < EPSILON) {

			// vFrom and vTo point in opposite directions

			r = 0;

			if (absFloat(vFrom.x) > absFloat(vFrom.z)) {

				this->x = -vFrom.y;
				this->y = vFrom.x;
				this->z = 0;
				this->w = r;

			}
			else {

				this->x = 0;
				this->y = -vFrom.z;
				this->z = vFrom.y;
				this->w = r;

			}

		}
		else {

			// crossVectors( vFrom, vTo ); // inlined to avoid cyclic dependency on Vector3

			this->x = vFrom.y * vTo.z - vFrom.z * vTo.y;
			this->y = vFrom.z * vTo.x - vFrom.x * vTo.z;
			this->z = vFrom.x * vTo.y - vFrom.y * vTo.x;
			this->w = r;

		}

		return this->normalizeLocal();

	}

	float angleTo(Quaternion q) {
		return 2 * acos(absFloat(clampFloat(this->dot(q), -1, 1)));
	}

	Quaternion* rotateTowardsLocal(Quaternion q, float step) {

		float angle = this->angleTo(q);

		if (angle == 0) { return this; }

		float t = minFloat(1, step / angle);

		this->slerpLocal(q, t);

		return this;

	}

	Quaternion* identity() {
		return this->set(0, 0, 0, 1);
	}

	Quaternion* invertLocal() {

		// quaternion is assumed to have unit length

		return this->conjugateLocal();

	}

	Quaternion* conjugateLocal() {

		this->x *= -1;
		this->y *= -1;
		this->z *= -1;

		// this->_onChangeCallback();

		return this;

	}

	float dot(Quaternion v) {
		return this->x * v.x + this->y * v.y + this->z * v.z + this->w * v.w;
	}

	float lengthSq() {

		return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;

	}

	float length() {

		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);

	}

	Quaternion* normalizeLocal() {

		float l = this->length();

		if (l == 0) {

			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 1;

		}
		else {

			l = 1 / l;

			this->x = this->x * l;
			this->y = this->y * l;
			this->z = this->z * l;
			this->w = this->w * l;

		}

		// this->_onChangeCallback();

		return this;

	}

	Quaternion* multiplyLocal(Quaternion q) {

		return this->multiplyQuaternionsLocal(*this, q);

	}

	Quaternion* premultiplyLocal(Quaternion q) {

		return this->multiplyQuaternionsLocal(q, *this);

	}

	Quaternion* multiplyQuaternionsLocal(Quaternion a, Quaternion b) {

		// from http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/code/index.htm

		float qax = a.x; float qay = a.y; float qaz = a.z; float qaw = a.w;
		float qbx = b.x; float qby = b.y; float qbz = b.z; float qbw = b.w;

		this->x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
		this->y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
		this->z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
		this->w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

		// this->_onChangeCallback();

		return this;

	}

	Quaternion* slerpLocal(Quaternion qb, float t) {

		if (t == 0) { return this; }
		if (t == 1) { return this->copy(qb); }

		float x = this->x;
		float y = this->y;
		float z = this->z;
		float w = this->w;

		// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/

		float cosHalfTheta = w * qb.w + x * qb.x + y * qb.y + z * qb.z;

		if (cosHalfTheta < 0) {

			this->w = -qb.w;
			this->x = -qb.x;
			this->y = -qb.y;
			this->z = -qb.z;

			cosHalfTheta = -cosHalfTheta;

		}
		else {

			this->copy(qb);

		}

		if (cosHalfTheta >= 1.0) {

			this->w = w;
			this->x = x;
			this->y = y;
			this->z = z;

			return this;

		}

		float sqrSinHalfTheta = 1.0 - cosHalfTheta * cosHalfTheta;

		if (sqrSinHalfTheta <= EPSILON) {

			float s = 1 - t;
			this->w = s * w + t * this->w;
			this->x = s * x + t * this->x;
			this->y = s * y + t * this->y;
			this->z = s * z + t * this->z;

			this->normalizeLocal();
			// this->_onChangeCallback();

			return this;

		}

		float sinHalfTheta = sqrt(sqrSinHalfTheta);
		float halfTheta = atan2(sinHalfTheta, cosHalfTheta);
		float ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
		float ratioB = sin(t * halfTheta) / sinHalfTheta;

		this->w = (w * ratioA + this->w * ratioB);
		this->x = (x * ratioA + this->x * ratioB);
		this->y = (y * ratioA + this->y * ratioB);
		this->z = (z * ratioA + this->z * ratioB);

		// this->_onChangeCallback();

		return this;

	}

	Quaternion* slerpQuaternionsLocal(Quaternion qa, Quaternion qb, float t) {
		return this->copy(qa)->slerpLocal(qb, t);
	}

	void applyToVec3Local(Vec3& self) {
		Quaternion& q = *this;


		float x = self.x;
		float y = self.y;
		float z = self.z;
		float qx = q.x;
		float qy = q.y;
		float qz = q.z;
		float qw = q.w;

		// calculate quat * vector

		float ix = qw * x + qy * z - qz * y;
		float iy = qw * y + qz * x - qx * z;
		float iz = qw * z + qx * y - qy * x;
		float iw = -qx * x - qy * y - qz * z;

		// calculate result * inverse quat
		self.x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
		self.y = iy * qw + iw * -qy + iz * -qx - ix * -qz;
		self.z = iz * qw + iw * -qz + ix * -qy - iy * -qx;
	}
	Quaternion* randomLocal() {

		// Derived from http://planning.cs.uiuc.edu/node198.html
		// Note, this source uses w, x, y, z ordering,
		// so we swap the order below.

		float u1 = random();
		float sqrt1u1 = sqrt(1 - u1);
		float sqrtu1 = sqrt(u1);

		float u2 = 2 * PI * random();

		float u3 = 2 * PI * random();

		return this->set(
			sqrt1u1 * cos(u2),
			sqrtu1 * sin(u3),
			sqrtu1 * cos(u3),
			sqrt1u1 * sin(u2)
		);

	}

	bool equals(Quaternion quaternion) {

		return eqFloat(quaternion.x, this->x) && eqFloat(quaternion.y, this->y)
			&& eqFloat(quaternion.z, this->z) && eqFloat(quaternion.w, this->w);

	}

	Quaternion* fromArray(float* array, int offset) {

		this->x = array[offset];
		this->y = array[offset + 1];
		this->z = array[offset + 2];
		this->w = array[offset + 3];

		// this->_onChangeCallback();

		return this;

	}

	float* toArray(float* array, int offset) {

		array[offset] = this->x;
		array[offset + 1] = this->y;
		array[offset + 2] = this->z;
		array[offset + 3] = this->w;

		return array;

	}

	// fromBufferAttribute( attribute, index ) {

	// 	this->x = attribute.getX( index );
	// 	this->y = attribute.getY( index );
	// 	this->z = attribute.getZ( index );
	// 	this->w = attribute.getW( index );

	// 	return this;

	// }




	static void slerpFlat(float* dst, int dstOffset, float* src0, int srcOffset0, float* src1, int srcOffset1, float t) {

		// fuzz-free, array-based Quaternion SLERP operation

		float x0 = src0[srcOffset0 + 0];
		float y0 = src0[srcOffset0 + 1];
		float z0 = src0[srcOffset0 + 2];
		float w0 = src0[srcOffset0 + 3];

		float x1 = src1[srcOffset1 + 0];
		float y1 = src1[srcOffset1 + 1];
		float z1 = src1[srcOffset1 + 2];
		float w1 = src1[srcOffset1 + 3];

		if (eqFloat(t, 0)) {

			dst[dstOffset + 0] = x0;
			dst[dstOffset + 1] = y0;
			dst[dstOffset + 2] = z0;
			dst[dstOffset + 3] = w0;
			return;

		}

		if (eqFloat(t, 1)) {

			dst[dstOffset + 0] = x1;
			dst[dstOffset + 1] = y1;
			dst[dstOffset + 2] = z1;
			dst[dstOffset + 3] = w1;
			return;

		}

		if (w0 != w1 || x0 != x1 || y0 != y1 || z0 != z1) {

			float s = 1 - t;
			float cosVal = x0 * x1 + y0 * y1 + z0 * z1 + w0 * w1;
			float dir = (cosVal >= 0 ? 1 : -1);
				float sqrSin = 1 - cosVal * cosVal;

			// Skip the Slerp for tiny steps to avoid numeric problems:
			if (sqrSin > EPSILON) {

				float sinVal = sqrt(sqrSin);
				float len = atan2(sinVal, cosVal * dir);

				s = sin(s * len) / sinVal;
				t = sin(t * len) / sinVal;

			}

			float tDir = t * dir;

			x0 = x0 * s + x1 * tDir;
			y0 = y0 * s + y1 * tDir;
			z0 = z0 * s + z1 * tDir;
			w0 = w0 * s + w1 * tDir;

			// Normalize in case we just did a lerp:
			if (s == 1 - t) {

				float f = 1 / sqrt(x0 * x0 + y0 * y0 + z0 * z0 + w0 * w0);

				x0 *= f;
				y0 *= f;
				z0 *= f;
				w0 *= f;

			}

		}

		dst[dstOffset] = x0;
		dst[dstOffset + 1] = y0;
		dst[dstOffset + 2] = z0;
		dst[dstOffset + 3] = w0;

	}

	static float* multiplyQuaternionsFlat(float* dst, int dstOffset, float* src0, int srcOffset0, float* src1, int srcOffset1) {

		float x0 = src0[srcOffset0];
		float y0 = src0[srcOffset0 + 1];
		float z0 = src0[srcOffset0 + 2];
		float w0 = src0[srcOffset0 + 3];

		float x1 = src1[srcOffset1];
		float y1 = src1[srcOffset1 + 1];
		float z1 = src1[srcOffset1 + 2];
		float w1 = src1[srcOffset1 + 3];

		dst[dstOffset] = x0 * w1 + w0 * x1 + y0 * z1 - z0 * y1;
		dst[dstOffset + 1] = y0 * w1 + w0 * y1 + z0 * x1 - x0 * z1;
		dst[dstOffset + 2] = z0 * w1 + w0 * z1 + x0 * y1 - y0 * x1;
		dst[dstOffset + 3] = w0 * w1 - x0 * x1 - y0 * y1 - z0 * z1;

		return dst;

	}
};