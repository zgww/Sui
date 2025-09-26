
typedef struct tagSuiCore$Line3 SuiCore$Line3;


#ifndef define_struct___SuiCore__Line3_orc_h__
#define define_struct___SuiCore__Line3_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Line3_orc_h__
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



#ifdef INCLUDE_ONLY_TYPE___SuiCore__Line3_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Line3 {
	SuiCore$Vec3 start ;
	SuiCore$Vec3 end ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Line3_orc_h__
#define __SuiCore__Line3_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "./Mat3_orc.h"
#include "./Vec3_orc.h"
#include "./Plane_orc.h"
#include "./Spherical_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Line3_getOrInitMetaStruct();

SuiCore$Line3 *  SuiCore$Line3$set(SuiCore$Line3 *  self, SuiCore$Vec3 start, SuiCore$Vec3 end);
SuiCore$Line3 *  SuiCore$Line3$copy(SuiCore$Line3 *  self, SuiCore$Line3 line);
SuiCore$Vec3 SuiCore$Line3$getCenter(SuiCore$Line3 *  self);
SuiCore$Vec3 SuiCore$Line3$delta(SuiCore$Line3 *  self);
float  SuiCore$Line3$distanceSq(SuiCore$Line3 *  self);
float  SuiCore$Line3$distance(SuiCore$Line3 *  self);
SuiCore$Vec3 SuiCore$Line3$at(SuiCore$Line3 *  self, float  t);
float  SuiCore$Line3$closestPointToPointParameter(SuiCore$Line3 *  self, SuiCore$Vec3 point, bool  clampToLine);
SuiCore$Vec3 SuiCore$Line3$closestPointToPoint(SuiCore$Line3 *  self, SuiCore$Vec3 point, bool  clampToLine);
SuiCore$Line3 *  SuiCore$Line3$applyMatrix4Local(SuiCore$Line3 *  self, Sgl$Mat matrix);
bool  SuiCore$Line3$equals(SuiCore$Line3 *  self, SuiCore$Line3 line);
SuiCore$Line3 SuiCore$Line3$clone(SuiCore$Line3 *  self);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
