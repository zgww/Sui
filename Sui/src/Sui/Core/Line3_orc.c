
#include "Line3_orc.h" 

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "./Mat3_orc.h"
#include "./Vec3_orc.h"
#include "./Plane_orc.h"
#include "./Spherical_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Line3_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Line3", sizeof( SuiCore$Line3 ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "start", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiCore$Line3, start), false, false, 0);
		orc_metaField_struct(&pNext, "end", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiCore$Line3, end), false, false, 0);
    }
	return meta;
}
SuiCore$Line3 *  SuiCore$Line3$set(SuiCore$Line3 *  self, SuiCore$Vec3 start, SuiCore$Vec3 end){
	SuiCore$Vec3$copy(&self->start, start) ;
	SuiCore$Vec3$copy(&self->end, end) ;
	return self; 
}

SuiCore$Line3 *  SuiCore$Line3$copy(SuiCore$Line3 *  self, SuiCore$Line3 line){
	SuiCore$Vec3$copy(&self->start, line.start) ;
	SuiCore$Vec3$copy(&self->end, line.end) ;
	return self; 
}

SuiCore$Vec3 SuiCore$Line3$getCenter(SuiCore$Line3 *  self){
	SuiCore$Vec3 target;
	SuiCore$Vec3$multiplyScalarLocal(SuiCore$Vec3$addVectorsLocal(&target, self->start, self->end) , 0.5) ;
	return target; 
}

SuiCore$Vec3 SuiCore$Line3$delta(SuiCore$Line3 *  self){
	SuiCore$Vec3 target;
	SuiCore$Vec3$subVectorsLocal(&target, self->end, self->start) ;
	return target; 
}

float  SuiCore$Line3$distanceSq(SuiCore$Line3 *  self){
	return SuiCore$Vec3$distanceToSquared(&self->start, self->end) ; 
}

float  SuiCore$Line3$distance(SuiCore$Line3 *  self){
	return SuiCore$Vec3$distanceTo(&self->start, self->end) ; 
}

SuiCore$Vec3 SuiCore$Line3$at(SuiCore$Line3 *  self, float  t){
	SuiCore$Vec3 tmpStructThis1;
	SuiCore$Vec3 target = SuiCore$Vec3$add(SuiCore$Vec3$multiplyScalarLocal((tmpStructThis1 = SuiCore$Line3$delta(self) ,&tmpStructThis1), t) , self->start) ;
	return target; 
}

float  SuiCore$Line3$closestPointToPointParameter(SuiCore$Line3 *  self, SuiCore$Vec3 point, bool  clampToLine){
	SuiCore$Vec3 _startP;
	SuiCore$Vec3 _startEnd;
	SuiCore$Vec3$subVectorsLocal(&_startP, point, self->start) ;
	SuiCore$Vec3$subVectorsLocal(&_startEnd, self->end, self->start) ;
	float  startEnd2 = SuiCore$Vec3$dot(&_startEnd, _startEnd) ;
	float  startEnd_startP = SuiCore$Vec3$dot(&_startEnd, _startP) ;
	float  t = startEnd_startP / startEnd2;
	if (clampToLine) {
		t = Orc$clampFloat(t, 0, 1) ;
	}
	return t; 
}

SuiCore$Vec3 SuiCore$Line3$closestPointToPoint(SuiCore$Line3 *  self, SuiCore$Vec3 point, bool  clampToLine){
	float  t = SuiCore$Line3$closestPointToPointParameter(self, point, clampToLine) ;
	SuiCore$Vec3 tmpStructThis1;
	SuiCore$Vec3 result = SuiCore$Vec3$add(SuiCore$Vec3$multiplyScalarLocal((tmpStructThis1 = SuiCore$Line3$delta(self) ,&tmpStructThis1), t) , self->start) ;
	return result; 
}

SuiCore$Line3 *  SuiCore$Line3$applyMatrix4Local(SuiCore$Line3 *  self, Sgl$Mat matrix){
	SuiCore$Vec3$applyMatrix4Local(&self->start, matrix) ;
	SuiCore$Vec3$applyMatrix4Local(&self->end, matrix) ;
	return self; 
}

bool  SuiCore$Line3$equals(SuiCore$Line3 *  self, SuiCore$Line3 line){
	return SuiCore$Vec3$equals(&line.start, self->start)  && SuiCore$Vec3$equals(&line.end, self->end) ; 
}

SuiCore$Line3 SuiCore$Line3$clone(SuiCore$Line3 *  self){
	return *self; 
}



