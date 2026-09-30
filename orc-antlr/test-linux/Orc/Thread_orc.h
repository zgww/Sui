
typedef struct tagOrc$Thread Orc$Thread;
typedef struct tagVtable_Orc$Thread Vtable_Orc$Thread;


#ifndef define_struct___Orc__Thread_orc_h__
#define define_struct___Orc__Thread_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Orc__Thread_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./Orc.h"




#ifdef INCLUDE_ONLY_TYPE___Orc__Thread_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Orc__Thread_orc_h__
#define __Orc__Thread_orc_h__

//include  importHeadCode
#include "./Time_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Orc$Thread {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Orc$Thread _vtable_Orc$Thread;

// class refc:0
struct tagOrc$Thread {
	Object super; 
	void  (**runFunc)(void *  self);
	void *  data ;
	void  (*run) (Orc$Thread *  self);
	void  (*initData) (Orc$Thread *  self);
	void  (*freeData) (Orc$Thread *  self);
	void  (*start) (Orc$Thread *  self);
	void  (*join) (Orc$Thread *  self);
};
Vtable_Orc$Thread* Vtable_Orc$Thread_init(Vtable_Orc$Thread* pvt);
void Orc$Thread_init_fields(Orc$Thread *self);
void Orc$Thread_init(Orc$Thread *self, void *pOwner);
Orc$Thread * Orc$Thread_new(void *pOwner);
void Orc$Thread_fini(Orc$Thread *self);

void  Orc$Thread$ctor(Orc$Thread *  self);
void  Orc$Thread$dtor(Orc$Thread *  self);
void  Orc$Thread$run(Orc$Thread *  self);
extern void  Orc$Thread$initData(Orc$Thread *  self);
extern void  Orc$Thread$freeData(Orc$Thread *  self);
extern void  Orc$Thread$start(Orc$Thread *  self);
extern void  Orc$Thread$join(Orc$Thread *  self);

void  Orc$testThread();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
