
typedef struct tagSgl$Sphere Sgl$Sphere;


#ifndef define_struct___Sgl__Sphere_orc_h__
#define define_struct___Sgl__Sphere_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Sphere_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INCLUDE_ONLY_TYPE
#include "../Sui/Core/Vec3_orc.h"
#undef INCLUDE_ONLY_TYPE



#ifdef INCLUDE_ONLY_TYPE___Sgl__Sphere_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSgl$Sphere {
	SuiCore$Vec3 center ;
	float  radius ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Sphere_orc_h__
#define __Sgl__Sphere_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sgl/Buffer_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../Sgl/Box3_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "../Sgl/Mat_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* Sgl$Sphere_getOrInitMetaStruct();

Sgl$Sphere *  Sgl$Sphere$set(Sgl$Sphere *  self, SuiCore$Vec3 center, float  radius);
Sgl$Sphere *  Sgl$Sphere$setFromPoints(Sgl$Sphere *  self, Sgl$Vec3Array *  points, SuiCore$Vec3 *  optionalCenter);
Sgl$Sphere *  Sgl$Sphere$copy(Sgl$Sphere *  self, Sgl$Sphere sphere);
bool  Sgl$Sphere$isEmpty(Sgl$Sphere *  self);
void  Sgl$Sphere$makeEmpty(Sgl$Sphere *  self);
bool  Sgl$Sphere$containsPoint(Sgl$Sphere *  self, SuiCore$Vec3 point);
float  Sgl$Sphere$distanceToPoint(Sgl$Sphere *  self, SuiCore$Vec3 point);
float  Sgl$Sphere$intersectsSphere(Sgl$Sphere *  self, Sgl$Sphere sphere);
bool  Sgl$Sphere$intersectsBox(Sgl$Sphere *  self, Sgl$Box3 box);
SuiCore$Vec3 Sgl$Sphere$clampPoint(Sgl$Sphere *  self, SuiCore$Vec3 point);
Sgl$Box3 Sgl$Sphere$getBoundingBox(Sgl$Sphere *  self);
void  Sgl$Sphere$applyMatrix4Local(Sgl$Sphere *  self, Sgl$Mat matrix);
void  Sgl$Sphere$translate(Sgl$Sphere *  self, SuiCore$Vec3 offset);
void  Sgl$Sphere$expandByPoint(Sgl$Sphere *  self, SuiCore$Vec3 point);
Sgl$Sphere *  Sgl$Sphere$union(Sgl$Sphere *  self, Sgl$Sphere sphere);
bool  Sgl$Sphere$equals(Sgl$Sphere *  self, Sgl$Sphere sphere);
Sgl$Sphere Sgl$Sphere$clone(Sgl$Sphere *  self);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
