
typedef struct tagSuiCore$Plane SuiCore$Plane;


#ifndef define_struct___SuiCore__Plane_orc_h__
#define define_struct___SuiCore__Plane_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Plane_orc_h__
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



#ifdef INCLUDE_ONLY_TYPE___SuiCore__Plane_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Plane {
	SuiCore$Vec3 normal ;
	float  constant ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Plane_orc_h__
#define __SuiCore__Plane_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../../Sgl/Sphere_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./Mat3_orc.h"
#include "./Vec3_orc.h"
#include "./Spherical_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Plane_getOrInitMetaStruct();

SuiCore$Plane *  SuiCore$Plane$set(SuiCore$Plane *  self, SuiCore$Vec3 normal, float  constant);
SuiCore$Plane *  SuiCore$Plane$setComponents(SuiCore$Plane *  self, float  x, float  y, float  z, float  w);
SuiCore$Plane *  SuiCore$Plane$setFromNormalAndCoplanarPoint(SuiCore$Plane *  self, SuiCore$Vec3 normal, SuiCore$Vec3 point);
SuiCore$Plane *  SuiCore$Plane$setFromCoplanarPoints(SuiCore$Plane *  self, SuiCore$Vec3 a, SuiCore$Vec3 b, SuiCore$Vec3 c);
SuiCore$Plane *  SuiCore$Plane$copy(SuiCore$Plane *  self, SuiCore$Plane plane);
SuiCore$Plane *  SuiCore$Plane$normalizeLocal(SuiCore$Plane *  self);
SuiCore$Plane *  SuiCore$Plane$negateLocal(SuiCore$Plane *  self);
float  SuiCore$Plane$distanceToPoint(SuiCore$Plane *  self, SuiCore$Vec3 point);
float  SuiCore$Plane$distanceToSphere(SuiCore$Plane *  self, Sgl$Sphere sphere);
SuiCore$Vec3 SuiCore$Plane$projectPoint(SuiCore$Plane *  self, SuiCore$Vec3 point);
SuiCore$Vec3 SuiCore$Plane$coplanarPoint(SuiCore$Plane *  self);
SuiCore$Plane *  SuiCore$Plane$translate(SuiCore$Plane *  self, SuiCore$Vec3 offset);
bool  SuiCore$Plane$equals(SuiCore$Plane *  self, SuiCore$Plane plane);
SuiCore$Plane SuiCore$Plane$clone(SuiCore$Plane *  self);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
