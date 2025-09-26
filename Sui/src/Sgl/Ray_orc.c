
#include "Ray_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "./Sphere_orc.h"
#include "./Box3_orc.h"
#include "./Mat_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* Sgl$Ray_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$Ray", sizeof( Sgl$Ray ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "origin", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Ray, origin), false, false, 0);
		orc_metaField_struct(&pNext, "direction", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Ray, direction), false, false, 0);
    }
	return meta;
}

// get or init meta 
MetaStruct* Sgl$IntersectResult_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$IntersectResult", sizeof( Sgl$IntersectResult ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "point", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$IntersectResult, point), false, false, 0);
		orc_metaField_primitive(&pNext, "succ", OrcMetaType_bool, offsetof(Sgl$IntersectResult, succ), 0, 0, 0, 0);//bool
    }
	return meta;
}
Sgl$IntersectResult Sgl$mkIntersectResult(SuiCore$Vec3 point){
	Sgl$IntersectResult r;
	r.point = point;
	r.succ = true;
	return r; 
}

Sgl$IntersectResult Sgl$mkIntersectResultFail(){
	Sgl$IntersectResult r;
	r.point = SuiCore$mkVec3(0, 0, 0) ;
	r.succ = false;
	return r; 
}

Sgl$Ray Sgl$mkRay(SuiCore$Vec3 origin, SuiCore$Vec3 direction){
	Sgl$Ray r;
	r.origin = origin;
	r.direction = direction;
	return r; 
}

void  Sgl$Ray$set(Sgl$Ray *  self, SuiCore$Vec3 origin, SuiCore$Vec3 direction){
	SuiCore$Vec3$copy(&self->origin, origin) ;
	SuiCore$Vec3$copy(&self->direction, direction) ;
}

void  Sgl$Ray$copy(Sgl$Ray *  self, Sgl$Ray ray){
	*self = ray;
}

SuiCore$Vec3 Sgl$Ray$at(Sgl$Ray *  self, float  t){
	SuiCore$Vec3 target = self->origin;
	SuiCore$Vec3$addScaledVectorLocal(&target, self->direction, t) ;
	return target; 
}

void  Sgl$Ray$lookAt(Sgl$Ray *  self, SuiCore$Vec3 v){
	SuiCore$Vec3 tmp = SuiCore$Vec3$sub(&v, self->origin) ;
	self->direction = SuiCore$Vec3$normal(&tmp) ;
}

void  Sgl$Ray$recast(Sgl$Ray *  self, float  t){
	SuiCore$Vec3$copy(&self->origin, Sgl$Ray$at(self, t) ) ;
}

SuiCore$Vec3 Sgl$Ray$closestPointToPoint(Sgl$Ray *  self, SuiCore$Vec3 point){
	SuiCore$Vec3 target = SuiCore$Vec3$sub(&point, self->origin) ;
	float  directionDistance = SuiCore$Vec3$dot(&target, self->direction) ;
	if (directionDistance < 0) {
		return self->origin; 
	}
	target = self->origin;
	SuiCore$Vec3$addScaledVectorLocal(&target, self->direction, directionDistance) ;
	return target; 
}

float  Sgl$Ray$distanceToPoint(Sgl$Ray *  self, SuiCore$Vec3 point){
	return sqrt(Sgl$Ray$distanceSqToPoint(self, point) ) ; 
}

float  Sgl$Ray$distanceSqToPoint(Sgl$Ray *  self, SuiCore$Vec3 point){
	SuiCore$Vec3 _v = SuiCore$Vec3$sub(&point, self->origin) ;
	float  directionDistance = SuiCore$Vec3$dot(&_v, self->direction) ;
	if (directionDistance < 0) {
		return SuiCore$Vec3$distanceToSquared(&self->origin, point) ; 
	}
	SuiCore$Vec3 tmp = self->origin;
	SuiCore$Vec3$addScaledVectorLocal(&tmp, self->direction, directionDistance) ;
	return SuiCore$Vec3$distanceToSquared(&tmp, point) ; 
}

Sgl$IntersectResult Sgl$Ray$intersectSphere(Sgl$Ray *  self, Sgl$Sphere sphere, SuiCore$Vec3 result){
	SuiCore$Vec3 target;
	SuiCore$Vec3 _vector = SuiCore$Vec3$sub(&sphere.center, self->origin) ;
	float  tca = SuiCore$Vec3$dot(&_vector, self->direction) ;
	float  d2 = SuiCore$Vec3$dot(&_vector, _vector)  - tca * tca;
	float  radius2 = sphere.radius * sphere.radius;
	if (d2 > radius2) {
		return Sgl$mkIntersectResultFail() ; 
	}
	float  thc = sqrt(radius2 - d2) ;
	float  t0 = tca - thc;
	float  t1 = tca + thc;
	if (t1 < 0) {
		return Sgl$mkIntersectResultFail() ; 
	}
	if (t0 < 0) {
		return Sgl$mkIntersectResult(Sgl$Ray$at(self, t1) ) ; 
	}
	return Sgl$mkIntersectResult(Sgl$Ray$at(self, t0) ) ; 
}

bool  Sgl$Ray$intersectsSphere(Sgl$Ray *  self, Sgl$Sphere sphere){
	return Sgl$Ray$distanceSqToPoint(self, sphere.center)  <= (sphere.radius * sphere.radius); 
}

Sgl$IntersectResult Sgl$Ray$intersectBox(Sgl$Ray *  self, Sgl$Box3 box){
	float  tmin = 0;
	float  tmax = 0;
	float  tymin = 0;
	float  tymax = 0;
	float  tzmin = 0;
	float  tzmax = 0;
	float  invdirx = 1 / self->direction.x;
	float  invdiry = 1 / self->direction.y;
	float  invdirz = 1 / self->direction.z;
	SuiCore$Vec3 origin = self->origin;
	if (invdirx >= 0) {
		tmin = (box.min.x - origin.x) * invdirx;
		tmax = (box.max.x - origin.x) * invdirx;
	}
	else {
		tmin = (box.max.x - origin.x) * invdirx;
		tmax = (box.min.x - origin.x) * invdirx;
	}
	if (invdiry >= 0) {
		tymin = (box.min.y - origin.y) * invdiry;
		tymax = (box.max.y - origin.y) * invdiry;
	}
	else {
		tymin = (box.max.y - origin.y) * invdiry;
		tymax = (box.min.y - origin.y) * invdiry;
	}
	if ((tmin > tymax) || (tymin > tmax)) {
		return Sgl$mkIntersectResultFail() ; 
	}
	if (tymin > tmin || Orc$isNaN(tmin) ) {
		tmin = tymin;
	}
	if (tymax < tmax || Orc$isNaN(tmax) ) {
		tmax = tymax;
	}
	if (invdirz >= 0) {
		tzmin = (box.min.z - origin.z) * invdirz;
		tzmax = (box.max.z - origin.z) * invdirz;
	}
	else {
		tzmin = (box.max.z - origin.z) * invdirz;
		tzmax = (box.min.z - origin.z) * invdirz;
	}
	if ((tmin > tzmax) || (tzmin > tmax)) {
		return Sgl$mkIntersectResultFail() ; 
	}
	if (tzmin > tmin || tmin != tmin) {
		tmin = tzmin;
	}
	if (tzmax < tmax || tmax != tmax) {
		tmax = tzmax;
	}
	if (tmax < 0) {
		return Sgl$mkIntersectResultFail() ; 
	}
	return Sgl$mkIntersectResult(Sgl$Ray$at(self, tmin >= 0 ? tmin : tmax) ) ; 
}

bool  Sgl$Ray$intersectsBox(Sgl$Ray *  self, Sgl$Box3 box){
	return Sgl$Ray$intersectBox(self, box) .succ; 
}

Sgl$IntersectResult Sgl$Ray$intersectTriangle(Sgl$Ray *  self, SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c, bool  backfaceCulling){
	SuiCore$Vec3 _edge1 = SuiCore$Vec3$sub(&b, a) ;
	SuiCore$Vec3 _edge2 = SuiCore$Vec3$sub(&c, a) ;
	SuiCore$Vec3 _normal = SuiCore$Vec3$cross(&_edge1, _edge2) ;
	float  DdN = SuiCore$Vec3$dot(&self->direction, _normal) ;
	float  sign;
	if (DdN > 0) {
		if (backfaceCulling) {
			return Sgl$mkIntersectResultFail() ; 
		}
		sign = 1;
	}
	else if (DdN < 0) {
		sign = -1;
		DdN = -DdN;
	}
	else {
		return Sgl$mkIntersectResultFail() ; 
	}
	SuiCore$Vec3 _diff = SuiCore$Vec3$sub(&self->origin, a) ;
	_edge2 = SuiCore$Vec3$cross(&_diff, _edge2) ;
	float  DdQxE2 = sign * SuiCore$Vec3$dot(&self->direction, _edge2) ;
	if (DdQxE2 < 0) {
		return Sgl$mkIntersectResultFail() ; 
	}
	float  DdE1xQ = sign * SuiCore$Vec3$dot(&self->direction, SuiCore$Vec3$cross(&_edge1, _diff) ) ;
	if (DdE1xQ < 0) {
		return Sgl$mkIntersectResultFail() ; 
	}
	if (DdQxE2 + DdE1xQ > DdN) {
		return Sgl$mkIntersectResultFail() ; 
	}
	float  QdN = -sign * SuiCore$Vec3$dot(&_diff, _normal) ;
	if (QdN < 0) {
		return Sgl$mkIntersectResultFail() ; 
	}
	return Sgl$mkIntersectResult(Sgl$Ray$at(self, QdN / DdN) ) ; 
}

void  Sgl$Ray$applyMatrix4Local(Sgl$Ray *  self, Sgl$Mat matrix4){
	SuiCore$Vec3$applyMatrix4Local(&self->origin, matrix4) ;
	SuiCore$Vec3$transformDirectionLocal(&self->direction, matrix4) ;
}

bool  Sgl$Ray$equals(Sgl$Ray *  self, Sgl$Ray ray){
	return SuiCore$Vec3$equals(&ray.origin, self->origin)  && SuiCore$Vec3$equals(&ray.direction, self->direction) ; 
}

Sgl$Ray Sgl$Ray$clone(Sgl$Ray *  self){
	return *self; 
}



