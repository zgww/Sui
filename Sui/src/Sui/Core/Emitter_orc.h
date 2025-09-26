
typedef struct tagSuiCore$Listener SuiCore$Listener;
typedef struct tagVtable_SuiCore$Listener Vtable_SuiCore$Listener;
typedef struct tagSuiCore$Emitter SuiCore$Emitter;
typedef struct tagVtable_SuiCore$Emitter Vtable_SuiCore$Emitter;


#ifndef define_struct___SuiCore__Emitter_orc_h__
#define define_struct___SuiCore__Emitter_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Emitter_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Emitter_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Emitter_orc_h__
#define __SuiCore__Emitter_orc_h__

//include  importHeadCode
#include "../../Orc/List_orc.h"
#include "../../Orc/String_orc.h"
#include "./Event_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$Listener {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Listener _vtable_SuiCore$Listener;

// class refc:1
struct tagSuiCore$Listener {
	Object super; 
	void  (*onListenerEvent) (SuiCore$Listener *  self, SuiCore$Event *  event);
};
Vtable_SuiCore$Listener* Vtable_SuiCore$Listener_init(Vtable_SuiCore$Listener* pvt);
void SuiCore$Listener_init_fields(SuiCore$Listener *self);
void SuiCore$Listener_init(SuiCore$Listener *self, void *pOwner);
SuiCore$Listener * SuiCore$Listener_new(void *pOwner);
void SuiCore$Listener_fini(SuiCore$Listener *self);

void  SuiCore$Listener$ctor(SuiCore$Listener *  self);
void  SuiCore$Listener$onListenerEvent(SuiCore$Listener *  self, SuiCore$Event *  event);


// 虚表
struct tagVtable_SuiCore$Emitter {
	Vtable_SuiCore$Listener super;
};
//虚表实例
extern Vtable_SuiCore$Emitter _vtable_SuiCore$Emitter;

// class refc:0
struct tagSuiCore$Emitter {
	SuiCore$Listener super; 
	Orc$List*  listeners ;
	SuiCore$Listener*  listener ;
	void  (**cbOnEvent)(void *  self, SuiCore$Event *  e);
	void  (*addListenerOnce) (SuiCore$Emitter *  self, SuiCore$Listener *  listener);
	void  (*addListener) (SuiCore$Emitter *  self, SuiCore$Listener *  listener);
	void  (*removeListener) (SuiCore$Emitter *  self, SuiCore$Listener *  listener);
	void  (*emit) (SuiCore$Emitter *  self, SuiCore$Event *  event);
	void  (*onEvent) (SuiCore$Emitter *  self, SuiCore$Event *  event);
};
Vtable_SuiCore$Emitter* Vtable_SuiCore$Emitter_init(Vtable_SuiCore$Emitter* pvt);
void SuiCore$Emitter_init_fields(SuiCore$Emitter *self);
void SuiCore$Emitter_init(SuiCore$Emitter *self, void *pOwner);
SuiCore$Emitter * SuiCore$Emitter_new(void *pOwner);
void SuiCore$Emitter_fini(SuiCore$Emitter *self);

void  SuiCore$Emitter$addListenerOnce(SuiCore$Emitter *  self, SuiCore$Listener *  listener);
void  SuiCore$Emitter$addListener(SuiCore$Emitter *  self, SuiCore$Listener *  listener);
void  SuiCore$Emitter$removeListener(SuiCore$Emitter *  self, SuiCore$Listener *  listener);
void  SuiCore$Emitter$emit(SuiCore$Emitter *  self, SuiCore$Event *  event);
void  SuiCore$Emitter$onEvent(SuiCore$Emitter *  self, SuiCore$Event *  event);

SuiCore$Emitter *  SuiCore$useEbus();
void  SuiCore$testEmitter();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
