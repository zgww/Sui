
typedef struct tagSuiCore$Border SuiCore$Border;
typedef struct tagVtable_SuiCore$Border Vtable_SuiCore$Border;


#ifndef define_struct___SuiCore__Border_orc_h__
#define define_struct___SuiCore__Border_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Border_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Border_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Border_orc_h__
#define __SuiCore__Border_orc_h__

//include  importHeadCode
#include "./Edge_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$Border {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Border _vtable_SuiCore$Border;

// class refc:0
struct tagSuiCore$Border {
	Object super; 
	SuiCore$Edge*  t ;
	SuiCore$Edge*  r ;
	SuiCore$Edge*  b ;
	SuiCore$Edge*  l ;
	bool  (*isAllHasWidth) (SuiCore$Border *  self);
	void  (*copyFrom) (SuiCore$Border *  self, SuiCore$Border *  b);
	void  (*setAll) (SuiCore$Border *  self, float  w, int  color);
	float  (*hor) (SuiCore$Border *  self);
	float  (*ver) (SuiCore$Border *  self);
};
Vtable_SuiCore$Border* Vtable_SuiCore$Border_init(Vtable_SuiCore$Border* pvt);
void SuiCore$Border_init_fields(SuiCore$Border *self);
void SuiCore$Border_init(SuiCore$Border *self, void *pOwner);
SuiCore$Border * SuiCore$Border_new(void *pOwner);
void SuiCore$Border_fini(SuiCore$Border *self);

bool  SuiCore$Border$isAllHasWidth(SuiCore$Border *  self);
void  SuiCore$Border$copyFrom(SuiCore$Border *  self, SuiCore$Border *  b);
void  SuiCore$Border$setAll(SuiCore$Border *  self, float  w, int  color);
float  SuiCore$Border$hor(SuiCore$Border *  self);
float  SuiCore$Border$ver(SuiCore$Border *  self);

SuiCore$Border*  SuiCore$mkBorder(SuiCore$Border **  __outRef__, float  w, int  color);
void  SuiCore$testBorder();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
