
typedef struct tagOrc$Map Orc$Map;
typedef struct tagVtable_Orc$Map Vtable_Orc$Map;


#ifndef define_struct___Orc__Map_orc_h__
#define define_struct___Orc__Map_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Orc__Map_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Orc__Map_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Orc__Map_orc_h__
#define __Orc__Map_orc_h__

//include  importHeadCode
#include "./List_orc.h"
#include "./String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Orc$Map {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Orc$Map _vtable_Orc$Map;

// class refc:0
struct tagOrc$Map {
	Object super; 
	void  (*put) (Orc$Map *  self, const char *  key, Object *  obj);
	void  (*del) (Orc$Map *  self, const char *  key);
	bool  (*has) (Orc$Map *  self, const char *  key);
	Object *  (*get) (Orc$Map *  self, const char *  key);
	void  (*clear) (Orc$Map *  self);
	Orc$List*  (*keys) (Orc$List **  __outRef__, Orc$Map *  self);
	int  (*size) (Orc$Map *  self);
	void *  data ;
};
Vtable_Orc$Map* Vtable_Orc$Map_init(Vtable_Orc$Map* pvt);
void Orc$Map_init_fields(Orc$Map *self);
void Orc$Map_init(Orc$Map *self, void *pOwner);
Orc$Map * Orc$Map_new(void *pOwner);
void Orc$Map_fini(Orc$Map *self);

extern void  Orc$Map$ctor(Orc$Map *  self);
extern void  Orc$Map$dtor(Orc$Map *  self);
extern void  Orc$Map$put(Orc$Map *  self, const char *  key, Object *  obj);
extern void  Orc$Map$del(Orc$Map *  self, const char *  key);
bool  Orc$Map$has(Orc$Map *  self, const char *  key);
extern Object *  Orc$Map$get(Orc$Map *  self, const char *  key);
void  Orc$Map$clear(Orc$Map *  self);
extern Orc$List*  Orc$Map$keys(Orc$List **  __outRef__, Orc$Map *  self);
extern int  Orc$Map$size(Orc$Map *  self);

void  Orc$Map_test();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
