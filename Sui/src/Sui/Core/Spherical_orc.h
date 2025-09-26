
typedef struct tagSuiCore$Spherical SuiCore$Spherical;


#ifndef define_struct___SuiCore__Spherical_orc_h__
#define define_struct___SuiCore__Spherical_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Spherical_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Spherical_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Spherical {
	float  radius ;
	float  phi ;
	float  theta ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Spherical_orc_h__
#define __SuiCore__Spherical_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "./Mat3_orc.h"
#include "./Vec3_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Spherical_getOrInitMetaStruct();

SuiCore$Spherical *  SuiCore$Spherical$set(SuiCore$Spherical *  self, float  radius, float  phi, float  theta);
SuiCore$Spherical *  SuiCore$Spherical$copy(SuiCore$Spherical *  self, SuiCore$Spherical other);
SuiCore$Spherical *  SuiCore$Spherical$makeSafe(SuiCore$Spherical *  self);
SuiCore$Spherical *  SuiCore$Spherical$setFromVector3(SuiCore$Spherical *  self, SuiCore$Vec3 v);
SuiCore$Spherical *  SuiCore$Spherical$setFromCartesianCoords(SuiCore$Spherical *  self, float  x, float  y, float  z);
SuiCore$Spherical SuiCore$Spherical$clone(SuiCore$Spherical *  self);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
