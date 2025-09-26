
typedef struct tagSuiView$Switch SuiView$Switch;
typedef struct tagVtable_SuiView$Switch Vtable_SuiView$Switch;


#ifndef define_struct___SuiView__Switch_orc_h__
#define define_struct___SuiView__Switch_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__Switch_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__Switch_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__Switch_orc_h__
#define __SuiView__Switch_orc_h__

//include  importHeadCode
#include "../Core/Node_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Timer_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/MouseEvent_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$Switch {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$Switch _vtable_SuiView$Switch;

// class refc:0
struct tagSuiView$Switch {
	SuiCore$View super; 
	SuiCore$View*  circle ;
	bool  checked ;
	SuiCore$AnimStep*  anim ;
	int  circleSize ;
	float  (*calcToX) (SuiView$Switch *  self);
	void  (*setChecked) (SuiView$Switch *  self, bool  v);
	void  (**onCheckedChanged)(void *  self, SuiView$Switch *  ins);
};
Vtable_SuiView$Switch* Vtable_SuiView$Switch_init(Vtable_SuiView$Switch* pvt);
void SuiView$Switch_init_fields(SuiView$Switch *self);
void SuiView$Switch_init(SuiView$Switch *self, void *pOwner);
SuiView$Switch * SuiView$Switch_new(void *pOwner);
void SuiView$Switch_fini(SuiView$Switch *self);

void  SuiView$Switch$ctor(SuiView$Switch *  self);
void  SuiView$Switch$react(SuiView$Switch *  self);
float  SuiView$Switch$calcToX(SuiView$Switch *  self);
void  SuiView$Switch$setChecked(SuiView$Switch *  self, bool  v);
void  SuiView$Switch$onEvent(SuiView$Switch *  self, SuiCore$Event *  ev);

SuiView$Switch*  SuiView$mkSwitch(SuiView$Switch **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
