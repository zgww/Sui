
typedef struct tagSuiCore$Bezier SuiCore$Bezier;


#ifndef define_struct___SuiCore__Bezier_orc_h__
#define define_struct___SuiCore__Bezier_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Bezier_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INCLUDE_ONLY_TYPE
#include "./Vec2_orc.h"
#undef INCLUDE_ONLY_TYPE



#ifdef INCLUDE_ONLY_TYPE___SuiCore__Bezier_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Bezier {
	SuiCore$Vec2 start ;
	SuiCore$Vec2 c0 ;
	SuiCore$Vec2 c1 ;
	SuiCore$Vec2 end ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Bezier_orc_h__
#define __SuiCore__Bezier_orc_h__

//include  importHeadCode
#include "./Vec2_orc.h"
#include "../../Orc/String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Bezier_getOrInitMetaStruct();

SuiCore$Bezier SuiCore$mkBezier();
Orc$String*  SuiCore$Bezier$toString(Orc$String **  __outRef__, SuiCore$Bezier *  self);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
