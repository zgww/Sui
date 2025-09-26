
#include "Sphere_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sgl/Buffer_orc.h"
#include "../Sgl/Box3_orc.h"
#include "../Sgl/Mat_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* Sgl$Sphere_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$Sphere", sizeof( Sgl$Sphere ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "center", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Sphere, center), false, false, 0);
		orc_metaField_primitive(&pNext, "radius", OrcMetaType_float, offsetof(Sgl$Sphere, radius), 0, 0, 0, 0);//float
    }
	return meta;
}
Sgl$Sphere *  Sgl$Sphere$set(Sgl$Sphere *  self, SuiCore$Vec3 center, float  radius){
	SuiCore$Vec3$copy(&self->center, center) ;
	self->radius = radius;
	return self; 
}

Sgl$Sphere *  Sgl$Sphere$setFromPoints(Sgl$Sphere *  self, Sgl$Vec3Array *  points, SuiCore$Vec3 *  optionalCenter){
	SuiCore$Vec3 *  center = &self->center;
	if (optionalCenter != NULL) {
		SuiCore$Vec3$copy(center, *optionalCenter) ;
	}
	else {
		Sgl$Box3 _box;
		Sgl$Box3$setFromPoints(&_box, points) ;
		self->center = Sgl$Box3$getCenter(&_box) ;
	}
	float  maxRadiusSq = 0;
	int  il = ((Sgl$StructArrayBase * )points)->size;
	for (int  i = 0; i < il; i++) {
		maxRadiusSq = Orc$maxFloat(maxRadiusSq, SuiCore$Vec3$distanceToSquared(center, points->data[i]) ) ;
	}
	self->radius = sqrt(maxRadiusSq) ;
	return self; 
}

Sgl$Sphere *  Sgl$Sphere$copy(Sgl$Sphere *  self, Sgl$Sphere sphere){
	*self = sphere;
	return self; 
}

bool  Sgl$Sphere$isEmpty(Sgl$Sphere *  self){
	return (self->radius < 0); 
}

void  Sgl$Sphere$makeEmpty(Sgl$Sphere *  self){
	SuiCore$Vec3$set(&self->center, 0, 0, 0) ;
	self->radius = -1;
}

bool  Sgl$Sphere$containsPoint(Sgl$Sphere *  self, SuiCore$Vec3 point){
	return (SuiCore$Vec3$distanceToSquared(&point, self->center)  <= (self->radius * self->radius)); 
}

float  Sgl$Sphere$distanceToPoint(Sgl$Sphere *  self, SuiCore$Vec3 point){
	return (SuiCore$Vec3$distanceTo(&point, self->center)  - self->radius); 
}

float  Sgl$Sphere$intersectsSphere(Sgl$Sphere *  self, Sgl$Sphere sphere){
	float  radiusSum = self->radius + sphere.radius;
	return SuiCore$Vec3$distanceToSquared(&sphere.center, self->center)  <= (radiusSum * radiusSum); 
}

bool  Sgl$Sphere$intersectsBox(Sgl$Sphere *  self, Sgl$Box3 box){
	return Sgl$Box3$intersectsSphere(&box, *self) ; 
}

SuiCore$Vec3 Sgl$Sphere$clampPoint(Sgl$Sphere *  self, SuiCore$Vec3 point){
	SuiCore$Vec3 target;
	float  deltaLengthSq = SuiCore$Vec3$distanceToSquared(&self->center, point) ;
	SuiCore$Vec3$copy(&target, point) ;
	if (deltaLengthSq > (self->radius * self->radius)) {
		target = SuiCore$Vec3$sub(&target, self->center) ;
		target = SuiCore$Vec3$normal(&target) ;
		target = SuiCore$Vec3$scale(&target, self->radius) ;
		target = SuiCore$Vec3$add(&target, self->center) ;
	}
	return target; 
}

Sgl$Box3 Sgl$Sphere$getBoundingBox(Sgl$Sphere *  self){
	Sgl$Box3 target;
	if (Sgl$Sphere$isEmpty(self) ) {
		Sgl$Box3$makeEmpty(&target) ;
		return target; 
	}
	Sgl$Box3$set(&target, self->center, self->center) ;
	Sgl$Box3$expandByScalar(&target, self->radius) ;
	return target; 
}

void  Sgl$Sphere$applyMatrix4Local(Sgl$Sphere *  self, Sgl$Mat matrix){
	SuiCore$Vec3$applyMatrix4Local(&self->center, matrix) ;
	self->radius = self->radius * Sgl$Mat$getMaxScaleOnAxis(&matrix) ;
}

void  Sgl$Sphere$translate(Sgl$Sphere *  self, SuiCore$Vec3 offset){
	self->center = SuiCore$Vec3$add(&self->center, offset) ;
}

void  Sgl$Sphere$expandByPoint(Sgl$Sphere *  self, SuiCore$Vec3 point){
	if (Sgl$Sphere$isEmpty(self) ) {
		SuiCore$Vec3$copy(&self->center, point) ;
		self->radius = 0;
		return ; 
	}
	SuiCore$Vec3 _v1 = SuiCore$Vec3$sub(&point, self->center) ;
	float  lengthSq = SuiCore$Vec3$lengthSq(&_v1) ;
	if (lengthSq > (self->radius * self->radius)) {
		float  length = sqrt(lengthSq) ;
		float  delta = (length - self->radius) * 0.5;
		SuiCore$Vec3$addScaledVectorLocal(&self->center, _v1, delta / length) ;
		self->radius += delta;
	}
}

Sgl$Sphere *  Sgl$Sphere$union(Sgl$Sphere *  self, Sgl$Sphere sphere){
	if (Sgl$Sphere$isEmpty(&sphere) ) {
		return self; 
	}
	if (Sgl$Sphere$isEmpty(self) ) {
		Sgl$Sphere$copy(self, sphere) ;
		return self; 
	}
	if (SuiCore$Vec3$equals(&self->center, sphere.center)  == true) {
		self->radius = Orc$maxFloat(self->radius, sphere.radius) ;
	}
	else {
		SuiCore$Vec3 _v2 = SuiCore$Vec3$sub(&sphere.center, self->center) ;
		SuiCore$Vec3$setLength(&_v2, sphere.radius) ;
		Sgl$Sphere$expandByPoint(self, SuiCore$Vec3$add(&sphere.center, _v2) ) ;
		Sgl$Sphere$expandByPoint(self, SuiCore$Vec3$sub(&sphere.center, _v2) ) ;
	}
	return self; 
}

bool  Sgl$Sphere$equals(Sgl$Sphere *  self, Sgl$Sphere sphere){
	return SuiCore$Vec3$equals(&sphere.center, self->center)  && (sphere.radius == self->radius); 
}

Sgl$Sphere Sgl$Sphere$clone(Sgl$Sphere *  self){
	return *self; 
}



