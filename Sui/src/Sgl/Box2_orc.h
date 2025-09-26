
typedef struct tagSgl$Box2 Sgl$Box2;


#ifndef define_struct___Sgl__Box2_orc_h__
#define define_struct___Sgl__Box2_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Box2_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define INCLUDE_ONLY_TYPE
#include "../Sui/Core/Vec2_orc.h"
#undef INCLUDE_ONLY_TYPE



#ifdef INCLUDE_ONLY_TYPE___Sgl__Box2_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSgl$Box2 {
	SuiCore$Vec2 min ;
	SuiCore$Vec2 max ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Box2_orc_h__
#define __Sgl__Box2_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sgl/Buffer_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* Sgl$Box2_getOrInitMetaStruct();

Sgl$Box2 Sgl$mkBox2Zero();
void  Sgl$Box2$set(Sgl$Box2 *  self, SuiCore$Vec2 min, SuiCore$Vec2 max);
Sgl$Box2 *  Sgl$Box2$setFromPoints(Sgl$Box2 *  self, Sgl$Vec2Array *  points);
void  Sgl$Box2$setFromCenterAndSize(Sgl$Box2 *  self, SuiCore$Vec2 center, SuiCore$Vec2 size);
void  Sgl$Box2$makeEmpty(Sgl$Box2 *  self);
bool  Sgl$Box2$isEmpty(Sgl$Box2 *  self);
SuiCore$Vec2 Sgl$Box2$getCenter(Sgl$Box2 *  self);
SuiCore$Vec2 Sgl$Box2$getSize(Sgl$Box2 *  self);
void  Sgl$Box2$expandByPoint(Sgl$Box2 *  self, SuiCore$Vec2 point);
void  Sgl$Box2$expandByVector(Sgl$Box2 *  self, SuiCore$Vec2 vector);
void  Sgl$Box2$expandByScalar(Sgl$Box2 *  self, float  scalar);
bool  Sgl$Box2$containsPoint(Sgl$Box2 *  self, SuiCore$Vec2 point);
bool  Sgl$Box2$containsBox(Sgl$Box2 *  self, Sgl$Box2 box);
SuiCore$Vec2 Sgl$Box2$getParameter(Sgl$Box2 *  self, SuiCore$Vec2 point);
bool  Sgl$Box2$intersectsBox(Sgl$Box2 *  self, Sgl$Box2 box);
SuiCore$Vec2 Sgl$Box2$clampPoint(Sgl$Box2 *  self, SuiCore$Vec2 point);
float  Sgl$Box2$distanceToPoint(Sgl$Box2 *  self, SuiCore$Vec2 point);
void  Sgl$Box2$intersect(Sgl$Box2 *  self, Sgl$Box2 box);
void  Sgl$Box2$union(Sgl$Box2 *  self, Sgl$Box2 box);
void  Sgl$Box2$translate(Sgl$Box2 *  self, SuiCore$Vec2 offset);
bool  Sgl$Box2$equals(Sgl$Box2 *  self, Sgl$Box2 box);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
