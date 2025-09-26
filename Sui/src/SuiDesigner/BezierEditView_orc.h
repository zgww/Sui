
typedef struct tagSuiDesigner$BezierEditView SuiDesigner$BezierEditView;
typedef struct tagVtable_SuiDesigner$BezierEditView Vtable_SuiDesigner$BezierEditView;


#ifndef define_struct___SuiDesigner__BezierEditView_orc_h__
#define define_struct___SuiDesigner__BezierEditView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__BezierEditView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../nanovg/nanovg.h"
#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__BezierEditView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__BezierEditView_orc_h__
#define __SuiDesigner__BezierEditView_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Bezier_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$BezierEditView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiDesigner$BezierEditView _vtable_SuiDesigner$BezierEditView;

// class refc:0
struct tagSuiDesigner$BezierEditView {
	SuiCore$View super; 
	SuiCore$Vec2 start ;
	SuiCore$Vec2 c0 ;
	SuiCore$Vec2 c1 ;
	SuiCore$Vec2 end ;
	SuiCore$View*  startView ;
	SuiCore$View*  c0View ;
	SuiCore$View*  c1View ;
	SuiCore$View*  endView ;
	SuiView$Drag*  drag ;
	void  (**onChanged)(void *  self, SuiDesigner$BezierEditView *  v);
	float  indicatorSize ;
	void  (*setBezier) (SuiDesigner$BezierEditView *  self, SuiCore$Bezier v);
	SuiCore$Bezier (*getBezier) (SuiDesigner$BezierEditView *  self);
	void  (*fire_onChanged) (SuiDesigner$BezierEditView *  self);
	void  (*_onIndicatorEvent) (SuiDesigner$BezierEditView *  self, int  id, SuiCore$Event *  e);
};
Vtable_SuiDesigner$BezierEditView* Vtable_SuiDesigner$BezierEditView_init(Vtable_SuiDesigner$BezierEditView* pvt);
void SuiDesigner$BezierEditView_init_fields(SuiDesigner$BezierEditView *self);
void SuiDesigner$BezierEditView_init(SuiDesigner$BezierEditView *self, void *pOwner);
SuiDesigner$BezierEditView * SuiDesigner$BezierEditView_new(void *pOwner);
void SuiDesigner$BezierEditView_fini(SuiDesigner$BezierEditView *self);

void  SuiDesigner$BezierEditView$setBezier(SuiDesigner$BezierEditView *  self, SuiCore$Bezier v);
SuiCore$Bezier SuiDesigner$BezierEditView$getBezier(SuiDesigner$BezierEditView *  self);
void  SuiDesigner$BezierEditView$fire_onChanged(SuiDesigner$BezierEditView *  self);
void  SuiDesigner$BezierEditView$layoutContent(SuiDesigner$BezierEditView *  self, SuiCore$Frame *  f);
void  SuiDesigner$BezierEditView$ctor(SuiDesigner$BezierEditView *  self);
void  SuiDesigner$BezierEditView$_onIndicatorEvent(SuiDesigner$BezierEditView *  self, int  id, SuiCore$Event *  e);
void  SuiDesigner$BezierEditView$react(SuiDesigner$BezierEditView *  self);
void  SuiDesigner$BezierEditView$draw_self(SuiDesigner$BezierEditView *  self, SuiCore$Canvas *  c);

SuiDesigner$BezierEditView*  SuiDesigner$mkBezierEditView(SuiDesigner$BezierEditView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
