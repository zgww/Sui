
typedef struct tagSuiCore$Triangle SuiCore$Triangle;


#ifndef define_struct___SuiCore__Triangle_orc_h__
#define define_struct___SuiCore__Triangle_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Triangle_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INCLUDE_ONLY_TYPE
#include "./Vec3_orc.h"
#undef INCLUDE_ONLY_TYPE



#ifdef INCLUDE_ONLY_TYPE___SuiCore__Triangle_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Triangle {
	SuiCore$Vec3 a ;
	SuiCore$Vec3 b ;
	SuiCore$Vec3 c ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Triangle_orc_h__
#define __SuiCore__Triangle_orc_h__

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
#include "./Vec3_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./Spherical_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Triangle_getOrInitMetaStruct();

SuiCore$Triangle *  SuiCore$Triangle$set(SuiCore$Triangle *  self, SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c);
SuiCore$Triangle *  SuiCore$Triangle$setFromPointsAndIndices(SuiCore$Triangle *  self, SuiCore$Vec3 *  points, int  i0, int  i1, int  i2);
SuiCore$Triangle SuiCore$Triangle$clone(SuiCore$Triangle *  self);
SuiCore$Triangle *  SuiCore$Triangle$copy(SuiCore$Triangle *  self, SuiCore$Triangle triangle);
float  SuiCore$Triangle$getArea(SuiCore$Triangle *  self);
SuiCore$Vec3 SuiCore$Triangle$getMidpoint(SuiCore$Triangle *  self);
SuiCore$Vec3 SuiCore$Triangle$getNormal(SuiCore$Triangle *  self);
SuiCore$Plane SuiCore$Triangle$getPlane(SuiCore$Triangle *  self);
SuiCore$Vec3 SuiCore$Triangle$getBarycoord(SuiCore$Triangle *  self, SuiCore$Vec3 point);
SuiCore$Vec3 SuiCore$Triangle$getInterpolation(SuiCore$Triangle *  self, SuiCore$Vec3 point, SuiCore$Vec3 v1, SuiCore$Vec3 v2, SuiCore$Vec3 v3);
bool  SuiCore$Triangle$containsPoint(SuiCore$Triangle *  self, SuiCore$Vec3 point);
bool  SuiCore$Triangle$isFrontFacing(SuiCore$Triangle *  self, SuiCore$Vec3 direction);
SuiCore$Vec3 SuiCore$Triangle$closestPointToPoint(SuiCore$Triangle *  self, SuiCore$Vec3 p);
bool  SuiCore$Triangle$equals(SuiCore$Triangle *  self, SuiCore$Triangle triangle);
SuiCore$Vec3 SuiCore$Triangle_getNormal(SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c);
SuiCore$Vec3 SuiCore$Triangle_getBarycoord(SuiCore$Vec3 point, SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c);
bool  SuiCore$Triangle_containsPoint(SuiCore$Vec3 point, SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c);
bool  SuiCore$Triangle_isFrontFacing(SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c, SuiCore$Vec3 direction);
SuiCore$Vec3 SuiCore$Triangle_getInterpolation(SuiCore$Vec3 point, SuiCore$Vec3 p1, SuiCore$Vec3 p2, SuiCore$Vec3 p3, SuiCore$Vec3 v1, SuiCore$Vec3 v2, SuiCore$Vec3 v3);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
