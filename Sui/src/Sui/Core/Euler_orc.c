
#include "Euler_orc.h" 

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "./Mat3_orc.h"
#include "./Vec3_orc.h"
#include "./Quaternion_orc.h"
#include "./Spherical_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Euler_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Euler", sizeof( SuiCore$Euler ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "x", OrcMetaType_float, offsetof(SuiCore$Euler, x), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "y", OrcMetaType_float, offsetof(SuiCore$Euler, y), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "z", OrcMetaType_float, offsetof(SuiCore$Euler, z), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "order", OrcMetaType_char, offsetof(SuiCore$Euler, order), 0, 0, 1, 1);//char
    }
	return meta;
}
const char *  SuiCore$Euler_XYZ = "XYZ";
const char *  SuiCore$Euler_YXZ = "YXZ";
const char *  SuiCore$Euler_ZXY = "ZXY";
const char *  SuiCore$Euler_ZYX = "ZYX";
const char *  SuiCore$Euler_YZX = "YZX";
const char *  SuiCore$Euler_XZY = "XZY";
const char *  SuiCore$Euler_Default = "XYZ";
bool  SuiCore$Euler$isXYZ(SuiCore$Euler *  self){
	return strcmp(self->order, "XYZ")  == 0; 
}

bool  SuiCore$Euler$isYXZ(SuiCore$Euler *  self){
	return strcmp(self->order, "YXZ")  == 0; 
}

bool  SuiCore$Euler$isZXY(SuiCore$Euler *  self){
	return strcmp(self->order, "ZXY")  == 0; 
}

bool  SuiCore$Euler$isZYX(SuiCore$Euler *  self){
	return strcmp(self->order, "ZYX")  == 0; 
}

bool  SuiCore$Euler$isYZX(SuiCore$Euler *  self){
	return strcmp(self->order, "YZX")  == 0; 
}

bool  SuiCore$Euler$isXZY(SuiCore$Euler *  self){
	return strcmp(self->order, "XZY")  == 0; 
}

SuiCore$Euler *  SuiCore$Euler$set(SuiCore$Euler *  self, float  x, float  y, float  z, const char *  order){
	self->x = x;
	self->y = y;
	self->z = z;
	self->order = order == NULL ? SuiCore$Euler_Default : order;
	return self; 
}

SuiCore$Euler SuiCore$Euler$clone(SuiCore$Euler *  self){
	return *self; 
}

SuiCore$Euler *  SuiCore$Euler$copy(SuiCore$Euler *  self, SuiCore$Euler euler){
	self->x = euler.x;
	self->y = euler.y;
	self->z = euler.z;
	self->order = euler.order;
	return self; 
}

SuiCore$Euler *  SuiCore$Euler$setFromRotationMatrix(SuiCore$Euler *  self, Sgl$Mat m, const char *  order){
	if (order == NULL) {
		order = SuiCore$Euler_Default;
	}
	float *  te = m.data;
	float  m11 = te[0];
	float  m12 = te[4];
	float  m13 = te[8];
	float  m21 = te[1];
	float  m22 = te[5];
	float  m23 = te[9];
	float  m31 = te[2];
	float  m32 = te[6];
	float  m33 = te[10];
	if (strcmp(order, "XYZ") ) {
		self->y = asin(Orc$clampFloat(m13, -1, 1) ) ;
		if (Orc$absFloat(m13)  < 0.9999999) {
			self->x = atan2(-m23, m33) ;
			self->z = atan2(-m12, m11) ;
		}
		else {
			self->x = atan2(m32, m22) ;
			self->z = 0;
		}
	}
	else if (strcmp(order, "YXZ") ) {
		self->x = asin(-Orc$clampFloat(m23, -1, 1) ) ;
		if (Orc$absFloat(m23)  < 0.9999999) {
			self->y = atan2(m13, m33) ;
			self->z = atan2(m21, m22) ;
		}
		else {
			self->y = atan2(-m31, m11) ;
			self->z = 0;
		}
	}
	else if (strcmp(order, "ZXY") ) {
		self->x = asin(Orc$clampFloat(m32, -1, 1) ) ;
		if (Orc$absFloat(m32)  < 0.9999999) {
			self->y = atan2(-m31, m33) ;
			self->z = atan2(-m12, m22) ;
		}
		else {
			self->y = 0;
			self->z = atan2(m21, m11) ;
		}
	}
	else if (strcmp(order, "ZYX") ) {
		self->y = asin(-Orc$clampFloat(m31, -1, 1) ) ;
		if (Orc$absFloat(m31)  < 0.9999999) {
			self->x = atan2(m32, m33) ;
			self->z = atan2(m21, m11) ;
		}
		else {
			self->x = 0;
			self->z = atan2(-m12, m22) ;
		}
	}
	else if (strcmp(order, "YZX") ) {
		self->z = asin(Orc$clampFloat(m21, -1, 1) ) ;
		if (Orc$absFloat(m21)  < 0.9999999) {
			self->x = atan2(-m23, m22) ;
			self->y = atan2(-m31, m11) ;
		}
		else {
			self->x = 0;
			self->y = atan2(m13, m33) ;
		}
	}
	else if (strcmp(order, "XZY") ) {
		self->z = asin(-Orc$clampFloat(m12, -1, 1) ) ;
		if (Orc$absFloat(m12)  < 0.9999999) {
			self->x = atan2(m32, m22) ;
			self->y = atan2(m13, m11) ;
		}
		else {
			self->x = atan2(-m23, m33) ;
			self->y = 0;
		}
	}
	else {
		printf(" setFromRotationMatrix() encountered an unknown order::%s ", order) ;
	}
	self->order = order;
	return self; 
}

SuiCore$Euler *  SuiCore$Euler$setFromQuaternion(SuiCore$Euler *  self, SuiCore$Quaternion q, const char *  order){
	Sgl$Mat _matrix;
	Sgl$Mat$makeRotationFromQuaternion(&_matrix, q) ;
	return SuiCore$Euler$setFromRotationMatrix(self, _matrix, order) ; 
}

SuiCore$Euler *  SuiCore$Euler$setFromVector3(SuiCore$Euler *  self, SuiCore$Vec3 v, const char *  order){
	return SuiCore$Euler$set(self, v.x, v.y, v.z, order) ; 
}

bool  SuiCore$Euler$equals(SuiCore$Euler *  self, SuiCore$Euler euler){
	return Orc$eqFloat(euler.x, self->x)  && Orc$eqFloat(euler.y, self->y)  && Orc$eqFloat(euler.z, self->z)  && (strcmp(euler.order, self->order)  == 0); 
}

SuiCore$Euler *  SuiCore$Euler$fromArray(SuiCore$Euler *  self, float *  array){
	self->x = array[0];
	self->y = array[1];
	self->z = array[2];
	return self; 
}

float *  SuiCore$Euler$toArray(SuiCore$Euler *  self, float *  array, int  offset){
	array[offset] = self->x;
	array[offset + 1] = self->y;
	array[offset + 2] = self->z;
	return array; 
}



