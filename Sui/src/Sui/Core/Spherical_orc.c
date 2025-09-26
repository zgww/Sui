
#include "Spherical_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "./Mat3_orc.h"
#include "./Vec3_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Spherical_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Spherical", sizeof( SuiCore$Spherical ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "radius", OrcMetaType_float, offsetof(SuiCore$Spherical, radius), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "phi", OrcMetaType_float, offsetof(SuiCore$Spherical, phi), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "theta", OrcMetaType_float, offsetof(SuiCore$Spherical, theta), 0, 0, 0, 0);//float
    }
	return meta;
}
SuiCore$Spherical *  SuiCore$Spherical$set(SuiCore$Spherical *  self, float  radius, float  phi, float  theta){
	self->radius = radius;
	self->phi = phi;
	self->theta = theta;
	return self; 
}

SuiCore$Spherical *  SuiCore$Spherical$copy(SuiCore$Spherical *  self, SuiCore$Spherical other){
	self->radius = other.radius;
	self->phi = other.phi;
	self->theta = other.theta;
	return self; 
}

SuiCore$Spherical *  SuiCore$Spherical$makeSafe(SuiCore$Spherical *  self){
	float  EPS = 0.000001;
	self->phi = Orc$maxFloat(EPS, Orc$minFloat(Orc$PI - EPS, self->phi) ) ;
	return self; 
}

SuiCore$Spherical *  SuiCore$Spherical$setFromVector3(SuiCore$Spherical *  self, SuiCore$Vec3 v){
	return SuiCore$Spherical$setFromCartesianCoords(self, v.x, v.y, v.z) ; 
}

SuiCore$Spherical *  SuiCore$Spherical$setFromCartesianCoords(SuiCore$Spherical *  self, float  x, float  y, float  z){
	self->radius = sqrt(x * x + y * y + z * z) ;
	if (Orc$eqFloat(self->radius, 0) ) {
		self->theta = 0;
		self->phi = 0;
	}
	else {
		self->theta = atan2(x, z) ;
		self->phi = acos(Orc$clampFloat(y / self->radius, -1, 1) ) ;
	}
	return self; 
}

SuiCore$Spherical SuiCore$Spherical$clone(SuiCore$Spherical *  self){
	return *self; 
}



