
typedef struct tagSuiCore$Inset SuiCore$Inset;


#ifndef define_struct___SuiCore__Inset_orc_h__
#define define_struct___SuiCore__Inset_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Inset_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdlib.h>
#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Inset_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Inset {
	float  left ;
	float  top ;
	float  right ;
	float  bottom ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Inset_orc_h__
#define __SuiCore__Inset_orc_h__

//include  importHeadCode
#include "../../Orc/List_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Inset_getOrInitMetaStruct();

void  SuiCore$Inset$setAll(SuiCore$Inset *  self, float  v);
void  SuiCore$Inset$setAxis(SuiCore$Inset *  self, float  v, float  h);
void  SuiCore$Inset$setHor(SuiCore$Inset *  self, float  v);
void  SuiCore$Inset$setVer(SuiCore$Inset *  self, float  v);
float  SuiCore$Inset$hor(SuiCore$Inset *  self);
float  SuiCore$Inset$ver(SuiCore$Inset *  self);
void  SuiCore$Inset$invert(SuiCore$Inset *  self);
SuiCore$Inset SuiCore$mkInset0();
SuiCore$Inset SuiCore$mkInset(float  t, float  r, float  b, float  l);
void  SuiCore$testInset();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
