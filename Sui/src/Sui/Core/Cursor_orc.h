
typedef struct tagSuiCore$Cursor SuiCore$Cursor;
typedef struct tagVtable_SuiCore$Cursor Vtable_SuiCore$Cursor;


#ifndef define_struct___SuiCore__Cursor_orc_h__
#define define_struct___SuiCore__Cursor_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Cursor_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Cursor_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Cursor_orc_h__
#define __SuiCore__Cursor_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$Cursor {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Cursor _vtable_SuiCore$Cursor;

// class refc:0
struct tagSuiCore$Cursor {
	Object super; 
	void  (*init) (SuiCore$Cursor *  self);
	bool  (*setCursor) (SuiCore$Cursor *  self, const char *  cursor);
	void  (*setIsLocked) (SuiCore$Cursor *  self, bool  v);
	void  (*_updateCursor) (SuiCore$Cursor *  self);
	bool  isLocked ;
	Orc$String*  cursor ;
};
Vtable_SuiCore$Cursor* Vtable_SuiCore$Cursor_init(Vtable_SuiCore$Cursor* pvt);
void SuiCore$Cursor_init_fields(SuiCore$Cursor *self);
void SuiCore$Cursor_init(SuiCore$Cursor *self, void *pOwner);
SuiCore$Cursor * SuiCore$Cursor_new(void *pOwner);
void SuiCore$Cursor_fini(SuiCore$Cursor *self);

extern void  SuiCore$Cursor$init(SuiCore$Cursor *  self);
bool  SuiCore$Cursor$setCursor(SuiCore$Cursor *  self, const char *  cursor);
void  SuiCore$Cursor$setIsLocked(SuiCore$Cursor *  self, bool  v);
extern void  SuiCore$Cursor$_updateCursor(SuiCore$Cursor *  self);

SuiCore$Cursor*  SuiCore$Cursor_ins(SuiCore$Cursor **  __outRef__);
void  SuiCore$testCursor();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
