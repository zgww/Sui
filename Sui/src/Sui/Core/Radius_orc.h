
typedef struct tagSuiCore$Radius SuiCore$Radius;
typedef struct tagVtable_SuiCore$Radius Vtable_SuiCore$Radius;


#ifndef define_struct___SuiCore__Radius_orc_h__
#define define_struct___SuiCore__Radius_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Radius_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Radius_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Radius_orc_h__
#define __SuiCore__Radius_orc_h__

//include  importHeadCode


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$Radius {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Radius _vtable_SuiCore$Radius;

// class refc:1
struct tagSuiCore$Radius {
	Object super; 
	float  tl ;
	float  tr ;
	float  bl ;
	float  br ;
	void  (*setAll) (SuiCore$Radius *  self, float  r);
};
Vtable_SuiCore$Radius* Vtable_SuiCore$Radius_init(Vtable_SuiCore$Radius* pvt);
void SuiCore$Radius_init_fields(SuiCore$Radius *self);
void SuiCore$Radius_init(SuiCore$Radius *self, void *pOwner);
SuiCore$Radius * SuiCore$Radius_new(void *pOwner);
void SuiCore$Radius_fini(SuiCore$Radius *self);

void  SuiCore$Radius$dtor(SuiCore$Radius *  self);
void  SuiCore$Radius$setAll(SuiCore$Radius *  self, float  r);

void  SuiCore$testRadius();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
