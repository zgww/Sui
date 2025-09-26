
typedef struct tagOrcLang$Thread OrcLang$Thread;
typedef struct tagVtable_OrcLang$Thread Vtable_OrcLang$Thread;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef ___orc_h__
#define ___orc_h__

//include  importHeadCode
#include "OrcLang/Orc.h"
#include <stdlib.h>
#include <stdio.h>
#include "./Time_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_OrcLang$Thread {
	Vtable_Object super;
};
//虚表实例
extern Vtable_OrcLang$Thread _vtable_OrcLang$Thread;

// class
struct tagOrcLang$Thread {
	Object super; 
	void  (**runFunc)(void *  self);
	void *  data ;
	void  (*run) (OrcLang$Thread *  self);
	void  (*initData) (OrcLang$Thread *  self);
	void  (*freeData) (OrcLang$Thread *  self);
	void  (*start) (OrcLang$Thread *  self);
	void  (*join) (OrcLang$Thread *  self);
};
Vtable_OrcLang$Thread* Vtable_OrcLang$Thread_init(Vtable_OrcLang$Thread* pvt);
void OrcLang$Thread_init_fields(OrcLang$Thread *self);
void OrcLang$Thread_init(OrcLang$Thread *self);
OrcLang$Thread * OrcLang$Thread_new();
void OrcLang$Thread_fini(OrcLang$Thread *self);

void  OrcLang$Thread$ctor(OrcLang$Thread *  self);
void  OrcLang$Thread$dtor(OrcLang$Thread *  self);
void  OrcLang$Thread$run(OrcLang$Thread *  self);
void  OrcLang$Thread$initData(OrcLang$Thread *  self);
void  OrcLang$Thread$freeData(OrcLang$Thread *  self);
void  OrcLang$Thread$start(OrcLang$Thread *  self);
void  OrcLang$Thread$join(OrcLang$Thread *  self);

void  OrcLang$testThread();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
