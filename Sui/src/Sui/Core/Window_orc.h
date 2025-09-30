
typedef struct tagSui$Window Sui$Window;
typedef struct tagVtable_Sui$Window Vtable_Sui$Window;
typedef struct tagSui$DragCrossWindowIndicator Sui$DragCrossWindowIndicator;
typedef struct tagVtable_Sui$DragCrossWindowIndicator Vtable_Sui$DragCrossWindowIndicator;


#ifndef define_struct___Sui__Window_orc_h__
#define define_struct___Sui__Window_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sui__Window_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sui__Window_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sui__Window_orc_h__
#define __Sui__Window_orc_h__

//include  importHeadCode
#include "../Core/Vec2_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Emitter_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../Core/View_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "../Core/Inset_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/Screen_orc.h"
#include "../Core/Timer_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/Time_orc.h"
#include "./App_orc.h"
#include "./Event_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./KeyEvent_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./Focus_orc.h"
#include "./Fps_orc.h"
#include "./Canvas_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sui$Window {
	Vtable_SuiCore$Emitter super;
};
//虚表实例
extern Vtable_Sui$Window _vtable_Sui$Window;

// class refc:0
struct tagSui$Window {
	SuiCore$Emitter super; 
	long long  id ;
	SuiCore$Fps fps ;
	SuiCore$ViewBase*  rootView ;
	SuiCore$Canvas*  canvas ;
	bool  borderless ;
	void *  data ;
	void  (*setTransparent) (Sui$Window *  self);
	void  (*setRootView) (Sui$Window *  self, SuiCore$ViewBase *  v);
	void  (*cleanData) (Sui$Window *  self);
	void  (*initData) (Sui$Window *  self);
	void  (*show) (Sui$Window *  self);
	void  (*hide) (Sui$Window *  self);
	void  (*maximize) (Sui$Window *  self);
	void  (*minimize) (Sui$Window *  self);
	void  (*normal) (Sui$Window *  self);
	void  (*enable) (Sui$Window *  self, bool  enable);
	void  (*close) (Sui$Window *  self);
	void  (*setOwner) (Sui$Window *  self, Sui$Window *  ownerWindow);
	int  layoutTimes ;
	void  (*layoutAndDraw) (Sui$Window *  self);
	void  (*layout) (Sui$Window *  self);
	void  (*draw) (Sui$Window *  self);
	bool  (*isVisible) (Sui$Window *  self);
	void  (*onDestroy) (Sui$Window *  self);
	void  (*setTitle) (Sui$Window *  self, const char *  title);
	Orc$String*  (*getTitle) (Orc$String **  __outRef__, Sui$Window *  self);
	SuiCore$Vec2 (*getPos) (Sui$Window *  self);
	void  (*setPos) (Sui$Window *  self, float  x, float  y);
	SuiCore$Vec2 (*getSize) (Sui$Window *  self);
	void  (*setSize) (Sui$Window *  self, float  x, float  y);
	void  (*setRect) (Sui$Window *  self, float  x, float  y, float  w, float  h);
	SuiCore$Vec2 (*getClientSize) (Sui$Window *  self);
	void  (*moveToCenter) (Sui$Window *  self);
	SuiCore$Inset (*getNonClientInset) (Sui$Window *  self);
};
Vtable_Sui$Window* Vtable_Sui$Window_init(Vtable_Sui$Window* pvt);
void Sui$Window_init_fields(Sui$Window *self);
void Sui$Window_init(Sui$Window *self, void *pOwner);
Sui$Window * Sui$Window_new(void *pOwner);
void Sui$Window_fini(Sui$Window *self);

void  Sui$Window$ctor(Sui$Window *  self);
extern void  Sui$Window$setTransparent(Sui$Window *  self);
void  Sui$Window$setRootView(Sui$Window *  self, SuiCore$ViewBase *  v);
void  Sui$Window$dtor(Sui$Window *  self);
extern void  Sui$Window$cleanData(Sui$Window *  self);
extern void  Sui$Window$initData(Sui$Window *  self);
extern void  Sui$Window$show(Sui$Window *  self);
extern void  Sui$Window$hide(Sui$Window *  self);
extern void  Sui$Window$maximize(Sui$Window *  self);
extern void  Sui$Window$minimize(Sui$Window *  self);
extern void  Sui$Window$normal(Sui$Window *  self);
extern void  Sui$Window$enable(Sui$Window *  self, bool  enable);
extern void  Sui$Window$close(Sui$Window *  self);
extern void  Sui$Window$setOwner(Sui$Window *  self, Sui$Window *  ownerWindow);
void  Sui$Window$layoutAndDraw(Sui$Window *  self);
extern void  Sui$Window$layout(Sui$Window *  self);
extern void  Sui$Window$draw(Sui$Window *  self);
extern bool  Sui$Window$isVisible(Sui$Window *  self);
void  Sui$Window$onDestroy(Sui$Window *  self);
extern void  Sui$Window$setTitle(Sui$Window *  self, const char *  title);
extern Orc$String*  Sui$Window$getTitle(Orc$String **  __outRef__, Sui$Window *  self);
extern SuiCore$Vec2 Sui$Window$getPos(Sui$Window *  self);
extern void  Sui$Window$setPos(Sui$Window *  self, float  x, float  y);
extern SuiCore$Vec2 Sui$Window$getSize(Sui$Window *  self);
extern void  Sui$Window$setSize(Sui$Window *  self, float  x, float  y);
extern void  Sui$Window$setRect(Sui$Window *  self, float  x, float  y, float  w, float  h);
extern SuiCore$Vec2 Sui$Window$getClientSize(Sui$Window *  self);
void  Sui$Window$moveToCenter(Sui$Window *  self);
extern SuiCore$Inset Sui$Window$getNonClientInset(Sui$Window *  self);

void  Sui$testWindow();
void  Sui$dispatchWindowFocusGainedEvent(long long  windowId);
void  Sui$dispatchWindowFocusLostEvent(long long  windowId);

// 虚表
struct tagVtable_Sui$DragCrossWindowIndicator {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sui$DragCrossWindowIndicator _vtable_Sui$DragCrossWindowIndicator;

// class refc:1
struct tagSui$DragCrossWindowIndicator {
	Object super; 
	void  (*_start) (Sui$DragCrossWindowIndicator *  self);
	void  (*_end) (Sui$DragCrossWindowIndicator *  self);
	void  (*_dragMove) (Sui$DragCrossWindowIndicator *  self);
	bool  dragging ;
	void  (*start) (Sui$DragCrossWindowIndicator *  self);
	void  (*end) (Sui$DragCrossWindowIndicator *  self);
	void  (*onDragMove) (Sui$DragCrossWindowIndicator *  self, SuiCore$Vec2 clientPos);
};
Vtable_Sui$DragCrossWindowIndicator* Vtable_Sui$DragCrossWindowIndicator_init(Vtable_Sui$DragCrossWindowIndicator* pvt);
void Sui$DragCrossWindowIndicator_init_fields(Sui$DragCrossWindowIndicator *self);
void Sui$DragCrossWindowIndicator_init(Sui$DragCrossWindowIndicator *self, void *pOwner);
Sui$DragCrossWindowIndicator * Sui$DragCrossWindowIndicator_new(void *pOwner);
void Sui$DragCrossWindowIndicator_fini(Sui$DragCrossWindowIndicator *self);

extern void  Sui$DragCrossWindowIndicator$_start(Sui$DragCrossWindowIndicator *  self);
extern void  Sui$DragCrossWindowIndicator$_end(Sui$DragCrossWindowIndicator *  self);
extern void  Sui$DragCrossWindowIndicator$_dragMove(Sui$DragCrossWindowIndicator *  self);
void  Sui$DragCrossWindowIndicator$start(Sui$DragCrossWindowIndicator *  self);
void  Sui$DragCrossWindowIndicator$end(Sui$DragCrossWindowIndicator *  self);
void  Sui$DragCrossWindowIndicator$onDragMove(Sui$DragCrossWindowIndicator *  self, SuiCore$Vec2 clientPos);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
