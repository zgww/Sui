
typedef struct tagSuiCore$Event SuiCore$Event;
typedef struct tagVtable_SuiCore$Event Vtable_SuiCore$Event;


#ifndef define_struct___SuiCore__Event_orc_h__
#define define_struct___SuiCore__Event_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Event_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Event_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Event_orc_h__
#define __SuiCore__Event_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$Event {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Event _vtable_SuiCore$Event;

// class refc:0
struct tagSuiCore$Event {
	Object super; 
	Orc$String*  name ;
	int  isStopPropagation ;
	void  (*stopPropagation) (SuiCore$Event *  self);
	void  (*stopImmediatePropagation) (SuiCore$Event *  self);
};
Vtable_SuiCore$Event* Vtable_SuiCore$Event_init(Vtable_SuiCore$Event* pvt);
void SuiCore$Event_init_fields(SuiCore$Event *self);
void SuiCore$Event_init(SuiCore$Event *self, void *pOwner);
SuiCore$Event * SuiCore$Event_new(void *pOwner);
void SuiCore$Event_fini(SuiCore$Event *self);

void  SuiCore$Event$stopPropagation(SuiCore$Event *  self);
void  SuiCore$Event$stopImmediatePropagation(SuiCore$Event *  self);

void  SuiCore$testEvent();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
