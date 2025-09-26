
typedef struct tagSuiCore$TextEventBase SuiCore$TextEventBase;
typedef struct tagVtable_SuiCore$TextEventBase Vtable_SuiCore$TextEventBase;
typedef struct tagSuiCore$TextEditingEvent SuiCore$TextEditingEvent;
typedef struct tagVtable_SuiCore$TextEditingEvent Vtable_SuiCore$TextEditingEvent;
typedef struct tagSuiCore$TextInputEvent SuiCore$TextInputEvent;
typedef struct tagVtable_SuiCore$TextInputEvent Vtable_SuiCore$TextInputEvent;
typedef struct tagSuiCore$KeyEvent SuiCore$KeyEvent;
typedef struct tagVtable_SuiCore$KeyEvent Vtable_SuiCore$KeyEvent;
typedef struct tagSuiCore$WindowFocusEvent SuiCore$WindowFocusEvent;
typedef struct tagVtable_SuiCore$WindowFocusEvent Vtable_SuiCore$WindowFocusEvent;


#ifndef define_struct___SuiCore__KeyEvent_orc_h__
#define define_struct___SuiCore__KeyEvent_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__KeyEvent_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__KeyEvent_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__KeyEvent_orc_h__
#define __SuiCore__KeyEvent_orc_h__

//include  importHeadCode
#include "./Event_orc.h"
#include "./MouseEvent_orc.h"
#include "../../Orc/String_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./Window_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./App_orc.h"
#include "./Focus_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$TextEventBase {
	Vtable_SuiCore$ViewEvent super;
};
//虚表实例
extern Vtable_SuiCore$TextEventBase _vtable_SuiCore$TextEventBase;

// class refc:0
struct tagSuiCore$TextEventBase {
	SuiCore$ViewEvent super; 
	Sui$Window*  window ;
	void  (*dispatch) (SuiCore$TextEventBase *  self);
};
Vtable_SuiCore$TextEventBase* Vtable_SuiCore$TextEventBase_init(Vtable_SuiCore$TextEventBase* pvt);
void SuiCore$TextEventBase_init_fields(SuiCore$TextEventBase *self);
void SuiCore$TextEventBase_init(SuiCore$TextEventBase *self, void *pOwner);
SuiCore$TextEventBase * SuiCore$TextEventBase_new(void *pOwner);
void SuiCore$TextEventBase_fini(SuiCore$TextEventBase *self);

void  SuiCore$TextEventBase$dispatch(SuiCore$TextEventBase *  self);


// 虚表
struct tagVtable_SuiCore$TextEditingEvent {
	Vtable_SuiCore$TextEventBase super;
};
//虚表实例
extern Vtable_SuiCore$TextEditingEvent _vtable_SuiCore$TextEditingEvent;

// class refc:0
struct tagSuiCore$TextEditingEvent {
	SuiCore$TextEventBase super; 
	Orc$String*  text ;
	int  start ;
	int  length ;
	void  (*reset) (SuiCore$TextEditingEvent *  self);
	bool  (*is_editing) (SuiCore$TextEditingEvent *  self);
	int  (*total_rune_length) (SuiCore$TextEditingEvent *  self);
};
Vtable_SuiCore$TextEditingEvent* Vtable_SuiCore$TextEditingEvent_init(Vtable_SuiCore$TextEditingEvent* pvt);
void SuiCore$TextEditingEvent_init_fields(SuiCore$TextEditingEvent *self);
void SuiCore$TextEditingEvent_init(SuiCore$TextEditingEvent *self, void *pOwner);
SuiCore$TextEditingEvent * SuiCore$TextEditingEvent_new(void *pOwner);
void SuiCore$TextEditingEvent_fini(SuiCore$TextEditingEvent *self);

void  SuiCore$TextEditingEvent$reset(SuiCore$TextEditingEvent *  self);
bool  SuiCore$TextEditingEvent$is_editing(SuiCore$TextEditingEvent *  self);
int  SuiCore$TextEditingEvent$total_rune_length(SuiCore$TextEditingEvent *  self);

void  SuiCore$dispatchImeEndComposition(long long  windowId);
void  SuiCore$dispatchImeComposition(const char *  text, int  start, int  length, long long  windowId);

// 虚表
struct tagVtable_SuiCore$TextInputEvent {
	Vtable_SuiCore$TextEventBase super;
};
//虚表实例
extern Vtable_SuiCore$TextInputEvent _vtable_SuiCore$TextInputEvent;

// class refc:0
struct tagSuiCore$TextInputEvent {
	SuiCore$TextEventBase super; 
	Orc$String*  text ;
};
Vtable_SuiCore$TextInputEvent* Vtable_SuiCore$TextInputEvent_init(Vtable_SuiCore$TextInputEvent* pvt);
void SuiCore$TextInputEvent_init_fields(SuiCore$TextInputEvent *self);
void SuiCore$TextInputEvent_init(SuiCore$TextInputEvent *self, void *pOwner);
SuiCore$TextInputEvent * SuiCore$TextInputEvent_new(void *pOwner);
void SuiCore$TextInputEvent_fini(SuiCore$TextInputEvent *self);


void  SuiCore$dispatchTextInputEvent(const char *  text, long long  windowId);

// 虚表
struct tagVtable_SuiCore$KeyEvent {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_SuiCore$KeyEvent _vtable_SuiCore$KeyEvent;

// class refc:0
struct tagSuiCore$KeyEvent {
	SuiCore$Event super; 
	int  char_code ;
	Orc$String*  key ;
	bool  isKeyDown ;
	bool  isKeyUp ;
	bool  shift ;
	bool  ctrl ;
	bool  alt ;
	Sui$Window*  window ;
	void  (*setIsKeyDown) (SuiCore$KeyEvent *  self, bool  isKeyDown);
	void  (*dispatch) (SuiCore$KeyEvent *  self);
};
Vtable_SuiCore$KeyEvent* Vtable_SuiCore$KeyEvent_init(Vtable_SuiCore$KeyEvent* pvt);
void SuiCore$KeyEvent_init_fields(SuiCore$KeyEvent *self);
void SuiCore$KeyEvent_init(SuiCore$KeyEvent *self, void *pOwner);
SuiCore$KeyEvent * SuiCore$KeyEvent_new(void *pOwner);
void SuiCore$KeyEvent_fini(SuiCore$KeyEvent *self);

void  SuiCore$KeyEvent$setIsKeyDown(SuiCore$KeyEvent *  self, bool  isKeyDown);
void  SuiCore$KeyEvent$dispatch(SuiCore$KeyEvent *  self);

void  SuiCore$dispatchEventToFocusNode(SuiCore$Event *  evt, Sui$Window *  window);

// 虚表
struct tagVtable_SuiCore$WindowFocusEvent {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_SuiCore$WindowFocusEvent _vtable_SuiCore$WindowFocusEvent;

// class refc:0
struct tagSuiCore$WindowFocusEvent {
	SuiCore$Event super; 
	bool  isFocus ;
	bool  isBlur ;
	Sui$Window*  window ;
};
Vtable_SuiCore$WindowFocusEvent* Vtable_SuiCore$WindowFocusEvent_init(Vtable_SuiCore$WindowFocusEvent* pvt);
void SuiCore$WindowFocusEvent_init_fields(SuiCore$WindowFocusEvent *self);
void SuiCore$WindowFocusEvent_init(SuiCore$WindowFocusEvent *self, void *pOwner);
SuiCore$WindowFocusEvent * SuiCore$WindowFocusEvent_new(void *pOwner);
void SuiCore$WindowFocusEvent_fini(SuiCore$WindowFocusEvent *self);


void  SuiCore$dispatchWindowFocusEvent(SuiCore$WindowFocusEvent *  e);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
