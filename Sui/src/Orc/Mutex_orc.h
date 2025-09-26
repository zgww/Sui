
typedef struct tagOrc$Mutex Orc$Mutex;
typedef struct tagVtable_Orc$Mutex Vtable_Orc$Mutex;


#ifndef define_struct___Orc__Mutex_orc_h__
#define define_struct___Orc__Mutex_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Orc__Mutex_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Orc__Mutex_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Orc__Mutex_orc_h__
#define __Orc__Mutex_orc_h__

//include  importHeadCode


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Orc$Mutex {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Orc$Mutex _vtable_Orc$Mutex;

// class refc:0
struct tagOrc$Mutex {
	Object super; 
	void *  data ;
	void  (*lock) (Orc$Mutex *  self);
	void  (*unlock) (Orc$Mutex *  self);
	bool  (*tryLock) (Orc$Mutex *  self);
	void  (*freeData) (Orc$Mutex *  self);
	void  (*initData) (Orc$Mutex *  self);
};
Vtable_Orc$Mutex* Vtable_Orc$Mutex_init(Vtable_Orc$Mutex* pvt);
void Orc$Mutex_init_fields(Orc$Mutex *self);
void Orc$Mutex_init(Orc$Mutex *self, void *pOwner);
Orc$Mutex * Orc$Mutex_new(void *pOwner);
void Orc$Mutex_fini(Orc$Mutex *self);

void  Orc$Mutex$ctor(Orc$Mutex *  self);
void  Orc$Mutex$dtor(Orc$Mutex *  self);
extern void  Orc$Mutex$lock(Orc$Mutex *  self);
extern void  Orc$Mutex$unlock(Orc$Mutex *  self);
extern bool  Orc$Mutex$tryLock(Orc$Mutex *  self);
extern void  Orc$Mutex$freeData(Orc$Mutex *  self);
extern void  Orc$Mutex$initData(Orc$Mutex *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
