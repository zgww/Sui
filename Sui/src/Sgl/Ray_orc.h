
typedef struct tagSgl$Ray Sgl$Ray;
typedef struct tagSgl$IntersectResult Sgl$IntersectResult;


#ifndef define_struct___Sgl__Ray_orc_h__
#define define_struct___Sgl__Ray_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Ray_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INCLUDE_ONLY_TYPE
#include "../Sui/Core/Vec3_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "../Sui/Core/Vec3_orc.h"
#undef INCLUDE_ONLY_TYPE



#ifdef INCLUDE_ONLY_TYPE___Sgl__Ray_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSgl$Ray {
	SuiCore$Vec3 origin ;
	SuiCore$Vec3 direction ;
};


struct tagSgl$IntersectResult {
	SuiCore$Vec3 point ;
	bool  succ ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Ray_orc_h__
#define __Sgl__Ray_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./Sphere_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "./Box3_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./Mat_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* Sgl$Ray_getOrInitMetaStruct();



//结构体元数据获取即初始化
MetaStruct* Sgl$IntersectResult_getOrInitMetaStruct();

Sgl$IntersectResult Sgl$mkIntersectResult(SuiCore$Vec3 point);
Sgl$IntersectResult Sgl$mkIntersectResultFail();
Sgl$Ray Sgl$mkRay(SuiCore$Vec3 origin, SuiCore$Vec3 direction);
void  Sgl$Ray$set(Sgl$Ray *  self, SuiCore$Vec3 origin, SuiCore$Vec3 direction);
void  Sgl$Ray$copy(Sgl$Ray *  self, Sgl$Ray ray);
SuiCore$Vec3 Sgl$Ray$at(Sgl$Ray *  self, float  t);
void  Sgl$Ray$lookAt(Sgl$Ray *  self, SuiCore$Vec3 v);
void  Sgl$Ray$recast(Sgl$Ray *  self, float  t);
SuiCore$Vec3 Sgl$Ray$closestPointToPoint(Sgl$Ray *  self, SuiCore$Vec3 point);
float  Sgl$Ray$distanceToPoint(Sgl$Ray *  self, SuiCore$Vec3 point);
float  Sgl$Ray$distanceSqToPoint(Sgl$Ray *  self, SuiCore$Vec3 point);
Sgl$IntersectResult Sgl$Ray$intersectSphere(Sgl$Ray *  self, Sgl$Sphere sphere, SuiCore$Vec3 result);
bool  Sgl$Ray$intersectsSphere(Sgl$Ray *  self, Sgl$Sphere sphere);
Sgl$IntersectResult Sgl$Ray$intersectBox(Sgl$Ray *  self, Sgl$Box3 box);
bool  Sgl$Ray$intersectsBox(Sgl$Ray *  self, Sgl$Box3 box);
Sgl$IntersectResult Sgl$Ray$intersectTriangle(Sgl$Ray *  self, SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c, bool  backfaceCulling);
void  Sgl$Ray$applyMatrix4Local(Sgl$Ray *  self, Sgl$Mat matrix4);
bool  Sgl$Ray$equals(Sgl$Ray *  self, Sgl$Ray ray);
Sgl$Ray Sgl$Ray$clone(Sgl$Ray *  self);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
