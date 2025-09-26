
typedef struct tagSuiCore$NodeRegisterInfo SuiCore$NodeRegisterInfo;
typedef struct tagVtable_SuiCore$NodeRegisterInfo Vtable_SuiCore$NodeRegisterInfo;
typedef struct tagSuiCore$NodeLib SuiCore$NodeLib;
typedef struct tagVtable_SuiCore$NodeLib Vtable_SuiCore$NodeLib;


#ifndef define_struct___SuiCore__NodeLib_orc_h__
#define define_struct___SuiCore__NodeLib_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__NodeLib_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiCore__NodeLib_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__NodeLib_orc_h__
#define __SuiCore__NodeLib_orc_h__

//include  importHeadCode
#include "../../Orc/List_orc.h"
#include "../../Orc/Map_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$NodeRegisterInfo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$NodeRegisterInfo _vtable_SuiCore$NodeRegisterInfo;

// class refc:0
struct tagSuiCore$NodeRegisterInfo {
	Object super; 
	const char *  className ;
	Vtable_Object *  vtable ;
	void  (*init) (SuiCore$NodeRegisterInfo *  self, Vtable_Object *  vt);
	Object*  (*mk) (Object **  __outRef__, SuiCore$NodeRegisterInfo *  self);
};
Vtable_SuiCore$NodeRegisterInfo* Vtable_SuiCore$NodeRegisterInfo_init(Vtable_SuiCore$NodeRegisterInfo* pvt);
void SuiCore$NodeRegisterInfo_init_fields(SuiCore$NodeRegisterInfo *self);
void SuiCore$NodeRegisterInfo_init(SuiCore$NodeRegisterInfo *self, void *pOwner);
SuiCore$NodeRegisterInfo * SuiCore$NodeRegisterInfo_new(void *pOwner);
void SuiCore$NodeRegisterInfo_fini(SuiCore$NodeRegisterInfo *self);

void  SuiCore$NodeRegisterInfo$init(SuiCore$NodeRegisterInfo *  self, Vtable_Object *  vt);
Object*  SuiCore$NodeRegisterInfo$mk(Object **  __outRef__, SuiCore$NodeRegisterInfo *  self);


// 虚表
struct tagVtable_SuiCore$NodeLib {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$NodeLib _vtable_SuiCore$NodeLib;

// class refc:0
struct tagSuiCore$NodeLib {
	Object super; 
	Orc$Map*  map ;
	Orc$List*  list ;
	SuiCore$NodeRegisterInfo*  (*findByClassName) (SuiCore$NodeRegisterInfo **  __outRef__, SuiCore$NodeLib *  self, const char *  className);
	void  (*registerClass) (SuiCore$NodeLib *  self, Vtable_Object *  vt);
};
Vtable_SuiCore$NodeLib* Vtable_SuiCore$NodeLib_init(Vtable_SuiCore$NodeLib* pvt);
void SuiCore$NodeLib_init_fields(SuiCore$NodeLib *self);
void SuiCore$NodeLib_init(SuiCore$NodeLib *self, void *pOwner);
SuiCore$NodeLib * SuiCore$NodeLib_new(void *pOwner);
void SuiCore$NodeLib_fini(SuiCore$NodeLib *self);

SuiCore$NodeRegisterInfo*  SuiCore$NodeLib$findByClassName(SuiCore$NodeRegisterInfo **  __outRef__, SuiCore$NodeLib *  self, const char *  className);
void  SuiCore$NodeLib$registerClass(SuiCore$NodeLib *  self, Vtable_Object *  vt);

SuiCore$NodeLib *  SuiCore$NodeLib_use();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
