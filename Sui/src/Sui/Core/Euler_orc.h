
typedef struct tagSuiCore$Euler SuiCore$Euler;


#ifndef define_struct___SuiCore__Euler_orc_h__
#define define_struct___SuiCore__Euler_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Euler_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Euler_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Euler {
	float  x ;
	float  y ;
	float  z ;
	const char *  order ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Euler_orc_h__
#define __SuiCore__Euler_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "./Mat3_orc.h"
#include "./Vec3_orc.h"
#include "./Quaternion_orc.h"
#include "./Spherical_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Euler_getOrInitMetaStruct();

extern const char *  SuiCore$Euler_XYZ;
extern const char *  SuiCore$Euler_YXZ;
extern const char *  SuiCore$Euler_ZXY;
extern const char *  SuiCore$Euler_ZYX;
extern const char *  SuiCore$Euler_YZX;
extern const char *  SuiCore$Euler_XZY;
extern const char *  SuiCore$Euler_Default;
bool  SuiCore$Euler$isXYZ(SuiCore$Euler *  self);
bool  SuiCore$Euler$isYXZ(SuiCore$Euler *  self);
bool  SuiCore$Euler$isZXY(SuiCore$Euler *  self);
bool  SuiCore$Euler$isZYX(SuiCore$Euler *  self);
bool  SuiCore$Euler$isYZX(SuiCore$Euler *  self);
bool  SuiCore$Euler$isXZY(SuiCore$Euler *  self);
SuiCore$Euler *  SuiCore$Euler$set(SuiCore$Euler *  self, float  x, float  y, float  z, const char *  order);
SuiCore$Euler SuiCore$Euler$clone(SuiCore$Euler *  self);
SuiCore$Euler *  SuiCore$Euler$copy(SuiCore$Euler *  self, SuiCore$Euler euler);
SuiCore$Euler *  SuiCore$Euler$setFromRotationMatrix(SuiCore$Euler *  self, Sgl$Mat m, const char *  order);
SuiCore$Euler *  SuiCore$Euler$setFromQuaternion(SuiCore$Euler *  self, SuiCore$Quaternion q, const char *  order);
SuiCore$Euler *  SuiCore$Euler$setFromVector3(SuiCore$Euler *  self, SuiCore$Vec3 v, const char *  order);
bool  SuiCore$Euler$equals(SuiCore$Euler *  self, SuiCore$Euler euler);
SuiCore$Euler *  SuiCore$Euler$fromArray(SuiCore$Euler *  self, float *  array);
float *  SuiCore$Euler$toArray(SuiCore$Euler *  self, float *  array, int  offset);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
