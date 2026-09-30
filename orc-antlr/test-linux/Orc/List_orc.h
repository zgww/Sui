
typedef struct tagOrc$List Orc$List;
typedef struct tagVtable_Orc$List Vtable_Orc$List;
typedef struct tagOrc$PointerArray Orc$PointerArray;
typedef struct tagVtable_Orc$PointerArray Vtable_Orc$PointerArray;


#ifndef define_struct___Orc__List_orc_h__
#define define_struct___Orc__List_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Orc__List_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___Orc__List_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Orc__List_orc_h__
#define __Orc__List_orc_h__

//include  importHeadCode
#include "./Math_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Orc$List {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Orc$List _vtable_Orc$List;

// class refc:0
struct tagOrc$List {
	Object super; 
	void *  data ;
	void  (*add) (Orc$List *  self, Object *  obj);
	bool  (*swap) (Orc$List *  self, int  fIndex, int  tIndex);
	void  (*resize) (Orc$List *  self, int  size);
	void  (*set) (Orc$List *  self, int  idx, Object *  obj);
	bool  (*addOnce) (Orc$List *  self, Object *  obj);
	bool  (*remove) (Orc$List *  self, Object *  obj);
	int  (*removeAll) (Orc$List *  self, Object *  obj);
	Orc$List*  (*span) (Orc$List **  __outRef__, Orc$List *  self, int  fromIndex, int  toIndex);
	bool  (*has) (Orc$List *  self, Object *  obj);
	int  (*indexOfFrom) (Orc$List *  self, Object *  obj, int  start);
	int  (*indexOf) (Orc$List *  self, Object *  obj);
	void  (*insert) (Orc$List *  self, Object *  obj, int  at);
	Object *  (*_get) (Orc$List *  self, int  index);
	Object *  (*get) (Orc$List *  self, int  index);
	int  (*size) (Orc$List *  self);
	Object *  (*at) (Orc$List *  self, int  index);
	void  (*removeAt) (Orc$List *  self, int  idx);
	Object *  (*first) (Orc$List *  self);
	Object *  (*last) (Orc$List *  self);
	void  (*clear) (Orc$List *  self);
	void  (*removeRange) (Orc$List *  self, int  start, int  end);
	void  (*removeFromStart) (Orc$List *  self, int  start);
	Orc$List*  (*copy) (Orc$List **  __outRef__, Orc$List *  self);
	void  (*push) (Orc$List *  self, Object *  obj);
	void  (*pop) (Orc$List *  self);
};
Vtable_Orc$List* Vtable_Orc$List_init(Vtable_Orc$List* pvt);
void Orc$List_init_fields(Orc$List *self);
void Orc$List_init(Orc$List *self, void *pOwner);
Orc$List * Orc$List_new(void *pOwner);
void Orc$List_fini(Orc$List *self);

extern void  Orc$List$ctor(Orc$List *  self);
extern void  Orc$List$dtor(Orc$List *  self);
extern void  Orc$List$add(Orc$List *  self, Object *  obj);
extern bool  Orc$List$swap(Orc$List *  self, int  fIndex, int  tIndex);
extern void  Orc$List$resize(Orc$List *  self, int  size);
extern void  Orc$List$set(Orc$List *  self, int  idx, Object *  obj);
bool  Orc$List$addOnce(Orc$List *  self, Object *  obj);
bool  Orc$List$remove(Orc$List *  self, Object *  obj);
int  Orc$List$removeAll(Orc$List *  self, Object *  obj);
Orc$List*  Orc$List$span(Orc$List **  __outRef__, Orc$List *  self, int  fromIndex, int  toIndex);
bool  Orc$List$has(Orc$List *  self, Object *  obj);
int  Orc$List$indexOfFrom(Orc$List *  self, Object *  obj, int  start);
extern int  Orc$List$indexOf(Orc$List *  self, Object *  obj);
extern void  Orc$List$insert(Orc$List *  self, Object *  obj, int  at);
extern Object *  Orc$List$_get(Orc$List *  self, int  index);
Object *  Orc$List$get(Orc$List *  self, int  index);
extern int  Orc$List$size(Orc$List *  self);
Object *  Orc$List$at(Orc$List *  self, int  index);
extern void  Orc$List$removeAt(Orc$List *  self, int  idx);
Object *  Orc$List$first(Orc$List *  self);
Object *  Orc$List$last(Orc$List *  self);
void  Orc$List$clear(Orc$List *  self);
void  Orc$List$removeRange(Orc$List *  self, int  start, int  end);
void  Orc$List$removeFromStart(Orc$List *  self, int  start);
Orc$List*  Orc$List$copy(Orc$List **  __outRef__, Orc$List *  self);
void  Orc$List$push(Orc$List *  self, Object *  obj);
void  Orc$List$pop(Orc$List *  self);

extern int  Orc$_getPointerSize();

// 虚表
struct tagVtable_Orc$PointerArray {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Orc$PointerArray _vtable_Orc$PointerArray;

// class refc:0
struct tagOrc$PointerArray {
	Object super; 
	void **  data ;
	int  capacity ;
	int  length ;
	void *  (*get) (Orc$PointerArray *  self, int  idx);
	int  (*calcExpandNewCapacity) (Orc$PointerArray *  self, int  newCount);
	void  (*expand) (Orc$PointerArray *  self, int  newCapacity);
	void  (*expandIfNeed) (Orc$PointerArray *  self, int  newCount);
	int  (*size) (Orc$PointerArray *  self);
	void  (*add) (Orc$PointerArray *  self, void *  ptr);
	void  (*insert) (Orc$PointerArray *  self, void *  ptr, int  i);
	void  (*removeAt) (Orc$PointerArray *  self, int  i);
	void  (*clear) (Orc$PointerArray *  self);
};
Vtable_Orc$PointerArray* Vtable_Orc$PointerArray_init(Vtable_Orc$PointerArray* pvt);
void Orc$PointerArray_init_fields(Orc$PointerArray *self);
void Orc$PointerArray_init(Orc$PointerArray *self, void *pOwner);
Orc$PointerArray * Orc$PointerArray_new(void *pOwner);
void Orc$PointerArray_fini(Orc$PointerArray *self);

void  Orc$PointerArray$ctor(Orc$PointerArray *  self);
void *  Orc$PointerArray$get(Orc$PointerArray *  self, int  idx);
int  Orc$PointerArray$calcExpandNewCapacity(Orc$PointerArray *  self, int  newCount);
void  Orc$PointerArray$expand(Orc$PointerArray *  self, int  newCapacity);
void  Orc$PointerArray$expandIfNeed(Orc$PointerArray *  self, int  newCount);
void  Orc$PointerArray$dtor(Orc$PointerArray *  self);
int  Orc$PointerArray$size(Orc$PointerArray *  self);
void  Orc$PointerArray$add(Orc$PointerArray *  self, void *  ptr);
void  Orc$PointerArray$insert(Orc$PointerArray *  self, void *  ptr, int  i);
void  Orc$PointerArray$removeAt(Orc$PointerArray *  self, int  i);
void  Orc$PointerArray$clear(Orc$PointerArray *  self);

void  Orc$List_test();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
