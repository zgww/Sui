
#include "Vec4_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "./Mat3_orc.h"
#include "./Euler_orc.h"
#include "./Color_orc.h"
#include "./Spherical_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Vec4_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Vec4", sizeof( SuiCore$Vec4 ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "x", OrcMetaType_float, offsetof(SuiCore$Vec4, x), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "y", OrcMetaType_float, offsetof(SuiCore$Vec4, y), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "z", OrcMetaType_float, offsetof(SuiCore$Vec4, z), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "w", OrcMetaType_float, offsetof(SuiCore$Vec4, w), 0, 0, 0, 0);//float
    }
	return meta;
}
float  SuiCore$Vec4$width(SuiCore$Vec4 *  self){
	return self->x; 
}

float  SuiCore$Vec4$height(SuiCore$Vec4 *  self){
	return self->y; 
}

SuiCore$Vec4 *  SuiCore$Vec4$set(SuiCore$Vec4 *  self, float  x, float  y, float  z, float  w){
	self->x = x;
	self->y = y;
	self->z = z;
	self->w = w;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$setScalar(SuiCore$Vec4 *  self, float  scalar){
	self->x = scalar;
	self->y = scalar;
	self->z = scalar;
	self->w = scalar;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$setX(SuiCore$Vec4 *  self, float  x){
	self->x = x;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$setY(SuiCore$Vec4 *  self, float  y){
	self->y = y;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$setZ(SuiCore$Vec4 *  self, float  z){
	self->z = z;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$setW(SuiCore$Vec4 *  self, float  w){
	self->w = w;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$setComponent(SuiCore$Vec4 *  self, int  index, float  value){
	if (index == 0) {
		self->x = value;
	}
	if (index == 1) {
		self->y = value;
	}
	if (index == 2) {
		self->z = value;
	}
	if (index == 3) {
		self->w = value;
	}
	return self; 
}

float  SuiCore$Vec4$getComponent(SuiCore$Vec4 *  self, int  index){
	if (index == 0) {
		return self->x; 
	}
	if (index == 1) {
		return self->y; 
	}
	if (index == 2) {
		return self->z; 
	}
	if (index == 3) {
		return self->w; 
	}
	return 0.0; 
}

SuiCore$Vec4 SuiCore$Vec4$clone(SuiCore$Vec4 *  self){
	return *self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$copy(SuiCore$Vec4 *  self, SuiCore$Vec4 v){
	self->x = v.x;
	self->y = v.y;
	self->z = v.z;
	self->w = v.w;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$addLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v){
	self->x += v.x;
	self->y += v.y;
	self->z += v.z;
	self->w += v.w;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$addScalarLocal(SuiCore$Vec4 *  self, float  s){
	self->x += s;
	self->y += s;
	self->z += s;
	self->w += s;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$addVectorsLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 a, SuiCore$Vec4 b){
	self->x = a.x + b.x;
	self->y = a.y + b.y;
	self->z = a.z + b.z;
	self->w = a.w + b.w;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$addScaledVectorLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v, float  s){
	self->x += v.x * s;
	self->y += v.y * s;
	self->z += v.z * s;
	self->w += v.w * s;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$subLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v){
	self->x -= v.x;
	self->y -= v.y;
	self->z -= v.z;
	self->w -= v.w;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$subScalarLocal(SuiCore$Vec4 *  self, float  s){
	self->x -= s;
	self->y -= s;
	self->z -= s;
	self->w -= s;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$subVectorsLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 a, SuiCore$Vec4 b){
	self->x = a.x - b.x;
	self->y = a.y - b.y;
	self->z = a.z - b.z;
	self->w = a.w - b.w;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$multiplyLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v){
	self->x *= v.x;
	self->y *= v.y;
	self->z *= v.z;
	self->w *= v.w;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$multiplyScalarLocal(SuiCore$Vec4 *  self, float  scalar){
	self->x *= scalar;
	self->y *= scalar;
	self->z *= scalar;
	self->w *= scalar;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$applyMatrix4Local(SuiCore$Vec4 *  self, Sgl$Mat m){
	float  x = self->x;
	float  y = self->y;
	float  z = self->z;
	float  w = self->w;
	float *  e = m.data;
	self->x = e[0] * x + e[4] * y + e[8] * z + e[12] * w;
	self->y = e[1] * x + e[5] * y + e[9] * z + e[13] * w;
	self->z = e[2] * x + e[6] * y + e[10] * z + e[14] * w;
	self->w = e[3] * x + e[7] * y + e[11] * z + e[15] * w;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$divideScalarLocal(SuiCore$Vec4 *  self, float  scalar){
	if (scalar != 0) {
		return SuiCore$Vec4$multiplyScalarLocal(self, 1 / scalar) ; 
	}
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$setAxisAngleFromRotationMatrixLocal(SuiCore$Vec4 *  self, Sgl$Mat m){
	float  angle;
	float  x;
	float  y;
	float  z;
	float  epsilon = 0.01;
	float  epsilon2 = 0.1;
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
	if ((Orc$absFloat(m12 - m21)  < epsilon) && (Orc$absFloat(m13 - m31)  < epsilon) && (Orc$absFloat(m23 - m32)  < epsilon)) {
		if ((Orc$absFloat(m12 + m21)  < epsilon2) && (Orc$absFloat(m13 + m31)  < epsilon2) && (Orc$absFloat(m23 + m32)  < epsilon2) && (Orc$absFloat(m11 + m22 + m33 - 3)  < epsilon2)) {
			SuiCore$Vec4$set(self, 1, 0, 0, 0) ;
			return self; 
		}
		angle = Orc$PI;
		float  xx = (m11 + 1) / 2.0;
		float  yy = (m22 + 1) / 2.0;
		float  zz = (m33 + 1) / 2.0;
		float  xy = (m12 + m21) / 4.0;
		float  xz = (m13 + m31) / 4.0;
		float  yz = (m23 + m32) / 4.0;
		if ((xx > yy) && (xx > zz)) {
			if (xx < epsilon) {
				x = 0;
				y = 0.707106781;
				z = 0.707106781;
			}
			else {
				x = sqrt(xx) ;
				y = xy / x;
				z = xz / x;
			}
		}
		else if (yy > zz) {
			if (yy < epsilon) {
				x = 0.707106781;
				y = 0;
				z = 0.707106781;
			}
			else {
				y = sqrt(yy) ;
				x = xy / y;
				z = yz / y;
			}
		}
		else {
			if (zz < epsilon) {
				x = 0.707106781;
				y = 0.707106781;
				z = 0;
			}
			else {
				z = sqrt(zz) ;
				x = xz / z;
				y = yz / z;
			}
		}
		SuiCore$Vec4$set(self, x, y, z, angle) ;
		return self; 
	}
	float  s = sqrt((m32 - m23) * (m32 - m23) + (m13 - m31) * (m13 - m31) + (m21 - m12) * (m21 - m12)) ;
	if (Orc$absFloat(s)  < 0.001) {
		s = 1;
	}
	self->x = (m32 - m23) / s;
	self->y = (m13 - m31) / s;
	self->z = (m21 - m12) / s;
	self->w = acos((m11 + m22 + m33 - 1) / 2) ;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$minLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v){
	self->x = Orc$minFloat(self->x, v.x) ;
	self->y = Orc$minFloat(self->y, v.y) ;
	self->z = Orc$minFloat(self->z, v.z) ;
	self->w = Orc$minFloat(self->w, v.w) ;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$maxLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v){
	self->x = Orc$maxFloat(self->x, v.x) ;
	self->y = Orc$maxFloat(self->y, v.y) ;
	self->z = Orc$maxFloat(self->z, v.z) ;
	self->w = Orc$maxFloat(self->w, v.w) ;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$clampLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 min, SuiCore$Vec4 max){
	self->x = Orc$maxFloat(min.x, Orc$minFloat(max.x, self->x) ) ;
	self->y = Orc$maxFloat(min.y, Orc$minFloat(max.y, self->y) ) ;
	self->z = Orc$maxFloat(min.z, Orc$minFloat(max.z, self->z) ) ;
	self->w = Orc$maxFloat(min.w, Orc$minFloat(max.w, self->w) ) ;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$clampScalarLocal(SuiCore$Vec4 *  self, float  minVal, float  maxVal){
	self->x = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->x) ) ;
	self->y = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->y) ) ;
	self->z = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->z) ) ;
	self->w = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->w) ) ;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$clampLengthLocal(SuiCore$Vec4 *  self, float  min, float  max){
	float  length = SuiCore$Vec4$length(self) ;
	return SuiCore$Vec4$multiplyScalarLocal(SuiCore$Vec4$divideScalarLocal(self, length == 0 ? 1 : length) , Orc$maxFloat(min, Orc$minFloat(max, length) ) ) ; 
}

SuiCore$Vec4 *  SuiCore$Vec4$floorLocal(SuiCore$Vec4 *  self){
	self->x = floor(self->x) ;
	self->y = floor(self->y) ;
	self->z = floor(self->z) ;
	self->w = floor(self->w) ;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$ceilLocal(SuiCore$Vec4 *  self){
	self->x = ceil(self->x) ;
	self->y = ceil(self->y) ;
	self->z = ceil(self->z) ;
	self->w = ceil(self->w) ;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$roundLocal(SuiCore$Vec4 *  self){
	self->x = round(self->x) ;
	self->y = round(self->y) ;
	self->z = round(self->z) ;
	self->w = round(self->w) ;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$roundToZeroLocal(SuiCore$Vec4 *  self){
	self->x = (self->x < 0) ? ceil(self->x)  : floor(self->x) ;
	self->y = (self->y < 0) ? ceil(self->y)  : floor(self->y) ;
	self->z = (self->z < 0) ? ceil(self->z)  : floor(self->z) ;
	self->w = (self->w < 0) ? ceil(self->w)  : floor(self->w) ;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$negateLocal(SuiCore$Vec4 *  self){
	self->x = -self->x;
	self->y = -self->y;
	self->z = -self->z;
	self->w = -self->w;
	return self; 
}

float  SuiCore$Vec4$dot(SuiCore$Vec4 *  self, SuiCore$Vec4 v){
	return self->x * v.x + self->y * v.y + self->z * v.z + self->w * v.w; 
}

float  SuiCore$Vec4$lengthSq(SuiCore$Vec4 *  self){
	return self->x * self->x + self->y * self->y + self->z * self->z + self->w * self->w; 
}

float  SuiCore$Vec4$length(SuiCore$Vec4 *  self){
	return sqrt(self->x * self->x + self->y * self->y + self->z * self->z + self->w * self->w) ; 
}

float  SuiCore$Vec4$manhattanLength(SuiCore$Vec4 *  self){
	return Orc$absFloat(self->x)  + Orc$absFloat(self->y)  + Orc$absFloat(self->z)  + Orc$absFloat(self->w) ; 
}

SuiCore$Vec4 SuiCore$Vec4$normal(SuiCore$Vec4 *  self, float  f){
	SuiCore$Vec4 ret = SuiCore$mkVec4(0, 0, 0, 0) ;
	ret.x = self->x * f;
	ret.y = self->y * f;
	ret.z = self->z * f;
	ret.w = self->w * f;
	return ret; 
}

SuiCore$Vec4 *  SuiCore$Vec4$normalizeLocal(SuiCore$Vec4 *  self){
	float  length = SuiCore$Vec4$length(self) ;
	return SuiCore$Vec4$divideScalarLocal(self, Orc$eqFloat(length, 0)  ? 1 : length) ; 
}

SuiCore$Vec4 *  SuiCore$Vec4$setLengthLocal(SuiCore$Vec4 *  self, float  length){
	return SuiCore$Vec4$multiplyScalarLocal(SuiCore$Vec4$normalizeLocal(self) , length) ; 
}

SuiCore$Vec4 *  SuiCore$Vec4$lerpLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v, float  alpha){
	self->x += (v.x - self->x) * alpha;
	self->y += (v.y - self->y) * alpha;
	self->z += (v.z - self->z) * alpha;
	self->w += (v.w - self->w) * alpha;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$lerpVectors(SuiCore$Vec4 *  self, SuiCore$Vec4 v1, SuiCore$Vec4 v2, float  alpha){
	self->x = v1.x + (v2.x - v1.x) * alpha;
	self->y = v1.y + (v2.y - v1.y) * alpha;
	self->z = v1.z + (v2.z - v1.z) * alpha;
	self->w = v1.w + (v2.w - v1.w) * alpha;
	return self; 
}

SuiCore$Vec4 *  SuiCore$Vec4$fromArray(SuiCore$Vec4 *  self, float *  array, int  offset){
	self->x = array[offset];
	self->y = array[offset + 1];
	self->z = array[offset + 2];
	self->w = array[offset + 3];
	return self; 
}

float *  SuiCore$Vec4$toArray(SuiCore$Vec4 *  self, float *  array, int  offset){
	array[offset] = self->x;
	array[offset + 1] = self->y;
	array[offset + 2] = self->z;
	array[offset + 3] = self->w;
	return array; 
}

SuiCore$Vec4 *  SuiCore$Vec4$randomLocal(SuiCore$Vec4 *  self){
	self->x = Orc$random() ;
	self->y = Orc$random() ;
	self->z = Orc$random() ;
	self->w = Orc$random() ;
	return self; 
}

SuiCore$Vec4 SuiCore$Vec4$add4f(SuiCore$Vec4 *  self, float  x, float  y, float  z, float  w){
	SuiCore$Vec4 ret = SuiCore$mkVec4(self->x + x, self->y + y, self->z + z, self->w + w) ;
	return ret; 
}

SuiCore$Vec4 SuiCore$Vec4$add(SuiCore$Vec4 *  self, SuiCore$Vec4 b){
	SuiCore$Vec4 ret = SuiCore$mkVec4(0, 0, 0, 0) ;
	ret.x = self->x + b.x;
	ret.y = self->y + b.y;
	ret.z = self->z + b.z;
	ret.w = self->w + b.w;
	return ret; 
}

SuiCore$Vec4 SuiCore$Vec4$sub(SuiCore$Vec4 *  self, SuiCore$Vec4 b){
	SuiCore$Vec4 ret = SuiCore$mkVec4(0, 0, 0, 0) ;
	ret.x = self->x - b.x;
	ret.y = self->y - b.y;
	ret.z = self->z - b.z;
	ret.w = self->w - b.w;
	return ret; 
}

float  SuiCore$Vec4$distanceToSquared(SuiCore$Vec4 *  self, SuiCore$Vec4 b){
	float  dx = b.x - self->x;
	float  dy = b.y - self->y;
	float  dz = b.z - self->z;
	float  dw = b.w - self->w;
	return dx * dx + dy * dy + dz * dz + dw * dw; 
}

float  SuiCore$Vec4$distanceTo(SuiCore$Vec4 *  self, SuiCore$Vec4 b){
	float  ret = sqrt(SuiCore$Vec4$distanceToSquared(self, b) ) ;
	return ret; 
}

bool  SuiCore$Vec4$equals(SuiCore$Vec4 *  self, SuiCore$Vec4 b){
	return fabsf(self->x - b.x)  < 0.00001 && fabsf(self->y - b.y)  < 0.00001 && fabsf(self->z - b.z)  < 0.00001 && fabsf(self->w - b.w)  < 0.00001; 
}

SuiCore$Vec4 SuiCore$mkVec4(float  x, float  y, float  z, float  w){
	SuiCore$Vec4 v;
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return v; 
}

void  SuiCore$testVec4(){
	SuiCore$Vec4 v = SuiCore$mkVec4(0, 0, 0, 0) ;
	v.x = 10;
	v.y = 10;
	SuiCore$Vec4 b = SuiCore$mkVec4(0, 0, 0, 0) ;
	b.x = 17;
	b.y = 17;
	float  dis = SuiCore$Vec4$distanceTo(&v, b) ;
	printf("dis:%f\n", dis) ;
	float  sqrDis = SuiCore$Vec4$distanceToSquared(&v, b) ;
	printf("sqrdis :%f\n", sqrDis) ;
	printf("equals: %d\n", SuiCore$Vec4$equals(&b, v) ) ;
	SuiCore$Vec4$set(&b, 10, 10.00001, 0, 0) ;
	printf("equals:%d\n", SuiCore$Vec4$equals(&b, v) ) ;
	printf("vec3 width:%f, height:%f %f %f\n", SuiCore$Vec4$width(&v) , SuiCore$Vec4$height(&v) , SuiCore$Vec4$width(&b) , SuiCore$Vec4$height(&b) ) ;
}



