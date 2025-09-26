
#include "Box2_orc.h" 

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sgl/Buffer_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* Sgl$Box2_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$Box2", sizeof( Sgl$Box2 ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "min", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(Sgl$Box2, min), false, false, 0);
		orc_metaField_struct(&pNext, "max", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(Sgl$Box2, max), false, false, 0);
    }
	return meta;
}
Sgl$Box2 Sgl$mkBox2Zero(){
	Sgl$Box2 r;
	memset(&r, 0, sizeof(Sgl$Box2) ) ;
	return r; 
}

void  Sgl$Box2$set(Sgl$Box2 *  self, SuiCore$Vec2 min, SuiCore$Vec2 max){
	SuiCore$Vec2$copy(&self->min, min) ;
	SuiCore$Vec2$copy(&self->max, max) ;
}

Sgl$Box2 *  Sgl$Box2$setFromPoints(Sgl$Box2 *  self, Sgl$Vec2Array *  points){
	Sgl$Box2$makeEmpty(self) ;
	int  il = ((Sgl$StructArrayBase * )points)->size;
	for (int  i = 0; i < il; i++) {
		Sgl$Box2$expandByPoint(self, points->data[i]) ;
	}
	return self; 
}

void  Sgl$Box2$setFromCenterAndSize(Sgl$Box2 *  self, SuiCore$Vec2 center, SuiCore$Vec2 size){
	SuiCore$Vec2 halfSize = SuiCore$Vec2$scale(&size, 0.5) ;
	self->min = SuiCore$Vec2$sub(&center, halfSize) ;
	self->max = SuiCore$Vec2$add(&center, halfSize) ;
}

void  Sgl$Box2$makeEmpty(Sgl$Box2 *  self){
	self->min.x = self->min.y = +INFINITY;
	self->max.x = self->max.y = -INFINITY;
}

bool  Sgl$Box2$isEmpty(Sgl$Box2 *  self){
	return (self->max.x < self->min.x) || (self->max.y < self->min.y); 
}

SuiCore$Vec2 Sgl$Box2$getCenter(Sgl$Box2 *  self){
	if (Sgl$Box2$isEmpty(self) ) {
		return SuiCore$mkVec2(0, 0) ; 
	}
	SuiCore$Vec2 tmp = SuiCore$Vec2$add(&self->min, self->max) ;
	return SuiCore$Vec2$scale(&tmp, 0.5) ; 
}

SuiCore$Vec2 Sgl$Box2$getSize(Sgl$Box2 *  self){
	if (Sgl$Box2$isEmpty(self) ) {
		return SuiCore$mkVec2(0, 0) ; 
	}
	SuiCore$Vec2 tmp = SuiCore$Vec2$sub(&self->max, self->min) ;
	return tmp; 
}

void  Sgl$Box2$expandByPoint(Sgl$Box2 *  self, SuiCore$Vec2 point){
	SuiCore$Vec2$minLocal(&self->min, point) ;
	SuiCore$Vec2$maxLocal(&self->max, point) ;
}

void  Sgl$Box2$expandByVector(Sgl$Box2 *  self, SuiCore$Vec2 vector){
	self->min = SuiCore$Vec2$sub(&self->min, vector) ;
	self->max = SuiCore$Vec2$add(&self->max, vector) ;
}

void  Sgl$Box2$expandByScalar(Sgl$Box2 *  self, float  scalar){
	SuiCore$Vec2$addScalarLocal(&self->min, -scalar) ;
	SuiCore$Vec2$addScalarLocal(&self->max, scalar) ;
}

bool  Sgl$Box2$containsPoint(Sgl$Box2 *  self, SuiCore$Vec2 point){
	return point.x < self->min.x || point.x > self->max.x || point.y < self->min.y || point.y > self->max.y ? false : true; 
}

bool  Sgl$Box2$containsBox(Sgl$Box2 *  self, Sgl$Box2 box){
	return self->min.x <= box.min.x && box.max.x <= self->max.x && self->min.y <= box.min.y && box.max.y <= self->max.y; 
}

SuiCore$Vec2 Sgl$Box2$getParameter(Sgl$Box2 *  self, SuiCore$Vec2 point){
	SuiCore$Vec2 target;
	SuiCore$Vec2$set(&target, (point.x - self->min.x) / (self->max.x - self->min.x), (point.y - self->min.y) / (self->max.y - self->min.y)) ;
	return target; 
}

bool  Sgl$Box2$intersectsBox(Sgl$Box2 *  self, Sgl$Box2 box){
	return box.max.x < self->min.x || box.min.x > self->max.x || box.max.y < self->min.y || box.min.y > self->max.y ? false : true; 
}

SuiCore$Vec2 Sgl$Box2$clampPoint(Sgl$Box2 *  self, SuiCore$Vec2 point){
	return SuiCore$Vec2$clamp(&point, self->min, self->max) ; 
}

float  Sgl$Box2$distanceToPoint(Sgl$Box2 *  self, SuiCore$Vec2 point){
	SuiCore$Vec2 tmpStructThis1;
	return SuiCore$Vec2$distanceTo((tmpStructThis1 = Sgl$Box2$clampPoint(self, point) ,&tmpStructThis1), point) ; 
}

void  Sgl$Box2$intersect(Sgl$Box2 *  self, Sgl$Box2 box){
	SuiCore$Vec2$maxLocal(&self->min, box.min) ;
	SuiCore$Vec2$minLocal(&self->max, box.max) ;
	if (Sgl$Box2$isEmpty(self) ) {
		Sgl$Box2$makeEmpty(self) ;
	}
}

void  Sgl$Box2$union(Sgl$Box2 *  self, Sgl$Box2 box){
	SuiCore$Vec2$minLocal(&self->min, box.min) ;
	SuiCore$Vec2$maxLocal(&self->max, box.max) ;
}

void  Sgl$Box2$translate(Sgl$Box2 *  self, SuiCore$Vec2 offset){
	self->min = SuiCore$Vec2$add(&self->min, offset) ;
	self->max = SuiCore$Vec2$add(&self->max, offset) ;
}

bool  Sgl$Box2$equals(Sgl$Box2 *  self, Sgl$Box2 box){
	return SuiCore$Vec2$equals(&box.min, self->min)  && SuiCore$Vec2$equals(&box.max, self->max) ; 
}



