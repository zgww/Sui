
typedef struct tagSuiView$ProgressView SuiView$ProgressView;
typedef struct tagVtable_SuiView$ProgressView Vtable_SuiView$ProgressView;


#ifndef define_struct___SuiView__ProgressView_orc_h__
#define define_struct___SuiView__ProgressView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__ProgressView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__ProgressView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__ProgressView_orc_h__
#define __SuiView__ProgressView_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Color_orc.h"
#include "../View/Drag_orc.h"
#include "../Core/Canvas_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Timer_orc.h"
#include "../../Orc/Math_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$ProgressView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$ProgressView _vtable_SuiView$ProgressView;

// class refc:0
struct tagSuiView$ProgressView {
	SuiCore$View super; 
	float  value ;
	float  valueForAnim ;
	SuiCore$AnimStep*  anim ;
	void  (*startValueAnim) (SuiView$ProgressView *  self);
	void  (*setValue) (SuiView$ProgressView *  self, float  v);
};
Vtable_SuiView$ProgressView* Vtable_SuiView$ProgressView_init(Vtable_SuiView$ProgressView* pvt);
void SuiView$ProgressView_init_fields(SuiView$ProgressView *self);
void SuiView$ProgressView_init(SuiView$ProgressView *self, void *pOwner);
SuiView$ProgressView * SuiView$ProgressView_new(void *pOwner);
void SuiView$ProgressView_fini(SuiView$ProgressView *self);

void  SuiView$ProgressView$ctor(SuiView$ProgressView *  self);
void  SuiView$ProgressView$startValueAnim(SuiView$ProgressView *  self);
void  SuiView$ProgressView$setValue(SuiView$ProgressView *  self, float  v);
void  SuiView$ProgressView$draw_self(SuiView$ProgressView *  self, SuiCore$Canvas *  canvas);

SuiView$ProgressView*  SuiView$mkProgressView(SuiView$ProgressView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
