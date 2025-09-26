
typedef struct tagOrcLang$Map OrcLang$Map;
typedef struct tagVtable_OrcLang$Map Vtable_OrcLang$Map;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef __Map_orc_h__
#define __Map_orc_h__

//include  importHeadCode
#include "Orc/Orc.h"
#include <stdlib.h>
#include <stdio.h>
#include "./List_orc.h"
#include "./String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_OrcLang$Map {
	Vtable_Object super;
};
//虚表实例
extern Vtable_OrcLang$Map _vtable_OrcLang$Map;

// class
struct tagOrcLang$Map {
	Object super; 
	void  (*put) (OrcLang$Map *  self, const char *  key, Object *  obj);
	void  (*del) (OrcLang$Map *  self, const char *  key);
	bool  (*has) (OrcLang$Map *  self, const char *  key);
	Object *  (*get) (OrcLang$Map *  self, const char *  key);
	void  (*clear) (OrcLang$Map *  self);
	OrcLang$List*  (*keys) (OrcLang$List **  __outRef__, OrcLang$Map *  self);
	int  (*size) (OrcLang$Map *  self);
	void *  data ;
};
Vtable_OrcLang$Map* Vtable_OrcLang$Map_init(Vtable_OrcLang$Map* pvt);
void OrcLang$Map_init_fields(OrcLang$Map *self);
void OrcLang$Map_init(OrcLang$Map *self);
OrcLang$Map * OrcLang$Map_new();
void OrcLang$Map_fini(OrcLang$Map *self);

void  OrcLang$Map$ctor(OrcLang$Map *  self);
void  OrcLang$Map$dtor(OrcLang$Map *  self);
void  OrcLang$Map$put(OrcLang$Map *  self, const char *  key, Object *  obj);
void  OrcLang$Map$del(OrcLang$Map *  self, const char *  key);
bool  OrcLang$Map$has(OrcLang$Map *  self, const char *  key);
Object *  OrcLang$Map$get(OrcLang$Map *  self, const char *  key);
void  OrcLang$Map$clear(OrcLang$Map *  self);
OrcLang$List*  OrcLang$Map$keys(OrcLang$List **  __outRef__, OrcLang$Map *  self);
int  OrcLang$Map$size(OrcLang$Map *  self);

void  OrcLang$Map_test();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
