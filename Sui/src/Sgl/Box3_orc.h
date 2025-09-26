
typedef struct tagSgl$Box3 Sgl$Box3;


#ifndef define_struct___Sgl__Box3_orc_h__
#define define_struct___Sgl__Box3_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Box3_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INCLUDE_ONLY_TYPE
#include "../Sui/Core/Vec3_orc.h"
#undef INCLUDE_ONLY_TYPE



#ifdef INCLUDE_ONLY_TYPE___Sgl__Box3_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSgl$Box3 {
	SuiCore$Vec3 min ;
	SuiCore$Vec3 max ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Box3_orc_h__
#define __Sgl__Box3_orc_h__

//include  importHeadCode
#include "../Sui/Core/Vec3_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sgl/Buffer_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./Sphere_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* Sgl$Box3_getOrInitMetaStruct();

void  Sgl$Box3$set(Sgl$Box3 *  self, SuiCore$Vec3 min, SuiCore$Vec3 max);
void  Sgl$Box3$setFromArray(Sgl$Box3 *  self, Sgl$FloatArray *  array);
void  Sgl$Box3$setFromPoints(Sgl$Box3 *  self, Sgl$Vec3Array *  points);
void  Sgl$Box3$setFromCenterAndSize(Sgl$Box3 *  self, SuiCore$Vec3 center, SuiCore$Vec3 size);
Sgl$Box3 Sgl$Box3$clone(Sgl$Box3 *  self);
void  Sgl$Box3$copy(Sgl$Box3 *  self, Sgl$Box3 box);
void  Sgl$Box3$makeEmpty(Sgl$Box3 *  self);
bool  Sgl$Box3$isEmpty(Sgl$Box3 *  self);
SuiCore$Vec3 Sgl$Box3$getCenter(Sgl$Box3 *  self);
SuiCore$Vec3 Sgl$Box3$getSize(Sgl$Box3 *  self);
void  Sgl$Box3$expandByPoint(Sgl$Box3 *  self, SuiCore$Vec3 point);
void  Sgl$Box3$expandByVector(Sgl$Box3 *  self, SuiCore$Vec3 vector);
void  Sgl$Box3$expandByScalar(Sgl$Box3 *  self, float  scalar);
bool  Sgl$Box3$containsPoint(Sgl$Box3 *  self, SuiCore$Vec3 point);
bool  Sgl$Box3$containsBox(Sgl$Box3 *  self, Sgl$Box3 box);
SuiCore$Vec3 Sgl$Box3$getParameter(Sgl$Box3 *  self, SuiCore$Vec3 point);
bool  Sgl$Box3$intersectsBox(Sgl$Box3 *  self, Sgl$Box3 box);
bool  Sgl$Box3$intersectsSphere(Sgl$Box3 *  self, Sgl$Sphere sphere);
SuiCore$Vec3 Sgl$Box3$clampPoint(Sgl$Box3 *  self, SuiCore$Vec3 point);
float  Sgl$Box3$distanceToPoint(Sgl$Box3 *  self, SuiCore$Vec3 point);
Sgl$Sphere Sgl$Box3$getBoundingSphere(Sgl$Box3 *  self);
Sgl$Box3 Sgl$Box3$intersect(Sgl$Box3 *  self, Sgl$Box3 box);
Sgl$Box3 Sgl$Box3$union(Sgl$Box3 *  self, Sgl$Box3 box);
void  Sgl$Box3$translate(Sgl$Box3 *  self, SuiCore$Vec3 offset);
bool  Sgl$Box3$equals(Sgl$Box3 *  self, Sgl$Box3 box);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
