
typedef struct tagSuiCore$Edge SuiCore$Edge;
typedef struct tagVtable_SuiCore$Edge Vtable_SuiCore$Edge;


#ifndef define_struct___SuiCore__Edge_orc_h__
#define define_struct___SuiCore__Edge_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Edge_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Edge_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Edge_orc_h__
#define __SuiCore__Edge_orc_h__

//include  importHeadCode


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$Edge {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Edge _vtable_SuiCore$Edge;

// class refc:1
struct tagSuiCore$Edge {
	Object super; 
	float  w ;
	int  color ;
	void  (*copyFrom) (SuiCore$Edge *  self, SuiCore$Edge *  v);
	void  (*set) (SuiCore$Edge *  self, float  w, int  color);
};
Vtable_SuiCore$Edge* Vtable_SuiCore$Edge_init(Vtable_SuiCore$Edge* pvt);
void SuiCore$Edge_init_fields(SuiCore$Edge *self);
void SuiCore$Edge_init(SuiCore$Edge *self, void *pOwner);
SuiCore$Edge * SuiCore$Edge_new(void *pOwner);
void SuiCore$Edge_fini(SuiCore$Edge *self);

void  SuiCore$Edge$copyFrom(SuiCore$Edge *  self, SuiCore$Edge *  v);
void  SuiCore$Edge$set(SuiCore$Edge *  self, float  w, int  color);

void  SuiCore$testEdge();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
