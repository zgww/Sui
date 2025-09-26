
typedef struct tagSuiView$Slider SuiView$Slider;
typedef struct tagVtable_SuiView$Slider Vtable_SuiView$Slider;


#ifndef define_struct___SuiView__Slider_orc_h__
#define define_struct___SuiView__Slider_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__Slider_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__Slider_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__Slider_orc_h__
#define __SuiView__Slider_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/Frame_orc.h"
#include "../View/Drag_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Canvas_orc.h"
#include "../../Orc/Math_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$Slider {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$Slider _vtable_SuiView$Slider;

// class refc:0
struct tagSuiView$Slider {
	SuiCore$View super; 
	SuiCore$View*  circle ;
	float  ratio ;
	float  fromValue ;
	float  toValue ;
	SuiView$Drag*  drag ;
	void  (**onChanged)(void *  self, float  v);
	void  (*fire_onChanged) (SuiView$Slider *  self);
	void  (*setRatioByValue) (SuiView$Slider *  self, float  value);
	float  (*getValue) (SuiView$Slider *  self);
	float  (*calcToX) (SuiView$Slider *  self);
	float  (*calcToY) (SuiView$Slider *  self);
	void  (*setRatio) (SuiView$Slider *  self, float  v);
};
Vtable_SuiView$Slider* Vtable_SuiView$Slider_init(Vtable_SuiView$Slider* pvt);
void SuiView$Slider_init_fields(SuiView$Slider *self);
void SuiView$Slider_init(SuiView$Slider *self, void *pOwner);
SuiView$Slider * SuiView$Slider_new(void *pOwner);
void SuiView$Slider_fini(SuiView$Slider *self);

void  SuiView$Slider$fire_onChanged(SuiView$Slider *  self);
void  SuiView$Slider$layoutContent(SuiView$Slider *  self, SuiCore$Frame *  f);
void  SuiView$Slider$setRatioByValue(SuiView$Slider *  self, float  value);
float  SuiView$Slider$getValue(SuiView$Slider *  self);
void  SuiView$Slider$ctor(SuiView$Slider *  self);
float  SuiView$Slider$calcToX(SuiView$Slider *  self);
float  SuiView$Slider$calcToY(SuiView$Slider *  self);
void  SuiView$Slider$draw_self(SuiView$Slider *  self, SuiCore$Canvas *  canvas);
void  SuiView$Slider$react(SuiView$Slider *  self);
void  SuiView$Slider$setRatio(SuiView$Slider *  self, float  v);
void  SuiView$Slider$onEvent(SuiView$Slider *  self, SuiCore$Event *  ev);

SuiView$Slider*  SuiView$mkSlider(SuiView$Slider **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
