
#include "Quaternion_orc.h" 

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "../../Sgl/Sphere_orc.h"
#include "./Mat3_orc.h"
#include "./Plane_orc.h"
#include "./Vec3_orc.h"
#include "./Euler_orc.h"
#include "./Spherical_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Quaternion_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Quaternion", sizeof( SuiCore$Quaternion ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "x", OrcMetaType_float, offsetof(SuiCore$Quaternion, x), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "y", OrcMetaType_float, offsetof(SuiCore$Quaternion, y), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "z", OrcMetaType_float, offsetof(SuiCore$Quaternion, z), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "w", OrcMetaType_float, offsetof(SuiCore$Quaternion, w), 0, 0, 0, 0);//float
    }
	return meta;
}
SuiCore$Quaternion *  SuiCore$Quaternion$set(SuiCore$Quaternion *  self, float  x, float  y, float  z, float  w){
	self->x = x;
	self->y = y;
	self->z = z;
	self->w = w;
	return self; 
}

SuiCore$Quaternion SuiCore$Quaternion$clone(SuiCore$Quaternion *  self){
	return *self; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$copy(SuiCore$Quaternion *  self, SuiCore$Quaternion quaternion){
	self->x = quaternion.x;
	self->y = quaternion.y;
	self->z = quaternion.z;
	self->w = quaternion.w;
	return self; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$setFromEuler(SuiCore$Quaternion *  self, SuiCore$Euler euler){
	float  x = euler.x;
	float  y = euler.y;
	float  z = euler.z;
	const char *  order = euler.order;
	float  c1 = cos(x / 2.0) ;
	float  c2 = cos(y / 2.0) ;
	float  c3 = cos(z / 2.0) ;
	float  s1 = sin(x / 2.0) ;
	float  s2 = sin(y / 2.0) ;
	float  s3 = sin(z / 2.0) ;
	if (strcmp(order, "XYZ")  == 0) {
		self->x = s1 * c2 * c3 + c1 * s2 * s3;
		self->y = c1 * s2 * c3 - s1 * c2 * s3;
		self->z = c1 * c2 * s3 + s1 * s2 * c3;
		self->w = c1 * c2 * c3 - s1 * s2 * s3;
	}
	else if (strcmp(order, "YXZ")  == 0) {
		self->x = s1 * c2 * c3 + c1 * s2 * s3;
		self->y = c1 * s2 * c3 - s1 * c2 * s3;
		self->z = c1 * c2 * s3 - s1 * s2 * c3;
		self->w = c1 * c2 * c3 + s1 * s2 * s3;
	}
	else if (strcmp(order, "ZXY")  == 0) {
		self->x = s1 * c2 * c3 - c1 * s2 * s3;
		self->y = c1 * s2 * c3 + s1 * c2 * s3;
		self->z = c1 * c2 * s3 + s1 * s2 * c3;
		self->w = c1 * c2 * c3 - s1 * s2 * s3;
	}
	else if (strcmp(order, "ZYX")  == 0) {
		self->x = s1 * c2 * c3 - c1 * s2 * s3;
		self->y = c1 * s2 * c3 + s1 * c2 * s3;
		self->z = c1 * c2 * s3 - s1 * s2 * c3;
		self->w = c1 * c2 * c3 + s1 * s2 * s3;
	}
	else if (strcmp(order, "YZX")  == 0) {
		self->x = s1 * c2 * c3 + c1 * s2 * s3;
		self->y = c1 * s2 * c3 + s1 * c2 * s3;
		self->z = c1 * c2 * s3 - s1 * s2 * c3;
		self->w = c1 * c2 * c3 - s1 * s2 * s3;
	}
	else if (strcmp(order, "XZY")  == 0) {
		self->x = s1 * c2 * c3 - c1 * s2 * s3;
		self->y = c1 * s2 * c3 - s1 * c2 * s3;
		self->z = c1 * c2 * s3 + s1 * s2 * c3;
		self->w = c1 * c2 * c3 + s1 * s2 * s3;
	}
	else {
		printf("Quaternion: .setFromEuler() encountered an unknown order: %s", order) ;
	}
	return self; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$setFromAxisAngle(SuiCore$Quaternion *  self, SuiCore$Vec3 axis, float  angle){
	float  halfAngle = angle / 2.0;
	float  s = sin(halfAngle) ;
	self->x = axis.x * s;
	self->y = axis.y * s;
	self->z = axis.z * s;
	self->w = cos(halfAngle) ;
	return self; 
}

SuiCore$Vec3 SuiCore$Quaternion$toVec3AsEuler(SuiCore$Quaternion *  self, const char *  order){
	SuiCore$Euler e;
	SuiCore$Euler$setFromQuaternion(&e, *self, order == NULL ? SuiCore$Euler_Default : order) ;
	SuiCore$Vec3 r;
	SuiCore$Vec3$setFromEuler(&r, e) ;
	return r; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$setFromRotationMatrix(SuiCore$Quaternion *  self, Sgl$Mat m){
	float *  te = m.data;
	float  m11 = te[0];
	float  m12 = te[4];
	float  m13 = te[8];
	float  m21 = te[1];
	float  m22 = te[5];
	float  m23 = te[9];
	float  m31 = te[2];
	float  m32 = te[6];
	float  m33 = te[10];
	float  trace = m11 + m22 + m33;
	if (trace > 0) {
		float  s = 0.5 / sqrt(trace + 1.0) ;
		self->w = 0.25 / s;
		self->x = (m32 - m23) * s;
		self->y = (m13 - m31) * s;
		self->z = (m21 - m12) * s;
	}
	else if (m11 > m22 && m11 > m33) {
		float  s = 2.0 * sqrt(1.0 + m11 - m22 - m33) ;
		self->w = (m32 - m23) / s;
		self->x = 0.25 * s;
		self->y = (m12 + m21) / s;
		self->z = (m13 + m31) / s;
	}
	else if (m22 > m33) {
		float  s = 2.0 * sqrt(1.0 + m22 - m11 - m33) ;
		self->w = (m13 - m31) / s;
		self->x = (m12 + m21) / s;
		self->y = 0.25 * s;
		self->z = (m23 + m32) / s;
	}
	else {
		float  s = 2.0 * sqrt(1.0 + m33 - m11 - m22) ;
		self->w = (m21 - m12) / s;
		self->x = (m13 + m31) / s;
		self->y = (m23 + m32) / s;
		self->z = 0.25 * s;
	}
	return self; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$setFromUnitVectors(SuiCore$Quaternion *  self, SuiCore$Vec3 vFrom, SuiCore$Vec3 vTo){
	float  r = SuiCore$Vec3$dot(&vFrom, vTo)  + 1;
	if (r < Orc$EPSILON) {
		r = 0;
		if (Orc$absFloat(vFrom.x)  > Orc$absFloat(vFrom.z) ) {
			self->x = -vFrom.y;
			self->y = vFrom.x;
			self->z = 0;
			self->w = r;
		}
		else {
			self->x = 0;
			self->y = -vFrom.z;
			self->z = vFrom.y;
			self->w = r;
		}
	}
	else {
		self->x = vFrom.y * vTo.z - vFrom.z * vTo.y;
		self->y = vFrom.z * vTo.x - vFrom.x * vTo.z;
		self->z = vFrom.x * vTo.y - vFrom.y * vTo.x;
		self->w = r;
	}
	return SuiCore$Quaternion$normalizeLocal(self) ; 
}

float  SuiCore$Quaternion$angleTo(SuiCore$Quaternion *  self, SuiCore$Quaternion q){
	return 2 * acos(Orc$absFloat(Orc$clampFloat(SuiCore$Quaternion$dot(self, q) , -1, 1) ) ) ; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$rotateTowardsLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion q, float  step){
	float  angle = SuiCore$Quaternion$angleTo(self, q) ;
	if (angle == 0) {
		return self; 
	}
	float  t = Orc$minFloat(1, step / angle) ;
	SuiCore$Quaternion$slerpLocal(self, q, t) ;
	return self; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$identity(SuiCore$Quaternion *  self){
	return SuiCore$Quaternion$set(self, 0, 0, 0, 1) ; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$invertLocal(SuiCore$Quaternion *  self){
	return SuiCore$Quaternion$conjugateLocal(self) ; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$conjugateLocal(SuiCore$Quaternion *  self){
	self->x *= -1;
	self->y *= -1;
	self->z *= -1;
	return self; 
}

float  SuiCore$Quaternion$dot(SuiCore$Quaternion *  self, SuiCore$Quaternion v){
	return self->x * v.x + self->y * v.y + self->z * v.z + self->w * v.w; 
}

float  SuiCore$Quaternion$lengthSq(SuiCore$Quaternion *  self){
	return self->x * self->x + self->y * self->y + self->z * self->z + self->w * self->w; 
}

float  SuiCore$Quaternion$length(SuiCore$Quaternion *  self){
	return sqrt(self->x * self->x + self->y * self->y + self->z * self->z + self->w * self->w) ; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$normalizeLocal(SuiCore$Quaternion *  self){
	float  l = SuiCore$Quaternion$length(self) ;
	if (l == 0) {
		self->x = 0;
		self->y = 0;
		self->z = 0;
		self->w = 1;
	}
	else {
		l = 1 / l;
		self->x = self->x * l;
		self->y = self->y * l;
		self->z = self->z * l;
		self->w = self->w * l;
	}
	return self; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$multiplyLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion q){
	return SuiCore$Quaternion$multiplyQuaternionsLocal(self, *self, q) ; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$premultiplyLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion q){
	return SuiCore$Quaternion$multiplyQuaternionsLocal(self, q, *self) ; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$multiplyQuaternionsLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion a, SuiCore$Quaternion b){
	float  qax = a.x;
	float  qay = a.y;
	float  qaz = a.z;
	float  qaw = a.w;
	float  qbx = b.x;
	float  qby = b.y;
	float  qbz = b.z;
	float  qbw = b.w;
	self->x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
	self->y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
	self->z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
	self->w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;
	return self; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$slerpLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion qb, float  t){
	if (t == 0) {
		return self; 
	}
	if (t == 1) {
		return SuiCore$Quaternion$copy(self, qb) ; 
	}
	float  x = self->x;
	float  y = self->y;
	float  z = self->z;
	float  w = self->w;
	float  cosHalfTheta = w * qb.w + x * qb.x + y * qb.y + z * qb.z;
	if (cosHalfTheta < 0) {
		self->w = -qb.w;
		self->x = -qb.x;
		self->y = -qb.y;
		self->z = -qb.z;
		cosHalfTheta = -cosHalfTheta;
	}
	else {
		SuiCore$Quaternion$copy(self, qb) ;
	}
	if (cosHalfTheta >= 1.0) {
		self->w = w;
		self->x = x;
		self->y = y;
		self->z = z;
		return self; 
	}
	float  sqrSinHalfTheta = 1.0 - cosHalfTheta * cosHalfTheta;
	if (sqrSinHalfTheta <= Orc$EPSILON) {
		float  s = 1 - t;
		self->w = s * w + t * self->w;
		self->x = s * x + t * self->x;
		self->y = s * y + t * self->y;
		self->z = s * z + t * self->z;
		SuiCore$Quaternion$normalizeLocal(self) ;
		return self; 
	}
	float  sinHalfTheta = sqrt(sqrSinHalfTheta) ;
	float  halfTheta = atan2(sinHalfTheta, cosHalfTheta) ;
	float  ratioA = sin((1 - t) * halfTheta)  / sinHalfTheta;
	float  ratioB = sin(t * halfTheta)  / sinHalfTheta;
	self->w = (w * ratioA + self->w * ratioB);
	self->x = (x * ratioA + self->x * ratioB);
	self->y = (y * ratioA + self->y * ratioB);
	self->z = (z * ratioA + self->z * ratioB);
	return self; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$slerpQuaternionsLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion qa, SuiCore$Quaternion qb, float  t){
	return SuiCore$Quaternion$slerpLocal(SuiCore$Quaternion$copy(self, qa) , qb, t) ; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$randomLocal(SuiCore$Quaternion *  self){
	float  u1 = Orc$random() ;
	float  sqrt1u1 = sqrt(1 - u1) ;
	float  sqrtu1 = sqrt(u1) ;
	float  u2 = 2 * Orc$PI * Orc$random() ;
	float  u3 = 2 * Orc$PI * Orc$random() ;
	return SuiCore$Quaternion$set(self, sqrt1u1 * cos(u2) , sqrtu1 * sin(u3) , sqrtu1 * cos(u3) , sqrt1u1 * sin(u2) ) ; 
}

bool  SuiCore$Quaternion$equals(SuiCore$Quaternion *  self, SuiCore$Quaternion quaternion){
	return Orc$eqFloat(quaternion.x, self->x)  && Orc$eqFloat(quaternion.y, self->y)  && Orc$eqFloat(quaternion.z, self->z)  && Orc$eqFloat(quaternion.w, self->w) ; 
}

SuiCore$Quaternion *  SuiCore$Quaternion$fromArray(SuiCore$Quaternion *  self, float *  array, int  offset){
	self->x = array[offset];
	self->y = array[offset + 1];
	self->z = array[offset + 2];
	self->w = array[offset + 3];
	return self; 
}

float *  SuiCore$Quaternion$toArray(SuiCore$Quaternion *  self, float *  array, int  offset){
	array[offset] = self->x;
	array[offset + 1] = self->y;
	array[offset + 2] = self->z;
	array[offset + 3] = self->w;
	return array; 
}

void  SuiCore$Quaternion_slerpFlat(float *  dst, int  dstOffset, float *  src0, int  srcOffset0, float *  src1, int  srcOffset1, float  t){
	float  x0 = src0[srcOffset0 + 0];
	float  y0 = src0[srcOffset0 + 1];
	float  z0 = src0[srcOffset0 + 2];
	float  w0 = src0[srcOffset0 + 3];
	float  x1 = src1[srcOffset1 + 0];
	float  y1 = src1[srcOffset1 + 1];
	float  z1 = src1[srcOffset1 + 2];
	float  w1 = src1[srcOffset1 + 3];
	if (Orc$eqFloat(t, 0) ) {
		dst[dstOffset + 0] = x0;
		dst[dstOffset + 1] = y0;
		dst[dstOffset + 2] = z0;
		dst[dstOffset + 3] = w0;
		return ; 
	}
	if (Orc$eqFloat(t, 1) ) {
		dst[dstOffset + 0] = x1;
		dst[dstOffset + 1] = y1;
		dst[dstOffset + 2] = z1;
		dst[dstOffset + 3] = w1;
		return ; 
	}
	if (w0 != w1 || x0 != x1 || y0 != y1 || z0 != z1) {
		float  s = 1 - t;
		float  cosVal = x0 * x1 + y0 * y1 + z0 * z1 + w0 * w1;
		float  dir = (cosVal >= 0 ? 1 : -1);
		float  sqrSin = 1 - cosVal * cosVal;
		if (sqrSin > Orc$EPSILON) {
			float  sinVal = sqrt(sqrSin) ;
			float  len = atan2(sinVal, cosVal * dir) ;
			s = sin(s * len)  / sinVal;
			t = sin(t * len)  / sinVal;
		}
		float  tDir = t * dir;
		x0 = x0 * s + x1 * tDir;
		y0 = y0 * s + y1 * tDir;
		z0 = z0 * s + z1 * tDir;
		w0 = w0 * s + w1 * tDir;
		if (s == 1 - t) {
			float  f = 1 / sqrt(x0 * x0 + y0 * y0 + z0 * z0 + w0 * w0) ;
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

float *  SuiCore$Quaternion_multiplyQuaternionsFlat(float *  dst, int  dstOffset, float *  src0, int  srcOffset0, float *  src1, int  srcOffset1){
	float  x0 = src0[srcOffset0];
	float  y0 = src0[srcOffset0 + 1];
	float  z0 = src0[srcOffset0 + 2];
	float  w0 = src0[srcOffset0 + 3];
	float  x1 = src1[srcOffset1];
	float  y1 = src1[srcOffset1 + 1];
	float  z1 = src1[srcOffset1 + 2];
	float  w1 = src1[srcOffset1 + 3];
	dst[dstOffset] = x0 * w1 + w0 * x1 + y0 * z1 - z0 * y1;
	dst[dstOffset + 1] = y0 * w1 + w0 * y1 + z0 * x1 - x0 * z1;
	dst[dstOffset + 2] = z0 * w1 + w0 * z1 + x0 * y1 - y0 * x1;
	dst[dstOffset + 3] = w0 * w1 - x0 * x1 - y0 * y1 - z0 * z1;
	return dst; 
}



