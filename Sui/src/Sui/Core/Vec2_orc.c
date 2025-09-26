
#include "Vec2_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "./Mat3_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$IntVec2_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$IntVec2", sizeof( SuiCore$IntVec2 ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "x", OrcMetaType_int, offsetof(SuiCore$IntVec2, x), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "y", OrcMetaType_int, offsetof(SuiCore$IntVec2, y), 0, 0, 0, 0);//int
    }
	return meta;
}

// get or init meta 
MetaStruct* SuiCore$Vec2_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Vec2", sizeof( SuiCore$Vec2 ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "x", OrcMetaType_float, offsetof(SuiCore$Vec2, x), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "y", OrcMetaType_float, offsetof(SuiCore$Vec2, y), 0, 0, 0, 0);//float
    }
	return meta;
}
Orc$String*  SuiCore$Vec2$toString(Orc$String **  __outRef__, SuiCore$Vec2 *  self){
	char  b[128];
	sprintf(b, "Vec2(%f,%f)", self->x, self->y) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, b) ) ; 
}

float  SuiCore$Vec2$width(SuiCore$Vec2 *  self){
	return self->x; 
}

float  SuiCore$Vec2$height(SuiCore$Vec2 *  self){
	return self->y; 
}

SuiCore$Vec2 *  SuiCore$Vec2$set(SuiCore$Vec2 *  self, float  x, float  y){
	self->x = x;
	self->y = y;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$setScalar(SuiCore$Vec2 *  self, float  scalar){
	self->x = scalar;
	self->y = scalar;
	return self; 
}

void  SuiCore$Vec2$setX(SuiCore$Vec2 *  self, float  x){
	self->x = x;
}

void  SuiCore$Vec2$setY(SuiCore$Vec2 *  self, float  y){
	self->y = y;
}

void  SuiCore$Vec2$setComponent(SuiCore$Vec2 *  self, int  index, float  value){
	if (index == 0) {
		self->x = value;
	}
	else if (index == 1) {
		self->y = value;
	}
}

float  SuiCore$Vec2$getComponent(SuiCore$Vec2 *  self, int  index){
	if (index == 0) {
		return self->x; 
	}
	else if (index == 1) {
		return self->y; 
	}
	return 0.0; 
}

SuiCore$Vec2 SuiCore$Vec2$clone(SuiCore$Vec2 *  self){
	return *self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$copy(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	self->x = v.x;
	self->y = v.y;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$addLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	self->x += v.x;
	self->y += v.y;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$addScalarLocal(SuiCore$Vec2 *  self, float  s){
	self->x += s;
	self->y += s;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$addVectorsLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 a, SuiCore$Vec2 b){
	self->x = a.x + b.x;
	self->y = a.y + b.y;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$addScaledVectorLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v, float  s){
	self->x += v.x * s;
	self->y += v.y * s;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$subLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	self->x -= v.x;
	self->y -= v.y;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$subScalarLocal(SuiCore$Vec2 *  self, float  s){
	self->x -= s;
	self->y -= s;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$subVectorsLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 a, SuiCore$Vec2 b){
	self->x = a.x - b.x;
	self->y = a.y - b.y;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$multiplyLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	self->x *= v.x;
	self->y *= v.y;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$multiplyScalarLocal(SuiCore$Vec2 *  self, float  scalar){
	self->x *= scalar;
	self->y *= scalar;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$divideLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	self->x /= v.x;
	self->y /= v.y;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$divideScalarLocal(SuiCore$Vec2 *  self, float  scalar){
	SuiCore$Vec2$multiplyScalarLocal(self, 1 / scalar) ;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$applyMatrix3Local(SuiCore$Vec2 *  self, SuiCore$Mat3 m){
	float  x = self->x;
	float  y = self->y;
	float *  e = m.data;
	self->x = e[0] * x + e[3] * y + e[6];
	self->y = e[1] * x + e[4] * y + e[7];
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$minLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	self->x = Orc$minFloat(self->x, v.x) ;
	self->y = Orc$minFloat(self->y, v.y) ;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$maxLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	self->x = Orc$maxFloat(self->x, v.x) ;
	self->y = Orc$maxFloat(self->y, v.y) ;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$floorLocal(SuiCore$Vec2 *  self){
	self->x = Orc$floorFloat(self->x) ;
	self->y = Orc$floorFloat(self->y) ;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$ceilLocal(SuiCore$Vec2 *  self){
	self->x = ceil(self->x) ;
	self->y = ceil(self->y) ;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$roundLocal(SuiCore$Vec2 *  self){
	self->x = round(self->x) ;
	self->y = round(self->y) ;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$roundToZeroLocal(SuiCore$Vec2 *  self){
	self->x = (self->x < 0) ? ceil(self->x)  : floor(self->x) ;
	self->y = (self->y < 0) ? ceil(self->y)  : floor(self->y) ;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$negateLocal(SuiCore$Vec2 *  self){
	self->x = -self->x;
	self->y = -self->y;
	return self; 
}

float  SuiCore$Vec2$dot(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	return self->x * v.x + self->y * v.y; 
}

float  SuiCore$Vec2$cross(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	return self->x * v.y - self->y * v.x; 
}

float  SuiCore$Vec2$lengthSq(SuiCore$Vec2 *  self){
	return self->x * self->x + self->y * self->y; 
}

float  SuiCore$Vec2$length(SuiCore$Vec2 *  self){
	return sqrt(self->x * self->x + self->y * self->y) ; 
}

float  SuiCore$Vec2$anhattanLength(SuiCore$Vec2 *  self){
	return Orc$absFloat(self->x)  + Orc$absFloat(self->y) ; 
}

SuiCore$Vec2 *  SuiCore$Vec2$normalizeLocal(SuiCore$Vec2 *  self){
	float  l = SuiCore$Vec2$length(self) ;
	return SuiCore$Vec2$divideScalarLocal(self, Orc$eqFloat(l, 0)  ? 1 : l) ; 
}

float  SuiCore$Vec2$angle(SuiCore$Vec2 *  self){
	float  angle = atan2(-self->y, -self->x)  + Orc$PI;
	return angle; 
}

float  SuiCore$Vec2$angleTo(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	float  denominator = sqrt(SuiCore$Vec2$lengthSq(self)  * SuiCore$Vec2$lengthSq(&v) ) ;
	if (Orc$eqFloat(denominator, 0) ) {
		return Orc$PI / 2.0; 
	}
	float  theta = SuiCore$Vec2$dot(self, v)  / denominator;
	return acos(Orc$clampFloat(theta, -1, 1) ) ; 
}

float  SuiCore$Vec2$distanceTo(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	return sqrt(SuiCore$Vec2$distanceToSquared(self, v) ) ; 
}

float  SuiCore$Vec2$distanceToSquared(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	float  dx = self->x - v.x;
	float  dy = self->y - v.y;
	return dx * dx + dy * dy; 
}

float  SuiCore$Vec2$manhattanDistanceTo(SuiCore$Vec2 *  self, SuiCore$Vec2 v){
	return Orc$absFloat(self->x - v.x)  + Orc$absFloat(self->y - v.y) ; 
}

SuiCore$Vec2 *  SuiCore$Vec2$setLengthLocal(SuiCore$Vec2 *  self, float  length){
	return SuiCore$Vec2$multiplyScalarLocal(SuiCore$Vec2$normalizeLocal(self) , length) ; 
}

SuiCore$Vec2 *  SuiCore$Vec2$lerpLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v, float  alpha){
	self->x += (v.x - self->x) * alpha;
	self->y += (v.y - self->y) * alpha;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$lerpVectorsLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v1, SuiCore$Vec2 v2, float  alpha){
	self->x = v1.x + (v2.x - v1.x) * alpha;
	self->y = v1.y + (v2.y - v1.y) * alpha;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$fromArray(SuiCore$Vec2 *  self, float *  array, int  offset){
	self->x = array[offset];
	self->y = array[offset + 1];
	return self; 
}

float *  SuiCore$Vec2$toArray(SuiCore$Vec2 *  self, float *  array, int  offset){
	array[offset] = self->x;
	array[offset + 1] = self->y;
	return array; 
}

SuiCore$Vec2 *  SuiCore$Vec2$rotateAroundLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 center, float  angle){
	float  c = cos(angle) ;
	float  s = sin(angle) ;
	float  x = self->x - center.x;
	float  y = self->y - center.y;
	self->x = x * c - y * s + center.x;
	self->y = x * s + y * c + center.y;
	return self; 
}

SuiCore$Vec2 *  SuiCore$Vec2$randomLocal(SuiCore$Vec2 *  self){
	self->x = rand() ;
	self->y = rand() ;
	return self; 
}

SuiCore$Vec2 SuiCore$Vec2$scale(SuiCore$Vec2 *  self, float  f){
	SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0) ;
	ret.x = self->x * f;
	ret.y = self->y * f;
	return ret; 
}

SuiCore$Vec2 *  SuiCore$Vec2$clampLengthLocal(SuiCore$Vec2 *  self, float  min, float  max){
	float  length = SuiCore$Vec2$length(self) ;
	SuiCore$Vec2$multiplyScalarLocal(SuiCore$Vec2$divideScalarLocal(self, Orc$eqFloat(length, 0)  ? 1 : length) , Orc$maxFloat(min, Orc$minFloat(max, length) ) ) ;
	return self; 
}

void  SuiCore$Vec2$clampLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 min, SuiCore$Vec2 max){
	self->x = Orc$maxFloat(min.x, Orc$minFloat(max.x, self->x) ) ;
	self->y = Orc$maxFloat(min.y, Orc$minFloat(max.y, self->y) ) ;
}

SuiCore$Vec2 SuiCore$Vec2$clamp(SuiCore$Vec2 *  self, SuiCore$Vec2 min, SuiCore$Vec2 max){
	SuiCore$Vec2 r;
	r.x = Orc$maxFloat(min.x, Orc$minFloat(max.x, self->x) ) ;
	r.y = Orc$maxFloat(min.y, Orc$minFloat(max.y, self->y) ) ;
	return r; 
}

SuiCore$Vec2 *  SuiCore$Vec2$clampScalarLocal(SuiCore$Vec2 *  self, float  minVal, float  maxVal){
	self->x = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->x) ) ;
	self->y = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->y) ) ;
	return self; 
}

SuiCore$Vec2 SuiCore$Vec2$clampScalar(SuiCore$Vec2 *  self, float  minVal, float  maxVal){
	SuiCore$Vec2 r;
	r.x = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->x) ) ;
	r.y = Orc$maxFloat(minVal, Orc$minFloat(maxVal, self->y) ) ;
	return r; 
}

SuiCore$Vec2 SuiCore$Vec2$add(SuiCore$Vec2 *  self, SuiCore$Vec2 b){
	SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0) ;
	ret.x = self->x + b.x;
	ret.y = self->y + b.y;
	return ret; 
}

SuiCore$Vec2 SuiCore$Vec2$sub(SuiCore$Vec2 *  self, SuiCore$Vec2 b){
	SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0) ;
	ret.x = self->x - b.x;
	ret.y = self->y - b.y;
	return ret; 
}

float  SuiCore$Vec2$radToXAxis(SuiCore$Vec2 *  self){
	return atan2(self->y, self->x) ; 
}

bool  SuiCore$Vec2$equals(SuiCore$Vec2 *  self, SuiCore$Vec2 b){
	return fabsf(self->x - b.x)  < Orc$EPSILON && fabsf(self->y - b.y)  < Orc$EPSILON; 
}

SuiCore$Vec2 SuiCore$mkVec2(float  x, float  y){
	SuiCore$Vec2 v;
	v.x = x;
	v.y = y;
	return v; 
}

void  SuiCore$testVec2(){
	SuiCore$Vec2 v = SuiCore$mkVec2(0, 0) ;
	v.x = 10;
	v.y = 10;
	SuiCore$Vec2 b = SuiCore$mkVec2(0, 0) ;
	b.x = 17;
	b.y = 17;
	float  dis = SuiCore$Vec2$distanceTo(&v, b) ;
	printf("dis:%f\n", dis) ;
	float  sqrDis = SuiCore$Vec2$distanceToSquared(&v, b) ;
	printf("sqrdis :%f\n", sqrDis) ;
	printf("equals: %d\n", SuiCore$Vec2$equals(&b, v) ) ;
	SuiCore$Vec2$set(&b, 10, 10.000001) ;
	printf("equals:%d\n", SuiCore$Vec2$equals(&b, v) ) ;
	printf("vec2 width:%f, height:%f %f %f\n", SuiCore$Vec2$width(&v) , SuiCore$Vec2$height(&v) , SuiCore$Vec2$width(&b) , SuiCore$Vec2$height(&b) ) ;
}



