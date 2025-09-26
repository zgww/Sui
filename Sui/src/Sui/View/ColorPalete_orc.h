
typedef struct tagSuiView$ColorPalete SuiView$ColorPalete;
typedef struct tagVtable_SuiView$ColorPalete Vtable_SuiView$ColorPalete;
typedef struct tagSuiView$ColorView SuiView$ColorView;
typedef struct tagVtable_SuiView$ColorView Vtable_SuiView$ColorView;


#ifndef define_struct___SuiView__ColorPalete_orc_h__
#define define_struct___SuiView__ColorPalete_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__ColorPalete_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__ColorPalete_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__ColorPalete_orc_h__
#define __SuiView__ColorPalete_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Image_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../View/TextView_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "./Drag_orc.h"
#include "./ViewBuilder_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$ColorPalete {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$ColorPalete _vtable_SuiView$ColorPalete;

// class refc:0
struct tagSuiView$ColorPalete {
	SuiCore$View super; 
	SuiCore$Vec2 indicatorPos ;
	SuiView$Drag*  drag ;
	int  color ;
	bool  xDraggale ;
	bool  yDraggale ;
	Orc$String*  kind ;
	Orc$String*  indicatorKind ;
	void  (**onChanged)(void *  self, SuiCore$Vec2 ratio);
	SuiCore$Vec2 (*calcIndicatorPosInPixel) (SuiView$ColorPalete *  self);
	void  (*onMouseEvent) (SuiView$ColorPalete *  self, SuiCore$MouseEvent *  me);
	void  (*onDrag) (SuiView$ColorPalete *  self, SuiView$Drag *  d);
	void  (*drawCircle) (SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  x, int  y);
	void  (*drawMark) (SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  y);
	void  (*drawHue) (SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  h);
	void  (*drawAlpha) (SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  h);
	void  (*drawSv) (SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  h);
};
Vtable_SuiView$ColorPalete* Vtable_SuiView$ColorPalete_init(Vtable_SuiView$ColorPalete* pvt);
void SuiView$ColorPalete_init_fields(SuiView$ColorPalete *self);
void SuiView$ColorPalete_init(SuiView$ColorPalete *self, void *pOwner);
SuiView$ColorPalete * SuiView$ColorPalete_new(void *pOwner);
void SuiView$ColorPalete_fini(SuiView$ColorPalete *self);

SuiCore$Vec2 SuiView$ColorPalete$calcIndicatorPosInPixel(SuiView$ColorPalete *  self);
void  SuiView$ColorPalete$onEvent(SuiView$ColorPalete *  self, SuiCore$Event *  e);
void  SuiView$ColorPalete$onMouseEvent(SuiView$ColorPalete *  self, SuiCore$MouseEvent *  me);
void  SuiView$ColorPalete$onDrag(SuiView$ColorPalete *  self, SuiView$Drag *  d);
void  SuiView$ColorPalete$drawCircle(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  x, int  y);
void  SuiView$ColorPalete$drawMark(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  y);
void  SuiView$ColorPalete$drawHue(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  h);
void  SuiView$ColorPalete$drawAlpha(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  h);
void  SuiView$ColorPalete$drawSv(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  h);
void  SuiView$ColorPalete$draw_self(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas);


// 虚表
struct tagVtable_SuiView$ColorView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiView$ColorView _vtable_SuiView$ColorView;

// class refc:0
struct tagSuiView$ColorView {
	SuiLayout$LayoutLinear super; 
	SuiCore$Hsva hsva ;
	bool  showRgba ;
	bool  showHsva ;
	bool  showHsla ;
	void  (**onChanged)(void *  self, int  newcolor);
	void  (*fire_onChanged) (SuiView$ColorView *  self);
	void  (*setColor) (SuiView$ColorView *  self, int  c);
};
Vtable_SuiView$ColorView* Vtable_SuiView$ColorView_init(Vtable_SuiView$ColorView* pvt);
void SuiView$ColorView_init_fields(SuiView$ColorView *self);
void SuiView$ColorView_init(SuiView$ColorView *self, void *pOwner);
SuiView$ColorView * SuiView$ColorView_new(void *pOwner);
void SuiView$ColorView_fini(SuiView$ColorView *self);

void  SuiView$ColorView$fire_onChanged(SuiView$ColorView *  self);
void  SuiView$ColorView$setColor(SuiView$ColorView *  self, int  c);
void  SuiView$ColorView$draw_self(SuiView$ColorView *  self, SuiCore$Canvas *  canvas);
void  SuiView$ColorView$react(SuiView$ColorView *  self);

SuiView$ColorPalete*  SuiView$mkColorPalete(SuiView$ColorPalete **  __outRef__, void *  parent, long long  key);
SuiView$ColorView*  SuiView$mkColorView(SuiView$ColorView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
