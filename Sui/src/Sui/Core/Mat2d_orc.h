
typedef struct tagSuiCore$Mat2d SuiCore$Mat2d;


#ifndef define_struct___SuiCore__Mat2d_orc_h__
#define define_struct___SuiCore__Mat2d_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Mat2d_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Mat2d_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Mat2d {
	float  data[6] ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Mat2d_orc_h__
#define __SuiCore__Mat2d_orc_h__

//include  importHeadCode
#include "./Node_orc.h"
#include "./Rect_orc.h"
#include "../../Orc/String_orc.h"
#include "./Vec2_orc.h"
#include "./Vec3_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Mat2d_getOrInitMetaStruct();

extern void  SuiCore$Mat2d$identity(SuiCore$Mat2d *  self);
extern void  SuiCore$Mat2d$translate(SuiCore$Mat2d *  self, float  x, float  y, float  z);
extern void  SuiCore$Mat2d$scale(SuiCore$Mat2d *  self, float  x, float  y, float  z);
extern void  SuiCore$Mat2d$rotate(SuiCore$Mat2d *  self, float  x, float  y, float  z);
extern void  SuiCore$Mat2d$multiply(SuiCore$Mat2d *  self, SuiCore$Mat2d *  b);
extern void  SuiCore$Mat2d$premultiply(SuiCore$Mat2d *  self, SuiCore$Mat2d *  b);
extern void  SuiCore$Mat2d$inverse(SuiCore$Mat2d *  self);
SuiCore$Mat2d SuiCore$Mat2d$inverseNew(SuiCore$Mat2d *  self);
extern SuiCore$Vec3 SuiCore$Mat2d$transformPoint(SuiCore$Mat2d *  self, float  x, float  y, float  z);
SuiCore$Vec3 SuiCore$Mat2d$localToLocal(SuiCore$Mat2d *  self, SuiCore$Mat2d *  invMat2d, float  x, float  y, float  z);
extern SuiCore$Mat2d SuiCore$mkMat2d();
void  SuiCore$testMat2d();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
