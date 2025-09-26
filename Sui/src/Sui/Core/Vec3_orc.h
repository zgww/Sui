
typedef struct tagSuiCore$Vec3 SuiCore$Vec3;


#ifndef define_struct___SuiCore__Vec3_orc_h__
#define define_struct___SuiCore__Vec3_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Vec3_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Vec3_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Vec3 {
	float  x ;
	float  y ;
	float  z ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Vec3_orc_h__
#define __SuiCore__Vec3_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "./Mat3_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./Euler_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "./Color_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "./Spherical_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Vec3_getOrInitMetaStruct();

Orc$String*  SuiCore$Vec3$toString(Orc$String **  __outRef__, SuiCore$Vec3 *  self);
float  SuiCore$Vec3$width(SuiCore$Vec3 *  self);
float  SuiCore$Vec3$height(SuiCore$Vec3 *  self);
SuiCore$Vec3 *  SuiCore$Vec3$set(SuiCore$Vec3 *  self, float  x, float  y, float  z);
SuiCore$Vec3 *  SuiCore$Vec3$setScalar(SuiCore$Vec3 *  self, float  scalar);
SuiCore$Vec3 *  SuiCore$Vec3$setX(SuiCore$Vec3 *  self, float  x);
SuiCore$Vec3 *  SuiCore$Vec3$setY(SuiCore$Vec3 *  self, float  y);
SuiCore$Vec3 *  SuiCore$Vec3$setZ(SuiCore$Vec3 *  self, float  z);
SuiCore$Vec3 *  SuiCore$Vec3$setComponent(SuiCore$Vec3 *  self, int  index, float  value);
float  SuiCore$Vec3$getComponent(SuiCore$Vec3 *  self, int  index);
SuiCore$Vec3 SuiCore$Vec3$clone(SuiCore$Vec3 *  self);
SuiCore$Vec3 *  SuiCore$Vec3$copy(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
SuiCore$Vec3 *  SuiCore$Vec3$addLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
SuiCore$Vec3 *  SuiCore$Vec3$addScalarLocal(SuiCore$Vec3 *  self, float  s);
SuiCore$Vec3 *  SuiCore$Vec3$addVectorsLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 a, SuiCore$Vec3 b);
SuiCore$Vec3 *  SuiCore$Vec3$addScaledVectorLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v, float  s);
SuiCore$Vec3 *  SuiCore$Vec3$subLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
SuiCore$Vec3 *  SuiCore$Vec3$subScalarLocal(SuiCore$Vec3 *  self, float  s);
SuiCore$Vec3 *  SuiCore$Vec3$subVectorsLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 a, SuiCore$Vec3 b);
SuiCore$Vec3 *  SuiCore$Vec3$multiplyLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
SuiCore$Vec3 *  SuiCore$Vec3$multiplyScalarLocal(SuiCore$Vec3 *  self, float  scalar);
SuiCore$Vec3 *  SuiCore$Vec3$multiplyVectorsLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 a, SuiCore$Vec3 b);
SuiCore$Vec3 *  SuiCore$Vec3$applyMatrix3Local(SuiCore$Vec3 *  self, SuiCore$Mat3 m);
SuiCore$Vec3 *  SuiCore$Vec3$applyNormalMatrixLocal(SuiCore$Vec3 *  self, SuiCore$Mat3 m);
SuiCore$Vec3 SuiCore$Vec3$applyMatrix4(SuiCore$Vec3 *  self, Sgl$Mat m);
SuiCore$Vec3 *  SuiCore$Vec3$applyMatrix4Local(SuiCore$Vec3 *  self, Sgl$Mat m);
SuiCore$Vec3 *  SuiCore$Vec3$transformDirectionLocal(SuiCore$Vec3 *  self, Sgl$Mat m);
SuiCore$Vec3 *  SuiCore$Vec3$divideLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
SuiCore$Vec3 *  SuiCore$Vec3$divideScalarLocal(SuiCore$Vec3 *  self, float  scalar);
SuiCore$Vec3 *  SuiCore$Vec3$minLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
SuiCore$Vec3 *  SuiCore$Vec3$maxLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
SuiCore$Vec3 *  SuiCore$Vec3$floorLocal(SuiCore$Vec3 *  self);
SuiCore$Vec3 *  SuiCore$Vec3$ceilLocal(SuiCore$Vec3 *  self);
SuiCore$Vec3 *  SuiCore$Vec3$roundLocal(SuiCore$Vec3 *  self);
SuiCore$Vec3 *  SuiCore$Vec3$roundToZeroLocal(SuiCore$Vec3 *  self);
SuiCore$Vec3 *  SuiCore$Vec3$negateLocal(SuiCore$Vec3 *  self);
float  SuiCore$Vec3$dot(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
float  SuiCore$Vec3$lengthSq(SuiCore$Vec3 *  self);
float  SuiCore$Vec3$length(SuiCore$Vec3 *  self);
float  SuiCore$Vec3$manhattanLength(SuiCore$Vec3 *  self);
SuiCore$Vec3 SuiCore$Vec3$normal(SuiCore$Vec3 *  self);
SuiCore$Vec3 *  SuiCore$Vec3$normalizeLocal(SuiCore$Vec3 *  self);
SuiCore$Vec3 *  SuiCore$Vec3$setLength(SuiCore$Vec3 *  self, float  length);
SuiCore$Vec3 SuiCore$Vec3$lerp(SuiCore$Vec3 *  self, SuiCore$Vec3 b, float  ratio);
SuiCore$Vec3 *  SuiCore$Vec3$lerpLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v, float  alpha);
SuiCore$Vec3 *  SuiCore$Vec3$lerpVectorsLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v1, SuiCore$Vec3 v2, float  alpha);
SuiCore$Vec3 SuiCore$Vec3$cross(SuiCore$Vec3 *  self, SuiCore$Vec3 b);
SuiCore$Vec3 *  SuiCore$Vec3$crossLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
SuiCore$Vec3 *  SuiCore$Vec3$crossVectorsLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 a, SuiCore$Vec3 b);
SuiCore$Vec3 *  SuiCore$Vec3$projectOnVectorLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
SuiCore$Vec3 *  SuiCore$Vec3$reflect(SuiCore$Vec3 *  self, SuiCore$Vec3 normal);
float  SuiCore$Vec3$angleTo(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
float  SuiCore$Vec3$distanceTo(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
float  SuiCore$Vec3$distanceToSquared(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
float  SuiCore$Vec3$manhattanDistanceTo(SuiCore$Vec3 *  self, SuiCore$Vec3 v);
SuiCore$Vec3 *  SuiCore$Vec3$setFromSphericalLocal(SuiCore$Vec3 *  self, SuiCore$Spherical s);
SuiCore$Vec3 *  SuiCore$Vec3$setFromSphericalCoordsLocal(SuiCore$Vec3 *  self, float  radius, float  phi, float  theta);
SuiCore$Vec3 *  SuiCore$Vec3$setFromMatrixPosition(SuiCore$Vec3 *  self, Sgl$Mat m);
SuiCore$Vec3 *  SuiCore$Vec3$setFromMatrixScale(SuiCore$Vec3 *  self, Sgl$Mat m);
SuiCore$Vec3 *  SuiCore$Vec3$setFromMatrixColumn(SuiCore$Vec3 *  self, Sgl$Mat m, int  index);
SuiCore$Vec3 *  SuiCore$Vec3$setFromMatrix3Column(SuiCore$Vec3 *  self, SuiCore$Mat3 m, int  index);
SuiCore$Vec3 *  SuiCore$Vec3$setFromEuler(SuiCore$Vec3 *  self, SuiCore$Euler e);
SuiCore$Vec3 *  SuiCore$Vec3$setFromRgbaf(SuiCore$Vec3 *  self, SuiCore$Rgbaf c);
SuiCore$Vec3 *  SuiCore$Vec3$fromArray(SuiCore$Vec3 *  self, float *  array, int  offset);
float *  SuiCore$Vec3$toArray(SuiCore$Vec3 *  self, float *  array, int  offset);
SuiCore$Vec3 *  SuiCore$Vec3$randomLocal(SuiCore$Vec3 *  self);
SuiCore$Vec3 *  SuiCore$Vec3$randomDirectionLocal(SuiCore$Vec3 *  self);
SuiCore$Vec3 SuiCore$Vec3$scale(SuiCore$Vec3 *  self, float  f);
SuiCore$Vec3 *  SuiCore$Vec3$add3fLocal(SuiCore$Vec3 *  self, float  x, float  y, float  z);
SuiCore$Vec3 SuiCore$Vec3$add3f(SuiCore$Vec3 *  self, float  x, float  y, float  z);
SuiCore$Vec3 SuiCore$Vec3$add(SuiCore$Vec3 *  self, SuiCore$Vec3 b);
SuiCore$Vec3 SuiCore$Vec3$sub(SuiCore$Vec3 *  self, SuiCore$Vec3 b);
void  SuiCore$Vec3$setAll(SuiCore$Vec3 *  self, float  v);
bool  SuiCore$Vec3$equals(SuiCore$Vec3 *  self, SuiCore$Vec3 b);
SuiCore$Vec3 *  SuiCore$Vec3$clampLocal(SuiCore$Vec3 *  self, SuiCore$Vec3 min, SuiCore$Vec3 max);
SuiCore$Vec3 *  SuiCore$Vec3$clampScalarLocal(SuiCore$Vec3 *  self, float  minVal, float  maxVal);
SuiCore$Vec3 *  SuiCore$Vec3$clampLengthLocal(SuiCore$Vec3 *  self, float  min, float  max);
SuiCore$Vec3 SuiCore$Vec3$clamp(SuiCore$Vec3 *  self, SuiCore$Vec3 min, SuiCore$Vec3 max);
SuiCore$Vec3 SuiCore$Vec3$clampScalar(SuiCore$Vec3 *  self, float  minVal, float  maxVal);
SuiCore$Vec3 SuiCore$Vec3$clampLength(SuiCore$Vec3 *  self, float  min, float  max);
SuiCore$Vec3 SuiCore$mkVec3(float  x, float  y, float  z);
void  SuiCore$testVec3();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
