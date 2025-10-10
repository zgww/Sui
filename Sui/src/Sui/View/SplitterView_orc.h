
typedef struct tagSuiView$SplitterView SuiView$SplitterView;
typedef struct tagVtable_SuiView$SplitterView Vtable_SuiView$SplitterView;


#ifndef define_struct___SuiView__SplitterView_orc_h__
#define define_struct___SuiView__SplitterView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__SplitterView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiView__SplitterView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__SplitterView_orc_h__
#define __SuiView__SplitterView_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../View/Drag_orc.h"
#include "../View/ViewBuilder_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../SuiDesigner/Theme_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$SplitterView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$SplitterView _vtable_SuiView$SplitterView;

// class refc:0
struct tagSuiView$SplitterView {
	SuiCore$View super; 
	SuiView$Drag*  drag ;
	int  hoverBg ;
	int  normalBg ;
	bool  isHor ;
	float  prevGrow ;
	float  nextGrow ;
};
Vtable_SuiView$SplitterView* Vtable_SuiView$SplitterView_init(Vtable_SuiView$SplitterView* pvt);
void SuiView$SplitterView_init_fields(SuiView$SplitterView *self);
void SuiView$SplitterView_init(SuiView$SplitterView *self, void *pOwner);
SuiView$SplitterView * SuiView$SplitterView_new(void *pOwner);
void SuiView$SplitterView_fini(SuiView$SplitterView *self);

void  SuiView$SplitterView$ctor(SuiView$SplitterView *  self);
void  SuiView$SplitterView$react(SuiView$SplitterView *  self);
void  SuiView$SplitterView$onEvent(SuiView$SplitterView *  self, SuiCore$Event *  e);
void  SuiView$SplitterView$onHoverChanged(SuiView$SplitterView *  self);

SuiView$SplitterView*  SuiView$mkSplitterView(SuiView$SplitterView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
