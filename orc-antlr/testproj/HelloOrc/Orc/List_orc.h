
typedef struct tagOrcLang$List OrcLang$List;
typedef struct tagVtable_OrcLang$List Vtable_OrcLang$List;
typedef struct tagOrcLang$PointerArray OrcLang$PointerArray;
typedef struct tagVtable_OrcLang$PointerArray Vtable_OrcLang$PointerArray;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef __List_orc_h__
#define __List_orc_h__

//include  importHeadCode
#include "Orc/Orc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./Math_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_OrcLang$List {
	Vtable_Object super;
};
//虚表实例
extern Vtable_OrcLang$List _vtable_OrcLang$List;

// class
struct tagOrcLang$List {
	Object super; 
	void *  data ;
	void  (*add) (OrcLang$List *  self, Object *  obj);
	bool  (*addOnce) (OrcLang$List *  self, Object *  obj);
	bool  (*remove) (OrcLang$List *  self, Object *  obj);
	bool  (*has) (OrcLang$List *  self, Object *  obj);
	int  (*indexOf) (OrcLang$List *  self, Object *  obj);
	void  (*insert) (OrcLang$List *  self, Object *  obj, int  at);
	Object *  (*_get) (OrcLang$List *  self, int  index);
	Object *  (*get) (OrcLang$List *  self, int  index);
	int  (*size) (OrcLang$List *  self);
	void  (*removeAt) (OrcLang$List *  self, int  idx);
	void  (*clear) (OrcLang$List *  self);
	void  (*removeRange) (OrcLang$List *  self, int  start, int  end);
	void  (*removeFromStart) (OrcLang$List *  self, int  start);
	OrcLang$List*  (*copy) (OrcLang$List **  __outRef__, OrcLang$List *  self);
};
Vtable_OrcLang$List* Vtable_OrcLang$List_init(Vtable_OrcLang$List* pvt);
void OrcLang$List_init_fields(OrcLang$List *self);
void OrcLang$List_init(OrcLang$List *self);
OrcLang$List * OrcLang$List_new();
void OrcLang$List_fini(OrcLang$List *self);

void  OrcLang$List$ctor(OrcLang$List *  self);
void  OrcLang$List$dtor(OrcLang$List *  self);
void  OrcLang$List$add(OrcLang$List *  self, Object *  obj);
bool  OrcLang$List$addOnce(OrcLang$List *  self, Object *  obj);
bool  OrcLang$List$remove(OrcLang$List *  self, Object *  obj);
bool  OrcLang$List$has(OrcLang$List *  self, Object *  obj);
int  OrcLang$List$indexOf(OrcLang$List *  self, Object *  obj);
void  OrcLang$List$insert(OrcLang$List *  self, Object *  obj, int  at);
Object *  OrcLang$List$_get(OrcLang$List *  self, int  index);
Object *  OrcLang$List$get(OrcLang$List *  self, int  index);
int  OrcLang$List$size(OrcLang$List *  self);
void  OrcLang$List$removeAt(OrcLang$List *  self, int  idx);
void  OrcLang$List$clear(OrcLang$List *  self);
void  OrcLang$List$removeRange(OrcLang$List *  self, int  start, int  end);
void  OrcLang$List$removeFromStart(OrcLang$List *  self, int  start);
OrcLang$List*  OrcLang$List$copy(OrcLang$List **  __outRef__, OrcLang$List *  self);

int  OrcLang$_getPointerSize();

// 虚表
struct tagVtable_OrcLang$PointerArray {
	Vtable_Object super;
};
//虚表实例
extern Vtable_OrcLang$PointerArray _vtable_OrcLang$PointerArray;

// class
struct tagOrcLang$PointerArray {
	Object super; 
	void **  data ;
	int  capacity ;
	int  length ;
	int  (*calcExpandNewCapacity) (OrcLang$PointerArray *  self, int  newCount);
	void  (*expand) (OrcLang$PointerArray *  self, int  newCapacity);
	void  (*expandIfNeed) (OrcLang$PointerArray *  self, int  newCount);
	int  (*size) (OrcLang$PointerArray *  self);
	void  (*add) (OrcLang$PointerArray *  self, void *  ptr);
	void  (*insert) (OrcLang$PointerArray *  self, void *  ptr, int  i);
	void  (*removeAt) (OrcLang$PointerArray *  self, int  i);
};
Vtable_OrcLang$PointerArray* Vtable_OrcLang$PointerArray_init(Vtable_OrcLang$PointerArray* pvt);
void OrcLang$PointerArray_init_fields(OrcLang$PointerArray *self);
void OrcLang$PointerArray_init(OrcLang$PointerArray *self);
OrcLang$PointerArray * OrcLang$PointerArray_new();
void OrcLang$PointerArray_fini(OrcLang$PointerArray *self);

void  OrcLang$PointerArray$ctor(OrcLang$PointerArray *  self);
int  OrcLang$PointerArray$calcExpandNewCapacity(OrcLang$PointerArray *  self, int  newCount);
void  OrcLang$PointerArray$expand(OrcLang$PointerArray *  self, int  newCapacity);
void  OrcLang$PointerArray$expandIfNeed(OrcLang$PointerArray *  self, int  newCount);
void  OrcLang$PointerArray$dtor(OrcLang$PointerArray *  self);
int  OrcLang$PointerArray$size(OrcLang$PointerArray *  self);
void  OrcLang$PointerArray$add(OrcLang$PointerArray *  self, void *  ptr);
void  OrcLang$PointerArray$insert(OrcLang$PointerArray *  self, void *  ptr, int  i);
void  OrcLang$PointerArray$removeAt(OrcLang$PointerArray *  self, int  i);

void  OrcLang$List_test();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
