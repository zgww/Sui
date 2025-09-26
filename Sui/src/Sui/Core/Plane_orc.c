
#include "Plane_orc.h" 

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "../../Sgl/Sphere_orc.h"
#include "./Mat3_orc.h"
#include "./Vec3_orc.h"
#include "./Spherical_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Plane_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Plane", sizeof( SuiCore$Plane ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "normal", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiCore$Plane, normal), false, false, 0);
		orc_metaField_primitive(&pNext, "constant", OrcMetaType_float, offsetof(SuiCore$Plane, constant), 0, 0, 0, 0);//float
    }
	return meta;
}
SuiCore$Plane *  SuiCore$Plane$set(SuiCore$Plane *  self, SuiCore$Vec3 normal, float  constant){
	SuiCore$Vec3$copy(&self->normal, normal) ;
	self->constant = constant;
	return self; 
}

SuiCore$Plane *  SuiCore$Plane$setComponents(SuiCore$Plane *  self, float  x, float  y, float  z, float  w){
	SuiCore$Vec3$set(&self->normal, x, y, z) ;
	self->constant = w;
	return self; 
}

SuiCore$Plane *  SuiCore$Plane$setFromNormalAndCoplanarPoint(SuiCore$Plane *  self, SuiCore$Vec3 normal, SuiCore$Vec3 point){
	SuiCore$Vec3$copy(&self->normal, normal) ;
	self->constant = -SuiCore$Vec3$dot(&point, self->normal) ;
	return self; 
}

SuiCore$Plane *  SuiCore$Plane$setFromCoplanarPoints(SuiCore$Plane *  self, SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c){
	SuiCore$Vec3 tmpStructThis1;
	SuiCore$Vec3 tmpStructThis2;
	SuiCore$Vec3 normal = SuiCore$Vec3$normal((tmpStructThis1 = SuiCore$Vec3$cross((tmpStructThis2 = SuiCore$Vec3$sub(&c, b) ,&tmpStructThis2), SuiCore$Vec3$sub(&a, b) ) ,&tmpStructThis1)) ;
	SuiCore$Plane$setFromNormalAndCoplanarPoint(self, normal, a) ;
	return self; 
}

SuiCore$Plane *  SuiCore$Plane$copy(SuiCore$Plane *  self, SuiCore$Plane plane){
	SuiCore$Vec3$copy(&self->normal, plane.normal) ;
	self->constant = plane.constant;
	return self; 
}

SuiCore$Plane *  SuiCore$Plane$normalizeLocal(SuiCore$Plane *  self){
	float  inverseNormalLength = 1.0 / SuiCore$Vec3$length(&self->normal) ;
	SuiCore$Vec3$multiplyScalarLocal(&self->normal, inverseNormalLength) ;
	self->constant *= inverseNormalLength;
	return self; 
}

SuiCore$Plane *  SuiCore$Plane$negateLocal(SuiCore$Plane *  self){
	self->constant *= -1.0;
	SuiCore$Vec3$negateLocal(&self->normal) ;
	return self; 
}

float  SuiCore$Plane$distanceToPoint(SuiCore$Plane *  self, SuiCore$Vec3 point){
	return SuiCore$Vec3$dot(&self->normal, point)  + self->constant; 
}

float  SuiCore$Plane$distanceToSphere(SuiCore$Plane *  self, Sgl$Sphere sphere){
	return SuiCore$Plane$distanceToPoint(self, sphere.center)  - sphere.radius; 
}

SuiCore$Vec3 SuiCore$Plane$projectPoint(SuiCore$Plane *  self, SuiCore$Vec3 point){
	SuiCore$Vec3 target = point;
	SuiCore$Vec3$addScaledVectorLocal(&target, self->normal, -SuiCore$Plane$distanceToPoint(self, point) ) ;
	return target; 
}

SuiCore$Vec3 SuiCore$Plane$coplanarPoint(SuiCore$Plane *  self){
	SuiCore$Vec3 target = self->normal;
	SuiCore$Vec3$multiplyScalarLocal(&target, -self->constant) ;
	return target; 
}

SuiCore$Plane *  SuiCore$Plane$translate(SuiCore$Plane *  self, SuiCore$Vec3 offset){
	self->constant -= SuiCore$Vec3$dot(&offset, self->normal) ;
	return self; 
}

bool  SuiCore$Plane$equals(SuiCore$Plane *  self, SuiCore$Plane plane){
	return SuiCore$Vec3$equals(&plane.normal, self->normal)  && (Orc$eqFloat(plane.constant, self->constant) ); 
}

SuiCore$Plane SuiCore$Plane$clone(SuiCore$Plane *  self){
	return *self; 
}



