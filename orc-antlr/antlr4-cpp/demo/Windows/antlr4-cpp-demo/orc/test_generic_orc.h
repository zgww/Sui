
typedef struct tagSuiCore$Vtable_Object SuiCore$Vtable_Object;
typedef struct tagVtable_SuiCore$Vtable_Object Vtable_SuiCore$Vtable_Object;


#ifndef define_struct___SuiCore__test_generic_orc_h__
#define define_struct___SuiCore__test_generic_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__test_generic_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>





#ifdef INCLUDE_ONLY_TYPE___SuiCore__test_generic_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__test_generic_orc_h__
#define __SuiCore__test_generic_orc_h__

//include  importHeadCode


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$Vtable_Object {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Vtable_Object _vtable_SuiCore$Vtable_Object;

// class refc:1
struct tagSuiCore$Vtable_Object {
	Object super; 
	Object*  (*create) (Object **  __outRef__, SuiCore$Vtable_Object *  self);
};
Vtable_SuiCore$Vtable_Object* Vtable_SuiCore$Vtable_Object_init(Vtable_SuiCore$Vtable_Object* pvt);
void SuiCore$Vtable_Object_init_fields(SuiCore$Vtable_Object *self);
void SuiCore$Vtable_Object_init(SuiCore$Vtable_Object *self, void *pOwner);
SuiCore$Vtable_Object * SuiCore$Vtable_Object_new(void *pOwner);
void SuiCore$Vtable_Object_fini(SuiCore$Vtable_Object *self);

Object*  SuiCore$Vtable_Object$create(Object **  __outRef__, SuiCore$Vtable_Object *  self);

Object*  SuiCore$mkObj(Object **  __outRef__, SuiCore$Vtable_Object vt);
extern Object*  SuiCore$mkObjExtern(Object **  __outRef__, SuiCore$Vtable_Object vt);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
