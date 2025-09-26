
#include "Triangle_orc.h" 

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
#include "./Spherical_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Triangle_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Triangle", sizeof( SuiCore$Triangle ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "a", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiCore$Triangle, a), false, false, 0);
		orc_metaField_struct(&pNext, "b", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiCore$Triangle, b), false, false, 0);
		orc_metaField_struct(&pNext, "c", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiCore$Triangle, c), false, false, 0);
    }
	return meta;
}
SuiCore$Triangle *  SuiCore$Triangle$set(SuiCore$Triangle *  self, SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c){
	SuiCore$Vec3$copy(&self->a, a) ;
	SuiCore$Vec3$copy(&self->b, b) ;
	SuiCore$Vec3$copy(&self->c, c) ;
	return self; 
}

SuiCore$Triangle *  SuiCore$Triangle$setFromPointsAndIndices(SuiCore$Triangle *  self, SuiCore$Vec3 *  points, int  i0, int  i1, int  i2){
	SuiCore$Vec3$copy(&self->a, points[i0]) ;
	SuiCore$Vec3$copy(&self->b, points[i1]) ;
	SuiCore$Vec3$copy(&self->c, points[i2]) ;
	return self; 
}

SuiCore$Triangle SuiCore$Triangle$clone(SuiCore$Triangle *  self){
	return *self; 
}

SuiCore$Triangle *  SuiCore$Triangle$copy(SuiCore$Triangle *  self, SuiCore$Triangle triangle){
	SuiCore$Vec3$copy(&self->a, triangle.a) ;
	SuiCore$Vec3$copy(&self->b, triangle.b) ;
	SuiCore$Vec3$copy(&self->c, triangle.c) ;
	return self; 
}

float  SuiCore$Triangle$getArea(SuiCore$Triangle *  self){
	SuiCore$Vec3 _v0;
	SuiCore$Vec3 _v1;
	SuiCore$Vec3$subVectorsLocal(&_v0, self->c, self->b) ;
	SuiCore$Vec3$subVectorsLocal(&_v1, self->a, self->b) ;
	SuiCore$Vec3 tmpStructThis1;
	return SuiCore$Vec3$length((tmpStructThis1 = SuiCore$Vec3$cross(&_v0, _v1) ,&tmpStructThis1))  * 0.5; 
}

SuiCore$Vec3 SuiCore$Triangle$getMidpoint(SuiCore$Triangle *  self){
	SuiCore$Vec3 target;
	SuiCore$Vec3$multiplyScalarLocal(SuiCore$Vec3$addLocal(SuiCore$Vec3$addVectorsLocal(&target, self->a, self->b) , self->c) , 1 / 3.0) ;
	return target; 
}

SuiCore$Vec3 SuiCore$Triangle$getNormal(SuiCore$Triangle *  self){
	SuiCore$Vec3 target;
	target = SuiCore$Triangle_getNormal(self->a, self->b, self->c) ;
	return target; 
}

SuiCore$Plane SuiCore$Triangle$getPlane(SuiCore$Triangle *  self){
	SuiCore$Plane target;
	SuiCore$Plane$setFromCoplanarPoints(&target, self->a, self->b, self->c) ;
	return target; 
}

SuiCore$Vec3 SuiCore$Triangle$getBarycoord(SuiCore$Triangle *  self, SuiCore$Vec3 point){
	return SuiCore$Triangle_getBarycoord(point, self->a, self->b, self->c) ; 
}

SuiCore$Vec3 SuiCore$Triangle$getInterpolation(SuiCore$Triangle *  self, SuiCore$Vec3 point, SuiCore$Vec3 v1, SuiCore$Vec3 v2, SuiCore$Vec3 v3){
	return SuiCore$Triangle_getInterpolation(point, self->a, self->b, self->c, v1, v2, v3) ; 
}

bool  SuiCore$Triangle$containsPoint(SuiCore$Triangle *  self, SuiCore$Vec3 point){
	return SuiCore$Triangle_containsPoint(point, self->a, self->b, self->c) ; 
}

bool  SuiCore$Triangle$isFrontFacing(SuiCore$Triangle *  self, SuiCore$Vec3 direction){
	return SuiCore$Triangle_isFrontFacing(self->a, self->b, self->c, direction) ; 
}

SuiCore$Vec3 SuiCore$Triangle$closestPointToPoint(SuiCore$Triangle *  self, SuiCore$Vec3 p){
	SuiCore$Vec3 target;
	SuiCore$Vec3 _vab;
	SuiCore$Vec3 _vac;
	SuiCore$Vec3 _vap;
	SuiCore$Vec3 _vbp;
	SuiCore$Vec3 _vcp;
	SuiCore$Vec3 _vbc;
	SuiCore$Vec3 a = self->a;
	SuiCore$Vec3 b = self->b;
	SuiCore$Vec3 c = self->c;
	float  v;
	float  w;
	SuiCore$Vec3$subVectorsLocal(&_vab, b, a) ;
	SuiCore$Vec3$subVectorsLocal(&_vac, c, a) ;
	SuiCore$Vec3$subVectorsLocal(&_vap, p, a) ;
	float  d1 = SuiCore$Vec3$dot(&_vab, _vap) ;
	float  d2 = SuiCore$Vec3$dot(&_vac, _vap) ;
	if (d1 <= 0 && d2 <= 0) {
		SuiCore$Vec3$copy(&target, a) ;
		return target; 
	}
	SuiCore$Vec3$subVectorsLocal(&_vbp, p, b) ;
	float  d3 = SuiCore$Vec3$dot(&_vab, _vbp) ;
	float  d4 = SuiCore$Vec3$dot(&_vac, _vbp) ;
	if (d3 >= 0 && d4 <= d3) {
		SuiCore$Vec3$copy(&target, b) ;
		return target; 
	}
	float  vc = d1 * d4 - d3 * d2;
	if (vc <= 0 && d1 >= 0 && d3 <= 0) {
		v = d1 / (d1 - d3);
		SuiCore$Vec3$addScaledVectorLocal(SuiCore$Vec3$copy(&target, a) , _vab, v) ;
		return target; 
	}
	SuiCore$Vec3$subVectorsLocal(&_vcp, p, c) ;
	float  d5 = SuiCore$Vec3$dot(&_vab, _vcp) ;
	float  d6 = SuiCore$Vec3$dot(&_vac, _vcp) ;
	if (d6 >= 0 && d5 <= d6) {
		SuiCore$Vec3$copy(&target, c) ;
		return target; 
	}
	float  vb = d5 * d2 - d1 * d6;
	if (vb <= 0 && d2 >= 0 && d6 <= 0) {
		w = d2 / (d2 - d6);
		SuiCore$Vec3$addScaledVectorLocal(SuiCore$Vec3$copy(&target, a) , _vac, w) ;
		return target; 
	}
	float  va = d3 * d6 - d5 * d4;
	if (va <= 0 && (d4 - d3) >= 0 && (d5 - d6) >= 0) {
		SuiCore$Vec3$subVectorsLocal(&_vbc, c, b) ;
		w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		SuiCore$Vec3$addScaledVectorLocal(SuiCore$Vec3$copy(&target, b) , _vbc, w) ;
		return target; 
	}
	float  denom = 1 / (va + vb + vc);
	v = vb * denom;
	w = vc * denom;
	SuiCore$Vec3$addScaledVectorLocal(SuiCore$Vec3$addScaledVectorLocal(SuiCore$Vec3$copy(&target, a) , _vab, v) , _vac, w) ;
	return target; 
}

bool  SuiCore$Triangle$equals(SuiCore$Triangle *  self, SuiCore$Triangle triangle){
	return SuiCore$Vec3$equals(&triangle.a, self->a)  && SuiCore$Vec3$equals(&triangle.b, self->b)  && SuiCore$Vec3$equals(&triangle.c, self->c) ; 
}

SuiCore$Vec3 SuiCore$Triangle_getNormal(SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c){
	SuiCore$Vec3 target;
	SuiCore$Vec3 _v0;
	SuiCore$Vec3$subVectorsLocal(&target, c, b) ;
	SuiCore$Vec3$subVectorsLocal(&_v0, a, b) ;
	SuiCore$Vec3$crossLocal(&target, _v0) ;
	float  targetLengthSq = SuiCore$Vec3$lengthSq(&target) ;
	if (targetLengthSq > 0) {
		SuiCore$Vec3$multiplyScalarLocal(&target, 1 / sqrt(targetLengthSq) ) ;
		return target; 
	}
	SuiCore$Vec3$set(&target, 0, 0, 0) ;
	return target; 
}

SuiCore$Vec3 SuiCore$Triangle_getBarycoord(SuiCore$Vec3 point, SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c){
	SuiCore$Vec3 target;
	SuiCore$Vec3 _v0;
	SuiCore$Vec3 _v1;
	SuiCore$Vec3 _v2;
	SuiCore$Vec3$subVectorsLocal(&_v0, c, a) ;
	SuiCore$Vec3$subVectorsLocal(&_v1, b, a) ;
	SuiCore$Vec3$subVectorsLocal(&_v2, point, a) ;
	float  dot00 = SuiCore$Vec3$dot(&_v0, _v0) ;
	float  dot01 = SuiCore$Vec3$dot(&_v0, _v1) ;
	float  dot02 = SuiCore$Vec3$dot(&_v0, _v2) ;
	float  dot11 = SuiCore$Vec3$dot(&_v1, _v1) ;
	float  dot12 = SuiCore$Vec3$dot(&_v1, _v2) ;
	float  denom = (dot00 * dot11 - dot01 * dot01);
	if (denom == 0) {
		SuiCore$Vec3$set(&target, -2, -1, -1) ;
		return target; 
	}
	float  invDenom = 1 / denom;
	float  u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float  v = (dot00 * dot12 - dot01 * dot02) * invDenom;
	SuiCore$Vec3$set(&target, 1 - u - v, v, u) ;
	return target; 
}

bool  SuiCore$Triangle_containsPoint(SuiCore$Vec3 point, SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c){
	SuiCore$Vec3 _v3 = SuiCore$Triangle_getBarycoord(point, a, b, c) ;
	return (_v3.x >= 0) && (_v3.y >= 0) && ((_v3.x + _v3.y) <= 1); 
}

bool  SuiCore$Triangle_isFrontFacing(SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c, SuiCore$Vec3 direction){
	SuiCore$Vec3 _v0;
	SuiCore$Vec3 _v1;
	SuiCore$Vec3$subVectorsLocal(&_v0, c, b) ;
	SuiCore$Vec3$subVectorsLocal(&_v1, a, b) ;
	SuiCore$Vec3 tmpStructThis1;
	return (SuiCore$Vec3$dot((tmpStructThis1 = SuiCore$Vec3$cross(&_v0, _v1) ,&tmpStructThis1), direction)  < 0) ? true : false; 
}

SuiCore$Vec3 SuiCore$Triangle_getInterpolation(SuiCore$Vec3 point, SuiCore$Vec3 p1, SuiCore$Vec3 p2, SuiCore$Vec3 p3, SuiCore$Vec3 v1, SuiCore$Vec3 v2, SuiCore$Vec3 v3){
	SuiCore$Vec3 target;
	SuiCore$Vec3 _v3 = SuiCore$Triangle_getBarycoord(point, p1, p2, p3) ;
	SuiCore$Vec3$setScalar(&target, 0) ;
	SuiCore$Vec3$addScaledVectorLocal(&target, v1, _v3.x) ;
	SuiCore$Vec3$addScaledVectorLocal(&target, v2, _v3.y) ;
	SuiCore$Vec3$addScaledVectorLocal(&target, v3, _v3.z) ;
	return target; 
}



