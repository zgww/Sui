#include "Mat.h"
#include "linmath.h"



Mat mkMatIdentity() {
	Mat m;
	m.identity();
	return m;
}

Mat* Mat::set(float n11, float n12, float n13, float n14, float n21, float n22, float n23, float n24, float n31, float n32, float n33, float n34, float n41, float n42, float n43, float n44) {

	float* te = this->data;

	te[0] = n11; te[4] = n12; te[8] = n13; te[12] = n14;
	te[1] = n21; te[5] = n22; te[9] = n23; te[13] = n24;
	te[2] = n31; te[6] = n32; te[10] = n33; te[14] = n34;
	te[3] = n41; te[7] = n42; te[11] = n43; te[15] = n44;

	return this;

}

Mat* Mat::identity() {
	this->set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
	return this;
}

Mat Mat::clone() {
	return *this;
}

Mat* Mat::copy(Mat m) {

	float* te = this->data;
	float* me = m.data;

	te[0] = me[0]; te[1] = me[1]; te[2] = me[2]; te[3] = me[3];
	te[4] = me[4]; te[5] = me[5]; te[6] = me[6]; te[7] = me[7];
	te[8] = me[8]; te[9] = me[9]; te[10] = me[10]; te[11] = me[11];
	te[12] = me[12]; te[13] = me[13]; te[14] = me[14]; te[15] = me[15];

	return this;

}

Mat* Mat::copyPosition(Mat m) {

	float* te = this->data;
	float* me = m.data;

	te[12] = me[12];
	te[13] = me[13];
	te[14] = me[14];

	return this;

}

Mat Mat::extractYRotationMatrix() {
	Quaternion q;
	this->decompose(nullptr, &q, nullptr);
	Vec3 forward = mkVec3(0, 0, -1);
	//q.applyToVec3Local(forward);
	forward.applyQuaternionLocal(q);
	forward.y = 0; // 
	forward.normalizeLocal();

	Quaternion q2;
	q2.setFromUnitVectors(mkVec3(0, 0, -1), forward);
	Mat ret;
	ret.makeRotationFromQuaternion(q2);
	return ret;
}
Mat* Mat::extractBasis(Vec3* xAxis, Vec3* yAxis, Vec3* zAxis) {
	*xAxis = mkVec3FromMatrixColumn(0);
	*yAxis = mkVec3FromMatrixColumn(1);
	*zAxis = mkVec3FromMatrixColumn(2);
	//xAxis->setFromMatrixColumn(*this, 0);
	//yAxis->setFromMatrixColumn(*this, 1);
	//zAxis->setFromMatrixColumn(*this, 2);

	return this;

}
Vec3 Mat::mkVec3FromMatrixColumn(int index) {
	Vec3 ret;
	ret.fromArray(data, index * 4);
	return ret;
}
Mat* Mat::makeBasis(Vec3 xAxis, Vec3 yAxis, Vec3 zAxis) {

	this->set(
		xAxis.x, yAxis.x, zAxis.x, 0,
		xAxis.y, yAxis.y, zAxis.y, 0,
		xAxis.z, yAxis.z, zAxis.z, 0,
		0, 0, 0, 1
	);

	return this;
}
Mat* Mat::extractRotationLocal(Mat m) {

	// this method does not support reflection matrices

	float* te = this->data;
	float* me = m.data;

	Vec3 _v1;

	float scaleX = 1 / m.mkVec3FromMatrixColumn(0).length();
	float scaleY = 1 / m.mkVec3FromMatrixColumn(1).length();
	float scaleZ = 1 / m.mkVec3FromMatrixColumn(2).length();

	te[0] = me[0] * scaleX;
	te[1] = me[1] * scaleX;
	te[2] = me[2] * scaleX;
	te[3] = 0;

	te[4] = me[4] * scaleY;
	te[5] = me[5] * scaleY;
	te[6] = me[6] * scaleY;
	te[7] = 0;

	te[8] = me[8] * scaleZ;
	te[9] = me[9] * scaleZ;
	te[10] = me[10] * scaleZ;
	te[11] = 0;

	te[12] = 0;
	te[13] = 0;
	te[14] = 0;
	te[15] = 1;

	return this;

}
Mat* Mat::makeRotationFromQuaternion(Quaternion q) {
	Vec3 _zero = mkVec3(0, 0, 0);
	Vec3 _one = mkVec3(1, 1, 1);

	return this->compose(_zero, q, _one);

}
Quaternion Mat::toQuaternionAsRotationMatrix() {
	Quaternion q;
	Mat& m = *this;
	// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

	// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

	float* te = m.data;

	float m11 = te[0]; float m12 = te[4]; float m13 = te[8];
	float m21 = te[1]; float m22 = te[5]; float m23 = te[9];
	float m31 = te[2]; float m32 = te[6]; float m33 = te[10];

	float trace = m11 + m22 + m33;

	if (trace > 0) {

		float s = 0.5f / sqrt(trace + 1.0);

		q.w = 0.25f / s;
		q.x = (m32 - m23) * s;
		q.y = (m13 - m31) * s;
		q.z = (m21 - m12) * s;

	}
	else if (m11 > m22 && m11 > m33) {

		float s = 2.0f * sqrt(1.0f + m11 - m22 - m33);

		q.w = (m32 - m23) / s;
		q.x = 0.25f * s;
		q.y = (m12 + m21) / s;
		q.z = (m13 + m31) / s;

	}
	else if (m22 > m33) {

		float s = 2.0f * sqrt(1.0 + m22 - m11 - m33);

		q.w = (m13 - m31) / s;
		q.x = (m12 + m21) / s;
		q.y = 0.25f * s;
		q.z = (m23 + m32) / s;

	}
	else {

		float s = 2.0f * sqrt(1.0f + m33 - m11 - m22);

		q.w = (m21 - m12) / s;
		q.x = (m13 + m31) / s;
		q.y = (m23 + m32) / s;
		q.z = 0.25f * s;

	}

	// this->_onChangeCallback();

	return q;

}

//只考虑旋转
Mat* Mat::lookAtLocal(Vec3 eye, Vec3 target, Vec3 up) {
	this->identity();

	Vec3 _z;
	Vec3 _y;
	Vec3 _x;

	float* te = this->data;

	_z.subVectorsLocal(eye, target);

	if (eqFloat(_z.lengthSq(), 0)) {

		// eye and target are in the same position

		_z.z = 1;

	}

	_z.normalizeLocal();
	_x.crossVectorsLocal(up, _z);

	if (eqFloat(_x.lengthSq(), 0)) {

		// up and z are parallel

		if (eqFloat(absFloat(up.z), 1)) {

			_z.x += 0.0001f;

		}
		else {

			_z.z += 0.0001f;

		}

		_z.normalizeLocal();
		_x.crossVectorsLocal(up, _z);

	}

	_x.normalizeLocal();
	_y.crossVectorsLocal(_z, _x);

	te[0] = _x.x; te[4] = _y.x; te[8] = _z.x;
	te[1] = _x.y; te[5] = _y.y; te[9] = _z.y;
	te[2] = _x.z; te[6] = _y.z; te[10] = _z.z;

	return this;
}
Mat* Mat::multiplyLocal(Mat m) {
	return this->multiplyMatricesLocal(*this, m);
}
Mat* Mat::premultiplyLocal(Mat m) {

	return this->multiplyMatricesLocal(m, *this);

}
Mat* Mat::multiplyMatricesLocal(Mat a, Mat b) {

	float* ae = a.data;
	float* be = b.data;
	float* te = this->data;

	float a11 = ae[0]; float a12 = ae[4]; float a13 = ae[8]; float a14 = ae[12];
	float a21 = ae[1]; float a22 = ae[5]; float a23 = ae[9]; float a24 = ae[13];
	float a31 = ae[2]; float a32 = ae[6]; float a33 = ae[10]; float a34 = ae[14];
	float a41 = ae[3]; float a42 = ae[7]; float a43 = ae[11]; float a44 = ae[15];

	float b11 = be[0]; float b12 = be[4]; float b13 = be[8]; float b14 = be[12];
	float b21 = be[1]; float b22 = be[5]; float b23 = be[9]; float b24 = be[13];
	float b31 = be[2]; float b32 = be[6]; float b33 = be[10]; float b34 = be[14];
	float b41 = be[3]; float b42 = be[7]; float b43 = be[11]; float b44 = be[15];

	te[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
	te[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
	te[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
	te[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

	te[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
	te[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
	te[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
	te[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

	te[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
	te[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
	te[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
	te[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

	te[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
	te[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
	te[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
	te[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

	return this;

}
Mat* Mat::multiplyScalarLocal(float s) {

	float* te = this->data;

	te[0] *= s; te[4] *= s; te[8] *= s; te[12] *= s;
	te[1] *= s; te[5] *= s; te[9] *= s; te[13] *= s;
	te[2] *= s; te[6] *= s; te[10] *= s; te[14] *= s;
	te[3] *= s; te[7] *= s; te[11] *= s; te[15] *= s;

	return this;
}
float Mat::determinant() {

	float* te = this->data;

	float n11 = te[0]; float n12 = te[4]; float n13 = te[8]; float n14 = te[12];
	float n21 = te[1]; float n22 = te[5]; float n23 = te[9]; float n24 = te[13];
	float n31 = te[2]; float n32 = te[6]; float n33 = te[10]; float n34 = te[14];
	float n41 = te[3]; float n42 = te[7]; float n43 = te[11]; float n44 = te[15];

	//TODO: make this more efficient
	//( based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm )

	return (
		n41 * (
			+n14 * n23 * n32
			- n13 * n24 * n32
			- n14 * n22 * n33
			+ n12 * n24 * n33
			+ n13 * n22 * n34
			- n12 * n23 * n34
			) +
		n42 * (
			+n11 * n23 * n34
			- n11 * n24 * n33
			+ n14 * n21 * n33
			- n13 * n21 * n34
			+ n13 * n24 * n31
			- n14 * n23 * n31
			) +
		n43 * (
			+n11 * n24 * n32
			- n11 * n22 * n34
			- n14 * n21 * n32
			+ n12 * n21 * n34
			+ n14 * n22 * n31
			- n12 * n24 * n31
			) +
		n44 * (
			-n13 * n22 * n31
			- n11 * n23 * n32
			+ n11 * n22 * n33
			+ n13 * n21 * n32
			- n12 * n21 * n33
			+ n12 * n23 * n31
			)

		);

}
Mat* Mat::transposeLocal() {

	float* te = this->data;
	float tmp;

	tmp = te[1]; te[1] = te[4]; te[4] = tmp;
	tmp = te[2]; te[2] = te[8]; te[8] = tmp;
	tmp = te[6]; te[6] = te[9]; te[9] = tmp;

	tmp = te[3]; te[3] = te[12]; te[12] = tmp;
	tmp = te[7]; te[7] = te[13]; te[13] = tmp;
	tmp = te[11]; te[11] = te[14]; te[14] = tmp;

	return this;

}
Mat* Mat::setPosition(float x, float y, float z) {
	float* te = this->data;

	// if ( x.isVector3 ) {

	// 	te[ 12 ] = x.x;
	// 	te[ 13 ] = x.y;
	// 	te[ 14 ] = x.z;

	// } else {

	te[12] = x;
	te[13] = y;
	te[14] = z;

	// }

	return this;

}
Mat* Mat::invertLocal() {

	// based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
	float* te = this->data;

	float n11 = te[0]; float n21 = te[1]; float n31 = te[2]; float n41 = te[3];
	float n12 = te[4]; float n22 = te[5]; float n32 = te[6]; float n42 = te[7];
	float n13 = te[8]; float n23 = te[9]; float n33 = te[10]; float n43 = te[11];
	float n14 = te[12]; float n24 = te[13]; float n34 = te[14]; float n44 = te[15];

	float t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44;
	float t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44;
	float t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44;
	float t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

	float det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;

	if (det == 0) { return this->set(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }

	float detInv = 1 / det;

	te[0] = t11 * detInv;
	te[1] = (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44) * detInv;
	te[2] = (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44) * detInv;
	te[3] = (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43) * detInv;

	te[4] = t12 * detInv;
	te[5] = (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44) * detInv;
	te[6] = (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44) * detInv;
	te[7] = (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43) * detInv;

	te[8] = t13 * detInv;
	te[9] = (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44) * detInv;
	te[10] = (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44) * detInv;
	te[11] = (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43) * detInv;

	te[12] = t14 * detInv;
	te[13] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) * detInv;
	te[14] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) * detInv;
	te[15] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) * detInv;

	return this;

}
Mat* Mat::scaleVec3(Vec3 v) {

	float* te = this->data;
	float x = v.x;
	float y = v.y;
	float z = v.z;

	te[0] *= x; te[4] *= y; te[8] *= z;
	te[1] *= x; te[5] *= y; te[9] *= z;
	te[2] *= x; te[6] *= y; te[10] *= z;
	te[3] *= x; te[7] *= y; te[11] *= z;

	return this;
}
float Mat::getMaxScaleOnAxis() {

	float* te = this->data;

	float scaleXSq = te[0] * te[0] + te[1] * te[1] + te[2] * te[2];
	float scaleYSq = te[4] * te[4] + te[5] * te[5] + te[6] * te[6];
	float scaleZSq = te[8] * te[8] + te[9] * te[9] + te[10] * te[10];

	return sqrt(maxFloat3(scaleXSq, scaleYSq, scaleZSq));

}
Mat* Mat::makeTranslation(float x, float y, float z) {

	this->set(

		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1

	);

	return this;

}
Mat* Mat::makeRotationX(float theta) {

	float c = cos(theta);
	float s = sin(theta);

	this->set(

		1, 0, 0, 0,
		0, c, -s, 0,
		0, s, c, 0,
		0, 0, 0, 1

	);

	return this;

}
Mat* Mat::makeRotationY(float theta) {

	float c = cos(theta);
	float s = sin(theta);

	this->set(
		c, 0, s, 0,
		0, 1, 0, 0,
		-s, 0, c, 0,
		0, 0, 0, 1
	);
	return this;
}
Mat* Mat::makeRotationZ(float theta) {

	float c = cos(theta);
	float s = sin(theta);

	this->set(
		c, -s, 0, 0,
		s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	return this;

}
Mat* Mat::makeRotationAxis(Vec3 axis, float angle) {

	// Based on http://www.gamedev.net/reference/articles/article1199.asp

	float c = cos(angle);
	float s = sin(angle);
	float t = 1 - c;
	float x = axis.x; float y = axis.y; float z = axis.z;
	float tx = t * x; float ty = t * y;

	this->set(
		tx * x + c, tx * y - s * z, tx * z + s * y, 0,
		tx * y + s * z, ty * y + c, ty * z - s * x, 0,
		tx * z - s * y, ty * z + s * x, t * z * z + c, 0,
		0, 0, 0, 1
	);

	return this;

}
Mat* Mat::makeScale(float x, float y, float z) {

	this->set(

		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1

	);

	return this;

}
Mat* Mat::makeShear(float xy, float xz, float yx, float yz, float zx, float zy) {
	this->set(
		1, yx, zx, 0,
		xy, 1, zy, 0,
		xz, yz, 1, 0,
		0, 0, 0, 1
	);

	return this;

}
Mat* Mat::compose(Vec3 position, Quaternion& quaternion, Vec3 scale) {

	float* te = this->data;
	float x = quaternion.x; float y = quaternion.y; float z = quaternion.z; float w = quaternion.w;
	float x2 = x + x; float	y2 = y + y; float z2 = z + z;
	float xx = x * x2; float xy = x * y2; float xz = x * z2;
	float yy = y * y2; float yz = y * z2; float zz = z * z2;
	float wx = w * x2; float wy = w * y2; float wz = w * z2;

	float sx = scale.x; float sy = scale.y; float sz = scale.z;

	te[0] = (1 - (yy + zz)) * sx;
	te[1] = (xy + wz) * sx;
	te[2] = (xz - wy) * sx;
	te[3] = 0;

	te[4] = (xy - wz) * sy;
	te[5] = (1 - (xx + zz)) * sy;
	te[6] = (yz + wx) * sy;
	te[7] = 0;

	te[8] = (xz + wy) * sz;
	te[9] = (yz - wx) * sz;
	te[10] = (1 - (xx + yy)) * sz;
	te[11] = 0;

	te[12] = position.x;
	te[13] = position.y;
	te[14] = position.z;
	te[15] = 1;

	return this;
}


Mat* Mat::decompose(Vec3* position, Quaternion* quaternion, Vec3* scale) {

	float* te = this->data;

	Vec3 _v1;
	Mat _m1;

	float sx = _v1.set(te[0], te[1], te[2])->length();
	float sy = _v1.set(te[4], te[5], te[6])->length();
	float sz = _v1.set(te[8], te[9], te[10])->length();

	// if determine is negative, we need to invert one scale
	float det = this->determinant();
	if (det < 0) { sx = -sx; }

	if (position != nullptr) {
		position->x = te[12];
		position->y = te[13];
		position->z = te[14];
	}

	// scale the rotation part
	_m1.copy(*this);

	float invSX = 1 / sx;
	float invSY = 1 / sy;
	float invSZ = 1 / sz;

	_m1.data[0] *= invSX;
	_m1.data[1] *= invSX;
	_m1.data[2] *= invSX;

	_m1.data[4] *= invSY;
	_m1.data[5] *= invSY;
	_m1.data[6] *= invSY;

	_m1.data[8] *= invSZ;
	_m1.data[9] *= invSZ;
	_m1.data[10] *= invSZ;

	if (quaternion != nullptr) {
		*quaternion = _m1.toQuaternionAsRotationMatrix();
		//quaternion->setFromRotationMatrix(_m1);
	}

	if (scale != nullptr) {
		scale->x = sx;
		scale->y = sy;
		scale->z = sz;
	}

	return this;
}

Mat* Mat::makePerspective(float left, float right, float top, float bottom, float near, float far) {

	float* te = this->data;
	float x = 2 * near / (right - left);
	float y = 2 * near / (top - bottom);

	float a = (right + left) / (right - left);
	float b = (top + bottom) / (top - bottom);
	float c = -(far + near) / (far - near);
	float d = -2 * far * near / (far - near);

	te[0] = x;	te[4] = 0;	te[8] = a;	te[12] = 0;
	te[1] = 0;	te[5] = y;	te[9] = b;	te[13] = 0;
	te[2] = 0;	te[6] = 0;	te[10] = c;	te[14] = d;
	te[3] = 0;	te[7] = 0;	te[11] = -1;	te[15] = 0;

	return this;

}

Mat* Mat::makeOrthographic(float left, float right, float top, float bottom, float near, float far) {

	float* te = this->data;
	float w = 1.0f / (right - left);
	float h = 1.0f / (top - bottom);
	float p = 1.0f / (far - near);

	float x = (right + left) * w;
	float y = (top + bottom) * h;
	float z = (far + near) * p;

	te[0] = 2 * w;	te[4] = 0;	te[8] = 0;	te[12] = -x;
	te[1] = 0;	te[5] = 2 * h;	te[9] = 0;	te[13] = -y;
	te[2] = 0;	te[6] = 0;	te[10] = -2 * p;	te[14] = -z;
	te[3] = 0;	te[7] = 0;	te[11] = 0;	te[15] = 1;

	return this;
}

bool Mat::equals(Mat matrix) {

	float* te = this->data;
	float* me = matrix.data;

	for (int i = 0; i < 16; i++) {

		if (!eqFloat(te[i], me[i])) { return false; }

	}

	return true;

}

Mat* Mat::fromArray(float* array, int offset) {

	for (int i = 0; i < 16; i++) {
		this->data[i] = array[i + offset];
	}

	return this;

}

float* Mat::toArray(float* array, int offset) {

	float* te = this->data;

	array[offset] = te[0];
	array[offset + 1] = te[1];
	array[offset + 2] = te[2];
	array[offset + 3] = te[3];

	array[offset + 4] = te[4];
	array[offset + 5] = te[5];
	array[offset + 6] = te[6];
	array[offset + 7] = te[7];

	array[offset + 8] = te[8];
	array[offset + 9] = te[9];
	array[offset + 10] = te[10];
	array[offset + 11] = te[11];

	array[offset + 12] = te[12];
	array[offset + 13] = te[13];
	array[offset + 14] = te[14];
	array[offset + 15] = te[15];

	return array;
}

Vec3 Mat::applyToVec3(Vec3 self) {
	auto& m = *this;

	float x = self.x;
	float y = self.y;
	float z = self.z;
	float* e = m.data;

	float w = 1 / (e[3] * x + e[7] * y + e[11] * z + e[15]);

	Vec3 ret;
	ret.x = (e[0] * x + e[4] * y + e[8] * z + e[12]) * w;
	ret.y = (e[1] * x + e[5] * y + e[9] * z + e[13]) * w;
	ret.z = (e[2] * x + e[6] * y + e[10] * z + e[14]) * w;

	return ret;
}

Vec3 Mat::transformDirection(Vec3 v3) {
	auto& m = *this;
	// input: THREE.Matrix4 affine matrix
	// vector interpreted as a direction

	float x = v3.x;
	float y = v3.y;
	float z = v3.z;
	float* e = m.data;

	Vec3 ret;
	ret.x = e[0] * x + e[4] * y + e[8] * z;
	ret.y = e[1] * x + e[5] * y + e[9] * z;
	ret.z = e[2] * x + e[6] * y + e[10] * z;

	ret.normalizeLocal();
	return ret;
}

//转为euler
Vec3 Mat::rotationMatrixToEulerXYZ() {
	float* te = this->data;
	float m11 = te[0]; float m12 = te[4];float m13 = te[8];
	float m21 = te[1]; float m22 = te[5];float m23 = te[9];
	float m31 = te[2]; float m32 = te[6];float m33 = te[10];

	Vec3 r;
	r.y = asin(clampFloat(m13, -1, 1));

	if (absFloat(m13) < 0.9999999) {

		r.x = atan2(-m23, m33);
		r.z = atan2(-m12, m11);

	}
	else {
		r.x = atan2(m32, m22);
		r.z = 0;
	}
	return r;
}

//void identity() {
//	// mat4x4 m = (mat4x4)this->data;
//	mat4x4_identity((void*)this->data);
//}
void Mat::rotateX(float angle) {
	mat4x4 bk;
	mat4x4_dup((vec4*)bk, (vec4*)this->data);
	mat4x4_rotate_X((vec4*)this->data, (vec4*)bk, angle);
}

// void copyFrom(Mat *m){
//     mat4x4_dup((void*)this->data, (void*)m.data)
// }
// Mat clone(){
//     Mat m;
//     m.copyFrom(this)
//     return m
// }
void Mat::rotateY(float angle) {
	mat4x4 bk;
	mat4x4_dup((vec4*)bk, (vec4*)(void *)this->data);
	mat4x4_rotate_Y((vec4*)this->data, (vec4*)bk, angle);
}

void Mat::rotateZ(float angle) {
	mat4x4 bk;
	mat4x4_dup((vec4*)bk, (vec4*)this->data);
	mat4x4_rotate_Z((vec4*)this->data, (vec4*)bk, angle);
}

void Mat::rotate(float x, float y, float z, float angle) {
	mat4x4 bk;
	mat4x4_dup((vec4*)bk, (vec4*)(const float*)this->data);

	mat4x4_rotate((vec4*)this->data, (vec4*)bk, x, y, z, angle);
}

void Mat::scale(float x, float y, float z) {
	mat4x4 bk;
	mat4x4_dup((vec4*)bk, (vec4*)this->data);
	mat4x4_scale_aniso((vec4*)this->data, (vec4*)bk, x, y, z);
}

// void transpose(){
//     mat4x4 bk;
//     mat4x4_dup((void*)bk, (void*)this->data)
//     mat4x4_transpose((void*)this->data, (void*)bk);
// }
void Mat::setTranslate(float x, float y, float z) {
	mat4x4_translate_in_place((vec4*)this->data, x, y, z);
}

void Mat::translate(float x, float y, float z) {
	mat4x4 bk;
	mat4x4_dup((vec4 *)bk, (vec4*)this->data);

	mat4x4 trM;
	//构建平移矩阵
	mat4x4_translate((vec4*)trM, x, y, z);

	//叠加 平移
	mat4x4_mul((vec4*)this->data, (vec4*)bk, (vec4*)trM);
}

Mat Mat::invert() {
	Mat c = *this;//.clone()
	c.invertLocal();
	return c;
}

void Mat::invertthis() {
	mat4x4 bk;
	mat4x4_dup((vec4*)bk, (vec4*)this->data);
	mat4x4_invert((vec4*)this->data, (vec4*)bk);
}

void Mat::frustum(float left, float right, float bottom, float top, float near, float far) {
	// mat4x4 m = (mat4x4)this->data;
	mat4x4_frustum((vec4*)this->data, left, right, bottom, top, near, far);
}

void Mat::ortho(float left, float right, float bottom, float top, float near, float far) {
	// mat4x4 m = (mat4x4)this->data;
	mat4x4_ortho((vec4*)this->data, left, right, bottom, top, near, far);
}

void Mat::perspective(float y_fov, float aspect, float near, float far) {
	// mat4x4 m = (mat4x4)this->data;
	mat4x4_perspective((vec4*)this->data, y_fov, aspect, near, far);
}

void Mat::mul(Mat* a, Mat* b) {
	// mat4x4 m = (mat4x4)this->data;
	mat4x4_mul((vec4*)this->data, (vec4*)a->data, (vec4*)b->data);
}

void Mat::lookAtFake(Vec3 eye, Vec3 center, Vec3 up) {
	vec3 e;
	e[0] = eye.x;
	e[1] = eye.y;
	e[2] = eye.z;

	vec3 c;
	c[0] = center.x;
	c[1] = center.y;
	c[2] = center.z;

	vec3 u;
	u[0] = up.x;
	u[1] = up.y;
	u[2] = up.z;

	mat4x4_look_at((vec4*)this->data, e, c, u);
}

Vec3 Mat::mulVec3(Vec3 v) {
	Vec4 v4;
	v4.x = v.x;
	v4.y = v.y;
	v4.z = v.z;
	v4.w = 1;
	Vec4 ret4 = mulVec4(v4);
	Vec3 ret;
	ret.x = ret4.x / ret4.w; // 齐次
	ret.y = ret4.y / ret4.w;
	ret.z = ret4.z / ret4.w;
	return ret;
}

Vec4 Mat::mulVec4(Vec4 v) {
	vec4 v2;
	v2[0] = v.x;
	v2[1] = v.y;
	v2[2] = v.z;
	v2[3] = v.w;
	vec4 result;

	mat4x4_mul_vec4(result, (vec4*)this->data, v2);

	Vec4 ret;
	ret.x = result[0];
	ret.y = result[1];
	ret.z = result[2];
	ret.w = result[3];

	return ret;
}

Mat* Mat::makeRotationFromEuler(Euler& euler) {

	float* te = this->data;

	float x = euler.x;
	float y = euler.y;
	float z = euler.z;
	float a = cos(x); float b = sin(x);
	float c = cos(y); float d = sin(y);
	float e = cos(z); float f = sin(z);

	if (euler.isXYZ()) {

		float ae = a * e; float af = a * f;float be = b * e;float bf = b * f;

		te[0] = c * e;
		te[4] = -c * f;
		te[8] = d;

		te[1] = af + be * d;
		te[5] = ae - bf * d;
		te[9] = -b * c;

		te[2] = bf - ae * d;
		te[6] = be + af * d;
		te[10] = a * c;

	}
	else if (euler.isYXZ()) {

		float ce = c * e;float cf = c * f;float de = d * e;float df = d * f;

		te[0] = ce + df * b;
		te[4] = de * b - cf;
		te[8] = a * d;

		te[1] = a * f;
		te[5] = a * e;
		te[9] = -b;

		te[2] = cf * b - de;
		te[6] = df + ce * b;
		te[10] = a * c;

	}
	else if (euler.isZXY()) {

		float ce = c * e;float cf = c * f;float de = d * e;float df = d * f;

		te[0] = ce - df * b;
		te[4] = -a * f;
		te[8] = de + cf * b;

		te[1] = cf + de * b;
		te[5] = a * e;
		te[9] = df - ce * b;

		te[2] = -a * d;
		te[6] = b;
		te[10] = a * c;

	}
	else if (euler.isZYX()) {

		float ae = a * e;float af = a * f;float be = b * e;float bf = b * f;

		te[0] = c * e;
		te[4] = be * d - af;
		te[8] = ae * d + bf;

		te[1] = c * f;
		te[5] = bf * d + ae;
		te[9] = af * d - be;

		te[2] = -d;
		te[6] = b * c;
		te[10] = a * c;

	}
	else if (euler.isYZX()) {

		float ac = a * c;float ad = a * d;float bc = b * c;float bd = b * d;

		te[0] = c * e;
		te[4] = bd - ac * f;
		te[8] = bc * f + ad;

		te[1] = f;
		te[5] = a * e;
		te[9] = -b * e;

		te[2] = -d * e;
		te[6] = ad * f + bc;
		te[10] = ac - bd * f;

	}
	else if (euler.isXZY()) {

		float ac = a * c;float ad = a * d;float bc = b * c;float bd = b * d;

		te[0] = c * e;
		te[4] = -f;
		te[8] = d * e;

		te[1] = ac * f + bd;
		te[5] = a * e;
		te[9] = ad * f - bc;

		te[2] = bc * f - ad;
		te[6] = b * e;
		te[10] = bd * f + ac;

	}

	// bottom row
	te[3] = 0;
	te[7] = 0;
	te[11] = 0;

	// last column
	te[12] = 0;
	te[13] = 0;
	te[14] = 0;
	te[15] = 1;

	return this;

}