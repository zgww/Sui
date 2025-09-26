
typedef struct tagSuiView$HoverViewEffect SuiView$HoverViewEffect;
typedef struct tagVtable_SuiView$HoverViewEffect Vtable_SuiView$HoverViewEffect;


#ifndef define_struct___SuiView__HoverViewEffect_orc_h__
#define define_struct___SuiView__HoverViewEffect_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__HoverViewEffect_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__HoverViewEffect_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__HoverViewEffect_orc_h__
#define __SuiView__HoverViewEffect_orc_h__

//include  importHeadCode
#include "../Core/Node_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Border_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "./ViewBuilder_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$HoverViewEffect {
	Vtable_SuiCore$Node super;
};
//虚表实例
extern Vtable_SuiView$HoverViewEffect _vtable_SuiView$HoverViewEffect;

// class refc:0
struct tagSuiView$HoverViewEffect {
	SuiCore$Node super; 
	int  backgroundColor ;
	SuiCore$Border*  border ;
	int  hoverBackgroundColor ;
	SuiCore$Border*  hoverBorder ;
	int  activeBackgroundColor ;
	SuiCore$Border*  activeBorder ;
	bool  isActive ;
	void  (**onClick)(void *  self, SuiCore$MouseEvent *  e);
	bool  (**onHostEvent)(void *  self, SuiCore$Event *  e);
	void  (**cbOnHoverChanged)(void *  self, SuiCore$ViewBase *  parent);
	void  (*applyEffect) (SuiView$HoverViewEffect *  self);
};
Vtable_SuiView$HoverViewEffect* Vtable_SuiView$HoverViewEffect_init(Vtable_SuiView$HoverViewEffect* pvt);
void SuiView$HoverViewEffect_init_fields(SuiView$HoverViewEffect *self);
void SuiView$HoverViewEffect_init(SuiView$HoverViewEffect *self, void *pOwner);
SuiView$HoverViewEffect * SuiView$HoverViewEffect_new(void *pOwner);
void SuiView$HoverViewEffect_fini(SuiView$HoverViewEffect *self);

void  SuiView$HoverViewEffect$onMounted(SuiView$HoverViewEffect *  self);
void  SuiView$HoverViewEffect$react(SuiView$HoverViewEffect *  self);
void  SuiView$HoverViewEffect$applyEffect(SuiView$HoverViewEffect *  self);
void  SuiView$HoverViewEffect$onUnmounting(SuiView$HoverViewEffect *  self);

SuiView$HoverViewEffect*  SuiView$mkHoverViewEffect(SuiView$HoverViewEffect **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
