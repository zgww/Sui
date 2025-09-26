
typedef struct tagSuiCore$IntVec2 SuiCore$IntVec2;
typedef struct tagSuiCore$Vec2 SuiCore$Vec2;


#ifndef define_struct___SuiCore__Vec2_orc_h__
#define define_struct___SuiCore__Vec2_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Vec2_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Vec2_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$IntVec2 {
	int  x ;
	int  y ;
};


struct tagSuiCore$Vec2 {
	float  x ;
	float  y ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Vec2_orc_h__
#define __SuiCore__Vec2_orc_h__

//include  importHeadCode
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "./Mat3_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$IntVec2_getOrInitMetaStruct();



//结构体元数据获取即初始化
MetaStruct* SuiCore$Vec2_getOrInitMetaStruct();

Orc$String*  SuiCore$Vec2$toString(Orc$String **  __outRef__, SuiCore$Vec2 *  self);
float  SuiCore$Vec2$width(SuiCore$Vec2 *  self);
float  SuiCore$Vec2$height(SuiCore$Vec2 *  self);
SuiCore$Vec2 *  SuiCore$Vec2$set(SuiCore$Vec2 *  self, float  x, float  y);
SuiCore$Vec2 *  SuiCore$Vec2$setScalar(SuiCore$Vec2 *  self, float  scalar);
void  SuiCore$Vec2$setX(SuiCore$Vec2 *  self, float  x);
void  SuiCore$Vec2$setY(SuiCore$Vec2 *  self, float  y);
void  SuiCore$Vec2$setComponent(SuiCore$Vec2 *  self, int  index, float  value);
float  SuiCore$Vec2$getComponent(SuiCore$Vec2 *  self, int  index);
SuiCore$Vec2 SuiCore$Vec2$clone(SuiCore$Vec2 *  self);
SuiCore$Vec2 *  SuiCore$Vec2$copy(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
SuiCore$Vec2 *  SuiCore$Vec2$addLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
SuiCore$Vec2 *  SuiCore$Vec2$addScalarLocal(SuiCore$Vec2 *  self, float  s);
SuiCore$Vec2 *  SuiCore$Vec2$addVectorsLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 a, SuiCore$Vec2 b);
SuiCore$Vec2 *  SuiCore$Vec2$addScaledVectorLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v, float  s);
SuiCore$Vec2 *  SuiCore$Vec2$subLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
SuiCore$Vec2 *  SuiCore$Vec2$subScalarLocal(SuiCore$Vec2 *  self, float  s);
SuiCore$Vec2 *  SuiCore$Vec2$subVectorsLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 a, SuiCore$Vec2 b);
SuiCore$Vec2 *  SuiCore$Vec2$multiplyLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
SuiCore$Vec2 *  SuiCore$Vec2$multiplyScalarLocal(SuiCore$Vec2 *  self, float  scalar);
SuiCore$Vec2 *  SuiCore$Vec2$divideLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
SuiCore$Vec2 *  SuiCore$Vec2$divideScalarLocal(SuiCore$Vec2 *  self, float  scalar);
SuiCore$Vec2 *  SuiCore$Vec2$applyMatrix3Local(SuiCore$Vec2 *  self, SuiCore$Mat3 m);
SuiCore$Vec2 *  SuiCore$Vec2$minLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
SuiCore$Vec2 *  SuiCore$Vec2$maxLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
SuiCore$Vec2 *  SuiCore$Vec2$floorLocal(SuiCore$Vec2 *  self);
SuiCore$Vec2 *  SuiCore$Vec2$ceilLocal(SuiCore$Vec2 *  self);
SuiCore$Vec2 *  SuiCore$Vec2$roundLocal(SuiCore$Vec2 *  self);
SuiCore$Vec2 *  SuiCore$Vec2$roundToZeroLocal(SuiCore$Vec2 *  self);
SuiCore$Vec2 *  SuiCore$Vec2$negateLocal(SuiCore$Vec2 *  self);
float  SuiCore$Vec2$dot(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
float  SuiCore$Vec2$cross(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
float  SuiCore$Vec2$lengthSq(SuiCore$Vec2 *  self);
float  SuiCore$Vec2$length(SuiCore$Vec2 *  self);
float  SuiCore$Vec2$anhattanLength(SuiCore$Vec2 *  self);
SuiCore$Vec2 *  SuiCore$Vec2$normalizeLocal(SuiCore$Vec2 *  self);
float  SuiCore$Vec2$angle(SuiCore$Vec2 *  self);
float  SuiCore$Vec2$angleTo(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
float  SuiCore$Vec2$distanceTo(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
float  SuiCore$Vec2$distanceToSquared(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
float  SuiCore$Vec2$manhattanDistanceTo(SuiCore$Vec2 *  self, SuiCore$Vec2 v);
SuiCore$Vec2 *  SuiCore$Vec2$setLengthLocal(SuiCore$Vec2 *  self, float  length);
SuiCore$Vec2 *  SuiCore$Vec2$lerpLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v, float  alpha);
SuiCore$Vec2 *  SuiCore$Vec2$lerpVectorsLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 v1, SuiCore$Vec2 v2, float  alpha);
SuiCore$Vec2 *  SuiCore$Vec2$fromArray(SuiCore$Vec2 *  self, float *  array, int  offset);
float *  SuiCore$Vec2$toArray(SuiCore$Vec2 *  self, float *  array, int  offset);
SuiCore$Vec2 *  SuiCore$Vec2$rotateAroundLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 center, float  angle);
SuiCore$Vec2 *  SuiCore$Vec2$randomLocal(SuiCore$Vec2 *  self);
SuiCore$Vec2 SuiCore$Vec2$scale(SuiCore$Vec2 *  self, float  f);
SuiCore$Vec2 *  SuiCore$Vec2$clampLengthLocal(SuiCore$Vec2 *  self, float  min, float  max);
void  SuiCore$Vec2$clampLocal(SuiCore$Vec2 *  self, SuiCore$Vec2 min, SuiCore$Vec2 max);
SuiCore$Vec2 SuiCore$Vec2$clamp(SuiCore$Vec2 *  self, SuiCore$Vec2 min, SuiCore$Vec2 max);
SuiCore$Vec2 *  SuiCore$Vec2$clampScalarLocal(SuiCore$Vec2 *  self, float  minVal, float  maxVal);
SuiCore$Vec2 SuiCore$Vec2$clampScalar(SuiCore$Vec2 *  self, float  minVal, float  maxVal);
SuiCore$Vec2 SuiCore$Vec2$add(SuiCore$Vec2 *  self, SuiCore$Vec2 b);
SuiCore$Vec2 SuiCore$Vec2$sub(SuiCore$Vec2 *  self, SuiCore$Vec2 b);
float  SuiCore$Vec2$radToXAxis(SuiCore$Vec2 *  self);
bool  SuiCore$Vec2$equals(SuiCore$Vec2 *  self, SuiCore$Vec2 b);
SuiCore$Vec2 SuiCore$mkVec2(float  x, float  y);
void  SuiCore$testVec2();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
