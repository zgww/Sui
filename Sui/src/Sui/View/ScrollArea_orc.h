
typedef struct tagSuiView$ScrollModel SuiView$ScrollModel;
typedef struct tagVtable_SuiView$ScrollModel Vtable_SuiView$ScrollModel;
typedef struct tagSuiView$ScrollArea SuiView$ScrollArea;
typedef struct tagVtable_SuiView$ScrollArea Vtable_SuiView$ScrollArea;
typedef struct tagSuiView$ScrollBar SuiView$ScrollBar;
typedef struct tagVtable_SuiView$ScrollBar Vtable_SuiView$ScrollBar;


#ifndef define_struct___SuiView__ScrollArea_orc_h__
#define define_struct___SuiView__ScrollArea_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__ScrollArea_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__ScrollArea_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__ScrollArea_orc_h__
#define __SuiView__ScrollArea_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "./ViewBuilder_orc.h"
#include "./Drag_orc.h"
#include "../../SuiDesigner/Theme_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$ScrollModel {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$ScrollModel _vtable_SuiView$ScrollModel;

// class refc:0
struct tagSuiView$ScrollModel {
	Object super; 
	float  scroll_left ;
	float  scroll_top ;
	SuiCore$Vec2 (**get_scroll_size)(void *  self);
	SuiCore$Vec2 (**get_client_size)(void *  self);
	bool  (*clampScrollOffsetValid) (SuiView$ScrollModel *  self);
	void  (*on_wheel_event) (SuiView$ScrollModel *  self, SuiCore$WheelEvent *  evt);
	float  (*get_h_rate) (SuiView$ScrollModel *  self);
	float  (*get_v_rate) (SuiView$ScrollModel *  self);
	float  (*get_h_length) (SuiView$ScrollModel *  self, int  full_size);
	float  (*get_v_length) (SuiView$ScrollModel *  self, int  full_size);
	float  (*get_v_pos) (SuiView$ScrollModel *  self, float  full_size);
	float  (*calc_scroll_left_by_bar_pos) (SuiView$ScrollModel *  self, float  full_size, float  position);
	float  (*calc_scroll_top_by_bar_pos) (SuiView$ScrollModel *  self, float  full_size, float  position);
	float  (*get_h_pos) (SuiView$ScrollModel *  self, float  full_size);
	float  (*bar_length) (SuiView$ScrollModel *  self, float  rate, float  full_size, float  min_size);
};
Vtable_SuiView$ScrollModel* Vtable_SuiView$ScrollModel_init(Vtable_SuiView$ScrollModel* pvt);
void SuiView$ScrollModel_init_fields(SuiView$ScrollModel *self);
void SuiView$ScrollModel_init(SuiView$ScrollModel *self, void *pOwner);
SuiView$ScrollModel * SuiView$ScrollModel_new(void *pOwner);
void SuiView$ScrollModel_fini(SuiView$ScrollModel *self);

bool  SuiView$ScrollModel$clampScrollOffsetValid(SuiView$ScrollModel *  self);
void  SuiView$ScrollModel$on_wheel_event(SuiView$ScrollModel *  self, SuiCore$WheelEvent *  evt);
float  SuiView$ScrollModel$get_h_rate(SuiView$ScrollModel *  self);
float  SuiView$ScrollModel$get_v_rate(SuiView$ScrollModel *  self);
float  SuiView$ScrollModel$get_h_length(SuiView$ScrollModel *  self, int  full_size);
float  SuiView$ScrollModel$get_v_length(SuiView$ScrollModel *  self, int  full_size);
float  SuiView$ScrollModel$get_v_pos(SuiView$ScrollModel *  self, float  full_size);
float  SuiView$ScrollModel$calc_scroll_left_by_bar_pos(SuiView$ScrollModel *  self, float  full_size, float  position);
float  SuiView$ScrollModel$calc_scroll_top_by_bar_pos(SuiView$ScrollModel *  self, float  full_size, float  position);
float  SuiView$ScrollModel$get_h_pos(SuiView$ScrollModel *  self, float  full_size);
float  SuiView$ScrollModel$bar_length(SuiView$ScrollModel *  self, float  rate, float  full_size, float  min_size);


// 虚表
struct tagVtable_SuiView$ScrollArea {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiView$ScrollArea _vtable_SuiView$ScrollArea;

// class refc:0
struct tagSuiView$ScrollArea {
	SuiLayout$LayoutLinear super; 
	SuiView$ScrollModel*  scroll_model ;
	SuiCore$Frame contentCtx ;
	bool  useMaxWidthConstraint ;
	bool  useMinWidthConstraint ;
	Orc$String*  scrollDirection ;
	void  (**onScrollChanged)(void *  self, SuiView$ScrollArea *  area);
	SuiCore$Vec2 (*calc_scroll_size) (SuiView$ScrollArea *  self);
	SuiView$ScrollBar*  verScrollBar ;
	SuiView$ScrollBar*  horScrollBar ;
	void  (*fireScrollChanged) (SuiView$ScrollArea *  self);
	void  (*onWheelEvent) (SuiView$ScrollArea *  self, SuiCore$WheelEvent *  e);
};
Vtable_SuiView$ScrollArea* Vtable_SuiView$ScrollArea_init(Vtable_SuiView$ScrollArea* pvt);
void SuiView$ScrollArea_init_fields(SuiView$ScrollArea *self);
void SuiView$ScrollArea_init(SuiView$ScrollArea *self, void *pOwner);
SuiView$ScrollArea * SuiView$ScrollArea_new(void *pOwner);
void SuiView$ScrollArea_fini(SuiView$ScrollArea *self);

SuiCore$Vec2 SuiView$ScrollArea$calc_scroll_size(SuiView$ScrollArea *  self);
void  SuiView$ScrollArea$ctor(SuiView$ScrollArea *  self);
void  SuiView$ScrollArea$react(SuiView$ScrollArea *  self);
void  SuiView$ScrollArea$layout(SuiView$ScrollArea *  self, SuiCore$Frame *  ctx);
void  SuiView$ScrollArea$onEvent(SuiView$ScrollArea *  self, SuiCore$Event *  e);
void  SuiView$ScrollArea$fireScrollChanged(SuiView$ScrollArea *  self);
void  SuiView$ScrollArea$onWheelEvent(SuiView$ScrollArea *  self, SuiCore$WheelEvent *  e);
void  SuiView$ScrollArea$draw_children(SuiView$ScrollArea *  self, SuiCore$Canvas *  canvas);
void  SuiView$ScrollArea$draw(SuiView$ScrollArea *  self, SuiCore$Canvas *  canvas);
SuiCore$ViewBase *  SuiView$ScrollArea$hitTest(SuiView$ScrollArea *  self, float  x, float  y);


// 虚表
struct tagVtable_SuiView$ScrollBar {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$ScrollBar _vtable_SuiView$ScrollBar;

// class refc:0
struct tagSuiView$ScrollBar {
	SuiCore$View super; 
	SuiView$Drag*  drag ;
	bool  isVer ;
	SuiView$ScrollArea*  scrollArea ;
	void  (*bindScrollArea) (SuiView$ScrollBar *  self, SuiView$ScrollArea *  area);
};
Vtable_SuiView$ScrollBar* Vtable_SuiView$ScrollBar_init(Vtable_SuiView$ScrollBar* pvt);
void SuiView$ScrollBar_init_fields(SuiView$ScrollBar *self);
void SuiView$ScrollBar_init(SuiView$ScrollBar *self, void *pOwner);
SuiView$ScrollBar * SuiView$ScrollBar_new(void *pOwner);
void SuiView$ScrollBar_fini(SuiView$ScrollBar *self);

void  SuiView$ScrollBar$ctor(SuiView$ScrollBar *  self);
void  SuiView$ScrollBar$onEvent(SuiView$ScrollBar *  self, SuiCore$Event *  e);
void  SuiView$ScrollBar$setHover(SuiView$ScrollBar *  self, bool  v);
bool  SuiView$ScrollBar$canLayoutByParent(SuiView$ScrollBar *  self);
void  SuiView$ScrollBar$bindScrollArea(SuiView$ScrollBar *  self, SuiView$ScrollArea *  area);
void  SuiView$ScrollBar$draw_self(SuiView$ScrollBar *  self, SuiCore$Canvas *  canvas);

SuiView$ScrollArea*  SuiView$mkScrollArea(SuiView$ScrollArea **  __outRef__, void *  parent, long long  key);
SuiView$ScrollBar*  SuiView$mkScrollBar(SuiView$ScrollBar **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
