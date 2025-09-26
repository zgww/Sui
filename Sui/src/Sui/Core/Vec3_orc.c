
#include "Vec3_orc.h" 

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
MetaStruct* SuiCore$Vec3_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Vec3", sizeof( SuiCore$Vec3 ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "x", OrcMetaType_float, offsetof(SuiCore$Vec3, x), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "y", OrcMetaType_float, offsetof(SuiCore$Vec3, y), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "z", OrcMetaType_float, offsetof(SuiCore$Vec3, z), 0, 0, 0, 0);//float
    }
	return meta;
}
Orc$String*  SuiCore$Vec3$toString(Orc$String **  __outRef__, SuiCore$Vec3 *  self){
	char  b[128];
	sprintf(b, "Vec3(%f,%f,%f)", self->x, self->y, self->z) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, b) ) ; 
}

float  SuiCore$Vec3$width(SuiCore$Vec3 *  self){
	return self->x; 
}

float  SuiCore$Vec3$height(SuiCore$Vec3 *  self){
	return self->y; 
}

SuiCore$Vec3 *  SuiCore$Vec3$set(SuiCore$Vec3 *  self, float  x, float  y, float  z){
	self->x = x;
	self->y = y;
	self->z = z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setScalar(SuiCore$Vec3 *  self, float  scalar){
	self->x = scalar;
	self->y = scalar;
	self->z = scalar;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setX(SuiCore$Vec3 *  self, float  x){
	self->x = x;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setY(SuiCore$Vec3 *  self, float  y){
	self->y = y;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setZ(SuiCore$Vec3 *  self, float  z){
	self->z = z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setComponent(SuiCore$Vec3 *  self, int  index, float  value){
	if (index == 0) {
		self->x = value;
	}
	if (index == 1) {
		self->y = value;
	}
	if (index == 2) {
		self->z = value;
	}
	return self; 
}

float  SuiCore$Vec3$getComponent(SuiCore$Vec3 *  self, int  index){
	if (index == 0) {
		return self->x; 
	}
	if (index == 1) {
		return self->y; 
	}
	if (index == 2) {
		return self->z; 
	}
	return 0.0; 
}

SuiCore$Vec3 SuiCore$Vec3$clone(SuiCore$Vec3 *  self){
	return *self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$copy(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	self->x = v.x;
	self->y = v.y;
	self->z = v.z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$addLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	self->x += v.x;
	self->y += v.y;
	self->z += v.z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$addScalarLocal(SuiCore$Vec3 *  self, float  s){
	self->x += s;
	self->y += s;
	self->z += s;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$addVectorsLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 a, SuiCore$Vec3 b){
	self->x = a.x + b.x;
	self->y = a.y + b.y;
	self->z = a.z + b.z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$addScaledVectorLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v, float  s){
	self->x += v.x * s;
	self->y += v.y * s;
	self->z += v.z * s;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$subLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	self->x -= v.x;
	self->y -= v.y;
	self->z -= v.z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$subScalarLocal(SuiCore$Vec3 *  self, float  s){
	self->x -= s;
	self->y -= s;
	self->z -= s;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$subVectorsLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 a, SuiCore$Vec3 b){
	self->x = a.x - b.x;
	self->y = a.y - b.y;
	self->z = a.z - b.z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$multiplyLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	self->x *= v.x;
	self->y *= v.y;
	self->z *= v.z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$multiplyScalarLocal(SuiCore$Vec3 *  self, float  scalar){
	self->x *= scalar;
	self->y *= scalar;
	self->z *= scalar;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$multiplyVectorsLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 a, SuiCore$Vec3 b){
	self->x = a.x * b.x;
	self->y = a.y * b.y;
	self->z = a.z * b.z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$applyMatrix3Local(SuiCore$Vec3 *  self, SuiCore$Mat3 m){
	float  x = self->x;
	float  y = self->y;
	float  z = self->z;
	float *  e = m.data;
	self->x = e[0] * x + e[3] * y + e[6] * z;
	self->y = e[1] * x + e[4] * y + e[7] * z;
	self->z = e[2] * x + e[5] * y + e[8] * z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$applyNormalMatrixLocal(SuiCore$Vec3 *  self, SuiCore$Mat3 m){
	return SuiCore$Vec3$normalizeLocal(SuiCore$Vec3$applyMatrix3Local(self, m) ) ; 
}

SuiCore$Vec3 SuiCore$Vec3$applyMatrix4(SuiCore$Vec3 *  self, Sgl$Mat m){
	SuiCore$Vec3 r = *self;
	SuiCore$Vec3$applyMatrix4Local(&r, m) ;
	return r; 
}

SuiCore$Vec3 *  SuiCore$Vec3$applyMatrix4Local(SuiCore$Vec3 *  self, Sgl$Mat m){
	float  x = self->x;
	float  y = self->y;
	float  z = self->z;
	float *  e = m.data;
	float  w = 1 / (e[3] * x + e[7] * y + e[11] * z + e[15]);
	self->x = (e[0] * x + e[4] * y + e[8] * z + e[12]) * w;
	self->y = (e[1] * x + e[5] * y + e[9] * z + e[13]) * w;
	self->z = (e[2] * x + e[6] * y + e[10] * z + e[14]) * w;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$transformDirectionLocal(SuiCore$Vec3 *  self, Sgl$Mat m){
	float  x = self->x;
	float  y = self->y;
	float  z = self->z;
	float *  e = m.data;
	self->x = e[0] * x + e[4] * y + e[8] * z;
	self->y = e[1] * x + e[5] * y + e[9] * z;
	self->z = e[2] * x + e[6] * y + e[10] * z;
	return SuiCore$Vec3$normalizeLocal(self) ; 
}

SuiCore$Vec3 *  SuiCore$Vec3$divideLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	self->x /= v.x;
	self->y /= v.y;
	self->z /= v.z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$divideScalarLocal(SuiCore$Vec3 *  self, float  scalar){
	return SuiCore$Vec3$multiplyScalarLocal(self, 1 / scalar) ; 
}

SuiCore$Vec3 *  SuiCore$Vec3$minLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	self->x = Orc$minFloat(self->x, v.x) ;
	self->y = Orc$minFloat(self->y, v.y) ;
	self->z = Orc$minFloat(self->z, v.z) ;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$maxLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	self->x = Orc$maxFloat(self->x, v.x) ;
	self->y = Orc$maxFloat(self->y, v.y) ;
	self->z = Orc$maxFloat(self->z, v.z) ;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$floorLocal(SuiCore$Vec3 *  self){
	self->x = floor(self->x) ;
	self->y = floor(self->y) ;
	self->z = floor(self->z) ;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$ceilLocal(SuiCore$Vec3 *  self){
	self->x = ceil(self->x) ;
	self->y = ceil(self->y) ;
	self->z = ceil(self->z) ;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$roundLocal(SuiCore$Vec3 *  self){
	self->x = round(self->x) ;
	self->y = round(self->y) ;
	self->z = round(self->z) ;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$roundToZeroLocal(SuiCore$Vec3 *  self){
	self->x = (self->x < 0.0) ? ceil(self->x)  : floor(self->x) ;
	self->y = (self->y < 0.0) ? ceil(self->y)  : floor(self->y) ;
	self->z = (self->z < 0.0) ? ceil(self->z)  : floor(self->z) ;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$negateLocal(SuiCore$Vec3 *  self){
	self->x = -self->x;
	self->y = -self->y;
	self->z = -self->z;
	return self; 
}

float  SuiCore$Vec3$dot(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	return self->x * v.x + self->y * v.y + self->z * v.z; 
}

float  SuiCore$Vec3$lengthSq(SuiCore$Vec3 *  self){
	return self->x * self->x + self->y * self->y + self->z * self->z; 
}

float  SuiCore$Vec3$length(SuiCore$Vec3 *  self){
	return sqrt(self->x * self->x + self->y * self->y + self->z * self->z) ; 
}

float  SuiCore$Vec3$manhattanLength(SuiCore$Vec3 *  self){
	return Orc$absFloat(self->x)  + Orc$absFloat(self->y)  + Orc$absFloat(self->z) ; 
}

SuiCore$Vec3 SuiCore$Vec3$normal(SuiCore$Vec3 *  self){
	float  len = SuiCore$Vec3$length(self) ;
	if (len == 0.0) {
		len = 1;
	}
	return SuiCore$Vec3$scale(self, 1 / len) ; 
}

SuiCore$Vec3 *  SuiCore$Vec3$normalizeLocal(SuiCore$Vec3 *  self){
	float  l = SuiCore$Vec3$length(self) ;
	return SuiCore$Vec3$divideScalarLocal(self, Orc$eqFloat(l, 0)  ? 1 : l) ; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setLength(SuiCore$Vec3 *  self, float  length){
	return SuiCore$Vec3$multiplyScalarLocal(SuiCore$Vec3$normalizeLocal(self) , length) ; 
}

SuiCore$Vec3 SuiCore$Vec3$lerp(SuiCore$Vec3 *  self, SuiCore$Vec3 b, float  ratio){
	SuiCore$Vec3 r;
	r.x = Orc$lerpFloat(self->x, b.x, ratio) ;
	r.y = Orc$lerpFloat(self->y, b.y, ratio) ;
	r.z = Orc$lerpFloat(self->z, b.z, ratio) ;
	return r; 
}

SuiCore$Vec3 *  SuiCore$Vec3$lerpLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v, float  alpha){
	self->x += (v.x - self->x) * alpha;
	self->y += (v.y - self->y) * alpha;
	self->z += (v.z - self->z) * alpha;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$lerpVectorsLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v1, SuiCore$Vec3 v2, float  alpha){
	self->x = v1.x + (v2.x - v1.x) * alpha;
	self->y = v1.y + (v2.y - v1.y) * alpha;
	self->z = v1.z + (v2.z - v1.z) * alpha;
	return self; 
}

SuiCore$Vec3 SuiCore$Vec3$cross(SuiCore$Vec3 *  self, SuiCore$Vec3 b){
	SuiCore$Vec3 r;
	r.x = self->y * b.z - self->z * b.y;
	r.y = self->z * b.x - self->x * b.z;
	r.z = self->x * b.y - self->y * b.x;
	return r; 
}

SuiCore$Vec3 *  SuiCore$Vec3$crossLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	return SuiCore$Vec3$crossVectorsLocal(self, *self, v) ; 
}

SuiCore$Vec3 *  SuiCore$Vec3$crossVectorsLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 a, SuiCore$Vec3 b){
	float  ax = a.x;
	float  ay = a.y;
	float  az = a.z;
	float  bx = b.x;
	float  by = b.y;
	float  bz = b.z;
	self->x = ay * bz - az * by;
	self->y = az * bx - ax * bz;
	self->z = ax * by - ay * bx;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$projectOnVectorLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	float  denominator = SuiCore$Vec3$lengthSq(&v) ;
	if (Orc$eqFloat(denominator, 0.0) ) {
		return SuiCore$Vec3$set(self, 0, 0, 0) ; 
	}
	float  scalar = SuiCore$Vec3$dot(&v, *self)  / denominator;
	return SuiCore$Vec3$multiplyScalarLocal(SuiCore$Vec3$copy(self, v) , scalar) ; 
}

SuiCore$Vec3 *  SuiCore$Vec3$reflect(SuiCore$Vec3 *  self, SuiCore$Vec3 normal){
	SuiCore$Vec3 _vector;
	return SuiCore$Vec3$subLocal(self, *(SuiCore$Vec3$multiplyScalarLocal(SuiCore$Vec3$copy(&_vector, normal) , 2 * SuiCore$Vec3$dot(self, normal) ) )) ; 
}

float  SuiCore$Vec3$angleTo(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	float  denominator = sqrt(SuiCore$Vec3$lengthSq(self)  * SuiCore$Vec3$lengthSq(&v) ) ;
	if (Orc$eqFloat(denominator, 0) ) {
		return Orc$PI / 2.0; 
	}
	float  theta = SuiCore$Vec3$dot(self, v)  / denominator;
	return acos(Orc$clampFloat(theta, -1, 1) ) ; 
}

float  SuiCore$Vec3$distanceTo(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	return sqrt(SuiCore$Vec3$distanceToSquared(self, v) ) ; 
}

float  SuiCore$Vec3$distanceToSquared(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	float  dx = self->x - v.x;
	float  dy = self->y - v.y;
	float  dz = self->z - v.z;
	return dx * dx + dy * dy + dz * dz; 
}

float  SuiCore$Vec3$manhattanDistanceTo(SuiCore$Vec3 *  self, SuiCore$Vec3 v){
	return Orc$absFloat(self->x - v.x)  + Orc$absFloat(self->y - v.y)  + Orc$absFloat(self->z - v.z) ; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setFromSphericalLocal(SuiCore$Vec3 *  self, SuiCore$Spherical s){
	return SuiCore$Vec3$setFromSphericalCoordsLocal(self, s.radius, s.phi, s.theta) ; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setFromSphericalCoordsLocal(SuiCore$Vec3 *  self, float  radius, float  phi, float  theta){
	float  sinPhiRadius = sin(phi)  * radius;
	self->x = sinPhiRadius * sin(theta) ;
	self->y = cos(phi)  * radius;
	self->z = sinPhiRadius * cos(theta) ;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setFromMatrixPosition(SuiCore$Vec3 *  self, Sgl$Mat m){
	float *  e = m.data;
	self->x = e[12];
	self->y = e[13];
	self->z = e[14];
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setFromMatrixScale(SuiCore$Vec3 *  self, Sgl$Mat m){
	float  sx = SuiCore$Vec3$length(SuiCore$Vec3$setFromMatrixColumn(self, m, 0) ) ;
	float  sy = SuiCore$Vec3$length(SuiCore$Vec3$setFromMatrixColumn(self, m, 1) ) ;
	float  sz = SuiCore$Vec3$length(SuiCore$Vec3$setFromMatrixColumn(self, m, 2) ) ;
	self->x = sx;
	self->y = sy;
	self->z = sz;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setFromMatrixColumn(SuiCore$Vec3 *  self, Sgl$Mat m, int  index){
	return SuiCore$Vec3$fromArray(self, m.data, index * 4) ; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setFromMatrix3Column(SuiCore$Vec3 *  self, SuiCore$Mat3 m, int  index){
	return SuiCore$Vec3$fromArray(self, m.data, index * 3) ; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setFromEuler(SuiCore$Vec3 *  self, SuiCore$Euler e){
	self->x = e.x;
	self->y = e.y;
	self->z = e.z;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$setFromRgbaf(SuiCore$Vec3 *  self, SuiCore$Rgbaf c){
	self->x = c.r;
	self->y = c.g;
	self->z = c.b;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$fromArray(SuiCore$Vec3 *  self, float *  array, int  offset){
	self->x = array[offset];
	self->y = array[offset + 1];
	self->z = array[offset + 2];
	return self; 
}

float *  SuiCore$Vec3$toArray(SuiCore$Vec3 *  self, float *  array, int  offset){
	array[offset] = self->x;
	array[offset + 1] = self->y;
	array[offset + 2] = self->z;
	return array; 
}

SuiCore$Vec3 *  SuiCore$Vec3$randomLocal(SuiCore$Vec3 *  self){
	self->x = Orc$random() ;
	self->y = Orc$random() ;
	self->z = Orc$random() ;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$randomDirectionLocal(SuiCore$Vec3 *  self){
	float  u = (Orc$random()  - 0.5) * 2;
	float  t = Orc$random()  * Orc$PI * 2;
	float  f = sqrt(1 - pow(u, 2) ) ;
	self->x = f * cos(t) ;
	self->y = f * sin(t) ;
	self->z = u;
	return self; 
}

SuiCore$Vec3 SuiCore$Vec3$scale(SuiCore$Vec3 *  self, float  f){
	SuiCore$Vec3 ret = SuiCore$mkVec3(0, 0, 0) ;
	ret.x = self->x * f;
	ret.y = self->y * f;
	ret.z = self->z * f;
	return ret; 
}

SuiCore$Vec3 *  SuiCore$Vec3$add3fLocal(SuiCore$Vec3 *  self, float  x, float  y, float  z){
	self->x += x;
	self->y += y;
	self->z += z;
	return self; 
}

SuiCore$Vec3 SuiCore$Vec3$add3f(SuiCore$Vec3 *  self, float  x, float  y, float  z){
	SuiCore$Vec3 ret = SuiCore$mkVec3(self->x + x, self->y + y, self->z + z) ;
	return ret; 
}

SuiCore$Vec3 SuiCore$Vec3$add(SuiCore$Vec3 *  self, SuiCore$Vec3 b){
	SuiCore$Vec3 ret = SuiCore$mkVec3(0, 0, 0) ;
	ret.x = self->x + b.x;
	ret.y = self->y + b.y;
	ret.z = self->z + b.z;
	return ret; 
}

SuiCore$Vec3 SuiCore$Vec3$sub(SuiCore$Vec3 *  self, SuiCore$Vec3 b){
	SuiCore$Vec3 ret;
	ret.x = self->x - b.x;
	ret.y = self->y - b.y;
	ret.z = self->z - b.z;
	return ret; 
}

void  SuiCore$Vec3$setAll(SuiCore$Vec3 *  self, float  v){
	self->x = v;
	self->y = v;
	self->z = v;
}

bool  SuiCore$Vec3$equals(SuiCore$Vec3 *  self, SuiCore$Vec3 b){
	return fabsf(self->x - b.x)  < 0.00001 && fabsf(self->y - b.y)  < 0.00001 && fabsf(self->z - b.z)  < 0.00001; 
}

SuiCore$Vec3 *  SuiCore$Vec3$clampLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 min, SuiCore$Vec3 max){
	self->x = Orc$maxFloat(min.x, Orc$minFloat(max.x, self->x) ) ;
	self->y = Orc$maxFloat(min.y, Orc$minFloat(max.y, self->y) ) ;
	self->z = Orc$maxFloat(min.z, Orc$minFloat(max.z, self->z) ) ;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$clampScalarLocal(SuiCore$Vec3 *  self, float  minVal, float  maxVal){
	self->x = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->x) ) ;
	self->y = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->y) ) ;
	self->z = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->z) ) ;
	return self; 
}

SuiCore$Vec3 *  SuiCore$Vec3$clampLengthLocal(SuiCore$Vec3 *  self, float  min, float  max){
	float  length = SuiCore$Vec3$length(self) ;
	return SuiCore$Vec3$multiplyScalarLocal(SuiCore$Vec3$divideScalarLocal(self, Orc$eqFloat(length, 0)  ? 1 : length) , Orc$maxFloat(min, Orc$minFloat(max, length) ) ) ; 
}

SuiCore$Vec3 SuiCore$Vec3$clamp(SuiCore$Vec3 *  self, SuiCore$Vec3 min, SuiCore$Vec3 max){
	SuiCore$Vec3 r;
	r.x = Orc$maxFloat(min.x, Orc$minFloat(max.x, self->x) ) ;
	r.y = Orc$maxFloat(min.y, Orc$minFloat(max.y, self->y) ) ;
	r.z = Orc$maxFloat(min.z, Orc$minFloat(max.z, self->z) ) ;
	return r; 
}

SuiCore$Vec3 SuiCore$Vec3$clampScalar(SuiCore$Vec3 *  self, float  minVal, float  maxVal){
	SuiCore$Vec3 r;
	r.x = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->x) ) ;
	r.y = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->y) ) ;
	r.z = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->z) ) ;
	return r; 
}

SuiCore$Vec3 SuiCore$Vec3$clampLength(SuiCore$Vec3 *  self, float  min, float  max){
	float  length = SuiCore$Vec3$length(self) ;
	SuiCore$Vec3 tmp = SuiCore$Vec3$scale(self, 1 / (length == 0 ? 1 : length)) ;
	return SuiCore$Vec3$scale(&tmp, Orc$maxFloat(min, Orc$minFloat(max, length) ) ) ; 
}

SuiCore$Vec3 SuiCore$mkVec3(float  x, float  y, float  z){
	SuiCore$Vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v; 
}

void  SuiCore$testVec3(){
	SuiCore$Vec3 v = SuiCore$mkVec3(0, 0, 0) ;
	v.x = 10;
	v.y = 10;
	SuiCore$Vec3 b = SuiCore$mkVec3(0, 0, 0) ;
	b.x = 17;
	b.y = 17;
	float  dis = SuiCore$Vec3$distanceTo(&v, b) ;
	printf("dis:%f\n", dis) ;
	float  sqrDis = SuiCore$Vec3$distanceToSquared(&v, b) ;
	printf("sqrdis :%f\n", sqrDis) ;
	printf("equals: %d\n", SuiCore$Vec3$equals(&b, v) ) ;
	SuiCore$Vec3$set(&b, 10, 10.00001, 0) ;
	printf("equals:%d\n", SuiCore$Vec3$equals(&b, v) ) ;
	printf("vec3 width:%f, height:%f %f %f\n", SuiCore$Vec3$width(&v) , SuiCore$Vec3$height(&v) , SuiCore$Vec3$width(&b) , SuiCore$Vec3$height(&b) ) ;
}



