
typedef struct tagSuiCore$Quat SuiCore$Quat;


#ifndef define_struct___SuiCore__Quat_orc_h__
#define define_struct___SuiCore__Quat_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Quat_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include "./linmath.h"
#include <stdio.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Quat_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Quat {
	float  x ;
	float  y ;
	float  z ;
	float  w ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Quat_orc_h__
#define __SuiCore__Quat_orc_h__

//include  importHeadCode
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "./Vec3_orc.h"
#include "../../Sgl/Mat_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Quat_getOrInitMetaStruct();

SuiCore$Vec3 SuiCore$Quat$toEulerXYZ(SuiCore$Quat *  self);
Sgl$Mat SuiCore$Quat$toRotationMat(SuiCore$Quat *  self);
Orc$String*  SuiCore$Quat$toString(Orc$String **  __outRef__, SuiCore$Quat *  self);
void  SuiCore$Quat$identity(SuiCore$Quat *  self);
SuiCore$Quat SuiCore$Quat$mul(SuiCore$Quat *  self, SuiCore$Quat q);
SuiCore$Quat SuiCore$Quat$conj(SuiCore$Quat *  self);
void  SuiCore$Quat$setRotate(SuiCore$Quat *  self, float  angle, SuiCore$Vec3 axis);
SuiCore$Vec3 SuiCore$Quat$mulVec3(SuiCore$Quat *  self, SuiCore$Vec3 v);
SuiCore$Quat SuiCore$Quat$lerp(SuiCore$Quat *  self, SuiCore$Quat b, float  ratio);
SuiCore$Quat SuiCore$Quat$clone(SuiCore$Quat *  self);
float  SuiCore$Quat$length(SuiCore$Quat *  self);
void  SuiCore$Quat$normalizeSelf(SuiCore$Quat *  self);
SuiCore$Quat SuiCore$Quat$slerp(SuiCore$Quat *  self, SuiCore$Quat qb, float  t);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
