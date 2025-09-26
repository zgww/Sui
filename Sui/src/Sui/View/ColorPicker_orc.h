
typedef struct tagSuiView$ColorPicker SuiView$ColorPicker;
typedef struct tagVtable_SuiView$ColorPicker Vtable_SuiView$ColorPicker;


#ifndef define_struct___SuiView__ColorPicker_orc_h__
#define define_struct___SuiView__ColorPicker_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__ColorPicker_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__ColorPicker_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__ColorPicker_orc_h__
#define __SuiView__ColorPicker_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Window_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Core/Event_orc.h"
#include "../Dialog/Toast_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../View/TextView_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "./Drag_orc.h"
#include "./ColorPalete_orc.h"
#include "./ViewBuilder_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$ColorPicker {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$ColorPicker _vtable_SuiView$ColorPicker;

// class refc:0
struct tagSuiView$ColorPicker {
	SuiCore$View super; 
	void  (**onChanged)(void *  self, int  newcolor);
	void  (*fire_onChanged) (SuiView$ColorPicker *  self, int  newcolor);
	void  (*showWindow_colorPalete) (SuiView$ColorPicker *  self);
	void  (*onMouseEvent) (SuiView$ColorPicker *  self, SuiCore$MouseEvent *  me);
};
Vtable_SuiView$ColorPicker* Vtable_SuiView$ColorPicker_init(Vtable_SuiView$ColorPicker* pvt);
void SuiView$ColorPicker_init_fields(SuiView$ColorPicker *self);
void SuiView$ColorPicker_init(SuiView$ColorPicker *self, void *pOwner);
SuiView$ColorPicker * SuiView$ColorPicker_new(void *pOwner);
void SuiView$ColorPicker_fini(SuiView$ColorPicker *self);

void  SuiView$ColorPicker$fire_onChanged(SuiView$ColorPicker *  self, int  newcolor);
void  SuiView$ColorPicker$ctor(SuiView$ColorPicker *  self);
void  SuiView$ColorPicker$showWindow_colorPalete(SuiView$ColorPicker *  self);
void  SuiView$ColorPicker$onEvent(SuiView$ColorPicker *  self, SuiCore$Event *  e);
void  SuiView$ColorPicker$onMouseEvent(SuiView$ColorPicker *  self, SuiCore$MouseEvent *  me);

SuiView$ColorPicker*  SuiView$mkColorPicker(SuiView$ColorPicker **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
