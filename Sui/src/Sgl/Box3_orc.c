
#include "Box3_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Sui/Core/Vec3_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sgl/Buffer_orc.h"
#include "./Sphere_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* Sgl$Box3_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$Box3", sizeof( Sgl$Box3 ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "min", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Box3, min), false, false, 0);
		orc_metaField_struct(&pNext, "max", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Box3, max), false, false, 0);
    }
	return meta;
}
void  Sgl$Box3$set(Sgl$Box3 *  self, SuiCore$Vec3 min, SuiCore$Vec3 max){
	SuiCore$Vec3$copy(&self->min, min) ;
	SuiCore$Vec3$copy(&self->max, max) ;
}

void  Sgl$Box3$setFromArray(Sgl$Box3 *  self, Sgl$FloatArray *  array){
	Sgl$Box3$makeEmpty(self) ;
	int  il = ((Sgl$StructArrayBase * )array)->size;
	for (int  i = 0; i < il; i += 3) {
		Sgl$Box3$expandByPoint(self, SuiCore$mkVec3(array->data[i], array->data[i + 1], array->data[i + 2]) ) ;
	}
}

void  Sgl$Box3$setFromPoints(Sgl$Box3 *  self, Sgl$Vec3Array *  points){
	Sgl$Box3$makeEmpty(self) ;
	int  il = ((Sgl$StructArrayBase * )points)->size;
	for (int  i = 0; i < il; i++) {
		Sgl$Box3$expandByPoint(self, points->data[i]) ;
	}
}

void  Sgl$Box3$setFromCenterAndSize(Sgl$Box3 *  self, SuiCore$Vec3 center, SuiCore$Vec3 size){
	SuiCore$Vec3 halfSize = SuiCore$Vec3$scale(&size, 0.5) ;
	self->min = SuiCore$Vec3$sub(&center, halfSize) ;
	self->max = SuiCore$Vec3$add(&center, halfSize) ;
}

Sgl$Box3 Sgl$Box3$clone(Sgl$Box3 *  self){
	return *self; 
}

void  Sgl$Box3$copy(Sgl$Box3 *  self, Sgl$Box3 box){
	SuiCore$Vec3$copy(&self->min, box.min) ;
	SuiCore$Vec3$copy(&self->max, box.max) ;
}

void  Sgl$Box3$makeEmpty(Sgl$Box3 *  self){
	self->min.x = self->min.y = self->min.z = +INFINITY;
	self->max.x = self->max.y = self->max.z = -INFINITY;
}

bool  Sgl$Box3$isEmpty(Sgl$Box3 *  self){
	return (self->max.x < self->min.x) || (self->max.y < self->min.y) || (self->max.z < self->min.z); 
}

SuiCore$Vec3 Sgl$Box3$getCenter(Sgl$Box3 *  self){
	SuiCore$Vec3 tmpStructThis1;
	return Sgl$Box3$isEmpty(self)  ? SuiCore$mkVec3(0, 0, 0)  : SuiCore$Vec3$scale((tmpStructThis1 = SuiCore$Vec3$add(&self->min, self->max) ,&tmpStructThis1), 0.5) ; 
}

SuiCore$Vec3 Sgl$Box3$getSize(Sgl$Box3 *  self){
	return Sgl$Box3$isEmpty(self)  ? SuiCore$mkVec3(0, 0, 0)  : SuiCore$Vec3$sub(&self->max, self->min) ; 
}

void  Sgl$Box3$expandByPoint(Sgl$Box3 *  self, SuiCore$Vec3 point){
	SuiCore$Vec3$minLocal(&self->min, point) ;
	SuiCore$Vec3$maxLocal(&self->max, point) ;
}

void  Sgl$Box3$expandByVector(Sgl$Box3 *  self, SuiCore$Vec3 vector){
	self->min = SuiCore$Vec3$sub(&self->min, vector) ;
	self->max = SuiCore$Vec3$add(&self->max, vector) ;
}

void  Sgl$Box3$expandByScalar(Sgl$Box3 *  self, float  scalar){
	SuiCore$Vec3$addScalarLocal(&self->min, -scalar) ;
	SuiCore$Vec3$addScalarLocal(&self->max, scalar) ;
}

bool  Sgl$Box3$containsPoint(Sgl$Box3 *  self, SuiCore$Vec3 point){
	return point.x < self->min.x || point.x > self->max.x || point.y < self->min.y || point.y > self->max.y || point.z < self->min.z || point.z > self->max.z ? false : true; 
}

bool  Sgl$Box3$containsBox(Sgl$Box3 *  self, Sgl$Box3 box){
	return self->min.x <= box.min.x && box.max.x <= self->max.x && self->min.y <= box.min.y && box.max.y <= self->max.y && self->min.z <= box.min.z && box.max.z <= self->max.z; 
}

SuiCore$Vec3 Sgl$Box3$getParameter(Sgl$Box3 *  self, SuiCore$Vec3 point){
	return SuiCore$mkVec3((point.x - self->min.x) / (self->max.x - self->min.x), (point.y - self->min.y) / (self->max.y - self->min.y), (point.z - self->min.z) / (self->max.z - self->min.z)) ; 
}

bool  Sgl$Box3$intersectsBox(Sgl$Box3 *  self, Sgl$Box3 box){
	return box.max.x < self->min.x || box.min.x > self->max.x || box.max.y < self->min.y || box.min.y > self->max.y || box.max.z < self->min.z || box.min.z > self->max.z ? false : true; 
}

bool  Sgl$Box3$intersectsSphere(Sgl$Box3 *  self, Sgl$Sphere sphere){
	SuiCore$Vec3 _vector = Sgl$Box3$clampPoint(self, sphere.center) ;
	return SuiCore$Vec3$distanceToSquared(&_vector, sphere.center)  <= (sphere.radius * sphere.radius); 
}

SuiCore$Vec3 Sgl$Box3$clampPoint(Sgl$Box3 *  self, SuiCore$Vec3 point){
	return SuiCore$Vec3$clamp(&point, self->min, self->max) ; 
}

float  Sgl$Box3$distanceToPoint(Sgl$Box3 *  self, SuiCore$Vec3 point){
	SuiCore$Vec3 _vector = Sgl$Box3$clampPoint(self, point) ;
	float  r = SuiCore$Vec3$distanceTo(&_vector, point) ;
	return r; 
}

Sgl$Sphere Sgl$Box3$getBoundingSphere(Sgl$Box3 *  self){
	if (Sgl$Box3$isEmpty(self) ) {
		Sgl$Sphere s;
		Sgl$Sphere$makeEmpty(&s) ;
		return s; 
	}
	else {
		Sgl$Sphere target;
		target.center = Sgl$Box3$getCenter(self) ;
		SuiCore$Vec3 tmpStructThis1;
		target.radius = SuiCore$Vec3$length((tmpStructThis1 = Sgl$Box3$getSize(self) ,&tmpStructThis1))  * 0.5;
		return target; 
	}
}

Sgl$Box3 Sgl$Box3$intersect(Sgl$Box3 *  self, Sgl$Box3 box){
	Sgl$Box3 r = *self;
	SuiCore$Vec3$maxLocal(&r.min, box.min) ;
	SuiCore$Vec3$minLocal(&r.max, box.max) ;
	if (Sgl$Box3$isEmpty(&r) ) {
		Sgl$Box3$makeEmpty(&r) ;
	}
	return r; 
}

Sgl$Box3 Sgl$Box3$union(Sgl$Box3 *  self, Sgl$Box3 box){
	Sgl$Box3 r = *self;
	SuiCore$Vec3$minLocal(&r.min, box.min) ;
	SuiCore$Vec3$maxLocal(&r.max, box.max) ;
	return r; 
}

void  Sgl$Box3$translate(Sgl$Box3 *  self, SuiCore$Vec3 offset){
	self->min = SuiCore$Vec3$add(&self->min, offset) ;
	self->max = SuiCore$Vec3$add(&self->max, offset) ;
}

bool  Sgl$Box3$equals(Sgl$Box3 *  self, Sgl$Box3 box){
	return SuiCore$Vec3$equals(&box.min, self->min)  && SuiCore$Vec3$equals(&box.max, self->max) ; 
}



