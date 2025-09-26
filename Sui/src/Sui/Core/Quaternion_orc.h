
typedef struct tagSuiCore$Quaternion SuiCore$Quaternion;


#ifndef define_struct___SuiCore__Quaternion_orc_h__
#define define_struct___SuiCore__Quaternion_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Quaternion_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Quaternion_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Quaternion {
	float  x ;
	float  y ;
	float  z ;
	float  w ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Quaternion_orc_h__
#define __SuiCore__Quaternion_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../../Sgl/Sphere_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "./Mat3_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "./Plane_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "./Vec3_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "./Euler_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "./Spherical_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Quaternion_getOrInitMetaStruct();

SuiCore$Quaternion *  SuiCore$Quaternion$set(SuiCore$Quaternion *  self, float  x, float  y, float  z, float  w);
SuiCore$Quaternion SuiCore$Quaternion$clone(SuiCore$Quaternion *  self);
SuiCore$Quaternion *  SuiCore$Quaternion$copy(SuiCore$Quaternion *  self, SuiCore$Quaternion quaternion);
SuiCore$Quaternion *  SuiCore$Quaternion$setFromEuler(SuiCore$Quaternion *  self, SuiCore$Euler euler);
SuiCore$Quaternion *  SuiCore$Quaternion$setFromAxisAngle(SuiCore$Quaternion *  self, SuiCore$Vec3 axis, float  angle);
SuiCore$Vec3 SuiCore$Quaternion$toVec3AsEuler(SuiCore$Quaternion *  self, const char *  order);
SuiCore$Quaternion *  SuiCore$Quaternion$setFromRotationMatrix(SuiCore$Quaternion *  self, Sgl$Mat m);
SuiCore$Quaternion *  SuiCore$Quaternion$setFromUnitVectors(SuiCore$Quaternion *  self, SuiCore$Vec3 vFrom, SuiCore$Vec3 vTo);
float  SuiCore$Quaternion$angleTo(SuiCore$Quaternion *  self, SuiCore$Quaternion q);
SuiCore$Quaternion *  SuiCore$Quaternion$rotateTowardsLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion q, float  step);
SuiCore$Quaternion *  SuiCore$Quaternion$identity(SuiCore$Quaternion *  self);
SuiCore$Quaternion *  SuiCore$Quaternion$invertLocal(SuiCore$Quaternion *  self);
SuiCore$Quaternion *  SuiCore$Quaternion$conjugateLocal(SuiCore$Quaternion *  self);
float  SuiCore$Quaternion$dot(SuiCore$Quaternion *  self, SuiCore$Quaternion v);
float  SuiCore$Quaternion$lengthSq(SuiCore$Quaternion *  self);
float  SuiCore$Quaternion$length(SuiCore$Quaternion *  self);
SuiCore$Quaternion *  SuiCore$Quaternion$normalizeLocal(SuiCore$Quaternion *  self);
SuiCore$Quaternion *  SuiCore$Quaternion$multiplyLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion q);
SuiCore$Quaternion *  SuiCore$Quaternion$premultiplyLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion q);
SuiCore$Quaternion *  SuiCore$Quaternion$multiplyQuaternionsLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion a, SuiCore$Quaternion b);
SuiCore$Quaternion *  SuiCore$Quaternion$slerpLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion qb, float  t);
SuiCore$Quaternion *  SuiCore$Quaternion$slerpQuaternionsLocal(SuiCore$Quaternion *  self, SuiCore$Quaternion qa, SuiCore$Quaternion qb, float  t);
SuiCore$Quaternion *  SuiCore$Quaternion$randomLocal(SuiCore$Quaternion *  self);
bool  SuiCore$Quaternion$equals(SuiCore$Quaternion *  self, SuiCore$Quaternion quaternion);
SuiCore$Quaternion *  SuiCore$Quaternion$fromArray(SuiCore$Quaternion *  self, float *  array, int  offset);
float *  SuiCore$Quaternion$toArray(SuiCore$Quaternion *  self, float *  array, int  offset);
void  SuiCore$Quaternion_slerpFlat(float *  dst, int  dstOffset, float *  src0, int  srcOffset0, float *  src1, int  srcOffset1, float  t);
float *  SuiCore$Quaternion_multiplyQuaternionsFlat(float *  dst, int  dstOffset, float *  src0, int  srcOffset0, float *  src1, int  srcOffset1);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
