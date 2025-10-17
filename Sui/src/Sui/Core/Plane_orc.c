
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

void  SuiCore$Plane$setByMatrixAndPlaneName(SuiCore$Plane *  self, Sgl$Mat worldTransform, const char *  planeName){
	if (planeName != NULL) {
		SuiCore$Vec3 tmpStructThis1;
		SuiCore$Vec3 a = SuiCore$Vec3$applyMatrix4((tmpStructThis1 = SuiCore$mkVec3(0, 0, 0) ,&tmpStructThis1), worldTransform) ;
		if (Orc$strEq(planeName, "XZ") ) {
			SuiCore$Vec3 tmpStructThis2;
			SuiCore$Vec3 b = SuiCore$Vec3$applyMatrix4((tmpStructThis2 = SuiCore$mkVec3(0, 0, 1) ,&tmpStructThis2), worldTransform) ;
			SuiCore$Vec3 tmpStructThis3;
			SuiCore$Vec3 c = SuiCore$Vec3$applyMatrix4((tmpStructThis3 = SuiCore$mkVec3(1, 0, 0) ,&tmpStructThis3), worldTransform) ;
			SuiCore$Plane$setFromCoplanarPoints(self, a, b, c) ;
		}
		else if (Orc$strEq(planeName, "XY") ) {
			SuiCore$Vec3 tmpStructThis4;
			SuiCore$Vec3 b = SuiCore$Vec3$applyMatrix4((tmpStructThis4 = SuiCore$mkVec3(1, 0, 0) ,&tmpStructThis4), worldTransform) ;
			SuiCore$Vec3 tmpStructThis5;
			SuiCore$Vec3 c = SuiCore$Vec3$applyMatrix4((tmpStructThis5 = SuiCore$mkVec3(0, 1, 0) ,&tmpStructThis5), worldTransform) ;
			SuiCore$Plane$setFromCoplanarPoints(self, a, b, c) ;
		}
		else if (Orc$strEq(planeName, "YZ") ) {
			SuiCore$Vec3 tmpStructThis6;
			SuiCore$Vec3 b = SuiCore$Vec3$applyMatrix4((tmpStructThis6 = SuiCore$mkVec3(0, 1, 0) ,&tmpStructThis6), worldTransform) ;
			SuiCore$Vec3 tmpStructThis7;
			SuiCore$Vec3 c = SuiCore$Vec3$applyMatrix4((tmpStructThis7 = SuiCore$mkVec3(0, 0, 1) ,&tmpStructThis7), worldTransform) ;
			SuiCore$Plane$setFromCoplanarPoints(self, a, b, c) ;
		}
	}
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

SuiCore$Plane *  SuiCore$Plane$applyMatrix4Local(SuiCore$Plane *  self, Sgl$Mat matrix){
	SuiCore$Mat3 normalMatrix;
	SuiCore$Mat3$getNormalMatrixLocal(&normalMatrix, matrix) ;
	SuiCore$Vec3 tmpStructThis1;
	SuiCore$Vec3 referencePoint = SuiCore$Vec3$applyMatrix4((tmpStructThis1 = SuiCore$Plane$coplanarPoint(self) ,&tmpStructThis1), matrix) ;
	SuiCore$Vec3 tmpStructThis2;
	SuiCore$Vec3 normal = SuiCore$Vec3$normalize((tmpStructThis2 = SuiCore$Vec3$applyMatrix3(&self->normal, normalMatrix) ,&tmpStructThis2)) ;
	self->constant = -SuiCore$Vec3$dot(&referencePoint, normal) ;
	return self; 
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

void  SuiCore$testPlane(){
	{
		SuiCore$Plane plane;
		Sgl$Mat m;
		Sgl$Mat$identity(&m) ;
		SuiCore$Plane$setByMatrixAndPlaneName(&plane, m, "YZ") ;
		float  dis = SuiCore$Plane$distanceToPoint(&plane, SuiCore$mkVec3(1000, 100, 10) ) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("yz:%f, normal:%s, dis:%f\n", plane.constant, SuiCore$Vec3$toString(&tmpReturn_1, &plane.normal) ->str, dis) ;
		SuiCore$Plane$setByMatrixAndPlaneName(&plane, m, "XZ") ;
		dis = SuiCore$Plane$distanceToPoint(&plane, SuiCore$mkVec3(1000, 100, 10) ) ;
		printf("xz:%f, normal:%f,%f,%f dis:%f\n", plane.constant, plane.normal.x, plane.normal.y, plane.normal.z, dis) ;
		SuiCore$Plane$setByMatrixAndPlaneName(&plane, m, "XY") ;
		dis = SuiCore$Plane$distanceToPoint(&plane, SuiCore$mkVec3(1000, 100, 10) ) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		printf("xy:%f, normal:%s, dis:%f\n", plane.constant, SuiCore$Vec3$toString(&tmpReturn_2, &plane.normal) ->str, dis) ;
	}
}



