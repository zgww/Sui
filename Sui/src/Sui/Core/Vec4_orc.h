
typedef struct tagSuiCore$Vec4 SuiCore$Vec4;


#ifndef define_struct___SuiCore__Vec4_orc_h__
#define define_struct___SuiCore__Vec4_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Vec4_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Vec4_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Vec4 {
	float  x ;
	float  y ;
	float  z ;
	float  w ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Vec4_orc_h__
#define __SuiCore__Vec4_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "./Mat3_orc.h"
#include "./Euler_orc.h"
#include "./Color_orc.h"
#include "./Spherical_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Vec4_getOrInitMetaStruct();

float  SuiCore$Vec4$width(SuiCore$Vec4 *  self);
float  SuiCore$Vec4$height(SuiCore$Vec4 *  self);
SuiCore$Vec4 *  SuiCore$Vec4$set(SuiCore$Vec4 *  self, float  x, float  y, float  z, float  w);
SuiCore$Vec4 *  SuiCore$Vec4$setScalar(SuiCore$Vec4 *  self, float  scalar);
SuiCore$Vec4 *  SuiCore$Vec4$setX(SuiCore$Vec4 *  self, float  x);
SuiCore$Vec4 *  SuiCore$Vec4$setY(SuiCore$Vec4 *  self, float  y);
SuiCore$Vec4 *  SuiCore$Vec4$setZ(SuiCore$Vec4 *  self, float  z);
SuiCore$Vec4 *  SuiCore$Vec4$setW(SuiCore$Vec4 *  self, float  w);
SuiCore$Vec4 *  SuiCore$Vec4$setComponent(SuiCore$Vec4 *  self, int  index, float  value);
float  SuiCore$Vec4$getComponent(SuiCore$Vec4 *  self, int  index);
SuiCore$Vec4 SuiCore$Vec4$clone(SuiCore$Vec4 *  self);
SuiCore$Vec4 *  SuiCore$Vec4$copy(SuiCore$Vec4 *  self, SuiCore$Vec4 v);
SuiCore$Vec4 *  SuiCore$Vec4$addLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v);
SuiCore$Vec4 *  SuiCore$Vec4$addScalarLocal(SuiCore$Vec4 *  self, float  s);
SuiCore$Vec4 *  SuiCore$Vec4$addVectorsLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 a, SuiCore$Vec4 b);
SuiCore$Vec4 *  SuiCore$Vec4$addScaledVectorLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v, float  s);
SuiCore$Vec4 *  SuiCore$Vec4$subLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v);
SuiCore$Vec4 *  SuiCore$Vec4$subScalarLocal(SuiCore$Vec4 *  self, float  s);
SuiCore$Vec4 *  SuiCore$Vec4$subVectorsLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 a, SuiCore$Vec4 b);
SuiCore$Vec4 *  SuiCore$Vec4$multiplyLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v);
SuiCore$Vec4 *  SuiCore$Vec4$multiplyScalarLocal(SuiCore$Vec4 *  self, float  scalar);
SuiCore$Vec4 *  SuiCore$Vec4$applyMatrix4Local(SuiCore$Vec4 *  self, Sgl$Mat m);
SuiCore$Vec4 *  SuiCore$Vec4$divideScalarLocal(SuiCore$Vec4 *  self, float  scalar);
SuiCore$Vec4 *  SuiCore$Vec4$setAxisAngleFromRotationMatrixLocal(SuiCore$Vec4 *  self, Sgl$Mat m);
SuiCore$Vec4 *  SuiCore$Vec4$minLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v);
SuiCore$Vec4 *  SuiCore$Vec4$maxLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v);
SuiCore$Vec4 *  SuiCore$Vec4$clampLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 min, SuiCore$Vec4 max);
SuiCore$Vec4 *  SuiCore$Vec4$clampScalarLocal(SuiCore$Vec4 *  self, float  minVal, float  maxVal);
SuiCore$Vec4 *  SuiCore$Vec4$clampLengthLocal(SuiCore$Vec4 *  self, float  min, float  max);
SuiCore$Vec4 *  SuiCore$Vec4$floorLocal(SuiCore$Vec4 *  self);
SuiCore$Vec4 *  SuiCore$Vec4$ceilLocal(SuiCore$Vec4 *  self);
SuiCore$Vec4 *  SuiCore$Vec4$roundLocal(SuiCore$Vec4 *  self);
SuiCore$Vec4 *  SuiCore$Vec4$roundToZeroLocal(SuiCore$Vec4 *  self);
SuiCore$Vec4 *  SuiCore$Vec4$negateLocal(SuiCore$Vec4 *  self);
float  SuiCore$Vec4$dot(SuiCore$Vec4 *  self, SuiCore$Vec4 v);
float  SuiCore$Vec4$lengthSq(SuiCore$Vec4 *  self);
float  SuiCore$Vec4$length(SuiCore$Vec4 *  self);
float  SuiCore$Vec4$manhattanLength(SuiCore$Vec4 *  self);
SuiCore$Vec4 SuiCore$Vec4$normal(SuiCore$Vec4 *  self, float  f);
SuiCore$Vec4 *  SuiCore$Vec4$normalizeLocal(SuiCore$Vec4 *  self);
SuiCore$Vec4 *  SuiCore$Vec4$setLengthLocal(SuiCore$Vec4 *  self, float  length);
SuiCore$Vec4 *  SuiCore$Vec4$lerpLocal(SuiCore$Vec4 *  self, SuiCore$Vec4 v, float  alpha);
SuiCore$Vec4 *  SuiCore$Vec4$lerpVectors(SuiCore$Vec4 *  self, SuiCore$Vec4 v1, SuiCore$Vec4 v2, float  alpha);
SuiCore$Vec4 *  SuiCore$Vec4$fromArray(SuiCore$Vec4 *  self, float *  array, int  offset);
float *  SuiCore$Vec4$toArray(SuiCore$Vec4 *  self, float *  array, int  offset);
SuiCore$Vec4 *  SuiCore$Vec4$randomLocal(SuiCore$Vec4 *  self);
SuiCore$Vec4 SuiCore$Vec4$add4f(SuiCore$Vec4 *  self, float  x, float  y, float  z, float  w);
SuiCore$Vec4 SuiCore$Vec4$add(SuiCore$Vec4 *  self, SuiCore$Vec4 b);
SuiCore$Vec4 SuiCore$Vec4$sub(SuiCore$Vec4 *  self, SuiCore$Vec4 b);
float  SuiCore$Vec4$distanceToSquared(SuiCore$Vec4 *  self, SuiCore$Vec4 b);
float  SuiCore$Vec4$distanceTo(SuiCore$Vec4 *  self, SuiCore$Vec4 b);
bool  SuiCore$Vec4$equals(SuiCore$Vec4 *  self, SuiCore$Vec4 b);
SuiCore$Vec4 SuiCore$mkVec4(float  x, float  y, float  z, float  w);
void  SuiCore$testVec4();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
