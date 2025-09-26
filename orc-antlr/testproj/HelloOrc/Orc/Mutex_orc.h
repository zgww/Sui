
typedef struct tagOrcLang$Mutex OrcLang$Mutex;
typedef struct tagVtable_OrcLang$Mutex Vtable_OrcLang$Mutex;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef __Mutex_orc_h__
#define __Mutex_orc_h__

//include  importHeadCode
#include "Orc/Orc.h"
#include <stdlib.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_OrcLang$Mutex {
	Vtable_Object super;
};
//虚表实例
extern Vtable_OrcLang$Mutex _vtable_OrcLang$Mutex;

// class
struct tagOrcLang$Mutex {
	Object super; 
	void *  data ;
	void  (*lock) (OrcLang$Mutex *  self);
	void  (*unlock) (OrcLang$Mutex *  self);
	bool  (*tryLock) (OrcLang$Mutex *  self);
	void  (*freeData) (OrcLang$Mutex *  self);
	void  (*initData) (OrcLang$Mutex *  self);
};
Vtable_OrcLang$Mutex* Vtable_OrcLang$Mutex_init(Vtable_OrcLang$Mutex* pvt);
void OrcLang$Mutex_init_fields(OrcLang$Mutex *self);
void OrcLang$Mutex_init(OrcLang$Mutex *self);
OrcLang$Mutex * OrcLang$Mutex_new();
void OrcLang$Mutex_fini(OrcLang$Mutex *self);

void  OrcLang$Mutex$ctor(OrcLang$Mutex *  self);
void  OrcLang$Mutex$dtor(OrcLang$Mutex *  self);
void  OrcLang$Mutex$lock(OrcLang$Mutex *  self);
void  OrcLang$Mutex$unlock(OrcLang$Mutex *  self);
bool  OrcLang$Mutex$tryLock(OrcLang$Mutex *  self);
void  OrcLang$Mutex$freeData(OrcLang$Mutex *  self);
void  OrcLang$Mutex$initData(OrcLang$Mutex *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
