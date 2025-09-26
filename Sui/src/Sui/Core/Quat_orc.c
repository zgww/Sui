
#include "Quat_orc.h" 

#include <math.h>
#include "./linmath.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "./Vec3_orc.h"
#include "../../Sgl/Mat_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Quat_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Quat", sizeof( SuiCore$Quat ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "x", OrcMetaType_float, offsetof(SuiCore$Quat, x), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "y", OrcMetaType_float, offsetof(SuiCore$Quat, y), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "z", OrcMetaType_float, offsetof(SuiCore$Quat, z), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "w", OrcMetaType_float, offsetof(SuiCore$Quat, w), 0, 0, 0, 0);//float
    }
	return meta;
}
SuiCore$Vec3 SuiCore$Quat$toEulerXYZ(SuiCore$Quat *  self){
	Sgl$Mat m = SuiCore$Quat$toRotationMat(self) ;
	SuiCore$Vec3 r = Sgl$Mat$rotationMatrixToEulerXYZ(&m) ;
	return r; 
}

Sgl$Mat SuiCore$Quat$toRotationMat(SuiCore$Quat *  self){
	Sgl$Mat m;
	mat4x4_from_quat(m.data, self) ;
	return m; 
}

Orc$String*  SuiCore$Quat$toString(Orc$String **  __outRef__, SuiCore$Quat *  self){
	char  tmp[256];
	sprintf(tmp, "Quat(%f,%f,%f,%f)", self->x, self->y, self->z, self->w) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, tmp) ) ; 
}

void  SuiCore$Quat$identity(SuiCore$Quat *  self){
	quat_identity((float * )self) ;
}

SuiCore$Quat SuiCore$Quat$mul(SuiCore$Quat *  self, SuiCore$Quat q){
	SuiCore$Quat r;
	quat_mul((float * )&r, (float * )self, (float * )&q) ;
	return r; 
}

SuiCore$Quat SuiCore$Quat$conj(SuiCore$Quat *  self){
	SuiCore$Quat r;
	quat_conj((float * )&r, (float * )self) ;
	return r; 
}

void  SuiCore$Quat$setRotate(SuiCore$Quat *  self, float  angle, SuiCore$Vec3 axis){
	quat_rotate((float * )self, angle, (float * )&axis) ;
}

SuiCore$Vec3 SuiCore$Quat$mulVec3(SuiCore$Quat *  self, SuiCore$Vec3 v){
	SuiCore$Vec3 r;
	quat_mul_vec3((float * )&r, (float * )self, (float * )&v) ;
	return r; 
}

SuiCore$Quat SuiCore$Quat$lerp(SuiCore$Quat *  self, SuiCore$Quat b, float  ratio){
	SuiCore$Quat r;
	r.x = Orc$lerpFloat(self->x, b.x, ratio) ;
	r.y = Orc$lerpFloat(self->y, b.y, ratio) ;
	r.z = Orc$lerpFloat(self->z, b.z, ratio) ;
	r.w = Orc$lerpFloat(self->w, b.w, ratio) ;
	return r; 
}

SuiCore$Quat SuiCore$Quat$clone(SuiCore$Quat *  self){
	SuiCore$Quat r;
	r.x = self->x;
	r.y = self->y;
	r.z = self->z;
	r.w = self->w;
	return r; 
}

float  SuiCore$Quat$length(SuiCore$Quat *  self){
	return sqrt(self->x * self->x + self->y * self->y + self->z * self->z + self->w * self->w) ; 
}

void  SuiCore$Quat$normalizeSelf(SuiCore$Quat *  self){
	float  l = SuiCore$Quat$length(self) ;
	if (l == 0) {
		self->x = 0;
		self->y = 0;
		self->z = 0;
		self->w = 1;
	}
	else {
		l = 1 / l;
		self->x = self->x * l;
		self->y = self->y * l;
		self->z = self->z * l;
		self->w = self->w * l;
	}
}

SuiCore$Quat SuiCore$Quat$slerp(SuiCore$Quat *  self, SuiCore$Quat qb, float  t){
	SuiCore$Quat r = SuiCore$Quat$clone(self) ;
	if (t == 0) {
		return r; 
	}
	if (t == 1) {
		return SuiCore$Quat$clone(&qb) ; 
	}
	float  x = r.x;
	float  y = r.y;
	float  z = r.z;
	float  w = r.w;
	float  cosHalfTheta = w * qb.w + x * qb.x + y * qb.y + z * qb.z;
	if (cosHalfTheta < 0) {
		r.w = -qb.w;
		r.x = -qb.x;
		r.y = -qb.y;
		r.z = -qb.z;
		cosHalfTheta = -cosHalfTheta;
	}
	else {
		r = qb;
	}
	if (cosHalfTheta >= 1.0) {
		r.w = w;
		r.x = x;
		r.y = y;
		r.z = z;
		return r; 
	}
	float  sqrSinHalfTheta = 1.0 - cosHalfTheta * cosHalfTheta;
	if (sqrSinHalfTheta <= Orc$EPSILON) {
		float  s = 1 - t;
		r.w = s * w + t * r.w;
		r.x = s * x + t * r.x;
		r.y = s * y + t * r.y;
		r.z = s * z + t * r.z;
		SuiCore$Quat$normalizeSelf(&r) ;
		return r; 
	}
	float  sinHalfTheta = sqrt(sqrSinHalfTheta) ;
	float  halfTheta = atan2(sinHalfTheta, cosHalfTheta) ;
	float  ratioA = sin((1 - t) * halfTheta)  / sinHalfTheta;
	float  ratioB = sin(t * halfTheta)  / sinHalfTheta;
	r.w = (w * ratioA + r.w * ratioB);
	r.x = (x * ratioA + r.x * ratioB);
	r.y = (y * ratioA + r.y * ratioB);
	r.z = (z * ratioA + r.z * ratioB);
	return r; 
}



